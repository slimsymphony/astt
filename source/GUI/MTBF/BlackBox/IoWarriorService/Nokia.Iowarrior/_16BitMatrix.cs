using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Iowarrior
{
    class _16BitMatrix
    {
        private _16BitMultiplexer rows;
        private _16BitMultiplexer columns;
        private Int32 matixEnableBit;

        // mapping iow ports -> A0..A3
        public _16BitMatrix(Int32 R0, Int32 R1, Int32 R2, Int32 R3, Int32 C0, Int32 C1, Int32 C2, Int32 C3, Int32 matixEnableBit)
        {
            rows = new _16BitMultiplexer(R0, R1, R2, R3);
            columns = new _16BitMultiplexer(C0, C1, C2, C3);
            this.matixEnableBit = matixEnableBit;
        }

        public void SetCodeBit(Byte row, Byte column)
        {
            rows.SetCodeBit(row);
            columns.SetCodeBit(column);            
        }

        public Dictionary<Int32, Boolean> CodeBits        
        {
            get
            {
                var result = new Dictionary<Int32, Boolean>();

                foreach (var dict in rows.CodeBits)
                    result.Add(dict.Key, dict.Value);
                
                foreach (var dict in columns.CodeBits)
                    result.Add(dict.Key, dict.Value);
                
                return result;
            }
        }
             
        public Int32 MatixEnableBit
        {
            get { return matixEnableBit; }
        }
    }
}