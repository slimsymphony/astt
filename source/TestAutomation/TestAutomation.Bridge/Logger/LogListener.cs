using Managed.Adb;
using Managed.Adb.Logs;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Listener for a single log bugger
    /// </summary>
    public class LogListener : ILogListener, IListener
    {
        private Regex m_messageRegex = new Regex("^(.*)\x00(.*)\x00$", RegexOptions.Compiled | RegexOptions.Singleline);
        private Encoding m_encoding = Encoding.GetEncoding("UTF-8");
        private LogBuffer m_sourceBuffer;
        private Device m_device;
        private Thread m_logger;
        private EventLogParser m_eventParser;
        private bool m_isLogging;
        private const string LOG_HOME = "/dev/log/";
        private LogReceiver m_receiver;
        private LogEntryCache m_cache;

        /// <summary>
        /// Internal class constructor
        /// </summary>
        /// <param name="device">The target device</param>
        /// <param name="sourceBuffer">Source buffer to listen</param>
        internal LogListener(Device device, LogBuffer sourceBuffer)
        {
            m_device = device;
            m_sourceBuffer = sourceBuffer;

            if (m_sourceBuffer == LogBuffer.Events)
            {
                m_eventParser = new EventLogParser();
                if (!m_eventParser.Init(m_device))
                {
                    throw new Exception("Failed to init the event log parser");
                }
            }
        }

        /// <summary>
        /// Fired on every log message received from the target log buffer
        /// </summary>
        public event LogDataReceivedHandler LogDataReceived;

        /// <summary>
        /// 
        /// </summary>
        public LogBuffer SourceBuffer { get { return m_sourceBuffer; }}

        /// <summary>
        /// Sends the log data t every subscriber
        /// </summary>
        /// <param name="data">Log data</param>
        private void OnDataReceived(ILogData data)
        {
            if (m_cache != null)
            {
                m_cache.TryAdd(data);
            }
            if (LogDataReceived != null)
            {
                LogDataReceived(data);
            }
        }

        /// <summary>
        /// Called on every log entry
        /// </summary>
        /// <param name="entry">Raw log data</param>
        public void NewEntry(LogEntry entry, DateTime localTimestamp)
        {
            //We got a log message from events buffer, and it needs a special attention
            if (m_sourceBuffer == LogBuffer.Events && m_eventParser != null)
            {
                var container = m_eventParser.Parse(entry);
                if (container != null)
                {
                    OnDataReceived(new LogData()
                    {
                        LocalTimestamp = localTimestamp,
                        SourceBuffer = m_sourceBuffer,
                        Priority = LogPriority.Info,
                        ProcessId = entry.ProcessId,
                        ThreadId = entry.ThreadId,
                        Seconds = entry.Seconds,
                        NanoSeconds = entry.NanoSeconds,
                        Tag = container.TagName,
                        Data = container.ToString().TrimEnd('\r', '\n', ' '),
                        EventData = container
                    });
                }
            }
            //We got a log message either from main, radio, or system buffer
            else if (entry.Data.Length > 1)
            {
                var priority = 0xFF & entry.Data[0];
                var data = m_encoding.GetString(entry.Data, 1, entry.Data.Length - 1);
                var dataMatch = m_messageRegex.Match(data);
                if (dataMatch.Success)
                {
                    OnDataReceived(new LogData()
                    {
                        LocalTimestamp = localTimestamp,
                        SourceBuffer = m_sourceBuffer,
                        Priority = (LogPriority)priority,
                        ProcessId = entry.ProcessId,
                        ThreadId = entry.ThreadId,
                        Seconds = entry.Seconds,
                        NanoSeconds = entry.NanoSeconds,
                        Tag = dataMatch.Groups[1].Value,
                        Data = dataMatch.Groups[2].Value.TrimEnd('\r', '\n', ' ')
                    });
                }
            }
        }

        /// <summary>
        /// Not used, but needs to be implemented
        /// </summary>
        /// <param name="data"></param>
        /// <param name="offset"></param>
        /// <param name="length"></param>
        public void NewData(byte[] data, int offset, int length) { }

        /// <summary>
        /// Clears the target log buffer
        /// </summary>
        public void ClearLogBuffer()
        {
            m_device.ExecuteShellCommand(string.Format("logcat -c -b {0}", m_sourceBuffer.ToString().ToLower()), NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
        }

        /// <summary>
        /// Starts the logging
        /// </summary>
        /// <param name="clearBuffer">Value indicating whether to clear the log before</param>
        public void Start(bool clearBuffer = true)
        {
            if (!m_isLogging)
            {
                m_logger = new Thread(() =>
                {
                    try
                    {
                        if (clearBuffer)
                        {
                            ClearLogBuffer();
                        }

                        m_isLogging = true;
                        m_receiver = new LogReceiver(this);
                        m_device.RunCatLog(LOG_HOME + m_sourceBuffer.ToString().ToLower(), m_receiver);
                    }
                    catch (ThreadAbortException)
                    {
                        Thread.ResetAbort();
                    }
                    catch (Exception) { }
                    finally
                    {
                        m_isLogging = false;
                    }

                }) {IsBackground = true, Priority = ThreadPriority.Highest};

                m_logger.Start();                
            }
        }

        /// <summary>
        /// Stops the logging
        /// </summary>
        /// <param name="clearBuffer">Value indicating whether to clear the log before</param>
        public void Stop(bool clearBuffer = false)
        {
            if (m_isLogging)
            {
                if (clearBuffer)
                {
                    ClearLogBuffer();
                }

                if (m_logger != null && m_logger.IsAlive)
                {
                    if (m_receiver != null)
                    {
                        m_receiver.Cancel();
                    }
                    if (!m_logger.Join(1000))
                    {
                        m_logger.Abort(); //From this level there are no sophisticated method to stop the logger thread
                    }
                }

                m_isLogging = false;
            }
        }

        /// <summary>
        /// Sets the cache object for the log entries
        /// </summary>
        /// <param name="cache">The cache object</param>
        public void SetCache(LogEntryCache cache)
        {
            m_cache = cache;
        }
    }
}
