using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Class for reading the apk information from the manifest file
    /// </summary>
    public sealed class ApkInfo
    {
        private string m_fileLocation;
        private XmlDocument m_manifest;

        /// <summary>
        /// Internal class constructor
        /// </summary>
        /// <param name="localApkFileLocation">File path to the apk file</param>
        internal ApkInfo(string localApkFileLocation)
        {
            if (string.IsNullOrEmpty(localApkFileLocation))
            {
                throw new ArgumentNullException("localApkFileLocation");
            }

            var info = new FileInfo(localApkFileLocation);

            if (!info.Exists)
            {
                throw new FileNotFoundException(localApkFileLocation);
            }

            if (info.Length == 0)
            {
                throw new Exception(string.Format("Size of {0} is zero", localApkFileLocation));
            }

            m_fileLocation = info.FullName;
            Info = info;
            m_manifest = GetManifest();
        }

        /// <summary>
        /// Gets the apk file info
        /// </summary>
        public FileInfo Info { get; private set; }

        /// <summary>
        /// Gets the decrypted manifest xml
        /// </summary>
        public XmlDocument Manifest
        {
            get
            {
                return m_manifest;
            }
        }

        /// <summary>
        /// Gets the name of the package from the manifest file
        /// Returns null if not found
        /// </summary>
        public string Package
        {
            get
            {
                if (Manifest != null)
                {
                    var node = Manifest.SelectSingleNode("//manifest[@package]");
                    if (node != null)
                    {
                        return node.Attributes["package"].Value;
                    }
                }
                return null;
            }
        }

        /// <summary>
        /// Decrypts and gets the manifest xml document
        /// </summary>
        /// <returns></returns>
        private XmlDocument GetManifest()
        {
            var bytes = GetManifestBytes(m_fileLocation);

            if (bytes != null)
            {
                var decoder = new ManifestDecoder();
                var xmlstr = decoder.decompressXML(bytes);
                var xml = new XmlDocument();
                xml.LoadXml(xmlstr);
                return xml;
            }

            return null;
        }

        /// <summary>
        /// Reads the decrypted manifest file from the apk archive
        /// </summary>
        /// <param name="localApkFile">File path of the apk archive</param>
        /// <returns>Encrypted manifest xml bytes</returns>
        private byte[] GetManifestBytes(string localApkFile)
        {
            using (ZipArchive archive = ZipFile.OpenRead(localApkFile))
            {
                foreach (ZipArchiveEntry entry in archive.Entries)
                {
                    if (string.Compare(entry.Name, "AndroidManifest.xml", true) == 0)
                    {
                        using (var ms = new MemoryStream())
                        {
                            using (var stream = entry.Open())
                            {
                                stream.CopyTo(ms);
                                ms.Position = 0;
                                return ms.ToArray();
                            }
                        }
                    }
                }
            }

            return null;
        }

        /// <summary>
        /// Summary description for ManifestDecoder
        /// </summary>
        private class ManifestDecoder
        {
            private string result = "";
            // decompressXML -- Parse the 'compressed' binary form of Android XML docs 
            // such as for AndroidManifest.xml in .apk files
            public static int endDocTag = 0x00100101;
            public static int startTag = 0x00100102;
            public static int endTag = 0x00100103;
            public string decompressXML(byte[] xml)
            {
                // Compressed XML file/bytes starts with 24x bytes of data,
                // 9 32 bit words in little endian order (LSB first):
                //   0th word is 03 00 08 00
                //   3rd word SEEMS TO BE:  Offset at then of StringTable
                //   4th word is: Number of strings in string table
                // WARNING: Sometime I indiscriminently display or refer to word in 
                //   little endian storage format, or in integer format (ie MSB first).
                int numbStrings = LEW(xml, 4 * 4);

                // StringIndexTable starts at offset 24x, an array of 32 bit LE offsets
                // of the length/string data in the StringTable.
                int sitOff = 0x24;  // Offset of start of StringIndexTable

                // StringTable, each string is represented with a 16 bit little endian 
                // character count, followed by that number of 16 bit (LE) (Unicode) chars.
                int stOff = sitOff + numbStrings * 4;  // StringTable follows StrIndexTable

                // XMLTags, The XML tag tree starts after some unknown content after the
                // StringTable.  There is some unknown data after the StringTable, scan
                // forward from this point to the flag for the start of an XML start tag.
                int xmlTagOff = LEW(xml, 3 * 4);  // Start from the offset in the 3rd word.
                // Scan forward until we find the bytes: 0x02011000(x00100102 in normal int)
                for (int ii = xmlTagOff; ii < xml.Length - 4; ii += 4)
                {
                    if (LEW(xml, ii) == startTag)
                    {
                        xmlTagOff = ii; break;
                    }
                } // end of hack, scanning for start of first start tag

                // XML tags and attributes:
                // Every XML start and end tag consists of 6 32 bit words:
                //   0th word: 02011000 for startTag and 03011000 for endTag 
                //   1st word: a flag?, like 38000000
                //   2nd word: Line of where this tag appeared in the original source file
                //   3rd word: FFFFFFFF ??
                //   4th word: StringIndex of NameSpace name, or FFFFFFFF for default NS
                //   5th word: StringIndex of Element Name
                //   (Note: 01011000 in 0th word means end of XML document, endDocTag)

                // Start tags (not end tags) contain 3 more words:
                //   6th word: 14001400 meaning?? 
                //   7th word: Number of Attributes that follow this tag(follow word 8th)
                //   8th word: 00000000 meaning??

                // Attributes consist of 5 words: 
                //   0th word: StringIndex of Attribute Name's Namespace, or FFFFFFFF
                //   1st word: StringIndex of Attribute Name
                //   2nd word: StringIndex of Attribute Value, or FFFFFFF if ResourceId used
                //   3rd word: Flags?
                //   4th word: str ind of attr value again, or ResourceId of value

                // TMP, dump string table to tr for debugging
                //tr.addSelect("strings", null);
                //for (int ii=0; ii<numbStrings; ii++) {
                //  // Length of string starts at StringTable plus offset in StrIndTable
                //  String str = compXmlString(xml, sitOff, stOff, ii);
                //  tr.add(String.valueOf(ii), str);
                //}
                //tr.parent();

                // Step through the XML tree element tags and attributes
                int off = xmlTagOff;
                int indent = 0;
                int startTagLineNo = -2;
                while (off < xml.Length)
                {
                    int tag0 = LEW(xml, off);
                    //int tag1 = LEW(xml, off+1*4);
                    int lineNo = LEW(xml, off + 2 * 4);
                    //int tag3 = LEW(xml, off+3*4);
                    int nameNsSi = LEW(xml, off + 4 * 4);
                    int nameSi = LEW(xml, off + 5 * 4);

                    if (tag0 == startTag)
                    { // XML START TAG
                        int tag6 = LEW(xml, off + 6 * 4);  // Expected to be 14001400
                        int numbAttrs = LEW(xml, off + 7 * 4);  // Number of Attributes to follow
                        //int tag8 = LEW(xml, off+8*4);  // Expected to be 00000000
                        off += 9 * 4;  // Skip over 6+3 words of startTag data
                        String name = compXmlString(xml, sitOff, stOff, nameSi);
                        //tr.addSelect(name, null);
                        startTagLineNo = lineNo;

                        // Look for the Attributes

                        string sb = "";
                        for (int ii = 0; ii < numbAttrs; ii++)
                        {
                            int attrNameNsSi = LEW(xml, off);  // AttrName Namespace Str Ind, or FFFFFFFF
                            int attrNameSi = LEW(xml, off + 1 * 4);  // AttrName String Index
                            int attrValueSi = LEW(xml, off + 2 * 4); // AttrValue Str Ind, or FFFFFFFF
                            int attrFlags = LEW(xml, off + 3 * 4);
                            int attrResId = LEW(xml, off + 4 * 4);  // AttrValue ResourceId or dup AttrValue StrInd
                            off += 5 * 4;  // Skip over the 5 words of an attribute

                            String attrName = compXmlString(xml, sitOff, stOff, attrNameSi);
                            String attrValue = attrValueSi != -1
                              ? compXmlString(xml, sitOff, stOff, attrValueSi)
                              : /*"resourceID 0x" + */attrResId.ToString();
                            sb += " " + attrName + "=\"" + attrValue + "\"";
                            //tr.add(attrName, attrValue);
                        }
                        prtIndent(indent, "<" + name + sb + ">");
                        indent++;

                    }
                    else if (tag0 == endTag)
                    { // XML END TAG
                        indent--;
                        off += 6 * 4;  // Skip over 6 words of endTag data
                        String name = compXmlString(xml, sitOff, stOff, nameSi);
                        prtIndent(indent, "</" + name + ">  \r\n"/*+"(line " + startTagLineNo + "-" + lineNo + ")"*/);
                        //tr.parent();  // Step back up the NobTree

                    }
                    else if (tag0 == endDocTag)
                    {  // END OF XML DOC TAG
                        break;

                    }
                    else
                    {
                        prt("  Unrecognized tag code '" + tag0.ToString("X")
                          + "' at offset " + off);
                        break;
                    }
                } // end of while loop scanning tags and attributes of XML tree
                //prt("    end at offset " + off);


                return result;
            } // end of decompressXML


            public String compXmlString(byte[] xml, int sitOff, int stOff, int strInd)
            {
                if (strInd < 0) return null;
                int strOff = stOff + LEW(xml, sitOff + strInd * 4);
                return compXmlStringAt(xml, strOff);
            }


            public static String spaces = "                                             ";
            public void prtIndent(int indent, String str)
            {
                prt(spaces.Substring(0, Math.Min(indent * 2, spaces.Length)) + str);
            }

            private void prt(string p)
            {
                result += p;
            }


            // compXmlStringAt -- Return the string stored in StringTable format at
            // offset strOff.  This offset points to the 16 bit string length, which 
            // is followed by that number of 16 bit (Unicode) chars.
            public String compXmlStringAt(byte[] arr, int strOff)
            {
                int strLen = arr[strOff + 1] << 8 & 0xff00 | arr[strOff] & 0xff;
                byte[] chars = new byte[strLen];
                for (int ii = 0; ii < strLen; ii++)
                {
                    chars[ii] = arr[strOff + 2 + ii * 2];
                }


                return System.Text.Encoding.UTF8.GetString(chars);  // Hack, just use 8 byte chars
            } // end of compXmlStringAt


            // LEW -- Return value of a Little Endian 32 bit word from the byte array
            //   at offset off.
            public int LEW(byte[] arr, int off)
            {
                return (int)(arr[off + 3] << 24 & 0xff000000 | arr[off + 2] << 16 & 0xff0000 | arr[off + 1] << 8 & 0xff00 | arr[off] & 0xFF);
            } // end of LEW

        }
    }
}
