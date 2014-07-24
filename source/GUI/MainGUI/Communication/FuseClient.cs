using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Windows;
using System.Xml;
using FuseLib;
using Marble.Model;
using Nokia.Connectivity.Messaging;
using Nokia.Connectivity.Messaging.Messages;
using System.Threading;
using System.Windows.Threading;

namespace Marble.Communication
{

    /// <summary>
    /// Type of the phone connection.
    /// <remarks>Enum constants match the exact bus name used by Fuse.</remarks>
    /// </summary>
    public enum EnumConnectionType
    {
        /// <summary>
        /// Connection type is not known.
        /// </summary>
        NotAvailable = 0,

        /// <summary>
        /// Universal Serial Bus.
        /// </summary>
        USB = 1,

        /// <summary>
        /// Transmission Control Protocol.
        /// </summary>
        TCP = 2,

        /// <summary>
        /// Fido (new trace box) debug and trace interface connected via USB.
        /// </summary>
        FIDO = 3,

        /// <summary>
        /// Musti (old trace box) debug and trace interface connected via USB.
        /// </summary>
        MUSTI_USB = 4,

        /// <summary>
        /// Musti (old trace box) debug and trace interface connected via TCP.
        /// </summary>
        MUSTI = 5,

        /// <summary>
        /// Prommer box interface connected via TCP.
        /// </summary>
        NFPD_TCP = 6,

        /// <summary>
        /// Prommer box interface connected via USB.
        /// </summary>
        NFPD_USB = 7
    }

    /// <summary>
    /// Indicates the state of the phone connection.
    /// </summary>
    public enum EnumProductPresence
    {
        /// <summary>
        /// No product detected.
        /// </summary>
        NotPresent = 0,

        /// <summary>
        /// Product is present but has not been identified yet.
        /// </summary>
        Present = 1,

        /// <summary>
        /// Product is present and identified.
        /// </summary>
        Identified = 2
    }

    /// <summary>
    /// Indicates how well two versions match each other.
    /// </summary>
    public enum EnumVersionMatch
    {
        /// <summary>
        /// Comparison couldn't be made because version info is not available.
        /// </summary>
        NotAvailable = 0,

        /// <summary>
        /// Neither version string or product code matches.
        /// </summary>
        NoMatch = 1,
        
        /// <summary>
        /// Product code is the same in both versions.
        /// </summary>
        ProductMatch = 2,

        /// <summary>
        /// Version string is the same in both versions.
        /// </summary>
        VersionMatch = 3,

        /// <summary>
        /// Match has not been verified.
        /// i.e. No match comparison has been performed.
        /// </summary>
        NotVerified = 4
    }

    /// <summary>
    /// Purpose of the phone connection.
    /// </summary>
    public enum EnumConnectionUsage
    {
        /// <summary>
        /// Used as a main phone that is being tested.
        /// </summary>
        Main = 0, 
        
        /// <summary>
        /// Used as a reference phone for interaction cases call, sms, mms etc.
        /// Reference phone should be stable already released product.
        /// </summary>
        Reference = 1, 
        
        /// <summary>
        /// Used to mediate trace messages.
        /// </summary>
        Trace = 2,

        /// <summary>
        /// Used as a remote phone that supports the testing of the main phone.
        /// Should be of the same type as the main product.
        /// </summary>
        Remote = 3
    }

    /// <summary>
    /// Helper class to implement INotifyPropertyChanged interface.
    /// </summary>
    public class NotifyPropertyChanged : System.ComponentModel.INotifyPropertyChanged
    {
        /// <summary>
        /// Event to trigger when any property is modified.
        /// </summary>
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Triggers PropertyChanged event. Called each time any property is modified.
        /// </summary>
        /// <param name="property">Name of the modified property</param>
        protected void OnPropertyChanged(string property)
        {
            System.ComponentModel.PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
                handler(this, new System.ComponentModel.PropertyChangedEventArgs(property));
        }
    }

    /// <summary>
    /// Represents the version information of a phone product or a PMD file.
    /// </summary>
    public class Version : NotifyPropertyChanged
    {
        private string date = string.Empty;
        private string rmCode = string.Empty;
        private string versionString = string.Empty;

        /// <summary>
        /// Date of the version as a string representation (DD-MM-YY e.g. 27-09-12).
        /// </summary>
        public string Date
        {
            get { return this.date; }
            set
            {
                if (this.date == value) return;

                this.date = value;
                this.OnPropertyChanged("Date");
            }
        }

        public DateTime DateAsDateTime
        {
            get
            {
                DateTime dateTime;
                if (DateTime.TryParseExact(this.date, "dd-MM-yy", new CultureInfo("fi"), DateTimeStyles.None, out dateTime))
                    return dateTime;

                return new DateTime();
            }
        }

        /// <summary>
        /// RM-Code of the product (e.g. RM-902).
        /// </summary>
        public string RMCode
        {
            get { return this.rmCode; }
            set
            {
                if (this.rmCode == value) return;

                this.rmCode = value;
                this.OnPropertyChanged("RMCode");
            }
        }

        /// <summary>
        /// Version string itself (e.g. Vp aqd12w39).
        /// </summary>
        public string VersionString
        {
            get { return this.versionString; }
            set
            {
                if (this.versionString == value) return;

                this.versionString = value;
                this.OnPropertyChanged("VersionString");
            }
        }

        /// <summary>
        /// Constructor. Initializes object with values parsed from given long version string.
        /// (e.g. Vp aqd12w30\n27-09-12\nRM-902\n(c) Nokia)
        /// </summary>
        /// <param name="versionInfo">Version string from which to parse values.</param>
        public Version(string versionInfo = null)
        {
            this.SetAllFromLongVersionString(versionInfo);
        }

        /// <summary>
        /// Constructor. Initializes object with given value(s).
        /// </summary>
        /// <param name="rmCode">RM-Code (e.g. RM-902)</param>
        /// <param name="version">Version string (e.g. Vp aqd12w39)</param>
        /// <param name="date">Date (e.g. 27-09-12)</param>
        public Version(string rmCode, string version=null, string date=null)
        {
            if (!string.IsNullOrEmpty(rmCode))
                this.RMCode = rmCode;
            if (!string.IsNullOrEmpty(version))
                this.VersionString = version;
            if (!string.IsNullOrEmpty(date))
                this.Date = date;
        }

        /// <summary>
        /// Helper method to parse all properties from one long version string.
        /// (e.g. Vp aqd12w30\n27-09-12\nRM-902\n(c) Nokia)
        /// <remarks>Either all values are succesfully parsed or none of the values.</remarks>
        /// </summary>
        /// <param name="versionInfo">Version string from which to parse values.</param>
        /// <returns>True if all values where successfully parsed otherwise false.</returns>
        public bool SetAllFromLongVersionString(string versionInfo)
        {
            if (string.IsNullOrEmpty(versionInfo)) return false;

            string[] blocks = versionInfo.Split('\n');
            if (blocks.Length < 3) return false;

            this.VersionString = blocks[0];
            this.Date = blocks[1];
            this.RMCode = blocks[2];

            return true;
        }

        /// <summary>
        /// Returns all information as a long string.
        /// </summary>
        /// <returns>VersionString, Date and RMCode separated by newline.</returns>
        public string ToLongString()
        {
            return string.Format("{0}\n{1}\n{2}", this.VersionString, this.Date, this.RMCode);
        }

        /// <summary>
        /// Determines how well two versions match each other.
        /// </summary>
        /// <returns>Match level</returns>
        public static EnumVersionMatch GetVersionMatch(Version version1, Version version2)
        {
            if (string.IsNullOrEmpty(version1.RMCode) && string.IsNullOrEmpty(version2.RMCode))
                return EnumVersionMatch.NotAvailable;

            // Exact match (correct product type and sw version)
            if (!string.IsNullOrEmpty(version1.VersionString) &&
                !string.IsNullOrEmpty(version2.VersionString) &&
                version1.RMCode.ToUpper() == version2.RMCode.ToUpper() &&
                version1.VersionString == version2.VersionString)
                return EnumVersionMatch.VersionMatch;

            // Type match (correct product type)
            if (version1.RMCode == version2.RMCode)
                return EnumVersionMatch.ProductMatch;

            // No match
            return EnumVersionMatch.NoMatch;
        }
    }

    /// <summary>
    /// Represents information of a PMD file.
    /// </summary>
    public class PMD : NotifyPropertyChanged
    {
        private string filePath = string.Empty;
        private Version version = new Version();
        private EnumVersionMatch matchLevel = EnumVersionMatch.NotVerified;

        /// <summary>
        /// File system path of the PMD file.
        /// </summary>
        public string FilePath
        {
            get { return this.filePath; }
            set
            {
                if (this.filePath == value) return;

                this.filePath = value;
                this.OnPropertyChanged("FilePath");
                this.MatchLevel = EnumVersionMatch.NotVerified;

                // Update the version information from the new path
                Version newVersion = ReadVersionString(value);
                if (newVersion != null)
                    this.Version = newVersion;
            }
        }

        /// <summary>
        /// Version information of the PMD file.
        /// </summary>
        public Version Version
        {
            get { return this.version; }
            set
            {
                if (this.version.ToLongString() == value.ToLongString()) return;

                this.version = value;
                this.OnPropertyChanged("Version");
            }
        }

        /// <summary>
        /// Indicates how well this PMD file matches to the attached product.
        /// </summary>
        public EnumVersionMatch MatchLevel
        {
            get { return this.matchLevel; }
            set
            {
                if (this.matchLevel == value) return;

                this.matchLevel = value;
                this.OnPropertyChanged("MatchLevel");
            }
        }

        /// <summary>
        /// Indicates whether the path of this PMD file was selected by user.
        /// i.e. It was not obtained automatically via product scan.
        /// This flag prevents overwriting the PMD path in subsequent scans.
        /// </summary>
        public bool IsUserSelected { get; set; }

