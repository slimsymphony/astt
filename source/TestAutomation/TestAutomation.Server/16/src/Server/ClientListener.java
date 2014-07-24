package Server;

import java.io.*;
import java.net.*;
import java.util.Arrays;
 
/**
 * Class proving the methods for listening RPC messages from a client
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public class ClientListener extends Thread {
    
	private ServerDispatcher m_serverDispatcher;
    private ClientInfo m_clientInfo;
    private InputStream m_in;
    
    /**
     * Class constructor
     * 
     * @param 		clientInfo			Information about the client for which this sender is initialized
     * @param 		serverDispatcher	Instance of a server dispatcher
     * @throws 		IOException
     * @since 		1.0.0.0
     */
    public ClientListener(ClientInfo clientInfo, ServerDispatcher serverDispatcher) throws IOException {
        
    	m_clientInfo = clientInfo;
        m_serverDispatcher = serverDispatcher;
        Socket socket = clientInfo.mSocket;     
        m_in = socket.getInputStream();
    }
 
    /**
     * Until interrupted, reads messages from the client socket, forwards them
     * to the server dispatcher's queue and notifies the server dispatcher.
     * 
     * @since		1.0.0.0
     */
    public void run()
    {
        try {
           
        	while (!isInterrupted()) {
        	   
        	   byte[] buffer = new byte[1024];
        	   
        	   int read = m_in.read(buffer);
        	   
        	   if (read == -1) {
        		   break;
        	   }       	   
        	   
        	   if (read < buffer.length) {
        		   buffer = Arrays.copyOfRange(buffer, 0, read);
        	   }
        	   
        	   RPCMessage rpc = RPCMessage.fromBytes(buffer);
        	   rpc.m_clientInfo = m_clientInfo;
        	   m_serverDispatcher.dispatchMessage(rpc);
        	   
    	   }
        } catch (IOException ioex) {
           // Problem reading from socket (communication is broken)
        	Trace.writeLine(ioex);
        }
 
        // Communication is broken. Interrupt both listener and sender threads
        m_clientInfo.mClientSender.interrupt();
        m_serverDispatcher.unregisterEventListener(m_clientInfo);
    }
}
