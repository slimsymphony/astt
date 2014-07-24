using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Management;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;
using System.Xml;
using System.Xml.Linq;
using Microsoft.VisualBasic.Devices;
using TestAutomation.Gui.Marble.Settings;

namespace Marble.Communication
{
    using Marble.Model;
    using Marble.ViewModel;

    /// <summary>
    /// Different states of the connector (and framework).
    /// State transitions are represented in 'Connector state diagram2.vsd'
    /// </summary>
    public enum ConnectorState
    {
        /// <summary>
        /// Framework is not started.
        /// </summary>
        Idle = 0, 

        /// <summary>
        /// Framework has been started. Connector is trying to connect to a socket opened by framework.
        /// </summary>
        StartingFramework = 1, 

        /// <summary>
        /// Framework is ready and connected but is not executing anything.
        /// </summary>
        FrameworkReady = 2, 

        /// <summary>
        /// A command has been sent to framework. Waiting for acknowledge.
        /// </summary>
        SendingCommand = 3, 

        /// <summary>
        /// Framework is executing a command.
        /// </summary>
        FrameworkExecuting = 4,
 
        /// <summary>
        /// Framework shutdown command has been sent.
        /// Waiting for the framework to shutdown itself.
        /// </summary>
        QuittingFramework = 5,

        /// <summary>
        /// Stop execution command has been sent.
        /// Wating for the framework to stop execution.
        /// </summary>
        StoppingExecution = 6
    }

    // TODO: Implement this using events?
    /// <summary>
    /// Method that connector calls to pass information to GUI thread (status updates, framework ouput and trace output)
    /// </summary>
    /// <param name="message">Information message line</param>
    /// <param name="logIndex">1 = status updates and framework output, 2 = trace output</param>
    public delegate void AppendLog(string message, int logIndex = 1);

    /// <summary>
    /// Handles the communication between the GUI and the framework.
    /// Connector is executed in a separate thread.
    /// 
    /// Accepts commands from GUI thread and executes them via framework process.
    /// GUI thread can directly call addToQueue method to enqueue commands.
    /// Connector notifies GUI thread via two methods ConnectorDone and AppendLog
    /// passing them to the GUI dispatcher for execution.
    /// Connector communicates with the framework via socket interface.
    /// 
    /// See "Connector state diagram2.vsd" for an overview of the logic.
    /// Changes on property named State are notified.
    /// </summary>
    public class Connector : System.ComponentModel.INotifyPropertyChanged
    {
        // properties for GUI communication
        private readonly Dispatcher mainWindowDispatcher;
        private readonly AppendLog appendLog;
#if FRAMEWORK_SUPPORTS_MARBLE_SETTINGS_DIRECTORY
        public string SettingsDirectory = "";
#else
        public string SettingsPath = "";
#endif

        // command queue
        //private System.Collections.Generic.Queue<BaseCommand> commandQueue;
        private readonly List<BaseCommand> commandQueue;
        private BaseCommand currentCommand;
        private BaseCommand stopCommand;
        private readonly Thread connectorThread;
        private bool stopThread;
        // internal state of the connector
        private ConnectorState state = ConnectorState.Idle;

        // properties for framework communication
        private Process fwProcess;
        private TcpClient client;
        private NetworkStream stream;
        // stores incomplete data from socket (message end sign not encountered)
        private String partialResponse = String.Empty;
        // framework log writer to file system
        private System.IO.StreamWriter logger;
        // lock for synchronization between the threads
        private readonly object loggerLock = new object();
        // buffers for the framework and trace output
        private readonly Utilities.TimedStringBuffer outputBuffer;
        private readonly Utilities.TimedStringBuffer traceBuffer;
        private bool isFollowerMode = false;

        // properties for framework timeout and error handling
        private DateTime lastConnectTry = DateTime.Now;
        private DateTime firstConnectTry = DateTime.MinValue;
        private DateTime lastMessageTime = DateTime.MinValue;
        private const int DefaultFrameworkTimeout = 300;
        private const int FrameworkQuitTimeout = 5;
        private TimeSpan socketTestInterval = new TimeSpan(0, 0, 0, 15);
        private DateTime lastSocketTest = DateTime.Now;
        private const int MAX_TRY_COUNT = 3;

        private readonly System.Timers.Timer fwQuitTimer;
        private readonly object waitLock = new object();
        // Ensures that socket stream is not read while performing framework cleanup
        private readonly object cleanUpLock = new object();
        private bool waitingFwQuit;
        private TimeSpan frameworkTimeout = new TimeSpan(0, 0, DefaultFrameworkTimeout);
        private Log4NetProvider log4NetProvider;


        public MarbleLogModel MarbleLogModel { get; set; }

        /// <summary>
        /// Gets state property changes are notified.
        /// </summary>
        public ConnectorState State
        {
            get { return this.state; }
            private set
            {
                if (this.state == value) return;

                this.state = value;
                this.OnPropertyChanged("State");

                if (this.state == ConnectorState.Idle)
                    this.isFollowerMode = false;

                App.ViewModel.UpdateConnectorRelatedProperties();
            }
        }

        /// <summary>
        /// Constructor. Creates a new thread for the connector and starts executing the main loop.
        /// </summary>
        /// <param name="mainWindowDispatcher">Dispatcher of the parent window hosting the connector</param>
        /// <param name="logMethod">Method to call for passing information</param>
        public Connector(Dispatcher mainWindowDispatcher, AppendLog logMethod)
        {
            this.mainWindowDispatcher = mainWindowDispatcher;
            this.appendLog = logMethod;
            this.commandQueue = new List<BaseCommand>();

            ////this.outputBuffer = new Utilities.TimedStringBuffer(WriteToGui);
            ////this.traceBuffer = new Utilities.TimedStringBuffer(WriteToGui, 2);
            this.fwQuitTimer = new System.Timers.Timer(FrameworkQuitTimeout * 1000);
            this.fwQuitTimer.Elapsed += FwQuitTimerElapsed;



            this.MarbleLogModel = new MarbleLogModel();

            this.connectorThread = new Thread(MainLoop);
            this.connectorThread.Start();
        }

        /// <summary>
        /// Calls OnPropertyChanged method for ConnectorState to refresh GUI bindings.
        /// </summary>
        public void RaiseConnectorStatePropertyChanged()
        {
            this.OnPropertyChanged("State");
        }

        /// <summary>
        /// Framework shutdown timeout expired - framework failed to shutdown in given time.
        /// Connector done event is triggered and framework is killed.
        /// </summary>
        /// <param name="source"></param>
        /// <param name="e"></param>
        private void FwQuitTimerElapsed(object source, System.Timers.ElapsedEventArgs e)
        {
            lock (this.waitLock)
            {
                if (!this.waitingFwQuit) return;

                // Stop command from outside of the connector
                if (this.stopCommand != null && !this.stopCommand.IsConnectorOriginated)
                    // Handle both situations: Test case was being executed or not
                    this.OnConnectorDone(this.currentCommand ?? this.stopCommand);

                this.CleanUpFramework("Failed to shutdown in given time", true);
            }
        }

        /// <summary>
        /// Triggered when the value of a public property has been changed.
        /// </summary>
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Called when the value of a public property has been changed.
        /// </summary>
        /// <param name="info">Name of the changed property</param>
        private void OnPropertyChanged(string info)
        {
            // Make a temporary copy of the event to avoid possibility of
            // a race condition if the last subscriber unsubscribes
            // immediately after the null check and before the event is raised.
            System.ComponentModel.PropertyChangedEventHandler handler = PropertyChanged;

            if (handler != null)
            {
                handler(this, new System.ComponentModel.PropertyChangedEventArgs(info));
            }
        }

