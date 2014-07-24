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
    public class _16Bit
    {
        private _8Bit register1 = new _8Bit(); // bits 0..7
        private _8Bit register2 = new _8Bit(); // bits 8..15

        public _16Bit() 
        {
            Reset();
        }

        public _16Bit(Byte register1, Byte register2) 
        {
            this.register1.SetBits(register1);
            this.register2.SetBits(register2);
        }
              
        public Boolean P00
        {
            set { register1.P00 = value; }
            get { return register1.P00; }
        }

        public Boolean P01
        {
            set {register1.P01 = value; }
            get { return register1.P01; }
        }

        public Boolean P02
        {
            set { register1.P02 = value; }
            get { return register1.P02; }
        }

        public Boolean P03
        {
            set { register1.P03 = value; }
            get { return register1.P03; }
        }

        public Boolean P04
        {
            set { register1.P04 = value; }
            get { return register1.P04; }
        }

        public Boolean P05
        {
            set { register1.P05 = value; }
            get { return register1.P05; }
        }

        public Boolean P06
        {
            set { register1.P06 = value; }
            get { return register1.P06; }
        }

        public Boolean P07
        {
            set { register1.P07 = value; }
            get { return register1.P07; }
        }

        public Boolean P10
        {
            set { register2.P00 = value; }
            get { return register2.P00; }
        }

        public Boolean P11
        {
            set {register2.P01 = value; }
            get { return register2.P01; }
        }

        public Boolean P12
        {
            set { register2.P02 = value; }
            get { return register2.P02; }
        }

        public Boolean P13
        {
            set { register2.P03 = value; }
            get { return register2.P03; }
        }

        public Boolean P14
        {
            set { register2.P04 = value; }
            get { return register2.P04; }
        }

        public Boolean P15
        {
            set { register2.P05 = value; }
            get { return register2.P05; }
        }

        public Boolean P16
        {
            set { register2.P06 = value; }
            get { return register2.P06; }
        }

        public Boolean P17
        {
            set { register2.P07 = value; }
            get { return register2.P07; }
        }

        public Byte[] GetBits()
        {
            Byte[] bits = new Byte[2];
            bits[0] = register1.GetBits();
            bits[1] = register2.GetBits();
            return bits;
        }

        public void SetBits(Byte[] bytes)
        {
            if (bytes.Length > 2)
                throw new Exception("Set bits failes incorrect number of bytes. Expected: 2, available: " + bytes.Length);

            register1.SetBits(bytes[0]);
            register2.SetBits(bytes[1]);
        }

        public void SetBits(Byte register1, Byte register2)
        {
            this.register1.SetBits(register1);
            this.register2.SetBits(register2);
        }

        public void Reset()
        {
            this.register1.Reset();
            this.register2.Reset();
        }

        public override String ToString()
        {
            return register1.ToString() + register2.ToString();
        }
    }
}
