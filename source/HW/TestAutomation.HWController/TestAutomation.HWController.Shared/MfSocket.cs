using System;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace TestAutomation.HWController.Shared
{
    public class MfSocket : IDisposable
    {
        #region Private fields

        private const ushort sizeBytesCount = 4;
        private const int maxDataSize = 9999;

        /// <summary>
        /// Maximum size of datachunk Netduino can send/receive at a time is 536 bytes.
        /// </summary>
        private const short chunkSize = 500;

        /// <summary>
        /// Socket Timeout in tics, default 50000000 (5 Sec).
        /// </summary>
        private int socketTimeout = 500000000;

        private Socket socket;
        private NetworkStream networkStream;

        #endregion

        #region Public properties

        /// <summary>
        /// Returns the available bytes to read
        /// </summary>
        public int Available
        { 
            get { return this.socket.Available; }
        }
        
        #endregion

        #region Constructor(s)

        public MfSocket(Socket s)
        {
            this.socket = s;
#if !MF_FRAMEWORK_VERSION_V4_3
            this.socket.SendTimeout = 5000;
            this.socket.ReceiveTimeout = 5000;
#endif
            this.networkStream = new NetworkStream(this.socket);
        }

        #endregion

        #region Public methods

        #region Send

        /// <summary>
        /// This function sends string data over network
        /// </summary>
        /// <param name="data">String data</param>
        public void Send(string data)
        {
            Send(data, 0, data.Length);
        }

        /// <summary>
        /// This function sends string data over network starting from offset till the size given
        /// </summary>
        /// <param name="data">String data</param>
        /// <param name="offset">Start position in string</param>
        /// <param name="size">Total size to be sent</param>
        public void Send(string data, int offset, int size)
        {
            int totalSize = offset + size; //The size of buffer can be more but this is bare minimum
            long startTickCount = DateTime.Now.Ticks;

            //Send Data Size that will be sent
            send(intToByteArray(size), 0, sizeBytesCount, socket, networkStream, socketTimeout);

            for (int partOffset = offset; partOffset < totalSize; partOffset += chunkSize)
            {
                if (DateTime.Now.Ticks > startTickCount + socketTimeout
                    && socketTimeout != 0)
                {
#if MF_FRAMEWORK_VERSION_V4_3
                            throw new SocketException(SocketError.TimedOut);
#else
                    throw new SocketException((int) SocketError.TimedOut);
#endif

                }

                //Send Data in chunks
                send(Encoding.UTF8.GetBytes(data), partOffset,
                     totalSize - partOffset > chunkSize ? chunkSize : size - partOffset, socket, networkStream,
                     socketTimeout);
            }
        }

        #endregion Send

        #region Receive

        /// <summary>
        /// This function is used to recive data from network
        /// </summary>
        /// <param name="data">String data to be set</param>
        /// <returns>Length of bytes received</returns>
        public int Receive(out string data)
        {
            return Receive(out data, 0, maxDataSize);
        }

        /// <summary>
        /// This function is used to recive data from network starting from offset till end of string
        /// </summary>
        /// <param name="data">String data to be set</param>
        /// <param name="offset"></param>
        /// <returns>Length of bytes received</returns>
        public int Receive(out string data, int offset)
        {
            return Receive(out data, offset, maxDataSize);
        }

        /// <summary>
        /// This function is used to recive data from network starting from offset till the size given
        /// </summary>
        /// <param name="data">String data to be set</param>
        /// <param name="offset">Start position in string</param>
        /// <param name="size">Total size in bytes to be received</param>
        /// <returns>Length of bytes received</returns>
        public int Receive(out string data, int offset, int size)
        {
            byte[] buffer = new byte[sizeBytesCount];

            //get data size that will be comming
            receive(buffer, 0, sizeBytesCount, socket, networkStream, socketTimeout);
            int incommingSize = Convert.ToInt32(new String(Encoding.UTF8.GetChars(buffer)));


            buffer = new byte[incommingSize];
            int received = receive(buffer, offset, size > incommingSize ? incommingSize : size, socket, networkStream,
                                   socketTimeout);
            data = new String(Encoding.UTF8.GetChars(buffer)).Trim('\0');
            return received;

        }

        #endregion Receive

        #endregion

        #region Private methods

        private void send(byte[] buffer, int offset, int size, Socket socket, NetworkStream networkStream,
                          int socketTimeout)
        {
            long startTickCount = DateTime.Now.Ticks;
            int sent = 0; // how many bytes is already sent

            networkStream.Flush();

            do
            {
                if (DateTime.Now.Ticks > startTickCount + socketTimeout
                    && socketTimeout != 0)
                {
#if MF_FRAMEWORK_VERSION_V4_3
                            throw new SocketException(SocketError.TimedOut);
#else
                    throw new SocketException((int) SocketError.TimedOut);
#endif
                }

                try
                {
                    sent += socket.Send(buffer, offset + sent, size - sent, SocketFlags.None);
                }
                catch (SocketException ex)
                {
                    if (ex.ErrorCode == (int) SocketError.WouldBlock ||
                        ex.ErrorCode == (int) SocketError.InProgress ||
                        ex.ErrorCode == (int) SocketError.NoBufferSpaceAvailable)
                    {
                        // socket buffer is probably full, wait and try again
                        Thread.Sleep(30);
                    }
                    else
                    {
                        throw ex; // any serious error occurr
                    }
                }
            } while (sent < size);

            networkStream.Flush();
        }

        private int receive(byte[] buffer, int offset, int size, Socket socket, NetworkStream networkStream,
                            int socketTimeout)
        {
            long startTickCount = DateTime.Now.Ticks;
            int received = 0; // how many bytes is already received

            networkStream.Flush();

            do
            {
                if (DateTime.Now.Ticks > startTickCount + socketTimeout
                    && socketTimeout != 0)
                {
#if MF_FRAMEWORK_VERSION_V4_3
                            throw new SocketException(SocketError.TimedOut);
#else
                    throw new SocketException((int) SocketError.TimedOut);
#endif
                }

                try
                {
                    received += socket.Receive(buffer, offset + received, size - received, SocketFlags.None);
                }
                catch (SocketException ex)
                {
                    if (ex.ErrorCode == (int) SocketError.WouldBlock ||
                        ex.ErrorCode == (int) SocketError.InProgress ||
                        ex.ErrorCode == (int) SocketError.NoBufferSpaceAvailable)
                    {
                        // socket buffer is probably empty, wait and try again
                        Thread.Sleep(30);
                    }
                    else
                    {
                        throw ex; // any serious error occurr
                    }
                }
            } while (received < size);

            networkStream.Flush();

            return received;
        }

        private byte[] intToByteArray(int size)
        {
            byte[] sizeInBytes = Encoding.UTF8.GetBytes(size.ToString());

            if (sizeInBytes.Length > sizeBytesCount)
            {
                throw new NotSupportedException("The size cannot be more than " + maxDataSize.ToString());
            }
            else if (sizeInBytes.Length < sizeBytesCount)
            {
                byte[] formatedSizeInBytes = new byte[] {48, 48, 48, 48}; // 48 is Zero in UTF8
                sizeInBytes.CopyTo(formatedSizeInBytes, sizeBytesCount - sizeInBytes.Length);
                sizeInBytes = formatedSizeInBytes;
            }

            return sizeInBytes;
        }

        /// <summary>
        /// This function closes and disposes Network Stream
        /// </summary>
        private void cleanStream()
        {
            if (this.networkStream != null)
            {
                try
                {
                    this.networkStream.Close();
                    this.networkStream.Dispose();
                }
                catch
                {
                    //Well there are very less options here to check if it was open or not
                }

                this.networkStream = null;
            }
        }

        /// <summary>
        /// This function closes and disposes Socket
        /// </summary>
        /// <param name="socket"></param>
        private void cleanSocket()
        {
            if (this.socket != null)
            {
                try
                {
                    this.socket.Close();
                }
                catch
                {
                    //Well there are very less options here to check if it was open or not
                }
                this.socket = null;
            }
        }

        #endregion

        #region IDisposable members

        public void Dispose()
        {
            this.cleanStream();
            this.cleanSocket();
        }

        #endregion
    }
}
