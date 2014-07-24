using System;

namespace Nokia.Tea.CoreFramework.BaseModules.Drivers.BaseInterfaces
{
    /// <summary>
    /// Base driver interface.
    /// </summary>
    public interface ITeaDriverLocking
    {
        /// <summary>
        /// Locks the driver for requestor.
        /// </summary>
        /// <param name="source">The caller object.</param>
        /// <returns>Object which holds the lock. Lock can be unlocked by disposing this Object</returns>
        IDisposable Lock(object source);

        /// <summary>
        /// Unlocks RCM
        /// </summary>
        /// <param name="source">The caller object ID</param>
        void Unlock(object source);

        /// <summary>
        /// Returns the locking status of driver
        /// </summary>
        /// <returns>True if locked</returns>
        bool IsLocked();
    }
}