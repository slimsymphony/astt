using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.ServiceModel;
using System.Threading;
using System.Threading.Tasks;
using TestAutomation.Gui.Marble.IPC.Interfaces;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon.Interfaces;
using Nokia.Iowarrior;
using log4net;
using log4net.Config;

namespace IoWarriorService
{
    class IoWarriorService
    {
        // Log4net logger object.
        private static ILog log;
        //private static MarbleWcfService service;
        private static IoWarriorHandler iowHandler;
        private static SettingsHandler settingsHandler;
        private static AutoResetEvent autoEvent;
        private static int serviceRunningCounter;
        private const int defaultRetriesOnError = 5;
        private static IoWarriorServiceSettings settings
        {
            get { return settingsHandler.SettingsObject as IoWarriorServiceSettings; }
        }

        /// <summary>
        /// Static constructor for Assebly resolver use
        /// </summary>
        static IoWarriorService()
        {
            // Set culture to en-us
            Thread.CurrentThread.CurrentCulture = GetCulture();
            Thread.CurrentThread.CurrentUICulture = GetCulture();
            // Get the current application path so that settings for the application are being loaded from correct folder.
            // If this process is started by another .NET process, Environment.CurrentDirectory will be the directory where ther mother process is started.
            Environment.CurrentDirectory = AppDomain.CurrentDomain.BaseDirectory;
            AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
        }

        private static Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            var assemblyname = new AssemblyName(args.Name).Name;
            var assemblyFileName = Path.Combine(@"..\..\framework\dlls\", assemblyname + ".dll");
            return Assembly.LoadFrom(assemblyFileName);
        }

        static void Main()
        {
            // Mutex will prevent an application to run twice
            bool mutexCreated;
            Mutex mutex = new Mutex(true, "IoWarriorService", out mutexCreated);

            // Crate settings handler and initialize log4net
            settingsHandler = new SettingsHandler(new IoWarriorServiceSettings());

            if (settings != null && settings.Logging != null)
            {
                XmlConfigurator.Configure(settings.Logging);
            }

            log = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
            if (mutexCreated)
            {
                log.Info("Starting IoWarrior WCF Service...");

                List<Tuple<Type, string>> endpoints = new List<Tuple<Type, string>>();
                endpoints.Add(new Tuple<Type, string>(typeof(IIoWarriorService), ServiceDefinitions.IoWarriorServiceEndpoint));
                iowHandler = new IoWarriorHandler();
                ServiceHost host = null;
                try
                {
                    host = new ServiceHost(iowHandler, new Uri(@"net.pipe://localhost/"));
                    NetNamedPipeBinding b = new NetNamedPipeBinding();
                    //b.ReceiveTimeout = TimeSpan.MaxValue;
                    host.AddServiceEndpoint(typeof(IIoWarriorService), b, "IoWarriorService");
                    log.Info("Adding Service Endpoint: net.pipe://localhost/IoWarriorService");

                    host.Faulted += new EventHandler(host_Faulted);
                    host.Closed += new EventHandler(host_Closed);
                    host.Opened += new EventHandler(host_Opened);
                    host.Open();
                }
                catch (Exception e)
                {
                    log.Fatal("Create WCF service for IoWarrior failed: " + Environment.NewLine + e.Message, e);
                    mutex.ReleaseMutex();
                    Environment.Exit(0);
                }

                // Create a timer that checks whether BlackBox service is running.
                // This check is here just to ensure that this process does not run forever
                // if it is not needed. In a normal situation, BlackBoxService should handle the closure
                // of this service

                serviceRunningCounter = 0;
                autoEvent = new AutoResetEvent(false);
                Timer timer = new Timer(checkStatus, autoEvent, 1000, 5000);
                
                // Wait for autoreset event to get signaled
                autoEvent.WaitOne();

                // Dispose resources and close IoWarrior
                timer.Dispose();
                host.Close();
                ((IDisposable)host).Dispose();
                new Nokia.Iowarrior.Devices.IowKit.IowKitWrapper().CloseAll();
                mutex.ReleaseMutex();
                log.Info("IoWarriorService Closed.");
            }
            else
            {
                log.Debug("IoWarrior was already running. Exiting process now.");
            }
        }

