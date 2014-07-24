using System.Collections.Generic;

namespace Nokia.Tea.CoreFramework.Diagnostics.Interfaces
{
    public interface ITraceLoggerServiceSubscribe
    {
        void SubscribeLogger(ITraceLoggerSubscriber observer);
        void UnSubscribeLogger(ITraceLoggerSubscriber observer);

        List<ITraceLoggerSubscriber> SubscribedLoggers { get; }
    }
}

