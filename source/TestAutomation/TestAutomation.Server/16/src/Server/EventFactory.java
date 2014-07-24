package Server;

/***
 * Class for packing events into RPC messages
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 *
 */
public class EventFactory {

	/***
	 * Creates a RPC message from an event
	 * 
	 * @param 		eventType		type of the event		
	 * @param 		eventArgs		Event object itself
	 * @return		RPC message whose type is event
	 * @since		1.0.0.0
	 */
	public static RPCMessage createEvent(Class<?> eventType, Object eventArgs) {
		String type = eventType.getSimpleName();
		String args = Serializer.getInstance().serialize(eventArgs);
		String json = Serializer.getInstance().serialize(new RPCEvent(type, args));
		return new RPCMessage(MessageType.Event,  MessageCounters.getNextEventIndex(), false, (short)0, json);
	}
}
