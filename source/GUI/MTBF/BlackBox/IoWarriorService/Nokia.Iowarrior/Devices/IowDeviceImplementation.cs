using System;
using System.Collections.Generic;
using System.Text;
using Nokia.Iowarrior.Devices.IowKit;
using System.Threading;

namespace Nokia.Iowarrior.Devices
{
    /// <summary>
    /// This abstract class is the base class for all Iowarrior device implementations.
    /// It is not intended to be used by user code directly.
    /// </summary>
    internal abstract class IowDeviceImplementation
    {
        String serialNumber = "";
        Int32 handle;
        Int32 productId;
        long lastAccessTime = DateTime.Now.Ticks;
        Int32 minimumTimeBetweenAccesses;
        private IowBits lastOutputs = new IowBits(0);
        private Boolean iicIsOn;
        private Boolean spiIsOn;
        private Boolean lcdIsOn;

        private IowKitWrapper iowKitWrapper = new IowKitWrapper();

        /// <summary>
        /// Gets IowKitWrapper instance which provides direct access to CodeMercenaries' Iowarrior driver.
        /// </summary>
        protected IowKitWrapper IowKitWrapper
        {
            get { return iowKitWrapper; }
        }

        /// <summary>
        /// Get/set the minimum time between two consecutive access to this Iowarrior device.
        /// Default value: 50 [ms]. Time cannot be set shorter than 10 [ms].
        /// </summary>
        public Int32 MinimumTimeBetweenAccesses
        {
            get { return minimumTimeBetweenAccesses; }
            set
            {
                minimumTimeBetweenAccesses = Math.Max(20, value);
            }
        }

        /// <summary>
        /// Creates an IowDeviceDummy object. 
        /// </summary>
        /// <returns>IowDeviceDummy object.</returns>
        public static IowDeviceImplementation Create()
        {
            return new IowDeviceDummy();
        }

        /// <summary>
        /// Creates an IowDeviceImplementation matching to the type of device identified by iowHandle.
        /// </summary>
        /// <param name="iowHandle">Handle of Iowarrior device.</param>
        /// <returns>IowDevice40, IowDevice56 or IowDeviceDummy object.</returns>
        public static IowDeviceImplementation Create(Int32 iowHandle)
        {
            switch (new IowKitWrapper().GetProductId(iowHandle))
            {
                case (short)ProductId.Iowarrior40: return new IowDevice40(iowHandle);
                case (short)ProductId.Iowarrior56: return new IowDevice56(iowHandle);
                default: return new IowDeviceDummy();
            }
        }

        // Constructors

        protected IowDeviceImplementation()
        {
            MinimumTimeBetweenAccesses = 50; // Default value: 50ms
            ReadDeviceInformation();
        }

        /// <summary>
        /// Constructor. Not intended to be used by the client application.
        /// Rather use the static methods of IowDevice class to retrieve collections containing already
        /// instantiated objects for all connected Iowarrior devices.
        /// </summary>
        /// <param name="iowHandle">Handle of the Iowarrior device this object instance will access. Get it from
        /// IowKit.IowKitGetDeviceHandle() or IowKit.IowKitOpenDevice().</param>
        protected IowDeviceImplementation(Int32 iowHandle)
        {
            MinimumTimeBetweenAccesses = 50; // Default value: 50ms
            handle = iowHandle;
            ReadDeviceInformation();
        }

        /// <summary>
        /// Get handle used by this object to access Iowarrior device. Use IowKit.IowKitGetDeviceHandle() or
        /// IowKit.IowKitOpenDevice() to retrieve a valid handle.
        /// </summary>
        public Int32 Handle
        {
            get { return handle; }
        }

        /// <summary>
        /// Get the product ID used by this object to access Iowarrior device. See Iowarrior data sheet for further information.
        /// </summary>
        public ProductId ProductId
        {
            get { return (ProductId)Enum.Parse(typeof(ProductId), productId.ToString()); }
        }

        /// <summary>
        /// Get the serial number used by this object to access Iowarrior device.
        /// </summary>
        public String SerialNumber
        {
            get { return serialNumber; }
        }

        /// <summary>
        /// Get the status of IIC in Iowarrior device. True = IIC on. False = IIC off.
        /// </summary>
        public Boolean IsInSpecialModeIic
        {
            get { return iicIsOn; }
        }

        /// <summary>
        /// Get the status of SPI in Iowarrior device. True = SPI on. False = SPI off.
        /// </summary>
        public Boolean IsInSpecialModeSpi
        {
            get { return spiIsOn; }
        }

        /// <summary>
        /// Get the status of LCD mode in Iowarrior device. True = LCD mode on. False = LCD mode off.
        /// </summary>
        public Boolean IsInSpecialModeLcd
        {
            get { return lcdIsOn; }
        }

