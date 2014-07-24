using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestAutomation.Client
{
    /// <summary>
    /// Class for holding the information about options for the scripting service client
    /// </summary>
    public class ScriptingServiceOptions
    {
        /// <summary>
        /// Returns the default options for the scripting service
        /// </summary>
        public static ScriptingServiceOptions Default
        {
            get
            {
                return new ScriptingServiceOptions()
                {
                    LocalPackageLocation =  Constants.SCRIPTING_SERVICE_APK_NAME,
                    PackageName =           Constants.SCRIPTING_SERVICE_PACKAGE_NAME,
                    ActionName =            Constants.SCRIPTING_SERVICE_ACTION_NAME,
                    ComponentName =         Constants.SCRIPTING_SERVICE_COMPONENT_NAME,
                    PortExtraKey =          Constants.SCRIPTING_SERVICE_PORT_EXTRA_KEY,
                    ForcePushPackage =      false
                };
            }
        }

        /// <summary>
        /// The preferred port the service should start listening
        /// </summary>
        public int ListeningPort { get; set; }

        /// <summary>
        /// Name of the service package
        /// </summary>
        public string PackageName { get; set; }

        /// <summary>
        /// Name of the service action
        /// </summary>
        public string ActionName { get; set; }

        /// <summary>
        /// Name of the service component
        /// </summary>
        public string ComponentName { get; set; }

        /// <summary>
        /// Loacation of the service package in the local machine
        /// </summary>
        public string LocalPackageLocation { get; set; }

        /// <summary>
        /// Key for defining the port for the service as a parameter
        /// </summary>
        public string PortExtraKey { get; set; }

        /// <summary>
        /// Value indicating whether to forcey install the service package in the remote device; i.e re-installing it without
        /// checking the if the local and remote package files are already in synch
        /// </summary>
        public bool ForcePushPackage { get; set; }

        /// <summary>
        /// Formats the compete command for the Activity starter
        /// </summary>
        /// <returns>The compete command for the activity starter</returns>
        public string CreateCommand()
        {
            return string.Format("-a {0} -n {1} --ei {2} {3}", ActionName, ComponentName, PortExtraKey, ListeningPort);

        }

        /// <summary>
        /// Formats the compete command for the Activity starter to kill all SL4A serices
        /// </summary>
        /// <returns>The compete command for the activity starter</returns>
        public string CreateKillCommand()
        {
            return string.Format("-a {0} -n {1}", ActionName, ComponentName);

        }
        
        /// <summary>
        /// Formats the compete command for the Activity starter
        /// </summary>
        /// <returns>The compete command for the activity starter</returns>
        public override string ToString()
        {
            return CreateCommand();
        }
    }
}
