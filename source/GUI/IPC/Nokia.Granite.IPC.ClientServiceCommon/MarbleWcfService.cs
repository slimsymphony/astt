using System;
using System.Collections.Generic;
using System.ServiceModel;
using log4net;

namespace TestAutomation.Gui.Marble.IPC.Services
{
    public class MarbleWcfService : IDisposable
    {
        #region private fields

        private object serviceImpl;
        private List<Tuple<Type, string>> endpointSettings;
        private int servicePort = -1;
        private readonly ILog log;
        ServiceHost host = null;
        private bool disposing;
        private bool faulted;

        #endregion

        #region Constructor(s)

        public MarbleWcfService(object serviceImpl, int servicePort, List<Tuple<Type, string>> endpointSettings)
        {
            this.disposing = false;
            this.faulted = false;
            this.log = LogManager.GetLogger(serviceImpl + " WCF Service");
            this.serviceImpl = serviceImpl;
            this.servicePort = servicePort;
            this.endpointSettings = endpointSettings;
            this.serviceStart();
        }

        #endregion

        #region Private methods

        private void serviceStart()
        {
            string uri = @"net.tcp://localhost:" + this.servicePort;
            log.Info("Starting ServiceHost at " + uri);
            host = new ServiceHost(this.serviceImpl, new Uri(uri));

            NetTcpBinding b = new NetTcpBinding(SecurityMode.Transport, true);
            b.SendTimeout = TimeSpan.FromSeconds(30);
            b.ReceiveTimeout = TimeSpan.FromMinutes(2);
            b.ReliableSession.InactivityTimeout = TimeSpan.FromMinutes(1);
            b.ReliableSession.Ordered = true;
            b.MaxReceivedMessageSize = 524288;
            b.MaxBufferSize = 524288;
            b.MaxBufferPoolSize = 4194304;
            b.OpenTimeout = TimeSpan.FromSeconds(30);

            foreach (Tuple<Type, string> ep in this.endpointSettings)
            {
                log.Info("Adding Service Endpoint: " + ep.Item1 + " " + b + " " + ep.Item2);
                host.AddServiceEndpoint(ep.Item1, b, ep.Item2);
            }

            host.Open();

            host.Faulted += new EventHandler(host_Faulted);
            host.Closed += new EventHandler(host_Closed);
            host.Opened += new EventHandler(host_Opened);
            this.faulted = false;
        }

        private void serviceClose()
        {
            if (host != null)
            {
                log.Info("Closing WCF Service Host");

                this.host.Faulted -= host_Faulted;
                this.host.Closed -= host_Closed;
                this.host.Opened -= host_Opened;

                if (this.disposing)
                {
                    try
                    {
                        log.Info("Dispose called: Trying to abort ServiceHost for quick exit");
                        host.Abort();
                        log.Info("Success...");
                    }
                    catch (Exception e)
                    {
                        log.Warn("Abort ServiceHost failed", e);
                    }
                }
                else
                {
                    if (host.State == CommunicationState.Opened)
                    {
                        try
                        {
                            log.Info("Trying to close ServiceHost");
                            host.Close();
                            log.Info("Success...");
                        }
                        catch (Exception ex)
                        {
                            log.Warn("Close ServiceHost failed", ex);
                            try
                            {
                                log.Info("Trying to abort ServiceHost");
                                host.Abort();
                                log.Info("Success...");
                            }
                            catch (Exception e)
                            {
                                log.Warn("Abort ServiceHost failed", e);
                            }
                        }
                    }
                    else
                    {
                        try
                        {
                            log.Info("Trying to abort ServiceHost");
                            host.Abort();
                            log.Info("Success...");
                        }
                        catch (Exception e)
                        {
                            log.Warn("Abort ServiceHost failed", e);
                        }
                    }
                }
                try
                {
                    log.Info("Trying to Dispose ServiceHost");
                    ((IDisposable)this.host).Dispose();
                    GC.SuppressFinalize(this.host);
                    log.Info("Success...");
                }
                catch (Exception e)
                {
                    log.Warn("Dispose ServiceHost failed", e);
                }

                this.host = null;
            }
        }

        void host_Opened(object sender, EventArgs e)
        {
            log.Debug("SERVICE HOST OPENED");
        }
        
        private void host_Closed(object sender, EventArgs e)
        {
            log.Debug("SERVICE HOST CLOSED");
            if (!this.disposing && !this.faulted)
            {
                log.Warn("CLOSING / REOPENING THE SERVICE!");
                this.serviceClose();
                this.serviceStart();
            }
        }

        private void host_Faulted(object sender, EventArgs e)
        {
            log.Fatal("SERVICE HOST FAULTED!");
            if (!this.disposing)
            {
                log.Warn("CLOSING / REOPENING THE SERVICE!");
                this.faulted = true;
                this.serviceClose();
                this.serviceStart();
            }
        }

        #endregion

        #region IDisposable members

        public void Dispose()
        {
            this.disposing = true;
            this.serviceClose();
        }

        #endregion
    }
}