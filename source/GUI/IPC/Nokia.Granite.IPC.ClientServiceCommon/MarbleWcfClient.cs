using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.ServiceModel;
using System.Threading;
using System.Timers;
using TestAutomation.Gui.Marble.IPC.Interfaces;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;
using log4net;

namespace TestAutomation.Gui.Marble.IPC.Clients
{
    public delegate void ServiceDelegate<in T>(T proxy);

    public class MarbleWcfClient<TClient> : IDisposable
    {
        #region Private fields

        private object lockObject = new object();
        private readonly ILog log;
        private IClientChannel clientChannel;
        private readonly EndpointAddress endpointAddress;
        private readonly string serviceExecutable;
        private bool faulted;
        private bool disposing;
        private readonly object callbackImpl;
        private System.Timers.Timer keepaliveTimer;
        private bool clientSubscribeEnabled;
        private IClientKeepalive clientKeepalive;
        private IClientSubscribe clientSubscribe;
        private NetTcpBinding binding;

        private enum ClientCallType
        {
            ClientKeepalive,
            ClientSubscribe
        }
        
        #endregion

        #region Constructor

        /// <summary>
        /// Constructs the MarbleWcfClient class.
        /// </summary>
        /// <param name="clientSettings">The settings used by this client</param>
        /// <param name="serviceName">The name of the service</param>
        /// <param name="callback">Callback implementation (if any)</param>
        public MarbleWcfClient(ClientSettings clientSettings, string serviceName = null, object callback = null)
        {           
            this.disposing = false;
            this.callbackImpl = callback;
            this.log = LogManager.GetLogger(serviceName + "Logger");

            this.log.Debug("Resolving IP-Address of " + clientSettings.ServiceUri.HostAddress);

            string serviceIp = string.Empty;
            IPAddress[] addresses = Dns.GetHostAddresses(clientSettings.ServiceUri.HostAddress);
            foreach (var gg in addresses)
            {
                if (gg.AddressFamily == AddressFamily.InterNetwork)
                {
                    serviceIp = gg.ToString();
                }
            }
            if (string.IsNullOrEmpty(serviceIp))
            {
                throw new InvalidOperationException("Unable to resolve IP-Address of " + clientSettings.ServiceUri.HostAddress);
            }

            string address = @"net.tcp://" + serviceIp + ":" + clientSettings.ServiceUri.ServicePort + "/" + serviceName;

            this.log.Debug("Connecting to " + address);
            this.serviceExecutable = clientSettings.ServiceExecutable;
            this.endpointAddress = new EndpointAddress(address);
            this.checkService();
        }

        #endregion

        #region Public methods

        public ILog Logger
        { 
            get 
            { 
                return this.log;
            } 
        }

        public NetTcpBinding Binding
        {
            get { return this.binding; }
        }

        /// <summary>
        /// Executes a service method using delegate with automatic retries. 
        /// Usage of this method should ensure that service is running and channel is open.
        /// </summary>
        /// <param name="serviceMethod"></param>
        /// <param name="retryOnError">Whether to retry if error occurred</param>
        public void DelegateExecutor(ServiceDelegate<TClient> serviceMethod, bool retryOnError = true)
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

                    serviceMethod((TClient)this.clientChannel);

