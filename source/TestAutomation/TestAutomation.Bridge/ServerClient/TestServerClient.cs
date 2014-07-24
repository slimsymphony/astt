using Managed.Adb;
using Managed.Adb.Exceptions;
using System;
using System.Collections.Generic;
using System.Dynamic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Web.Script.Serialization;
using TestAutomation.Bridge;

namespace TestAutomation.Client
{
    /// <summary>
    /// Different possible states of the connection from client to the server
    /// </summary>
    public enum ConnectionState
    {
        Connected,
        FailedToConnect,
        UserDisconnected,
        HostExited,
        UsbDisconnected,
        Initial
    }

    /// <summary>
    /// Class for creating a connection to a remote test server
    /// </summary>
    public sealed class TestServerClient : DynamicObject, IDisposable
    {
        #region "Private fields"

        private Socket m_eventSocket = null;
        
        private Thread m_eventLoop = null;
        private Thread m_eventDispatcher = null;
        private Thread m_serverThread = null;
        
        private Lazy<List<RPCMessage>> m_eventQueue = null;

        private JavaScriptSerializer m_serializer = null;

        private TABConnection m_tab = null;

        private ManualResetEvent m_events = null;
        private ManualResetEvent m_serverStarted = null;

        private TestAutomationServerListener m_serverOutput = null;

        private TestAutomationServerPushProgress m_serverPushProgress = null;

        private TestAutomationServerOptions m_options = null;

        private ConnectionState m_connectionState;

        private RemoteFileSystem m_fileSystem = null;

        private int m_port = -1;

        private bool m_eventsEnabled = false;
        private bool m_eventsLooping = false;
        private bool m_disposed = false;
        private bool m_userStoppedServer = false;

        private Keyboard m_keyboard;
        private Albumset m_galleryAlbumset;
        private Album m_galleryAlbum;

        private object m_keyboardLocker = new object();
        private object m_galleryLocker = new object();

        private event TestAutomationServerStartedHandler m_serverStartedE;

        private event TestAutomationServerExitHandler m_serverExitedE;

        private event AccessibilityEventHandler m_uiEventE;

        private List<Action<DirectoryObserverEvent>> m_directoryObservers;

        private Dictionary<string, List<string>> m_observerDirectories;

        #endregion

        #region "Constructors"

        /// <summary>
        /// Class constructor
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="tab">Connection to the device under test</param>
        internal TestServerClient(TABConnection tab) : this(tab, TestAutomationServerOptions.Default)
        { }

        /// <summary>
        /// Class constructor
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="tab">Connection to the device under test</param>
        /// <param name="options">Options how to configure the server</param>
        internal TestServerClient(TABConnection tab, TestAutomationServerOptions options)
        {
            m_connectionState = ConnectionState.Initial;
            m_tab = tab;
            m_options = options;
            ValidateOptions();
            m_serializer = new JavaScriptSerializer();
            m_eventQueue = new Lazy<List<RPCMessage>>(() => new List<RPCMessage>());
            m_events = new ManualResetEvent(false);
            m_serverStarted = new ManualResetEvent(false);
            m_fileSystem = new RemoteFileSystem(this);
            m_serverOutput = new TestAutomationServerListener(m_serverStarted);
            m_serverPushProgress = new TestAutomationServerPushProgress();
            m_directoryObservers = new List<Action<DirectoryObserverEvent>>();
            m_observerDirectories = new Dictionary<string, List<string>>();
            StartEventDispatcher();
        }

        #endregion

        #region "Public properties"

        /// <summary>
        /// Gets the state of the connection
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        public ConnectionState ConnectionState 
        {
            get
            {
                CheckDisposed();

                return m_connectionState;
            }
        }

        /// <summary>
        /// Gets the options for the server use
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        public TestAutomationServerOptions Options 
        { 
            get 
            {
                CheckDisposed();

                return m_options; 
            } 
        }

        /// <summary>
        /// Gets RPC access to the filesystem implementation in the test server
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        public RemoteFileSystem FileSystem 
        {
            get
            {
                CheckDisposed();

                return m_fileSystem;
            }
        }

        /// <summary>
        /// Gets the device start time
        /// 
        /// @Since 1.0.0.0
        /// </summary>
        public DateTime? DeviceStartTime { get; private set; }

        /// <summary>
        /// Enable or disable remote GUI events
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        public bool EnableRemoteEvents
        {
            get
            {
                CheckDisposed();

                return m_eventsEnabled;
            }
            set
            {
                CheckDisposed();

                if (value && !m_eventsEnabled)
                {
                    if (!m_eventsLooping && ConnectionState == Client.ConnectionState.Connected)
                    {
                        StartListeningForRemoteEvents();
                    }
                    m_eventsEnabled = true;
                }
                else
                {
                    if (m_eventsLooping)
                    {
                        StopEventListener();
                    }
                    m_eventsEnabled = false;
                }
            }
        }

        /// <summary>
        /// Gets the latest information about the keyboard
        /// </summary>
        public Keyboard Keyboard
        {
            get
            {
                lock (m_keyboardLocker)
                {
                    return m_keyboard;
                }
            }
            private set
            {
                lock (m_keyboardLocker)
                {
                    m_keyboard = value;
                    if (!m_keyboard.KeyboardOn)
                    {
                        m_keyboard.Keys = new List<Key>();
                    }
                }
            }
        }

        /// <summary>
        /// Gets the latest information about the gallery albumset view
        /// </summary>
        public Albumset GalleryAlbumset
        {
            get
            {
                lock (m_galleryLocker)
                {
                    return m_galleryAlbumset;
                }
            }
            private set
            {
                lock (m_galleryLocker)
                {
                    m_galleryAlbumset = value;
                }
            }        
         }

        /// <summary>
        /// Gets the latest information about the gallery album view
        /// </summary>
        public Album GalleryAlbum
        {
            get
            {
                lock (m_galleryLocker)
                {
                    return m_galleryAlbum;
                }
            }
            private set
            {
                lock (m_galleryLocker)
                {
                    m_galleryAlbum = value;
                }
            }
        }


        #endregion

        #region "Private properties"

        /// <summary>
        /// Checks if the device is still being connected via ADB. TODO: Better implementation for this is needed.
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        private bool IsConnectedViaAbd
        {
            get
            {
                try
                {
                    //just call the remote device some way...
                    IpHelper.GetReservedRemotePorts(m_tab);
                    return true;
                }
                catch (Exception)
                {
                    return false;
                }
            }
        }

