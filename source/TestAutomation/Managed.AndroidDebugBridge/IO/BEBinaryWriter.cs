namespace Managed.Adb.IO
{
    using System;
    using System.IO;
    using System.Net;

    /// <summary> 
    /// Big-Endian Binary Writer 
    /// </summary> 
    public class BEBinaryWriter : BinaryWriter
    {
        public BEBinaryWriter(MemoryStream s)
            : base(s)
        { }

        /// <summary> 
        /// Writes a two-byte signed integer to the current stream and advances the stream  
        /// position by two bytes. 
        /// </summary> 
        /// <param name="value"></param> 
        public override void Write(short value)
        {
            base.Write(IPAddress.HostToNetworkOrder(value));
        }

        /// <summary> 
        /// Writes a four-byte signed integer to the current stream and advances the stream  
        /// position by four bytes. 
        /// </summary> 
        /// <param name="value"></param> 
        public override void Write(int value)
        {
            base.Write(IPAddress.HostToNetworkOrder(value));
        }

        /// <summary> 
        /// Writes an eight-byte signed integer to the current stream and advances the stream  
        /// position by eight bytes. 
        /// </summary> 
        /// <param name="value"></param> 
        public override void Write(long value)
        {
            base.Write(IPAddress.HostToNetworkOrder(value));
        }

        /// <summary> 
        /// Writes a four-byte floating-point value to the current stream and advances the  
        /// stream position by four bytes. 
        /// </summary> 
        /// <param name="value"></param> 
        public override void Write(float value)
        {
            byte[] temp = BitConverter.GetBytes(value);
            Array.Reverse(temp);
            base.Write(BitConverter.ToSingle(temp, 0));
        }

        /// <summary> 
        /// Writes an eight-byte floating-point value to the current stream and advances  
        /// the stream position by eight bytes. 
        /// </summary> 
        /// <param name="value"></param> 
        public override void Write(double value)
        {
            byte[] temp = BitConverter.GetBytes(value);
            Array.Reverse(temp);
            base.Write(BitConverter.ToDouble(temp, 0));
        }
    }
}
