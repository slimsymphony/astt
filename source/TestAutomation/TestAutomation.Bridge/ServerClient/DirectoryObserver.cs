using Managed.Adb.IO;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using TestAutomation.Bridge.ScriptingTools;
using TestAutomation.Client;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// File change types in the remote device
    /// </summary>
    public enum FileChangeTypes : int
    {
        /// <summary>
        /// Event type: Data was read from a file
        /// </summary>
        ACCESS = 0x00000001,

        /// <summary>
        /// Event mask: All valid event types, combined
        /// </summary>
        ALL_EVENTS = 0x00000fff,

        /// <summary>
        /// Event type: Metadata (permissions, owner, timestamp) was changed explicitly
        /// </summary>
        ATTRIB = 0x00000004,

        /// <summary>
        /// Event type: Someone had a file or directory open read-only, and closed it
        /// </summary>
        CLOSE_NOWRITE = 0x00000010,

        /// <summary>
        /// Event type: Someone had a file or directory open for writing, and closed it
        /// </summary>
        CLOSE_WRITE = 0x00000008,

        /// <summary>
        /// Event type: A new file or subdirectory was created under the monitored directory
        /// </summary>
        CREATE = 0x00000100,

        /// <summary>
        /// Event type: A file was deleted from the monitored directory
        /// </summary>
        DELETE = 0x00000200,

        /// <summary>
        /// Event type: The monitored file or directory was deleted; monitoring effectively stops
        /// </summary>
        DELETE_SELF = 0x00000400,

        /// <summary>
        /// Event type: Data was written to a file
        /// </summary>
        MODIFY = 0x00000002,

        /// <summary>
        /// Event type: A file or subdirectory was moved from the monitored directory
        /// </summary>
        MOVED_FROM = 0x00000040,

        /// <summary>
        /// Event type: A file or subdirectory was moved to the monitored directory
        /// </summary>
        MOVED_TO = 0x00000080,

        /// <summary>
        /// Event type: The monitored file or directory was moved; monitoring continues
        /// </summary>
        MOVE_SELF = 0x00000800,

        /// <summary>
        /// Event type: A file or directory was opened
        /// </summary>
        OPEN = 0x00000020
    }

    /// <summary>
    /// Class for presenting the directory observer event data
    /// </summary>
    public sealed class DirectoryObserverEvent : PythonCallable
    {
        private static DateTime m_epoc = new DateTime(1970, 1, 1, 0, 0, 0);

        /// <summary>
        /// Gets the File Change Type
        /// </summary>
        public FileChangeTypes ChangeType { get; set; }
        
        /// <summary>
        /// Gets the directory in which the file change occured
        /// </summary>
        public string Directory { get; set; }
        
        /// <summary>
        /// Gets the name of the file which changed
        /// </summary>
        public string FileName { get; set; }

        /// <summary>
        /// Gets the full file path
        /// </summary>
        public string FullName
        {
            get
            {
                return FileName != null && Directory != null ? LinuxPath.Combine(Directory, FileName) : null;
            }
        }

        /// <summary>
        /// Gets the event time (milliseconds since the device was booted up)
        /// </summary>
        public long EventTime { get; set; }
        
        /// <summary>
        /// Gets the event time stamp as local date and time (null if failed to convert)
        /// </summary>
        public DateTime TimeStamp
        {
            get
            {
                return m_epoc.AddMilliseconds(EventTime).ToLocalTime();
            }
        }
    }

    /// <summary>
    /// Class for observing file changes in a directory in a remote device
    /// </summary>
    public sealed class DirectoryObserver : PythonCallable, IDisposable
    {
        private TestServerClient m_client;
        private bool m_isObserving;
        private string m_guid;
        private bool m_isDisposed;
        private Regex m_filterPattern;
        private Action<DirectoryObserverEvent> m_handler;

        /// <summary>
        /// Internal class constructor
        /// </summary>
        /// <param name="client">Test server client</param>
        /// <param name="path">Directory path to observe</param>
        internal DirectoryObserver(TestServerClient client, string path, Action<DirectoryObserverEvent> handler) :
            this(client, path, null, handler) { }

        /// <summary>
        /// Internal class constructor
        /// </summary>
        /// <param name="client">Test server client</param>
        /// <param name="path">Directory path to observe</param>
        /// <param name="filter">File name filter</param>
        internal DirectoryObserver(TestServerClient client, string path, string filter, Action<DirectoryObserverEvent> handler)
	    {
            if (string.IsNullOrEmpty(path))
            {
                throw new ArgumentNullException("path");
            }

            if (handler == null)
            {
                throw new ArgumentNullException("handler");
            }
            
            m_handler = handler;
            
            Path = path;
            Filter = filter??string.Empty;
            m_client = client;
            GetGuid();
            CreateFilter();
        }

        /// <summary>
        /// Class destructor
        /// </summary>
        ~DirectoryObserver()
        {
            Dispose();
        }

        /// <summary>
        /// Stops observing
        /// </summary>
        public void Dispose()
        {
            if (m_isDisposed)
            {
                EnableRaisingEvents = false;
                m_isDisposed = true;
            }
        }

        /// <summary>
        /// Enables/disables observing
        /// </summary>
        public bool EnableRaisingEvents 
        {
            get
            {
                return m_isObserving;
            }
            set
            {
                if (value)
                {
                    Start();
                }
                else
                {
                    Stop();
                }
            }
        }

        /// <summary>
        /// Gets the directory path which is observed
        /// </summary>
        public string Path { get; private set; }

        /// <summary>
        /// Gets the filter used for file names
        /// </summary>
        public string Filter { get; private set; }

        /// <summary>
        /// Starts observing
        /// </summary>
        private void Start()
        {
            if (!m_isObserving && m_client != null)
            {
                m_isObserving = m_client.RegisterDirectoryObserver(Path, m_guid);
                if (m_isObserving)
                {
                    m_client.AddDirectoryObserver(OnDirectoryChanged);
                }
            }
        }

        /// <summary>
        /// Stops observing
        /// </summary>
        private void Stop()
        {
            if (m_isObserving && m_client != null)
            {
                m_isObserving = !m_client.UnRegisterDirectoryObserver(Path, m_guid);
                m_client.RemoveDirectoryObserver(OnDirectoryChanged);
            }
        }

        /// <summary>
        /// Converts the file name filter into regular expression
        /// </summary>
        private void CreateFilter()
        {
            if (!string.IsNullOrEmpty(Filter))
            {
                var filter = Filter.
                    Replace(".", "\\.").
                    Replace("(", "\\(").
                    Replace(")", "\\)").
                    Replace("[", "\\[").
                    Replace("*", "(.*)").
                    Replace("]", "\\]");
                m_filterPattern = new Regex(filter, RegexOptions.Compiled);
            }
        }

        /// <summary>
        /// Gets a unique id for this object
        /// </summary>
        /// <returns>Guid</returns>
        private void GetGuid()
        {
            m_guid = Guid.NewGuid().ToString();
        }

        /// <summary>
        /// Called on every directory change in the remote device
        /// </summary>
        /// <param name="args">Details</param>
        private void OnDirectoryChanged(DirectoryObserverEvent args)
        {
            if (m_isObserving && m_handler != null)
            {
                if (args.Directory.Equals(Path))
                {
                    if (m_filterPattern != null)
                    {
                        if (m_filterPattern.IsMatch(args.FileName))
                        {
                            m_handler(args);
                        }
                    }
                    else
                    {
                        m_handler(args);
                    }
                }
            }
        }
    }
}
