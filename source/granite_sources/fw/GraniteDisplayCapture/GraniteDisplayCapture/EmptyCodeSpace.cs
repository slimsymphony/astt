﻿// The WAP Binary XML (WBXML) specification is developed by the 
// Open Mobile Alliance (http://www.openmobilealliance.org/)
// Details about this specification can be found at
// http://www.openmobilealliance.org/tech/affiliates/wap/wap-192-wbxml-20010725-a.pdf

using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Granite.Display.Capture
{
    class EmptyCodeSpace : TagCodeSpace
    {
        public override int GetPublicIdentifier()
        {
            return (int)0x01;
        }

        public override TagCodePage GetCodePage()
        {
            return new EmptyCodePage();
        }
    }
}
