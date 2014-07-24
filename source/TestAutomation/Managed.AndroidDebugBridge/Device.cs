using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Text.RegularExpressions;
using System.IO;
using System.Reflection;
using System.ComponentModel;
using Managed.Adb.Exceptions;
using Managed.Adb.IO;
using Managed.Adb.Logs;

namespace Managed.Adb
{

    /// <summary>
    /// Possible device states
    /// </summary>
    public enum DeviceState
    {
        Recovery,
        BootLoader,
        Offline,
        Online,
        Download,
        Unknown
    }

    /// <summary>
    /// 
    /// </summary>
    public class Device : IDevice
    {
        /// <summary>
        /// 
        /// </summary>
        private const string MNT_EXTERNAL_STORAGE = "EXTERNAL_STORAGE";
        
        /// <summary>
        /// 
        /// </summary>
        private const string MNT_DATA = "ANDROID_DATA";
        
        /// <summary>
        /// 
        /// </summary>
        private const string MNT_ROOT = "ANDROID_ROOT";

        /// <summary>
        /// Occurs when [state changed].
        /// </summary>
        public event EventHandler<EventArgs> StateChanged;
        
        /// <summary>
        /// Occurs when [build info changed].
        /// </summary>
        public event EventHandler<EventArgs> BuildInfoChanged;
       
        /// <summary>
        /// Occurs when [client list changed].
        /// </summary>
        public event EventHandler<EventArgs> ClientListChanged;

        /// <summary>
        /// 
        /// </summary>
        public const string TEMP_DIRECTORY_FOR_INSTALL = "/sdcard/tmp/";

        /// <summary>
        /// 
        /// </summary>
        public const string PROP_BUILD_VERSION = "ro.build.version.release";

        /// <summary>
        /// 
        /// </summary>
        public const string PROP_BUILD_API_LEVEL = "ro.build.version.sdk";

        /// <summary>
        /// 
        /// </summary>
        public const string PROP_BUILD_CODENAME = "ro.build.version.codename";

        /// <summary>
        /// 
        /// </summary>
        public const string PROP_DEBUGGABLE = "ro.debuggable";

        /// <summary>
        /// Serial number of the first connected emulator. 
        /// </summary>
        public const string FIRST_EMULATOR_SN = "emulator-5554";

        /** @deprecated Use {@link #PROP_BUILD_API_LEVEL}. */
        [Obsolete("Use PROP_BUILD_API_LEVEL")]
        public const string PROP_BUILD_VERSION_NUMBER = PROP_BUILD_API_LEVEL;

        /// <summary>
        ///  Emulator Serial Number regexp.
        /// </summary>
        private const string RE_EMULATOR_SN = @"emulator-(\d+)";

        /// <summary>
        /// Device list info regex
        /// </summary>
        private const string RE_DEVICELIST_INFO = @"^([^\s]+)\s+(device|offline|unknown|bootloader|recovery|download)$";

        /// <summary>
        /// Tag
        /// </summary>
        private const string LOG_TAG = "Device";

        private const int BATTERY_TIMEOUT = 2 * 1000; //2 seconds
        private const int GETPROP_TIMEOUT = 2 * 1000; //2 seconds
        private const int INSTALL_TIMEOUT = 2 * 60 * 1000; // 2 minutes

        /// <summary>
        /// 
        /// </summary>
        private string avdName;
        private bool _canSU = false;
        private BatteryInfo lastBatteryInfo = null;
        private DateTime lastBatteryCheckTime = DateTime.MinValue;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="serial"></param>
        /// <param name="state"></param>
        public Device(string serial, DeviceState state)
        {
            SerialNumber = serial;
            State = state;
            MountPoints = new Dictionary<String, MountPoint>();
            Properties = new Dictionary<string, string>();
            EnvironmentVariables = new Dictionary<string, string>();
            Clients = new List<IClient>();
            FileSystem = new FileSystem(this);
            BusyBox = new BusyBox(this);
            RetrieveDeviceInfo();
        }

        /// <summary>
        /// Retrieves the device info.
        /// </summary>
        public void RetrieveDeviceInfo()
        {
            RefreshMountPoints();
            RefreshEnvironmentVariables();
            RefreshProperties();
        }

