using System;
using System.Diagnostics;
using System.IO;
using System.ServiceModel;
using System.Threading;
using log4net;
using TestAutomation.Gui.Marble.IPC.Interfaces;

namespace TestAutomation.Gui.Marble.IPC.Clients
{
    public class MarbleFwVideoRecorderClient : IDisposable, IVideoRecorderService
    {
        #region Private fields

        private object lockObject = new object();
        private readonly ILog log;
        private IClientChannel clientChannel;
        private readonly string servicePath;
        private readonly string serviceExecutable;
        private string serviceUri;
        private string serviceArgs;
        private bool faulted;
        private bool disposing;
        private readonly bool ensureServiceRunning;

        #endregion

        #region Constructors

        public MarbleFwVideoRecorderClient(string servicePath = "", string args = "", bool ensureServiceRunning = true)
        {
            this.serviceUri = string.Empty;
            this.serviceArgs = args;
            this.ensureServiceRunning = ensureServiceRunning;
            this.disposing = false;
            this.log = LogManager.GetLogger("VideoRecorderServiceLogger");
            if (string.IsNullOrEmpty(servicePath))
            {
                string clientProcessDirectory = Environment.CurrentDirectory.Substring(0,
                    Environment.CurrentDirectory.LastIndexOf(Path.DirectorySeparatorChar));
                this.servicePath = clientProcessDirectory + @"\Services\VideoRecorder";
                this.serviceExecutable = this.servicePath + @"\VideoRecorder.exe";
            }
            else
            {
                this.servicePath = servicePath;
                this.serviceExecutable = this.servicePath + @"\VideoRecorder.exe";
            }

            this.generateServiceUri(this.servicePath);
            this.checkService();
        }

        #endregion

        #region Public methods

        public void RecordVideo(string path)
        {
            this.delegateExecutor(proxy => proxy.RecordVideo(path));
        }

        public void TakePicture(string path)
        {
            this.delegateExecutor(proxy => proxy.TakePicture(path));
        }

        public void StopRecording()
        {
            this.delegateExecutor(proxy => proxy.StopRecording());
        }

        public void SetOverlayTextToVideo(string text)
        {
            this.delegateExecutor(proxy => proxy.SetOverlayTextToVideo(text));
        }

        public int GetCountMotionFrames()
        {
            int c = -1;
            this.delegateExecutor(proxy => c = proxy.GetCountMotionFrames());
            return c;
        }

        public string IsServiceAvailable()
        {
            string s = string.Empty;
            // Return value: empty string if service is available. Otherwise a reason why service is not available.
            this.delegateExecutor(proxy => s = proxy.IsServiceAvailable());
            return s;
        }

        public bool IsVideoRecorderAvailable
        {
            get
            {
                return string.IsNullOrEmpty(this.IsServiceAvailable());
            }
        }

        public string TestUnitNumber
        {
            get
            {
                string fromRecorder = string.Empty;
                this.delegateExecutor(proxy => fromRecorder = proxy.TestUnitNumber, false);
                return fromRecorder;
            }
            set
            {
                this.delegateExecutor(proxy => proxy.TestUnitNumber = value, false);
            }
        }

        public VideoRecorderInfo RecorderInfo
        {
            get
            {
                VideoRecorderInfo fromRecorder = null;
                this.delegateExecutor(proxy => fromRecorder = proxy.RecorderInfo, false);
                return fromRecorder;
            }
            set
            {
                this.delegateExecutor(proxy => proxy.RecorderInfo = value, false);
            }
        }

        public void DisconnectCamera()
        {
            this.delegateExecutor(proxy => proxy.DisconnectCamera(), false);
        }

        #endregion

        #region Private methods

