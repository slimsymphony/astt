using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Windows;
using Marble.Views.Dialogs;
using TestAutomation.Gui.Marble.IPC.Clients;
using TestAutomation.Gui.Marble.IPC.Interfaces;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;
using Brush = System.Windows.Media.Brush;
using Brushes = System.Windows.Media.Brushes;
using MessageBox = System.Windows.MessageBox;

namespace Marble.ViewModel
{
    public class BlackBoxViewModel : INotifyPropertyChanged
    {
        #region Parameter classes

        public class IoWarriorCardSetup
        {
            public string CardRequired { get; set; }
            public string CardFound { get; set; }
            public Brush ForegroundColor { get; set; }
            public FontWeight FontWeight { get; set; }

            public IoWarriorCardSetup()
            {
                this.CardFound = string.Empty;
                this.CardRequired = string.Empty;
                this.ForegroundColor = Brushes.Black;
                this.FontWeight = FontWeights.Normal;
            }
        }

        //public class EmulationCardSettings : INotifyPropertyChanged
        //{
        //    private BlackBoxViewModel vm;
        //    public string EmulationCard { get; set; }

        //    private string comPort { get; set; }
        //    public string ComPort
        //    {
        //        get { return this.comPort; }
        //        set
        //        {
        //            if (this.comPort != value)
        //            {
        //                this.comPort = value;
        //                if (!string.IsNullOrEmpty(this.EmulationCard))
        //                {
        //                    if (this.EmulationCard == TouchEmulation)
        //                    {
        //                        vm.TouchEmulationComPortChanged(value);
        //                    }
        //                    else
        //                    {
        //                        vm.AccelerometerEmulationComPortChanged(value);
        //                    }
        //                }
        //            }
        //            if (PropertyChanged != null)
        //                PropertyChanged(this, new PropertyChangedEventArgs("ComPort"));
        //        }
        //    }

        //    private List<string> comPortsAvailable;
        //    public List<string> ComPortsAvailable 
        //    {
        //        get { return this.comPortsAvailable; }
        //        set
        //        {
        //            this.comPortsAvailable = value;
        //            if (PropertyChanged != null)
        //                PropertyChanged(this, new PropertyChangedEventArgs("ComPortsAvailable"));
        //        }
        //    }

        //    private bool emulationEnabled;
        //    public bool EmulationEnabled 
        //    {
        //        get { return this.emulationEnabled; }
        //        set
        //        {
        //            if (this.emulationEnabled != value)
        //            {
        //                this.emulationEnabled = value;
        //                if (!string.IsNullOrEmpty(this.EmulationCard))
        //                {
        //                    if (this.EmulationCard == TouchEmulation)
        //                    {
        //                        vm.TouchEmulationEnabledChanged(value);
        //                    }
        //                    else
        //                    {
        //                        vm.AccelerometerEmulationEnabledChanged(value);
        //                    }
        //                }
        //            }
        //            if (PropertyChanged != null)
        //                PropertyChanged(this, new PropertyChangedEventArgs("EmulationEnabled"));
        //        }
        //    }

        //    public string FwVersion 
        //    {
        //        get 
        //        {
        //            if (this.EmulationCard == TouchEmulation)
        //            {
        //                string fwv = string.Empty;
        //                this.vm.blackBoxClient.DelegateExecutor(proxy => fwv = proxy.TouchFwVersion);
        //                return fwv;
        //            }
        //            else
        //            {
        //                string fwv = string.Empty;
        //                this.vm.blackBoxClient.DelegateExecutor(proxy => fwv = proxy.AccFwVersion);
        //                return fwv;
        //            }
        //        }
        //    }

        //    public EmulationCardSettings(BlackBoxViewModel vm)
        //    {
        //        this.vm = vm;
        //        this.EmulationCard = string.Empty;
        //        this.ComPort = string.Empty;
        //        this.EmulationEnabled = true;
        //        this.ComPortsAvailable = new List<string>();
        //    }

        //    public event PropertyChangedEventHandler PropertyChanged;
        //}

        #endregion

        //#region Constants

        //internal const string TouchEmulation = "Touch Emulation";
        //internal const string AccelerometerEmulation = "Accelerometer Emulation";

        //#endregion

        #region Public events

        public event PropertyChangedEventHandler PropertyChanged;

        #endregion

        #region Private members

        internal MarbleWcfClient<IBlackBoxRemoteGuiService> blackBoxClient;
        private readonly SettingsHandler settingsHandler;
        private BlackBoxServiceSettings blackBoxServiceSettings;

        //private MarbleWcfClient<IVideoRecorderService> videoRecorderClient;
        private bool iowScanFailed;
        //private dynamic settings;
        //private bool touchEmulationNotePopupShown = false;

        #endregion

        #region Constructors

        public BlackBoxViewModel()
        {
            //this.settings = SettingsManager.Instance;
            this.blackBoxServiceSettings = new BlackBoxServiceSettings();
            //Crate settings handler
            this.settingsHandler = null;
            string settingsPath = @"..\settings\BlackBoxGuiClientSettings.xml";
            if (File.Exists(settingsPath))
            {
                this.settingsHandler = new SettingsHandler(new BlackBoxClientSettings(), settingsPath);
            }
        }

