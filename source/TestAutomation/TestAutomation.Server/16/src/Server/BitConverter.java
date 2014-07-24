package Server;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

/**
 * Converts base data types to an array of bytes, and an array of bytes to base
 * data types.
 * 
 * @author 		Sami Utriainen
 * @version 	1.0.0.0
 *
 */
public class BitConverter {

	/**
	 * Converts the numeric value of each element of a specified array of bytes
     * to its equivalent hexadecimal string representation.
     * 
	 * @param 		bytes		An array of bytes.
	 * @return		A string of hexadecimal pairs separated by hyphens, where each pair represents
     *				the corresponding element in value; for example, "7F-2C-4A-00".
     * @since 		1.0.0.0
	 */
	public static String getHexString (byte[] bytes) {
	    
		StringBuffer sb = new StringBuffer();

	    for (int i = 0; i < bytes.length; i++) {
	        sb.append(String.format("%02x", bytes[i]).toUpperCase());
	        if (i < (bytes.length - 1))
	        	sb.append("-");
	    }

	    return sb.toString();
	}
	
	/**
	 * Returns the specified 32-bit signed integer value as an array of bytes.
	 * @param 		value		The number to convert.
	 * @return		An array of bytes with length 4.
	 * @since 		1.0.0.0
	 */
	public static byte[] getBytes(int value) {
		return ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(value).array();
	}
	
	/**
	 * Returns the specified 16-bit signed integer value as an array of bytes.
	 * @param 		value		The number to convert.
	 * @return		An array of bytes with length 2.
	 * @since 1.0.0.0
	 */
	public static byte[] getBytes(short value) {
		return ByteBuffer.allocate(2).order(ByteOrder.LITTLE_ENDIAN).putShort(value).array();
	}
	
	/**
	 * Returns the specified 64-bit signed integer value as an array of bytes.
	 * @param 		value		The number to convert.
	 * @return		An array of bytes with length 8.
	 * @since 1.0.0.0
	 */
	public static byte[] getBytes(long value) {
		return ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN).putLong(value).array();
	}
	
	/**
	 * Returns the specified Unicode character value as an array of bytes.
	 * @param 		value		A character to convert.
	 * @return		An array of bytes with length 2.
	 * @since 1.0.0.0
	 */
	public static byte[] getBytes(char value) {
		return ByteBuffer.allocate(2).order(ByteOrder.LITTLE_ENDIAN).putChar(value).array();
	}
	
	/**
	 * Returns the specified Unicode character value as an array of bytes.
	 * @param 		value		A boolean to convert.
	 * @return		An array of bytes with length 1.
	 * @since		1.0.0.0
	 */
	public static byte[] getBytes(boolean value) {
		
		if (value) {
			return new byte[] { 1 };
		}
		return new byte[] { 0 };
	}
	
	/**
	 * Returns a 32-bit signed integer converted from four bytes at a specified
     * position in a byte array.
	 * @param 		value		An array of bytes.
	 * @param 		startIndex	The starting position within value.		
	 * @return		A 32-bit signed integer formed by four bytes beginning at startIndex.
	 * @since 		1.0.0.0
	 */
	public static int toInt32(byte[] value, int startIndex) {
		return ByteBuffer.wrap(value, startIndex, 4).order(ByteOrder.LITTLE_ENDIAN).getInt();
	}
	
	/**
	 * Returns a 32-bit signed integer converted from four bytes.
	 * @param 		value		An array of bytes.	
	 * @return		A 32-bit signed integer formed by four bytes.
	 * @since 		1.0.0.0
	 */
	public static int toInt32(byte[] value) {
		return toInt32(value, 0);
	}
	
	/**
	 * Returns a 16-bit signed integer converted from two bytes at a specified
     * position in a byte array.
	 * @param 		value		An array of bytes.
	 * @param 		startIndex	The starting position within value.		
	 * @return		A 16-bit signed integer formed by two bytes beginning at startIndex.
	 * @since 		1.0.0.0
	 */
	public static short toInt16(byte[] value, int startIndex) {
		return ByteBuffer.wrap(value, startIndex, 2).order(ByteOrder.LITTLE_ENDIAN).getShort();
	}
	
	/**
	 * Returns a 16-bit signed integer converted from two bytes.
	 * @param 		value		An array of bytes.	
	 * @return		A 16-bit signed integer formed by two bytes.
	 * @since 		1.0.0.0
	 */
	public static short toInt16(byte[] value) {
		return toInt16(value, 0);
	}
	
	/**
	 * Returns a 16-bit unsigned integer converted from two bytes at a specified
     * position in a byte array.
	 * @param 		value		An array of bytes.
	 * @param 		startIndex	The starting position within value.		
	 * @return		A 16-bit unsigned integer formed by two bytes beginning at startIndex.
	 * @since 		1.0.0.0
	 */
	public static int toUInt16(byte[] value, int startIndex) {
		return ByteBuffer.wrap(value, startIndex, 2).order(ByteOrder.LITTLE_ENDIAN).getChar();
	}
	
	/**
	 * Returns a 16-bit unsigned integer converted from two bytes.
	 * @param 		value		An array of bytes.	
	 * @return		A 16-bit unsigned integer formed by two bytes.
	 * @since 		1.0.0.0
	 */
	public static int toUInt16(byte[] value) {
		return toUInt16(value, 0);
	}
	
	/**
	 * Returns a 64-bit signed integer converted from eight bytes at a specified
     * position in a byte array.
	 * @param 		value		An array of bytes.
	 * @param 		startIndex	The starting position within value.		
	 * @return		A 64-bit signed integer formed by eight bytes beginning at startIndex.
	 * @since 		1.0.0.0
	 */
	public static long toInt64(byte[] value, int startIndex) {
		return ByteBuffer.wrap(value, startIndex, 8).order(ByteOrder.LITTLE_ENDIAN).getLong();
	}
	
	/**
	 * Returns a 64-bit signed integer converted from eight bytes.
	 * @param 		value		An array of bytes.	
	 * @return		A 64-bit signed integer formed by eight bytes.
	 * @since 		1.0.0.0
	 */
	public static long toInt64(byte[] value) {
		return toInt16(value, 0);
	}
	
	/**
	 * Returns a boolean converted from one byte.
	 * @param 		value		An array of bytes.	
	 * @return		A boolean formed by one byte.
	 * @since 		1.0.0.0
	 */
	public static boolean toBoolean(byte[] value) {
		return toBoolean(value, 0);
	}
	
	/**
	 * Returns a boolean converted from one byte.
	 * @param 		value		An array of bytes.	
	 * @param 		startIndex	The starting position within value.
	 * @return		A boolean formed by one byte.
	 * @since 		1.0.0.0
	 */
	public static boolean toBoolean(byte[] value, int startIndex) {

		if (value[startIndex] == 0) {
			return false;
		}
		return true;
	}
	
	/**
	 * Returns a sub array from the given byte array
	 * @param 		value		An array of bytes
	 * @param 		startIndex	The starting position within value.
	 * @param 		count		Number of bytes in the sub array
	 * @return		A sub array from the given byte array
	 * @since		1.0.0.0
	 */
	public static byte[] take(byte[] value, int startIndex, int count) {
		return Arrays.copyOfRange(value, startIndex, (startIndex + count));
	}
}