        static void host_Opened(object sender, EventArgs e)
        {
            log.Debug("SERVICE HOST OPENED");
        }

        static void host_Closed(object sender, EventArgs e)
        {
            log.Debug("SERVICE HOST CLOSED");
        }

        static void host_Faulted(object sender, EventArgs e)
        {
            new Nokia.Iowarrior.Devices.IowKit.IowKitWrapper().CloseAll();
            Environment.Exit(1);
        }

        private static void checkStatus(object o)
        {
            AutoResetEvent autoEvent = (AutoResetEvent)o;
            var processes = Process.GetProcessesByName("BlackBoxService");
            if (processes.Length == 0)
            {
                serviceRunningCounter++;
            }
            else
            {
                serviceRunningCounter = 0;
            }
            // If BlackBox service has not been running within one minute, it is time to also close this service.
            if (serviceRunningCounter >= 3)
            {
                log.Warn("BlackBoxService process has not been running for 15 seconds. Closing IoWarriorService.");
                autoEvent.Set();
            }
        }

        /// <summary>
        /// Ensure that proper culture specific settings are always used!
        /// We do not want to see any incorrect .ToString() and Double.Parse() behaviour related to
        /// DateTime or NumberDecimalSeparator.
        /// </summary>
        /// <returns>CultureInfo of en-US</returns>
        internal static CultureInfo GetCulture()
        {
            CultureInfo cultureInfo;
            NumberFormatInfo provider = new NumberFormatInfo
            {
                NumberDecimalSeparator = "."
            };
            cultureInfo = new CultureInfo("en-US")
            {
                DateTimeFormat =
                {
                    ShortDatePattern = "dd.MM.yyyy",
                    LongDatePattern = "dd.MM.yyyy",
                    ShortTimePattern = "HH:mm:ss",
                    LongTimePattern = "HH:mm:ss"
                },
                NumberFormat =
                {
                    NumberDecimalSeparator = provider.NumberDecimalSeparator
                }
            };

            return cultureInfo;
        }

        [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single, ConcurrencyMode = ConcurrencyMode.Single)]
        public class IoWarriorHandler : IIoWarriorService
        {
            private IowCardDictionary iowCardDictionary;
            private List<string> defaultIowCardsRequired;
            private bool batCardWithUniSwitchInUse;
            private bool usbCardWithUniSwitchInUse;
            private bool developerMode;

            public IoWarriorHandler()
            {
                this.iowCardDictionary = null;
                this.defaultIowCardsRequired = new List<string>();
            }

            public List<string> IoWarriorCardsFound
            {
                get
                {
                    List<string> l = new List<string>();
                    if (this.iowCardDictionary != null)
                    {
                        l.AddRange(this.iowCardDictionary.GetCards().Select(card => card.GetType().Name));
                    }
                    return l;
                }
            }

            public void ExecuteCommand(string card, string command)
            {
                for (int i = 0; i < defaultRetriesOnError; i++)
                {
                    try
                    {
                        IowCard iowCard = this.getCard(card);
                        if (iowCard != null)
                        {
                            iowCard.ExecuteCommand(command);
                            break;
                        }
                        else
                        {
                            throw new FaultException(
                                "ExecuteCommand(" + card + ", " + command + ") failed: card " + card + " was not found",
                                new FaultCode(ServiceDefinitions.IoWarriorConfigurationFault));
                        }
                    }
                    catch (Exception ex)
                    {
                        string errorString = "ExecuteCommand(" + card + ", " + command + ") failed: " + ex.Message;
                        log.Warn(errorString, ex);
                        if (i == defaultRetriesOnError -1)
                            throw new FaultException(errorString, new FaultCode(ServiceDefinitions.IoWarriorFault));
                    }
                }
            }

