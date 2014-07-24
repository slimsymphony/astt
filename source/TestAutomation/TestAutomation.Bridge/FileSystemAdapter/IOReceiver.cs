using Managed.Adb;
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
    internal sealed class IOReceiver : MultiLineReceiver
    {
        /// <summary>
        /// 
        /// </summary>
        internal bool Success { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        internal bool FileNotFound { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        internal bool DirectoryNotFound { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        internal bool ReadDenied { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        internal bool WriteDenied { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        internal string Message { get; private set; }

        /// <summary>
        /// Processes the new lines.
        /// </summary>
        /// <param name="lines">The lines.</param>
        protected override void ProcessNewLines(string[] lines)
        {
            if (lines != null && lines.Length > 0)
            {
                var items = lines[0].Trim().Split(new char[] { ':' }, StringSplitOptions.RemoveEmptyEntries);
                if (items.Length > 0)
                {
                    var line = items[0].ToLower();

                    if (string.Compare(line, "true") == 0)
                    {
                        Success = true;
                    }
                    else if (string.Compare(line, "read_denied") == 0)
                    {
                        ReadDenied = true;
                    }
                    else if (string.Compare(line, "write_denied") == 0)
                    {
                        WriteDenied = true;
                    }
                    else if (string.Compare(line, "file_not_found") == 0)
                    {
                        FileNotFound = true;
                    }
                    else if (string.Compare(line, "directory_not_found") == 0)
                    {
                        DirectoryNotFound = true;
                    }

                    if (items.Length > 1)
                    {
                        Message = items[1];
                    }
                }
            }
        }
    }
}
