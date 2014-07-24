namespace Nokia.Tea.CoreFramework.Diagnostics.Interfaces
{
    public interface ITraceLogger : ITraceLoggerBase
    {
        void Log(string traceMessage);
    }
}

