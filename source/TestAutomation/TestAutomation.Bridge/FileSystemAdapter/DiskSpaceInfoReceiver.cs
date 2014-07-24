using Managed.Adb;
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
    /// 
    /// </summary>
    internal sealed class DiskSpaceInfo
    {
        /// <summary>
        /// 
        /// </summary>
        internal string Name { get; set; }

        /// <summary>
        /// 
        /// </summary>
        internal double Size { get; set; }

        /// <summary>
        /// 
        /// </summary>
        internal double Free { get; set; }

        /// <summary>
        /// 
        /// </summary>
        internal double Used { get; set; }

        /// <summary>
        /// 
        /// </summary>
        internal double BlkSize { get; set; }
    }

    /// <summary>
    /// 
    /// </summary>
    internal sealed class DiskSpaceInfoReceiver : MultiLineReceiver
    {
        private static Regex m_matcher = new Regex(@"([^ \t]+)[ \t]+([0-9\.]+)([MGK]{1})[ \t]+([0-9\.]+)([MGK]{1})[ \t]+([0-9\.]+)([MGK]{1})[ \t]+([0-9\.]+)", RegexOptions.Compiled | RegexOptions.IgnoreCase);

        /// <summary>
        /// 
        /// </summary>
        internal DiskSpaceInfoReceiver()
        {
            DiskSpace = new List<DiskSpaceInfo>();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="lines"></param>
        protected override void ProcessNewLines(string[] lines)
        {
            if (lines != null && lines.Length > 0)
            {
                foreach (var line in lines)
                {
                    var match = m_matcher.Match(line);

                    if (match.Success)
                    {
                        var disk = new DiskSpaceInfo();
                        disk.Name = match.Groups[1].Value;

                        for (int i = 2; i <= 8; i += 2)
                        {
                            double parsed;
                            if (!double.TryParse(match.Groups[i].Value, NumberStyles.Any, CultureInfo.InvariantCulture, out parsed)) continue;
                            if (i < 8)
                            {
                                switch (match.Groups[i + 1].Value.ToLower()[0])
                                {
                                    case 'k':
                                        parsed *= 1024;
                                        break;
                                    case 'm':
                                        parsed *= 1024 * 1024;
                                        break;
                                    case 'g':
                                        parsed *= 1024 * 1024 * 1024;
                                        break;
                                    default:
                                        break;
                                }
                            }
                            switch (i)
                            {
                                case 2:
                                    disk.Size = parsed;
                                    break;
                                case 4:
                                    disk.Used = parsed;
                                    break;
                                case 6:
                                    disk.Free = parsed;
                                    break;
                                case 8:
                                    disk.BlkSize = parsed;
                                    break;
                                default:
                                    break;
                            }
                        }

                        DiskSpace.Add(disk);
                    }
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        internal List<DiskSpaceInfo> DiskSpace { get; private set; }
    }
}
