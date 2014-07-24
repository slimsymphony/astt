using System;
using System.Collections.Generic;
using Nokia.Tea.CoreFramework.BaseModules.Drivers.BaseInterfaces;

namespace Nokia.Tea.Drivers.TypeInterfaces.TouchController
{
    /// <summary>
    /// IDriverTouchControllerTi
    /// </summary>
    public interface IDriverTouchControllerTi : ITeaDriverInfo, ITeaDriverLocking, IDisposable
    {
        /// <summary>
        /// Sends the specified message.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <returns></returns>
        int Send(Byte[] message);

        /// <summary>
        /// Sends the specified messages.
        /// </summary>
        /// <param name="messages">The messages.</param>
        /// <returns></returns>
        int Send(List<Byte[]> messages);

        /// <summary>
        /// Releases this instance.
        /// </summary>
        /// <returns></returns>
        int Release();
    }
}
