using System.Collections.Generic;
using System.Threading;
using Nokia.Tea.CoreFramework.BaseModules.TeaCoreModule;
using Nokia.Tea.CoreFramework.Diagnostics.Interfaces;

namespace Nokia.Tea.CoreFramework.Diagnostics.Implementations
{
    /// <summary>
    /// Trace Logger Service Client implementation.
    /// This class offers a convenient way to write the trace log messages
    /// to Trace Logger Service Interface.
    /// </summary>
    public class TraceLoggerServiceClient : ITraceLoggerServiceClient
    {
        #region Private Members

        /// <summary>
        /// Stores the trace source name.
        /// The trace source name is a combination of
        /// calling class namespace and calling class name.
        /// This member can be read only since it's
        /// value can only be set in constructor.
        /// </summary>
        private readonly string traceSource;

        /// <summary>
        /// The ITraceLoggerService object.
        /// This member can be read only since it's
        /// value can only be set in constructor.
        /// </summary>
        private readonly ITraceLoggerService traceLoggerService;

        private object senderObject;

        #endregion

        #region Constructors

        /// <summary>
        /// Initializes a new instance of the <see cref="TraceLoggerServiceClient"/> class.
        /// </summary>
        /// <param name="traceLoggerService">
        /// The trace Logger object.
        /// </param>
        /// <param name="sender">
        /// The class that initialized the TeaTracePublisher.
        /// </param>
        public TraceLoggerServiceClient(ITraceLoggerService traceLoggerService, object sender)
        {
            TeaGlobalization teaGlobalization = new TeaGlobalization();
            this.senderObject = sender;
            Thread.CurrentThread.CurrentCulture = teaGlobalization.TeaCultureInfo;
            this.traceLoggerService = traceLoggerService;
            this.traceSource = sender.GetType().FullName;
            this.IgnoreMethodStructure = false;
            this.IgnoreTraceMessageTypes = new List<TraceMessageType>();
        }

        #endregion

        #region Accessors

        /// <summary>
        /// Gets or sets a value indicating whether method structure
        /// should be automatically generated using reflection.
        /// Set to true to ignore the method structure
        /// from being automatically generated using reflection.
        /// NOTE: If this flag is set to true, TraceData.MethodStructure field will not be automatically filled.
        /// This flag is meant to be used only when maximum performance must be achieved.
        /// In any normal situation the value of this flag should be false.
        /// </summary>
        public bool IgnoreMethodStructure { get; set; }

        /// <summary>
        /// Gets or sets a list of TraceMessageTypes that will be ignored from trace:
        /// E.g. By adding TraceMessageType.Information and TraceMessageType.Warning
        /// to the ignore list will prevent any trace message that are of type 
        /// TraceMessageType.Information or TraceMessageType.Warning to be passed to TraceLoggerService.
        /// The default behaviour is to trace all message types (empty list).
        /// </summary>
        public List<TraceMessageType> IgnoreTraceMessageTypes { get; set; }

        #endregion

        #region Public methods

        /// <summary>
        /// Creates a trace message of given type with no additional message and parameters.
        /// NOTE: If the given type is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessageType">
        /// The trace Message Type.
        /// </param>
        public void Trace(TraceMessageType traceMessageType)
        {
            this.prepareTraceMessage(traceMessageType, null, null);
        }

        /// <summary>
        /// Creates a trace message of given type with custom trace message.
        /// NOTE: If the given type is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessageType">
        /// The trace Message Type.
        /// </param>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        public void Trace(TraceMessageType traceMessageType, string traceMessage)
        {
            this.prepareTraceMessage(traceMessageType, traceMessage, null);
        }

        /// <summary>
        /// Creates a trace message of given type with custom trace message and parameters.
        /// NOTE: If the given type is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessageType">
        /// The trace Message Type.
        /// </param>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        public void Trace(TraceMessageType traceMessageType, string traceMessage, params object[] traceParameters)
        {
            this.prepareTraceMessage(traceMessageType, traceMessage, traceParameters);
        }

