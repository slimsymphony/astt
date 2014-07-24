using System.Collections.Generic;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Xml.Serialization;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;

namespace TestAutomation.Gui.Marble.IPC.Interfaces
{
    [ServiceContract(SessionMode = SessionMode.Required)]
    public interface IBlackBoxService : IClientKeepalive
    {
        [OperationContract]
        void InitIoWarrior(bool grayboxEnabled);

        /// <summary>
        /// Resets IoWarrior by closing/reopening the HW
        /// </summary>
        /// <param name="resetAndExit">If set to true, resets IoWarrior by exiting the IoWarrior service process</param>
        [OperationContract]
        void ResetIoWarrior(bool resetAndExit = false);

        [OperationContract]
        void ConnectPower();

        [OperationContract]
        void DisconnectPower();

        [OperationContract]
        void DisconnectUsb();

        [OperationContract]
        void InitTouch();

        [OperationContract]
        void InitAccelerometer();

        [OperationContract]
        void ExecuteHwOperation(string operation);

        [OperationContract]
        TouchStateResponse TouchEvent(List<MarbleTouchData> marbleTouchData);

        [OperationContract]
        TouchStateResponse PressKey(string key, int delay);

        [OperationContract]
        void CloseAll();

        [OperationContract]
        void CheckIoWarriorCards();

        [OperationContract]
        void PhoneModelSelected(string phoneModel);

        [OperationContract]
        bool ConnectDefaultUsbAccessoryConnector();

        [OperationContract]
        void ConnectUsb(UsbPort usbPort);

        [OperationContract]
        void ConnectSim(SimCard sim);
        
        [OperationContract]
        void ConnectMemoryCard(MemoryCard memoryCard);

        [OperationContract]
        void ConnectAvPlug(AvPlug avPlugPort);

        [OperationContract]
        void SetOrientation(string orientation);

        bool IsTouchReady
        {
            [OperationContract]
            get;
        }

        bool IsAccelerometerReady
        {
            [OperationContract]
            get;
        }

        bool IsRequiredIoWCardsFound
        {
            [OperationContract]
            get;
        }

        BlackBoxServiceSettings Settings
        {
            [OperationContract]
            get;

            [OperationContract]
            set;
        }

        string TouchFwVersion
        {
            [OperationContract]
            get;
        }

        string TouchFwVersionRequired
        {
            [OperationContract]
            get;
        }

        string AccFwVersion
        {
            [OperationContract]
            get;
        }

        List<CommandSequenceItem> PowerOnPhoneSequence
        {
            [OperationContract]
            get;
        }
        List<CommandSequenceItem> ResetPhonePowerSequence
        {
            [OperationContract]
            get;
        }
    }

    [ServiceContract(SessionMode = SessionMode.Required)]
    public interface IBlackBoxRemoteGuiService : IBlackBoxService
    {
        [OperationContract]
        void ClearRequirements();

        [OperationContract]
        void SetDefaultUsbAccessoryConnector(UsbPort port);

        [OperationContract]
        void TouchSetComPort(string comPort);

        [OperationContract]
        void AccelerometerSetComPort(string comPort);

        [OperationContract]
        void TouchSetEnabled(bool enabled);

        [OperationContract]
        void AccelerometerSetEnabled(bool enabled);

        [OperationContract]
        List<string> DetectEmulationCards();

        List<string> UsbAccessoryPortsAvailable
        {
            [OperationContract]
            get;
        }

        List<string> IoWarriorCardsFound
        {
            [OperationContract]
            get;
        }

        List<string> ProductVariants
        {
            [OperationContract]
            get;
        }

        List<CommandMapping> CommandMapping
        {
            [OperationContract]
            get;
        }

        List<string> IoWarriorCardsRequiredForTesting
        {
            [OperationContract]
            get;
        }  

    }

