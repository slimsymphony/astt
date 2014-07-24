package Server;

import java.util.*;

/**
 * The class, which handles all the messaging in this server
 * 
 * @author 		Sami Utriainen
 * @version 	1.0.0.0
 */
public class ServerDispatcher extends Thread {
    
	private List<RPCMessage> m_messageInbox = new ArrayList<RPCMessage>();
    private List<ClientInfo> m_eventListeners = new ArrayList<ClientInfo>();
    private Invoker m_invoker = null;
    
    /**
     * Gets an amount the currently registered event listeners
     * 
     * @return		An amount the currently registered event listeners
     * @since		1.0.0.0
     */
    public synchronized int getEventListenerCount() {
    	return m_eventListeners.size();
    }
    
    /**
     * Sets the method invoker implementation for the actual invoker
     * 
     * @param 		invoker		The invoker implementation
     * @since		1.0.0.0
     */
    public synchronized void setInvoker(Invoker invoker) {
    	m_invoker = invoker;
    }
    
    /**
     *
     * Adds a given client to the server's event listener list.
	 * 
     * @param 		clientInfo		Listener to be added
  	 * @since		1.0.0.0
     */
    public synchronized void registerEventListener(ClientInfo clientInfo) {
        
    	m_eventListeners.add(clientInfo);
    }
 
    /**
     * Deletes given client from the server's event listener list
     * if the client is in the list.
     *
     * @param 		clientInfo		Lister client to be removed
  	 * @since		1.0.0.0
     */
    public synchronized void unregisterEventListener(ClientInfo clientInfo) {
        
    	int clientIndex = m_eventListeners.indexOf(clientInfo);
        if (clientIndex != -1)
        	m_eventListeners.remove(clientIndex);
    }
 
    /**
     * Adds given message to the dispatcher's message queue and notifies this
     * thread to wake up the message queue reader (getNextMessageFromQueue method).
     * dispatchMessage method is called by other threads (ClientListener) when
     * a message is arrived.
     *
     * @param 		message		RPCMesage to be dispatched
	 * @since		1.0.0.0
     */
    public synchronized void dispatchMessage(RPCMessage message) {
    	
    	m_messageInbox.add(message);
        notify();
    }
    
    /**
     * Gets and deletes the next message from the message queue. If there is no
     * messages in the queue, falls in sleep until notified by dispatchMessage method.
     *
     * @return		Next (FIFO) message in the queue
     * @throws 		InterruptedException
	 * @since		1.0.0.0
     */
    private synchronized RPCMessage getNextMessageFromInbox() throws InterruptedException {
        
    	while (m_messageInbox.size()==0) {
           wait();
    	}
        
    	RPCMessage message = m_messageInbox.get(0);
    	m_messageInbox.remove(0);
        return message;
    }
 
    /**
     * Sends given message to all clients in the client list. Actually the
     * message is added to the client sender thread's message queue and this
     * client sender thread is notified.
     *
     * @param 		message		Message, usually type of Event, to be send
	 * @since		1.0.0.0
     */
    private synchronized void broadcastEventToListeners(RPCMessage message) {
    	for (int i=0; i < m_eventListeners.size(); i++) {
           ClientInfo clientInfo = m_eventListeners.get(i);
           clientInfo.mClientSender.sendMessage(message);
        }
    }
    
    /**
     * Sends a message to the requesting client 
     * 
     * @param 		message		Message, usually type of MethodResponse, to be send
	 * @since		1.0.0.0
     */
    private synchronized void sendMessageToClient(RPCMessage message) {
        message.m_clientInfo.mClientSender.sendMessage(message); //How beautiful this line of code is?
    }
    
    /**
     * Invokes a RPC call in an own thread: therefore we don't waste time in reading the other requests from the queue
     * 
     * @param 		message		RPCMessage, type of MethodCall
     * @since		1.0.0.0
     */
    private synchronized void invoke(RPCMessage message) {

    	InvokeAction action = new InvokeAction(this, m_invoker, message);
    	action.start();
    }
    
    /**
     * Infinitely reads messages from the queue and dispatch them
     * to client(s) connected to the server.
     * 
	 * @since		1.0.0.0
     */
    public void run() {
    	
    	try {
           
    		while (true) {
        	
    			RPCMessage message = getNextMessageFromInbox(); //blocking call until there's something to read
    			
    			//Message's type is an event: we broadcast it to all subscribing clients
    			if (message.getMessageType() == MessageType.Event) {
    				broadcastEventToListeners(message);
    			}
    			//Message's type is method call, we pass it to invoker
    			else if (message.getMessageType() == MessageType.MethodCall) {
    				invoke(message);
    			}
    			//Message's type is method response, we send it to calling client
    			else if (message.getMessageType() == MessageType.MethodResponse) {
    				sendMessageToClient(message);
    			}
           }
        } catch (InterruptedException ie) {
           // Thread interrupted. Stop its execution
        	Trace.writeLine(ie);
        }
    }
}