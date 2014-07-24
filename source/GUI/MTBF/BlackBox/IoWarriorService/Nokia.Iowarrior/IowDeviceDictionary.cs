using System;
using System.Collections.Generic;
using System.Text;
using Nokia.Iowarrior.Devices;
using Nokia.Iowarrior.Devices.IowKit;

namespace Nokia.Iowarrior
{
    /// <summary>
    /// Dictionary about all connected Iowarrior devices.
    /// Every device is accessed via its serial number String.
    /// </summary>
    public class IowDeviceDictionary : Dictionary<String, IowDevice>
    {
        /// <summary>
        /// Create new and empty IowDevice dictionary.
        /// </summary>
        public IowDeviceDictionary()
        {
        }

        /// <summary>
        /// Create new IowDevice dictionary. If <paramref name="refresh"/> is true, it will probe for attached devices
        /// and fill the dictionary.
        /// </summary>
        /// <param name="refresh">If true, the constructor will fill the dictionary with Refresh().</param>
        public IowDeviceDictionary(Boolean refresh)
        {
            if (refresh)
                Refresh();
        }

        /// <summary>
        /// Get all serial numbers contained in the dictionary.
        /// </summary>
        public ICollection<String> SerialNumbers
        {
            get
            {
                String[] names = new String[Count];
                int index = 0;
                foreach (String name in Keys)
                    names[index++] = name;
                return names;
            }
        }

        /// <summary>
        /// Create IowDeviceDictionary of all connected Iowarrior chips.
        /// The access key is the serial number of a device.
        /// If there is no chip connected, the dictionary is empty.
        /// </summary>
        /// <returns>IowDeviceDictionary.</returns>
        public IowDeviceDictionary Refresh()
        {
            IowDevice dummyDevice = new IowDevice();

            dummyDevice.CloseAll();
            dummyDevice.OpenAll();

            for (Int32 i = 0; i < dummyDevice.GetMaximumNumberOfDevices(); i++)
            {
                Int32 handle = dummyDevice.GetHandle(i);
                if (handle != 0)
                {
                    IowDevice iow = new IowDevice(handle);

                    if (!ContainsKey(iow.SerialNumber) && iow.CheckIsAlive())
                        this[iow.SerialNumber] = iow;
                }
            }

            Dictionary<String, IowDevice> tmpDict = new Dictionary<string, IowDevice>();
            foreach (String key in Keys)
                tmpDict[key] = this[key];

            foreach (String key in tmpDict.Keys)
            {
                if (!tmpDict[key].CheckIsAlive())
                    Remove(key);
            }

            return this;
        }
    };
}
