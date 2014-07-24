using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Managed.Adb.IO;
using Managed.Adb.MoreLinq;
using Managed.Adb.Exceptions;
using System.Text.RegularExpressions;

namespace Managed.Adb
{
	/// <summary>
	/// A class to help with working with BusyBox
	/// </summary>
	public class BusyBox
    {
		/// <summary>
		/// 
		/// </summary>
		private const string BUSYBOX_BIN = "/data/local/bin/";
		/// <summary>
		/// 
		/// </summary>
		private const string BUSYBOX_COMMAND = "busybox";

		/// <summary>
		/// Initializes a new instance of the <see cref="BusyBox"/> class.
		/// </summary>
		/// <param name="device">The device.</param>
		internal BusyBox(Device device)
        {
			Device = device;
			Version = new System.Version("0.0.0.0");
			Commands = new List<string>();
			CheckForBusyBox();

		}

		/// <summary>
		/// Attempts to install on the device
		/// </summary>
		/// <param name="busybox">The path to the busybox binary to install.</param>
		/// <returns><c>true</c>, if successful; otherwise, <c>false</c></returns>
		public bool Install(string busybox)
        {
			busybox.ThrowIfNullOrWhiteSpace("busybox");

			FileEntry bb = null;

			try
            {
                Device.ExecuteShellCommand(BUSYBOX_COMMAND, NullOutputReceiver.Instance, DdmPreferences.Timeout);
				return true;
			}
            catch
            {
				// we are just checking if it is already installed so we really expect it to wind up here.
			}

			try
            {
				MountPoint mp = Device.MountPoints["/data"];
				bool isRO = mp.IsReadOnly;
				Device.RemountMountPoint(Device.MountPoints["/data"], false);

				FileEntry path = null;
				try
                {
					path = Device.FileListingService.FindFileEntry(BUSYBOX_BIN);
				}
                catch(FileNotFoundException)
                {
					// path doesn't exist, so we make it.
					Device.FileSystem.MakeDirectory(BUSYBOX_BIN);
					// attempt to get the FileEntry after the directory has been made
					path = Device.FileListingService.FindFileEntry(BUSYBOX_BIN);
				}

				Device.FileSystem.Chmod(path.FullPath, "0755");

				string bbPath = LinuxPath.Combine(path.FullPath, BUSYBOX_COMMAND);

				Device.FileSystem.Copy(busybox, bbPath);

				bb = Device.FileListingService.FindFileEntry(bbPath);
				Device.FileSystem.Chmod(bb.FullPath, "0755");

                Device.ExecuteShellCommand("{0}/busybox --install {0}", new ConsoleOutputReceiver(), DdmPreferences.Timeout, path.FullPath);

				// check if this path exists in the path already
				if (Device.EnvironmentVariables.ContainsKey("PATH"))
                {
					var paths = Device.EnvironmentVariables["PATH"].Split(':');
					var found = paths.Where(p => string.Compare(p, BUSYBOX_BIN, false) == 0).Count() > 0;

					// we didnt find it, so add it.
					if (!found)
                    {
						// this doesn't seem to actually work
                        Device.ExecuteShellCommand(@"echo \ Mad Bee buxybox >> /init.rc", NullOutputReceiver.Instance, DdmPreferences.Timeout);
						Device.ExecuteShellCommand(@"echo export PATH={0}:\$PATH >> /init.rc", NullOutputReceiver.Instance, DdmPreferences.Timeout, BUSYBOX_BIN);
					}
				}


				if (mp.IsReadOnly != isRO)
                {
					// Put it back, if we changed it
					Device.RemountMountPoint(mp, isRO);
				}

                Device.ExecuteShellCommand("sync", NullOutputReceiver.Instance, DdmPreferences.Timeout);
			}
            catch(Exception)
            {
				throw;
			}

			CheckForBusyBox();
			return true;
		}

		/// <summary>
		/// Checks for busy box.
		/// </summary>
		private void CheckForBusyBox()
        {
			if (Device.IsOnline)
            {
                try
                {
                    Commands.Clear();
                    Device.ExecuteShellCommand(BUSYBOX_COMMAND, new BusyBoxCommandsReceiver(this), DdmPreferences.Timeout);
                    Available = true;
                }
                catch (FileNotFoundException)
                {
                    Available = false;
                }
                catch (AdbException)
                {
                    Available = false;
                }
			}
            else
            {
				Available = false;
			}
		}

		/// <summary>
		/// Executes a busybox command on the device
		/// </summary>
		/// <param name="command"></param>
		/// <param name="receiver"></param>
		/// <param name="commandArgs"></param>
		public void ExecuteShellCommand(string command, IShellOutputReceiver receiver, params object[] commandArgs)
        {
			command.ThrowIfNullOrWhiteSpace("command");
			var cmd = string.Format("{0} {1}", BUSYBOX_COMMAND, string.Format(command, commandArgs));
			Log.d("executing: {0}", cmd);
            AdbHelper.Instance.ExecuteRemoteCommand(AndroidDebugBridge.SocketAddress, cmd, this.Device, receiver);
		}

