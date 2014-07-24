using System;
using System.Text;
using Nokia.Iowarrior.Devices;
using Nokia.Iowarrior.Devices.IowKit;


// IMPORTANT:
// COMPATIBILITY ISSUE: THIS CODE IS TESTED AND OK WITH WITH IOWKIT.DLL version 1.4!
// IT SHOULD WORK WITH IOWKIT.DLL version 1.3, BUT HAS NOT BEEN TESTED WITH IT.
// IT WORKS WITH IOWKIT.DLL version 1.5, BUT THIS DLL SHOWS SOME BAD TIMING BEHAVIOUR!
// CHECK THAT YOU USE IOWKIT.DLL version 1.4!
// ReadReportNonBlocking() method is NOT available in IOWKIT.DLL 1.4 and below!

[assembly:CLSCompliant(true)]
namespace Nokia.Iowarrior
{
    /// <summary>
    /// Enum of supported Iowarrior Product Id values.
    /// </summary>
    public enum ProductId
    {
        /// Unknown Iowarrior device type.
        Unknown = 0,
        /// Iowarrior40 device type, Id=0x1500.
        Iowarrior40 = 0x1500,
        /// Iowarrior40 device type, Id=0x1503.
        Iowarrior56 = 0x1503
    }

    /// <summary>
    /// This class provides methods to access the features of a single Iowarrior device.
    /// Supported Iowarrior chip types are defined in <typeparamref name="ProductId"/> enum.
    /// IowDevice class can be remoted.
    /// </summary>
    public class IowDevice
    {
        IowDeviceImplementation implementation;
        private IowKitWrapper _iowKitWrapper = new IowKitWrapper();

        /// <summary>
        /// Internal constructor. Not intended to be called by user code. Only used for remoting.
        /// </summary>
        public IowDevice()
        {
            implementation = IowDeviceImplementation.Create();
        }

        /// <summary>
        /// Get IowKitWrapper object used to communicate with the physical Iowarrior device.
        /// </summary>
        public IowKitWrapper IowKitWrapper
        {
            get { return _iowKitWrapper; }
        }

        /// <summary>
        /// Get Product Id of this Iowarrior device.
        /// </summary>
        public ProductId ProductId
        {
            get { return implementation.ProductId; }
        }

        /// <summary>
        /// Get/set the minimum time span [ms] between two consecutive accesses to this device.
        /// Default value: 50ms. Minimum value: 10ms. Values between below 10ms will be changed internally to 10ms.
        /// </summary>
        public Int32 MinimumTimeBetweenAccesses
        {
            get { return implementation.MinimumTimeBetweenAccesses; }
            set { implementation.MinimumTimeBetweenAccesses = value; }
        }

        /// <summary>
        /// Internal constructor. Not intended to be called by user code.
        /// </summary>
        /// <param name="iowHandle"></param>
        public IowDevice(Int32 iowHandle)
        {
            implementation = IowDeviceImplementation.Create(iowHandle);
        }

        /// <summary>
        /// Get the serial number used by this object to access Iowarrior device.
        /// </summary>
        public String SerialNumber
        {
            get { return implementation.SerialNumber; }
        }

        /// <summary>
        /// Get the last value written to the output pins.
        /// </summary>
        public IowBits LastOutputs
        {
            get { return implementation.LastOutputs; }
        }

        /// <summary>
        /// Get the status of IIC in Iowarrior device. True: IIC is on. False: IIC is off.
        /// </summary>
        public Boolean IsInSpecialModeIic
        {
            get { return implementation.IsInSpecialModeIic; }
        }

        /// <summary>
        /// Get the status of SPI in Iowarrior device. True: SPI is on. False: SPI is off.
        /// </summary>
        public Boolean IsInSpecialModeSpi
        {
            get { return implementation.IsInSpecialModeSpi; }
        }

        /// <summary>
        /// Return connection status of IowDevices IowKitUnsafeNativeMethods.
        /// </summary>
        public Boolean IsOpen
        {
            get { return implementation.IsOpen; }
        }

