// The WAP Binary XML (WBXML) specification is developed by the 
// Open Mobile Alliance (http://www.openmobilealliance.org/)
// Details about this specification can be found at
// http://www.openmobilealliance.org/tech/affiliates/wap/wap-192-wbxml-20010725-a.pdf

using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Granite.Tracing.Decoding
{
    public class AttributeStart
    {
        private byte token;
        private string name;
        private string prefix;

        public byte Token
        {
            get
            {
                return this.token;
            }
        }

        public string Name
        {
            get
            {
                return this.name;
            }
        }

        public string Prefix
        {
            get
            {
                return this.prefix;
            }
        }

        public AttributeStart(byte token, string name)
            : this(token, name, "")
        {
        }

        public AttributeStart(byte token, string name, string prefix)
        {
            this.token = token;
            this.name = name;
            this.prefix = prefix;
        }
    }
}
