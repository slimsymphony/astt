package Server;

import java.lang.reflect.Field;
import java.lang.reflect.Method;

import android.view.accessibility.AccessibilityNodeInfo;

import com.android.uiautomator.core.UiDevice;

/***
 * Provides access to hidden UiAutomatorBridge and it's fields
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 *
 */
public class AutomatorBridge {

	private static AutomatorBridge m_instance;
	
	private boolean mIsApi18OrLater = false;
	
	private Object mBridgeObject = null;
	private Object mQueryController = null;
	private Object mInterActionController = null;
	private Object mWindowManager = null;
	private Method mEventListenerSetter = null;
	private Class<?> mAccessibilityEventHandlerClass = null;
	private Method mRotationGetter = null;
	private Method mSystemLongPressTimeGetter = null;
	
	/***
	 * Private constructor for the class as we provide only a singleton instance
	 * 
	 * @since		1.0.0.0
	 */
	private AutomatorBridge() {
		init();
	}
	
	/***
	 * Gets the singleton instance of the class
	 * 
	 * @return		The singleton instance of the class
	 * @since		1.0.0.0
	 */
	public static AutomatorBridge getInstance() {
		
		if (m_instance == null) {
			m_instance = new AutomatorBridge();
		}
		return m_instance;
	}
	
	/***
	 * Digs out the hidden fields
	 * 
	 * @since		1.0.0.0
	 */
	private void init() {
		
		String[] items = Environment.getOSVersion().split("\\.");
		int minor = Integer.parseInt(items[1]);
		if (minor >= 3) {
			mIsApi18OrLater = true;
		}
		mBridgeObject = internalGetBridgeObject();
		mQueryController = internalGetQueryController();
		mInterActionController = internalGetInteractionController();
		mEventListenerSetter = internalGetEventListenerSetter();
		mAccessibilityEventHandlerClass = internalGetOnAccessibilityEventHandlerClass();
		mRotationGetter = internalGetDisplayRotationGetter();
		mSystemLongPressTimeGetter = internalSystemLongPressTimeGetter();
	}
	
