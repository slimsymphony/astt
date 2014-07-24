using System;
using System.Reflection;

namespace Nokia.Tea.CoreFramework.BaseModules.Drivers.Classes
{
    /// <summary>
    /// This class is for locking purposes.
    /// When class is disposed the lock is also released
    /// </summary>
    public class Locking : IDisposable
    {
        #region Private members

        /// <summary>
        /// The object reference for creator.
        /// </summary>
        private readonly object createdBy;

        #endregion

        #region Constructors

        /// <summary>
        /// Initializes a new instance of the <see cref="Locking"/> class.
        /// </summary>
        /// <param name="source">
        /// The caller object ID.
        /// </param>
        public Locking(object source)
        {
            this.createdBy = source;
        }

        ///<summary>
        /// Parameterless constructor use only with WCF
        ///</summary>
        public Locking()
        {
        }

        #endregion

        #region Public methods

        /// <summary>
        /// Dispose. Unlocks the driver.
        /// </summary>
        public void Dispose()
        {
            this.unlock();
        }

        #endregion

        #region Private methods

        ///// <summary>
        ///// Unlocks driver
        ///// </summary>
        private void unlock()
        {
            if (this.createdBy == null)
            {
                return;
            }

            // Get caller class unlock method
            Type thisType = this.createdBy.GetType();
            MethodInfo unlockMethod = thisType.GetMethod("Unlock");

            object[] objects = new object[1];

            objects[0] = this.createdBy;

            // RunStep caller class unlock method
            unlockMethod.Invoke(this.createdBy, objects);
        }

        #endregion
    }
}