        #endregion

        #region Accessors

        private BlackBoxClientSettings blackBoxClientSettings
        {
            get
            {
                if (this.settingsHandler != null)
                    return this.settingsHandler.SettingsObject as BlackBoxClientSettings;
                return new BlackBoxClientSettings();
            }
        }

        public bool IsBlackBoxReady
        {
            get
            {
                return this.IsIoWReady;
            }
        }

        public bool IsIoWReady
        {
            get
            {
                bool iowReady = false;
                this.blackBoxClient.DelegateExecutor(proxy => iowReady = proxy.IsRequiredIoWCardsFound);
                return iowReady;
            }
        }
        public bool IsBlackBoxServiceRunning
        {
            get
            {
                var processes = Process.GetProcessesByName("BlackBoxService");
                return processes.Length == 1;
            }
        }
        //public bool IsTouchEmulationReady
        //{
        //    get
        //    {
        //        bool touchReady = false;
        //        this.blackBoxClient.DelegateExecutor(proxy => touchReady = proxy.IsTouchReady);
        //        return touchReady && this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled;
        //    }
        //}

        //public bool IsAccelerometerEmulationReady
        //{
        //    get
        //    {
        //        bool accReady = false;
        //        this.blackBoxClient.DelegateExecutor(proxy => accReady = proxy.IsAccelerometerReady);
        //        return accReady;
        //    }
        //}

        private bool expanderExpanded;
        public bool ExpanderExpanded
        {
            get { return expanderExpanded; }
            set
            {
                expanderExpanded = value;
                // If expander is closing, also close touch screen
                //if (!expanderExpanded)
                //{
                //    //this.TouchScreenVisible = expanderExpanded;
                //    //this.VideoFrameCallbackClientUnSubscribe();
                //}

                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("ExpanderExpanded"));
            }
        }

        //private bool touchScreenVisible;
        //public bool TouchScreenVisible
        //{
        //    get { return touchScreenVisible; }
        //    set
        //    {
        //        touchScreenVisible = value;
        //        if (PropertyChanged != null)
        //            PropertyChanged(this, new PropertyChangedEventArgs("TouchScreenVisible"));
        //    }
        //}

