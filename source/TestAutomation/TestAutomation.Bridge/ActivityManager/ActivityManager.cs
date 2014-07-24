using Managed.Adb;
using Managed.Adb.Exceptions;
using Managed.Adb.IO;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;


namespace TestAutomation.Bridge
{
    /// <summary>
    /// Process/activity manager for the remote device
    /// </summary>
    public sealed class ActivityManager //create the python style by using DynamicProxy
    {
        private TABConnection m_tab;

        /// <summary>
        /// Internal class constructor
        /// </summary>
        /// <param name="tab">Device instance for which the Process/activity manager is created</param>
        internal ActivityManager(TABConnection tab)
        {
            m_tab = tab;
        }

        /// <summary>
        /// Kills a process/activity
        /// </summary>
        /// <param name="activity">A process to kill</param>
        public void KillProcess(Activity activity)
        {
            m_tab.ExecuteShellCommand(string.Format("kill {0}", activity.PID), NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
        }

        /// <summary>
        /// Force stops a process/activity
        /// </summary>
        /// <param name="activity">A process to force-stop</param>
        public void ForceStopProcess(Activity activity)
        {
            m_tab.ExecuteShellCommand(string.Format("am force-stop {0}", activity.Name), NullOutputReceiver.Instance, 
                TABInterface.DEFAULT_ADB_TIMEOUT);
        }

        /// <summary>
        /// Checks if a process with given pid is a 
        /// </summary>
        /// <param name="pid"></param>
        /// <returns></returns>
        public bool IsApplication(int pid)
        {
            var command = string.Format("ls -la /proc/{0}/exe", pid);
            var listener = new IsApplicationListener();
            try
            {
                m_tab.ExecuteShellCommand(command, listener, TABInterface.DEFAULT_ADB_TIMEOUT);
                return listener.IsApplication;
            }
            catch 
            {
                return false;
            }

        }

        /// <summary>
        /// Dumps the heap of the activity/process into a file in local file system
        /// </summary>
        /// <param name="process">Activity/process whose heap to dump</param>
        /// <param name="localFilePath">Path to the local file</param>
        internal void DumpHeap(Activity process, string localFilePath)
        {
            if (string.IsNullOrEmpty(localFilePath))
            {
                throw new ArgumentNullException("localFile");
            }

            using (var stream = DumpHeapToStream(process))
            {
                using (var dest = new FileStream(localFilePath, FileMode.OpenOrCreate))
                {
                    stream.CopyTo(dest);
                }
            }
        }

        /// <summary>
        /// Dumps the heap of the activity/process into a stream
        /// </summary>
        /// <param name="process">Activity/process whose heap to dump</param>
        /// <returns>Heap dump stream</returns>
        internal Stream DumpHeapToStream(Activity process)
        {
            if (process == null)
            {
                throw new ArgumentNullException("process");
            }
            if (!process.IsDebuggable)
            {
                throw new Exception(string.Format("{0}({1}) is not debuggable", process.Name, process.PID));
            }

            var filename = process.PID + ".hprof";
            var dumpName = LinuxPath.Combine(m_tab.File.Temp, filename);

            try
            {
                var script = CreateDumpScript(process.PID, dumpName);
                var retVal = m_tab.Shell.ExecuteCommand(script).LastOrDefault();
                bool success;
                if (retVal != null && bool.TryParse(retVal, out success) && success)
                {
                    return m_tab.File.OpenRead(dumpName);
                }
                throw new Exception(string.Format("Failed to create heap dump from {0}({1})", process.Name, process.PID));
            }
            finally
            {
                try
                {
                    m_tab.Shell.BeginExecuteCommand(string.Format("rm {0}", dumpName));
                }
                catch { }
            }
        }

        /// <summary>
        /// Dumps the heap of the activity/process into a file in local file system
        /// </summary>
        /// <param name="processName">Name of the activity/process whose heap to dump</param>
        /// <param name="localFilePath">Path to the local file</param>
        public void DumpHeap(string processName, string localFilePath)
        {
            var process = GetActivityByName(processName);
            DumpHeap(process, localFilePath);
        }

        /// <summary>
        /// Dumps the heap of the activity/process into a file in local file system
        /// </summary>
        /// <param name="pid">Id of the activity/process whose heap to dump</param>
        /// <param name="localFilePath">Path to the local file</param>
        public void DumpHeap(int pid, string localFilePath)
        {
            var process = GetActivityById(pid);
            DumpHeap(process, localFilePath);
        }

        /// <summary>
        /// Dumps the heap of the activity/process into a stream
        /// </summary>
        /// <param name="processName">Name of the activity/process whose heap to dump</param>
        /// <returns>Heap dump stream</returns>
        public Stream DumpHeapToStream(string processName)
        {
            var process = GetActivityByName(processName);
            return DumpHeapToStream(process);
        }

        /// <summary>
        /// Dumps the heap of the activity/process into a stream
        /// </summary>
        /// <param name="pid">Id of the activity/process whose heap to dump</param>
        /// <returns>Heap dump stream</returns>
        public Stream DumpHeapToStream(int pid)
        {
            var process = GetActivityById(pid);
            return DumpHeapToStream(process);
        }

        /// <summary>
        /// Start an activity
        /// </summary>
        /// <param name="packageName">Name of a process/activity to start</param>
        /// <returns>True when successfully started; False otherwise</returns>
        public void StartActivity(string packageName)
        {
            if (string.IsNullOrEmpty(packageName))
            {
                throw new ArgumentNullException("packageName");
            }
            if (packageName.Contains("/"))
            {
                var items = packageName.Split(new char[] { '/' }, StringSplitOptions.RemoveEmptyEntries);
                if (items.Length == 2)
                {
                    StartActivity(items[0], items[1]);
                    return;
                }
            }

            StartActivity(packageName, null);
        }

        /// <summary>
        /// Start an activity
        /// </summary>
        /// <param name="packageName">Name of a process/activity to start</param>
        /// <param name="componentName">Component name</param>
        public void StartActivity(string packageName, string componentName)
        {
            if (string.IsNullOrEmpty(packageName))
            {
                throw new ArgumentNullException("packageName");
            }

            var command = string.Format("am start {0}{1}", componentName != null ? "-n " : "", packageName);
            if (componentName != null)
            {
                componentName = componentName.TrimStart('/', '.');
                command = string.Format("{0}/{1}{2}", command, (componentName.StartsWith(packageName) ? "" : "."), componentName);
            }

            var listener = new ActivityStartListener();
            m_tab.ExecuteShellCommand(command, listener, TABInterface.DEFAULT_ADB_TIMEOUT);
            if (!listener.Success)
            {
                throw new TABException(listener.ErrorMessage);
            }
        }

        /// <summary>
        /// Starts an action
        /// </summary>
        /// <param name="actionName">Full name of the action</param>
        public void StartAction(string actionName)
        {
            StartAction(actionName, null, null);
        }

        /// <summary>
        /// Starts an action
        /// </summary>
        /// <param name="actionName">Full name of the action</param>
        /// <param name="datauri">Data uri</param>
        public void StartAction(string actionName, string datauri)
        {
            StartAction(actionName, datauri, null);
        }

        /// <summary>
        /// Starts an action
        /// </summary>
        /// <param name="actionName">Full name of the action</param>
        /// <param name="datauri">Data uri</param>
        /// <param name="mimeType">Mime type</param>
        public void StartAction(string actionName, string datauri, string mimeType)
        {
            if (string.IsNullOrEmpty(actionName))
            {
                throw new ArgumentNullException("actionName");
            }

            var command = new StringBuilder(string.Format("am start -a {0}"));

            if (!string.IsNullOrEmpty(datauri))
            {
                command.Append(string.Format(" -d \"{0}\"", datauri.Trim().Trim('\"')));

                if (!string.IsNullOrEmpty(mimeType))
                {
                    command.Append(string.Format(" -t {0}", mimeType.Trim()));
                }
            }
            
            var listener = new ActivityStartListener();
            m_tab.ExecuteShellCommand(command.ToString(), listener, TABInterface.DEFAULT_ADB_TIMEOUT);
            if (!listener.Success)
            {
                throw new Exception(listener.ErrorMessage);
            }
        }

        /// <summary>
        /// Checks whether a procss with given name is running
        /// </summary>
        /// <param name="name">Name of the process/activity</param>
        /// <returns>True is process/activity with given name is running; False otherwise</returns>
        public bool ActivityExists(string name)
        {
            var process = GetActivityByName(name);
            return process != null;
        }

        /// <summary>
        /// Returns a process/activity instance by it's name
        /// </summary>
        /// <param name="name">Name of the process/activity</param>
        /// <returns>Process/Activity instance if found; null otherwise</returns>
        public Activity GetActivityByName(string name)
        {
            foreach (var process in GetActivities())
            {
                if (process.Name == name)
                {
                    return process;
                }
            }
            return null;
        }

        /// <summary>
        /// Returns a process/activity instance by ID
        /// </summary>
        /// <param name="pid">Id of a process/activity</param>
        /// <returns>Process/Activity instance if found; null otherwise</returns>
        public Activity GetActivityById(int pid)
        {
            foreach (var process in GetActivities())
            {
                if (process.PID == pid)
                {
                    return process;
                }
            }
            return null;
        }

        /// <summary>
        /// Returns the currently running precesses in the remote device
        /// </summary>
        /// <returns>The currently running precesses in the remote device</returns>
        public List<Activity> GetActivities()
        {
            var debuggableProcesses = m_tab.GetDebuggableProcesses();

            var listener = new ActivityListListener();
            m_tab.ExecuteShellCommand("ps -P", listener, TABInterface.DEFAULT_ADB_TIMEOUT);

            var processes = new List<Activity>();

            foreach (var line in listener.ProcessInfoCollection)
            {
                if (listener.ProcessInfoCollection.IndexOf(line) == 0)
                {
                    continue;
                }

                var items = line.Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries).ToList();

                if (items.Count >= 9)
                {
                    try
                    {
                        var hasBgFginfo = (string.Compare(items[5], "bg") == 0 || string.Compare(items[5], "fg") == 0);

                        string user = items[0];
                        string pid = items[1];
                        string ppid = items[2];
                        string vsize = items[3];
                        string rss = items[4];
                        bool isBackGround = true;
                        string wchan = "";
                        string pc = "";
                        string name = "";

                        if (hasBgFginfo && items.Count > 9)
                        {
                            isBackGround = string.Compare(items[5], "bg") == 0;
                            wchan = items[6];
                            pc = items[7];
                            name = items[9];
                        }
                        else
                        {
                            wchan = items[5];
                            pc = items[6];
                            name = items[8];
                        }

                        if (items.IndexOf(name) < (items.Count - 1))
                        {
                            for (int i = items.IndexOf(name) + 1; i < items.Count; i++)
                            {
                                name += " " + items[i];
                            }
                        }

                        var activity = new Activity(this)
                        {
                            User = user,
                            PID = int.Parse(pid),
                            PPID = int.Parse(ppid),
                            VSIZE = int.Parse(vsize),
                            RSS = int.Parse(rss),
                            IsBackground = isBackGround,
                            WCHAN = long.Parse(wchan, System.Globalization.NumberStyles.HexNumber),
                            PC = long.Parse(pc, System.Globalization.NumberStyles.HexNumber),
                            Name = name
                        };
                        
                        activity.IsDebuggable = debuggableProcesses != null && debuggableProcesses.ToList().Contains(activity.PID);
                        processes.Add(activity);
                    }
                         
                    catch { }
                }
            }

            return processes;
        }
        