        /// <summary>
        /// Called when connector has finished executing a framework command.
        /// </summary>
        /// <param name="executedCommand">Command that was executed</param>
        private void OnConnectorDone(BaseCommand executedCommand)
        {
            // hands the call back for GUI thread to execute
            if (executedCommand != null && executedCommand.CallBackMethod != null)
                mainWindowDispatcher.BeginInvoke(DispatcherPriority.Normal, (ThreadStart)(() => executedCommand.CallBackMethod(executedCommand)));
        }

        /// <summary>
        /// Writes and prints framework memory usage to framework log.
        /// </summary>
        /// <param name="writeToGUI">Whether to print memory usage to GUI.</param>
        private void LogFrameworkMemoryUsage(bool writeToGUI = false)
        {
            // Calculate available physical memory
            var computerInfo = new ComputerInfo();
            double percentFree = 0;
            try
            {
                if (computerInfo.TotalPhysicalMemory > 0)
                    percentFree = (double)computerInfo.AvailablePhysicalMemory / computerInfo.TotalPhysicalMemory;
            }
            catch(Win32Exception) {}

            // Write to framework log
            if (this.logger != null)
            {
                lock (this.loggerLock)
                {
                    this.logger.WriteLine("Available Phys:   {0}", computerInfo.AvailablePhysicalMemory);
                    this.logger.WriteLine("Available (%):    {0:P0}", percentFree);
                    this.logger.WriteLine("Private:          {0}", this.fwProcess.PrivateMemorySize64);
                    this.logger.WriteLine("Non paged (sys):  {0}", this.fwProcess.NonpagedSystemMemorySize64);
                    this.logger.WriteLine("Paged (sys):      {0}", this.fwProcess.PagedSystemMemorySize64);
                    this.logger.WriteLine("Paged:            {0}", this.fwProcess.PagedMemorySize64);
                    this.logger.WriteLine("Peak paged:       {0}", this.fwProcess.PeakPagedMemorySize64);
                    this.logger.WriteLine("Virtual:          {0}", this.fwProcess.VirtualMemorySize64);
                    this.logger.WriteLine("Peak virtual:     {0}", this.fwProcess.PeakVirtualMemorySize64);
                    this.logger.WriteLine("Working set:      {0}", this.fwProcess.WorkingSet64);
                    this.logger.WriteLine("Peak working set: {0}", this.fwProcess.PeakWorkingSet64);
                }
            }

            // Print to GUI
            if (!writeToGUI) return;

            ////this.outputBuffer.Append(string.Format("Available Phys:   {0}\n", computerInfo.AvailablePhysicalMemory));
            ////this.outputBuffer.Append(string.Format("Available (%):    {0:P0}\n", percentFree));
            ////this.outputBuffer.Append(string.Format("Private:          {0}\n", this.fwProcess.PrivateMemorySize64));
            ////this.outputBuffer.Append(string.Format("Non paged (sys):  {0}\n", this.fwProcess.NonpagedSystemMemorySize64));
            ////this.outputBuffer.Append(string.Format("Paged (sys):      {0}\n", this.fwProcess.PagedSystemMemorySize64));
            ////this.outputBuffer.Append(string.Format("Paged:            {0}\n", this.fwProcess.PagedMemorySize64));
            ////this.outputBuffer.Append(string.Format("Peak paged:       {0}\n", this.fwProcess.PeakPagedMemorySize64));
            ////this.outputBuffer.Append(string.Format("Virtual:          {0}\n", this.fwProcess.VirtualMemorySize64));
            ////this.outputBuffer.Append(string.Format("Peak virtual:     {0}\n", this.fwProcess.PeakVirtualMemorySize64));
            ////this.outputBuffer.Append(string.Format("Working set:      {0}\n", this.fwProcess.WorkingSet64));
            ////this.outputBuffer.Append(string.Format("Peak working set: {0}\n", this.fwProcess.PeakWorkingSet64));
        }

        /// <summary>
        /// Main loop for the connector thread
        /// 
        /// Reads commands from the command queue
        /// Tries to connect to the framework
        /// Sends commands to the framework
        /// Handles responses from the framework
        /// </summary>
        private void MainLoop()
        {
            while (true)
            {
                // Try to connect to the framework
                if (this.State == ConnectorState.StartingFramework)
                    if (this.TryConnect())
                        this.State = ConnectorState.FrameworkReady;

                // Check if command queue contains emergency stop or regular stop
                if (this.State != ConnectorState.QuittingFramework)
                {
                    // Store emergency stop command for execution
                    if (this.stopCommand == null || this.stopCommand.GetType() != typeof(EmergencyStop))
                        lock (this.commandQueue)
                            this.stopCommand =
                                this.commandQueue.FirstOrDefault(cmd => cmd.GetType() == typeof (EmergencyStop));

                    // Store regular stop command for execution
                    if (this.stopCommand == null)
                        lock (this.commandQueue)
                            this.stopCommand =
                                this.commandQueue.FirstOrDefault(cmd => cmd.GetType() == typeof (StopExecution));

                    // Execute emergency stop or regular stop command
                    if (this.stopCommand != null && this.stopCommand.GetType() == typeof(EmergencyStop))
                        this.PerformQuitFramework(this.stopCommand);
                    else if (this.stopCommand != null)
                        this.HandleStopCommand(this.stopCommand);
                }

                // Get a task from the command queue
                lock (this.commandQueue)
                    if (this.currentCommand == null && this.commandQueue.Count > 0 && this.stopCommand == null)
                    {
                        this.currentCommand = this.commandQueue[0];
                        this.currentCommand.TryCount++;
                    }

                // Execute current command (if framework is not shutting down)
                if (this.currentCommand != null && this.State != ConnectorState.QuittingFramework)
                {                        

                    // Handle RunTC, Capture, Settings update, Shutdown, Menu, Testrun end, Images fetch, create CTT test set, update CTT configuration
                    if (this.currentCommand.GetType() == typeof(RunTestCaseCommand) ||
                        this.currentCommand.GetType() == typeof(CaptureCommand) ||
                        this.currentCommand.GetType() == typeof(SettingsCommand) ||
                        this.currentCommand.GetType() == typeof(ShutdownFramework) ||
                        this.currentCommand.GetType() == typeof(MenuCommand) ||
                        this.currentCommand.GetType() == typeof(InitMarbleServerCommand) ||
                        this.currentCommand.GetType() == typeof(TestRunEnd) ||
                        this.currentCommand.GetType() == typeof(DisableLockScreen) ||
                        this.currentCommand.GetType() == typeof(ExecuteTestStep) ||
                        this.currentCommand.GetType() == typeof(ImagesCommand) ||
                        this.currentCommand.GetType() == typeof(CreateCoreTestToolTestSetCommand) ||
                        this.currentCommand.GetType() == typeof(CreateSxTestSetCommand) ||
                        this.currentCommand.GetType() == typeof(UpdateCoreTestToolConfigurationCommand))
                        this.HandleRunTc(this.currentCommand);

                    // invalid command
                    else
                    {
                        lock (this.commandQueue)
                            if (this.commandQueue.Count > 0 && this.currentCommand == this.commandQueue[0])
                                this.commandQueue.RemoveAt(0);
                        this.currentCommand = null;
                    }
                }

                // handle received data
                if (State != ConnectorState.Idle && State != ConnectorState.StartingFramework
                    && State != ConnectorState.FrameworkReady && !this.isFollowerMode)
                    HandleResponse();

                // Quit main loop and stop connector
                if (this.stopThread && this.State == ConnectorState.Idle)
                    break;

                // No ongoing execution: Wait 250 ms before the next round - so process will not consume CPU time
                if (this.State == ConnectorState.Idle || this.State == ConnectorState.FrameworkReady)
                    Thread.Sleep(250);
                else
                    Thread.Sleep(10);
            }
            // Wrap it up
            this.CleanUpFramework("Application shutting down", true);

            // Prevent garbage collection of timer instance before this point
            GC.KeepAlive(this.fwQuitTimer);
        }