                    if (this.clientSubscribe != null)
                    {
                        if (serviceMethod.Method.Name.Contains("ClientSubscribe"))
                        {
                            this.log.Debug("this.clientSubscribe not null. in DelegateExecutor. Setting variables...");
                            this.log.Debug("ClientSubscribe called. Setting this.isClientSubscribe = true");
                            this.clientSubscribeEnabled = true;
                        }
                        else if (serviceMethod.Method.Name.Contains("ClientUnSubscribe"))
                        {
                            this.log.Debug("this.clientSubscribe not null. in DelegateExecutor. Setting variables...");
                            this.log.Debug("ClientUnSubscribe called. Setting this.isClientSubscribe = false");
                            this.clientSubscribeEnabled = false;
                        }
                    }
                        
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
                log.Error("WCF call failed after " + retryCount + " retries when executing: " + serviceMethod.Method.Name, mostRecentEx);
                throw new Exception("WCF call failed after " + retryCount + " retries.", mostRecentEx);
            }
        }

        #endregion

        #region Private methods

        private void checkService(bool resetRunningService = false)
        {
            if (!disposing)
            {
                // Use a lock object due to keepalive timer may call this method from timer thread, which may cause cross-thread issues
                lock (lockObject)
                {
                    // For local services, check that service is running.
                    if (!string.IsNullOrEmpty(this.serviceExecutable) &&
                        (this.endpointAddress.ToString().ToLower().Contains("127.0.0.1") ||
                         this.endpointAddress.ToString().ToLower().Contains("localhost")))
                    {
                        bool fullPathSpecified = false;
                        try
                        {
                            fullPathSpecified = Path.IsPathRooted(this.serviceExecutable);
                        }
                        catch (Exception e)
                        {
                            this.log.Error("Unable to define the full path from " + this.serviceExecutable);
                        }


                        string serviceName = Path.GetFileNameWithoutExtension(this.serviceExecutable);
                        this.log.Debug("Checking whether " + serviceName + " is running...");
                        bool serviceRunning = false;
                        var processes = Process.GetProcessesByName(serviceName);
                        if (processes.Length == 1)
                        {
                            this.log.Debug(serviceName + " is running at " + processes[0].MainModule.FileName);
                            if (resetRunningService)
                            {
                                this.log.Debug(serviceName + " reset requested.");
                                processes[0].Kill();
                            }
                            else
                            {
                                serviceRunning = true;
                            }

                            processes[0].Close();
                            processes[0].Dispose();
                        }
                        if (!serviceRunning)
                        {
                            if (!fullPathSpecified)
                            {
                                try
                                {
                                    var serviceFiles =
                                        Directory.GetFiles(
                                            Environment.CurrentDirectory.ToLower().Contains("services")
                                                ? @"..\"
                                                : @"..\Services\", this.serviceExecutable, SearchOption.AllDirectories);
                                    if (serviceFiles.Length == 1)
                                    {
                                        this.log.Debug(serviceName + " is not running. Starting service now at " +
                                                       serviceFiles[0]);
                                        Process.Start(serviceFiles[0]);
                                    }
                                }
                                catch (Exception ex)
                                {
                                    log.Warn("Unable to start service process", ex);
                                }
                            }
                            else
                            {
                                try
                                {
                                    this.log.Debug(serviceName + " is not running. Starting service now at " +
                                                   this.serviceExecutable);
                                    Process.Start(this.serviceExecutable);
                                }
                                catch (Exception ex)
                                {
                                    log.Warn("Unable to start service process", ex);
                                }
                            }
                        }
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
                    this.binding = new NetTcpBinding(SecurityMode.Transport, true);
                    this.binding.OpenTimeout = TimeSpan.FromSeconds(20);
                    this.binding.SendTimeout = TimeSpan.FromSeconds(20);
                    this.binding.ReliableSession.InactivityTimeout = TimeSpan.FromMinutes(1);
                    this.binding.ReliableSession.Ordered = true;
                    this.binding.MaxReceivedMessageSize = 524288;
                    this.binding.MaxBufferSize = 524288;
                    this.binding.MaxBufferPoolSize = 4194304;
                    this.binding.ReaderQuotas.MaxArrayLength = 2147483647;
                    this.binding.ReaderQuotas.MaxBytesPerRead = 4096;
                    this.binding.ReaderQuotas.MaxDepth = 64;
                    this.binding.ReaderQuotas.MaxNameTableCharCount = 16384;
                    this.binding.ReaderQuotas.MaxStringContentLength = 2147483647;

                    // Use a duplicate binding if callback implementation provided...
                    if (this.callbackImpl != null)
                    {
                        var factory = new DuplexChannelFactory<TClient>(this.callbackImpl, this.binding, this.endpointAddress);
                        this.clientChannel = (IClientChannel)factory.CreateChannel();
                    }
                    else
                    {
                        var factory = new ChannelFactory<TClient>(this.binding, this.endpointAddress);
                        this.clientChannel = (IClientChannel)factory.CreateChannel();
                    }

                    foreach (Type t in this.clientChannel.GetType().GetInterfaces())
                    {
                        if (t == typeof(IClientSubscribe))
                        {
                            this.clientSubscribe = (IClientSubscribe)this.clientChannel;
                            this.log.Debug(this + " Inherits from IClientSubscribe. Typecasting this.clientChannel to IClientSubscribe");
                        }
                        if (t == typeof(IClientKeepalive))
                        {
                            this.clientKeepalive = (IClientKeepalive)this.clientChannel;
                            this.log.Debug(this + " Inherits from IClientKeepalive. Typecasting this.clientChannel to IClientKeepalive");
                        }
                    }

                    this.clientChannel.Faulted += new EventHandler(serviceChannel_Faulted);
                    this.clientChannel.Opened += new EventHandler(serviceChannel_Opened);
                    this.clientChannel.Closed += new EventHandler(serviceChannel_Closed);

                    this.clientChannel.Open();
                    this.faulted = false;

                    // If the client inherits from IClientKeepalive or IClientSubscribe, start a keepalive timer
                    if (this.clientSubscribe != null || this.clientKeepalive != null)
                    {
                        if (this.keepaliveTimer == null)
                        {
                            this.keepaliveTimer = new System.Timers.Timer(5000);
                            this.keepaliveTimer.Elapsed += keepaliveTimerElapsed;
                               
                        }
                        this.keepaliveTimer.Start();
                    }
                }
            }
        }

        private void clientClose()
        {
            // Use a lock object due to keepalive timer may call this method from timer thread, which may cause cross-thread issues
            lock (lockObject)
            {
                //if (this.keepaliveTimer != null)
                //{
                //    this.keepaliveTimer.Stop();
                //}
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

                        // Also prevent auto subscribe calls (if enabled)
                        //this.isClientSubscribe = false;
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
        
        private void tryCatchExecutor(ClientCallType clientCallType)
        {
            bool retryOnError = true;
            const int retryCount = 3;
            Exception mostRecentEx = null;
            for (int i = 0; i < retryCount; i++)  // Attempt a maximum of 3 times 
            {
                if (this.disposing || (mostRecentEx != null))
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

                    switch (clientCallType)
                    {
                        case ClientCallType.ClientKeepalive:
                            if (this.clientKeepalive != null)
                            {
                                this.log.Debug("this.clientKeepalive not null in tryCatchExecutor. Executing ClientKeepalive WCF call");
                                this.clientKeepalive.ClientKeepalive();
                            }
                            else
                            {
                                this.log.Error("this.clientKeepalive is null in tryCatchExecutor!!!!!!!!!!! SHOULD NOT BE NULL HERE!!! CHECK THIS!!!!!");
                            }
                            break;

                        case ClientCallType.ClientSubscribe:
                            if (this.clientSubscribe != null)
                            {
                                this.log.Debug("this.clientSubscribe not null in tryCatchExecutor. Executing ClientSubscribe WCF call");
                                this.clientSubscribe.ClientSubscribe();
                            }
                            else
                            {
                                this.log.Error("this.clientSubscribe is null in tryCatchExecutor!!!!!!!!!!! SHOULD NOT BE NULL HERE!!! CHECK THIS!!!!!");
                            }
                            break;
                    }

                    mostRecentEx = null;
                    break;
                }

                // The following is typically thrown on the client when a channel is terminated due to the server closing the connection.
                catch (ChannelTerminatedException cte)
                {
                    if (!retryOnError)
                        break;
                    log.Error("tryCatchExecutor caught ChannelTerminatedException from service: ", cte);
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
                    log.Error("tryCatchExecutor caught EndpointNotFoundException from service: ", enfe);
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
                    log.Error("tryCatchExecutor caught ServerTooBusyException from service: ", stbe);
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
                    log.Error("tryCatchExecutor caught CommunicationObjectFaultedException from service: ", fe);
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
                    log.Error("tryCatchExecutor caught TimeoutException from service when executing: " + clientCallType, te);
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
                    log.Warn("tryCatchExecutor caught fault from service: ", ex);
                    throw;
                }
            }
            if (mostRecentEx != null)
            {
                this.clientClose();
                log.Error("WCF call failed after " + retryCount + " retries when executing: " + clientCallType, mostRecentEx);
                throw new Exception("WCF call failed after " + retryCount + " retries.", mostRecentEx);
            }

        }

        private void keepaliveTimerElapsed(object source, ElapsedEventArgs e)
        {
            if (!this.disposing)
            {
                log.Debug("keepaliveTimerElapsed");

                if (this.clientKeepalive != null)
                {
                    log.Debug("IClientKeepalive");
                    try
                    {
                        this.tryCatchExecutor(ClientCallType.ClientKeepalive);
                    }
                    catch (Exception ex)
                    {
                        log.Error("Failed to execute ClientKeepalive call in TimerElapsed", ex);
                    }
                }
                else
                {
                    log.Debug("this.clientKeepalive == null in keepaliveTimerElapsed!!!!");
                }
                if (this.clientSubscribe != null)
                {
                    log.Debug("IClientSubscribe not null in keepaliveTimerElapsed");
                    if (this.clientSubscribeEnabled)
                    {
                        log.Debug("this.clientSubscribeEnabled == true in keepaliveTimerElapsed");
                        try
                        {
                            log.Debug("Try: keepaliveTimerElapsed -->ClientSubscribe...");
                            this.tryCatchExecutor(ClientCallType.ClientSubscribe);
                            log.Debug("Try: keepaliveTimerElapsed -->ClientSubscribe Succeeded");
                        }
                        catch (Exception ex)
                        {
                            log.Error("Failed to execute ClientSubscribe call in TimerElapsed", ex);
                        }
                    }
                }
                else
                {
                    log.Debug("this.clientSubscribe == null in keepaliveTimerElapsed!!!!");
                }
            }
        }

        void serviceChannel_Closed(object sender, EventArgs e)
        {
            log.Debug("CLIENT CHANNEL CLOSED");
        }

        void serviceChannel_Opened(object sender, EventArgs e)
        {
            log.Debug("CLIENT CHANNEL OPENED");
        }

        void serviceChannel_Faulted(object sender, EventArgs e)
        {
            this.faulted = true;
            log.Warn("CLIENT CHANNEL FAULTED!");
        }

        #endregion

        #region IDisposable members

        public void Dispose()
        {
            log.Info("Dispose called, setting disposing flag to true");
            this.disposing = true;
            this.clientClose();
            if (this.keepaliveTimer != null)
            {
                this.keepaliveTimer.Stop();
                this.keepaliveTimer.Close();
                this.keepaliveTimer.Elapsed -= keepaliveTimerElapsed;
                this.keepaliveTimer.Dispose();
                this.keepaliveTimer = null;
            }
            this.disposing = false;
            log.Info("Dispose succeeded, setting disposing flag to false");
        }

        #endregion
    }
}
