// The WAP Binary XML (WBXML) specification is developed by the 
// Open Mobile Alliance (http://www.openmobilealliance.org/)
// Details about this specification can be found at
// http://www.openmobilealliance.org/tech/affiliates/wap/wap-192-wbxml-20010725-a.pdf

using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Collections;
using System.Xml.Linq;
using System.IO;
using System.Linq;
using System.Drawing;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Reflection;

namespace Nokia.Granite.Tracing.Decoding
{
    public sealed class GraniteWbxmlDocument : XmlDocument
    {
        private static GraniteWbxmlDocument instance;
        private static readonly object LockObject = new Object();
        private GlobalTokens globalTokens = new GlobalTokens();
        private GraniteTokens grnTokens = new GraniteTokens();
        private GraniteAttributeLabels grnAttributeLabels = new GraniteAttributeLabels();
        private GraniteAttributeValues grnAttributeValues = new GraniteAttributeValues();
        private FontTokens fontTokens = new FontTokens();

        private TagCodeSpace tagCodeSpace = new EmptyCodeSpace();
        private AttributeCodeSpace attributeCodeSpace = new AttributeCodeSpace();
        private Encoding textEncoding = Encoding.UTF8;
        private double versionNumber;
        private int publicIdentifier;
        private StringTable stringTable = new StringTable();
        private List<OpaqueDataExpression> opaqueDataExpressions = new List<OpaqueDataExpression>();
        private List<GraniteImage> grnImages = new List<GraniteImage>();
        private bool callerVerified = false;

        // Singleton instance for thread safety
        public static GraniteWbxmlDocument Instance
        {
            get
            {
                if (instance == null)
                {
                    lock (LockObject)
                    {
                        if (instance == null)
                        {
                            instance = new GraniteWbxmlDocument();
                        }
                    }
                }
                return instance;
            }
        }

        // private constructor
        private GraniteWbxmlDocument()
        {
        }

        public string ToString(bool doIndent)
        {
            if (string.IsNullOrEmpty(this.OuterXml))
            {
                return base.ToString();
            }
            else if (!doIndent)
            {
                return this.OuterXml;
            }
            else
            {
                XDocument document;
                using (StringReader reader = new StringReader(this.OuterXml))
                {
                    //return XDocument.Load(new StringReader(this.OuterXml)).ToString();
                    document = XDocument.Load(reader);
                }
                return document.ToString();

            }
        }
        
        public double VersionNumber
        {
            get
            {
                return this.versionNumber;
            }
            set
            {
                this.versionNumber = value;
            }
        }

        public int PublicIdentifier
        {
            get
            {
                return this.publicIdentifier;
            }
            set
            {
                this.publicIdentifier = value;
            }
        }

        public Encoding Encoding
        {
            get
            {
                return this.textEncoding;
            }
            set
            {
                this.textEncoding = value;
            }
        }

        public TagCodeSpace TagCodeSpace
        {
            get
            {
                return this.tagCodeSpace;
            }
            set
            {
                this.tagCodeSpace = value;
            }
        }

        public AttributeCodeSpace AttributeCodeSpace
        {
            get
            {
                return this.attributeCodeSpace;
            }
            set
            {
                this.attributeCodeSpace = value;
            }
        }

        public StringTable StringTable
        {
            get
            {
                return this.stringTable;
            }
            set
            {
                this.stringTable = value;
            }
        }

        public List<OpaqueDataExpression> OpaqueDataExpressions
        {
            get
            {
                return this.opaqueDataExpressions;
            }
        }

        #region Decoder

        public void Decode(byte[] bytes, string imagePath)
        {
            DecodeWBXML(bytes);
            HandleImages(imagePath);
        }
        