            public void ResetIoWarrior()
            {
                try
                {
                    this.CloseIoWarrior();
                }
                catch (Exception ex)
                {
                    log.Error("ResetIoWarrior: CloseIoWarrior failed!", ex);
                }
                try
                {
                    this.InitIoWarrior(this.defaultIowCardsRequired, this.batCardWithUniSwitchInUse, this.usbCardWithUniSwitchInUse, this.developerMode ,15);
                }
                catch (Exception ex)
                {
                    log.Error("ResetIoWarrior: ScanForIowDevices failed!", ex);
                    throw new FaultException("ResetIoWarrior failed: " + ex.Message, new FaultCode(ServiceDefinitions.IoWarriorFault));
                }
            }

            public List<string> InitIoWarrior(List<string> iowCardsRequired, bool batCardWithUniSwitchInUse, bool usbCardWithUniSwitchInUse, bool developerMode, int timeoutForScan = 20)
            {
                this.batCardWithUniSwitchInUse = batCardWithUniSwitchInUse;
                this.usbCardWithUniSwitchInUse = usbCardWithUniSwitchInUse;
                this.developerMode = developerMode;
                this.defaultIowCardsRequired = iowCardsRequired;
                bool abortScan = false;
                log.Debug("InitIoWarrior started");
                Action a = () =>
                {
                    while (true)
                    {
                        try
                        {
                            if (abortScan)
                                break;
                            if (iowCardDictionary != null)
                            {
                                this.CloseIoWarrior();
                            }

                            this.iowCardDictionary = null;
                            Action action = () => this.iowCardDictionary = new IowCardDictionary(new IowDeviceDictionary(true));
                            Task t = Task.Factory.StartNew(action);

                            //Wait for action to complete
                            if (!t.Wait(10000))
                            {
                                throw new FaultException("IoWarrior Error: No response received from IoWarrior driver within 10 seconds!", new FaultCode(ServiceDefinitions.IoWarriorFault));
                            }

                            if (abortScan)
                                break;
                            
                            if (this.iowCardDictionary.Count > 0)
                            {
                                // Check that no unknown cards were found
                                if (!this.unknownCardFound)
                                {
                                    // Check battery cards, switch cards, usb cards and also additional required cards e.g. SIMSwitchCard
                                    if (this.switchCardFound && this.batteryCardFound && this.usbCardFound && this.requiredCardFound(iowCardsRequired).Count == 0)
                                        break;
                                }
                            }
                        }
                        catch (Exception ex)
                        {
                            log.Error("ScanForIowDevices failed: " + ex.Message);
                            Thread.Sleep(1000);
                        }
                    }
                };
                Task task = Task.Factory.StartNew(a);

                //Wait for action to complete
                if (!task.Wait(timeoutForScan * 1000))
                {
                    abortScan = true;
                }
                if (abortScan)
                {
                    task.Wait();
                    string errorString = "IoWarrior Error: InitIoWarrior did not finish within " + timeoutForScan + " seconds.";

                    if (this.unknownCardFound)
                        errorString += Environment.NewLine + "Unknown IoWarrior cards found. Check that IoWarrior chip(s) are properly programmed with IoWarriorConfigurator SW.";

                    if (!this.developerMode)
                    {
                        if (!this.switchCardFound)
                        {
                            // 30.01.2014: For Aol it is agreed that JIG Uni switch V1 / IowCardUniSwitch will be used
                            errorString += Environment.NewLine + "JIG Uni switch V1 / IowCardUniSwitch card required for testing was not found. Check your HW configuration!";
                            //"No RelaySwitch card required for testing was found. Check your HW configuration!" +
                            //Environment.NewLine +
                            //"Card of type IowCardUniSwitch or IowCardMatrix_16x16 expected.";
                        }
                        if (!this.batteryCardFound)
                        {
                            // 30.01.2014: For Aol it is agreed that Charger V4 / IowCardChargerWithBatteryV2 will be used 
                            errorString += Environment.NewLine + "Charger V4 / IowCardChargerWithBatteryV2 card required for testing was not found. Check your HW configuration!";
                            //"No BSI or Battery card required for testing was found. Check your HW configuration!" +
                            //Environment.NewLine +
                            //"Card of type IowCardBsiSimSwitch, IowCardBsiSimSwitchV1, IowCardChargerWithBattery or IowCardChargerWithBatteryV2 expected.";
                        }
                        if (!this.usbCardFound)
                        {
                            // 30.01.2014: For Aol it is agreed that USB-Accessory Card V1.1 / IowCardUSBAccessory will be used
                            errorString += Environment.NewLine + "USB-Accessory Card V1.1 / IowCardUSBAccessory card required for testing was not found. Check your HW configuration!";
                            //errorString += Environment.NewLine +
                            //               "No USB Accessory card required for testing was found. Check your HW configuration!" +
                            //               Environment.NewLine +
                            //               "Card of type IowCardUSBAccessory, IowCardAccessory or IowCardFlash (modified to be used as USB Switch card) expected.";
                        }

                        List<string> requiredCardsNotFound = this.requiredCardFound(iowCardsRequired);
                        if (requiredCardsNotFound.Count > 0)
                        {
                            string cardList = string.Join(", ", requiredCardsNotFound.ToArray());
                            errorString += Environment.NewLine + cardList +
                                           " Card(s) required for testing was not found. Check your HW configuration!";
                        }
                    }
                    throw new FaultException(errorString, new FaultCode(ServiceDefinitions.IoWarriorFault));
                }

                log.Debug("scanForIowDevices executed, " + iowCardDictionary.Count + " devices found.");
                return this.IoWarriorCardsFound;
            }

