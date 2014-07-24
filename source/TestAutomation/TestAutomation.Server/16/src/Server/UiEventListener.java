package Server;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.util.ArrayList;

import android.view.accessibility.AccessibilityEvent;

import com.android.uiautomator.core.UiDevice;

/***
 * Class, which is used for registering a custom handler for listening UI/Accessibility events
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public class UiEventListener {
	
	private static ArrayList<UiEventListenerHandler> mHandlers = new ArrayList<UiEventListenerHandler>();
	
    /***
     * Creates a proxy object/interface to be set for AccessibilityEventListener
     * 
	 * @return		A proxy object/interface to be set for AccessibilityEventListener; null if unable to create
	 * @since		1.0.0.0
     */
    private static Object createEventListenerProxy() {
        
    	Class<?> type = AutomatorBridge.getInstance().getAccessibilityEventHandlerClass();
    	
    	if (type == null) {
    		return null;
    	}
    	
    	try {
	        
	        if (type != null) {
	        	Object eventListener = Proxy.newProxyInstance(type.getClassLoader(), new Class[] { type }, new InvocationHandler() {
	        		
	        		@Override
	                public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
	        			AccessibilityEvent event = (AccessibilityEvent)args[0];
	        			onAccessibilityEvent(event);
	        			return null;
	        		}
	        	});
	        	
	        	return eventListener;
	        }
    	} catch (Exception e) {
    		Trace.writeLine(e);
    	}
    	
    	return null;
    }
    
    /***
     * Sets the proxy interface for AccessibilityEventListener
     * 
	 * @return		True if successfully set; false otherwise
	 * @since		1.0.0.0
     */
    private static boolean setEventListenerProxy() {
    	
    	Object proxyObject = createEventListenerProxy();
    	
    	if (proxyObject == null) {
    		return false;
    	}
    	
    	try {
	    	
    		Method setter = AutomatorBridge.getInstance().getEventListenerSetter();
	    	
	    	if (setter != null) {
	    		setter.invoke(AutomatorBridge.getInstance().getBridgeObject(), new Object[] { proxyObject });
	    		return true;
	    	}
    	} catch(Exception e) {
    		Trace.writeLine(e);
    	}
    	
    	return false;
    }
    
    /***
     * Called on every AccessibilityEvent: forward the event for every subscriber
     * 
     * @param 		event		AccessibilityEvent object, which was fired
     * @since		1.0.0.0
     */
    private static void onAccessibilityEvent(AccessibilityEvent event) {

    	for(UiEventListenerHandler handler : mHandlers) {
    		handler.onUiEvent(event);
    	}
    }
    
    /***
     * Adds an event handler for listening AccessibilityEvents
     * 
     * @param 		handler		An event handler for listening AccessibilityEvents
	 * @return		True is successfully set; false otherwise
	 * @since		1.0.0.0
     */
    private synchronized static boolean addEventHandler(UiEventListenerHandler handler) {
    	
    	if (mHandlers.size() == 0) {
    	
    		boolean success = setEventListenerProxy();
    		
    		if (!success) {
    			return false;
    		}
    	}
    	
    	return mHandlers.add(handler);
    }
    
    /***
     * Removes an event handler from listening AccessibilityEvents
     * 
     * @param 		handler		An event handler to be removed
     * @since		1.0.0.0
     */
    private synchronized static void removeEventHandler(UiEventListenerHandler handler) {
    	
    	mHandlers.remove(handler);
    	if (mHandlers.size() == 0) {
    		//TODO: Should we completely destroy the proxy interface?
    	}
    }
    
    /***
     * Subscribes AccessibilityEvents for the caller, for given handler implementation
     * 
     * @param 		handler		An event handler for listening AccessibilityEvents
	 * @return		True if successfully subscribed; false otherwise
	 * @since		1.0.0.0
     */
	public static boolean subscribeForUiEvents(UiEventListenerHandler handler) {
		return addEventHandler(handler);
	}
	
	/***
	 * Unsubscribes an event handler from listening AccessibilityEvents
	 * 
	 * @param 		handler		An event handler to be removed
	 * @since		1.0.0.0
	 */
	public static void unsubscribeForUiEvents(UiEventListenerHandler handler) {
		removeEventHandler(handler);
	}
}