        private void DecodeWBXML(byte[] bytes)
        {
            VerifyAssemblyCaller();
            
            // clear all nodes from XmlDocument
            this.RemoveAll();

            AttributeCodePage codePage = new AttributeCodePage();
            attributeCodeSpace.AddCodePage(codePage);

            tagCodeSpace.SwitchCodePage(1);                        
            attributeCodeSpace.SwitchCodePage(0);

            bool isAttribute = false;
            bool tagHasAttributes = false;
            bool tagHasContent = false;

            // variables for bitmap handling
            List<Int32> bitmapBytes = new List<Int32>();
            List<IList> bitmapByteLists = new List<IList>();
            string bitmapTag = "bitmap";
            int bitmapWidth = 0;
            int bitmapHeight = 0;
            bool littleEndianCpu = true;
            GraniteImage.BitmapType bitmapType = GraniteImage.BitmapType.CAPTURE_BITMAP;

            // empty grnImages list
            grnImages.Clear();
            
            XmlNode activeNode = this;
            XmlAttribute activeAttribute = null;

            Queue<byte> byteQueue = new Queue<byte>(bytes);

            //Get the WBXML version number;
            versionNumber = ((double)byteQueue.Dequeue() / 10.0) + 1.0;

            //Get the value of the public identifier
            publicIdentifier = GetInt(byteQueue);

            if (publicIdentifier == 0)
            {
                //TODO the publicIdentifier is defined as string inside the stringtable
                int publicIdentifierStringTableIndex = GetInt(byteQueue);
            }

            //Get the charset for text encoding
            textEncoding = IANACharacterSets.GetEncoding(GetInt(byteQueue));

            XmlDeclaration declaration = CreateXmlDeclaration("1.0", textEncoding.WebName, null);
            activeNode.AppendChild(declaration);

            //Get the string table (use of the string table is not implemented)
            int stringTableLength = GetInt(byteQueue);
            if (stringTableLength > 0)
            {
                Queue<byte> byteStringTableQueue = new Queue<byte>();
                for (int i = 0; i < stringTableLength; i++)
                {
                    byteStringTableQueue.Enqueue(byteQueue.Dequeue());
                }

                List<string> stringTableList = new List<string>();

                while (byteStringTableQueue.Count > 0)
                {
                    string stringTableItem = GetString(byteStringTableQueue);
                    stringTableList.Add(stringTableItem);
                }

                stringTable = new StringTable(stringTableList.ToArray());
            }

            //WBXML body
            while (byteQueue.Count > 0)
            {
                byte byteItem = byteQueue.Dequeue();

                if (globalTokens.Contains(byteItem))
                {
                    GraniteWbxmlGlobals globalToken = globalTokens.GetToken(byteItem);

                    switch (globalToken)
                    {
                        //case GraniteWbxmlGlobals.GRN_WBXML_SWITCH_PAGE:     //not used

                            //tagCodeSpace.SwitchCodePage((int)byteQueue.Dequeue());
                            //break;

                        case GraniteWbxmlGlobals.GRN_WBXML_END:
                            if (isAttribute)
                            {
                                isAttribute = false;
                                activeAttribute = null;

                                if (!tagHasContent)
                                {
                                    activeNode = activeNode.ParentNode;
                                }
                            }
                            else if (activeNode.ParentNode != null && activeNode.Name != "teststep")
                            {
                                activeNode = activeNode.ParentNode;
                            }
                            break;

                        case GraniteWbxmlGlobals.GRN_WBXML_ENTITY: //not used

                            //int entityLength = GetInt(byteQueue);
                            break;

                        //used for string values and text content
                        case GraniteWbxmlGlobals.GRN_WBXML_STR_I:
                        case GraniteWbxmlGlobals.GRN_WBXML_LITERAL:     //not in use
                        case GraniteWbxmlGlobals.GRN_WBXML_EXT_I_0:     //not in use
                        case GraniteWbxmlGlobals.GRN_WBXML_EXT_I_1:     //not in use
                        case GraniteWbxmlGlobals.GRN_WBXML_EXT_I_2:     //not in use
                        case GraniteWbxmlGlobals.GRN_WBXML_PI:          //not in use
                        case GraniteWbxmlGlobals.GRN_WBXML_LITERAL_C:   //not in use
                            if (activeNode.Name == "xml")
                            {
                                XmlDocument xmlDump = new XmlDocument();
                                char[] trimList = "\"".ToCharArray();

                                String xmlString = GetString(byteQueue);

                                // replace xml token strings
                                xmlString = xmlString.Replace("&", "&amp;");
                                xmlString = xmlString.Replace("\"<\"", "\"&lt;\"").Replace("'<'", "'&lt;'");
                                xmlString = xmlString.Replace("\">\"", "\"&gt;\"").Replace("'>'", "'&gt;'");
                                
                                // replace strings """ and '''
                                // FIXME: Add also replacing for string like "some"text"
                                xmlString = xmlString.Replace("\"\"\"", "'\"'");
                                xmlString = xmlString.Replace("'''", "\"'\"");

                                try
                                {
                                    xmlDump.LoadXml(xmlString);
                                }
                                catch (XmlException)
                                {
                                    try
                                    {
                                        // sanitize xml string in case of invalid characters
                                        xmlDump.LoadXml(SanitizeXmlString(xmlString));
                                    }
                                    catch (XmlException)
                                    {
                                        // if sanitation is not working, there isn't much to be done
                                    }
                                }

                                if (xmlDump.DocumentElement != null)
                                {                                    
                                    // append loaded xml to active node
                                    try
                                    {
                                        activeNode.AppendChild(this.ImportNode(xmlDump.DocumentElement, true));
                                    }
                                    catch (XmlException)
                                    {
                                        //something went wrong, create plain text node for debugging
                                        activeNode.AppendChild(CreateTextNode(xmlString));
                                    }
                                }
                                else
                                {
                                    // sx resp is not valid xml --> create plain text node for debugging
                                    activeNode.AppendChild(CreateTextNode(xmlString));
                                }
                            }
                            else
                            {
                                if (isAttribute && activeAttribute != null)
                                {
                                    activeAttribute.InnerText += GetString(byteQueue);
                                }
                                else
                                {
                                    activeNode.AppendChild(CreateTextNode(GetString(byteQueue)));
                                }
                            }
                            break;

                        //used for integer values
                        case GraniteWbxmlGlobals.GRN_WBXML_EXT_0:
                        case GraniteWbxmlGlobals.GRN_WBXML_EXT_1:       //not in use
                        case GraniteWbxmlGlobals.GRN_WBXML_EXT_2:       //not in use
                        case GraniteWbxmlGlobals.GRN_WBXML_STR_T:       //not in use
                        case GraniteWbxmlGlobals.GRN_WBXML_LITERAL_A:   //not in use
                        case GraniteWbxmlGlobals.GRN_WBXML_EXT_T_0:     //not in use
                        case GraniteWbxmlGlobals.GRN_WBXML_EXT_T_1:     //not in use
                        case GraniteWbxmlGlobals.GRN_WBXML_EXT_T_2:     //not in use

                            if (isAttribute && activeAttribute != null)
                            {
                                if (activeAttribute.Name == "font")
                                {
                                    activeAttribute.Value = fontTokens.GetFontValue((byte)GetInt(byteQueue));
                                }
                                else
                                {
                                    activeAttribute.Value = GetInt64(byteQueue).ToString();
                                }
                            }

                            break;

                        //used for bitmap images
                        case GraniteWbxmlGlobals.GRN_WBXML_OPAQUE:
                            int opaqueLength = GetInt(byteQueue);

                            Int32[] opaqueIntArray = GetInt32Array(byteQueue, opaqueLength);

                            byteQueue.Skip(opaqueLength);

                            // gather 32-bit image data to bitmapBytes list                            
                            foreach (Int32 item in opaqueIntArray)
                            {
                                bitmapBytes.Add(item);
                            }

                            break;

                        case GraniteWbxmlGlobals.GRN_WBXML_LITERAL_AC:
                            //Not in use
                            break;
                    }
                }
                else if (!isAttribute)
                {
                    tagHasAttributes = IsBitSet(byteItem, 7);
                    tagHasContent = IsBitSet(byteItem, 6);

                    byteItem &= 127;
                    byteItem &= 63;

                    string tagValue;
                    string dataTag = "data";

                    if (grnTokens.Contains(byteItem))
                    {
                        tagValue = grnTokens.GetTokenString(byteItem);
                    }

                    else if (tagCodeSpace.GetCodePage().ContainsTag(byteItem))
                    {
                        tagValue = tagCodeSpace.GetCodePage().GetTag(byteItem).Name;
                    }

                    else
                    {
                        tagValue = "Tag_" + byteItem.ToString("X2");
                    }

                    // get bitmap information for image creation purposes
                    if (activeNode.Name == "bitmap")
                    {
                        if (bitmapHeight == 0 && bitmapWidth == 0)
                        {
                            XmlElement xmlNode = (XmlElement)activeNode;

                            bitmapHeight = Convert.ToInt32(xmlNode.GetAttribute("height"));
                            bitmapWidth = Convert.ToInt32(xmlNode.GetAttribute("width"));

                            if (xmlNode.GetAttribute("little_endian_cpu") == "yes")
                            {
                                littleEndianCpu = true;
                            }
                            else
                            {
                                littleEndianCpu = false;
                            }

                            // set bitmap type info according to parent
                            if (xmlNode.ParentNode.Name == "capture")
                            {
                                bitmapType = GraniteImage.BitmapType.CAPTURE_BITMAP;
                            }
                            else
                            {
                                bitmapType = GraniteImage.BitmapType.ERROR_BITMAP;
                            }
                            // FIXME: Create another bitmap type for bitmap verify images if needed
                        }
                    }

                    // skip xml node creation and handling for data tags
                    if (grnTokens.GetByte(dataTag) != byteItem)
                    {
                        XmlElement xmlElement = CreateElement(tagValue);

                        activeNode.AppendChild(xmlElement);

                        if (tagHasContent || tagHasAttributes)
                        {
                            activeNode = xmlElement;

                            if (tagHasAttributes)
                            {
                                isAttribute = true;
                            }
                        }
                    }
                }
                // when bitmap tag is found and data has already been gathered, store bitmap bytes
                else if (grnTokens.GetByte(bitmapTag) == byteItem && bitmapBytes.Count > 0)
                {
                    bitmapByteLists.Add(bitmapBytes);
                    bitmapBytes.Clear();
                    bitmapHeight = 0;
                    bitmapWidth = 0;
                }
                else
                {
                    if (byteItem < 128)
                    {
                        if (grnAttributeLabels.Contains(byteItem))
                        {
                            XmlAttribute xmlAttribute = CreateAttribute(grnAttributeLabels.GetTokenString(byteItem));
                            activeNode.Attributes.Append(xmlAttribute);
                            activeAttribute = xmlAttribute;
                        }
                        else if (attributeCodeSpace.GetCodePage().ContainsAttributeStart(byteItem))
                        {
                            AttributeStart attributeStart = attributeCodeSpace.GetCodePage().GetAttributeStart(byteItem);
                            XmlAttribute xmlAttribute = CreateAttribute(attributeStart.Name);
                            xmlAttribute.InnerText = attributeStart.Prefix;
                            activeNode.Attributes.Append(xmlAttribute);

                            activeAttribute = xmlAttribute;
                        }
                        else
                        {
                            XmlAttribute xmlAttribute = CreateAttribute("attribute_" + byteItem.ToString("X2"));
                            activeNode.Attributes.Append(xmlAttribute);

                            activeAttribute = xmlAttribute;
                        }
                    }
                    else
                    {
                        if (grnAttributeValues.Contains(byteItem) && activeAttribute != null)
                        {
                            activeAttribute.Value = grnAttributeValues.GetTokenString(byteItem);
                        }

                        else if (attributeCodeSpace.GetCodePage().ContainsAttributeValue(byteItem) && activeAttribute != null)
                        {
                            AttributeValue attributeValue = attributeCodeSpace.GetCodePage().GetAttributeValue(byteItem);
                            activeAttribute.InnerText += attributeValue.Value;
                        }
                    }
                }
            }

        // get last bitmap byte list
        if (bitmapBytes.Count > 0)
        {
            bitmapByteLists.Add(bitmapBytes);
        }

        // create image from every bitmap byte list
        foreach (List<Int32> bitmapByteList in bitmapByteLists)
        {
            CreateBitmapImage(bitmapByteList, bitmapWidth, bitmapHeight, littleEndianCpu, bitmapType);
        }

        }

