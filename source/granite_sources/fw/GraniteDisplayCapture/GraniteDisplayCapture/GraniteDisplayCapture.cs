using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Nokia.RD;
using Nokia.RD.Communication;
using FuseLib;
using System.Threading;


namespace Nokia.Granite.Display.Capture
{
    public sealed class GraniteDisplayCapture
    {
        private byte graniteObjectId = 0;
        private readonly FuseLoader fuseLoader = null; //Fuse loader that is used to create all Fuse components.
        private readonly ConnectionServices connectionServices = null; //Fuses main connection list services
        private IDtlConnection dtlConnection = null;
        private readonly GraniteWbxmlDocument decoder = null;

        private Connection connection = null;
        private MessageSender messageSender = null;
        public int imageWidth = 0;
        public int imageHeight = 0;

        // constructor
        public GraniteDisplayCapture()
        {
            fuseLoader = new FuseLoader();
            connectionServices = (ConnectionServices)fuseLoader.CreateConnectionServices();
            decoder = new GraniteWbxmlDocument();
        }

        #region Private

        private bool CreateConnection(string connGuid)
        {
            if (connection != null)
            {
                if (!connection.IsConnected)
                {
                    connection.ConnectDevice();
                }

                return true;
            }
                      
            for (int ii = 1; ii <= connectionServices.ConnectionIdentifiers.Count; ii++)
            {
                DtlConnectionIdentifier connectionId = connectionServices.ConnectionIdentifiers[ii];

                if (connGuid == connectionId.Guid)
                {
                    // create dtl connection and attach to it
                    dtlConnection = (DtlConnection)fuseLoader.CreateDtlConnection();
                    dtlConnection.Attach(connectionId);
                }
            }

            if (dtlConnection == null)
            {
                Console.WriteLine("Invalid connection guid given: " + connGuid);
                return false;
            }

            try
            {
                // create connection and connect to device                        
                connection = new Connection(dtlConnection);
                connection.ConnectDevice();
            }
            catch (Exception err)
            {
                Console.WriteLine("Error in connection creation: " + err.ToString());
                dtlConnection.Detach();
                System.Runtime.InteropServices.Marshal.ReleaseComObject(dtlConnection);
                dtlConnection = null;
                
                return false;
            }

            // create message sender
            messageSender = new MessageSender(connection);

            return true;
        }

        private void CloseConnection()
        {
            if (connection != null)
            {
                if (connection.IsConnected)
                {
                    connection.Disconnect();
                }

                if (messageSender != null)
                {
                    messageSender.Dispose();
                    messageSender = null;
                }

                connection.Dispose();
                connection = null;

                if (dtlConnection != null)
                {
                    dtlConnection.Detach();
                    System.Runtime.InteropServices.Marshal.ReleaseComObject(dtlConnection);
                    dtlConnection = null;
                }
            }
        }

        private bool SendTestRequest()
        {
            if (graniteObjectId == 0)
            {
                graniteObjectId = GetGraniteServerObjectID();

                // activate Granite server if object id is not gotten
                if (graniteObjectId == 0)
                {
                    ActivateGraniteServer();

                    graniteObjectId = GetGraniteServerObjectID();
                }
            }

            ClearGraniteServer();

            byte[] testReqByteList = { 0x00, 0x00, 0x10, 0xe1, 0x00, 0x46, 0x62, 0x00, 0xc1, 0x02, 0xff, 0x0d, 0x00, 0x00, 0x00, 0x01, 0x02, 0x01, 0x00, 0x3c, 0x03, 0x20, 0x6a, 0x00, 0xc5, 0x12, 0x03, 0x27, 0x70, 0x68, 0x6f, 0x6e, 0x65, 0x5f, 0x64, 0x69, 0x73, 0x70, 0x6c, 0x61, 0x79, 0x5f, 0x63, 0x61, 0x70, 0x74, 0x75, 0x72, 0x65, 0x27, 0x00, 0x09, 0x80, 0xce, 0x10, 0x01, 0x92, 0x1c, 0x80, 0x83, 0x80, 0x00, 0x1b, 0x85, 0x1e, 0x80, 0x64, 0x1d, 0x80, 0x64, 0x37, 0x86, 0x01, 0x90, 0x01, 0x01 };
            testReqByteList[6] = Convert.ToByte(graniteObjectId);
            
            PhonetMessage testReq = new PhonetMessage(testReqByteList);
            PhonetMessage respMessage = null;

            try
            {
                messageSender.Timeout = 5000;
                messageSender.Send(testReq, out respMessage);

                if (respMessage == null)
                {
                    Console.WriteLine("No response to test request");
                    return false;
                }
            }
            catch (Exception err)
            {
                Console.WriteLine("Error in sending: " + err.ToString());
                return false;
            }
            finally
            {
                testReq.Dispose();
                if (respMessage != null)
                {
                    respMessage.Dispose();
                }                
            }

            return true;
        }