        /// <summary>
        /// Close all Iowarrior devices. Make sure that this is called when IowCards are not needed any more in the application.
        /// Not doing so might cause problems with device driver DLL.
        /// </summary>
        public void CloseAll()
        {
            IowKitWrapper.CloseAll();
        }

        /// <summary>
        /// Open all Iowarrior devices. Make sure that this is called when IowCards are not needed any more in the application.
        /// Not doing so might cause problems with device driver DLL.
        /// </summary>
        /// <returns>Number of Iowarrior devices.</returns>
        public Int32 OpenAll()
        {
            return IowKitWrapper.OpenAll();
        }

        /// <summary>
        /// Computes the bit number from a given port name ("Px.y").
        /// </summary>
        /// <param name="portName">Port name "Px.y" of Iowarrior device.</param>
        /// <returns>Bit position usable e.g. for WriteOutput() or ReadInput() methods.</returns>
        /// <exception cref="ArgumentOutOfRangeException">In case the portName is not valid for this Iowarrior device instance.</exception>
        public Int32 TranslatePortNameToBitNumber(String portName)
        {
            return implementation.TranslatePortNameToBitNumber(portName);
        }

        /// <summary>
        /// Computes the port name ("Px.y") from the bit number as used in WriteOutput() or ReadInput() methods.
        /// </summary>
        /// <param name="bitNumber">Bit number (0..31/56), depending on Iowdevice.</param>
        /// <returns>Name of the port ("Px.y").</returns>
        /// <exception cref="ArgumentOutOfRangeException">In case the bitNumber is outside the values supported by this Iowarrior device instance.</exception>
        public String TranslateBitNumberToPortName(Int32 bitNumber)
        {
            return implementation.TranslateBitNumberToPortName(bitNumber);
        }

        /// <summary>
        /// Set all output pins of the Iowarrior at the same time.
        /// Be aware that special mode functions like IIC, LCD and SPI use some I/O pins which will become unusable for WriteOutputs() if those
        /// functions are activated.
        /// </summary>
        /// <param name="bits">IowBits containing the bit pattern to be sent to output pins.</param>
        public virtual void WriteOutputs(IowBits bits)
        {
            implementation.WriteOutputs(bits);
        }

        /// <summary>
        /// Set a given bit of the Iowarrior to the desired state. Bit #0 is P0.0, bit #31 is P3.7,
        /// bit #55 is P6.7.
        /// Caution: Bits 49..54 on Iowarrior56 are not usable and always set to "1".
        /// Be aware that special mode functions like IIC, LCD and SPI use some I/O pins which will become unusable for WriteOutput() if those
        /// functions are activated.
        /// </summary>
        /// <param name="bitNumber">Bit number [0..31/55].</param>
        /// <param name="state">True or false.</param>
        public void WriteOutput(Int32 bitNumber, Boolean state)
        {
            IowBits bv = LastOutputs;
            bv[bitNumber] = state;
            WriteOutputs(bv);
        }

        /// <summary>
        /// Read real input values from Iowarrior input pins.
        /// Take care that only pins set to "true" using WriteOutput() or WriteOutputs() can be used as input.
        /// Be aware that special mode functions like IIC, LCD and SPI use some I/O pins which will become unusable if those
        /// functions are activated.
        /// Those pins return "false" when being read while the special function is on.
        /// </summary>
        /// <returns>Bit pattern as seen by the Iowarrior input pins.</returns>
        public IowBits ReadInputs()
        {
            return implementation.ReadInputs();
        }

        /// <summary>
        /// Read the status of a certain input pin.
        /// Be aware that special mode functions like IIC, LCD and SPI use some I/O pins which will become unusable if those
        /// functions are activated.
        /// Those pins return "false" when being read while the special function is on.
        /// </summary>
        /// <param name="bitNumber">Bit number [0..31].</param>
        /// <returns>State of the input pin.</returns>
        public Boolean ReadInput(Int32 bitNumber)
        {
            return ReadInputs()[bitNumber];
        }

        /// <summary>
        /// Turn off IIC support.
        /// Caution: This might cause some glitches on the IIC pins which could have effect on the connected hardware.
        /// Use this function only when absolutely needed.
        /// Look into Iowarrior data sheet to see which pins are affected.
        /// </summary>
        public void DisableIic()
        {
            implementation.DisableIic();
        }

