using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestAutomation.Client
{
    /// <summary>
    /// Type of the RPC message
    /// </summary>
    public enum MessageType
    {
        /// <summary>
        /// For RCP invoke
        /// </summary>
        MethodInvoke = 0x00,

        /// <summary>
        /// For RPC response
        /// </summary>
        MethodResponse = 0x01,

        /// <summary>
        /// For RPC event
        /// </summary>
        Event = 0x02
    }

    /// <summary>
    /// Class for defining a RPC message
    /// </summary>
    public class RPCMessage
    {
        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="messageType">Type of the RPC message</param>
        /// <param name="transactionId">Transaction ID for the RPC message</param>
        /// <param name="totalDataLength">Total length of the json data in the RPC message</param>
        /// <param name="@continue">Value indicating whether this is the last chunk of the RPC message</param>
        /// <param name="index">Index number of the chunk of the RPC message</param>
        /// <param name="json">Json data in the RPC message</param>
        public RPCMessage(MessageType messageType, ushort transactionId, uint totalDataLength, bool @continue,
            ushort index, string json) : this(messageType, transactionId, totalDataLength, @continue, index, null, json) { }

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="messageType">Type of the RPC message</param>
        /// <param name="transactionId">Transaction ID for the RPC message</param>
        /// <param name="totalDataLength">Total length of the json data in the RPC message</param>
        /// <param name="@continue">Value indicating whether this is the last chunk of the RPC message</param>
        /// <param name="index">Index number of the chunk of the RPC message</param>
        /// <param name="optionalBytes">Optional bytes in the RPC message header</param>
        /// <param name="json">Json data in the RPC message</param>
        public RPCMessage(MessageType messageType, ushort transactionId, uint totalDataLength, bool @continue,
            ushort index, byte[] optionalBytes, string json)
        {
            if (optionalBytes == null)
            {
                OptionalBytes = new byte[4];
            }
            else if (optionalBytes.Length > 4)
            {
                OptionalBytes = optionalBytes.Take(4).ToArray();
            }
            else if (optionalBytes.Length < 4)
            {
                var tmp = new byte[4];
                Array.Copy(optionalBytes, 0, tmp, 0, optionalBytes.Length);
                OptionalBytes = tmp;
            }
            else
            {
                OptionalBytes = optionalBytes;
            }

            MessageType = messageType;
            TransactionId = transactionId;
            TotalDataLength = totalDataLength;
            Continue = @continue;
            Index = index;
            TotalChunkLength = (uint)json.Length;
            Json = json;
        }

        /// <summary>
        /// Gets the encoding to use
        /// </summary>
        private static Encoding MessageEncoding
        {
            get
            {
                return Encoding.UTF8;
            }
        }

        /// <summary>
        /// Gets the type of the RPC message
        /// </summary>
        public MessageType MessageType { get; private set; }

        /// <summary>
        /// Gets the transaction ID for the RPC message
        /// </summary>
        public ushort TransactionId { get; private set; }

        /// <summary>
        /// Gets the total length of the json data in the RPC message
        /// </summary>
        public uint TotalDataLength { get; private set; }

        /// <summary>
        /// Gets or sets the value indicating whether this is the last chunk of the RPC message
        /// </summary>
        public bool Continue { get; set; }

        /// <summary>
        /// Gets the index number of the chunk of the RPC message
        /// </summary>
        public ushort Index { get; private set; }

        /// <summary>
        /// Gets the length of the json chunk data in the RPC message
        /// </summary>
        public uint TotalChunkLength { get; private set; }

        /// <summary>
        /// Gets the optional bytes in the RPC message header
        /// </summary>
        public byte[] OptionalBytes { get; private set; }

        /// <summary>
        /// Gets the Json data in the RPC message
        /// </summary>
        public string Json { get; private set; }

        /// <summary>
        /// Gets the length of the complete message (header + chunk data)
        /// </summary>
        public uint MessageLength { get { return Constants.RPC_MESSAGE_HEADER_LENGTH + TotalChunkLength; } }

        /// <summary>
        /// Creates a RPCMessage instance from header and data bytes
        /// </summary>
        /// <param name="header">RCP message header</param>
        /// <param name="data">RPC message data (excluding the header, i.e. Json data)</param>
        /// <param name="count">Number of valid bytes in the data array</param>
        /// <returns>RPCMessage instance</returns>
        /// <exception cref="NullReferenceException">If data array is null</exception>
        public static RPCMessage FromBytes(RPCMessageHeader header, byte[] data, int count)
        {
            return FromBytes(header, data.Take(count).ToArray());
        }

        /// <summary>
        /// Creates a RPCMessage instance from header and data bytes
        /// </summary>
        /// <param name="header">RCP message header</param>
        /// <param name="data">RPC message data (excluding the header, i.e. Json data)</param>
        /// <returns>RPCMessage instance</returns>
        /// <exception cref="NullReferenceException">If data array is null</exception>
        public static RPCMessage FromBytes(RPCMessageHeader header, byte[] data)
        {
            if (data == null)
            {
                throw new NullReferenceException("data");
            }

            return new RPCMessage(header.MessageType, header.TransactionId, header.TotalDataLength, header.Continue,
                header.Index, header.OptionalBytes, RPCMessage.MessageEncoding.GetString(data));
        }

        /// <summary>
        /// Creates a RPCMessage instance from bytes
        /// </summary>
        /// <param name="data">RPC message data (including header)</param>
        /// <param name="count">Number of valid bytes in the data array</param>
        /// <returns>RPCMessage instance</returns>
        /// <exception cref="NullReferenceException">If data array is null</exception>
        public static RPCMessage FromBytes(byte[] data, int count)
        {
            return FromBytes(data.Take(count).ToArray());
        }

        /// <summary>
        /// Creates a RPCMessage instance from bytes
        /// </summary>
        /// <param name="data">RPC message data (including header)</param>
        /// <returns>RPCMessage instance</returns>
        /// <exception cref="NullReferenceException">If data array is null</exception>
        public static RPCMessage FromBytes(byte[] data)
        {
            if (data == null)
            {
                throw new NullReferenceException("data");
            }
            if (data.Length < Constants.RPC_MESSAGE_HEADER_LENGTH)
            {
                throw new ArgumentException("Message header is not complete");
            }

            var type = (MessageType)data[0];
            var transactionId = BitConverter.ToUInt16(data, 1);
            var totalLength = BitConverter.ToUInt32(data, 3);
            var @continue = BitConverter.ToBoolean(data, 7);
            var index = BitConverter.ToUInt16(data, 8);
            var chunkDataLength = BitConverter.ToUInt32(data, 10);
            var optional = data.Skip(14).Take(4).ToArray();
            var json = RPCMessage.MessageEncoding.GetString(data, Constants.RPC_MESSAGE_HEADER_LENGTH, (int)chunkDataLength);

            return new RPCMessage(type, transactionId, totalLength, @continue, index, optional, json);
        }

        /// <summary>
        /// Converts the RPCMessage instance into bytes for sending
        /// </summary>
        /// <returns>RPCMessage object as byte array</returns>
        public byte[] GetBytes()
        {
            var bytes = new List<byte>();
            bytes.Add((byte)MessageType);
            bytes.AddRange(BitConverter.GetBytes(TransactionId));
            bytes.AddRange(BitConverter.GetBytes(TotalDataLength));
            bytes.AddRange(BitConverter.GetBytes(Continue));
            bytes.AddRange(BitConverter.GetBytes(Index));
            bytes.AddRange(BitConverter.GetBytes(TotalChunkLength));
            bytes.AddRange(OptionalBytes);
            bytes.AddRange(RPCMessage.MessageEncoding.GetBytes(Json));

            return bytes.ToArray();
        }
    }

    /// <summary>
    /// Class for defining a RPC message header
    /// </summary>
    public class RPCMessageHeader
    {
        /// <summary>
        /// Private class constructor
        /// </summary>
        private RPCMessageHeader()
        { }

        /// <summary>
        /// Tries to parse the header from bytes
        /// </summary>
        /// <param name="data">Header data in byte array</param>
        /// <param name="header">Parsed header instance</param>
        /// <returns>Bool if header was successfully validated and parsed</returns>
        public static bool TryGetFromBytes(byte[] data, out RPCMessageHeader header)
        {
            header = null;

            if (data == null)
            {
                return false;
            }
            if (data.Length < Constants.RPC_MESSAGE_HEADER_LENGTH)
            {
                return false;
            }
            if (data[0] > Enum.GetValues(typeof(MessageType)).Length)
            {
                return false;
            }

            header = new RPCMessageHeader();
            header.MessageType = (MessageType)data[0];
            header.TransactionId = BitConverter.ToUInt16(data, 1);
            header.TotalDataLength = BitConverter.ToUInt32(data, 3);
            header.Continue = BitConverter.ToBoolean(data, 7);
            header.Index = BitConverter.ToUInt16(data, 8);
            header.TotalChunkLength = BitConverter.ToUInt32(data, 10);
            header.OptionalBytes = data.Skip(14).Take(4).ToArray();

            return true;
        }

        /// <summary>
        /// Gets the type of the RPC message
        /// </summary>
        public MessageType MessageType { get; private set; }

        /// <summary>
        /// Gets the transaction ID for the RPC message
        /// </summary>
        public ushort TransactionId { get; private set; }

        /// <summary>
        /// Gets the total length of the json data in the RPC message. This is the total size of the message: even if multipart message 
        /// </summary>
        public uint TotalDataLength { get; private set; }

        /// <summary>
        /// Gets or sets the value indicating whether this is the last chunk of the RPC message
        /// </summary>
        public bool Continue { get; set; }

        /// <summary>
        /// Gets the index number of the chunk of the RPC message
        /// </summary>
        public ushort Index { get; private set; }

        /// <summary>
        /// Gets the length of the json chunk data in the RPC message
        /// </summary>
        public uint TotalChunkLength { get; private set; }

        /// <summary>
        /// Gets the optional bytes in the RPC message header
        /// </summary>
        public byte[] OptionalBytes { get; private set; }
    }

    /// <summary>
    /// Class for serializing the information for remote invoke
    /// </summary>
    public class RPCInvoke
    {
        /// <summary>
        /// Name of the method to be invoked
        /// </summary>
        public string MethodName { get; set; }

        /// <summary>
        /// Name of the class from which to invoke the method
        /// </summary>
        public string ClassName { get; set; }

        /// <summary>
        /// Array of arguments to be passed for the method
        /// </summary>
        public object[] Args { get; set; }
    }

    /// <summary>
    /// Class for deserializing the result from remote invoke
    /// </summary>
    public class RPCResponse
    {
        /// <summary>
        /// Name of the method from which the result is originated
        /// </summary>
        public string MethodName { get; set; }

        /// <summary>
        /// Name of the class defining the method from which the result is originated
        /// </summary>
        public string ClassName { get; set; }

        /// <summary>
        /// Result from the invoke
        /// </summary>
        public object Result { get; set; }

        /// <summary>
        /// Error message from the invoke, if any
        /// </summary>
        public string Error { get; set; }
    }

    /// <summary>
    /// Class for deserializing an event from remote device
    /// </summary>
    public class RPCEvent
    {
        /// <summary>
        /// Type of the event (Friendly/short name, without package or namespace)
        /// </summary>
        public string EventType { get; set; }

        /// <summary>
        /// Content of the event in json format
        /// </summary>
        public string EventArgs { get; set; }

        /// <summary>
        /// Gets the type of the event. Type needs to be either a type defined in the executing assembly, in an assembly in the current
        /// applicatio domain, or in a system assembly
        /// </summary>
        /// <returns></returns>
        public Type GetEventType()
        {
            return TypeFromFriendlyName(EventType);
        }

        /// <summary>
        /// Tries to find the type based on it's name. Searches from the executing assembly, from the assemblies in the current
        /// applicatio domain, or from the system assemblies
        /// </summary>
        /// <param name="friendlyName">Friendly name of the type</param>
        /// <param name="ignoreCase">Whether to ignore the case when searching the type by name</param>
        /// <returns>A ype matching to the given type name; null if not found</returns>
        private Type TypeFromFriendlyName(string friendlyName, bool ignoreCase = false)
        {
            int dot = friendlyName.LastIndexOf('.');

            if (dot >= 0 && dot < (friendlyName.Length - 1))
            {
                friendlyName = friendlyName.Substring(dot + 1);
            }

            var type = GetType().Assembly.GetTypes().ToList().Find(n => string.Compare(friendlyName, n.Name, ignoreCase) == 0);
            if (type != null)
            {
                return type;
            }
            type = typeof(bool).Assembly.GetTypes().ToList().Find(n => string.Compare(friendlyName, n.Name, ignoreCase) == 0);
            if (type != null)
            {
                return type;
            }
            foreach (var a in AppDomain.CurrentDomain.GetAssemblies())
            {
                type = a.GetTypes().ToList().Find(n => string.Compare(friendlyName, n.Name, ignoreCase) == 0);
                if (type != null)
                {
                    return type;
                }
            }
            return null;
        }
    }
}
