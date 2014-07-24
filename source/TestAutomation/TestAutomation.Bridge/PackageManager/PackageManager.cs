using Managed.Adb;
using Managed.Adb.Exceptions;
using Managed.Adb.IO;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using TestAutomation.Bridge.ScriptingTools;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Package manager class for handling the packages in and for the device
    /// </summary>
    [Serializable]
    public sealed class PackageManager//create the python style by using DynamicProxy
    {
        private const string PM_LIST_FULL = "pm list packages -f";

        private TABConnection m_tab;

        /// <summary>
        /// Internal class constructor
        /// </summary>
        /// <param name="tab">Device bridge</param>
        internal PackageManager(TABConnection tab)
        {
            m_tab = tab;
        }

        /// <summary>
        /// Installs an Android application on device.
        /// </summary>
        /// <param name="packageFilePath">The absolute file system path to file on local host to install</param>
        /// <returns>A tuple in which the first item is the final location of the apk file; and the second item is the package name</returns>
        public Tuple<string, string> InstallPackage(string packageFilePath)
        {
            return InstallPackage(packageFilePath, true);
        }

        /// <summary>
        /// Installs an Android application on device.
        /// </summary>
        /// <param name="packageFilePath">The absolute file system path to file on local host to install</param>
        /// <param name="reinstall">Set to <code>true</code>if re-install of app should be performed</param>
        /// <returns>A tuple in which the first item is the final location of the apk file; and the second item is the package name</returns>
        public Tuple<string, string> InstallPackage(string packageFilePath, bool reinstall)
        {
            if (string.IsNullOrEmpty(packageFilePath))
            {
                throw new ArgumentNullException("packageFilePath");
            }

            var info = new FileInfo(packageFilePath);

            if (!info.Exists)
            {
                throw new FileNotFoundException(packageFilePath);
            }

            if (info.Length == 0)
            {
                throw new IOException(string.Format("Size of '{0}' is zero", packageFilePath));
            }

            var apk = new ApkInfo(packageFilePath);

            var package = apk.Package;

            try
            {
                DoInstallPackage(packageFilePath, reinstall);
            }
            catch (PackageInstallationException)
            { }

            if (package != null)
            {
                string apkLocation = FindApkPath(package);
                if (apkLocation != null)
                {
                    return new Tuple<string, string>(apkLocation, package);
                }
            }
            
            return null;
        }

        /// <summary>
        /// Uninstall an package from the device.
        /// </summary>
        /// <param name="packageName">Name of the package.</param>
        /// <returns><code>true</code> if successfully uninstalled, <code>false</code> otherwise</returns>
        public bool UninstallPackage(string packageName)
        {
            if (string.IsNullOrEmpty(packageName))
            {
                throw new ArgumentNullException("packageName");
            }
            
            DoUninstallPackage(packageName);
            
            return !PackageExists(packageName);
        }

        /// <summary>
        /// Gets the package listing, where a key is the absolute path of the package; and the value is the package name
        /// </summary>
        /// <returns>Package listing, where a key is the absolute path of the package; and the value is the package name</returns>
        public Dictionary<string, string> ListPackages()
        {
            var receiver = new ApkLocationReceiver();
            m_tab.ExecuteShellCommand(PM_LIST_FULL, receiver, TABInterface.DEFAULT_ADB_TIMEOUT);
            return receiver.Packages;
        }

        /// <summary>
        /// Finds the apk path.
        /// </summary>
        /// <param name="packageName">The package.</param>
        /// <returns>Path of the package's apk file; <code>null</code> if not found</returns>
        public string FindApkPath(string packageName)
        {
            if (string.IsNullOrEmpty(packageName))
            {
                throw new ArgumentNullException("packageName");
            }
            try
            {
                return m_tab.PackageManager.GetApkPath(packageName);
            }
            catch (FileNotFoundException)
            {
                return null;
            }
        }

        /// <summary>
        /// Checks if a package with given name exists
        /// </summary>
        /// <param name="packageName">The name of the package</param>
        /// <returns><code>true</code> if exists; <code>false</code> otherwise</returns>
        public bool PackageExists(string packageName)
        {
            if (string.IsNullOrEmpty(packageName))
            {
                throw new ArgumentNullException("packageName");
            }

            var p = ListPackages().Values.ToList().Find(a => string.Compare(a, packageName, false) == 0);
            return p != null;
        }

        /// <summary>
        /// Enables a packages in the device
        /// </summary>
        /// <param name="packageName">Name of the package (package or package/class)</param>
        /// <returns>True if successfully enabled; false otherwise</returns>
        public bool EnablePackage(string packageName)
        {
            return EnablePackage(packageName, true);
        }

        /// <summary>
        /// Disables a packages in the device
        /// </summary>
        /// <param name="packageName">Name of the package (package or package/class)</param>
        /// <returns>True if successfully disabled; false otherwise</returns>
        public bool DisablePackage(string packageName)
        {
            return EnablePackage(packageName, false);
        }

        /// <summary>
        /// Enables/disables a packages in the device
        /// </summary>
        /// <param name="packageName">Name of the package (package or package/class)</param>
        /// <param name="value">True to enable; false to disable</param>
        /// <returns>True if successfully enabled/disabled; false otherwise</returns>
        private bool EnablePackage(string packageName, bool value)
        {
            if (string.IsNullOrEmpty(packageName))
            {
                throw new ArgumentNullException("packageName");
            }

            var command = string.Format("pm {0} {1}", (value ? "enable": "disable"), packageName);
            var receiver = new PackageEnablerReceiver();
            m_tab.ExecuteShellCommand(command, receiver, TABInterface.DEFAULT_ADB_TIMEOUT);

            if (value && receiver.PackageState == PackageEnablerReceiver.State.Enabled)
            {
                return true;
            }
            else if (!value && receiver.PackageState == PackageEnablerReceiver.State.Disabled)
            {
                return true;
            }
            else if (receiver.PackageState != PackageEnablerReceiver.State.Unknown)
            {
                return false;
            }
            else
            {
                throw new Exception(string.Format("Received no response when {0} package: {1}",
                    (value ? "enabling" : "disabling"), packageName));
            }
        }

        /// <summary>
        /// Installs an Android application on device.
        /// This is a helper method that combines the syncPackageToDevice, installRemotePackage,
        /// and removePackage steps
        /// </summary>
        /// <param name="packageFilePath">the absolute file system path to file on local host to install</param>
        /// <param name="reinstall">set to <code>true</code>if re-install of app should be performed</param>
        private void DoInstallPackage(string packageFilePath, bool reinstall)
        {
            var remoteFilePath = SyncPackageToDevice(packageFilePath);
            InstallRemotePackage(remoteFilePath, reinstall);
            RemoveRemotePackage(remoteFilePath);
        }

        /// <summary>
        /// Internal package installer: for internal packages
        /// </summary>
        /// <param name="packageStream">Package stream</param>
        /// <param name="packageName">Package name</param>
        /// <param name="packageHash">Package hash</param>
        /// <param name="reinstall">True to reinstall the package</param>
        /// <param name="keepArchive">True to keep to original archive after install</param>
        internal void DoInstallPackage(Stream packageStream, string packageName, string packageHash, bool reinstall, bool keepArchive)
        {
            var remoteFilePath = SyncPackageToDevice(packageStream, packageName, packageHash);
            InstallRemotePackage(remoteFilePath, reinstall);
            if (!keepArchive) RemoveRemotePackage(remoteFilePath);
        }

        /// <summary>
        /// Pushes a file to device
        /// </summary>
        /// <param name="localFilePath">the absolute path to file on local host</param>
        /// <returns>destination path on device for file</returns>
        private string SyncPackageToDevice(string localFilePath)
        {
            var packageFileName = Path.GetFileName(localFilePath);
            var remoteFilePath = string.Format("/data/local/tmp/{0}", packageFileName);
            m_tab.File.Push(localFilePath, remoteFilePath);
            return remoteFilePath;
        }

        /// <summary>
        /// Syncs a package from stream
        /// </summary>
        /// <param name="packageStream">the package stream</param>
        /// <param name="packageName">Name of the package</param>
        /// <param name="packageHash">Package hash</param>
        /// <returns>Package's location in the device</returns>
        private string SyncPackageToDevice(Stream packageStream, string packageName, string packageHash)
        {
            var remoteFilePath = string.Format("/data/local/tmp/{0}", packageName);
            
            var push = false;

            if (m_tab.File.FileExists(remoteFilePath))
            {
                if (MD5.CalculateRemote(m_tab, remoteFilePath) != packageHash)
                {
                    push = true;
                }
            }
            else
            {
                push = true;
            }

            if (push)
            {
                m_tab.SyncService.PushStream(packageStream, remoteFilePath);
            }
            
            return remoteFilePath;
        }

        /// <summary>
        /// Installs the application package that was pushed to a temporary location on the device.
        /// </summary>
        /// <param name="remoteFilePath">absolute file path to package file on device</param>
        /// <param name="reinstall">set to <code>true</code> if re-install of app should be performed</param>
        private void InstallRemotePackage(string remoteFilePath, bool reinstall)
        {
            var receiver = new InstallReceiver();
            var cmd = string.Format("pm install {1}{0}", remoteFilePath, reinstall ? "-r " : string.Empty);
            m_tab.ExecuteShellCommand(cmd, receiver, TABInterface.LONG_TIMEOUT); //30000

            if (!string.IsNullOrEmpty(receiver.ErrorMessage))
            {
                throw new PackageInstallationException(receiver.ErrorMessage);
            }
        }

        /// <summary>
        /// Remove a file from device
        /// </summary>
        /// <param name="remoteFilePath">path on device of file to remove</param>
        /// <exception cref="IOException">if file removal failed</exception>
        private void RemoveRemotePackage(string remoteFilePath)
        {
            // now we delete the app we sync'ed
            try
            {
                m_tab.ExecuteShellCommand("rm " + remoteFilePath, NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
            }
            catch (IOException e)
            {
                //Log.e(LOG_TAG, string.Format("Failed to delete temporary package: {0}", e.Message));
                throw e;
            }
        }

        /// <summary>
        /// Uninstall an package from the device.
        /// </summary>
        /// <param name="packageName">Name of the package.</param>
        private void DoUninstallPackage(string packageName)
        {
            var receiver = new InstallReceiver();
            m_tab.ExecuteShellCommand(string.Format("pm uninstall {0}", packageName), receiver, TABInterface.LONG_TIMEOUT); //30000

            if (!string.IsNullOrEmpty(receiver.ErrorMessage))
            {
                throw new PackageInstallationException(receiver.ErrorMessage);
            }
        }

        /// <summary>
        /// Class for observing the pm enable/disable output
        /// </summary>
        private class PackageEnablerReceiver : MultiLineReceiver
        {
            private static Regex m_state_pattern = new Regex("(.*new state:\\s*)(enabled|disabled)\\s*", RegexOptions.Compiled);

            /// <summary>
            /// State of the package
            /// </summary>
            public enum State
            {
                /// <summary>
                /// Unknown state
                /// </summary>
                Unknown,

                /// <summary>
                /// Enabled
                /// </summary>
                Enabled,
                
                /// <summary>
                /// Disabled
                /// </summary>
                Disabled
            }

            /// <summary>
            /// Class constructor
            /// </summary>
            public PackageEnablerReceiver()
            {
                PackageState = State.Unknown;
            }

            /// <summary>
            /// Gets the state of the package
            /// </summary>
            public State PackageState { get; private set; }

            /// <summary>
            /// Called to process a chunk of shell output lines
            /// </summary>
            /// <param name="lines">Lines to analyze</param>
            protected override void ProcessNewLines(string[] lines)
            {
                if (PackageState == State.Unknown)
                {
                    lines.ToList().ForEach(l =>
                        {
                            var m = m_state_pattern.Match(l);
                            if (m.Success)
                            {
                                State state;
                                if (Enum.TryParse<State>(m.Groups[2].Value, true, out state))
                                {
                                    PackageState = state;
                                }
                            }
                        });
                }
            }
        }

        /// <summary>
        /// Receiver class for package listing
        /// </summary>
        private class ApkLocationReceiver : MultiLineReceiver
        {
            private static Regex pm_package_pattern = new Regex("^package:(.+?)=(.+)$", RegexOptions.Compiled);

            /// <summary>
            /// Class constructor
            /// </summary>
            public ApkLocationReceiver()
            {
                Packages = new Dictionary<string, string>();
            }
            
            /// <summary>
            /// Gets a dictionary of packages, where key is apk location and value is the package name
            /// </summary>
            public Dictionary<string, string> Packages { get; private set; }
            
            /// <summary>
            /// Called for output processing
            /// </summary>
            /// <param name="lines">Packages in raw, un-parsed format</param>
            protected override void ProcessNewLines(string[] lines)
            {
                Packages.Clear();

                lines.ToList().ForEach(line =>
                {
                    if (line.Trim().Length > 0)
                    {
                        var m = pm_package_pattern.Match(line);
                        if (m.Success)
                        {
                            if (Packages.ContainsKey(m.Groups[1].Value))
                            {
                                Packages[m.Groups[1].Value] = m.Groups[2].Value;
                            }
                            else
                            {
                                Packages.Add(m.Groups[1].Value, m.Groups[2].Value);
                            }
                        }
                    }
                });
            }
        }
    }
}
