package Server;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import android.util.Log;
import android.view.accessibility.*;
import android.os.RemoteException;
import android.graphics.Point;

import com.android.uiautomator.testrunner.UiAutomatorTestCase;
import com.android.uiautomator.core.UiDevice;
import com.android.uiautomator.core.UiObject;
import com.android.uiautomator.core.UiObjectNotFoundException;
import com.android.uiautomator.core.UiSelector;

/***
 * Class which contains the main implementation of our testing sever 
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 *
 */
public class TAServer extends UiAutomatorTestCase {

	private static final String SERVER_VERSION = "1.0.0.0";
	private static final int TARGET_API_VERSION = 16;
	
	private static String mLastActivityName = null;
	private static String mLastTraversedText = "";
		
	private static final Object mLock = new Object();
	
	private static boolean mIsRoot = false;
	
	/***
	 * Sets the details for this process: display name of the process, out-of-memory management
	 * adjustment score, and process priority
	 * 
	 * @param 	name		Display name of the process
	 * @param 	oom_score	-17 taims the oom
	 * @param	nice		-20 sets the maximum priority
	 * 
	 * @since	1.0.1.0
	 */
	private void setProcessDetails(String name, int oom_score, int nice) {
		
		try	{
			
			android.os.Process.setThreadPriority(nice);
            android.os.Process.class.getMethod("setArgV0", String.class).invoke(null, name);
            android.os.Process.class.getMethod("setOomAdj", int.class, int.class).invoke(null, android.os.Process.myPid(), oom_score);
			
		} catch (Exception e) { }
		
	}
	
	/***
	 * 
	 * 
	 * @throws Exception
	 */
	public void start() throws Exception {
	
		setProcessDetails("TAServer", -17, -20);
		
		//Sets the cmd args to env
		Environment.setCommandLineArgs(getParams());
		
		mIsRoot = Environment.isRoot();
		
		//We introduce the classes which we want to be visible for RPC calls
		Reflector.getInstance().AddTarget(TAServer.class, RPCMethod.class);
		Reflector.getInstance().AddTarget(FileSystem.class, RPCMethod.class);
		
		//The invoker interface implementation: Reflector does the final invoking
	    Invoker invoker = new Invoker() {
	    	public Object invoke(String className, String methodName, Object[] args) throws Exception {
	    		return Reflector.getInstance().invoke(className, methodName, args);
	    	}
	    };      
	    
	    //Interface implementation for ui event listener : RPC server broadcasts these events further
        UiEventListenerHandler handler = new UiEventListenerHandler() {
        	public void onUiEvent(AccessibilityEvent event) {
        		synchronized (mLock) {
	        		if (RPCServer.getInstance().getEventListenerCount() > 0) {
        				int pageFlips = mIsRoot ? SurfaceFlingerProxy.getInstance().getPageFlipCount() : -1;
        				long pageFlipTimeStamp = System.currentTimeMillis();
	        			SerializableAccessibilityEvent se = 
	        					SerializableAccessibilityEvent.fromAccessibilityEvent(event, pageFlips, pageFlipTimeStamp);
	        			if (se.isOkay()) {
	        				RPCServer.getInstance().broadcastEvent(AccessibilityEvent.class, se);
	        			}
	        		}
	        		checkEvent(event);
        		}
        	}
        };
                
	    RPCServer server = RPCServer.getInstance();
	    server.setInvoker(invoker); //we set our invoker
	    server.start(); //starts the RPC server
	    Trace.writeLine("SERVER=OK"); //This is a must print: it tells the client that we're running
        UiEventListener.subscribeForUiEvents(handler); //subscribes the ui events
        
	    try {
			server.join(); //We start waiting for the RCPServer thread until our process is being killed
		} catch (InterruptedException e) {
			Trace.writeLine(e);
		}
	    
	    UiEventListener.unsubscribeForUiEvents(handler);
	}
	
	/***
	 * 
	 * @param event
	 */
	private static void checkEvent(AccessibilityEvent event) {
        switch(event.getEventType()) {
	        case AccessibilityEvent.TYPE_WINDOW_STATE_CHANGED:
	            // don't trust event.getText(), check for nulls
	            if (event.getText() != null && event.getText().size() > 0) {
	                if(event.getText().get(0) != null)
	                    mLastActivityName = event.getText().get(0).toString();
	            }
	           break;
	        case AccessibilityEvent.TYPE_VIEW_TEXT_TRAVERSED_AT_MOVEMENT_GRANULARITY:
	            // don't trust event.getText(), check for nulls
	            if (event.getText() != null && event.getText().size() > 0)
	                if(event.getText().get(0) != null)
	                    mLastTraversedText = event.getText().get(0).toString();
	            break;
        }
	}
		
