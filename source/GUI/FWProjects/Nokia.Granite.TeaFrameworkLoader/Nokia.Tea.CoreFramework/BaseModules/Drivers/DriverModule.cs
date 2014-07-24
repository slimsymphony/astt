using System;
using Nokia.Tea.CoreFramework.BaseModules.Drivers.BaseInterfaces;
using Nokia.Tea.CoreFramework.BaseModules.Drivers.Classes;
using Nokia.Tea.CoreFramework.ToolBox.Interfaces;

namespace Nokia.Tea.CoreFramework.BaseModules.Drivers
{
    /// <summary>
    /// A base class for all Driver modules.
    /// </summary>
    public class DriverModule : TeaModule, ITeaDriverLocking
    {
        #region Private members

        /// <summary>
        /// Configuration class id suffix.
        /// </summary>
        private const string conf = "Configuration";

        /// <summary>
        /// Object which has locked the resource
        /// </summary>
        private object lockedBy;

        #endregion

        /// <summary>
        /// Initializes a new instance of the <see cref="DriverModule"/> class.
        /// </summary>
        /// <param name="moduleId">
        /// The module id.
        /// </param>
        /// <param name="toolBox">
        /// The tool box.
        /// </param>
        public DriverModule(string moduleId, IToolBox toolBox)
            : base(moduleId, toolBox)
        {
        }

        #region Public methods

        /// <summary>
        /// Locks the driver for caller object
        /// </summary>
        /// <param name="source">The caller object</param>
        /// <returns>Object which holds the lock. Lock can be unlocked by disposing this Object</returns>
        /// <exception cref="InvalidOperationException">Thrown if driver is already locked</exception>
        public IDisposable Lock(object source)
        {
            if (this.lockedBy != null)
            {
                throw new InvalidOperationException("Cannot lock driver. Already locked by " + source);
            }

            this.lockedBy = source;
            return new Locking(source);
        }

        /// <summary>
        /// Unlocks the driver if locked by this resource
        /// </summary>
        /// <param name="source">Caller objer</param>
        /// <exception cref="InvalidOperationException">Thrown if driver is locked by another object or is not locked</exception>
        public void Unlock(object source)
        {
            if (this.lockedBy == null)
            {
                throw new InvalidOperationException("Cannot unlock driver which is not locked");
            }

            if (this.lockedBy == source)
            {
                this.lockedBy = null;
            }
            else
            {
                // base.Logger.TraceError("DriverModule, Unlock() ERROR: Cannot unlock driver" + source);
                throw new InvalidOperationException("Cannot unlock driver. It's locked by " + source);
            }
        }

        /// <summary>
        /// Returns the locking status of driver
        /// </summary>
        /// <returns>True if locked</returns>
        public bool IsLocked()
        {
            return this.lockedBy != null;
        }

        /// <summary>
        /// Unlocks driver even if it's locked by another resource. 
        /// Should be used only in error recovery.
        /// </summary>
        public void ForceUnlock()
        {
            this.lockedBy = null;
        }

        #endregion

        #region Protected methods

        /// <summary>
        /// Gets the configuration class module.
        /// </summary>
        /// <returns>Returns the configuration class object.</returns>
        protected object GetConfiguration()
        {
            return base.ToolBox.Get(base.ModuleId + conf, this.GetType());
        }

        /// <summary>
        /// Checks if driver is not locked for caller object.
        /// </summary>
        /// <param name="source">caller object</param>
        /// <returns>True if driver can be used without restrictions for caller Object</returns>
        protected bool IsUsableByCaller(object source)
        {
            return this.lockedBy == null || source == this.lockedBy;
        }

        /// <summary>
        /// Checks if driver is usable by given object. If not exception is thrown
        /// </summary>
        /// <param name="source">caller object</param>
        /// <exception cref="InvalidOperationException">Thrown if driver is not usable by given object</exception>        
        protected void CheckIfUsableByCaller(object source)
        {
            if (this.lockedBy == null || source == this.lockedBy)
            {
                return;
            }

            // base.Logger.TraceError("DriverModule, CheckIfUsableByCaller() ERROR: Driver locked by another object" + this.lockedBy);
            throw new InvalidOperationException("Driver locked by another object");
        }

        #endregion
    }
}