        /// <summary>
        /// Sends framework quit command if framework is running or ready.
        /// </summary>
        /// <param name="command">Quit command to send.</param>
        private void HandleFrameworkQuit(BaseCommand command)
        {
            if (this.State == ConnectorState.Idle)
                this.FinalizeStop();
            else if (this.State != ConnectorState.QuittingFramework && this.State != ConnectorState.StartingFramework)
            {
                this.WriteToLogs("Executing " + command.GetInfoString());
                ////this.WriteToLogs(new MarbleLogEntry("Executing " + command.GetInfoString()));
                this.stopCommand = command;
                this.State = ConnectorState.QuittingFramework;
                this.SendData(command.CreateCommand());
            }
        }

        /// <summary>
        /// Sends stop command to framework if framework is executing or receiving a command.
        /// Finalizes stop command if framework is already stopping or shutting down.
        /// </summary>
        /// <param name="command">Stop command to send</param>
        private void HandleStopCommand(BaseCommand command)
        {
            if (this.State == ConnectorState.FrameworkExecuting || this.State == ConnectorState.SendingCommand)
            {
                this.WriteToLogs("Executing " + command.GetInfoString());
                ////this.WriteToLogs(new MarbleLogEntry("Executing " + command.GetInfoString()));
                this.State = ConnectorState.StoppingExecution;
                this.SendData(command.CreateCommand());
            }
            else if (this.State == ConnectorState.Idle || this.State == ConnectorState.FrameworkReady)
            {
                this.CommandCompleted("Execution stopped");
            }
        }

        /// <summary>
        /// Logic for controlling states during a test case execution
        /// </summary>
        /// <param name="command">Command to be executed</param>
        private void HandleRunTc(BaseCommand command)
        {
            // IDLE
            if (State == ConnectorState.Idle)
            {
                if (command.GetType() == typeof (ShutdownFramework) || command.GetType() == typeof (TestRunEnd))
                    this.CommandCompleted("marble_resp");
                else
                    StartFramework(GetStartUpArguments());
            }
            // FW_READY
            else if (State == ConnectorState.FrameworkReady)
            {
                // Send command to framework
                State = ConnectorState.SendingCommand;
                SendData(command.CreateCommand());
                this.WriteToLogs("Executing " + command.GetInfoString());
                ////this.WriteToLogs(new MarbleLogEntry("Executing " + command.GetInfoString()));
            }
        }

        /// <summary>
        /// Clears the command queue and sets stop command to null.
        /// </summary>
        private void FinalizeStop()
        {
            if (!this.stopCommand.IsConnectorOriginated)
                lock (this.commandQueue)
                    this.commandQueue.Clear();

            this.stopCommand = null;            
        }

        /// <summary>
        /// Sets framework quit command as the current command.
        /// Timer is started to trigger killing of the framework if no correct response received.
        /// </summary>
        private void PerformQuitFramework(BaseCommand command)
        {
            // Should not be executed but just in case
            if (this.State == ConnectorState.Idle)
            {
                this.CleanUpFramework(command.GetInfoString(), true);
                return;
            }

            // Start wait timer
            lock (this.waitLock)
            {
                if (!this.waitingFwQuit)
                {
                    this.fwQuitTimer.Interval = FrameworkQuitTimeout * 1000;
                    this.fwQuitTimer.Start();
                }
                this.waitingFwQuit = true;
            }

            // Send quit command to framework
            this.HandleFrameworkQuit(command);
        }

        /// <summary>
        /// Tries to read response message from the socket
        /// Takes care of attaching partial responses together
        /// Modifies connector state according to response messages
        /// </summary>
        private void HandleResponse()
        {
            // fetch data from the socket stream
            String resp = ReceiveData();
            if (resp.Length <= 0)
                return;

            //writeToGUI(resp);
            this.partialResponse += resp;
            // message end-mark not included i.e. only part of the message received
            if (!resp.Contains("\n"))
                return;

            String newPartialResponse = String.Empty;
            // incomplete message exists
            if (!this.partialResponse.EndsWith("\n"))
            {
                // extract incomplete message
                newPartialResponse = this.partialResponse.Substring(partialResponse.LastIndexOf("\n", StringComparison.Ordinal) + 1);
                this.partialResponse = this.partialResponse.Substring(0, partialResponse.LastIndexOf("\n", StringComparison.Ordinal) + 1);
            }

            // split complete messages
            String[] messages = this.partialResponse.Split(new[] { '\n' }, StringSplitOptions.RemoveEmptyEntries);

            // For next round: Empty or extracted incomplete message
            this.partialResponse = newPartialResponse;

            // handle each message
            foreach (string message in messages)
            {
                if (this.MarbleLogModel != null)
                    this.MarbleLogModel.AddMarbleLogEntry(new MarbleLogEntry(MarbleLogEntryType.FrameworkResponse, message.TrimEnd('\n')));

                // MARBLE_WAIT = marble_wait|delay|string_message
                if (message.Contains("marble_wait"))
                {
                    // extract the timeout value framework desires
                    String[] blocks = message.Split(new[] { '|' });
                    // timeout value in seconds
                    if (blocks[1].Length > 0)
                    {
                        // Set timeout - default framework timeout (30s.) + desired timeout
                        int timeout;
                        this.frameworkTimeout = new TimeSpan(0, 0, DefaultFrameworkTimeout);
                        if (int.TryParse(blocks[1], out timeout))
                            this.frameworkTimeout = this.frameworkTimeout.Add(new TimeSpan(0, 0, timeout));
                    }

                    // SENDING_COMMAND
                    if (State == ConnectorState.SendingCommand && blocks.Length > 2 && blocks[2].Contains("command OK"))
                        // Test run end command doesn't need to wait for a response
                        if (this.currentCommand != null &&
                            (this.currentCommand.GetType() == typeof (TestRunEnd) || this.currentCommand.GetType() == typeof (DisableLockScreen)))
                            this.CommandCompleted("marble_resp");
                        else if (this.currentCommand != null && this.currentCommand.GetType().IsAssignableFrom(typeof(ShutdownFramework)))
                            this.State = ConnectorState.QuittingFramework;
                        else
                            this.State = ConnectorState.FrameworkExecuting;
                }
                
                // MARBLE_RESP or MARBLE_ERROR
                else if((message.StartsWith("marble_resp") || message.StartsWith("marble_error")) &&
                    (this.currentCommand != null && message.Contains(this.currentCommand.Command) || this.stopCommand != null && message.Contains(this.stopCommand.Command)) &&
                    (this.State == ConnectorState.StoppingExecution || this.State == ConnectorState.FrameworkExecuting || this.State == ConnectorState.QuittingFramework))
                {
                    this.CommandCompleted(message);
                }
            }
        }

