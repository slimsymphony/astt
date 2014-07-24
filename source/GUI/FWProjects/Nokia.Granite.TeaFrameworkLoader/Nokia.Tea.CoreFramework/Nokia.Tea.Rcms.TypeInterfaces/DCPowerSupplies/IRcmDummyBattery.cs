using Nokia.Tea.CoreFramework.BaseModules.Rcms.BaseInterfaces;

namespace Nokia.Tea.Rcms.TypeInterfaces.DCPowerSupplies
{
    /// <summary>
    /// Interface for dummy battery.
    /// </summary>
    public interface IRcmDummyBattery : ITeaRcm
    {
        //THIS FUNCTIONALITY IS REQUIRED BY TEA TOUCH.
        //THIS FUNCTIONALITY IS NOT ENOUGH FOR ENERGY MANAGEMENT TEST SYSTEMS

        /// <summary>
        /// Initializes the Dummy battery
        /// Initial state:
        /// Battery disconnected
        /// </summary>
        void InitAtStartTest();

        /// <summary>
        /// Connects the battery
        /// </summary>
        void ConnectBattery();

        /// <summary>
        /// Disconnects the battery
        /// </summary>
        void DisconnectBattery();
    }
}