package Server;

/**
 * Message counter class for different types of asynchronous messages sent by the server
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public class MessageCounters {

	private static short m_errorCounter = 0;
	private static short m_debugCounter = 0;
	
	/**
	 * Gets next transaction index for an error message
	 * 
	 * @return		Next transaction index for an error message
	 * @since		1.0.0.0	
	 */
	public static short getNextErrorIndex() {
		short index = m_errorCounter;
		m_errorCounter++;
		return index;
	}
	
	/**
	 * Gets next transaction index for an event message (always zero)
	 * 
	 * @return		Next transaction index for an event message
	 * @since		1.0.0.0	
	 */
	public static short getNextEventIndex() {
		return 0;
	}
	
	/**
	 * Gets next transaction index for a debug message
	 * 
	 * @return		Next transaction index for a debug message
	 * @since		1.0.0.0	
	 */
	public static short getNextDebugIndex() {
		short index = m_debugCounter;
		m_debugCounter++;
		return index;
	}
}
