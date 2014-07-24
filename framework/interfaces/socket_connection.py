"""Socket connection module.
    
    Generic socket level connection. Implementation made both for client 
    and server side.
"""

import socket, sys

import clr

from System.Net.Sockets import Socket, SocketError, AddressFamily, SocketType, \
                               ProtocolType, TcpListener, TcpClient, SocketException
from System.Net import IPEndPoint, IPAddress
from System import Array, Byte
from System.Text import Encoding

# FIXME: Implement also asyncronous message send/recv using callbacks!

def getAvailableSocketPort():
    """Returns available socket port."""
    try:
        sock = Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp)

        # Loopback returns IPV4 address of localhost
        ipAddress = IPAddress.Loopback
        ipLocalEndPoint = IPEndPoint(ipAddress, 0);

        sock.Bind(ipLocalEndPoint)

        localEndPoint = clr.Convert(sock.LocalEndPoint, IPEndPoint)
        
        port = localEndPoint.Port

        sock.Close()
    except socket.error, err:
        # in error situation, 0 is returned
        print 'Socket error in getting available socket port: ', str(err)
        port = 0

    return port
    
def isSocketPortAvailable(port):
    """Checks if given port is available or not.
    
        Parameters

        port        port number (integer 1-65535)
        
        Returns True if port is available, otherwise False.
    """
    assert isinstance(port, int), 'Valid port parameter not given!'

    portAvailable = False

    try:
        sock = Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp)
        # Don't allow another socket to bind to this port
        sock.ExclusiveAddressUse = True

        # try binding to given port, if it succeeds port is available
        
        # Loopback returns IPV4 address of localhost
        ipAddress = IPAddress.Loopback
        ipLocalEndPoint = IPEndPoint(ipAddress, port);

        sock.Bind(ipLocalEndPoint)

        sock.Close()
        portAvailable = True
    except OSError, err:
        # socket is either in use or other error occurred
        #print 'Socket error in checking port availability: ', str(err)
        pass

    return portAvailable

class SocketTimeoutException(Exception):
    """Exception class for socket timeout exceptions."""
    pass

class SocketErrorException(Exception):
    """Exception class for socket error exceptions."""
    pass

class SocketNonBlockingException(Exception):
    """Exception class for non blocking socket when no data is available."""
    pass

class SocketConnection(object):
    """Base class for socket connection.

        Includes methods for reading and writing to/from tcp/ip socket.
    """
    MESSAGE_TERMINATOR = '\n'
    # FIXME: What is the best string to replacement?
    MESSAGE_TERMINATOR_REPLACEMENT = '?#-'
    MAX_MESSAGE_LENGTH = 1638400
    
    def __init__(self):
        self._socketServer = None   # TcpListener instance
        self._socketClient = None   # TcpClient instance
        self._stream = None         # stream object for message send/receive
        
    def sendMessage(self, message, dataPickled = False ):
        """Sends string trough socket, adds message terminator to end."""
        assert self.isOpen(), 'Connection was not open!'

        # if MESSAGE_TERMINATOR character is used inside the message,
        # replace it with MESSAGE_TERMINATOR_REPLACEMENT
        if not dataPickled:
            message = message.replace(self.MESSAGE_TERMINATOR,
                                  self.MESSAGE_TERMINATOR_REPLACEMENT)

        # cut message if it is too long
        # this should be OK if we know that end part of message is always
        # freeform text
        # MESSAGE_TERMINATOR length is 1
        if len(message) >= self.MAX_MESSAGE_LENGTH - 1:
            message = message[:self.MAX_MESSAGE_LENGTH - 4] + '...'
            debug.err('Message was splitted! (length of message to be sent %s)' % len(message))

        if not dataPickled:
            # add message terminator to the end
            message += self.MESSAGE_TERMINATOR

        msgArray = Encoding.UTF8.GetBytes(message)

        try:
            self._stream.Write(msgArray, 0, msgArray.Length)
        except SocketError, err:
            raise SocketErrorException

        # FIXME: how to check that all data is sent??
        #try:
        #    bytesSent = self.connFile.write(message + self.MESSAGE_TERMINATOR)        
        #    self.connFile.flush()
        #except socket.error:
        #    raise SocketErrorException

    def receiveMessage(self, timeout = None, dataPickled = False):
        """Reads data from socket stream.
        
            Parameters

            timeout         timeout in milliseconds (default = None --> infinite)
        """
        assert self.isOpen(), 'Connection was not open!'

        recvBuf = Array.CreateInstance(Byte, self.MAX_MESSAGE_LENGTH)
                
        if timeout is not None:
            self._stream.ReadTimeout = timeout

        try:
            recvData = ''
            dataIndex = None
            
            # loop to receive all the data
            while dataIndex != 0:
                dataIndex = self._stream.Read(recvBuf, 0, recvBuf.Length)
                #print 'dataIndex: ', dataIndex
                
                # Translate data bytes to a UTF8 string
                recvData = Encoding.UTF8.GetString(recvBuf, 0, dataIndex)

                # process received message
                # if MESSAGE_TERMINATOR_REPLACEMENT character is inside the data,
                # replace it with MESSAGE_TERMINATOR
                

                if not dataPickled:
                    recvData = recvData.replace(self.MESSAGE_TERMINATOR_REPLACEMENT,
                                            self.MESSAGE_TERMINATOR)
                    return recvData[:-1] # remove \n from end of string
                else:
                    return recvData

        except IOError, IOerr:            
            # FIXME: Study why IOError is given here instead of 
            #        SocketException which should be coming according to documentation
            raise SocketTimeoutException
        except SocketError, err:
            if err == SocketError.TimedOut:
                raise SocketTimeoutException
            else:
                #if timeout is not 0:
                raise SocketErrorException
                #else:
                #    raise SocketNonBlockingException
        
    def disconnect(self):
        """Close socket connection either from client or server."""
        if self.isOpen():
            if self._socketServer:
                self._socketServer.Stop()
            elif self._socketClient:
                self._socketClient.Close()

    def isOpen(self):
        """Returns if the socket is open or not."""
        return self._stream != None
        #if self._socketserver:
        #    print 'self._socketserver.server.connected: ', self._socketserver.server.connected
        #    self._socketserver.server.connected
        #elif self._socketclient:    
        #    print 'self._socketclient.active: ', self._socketclient.active
        #    return self._socketclient.active

