using System;
using Nokia.Tea.CoreFramework.Diagnostics.Interfaces;

namespace Nokia.Tea.CoreFramework.Diagnostics.Implementations
{
    /// <summary>
    /// Defines the default class that is used to store
    /// the trace data.
    /// The TraceData class object is typically used as a parameter
    /// that is passed along with the trace message to be consumed by
    /// the trace loggers (subscribers).
    /// </summary>
    public class TraceData : ITraceData
    {
        #region Constructors

        /// <summary>
        /// Initializes a new instance of the <see cref="TraceData"/> class.
        /// </summary>
        /// <param name="senderData">Sender data object.</param>
        /// <param name="methodStructure">
        /// The method Structure.
        /// </param>
        /// <param name="traceMessage">
        /// The trace message.
        /// </param>
        /// <param name="tracedateTime">
        /// The date and time the trace occurred.
        /// </param>
        /// <param name="traceParameters">
        /// The trace parameters.
        /// </param>
        public TraceData(object senderData, string methodStructure, string traceMessage, DateTime tracedateTime, params object[] traceParameters)
        {
            this.MethodStructure = methodStructure;
            this.TraceMessage = traceMessage;
            this.TraceDateTime = tracedateTime;
            this.SenderData = senderData;

            if (traceParameters != null)
            {
                this.TraceParameters = traceParameters;
            }
            else
            {
                this.TraceParameters = new object[0];
            }
        }

        /// <summary>
        /// Parameterless constructor use only with WCF.
        /// </summary>
        public TraceData()
        {
        }

        #endregion

        #region ITraceData members

        /// <summary>
        /// Gets the MethodStructure.
        /// The MethodStructure stores the information about the method
        /// that the trace is called from.
        /// E.g "int MyMethod(int valueInt, bool myBoolean, string myString)"
        /// </summary>
        public string MethodStructure { get; private set; }

        /// <summary>
        /// Gets the TraceMessage.
        /// The TraceMessage is the actual
        /// message output to the trace.
        /// </summary>
        public string TraceMessage { get; private set; }

        /// <summary>
        /// Gets the TraceDateTime.
        /// This is the Date and Time the trace occurred.
        /// </summary>
        public DateTime TraceDateTime { get; private set; }

        /// <summary>
        /// Gets TraceParameters. 
        /// E.g. The method parameters or other parameters
        /// written to trace by the module developer.
        /// </summary>
        public object[] TraceParameters { get; private set; }

        /// <summary>
        /// Gets sender data if available otherwise null.
        /// </summary>
        public object SenderData { get; private set; }

        #endregion
    }
}

