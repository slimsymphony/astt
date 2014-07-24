// Disable "Missing XML comment for public type or member" warning.
// This file contains only code being accessed through an abstract interface class.
// The public methods are documented in this abstract interface class.
#pragma warning disable 1591

using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace Nokia.Iowarrior
{
    class JigDataHandler
    {        
        private const Byte jigDataAddress = 0x50;
        private const Byte jigDataLength = 0xAF;
        private const Byte jigInitializeDateAddress = 0x50;
        private const Byte jigLastAccessDateAddress = 0x54;
        private const Byte jigIDAddress = 0x58;
        private const Byte jigCounterAddress = 0x5C;
        private const Byte jigProductAddress = 0x60;

        private const Int32 jigInitializeDateIndex = 0;
        private const Int32 jigLastAccessDateIndex = 4;
        private const Int32 jigIdIndex = 8;
        private const Int32 jigCountIndex = 12;
        private const Int32 jigProductIndex = 16;
        
        private Byte[] data;
        private Byte jigAddress;
        private IowDevice device;
                
        public JigDataHandler(IowDevice device, Byte jigAddress)
        {
            this.device = device;
            this.jigAddress = jigAddress;
        }

        public void ReadDataFromJig()
        {
            device.EnableIic(); 
            data = device.ReadEEpromBytes(jigAddress, jigDataAddress, jigDataLength);
            device.DisableIic();
        }        

        public DateTime InitializeTime
        {
            get 
            {
                Byte[] content = new Byte[4];
                Array.Copy(data, jigInitializeDateIndex, content, 0, 4); 
                return IowUtil.DateBytesToDateTime(content);
            }
        }

        public DateTime LastAccess
        {
            get 
            {
                Byte[] content = new Byte[4];
                Array.Copy(data, jigLastAccessDateIndex, content, 0, 4); 
                return IowUtil.DateBytesToDateTime(content);
            }
        }

        public Int32 Id
        {
            get 
            {
                Byte[] content = new Byte[4];
                Array.Copy(data, jigIdIndex, content, 0, 4); 
                return BitConverter.ToInt32(content, 0);
            }
        }

        public Int32 Count
        {
            get 
            {
                Byte[] content = new Byte[4];
                Array.Copy(data, jigCountIndex, content, 0, 4); 
                return BitConverter.ToInt32(content, 0);
            }
        }

        public String Product
        {
            get 
            {
                 Int32 length = (Int32)data[jigProductIndex];
                 Byte[] content = new Byte[length];
                 Array.Copy(data, jigProductIndex, content, 0, length);
                 return IowUtil.ConvertByteArrayToString(content);
            }
        }  
        
        public void WriteInitializeDate(DateTime date)
        {
            device.EnableIic(); 
            device.WriteEEprom(jigAddress, jigInitializeDateAddress, IowUtil.DateTimeToDateBytes(date));
            device.DisableIic();
        }

        public void WriteLastAccessDate(DateTime date)
        {
            device.EnableIic(); 
            device.WriteEEprom(jigAddress, jigLastAccessDateAddress, IowUtil.DateTimeToDateBytes(date));
            device.DisableIic();
        }

        public void WriteId(Int32 id)
        {
            device.EnableIic(); 
            device.WriteEEprom(jigAddress, jigIDAddress, BitConverter.GetBytes(id));
            device.DisableIic();
        }

        public void WriteCount(Int32 count)
        {
            device.EnableIic();
            device.WriteEEprom(jigAddress, jigCounterAddress, BitConverter.GetBytes(count));
            device.DisableIic();
        }

        public void WriteProduct(String product)
        {
            device.EnableIic(); 
            device.WriteEEprom(jigAddress, jigProductAddress, IowUtil.ConvertStringToByteArray(product));
            device.DisableIic();
        }

        public void WriteJigInitialData(Int32 jigId, String product)
        {
            WriteInitializeDate(DateTime.Now);
            WriteLastAccessDate(DateTime.Now);
            WriteId(jigId);
            WriteCount(0);
            WriteProduct(product);
        }

        public void UpdateJigAccessCounter()
        {
            ReadDataFromJig();
            WriteLastAccessDate(DateTime.Now);

            Byte[] content = new Byte[4];
            Array.Copy(data, jigCountIndex, content, 0, 4);
            Int32 count = BitConverter.ToInt32(content, 0);
            count++;             
            WriteCount(count);
        }

        public override String ToString()
        {
            return 
                "Product: " + Product + Environment.NewLine +
                "ID: " + Id.ToString() + Environment.NewLine +
                "Counter: " + Count.ToString() + Environment.NewLine +
                "Last Acces Date: " + LastAccess.ToString() + Environment.NewLine +
                "Init Date: " + InitializeTime.ToString();
            
        }
    }
}