class SocketClient(SocketConnection):
    """Class for socket client.

        Includes methods for connecting to socket server.
    """
    #def __init__(self, host = "127.0.0.1", port = 31336):
    #    """Initialize socket client as TcpClient.
    #    
    #        Parameters
    #       
    #        host        tcp/ip address of the host (default = "127.0.0.1")
    #        port        port number    (default = 31336)
    #    """
    #    SocketConnection.__init__(self)

    #    try:
    #        # create client instance and connect to server
    #        TcpClient.__init__(self, host, port)
    #    except (SocketError, OSError), err:
    #        raise 'Error in connecting to socket server: ', str(err)
    #    else:
    #        # get a client stream for reading and writing
    #        self._stream = self.GetStream()
    #        print 'client self._stream: ', self._stream
    #        
    #        # store that we have now socket client in SocketConnection class
    #        self._socketClient = True

    def connectToSocketServer(self, host = "127.0.0.1", port = 31336):        
        """Open connection to socket server.

        Parameters

            host (Str) default "127.0.0.1"
            port (int) default 31336

        Returns True  when connection is established.
        Otherwise returns False
        """
        try:
            # create client instance and connect to server
            client = TcpClient(host, port)
        except (SocketError, OSError), err:
            print 'Error in connecting to socket server: ', str(err)
            return False
        else:
            # get a client stream for reading and writing
            self._stream = client.GetStream()
            
            # store server as socket object
            self._socketClient = client

            return True

class SocketServer(SocketConnection):
    """Class for socket server.

        Includes methods for creating socket server.
    """
    #def __init__(self, address = "127.0.0.1", port = 31336):
    #    """Initialize socket server as TcpListener.
    #    
    #        Parameters

    #        address     tcp/ip address (default = "127.0.0.1")
    #        port        port number    (default = 31336)
    #    """
    #    SocketConnection.__init__(self)

    #    TcpListener.__init__(self, IPAddress.Parse(address), port)
    #    self.ExclusiveAddressUse = True
    #  
    #    try:
    #        # start listening for client requests
    #        self.Start()
    #    except (SocketError, OSError), err:            
    #        self.Stop()
    #        raise 'Error in socket binding: ', str(err)

    #def waitForConnection(self):
    #    """Start waiting for client connection.
    #    
    #       Returns True when client connection has been made,
    #       False in error situations.
    #    """
    #    try:
    #        # start waiting for client connection
    #        client = self.AcceptTcpClient();
    #        print 'Socket connection from: ', client        

    #        # Get a stream object for reading and writing
    #        self._stream = client.GetStream()
    #        print 'server self._stream: ', self._stream

    #        # store that we have now socket server in SocketConnection class
    #        self._socketServer = True
    #    except (SocketError, OSError), err:
    #        print 'Error in client connection: ', str(err)
    #        self.Stop()
    #        return False

    #    return True
        
    def startServer(self, address = "127.0.0.1", port = 31336):
        """Start the socket server to wanted address and port.

        address         -- TCP/IP addressr (default = "127.0.0.1")
        port            -- Port number     (default = 31336)

        Blocks until client connects to server and 
        returns True when client has connected to server.
        False is returned if something goes wrong.
        """
        server = TcpListener(IPAddress.Parse(address), port)
        # Don't allow another socket to bind to this port
        server.ExclusiveAddressUse = True
      
        try:
            # start listening for client requests
            server.Start()
        except (SocketError, OSError), err:
            print 'Error in socket binding: ', str(err)
            server.Stop()
            return False
        else:
            # start waiting for client connection
            client = server.AcceptTcpClient();
            #print 'Socket connection from: ', client        

            # Get a stream object for reading and writing
            self._stream = client.GetStream()

            # store server as socket object
            self._socketServer = server

            return True
            