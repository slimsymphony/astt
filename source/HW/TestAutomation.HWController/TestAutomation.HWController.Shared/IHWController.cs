namespace TestAutomation.HWController.Shared
{
    interface IHWController
    {
        void ConnectBatteryCharger();
        void ConnectHeadset();
        void ConnectPower();
        void InsertSIM2();
        void ConnectUSBMain();
        void ConnectUSBChargerMain();
        void ConnectUSBRemote();
        void DisconnectBatteryCharger();
        void DisconnectHeadset();
        void DisconnectPower();
        void RemoveSIM2();
        void DisconnectUSBMain();
        void DisconnectUSBRemote();
        void InsertMemoryCard();
        void PressKeylockPowerButton(int delay);
        void RemoveMemoryCard();
        void ConnectExt(int pinId);
        void DisconnectExt(int pinId);
        string GetHwStatus();
        string GetApplicationVersion();
    }
}
