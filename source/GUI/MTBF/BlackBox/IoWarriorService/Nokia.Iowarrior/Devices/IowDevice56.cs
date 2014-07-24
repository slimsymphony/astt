using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

using Nokia.Iowarrior.Devices.IowKit;

namespace Nokia.Iowarrior.Devices
{
    internal class IowDevice56 : IowDeviceImplementation
    {        
        // Constructors
        public IowDevice56(Int32 iowHandle): base(iowHandle)
        {         
        }

        public override void DisableIic()
        {
            if (IsInSpecialModeIic)
            {
                Byte[] report = new Byte[63];
                report[0] = 0x00;                   // mode: IIC off
                report[1] = 0x01;                   // speed: 400kHz
                SendSpecialReport(0x01, report);
                base.DisableIic();
            }
        }

        public override void EnableIic()
        {
            if (!IsInSpecialModeIic)
            {
                Byte[] report = new Byte[63];
                report[0] = 0x01;                   // mode: IIC on
                report[1] = 0x01;                   // speed: 400kHz
                SendSpecialReport(0x01, report);
                base.EnableIic();
            }
        }

        public override IowBits ReadInputs()
        {
            SendSpecialReport(0xff, new Byte[63]);
            Byte[] report = ReadSpecialReport();
            Int64 value = 0;

            for (int i = 7; i > 0; i--)
            {
                value = value * 256 + report[i];
            }

            return new IowBits(value);
        }

        public override void WriteOutputs(IowBits bits)
        {
            Byte[] reportidBytes = new Byte[8];

            // According to Iow56 data sheet, bits 49..54 shall always be "1".

            for (int i = 49; i < 55; i++)
                bits[i] = true;

            reportidBytes[0] = 0;
            for (Int32 d = 0; d < reportidBytes.Length - 1; d++)
            {
                reportidBytes[d + 1] = BitConverter.GetBytes(bits.Value)[d];
            }
            WriteToIowarriorPipe(0, reportidBytes);

            base.WriteOutputs(bits);
        }

        public override Byte[] ReadEEpromBytes(Byte chipAddress, Byte address, Byte length)
        {
            for (int tries = 0; tries < 3; tries++)
            {
                try
                {
                    // Send Read command to EEprom
                    Byte[] iicReport = { chipAddress, address };
                    WriteIicReport(iicReport, true, false);

                    // Read data from EEprom
                    Byte[] x =  ReadIic((Byte)(chipAddress | 0x01), length);
                    return x;
                }
                catch (InvalidOperationException e)
                {
                    if (!e.Message.Contains("Iic"))
                        throw;
                    Thread.Sleep(100);
                }
            }

            return new Byte[0];
        }

        public override Int32 WriteEEprom(Byte chipAddress, Byte address, Byte[] data)
        {
            Byte[] sendData = new Byte[5];
            Int32 position = 0;

            // EEPROM supports multi-byte write with up to 4 bytes in a single write command.
            // Make sure that two write accesses do not follow quicker than 20 ms,
            // i.e. EnsureSafeTiming() should not be lower than 20ms.
            while (data.Length - position > 4)
            {
                sendData[0] = (Byte)(address + position);
                for (int i = 0; i < 4; i++)
                    sendData[i + 1] = data[position++];

                WriteIic(chipAddress, sendData);
                Thread.Sleep(20);               // Wait for EEprom to finish writing
            }

            for (int i = position; i < data.Length; i++)
                sendData[i - position + 1] = data[i];

            sendData[0] = (Byte)(address + position);
            WriteIic(chipAddress, sendData);

            return data.Length;
        }

        /// <summary>
        /// Write data to IIC bus.
        /// </summary>
        /// <param name="data">Array of bytes to send to IIC device.</param>
        /// <param name="start">True, if start condition to be set before start of sending.</param>
        /// <param name="stop">True, if stop condition to be set after sending.</param>
        /// <returns>Returns data.Length if sending was successful.</returns>
        private Int32 WriteIicReport(Byte[] data, Boolean start, Boolean stop)
        {
            Byte[] sendData = new Byte[63];
            Byte flags = 0;
            Int32 position = 0;
            Byte[] response;

            while (data.Length - position > 62)
            {
                flags = 0x06;               // 6 data bytes
                if (start) flags |= 0x80;	// start/stop flags

                sendData[0] = flags;
                for (int i = 1; i < 64; i++)
                    sendData[i] = data[position++];

                // See Iowarrior Data Sheet, Ch. 5.10.1, p. 13
                SendSpecialReport(0x02, sendData);
                Thread.Sleep(20);                   // Wait for IIC devices
                response = ReadSpecialReport();			// get IIC response
                if (response[1] >= 128)
                    throw new InvalidOperationException("WriteIic: Error occurred.");

                // start has been sent
                start = false;
            }

            flags = (Byte)(data.Length - position);
            if (start) flags |= 0x80;
            if (stop) flags |= 0x40;

            sendData[0] = flags;
            for (int i = position; i < data.Length; i++)
                sendData[1 + i - position] = data[i];

            // See Iowarrior Data Sheet, Ch. 5.10.1, p. 13
            SendSpecialReport(0x02, sendData);
            Thread.Sleep(20);                   // Wait for IIC devices
            response = ReadSpecialReport();			// get IIC response
            if (response[1] >= 128)
                throw new InvalidOperationException("WriteIic: Error occurred.");

            return data.Length;
        }

