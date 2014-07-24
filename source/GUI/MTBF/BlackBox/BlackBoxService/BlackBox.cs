using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Management;
using System.Reflection;
using System.ServiceModel;
using System.Threading;
using System.Threading.Tasks;
using BlackBoxService;
using TestAutomation.Gui.Marble.IPC.Interfaces;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon.Interfaces;
using Nokia.Tea.Rcms.TypeInterfaces.TouchController;
using log4net;

namespace TestAutomation.Gui.Marble.Drivers
{
    /// <summary>
    /// The BlackBox class
    /// </summary>
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single, ConcurrencyMode = ConcurrencyMode.Multiple)]
    public class BlackBox : IDisposable, IBlackBoxRemoteGuiService
    {
        #region Private constants

        // Commands used with UniSwitch when no 'old style' pwr control or usb card in use
        private const string connectPowerCommand = "Connect_Power";
        private const string disconnectPowerCommand = "Disconnect_Power";
        private const string connectUsbCommand = "Connect_USB";
        private const string disconnectUsbCommand = "Disconnect_USB";

        #endregion

        #region Private Members

        private ITouchController touchController;
        private PhoneModelCardMapping cardMapping;
        private bool toucInitialized;
        private bool accelerometerInitialized;
        private bool cardsRequiredFound;
        private bool reInitIoWarriorRequired;

        private readonly ILog log;
        private readonly SettingsHandler settingsHandler;

        private IIoWarriorService ioWarrior;
        private List<string> iowCardsFound;
        private string usbAccessoryCard;
        private string batteryCard;
        private bool disposing;
        private const int defaultRetriesOnError = 5;
        private bool constructorInit;

        #endregion

        #region Accessors

        /// <summary>
        /// Property for getting full BlackBox settings
        /// </summary>
        public BlackBoxServiceSettings Settings
        {
            get { return this.settingsHandler.SettingsObject as BlackBoxServiceSettings; }
            set
            {
                this.settingsHandler.SettingsObject = value;
                this.settingsHandler.SaveSettings();
            }
        }

        public string TouchFwVersion
        {
            get
            {
                if (this.toucInitialized && this.touchController is TouchControllerCypressGen4)
                    return ((TouchControllerCypressGen4)this.touchController).TouchVersion;
                return string.Empty;
            }
        }

        public string TouchFwVersionRequired
        {
            get
            {
                if (this.cardMapping != null)
                    return this.cardMapping.TouchMapping.TouchControllerSettings.FwVersionRequired;
                return string.Empty;
            }
        }

        public string AccFwVersion
        {
            get { return string.Empty; }
        }

        public List<CommandSequenceItem> PowerOnPhoneSequence
        {
            get { return this.cardMapping.PowerOnPhoneSequence; }
        }

        public List<CommandSequenceItem> ResetPhonePowerSequence
        {
            get { return this.cardMapping.ResetPhonePowerSequence; }
        }

        /// <summary>
        /// Gets touch controller status
        /// </summary>
        public bool IsTouchReady
        {
            get { return this.toucInitialized; }
        }

        /// <summary>
        /// Gets accelerometer controller status
        /// </summary>
        public bool IsAccelerometerReady
        {
            get
            {
                return accelerometerInitialized;
            }
        }

        /// <summary>
        /// Gets required iow cards status
        /// </summary>
        public bool IsRequiredIoWCardsFound
        {
            get
            {
                return cardsRequiredFound;
            }
        }

        private bool isIoWarriorServiceRunning
        {
            get
            {
                var processes = Process.GetProcessesByName("IoWarriorService");
                if (processes.Length == 1)
                {
                    this.log.Debug("IoWarriorService is running at " + processes[0].MainModule.FileName);
                    processes[0].Close();
                    processes[0].Dispose();
                    return true;
                }
                return false;
            }
        }

        private bool marblebatCardWithUniSwitchInUse
        {
            get
            {
                string command = string.Empty;
                // Check whether marble battery/charger/power switch card in use
                foreach (CommandMapping mapping in this.cardMapping.CommandMappings.Where(mapping => mapping.MarbleCommand == connectPowerCommand))
                {
                    command = mapping.CardCommand;
                    break;
                }

                if (!string.IsNullOrEmpty(command))
                {
                    command = string.Empty;
                    foreach (CommandMapping mapping in this.cardMapping.CommandMappings.Where(mapping => mapping.MarbleCommand == disconnectPowerCommand))
                    {
                        command = mapping.CardCommand;
                        break;
                    }
                }
                if (!string.IsNullOrEmpty(command))
                    return true;

                return false;
            }
        }

        private bool usbCardWithUniSwitchInUse
        {
            get
            {
                string command = string.Empty;
                // Check whether UniSwitch used to controll the USB connection
                foreach (CommandMapping mapping in this.cardMapping.CommandMappings.Where(mapping => mapping.MarbleCommand == disconnectUsbCommand))
                {
                    command = mapping.CardCommand;
                    break;
                }

                if (!string.IsNullOrEmpty(command))
                {
                    command = string.Empty;
                    foreach (CommandMapping mapping in this.cardMapping.CommandMappings.Where(mapping => mapping.MarbleCommand == connectUsbCommand))
                    {
                        command = mapping.CardCommand;
                        break;
                    }
                }
                if (!string.IsNullOrEmpty(command))
                    return true;

                return false;
            }
        }

        #endregion

        #region Constructors

        public BlackBox(SettingsHandler settingsHandler)
        {
            this.constructorInit = true;
            this.cardsRequiredFound = false;
            this.log = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
            this.settingsHandler = settingsHandler;

            this.toucInitialized = false;
            this.accelerometerInitialized = false;
            this.iowCardsFound = new List<string>();

            if (!string.IsNullOrEmpty(this.Settings.General.PhoneModel))
            {
                try
                {
                    this.useCardMapping(this.Settings.General.PhoneModel);
                }
                catch (Exception ex)
                {
                    this.cardMapping = null;
                }
            }

            this.iowServiceConnect();
            // Try to initialize everything using default known settings.
            //try
            //{
            //    this.ioWarrior.InitIoWarrior(this.cardMapping.IoWCardsRequired, 20);
            //    this.reInitIoWarriorRequired = false;
            //}
            //catch (Exception ex)
            //{
            //    this.log.Warn("InitIoWarrior failed: " + ex.Message, ex);
            //}
            //try
            //{
            //    this.CheckIoWarriorCards();
            //}
            //catch (Exception ex)
            //{
            //    this.log.Warn("CheckIoWarriorCards failed: " + ex.Message, ex);
            //}

            //if (string.IsNullOrEmpty(this.Settings.General.CurrentUsbAccessoryConnector))
            //{
            //    try
            //    {
            //        this.ConnectDefaultUsbAccessoryConnector();
            //    }
            //    catch (Exception ex)
            //    {
            //        this.log.Warn("ConnectDefaultUsbAccessoryConnector failed: " + ex.Message, ex);
            //    }
            //}

            //if (this.Settings.General.TouchCard.EmulationEnabled)
            //{
            //    try
            //    {
            //        this.InitTouch();
            //    }
            //    catch (Exception e)
            //    {

            //        this.log.Warn("InitTouch failed: " + e.Message, e);
            //    }
            //}

            //if (this.Settings.General.AccelerometerCard.EmulationEnabled)
            //{
            //    try
            //    {
            //        this.InitAccelerometer();
            //    }
            //    catch (Exception e)
            //    {

            //        this.log.Warn("InitAccelerometer failed: " + e.Message, e);
            //    }
            //}
            //try
            //{
            //    this.ConnectUsb(UsbPort.None);
            //    Thread.Sleep(5000);
            //}
            //catch (Exception e)
            //{
            //    this.log.Warn("Connect USB None failed: " + e.Message, e);
            //}

            //try
            //{
            //    ConnectDefaultUsbAccessoryConnector();
            //}
            //catch (Exception e)
            //{
            //    this.log.Warn("Connect Default USB Accessory port failed: " + e.Message, e);
            //}

            //this.log.Info("BlackBox started...");
            this.constructorInit = false;
        }

        #endregion

        private void iowServiceConnect()
        {
            this.log.Debug("Checking whether IoWarriorService is running");
 
            if (!this.isIoWarriorServiceRunning)
            {
                try
                {
                    var serviceFiles = Directory.GetFiles(Environment.CurrentDirectory.ToLower().Contains("services") ? @"..\" : @"..\Services\", "IoWarriorService.exe", SearchOption.AllDirectories);
                    if (serviceFiles.Length == 1)
                    {
                        this.log.Debug("IoWarriorService is not running. Starting service now at " + serviceFiles[0]);

                        bool abort = false;
                        Action a = () =>
                        {
                            while (true)
                            {
                                if (abort || this.isIoWarriorServiceRunning)
                                    break;
                                try
                                {
                                    Process.Start(serviceFiles[0]);
                                }
                                catch {/* If Process.Start fails, just re-try*/}
                                Thread.Sleep(100);
                            } 
                        };
                        Task task = Task.Factory.StartNew(a);
                
                        //Wait for action to complete
                        if (!task.Wait(15000))
                        {
                            abort = true;
                        }
                        if (abort)
                        {
                            this.log.Error("Starting IoWarriorService in 15 seconds failed!");
                        }

                        // Service may have been restarted. ReInitIoWarrior is required.
                        this.reInitIoWarriorRequired = true;
                    }
                }
                catch (Exception ex)
                {
                    log.Error("iowServiceConnect: Unable to start service process", ex);
                }
            }

            this.log.Debug("Opening WCF ClientChannel");
            this.createClientChannel();

            int i = 0;
            while (true)
            {
                if (this.disposing)
                {
                    break;
                }
                try
                {
                    if (!((IContextChannel)this.ioWarrior).State.Equals(CommunicationState.Opened))
                    {
                        if (!((IContextChannel)this.ioWarrior).Equals(CommunicationState.Opening))
                        {
                            try
                            {
                                ((IContextChannel)this.ioWarrior).Open(TimeSpan.FromSeconds(1000));
                                break;
                            }
                            catch
                            {
                                this.iowServiceClose();
                                this.createClientChannel();
                            }
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                catch { }

                Thread.Sleep(500);
                i++;
                if (i == 20)
                {
                    log.Error("Opening WCF connection to IoWarriorService failed in 10 seconds!");
                    closeIoWarriorAndExit();
                    break;
                }
            }
        }

        private void createClientChannel()
        {
            // Try to create a client channel from client to service
            const int tryCount = 10;
            for (int i = 0; i < tryCount; i++)
            {
                if (this.disposing)
                {
                    break;
                }
                // Endpoint address = Uri + Endpoint name e.g. net.pipe://localhost/BlackBox/WcfEndpoint
                try
                {
                    this.ioWarrior = new ChannelFactory<IIoWarriorService>(new NetNamedPipeBinding(), @"net.pipe://localhost/IoWarriorService").CreateChannel();
                    IServiceChannel c = ((IServiceChannel)this.ioWarrior);
                    c.Opened += new EventHandler(serviceChannel_Opened);
                    c.Closed += new EventHandler(serviceChannel_Closed);
                    c.Faulted += new EventHandler(serviceChannel_Faulted);
                    break;
                }
                catch
                {
                    Thread.Sleep(500);
                }
            }
        }

        private void iowServiceClose()
        {
            if (this.ioWarrior != null)
            {
                this.log.Info("Closing WCF ClientChannel");

                IServiceChannel c = ((IServiceChannel)this.ioWarrior);
                c.Faulted -= serviceChannel_Faulted;
                c.Closed -= serviceChannel_Closed;
                c.Opened -= serviceChannel_Opened;

                if (this.disposing)
                {
                    try
                    {
                        this.log.Info("Dispose called: Trying to abort ClientChannel for quick exit");
                        c.Abort();
                        this.log.Info("Success...");
                    }
                    catch (Exception e)
                    {
                        this.log.Warn("Abort ClientChannel failed", e);
                    }
                }
                else
                {
                    if (c.State == CommunicationState.Opened)
                    {
                        try
                        {
                            this.log.Info("Trying to close client ServiceChannel");
                            c.Close();
                            this.log.Info("Success...");
                        }
                        catch (Exception ex)
                        {
                            this.log.Warn("Close ServiceChannel failed", ex);
                            try
                            {
                                this.log.Info("Trying to abort client ServiceChannel");
                                c.Abort();
                                this.log.Info("Success...");
                            }
                            catch (Exception e)
                            {
                                log.Warn("Abort client ServiceChannel failed", e);
                            }
                        }
                    }
                    else
                    {
                        try
                        {
                            this.log.Info("Trying to abort client ServiceChannel");
                            c.Abort();
                            this.log.Info("Success...");
                        }
                        catch (Exception e)
                        {
                            this.log.Warn("Abort clien ServiceChannel failed", e);
                        }
                    }
                }
                try
                {
                    this.log.Info("Trying Dispose ServiceChannel");

                    ((IDisposable)this.ioWarrior).Dispose();
                    this.log.Info("Success...");
                }
                catch (Exception e)
                {
                    this.log.Warn("Dispose ServiChannel failed", e);
                }

                this.ioWarrior = null;
            }
        }

        void serviceChannel_Faulted(object sender, EventArgs e)
        {
            log.Debug("SERVICE CHANNEL FAULTED");
        }

        void serviceChannel_Closed(object sender, EventArgs e)
        {
            log.Debug("SERVICE CHANNEL CLOSED");
        }

        void serviceChannel_Opened(object sender, EventArgs e)
        {
            log.Debug("SERVICE CHANNEL OPENED");
        }

        #region Public Methods

        /// <summary>
        /// Initialializes the Touch emulation
        /// </summary>
        public void InitTouch()
        {
            this.log.Debug("InitTouch");
            toucInitialized = false;
            if (this.Settings.General.TouchCard.EmulationEnabled)
            {
                if (this.Settings == null)
                {
                    throw new FaultException("Unable to initialize Touch Emulation: Settings object is null!");
                }
                if (touchController != null)
                {
                    touchController.Close();
                    touchController = null;
                }

                if (string.IsNullOrEmpty(Settings.General.TouchCard.SerialPort))
                {
                    throw new FaultException("Unable to initialize Touch emulation: Missing serial port definition for Touch!");
                }

                if (this.cardMapping.TouchMapping.TouchControllerSettings != null)
                {
                    // Get proper settings from mapped Touch Controller
                    TouchControllerCypress touchSettings = this.cardMapping.TouchMapping.TouchControllerSettings;

                    if (touchSettings.TouchControllerType == "TouchControllerCypressGen4")
                    {
                        try
                        {
                            touchController = new TouchControllerCypressGen4(touchSettings, this.Settings.General.TouchCard.SerialPort);
                            touchController.Open();
                        }
                        catch (Exception e)
                        {
                            throw new FaultException("Unable to initialize Touch emulation: " + e.Message);
                        }
                    }
                }
                toucInitialized = true;
            }
        }

        /// <summary>
        /// Initialializes the Accelerometer emulation.
        /// </summary>
        public void InitAccelerometer()
        {
            this.log.Debug("InitAccelerometer");
            accelerometerInitialized = false;
            if (this.Settings.General.AccelerometerCard.EmulationEnabled)
            {
                if (this.Settings == null)
                {
                    throw new FaultException("Unable to initialize Accelerometer Emulation: Settings object is null!");
                }

                if (string.IsNullOrEmpty(Settings.General.AccelerometerCard.SerialPort))
                {
                    throw new FaultException(
                        "Unable to initialize Accelerometer emulation: Missing serial port definition for Accelerometer!");
                }

                try
                {
                    SetOrientation("Portrait");
                }
                catch (Exception ex)
                {
                    throw new FaultException("Unable to initialize Accelerometer emulation: " + ex.Message);
                }
                accelerometerInitialized = true;
            }
        }

        /// <summary>
        /// Closes all the devices. IoWarrior and Touch.
        /// </summary>
        public void CloseAll()
        {
            this.log.Debug("CloseAll");
            CloseAccelerometer();
            CloseTouch();
        }

        /// <summary>
        /// Closes the touch controller driver
        /// </summary>
        public void CloseTouch()
        {
            this.log.Debug("CloseTouch");
            if (touchController != null)
            {
                try
                {
                    touchController.Close();
                }
                catch { /* Failure on closing the touch controller should not cause any actions, since on next initialization, touch is reinitialized anyway */}
                touchController = null;
            }
            toucInitialized = false;
        }

        /// <summary>
        /// Sets accelerometer initialized to false.
        /// </summary>
        public void CloseAccelerometer()
        {
            this.log.Debug("CloseAccelerometer");
            accelerometerInitialized = false;
        }

        /// <summary>
        /// Powers on the phone
        /// </summary>
        public void ConnectPower()
        {
            if (this.reInitIoWarriorRequired && !this.constructorInit)
            {
                try
                {
                    this.InitIoWarrior();
                }
                catch (Exception ex)
                {
                    this.log.Error("ConnectPower() --> Reinit IoWarrior was required but InitIoWarrior failed!", ex);
                }
            }

            this.log.Debug("ConnectPower");

            // Check whether new battery/charger/power switch card in use
            string command = string.Empty;
            string cardType = string.Empty;
            foreach (CommandMapping mapping in this.cardMapping.CommandMappings.Where(mapping => mapping.MarbleCommand == connectPowerCommand))
            {
                command = mapping.CardCommand;
                cardType = mapping.CardType;
                break;
            }

            if (!string.IsNullOrEmpty(command))
            {
                for (int i = 0; i < defaultRetriesOnError; i++)
                {
                    try
                    {
                        this.ioWarrior.ExecuteCommand(cardType, command);
                        break;
                    }
                    catch (FaultException e)
                    {
                        throw new FaultException(e.Message, e.Code);
                    }
                    catch (Exception ex)
                    {
                        this.log.Warn(ex.Message);
                        this.iowServiceClose();
                        this.iowServiceConnect();
                        if ((i == defaultRetriesOnError - 1) || this.constructorInit)
                            throw new FaultException(ex.Message);
                    }
                }
            }
            else
            {
                for (int i = 0; i < defaultRetriesOnError; i++)
                {
                    try
                    {
                        // Check which card type is used
                        if (this.batteryCard == IowCardNames.IowCardChargerWithBattery)
                        {
                            this.ioWarrior.ExecuteCommand(this.batteryCard, "connect:battery");
                        }
                        else
                        {
                            this.ioWarrior.ExecuteCommand(this.batteryCard, "connect:power");
                        }
                        break;
                    }
                    catch (FaultException e)
                    {
                        throw new FaultException(e.Message, e.Code);
                    }
                    catch (Exception ex)
                    {
                        this.log.Warn(ex.Message);
                        this.iowServiceClose();
                        this.iowServiceConnect();
                        if ((i == defaultRetriesOnError - 1) || this.constructorInit)
                            throw new FaultException(ex.Message);
                    }
                } 
            }
        }

        /// <summary>
        /// Disconnects phone power
        /// </summary>
        public void DisconnectPower()
        {
            if (this.reInitIoWarriorRequired && !this.constructorInit)
            {
                try
                {
                    this.InitIoWarrior();
                }
                catch (Exception ex)
                {
                    this.log.Error("DisconnectPower() --> Reinit IoWarrior was required but InitIoWarrior failed!", ex);
                }
            }

            this.log.Debug("DisconnectPower");

            // Check whether new battery/charger/power switch card in use
            string command = string.Empty;
            string cardType = string.Empty;
            foreach (CommandMapping mapping in this.cardMapping.CommandMappings.Where(mapping => mapping.MarbleCommand == disconnectPowerCommand))
            {
                command = mapping.CardCommand;
                cardType = mapping.CardType;
                break;
            }

            if (!string.IsNullOrEmpty(command))
            {
                for (int i = 0; i < defaultRetriesOnError; i++)
                {
                    try
                    {
                        this.ioWarrior.ExecuteCommand(cardType, command);
                        break;
                    }
                    catch (FaultException e)
                    {
                        throw new FaultException(e.Message, e.Code);
                    }
                    catch (Exception ex)
                    {
                        this.log.Warn(ex.Message);
                        this.iowServiceClose();
                        this.iowServiceConnect();
                        if ((i == defaultRetriesOnError - 1) || this.constructorInit)
                            throw new FaultException(ex.Message);
                    }
                }
            }
            else
            {
                for (int i = 0; i < defaultRetriesOnError; i++)
                {
                    try
                    {
                        if (this.batteryCard == IowCardNames.IowCardChargerWithBattery ||
                            this.batteryCard == IowCardNames.IowCardChargerWithBatteryV2)
                        {
                            this.ioWarrior.ExecuteCommand(this.batteryCard, "disconnect:battery");
                        }
                        else
                        {
                            this.ioWarrior.ExecuteCommand(this.batteryCard, "disconnect:power");
                        }
                        break;
                    }
                    catch (FaultException e)
                    {
                        throw new FaultException(e.Message, e.Code);
                    }
                    catch (Exception ex)
                    {
                        this.log.Warn(ex.Message);
                        this.iowServiceClose();
                        this.iowServiceConnect();
                        if ((i == defaultRetriesOnError - 1) || this.constructorInit)
                            throw new FaultException(ex.Message);
                    }
                }
            }
        }

        /// <summary>
        /// Executes the given HW related operation
        /// </summary>
        /// <param name="command">The operation to execute</param>
        public void ExecuteHwOperation(string command)
        {
            if (this.reInitIoWarriorRequired && !this.constructorInit)
            {
                try
                {
                    this.InitIoWarrior();
                }
                catch (Exception ex)
                {
                    this.log.Error("ExecuteHwOperation: " + command + " --> Reinit IoWarrior was required but InitIoWarrior failed!", ex);
                }
            }

            this.log.Debug("ExecuteHwOperation: " + command);
            if (cardMapping == null)
            {
                throw new FaultException("Unable to execute IoWarrior command: No phone specific command mappings loaded for IoWarrior!", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
            }

            if (command.StartsWith("KEYCODE"))
            {
                this.PressKey(command);
            }
            else
            {
                bool commandFound = false;
                foreach (CommandMapping mapping in cardMapping.CommandMappings)
                {
                    if (mapping.MarbleCommand == command)
                    {
                        commandFound = true;
                        if (this.iowCardsFound.Contains(mapping.CardType))
                        {
                            for (int i = 0; i < defaultRetriesOnError; i++)
                            {
                                try
                                {
                                    this.ioWarrior.ExecuteCommand(mapping.CardType, mapping.CardCommand);
                                    break;
                                }
                                catch (FaultException e)
                                {
                                    throw new FaultException(e.Message, e.Code);
                                }
                                catch (Exception ex)
                                {
                                    this.log.Warn(ex.Message);
                                    this.iowServiceClose();
                                    this.iowServiceConnect();
                                    if ((i == defaultRetriesOnError - 1) || this.constructorInit)
                                        throw new FaultException(ex.Message);
                                }
                            }
                            break;
                        }
                        throw new FaultException("No IoWarrior card found for command '" + command + "'" +
                                                            ". Card of type" + mapping.CardType + "  expected.", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
                    }
                }

                if (!commandFound)
                {
                    throw new FaultException("No IoWarrior card mapping found for command '" + command + "'" +
                                                        ". Check your test script or add proper command mapping. See " +
                                                        this.settingsHandler.SettingsFilePath, new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
                }
            }
        }

        /// <summary>
        /// Presses the given key
        /// </summary>
        /// <param name="key">The key to press</param>
        public void PressKey(string key)
        {
            PressKey(key, 100);
        }

        /// <summary>
        /// Presses the given key.
        /// </summary>
        /// <param name="key">Key to press</param>
        /// <param name="delay">Delay in millisecond</param>
        public TouchStateResponse PressKey(string key, int delay)
        {
            //if (this.reInitIoWarriorRequired && !this.constructorInit)
            //{
            //    try
            //    {
            //        this.InitIoWarrior();
            //    }
            //    catch (Exception ex)
            //    {
            //        this.log.Error("PressKey: " + key + " Delay: " + delay +" --> Reinit IoWarrior was required but InitIoWarrior failed!", ex);
            //    }
            //}
            this.log.Debug("PressKey: " + key + " Delay: " + delay);
            if (cardMapping == null)
            {
                throw new FaultException("Unable to execute IoWarrior command: No phone specific command mappings loaded for IoWarrior!", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
            }

            bool keyFound = false;
            foreach (CommandMapping mapping in cardMapping.CommandMappings)
            {
                if (mapping.MarbleCommand == key)
                {
                    keyFound = true;

                    if (this.iowCardsFound.Contains(mapping.CardType) || mapping.CardType == "Touch")
                    {
                        for (int i = 0; i < defaultRetriesOnError; i++)
                        {
                            try
                            {
                                if (mapping.CardType == IowCardNames.IowCardUniSwitch)
                                {
                                    this.ioWarrior.ExecuteCommand(mapping.CardType, mapping.CardCommand + "/" + delay);
                                }
                                if (mapping.CardType == IowCardNames.IowCardMatrix_16x16)
                                {
                                    if (mapping.CardCommand.ToLower().StartsWith("press:uni"))
                                    {
                                        // Execute uni key press
                                        if (delay > 100)
                                        {
                                            this.log.Debug(mapping.CardCommand);
                                            string uniKey = mapping.CardCommand.Substring(mapping.CardCommand.LastIndexOf("=") + 1);
                                            this.log.Debug("unikey = " + uniKey);
                                            this.ioWarrior.ExecuteCommand(mapping.CardType, "close:uni=" + uniKey);
                                            Thread.Sleep(delay);
                                            this.ioWarrior.ExecuteCommand(mapping.CardType, "open:uni=" + uniKey);
                                        }
                                        else
                                        {
                                            this.ioWarrior.ExecuteCommand(mapping.CardType, mapping.CardCommand);
                                        }
                                    }
                                    if (mapping.CardCommand.ToLower().StartsWith("open:uni") ||
                                        mapping.CardCommand.ToLower().StartsWith("close:uni"))
                                    {
                                        this.ioWarrior.ExecuteCommand(mapping.CardType, mapping.CardCommand);
                                    }
                                    if (mapping.CardCommand.ToLower().StartsWith("press:key=r"))
                                    {
                                        // Execute card matrix command
                                        this.ioWarrior.ExecuteCommand(mapping.CardType,
                                                                      mapping.CardCommand + "/" + delay);
                                    }
                                }
                                else if (mapping.CardType == IowCardNames.IowCardMatrix_5x6 ||
                                         mapping.CardType == IowCardNames.IowCardMatrix_4x7)
                                {
                                    if (mapping.CardCommand.ToLower().StartsWith("press:key=r"))
                                    {
                                        // Execute card matrix command
                                        this.ioWarrior.ExecuteCommand(mapping.CardType,
                                                                      mapping.CardCommand + "/" + delay);
                                    }
                                }
                                else if (mapping.CardType == "Touch" &&
                                    this.cardMapping.TouchMapping.TouchControllerSettings.TouchControllerType == "TouchControllerCypressGen4" &&
                                    mapping.CardCommand.StartsWith("CapacitiveBack"))
                                {
                                    TouchControllerCypressGen4 touch = this.touchController as TouchControllerCypressGen4;
                                    if (touch != null)
                                    {
                                        return touch.CapacitiveBack(mapping.CardCommand.Contains("Ara"), delay);
                                    }
                                }
                                else if (mapping.CardType == "Touch" &&
                                    this.cardMapping.TouchMapping.TouchControllerSettings.TouchControllerType == "TouchControllerCypressGen4" &&
                                    mapping.CardCommand.StartsWith("CapacitiveHome"))
                                {
                                    TouchControllerCypressGen4 touch = this.touchController as TouchControllerCypressGen4;
                                    if (touch != null)
                                    {
                                        return touch.CapacitiveHome(mapping.CardCommand.Contains("Ara"), delay);
                                    }
                                }
                                break;

                            }
                            catch (FaultException e)
                            {
                                throw new FaultException(e.Message, e.Code);
                            }
                            catch (Exception ex)
                            {
                                this.log.Warn(ex.Message);
                                this.iowServiceClose();
                                this.iowServiceConnect();
                                if ((i == defaultRetriesOnError - 1) || this.constructorInit)
                                    throw new FaultException(ex.Message);
                            }
                        }
                        break;
                    }
                    throw new FaultException("No IoWarrior card found for command '" + key + "'" + ". Card of type " + mapping.CardType + "  expected.", 
                        new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
                }
            }

            if (!keyFound)
            {
                throw new FaultException("No IoWarrior card mapping found for command '" + key + "'" + ". Check your test script or add proper card mapping. See " + 
                    this.settingsHandler.SettingsFilePath, new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
            }

            return new TouchStateResponse();
        }

        /// <summary>
        /// Connects SIM card 1-6 or no SIM. 
        /// </summary>
        /// <param name="sim">Sim card to connect</param>
        public void ConnectSim(SimCard sim)
        {
            if (this.reInitIoWarriorRequired && !this.constructorInit)
            {
                try
                {
                    this.InitIoWarrior();
                }
                catch (Exception ex)
                {
                    this.log.Error("ConnectSim: " + sim + " --> Reinit IoWarrior was required but InitIoWarrior failed!", ex);
                }
            }
            this.log.Debug("ConnectSim: " + sim);
            if (this.iowCardsFound.Contains(IowCardNames.IowCardSim))
            {
                for (int i = 0; i < defaultRetriesOnError; i++)
                {
                    try
                    {
                        this.ioWarrior.ExecuteCommand(IowCardNames.IowCardSim, "close:sim=" + (int)sim);
                        break;
                    }
                    catch (FaultException e)
                    {
                        throw new FaultException(e.Message, e.Code);
                    }
                    catch (Exception ex)
                    {
                        this.log.Warn(ex.Message);
                        this.iowServiceClose();
                        this.iowServiceConnect();
                        if ((i == defaultRetriesOnError - 1) || this.constructorInit)
                            throw new FaultException(ex.Message);
                    }
                }
            }
            else
            {
                throw new FaultException("No IoWarrior card found for command 'ConnectSim(" + sim + ")'. Card of type IowCardSim expected.", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
            }
        }

        /// <summary>
        /// Connects memory cards A-D or no memory card. 
        /// </summary>
        /// <param name="memoryCard">Memory card to connect</param>
        public void ConnectMemoryCard(MemoryCard memoryCard)
        {
            if (this.reInitIoWarriorRequired && !this.constructorInit)
            {
                try
                {
                    this.InitIoWarrior();
                }
                catch (Exception ex)
                {
                    this.log.Error("ConnectMemoryCard: " + memoryCard + " --> Reinit IoWarrior was required but InitIoWarrior failed!", ex);
                }
            }
            this.log.Debug("ConnectMemoryCard: " + memoryCard);
            if (this.iowCardsFound.Contains(IowCardNames.IowCarduSDSwitch))
            {
                for (int i = 0; i < defaultRetriesOnError; i++)
                {
                    try
                    {
                        this.ioWarrior.ExecuteCommand(IowCardNames.IowCarduSDSwitch, "connect:mmc=" + (int)memoryCard);
                        break;
                    }
                    catch (FaultException e)
                    {
                        throw new FaultException(e.Message, e.Code);
                    }
                    catch (Exception ex)
                    {
                        this.log.Warn(ex.Message);
                        this.iowServiceClose();
                        this.iowServiceConnect();
                        if ((i == defaultRetriesOnError - 1) ||  this.constructorInit)
                            throw new FaultException(ex.Message);
                    }
                }
            }
            else
            {
                throw new FaultException("No IoWarrior card found for command 'ConnectMemoryCard(" + memoryCard + ")'. Card of type IowCarduSDSwitch expected.", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
            }
        }

        /// <summary>
        /// Connects the USB accessory card default connector to phone. E.g
        /// Connects USB cable connected to accessory card port 1 from PC to accessory card output.
        /// </summary>
        public bool ConnectDefaultUsbAccessoryConnector()
        {
            this.log.Debug("ConnectDefaultUsbAccessoryConnector");
            if (this.Settings.General.DefaultUsbAccessoryConnector.ToString() != string.Empty)
            {
                ConnectUsb(this.Settings.General.DefaultUsbAccessoryConnector);
                return true;
            }
            return false;
        }

        /// <summary>
        /// Connects USB port 1-4 or no USB port. 
        /// </summary>
        /// <param name="usbPort">USB to connect</param>
        public void ConnectUsb(UsbPort usbPort)
        {
            if (this.reInitIoWarriorRequired && !this.constructorInit)
            {
                try
                {
                    this.InitIoWarrior();
                }
                catch (Exception ex)
                {
                    this.log.Error("ConnectUsb: " + usbPort + " --> Reinit IoWarrior was required but InitIoWarrior failed!", ex);
                }
            }
            this.log.Debug("ConnectUsb: " + usbPort);

            // Check whether UniSwitch used to controll the USB
            string command = string.Empty;
            string cardType = string.Empty;

            if (usbPort == UsbPort.None)
            {
                foreach (CommandMapping mapping in this.cardMapping.CommandMappings.Where(mapping => mapping.MarbleCommand == disconnectUsbCommand))
                {
                    command = mapping.CardCommand;
                    cardType = mapping.CardType;
                    break;
                }
            }
            else
            {
                foreach (CommandMapping mapping in this.cardMapping.CommandMappings.Where(mapping => mapping.MarbleCommand == connectUsbCommand))
                {
                    command = mapping.CardCommand;
                    cardType = mapping.CardType;
                    break;
                }
            }
            if (!string.IsNullOrEmpty(command))
            {
                for (int i = 0; i < defaultRetriesOnError; i++)
                {
                    try
                    {
                        this.ioWarrior.ExecuteCommand(cardType, command);
                        break;
                    }
                    catch (FaultException e)
                    {
                        throw new FaultException(e.Message, e.Code);
                    }
                    catch (Exception ex)
                    {
                        this.log.Warn(ex.Message);
                        this.iowServiceClose();
                        this.iowServiceConnect();
                        if ((i == defaultRetriesOnError - 1) || this.constructorInit)
                            throw new FaultException(ex.Message);
                    }
                }

                if (usbPort != UsbPort.None)
                    usbPort = UsbPort.Usb1;
            }
            else
            {
                for (int i = 0; i < defaultRetriesOnError; i++)
                {
                    try
                    {
                        if (this.usbAccessoryCard == IowCardNames.IowCardUSBAccessory)
                        {
                            this.ioWarrior.ExecuteCommand(IowCardNames.IowCardUSBAccessory, "connect:usb=" + (int)usbPort);
                        }
                        else if (this.usbAccessoryCard == IowCardNames.IowCardAccessory)
                        {
                            if (usbPort == UsbPort.None)
                            {
                                this.ioWarrior.ExecuteCommand(IowCardNames.IowCardAccessory, "disconnect:acc=all");
                            }
                            else if (usbPort == UsbPort.Usb1 || usbPort == UsbPort.Usb2)
                            {
                                this.ioWarrior.ExecuteCommand(IowCardNames.IowCardAccessory, "connect:acc=" + (int)usbPort);
                            }
                            else
                            {
                                throw new FaultException("IowCardAccessory: Card HW cannot support command 'ConnectUsb(" +
                                                         usbPort + ")'");
                            }
                        }
                        else if (this.usbAccessoryCard == IowCardNames.IowCardFlash)
                        {
                            if (usbPort == UsbPort.None)
                            {
                                this.ioWarrior.ExecuteCommand(IowCardNames.IowCardFlash, "open:flash=all");
                            }
                            else if (usbPort == UsbPort.Usb1)
                            {
                                this.ioWarrior.ExecuteCommand(IowCardNames.IowCardFlash, "close: flash");
                            }
                            else
                            {
                                throw new FaultException(
                                    "IowCardFlash (modified to be used as USB Switch card): Card HW cannot support command 'ConnectUsb(" +
                                    usbPort + ")'", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
                            }
                        }
                        break;
                    }
                    catch (FaultException e)
                    {
                        throw new FaultException(e.Message, e.Code);
                    }
                    catch (Exception ex)
                    {
                        this.log.Warn(ex.Message);
                        this.iowServiceClose();
                        this.iowServiceConnect();
                        if ((i == defaultRetriesOnError - 1) || this.constructorInit)
                            throw new FaultException(ex.Message);
                    }
                }
            }

            this.Settings.General.CurrentUsbAccessoryConnector = usbPort.ToString();
            this.settingsHandler.SaveSettings();
        }

        /// <summary>
        /// Connects AV plug port 1-4 or no AV port. 
        /// </summary>
        /// <param name="avPlugPort">AV plug to connect</param>
        public void ConnectAvPlug(AvPlug avPlugPort)
        {
            if (this.reInitIoWarriorRequired && !this.constructorInit)
            {
                try
                {
                    this.InitIoWarrior();
                }
                catch (Exception ex)
                {
                    this.log.Error("ConnectAvPlug: " + avPlugPort + " --> Reinit IoWarrior was required but InitIoWarrior failed!", ex);
                }
            }
            this.log.Debug("ConnectAvPlug: " + avPlugPort);
            if (this.iowCardsFound.Contains(IowCardNames.IowCardUSBAccessory))
            {
                for (int i = 0; i < defaultRetriesOnError; i++)
                {
                    try
                    {
                        this.ioWarrior.ExecuteCommand(IowCardNames.IowCardUSBAccessory, "connect:av=" + (int)avPlugPort);
                        break;
                    }
                    catch (FaultException e)
                    {
                        throw new FaultException(e.Message, e.Code);
                    }
                    catch (Exception ex)
                    {
                        this.log.Warn(ex.Message);
                        this.iowServiceClose();
                        this.iowServiceConnect();
                        if ((i == defaultRetriesOnError - 1) || this.constructorInit)
                            throw new FaultException(ex.Message);
                    }
                }
            }
            else
            {
                throw new FaultException("No IoWarrior card found for command 'ConnectAvPlug(" + avPlugPort + ")'. Card of type IowCardUSBAccessory expected.", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
            }
        }

        /// <summary>
        /// Generates a touch even on the Touch Panel Controller.
        /// Either a press or a move event
        /// </summary>
        /// <param name="marbleTouchData"></param>
        public TouchStateResponse TouchEvent(List<MarbleTouchData> marbleTouchData)
        {
            if (this.Settings.General.TouchCard.EmulationEnabled)
            {
                if (touchController == null)
                {
                    this.InitTouch();
                }
                else
                    return touchController.Move(marbleTouchData);
            }

            return new TouchStateResponse();
        }

        /// <summary>
        /// Sets orientation of DUT with Accelerometer card.
        /// Commands: Portrait, Landscape
        /// </summary>
        /// <param name="orientation"></param>
        public void SetOrientation(string orientation)
        {
            this.log.Debug("SetOrientation: " + orientation);
            if (this.Settings.General.AccelerometerCard.EmulationEnabled)
            {
                try
                {
                    new AccelerometerAqua(Settings.General.AccelerometerCard.SerialPort, orientation);
                }
                catch (Exception e)
                {
                    throw new FaultException(e.Message);
                }
            }
        }

        /// <summary>
        /// Checkt that given cards are found by IoWarrior device and cards are properly initialized.
        /// </summary>
        public void CheckIoWarriorCards()
        {
            this.log.Debug("CheckIoWarriorCards");
            
            // No checking whether all the cards are found if running in developer mode.
            if (this.Settings.General.DeveloperMode)
            {
                cardsRequiredFound = true;
                return;
            }

            // Check battery cards
            if (string.IsNullOrEmpty(this.batteryCard) && !this.marblebatCardWithUniSwitchInUse)
            {
                // 30.01.2014: For Aol it is agreed that Charger V4 / IowCardChargerWithBatteryV2 will be used 
                //throw new FaultException("No Battery card required for testing was found. Check your HW configuration!" + Environment.NewLine +
                //                         "Card of type IowCardBsiSimSwitch, IowCardBsiSimSwitchV1, IowCardChargerWithBattery or IowCardChargerWithBatteryV2 expected.", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
                throw new FaultException("Charger V4 / IowCardChargerWithBatteryV2 card required for testing was not found. Check your HW configuration!", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
            }

            int countBatteryCard = 0;
            if (this.iowCardsFound.Contains(IowCardNames.IowCardBsiSimSwitch))
            {
                countBatteryCard++;
            }
            else if (this.iowCardsFound.Contains(IowCardNames.IowCardBsiSimSwitchV1))
            {
                countBatteryCard++;
            }
            else if (this.iowCardsFound.Contains(IowCardNames.IowCardChargerWithBattery))
            {
                countBatteryCard++;
            }
            else if (this.iowCardsFound.Contains(IowCardNames.IowCardChargerWithBatteryV2))
            {
                countBatteryCard++;
            }

            if (countBatteryCard > 1)
            {
                // 30.01.2014: For Aol it is agreed that Charger V4 / IowCardChargerWithBatteryV2 will be used 
                //throw new FaultException("More than one BSI or Battery card connected to BlackBox. Check your HW configuration!" + Environment.NewLine +
                //                         "One card of type IowCardBsiSimSwitch, IowCardBsiSimSwitchV1, IowCardChargerWithBattery or IowCardChargerWithBatteryV2 expected.", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
                throw new FaultException("More than one BSI or Battery card connected to BlackBox. Check your HW configuration!" + Environment.NewLine +
                                         "One card of type Charger V4 / IowCardChargerWithBatteryV2 expected.", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
            }

            // Check USB cards
            if (string.IsNullOrEmpty(this.usbAccessoryCard) && !this.usbCardWithUniSwitchInUse)
            {
                // 30.01.2014: For Aol it is agreed that USB-Accessory Card V1.1 / IowCardUSBAccessory will be used
                //throw new FaultException("No USB Accessory card required for testing was found. Check your HW configuration!" + Environment.NewLine +
                //                         "Card of type IowCardUSBAccessory, IowCardAccessory or IowCardFlash (modified to be used as USB Switch card) expected.", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));

                throw new FaultException("No USB Accessory card required for testing was found. Check your HW configuration!" + Environment.NewLine +
                                         "Card of type USB-Accessory Card V1.1 / IowCardUSBAccessory expected.", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
            }

            int countUsbCard = 0;
            if (this.iowCardsFound.Contains(IowCardNames.IowCardUSBAccessory))
            {
                countUsbCard++;
            }
            else if (this.iowCardsFound.Contains(IowCardNames.IowCardAccessory))
            {
                countUsbCard++;
            }
            else if (this.iowCardsFound.Contains(IowCardNames.IowCardFlash))
            {
                countUsbCard++;
            }

            if (countUsbCard > 1)
            {
                // 30.01.2014: For Aol it is agreed that USB-Accessory Card V1.1 / IowCardUSBAccessory will be used
                //throw new FaultException("More than one USB Accessory card connected to BlackBox. Check your HW configuration!" + Environment.NewLine +
                //                         "One card of type IowCardUSBAccessory, IowCardAccessory or IowCardFlash (modified to be used as USB Switch card) expected.", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
                throw new FaultException("More than one USB Accessory card connected to BlackBox. Check your HW configuration!" + Environment.NewLine +
                         "One card of type USB-Accessory Card V1.1 / IowCardUSBAccessory expected.", new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
            }

            List<string> neededCardsNotFound = this.cardMapping.IoWCardsRequired.Where(requiredCard => !this.iowCardsFound.Contains(requiredCard)).ToList();

            if (neededCardsNotFound.Count >= 1)
            {
                string errorString = string.Empty;
                if (neededCardsNotFound.Count == 1)
                {
                    errorString += "IoWarrior card " + neededCardsNotFound[0];
                }
                else
                {
                    errorString += "IoWarrior cards ";
                    errorString = neededCardsNotFound.Aggregate(errorString,
                                                                (current, neededCard) =>
                                                                current + (neededCard + ", "));
                    errorString = errorString.Remove(errorString.LastIndexOf(','));
                }

                errorString += " required for testing not found!";
                cardsRequiredFound = false;
                throw new FaultException(errorString, new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
            }
            cardsRequiredFound = true;
        }

        // Dummy method for keeping this class backward compatible
        public void InitIoWarrior(bool grayboxEnabled)
        {
            this.InitIoWarrior();
        }

        /// <summary>
        /// Initializes all the IoWarrior cards
        /// </summary>
        public void InitIoWarrior()
        {
            if (!this.isIoWarriorServiceRunning)
                this.iowServiceConnect();

            if (((IServiceChannel)this.ioWarrior).State != CommunicationState.Opened)
                this.iowServiceClose();
                this.iowServiceConnect();

            this.log.Debug("InitIoWarrior");
            try
            {
                this.iowCardsFound = new List<string>();

                // Check for required SwitchCard
                List<string> requiredSwitchCards = new List<string>();
                if (!this.Settings.General.DeveloperMode)
                {
                    if (this.cardMapping != null)
                    {
                        foreach (CommandMapping mapping in this.cardMapping.CommandMappings)
                        {
                            if (!requiredSwitchCards.Contains(mapping.CardType) && mapping.CardType != "Touch")
                            {
                                requiredSwitchCards.Add(mapping.CardType);
                            }
                        }
                    }

                    foreach (string requiredSwitchCard in requiredSwitchCards)
                    {
                        if (!this.cardMapping.IoWCardsRequired.Contains(requiredSwitchCard))
                        {
                            this.cardMapping.IoWCardsRequired.Add(requiredSwitchCard);
                        }
                    }
                }
                else
                {
                    this.cardMapping.IoWCardsRequired.Clear();
                }

                this.iowCardsFound = this.ioWarrior.InitIoWarrior(this.cardMapping.IoWCardsRequired, this.marblebatCardWithUniSwitchInUse, this.usbCardWithUniSwitchInUse, this.Settings.General.DeveloperMode);
                this.initIoWarriorCards();
                this.reInitIoWarriorRequired = false;
            }
            catch (FaultException e)
            {
                throw new FaultException(e.Message, e.Code);
            }
            catch (Exception ex)
            {
                throw new FaultException(ex.Message);
            }
            try
            {
                this.ExecuteHwOperation(BlackBoxServiceSettings.DisconnectHeadsetCommand);
            }
            catch{ /* No actions required. */}
        }

        /// <summary>
        /// Resets IoWarrior by closing/reopening the HW
        /// </summary>
        /// <param name="resetAndExit">If set to true, resets IoWarrior by exiting the IoWarrior service process</param>
        public void ResetIoWarrior(bool resetAndExit = false)
        {
            this.log.Debug("ResetIoWarrior(resetAndExit = " + resetAndExit + ")");
            if (!resetAndExit)
            {
                try
                {
                    this.ioWarrior.ResetIoWarrior();
                }
                catch (FaultException e)
                {
                    throw new FaultException(e.Message, e.Code);
                }
                catch (Exception ex)
                {
                    throw new FaultException(ex.Message);
                }
            }
            else
            {
                try
                {
                    this.closeIoWarriorAndExit();
                }
                catch (FaultException e)
                {
                    throw new FaultException(e.Message, e.Code);
                }
                catch (Exception ex)
                {
                    throw new FaultException(ex.Message);
                }
                try
                {
                    this.ioWarrior.InitIoWarrior(this.cardMapping.IoWCardsRequired, this.marblebatCardWithUniSwitchInUse, this.usbCardWithUniSwitchInUse, this.Settings.General.DeveloperMode);
                }
                catch (FaultException e)
                {
                    throw new FaultException(e.Message, e.Code);
                }
                catch (Exception ex)
                {
                    throw new FaultException(ex.Message);
                }
            }
        }

        public void ClearRequirements()
        {
            this.log.Debug("ClearRequirements");
            this.cardMapping.IoWCardsRequired.Clear();
            this.settingsHandler.SaveSettings();

            bool abort = false;
            Action a = () =>
            {
                while (true)
                {
                    if (abort)
                        break;
                    this.log.Info("Shutting down IoWarriorService...");
                    var processes = Process.GetProcessesByName("IoWarriorService");
                    if (processes.Length == 1)
                    {
                        processes[0].Kill();
                        processes[0].Close();
                        processes[0].Dispose();
                        Thread.Sleep(500);
                    }
                    else
                    {
                        break;
                    }
                } 
            };
            Task task = Task.Factory.StartNew(a);
                
            //Wait for action to complete
            if (!task.Wait(15000))
            {
                abort = true;
            }
            if (abort)
            {
                this.log.Error("Killing IoWarriorService failed withing 15 seconds!");
            }
        }

        public void SetDefaultUsbAccessoryConnector(UsbPort port)
        {
            this.log.Debug("SetDefaultUsbAccessoryConnector: " + port);
            try
            {
                this.Settings.General.DefaultUsbAccessoryConnector = port;
                this.ConnectDefaultUsbAccessoryConnector();
                this.settingsHandler.SaveSettings();
            }
            catch (FaultException e)
            {
                throw new FaultException(e.Message, e.Code);
            }
            catch (Exception ex)
            {
                throw new FaultException(ex.Message);
            }
        }

        public void DisconnectUsb()
        {
            this.ConnectUsb(UsbPort.None);
        }

        public void PhoneModelSelected(string phoneModel)
        {
            this.log.Debug("PhoneModelSelected: " + phoneModel);
            this.CloseAll();
            this.batteryCard = string.Empty;
            this.usbAccessoryCard = string.Empty;
            this.useCardMapping(phoneModel);
            this.Settings.General.PhoneModel = phoneModel;
            this.cardsRequiredFound = false;
        }

        public List<string> DetectEmulationCards()
        {
            List<string> portList = new List<string>();
            using (var searcher = new ManagementObjectSearcher("SELECT * FROM Win32_PnPEntity")) //For searching "real" serial ports: "SELECT * FROM WIN32_SerialPort"
            {                                                                                    //Note: does not find USB serial ports.
                List<ManagementBaseObject> ports = null;
                try
                {
                    ports = searcher.Get().Cast<ManagementBaseObject>().ToList();
                }
                catch (Exception ex)
                {
                    log.Error("DetectEmulationCards failed", ex);
                }
                if (ports != null)
                {
                    foreach (var port in ports)
                    {
                        try
                        {
                            string portString = port["Caption"].ToString();
                            if (portString.ToLower().Contains("usb serial port") &&
                                port["DeviceID"].ToString().Contains("FTDIBUS"))
                            {
                                int startIndex = portString.IndexOf('(');
                                int endIndex = portString.IndexOf(')');
                                string parsed = portString.Substring(startIndex + 1, endIndex - startIndex - 1);
                                portList.Add(parsed.ToUpper());
                            }
                        }
                        catch (Exception e)
                        {
                            log.Error("DetectEmulationCards failed", e);
                        }
                    }
                }
            }

            return portList;
        }

        public void TouchSetComPort(string comPort)
        {
            if (this.Settings.General.TouchCard.SerialPort != null && this.Settings.General.TouchCard.SerialPort != comPort)
            {
                this.CloseTouch();
                this.Settings.General.TouchCard.SerialPort = comPort;
                this.settingsHandler.SaveSettings();
                App.setPersistentSettings();
                if (this.Settings.General.TouchCard.EmulationEnabled && !string.IsNullOrEmpty(this.Settings.General.TouchCard.SerialPort))
                    this.InitTouch();
            }
        }

        public void TouchSetEnabled(bool enabled)
        {
            if (this.Settings.General.TouchCard.EmulationEnabled != enabled)
            {
                this.Settings.General.TouchCard.EmulationEnabled = enabled;
                this.settingsHandler.SaveSettings();
                App.setPersistentSettings();
                if (this.Settings.General.TouchCard.EmulationEnabled)
                    this.InitTouch();
                else
                   this.CloseTouch();
            }
        }

        public void AccelerometerSetComPort(string comPort)
        {
            if (this.Settings.General.AccelerometerCard.SerialPort != comPort)
            {
                this.CloseAccelerometer();
                this.Settings.General.AccelerometerCard.SerialPort = comPort;
                this.settingsHandler.SaveSettings();
                if (this.Settings.General.AccelerometerCard.EmulationEnabled && !string.IsNullOrEmpty(this.Settings.General.AccelerometerCard.SerialPort))
                    this.InitAccelerometer();
            }
        }

        public void AccelerometerSetEnabled(bool enabled)
        {
            if (this.Settings.General.AccelerometerCard.EmulationEnabled != enabled)
            {
                this.Settings.General.AccelerometerCard.EmulationEnabled = enabled;
                this.settingsHandler.SaveSettings();
                if (this.Settings.General.AccelerometerCard.EmulationEnabled)
                    this.InitAccelerometer();
                else
                    this.CloseAccelerometer();
            }
        }

        public List<CommandMapping> CommandMapping
        {
            get { return this.cardMapping.CommandMappings; }
        }

        public List<string> IoWarriorCardsRequiredForTesting
        {
            get { return this.cardMapping.IoWCardsRequired; }
        }

        public List<string> ProductVariants
        {
            get
            {
                return this.cardMapping.ProductVariant;
            }
        }

        public List<string> IoWarriorCardsFound
        {
            get
            {
                return this.iowCardsFound;
            }
        }

        public List<string> UsbAccessoryPortsAvailable
        {
            get
            {
                List<string> l = new List<string>();

                // Check whether UniSwitch used to controll the USB
                bool uniSwitchUsb = false;
                foreach (CommandMapping mapping in this.cardMapping.CommandMappings)
                {
                    if (mapping.MarbleCommand == disconnectUsbCommand)
                    {
                        l.Add("None");
                        uniSwitchUsb = true;
                    }
                    else if (mapping.MarbleCommand == connectUsbCommand)
                    {
                        l.Add("Usb1");
                        uniSwitchUsb = true;
                    }
                }

                if (!uniSwitchUsb)
                {
                    if (this.usbAccessoryCard == IowCardNames.IowCardUSBAccessory)
                    {
                        // USBAccessoryCard supports switching between four USB ports
                        l.AddRange(from object port in Enum.GetValues(typeof(UsbPort)) select port.ToString());
                    }
                    else if (this.usbAccessoryCard == IowCardNames.IowCardAccessory)
                    {
                        // Old AccessoryCard supports switching between two USB ports
                        int i = 0;
                        foreach (var port in Enum.GetValues(typeof(UsbPort)))
                        {
                            if (i == 3)
                            {
                                break;
                            }
                            l.Add(port.ToString());
                            i++;
                        }
                    }
                    else if (this.usbAccessoryCard == IowCardNames.IowCardFlash)
                    {
                        // Modified Flash card supports only "switching" between None and USB1
                        int i = 0;
                        foreach (var port in Enum.GetValues(typeof(UsbPort)))
                        {
                            if (i == 2)
                            {
                                break;
                            }
                            l.Add(port.ToString());
                            i++;
                        }
                    }
                }
                if (l.Count == 0)
                {
                    l.Add("None");
                }
                l.Sort();
                return l;
            }
        }

        /// <summary>
        /// Internal method. To be run when BlackBoxService is closed manually by user.
        /// </summary>
        internal void closeIoWarriorAndExit()
        {
            FaultException exx = null;
            log.Info("Closing IoWarrior Service and killing the IoWarriorServiceHost.");
            try
            {
                this.ioWarrior.CloseIoWarrior();
            }
            catch (FaultException e)
            {
                exx = e;
            }
            catch (Exception ex)
            {
                exx = new FaultException(ex.Message);
            }
            finally
            {
                log.Info("IoWarrior closed. Killing IoWarriorServiceHost process.");
                var processes = Process.GetProcessesByName("IoWarriorService");
                if (processes.Length == 1)
                {
                    processes[0].Kill();
                    processes[0].Close();
                    processes[0].Dispose();
                }
                if (exx != null)
                {
                    throw exx;
                }
            }
        }

        #endregion

        #region IDisposable Methods

        public void Dispose()
        {
            this.CloseAll();
            this.disposing = true;
            this.iowServiceClose();
            this.disposing = false;
        }

        #endregion

        #region Private Methods

        private void initIoWarriorCards()
        {
            // 30.01.2014: For Aol it is agreed that Charger V4 / IowCardChargerWithBatteryV2, USB-Accessory Card V1.1 / IowCardUSBAccessory, JIG Uni switch V1 / IowCardUniSwitch will be used only
            // Add USB Accessory card
            if (this.iowCardsFound.Contains(IowCardNames.IowCardUSBAccessory))
            {
                this.usbAccessoryCard = IowCardNames.IowCardUSBAccessory;
            }
            //else if (this.iowCardsFound.Contains(IowCardNames.IowCardAccessory))
            //{
            //    this.usbAccessoryCard = IowCardNames.IowCardAccessory;
            //}
            //else if (this.iowCardsFound.Contains(IowCardNames.IowCardFlash))
            //{
            //    this.usbAccessoryCard = IowCardNames.IowCardFlash;
            //}

            // Add batterycard
            //if (this.iowCardsFound.Contains(IowCardNames.IowCardBsiSimSwitch))
            //{
            //    this.batteryCard = IowCardNames.IowCardBsiSimSwitch;
            //}
            //else if (this.iowCardsFound.Contains(IowCardNames.IowCardBsiSimSwitchV1))
            //{
            //    this.batteryCard = IowCardNames.IowCardBsiSimSwitchV1;
            //}
            //else if (this.iowCardsFound.Contains(IowCardNames.IowCardChargerWithBattery))
            //{
            //    this.batteryCard = IowCardNames.IowCardChargerWithBattery;
            //}
            if (this.iowCardsFound.Contains(IowCardNames.IowCardChargerWithBatteryV2))
            {
                this.batteryCard = IowCardNames.IowCardChargerWithBatteryV2;
            }

            bool cardAdded = false;
            // Update cards required
            foreach (string cardFound in this.iowCardsFound)
            {
                if (!this.cardMapping.IoWCardsRequired.Contains(cardFound))
                {
                    this.cardMapping.IoWCardsRequired.Add(cardFound);
                    cardAdded = true;
                }
            }

            if (cardAdded)
                this.settingsHandler.SaveSettings();
        }

        /// <summary>
        /// Takes in use the command mappings from settings class according to given phone model
        /// </summary>
        /// <param name="phoneModel"></param>
        private void useCardMapping(string phoneModel)
        {
            if (string.IsNullOrEmpty(phoneModel))
            {
                throw new FaultException("Error: Phone model parameter cannot be null or empty!");
            }

            if (this.Settings == null)
            {
                throw new FaultException("Error: BlackBox settings has not been loaded from xml. Load settings first before trying to use them!");
            }

            List<PhoneModelCardMapping> foundModelMapping = new List<PhoneModelCardMapping>();
            foreach (PhoneModelCardMapping cardCommandsMapping in this.Settings.PhoneModelCardMappings)
            {
                if (cardCommandsMapping.PhoneModel == phoneModel || cardCommandsMapping.ProductVariant.Contains(phoneModel))
                {
                    foundModelMapping.Add(cardCommandsMapping);
                }
            }

            if (foundModelMapping.Count == 1)
            {
                cardMapping = foundModelMapping[0];
            }
            else
            {
                if (foundModelMapping.Count == 0)
                {
                    string message = "Error: Command mapping for the given phone model: " + phoneModel;
                    message += " was not found. Check " + this.settingsHandler.SettingsFilePath;
                    throw new FaultException(message);
                }
                if (foundModelMapping.Count > 1)
                {
                    string message = "Error: More than one command mapping for the given phone model: " + phoneModel;
                    message += " was found. Check " + this.settingsHandler.SettingsFilePath;
                    throw new FaultException(message);
                }
            }
        }
        
        private void capacitiveBackPress(string x, string y, int delay)
        {
            List<MarbleTouchData> touchData = new List<MarbleTouchData>();
            touchData.Add(new MarbleTouchData("press", x, y, "0", delay.ToString()));
            touchData.Add(new MarbleTouchData("release", x, y, "0", "0"));
            this.TouchEvent(touchData);
        }

        // OLD STUFF THAT CANNOT BE USED NOW DUE TO TOO ATMEL CARDS USED SIMULTANEOUSLY
        ///// <summary>
        ///// Autodetect serial port of touch controller
        ///// </summary>
        //private string autoDetectSerialPort(string controllerName, string serialPort, int latencyTimer)
        //{
        //    List<string> portList = new List<string>();
        //    using (var searcher = new ManagementObjectSearcher("SELECT * FROM Win32_PnPEntity")) //For searching "real" serial ports: "SELECT * FROM WIN32_SerialPort"
        //    {                                                                                    //Note: does not find USB serial ports.
        //        var ports = searcher.Get().Cast<ManagementBaseObject>().ToList();
        //        foreach (var port in ports)
        //        {
        //            try
        //            {
        //                string portString = port["Caption"].ToString();
        //                if (portString.ToLower().Contains("usb serial port") && port["DeviceID"].ToString().Contains("FTDIBUS"))
        //                {
        //                    int startIndex = portString.IndexOf('(');
        //                    int endIndex = portString.IndexOf(')');
        //                    string parsed = portString.Substring(startIndex + 1, endIndex - startIndex - 1);
        //                    portList.Add(parsed.ToUpper());
        //                }
        //            }
        //            catch
        //            {
        //            }
        //        }
        //    }

        //    if (portList.Count == 0)
        //    {
        //        throw new FaultException(controllerName + " Touch Controller device was not found. USB cable disconnected or USB-->Serial driver not installed or driver malfunctioning!");
        //    }
        //    if (portList.Count > 1)
        //    {
        //        if (string.IsNullOrEmpty(serialPort))
        //        {
        //            throw new FaultException("Unable to autodetect " + controllerName + " Touch Controller serial port. Define the 'PortName' parameter by hand. E.g. 'PortName=\"COM7\"' See " + this.settingsHandler.SettingsFilePath);
        //        }
        //    }
        //    else
        //    {
        //        serialPort = portList[0];
        //    }

        //    // Check for proper LatencyTimer value. FTDIBUS driver stores the value in
        //    // HKLM\System\CurrentControlSet\Enum\FTDIBUS\VID_0403+PID_6001+A8003Ub1A\0000\Device Parameters\LatencyTimer
        //    // DeviceID may not be the same for this driver in every PC, so read it from the registry using serial port number:
        //    // E.g. string deviceID = deviceIdByPortName("COM2");
        //    string id = deviceIdByPortName(serialPort);
        //    if (id != null)
        //    {
        //        string keyPath = @"System\CurrentControlSet\Enum\" + id + @"\Device Parameters\";

        //        RegistryKey deviceParametersKey = Registry.LocalMachine.OpenSubKey(keyPath, true);
        //        if (deviceParametersKey != null)
        //        {
        //            object obj = deviceParametersKey.GetValue("LatencyTimer");
        //            if (obj != null)
        //            {
        //                int currValue = int.Parse(obj.ToString());
        //                if (currValue != latencyTimer)
        //                {
        //                    deviceParametersKey.SetValue("LatencyTimer", latencyTimer);
        //                }
        //            }
        //            deviceParametersKey.Close();
        //        }
        //    }
        //    else
        //    {
        //        throw new FaultException(controllerName + " Touch Controller device was not found. USB cable disconnected or USB-->Serial driver not installed or driver malfunctioning!");
        //    }
        //    return serialPort;
        //}

        ///// <summary>
        ///// Gets the device ID of the USB-->Serial Port converter in the given port
        ///// </summary>
        ///// <param name="portName"></param>
        ///// <returns>The device ID</returns>
        //private string deviceIdByPortName(string portName)
        //{
        //    string deviceId = null;
        //    using (var searcher = new ManagementObjectSearcher("SELECT * FROM Win32_PnPEntity"))
        //    {
        //        var ports = searcher.Get().Cast<ManagementBaseObject>().ToList();
        //        foreach (var port in ports)
        //        {
        //            if (port["Caption"].ToString().Contains(portName))
        //            {
        //                deviceId = port["DeviceID"].ToString();
        //                break;
        //            }
        //        }
        //    }
        //    return deviceId;
        //}

        #endregion

        #region IClientKeepalive methods

        public bool ClientKeepalive()
        {
            // Just a dummy method for client side to call to keep the WCF connection alive
            return true;
        }

        #endregion
    }
}