        /// <summary>
        /// Reads version information from the PMD file.
        /// </summary>
        /// <param name="filePath">File system path of the PMD file to read.</param>
        /// <returns>Version information as a Version object or null.</returns>
        public static Version ReadVersionString(string filePath)
        {
            if (string.IsNullOrEmpty(filePath) || !File.Exists(filePath)) return null;

            string pmdVersionString;
            using (XmlReader reader = new XmlTextReader(filePath))
            {
                try
                {
                    // Causes following exception to Output although correct element is found
                    // A first chance exception of type 'System.Text.DecoderFallbackException' occurred in mscorlib.dll
                    if (!reader.ReadToFollowing("SwVersion")) return null;
                    pmdVersionString = reader.ReadElementContentAsString();
                }
                catch (XmlException)
                {
                    return null;
                }
            }            
            return new Version(pmdVersionString);
        }

        /// <summary>
        /// Constructor. Sets given path as the FilePath and reads version information from the path.
        /// </summary>
        /// <param name="filePath">File system path of the PMD file.</param>
        public PMD(string filePath=null)
        {
            if (string.IsNullOrEmpty(filePath) || !File.Exists(filePath)) return;

            this.FilePath = filePath;
            Version versionRead = ReadVersionString(filePath);
            if (versionRead != null)
                this.Version = versionRead;
        }

        /// <summary>
        /// Gets the PMD file from the phone_packages directory that best matches to the given product version.
        /// Product version string and product code are used when searching for a match.
        /// </summary>
        /// <param name="productVersion">Product version for which the PMD is selected. </param>
        /// <returns>PMD information that best matches the given product or null.</returns>
        public static PMD SelectPMDFile(Version productVersion)
        {
            if (productVersion == null) return null;

            // get all .pmd files from the phone_packages directory
            List<string> pmdList = Directory.GetFiles(@"..\phone_packages", "*.pmd").ToList();

            PMD bestMatch = null;

            // Default PMD file to use if it exists and no other matches found = local.pmd
            string defaultPMDPath = string.Empty;

            foreach (var pmdPath in pmdList)
            {
                // local.pmd doesn't contain version information
                if (pmdPath.EndsWith("local.pmd"))
                {
                    defaultPMDPath = pmdPath;
                    continue;
                }

                var tempPMD = new PMD(pmdPath);
                tempPMD.MatchLevel = Version.GetVersionMatch(tempPMD.Version, productVersion);

                // Exact match (correct product type and sw version)
                if (tempPMD.MatchLevel == EnumVersionMatch.VersionMatch)
                {
                    bestMatch = tempPMD;
                    break;
                }

                // Type match (correct product type)
                if (tempPMD.MatchLevel == EnumVersionMatch.ProductMatch &&
                    (bestMatch == null || bestMatch.Version.DateAsDateTime < tempPMD.Version.DateAsDateTime))
                    bestMatch = tempPMD;
            }

            // No matches found
            if (bestMatch == null)
            {
                // Default PMD file
                if (!string.IsNullOrEmpty(defaultPMDPath))
                    bestMatch = new PMD(defaultPMDPath);
                // First available PMD file
                else if (pmdList.Count > 0)
                    bestMatch = new PMD(pmdList[0]);
            }

            return bestMatch;
        }

        /// <summary>
        /// Performs value comparison between this and given PMD info.
        /// </summary>
        /// <param name="otherPMD">PMD info to compare with.</param>
        /// <returns>True if all values are equal otherwise false.</returns>
        public bool EqualsByValues(PMD otherPMD)
        {
            return this.FilePath == otherPMD.FilePath &&
                   this.Version.ToLongString() == otherPMD.Version.ToLongString() &&
                   this.MatchLevel == otherPMD.MatchLevel &&
                   this.IsUserSelected == otherPMD.IsUserSelected;
        }
    }

    /// <summary>
    /// Represents information about a Fuse connection.
    /// </summary>
    public class ConnectionInfo : NotifyPropertyChanged
    {
        private EnumConnectionType type = EnumConnectionType.NotAvailable;
        private string guid = string.Empty;
        private string name = string.Empty;

        /// <summary>
        /// Type of the connection.
        /// <remarks>Name of the enum constant equals the bus name of the Fuse connection.</remarks>
        /// <example>Enum.GetName(typeof(ConnectionType), this.Type)</example>
        /// </summary>
        public EnumConnectionType Type
        {
            get { return this.type; }
            set
            {
                if (this.type == value) return;

                this.type = value;
                this.OnPropertyChanged("Type");
            }
        }

        /// <summary>
        /// Global Unique Identifier of the connection. e.g. GConnId_e4ed89e1b44f4b19
        /// </summary>
        public string GUID
        {
            get { return this.guid; }
            set
            {
                if (this.guid == value) return;

                this.guid = value;
                this.OnPropertyChanged("GUID");
            }
        }

        /// <summary>
        /// Friendly name of the connection. e.g. USB1
        /// </summary>
        public string Name
        {
            get { return this.name; }
            set
            {
                if (this.name == value) return;

                this.name = value;
                this.OnPropertyChanged("Name");
            }
        }

        /// <summary>
        /// Constructor. Gets GUID and friendly name of the connection from existing Fuse connection identifier.
        /// </summary>
        /// <param name="connectionId">Existing Fuse connection identifier from which to obtain values.</param>
        public ConnectionInfo(DtlConnectionIdentifier connectionId=null)
        {
            if (connectionId == null) return;

            this.GUID = connectionId.Guid;
            this.Name = connectionId.FriendlyName;
        }

        /// <summary>
        /// Performs value comparison between this and given connection info.
        /// </summary>
        /// <param name="otherConnectionInfo">Connection info to compare with.</param>
        /// <returns>True if all values are equal otherwise false.</returns>
        public bool EqualsByValues(ConnectionInfo otherConnectionInfo)
        {
            return this.GUID == otherConnectionInfo.GUID &&
                   this.Name == otherConnectionInfo.Name &&
                   this.Type == otherConnectionInfo.Type;
        }
    }

    /// <summary>
    /// Observable collection extended with some ProductInfo specific helper methods.
    /// </summary>
    public class ProductInfoObservableCollection : System.Collections.ObjectModel.ObservableCollection<ProductInfo>
    {
        /// <summary>
        /// Gets the index of the ProductInfo that matches the given connection GUID
        /// </summary>
        /// <param name="connectionGuid">Connection GUID to look for</param>
        /// <returns>Index of the matching ProductInfo or -1 if no match</returns>
        public int IndexOfGuid(string connectionGuid)
        {
            for (int ii = 0; ii < Count; ii++)
            {
                if (this[ii].Connection.GUID == connectionGuid)
                    return ii;
            }
            return -1;
        }

        /// <summary>
        /// Removes item with a matching connection GUID
        /// </summary>
        /// <param name="connectionGuid">Connection GUID to look for</param>
        /// <returns>True if item was found and removed otherwise False</returns>
        public bool RemoveByGuid(string connectionGuid)
        {
            int index = IndexOfGuid(connectionGuid);
            if (index != -1)
            {
                RemoveAt(index);
                return true;
            }
            return false;
        }

        /// <summary>
        /// Helper for clearing IsMain, IsReference and IsTrace flags from other ProductInfo elements.
        /// Only one element can be the main, reference or trace connection at a time.
        /// </summary>
        /// <param name="connectionGuid">Connection GUID of the ProductInfo that is not cleared</param>
        /// <param name="conUse">Usage purpose of the connection</param>
        public void ClearOthers(string connectionGuid, EnumConnectionUsage conUse=EnumConnectionUsage.Main)
        {
            foreach (ProductInfo productInfo in this)
            {
                if (productInfo.Connection.GUID == connectionGuid) continue;
                switch (conUse)
                {
                    case EnumConnectionUsage.Main:
                        productInfo.IsMain = false;
                        break;
                    case EnumConnectionUsage.Reference:
                        productInfo.IsReference = false;
                        break;
                    default:
                        productInfo.IsTrace = false;
                        break;
                }
            }
        }

        /// <summary>
        /// Adds a ProductInfo element and registers for property changed event of the added element.
        /// ProductInfo is not added if item with same connection GUID already exists.
        /// </summary>
        /// <param name="productInfo">ProductInfo to be added</param>
        new public void Add(ProductInfo productInfo)
        {
            int index = IndexOfGuid(productInfo.Connection.GUID);
            if (index == -1)
            {
                productInfo.PropertyChanged += ProductInfoPropertyChanged;
                base.Add(productInfo);
            }
        }

        /// <summary>
        /// Finds or creates a product info for the given connection identifier.
        /// </summary>
        /// <param name="connectionId">Connection identifier to look for.</param>
        /// <returns>Product info corresponding to given connection identifier.</returns>
        public ProductInfo GetOrCeateProductInfo(DtlConnectionIdentifier connectionId)
        {
            var productInfo = this.FirstOrDefault(p => p.Connection.GUID == connectionId.Guid);
            if (productInfo == null)
            {
                productInfo = new ProductInfo(connectionId);
                productInfo.PropertyChanged += ProductInfoPropertyChanged;
                base.Add(productInfo);
            }
            return productInfo;
        }

        /// <summary>
        /// Event handler for modification of IsMain or IsReference properties of the ProductInfo elements.
        /// Forwards the modification event to upper level (raises event MainConnectionSet).
        /// </summary>
        /// <param name="obj">ProductInfo that was modified</param>
        /// <param name="eArgs">Property that was modified</param>
        private void ProductInfoPropertyChanged(object obj, System.ComponentModel.PropertyChangedEventArgs eArgs)
        {
            var productInfo = (ProductInfo)obj;
            switch (eArgs.PropertyName)
            {
                case "IsMain":
                    // This product was set as the main product
                    if (productInfo.IsMain)
                        ClearOthers(productInfo.Connection.GUID);
                    OnMainConnectionChanged(productInfo, eArgs.PropertyName);
                    break;
                case "IsReference":
                    // This product was set as the reference product
                    if (productInfo.IsReference)
                        ClearOthers(productInfo.Connection.GUID, EnumConnectionUsage.Reference);
                    break;
                case "IsTrace":
                    // This connection was set as the trace connection
                    if (productInfo.IsTrace)
                        ClearOthers(productInfo.Connection.GUID, EnumConnectionUsage.Trace);
                    break;
                case "IsRemote":
                    // Remote was set, count index for this product
                    if (productInfo.IsRemote)
                        productInfo.RemoteIndex = this.Count(p => p.IsRemote);
                    // Remote was unset, decrease all remote indexes above this one
                    else
                    {
                        foreach (var otherProduct in this.Where(p => p.RemoteIndex > productInfo.RemoteIndex))
                            otherProduct.RemoteIndex--;
                        productInfo.RemoteIndex = 0;
                    }
                    break;
                case "ProductPresent":
                    this.OnProductPresenceChanged(productInfo);
                    break;
            }
        }

