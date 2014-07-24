using System;
using System.Text;
using System.Runtime.InteropServices;

namespace Nokia.Iowarrior.Devices.IowKit
{
    /// <summary>
    /// This is the public wrapper class around the imported (unsafe) original IOWKIT.DLL functions.
    /// It provides exceptions and guarantees that IOWKIT.DLL is closed at normal program termination.
    /// IowKitWrapper class can be remoted.
    /// </summary>
    public class IowKitWrapper
    {
        static Boolean isOpen;
        static CleanupClass ensureCleanupOnExit;

        /// <summary>
        /// Constructor for internal use only. Not intended to be called by client code.
        /// </summary>
        public IowKitWrapper()
        {
            if (ensureCleanupOnExit == null)
                ensureCleanupOnExit = new CleanupClass();
        }

        /// <summary>
        /// Return connection status of IowDevices IowKitUnsafeNativeMethods.
        /// </summary>
        public Boolean IsOpen
        {
            get { return isOpen; }
        }

        /// <summary>
        /// Returns Product Id of the Iowarrior device. See Iowarrior data sheets for more information.
        /// </summary>
        /// <param name="iowHandle">Handle of the Iowarrior device.</param>
        /// <returns>Product Id of the Iowarrior device.</returns>
        public Int32 GetProductId(Int32 iowHandle)
        {
            return IowKitUnsafeNativeMethods.IowKitGetProductId(iowHandle);
        }

        /// <summary>
        /// Open all Iowarrior devices. There is no way to open a single Iowarrior device connection.
        /// Sets Timeout of all Iowarrior devices to 1000ms.
        /// CAUTION: Be aware that Iowarrior SDK requires also a call to CloseAll() in any case
        /// when the application terminates (i.e. also in case of error!) Iowarrior SDK might completely
        /// block and require a reboot when failing to do so.
        /// Rather call CloseAll() too often...
        /// </summary>
        /// <returns>Number of attached devices.</returns>
        public Int32 OpenAll()
        {
            Int32 numberOfDevices = 0;

            if (!isOpen) {
                try {
                    IowKitUnsafeNativeMethods.IowKitOpenDevice();
                    for (Int32 i = 0; i < IowKitUnsafeNativeMethods.MaximumNumberOfDevices; i++)
                        IowKitUnsafeNativeMethods.IowKitSetTimeout(IowKitUnsafeNativeMethods.IowKitGetDeviceHandle(i + 1), 1000);
                    isOpen = true;
                    numberOfDevices = Count();
                }
                catch {
                    isOpen = false;
                    throw;
                }
            }

            return numberOfDevices;
        }

        /// <summary>
        /// Closes all Iowarrior devices. There is no way to close a single Iowarrior device connection.
        /// IMPORTANT: Make sure that CloseAll is called before the application ends! Otherwise the IOWKIT.DLL might
        /// not be accessible without a reboot of the PC.
        /// </summary>
        public void CloseAll()
        {
            // Closes ALL IoWarriors at the same time.
            if (isOpen) {
                IowKitUnsafeNativeMethods.IowKitCloseDevice(0);
                isOpen = false;
            }
        }

        /// <summary>
        /// Get the serial number of an Iowarrior device identified by its handle.
        /// </summary>
        /// <param name="iowHandle">Handle of the Iowarrior device. Use GetHandle() to retrieve a valid handle.</param>
        /// <returns>Serial number of the device.</returns>
        public String GetSerialNumber(Int32 iowHandle)
        {
            StringBuilder serialNumber = new StringBuilder(16);
            short[] sn = new short[8];
            bool res = IowKitUnsafeNativeMethods.IowKitGetSerialNumber(iowHandle, ref sn[0]);
            foreach (char s in sn)
                if ((s >= '0' && s <= '9') || (s >= 'A' && s <= 'F'))
                    serialNumber.Append(s);
                else
                    serialNumber.Append('?');

            return serialNumber.ToString();
        }

        /// <summary>
        /// Get handle of Iowarrior chip numbered as "index" by IOWKIT.DLL.
        /// </summary>
        /// <param name="index">Index of Iowarrior device [0..Count()-1].</param>
        /// <returns>Handle of the Iowarrior device.</returns>
        public Int32 GetHandle(Int32 index)
        {
            if (index < 0 || index > 63)
                throw new ArgumentException("Out of bounds.", "index");

            OpenAll();
            return IowKitUnsafeNativeMethods.IowKitGetDeviceHandle(index + 1);
        }

        /// <summary>
        /// Get the amount of connected Iowarrior devices.
        /// </summary>
        /// <returns>Number of devices.</returns>
        public Int32 Count()
        {
            return IowKit.IowKitUnsafeNativeMethods.IowKitGetNumDevs();
        }