        /// <summary>
        /// Framework finished executing the command.
        /// </summary>
        /// <param name="message">Response message returned by framework.</param>
        private void CommandCompleted(string message="")
        {
            // Don't call ConnectorDone when executing test run end command or stop command is created by connector
            if (this.stopCommand == null && this.currentCommand != null &&
                this.currentCommand.GetType() != typeof(TestRunEnd) && this.currentCommand.GetType() != typeof(DisableLockScreen) ||
                (this.stopCommand != null && !this.stopCommand.IsConnectorOriginated))
                this.OnConnectorDone(this.currentCommand ?? this.stopCommand);

            // Not internal stop command created by Connector
            if (this.stopCommand == null || !this.stopCommand.IsConnectorOriginated)
                lock (this.commandQueue)
                {
                    // Clear command queue on stop
                    if (this.stopCommand != null)
                        this.FinalizeStop();

                    // Remove executed command from the queue
                    else if (this.currentCommand != null && this.commandQueue.Count > 0 && this.currentCommand == this.commandQueue[0])
                        this.commandQueue.RemoveAt(0);
                }

            // Execution success
            if (message.StartsWith("marble_resp"))
            {
                // Framework was shutdown: Perform cleanup.
                if (this.State == ConnectorState.QuittingFramework)
                    this.CleanUpFramework("Shut down called");
                else if (this.State != ConnectorState.Idle)
                    State = ConnectorState.FrameworkReady;

                // Print done message
                string replyCommand = string.Empty;
                if (message.IndexOf('|') >= 0)
                    replyCommand = message.Substring(message.IndexOf('|') + 1);
                else if (this.currentCommand != null && this.currentCommand.GetType() == typeof(TestRunEnd))
                    replyCommand = "end";

                // Don't print "Done" for Disable lock screen operation
                if (this.currentCommand == null || this.currentCommand.GetType() != typeof(DisableLockScreen))
                    this.WriteToLogs(string.IsNullOrEmpty(replyCommand)
                                            ? "Done"
                                            : string.Format("Done ({0})", replyCommand));
                    ////this.WriteToLogs(new MarbleLogEntry(string.IsNullOrEmpty(replyCommand)
                    ////                        ? "Done"
                    ////                        : string.Format("Done ({0})", replyCommand)));
            }

            // Error occurred
            else
            {
                // Framework shutdown failed: Kill framework and perform cleanup.
                if (this.State == ConnectorState.QuittingFramework)
                    this.CleanUpFramework("Failed to shutdown", true);
                else
                    this.State = this.State == ConnectorState.Idle ? ConnectorState.Idle : ConnectorState.FrameworkReady;

                // Replace ?#- (erroneous new line) with correct new line
                this.WriteToLogs(message.Replace("?#-", "\n"));
                ////this.WriteToLogs(new MarbleLogEntry(message.Replace("?#-", "\n")));
            }

            // Clear handled command
            this.currentCommand = null;
            this.frameworkTimeout = new TimeSpan(0, 0, DefaultFrameworkTimeout);

            this.FlushLogger();                    

            // Check available memory and restart framework if needed
            if (this.State != ConnectorState.Idle && this.fwProcess != null && !this.fwProcess.HasExited)
            {
                this.fwProcess.Refresh();
                this.LogFrameworkMemoryUsage();
                
                // Shutdown framework if it consumes more than 1000MB of memory
                if (this.fwProcess.WorkingSet64 > 1000000000)
                    lock (this.commandQueue)
                        this.commandQueue.Insert(0, new ShutdownFramework("High memory usage"));
            }
        }

        /// <summary>
        /// Flushes logger i.e. writes logging buffer to log file.
        /// Catches IOExpection and displays a message box to inform user about the error that occurred.
        /// For example if hard disk full.
        /// </summary>
        private void FlushLogger()
        {
            lock (loggerLock)
            {
                if (logger == null) return;

                try
                {
                    logger.Flush();
                }
                catch (IOException e)
                {
                    // Check if the error is due to disk full and print information accordingly
                    const long errorHandleDiskFull = 0x27;
                    const long errorDiskFull = 0x70;

                    long win32ErrorCode = Marshal.GetHRForException(e) & 0xFFFF;
                    if (win32ErrorCode == errorHandleDiskFull || win32ErrorCode == errorDiskFull)
                    {
                        MessageBox.Show("Please free some space from the hard drive before continuing.",
                                        "Not enough space on target disk",
                                        MessageBoxButton.OK, MessageBoxImage.Error);
                    }
                    // Print generic error message
                    else
                    {
                        var errorMessage = string.Format("Exception: {0}\nInnerException: {1}",
                                                         e.Message,
                                                         e.InnerException.Message);
                        MessageBox.Show(errorMessage, e.GetType().Name, MessageBoxButton.OK, MessageBoxImage.Error);
                    }
                }
            }
        }

        /// <summary>
        /// Tries to create a connection to the framework process
        /// Connection creation is tried at most once in every second
        /// Maximum time of 60 seconds is tried and then framework is killed
        /// This is repeated maximum of three times and then emergencyStop is executed 
        /// On success private properties TcpClient client and NetworkStream stream are set 
        /// </summary>
        /// <returns>True on success otherwise false</returns>
        private bool TryConnect()
        {
            dynamic settings = SettingsManager.Instance;
            // Maximum time to try is 60 seconds
            var maxConnectTimeout = new TimeSpan(0, 0, 60);
            if (firstConnectTry == DateTime.MinValue)
                firstConnectTry = DateTime.Now;

            // Maximum time has passed since first try - kill framework
            if (DateTime.Now - firstConnectTry > maxConnectTimeout)
            {
                this.WriteToLogs("Could not connect to framework");
                ////this.WriteToLogs(new MarbleLogEntry("Could not connect to framework"));
                this.HandleFrameworkError();
                CleanUpFramework("Connect timeout", true);
                return false;
            }

            // one second has passed since last try - try to connect
            if (DateTime.Now - lastConnectTry > new TimeSpan(0, 0, 1))
            {
                lastConnectTry = DateTime.Now;
                try
                {
                    // Create a TcpClient.
                    client = new TcpClient("127.0.0.1", settings.System.GuiFrameworkProtocolPort);

                    // Get a client stream for reading and writing.
                    stream = client.GetStream();
                    State = ConnectorState.FrameworkReady;
                    this.WriteToLogs("Connected to framework");
                    ////this.WriteToLogs(new MarbleLogEntry("Connected to framework"));
                    firstConnectTry = DateTime.MinValue;
                    lastMessageTime = DateTime.Now;
                    if (this.log4NetProvider != null && this.log4NetProvider.IsActive)
                        this.log4NetProvider.Close();

                    this.log4NetProvider = new Log4NetProvider(this, settings.System.FrameworkGuiLoggerPort);
                    return true;

                }
                // connection attempt failed
                catch (SocketException)
                {
                    //Console.WriteLine("SocketException: {0}", e);
                }
            }
            return false;
        }

        /// <summary>
        /// Sends information message to GUI thread via appendLog method
        /// </summary>
        /// <param name="str">Information line to be passed to GUI</param>
        /// <param name="textLog">>1 = status updates, 2 = framework output</param>
        private void WriteToGui(string str, int textLog = 1)
        {
            // add new line at the end
            
            if (!str.EndsWith("\n"))
                str += "\n";

            ////// hands the command for GUI thread to execute                
            ////mainWindowDispatcher.BeginInvoke(DispatcherPriority.Background,
            ////    (ThreadStart)(() => appendLog(str, textLog))
            ////    );
            
            this.WriteToLogs(str);
        }

