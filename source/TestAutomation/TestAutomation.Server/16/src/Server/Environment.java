package Server;

import android.os.Bundle;

/***
 * Class for retrieving environmental values from the system
 * 
 * @author		Sami Utriainen
 * @version		1.0.0.0
 *
 */
public class Environment {
	
	private static Bundle m_args = null;
	
	/**
	 * Sets the command line arguments (to be called only by the entry method of the TAServer class)
	 * 
	 * @param 		args		Command line arguments
	 * @since		1.0.0.0
	 */
	public static synchronized void setCommandLineArgs(Bundle args) {
		if (args != null) {
			m_args = args;
		}
	}
	
	/**
	 * Returns a bundle containing the command-line arguments for the current process.
	 * 
	 * @return		Command-line arguments for the current process. (key-value pairs)
	 * @since		1.0.0.0
	 */
	public static synchronized Bundle getCommandLineArgs() {
		
		if (m_args == null) {
			m_args = new Bundle();
		}
		return m_args;
	}
	
	/**
	 * Gets the newline string defined for this environment.
	 * 
	 * @return		A string containing "\r\n" for non-Unix platforms, or a string containing
     *				"\n" for Unix platforms.
     *@since		1.0.0.0
	 */
	public static String getNewLine() {
		return System.getProperty("line.separator");
	}
	
	/**
	 * Gets String containing the current platform version number
	 * 
	 * @return		String containing the current platform version number
	 * @since		1.0.0.0
	 */
	public static String getOSVersion() {
		return android.os.Build.VERSION.RELEASE;
	}
	
	/**
	 * Gets the fully qualified path of the current working directory.
	 * 
	 * @return		A string containing a directory path.
	 * @since		1.0.0.0
	 */
	public static String getCurrentDirectory() {
		return System.getProperty("user.dir");
	}
	
	/***
	 * 
	 * @return
	 */
	public static boolean isRoot() {
		if (Environment.getCommandLineArgs().containsKey("root")) {
			
			try {
				return Boolean.parseBoolean(Environment.getCommandLineArgs().getString("root"));
			} catch (Exception e) {		
				return false;
			}
		}
		return false;
	}
}
