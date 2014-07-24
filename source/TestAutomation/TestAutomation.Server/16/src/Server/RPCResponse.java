package Server;

/**
 * Class for serializing the information for the RPC response: class name, method name, result or error
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public class RPCResponse {
	
	/***
	 * Name of the class
	 */
	public String ClassName;
	
	/***
	 * Name of the method
	 */
	public String MethodName;
	
	/***
	 * Return value
	 */
	public Object Result;
	
	/***
	 * Error message if failed
	 */
	public String Error;
}