        private bool blackBoxGuiEnabled;
        public bool BlackBoxGuiEnabled
        {
            get { return blackBoxGuiEnabled; }
            set
            {
                blackBoxGuiEnabled = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("BlackBoxGuiEnabled"));
            }
        }

        private bool cardSelected;
        public bool CardSelected
        {
            get { return cardSelected; }
            set
            {
                cardSelected = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("CardSelected"));
            }
        }

        public ObservableCollection<string> PhoneModelsAvailable
        {
            get
            {
                ObservableCollection<string> c = new ObservableCollection<string>();
                foreach (PhoneModelCardMapping mapping in this.blackBoxServiceSettings.PhoneModelCardMappings)
                {
                    c.Add(mapping.PhoneModel);
                }
                return c;
            }
        }

        public string PhoneModelSelected
        {
            get { return this.blackBoxServiceSettings.General.PhoneModel; }
            set
            {
                if (this.blackBoxServiceSettings.General.PhoneModel != value)
                {
                    this.blackBoxServiceSettings.General.PhoneModel = value;

                    // Update settings back to BlackBox service. Update GUI according to new settings.
                    this.blackBoxClient.DelegateExecutor(proxy => proxy.PhoneModelSelected(value));
                    this.UpdateData();
                }
            }
        }

        public List<string> UsbAccessoryPortsAvailable
        {
            get
            {
                List<string> l = new List<string>();
                this.blackBoxClient.DelegateExecutor(proxy => l = proxy.UsbAccessoryPortsAvailable);
                return l;
            }
        }

        public string UsbAccessoryPortSelected
        {
            get { return this.blackBoxServiceSettings.General.DefaultUsbAccessoryConnector.ToString(); }
            set
            {
                UsbPort usbPortValue = (UsbPort)Enum.Parse(typeof(UsbPort), value);
                if (this.blackBoxServiceSettings.General.DefaultUsbAccessoryConnector != usbPortValue)
                {
                    this.blackBoxServiceSettings.General.DefaultUsbAccessoryConnector = usbPortValue;

                    // Update settings back to BlackBox service. Update GUI according to new settings.
                    this.blackBoxClient.DelegateExecutor(proxy => proxy.SetDefaultUsbAccessoryConnector(usbPortValue));
                    if (PropertyChanged != null)
                        PropertyChanged(this, new PropertyChangedEventArgs("UsbAccessoryPortSelected"));
                }
            }
        }

        public List<CommandMapping> CommandMapping
        {
            get
            {
                List<CommandMapping> l = new List<CommandMapping>();
                this.blackBoxClient.DelegateExecutor(proxy => l = proxy.CommandMapping);
                return l;
            }
        }

        private ObservableCollection<IoWarriorCardSetup> ioWCardSetup;
        public ObservableCollection<IoWarriorCardSetup> IoWCardSetup
        {
            get { return this.ioWCardSetup; }
            set
            {
                this.ioWCardSetup = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("IoWCardSetup"));
            }
        }

        //private ObservableCollection<EmulationCardSettings> emulationCardSetup;
        //public ObservableCollection<EmulationCardSettings> EmulationCardSetup
        //{
        //    get { return this.emulationCardSetup; }
        //    set
        //    {
        //        this.emulationCardSetup = value;
        //        if (PropertyChanged != null)
        //            PropertyChanged(this, new PropertyChangedEventArgs("EmulationCardSetup"));
        //    }
        //}
        
        private string productCodesSelectedProduct;
        public string ProductCodesSelectedProduct
        {
            get { return this.productCodesSelectedProduct; }
            set
            {
                this.productCodesSelectedProduct = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("ProductCodesSelectedProduct"));
            }
        }

        public string GrayboxEnabled
        {
            get
            {
                return "True";
            }
        }

        //private bool videoRecordingReady;
        //public bool VideoRecordingReady
        //{
        //    get { return videoRecordingReady; }
        //    set
        //    {
        //        videoRecordingReady = value;
        //        if (PropertyChanged != null)
        //            PropertyChanged(this, new PropertyChangedEventArgs("VideoRecordingReady"));
        //    }
        //}

        //private string videoRecordingStatus;
        //public string VideoRecordingStatus
        //{
        //    get { return this.videoRecordingStatus; }
        //    set
        //    {
        //        this.videoRecordingStatus = value;
        //        if (PropertyChanged != null)
        //            PropertyChanged(this, new PropertyChangedEventArgs("VideoRecordingStatus"));
        //    }
        //}

        //private string emulationStatus;
        //public string EmulationStatus
        //{
        //    get { return this.emulationStatus; }
        //    set
        //    {
        //        this.emulationStatus = value;
        //        if (PropertyChanged != null)
        //            PropertyChanged(this, new PropertyChangedEventArgs("EmulationStatus"));
        //    }
        //}

        //private Brush emulationForeGround;
        //public Brush EmulationForeGround
        //{
        //    get { return this.emulationForeGround; }
        //    set
        //    {
        //        this.emulationForeGround = value;
        //        if (PropertyChanged != null)
        //            PropertyChanged(this, new PropertyChangedEventArgs("EmulationForeGround"));
        //    }
        //}

        //private List<string> emulationCards
        //{
        //    get
        //    {
        //        List<string> l = new List<string>();
        //        this.blackBoxClient.DelegateExecutor(proxy => l = proxy.DetectEmulationCards());
        //        l.Add("");
        //        return l;
        //    }
        //}

        //private Image videoFrame;
        //public Image VideoFrame
        //{
        //    get { return this.videoFrame; }
        //    set
        //    {
        //        this.videoFrame = value;
        //        if (PropertyChanged != null)
        //            PropertyChanged(this, new PropertyChangedEventArgs("VideoFrame"));
        //    }
        //}

        //public Tuple<int,int> ScreenResolution
        //{
        //    get 
        //    { 
        //        int resolutionX = 0;
        //        int resolutionY = 0;
        //        foreach (PhoneModelCardMapping mapping in this.blackBoxServiceSettings.PhoneModelCardMappings)
        //        {
        //            if (mapping.PhoneModel == this.PhoneModelSelected)
        //            {
        //                resolutionX = mapping.TouchMapping.TouchControllerSettings.PanelSettings.ScreenWidth;
        //                resolutionY = mapping.TouchMapping.TouchControllerSettings.PanelSettings.ScreenHeight;
        //            }
        //        }
        //        return new Tuple<int, int>(resolutionX, resolutionY); 
        //    }
        //}
        
        //public bool IsTouchEmulationEnabled
        //{
        //    get
        //    {
        //        return this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled;
        //    }
        //}

        #endregion

        #region Internal methods

        internal void ServiceConnect(string hostAddress = null, int servicePort = -1)
        {
            //this.touchEmulationNotePopupShown = false;
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs("GrayboxEnabled"));

            iowScanFailed = false;
            if (hostAddress != null)
                this.blackBoxClientSettings.ServiceUri.HostAddress = hostAddress;
            if (servicePort != -1)
                this.blackBoxClientSettings.ServiceUri.ServicePort = servicePort;

            if (this.blackBoxClient == null)
            {
                this.blackBoxServiceConnect();
            }

            int tryCount = 5;
            //Try few times. It may be so that BlackBox WCF service is not yet running so a failure may occur.
            for (int i = 0; i < tryCount; i++)
            {
                try
                {
                    this.blackBoxClient.DelegateExecutor(proxy => this.blackBoxServiceSettings = proxy.Settings, false);
                    break;
                }
                catch
                {
                    if (i == tryCount - 1)
                        throw;
                    else
                        Thread.Sleep(2000);
                }
            }

            // Connect to VideoRecorder
            App.ViewModel.StartVideoRecorderIfEnabled();
            //var callback = new VideoRecorderServiceCallback(this);
            //videoRecorderClient = new MarbleWcfClient<IVideoRecorderService>(videoSettings, ServiceDefinitions.VideoRecorderServiceEndpoint, callback);
        }

        internal void ServiceDisconnect()
        {
            iowScanFailed = false;
            if (this.blackBoxClient != null)
            {
                this.blackBoxClient.Dispose();
                this.blackBoxClient = null;
            }
            //if (this.videoRecorderClient != null)
            //{
            //    this.videoRecorderClient.Dispose();
            //    this.videoRecorderClient = null;
            //}
            this.ExpanderExpanded = false;
        }

        //internal void VideoFrameCallbackClientSubscribe()
        //{
        //    this.VideoFrame = new Bitmap(240, 320);
        //    this.videoRecorderClient.DelegateExecutor(proxy => proxy.ClientSubscribe());
        //}

        //internal void VideoFrameCallbackClientUnSubscribe()
        //{
        //    if (this.videoRecorderClient != null)
        //    {
        //        this.videoRecorderClient.DelegateExecutor(proxy => proxy.ClientUnSubscribe(), false);
        //    }
        //}

        private void blackBoxServiceConnect()
        {
            this.blackBoxClient = new MarbleWcfClient<IBlackBoxRemoteGuiService>(this.blackBoxClientSettings, ServiceDefinitions.BlackBoxRemoteGuiServiceEndpoint);
        }

        #endregion

        #region Public methods

        public void InitBlackBox()
        {
            bool gbEnabled = true;

            this.BlackBoxGuiEnabled = false;
            this.blackBoxClient.DelegateExecutor(proxy => this.blackBoxServiceSettings = proxy.Settings);
            ProgressDialogResult result = ProgressDialog.Execute("Marble - BlackBox", "Initializing BlackBox", (bw, we) =>
            {
                //ProgressDialog.ReportWithCancellationCheck(bw, we, "Checking emulation card settings");

                //// Check whether COM port changed.
                //List<string> cards = this.emulationCards;
                //if (cards.Count == 2)
                //{
                //    if (!cards.Contains(this.blackBoxServiceSettings.General.TouchCard.SerialPort) && cards.Contains(this.blackBoxServiceSettings.General.AccelerometerCard.SerialPort))
                //    {
                //        foreach (string card in cards.Where(card => card != this.blackBoxServiceSettings.General.AccelerometerCard.SerialPort))
                //        {
                //            this.blackBoxServiceSettings.General.TouchCard.SerialPort = card;
                //            break;
                //        }
                //    }
                //    else if (!cards.Contains(this.blackBoxServiceSettings.General.TouchCard.SerialPort) && cards.Contains(this.blackBoxServiceSettings.General.TouchCard.SerialPort))
                //    {
                //        foreach (string card in cards.Where(card => card != this.blackBoxServiceSettings.General.TouchCard.SerialPort))
                //        {
                //            this.blackBoxServiceSettings.General.AccelerometerCard.SerialPort = card;
                //            break;
                //        }
                //    }
                //}

                //// Check for COM ports.
                //if (string.IsNullOrEmpty(this.blackBoxServiceSettings.General.TouchCard.SerialPort) && this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled)
                //{
                //    string errorString = "Missing serial port definition for touch emulation card. " + constructEmulationCardErrorString();
                //    throw new Exception(errorString);
                //}
                //if (string.IsNullOrEmpty(this.blackBoxServiceSettings.General.AccelerometerCard.SerialPort) && this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled)
                //{
                //    string errorString = "Missing serial port definition for accelerometer emulation card. " + constructEmulationCardErrorString();
                //    throw new Exception(errorString);
                //}

                ProgressDialog.ReportWithCancellationCheck(bw, we, "Setting Up IoWarrior");

                if (this.iowScanFailed)
                    this.blackBoxClient.DelegateExecutor(proxy => proxy.ClearRequirements(), false);
                try
                {
                    this.blackBoxClient.DelegateExecutor(proxy => proxy.InitIoWarrior(gbEnabled), false);
                    this.iowScanFailed = false;
                }
                catch (Exception)
                {
                    iowScanFailed = true;
                    throw;
                }

                ProgressDialog.ReportWithCancellationCheck(bw, we, "Checking required IoWarrior cards");
                this.blackBoxClient.DelegateExecutor(proxy => proxy.CheckIoWarriorCards());

                //if (this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled)
                //{
                //    ProgressDialog.ReportWithCancellationCheck(bw, we, "Setting up touch emulation");
                //    this.blackBoxClient.DelegateExecutor(proxy => proxy.InitTouch());
                //}

                //if (this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled)
                //{
                //    ProgressDialog.ReportWithCancellationCheck(bw, we, "Setting up accelerometer emulation");
                //    this.blackBoxClient.DelegateExecutor(proxy => proxy.InitAccelerometer());
                //}

                ProgressDialog.ReportWithCancellationCheck(bw, we, "Connecting default USB accessory connector");

                this.blackBoxClient.DelegateExecutor(proxy => proxy.ConnectDefaultUsbAccessoryConnector());

                App.ViewModel.IsBlackboxCheckBoxesEnabled = true;
                App.ViewModel.UpdateBlackboxRelatedControls();

            }, ProgressDialogSettings.WithSubLabel);

            if (result.Cancelled)
            {
                MessageBox.Show("Initialize BlackBox canceled.");
            }
            else if (result.OperationFailed)
            {
                this.blackBoxClient.DelegateExecutor(proxy => proxy.CloseAll());
                MessageBox.Show(result.Error.Message, "Initialize BlackBox failed", MessageBoxButton.OK, MessageBoxImage.Error);

                App.ViewModel.IsBlackboxCheckBoxesEnabled = false;
                App.ViewModel.UpdateBlackboxRelatedControls();
            }
            //else
            //{
            //    this.checkTouchFwVersion();
            //}
            this.BlackBoxGuiEnabled = true;
            this.UpdateData();
        }

        public void PowerOnPhone()
        {
            this.BlackBoxGuiEnabled = false;
            ProgressDialogResult result = ProgressDialog.Execute("Marble - BlackBox", "Powering on the phone", (bw, we) =>
            {
                ProgressDialog.ReportWithCancellationCheck(bw, we, "Disconnecting USB");
                this.blackBoxClient.DelegateExecutor(proxy => proxy.DisconnectUsb());

                ProgressDialog.ReportWithCancellationCheck(bw, we, "Disconnecting phone power");
                this.blackBoxClient.DelegateExecutor(proxy => proxy.DisconnectPower());

                // Wait a while before re-powering the phone.
                Thread.Sleep(2000);
                ProgressDialog.ReportWithCancellationCheck(bw, we, "Connecting phone power");
                this.powerOnPhone();

            }, ProgressDialogSettings.WithSubLabel);

            if (result.OperationFailed)
            {
                MessageBox.Show(result.Error.Message, "BlackBox Error!", MessageBoxButton.OK, MessageBoxImage.Error);
            }

            this.BlackBoxGuiEnabled = true;
            this.UpdateData();
        }

        public void ExecuteCommand(string command)
        {
            this.blackBoxClient.DelegateExecutor(proxy => proxy.ExecuteHwOperation(command));
        }

        public void PressKey(string key, int delay)
        {
            this.blackBoxClient.DelegateExecutor(proxy => proxy.PressKey(key, delay));
        }

        //public void TouchEvent(string eventType, string x, string y)
        //{
        //    if (this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled)
        //    {
        //        try
        //        {
        //            if (this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled && this.IsTouchEmulationReady)
        //            {
        //                MarbleTouchData data = new MarbleTouchData(eventType, x, y, "0", "20");
        //                List<MarbleTouchData> l = new List<MarbleTouchData>();
        //                l.Add(data);
        //                this.blackBoxClient.DelegateExecutor(proxy => proxy.TouchEvent(l));
        //                this.touchEmulationNotePopupShown = false;
        //            }
        //        }
        //        catch (Exception)
        //        {
        //            this.TouchEmulationEnabledChanged(false);
        //            throw;
        //        }
        //    }
        //    else
        //    {
        //        if (!touchEmulationNotePopupShown)
        //            MessageBox.Show("Unble to execute command: " + Environment.NewLine + "Touch emulation not enabled.", "Touch emulation status note", MessageBoxButton.OK, MessageBoxImage.Information);
        //        this.touchEmulationNotePopupShown = true;
        //    }
        //}

        public void UpdateData()
        {
            this.blackBoxClient.DelegateExecutor(proxy => this.blackBoxServiceSettings = proxy.Settings);
            //this.updateProductCodes();

            this.ioWCardSetup = new ObservableCollection<IoWarriorCardSetup>();

            var cardsRequired = new List<string>();
            this.blackBoxClient.DelegateExecutor(proxy => cardsRequired = proxy.IoWarriorCardsRequiredForTesting);

            List<string> cardsFound = new List<string>();
            this.blackBoxClient.DelegateExecutor(proxy => cardsFound = proxy.IoWarriorCardsFound);

            foreach (string cardRequired in cardsRequired)
            {
                IoWarriorCardSetup setup = new IoWarriorCardSetup();
                setup.CardRequired = cardRequired;

                foreach (string cardFound in cardsFound)
                {
                    if (cardFound == setup.CardRequired)
                    {
                        setup.CardFound = setup.CardRequired;
                        break;
                    }
                }
                if (string.IsNullOrEmpty(setup.CardFound))
                {
                    setup.FontWeight = FontWeights.Bold;
                    setup.ForegroundColor = Brushes.Red;
                }
                this.ioWCardSetup.Add(setup);
            }

            PropertyChanged(this, new PropertyChangedEventArgs("PhoneModelsAvailable"));
            PropertyChanged(this, new PropertyChangedEventArgs("PhoneModelSelected"));
            PropertyChanged(this, new PropertyChangedEventArgs("UsbAccessoryPortsAvailable"));
            PropertyChanged(this, new PropertyChangedEventArgs("UsbAccessoryPortSelected"));
            PropertyChanged(this, new PropertyChangedEventArgs("CommandMapping"));
            PropertyChanged(this, new PropertyChangedEventArgs("GrayboxEnabled"));

            //// Update emulation cards specific data
            //var emulationCardsetup = new ObservableCollection<EmulationCardSettings>();
            //List<string> comPorts = this.emulationCards;
            //emulationCardsetup.Add(new EmulationCardSettings(this));
            //emulationCardsetup.Add(new EmulationCardSettings(this));
            //emulationCardsetup[0].ComPort = this.blackBoxServiceSettings.General.TouchCard.SerialPort;
            //emulationCardsetup[0].EmulationCard = TouchEmulation;
            //emulationCardsetup[0].EmulationEnabled = this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled;
            //emulationCardsetup[0].ComPortsAvailable = comPorts;

            //emulationCardsetup[1].ComPort = this.blackBoxServiceSettings.General.AccelerometerCard.SerialPort;
            //emulationCardsetup[1].EmulationCard = AccelerometerEmulation;
            //emulationCardsetup[1].EmulationEnabled = this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled;
            //emulationCardsetup[1].ComPortsAvailable = comPorts;
            //this.EmulationCardSetup = emulationCardsetup;

            //string recorderStatus = string.Empty;
            //this.videoRecorderClient.DelegateExecutor(proxy => recorderStatus = proxy.IsServiceAvailable());
            //if (recorderStatus == string.Empty)
            //{
            //    this.VideoRecordingReady = true;
            //    this.VideoRecordingStatus = "Ready";
            //}
            //else
            //{
            //    this.VideoRecordingReady = false;
            //    this.VideoRecordingStatus = recorderStatus;
            //}

            //string status = string.Empty;
            //Brush foreGround = Brushes.Red;

            //if (!this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled && !this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled)
            //{
            //    status = "Touch disabled, Accelerometer disabled";
            //    foreGround = Brushes.Red;
            //}
            //else if (!this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled && this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled && !this.IsAccelerometerEmulationReady)
            //{
            //    status = "Touch disabled, Accelerometer not ready";
            //    foreGround = Brushes.Red;
            //}
            //else if (!this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled && this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled && this.IsAccelerometerEmulationReady)
            //{
            //    status = "Touch disabled, Accelerometer ready";
            //    foreGround = Brushes.Blue;
            //}
            //else if (this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled && !this.IsTouchEmulationReady && !this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled)
            //{
            //    status = "Touch not ready, Accelerometer disabled";
            //    foreGround = Brushes.Red;
            //}
            //else if (this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled && this.IsTouchEmulationReady && !this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled)
            //{
            //    status = "Touch ready, Accelerometer disabled";
            //    foreGround = Brushes.Blue;
            //}
            //else if (this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled && !this.IsTouchEmulationReady && this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled && this.IsAccelerometerEmulationReady)
            //{
            //    status = "Touch not ready, Accelerometer ready";
            //    foreGround = Brushes.Blue;
            //}
            //else if (this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled && this.IsTouchEmulationReady && this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled && !this.IsAccelerometerEmulationReady)
            //{
            //    status = "Touch ready, Accelerometer not ready";
            //    foreGround = Brushes.Blue;
            //}
            //else if (this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled && !this.IsTouchEmulationReady && this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled && !this.IsAccelerometerEmulationReady)
            //{
            //    status = "Touch not ready, Accelerometer not ready";
            //    foreGround = Brushes.Red;
            //}
            //else if (this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled && this.IsTouchEmulationReady && this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled && this.IsAccelerometerEmulationReady)
            //{
            //    status = "Touch ready, Accelerometer ready";
            //    foreGround = Brushes.Green;
            //}

            //this.EmulationStatus = status;
            //this.EmulationForeGround = foreGround;

            if (!this.IsIoWReady)// || this.EmulationForeGround == Brushes.Red || this.EmulationForeGround == Brushes.Blue)
            {
                this.ExpanderExpanded = true;
            }
            PropertyChanged(this, new PropertyChangedEventArgs("IsIoWReady"));
            PropertyChanged(this, new PropertyChangedEventArgs("IoWCardSetup"));
            PropertyChanged(this, new PropertyChangedEventArgs("CommandMapping"));
            //PropertyChanged(this, new PropertyChangedEventArgs("FwVersion"));
            //PropertyChanged(this, new PropertyChangedEventArgs("IsTouchEmulationReady"));         
            App.ViewModel.IsBlackboxCheckBoxesEnabled = this.IsBlackBoxReady;
            App.ViewModel.UpdateBlackboxRelatedControls();
        }

        //public void UpdateEmulationCardComPorts()
        //{
        //    // Update emulation cards specific data
        //    var emulationCardsetup = this.EmulationCardSetup;
        //    List<string> comPorts = this.emulationCards;
        //    emulationCardsetup[0].ComPortsAvailable = comPorts;
        //    emulationCardsetup[1].ComPortsAvailable = comPorts;
        //    if (!comPorts.Contains(emulationCardsetup[0].ComPort) || (emulationCardsetup[1].ComPort == emulationCardsetup[0].ComPort && emulationCardsetup[1].EmulationEnabled))
        //    {
        //        emulationCardsetup[0].ComPort = string.Empty;
        //    }
        //    if (!comPorts.Contains(emulationCardsetup[1].ComPort) || (emulationCardsetup[0].ComPort == emulationCardsetup[1].ComPort && emulationCardsetup[0].EmulationEnabled))
        //    {
        //        emulationCardsetup[1].ComPort = string.Empty;
        //    }
        //    this.EmulationCardSetup = emulationCardsetup;
        //}

        //public void TouchEmulationComPortChanged(string port)
        //{
        //    if (port == "")
        //    {
        //        this.blackBoxClient.DelegateExecutor(proxy => proxy.TouchSetComPort(port));
        //        this.blackBoxClient.DelegateExecutor(proxy => proxy.TouchSetEnabled(false));
        //    }
        //    else if (port == this.blackBoxServiceSettings.General.AccelerometerCard.SerialPort)
        //    {
        //        MessageBox.Show("The same port already selected for Accelerometer emulation", "Touch emulation card error", MessageBoxButton.OK, MessageBoxImage.Error);
        //        this.blackBoxClient.DelegateExecutor(proxy => proxy.TouchSetComPort(""));
        //        this.blackBoxClient.DelegateExecutor(proxy => proxy.TouchSetEnabled(false));
        //    }
        //    else
        //    {
        //        try
        //        {
        //            this.blackBoxClient.DelegateExecutor(proxy => proxy.TouchSetComPort(port));
        //        }
        //        catch (Exception ex)
        //        {
        //            MessageBox.Show(ex.Message, "Touch emulation card error", MessageBoxButton.OK, MessageBoxImage.Error);
        //            this.blackBoxClient.DelegateExecutor(proxy => proxy.TouchSetEnabled(false));
        //        }
        //    }

        //    this.UpdateData();
        //}

        //public void TouchEmulationEnabledChanged(bool enabled)
        //{
        //    if (this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled != enabled)
        //    {
        //        try
        //        {
        //            this.blackBoxClient.DelegateExecutor(proxy => proxy.TouchSetEnabled(enabled));
        //            this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled = enabled;
        //            if (enabled)
        //            {
        //                this.checkTouchFwVersion();
        //            }
        //        }
        //        catch (Exception ex)
        //        {
        //            MessageBox.Show(ex.Message, "Touch emulation card error", MessageBoxButton.OK, MessageBoxImage.Error);
        //            this.blackBoxClient.DelegateExecutor(proxy => proxy.TouchSetEnabled(false));
        //        }
        //        this.UpdateData();
        //    }
        //}

        //public void AccelerometerEmulationComPortChanged(string port)
        //{
        //    if (port == "")
        //    {
        //        this.blackBoxClient.DelegateExecutor(proxy => proxy.AccelerometerSetComPort(port));
        //        this.blackBoxClient.DelegateExecutor(proxy => proxy.AccelerometerSetEnabled(false));
        //    }
        //    else if (port == this.blackBoxServiceSettings.General.TouchCard.SerialPort)
        //    {
        //        MessageBox.Show("The same port already selected for Touch emulation", "Accelerometer emulation card error", MessageBoxButton.OK, MessageBoxImage.Error);
        //        this.blackBoxClient.DelegateExecutor(proxy => proxy.AccelerometerSetComPort(""));
        //        this.blackBoxClient.DelegateExecutor(proxy => proxy.AccelerometerSetEnabled(false));
        //    }
        //    else
        //    {
        //        try
        //        {
        //            this.blackBoxClient.DelegateExecutor(proxy => proxy.AccelerometerSetComPort(port));
        //        }
        //        catch (Exception ex)
        //        {
        //            MessageBox.Show(ex.Message, "Accelerometer emulation card error", MessageBoxButton.OK,
        //                            MessageBoxImage.Error);
        //            this.blackBoxClient.DelegateExecutor(proxy => proxy.AccelerometerSetEnabled(false));
        //        }
        //    }
        //    this.UpdateData();
        //}

        //public void AccelerometerEmulationEnabledChanged(bool enabled)
        //{
        //     if (this.blackBoxServiceSettings.General.AccelerometerCard.EmulationEnabled != enabled)
        //     {
        //         try
        //         {
        //             this.blackBoxClient.DelegateExecutor(proxy => proxy.AccelerometerSetEnabled(enabled));
        //         }
        //         catch (Exception ex)
        //         {
        //            MessageBox.Show(ex.Message, "Accelerometer emulation card error", MessageBoxButton.OK, MessageBoxImage.Error);
        //            this.blackBoxClient.DelegateExecutor(proxy => proxy.AccelerometerSetEnabled(false));
        //         }
        //         this.UpdateData();
        //     }
        //}

        public void ClearRequirements()
        {
            ProgressDialog.Execute("Marble - BlackBox", "Cleaning up", (bw, we) =>
            {
                ProgressDialog.ReportWithCancellationCheck(bw, we, "Deinitializing IoWarrior");
                this.blackBoxClient.DelegateExecutor(proxy => proxy.ClearRequirements());

            }, ProgressDialogSettings.WithSubLabel);
            
        }

        #endregion

        #region Private Methods

        //private void checkTouchFwVersion()
        //{
        //    bool showMessage = false;
        //    string fwVersionRequired = string.Empty;
        //    string fwVersion = string.Empty;
        //    if (this.blackBoxServiceSettings.General.TouchCard.EmulationEnabled)
        //    {
        //        // It may take a while untill touch fw version is returned from touch emulation card, so try a few times before giving up.
        //        for (int i = 0; i < 3; i++)
        //        {
        //            this.blackBoxClient.DelegateExecutor(proxy => fwVersion = proxy.TouchFwVersion, false);
        //            if (!string.IsNullOrEmpty(fwVersion))
        //            {
        //                //E.g. 13w500 (year, week, day)
        //                int fwYear = int.Parse(fwVersion.Substring(0, 2));
        //                int fwWeek = int.Parse(fwVersion.Substring(3, 2));
        //                int fwDay = int.Parse(fwVersion.Substring(5, 1));

        //                this.blackBoxClient.DelegateExecutor(proxy => fwVersionRequired = proxy.TouchFwVersionRequired, false);

        //                if (!string.IsNullOrEmpty(fwVersionRequired))
        //                {
        //                    int requiredFwYear = int.Parse(fwVersionRequired.Substring(0, 2));
        //                    int requiredFwWeek = int.Parse(fwVersionRequired.Substring(3, 2));
        //                    int requiredFwDay = int.Parse(fwVersionRequired.Substring(5, 1));
        //                    if (requiredFwYear > fwYear)
        //                    {
        //                        showMessage = true;
        //                        break;
        //                    }
        //                    if (requiredFwWeek > fwWeek)
        //                    {
        //                        showMessage = true;
        //                        break;
        //                    }
        //                    if (requiredFwDay > fwDay)
        //                    {
        //                        showMessage = true;
        //                        break;
        //                    }
        //                    break;
        //                }
        //            }
        //            else
        //                Thread.Sleep(100);

        //        }
        //    }
        //    if (showMessage && !string.IsNullOrEmpty(fwVersionRequired))
        //        MessageBox.Show("Touch FW Version " + fwVersionRequired + " or Newer Required." + Environment.NewLine + "Please Update Your Touch FW.", "FW Version Note", MessageBoxButton.OK, MessageBoxImage.Information);
        //}

        //private string constructEmulationCardErrorString()
        //{
        //    string errorString = Environment.NewLine;
        //    var cards = this.emulationCards;
        //    if (cards.Count > 0)
        //    {
        //        errorString += "Detected " + cards.Count + " emulation card(s) at: ";
        //        errorString += string.Join(", ", cards);
        //        errorString += ".";
        //    }
        //    else
        //    {
        //        errorString += "No emulation cards detected.";
        //    }
        //    errorString += " Check your settings!";
        //    return errorString;
        //}

        //private void updateProductCodes()
        //{
        //    List<string> pCodesList = new List<string>();
        //    this.blackBoxClient.DelegateExecutor(proxy => pCodesList = proxy.ProductVariants);

        //    string pCodes = pCodesList.Aggregate(string.Empty, (current, variant) => current + (variant + @"/"));
        //    if (pCodes.EndsWith(@"/"))
        //    {
        //        pCodes = pCodes.TrimEnd('/');
        //    }
        //    if (string.IsNullOrEmpty(pCodes))
        //    {
        //        pCodes = "None";
        //    }
        //    ProductCodesSelectedProduct = pCodes;
        //}

        //private ProductInfo getMainProneProductInfo()
        //{
        //    ProductInfo mainProduct = new ProductInfo();
        //    foreach (ProductInfo info in App.ViewModel.FuseClient.ConnectedProducts.Where(info => info.IsMain))
        //    {
        //        mainProduct = info;
        //    }

        //    return mainProduct;
        //}

        private void powerOnPhone()
        {
            List<CommandSequenceItem> powerOnPhoneSequence = new List<CommandSequenceItem>();
            this.blackBoxClient.DelegateExecutor(proxy => powerOnPhoneSequence = proxy.PowerOnPhoneSequence);
            foreach (CommandSequenceItem seqItem in powerOnPhoneSequence)
            {
                mapBlackBoxCommand(seqItem);
            }

            this.blackBoxClient.DelegateExecutor(proxy => proxy.ConnectDefaultUsbAccessoryConnector());
        }

        private void mapBlackBoxCommand(CommandSequenceItem sequenceItem)
        {
            if (sequenceItem.BlackBoxCommand.StartsWith("KEYCODE"))
            {
                if (!string.IsNullOrEmpty(sequenceItem.Attribute))
                {
                    this.blackBoxClient.DelegateExecutor(proxy => proxy.PressKey(sequenceItem.BlackBoxCommand, int.Parse(sequenceItem.Attribute)));
                }
                else
                {
                    this.blackBoxClient.DelegateExecutor(proxy => proxy.PressKey(sequenceItem.BlackBoxCommand, 100));
                }
            }
            else if (sequenceItem.BlackBoxCommand == BlackBoxServiceSettings.ConnectUsbCommand)
            {
                this.blackBoxClient.DelegateExecutor(proxy => proxy.ConnectUsb((UsbPort)Enum.Parse(typeof(UsbPort), sequenceItem.Attribute)));
            }
            else if (sequenceItem.BlackBoxCommand == BlackBoxServiceSettings.SleepCommand)
            {
                Thread.Sleep(int.Parse(sequenceItem.Attribute));
            }
            else if (sequenceItem.BlackBoxCommand == BlackBoxServiceSettings.ConnectPowerCommand)
            {
                this.blackBoxClient.DelegateExecutor(proxy => proxy.ConnectPower());
            }
            else if (sequenceItem.BlackBoxCommand == BlackBoxServiceSettings.DisconnectPowerCommand)
            {
                this.blackBoxClient.DelegateExecutor(proxy => proxy.DisconnectPower());
            }
            else if (sequenceItem.BlackBoxCommand == BlackBoxServiceSettings.ResetTouchCommand)
            {
                this.blackBoxClient.DelegateExecutor(proxy => proxy.ExecuteHwOperation(BlackBoxServiceSettings.ResetTouchCommand));
            }
        }

        #endregion
    }
}