	/***
	 * Gets the version of the server currently running
	 * 
	 * @return		The version of the server currently running
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the version of the server currently running", since = "1.0.0.0")	
	public static String getServerVersion() {
		return SERVER_VERSION;
	}
	
	/***
	 * Gets the API version this server is targeting for
	 * 
	 * @return		The API version this server is targeting for
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the API version this server is targeting for", since = "1.0.0.0")
	public static int getTargetApiVersion() {
		return TARGET_API_VERSION;
	}
	
	/***
	 * Gets the display orientation/rotation
	 * 
	 * @return		The display orientation/rotation
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the display orientation/rotation", 
			usage = "0 = 0; 1 = 90; 2 = 180; 3 = 270",
			since = "1.0.0.0")
	public static int getDisplayOrientation() {
		return Input.getInstance().getDisplayRotation();
	}
	
	/***
	 * Gets the system's long press time
	 * 
	 * @return		The system's long press time
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the system's long press time", since = "1.0.0.0")
	public static long getSystemLongPressTime() {
		return Input.getInstance().getSystemLongPressTime();
	}
	
	/***
	 * Simulates the touch up
	 * 
	 * @param 		x		The x-coordinate in the screen from which to touch up
	 * @param 		y		The y-coordinate in the screen from which to touch up
	 * @return		True is successfully touched up; false otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Simulates the touch up", since = "1.0.0.0")
	public static boolean touchUp(Double x, Double y) {
		return Input.getInstance().touchUp(x.intValue(), y.intValue());
	}
	
	/***
	 * Simulates the touch down
	 * 
	 * @param 		x		The x-coordinate in the screen on which to touch down
	 * @param 		y		The y-coordinate in the screen on which to touch down
	 * @return		True is successfully touched down; false otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Simulates the touch down", since = "1.0.0.0")
	public static boolean touchDown(Double x, Double y) {
		return Input.getInstance().touchDown(x.intValue(), y.intValue());
	}
	
	/***
	 * Simulates a touch move when touch has already been set down 
	 * 
	 * @param 		x		The x-coordinate for which to move
	 * @param 		y		The y-coordinate for which to move
	 * @return		True if successfully moved; false otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Simulates a touch move when touch has already been set down ", since = "1.0.0.0")
	public static boolean touchMove(Double x, Double y) {
		return Input.getInstance().touchMove(x.intValue(), y.intValue());
	}
	
	/***
	 * Gets a dictionary of available key codes
	 * 
	 * @return		A dictionary of available key codes
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets a dictionary of available key codes", since = "1.0.0.0")
	public static Map<String, Integer> getKeyCodes() {
		return Input.getInstance().getKeyCodes();
	}
	
	/***
	 * Sends a long key event to the device
	 * 
	 * @param 		key			Code of the key to send
	 * @param 		metaState	Meta state of the key
	 * @return		True if successfully sent; false otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Sends a long key event to the device", since = "1.0.0.0")
	public static boolean sendLongKey(Double key, Double metaState) {
		return Input.getInstance().sendKeyLong(key.intValue(), metaState.intValue());
	}
	
	/***
	 * Sends a key event to the device
	 * 
	 * @param 		key			Code of the key to send
	 * @param 		metaState	Meta state of the key
	 * @return		True if successfully sent; false otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Sends a key event to the device", since = "1.0.0.0")
	public static boolean sendKey(Double key, Double metaState) {
		//Log.d("Marble", "Sending key:" + key.intValue());
		boolean retVal = Input.getInstance().sendKey(key.intValue(), metaState.intValue());
		//Log.d("Marble", "Key sent:" + key.intValue() + "=" + retVal);
		return retVal;
	}
		
	/***
	 * Gets the width of the display, in pixels. The width details are reported based on the current orientation
	 * of the display.
	 * 
	 * @return		The width of the display, in pixels
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the width of the display, in pixels. The width details are reported based on the " +
			"current orientation of the display.", since = "1.0.0.0")	
	public static int getDisplayWidth() {
		return UiDevice.getInstance().getDisplayWidth();
	}
	
	/***
	 * Gets the height of the display, in pixels. The height details are reported based on the current orientation
	 * of the display.
	 * 
	 * @return		The height of the display, in pixels
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the height of the display, in pixels. The height details are reported based on the " +
			"current orientation of the display.", since = "1.0.0.0")
	public static int getDisplayHeight() {
		return UiDevice.getInstance().getDisplayHeight();
	}
	
	/***
	 * Gets the size of the display in the device.
	 * 
	 * @return 		The size of the display in the device
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the size of the display in the device, in pixels. Based on the current orientation" +
	 "of the display", since = "1.0.0.0")
	public static int[] getDisplaySize() {
		return new int[] { getDisplayWidth(), getDisplayHeight() };
	}
	
	/***
	 * Gets the current orientation of the display
	 * 
	 * @return		The current orientation of the display
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the current orientation of the display", since = "1.0.0.0.0", usage =
			"0 = 0; 1 = 90; 2 = 180; 3 = 270")
	public static int getOrientation() {
		return AutomatorBridge.getInstance().getDisplayRotation();
	}
	
	/***
	 * Check if the device is in its natural orientation. This is determined by checking if the orientation is at 0 or 180 degrees.
	 * 
	 * @return		True if it is in natural orientation
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Check if the device is in its natural orientation. This is determined by checking if the orientation is at 0 or 180 degrees.", 
			since = "1.0.0.0")
	public static boolean isNaturalOrientation() {
		return Input.getInstance().isNaturalOrientation();
	}
	
	/***
	 * Rotates up and also freezes rotation in that position by disabling the sensors.
	 * 
	 * @return 		True if success; False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Rotates up and also freezes rotation in that position by disabling the sensors.", 
			since = "1.0.0.0")
	public static boolean setOrientationNatural() {
		return Input.getInstance().setOrientationNatural();
	}
	
	/***
	 * Simulates orienting the device to the left and also freezes rotation by disabling the sensors.
	 * 
	 * @return		True if success; False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Simulates orienting the device to the left and also freezes rotation by disabling the sensors.", 
			since = "1.0.0.0")
	public static boolean setOrientationLeft() {
		return Input.getInstance().setOrientationLeft();
	}
	
	/***
	 * Simulates orienting the device to the right and also freezes rotation by disabling the sensors.
	 * 
	 * @return		True if success; False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Simulates orienting the device to the right and also freezes rotation by disabling the sensors.", 
			since = "1.0.0.0")
	public static boolean setOrientationRight() {
		return Input.getInstance().setOrientationRight();
	}
	
	/***
	 * Performs a swipe between points in the Point array using the number of steps to determine smoothness and speed.
	 * 
	 * @param 		points		[x1, y1, x2, y2, ..., xn, yn]
	 * @param 		steps		Steps to determine smoothness and speed
	 * @return		True if swipe was successful, False otherwise 
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Performs a swipe between points in the Point array using the number of " +
			"steps to determine smoothness and speed.", since = "1.0.0.0", usage = "[x1, y1, x2, y2, ..., xn, yn], steps")
	public static boolean swipeRegion(List<Double> points, Double steps) {
		
		if (points.size() % 2 == 0) {
			
			Point[] region = new Point[points.size() / 2];
			
			for(int i = 0; i < points.size(); i+=2) {
				region[i / 2] = new Point(points.get(i).intValue(), points.get(i + 1).intValue());
			}
			
			return UiDevice.getInstance().swipe(region, steps.intValue());
		}
		
		return false;
	}
			
	/***
	 * Long presses a point in screen
	 * 
	 * @param 		x		X-coordinate of the point
	 * @param 		y		Y-coordinate of the point
	 * @return		True if success; False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Long presses a point in screen", since = "1.0.0.0")
	public static boolean longTap(Double x, Double y) {
		return Input.getInstance().longTap(x.intValue(), y.intValue());
	}
	
	/***
	 * Adds a marker to system log
	 * 
	 * @param 		tag		Name of the text provider
	 * @param 		msg		The actual text to add to the log
	 * @return		?
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Adds a marker to system log", since = "1.0.0.0")
	public static int addLogMarker(String tag, String msg) {
		return Log.i(tag, msg);
	}
	
	/***
	 * Gets a list of class names providing RPC methods
	 * 
	 * @return		A list of class names providing RPC methods
	 */
	@RPCMethod(description = "Gets a list of class names providing RPC methods", since = "1.0.0.0")
	public static List<String> getAvailableClassNames() {
		return Reflector.getInstance().getAvailableClassNames();
	}
	
