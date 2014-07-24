using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.ServiceModel;
using System.ServiceModel.Discovery;
using Nokia.Granite.IPC.Interfaces;
using System.Collections;

using System.Xml;
using System.IO;
using System.Dynamic;
using System.Xml.Linq;

// Import log4net classes.
using log4net;
using log4net.Config;

namespace Nokia.Granite.IPC.Clients.LeadFollower
{
    public class GraniteFollowerClient : IGraniteFollowerCallback
    {
        #region GraniteFollowerClient Properties and Constructors

        private IGraniteLeadService serviceProxy;
        private string ClientId = null;
        // for accessing current test case data from FollowerClient
        // class, subarea , feature, method, tcId, docstring
        private string[] mCurrentTestCase = new string[6] {null, null, null, null, null, null};
        private bool mExecutionQueueOpen = false;
        protected static readonly ILog log = LogManager.GetLogger("LeaderFollowerLogger");
        
        # region Client controlling properties needed by Follower test case

        public bool IsConnectedToService { get; private set; }
        public string ServiceUri = null;
        public bool TearDownFinished = true; // status can be set from execution, will be false after initialization
        public bool ExecutionSuccess = true; // will be set by follower after the execution queue has been finished

        // todo: change result to single dictionary
        public string CaseResult = "Not executed";
        public string ResultLink = "";
        public string ResultDir = "";
        public string ExecutionTime = "0";
        public string EndTime = "";
        public List<string> ScreenCaptures = new List<string>();
        public List<string> XFiles = new List<string>();
        
        public GraniteFollowerClient()
        {
            IsConnectedToService = false;
            log.Debug("Init GraniteFollowerCallback");
        }

        #endregion

        public string[] CurrentTestCase { 
            get { return mCurrentTestCase; }
            set
            {
                for (int i = 0; i < mCurrentTestCase.Length; i++)
                {
                    mCurrentTestCase[i] = null;
                }
            }
        }

        private void DebugMessage(string message)
        {
            Console.WriteLine(message);
            log.Debug(message);
        }
        
        // for requesting test case stop from Service side
        private bool mStopTestCase = false;
        public bool StopCurrentTestCase { get { return mStopTestCase; } set { mStopTestCase = value; } }

        // Execution queue, returning / taking in execution objects
        private Queue mExecutionQueue = new Queue();
        public Object ExecutionQueue
        {
            get 
            {
                if (mExecutionQueue.Count < 1)
                {
                    return null;
                }
                else
                {
                    return mExecutionQueue.Dequeue();
                }
            }
            set
            {
                if (mCurrentTestCase[0] != null & mExecutionQueueOpen == true)
                {
                    if (value == null)
                    {
                        mExecutionQueue.Clear();
                    }
                    else
                    {
                        mExecutionQueue.Enqueue(value);
                    }
                }
                else if (mCurrentTestCase[0] == null)
                {
                    log.Debug("Cannot add to execution queue, case not initialized!");
                }
                else
                {
                    log.Debug("Cannot add to execution queue, queue is not open!");
                }
            }
        }
        
        public int ExecutionQueueLen { get { return mExecutionQueue.Count; } }

        // image dictionary
        private Dictionary<string, string> mImageDictionary = new Dictionary<string, string>();
        public Dictionary<string, string> ImageDictionary { get { return mImageDictionary; } set { mImageDictionary = value; } }

        public void AbortCurrentTestCase()
        {
            DebugMessage("Aborting current case");
            StopCurrentTestCase = true;
            mExecutionQueueOpen = false;
            mExecutionQueue.Clear();
            CurrentTestCase = null;
            TearDownFinished = true;
            ExecutionSuccess = true;
            CaseResult = "Case aborted";
        }

        public void AddVariable(string v)
        {
            log.Debug("New variable " + v);
            serviceProxy.AddVariable(v);
        }

        public void AddTaskToLeaderQueue(ConfigurationRequestTask ct)
        {
            log.Debug("Configuration request");
            serviceProxy.ConfigurationRequest(ct);
        }

        public void ClientFiasco(string clientId, string reason, string step)
        {
            log.Error(String.Format("Client FIASCO {0}, Reason: {1}, Step: {2}", clientId, reason, step));
            CaseResult = String.Format("Failed: FIASCO {0} @ {1}", reason, step);
            mExecutionQueueOpen = false; // close the execution queue for new steps
            mExecutionQueue.Clear();     // clear the queue, no reason to execute steps anymore
            StopCurrentTestCase = true;  // request test case teardown
            serviceProxy.ClientFiasco(clientId, reason, step);
        }

        public void ClientFail(string clientId, string reason, string step)
        {
            log.Error(String.Format("Client {0} Failed, Reason: {1}, Step: {2}", clientId, reason, step));
            CaseResult = String.Format("Failed: {0} @ {1}", reason, step);
            mExecutionQueueOpen = false; // close the execution queue for new steps
            mExecutionQueue.Clear();     // clear the queue, no reason to execute steps anymore
            StopCurrentTestCase = true;  // request test case teardown
            serviceProxy.ClientFail(clientId, reason, step);
        }

