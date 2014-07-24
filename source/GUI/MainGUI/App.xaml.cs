using System;
using System.Diagnostics;
using System.IO;
using System.Management;
using System.Windows.Forms;
using Marble.ViewModel;
using log4net.Config;
using Application = System.Windows.Application;
using MessageBox = System.Windows.Forms.MessageBox;

namespace Marble
{
    using System.Globalization;
    using System.Threading;

    using Views.Dialogs;

    using MarbleLibrary.CustomControls;
    using MarbleLibrary.Utilities;

    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        /// <summary>
        /// A static view model.
        /// </summary>
        /// <returns>The MarbleMainViewModel object.</returns>
        private static MarbleMainViewModel marbleViewModel;

        /// <summary>
        /// ManagementEventWatcher object to detect USB device removals.
        /// </summary>
        private static ManagementEventWatcher usbRemovedWatcher;

        /// <summary>
        /// ManagementEventWatcher object to detect USB device insertions.
        /// </summary>
        private static ManagementEventWatcher usbInsertedWatcher;
        
        public static MarbleMainViewModel ViewModel
        {
            get { return marbleViewModel; }
        }

        internal static SimManagerViewModel SimManagerViewModel { get; private set; }

        internal static FlasherViewModel FlasherViewModel { get; private set; }

        internal static BlackBoxViewModel BlackBoxViewModel { get; private set; }

        internal static QcSettingsViewModel QcSettingsViewModel { get; private set; }

        public App()
        {
            try
            {
                initializeCultureInfos();

                // Initialize log4net
                XmlConfigurator.Configure(new FileInfo(@"..\settings\MarbleGuiLogSettings.xml"));

                showSplashScreen();

                MarblePaths.CheckAllMarbleDirectories();

                MarblePaths.CheckAllMarbleDirectories();
                marbleViewModel = new MarbleMainViewModel();
                
                // Subscribe eventhandlers
                addInsetUSBHandler();
                addRemoveUSBHandler();
            }
            catch (Exception ex)
            {
                showErrorDialog(ex);
            }
        }

        internal static void createViewModels()
        {
            try
            {
                SimManagerViewModel = new SimManagerViewModel();
                FlasherViewModel = new FlasherViewModel();
                BlackBoxViewModel = new BlackBoxViewModel();
                QcSettingsViewModel = new QcSettingsViewModel();
            }
            catch (Exception ex)
            {
                showErrorDialog(ex);
            }
        }

        /// <summary>
        /// Initializes culture infos to "en-US" to ensure proper compatibility with e.g. decimal points with double variables.
        /// </summary>
        private static void initializeCultureInfos()
        {
            CultureInfo cultureInfo = new CultureInfo("en-US");

            Thread.CurrentThread.CurrentCulture = cultureInfo;
            Thread.CurrentThread.CurrentUICulture = cultureInfo;
        }

        private static void showSplashScreen()
        {
            SplashScreenUtility.SplashScreen = new MarbleSplashScreen();
            SplashScreenUtility.ShowSplashScreen();
        }

