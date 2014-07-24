// The WAP Binary XML (WBXML) specification is developed by the 
// Open Mobile Alliance (http://www.openmobilealliance.org/)
// Details about this specification can be found at
// http://www.openmobilealliance.org/tech/affiliates/wap/wap-192-wbxml-20010725-a.pdf

using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Granite.Display.Capture
{
    public abstract class TagCodeSpace
    {
        private int codepageId = 0;

        private List<TagCodePage> codePages = new List<TagCodePage>();

        public void AddCodePage(TagCodePage codePage)
        {
            codePages.Add(codePage);
        }

        public virtual TagCodePage GetCodePage()
        {
            return codePages[codepageId];
        }

        public void SwitchCodePage(int codepageId)
        {
            this.codepageId = codepageId;
        }

        public int ContainsTag(string name)
        {
            if (codePages[codepageId].ContainsTag(name))
            {
                return codepageId;
            }

            for (int i = 0; i < codePages.Count; i++)
            {
                if (i != codepageId)
                {
                    if (codePages[i].ContainsTag(name))
                    {
                        return i;
                    }
                }
            }

            return -1;
        }

        public int CodePageId
        {
            get
            {
                return codepageId;
            }
        }

        public abstract int GetPublicIdentifier();
    }
}
