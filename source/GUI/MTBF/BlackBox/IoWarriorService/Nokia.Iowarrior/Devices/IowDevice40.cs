using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

using Nokia.Iowarrior.Devices.IowKit;

namespace Nokia.Iowarrior.Devices
{
    internal class IowDevice40 : IowDeviceImplementation
    {
        // Constructors

        public IowDevice40(Int32 iowHandle): base(iowHandle)
        {
        }

        // Accessors, ToString

        /// <summary>
        /// Get string representation of this object.
        /// </summary>
        /// <returns>String containing information about this object instance.</returns>
        public override String ToString()
        {
            return this.GetType().Name
                    + "("
                    + "H=0x" + Handle.ToString("X")
                    + ", PID=0x" + ProductId.ToString("X")
                    + ", SN=" + SerialNumber
                    + ", In=" + ReadInputs()
                    + ", Out=" + LastOutputs
                    + ", Pins=" + LastOutputs
                    + ")";
        }

        // Set outputs / get inputs

        public override void WriteOutputs(IowBits bits)
        {
            Byte[] reportidBytes = new Byte[5];

            reportidBytes[0] = 0;
            for (Int32 d = 0; d < reportidBytes.Length - 1; d++)
            {
                reportidBytes[d + 1] = BitConverter.GetBytes(bits.Value)[d];
            }
            WriteToIowarriorPipe(0, reportidBytes);

            base.WriteOutputs(bits);
        }

	    public override IowBits ReadInputs()
        {
            SendSpecialReport(0xff, 0,0,0,0,0,0,0);
            Byte[] report = ReadSpecialReport();
            Int64 value = 0;

            for (int i = 7; i > 0; i--)
            {
                value = value * 256 + report[i];
            }

            return new IowBits(value);
        }

        // Still alive?

        public override Boolean CheckIsAlive()
        {
            return IowKitWrapper.GetIsAlive(Handle);
        }

        // IIC-related functions

        public override void EnableIic()
        {
            // See Iowarrior Data Sheet, Ch. 5.10.1, p. 13
            if (SendSpecialReport(0x01, 0x01, 0, 0, 0, 0, 0, 0))
                base.EnableIic();

            // Let Iowarrior and IIC devices settle down before continuing.
            Thread.Sleep(100);
        }

        public override void DisableIic()
        {
            // See Iowarrior Data Sheet, Ch. 5.10.1, p. 13
            if (SendSpecialReport(0x01, 0x00, 0, 0, 0, 0, 0, 0))
                base.DisableIic();

            // Let Iowarrior settle down
            Thread.Sleep(100);
        }

        /// <summary>
        /// Read bytes from IIC bus.
        /// </summary>
        /// <param name="command">Read command to be sent to IIC device.</param>
        /// <param name="count">Number of data bytes expected from IIC device.</param>
        /// <returns>Array of data bytes read from IIC device.</returns>
        public override Byte[] ReadIic(Byte command, Byte count)
        {
            if (SendSpecialReport(0x03, count, command, 0, 0, 0, 0, 0))
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
                    for (int i = 1; i <= (report[1] & 0x07); i++)
                        if (position < count)
                            read[position++] = report[1 + i];
                }

                return read;
            }
            return new Byte[count];
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
            Byte[] sendData = new Byte[6];
            Byte flags = 0;
            Int32 position = 0;
            Byte[] response;

            while (data.Length - position > 6)
            {
                flags = 0x06;               // 6 data bytes
                if (start) flags |= 0x80;	// start/stop flags

                for (int i = 0; i < 6; i++)
                    sendData[i] = data[position++];

                // See Iowarrior Data Sheet, Ch. 5.10.1, p. 13
                SendSpecialReport(0x02, flags, sendData[0], sendData[1], sendData[2], sendData[3], sendData[4], sendData[5]);
                response = ReadSpecialReport();			// get IIC response
                if (response[1] >= 128)
                    throw new InvalidOperationException("WriteIic: Error occurred.");

                // start has been sent
                start = false;
            }

            flags = (Byte)(data.Length - position);
            if (start) flags |= 0x80;
            if (stop) flags |= 0x40;

            for (int i = position; i < data.Length; i++)
                sendData[i - position] = data[i];

            // See Iowarrior Data Sheet, Ch. 5.10.1, p. 13
            SendSpecialReport(0x02, flags, sendData[0], sendData[1], sendData[2], sendData[3], sendData[4], sendData[5]);
            response = ReadSpecialReport();			// get IIC response
            if (response[1] >= 128)
                throw new InvalidOperationException("WriteIic: Error occurred.");