        /// <summary>
        /// Creates a trace message of given type with custom trace parameters.
        /// NOTE: If the given type is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessageType">
        /// The trace Message Type.
        /// </param>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        public void Trace(TraceMessageType traceMessageType, params object[] traceParameters)
        {
            this.prepareTraceMessage(traceMessageType, null, traceParameters);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.Errorwith custom trace message and parameters.
        /// NOTE: If TraceMessageType.Error is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        public void TraceError(string traceMessage)
        {
            this.prepareTraceMessage(TraceMessageType.Error, traceMessage, null);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.Error with custom trace parameters.
        /// NOTE: If TraceMessageType.Error is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        public void TraceError(string traceMessage, params object[] traceParameters)
        {
            this.prepareTraceMessage(TraceMessageType.Error, traceMessage, traceParameters);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.Warning with custom trace message.
        /// NOTE: If TraceMessageType.Warning is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        public void TraceWarning(string traceMessage)
        {
            this.prepareTraceMessage(TraceMessageType.Warning, traceMessage, null);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.Warning with custom trace message and parameters.
        /// NOTE: If TraceMessageType.Warning is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        public void TraceWarning(string traceMessage, params object[] traceParameters)
        {
            this.prepareTraceMessage(TraceMessageType.Warning, traceMessage, traceParameters);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.Information with custom trace message.
        /// NOTE: If TraceMessageType.Information is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        public void TraceInformation(string traceMessage)
        {
            this.prepareTraceMessage(TraceMessageType.Information, traceMessage, null);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.Information with custom trace message and parameters.
        /// NOTE: If TraceMessageType.Information is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        public void TraceInformation(string traceMessage, params object[] traceParameters)
        {
            this.prepareTraceMessage(TraceMessageType.Information, traceMessage, traceParameters);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.StepResult with custom trace message.
        /// NOTE: If TraceMessageType.StepResult is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        public void TraceStepResult(string traceMessage)
        {
            this.prepareTraceMessage(TraceMessageType.StepResult, traceMessage, null);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.StepResult with custom trace message and parameters.
        /// NOTE: If TraceMessageType.StepResult is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        public void TraceStepResult(string traceMessage, params object[] traceParameters)
        {
            this.prepareTraceMessage(TraceMessageType.StepResult, traceMessage, traceParameters);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.PrintToUI with custom trace message.
        /// NOTE: If TraceMessageType.PrintToUI is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        public void TracePrintToUi(string traceMessage)
        {
            this.prepareTraceMessage(TraceMessageType.PrintToUi, traceMessage, null);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.PrintToUI with custom trace message and parameters.
        /// NOTE: If TraceMessageType.PrintToUI is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        public void TracePrintToUi(string traceMessage, params object[] traceParameters)
        {
            this.prepareTraceMessage(TraceMessageType.PrintToUi, traceMessage, traceParameters);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.MethodStart with no message and parameters.
        /// NOTE: If TraceMessageType.MethodStart is in the list of ignored messages, no trace message will be sent.
        /// </summary>
        public void TraceMethodStart()
        {
            this.prepareTraceMessage(TraceMessageType.MethodStart, null, null);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.MethodStart with custom trace message.
        /// NOTE: If TraceMessageType.MethodStart is in the list of ignored messages, no trace message will be sent
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        public void TraceMethodStart(string traceMessage)
        {
            this.prepareTraceMessage(TraceMessageType.MethodStart, traceMessage, null);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.MethodStart with custom trace message and parameters.
        /// NOTE: If TraceMessageType.MethodStart is in the list of ignored messages, no trace message will be sent
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        public void TraceMethodStart(string traceMessage, params object[] traceParameters)
        {
            this.prepareTraceMessage(TraceMessageType.MethodStart, traceMessage, traceParameters);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.MethodStart with custom trace parameters.
        /// NOTE: If TraceMessageType.MethodStart is in the list of ignored messages, no trace message will be sent
        /// </summary>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        public void TraceMethodStart(params object[] traceParameters)
        {
            this.prepareTraceMessage(TraceMessageType.MethodStart, null, traceParameters);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.MethodExit with no message and parameters.
        /// NOTE: If TraceMessageType.MethodExit is in the list of ignored messages, no trace message will be sent
        /// </summary>
        public void TraceMethodExit()
        {
            this.prepareTraceMessage(TraceMessageType.MethodExit, null, null);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.MethodExit with custom trace message.
        /// NOTE: If TraceMessageType.MethodExit is in the list of ignored messages, no trace message will be sent
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        public void TraceMethodExit(string traceMessage)
        {
            this.prepareTraceMessage(TraceMessageType.MethodExit, traceMessage, null);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.MethodExit with custom trace message and parameters.
        /// NOTE: If TraceMessageType.MethodExit is in the list of ignored messages, no trace message will be sent
        /// </summary>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        public void TraceMethodExit(string traceMessage, params object[] traceParameters)
        {
            this.prepareTraceMessage(TraceMessageType.MethodExit, traceMessage, traceParameters);
        }

        /// <summary>
        /// Creates a trace message of type TraceMessageType.MethodExit with custom trace parameters.
        /// NOTE: If TraceMessageType.MethodExit is in the list of ignored messages, no trace message will be sent
        /// </summary>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        public void TraceMethodExit(params object[] traceParameters)
        {
            this.prepareTraceMessage(TraceMessageType.MethodExit, null, traceParameters);
        }

        #endregion

        #region Private methods

        /// <summary>
        /// A private class that check whether this type of message should be sent to
        /// Trace Logger Service and does the needed preparations to the message.
        /// </summary>
        /// <param name="traceMessageType">
        /// The trace message type.
        /// </param>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        private void prepareTraceMessage(TraceMessageType traceMessageType, string traceMessage, object[] traceParameters)
        {
            // TODO: Commented out due to in Marble there is no need for Tea TraceLogger
            //if (this.checkSourceFilter(traceMessageType))
            //{
            //    if (traceMessageType == TraceMessageType.PrintToUi)
            //    {
            //        StackFrame[] list = new StackTrace().GetFrames();
            //    }

            //    ITraceData traceData = this.fillTraceData(traceMessage, traceParameters);
            //    this.traceSend(traceMessageType, traceData);
            //}
        }



        ///// <summary>
        ///// Fills the TraceData object with the given parameters
        ///// and method structure digged from StackTrace.
        ///// NOTE: If IgnoreMethodStructure is set to true, MethodStructure field will not be filled.
        ///// </summary>
        ///// <param name="traceMessage">
        ///// The trace message.
        ///// </param>
        ///// <param name="traceParameters">
        ///// The trace parameters.
        ///// </param>
        ///// <returns>
        ///// The readymade TraceData object.
        ///// </returns>
        //private ITraceData fillTraceData(string traceMessage, object[] traceParameters)
        //{
        //    if (this.IgnoreMethodStructure)
        //    {
        //        return new TraceData(this.senderObject, string.Empty, traceMessage, DateTime.Now, traceParameters);
        //    }

        //    // No message given.
        //    if (traceMessage == null)
        //    {
        //        traceMessage = string.Empty;
        //    }

        //    // No trace parameters given.
        //    if (traceParameters == null)
        //    {
        //        traceParameters = new object[0];
        //    }

        //    MethodBase methodBase = new StackTrace().GetFrame(3).GetMethod();

        //    string tt = methodBase.ReflectedType.ToString();
        //    string nn = methodBase.Name;
        //    string methodStructure = methodBase.ToString();
        //    methodStructure = methodStructure.Remove(methodStructure.IndexOf('(') + 1);

        //    ParameterInfo[] parameterInfos = methodBase.GetParameters();
        //    foreach (ParameterInfo info in parameterInfos)
        //    {
        //        methodStructure += info.ToString() + ", ";
        //    }

        //    if (methodStructure.EndsWith(", "))
        //    {
        //        methodStructure = methodStructure.Remove(methodStructure.LastIndexOf(','));
        //    }

        //    methodStructure += ")";

        //    return new TraceData(this.senderObject, methodStructure, traceMessage, DateTime.Now, traceParameters);
        //}

        ///// <summary>
        ///// Check whether the source filter is set to ignore
        ///// the messages of type <see cref="TraceMessageType"/> to be traced.
        ///// </summary>
        ///// <param name="messageType">
        ///// The message type.
        ///// </param>
        ///// <returns>
        ///// True if the given type will be traced.
        ///// False if the given type will be ignored.
        ///// </returns>
        //private bool checkSourceFilter(TraceMessageType messageType)
        //{
        //    foreach (TraceMessageType ignoredType in this.IgnoreTraceMessageTypes)
        //    {
        //        if (messageType == ignoredType)
        //        {
        //            return false;
        //        }
        //    }

        //    return true;
        //}

        ///// <summary>
        ///// Send the message to the TraceLoggerService.
        ///// </summary>
        ///// <param name="messageType">
        ///// The message type.
        ///// </param>
        ///// <param name="data">
        ///// The data.
        ///// </param>
        //private void traceSend(TraceMessageType messageType, ITraceData data)
        //{
        //    if (this.traceLoggerService != null)
        //    {
        //        this.traceLoggerService.Log(this.traceSource, messageType, data);
        //    }
        //}

        #endregion
    }
}