        /// <summary>
        /// Checks if the connection to the device can be still estabished
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        public bool IsConnected
        {
            get
            {
                // with invalid port just return
                if (m_port == -1)
                {
                    return false;
                }

                using (Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                {
                    try
                    {
                        socket.Connect(IPAddress.Loopback, m_port);
                        //Is connected + the process is alive: in the case of uiautomator process is killed, the port forwarder still 
                        //claims the socket connection to be valid
                        return m_tab.ActivityManager.ActivityExists(Constants.UI_AUTOMATOR_PROCESS_NAME);
                        //TODO: we should check our PID for the uiautomator and compare that
                    }
                    catch (SocketException) { }
                    finally
                    {
                        socket.CloseNoWait();
                    }
                }

                return false;
            }
        }

        #endregion

        #region "Public Events"

        /// <summary>
        /// Fired when pushing of server archive to the device is progressing
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        public event TestAutomationServerPushProgressHandler ServerPushProgress
        {
            add
            {
                CheckDisposed();

                m_serverPushProgress.Progress += value;
            }
            remove
            {
                CheckDisposed();

                m_serverPushProgress.Progress -= value;
            }
        }

        /// <summary>
        /// Fired on every server trace
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        public event TestAutomationServerTraceHandler ServerTrace
        {
            add
            {
                CheckDisposed();

                m_serverOutput.OnTrace += value;
            }
            remove
            {
                CheckDisposed();

                m_serverOutput.OnTrace -= value;
            }
        }

        /// <summary>
        /// Fired when the test server has started
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        public event TestAutomationServerStartedHandler ServerStarted
        {
            add
            {
                CheckDisposed();

                m_serverStartedE += value;
            }
            remove
            {
                CheckDisposed();

                m_serverStartedE -= value;
            }
        }

        /// <summary>
        /// Fired when the test server has stopped/Terminated
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        public event TestAutomationServerExitHandler ServerExited
        {
            add
            {
                CheckDisposed();

                m_serverExitedE += value;

                //if (TABInterface.reservedServerPorts.ContainsKey(m_port))
                //{
                //    SocketMutex.FreeMutex(TABInterface.reservedServerPorts[m_port]);
                //    TABInterface.reservedServerPorts.Remove(m_port);
                //}
            }
            remove
            {
                CheckDisposed();

                m_serverExitedE -= value;
            }
        }

        /// <summary>
        /// Fired on every GUI update in the device under test
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        public event AccessibilityEventHandler UiEvent
        {
            add
            {
                CheckDisposed();

                m_uiEventE += value;
            }
            remove
            {
                CheckDisposed();

                m_uiEventE -= value;
            }
        }

        #endregion

        #region "Public methods"

        /// <summary>
        /// Disposes the object: disconnect the connection, and and frees all the unmanaged resources
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        public void Dispose()
        {
            CheckDisposed();

            if (!m_disposed)
            {
                Disconnect(true);
                m_events.Dispose();
                m_events = null;
                m_serverStarted.Dispose();
                m_serverStarted = null;
                m_disposed = true;
            }
        }

        /// <summary>
        /// Creates a connection/reconnects to the server in a device
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="startServer">Value indicating whether to re-start the server</param>
        /// <returns>True if successfully connected/reconnected</returns>
        public bool Connect()
        {
            CheckDisposed();

            DeviceStartTime = GetDeviceStartTime();

            var startServer = false;

            //We are conencting at the first time or we have lost the connection due to server crash of reset
            if (ConnectionState == ConnectionState.Initial || ConnectionState == ConnectionState.HostExited)
            {
                startServer = true;
            }

            //User has called Disconnect
            else if (ConnectionState == ConnectionState.UserDisconnected)
            {
                //User did also stop the server
                if (m_userStoppedServer)
                {
                    startServer = true;
                }
            }

            //Usb cable has been removed
            else if (ConnectionState == ConnectionState.UsbDisconnected)
            {
                //and according to options, usb disconnect should not stop the server process (--nohup -option)
                //Currently it seems that even with --nohup - option, the OS at device side breaks the listening socket
                //of the server, which makes is impossible to reconnect to device, the the same server instance after reconnecting
                //the usb
                if (m_options.ShutDownOnUsbDisconnect)
                {
                    startServer = true;
                }
            }

            var started = true;

            if (startServer)
            {
                //Let's ask for a new server port only at initial state
                //if (ConnectionState == ConnectionState.Initial)
                //{
                m_port = GetPortPair(Constants.DEFAULT_SERVER_PORT_RANGE_START, Constants.DEFAULT_SERVER_PORT_RANGE_END);
                    //}
                started = StartRemoteServer();
            }
            //Server OK and port forwarding succeeded
            if (started && m_port != -1 && PortForward())
            {
                //Events have been enabled before the initial connect, or we're reconnecting, and this is the current value
                if (EnableRemoteEvents)
                {
                    StartListeningForRemoteEvents();
                }
                m_connectionState = IsConnected ? ConnectionState.Connected : ConnectionState.FailedToConnect;
            }

            if (ConnectionState == ConnectionState.Connected)
            {
                RegisterDirectoryObservers();
                return true;
            }
            return false;
        }

        /// <summary>
        /// Disconnects from the server in a device (stops listening for the events)
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="stopServer">Stops the process running the remote server (this is recommneded)</param>
        /// <returns>True if successfully disconnected</returns>
        public bool Disconnect(bool stopServer, bool forced = false)
        {
            CheckDisposed();

            StopEventListener();

            if ((forced || (IsConnectedViaAbd && IsConnected)) && stopServer)
            {
                StopRemoteServer();
                m_userStoppedServer = true;
            }

            m_connectionState = ConnectionState.UserDisconnected;
            
            try
            {
                bool disconnectOk = true;

                // remove forward if port is defined
                if (m_port != -1)
                {
                    disconnectOk = RemoveForward();
                }

                // FIXME: We should clear possible lingering port forwardings
                return disconnectOk;
            }
            finally
            {
                if (TABInterface.reservedServerPorts.ContainsKey(m_port))
                {
                    SocketMutex.FreeMutex(TABInterface.reservedServerPorts[m_port]);
                    TABInterface.reservedServerPorts.Remove(m_port);
                }

                // finally clear port so that we check the port again in next server start
                m_port = -1;
            }
        }

        /// <summary>
        /// Waits for an event which satisfies the given predicate method/delegate
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="match">Predicate method/delegate</param>
        /// <param name="timeout">Maximum period of time to wait for a given condition to be satisfied</param>
        /// <returns>True if the given condition was satisfied in the given time period</returns>
        public bool WaitForEvent(Predicate<AccessibilityEvent> match, int timeout)
        {
            CheckDisposed();
            CheckConnected();

            var eventReceived = false;

            var wasEnabled = EnableRemoteEvents;

            if (!wasEnabled)
            {
                EnableRemoteEvents = true;
            }

            using (ManualResetEvent received = new ManualResetEvent(false))
            {
                var handler = new AccessibilityEventHandler((ae) =>
                {
                    if (match.Invoke(ae))
                    {
                        eventReceived = true;
                        try
                        {
                            received.Set();
                        }
                        //catch (ThreadAbortException)
                        //{
                        //    Thread.ResetAbort();
                        //    received.Set();
                        //}
                        catch (ObjectDisposedException)
                        {
                            // NOTE: This may occur when WaitForEvent is triggered from IronPython thread, but doesn't cause any actions
                        }
                    }
                });

                UiEvent += handler;

                received.WaitOne(timeout);

                UiEvent -= handler;
            }

            if (!wasEnabled)
            {
                EnableRemoteEvents = false;
            }

            return eventReceived;
        }

        /// <summary>
        /// Waits for an certain type of event, for a certain period of time
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="eventTypes">Type of an event to wait for</param>
        /// <param name="timeout">Maximum time to wait for the event</param>
        /// <param name="event">The event that was fired; null if no event fired withing the given time period</param>
        /// <returns>True if the event was fired; false otherwise</returns>
        public bool WaitForEventType(EventType eventType, int timeout, out AccessibilityEvent @event)
        {
            CheckDisposed();
            CheckConnected();

            List<AccessibilityEvent> temp;
            if (WaitForEventTypeSequence(new EventType[] { eventType }, timeout, out temp))
            {
                if (temp != null && temp.Count == 1)
                {
                    @event = temp[0];
                    return true;
                }
            }

            @event = null;
            return false;
        }

        /// <summary>
        /// Waits for certain event sequence, for certain period of time
        /// </summary>
        /// <param name="eventTypes">Event sequence in the order the events are expected to occur</param>
        /// <param name="timeout">Maximum time to wait for the events</param>
        /// <param name="events">The events that were fired; null in case all the expected events were not fired</param>
        /// <returns>True if the events were fired; false otherwise</returns>
        public bool WaitForEventTypeSequence(ICollection<EventType> eventTypes, int timeout, out List<AccessibilityEvent> events)
        {
            CheckDisposed();
            CheckConnected();

            var eventSequenceToWait = new Lazy<List<EventType>>(() =>
                {
                    return new List<EventType>(eventTypes);
                });

            var _events = new List<AccessibilityEvent>();

            var eventsReceived = false;

            var wasEnabled = EnableRemoteEvents;

            if (!wasEnabled)
            {
                EnableRemoteEvents = true;
            }

            using (ManualResetEvent received = new ManualResetEvent(false))
            {
                var handler = new AccessibilityEventHandler((ae) =>
                {
                    if (eventSequenceToWait.Value.IndexOf(ae.EventType) == 0)
                    {
                        _events.Add(ae);
                        eventSequenceToWait.Value.RemoveAt(0);
                    }
                    if (eventSequenceToWait.Value.Count == 0)
                    {
                        eventsReceived = true;
                        received.Set();
                    }
                });
                
                UiEvent += handler;

                received.WaitOne(timeout);

                UiEvent -= handler;
            }

            if (!wasEnabled)
            {
                EnableRemoteEvents = false;
            }
            
            events = _events != null ? _events : null;
            return eventsReceived;
        }

        /// <summary>
        /// Adds a directory observer action into the subscription list
        /// </summary>
        /// <param name="observer">The observer action</param>
        internal void AddDirectoryObserver(Action<DirectoryObserverEvent> observer)
        {
            if (observer != null)
            {
                m_directoryObservers.Add(observer);
            }
        }

        /// <summary>
        /// Registers all the directory observers to the server (from cache)
        /// </summary>
        private void RegisterDirectoryObservers()
        {
            if (m_directoryObservers.Count > 0)
            {
                m_observerDirectories.Keys.ToList().ForEach(guid =>
                    {
                        m_observerDirectories[guid].ForEach(path =>
                            {
                                ((dynamic)this).registerDirectoryObserver(path, guid);
                            });
                    });
            }
        }

        /// <summary>
        /// Registers and caches a remote directory observer by guid.
        /// Observer requests are cached locally in case of server shuts down and 
        /// Requests need to be re-registered at server ramp up.
        /// </summary>
        /// <param name="path">Directory to start observing</param>
        /// <param name="guid">Observer guid</param>
        /// <returns>True in case of successfull registration, or if cached; false otherwise</returns>
        internal bool RegisterDirectoryObserver(string path, string guid)
        {
            if (!m_observerDirectories.ContainsKey(guid))
            {
                m_observerDirectories.Add(guid, new List<string>());
            }

            m_observerDirectories[guid].Add(path);

            if (ConnectionState == ConnectionState.Connected)
            {
                return ((dynamic)this).registerDirectoryObserver(path, guid);
            }
            return true; //we just need to assume this will be succesfull once we (re)connect
        }

        /// <summary>
        /// Unregisters a remote directory observer by guid; clears it also from the cache
        /// </summary>
        /// <param name="path">Directory being observed</param>
        /// <param name="guid">Observer guid</param>
        /// <returns>True in case of successfull removal; false otherwise</returns>
        internal bool UnRegisterDirectoryObserver(string path, string guid)
        {
            if (m_observerDirectories.ContainsKey(guid))
            {
                m_observerDirectories[guid].Remove(path);
            }
            if (ConnectionState == ConnectionState.Connected)
            {
                return ((dynamic)this).unregisterDirectoryObserver(path, guid);
            }
            return true;
        }

        /// <summary>
        /// Removes a directory observer action from the subscription list
        /// </summary>
        /// <param name="observer">The observer action</param>
        internal void RemoveDirectoryObserver(Action<DirectoryObserverEvent> observer)
        {
            if (observer != null)
            {
                m_directoryObservers.Remove(observer);
            }
        }

        #region "Dynamic methods"

        /// <summary>
        /// Does the dynamic invoking from remote server
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="binder">Binder which provides the method name of the dynamic call</param>
        /// <param name="args">Arguments for the method</param>
        /// <param name="result">Object</param>
        /// <returns>Always true</returns>
        public override bool TryInvokeMember(InvokeMemberBinder binder, object[] args, out object result)
        {
            CheckDisposed();
            //CheckConnected();
            result = RemoteInvoke(Constants.TEST_SERVER_CLASS_NAME, binder.Name, args);
            return true;
        }

        /// <summary>
        /// Returns a delegate for invoking from remote server. This is done as such due to IronPython's inability to distinguish 
        /// a dynamic property getter and dynamic method
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="binder">Binder which provides the method name of the dynamic call</param>
        /// <param name="result">A delegate for invoking from remote server</param>
        /// <returns>Always true</returns>
        public override bool TryGetMember(GetMemberBinder binder, out object result)
        {
            if (m_tab.DisAllowedBinderNames.Any(s => binder.Name.Contains(s)))
            {
                throw new Exception(String.Format("Disallowed server level binder: {0}", binder.Name));
            }
            CheckDisposed();
            //CheckConnected();
            result = new DynamicInvoker((args) =>
            {
                return RemoteInvoke(Constants.TEST_SERVER_CLASS_NAME, binder.Name, args);
            });
            return true;
        }

        #endregion

        #endregion

        #region "Private methods"

        #region "Validation"

        /// <summary>
        /// Validates the given options
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        private void ValidateOptions()
        {
            if (m_options == null)
            {
                throw new ArgumentNullException("options");
            }
            if (string.IsNullOrEmpty(m_options.ClassName))
            {
                throw new ArgumentNullException("options.ClassName");
            }
            if (string.IsNullOrEmpty(m_options.EntryMethodName))
            {
                throw new ArgumentNullException("options.EntryMethodName");
            }
            if (string.IsNullOrEmpty(m_options.PackageName))
            {
                throw new ArgumentNullException("options.PackageName");
            }
            if (string.IsNullOrEmpty(m_options.LocalArchiveLocation))
            {
                throw new ArgumentNullException("options.LocalArchiveLocation");
            }
        }
        
        /// <summary>
        /// Throws ObjectDisposedException if calling an already disposed object
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        private void CheckDisposed()
        {
            if (m_disposed)
            {
                throw new ObjectDisposedException(GetType().Name);
            }
        }

        /// <summary>
        /// Throws Exception if trying RPC when test server is not running
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        private void CheckConnected()
        {
            if (m_connectionState != Client.ConnectionState.Connected)
            {
                throw new Exception("Not connected to the test server");
            }
        }

        #endregion

        #region "Server push"

        /// <summary>
        /// Pushes a server archive to a remote device. Compares file sizes and pushes only if
        /// sizes of the files differ
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <returns>Synch result</returns>
        private bool PushServerToDevice()
        {
            return PushServerToDevice(false);
        }

        /// <summary>
        /// Pushes a server archive to a remote device. Compares file sizes if not in force mode, and pushes only if
        /// sizes of the files differ
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="force">If set true, will overwrite an existing server archive</param>
        /// <returns>true if server push succeeded or correct server already in device, otherwise false</returns>
        private bool PushServerToDevice(bool force)
        {
            var archiveFile = Path.GetFileName(m_options.LocalArchiveLocation);
            var remoteLocation = Constants.TEST_SERVER_REMOTE_PATH + archiveFile;

            var push = false;

            if (m_tab.File.FileExists(remoteLocation))
            {
                if (force || MD5.CalculateRemote(m_tab, remoteLocation) !=
                    TestServer.TestServer.GetServerHash())
                {
                    push = true;
                }
            }
            else
            {
                push = true;
            }

            if (!push) return true;

            using (var stream = TestServer.TestServer.GetServerStream())
            {
                m_tab.SyncService.PushStream(stream, remoteLocation);
            }

            return m_tab.File.FileExists(remoteLocation);
        }

        #endregion

        #region "Server management"

        /// <summary>
        /// Called when uiautomator process ends at the remote end: process crashed, usb diconnecect, phone reboots/resets, or
        /// client Disconnect is called with 'stopServer' -flag set true. This also fires the ServerExited event
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        private void OnServerExit()
        {
            if (IsConnectedViaAbd) //Better way of checking this? This causes an exception when usb is disconnected, and we simple catch the exception
            {
                m_connectionState = ConnectionState.HostExited;
                RemoveForward();
            }
            else
            {
                m_connectionState = ConnectionState.UsbDisconnected;
                RemoveForward();
            }

            //Event listener thread has probably already stopped at this point, but just in 
            //case we check (it stops when host disconnects)
            if (m_eventsLooping)
            {
                StopEventListener();
            }
            
            //Finally the we fire the event
            if (m_serverExitedE != null)
            {
                m_serverExitedE();
            }
        }

        /// <summary>
        /// Fires the ServerStarted event
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        private void OnServerStart()
        {
            if (m_serverStartedE != null)
            {
                m_serverStartedE();
            }
        }

        /// <summary>
        /// Closes down the server process
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <returns>True in case of successfull closing; otherwise false</returns>
        private bool CloseRemoteServer()
        {
            bool closeSuccessful = false;

            if (IsConnectedViaAbd && IsConnected)
            {
                // run kill in server level
                try
                {
                    ((dynamic)this).kill();
                }
                catch (MissingMethodException) { }
            }

            // loop to check whether uiautomator process died
            for (int i = 0; i < 5; i++)
            {
                if (m_tab.ActivityManager.GetActivityByName(Constants.UI_AUTOMATOR_PROCESS_NAME) == null)
                {
                    closeSuccessful = true;
                    break;
                }
                else
                {
                    // sleep for a while before next check
                    Thread.Sleep(200);
                }
            }

            return closeSuccessful;
        }

        /// <summary>
        /// Stops the remote server processes in a brutal manner
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        private void StopRemoteServer()
        {
            // kill uiautomator process if it's still alive
            if (!CloseRemoteServer())
            {
                Activity uiautomator = null;

                for (int i = 0; i < 50; i++)
                {
                    uiautomator = m_tab.ActivityManager.GetActivityByName(Constants.UI_AUTOMATOR_PROCESS_NAME);

                    if (uiautomator != null)
                    {
                        uiautomator.Kill();
                        // sleep for a while before next kill try
                        Thread.Sleep(100);
                    }
                }
            }

            if (m_serverThread != null && m_serverThread.IsAlive)
            {
                m_serverThread.Abort();
            }
        }

        /// <summary>
        /// Starts the test server by:
        /// 1) pushing the server arhive to the device (if in force push mode, or if otherwise the file is not in synch with the local file)
        /// 2) starting the server via uiautomator
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <returns>True is server is started successfully</returns>
        private bool StartRemoteServer()
        {
            var success = PushServerToDevice(m_options.ForcePushArchive);

            if (success)
            {
                m_serverStarted.Reset();
                m_serverOutput.Reset();

                var args = string.Format("-e port {0} -e root {1}", m_port, m_tab.IsRooted);
                var keepAlive = m_options.ShutDownOnUsbDisconnect ? "" : "--nohup";
                var archive = Path.GetFileName(m_options.LocalArchiveLocation);
                var package = m_options.PackageName;
                var @class = m_options.ClassName;
                var entry = m_options.EntryMethodName;

                var cmd = string.Format("uiautomator runtest {0} -c {1}.{2}#{3} {4} {5}", archive, package, @class, entry, keepAlive, args);

                m_serverThread = new Thread(new ThreadStart(() =>
                    {
                        try
                        {
                            m_tab.ExecuteShellCommand(cmd, m_serverOutput, TABInterface.INFINITE_ADB_TIMEOUT); //this blocks the thread until server stops
                        }
                        catch (ThreadAbortException)
                        {
                            Thread.ResetAbort();
                        }
                        // FIXME: What to do when ADB connection breaks?
                        catch (AdbException)
                        { }
                        finally
                        {
                            OnServerExit();
                        }
                    })) { IsBackground = true };

                m_serverThread.Start();
                m_serverStarted.WaitOne(Constants.TEST_SERVER_START_TIMEOUT);

                if (m_serverOutput.Success)// && m_serverOutput.ListeningPort == m_port)
                {
                    OnServerStart();
                    return true;
                }
                else
                {
                    throw new TABException("Unable to start TA server process!");
                }
            }

            throw new Exception("Unable to push TA server to device!");
        }

        #endregion

        #region "Ports"

        /// <summary>
        /// Does the port forwarding from local machine to the remote device
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <returns>True when succesfully forwarded the port</returns>
        private bool PortForward()
        {
            if (!IsForwarding(m_port))
            {
                return m_tab.CreateForward(m_port, m_port);
            }

            return true;
        }

        /// <summary>
        /// Removed the exiting port forwarding. Will throw an exception when there is no active forwarding.
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <returns>True of successfully removed the forwarding</returns>
        private bool RemoveForward()
        {
            if (IsForwarding(m_port))
            {
                try
                {
                    return m_tab.RemoveForward(m_port);
                }
                catch (Exception err)
                {
                    Console.Error.Write("Exception in RemoteForward: " + err.ToString());
                    return false;
                }
            }

            return true;
        }

        /// <summary>
        /// Check port forwarding
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="localPort">local socket port</param>
        /// <returns>True if port forwarding enabled, False if not.</returns>
        private bool IsForwarding(int localPort)
        {
            foreach (string portForward in m_tab.ListForward())
            {
                if (portForward.Contains(localPort.ToString()))
                {
                    return true;
                }
            }

            return false;
        }

        /// <summary>
        /// Gets a port number which is available in both, local and remote machine/device
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <returns>A port number which is available in both, local and remote machine/device</returns>
        private int GetPortPair()
        {
            return GetPortPair(Constants.DEFAULT_SERVER_PORT_RANGE_START, Constants.DEFAULT_SERVER_PORT_RANGE_END);
        }

        /// <summary>
        /// Gets a port number which is available in both, local and remote machine/device
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="fromValue">The value from which to start looking</param>
        /// <param name="toValue">The value to which stop looking</param>
        /// <returns>A port number which is available in both, local and remote machine/device</returns>
        private int GetPortPair(int fromValue, int toValue)
        {
            if (fromValue < toValue)
            {
                var reservedLocal = GetReservedLocalPorts();
                var reservedRemote = IpHelper.GetReservedRemotePorts(m_tab);

                for (int i = fromValue; i < toValue; i++)
                {
                    if (!reservedLocal.Contains(i) && !reservedRemote.Contains(i) && !TABInterface.reservedServerPorts.ContainsKey(i))
                    {
                        // protect reserved socket with mutex
                        Mutex socketMutex = SocketMutex.EnterMutex(i);

                        if (socketMutex != null)
                        {
                            TABInterface.reservedServerPorts[i] = socketMutex;
                            return i;
                        }
                    }
                }
            }

            return -1;
        }

        /// <summary>
        /// Gets a list of reserved local ports
        ///
        /// @Since      1.0.0.0
        /// </summary>
        /// <returns>A list of reserved local ports</returns>
        private List<int> GetReservedLocalPorts()
        {
            var ports = new List<int>();
            //foreach (var listener in IPGlobalProperties.GetIPGlobalProperties().GetActiveTcpListeners())
            foreach (var connection in IPGlobalProperties.GetIPGlobalProperties().GetActiveTcpConnections())
            {
                //var port = listener.Port;
                var port = connection.LocalEndPoint.Port;
                if (!ports.Contains(port))
                {
                    ports.Add(port);
                }
            }

            return ports;
        }

        #endregion

        #region "Remote event handling"

        /// <summary>
        /// Starts the event dispatcher thread
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        private void StartEventDispatcher()
        {
            m_eventDispatcher = new Thread(new ThreadStart(DoEventDispatching)) { IsBackground = true };
            m_eventDispatcher.Start();
        }

        /// <summary>
        /// Dispatches an event to event queue, and nofifies the queue reader
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="eventMessage">Event message</param>
        private void DispatchEvent(RPCMessage eventMessage)
        {
            if (eventMessage != null)
            {
                m_eventQueue.Value.Add(eventMessage);
                m_events.Set();
            }
        }

        /// <summary>
        /// Gets the first (FIFO) event from event queue, and removes it after returning it. This method blocks until there are messages in
        /// the queue to read
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <returns>The first (FIFO) event from event queue</returns>
        private RPCMessage GetNextEventFromQueue()
        {
            RPCMessage eventMessage = null;

            while (m_eventQueue.Value.Count == 0)
            {
                m_events.Reset();
                m_events.WaitOne();
            }

            try
            {
                eventMessage = m_eventQueue.Value.First();
                m_eventQueue.Value.RemoveAt(0);
            }
            catch (IndexOutOfRangeException)
            {
                eventMessage = null;
            }

            return eventMessage;
        }

        /// <summary>
        /// The event dispatcher loop
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        private void DoEventDispatching()
        {
            while (true)
            {
                var msg = GetNextEventFromQueue(); //blocks until there are events in the queue
                if (msg != null && msg.MessageType == MessageType.Event)
                {
                    OnRPCEvent(DeserializeRPCEvent(msg.Json));
                }
            }
        }

        /// <summary>
        /// Starts listening for remote events from the event socket
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        private void StartListeningForRemoteEvents()
        {
            if (m_eventsLooping)
            {
                return;
            }

            var rpcRequest = new RPCInvoke() { 
                ClassName = Constants.TEST_SERVER_CLASS_NAME, 
                MethodName = Constants.TEST_SERVER_EVENT_SUBSCRIPTION, 
                Args = new object[] { } 
            };
            
            var data = m_serializer.Serialize(rpcRequest);
            
            var message = new RPCMessage(
                MessageType.MethodInvoke, 
                MessageCounter.GetNextTransactionId(), 
                (uint)data.Length, 
                false, 
                0, 
                data);

            //This is the one and only socket which can send this request, and it cannot be used inside a using block (cannot be disposed)
            m_eventSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            LingerOption lo = new LingerOption(true, 0);
            m_eventSocket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, lo);
            m_eventSocket.Connect(IPAddress.Loopback, m_port);
            m_eventSocket.ReceiveTimeout = TABInterface.DEFAULT_ADB_TIMEOUT;
            m_eventSocket.ReceiveBufferSize = 1024 * 1024;
            m_eventSocket.Blocking = true;

            //No response for event subscription expected; maybe there should be...?
            var sent = m_eventSocket.Send(message.GetBytes(), SocketFlags.None);

            if (sent != message.MessageLength)
            {
                m_eventSocket.Close();
                throw new Exception("Failed to send remote events subscription message to the remote host");
            }

            var respMessage = ReceiveMessage(m_eventSocket, message.TransactionId);

            m_eventSocket.ReceiveTimeout = 0; // The default value is 0, which indicates an infinite time-out period. Specifying -1 also indicates an infinite time-out period.

            if (respMessage == null || !m_serializer.Deserialize<RPCResponse>(respMessage.Json).Result.Equals(true))
            {
                m_eventSocket.Close();
                throw new Exception("Failed to subscribe events from the remote device");
            }

            m_eventLoop = new Thread(new ThreadStart(() =>
                {
                    try
                    {
                        m_eventsLooping = true;

                        while (true)
                        {
                            var @event = ReceiveMessage(m_eventSocket, 0); //blocking call
                            DispatchEvent(@event);
                        }
                    }
                    catch (ThreadAbortException)
                    {
                        Thread.ResetAbort();
                    }
                    //This block will be called when the main thread closes the socket. This is the way to end this thread, in which
                    //the read from socket is blocking
                    catch (Exception) { }
                    finally
                    {
                        if (m_eventSocket != null)
                        {
                            m_eventSocket.Close();
                        }
                        m_eventsLooping = false;
                    }
                })) { IsBackground = true };
            
            m_eventLoop.Start();
        }

