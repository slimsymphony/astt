package Server;

import java.io.*;
import java.net.*;
import java.util.*;
 
/**
 * Class proving the methods for sending RPC messages for a client
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public class ClientSender extends Thread {
    
	private List<RPCMessage> m_outbox = new ArrayList<RPCMessage>();
    private ServerDispatcher m_serverDispatcher;
    private ClientInfo m_clientInfo;
    private OutputStream m_out;
 
    /**
     * Class constructor
     * 
     * @param 		clientInfo			Information about the client for which this sender is initialized
     * @param		serverDispatcher	Instance of a server dispatcher
     * @throws 		IOException
     * @since		1.0.0.0
     */
    public ClientSender(ClientInfo clientInfo, ServerDispatcher serverDispatcher) throws IOException {
        
    	m_clientInfo = clientInfo;
        m_serverDispatcher = serverDispatcher;
        Socket socket = clientInfo.mSocket;
        m_out = socket.getOutputStream();
    }
     
    /**
     * Adds given message to the message queue and notifies this thread
     * (actually getNextMessageFromQueue method) that a message is arrived.
     * sendMessage is called by other threads (ServeDispatcher).
     * 
     * @param 		message
     * @since		1.0.0.0
     */
    public synchronized void sendMessage(RPCMessage message) {
    	
    	m_outbox.add(message);
        notify();
    }
 
    /**
     * Gets and deletes the next message from the message queue. If the queue is empty, 
     * falls in sleep until notified for message arrival by sendMessage method.
     * 
     * @return		
     * @throws 		InterruptedException
     * @since		1.0.0.0
     */
    private synchronized RPCMessage getNextMessageFromOutBox() throws InterruptedException {
        
    	while (m_outbox.size()==0) {
           wait();
        }
    	RPCMessage message = m_outbox.get(0);
        m_outbox.remove(0);
        return message;
    }
 
    /**
     * Sends given message to the client's socket.
     * 
     * @param 		message
     * @since		1.0.0.0
     */
    private synchronized void sendMessageToClient(RPCMessage message) {
        
    	try {
    		//If the size of the message exceeds the maximum packet size, we split and send the message in chunks
    		if (message.getMessageLength() > Constants.MAX_PACKET_SIZE) {	   			
    			for(RPCMessage msg : message.getMessageChunks(Constants.MAX_PACKET_SIZE)) {
    				m_out.write(msg.getBytes());
    				m_out.flush();
    			}
    		}
    		else {
    			m_out.write(message.getBytes());
    			m_out.flush();
    		}
		} catch (Exception e) {
			Trace.writeLine(e);
		}
    }
 
    /**
     * Until interrupted, reads messages from the message queue
     * and sends them to the client's socket.
     * 
     * @since		1.0.0.0
     */
    public void run() {
        
    	try {
           
        	while (!isInterrupted()) {
        	   RPCMessage message = getNextMessageFromOutBox();
               sendMessageToClient(message);
           }
        } 
        catch (InterruptedException ie) {
        	//This we don't trace
        }
        catch (Exception e) {
           // Communication problem
        	Trace.writeLine(e);
        }
 
        // Communication is broken. Interrupt both listener and sender threads
        m_clientInfo.mClientListener.interrupt();
        m_serverDispatcher.unregisterEventListener(m_clientInfo);
    }
 
}