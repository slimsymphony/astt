using System.Collections.Generic;
using TestAutomation.Gui.Marble.IPC.Interfaces;

namespace Nokia.Tea.Rcms.TypeInterfaces.TouchController
{
    /// <summary>
    /// Touch controller interface
    /// </summary>
    public interface ITouchController
    {     
        /// <summary>
        /// Move
        /// </summary>
        /// <param name="parameters"></param>
        TouchStateResponse Move(List<MarbleTouchData> marbleTouchData);

        /// <summary>
        /// Release
        /// </summary>
        /// <param name="finger"></param>
        //void Release(int finger);

        /// <summary>
        /// Closes the touch controller
        /// </summary>
        void Close();

        /// <summary>
        /// Opens the touch controller
        /// </summary>
        void Open();
    }
}