        /// <summary>
        /// Event to trigger when IsMain property of any ProductInfo element is set to true.
        /// </summary>
        public event System.ComponentModel.PropertyChangedEventHandler MainConnectionChanged;

        /// <summary>
        /// Triggers MainConnectionChanged event. This is called when IsMain property of any ProductInfo elements is set to true.
        /// </summary>
        /// <param name="productInfo"></param>
        /// <param name="property"></param>
        private void OnMainConnectionChanged(ProductInfo productInfo, string property)
        {
            if (MainConnectionChanged != null)
                MainConnectionChanged(productInfo, new System.ComponentModel.PropertyChangedEventArgs(property));
        }

        public event System.ComponentModel.PropertyChangedEventHandler ProductPresenceChanged;

        private void OnProductPresenceChanged(ProductInfo productInfo)
        {
            if (this.ProductPresenceChanged != null)
                this.ProductPresenceChanged(productInfo, null);
        }
    }


    /// <summary>
    /// Encapsulates product and connection specific information that can be obtained directly via Fuse connection
    /// without a PMD file
    /// </summary>
    public class ProductInfo : NotifyPropertyChanged
    {
        public EventHandler<EventArgs> ProductScanned;

        private ConnectionInfo connection = new ConnectionInfo();
        private Version version = new Version();
        private PMD pmd = new PMD();

        private string productCode = "";
        private string productName = "";
        private string productImei = "";
        private EnumProductPresence productPresent = EnumProductPresence.NotPresent;
        private bool isMain;
        private bool isReference;
        private bool isTrace;
        private bool isRemote;
        private int remoteIndex;

        /// <summary>
        /// Contains connection specific information.
        /// </summary>
        public ConnectionInfo Connection
        {
            get { return this.connection; }
            set
            {
                if (this.connection.EqualsByValues(value)) return;

                this.connection = value;
                this.OnPropertyChanged("Connection");
            }
        }

        /// <summary>
        /// Version information about the product.
        /// Setting this also updates the PMD file.
        /// </summary>
        public Version Version
        {
            get { return this.version; }
            set
            {
                if (this.version.ToLongString() == value.ToLongString()) return;

                this.version.PropertyChanged -= this.PropertyOfChildChanged;
                value.PropertyChanged += this.PropertyOfChildChanged;

                this.version = value;
                this.OnPropertyChanged("Version");

                var bestPMD = PMD.SelectPMDFile(this.Version);

                // Update PMD file
                if (!this.PMD.IsUserSelected || bestPMD.MatchLevel == EnumVersionMatch.VersionMatch)
                    this.PMD = PMD.SelectPMDFile(this.Version);
                // Update PMD match level
                else
                    this.PMD.MatchLevel = Version.GetVersionMatch(this.PMD.Version, value);
            }
        }

        /// <summary>
        /// Information about the assigned PMD file.
        /// </summary>
        public PMD PMD
        {
            get { return this.pmd; }
            set
            {
                if (this.pmd.EqualsByValues(value)) return;

                this.pmd.PropertyChanged -= this.PropertyOfChildChanged;
                value.PropertyChanged += this.PropertyOfChildChanged;

                this.pmd = value;
                this.OnPropertyChanged("PMD");
                // Update PMD match level
                this.PMD.MatchLevel = Version.GetVersionMatch(value.Version, this.Version);
            }
        }

        private SimModel sim1;

        /// <summary>
        /// International Mobile Subscriber Identity of the primary sim.
        /// </summary>
        public SimModel SIM1
        {
            get { return this.sim1; }
            set
            {
                if (value == this.sim1) return;

                this.sim1 = value;
                OnPropertyChanged("IMSI1");
            }
        }

        private SimModel sim2;

        /// <summary>
        /// International Mobile Subscriber Identity of the secondary sim.
        /// </summary>
        public SimModel SIM2
        {
            get { return this.sim2; }
            set
            {
                if (value == this.sim2) return;
                
                this.sim2 = value;
                OnPropertyChanged("IMSI2");
            }
        }

        /// <summary>
        /// Some product identifier e.g. 059C0W7
        /// </summary>
        public string ProductCode
        {
            get { return productCode; }
            set
            {
                if (productCode == value) return;
                productCode = value;
                OnPropertyChanged("ProductCode");
            }
        }

        /// <summary>
        /// Name of the product that is stored in phone. e.g. Nokia C3-03
        /// </summary>
        public string ProductName
        {
            get { return productName; }
            set
            {
                if (productName == value) return;
                productName = value;
                OnPropertyChanged("ProductName");
            }
        }

        /// <summary>
        /// Primary IMEI code of the product. e.g. 004402132559760
        /// </summary>
        public string ProductImei
        {
            get { return productImei; }
            set
            {
                if (productImei == value) return;
                productImei = value;
                OnPropertyChanged("ProductImei");
            }
        }

        /// <summary>
        /// Indicates product presence. 0 = not present, 1 = present, 2 = present and identified
        /// </summary>
        public EnumProductPresence ProductPresent
        {
            get { return productPresent; }
            set
            {
                if (productPresent == value) return;
                productPresent = value;
                OnPropertyChanged("ProductPresent");
            }
        }

        /// <summary>
        /// Is this connection selected as the main connection.
        /// If this is set to true IsReference and IsRemote are set to false.
        /// </summary>
        public bool IsMain
        {
            get { return this.isMain; }
            set
            {
                if (this.isMain == value) return;

                this.isMain = value;
                OnPropertyChanged("IsMain");

                if (!value) return;
                this.IsReference = false;
                this.IsRemote = false;

            }
        }

        /// <summary>
        /// Indicates whether this connection is selected as the reference connection.
        /// If this is set to true IsMain, IsRemote and IsTrace are set to false.
        /// </summary>
        public bool IsReference
        {
            get { return this.isReference; }
            set
            {
                if (this.isReference == value) return;

                this.isReference = value;
                OnPropertyChanged("IsReference");

                if (!value) return;
                this.IsMain = false;
                this.IsTrace = false;
                this.IsRemote = false;
            }
        }

        /// <summary>
        /// Indicates whether this connection is selected as the trace connection.
        /// If this is set to true IsReference and IsRemote are set to false.
        /// </summary>
        public bool IsTrace
        {
            get { return this.isTrace; }
            set
            {
                if (this.isTrace == value) return;

                this.isTrace = value;
                OnPropertyChanged("IsTrace");

                if (!value) return;
                this.IsReference = false;
                this.IsRemote = false;
            }
        }

        /// <summary>
        /// Indicates whether this connection is selected as the remote connection.
        /// If this is set to true IsMain, IsReference and IsTrace are set to false.
        /// </summary>
        public bool IsRemote
        {
            get { return this.isRemote; }
            set
            {
                if (this.isRemote == value) return;

                this.isRemote = value;
                OnPropertyChanged("IsRemote");

                if (!value) return;
                this.IsMain = false;
                this.IsReference = false;
                this.IsTrace = false;
            }
        }

        /// <summary>
        /// Index of the remote phone (1,2,3,4, etc.)
        /// </summary>
        public int RemoteIndex
        {
            get { return this.remoteIndex; }
            set
            {
                if (this.remoteIndex == value) return;

                this.remoteIndex = value;
                OnPropertyChanged("RemoteIndex");
            }
        }

        /// <summary>
        /// Constructor. Initializes connection information from a given Fuse connection identifier.
        /// </summary>
        /// <param name="connection">Connection identifier to use as a base for this product info</param>
        public ProductInfo(DtlConnectionIdentifier connection=null)
        {
            this.Connection = new ConnectionInfo(connection);
        }

        /// <summary>
        /// Sets the use purpose of this connection (Main, Remote, Reference or Trace).
        /// </summary>
        /// <param name="usage">Use purpose as a string (Main, Referecene, Trace or Remote, Remote2, Remote3 etc.)</param>
        /// <returns></returns>
        public bool SetUsage(string usage)
        {
            if (string.IsNullOrEmpty(usage))
                return false;

            if (usage.StartsWith("Main"))
            {
                this.IsMain = true;
                return true;
            }
            if (usage.StartsWith("Reference"))
            {
                this.IsReference = true;
                return true;
            }
            if (usage.StartsWith("Trace"))
            {
                this.IsTrace = true;
                return true;
            }
            if (usage.StartsWith("Remote"))
            {
                this.isRemote = true;
                int index = 1;
                int.TryParse(usage.Substring("Remote".Length), out index);
                this.RemoteIndex = index;
                return true;
            }

            return false;
        }

        /// <summary>
        /// Gets the use purpose of this connection (Main, Remote, Reference or Trace).
        /// </summary>
        /// <returns>Use purpose as a string (Main, Referecene, Trace or Remote, Remote2, Remote3 etc.)</returns>
        public string GetUsage()
        {
            if (this.IsMain)
                return "Main";

            if (this.IsReference)
                return "Reference";

            if (this.isTrace)
                return "Trace";

            if (this.IsRemote)
                return "Remote" + this.RemoteIndex;

            return string.Empty;
        }

        /// <summary>
        /// Event handler for property changes of child properties.
        /// </summary>
        /// <param name="source"></param>
        /// <param name="e"></param>
        public void PropertyOfChildChanged(object source, System.ComponentModel.PropertyChangedEventArgs e)
        {
            // Property of Version is changed
            if (source.GetType() == typeof(Version))
            {
                if ((e.PropertyName == "RMCode" || e.PropertyName == "VersionString") && !this.PMD.IsUserSelected)
                    this.PMD = PMD.SelectPMDFile(this.Version);
            }
            // Property of PMD is changed
            else if (source.GetType() == typeof(PMD))
            {
                if (e.PropertyName == "Version")
                    this.PMD.MatchLevel = Version.GetVersionMatch(this.PMD.Version, this.Version);
            }
        }
    }