        /// <summary>
        /// Return connection status of IowKit.DLL.
        /// </summary>
        public Boolean IsOpen
        {
            get { return iowKitWrapper.IsOpen; }
        }

        /// <summary>
        /// Read all required information from current Iowarrior device. Normally called by constructor only.
        /// </summary>
        public void ReadDeviceInformation()
        {
            // Define default serial number
            serialNumber = "0x" + NamedCountersSingleton.GetNext("Dummy").ToString("X8");
            productId = 0x0000;

            if (Handle != 0)
            {
                EnsureSafeTiming();
                productId = iowKitWrapper.GetProductId(Handle);
                serialNumber = "0x" + iowKitWrapper.GetSerialNumber(Handle);
            }
        }

        /// <summary>
        /// Ensures minimum time span between two consecutive accesses to the same Iowarrior device.
        /// Uses the value set in MinimumTimeBetweenAccesses property.
        /// </summary>
        protected void EnsureSafeTiming()
        {
            EnsureSafeTiming(MinimumTimeBetweenAccesses);
        }

        /// <summary>
        /// Ensures minimum time span between two consecutive accesses to the same Iowarrior device.
        /// There should be at least 8ms between to accesses according to manual. Experience shows that 20ms provides
        /// enough stability.
        /// </summary>
        /// <param name="milliseconds">Minimum time span [ms] elapsed since last access to this device. Should not be below 10.</param>
        protected void EnsureSafeTiming(Int32 milliseconds)
        {
            milliseconds = Math.Abs(milliseconds);

            long deltaT = Math.Abs(DateTime.Now.Ticks - lastAccessTime);
             
            if (deltaT < 10000 * milliseconds)
            {
                Int32 deltaTimeMilliseconds = (Int32)(deltaT / (long)10000);
                Thread.Sleep(milliseconds - deltaTimeMilliseconds);
            }

            lastAccessTime = DateTime.Now.Ticks;
        }

        /// <summary>
        /// Turn off Iowarrior IIC support.
        /// Caution: This might cause some glitches on the IIC pins which could have effect on the connected hardware.
        /// Use this function only when absolutely needed.
        /// Look into Iowarrior data sheet to see which pins are affected.
        /// </summary>
        public virtual void DisableIic()
        {
            iicIsOn = false;
        }

        /// <summary>
        /// Turn on Iowarrior IIC support. Make sure you do this before any further IIC operation.
        /// IIC read operation will block, if IIC was not turned on.
        /// See Iowarrior data sheet for pinout and side effects to IO pins.
        /// </summary>
        public virtual void EnableIic()
        {
            iicIsOn = true;
        }

        /// <summary>
        /// Turn off Iowarrior SPI support.
        /// Be aware that this is only supported on Iowarrior56 devices. Calling this on any other real device
        /// will result in an exception.
        /// </summary>
        public virtual void DisableSpi()
        {
            spiIsOn = false;
        }

        /// <summary>
        /// Turn on Iowarrior SPI support.
        /// Be aware that this is only supported on Iowarrior56 devices. Calling this on any other real device
        /// will  result in an exception.
        /// </summary>
        public virtual void EnableSpi()
        {
            spiIsOn = false;
        }

        /// <summary>
        /// Turn off Iowarrior LCD support.
        /// </summary>
        public virtual void DisableLcd()
        {
            lcdIsOn = false;
        }

        /// <summary>
        /// Turn on Iowarrior LCD support. This will turn on LCD in HD44780 compatible mode with cursor being off and blanked display.
        /// </summary>
        public virtual void EnableLcd()
        {
            lcdIsOn = true;
        }

        /// <summary>
        /// Write text to the alphanumeric text display. This method supports only 20x4 LCD layouts, i.e.
        /// the text of each line will be truncated to 20 characters before being written to the display or
        /// padded with blanks on the right. Only the first 4 array items will be regarded.
        /// The display content is always fully overwritten.
        /// </summary>
        /// <param name="lines">Array of strings. One for each line, starting from top.</param>
        public virtual void WriteLcdLines(String[] lines)
        {
            if (lines == null)
                throw new ArgumentNullException("lines");

            String[] displayLines = new String[4];

            for (int i = 0; i < lines.Length; i++)
            {
                displayLines[i] = lines[i].PadRight(20, ' ').Substring(0, 20);
            }

            for (int i = lines.Length; i < 4; i++)
            {
                displayLines[i] = " ".PadRight(20, ' ');
            }

            WriteLcdMemory(displayLines[0]+displayLines[2]+displayLines[1]+displayLines[3]);
        }