        /// <summary>
        /// Get the device state from the string value
        /// </summary>
        /// <param name="state">The device state string</param>
        /// <returns></returns>
        public static DeviceState GetStateFromString(string state)
        {
            if (string.Compare(state, "device", true) == 0)
            {
                state = "online";
            }

            DeviceState ds;
            if (Enum.TryParse<DeviceState>(state, true, out ds))
            {
                return ds;
            }

            return DeviceState.Unknown;
        }

        /// <summary>
        /// Create a device from Adb Device list data
        /// </summary>
        /// <param name="data">the line data for the device</param>
        /// <returns></returns>
        public static Device CreateFromAdbData(string data)
        {
            Regex re = new Regex(RE_DEVICELIST_INFO, RegexOptions.Compiled | RegexOptions.IgnoreCase);
            Match m = re.Match(data);
            if (m.Success)
            {
                return new Device(m.Groups[1].Value, GetStateFromString(m.Groups[2].Value));
            }
            else
            {
                throw new ArgumentException("Invalid device list data");
            }
        }

        /// <summary>
        /// Determines whether this instance can use the SU shell.
        /// </summary>
        /// <returns>
        ///   <c>true</c> if this instance can use the SU shell; otherwise, <c>false</c>.
        /// </returns>
        public bool CanSU
        {
            get
            {
                if (_canSU)
                {
                    return _canSU;
                }

                try
                {
                    // workitem: 16822
                    // this now checks if permission was denied and accounts for that. 
                    // The nulloutput receiver is fine here because it doesn't need to send the output anywhere,
                    // the execute command can still handle the output with the null output receiver.
                    ExecuteRootShellCommand("echo \\\"I can haz root\\\"", NullOutputReceiver.Instance);
                    _canSU = true;
                }
                catch (PermissionDeniedException)
                {
                    _canSU = false;
                }
                catch (FileNotFoundException)
                {
                    _canSU = false;
                }

                return _canSU;
            }
        }

        /// <summary>
        /// Gets or sets the client monitoring socket.
        /// </summary>
        /// <value>
        /// The client monitoring socket.
        /// </value>
        public Socket ClientMonitoringSocket { get; set; }

        /// <summary>
        /// Gets the device serial number
        /// </summary>
        public string SerialNumber { get; private set; }

        /// <summary>
        /// Gets or sets the Avd name.
        /// </summary>
        public string AvdName
        {
            get
            {
                return avdName;
            }
            set
            {
                if (!IsEmulator)
                {
                    throw new ArgumentException("Cannot set the AVD name of the device is not an emulator");
                }
                avdName = value;
            }
        }

        /// <summary>
        /// Gets the device state
        /// </summary>
        public DeviceState State { get; set; }

        /// <summary>
        /// Gets the device mount points.
        /// </summary>
        public Dictionary<String, MountPoint> MountPoints { get; private set; }

        /// <summary>
        /// Returns the device properties. It contains the whole output of 'getprop'
        /// </summary>
        /// <value>The properties.</value>
        public Dictionary<String, String> Properties { get; private set; }

        /// <summary>
        /// Gets the environment variables.
        /// </summary>
        /// <value>The environment variables.</value>
        public Dictionary<String, String> EnvironmentVariables { get; private set; }

        /// <summary>
        /// Gets the property value.
        /// </summary>
        /// <param name="name">The name of the property.</param>
        /// <returns>
        /// the value or <code>null</code> if the property does not exist.
        /// </returns>
        public string GetProperty(string name)
        {
            return GetProperty(new string[] { name });
        }

        /// <summary>
        /// Gets the first property that exists in the array of property names.
        /// </summary>
        /// <param name="name">The array of property names.</param>
        /// <returns></returns>
        public string GetProperty(params string[] name)
        {
            foreach (var item in name)
            {
                if (Properties.ContainsKey(item))
                {
                    return Properties[item];
                }
            }

            return null;
        }

        /// <summary>
        /// Sets a property
        /// </summary>
        /// <param name="key">Property key</param>
        /// <param name="value">Property value</param>
        public void SetProperty(string key, object value)
        {
            if (!string.IsNullOrEmpty(key) && value != null && Properties.ContainsKey(key))
            {
                ExecuteShellCommand(string.Format("setprop {0} {1}", key, value.ToString()),
                    NullOutputReceiver.Instance, DdmPreferences.Timeout);
                RefreshProperties();
            }
        }

