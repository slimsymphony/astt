﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using Managed.Adb.MoreLinq;

namespace Managed.Adb
{
    /// <summary>
    /// A dynamic mount point receiver.
    /// </summary>
    /// <remarks>Works on busybox and non-busybox devices</remarks>
    public class MountPointReceiver : MultiLineReceiver
    {
        /// <summary>
        /// The mount parsing pattern.
        /// </summary>
        private const string RE_MOUNTPOINT_PATTERN = @"^([\S]+)\s+([\S]+)\s+([\S]+)\s+(r[wo]).*$";
        
        /// <summary>
        /// The mount command
        /// </summary>
        public const string MOUNT_COMMAND = "cat /proc/mounts";

        /// <summary>
        /// Initializes a new instance of the <see cref="MountPointReceiver"/> class.
        /// </summary>
        /// <param name="device">The device.</param>
        public MountPointReceiver(Device device)
        {
            Device = device;
        }

        /// <summary>
        /// Processes the new lines.
        /// </summary>
        /// <param name="lines">The lines.</param>
        /// <workitem id="16001">Bug w/ MountPointReceiver.cs/ProcessNewLines()</workitem>
        protected override void ProcessNewLines(string[] lines)
        {
            Device.MountPoints.Clear();

            lines.ForEach(line =>
            {
                var m = line.Match(RE_MOUNTPOINT_PATTERN, RegexOptions.Compiled | RegexOptions.IgnoreCase | RegexOptions.IgnorePatternWhitespace);
                if (m.Success)
                {
                    string block = m.Groups[1].Value.Trim().Replace("//", "/");
                    string name = m.Groups[2].Value.Trim();
                    string fs = m.Groups[3].Value.Trim();
                    bool ro = string.Compare("ro", m.Groups[4].Value.Trim(), false) == 0;
                    MountPoint mnt = new MountPoint(block, name, fs, ro);
                    string key = name.Substring(1);
                    // currently does not support multiple mounts to the same location...
                    if (!Device.MountPoints.ContainsKey(name))
                    {
                        Device.MountPoints.Add(name, mnt);
                    }
                }
            });
        }

        /// <summary>
        /// Finishes the receiver
        /// </summary>
        protected override void Done()
        {
            Device.OnBuildInfoChanged(EventArgs.Empty);
            base.Done();
        }

        /// <summary>
        /// Gets or sets the device.
        /// </summary>
        /// <value>
        /// The device.
        /// </value>
        private Device Device { get; set; }
    }
}
