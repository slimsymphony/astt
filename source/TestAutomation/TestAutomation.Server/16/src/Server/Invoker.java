package Server;

/**
 * Interface for implementing a method invoker
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public interface Invoker {
	
	/***
	 * Tries to invoke a method with given parameters from a given class (name)
	 * 
	 * @param 		className		Name of the class from which to invoke the method
	 * @param 		methodName		Name of the method to invoke
	 * @param 		args			Parameters for the method
	 * @return		Any return value from the method invocation; null with return type of void
	 * @throws 		Exception		Thrown if class not found
	 * @since		1.0.0.0
	 */
	public Object invoke(String className, String methodName, Object[] args) throws Exception;
}