        /// <summary>
        /// Gets the file system for this device.
        /// </summary>
        public FileSystem FileSystem { get; private set; }

        /// <summary>
        /// Gets the busy box object for this device.
        /// </summary>
        public BusyBox BusyBox { get; private set; }

        /// <summary>
        /// Gets a value indicating whether the device is online.
        /// </summary>
        /// <value><c>true</c> if the device is online; otherwise, <c>false</c>.</value>
        public bool IsOnline
        {
            get
            {
                return State == DeviceState.Online;
            }
        }

        /// <summary>
        /// Gets a value indicating whether this device is emulator.
        /// </summary>
        /// <value><c>true</c> if this device is emulator; otherwise, <c>false</c>.</value>
        public bool IsEmulator
        {
            get
            {
                return Regex.IsMatch(SerialNumber, RE_EMULATOR_SN, RegexOptions.Compiled);
            }
        }

        /// <summary>
        /// Gets a value indicating whether this device is offline.
        /// </summary>
        /// <value><c>true</c> if this device is offline; otherwise, <c>false</c>.</value>
        public bool IsOffline
        {
            get
            {
                return State == DeviceState.Offline;
            }
        }

        /// <summary>
        /// Gets a value indicating whether this device is in boot loader mode.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if this device is in boot loader mode; otherwise, <c>false</c>.
        /// </value>
        public bool IsBootLoader
        {
            get
            {
                return State == DeviceState.BootLoader;
            }
        }

        /// <summary>
        /// Gets a value indicating whether this instance is recovery.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if this instance is recovery; otherwise, <c>false</c>.
        /// </value>
        public bool IsRecovery
        {
            get
            {
                return State == DeviceState.Recovery;
            }
        }

        /// <summary>
        /// Remounts the mount point.
        /// </summary>
        /// <param name="mnt">The mount point.</param>
        /// <param name="readOnly">if set to <c>true</c> the mount poine will be set to read-only.</param>
        public void RemountMountPoint(MountPoint mnt, bool readOnly)
        {
            string command = string.Format("mount -o {0},remount -t {1} {2} {3}", readOnly ? "ro" : "rw", mnt.FileSystem, mnt.Block, mnt.Name);
            ExecuteShellCommand(command, NullOutputReceiver.Instance, DdmPreferences.Timeout);
            RefreshMountPoints();
        }

        /// <summary>
        /// Remounts the mount point.
        /// </summary>
        /// <param name="mountPoint">the mount point</param>
        /// <param name="readOnly">if set to <c>true</c> the mount poine will be set to read-only.</param>
        /// <exception cref="IOException">Throws if the mount point does not exist.</exception>
        public void RemountMountPoint(string mountPoint, bool readOnly)
        {
            if (MountPoints.ContainsKey(mountPoint))
            {
                MountPoint mnt = MountPoints[mountPoint];
                RemountMountPoint(mnt, readOnly);
            }
            else
            {
                throw new IOException("Invalid mount point");
            }
        }

        /// <summary>
        /// Refreshes the mount points.
        /// </summary>
        public void RefreshMountPoints()
        {
            if (!IsOffline)
            {
                try
                {
                    ExecuteShellCommand(MountPointReceiver.MOUNT_COMMAND, new MountPointReceiver(this), DdmPreferences.Timeout);
                }
                catch (AdbException)
                { }
            }
        }

        /// <summary>
        /// Refreshes the environment variables.
        /// </summary>
        public void RefreshEnvironmentVariables()
        {
            if (!IsOffline)
            {
                try
                {
                    ExecuteShellCommand(EnvironmentVariablesReceiver.ENV_COMMAND, new EnvironmentVariablesReceiver(this), DdmPreferences.Timeout);
                }
                catch (AdbException)
                { }
            }
        }

        /// <summary>
        /// Refreshes the properties.
        /// </summary>
        public void RefreshProperties()
        {
            if (!IsOffline)
            {
                try
                {
                    ExecuteShellCommand(GetPropReceiver.GETPROP_COMMAND, new GetPropReceiver(this), DdmPreferences.Timeout);
                }
                catch (AdbException)
                { }
            }
        }