        /// <summary>
        /// Creates a sh script which dumps the heap of the process, and waits until the dump is fully written
        /// </summary>
        /// <param name="pid">Id of the process/activity</param>
        /// <param name="dumpLocation">Location of the dump in the device</param>
        /// <returns>The sh script</returns>
        private static string CreateDumpScript(int pid, string dumpLocation)
        {
            var scriptBuilder = new StringBuilder();
            scriptBuilder.Append(string.Format("pid=\"{0}\"; file=\"{1}\";", pid, dumpLocation));
            scriptBuilder.Append(" am dumpheap $pid $file;");
            scriptBuilder.Append(" a=0;");
            scriptBuilder.Append(" while [ true ];");
            scriptBuilder.Append(" do");
            scriptBuilder.Append(" size=$(ls -l $file|grep -o \"[a-z][ \t]*[0-9]\\{{1,\\}}\"|grep -o \"[0-9]\\{{1,\\}}\");");
            scriptBuilder.Append(" echo $size;");
            scriptBuilder.Append(" if [ \"$size\" -eq \"0\" ];");
            scriptBuilder.Append(" then");
            scriptBuilder.Append(" sleep 0.005;");
            scriptBuilder.Append(" else");
            scriptBuilder.Append(" echo true;");
            scriptBuilder.Append(" break;");
            scriptBuilder.Append(" fi;");
            scriptBuilder.Append(" ((a=a+1));");
            scriptBuilder.Append(" if [ a -eq 1000 ];");
            scriptBuilder.Append(" then");
            scriptBuilder.Append(" echo false;");
            scriptBuilder.Append(" break;");
            scriptBuilder.Append(" fi;");
            scriptBuilder.Append(" done;");
            return scriptBuilder.ToString();
        }