    /// <summary>
    /// Encapsulates connection related information and operations.
    /// Maintains a collection of information about currently connected products via USB.
    /// Information is updated automatically via Fuse events.
    /// </summary>
    public class FuseClient : NotifyPropertyChanged
    {
        private readonly Dispatcher mainDispatcher;

        /// <summary>
        /// Indicates whether the phone connection error message box is already displayed. This is used to restrict number of phone connection error message boxes.
        /// </summary>
        private static bool isPhoneConnectionErrorMessageBoxDisplayed;

        //helper variable for asynchronouse message sending
        private bool asynchronousResponseReceived;

        private readonly FuseLoader fuseLoader; //Fuse loader that is used to create all Fuse components.
        private readonly Detection fuseDetection; //Fuse detection class that offers all Fuse's detection services.
        private readonly ProductPresence fuseProductPresence; //Fuse's product presence service.
        private readonly ProductIdentification fuseProductIdentification; //Fuse's product identification service
        private readonly ConnectionServices connectionServices; //Fuse's main connection list services

        private IDtlConnection connection;
        private IDtlMessaging messaging;

        /// <summary>
        /// Connected products are not scanned if this is set to false.
        /// Product scans should be disabled for example during flashing.
        /// </summary>
        public bool AllowProductScan = true;

        /// <summary>
        /// Observable collection of ProductInfo elements.
        /// Contains up-to-date information about connected products.
        /// </summary>
        public ProductInfoObservableCollection Connections { get ;private set; }

        /// <summary>
        /// Gets the connections supported by Flasher.
        /// </summary>
        public List<ProductInfo> ConnectionsSupportedByFlasher
        {
            get
            {
                // Connections that have a product present and are of type USB, NFPD_TCP or NFPD_USB
                return this.Connections.Where(
                            c => c.ProductPresent != EnumProductPresence.NotPresent &&
                            (c.Connection.Type == EnumConnectionType.USB || c.Connection.Type == EnumConnectionType.NFPD_TCP ||
                             c.Connection.Type == EnumConnectionType.NFPD_USB)).ToList();
            }
        }

        /// <summary>
        /// Connections that have a product present.
        /// </summary>
        public List<ProductInfo> ConnectedProducts
        {
            get { return Connections.Where(p => p.ProductPresent > 0).ToList(); }
        }

        /// <summary>
        /// Getter for the main connection ProductInfo. May be null.
        /// </summary>
        public ProductInfo MainConnection
        {
            get { return this.Connections.FirstOrDefault(p => p.IsMain); }
        }

        /// <summary>
        /// Getter for the reference connection ProductInfo. May be null.
        /// </summary>
        public ProductInfo ReferenceConnection
        {
            get { return this.Connections.FirstOrDefault(p => p.IsReference); }
        }

        /// <summary>
        /// Getter for the trace connection ProductInfo. May be null.
        /// </summary>
        public ProductInfo TraceConnection
        {
            get { return this.Connections.FirstOrDefault(p => p.IsTrace); }
        }

        /// <summary>
        /// Getter for IEnumerable of remote connection ProductInfos.
        /// </summary>
        public IEnumerable<ProductInfo> RemoteConnections
        {
            get { return this.Connections.Where(p => p.IsRemote); }
        }

        /// <summary>
        /// Constructor.
        /// Creates Fuse access objects and registeres to all Fuse events.
        /// </summary>
        /// <param name="dispatcher">Dispatcher of the main thread of the GUI.
        /// Additions or removals to connected products collection must be executed in the main thread.</param>
        public FuseClient(Dispatcher dispatcher)
        {
            Debug.Indent();
            Debug.WriteLine("StartFuseClient");
            Debug.Flush();
            mainDispatcher = dispatcher;
            Connections = new ProductInfoObservableCollection();
            this.Connections.MainConnectionChanged += (s, e) => this.OnPropertyChanged("MainConnection");
            this.Connections.ProductPresenceChanged += (s, e) => this.UpdateConnectedProducts();

            //Create Fuse loader
            fuseLoader = new FuseLoader();            
            Debug.WriteLine("FuseLoader");
            Debug.Flush();

            // Try (3 times) creating the main Fuse components with Fuse loader
            for (int ii = 0; ii < 3; ii++)
            {
                try
                {
                    connectionServices = (ConnectionServices)fuseLoader.CreateConnectionServices();
                    Debug.WriteLine("ConnectionServices");
                    Debug.Flush();
                    fuseDetection = fuseLoader.CreateDetection();
                    Debug.WriteLine("Detection");
                    Debug.Flush();
                    fuseProductPresence = fuseDetection.ProductPresence;
                    Debug.WriteLine("Presence");
                    Debug.Flush();
                    fuseProductIdentification = fuseDetection.ProductIdentification;
                    Debug.WriteLine("Identification");
                    Debug.Flush();
                    break;
                }
                catch (System.Runtime.InteropServices.COMException)
                {
                    // TODO: dispose components that were succesfully created before creating them again
                    Console.WriteLine("Failed to load fuse components. Tried {0} times", ii + 1); 
                    if (ii >= 2)
                    {
                        MessageBox.Show("Failed to load Fuse components. Please restart the application.", "Fuse error");
                        Environment.Exit(0);
                    }
                }
            }

            //set connection list event handlers
            connectionServices.OnConnectionAdded += connectionServices_OnConnectionAdded;
            connectionServices.OnConnectionModified += connectionServices_OnConnectionModified;
            connectionServices.OnConnectionOrderChanged += connectionServices_OnConnectionOrderChanged;
            connectionServices.OnConnectionRemoved += connectionServices_OnConnectionRemoved;

            //set detection event handlers
            fuseProductPresence.OnProductPresenceChanged += fuseProductPresence_OnProductPresenceChanged;
            fuseProductIdentification.OnProductIdentified += fuseProductIdentification_OnProductIdentified;

            //register to product events (all existing connections)
            Debug.WriteLine("Registering");
            Debug.Flush();
            RegisterToProductPresences();
            Debug.WriteLine("Presence registered");
            Debug.Flush();
            RegisterToProductIdentifications();
            Debug.WriteLine("Identification registered");
            Debug.Flush();

            // populate connected products collection
            ScanPhones();
            Debug.WriteLine("Scanned");
            Debug.Flush();

            // Set previously used connection usages if possible
            //if (!this.UsePreviousConnections())
            //{
            //    // Select Aqua as the main connection if possible
            //    // Aqua - DS EU RM-902, SS EU RM-899, DS US RM-903, SS US RM-900 

            //    foreach (string rmCode in new[]
            //        {
            //            "RM-902", "RM-899", "RM-903", "RM-900"
            //        })
            //    {
            //        // Stop on correct type match
            //        EnumVersionMatch match = SelectConnection(new Version(rmCode: rmCode));
            //        if (match == EnumVersionMatch.VersionMatch ||
            //            match == EnumVersionMatch.ProductMatch)
            //            break;
            //    }
            //}

            Debug.WriteLine("EndFuseClient");
            Debug.Flush();
        }

        /*        
        ~FuseClient()
        {
            UnregisterAll();
            System.Runtime.InteropServices.Marshal.ReleaseComObject(fuseProductIdentification);
            System.Runtime.InteropServices.Marshal.ReleaseComObject(fuseProductPresence);
            System.Runtime.InteropServices.Marshal.ReleaseComObject(fuseDetection);
            System.Runtime.InteropServices.Marshal.ReleaseComObject(connectionServices);
            System.Runtime.InteropServices.Marshal.ReleaseComObject(fuseLoader);
        }

        private void UnregisterAll()
        {
            ConnectionIdentifiers connections = connectionServices.ConnectionIdentifiers;
            for (int i = 1; i <= connections.Count; i++)
            {
                fuseProductPresence.UnregisterProductPresenceEvents(connections[i]);
                fuseProductIdentification.UnregisterProductIdentificationEvents(connections[i]);
            }
        }
        */

        /// <summary>
        /// Updates connected products. Use this instead of "this.OnPropertyChanged("ConnectedProducts");" to update all related collections.
        /// </summary>
        public void UpdateConnectedProducts()
        {
            this.OnPropertyChanged("ConnectedProducts");
            this.OnPropertyChanged("ConnectionsSupportedByFlasher");
        }

        /// <summary>
        /// Parses bus name (e.g. USB or TCP) of the connection from the connection configuration string.
        /// </summary>
        /// <param name="connectionString">Connection configuration string from which to parse the bus name.</param>
        /// <returns>Bus name or empty string.</returns>
        public static string GetBusName(string connectionString)
        {
            const string searchStr = "BUS_NAME:";
            connectionString = connectionString.ToUpper();
            if (!connectionString.Contains(searchStr)) return string.Empty;

            int startIndex = connectionString.IndexOf(searchStr, StringComparison.Ordinal) + searchStr.Length;
            int endIndex = connectionString.Contains(' ')
                               ? connectionString.IndexOf(' ', startIndex)
                               : connectionString.Length;
            return connectionString.Substring(startIndex, endIndex - startIndex);
        }

        /// <summary>
        /// Parses connection type from the connection configuration string.
        /// </summary>
        /// <param name="connectionString">Connection configuration string from which to parse the connection type.</param>
        /// <returns>Parsed connection type or ConnectionType.NotAvailable</returns>
        public static EnumConnectionType GetConnectionType(string connectionString)
        {
            EnumConnectionType connectionType;
            if (!Enum.TryParse(GetBusName(connectionString), true, out connectionType))
                connectionType = EnumConnectionType.NotAvailable;
            return connectionType;
        }

        /// <summary>
        /// Populates connected products collection.
        /// Goes through all defined Fuse connections and checks for connected products.
        /// Product info is scanned if connected product is found.
        /// </summary>
        public void ScanPhones()
        {
            Debug.Indent();
            for (int ii = 1; ii <= connectionServices.ConnectionIdentifiers.Count; ii++)
            {
                DtlConnectionIdentifier connectionId = connectionServices.ConnectionIdentifiers[ii];
                Debug.WriteLine(connectionId.FriendlyName);
                Debug.Flush();

                //if (productInfo.Connection.Type != EnumConnectionType.USB)
                
                // Take this into use when TCP and Fido connections are supported in Fuse
                /*if (fuseProductPresence.ReadProductPresence(connectionId) != EnumDtlProductPresenceState.eDtlProductStatePresent)
                    continue;*/
                var productInfo = this.Connections.GetOrCeateProductInfo(connectionId);
                Debug.WriteLine("Created" + connectionId.FriendlyName);
                Debug.Flush();

                // Scan product information
                this.ScanProductInfo(connectionId, productInfo);
            }
        }

