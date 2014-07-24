using System;
using System.Collections.Generic;
using System.ServiceModel;
using System.ServiceModel.Discovery;
using System.Threading;
using System.Threading.Tasks;
using Nokia.Granite.IPC.Interfaces;

using System.Xml;
using System.Dynamic;
using System.Collections;
using System.Xml.Linq;

// Import log4net classes.
using log4net;
using log4net.Config;

namespace Nokia.Granite.IPC.Services.LeadFollower
{
    public class GraniteLeadService : IDisposable
    {
        // Uri of WcfDiscoveryProxy
        private const string DiscoveryProxyAddress = "net.tcp://localhost:9021/Announcement";
        // Uri of this service.
        private const string ServiceBaseAddress = "net.tcp://localhost:8022/GraniteLeadService";

        protected static readonly ILog log = LogManager.GetLogger("LeaderFollowerLogger");

        #region ServiceClass for firing client side callbacks

        // NOTE: Serviceclass / IGraniteLeadService implementation needs to be in own class  
        // since it's being called each time client connects.

        [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single, ConcurrencyMode = ConcurrencyMode.Multiple)]
        public class ServiceClass : IGraniteLeadService
        {
            public List<Follower> Followers;
            public List<string> ClientVariables = new List<string>();
            
            public class Follower
            {
                public string ClientId;
                public IGraniteFollowerCallback Callback;

                public Follower(string clientId, IGraniteFollowerCallback cb)
                {
                    ClientId = clientId;
                    Callback = cb;
                }
            }

            public ServiceClass()
            {
                Followers = new List<Follower>();
            }

            // client can inform that it holds a variable
            public void AddVariable(string variable)
            {
                if (!ClientVariables.Contains(variable))
                {
                    log.Debug("New variable on client: " + variable);
                    ClientVariables.Add(variable);
                }
            }