        public override Int32 WriteIic(Byte command, Byte[] data)
        {
            if (data == null)
                throw new ArgumentNullException("data", "Must not be null.");

            if (data.Length == 0)
                return 0;

            Byte[] iicReport = new Byte[data.Length + 1];
            iicReport[0] = command;
            for (int i = 0; i < data.Length; i++)
                iicReport[i + 1] = data[i];

            return WriteIicReport(iicReport, true, true);
        }

        public override Byte[] ReadIic(Byte command, Byte count)
        {
            if (SendSpecialReport(0x03, new Byte[] { count, command, 0, 0, 0, 0, 0 } ))
            {
                Byte[] read = new Byte[count];
                Byte position = 0;

                // Allow the IIC device to handle the request
                EnsureSafeTiming(20);

                while (position < count)
                {
                    Byte[] report = ReadSpecialReport();
                    if (report[1] >= 128)
                        throw new InvalidOperationException("ReadIic: Error occurred.");
                    for (int i = 1; i <= (report[1] & 0x7f); i++)
                        if (position < count)
                            read[position++] = report[1 + i];
                }

                return read;
            }
            return new Byte[count];
        }

        public override Boolean CheckIsAlive()
        {
            if (SendSpecialReport(0xff, new Byte[63]))
            {
                ReadSpecialReport();
                return true;
            }

            return false;
        }

        /// <summary>
        /// Wrapper function to WriteToIowarriorPipe. Sends always to port 1.
        /// Further information can be found in Iowarrior data sheet.
        /// Blocking.
        /// </summary>
        /// <param name="reportId"></param>
        /// <param name="data"></param>
        private Boolean SendSpecialReport(Byte reportId, Byte[] data)
        {
            if (data.Length > 63)
                throw new ArgumentException("Too many data to send.");

            Byte[] reportIdBytes = new Byte[64];

            reportIdBytes[0] = reportId;

            for (int i = 0; i < data.Length; i++)
            {
                reportIdBytes[i + 1] = data[i];
            }

            try
            {
                WriteToIowarriorPipe(1, reportIdBytes);
                return true;
            }
            catch (InvalidOperationException)
            {
                return false;
            }
        }

        // Basic Iowarrior IO
        /// <summary>
        /// Send Iowarrior IO report or Special report.
        /// </summary>
        /// <param name="numPipe">0: IO report, 1: Special report</param>
        /// <param name="data">IO report: 64 byte, Special report: 8 byte</param>
        private void WriteToIowarriorPipe(Byte numPipe, Byte[] data)
        {
            if (numPipe < 0 || numPipe > 1)
                throw new ArgumentOutOfRangeException("numPipe");

            int reportLength = (numPipe == 0 ? 8 : 64);

            if (data.Length > reportLength)
                throw new ArgumentOutOfRangeException("data", "Too many bytes to send.");
            if (Handle == 0)
                throw new ArgumentException("Cannot send report because the handle of the device is zero.");

            EnsureSafeTiming(MinimumTimeBetweenAccesses);
            int written = IowKitWrapper.Write(Handle, numPipe, ref data);
            if (written != data.Length)
                throw new InvalidOperationException("Could not send data to IoWarrior " + SerialNumber);
        }

        /// <summary>
        /// Wrapper function to ReadFromIowarriorPipe. Reads always from port 1.
        /// Further information can be found in Iowarrior data sheet.
        /// Blocking.
        /// </summary>
        /// <returns>Special report read from Iowarrior.</returns>
        private Byte[] ReadSpecialReport()
        {
            return ReadFromIowarriorPipe(1);
        }

        /// <summary>
        /// Read a report from given Iowarrior pipe, non-blocking version.
        /// </summary>
        /// <param name="numPipe">0: IO report (= IO pins), 1: Special report (= function).</param>
        /// <returns>Report read from Iowarrior. (IO report: 8 byte, Special report: 64 byte).</returns>
        private Byte[] ReadFromIowarriorPipe(Int32 numPipe)
        {
            Int32 reportLength = (numPipe == 0 ? 8 : 64);

            Byte[] report = new Byte[reportLength];

            EnsureSafeTiming(MinimumTimeBetweenAccesses);

            Int32 count = IowKitWrapper.ReadNonBlocking(Handle, numPipe, ref report);

            // Some data read => empty the buffer in IowKit DLL only when reading I/O pins
            if (numPipe == 0 && count != 0)
            {
                while (IowKitWrapper.ReadNonBlocking(Handle, numPipe, ref report) != 0)
                {
                    // simply read until no more values are read.
                }
            }
            else
            {
                if (count != report.Length)
                    throw new InvalidOperationException("ReadFromIowarriorPipe: Error reading from Iowarrior device.");
            }

            return report;
        }

