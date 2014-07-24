using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Managed.Adb.Logs
{
    /// <summary>
    /// 
    /// </summary>
    public sealed class LogEntry
    {
        public int Length { get; set; }
        public int ProcessId { get; set; }
        public int ThreadId { get; set; }
        public int Seconds { get; set; }
        public int NanoSeconds { get; set; }
        public byte[] Data { get; set; }
    }
}