    /// <summary>
    /// Parameterclass that stores the settings needed for BlackBox Client to communicate with BlackBox Service.
    /// Inherits BaseSettings so that logging services are automatically taken into use (if configured).
    /// </summary>
    [DataContract]
    public class BlackBoxClientSettings : ClientSettings
    {      
        public BlackBoxClientSettings()
        {
            base.ServiceExecutable = "BlackBoxService.exe";
            base.ServiceUri.HostAddress = "localhost";
            base.ServiceUri.ServicePort = 8051;
        }
    }

    /// <summary>
    /// BlackBox settings class for BlackBox Service.
    /// This class is also serializable so that BlackBox remote GUI is able to access these settings.
    /// </summary>
    [DataContract]
    public class BlackBoxServiceSettings : BaseSettings
    {
        public const string ResetTouchCommand = "Reset_Touch";
        public const string ConnectHeadsetCommand = "Connect_Headset";
        public const string DisconnectHeadsetCommand = "Disconnect_Headset";
        public const string ConnectMemoryCardCommand = "Connect_MMC";
        public const string DisconnectMemoryCardCommand = "Disconnect_MMC";
        public const string ConnectSimSensorCommand = "Connect_SIM";
        public const string DisconnectSimSensorCommand = "Disconnect_SIM";
        public const string ConnectBtHeadsetCommand = "Connect_BT_Headset";
        public const string DisconnectBtHeadsetCommand = "Disconnect_BT_Headset";

        // CommandSequenceItem mappings
        public const string ConnectUsbCommand = "ConnectUsb";
        public const string SleepCommand = "Sleep";
        public const string ConnectPowerCommand = "ConnectPower";
        public const string DisconnectPowerCommand = "DisconnectPower";

        [DataMember]
        [XmlElement]
        public int ServicePort { get; set; }

        [DataMember]
        [XmlElement]
        public GeneralSettings General { get; set; }

        [DataMember]
        [XmlArray]
        public List<PhoneModelCardMapping> PhoneModelCardMappings { get; set; }

        public BlackBoxServiceSettings()
        {
            this.ServicePort = 8051;
            General = new GeneralSettings();
            PhoneModelCardMappings = new List<PhoneModelCardMapping>();
        }
    }

    #region BlackBox Settings Parameter Classes

    /// <summary>
    /// Stores the recent phone model used the last time BlackBox is used. Phone model and phone IMEI code
    /// </summary>
    [DataContract]
    public class GeneralSettings
    {
        [DataMember]
        [XmlElement]
        public string PhoneModel { get; set; }

        [DataMember]
        [XmlElement]
        public UsbPort DefaultUsbAccessoryConnector { get; set; }

        [DataMember]
        [XmlElement]
        public string CurrentUsbAccessoryConnector { get; set; }

        [DataMember]
        [XmlElement]
        public EmulationCard TouchCard { get; set; }

        [DataMember]
        [XmlElement]
        public EmulationCard AccelerometerCard { get; set; }

        [DataMember]
        [XmlElement]
        public bool DeveloperMode { get; set; }

        public GeneralSettings()
        {
            this.PhoneModel = string.Empty;
            this.DefaultUsbAccessoryConnector = UsbPort.Usb1;
            this.CurrentUsbAccessoryConnector = string.Empty;
            this.TouchCard = new EmulationCard();
            this.AccelerometerCard = new EmulationCard();
            this.DeveloperMode = false;
        }
    }


    /// <summary>
    /// Mapping class, which maps Atmel card to COM port.
    /// </summary>
    [DataContract]
    public class EmulationCard
    {
        [DataMember]
        [XmlAttribute]
        public string SerialPort { get; set; }

        [DataMember]
        [XmlAttribute]
        public bool EmulationEnabled { get; set; }

        public EmulationCard()
        {
            SerialPort = string.Empty;
            EmulationEnabled = false;
        }
    }


    /// <summary>
    /// Mapping class, which maps all the phone specific information together:
    /// E.g. How to power on this phone model, how to reset the power of this phone model,
    /// which touch controlle (and settings) this phone model uses, how are the IoWarrior cards configured for this phone (or model)
    /// </summary>
    [DataContract]
    public class PhoneModelCardMapping
    {
        [DataMember]
        [XmlElement]
        public string PhoneModel { get; set; }

