package Server;

/**
 * Represents a character encoding.
 * 
 * @author 					Sami Utriainen
 * @version 				1.0.0.0
 *
 */
public class Encoding {
	
	private static final String DEFAULT_ENCODING = "ISO-8859-1";
	private static final String UTF8_ENCODING = "UTF-8";
	
	private static Encoding m_default = null;
	private static Encoding m_utf8 = null;
	
	private String m_bodyName = null;
	
	/**
	 * Initializes a new instance of the utils.Encoding class.
	 * 
	 * @since					1.0.0.0
	 */
	private Encoding() {
	}
	
	/**
	 * Initializes a new instance of the utils.Encoding class that corresponds
	 * to the specified code page name.
	 * 
	 * @param 		name		The code page name of the preferred encoding.
	 * @since					1.0.0.0
	 */
	private Encoding(String name) {
		m_bodyName = name;
	}
	
	/**
	 * Returns the encoding associated with the specified code page name.
	 * 
	 * @param 		name		The code page name of the preferred encoding.
	 * @return					The encoding associated with the specified code page.
	 * @since					1.0.0.0
	 */
	public static Encoding getEncoding(String name) {
		return new Encoding(name);
	}
	
	/**
	 * Gets an encoding for ISO-8859-1 code page
	 * 
	 * @return					An encoding for ISO-8859-1 code page
	 * @since					1.0.0.0
	 */
	public static Encoding getDefault() {
		
		if (m_default == null) {
			m_default = new Encoding(DEFAULT_ENCODING);
		}
		return m_default;
	}
	
	/**
	 * Gets an encoding for the UTF-8 format.
	 * 
	 * @return					An encoding for the UTF-8 format.
	 * @since					1.0.0.0
	 */
	public static Encoding getUtf8() {
		
		if (m_utf8 == null) {
			m_utf8 = new Encoding(UTF8_ENCODING);
		}
		return m_utf8;
	}
	
	/**
	 * Gets a name for the current encoding code page
	 * 
	 * @return					Name for the current encoding code page
	 * @since					1.0.0.0
	 */
	public String getBodyName() {
		return m_bodyName.toLowerCase();
	}
	
	/**
	 * Decodes all the bytes in the specified
     * byte array into a string.
     * 
	 * @param 		bytes		The byte array containing the sequence of bytes to decode.
	 * @return					A String containing the results of decoding the specified sequence of bytes.
	 * @since					1.0.0.0
	 */
	public String getString(byte[] bytes) {
		return getString(bytes, 0, bytes.length);
	}
	
	/**
	 * Decodes all the bytes in the specified
     * byte array into a string.
     * 
	 * @param 		bytes		The byte array containing the sequence of bytes to decode.
	 * @param 		index		The index of the first byte to decode.
	 * @return					A String containing the results of decoding the specified sequence of bytes.
	 * @since					1.0.0.0
	 */
	public String getString(byte[] bytes, int index) {
		return getString(bytes, index, (bytes.length - index));
	}
	
	/**
	 * Decodes all the bytes in the specified
     * byte array into a string.
     * 
	 * @param 		bytes		The byte array containing the sequence of bytes to decode.
	 * @param 		index		The index of the first byte to decode.
	 * @param		count		The number of bytes to decode.
	 * @return					A String containing the results of decoding the specified sequence of bytes.
	 * @since					1.0.0.0
	 */
	public String getString(byte[] bytes, int index, int count) {
		
		if (index > 0 || (index + count) > bytes.length) {
			bytes = BitConverter.take(bytes, index, count);//ByteBuffer.wrap(bytes, index, count).array();
		}
		
		try {
			return new String(bytes, m_bodyName);
		} catch (Exception e) {
			return null;
		}
	}
	
	/**
	 * Encodes all the characters in the specified
     * string into a sequence of bytes.
     * 
	 * @param 		s			The string containing the characters to encode.
	 * @return					A byte array containing the results of encoding the specified set of characters.
	 * @since					1.0.0.0
	 */
	public byte[] getBytes(String s) {
		
		try {
			return s.getBytes(m_bodyName);
		} catch (Exception e) {
			return null;
		}
	}
}
