using System;

namespace Nokia.Tea.CoreFramework.BaseModules.Drivers.BaseInterfaces
{
    /// <summary>
    /// Base interface for locking driver channel.
    /// E.g. some device with multiple input/output channels may need to be used
    /// by multiple rcms.
    /// </summary>
    public interface ITeaDriverChannelLocking
    {
        // INSPECT: Suggestion from Tea.Framework developers: LockChannel, UnlockChannel?
        // Should the channel locking be separated from the full driver locking?
        // ITeaDriverLocking interface provides methods Lock(object source);, Unlock(object source);
        // which may be used to lock the entire driver for the calling RCM. In some cases locking
        // the entire driver is not an option e.g. PowerSupply with multiple channels, Data Acquisition
        // card that may be used by multiple RCMs etc.
        // then ITeaDriverChannelLocking may be used to lock only the channel the calling RCM needs.
        // But should this lock be named as LockChannel, UnlockChannel rather than overload the
        // ITeaDriverLocking methods Lock(object source);, Unlock(object source); with
        // Lock(object source, int channel);, Unlock(object source, int channel);

        /// <summary>
        /// Locks the driver channel for requestor.
        /// </summary>
        /// <param name="source">The caller object.</param>
        /// <param name="channel">The channel to be locked.</param>
        /// <returns>Object which holds the lock. Lock can be unlocked by disposing this Object</returns>
        IDisposable LockChannel(object source, int channel);

        /// <summary>
        /// Unlocks the driver channel from the requestor
        /// </summary>
        /// <param name="source">The caller object ID</param>
        /// <param name="channel">The channel to be unlocked.</param>
        void UnlockChannel(object source, int channel);
    }
}