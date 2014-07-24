using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Reflection;
using System.Runtime.InteropServices;
using System.ServiceModel;
using System.Threading;
using System.Windows.Forms;
using TestAutomation.Gui.Marble.IPC.Interfaces;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;
using log4net;
using log4net.Config;

namespace TestAutomation.Gui.Marble.IPC.Services
{
    static class VideoRecorderService
    {
        [DllImport("User32.dll")]
        private static extern bool SetForegroundWindow(IntPtr hWnd);
        internal static ILog log;
        private static ServiceHost host = null;
        private static Mutex mutex;

        /// <summary>
        /// Static constructor for Assebly resolver use
        /// </summary>
        static VideoRecorderService()
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
            if (File.Exists(assemblyFileName))
                return Assembly.LoadFrom(assemblyFileName);
            return null;
        }

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            //servicePort = randomizePort();
            string testUnitNumber = string.Empty;
            if (args.Length == 1)
            {
                testUnitNumber = args[0];
            }
            bool mutexCreated;

            // Mutex will prevent an application to run twice
            mutex = new Mutex(true, Environment.CurrentDirectory.Replace(@"\", "_"), out mutexCreated);
            
            // Crate settings handler and initialize log4net
            string userSettingsFilePath = @"..\..\settings\VideoRecorder.xml";
            string defaultSettingsFilePath = @"..\..\settings\default\VideoRecorder.xml";
            if (!File.Exists(userSettingsFilePath))
            {
                if (File.Exists(defaultSettingsFilePath))
                    File.Copy(defaultSettingsFilePath, userSettingsFilePath);
                else
                    userSettingsFilePath = @".\VideoRecorder.xml"; // If files are not found use backup file
            }
            
            SettingsHandler settingsHandler = new SettingsHandler(new VideoRecorderServiceSettings(), userSettingsFilePath);
            VideoRecorderServiceSettings settings = settingsHandler.SettingsObject as VideoRecorderServiceSettings;
            if (settings != null)
            {
                XmlConfigurator.Configure(settings.Logging);
            }
                
            log = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
            if (mutexCreated)
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                VideoRecorderGUI recorder = new VideoRecorderGUI(settingsHandler);
               
                recorder.TestUnitNumber = testUnitNumber;
                log.Info("Starting VideoRecorder WCF Service");

                string epName = Environment.CurrentDirectory;
                epName = epName.Substring(epName.IndexOf(@"\") + 1);
                epName = epName.Replace(@"\", "_");
                epName = epName.Replace(@" ", "_");
                try
                {
                    string uri = @"net.pipe://localhost/" + epName + "/" + ServiceDefinitions.VideoRecorderServiceEndpoint;
                    host = new ServiceHost(recorder, new Uri(@"net.pipe://localhost/" + epName + "/"));
                    NetNamedPipeBinding b = new NetNamedPipeBinding();
                    host.AddServiceEndpoint(typeof(IVideoRecorderService), b, ServiceDefinitions.VideoRecorderServiceEndpoint);
                    log.Info("Adding Service Endpoint: " + uri);

                    host.Faulted += new EventHandler(host_Faulted);
                    host.Closed += new EventHandler(host_Closed);
                    host.Opened += new EventHandler(host_Opened);
                    host.Open();
                }
                catch (Exception e)
                {
                    log.Fatal("Create WCF service for VideoRecorder failed: " + Environment.NewLine + e.Message, e);
                    mutex.ReleaseMutex();
                    Environment.Exit(0);
                }
                
                log.Info("Application.Run(VideoRecorder GUI)");
                Application.Run(recorder);
                videoRecorderExit();

            }
            else
            {
                string currentDir = Environment.CurrentDirectory.Substring(0, Environment.CurrentDirectory.LastIndexOf(Path.DirectorySeparatorChar));
                var videoRecorderProcesses = Process.GetProcessesByName("VideoRecorder");
                foreach (Process p in videoRecorderProcesses)
                {
                    if (p.Id != Process.GetCurrentProcess().Id)
                    {
                        string processPath = Path.GetDirectoryName(p.MainModule.FileName);
                        if (!string.IsNullOrEmpty(processPath) && processPath.StartsWith(currentDir))
                        {
                            bringToFront(p.MainWindowHandle);
                        }
                    }
                }
                log.Info("VideoRecorder was already running. Exiting process now.");
            }

            log.Info("Process exit...");
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
            log.Error("SERVICE HOST FAULTED");
            videoRecorderExit();
        }

        internal static void videoRecorderExit()
        {
            log.Info("Disposing WCF service");
            host.Close();
            ((IDisposable)host).Dispose();
            mutex.ReleaseMutex();
            log.Info("Process exit...");
            Environment.Exit(0);
        }

        internal static void bringToFront(IntPtr handle)
        {
            SetForegroundWindow(handle);
        }

        private static int randomizePort()
        {
            // Evaluate current system tcp connections. This is the same information provided
            // by the netstat command line application, just in .Net strongly-typed object
            // form.  We will look through the list, and if our port we would like to use
            // in our TcpClient is occupied, we will set isAvailable to false.
            IPGlobalProperties ipGlobalProperties = IPGlobalProperties.GetIPGlobalProperties();
            IPEndPoint[] ipEndpoints = ipGlobalProperties.GetActiveTcpListeners();

            // Select a random port from the private range 49152–65535
            Random rnd = new Random();
            while (true)
            {
                int randomPort = rnd.Next(49152, 65535);
                bool isAvailable = ipEndpoints.All(ep => ep.Port != randomPort);
                if (isAvailable)
                    return randomPort;
            }
        }

        /// <summary>
        /// Ensure that proper culture specific settings are always used!
        /// We do not want to see any incorrect .ToString() and Double.Parse() behaviour related to
        /// DateTime or NumberDecimalSeparator.
        /// </summary>
        /// <returns>CultureInfo of en-US</returns>
        public static CultureInfo GetCulture()
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
    }
}
