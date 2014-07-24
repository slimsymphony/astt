using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestAutomation.Client
{
    /// <summary>
    /// Class for holding the information about options for the test server client
    /// </summary>
    public class TestAutomationServerOptions
    {
        /// <summary>
        /// Returns the default options for the test server
        /// </summary>
        public static TestAutomationServerOptions Default
        {
            get
            {
                return new TestAutomationServerOptions()
                {
                    LocalArchiveLocation =      Constants.TEST_SERVER_ARCHIVE_NAME,
                    PackageName =               Constants.TEST_SERVER_PACKAGE_NAME,
                    ClassName =                 Constants.TEST_SERVER_CLASS_NAME,
                    EntryMethodName =           Constants.TEST_SERVER_ENTRY_METHOD_NAME,
                    ForcePushArchive =          false,
                    ShutDownOnUsbDisconnect =   true
                };
            }
        }

        /// <summary>
        /// Loacation of the server archive in the local machine
        /// </summary>
        public string LocalArchiveLocation { get; set; }

        /// <summary>
        /// Name of the test server package
        /// </summary>
        public string PackageName { get; set; }
        
        /// <summary>
        /// Name of the test server class
        /// </summary>
        public string ClassName { get; set; }
        
        /// <summary>
        /// Name of the entry method in the test server class
        /// </summary>
        public string EntryMethodName { get; set; }

        /// <summary>
        /// Value indicating whether to forcey install the server archive in the remote device; i.e re-installing it without
        /// checking the if the local and remote archive files are already in synch
        /// </summary
        public bool ForcePushArchive { get; set; }

        /// <summary>
        /// Value indicating whether to keep the test server alive in the device even 
        /// if its parent process is terminated (for example, if the device is disconnected).
        /// </summary>
        public bool ShutDownOnUsbDisconnect { get; set; }
    }
}
