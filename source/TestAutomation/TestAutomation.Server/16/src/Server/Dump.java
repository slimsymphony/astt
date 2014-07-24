package Server;

import java.io.IOException;
import java.io.StringWriter;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.regex.Pattern;

import org.xmlpull.v1.XmlSerializer;

import com.android.uiautomator.core.UiDevice;

import android.graphics.Rect;
import android.util.Xml;
import android.view.accessibility.*;

/***
 * Class for retrieving the UI layout hierarchy dump
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 *
 */
public class Dump {
	
    private static final String[] NAF_EXCLUDED_CLASSES = new String[] {
        android.widget.GridView.class.getName(), android.widget.GridLayout.class.getName(),
        android.widget.ListView.class.getName(), android.widget.TableLayout.class.getName()
	};
	
    private static final Pattern mInvalidXmlCharPattern = 
    		Pattern.compile("[^\\u0009\\u000a\\u000d\\u0020-\\u007e\\u0085\\u00a0-\\ud7ff\\ue000-\\ufdcf\\ufde0-\\ufffd]");
    
    /***
     * Private constructor, as we provide only singleton for this class object
     * 
     * @since		1.0.0.0
     */
	private Dump() {
	}
	
    /**
     * Using {@link AccessibilityNodeInfo} this method will walk the layout hierarchy
     * and generates an xml dump to the location specified by <code>dumpFile</code>
     * 
     * @throws 		SecurityException 
     * @throws 		NoSuchFieldException 
     * @throws 		IllegalAccessException 
     * @throws 		IllegalArgumentException 
     * @throws 		NoSuchMethodException 
     * @throws 		InvocationTargetException
     * @since		1.0.0.0 
     */
    public static String getDump(boolean refresh) 
    		throws NoSuchFieldException, SecurityException, IllegalArgumentException, IllegalAccessException, 
    		InvocationTargetException, NoSuchMethodException { 	
    	
    	AccessibilityNodeInfo root = AutomatorBridge.getInstance().getAccessibilityRootNode();
    	
    	if (root == null) {
            Trace.writeLine("WARNING: No dump received from AccessibilityService");
    		return null;
        }
    	
    	if (refresh && AutomatorBridge.getInstance().isApi18OrLater()) {
	    	try {
	    		//Valid from API18 onwards
		    	Method refresher = root.getClass().getMethod("refresh");
		    	if (refresher != null)
		    	{
		    		for(int i = 0; i < 10; i++) {
			    		//If this method returns false this info is obsolete
		    			//since it represents a view that is no longer in the view tree and should
			    		//be recycled.
			    		Boolean success = (Boolean)refresher.invoke(root);
			    		if (!success) {
			    			Trace.writeLine("WARNING: obsolte AccessibilityinfoNode found, recycling it");
			    			root.recycle();
			    			root = AutomatorBridge.getInstance().getAccessibilityRootNode();
			    		} else {
			    			break;
			    		}
		    		}

		    	}
	    	} catch (Exception ex) {
	    		Trace.writeLine(ex);
	    	}
    	}
    	
    	int width = UiDevice.getInstance().getDisplayWidth();
    	int height = UiDevice.getInstance().getDisplayHeight();
    	int rotation = AutomatorBridge.getInstance().getDisplayRotation();
    	
    	
    	StringWriter stringWriter = new StringWriter();
    	
        try {
            
        	XmlSerializer serializer = Xml.newSerializer();
            serializer.setOutput(stringWriter);
            serializer.startDocument("UTF-8", true);
            serializer.startTag("", "hierarchy");
            serializer.attribute("", "rotation", Integer.toString(rotation));
            dumpNodeRec(root, serializer, 0, width, height);
            serializer.endTag("", "hierarchy");
            serializer.endDocument();

        } catch (IOException e) {
        	Trace.writeLine(e);
        }
               
        return stringWriter.toString();
    }
    
