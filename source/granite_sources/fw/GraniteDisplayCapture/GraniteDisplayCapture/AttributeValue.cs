// The WAP Binary XML (WBXML) specification is developed by the 
// Open Mobile Alliance (http://www.openmobilealliance.org/)
// Details about this specification can be found at
// http://www.openmobilealliance.org/tech/affiliates/wap/wap-192-wbxml-20010725-a.pdf

using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Granite.Display.Capture
{
    public class AttributeValue
    {
        private byte token;
        private string attributeValue;

        public byte Token
        {
            get
            {
                return token;
            }
        }

        public string Value
        {
            get
            {
                return attributeValue;
            }
        }

        public AttributeValue(byte token, string attributeValue)
        {
            this.token = token;
            this.attributeValue = attributeValue;
        }
    }
}
