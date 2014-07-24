using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using Nokia.RD;
using Nokia.RD.Communication;
using FuseLib;
using System.Threading;
using Nokia.RD.Tracing.Logging;
using System.IO;


namespace Nokia.Granite.TraceConnection
{
    public sealed class GraniteTraceConnection
    {
        private readonly FuseLoader fuseLoader = null; //Fuse loader that is used to create all Fuse components.
        private readonly ConnectionServices connectionServices = null; //Fuses main connection list services
        private IDtlConnection dtlConnection = null;

        private Connection connection = null;
        private MessageSender messageSender = null;
        private BinaryLog binaryLog = null;
        private MessageRecorder messageRecorder = null;

        public MessageSender MessageSender
        {
            get
            {
                return messageSender;
            }
        }
        // constructor
        public GraniteTraceConnection()
        {
            fuseLoader = new FuseLoader();
            connectionServices = (ConnectionServices)fuseLoader.CreateConnectionServices();
        }

        #region Private

        private bool CheckBlxFilePath(string blxFilePath)
        {
            if (blxFilePath == "")
            {
                return false;
            }

            string blxDir = Path.GetDirectoryName(blxFilePath);
            bool dirExists = Directory.Exists(blxDir);

            if (blxDir == "" || dirExists)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        #endregion

        #region Public

        public Connection CreateConnection(string connGuid, string blxFileName = "")
        {
            if (connection != null)
            {
                if (!connection.IsConnected)
                {
                    connection.ConnectDevice();
                    messageSender = new MessageSender(connection);
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

                if (connection.IsConnected)
                {
                    connection.Disconnect();
                }

                StartRecording(blxFileName);

                connection.ConnectDevice();
                messageSender = new MessageSender(connection);
            }
            catch (Exception err)
            {
                Console.WriteLine("Error in connection creation: " + err.ToString());

                CloseConnection();
                
                return null;
            }

            if (connection.IsConnected)
            {
                return connection;
            }
            else
            {
                try
                {
                    connection.Disconnect();

                    StartRecording(blxFileName);

                    connection.ConnectDevice();
                    messageSender = new MessageSender(connection);
                }
                catch (Exception err)
                {
                    Console.WriteLine("Error in connection creation: " + err.ToString());

                    CloseConnection();


                    return null;
                }

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
                StopRecording();

                if (messageSender != null)
                {
                    messageSender.Dispose();
                    messageSender = null;
                }
                if (binaryLog != null)
                {
                    binaryLog.Dispose();
                    binaryLog = null;
                }

                if (messageRecorder != null)
                {
                    messageRecorder.Dispose();
                    messageRecorder = null;
                }
                
                if (connection.IsConnected)
                {
                    connection.Disconnect();
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

        public void StartRecording(string blxFileName = "")
        {
            if (messageRecorder != null && binaryLog != null)
            {
                if (CheckBlxFilePath(blxFileName))
                {
                    if (binaryLog.IsOpen)
                    {
                        binaryLog.Rename(blxFileName);
                    }
                    else
                    {
                        binaryLog.Create(blxFileName, "Granite", "", "", true, 0L);
                    }
                }

                messageRecorder.StartRecording();
            }
            else if (messageRecorder == null && binaryLog == null)
            {
                if (CheckBlxFilePath(blxFileName))
                {
                    binaryLog = new BinaryLog();
                    binaryLog.Create(blxFileName, "Granite", "", "", true, 0L);

                    messageRecorder = new MessageRecorder(connection, binaryLog);
                    messageRecorder.StartRecording();
                }
            }
        }

        public void StopRecording()
        {
            if (messageRecorder != null)
            {
                messageRecorder.StopRecording();
            }

            if (binaryLog != null && binaryLog.IsOpen)
            {
                binaryLog.Close();
            }
        }

        public void SplitBlxFile(string blxFileName = "")
        {
            if (binaryLog != null)
            {
                if (CheckBlxFilePath(blxFileName))
                {
                    binaryLog.Rename(blxFileName);
                }
                                
                binaryLog.SplitFile();
            }
        }

        public void SetMarker(string markerString)
        {
            if (binaryLog != null)
            {
                TextMessage blxMarkerMsg = new TextMessage(markerString);
                binaryLog.Append(blxMarkerMsg);
                blxMarkerMsg.Dispose();
            }
        }

        #endregion
    }
}