	/***
	 * Gets a list of available RPC method names in a given class
	 * 
	 * @param 		className		Simple name of the class from which to list the methods
	 * @return		A list of the available RPC methods in a given class
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets a list of available RPC method names in a given class", since = "1.0.0.0",
			usage = "e.g. getMethods(\"TAServer\");")
	public static List<String> getAvailableMethodNames(String className) {
		return Reflector.getInstance().getAvailableMethodNames(className);
	}
	
	/***
	 * Gets the document of remotely accessible classes and methods.
	 * 
	 * @return		Document of remotely accessible classes and methods.
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the document of remotely accessible classes and methods", since = "1.0.0.0")
	public static String getDoc() {
		return String.format("Server version:%s; Target API version:%s\n%s", SERVER_VERSION, TARGET_API_VERSION,
				Reflector.getInstance().getDoc());
	}
	
	/***
	 * Taps a given coordinate
	 * 
	 * @param 		x		 X-coordinate of the point to touch
	 * @param 		y		 Y-coordinate of the point to touch
	 * @param		duration Duration of the tap
	 * @return		True if success, False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Taps a given coordinate by given duration", since = "1.0.0.0")
	public static boolean tap(Double x, Double y, Double duration) {
		return Input.getInstance().tap(x.intValue(), y.intValue(), duration.intValue());
	}
	
	/***
	 * Taps a given list of coordinate, and sleeps between each tap for a given period of time
	 * 
	 * @param 		points			List of coordinates (odd = x, even = y) to be tapped
	 * @param		duration		Duration of each tap
	 * @param 		sleepBetween	Time to sleep between taps
	 * @return		True if the whole sequence was tapped successfully; false if any tap or sleep fails
	 * @throws 		InterruptedException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Taps a given list of coordinate, and sleeps between each tap for a given period of time",
			usage = "[x1, y1, x2, y2, ... xn, yn], <sleep ms>", since = "1.0.0.0")
	public static boolean tapSequence(List<Double> points, Double duration, Double sleepBetween) {
		
		if (points.size() % 2 == 0) {
			
			for(int i = 0; i < points.size(); i+=2) {
				
				if (!tap(points.get(i), points.get(i + 1), duration)) {
					return false;
				}
				if ((i + 1) < (points.size() - 1)) {
					try {
						Thread.sleep(sleepBetween.longValue());
					} catch (InterruptedException e) {
						String message = e.getMessage();
						if (message != null) {
							Trace.writeLine(message);
						}
						return false;
					}
				}
			}
			
			return true;
		}
		
		return false;
	}
	
	
	/***
	 * Repeats key press of volume down for given amount of times
	 * 
	 * @param 		steps		Amount of repeats
	 * @return		True if all success; False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Repeats key press of volume down for given amount of times", since = "1.0.0.0")
	public static boolean volDown(Double steps) {
		return Input.getInstance().volDown(steps.intValue());
	}
	
	
	/***
	 * Repeats key press of volume up for given amount of times
	 * @param 		steps		Amount of repeats
	 * @return		True is success; False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Repeats key press of volume up for given amount of times", since = "1.0.0.0")
	public static boolean volUp(Double steps) {
		return Input.getInstance().volUp(steps.intValue());
	}
	
	/***
	 * Presses the home key
	 * 
	 * @return		True if success, False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Presses the home key", since = "1.0.0.0")
	public static boolean pressHome() {
		return UiDevice.getInstance().pressHome();
	}
	
	/***
	 * Wakes up the display if in sleep state
	 * 
	 * @return		True if success, False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Wakes up the display if in sleep state", since = "1.0.0.0")
	public static boolean wakeUp() {
		try {
			if (!UiDevice.getInstance().isScreenOn()) {	
				try {
					UiDevice.getInstance().wakeUp();
					return true;
				} catch (RemoteException e) {
					return false;
				}
			}
			else {
				return true;
			}
		} catch (RemoteException e) {
		}
		return false;
	}
	
	/***
	 * Tries to select a visible UI object based on it's text value
	 * 
	 * @param 		text		Text of an item to select
	 * @return		True if successfully selected, False otherwise
	 * @throws 		UiObjectNotFoundException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Tries to select a visible UI object based on it's text value", since = "1.0.0.0")
	public static boolean selectByText(String text) throws UiObjectNotFoundException {
		
		if (text == null || text.isEmpty()) {
			return false;
		}
		UiObject object = new UiObject(new UiSelector().text(text));
		return object.click();
	}
	
	/***
	 * Tries to select a visible UI object based on it's description value
	 * 
	 * @param 		desc		Description of an item to select
	 * @return		True if successfully selected, False otherwise
	 * @throws 		UiObjectNotFoundException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Tries to select a visible UI object based on it's description value", since = "1.0.0.0")
	public static boolean selectByDescription(String desc) throws UiObjectNotFoundException {
		
		if (desc == null || desc.isEmpty()) {
			return false;
		}
		UiObject object = new UiObject(new UiSelector().description(desc));
		return object.click();
	}
	
	
	/***
	 * Tries to press the menu button
	 * 
	 * @return		True if successfully selected, False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Tries to press the menu button", since = "1.0.0.0")
	public static boolean pressMenu() {
		return UiDevice.getInstance().pressMenu();
	}
	
	/***
	 * Tries to press the back button
	 * 
	 * @return		True if successfully selected, False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Tries to press the back button", since = "1.0.0.0")
	public static boolean pressBack() {
		return UiDevice.getInstance().pressBack();
	}
	
	/**
	 * Tries to press the search button
	 * 
	 * @return		True if successfully selected, False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Tries to press the search button", since = "1.0.0.0")
	public static boolean pressSearch() {
		return UiDevice.getInstance().pressSearch();
	}
	
	/**
	 * Tries to press the recent apps button
	 * 
	 * @return		True if successfully selected, False otherwise
	 * @throws 		RemoteException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Tries to press the recent apps button", since = "1.0.0.0")
	public static boolean pressRecentApps() throws RemoteException {
		return UiDevice.getInstance().pressRecentApps();
	}
	
	/**
	 * Tries to push a text in a currently selected UI object
	 * 
	 * @param 		text		Text to push	
	 * @return		True if successfully selected, False otherwise
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Tries to push a text in a currently selected UI object", since = "1.0.0.0")
	public static boolean pushText(String text) {
		
		if (text == null || text.isEmpty()) {
			return true;
		}
		return Input.getInstance().sendText(text);
	}
	
	/**
	 * Tries to freeze/unfreeze the rotation of the display.
	 * @param 		value		True=freeze; False=unfreeze
	 * @return		True id success; False otherwise
	 */
	@RPCMethod(description = "Tries to freeze/unfreeze the rotation of the display.", since = "1.0.0.0")
	public static boolean freezeRotation(boolean value) {
		try {
			
			if (value) {
				UiDevice.getInstance().freezeRotation();
			}
			else {
				UiDevice.getInstance().unfreezeRotation();
			}
			return true;
		} catch (RemoteException e) {
			return false;
		}
	}
	