        /// <summary>
        /// Turn on IIC support. Make sure you do this before any further IIC operation.
        /// IIC read operation will block, if IIC was not turned on.
        /// See Iowarrior data sheet for pinout and side effects to IO pins.
        /// </summary>
        public void EnableIic()
        {
            implementation.EnableIic();
        }

        /// <summary>
        /// Turn off Iowarrior SPI support.
        /// Be aware that this is only supported on Iowarrior56 devices. Calling this on any other real device
        /// will result in an exception.
        /// </summary>
        public void DisableSpi()
        {
            implementation.DisableIic();
        }

        /// <summary>
        /// Turn on SPI support.
        /// Be aware that this is only supported on Iowarrior56 devices. Calling this on any other real device
        /// will  result in an exception.
        /// </summary>
        public void EnableSpi()
        {
            implementation.EnableSpi();
        }

        /// <summary>
        /// Turn off LCD support.
        /// </summary>
        public void DisableLcd()
        {
            implementation.DisableLcd();
        }

        /// <summary>
        /// Turn on LCD support. Supports only single-controller
        /// HD44780-compatible alphanumeric displays.
        /// </summary>
        public void EnableLcd()
        {
            implementation.EnableLcd();
        }

        /// <summary>
        /// Copies the text 1:1 into LCD memory. The user application has to
        /// take care to format the string properly for the given LCD layout.
        /// See your LCD data sheet for more information.
        /// </summary>
        /// <param name="text">Text to be displayed on LCD.</param>
        public void WriteLcdMemory(String text)
        {
            implementation.WriteLcdMemory(text);
        }

        /// <summary>
        /// Shows the given lines on the display. The only supported display layout
        /// is 20x4 characters. The complete content of the display is overwritten with
        /// the contents of lines array top-to-bottom until either the array length has been
        /// reached or 4 lines have been put on display. Depending on the length of a 
        /// line's content it will be either cut after 20 characters or padded with blanks
        /// on the right side.
        /// </summary>
        /// <param name="lines">String array with lines to display.</param>
        public void WriteLcdLines(String[] lines)
        {
            implementation.WriteLcdLines(lines);
        }

        /// <summary>
        /// Read the specified number of bytes from EEprom (chip address hard coded to 0xA0)
        /// starting at given address.
        /// Read operation is converted into single-byte read operations. Thus, the time required
        /// directly depends on the number of data to read.
        /// Address overflow is neither checked nor handled!
        /// </summary>
        /// <param name="address">Start address in EEprom to read from.</param>
        /// <param name="count">Amount of data to read.</param>
        /// <returns>Array of data bytes read from the EEprom.</returns>
        public Byte[] ReadEEpromBytes(Byte address, Byte count)
        {
            return implementation.ReadEEpromBytes(0xA0, address, count);
        }

        /// <summary>
        /// Reads bytes from EEprom like ReadEEpromBytes(Byte address, Byte count).
        /// But this method also allows to address the chip by the caller.
        /// </summary>
        /// <param name="chipAddress">Address of the EEprom chip. Valid addresses are 0xA0, 0xA2, 0xA4, 0xA6, 0xA8, 0xAA, 0xAC, 0xAE.</param>
        /// <param name="address">Start address in EEprom to read from.</param>
        /// <param name="count">Amount of data to read.</param>
        /// <returns>Array of data bytes read from the EEprom.</returns>
        public Byte[] ReadEEpromBytes(Byte chipAddress, Byte address, Byte count)
        {
            return implementation.ReadEEpromBytes(chipAddress, address, count);
        }

        /// <summary>
        /// Write a command to IIC device with multiple data bytes.
        /// </summary>
        /// <param name="command">Command byte for the IIC device.</param>
        /// <param name="data">Parameter data of the command.</param>
        /// <returns>Number of bytes confirmed by IIC device. See Iowarrior and IIC device data sheet for more information.
        /// </returns>
        public Int32 WriteIic(Byte command, Byte[] data)
        {
            return implementation.WriteIic(command, data);
        }

