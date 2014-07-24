using Managed.Adb;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Managed.Adb.MoreLinq;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Cache for log entries
    /// </summary>
    public class LogEntryCache : BlockingCollection<ILogData>
    {
        /// <summary>
        /// Clears the cache
        /// </summary>
        public void Clear()
        {
            this.TakeWhile(entry => true);
        }

        /// <summary>
        /// Gets the next cached entry. Blocks the call until there is something in the cache
        /// </summary>
        /// <param name="cancelToken">CancelToken to cancel the operations</param>
        /// <returns>ILogData entry. Null if take operation failed</returns>
        public ILogData GetNext(CancellationToken cancelToken)
        {
            ILogData entry;
            if (this.TryTake(out entry, int.MaxValue, cancelToken))
            {
                return entry;
            }
            return null;
        }
    }

    /// <summary>
    /// Class for listening and recording log messages from an Android device
    /// </summary>
    public sealed class Logger : IDisposable
    {
        private Device m_device;
        private LogEntryCache m_cache;
        private CancellationTokenSource m_cancel;
        private List<IListener> m_listeners;
        private bool m_isListening;
        private bool m_isRecording;
        private bool m_disposed;
        private OutputFormat m_format;
        private LogTimestampMode m_timestampMpde;
        private bool m_writeSourceBufferName;
        private event LogDataReceivedHandler m_logDataReceived;
        private TextWriter _writer;
        private static object _writerLock = new object();
        private string m_logFile;
        private int m_logIndex = 0;

        private static readonly Dictionary<LogPriority, DmesgLogPriority> PriorityMap = 
            new Dictionary<LogPriority, DmesgLogPriority>
                {
                    { LogPriority.Debug, DmesgLogPriority.Debug },
                    { LogPriority.Info, DmesgLogPriority.Info },
                    { LogPriority.Error, DmesgLogPriority.Error },
                    { LogPriority.Fatal, DmesgLogPriority.Critical }, 
                    { LogPriority.Warning, DmesgLogPriority.Warning }
                };

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="device">Device from which to listen for the log messages</param>
        public Logger(Device device)
        {
            m_device = device;
            m_cache = new LogEntryCache();
            m_listeners = new List<IListener>();
            m_format = OutputFormat.Brief;
            m_timestampMpde = LogTimestampMode.Remote;
            m_writeSourceBufferName = true;
        }

        /// <summary>
        /// Class destructor
        /// </summary>
        ~Logger()
        {
            Dispose();
        }

        /// <summary>
        /// Gets of sets the output format for log recording. This value cannot be changed during the recording
        /// </summary>
        public OutputFormat OutputFormat 
        {
            get
            {
                CheckDisposed();
                return m_format;
            }
            set
            {
                CheckDisposed();
                if (!m_isRecording)
                {
                    m_format = value;
                }
            }
        }

        /// <summary>
        /// Gets of sets the time stamp mode for log recording. This value cannot be changed during the recording
        /// </summary>
        public LogTimestampMode TimestampMode
        {
            get
            {
                CheckDisposed();
                return m_timestampMpde;
            }
            set
            {
                CheckDisposed();
                if (!m_isRecording)
                {
                    m_timestampMpde = value;
                }
            }
        }

        /// <summary>
        /// Gets the recording state
        /// </summary>
        public bool IsRecording
        {
            get
            {
                CheckDisposed();
                return m_isRecording;
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether to write the name of the source buffer in the beginning
        /// of the each log message written into file.
        /// This value cannot be changed during the recording.
        /// </summary>
        public bool WriteSourceBufferName
        {
            get
            {
                CheckDisposed();
                return m_writeSourceBufferName;
            }
            set
            {
                CheckDisposed();
                if (!m_isRecording)
                {
                    m_writeSourceBufferName = value;
                }
            }
        }

        /// <summary>
        /// Fired when a log message is being received
        /// </summary>
        public event LogDataReceivedHandler LogDataReceived
        {
            add
            {
                CheckDisposed();
                m_logDataReceived += value;
            }
            remove
            {
                CheckDisposed();
                m_logDataReceived -= value;
            }
        }

        /// <summary>
        /// Gets the bit flag of sources, which are being listened
        /// </summary>
        public LogBuffer ActiveSources
        {
            get
            {
                LogBuffer bitmap = 0;
                m_listeners.Select(l => l.SourceBuffer).ToArray().ForEach(b => bitmap |= b);
                return bitmap;
            }
        }

        /// <summary>
        /// Resets the cache
        /// </summary>
        private void Reset()
        {
            m_cancel = new CancellationTokenSource();
            if (m_cache != null) m_cache.Clear();
        }
        
        /// <summary>
        /// Starts the log message listening from main buffer
        /// </summary>
        /// <param name="clearBuffer">Value indicating whether to clear the log before</param>
        public void Start(bool clearBuffer = true)
        {
            CheckDisposed();
            Start(LogBuffer.All, clearBuffer);
        }

        /// <summary>
        /// Starts the log message listening from defined buffers
        /// </summary>
        /// <param name="sourceBuffer">Buffers to listen</param>
        /// <param name="clearBuffer">Value indicating whether to clear the log before</param>
        public void Start(LogBuffer sourceBuffer, bool clearBuffer = true)
        {
            CheckDisposed();

            if (m_isListening)
            {
                return;
            }

            try
            {
                Reset();
                StartEventDispatching();

                if (sourceBuffer.HasFlag(LogBuffer.All))
                {
                    sourceBuffer = LogBuffer.Main | LogBuffer.Radio | LogBuffer.Events | LogBuffer.System | LogBuffer.Kernel;
                }
                if (sourceBuffer.HasFlag(LogBuffer.Main) && !m_listeners.Exists(l => l.SourceBuffer.HasFlag(LogBuffer.Main)))
                {
                    m_listeners.Add(new LogListener(m_device, LogBuffer.Main));
                }
                if (sourceBuffer.HasFlag(LogBuffer.Radio) && !m_listeners.Exists(l => l.SourceBuffer.HasFlag(LogBuffer.Radio)))
                {
                    m_listeners.Add(new LogListener(m_device, LogBuffer.Radio));
                }
                if (sourceBuffer.HasFlag(LogBuffer.System)  && !m_listeners.Exists(l => l.SourceBuffer.HasFlag(LogBuffer.System)))
                {
                    m_listeners.Add(new LogListener(m_device, LogBuffer.System));
                }
                if (sourceBuffer.HasFlag(LogBuffer.Events)  && !m_listeners.Exists(l => l.SourceBuffer.HasFlag(LogBuffer.Events)))
                {
                    m_listeners.Add(new LogListener(m_device, LogBuffer.Events));
                }
                if (sourceBuffer.HasFlag(LogBuffer.Kernel) && !m_listeners.Exists(l => l.SourceBuffer.HasFlag(LogBuffer.Kernel)) && m_device.IsRooted)
                {
                    m_listeners.Add(new DmesgListener(m_device));
                }
                
                Parallel.ForEach(m_listeners, (l) =>
                    {
                        l.SetCache(m_cache); 
                        l.Start(clearBuffer);
                    });

                m_isListening = true;
            }
            catch (Exception err)
            {
                Console.Error.Write("Error when setting log listeners: " + err);
                Stop();
            }            
        }

        /// <summary>
        /// Start the event dispatcher
        /// </summary>
        private void StartEventDispatching()
        {
            Task.Factory.StartNew(() =>
            {
                while (m_cancel != null && !m_cancel.IsCancellationRequested)
                {
                    try
                    {
                        var data = m_cache.GetNext(m_cancel.Token);

                        if (data != null)
                        {
                            OnLogDataReceived(data);
                        }
                    }
                    catch (OperationCanceledException) { }
                    catch (ObjectDisposedException) { }
                    catch (Exception e)
                    {
                        //Log e
                    }
                }
            });
        }

        /// <summary>
        /// Internal handler for log messages
        /// </summary>
        /// <param name="data">Log message data</param>
        private void OnLogDataReceived(ILogData data)
        {
            if (m_logDataReceived != null)
            {
                m_logDataReceived(data);
            }

            if (m_isRecording && _writer != null)
            {
                CheckLogDataSize();

                if (m_writeSourceBufferName)
                {
                    _writer.WriteLine(string.Format("[{0}] [{1}:] {2}", data.LocalTimestamp.ToString("MM-dd HH:mm:ss.fff"), data.SourceBuffer, data.ToString(OutputFormat, TimestampMode)));
                }
                else
                {
                    _writer.WriteLine(string.Format("[{0}] {1}", data.LocalTimestamp.ToString("MM-dd HH:mm:ss.fff"), data.ToString(OutputFormat, TimestampMode)));
                }

                m_logIndex += 1;

                _writer.Flush();
            }
        }

        /// <summary>
        /// Internal log writer creator
        /// </summary>
        private void CreateLogWriter()
        {
            if (_writer != null)
            {
                try
                {
                    _writer.Flush();
                    _writer.Dispose();
                }
                catch (ObjectDisposedException) { }
            }
            _writer = TextWriter.Synchronized(new StreamWriter(new FileStream(m_logFile, FileMode.Create, FileAccess.Write, FileShare.Read)));
        }

        /// <summary>
        /// Internal handler for log messages
        /// </summary>
        /// <param name="data">Log message data</param>
        private void CheckLogDataSize()
        {
            // check file size every 1000 line
            if (m_logFile != null && (m_logIndex % 1000) == 0)
            {
                var info = new FileInfo(m_logFile);

                // split log file if size is over 100 mega bytes
                if (info.Length > 100000000)
                {
                    m_isRecording = false;
                    m_logIndex = 0;

                    if (_writer != null)
                    {
                        try
                        {
                            _writer.Flush();
                            _writer.Dispose();
                        }
                        catch (ObjectDisposedException) { }
                    }

                    // set new file name
                    var logDir = Path.GetDirectoryName(m_logFile);
                    var logName = Path.GetFileName(m_logFile);
                    var plainLogName = Path.GetFileNameWithoutExtension(logName);

                    int index;

                    // already splitted log
                    if (logName.Contains("_"))
                    {
                        index = Convert.ToInt16(plainLogName.Split(new char[] { '_' }).Last());
                        var beginOfLog = plainLogName.Split(new char[] { '_' }).First();
                        index += 1;

                        logName = String.Join("", beginOfLog, "_", index.ToString(), ".txt");
                    // original log
                    }
                    else
                    {
                        index = 2;

                        logName = String.Join("", plainLogName, "_", index.ToString(), ".txt");
                    }
                    
                    m_logFile = Path.Combine(logDir, logName);

                    CreateLogWriter();

                    m_isRecording = true;
                }
            }
        }

        /// <summary>
        /// Adds a text marker to a log file, which is being recorded.
        /// Has no effect if the recording is not ongoing
        /// </summary>
        /// <param name="marker">Marker text</param>
        public void AddMarkerToLogFile(string marker)
        {
            CheckDisposed();

            if (m_isRecording && _writer != null)
            {
                CheckLogDataSize();

                m_logIndex += 1;

                _writer.WriteLine(string.Format("[{0}] [Marker:] {1}", DateTime.Now.ToString("MM-dd HH:mm:ss.fff"), marker));
                _writer.Flush();
            }
        }

        /// <summary>
        /// Writes a message to kernel log. NOTE that this requires root permissions, but is safe to call in any case.
        /// </summary>
        /// <param name="message">The message to write</param>
        /// <param name="priority">The message priority</param>
        public void WriteToKernelLog(string message, DmesgLogPriority priority = DmesgLogPriority.Info)
        {
            CheckDisposed();

            if (m_device.IsOffline) return;
            
            if (priority == DmesgLogPriority.Unknown) priority = DmesgLogPriority.Info;

            m_device.ExecuteShellCommand(string.Format("k='/dev/kmsg'; if [ -r $k ]; then echo '<{0}>{1}' > $k; fi", 
                (int)priority,
                message.Substring(0, Math.Min(100, message.Length))), 
                NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
        }

        /// <summary>
        /// Writes a log message to user space log
        /// </summary>
        /// <param name="message">The message to write</param>
        /// <param name="tag">The tag for the message</param>
        /// <param name="destination">The destionation buffer</param>
        /// <param name="priority">The priority of the message</param>
        public void WriteToUserLog(string message, string tag, LogBuffer destination = LogBuffer.Main, LogPriority priority = LogPriority.Info)
        {
            CheckDisposed();

            if (string.IsNullOrEmpty(message) || m_device.IsOffline) return;

            tag = !string.IsNullOrEmpty(tag) ? tag : "TestAutomation";

            var buffer = destination.ToString()
                .Split(new[] {", "}, StringSplitOptions.None)
                .Select(v => (LogBuffer) Enum.Parse(typeof (LogBuffer), v)).FirstOrDefault();

            buffer = buffer.HasFlag(LogBuffer.All) ? LogBuffer.Main : buffer;

            if (priority == LogPriority.Default || priority == LogPriority.Silent || priority == LogPriority.Unknown) priority = LogPriority.Info;

            if (buffer.HasFlag(LogBuffer.Kernel))
            {
                var kpriority = PriorityMap.ContainsKey(priority) ? PriorityMap[priority] : DmesgLogPriority.Info;
                WriteToKernelLog(string.Format("{0}/{1}", tag, message), kpriority);
                return;
            }

            var command = string.Format("echo \\\\0{0}'{1}'\\\\0'{2}'\\\\0 > /dev/log/{3}", 
                (int)priority,
                tag.Substring(0, Math.Min(20, tag.Length)),
                message.Substring(0, Math.Min(250, message.Length)),
                buffer.ToString().ToLower());

            m_device.ExecuteShellCommand(command, NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
        }

        /// <summary>
        /// Stops listening for the log messages
        /// </summary>
        /// <param name="clearBuffer">Value indicating whether to clear the log before</param>
        public void Stop(bool clearBuffer = false)
        {
            CheckDisposed();

            //Stops the consumer thread
            if (m_cancel != null) m_cancel.Cancel();

            //Stops the producer threads
            Parallel.ForEach(m_listeners, (l) =>
                {
                    l.Stop(clearBuffer);
                });

            m_listeners.Clear();
            m_isListening = false;
        }

        /// <summary>
        /// Stops listening the sources given this the bit field
        /// </summary>
        /// <param name="sourceBuffer">Bit field of source buffers</param>
        /// <param name="clearBuffer">Value indicating whether to clear each buffer after the listening ends</param>
        public void StopListeners(LogBuffer sourceBuffer, bool clearBuffer = false)
        {
            CheckDisposed();

            if (sourceBuffer.HasFlag(LogBuffer.All))
            {
                Stop(clearBuffer);
                return;
            }

            foreach (var listener in m_listeners.ToArray().Where(listener => sourceBuffer.HasFlag(listener.SourceBuffer)))
            {
                listener.Stop(clearBuffer);
                m_listeners.Remove(listener);
            }

            if (m_listeners.Count != 0) return;
            
            if (m_cancel != null) m_cancel.Cancel();
            m_isListening = false;
        }

        /// <summary>
        /// Starts writing log messages into a file
        /// </summary>
        /// <param name="fileLocation">A file where to write</param>    
        public void StartRecording(string fileLocation)
        {
            CheckDisposed();

            if (string.IsNullOrEmpty(fileLocation))
            {
                throw new ArgumentNullException("logFileLocation");
            }

            if (m_isRecording)
            {
                return;
            }

            m_logFile = fileLocation;

            lock (_writerLock)
            {
                m_isRecording = false;

                CreateLogWriter();

                m_isRecording = true;
            }
        }

        /// <summary>
        /// Stops log message recording into a file
        /// </summary>
        public void StopRecording()
        {
            CheckDisposed();

            if (m_isRecording)
            {
                lock (_writerLock)
                {
                    m_isRecording = false;

                    if (_writer != null)
                    {
                        try
                        {
                            _writer.Flush();
                            _writer.Dispose();
                        }
                        catch (ObjectDisposedException) { }
                    }
                }
            }
        }

        /// <summary>
        /// Disposes the object: frees the resources and stops the log listening and recording
        /// </summary>
        public void Dispose()
        {
            if (!m_disposed)
            {
                Stop();
                StopRecording();               
                m_disposed = true;
            }
        }

        /// <summary>
        /// Throws ObjectDisposedException if object has been already disposed
        /// </summary>
        private void CheckDisposed()
        {
            if (m_disposed)
            {
                throw new ObjectDisposedException(GetType().Name);
            }
        }
    }
}
