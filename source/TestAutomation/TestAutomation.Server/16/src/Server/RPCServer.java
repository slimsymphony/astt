package Server;

import java.io.IOException;
import java.net.BindException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;

import android.util.Log;

/**
 * RPCServer class 
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public class RPCServer extends Thread {
	
	private ServerSocket m_serverSocket = null;
	private ServerDispatcher m_serverDispatcher = null;
	private boolean m_isListening = false;
	private boolean m_closing = false;
	private static RPCServer m_instance = null;
	
	/***
	 * Kills/closes the server 
	 * 
	 * @since		1.0.1.0
	 */
	public void kill() {
		
		if (m_serverSocket != null && m_isListening) {
			try	{
				m_closing = true;			
				m_serverSocket.close();
			} catch (IOException ioe) {
				Trace.writeLine(ioe);
			}
		}
	}
	
	/**
	 * Private class constructor as we provide only a singleton instance
	 * 
	 * @since		1.0.0.0
	 */
	private RPCServer() {
		m_isListening = init();
	}
	
	/**
	 * Gets the singleton instance of the class
	 * 
	 * @return		The singleton instance of the class
	 * @since		1.0.0.0
	 */
	public static RPCServer getInstance() {
		
		if (m_instance == null) {
			m_instance = new RPCServer();
		}
		return m_instance;
	}
	
	/**
	 * Gets the amount of subscribing event listeners
	 * 
	 * @return		The amount of subscribing event listeners
	 * @since		1.0.0.0
	 */
	public synchronized int getEventListenerCount() {
		return m_serverDispatcher.getEventListenerCount();
	}
	
	/**
	 * Returns a value indicating whether the server is running
	 * 
	 * @return		A value indicating whether the server is running
	 * @since		1.0.0.0
	 */
	public boolean isListening() {
		return m_isListening;
	}
	
	/**
	 * Sets the invoker which is used for RPC method invocations
	 * 
	 * @param 		Invoker which is used for RPC method invocations
	 * @since		1.0.0.0
	 */
	public void setInvoker(Invoker invoker)
	{
		m_serverDispatcher.setInvoker(invoker);
	}
	
	/***
	 * Broadcasts an event to subscribed event listeners
	 * 
	 * @param 		eventArgs		Event object
	 * @since		1.0.0.0
	 */
	public synchronized void broadcastEvent(Object eventArgs) {
		broadcastEvent(eventArgs.getClass(), eventArgs);
	}
	
	/***
	 * Broadcasts an event to subscribed event listeners
	 * 
	 * @param 		eventType		Class of an event
	 * @param 		eventArgs		Event object
	 * @since		1.0.0.0
	 */
	public synchronized void broadcastEvent(Class<?> eventType, Object eventArgs) {
		m_serverDispatcher.dispatchMessage(EventFactory.createEvent(eventType, eventArgs));
	}
	
	/**
	 * Gets listening port from cmd args; or if not found, get the default value
	 * 
	 * @return		Listening port
	 * @since		1.0.0.0
	 */
	private int getListeningPort() {
		
		if (Environment.getCommandLineArgs().containsKey("port")) {
			
			try {
				return Integer.parseInt(Environment.getCommandLineArgs().getString("port"));
			} catch (Exception e) {		
			}
		}
		
		return Constants.DEFAULT_LISTENING_PORT;
	}
	
	/**
	 * Inits the server: binds to the listening port, and starts the dispatcher
	 * 
	 * @return		True if successfully initialized; false otherwise
	 * @since		1.0.0.0
	 */
	private boolean init() {
			
		m_serverDispatcher = new ServerDispatcher();
		
		int port = getListeningPort();
		
		boolean success = false;
		
		try {
			m_serverSocket = new ServerSocket(port);
			m_serverSocket.setReuseAddress(true);
			success = true;
		} catch (Exception ex) {
        	
			if (ex instanceof IOException || ex instanceof BindException) {
				String message = "Failed to bind the server port to: " + port;
				Trace.writeLine(message);
				Log.e("TAServer", message);
				try {
					m_serverSocket = new ServerSocket(0); //0 gets it from OS
					message = "Instead, got port: " + m_serverSocket.getLocalPort();
					success = true;
					Trace.writeLine(message);
					Log.e("TAServer", message);
				 } catch (Exception e) {
					 Trace.writeLine("PORT=ERROR");
					 return false;
				 }
        	}
			else {
				Trace.writeLine(ex);
			}
        }
 		
		if (success) {
			Trace.writeLine("PORT=" + m_serverSocket.getLocalPort());
        	m_serverDispatcher.start();
		}
		return success;
	}
	
	/**
	 * Starts running the server in an own thread
	 * 
	 * @since		1.0.0.0
	 */
	public void run() {
		
		m_isListening = true;
        // Accept and handle client connections
        while (true) {
           
        	try {
               
        	   Socket socket = m_serverSocket.accept();
        	   socket.setSoLinger(true, 0);
               ClientInfo clientInfo = new ClientInfo();
               clientInfo.mSocket = socket;
               ClientListener clientListener = new ClientListener(clientInfo, m_serverDispatcher);
               ClientSender clientSender = new ClientSender(clientInfo, m_serverDispatcher);
               clientInfo.mClientListener = clientListener;
               clientInfo.mClientSender = clientSender;
               clientListener.start();
               clientSender.start();
                 
		   } catch (IOException ioe) {
			   m_isListening = false;
			   if (!m_closing) {
				   Trace.writeLine("SERVER=ERROR");
			   	   Trace.writeLine(ioe);
			   }
			   else {
				   Trace.writeLine("Closed.");
				   break;
			   }
		   } 
        }
	}
}