        /// <summary>
        /// Scans product information from a Fuse connection.
        /// This is the main method for populating ProductInfo objects.
        /// <remarks>
        /// Can safely be called only from the UI thread.
        /// Because of accessing properties of App.Current.
        /// </remarks>
        /// </summary>
        /// <param name="connectionId">Fuse connection identifier from which to scan information</param>
        /// <param name="productInfo">Product info to which the information is stored</param>
        /// <returns>True on success otherwise false</returns>
        public bool ScanProductInfo(DtlConnectionIdentifier connectionId, ProductInfo productInfo)
        {
            // Product scan not allowed
            if (!this.AllowProductScan) return false;

            // Read the connection type of the connection
            DtlConnection dtlConnection = fuseLoader.CreateDtlConnection();
            Debug.WriteLine("DtlCreated");
            Debug.Flush();
            try
            {
                dtlConnection.Attach(connectionId);
                Debug.WriteLine("Attach");
                Debug.Flush();
                productInfo.Connection.Type = GetConnectionType(dtlConnection.GetConfiguration());
                Debug.WriteLine("Connection Type");
                Debug.Flush();
            }
            catch (System.Runtime.InteropServices.COMException)
            {
                // Seen error - DTL Connection: Correct response was not received, last error code = 0x102
            }
            finally
            {
                dtlConnection.Detach();
                Debug.WriteLine("Detach");
                Debug.Flush();
            }

            // For now skip all other connection but USB
            if (productInfo.Connection.Type != EnumConnectionType.USB)
                return false;

            // Fuse product presence/identification is not supported for MUSTI and MUSTI_USB connections.
            // TCP is supported from 2012.27.4.251 version onwards.
            // Fido is supported from 2013.4.1.288 version onwards.
            // Not supported connections are displayed in UI without scanning them.
            if ((productInfo.Connection.Type == EnumConnectionType.TCP && String.Compare(fuseLoader.FuseVersion, "2012.27.4.251", StringComparison.Ordinal) < 0) ||
                (productInfo.Connection.Type == EnumConnectionType.FIDO && String.Compare(fuseLoader.FuseVersion, "2013.4.1.288", StringComparison.Ordinal) < 0) ||
                productInfo.Connection.Type == EnumConnectionType.MUSTI ||
                productInfo.Connection.Type == EnumConnectionType.MUSTI_USB)
            {
                productInfo.ProductPresent = EnumProductPresence.Present;

                // Select first available PMD file if it has not been selected by user previously
                //if (!productInfo.PMD.IsUserSelected)
                //    productInfo.PMD = PMD.SelectPMDFile(productInfo.Version);

                return true;
            }

            // Check product presence
            if (fuseProductPresence.ReadProductPresence(connectionId) !=
                EnumDtlProductPresenceState.eDtlProductStatePresent) return false;

            Debug.WriteLine("Product present");
            Debug.Flush();
            productInfo.ProductPresent = EnumProductPresence.Present;

            // Check product identity
            ProductIdentity productIdentity;
            try
            {
                productIdentity = fuseProductIdentification.ReadProductIdentity(
                    connectionId, (uint)EnumProductIdentification.eProductIdentificationAll);
            }
                // COMException is raised if USB is jammed (phone is connected but identity can't be read)
                // Occurs also when disconnecting phone when scanning is in progress
            catch (System.Runtime.InteropServices.COMException)
            {
                // Skip error handling
                FuseClient.isPhoneConnectionErrorMessageBoxDisplayed = true;

                // Multiple phone connection error message boxes are not displayed.
                if (FuseClient.isPhoneConnectionErrorMessageBoxDisplayed) return false;

                string message = String.Format("{0}: Phone can be detected but the connection attempt to it fails.\n" +
                                               "Try:\n1. Re-plugging the device\n" + 
                                               "2. Re-creating the connection from Fuse\n" + 
                                               "3. Restarting the device\n4. Restarting the computer",
                                               connectionId.FriendlyName);
                // For some reason displaying a message box before GUI startup prevents the main window startup
                // Below property accesses require that this code is executed in the main UI thread
                if (Application.Current.MainWindow != null && Application.Current.MainWindow.GetType() != typeof(Views.Dialogs.MarbleSplashScreen))
                {
                    FuseClient.isPhoneConnectionErrorMessageBoxDisplayed = true;

                    MessageBox.Show(Application.Current.MainWindow, message, "Error in connecting to phone");

                    FuseClient.isPhoneConnectionErrorMessageBoxDisplayed = false;
                }
                return false;
            }

            if (productIdentity == null) return false;

            // Read product information
            productInfo.ProductCode = productIdentity.GetIdentityValue(EnumProductIdentification.eProductIdentificationProductCode);
            // productInfo.Version.RMCode = productIdentity.GetIdentityValue(EnumProductIdentification.eProductIdentificationProductType);
            productInfo.ProductName = productIdentity.GetIdentityValue(EnumProductIdentification.eProductIdentificationProductName);

            // Skip "bad" products
            if (productInfo.ProductName == "Nokia XXX")
            {
                productInfo.ProductPresent = EnumProductPresence.NotPresent;
                return false;
            }
                    
            // try to open a connection to the phone
            MessageStream messageStream = this.OpenConnection(connectionId);
            if (messageStream == null) return false;

            // query version and IMEI
            productInfo.Version = new Version(this.GetVersion(messageStream));
            productInfo.ProductImei = this.GetImei(messageStream);

            // query SIM IMSIs
            productInfo.SIM1 = this.GetSimIMSI(messageStream);
            productInfo.SIM2 = this.GetSimIMSI(messageStream, 2);

            this.CloseConnection(messageStream);

            productInfo.ProductPresent = EnumProductPresence.Identified;

            // trigger product scanned event
            if (productInfo.ProductScanned != null) productInfo.ProductScanned(productInfo, null);

            return true;
        }

        /// <summary>
        /// Takes previously saved connection selections into use.
        /// Sets usages (Main, Remote, Reference or Trace) to correct connections.
        /// </summary>
        /// <returns></returns>
        public bool UsePreviousConnections()
        {
            bool connectionsSet = false;
            foreach (var item in MarbleSettingsModel.RecentConnections)
            {
                var matchingConnection = ConnectedProducts.FirstOrDefault(con => con.Connection.GUID == item.Value);
                if (matchingConnection == null) continue;

                if (matchingConnection.SetUsage(item.Key))
                    connectionsSet = true;
            }

            return connectionsSet;
        }

        /// <summary>
        /// Writes currently selected connections to xml file.
        /// Same selections can be then restored on next GUI startup.
        /// </summary>
        public void SaveUsedConnections()
        {
            MarbleSettingsModel.RecentConnections.Clear();

            foreach (var presentConnection in this.ConnectedProducts)
            {
                var usage = presentConnection.GetUsage();
                if (!string.IsNullOrEmpty(usage))
                    MarbleSettingsModel.RecentConnections.Add(usage, presentConnection.Connection.GUID);
            }
            MarbleSettingsModel.UpdateRecentConnections();
        }

        /// <summary>
        /// Selects the best matching main connection of the connected products.
        /// Version string match is tried first then type match.
        /// First available connection is selected if any kind of match couldn't be found.
        /// MainProduct is set accordingly.
        /// </summary>
        /// <param name="wantedVersion">Version to look for.</param>
        /// <returns>Version match</returns>
        public EnumVersionMatch SelectConnection(Version wantedVersion)
        {
            var returnValue = EnumVersionMatch.NotAvailable;
            ProductInfo bestMatchingConnection = null;

            // Check all connection with product present
            foreach (ProductInfo product in Connections.Where(p => p.ProductPresent > (int)EnumProductPresence.NotPresent))
            {
                var match = Version.GetVersionMatch(wantedVersion, product.Version);

                // version match
                if (match == EnumVersionMatch.VersionMatch)
                {
                    product.IsMain = true;
                    return EnumVersionMatch.VersionMatch;
                }

                // type match
                if (match == EnumVersionMatch.ProductMatch && bestMatchingConnection == null)
                {
                    bestMatchingConnection = product;
                    returnValue = EnumVersionMatch.ProductMatch;
                }
            }

            // any connected phone
            if (returnValue == 0 && Connections.Count > 0)
            {
                bestMatchingConnection = Connections[0];
                returnValue = EnumVersionMatch.NoMatch;
            }

            if (bestMatchingConnection != null)
                bestMatchingConnection.IsMain = true;

            return returnValue;
        }

        /// <summary>
        /// Sends a given request to given connection.
        /// Creates and disposes connection, messaging and messagestream objects.
        /// </summary>
        /// <param name="connectionIdentifier">Identifier of the connection to send the request</param>
        /// <param name="request">Request to send. e.g. instance of PhonetMessage or IsiMessage</param>
        /// <returns>Message object gotten as a response</returns>
        private Message SendRequest(DtlConnectionIdentifier connectionIdentifier, Message request)
        {
            if (fuseProductPresence.ReadProductPresence(connectionIdentifier) !=
                EnumDtlProductPresenceState.eDtlProductStatePresent)
            {
                Console.WriteLine("Error: Product is not present");
                return null;
            }

            IDtlConnection dtlConnection = fuseLoader.CreateDtlConnection();
            dtlConnection.Attach(connectionIdentifier);
            dtlConnection.ConnectToMedia();

            IDtlMessaging dtlMessaging = fuseLoader.CreateDtlMessaging();
            dtlMessaging.SetDtlConnection(dtlConnection);

            var messageStream = new MessageStream(dtlMessaging, "new message stream");
            Message response = messageStream.MsgIO(request);
            messageStream.Dispose();            

            System.Runtime.InteropServices.Marshal.ReleaseComObject(dtlMessaging);
            dtlConnection.DisconnectFromMedia();
            dtlConnection.Detach();
            System.Runtime.InteropServices.Marshal.ReleaseComObject(dtlConnection);

            return response;
        }

