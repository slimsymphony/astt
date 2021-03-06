﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using System.IO;
using System.Threading;

namespace Nokia.Granite.Tracing.Decoding
{
    public class GraniteWbxmlDecoder
    {
        static void Main(string[] args)
        {
            //string xml = "<teststep name=\"'Verify keypad active state'\" timeout=\"9550\"><config background=\"no\" bitmap_capture=\"yes\" keypress_length=\"100\" keypress_wait=\"100\" max_isi_data_length=\"2048\"/><expect timeout=\"500\"><display><text screen=\"1\">Battery full. Save energy and remove charger from wall socket.</text></display><display><text screen=\"1\" valid=\"no\">Battery full. Save energy and remove charger from wall socket.</text></display></expect></teststep>";

            //byte[] bytes = new byte[] { 0x03, 0x20, 0x6a, 0x00, 0xc5, 0x12, 0x03, 0x27, 0x56, 0x65, 0x72, 0x69, 0x66, 0x79, 0x20, 0x6b, 0x65, 0x79, 0x70, 0x61, 0x64, 0x20, 0x61, 0x63, 0x74, 0x69, 0x76, 0x65, 0x20, 0x73, 0x74, 0x61, 0x74, 0x65, 0x27, 0x00, 0x09, 0x80, 0xca, 0x4e, 0x01, 0x93, 0x1d, 0x80, 0x64, 0x1c, 0x80, 0x90, 0x00, 0x1b, 0x85, 0x37, 0x86, 0x1e, 0x80, 0x64, 0x01, 0xcb, 0x09, 0x80, 0x83, 0x74, 0x01, 0x4c, 0xce, 0x1f, 0x80, 0x01, 0x01, 0x03, 0x42, 0x61, 0x74, 0x74, 0x65, 0x72, 0x79, 0x20, 0x66, 0x75, 0x6c, 0x6c, 0x2e, 0x20, 0x53, 0x61, 0x76, 0x65, 0x20, 0x65, 0x6e, 0x65, 0x72, 0x67, 0x79, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x72, 0x65, 0x6d, 0x6f, 0x76, 0x65, 0x20, 0x63, 0x68, 0x61, 0x72, 0x67, 0x65, 0x72, 0x20, 0x66, 0x72, 0x6f, 0x6d, 0x20, 0x77, 0x61, 0x6c, 0x6c, 0x20, 0x73, 0x6f, 0x63, 0x6b, 0x65, 0x74, 0x2e, 0x00, 0x01, 0x01, 0x4c, 0xce, 0x1f, 0x80, 0x01, 0x13, 0x86, 0x01, 0x03, 0x42, 0x61, 0x74, 0x74, 0x65, 0x72, 0x79, 0x20, 0x66, 0x75, 0x6c, 0x6c, 0x2e, 0x20, 0x53, 0x61, 0x76, 0x65, 0x20, 0x65, 0x6e, 0x65, 0x72, 0x67, 0x79, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x72, 0x65, 0x6d, 0x6f, 0x76, 0x65, 0x20, 0x63, 0x68, 0x61, 0x72, 0x67, 0x65, 0x72, 0x20, 0x66, 0x72, 0x6f, 0x6d, 0x20, 0x77, 0x61, 0x6c, 0x6c, 0x20, 0x73, 0x6f, 0x63, 0x6b, 0x65, 0x74, 0x2e, 0x00, 0x01, 0x01, 0x01, 0x01 };

            // take byte list from file
            List<Byte> bytes = new List<byte>();
            StreamReader wbxmlDataFile = new StreamReader("Z:\\granite_git\\granite\\gui\\wbxml_data.txt");
            //StreamReader wbxmlDataFile = new StreamReader("Z:\\granite_git\\granite\\framework\\wbxml_data.txt");

            string wbxmlDataFileContent = wbxmlDataFile.ReadToEnd();
            // get rid of unwanted chars
            wbxmlDataFileContent = wbxmlDataFileContent.Replace("[", "").Replace("]", "").Replace("'", "").Replace("\r", "").Replace("\n", "");

            // put string bytes to a list
            string[] bytesInData = wbxmlDataFileContent.Split(',');

            // convert strings to bytes and add them to list
            foreach (string byteString in bytesInData)
            {
                string tempString = byteString.Replace(" ", "");
                bytes.Add(Convert.ToByte(tempString, 16));
            }

            wbxmlDataFile.Close();

            {
                int loops = 10000;

                for (int i = 0; i < loops; i++)
                {
                    //GraniteWbxmlDocument doc = new GraniteWbxmlDocument();

                    //doc.LoadBytes(bytes.ToArray());
                    GraniteWbxmlDocument.Instance.Decode(bytes.ToArray(), ".", "", false, 0, 0);

                    //Console.WriteLine(GraniteWbxmlDocument.Instance.ResponseData.Count);

                    GraniteWbxmlDocument.Instance.ResponseData.Clear();

                    //Console.WriteLine(doc.ToString(true));
                    Thread.Sleep(100);
                }

            }
        }
    }
}
