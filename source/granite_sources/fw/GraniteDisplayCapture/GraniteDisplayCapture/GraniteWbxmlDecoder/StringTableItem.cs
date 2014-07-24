// The WAP Binary XML (WBXML) specification is developed by the 
// Open Mobile Alliance (http://www.openmobilealliance.org/)
// Details about this specification can be found at
// http://www.openmobilealliance.org/tech/affiliates/wap/wap-192-wbxml-20010725-a.pdf

using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Granite.Tracing.Decoding
{
    public class StringTableItem
    {
        private int index;
        private string itemValue;

        public int Index
        {
            get
            {
                return index;
            }
        }

        public string Value
        {
            get
            {
                return itemValue;
            }
        }

        public StringTableItem(int index, string itemValue)
        {
            this.index = index;
            this.itemValue = itemValue;
        }
    }
}
