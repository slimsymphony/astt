// The WAP Binary XML (WBXML) specification is developed by the 
// Open Mobile Alliance (http://www.openmobilealliance.org/)
// Details about this specification can be found at
// http://www.openmobilealliance.org/tech/affiliates/wap/wap-192-wbxml-20010725-a.pdf

using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Granite.Tracing.Decoding
{
    public class AttributeCodeSpace
    {
        private int codepage = 0;

        private List<AttributeCodePage> codePages = new List<AttributeCodePage>();

        public void AddCodePage(AttributeCodePage codePage)
        {
            codePages.Add(codePage);
        }

        public virtual AttributeCodePage GetCodePage()
        {
            return codePages[codepage];
        }

        public void SwitchCodePage(int codepage)
        {
            this.codepage = codepage;
        }

    }
}