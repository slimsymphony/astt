// The WAP Binary XML (WBXML) specification is developed by the 
// Open Mobile Alliance (http://www.openmobilealliance.org/)
// Details about this specification can be found at
// http://www.openmobilealliance.org/tech/affiliates/wap/wap-192-wbxml-20010725-a.pdf

using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Granite.Display.Capture
{
    public class StringTable
    {
        private Dictionary<int, string> stringTableIndexDictionary = new Dictionary<int, string>();
        private Dictionary<string, int> stringTableValueDictionary = new Dictionary<string, int>();
        private int stringTableLength = 0;

        public int Length
        {
            get
            {
                return stringTableLength;
            }
        }

        public StringTable()
        {
            stringTableLength = 0;
        }

        public StringTable(string[] stringTableItems)
        {
            int stringTableIndex = 0;
            foreach (string item in stringTableItems)
            {
                stringTableIndexDictionary.Add(stringTableIndex, item);
                stringTableValueDictionary.Add(item, stringTableIndex);

                stringTableIndex += item.Length + 1;
            }
            stringTableLength = stringTableIndex;
        }

        public bool ContainsString(int index)
        {
            return stringTableIndexDictionary.ContainsKey(index);
        }

        public bool ContainsString(string stringTableValue)
        {
            foreach (string stringTableItem in stringTableValueDictionary.Keys)
            {
                if (stringTableValue.Contains(stringTableItem))
                {
                    return true;
                }
            }

            return false;
        }

        public StringTableItem GetString(string stringTableValue)
        {
            StringTableItem returnValue = null;

            foreach (string stringTableItem in stringTableValueDictionary.Keys)
            {
                if (stringTableValue.Contains(stringTableItem))
                {
                    if (returnValue == null
                        || stringTableValue.IndexOf(stringTableItem) < stringTableValue.IndexOf(returnValue.Value)
                        || stringTableItem.Length > returnValue.Value.Length)
                    {
                        returnValue = new StringTableItem(stringTableValueDictionary[stringTableItem], stringTableItem);
                    }
                }
            }

            return returnValue;
        }

        public StringTableItem GetString(int index)
        {
            return new StringTableItem(index, stringTableIndexDictionary[index]);
        }

        public byte[] GetStringTableBytes(Encoding textEncoding)
        {
            List<byte> stringTableBytes = new List<byte>();

            foreach (string item in stringTableValueDictionary.Keys)
            {
                stringTableBytes.AddRange(textEncoding.GetBytes(item));
                stringTableBytes.Add(0x00);
            }

            return stringTableBytes.ToArray();
        }

    }
}