        /// <summary>
        /// Read count bytes from IIC device addressed by command.
        /// </summary>
        /// <param name="command">The command byte written on IIC bus to address the device.</param>
        /// <param name="count">Number of bytes expected to read after the command byte has been sent.</param>
        /// <returns>Byte array with the read values.</returns>
        public Byte[] ReadIic(Byte command, Byte count)
        {
            return implementation.ReadIic(command, count);
        }

        /// <summary>
        /// Write a single command with a single data byte to the IIC bus.
        /// </summary>
        /// <param name="command">Command byte.</param>
        /// <param name="data">Data byte.</param>
        /// <returns>Number of bytes confirmed by IIC device. See Iowarrior and IIC device data sheet for more information.
        /// </returns>
        public Int32 WriteIic(Byte command, Byte data)
        {
            return WriteIic(command, new Byte[] { data });
        }

        /// <summary>
        /// Write the arrays to SPI interface. This is only supported on Iowarrior56 devices. Calling it on any other
        /// real device will result in an exception.
        /// </summary>
        /// <param name="bytes">Data bytes to send.</param>
        public void WriteSpiBytes(Byte[] bytes)
        {
            implementation.WriteSpiBytes(bytes);
        }
        
        /// <summary>
        /// Checks whether the Iowarrior device is accessible.
        /// </summary>
        /// <returns>True, if the Iowarrior is still alive.</returns>
        public Boolean CheckIsAlive()
        {
            return implementation.CheckIsAlive();
        }

        /// <summary>
        /// Read a single byte from the IIC EEPROM.
        /// </summary>
        /// <param name="address">Address to read from.</param>
        /// <returns>Data byte stored in the EEPROM at the given address.</returns>
        public Byte ReadEEpromByte(Byte address)
        {
            return ReadEEpromBytes(address, 1)[0];
        }

        /// <summary>
        /// Read an Int32 value from EEPROM starting at the given address.
        /// Address overflow is neither checked nor handled.
        /// </summary>
        /// <param name="address">Start address of Int32 value in the EEPROM.</param>
        /// <returns>Int32 value read from EEPROM.</returns>
        public Int32 ReadEEpromInt32(Byte address)
        {
            Byte[] intValue = ReadEEpromBytes(address, 4);

            return BitConverter.ToInt32(intValue, 0);
        }

        /// <summary>
        /// Read a string from the EEPROM starting at the given address.
        /// The address must point to the length byte of the string. The string is stored PASCAL-style, i.e. it has a length byte first, followed by string data.
        /// Read operation is split into single-byte-read operations. Thus the time required is directly
        /// dependent on the string length.
        /// Address overflow is neither checked nor handled.
        /// </summary>
        /// <param name="address">Starting address of the string (must point to length byte).</param>
        /// <returns>String read from the EEPROM.</returns>
        public String ReadEEpromString(Byte address)
        {
            Byte length = ReadEEpromByte(address++);
            Byte[] stringBytes = ReadEEpromBytes(address, length);

            StringBuilder response = new StringBuilder();

            for (int i = 0; i < stringBytes.Length; i++)
            {
                response.Append((char)stringBytes[i]);
            }

            return response.ToString();
        }
        
        /// <summary>
        /// Reads a date to IIC EEPROM starting at the given address.
        /// A date is stored in the EEPROM in the following style: 
        /// [31..26] [25..22] [21..17] [16..12] [11..6] [5..0] Bits
        ///  Year     Month    Day      Hour     Minutes Seconds
        /// </summary>
        /// <param name="address"></param>
        /// <returns>DateTime read from the EEPROM</returns>
        public DateTime ReadEEpromDate(Byte address)
        {   
            return IowUtil.DateBytesToDateTime(ReadEEpromBytes(address, 4));            
        }

        /// <summary>
        /// Write bytes to IIC EEPROM starting at given address.
        /// The number of bytes is only limited by the size of the EEPROM (up to 256x8 bit supported).
        /// Write operations are converted to single-byte operations. Thus, the write time is directly
        /// dependent on the number bytes to write.
        /// </summary>
        /// <param name="address">Start address for data in EEPROM.</param>
        /// <param name="data">Data to store to EEPROM.</param>
        /// <returns>Returns data.Length if write was successful.</returns>
        public Int32 WriteEEprom(Byte address, Byte[] data)
        {
            return implementation.WriteEEprom(0xA0, address, data);
        }