        /// <summary>
        /// Sends data to the framework process
        /// </summary>
        /// <param name="str">Data to be sent to the framework</param>
        private void SendData(String str)
        {
            if (this.stream == null)
            {
                Console.Write("Socket stream not open: {0}", str);
                return;
            }
            // Translate the passed message into ASCII and store it as a Byte array.
            Byte[] data = System.Text.Encoding.ASCII.GetBytes(str);

            try
            {
                if (this.MarbleLogModel != null)
                    this.MarbleLogModel.AddMarbleLogEntry(new MarbleLogEntry(MarbleLogEntryType.FrameworkRequest, str.TrimEnd('\n')));

                // Send the message to the connected TcpServer. 
                stream.Write(data, 0, data.Length);
                lastMessageTime = DateTime.Now;
            }
            catch (System.IO.IOException ioe)
            {
                Console.WriteLine("IOException: {0}", ioe);
                this.WriteToLogs("Message sending to framework failed");
                this.HandleFrameworkError();
                CleanUpFramework("Message sending failure", true);
            }
            Console.Write("Sent:{0:HH:mm:ss.fff} {1}", DateTime.Now, str);
        }

        /// <summary>
        /// Checks whether the network stream to framework is still usable (by sending one byte into it).
        /// </summary>
        /// <returns>True on success false otherwise.</returns>
        private bool IsStreamConnected()
        {
            if (stream == null || !stream.CanRead || !stream.CanWrite) return false;

            try
            {
                stream.WriteByte(new byte());
            }
            catch (IOException)
            {
                return false;
            }

            return true;
        }

        /// <summary>
        /// Receives data from the framework process
        /// </summary>
        /// <returns>Data received from the framework</returns>
        private String ReceiveData()
        {
            lock (this.cleanUpLock)
            {
                if (stream == null)
                    return string.Empty;

                try
                {
                    // Stream doesn't contain data
                    if (!stream.DataAvailable)
                    {
                        // Check framework connection status
                        if (DateTime.Now - lastSocketTest > socketTestInterval)
                        {
                            bool connected = true;
                            if (this.fwProcess.HasExited)
                            {
                                this.WriteToLogs(
                                    string.Format(
                                        "Framework process has exited unexpectedly at {0:HH:mm:ss.fff} with exit code {1}.",
                                        fwProcess.ExitTime, fwProcess.ExitCode));
                                connected = false;
                            }
                            else if (!this.IsStreamConnected())
                            {
                                this.WriteToLogs("Can't receive data from the framework. Socket connection unavailable.");
                                connected = false;
                            }

                            lastSocketTest = DateTime.Now;

                            if (!connected)
                            {
                                this.HandleFrameworkError();
                                this.CleanUpFramework("Lost connection to framework");
                                return string.Empty;
                            }
                        }

                        // Connection OK but no data received from the framework within the timeout limit
                        if (DateTime.Now - lastMessageTime > frameworkTimeout)
                        {
                            this.WriteToLogs("Framework timed out");
                            this.HandleFrameworkError();

                            // Kill framework if we already have asked it to quit
                            if (this.State == ConnectorState.QuittingFramework)
                                this.CleanUpFramework("Failed to shutdown", true);
                                // Send quit command to framework
                            else
                                this.PerformQuitFramework(new ShutdownFramework("Receive timeout")
                                    {
                                        IsConnectorOriginated = true
                                    });
                        }
                        return String.Empty;
                    }

                    // Buffer to store the response bytes.
                    var data = new Byte[512];

                    // Read the first batch of the TcpServer response bytes.
                    Int32 bytes = stream.Read(data, 0, data.Length);

                    // String to store the response ASCII representation.
                    string responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
                    Console.Write("Rec:{0:HH:mm:ss.fff} {1}", DateTime.Now, responseData);
                    lastMessageTime = DateTime.Now;
                    lastSocketTest = DateTime.Now;

                    return responseData;
                }
                catch (SocketException ex)
                {
                    this.WriteToLogs("Lost connection to framework. Exception: " + ex.Message);
                    this.HandleFrameworkError();
                    CleanUpFramework("Receive failure", true);
                    return String.Empty;
                }
            }
        }

        /// <summary>
        /// Closes the socket connection to framework
        /// </summary>
        private void Disconnect()
        {
            lock (cleanUpLock)
            {
                // Close stream and client
                if (stream != null)
                {
                    stream.Close();
                    stream = null;
                }
                if (client != null)
                {
                    client.Close();
                    client = null;
                }
            }
        }

        /// <summary>
        /// This method is called when framework crashes or times out.
        /// Determines whether the execution of the current command should be tried again or should we move on to the next command.
        /// </summary>
        private void HandleFrameworkError()
        {
            if (this.currentCommand == null || this.currentCommand.TryCount < MAX_TRY_COUNT) return;

            // Remove executed command from the queue
            if (this.commandQueue.Count > 0 && this.currentCommand == this.commandQueue[0])
                this.commandQueue.RemoveAt(0);

            this.currentCommand.Error = "Framework could not complete execution in three tries.";
            this.OnConnectorDone(this.currentCommand);
        }

        /// <summary>
        /// Disconnects from the framework, closes the logger and sets connector state to IDLE.
        /// <param name="killFramework">Whether to also kill the framework. Used if framework is not responding.</param>
        /// <param name="waitExtra">Whether to give framework some extra time to shutdown itself.</param>
        /// </summary>
        private void CleanUpFramework(string reason="", bool killFramework = true, bool waitExtra = true)
        {

            // Stop waiting for framework quit
            this.fwQuitTimer.Stop();
            lock (this.waitLock)
                this.waitingFwQuit = false;

            this.currentCommand = null;
            if (this.stopCommand != null)
                this.FinalizeStop();

            // reset connecting timeout
            this.firstConnectTry = DateTime.MinValue;

            // close connections
            this.Disconnect();

            // wait maximum of three seconds for the framework to shutdown
            var maxWait = new TimeSpan(0, 0, 3);
            var startTime = DateTime.Now;
            Thread.Sleep(250);
            int count = 0;
            while (waitExtra && this.fwProcess != null && !this.fwProcess.HasExited && DateTime.Now - startTime < maxWait )
            {
                if (count % 4 == 0)
                    this.WriteToLogs(string.Format("Framework not closed yet - waiting {0:F0}/{1:F0} (ms)", (DateTime.Now - startTime).TotalMilliseconds, maxWait.TotalMilliseconds));
                Thread.Sleep(250);
                count++;
            }

            // kill and close framework process
            if (killFramework && this.fwProcess != null && !this.fwProcess.HasExited)
            {
                this.fwProcess.Kill();
                this.WriteToLogs(string.IsNullOrEmpty(reason)
                                             ? "Framework killed"
                                             : string.Format("Framework killed ({0})", reason));
            }

            if (killFramework && this.fwProcess != null)
            {
                this.fwProcess.Dispose();
                this.fwProcess = null;
            }
            this.WriteToLogs(string.IsNullOrEmpty(reason)
                                         ? "Framework cleaned up"
                                         : string.Format("Framework cleaned up ({0})", reason));            
            
            // Close Log4Net UDP listener
            if (this.log4NetProvider != null && this.log4NetProvider.IsActive)
            {
                this.log4NetProvider.Close();
                this.log4NetProvider = null;
            }

            // close logger
            lock (this.loggerLock)
            {
                if (this.logger != null)
                {
                    logger.WriteLine("{0:dd.MM.yyyy HH:mm:ss.fff} {1}", DateTime.Now, "Logger closed");
                    this.FlushLogger();
                    this.logger.Close();
                    this.logger = null;
                }
            }

            // set connector to idle
            this.State = ConnectorState.Idle;
        }

