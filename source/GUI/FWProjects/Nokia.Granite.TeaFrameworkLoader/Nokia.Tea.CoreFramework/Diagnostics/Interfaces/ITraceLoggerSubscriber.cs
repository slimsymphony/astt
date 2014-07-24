using System.Collections.Generic;
using Nokia.Tea.CoreFramework.Diagnostics.Implementations;

namespace Nokia.Tea.CoreFramework.Diagnostics.Interfaces
{ 
    public interface ITraceLoggerSubscriber
    {
        void AddMessage(LogMessage message);
        void StopMessageWriting();

        List<ISourceFilter> SourceFilters { get; set; }

        ITraceLoggerBase TraceLogger { get; set; }
    }
}