        private List<byte> SendResultRequests()
        {
            byte[] resultReqByteList = { 0x00, 0x00, 0x10, 0xe1, 0x00, 0x12, Convert.ToByte(graniteObjectId), 0x00, 0xda, 0x0f, 0xff, 0x0d, 0x00, 0x00, 0x00, 0x01, 0x06, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00 };
                
            bool messagesToBeSent = true;
            int index = 0;
            List<byte> responseBytes = new List<byte>();

            while (messagesToBeSent)
            {
                if (index != 0)
                {
                    byte[] indexArray = BitConverter.GetBytes(index);

                    for (int i = 0; i < 4; i++)
                    {
                        resultReqByteList[(resultReqByteList.Length - 1) - i] = indexArray[i];
                    }
                }

                PhonetMessage resultReq = new PhonetMessage(resultReqByteList);
                PhonetMessage respMessage = null;
                
                try
                {
                    messageSender.Timeout = 5000;
                    messageSender.Send(resultReq, out respMessage);

                    if (respMessage == null || respMessage.Count == 0)
                    {
                        Console.WriteLine("No response to result request");
                        break;
                    }
                    else
                    {
                        byte[] msgArray = respMessage.ToArray();

                        for (int i = 28; i < msgArray.Length; i++)
                        {
                            responseBytes.Add(msgArray[i]);
                            index += 1;
                        }

                        if (msgArray[12] == 0)
                        {
                            messagesToBeSent = false;
                        }
                    }
                }
                catch (Exception err)
                {
                    Console.WriteLine("Error in sending: " + err.ToString());
                    break;
                }
                finally
                {
                    resultReq.Dispose();
                    if (respMessage != null)
                    {
                        respMessage.Dispose();
                    }
                }
            }

            ClearGraniteServer();

            return responseBytes;
        }

        private void ClearGraniteServer()
        {
            byte[] clearReqByteList = { 0x00, 0x00, 0x10, 0xe1, 0x00, 0x07, Convert.ToByte(graniteObjectId), 0x00, 0x04, 0x14, 0xff, 0x0d, 0x00 };
            PhonetMessage clearReq = new PhonetMessage(clearReqByteList);
            PhonetMessage clearRespMessage = null;

            try
            {
                messageSender.Send(clearReq, out clearRespMessage);

                if (clearRespMessage == null)
                {
                    Console.WriteLine("No response to clear request");
                }

            }
            catch (Exception err)
            {
                Console.WriteLine("Error in sending: " + err.ToString());
            }
            finally
            {
                clearReq.Dispose();
                if (clearRespMessage != null)
                {
                    clearRespMessage.Dispose();
                }
            }
        }