	/***
	 * Digs out the UiAutomatorBridge object from the UiDevice class
	 * 
	 * @return		The UiAutomatorBridge object from the UiDevice class; null if not found
	 * @since		1.0.0.0
	 */
	private Object internalGetBridgeObject() {
		
		try {
			Method bridgeGetter = UiDevice.class.getDeclaredMethod(Constants.AUTOMATION_BRIDGE_GETTER, new Class<?>[] { });
			bridgeGetter.setAccessible(true);
			return bridgeGetter.invoke(UiDevice.getInstance(), new Object[] { });
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		
		return null;
	}
	
	/***
	 * Digs out the display rotation getter
	 * 
	 * @return		The display rotation getter
	 * @since		1.0.0.0
	 */
	private Method internalGetDisplayRotationGetter() {
		
		try {
			if (mIsApi18OrLater) {
				Method getter = getBridgeClass().getDeclaredMethod(Constants.GET_DISPLAY_ROTATION, new Class<?>[] { });
				getter.setAccessible(true);
				return getter;
			} else {
				Field wm = mInterActionController.getClass().getDeclaredField(Constants.WINDOW_MANAGER);
				if (wm != null) {
					wm.setAccessible(true);
					mWindowManager = wm.get(mInterActionController);
					Method getter = mWindowManager.getClass().getDeclaredMethod(Constants.GET_DISPLAY_ROTATION, new Class<?>[] { });
					getter.setAccessible(true);
					return getter;
				}
			}
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		return null;
	}
	
	/***
	 * Digs out the QueryController object from the UiAutomatorBridge instance
	 * 
	 * @return		The QueryController object from the UiAutomatorBridge instance; null if not found
	 * @since		1.0.0.0
	 */
	private Object internalGetQueryController() {
		
		try {
			Field privateField = getBridgeClass().getDeclaredField(Constants.QUERY_CONTROLLER);
			privateField.setAccessible(true);
			return privateField.get(mBridgeObject);
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		return null;
	}
	
	/***
	 * Digs out the InteractionController object from the UiAutomatorBridge instance
	 * 
	 * @return		The InteractionController object from the UiAutomatorBridge instance; null if not found
	 * @since		1.0.0.0
	 */
	private Object internalGetInteractionController() {
		
		try {
			Field privateField = getBridgeClass().getDeclaredField(Constants.INTERACTION_CONTROLLER);	
			privateField.setAccessible(true);
			return privateField.get(mBridgeObject);
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		return null;
	}
	
	/***
	 * Digs out the AccessibilityEventHandler setter method from the UiAutomatorBridge instance
	 * 
	 * @return		The AccessibilityEventHandler setter method from the UiAutomatorBridge instance; null if not found
	 * @since		1.0.0.0
	 */
	private Method internalGetEventListenerSetter() {
		
		//The method name and input parameter types changed for API level 18
		String methodToLookFor = mIsApi18OrLater ? Constants.SET_ON_ACCESSIBILITY_EVENT_LISTENER :
			Constants.ADD_ACCESSIBILITY_EVENT_LISTENER;
		
		for (Method method : getBridgeClass().getDeclaredMethods()) {
			if (method.getName().contains(methodToLookFor)) {
				method.setAccessible(true);
				return method;
			}
		}
		
		return null;
	}
	
	/***
	 * Digs out the class (type) for the AccessibilityEventHandler
	 * 
	 * @return		The class (type) for the AccessibilityEventHandler; null if not found
	 * @since		1.0.0.0
	 */
	private Class<?> internalGetOnAccessibilityEventHandlerClass()
	{
		try {
			//The class type changed for API level 18
			if (mIsApi18OrLater) {
				for(Class<?> c : Class.forName(Constants.UI_AUTOMATION_CLASS_NAME).getClasses()) {
					if (c.getName().contains(Constants.ON_ACCESSIBILITY_EVENT_LISTENER)) {
						return c;
					}
				}	
			}
			else {
				for(Class<?> c : getBridgeClass().getClasses()) {
					if (c.getName().contains(Constants.ACCESSIBILITY_EVENT_LISTENER)) {
						return c;
					}
				}
			}
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		return null;
	
	}
	
	/***
	 * Digs out the system long press time getter
	 * 
	 * @return		The system long press time getter
	 * @since		1.0.0.0
	 */
	private Method internalSystemLongPressTimeGetter() {
		
		try {
			
			if (!mIsApi18OrLater && mInterActionController != null) {
				Method getter = mInterActionController.getClass().getDeclaredMethod(Constants.GET_SYSTEM_LONG_PRESS_TIME,
						new Class<?>[] { });
				getter.setAccessible(true);
				return getter;
			} else if (mBridgeObject != null){
				Method getter = getBridgeClass().getDeclaredMethod(Constants.GET_SYSTEM_LONG_PRESS_TIME,
						new Class<?>[] { });
				getter.setAccessible(true);
				return getter;
			}		
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		return null;
	}
	
	/***
	 * Gets the display's current rotation
	 * 
	 * @return		The display's current rotation
	 * @since		1.0.0.0
	 */
	public int getDisplayRotation() {
		
		try {
			if (mRotationGetter != null) {
				if (mIsApi18OrLater) {
					return (Integer)mRotationGetter.invoke(mBridgeObject, new Object[] { }); 
				}
				else if (mWindowManager != null) {
					return (Integer)mRotationGetter.invoke(mWindowManager, new Object[] { }); 
				}
			}
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		return -1;
	}
	
	/***
	 * Gets the default long press time of the system
	 * 
	 * @return		The default long press time of the system
	 * @since		1.0.0.0
	 */
	public long getSystemLongPressTime() {
		
		try {
			if (mSystemLongPressTimeGetter != null) {
				return (Long)mSystemLongPressTimeGetter.invoke(
						(mIsApi18OrLater ? mBridgeObject : mInterActionController), new Object[] { });
			}
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		return -1;
	}
	
	/***
	 * Return the current API version
	 * 
	 * @return		The current API version
	 * @since		1.0.1.0
	 */
	public int apiVersion() {
		return android.os.Build.VERSION.SDK_INT;
	}
	
	/***
	 * Checks if the API level in the current device is at least 18
	 * 
	 * @return		True if API level 18 or later
	 * @since		1.0.0.0
	 */
	public boolean isApi18OrLater() {
		return mIsApi18OrLater;
	}
	
	/***
	 * Gets the UiAutomatorBridge object
	 * 
	 * @return		The UiAutomatorBridge object; null if not found
	 * @since		1.0.0.0
	 */
	public Object getBridgeObject() {
		return mBridgeObject;
	}
	
	/***
	 * Gets the class/type of the UiAutomatorBridge object; do not get this directly from object itself
	 *  
	 * @return		The class/type of the UiAutomatorBridge object, null if UiAutomatorBridge object is null
	 * @since		1.0.0.0
	 */
	public Class<?> getBridgeClass() {
		
		if (mBridgeObject == null) {
			return null;
		}
		//This did change in API level 18: UiAutomatorBridge became an abstract class
		return mIsApi18OrLater ? mBridgeObject.getClass().getSuperclass() : mBridgeObject.getClass();
	}
	
	/***
	 * Gets the QueryController instance from the UiAutomatorBridge instance
	 * 
	 * @return		The QueryController instance from the UiAutomatorBridge instance, null if not found
	 * @since		1.0.0.0
	 */
	public Object getQueryController() {
		return mQueryController;
	}
	
	/***
	 * Gets the InteractionController instance from the UiAutomatorBridge instance
	 * 
	 * @return		The InteractionController instance from the UiAutomatorBridge instance, null if not found
	 * @since		1.0.0.0
	 */
	public Object getInteractionController() {
		return mInterActionController;
	}
	
	/***
	 * Gets the AccessibilityEventHandler setter method from the UiAutomatorBridge instance
	 * 
	 * @return		The AccessibilityEventHandler setter method from the UiAutomatorBridge instance; null if not found
	 * @since		1.0.0.0
	 */
	public Method getEventListenerSetter() {
		return mEventListenerSetter;
	}
	
	/***
	 * Gets the class (type) for the AccessibilityEventHandler
	 * 
	 * @return		The class (type) for the AccessibilityEventHandler; null if not found
	 * @since		1.0.0.0
	 */
	public Class<?> getAccessibilityEventHandlerClass() {
		return mAccessibilityEventHandlerClass;
	}
	
	/***
	 * Gets the current AccessibilityRootNodeInfo
	 * 
	 * @return		The current AccessibilityRootNodeInfo; null if not found
	 * @since		1.0.0.0
	 */
	public AccessibilityNodeInfo getAccessibilityRootNode() {
		if (mQueryController != null) {
			try {
				return (AccessibilityNodeInfo)mQueryController.getClass().
						getMethod(Constants.GET_ACCESSIBILITY_ROOT_NODE, new Class<?>[] { }).invoke(mQueryController, new Object[] { });
				} catch (Exception e) {
					Trace.writeLine(e);
			}
		}
		return null;
	}
}