    /***
     * Writes the AccessibilityNode information recursively into a xml serializer
     * 
     * @param 		node
     * @param 		serializer
     * @param 		index
     * @throws 		IOException
     * @since		1.0.0.0
     */
    private static void dumpNodeRec(AccessibilityNodeInfo node, XmlSerializer serializer, int index, int width, int height)
    		throws IOException {
        
    	serializer.startTag("", "node");
        if (!nafExcludedClass(node) && !nafCheck(node))
            serializer.attribute("", "NAF", Boolean.toString(true));
        serializer.attribute("", "index", Integer.toString(index));
       	serializer.attribute("", "text", safeCharSeqToString(node.getText()));
        
        //Resource-id became supported in API level 18
        try {
        	String resourceName = (String)node.getClass().getDeclaredMethod(Constants.GET_VIEW_ID_RESOURCE_NAME, new Class<?>[] { }).
        			invoke(node, new Object[] { });
        	serializer.attribute("", "resource-id", safeCharSeqToString(resourceName));
        } catch (Exception e) {
        	serializer.attribute("", "resource-id", "");
        }       
        
        serializer.attribute("", "class", safeCharSeqToString(node.getClassName()));
        serializer.attribute("", "package", safeCharSeqToString(node.getPackageName()));
      	serializer.attribute("", "content-desc", safeCharSeqToString(node.getContentDescription()));
        serializer.attribute("", "checkable", Boolean.toString(node.isCheckable()));
        serializer.attribute("", "checked", Boolean.toString(node.isChecked()));
        serializer.attribute("", "clickable", Boolean.toString(node.isClickable()));
        serializer.attribute("", "enabled", Boolean.toString(node.isEnabled()));
        serializer.attribute("", "focusable", Boolean.toString(node.isFocusable()));
        serializer.attribute("", "focused", Boolean.toString(node.isFocused()));
        serializer.attribute("", "scrollable", Boolean.toString(node.isScrollable()));
        serializer.attribute("", "long-clickable", Boolean.toString(node.isLongClickable()));
        serializer.attribute("", "password", Boolean.toString(node.isPassword()));
        serializer.attribute("", "selected", Boolean.toString(node.isSelected()));
        serializer.attribute("", "bounds", getVisibleBoundsInScreen(node, width, height).toShortString());
        
        int count = node.getChildCount();
        for (int i = 0; i < count; i++) {
            AccessibilityNodeInfo child = node.getChild(i);
            if (child != null) {
            	if (child.isVisibleToUser()) {
        			dumpNodeRec(child, serializer, i, width, height);
        			child.recycle();
            	} else {
            		//Trace.writeLine(String.format("Skipping invisible child: %s", child.toString()));
            	}
            } else {
            	//Trace.writeLine(String.format("Null child %d/%d, parent: %s",
                //        i, count, node.toString()));
            }
        }
        serializer.endTag("", "node");
    }
	
    /***
     * Returns the node's bounds clipped to the size of the display
     * 
     * @param 		node		The node from which to check
     * @param 		width		Pixel width of the display
     * @param 		height		Pixel height of the display
     * @return		Null if node is null, else a Rect containing visible bounds
     */
    private static Rect getVisibleBoundsInScreen(AccessibilityNodeInfo node, int width, int height) {
	    
    	if (node == null) {
	        return null;
	    }
	    // targeted node's bounds
	    Rect nodeRect = new Rect();
	    node.getBoundsInScreen(nodeRect);
	
	    Rect displayRect = new Rect();
	    displayRect.top = 0;
	    displayRect.left = 0;
	    displayRect.right = width;
	    displayRect.bottom = height;
	
	    nodeRect.intersect(displayRect);
	    return nodeRect;
    }
    
    /**
     * The list of classes to exclude my not be complete. We're attempting to
     * only reduce noise from standard layout classes that may be falsely
     * configured to accept clicks and are also enabled.
     *
     * @param 		node
     * @return 		true if node is excluded.
     * @since		1.0.0.0
     */
    private static boolean nafExcludedClass(AccessibilityNodeInfo node) {
        String className = safeCharSeqToString(node.getClassName());
        for(String excludedClassName : NAF_EXCLUDED_CLASSES) {
            if(className.endsWith(excludedClassName))
                return true;
        }
        return false;
    }

    /**
     * We're looking for UI controls that are enabled, clickable but have no
     * text nor content-description. Such controls configuration indicate an
     * interactive control is present in the UI and is most likely not
     * accessibility friendly. We refer to such controls here as NAF controls
     * (Not Accessibility Friendly)
     *
     * @param 		node
     * @return 		false if a node fails the check, true if all is OK
     * @since		1.0.0.0
     */
    private static boolean nafCheck(AccessibilityNodeInfo node) {
        boolean isNaf = node.isClickable() && node.isEnabled()
                && safeCharSeqToString(node.getContentDescription()).isEmpty()
                && safeCharSeqToString(node.getText()).isEmpty();

        if (!isNaf)
            return true;

        // check children since sometimes the containing element is clickable
        // and NAF but a child's text or description is available. Will assume
        // such layout as fine.
        return childNafCheck(node);
    }

    /**
     * This should be used when it's already determined that the node is NAF and
     * a further check of its children is in order. A node maybe a container
     * such as LinerLayout and may be set to be clickable but have no text or
     * content description but it is counting on one of its children to fulfill
     * the requirement for being accessibility friendly by having one or more of
     * its children fill the text or content-description. Such a combination is
     * considered by this dumper as acceptable for accessibility.
     *
     * @param 		node
     * @return 		false if node fails the check.
     * @since		1.0.0.0
     */
    private static boolean childNafCheck(AccessibilityNodeInfo node) {
        int childCount = node.getChildCount();
        for (int x = 0; x < childCount; x++) {
            AccessibilityNodeInfo childNode = node.getChild(x);
            
            if (childNode != null) {
            
	            if (!safeCharSeqToString(childNode.getContentDescription()).isEmpty()
	                    || !safeCharSeqToString(childNode.getText()).isEmpty()) {
	                return true;
	            }
	
	            if (childNafCheck(childNode)) {
	                return true;
	            }
            }
        }
        return false;
    }

    /***
     * Converts a CharSequence into s String
     * 
     * @param 		cs			The CharSequence to convert
     * @return		Converted CharSequence
     * @since		1.0.0.0
     */
    private static String safeCharSeqToString(CharSequence cs) {
        
    	return cs == null ? "" : mInvalidXmlCharPattern.matcher(cs).replaceAll(".");
    }
}
