package Server;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.graphics.Point;
import android.os.SystemClock;
import android.view.InputEvent;

import android.view.InputDevice;
import android.view.KeyCharacterMap;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.MotionEvent.PointerCoords;
import android.view.MotionEvent.PointerProperties;

/***
 * Class for calling the methods not visible for UiDevice, via reflection
 * See: https://android.googlesource.com/platform/frameworks/testing/+/android-sdk-support_r11/uiautomator/library/src/com/android/uiautomator/core/InteractionController.java
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public class Input {
	
	private static final long REGULAR_CLICK_LENGTH = 100;
	private static final int MOTION_EVENT_INJECTION_DELAY_MILLIS = 5;
	
	private Method m_injectEventSync = null;
	private Method m_sendText = null;
	private Method m_longTap = null;
	private Method m_setRotationNatural = null;
	private Method m_setRotationRight = null;
	private Method m_setRotationLeft = null;
	private Method m_touchUp = null;
	private Method m_touchDown = null;
	private Method m_touchMove = null;
	private Method m_sendKey = null;
	private Method m_scrollSwipe = null;
		
	private Object m_controller = null;
	
	private Map<String, Integer> m_keyCodes = null;
	
	private static Input m_instance;
	
	/***
	 * Private class constructor as we provide only a singleton instance of the class
	 * 
	 * @since		1.0.0.0
	 */
	private Input() {
		
		try {
			init();
		} catch (Exception e) {
			Trace.writeLine(e);
		} 
	}
	
	/***
	 * Gets the singleton instance of the class
	 * 
	 * @return		Singleton instance of the class
	 * @since		1.0.0.0
	 */
	public static Input getInstance() {
		
		if (m_instance == null) {
			m_instance = new Input();
		}
		return m_instance;
	}
	
	/***
	 * Initializes the class. Digs out the private methods we need
	 * 
	 * @throws 		NoSuchFieldException
	 * @throws 		SecurityException
	 * @throws 		IllegalArgumentException
	 * @throws 		IllegalAccessException
	 * @throws 		InvocationTargetException
	 * @throws 		NoSuchMethodException
	 * @since		1.0.0.0
	 */
	private void init() throws NoSuchFieldException, SecurityException, IllegalArgumentException, IllegalAccessException, InvocationTargetException, NoSuchMethodException {

		//Gets the InteractionController instance
		m_controller = AutomatorBridge.getInstance().getInteractionController();
		
		//Gets the touchDown -method from the InteractionController instance
		m_touchDown = m_controller.getClass().getDeclaredMethod(Constants.TOUCH_DOWN, int.class, int.class);
		m_touchDown.setAccessible(true);
		
		//Gets the touchUp -method from the InteractionController instance
		m_touchUp = m_controller.getClass().getDeclaredMethod(Constants.TOUCH_UP, int.class, int.class);
		m_touchUp.setAccessible(true);
		
		//Gets the touchMove -method from the InteractionController instance
		m_touchMove = m_controller.getClass().getDeclaredMethod(Constants.TOUCH_MOVE, int.class, int.class);
		m_touchMove.setAccessible(true);
		
		//Gets the sendKey -method from the InteractionController instance
		m_sendKey = m_controller.getClass().getDeclaredMethod(Constants.SEND_KEY, int.class, int.class);
		m_sendKey.setAccessible(true);
		
		//Gets the scrollSwipe -method from the InteractionController instance
		m_scrollSwipe = m_controller.getClass().getDeclaredMethod(Constants.SCROLL_SWIPE, int.class, int.class, int.class, int.class, int.class);
		m_scrollSwipe.setAccessible(true);
		
		//Gets the injectEventSync -method from the InteractionController instance
		m_injectEventSync = m_controller.getClass().getDeclaredMethod(Constants.INJECT_EVENT_SYNC, InputEvent.class);
		m_injectEventSync.setAccessible(true);
		
		//Gets the sendText -method from the InteractionController instance
		m_sendText = m_controller.getClass().getDeclaredMethod(Constants.SEND_TEXT, String.class);
		m_sendText.setAccessible(true);
		
		//Gets the longTap -method from the InteractionController instance: the method name was changed for API level 18
		m_longTap = m_controller.getClass().getDeclaredMethod((AutomatorBridge.getInstance().isApi18OrLater() ?
				Constants.LONG_TAP_NO_SYNC : Constants.LONG_TAP), int.class, int.class);
		m_longTap.setAccessible(true);
		
		//Gets the setRotationNatural -method from the InteractionController instance
		m_setRotationNatural = m_controller.getClass().getDeclaredMethod(Constants.SET_ROTATION_NATURAL, new Class<?>[] { });
		m_setRotationNatural.setAccessible(true);
		
		//Gets the setRotationRight -method from the InteractionController instance
		m_setRotationRight = m_controller.getClass().getDeclaredMethod(Constants.SET_ROTATION_RIGHT, new Class<?>[] { });
		m_setRotationRight.setAccessible(true);
		
		//Gets the setRotationLeft -method from the InteractionController instance
		m_setRotationLeft = m_controller.getClass().getDeclaredMethod(Constants.SET_ROTATION_LEFT, new Class<?>[] { });
		m_setRotationLeft.setAccessible(true);
		
		m_keyCodes = internalGetKeyCodes();
	}
	
	/***
	 * Gets all the system key codes
	 * 
	 * @return		All the system key codes
	 * @since		1.0.0.0
	 */
	public Map<String, Integer> getKeyCodes() {
		return m_keyCodes;
	}
	
	/***
	 * Internal getter for system key codes
	 * 
	 * @return		All the system key codes
	 * @since		1.0.0.0
	 */
	private Map<String, Integer> internalGetKeyCodes() {
		
		Map<String, Integer> keys = new HashMap<String, Integer>();
		
		for (Field f : KeyEvent.class.getFields()) {
			int mod = f.getModifiers();
			String name = f.getName();
			if (name.startsWith("KEYCODE_") && Modifier.isPublic(mod) && Modifier.isStatic(mod) && 
					Modifier.isFinal(mod) && f.getType().equals(int.class) ) {
				try {
					keys.put(name, (Integer)f.get(null));
				} catch (Exception e) {
					Trace.writeLine(e);
				}
			}
		}
		
		return keys;
	}
	
	/***
	 * Gets the current rotation of the display
	 * 
	 * @return		The current rotation of the display: 0 = 0; 1 = 90; 2 = 180; 3 = 270
	 * @since		1.0.0.0
	 */
	public int getDisplayRotation() {
		return AutomatorBridge.getInstance().getDisplayRotation();
	}
	
	/***
	 * Gets the default long press time used by the system
	 * 
	 * @return		The default long press time used by the system
	 * @since		1.0.0.0
	 */
	public long getSystemLongPressTime() {
		return AutomatorBridge.getInstance().getSystemLongPressTime();
	}
	
    /***
     * Handle a drag in any direction.
     * 
     * @param 		downX
     * @param 		downY
     * @param 		upX
     * @param 		upY
     * @param 		steps
     * @return 		true if the drag executed successfully
     * @since		1.0.0.0
     */
	public boolean drag(int startX, int startY, int endX, int endY, int steps) {
		return swipe(startX, startY, endX, endY, steps, true /*drag*/);
	}
	
    /***
     * Handle a swipe in any direction.
     * 
     * @param 		downX
     * @param 		downY
     * @param 		upX
     * @param 		upY
     * @param 		steps
     * @return 		true if the swipe executed successfully
     * @since		1.0.0.0
     */
    public boolean swipe(int downX, int downY, int upX, int upY, int steps) {
        return swipe(downX, downY, upX, upY, steps, false /*drag*/);
    }
	
    /***
     * Handle swipes/drags in any direction.
     * 
     * @param 		downX
     * @param 		downY
     * @param 		upX
     * @param 		upY
     * @param 		steps
     * @param 		drag when true, the swipe becomes a drag swipe
     * @return 		true if the swipe executed successfully
     * @since		1.0.0.0
     */
	private boolean swipe(int downX, int downY, int upX, int upY, int steps, boolean drag) {
        
		boolean ret = false;
        int swipeSteps = steps;
        double xStep = 0;
        double yStep = 0;

        // avoid a divide by zero
        if(swipeSteps == 0)
            swipeSteps = 1;

        xStep = ((double)(upX - downX)) / swipeSteps;
        yStep = ((double)(upY - downY)) / swipeSteps;

        // first touch starts exactly at the point requested
        ret = touchDown(downX, downY);
        if (drag)
            SystemClock.sleep(getSystemLongPressTime());
        for(int i = 1; i < swipeSteps; i++) {
            ret &= touchMove(downX + (int)(xStep * i), downY + (int)(yStep * i));
            if(ret == false)
                break;
            // set some known constant delay between steps as without it this
            // become completely dependent on the speed of the system and results
            // may vary on different devices. This guarantees at minimum we have
            // a preset delay.
            SystemClock.sleep(MOTION_EVENT_INJECTION_DELAY_MILLIS);
        }
        if (drag)
            SystemClock.sleep(REGULAR_CLICK_LENGTH);
        ret &= touchUp(upX, upY);
        return(ret);
	}
	
    /***
     * Performs a swipe between points in the Point array.
     * 
     * @param 		segments is Point array containing at least one Point object
     * @param 		segmentSteps steps to inject between two Points
     * @return 		true on success
     * @since		1.0.0.0
     */
    public boolean swipe(Point[] segments, int segmentSteps) {
        boolean ret = false;
        int swipeSteps = segmentSteps;
        double xStep = 0;
        double yStep = 0;

        // avoid a divide by zero
        if(segmentSteps == 0)
            segmentSteps = 1;

        // must have some points
        if(segments.length == 0)
            return false;

        // first touch starts exactly at the point requested
        ret = touchDown(segments[0].x, segments[0].y);
        for(int seg = 0; seg < segments.length; seg++) {
            if(seg + 1 < segments.length) {

                xStep = ((double)(segments[seg+1].x - segments[seg].x)) / segmentSteps;
                yStep = ((double)(segments[seg+1].y - segments[seg].y)) / segmentSteps;

                for(int i = 1; i < swipeSteps; i++) {
                    ret &= touchMove(segments[seg].x + (int)(xStep * i),
                            segments[seg].y + (int)(yStep * i));
                    if(ret == false)
                        break;
                    // set some known constant delay between steps as without it this
                    // become completely dependent on the speed of the system and results
                    // may vary on different devices. This guarantees at minimum we have
                    // a preset delay.
                    SystemClock.sleep(MOTION_EVENT_INJECTION_DELAY_MILLIS);
                }
            }
        }
        ret &= touchUp(segments[segments.length - 1].x, segments[segments.length -1].y);
        return(ret);
    }
	
    /***
     * 
     * 
     * @param motionEnvent
     * @param index
     * @return
     * @since		1.0.0.0
     */
    private int getPointerAction(int motionEnvent, int index) {
        return motionEnvent + (index << MotionEvent.ACTION_POINTER_INDEX_SHIFT);
    }
    
    /**
     * Performs a multi-touch gesture
     *
     * Takes a series of touch coordinates for at least 2 pointers. Each pointer must have
     * all of its touch steps defined in an array of {@link PointerCoords}. By having the ability
     * to specify the touch points along the path of a pointer, the caller is able to specify
     * complex gestures like circles, irregular shapes etc, where each pointer may take a
     * different path.
     *
     * To create a single point on a pointer's touch path
     * <code>
     *       PointerCoords p = new PointerCoords();
     *       p.x = stepX;
     *       p.y = stepY;
     *       p.pressure = 1;
     *       p.size = 1;
     * </code>
     * @param touches each array of {@link PointerCoords} constitute a single pointer's touch path.
     *        Multiple {@link PointerCoords} arrays constitute multiple pointers, each with its own
     *        path. Each {@link PointerCoords} in an array constitute a point on a pointer's path.
     * @return <code>true</code> if all points on all paths are injected successfully, <code>false
     *        </code>otherwise
     * @since 1.0.0.0
     */
    public boolean performMultiPointerGesture(PointerCoords[] ... touches) {
        boolean ret = true;
        if (touches.length < 2) {
            throw new IllegalArgumentException("Must provide coordinates for at least 2 pointers");
        }

        // Get the pointer with the max steps to inject.
        int maxSteps = 0;
        for (int x = 0; x < touches.length; x++)
            maxSteps = (maxSteps < touches[x].length) ? touches[x].length : maxSteps;

        // specify the properties for each pointer as finger touch
        PointerProperties[] properties = new PointerProperties[touches.length];
        PointerCoords[] pointerCoords = new PointerCoords[touches.length];
        for (int x = 0; x < touches.length; x++) {
            PointerProperties prop = new PointerProperties();
            prop.id = x;
            prop.toolType = MotionEvent.TOOL_TYPE_FINGER;
            properties[x] = prop;

            // for each pointer set the first coordinates for touch down
            pointerCoords[x] = touches[x][0];
        }

        // Touch down all pointers
        long downTime = SystemClock.uptimeMillis();
        MotionEvent event;
        event = MotionEvent.obtain(downTime, SystemClock.uptimeMillis(), MotionEvent.ACTION_DOWN, 1,
                properties, pointerCoords, 0, 0, 1, 1, 0, 0, InputDevice.SOURCE_TOUCHSCREEN, 0);
        ret &= injectEventSync(event);

        for (int x = 1; x < touches.length; x++) {
            event = MotionEvent.obtain(downTime, SystemClock.uptimeMillis(),
                    getPointerAction(MotionEvent.ACTION_POINTER_DOWN, x), x + 1, properties,
                    pointerCoords, 0, 0, 1, 1, 0, 0, InputDevice.SOURCE_TOUCHSCREEN, 0);
            ret &= injectEventSync(event);
        }

        // Move all pointers
        for (int i = 1; i < maxSteps - 1; i++) {
            // for each pointer
            for (int x = 0; x < touches.length; x++) {
                // check if it has coordinates to move
                if (touches[x].length > i)
                    pointerCoords[x] = touches[x][i];
                else
                    pointerCoords[x] = touches[x][touches[x].length - 1];
            }

            event = MotionEvent.obtain(downTime, SystemClock.uptimeMillis(),
                    MotionEvent.ACTION_MOVE, touches.length, properties, pointerCoords, 0, 0, 1, 1,
                    0, 0, InputDevice.SOURCE_TOUCHSCREEN, 0);

            ret &= injectEventSync(event);
            SystemClock.sleep(MOTION_EVENT_INJECTION_DELAY_MILLIS);
        }

        // For each pointer get the last coordinates
        for (int x = 0; x < touches.length; x++)
            pointerCoords[x] = touches[x][touches[x].length - 1];

        // touch up
        for (int x = 1; x < touches.length; x++) {
            event = MotionEvent.obtain(downTime, SystemClock.uptimeMillis(),
                    getPointerAction(MotionEvent.ACTION_POINTER_UP, x), x + 1, properties,
                    pointerCoords, 0, 0, 1, 1, 0, 0, InputDevice.SOURCE_TOUCHSCREEN, 0);
            ret &= injectEventSync(event);
        }

        // first to touch down is last up
        event = MotionEvent.obtain(downTime, SystemClock.uptimeMillis(), MotionEvent.ACTION_UP, 1,
                properties, pointerCoords, 0, 0, 1, 1, 0, 0, InputDevice.SOURCE_TOUCHSCREEN, 0);
        ret &= injectEventSync(event);
        return ret;
    }	
	
    /***
     * Simulates a finger up event
     * 
     * @param 		x	x-coordinate from which to finger up	
     * @param 		y	y-coordinate from which to finger up	
     * @return		True if fingered up successfully; false otherwise
     * @since		1.0.0.0
     */
	public boolean touchUp(int x, int y) {
		
		try {
			return (Boolean)m_touchUp.invoke(m_controller, x, y);
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		return false;
	}
	
    /***
     * Simulates a finger down event
     * 
     * @param 		x	x-coordinate to finger down	
     * @param 		y	y-coordinate to finger down	
     * @return		True if fingered down successfully; false otherwise
     * @since		1.0.0.0
     */
	public boolean touchDown(int x, int y) {
		
		try {
			return (Boolean)m_touchDown.invoke(m_controller, x, y);
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		return false;
	}
	
	/***
	 * Simulates a finger move while the finger is touched down
	 * 
	 * @param 		x		The end x-coordinate of the finger move
	 * @param 		y		The end y-coordinate of the finger move
	 * @return		True if finger moved successfully; false otherwise
	 */
	public boolean touchMove(int x, int y) {
		
		try {
			return (Boolean)m_touchMove.invoke(m_controller, x, y);
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		return false;
	}
	
	/***
	 * Simulates a key press
	 * 
	 * @param 		key			The code of the key	
	 * @param 		metaState	Flags indicating which meta keys are currently pressed
	 * @return		True is the key was successfully pressed; false otherwise
	 * @since		1.0.0.0
	 */
	public boolean sendKey(int key, int metaState) {
		
		if (m_sendKey != null) {
			try {
				return (Boolean)m_sendKey.invoke(m_controller, key, metaState);
			} catch (Exception e) {
				Trace.writeLine(e);
			}		
		}
		return false;
	}

	/***
	 * Simulates a long key press
	 * 
	 * @param 		key			The code of the key	
	 * @param 		metaState	Flags indicating which meta keys are currently pressed
	 * @return		True is the key was successfully pressed; false otherwise
	 * @since		1.0.0.0
	 */
	public boolean sendKeyLong(int key, int metaState) {
	
		final long eventTime = SystemClock.uptimeMillis();
		long sleep = (long)(getSystemLongPressTime() * 1.5f);
		int repeats = 1;
		
		KeyEvent down = new KeyEvent(eventTime, eventTime, KeyEvent.ACTION_DOWN, key, repeats, metaState, 
				KeyCharacterMap.VIRTUAL_KEYBOARD, 0, 0, InputDevice.SOURCE_KEYBOARD);
		
		KeyEvent up = new KeyEvent(eventTime + sleep, eventTime + sleep, KeyEvent.ACTION_UP, key, 0, metaState, 
				KeyCharacterMap.VIRTUAL_KEYBOARD, 0, 0, InputDevice.SOURCE_KEYBOARD);
		
		boolean success = injectEventSync(down);
		
		SystemClock.sleep(sleep);
		
		success &= injectEventSync(up);
		
		return success;
	
	}
	
	/***
	 * Simulates a scroll swipe
	 * 
	 * @param 		downX
	 * @param 		downY
	 * @param 		upX
	 * @param 		upY
	 * @param 		steps
	 * @return		True is the scroll swipe was performed successfully; false otherwise
	 * @since		1.0.0.0
	 */
	public boolean scrollSwipe(int downX, int downY, int upX, int upY, int steps) {
		
		try {
			return (Boolean)m_scrollSwipe.invoke(m_controller, downX, downY, upX, upY, steps);
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		return false;
	}
	
	/***
	 * Injects any event deriving from InputEvent -base event
	 * 
	 * @param 		event		Any event deriving from InputEvent -base event
	 * @return		true if success; false otherwise
	 * @since		1.0.0.0
	 */
	public boolean injectEventSync(InputEvent event) {
		
		try {
			return (Boolean)m_injectEventSync.invoke((AutomatorBridge.getInstance().isApi18OrLater() ? 
					m_controller : null), event);
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		
		return false;
	}
	
	/***
	 * Check if the device is in its natural orientation. This is determined by checking if the orientation is at 0 or 180 degrees.
	 * 
	 * @return		true if it is in natural orientation
	 * @since		1.0.0.0
	 */
	public boolean isNaturalOrientation() {

		int rotation = AutomatorBridge.getInstance().getDisplayRotation();
		return rotation == 0 || rotation == 2; //0 or 180
	}
	
	/***
	 * Simulates orienting the device to the left and also freezes rotation by disabling the sensors. 
	 * If you want to un-freeze the rotation and re-enable the sensors see unfreezeRotation().
	 * 
	 * @return		true if no exception were thrown
	 * @since		1.0.0.0
	 */
	public boolean setOrientationLeft() {
				
		try	{
			m_setRotationLeft.invoke(m_controller, new Object[] { });
			return true;
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		return false;
	}
	
	/***
	 * Simulates orienting the device into its natural orientation and also freezes rotation by disabling the sensors. 
	 * If you want to un-freeze the rotation and re-enable the sensors see unfreezeRotation().
	 * 
	 * @return		true if no exception were thrown
	 * @since		1.0.0.0
	 */
	public boolean setOrientationNatural() {

		try	{
			m_setRotationNatural.invoke(m_controller, new Object[] { });
			return true;
		} catch (Exception e) {
			Trace.writeLine(e);
		}

		return false;
	}
	
	/***
	 * Simulates orienting the device to the right and also freezes rotation by disabling the sensors. 
	 * If you want to un-freeze the rotation and re-enable the sensors see unfreezeRotation().
	 * 
	 * @return		true if no exception were thrown
	 * @since		1.0.0.0
	 */
	public boolean setOrientationRight() {
		
		try	{
			m_setRotationRight.invoke(m_controller, new Object[] { });
			return true;
		} catch (Exception e) {
			Trace.writeLine(e);
		}

		return false;
	}
	
	/***
	 * Repeats key press of volume down for given amount of times
	 * @param 		steps		Amount of repeats
	 * @return		True is success; False otherwise
	 * @since		1.0.0.0
	 */
	public boolean volDown(int steps) {
		
		int code = KeyEvent.KEYCODE_VOLUME_DOWN;
		
		for (int i = 0; i < steps; i++) {
			if (!sendKey(code, 0)) {
				return false;
			}
		}
		
		return true;
		
	}
	
	/***
	 * Repeats key press of volume up for given amount of times
	 * @param 		steps		Amount of repeats
	 * @return		True is success; False otherwise
	 * @since		1.0.0.0
	 */
	public boolean volUp(int steps) {
		
		int code = KeyEvent.KEYCODE_VOLUME_UP;
		
		for (int i = 0; i < steps; i++) {
			if (!sendKey(code, 0)) {
				return false;
			}
		}
		
		return true;
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
	public boolean tap(int x, int y, int duration) {
		
		try {
			boolean success = touchDown(x, y);
			SystemClock.sleep(duration);
			return success && touchUp(x,y);
		} catch (Exception e) {
			Trace.writeLine(e);
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
	public boolean longTap(int x, int y) {

		try {
			return (Boolean)m_longTap.invoke(m_controller, x, y);
		} catch (Exception e) {
			Trace.writeLine(e);
		}

		return false;
	}
	
	/**
	 * Tries to send a text in a currently selected UI object
	 * 
	 * @param 		text		Text to push	
	 * @return		True if successfully selected, False otherwise
	 * @since		1.0.0.0
	 */
	public boolean sendText(String text) {
		
		try {
			return (Boolean)m_sendText.invoke(m_controller, text);
		} catch (Exception e) {
			Trace.writeLine(e);
		}

		return false;
	}
	
	/***
	 * Pinches the display with two fingers
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
	 * @return 		True if successfully pinched; False otherwise
	 * @since		1.0.1.0
	 */
	public boolean pinch(int downX1, int downY1, int downX2, int downY2, 
			  int upX1, int upY1, int upX2, int upY2, int steps) {

		boolean ret = false;
		int pinchSteps = steps;	        
		long mDownTime;
		
		// avoid a divide by zero
		if(pinchSteps == 0)
			pinchSteps = 1;
		  
		PointerProperties pp1 = new PointerProperties();
		pp1.id = 0;
		pp1.toolType = MotionEvent.TOOL_TYPE_FINGER;
		PointerProperties pp2 = new PointerProperties();
		pp2.id = 1;
		pp2.toolType = MotionEvent.TOOL_TYPE_FINGER;
		PointerProperties[] properties = new PointerProperties[] { pp1, pp2 };
		
		PointerCoords pc1 = new PointerCoords();
		pc1.x = downX1;
		pc1.y = downY1;
		pc1.pressure = 1; 
		pc1.size = 1;
		PointerCoords pc2 = new PointerCoords();
		pc2.x = downX2;
		pc2.y = downY2;
		pc2.pressure = 1;
		pc2.size = 1;
		PointerCoords[] pointerCoords = new PointerCoords[] { pc1, pc2 };
		
		mDownTime = SystemClock.uptimeMillis();
		
		MotionEvent event1 = MotionEvent.obtain(mDownTime, mDownTime, 
		          		 	 MotionEvent.ACTION_DOWN, 
		          		 	 1, properties, pointerCoords, 0,  0, 1, 1, 0, 0, InputDevice.SOURCE_TOUCHSCREEN, 0);
		
		MotionEvent event2 = MotionEvent.obtain(mDownTime, mDownTime, 
							 MotionEvent.ACTION_POINTER_DOWN + (pp2.id << MotionEvent.ACTION_POINTER_INDEX_SHIFT), 
							 2, properties, pointerCoords, 0, 0, 1, 1, 0, 0, InputDevice.SOURCE_TOUCHSCREEN, 0);
		
		double stepX1 = (double)((upX1 - downX1)) / pinchSteps;
		double stepY1 = (double)((upY1 - downY1)) / pinchSteps;
		double stepX2 = (double)((upX2 - downX2)) / pinchSteps;
		double stepY2 = (double)((upY2 - downY2)) / pinchSteps;
		
		ret = injectEventSync(event1);
		ret &= injectEventSync(event2);
		
		for (int i = 1; i < pinchSteps; i++) {
		  
		  pc1.x = downX1 + (int)(stepX1 * i);
		  pc1.y = downY1 + (int)(stepY1 * i);
		  pc2.x = downX2 + (int)(stepX2 * i);
		  pc2.y = downY2 + (int)(stepY2 * i);
		
		  pointerCoords[0] = pc1;
		  pointerCoords[1] = pc2;
		  
		  final long eventTime = SystemClock.uptimeMillis();
		  
		  event1 = MotionEvent.obtain(mDownTime, eventTime,
		           MotionEvent.ACTION_MOVE, 
		           2, properties, pointerCoords, 0, 0, 1, 1, 0, 0, InputDevice.SOURCE_TOUCHSCREEN, 0);
		
		  ret &=injectEventSync(event1);
		  
		  if (!ret) {
		  	break;
		  }
		  // set some known constant delay between steps as without it this
		  // become completely dependent on the speed of the system and results
		  // may vary on different devices. This guarantees at minimum we have
		  // a preset delay.
		  SystemClock.sleep(5);
		}
		
		pc1.x = upX1;
		pc1.y = upY1;
		pc2.x = upX2;
		pc2.y = upY2;
		pointerCoords[0] = pc1;
		pointerCoords[1] = pc2;
		
		final long eventTime = SystemClock.uptimeMillis();
		
		event2 = MotionEvent.obtain(mDownTime, eventTime,
				 MotionEvent.ACTION_POINTER_UP + (pp2.id << MotionEvent.ACTION_POINTER_INDEX_SHIFT), 
				 2, properties, pointerCoords, 0, 0, 1, 1, 0, 0, InputDevice.SOURCE_TOUCHSCREEN, 0);
		
		event1 = MotionEvent.obtain(mDownTime, eventTime, 
				 MotionEvent.ACTION_UP,
				 1, properties, pointerCoords, 0, 0, 1, 1, 0, 0, InputDevice.SOURCE_TOUCHSCREEN, 0);
		
		ret &= injectEventSync(event2);    
		ret &= injectEventSync(event1);
		
		return ret;
	}
	
	/***
	 * 
	 * @param 		from
	 * @param 		radius
	 * @param 		angle
	 * @param 		steps
	 * @return		
	 * @since		1.0.1.0
	 */
	public boolean pinchOut(Point from, int radius, double angle, int steps) {
		
		Point p1 = getPointFromCircle(from, radius, angle, false);
		Point p2 = getPointFromCircle(from, radius, (angle - 180.0), false);
		return pinch(from.x, from.y, from.x, from.y, p1.x, p1.y, p2.x, p2.y, steps);
	}
	
	/***
	 * 
	 * @param 		to
	 * @param 		radius
	 * @param 		angle
	 * @param 		steps
	 * @return		
	 * @since		1.0.1.0
	 */
	public boolean pinchIn(Point to, int radius, double angle, int steps) {
		Point p1 = getPointFromCircle(to, radius, angle, false);
		Point p2 = getPointFromCircle(to, radius, (angle - 180.0), false);
		return pinch(p1.x, p1.y, p2.x, p2.y, to.x, to.y, to.x, to.y, steps);
	}
	
	/***
	 * 
	 * @param 		center
	 * @param 		radius
	 * @param 		startAngle
	 * @param 		stopAngle
	 * @param 		intervalAngle
	 * @param 		clockwise
	 * @return		
	 * @since		1.0.1.0
	 */
	public boolean curvedSwipe(Point center, int radius, double startAngle, double stopAngle,
			double intervalAngle, boolean clockwise) {
		
		List<Point> points = new ArrayList<Point>();
				
		intervalAngle = Math.abs(intervalAngle);
		
		if (intervalAngle == 0) {
			intervalAngle = 1;
		}
		else {
			while (intervalAngle > 360.0) {
				intervalAngle -= 360.0;
			}
		}
		
		if (startAngle < stopAngle) {
			for(double angle = startAngle; angle <= stopAngle; angle += intervalAngle) {
				points.add(getPointFromCircle(center, radius, angle, clockwise));
			}
		}
		else if (startAngle > stopAngle) {
			for(double angle = startAngle; angle >= stopAngle; angle -= intervalAngle) {
				points.add(getPointFromCircle(center, radius, angle, clockwise));
			}
		}
		else if (startAngle == stopAngle) {
			return curvedSwipe(center, radius, startAngle, (startAngle + 360.0), intervalAngle, clockwise);
		}
		
		return swipe(points.toArray(new Point[points.size()]), 1);
	}
	
	/***
	 * 
	 * @param 		center
	 * @param 		radius
	 * @param 		angle
	 * @return		
	 * @since		1.0.1.0
	 */
	private Point getPointFromCircle(Point center, int radius, double angle, boolean clockwise) {
		
		Point p = new Point();
		double radius_angle = getRadius(angle, clockwise);
		p.x = center.x + (int)Math.round(Math.cos(radius_angle) * (double)Math.abs(radius));
		p.y = center.y + (int)Math.round(Math.sin(radius_angle) * (double)Math.abs(radius));
		return p;
	}
	
	/***
	 * 
	 * @param degrees
	 * @return
	 */
	private double getRadius(double angle, boolean clockwise) {
		double radius = Math.PI * angle / 180.0;
		return !clockwise ? radius * -1.0 : radius;
	}
}