        private byte GetGraniteServerObjectID()
        {
            byte graniteObjectId = 0;
            byte[] nameQuery = { 0x00, 0x00, 0x10, 0xdb, 0x00, 0x0e, 0x00, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0xff, 0x0d, 0xe1, 0xff, 0xff, 0xff, 0xff };

            PhonetMessage nameQueryReq = new PhonetMessage(nameQuery);
            PhonetMessage respMessage = null;;

            try
            {
                messageSender.Send(nameQueryReq, out respMessage);

                if (respMessage != null)
                {
                    byte[] msgArray = respMessage.ToArray();
                    if (msgArray.Length > 21)
                    {
                        graniteObjectId = msgArray[21];
                    }
                }
            }
            catch (Exception err)
            {
                Console.WriteLine("Error in sending: " + err.ToString());
                return 0;
            }
            finally
            {
                nameQueryReq.Dispose();
                if (respMessage != null)
                {
                    respMessage.Dispose();
                }
            }

            return graniteObjectId;
        }

        private bool ActivateGraniteServer()
        {
            byte[] fileCreateReq = { 0x00, 0x00, 0x10, 0x6d, 0x00, 0x56, 0x00, 0x1, 0x14, 0x72, 0x11, 0x1, 0x00, 0x26, 0x00, 0x43, 0x00, 0x3a, 0x00, 0x5c, 0x00, 0x70, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00, 0x65, 0x00, 0x66, 0x00, 0x68, 0x00, 0x69, 0x00, 0x64, 0x00, 0x64, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x66, 0x00, 0x6f, 0x00, 0x6c, 0x00, 0x64, 0x00, 0x65, 0x00, 0x72, 0x00, 0x5c, 0x00, 0x67, 0x00, 0x72, 0x00, 0x61, 0x00, 0x6e, 0x00, 0x69, 0x00, 0x74, 0x00, 0x65, 0x00, 0x2e, 0x00, 0x73, 0x00, 0x74, 0x00, 0x61, 0x00, 0x72, 0x00, 0x74, 0x00, 0x75, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00 };
            byte[] fileWriteReq = { 0x00, 0x00, 0x10, 0x6d, 0x00, 0x7a, 0x00, 0x1, 0x15, 0x58, 0x00, 0x00, 0x10, 0x00, 0x1, 0xd1, 0x00, 0x00, 0x00, 0x6c, 0x54, 0x68, 0x69, 0x73, 0x20, 0x66, 0x69, 0x6c, 0x65, 0x20, 0x69, 0x73, 0x20, 0x75, 0x73, 0x65, 0x64, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x47, 0x72, 0x61, 0x6e, 0x69, 0x74, 0x65, 0x20, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x20, 0x61, 0x63, 0x74, 0x69, 0x76, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x20, 0x44, 0x6f, 0x6e, 0x27, 0x74, 0x20, 0x64, 0x65, 0x6c, 0x65, 0x74, 0x65, 0x20, 0x74, 0x68, 0x69, 0x73, 0x20, 0x69, 0x66, 0x20, 0x79, 0x6f, 0x75, 0x20, 0x61, 0x72, 0x65, 0x20, 0x74, 0x65, 0x73, 0x74, 0x69, 0x6e, 0x67, 0x20, 0x70, 0x68, 0x6f, 0x6e, 0x65, 0x20, 0x73, 0x77, 0x20, 0x77, 0x69, 0x74, 0x68, 0x20, 0x47, 0x72, 0x61, 0x6e, 0x69, 0x74, 0x65, 0x2e };
            byte[] fileCloseReq = { 0x00, 0x00, 0x10, 0x6d, 0x00, 0xa, 0x00, 0x1, 0x16, 0x74, 0x00, 0x00, 0x10, 0x00, 0x1, 0xd1 };
            byte[] resetReq = { 0x00, 0x00, 0x10, 0x15, 0x00, 0x6, 0x00, 0x1, 0x17, 0x6, 0x7, 0x00 };

            List<byte[]> messagesToBeSent = new List<byte[]>();

            messagesToBeSent.Add(fileCreateReq);
            messagesToBeSent.Add(fileWriteReq);
            messagesToBeSent.Add(fileCloseReq);
            messagesToBeSent.Add(resetReq);

            foreach (byte[] message in messagesToBeSent)
            {                
                PhonetMessage messageToBeSent = new PhonetMessage(message);
                PhonetMessage respMessage = null; ;

                try
                {
                    messageSender.Timeout = 10000;
                    messageSender.Send(messageToBeSent, out respMessage);

                    if (respMessage == null)
                    {
                        Console.WriteLine("Error in sending, no response message");
                        return false;
                    }
                }
                catch (Exception err)
                {
                    Console.WriteLine("Error in sending: " + err.ToString());
                    return false;
                }
                finally
                {
                    messageToBeSent.Dispose();
                    if (respMessage != null)
                    {
                        respMessage.Dispose();
                    }
                }

                // wait for a while before next message
                Thread.Sleep(500);
            }

            Console.WriteLine("Waiting for phone to boot up...");
            // wait for phone bootup
            Thread.Sleep(30000);

            // restore connection
            if (!connection.IsConnected)
            {
                connection.ConnectDevice();
            }

            return true;
        }

