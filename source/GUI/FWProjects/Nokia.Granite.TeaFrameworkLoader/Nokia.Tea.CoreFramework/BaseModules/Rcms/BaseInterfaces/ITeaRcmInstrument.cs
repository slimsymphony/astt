using System;

namespace Nokia.Tea.CoreFramework.BaseModules.Rcms.BaseInterfaces
{
    /// <summary>
    /// The Role Control Module Instrument base interface.
    /// </summary>
    public interface ITeaRcmInstrument : ITeaRcm
    {
        /// <summary>
        /// Gets the model name of the instrument
        /// </summary>
        string InstrumentModel { get; }

        /// <summary>
        /// Gets the resource descriptor which specifies the connection to a physical device.
        /// </summary>
        string IoResourceDescriptor { get; }

        /// <summary>
        /// Gets the instrument firmware revision information.
        /// </summary>
        string InstrumentFirmwareRevision { get; }

        /// <summary>
        /// Locks the instrument and returns object which keeps the lock. Preferred
        /// way of locking is by having the using method. E.g. using (RcmExample.Lock) {...}
        /// </summary>
        /// <returns>Object which holds the lock. Lock can be unlocked by disposing this object</returns>
        IDisposable Lock();

        /// <summary>
        /// Unlocks instrument.
        /// </summary>
        void Unlock();
    }
}