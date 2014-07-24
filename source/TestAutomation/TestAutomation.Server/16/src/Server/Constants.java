package Server;

/***
 * Class for providing constants, mainly for reflection
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 *
 */
public class Constants {

	public static final int DEFAULT_LISTENING_PORT = 38600;
	
	public final static int MAX_PACKET_SIZE = 1024 * 4; //Max ADB payload
	
	public final static String EVENTS_SUBSCRIPTION = "subscribeForEvents";
	
	public static final String UI_AUTOMATION_CLASS_NAME = "android.app.UiAutomation";
	public static final String GET_VIEW_ID_RESOURCE_NAME = "getViewIdResourceName";
	public static final String AUTOMATION_BRIDGE_GETTER = "getAutomatorBridge";
	public static final String QUERY_CONTROLLER = "mQueryController";
	public static final String INTERACTION_CONTROLLER = "mInteractionController";
	public static final String WINDOW_MANAGER = "mWindowManager";
	public static final String GET_ACCESSIBILITY_ROOT_NODE = "getAccessibilityRootNode";
	
	public static final String ACCESSIBILITY_EVENT_LISTENER = "AccessibilityEventListener";
	public static final String ON_ACCESSIBILITY_EVENT_LISTENER = "OnAccessibilityEventListener";
	public static final String ADD_ACCESSIBILITY_EVENT_LISTENER = "addAccessibilityEventListener";
	public static final String SET_ON_ACCESSIBILITY_EVENT_LISTENER = "setOnAccessibilityEventListener";
	
	public static final String GET_SYSTEM_LONG_PRESS_TIME = "getSystemLongPressTime";
	public static final String GET_DISPLAY_ROTATION = "getRotation";
    public static final String INJECT_EVENT_SYNC = "injectEventSync"; 
    public static final String SEND_TEXT = "sendText";
    public static final String LONG_TAP = "longTap";
    public static final String LONG_TAP_NO_SYNC = "longTapNoSync";
    public static final String IS_NATURAL_ORIENTATION = "isNaturalRotation";
    public static final String SET_ROTATION_NATURAL = "setRotationNatural";
    public static final String SET_ROTATION_RIGHT = "setRotationRight";
    public static final String SET_ROTATION_LEFT = "setRotationLeft";	
    public static final String TOUCH_DOWN = "touchDown";
    public static final String TOUCH_UP = "touchUp";
    public static final String TOUCH_MOVE = "touchMove";
    public static final String SEND_KEY = "sendKey";
    public static final String SCROLL_SWIPE = "scrollSwipe";
}