        /// <summary>
        /// Add a framework command to the end of the command queue
        /// </summary>
        /// <param name="command">Command to be added to the queue</param>
        public void AddToQueue(BaseCommand command)
        {
            lock (this.commandQueue)
                commandQueue.Add(command);
        }

        /// <summary>
        /// Kills framework and stops connector process.
        /// Joins connector thread to GUI thread.
        /// </summary>
        public void StopAndWaitToFinish()
        {
            if (this.State != ConnectorState.Idle)
                this.AddToQueue(new EmergencyStop("Connector stopped"));
            this.stopThread = true;

            if (this.MarbleLogModel != null)
            {
                this.MarbleLogModel = null;
            }

            // GUI thread waits for the connector thread to finish
            if (this.connectorThread != null)
            {
                this.connectorThread.Join();
            }
        }

        /// <summary>
        /// Creates startup parameters for the framework process.
        /// </summary>
        /// <returns>Startup parameters string</returns>
        private String GetStartUpArguments()
        {
#if FRAMEWORK_SUPPORTS_MARBLE_SETTINGS_DIRECTORY
            // "..\framework\marble.py" --settings_dir = "..\settings"
            return String.Format("\"{0}\" --settings_dir \"{1}\"",
                Path.GetFullPath(@"..\framework\marble.py"),
                SettingsDirectory);
#else
            // "..\framework\marble.py" --settings "modified.settings"
            //// CHANGE G.R.A.N.I.T.E to marble.py when ready.
            return String.Format("\"{0}\" --settings \"{1}\"",
                System.IO.Path.GetFullPath(@"..\framework\marble.py"),
                SettingsPath);
#endif
        }

        /// <summary>
        /// Starts the framework in MTBF Follower mode. GUI-->FW connector is not used in this mode.
        /// </summary>
        internal void StartFrameworkInFollowerMode(bool whiteBoxFollower = false, bool bltueEnabled = false)
        {
            // Cleanup any existing FW run without waiting
            if (this.fwProcess != null)
                this.CleanUpFramework("Clean previous framework", true, false);

            this.frameworkTimeout = TimeSpan.MaxValue;

            string additionalArgs = string.Empty;
            if (!whiteBoxFollower)
                additionalArgs = "--blackbox_phonemodel=" + App.BlackBoxViewModel.PhoneModelSelected;

            if (bltueEnabled)
            {
                if (!string.IsNullOrEmpty(additionalArgs))
                    additionalArgs += " ";
                additionalArgs += "--bltue_enabled";
            }

            this.StartFramework(this.GetStartUpArguments() + " --follower true " + additionalArgs);
            this.isFollowerMode = true;

            this.WriteToLogs("Starting follower mode execution");

            if (this.log4NetProvider != null && this.log4NetProvider.IsActive)
                this.log4NetProvider.Close();

            dynamic settings = SettingsManager.Instance;
            this.log4NetProvider = new Log4NetProvider(this, settings.System.FrameworkGuiLoggerPort);
            this.State = ConnectorState.FrameworkExecuting;
        }

        /// <summary>
        /// Stops the MTBF Follower mode execution. GUI-->FW connector is not used in this mode, so just kill the fwProcess.
        /// </summary>
        internal void StopFollowerExecution()
        {
            this.CleanUpFramework("Stopped follower mode execution", true, false);
        }

        /// <summary>
        /// Starts the framework process with given startup parameters.
        /// Standard and error outputs are redirected to output handler.
        /// </summary>
        /// <param name="arguments">Startup parameters to be used</param>
        private void StartFramework(string arguments)
        {
            if (App.ViewModel.debugMode)
            {
                arguments = arguments.Insert(0, "-X:Debug ");
            }

            // Terminate previous left over ipy processes.
            this.TerminateIpyProcess();

            //try
            //{
                // Randomize ports used between GUI-->FW communications. Socket connector, BLT-UE service, Log4Net UDP logger.
                this.randomizePorts();
            //}
            //catch (Exception e)
            //{
            //    throw e;
            //}

            dynamic settings = SettingsManager.Instance;
            bool developerMode = settings.System.DeveloperMode;
            ProcessWindowStyle windowStyle = ProcessWindowStyle.Hidden;
            if (developerMode)
                windowStyle = ProcessWindowStyle.Normal;
            fwProcess = new Process
            {
                StartInfo =
                    {
                        FileName = "ipy",
                        Arguments = arguments,
                        WindowStyle = windowStyle
                    }
            };

            // close previous logger
            lock (loggerLock)
            {
                if (logger != null)
                {
                    logger.WriteLine("{0:dd.MM.yyyy HH:mm:ss.fff} {1}", DateTime.Now, "Logger closed");
                    this.FlushLogger();
                    logger.Close();
                    logger = null;
                }
            }

            if (!System.IO.Directory.Exists("Framework_logs"))
                System.IO.Directory.CreateDirectory("Framework_logs");

            string logPath = newUniquePath(@"Framework_logs\Log.txt");
            logger = new System.IO.StreamWriter(logPath, false);

            try
            {
                fwProcess.Start();
            }
            catch (System.ComponentModel.Win32Exception e)
            {
                fwProcess.Close();
                fwProcess = null;
                this.CleanUpFramework("Failed to start", true);
                System.Windows.MessageBox.Show("Error: " + e.Message + " (ipy.exe)" +
                    "\nPlease make sure IronPython folder can be found from the path environment variable" +
                    "\ne.g. C:\\Program Files (x86)\\IronPython 2.7.1\\",
                    "Error in starting the framework");
                return;
            }

            State = ConnectorState.StartingFramework;
            this.WriteToLogs("Framework started\n");
        }

        /// <summary>
        /// Check if previous ipy processes are running and terminate them.
        /// </summary>
        private void TerminateIpyProcess()
        {
            const string query = @"SELECT * FROM Win32_Process Where Caption = ""ipy.exe""";
            using (var processSearcher = new ManagementObjectSearcher(query))
            {
                using (ManagementObjectCollection objectCollection = processSearcher.Get())
                {
                    foreach (ManagementObject obj in objectCollection)
                    {
                        if (obj["CommandLine"] == null)
                        {
                            obj.Dispose();
                            continue;
                        }

                        string commandLine = obj["CommandLine"].ToString();

                        // Check whether this ipy process is a Marble framework from the same directory
                        if (commandLine.Contains(Path.GetFullPath(@"..\framework\marble.py")))
                        {
                            // Check whether this framework process is launched from command line
                            bool isCommandLineFramework =
                                commandLine.Split(new[] {' '}, StringSplitOptions.RemoveEmptyEntries)
                                           .Any(param => param.StartsWith("--test_set") ||
                                               param.StartsWith("--test_file_list") || param.StartsWith("--test_file_xml"));

                            // Skip this since it's a command line framework (started without GUI)
                            if (isCommandLineFramework)
                                continue;

                            // Terminate leftover framework process
                            try
                            {
                                obj.InvokeMethod("Terminate", null);
                            }
                            catch (ManagementException ex)
                            {
                                this.WriteToLogs("Could not kill old ipy process. " + ex.Message + " " + ex.InnerException.Message);
                            }
                        }
                        obj.Dispose();
                    }
                }
            }
        }

