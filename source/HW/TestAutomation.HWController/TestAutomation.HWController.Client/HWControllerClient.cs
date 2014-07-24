using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Management;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Reflection;
using System.Text;
using System.Threading;
using log4net;
using TestAutomation.HWController.Shared;

namespace TestAutomation.HWController.Client
{
    public class HWControllerClient : MarshalByRefObject, IHWController
    {
        #region Enumerations

        public enum Connection
        {
            USB,
            TCP
        }

        #endregion

        #region Private Members

        private int testUnit;
        private string serverAddress;
        private string serialPort;
        private int serverPort;
        private ILog log;
        private TcpClient tcpClient;
        private MfSocket mfSocket;
        private static HWControllerClient instance;
        private const int defaultReadTimeout = 5000;

        #endregion

        #region Properties

        public static HWControllerClient Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new HWControllerClient();
                    instance.testUnit = 1;
                    instance.log = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
                }
                return instance;
            }
        }

        public int TestUnitNumber
        {
            get { return this.testUnit; }
            set { this.testUnit = value; }
        }

        public string ServerAddress
        {
            get { return this.serverAddress; }
            set { this.serverAddress = value; }
        }

        public ILog Logger
        {
            get { return this.log; }
            set { this.log = value; }
        }

        public Connection ConnectionMode
        {
            get; set;
        }

        #endregion

        #region Constructor(s)

        private HWControllerClient()
        {
        }

        #endregion

        #region Public Methods

        public void InitTcpMode(string serverAddress, int serverPort = 8888)
        {
            this.serverAddress = serverAddress;
            this.serverPort = serverPort;
            this.log.Debug("HWControllerClient in TCP communication mode: " + this.serverAddress + ":" + this.serverPort);
            this.ConnectionMode = Connection.TCP;
        }

        public string InitUsbMode(string serialPort = "")
        {
            this.ConnectionMode = Connection.USB;
            if (string.IsNullOrEmpty(serialPort))
            {
                var devices = this.DetectDevices();
                if (devices.Count > 0)
                    this.serialPort = devices[0];
                return this.serialPort;
            }
            else
                this.serialPort = serialPort;

            this.log.Debug("HWControllerClient in USB serial communication mode: " + this.serialPort);
            return string.Empty;
        }

        public IPStatus PingServer(string address = "")
        {
            if (string.IsNullOrEmpty(address))
                address = this.serverAddress;
            Ping pingSender = new Ping();
            PingOptions options = new PingOptions();

            // Use the default Ttl value which is 128, 
            // but change the fragmentation behavior.
            options.DontFragment = true;

            // Create a buffer of 32 bytes of data to be transmitted. 
            string data = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
            byte[] buffer = Encoding.ASCII.GetBytes(data);
            int timeout = 120;
            PingReply reply = pingSender.Send(address, timeout, buffer, options);
            if (reply.Status == IPStatus.Success)
            {

                this.log.Info("Address: " + reply.Address);
                this.log.Info("RoundTrip time: " + reply.RoundtripTime);
                this.log.Info("Time to live: " + reply.Options.Ttl);
                this.log.Info("Don't fragment: " + reply.Options.DontFragment);
                this.log.Info("Buffer size: " + reply.Buffer.Length);
            }
            else
            {
                this.log.Error(reply.Status.ToString());
            }

            return reply.Status;
        }

        public string PingUsb()
        {
            string resp = this.GetApplicationVersion();
            if (!string.IsNullOrEmpty(resp))
            {
                return "OK";
            }
            return "Error";
        }

        public void Initialize()
        {
            this.ConnectBatteryCharger();
            this.ConnectPower();
            this.InsertSIM2();
            this.InsertMemoryCard();
            this.DisconnectHeadset();
            this.ConnectUSBMain();
            this.ConnectUSBRemote();
        }

        public void ConnectBatteryCharger()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void ConnectHeadset()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void ConnectPower()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void InsertSIM2()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void ConnectUSBMain()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void ConnectUSBChargerMain()
        {
            this.DisconnectUSBMain();
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void ConnectUSBRemote()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void DisconnectBatteryCharger()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void DisconnectHeadset()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void DisconnectPower()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void RemoveSIM2()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void DisconnectUSBMain()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void DisconnectUSBRemote()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void InsertMemoryCard()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void PressKeylockPowerButton(int delay)
        {
            // Pass delay so that Thread.Sleep in Netduino side does not cause read timeout in client side
            this.executeMethod(MethodBase.GetCurrentMethod().Name + ":" + delay, delay);
        }

        public void RemoveMemoryCard()
        {
            this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        /// <summary>
        /// Connect external pin (1-16)
        /// </summary>
        /// <param name="pinId"></param>
        public void ConnectExt(int pinId)
        {
            if (pinId >= 0 && pinId <= 15)
                this.executeMethod(MethodBase.GetCurrentMethod().Name + ":" + pinId);
            else
                throw new IndexOutOfRangeException("ConnectExt pins 0-15 available");
        }

        /// <summary>
        /// Disconnect external pin (1-16)
        /// </summary>
        /// <param name="pinId"></param>
        public void DisconnectExt(int pinId)
        {
            if (pinId >= 0 && pinId <= 15)
                this.executeMethod(MethodBase.GetCurrentMethod().Name + ":" + pinId);
            else
                throw new IndexOutOfRangeException("DisconnectExt pins 0-15 available");
        }

        public string GetHwStatus()
        {
            return this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public string GetApplicationVersion()
        {
            return this.executeMethod(MethodBase.GetCurrentMethod().Name);
        }

        public void Close()
        {
            this.tryCloseTcp();    
        }

        public List<string> DetectDevices()
        {
            List<string> portList = new List<string>();
            ManagementClass mc = new ManagementClass("Win32_PnPEntity");
            ManagementObjectCollection moc = mc.GetInstances();
            foreach (var mo in moc)
            {
                try
                {
                    string caption = mo["Caption"].ToString();
                    string deviceId = mo["DeviceID"].ToString();
                    if (caption.ToLower().Contains("usb serial port") &&
                        deviceId.Contains("FTDIBUS") && deviceId.Contains("MARBLEHW"))
                    {
                        int startIndex = caption.IndexOf('(');
                        int endIndex = caption.IndexOf(')');
                        string parsed = caption.Substring(startIndex + 1, endIndex - startIndex - 1);
                        portList.Add(parsed.ToUpper());
                    }
                }
                catch (Exception e)
                {
                    log.Error("DetectDevices failed", e);
                }
            }
            return portList;
        }

        #endregion

        #region Private Methods

        private string executeMethod(string method, int readTimeout = 0)
        {
            method = method.Insert(0, this.testUnit + ":");
            this.log.Debug("Executing " + method + " over " + this.ConnectionMode + " connection");
            if (this.ConnectionMode == Connection.TCP)
                return this.executeTcp(method, readTimeout);
            else
                return this.executeUsb(method, readTimeout);
        }

        private string executeTcp(string method, int additionalReadTimeout = 0)
        {
            string returndata = string.Empty;
            try
            {
                if (this.tcpClient == null || !this.tcpClient.Connected)
                    this.tryConnectTcp();

                // Handle possible TCP timeout when Thread.Sleep in Netduino side
                this.tcpClient.ReceiveTimeout = defaultReadTimeout + additionalReadTimeout;
                this.mfSocket.Send(method);
                this.mfSocket.Receive(out returndata);
            }
            catch (Exception ex)
            {
                this.log.Error("Execute command: " + method + " failed: " + ex.Message);
                try
                {
                    tryCloseTcp();
                }
                catch
                {
                    this.tcpClient = null;
                }
                throw;
            }

            return returndata;
        }

        private string executeUsb(string method, int additionalReadTimeout = 0)
        {
            string returnData = string.Empty;
            try
            {
                if (string.IsNullOrEmpty(this.serialPort))
                {
                    var devices = this.DetectDevices();
                    if (devices.Count > 0)
                        this.serialPort = devices[0];
                }
                using (SerialPort serial = new SerialPort(this.serialPort, 57600, Parity.None, 8, StopBits.One))
                {
                    serial.NewLine = "\n";
                    // Handle possible serialport read timeout when Thread.Sleep in Netduino side
                    serial.ReadTimeout = defaultReadTimeout + additionalReadTimeout;
                    //Stream serialStream = null;
                    //Mutex mutex = new Mutex(false, "HWController");
                    int tryCount = 300;
                    for (int i = 0; i < tryCount; i++)
                    {
                        try
                        {
                            //mutex.WaitOne();
                            serial.Open();
                            //serialStream = serial.BaseStream;
                            //GC.SuppressFinalize(serialStream);
                            break;
                        }
                        catch (Exception)
                        {
                            //Console.WriteLine("serial.open failed " + i);
                            Thread.Sleep(50);
                        }
                    }
                    // Line change char for serial port = '\n'
                    method += '\n';
                    // convert the line to bytes
                    byte[] utf8Bytes = Encoding.UTF8.GetBytes(method);

                    // send the bytes over the serial-port
                    try
                    {
                        if (serial.IsOpen)
                            serial.Write(utf8Bytes, 0, utf8Bytes.Length);
                    }
                    catch (Exception e)
                    {
                        log.Error("Write serialport failed: " + e.Message);
                    }

                    // Read the response over the serial-port
                    try
                    {
                        returnData = serial.ReadLine();
                    }
                    catch (Exception e)
                    {
                        log.Error("Read serialport failed: " + e.Message);
                    }
                    //try
                    //{
                    //    if (serialStream != null)
                    //        serialStream.Close();
                    //}
                    //catch (Exception e2)
                    //{
                    //    Console.WriteLine("Close serial stream failed: " + e2.Message);
                    //}
                    try
                    {
                        if (serial.IsOpen)
                            serial.Close();
                    }
                    catch (Exception e3)
                    {
                        log.Error("Close SerialPort object failed: " + e3.Message);
                    }
                    //try
                    //{
                    //    mutex.ReleaseMutex();
                    //}
                    //catch (Exception ex)
                    //{
                    //    Console.WriteLine("ReleaseMutex failed: " + ex.Message);
                    //}
                }
            }
            catch (Exception ex)
            {
                log.Error(ex.Message);
            }
            return returnData;
        }

        private void tryConnectTcp()
        {
            try
            {
                this.log.Info("Trying to connect to " + this.serverAddress);
                this.tcpClient = new TcpClient();
                this.tcpClient.Connect(this.serverAddress, this.serverPort);
                this.log.Info("Client Socket Program - Server Connected ...");
                this.mfSocket = new MfSocket(tcpClient.Client);
            }
            catch (Exception ex)
            {
                this.log.Error("TryConnect FAILED: " + ex.Message);
                throw;
            }
        }

        private void tryCloseTcp()
        {
            try
            {
                if (this.mfSocket != null)
                {
                    this.log.Info("Trying to close socket...");
                    this.mfSocket.Dispose();
                    this.mfSocket = null;
                }
                if (this.tcpClient != null)
                {
                    this.tcpClient.Close();
                    this.tcpClient = null;
                }
            }
            catch (Exception ex)
            {
                this.log.Error("TryClose FAILED: " + ex.Message);
                throw;
            }
        }

        #endregion

        #region MarshalByRefObject Methods

        public override object InitializeLifetimeService()
        {
            return null;
        }

        #endregion
    }
}
