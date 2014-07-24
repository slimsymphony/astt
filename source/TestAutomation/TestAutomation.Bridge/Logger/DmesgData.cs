using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Container class for dmesg/kernel log messages
    /// </summary>
    public class DmesgData : ILogData
    {
        private static Regex m_regexpDmesgLog = new Regex("^\\<(\\d+)\\>\\s*\\[\\s*(\\d+.\\d+)\\s*\\]\\s*(.*)", RegexOptions.Compiled);

        /// <summary>
        /// Always gets Kernel
        /// </summary>
        public LogBuffer SourceBuffer
        {
            get
            {
                return LogBuffer.Kernel;
            }
        }

        /// <summary>
        /// Gets the log message priority
        /// </summary>
        public DmesgLogPriority Priority { get; private set; }

        /// <summary>
        /// Gets the log message tag
        /// </summary>
        public string Tag { get; private set; }

        /// <summary>
        /// Gets the log message data
        /// </summary>
        public string Data { get; private set; }

        /// <summary>
        /// Gets the remote time stamp
        /// </summary>
        public DateTime RemoteTimestamp { get; private set; }

        /// <summary>
        /// Gets the local time stamp
        /// </summary>
        public DateTime LocalTimestamp { get; private set; }

        /// <summary>
        /// Parses log message from raw string
        /// </summary>
        /// <param name="dmsg">Raw kernel message</param>
        /// <param name="timestamp">Local time stamp</param>
        /// <param name="kernelBoot">Remote system uptime</param>
        /// <returns>DmesgData instance; null if unable to parse</returns>
        internal static DmesgData FromString(string dmsg, DateTime timestamp, DateTime? kernelBoot)
        {
            var m = m_regexpDmesgLog.Match(dmsg);
            if (m.Success)
            {               
                int priority;
                if (int.TryParse(m.Groups[1].Value, out priority))
                {
                    double upTimeStamp = 0;
                    if (kernelBoot.HasValue && double.TryParse(m.Groups[2].Value, NumberStyles.Number, CultureInfo.InvariantCulture, out upTimeStamp))
                    {
                        var remoteStamp = kernelBoot.Value.AddSeconds(upTimeStamp).ToLocalTime();
                        return new DmesgData()
                        {
                            Priority = (DmesgLogPriority)priority,
                            Tag = string.Empty,
                            Data = m.Groups[3].Value.TrimEnd('\r', '\n', ' '),
                            LocalTimestamp = timestamp,
                            RemoteTimestamp = remoteStamp
                        };
                    }
                }
            }
            return null;
        }

        /// <summary>
        /// Formats the log message into a string presentation
        /// </summary>
        /// <returns>String presentation of the message</returns>
        public override string ToString()
        {
            return ToString(OutputFormat.Brief, LogTimestampMode.Remote);
        }

        /// <summary>
        /// Formats the log message into a string presentation
        /// </summary>
        /// <param name="format">Desired format of the message</param>
        /// <param name="timestampMode">Desired timestamp mode for the message</param>
        /// <returns>String presentation of the message</returns>
        public string ToString(OutputFormat format, LogTimestampMode timestampMode)
        {
            var timestamp = timestampMode == LogTimestampMode.Remote ? RemoteTimestamp : LocalTimestamp;

            switch (format)
            {
                case OutputFormat.Brief:
                case OutputFormat.Process:
                case OutputFormat.Tag:
                    return string.Format("{0}/{1}", Priority.ToString()[0], Data);
                case OutputFormat.Long:
                    return string.Format("[ {0} {1} ]\n{2}\n", timestamp.ToString("MM-dd HH:mm:ss.fff"), Priority.ToString()[0], Data);
                case OutputFormat.Raw:
                    return string.Format("<{0}>[{1}]{2}", (int)Priority, timestamp.ToString("MM-dd HH:mm:ss.fff"), Data);
                case OutputFormat.ThreadTime:
                case OutputFormat.Time:
                    return string.Format("{0} {1}/{2}", timestamp.ToString("MM-dd HH:mm:ss.fff"), Priority.ToString()[0], Data);
                case OutputFormat.ADBMimic:
                    return string.Format("{0} {1}: {2}", timestamp.ToString("MM-dd HH:mm:ss.fff"), Priority.ToString()[0], Data);
                default:
                    return string.Empty;
            }
        }
    }
}