        #endregion

        #region Public

        public void GetDisplayCapture(string imagePath, string connGuid)
        {            
            CreateConnection(connGuid);

            // check connection status
            if (connection.IsConnected)
            {
                SendTestRequest();
                List<byte> bytes = SendResultRequests();

                if (bytes.Count > 0)
                {
                    decoder.Decode(bytes.ToArray(), imagePath);
                    imageHeight = decoder.bitmapHeight;
                    imageWidth = decoder.bitmapWidth;
                }

                CloseConnection();
            }
            else
            {
                throw new Exception("Phone is not connected!");
            }
        }

        public void GetDisplayCapture(string imagePath, Connection connection)
        {
            // store connection pointer
            this.connection = connection;

            // new messageSender
            if (messageSender == null)
            {
                messageSender = new MessageSender(connection);
            }
            // new messageSender, because connection changed
            else if (messageSender.Connection != connection)
            {
                messageSender.Dispose();
                messageSender = new MessageSender(connection);
            }

            // check connection status
            if (connection.IsConnected)
            {
                SendTestRequest();
                List<byte> bytes = SendResultRequests();

                if (bytes.Count > 0)
                {
                    decoder.Decode(bytes.ToArray(), imagePath);
                    imageHeight = decoder.bitmapHeight;
                    imageWidth = decoder.bitmapWidth;
                }
            }
            else
            {
                throw new Exception("Phone is not connected!");
            }
        }

        public void GetDisplayCapture(string imagePath, MessageSender messageSender)
        {
            // store connection pointer
            this.connection = messageSender.Connection;

            this.messageSender = messageSender;

            // check connection status
            if (this.messageSender.Connection.IsConnected)
            {
                SendTestRequest();
                List<byte> bytes = SendResultRequests();

                if (bytes.Count > 0)
                {
                    decoder.Decode(bytes.ToArray(), imagePath);
                    imageHeight = decoder.bitmapHeight;
                    imageWidth = decoder.bitmapWidth;
                }
            }
            else
            {
                throw new Exception("Phone is not connected!");
            }
        }

        public List<byte> GetDisplayCaptureRaw(string connGuid)
        {
            List<byte> data = new List<byte>();

            CreateConnection(connGuid);

            // check connection status
            if (connection.IsConnected)
            {
                SendTestRequest();
                List<byte> bytes = SendResultRequests();

                if (bytes.Count > 0)
                {
                    data = decoder.Decode(bytes.ToArray());
                    imageHeight = decoder.bitmapHeight;
                    imageWidth = decoder.bitmapWidth;
                }

                CloseConnection();

                return data;
            }
            else
            {
                throw new Exception("Phone is not connected!");
            }
        }

