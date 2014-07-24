package Server;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Class which present the packet format with which the client and server communicates
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public class RPCMessage {
	
	private static Encoding m_encoding = Encoding.getUtf8();
	
	private static final int HEADER_LENGTH = 18;
	
	private MessageType m_messageType = null;
	private short m_transactionId = 0;
	private int m_totalDataLength = 0;
	private int m_chunkLength = 0;
	private boolean m_continue = false;
	private short m_index = 0;
	private byte[] m_optionalBytes = new byte[4];
	private byte[] m_json = null;
	
	/***
	 * Info to provide information about who is the client the message came from, and/or to which client to send the message:
	 * i.e. sender/receiver
	 */
	public ClientInfo m_clientInfo = null;
	
	/***
	 * Class constructor
	 * 
	 * @param 		messageType			Type of the message 
	 * @param 		transactionId		Transaction id of the message
	 * @param 		_continue			Value indicating whether this message is to be continued (multi-chunk messages)
	 * @param 		index				Index of the message chunk (multi-chunk messages)
	 * @param 		json				Json string
	 * @since		1.0.0.0
	 */
	public RPCMessage(MessageType messageType, short transactionId, boolean _continue, 
			short index, String json) {
		this(messageType, transactionId, _continue, index, (json != null ? m_encoding.getBytes(json) : null));
	}
	
	/***
	 * Class constructor
	 * 
	 * @param 		messageType			Type of the message 
	 * @param 		transactionId		Transaction id of the message
	 * @param 		_continue			Value indicating whether this message is to be continued (multi-chunk messages)
	 * @param 		index				Index of the message chunk (multi-chunk messages)
	 * @param 		json				Json data
	 * @since		1.0.0.0
	 */
	public RPCMessage(MessageType messageType, short transactionId, boolean _continue, 
			short index, byte[] json) {
		this(messageType, transactionId, (json != null ? json.length : 0), _continue, index, json);
	}
	
	/***
	 * Class constructor
	 * 
	 * @param 		messageType			Type of the message 
	 * @param 		transactionId		Transaction id of the message
	 * @param 		totalDataLength		Total length of the Json data
	 * @param 		_continue			Value indicating whether this message is to be continued (multi-chunk messages)
	 * @param 		index				Index of the message chunk (multi-chunk messages)
	 * @param 		json				Json data
	 * @since		1.0.0.0
	 */
	public RPCMessage(MessageType messageType, short transactionId, int totalDataLength, boolean _continue, 
			short index, byte[] json) {
		this(messageType, transactionId, totalDataLength, _continue, index, null, json);
	}
	
	/***
	 * Class constructor
	 * 
	 * @param 		messageType			Type of the message 
	 * @param 		transactionId		Transaction id of the message
	 * @param 		_continue			Value indicating whether this message is to be continued (multi-chunk messages)
	 * @param 		index				Index of the message chunk (multi-chunk messages)
	 * @param 		json				Json data
	 * @param		optionalBytes		4 bytes in header reserved for custom, future needs
	 * @since		1.0.0.0
	 */
	public RPCMessage(MessageType messageType, short transactionId, boolean _continue, 
			short index, byte[] optionalBytes, byte[] json) {
		this(messageType, transactionId, (json != null ? json.length : 0), _continue, index, optionalBytes, json);
	}
	
	/***
	 * Class constructor
	 * 
	 * @param 		messageType			Type of the message 
	 * @param 		transactionId		Transaction id of the message
	 * @param 		totalDataLength		Total length of the Json data
	 * @param 		_continue			Value indicating whether this message is to be continued (multi-chunk messages)
	 * @param 		index				Index of the message chunk (multi-chunk messages)
	 * @param 		json				Json data
	 * @param		optionalBytes		4 bytes in header reserved for custom, future needs
	 * @since		1.0.0.0
	 */
	public RPCMessage(MessageType messageType, short transactionId, int totalDataLength, boolean _continue, 
			short index, byte[] optionalBytes, byte[] json) {
		
		if (optionalBytes == null) {
			m_optionalBytes = new byte[] { 0x00,0x00,0x00,0x00 };
		}
		else if (optionalBytes.length > 4) {
			m_optionalBytes = BitConverter.take(optionalBytes, 0, 4);
		}
		else if (optionalBytes.length < 4) {
			byte[] tmp = new byte[] { 0x00,0x00,0x00,0x00 };
			System.arraycopy(optionalBytes, 0, tmp, 0, optionalBytes.length);
			m_optionalBytes = tmp;
		}
		else {
			m_optionalBytes = optionalBytes;
		}
		m_messageType = messageType;
		m_transactionId = transactionId;
		m_totalDataLength = totalDataLength;
		m_continue = _continue;
		m_index = index;
		m_json = json;
		m_chunkLength = json != null ? json.length : 0;
	}
	
		
	/**
	 * Gets the type of the message
	 * 
	 * @return		The type of the message			
	 * @since		1.0.0.0		
	 */
	public MessageType getMessageType() {
		return m_messageType;
	}
	
	/**
	 * Gets the transaction id of the message.
	 * Note that with event messages, this value is always zero (0)
	 * 
	 * @return		The transaction id of the message
	 * @since		1.0.0.0	
	 */
	public short getTransactionId() {
		return m_transactionId;
	}
	
	/**
	 * Gets the total length of the data (json) part of the message
	 * NOTE that even in a single chunk of a multi-chunk message, this method
	 * return the total length of the data (json) of a complete message
	 * 
	 * @return		The total length of the data (json) part of the message
	 * @since		1.0.0.0		
	 */
	public int getTotalDataLength() {
		return m_totalDataLength;
	}
	
	/***
	 * Gets the length of the partial message chunk
	 * 
	 * @return		The length of the partial message chunk
	 * @since		1.0.0.0
	 */
	public int getChunkLenght() {
		return m_chunkLength;
	}
	
	/**
	 * Gets a value indicating whether this message is to be continued.
	 * Used mainly for multi-chunk messages
	 * 
	 * @return		A value indicating whether this message is to be continued.
	 * @since		1.0.0.0
	 */
	public boolean getContinue() {
		return m_continue;
	}
	
	/**
	 * Sets a value indicating whether this message is to be continued.
	 * Used mainly for multi-chunk messages
	 * 
	 * @param 		value		A value indicating whether this message is to be continued
	 * @since		1.0.0.0
	 */
	public void setContinue(boolean value) {
		m_continue = value;
	}
	
	/**
	 * Gets the total length of the message (header + data chunk)
	 * 
	 * @return		Total length of the message (header + data chunk)
	 * @since		1.0.0.0
	 */
	public int getMessageLength() {
		return HEADER_LENGTH + m_chunkLength;
	}
	
	/**
	 *  Gets the message index from the header
	 * 
	 * @return		Message index from the header
	 * @since		1.0.0.0
	 */
	public short getMessageIndex() {
		return m_index;
	}
	
	/**
	 * Gets the optional bytes from the header
	 * 
	 * @return		Optional bytes from the header
	 * @since		1.0.0.0		
	 */
	public byte[] getOptinalBytes() {
		return m_optionalBytes;
	}
	
	/**
	 * Gets the Json data
	 * 
	 * @return		Json data	
	 * @since		1.0.0.0		
	 */
	public String getJson() {
		return m_json != null ? m_encoding.getString(m_json) : null;
	}
		
	/***
	 * Splits the existing message in multiple chunks
	 * 
	 * @param 		chunkSize		Maximum size of the chunk
	 * @return		List RPCMessages, with the given chunk size
	 * @since		1.0.0.0
	 */
	public List<RPCMessage> getMessageChunks(int chunkSize) {
				
		List<RPCMessage> chunks = new ArrayList<RPCMessage>();
		
		int dataSize = m_json.length;

		int size = chunkSize - HEADER_LENGTH;
		short index = 0;
		
		for (int start = 0; start < dataSize; start += size) {
			chunks.add(new RPCMessage(m_messageType, m_transactionId, m_totalDataLength, 
					((dataSize - start) > size), index, Arrays.copyOfRange(m_json, start, Math.min(dataSize, start + size))));
			index++;
		}
		
		return chunks;
	}
	
	/**
	 * Creates the RPCMessage from an Byte array
	 * 
	 * @param 		value		An array of bytes containing the data for the RCPMessage
	 * @return		RPCMessage
	 * @throws 		NullPointerException
	 * @throws 		IllegalArgumentException
	 * @since		1.0.0.0
	 */
	public static RPCMessage fromBytes(byte[] value) throws NullPointerException, IllegalArgumentException {
		
		if (value == null) {
			throw new NullPointerException("value");
		}
		
		if (value.length < HEADER_LENGTH) {
			throw new IllegalArgumentException("Message header is not complete");
		}
		
		MessageType type = MessageType.fromByte(value[0]);
		
		short transactionId = BitConverter.toInt16(value, 1);
		
		int totalLength = BitConverter.toInt32(value, 3);
		
		boolean _continue = BitConverter.toBoolean(value, 7);
		
		short index = BitConverter.toInt16(value, 8);
		
		int chunkLength = BitConverter.toInt32(value, 10);
		
		byte[] optional = BitConverter.take(value, 14, 4);
		
		byte[] json = BitConverter.take(value, HEADER_LENGTH, chunkLength);
			
		return new RPCMessage(type, transactionId, totalLength, _continue, index, optional, json);
	}
	
	/**
	 * Converts the whole message into a Byte array
	 * 
	 * @return		Message converted into a Byte array
	 * @since		1.0.0.0		
	 */
	public byte[] getBytes() {
		
		ByteBuffer bytes = ByteBuffer.allocate(HEADER_LENGTH + m_json.length);
		bytes = bytes.put(MessageType.toByte(m_messageType));
		bytes = bytes.put(BitConverter.getBytes(m_transactionId));
		bytes = bytes.put(BitConverter.getBytes(m_totalDataLength));
		bytes = bytes.put(BitConverter.getBytes(m_continue));
		bytes = bytes.put(BitConverter.getBytes(m_index));
		bytes = bytes.put(BitConverter.getBytes(m_chunkLength));
		bytes = bytes.put(m_optionalBytes);
		bytes = bytes.put(m_json);
		return bytes.array();
	}
}