        // returns root document as cloned XmlDocument instance
        private XmlDocument GetXml()
        {
            return (XmlDocument)this.CloneNode(true);
        }

        private void HandleImages(string imagePath)
        {
            // NOTE: Only one image can be in the list
            if (grnImages.Count > 0)
            {
                string imageDir = Path.GetDirectoryName(imagePath);

                foreach (GraniteImage image in grnImages)
                {
                    bool dirExists = Directory.Exists(imageDir);

                    if (!dirExists)
                    {
                        Directory.CreateDirectory(imageDir);
                    }

                    image.bitmap.Save(imagePath);
                    image.bitmap.Dispose();
                }
            }

            // empty images list
            grnImages.Clear();
        }

        private string SanitizeXmlString(string xml)
        {
            if (xml == null)
            {
                throw new ArgumentNullException("xml is missing");
            }
        
            StringBuilder buffer = new StringBuilder(xml.Length);

            foreach (char c in xml)
            {
                if (IsLegalXmlChar(c))
                {
                    buffer.Append(c);
                }
            }

        return buffer.ToString();
        }

        private bool IsLegalXmlChar(int character)
        {
            return
            (
            character == 0x9 /* == '\t' == 9   */          ||
            character == 0xA /* == '\n' == 10  */          ||
            character == 0xD /* == '\r' == 13  */          ||
            (character >= 0x20    && character <= 0xD7FF  ) ||
            (character >= 0xE000  && character <= 0xFFFD  ) ||
            (character >= 0x10000 && character <= 0x10FFFF)
            );
        }

