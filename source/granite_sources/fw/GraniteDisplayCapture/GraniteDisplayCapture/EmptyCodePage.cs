// The WAP Binary XML (WBXML) specification is developed by the 
// Open Mobile Alliance (http://www.openmobilealliance.org/)
// Details about this specification can be found at
// http://www.openmobilealliance.org/tech/affiliates/wap/wap-192-wbxml-20010725-a.pdf

using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Granite.Display.Capture
{
    public class EmptyCodePage : TagCodePage
    {
        public override bool ContainsTag(byte token)
        {
            return true;
        }

        public override Tag GetTag(byte token)
        {
            return new Tag(token, "Tag_" + token.ToString("X2"));
        }
    }
}