            public void CloseIoWarrior()
            {
                log.Error("CloseIoWarrior()");
                new Nokia.Iowarrior.Devices.IowKit.IowKitWrapper().CloseAll();
                if (iowCardDictionary != null)
                {
                    iowCardDictionary.Clear();
                    this.iowCardDictionary = null;
                }
            }

            private IowCard getCard(string card)
            {
                if (iowCardDictionary != null)
                    return this.iowCardDictionary.GetCards().FirstOrDefault(iowcard => iowcard.GetType().Name == card);
                CloseIoWarrior();
                Environment.Exit(0);
                return null;
            }

            private bool batteryCardFound
            {
                get
                {
                    // If developer mode set, no cards are required
                    if (this.developerMode || this.batCardWithUniSwitchInUse)
                        return true;
                    // 30.01.2014: For Aol it is agreed that Charger V4 / IowCardChargerWithBatteryV2 will be used or Marble charger/pwr switch with UniSwitch controlling it used.
                    //return this.IoWarriorCardsFound.Any(iowCardFound => IowCardNames.BatteryCards.Any(batteryCard => iowCardFound == batteryCard) || iowCardFound == "IowCardUniSwitch" || iowCardFound == "IowCardMatrix_16x16");
                    return this.IoWarriorCardsFound.Any(iowCardFound => IowCardNames.BatteryCards.Any(batteryCard => iowCardFound == batteryCard));
                }
            }
            
            private bool switchCardFound
            {
                get
                {
                    // If developer mode set, no cards are required
                    if (this.developerMode)
                        return true;
                    return this.IoWarriorCardsFound.Any(iowCardFound => IowCardNames.SwitchCards.Any(switchCard => iowCardFound == switchCard));
                }
            }
            
            private bool usbCardFound
            {
                get
                {
                    // If developer mode set, no cards are required
                    if (this.developerMode || this.usbCardWithUniSwitchInUse)
                        return true;
                    return this.IoWarriorCardsFound.Any(iowCardFound => IowCardNames.UsbCards.Any(usbCard => iowCardFound == usbCard));
                }
            }

            private bool unknownCardFound
            {
                get
                {
                    return this.IoWarriorCardsFound.Any(iowCardFound => IowCardNames.UnknownCards.Any(unknownCard => iowCardFound == unknownCard));
                }
            }

            private List<string> requiredCardFound(List<string> iowCardsRequired)
            {
                List<string> requiredCardsNotFound = new List<string>();
                if (iowCardsRequired != null && iowCardsRequired.Count > 0)
                {
                    requiredCardsNotFound.AddRange(iowCardsRequired.Where(requiredCard => !this.IoWarriorCardsFound.Contains(requiredCard)));
                }

                return requiredCardsNotFound;
            }
        }
    }
}
