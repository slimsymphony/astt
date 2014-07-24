using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Managed.Adb
{
    /// <summary>
    /// 
    /// </summary>
    internal static class DdmPreferences
    {
        //Default value for thread update flag upon client connection.
        public const bool DEFAULT_INITIAL_THREAD_UPDATE = false;
       
        //Default value for heap update flag upon client connection.
        public const bool DEFAULT_INITIAL_HEAP_UPDATE = false;
        
        //Default value for the selected client debug port
        public const int DEFAULT_SELECTED_DEBUG_PORT = 8700;
        
        //Default value for the debug port base
        public const int DEFAULT_DEBUG_PORT_BASE = 8600;
        
        //Default value for the logcat {@link LogLevel}
        public static readonly LogLevel.LogLevelInfo DEFAULT_LOG_LEVEL = Managed.Adb.LogLevel.Error;
        
        //Default timeout values for adb connection (milliseconds)
        public const int DEFAULT_TIMEOUT = 10000; // standard delay, in ms
        public const int LONG_TIMEOUT = 30000; // standard delay, in ms

        /// <summary>
        /// 
        /// </summary>
        private static int _selectedDebugPort;
        
        /// <summary>
        /// 
        /// </summary>
        private static LogLevel.LogLevelInfo _logLevel;

        /// <summary>
        /// 
        /// </summary>
        static DdmPreferences()
        {
            Timeout = DEFAULT_TIMEOUT;
            LongTimeout = LONG_TIMEOUT;
            LogLevel = DEFAULT_LOG_LEVEL;
            SelectedDebugPort = DEFAULT_SELECTED_DEBUG_PORT;
            DebugPortBase = DEFAULT_DEBUG_PORT_BASE;
            InitialThreadUpdate = DEFAULT_INITIAL_THREAD_UPDATE;
            InitialHeapUpdate = DEFAULT_INITIAL_HEAP_UPDATE;
        }

        /// <summary>
        /// 
        /// </summary>
        public static int Timeout { get; set; }
        public static int LongTimeout { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public static LogLevel.LogLevelInfo LogLevel
        {
            get
            {
                return _logLevel;
            }
            set
            {
                _logLevel = value;
                Log.Level = value;
            }
        }
        
        /// <summary>
        /// 
        /// </summary>
        public static int DebugPortBase { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public static int SelectedDebugPort
        {
            get
            {
                return _selectedDebugPort;
            }
            set
            {
                _selectedDebugPort = value;

                MonitorThread monitorThread = MonitorThread.Instance;
                if (monitorThread != null)
                {
                    monitorThread.SetDebugSelectedPort(value);
                }
            }
        }
        
        /// <summary>
        /// 
        /// </summary>
        public static bool InitialThreadUpdate { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public static bool InitialHeapUpdate { get; set; }
    }
}