        [DataMember]
        [XmlArray]
        public List<string> IoWCardsRequired { get; set; }

        [DataMember]
        [XmlArray]
        public List<string> ProductVariant { get; set; }

        [DataMember]
        [XmlArray]
        public List<CommandSequenceItem> PowerOnPhoneSequence { get; set; }

        [DataMember]
        [XmlArray]
        public List<CommandSequenceItem> ResetPhonePowerSequence { get; set; }

        [DataMember]
        [XmlArray]
        public List<CommandMapping> CommandMappings { get; set; }

        [DataMember]
        [XmlElement]
        public PhoneModelTouchMapping TouchMapping { get; set; }

        public PhoneModelCardMapping()
        {
            this.PhoneModel = string.Empty;
            this.IoWCardsRequired = new List<string>();
            this.ProductVariant = new List<string>();
            this.CommandMappings = new List<CommandMapping>();
            this.TouchMapping = new PhoneModelTouchMapping();
        }
    }

    /// <summary>
    /// Describes a Command Sequence Item: Used e.g. to create a "Power on phone", "Reset phone power" etc kind of sequences, where information
    /// such, what to do with which IoWarrior card, and how long to sleep after a command has been executed is needed
    /// </summary>
    [DataContract]
    public class CommandSequenceItem
    {
        [DataMember]
        [XmlAttribute]
        public string BlackBoxCommand { get; set; }

        [DataMember]
        [XmlAttribute]
        public string Attribute { get; set; }

        public CommandSequenceItem()
        {
            BlackBoxCommand = string.Empty;
            Attribute = string.Empty;
        }
    }

    /// <summary>
    /// Mapping class to map the commands used in Marble to IoWarrior cards and commands
    /// </summary>
    [DataContract]
    public class CommandMapping
    {
        [DataMember]
        [XmlAttribute]
        public string MarbleCommand { get; set; }

        [DataMember]
        [XmlAttribute]
        public string CardType { get; set; }

        [DataMember]
        [XmlAttribute]
        public string CardCommand { get; set; }

        public CommandMapping()
        {
            MarbleCommand = string.Empty;
            CardType = null;
            CardCommand = string.Empty;
        }
    }

    /// <summary>
    /// Mapping class to map the phone model to used touch controller
    /// </summary>
    [DataContract]
    public class PhoneModelTouchMapping
    {
        [DataMember]
        [XmlElement]
        public TouchControllerCypress TouchControllerSettings;

        public PhoneModelTouchMapping()
        {
            TouchControllerSettings = new TouchControllerCypress();
        }
    }

    /// <summary>
    /// TouchControllerCy
    /// </summary>
    [DataContract]
    public class TouchControllerCypress
    {
        [DataMember]
        [XmlAttribute]
        public string TouchControllerType;

        [DataMember]
        [XmlAttribute]
        public string FwVersionRequired;
        
        [DataMember]
        [XmlElement]
        public CypressComSettings PortSettings;

        [DataMember]
        [XmlElement]
        public CypressPanelSettings PanelSettings;
        
        public TouchControllerCypress()
        {
            TouchControllerType = "TouchControllerEvoCypress";
            this.FwVersionRequired = "13w500";
            PortSettings = new CypressComSettings();
            PanelSettings = new CypressPanelSettings();
        }

        #region Port settings

        [DataContract]
        public class CypressComSettings
        {
            [DataMember]
            [XmlAttribute]
            public string PortName;

            /// <summary>
            /// Baud rate of used COM port
            /// </summary>
            [DataMember]
            [XmlAttribute]
            public int BaudRate;

            /// <summary>
            /// USB-->Serial Port driver latency timer value
            /// </summary>
            [DataMember]
            [XmlAttribute]
            public int LatencyTimer;
        }

        #endregion

        #region Touch panel specific settings

        [DataContract]
        public class CypressPanelSettings
        {
            /// <summary>
            /// Display orientation.
            /// </summary>
            [DataMember]
            [XmlAttribute]
            public string DisplayOrientation;

