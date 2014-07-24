using Managed.Adb;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Class for providing ip helper functions
    /// </summary>
    public sealed class IpHelper
    {
        private const string NETSTAT_CMD = "netstat";

        /// <summary>
        /// Gets a list of reserved ports in the remote device
        /// </summary>
        /// <param name="device">The device from which to request</param>
        /// <returns>List of reserved ports</returns>
        public static List<int> GetReservedRemotePorts(Device device)
        {
            var listener = new ReservedPortListener();
            device.ExecuteShellCommand(NETSTAT_CMD, listener, TABInterface.DEFAULT_ADB_TIMEOUT);
            return listener.ReserverPorts;
        }

        /// <summary>
        /// Class for listening output from adb shell netstats
        /// </summary>
        private class ReservedPortListener : MultiLineReceiver
        {
            private static Regex m_ipRegex = new Regex(@"(:*[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}):([0-9]+)", RegexOptions.Compiled);

            /// <summary>
            /// Class constructor
            /// </summary>
            public ReservedPortListener()
            {
                ReserverPorts = new List<int>();
            }

            /// <summary>
            /// The ports that are in use in the remote system
            /// </summary>
            public List<int> ReserverPorts { get; private set; }

            /// <summary>
            /// Shell output is processed here. We parse the reserved ports from raw data
            /// </summary>
            /// <param name="lines">String data</param>
            protected override void ProcessNewLines(string[] lines)
            {
                lines.ToList().ForEach(line =>
                {
                    var matches = m_ipRegex.Matches(line);

                    if (matches != null && matches.Count > 0)
                    {
                        foreach (Match match in matches)
                        {
                            var port = int.Parse(match.Groups[2].Value);
                            if (!ReserverPorts.Contains(port))
                            {
                                ReserverPorts.Add(port);
                            }
                        }
                    }
                });
            }
        }
    }
}
