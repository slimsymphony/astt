using Managed.Adb;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Provdes the functionality to calculate md5 hash a file in local machine and in the remote devices
    /// </summary>
    internal static class MD5
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="localFile"></param>
        /// <returns></returns>
        internal static string CalculateLocal(string localFile)
        {
            using (var md5 = System.Security.Cryptography.MD5.Create())
            {
                using (var inStream = File.OpenRead(localFile))
                {
                    var hash = md5.ComputeHash(inStream);
                    var builder = new StringBuilder();
                    for (int i = 0; i < hash.Length; i++)
                    {
                        builder.Append(hash[i].ToString("X2"));
                    }
                    return builder.ToString().ToLower();
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="tab"></param>
        /// <param name="remoteFile"></param>
        /// <returns></returns>
        internal static string CalculateRemote(TABConnection tab, string remoteFile)
        {
            if (tab.IsOnline)
            {
                var receiver = new MD5Receiver();
                tab.ExecuteShellCommand(string.Format("md5 {0}", remoteFile), receiver, TABInterface.DEFAULT_ADB_TIMEOUT * 2);
                return receiver.Hash;
            }
            return null;
        }

        /// <summary>
        /// 
        /// </summary>
        private class MD5Receiver : MultiLineReceiver
        {
            private static Regex m_matcher = new Regex("([A-Fa-f0-9]+)[ \t]+.+", RegexOptions.Compiled | RegexOptions.IgnoreCase);

            protected override void ProcessNewLines(string[] lines)
            {
                if (lines != null && lines.Length > 0)
                {
                    var m = m_matcher.Match(lines[0]);
                    if (m.Success)
                    {
                        Hash = m.Groups[1].Value.Trim().ToLower();
                    }
                }
            }

            public string Hash { get; private set; }
        }
    }
}
