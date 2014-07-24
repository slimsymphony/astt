using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Linq;
using System.Text;
using System.Threading;
using System.Drawing;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;
using Managed.Adb;
using Managed.Adb.Exceptions;
using TestAutomation.Client;
using TestAutomation.Utils;


namespace TestAutomation.Bridge
{
	/// <summary>
	/// Represents an exception with TAB interface
	/// </summary>
    public class TABException : Exception
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="TABException"/> class.
        /// </summary>
        public TABException()
            : base("An error occurred with TAB interface")
        { }

        /// <summary>
        /// Initializes a new instance of the <see cref="TABException"/> class.
        /// </summary>
        /// <param name="message">The message.</param>
        public TABException(string message)
            : base(message)
        { }

        /// <summary>
        /// Initializes a new instance of the <see cref="TABException"/> class.
        /// </summary>
        /// <param name="serializationInfo">The serialization info.</param>
        /// <param name="context">The context.</param>
        public TABException(SerializationInfo serializationInfo, StreamingContext context)
            : base(serializationInfo, context)
        { }

        /// <summary>
        /// Initializes a new instance of the <see cref="TABException"/> class.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="innerException">The inner exception.</param>
        public TABException(string message, Exception innerException)
            : base(message, innerException)
        { }
    }

    /// <summary>
    /// Test Automation Bridge interface class
    /// </summary>
    public static class TABInterface
    {
        public static int DEFAULT_ADB_TIMEOUT { get; private set; }
        public static int INFINITE_ADB_TIMEOUT { get; private set; }
        public static int LONG_TIMEOUT { get; private set; }

        // FIXME: Add support for multiple devices having crash dumps
        public static bool crashDumpFilesChecked;
        public static List<string> handledCrashDumpFiles;
        public static List<string> newRamDumpFiles;
        public static List<string> handledRamDumpFiles;
        public static long AnrTracesFileSize = 0;

        public static Dictionary<int, Mutex> reservedServerPorts;
        public static Dictionary<int, Mutex> reservedScriptingPorts;

        /// <summary>
        /// 
        /// </summary>
        public const int DEFAULT_ADB_FORKER_WAIT_TIME = 10000;

        /// <summary>
        /// 
        /// </summary>
        public const int DEFAULT_ADB_SERVER_WAIT_TIME = 10000;

        /// <summary>
        /// 
        /// </summary>
        private const string ADB_RECREATION_LOCK = "TESTAUTOMATION_ADB_RECREATION";

        /// <summary>
        /// 
        /// </summary>
        private static string ADB_LOCATION = "";

        /// <summary>
        /// Device type enumeratios
        /// </summary>
        public enum DeviceType
        {
            /// <summary>
            /// HW device
            /// </summary>
            HW = 1,
            /// <summary>
            /// Emulator device
            /// </summary>
            EMULATOR = 2,
            /// <summary>
            /// Either HW or emulator device
            /// </summary>
            ANY = 3,
        }

        /// <summary>
        /// Event type enumeratios
        /// </summary>
        public static EventType TABEvents;

        /// <summary>
        /// Private constructor
        /// </summary>
        static TABInterface()
        {         
            DEFAULT_ADB_TIMEOUT = 10000;
            INFINITE_ADB_TIMEOUT = int.MaxValue;
            LONG_TIMEOUT = 30000;
            crashDumpFilesChecked = false;;
            handledCrashDumpFiles = new List<string>();
            newRamDumpFiles = new List<string>();
            handledRamDumpFiles = new List<string>();
            reservedServerPorts = new Dictionary<int, Mutex>();
            reservedScriptingPorts = new Dictionary<int, Mutex>();
        }

        #region Private

        /// <summary>
        /// Create connection
        /// </summary>
        /// <param name="serial"></param>
        /// <param name="deviceType"></param>
        /// <param name="rootAndRemount">Whether root and remount commands will be run</param>
        /// <param name="serverLevelInUse">Whether server level and scripting layer is used or not</param>
        /// <param name="ciEnabled">Whether Marble is run in C.I environment or not</param>
        /// <returns>TABConnection instance or null</returns>
        /// <exception cref="TABException"></exception>
        private static TABConnection CreateConnection(string serial, DeviceType deviceType, bool rootAndRemount, bool serverLevelInUse, bool ciEnabled)
        {
            TABConnection tab = null;
            TestAutomationServerOptions serverOptions = TestAutomationServerOptions.Default;
            ScriptingServiceOptions scriptingServiceOptions = ScriptingServiceOptions.Default;

            if (serverLevelInUse)
            {
                // set test automation server and scripting options
                //serverOptions.ForcePushArchive = true;
                serverOptions.LocalArchiveLocation = "TAServer.jar";

                serverOptions.ShutDownOnUsbDisconnect = true;

                /*
                con.TestServerClient.ServerPushProgress += TestServerClient_ServerPushProgress;            
                con.TestServerClient.UiEvent += TestServerClient_UiEvent;
                con.TestServerClient.ServerTrace += TestServerClient_ServerTrace;
                con.TestServerClient.EnableRemoteEvents = true;
                */
            }
            
            // check with GetDevices is ADB connection ok or not
            List<string> deviceList = new List<string>();

            try
            {
                deviceList = GetDevices(deviceType);
            }
            catch (Exception)
            {
                // exception in GetDevices, recreate ADB connection
                // in C.I environment we can't restart ADB
                if (!ciEnabled)
                {
                    RecreateADBConnection();
                }

                deviceList = GetDevices(deviceType);
            }

            try
            {
                // create connection to specific device
                if (serial != "")
                {
                    if (deviceList.Contains(serial))
                    {

                        try
                        {
                            tab = new TABConnection(serial, serverLevelInUse, serverOptions, scriptingServiceOptions);
                        }
                        catch (DeviceNotFoundException)
                        {
                            throw new TABException("Device not found with serial: " + serial);
                        }
                    }
                    else
                    {
                        throw new TABException("Device not found with serial: " + serial);
                    }
                }
                // create connection to first device found
                else
                {
                    if (deviceList.Count > 0)
                    {
                        tab = new TABConnection(deviceList[0], serverLevelInUse, serverOptions, scriptingServiceOptions);
                    }
                }
            }
            catch (Exception err)
            {
                // FIXME: What to do when "[System.Net.Sockets.SocketException] = {"No connection could be made because the target machine actively refused it 127.0.0.1:5037"}" occurs
                // This happens at least when ADB daemon is not running

                Console.Error.Write("Error in TAB connection creation: " + err.ToString());
                throw new TABException(err.ToString());
            }

            if (tab != null && rootAndRemount)
            {
                // NOTE: Loop here, because root and remount command could happen too soon after connection creation
                for (int i = 0; i < 3; i++)
                {
                    try
                    {
                        // root and remout device
                        tab.RootAndRemount();
                        break;
                    }
                    catch (TABException err)
                    {
                        Console.Error.Write("Error when trying to root and remount: " + err.ToString());
                        Thread.Sleep(2000);
                    }
                }
            }

            return tab;
        }

        /// <summary>
        /// Enters into ADB recreation mutex
        /// </summary>
        /// <returns>Mutex or null</returns>
        internal static Mutex EnterMutex()
        {
            Mutex mutex;
            string name = "MARBLE_ADB_RECREATION";

            if (!Mutex.TryOpenExisting(name, out mutex))
            {
                mutex = new Mutex(false, name);
            }

            return mutex;
        }

        /// <summary>
        /// Frees mutex
        /// </summary>
        /// <param name="mutex"></param>
        internal static void FreeMutex(Mutex mutex)
        {
            if (mutex != null)
            {
                try
                {
                    mutex.ReleaseMutex();
                }
                catch (ObjectDisposedException)
                { }
            }
        }

        #endregion

        #region Public

        /// <summary>
        /// Run given ADB command
        /// </summary>
        /// <param name="AdbCommand">ADB command string</param>
        /// <param name="responseComing">Whether response is coming to given command</param>
        /// <exception cref="TABException"></exception>
        /// 
        public static string RunAdbCommand(string AdbCommand, bool responseComing = true)
        {
            byte[] request = AdbHelper.Instance.FormAdbRequest(AdbCommand);
            byte[] reply;
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                socket.Connect(AndroidDebugBridge.SocketAddress);
                socket.Blocking = true;
                socket.ReceiveTimeout = DEFAULT_ADB_TIMEOUT;

                if (!AdbHelper.Instance.Write(socket, request))
                {
                    throw new TABException("failed to execute command: " + AdbCommand);
                }

                AdbResponse resp = AdbHelper.Instance.ReadAdbResponse(socket, false);
                if (!resp.IOSuccess || !resp.Okay)
                {
                    socket.CloseNoWait();
                    throw new TABException("invalid response command: " + AdbCommand);
                }

                if (responseComing)
                {
                    reply = new byte[4];
                    if (!AdbHelper.Instance.Read(socket, reply))
                    {
                        socket.CloseNoWait();
                        throw new TABException("unable to read response to command: " + AdbCommand);
                    }
                    string lenHex = Encoding.Default.GetString(reply);
                    int len = int.Parse(lenHex, System.Globalization.NumberStyles.HexNumber);

                    reply = new byte[len];
                    if (!AdbHelper.Instance.Read(socket, reply))
                    {
                        socket.CloseNoWait();
                        throw new TABException("unable to read response to command: " + AdbCommand);
                    }

                    return Encoding.Default.GetString(reply);
                }
                else
                {
                    return "";
                }
            }
            catch (SocketException err)
            {
                throw new TABException("unable to execute ADB command: " + AdbCommand + " socket error: " + err.ToString());
            }
            finally
            {
                socket.CloseNoWait();
            }
        }

        /// <summary>
        /// Get available device names
        /// </summary>
        /// <param name="deviceType">enum DeviceType</param>  
        /// <returns>List<string> of available devices.</returns>
        /// <exception cref="TABException"></exception>
        public static List<string> GetDevices(DeviceType deviceType = DeviceType.ANY)
        {
            List<string> deviceList = new List<string>();

            string[] response = RunAdbCommand("host:devices").Split(new string[] { "\r\n", "\n" }, StringSplitOptions.RemoveEmptyEntries);

            foreach (string deviceInfo in response)
            {
                if (deviceInfo.Contains("offline"))
                {
                    continue;
                }

                string deviceName = deviceInfo.Split('\t')[0];

                if ((deviceType == DeviceType.EMULATOR && deviceName.StartsWith("emulator")) ||
                    (deviceType == DeviceType.HW && !deviceName.StartsWith("emulator")) ||
                    deviceType == DeviceType.ANY)
                {
                    deviceList.Add(deviceName);
                }
            }

            return deviceList;
        }

        /// <summary>
        /// Create connection
        /// </summary>
        /// <param name="serial">Serial number of the device</param>
        /// <param name="sl4aPath">Path to sl4a apk file</param>
        /// <param name="rootAndRemount">Whether root and remount commands will be run</param>
        /// <param name="serverLevelInUse">Whether server level and scripting layer is used or not</param>
        /// <param name="ciEnabled">Whether Marble is run in C.I environment or not</param>
        /// <returns>TABConnection instance or null</returns>
        /// 
        public static TABConnection CreateConnectionWithSerial(string serial, bool rootAndRemount = true, bool serverLevelInUse = true, bool ciEnabled = false)
        {
            return CreateConnection(serial, DeviceType.ANY, rootAndRemount, serverLevelInUse, ciEnabled);
        }

        /// <summary>
        /// Create connection
        /// </summary>
        /// <param name="deviceType">enum DeviceType</param>
        /// <param name="rootAndRemount">Whether root and remount commands will be run</param>
        /// <param name="serverLevelInUse">Whether server level and scripting layer is used or not</param>
        /// <param name="ciEnabled">Whether Marble is run in C.I environment or not</param>
        /// <returns>TABConnection instance or null</returns>
        /// 
        public static TABConnection CreateConnection(DeviceType deviceType = DeviceType.ANY, bool rootAndRemount = true, bool serverLevelInUse = true, bool ciEnabled = false)
        {
            return CreateConnection("", deviceType, rootAndRemount, serverLevelInUse, ciEnabled);
        }


        /// <summary>
        /// Set ADB executables path.
        /// </summary>
        /// <param name="path">ADB path string</param>
        public static void SetADBPath(string path)
        {
            AndroidDebugBridge.AdbOsLocation = ADB_LOCATION = path;
        }

        /// <summary>
        /// Restart the ADB server to get ADB connection working.
        /// </summary>
        /// <param name="onlyIfNotAlive">Restart ADB server only if it's not alive</param>
        /// <returns>True if ADB was restarted, False if not.</returns>
        public static bool RecreateADBConnection(bool onlyIfNotAlive = false)
        {
            List<Process> adbProcesses = new List<Process>();
            bool adbRestarted = false;
            Mutex adbRestartMutex = null;
                        
            try
            {
                using (adbRestartMutex = EnterMutex())
                {
                    try
                    {
                        if (!adbRestartMutex.WaitOne(30000))
                        {
                            // other Marble process is restarting ADB
                            return false;
                        }
                    }
                    catch (MulticastNotSupportedException)
                    {
                        //Another process/thread using the same device has crashed
                    }

                    // go through ADB processes
                    foreach (Process adbProcess in Process.GetProcessesByName("adb"))
                    {
                        adbProcesses.Add(adbProcess);
                    }

                    if (onlyIfNotAlive)
                    {
                        if (adbProcesses.Count == 0)
                        {
                            return AndroidDebugBridge.Instance.StartAdb();
                        }
                    }
                    else
                    {
                        AndroidDebugBridge.Instance.StopAdb();

                        // if ADB executable is jammed, kill it
                        foreach (Process adbProcess in adbProcesses)
                        {
                            adbProcess.Kill();
                        }

                        adbRestarted = AndroidDebugBridge.Instance.StartAdb();
                    }
                }
            }
            finally
            {
                FreeMutex(adbRestartMutex);
            }

            //AndroidDebugBridge.DisconnectBridge();
            //AndroidDebugBridge.Instance.Restart();
            //AndroidDebugBridge.CreateBridge(AndroidDebugBridge.AdbOsLocation, true);
            //AndroidDebugBridge.CreateBridge();

            return adbRestarted;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public static bool RestartAdbServer()
        {
            if (!string.IsNullOrEmpty(ADB_LOCATION))
            {
                Mutex mutex = null;
                if (LockAdbRestart(out mutex))
                {
                    var success = StopAdbServer();
                    if (success)
                    {
                        success &= StartAdbServer();
                    }
                    FreeAdbRestart(mutex);
                    return success;
                }
                else
                {
                    var waitTime = DEFAULT_ADB_FORKER_WAIT_TIME + DEFAULT_ADB_SERVER_WAIT_TIME;
                    if (WaitForAdb(waitTime))
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="timeout"></param>
        /// <returns></returns>
        public static bool WaitForAdb(int timeout)
        {
            var start = DateTime.Now;

            while (DateTime.Now.Subtract(start).TotalMilliseconds < timeout)
            {
                if (AdbDiagnostics.IsRunning)
                {
                    return true;
                }
                Thread.Sleep(200);
            }
            return AdbDiagnostics.IsRunning;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private static bool LockAdbRestart(out Mutex mutex)
        {
            mutex = null;

            if (!Mutex.TryOpenExisting(ADB_RECREATION_LOCK, out mutex))
            {
                mutex = new Mutex(false, ADB_RECREATION_LOCK);
            }
            using (mutex)
            {
                var locked = false;

                try
                {
                    locked = !mutex.WaitOne(0);
                }
                catch (AbandonedMutexException)
                {
                    locked = false;
                }

                if (!locked)
                {
                    return true;
                }

                try
                {
                    mutex.ReleaseMutex();
                }
                catch (ApplicationException) { }

                return false;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="mutex"></param>
        private static void FreeAdbRestart(Mutex mutex)
        {
            try
            {
                using (mutex)
                {
                    mutex.ReleaseMutex();
                }
            }
            catch (Exception) { }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="hostPort"></param>
        /// <returns></returns>
        private static bool StopAdbServer()
        {
            if (!AdbDiagnostics.IsRunning) return true;

            var adb = AdbDiagnostics.Process;
            if (adb != null)
            {
                adb.Kill();
            }

            return !AdbDiagnostics.IsRunning;
        }

        /// <summary>
        /// Starts the ADB server
        /// </summary>
        private static bool StartAdbServer()
        {
            if (AdbDiagnostics.IsRunning) return true;

            if (string.IsNullOrEmpty(ADB_LOCATION) || !File.Exists(ADB_LOCATION))
            {
                ADB_LOCATION = AdbDiagnostics.DefaultAdbLocation;
            }

            var adbForkerProcess = new Process
            {
                StartInfo =
                {
                    FileName = ADB_LOCATION,
                    Arguments = "start-server",
                    UseShellExecute = true, //WE DO NOT TAKE THE OWNERSHIP!!!
                    CreateNoWindow = true,
                    WindowStyle = ProcessWindowStyle.Hidden
                }
            };

            if (adbForkerProcess.Start())
            {
                adbForkerProcess.WaitForExit(DEFAULT_ADB_FORKER_WAIT_TIME);
            }
            return adbForkerProcess.HasExited && adbForkerProcess.ExitCode == 0 && WaitForAdb(DEFAULT_ADB_SERVER_WAIT_TIME);
        }

        #endregion
    }

    /// <summary>
    /// Test Automation Bridge connection class. Implemented on top of ADB Device class.
    /// </summary>
    public sealed class TABConnection : Device, IDisposable
    {
        private const string TIME_ZONE_TAG = "persist.sys.timezone";

        string baseInputCommand = "";
        public MemoryStream screencapDataStream { get; private set; }
        public bool RootSuccess = false;
        public bool RemountSuccess = false;
        public List<String> DisAllowedBinderNames = new List<string>();
        private static bool callerVerified = false;
        private Mutex connectionMutex = null;
        
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="serial"></param>
        /// <param name="serverLevelInUse">Whether server level and scripting layer is used or not</param>
        /// <param name="serverOptions">TestAutomationServerOptions</param>
        /// <param name="scriptingServiceOptions">ScriptingServiceOptions</param>
        /// 
        public TABConnection(string serial, bool serverLevelInUse, TestAutomationServerOptions serverOptions, ScriptingServiceOptions scriptingServiceOptions)
            : base(serial, DeviceState.Online)
        {
            // try to pass the "Hodge filter"
            HodgeFilter();

            //// get mutex
            //using (connectionMutex = EnterMutex(serial))
            //{
            //    try
            //    {
            //        if (!connectionMutex.WaitOne(10000))
            //        {
            //            throw new TABException("Device with serial: " + serial + " was reserved by other process");
            //        }
            //    }
            //    catch (MulticastNotSupportedException)
            //    {
            //        //Another process/thread using the same device has crashed
            //    }
            //}

            Logger = new Logger(this); //dispose
            Logger.WriteSourceBufferName = true;
            Logger.OutputFormat = OutputFormat.Long;
            Crashdumps = new CrashdumpInfoCollection();
            File = new FileSystemAdapter(this);
            Shell = new Shell(this);
            Time = new Time(this);
            SqLite = new SqLite(this);
            MediaPlayer = new MediaPlayer(this);
            ViewServerClient = new ViewServerClient(this);
            PowerManager = new PowerManager(this);
            Packages = new PackageManager(this);
            ActivityManager = new ActivityManager(this);
            BugReport = new BugReport(this);

            if (serverLevelInUse)
            {
                TestServerClient = new TestServerClient(this, serverOptions); //dispose
                
                ScriptingServiceClient = new ScriptingServiceClient(this, scriptingServiceOptions); //dispose

                //Requires TestServerClient to be connected
                TombstoneObserver = new DirectoryObserver(TestServerClient, "/data/tombstones/", OnTombstoneObserved);
                TombstoneObserver.EnableRaisingEvents = true;

                //Requires TestServerClient to be connected
                DropboxObserver = new DirectoryObserver(TestServerClient, "/data/system/dropbox/", OnDropboxObserved);
                DropboxObserver.EnableRaisingEvents = true;

                //Requires TestServerClient to be connected
                AnrObserver = new DirectoryObserver(TestServerClient, "/data/anr/", OnAnrObserved);
                AnrObserver.EnableRaisingEvents = true;
            }

            // initialize memory stream
            screencapDataStream = new MemoryStream();

            baseInputCommand = "sendevent /dev/input/event0";

            // set base input command according to device type
            //if (IsEmulator)
            //{
            
            //}
            //else
            //{
            //    baseInputCommand = "sendevent /dev/input/event1";
            //}
            /*
            else
            {
                // event4 for Onda
                baseInputCommand = "sendevent /dev/input/event4";
            }
            */
        }

        ///// <summary>
        ///// Destructor
        ///// </summary>
        //~TABConnection() 
        //{
        //    FreeMutex(connectionMutex);
        //}

        /// <summary>
        /// Dispose
        /// </summary>
        public void Dispose()
        {
            //FreeMutex(connectionMutex);
        }

        #region "Public events"

        /// <summary>
        /// Fired when a new crash dump file is reported
        /// </summary>
        public event CrashDumpHandler CrashDumpCreated;

        #endregion

        #region "Public properties"

        /// <summary>
        /// Gets the instance providing logcat services
        /// </summary>
        public Logger Logger { get; private set; }

        /// <summary>
        /// Gets the instance of crashdump collection
        /// </summary>
        public CrashdumpInfoCollection Crashdumps { get; private set;}

        /// <summary>
        /// Gets the  SqlLite manager instance
        /// </summary>
        public SqLite SqLite { get; private set; }

        /// <summary>
        /// Gets the file system adapter instance for file operations
        /// </summary>
        public FileSystemAdapter File { get; private set; }

        /// <summary>
        /// Gets the shell instance
        /// </summary>
        public Shell Shell { get; private set; }

        /// <summary>
        /// Gets the time instance
        /// </summary>
        public Time Time { get; private set; }

        /// <summary>
        /// Gets the activity manager instance
        /// </summary>
        public ActivityManager ActivityManager { get; private set; }

        /// <summary>
        /// Gets the test server client instance
        /// </summary>
        public TestServerClient TestServerClient { get; private set; }

        /// <summary>
        /// Gets the scripting service client instance
        /// </summary>
        public ScriptingServiceClient ScriptingServiceClient { get; private set; }

        /// <summary>
        /// Gets the media player instance
        /// </summary>
        public MediaPlayer MediaPlayer { get; private set; }

        /// <summary>
        /// Gets the view server client instance
        /// </summary>
        public ViewServerClient ViewServerClient { get; private set; }

        /// <summary>
        /// Gets the power manager instance
        /// </summary>
        public PowerManager PowerManager { get; private set; }

        /// <summary>
        /// Gets the package manager instance
        /// </summary>
        public PackageManager Packages { get; private set; }

        /// <summary>
        /// Gets the BugReport instance
        /// </summary>
        public BugReport BugReport { get; private set; }


        #endregion

        #region Private

        /// <summary>
        /// Gets the tombstone observer instance
        /// </summary>
        private DirectoryObserver TombstoneObserver { get; set; }

        /// <summary>
        /// Gets the dropbox observer instance
        /// </summary>
        private DirectoryObserver DropboxObserver { get; set; }

        /// <summary>
        /// Gets the anr observer instance
        /// </summary>
        private DirectoryObserver AnrObserver { get; set; }

        /// <summary>
        /// Called when a tombstone is being created, changed, removed
        /// </summary>
        /// <param name="devent">Details</param>
        private void OnTombstoneObserved(DirectoryObserverEvent devent)
        {
            if (devent.ChangeType == FileChangeTypes.CREATE)
            {
                if (CrashDumpCreated != null)
                {
                    CrashDumpCreated(new CrashdumpInfo(devent.FileName, devent.TimeStamp, CrashdumpSource.Tombstone));
                }
            }
        }

        /// <summary>
        /// Called when a dropbox is being accessed
        /// </summary>
        /// <param name="devent">Details</param>
        private void OnDropboxObserved(DirectoryObserverEvent devent)
        {
            if (devent.ChangeType == FileChangeTypes.CREATE)
            {               
                if (CrashDumpCreated != null)
                {
                    CrashDumpCreated(new CrashdumpInfo(devent.FileName, devent.TimeStamp, CrashdumpSource.Dropbox));
                }
            }
        }

        /// <summary>
        /// Called when an anr is being created, changed, removed
        /// </summary>
        /// <param name="devent">Details</param>
        private void OnAnrObserved(DirectoryObserverEvent devent)
        {
            if (devent.ChangeType == FileChangeTypes.CREATE)
            {
                if (CrashDumpCreated != null)
                {
                    CrashDumpCreated(new CrashdumpInfo(devent.FileName, devent.TimeStamp, CrashdumpSource.Anr));
                }
            }
        }

        /// <summary>
        /// Touch press command function
        /// </summary>
        /// <param name="x">x coordinate.</param>
        /// <param name="y">y coordinate.</param>
        /// <param name="wait">wait, how long press will be.</param>
        /// <returns>true if actions succeeds, false if not.</returns>
        private bool TouchPress(int x, int y, int wait)
        {
            string commandString = "";

            if (Properties["ro.build.product"] == "crespo")
            {
                commandString = String.Join(";",
                                            baseInputCommand + " 3 53 " + y.ToString(),
                                            baseInputCommand + " 3 54 " + x.ToString(),
                                            baseInputCommand + " 3 58 45",
                                            baseInputCommand + " 0 2 0",
                                            baseInputCommand + " 0 0 0");
            }
            else
            {
                commandString = String.Join(";",
                                            baseInputCommand + " 3 0 " + x.ToString(),
                                            baseInputCommand + " 3 1 " + y.ToString(),
                                            baseInputCommand + " 1 330 1",
                                            baseInputCommand + " 0 0 0");
            }

            // put command to touch command string
            //touchCommands.Add(commandString);

            try
            {
                ExecuteShellCommand(commandString, NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
            }
            catch (Exception)
            {
                return false;
            }

            Thread.Sleep(wait);

            return true;
        }

        /// <summary>
        /// Touch move command function
        /// </summary>
        /// <param name="x">x coordinate.</param>
        /// <param name="y">y coordinate.</param>
        /// <param name="wait">wait after move.</param>
        /// <returns>true if actions succeeds, false if not.</returns>
        private bool TouchMove(int x, int y, int wait)
        {
            string commandString = "";

            if (Properties["ro.build.product"] == "crespo")
            {
                commandString = String.Join(";",
                                            baseInputCommand + " 3 53 " + y.ToString(),
                                            baseInputCommand + " 3 54 " + x.ToString(),
                                            baseInputCommand + " 3 58 45",
                                            baseInputCommand + " 0 2 0",
                                            baseInputCommand + " 0 0 0");
            }
            else
            {
                commandString = String.Join(";",
                                            baseInputCommand + " 3 0 " + x.ToString(),
                                            baseInputCommand + " 3 1 " + y.ToString(),
                                            baseInputCommand + " 0 0 0");
            }

            // append command to touch command string
            //touchCommands.Add(commandString);

            try
            {
                ExecuteShellCommand(commandString, NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
            }
            catch (Exception)
            {
                return false;
            }

            Thread.Sleep(wait);

            return true;
        }
        
        /// <summary>
        /// Gets the image using screencap process
        /// </summary>
        /// <param name="imageFilePath">Destination image file path.</param>
        /// <exception cref="TABException"></exception>
        /// <returns>true if image capturing succeeded, false if not</returns>
        private bool GetImage(string imageFilePath)
        {
            ScreencapResponseReceiver receiver = new ScreencapResponseReceiver(this, imageFilePath);

            bool success = false;
            
            // NOTE: Loop here because sometimes screencap returns invalid PNG data and then we need to try again
            for (int i = 0; i < 50; i++)
            {
                try
                {
                    receiver.Execute();
                    success = receiver.Success;

                    if (success)
                    {
                        break;
                    }
                }
                catch (Exception err)
                {
                    Console.Error.Write("Unable to capture image: " + err.ToString());
                    success = false;
                }
            }

            return success;
        }

        private void CheckAllowedCall(string name)
        {
            if (this.DisAllowedBinderNames.Any(s => name.Contains(s)))
            {
                throw new Exception(String.Format("Disallowed binder: {0}", name));
            }
        }

        /// <summary>
        /// Returns memory card file system items
        /// </summary>
        /// <param name="filePath"></param>
        /// <returns>IEnumerable(RemoteFileInfo) of file system items</returns>
        private IEnumerable<RemoteFileInfo> GetFileSystemItems(string filePath)
        {
            var fileEntries = new List<RemoteFileInfo>();

            try
            {
                fileEntries = File.GetFileSystemItems(filePath);
            }
            catch (DirectoryNotFoundException)
            {}
            catch (UnauthorizedAccessException)
            {}

            return fileEntries;
        }

        #endregion

        #region Protection

        internal static void HodgeFilter()
        {
            if (!IsExecutedViaDebugging)
            {
                if (!callerVerified)
                {
                    if (!IsRunningInIronPython && !IsExecutedByOratorGui && !IsExecutedByMarbleGui && !IsDirectlyExecutedFromConsole && !IsExecutedFromVisualStudio && !IsExecutedFromPython)
                    {
                        Process.GetCurrentProcess().Kill();
                    }

                    callerVerified = true;
                }
            }
        }

        internal static bool IsExecutedByMarbleGui
        {
            get
            {
                return IsExecutedByProcessName("Marble", false, false) || IsExecutedByProcessName("Marble.vshost", false, false);
            }
        }

        internal static bool IsExecutedByOratorGui
        {
            get
            {
                Process pr = Process.GetCurrentProcess();

                if (pr.ProcessName == "OratorAoL.UI" || pr.ProcessName == "OratorAoL.UI.vshost")
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        internal static bool IsRunningInIronPython
        {
            get
            {
                return IsCalledByAssemblyName("Microsoft.Dynamic") &&
                    IsRunningInProcessByName("ipy") &&
                    VerifyEntryAssemblyByName("ipy");
            }
        }

        internal static bool IsCalledByAssemblyName(string assemblyName)
        {
            string myName = typeof(TABConnection).Assembly.GetName().Name;

            if (myName == assemblyName)
            {
                return true;
            }
            //If assembly is being called by MS dynamic, it is loaded to appdomain, but it cannot be found from MS dynamic refrence assemblies;
            //in this case, it shall not either be found from referenced assemblies by other assemblies in appdomain. MS dynamic in this case needs to
            //be loaded in appdomain
            if (assemblyName == "Microsoft.Dynamic")
            {
                //If MS dynamic is not loaded at all...
                if (!AppDomain.CurrentDomain.GetAssemblies().Any(a => a.GetName().Name == "Microsoft.Dynamic"))
                {
                    return false;
                }
                //other assemblies than this itself and MS Dynamic
                var assemblies = AppDomain.CurrentDomain.GetAssemblies().Where(a => a.GetName().Name != "Microsoft.Dynamic"
                    && a.GetName().Name != myName);

                bool anyOtherReferences = assemblies.Any(a => a.GetReferencedAssemblies().Any(an => an.Name == myName));

                return !anyOtherReferences;
            }
            else
            {
                Assembly ass = AppDomain.CurrentDomain.GetAssemblies().First(a => a.GetName().Name == assemblyName);

                if (ass != null)
                {
                    Console.WriteLine();
                    return ass.GetReferencedAssemblies().Any(an => an.Name == myName);
                }

                return false;
            }
        }

        internal static bool VerifyEntryAssemblyByName(string assemblyName)
        {
            return Assembly.GetEntryAssembly().GetName().Name == assemblyName;
        }

        internal static bool IsRunningInProcessByName(string processName)
        {
            return Process.GetCurrentProcess().ProcessName == processName;
        }

        internal static bool IsDirectlyExecutedFromConsole
        {
            get
            {
                Process p = Process.GetCurrentProcess();

                if (!p.HasParent())
                {
                    return true;
                }

                string parentName = p.ParentProcess().ProcessName;

                return parentName == "explorer" || parentName == "cmd";
            }
        }

        internal static bool IsExecutedFromPython
        {
            get
            {
                Process p = Process.GetCurrentProcess();

                if (!p.HasParent())
                {
                    return true;
                }

                string parentName = p.ParentProcess().ProcessName;

                return parentName == "python" || parentName == "ipy";
            }
        }

        internal static bool IsExecutedFromVisualStudio
        {
            get
            {
                Process p = Process.GetCurrentProcess();

                if (!p.HasParent())
                {
                    return true;
                }

                string parentName = p.ParentProcess().ProcessName;

                return parentName == "devenv";
            }
        }

        internal static bool IsExecutedViaDebugging
        {
            get
            {
                return System.Diagnostics.Debugger.IsAttached;
            }
        }

        internal static bool IsExecutedByProcessName(string processName,
            bool checkStdOutRedirection = true,
            bool checkStdErrRedirection = true)
        {
            Process pr = Process.GetCurrentProcess();

            if (!pr.HasParent())
            {
                return false;
            }

            if (pr.ParentProcess().ProcessName != processName)
            {
                return false;
            }

            if (checkStdOutRedirection && !pr.StartInfo.RedirectStandardOutput)
            {
                return false;
            }

            if (checkStdErrRedirection && !pr.StartInfo.RedirectStandardError)
            {
                return false;
            }

            return true;
        }

        ///// <summary>
        ///// Enters into mutex with connection's serial
        ///// </summary>
        ///// <param name="serial"></param>
        ///// <returns>Mutex or null</returns>
        //internal static Mutex EnterMutex(string serial)
        //{
        //    Mutex mutex;

        //    if (!Mutex.TryOpenExisting(serial, out mutex))
        //    {
        //        mutex = new Mutex(false, serial);
        //    }

        //    return mutex;
        //}

        ///// <summary>
        ///// Frees mutex
        ///// </summary>
        ///// <param name="mutex"></param>
        //internal static void FreeMutex(Mutex mutex)
        //{
        //    if (mutex != null)
        //    {
        //        try
        //        {
        //            mutex.ReleaseMutex();
        //        }
        //        catch (ObjectDisposedException)
        //        { }
        //    }
        //}

        #endregion

        #region Public

        #region ADB

        /// <summary>
        /// Root and remount device
        /// </summary>
        /// <exception cref="TABException"></exception>
        public void RootAndRemount()
        {
            RootDevice();
            RemountDevice();
        }

        public void RootDevice()
        {
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                socket.Connect(AndroidDebugBridge.SocketAddress);
                socket.Blocking = true;
                socket.ReceiveTimeout = TABInterface.DEFAULT_ADB_TIMEOUT;

                // set up transport to device
                AdbHelper.Instance.SetDevice(socket, this);

                // root
                string command = "root:";
                byte[] request = AdbHelper.Instance.FormAdbRequest(command);

                if (!AdbHelper.Instance.Write(socket, request))
                {
                    throw new TABException("failed to execute command: " + command);
                }

                AdbResponse resp = AdbHelper.Instance.ReadAdbResponse(socket, false);

                if (!resp.IOSuccess || !resp.Okay)
                {
                    throw new TABException("invalid response to command: " + command);
                }

                RootSuccess = true;
            }
            catch (Exception err)
            {
                throw new TABException(err.ToString());
            }
            finally
            {
                socket.CloseNoWait();
            }
        }

        public void RemountDevice()
        {
            try
            {
                // remount system and data
                RemountMountPoint("/system", false);
                RemountMountPoint("/data", false);

                RemountSuccess = true;
            }
            catch (Exception err)
            {
                throw new TABException(err.ToString());
            }
        }

        /// <summary>
        /// Gets a list of reserved ports in the remote device
        /// </summary>
        /// <returns>List of reserved ports</returns>
        public List<int> GetReservedRemotePorts()
        {
            return IpHelper.GetReservedRemotePorts(this);
        }

        /// <summary>
        /// Get crash dump files
        /// </summary>
        /// <param name="destinationDir">Destination directory where crash dump files will be copied.</param>
        /// <param name="retrieveAllFiles">Whether all crash dump files are retrieved or not.</param>
        /// <param name="deleteFiles">Whether crash dump files are deleted after copying or not.</param>
        /// <returns>true if crash dumps were found, false if not.</returns>
        public bool GetCrashDumps(string destinationDir, bool retrieveAllFiles = false, bool deleteFiles = false)
        {
            var crashDumpPaths = new List<string>(new string[] 
                { "/data/tombstones/", "/data/anr/", "/data/system/dropbox/" });
            bool crashDumpsFound = false;

            try
            {
                foreach (string crashDumpPath in crashDumpPaths)
                {
                    var fileEntries = new List<RemoteFileInfo>();

                    foreach (var foundFile in GetFileSystemItems(crashDumpPath))
                    {
                        if (!foundFile.IsDirectory)
                        {
                            if (crashDumpPath == "/data/anr/")
                            {
                                if (foundFile.Name == "traces.txt")
                                {
                                    // add traces.txt only when size changes
                                    if (TABInterface.AnrTracesFileSize == 0 ||
                                        TABInterface.AnrTracesFileSize != foundFile.Length)
                                    {
                                        fileEntries.Add(foundFile);
                                    }

                                    TABInterface.AnrTracesFileSize = foundFile.Length;
                                }
                                // skip bugreport file
                                else if (foundFile.Name != "traces.txt.bugreport")
                                {
                                    fileEntries.Add(foundFile);
                                }
                            }
                            else
                            {
                                fileEntries.Add(foundFile);
                            }
                        }
                    }

                    if (fileEntries.Count > 0)
                    {
                        // if this is the first time, only save the file names so that we know if new ones appear
                        // or just delete them if wanted
                        if (!TABInterface.crashDumpFilesChecked && !retrieveAllFiles)
                        {
                            foreach (var fileEntry in fileEntries)
                            {
                                // delete file if necessary (NOTE: crash dumps are always files not folders)
                                if (deleteFiles)
                                {
                                    File.RemoveFile(fileEntry.FullName);

                                    if (Logger.IsRecording)
                                    {
                                        Logger.AddMarkerToLogFile(String.Format("Marble deleted: {0}",
                                            fileEntry.FullName));
                                    }

                                    if (TABInterface.handledCrashDumpFiles.Contains(fileEntry.FullName))
                                    {
                                        TABInterface.handledCrashDumpFiles.Remove(fileEntry.FullName);
                                    }
                                }
                                else if (!TABInterface.handledCrashDumpFiles.Contains(fileEntry.FullName))
                                {
                                    TABInterface.handledCrashDumpFiles.Add(fileEntry.FullName);
                                }
                            }
                        }
                        else
                        {
                            var newFileEntries = new List<RemoteFileInfo>();

                            foreach (var fileEntry in fileEntries)
                            {
                                // add all files to list
                                if (retrieveAllFiles)
                                {
                                    newFileEntries.Add(fileEntry);
                                }
                                // add all new files to list
                                else if (!TABInterface.handledCrashDumpFiles.Contains(fileEntry.FullName))
                                {
                                    newFileEntries.Add(fileEntry);
                                    TABInterface.handledCrashDumpFiles.Add(fileEntry.FullName);
                                // anr/traces.txt file is an exception
                                }
                                else if (fileEntry.FullName.EndsWith("anr/traces.txt"))
                                {
                                    newFileEntries.Add(fileEntry);
                                }
                            }

                            if (newFileEntries.Count > 0)
                            {
                                destinationDir = Path.GetFullPath(destinationDir);

                                if (!Directory.Exists(destinationDir))
                                {
                                    Directory.CreateDirectory(destinationDir);
                                }

                                crashDumpsFound = true;

                                // copy files using file stream
                                foreach (var remoteFile in newFileEntries)
                                {
                                    var filePath = remoteFile.FullName;

                                    if (filePath == null) continue;

                                    var crashDumpDirName =
                                        crashDumpPath.Split(new string[] {@"/"}, StringSplitOptions.RemoveEmptyEntries)
                                            .Last();
                                    var localFilePath = Path.Combine(destinationDir, crashDumpDirName,
                                        Path.GetFileName(filePath));

                                    if (!Directory.Exists(Path.Combine(destinationDir, crashDumpDirName)))
                                    {
                                        Directory.CreateDirectory(Path.Combine(destinationDir, crashDumpDirName));
                                    }

                                    File.Pull(filePath, localFilePath);

                                    //using (var dest = new FileStream(localFilePath, FileMode.OpenOrCreate))
                                    //{
                                    //    using (var stream = File.OpenRead(filePath))
                                    //    {
                                    //        stream.CopyTo(dest);
                                    //    }
                                    //}

                                    if (Logger.IsRecording)
                                    {
                                        Logger.AddMarkerToLogFile(String.Format("Marble copied {0} to {1}", filePath,
                                            destinationDir));
                                    }

                                    // delete file if necessary (NOTE: crash dumps are always files not folders)
                                    if (deleteFiles)
                                    {
                                        File.RemoveFile(filePath);

                                        if (Logger.IsRecording)
                                        {
                                            Logger.AddMarkerToLogFile(String.Format("Marble deleted: {0}", filePath));
                                        }

                                        if (TABInterface.handledCrashDumpFiles.Contains(filePath))
                                        {
                                            TABInterface.handledCrashDumpFiles.Remove(filePath);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            catch (Exception err)
            {
                TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, String.Format("Error in GetCrashDumps: {0}", err.ToString()));
            }

            // clear first time flag
            if (!TABInterface.crashDumpFilesChecked && !retrieveAllFiles)
            {
                TABInterface.crashDumpFilesChecked = true;
            }

            return crashDumpsFound;
        }

        /// <summary>
        /// Get package information from crash dump. .txt and .gz file formats supported.
        /// </summary>
        /// <param name="filePath">Crash dump file path.</param>
        /// <returns>Package name in string if found.</returns>
        public string GetPackageFromCrashDump(string filePath)
        {
            var package = "";

            filePath = Path.GetFullPath(filePath);

            if (!System.IO.File.Exists(filePath))
            {
                return package;
            }

            if (filePath.EndsWith(".txt"))
            {
                using (var fileStream = System.IO.File.OpenRead(filePath))
                {
                    package = GetPackageFromCrashDumpFile(fileStream);
                }
            }
            else if (filePath.EndsWith(".gz"))
            {
                using (var archive = new GZipStream(System.IO.File.OpenRead(filePath), CompressionMode.Decompress))
                {
                    package = GetPackageFromCrashDumpFile(archive);
                }
            }

            return package;
        }

        /// <summary>
        /// Get package information from crash dump
        /// </summary>
        /// <param name="fileStream">Crash dump file stream.</param>
        /// <returns>Package name in string if found.</returns>
        private string GetPackageFromCrashDumpFile(Stream fileStream)
        {
            var package = "";

            using (var file = new StreamReader(fileStream))
            {
                string line;

                while ((line = file.ReadLine()) != null)
                {
                    if (line.Contains("Package:"))
                    {
                        package =
                            line.Replace("\n", "")
                                .Split(new string[] { "Package:" }, StringSplitOptions.RemoveEmptyEntries)
                                .Last();
                        break;
                    }
                }
            }

            return package;
        }

        /// <summary>
        /// Get heap dumps from process(es)
        /// </summary>
        /// <param name="processList">List of process names form which to take heap dumps If empty, dumps are taken from all processes.</param>
        /// <param name="destinationDir">Directory where to copy heap dumps.</param>
        /// <returns>true if heap dump taking succeeded, false if not.</returns>
        public bool GetHeapDumps(string[] processList, string destinationDir)
        {
            var heapDumpsTaken = false;

            try
            {
                if (processList.Length > 0)
                {
                    foreach (var activityName in processList)
                    {
                        try
                        {
                            var activity = ActivityManager.GetActivityByName(activityName);

                            if (activity == null)
                            {
                                TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, String.Format("Process: {0} not found for heap dumping!", activityName));
                            }
                            else if (!activity.IsDebuggable)
                            {
                                TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, String.Format("Process: {0} is not debuggable for heap dumping!", activityName));
                            }
                            else
                            {
                                var filePath =
                                        Path.GetFullPath(Path.Combine(destinationDir,
                                            String.Format("{0}_{1}.hprof", string.Join("_", activity.Name.Replace("/", "").Split(Path.GetInvalidFileNameChars())),
                                                DateTime.Now.ToString("yyyyMMddHHmmss"))));

                                TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, String.Format("Dumping heap from: {0} to: {1}", activityName, filePath));
                                activity.DumpHeap(filePath);
                                heapDumpsTaken = true;
                            }
                        }
                        catch (Exception)
                        {
                            TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, String.Format("Dumping heap from: {0} failed!", activityName));
                        }
                    }
                }
                else
                {
                    TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, "Dumping heap from all running processes...");

                    foreach (var activity in ActivityManager.GetActivities())
                    {
                        if (!activity.IsDebuggable)
                        {
                            continue;
                        }

                        try
                        {
                            var filePath =
                                Path.GetFullPath(Path.Combine(destinationDir,
                                    String.Format("{0}_{1}.hprof", string.Join("_", activity.Name.Replace("/", "").Split(Path.GetInvalidFileNameChars())),
                                        DateTime.Now.ToString("yyyyMMddHHmmss"))));

                            TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, String.Format("Dumping heap from: {0} to: {1}", activity.Name, filePath));
                            activity.DumpHeap(filePath);
                            heapDumpsTaken = true;
                        }
                        catch (Exception)
                        {
                            TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, String.Format("Dumping heap from: {0} failed!", activity.Name));
                        }
                    }
                }
            }
            catch (Exception e)
            {
            }

            return heapDumpsTaken;
        }

        // <summary>
        // Check RAM dumps from memory card.
        /// <param name="checkAll">Whether all ram dump files are checked or not</param>
        /// <param name="deleteRawDumps">Whether raw ram dumps are deleted (engineering build)</param>
        /// <param name="copyRawDumps">Whether raw ram dumps are copied instead of Noklog dumps (engineering build)</param>
        /// <returns>number of found ram dump files.</returns>
        public int CheckRamDumps(bool checkAll = false, bool deleteRawDumps = true, bool copyRawDumps = false)
        {
            var ramDumpfileEntries = new List<RemoteFileInfo>();
            var toBeDeletedRamDumpFileEntries = new List<RemoteFileInfo>();
            var nokLogRamDumpPaths = new List<string>(new string[] 
                { Path.Combine(File.SdCard, "logs", "upload", "Crash").Replace("\\", "/"),
                  Path.Combine(File.SdCard, "logs", "upload", "SYSTEM_TOMBSTONE").Replace("\\", "/") });
            var ramDumpFolder = Path.Combine(File.SdCard, "ramdump").Replace("\\", "/");

            // check build type
            if (!Properties.ContainsKey("ro.build.type"))
            {
                // can't determine build type, returning 0
                return 0;
            }

            // engineering build
            if (Properties["ro.build.type"] == "eng")
            {
                try
                {
                    // go through raw ramp dumps to check should we delete them
                    foreach (var foundFile in GetFileSystemItems(File.SdCard))
                    {
                        if (foundFile.IsDirectory) // dumps are folders
                        {
                            int num;
                            var isNum = int.TryParse(foundFile.Name, out num); // check that folder name is numerical 
                            if (!isNum) continue;

                            // check that it contains "load.cmm" to verify that content is RAM dump
                            // NOTE: Using Path.Combine instead of FullName, because FullName is not working at the moment with SD card paths
                            if (GetFileSystemItems(Path.Combine(foundFile.DirectoryName, foundFile.Name).Replace("\\", "/")).All(i => (i.Name != "load.cmm" && i.Name != "errfile.txt"))) continue;

                            // when raw dumps are copied just add item to list
                            if (copyRawDumps)
                            {
                                ramDumpfileEntries.Add(foundFile);
                            }
                            else
                            {
                                // check if timestamp's year is 1980, which means new ramp dump
                                // NOTE: Phone SW bug which caused this false timestamp has been fixed, but keeping this piece of code here still just in case
                                if (foundFile.LastAccessTime.Year == 1980)
                                {
                                    // touch the file so that in the next round we can possibly delete it
                                    // NOTE: Using Path.Combine instead of FullName, because FullName is not working at the moment with SD card paths
                                    ExecuteShellCommand(
                                        "touch " +
                                        Path.Combine(foundFile.DirectoryName, foundFile.Name).Replace("\\", "/"),
                                        NullOutputReceiver.Instance,
                                        TABInterface.DEFAULT_ADB_TIMEOUT);
                                }
                                    // mark folders older than 30 minutes to be deleted
                                else if (foundFile.LastAccessTime < DateTime.Now.AddMinutes(-30))
                                {
                                    toBeDeletedRamDumpFileEntries.Add(foundFile);
                                }
                            }
                        }
                    }
                }
                catch (AdbException err)
                {
                    Console.Error.Write("ADB error in CheckRamDumps: " + err.ToString());
                    return 0;
                }

                if (!copyRawDumps)
                {
                    if (deleteRawDumps)
                    {
                        // delete raw ramp dump folders
                        foreach (var fileEntry in toBeDeletedRamDumpFileEntries)
                        {
                            // NOTE: Using Path.Combine instead of FullName, because FullName is not working at the moment with SD card paths
                            var ramDumpPath = Path.Combine(fileEntry.DirectoryName, fileEntry.Name).Replace("\\", "/");

                            File.RemoveDirectory(ramDumpPath);

                            if (Logger.IsRecording)
                            {
                                Logger.AddMarkerToLogFile(String.Format("Marble deleted: {0}", ramDumpPath));
                            }
                        }
                    }

                    // go through NokLog ram dump folders
                    foreach (var nokLogRamDumpPath in nokLogRamDumpPaths)
                    {
                        foreach (var foundFile in GetFileSystemItems(nokLogRamDumpPath))
                        {
                            if (!foundFile.IsDirectory)
                            {
                                ramDumpfileEntries.Add(foundFile);
                            }
                        }
                    }
                }
            }
            // user build
            else if (Properties["ro.build.type"] == "user")
            {
                // go through raw ramp dumps
                foreach (var foundFile in GetFileSystemItems(File.SdCard))
                {
                    if (foundFile.IsDirectory) // dumps are folders
                    {
                        int num;
                        var isNum = int.TryParse(foundFile.Name, out num); // check that folder name is numerical 
                        if (!isNum) continue;

                        // check that it contains "load.cmm" to verify that content is RAM dump
                        // NOTE: Using Path.Combine instead of FullName, because FullName is not working at the moment with SD card paths
                        if (GetFileSystemItems(Path.Combine(foundFile.DirectoryName, foundFile.Name).Replace("\\", "/")).Any(i => (i.Name == "load.cmm" || i.Name == "errfile.txt")))
                        {
                            ramDumpfileEntries.Add(foundFile);
                        }
                    }
                }
            }

            // check also "ramdump" folder for both engineering and user build 
            foreach (var foundFile in GetFileSystemItems(ramDumpFolder))
            {
                if (!foundFile.IsDirectory)
                {
                    ramDumpfileEntries.Add(foundFile);
                }
            }

            // in the end check did we got new ram dumps
            TABInterface.newRamDumpFiles.Clear();

            if (ramDumpfileEntries.Count > 0)
            {
                foreach (var fileEntry in ramDumpfileEntries)
                {
                    // NOTE: Using Path.Combine instead of FullName, because FullName is not working at the moment with SD card paths
                    var ramDumpPath = Path.Combine(fileEntry.DirectoryName, fileEntry.Name).Replace("\\", "/");

                    // when checkAll is given all ram dumps are new
                    if (!TABInterface.handledRamDumpFiles.Contains(ramDumpPath) || checkAll)
                    {
                        TABInterface.newRamDumpFiles.Add(ramDumpPath);
                    }
                }
            }

            return TABInterface.newRamDumpFiles.Count;
        }

        /// <summary>
        /// Get new ram dump files
        /// </summary>
        /// <param name="destinationDir">Destination directory where new ram dump files will be copied.</param>
        /// <param name="deleteFiles">Whether ram dump files are deleted after copying or not.</param>
        /// <returns>true if ram dumps were copied, false if not.</returns>
        public bool GetNewRamDumps(string destinationDir, bool deleteFiles = false)
        {
            bool ramDumpsCopied = false;

            try
            {
                if (TABInterface.newRamDumpFiles.Count > 0)
                {
                    destinationDir = Path.GetFullPath(destinationDir);

                    if (!Directory.Exists(destinationDir))
                    {
                        Directory.CreateDirectory(destinationDir);
                    }

                    foreach (var filePath in TABInterface.newRamDumpFiles)
                    {
                        if (filePath == null) continue;
                        
                        //var localFilePath = Path.Combine(destinationDir, Path.GetFileName(filePath));

                        File.Pull(filePath, destinationDir);

                        //using (var dest = new FileStream(localFilePath, FileMode.OpenOrCreate))
                        //{
                        //    using (var stream = File.OpenRead(filePath))
                        //    {
                        //        stream.CopyTo(dest);
                        //    }
                        //}

                        if (Logger.IsRecording)
                        {
                            Logger.AddMarkerToLogFile(String.Format("Marble copied {0} to {1}", filePath, destinationDir));
                        }

                        // delete file/directory if necessary
                        if (deleteFiles)
                        {
                            if (File.DirectoryExists(filePath))
                            {
                                File.RemoveDirectory(filePath);
                            }
                            else
                            {
                                File.RemoveFile(filePath);
                            }

                            if (Logger.IsRecording)
                            {
                                Logger.AddMarkerToLogFile(String.Format("Marble deleted: {0}", filePath));
                            }

                            if (TABInterface.handledRamDumpFiles.Contains(filePath))
                            {
                                TABInterface.handledRamDumpFiles.Remove(filePath);
                            }
                        }
                        else
                        {
                            if (!TABInterface.handledRamDumpFiles.Contains(filePath))
                            {
                                TABInterface.handledRamDumpFiles.Add(filePath);
                            }
                        }
                    }

                    ramDumpsCopied = true;
                }
            }
            catch (Exception err)
            {
                TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, String.Format("Error in GetNewRamDumps: {0}", err.ToString()));
            }

            return ramDumpsCopied;
        }

        /// <summary>
        /// Get current port forwardings
        /// </summary>
        /// <returns>string[] of port forwardings.</returns>
        /// <exception cref="TABException"></exception>
        public string[] ListForward()
        {
            string[] portForwardings = new string[]{};

            try
            {
                portForwardings = TABInterface.RunAdbCommand(string.Format("host-serial:{0}:list-forward", this.SerialNumber)).Split(new string[] { "\r\n", "\n" }, StringSplitOptions.RemoveEmptyEntries);
            }
            catch (Exception)
            { }

            return portForwardings;
        }

        /// <summary>
        /// Check device status by checking whether system ui process is running and connection to ADB is working
        /// </summary>
        /// <returns>0 if device status is ok
        ///          1 if system ui process is not running
        ///          2 if ADB connection is not working</returns>
        public int CheckDeviceStatus()
        {
            if (ActivityManager.GetActivityByName("com.android.systemui") == null)
            {
                return 1;
            }
            else
            {
                if (!TABInterface.WaitForAdb(30))
                {
                    return 2;
                }

                try
                {
                    // check ADB connection by running ps command in shell
                    ShellCommand("ps");
                }
                catch (Exception)
                {
                    return 2;
                }

                return 0;
            }            
        }

        /// <summary>
        /// Raise ADB daemon process priority so that it won't run out of memory
        /// </summary>
        public void RaiseAdbdPriority()
        {
            var adbd = ActivityManager.GetActivityByName("/sbin/adbd");

            if (adbd != null)
            {
                try
                {
                    if ((File.Cat(string.Format("/proc/{0}/oom_score_adj", adbd.PID))[0]) != "-1000")
                    {
                        Shell.ExecuteCommand(string.Format("echo \"-17\" > /proc/{0}/oom_adj", adbd.PID));
                    }

                    Shell.ExecuteCommand(string.Format("renice -- -20 -p {0}", adbd.PID));
                }
                catch (Exception err)
                {
                    Console.Error.Write("Error in raising ADBD priority: " + err.ToString());
                }
            }
        }

        /// <summary>
        /// Waits until a device is completely booted. Device needs to be in online state in order to use this method.
        /// The remote device does the polling work; we just wait.
        /// </summary>
        /// <param name="timeout">Timeout for waiting</param>
        /// <returns>True if the device was successfully booted within the timeout value.</returns>
        public bool WaitBooted(TimeSpan timeout)
        {
            if (timeout < TimeSpan.Zero) return false;

            if (IsOnline)
            {
                string ifCommand = "if [[ $(getprop init.svc.bootanim) == stopped || ! $(getprop init.svc.bootanim) ]] && [[ $(getprop sys.boot_completed) == 1 || ! $(getprop sys.boot_completed) ]] && [[ $(getprop dev.bootcomplete) == 1 || ! $(getprop dev.bootcomplete) ]]";
                var command = string.Format("start=$(date +%s); while [ $(($(date +%s)-$start)) -le {0} ]; do {1}; then break; fi; sleep 0.5; done; {2}; then echo booted; else echo timeout; fi",
                    (int)Math.Round(timeout.TotalSeconds, 0), ifCommand, ifCommand);
                try
                {
                    var recv = new BootReceiver();
                    ExecuteShellCommand(command, recv, (int)timeout.TotalMilliseconds * 2);
                    return recv.Booted;
                }
                catch (Exception e)
                {
                    //log e
                }
            }
            return false;
        }

        /// <summary>
        /// Receiver class for handling the boot result
        /// </summary>
        private class BootReceiver : MultiLineReceiver
        {
            /// <summary>
            /// Called wheh the shell returns
            /// </summary>
            /// <param name="lines">Shell output</param>
            protected override void ProcessNewLines(string[] lines)
            {
                if (lines != null && lines.Length == 1)
                {
                    var result = lines[0].Trim().ToLower();

                    if (string.Compare(result, "booted", false) == 0)
                    {
                        Booted = true;
                    }
                    else if (string.Compare(result, "timeout", false) == 0)
                    {
                        TimedOut = true;
                    }
                }
            }

            /// <summary>
            /// Gets the value indicating whether the device was successfully booted
            /// </summary>
            public bool Booted { get; private set; }

            /// <summary>
            /// Gets the value indicating whether the timeout expired when waiting for the device to boot up.
            /// </summary>
            public bool TimedOut { get; private set; }
        }

        #endregion

        #region Logging

        /// <summary>
        /// Start logging        
        /// </summary>
        /// <param name="logFilePath">Log file path.</param>
        /// <param name="clearBuffer">Value indicating whether to clear the log before</param>
        public void StartLogging(string logFilePath, bool clearBuffer = true)
        {
            if (!Directory.Exists(Path.GetDirectoryName(logFilePath)))
            {
                Directory.CreateDirectory(Path.GetDirectoryName(logFilePath));
            }

            Logger.StartRecording(logFilePath);
            Logger.Start(LogBuffer.All, clearBuffer);
        }

        /// <summary>
        /// Stop logging
        /// </summary>
        /// <param name="clearBuffer">Value indicating whether to clear the log before</param>
        public void StopLogging(bool clearBuffer = false)
        {
            Logger.StopRecording();
            Logger.Stop(clearBuffer);
        }

        #endregion

        #region Capture

        /// <summary>
        /// Capture screen
        /// </summary>
        /// <param name="imageFilePath">Destination image file path.</param>
        /// <returns>true if actions succeeds, false if not.</returns>
        public bool Capture(string imageFilePath)
        {
            if (Directory.Exists(Path.GetDirectoryName(imageFilePath)))
            {
                Image shot = null;

                //shot = GetFrameBuffer().ToImage(); // not working yet

                try
                {
                    // NOTE: with crespo we need to use screencap process way, because framebuffer service will leave screencap process alive for unknown reason
                    if (Properties["ro.build.product"] == "crespo")
                    {
                        return GetImage(imageFilePath); // via screencap process
                    }
                    else
                    {
                        shot = CaptureScreen<Bitmap>();
                        //var rawImage = CaptureScreen(); // via madb framebuffer service

                        //if (rawImage != null)
                        //{
                        //    shot = rawImage.ToImage();
                        //}
                    }

                    if (shot != null)
                    {
                        shot.Save(imageFilePath);
                        return true;                           
                    }
                    else
                    {
                        return false;
                    }
                }
                catch (Exception err)
                {
                    Console.Error.Write("Error in Capture: " + err.ToString());
                    return false;
                }
                finally
                {
                    if (shot != null)
                    {
                        shot.Dispose();
                    }
                }
            }
            else
            {
                Console.Error.Write("Invalid image file path given in Capture!");
                return false;
            }
        }

        #endregion

        #region WithoutServer

        /// <summary>
        /// Get XML dump from the phone
        /// </summary>
        /// <param name="xmlFilePath">Destination XML file path.</param>
        /// <exception cref="TABException"></exception>
        public void GetXMLDump(string xmlFilePath)
        {
            string dumpFilePath = "/data/local/tmp/dump.xml";

            ExecuteShellCommand("uiautomator dump " + dumpFilePath, NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);

            bool FileExists = FileSystem.Exists(dumpFilePath);

            if (FileExists && Directory.Exists(Path.GetDirectoryName(xmlFilePath)))
            {
                SyncService sync = SyncService;
                if (sync != null)
                {
                    try
                    {
                        FileEntry entry = FileListingService.FindFileEntry(dumpFilePath);

                        ISyncProgressMonitor progressMonitor = new NullSyncProgressMonitor();

                        SyncResult syncResult = sync.PullFile(entry, xmlFilePath, progressMonitor);
                    }
                    catch (FileNotFoundException)
                    {
                        throw new TABException(dumpFilePath + " was not found!");
                    }
                }
                else
                {
                    throw new TABException("Unable to open sync connection!");
                }
            }
            else
            {
                throw new TABException("XML dump was not generated!");
            }
        }

        /// <summary>
        /// Touch screen
        /// </summary>
        /// <param name="x">x coordinate.</param>
        /// <param name="y">y coordinate.</param>
        /// <param name="wait">wait, how long press will be.</param>
        /// <param name="release">whether press will be released or not.</param>
        /// <param name="waifAfterRelease">wait after release.</param>
        /// <returns>true if actions succeeds, false if not.</returns>
        public bool Touch(int x, int y, int wait = 350, int waifAfterRelease = 100, bool release = true)
        {
            CheckAllowedCall("Touch");
            bool pressOK = TouchPress(x, y, wait);
            bool releaseOK = true;

            if (release)
            {
                releaseOK = TouchRelease(waifAfterRelease);
            }

            return pressOK && releaseOK;
        }

        /// <summary>
        /// Touch release command function
        /// </summary>
        /// <param name="wait">Wait after release.</param>
        /// <returns>true if actions succeeds, false if not.</returns>
        public bool TouchRelease(int wait = 100)
        {
            string commandString = "";

            if (Properties["ro.build.product"] == "crespo")
            {
                commandString = String.Join(";",
                                            baseInputCommand + " 0 2 0",
                                            baseInputCommand + " 0 0 0");
            }
            else
            {
                commandString = String.Join(";",
                                   baseInputCommand + " 1 330 0",
                                   baseInputCommand + " 0 0 0");
            }

            try
            {
                ExecuteShellCommand(commandString, NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
            }
            catch (Exception)
            {
                return false;
            }

            Thread.Sleep(wait);

            return true;

            /*
            // append command to touch command
            touchCommands.Add(commandString);

            // NOTE: Maximum number of simultaneous commands to ADB is 9
            int skip = 9;

            if (touchCommands.Count < skip)
            {
                skip = touchCommands.Count;
            }

            // execute and clear touch commands
            for (int i = 0; i < touchCommands.Count; i += skip)
            {
                if (touchCommands.Count - i < skip)
                {
                    skip = touchCommands.Count - i;
                }

                ExecuteShellCommand(String.Join(";", touchCommands.GetRange(i, skip)), NullOutputReceiver.Instance);
            }

            touchCommands.Clear();
            */
        }

        /// <summary>
        /// Perform touch action having list of coordinates (e.g swipe)
        /// </summary>
        /// <param name="values">List of x, y, wait values.</param>
        /// <returns>true if actions succeeds, false if not.</returns>
        public bool TouchAction(List<int> values)
        {
            CheckAllowedCall("TouchAction");
            bool touchOK = true;

            for (int i = 0; i < values.Count; i += 3)
            {
                try
                {
                    if (i == 0)
                    {
                        var pressOK = TouchPress(values[i], values[i + 1], values[i + 2]);

                        if (!pressOK)
                        {
                            touchOK = pressOK;
                        }
                    }
                    else
                    {
                        var moveOK = TouchMove(values[i], values[i + 1], values[i + 2]);

                        if (!moveOK)
                        {
                            touchOK = moveOK;
                        }

                        bool releaseOK = true;

                        if (i == values.Count - 3)
                        {
                            releaseOK = TouchRelease();
                        }
                        else if (i == values.Count - 4)
                        {
                            releaseOK = TouchRelease(values[i + 3]);
                        }

                        if (!releaseOK)
                        {
                            touchOK = releaseOK;
                        }                        
                    }
                }
                catch (ArgumentOutOfRangeException)
                {
                    return false;
                }
            }

            return touchOK;
        }
        
        /// <summary>
        /// Input text to focused text input field
        /// </summary>
        /// <param name="text">Text to be inputted.</param>
        public void Input(string text)
        {
            CheckAllowedCall("Input");
            ExecuteShellCommand("input text " + text, NullOutputReceiver.Instance, 60000);
        }

        /// <summary>
        /// Press back button
        /// </summary>
        public void Back()
        {
            CheckAllowedCall("Back");
            // back key code is 4
            ExecuteShellCommand("input keyevent 4", NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
        }

        #endregion

        #region "Time"

        /// <summary>
        /// Synchronizes the PC time to the device
        /// </summary>
        /// <returns>True if successfully synchronized; false otherwise</returns>
        public bool SyncPcDateTime()
        {
            return Time.SyncPcDateTime();
        }

        /// <summary>
        /// Sets the given time to the device
        /// </summary>
        /// <param name="dateTime">The time to set</param>
        /// <returns>True is successfully set; false otherwise</returns>
        public bool SetSystemDateTime(DateTime dateTime)
        {
            return Time.SetSystemDateTime(dateTime);
        }

        /// <summary>
        /// Sets the system's time zone to UTC
        /// </summary>
        public void SetUtcTimeZone()
        {
            Time.SetUtcTimeZone();
        }

        /// <summary>
        /// Gets the device system time
        /// </summary>
        /// <returns>The device system time</returns>
        public DateTime GetSystemDateTime()
        {
            return Time.GetSystemDateTime();
        }

        /// <summary>
        /// Sets the system time by keeping its current date
        /// </summary>
        /// <param name="hour">Hour</param>
        /// <param name="minute">Minute</param>
        /// <param name="second">Second</param>
        /// <returns>True is success; False otherwise</returns>
        public bool SetSystemTime(int hour, int minute, int second)
        {
            return Time.SetSystemTime(hour, minute, second);
        }

        /// <summary>
        /// Sets the system date by keeping its current time
        /// </summary>
        /// <param name="year">Year</param>
        /// <param name="month">Month</param>
        /// <param name="day">Day</param>
        /// <returns>True is success; False otherwise</returns>
        public bool SetSystemDate(int year, int month, int day)
        {
            return Time.SetSystemDate(year, month, day);
        }

        #endregion

        #region "Shell"

        /// <summary>
        /// Executes a shell command in device
        /// </summary>
        /// <param name="command">Command to execute</param>
        /// <returns>Output lines</returns>
        public string[] ShellCommand(string command)
        {
            return Shell.ExecuteCommand(command).ToArray();
        }

        #endregion

        #region "Keyguard"

        /// <summary>
        /// Disables key guard
        /// Reboots the device automatically
        /// </summary>
        /// <returns>True if successfully disabled</returns>
        public bool DisableLockScreen()
        {
            return DisableLockScreen(true);
        }

        /// <summary>
        /// Disables key guard
        /// </summary>
        /// <param name="reboot">Value indicating whether to reboot the device after disabling the key guard</param>
        /// <returns>True if successfully disabled</returns>
        public bool DisableLockScreen(bool reboot)
        {
            CheckAllowedCall("DisableLockScreen");
            var db = SqLite.Connect("/data/system/locksettings.db");
            if (db != null)
            {
                var table = db.GetTable("locksettings");

                if (table != null)
                {
                    var success = false;

                    var record = table.GetRecord("name", "lockscreen.password_type");

                    if (record != null)
                    {
                        record.SetString("value", "0");
                        success = record.GetString("value") == "0";
                    }

                    if (success)
                    {
                        record = table.GetRecord("name", "lockscreen.disabled");

                        if (record != null)
                        {
                            record.SetString("value", "1");
                            if (record.GetString("value") == "1")
                            {
                                if (reboot)
                                {
                                    Reboot();
                                    Thread.Sleep(TimeSpan.FromSeconds(10));
                                }
                                return true;
                            }
                        }
                    }
                }
            }

            return false;
        }

        #endregion

        #region "Observers"

        /// <summary>
        /// Creates a directory observer
        /// </summary>
        /// <param name="path">Directory path in the device</param>
        /// <returns>DirectoryObserver instance</returns>
        public DirectoryObserver CreateDirectoryObserver(string path, Action<DirectoryObserverEvent> handler)
        {
            return CreateDirectoryObserver(path, null, handler);
        }

        /// <summary>
        /// Creates a directory observer
        /// </summary>
        /// <param name="path">Directory path in the device</param>
        /// <param name="filter">Filename filter</param>
        /// <returns>DirectoryObserver instance</returns>
        public DirectoryObserver CreateDirectoryObserver(string path, string filter, Action<DirectoryObserverEvent> handler)
        {
            if (TestServerClient != null)
            {
                return new DirectoryObserver(TestServerClient, path, filter, handler);
            }
            throw new TABException("Directory observers can be created only when executing tests with the test server");
        }

        #endregion

    }

    #region "Screencap"

    /// <summary>
    /// Class for receiving screencap process response
    /// </summary>
    public sealed class ScreencapResponseReceiver
    {
        internal bool Success { get; private set; }
        static int receiveLength = 131072;
        TABConnection connection;
        string imageFilePath;

        /// <summary>
        /// Initializes a new instance of the <see cref="ScreencapResponseReceiver"/> class.
        /// <param name="connection">TAB connection instance</param>
        /// <param name="imageFilePath">Destination image file path.</param>
        /// </summary>
        public ScreencapResponseReceiver(TABConnection connection, string imageFilePath)
        {
            this.connection = connection;
            this.imageFilePath = imageFilePath;
            Success = false;
        }

        /// <summary>
        /// Saves the image
        /// </summary>
        private void SaveImage()
        {
            try
            {
                using (Image image = Image.FromStream(this.connection.screencapDataStream))
                {
                    this.connection.screencapDataStream.Seek(0, SeekOrigin.Begin);
                    image.Save(imageFilePath);
                }

                Success = true;
            }
            catch (Exception err)
            {
                Console.Error.Write("Error when saving image: " + err.ToString());
                Success = false;
            }
        }

        /// <summary>
        /// Execute screencap ADB command and gather response data.
        /// </summary>
        private void ExecuteCommand()
        {
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            if (!this.connection.IsOnline)
            {
                return;
            }

            try
            {
                socket.Connect(AndroidDebugBridge.SocketAddress);
                //socket.SendTimeout = maxTimeToOutputResponse;
                socket.Blocking = true;

                AdbHelper.Instance.SetDevice(socket, this.connection);

                var request = AdbHelper.Instance.FormAdbRequest("shell:screencap -p");

                if (!AdbHelper.Instance.Write(socket, request))
                {
                    throw new AdbException("failed submitting shell command");
                }

                AdbResponse resp = AdbHelper.Instance.ReadAdbResponse(socket, false);

                if (!resp.IOSuccess || !resp.Okay)
                {
                    throw new AdbException("sad result from adb: " + resp.Message);
                }

                socket.ReceiveTimeout = TABInterface.DEFAULT_ADB_TIMEOUT;
                socket.ReceiveBufferSize = receiveLength;

                var data = new byte[receiveLength];
                int count = -1;
                int index = 0;

                byte[] header = new byte[8] { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };

                while (count != 0)
                {
                    count = socket.Receive(data);

                    if (count > 0)
                    {
                        for (int i = 0; i < count; i++)
                        {
                            byte byteToWrite;

                            // end of line mark conversion needed, because ADB shell messes them up
                            if (count > i + 1 && data[i] == 0x0d && data[i + 1] == 0x0a)
                            {
                                byteToWrite = 0x0a;
                                i++;
                            }
                            else
                            {
                                byteToWrite = data[i];
                            }

                            this.connection.screencapDataStream.WriteByte(byteToWrite);

                            if (index <= 7 && byteToWrite != header[index])
                            {
                                Console.Error.Write("Invalid PNG header");
                            }

                            index++;
                        }
                    }
                }

                index = 0;

                /*
                using (StreamWriter w = File.AppendText("test.txt"))
                {
                    byte[] buffer = this.connection.screencapDataStream.GetBuffer();

                    if (buffer.Length == 0)
                    {
                        w.Write("EMPTY BYTELIST");
                    }

                    foreach (byte dataByte in buffer)
                    {
                        w.Write(dataByte.ToString() + ", ");
                    }

                    w.Write("\n");
                    w.Write("\n");
                }
                 */
            }
            catch (SocketException err)
            {
                Console.Error.Write("Socket error while receiving response: " + err.ToString());
            }
            finally
            {
                if (socket != null)
                {
                    socket.CloseNoWait();
                }
            }
        }

        /// <summary>
        /// Execute command, save the image and clear memory stream
        /// </summary>
        public void Execute()
        {
            ExecuteCommand();

            if (this.connection.screencapDataStream.Length > 0)
            {
                SaveImage();

                byte[] buffer = this.connection.screencapDataStream.GetBuffer();
                Array.Clear(buffer, 0, buffer.Length);
                this.connection.screencapDataStream.Position = 0;
                this.connection.screencapDataStream.SetLength(0);
            }
        }
    }

        #endregion

        #region "ConnectionProtection"

    /// <summary>
    /// Class for protecting connection sockets with mutex
    /// </summary>
    public static class SocketMutex
    {
        private const string MutexString = "TEST_AUTOMATION_PORT_";

        /// <summary>
        /// Enters into mutex with socket port
        /// </summary>
        /// <param name="port"></param>
        /// <returns>Mutex or null</returns>
        public static Mutex EnterMutex(int port)
        {
            Mutex mutex = null;

            //TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, "Checking mutex for port: {0}", port.ToString());

            string mutexString = String.Concat(MutexString, port.ToString());

            // check if other process has already created mutex
            if (Mutex.TryOpenExisting(mutexString, out mutex))
            {
                //TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, "Mutex already existing");
                mutex.Dispose();
                mutex = null;
            }
            else
            {
                try
                {
                    mutex = new Mutex(true, mutexString);
                    //TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, "Returning Mutex: {0}", mutex.ToString());
                }
                // in case that other process is just creating the same mutex
                catch (Exception)
                {
                    mutex = null;
                }
            }

            return mutex;
        }

        /// <summary>
        /// Frees the mutex
        /// </summary>
        /// <param name="mutex"></param>
        public static void FreeMutex(Mutex mutex)
        {
            if (mutex != null)
            {
                try
                {
                    mutex.ReleaseMutex();
                    //TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, "FreeMutex");
                    mutex.Dispose();
                }
                catch (ObjectDisposedException)
                {
                }
                catch (ApplicationException e)
                {
                }
                catch (Exception e)
                {
                    TestAutomation.Bridge.Tracing.Trace.WriteMessage(null, "FreeMutex failed: {0}", e.Message);
                }
            }
        }
    }
        #endregion
}
        #endregion

#region Protection

public static class ProcessExtensions
{
    public static bool HasParent(this Process process)
    {
        try
        {
            return process.ParentProcess() != null;
        }
        catch
        {
            return false;
        }
    }

    public static Process ParentProcess(this Process process)
    {
        int parentPid = 0;
        int processPid = process.Id;
        uint TH32CS_SNAPPROCESS = 2;

        // Take snapshot of processes
        IntPtr hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (hSnapshot == IntPtr.Zero)
        {
            return null;
        }

        PROCESSENTRY32 procInfo = new PROCESSENTRY32();

        procInfo.dwSize = (uint)Marshal.SizeOf(typeof(PROCESSENTRY32));

        // Read first
        if (Process32First(hSnapshot, ref procInfo) == false)
        {
            return null;
        }

        // Loop through the snapshot
        do
        {
            // If it's me, then ask for my parent.
            if (processPid == procInfo.th32ProcessID)
            {
                parentPid = (int)procInfo.th32ParentProcessID;
            }
        }
        while (parentPid == 0 && Process32Next(hSnapshot, ref procInfo)); // Read next

        if (parentPid > 0)
        {
            return Process.GetProcessById(parentPid);
        }
        else
        {
            return null;
        }
    }

    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern IntPtr CreateToolhelp32Snapshot(uint dwFlags, uint th32ProcessID);

    [DllImport("kernel32.dll")]
    private static extern bool Process32First(IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

    [DllImport("kernel32.dll")]
    private static extern bool Process32Next(IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

    [StructLayout(LayoutKind.Sequential)]
    private struct PROCESSENTRY32
    {
        public uint dwSize;
        public uint cntUsage;
        public uint th32ProcessID;
        public IntPtr th32DefaultHeapID;
        public uint th32ModuleID;
        public uint cntThreads;
        public uint th32ParentProcessID;
        public int pcPriClassBase;
        public uint dwFlags;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
        public string szExeFile;
    }
}

#endregion