        /// <summary>
        /// For keeping the connection to service open
        /// </summary>
        /// <returns>
        /// 0 success, 
        /// 1 channel open but not registered in service 
        /// -1 channel lost
        /// </returns>
        public int KeepAlive()
        {
            try
            {
                bool ret = serviceProxy.KeepAlive(ClientId);
                if (ret)
                {
                    return 0; // all ok
                }
                else
                {
                    return 1; // channel ok, not registered
                }
            }
            catch
            {
                DebugMessage("Channel lost to Leader service");
                return -1;
            }
        }

        #endregion

        #region Client controlling operations called by Leader (Interface implementation)

        public bool Ping()
        {
            return true;
        }

        public string GetClientId()
        {
            return ClientId;
        }
        
        public void PressKey(string key, int delay)
        {
            log.Error("Not Handled: GraniteFollowerClient Press key: " + key + " delay: " + delay);
        }

        public void TouchEvent(List<TouchTask> graniteTouchTasks)
        {
            log.Debug("TouchData received");
            foreach (var touchTask in graniteTouchTasks)
            {
                ExecutionQueue = touchTask;
            }
            
        }

        /// <summary>
        /// Leader can ask if follower is ready for taking new test case
        /// </summary>
        /// <returns>
        /// 0 if ready
        /// -1 if current test case has been initialized
        /// -2 if queue is empty, but still recovering after execution
        /// otherwise the lenght of the execution queue
        /// </returns>
        public int GetStatus()
        {
            if (ExecutionQueueLen > 0)
            {
                log.Debug("GetStatus: Execution Queue len " + ExecutionQueueLen);
                return ExecutionQueueLen;
            }
            else if (!TearDownFinished)
            {
                log.Debug("GetStatus: Teardown ongoing..");
                return -2;
            }
            else if (CurrentTestCase[0] != null)
            {
                log.Debug("GetStatus: No case in execution");
                return -1;
            }
            else
            {
                log.Debug("GetStatus: Ready for steps..");
                return 0;
            }
        }

        /// <summary>
        /// Return a dictionary containing current resultss
        /// </summary>
        /// <returns>
        /// string result, string resultlink
        /// </returns>
        public Dictionary<string, string> GetResults()
        {
            Dictionary<string, string> results = new Dictionary<string, string>();
            results.Add("Result", CaseResult);
            results.Add("Video", ResultLink);
            results.Add("ResultDir", ResultDir);
            results.Add("Duration", ExecutionTime.ToString());
            results.Add("EndTime", EndTime.ToString());
            
            string imagename;
            for (int i = 0; i < ScreenCaptures.Count ; i++)
            {
                imagename = "Capture" + i;
                results.Add(imagename, ScreenCaptures[i]);
            }

            return results;
        }

        public bool InitializeTestCase(string[] attributes)
        {
            log.Debug("GraniteFollowerClient Initializing test case");
            if (ExecutionQueueLen > 0 | !TearDownFinished )
            {
                if (!TearDownFinished)
                {
                    DebugMessage("WARNING: cannot initialize test case, existing case teardown has not been finished! Closing execution queue and stopping current test case.");
                }
                else
                {
                    DebugMessage("WARNING: cannot initialize test case, execution queue has not been finished! Closing execution queue and stopping current case.");
                }
                mExecutionQueueOpen = false;
                StopCurrentTestCase = true;
                return false;
            }
            mCurrentTestCase = attributes;
            StopCurrentTestCase = false;
            TearDownFinished = false;
            mExecutionQueueOpen = true;
            ExecutionSuccess = false;
            return true;
        }

        public void StopTest()
        {
            log.Debug("GraniteFollowerClient StopTest");
            mExecutionQueueOpen = false; // avoid any excess tasks (comments etc) coming
            StopCurrentTestCase = true;
            if (ExecutionQueueLen > 0)
            {
                log.Info("Warning: StopTest, queue is not empty!");
            }
            
        }

        public void SaveCurrentState(XElement state)
        {
            log.Debug("Save current state");
            log.Debug(state.ToString());
        }

        public void ExecuteString(StringTask st)
        {
            log.Debug("Execute " + st.ExecString);
            ExecutionQueue = st;
        }

        public void SaveLayoutMaps(LayoutMapSaveTask st)
        {
            log.Debug("Received layoutmaps");
            ExecutionQueue = st;
        }

        public void SaveImageDictionary(Dictionary<string, string> imageDict)
        {
            log.Debug("Received image dictionary");
            foreach (KeyValuePair<string, string> kvp in imageDict)
            {
                log.Debug(String.Format("Key = {0}, Value = {1}",kvp.Key, kvp.Value));
            }
            ExecutionQueue = new ImageDictSaveTask("", "", imageDict);
        }