        /// <summary>
        /// Stops the event listener thread
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        private void StopEventListener()
        {
            if (m_eventLoop != null && m_eventLoop.IsAlive && m_eventSocket != null)
            {
                //this causes the event listener thread to exit the loop as the blocking socket read stops.
                //WE DO NOT USE thread abort here: never ever
                m_eventSocket.Close();
                m_eventSocket.Dispose();
                m_eventSocket = null;
            }
            m_eventsLooping = false;
        }

        /// <summary>
        /// Finds a correct event handler for a generic remote event
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="eventArgs">The actual event args</param>
        private void OnRPCEvent(object eventArgs)
        {
            if (eventArgs != null)
            {
                if (eventArgs is AccessibilityEvent)
                {
                    var ae = eventArgs as AccessibilityEvent;
                    if (ae.EventType == EventType.TYPE_NOTIFICATION_STATE_CHANGED && ae.ContentDescription == Keyboard.DESCRIPTION)
                    {
                        try
                        {
                            if (ae.Text != null && ae.Text.Count > 0 && ae.Text[0] != null)
                            {
                                var keyboard = m_serializer.Deserialize<Keyboard>(ae.Text[0]);
                                if (keyboard != null)
                                {
                                    Keyboard = keyboard;
                                }
                            }
                        }
                        catch { }
                    }
                    else if (ae.EventType == EventType.TYPE_NOTIFICATION_STATE_CHANGED && ae.ContentDescription == Albumset.DESCRIPTION)
                    {
                        try
                        {
                            if (ae.Text != null && ae.Text.Count > 0 && ae.Text[0] != null)
                            {
                                if (ae.Text[0].StartsWith("{\"Albumset\":"))
                                {
                                    // strip the Albumset tag to make it serializable
                                    var gallery = m_serializer.Deserialize<Albumset>(ae.Text[0].Substring(12, ae.Text[0].Length - 13));
                                    if (gallery != null)
                                    {
                                        GalleryAlbumset = gallery;
                                        GalleryAlbum = null;
                                    }
                                }
                                else if (ae.Text[0].StartsWith("{\"Album\":"))
                                {
                                    // strip the Album tag
                                    var gallery = m_serializer.Deserialize<Album>(ae.Text[0].Substring(9, ae.Text[0].Length - 10));
                                    if (gallery != null)
                                    {
                                        GalleryAlbum = gallery;
                                        GalleryAlbumset = null;
                                    }
                                }
                            }
                        }
                        catch { }
                    }
                    else if (m_uiEventE != null)
                    {
                        if (DeviceStartTime.HasValue)
                        {
                            ae.TimeStamp = DeviceStartTime.Value.AddMilliseconds(ae.EventTime).ToLocalTime();
                        }
                        m_uiEventE(ae);
                    }
                }
                else if (eventArgs is DirectoryObserverEvent && m_directoryObservers.Count > 0)
                {
                    var doe = eventArgs as DirectoryObserverEvent;
                    BroadcastDirectoryEvent(doe);
                }
            }
        }

