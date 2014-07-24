using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Nokia.Iowarrior;
using System.Threading;

namespace Nokia.Iowarrior.Cards
{
    public class ADM1191
    {
        Byte adcWriteAddress = 0x00;
        Byte adcReadAddress = 0x00;
        String convertPin = "P0.0";

        const Double vFullScale = 6.65;
        const Double vFullScale2 = 26.52;
        const Double iFullScale = 105.84;//mV
        const Double senseResistor = 100;//Ohm

        IowDevice device;
        IowBits bits = new IowBits();
        Object thisLock = new Object();

        public ADM1191(IowDevice device, Byte adcAddress, String convertPin, Object lockObject)
        {
            this.device = device;
            this.thisLock = lockObject;
            this.convertPin = convertPin;
            adcWriteAddress = adcAddress;
            adcReadAddress = (Byte)(adcAddress + 1);
        }

        public PowerMeasurement ReadADCValue(Byte configuration)
        {
            lock (thisLock)
            {
                device.EnableIic();

                // Convert pin to trigger the result
                device.WriteOutput(device.TranslatePortNameToBitNumber(convertPin), true);

                device.WriteIic(adcWriteAddress, configuration);
                Thread.Sleep(1000);

                Byte[] value = device.ReadIic(adcReadAddress, 0x03);
                value = device.ReadIic(adcReadAddress, 0x03);

                device.DisableIic();

                Double voltage = (value[0] << 4) + (value[2] >> 4);
                Double current = (value[1] << 4) + (value[2] & 15);

                voltage = (vFullScale / 4096.0) * voltage;
                current = ((iFullScale / 4096.0) * current) / senseResistor;

                PowerMeasurement pM = new PowerMeasurement(voltage, current);

                return pM;
            }
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

        public String ConvertPin
        {
            get { return convertPin; }
            set { convertPin = value; }
        }
    }
}