        /// <summary>
        /// Checks whether the Iowarrior device with the given iowHandle is still accessible.
        /// </summary>
        /// <param name="iowHandle">Handle of Iowarrior device.</param>
        /// <returns>True, if the Iowarrior is still alive.</returns>
        public Boolean GetIsAlive(Int32 iowHandle)
        {
            if (iowHandle == 0)
                return false;

            Int32 dummy = 0;
            Boolean result = IowKit.IowKitUnsafeNativeMethods.IowKitReadImmediate(iowHandle, ref dummy);
            return result;
        }

        /// <summary>
        /// Provides access to IowKitWrite function. See Iowarrior SDK for more details.
        /// </summary>
        /// <param name="handle">Handle of the Iowarrior device.</param>
        /// <param name="numPipe">Pipe number.</param>
        /// <param name="buffer">Data to be written.</param>
        /// <returns>Number of bytes being written.</returns>
        public int Write(int handle, byte numPipe, ref byte[] buffer)
        {
            return IowKit.IowKitUnsafeNativeMethods.IowKitWrite(handle, numPipe, ref buffer[0], buffer.Length);
        }

        /// <summary>
        /// Provides access to IowKitReadNonBlocking function. See Iowarrior SDK for more details.
        /// </summary>
        /// <param name="handle">Handle of the Iowarrior device.</param>
        /// <param name="numPipe">Pipe number.</param>
        /// <param name="buffer">Data buffer to be filled.</param>
        /// <returns>Number of bytes being read.</returns>
        public int ReadNonBlocking(int handle, int numPipe, ref byte[] buffer)
        {
            return IowKit.IowKitUnsafeNativeMethods.IowKitReadNonBlocking(handle, numPipe, ref buffer[0], buffer.Length);
        }

        /// <summary>
        /// Gets maximum number of devices which can be handled by IowKit.DLL.
        /// </summary>
        /// <returns>Maximum number of devices which can be handled by IowKit.DLL.</returns>
        public int GetMaximumNumberOfDevices()
        {
            return IowKit.IowKitUnsafeNativeMethods.MaximumNumberOfDevices;
        }
    }

    /// <summary>
    /// The only task of this class is to call CloseAll() when being destroyed.
    /// </summary>
    class CleanupClass
    {
        ~CleanupClass()
        {
            try
            {
                new IowKitWrapper().CloseAll();
            }
            catch
            {
                // Ignore any errors
            }
        }
    }

    /// <summary>
    /// Library Functions from original iowkit.dll (should be in the Windows/System32 Directory)
    /// This class is not supposed to be used directly!
    /// </summary>
    static class IowKitUnsafeNativeMethods
    {
        // We have a specially compiled version which supports maximum 32 devices

        internal static Int32 MaximumNumberOfDevices = 32;

        // Imported original SDK functions from IowKit.DLL

        [DllImport("iowkit", SetLastError = true)]
        internal static extern Int32 IowKitOpenDevice();

        [DllImport("iowkit", SetLastError = true)]
        internal static extern void IowKitCloseDevice(Int32 iowHandle);

        [DllImport("iowkit", SetLastError = true)]
        internal static extern Int32 IowKitWrite(Int32 iowHandle, Int32 numPipe, ref Byte buffer, Int32 length);

        //Not imported any more. Use ReadNonBlocking instead.
        //[DllImport("iowkit", SetLastError = true)]
        //internal static extern Int32 IowKitRead(Int32 iowHandle, Int32 numPipe, ref Byte buffer, Int32 length);

        [DllImport("iowkit", SetLastError = true)]
        internal static extern Int32 IowKitReadNonBlocking(Int32 iowHandle, Int32 numPipe, ref Byte buffer, Int32 length);

        [DllImport("iowkit", SetLastError = true)]
        internal static extern Boolean IowKitReadImmediate(Int32 iowHandle, ref Int32 buffer);

        [DllImport("iowkit", SetLastError = true)]
        internal static extern Int32 IowKitGetNumDevs();

        [DllImport("iowkit", SetLastError = true)]
        internal static extern Int32 IowKitGetDeviceHandle(Int32 numDevice);

        [DllImport("iowkit", SetLastError = true)]
        internal static extern short IowKitGetProductId(Int32 iowHandle);

        [DllImport("iowkit", SetLastError = true)]
        internal static extern Boolean IowKitGetSerialNumber(Int32 iowHandle, ref short serialNumber);

        [DllImport("iowkit", SetLastError = true)]
        internal static extern Boolean IowKitSetTimeout(Int32 iowHandle, Int32 timeout);

        // Not imported since it is not used right now
        //
        // [DllImport("iowkit", SetLastError = true)]
        // internal static extern Int32 IowKitCancelIo(Int32 iowHandle, Int32 numPipe);
    }
}