        /// <summary>
        /// Broadcasts a directory observer event to all of the subscribers
        /// </summary>
        /// <param name="devent">The directory observer event</param>
        private void BroadcastDirectoryEvent(DirectoryObserverEvent devent)
        {
            Parallel.ForEach(m_directoryObservers.ToList(), (observer) =>
                {
                    observer.Invoke(devent);
                });
        }

        /// <summary>
        /// Deserializes an event from it's json presentation
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="json">Event json</param>
        /// <returns>Event object; null if target type is not found from this Application domain</returns>
        private object DeserializeRPCEvent(string json)
        {
            if (!string.IsNullOrEmpty(json))
            {
                //We actually have json in json; the first json explains the the type of secondary json
                RPCEvent _event = m_serializer.Deserialize<RPCEvent>(json);

                Type eventType = _event.GetEventType();

                if (eventType != null)
                {
                    return m_serializer.Deserialize(_event.EventArgs, eventType);
                }
            }
            //Event's type is unknown
            return null;
        }

        #endregion

        #region "Time"

        /// <summary>
        /// Gets the time the device was started
        /// </summary>
        /// <returns>The time the device was started</returns>
        private DateTime? GetDeviceStartTime()
        {
            var startTime = m_tab.GetProperty(Constants.DEVICE_START_TIME_TAG);

            if (!string.IsNullOrEmpty(startTime))
            {
                double timestamp;
                if (double.TryParse(startTime, out timestamp))
                {
                    return new DateTime(1970, 1, 1, 0, 0, 0).AddMilliseconds(timestamp).ToLocalTime();
                }
            }

            return null;
        }

