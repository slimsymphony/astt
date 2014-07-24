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
using System.Threading;
using System.Threading.Tasks;
using System.Web.Script.Serialization;
using TestAutomation.Bridge;
using System.Globalization;

namespace TestAutomation.Client
{
    /// <summary>
    /// Class for creating a connection to a remote scripting service
    /// </summary>
    public sealed class ScriptingServiceClient : DynamicObject
    {
        private readonly JavaScriptSerializer _serializer;
        private readonly TABConnection _tab;
        private readonly ScriptingServiceOptions _options;
        private int _port = -1;
        private static int _id;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="tab"></param>
        internal ScriptingServiceClient(TABConnection tab) : this(tab, ScriptingServiceOptions.Default)
        { }

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="tab">Device connection interface</param>
        /// <param name="options">Options for launching the service</param>
        internal ScriptingServiceClient(TABConnection tab, ScriptingServiceOptions options)
        {
            _tab = tab;
            _options = options;
            _serializer = new JavaScriptSerializer();
            ValidateOptions();
        }

        /// <summary>
        /// Validates the given options
        /// </summary>
        private void ValidateOptions()
        {
            if (_options == null)
            {
                throw new ArgumentNullException("options");
            }
            if (string.IsNullOrEmpty(_options.ActionName))
            {
                throw new ArgumentNullException("options.ActionName");
            }
            if (string.IsNullOrEmpty(_options.ComponentName))
            {
                throw new ArgumentNullException("options.ComponentName");
            }
            if (string.IsNullOrEmpty(_options.PackageName))
            {
                throw new ArgumentNullException("options.PackageName");
            }
            if (string.IsNullOrEmpty(_options.PortExtraKey))
            {
                throw new ArgumentNullException("options.PortExtraKey");
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public ScriptingServiceOptions Options
        {
            get
            {
                return _options;
            }
        }

        /// <summary>
        /// Connects to a remote scripting service
        /// </summary>
        /// <returns>True if successfully connected; False otherwise</returns>
        public bool Connect()
        {
            return Connect(true);
        }

        /// <summary>
        /// Connects to a remote scripting service
        /// </summary>
        /// <param name="installService">Value indicating whether to install the service to the device</param>
        /// <returns>True if successfully connected; False otherwise</returns>
        private bool Connect(bool installService)
        {
            if (installService)
            {
                // check do we need to stop/install
                var remoteFilePath = string.Format("/data/local/tmp/{0}", ScriptingService.ScriptingService.GetServiceName());
                if ((!_tab.File.FileExists(remoteFilePath) ||
                    (MD5.CalculateRemote(_tab, remoteFilePath) != ScriptingService.ScriptingService.GetServiceHash())) ||
                    !_tab.Packages.PackageExists(_options.PackageName))
                {
                    StopExistingScriptingService(_options.ForcePushPackage);
                    InstallScriptingService();
                }
            }

            // free previous port
            if (TABInterface.reservedScriptingPorts.ContainsKey(_port))
            {
                SocketMutex.FreeMutex(TABInterface.reservedScriptingPorts[_port]);
                TABInterface.reservedScriptingPorts.Remove(_port);
            }

            _port = _options.ListeningPort = GetPortPair();

            if (StartService())
            {
                return (_tab.CreateForward(_port, _port));
            }
            return false;
        }

        /// <summary>
        /// Stops the scripting service and removes the existing port forwardings
        /// </summary>
        /// <param name="uninstall">Value indicating whether to uninstall the service</param>
        /// <returns>True if successfully dicconnected; False otherwise</returns>
        public bool Disconnect(bool uninstall = false)
        {
            StopExistingScriptingService(uninstall);

            try
            {
                if (_port != -1 && IsConnected)
                {
                    try
                    {
                        if (IsForwarding(_port))
                        {
                            return _tab.RemoveForward(_port);
                        }
                    }
                    catch (AdbException)// err)
                    {
                        //Console.Error.Write("ADB exception in RemoteForward: " + err.ToString());
                        return false;
                    }
                }

                return true;
            }
            finally
            {
                if (TABInterface.reservedScriptingPorts.ContainsKey(_port))
                {
                    SocketMutex.FreeMutex(TABInterface.reservedScriptingPorts[_port]);
                    TABInterface.reservedScriptingPorts.Remove(_port);
                }

                // finally clear port so that we check the port again in next scripting service start
                _port = -1;
            }
        }

        /// <summary>
        /// Invokes a remote method with given name and parameters
        /// </summary>
        /// <param name="methodName">Name of the method to invoke</param>
        /// <param name="args">Parameters for the method</param>
        /// <returns>Method's return value</returns>
        public object Invoke(string methodName, params object[] args)
        {
            var data = new InvokeData() { id = _id, method = methodName, @params = args };
            _id++;
            return Invoke(data);
        }

        /// <summary>
        /// Invokes a remote method with given invoke data
        /// </summary>
        /// <param name="data">Data containing needed information for the invoke</param>
        /// <returns>Method's return value</returns>
        private object Invoke(InvokeData data)
        {
            var respStr = Send(data);
            var resp = GetResponse(respStr);

            if (resp.error != null)
            {
                throw new Exception("\"" + data.method + "\" : " + resp.error);
            }
            if (data.id != resp.id)
            {
                throw new Exception("IDs of sent and received messages do not match");
            }

            return resp.result;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public object toggleAirplaneMode()
        {
            bool value = !(bool)this.Invoke("checkAirplaneMode");
            return toggleAirplaneMode(value);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public object toggleAirplaneMode(bool value)
        {
            if (int.Parse(_tab.Properties["ro.build.version.sdk"]) >= 17)
            {
                _tab.ShellCommand(value ? "settings put global airplane_mode_on 1; am broadcast -a android.intent.action.AIRPLANE_MODE --ez state true" :
                    "settings put global airplane_mode_on 0; am broadcast -a android.intent.action.AIRPLANE_MODE --ez state false");
                return value;
            }

            return (bool)this.Invoke(new InvokeData() { id = _id, method = "toggleAirplaneMode", @params = new object[] { value } });
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="result"></param>
        /// <returns></returns>
        public override bool TryGetMember(GetMemberBinder binder, out object result)
        {
            result = new DynamicInvoker((args) =>
            {
                var data = new InvokeData() { id = _id, method = binder.Name, @params = args };
                _id++;
                return Invoke(data);
            });
            return true;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="args"></param>
        /// <param name="result"></param>
        /// <returns></returns>
        public override bool TryInvokeMember(InvokeMemberBinder binder, object[] args, out object result)
        {
            var data = new InvokeData() { id = _id, method = binder.Name, @params = args };
            _id++;
            result = Invoke(data);
            return true;
        }

        /// <summary>
        /// Deserializes the methos response from its Json presentation
        /// </summary>
        /// <param name="json">Json containing all the response data</param>
        /// <returns>Derialized object</returns>
        private ServiceResponse GetResponse(string json)
        {
            return _serializer.Deserialize<ServiceResponse>(json);
        }

        /// <summary>
        /// Creates the request data from InvokeData object
        /// </summary>
        /// <param name="data">InvokeData object</param>
        /// <returns>Request data in byte array</returns>
        private byte[] CreateRequest(InvokeData data)
        {
            var json = _serializer.Serialize(data).Replace("@params", "params") + "\n";
            return Encoding.Default.GetBytes(json);
        }

        /// <summary>
        /// Sends the invoke request to remote host and returns the response in Json format
        /// </summary>
        /// <param name="data">InvokeData object</param>
        /// <returns>The response in Json format</returns>
        private string Send(InvokeData request)
        {
            // check connection before sending
            if (IsConnected)
            {
                var req = CreateRequest(request);

                using (var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                {
                    socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, new LingerOption(true, 0));
                    socket.Connect(IPAddress.Loopback, _port);
                    socket.Blocking = true;

                    var sent = socket.Send(req);

                    if (sent != req.Length)
                    {
                        throw new Exception("Failed to send to socket");
                    }

                    var message = new List<byte>();
                    var buffer = new byte[1024 * 4];
                    var read = -1;
                    var messageSize = 0;
                    var loopCounter = 0;

                    while ((message.Count == 0 || message.Count - 4 < messageSize) && read != 0)
                    {
                        // To make sure that we are not stuck into infinite loop
                        loopCounter++;
                        if (loopCounter > 10)
                        {
                            throw new Exception("Loop counter exceeded 10. Problem while receiving JSON data");
                        }

                        read = socket.Receive(buffer);

                        if (read > 4)
                        {
                            if (messageSize == 0)
                            {
                                messageSize = BitConverter.ToInt32(buffer, 0);
                            }
                            message.AddRange(buffer.Take(read));
                        }
                        else if (read == -1)
                        {
                            throw new Exception("Failed to read from socket");
                        }
                        else
                        {
                            return "{\"error\":\"No valid data received from Marble RPC service. Only " + read.ToString() +" bytes received. \",\"id\":0,\"result\":null}";
                        }

                        // Check that do we have received enough data
                        if (message.Count >= messageSize)
                            read = 0;
                        else
                        {
                            // Poll some time to see if next chunk is available
                            for (var i = 0; i < 20; i++)
                            {
                                Thread.Sleep(1);
                                read = socket.Available;
                                if (read > 0)
                                    break;
                            }
                        }
                    }
                    return Encoding.UTF8.GetString(message.Skip(4).ToArray(), 0, message.Count - 4);
                    // skip the length information 4 bytes
                }
            }

            return "";
        }

        /// <summary>
        /// Starts a scripting service, and stops existing instances of the service if found any
        /// </summary>
        /// <returns>True if started successfully; False otherwise</returns>
        private bool StartScriptingService()
        {
            StopExistingScriptingService(false);
            InstallScriptingService();
            return StartService();
        }

        /// <summary>
        /// Stops existing instances of the service if found any
        /// </summary>
        private void StopExistingScriptingService(bool uninstall)
        {
            if (!_tab.IsOnline) return;

            var stop = _tab.ActivityManager.GetActivityByName(_options.PackageName) != null;

            if (stop)
            {
                try
                {
                    var scriptingServiceOptions = ScriptingServiceOptions.Default;
                    scriptingServiceOptions.ActionName = Constants.SCRIPTING_SERVICE_KILL_ACTION_NAME;
                    _tab.ActivityManager.StartActivity(scriptingServiceOptions.CreateKillCommand(), null);
                }
                catch { }

                for (var i = 0; i < 5; i++)
                {
                    var lastPid = -1;

                    var service = _tab.ActivityManager.GetActivityByName(_options.PackageName);

                    if (service == null) break;

                    if (service.PID != lastPid) //The process list might not have updated yet
                    {
                        lastPid = service.PID;

                        // kill the service if force stop won't work
                        if (i == 3)
                        {
                            service.Kill();
                        }
                        else
                        {
                            service.ForceStop();
                        }
                    }
                    else
                    {
                        Thread.Sleep(100);
                    }
                }
            }
            // remove installed package
            if (uninstall && _tab.Packages.PackageExists(_options.PackageName))
            {
                _tab.Packages.UninstallPackage(_options.PackageName);
            }
        }

        /// <summary>
        /// Starts the scripting service
        /// </summary>
        /// <returns>True is successfully started; False otherwise</returns>
        private bool StartService()
        {
            return StartService(TimeSpan.FromMilliseconds(5000));
        }

        /// <summary>
        /// Starts the scripting service
        /// </summary>
        /// <param name="timeout">Timeout value of how long to wait the service to get up</param>
        /// <returns>True is successfully started; False otherwise</returns>
        private bool StartService(TimeSpan timeout)
        {
            try
            {
                _tab.ActivityManager.StartActivity(_options.ToString(), null);

                var start = DateTime.Now;

                while (!IpHelper.GetReservedRemotePorts(_tab).Contains(_port) && DateTime.Now.Subtract(start) < timeout)
                {
                    Thread.Sleep(200);
                }
                return IpHelper.GetReservedRemotePorts(_tab).Contains(_port);
            }
            catch { }
            return false;
        }

        /// <summary>
        /// Installs the scripting service
        /// </summary>
        private void InstallScriptingService()
        {
            using (var stream = ScriptingService.ScriptingService.GetServiceStream())
            {
                // remove already installed package
                if (_tab.Packages.PackageExists(_options.PackageName))
                {
                    _tab.Packages.UninstallPackage(_options.PackageName);
                }

                // install package
                _tab.Packages.DoInstallPackage(stream, ScriptingService.ScriptingService.GetServiceName(), ScriptingService.ScriptingService.GetServiceHash(), _options.ForcePushPackage, true);
            }
        }

        /// <summary>
        /// Checks if the remote host is available
        /// </summary>
        public bool IsConnected
        {
            get
            {
                // with invalid port just return
                if (_port == -1 || !_tab.ActivityManager.ActivityExists(_options.PackageName))
                {
                    return false;
                }

                using (var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                {
                    socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, new LingerOption(true, 0));

                    try
                    {
                        socket.Connect(IPAddress.Loopback, _port);
                        return true;
                    }
                    catch (SocketException) { }
                }

                return false;
            }
        }

        /// <summary>
        /// Gets a list of reserved local ports
        /// </summary>
        /// <returns>A list of reserved local ports</returns>
        private List<int> GetReservedLocalPorts()
        {
            var ports = new List<int>();
            foreach (var connection in IPGlobalProperties.GetIPGlobalProperties().GetActiveTcpConnections())
            {
                var port = connection.LocalEndPoint.Port;
                if (!ports.Contains(port))
                {
                    ports.Add(port);
                }
            }

            return ports;
        }

        /// <summary>
        /// Gets a port number which is available in both, local and remote machine/device
        /// </summary>
        /// <returns>A port number which is available in both, local and remote machine/device</returns>
        private int GetPortPair()
        {
            return GetPortPair(Constants.DEFAULT_SCRIPTING_PORT_RANGE_START, Constants.DEFAULT_SCRIPTING_PORT_RANGE_END);
        }

        /// <summary>
        /// Gets a port number which is available in both, local and remote machine/device
        /// </summary>
        /// <param name="fromValue">The value from which to start looking</param>
        /// <param name="toValue">The value to which stop looking</param>
        /// <returns>A port number which is available in both, local and remote machine/device</returns>
        private int GetPortPair(int fromValue, int toValue)
        {
            if (fromValue < toValue)
            {
                var reservedLocal = GetReservedLocalPorts();
                var reservedRemote = IpHelper.GetReservedRemotePorts(_tab);

                for (int i = fromValue; i < toValue; i++)
                {
                    if (!reservedLocal.Contains(i) && !reservedRemote.Contains(i) && !TABInterface.reservedScriptingPorts.ContainsKey(i))
                    {
                        // protect reserved socket with mutex
                        Mutex socketMutex = SocketMutex.EnterMutex(i);

                        if (socketMutex != null)
                        {
                            TABInterface.reservedScriptingPorts[i] = socketMutex;
                            return i;
                        }
                    }
                }
            }

            return -1;
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
            foreach (string portForward in _tab.ListForward())
            {
                if (portForward.Contains(localPort.ToString()))
                {
                    return true;
                }
            }

            return false;
        }
    }

    /// <summary>
    /// Class to be used for json seriliazer in order to pass the method invoke information
    /// </summary>
    internal class InvokeData
    {
        /// <summary>
        /// Message id (Java type casing due to receiving end)
        /// </summary>
        public int id { get; set; }

        /// <summary>
        /// Method name (Java type casing due to receiving end)
        /// </summary>
        public string method { get; set; }

        /// <summary>
        /// Method parameters (Java type casing due to receiving end)
        /// </summary>
        public object[] @params { get; set; }
    }

    /// <summary>
    /// Class for deserializing the method response from host
    /// </summary>
    internal class ServiceResponse
    {
        /// <summary>
        /// Error message if any (Java type casing due to receiving end)
        /// </summary>
        public string error { get; set; }

        /// <summary>
        /// Message id matching to the invoke request (Java type casing due to receiving end)
        /// </summary>
        public int id { get; set; }

        /// <summary>
        /// Invoke result (Java type casing due to receiving end)
        /// </summary>
        public object result { get; set; }
    }

}
