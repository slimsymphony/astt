package Server;

/**
 * Enumerator for different message types
 * 
 * @author 		Sami Utriainen
 * @version  	1.0.0.0
 *
 */
public enum MessageType {
	
	MethodCall,
	MethodResponse,
	Event,
	Error,
	Debug;
	
	private static final byte METHOD_CALL = 0x00;
	private static final byte METHOD_RESPONSE = 0x01;
	private static final byte EVENT = 0x02;
	private static final byte ERROR = 0x03;
	private static final byte DEBUG = 0x04;
	
	/**
	 * Casts a byte value into a matching MessageType enum value
	 * 
	 * @param 		value		Byte value which to cast
	 * @return		Matching MessageType enum value
	 * @throws 		IllegalArgumentException
	 * @since		1.0.0.0
	 */
	public static MessageType fromByte(byte value) throws IllegalArgumentException {
		
		switch (value) {
			case METHOD_CALL :
				return MethodCall;
			case METHOD_RESPONSE :
				return MethodResponse;
			case EVENT :
				return Event;
			case ERROR :
				return Error;
			case DEBUG :
				return Debug;
			default :
				throw new IllegalArgumentException(value + "does not map to any MessageType enum");
		}
	}
	
	/**
	 * Casts a MessageType enum value into a matching byte value
	 * 
	 * @param 		value	MessageType enum value which to cast
	 * @return		Matching byte value			
	 * @throws 		IllegalArgumentException 
	 * @since		1.0.0.0
	 */
	public static byte toByte(MessageType value) throws IllegalArgumentException {
		
		switch(value) {
			case MethodCall :
				return METHOD_CALL;
			case MethodResponse :
				return METHOD_RESPONSE;
			case Event :
				return EVENT;
			case Error :
				return ERROR;
			case Debug :
				return DEBUG;
			default :
				throw new IllegalArgumentException("No implementation for enum with " + value + " value.");
		}
	}
}
	
	