using Managed.Adb;
using Managed.Adb.IO;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using TestAutomation.Client;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Class for interacting with remote shell
    /// </summary>
    public sealed class Shell //create the python style by using DynamicProxy
    {
        private TABConnection m_tab;

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="tab">TAB/Device connection</param>
        internal Shell(TABConnection tab)
        {
            m_tab = tab;
        }

        /// <summary>
        /// Executes a command via the remote shell
        /// </summary>
        /// <param name="command">The command to be executed</param>
        /// <returns>Output of the command</returns>
        public List<string> ExecuteCommand(string command)
        {
            ValidateCommand(command);

            return ExecuteCommand(command, null, TABInterface.DEFAULT_ADB_TIMEOUT);
        }

        /// <summary>
        /// Executes a command via the remote shell
        /// </summary>
        /// <param name="command">The command to be executed</param>
        /// <param name="outputHandler">Handler for output messages</param>
        /// <param name="timeout">Timeout for script execution</param>
        /// <returns>Output of the script</returns>
        private List<string> ExecuteCommand(string command, Action<string> outputHandler, int timeout)
        {
            using (var receiver = new GenericShellReceiver(outputHandler))
            {
                m_tab.ExecuteShellCommand(command, receiver, timeout);
                return receiver.Output;
            }
        }

        /// <summary>
        /// Begins executing a shell command in the device in background
        /// </summary>
        /// <param name="command">The command to be executed</param>
        public void BeginExecuteCommand(string command)
        {
            BeginExecuteCommand(command, null);
        }

        /// <summary>
        /// Begins executing a shell command in the device in background
        /// </summary>
        /// <param name="command">The command to be executed</param>
        /// <param name="outputHandler">Handler for output messages</param>
        public void BeginExecuteCommand(string command, Action<string> outputHandler)
        {
            ValidateCommand(command);

            var executer = new Thread(new ThreadStart(() =>
                {
                    try
                    {
                        ExecuteCommand(command, outputHandler, TABInterface.INFINITE_ADB_TIMEOUT);
                    }
                    catch { }

                })) { IsBackground = true };
            
            executer.Start();
        }

        /// <summary>
        /// Executes a shell script in the device
        /// </summary>
        /// <param name="script">Shell script as string</param>
        /// <returns>Output of the script</returns>
        public List<string> ExecuteScript(string script)
        {
            if (string.IsNullOrEmpty(script))
            {
                throw new ArgumentNullException("script");
            }
            return ExecuteScript(script, null, TABInterface.DEFAULT_ADB_TIMEOUT);
        }

        /// <summary>
        /// Executes a shell script in the device
        /// </summary>
        /// <param name="script">Shell script as string</param>
        /// <param name="outputHandler">Handler for output messages</param>
        /// <param name="timeout">Timeout for script execution</param>
        /// <returns>Output of the script</returns>
        private List<string> ExecuteScript(string script, Action<string> outputHandler, int timeout)
        {        
            var temp = Path.GetTempFileName();
            var remoteFolder = m_tab.File.Temp;
            var remotePath = LinuxPath.Combine(remoteFolder, Path.GetFileName(temp));

            try
            {
                File.WriteAllText(temp, FormatScript(script));
                m_tab.SyncService.PushFile(temp, remotePath, new NullSyncProgressMonitor());
                File.Delete(temp);
                return ExecuteCommand(string.Format("sh {0}", remotePath), outputHandler, timeout);
            }
            finally
            {
                try
                {
                    BeginExecuteCommand(string.Format("rm {0}", remotePath));
                }
                catch { }
            }
        }

        /// <summary>
        /// Begins executing a shell script in the device in background
        /// </summary>
        /// <param name="script">Shell script as string</param>
        public void BeginExecuteScript(string script)
        {
            BeginExecuteScript(script, null);
        }

        /// <summary>
        /// Begins executing a shell script in the device in background
        /// </summary>
        /// <param name="script">Shell script as string</param>
        /// <param name="outputHandler">Handler for output messages</param>
        public void BeginExecuteScript(string script, Action<string> outputHandler)
        {
            if (string.IsNullOrEmpty(script))
            {
                throw new ArgumentNullException("script");
            }

            var executor = new Thread(new ThreadStart(() =>
                {
                    try
                    {
                        ExecuteScript(script, outputHandler, TABInterface.INFINITE_ADB_TIMEOUT);
                    }
                    catch { }
                })) { IsBackground = true };
            executor.Start();
        }

        /// <summary>
        /// Validates the shell command
        /// </summary>
        /// <param name="command">The command to be valdated</param>
        private void ValidateCommand(string command)
        {
            if (string.IsNullOrEmpty(command))
            {
                throw new ArgumentNullException("command");
            }
            var bannedCommands = new List<string>(new string[] { "log:", "uiautomator", "monkey", "cat /proc/kmsg" });
            var cmd = command.Trim();

            if (bannedCommands.Exists(c => cmd.StartsWith(c)))
            {
                throw new Exception(string.Format("Instead of shell:{0}; use framework methods for the same purpose", cmd));
            }
        }

        /// <summary>
        /// Formats the shell script
        /// </summary>
        /// <param name="script">the script to be formatted</param>
        /// <returns>Formatted shell script</returns>
        private string FormatScript(string script)
        {
            var formatted = script.Replace("\r\n", "\n");

            var scriptStart = "#!/bin/bash";

            if (!formatted.Contains(scriptStart))
            {
                formatted = scriptStart + "\n\n" + formatted;
            }
            return formatted;
        }

        /// <summary>
        /// Generic receiver for shell command responses
        /// </summary>
        private class GenericShellReceiver : ObservingMultiLineReceiver, IDisposable
        {
            private Lazy<List<string>> m_lines;
            private WeakReference m_outputHandler;

            /// <summary>
            /// Class constructor
            /// </summary>
            public GenericShellReceiver()
            {
                m_lines = new Lazy<List<string>>(() =>
                {
                    return new List<string>();
                });

                NewLine += OnNewLine;
            }

            /// <summary>
            /// Called per each output line
            /// </summary>
            /// <param name="line">The output line</param>
            private void OnNewLine(string line)
            {
                if (m_outputHandler != null && m_outputHandler.IsAlive)
                {
                    (m_outputHandler.Target as Action<string>).Invoke(line);
                }
            }

            /// <summary>
            /// Class constructor
            /// </summary>
            /// <param name="outputHandler">Handler which is to be called on every line entry</param>
            public GenericShellReceiver(Action<string> outputHandler) :
                this()
            {
                if (outputHandler != null)
                {
                    m_outputHandler = new WeakReference(outputHandler, false);
                }
            }

            /// <summary>
            /// Output lines
            /// </summary>
            public List<string> Output
            {
                get
                {
                    return m_lines.Value.ToList();
                }
            }

            /// <summary>
            /// Called on every array of shell output lines
            /// </summary>
            /// <param name="lines">Data lines</param>
            protected override void ProcessNewLines(string[] lines)
            {
                var data = lines.ToList().ConvertAll<string>(l => l.Trim());
                m_lines.Value.AddRange(data);
            }

            /// <summary>
            /// Disposes the object
            /// </summary>
            public void Dispose()
            {
                NewLine -= OnNewLine;
            }
        }

        /// <summary>
        /// Handler delegate for new lines in ObservingMultiLineReceiver
        /// </summary>
        /// <param name="line">The new output line</param>
        private delegate void NewLineHandler(string line);

        /// <summary>
        /// ObservingMultiLineReceiver class
        /// </summary>
        private abstract class ObservingMultiLineReceiver : MultiLineReceiver
        {
            /// <summary>
            /// Fired on each output line
            /// </summary>
            public event NewLineHandler NewLine;

            /// <summary>
            /// Called on each output line
            /// </summary>
            /// <param name="line">The output line</param>
            protected override void AddLine(string line)
            {
                if (NewLine != null)
                {
                    NewLine(line);
                }
                base.AddLine(line);
            }

            /// <summary>
            /// Called to process a chunk of output lines
            /// </summary>
            /// <param name="lines">the chunk of output lines</param>
            protected override void ProcessNewLines(string[] lines)
            { }
        }
    }
}