        public override void DisableSpi()
        {
            if (IsInSpecialModeSpi)
            {
                Byte[] report = new Byte[63];
                report[0] = 0x00;                   // enable: SPI off
                report[1] = 0x00;                   // mode: CPOL=0 (CLK idle Low), CPHA=0 (Send data on second edge), LSBFirst=0
                report[2] = 1;                     // clock: 24MHz / (1 + 1)
                SendSpecialReport(0x08, report);
                base.DisableSpi();
            }
        }

        public override void EnableSpi()
        {
            if (!IsInSpecialModeSpi)
            {
                Byte[] report = new Byte[63];
                report[0] = 0x01;                   // enable: SPI on
                report[1] = 0x00;                   // mode: CPOL=0 (CLK idle Low), CPHA=0 (Send data on second edge), LSBFirst=0
                report[2] = 1;                      // clock: 24MHz / (1 + 1)
                SendSpecialReport(0x08, report);
                base.EnableSpi();
            }
        }

        public override void DisableLcd()
        {
            if (IsInSpecialModeLcd)
            {
                Byte[] report = new Byte[63];
                report[0] = 0x00;                  // enable: LCD off
                report[1] = 0x00;                  // mode: 0 = single HD44780 compatible mode
                SendSpecialReport(0x04, report);

                WriteLcdCommand(0x08);             // Display off, cursor off

                base.DisableLcd();
            }
        }

        public override void EnableLcd()
        {
            if (!IsInSpecialModeLcd)
            {
                Byte[] report = new Byte[63];
                report[0] = 0x01;                  // enable: LCD on
                report[1] = 0x00;                  // mode: 0 = single HD44780 compatible mode
                SendSpecialReport(0x04, report);

                // Display on, cursor off, cursor home, clear contents
                // TODO: Commands taken from sample code - check with data sheet
                WriteLcdCommand(0x38);
                WriteLcdCommand(0x01);
                WriteLcdCommand(0x0C);

                base.EnableLcd();
            }
        }

        public override void WriteSpiBytes(Byte[] bytes)
        {
            if (bytes.Length > 61)
                throw new ArgumentOutOfRangeException("bytes", "At most 61 data bytes can be sent.");

            Byte[] report = new Byte[63];   
            report[0] = (Byte)bytes.Length;         // count: amount of data bytes to send
            report[1] = 0x20;                       // flags: useDRDY=0, SSactive=0, ignoreDRDY=1

            for (int i = 0; i < bytes.Length; i++)
                report[2 + i] = bytes[i];

            SendSpecialReport(0x09, report);        // send bytes without reading in the incoming bytes
        }

        public override int TranslatePortNameToBitNumber(string portName)
        {
            if (String.IsNullOrEmpty(portName))
                throw new ArgumentException("Is null or empty.", "portName");

            switch (portName[0])
            {
                case 'P':
                case 'p':
                    Int32 portNum = -1;
                    Int32 portBit = -1;
                    String[] args = portName.Substring(1).Split('.');
                    if (args.Length != 2)
                        break;
                    Int32.TryParse(args[0], out portNum);
                    Int32.TryParse(args[1], out portBit);
                    if (portNum < 0 || portBit < 0)
                        break;
                    if (portNum < 0 || portNum > 6)
                        throw new ArgumentOutOfRangeException("portName", "Port number x in Px.y is out of range 0..6.");
                    if (portBit < 0 || portBit > 7)
                        throw new ArgumentOutOfRangeException("portName", "Port bit number y in Px.y is out of range 0..7.");
                    if (portNum == 6)
                    {
                        if (portBit > 0 && portBit < 7)
                            throw new ArgumentOutOfRangeException("portName", "On port 6 only P6.0 and P6.7 are supported.");
                    }
                    return portNum * 8 + portBit;
                default:
                    break;
            }

            throw new ArgumentException("Does not follow Px.y format.", "portName");
        }

        public override string TranslateBitNumberToPortName(Int32 bitNumber)
        {
            switch (bitNumber)
            {
                case 55:
                    return "P6.7";
                default:
                    if (bitNumber < 0 || bitNumber > 47)
                        throw new ArgumentOutOfRangeException("Invalid bit number for Iowarrior 56.", "bitNumber");
                    return String.Format("P{0}.{1}", bitNumber / 8, bitNumber % 8);
            }
        }

        private void WriteLcdCommand(Byte command)
        {
            Byte[] lcdPacket = new Byte[63];
            lcdPacket[0] = 1;
            lcdPacket[1] = command;
            SendSpecialReport(0x05, lcdPacket);
        }

        public override void WriteLcdMemory(string text)
        {
            int guardTime = MinimumTimeBetweenAccesses;
            MinimumTimeBetweenAccesses = 0;

            WriteLcdCommand(0x80);

            text = text.PadRight(80, ' ');
            text = text.Substring(0, 80);

            Byte[] data = new Byte[17];
            data[0] = 0x80 + 16;

            for (int p = 0; p < 5; p++)
            {
                for (int i = 0; i < 16; i++)
                {
                    data[i + 1] = (Byte)text[p*16+i];
                }

                SendSpecialReport(0x05, data);
            }

            MinimumTimeBetweenAccesses = guardTime;
        }
    }
}