            /// <summary>
            /// The max amount of fingers the touch panel supports
            /// </summary>
            [DataMember]
            [XmlAttribute]
            public int NumberOfFingers;

            /// <summary>
            ///  The delay between touch presses
            /// </summary>
            [DataMember]
            [XmlAttribute]
            public int DelayBetweenPresses;

            /// <summary>
            /// The max value of X known by the touch panel
            /// </summary>
            [DataMember]
            [XmlAttribute]
            public int Xmax;

            /// <summary>
            /// The max value of Y known by the touch panel
            /// </summary>
            [DataMember]
            [XmlAttribute]
            public int Ymax;

            /// <summary>
            /// The min value of X known by the touch panel
            /// </summary>
            [DataMember]
            [XmlAttribute]
            public int Xmin;

            /// <summary>
            /// The min value of Y known by the touch panel
            /// </summary>
            [DataMember]
            [XmlAttribute]
            public int Ymin;

            /// <summary>
            /// Screen Height of the DUT
            /// </summary>
            [DataMember]
            [XmlAttribute]
            public int ScreenHeight;

            /// <summary>
            /// Screen Width of the DUT
            /// </summary>
            [DataMember]
            [XmlAttribute]
            public int ScreenWidth;
        }

        #endregion
    }

    #endregion

    #region DataContract for BlackBox specific enumerations and parameter classes

    /// <summary>
    /// Defines the SIM cards available to switch between for SimCardSwitc card.
    /// </summary>
    [DataContract]
    public enum SimCard
    {
        [EnumMember]
        None = 0,
        [EnumMember]
        Sim1,
        [EnumMember]
        Sim2,
        [EnumMember]
        Sim3,
        [EnumMember]
        Sim4,
        [EnumMember]
        Sim5,
        [EnumMember]
        Sim6
    }

    /// <summary>
    /// Defines the memory cards available to switch between for uSDCardSwitc card.
    /// </summary>
    [DataContract]
    public enum MemoryCard
    {
        [EnumMember]
        None = 0,
        [EnumMember]
        CadrA,
        [EnumMember]
        CadrB,
        [EnumMember]
        CadrC,
        [EnumMember]
        CadrD,
    }

    /// <summary>
    /// Defines the USB ports available to switch between for USBAccessory card.
    /// </summary>
    [DataContract]
    public enum UsbPort
    {
        [EnumMember]
        None = 0,
        [EnumMember]
        Usb1,
        [EnumMember]
        Usb2,
        [EnumMember]
        Usb3,
        [EnumMember]
        Usb4
    }

    /// <summary>
    /// Defines the AV plugs available to switch between for USBAccessory card.
    /// </summary>
    [DataContract]
    public enum AvPlug
    {
        [EnumMember]
        None = 0,
        [EnumMember]
        Av1,
        [EnumMember]
        Av2,
        [EnumMember]
        Av3,
        [EnumMember]
        Av4
    }

    [DataContract]
    public class MarbleTouchData
    {
        public MarbleTouchData(string eventType, string x, string y, string touchId, string wait)
        {
            EventType = eventType;
            X = x;
            Y = y;
            TouchId = touchId;
            Wait = wait;
        }

        [DataMember]
        public string EventType;

        [DataMember]
        public string X;

        [DataMember]
        public string Y;

        [DataMember]
        public string TouchId;

        [DataMember]
        public string Wait;
    }

    /// <summary>
    /// Defines the touch response enum sent to Marble tool
    /// </summary>
    [DataContract]
    public enum TouchState
    {
        [EnumMember]
        Normal = 0,
        [EnumMember]
        PowerOffOrSleepMode,
        [EnumMember]
        Warning
    }

    [DataContract]
    public class TouchStateResponse
    {
        public TouchStateResponse()
        {
            this.State = TouchState.Normal;
            this.StateInfo = string.Empty;
        }

        public TouchStateResponse(TouchState state, string stateInfo)
        {
            this.State = state;
            this.StateInfo = stateInfo;
        }

        [DataMember]
        public TouchState State;

        [DataMember]
        public string StateInfo;
    }

    #endregion
}