	/**
	 * Performs a swipe from one coordinate to another using the number of steps 
	 * to determine smoothness and speed. Each step execution is throttled to 5ms 
	 * per step. So for a 100 steps, the swipe will take about 1/2 second to complete.
	 * 
	 * @param 		startX		X-coordinate of the start point
	 * @param 		startY		Y-coordinate of the start point
	 * @param 		endX		X-coordinate of the end point
	 * @param 		endY		Y-coordinate of the end point
	 * @param 		steps		is the number of move steps sent to the system
	 * @return		false if the operation fails or the coordinates are invalid
	 * @since		1.0.0.0		
	 */
	@RPCMethod(description = "Performs a swipe from one coordinate to another using the number of steps\n" +
	 "to determine smoothness and speed. Each step execution is throttled to 5ms\n" +
	 "per step. So for a 100 steps, the swipe will take about 1/2 second to complete.", since = "1.0.0.0")
	public static boolean swipe(Double startX, Double startY, Double endX, Double endY, Double steps) {
		return Input.getInstance().swipe(startX.intValue(), startY.intValue(), endX.intValue(),
				endY.intValue(), steps.intValue());
	}
	
    /**
     * Handle swipes in any direction where the result is a scroll event. This call blocks
     * until the UI has fired a scroll event or timeout.
     * @param 		downX
     * @param 		downY
     * @param 		upX
     * @param 		upY
     * @param 		steps
     * @return 		true if we are not at the beginning or end of the scrollable view.
     * @since		1.0.0.0
     */
	@RPCMethod(description = "Handle swipes in any direction where the result is a scroll event. This call blocks\n" +
     "until the UI has fired a scroll event or timeout.", since = "1.0.0.0")
	public static boolean scrollSwipe(Double downX, Double downY, Double upX, Double upY,  Double steps) {
		return Input.getInstance().scrollSwipe(downX.intValue(), downY.intValue(), upX.intValue(),
				upY.intValue(), steps.intValue());
	}
	
