// The WAP Binary XML (WBXML) specification is developed by the 
// Open Mobile Alliance (http://www.openmobilealliance.org/)
// Details about this specification can be found at
// http://www.openmobilealliance.org/tech/affiliates/wap/wap-192-wbxml-20010725-a.pdf

using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Granite.Tracing.Decoding
{
    public class Tag
    {
        private byte token;
        private string name;

        public byte Token
        {
            get
            {
                return token;
            }
        }

        public string Name
        {
            get
            {
                return name;
            }
        }

        public Tag(byte token, string name)
        {
            this.token = token;
            this.name = name;
        }
    }
}
