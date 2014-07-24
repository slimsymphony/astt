using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using TestAutomation.Bridge.ScriptingTools;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Class for presenting a remote process/activity
    /// </summary>
    public sealed class Activity : PythonCallable
    {
        private const int DEFAULT_RESTART_TIMEOUT = 5000;

        private WeakReference m_wam;

        private string[] m_notApp = { "zygote", "system_server" };

        /// <summary>
        /// Internal class constructor
        /// </summary>
        /// <param name="am">A process/activity manager instance</param>
        internal Activity(ActivityManager am)
        {
            m_wam = new WeakReference(am, false);
        }

        /// <summary>
        /// User of the process/activity
        /// </summary>
        public string User { get; internal set; }

        /// <summary>
        /// ID of the process/activity
        /// </summary>
        public int PID { get; internal set; }

        /// <summary>
        /// PPID of the process/activity
        /// </summary>
        public int PPID { get; internal set; }

        /// <summary>
        /// VSIZE of the process/activity
        /// </summary>
        public int VSIZE { get; internal set; }

        /// <summary>
        /// RSS of the process/activity
        /// </summary>
        public int RSS { get; internal set; }

        /// <summary>
        /// Value indicating whether the process/activity runs in background 
        /// </summary>
        public bool IsBackground { get; internal set; }

        /// <summary>
        /// WCHAN of the process/activity
        /// </summary>
        public long WCHAN { get; internal set; }

        /// <summary>
        /// PC of the process/activity
        /// </summary>
        public long PC { get; internal set; }

        /// <summary>
        /// Name of the process/activity
        /// </summary>
        public string Name { get; internal set; }

        /// <summary>
        /// Gets a value indicaing whether the process is an application process
        /// </summary>
        /// <returns></returns>
        public bool IsApplication
        {
            get
            {
                return !m_notApp.Any((na) => na == Name) && (m_wam.Target as ActivityManager).IsApplication(PID);
            }
        }

        /// <summary>
        /// Gets a value indicating whether the process is debuggable
        /// </summary>
        public bool IsDebuggable { get; internal set; }

        /// <summary>
        /// Kills a process/activity
        /// </summary>
        public void Kill()
        {
            (m_wam.Target as ActivityManager).KillProcess(this);
        }

        /// <summary>
        /// Force-stops a process/activity
        /// </summary>
        public void ForceStop()
        {
            (m_wam.Target as ActivityManager).ForceStopProcess(this);
        }

        /// <summary>
        /// Dumps the heap of the activity/process to a file in local file system
        /// </summary>
        /// <param name="localFilePath">Path of the local file</param>
        public void DumpHeap(string localFilePath)
        {
            (m_wam.Target as ActivityManager).DumpHeap(this, localFilePath);
        }

        /// <summary>
        /// Dumps the heap of the activity/process into a stream
        /// </summary>
        /// <returns>Heap dump stream</returns>
        public Stream DumpHeapToStream()
        {
            return (m_wam.Target as ActivityManager).DumpHeapToStream(this);
        }

        /// <summary>
        /// Restarts the activity/process
        /// </summary>
        public void Restart()
        {
            Restart(false, DEFAULT_RESTART_TIMEOUT);
        }

        /// <summary>
        /// Restarts the activity/process
        /// </summary>
        /// <param name="timeout">Timeout for the restart sequence</param>
        public void Restart(int timeout)
        {
            Restart(false, timeout);
        }

        /// <summary>
        /// Restarts the activity/process
        /// </summary>
        /// <param name="force">Shut down the process by "kill"</param>
        public void Restart(bool force)
        {
            Restart(force, DEFAULT_RESTART_TIMEOUT);
        }

        /// <summary>
        /// Restarts the activity/process
        /// </summary>
        /// <param name="force">Shut down the process by "kill"</param>
        /// <param name="timeout">Timeout for the restart sequence</param>
        public void Restart(bool force, int timeout)
        {
            if (!IsApplication)
            {
                throw new Exception("Can't restart a process which is not an application");
            }

            if (timeout < 0)
            {
                timeout = 0;
            }

            var am = m_wam.Target as ActivityManager;

            if (force)
            {
                Kill();
            }
            else
            {
                ForceStop();
            }

            var start = DateTime.Now;
            var killed = false;
            var timeLeft = 0.0;

            while (true)
            {
                var process = am.GetActivityByName(Name);

                var timeUsed = DateTime.Now.Subtract(start).TotalMilliseconds;

                if (process != null)
                {
                    if (timeUsed < timeout)
                    {
                        Thread.Sleep(200);
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    timeLeft = timeout - timeUsed;
                    killed = true;
                    break;
                }
            }

            if (!killed)
            {
                throw new Exception(string.Format("Failed to kill the application by using '{0}' within the given timeout: {1}",
                    (force ? "kill" : "forceStop"), timeout));
            }

            am.StartActivity(Name);

            var started = false;
            start = DateTime.Now;

            while (true)
            {
                var process = am.GetActivityByName(Name);
                var timeUsed = DateTime.Now.Subtract(start).TotalMilliseconds;
                if (process == null)
                {
                    if (timeUsed < timeLeft)
                    {
                        Thread.Sleep(200);
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    Name = process.Name;
                    PID = process.PID;
                    PPID = process.PPID;
                    User = process.User;
                    VSIZE = process.VSIZE;
                    WCHAN = process.WCHAN;
                    RSS = process.RSS;
                    PC = process.PC;
                    IsDebuggable = process.IsDebuggable;
                    IsBackground = process.IsBackground;
                    started = true;
                    break;
                }
            }

            if (!started)
            {
                throw new Exception(string.Format("Failed to start the application within the given timeout: {0}",
                    timeout));
            }
        }

        /// <summary>
        /// Gets the name of the process/activity
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return Name;
        }
    }
}