	/***
	 * Performs a drag from one coordinate to another coordinate. You can control the smoothness and 
	 * speed of the swipe by specifying the number of steps. Each step execution is throttled to 
	 * 5 milliseconds per step, so for a 100 steps, the swipe will take around 0.5 seconds to complete.
	 * @param 		startX
	 * @param 		startY
	 * @param 		endX
	 * @param 		endY
	 * @param 		steps
	 * @return		true if drag is performed, false if the operation fails or the coordinates are invalid
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Performs a drag from one coordinate to another coordinate. You can control the smoothness and\n" +
	 "speed of the swipe by specifying the number of steps. Each step execution is throttled to\n" +
	 "5 milliseconds per step, so for a 100 steps, the swipe will take around 0.5 seconds to complete.",
	 since = "1.0.0.0")
	public static boolean drag(Double startX, Double startY, Double endX, Double endY, Double steps) {
		return Input.getInstance().drag(startX.intValue(), startY.intValue(), endX.intValue(),
				endY.intValue(), steps.intValue());
	}
	
	/***
	 * Pinches the display with two fingers. You can control the smoothness and 
	 * speed of the pinch by specifying the number of steps. Each step execution is throttled to 
	 * 5 milliseconds per step, so for a 100 steps, the swipe will take around 0.5 seconds to complete.
	 * 
	 * @param 		downX1
	 * @param 		downY1
	 * @param 		downX2
	 * @param 		downY2
	 * @param 		upX1
	 * @param 		upY1
	 * @param 		upX2
	 * @param 		upY2
	 * @param 		steps
	 * @return		True if successfully pinched; False otherwise
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Pinches the display with two fingers. You can control the smoothness and\n" +
			 "speed of the pinch by specifying the number of steps. Each step execution is throttled to\n" +
			 "5 milliseconds per step, so for a 100 steps, the swipe will take around 0.5 seconds to complete.",
			 since = "1.0.1.0")
	public static boolean pinch(Double downX1, Double downY1, Double downX2, Double downY2,
			Double upX1, Double upY1, Double upX2, Double upY2, Double steps) {
		
		return Input.getInstance().pinch(downX1.intValue(), downY1.intValue(), downX2.intValue(), 
				downY2.intValue(), upX1.intValue(), upY1.intValue(), upX2.intValue(), upY2.intValue(),
				steps.intValue());
	}
	
	/***
	 * Performs a pinch out with two fingers. You can control the smoothness and 
	 * speed of the pinch by specifying the number of steps. Each step execution is throttled to 
	 * 5 milliseconds per step, so for a 100 steps, the swipe will take around 0.5 seconds to complete.
	 * @param 		fromX
	 * @param 		fromY
	 * @param 		radius
	 * @param 		angle
	 * @param 		steps
	 * @return
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Performs a pinch out with two fingers. You can control the smoothness and\n" +
			 "speed of the pinch by specifying the number of steps. Each step execution is throttled to\n" +
			 "5 milliseconds per step, so for a 100 steps, the swipe will take around 0.5 seconds to complete.",
			 since = "1.0.1.0")
	public static boolean pinchOut(Double fromX, Double fromY, Double radius, Double angle, Double steps) {
		
		return Input.getInstance().pinchOut(new Point(fromX.intValue(),  fromY.intValue()), radius.intValue(),
				angle, steps.intValue());
	}
	
	/***
	 * Performs a pinch in with two fingers. You can control the smoothness and 
	 * speed of the pinch by specifying the number of steps. Each step execution is throttled to 
	 * 5 milliseconds per step, so for a 100 steps, the swipe will take around 0.5 seconds to complete.
	 * @param 		toX
	 * @param 		toY
	 * @param 		radius
	 * @param 		angle
	 * @param 		steps
	 * @return		
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Performs a pinch in with two fingers. You can control the smoothness and\n" +
			 "speed of the pinch by specifying the number of steps. Each step execution is throttled to\n" +
			 "5 milliseconds per step, so for a 100 steps, the swipe will take around 0.5 seconds to complete.",
			 since = "1.0.1.0")
	public static boolean pinchIn(Double toX, Double toY, Double radius, Double angle, Double steps) {
		
		return Input.getInstance().pinchIn(new Point(toX.intValue(),  toY.intValue()), radius.intValue(),
				angle, steps.intValue());
	}
	
	/***
	 * 
	 * @param 		centerX
	 * @param 		centerY
	 * @param 		radius
	 * @param 		startAngle
	 * @param 		stopAngle
	 * @param 		intervalAngle
	 * @param 		clockwise
	 * @return		
	 * @since		1.0.1.0
	 */
	public static boolean curvedSwipe(Double centerX, Double centerY, Double radius, Double startAngle,
			Double stopAngle, Double intervalAngle, boolean clockwise) {
		
		return Input.getInstance().curvedSwipe(new Point(centerX.intValue(), centerY.intValue()), radius.intValue(),
				startAngle, stopAngle, intervalAngle, clockwise);
	}
	
