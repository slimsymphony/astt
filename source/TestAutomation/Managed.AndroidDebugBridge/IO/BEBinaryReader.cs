using System;
using System.IO;
using System.Net;

namespace Managed.Adb.IO
{
    /// <summary> 
    /// Big-Endian Binary Reader 
    /// </summary> 
    public class BEBinaryReader : BinaryReader
    {
        public BEBinaryReader(MemoryStream s)
            : base(s)
        { }

        /// <summary> 
        /// Reads a 2-byte signed integer from the current stream and advances the  
        /// current position of the stream by two bytes. 
        /// </summary> 
        /// <returns></returns> 
        public override short ReadInt16()
        {
            return IPAddress.NetworkToHostOrder(base.ReadInt16());
        }

        /// <summary> 
        /// Reads a 4-byte signed integer from the current stream and advances the  
        /// current position of the stream by four bytes. 
        /// </summary> 
        /// <returns></returns> 
        public override int ReadInt32()
        {
            return IPAddress.NetworkToHostOrder(base.ReadInt32());
        }

        /// <summary> 
        /// Reads an 8-byte signed integer from the current stream and advances  
        /// the current position of the stream by four bytes. 
        /// </summary> 
        /// <returns></returns> 
        public override long ReadInt64()
        {
            return IPAddress.NetworkToHostOrder(base.ReadInt64());
        }

        /// <summary> 
        /// Reads a 4-byte floating point value from the current stream and  
        /// advances the current position of the stream by four bytes. 
        /// </summary> 
        /// <returns></returns> 
        public override float ReadSingle()
        {
            byte[] temp = BitConverter.GetBytes(base.ReadSingle());
            Array.Reverse(temp);
            float returnVal = BitConverter.ToSingle(temp, 0);
            return returnVal;
        }

        /// <summary> 
        /// Reads an 8-byte floating point value from the current stream and  
        /// advances the current position of the stream by eight bytes. 
        /// </summary> 
        /// <returns></returns> 
        public override double ReadDouble()
        {
            byte[] temp = BitConverter.GetBytes(base.ReadDouble());
            Array.Reverse(temp);
            double returnVal = BitConverter.ToDouble(temp, 0);
            return returnVal;
        }
    }
}
