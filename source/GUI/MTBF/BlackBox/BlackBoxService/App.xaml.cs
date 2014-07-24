using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Reflection;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Forms;
using System.Xml.Serialization;
using TestAutomation.Gui.Marble.Drivers;
using TestAutomation.Gui.Marble.IPC.Interfaces;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;
using TestAutomation.Gui.Marble.IPC.Services;
using log4net;
using log4net.Config;
using Application = System.Windows.Application;
using MessageBox = System.Windows.MessageBox;

namespace BlackBoxService
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        #region Parameter class for storing persistent Marble BlackBox settings that should be kept between Marble releases

        public class BlackBoxPersistent
        {
            [XmlElement]
            public string ComPortTouch { get; set; }

            [XmlElement]
            public string ComPortAccelerometer { get; set; }

            public BlackBoxPersistent()
            {
                this.ComPortTouch = string.Empty;
                this.ComPortAccelerometer = string.Empty;
            }
        }

        #endregion

        // Log4net logger object.
        private static ILog log;
        private static MarbleWcfService service;
        internal static BlackBox blackBox;
        private static SettingsHandler settingsHandler;
        private static Mutex mutex;
        internal static NotifyIcon notifyIcon;
        private static BlackBoxServiceSettings settings
        {
            get { return settingsHandler.SettingsObject as BlackBoxServiceSettings; }
        }

        /// <summary>
        /// Static constructor for Assebly resolver use
        /// </summary>
        static App()
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

        public App()
        {
            notifyIcon = new NotifyIcon();
            // Crate settings handler and initialize log4net
            settingsHandler = new SettingsHandler(new BlackBoxServiceSettings());
            if (settings != null && settings.Logging != null)
            {
                XmlConfigurator.Configure(settings.Logging);
            }

            log = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
            log.Info("CurrentDirectory: " + Environment.CurrentDirectory);

            // Mutex will prevent an application to run twice
            bool mutexCreated;
            mutex = new Mutex(true, "BlackBoxService", out mutexCreated);
            if (!mutexCreated)
            {
                log.Info("BlackBox service was already running. Exiting process now.");
                Current.Shutdown();
            }
        }

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            checkPersistentSettings();
            setPersistentSettings();
            log.Info("Starting BlackBox WCF Services...");

            List<Tuple<Type, string>> endpoints = new List<Tuple<Type, string>>();
            endpoints.Add(new Tuple<Type, string>(typeof(IBlackBoxService), ServiceDefinitions.BlackBoxServiceEndpoint));
            endpoints.Add(new Tuple<Type, string>(typeof(IBlackBoxRemoteGuiService), ServiceDefinitions.BlackBoxRemoteGuiServiceEndpoint));

            blackBox = new BlackBox(settingsHandler);

            Task calc = Task.Factory.StartNew(() =>
            {
                service = new MarbleWcfService(blackBox, settings.ServicePort, endpoints);
            });

            try
            {
                if (!calc.Wait(10000))
                {
                    throw new AggregateException(new InvalidOperationException("ServiceHost failed to start within 10 seconds"));
                }
            }
            catch (AggregateException aex)
            {
                string error = "Create WCF service for BlackBox failed: " + Environment.NewLine + aex.InnerException.Message;
                log.Fatal(error, aex.InnerException);
                MessageBox.Show(error, "BlackBox Service Error", MessageBoxButton.OK, MessageBoxImage.Error);

                try
                {
                    blackBox.closeIoWarriorAndExit();
                }
                catch {/* No need to handle this exception due to we are closing anyway */}
                mutex.ReleaseMutex();
                Environment.Exit(1);
            }
        }

        private void Application_Exit(object sender, ExitEventArgs e)
        {
            notifyIcon.Visible = false;
            notifyIcon.Dispose();
            notifyIcon = null;
            try
            {
                blackBox.closeIoWarriorAndExit();
            }
            catch {/* No need to handle this exception due to we are closing anyway */}
            try
            {
                if (service != null)
                {
                    log.Info("Disposing BlackBox WCF service");
                    service.Dispose();
                    service = null;
                }
            }
            catch { /* Process is closing, no need to handle this exception */ }
            try
            {
                if (blackBox != null)
                {
                    log.Info("Disposing BlackBox");
                    blackBox.Dispose();
                }
            }
            catch { /* Process is closing, no need to handle this exception */ }

            log.Debug("BlackBox service Application_Exit");
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

        internal static void checkPersistentSettings()
        {
            if (settings != null)
            {
                string localAppData = null;
                try
                {
                    localAppData = Environment.GetEnvironmentVariable("LocalAppData");
                }
                catch (Exception ex)
                {
                    if (log != null)
                        log.Warn("checkPersistentSettings failed to GetEnvironmentVariable LocalAppData", ex);
                }

                if (localAppData != null)
                {
                    try
                    {
                        // If there is no definition for serialport for touch or for accelerometer defined in settings, check from "persistent" default settings path.
                        if (string.IsNullOrEmpty(settings.General.AccelerometerCard.SerialPort) ||
                            string.IsNullOrEmpty(settings.General.TouchCard.SerialPort))
                        {
                            BlackBoxPersistent x = new SettingsHandler(new BlackBoxPersistent(), localAppData +
                                                    @"\Nokia\Marble\BlackBoxPersistent.xml").SettingsObject as BlackBoxPersistent;
                            if (x != null)
                            {
                                if (!string.IsNullOrEmpty(x.ComPortAccelerometer) &&
                                    string.IsNullOrEmpty(settings.General.AccelerometerCard.SerialPort))
                                {
                                    settings.General.AccelerometerCard.SerialPort = x.ComPortAccelerometer;
                                    settingsHandler.SaveSettings();
                                }

                                if (!string.IsNullOrEmpty(x.ComPortTouch) &&
                                    string.IsNullOrEmpty(settings.General.TouchCard.SerialPort))
                                {
                                    settings.General.TouchCard.SerialPort = x.ComPortTouch;
                                    settingsHandler.SaveSettings();
                                }
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        if (log != null)
                            log.Warn("checkPersistentSettings failed to load settings from LocalAppData folder", ex);
                    }
                }
            }
        }

        internal static void setPersistentSettings()
        {
            if (settings != null)
            {
                string localAppData = null;
                try
                {
                    localAppData = Environment.GetEnvironmentVariable("LocalAppData");
                }
                catch (Exception ex)
                {
                    if (log != null)
                        log.Warn("setkPersistentSettings failed to GetEnvironmentVariable LocalAppData", ex);
                }


                if (localAppData != null)
                {
                    try
                    {

                        // If there is no definition for serialport for touch or for accelerometer defined in settings, check from "persistent" default settings path.
                        if (!string.IsNullOrEmpty(settings.General.AccelerometerCard.SerialPort) ||
                            !string.IsNullOrEmpty(settings.General.TouchCard.SerialPort))
                        {
                            SettingsHandler bbHandler = new SettingsHandler(new BlackBoxPersistent(),
                                                                            Environment.GetEnvironmentVariable(
                                                                                "LocalAppData") +
                                                                            @"\Nokia\Marble\BlackBoxPersistent.xml");
                            BlackBoxPersistent x = bbHandler.SettingsObject as BlackBoxPersistent;
                            if (x != null)
                            {
                                if (!string.IsNullOrEmpty(settings.General.AccelerometerCard.SerialPort))
                                {
                                    x.ComPortAccelerometer = settings.General.AccelerometerCard.SerialPort;
                                    bbHandler.SaveSettings();
                                }

                                if (!string.IsNullOrEmpty(settings.General.TouchCard.SerialPort))
                                {
                                    x.ComPortTouch = settings.General.TouchCard.SerialPort;
                                    bbHandler.SaveSettings();
                                }
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        if (log != null)
                            log.Warn("setPersistentSettings failed to save settings to LocalAppData folder", ex);
                    }
                }
            }
        }
    }
}
