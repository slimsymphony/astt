package Server;

import java.lang.reflect.InvocationTargetException;

/**
 * An instance of this class is created and started in order to perform any method invocation request.
 * This way our dispatcher won't be too busy with the invocation itself, and will be free to handle other
 * requests quickly.  
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public class InvokeAction extends Thread {
	
	private Invoker m_invoker = null;
	private RPCMessage m_message = null;
	private ServerDispatcher m_dispatcher = null; 
		
	/**
	 * Class constructor
	 * 
	 * @param 		dispatcher		Dispatcher for which to dispatch the response message
	 * @param 		invoker			Invoker which to invoke
	 * @param 		message			The original request message
	 * @since		1.0.0.0
	 */
	public InvokeAction(ServerDispatcher dispatcher, Invoker invoker, RPCMessage message) {
		m_dispatcher = dispatcher;
		m_invoker = invoker;
		m_message = message;
	}
	
	/**
	 * Runs the task as a thread
	 * 
	 * @since		1.0.0.0
	 */
	public void run() {
    	
		if (m_message.getMessageType() == MessageType.MethodCall && m_invoker != null) {
    		
    		RPCCall call = Serializer.getInstance().deserialize(m_message.getJson(), RPCCall.class);
    		
    		RPCResponse resp = new RPCResponse();
    		resp.ClassName = call.ClassName;
    		resp.MethodName = call.MethodName;
    		
    		if (call.MethodName.equals(Constants.EVENTS_SUBSCRIPTION)) {
    			m_dispatcher.registerEventListener(m_message.m_clientInfo);
    			resp.Result = true;
    		}
    		else {
	    		try {
	    			Object retVal = m_invoker.invoke(call.ClassName, call.MethodName, call.Args);
	    			resp.Result = retVal;
	    		} 
	    		catch (InvocationTargetException tae) {
	    			if (tae.getCause() != null) {
	    				resp.Error = tae.getCause().getClass().getSimpleName() + " : " + 
	    						tae.getCause().getMessage();
	    				Trace.writeLine(tae.getCause());
	    			}
	    		}
	    		catch (Exception ex) {
	    			resp.Error = ex.getClass().getSimpleName() + " : " + ex.getMessage();
	    			Trace.writeLine(ex);
	    		}
    		}
    		
    		String json = Serializer.getInstance().serialize(resp);
    		RPCMessage msg = new RPCMessage(MessageType.MethodResponse, m_message.getTransactionId(), false, (short)0, json);
    		msg.m_clientInfo = m_message.m_clientInfo;
    		m_dispatcher.dispatchMessage(msg);
    	}
	}
}