        /// <summary>
        /// Like WriteEEprom(Byte address, Byte[] data), but writes the data to the EEPROM addressed
        /// by chipAddress.
        /// </summary>
        /// <param name="chipAddress">Address of the EEPROM chip.</param>
        /// <param name="address">Memory address within the EEPROM.</param>
        /// <param name="data">Byte array of data to write.</param>
        /// <returns>Returns data.Length if write was successful.</returns>
        public Int32 WriteEEprom(Byte chipAddress, Byte address, Byte[] data)
        {
            return implementation.WriteEEprom(chipAddress, address, data);
        }

        /// <summary>
        /// Write a single byte to the given EEPROM address.
        /// </summary>
        /// <param name="address">Address to store data to.</param>
        /// <param name="data">Data byte to write.</param>
        /// <returns>Number of bytes confirmed by IIC device. See Iowarrior and IIC device data sheet for more information.</returns>
        public Int32 WriteEEprom(Byte address, Byte data)
        {
            return WriteEEprom(address, new Byte[] { data });
        }

        /// <summary>
        /// Write a string to IIC EEPROM starting at the given address.
        /// A string is stored in the EEPROM in PASCAL style: First there is a length byte followed by the string data.
        /// Write operation is split into single-byte write operations. The required time is directly
        /// dependent on the length of the string to write.
        /// Address overflow is neither checked nor handled!
        /// </summary>
        /// <param name="address">Start address of string. Points to the length byte.</param>
        /// <param name="data">String to write to EEPROM.</param>
        /// <returns>Number of bytes confirmed by IIC device. This is not equal to data.Length()!</returns>
        public Int32 WriteEEprom(Byte address, String data)
        {
            if (data == null)
                return 0;

            data = data.Substring(0, Math.Min(254, data.Length));

            Byte[] toWrite = new Byte[data.Length + 1];
            toWrite[0] = (Byte)data.Length;
            for (int i = 0; i < data.Length; i++)
                toWrite[i + 1] = (Byte)data[i];

            return WriteEEprom(address, toWrite);
        }

        /// <summary>
        /// Write an Int32 value to the EEPROM at the given address.
        /// Address overflow is neither checked nor handled!
        /// </summary>
        /// <param name="address">Start address of Int32 value.</param>
        /// <param name="data">Int32 value to store.</param>
        /// <returns>4.</returns>
        public Int32 WriteEEprom(Byte address, Int32 data)
        {
            return WriteEEprom(address, BitConverter.GetBytes(data));
        }

        /// <summary>
        /// Write a date to IIC EEPROM starting at the given address.
        /// A date is stored in the EEPROM in the following style: 
        /// [31..26] [25..22] [21..17] [16..12] [11..6] [5..0] Bits
        ///  Year     Month    Day      Hour     Minutes Seconds
        /// </summary>
        /// <param name="address">Start address of date value.</param>
        /// <param name="date">DateTime to write to EEPROM.</param>
        /// <returns></returns>
        public Int32 WriteEEprom(Byte address, DateTime date)
        {   
            return WriteEEprom(address, IowUtil.DateTimeToDateBytes(date));
        }

        /// <summary>
        /// Gets maximum number of Iowarrior chips which can be handled by IowKit.DLL.
        /// </summary>
        /// <returns>Maximum number of devices which can be handled by IowKit.DLL.</returns>
        public int GetMaximumNumberOfDevices()
        {
            return IowKitWrapper.GetMaximumNumberOfDevices();
        }

        /// <summary>
        /// Get handle of Iowarrior chip numbered as "index" by IowKit.DLL.
        /// </summary>
        /// <param name="index">Zero-based index of Iowarrior device [0..GetMaximumNumberOfDevices()-1].</param>
        /// <returns>Handle of the Iowarrior device.</returns>
        public int GetHandle(int index)
        {
            return IowKitWrapper.GetHandle(index);
        }
    }
}
