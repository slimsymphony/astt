using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Net;
using System.IO;
using System.Threading;
using Managed.Adb.Exceptions;
using Managed.Adb.MoreLinq;
using Managed.Adb.IO;
using Managed.Adb.Logs;
using System.Text.RegularExpressions;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

// services that are supported by adb: https://github.com/android/platform_system_core/blob/master/adb/SERVICES.TXT
namespace Managed.Adb
{
    /// <summary>
    /// The ADB Helper class
    /// </summary>
    public  class AdbHelper
    {
        /// <summary>
        /// Logging tag
        /// </summary>
        private const string TAG = "AdbHelper";
        /// <summary>
        /// The time to wait
        /// </summary>
        private const int WAIT_TIME = 5;
        /// <summary>
        /// The default encoding
        /// </summary>
        public static string DEFAULT_ENCODING = "ISO-8859-1";

        /// <summary>
        /// 
        /// </summary>
        private static AdbHelper _instance = null;

        /// <summary>
        /// Prevents a default instance of the <see cref="AdbHelper"/> class from being created.
        /// </summary>
        private AdbHelper()
        { }

        /// <summary>
        /// Gets an instance of the <see cref="AdbHelper"/> class
        /// </summary>
        public static AdbHelper Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new AdbHelper();
                }
                return _instance;
            }
        }

        /// <summary>
        /// Opens the specified address on the device on the specified port.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="device">The device.</param>
        /// <param name="port">The port.</param>
        /// <returns></returns>
        public Socket Open(IPAddress address, IDevice device, int port)
        {
            Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                s.Connect(address, port);
                s.Blocking = true;
                s.NoDelay = false;

                SetDevice(s, device);

                byte[] req = CreateAdbForwardRequest(null, port);
                if (!Write(s, req))
                {
                    throw new AdbException("failed submitting request to ADB");
                }
                AdbResponse resp = ReadAdbResponse(s, false);
                if (!resp.Okay)
                {
                    throw new AdbException("connection request rejected");
                }
                s.Blocking = true;
            }
            catch (AdbException)
            {
                s.Close();
                throw;
            }
            return s;
        }

        /// <summary>
        /// Kills the adb server.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <returns></returns>
        /// <exception cref="System.IO.IOException">failed asking to kill adb</exception>
        public int KillAdb(IPEndPoint address)
        {
            var request = FormAdbRequest("host:kill");
            using (var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                socket.Connect(address);
                socket.Blocking = true;
                if (!Write(socket, request))
                {
                    throw new IOException("failed asking to kill adb");
                }
                var resp = ReadAdbResponse(socket, false);
                if (!resp.IOSuccess || !resp.Okay)
                {
                    Log.e(TAG, "Got timeout or unhappy response from ADB req: " + resp.Message);
                    socket.Close();
                    return -1;
                }
                return 0;
            }
        }

        /// <summary>
        /// Gets the debuggable processes
        /// </summary>
        /// <param name="address">The address,</param>
        /// <returns></returns>
        public int[] GetDebuggableProcesses(IPEndPoint address, Device device)
        {
            var request = FormAdbRequest("track-jdwp");
            byte[] reply;
            Socket adbChan = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                adbChan.Connect(address);
                adbChan.Blocking = true;

                SetDevice(adbChan, device);

                if (!Write(adbChan, request))
                    throw new IOException("failed asking for debuggable processes");

                AdbResponse resp = ReadAdbResponse(adbChan, false);
                if (!resp.IOSuccess || !resp.Okay)
                {
                    Log.e(TAG, "Got timeout or unhappy response from ADB fb req: " + resp.Message);
                    adbChan.CloseNoWait();
                    return null;
                }

                reply = new byte[4];
                if (!Read(adbChan, reply))
                {
                    Log.e(TAG, "error in getting data length");
                    adbChan.CloseNoWait();
                    return null;
                }

                string lenHex = reply.GetString(AdbHelper.DEFAULT_ENCODING);
                int len = int.Parse(lenHex, System.Globalization.NumberStyles.HexNumber);

                reply = new byte[len];
                if (!Read(adbChan, reply))
                {
                    Log.e(TAG, "did not get debuggable processes");

                    adbChan.CloseNoWait();
                    return null;
                }

                string sReply = reply.GetString(AdbHelper.DEFAULT_ENCODING);

                var pids = new List<int>();

                sReply.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries).ToList().ForEach(pid =>
                    {
                        int p;
                        if (int.TryParse(pid, out p))
                        {
                            pids.Add(p);
                        }
                    });
                return pids.ToArray();
            }
            finally 
            {
                adbChan.CloseNoWait();
            }
        }

        /// <summary>
        /// Gets the adb version.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <returns></returns>
        public int GetAdbVersion(IPEndPoint address)
        {
            var request = FormAdbRequest("host:version");
            byte[] reply;
            Socket adbChan = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                adbChan.Connect(address);
                adbChan.Blocking = true;
                if (!Write(adbChan, request))
                    throw new IOException("failed asking for adb version");

                AdbResponse resp = ReadAdbResponse(adbChan, false);
                if (!resp.IOSuccess || !resp.Okay)
                {
                    Log.e(TAG, "Got timeout or unhappy response from ADB fb req: " + resp.Message);
                    adbChan.Close();
                    return -1;
                }

                reply = new byte[4];
                if (!Read(adbChan, reply))
                {
                    Log.e(TAG, "error in getting data length");
                    adbChan.Close();
                    return -1;
                }

                string lenHex = reply.GetString(AdbHelper.DEFAULT_ENCODING);
                int len = int.Parse(lenHex, System.Globalization.NumberStyles.HexNumber);

                // the protocol version.
                reply = new byte[len];
                if (!Read(adbChan, reply))
                {
                    Log.e(TAG, "did not get the version info");

                    adbChan.Close();
                    return -1;
                }

                string sReply = reply.GetString(AdbHelper.DEFAULT_ENCODING);
                return int.Parse(sReply, System.Globalization.NumberStyles.HexNumber);

            }
            catch (Exception)
            {
                //Console.WriteLine(ex);
                throw;
            }
        }

        /// <summary>
        /// Creates and connects a new pass-through socket, from the host to a port on the device.
        /// </summary>
        /// <param name="endpoint"></param>
        /// <param name="device">the device to connect to. Can be null in which case the connection will be 
        /// to the first available device.</param>
        /// <param name="pid">the process pid to connect to.</param>
        /// <returns>The Socket</returns>
        public Socket CreatePassThroughConnection(IPEndPoint endpoint, Device device, int pid)
        {
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                socket.Connect(endpoint);
                socket.NoDelay = true;

                // if the device is not -1, then we first tell adb we're looking to
                // talk to a specific device
                SetDevice(socket, device);

                byte[] req = CreateJdwpForwardRequest(pid);

                if (!Write(socket, req))
                    throw new AdbException("failed submitting request to ADB");

                AdbResponse resp = ReadAdbResponse(socket, false);
                if (!resp.Okay)
                    throw new AdbException("connection request rejected: " + resp.Message);

            }
            catch (AdbException ioe)
            {
                socket.Close();
                throw ioe;
            }

            return socket;
        }

        /// <summary>
        /// Creates the adb forward request.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="port">The port.</param>
        /// <returns></returns>
        public byte[] CreateAdbForwardRequest(string address, int port)
        {
            string request;

            if (address == null)
                request = "tcp:" + port;
            else
                request = "tcp:" + port + ":" + address;
            return FormAdbRequest(request);
        }

        /// <summary>
        /// Forms the adb request.
        /// </summary>
        /// <param name="req">The req.</param>
        /// <returns></returns>
        public byte[] FormAdbRequest(string req)
        {
            string resultStr = string.Format("{0}{1}\n", req.Length.ToString("X4"), req);
            byte[] result;
            try
            {
                result = resultStr.GetBytes(AdbHelper.DEFAULT_ENCODING);
            }
            catch (EncoderFallbackException efe)
            {
                Log.e(TAG, efe);
                return null;
            }

            //System.Diagnostics.Debug.Assert(result.Length == req.Length + 5, string.Format("result: {1}{0}\nreq: {3}{2}", result.Length, result.GetString(AdbHelper.DEFAULT_ENCODING), req.Length, req));
            return result;
        }

        /// <summary>
        /// Writes the specified data to the specified socket.
        /// </summary>
        /// <param name="socket">The socket.</param>
        /// <param name="data">The data.</param>
        /// <returns></returns>
        public bool Write(Socket socket, byte[] data)
        {
            try
            {
                Write(socket, data, -1, DdmPreferences.Timeout);
            }
            catch (IOException e)
            {
                Log.e(TAG, e);
                return false;
            }

            return true;
        }

        /// <summary>
        /// Writes the specified data to the specified socket.
        /// </summary>
        /// <param name="socket">The socket.</param>
        /// <param name="data">The data.</param>
        /// <param name="length">The length.</param>
        /// <param name="timeout">The timeout.</param>
        public void Write(Socket socket, byte[] data, int length, int timeout)
        {
            int numWaits = 0;
            int count = -1;

            try
            {
                // NOTE: timeout parameter was not used in original AdbHelper code, so using it now (ripakane)
                socket.SendTimeout = timeout;
                count = socket.Send(data, 0, length != -1 ? length : data.Length, SocketFlags.None);
                if (count < 0)
                {
                    throw new AdbException("channel EOF");
                }
                else if (count == 0)
                {
                    // TODO: need more accurate timeout?
                    if (timeout != 0 && numWaits * WAIT_TIME > timeout)
                    {
                        throw new AdbException("timeout");
                    }
                    // non-blocking spin
                    Thread.Sleep(WAIT_TIME);
                    numWaits++;
                }
                else
                {
                    numWaits = 0;
                }
            }
            catch (SocketException)
            {
                //Console.WriteLine(sex);
                throw;
            }
        }

        /// <summary>
        /// Reads the adb response.
        /// </summary>
        /// <param name="socket">The socket.</param>
        /// <param name="readDiagString">if set to <c>true</c> [read diag string].</param>
        /// <returns></returns>
        public AdbResponse ReadAdbResponse(Socket socket, bool readDiagString)
        {
            AdbResponse resp = new AdbResponse();

            byte[] reply = new byte[4];
            if (!Read(socket, reply))
            {
                return resp;
            }
            resp.IOSuccess = true;

            if (IsOkay(reply))
            {
                resp.Okay = true;
            }
            else
            {
                readDiagString = true; // look for a reason after the FAIL
                resp.Okay = false;
            }

            // not a loop -- use "while" so we can use "break"
            while (readDiagString)
            {
                // length string is in next 4 bytes
                byte[] lenBuf = new byte[4];
                if (!Read(socket, lenBuf))
                {
                    //Console.WriteLine ( "Expected diagnostic string not found" );
                    break;
                }

                string lenStr = ReplyToString(lenBuf);

                int len;
                try
                {
                    len = int.Parse(lenStr, System.Globalization.NumberStyles.HexNumber);

                }
                catch (FormatException)
                {
                    Log.e(TAG, "Expected digits, got : {0} {1} {2} {3}", lenBuf[0], lenBuf[1], lenBuf[2], lenBuf[3]);
                    Log.e(TAG, "reply was {0}", ReplyToString(reply));
                    break;
                }

                byte[] msg = new byte[len];
                if (!Read(socket, msg))
                {
                    Log.e(TAG, "Failed reading diagnostic string, len={0}", len);
                    break;
                }

                resp.Message = ReplyToString(msg);
                Log.e(TAG, "Got reply '{0}', diag='{1}'", ReplyToString(reply), resp.Message);
                break;
            }

            return resp;
        }

        /// <summary>
        /// Reads the data from specified socket.
        /// </summary>
        /// <param name="socket">The socket.</param>
        /// <param name="data">The data.</param>
        /// <returns></returns>
        public bool Read(Socket socket, byte[] data)
        {
            try
            {
                Read(socket, data, -1, DdmPreferences.Timeout);
            }
            catch (AdbException)
            {
                return false;
            }

            return true;
        }

        /// <summary>
        /// Reads the data from specified socket.
        /// </summary>
        /// <param name="socket">The socket.</param>
        /// <param name="data">The data.</param>
        /// <param name="length">The length.</param>
        /// <param name="timeout">The timeout.</param>
        public void Read(Socket socket, byte[] data, int length, int timeout)
        {
            int expLen = length != -1 ? length : data.Length;
            int count = -1;
            int totalRead = 0;

            while (count != 0 && totalRead < expLen)
            {
                try
                {
                    int left = expLen - totalRead;
                    int buflen = left < socket.ReceiveBufferSize ? left : socket.ReceiveBufferSize;

                    byte[] buffer = new byte[buflen];
                    socket.ReceiveBufferSize = expLen;
                    count = socket.Receive(buffer, buflen, SocketFlags.None);
                    if (count < 0)
                    {
                        Log.e(TAG, "read: channel EOF");
                        throw new AdbException("EOF");
                    }
                    else if (count == 0)
                    {
                        //Console.WriteLine ("DONE with Read");
                    }
                    else
                    {
                        Array.Copy(buffer, 0, data, totalRead, count);
                        totalRead += count;
                    }
                }
                catch (SocketException sex)
                {
                    throw new AdbException(string.Format("No Data to read: {0}", sex.Message));
                }
            }
        }

        /// <summary>
        /// Creates the JDWP forward request.
        /// </summary>
        /// <param name="pid">The pid.</param>
        /// <returns></returns>
        private byte[] CreateJdwpForwardRequest(int pid)
        {
            string req = string.Format("jdwp:{0}", pid);
            return FormAdbRequest(req);
        }

        /// <summary>
        /// Creates the forward.
        /// </summary>
        /// <param name="adbSockAddr">The adb sock addr.</param>
        /// <param name="device">The device.</param>
        /// <param name="localPort">The local port.</param>
        /// <param name="remotePort">The remote port.</param>
        /// <returns></returns>
        public bool CreateForward(IPEndPoint adbSockAddr, Device device, int localPort, int remotePort)
        {
            Socket adbChan = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                adbChan.Connect(adbSockAddr);
                adbChan.Blocking = true;

                var request = FormAdbRequest(string.Format("host-serial:{0}:forward:tcp:{1};tcp:{2}",
                    device.SerialNumber, localPort, remotePort));

                if (!Write(adbChan, request))
                {
                    throw new AdbException("failed to submit the forward command.");
                }

                AdbResponse resp = ReadAdbResponse(adbChan, false);
                if (!resp.IOSuccess || !resp.Okay)
                {
                    throw new AdbException("Device rejected command: " + resp.Message);
                }
            }
            finally
            {
                if (adbChan != null)
                {
                    adbChan.Close();
                }
            }

            return true;
        }

        /// <summary>
        /// Removes the forward.
        /// </summary>
        /// <param name="adbSockAddr">The adb sock addr.</param>
        /// <param name="device">The device.</param>
        /// <param name="localPort">The local port.</param>
        /// <returns></returns>
        public bool RemoveForward(IPEndPoint adbSockAddr, Device device, int localPort)
        {
            Socket adbChan = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                adbChan.Connect(adbSockAddr);
                adbChan.Blocking = true;

                var request = FormAdbRequest(string.Format("host-serial:{0}:killforward:tcp:{1}",
                    device.SerialNumber, localPort));

                if (!Write(adbChan, request))
                {
                    throw new AdbException("failed to submit the remove forward command.");
                }

                AdbResponse resp = ReadAdbResponse(adbChan, false);
                if (!resp.IOSuccess || !resp.Okay)
                {
                    throw new AdbException("Device rejected command: " + resp.Message);
                }
            }
            finally
            {
                if (adbChan != null)
                {
                    adbChan.Close();
                }
            }

            return true;
        }

        /// <summary>
        /// Determines whether the specified reply is okay.
        /// </summary>
        /// <param name="reply">The reply.</param>
        /// <returns>
        ///   <c>true</c> if the specified reply is okay; otherwise, <c>false</c>.
        /// </returns>
        public bool IsOkay(byte[] reply)
        {
            return reply[0] == (byte)'O' && reply[1] == (byte)'K'
                && reply[2] == (byte)'A' && reply[3] == (byte)'Y';
        }

        /// <summary>
        /// Replies to string.
        /// </summary>
        /// <param name="reply">The reply.</param>
        /// <returns></returns>
        public string ReplyToString(byte[] reply)
        {
            string result;
            try
            {
                result = Encoding.Default.GetString(reply);
            }
            catch (DecoderFallbackException uee)
            {
                Log.e(TAG, uee);
                result = "";
            }

            return result;
        }

        /// <summary>
        /// Gets the devices that are available for communication.
        /// </summary>
        public List<Device> GetDevices()
        {
            return GetDevices(AndroidDebugBridge.SocketAddress);
        }

        /// <summary>
        /// Gets the devices that are available for communication.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <returns></returns>
        public List<Device> GetDevices(IPEndPoint address)
        {
            byte[] request = FormAdbRequest("host:devices");
            byte[] reply;
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                socket.Connect(address);
                socket.Blocking = true;
                if (!Write(socket, request))
                {
                    throw new AdbException("failed asking for devices");
                }

                AdbResponse resp = ReadAdbResponse(socket, false);
                if (!resp.IOSuccess || !resp.Okay)
                {
                    Log.e(TAG, "Got timeout or unhappy response from ADB fb req: " + resp.Message);
                    socket.Close();
                    return null;
                }

                reply = new byte[4];
                if (!Read(socket, reply))
                {
                    Log.e(TAG, "error in getting data length");
                    socket.Close();
                    return null;
                }
                string lenHex = Encoding.Default.GetString(reply);
                int len = int.Parse(lenHex, System.Globalization.NumberStyles.HexNumber);

                reply = new byte[len];
                if (!Read(socket, reply))
                {
                    Log.e(TAG, "error in getting data");
                    socket.Close();
                    return null;
                }

                List<Device> s = new List<Device>();

                string[] data = Encoding.Default.GetString(reply).Split(new string[] { "\r\n", "\n" }, StringSplitOptions.RemoveEmptyEntries);
                data.ForEach(item =>
                    {
                        s.Add(Device.CreateFromAdbData(item));
                    });

                return s;
            }
            finally
            {
                socket.Close();
            }
        }

        /// <summary>
        /// Gets the frame buffer from the specified end point.
        /// </summary>
        /// <param name="adbSockAddr">The adb sock addr.</param>
        /// <param name="device">The device.</param>
        /// <returns></returns>
        public RawImage GetFrameBuffer(IPEndPoint adbSockAddr, IDevice device)
        {
            return GetFrameBuffer<RawImage>(adbSockAddr, device);
        }

        /// <summary>
        /// Gets the frame buffer from the specified end point.
        /// </summary>
        /// <typeparam name="T">Type of the image.</typeparam>
        /// <param name="adbSockAddr">The adb sock addr.</param>
        /// <param name="device">The device.</param>
        /// <returns></returns>
        public T GetFrameBuffer<T>(IPEndPoint adbSockAddr, IDevice device) where T : class
        {
            var targetType = typeof(T);
            if (targetType != typeof(RawImage) && targetType != typeof(Bitmap) && targetType != typeof(Image))
            {
                throw new ArgumentException(targetType.Name);
            }

            RawImage imageParams = new RawImage();
            var request = FormAdbRequest("framebuffer:");
            byte[] nudge = { 0 };
            byte[] reply;

            Socket adbChan = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                adbChan.Connect(adbSockAddr);
                adbChan.Blocking = true;

                // if the device is not -1, then we first tell adb we're looking to talk
                // to a specific device
                SetDevice(adbChan, device);

                if (!Write(adbChan, request))
                    throw new AdbException("failed asking for frame buffer");

                AdbResponse resp = ReadAdbResponse(adbChan, false);

                if (!resp.IOSuccess || !resp.Okay)
                {
                    Log.w(TAG, "Got timeout or unhappy response from ADB fb req: " + resp.Message);
                    adbChan.Close();
                    return default(T);
                }

                // first the protocol version.
                reply = new byte[4];
                if (!Read(adbChan, reply))
                {
                    Log.w(TAG, "got partial reply from ADB fb:");

                    adbChan.Close();
                    return default(T);
                }

                int version = BitConverter.ToInt16(reply, 0);

                // get the header size (this is a count of int)
                int headerSize = RawImage.GetHeaderSize(version);
                // read the header
                reply = new byte[headerSize * 4];
                if (!Read(adbChan, reply))
                {
                    Log.w(TAG, "got partial reply from ADB fb:");

                    adbChan.Close();
                    return default(T);
                }

                if (!imageParams.ReadHeader(version, reply))
                {
                    Log.w(TAG, "Unsupported protocol: " + version);
                    return default(T);
                }

                Log.d(TAG, "image params: bpp=" + imageParams.Bpp + ", size="
                                + imageParams.Size + ", width=" + imageParams.Width
                                + ", height=" + imageParams.Height);

                if (!Write(adbChan, nudge))
                    throw new AdbException("failed nudging");

                reply = new byte[imageParams.Size];
                if (!Read(adbChan, reply))
                {
                    Log.w(TAG, "got truncated reply from ADB fb data");
                    adbChan.Close();
                    return default(T);
                }

                if (targetType == typeof(RawImage))
                {
                    imageParams.Data = reply;
                    return imageParams as T;
                }
                else if (targetType == typeof(Bitmap) || targetType == typeof(Image))
                {
                    if (imageParams.Bpp == 32)
                    {
                        for (int i = 0; i < reply.Length; i += 4)
                        {
                            reply[i] = (byte)(reply[i] ^ reply[i + 2]);
                            reply[i + 2] = (byte)(reply[i] ^ reply[i + 2]);
                            reply[i] = (byte)(reply[i] ^ reply[i + 2]);
                        }
                    }
                    var format = imageParams.Bpp == 32 ? PixelFormat.Format32bppArgb : PixelFormat.Format16bppRgb565;
                    var bitmap = new Bitmap(imageParams.Width, imageParams.Height, format);
                    var bitmapdata = bitmap.LockBits(new Rectangle(0, 0, imageParams.Width, imageParams.Height), ImageLockMode.WriteOnly, format);

                    Marshal.Copy(reply, 0, bitmapdata.Scan0, imageParams.Size);
                    bitmap.UnlockBits(bitmapdata);
                    return bitmap as T;
                }
            }
            finally
            {
                if (adbChan != null)
                {
                    adbChan.Close();
                }
            }

            return default(T);
        }

        /// <summary>
        /// Executes a shell command on the remote device
        /// </summary>
        /// <param name="endPoint">The end point.</param>
        /// <param name="command">The command.</param>
        /// <param name="device">The device.</param>
        /// <param name="rcvr">The RCVR.</param>
        /// <remarks>Should check if you CanSU before calling this.</remarks>
        public void ExecuteRemoteRootCommand(IPEndPoint endPoint, string command, Device device, IShellOutputReceiver rcvr)
        {
            ExecuteRemoteRootCommand(endPoint, string.Format("su -c \"{0}\"", command), device, rcvr, int.MaxValue);
        }

        /// <summary>
        /// Executes a shell command on the remote device
        /// </summary>
        /// <param name="endPoint">The end point.</param>
        /// <param name="command">The command.</param>
        /// <param name="device">The device.</param>
        /// <param name="rcvr">The RCVR.</param>
        /// <param name="maxTimeToOutputResponse">The max time to output response.</param>
        public void ExecuteRemoteRootCommand(IPEndPoint endPoint, string command, Device device, IShellOutputReceiver rcvr, int maxTimeToOutputResponse)
        {
            ExecuteRemoteCommand(endPoint, string.Format("su -c \"{0}\"", command), device, rcvr);
        }

        /// <summary>
        /// Executes the remote command.
        /// </summary>
        /// <param name="endPoint">The end point.</param>
        /// <param name="command">The command.</param>
        /// <param name="device">The device.</param>
        /// <param name="rcvr">The RCVR.</param>
        /// <param name="maxTimeToOutputResponse">The max time to output response.</param>
        /// <exception cref="AdbException">failed submitting shell command</exception>
        /// <exception cref="System.OperationCanceledException"></exception>
        /// <exception cref="Managed.Adb.Exceptions.ShellCommandUnresponsiveException"></exception>
        /// <exception cref="System.IO.FileNotFoundException"></exception>
        /// <exception cref="UnknownOptionException"></exception>
        /// <exception cref="CommandAbortingException"></exception>
        /// <exception cref="PermissionDeniedException"></exception>
        public void ExecuteRemoteCommand(IPEndPoint endPoint, string command, Device device, IShellOutputReceiver rcvr, int maxTimeToOutputResponse)
        {

            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            if (!device.IsOnline)
            {
                return;
            }

            try
            {
                socket.Connect(endPoint);
                socket.ReceiveTimeout = maxTimeToOutputResponse;
                socket.SendTimeout = maxTimeToOutputResponse;
                socket.Blocking = true;

                SetDevice(socket, device);

                var request = FormAdbRequest("shell:" + command);

                if (!Write(socket, request))
                {
                    throw new AdbException("failed submitting shell command");
                }

                AdbResponse resp = ReadAdbResponse(socket, false);

                if (!resp.IOSuccess || !resp.Okay)
                {
                    throw new AdbException("sad result from adb: " + resp.Message);
                }

                var data = new byte[16384];
                int count = -1;
                while (count != 0)
                {

                    if (rcvr != null && rcvr.IsCancelled)
                    {
                        Log.w(TAG, "execute: cancelled");
                        throw new OperationCanceledException();
                    }

                    count = socket.Receive(data);
                    if (count == 0)
                    {
                        // we're at the end, we flush the output
                        rcvr.Flush();
                        Log.w(TAG, "execute '" + command + "' on '" + device + "' : EOF hit. Read: " + count);
                    }
                    else
                    {
                        string[] cmd = command.Trim().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                        string sdata = data.GetString(0, count, AdbHelper.DEFAULT_ENCODING);

                        var sdataTrimmed = sdata.Trim();
                        if (sdataTrimmed.EndsWith(string.Format("{0}: not found", cmd[0])))
                        {
                            Log.w(TAG, "The remote execution returned: '{0}: not found'", cmd[0]);
                            throw new FileNotFoundException(string.Format("The remote execution returned: '{0}: not found'", cmd[0]));
                        }

                        if (sdataTrimmed.EndsWith("No such file or directory"))
                        {
                            Log.w(TAG, "The remote execution returned: {0}", sdataTrimmed);
                            throw new FileNotFoundException(string.Format("The remote execution returned: {0}", sdataTrimmed));
                        }

                        // for "unknown options"
                        if (sdataTrimmed.Contains("Unknown option"))
                        {
                            Log.w(TAG, "The remote execution returned: {0}", sdataTrimmed);
                            throw new UnknownOptionException(sdataTrimmed);
                        }

                        // for "aborting" commands
                        if (sdataTrimmed.IsMatch("Aborting.$"))
                        {
                            Log.w(TAG, "The remote execution returned: {0}", sdataTrimmed);
                            throw new CommandAbortingException(sdataTrimmed);
                        }

                        // for busybox applets 
                        // cmd: applet not found
                        if (sdataTrimmed.IsMatch("applet not found$") && cmd.Length > 1)
                        {
                            Log.w(TAG, "The remote execution returned: '{0}'", sdataTrimmed);
                            throw new FileNotFoundException(string.Format("The remote execution returned: '{0}'", sdataTrimmed));
                        }

                        // checks if the permission to execute the command was denied.
                        // workitem: 16822
                        if (sdataTrimmed.IsMatch("(permission|access) denied$"))
                        {
                            Log.w(TAG, "The remote execution returned: '{0}'", sdataTrimmed);
                            throw new PermissionDeniedException(string.Format("The remote execution returned: '{0}'", sdataTrimmed));
                        }

                        // Add the data to the receiver
                        if (rcvr != null)
                        {
                            rcvr.AddOutput(data, 0, count);
                        }

                    }
                }
            }
            catch (SocketException)
            {
                throw new ShellCommandUnresponsiveException();
            }
            finally
            {
                if (socket != null)
                {
                    socket.CloseNoWait();
                }
                rcvr.Flush();
            }
        }

        /// <summary>
        /// Executes a shell command on the remote device
        /// </summary>
        /// <param name="endPoint">The socket end point</param>
        /// <param name="command">The command to execute</param>
        /// <param name="device">The device to execute on</param>
        /// <param name="rcvr">The shell output receiver</param>
        /// <exception cref="FileNotFoundException">Throws if the result is 'command': not found</exception>
        /// <exception cref="IOException">Throws if there is a problem reading / writing to the socket</exception>
        /// <exception cref="OperationCanceledException">Throws if the execution was canceled</exception>
        /// <exception cref="EndOfStreamException">Throws if the Socket.Receice ever returns -1</exception>
        public void ExecuteRemoteCommand(IPEndPoint endPoint, string command, Device device, IShellOutputReceiver rcvr)
        {
            ExecuteRemoteCommand(endPoint, command, device, rcvr, int.MaxValue);
        }

        /// <summary>
        /// Sets the device.
        /// </summary>
        /// <param name="adbChan">The adb chan.</param>
        /// <param name="device">The device.</param>
        public void SetDevice(Socket adbChan, IDevice device)
        {
            // if the device is not null, then we first tell adb we're looking to talk
            // to a specific device
            if (device != null)
            {
                String msg = "host:transport:" + device.SerialNumber;
                byte[] device_query = FormAdbRequest(msg);

                if (!Write(adbChan, device_query))
                {
                    throw new AdbException("failed submitting device (" + device + ") request to ADB");
                }

                AdbResponse resp = ReadAdbResponse(adbChan, false);

                if (!resp.Okay)
                {
                    if (string.Compare("device not found", resp.Message, true) == 0)
                    {
                        throw new DeviceNotFoundException(device.SerialNumber);
                    }
                    else
                    {
                        if (resp.Message.Equals("device offline"))
                        {
                            ((Device)device).State = DeviceState.Offline;
                        }

                        throw new AdbException("device (" + device + ") request rejected: " + resp.Message);
                    }
                }
            }
        }

        /// <summary>
        /// Runs the Event log service on the Device, and provides its output to the LogReceiver.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="device">The device.</param>
        /// <param name="rcvr">The RCVR.</param>
        public void RunEventLogService(IPEndPoint address, Device device, LogReceiver rcvr)
        {
            RunLogService(address, device, "events", rcvr);
        }

        /// <summary>
        /// Runs the Event log service on the Device, and provides its output to the LogReceiver.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="device">The device.</param>
        /// <param name="logName">Name of the log.</param>
        /// <param name="rcvr">The RCVR.</param>
        /// <exception cref="AdbException">failed asking for log</exception>
        /// <exception cref="Managed.Adb.Exceptions.AdbCommandRejectedException"></exception>
        public void RunLogService(IPEndPoint address, Device device, string logName, LogReceiver rcvr)
        {
            try
            {
                using (var adbChan = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                {
                    adbChan.ReceiveBufferSize = 4 * 1024;
                    adbChan.Connect(address);
                    adbChan.Blocking = true;
                    // if the device is not -1, then we first tell adb we're looking to talk
                    // to a specific device
                    SetDevice(adbChan, device);

                    var request = FormAdbRequest("log:" + logName);
                    if (!Write(adbChan, request))
                    {
                        throw new AdbException("failed asking for log");
                    }

                    var resp = ReadAdbResponse(adbChan, false);
                    if (resp.Okay == false)
                    {
                        throw new AdbCommandRejectedException(resp.Message);
                    }

                    while (true)
                    {
                        int count;
                        if (rcvr != null && rcvr.IsCancelled)
                        {
                            break;
                        }

                        var buffer = new byte[4 * 1024];

                        count = adbChan.Receive(buffer);

                        if (count < 0)
                        {
                            break;
                        }
                        else if (count == 0)
                        {
                            try
                            {
                                Thread.Sleep(WAIT_TIME * 5);
                            }
                            catch (ThreadInterruptedException)
                            {
                            }
                        }
                        else
                        {
                            if (rcvr != null)
                            {
                                rcvr.ParseNewData(buffer, 0, count, DateTime.Now);
                            }
                        }
                    }
                }
            }
            finally { }
        }

        /// <summary>
        /// Runs the dev service on the Device, and provides its output to the stream.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="device">The device.</param>
        /// <param name="filePath">Absolute path to the remote file.</param>
        /// <param name="target">The stream to copy into</param>
        /// <returns>File contents as stream</returns>
        public Stream RunDevService(IPEndPoint address, Device device, string filePath, Stream target = null)
        {
            var stream = target ?? new MemoryStream();
            var adbChan = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                adbChan.ReceiveBufferSize = 4 * 1024;
                adbChan.ReceiveTimeout = DdmPreferences.LongTimeout;
                adbChan.SendTimeout = DdmPreferences.Timeout;
                adbChan.Connect(address);
                adbChan.Blocking = true;
                    
                SetDevice(adbChan, device);
                   
                var request = FormAdbRequest("dev:" + filePath);
                if (!Write(adbChan, request))
                {
                    throw new AdbException("failed asking for file stream");
                }

                var resp = ReadAdbResponse(adbChan, false);
                if (resp.Okay == false)
                {
                    throw new AdbCommandRejectedException(resp.Message);
                }
                                        
                while (true)
                {
                    var buffer = new byte[4 * 1024];
                    var count = adbChan.Receive(buffer);
                    if (count <= 0)
                    {
                        break;
                    }
                    stream.Write(buffer, 0, count);
                }
            }
            finally 
            {
                adbChan.CloseNoWait();
                stream.Position = 0;
            }
            return stream;
        }

        /// <summary>
        /// Runs the file tail on the Device, and provides its output to the receiver.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="device">The device.</param>
        /// <param name="filePath">Absolute path to the remote file.</param>
        /// <param name="trcvr">The RCVR.</param>
        /// <param name="bufferSize">Size of the buffer to be used</param>
        public void RunTailService(IPEndPoint address, Device device, string filePath, ITailReceiver trcvr, int bufferSize = 4 * 1024)
        {
            var adbChan = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                adbChan.ReceiveBufferSize = bufferSize;
                adbChan.Connect(address);
                adbChan.Blocking = true;

                SetDevice(adbChan, device);

                var request = FormAdbRequest("dev:" + filePath);
                if (!Write(adbChan, request))
                {
                    throw new AdbException("failed asking for file stream");
                }

                var resp = ReadAdbResponse(adbChan, false);
                if (resp.Okay == false)
                {
                    throw new AdbCommandRejectedException(resp.Message);
                }
                
                while (true)
                {
                    if (trcvr != null && trcvr.IsCancelled)
                    {
                        break;
                    }

                    var buffer = new byte[bufferSize];

                    var count = adbChan.Receive(buffer);

                    if (count < 0)
                    {
                        break;
                    }
                    else if (count == 0)
                    {
                        try
                        {
                            Thread.Sleep(WAIT_TIME * 5);
                        }
                        catch (ThreadInterruptedException)
                        {
                        }
                    }
                    else
                    {
                        if (trcvr != null)
                        {
                            trcvr.Tail(buffer, 0, count);
                        }
                    }
                }
            }
            finally
            {
                adbChan.CloseNoWait();
            }
        }

        /// <summary>
        /// Runs cat for a log file (character device file).  
        /// </summary>
        /// <param name="address"></param>
        /// <param name="device"></param>
        /// <param name="filePath"></param>
        /// <param name="receiver"></param>
        public void RunCatLog(IPEndPoint address, Device device, string filePath, LogReceiver receiver)
        {
            if (!device.IsOnline || receiver == null) return;

            var max_logger_entry_len = 5 * 1024; //However, adb max playload is 4096...

            using (var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                try
                {
                    socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, new LingerOption(true, 0));
                    socket.ReceiveTimeout = -1; //infinite
                    socket.ReceiveBufferSize = max_logger_entry_len + 1;
                    socket.Blocking = true;
                    socket.Connect(AndroidDebugBridge.SocketAddress);
                    receiver.CancelAction = new Action(() =>
                    {
                        if (socket != null) socket.Close();
                    });

                    SetDevice(socket, device);

                    var request = AdbHelper.Instance.FormAdbRequest(string.Format("shell:cat {0}", filePath));

                    if (!Write(socket, request))
                    {
                        throw new AdbException("failed submitting shell command");
                    }

                    var resp = AdbHelper.Instance.ReadAdbResponse(socket, false);

                    if (!resp.IOSuccess || !resp.Okay)
                    {
                        throw new AdbException("sad result from adb: " + resp.Message);
                    }

                    var data = new byte[max_logger_entry_len + 1];

                    byte last = 0x00;

                    while (device.IsOnline && receiver != null && !receiver.IsCancelled)
                    {
                        var count = socket.Receive(data);

                        var now = DateTime.Now;

                        if (count > 0)
                        {
                            using (var chunk = new MemoryStream())
                            {
                                for (int i = 0; i < count; i++)
                                {
                                    // end of line mark conversion needed, because ADB shell messes them up
                                    if ((count > i + 1 && data[i] == 0x0d && data[i + 1] == 0x0a) || (last == 0x0d && data[i] == 0x0a))
                                    {
                                        chunk.WriteByte(0x0a);
                                        i++;
                                    }
                                    else
                                    {
                                        chunk.WriteByte(data[i]);
                                    }

                                    if (i == count - 1)
                                    {
                                        last = data[i];
                                    }
                                }
                                receiver.ParseNewData(chunk.ToArray(), 0, (int)chunk.Length, now);
                            }
                        }
                    }
                }
                catch (SocketException err)
                {
                    if (err.SocketErrorCode != SocketError.ConnectionAborted)
                    {
                        Log.e("Socket error while receiving response", err);
                    }
                }
            }
        }

        /// <summary>
        /// Executes the bugreport/dumpstate command in the remote device. More optimized than ExecuteRemote command because doe not evaluate the data.
        /// </summary>
        /// <param name="endPoint">The socket end point</param>
        /// <param name="device">The device to execute on</param>
        /// <param name="rcvr">The shell output receiver</param>
        /// <param name="timeout">The socket read timeout</param>
        public void RunBugReporterService(IPEndPoint endPoint, Device device, IShellOutputReceiver rcvr, int timeout)
        {
            var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, new LingerOption(true, 0));

            if (!device.IsOnline)
            {
                return;
            }

            try
            {
                var bufferSize = 4096;

                socket.Connect(endPoint);
                socket.ReceiveTimeout = timeout;
                socket.ReceiveBufferSize = bufferSize;
                socket.Blocking = true;

                SetDevice(socket, device);

                var request = FormAdbRequest("shell:dumpstate -q");

                if (!Write(socket, request))
                {
                    throw new AdbException("failed submitting dumpstate request");
                }

                var resp = ReadAdbResponse(socket, false);

                if (!resp.IOSuccess || !resp.Okay)
                {
                    throw new AdbException("sad result from adb: " + resp.Message);
                }

                var data = new byte[bufferSize];
                var count = -1;

                while (count != 0)
                {
                    if (rcvr != null && rcvr.IsCancelled)
                    {
                        Log.w(TAG, "execute: cancelled");
                        break;
                    }

                    count = socket.Receive(data);

                    if (count == 0)
                    {
                        Log.w(TAG, "dumpstate on '" + device + "' : EOF hit. Read: " + count);
                    }
                    else
                    {
                        // Add the data to the receiver
                        if (rcvr != null)
                        {
                            rcvr.AddOutput(data, 0, count);
                        }
                    }
                }
            }
            catch (SocketException)
            {
                throw new ShellCommandUnresponsiveException();
            }
            finally
            {
                if (socket != null)
                {
                    socket.Close();
                }
                rcvr.Flush();
            }
        }

        /// <summary>
        /// Reboots the specified adb socket address.
        /// </summary>
        /// <param name="adbSocketAddress">The adb socket address.</param>
        /// <param name="device">The device.</param>
        public void Reboot(IPEndPoint adbSocketAddress, Device device)
        {
            Reboot("", adbSocketAddress, device);
        }

        /// <summary>
        /// Reboots the specified device in to the specified mode.
        /// </summary>
        /// <param name="into">The into.</param>
        /// <param name="adbSockAddr">The adb sock addr.</param>
        /// <param name="device">The device.</param>
        public void Reboot(string into, IPEndPoint adbSockAddr, Device device)
        {
            byte[] request;

            if (into == null)
            {
                request = FormAdbRequest("reboot:");
            }
            else
            {
                request = FormAdbRequest("reboot:" + into);
            }

            Socket adbChan = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                adbChan.Connect(adbSockAddr);
                adbChan.Blocking = true;

                // if the device is not -1, then we first tell adb we're looking to talk
                // to a specific device
                SetDevice(adbChan, device);

                if (!Write(adbChan, request))
                {
                    throw new AdbException("failed asking for reboot");
                }
            }
            finally
            {
                if (adbChan != null)
                {
                    adbChan.Close();
                }
            }
        }
    }

    /// <summary>
    /// Extension class for socket close with linger option
    /// </summary>
    public static class SocketExtension
    {
        public static void CloseNoWait(this Socket sock)
        {
            try
            {
                LingerOption lo = new LingerOption(true, 0);
                sock.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, lo);
                sock.Close();
            }
            catch (ObjectDisposedException)
            { }
        }
    }

}

