using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using CookComputing.XmlRpc;
using TestAutomation.Gui.Marble.Settings;
using log4net;

namespace TestAutomation.Gui.Marble.PoxBackend
{
    #region Exceptions

    /// <summary>
    /// The exception that is thrown when POX Connection error is detected.
    /// </summary>
    public class PoxConnectionException : SystemException
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="PoxConnectionException"/> class with a specified error message.
        /// </summary>
        /// <param name="message">The message that describes the error. </param>
        public PoxConnectionException(string message) : base(message){}
    }

    /// <summary>
    /// The exception that is thrown when POX Robot error is detected.
    /// </summary>
    public class PoxRobotException : SystemException
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="PoxRobotException"/> class with a specified error message.
        /// </summary>
        /// <param name="message">The message that describes the error. </param>
        public PoxRobotException(string message) : base(message) { }
    }

    #endregion

    /// <summary>
    /// Main class for XmlRpcClient
    /// </summary>
    public class XmlRpcClient
    {
        #region XML-RPC.Net Interface

        /// <summary>
        /// IXmlRpcProxy derived interface
        /// that defines XmlRpcMethods to use when communicating
        /// with the server controller.
        /// </summary>
        public interface IPoxInterface : IXmlRpcProxy
        {
            /// <summary>
            /// XmlRpcMethod. Authenticates user with Server Controller.
            /// </summary>
            /// <param name="userAccount">The user account for Server Controller.</param>
            /// <param name="password">The password for Server Controller.</param>
            /// <returns>Status as an array (Array).</returns>
            [XmlRpcMethod]
            object[] userAuthenticate(string userAccount, string password);

            /// <summary>
            /// XmlRpcMethod. Commands Server Controller to start a job.
            /// </summary>
            /// <param name="userAccount">The user account for Server Controller.</param>
            /// <param name="hash">The hash key received from the Server Controller.</param>
            /// <param name="jobArray">The job array for Server Controller.</param>
            /// <returns>Status as an array (Array).</returns>
            [XmlRpcMethod]
            object[] start(string userAccount, string hash, XmlRpcStruct jobArray);

            /// <summary>
            /// XmlRpcMethod. Inserts a command to dynamic job.
            /// </summary>
            /// <param name="userAccount">The user account for Server Controller.</param>
            /// <param name="hash">The hash key received from the Server Controller.</param>
            /// <param name="parameters">The job id received from the Server Controller.</param>
            /// <returns>Status as an array (Array).</returns>
            [XmlRpcMethod]
            object[] insert(string userAccount, string hash, object[] parameters);

            /// <summary>
            /// XmlRpcMethod. Queries the job status.
            /// </summary>
            /// <param name="userAccount">The user account for Server Controller.</param>
            /// <param name="hash">The hash key received from the Server Controller.</param>
            /// <param name="jobId">The job id received from the Server Controller.</param>
            /// <returns>Status as an array (Array).</returns>
            [XmlRpcMethod]
            object[] status(string userAccount, string hash, int jobId);

            /// <summary>
            /// XmlRpcMethod. Commands Server Controller to stop a job.
            /// </summary>
            /// <param name="userAccount">The user account for Server Controller.</param>
            /// <param name="hash">The hash key received from the Server Controller.</param>
            /// <param name="jobId">The job id received from the Server Controller.</param>
            /// <returns>Status as an array (Array).</returns>
            [XmlRpcMethod]
            object[] stop(string userAccount, string hash, int jobId);

            /// <summary>
            /// XmlRpcMethod. Queries the Server Controller status.
            /// </summary>
            /// <returns>Status as an array (Array).</returns>
            [XmlRpcMethod]
            object[] serverStatus();
        }

        #endregion

        #region Parameter classes, definitions and enumerations

        /// <summary>
        /// The default job length Marble uses to initialize POX.
        /// If job length reported by POX is shorter than this, job length will be increased. 
        /// </summary>
        private const int defaultJobLength = 108000;

        internal class PoxPhone
        {
            public string MarblePhoneName;
            public string AlternativePhoneName;
            public string PhoneNumber;
            public int poxRobotIndex;
            public int marblePhoneIndex;

            public PoxPhone()
            {
                this.MarblePhoneName = string.Empty;
                this.AlternativePhoneName = string.Empty;
                this.PhoneNumber = string.Empty;
                this.poxRobotIndex = -1;
                this.marblePhoneIndex = -1;
            }
        }

        internal class JobInfo
        {
            public TimeSpan JobLength;
            public DateTime JobLengthSetTime;
            public int JobId;

            public JobInfo()
            {
                this.JobLength = TimeSpan.FromSeconds(0);
                this.JobId = -1;
                this.JobLengthSetTime = DateTime.Now;
            }
        }
        #endregion

        #region Private members

        /// <summary>
        /// The Xml-Rpc.Net interface to POX server.
        /// </summary>
        private IPoxInterface xmlRpcProxy;

        private const string useraccount = "ouluci";
        private const string password = "ouluci";
        private readonly ILog log;
        private JobInfo jobInfo;
        private string poxUri;
        private readonly object connectionLock = new object();
        private dynamic settings;
        private List<PoxPhone> poxPhones;
        
        private string device1voipaccount;
        private string device1voippassword;
        private string device1Number;
        private string device2Number;

        private string poxSIPRegistrarServerUri;
        private string poxSipProxy;
        private bool poxFailure;
        private int poxFailAmountMax;

        /// <summary>
        /// How many times RPC calls will be retries in case of web time out.
        /// </summary>
        private int rpcRetryCount = 10;

        /// <summary>
        /// The time before RPC call is retried, in milliseconds.
        /// </summary>
        private int rpcRetryDelay = 5000;

        private int failAmount;

        #endregion

        #region Properties

        public int JobId
        {
            get { return this.jobInfo.JobId; }
        }

        public int FailAmount
        {
            get { return this.failAmount; }
        }
        

        #endregion

        #region Constructor(s)

        /// <summary>
        /// Initializes a new instance of the XmlRpcClient class.
        /// </summary>
        public XmlRpcClient(string poxUri)
        {
            this.poxFailure = false;
            this.failAmount = 0;
            this.log = LogManager.GetLogger("FrameworkLogger");
            this.log.Debug("-  Pox-Backend XML-RPC Client object created. POX URI: " + poxUri);
            this.jobInfo = new JobInfo();

            this.poxPhones = new List<PoxPhone>();
            this.settings = SettingsManager.Instance;
            this.poxFailAmountMax = this.settings.TestRun.POXFailAmountMax;
            this.rpcRetryCount = this.settings.TestRun.POXmlRpcCommandRetryCount;
            this.poxSipProxy = this.settings.TestRun.POXSIPProxy;
            this.log.Debug("-  Using " + this.poxSipProxy + " SIP Proxy");

            // XML RPC Proxy
            this.xmlRpcProxy = XmlRpcProxyGen.Create<IPoxInterface>();
            this.xmlRpcProxy.UseIntTag = true;
            this.xmlRpcProxy.UseStringTag = true;
            this.xmlRpcProxy.XmlEncoding = Encoding.UTF8;
            this.xmlRpcProxy.NonStandard = XmlRpcNonStandard.All;
            this.xmlRpcProxy.Timeout = this.settings.TestRun.POXmlRpcProxyTimeout * 1000;
            this.rpcRetryDelay = this.settings.TestRun.POXmlRpcDelayBetweenRetries * 1000;
            this.connectPox(poxUri);
            this.poxUri = poxUri;
            this.device1voipaccount = string.Empty;
            this.device1voippassword = string.Empty;
            this.poxSIPRegistrarServerUri = string.Empty;
            this.device1Number = !string.IsNullOrEmpty(this.settings.Main.SIM1PhoneNumber) ? this.settings.Main.SIM1PhoneNumber : this.settings.Main.SIM2PhoneNumber;

            if (!string.IsNullOrEmpty(this.settings.Main.SIM2PhoneNumber) && this.device1Number != this.settings.Main.SIM2PhoneNumber)
                this.device2Number = this.settings.Main.SIM2PhoneNumber;

            SettingsManager.Instance.SettingPropertyQuery += settingPropertyQueryHandler;
            SettingsManager.Instance.SettingValueChanged += new SettingPropertyChangedEventHandler(Instance_SettingValueChanged);
        }

        void Instance_SettingValueChanged(SettingPropertyChangedEventArgs args)
        {
            // TODO: Implement handler to situation when Marble main phone number changes?
        }

        #endregion

        #region General Commands

        /// <summary>
        /// Creates a call using the given reference/virtual phone.
        /// </summary>
        public void CreateCall(string phoneNumber, int phone, bool voip = false)
        {
            lock (this.connectionLock)
            {
                // Check that POX job is created and not yet finished
                this.startOrCheckPoxJob();

                string dynamicCommand = voip ? "voipCreateCall" : "createCall";

                // Verify that robot is ready for the call. If no robot created, create a new one.
                string robotPoxName = this.getRobotPoxName(phone);
                if (robotPoxName == null)
                {
                    string marblePhoneName = "Virtual";
                    if (phone > 1)
                        marblePhoneName += phone;

                    this.getRobotPhoneNumber(marblePhoneName);
                    robotPoxName = this.getRobotPoxName(phone);
                }
                    
                string robotState = this.checkRobotStatus(robotPoxName, "idle");
                if (robotState != "idle")
                    throw new InvalidOperationException("Unable to execute "+ dynamicCommand + " on POX robot " + robotPoxName +
                                                        ". Reason: POX reported robot state '" + robotState + "'. Robot state 'idle' expected.");

                // Make the call
                object[] commandArray = new object[4];
                commandArray[0] = this.jobInfo.JobId;
                commandArray[1] = dynamicCommand;
                commandArray[2] = robotPoxName;
                commandArray[3] = phoneNumber;

                this.executeDynamicPoxCommand(dynamicCommand, robotPoxName, commandArray);

                // Wait for outgoing call status
                this.waitForStateChange(dynamicCommand, "outgoing call", robotPoxName);
            }
        }

        /// <summary>
        /// Answers a call ongoing on the given reference/virtual phone.
        /// </summary>
        public void AnswerCall(int phone, bool voip = false)
        {
            lock (this.connectionLock)
            {
                string dynamicCommand = voip ? "voipAnswerCall" : "answerCall";

                // Check that POX job is created and not yet finished
                if (this.jobInfo.JobId == -1 || this.isJobFinished())
                {
                    throw new PoxRobotException(dynamicCommand + " command not possible to execute on POX robot! Reason: no POX job running.");
                }

                // There is a job running. Check joblength
                if (this.shouldCheckJobLength())
                {
                    int jobLength = this.getJobLength();
                    if (jobLength < defaultJobLength)
                    {
                        this.extendJob();
                    }
                }

                // If Job started but no robot inserted yet, cannot execute AnswerCall.
                string robotPoxName = this.getRobotPoxName(phone);
                if (robotPoxName == null)
                    throw new PoxRobotException(dynamicCommand + " command not possible to execute on POX robot! Reason: no POX robot running that can answer the call.");

                // Wait for incoming call status
                this.waitForStateChange(dynamicCommand, "incoming call", robotPoxName);

                // Answer the call
                object[] commandArray = new object[3];
                commandArray[0] = this.jobInfo.JobId;
                commandArray[1] = dynamicCommand;
                commandArray[2] = robotPoxName;

                this.executeDynamicPoxCommand(dynamicCommand, robotPoxName, commandArray);

                // Wait for ongoing call status
                this.waitForStateChange(dynamicCommand, "ongoing call", robotPoxName);
            }
        }

        /// <summary>
        /// Releases a call ongoing on the given reference/virtual phone.
        /// </summary>
        public void ReleaseCall(int phone, bool voip = false)
        {
            lock (this.connectionLock)
            {
                // If job not created or job finished, no need (cannot) execute ReleaseCall.
                if (this.jobInfo.JobId == -1 || this.isJobFinished())
                {
                    return;
                }

                // Also if Job started but no robot inserted yet, no need (cannot) execute ReleaseCall.
                string robotPoxName = this.getRobotPoxName(phone);
                if (robotPoxName == null)
                    return;

                string dynamicCommand = voip ? "voipReleaseCall" : "releaseCall";

                // Release the call in all cases
                object[] commandArray = new object[3];
                commandArray[0] = this.jobInfo.JobId;
                commandArray[1] = "releaseCall";
                commandArray[2] = robotPoxName;

                this.executeDynamicPoxCommand(dynamicCommand, robotPoxName, commandArray);

                // Wait for call status to return to idle
                this.waitForStateChange(dynamicCommand, "idle", robotPoxName);
            }
        }

        /// <summary>
        /// Closes the connection to POX. Unsubscribes eventhandler.
        /// </summary>
        public void Close()
        {
            lock (this.connectionLock)
            {
                SettingsManager.Instance.SettingPropertyQuery -= this.settingPropertyQueryHandler;

                if (this.jobInfo.JobId != -1 && this.xmlRpcProxy != null)
                {
                    int retries = rpcRetryCount + 1;
                    int loop = 0;
                    while (loop++ < retries)
                    {
                        try
                        {
                            xmlRpcProxy.stop(useraccount, "", this.jobInfo.JobId);
                            break;
                        }
                        catch (Exception ex)
                        {
                            if (loop == rpcRetryCount)
                            {
                                throw new PoxConnectionException(
                                    "Stop and close to POX connection failed after trying " + loop + " times. Reason : " +
                                    ex.Message);
                            }
                            this.log.Debug("-  Attempt to stop and close POX connection failed in loop " + loop +
                                           ". Reason: " + ex.Message + ". Retrying... (Total amount of retries to be executed: " + rpcRetryCount + ")");
                            // In case of net timeout wait and try again.
                            Thread.Sleep(this.rpcRetryDelay);
                        }
                    }

                    this.jobInfo.JobId = -1;
                    this.poxPhones.Clear();
                    this.xmlRpcProxy = null;
                }
            }
        }

        #endregion

        #region Private methods

        /// <summary>
        /// Initializes POX server connection.
        /// </summary>
        private void connectPox(string uri)
        {
            lock (this.connectionLock)
            {
                xmlRpcProxy.Url = uri;

                int retries = rpcRetryCount + 1;
                int loop = 0;
                while (loop++ < retries)
                {
                    try
                    {
                        xmlRpcProxy.userAuthenticate(useraccount, password);
                        break;
                    }
                    catch (Exception ex)
                    {
                        if (loop == rpcRetryCount)
                        {
                            this.poxFailure = true;
                            throw new PoxConnectionException("Connect to POX service failed after trying " + loop +
                                                                " times. Reason : " + ex.Message);
                        }
                        this.log.Debug("-  Attempt to connect to POX server failed in loop " + loop + ". Reason: " +
                                       ex.Message + ". Retrying... (Total amount of retries to be executed: " + rpcRetryCount + ")");
                        // In case of net timeout wait and try again.
                        Thread.Sleep(this.rpcRetryDelay);
                    }
                }
            }
        }

        private void startPoxJob()
        {
            lock (this.connectionLock)
            {
                this.log.Debug("-  Starting POX job...");

                XmlRpcStruct phoneInfoStruct = new XmlRpcStruct
                {
                    {"sequence", "dynamic"},
                    {"length", (defaultJobLength * 1.2) + "sec"},
                    {"device1user", "dynamic"},
                    {"device1number", this.device1Number},
                    {"device1server", this.poxSipProxy}

                };

                if (device2Number != null)
                {
                    phoneInfoStruct.Add("device2user", "dynamic");
                    phoneInfoStruct.Add("device2number", this.device2Number);
                    phoneInfoStruct.Add("device2server", this.poxSipProxy);
                }

                int retries = rpcRetryCount + 1;
                int loop = 0;
                this.poxPhones.Clear();
                this.jobInfo.JobId = -1;

                while (loop++ < retries)
                {
                    try
                    {
                        object[] statusArray = xmlRpcProxy.start(useraccount, password, phoneInfoStruct);
                        this.jobInfo.JobId = (int)statusArray[1];
                        string jobLength = (string)this.getValue(statusArray, "length");
                        this.jobInfo.JobLength = TimeSpan.FromSeconds(this.parseJobLength(jobLength));
                        this.jobInfo.JobLengthSetTime = DateTime.Now;
                        this.device1voipaccount = (string)this.getValue(statusArray, "device1user");
                        this.device1voippassword = "password";
                        this.poxSIPRegistrarServerUri = (string)this.getValue(statusArray, "device1rcsdomain");
                        this.log.Debug("-  Started POX job " + this.jobInfo.JobId);
                        this.failAmount = 0;
                        this.poxFailure = false;
                        break;
                    }
                    catch (Exception ex)
                    {
                        if (loop == rpcRetryCount)
                        {
                            this.poxFailure = true;
                            this.checkFailCount();
                            throw new PoxConnectionException("Start POX job failed after " + loop +
                                                                " tries. Reason : " + ex.Message);
                        }
                        this.log.Debug("-  Start POX job failed in loop " + loop + ". Reason: " +
                                       ex.Message + ". Retrying... (Total amount of retries to be executed: " + rpcRetryCount + ")");
                        // In case of net timeout wait and try again.
                        Thread.Sleep(this.rpcRetryDelay);
                    }
                }
            }
        }

        private string getRobotPhoneNumber(string phoneName)
        {
            // In Marble VirtualPhone1 "self.settings.Virtual.PhoneNumber" will be handled as
            // RerefencePhone "self.settings.Reference.PhoneNumber" and vice versa for script compatibility
            foreach (PoxPhone p in this.poxPhones)
            {
                if (p.MarblePhoneName == phoneName || p.AlternativePhoneName == phoneName)
                {
                    return p.PhoneNumber;
                }
            }

            this.log.Debug("-  Getting phone number for " + phoneName + " phone dynamically from POX");

            // No robot found. Add new robot dynamically
            PoxPhone newPoxPhone = new PoxPhone();
            newPoxPhone.MarblePhoneName = phoneName;
            newPoxPhone.poxRobotIndex = this.poxPhones.Count + 1;

            object[] commandArray = new object[4];
            commandArray[0] = this.jobInfo.JobId;
            commandArray[1] = "createRobot";
            commandArray[2] = "dynamic";
            commandArray[3] = this.poxSipProxy;

            int retries = rpcRetryCount + 1;
            int loop = 0;
            while (loop++ < retries)
            {
                try
                {
                    xmlRpcProxy.insert(useraccount, "", commandArray);
                    object[] statusArray = xmlRpcProxy.status(useraccount, "", this.jobInfo.JobId);
                    object o = this.getValue(statusArray, "robot" + newPoxPhone.poxRobotIndex + "number");
                    newPoxPhone.PhoneNumber = o.ToString();

                    if (phoneName == "Virtual")
                    {
                        newPoxPhone.AlternativePhoneName = "Reference";
                        newPoxPhone.marblePhoneIndex = 1;
                    }
                    else if (phoneName == "Reference")
                    {
                        newPoxPhone.AlternativePhoneName = "Virtual";
                        newPoxPhone.marblePhoneIndex = 1;
                    }
                    else
                    {
                        newPoxPhone.marblePhoneIndex = int.Parse(phoneName.Substring(phoneName.Length - 1));
                    }

                    this.poxPhones.Add(newPoxPhone);
                    this.savePhoneNumberToMarbleSettings(phoneName, newPoxPhone.PhoneNumber);
                    this.log.Debug("-  Phone number of " + phoneName + " phone: " + newPoxPhone.PhoneNumber);
                    this.failAmount = 0;
                    return newPoxPhone.PhoneNumber;
                }
                catch (Exception ex)
                {
                    if (loop == rpcRetryCount)
                    {
                        this.poxFailure = true;
                        this.checkFailCount();
                        throw new PoxConnectionException("Create POX robot failed after " + loop +
                                                            " tries. Reason : " + ex.Message);
                    }
                    this.log.Debug("-  Create POX robot failed in loop " + loop + ". Reason: " +
                                   ex.Message + ". Retrying... (Total amount of retries to be executed: " + rpcRetryCount + ")");
                    // In case of net timeout wait and try again.
                    Thread.Sleep(this.rpcRetryDelay);
                }
            }

            if (string.IsNullOrEmpty(newPoxPhone.PhoneNumber))
                throw new PoxRobotException("Create POX robot failed. Unable to get phonenumber for POX robot: " + "robot" + newPoxPhone.poxRobotIndex);

            return null;
        }

        private void savePhoneNumberToMarbleSettings(string phoneName, string phoneNumber)
        {
            switch (phoneName)
            {
                case "Reference":
                    if (this.settings.TestRun.EnableVirtualReferencePhone)
                    {
                        this.settings.Reference.PhoneNumber = phoneNumber;
                    }
                    break;

                case "Virtual":
                    if (this.settings.TestRun.EnableVirtualReferencePhone)
                    {
                        this.settings.Reference.PhoneNumber = phoneNumber;
                    }
                    this.settings.Virtual.PhoneNumber = phoneNumber;
                    break;

                case "Virtual2":
                    this.settings.Virtual2.PhoneNumber = phoneNumber;
                    break;

                case "Virtual3":
                    this.settings.Virtual3.PhoneNumber = phoneNumber;
                    break;

                case "Virtual4":
                    this.settings.Virtual4.PhoneNumber = phoneNumber;
                    break;

                case "Virtual5":
                    this.settings.Virtual5.PhoneNumber = phoneNumber;
                    break;

                case "Virtual6":
                    this.settings.Virtual6.PhoneNumber = phoneNumber;
                    break;

                case "Virtual7":
                    this.settings.Virtual7.PhoneNumber = phoneNumber;
                    break;

                case "Virtual8":
                    this.settings.Virtual8.PhoneNumber = phoneNumber;
                    break;

                case "Virtual9":
                    this.settings.Virtual9.PhoneNumber = phoneNumber;
                    break;
            }
        }

        private string getRobotPoxName(int phoneIndex)
        {
            return (from p in this.poxPhones where p.marblePhoneIndex == phoneIndex select "robot" + p.poxRobotIndex).FirstOrDefault();
        }

        private bool isJobFinished()
        {
            // To improve performance firstcheck from local Job Info whether job should still be alive.
            // If local job count time is less than 10 minutes, check the value from POX server just to be sure. 
            TimeSpan timeElapsed = DateTime.Now - this.jobInfo.JobLengthSetTime;
            TimeSpan timeLeft = this.jobInfo.JobLength - timeElapsed;
            if (timeLeft.TotalMinutes < 10 || this.poxFailure)
            {
                int retries = rpcRetryCount + 1;
                int loop = 0;
                while (loop++ < retries)
                {
                    try
                    {
                        object[] statusArray = xmlRpcProxy.status(useraccount, "", this.jobInfo.JobId);
                        this.failAmount = 0;
                        return (bool)this.getValue(statusArray, "finished");
                    }
                    catch (Exception ex)
                    {
                        if (loop == rpcRetryCount)
                        {
                            this.poxFailure = true;
                            this.checkFailCount();
                            throw new PoxConnectionException("Check POX job " + this.jobInfo.JobId +
                                                             " status failed after " + loop + " retries." +
                                                             " Fail reason : " + ex.Message);
                        }
                        this.log.Debug("-  Check POX job " + this.jobInfo.JobId + " status failed in loop " + loop +
                                       ". Reason: " + ex.Message + " Retrying... (Total amount of retries to be executed: " + rpcRetryCount + ")");
                        // In case of net timeout wait and try again.
                        Thread.Sleep(this.rpcRetryDelay);
                    }
                }
                return true;
            }

            return false;
        }

        private bool shouldCheckJobLength()
        {
            // To improve performance firstcheck from local Job Info whether job should still be alive.
            // If local job count time is less than 60% defaultJobLength, check the value from POX server just to be sure. 
            TimeSpan timeElapsed = DateTime.Now - this.jobInfo.JobLengthSetTime;
            TimeSpan timeLeft = this.jobInfo.JobLength - timeElapsed;
            if (timeLeft.TotalSeconds < (0.6 * defaultJobLength))
            {
                return true;
            }

            return false;
        }

        private int getJobLength()
        {
            int retries = rpcRetryCount + 1;
            int loop = 0;
            while (loop++ < retries)
            {
                try
                {
                    object[] statusArray = xmlRpcProxy.status(useraccount, "", this.jobInfo.JobId);
                    string jobLength = (string)this.getValue(statusArray, "length");
                    this.failAmount = 0;
                    return this.parseJobLength(jobLength);
                }
                catch (Exception ex)
                {
                    if (loop == rpcRetryCount)
                    {
                        this.poxFailure = true;
                        this.checkFailCount();
                        throw new PoxConnectionException("Get POX job " + this.jobInfo.JobId + " length failed after " + loop +
                                                            " retries." + " Fail reason : " + ex.Message);
                    }
                    this.log.Debug("-  Get POX job " + this.jobInfo.JobId + " length failed in loop " + loop + ". Reason: " +
                                   ex.Message + " Retrying... (Total amount of retries to be executed: " + rpcRetryCount + ")");
                    // In case of net timeout wait and try again.
                    Thread.Sleep(this.rpcRetryDelay);
                }
            }

            return -1;
        }

        private int parseJobLength(string jobLength)
        {
            if (jobLength.Contains("sec"))
            {
                jobLength = jobLength.Substring(0, jobLength.Length - 3);
                return int.Parse(jobLength);
            }
            if (jobLength.Contains("min"))
            {
                jobLength = jobLength.Substring(0, jobLength.Length - 3);
                return (int.Parse(jobLength) * 60);
            }

            return -1;
        }

        private void extendJob()
        {
            // Extend the jobLength
            object[] commandArray = new object[3];
            commandArray[0] = this.jobInfo.JobId;
            commandArray[1] = "extendJob";
            commandArray[2] = defaultJobLength + "sec";

            int retries = rpcRetryCount + 1;
            int loop = 0;
            while (loop++ < retries)
            {
                try
                {
                    xmlRpcProxy.insert(useraccount, "", commandArray);
                    this.jobInfo.JobLength = TimeSpan.FromSeconds(this.getJobLength());
                    this.jobInfo.JobLengthSetTime = DateTime.Now;
                    this.failAmount = 0;
                    break;
                }
                catch (Exception ex)
                {
                    if (loop == rpcRetryCount)
                    {
                        this.poxFailure = true;
                        this.checkFailCount();
                        throw new PoxConnectionException("ExtendJob" + this.jobInfo.JobId + " failed after " + loop +
                                                            " retries. Reason : " + ex.Message);
                    }
                    this.log.Debug("ExtendJob" + this.jobInfo.JobId + " failed in loop " + loop + ". Reason: " +
                                   ex.Message + ". Retrying... (Total amount of retries to be executed: " + rpcRetryCount + ")");
                    // In case of net timeout wait and try again.
                    Thread.Sleep(this.rpcRetryDelay);
                }
            }
        }

        private void waitForStateChange(string dynamicCommand, string expectedState, string robot)
        {
            string poxState = string.Empty;
            // Wait for state change
            int loop = 0;
            const int waitForChangingStatus = 25;
            while (loop++ < waitForChangingStatus)
            {
                poxState = string.Empty;
                try
                {
                    poxState = this.checkRobotStatus(robot, expectedState);
                    if (poxState != expectedState)
                    {
                        Thread.Sleep(1000);
                        continue;
                    }
                    return;
                }
                catch (Exception ex)
                {
                    this.log.Debug("-  POX: Wait for " + expectedState + " failed in " + dynamicCommand + " method", ex);
                    // In case of net timeout wait and try again.
                    Thread.Sleep(1000);
                }
            }

            this.poxFailure = true;
            throw new PoxRobotException(dynamicCommand + " on POX robot " + robot + " failed due to POX robot did not enter '" + expectedState + "' state within " + waitForChangingStatus + " seconds. State reported by POX: '" + poxState + "'" );
        }

        private void executeDynamicPoxCommand(string dynamicCommand, string robot, object[] commandArray)
        {
            int retries = rpcRetryCount + 1;
            int loop = 0;
            while (loop++ < retries)
            {
                try
                {
                    xmlRpcProxy.insert(useraccount, "", commandArray);
                    this.failAmount = 0;
                    break;
                }
                catch (Exception ex)
                {
                    if (loop == rpcRetryCount)
                    {
                        this.poxFailure = true;
                        this.checkFailCount();
                        throw new PoxConnectionException(dynamicCommand + " on POX robot " + robot + " failed after " + loop +
                                                            " tries. Reason : " + ex.Message);
                    }
                    this.log.Debug(dynamicCommand + " on POX robot " + robot + " failed in loop " + loop + ". Reason: " +
                                   ex.Message + ". Retrying... (Total amount of retries to be executed: " + rpcRetryCount + ")");
                    // In case of net timeout wait and try again.
                    Thread.Sleep(this.rpcRetryDelay);
                }
            }
        }

        private string checkRobotStatus(string robot, string statusExpected)
        {
            string status = string.Empty;
            int retries = rpcRetryCount + 1;
            int loop = 0;
            while (loop++ < retries)
            {
                status = string.Empty;
                try
                {
                    object[] statusArray = xmlRpcProxy.status(useraccount, "", this.jobInfo.JobId);
                    status = (string)this.getValue(statusArray, robot + "status");
                    this.failAmount = 0;
                    break;
                }
                catch (Exception ex)
                {
                    if (loop == rpcRetryCount)
                    {
                        this.poxFailure = true;
                        this.checkFailCount();
                        throw new PoxConnectionException("Check POX robot status failed after " + loop +
                                                            " tries. Robot checked: " + robot + ". Status expected: " + statusExpected +
                                                            ". Fail reason : " + ex.Message);
                    }
                    this.log.Debug("-  Check POX robot status failed in loop " + loop + ". Reason: " +
                                   ex.Message + ". Retrying... (Total amount of retries to be executed: " + rpcRetryCount + ")");
                    // In case of net timeout wait and try again.
                    Thread.Sleep(this.rpcRetryDelay);
                }
            }

            return status;
        }

        /// <summary>
        /// Handler for Marble setting query. E.g self.settings.Reference.PhoneNumber.
        /// </summary>
        /// <param name="args"></param>
        private void settingPropertyQueryHandler(SettingPropertyQueryEventArgs args)
        {
            if ((args.SettingModuleName.StartsWith("Virtual") || args.SettingModuleName == "Reference") && args.SettingName == "PhoneNumber")
            {
                if (args.SettingModuleName == "Reference" && args.SettingName == "PhoneNumber" && !this.settings.TestRun.EnableVirtualReferencePhone)
                    return;

                startOrCheckPoxJob();
                string robotNumber = this.getRobotPhoneNumber(args.SettingModuleName);
                if ((string)args.OldValue != robotNumber)
                {
                    args.NewValue = robotNumber;
                }
            }
            else if (args.SettingModuleName == "Main" && (args.SettingName == "VoIPAccount" || args.SettingName == "VoIPPassword"))
            {
                startOrCheckPoxJob();
                if (args.SettingName == "VoIPAccount")
                {
                    if ((string)args.OldValue != this.device1voipaccount)
                    {
                        args.NewValue = this.device1voipaccount;
                    }
                }
                else if (args.SettingName == "VoIPPassword")
                {
                    if ((string)args.OldValue != this.device1voippassword)
                    {
                        args.NewValue = this.device1voippassword;
                    }
                }
            }
            else if (args.SettingModuleName == "TestRun" && args.SettingName == "POXSIPRegistrarServerUri")
            {
                startOrCheckPoxJob();
                if ((string)args.OldValue != this.poxSIPRegistrarServerUri)
                {
                    args.NewValue = this.poxSIPRegistrarServerUri;
                }
            }            
        }
       
        private void startOrCheckPoxJob()
        {
            try
            {
                this.connectPox(this.poxUri);
            }
            catch (Exception ex)
            {
                this.log.Error(ex.Message);
            }

            // Check that POX job is created and not yet finished
            if (this.jobInfo.JobId == -1 || this.isJobFinished())
            {
                try
                {
                    this.startPoxJob();
                }
                catch (Exception ex)
                {
                    this.log.Error(ex.Message);
                }
            }
            else
            {
                // There is a job running. Check joblength
                if (this.shouldCheckJobLength())
                {
                    int jobLength = this.getJobLength();
                    if (jobLength < defaultJobLength)
                    {
                        this.extendJob();
                    }
                }
            }
        }

        private object getValue(IEnumerable<object> array, object value)
        {
            return array.OfType<XmlRpcStruct>().Select(o => this.handleResponse(o, value)).FirstOrDefault();
        }

        private object handleResponse(XmlRpcStruct response, object value)
        {
            if (response.ContainsKey(value))
            {
                return response[value];
            }

            foreach (object o in response.Values)
            {
                if (o is XmlRpcStruct)
                {
                    XmlRpcStruct r = o as XmlRpcStruct;
                    if (r.ContainsKey(value))
                    {
                        return r[value];
                    }
                    object val = this.handleResponse(r, value);
                    if (val != null)
                    {
                        return val;
                    }
                }
            }

            return null;
        }

        private void checkFailCount()
        {
            this.failAmount++;
            if (this.failAmount >= this.poxFailAmountMax)
            {
                this.settings.TestRun.BackendAvailable = false;
            }
        }

        #endregion

        # region Destructor
        
        ~XmlRpcClient()
        {
            this.Close();
        }

        #endregion
    }
}