        /// <summary>
        /// Class for listening the out put from adb shell ps -P
        /// </summary>
        private class ActivityListListener : MultiLineReceiver
        {
            /// <summary>
            /// Class constructor
            /// </summary>
            public ActivityListListener()
            {
                ProcessInfoCollection = new List<string>();
            }

            /// <summary>
            /// Collection of process information as unparsed strings
            /// </summary>
            public List<string> ProcessInfoCollection { get; private set; }

            /// <summary>
            /// Shell output is redirected here. We parse the process list from an array of lines
            /// </summary>
            /// <param name="data">Lines as string array</param>
            protected override void ProcessNewLines(string[] lines)
            {
                ProcessInfoCollection.AddRange(lines.ToList().ConvertAll<string>(l => l.Trim()));
            }
        }

        /// <summary>
        /// Class for listening the out put from adb shell am start [component]
        /// </summary>
        private class ActivityStartListener : MultiLineReceiver
        {
            /// <summary>
            /// Class constructor
            /// </summary>
            public ActivityStartListener()
            {
                Success = false;
                ErrorMessage = string.Empty;
            }

            /// <summary>
            /// Gets a value indicating whether the activity was successfully started
            /// </summary>
            public bool Success { get; private set; }

            /// <summary>
            /// Gets the error mesage if any
            /// </summary>
            public string ErrorMessage { get; private set; }

