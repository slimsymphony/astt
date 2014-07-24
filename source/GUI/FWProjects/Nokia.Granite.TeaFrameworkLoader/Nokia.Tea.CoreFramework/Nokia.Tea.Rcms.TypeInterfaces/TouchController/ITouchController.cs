
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
        //void Move(MarbleTouchData[] marbleTouchData);

        /// <summary>
        /// Move
        /// </summary>
        /// <param name="parameters"></param>
        void Move(object[] marbleTouchData);

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