        #endregion

        #region Encoder
        public byte[] GetBytes()
        {
            List<byte> bytesList = new List<byte>();

            //Versionnumber
            bytesList.Add((byte)((int)((versionNumber * 10) - 10)));

            //Public identifier (currently implemented as unknown)
            bytesList.AddRange(GetMultiByte((int)GraniteWbxmlPublicId.GRN_WBXML_PUBLIC_ID));

            //Encoding
            bytesList.AddRange(GetMultiByte((int)GraniteWbxmlCharsets.GRN_WBXML_CHARSET_UTF8));

            //String table length
            int stringTableLength = stringTable.Length;
            if (stringTableLength > 0)
            {
                bytesList.AddRange(GetMultiByte(stringTableLength));
                bytesList.AddRange(stringTable.GetStringTableBytes(textEncoding));
            }
            else
            {
                bytesList.Add(0);
            }

            bytesList.AddRange(EncodeNodes(this.ChildNodes));

            return bytesList.ToArray();
        }

        private byte[] EncodeNodes(XmlNodeList nodes)
        {
            List<byte> bytesList = new List<byte>();

            foreach (XmlNode node in nodes)
            {
                bytesList.AddRange(EncodeNode(node));
            }

            return bytesList.ToArray();
        }

        private byte[] EncodeNode(XmlNode node)
        {
            List<byte> bytesList = new List<byte>();

            switch (node.NodeType)
            {
                case XmlNodeType.Element:
                
                    bool hasAttributes = node.Attributes.Count > 0;
                    bool hasContent = node.HasChildNodes;
                    //int codePage = tagCodeSpace.ContainsTag(node.Name);

                    if (grnTokens.Contains(node.Name))
                    {
                        byte keyValue = grnTokens.GetByte(node.Name);
                        if (hasAttributes)
                        {
                            keyValue |= 128;
                        }
                        if (hasContent)
                        {
                            keyValue |= 64;
                        }
                        bytesList.Add(keyValue);
                    }

                    else if (tagCodeSpace.ContainsTag(node.Name) >= 0)
                    {
                        if (tagCodeSpace.CodePageId != tagCodeSpace.ContainsTag(node.Name))
                        {
                            bytesList.Add((byte)GraniteWbxmlGlobals.GRN_WBXML_SWITCH_PAGE);
                            bytesList.Add((byte)tagCodeSpace.ContainsTag(node.Name));
                            tagCodeSpace.SwitchCodePage(tagCodeSpace.ContainsTag(node.Name));
                        }

                        byte keyValue = tagCodeSpace.GetCodePage().GetTag(node.Name).Token;
                        if (hasAttributes)
                        {
                            keyValue |= 128;
                        }
                        if (hasContent)
                        {
                            keyValue |= 64;
                        }
                        bytesList.Add(keyValue);
                    }
                    else
                    {
                        //TODO: unkown tag
                    }

                    if (hasAttributes)
                    {
                        foreach (XmlAttribute attribute in node.Attributes)
                        {
                            bytesList.AddRange(EncodeNode(attribute));
                        }
                        bytesList.Add((byte)GraniteWbxmlGlobals.GRN_WBXML_END);
                    }

                    if (hasContent)
                    {
                        bytesList.AddRange(EncodeNodes(node.ChildNodes));
                        bytesList.Add((byte)GraniteWbxmlGlobals.GRN_WBXML_END);
                    }
                    break;
                
                case XmlNodeType.Text:
                
                    bool isOpaqueData = false;

                    if (opaqueDataExpressions.Count > 0)
                    {
                        foreach (OpaqueDataExpression expression in OpaqueDataExpressions)
                        {
                            if (expression.TagName.Equals(node.ParentNode.Name))
                            {
                                if (node.ParentNode.SelectSingleNode(expression.Expression) != null)
                                {
                                    isOpaqueData = true;
                                    break;
                                }
                            }
                        }
                    }

                    if (isOpaqueData)
                    {
                        byte[] opaqueDataBytes = GetBytes(node.Value);
                        bytesList.Add((byte)GraniteWbxmlGlobals.GRN_WBXML_OPAQUE);
                        bytesList.AddRange(GetMultiByte(opaqueDataBytes.Length));
                        bytesList.AddRange(opaqueDataBytes);
                    }
                    else
                    {
                        string textValue = node.Value;

                        while (textValue.Length > 0)
                        {
                            int stringTableIndex = textValue.Length;

                            if (stringTable.ContainsString(textValue))
                            {
                                StringTableItem stringTableItem = stringTable.GetString(textValue);
                                stringTableIndex = textValue.IndexOf(stringTableItem.Value);

                                if (stringTableIndex == 0)
                                {
                                    bytesList.Add((byte)GraniteWbxmlGlobals.GRN_WBXML_STR_T);
                                    bytesList.AddRange(GetMultiByte(stringTableItem.Index));
                                    textValue = textValue.Substring(stringTableItem.Value.Length);
                                    continue;
                                }
                            }

                            bytesList.Add((byte)GraniteWbxmlGlobals.GRN_WBXML_STR_I);
                            bytesList.AddRange(textEncoding.GetBytes(textValue.Substring(0, stringTableIndex)));
                            bytesList.Add(0);

                            textValue = textValue.Substring(stringTableIndex);
                        }
                    }
                    break;
                
                case XmlNodeType.EntityReference:
                    
                    bytesList.Add((byte)GraniteWbxmlGlobals.GRN_WBXML_ENTITY);
                    XmlEntityReference reference = (XmlEntityReference)node;
                    foreach (int stringItem in reference.InnerText.ToCharArray())
                    {
                        bytesList.AddRange(GetMultiByte(stringItem));
                    }
                    break;
                
                case XmlNodeType.Attribute:

                    if (grnAttributeLabels.Contains(node.Name))
                    {
                        AttributeStart attributeStart = new AttributeStart(grnAttributeLabels.GetByte(node.Name), node.Name);
                        bytesList.Add(attributeStart.Token);

                        string postAttributeValue = node.Value.Substring(attributeStart.Prefix.Length);
                        while (postAttributeValue.Length > 0)
                        {
                            int attrValueIndex = postAttributeValue.Length;

                            if (grnAttributeValues.Contains(postAttributeValue))
                            {
                                AttributeValue attrValue = new AttributeValue(grnAttributeValues.GetByte(postAttributeValue), postAttributeValue);
                                attrValueIndex = postAttributeValue.IndexOf(attrValue.Value);

                                if (attrValueIndex == 0)
                                {
                                    bytesList.Add(attrValue.Token);
                                    postAttributeValue = postAttributeValue.Substring(attrValue.Value.Length);
                                    continue;
                                }
                            }

                            int stringTableIndex = postAttributeValue.Length;

                            if (stringTable.ContainsString(postAttributeValue))
                            {
                                StringTableItem stringTableItem = stringTable.GetString(postAttributeValue);
                                stringTableIndex = postAttributeValue.IndexOf(stringTableItem.Value);

                                if (stringTableIndex == 0)
                                {
                                    bytesList.Add((byte)GraniteWbxmlGlobals.GRN_WBXML_STR_T);
                                    bytesList.AddRange(GetMultiByte(stringTableItem.Index));

                                    postAttributeValue = postAttributeValue.Substring(stringTableItem.Value.Length);
                                    continue;
                                }
                            }

                            int firstReferenceIndex = Math.Min(attrValueIndex, stringTableIndex);
                            bytesList.Add((byte)GraniteWbxmlGlobals.GRN_WBXML_STR_I);
                            bytesList.AddRange(textEncoding.GetBytes(postAttributeValue.Substring(0, firstReferenceIndex)));
                            bytesList.Add(0);

                            postAttributeValue = postAttributeValue.Substring(firstReferenceIndex);
                        }
                    }

                    else if (attributeCodeSpace.GetCodePage().ContainsAttributeStart(node.Name, node.Value))
                    {
                        AttributeStart attributeStart = attributeCodeSpace.GetCodePage().GetAttributeStart(node.Name, node.Value);
                        bytesList.Add(attributeStart.Token);

                        string postAttributeValue = node.Value.Substring(attributeStart.Prefix.Length);
                        while (postAttributeValue.Length > 0)
                        {
                            int attrValueIndex = postAttributeValue.Length;

                            if (attributeCodeSpace.GetCodePage().ContainsAttributeValue(postAttributeValue))
                            {
                                AttributeValue attrValue = attributeCodeSpace.GetCodePage().GetAttributeValue(postAttributeValue);
                                attrValueIndex = postAttributeValue.IndexOf(attrValue.Value);

                                if (attrValueIndex == 0)
                                {
                                    bytesList.Add(attrValue.Token);
                                    postAttributeValue = postAttributeValue.Substring(attrValue.Value.Length);
                                    continue;
                                }
                            }

                            int stringTableIndex = postAttributeValue.Length;

                            if (stringTable.ContainsString(postAttributeValue))
                            {
                                StringTableItem stringTableItem = stringTable.GetString(postAttributeValue);
                                stringTableIndex = postAttributeValue.IndexOf(stringTableItem.Value);

                                if (stringTableIndex == 0)
                                {
                                    bytesList.Add((byte)GraniteWbxmlGlobals.GRN_WBXML_STR_T);
                                    bytesList.AddRange(GetMultiByte(stringTableItem.Index));

                                    postAttributeValue = postAttributeValue.Substring(stringTableItem.Value.Length);
                                    continue;
                                }
                            }

                            int firstReferenceIndex = Math.Min(attrValueIndex, stringTableIndex);
                            bytesList.Add((byte)GraniteWbxmlGlobals.GRN_WBXML_STR_I);
                            bytesList.AddRange(textEncoding.GetBytes(postAttributeValue.Substring(0, firstReferenceIndex)));
                            bytesList.Add(0);

                            postAttributeValue = postAttributeValue.Substring(firstReferenceIndex);
                        }
                    }
                    break;
            }

            return bytesList.ToArray();
        }
        #endregion
        