	/**
	 * Retrieves the last activity to report accessibility events.
	 * The results returned should be considered unreliable
	 * 
	 * @return		String name of activity
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Retrieves the last activity to report accessibility events.\n" + 
	 "The results returned should be considered unreliable", since = "1.0.0.0")
	public static String getCurrentActivityName() {
        synchronized (mLock) {
            return mLastActivityName;
        }
	}
	
	/**
	 * Retrieves the name of the last package to report accessibility events.
	 * 
	 * @return		String name of package
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Retrieves the name of the last package to report accessibility events.", since = "1.0.0.0")
	public static String getCurrentPackageName() {
		return UiDevice.getInstance().getCurrentPackageName();
	}
	
	/**
	 * Retrieves the text from the last UI traversal event received. You can use this 
	 * method to read the contents in a WebView container because the accessibility 
	 * framework fires events as each text is highlighted. You can write a test to perform 
	 * directional arrow presses to focus on different elements inside a WebView, and call 
	 * this method to get the text from each traversed element. If you are testing a view 
	 * container that can return a reference to a Document Object Model (DOM) object, your 
	 * test should use the view's DOM instead.
	 * 
	 * @return		text of the last traversal event, else return an empty string
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Retrieves the text from the last UI traversal event received. You can use this\n" +
	 "method to read the contents in a WebView container because the accessibility\n" +
	 "framework fires events as each text is highlighted. You can write a test to perform\n" + 
	 "directional arrow presses to focus on different elements inside a WebView, and call\n" +
	 "this method to get the text from each traversed element. If you are testing a view\n" +
	 "container that can return a reference to a Document Object Model (DOM) object, your\n" +
	 "test should use the view's DOM instead.", since = "1.0.0.0")
	public static String getLastTraversedText() {
        synchronized (mLock) {
            if (mLastTraversedText.length() > 0) {
                return mLastTraversedText;
            }
        }
        return null;
	}
	
    /**
     * Clears the last text selection value saved from the TYPE_VIEW_TEXT_SELECTION_CHANGED
     * event
     */
    public static void clearLastTraversedText() {
        synchronized (mLock) {
            mLastTraversedText = "";
        }
    }
	
