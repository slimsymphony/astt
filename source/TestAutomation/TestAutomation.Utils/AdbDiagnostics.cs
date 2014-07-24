using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;


namespace TestAutomation.Utils
{
    /// <summary>
    /// 
    /// </summary>
    public static class AdbDiagnostics
    {
        /// <summary>
        /// 
        /// </summary>
        public const int DEFAULT_ADB_PORT = 5037;

        /// <summary>
        /// 
        /// </summary>
        private const string DEFAULT_PROCESS_NAME = "adb";

        /// <summary>
        /// 
        /// </summary>
        private static string[] m_adbFiles = 
        { 
            "adb.exe",
            "AdbWinApi.dll",
            "AdbWinUsbApi.dll"
        };

        ///// <summary>
        ///// 
        ///// </summary>
        //static AdbDiagnostics()
        //{
        //    ExtractAdb();
        //}

        ///// <summary>
        ///// 
        ///// </summary>
        //private static void ExtractAdb()
        //{
        //    var directory = Path.GetDirectoryName(DefaultAdbLocation);

        //    if (!Directory.Exists(directory))
        //    {
        //        Directory.CreateDirectory(directory);
        //    }
        //    m_adbFiles.ToList().ForEach(file =>
        //        {
        //            var lib = Path.Combine(directory, file);
        //            if (!File.Exists(lib))
        //            {
        //                typeof(AdbDiagnostics).Assembly.ExtractManifestResourceZipEntry(
        //                    "adb.zip",
        //                    directory, 
        //                    file);
        //            }
        //        });

        //}

        /// <summary>
        /// 
        /// </summary>
        public static string DefaultAdbLocation
        {
            get
            {
                var root = Path.GetDirectoryName(typeof(AdbDiagnostics).Assembly.Location);
                return Path.Combine(root, "adb\\adb.exe");
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public static bool IsRunning
        {
            get
            {
                return Process.GetProcessesByName(DEFAULT_PROCESS_NAME).Any(p => p.ListensTcp(DEFAULT_ADB_PORT));
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public static Process Process
        {
            get
            {
                return Process.GetProcessesByName(DEFAULT_PROCESS_NAME).ToList().Find(p => p.ListensTcp(DEFAULT_ADB_PORT));
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public static TimeSpan? UpTime
        {
            get
            {
                //Only in admin mode; otherwise Win32Exception is thrown 
                try
                {
                    var process = Process.GetProcessesByName(DEFAULT_PROCESS_NAME).ToList().Find(p => p.ListensTcp(DEFAULT_ADB_PORT));
                    if (process != null)
                    {
                        return DateTime.Now.Subtract(process.StartTime);
                    }
                }
                catch { }
                return null;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public static int[] GetPortForwardings()
        {
            List<int> ports = null;
            if (Process.GetProcessesByName(DEFAULT_PROCESS_NAME).ToList().Find(p => p.ListensTcp(out ports)) != null)
            {
                return ports.FindAll(port => port != DEFAULT_ADB_PORT).ToArray();
            }
            return new int[0];
        }

        /// <summary>
        /// 
        /// </summary>
        public static string ExecutingAdbLocation
        {
            get
            {
                //Only in admin mode; otherwise Win32Exception is thrown 
                try
                {
                    var process = Process.GetProcessesByName(DEFAULT_PROCESS_NAME).ToList().Find(p => p.MainModule != null);
                    if (process != null)
                    {
                        return process.MainModule.FileName;
                    }
                }
                catch { }
                return null;
            }
        }
    }

    /// <summary>
    /// 
    /// </summary>
    public static class Extensions
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="proc"></param>
        /// <returns></returns>
        public static bool ListensAnyTcp(this Process proc)
        {
            List<int> temp;
            return ListensTcp(proc, out temp);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="proc"></param>
        /// <param name="port"></param>
        /// <returns></returns>
        public static bool ListensTcp(this Process proc, int port)
        {
            List<int> ports;
            if (ListensTcp(proc, out ports))
            {
                return ports.Contains(port);
            }
            return false;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="proc"></param>
        /// <param name="ports"></param>
        /// <returns></returns>
        public static bool ListensTcp(this Process proc, out List<int> ports)
        {
            ports = TestAutomation.Utils.ManagedIpHelper.GetExtendedTcpTable(false).
                ToList().FindAll(tcp => tcp.ProcessId == proc.Id &&
                    tcp.State == System.Net.NetworkInformation.TcpState.Listen).
                    ConvertAll(tcp => tcp.LocalEndPoint.Port);
            return ports.Count > 0;
        }
    }
}