        #region Util Methods

        private string GetString(Queue<byte> byteQueue)
        {
            List<byte> byteList = new List<byte>();
            while (byteQueue.Count > 0 && byteQueue.Peek() != 0)
            {
                byteList.Add(byteQueue.Dequeue());
            }

            if (byteQueue.Count > 0)
            {
                byteQueue.Dequeue();
            }

            return textEncoding.GetString(byteList.ToArray());
        }

        private string GetString(Queue<byte> byteQueue, int length)
        {
            List<byte> byteList = new List<byte>();
            for (int i = 0; i < length; i++)
            {
                byteList.Add(byteQueue.Dequeue());
            }
            return textEncoding.GetString(byteList.ToArray());
        }

        private byte[] GetMultiByte(int multiByteValue)
        {
            if (multiByteValue == 0)
            {
                return new byte[] { 0x00 };
            }
            else
            {
                List<byte> multiByteList = new List<byte>();

                while (multiByteValue > 0)
                {
                    int byteValue = 0;
                    for (int i = 0; i < 7; i++)
                    {
                        if (IsBitSet(multiByteValue, i))
                        {
                            byteValue += (int)Math.Pow(2, i);
                        }
                    }

                    if (multiByteList.Count > 0)
                    {
                        byteValue += 128;
                    }

                    multiByteList.Insert(0, (byte)byteValue);
                    multiByteValue >>= 7;
                }

                return multiByteList.ToArray();
            }
        }

