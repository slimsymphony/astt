// The WAP Binary XML (WBXML) specification is developed by the 
// Open Mobile Alliance (http://www.openmobilealliance.org/)
// Details about this specification can be found at
// http://www.openmobilealliance.org/tech/affiliates/wap/wap-192-wbxml-20010725-a.pdf

using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Granite.Display.Capture
{
    public class OpaqueDataExpression
    {
        private string tagName;
        private string xPathExpression;

        public string TagName
        {
            get
            {
                return tagName;
            }
            set
            {
                this.tagName = value;
            }
        }

        public string Expression
        {
            get
            {
                return this.xPathExpression;
            }
            set
            {
                this.xPathExpression = value;
            }
        }

        public OpaqueDataExpression(string name, string expression)
        {
            this.tagName = name;
            this.xPathExpression = expression;
        }
    }
}