// Disable "Missing XML comment for public type or member" warning.
// This file contains only code being accessed through an abstract interface class.
// The public methods are documented in this abstract interface class.
#pragma warning disable 1591

using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Iowarrior
{
    [CLSCompliant(false)]
    public class _8Bit
    {
        private Boolean[] bits = new Boolean[8];

        public _8Bit()
        {
            Reset();
        }

        public _8Bit(Byte register)
        {
            SetBits(register);
        }

        public Boolean P00
        {
            set { bits[0] = value; }
            get { return bits[0]; }
        }

        public Boolean P01
        {
            set { bits[1] = value; }
            get { return bits[1]; }
        }

        public Boolean P02
        {
            set { bits[2] = value; }
            get { return bits[2]; }
        }

        public Boolean P03
        {
            set { bits[3] = value; }
            get { return bits[3]; }
        }

        public Boolean P04
        {
            set { bits[4] = value; }
            get { return bits[4]; }
        }

        public Boolean P05
        {
            set { bits[5] = value; }
            get { return bits[5]; }
        }

        public Boolean P06
        {
            set { bits[6] = value; }
            get { return bits[6]; }
        }

        public Boolean P07
        {
            set { bits[7] = value; }
            get { return bits[7]; }
        }

        public Byte GetBits()
        {           
            Int32 tmp = 0;
            Int32 commandBits = 0;

            for (Int32 i = 0; i < 8; i++)
            {
                if(bits[i])
                {
                    tmp = 1;
                    tmp = tmp << (i);
                    commandBits += tmp;
                }
            }
            
            return Byte.Parse(commandBits.ToString());                
        }

        public void SetBits(Byte byteValue)
        {            
            Int32 mask, value;
            for (Int32 i = 0; i < 8; i++)
            {
                mask = 1 << i;
                value = byteValue & mask;
                value = value >> i;

                if (value == 1)
                    bits[i] = true;
                else
                    bits[i] = false;
            }
        }

        public void SetBit(Int32 bit, Boolean value)
        {
           bits[bit] = value;            
        }

        public void Reset()
        {
            for (Int32 i = 0; i < 8; i++)
                bits[i] = false;
        }

        public override String ToString()
        {
            String value = "";

            for (Int32 i = 0; i < 8; i++)
            {
                if (bits[i])
                    value += "1";
                else
                    value += "0";
            }

            return value;
        }
    }
}
