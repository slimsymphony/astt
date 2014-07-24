using System.Collections.Generic;

namespace Nokia.Tea.CoreFramework.Diagnostics.Interfaces
{
    public interface ITraceLoggerServiceClient
    {
        void Trace(TraceMessageType traceMessageType);
        void Trace(TraceMessageType traceMessageType, string traceMessage);
        void Trace(TraceMessageType traceMessageType, params object[] traceParameters);
        void Trace(TraceMessageType traceMessageType, string traceMessage, params object[] traceParameters);
        void TraceError(string traceMessage);
        void TraceError(string traceMessage, params object[] traceParameters);
        void TraceInformation(string traceMessage);
        void TraceInformation(string traceMessage, params object[] traceParameters);
        void TraceMethodExit();
        void TraceMethodExit(params object[] traceParameters);
        void TraceMethodExit(string traceMessage);
        void TraceMethodExit(string traceMessage, params object[] traceParameters);
        void TraceMethodStart();
        void TraceMethodStart(string traceMessage);
        void TraceMethodStart(params object[] traceParameters);
        void TraceMethodStart(string traceMessage, params object[] traceParameters);
        void TracePrintToUi(string traceMessage);
        void TracePrintToUi(string traceMessage, params object[] traceParameters);
        void TraceStepResult(string traceMessage);
        void TraceStepResult(string traceMessage, params object[] traceParameters);
        void TraceWarning(string traceMessage);
        void TraceWarning(string traceMessage, params object[] traceParameters);

        bool IgnoreMethodStructure { get; set; }

        List<TraceMessageType> IgnoreTraceMessageTypes { get; set; }
    }
}

