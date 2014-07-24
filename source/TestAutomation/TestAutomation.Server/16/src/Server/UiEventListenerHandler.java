package Server;

import android.view.accessibility.AccessibilityEvent;

/**
 * Handler interface for UI (Accessibility) events fired by the system
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public interface UiEventListenerHandler {
	
	/**
	 * Method to be implemented by the handlers
	 * 
	 * @param 		event		AccessibilityEvent raised by the system
	 * @since		1.0.0.0
	 */
	public void onUiEvent(AccessibilityEvent event);
}
