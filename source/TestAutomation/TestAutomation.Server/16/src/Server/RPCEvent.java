package Server;

/***
 * Class for serializing an RCP event. This is a special class as it is actually used for 
 * storing Json inside Json 
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public class RPCEvent {
	
	/***
	 * Parametreless class constructor (needed by serializer)
	 * @since		1.0.0.0
	 */
	public RPCEvent() {
	}
	
	/***
	 * Class constructor
	 * 
	 * @param 		eventType		Simple name of the type/class of the event
	 * @param 		eventArgs		Json serialized event object
	 * @since		1.0.0.0
	 */
	public RPCEvent(String eventType, String eventArgs) {
		EventType = eventType;
		EventArgs = eventArgs;
	}
	
	/***
	 * Simple name of the event type/class
	 */
    public String EventType;
    
    /***
     * Json serialized event object
     */
    public String EventArgs; 
}