        /// <summary>
        /// Creates and opens a connection to the phone.
        /// Use this to send multiple requests to the phone without creating a new connection for each request.
        /// Remember to call closeConnection at the end.
        /// </summary>
        /// <param name="connectionId">Id of the connection to connect to.</param>
        /// <returns>Message stream attached to the connection or null on error.</returns>
        private MessageStream OpenConnection(DtlConnectionIdentifier connectionId)
        {
            connection = fuseLoader.CreateDtlConnection();
            connection.Attach(connectionId);
            try
            {
                connection.ConnectToMedia();
            }
            catch (System.Runtime.InteropServices.COMException)
            {
                connection.Detach();
                System.Runtime.InteropServices.Marshal.ReleaseComObject(connection);
                return null;
            }

            messaging = fuseLoader.CreateDtlMessaging();
            messaging.SetDtlConnection(connection);

            return new MessageStream(messaging, "new message stream");
        }

        /// <summary>
        /// Releases connection to the phone.
        /// Connection, messaging and message stream instances are disposed.
        /// </summary>
        /// <param name="messageStream">Message stream to close.</param>
        private void CloseConnection(MessageStream messageStream)
        {
            messageStream.Dispose();
            System.Runtime.InteropServices.Marshal.ReleaseComObject(messaging);
            connection.DisconnectFromMedia();
            connection.Detach();
            System.Runtime.InteropServices.Marshal.ReleaseComObject(connection);
        }

        /// <summary>
        /// Queries a version string from the given connection with a fixed phonet message.
        /// </summary>
        /// <param name="messageStream">Message stream to be used as a communication channel.</param>
        /// <returns>Version string returned by the phone.</returns>
        private string GetVersion(MessageStream messageStream)
        {
            // pn: dev_sw_version_get; string:PN_RPC_ARG_STRING; void:PN_RPC_ARG_VOID
            Message request = new PhoNetMessage(
                new byte[] { 0x00, 0x00, 0x10, 0xd1, 0x00, 0x05, 0x00, 0x01, 0x00, 0x03, 0x00 }, true, false);
            Message response;
            try
            {
                response = messageStream.MsgIO(request);
            }
            catch (MessagingException)
            {
                return "";
            }
            return ConvertMessageDataToString(response.Contents);
        }

        /// <summary>
        /// Queries primary IMEI code of the phone from the given connection with a fixed isi message.
        /// </summary>
        /// <param name="messageStream">Message stream to be used as a communication channel.</param>
        /// <returns>IMEI code returned by the phone.</returns>
        private string GetImei(MessageStream messageStream)
        {
            // isi: INFO_SERIAL_NUMBER_READ_REQ; target:INFO_SN_IMEI_PLAIN
            Message request = new IsiMessage(
                new byte[] { 0x00, 0x00, 0x10, 0x1b, 0x00, 0x05, 0x00, 0x01, 0x02, 0x00, 0x41 }, true, false);
            Message response;
            try
            {
                response = messageStream.MsgIO(request);
            }
            catch (MessagingException)
            {
                return "";
            }
            return ConvertMessageDataToString(response.Contents, 16);
        }

        /// <summary>
        /// Queries for the object id of the sim server (with a fixed PhoNet constant PN_SIM = 9 = 0x09).
        /// </summary>
        /// <param name="messageStream">Communication channel to the phone</param>
        /// <returns>Object id or 0x00 on error.</returns>
        private byte GetSimServerObjectId(MessageStream messageStream)
        {
            //#define PN_SIM	9	/* 0x09  [S] Generic SIM access etc. */

            //00,00,10,db,00,0e,00,01,08,01,00,00,00,00,00,09,ff,ff,ff,ff
            //PNS_NAME_QUERY_REQ:
            //   0  (8) Media.......................: 0x00               => PN_MEDIA_ROUTING_REQ
            //   1  (6) Receiver Device.............: 0x00               => PN_DEV_HOST
            //   2  (6) Sender Device...............: 0x10               => PN_DEV_PC
            //   3  (8) Resource....................: 0xDB               => PN_NAMESERVICE
            //   4 (16) Length......................: 0x000E             => 14
            //   6 (10) Receiver Object.............: 0x000              => PN_OBJ_ROUTING_REQ
            //   7 (10) Sender Object...............: 0x001              => 1
            //   8  (8) Unique Transaction ID.......: 0x06               => 6
            //   9  (8) Sub Function................: 0x01               => PNS_NAME_QUERY_REQ
            //  10  (8) Reserved 1..................: 0x00               => 0x00
            //  11  (8) Reserved 2..................: 0x00               => 0x00
            //  12 (32) Name........................: 0x00000009         => 0x00000009 <---
            //  16 (32) Mask........................: 0xFFFFFFFF         => 0xFFFFFFFF

            Message request = new IsiMessage(
                new byte[] { 0x00, 0x00, 0x10, 0xdb, 0x00, 0x0e, 0x00, 0x01, 0x08, 0x01,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0xff, 0xff, 0xff, 0xff }, true, false);
            Message response;
            try
            {
                response = messageStream.MsgIO(request);
            }
            catch (MessagingException)
            {
                return 0x00;
            }           

            //1b,10,00,db,00,12,01,00,07,02,00,01,00,01,00,00,00,00,00,0d,00,69,02,00
            //PNS_NAME_QUERY_RESP:
            //   0  (8) Media.......................: 0x1B               => PN_MEDIA_USB
            //   1  (6) Receiver Device.............: 0x10               => PN_DEV_PC
            //   2  (6) Sender Device...............: 0x00               => PN_DEV_HOST
            //   3  (8) Resource....................: 0xDB               => PN_NAMESERVICE
            //   4 (16) Length......................: 0x0012             => 18
            //   6 (10) Receiver Object.............: 0x001              => 1
            //   7 (10) Sender Object...............: 0x000              => PN_OBJ_ROUTING_REQ
            //   8  (8) Unique Transaction ID.......: 0x07               => 7
            //   9  (8) Sub Function................: 0x02               => PNS_NAME_QUERY_RESP
            //  10 (16) Total number of names left..: 0x0001             => 1 <---
            //  12 (16) Number of names.............: 0x0001             => 1
            //  14  (8) Reserved 1..................: 0x00               => 0x00
            //  15  (8) Reserved 2..................: 0x00               => 0x00
            //  Names [1]
            //  16 (32) Name........................: 0x0000000D         => 0x0000000D
            //  20  (8) DeviceId....................: 0x00               => PN_DEV_HOST
            //  21  (8) ObjectId....................: 0x69               => 0x69 <---
            //  22  (8) Record flags................: 0x02               => ------1-  PN_NAME_NOCHG
            //  23  (8) Reserved....................: 0x00               => 0x00  

            byte[] content = response.Contents;
            // content[11] == Total number of names left
            if (content[11] > 0 && content.Length > 21)
            {
                return content[21];
            }

            return 0x00;
        }

        /// <summary>
        /// Queries the SimModel of the given sim slot from the phone
        /// </summary>
        /// <param name="messageStream">Communication channel to the phone</param>
        /// <param name="simSlot">1=primary sim, 2=secondary sim</param>
        /// <returns>SimModel instance (with empty values on error).</returns>
        private SimModel GetSimIMSI(MessageStream messageStream, int simSlot=1)
        {
            byte serverId = GetSimServerObjectId(messageStream);

            //#define PN_DEV_MODEM   0x60 /* [D] 96  Modem device number 1 */
            //#define PN_DEV_MODEM_2 0x68 /* [D] 104 Modem device number 2 */

            byte deviceID = 0x60;
            if (simSlot > 1)
                deviceID = 0x68;

            //00,00,10,09,00,16,69,01,1c,45,00,02,fd,02,00,08,60,00,00,00,00,72,00,08,00,00,00,00
            //ASIM_READ_REQ:
            //   0  (8) Media.......................: 0x00               => PN_MEDIA_ROUTING_REQ
            //   1  (6) Receiver Device.............: 0x00               => PN_DEV_HOST
            //   2  (6) Sender Device...............: 0x10               => PN_DEV_PC
            //   3  (8) Resource....................: 0x09               => PN_SIM
            //   4 (16) Length......................: 0x0016             => 22
            //   6 (10) Receiver Object.............: 0x069              => PN_OBJ_LOCOS_SERV <---
            //   7 (10) Sender Object...............: 0x001              => 1
            //   8  (8) Transaction ID..............: 0x1C               => 28
            //   9  (8) Message ID..................: 0x45               => ASIM_READ_REQ
            //  10  (8) Filler......................: 0x00               => 8 bit padding
            //  11  (8) Number of Subblocks.........: 0x02               => 2
            //Sub block 1: MULTI_SIM_SHARED_SB_DEVICE_ID
            //  12 (16) Sub Block ID................: 0xFD02             => MULTI_SIM_SHARED_SB_DEVICE_ID
            //  14 (16) Sub Block Length............: 0x0008             => 8
            //  16  (8) Device ID...................: 0x60               => 96 <---
            //  17 (24) Filler......................: 0x000000           => 24 bit padding
            //Sub block 2: ASIM_SB_IMSI_ID
            //  20 (16) Sub Block ID................: 0x0072             => ASIM_SB_IMSI_ID
            //  22 (16) Sub Block Length............: 0x0008             => 8
            //  24  (8) Status......................: 0x00               => 0x00
            //  25  (8) No of digits in MNC.........: 0x00               => 0
            //  26  (8) Filler......................: 0x00               => 8 bit padding
            //  27  (8) Length of SimModel..............: 0x00               => 0
            //  28  (0) Filler......................:                    => Alignment to 32 bit boundary

            Message request = new IsiMessage(
                new byte[] { 0x00, 0x00, 0x10, 0x09, 0x00, 0x16, serverId, 0x01, 0x1c, 0x45, 0x00, 0x02,
                    0xfd, 0x02, 0x00, 0x08, deviceID, 0x00, 0x00, 0x00,
                    0x00, 0x72, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00 }, true, false);
            Message response;
            try
            {
                response = messageStream.MsgIO(request);
            }
            catch (MessagingException)
            {
                return new SimModel();
            }

            //1b,10,00,09,00,1e,01,69,1c,46,01,02,fd,02,00,08,60,00,00,00,00,72,00,10,01,02,00,08,29,44,50,12,16,40,53,80
            //ASIM_READ_RESP:
            //   0  (8) Media.......................: 0x1B               => PN_MEDIA_USB
            //   1  (6) Receiver Device.............: 0x10               => PN_DEV_PC
            //   2  (6) Sender Device...............: 0x00               => PN_DEV_HOST
            //   3  (8) Resource....................: 0x09               => PN_SIM
            //   4 (16) Length......................: 0x001E             => 30
            //   6 (10) Receiver Object.............: 0x001              => 1
            //   7 (10) Sender Object...............: 0x069              => PN_OBJ_LOCOS_SERV
            //   8  (8) Transaction ID..............: 0x1C               => 28
            //   9  (8) Message ID..................: 0x46               => ASIM_READ_RESP
            //  10  (8) Status......................: 0x01               => ASIM_STA_OK <---
            //  11  (8) Number of Subblocks.........: 0x02               => 2 <---
            //Sub block 1: MULTI_SIM_SHARED_SB_DEVICE_ID
            //  12 (16) Sub Block ID................: 0xFD02             => MULTI_SIM_SHARED_SB_DEVICE_ID
            //  14 (16) Sub Block Length............: 0x0008             => 8
            //  16  (8) Device ID...................: 0x60               => 96
            //  17 (24) Filler......................: 0x000000           => 24 bit padding
            //Sub block 2: ASIM_SB_IMSI_ID
            //  20 (16) Sub Block ID................: 0x0072             => ASIM_SB_IMSI_ID <---
            //  22 (16) Sub Block Length............: 0x0010             => 16
            //  24  (8) Status......................: 0x01               => ASIM_STA_OK
            //  25  (8) No of digits in MNC.........: 0x02               => 2 <---
            //  26  (8) Filler......................: 0x00               => 8 bit padding
            //  27  (8) Length of SimModel..............: 0x08               => 8
            //  28  (8) SimModel[1].....................: 0x29               => 0x29 <---
            //  29  (8) SimModel[2].....................: 0x44               => 0x44 <---
            //  30  (8) SimModel[3].....................: 0x50               => 0x50 <---
            //  31  (8) SimModel[4].....................: 0x12               => 0x12 <---
            //  32  (8) SimModel[5].....................: 0x16               => 0x16 <---
            //  33  (8) SimModel[6].....................: 0x40               => 0x40 <---
            //  34  (8) SimModel[7].....................: 0x53               => 0x53 <---
            //  35  (8) SimModel[8].....................: 0x80               => 0x80 <---
            //  36  (0) Filler......................:                    => Alignment to 32 bit boundary

            var content = new List<byte>(response.Contents);
            // content[10] == ASIM_STA_OK == 1 && content[11] == Number of Sub Blocks == 2
            // 0xFB => ASIM_STA_NOTREADY
            if (content[10] == 1 && content[11] == 2 && content.Count >= 36)
            {
                string imsi = BinaryCodedDecimalToString(content.GetRange(28, 8).ToArray());
                return new SimModel(imsi, content[25]);
            }

            return new SimModel();
        }