        /// <summary>
        /// Reboots the device in to the specified state
        /// </summary>
        /// <param name="into">The reboot state</param>
        public void Reboot(string into)
        {
            AdbHelper.Instance.Reboot(into, AndroidDebugBridge.SocketAddress, this);
        }

        /// <summary>
        /// Reboots the device in to the specified state
        /// </summary>
        public void Reboot()
        {
            Reboot(string.Empty);
        }

        /// <summary>
        /// Gets the battery level.
        /// </summary>
        /// <returns></returns>
        public BatteryInfo GetBatteryInfo()
        {
            return GetBatteryInfo(5 * 60 * 1000);
        }

        /// <summary>
        /// Gets the battery level.
        /// </summary>
        /// <param name="freshness">The freshness.</param>
        /// <returns></returns>
        public BatteryInfo GetBatteryInfo(long freshness)
        {
            if (lastBatteryInfo != null
                && lastBatteryCheckTime > (DateTime.Now.AddMilliseconds(-freshness)))
            {
                return lastBatteryInfo;
            }
            var receiver = new BatteryReceiver();
            ExecuteShellCommand("dumpsys battery", receiver, BATTERY_TIMEOUT, DdmPreferences.Timeout);
            lastBatteryInfo = receiver.BatteryInfo;
            lastBatteryCheckTime = DateTime.Now;
            return lastBatteryInfo;
        }

        /// <summary>
        /// Gets a value indicating whether this instance has clients.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if this instance has clients; otherwise, <c>false</c>.
        /// </value>
        public bool HasClients
        {
            get
            {
                return Clients.Count > 0;
            }
        }

        /// <summary>
        /// Gets the list of clients
        /// </summary>
        public List<IClient> Clients { get; private set; }

        /// <summary>
        /// Returns a <see cref="SyncService"/> object to push / pull files to and from the device.
        /// </summary>
        /// <value></value>
        /// <remarks>
        /// 	<code>null</code> if the SyncService couldn't be created. This can happen if adb
        /// refuse to open the connection because the {@link IDevice} is invalid (or got disconnected).
        /// </remarks>
        /// <exception cref="IOException">Throws IOException if the connection with adb failed.</exception>
        public SyncService SyncService
        {
            get
            {
                SyncService syncService = new SyncService(AndroidDebugBridge.SocketAddress, this);
                if (syncService.Open())
                {
                    return syncService;
                }

                return null;
            }
        }

        /// <summary>
        /// Returns a <see cref="PackageManager"/> for this device.
        /// </summary>
        public PackageManager PackageManager
        {
            get
            {
                return new PackageManager(this);
            }
        }

        /// <summary>
        /// Returns a <see cref="FileListingService"/> for this device.
        /// </summary>
        /// <value></value>
        public FileListingService FileListingService
        {
            get
            {
                return new FileListingService(this);
            }
        }

        /// <summary>
        /// Gets an array of debuggable processes from the device
        /// </summary>
        /// <returns></returns>
        public int[] GetDebuggableProcesses()
        {
            return AdbHelper.Instance.GetDebuggableProcesses(AndroidDebugBridge.SocketAddress, this);
        }

        /// <summary>
        /// Takes a screen shot of the device and returns it as a <see cref="RawImage"/>
        /// </summary>
        /// <value>The screenshot.</value>
        public RawImage CaptureScreen()
        {
            return AdbHelper.Instance.GetFrameBuffer(AndroidDebugBridge.SocketAddress, this);
        }

        /// <summary>
        /// Takes a screen shot of the device and returns it in defined image format
        /// </summary>
        /// <typeparam name="T">Type of the image</typeparam>
        /// <returns>The screenshot.</returns>
        public T CaptureScreen<T>() where T : class
        {
            return AdbHelper.Instance.GetFrameBuffer<T>(AndroidDebugBridge.SocketAddress, this);
        }

        /// <summary>
        /// Executes a shell command on the device, and sends the result to a receiver.
        /// </summary>
        /// <param name="command">The command to execute</param>
        /// <param name="receiver">The receiver object getting the result from the command.</param>
        public void ExecuteShellCommand(string command, IShellOutputReceiver receiver)
        {
            ExecuteShellCommand(command, receiver, new object[] { });
        }

