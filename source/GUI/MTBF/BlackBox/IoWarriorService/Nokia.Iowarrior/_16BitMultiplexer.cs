using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Iowarrior
{
    class _16BitMultiplexer
    {        
        private Int32 A0;
        private Int32 A1;
        private Int32 A2;
        private Int32 A3;
        private Dictionary<Int32, Boolean> codeBits;
        
        public _16BitMultiplexer(Int32 A0, Int32 A1, Int32 A2, Int32 A3)
        {
            // mapping A0..A3 zu Iow Port
            this.A0 = A0;
            this.A1 = A1;
            this.A2 = A2;
            this.A3 = A3;
                     
            codeBits = new Dictionary<Int32, Boolean>();

            codeBits.Add(A0, false);
            codeBits.Add(A1, false);
            codeBits.Add(A2, false);
            codeBits.Add(A3, false);            
        }

        public void SetCodeBit(Byte bitValue)
        {  
            codeBits[A0] = IowUtil.GetBit(bitValue, 0);
            codeBits[A1] = IowUtil.GetBit(bitValue, 1);
            codeBits[A2] = IowUtil.GetBit(bitValue, 2);
            codeBits[A3] = IowUtil.GetBit(bitValue, 3);           
        }

        public Dictionary<Int32, Boolean> CodeBits
        {
            get { return codeBits; }
        }
    }
}