	/***
	 * Gets an xml dump describing the current ui hierarchy in the device.
	 * 
	 * @return		An xml dump describing the current ui hierarchy in the device.
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets an xml dump describing the current ui layout hierarchy in the device.", since = "1.0.0.0")
	public static String getDump(boolean refresh) {

		try {
			return Dump.getDump(refresh);
		} catch (Exception e) {
			Trace.writeLine(e);
		} 
		return null;
	}
	
	@RPCMethod(description = "", since = "1.0.1.0")
	public static boolean registerDirectoryObserver(String directory, String guid) {
		return DirectoryObserver.getInstance().startObserving(directory, guid);
	}
	
	@RPCMethod(description = "", since = "1.0.1.0")
	public static boolean unregisterDirectoryObserver(String directory, String guid) {
		return DirectoryObserver.getInstance().stopObserving(directory, guid);
	}
	
	/***
	 * Stops the server and closes the sockets
	 * 
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Stops the server and closes the sockets", since = "1.0.1.0")
	public static void kill() {
		RPCServer.getInstance().kill();
	}
	
	/***
	 * Gets the page flip count from SurfaceFlinger
	 * 
	 * @return		The page flip count from SurfaceFlinger
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Gets the page flip count from SurfaceFlinger", since = "1.0.1.0")
	public static int getPageFlipCount() {
		return mIsRoot ? SurfaceFlingerProxy.getInstance().getPageFlipCount() : -1;
	}
	
	/***
	 * Gets the names of the supported audio streams
	 * 
	 * @return		The names of the supported audio streams
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Gets the names of the supported audio streams", since = "1.0.1.0")
	public static String[] getAudioStreamNames() {
		return AudioManagerProxy.getInstance().getAudioStreamNames();
	}
	
	/***
	 * Gets the current ringer volume index
	 * 
	 * @return		The current ringer volume; -1 in case of service unreachable
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Gets the current ringer volume index", since = "1.0.1.0")
	public static int getRingerVolume() {
		return AudioManagerProxy.getInstance().getRingerVolume();
	}
	
	/***
	 * Gets the current media volume index
	 * 
	 * @return		The current media volume; -1 in case of service unreachable
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Gets the current media volume index", since = "1.0.1.0")
	public static int getMediaVolume() {
		return AudioManagerProxy.getInstance().getMediaVolume();
	}
	
	/***
	 * Sets the ringer volume index
	 * 
	 * @return		True if the operation was successfully performed; otherwise, false
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Sets the ringer volume index", since = "1.0.1.0")
	public static boolean setRingerVolume(Double index) {
		return AudioManagerProxy.getInstance().setRingerVolume(index.intValue());
	}
	
	/***
	 * Sets the media volume index
	 * 
	 * @return		True if the operation was successfully performed; otherwise, false
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Sets the media volume index", since = "1.0.1.0")
	public static boolean setMediaVolume(Double index) {
		return AudioManagerProxy.getInstance().setMediaVolume(index.intValue());
	}
	
	/***
	 * Gets the maximum volume index of the master stream
	 * 
	 * @return		The maximum volume index of the master stream; -1 in case of service unreachable
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Gets the maximum volume index of the master stream", since = "1.0.1.0")
	public static int getMasterMaxVolume() {
		return AudioManagerProxy.getInstance().getMasterMaxVolume();
	}
	
	/***
	 * Gets the current volume index of the master stream
	 * 
	 * @return		The current volume index of the master stream; -1 in case of service unreachable
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Gets the current volume index of the master stream", since = "1.0.1.0")
	public static int getMasterVolume() {
		return AudioManagerProxy.getInstance().getMasterVolume();
	}
	
	/***
	 * Sets the master stream's volume level index
	 * 
	 * @param 		index		The volume level index to set
	 * @return		True if the operation was successfully performed; otherwise, false
	 * @since		1.0.1.0	
	 */
	@RPCMethod(description = "Sets the master stream's volume level index", since = "1.0.1.0")
	public static boolean setMasterVolume(Double index) {
		return AudioManagerProxy.getInstance().setMasterVolume(index.intValue());
	}
	
