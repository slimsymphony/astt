using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Nokia.Iowarrior;

namespace Nokia.Iowarrior.Cards
{
    public class AD7995
    {
        Byte adcWriteAddress = 0x00;
        Byte adcReadAddress = 0x00;

        Object thisLock = new Object();
        IowDevice device;
        Double refVoltage = 4.5;


        public AD7995(IowDevice device, Byte adcAddress, Object lockObject)
        {
            this.device = device;
            this.thisLock = lockObject;

            adcWriteAddress = adcAddress;
            adcReadAddress = (Byte)(adcAddress + 1);
        }

        public Double ReadADCValue(Byte configuration)
        {
            Double result;

            lock (thisLock)
            {
                device.EnableIic();
                device.WriteIic(adcWriteAddress, configuration);
                //Thread.Sleep(timeAfterCofigurationChanged);
                // Read old measurement stored in A/D converter and trigger new conversion
                Byte[] value = device.ReadIic(adcReadAddress, 0x02);

                // 2Byte result: LSB=2 -> MSB=11
                result = ((value[0] & 15) << 6) + ((value[1] & 252) >> 2);

                result = refVoltage / 1023 * result;

                device.DisableIic();
            }
            return result;
        }

        public Double RefVoltage
        {
            get { return refVoltage; }
            set { refVoltage = value; }
        }


        public Byte AdcWriteAddress
        {
            get { return adcWriteAddress; }
            set { adcWriteAddress = value; }
        }

        public Byte AdcReadAddress
        {
            get { return adcReadAddress; }
            set { adcReadAddress = value; }
        }

    }
}
