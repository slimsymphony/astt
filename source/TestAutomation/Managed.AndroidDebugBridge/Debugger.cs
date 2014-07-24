using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Net.Sockets;
using System.Net;

namespace Managed.Adb
{
    /// <summary>
    /// 
    /// </summary>
    public class Debugger : IPacketConsumer
    {
        /// <summary>
        /// 
        /// </summary>
        public enum ConnectionStates
        {
            NotConnected = 1,
            AwaitShake = 2,
            Ready = 3
        }
        
        /// <summary>
        /// 
        /// </summary>
        private const int INITIAL_BUF_SIZE = 1 * 1024;
        
        /// <summary>
        /// 
        /// </summary>
        private const int MAX_BUF_SIZE = 32 * 1024;

        /// <summary>
        /// 
        /// </summary>
        private const int PRE_DATA_BUF_SIZE = 256;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="client"></param>
        /// <param name="listenPort"></param>
        public Debugger(IClient client, int listenPort)
        {
            Client = client;
            ListenPort = listenPort;

            IPEndPoint endPoint = new IPEndPoint(IPAddress.Loopback, listenPort);
            ListenChannel = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            ListenChannel.Blocking = false;
            ListenChannel.ExclusiveAddressUse = false;
            ListenChannel.Bind(endPoint);

            ConnectionState = ConnectionStates.NotConnected;
            Log.d("ddms", ToString());
        }

        /// <summary>
        /// 
        /// </summary>
        public BinaryReader ReadBuffer { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public BinaryWriter PreDataBuffer { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public Socket ListenChannel { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public Socket Channel { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public IClient Client { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public int ListenPort { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public ConnectionStates ConnectionState { get; set; }

        /// <summary>
        /// 
        /// </summary>
        public bool IsDebuggerAttached { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public void Read()
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public /*JdwpPacket*/ Object GetJdwpPacket()
        {
            throw new NotImplementedException();
        }

        // TODO: JdwpPacket
        /// <summary>
        /// 
        /// </summary>
        /// <param name="packet"></param>
        public void ForwardPacketToClient( /*JdwpPacket*/ Object packet)
        {
            Client.SendAndConsume(packet);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public bool SendHandshake()
        {
            throw new NotImplementedException();
        }

        //TODO: JdwpPacket
        /// <summary>
        /// 
        /// </summary>
        /// <param name="packet"></param>
        public void SendAndConsume( /*JdwpPacket*/ Object packet)
        {
            if (Channel == null)
            {
                /*
                 * Buffer this up so we can send it to the debugger when it
                 * finally does connect.  This is essential because the VM_START
                 * message might be telling the debugger that the VM is
                 * suspended.  The alternative approach would be for us to
                 * capture and interpret VM_START and send it later if we
                 * didn't choose to un-suspend the VM for our own purposes.
                 */
                //Log.d ( "ddms", "Saving packet 0x" + packet.ID.ToString ( "X" ) );
                //packet.MovePacket ( PreDataBuffer );
            }
            else
            {
                //packet.WriteAndConsume ( Channel );
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public Socket Accept()
        {
            return Accept(ListenChannel);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="listenChan"></param>
        /// <returns></returns>
        public Socket Accept(Socket listenChan)
        {
            lock (listenChan)
            {
                if (listenChan != null)
                {
                    Socket newChan = listenChan.Accept();
                    if (Channel != null)
                    {
                        Log.w("ddms", "debugger already talking to " + Client.ToString() + " on " + ListenPort.ToString());
                        newChan.Close();
                        return null;
                    }

                    Channel = newChan;
                    Channel.Blocking = false;
                    ConnectionState = ConnectionStates.AwaitShake;
                    return Channel;
                }

                return null;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void CloseData()
        {
            try
            {
                if (Channel != null)
                {
                    Channel.Close();
                    Channel = null;
                    ConnectionState = ConnectionStates.NotConnected;

                    //TODO: ClientData
                    /*ClientData cd = Client.ClientData;
                    cd.DebuggerConnectionStatus = DebuggerStatus.Default;*/
                    Client.Update(ClientChangeMask.ChangeDebuggerStatus);

                }
            }
            catch (IOException ioe)
            {
                Log.w("ddms", ioe);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void Close()
        {
            try
            {
                if (ListenChannel != null)
                {
                    ListenChannel.Close();
                }
                ListenChannel = null;
                CloseData();
            }
            catch (IOException ioe)
            {
                Log.w("ddms", ioe);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            // mChannel != null means we have connection, ST_READY means it's going
            return "[Debugger " + ListenPort + "-->" + Client.ClientData/*.Pid*/
                            + ((ConnectionState != ConnectionStates.Ready) ? " inactive]" : " active]");
        }
    }
}