            return data.Length;
        }

        /// <summary>
        /// Write a command to IIC device with multiple data bytes.
        /// </summary>
        /// <param name="command">Command byte for the IIC device.</param>
        /// <param name="data">Parameter data of the command.</param>
        /// <returns>Number of bytes confirmed by IIC device. See Iowarrior and IIC device data sheet for more information.
        /// </returns>
        public override Int32 WriteIic(Byte command, Byte[] data)
        {
            if (data == null)
                throw new ArgumentNullException("data", "Must not be null.");

            if (data.Length == 0)
                return 0;

            Byte[] iicReport = new Byte[data.Length+1];
            iicReport[0] = command;
            for (int i = 0; i < data.Length; i++)
                iicReport[i + 1] = data[i];

            return WriteIicReport(iicReport, true, true);
        }

        // EEprom functions

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
                    sendData[i+1] = data[position++];

                WriteIic(chipAddress, sendData);
            }

            for (int i = position; i < data.Length; i++)
                sendData[i - position + 1] = data[i];

            sendData[0] = (Byte)(address + position);
            WriteIic(chipAddress, sendData);

            return data.Length;
        }

        public override Byte[] ReadEEpromBytes(Byte chipAddress, Byte address, Byte length)
        {
            for (int tries = 0; tries < 3; tries++)
            {
                try
                {
                    // Send Read command to EEprom
                    Byte[] iicReport = { chipAddress, address };
                    WriteIicReport(iicReport, true, true);

                    // Read data from EEprom
                    return ReadIic((Byte)(chipAddress | 0x01), length);
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

        // Basic Iowarrior IO
        /// <summary>
        /// Send Iowarrior IO report or Special report.
        /// </summary>
        /// <param name="numPipe">0: IO report, 1: Special report</param>
        /// <param name="data">IO report: 5 byte, Special report: 8 byte</param>
        private void WriteToIowarriorPipe(Byte numPipe, Byte[] data)
        {
            if (numPipe < 0 || numPipe > 2)
                throw new ArgumentOutOfRangeException("numPipe");

            int reportLength = (numPipe == 1 ? 8 : 5);

            if (data.Length > reportLength)
                throw new ArgumentOutOfRangeException("data", "Too many bytes to send.");
            if (Handle == 0)
                throw new ArgumentException("Cannot send report because the handle of the device is zero.");

            EnsureSafeTiming();

            int written = IowKitWrapper.Write(Handle, numPipe, ref data);

            if (written != data.Length)
                throw new InvalidOperationException("Could not send data to IoWarrior " + SerialNumber);
        }

        /// <summary>
        /// Read a report from given Iowarrior pipe, non-blocking version.
        /// </summary>
        /// <param name="numPipe">0: IO report (= IO pins), 1: Special report (= function).</param>
        /// <returns>Report read from Iowarrior. (IO report: 5 byte, Special report: 8 byte).</returns>
        private Byte[] ReadFromIowarriorPipe(Int32 numPipe)
        {
            Int32 reportLength = (numPipe == 1 ? 8 : 5);

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

        /// <summary>
        /// Wrapper function to WriteToIowarriorPipe. Sends always to port 1.
        /// Further information can be found in Iowarrior data sheet.
        /// Blocking.
        /// </summary>
        /// <param name="reportId"></param>
        /// <param name="d1"></param>
        /// <param name="d2"></param>
        /// <param name="d3"></param>
        /// <param name="d4"></param>
        /// <param name="d5"></param>
        /// <param name="d6"></param>
        /// <param name="d7"></param>
        private Boolean SendSpecialReport(Byte reportId, Byte d1, Byte d2, Byte d3, Byte d4, Byte d5, Byte d6, Byte d7)
        {
            Byte[] reportidBytes = { reportId, d1, d2, d3, d4, d5, d6, d7 };

            try
            {
                WriteToIowarriorPipe(1, reportidBytes);
                return true;
            } catch(InvalidOperationException)
            {
                return false;
            }
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

        public override void DisableSpi()
        {
            throw new InvalidOperationException("SPI interface not supported by Iowarrior40 device.");
        }

        public override void EnableSpi()
        {
            throw new InvalidOperationException("SPI interface not supported by Iowarrior40 device.");
        }

        public override void DisableLcd()
        {
            if (IsInSpecialModeLcd)
            {
                if (SendSpecialReport(0x04, 0, 0, 0, 0, 0, 0, 0)) // d1=0: LCD off, d2=0: single HD44780
                {
                    base.DisableLcd();
                }
            }
        }

        public override void EnableLcd()
        {
            if (IsInSpecialModeLcd)
            {
                if (SendSpecialReport(0x04, 0x01, 0, 0, 0, 0, 0, 0)) // d1=1: LCD on, d2=0: single HD44780
                {
                    base.EnableLcd();
                }
            }
        }

        public override void WriteSpiBytes(Byte[] bytes)
        {
            throw new InvalidOperationException("SPI interface not supported by Iowarrior40 device.");
        }

        public override int TranslatePortNameToBitNumber(String portName)
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
                    if (portNum < 0 || portNum > 3)
                        throw new ArgumentOutOfRangeException("portName", "Port number x in Px.y is out of range 0..3.");
                    if (portBit < 0 || portBit > 7)
                        throw new ArgumentOutOfRangeException("portName", "Port bit number y in Px.y is out of range 0..7.");

                    return portNum * 8 + portBit;
                default:
                    break;
            }

            throw new ArgumentException("Does not follow Px.y format.", "portName");
        }

        public override string TranslateBitNumberToPortName(Int32 bitNumber)
        {
            if (bitNumber < 0 || bitNumber > 31)
                throw new ArgumentOutOfRangeException("Invalid bit number for Iowarrior 40.", "bitNumber");
            return String.Format("P{0}.{1}", bitNumber / 8, bitNumber % 8);
        }

        private void WriteLcdCommand(Byte command)
        {
            SendSpecialReport(0x05, 0x01, command, 0, 0, 0, 0, 0);
        }

        public override void WriteLcdMemory(string text)
        {
            int guardTime = MinimumTimeBetweenAccesses;
            MinimumTimeBetweenAccesses = 0;

            WriteLcdCommand(0x80);

            text = text.PadRight(80, ' ');
            text = text.Substring(0, 80);

            Byte[] data = new Byte[6];
            data[0] = 0x80 + 5;

            for (int p = 0; p < 16; p++)
            {
                for (int i = 0; i < 5; i++)
                {
                    data[i + 1] = (Byte)text[p * 4 + i];
                }

                SendSpecialReport(0x05, 0x85, (Byte)text[p * 4], (Byte)text[p * 4 + 1], (Byte)text[p * 4 + 2], (Byte)text[p * 4 + 3], (Byte)text[p * 4 + 4], 0);
            }

            MinimumTimeBetweenAccesses = guardTime;
        }
    }
}