        /// <summary>
        /// Queries for the object id of the multi sim server (with a fixed PhoNet constant PN_MULTI_SIM = 13 = 0x0D).
        /// </summary>
        /// <param name="messageStream">Communication channel to the phone</param>
        /// <returns>Object id or 0x00 on error</returns>
        private byte GetMultiSimServerObjectId(MessageStream messageStream)
        {
            // isi: PNS_NAME_QUERY_REQ
            Message request = new IsiMessage(
                new byte[] { 0x00, 0x00, 0x10, 0xdb, 0x00, 0x0e, 0x00, 0x01, 0x08, 0x01,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xff, 0xff, 0xff, 0xff }, true, false);
            Message response;
            try
            {
                response = messageStream.MsgIO(request);
            }
            catch (MessagingException)
            {
                return 0x00;
            }

            // isi: PNS_NAME_QUERY_RESP
            byte[] content = response.Contents;
            // content[11] == Total number of names left
            if (content[11] > 0 && content.Length > 21)
            {
                return content[21];
            }

            return 0x00;
        }

        /// <summary>
        /// Queries for the sim ICC of the primary sim.
        /// </summary>
        /// <param name="messageStream">Communication channel to the phone</param>
        /// <returns>Sim id or empty string on error</returns>
        private string GetInsertedSimICC(MessageStream messageStream)
        {
            byte serverId = GetMultiSimServerObjectId(messageStream);

            // isi: MULTI_SIM_INFO_GET_REQ
            Message request = new IsiMessage(
                new byte[] { 0x00, 0x00, 0x10, 0x0d, 0x00, 0x06, serverId, 0x01, 0x02, 0x01, 0x00, 0x00 }, true, false); // all sims
                // inserted sims ** new byte[] { 0x00, 0x00, 0x10, 0x0d, 0x00, 0x06, serverId, 0x01, 0x02, 0x01, 0x0d, 0x00 }, true, false);
            Message response;
            try
            {
                response = messageStream.MsgIO(request);
            }
            catch (MessagingException)
            {
                return "";
            }

            // isi: MULTI_SIM_INFO_GET_RESP:
            var content = new List<byte>(response.Contents);
            // content[10] == MULTI_SIM_RESPONSE_OK && content[11] == Number of Sub Blocks
            if (content[10] == 0 && content[11] > 0 && content.Count > 29)
                return BinaryCodedDecimalToString(content.GetRange(20, 10).ToArray());

            return "";
        }

        /// <summary>
        /// Converts binary-coded decimal to string
        /// </summary>
        /// <param name="data">Byte array to convert</param>
        /// <returns>String reprentation of the given array</returns>
        private string BinaryCodedDecimalToString(IEnumerable<byte> data)
        {
            string output = "";
            foreach (byte Byte in data)
            {
                // first half
                output += (Byte & 0x0F).ToString(CultureInfo.InvariantCulture);
                // second half
                output += (Byte >> 4).ToString(CultureInfo.InvariantCulture);
            }

            return output;
        }

        /// <summary>
        /// Sends a synchronous message to given DTL connection.
        /// RPC0 is used as the message.
        /// </summary>
        /// <param name="dtlMessaging">Messaging stream to use</param>
        private void SendAsynchronousMessage(IDtlMessaging dtlMessaging)
        {
            Console.WriteLine("\r\nSending asynchronous message (RPC0)");
            var messageStream = new MessageStream(dtlMessaging, "Fuse .NET Example");
            messageStream.Received += MessageStreamReceivedCallback;

            Message request = new PhoNetMessage(
                new byte[] { 0x00, 0x00, 0x10, 0xd1, 0x00, 0x05, 0x00, 0x01, 0x00, 0x03, 0x00 }, true, false);
            Console.WriteLine("Sending RPC0 request");
            messageStream.Send(request);

            //waiting for the asynchronouse response 
            //Note: Done in real dummy way just for example of asynchronous message sending!!
            long timeout = 3000;
            while (!asynchronousResponseReceived)
            {
                Thread.Sleep(50);
                timeout -= 50;
                if (timeout <= 0)
                {
                    Console.WriteLine("Error: Asynchronouse message response was not received in set timeout.");
                    break;
                }
            }

            messageStream.Dispose();
        }

        /// <summary>
        /// Asynchronous response callback. Is used by the SendSynchronouseMessage method.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void MessageStreamReceivedCallback(object sender, StreamEventArgs e)
        {
            Console.WriteLine("Asynchronous response received:\r\n " +
                ConvertMessageDataToString(e.ReceiveData.Message.Contents));
            asynchronousResponseReceived = true;
        }

        #region Fuse event handlers

        /// <summary>
        /// Event handler for Fuse's connection added event.
        /// Registers added connection to product presence and identification.
        /// Scans product info from the added connection and updates connected products accordingly.
        /// </summary>
        /// <param name="pIDtlConnectionIdentifier">Added connection.</param>
        void connectionServices_OnConnectionAdded(DtlConnectionIdentifier pIDtlConnectionIdentifier)
        {
            Console.WriteLine("--> Connection added event received: " + pIDtlConnectionIdentifier.FriendlyName +
                " was added");

            //registering to detection events
            RegisterToProductPresence(pIDtlConnectionIdentifier);
            RegisterToProductIdentification(pIDtlConnectionIdentifier);

            // scan product from new connection and add it to connected products
            var productInfo = new ProductInfo(pIDtlConnectionIdentifier);
            mainDispatcher.BeginInvoke(DispatcherPriority.Normal,
                (ThreadStart)(() =>
                    {
                        // Scan must be done in UI thread
                        this.Connections.Add(productInfo);
                        this.ScanProductInfo(pIDtlConnectionIdentifier, productInfo);
                    })
                );
        }

        /// <summary>
        /// Event handler for Fuse's connection removed event.
        /// </summary>
        /// <param name="pIDtlConnectionIdentifier">Removed connection</param>
        void connectionServices_OnConnectionRemoved(DtlConnectionIdentifier pIDtlConnectionIdentifier)
        {
            Console.WriteLine("--> Connection removed event received: " + pIDtlConnectionIdentifier.FriendlyName +
                " was removed");
            this.Connections.RemoveByGuid(pIDtlConnectionIdentifier.Guid);
        }

        /// <summary>
        /// Event handler for Fuse's connection list order changed event.
        /// </summary>
        void connectionServices_OnConnectionOrderChanged()
        {
            Console.WriteLine("--> Connection order changed event received");
        }

        /// <summary>
        /// Event handler for Fuse's connection modified event.
        /// Updates friendly name of the modified connection to connected products collection.
        /// </summary>
        /// <param name="pIDtlConnectionIdentifier">Connection that has been modified.</param>
        void connectionServices_OnConnectionModified(DtlConnectionIdentifier pIDtlConnectionIdentifier)
        {
            int index = Connections.IndexOfGuid(pIDtlConnectionIdentifier.Guid);
            if (index > -1)
                Connections[index].Connection.Name = pIDtlConnectionIdentifier.FriendlyName;

            Console.WriteLine("--> Connection modified event received: " + pIDtlConnectionIdentifier.FriendlyName +
                " was modified");
        }

