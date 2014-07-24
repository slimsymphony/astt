using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Text;

namespace Nokia.Iowarrior
{
    /// <summary>
    /// This class handles all bit pattern tasks required by Iowarrior device.
    /// It is limited to 64 bit currently.
    /// </summary>
    public class IowBits
    {
        Boolean[] bits;
        Boolean invalid = true;

        /// <summary>
        /// Constructs an empty, i.e. undefined bit pattern.
        /// </summary>
        public IowBits()
        {
            SetValue(0);
            invalid = true;
        }

        /// <summary>
        /// Constructs a bit pattern from the Int32 input value.
        /// </summary>
        /// <param name="value">Int32 representation of the bit pattern.</param>
        public IowBits(Int32 value)
        {
            SetValue((Int64)value);
        }

        /// <summary>
        /// Constructs a bit pattern from the Int64 input value.
        /// </summary>
        /// <param name="value">Int32 representation of the bit pattern.</param>
        public IowBits(Int64 value)
        {
            SetValue(value);
        }

        /// <summary>
        /// Calculates and initializes internal bitvector from the given value.
        /// </summary>
        /// <param name="value">Int64 value.</param>
        private void SetValue(Int64 value)
        {
            bits = new Boolean[64];

            for (int i = 0; i < bits.Length; i++)
            {
                bits[i] = ((value & 0x01) == 1);
                value >>= 1;
            }

            invalid = false;
        }

        /// <summary>
        /// Get Int64 value from internal bitvector.
        /// </summary>
        /// <returns></returns>
        private Int64 GetValue()
        {
            Int64 value = 0;

            for (int i = bits.Length-1; i >= 0; i--)
            {
                value *= 2;
                value = value + (bits[i] ? 1 : 0);
            }

            return value;
        }

        /// <summary>
        /// Get/set the bit pattern as Int64.
        /// </summary>
        public Int64 Value
        {
            get { return GetValue(); }
            set { SetValue(value); invalid = false; }
        }

        /// <summary>
        /// Get the number of bits contained in this IowBit object.
        /// </summary>
        public Int32 Length
        {
            get { return bits.Length; }
        }

        /// <summary>
        /// Get/set a certain bit of the bit pattern. Bit position 0 is P0.0, bit position 31 is P3.7.
        /// </summary>
        /// <param name="index">Bit position [0..31].</param>
        /// <returns>Bit pattern (after the set operation).</returns>
        public Boolean this[Int32 index] {
            get { return bits[index]; }
            set { bits[index] = value; invalid = false;  }
        }

        /// <summary>
        /// Returns a string representation of the bit pattern, starting with highest bit number down to bit #0.
        /// </summary>
        /// <returns>String representation of the bit pattern.</returns>
        public override String ToString()
        {
            if (invalid)
            {
                return this.GetType().Name + "{not set}";
            }
            else
            {
                StringBuilder b = new StringBuilder(bits.Length+2);
                b.Append('{');
                for (int i = bits.Length-1; i >= 0; i--)
                {
                    b.Append(bits[i] ? "1" : "0");
                    if (i % 8 == 0 && i > 0)
                    {
                        b.Append(',');
                    }
                }
                b.Append('}');
                return this.GetType().Name + b.ToString();
            }
        }
    }
}
