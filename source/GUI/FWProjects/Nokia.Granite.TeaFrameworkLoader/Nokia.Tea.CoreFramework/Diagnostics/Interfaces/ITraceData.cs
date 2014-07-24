using System;

namespace Nokia.Tea.CoreFramework.Diagnostics.Interfaces
{
    public interface ITraceData
    {
        string MethodStructure { get; }

        object SenderData { get; }

        DateTime TraceDateTime { get; }

        string TraceMessage { get; }

        object[] TraceParameters { get; }
    }
}

