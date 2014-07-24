namespace Nokia.Tea.CoreFramework.BaseModules.Drivers.BaseInterfaces
{
    /// <summary>
    /// A base interface a driver may implement.
    /// This interface describes some basic information that
    /// could usually be queried from a device, or could be coded
    /// within the implemented driver.
    /// </summary>
    public interface ITeaDriverInfo
    {
        /// <summary>
        /// The vendor of the device.
        /// N/A if not available.
        /// </summary>
        string Vendor { get; }

        /// <summary>
        /// Description of the device.
        /// N/A if not available.
        /// </summary>
        string Description { get; }

        /// <summary>
        /// Version number of the driver on the form : major.minor.revision e.g. 2.1.15
        /// N/A if not available.
        /// </summary>
        string Version { get; }

        /// <summary>
        /// Firmware version of the device this driver is controlling.
        /// N/A if not available.
        /// </summary>
        string InstrumentFirmwareRevision { get; }

        /// <summary>
        /// Model name of the instrument.
        /// N/A if not available.
        /// </summary>
        string InstrumentModel { get; }

        /// <summary>
        /// The resource descriptor specifies the connection to a physical device.
        /// E.g. USB, GPIB.
        /// N/A if not available.
        /// </summary>
        string IoResourceDescriptor { get; }

        /// <summary>
        /// Setup of driver.
        /// </summary>
        string Setup { get; }
    }
}
