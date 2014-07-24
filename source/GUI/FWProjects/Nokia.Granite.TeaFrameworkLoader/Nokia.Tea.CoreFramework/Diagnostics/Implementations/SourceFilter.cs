using System.Collections.Generic;
using Nokia.Tea.CoreFramework.Diagnostics.Interfaces;

namespace Nokia.Tea.CoreFramework.Diagnostics.Implementations
{
    /// <summary>
    /// Defines the source filter class.
    /// </summary>
    public class SourceFilter : ISourceFilter
    {
        #region Constructors

        /// <summary>
        /// Initializes a new instance of the <see cref="SourceFilter"/> class.
        /// NOTE: This constructor creates an empty list of SourceFilters
        /// and an empty list of TraceMessageTypes that the filtering is targeted at.
        /// Nothin will be passed through the filter until the SourceFilters and TraceMessageTypes
        /// lists are filled with the needed data.
        /// </summary>
        public SourceFilter() : this(new List<string>(), new List<TraceMessageType>())
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SourceFilter"/> class.
        /// This constructor uses the given TraceMessageTypes list and enables
        /// tracing for given types(positive filtering).
        /// Set the InverseFiltering flag to true to enable tracing all trace message types
        /// except the types in the TraceMessageTypes list(negative filtering).
        /// </summary>
        /// <param name="traceSources">
        /// The trace sources the filtering is targeted at.
        /// The TraceSource may be a full module (namespace+class) name
        /// E.g. 'Nokia.Tea.CommonFramework.Drivers.DriverDcPowerSupplyAgilent663Xxx'
        /// or just a part of the module name E.g. 'Steps'.
        /// </param>
        /// <param name="traceMessageTypes">
        /// The trace message types the filtering is targeted at.
        /// </param>
        public SourceFilter(List<string> traceSources, List<TraceMessageType> traceMessageTypes)
        {
            this.InverseFiltering = false;
            this.TraceSources = traceSources;
            this.TraceMessageTypes = traceMessageTypes;
            this.LogTraceMessageType = true;
            this.LogTraceSource = true;
            this.LogTraceMessage = true;
            this.LogMethodStructure = true;
            this.LogTraceParameters = true;
        }

        #endregion

        #region ISourceFilter Members

        /// <summary>
        /// Gets or sets a list of SourceFilters the filtering is targeted at, and that
        /// shares the same filtering options.
        /// The TraceSource may be a full module (namespace+class) name
        /// E.g. 'Nokia.Tea.CommonFramework.Drivers.DriverDcPowerSupplyAgilent663Xxx'
        /// or just a part of the module name E.g. 'Steps'.
        /// </summary>
        public List<string> TraceSources { get; set; }

        /// <summary>
        /// Gets or sets a list of TraceMessageTypes that the 
        /// filtration action(s) is targeted at.
        /// </summary>
        public List<TraceMessageType> TraceMessageTypes { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether InverseFiltering is used.
        /// The InverseFiltering flag affects the way the actual filtering is handled.
        /// If the InverseFiltering flag is set to false(default condition), only message
        /// types defined in TraceMessageTypes list are passed to subscriber.
        /// If the InverseFiltering flag is set to true, all message types expect the types
        /// defined in TraceMessageTypes list are passed to subscriber.
        /// </summary>
        public bool InverseFiltering { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether the actual log message will include
        /// Date and Time information.
        /// Set to true/false to enable or disable the logging of
        /// trace date and time from TraceSource.
        /// </summary>
        public bool LogTraceDateTime { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether the actual log message will include
        /// the message type information.
        /// Set to true/false to enable or disable the logging of
        /// trace message type from TraceSource.
        /// </summary>
        public bool LogTraceMessageType { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether the actual log message will include
        /// the trace source information.
        /// Set to true/false to enable or disable the logging of
        /// trace source information from TraceSource.
        /// </summary>
        public bool LogTraceSource { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether the actual log message will include
        /// the actual trace message.
        /// Set to true/false to enable or disable the logging of
        /// actual trace message from TraceSource.
        /// </summary>
        public bool LogTraceMessage { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether the actual log message will include
        /// the method structure information.
        /// Set to true/false to enable or disable the logging of
        /// method structure from TraceSource.
        /// </summary>
        public bool LogMethodStructure { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether the actual log message will include
        /// the trace parameters information.
        /// Set to true/false to enable or disable the logging of
        /// trace parameters from TraceSource.
        /// </summary>
        public bool LogTraceParameters { get; set; }

        #endregion
    }
}

