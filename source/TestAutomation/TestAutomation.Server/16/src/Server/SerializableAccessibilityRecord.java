package Server;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

import android.view.accessibility.AccessibilityRecord;

/***
 * This class is created in order to be able to serialize needed values from
 * android.view.accessibility.AccessibilityRecord, which itself isn't serializable
 * 
 * android.view.accessibility.AccessibilityRecord:
 * "Represents a record in an AccessibilityEvent and contains information about state
 * change of its source View. When a view fires an accessibility event it requests from 
 * its parent to dispatch the constructed event. The parent may optionally append a record 
 * for itself for providing more context to AccessibilityServices. Hence, accessibility 
 * services can facilitate additional accessibility records to enhance feedback."
 * 
 * http://developer.android.com/reference/android/view/accessibility/AccessibilityRecord.html
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public class SerializableAccessibilityRecord {

	 protected static final Pattern mInvalidXmlCharPattern = 
	    		Pattern.compile("[^\\u0009\\u000a\\u000d\\u0020-\\u007e\\u0085\\u00a0-\\ud7ff\\ue000-\\ufdcf\\ufde0-\\ufffd]");
	    
	
	protected boolean m_isOkay = false;
	
	/***
	 * Parametreless class constructor (due to Json serialization)
	 * 
	 * @since		1.0.0.0
	 */
	public SerializableAccessibilityRecord() {
	}
	
	/***
	 * Everything ok with the event
	 * 
	 * @return
	 * @since		1.0.0.0
	 */
	public boolean isOkay() {
		return m_isOkay;
	}
	
	/***
	 * Class constructor
	 * 
	 * @param 		record		Original android.view.accessibility.AccessibilityRecord
	 * @since		1.0.0.0
	 */
	public SerializableAccessibilityRecord(AccessibilityRecord record) {
		
		if (record == null) {
			Trace.writeLine("Null record received");
		}
		else {
			
			m_isOkay = true;
			
			try {
				
				ClassName = record.getClassName() != null ? record.getClassName().toString() : null;
				Text = new ArrayList<String>();
				List<CharSequence> text = record.getText();
				if (text != null) {
					for (CharSequence cs : text) {
						if (cs != null) {
							Text.add(mInvalidXmlCharPattern.matcher(cs).replaceAll("."));
						}
					}
				}
				ContentDescription = record.getContentDescription() != null ?  mInvalidXmlCharPattern.matcher(record.getContentDescription()).replaceAll(".") : null;
				ItemCount = record.getItemCount();
				CurrentItemIndex = record.getCurrentItemIndex();
				IsEnabled = record.isEnabled();
				IsPassword = record.isPassword();
				IsChecked = record.isChecked();
				IsFullScreen = record.isFullScreen();
				IsScrollable = record.isScrollable();
				BeforeText = record.getBeforeText() != null ? mInvalidXmlCharPattern.matcher(record.getBeforeText()).replaceAll(".") : null;
				FromIndex = record.getFromIndex();
				ToIndex = record.getToIndex();
				ScrollX = record.getScrollX();
				ScrollY = record.getScrollY();
				AddedCount = record.getAddedCount();
				RemovedCount = record.getRemovedCount();
				
			} catch (Exception e) {
				Trace.writeLine(e);
			}
		}
	}
	
	/***
	 * Creates a SerializableAccessibilityRecord instance from an original android.view.accessibility.AccessibilityRecord
	 * 
	 * @param 		record		An original android.view.accessibility.AccessibilityRecord
	 * @return		A SerializableAccessibilityRecord instance
	 * @since		1.0.0.0
	 */
	public static SerializableAccessibilityRecord fromAccessibilityRecord(AccessibilityRecord record) {
		return new SerializableAccessibilityRecord(record);
	}
	
	/***
	 * Gets or sets the class name of the source
	 */
    public String ClassName;
    
    /***
     * Gets or sets the text of the event. The index in the list represents the priority of the text. 
     * Specifically, the lower the index the higher the priority.
     */
    public List<String> Text;
    
    /***
     * Gets or sets the description of the source
     */
    public String ContentDescription;
    
    /***
     * Gets or sets the number of items that can be visited
     */
    public int ItemCount;
    
    /***
     * Gets or sets the index of the source in the list of items the can be visited
     */
    public int CurrentItemIndex;
    
    /***
     * Gets or sets if the source is enabled
     */
    public boolean IsEnabled;
    
    /***
     * Gets or sets if the source is a password field
     */
    public boolean IsPassword;
    
    /***
     * Gets or sets if the source is checked
     */
    public boolean IsChecked;
    
    /***
     * Gets or sets if the source is taking the entire screen
     */
    public boolean IsFullScreen;
    
    /***
     * Gets or sets if the source is scrollable
     */
    public boolean IsScrollable;
    
    /***
     * Gets or sets the text before a change
     */
    public String BeforeText;
    
    /***
     * Gets or sets the index of the first character of the changed sequence, or the beginning 
     * of a text selection or the index of the first visible item when scrolling
     */
    public int FromIndex;
   
    /***
     * Gets or sets the index of text selection end or the index of the last visible item when scrolling
     */
    public int ToIndex;
    
    /***
     * Gets or sets the scroll offset of the source left edge in pixels
     */
    public int ScrollX;
    
    /***
     * Gets or sets the scroll offset of the source top edge in pixels
     */
    public int ScrollY;
    
    /***
     * Gets or sets the number of added characters
     */
    public int AddedCount;
    
    /***
     * Gets or sets the number of removed characters
     */
    public int RemovedCount;
    
    /***
     * Gets the total number of page flips done in SurfaceFlinger; -1 with non-rooted devices
     */
    public int PageFlipCount;
    
    /***
     * Gets the timestamp when the page flip count was taken
     */
    public long PageFlipCountTimestamp;
}