        #endregion

        #region "Socket receive"

        /// <summary>
        /// Receives any type of message from a given, open socket. Handles messages which come in multiple chunks.
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="socket">Open socket</param>
        /// <param name="expectedTransactionId">Transaction ID, which we expect from incoming message</param>
        /// <returns>Incoming message, merged to one  message if received in multiple chunks</returns>
        private RPCMessage ReceiveMessage(Socket socket, ushort expectedTransactionId)
        {
            var jsonBuilder = new StringBuilder();
            uint? expectedDataLength = null;
            MessageType? messageType = null;
            var received = 0;
            var disconnected = false;
            var packetIndex = -1;

            //The message (especially display xml dumps) might come in several chunks
            while (true)
            {
                //Each starts with fixed length header
                var headerBuffer = new byte[Constants.RPC_MESSAGE_HEADER_LENGTH];

                int read = socket.Receive(headerBuffer, headerBuffer.Length, SocketFlags.Partial);

                if (read < headerBuffer.Length)
                {
                    if (!IsConnected)
                    {
                        //We got disconnected during receiving the message
                        disconnected = true;
                        break;
                    }

                    throw new Exception(string.Format("Expected header data (length of {0}); got {1}",
                        Constants.RPC_MESSAGE_HEADER_LENGTH, read));
                }

                RPCMessageHeader header;

                if (!RPCMessageHeader.TryGetFromBytes(headerBuffer, out header))
                {
                    throw new Exception(string.Format("Incorrect header data received: {0}",
                        BitConverter.ToString(headerBuffer, 0, read)));
                }

                if (header.TransactionId != expectedTransactionId)
                {
                    throw new Exception(string.Format("Message or partial message with unexpected transaction ID received: expected {0}; got {1}", 
                        expectedTransactionId, header.TransactionId));
                }

                var chunkLength = header.TotalChunkLength;

                var dataBuffer = new byte[chunkLength];

                if ((read = socket.Receive(dataBuffer, (int)chunkLength, SocketFlags.Partial)) >= 0)
                {
                    received += read;
                }

                //We didn't get all the data we needed
                if (read < header.TotalChunkLength)
                {
                    var remaining = header.TotalChunkLength - read;

                    while (remaining > 0)
                    {
                        var tempBuffer = new byte[remaining];
                        var remainingRead = socket.Receive(tempBuffer, (int)remaining, SocketFlags.Partial);
                        Array.Copy(tempBuffer, 0, dataBuffer, read, remainingRead);
                        remaining -= remainingRead;
                        
                        /* increase received data variables */
                        received += remainingRead;
                        read += remainingRead;
                    }
                }

                //This should be just one package, but the read was no complete
                if ((header.TotalDataLength < chunkLength) && (read < header.TotalDataLength))
                {
                    if (!IsConnected)
                    {
                        disconnected = true;
                        break;
                    }
                }
                //Read is less than a max packaet size and this is not the final package
                else if ((read < chunkLength) && header.Continue && (received < header.TotalDataLength))
                {
                    if (!IsConnected)
                    {
                        disconnected = true;
                        break;
                    }
                }
                //Responses sent in multiple chunks must have a rolling index number for chunks
                packetIndex++;

                if (header.Index != packetIndex)
                {
                    throw new Exception(string.Format("Expected packet chink with index {0}; got {1}", packetIndex, header.Index));
                }

                var response = RPCMessage.FromBytes(header, dataBuffer, read);

                if (!expectedDataLength.HasValue)
                {
                    expectedDataLength = response.TotalDataLength;
                }

                if (!messageType.HasValue)
                {
                    messageType = response.MessageType;
                }
                else if (messageType.Value != response.MessageType)
                {
                    throw new Exception(string.Format("Variation in message types of partial message chunks"));
                }

                jsonBuilder.Append(response.Json);

                //We're done
                if (!response.Continue && (received == header.TotalDataLength))
                {
                    break;
                }
            }

            if (!disconnected)
            {
                var json = jsonBuilder.ToString();

                if (expectedDataLength != null && expectedDataLength < json.Length)
                {
                    throw new Exception(string.Format("Expected {0} bytes of data; got {1}", expectedDataLength, json.Length));
                }

                return new RPCMessage(messageType.Value, expectedTransactionId, (uint)json.Length, false, 0, json);
            }

            return null;
        }

