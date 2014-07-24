using Managed.Adb;
using Managed.Adb.Logs;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using Managed.Adb.Receivers;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Class for listening dmesg/kernel messages
    /// </summary>
    public sealed class DmesgListener : IListener
    {
        private const string LOG_LOCATION = "/proc/kmsg";
        private const string UPTIME_LOCATION = "/proc/uptime";
        private const string BOOT_KEY = "ro.runtime.firstboot";
        private const string KERNEL_BOOT_QUERY = "boot=($(grep ^btime /proc/stat)); echo ${{boot[1]}}";
        private const int READ_BUFFER_SIZE = 100;
        public const string CLEAR = "==CLEAR==";

        private Thread m_logger;
        private Device m_device;
        private DateTime? m_bootTime;
        private LogEntryCache m_cache;

        private bool m_clearing;

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="device">Device instance from which to listen</param>
        internal DmesgListener(Device device)
        {
            m_device = device;
        }

        /// <summary>
        /// Event which is fired on every log entry
        /// </summary>
        public event LogDataReceivedHandler LogDataReceived;

        /// <summary>
        /// 
        /// </summary>
        public LogBuffer SourceBuffer { get { return LogBuffer.Kernel; }}

        /// <summary>
        /// Gets a value indicating whether the logging is active
        /// </summary>
        public bool IsLogging { get; private set; }

        /// <summary>
        /// Clears the dmesg buffer
        /// </summary>
        public void ClearLogBuffer()
        {
            //Cannot be cleared: dmesg -c does not work with this
        }

        /// <summary>
        /// Sends a synch message to the kernel buffer to see the delta between timestamps and real kernel uptime
        /// </summary>
        public void SendSyncMessage()
        {
            var command = "k='/dev/kmsg'; if [ -r $k ]; then echo '<6>**synctime:'$(cat /proc/uptime) > $k; fi";
            m_device.ExecuteShellCommand(command, NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
        }

        /// <summary>
        /// Enables timestamps in the kernel messages. Not in all the Linux distributions timestamps are enabled by default
        /// </summary>
        private void EnableTimestamps()
        {
            var command = "ts='/sys/module/printk/parameters/time'; if [ -r $ts ]; then echo 1 > $ts; fi";
            m_device.ExecuteShellCommand(command, NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
        }

        /// <summary>
        /// Sends the clear message to the kernel buffer
        /// </summary>
        private void SendClearMessage()
        {
            var command = string.Format("k='/dev/kmsg'; if [ -r $k ]; then echo '{0}' > $k; fi", CLEAR);
            m_device.ExecuteShellCommand(command, NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
        }

        /// <summary>
        /// Starts listening the dmesg data. Clears the buffer by default
        /// </summary>
        public void Start()
        {
            Start(true);
        }

        /// <summary>
        /// Starts listening for the dmesg data
        /// </summary>
        /// <param name="clearBuffer">Value indicating whether to clear the buffer</param>
        public void Start(bool clearBuffer = true)
        {
            if (!IsLogging)
            {
                GetBootTime();
                EnableTimestamps();

                m_logger = new Thread(() =>
                {
                    try
                    {
                        using(var receiver = new DmesgReceiver(OnOutput))
                        {
                            if (clearBuffer)
                            {
                                m_clearing = clearBuffer;
                                SendClearMessage();
                            }
                            IsLogging = true;
                            m_device.RunTailService(LOG_LOCATION, receiver, READ_BUFFER_SIZE);
                        }
                    }
                    catch (ThreadAbortException)
                    {
                        Thread.ResetAbort();
                    }
                    catch (Exception) { }
                    finally
                    {
                        IsLogging = false;
                    }

                }) {IsBackground = true, Priority = ThreadPriority.Highest};

                m_logger.Start();
            }
        }
       
        /// <summary>
        /// Stops listening for the dmesg data 
        /// </summary>
        /// <param name="clearBuffer">Value indicating whether to clear the buffer</param>
        public void Stop(bool clearBuffer = false)
        {
            if (IsLogging)
            {
                if (m_logger != null && m_logger.IsAlive)
                {
                    m_logger.Abort();
                }
                IsLogging = false;
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

        /// <summary>
        /// 
        /// </summary>
        /// <param name="timeStamp"></param>
        /// <param name="line"></param>
        private void OnOutput(DateTime timeStamp, string line)
        {
            foreach (var trace in line.Split(new[] { '\n' }, StringSplitOptions.RemoveEmptyEntries))
            {
                var dmsg = DmesgData.FromString(trace, timeStamp, m_bootTime);

                if (dmsg != null)
                {
                    if (m_clearing)
                    {
                        if (!dmsg.Data.Contains(CLEAR))
                        {
                            continue;
                        }
                        else
                        {
                            m_clearing = false;
                            continue;
                        }
                    }
                    if (m_cache != null)
                    {
                        m_cache.TryAdd(dmsg);
                    }
                    if (LogDataReceived != null)
                    {
                        LogDataReceived(dmsg);
                    }
                }
            }
        }

        /// <summary>
        /// Stores the device boot since epoc
        /// </summary>
        private void GetBootTime()
        {
            //First, we try to receive the Kernel boot time; which is the time we really want. However, that time
            //is only presented with accuracy of seconds
            var epoc = new DateTime(1970, 1, 1, 0, 0, 0);
            var recv = new KernelBootReceiver();
            m_device.ExecuteShellCommand(KERNEL_BOOT_QUERY, recv, TABInterface.DEFAULT_ADB_TIMEOUT);

            if (recv.Received)
            {
                m_bootTime = epoc.AddSeconds(recv.KernelBoot.Value);
            }
            //We didn't get it; so we need to us Android FW boot time, and we well see several seconds of delta in the kernel log timestamps
            //when comparing to e.g. logcat log timestamps. But, it's better than nothing
            else
            {
                if (m_device.Properties != null && m_device.Properties.ContainsKey(BOOT_KEY))
                {
                    var msStr = m_device.Properties[BOOT_KEY];
                    double ms = 0;
                    if (double.TryParse(msStr, out ms))
                    {

                        m_bootTime = epoc.AddMilliseconds(ms);
                    }
                }
            }
        }

        /// <summary>
        /// Gets the device/kernel uptime in seconds; null if not available
        /// </summary>
        /// <returns>The device/kernel uptime in seconds; null if not available</returns>
        private double? GetDeviceUptime()
        {
            var receiver = new UpTimeReceiver();
            m_device.ExecuteShellCommand(string.Format("cat {0}", UPTIME_LOCATION), receiver, TABInterface.DEFAULT_ADB_TIMEOUT);
            return receiver.Uptime;
        }

        /// <summary>
        /// Class for receiving/tailing dmesg/kernel trace lines
        /// </summary>
        private class DmesgReceiver : SingleLineReceiver, IDisposable
        {
            private Action<DateTime, string> m_output;

            /// <summary>
            /// Class constructor
            /// </summary>
            /// <param name="action">Action to be called</param>
            public DmesgReceiver(Action<DateTime, string> action)
            {
                m_output = action;
            }

            /// <summary>
            /// Sets the handler to null
            /// </summary>
            public void Dispose()
            {
                m_output = null;
            }

            /// <summary>
            /// 
            /// </summary>
            /// <param name="timeStamp"></param>
            /// <param name="line"></param>
            protected override void OnNewLine(DateTime timeStamp, string line)
            {
                if (m_output == null || string.IsNullOrEmpty(line)) return;
                m_output.Invoke(timeStamp, line);
            }
        }

        /// <summary>
        /// Receiver for device uptime
        /// </summary>
        private class UpTimeReceiver : MultiLineReceiver
        {
            private static Regex m_uptimeMatcher = new Regex(@"([0-9\.]+)[ \t][0-9\.]+", RegexOptions.Compiled);

            /// <summary>
            /// Process all te output lines
            /// </summary>
            /// <param name="lines">Lines from shell stdout</param>
            protected override void ProcessNewLines(string[] lines)
            {
                if (lines != null && lines.Length > 0)
                {
                    var line = lines.FirstOrDefault();
                    if (line != null)
                    {
                        var match = m_uptimeMatcher.Match(line);
                        double uptime;
                        if (match.Success && double.TryParse(match.Groups[1].Value, NumberStyles.Number, CultureInfo.InvariantCulture, out uptime))
                        {
                            Uptime = uptime;
                        }
                    }
                }
            }

            /// <summary>
            /// Device/kernel uptime in seconds; null if not received
            /// </summary>
            public double? Uptime { get; private set; }
        }

        /// <summary>
        /// Raceiver for Kernel boot time
        /// </summary>
        private class KernelBootReceiver : MultiLineReceiver
        {
            /// <summary>
            /// Gets a value indicating whether the kernel boot time has been successfully received
            /// </summary>
            public bool Received
            {
                get
                {
                    return KernelBoot.HasValue;
                }
            }

            /// <summary>
            /// Gets the kernel boot time if available; otherwise, null
            /// </summary>
            public double? KernelBoot { get; private set; }

            /// <summary>
            /// Processes any data received from the shell stdout
            /// </summary>
            /// <param name="lines">lines printed to shell stdout and stderr</param>
            protected override void ProcessNewLines(string[] lines)
            {
                if (lines != null && lines.Length > 0)
                {
                    double boot;

                    if (double.TryParse(lines[0].Trim(), out boot))
                    {
                        KernelBoot = boot;
                    }
                }
            }
        }
    }
}
