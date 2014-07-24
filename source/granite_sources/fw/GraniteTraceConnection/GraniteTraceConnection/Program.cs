using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using Nokia.RD;
using Nokia.RD.Communication;
using FuseLib;
using Nokia.RD.Tracing.Logging;
using System.Security.Principal;
using System.Security;
using System.Reflection;


namespace Nokia.Granite.TraceConnection
{
    public class GraniteConnectionTester
    {
        static void Main(string[] args)
        {
            //int loops = 10000;
            //int loops = 1;
            //int loops = 5;
            int loops = 100;

            bool connected = false;

            GraniteTraceConnection gtc = new GraniteTraceConnection();
            BackKeyPresser bkp = new BackKeyPresser();

            //CreateConnection("GConnId_1634ac214b0f48e7"); // NoSE
            //CreateConnection("GConnId_27f6d1a2f85144d4"); // USB3
            //gc.CreateConnection("GConnId_27f6d1a2f85144d4"); // USB3

            // NOTE: trace connection must be created first!!!
            gtc.CreateConnection("GConnId_6a64b18c82084f08", "test.blx"); // USB2

            // create connection for back key pressing
            connected = bkp.CreateConnection("GConnId_6a64b18c82084f08"); // USB2

            if (!connected)
            {
                gtc.CloseConnection();
                Console.WriteLine("Phone is not connected!");
            }
            else
            {                                   
                for (int i = 0; i < loops; i++)
                {
                    //gtc.CreateConnection("GConnId_6a64b18c82084f08", "test.blx"); // USB2
                    //gtc.StartRecording("test" + i.ToString() + ".blx");

                    bkp.PressBackKey();
                    Thread.Sleep(100);

                    gtc.SetMarker("terve");

                    if (i > 10)
                    {
                        gtc.SplitBlxFile("renamed_" + i.ToString() + ".blx");
                    }
                    else
                    {
                        gtc.SplitBlxFile();
                    }

                    //gtc2.StopRecording();
                    //gtc.CloseConnection();
                }

                GC.Collect();
                Thread.Sleep(1000000);

                bkp.CloseConnection();
                gtc.CloseConnection();
            }
        }
    }

    public sealed class BackKeyPresser
    {
        private readonly FuseLoader fuseLoader = null; //Fuse loader that is used to create all Fuse components.
        private readonly ConnectionServices connectionServices = null; //Fuses main connection list services
        private IDtlConnection dtlConnection = null;

        private Connection connection = null;
        private MessageSender messageSender = null;

        // constructor
        public BackKeyPresser()
        {
            fuseLoader = new FuseLoader();
            connectionServices = (ConnectionServices)fuseLoader.CreateConnectionServices();
        }

        public bool CreateConnection(string connGuid)
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
                CloseConnection();

                return false;
            }

            return connection.IsConnected;
        }

        public void CloseConnection()
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
                GC.SuppressFinalize(connection);
                connection = null;
            }

            if (dtlConnection != null)
            {
                dtlConnection.Detach();
                System.Runtime.InteropServices.Marshal.ReleaseComObject(dtlConnection);
                dtlConnection = null;
            }
        }

        public void PressBackKey()
        {
            if (connection == null)
            {
                throw new Exception("Phone is not connected!");
            }

            // create messageSender instance if needed
            if (messageSender == null)
            {
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
    }

    //public class ThreadParameter
    //{
    //    public Connection connection { get; set; }
    //}

    //public class DisplayCapturer
    //{
    //    public void TakeCapturesInThread(object parameters)
    //    {
    //        int loops = 10000;
    //        GraniteConnection gdc = new GraniteConnection();

    //        for (int i = 0; i < loops; i++)
    //        {
    //            DateTime startTime = DateTime.Now;

    //            //gdc.GetDisplayCapture("./image.png", "GConnId_27f6d1a2f85144d4");
    //            //gdc.GetDisplayCapture("./image.png", gdc.connection);
    //            //gdc.GetDisplayCapture("./image.png", gdc.messageSender);

    //            //List<byte> data = gdc.GetDisplayCaptureRaw("GConnId_27f6d1a2f85144d4");
    //            //List<byte> data2 = gdc.GetDisplayCaptureRaw(((ThreadParameter)parameters).connection);
    //            //List<byte> data3 = gdc.GetDisplayCaptureRaw(gdc.messageSender);

    //            DateTime stopTime = DateTime.Now;
    //            TimeSpan duration = stopTime - startTime;
    //            Console.WriteLine(duration);
    //            //Console.WriteLine(data2.Count);

    //            //Thread.Sleep(1000);
    //        }
    //    }
    //}

    //CreateConnection (blx name, conn guid)
    //CloseConnection
    //SplitBlxLog (name mandatory)
    //StartRecording (name optional)
    //StopRecording
    //SetMarker (marker string)

}