using Nokia.Tea.CoreFramework.Diagnostics.Interfaces;

namespace Nokia.Tea.CoreFramework.Diagnostics.Implementations
{
    /// <summary>
    /// This class covers a log message that is stored to message queue.
    /// Class is internal because it does not need to be seen outside TraceLoggerService.
    /// </summary>
    public class LogMessage
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="LogMessage"/> class.
        /// </summary>
        /// <param name="traceSource">
        /// The trace source.
        /// </param>
        /// <param name="messageType">
        /// The message type.
        /// </param>
        /// <param name="traceData">
        /// The trace data.
        /// </param>
        public LogMessage(string traceSource, TraceMessageType messageType, ITraceData traceData)
        {
            this.TraceSource = traceSource;
            this.MessageType = messageType;
            this.TraceData = traceData;
        }

        /// <summary>
        /// Gets TraceSource.
        /// </summary>
        public string TraceSource { get; private set; }

        /// <summary>
        /// Gets MessageType.
        /// </summary>
        public TraceMessageType MessageType { get; private set; }

        /// <summary>
        /// Gets TraceData.
        /// </summary>
        public ITraceData TraceData { get; private set; }
    }
}