        /// <summary>
        /// Executes a busybox command on the device
        /// </summary>
        /// <param name="command"></param>
        /// <param name="receiver"></param>
        /// <param name="timeout"></param>
        /// <param name="commandArgs"></param>        
        public void ExecuteShellCommand(string command, IShellOutputReceiver receiver, int timeout, params object[] commandArgs)
        {
            command.ThrowIfNullOrWhiteSpace("command");
            var cmd = string.Format("{0} {1}", BUSYBOX_COMMAND, string.Format(command, commandArgs));
            Log.d("executing: {0}", cmd);
            AdbHelper.Instance.ExecuteRemoteCommand(AndroidDebugBridge.SocketAddress, cmd, this.Device, receiver, timeout);
        }

		/// <summary>
		/// Executes a busybox command on the device as root
		/// </summary>
		/// <param name="command">The command.</param>
		/// <param name="receiver">The receiver.</param>
		/// <param name="commandArgs">The command args.</param>
		public void ExecuteRootShellCommand(string command, IShellOutputReceiver receiver, params object[] commandArgs)
        {
			command.ThrowIfNullOrWhiteSpace("command");
			var cmd = string.Format("{0} {1}", BUSYBOX_COMMAND, string.Format(command, commandArgs));
			Log.d("executing (su): {0}", cmd);
            AdbHelper.Instance.ExecuteRemoteRootCommand(AndroidDebugBridge.SocketAddress, cmd, this.Device, receiver);
		}

		/// <summary>
		/// Executes a busybox command on the device as root
		/// </summary>
		/// <param name="command">The command.</param>
		/// <param name="receiver">The receiver.</param>
        /// <param name="timeout"></param>
		/// <param name="commandArgs">The command args.</param>
		public void ExecuteRootShellCommand(string command, IShellOutputReceiver receiver, int timeout, params object[] commandArgs)
        {
			command.ThrowIfNullOrWhiteSpace("command");
			var cmd = string.Format("{0} {1}", BUSYBOX_COMMAND, string.Format(command, commandArgs));
			Log.d("executing (su): {0}", cmd);
            AdbHelper.Instance.ExecuteRemoteRootCommand(AndroidDebugBridge.SocketAddress, cmd, this.Device, receiver, timeout);
		}

		/// <summary>
		/// Gets or sets the device.
		/// </summary>
		/// <value>
		/// The device.
		/// </value>
		private Device Device { get; set; }
		/// <summary>
		/// Gets if busybox is available on this device.
		/// </summary>
		public bool Available { get; private set; }
		/// <summary>
		/// Gets the version of busybox
		/// </summary>
		public Version Version { get; internal set; }
		/// <summary>
		/// Gets a collection of the supported commands
		/// </summary>
		public List<String> Commands { get; private set; }

		/// <summary>
		/// Gets if the specified command name is supported by this version of busybox
		/// </summary>
		/// <param name="command">The command name to check</param>
		/// <returns><c>true</c>, if supported; otherwise, <c>false</c>.</returns>
		public bool Supports(string command)
        {
			command.ThrowIfNullOrWhiteSpace("command");

			if (Available && (Commands == null || Commands.Count == 0))
            {
				CheckForBusyBox();
			}

			return Commands.Where(c => string.Compare(c,command,false) == 0).FirstOrDefault() != null;
		}

		/// <summary>
		/// 
		/// </summary>
		private class BusyBoxCommandsReceiver : MultiLineReceiver
        {
			/// <summary>
			/// The busybox version regex pattern
			/// </summary>
			private const string BB_VERSION_PATTERN = @"^BusyBox\sv(\d{1,}\.\d{1,}\.\d{1,})";
			/// <summary>
			/// the busybox commands list regex pattern
			/// </summary>
			private const string BB_FUNCTIONS_PATTERN = @"(?:([\[a-z0-9]+)(?:,\s*))";

			public BusyBoxCommandsReceiver(BusyBox bb) : base()
            {
				TrimLines = true;
				BusyBox = bb;
			}

			/// <summary>
			/// Gets or sets the busy box.
			/// </summary>
			/// <value>
			/// The busy box.
			/// </value>
			private BusyBox BusyBox { get; set; }

			/// <summary>
			/// Processes the new lines.
			/// </summary>
			/// <param name="lines">The lines.</param>
			/// <workitem id="16000">Issues w/ BusyBox.cs/ProcessNewLines()</workitem>
			protected override void ProcessNewLines(string[] lines)
            {
				Match match = null;
				int state = 0;
				foreach (var line in lines)
                {
					if (line.IsNullOrWhiteSpace())
                    {
						continue;
					}
					switch(state)
                    {
						case 0:
							match = line.Match(BB_VERSION_PATTERN, RegexOptions.Compiled | RegexOptions.IgnoreCase);
							if (match.Success)
                            {
								BusyBox.Version = new Version(match.Groups[1].Value);
								state = 1;
								continue;
							}
							break;
						case 1:
							if (line.Contains("defined functions"))
                            {
								state = 2;
							}
							break;
						case 2:
							match = line.Trim().Match(BB_FUNCTIONS_PATTERN, RegexOptions.Compiled);
							while(match.Success)
                            {
								BusyBox.Commands.Add(match.Groups[1].Value.Trim());
								match = match.NextMatch();
							}
							break;
					}
				}
			}
		}
	}
}
