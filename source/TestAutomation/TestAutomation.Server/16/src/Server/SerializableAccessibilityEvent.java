package Server;

import java.util.ArrayList;
import java.util.List;

import android.view.accessibility.AccessibilityEvent;
import android.view.accessibility.AccessibilityRecord;

/***
 * This class is created in order to be able to serialize needed values from
 * android.view.accessibility.AccessibilityEvent, which itself isn't serializable
 * 
 * android.view.accessibility.AccessibilityEvent:
 * "This class represents accessibility events that are sent by the system when something 
 * notable happens in the user interface. For example, when a Button is clicked, a View is 
 * focused, etc.
 *
 * An accessibility event is fired by an individual view which populates the event with data 
 * for its state and requests from its parent to send the event to interested parties. 
 * The parent can optionally add an AccessibilityRecord for itself before dispatching a similar 
 * request to its parent. A parent can also choose not to respect the request for sending an event. 
 * The accessibility event is sent by the topmost view in the view tree. Therefore, 
 * an AccessibilityService can explore all records in an accessibility event to obtain more information 
 * about the context in which the event was fired.
 *
 * The main purpose of an accessibility event is to expose enough information for an AccessibilityService 
 * to provide meaningful feedback to the user. Sometimes however, an accessibility service may need more 
 * contextual information then the one in the event pay-load. In such cases the service can obtain the event 
 * source which is an AccessibilityNodeInfo (snapshot of a View state) which can be used for exploring 
 * the window content. Note that the privilege for accessing an event's source, thus the window content, 
 * has to be explicitly requested. For more details refer to AccessibilityService. If an accessibility 
 * service has not requested to retrieve the window content the event will not contain reference to its source. 
 * Also for events of type TYPE_NOTIFICATION_STATE_CHANGED the source is never available."
 * 
 * http://developer.android.com/reference/android/view/accessibility/AccessibilityEvent.html
 * 
 * @author		Sami Utriainen
 * @since		1.0.0.0
 *
 */
public class SerializableAccessibilityEvent extends SerializableAccessibilityRecord {
	
	/***
	 * Parametreless class constructor (due to Json serialization)
	 * 
	 * @since		1.0.0.0
	 */
	public SerializableAccessibilityEvent() {
	}
	
	/***
	 * Class constructor
	 * 
	 * @param 		event		Original android.view.accessibility.AccessibilityEvent
	 * @since		1.0.0.0
	 */
	public SerializableAccessibilityEvent(AccessibilityEvent event, int pageFlips, long pageFlipTimestamp) {
	    
		if (event == null) {
			Trace.writeLine("Null event received");
		} 
		else {
			
			m_isOkay = true;
			
			try {
				PageFlipCountTimestamp = pageFlipTimestamp;
				PageFlipCount = pageFlips;
				RecordCount = event.getRecordCount();
				EventType = event.getEventType();
				EventTime = event.getEventTime();
				PackageName = event.getPackageName() != null ? event.getPackageName().toString() : null;
				MovementGranularity = event.getMovementGranularity();
				Action = event.getAction();
				Records = new ArrayList<SerializableAccessibilityRecord>();
				ClassName = event.getClassName() != null ? event.getClassName().toString() : null;
				Text = new ArrayList<String>();
				List<CharSequence> text = event.getText();
				if (text != null) {
					for (CharSequence cs : text) {
						if (cs != null) {
							Text.add(mInvalidXmlCharPattern.matcher(cs).replaceAll("."));
						}
					}
				}
				ContentDescription = event.getContentDescription() != null ? mInvalidXmlCharPattern.matcher(event.getContentDescription()).replaceAll(".") : null;
				ItemCount = event.getItemCount();
				CurrentItemIndex = event.getCurrentItemIndex();
				IsEnabled = event.isEnabled();
				IsPassword = event.isPassword();
				IsChecked = event.isChecked();
				IsFullScreen = event.isFullScreen();
				IsScrollable = event.isScrollable();
				BeforeText = event.getBeforeText() != null ? mInvalidXmlCharPattern.matcher(event.getBeforeText()).replaceAll(".") : null;
				FromIndex = event.getFromIndex();
				ToIndex = event.getToIndex();
				ScrollX = event.getScrollX();
				ScrollY = event.getScrollY();
				AddedCount = event.getAddedCount();
				RemovedCount = event.getRemovedCount();
				
				for(int i = 0; i < RecordCount; i++) {
					AccessibilityRecord record = event.getRecord(i);
					SerializableAccessibilityRecord sr = 
							SerializableAccessibilityRecord.fromAccessibilityRecord(record);
					if (sr.isOkay()) {
						Records.add(sr);
					}
				}
				
			 } catch (Exception e) {
				 Trace.writeLine(e);
			 }
		}
	}
	
	/***
	 * Creates a SerializableAccessibilityEvent instance from an original android.view.accessibility.AccessibilityEvent
	 * 
	 * @param 		event		An original android.view.accessibility.AccessibilityEvent
	 * @return		A SerializableAccessibilityEvent instance
	 * @since		1.0.0.0
	 */
	public static SerializableAccessibilityEvent fromAccessibilityEvent(AccessibilityEvent event, int pageFlips, long pageFlipTimestamp) {
		return new SerializableAccessibilityEvent(event, pageFlips, pageFlipTimestamp);
	}
	
	/***
	 * Gets or sets the number of records contained in the event
	 */
    public int RecordCount;
    
    /***
     * Gets or sets the event type
     */
    public int EventType;
    
    /***
     * Gets or sets the time in which this event was sent
     */
    public long EventTime;
    
    /***
     * Gets or sets the package name of the source
     */
    public CharSequence PackageName;
    
    /***
     * Gets or sets the movement granularity that was traversed
     */
    public int MovementGranularity;
    
    /***
     * Gets or sets the performed action that triggered this event
     */
    public int Action;
    
    /***
     * Gets or sets the records contained in the event.
     */
    public List<SerializableAccessibilityRecord> Records;	
}