        /// <summary>
        /// Executes a service method using delegate with automatic retries. 
        /// Usage of this method should ensure that service is running and channel is open.
        /// </summary>
        /// <param name="serviceMethod"></param>
        /// <param name="retryOnError">Whether to retry if error occurred</param>
        private void delegateExecutor(ServiceDelegate<IVideoRecorderService> serviceMethod, bool retryOnError = true)
        {
            const int retryCount = 3;
            Exception mostRecentEx = null;
            for (int i = 0; i < retryCount; i++)  // Attempt a maximum of 3 times 
            {
                if (this.disposing || (mostRecentEx != null && !retryOnError))
                {
                    mostRecentEx = null;
                    break;
                }
                try
                {
                    if (this.clientChannel == null || this.clientChannel.State != CommunicationState.Opened || this.faulted)
                    {
                        this.clientClose();
                        this.checkService();
                        this.clientOpen();
                    }

                    serviceMethod((IVideoRecorderService)this.clientChannel);
                    mostRecentEx = null;
                    break;
                }

                // The following is typically thrown on the client when a channel is terminated due to the server closing the connection.
                catch (ChannelTerminatedException cte)
                {
                    if (!retryOnError)
                        break;
                    log.Error("DelegateExecutor caught ChannelTerminatedException from service: ", cte);
                    mostRecentEx = cte;
                    if (i < retryCount)
                    {
                        this.clientClose();
                        this.checkService();
                        Thread.Sleep(2000);
                    }
                }

                // The following is thrown when a remote endpoint could not be found or reached.  The endpoint may not be found or 
                // reachable because the remote endpoint is down, the remote endpoint is unreachable, or because the remote network is unreachable.
                catch (EndpointNotFoundException enfe)
                {
                    if (!retryOnError)
                        break;
                    log.Error("DelegateExecutor caught EndpointNotFoundException from service: ", enfe);
                    mostRecentEx = enfe;
                    if (i < retryCount)
                    {
                        this.clientClose();
                        this.checkService();
                        Thread.Sleep(2000);
                    }
                }

                // The following exception that is thrown when a server is too busy to accept a message.
                catch (ServerTooBusyException stbe)
                {
                    if (!retryOnError)
                        break;
                    log.Error("DelegateExecutor caught ServerTooBusyException from service: ", stbe);
                    mostRecentEx = stbe;
                    if (i < retryCount)
                    {
                        this.clientClose();
                        this.checkService();
                        Thread.Sleep(2000);
                    }
                }

                // The exception that is thrown when a call is made to a communication object that has faulted.
                catch (CommunicationObjectFaultedException fe)
                {
                    if (!retryOnError)
                        break;
                    log.Error("DelegateExecutor caught CommunicationObjectFaultedException from service: ", fe);
                    mostRecentEx = fe;
                    if (i < retryCount)
                    {
                        this.clientClose();
                        this.checkService();
                        Thread.Sleep(2000);
                    }
                }
                // The exception that is thrown when the time allotted for a process or operation has expired.
                catch (TimeoutException te)
                {
                    if (!retryOnError)
                        break;
                    // This should not happen in normal situations, so re-throw this exception.
                    log.Error("DelegateExecutor caught TimeoutException from service when executing: " + serviceMethod.Method.Name, te);
                    mostRecentEx = te;
                    if (i < retryCount)
                    {
                        this.clientClose();
                        this.checkService();
                        Thread.Sleep(2000);
                    }
                }

                catch (Exception ex)
                {
                    if (!retryOnError)
                        break;
                    log.Warn("DelegateExecutor caught fault from service: ", ex);
                    throw;
                }
            }
            if (mostRecentEx != null)
            {
                this.clientClose();
                this.checkService(true);
                log.Error("WCF call failed after " + retryCount + " retries when executing: " + serviceMethod.Method.Name, mostRecentEx);
                //throw new Exception("WCF call failed after " + retryCount + " retries.", mostRecentEx);
            }
        }