	/***
	 * Gets the name of the master stream
	 * 
	 * @return		The name of the master stream; null in case of service unreachable
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Gets the name of the master stream", since = "1.0.1.0")
	public static String getMasterStreamName() {
		return AudioManagerProxy.getInstance().getMasterStreamName();
	}
	
	/***
	 * Gets the maximum volume of a stream by its name
	 * 
	 * @param 		streamName		Name of the stream
	 * @return		The maximum volume of a stream by it's name; -1 in case of service unreachable
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Gets the maximum volume of a stream by its name", since = "1.0.1.0")
	public static int getStreamMaxVolume(String streamName) {
		return AudioManagerProxy.getInstance().getStreamMaxVolume(streamName);
	}
	
	/***
	 * Gets the current volume index of a stream by its name
	 * 
	 * @param 		streamName		Name of the stream
	 * @return		The current volume index of a stream by its name; -1 in case of service unreachable
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Gets the current volume index of a stream by its name", since = "1.0.1.0")
	public static int getStreamVolume(String streamName) {
		return AudioManagerProxy.getInstance().getStreamVolume(streamName);
	}
	
	/***
	 * Sets a stream's volume level index
	 * 
	 * @param 		streamName	Name of the audio stream
	 * @param 		index		The volume level index to set
	 * @return		True if the operation was successfully performed; otherwise, false
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Sets a stream's volume level index", since = "1.0.1.0")
	public static boolean setStreamVolume(String streamName, Double index) {
		return AudioManagerProxy.getInstance().setStreamVolume(streamName, index.intValue());
	}
	
	/***
	 * Gets a value indicating whether the master stream is muted
	 * 
	 * @return		True if muted; otherwise, false. Also, false in case of service unreachable
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Gets a value indicating whether the master stream is muted", since = "1.0.1.0")
	public static boolean isMasterMute() {
		return AudioManagerProxy.getInstance().isMasterMute();
	}
	
	/***
	 * Toggles the master stream's mute state
	 * 
	 * @param 		state		True to mute; false to unmute		
	 * @return		True if the operation was successfully performed; otherwise, false
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Toggles the master stream's mute state", since = "1.0.1.0")
	public static boolean setMasterMute(boolean state) {
		return AudioManagerProxy.getInstance().setMasterMute(state);
	}
		
	/***
	 * Gets a value indicating whether the speaker phone is on
	 * 
	 * @return		True if on; otherwise, false. Also, false in case of service unreachable
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Gets a value indicating whether the speaker phone is on", since = "1.0.1.0")
	public static boolean isSpeakerphoneOn() {
		return AudioManagerProxy.getInstance().isSpeakerphoneOn();
	}
	
	/***
	 * Toggles the speaker phone state 
	 * 
	 * @param 		on		True to enable; false to disable
	 * @return		True if the operation was successfully performed; otherwise, false
	 * @since		1.0.1.0
	 */
	@RPCMethod(description = "Toggles the speaker phone state", since = "1.0.1.0")
	public static boolean setSpeakerphoneOn(boolean on) {
		return AudioManagerProxy.getInstance().setSpeakerphoneOn(on);
	}
}