        /// <summary>
        /// Event handler for standard output of the framework process.
        /// Writes output data to GUI and framework log.
        /// </summary>
        /// <param name="data">Data send by the process</param>
        internal void outputHandler(string data)
        {
            if (String.IsNullOrEmpty(data)) return;

            this.WriteToLogs(data);
        }

        /// <summary>
        /// Event handler for standard output of the framework process.
        /// Writes output data to GUI and framework log.
        /// </summary>
        /// <param name="data">Data send by the process</param>
        internal void outputHandler(Log4NetProvider.LogEntry data)
        {
            if (data == null) return;

            MarbleLogEntry marbleLogEntry = new MarbleLogEntry(data);

            this.WriteToLogs(marbleLogEntry);
        }

        /// <summary>
        /// Event handler for standard error output of the framework process.
        /// Writes output data to trace window of the GUI.
        /// </summary>
        /// <param name="data">Data send by the process</param>
        internal void errorOutputHandler(string data)
        {
            if (!String.IsNullOrEmpty(data))
                traceBuffer.Append(data + "\n");
        }

        /// <summary>
        /// Creates a new unique filename from the given file path by adding a running index to the filename.
        /// </summary>
        /// <param name="filePath">File system path to modidy</param>
        /// <returns>File path appended with a running number or same path if it doesn't already exist</returns>
        private string newUniquePath(string filePath)
        {
            int index = 1;
            string directoryPath = System.IO.Path.GetDirectoryName(filePath) ?? "";
            string filenameNoExtension = System.IO.Path.GetFileNameWithoutExtension(filePath);
            string extension = System.IO.Path.GetExtension(filePath);
            string newPath = filePath;
            while (System.IO.File.Exists(newPath))
            {
                newPath = System.IO.Path.Combine(directoryPath, filenameNoExtension + index + extension);
                index++;
            }
            return newPath;
        }

        /// <summary>
        /// Helper method for outputting information messages.
        /// Given input is displayed at the GUI and saved to log file.
        /// Timestamp is inserted before the input.
        /// Extra new line characters are removed from the end of the input.
        /// </summary>
        /// <param name="lineToWrite">Message string to display and save.</param>
        private void WriteToLogs(string lineToWrite)
        {
            if (string.IsNullOrEmpty(lineToWrite)) return;

            this.WriteToLogs(new MarbleLogEntry(lineToWrite));
        }

        /// <summary>
        /// Helper method for outputting information messages.
        /// Given input is displayed at the GUI and saved to log file.
        /// Timestamp is inserted before the input.
        /// Extra new line characters are removed from the end of the input.
        /// </summary>
        /// <param name="logEntry">Marble log entry to display and save.</param>
        private void WriteToLogs(MarbleLogEntry logEntry)
        {
            lock (loggerLock)
            {
                if (logEntry == null) return;

                if (this.MarbleLogModel != null)
                {
                    this.MarbleLogModel.AddMarbleLogEntry(logEntry);
                }

                if (logger != null)
                    logger.WriteLine(
                        "{0:dd.MM.yyyy HH:mm:ss.fff} {1}", logEntry.TimeStamp, logEntry.OriginalMessage.TrimEnd('\n'));
            }
        }

        public void WriteTestDataToLogs(MarbleLogEntry logEntry)
        {
            //NOTE: REMOVE THIS!!!!

            this.WriteToLogs(logEntry);
        }

        private void randomizePorts()
        {
            dynamic settings = SettingsManager.Instance;
            // TCP port for GUI --> FW protocol and BLT-UE WCF service
            settings.System.GuiFrameworkProtocolPort = this.randomizePort(TransportType.Tcp, settings);
            settings.System.FrameworkGuiBltUeServicePort = this.randomizePort(TransportType.Tcp, settings);

            // UDP port for FW-->GUI Log4Net logger
            settings.System.FrameworkGuiLoggerPort = this.randomizePort(TransportType.Udp, settings);

            // Save settings
            SettingsManager.Instance.Save("System");
        }

        private int randomizePort(TransportType transportType, dynamic settings)
        {
            // Evaluate current system tcp connections. This is the same information provided
            // by the netstat command line application, just in .Net strongly-typed object
            // form.  We will look through the list, and if our port we would like to use
            // in our TcpClient is occupied, we will set isAvailable to false.
            IPGlobalProperties ipGlobalProperties = IPGlobalProperties.GetIPGlobalProperties();
            IPEndPoint[] ipEndpoints = transportType == TransportType.Tcp ? ipGlobalProperties.GetActiveTcpListeners() : ipGlobalProperties.GetActiveUdpListeners();

            // Select a random port from the private range 49152–65535
            Random rnd = new Random();
            while (true)
            {
                int randomPort = rnd.Next(49152, 65535);
                // Check that the newly generated random port number is not reserved for us
                if ((randomPort == settings.System.GuiFrameworkProtocolPort) || (randomPort == settings.System.FrameworkGuiBltUeServicePort) || (randomPort == settings.System.FrameworkGuiLoggerPort))
                    continue;

                bool isAvailable = ipEndpoints.All(ep => ep.Port != randomPort);
                if (isAvailable)
                    return randomPort;
            }
        }
    }

    #region Listener for Log4Net UDP logging

    public class Log4NetProvider
    {
        internal class LogEntry : INotifyPropertyChanged
        {
            public LogEntry()
            {
                Type = "DEBUG";
                DateTime = DateTime.Now;
                Description = "Fake Message";
                Source = "Fake source";
                System = "System";
                Thread = "123";
            }

            /// <summary>
            /// Classification for the log entry.  Can be free-text but will typically
            /// contain values like "DEBUG" or "ERROR".
            /// </summary>
            public string Type { get; set; }

            /// <summary>
            /// Date/Time for the original log entry.
            /// </summary>
            public DateTime DateTime { get; set; }

            /// <summary>
            /// The main body of the log entry.
            /// </summary>
            public string Description { get; set; }

            /// <summary>
            /// Source of the log entry, e.g. where it came from.
            /// </summary>
            public string Source { get; set; }

            /// <summary>
            /// The system (e.g. machine) where this message came from.
            /// </summary>
            public string System { get; set; }

            /// <summary>
            /// Thread identifier for the source of the message.
            /// </summary>
            public string Thread { get; set; }

            /// <summary>
            /// Dictionary of any meta-data that doesn't fit into the above values.
            /// </summary>
            public Dictionary<string, object> MetaData { get; set; }

            #region INotifyPropertyChanged Members

            public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

            private void OnPropertyChanged(string propertyName)
            {
                if (PropertyChanged != null)
                {
                    PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
                }
            }

            #endregion
        }

        protected readonly Queue<string> PendingQueue = new Queue<string>();

        private const int PumpFrequency = 100;

        private static readonly XmlNamespaceManager NamespaceManager = new XmlNamespaceManager(new NameTable());

        private readonly XNamespace log4Net = "unique";

        private CancellationTokenSource cancellationTokenSource;

        private Task udpListenerTask;

        private Connector marbleConnector;

        static Log4NetProvider()
        {
            NamespaceManager.AddNamespace("log4net", "http://logging.apache.org/log4net");
        }

        public Log4NetProvider(Connector marbleConnector, int clientPort)
        {
            this.Port = clientPort;
            this.marbleConnector = marbleConnector;
            this.Start();
        }
        

        public string Name { get; set; }