        private int GetInt(Queue<byte> byteQueue)
        {
            List<byte> multiByteList = new List<byte>();
            while (IsBitSet(byteQueue.Peek(), 7))
            {
                byte byteItem = byteQueue.Dequeue();
                byteItem &= 127;
                multiByteList.Add(byteItem);
            }

            //Add the next byte because it is the last part of the multibyte
            //(or even the only part of the multibyte)
            multiByteList.Add(byteQueue.Dequeue());

            int returnValue = 0;
            for (int i = 0; i < multiByteList.Count; i++)
            {
                int byteValue = (int)multiByteList[i];
                double power = 7 * (multiByteList.Count - 1 - i);
                returnValue += (int)(byteValue * Math.Pow(2, power));
            }
            return returnValue;
        }

        private Int64 GetInt64(Queue<byte> byteQueue)
        {
            List<byte> multiByteList = new List<byte>();
            while (IsBitSet(byteQueue.Peek(), 7))
            {
                byte byteItem = byteQueue.Dequeue();
                byteItem &= 127;
                multiByteList.Add(byteItem);
            }

            //Add the next byte because it is the last part of the multibyte
            //(or even the only part of the multibyte)
            multiByteList.Add(byteQueue.Dequeue());

            Int64 returnValue = 0;
            for (int i = 0; i < multiByteList.Count; i++)
            {
                int byteValue = (int)multiByteList[i];
                double power = 7 * (multiByteList.Count - 1 - i);
                returnValue += Convert.ToInt64(byteValue * Math.Pow(2, power));
            }
            return returnValue;
        }