        #endregion

        #endregion

        #region "Internal methods"

        /// <summary>
        /// Does the actual RCP to the remote device
        /// 
        /// @Since      1.0.0.0
        /// </summary>
        /// <param name="className">Name of the class from which to invoke the method</param>
        /// <param name="methodName">Name of the method which to invoke</param>
        /// <param name="args">Arguments for the method to be invoked</param>
        /// <returns>Return value from the invoke</returns>
        internal object RemoteInvoke(string className, string methodName, object[] args)
        {
            CheckDisposed();

            //1. First we serialize the invoke information
            var rpc = new RPCInvoke() { 
                MethodName = methodName, 
                ClassName = className, 
                Args = args 
            };
            
            string data = m_serializer.Serialize(rpc);

            //2. Then we create a packet contaning the data
            var message = new RPCMessage(
                MessageType.MethodInvoke, 
                MessageCounter.GetNextTransactionId(), 
                (uint)data.Length, 
                false, 
                0, 
                data);

            using (Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                try
                {
                    LingerOption lo = new LingerOption(true, 0);
                    socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, lo);
                    socket.Connect(IPAddress.Loopback, m_port);
                    socket.ReceiveBufferSize = Constants.RPC_MAX_PACKET_SIZE * 10;
                    socket.ReceiveTimeout = 10000; // default socket timeout 10 seconds
                    socket.Blocking = true;

                    int sent = socket.Send(message.GetBytes(), SocketFlags.None);

                    if (sent != message.MessageLength)
                    {
                        if (!IsConnected)
                        {
                            //We got disconnected during the send
                            return null;
                        }
                    }

                    var respMessage = ReceiveMessage(socket, message.TransactionId);

                    if (respMessage != null)
                    {
                        var resp = m_serializer.Deserialize<RPCResponse>( respMessage.Json);

                        if (resp.Error != null)
                        {
                            throw new Exception(resp.Error);
                        }

                        return resp.Result;
                    }
                }
                catch (SocketException)
                {
                    if (!IsConnected)
                    {
                        return null;
                    }
                }
                catch (Exception)
                {
                    throw;
                }
                finally
                {
                    socket.Close();
                }
                