        /// <summary>
        /// Copy string contents into LCD controller memory. The user of this function has to take care
        /// for the used layout to get the intended display content.
        /// See HD44780 data sheet or CodeMercenaries Application Note on LCD support for more details.
        /// </summary>
        /// <param name="text">Text to be written into display memory.</param>
        public abstract void WriteLcdMemory(String text);

        /// <summary>
        /// Write the arrays to SPI interface. This is only supported on Iowarrior56 devices. Calling it on any other
        /// real device will result in an exception.
        /// </summary>
        /// <param name="bytes">Data bytes to send.</param>
        public abstract void WriteSpiBytes(Byte[] bytes);

        /// <summary>
        /// Read real input values from Iowarrior input pins.
        /// Take care that only pins set to "true" using SetOutput() can be used as input.
        /// Be aware that IIC and LCD function use some I/O pins which will become unusable if those
        /// functions are activated and return "false" when being read.
        /// </summary>
        /// <returns>Bit pattern as seen by the Iowarrior input pins.</returns>
        public abstract IowBits ReadInputs();

        /// <summary>
        /// Get the last value written to the output pins.
        /// </summary>
        public IowBits LastOutputs
        {
            get { return lastOutputs; }
        }

        /// <summary>
        /// Set all output pins of the Iowarrior at the same time.
        /// </summary>
        /// <param name="bits">IowBits containing the bit pattern to be sent to output pins.</param>
        public virtual void WriteOutputs(IowBits bits)
        {
            lastOutputs = bits;
        }

        /// <summary>
        /// Read the specified number of bytes from EEPROM starting at given address.
        /// Read operation is converted into single-byte read operations. Thus, the time required
        /// directly depends on the number of data to read.
        /// Address overflow is neither checked nor handled!
        /// </summary>
        /// <param name="chipAddress">Address of the EEPROM chip itself (0xA_)</param>
        /// <param name="memAddress">Start address in EEPROM to read from.</param>
        /// <param name="count">Amount of data to read.</param>
        /// <returns>Data bytes read from the EEPROM.</returns>
        public abstract Byte[] ReadEEpromBytes(Byte chipAddress, Byte memAddress, Byte count);

        /// <summary>
        /// Write bytes to IIC EEPROM starting at given address.
        /// The number of bytes is only limited by the size of the EEPROM (up to 256x8 bit supported).
        /// Write operations are converted to single-byte operations. Thus, the write time is directly
        /// dependent on the number bytes to write.
        /// </summary>
        /// <param name="chipAddress">Address of the memory chip itself (0xA_).</param>
        /// <param name="memAddress">Start address for data in EEPROM.</param>
        /// <param name="data">Data to store to EEPROM.</param>
        /// <returns>Returns data.Length if write was successful.</returns>
        public abstract Int32 WriteEEprom(Byte chipAddress, Byte memAddress, Byte[] data);

        /// <summary>
        /// Write a command to IIC device with multiple data bytes.
        /// </summary>
        /// <param name="command">Command byte for the IIC device.</param>
        /// <param name="data">Parameter data of the command.</param>
        /// <returns>Number of bytes confirmed by IIC device. See Iowarrior and IIC device data sheet for more information.
        /// </returns>
        public abstract Int32 WriteIic(Byte command, Byte[] data);

        /// <summary>
        /// Read bytes from IIC bus.
        /// </summary>
        /// <param name="command">Read command to be sent to IIC device.</param>
        /// <param name="count">Number of data bytes expected from IIC device.</param>
        /// <returns>Array of data bytes read from IIC device.</returns>
        public abstract Byte[] ReadIic(Byte command, Byte count);

        /// <summary>
        /// Checks whether the Iowarrior device is still accessible.
        /// </summary>
        /// <returns>True, if the Iowarrior is still alive.</returns>
        public abstract Boolean CheckIsAlive();

        /// <summary>
        /// Computes the bit number from a given port name ("Px.y").
        /// </summary>
        /// <param name="portName">Port name "Px.y" of Iowarrior device.</param>
        /// <returns>Bit position usable e.g. for WriteOutput() or ReadInput() methods.</returns>
        /// <exception cref="ArgumentOutOfRangeException">In case the portName is not valid for this Iowarrior device instance.</exception>
        public abstract Int32 TranslatePortNameToBitNumber(string portName);

        /// <summary>
        /// Computes the port name ("Px.y") from the bit number as used in WriteOutput() or ReadInput() methods.
        /// </summary>
        /// <param name="bitNumber">Bit number (0..31/56), depending on Iowdevice.</param>
        /// <returns>Name of the port ("Px.y").</returns>
        /// <exception cref="ArgumentOutOfRangeException">In case the bitNumber is outside the values supported by this Iowarrior device instance.</exception>
        public abstract String TranslateBitNumberToPortName(Int32 bitNumber);
    }
}