        /// <summary>
        /// Event handler for Fuse's product presence event.
        /// Add or removes product info element from the connected products collection accordingly.
        /// </summary>
        /// <param name="pIDtlConnectionIdentifier">Connection which product presence has been changed.</param>
        /// <param name="eDtlProductPresenceState">State of the product presence.</param>
        void fuseProductPresence_OnProductPresenceChanged(DtlConnectionIdentifier pIDtlConnectionIdentifier, EnumDtlProductPresenceState eDtlProductPresenceState)
        {

            string presentState = "not present";
            if (eDtlProductPresenceState == EnumDtlProductPresenceState.eDtlProductStatePresent)
                presentState = "present";
            else if (eDtlProductPresenceState == EnumDtlProductPresenceState.eDtlProductStateUnknown)
                presentState = "unknown";

            Console.WriteLine("--> Product presence event received: " + pIDtlConnectionIdentifier.FriendlyName + " is " + presentState);

            // Find or create product info for the connection that was changed
            //var productInfo = this.Connections.GetOrCeateProductInfo(pIDtlConnectionIdentifier);

            // Only get existing connection
            var productInfo = this.Connections.FirstOrDefault(con => con.Connection.GUID == pIDtlConnectionIdentifier.Guid);

            if (productInfo == null) return;

            // Set product presence
            productInfo.ProductPresent =
                eDtlProductPresenceState == EnumDtlProductPresenceState.eDtlProductStatePresent ?
                EnumProductPresence.Present :
                EnumProductPresence.NotPresent;
        }

        /// <summary>
        /// Event handler for Fuse's product identified event.
        /// Updates information to the connected products collection.
        /// Presence of the main or reference phone is also updated.
        /// </summary>
        /// <param name="pIDtlConnectionIdentifier">Connection which product has been identified</param>
        /// <param name="pIProductIdentificationFields">Identification information</param>
        void fuseProductIdentification_OnProductIdentified(DtlConnectionIdentifier pIDtlConnectionIdentifier, ProductIdentity pIProductIdentificationFields)
        {
            Console.WriteLine("--> Product identified: " + pIDtlConnectionIdentifier.FriendlyName);

            var productInfo = this.Connections.GetOrCeateProductInfo(pIDtlConnectionIdentifier);

            mainDispatcher.BeginInvoke(DispatcherPriority.Normal,
                (ThreadStart)(() => this.ScanProductInfo(pIDtlConnectionIdentifier, productInfo))
                );
        }
        
        #endregion

        #region Fuse event registration

        /// <summary>
        /// Registeres to all Fuse's connections product presence. After the registration
        /// Fuse's product presence events from all connections are delivered to the product
        /// presence event handler.
        /// </summary>
        public void RegisterToProductPresences()
        {
            //Note: index is 1-based!
            ConnectionIdentifiers connections = connectionServices.ConnectionIdentifiers;
            for (int i = 1; i <= connections.Count; i++)
            {
                RegisterToProductPresence(connections[i]);
            }
        }

        /// <summary>
        /// Registeres to specific connection's product presence.
        /// </summary>
        /// <param name="connectionIdentifier">Connection which product presence is registered</param>
        private void RegisterToProductPresence(DtlConnectionIdentifier connectionIdentifier)
        {
            // Try three times. Print error and try again. After last try display message box.
            for (int ii = 0; ii < 3; ii++)
            {
                try
                {
                    fuseProductPresence.RegisterToProductPresenceEvents(connectionIdentifier);
                    Console.WriteLine("Registered to Fuse product presence: " + connectionIdentifier.FriendlyName);
                    break;
                }
                catch (System.Runtime.InteropServices.COMException)
                {
                    Console.WriteLine("Failed to register to product presence. Tried {0} times", ii + 1);
                    if (ii >= 2)
                    {
                        MessageBox.Show("Failed to register to Fuse product presence events. Please restart the application.", "Fuse error");
                        Environment.Exit(0);
                    }
                }
            }
        }

        /// <summary>
        /// Unregisteres product presence from all Fuse connections.
        /// </summary>
        public void UnRegisterFromProductPresences()
        {
            //Note: index is 1-based!
            ConnectionIdentifiers connections = connectionServices.ConnectionIdentifiers;
            for (int i = 1; i <= connections.Count; i++)
                this.UnRegisterFromProductPresence(connections[i]);
        }

        /// <summary>
        /// Unregisteres product presence for a specific connection.
        /// </summary>
        /// <param name="connectionIdentifier">Connection which product presence is unregistered</param>
        private void UnRegisterFromProductPresence(DtlConnectionIdentifier connectionIdentifier)
        {
            try
            {
                fuseProductPresence.UnregisterProductPresenceEvents(connectionIdentifier);
                Console.WriteLine("Unregistered from Fuse product presence: " + connectionIdentifier.FriendlyName);
            }
            catch (System.Runtime.InteropServices.COMException)
            {
                Console.WriteLine("{0}:Failed to unregister from product presence.", connectionIdentifier.FriendlyName);
            }
        }

        /// <summary>
        /// Registeres to all Fuse's connections product identification. After the registration
        /// Fuse's product identification events from all connections are delivered to the product
        /// identification event handler.
        /// </summary>
        public void RegisterToProductIdentifications()
        {
            //Note: index is 1-based!
            ConnectionIdentifiers connections = connectionServices.ConnectionIdentifiers;
            for (int i = 1; i <= connections.Count; i++)
                this.RegisterToProductIdentification(connections[i]);
        }

        /// <summary>
        /// Registeres to specific connection's product identification.
        /// </summary>
        /// <param name="connectionIdentifier">Connection which product identification is registered</param>
        private void RegisterToProductIdentification(DtlConnectionIdentifier connectionIdentifier)
        {
            // Try three times. Print error and try again. After last try display message box.
            for (int ii = 0; ii < 3; ii++)
            {
                try
                {
                    fuseProductIdentification.RegisterToProductIdentificationEvents(connectionIdentifier,
                        (uint)EnumProductIdentification.eProductIdentificationAll);
                    Console.WriteLine("Registered to Fuse product identification: " + connectionIdentifier.FriendlyName);
                    break;
                }
                catch (System.Runtime.InteropServices.COMException)
                {
                    Console.WriteLine("Failed to register to product identification. Tried {0} times", ii + 1);
                    if (ii >= 2)
                    {
                        MessageBox.Show(
                            "Failed to register to Fuse product identification events. Please restart the application.",
                            "Fuse error", MessageBoxButton.OK, MessageBoxImage.Error);
                        Environment.Exit(0);
                    }
                }
            }
        }

        /// <summary>
        /// Unregisteres from all Fuse connections product identification.
        /// </summary>
        public void UnRegisterFromProductIdentifications()
        {
            //Note: index is 1-based!
            ConnectionIdentifiers connections = connectionServices.ConnectionIdentifiers;
            for (int i = 1; i <= connections.Count; i++)
                this.UnRegisterFromProductIdentification(connections[i]);
        }

        /// <summary>
        /// Unregisteres from a specific connection's product identification.
        /// </summary>
        /// <param name="connectionIdentifier">Connection which product identification is unregistered</param>
        private void UnRegisterFromProductIdentification(DtlConnectionIdentifier connectionIdentifier)
        {
            try
            {
                fuseProductIdentification.UnregisterProductIdentificationEvents(connectionIdentifier);
                Console.WriteLine("Unregistered from Fuse product identification: " + connectionIdentifier.FriendlyName);
            }
            catch (System.Runtime.InteropServices.COMException)
            {
                Console.WriteLine("{0}: Failed to unregister from product identification.", connectionIdentifier.FriendlyName);
            }
        }
        #endregion

        #region Helpers
        /// <summary>
        /// Shows the Fuse's list of configured connection. Connection states: product presence and
        /// product identification are also displayd.
        /// </summary>
        public void ShowStateOfConnections()
        {
            Console.WriteLine("\r\nStates of the configured connections:");
            ConnectionIdentifiers connections = connectionServices.ConnectionIdentifiers;
            for (int i = 1; i <= connections.Count; i++)
            {
                ShowConnectionState(connections[i]);
            }
            
            if (connections.Count == 0)
            {
                Console.WriteLine("No configured connections");
            }
            Console.WriteLine();
        }

        /// <summary>
        /// Shows the state (presence, identification) of a connection.
        /// </summary>
        /// <param name="connectionId">Connection which state is displayd</param>
        private void ShowConnectionState(DtlConnectionIdentifier connectionId)
        {
            EnumDtlProductPresenceState presence = fuseProductPresence.ReadProductPresence(connectionId);
            switch (presence)
            {
                case EnumDtlProductPresenceState.eDtlProductStateNotPresent:
                    Console.WriteLine(connectionId.FriendlyName + ": product not present");
                    break;
                case EnumDtlProductPresenceState.eDtlProductStatePresent:
                    //product is present, try to identify it
                    try
                    {
                        ProductIdentity productIdentity = fuseProductIdentification.ReadProductIdentity(
                            connectionId, (uint)EnumProductIdentification.eProductIdentificationAll);
                        Console.WriteLine(connectionId.FriendlyName + ": product is present, type: " +
                            productIdentity.GetIdentityValue(EnumProductIdentification.eProductIdentificationProductType) +
                            " code: " + productIdentity.GetIdentityValue(EnumProductIdentification.eProductIdentificationProductCode));
                    }
                    catch (Exception)
                    {
                        Console.WriteLine(connectionId.FriendlyName + ": product is present, identification failed");
                    }
                    break;
                case EnumDtlProductPresenceState.eDtlProductStateUnknown:
                    Console.WriteLine(connectionId.FriendlyName + ": product presence unknown");
                    break;
            }
        }

        /// <summary>
        /// Helper function to convert message data to string.
        /// Note: This function should be only be used in demostration purposes.
        /// </summary>
        /// <param name="data">Response message in bytes</param>
        /// <param name="startIndex">Start of the string content to convert</param>
        /// <param name="length">Length of slice to convert</param>
        /// <returns></returns>
        private string ConvertMessageDataToString(byte[] data, int startIndex=10, int length = int.MaxValue)
        {
            string result = "";
            for (int ii = startIndex; ii < data.Length && ii - startIndex < length; ii++)
            {
                if (data[ii] == 0)
                    break;
                result = result + (char)data[ii];
            }
            return result;
        }

        #endregion
    }

}
