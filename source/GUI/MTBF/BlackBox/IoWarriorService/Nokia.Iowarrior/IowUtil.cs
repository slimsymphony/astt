using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Iowarrior
{
    static class IowUtil
    {     
        /// <summary>
        /// Converts a DateTime Object to following bit pattern
        /// [31..26] [25..22] [21..17] [16..12] [11..6] [5..0] Bits
        ///  Year     Month    Day      Hour     Minutes Seconds 
        /// </summary>
        /// <param name="date"></param>
        /// <returns></returns>
        public static Byte[] DateTimeToDateBytes(DateTime date)
        {
            // Convert DateTime to the bit format
            Int32 datebits = 0;
            datebits = date.Second;
            datebits += date.Minute << 6;
            datebits += date.Hour << 12;
            datebits += date.Day << 17;
            datebits += date.Month << 22;
            Int32 year = date.Year - 2000;
            datebits += year << 26;

            return BitConverter.GetBytes(datebits);
        }

        /// <summary>
        /// Converts the following bit pattern to a DateTimeObject
        /// [31..26] [25..22] [21..17] [16..12] [11..6] [5..0] Bits
        ///  Year     Month    Day      Hour     Minutes Seconds 
        /// </summary>
        /// <param name="dateBytes"></param>
        /// <returns></returns>
        public static DateTime DateBytesToDateTime(Byte[] dateBytes)
        {
            Int32 year, month, day, hour, minute, second;
            Int32 datebits = BitConverter.ToInt32(dateBytes, 0);

            Int32 mask = 63;
            second = datebits & mask;

            mask = 63 << 6;
            minute = datebits & mask;
            minute = minute >> 6;

            mask = 31 << 12;
            hour = datebits & mask;
            hour = hour >> 12;

            mask = 31 << 17;
            day = datebits & mask;
            day = day >> 17;

            mask = 15 << 22;
            month = datebits & mask;
            month = month >> 22;

            mask = 63 << 26;
            year = datebits & mask;
            year = year >> 26;
            year += 2000;

            return new DateTime(year, month, day, hour, minute, second);
        }

        public static Byte[] ConvertStringToByteArray(String data)
        {           
            Int32 length = data.Length + 1;
            Byte[] content = new Byte[length];
            content[0] = (Byte)length;

            for (Int32 i = 1; i < content.Length; i++)
                content[i] = (Byte)data[i - 1];

            return content;
        }

        public static String ConvertByteArrayToString(Byte[] data)
        {   
            String text = "";
            for (Int32 i = 1; i < data.Length; i++)
                text += (Char)data[i];

            return text;
        }
                
        public static Boolean GetBit(Byte register, Int32 bit)
        {
            if((bit > 7) || (bit < 0))
                throw new Exception("Bit value out of range (valid values: 0..7)");

            Int32 mask = 1 << bit;
            Int32 value = register & mask;
            value = value >> bit;

            if(value == 1)
                return true;
            else
                return false;
        }
    }
}
