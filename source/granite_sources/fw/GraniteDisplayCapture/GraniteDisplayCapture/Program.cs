using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using Nokia.RD;
using Nokia.RD.Communication;
using FuseLib;


namespace Nokia.Granite.Display.Capture
{
    public class GraniteDisplayCapturer
    {
        static void Main(string[] args)
        {
            int loops = 10000;
            //int loops = 1;

            Connection connection = null;

            GraniteDisplayCapture gdc = new GraniteDisplayCapture();
            ConnectionCreator cc = new ConnectionCreator();

            //CreateConnection("GConnId_1634ac214b0f48e7"); // NoSE
            //CreateConnection("GConnId_27f6d1a2f85144d4"); // USB3
            //connection = cc.CreateConnection("GConnId_27f6d1a2f85144d4"); // USB3
            connection = cc.CreateConnection("GConnId_a5c0bb9aee4f432d"); // USB2

            if (connection == null || connection.IsDisconnected)
            {
                cc.CloseConnection();
                Console.WriteLine("Phone is not connected!");
            }
            else
            {
                DisplayCapturer dc = new DisplayCapturer();
                Thread t = new Thread(new ParameterizedThreadStart(dc.TakeCapturesInThread));
                t.Start(new ThreadParameter() { connection = connection });

                /*
                for (int i = 0; i < loops; i++)
                {
                    gdc.PressBackKey(connection);
                    Thread.Sleep(100);
                }
                */

                /*
                for (int i = 0; i < loops; i++)
                {
                    DateTime startTime = DateTime.Now;

                    //gdc.GetDisplayCapture("./image.png", "GConnId_27f6d1a2f85144d4");
                    //gdc.GetDisplayCapture("./image.png", gdc.connection);
                    //gdc.GetDisplayCapture("./image.png", gdc.messageSender);

                    //List<byte> data = gdc.GetDisplayCaptureRaw("GConnId_27f6d1a2f85144d4");
                    List<byte> data2 = gdc.GetDisplayCaptureRaw(connection);
                    //List<byte> data3 = gdc.GetDisplayCaptureRaw(gdc.messageSender);

                    DateTime stopTime = DateTime.Now;
                    TimeSpan duration = stopTime - startTime;
                    Console.WriteLine(duration);
                    Console.WriteLine(data2.Count);

                    //Thread.Sleep(1000);
                }
                */
            }
        }
    }

    public sealed class ConnectionCreator
    {
        private readonly FuseLoader fuseLoader = null; //Fuse loader that is used to create all Fuse components.
        private readonly ConnectionServices connectionServices = null; //Fuses main connection list services
        private IDtlConnection dtlConnection = null;
        private Connection connection = null;

        // constructor
        public ConnectionCreator()
        {
            fuseLoader = new FuseLoader();
            connectionServices = (ConnectionServices)fuseLoader.CreateConnectionServices();
        }

        public Connection CreateConnection(string connGuid)
        {
            if (connection != null)
            {
                if (!connection.IsConnected)
                {
                    connection.ConnectDevice();
                }

                return connection;
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
                return null;
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

                return null;
            }

            if (connection.IsConnected)
            {
                return connection;
            }
            else
            {
                connection.Disconnect();
                connection.ConnectDevice();

                if (connection.IsConnected)
                {
                    return connection;
                }
                else
                {
                    return null;
                }
            }
        }

        public void CloseConnection()
        {
            if (connection != null)
            {
                if (connection.IsConnected)
                {
                    connection.Disconnect();
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
    }

    public class ThreadParameter
    {
        public Connection connection { get; set; }
    }

    public class DisplayCapturer
    {
        public void TakeCapturesInThread(object parameters)
        {
            int loops = 10000;
            GraniteDisplayCapture gdc = new GraniteDisplayCapture();

            for (int i = 0; i < loops; i++)
            {
                DateTime startTime = DateTime.Now;

                //gdc.GetDisplayCapture("./image.png", "GConnId_27f6d1a2f85144d4");
                //gdc.GetDisplayCapture("./image.png", gdc.connection);
                //gdc.GetDisplayCapture("./image.png", gdc.messageSender);

                //List<byte> data = gdc.GetDisplayCaptureRaw("GConnId_27f6d1a2f85144d4");
                List<byte> data2 = gdc.GetDisplayCaptureRaw(((ThreadParameter)parameters).connection);
                //List<byte> data3 = gdc.GetDisplayCaptureRaw(gdc.messageSender);

                DateTime stopTime = DateTime.Now;
                TimeSpan duration = stopTime - startTime;
                Console.WriteLine(duration);
                Console.WriteLine(data2.Count);

                //Thread.Sleep(1000);
            }
        }
    }
}