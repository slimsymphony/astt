using Managed.Adb;
using Managed.Adb.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// 
    /// </summary>
    internal sealed class LsReceiver : MultiLineReceiver
    {
        private string m_fullName;
        private bool m_isDirectory;
        private TimeSpan m_timeZoneOffset;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="fullName"></param>
        /// <param name="isDirectory"></param>
        internal LsReceiver(string fullName, bool isDirectory) :
            this(fullName, isDirectory, TimeSpan.Zero) { }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="fullName"></param>
        /// <param name="isDirectory"></param>
        /// <param name="timeZoneOffset"></param>
        internal LsReceiver(string fullName, bool isDirectory, TimeSpan timeZoneOffset)
        {
            m_fullName = fullName;
            m_isDirectory = isDirectory;
            m_timeZoneOffset = timeZoneOffset;//.Negate();
            Entries = new List<RemoteFileInfo>();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="lines"></param>
        protected override void ProcessNewLines(string[] lines)
        {
            if (lines != null && lines.Length == 1)
            {
                var line = lines[0].Trim().ToUpper();

                if (string.Compare(line, "NO_ACCESS", false) == 0)
                {
                    PermissionDenied = true;
                    return;
                }
                else if (string.Compare(line, "NOT_FOUND", false) == 0)
                {
                    DirectoryNotFound = true;
                    return;
                }
                else if (string.Compare(line, "LINK", false) == 0)
                {
                    IsLink = true;
                    return;
                }
            }

            foreach (var entry in lines)
            {
                var info = RemoteFileInfo.Parse(entry, (m_isDirectory ? m_fullName.TrimEnd('/') : LinuxPath.GetDirectoryName(m_fullName)), m_timeZoneOffset);
                if (info != null)
                {
                    Entries.Add(info);
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        internal List<RemoteFileInfo> Entries { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        internal bool IsLink { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        internal bool PermissionDenied { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        internal bool DirectoryNotFound { get; private set; }
    }
}
