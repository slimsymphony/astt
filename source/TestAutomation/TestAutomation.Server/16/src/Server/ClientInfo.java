package Server;

import java.net.Socket;

/**
 * Class containing the needed information in order or to communicate with a client
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 *
 */
public class ClientInfo {
    
	/***
	 * Client's socket
	 */
	public Socket mSocket = null;
    
	/***
	 * Thread which listens messages from a client
	 */
	public ClientListener mClientListener = null;
    
	/***
	 * Thread which sends messages to a client
	 */
	public ClientSender mClientSender = null;
}