                return null;
            }
        }

        #endregion

        #region "Receivers"

        /// <summary>
        /// Class for listening the test server's printfs
        /// </summary>
        private class TestAutomationServerListener : IShellOutputReceiver
        {
            private Regex m_serverOk;
            private Regex m_portRegex;
            private ManualResetEvent m_serverStarted;

            /// <summary>
            /// Class constructor
            /// </summary>
            /// <param name="serverStarted">Reset event which is to be signaled when the server is started</param>
            public TestAutomationServerListener(ManualResetEvent serverStarted)
            {
                m_serverOk = new Regex(@"(SERVER=)(OK|ERROR)", RegexOptions.Compiled);
                m_portRegex = new Regex(@"(PORT=)([0-9]+)", RegexOptions.Compiled);
                ListeningPort = -1;
                m_serverStarted = serverStarted;
            }

            public void Reset()
            {
                ListeningPort = -1;
                Success = false;
            }

            /// <summary>
            /// Event that is fired on every trace message coming from the test server
            /// </summary>
            public event TestAutomationServerTraceHandler OnTrace;

            /// <summary>
            /// Broadcasts the event
            /// </summary>
            /// <param name="trace">Trace message</param>
            private void OnTraceReceived(string trace)
            {
                if (!string.IsNullOrEmpty(trace) && OnTrace != null)
                {
                    OnTrace(trace);
                }
            }