        public bool IsActive
        {
            get
            {
                return udpListenerTask != null && udpListenerTask.Status == TaskStatus.Running;
            }
        }

        public int Port { get; private set; }

        public void Start()
        {
            //Log.Debug("Start requested");

            if (udpListenerTask == null || udpListenerTask.IsCompleted)
            {
                cancellationTokenSource = new CancellationTokenSource();
                var token = cancellationTokenSource.Token;

                udpListenerTask = Task.Factory.StartNew(SocketListener, token);
                Task.Factory.StartNew(MessagePump, token);
            }
            else
            {
                //Log.Warn("UDP listener task is already active and can not be started again.");
            }
        }

        public void Close()
        {
            //Log.Debug("Close requested");
            if (cancellationTokenSource != null && !cancellationTokenSource.IsCancellationRequested)
            {
                //Log.Debug("Cancellation token triggered");
                cancellationTokenSource.Cancel();
            }
        }

        private void SocketListener()
        {
            //Log.Debug("SocketListener started");

            while (!cancellationTokenSource.IsCancellationRequested)
            {
                var endPoint = new IPEndPoint(IPAddress.Any, this.Port);

                using (var listener = new UdpClient(endPoint))
                {
                    while (!cancellationTokenSource.IsCancellationRequested)
                    {
                        var remoteEndPoint = new IPEndPoint(IPAddress.Any, 0);
                        listener.Client.ReceiveTimeout = 1000;
                        try
                        {
                            // No ongoing execution: Wait 250 ms before the next round - so process will not consume CPU time
                            if (this.marbleConnector.State == ConnectorState.Idle || this.marbleConnector.State == ConnectorState.FrameworkReady)
                                Thread.Sleep(250);
                            else
                                Thread.Sleep(10);

                            if (listener.Available <= 0)
                                continue;

                            var bytes = listener.Receive(ref remoteEndPoint);

                            //Log.Debug(string.Format("Received {0} bytes from {1}", bytes.Length, remoteEndPoint.Address));

                            var message = Encoding.UTF8.GetString(bytes, 0, bytes.Length);
                            lock (PendingQueue)
                            {
                                PendingQueue.Enqueue(message);
                            }
                        }
                        catch (SocketException socketException)
                        {
                            if (socketException.SocketErrorCode != SocketError.TimedOut)
                            {
                                //Log.Debug("SocketException", socketException);
                                //Log.DebugFormat(
                                //"SocketException.SocketErrorCode = {0}",
                                //socketException.SocketErrorCode);

                                // Break out of the 'using socket' loop and try to establish a new socket.
                                break;
                            }
                        }
                        catch (Exception e)
                        {
                            //Log.DebugFormat("Exception: {0}", e.Message);
                            // Break out of the 'using socket' loop and try to establish a new socket.
                            break;
                        }
                    }
                }
            }

            //Log.Debug("SocketListener completed");
        }

        private void MessagePump()
        {
            //Log.Debug("MessagePump started");

            while (!cancellationTokenSource.IsCancellationRequested)
            {
                Thread.Sleep(PumpFrequency);

                try
                {
                    lock (PendingQueue)
                    {
                        var processedQueue = new Queue<LogEntry>();

                        while (PendingQueue.Count > 0)
                        {
                            var message = PendingQueue.Dequeue();

                            if (IsValidMessage(message))
                            {
                                var deserializeMessage = DeserializeMessage(message);

                                if (deserializeMessage != null)
                                {
                                    processedQueue.Enqueue(deserializeMessage);
                                }
                            }
                        }

                        while (processedQueue.Count > 0)
                        {
                            LogEntry e = processedQueue.Dequeue();
                            if (e.Type == "ERROR" || e.Type == "FATAL")
                            {
                                this.marbleConnector.errorOutputHandler(e.Description);
                            }
                            else
                            {
                                ////this.marbleConnector.outputHandler(e.Description);

                                ////MarbleLogEntry marbleLogEntry = new MarbleLogEntry(e);

                                ////this.marbleConnector.MarbleLogModel.AddMarbleLogEntry(marbleLogEntry);
                                
                                this.marbleConnector.outputHandler(e);
                            }
                        }
                    }
                }
                catch (Exception e)
                {
                    //Log.Error("MessagePump failed", e);
                }
            }

            //Log.Debug("MessagePump completed");
        }

        private LogEntry DeserializeMessage(string message)
        {
            try
            {
                var payload = string.Format(@"<entry xmlns:log4net=""{0}"">{1}</entry>", log4Net, message);
                var element = XElement.Parse(payload);
                var entryEvent = element.Element(log4Net + "event");

                // Establish whether a sub-system seems to be defined.
                if (entryEvent != null)
                {
                    var description = entryEvent.Element(log4Net + "message").Value;

                    var classification = string.Empty;
                    var system = entryEvent.GetAttribute("logger", string.Empty);
                    var type = entryEvent.GetAttribute("level", string.Empty);
                    var host = string.Empty;

                    foreach (var propertyElement in entryEvent.Element(log4Net + "properties").Elements())
                    {
                        if (propertyElement.Name == log4Net + "data")
                        {
                            var name = propertyElement.GetAttribute("name", string.Empty);
                            var value = propertyElement.GetAttribute("value", string.Empty);

                            switch (name)
                            {
                                case "log4net:HostName":
                                    host = value;
                                    break;
                                default:
                                    //Log.WarnFormat("Found unknown property named '{0}' with value '{1}'", name, value);
                                    break;
                            }
                        }
                    }

                    var metaData = new Dictionary<string, object>();
                    metaData["Classification"] = classification;
                    metaData["Host"] = host;

                    AddExceptionIfFound(entryEvent, metaData);

                    var logEntry = new LogEntry
                    {
                        DateTime = entryEvent.GetAttributeDateTime("timestamp", DateTime.Now),
                        System = system,
                        Thread = entryEvent.GetAttribute("thread", string.Empty),
                        Description = description,
                        Type = type,
                        MetaData = metaData
                    };

                    return logEntry;
                }
            }
            catch (Exception e)
            {
                //Log.Error("DeserializeMessage: exception when processing incoming message", e);
            }

            return null;
        }

        private void AddExceptionIfFound(XElement entryEvent, Dictionary<string, object> metaData)
        {
            if (entryEvent == null)
            {
                throw new ArgumentNullException("entryEvent");
            }

            if (metaData == null)
            {
                throw new ArgumentNullException("metaData");
            }

            var exceptionElement = entryEvent.Element(log4Net + "exception");
            if (exceptionElement != null)
            {
                metaData["Exception"] = exceptionElement.Value;
            }
        }

        private bool IsValidMessage(string message)
        {
            if (string.IsNullOrWhiteSpace(message))
            {
                throw new ArgumentNullException("message");
            }

            return message.StartsWith("<log4net:event");
        }
    }

    public static class XElementHelpers
    {
        public static string GetAttribute(this XElement element, string attributeName, string defaultValue)
        {
            if (element == null)
            {
                throw new ArgumentNullException("element");
            }

            if (!element.HasAttributes)
            {
                return defaultValue;
            }

            var value = element.Attribute(attributeName);
            return value == null ? defaultValue : value.Value;
        }

        public static DateTime GetAttributeDateTime(this XElement element, string attributeName, DateTime defaultValue)
        {
            var value = element.GetAttribute(attributeName, string.Empty);

            var result = defaultValue;
            if (!string.IsNullOrWhiteSpace(value))
            {
                DateTime.TryParse(value, out result);
            }

            return result;
        }
    }

    #endregion
}