        public void InputString(InputTask inputTask)
        {
            log.Debug("InputTask received: " + inputTask.InputString + " evaluate " + inputTask.Evaluate);
            ExecutionQueue = inputTask;
        }
		
		public void RemotePhoneExecute(RemotePhoneTask remoteTask)
        {
            log.Debug("RemotePhoneTask received");
            ExecutionQueue = remoteTask;
        }

        public void VirtualPhoneExecute(VirtualPhoneTask virtualPhoneTask)
        {
            log.Debug("VirtualPhoneTask received");
            ExecutionQueue = virtualPhoneTask;
        }
		
        #endregion
        
        #region Connection creation methods to be called by ironpython client

        public void Connect(string serviceUri)
        {
            NetTcpBinding binding = new NetTcpBinding(SecurityMode.None, true);
            binding.CloseTimeout = TimeSpan.FromSeconds(30);
            binding.OpenTimeout = TimeSpan.FromSeconds(30);
            binding.ReceiveTimeout = TimeSpan.MaxValue;
            binding.SendTimeout = TimeSpan.FromSeconds(30);
            binding.ReliableSession.InactivityTimeout = TimeSpan.FromMinutes(1);
            binding.ReliableSession.Ordered = true;
            binding.MaxReceivedMessageSize = 524288;
            binding.MaxBufferSize = 524288;
            binding.MaxBufferPoolSize = 4194304;

            DuplexChannelFactory<IGraniteLeadService> pipeFactory = new DuplexChannelFactory<IGraniteLeadService>(this, binding, new EndpointAddress(serviceUri));
            serviceProxy = pipeFactory.CreateChannel();
            IsConnectedToService = true;
            ServiceUri = serviceUri;

            //NetTcpBinding binding = new NetTcpBinding();
            // TODO: Check whether modifying the default timeous is either a good or a bad idea when running over a TCP pipe.
            //binding.ReceiveTimeout = TimeSpan.MaxValue;
            //binding.MaxReceivedMessageSize = 524288;
            //binding.MaxBufferSize = 524288;
            //binding.MaxBufferPoolSize = 4194304;
            //DuplexChannelFactory<IGraniteLeadService> pipeFactory = new DuplexChannelFactory<IGraniteLeadService>(this, binding, new EndpointAddress(serviceUri));
            //serviceProxy = pipeFactory.CreateChannel();
            //IsConnectedToService = true;
            //((IContextChannel)serviceProxy).OperationTimeout = TimeSpan.MaxValue;
        }

        public void SubscribeToService(string clientId)
        {
            serviceProxy.ClientSubscribe(clientId);
            ClientId = clientId;
        }

        public bool Reconnect()
        {
            Dispose();
            IsConnectedToService = false;
            try
            {
                Connect(ServiceUri);
                SubscribeToService(ClientId);
                return true;
            }
            catch (System.ServiceModel.EndpointNotFoundException)
            {
                log.Debug("Reconnecting failed. Leader service could not be reached");
                return false;
            }
            catch (Exception e)
            {
                log.Debug(String.Format("Reconnecting failed. Exception {0}: {1}", e.GetType().ToString(), e));
                return false;
            }
        }

        public List<string> DiscoverAvailableServices(string proxyAddress)
        {
            List<string> discoveredEndpoints = new List<string>();
            // Create a DiscoveryEndpoint that points to the DiscoveryProxy
            Uri probeEndpointAddress = new Uri(proxyAddress);
            DiscoveryEndpoint discoveryEndpoint = new DiscoveryEndpoint(new NetTcpBinding(), new EndpointAddress(probeEndpointAddress));

            // Create a DiscoveryClient passing in the discovery endpoint
            using (DiscoveryClient discoveryClient = new DiscoveryClient(discoveryEndpoint))
            {
                try
                {
                    // Search for services that implements IGraniteLeadService            
                    FindResponse findResponse = discoveryClient.Find(new FindCriteria(typeof(IGraniteLeadService)));
                    discoveredEndpoints.AddRange(findResponse.Endpoints.Select(endpoint => endpoint.Address.Uri.ToString()));
                }
                catch (TargetInvocationException)
                {
                    throw new InvalidOperationException("The client was unable to connect to connect to the discovery proxy. Ensure that the proxy is up and running!");
                }
            }

            return discoveredEndpoints;
        }

        #endregion
        
        #region IDisposable members

        public void Dispose()
        {
            if (this.serviceProxy != null)
            {
                // Try to close and dispose proxy object. It should not matter if Close/Dispose fails,
                // GC should take care of cleaning these objects due to reference count decreases to zero.
                try
                {
                    ((IClientChannel)serviceProxy).Close();
                }
                catch { }
                try
                {
                    ((IDisposable)serviceProxy).Dispose();
                }
                catch { }
                this.serviceProxy = null;
                IsConnectedToService = false;
                //Console.WriteLine("GraniteFollowerClient: Dispose");
            }
        }

        #endregion
    }
}
