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
    internal sealed class LinkResolverReceiver : MultiLineReceiver
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="toResolve"></param>
        internal LinkResolverReceiver(string toResolve)
        {
            RealPath = toResolve;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="lines"></param>
        protected override void ProcessNewLines(string[] lines)
        {
            if (lines != null && lines.Length > 0 && !lines.Any(line => line.Contains("No such file or directory")))
            {
                RealPath = lines[0].TrimEnd();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        internal string RealPath { get; private set; }
    }
}