        public List<byte> GetDisplayCaptureRaw(Connection connection)
        {
            // store connection pointer
            this.connection = connection;

            List<byte> data = new List<byte>();

            // new messageSender
            if (messageSender == null)
            {
                messageSender = new MessageSender(connection);
            }
            // new messageSender, because connection changed
            else if (messageSender.Connection != connection)
            {
                messageSender.Dispose();
                messageSender = new MessageSender(connection);
            }

            // check connection status
            if (connection.IsConnected)
            {
                SendTestRequest();
                List<byte> bytes = SendResultRequests();

                if (bytes.Count > 0)
                {
                    data = decoder.Decode(bytes.ToArray());
                    imageHeight = decoder.bitmapHeight;
                    imageWidth = decoder.bitmapWidth;
                }

                return data;
            }
            else
            {
                throw new Exception("Phone is not connected!");
            }
        }

        public List<byte> GetDisplayCaptureRaw(MessageSender messageSender)
        {
            // store connection pointer
            this.connection = messageSender.Connection;

            this.messageSender = messageSender;

            List<byte> data = new List<byte>();

            // check connection status
            if (this.messageSender.Connection.IsConnected)
            {
                //DateTime startTime = DateTime.Now;

                SendTestRequest();

                //DateTime stopTime = DateTime.Now;
                //TimeSpan duration = stopTime - startTime;
                //Console.WriteLine("test request: " + duration);

                //DateTime startTime2 = DateTime.Now;

                List<byte> bytes = SendResultRequests();

                //DateTime stopTime2 = DateTime.Now;
                //TimeSpan duration2 = stopTime2 - startTime2;
                //Console.WriteLine("result requests: " + duration2);

                if (bytes.Count > 0)
                {
                    data = decoder.Decode(bytes.ToArray());
                    imageHeight = decoder.bitmapHeight;
                    imageWidth = decoder.bitmapWidth;
                }

                return data;
            }
            else
            {
                throw new Exception("Phone is not connected!");
            }
        }

        public void PressBackKey(Connection connection)
        {
            // new messageSender
            if (messageSender == null)
            {
                messageSender = new MessageSender(connection);
            }
            // new messageSender, because connection changed
            else if (messageSender.Connection != connection)
            {
                messageSender.Dispose();
                messageSender = new MessageSender(connection);
            }

            // check connection status
            if (connection.IsConnected)
            {
                byte[] kbdBackDown = { 0x00, 0x00, 0x10, 0x0c, 0x00, 0x0e, 0x00, 0x01, 0x02, 0x11, 0x00, 0x01, 0x01, 0x08, 0xe0, 0x7d, 0x01, 0x00, 0x00, 0x00 };
                byte[] kbdBackUp = { 0x00, 0x00, 0x10, 0x0c, 0x00, 0x0e, 0x00, 0x01, 0x03, 0x11, 0x00, 0x01, 0x01, 0x08, 0xe0, 0x7d, 0x00, 0x00, 0x00, 0x00 };

                List<byte[]> messagesToBeSent = new List<byte[]>();

                messagesToBeSent.Add(kbdBackDown);
                messagesToBeSent.Add(kbdBackUp);

                foreach (byte[] message in messagesToBeSent)
                {
                    PhonetMessage messageToBeSent = new PhonetMessage(message);
                    PhonetMessage respMessage = null; ;

                    try
                    {
                        messageSender.Timeout = 10000;
                        messageSender.Send(messageToBeSent, out respMessage);

                        if (respMessage == null)
                        {
                            Console.WriteLine("Error in sending, no response message");
                        }
                    }
                    catch (Exception err)
                    {
                        Console.WriteLine("Error in sending: " + err.ToString());
                    }
                    finally
                    {
                        messageToBeSent.Dispose();
                        if (respMessage != null)
                        {
                            respMessage.Dispose();
                        }
                    }

                    // wait for a while before next message
                    Thread.Sleep(50);
                }
            }
            else
            {
                throw new Exception("Phone is not connected!");
            }
        }

        #endregion
    }
}