        /// <summary>
        /// Executes a shell command on the device, and sends the result to a receiver.
        /// </summary>
        /// <param name="command">The command.</param>
        /// <param name="receiver">The receiver.</param>
        /// <param name="timeout">The timeout.</param>
        public void ExecuteShellCommand(string command, IShellOutputReceiver receiver, int timeout)
        {
            ExecuteShellCommand(command, receiver, timeout, new object[] { });
        }

        /// <summary>
        /// Executes a shell command on the device, and sends the result to a receiver.
        /// </summary>
        /// <param name="command">The command.</param>
        /// <param name="receiver">The receiver.</param>
        /// <param name="commandArgs">The command args.</param>
        public void ExecuteShellCommand(string command, IShellOutputReceiver receiver, params object[] commandArgs)
        {
            AdbHelper.Instance.ExecuteRemoteCommand(AndroidDebugBridge.SocketAddress, string.Format(command, commandArgs), this, receiver);
        }

        /// <summary>
        /// Executes a shell command on the device, and sends the result to a receiver.
        /// </summary>
        /// <param name="command">The command.</param>
        /// <param name="receiver">The receiver.</param>
        /// <param name="timeout">The timeout.</param>
        /// <param name="commandArgs">The command args.</param>
        public void ExecuteShellCommand(string command, IShellOutputReceiver receiver, int timeout, params object[] commandArgs)
        {
            AdbHelper.Instance.ExecuteRemoteCommand(AndroidDebugBridge.SocketAddress, string.Format(command, commandArgs), this, receiver, timeout);
        }

        /// <summary>
        /// Executes a shell command on the device as root, and sends the result to a receiver.
        /// </summary>
        /// <param name="command">The command.</param>
        /// <param name="receiver">The receiver.</param>
        public void ExecuteRootShellCommand(string command, IShellOutputReceiver receiver, int timeout)
        {
            ExecuteRootShellCommand(command, receiver, timeout, new object[] { });
        }

        /// <summary>
        /// Executes a shell command on the device as root, and sends the result to a receiver.
        /// </summary>
        /// <param name="command">The command to execute</param>
        /// <param name="receiver">The receiver object getting the result from the command.</param>
        public void ExecuteRootShellCommand(string command, IShellOutputReceiver receiver)
        {
            ExecuteRootShellCommand(command, receiver, int.MaxValue);
        }

        /// <summary>
        /// Executes a root shell command on the device, and sends the result to a receiver.
        /// </summary>
        /// <param name="command">The command.</param>
        /// <param name="receiver">The receiver.</param>
        /// <param name="commandArgs">The command args.</param>
        public void ExecuteRootShellCommand(string command, IShellOutputReceiver receiver, params object[] commandArgs)
        {
            ExecuteRootShellCommand(command, receiver, int.MaxValue, commandArgs);
        }

        /// <summary>
        /// Executes a root shell command on the device, and sends the result to a receiver.
        /// </summary>
        /// <param name="command">The command.</param>
        /// <param name="receiver">The receiver.</param>
        /// <param name="timeout">The timeout.</param>
        /// <param name="commandArgs">The command args.</param>
        public void ExecuteRootShellCommand(string command, IShellOutputReceiver receiver, int timeout, params object[] commandArgs)
        {
            AdbHelper.Instance.ExecuteRemoteRootCommand(AndroidDebugBridge.SocketAddress, string.Format(command, commandArgs), this, receiver, timeout);
        }

        /// <summary>
        /// Runs the dev service.
        /// </summary>
        /// <param name="filePath">File to read.</param>
        /// <param name="target">The stream to copy into</param>
        /// <returns>The file contents in a stream</returns>
        public Stream RunDevService(string filePath, Stream target = null)
        {
            try
            {
                return AdbHelper.Instance.RunDevService(AndroidDebugBridge.SocketAddress, this, filePath, target);
            }
            catch (AdbCommandRejectedException e)
            {
                if (string.Compare(e.Message, "closed", true) == 0)
                {
                    throw new FileNotFoundException(filePath);
                }
                throw e;
            }
            catch
            {
                throw;
            }
        }

