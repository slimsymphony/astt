namespace Nokia.Tea.CoreFramework.Diagnostics.Interfaces
{
    public interface ITraceLoggerService
    {
        void Log(string traceSource, TraceMessageType messageType, ITraceData traceData);
    }
}