        private byte[] GetByteArray(Queue<byte> messageQueue, int length)
        {
            List<byte> byteList = new List<byte>();
            for (int i = 0; i < length; i++)
            {
                byteList.Add(messageQueue.Dequeue());
            }
            return byteList.ToArray();
        }

        private Int32[] GetInt32Array(Queue<byte> messageQueue, int length)
        {
            List<Int32> intList = new List<Int32>();
            for (int i = 0; i < length; i++)
            {
                intList.Add(messageQueue.Dequeue());
            }
            return intList.ToArray();
        }

        private byte[] GetBytes(string messageValue)
        {
            List<byte> byteList = new List<byte>();
            if (messageValue == null || messageValue.Length % 2 == 1)
            {
                return byteList.ToArray();
            }

            for (int i = 0; i < messageValue.Length / 2; i++)
            {
                byteList.Add((byte)Int32.Parse(messageValue.Substring(i * 2, 2), System.Globalization.NumberStyles.HexNumber));
            }

            return byteList.ToArray();
        }

        private bool IsBitSet(int byteItem, int bitNumber)
        {
            return ((byteItem & (1 << bitNumber)) == Math.Pow(2, bitNumber));
        }


        private void CreateBitmapImage(List<Int32> bitmapBytes, int width, int height, bool littleEndianCpu, GraniteImage.BitmapType bitmapType)
        {     
            List<Int32> bytesList = new List<Int32>();            
            Bitmap image = new Bitmap(width, height);
            
            for (int index = 0; index < bitmapBytes.Count; index += 2)
            {
                Int32 value;

                if (littleEndianCpu)
                {
                    value = bitmapBytes[index + 1] << 8;
                    value += bitmapBytes[index];
                }
                else
                {
                    value = bitmapBytes[index] << 8;
                    value += bitmapBytes[index + 1];
                }

                bytesList.Add(value);
            }

            int dataIndex = 0;

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    int red = (int)((((bytesList[dataIndex] & 0xf800) >> 11) * 0xff) / 0x1f);
                    int green = (int)((((bytesList[dataIndex] & 0x07e0) >> 5) * 0xff) / 0x3f);
                    int blue = (int)(((bytesList[dataIndex] & 0x001f) * 0xff) / 0x1f);

                    Color color = Color.FromArgb(red, green, blue);
                    image.SetPixel(x, y, color);

                    dataIndex += 1;
                }
            }

            GraniteImage grnImage = new GraniteImage();
            grnImage.bitmap = image;
            grnImage.type = bitmapType;