        /// <summary>
        /// Runs the bug reporter service, and feeds the receiver with the data
        /// </summary>
        /// <param name="receiver">The receiver object getting the result from the bugreporter</param>
        /// <param name="timeout">The timeout</param>
        public void RunBugReporterService(IShellOutputReceiver receiver, int timeout)
        {
            AdbHelper.Instance.RunBugReporterService(AndroidDebugBridge.SocketAddress, this, receiver, timeout);
        }

        /// <summary>
        /// Runs the tail service.
        /// </summary>
        /// <param name="filePath">File to tail.</param>
        /// <param name="receiver">The receiver.</param>
        /// <param name="bufferSize">Size of the buffer to be used</param>
        public void RunTailService(string filePath, ITailReceiver receiver, int bufferSize = 4 * 1024)
        {
            try
            {
                AdbHelper.Instance.RunTailService(AndroidDebugBridge.SocketAddress, this, filePath, receiver, bufferSize);
            }
            catch (AdbCommandRejectedException e)
            {
                if (string.Compare(e.Message, "closed", true) == 0)
                {
                    throw new FileNotFoundException(filePath);
                }
                throw e;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="filePath"></param>
        /// <param name="receiver"></param>
        public void RunCatLog(string filePath, LogReceiver receiver)
        {
            AdbHelper.Instance.RunCatLog(AndroidDebugBridge.SocketAddress, this, filePath, receiver);
        }

        /// <summary>
        /// Runs the event log service.
        /// </summary>
        /// <param name="receiver">The receiver.</param>
        public void RunEventLogService(LogReceiver receiver)
        {
            AdbHelper.Instance.RunEventLogService(AndroidDebugBridge.SocketAddress, this, receiver);
        }

        /// <summary>
        /// Runs the log service.
        /// </summary>
        /// <param name="logname">The logname.</param>
        /// <param name="receiver">The receiver.</param>
        public void RunLogService(string logname, LogReceiver receiver)
        {
            AdbHelper.Instance.RunLogService(AndroidDebugBridge.SocketAddress, this, logname, receiver);
        }

        /// <summary>
        /// Creates a port forwarding between a local and a remote port.
        /// </summary>
        /// <param name="localPort">the local port to forward</param>
        /// <param name="remotePort">the remote port.</param>
        /// <returns><code>true</code> if success.</returns>
        public bool CreateForward(int localPort, int remotePort)
        {
            try
            {
                return AdbHelper.Instance.CreateForward(AndroidDebugBridge.SocketAddress, this, localPort, remotePort);
            }
            catch (IOException e)
            {
                Log.w("ddms", e);
                return false;
            }
        }

        /// <summary>
        /// Removes a port forwarding between a local and a remote port.
        /// </summary>
        /// <param name="localPort">the local port to forward</param>
        /// <returns><code>true</code> if success.</returns>
        public bool RemoveForward(int localPort)
        {
            try
            {
                return AdbHelper.Instance.RemoveForward(AndroidDebugBridge.SocketAddress, this, localPort);
            }
            catch (IOException e)
            {
                Log.w("ddms", e);
                return false;
            }
        }

        /// <summary>
        /// Installs an Android application on device.
        /// This is a helper method that combines the syncPackageToDevice, installRemotePackage,
        /// and removePackage steps
        /// </summary>
        /// <param name="packageFilePath">the absolute file system path to file on local host to install</param>
        /// <param name="reinstall">set to <code>true</code>if re-install of app should be performed</param>
        public void InstallPackage(string packageFilePath, bool reinstall)
        {
            string remoteFilePath = SyncPackageToDevice(packageFilePath);
            InstallRemotePackage(remoteFilePath, reinstall);
            RemoveRemotePackage(remoteFilePath);
        }

        /// <summary>
        /// Pushes a file to device
        /// </summary>
        /// <param name="localFilePath">the absolute path to file on local host</param>
        /// <returns>destination path on device for file</returns>
        /// <exception cref="IOException">if fatal error occurred when pushing file</exception>
        public string SyncPackageToDevice(string localFilePath)
        {
            try
            {
                string packageFileName = Path.GetFileName(localFilePath);
                // only root has access to /data/local/tmp/... not sure how adb does it then...
                // workitem: 16823
                // string remoteFilePath = string.Format ( "/data/local/tmp/{0}", packageFileName );

                //string remoteFilePath = LinuxPath.Combine(TEMP_DIRECTORY_FOR_INSTALL, localFilePath);
                // CHANGE FOR Test Automation Bridge
                string remoteFilePath = string.Format("/data/local/tmp/{0}", packageFileName);
                //Console.WriteLine(string.Format("Uploading {0} onto device '{1}'", packageFileName, SerialNumber));
                Log.d(packageFileName, string.Format("Uploading {0} onto device '{1}'", packageFileName, SerialNumber));

                SyncService sync = SyncService;
                if (sync != null)
                {
                    String message = string.Format("Uploading file onto device '{0}'", SerialNumber);
                    Log.d(LOG_TAG, message);
                    SyncResult result = sync.PushFile(localFilePath, remoteFilePath, SyncService.NullProgressMonitor);

                    if (result.Code != ErrorCodeHelper.RESULT_OK)
                    {
                        throw new IOException(string.Format("Unable to upload file: {0}", result.Message));
                    }
                }
                else
                {
                    throw new IOException("Unable to open sync connection!");
                }
                return remoteFilePath;
            }
            catch (IOException e)
            {
                Log.e(LOG_TAG, string.Format("Unable to open sync connection! reason: {0}", e.Message));
                throw;
            }
        }

        /// <summary>
        /// Installs the application package that was pushed to a temporary location on the device.
        /// </summary>
        /// <param name="remoteFilePath">absolute file path to package file on device</param>
        /// <param name="reinstall">set to <code>true</code> if re-install of app should be performed</param>
        public void InstallRemotePackage(string remoteFilePath, bool reinstall)
        {
            InstallReceiver receiver = new InstallReceiver();
            FileEntry entry = FileListingService.FindFileEntry(remoteFilePath);
            string cmd = string.Format("pm install {1}{0}", entry.FullEscapedPath, reinstall ? "-r " : string.Empty);
            ExecuteShellCommand(cmd, receiver, DdmPreferences.LongTimeout);

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
        public void RemoveRemotePackage(string remoteFilePath)
        {
            // now we delete the app we sync'ed
            try
            {
                ExecuteShellCommand("rm " + remoteFilePath, NullOutputReceiver.Instance, DdmPreferences.Timeout);
            }
            catch (IOException e)
            {
                Log.e(LOG_TAG, string.Format("Failed to delete temporary package: {0}", e.Message));
                throw e;
            }
        }

        /// <summary>
        /// Uninstall an package from the device.
        /// </summary>
        /// <param name="packageName">Name of the package.</param>
        /// <exception cref="IOException"></exception>
        /// <exception cref="PackageInstallException"></exception>
        public void UninstallPackage(string packageName)
        {
            InstallReceiver receiver = new InstallReceiver();
            ExecuteShellCommand(string.Format("pm uninstall {0}", packageName), receiver, DdmPreferences.LongTimeout);

            if (!string.IsNullOrEmpty(receiver.ErrorMessage))
            {
                throw new PackageInstallationException(receiver.ErrorMessage);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:StateChanged"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        internal void OnStateChanged(EventArgs e)
        {
            if (StateChanged != null)
            {
                StateChanged(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:BuildInfoChanged"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        internal void OnBuildInfoChanged(EventArgs e)
        {
            if (BuildInfoChanged != null)
            {
                BuildInfoChanged(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:ClientListChanged"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        internal void OnClientListChanged(EventArgs e)
        {
            if (ClientListChanged != null)
            {
                ClientListChanged(this, e);
            }
        }

        private class IsRootedReceiver : MultiLineReceiver
        {
            protected override void ProcessNewLines(string[] lines)
            {
                IsRooted = lines.Length >= 2 && lines[1].Trim().ToLower().StartsWith("root");
            }

            public bool IsRooted { get; private set; }
        }

        /// <summary>
        /// 
        /// </summary>
        public bool IsRooted
        {
            get
            {
                if (IsOnline)
                {
                    var receiver = new IsRootedReceiver();
                    ExecuteShellCommand("ps adbd", receiver);
                    return receiver.IsRooted;
                }
                return false;
            }
        }
    }
}