using System.Collections.Generic;
using System.Runtime.Serialization;
using System.ServiceModel;

namespace TestAutomation.Gui.Marble.IPC.ServiceClientCommon.Interfaces
{
    [ServiceContract]
    public interface IIoWarriorService
    {
        List<string> IoWarriorCardsFound
        {
            [OperationContract]
            get;
        }

        [OperationContract]
        void ExecuteCommand(string card, string command);

        /// <summary>
        /// Initializes the IoWarrior device(s)
        /// </summary>
        /// <param name="iowCardsRequired">The cards that are required to be found</param>
        /// <param name="timeoutForScan">Timeout for scan (in seconds) for the cards to be found</param>
        /// <returns></returns>
        [OperationContract]
        List<string> InitIoWarrior(List<string> iowCardsRequired, bool batCardWithUniSwitchInUse, bool usbCardWithUniSwitchInUse, bool developerMode, int timeoutForScan = 30);

        [OperationContract]
        void ResetIoWarrior();

        [OperationContract]
        void CloseIoWarrior();
    }

    /// <summary>
    /// Parameterclass that stores the settings needed for BlackBox service to communicate with IoWarrior Service.
    /// Inherits BaseSettings so that logging services are automatically taken into use (if configured).
    /// </summary>
    [DataContract]
    public class IoWarriorClientSettings : ClientSettings
    {
        public IoWarriorClientSettings()
        {
            base.ServiceExecutable = "IoWarriorService.exe";
            base.ServiceUri.HostAddress = "localhost";
            base.ServiceUri.ServicePort = 8052;
        }
    }

    /// <summary>
    /// Settings class for IoWarrior Service.
    /// </summary>
    [DataContract]
    public class IoWarriorServiceSettings : BaseSettings
    {
    }

    public class IowCardNames
    {
        public const string IowCardUnknown = "IowCardUnknown";
        public const string IowCardInvalid = "IowCardInvalid";
        public const string IowCardChargerWithBatteryV2 = "IowCardChargerWithBatteryV2";
        public const string IowCardUniSwitch = "IowCardUniSwitch";
        public const string IowCardMatrix_5x6 = "IowCardMatrix_5x6";
        public const string IowCardMatrix2_5x6 = "IowCardMatrix2_5x6";
        public const string IowCardBsiSimSwitch = "IowCardBsiSimSwitch";
        public const string IowCardBsiSimSwitchV1 = "IowCardBsiSimSwitchV1";
        public const string IowCardAudio = "IowCardAudio";
        public const string IowCardAccessory = "IowCardAccessory";
        public const string IowCardCharger = "IowCardCharger";
        public const string IowCardChargerWithBattery = "IowCardChargerWithBattery";
        public const string IowCardMatrix_4x7 = "IowCardMatrix_4x7";
        public const string IowCardMatrix2_4x7 = "IowCardMatrix2_4x7";
        public const string IowCardFlash = "IowCardFlash";
        public const string IowCardSim = "IowCardSim";
        public const string IowCardCapacitiveKeys = "IowCardCapacitiveKeys";
        public const string IowCardTouchRC = "IowCardTouchRC";
        public const string IowCarduSDSwitch = "IowCarduSDSwitch";
        public const string IowCardMatrix_16x16 = "IowCardMatrix_16x16";
        public const string IowCardUSBAccessory = "IowCardUSBAccessory";
        public const string IowCardExperimental = "IowCardExperimental";

        public static readonly string[] UnknownCards = { IowCardUnknown, IowCardInvalid };
        // 30.01.2014: For Aol it is agreed that Charger V4 / IowCardChargerWithBatteryV2 will be used 
        //public static readonly string[] BatteryCards = { IowCardBsiSimSwitch, IowCardBsiSimSwitchV1, IowCardCharger, IowCardChargerWithBattery, IowCardChargerWithBatteryV2 };
        public static readonly string[] BatteryCards = { IowCardChargerWithBatteryV2 };
        // 30.01.2014: For Aol it is agreed that USB-Accessory Card V1.1 / IowCardUSBAccessory will be used
        //public static readonly string[] UsbCards = { IowCardAccessory, IowCardUSBAccessory, IowCardFlash };
        public static readonly string[] UsbCards = { IowCardUSBAccessory };
        // 30.01.2014: For Aol it is agreed that JIG Uni switch V1 / IowCardUniSwitch will be used
        //public static readonly string[] SwitchCards = { IowCardUniSwitch, IowCardMatrix_16x16, IowCardFlash };
        public static readonly string[] SwitchCards = { IowCardUniSwitch };
    }
}