            // Execution queue accessed by Leader only
            internal Queue mExecutionQueue = new Queue();
            public Object LeaderExecutionQueue
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
                    if (value == null)
                    {
                        mExecutionQueue.Clear();
                    }
                    else
                    {
                        mExecutionQueue.Enqueue(value);
                    }
                }
            }
            
            public void ConfigurationRequest(ConfigurationRequestTask ct)
            {
                LeaderExecutionQueue = ct;
            }

            public bool KeepAlive(string clientId)
            {
                foreach (Follower f in Followers)
                {
                    if (f.ClientId == clientId)
                    {
                        return true;
                    }
                }
                return false;
            }

            // unexpected things will fail the case in leader
            public void ClientFiasco(string clientId, string reason, string step)
            {
                FiascoTask ft = new FiascoTask(clientId, reason, step);
                DebugMessage(String.Format("Client {0} FIASCO at step {1}, reason {2}", ft.ClientId, ft.Step, ft.Reason));
                LeaderExecutionQueue = ft;
            }

            // unexpected things will generate warning in leader
            public void ClientFail(string clientId, string reason, string step)
            {
                FailureTask ft = new FailureTask(clientId, reason, step);
                DebugMessage(String.Format("Client {0} Failed at step {1}, reason {2}", ft.ClientId, ft.Step, ft.Reason));
                LeaderExecutionQueue = ft;
            }

            /// <summary>
            /// Remove follower from list of followers
            /// </summary>
            /// <param name="clientId">follower id to be removed</param>
            /// <returns>
            /// True if clientId was found and removed, otherwise False.
            /// </returns>
            public bool RemoveFollower(string clientId)
            {
                bool ret = false;
                for (int i = Followers.Count - 1; i >= 0; i--)
                {
                    if (Followers[i].ClientId == clientId)
                    {
                        Followers.Remove(Followers[i]);
                        DebugMessage("GraniteLeadService: Client " + clientId + " unsubscribed at " + DateTime.Now);
                        ret = true;
                    }
                }
                return ret;
            }

            public bool Connect()
            {
                return true;
            }

            public bool ClientSubscribe(string clientId)
            {
                try
                {
                    IGraniteFollowerCallback callback = OperationContext.Current.GetCallbackChannel<IGraniteFollowerCallback>();

                    if (RemoveFollower(clientId))
                    {
                        DebugMessage("GraniteLeadService: Client " + clientId + " re-subscribing..");
                    }

                    Follower f = new Follower(clientId, callback);
                    Followers.Add(f);
                    DebugMessage("GraniteLeadService: Client " + clientId + " subscribed at " + DateTime.Now + " ThreadID: " + Thread.CurrentThread.ManagedThreadId.ToString());
                    
                    return true;
                }
                catch (Exception e)
                {
                    DebugMessage("GraniteLeadService: Client " + clientId + " failed to subscribe at " + DateTime.Now + "Error: " + e);
                    return false;
                }
            }

            public bool ClientUnsubscribe(string clientId)
            {
                try
                {
                    return RemoveFollower(clientId);
                }
                catch (Exception e)
                {
                    DebugMessage("GraniteLeadService: Client " + clientId + " failed to unsubscribe at " + DateTime.Now + "Error: " + e);
                    return false;
                }
            }
        }

        #endregion

        #region Private fields

        private CancellationTokenSource wcfHostTaskCancellation;
        private static GraniteLeadService instance;
        private bool running = false;
        
        #endregion

        public ServiceClass serviceClass;
        public string[] currentTestCaseDetails = new string[6];
        public string currentTestStep;
        public bool sendTouches = true;
        public List<string> inputParams = new List<string>();
        public bool caseRunning { get { return running; } }
        
        // Dictionary for layoutMaps
        //public Dictionary<int, Dictionary<string, Array
        //public struct charData
        //{
        //    public int[] coords = new int[2];
        //    public int flags;
        //    public int repeats;
        //}

        #region Constructor

        private GraniteLeadService()
        {
            //Debugger.Launch();
            //GlobalContext.Properties["LoggingBase"] = Directory.GetCurrentDirectory();
            //XmlConfigurator.Configure(new System.IO.FileInfo("..\\settings\\LeaderFollowerLogSettings.xml"));
            //log = LogManager.GetLogger(typeof(GraniteLeadService));
            this.serviceClass = new ServiceClass();
        }

        public static GraniteLeadService Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new GraniteLeadService();
                }
                return instance;
            }
        }

        #endregion

        #region Service controlling methods called from ironpython / leader

        public void ServiceStart()
        {
            this.wcfHostTaskCancellation = new CancellationTokenSource();
            Task.Factory.StartNew(() => wcfHostTaskMethod(wcfHostTaskCancellation.Token), wcfHostTaskCancellation.Token);    
        }

        //public void WaitForSubscribers()
        //{
        //    while (this.serviceClass.Followers.Count != 1)
        //    {
        //        Console.WriteLine("Waiting for subscribers... Amount of subscribers now: " + this.serviceClass.Followers.Count);
        //        Thread.Sleep(1000);
        //    }
        //}

        #endregion

        #region Client controlling methods called from ironpython / leader

        public int LeaderExecutionQueueLen()
        {
            return serviceClass.mExecutionQueue.Count;
        }

        // DebugMessage will log to file and to Granite output
        protected static void DebugMessage(string message)
        {
            Console.WriteLine(message);
            log.Debug(message);
        }

        public void InitializeTestCase(string[] testCaseAttributes)
        {
            // flexible version of tc attributes
            //string[] attributes = new string[testCaseAttributes.Count];

            Array.Clear(currentTestCaseDetails, 0, currentTestCaseDetails.Length);
            testCaseAttributes.CopyTo(currentTestCaseDetails, 0);
            
            log.Debug("GraniteLeadService: Initializing test case " + string.Join(", ", testCaseAttributes));
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                try
                {
                    serviceClass.Followers[i].Callback.InitializeTestCase(currentTestCaseDetails);
                }
                catch (Exception e)
                {
                    DebugMessage("Initialize test case: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
                
            }
            serviceClass.ClientVariables.Clear();
            running = true;
        }
        /// <summary>
        /// Check followers whether they are ready for starting a new test case
        /// <returns>
        /// Dictionary (string clientID, Dictionary (string caseresult, int status))
        /// statuses:
        /// 0 if ready
        /// -1 if current test case has been initialized
        /// -2 if queue is empty, but still recovering after execution
        /// otherwise the lenght of the execution queue
        /// </returns>
        /// </summary>
        public Dictionary<string, int> GetStatus()
        {
            log.Debug("GraniteLeadService: Query follower statuses..");
            Dictionary<string, int> ret = new Dictionary<string, int>();
            int readyvalue;
            
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {   
                try
                {
                    readyvalue = serviceClass.Followers[i].Callback.GetStatus();
                    ret.Add(serviceClass.Followers[i].ClientId, readyvalue);
                }
                catch (Exception e)
                {
                    DebugMessage("ExecuteString: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }
            return ret;
        }

        /// <summary>
        /// Get follower results
        /// <returns>
        /// Dictionary (string clientId, Dictionary (string result, string resultlink) )
        ///     clientId 
        ///     Dictionary: result is 'Passed', 'Reset' etc, resultlink a link to video/result
        /// </returns>
        /// </summary>
        public Dictionary<string, Dictionary<string, string>> GetResults()
        {
            log.Debug("GraniteLeadService: Query follower results..");
            Dictionary<string, Dictionary<string, string>> ret = new Dictionary<string, Dictionary<string, string>>();
            Dictionary<string, string> followerResult;
            
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                try
                {
                    followerResult = serviceClass.Followers[i].Callback.GetResults();
                    ret.Add(serviceClass.Followers[i].ClientId, followerResult);
                }
                catch (Exception e)
                {
                    DebugMessage("ExecuteString: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }
            return ret;
        }

        /// <summary>
        /// Add plain string to clients execution queue
        /// </summary>
        /// <param name="s">String to be added to queue</param>
        public void ExecuteString(string s)
        {
            if ( s.Trim().StartsWith("self.")) // set step name based on 
            {
                currentTestStep = s;
            }

            StringTask st = new StringTask(currentTestCaseDetails[0], currentTestStep, s);
            log.Debug("GraniteLeadService: Add to client queue: " + s);
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                try
                {
                    serviceClass.Followers[i].Callback.ExecuteString(st);
                }
                catch (Exception e)
                {
                    DebugMessage("ExecuteString: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }
        }

        /// <summary>
        /// Sets the client stop test boolean true
        /// </summary>
        public void StopTest()
        {
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                log.Debug("GraniteLeadService: Stop current test case");
                try
                {
                    serviceClass.Followers[i].Callback.StopTest();
                }
                catch (Exception e)
                {
                    DebugMessage("StopTest: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }
            Array.Clear(currentTestCaseDetails, 0, currentTestCaseDetails.Length);
            running = false;
        }

        /// <summary>
        /// Sets the client stop test boolean true
        /// </summary>
        public void AbortCurrentTestCase()
        {
            log.Debug("GraniteLeadService: Abort current test case");
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                try 
                { 
                    serviceClass.Followers[i].Callback.AbortCurrentTestCase();
                }
                catch (Exception e)
                {
                    DebugMessage("AbortCurrentTestCase: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }
            running = false;
        }
        /// <summary>
        /// Save the current state to followers
        /// </summary>
        /// <param name="xmlDump">XmlDocument to send to follower</param>
        public void SaveCurrentState(XElement state)
        {
            log.Debug("GraniteLeadService: Save xml dump");
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                try
                {
                    serviceClass.Followers[i].Callback.SaveCurrentState(state);
                }
                catch (Exception e)
                {
                    DebugMessage("SaveCurrentState: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }

        }

        /// <summary>
        /// Input string on follower
        /// </summary>
        /// <param name="inputStr">string which needs to be evaluated</param>
        public void InputString(string inputStr, bool evaluate, string mode, string orientation, int delayBetweenPresses, string toBeEvaluatedSettings)
        {
            InputTask inputTask = new InputTask(currentTestCaseDetails[0], currentTestStep, inputStr, evaluate, mode, orientation, delayBetweenPresses, toBeEvaluatedSettings);
            log.Debug("New InputTask created, evaluate: " + inputTask.Evaluate);
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                try
                {
                    serviceClass.Followers[i].Callback.InputString(inputTask);
                }
                catch (Exception e)
                {
                    DebugMessage("InputString: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }

        }
			
		/// <summary>
        /// Execute scripting method in follower remote
        /// </summary>
        /// <param name="method">name of method</param>
        /// <param name="args">List of arguments for method call</param>
        /// <param name="kwargs">Dictionary of keyword arguments for method call</param>
        public void RemotePhoneExecute(string method, List<object> args, List<int> argsEvalIndex, Dictionary<object, object> kwargs, List<int> kwargsEvalIndex, string toBeEvaluatedSettings)
        {
            RemotePhoneTask remoteTask = new RemotePhoneTask(currentTestCaseDetails[0], currentTestStep, method, args, argsEvalIndex, kwargs, kwargsEvalIndex, toBeEvaluatedSettings);
            
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                try
                {
                    serviceClass.Followers[i].Callback.RemotePhoneExecute(remoteTask);
                }
                catch (Exception e)
                {
                    DebugMessage("RemotePhoneExecute: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }

        }

        /// <summary>
        /// Execute scripting method in Virtual Phone
        /// </summary>
        /// <param name="method">name of method</param>
        /// <param name="args">List of arguments for method call</param>
        /// <param name="kwargs">Dictionary of keyword arguments for method call</param>
        public void VirtualPhoneExecute(string method, List<object> args, List<int> argEvalIndex, Dictionary<object, object> kwargs, List<int> kwargEvalIndex)
        {
            VirtualPhoneTask virtualPhoneTask = new VirtualPhoneTask(currentTestCaseDetails[0], currentTestStep, method, args, argEvalIndex, kwargs, kwargEvalIndex);

            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                try
                {
                    serviceClass.Followers[i].Callback.VirtualPhoneExecute(virtualPhoneTask);
                }
                catch (Exception e)
                {
                    DebugMessage("VirtualPhoneExecute: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }

        }

        /// <summary>
        /// Save the image dict to followers
        /// </summary>
        /// <param name="xmlDump">XmlDocument to send to follower</param>
        //public void SaveImageDictionary(Dictionary<string, string> imageDict)
        public void SaveImageDictionary(Dictionary<string, string> imageDict)
        {
            log.Debug("SaveImageDictionary");
            // Dictionary<string, string> t = (Dictionary<string, string>)imageDict;
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                try
                {
                    serviceClass.Followers[i].Callback.SaveImageDictionary(imageDict);
                }
                catch (Exception e)
                {
                    DebugMessage("SaveImageDictionary: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }

        }

        /// <summary>
        /// Send layout map repr as string to Followers
        /// </summary>
        /// <param name="xmlDump">XmlDocument to send to follower</param>
        //public void SaveImageDictionary(Dictionary<string, string> imageDict)
        public void SendLayoutMaps(string layoutRepr)
        {
            log.Debug("SendLayoutMaps");
            LayoutMapSaveTask st = new LayoutMapSaveTask(currentTestCaseDetails[0], currentTestStep, layoutRepr);
            
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                try
                {
                    serviceClass.Followers[i].Callback.SaveLayoutMaps(st);
                }
                catch (Exception e)
                {
                    DebugMessage("SendLayoutMaps: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }

        }

        /// <summary>
        /// Presses the given key.
        /// </summary>
        /// <param name="key">Key to press</param>
        /// <param name="delay">Delay in millisecond</param>
        public void PressKey(string key, int delay)
        {
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                log.Debug("GraniteLeadService: PressKey " + key + " delay " + delay);
                try
                {
                    serviceClass.Followers[i].Callback.PressKey(key, delay);
                }
                catch (Exception e)
                {
                    DebugMessage("PressKey: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }
        }

        /// <summary>
        /// Generates a touch even on the Touch Panel Controller.
        /// Either a press or a move event
        /// </summary>
        /// <param name="touchData"></param>
        public void TouchEvent(List<XElement> touchDatas, double interval)
        {
            // create a list of TouchTasks
            List<TouchTask> tasks = new List<TouchTask>();
            foreach (var touchData in touchDatas)
            {
                tasks.Add(new TouchTask(currentTestCaseDetails[0], currentTestStep, touchData, interval));
                interval = 0; // if more touches are in the same task, their interval are 0
                //log.Debug("Added touchdata {0}", touchData.ToString());
            }

            if (tasks.Count > 0)
            {
                for (int i = 0; i < serviceClass.Followers.Count; i++)
                {
                    try
                    {
                        serviceClass.Followers[i].Callback.TouchEvent(tasks);
                    }
                    catch (Exception e)
                    {
                        DebugMessage("TouchEvent: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                        serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                    }
                }
            }
        }

        /// <summary>
        /// Ping each follower and remove ones which are not connected to service
        /// </summary>
        public void PingFollowers()
        {
            for (int i = 0; i < serviceClass.Followers.Count; i++)
            {
                try
                {
                    if (!serviceClass.Followers[i].Callback.Ping())
                    {
                        serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                    }
                }
                catch (Exception e)
                {
                    DebugMessage("PingFollower: Client " + serviceClass.Followers[i].ClientId + " error: " + e + ".\nFollower was removed");
                    serviceClass.RemoveFollower(serviceClass.Followers[i].ClientId);
                }
            }
        }

        //public void SendAnnouncements()
        //{
        //    Uri announcementEndpointAddress = new Uri(DiscoveryProxyAddress);
        //    AnnouncementEndpoint announcementEndpoint = new AnnouncementEndpoint(new NetTcpBinding(), new EndpointAddress(announcementEndpointAddress));
        //    AnnouncementClient client = new AnnouncementClient(announcementEndpoint);
        //    //var endpointDiscoveryMetadata = EndpointDiscoveryMetadata.FromServiceEndpoint(netTcpEndpoint);

        //    //client.AnnounceOnline(endpointDiscoveryMetadata);
        //}

        #endregion

        #region Private methods

        private void wcfHostTaskMethod(CancellationToken ct)
        {
            Uri baseAddress = new Uri(ServiceBaseAddress);
            Uri announcementEndpointAddress = new Uri(DiscoveryProxyAddress);

            // this gets called each time client connects ((DuplexChannelFactory).CreateChannel() -> serviceClass instance is created
            using (ServiceHost serviceHost = new ServiceHost(this.serviceClass, baseAddress))
            {
                NetTcpBinding binding = new NetTcpBinding(SecurityMode.None, true);
                binding.SendTimeout = TimeSpan.FromSeconds(10);
                binding.ReceiveTimeout = TimeSpan.MaxValue;
                binding.ReliableSession.InactivityTimeout = TimeSpan.FromMinutes(5);
                binding.ReliableSession.Ordered = true;
                binding.MaxReceivedMessageSize = 524288;
                binding.MaxBufferSize = 524288;
                binding.MaxBufferPoolSize = 4194304;
                serviceHost.AddServiceEndpoint(typeof(IGraniteLeadService), binding, string.Empty);

                // Create an announcement endpoint, which points to the Announcement Endpoint hosted by the proxy service.
                //AnnouncementEndpoint announcementEndpoint = new AnnouncementEndpoint(new NetTcpBinding(), new EndpointAddress(announcementEndpointAddress));
                //ServiceDiscoveryBehavior serviceDiscoveryBehavior = new ServiceDiscoveryBehavior();
                //serviceDiscoveryBehavior.AnnouncementEndpoints.Add(announcementEndpoint);

                //// Make the service discoverable
                //serviceHost.Description.Behaviors.Add(serviceDiscoveryBehavior);
                
                serviceHost.Open();
                log.Debug(String.Format("GraniteLeadService Started at {0}", baseAddress));
                // Wait while waithandle is signaled.
                ct.WaitHandle.WaitOne();
                try
                {
                    // Give the host 10 seconds to close
                    serviceHost.Close(TimeSpan.FromSeconds(10));
                }
                catch { /* If Abort or Close fails, it should not matter since host will be Disposed anyway due to using block is used */ }
                if (serviceHost.State != CommunicationState.Closed)
                {
                    try
                    {
                        serviceHost.Abort();
                    }
                    catch { /* If Abort or Close fails, it should not matter since host will be Disposed anyway due to using block is used */ }
                }
            }
        }

        #endregion

        #region IDisposable members

        public void Dispose()
        {            
            // Cancel task and dispose resources
            try
            {
                if (this.wcfHostTaskCancellation != null)
                {
                    this.wcfHostTaskCancellation.Cancel();
                    this.wcfHostTaskCancellation.Dispose();
                    GC.SuppressFinalize(this);
                    this.wcfHostTaskCancellation = null;
                    log.Debug("GraniteLeadService: Dispose");
                }
            }
            catch{ /* May not able to dispose cancellation token if process is being closed by force. GC should eventually handle this.*/}
        }

        #endregion
    }
}
