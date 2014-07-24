package Server;

/**
 * Class for deserializing the information of the RPC call: class name, method name, and an array of parameters
 * 
 * @author 		Sami Utriainen
 * @version 	1.0.0.0
 */
public class RPCCall {
	
	/***
	 * Name of the method
	 */
	String MethodName;
	
	/***
	 * Name of the class
	 */
	String ClassName;
	
	/***
	 * An array of parameters 
	 */
	Object[] Args;
}
