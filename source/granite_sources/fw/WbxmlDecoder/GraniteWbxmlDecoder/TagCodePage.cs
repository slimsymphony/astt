// The WAP Binary XML (WBXML) specification is developed by the 
// Open Mobile Alliance (http://www.openmobilealliance.org/)
// Details about this specification can be found at
// http://www.openmobilealliance.org/tech/affiliates/wap/wap-192-wbxml-20010725-a.pdf

using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Granite.Tracing.Decoding
{
    public class TagCodePage
    {
        private Dictionary<byte, string> tokenDictionary = new Dictionary<byte, string>();
        private Dictionary<string, byte> nameDictionary = new Dictionary<string, byte>();

        public void AddToken(byte token, string name)
        {
            tokenDictionary.Add(token, name);
            nameDictionary.Add(name, token);
        }

        public virtual bool ContainsTag(byte token)
        {
            return tokenDictionary.ContainsKey(token);
        }

        public virtual bool ContainsTag(string name)
        {
            return nameDictionary.ContainsKey(name);
        }

        public virtual Tag GetTag(byte token)
        {
            return new Tag(token, tokenDictionary[token]);
        }

        public virtual Tag GetTag(string name)
        {
            return new Tag(nameDictionary[name], name);
        }
    }
}
