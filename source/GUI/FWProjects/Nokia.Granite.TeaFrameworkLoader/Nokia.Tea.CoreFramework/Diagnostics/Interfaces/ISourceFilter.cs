using System.Collections.Generic;

namespace Nokia.Tea.CoreFramework.Diagnostics.Interfaces
{
    public interface ISourceFilter
    {
        bool InverseFiltering { get; set; }

        bool LogMethodStructure { get; set; }

        bool LogTraceDateTime { get; set; }

        bool LogTraceMessage { get; set; }

        bool LogTraceMessageType { get; set; }

        bool LogTraceParameters { get; set; }

        bool LogTraceSource { get; set; }

        List<TraceMessageType> TraceMessageTypes { get; set; }

        List<string> TraceSources { get; set; }
    }
}