            /// <summary>
            /// Shell output is processed here. We check from output whether the process was successfully started.
            /// </summary>
            /// <param name="data">String data</param>
            protected override void ProcessNewLines(string[] lines)
            {
                var result = lines.ToList().ConvertAll<string>(l => l.Trim('\n', '\r', '\t', ' '));
                int? errorline = null;
                result.ForEach(line =>
                    {
                        if (line.ToLower().StartsWith("starting:"))
                        {
                            Success = true;

                        }
                        else if (line.ToLower().StartsWith("error:"))
                        {
                            Success = false;
                            ErrorMessage = line.Substring(6);
                            errorline = result.IndexOf(line);
                        }
                    });
                if (errorline.HasValue && errorline.Value + 1 < (result.Count - 1))
                {
                    for (int i = errorline.Value + 1; i < result.Count; i++)
                    {
                        ErrorMessage += Environment.NewLine + result[i];
                    }
                }
            }
        }

        /// <summary>
        /// Class for listening the output from ls -la for the process directory
        /// </summary>
        private class IsApplicationListener : MultiLineReceiver
        {
            private const string APPLICATION_DIRECTORY = "/system/bin/app_process";

            /// <summary>
            /// Called for output data lines
            /// </summary>
            /// <param name="lines"></param>
            protected override void ProcessNewLines(string[] lines)
            {
                if (!IsApplication)
                {
                    IsApplication = lines.ToList().Exists(l => l.Trim(' ', '\t', '\r', '\n').EndsWith(APPLICATION_DIRECTORY));
                }
            }

            /// <summary>
            /// Gets a value indicating whether the process is an application process
            /// </summary>
            public bool IsApplication { get; private set; }
        }
    }
}
