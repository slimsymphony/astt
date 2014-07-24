using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Iowarrior.Devices
{
    internal class IowDeviceDummy : IowDeviceImplementation
    {
        public override void DisableIic()
        {
            base.DisableIic();
        }

        public override void EnableIic()
        {
            base.EnableIic();
        }

        public override void WriteOutputs(IowBits bits)
        {
            base.WriteOutputs(bits);
        }

        public override IowBits ReadInputs()
        {
            return new IowBits(0);
        }

        public override Byte[] ReadEEpromBytes(Byte chipAddress, Byte address, Byte length)
        {
            return new Byte[length];
        }

        public override Int32 WriteIic(Byte command, Byte[] data)
        {
            return 1;
        }

        public override Boolean CheckIsAlive()
        {
            return false;
        }

        public override Int32 WriteEEprom(Byte chipAddress, Byte address, Byte[] data)
        {
            return 1;
        }

        public override Byte[] ReadIic(Byte command, Byte length)
        {
            return new Byte[length];
        }

        public override void DisableSpi()
        {
            base.DisableSpi();
        }

        public override void EnableSpi()
        {
            base.EnableSpi();
        }

        public override void DisableLcd()
        {
            base.DisableLcd();
        }

        public override void EnableLcd()
        {
            base.EnableLcd();
        }

        public override void WriteSpiBytes(Byte[] bytes)
        {
            return;
        }

        public override int TranslatePortNameToBitNumber(string portName)
        {
            return 0;
        }

        public override string TranslateBitNumberToPortName(Int32 bitNumber)
        {
            return "P0.0";
        }

        public override void WriteLcdLines(string[] lines)
        {
            return;
        }

        public override void WriteLcdMemory(string text)
        {
            return;
        }
    }
}
