using Managed.Adb.Logs;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProtoBuf;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Handler delegate for log data
    /// </summary>
    /// <param name="data">Log data</param>
    public delegate void LogDataReceivedHandler(ILogData data);

    /// <summary>
    /// Source buffer for the log messages
    /// </summary>
    [Flags]
    [ProtoContract]
    public enum LogBuffer
    {
        /// <summary>
        /// Main buffer (default)
        /// </summary>
        Main = 0x01,
        
        /// <summary>
        /// Radio/telephony related messages
        /// </summary>
        Radio = 0x02,
        
        /// <summary>
        /// Events-related messages
        /// </summary>
        Events = 0x04,
        
        /// <summary>
        /// System buffer
        /// </summary>
        System = 0x08,

        /// <summary>
        /// Dmesg buffer
        /// </summary>
        Kernel = 0x10,

        /// <summary>
        /// All suported buffers
        /// </summary>
        All = 0x20
    }

    /// <summary>
    /// 
    /// </summary>
    public enum LogTimestampMode
    {
        /// <summary>
        /// 
        /// </summary>
        Remote,
        
        /// <summary>
        /// 
        /// </summary>
        Local
    }

    /// <summary>
    /// Log message priority
    /// </summary>
    public enum LogPriority : int
    {
        /// <summary>
        /// Unknown priority
        /// </summary>
        Unknown = 0,
        
        /// <summary>
        /// 
        /// </summary>
        Default = 1,
        
        /// <summary>
        /// Verbose (lowest priority)
        /// </summary>
        Verbose = 2,
        
        /// <summary>
        /// Debug (2nd lowest priority)
        /// </summary>
        Debug = 3,
        
        /// <summary>
        /// Info (3rd lowest priority)
        /// </summary>
        Info = 4,
        
        /// <summary>
        /// Warning (4th lowest priority)
        /// </summary>
        Warning = 5,
        
        /// <summary>
        /// Error (5th lowest priority)
        /// </summary>
        Error = 6,
        
        /// <summary>
        /// Fatal (6th lowest priority)
        /// </summary>
        Fatal = 7,
        
        /// <summary>
        ///  Silent (highest priority, on which nothing is ever printed)
        /// </summary>
        Silent = 8
    }

    /// <summary>
    /// Dmesg/kernel message priority
    /// </summary>
    public enum DmesgLogPriority
    {
        /// <summary>
        /// Unknown
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// Emergency
        /// </summary>
        Emergency = 0,

        /// <summary>
        /// Alert
        /// </summary>
        Alert = 1,

        /// <summary>
        /// Critical
        /// </summary>
        Critical = 2,

        /// <summary>
        /// Error
        /// </summary>
        Error = 3,

        /// <summary>
        /// Warning
        /// </summary>
        Warning = 4,

        /// <summary>
        /// Notice
        /// </summary>
        Notice = 5,

        /// <summary>
        /// Info
        /// </summary>
        Info = 6,

        /// <summary>
        /// Debug
        /// </summary>
        Debug = 7
    }

    /// <summary>
    /// Output format for printing the log messages
    /// </summary>
    public enum OutputFormat
    {
        /// <summary>
        /// Display priority/tag and PID of the process issuing the message (the default format)
        /// </summary>
        Brief,
        
        /// <summary>
        /// Display PID only.
        /// </summary>
        Process,
        
        /// <summary>
        /// Display the priority/tag only
        /// </summary>
        Tag,
        
        /// <summary>
        ///  Display the raw log message, with no other metadata fields
        /// </summary>
        Raw,
        
        /// <summary>
        /// Display the date, invocation time, priority/tag, and PID of the process issuing the message
        /// </summary>
        Time,
        
        /// <summary>
        /// Display the date, invocation time, priority, tag, and the PID and TID of the thread issuing the message
        /// </summary>
        ThreadTime,
        
        /// <summary>
        /// Display all metadata fields and separate messages with blank lines
        /// </summary>
        Long,

        /// <summary>
        /// Mimic logcat - all on one line
        /// </summary>
        ADBMimic
    }

    /// <summary>
    /// 
    /// </summary>
    public interface ILogData
    {
        /// <summary>
        /// 
        /// </summary>
        LogBuffer SourceBuffer { get; }

        /// <summary>
        /// 
        /// </summary>
        string Tag { get; }

        /// <summary>
        /// 
        /// </summary>
        string Data { get; }

        /// <summary>
        /// 
        /// </summary>
        DateTime RemoteTimestamp { get; }

        /// <summary>
        /// 
        /// </summary>
        DateTime LocalTimestamp { get; }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="format"></param>
        /// <returns></returns>
        string ToString(OutputFormat format, LogTimestampMode timestampMode);
    }

    /// <summary>
    /// 
    /// </summary>
    public interface IListener
    {
        /// <summary>
        /// 
        /// </summary>
        event LogDataReceivedHandler LogDataReceived;

        /// <summary>
        /// 
        /// </summary>
        LogBuffer SourceBuffer { get; }

        /// <summary>
        /// 
        /// </summary>
        void ClearLogBuffer();

        /// <summary>
        /// 
        /// </summary>
        void Start(bool clearBuffer = true);

        /// <summary>
        /// 
        /// </summary>
        void Stop(bool clearBuffer = false);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="cache"></param>
        void SetCache(LogEntryCache cache);
    }

    /// <summary>
    /// 
    /// </summary>
    [Serializable]
    public class LogData: ILogData
    {
        private DateTime m_epoc = new DateTime(1970, 1, 1, 0, 0, 0);

        /// <summary>
        /// Gets the source buffer of the log message
        /// </summary>
        public LogBuffer SourceBuffer { get; internal set; }

        /// <summary>
        /// Gets the priority of the message
        /// </summary>
        public LogPriority Priority { get; internal set; }

        /// <summary>
        /// Gets the process ID of the process issuing the log message
        /// </summary>
        public int ProcessId { get; internal set; }
        
        /// <summary>
        /// Gets the thread ID of the thread issuing the log message
        /// </summary>
        public int ThreadId { get; internal set; }

        /// <summary>
        /// Gets the textual identifier of the instance issuing the log message
        /// </summary>
        public string Tag { get; internal set; }

        /// <summary>
        /// Gets the data in the log message, i.e. the message itself in readable format
        /// </summary>
        public string Data { get; internal set; }

        /// <summary>
        /// Gets the log message timestamp: seconds after epoc
        /// </summary>
        public int Seconds { get; internal set; }

        /// <summary>
        /// Gets the log message timestamp: nanosecond part. To be added to Seconds
        /// </summary>
        public int NanoSeconds { get; internal set; }

        /// <summary>
        /// Gets the log message timestamp converted to local time
        /// </summary>
        public DateTime RemoteTimestamp
        {
            get
            {
                return m_epoc.AddSeconds(Seconds).AddTicks(NanoSeconds / 100).ToLocalTime();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public DateTime LocalTimestamp { get; internal set; }

        /// <summary>
        /// Gets the event data if the log message source is events-buffer; null otherwise
        /// </summary>
        public EventContainer EventData { get; internal set; }

        /// <summary>
        /// Gets a value indicating if the EventData is originated from GC
        /// </summary>
        public bool HasGCEventData
        {
            get
            {
                return EventData != null && (EventData is GcEventContainer);
            }
        }
        
        /// <summary>
        /// Formats the log data into readable format
        /// </summary>
        /// <returns>Log data in readable format</returns>
        public override string ToString()
        {
            return ToString(OutputFormat.Brief, LogTimestampMode.Remote);
        }

        /// <summary>
        /// Formats the log data into readable format
        /// </summary>
        /// <param name="format">Format to use</param>
        /// <returns>Log data in readable format</returns>
        public string ToString(OutputFormat format, LogTimestampMode timestampMode)
        {
            var timestamp = timestampMode == LogTimestampMode.Remote ? RemoteTimestamp : LocalTimestamp;

            switch (format)
            {
                case OutputFormat.Brief:
                    return string.Format("{0}/{1}({2}): {3}", Priority.ToString()[0], Tag.PadRight(8, ' '), ProcessId.ToString().PadLeft(5, ' '), Data);
                case OutputFormat.Long:
                    return string.Format("[ {0} {1}: {2} {3}/{4} ]\r\n{5}\r\n", timestamp.ToString("MM-dd HH:mm:ss.fff"), ProcessId, ThreadId, Priority.ToString()[0], Tag, Data);
                case OutputFormat.Process:
                    return string.Format("{0}({1}) {2}", Priority.ToString()[0], ProcessId.ToString().PadLeft(5, ' '), Data);
                case OutputFormat.Raw:
                    return Data;
                case OutputFormat.Tag:
                    return string.Format("{0}/{1}: {2}", Priority.ToString()[0], Tag, Data);
                case OutputFormat.ThreadTime:
                    return string.Format("{0} {1} {2} {3} {4}: {5}", timestamp.ToString("MM-dd HH:mm:ss.fff"), ProcessId.ToString().PadLeft(5, ' '), ThreadId.ToString().PadLeft(5, ' '), Priority.ToString()[0], Tag, Data);
                case OutputFormat.Time:
                    return string.Format("{0} {1}/{2}( {3}): {4}", timestamp.ToString("MM-dd HH:mm:ss.fff"), Priority.ToString()[0], Tag.PadRight(8, ' '), ProcessId, Data);
                case OutputFormat.ADBMimic:
                    return string.Format("{0} {1}/{2}( {3}) ({4}): {5}", timestamp.ToString("MM-dd HH:mm:ss.fff"), Priority.ToString()[0], Tag, ProcessId, ThreadId, Data);
                default:
                    return string.Empty;
            }
        }
    }
}