        private void generateServiceUri(string processPath)
        {
            string epName = processPath.Substring(processPath.IndexOf(@"\") + 1);
            epName = epName.Replace(@"\", "_");
            epName = epName.Replace(@" ", "_");
            this.serviceUri = @"net.pipe://localhost/" + epName + "/" + ServiceDefinitions.VideoRecorderServiceEndpoint;
            this.log.Debug("Service URI = " + this.serviceUri);
        }

        private void checkService(bool resetRunningService = false)
        {
            if (!disposing && this.ensureServiceRunning)
            {
                string serviceExecutableName = "VideoRecorder";
                bool serviceRunning = false;
                var processes = Process.GetProcessesByName(serviceExecutableName);
                foreach (Process p in processes)
                {
                    try
                    {
                        string processFile = p.MainModule.FileName;
                        if (processFile == this.serviceExecutable)
                        {
                            if (resetRunningService)
                            {
                                this.log.Debug(processFile + " reset requested.");
                                p.Kill();
                            }
                            else
                            {
                                serviceRunning = true;
                            }
                        }
                        p.Close();
                        p.Dispose();
                        if (serviceRunning)
                        {
                            this.log.Debug("VideoRecorderService is running at " + processFile);
                            break;
                        }
                    }
                    catch (Exception ex)
                    {
                        this.log.Warn("Check if VideoRecorderService is running failed: " + ex.Message);
                    }
                }
                if (!serviceRunning)
                {
                    try
                    {
                        this.log.Debug("VideoRecorder is not running. Starting service now at " + this.serviceExecutable);
                        Process.Start(this.serviceExecutable, this.serviceArgs);
                    }
                    catch (Exception ex)
                    {
                        log.Warn("Unable to start service process", ex);
                    }
                }
            }
        }

        private void clientOpen()
        {
            // Use a lock object due to keepalive timer may call this method from timer thread, which may cause cross-thread issues
            lock (lockObject)
            {
                if (!disposing)
                {
                    this.log.Info("Opening WCF ClientChannel");
                    var factory = new ChannelFactory<IVideoRecorderService>(new NetNamedPipeBinding(), this.serviceUri);
                    this.clientChannel = (IClientChannel)factory.CreateChannel();
                    

                    this.clientChannel.Faulted += new EventHandler(serviceChannel_Faulted);
                    this.clientChannel.Opened += new EventHandler(serviceChannel_Opened);
                    this.clientChannel.Closed += new EventHandler(serviceChannel_Closed);

                    this.clientChannel.Open(TimeSpan.FromSeconds(20));
                    this.faulted = false;
                }
            }
        }

        private void clientClose()
        {
            // Use a lock object due to keepalive timer may call this method from timer thread, which may cause cross-thread issues
            lock (lockObject)
            {
                if (this.clientChannel != null)
                {
                    this.log.Info("Closing WCF ClientChannel");

                    this.clientChannel.Faulted -= serviceChannel_Faulted;
                    this.clientChannel.Closed -= serviceChannel_Closed;
                    this.clientChannel.Opened -= serviceChannel_Opened;

                    if (this.disposing)
                    {
                        try
                        {
                            this.log.Info("Dispose called: Trying to abort ClientChannel for quick exit");
                            this.clientChannel.Abort();
                            this.log.Info("Success...");
                        }
                        catch (Exception e)
                        {
                            this.log.Warn("Abort ClientChannel failed", e);
                        }
                    }
                    else
                    {
                        if (this.clientChannel.State == CommunicationState.Opened)
                        {
                            try
                            {
                                this.log.Info("Trying to close clientChannel");
                                this.clientChannel.Close();
                                this.log.Info("Success...");
                            }
                            catch (Exception ex)
                            {
                                this.log.Warn("Close clienChannel failed", ex);
                                try
                                {
                                    this.log.Info("Trying to abort clientChannel");
                                    this.clientChannel.Abort();
                                    this.log.Info("Success...");
                                }
                                catch (Exception e)
                                {
                                    log.Warn("Abort clientChannel failed", e);
                                }
                            }
                        }
                        else
                        {
                            try
                            {
                                this.log.Info("Trying to abort clientChannel");
                                this.clientChannel.Abort();
                                this.log.Info("Success...");
                            }
                            catch (Exception e)
                            {
                                this.log.Warn("Abort clientChannel failed", e);
                            }
                        }
                    }
                    try
                    {
                        this.log.Info("Trying Dispose clientChannel");

                        this.clientChannel.Dispose();
                        this.log.Info("Success...");
                    }
                    catch (Exception e)
                    {
                        this.log.Warn("Dispose clientChannel failed", e);
                    }

                    this.clientChannel = null;
                }
            }
        }

        private void serviceChannel_Faulted(object sender, EventArgs e)
        {
            this.faulted = true;
            log.Debug("VideoRecorderServiceClient: SERVICE CHANNEL FAULTED");
        }

        private void serviceChannel_Closed(object sender, EventArgs e)
        {
            log.Debug("VideoRecorderServiceClient: SERVICE CHANNEL CLOSED");
        }

        private void serviceChannel_Opened(object sender, EventArgs e)
        {
            log.Debug("VideoRecorderServiceClient: SERVICE CHANNEL OPENED");
        }

        #endregion

        #region IDisposable members

        public void Dispose()
        {
            log.Info("Dispose called, setting disposing flag to true");
            this.disposing = true;
            this.clientClose();
            this.disposing = false;
            log.Info("Dispose succeeded, setting disposing flag to false");
        }

        #endregion
    }
}
