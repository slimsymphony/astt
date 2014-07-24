using System.IO;
using System.Management;
using System.Security.AccessControl;
using System.Security.Principal;

namespace LeaderFollowerInterface
{
    public static class FolderShare
    {
        public static void CreateShare(string shareFolder, string shareName)
        {
            // Check if the share already exists, or if a different folder is shared with the same sharename
            if (checkExistingShare(shareFolder, shareName))
                return;

            // Share the folder with everyone.
            NTAccount ntAccount = new NTAccount("Everyone");

            // Get the group’s Security Identifier (SID).
            SecurityIdentifier oGrpSid = (SecurityIdentifier)ntAccount.Translate(typeof(SecurityIdentifier));
            byte[] utenteSidArray = new byte[oGrpSid.BinaryLength];
            oGrpSid.GetBinaryForm(utenteSidArray, 0);

            // Create a trustee instance from the group SID above
            ManagementObject oGrpTrustee = new ManagementClass(new ManagementPath("Win32_Trustee"), null);
            oGrpTrustee["Name"] = "Everyone";
            oGrpTrustee["SID"] = utenteSidArray;

            // Create an Access Control Entry object. Give full access to the folder and allow sub folder to inherit
            ManagementObject oGrpAce = new ManagementClass(new ManagementPath("Win32_Ace"), null);
            oGrpAce["AccessMask"] = 2032127; // Full access
            oGrpAce["AceFlags"] = AceFlags.ObjectInherit | AceFlags.ContainerInherit; // Propagate the AccessMask to the subfolders
            oGrpAce["AceType"] = AceType.AccessAllowed;
            oGrpAce["Trustee"] = oGrpTrustee;

            // Create a security descriptor; this will contain the security information for the group
            ManagementObject oGrpSecurityDescriptor = new ManagementClass(new ManagementPath("Win32_SecurityDescriptor"), null);
            oGrpSecurityDescriptor["ControlFlags"] = 4; // SE_DACL_PRESENT
            oGrpSecurityDescriptor["DACL"] = new object[] { oGrpAce };

            // Lastly Share the directory in question and upgrade the security permissions.
            ManagementClass mc = new ManagementClass("win32_share");
            ManagementBaseObject inParams = mc.GetMethodParameters("Create");
            inParams["Description"] = "";
            inParams["Name"] = shareName;
            inParams["Path"] = shareFolder;
            inParams["Type"] = 0x0; // Disk Drive
            inParams["MaximumAllowed"] = null;
            inParams["Password"] = null;
            inParams["Access"] = oGrpSecurityDescriptor;
            mc.InvokeMethod("Create", inParams, null);
        }

        private static bool checkExistingShare(string shareFolder, string shareName)
        {
            if (!Directory.Exists(shareFolder))
                Directory.CreateDirectory(shareFolder);

            // Create an Object to query the WMI Win32_Share API for shared files
            ManagementObjectSearcher searcher = new ManagementObjectSearcher("select * from win32_share");

            // Loop through all the local shares
            foreach (ManagementObject share in searcher.Get())
            {
                string type = share["Type"].ToString();

                if (type == "0") // Check if it’s a DiskDrive                 
                {
                    string path = share["Name"].ToString(); // Getting share path name
                    if (path == shareName)
                    {
                        if (share["Path"].ToString() == shareFolder)
                            return true;

                        // Delete the share if is on a different folder
                        ManagementBaseObject outParams = share.InvokeMethod("delete", null, null);
                        if (outParams != null)
                        {
                            if (((uint)outParams.Properties["ReturnValue"].Value) == 0)
                                break;
                        }
                    }
                }
            }

            return false;
        }
    }
}