        private static void showErrorDialog(Exception ex)
        {
            string errorString = "Marble failed to start! Please report this error to Marble development team." + Environment.NewLine;
            errorString += Environment.NewLine + "Exception: " + ex.Message;

            if (ex.InnerException != null && !string.IsNullOrEmpty(ex.InnerException.Message))
            {
                errorString += Environment.NewLine + "Inner Exception: " + ex.InnerException.Message;
            }
            if (!string.IsNullOrEmpty(ex.StackTrace))
            {
                errorString += Environment.NewLine + "StackTrace: " + ex.StackTrace;
            }

            MessageBox.Show(errorString, "Marble failed to start!", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // If Marble connector is running, close it. This also kills the IronPython process
            if (App.ViewModel.MarbleConnector != null)
            {
                App.ViewModel.MarbleConnector.StopAndWaitToFinish();
            }
            Environment.Exit(0);
        }

        private void Application_Exit(object sender, System.Windows.ExitEventArgs e)
        {
            // Unsubscribe insert/remove USB device watcher
            usbInsertedWatcher.Stop();
            usbRemovedWatcher.Stop();

            // Close all services and processes related to blackbox execution (if running)
            closeBlackBoxRelatedProcesses();
            // Also close videorecorder (if running)
            ThreadPool.QueueUserWorkItem(state => closeServiceProcess("VideoRecorder"));
        }

        internal static void closeBlackBoxRelatedProcesses()
        {
            ThreadPool.QueueUserWorkItem(state => closeServiceProcess("IOWarriorUI", true));
            ThreadPool.QueueUserWorkItem(state => closeServiceProcess("BlackBoxService", true));
            ThreadPool.QueueUserWorkItem(state => closeServiceProcess("IoWarriorService", true));
        }

        private static void closeServiceProcess(string serviceProcess, bool global = false)
        {
            string guiPath = Environment.CurrentDirectory.Substring(0, Environment.CurrentDirectory.LastIndexOf(Path.DirectorySeparatorChar));
            var processes = Process.GetProcessesByName(serviceProcess);
            if (processes.Length > 0)
            {
                foreach (var process in processes)
                {
                    try
                    {
                        // Hack: set process priority so that in the BlackBoxService process we can identify that the process is closed by calling Process.CloseMainWindow instead of
                        // pressing the "Close Service" button in the BlackBoxService GUI.
                        if (serviceProcess == "BlackBoxService")
                            process.PriorityClass = ProcessPriorityClass.RealTime;
                    }
                    catch {/*No actions required*/}

                    try
                    {
                        // Close the service process if running under GUI directory or if defined to be closed globally
                        string processPath = Path.GetDirectoryName(process.MainModule.FileName);
                        if (!string.IsNullOrEmpty(processPath) && processPath.StartsWith(guiPath) || global)
                        {
                            if (!process.CloseMainWindow())
                            {
                                process.Kill();
                            }
                            else
                            {
                                if (!process.WaitForExit(4000))
                                {
                                    process.Kill();
                                }
                            }
                        }
                    }
                    catch {/*No actions required*/}

                    process.Close();
                    process.Dispose();
                }
            }
        }

        private static void addRemoveUSBHandler()
        {
            ManagementScope scope = new ManagementScope("root\\CIMV2") {Options = {EnablePrivileges = true}};
            try
            {
                WqlEventQuery query = new WqlEventQuery
                {
                    EventClassName = "__InstanceDeletionEvent",
                    WithinInterval = new TimeSpan(0, 0, 3),
                    Condition = @"TargetInstance ISA 'Win32_USBHub'"
                };

                usbRemovedWatcher = new ManagementEventWatcher(scope, query);
                usbRemovedWatcher.EventArrived += uSBInsertedOrRemoved;
                usbRemovedWatcher.Start();
            }
            catch
            {
                if (usbRemovedWatcher != null)
                    usbRemovedWatcher.Stop();
            }
        }

        private static void addInsetUSBHandler()
        {
            ManagementScope scope = new ManagementScope("root\\CIMV2") { Options = { EnablePrivileges = true } };
            try
            {
                WqlEventQuery query = new WqlEventQuery
                {
                    EventClassName = "__InstanceCreationEvent",
                    WithinInterval = new TimeSpan(0, 0, 3),
                    Condition = @"TargetInstance ISA 'Win32_USBHub'"
                };
                usbInsertedWatcher = new ManagementEventWatcher(scope, query);
                usbInsertedWatcher.EventArrived += uSBInsertedOrRemoved;
                usbInsertedWatcher.Start();
            }
            catch
            {
                if (usbInsertedWatcher != null)
                    usbInsertedWatcher.Stop();
            }
        }

        private static void uSBInsertedOrRemoved(object sender, EventArgs e)
        {
            App.marbleViewModel.CheckHWControllerTypeAndAvailability();
        }
    }
}