            grnImages.Add(grnImage);
            //image.Save("test.png"); //, System.Drawing.Imaging.ImageFormat.Png);
        }
        #endregion

        #region Protection

        internal void VerifyAssemblyCaller()
        {
            if (!IsExecutedViaDebugging)
            {                
                if (!this.callerVerified)
                {
                    if (!IsExecutedFromVisualStudio && !IsExecutedByCorrectProcess)
                    {
                        Process.GetCurrentProcess().Kill();
                    }

                    this.callerVerified = true;
                }
            }
        }

        internal bool IsCalledByAssemblyName(string assemblyName)
        {
            string myName = GetType().Assembly.GetName().Name;

            if (myName == assemblyName)
            {
                return true;
            }
            //If assembly is being called by MS dynamic, it is loaded to appdomain, but it cannot be found from MS dynamic refrence assemblies;
            //in this case, it shall not either be found from referenced assemblies by other assemblies in appdomain. MS dynamic in this case needs to
            //be loaded in appdomain
            if (assemblyName == "Microsoft.Dynamic")
            {
                //If MS dynamic is not loaded at all...
                if (!AppDomain.CurrentDomain.GetAssemblies().Any(a => a.GetName().Name == "Microsoft.Dynamic"))
                {
                    return false;
                }
                //other assemblis than this itself and MS Dynamic
                var assemblies = AppDomain.CurrentDomain.GetAssemblies().Where(a => a.GetName().Name != "Microsoft.Dynamic"
                    && a.GetName().Name != myName);

                bool anyOtherReferences = assemblies.Any(a => a.GetReferencedAssemblies().Any(an => an.Name == myName));

                return !anyOtherReferences;
            }
            else
            {
                Assembly ass = AppDomain.CurrentDomain.GetAssemblies().First(a => a.GetName().Name == assemblyName);

                if (ass != null)
                {
                    Console.WriteLine();
                    return ass.GetReferencedAssemblies().Any(an => an.Name == myName);
                }

                return false;
            }
        }

        internal bool VerifyEntryAssemblyByName(string assemblyName)
        {
            return Assembly.GetEntryAssembly().GetName().Name == assemblyName;
        }

        internal bool IsRunningInProcessByName(string processName)
        {
            return Process.GetCurrentProcess().ProcessName == processName;
        }


        internal bool IsExecutedByCorrectProcess
        {
            get
            {
                return IsExecutedByProcessName("fasttrace", false, false) || IsExecutedByProcessName("GraniteDisplayCapture.vshost", false, false);
            }
        }

        internal bool IsExecutedFromVisualStudio
        {
            get
            {
                Process p = Process.GetCurrentProcess();

                if (!p.HasParent())
                {
                    return true;
                }

                string parentName = p.ParentProcess().ProcessName;

                return parentName == "devenv";
            }
        }

        internal bool IsExecutedViaDebugging
        {
            get
            {
                return System.Diagnostics.Debugger.IsAttached;
            }
        }

        internal bool IsExecutedByProcessName(string processName,
            bool checkStdOutRedirection = true,
            bool checkStdErrRedirection = true)
        {
            Process pr = Process.GetCurrentProcess();

            if (!pr.HasParent())
            {
                return false;
            }

            if (pr.ParentProcess().ProcessName != processName)
            {
                return false;
            }

            if (checkStdOutRedirection && !pr.StartInfo.RedirectStandardOutput)
            {
                return false;
            }

            if (checkStdErrRedirection && !pr.StartInfo.RedirectStandardError)
            {
                return false;
            }

            return true;
        }

        #endregion
    }

    public sealed class GraniteImage
    {
        public Bitmap bitmap = null;
        public BitmapType type = BitmapType.CAPTURE_BITMAP; 

        public enum BitmapType :int
        {
            CAPTURE_BITMAP = 1,
            ERROR_BITMAP = 2,
        }
    }

    #region Protection

    public static class ProcessExtensions
    {
        public static bool HasParent(this Process process)
        {
            try
            {
                return process.ParentProcess() != null;
            }
            catch
            {
                return false;
            }
        }

        public static Process ParentProcess(this Process process)
        {
            int parentPid = 0;
            int processPid = process.Id;
            uint TH32CS_SNAPPROCESS = 2;

            // Take snapshot of processes
            IntPtr hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

            if (hSnapshot == IntPtr.Zero)
            {
                return null;
            }

            PROCESSENTRY32 procInfo = new PROCESSENTRY32();

            procInfo.dwSize = (uint)Marshal.SizeOf(typeof(PROCESSENTRY32));

            // Read first
            if (Process32First(hSnapshot, ref procInfo) == false)
            {
                return null;
            }

            // Loop through the snapshot
            do
            {
                // If it's me, then ask for my parent.
                if (processPid == procInfo.th32ProcessID)
                {
                    parentPid = (int)procInfo.th32ParentProcessID;
                }
            }
            while (parentPid == 0 && Process32Next(hSnapshot, ref procInfo)); // Read next

            if (parentPid > 0)
            {
                return Process.GetProcessById(parentPid);
            }
            else
            {
                return null;
            }
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr CreateToolhelp32Snapshot(uint dwFlags, uint th32ProcessID);

        [DllImport("kernel32.dll")]
        private static extern bool Process32First(IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

        [DllImport("kernel32.dll")]
        private static extern bool Process32Next(IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

        [StructLayout(LayoutKind.Sequential)]
        private struct PROCESSENTRY32
        {
            public uint dwSize;
            public uint cntUsage;
            public uint th32ProcessID;
            public IntPtr th32DefaultHeapID;
            public uint th32ModuleID;
            public uint cntThreads;
            public uint th32ParentProcessID;
            public int pcPriClassBase;
            public uint dwFlags;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
            public string szExeFile;
        }
    }

    #endregion
}