            /// <summary>
            /// The port the server starts actually listening
            /// </summary>
            public int ListeningPort { get; private set; }

            /// <summary>
            /// value indcating whether the test server started successfully
            /// </summary>
            public bool Success { get; private set; }

            /// <summary>
            /// Shell output is redirected here. We parse the incoming trace from raw data
            /// </summary>
            /// <param name="data">String data in raw bytes</param>
            /// <param name="offset">Offset</param>
            /// <param name="length">Length of the string</param>
            public void AddOutput(byte[] data, int offset, int length)
            {
                var line = Encoding.Default.GetString(data, offset, length).TrimEnd('\r', '\n');

                if (!Success)
                {
                    var matchStatus = m_serverOk.Match(line);
                    if (matchStatus.Success)
                    {
                        if (string.Compare(matchStatus.Groups[2].Value, "OK") == 0)
                        {
                            Success = true;
                            m_serverStarted.Set();
                        }
                    }

                    var matchPort = m_portRegex.Match(line);
                    if (matchPort.Success)
                    {
                        ListeningPort = int.Parse(matchPort.Groups[2].Value);
                    }
                }
                else
                {
                    OnTraceReceived(line);
                }
            }

            /// <summary>
            /// Not in use
            /// </summary>
            public void Flush() { }

            /// <summary>
            /// Not in use
            /// </summary>
            public bool IsCancelled { get { return false; } }
        }

        /// <summary>
        /// Class for broadcasting the progress of pushing the server archive to te device
        /// </summary>
        private class TestAutomationServerPushProgress : ISyncProgressMonitor
        {
            private DateTime m_start;
            private long m_total;
            private long m_sent;

            /// <summary>
            /// Fired 1 - N times to indicate the progress of pushing the server archive to te device
            /// </summary>
            public event TestAutomationServerPushProgressHandler Progress;

            /// <summary>
            /// Time took to psuh the server archive to the device
            /// </summary>
            public TimeSpan TransferTime { get; private set; }

            /// <summary>
            /// Not in use
            /// </summary>
            public bool IsCanceled { get { return false; } }

            /// <summary>
            /// Called to inform about length of the next data chunk to push
            /// </summary>
            /// <param name="work">Length of the next data chunk to push</param>
            public void Advance(long work)
            {
                m_sent += work;
                OnProgress();
            }

            /// <summary>
            /// Called when the push action is starting to inform about the total length of data to be pushed
            /// </summary>
            /// <param name="totalWork">Total length of data to be pushed</param>
            public void Start(long totalWork)
            {
                m_total = totalWork;
                m_start = DateTime.Now;
            }

            /// <summary>
            /// Not in use
            /// </summary>
            /// <param name="source"></param>
            /// <param name="destination"></param>
            public void StartSubTask(string source, string destination) { }

            /// <summary>
            /// Called when the pusch action is completed/stopped
            /// </summary>
            public void Stop()
            {
                TransferTime = DateTime.Now.Subtract(m_start);
            }

            /// <summary>
            /// Fires the event to inform about the push action progress
            /// </summary>
            private void OnProgress()
            {
                if (m_total > 0 && Progress != null)
                {
                    float progress = ((float)(m_sent) / (float)m_total) * (float)100.0;
                    Progress((int)Math.Round(progress, 0), (m_sent), m_total);
                }
            }
        }

        #endregion
    }
}
