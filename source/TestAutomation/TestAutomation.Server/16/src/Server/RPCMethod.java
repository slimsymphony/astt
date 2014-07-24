package Server;

import java.lang.annotation.*;

/**
 * Annotation for providing the RPC visibility for a method
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
@Target({ ElementType.METHOD })
@Retention(RetentionPolicy.RUNTIME)
public @interface RPCMethod {
	
	/***
	 * Gets the description of the message
	 * 
	 * @return		The description of the message
	 * @since		1.0.0.0
	 */
	String description() default "";
	
	/***
	 * Gets the version since which this method has been available
	 * 
	 * @return		The version since which this method has been available
	 * @since		1.0.0.0
	 */
	String since() default "1.0.0.0";
	
	/***
	 * Gets the usage of this method.
	 * 
	 * @return		the usage of this method
	 * @since		1.0.0.0
	 */
	String usage() default "";
}
