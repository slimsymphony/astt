using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Management;
using System.Net.NetworkInformation;
using System.Threading;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Input;
using Marble.Views.Dialogs;
using MarbleLibrary;
using MediatorLib;

using Marble.Communication;
using Marble.Model;
using Marble.Utilities;
using Marble.Views;
using TestAutomation.Gui.Marble.IPC.Clients;
using TestAutomation.Gui.Marble.IPC.Interfaces;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;
using TestAutomation.HWController.Client;
using Application = System.Windows.Application;
using DataFormats = System.Windows.DataFormats;
using DragEventArgs = System.Windows.DragEventArgs;
using MessageBox = System.Windows.MessageBox;

namespace Marble.ViewModel
{
    using System.ComponentModel;
    using System.Text;
    using System.Windows.Media.Imaging;
    using System.Windows.Threading;

    using MarbleLibrary.Commands;
    using MarbleLibrary.Utilities;

    using Microsoft.Win32;
    using System.Windows.Data;
    using System.Collections.Specialized;
    using System.Threading.Tasks;
    using TestAutomation.Gui.Marble.Settings;
    using System.Net;
    using System.Net.Sockets;
    using Service;
    using TestAutomation.Remote.Shared;

    public class MarbleMainViewModel : MediatorModel, INotifyPropertyChanged, IDisposable
    {
        // Event which is invoked when test result has been handled (test case has finished).
        public static event EventHandler TestResultHandledEventHandler;

        // Event which is invoked when test reports tab needs initialization.
        public static event EventHandler TestReportsTabInitializationNeededEventHandler;

        #region Properties

        //public MarbleMainModel MarbleModel { get; set; }
        public MarbleTestSetModel TestSetModel { get; set; }

        public TestReportViewModel MainWindowTestReportViewModel { get; set; }
       
        public Connector MarbleConnector { get; set; }
        public FuseClient FuseClient { get; set; }
        private string TestSetXmlFile { get; set; }

        /// <summary>
        /// Flag to detect redundant dispose calls.
        /// </summary>
        private bool _disposed;

        /// <summary>
        /// Field for the name of the currently active view in UI.
        /// </summary>
        private string _activeView;

        /// <summary>
        /// Property for the name of the currently active view in UI.
        /// </summary>
        public string ActiveView
        {
            get { return _activeView; }
            set
            {
                if (_activeView != value)
                {
                    _activeView = value;
                    OnPropertyChanged("ActiveView");
                }
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the test run pause is requested.
        /// </summary>
        public bool IsTestRunPauseRequested
        {
            get
            {
                return this.isTestRunPauseRequested;
            }
            set
            {
                // When test run is paused, pause requests are not active.
                if (this.IsTestRunPaused && value) return;

                this.isTestRunPauseRequested = value;
                this.OnPropertyChanged("IsTestRunPauseRequested");

                this.MarbleConnector.RaiseConnectorStatePropertyChanged();
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether black box icon should be visible
        /// </summary>
        private bool isIoWarriorHwForBlackBoxAvailable;
        public bool IsIoWarriorHWForBlackBoxAvailable
        {
            get { return this.isIoWarriorHwForBlackBoxAvailable; }
            private set
            {
                this.isIoWarriorHwForBlackBoxAvailable = value;
                this.OnPropertyChanged("IsIoWarriorHWForBlackBoxAvailable");
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the test run is paused.
        /// </summary>
        public bool IsTestRunPaused
        {
            get
            {
                return this.isTestRunPaused;
            }
            set
            {
                
                this.isTestRunPaused = value;

                // Pause request is not active when test run is paused.
                if (value)
                    this.isTestRunPauseRequested = false;

                this.OnPropertyChanged("IsTestRunPaused");

                this.MarbleConnector.RaiseConnectorStatePropertyChanged();
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the test run execution is stopping.
        /// </summary>
        public bool StoppingExecution
        {
            get
            {
                return this.stoppingExecution;
            }
            set
            {
                this.stoppingExecution = value;
                this.OnPropertyChanged("StoppingExecution");

                this.MarbleConnector.RaiseConnectorStatePropertyChanged();
            }
        }

        private bool isWhiteboxHeaderSplitButtonCheckBoxChecked;
        /// <summary>
        /// Property for Test Lab DataGrid header SplitButton CheckBox checked status.
        /// </summary>
        public bool IsWhiteboxHeaderSplitButtonCheckBoxChecked
        {
            get { return this.isWhiteboxHeaderSplitButtonCheckBoxChecked; }
            set
            {
                if (this.isWhiteboxHeaderSplitButtonCheckBoxChecked == value) return;

                this.isWhiteboxHeaderSplitButtonCheckBoxChecked = value;
                this.OnPropertyChanged("IsWhiteboxHeaderSplitButtonCheckBoxChecked");

                // Set value to all root test cases
                foreach (var testcase in this.TestSetModel.TestCases.Where(tc => tc.IsRoot && tc.IsWhiteboxChecked != value))
                    testcase.IsWhiteboxChecked = value;
            }
        }

        private bool isBlackboxHeaderSplitButtonCheckBoxChecked;

        /// <summary>
        /// Property for Test Lab DataGrid header SplitButton CheckBox checked status.
        /// </summary>
        public bool IsBlackboxHeaderSplitButtonCheckBoxChecked
        {
            get { return this.isBlackboxHeaderSplitButtonCheckBoxChecked; }
            set
            {
                if (this.isBlackboxHeaderSplitButtonCheckBoxChecked == value) return;

                this.isBlackboxHeaderSplitButtonCheckBoxChecked = value;
                this.OnPropertyChanged("IsBlackboxHeaderSplitButtonCheckBoxChecked");

                // Set value to all root test cases
                foreach (var testcase in this.TestSetModel.TestCases.Where(tc => tc.IsRoot && tc.IsBlackboxChecked != value))
                    testcase.IsBlackboxChecked = value;
            }
        }

        private bool isBlackboxInitStarted;

        /// <summary>
        /// Gets a value indicating whether Blackbox init has started.
        /// </summary>
        public bool IsBlackboxInitStarted
        {
            get
            {
                return this.isBlackboxInitStarted;
            }
            private set
            {
                this.isBlackboxInitStarted = value;
                this.OnPropertyChanged("IsBlackboxInitStarted");
            }
        }

        private bool isBlackboxCheckBoxesEnabled;

        /// <summary>
        /// Gets or sets a value indicating whether the check boxes for Blackbox are enabled.
        /// </summary>
        public bool IsBlackboxCheckBoxesEnabled
        {
            get
            {
                return this.isBlackboxCheckBoxesEnabled;
            }
            set
            {
                this.isBlackboxCheckBoxesEnabled = value;
                this.OnPropertyChanged("IsBlackboxCheckBoxesEnabled");
                this.OnPropertyChanged("CanWhiteboxCheckBoxesBeEnabled");

                if (!value)
                {
                    this.IsWhiteboxCheckBoxesEnabled = true;

                    // When Blackbox check boxes are hidden every Blackbox check box is unchecked.
                    foreach (TestCase testCase in this.TestSetModel.TestCases)
                    {
                        testCase.IsBlackboxChecked = false;
                    }
                }
            }
        }

        private bool isWhiteboxCheckBoxesEnabled;

        /// <summary>
        /// Gets or sets a value indicating whether the check boxes for Whitebox are enabled.
        /// </summary>
        public bool IsWhiteboxCheckBoxesEnabled
        {
            get
            {
                return this.isWhiteboxCheckBoxesEnabled;
            }
            set
            {
                if (!this.IsBlackboxCheckBoxesEnabled && !value) return;

                this.isWhiteboxCheckBoxesEnabled = value;
                this.OnPropertyChanged("IsWhiteboxCheckBoxesEnabled");

                if (!value)
                {
                    // When Whitebox check boxes are hidden every Whitebox check box is unchecked.
                    foreach (TestCase testCase in this.TestSetModel.TestCases)
                    {
                        testCase.IsWhiteboxChecked = false;
                    }
                }
            }
        }

        private bool isTracingEnabledForTestrun;

        /// <summary>
        /// Gets or sets a value indicating whether the tracing is enabled for the testrun.
        /// </summary>
        public bool IsTracingEnabledForTestrun
        {
            get
            {
                return this.isTracingEnabledForTestrun;
            }
            set
            {
                this.isTracingEnabledForTestrun = value;
                this.OnPropertyChanged("IsTracingEnabledForTestrun");
                if (this.IsTracingEnabledForTestrun)
                    this.IsMemoryLeakTestingEnabledForTestrun = false;
            }
        }

        private string traceXmlPath;

        /// <summary>
        /// File system path of the selected xml file used for activating traces.
        /// </summary>
        public string TraceXmlPath
        {
            get
            {
                return this.traceXmlPath;
            }
            set
            {
                this.traceXmlPath = value;
                this.OnPropertyChanged("IsTracingEnabledForTestrun");
            }
        }

        private bool isMemoryLeakTestingEnabledForTestrun;

        /// <summary>
        /// Gets or sets a value indicating whether the memory leak testing is enabled for the testrun.
        /// </summary>
        public bool IsMemoryLeakTestingEnabledForTestrun
        {
            get
            {
                return this.isMemoryLeakTestingEnabledForTestrun;
            }
            set
            {
                this.isMemoryLeakTestingEnabledForTestrun = value;
                this.OnPropertyChanged("IsMemoryLeakTestingEnabledForTestrun");
                if (this.IsMemoryLeakTestingEnabledForTestrun)
                    this.IsTracingEnabledForTestrun = false;
            }
        }

        /// <summary>
        /// Setting to control whether setup and teardown will be skipped on test case execution.
        /// </summary>
        public bool IsSetupAndTearDownDisabled { get; set; }

        public bool CanWhiteboxCheckBoxesBeEnabled { get { return true; } }

        public bool CanBlackboxCheckBoxesBeEnabled
        {
            get
            {
                return App.BlackBoxViewModel != null && App.BlackBoxViewModel.IsBlackBoxReady;
            }
        }

        private string _marbleApplicationTitleText;
        /// <summary>
        /// Property for storing Marble Application Title Text.
        /// </summary>
        public string MarbleApplicationTitleText
        {
            get { return _marbleApplicationTitleText; }
            set
            {
                if (_marbleApplicationTitleText != value)
                {
                    _marbleApplicationTitleText = value;
                    OnPropertyChanged("MarbleApplicationTitleText");
                }
            }
        }

        #endregion

        // Test Lab commands.
        //private DelegateCommand<RoutedEventArgs> _headerCheckBoxChecked;
        //private DelegateCommand<RoutedEventArgs> _headerCheckBoxUnChecked;
        private DelegateCommand<TestCase> _headerCheckBoxChecked;
        private DelegateCommand<TestCase> _headerCheckBoxUnChecked;
        private DelegateCommand<TestCase> headerBlackboxCheckBoxChecked;
        private DelegateCommand<TestCase> headerBlackboxCheckBoxUnChecked;
        private DelegateCommand<EventBehaviourArgs> _dataGridDrop;
        private DelegateCommand<string> _totalRunCountTextBoxCommand;
        private DelegateCommand<string> _totalRunCountHeaderTextBoxCommand;
        private DelegateCommand<TestCase> _testLabRowExpander;
        private DelegateCommand _editSelectedTest;
       
        // RibbonButton related commands.
        private DelegateCommand _newTestsetFile;
        private DelegateCommand _newTestRun;
        private DelegateCommand _openTestsetFile;
        private DelegateCommand _saveTestsetFile;
        private DelegateCommand _saveAsTestsetFile;
        private DelegateCommand _showReport;
        private DelegateCommand _emailReport;
        private DelegateCommand _showConnectionWindow;
        private DelegateCommand _runTestSet;
        private DelegateCommand stopTestRunCommand;
        private DelegateCommand _showExecutorWindow;
        private DelegateCommand _showCaptureTool;

        // Main window commands.
        private DelegateCommand _mainWindowClosing;

        private Process reportGenerator;
#if FRAMEWORK_SUPPORTS_MARBLE_SETTINGS_DIRECTORY
        /// <summary>
        /// Dynamic settings manager object used to access any settings
        /// </summary>
        private dynamic settings;

        /// <summary>
        /// Task used when loading the settings asynchronously.
        /// </summary>
        Task _loadSettingsTask;
#else
        public SettingsModel settingsModel;
#endif
        private Process webBrowser;
        public Executor logWindow;
        public ConnectionSelectionWindow connectionWindow;
        private CaptureTool captureTool;

        private Window marbleWikiWindow;
        private Window blackBoxWindow;

        const int LogBuilderSize = 131072;
        private System.Text.StringBuilder outputLogBuilder;
        private System.Text.StringBuilder traceLogBuilder;

        private bool stoppingExecution;

        private string marbleVersion;

        internal bool debugMode;

        private RemoteBoxInfo RemoteboxService;

        public DeviceCollection DeviceCollection { get; set; }

        /// <summary>
        /// Gets command for checking the CheckBox in the first column of row.
        /// </summary>
        public ICommand GridRowCheckBoxCheckedCommand
        {
            get
            {
                if (this._headerCheckBoxChecked == null)
                {
                    this._headerCheckBoxChecked = new DelegateCommand<TestCase>(this.GridRowCheckBoxCheckExecuted, this.GridRowCheckBoxCheckCanExecute);
                }

                return this._headerCheckBoxChecked;
            }
        }

        /// <summary>
        /// Gets command for unchecking the CheckBox in the first column of row.
        /// </summary>
        public ICommand GridRowCheckBoxUnCheckedCommand
        {
            get
            {
                if (this._headerCheckBoxUnChecked == null)
                {
                    this._headerCheckBoxUnChecked = new DelegateCommand<TestCase>(this.GridRowCheckBoxUnCheckExecuted, this.GridRowCheckBoxUnCheckCanExecute);
                }

                return this._headerCheckBoxUnChecked;
            }
        }

        /// <summary>
        /// Gets command for checking the CheckBox in the Blackbox column.
        /// </summary>
        public ICommand TestCaseBlackboxCheckBoxCheckedCommand
        {
            get
            {
                if (this.headerBlackboxCheckBoxChecked == null)
                {
                    this.headerBlackboxCheckBoxChecked = new DelegateCommand<TestCase>(this.TestCaseBlackboxCheckBoxCheckExecuted, this.TestCaseBlackboxCheckBoxCheckCanExecute);
                }

                return this.headerBlackboxCheckBoxChecked;
            }
        }

        /// <summary>
        /// Gets command for unchecking the CheckBox in the Blackbox column.
        /// </summary>
        public ICommand TestCaseBlackboxCheckBoxUnCheckedCommand
        {
            get
            {
                if (this.headerBlackboxCheckBoxUnChecked == null)
                {
                    this.headerBlackboxCheckBoxUnChecked = new DelegateCommand<TestCase>(this.TestCaseBlackboxCheckBoxUnCheckExecuted, this.TestCaseBlackboxCheckBoxUnCheckCanExecute);
                }

                return this.headerBlackboxCheckBoxUnChecked;
            }
        }

        /// <summary>
        /// Gets command DataGrip Drop event.
        /// </summary>
        public ICommand DataGridDropCommand
        {
            get
            {
                if (this._dataGridDrop == null)
                {
                    this._dataGridDrop = new DelegateCommand<EventBehaviourArgs>(this.DataGridDropCommandExecuted, this.DataGridDropCommandCanExecute);
                }

                return this._dataGridDrop;
            }
        }

        /// <summary>
        /// Command for changing the run count of test case according to value in TextBox.
        /// </summary>
        public ICommand TotalRunCountTextBoxCommand
        {
            get
            {
                if (_totalRunCountTextBoxCommand == null)
                {
                    _totalRunCountTextBoxCommand = new DelegateCommand<string>(TotalRunCountTextBoxCommandExecuted, TotalRunCountTextBoxCommandCanExecute);
                }

                return _totalRunCountTextBoxCommand;
            }
        }

        /// <summary>
        /// Command for expanding/collapsing the result column tree.
        /// </summary>
        public ICommand TestLabRowExpanderCommand
        {
            get
            {
                if (_testLabRowExpander == null)
                {
                    _testLabRowExpander = new DelegateCommand<TestCase>(TestLabRowExpanderCommandExecuted, TestLabRowExpanderCommandCanExecute);
                }

                return _testLabRowExpander;
            }
        }

        /// <summary>
        /// Command for editing the selected test.
        /// </summary>
        public ICommand EditSelectedTestCommand
        {
            get
            {
                if (_editSelectedTest == null)
                {
                    _editSelectedTest = new DelegateCommand(EditSelectedTestCommandExecuted, EditSelectedTestCommandCanExecute);
                }

                return _editSelectedTest;
            }
        }

        /// <summary>
        /// Command for running the selected test cases.
        /// </summary>
        public ICommand RunTestSetCommand
        {
            get
            {
                if (this._runTestSet == null)
                {
                    this._runTestSet = new DelegateCommand(this.RunTestSetCommandExecuted, this.RunTestSetCommandCanExecute);
                }

                return this._runTestSet;
            }
        }

        public ICommand StopTestRunCommand
        {
            get
            {
                if (this.stopTestRunCommand == null)
                {
                    this.stopTestRunCommand = new DelegateCommand(this.StopTestSetCommandExecuted, this.StopTestRunCommandCanExecute);
                }

                return this.stopTestRunCommand;
            }
        }

        /// <summary>
        /// Command for creating new empty testset file.
        /// </summary>
        public ICommand NewTestsetFileCommand
        {
            get
            {
                if (_newTestsetFile == null)
                {
                    _newTestsetFile = new DelegateCommand(NewTestsetFileCommandExecuted, NewTestsetFileCommandCanExecute);
                }

                return _newTestsetFile;
            }
        }

        /// <summary>
        /// Command for creating new empty testset file.
        /// </summary>
        public ICommand NewTestRunCommand
        {
            get
            {
                if (_newTestRun == null)
                    _newTestRun = new DelegateCommand(NewTestRunCommandExecuted, NewTestRunCommandCanExecute);

                return _newTestRun;
            }
        }

        /// <summary>
        /// Command for opening testset file.
        /// </summary>
        public ICommand OpenTestsetFileCommand
        {
            get
            {
                if (_openTestsetFile == null)
                {
                    _openTestsetFile = new DelegateCommand(OpenTestsetFileCommandExecuted, OpenTestsetFileCommandCanExecute);
                }

                return _openTestsetFile;
            }
        }

        /// <summary>
        /// Command for saving testset file.
        /// </summary>
        public ICommand SaveTestsetFileCommand
        {
            get
            {
                if (_saveTestsetFile == null)
                {
                    _saveTestsetFile = new DelegateCommand(SaveTestsetFileCommandExecuted, SaveTestsetFileCommandCanExecute);
                }

                return _saveTestsetFile;
            }
        }

        /// <summary>
        /// Command for saving testset file with name.
        /// </summary>
        public ICommand SaveAsTestsetFileCommand
        {
            get
            {
                if (_saveAsTestsetFile == null)
                {
                    _saveAsTestsetFile = new DelegateCommand(SaveAsTestsetFileCommandExecuted, SaveAsTestsetFileCommandCanExecute);
                }

                return _saveAsTestsetFile;
            }
        }

        /// <summary>
        /// Command for showing report.
        /// </summary>
        public ICommand ShowReportCommand
        {
            get
            {
                if (_showReport == null)
                {
                    _showReport = new DelegateCommand(ShowReportCommandExecuted, ShowReportCommandCanExecute);
                }

                return _showReport;
            }
        }

        /// <summary>
        /// Command for emailing report.
        /// </summary>
        public ICommand EmailReportCommand
        {
            get
            {
                if (_emailReport == null)
                {
                    _emailReport = new DelegateCommand(EmailReportCommandExecuted, EmailReportCommandCanExecute);
                }

                return _emailReport;
            }
        }

        /// <summary>
        /// Command for showing the connection window.
        /// </summary>
        public ICommand ShowConnectionWindowCommand
        {
            get
            {
                if (_showConnectionWindow == null)
                {
                    _showConnectionWindow = new DelegateCommand(ShowConnectionWindowCommandExecuted, ShowConnectionWindowCommandCanExecute);
                }

                return _showConnectionWindow;
            }
        }

        /// <summary>
        /// Command for showing the executor window.
        /// </summary>
        public ICommand ShowExecutorWindowCommand
        {
            get
            {
                if (_showExecutorWindow == null)
                {
                    _showExecutorWindow = new DelegateCommand(ShowExecutorWindowCommandExecuted, ShowExecutorWindowCommandCanExecute);
                }

                return _showExecutorWindow;
            }
        }

        /// <summary>
        /// Command for showing the capture tool.
        /// </summary>
        public ICommand ShowCaptureToolCommand
        {
            get
            {
                if (_showCaptureTool == null)
                {
                    _showCaptureTool = new DelegateCommand(ShowCaptureToolCommandExecuted, ShowCaptureToolCommandCanExecute);
                }

                return _showCaptureTool;
            }
        }

        private DelegateCommand updateDevices;

        /// <summary>
        /// Command for re-creating the device listener.
        /// </summary>
        public ICommand UpdateDevicesCommand
        {
            get
            {
                if (updateDevices == null)
                {
                    updateDevices = new DelegateCommand(UpdateDevicesCommandExecuted, UpdateDevicesCommandCanExecute);
                }

                return updateDevices;
            }
        }

        /// <summary>
        /// Check to see if UpdateDevicesCommand can be run.
        /// </summary>
        public bool UpdateDevicesCommandCanExecute()
        {
            return true;
        }

        /// <summary>
        /// Re-creates the device listener.
        /// </summary>
        public void UpdateDevicesCommandExecuted()
        {
            this.DeviceCollection.ReCreateListener();
        }

        private DelegateCommand<string> disableLockScreen;

        /// <summary>
        /// 
        /// </summary>
        public ICommand DisableLockScreen
        {
            get
            {
                if (disableLockScreen == null)
                    disableLockScreen = new DelegateCommand<string>(DisableLockScreenCommandExecuted, DisableLockScreenCommandCanExecute);

                return disableLockScreen;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public bool DisableLockScreenCommandCanExecute(string serialNumber)
        {
            return true;
        }

        /// <summary>
        /// 
        /// </summary>
        public void DisableLockScreenCommandExecuted(string serialNumber)
        {
            if (string.IsNullOrEmpty(serialNumber)) return;

            var device = this.DeviceCollection.FirstOrDefault(d => d.SerialNumber == serialNumber);
            if (device == null) return;

            var reply = MessageBox.Show("Are you sure you want to disable security lock and boot the device?\nThis operation will take a while and can not be undone.",
                            "Disable security lock?",
                            MessageBoxButton.YesNo, MessageBoxImage.Question);

            if (reply != MessageBoxResult.Yes) return;

            device.IsMain = true;
            this.UpdateSettings();
            this.ShowExecutorWindowCommandExecuted();
            this.MarbleConnector.AddToQueue(new DisableLockScreen());
        }

        public ObservableCollectionAdv<TestCase> SelectedTestCases { get; private set; }

        public TestCase SelectedTestCase { get { return this.SelectedTestCases.FirstOrDefault(); } }

        /// <summary>
        /// Gets all first level Test Cases which are selected.
        /// </summary>
        public IEnumerable<TestCase> SelectedFirstLevelTestCases
        {
            get { return this.SelectedTestCases.Where(tc => tc.Level == 1); }
        }

        /// <summary>
        /// Gets the enum indicating the status of currently selected report(s).
        /// </summary>
        public SelectedReportsEnum SelectedReportsStatus
        {
            get
            {
                int testCaseCheckedCount = this.TestSetModel.TestCases.Count(testCase => testCase.IsWhiteboxChecked || testCase.IsBlackboxChecked);

                if (testCaseCheckedCount <= 0) 
                    return SelectedReportsEnum.None;

                bool containsPassedTests = false;

                foreach (TestCase testCase in this.TestSetModel.TestCases)
                {
                    if (!testCase.IsWhiteboxChecked || !testCase.IsBlackboxChecked) continue;

                    switch (testCase.Result.Result)
                    {
                        case "Failed":
                        case "Failed in tearDown":
                        case "Failed in setUp":
                            if (testCaseCheckedCount == 1)
                                return SelectedReportsEnum.FailedReport;
                            if (testCaseCheckedCount > 1)
                                return SelectedReportsEnum.MultipleContainingFailedReport;
                            break;
                        case "Passed":
                            containsPassedTests = true;
                            if (testCaseCheckedCount == 1)
                                return SelectedReportsEnum.PassedReport;
                            break;
                        case "No Result":
                        case "No Run":
                            if (testCaseCheckedCount == 1)
                                return SelectedReportsEnum.UnresolvedReport;
                            break;
                    }
                }

                if (containsPassedTests && testCaseCheckedCount > 1)
                    return SelectedReportsEnum.MultipleAllPassedReports;
                
                return SelectedReportsEnum.None;
            }
        }

        /// <summary>
        /// Begins loading of settings asynchronously.
        /// </summary>
        public void StartLoadingSettings()
        {
            string settingsDirectory = Path.GetFullPath(@"..\settings");
            _loadSettingsTask = SettingsManager.Instance.BeginLoadSettingsFromDirectory(settingsDirectory);
            MarbleConnector.SettingsDirectory = settingsDirectory;
            _loadSettingsTask.ContinueWith(continuation  =>
            {
                this.CheckHWControllerTypeAndAvailability();
                this.updateWindowTitle();
                this.StartVideoRecorderIfEnabled();
                return StartRemoteBox();
            });
        }

        /// <summary>
        /// Start remotebox service locally if defined in settings.
        /// 
        /// Remotebox is service which handles communication between Marble and NG Phone used as remote phone.
        /// </summary>
        /// <returns>true if service is started. Otherwise returns false.</returns>
        private bool StartRemoteBox()
        {
            if (settings.System.RemoteBoxAddress == "localhost")
            {
                //Start RemoteBox service if needed
                // Find port
                int port = FindPort();
                settings.System.RemoteBoxPort = port;
                NgBox box = new NgBox();
                box.BoxConfPath = @"..\settings\sim_info.xml";
                RemoteboxService = RemoteBox.StartHosting(box, port, "NgBox");

                Debug.WriteLine("Start RemoteBox service");
                Debug.Flush();
                return true;
            }
            return false;
        }

        private static readonly object DevicesCollectionLock = new object();

        /// <summary>
        /// Constructor for the <see cref="MarbleMainViewModel"/> object.
        /// </summary>
        public MarbleMainViewModel()
        {
            Debug.Indent();
            Debug.WriteLine("BeginVersion");
            this.marbleVersion = GetMarbleVersion();
            // Disabled for Marble Aol.
            //UltimaUsageLogger.SendMarbleUsageToUltima(this.marbleVersion);
            Debug.WriteLine("EndVersion");
            Debug.Flush();
            this.FuseClient = new FuseClient(Application.Current.Dispatcher);
            Debug.WriteLine("FuseClient");
            Debug.Flush();
            this.MarbleConnector = new Connector(Application.Current.Dispatcher, AppendText);
            Debug.WriteLine("Connector");
            Debug.Flush();

#if FRAMEWORK_SUPPORTS_MARBLE_SETTINGS_DIRECTORY
            // Allow any settings to be updated
            SettingsManager.Instance.ReadOnly = false;

            // Store the settings manager instance as a dynamic object
            settings = SettingsManager.Instance;

            Debug.WriteLine("SettingsManager");
            Debug.Flush();
#else
            settingsModel = new SettingsModel(@"..\settings\default.settings");

            // Save default settings to a new file
            settingsModel.Save(System.IO.Path.GetFullPath(@"..\settings\modified.settings"));
            MarbleConnector.SettingsPath = settingsModel.DocumentPath;
#endif

            this.SelectedTestCases = new ObservableCollectionAdv<TestCase>();

            // Register all decorated methods to the Mediator.
            Mediator.Register(this);

            TestSetModel = new MarbleTestSetModel(string.Empty);
            this.NewTestsetFileCommandExecuted();
            this.TestSetModel.IsChanged = false;

            this.IsTimedRunStartedForUi = this.TestSetModel.TimedRunEnabled;
            this.CurrentTestRuntimeUnit = this.TestSetModel.CurrentTestRuntimeUnit;
            this.TestSetRepeatTimeForUi = this.TestSetModel.TestSetRepeatTime;

            Debug.WriteLine("SettingsModel");
            Debug.Flush();

            this.TestSetModel.TestCases.CollectionChanged += OnTestCasesCollectionChanged;

            //settings = new SettingsModel(@"..\settings\default.settings");
            TestSetModel.CurrentIndex = -1;
            outputLogBuilder = new System.Text.StringBuilder(LogBuilderSize);
            traceLogBuilder = new System.Text.StringBuilder(LogBuilderSize);

            TestSetModel.TestRunProgressValue = 0;

            this.UpdateStatusBar();

            this.IsWhiteboxCheckBoxesEnabled = true;

            this.InitializeTestExecutionDispatcherTimer();
            this.DeviceCollection = new DeviceCollection();
            BindingOperations.EnableCollectionSynchronization(this.DeviceCollection, DevicesCollectionLock);
        }

        /// <summary>
        /// Destructor for the <see cref="MarbleMainViewModel"/> object.
        /// </summary>
        ~MarbleMainViewModel()
        {
            if (RemoteboxService != null)
                RemoteboxService.Close();
            Dispose(false);
        }

        private static int FindPort()
        {
            var endPoint = new IPEndPoint(IPAddress.Any, 0);

            using (Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                socket.Bind(endPoint);
                IPEndPoint local = (IPEndPoint)socket.LocalEndPoint;
                return local.Port;
            }
        }

        /// <summary>
        /// Reads version string from the Marble version file
        /// </summary>
        /// <returns>Version string that is at maximum 40 chars long</returns>
        private static string GetMarbleVersion()
        {
            string version = "Marble - Version not available";

            // Version file not found
            if (!File.Exists(FileUtilities.VersionFilePath)) return version;

            try
            {
                version = File.ReadAllText(FileUtilities.VersionFilePath);
            }
            catch (IOException) {}

            // Limit the length to 40 characters at maximum
            return version.Length > 40 ? version.Substring(0, 40) : version;
        }

        /// <summary>
        /// Updates test case result counts in status bar.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void OnTestCasesCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            this.UpdateStatusBar();
            
        }

        /// <summary>
        /// Updates the test case statuses in the status bar.
        /// </summary>
        public void UpdateStatusBar()
        {
            TestSetModel.PassedTestCases = 0;
            TestSetModel.NoResultTestCases = 0;
            TestSetModel.FailedTestCases = 0;

            if (this.TestSetModel.TestCases != null)
            {
                foreach (TestCase testCase in this.TestSetModel.TestCases.Where(tc => tc.IsRoot))
                {
                    this.UpdateResultCount(testCase.Result.Result);
                }
            }
        }

        /// <summary>
        /// Updates the test case status counts. This is called from TestCase result modifications.
        /// </summary>
        [MediatorMessageSink("UpdateStatusBar", ParameterType = typeof(TestCase))]
        public void UpdateStatusBar(TestCase testCase)
        {
            if (this.TestSetModel == null || this.TestSetModel.TestCases == null || testCase == null)
                return;

            // Remove previous result
            this.UpdateResultCount(testCase.Result.PreviousResult, false);
            // Add new result
            this.UpdateResultCount(testCase.Result.Result);
        }

        /// <summary>
        /// Adds or subtracts given result to specific test case summary count
        /// (Passed, Failed or No result test cases).
        /// </summary>
        /// <param name="result">Result value to add or subtract</param>
        /// <param name="add">Whether to add or subtract</param>
        private void UpdateResultCount(string result, bool add=true)
        {
            int change = add ? 1 : -1;

            if (result.ToLower() == "passed")
                this.TestSetModel.PassedTestCases += change;
            else if (string.IsNullOrEmpty(result) || result.ToLower() == "no result" || result.ToLower() == "no run")
                this.TestSetModel.NoResultTestCases += change;
            else if (result.ToLower().StartsWith("failed") || result.ToLower() == "error")
                this.TestSetModel.FailedTestCases += change;
        }

        /// <summary>
        /// Updates the provided cases status to status bar.
        /// </summary>
        /// <param name="testCase">TestCase object</param>
        /// <param name="subtract">Whether to subtract</param>
        public void UpdateStatusBar(TestCase testCase, bool subtract)
        {
            var result = TestSetModel.TestCases.Where(item => item.Name.Equals(testCase.Name));

            foreach (TestCase item in result)
            {
                if (item.IsRoot)
                {
                    if (item.Result.Result == "Passed")
                    {
                        if (subtract)
                            TestSetModel.PassedTestCases -= 1;
                        else
                            TestSetModel.PassedTestCases += 1;
                    }
                    else if (item.Result.Result == "No Result"
                        || item.Result.Result == "No Run"
                        || item.Result.Result == string.Empty)
                    {
                        if (subtract)
                            TestSetModel.NoResultTestCases -= 1;
                        else
                            TestSetModel.NoResultTestCases += 1;
                    }
                    else
                    {
                        if (subtract)
                            TestSetModel.FailedTestCases -= 1;
                        else
                            TestSetModel.FailedTestCases += 1;
                    }
                }
            }
        }

        /// <summary>
        /// Calls OnPropertyChanged for all Connector related properties to refresh GUI.
        /// </summary>
        public void UpdateConnectorRelatedProperties()
        {
            this.OnPropertyChanged("IsTestRunPaused");
            this.OnPropertyChanged("IsTestRunPauseRequested");
            this.OnPropertyChanged("StoppingExecution");
        }

        /// <summary>
        /// Helper function to check if collection is empty or null.
        /// </summary>
        /// <param name="collection">either of type ObservableCollection or ObservableCollectionAdv</param>
        /// <returns>true if collection is empty or null</returns>
        public bool IsCollectionEmptyOrNull(dynamic collection)
        {
            if (collection == null || collection.Count == 0)
                return true;
            
            return false;
        }

        /// <summary>
        /// Helper function to add a text string to the end of the GUI log
        /// </summary>
        /// <param name="text">Text string to add to the log</param>
        /// <param name="logIndex">To which log the text is added. 1=Framework output, 2=Trace output</param>
        public void AppendText(String text, int logIndex = 1)
        {
            return;

            ////if (this.logWindow == null)
            ////    return;

            ////// status updates and framework output
            ////if (logIndex < 2)
            ////{
            ////    // remove lines from the buffer if needed
            ////    if (this.outputLogBuilder.Length + text.Length > outputLogBuilder.Capacity)
            ////    {
            ////        // remove about 50%  from the beginning
            ////        double cutSize = this.outputLogBuilder.Length * 0.5;
            ////        this.outputLogBuilder.Remove(0, this.outputLogBuilder.ToString().IndexOf('\n', (int)cutSize) + 1);
            ////    }
            ////    this.outputLogBuilder.Append(text);

            ////    // display buffer contents and scroll to the end
            ////    this.logWindow.frameworkOutput.Text = this.outputLogBuilder.ToString();
            ////    ////this.logWindow.frameworkLogScroller.ScrollToBottom();
            ////    this.logWindow.frameworkOutput.ScrollToEnd();
                
            ////    // NOTE: Add better scrolling logic.
            ////    ////if (this.logWindow.frameworkOutput.TextArea.TextView.VerticalOffset 
            ////    ////    + this.logWindow.frameworkOutput.TextArea.TextView.ActualHeight + 32 >= 
            ////    ////    this.logWindow.frameworkOutput.TextArea.TextView.DocumentHeight)
            ////    ////    this.logWindow.frameworkOutput.ScrollToEnd();
            ////}

            //////trace output
            ////else
            ////{
            ////    // remove lines from the buffer if needed
            ////    if (this.traceLogBuilder.Length + text.Length > traceLogBuilder.Capacity)
            ////    {
            ////        // remove about 50%  from the beginning
            ////        double cutSize = this.traceLogBuilder.Length * 0.5;
            ////        this.traceLogBuilder.Remove(0, this.traceLogBuilder.ToString().IndexOf('\n', (int)cutSize) + 1);
            ////    }
            ////    this.traceLogBuilder.Append(text);

            ////    // display buffer and scroll to the end
            ////    this.logWindow.traceLogOutput.Text = this.traceLogBuilder.ToString();
            ////    ////this.logWindow.traceLogScroller.ScrollToBottom();
            ////    this.logWindow.traceLogOutput.ScrollToEnd();
            ////}
        }

        // TODO: change fromAll to false, when reporting is fixed
        public void GenerateReports(bool showReport, bool fromAll = false)
        {
            if (reportGenerator != null)
            {
                reportGenerator.Dispose();
            }

            // start report generator process
            reportGenerator = new Process();
            reportGenerator.StartInfo.FileName = "ipy";

            string testsetDir = System.IO.Path.GetDirectoryName(TestSetModel.DocumentPath);
            string testsetName = System.IO.Path.GetFileNameWithoutExtension(TestSetModel.DocumentPath);
            string resultPath = System.IO.Path.Combine(testsetDir, testsetName + "_results");
            string reportPath = System.IO.Path.Combine(resultPath, "xml");

            // all test cases
            if (fromAll)
            {
                
            }

            // TODO: finish this
            // multiple test cases
            //else if (TestSetModel.SelectedTestCaseList.Count > 0)

            // single test case
            else if (this.SelectedTestCase != null && !String.IsNullOrEmpty(this.SelectedTestCase.Result.ResultPath))
            {
                reportPath = System.IO.Path.Combine(testsetDir, this.SelectedTestCase.Result.ResultPath);
            }

            string arguments = String.Format("\"{0}\" \"{1}\" \"{2}\"",
                System.IO.Path.GetFullPath(@"..\framework\core\reporting\xslt_report_generator.py"),
                reportPath,
                resultPath);

            // TODO catch ipy not found exception
            reportGenerator.StartInfo.Arguments = arguments;
            reportGenerator.StartInfo.WorkingDirectory = System.IO.Path.GetFullPath(@"..\framework");
            reportGenerator.Start();
            reportGenerator.WaitForExit();

            if (showReport)
            {
                // TODO inform user if html was not generated
                string htmlPath = System.IO.Path.Combine(resultPath, "test_report_main.html");
                if (System.IO.File.Exists(htmlPath))
                {
                    if (webBrowser != null)
                    {
                        webBrowser.Dispose();
                    }

                    // open report with a default program for html files
                    webBrowser = new Process();
                    webBrowser.StartInfo.FileName = System.IO.Path.Combine(resultPath, "test_report_main.html");
                    webBrowser.Start();
                }
            }
        }

        /// <summary>
        /// Callback for a command when Core Test Tool (CTT) or SX test set has been created by the framework.
        /// </summary>
        public void CreateCttOrSxTestSetCommandDone(BaseCommand baseCommand)
        {
            // Handle only create test set commands
            if (baseCommand != null)
            {
                string testSetFilePath;
                if (baseCommand is CreateCoreTestToolTestSetCommand)
                    testSetFilePath = ((CreateCoreTestToolTestSetCommand)baseCommand).TestSetFilePath;
                else if (baseCommand is CreateSxTestSetCommand)
                    testSetFilePath = ((CreateSxTestSetCommand)baseCommand).TestSetFilePath;
                else
                    return;

                // If the new test set file has been created
                if (File.Exists(testSetFilePath))
                {
                    // Retrieve the test cases from the test set file
                    TestCase[] testCases = TestsetXmlParser.ParseTestsetFile(testSetFilePath);

                    // Add all new cases found from the test set file
                    foreach (TestCase testCase in testCases)
                    {
                        TestCase existingTestCase = null;

                        if (baseCommand is CreateSxTestSetCommand)
                        {
                            foreach (var x in this.TestSetModel.TestCases)
                            {
                                if (x.Name == testCase.Name)
                                {
                                    existingTestCase = testCase;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            // Determine whether we already have this test in the test set
                            existingTestCase =
                                this.TestSetModel.TestCases.FirstOrDefault(
                                    tc => TestScript.Compare(testCase.Script, tc.Script));
                        }

                        // If we do not have an existing test case that matches
                        if (existingTestCase == null)
                        {
                            // Add the new test case
                            TestSetModel.TestCases.Add(testCase);
                            TestSetModel.IsChanged = true;
                        }
                    }

                    // Delete the file since it is no longer needed
                    File.Delete(testSetFilePath);
                }

                // Check that do we have some standalone SX scripts
                if (baseCommand is CreateSxTestSetCommand)
                {
                    foreach (var filePath in ((CreateSxTestSetCommand)baseCommand).ScriptFilePaths)                    
                    {
                        bool existingTestCase = false;

                        foreach (var x in this.TestSetModel.TestCases)
                        {
                            // If file path or feature name matches, it's existing test case
                            if (x.Name == Path.GetFileName(filePath) ||
                                x.Feature == Path.GetFileNameWithoutExtension(filePath))
                            {
                                existingTestCase = true;
                                break;
                            }
                        }

                        // If we do not have an existing test case that matches
                        if (!existingTestCase)
                        {
                            TestScript script = new TestScript(string.Empty, Path.GetDirectoryName(filePath), Path.GetFileName(filePath), string.Empty);
                            TestCase sxCase = new TestCase(Path.GetFileName(filePath), script, null, Path.GetFileName(filePath), "SX");

                            // Add the new test case
                            TestSetModel.TestCases.Add(sxCase);
                            TestSetModel.IsChanged = true;
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Handler for the ConnectorDone event.
        /// Sets the result of the previous test case.
        /// Runs the next test case, if any are left.
        /// </summary>
        public void RunTestLabTestCaseCommandDone(BaseCommand command)
        {
            // Handle only run test case commands
            if (command.GetType() != typeof(RunTestCaseCommand) &&
                command.GetType().IsAssignableFrom(typeof(ShutdownFramework)) &&
                command.GetType() != typeof(StopExecution))
                return;

            // Handle the result of the previous test case
            this.HandleResult(command);

            bool repeatTimeCompleted = false;

            // Test execution is stopped when test execution stopwatch has reached test set repeat duration.
            if (this.TestSetModel.TimedRunEnabled && this.TestSetModel.TestSetRepeatTimeSpan.Ticks < this.TestExecutionTimeSpan.Ticks)
            {
                repeatTimeCompleted = true;
                this.IsTestRunPauseRequested = false;
            }

            // When test run pause has been requested this is where the pause becomes active.
            if (this.IsTestRunPauseRequested)
            {
                TestCase testCase = TestSetModel.GetNextTestCaseToRun(false);

                if (testCase != null)
                {
                    this.IsTestRunPaused = true;
                    this.PauseTestExecutionStopwatches();

                    return;
                }

                this.IsTestRunPauseRequested = false;
            }

            // Finish run or start running the next selected test case
            if (this.StoppingExecution || repeatTimeCompleted || !this.RunNextTestCase())
            {

                // Set the progressbar value to 0 after all cases are run.
                this.TestSetModel.TestRunProgressValue = 0;
                if (this.TestSetModel.CurrentTestCase != null)
                {
                    this.TestSetModel.CurrentTestCase.IsRunning = false;
                    this.TestSetModel.CurrentTestCase = null;
                }
                
                this.StopTestExecutionStopwatches();

                // Load next test set and start executing it
                if (!this.StoppingExecution && !string.IsNullOrEmpty(this.TestSetModel.NextTestSetPath))
                {
                    // Next test set file doesn't exist
                    if (!File.Exists(this.TestSetModel.NextTestSetPath))
                    {
                        MessageBox.Show("Next test set is defined but the file doesn't exist. \n" + this.TestSetModel.NextTestSetPath, "Next test set is not found",
                                                 MessageBoxButton.OK, MessageBoxImage.Error);
                        return;
                    }

                    this.TestSetModel.Save();
                    this.LoadTestSetFile(new string[] { this.TestSetModel.NextTestSetPath });
                    // check all test cases
                    foreach (TestCase tc in this.TestSetModel.TestCases.Where(tc => tc.IsRoot))
                    {
                        if (this.IsBlackboxCheckBoxesEnabled)
                            tc.IsBlackboxChecked = true;
                        else
                            tc.IsWhiteboxChecked = true;
                        this.TestSetModel.CheckedTestCases++;
                    }
                    this.RunTestSetCommandExecuted();
                }

                // Test run finished
                if (this.TestSetModel.CurrentTestCase == null || this.StoppingExecution)
                {
                    // Send test run end command to framework if it's running
                    if (this.MarbleConnector.State != ConnectorState.Idle)
                        MarbleConnector.AddToQueue(new TestRunEnd());

                    // Register to Fuse connection events
                    FuseClient.RegisterToProductPresences();
                    FuseClient.RegisterToProductIdentifications();
                }

                this.StoppingExecution = false;
            }

            ////if (MarbleMainViewModel.TestResultHandledEventHandler != null) MarbleMainViewModel.TestResultHandledEventHandler.Invoke(null, null);
        }

        /// <summary>
        /// Gets the result of the previously run test case.
        /// Updates status bar and progress bar.
        /// </summary>
        public void HandleResult(BaseCommand executedCommand)
        {
            // No test case has been executed
            if (this.TestSetModel.CurrentTestCase == null)
                return;

            string reportPath = Path.Combine(Path.GetDirectoryName(this.TestSetModel.DocumentPath), Path.GetFileNameWithoutExtension(this.TestSetModel.DocumentPath) + "_results");
            FileUtilities.CheckDirectory(Path.Combine(reportPath, "xml"), true);
            int index = TestSetModel.CurrentTestCase.RunCount > 0 ? TestSetModel.CurrentTestCase.RunCount : 1;
            string resultFile = GetResultFilePath(this.TestSetModel.CurrentTestCase, reportPath, index);

            TestResult result = TestsetXmlParser.GetTestCaseResult(resultFile);

            // Error occurred, result file haven't been created
            if (result == null)
            {
                result = new TestResult();
                result.Result = "No Result";
                result.RunTime = DateTime.Now;
                result.IsBlackboxModeOn = this.TestSetModel.CurrentTestCase.IsBlackboxChecked;
                result.ResultPath = resultFile;
                result.ErrorReason = !string.IsNullOrEmpty(executedCommand.Error) ? executedCommand.Error : "Result file not found";
            }
            if (this.StoppingExecution && ((string.IsNullOrEmpty(result.ErrorReason) || result.ErrorReason == "Result file not found")))
                result.ErrorReason = "Execution aborted by user";

            this.TestSetModel.SetResult(this.TestSetModel.CurrentTestCase, result);

            // Set the progress value for the progressbar.
            if (this.TestSetModel.TimedRunEnabled)
            {
                if (this.TestSetModel.TestSetRepeatTime > 0)
                {
                    double secondsRun = (DateTime.Now - this.TestSetModel.TestSetRunStart).TotalSeconds;
                    this.TestSetModel.TestRunProgressValue = secondsRun/
                                                             this.TestSetModel.TestSetRepeatTimeSpan.TotalSeconds*100;
                }
                else
                    this.TestSetModel.TestRunProgressValue = 100;
            }
            else
            {
                // Count the remaining total iterations from all test cases
                int totalIterationCount =
                    this.TestSetModel.TestCases.Where(
                        tc =>
                        tc.IsRoot && (tc.IsWhiteboxChecked || tc.IsBlackboxChecked) &&
                        tc.TotalRunCount > tc.GetRunCountFromTime(this.TestSetModel.TestSetRunStart))
                        .Sum(testCase => testCase.TotalRunCount - testCase.GetRunCountFromTime(this.TestSetModel.TestSetRunStart));
                this.TestSetModel.TestRunProgressValue = this.TestSetModel.CurrentIndex / (double) totalIterationCount * 100.0;
            }

            //this.TestSetModel.WriteTestResultToXml(this.TestSetModel.CurrentTestCase);
            this.TestSetModel.Save();

            this.TestSetModel.RefreshResultsCounts();

            if (MarbleMainViewModel.TestResultHandledEventHandler != null) MarbleMainViewModel.TestResultHandledEventHandler.Invoke(this.TestSetModel.CurrentTestCase, null);
        }

        /// <summary>
        /// Constructs the file path for the results file.
        /// </summary>
        /// <param name="testCase">Test case.</param>
        /// <param name="reportPath">Directory where the reports are stored.</param>
        /// <param name="index">The index number of the current run.</param>
        /// <returns>Full path for the test case result file.</returns>
        private static string GetResultFilePath(TestCase testCase, string reportPath, int index)
        {
            string resultFilePath;

            // If this is a CTT test case
            if (CoreTestToolUtilities.IsCoreTestToolTest(testCase))
            {
                // For a CTT test case we generate the result file path using the assembly name and the CTT test case id 
                // since the CTT test name may not necessarily be unique and may contain characters that are invalid for 
                // a file name.

                // Construct path to the result xml with running index number on the end
                resultFilePath = Path.Combine(Path.Combine(reportPath, "xml"), Path.GetFileNameWithoutExtension(testCase.Script.file) + "_" + testCase.Script.method.Replace('.', '_') + "_" + index + ".xml");
            }

            // Else this is not a CTT test
            else
            {
                // Construct path to the result xml with running index number on the end
                resultFilePath = Path.Combine(Path.Combine(reportPath, "xml"), FileUtilities.GetValidFilename(testCase.Name) + "_" + index + ".xml");

            }

            return resultFilePath;
        }

        /// <summary>
        /// Adds next selected test case to connector queue.
        /// </summary>
        /// <returns>True if case execution was started false otherwise.</returns>
        public bool RunNextTestCase()
        {
            TestCase testCase = TestSetModel.GetNextTestCaseToRun();

            if (testCase == null)
                return false;

            // Send new settings file to framework if required.
            this.UpdateSettings();

            // Fetch required paths
            string testsetDir = Path.GetDirectoryName(this.TestSetModel.DocumentPath);
            string testsetName = Path.GetFileNameWithoutExtension(this.TestSetModel.DocumentPath);
            string reportPath = Path.Combine(testsetDir, testsetName + "_results");

            // Set current test case.
            this.TestSetModel.CurrentTestCase = testCase;
            this.TestSetModel.CurrentTestCase.IsRunning = true;
            this.TestSetModel.CurrentTestCase.Result.Result = string.Empty;
            this.TestSetModel.CurrentTestCase.Result.ErrorReason = string.Empty;

            int index = TestSetModel.CurrentTestCase.RunCount > 0 ? TestSetModel.CurrentTestCase.RunCount : 1;
            // Construct path to the result xml with running number on the end.
            reportPath = GetResultFilePath(this.TestSetModel.CurrentTestCase, reportPath, index);

            // Delete old report if existing in the current path
            if (File.Exists(reportPath))
                File.Delete(reportPath);

            // Create the command to run the test case
            BaseCommand command = new RunTestCaseCommand(testCase.Script, testCase.Name, reportPath, testCase.IsBlackboxChecked, this.IsBltUeTestingEnabledForTestrun)
                {
                    CallBackMethod = this.RunTestLabTestCaseCommandDone
                };

            // Add the test case to connector queue
            MarbleConnector.AddToQueue(command);

            return true;
        }

        /// <summary>
        /// Loads the opened or dragged testset or python script to the TestSetModel.TestCases collection.
        /// </summary>
        /// <param name="fileNames">String array containing filename(s) of file(s) to be opened.</param>
        public void LoadTestSetFile(string[] fileNames)
        {
            // List of assemblies from which a test set will be created
            List<string> assemblyList = new List<string>();
            
            // List of SX scripts from which a test set will be created
            List<string> sxScriptList = new List<string>();

            foreach (string fileName in fileNames)
            {
                if (fileName.EndsWith(".testset") || fileName.EndsWith(".testset_backup"))
                {
                    // Make relative path.
                    string relativeFilePath = FileUtilities.GetRelativePath(System.IO.Directory.GetCurrentDirectory(), fileName);

                    this.TestSetModel.LoadFromXml(relativeFilePath);
                    this.TestSetModel.IsChanged = false;
                    this.IsTimedRunStartedForUi = this.TestSetModel.TimedRunEnabled;
                    this.CurrentTestRuntimeUnit = this.TestSetModel.CurrentTestRuntimeUnit;
                    this.TestSetRepeatTimeForUi = this.TestSetModel.TestSetRepeatTime;
                }
                else if (fileName.EndsWith(".py"))
                {
                    bool caseAdded = false;
                    // Add all new cases found from the script file
                    foreach (TestCase pyCase in TestCasePyParser.GetTestCases(fileName))
                    {
                        TestCase sameCase = this.TestSetModel.TestCases.FirstOrDefault(tc => TestScript.Compare(pyCase.Script, tc.Script));

                        // Add new case
                        if (sameCase == null)
                        {
                            TestSetModel.TestCases.Add(pyCase);
                            caseAdded = true;
                            TestSetModel.IsChanged = true;
                        }
                    }

                    // Create the required python module file (__init__.py)
                    if (caseAdded)
                    {
                        string directory = Path.GetDirectoryName(fileName);
                        if (directory != null && !File.Exists(Path.Combine(directory, "__init__.py")))
                            File.WriteAllText(Path.Combine(directory, "__init__.py"), MarbleTexts.InitFileContent);
                    }
                }
                else if (fileName.EndsWith(".sx"))
                {
                    sxScriptList.Add(fileName);
                }
                else if (Path.GetExtension(fileName) == ".dll")
                {
                    // Store the assembly file path
                    assemblyList.Add(fileName);
                }
                else if (Path.GetExtension(fileName) == ".jad" || Path.GetExtension(fileName) == ".jar")
                {
                    TestCase newTestCase = NokiaTestHarnessUtilities.CreateTestCase(fileName);

                    // Determine whether we already have this test in the test set
                    TestCase existingTestCase = this.TestSetModel.TestCases.FirstOrDefault(tc => TestScript.Compare(newTestCase.Script, tc.Script));

                    // If we do not have an existing test case that matches
                    if (existingTestCase == null)
                    {
                        // Add the new test case
                        TestSetModel.TestCases.Add(newTestCase);
                        TestSetModel.IsChanged = true;
                    }
                }
            }

            // If we have had assemblies or SX scripts added: initialize framework before running FW commands
            if (assemblyList.Count > 0 || sxScriptList.Count > 0)
            {
                FrameworkInitialization();
            }

            // If we have had assemblies added
            if (assemblyList.Count > 0)
            {
                // Use a temporary file to store the test set generated from the assemblies
                string testSetFilePath = Path.GetTempFileName();

                // If the test set file already exists
                if (File.Exists(testSetFilePath))
                {
                    // Delete the file so we ensure we use the new file that will be created
                    File.Delete(testSetFilePath);
                }

                // Send a command to the framework to create the test set from the list of assemblies
                MarbleConnector.AddToQueue(
                    new CreateCoreTestToolTestSetCommand(assemblyList.ToArray(), testSetFilePath)
                    {
                        CallBackMethod = CreateCttOrSxTestSetCommandDone
                    });
            }

            // If SX scripts added
            if (sxScriptList.Count > 0)
            {
                // Use a temporary file to store the test set generated from the assemblies
                string testSetFilePath = Path.GetTempFileName();

                // If the test set file already exists
                if (File.Exists(testSetFilePath))
                {
                    // Delete the file so we ensure we use the new file that will be created
                    File.Delete(testSetFilePath);
                }

                // Send a command to the framework to create the test set from the list of SX scripts
                MarbleConnector.AddToQueue(
                    new CreateSxTestSetCommand(sxScriptList.ToArray(), testSetFilePath)
                    {
                        CallBackMethod = CreateCttOrSxTestSetCommandDone
                    });
            }

            MarbleFileSettingsModel.AddLoadedTestSetToRecentTestSets(fileNames.ToList());

            if (MarbleMainViewModel.TestResultHandledEventHandler != null) MarbleMainViewModel.TestResultHandledEventHandler.Invoke(null, null);

            this.TestSetModel.RefreshResultsCounts();
        }

        /// <summary>
        /// Confirms whether user wants to save current testset or cancel before New, Open or Close operations.
        /// </summary>
        /// <returns>Returns false if user selects Cancel, otherwise returns true.</returns>
        private bool ConfirmSaveOrContinueOperation()
        {
            MessageBoxResult result = new MessageBoxResult();

            if (this.TestSetModel.IsChanged)
            {
                // New test set
                if (!string.IsNullOrEmpty(this.TestSetModel.TempDocumentPath))
                {
                    result = MessageBox.Show("Would you like to save changes to Untitled?", "Marble", 
                                             MessageBoxButton.YesNoCancel, MessageBoxImage.Exclamation);
                }
                // Existing test set
                else
                {
                    string testsetFileName = Path.GetFileName(this.TestSetModel.DocumentPath);
                    result = MessageBox.Show("Would you like to save changes to " + testsetFileName + "?", "Marble", 
                                              MessageBoxButton.YesNoCancel, MessageBoxImage.Exclamation);
                }
            }

            // Cancel create new testset or save the currently opened testset.
            if (result.Equals(MessageBoxResult.Cancel))
                return false;
            if (result.Equals(MessageBoxResult.Yes))
                SaveTestsetFileCommandExecuted();

            return true;
        }

        /// <summary>
        /// Set the test set file name as the title of the Marble application.
        /// "Untitled *" is displayed if new test set is created.
        /// </summary>
        public void SetMarbleApplicationTitleText(string view = "")
        {
            string filePath = string.Empty;
            bool isDirty = false;

            ////if (view.Equals("TestLab"))
            ////{
            ////    filePath = this.TestSetModel.DocumentPath;
            ////    isDirty = this.TestSetModel.IsChanged;
            ////}

            filePath = this.TestSetModel.DocumentPath;
            isDirty = this.TestSetModel.IsChanged;

            string titleText = string.Empty;

            if (string.IsNullOrEmpty(filePath))
            {
                titleText += "Untitled *";
            }
            else
            {
                int index = filePath.LastIndexOf('\\');

                if (isDirty)
                    titleText += filePath.Substring(index + 1) + " *";
                else
                    titleText += filePath.Substring(index + 1);
            }

            this.MarbleApplicationTitleText = titleText + " - " + this.marbleVersion;
        }

        [MediatorMessageSink("UpdateApplicationTitle", ParameterType = typeof(bool))]
        /// <summary>
        /// Set the test set file name as the title of the Marble application.
        /// "Untitled *" is displayed if new test set is created.
        /// </summary>
        /// <param name="param">Mediator requires a parameter, so this is just for that. This is not used.</param>
        public void SetMarbleApplicationTitleText(bool param)
        {
            //TODO: Remove the event listener from MarbleMainViewModel constructor.
            if (this.ActiveView == null) return;

            string filePath = string.Empty;
            bool isDirty = false;

            if (this.ActiveView.Equals("TestLab"))
            {
                filePath = this.TestSetModel.DocumentPath;
                isDirty = this.TestSetModel.IsChanged;
            }

            string titleText = string.Empty;

            if (string.IsNullOrEmpty(filePath))
            {
                titleText += "Untitled *";
            }
            else
            {
                int index = filePath.LastIndexOf('\\');

                if (isDirty)
                    titleText += filePath.Substring(index + 1) + " *";
                else
                    titleText += filePath.Substring(index + 1);
            }

            this.MarbleApplicationTitleText = titleText + " - " + this.marbleVersion;
        }

        /// <summary>
        /// Hide or unhide the result rows if test case has multiple results.
        /// </summary>
        /// <param name="testCase">Root TestCase.</param>
        private void UpdateResultTree(TestCase testCase)
        {
            if (testCase.IsExpanded)
            {
                var results = this.TestSetModel.TestCases.Where(item => item.Name.Equals(testCase.Name)
                                                                && item.Feature.Equals(testCase.Feature)
                                                                && item.Subarea.Equals(testCase.Subarea)
                                                                && !item.IsRoot).ToList();
                foreach (TestCase tCase in results)
                {
                    tCase.IsVisible = false;
                    this.TestSetModel.TestCases.Remove(tCase);
                }

                testCase.IsExpanded = false;
            }
            else
            {
                List<TestCase> childTestCaseList = new List<TestCase>();
                int index = this.TestSetModel.TestCases.IndexOf(testCase);

                foreach (TestCase childCase in testCase.Children)
                {
                    childCase.IsVisible = true;
                    childTestCaseList.Add(childCase);
                }

                testCase.IsExpanded = true;
                this.TestSetModel.TestCases.InsertRange(index + 1, childTestCaseList);
            }
        }

        #region [ Enums ]

        public enum SelectedReportsEnum
        {
            None = 0,
            UnresolvedReport = 1,
            FailedReport = 2,
            PassedReport = 3,
            MultipleContainingFailedReport = 4,
            MultipleAllPassedReports = 5,
        }

        #endregion [ Enums ]

        #region CommandActions

        /// <summary>
        /// Checks if the check command can run.
        /// </summary>
        /// <returns>returns true if backgroundworker is not running</returns>
        public bool GridRowCheckBoxCheckCanExecute(TestCase testCase)
        {
            return true;
        }

        /// <summary>
        /// Marks the checked item as checked.
        /// </summary>
        public void GridRowCheckBoxCheckExecuted(TestCase testCase)
        {
            if (testCase != null)
            {
                if (!testCase.IsWhiteboxChecked)
                {
                    testCase.IsWhiteboxChecked = true;
                }
            }

            if (this.TestSetModel.TestCases.All(item => item.IsWhiteboxChecked))
                this.IsWhiteboxHeaderSplitButtonCheckBoxChecked = true;
        }

        /// <summary>
        /// Checks if the uncheck command can run.
        /// </summary>
        /// <returns>returns true if backgroundworker is not running</returns>
        public bool GridRowCheckBoxUnCheckCanExecute(TestCase testCase)
        {
            return true;
        }

        /// <summary>
        /// Marks the checked item as unchecked.
        /// </summary>
        public void TestCaseBlackboxCheckBoxUnCheckExecuted(TestCase testCase)
        {
            if (testCase != null)
            {
                if (testCase.IsBlackboxChecked)
                    testCase.IsBlackboxChecked = false;
            }

            if (this.TestSetModel.TestCases.All(item => !item.IsBlackboxChecked))
                this.IsBlackboxHeaderSplitButtonCheckBoxChecked = false;
        }

        /// <summary>
        /// Checks if the check command can run.
        /// </summary>
        /// <returns>returns true if backgroundworker is not running</returns>
        public bool TestCaseBlackboxCheckBoxCheckCanExecute(TestCase testCase) { return true; }

        /// <summary>
        /// Marks the checked item as checked.
        /// </summary>
        public void TestCaseBlackboxCheckBoxCheckExecuted(TestCase testCase)
        {
            if (testCase != null)
            {
                if (!testCase.IsBlackboxChecked)
                    testCase.IsBlackboxChecked = true;
            }

            if (this.TestSetModel.TestCases.All(item => item.IsBlackboxChecked))
                this.IsBlackboxHeaderSplitButtonCheckBoxChecked = true;
        }

        /// <summary>
        /// Checks if the uncheck command can run.
        /// </summary>
        /// <returns>returns true if backgroundworker is not running</returns>
        public bool TestCaseBlackboxCheckBoxUnCheckCanExecute(TestCase testCase) { return true; }

        /// <summary>
        /// Marks the checked item as unchecked.
        /// </summary>
        public void GridRowCheckBoxUnCheckExecuted(TestCase testCase)
        {
            if (testCase != null)
            {
                if (testCase.IsWhiteboxChecked)
                    testCase.IsWhiteboxChecked = false;
            }

            if (this.TestSetModel.TestCases.All(item => !item.IsWhiteboxChecked))
                this.IsWhiteboxHeaderSplitButtonCheckBoxChecked = false;
        }

        /// <summary>
        /// Checks if the DataGridDropCommandExecuted can run.
        /// </summary>
        /// <returns>returns true</returns>
        public bool DataGridDropCommandCanExecute(EventBehaviourArgs e)
        {
            return true;
        }

        /// <summary>
        /// Handles the DataGrid drop event and loads the dropped file(s).
        /// </summary>
        public void DataGridDropCommandExecuted(EventBehaviourArgs e)
        {
            if (e == null) return;

            DragEventArgs dragEventArgs = e.OriginalEventArgs as DragEventArgs;

            if (dragEventArgs.Data.GetDataPresent(DataFormats.FileDrop))
            {
                string[] data = dragEventArgs.Data.GetData(DataFormats.FileDrop) as string[];
                if (data == null)
                    return;

                // If one of the files to be opened is .testset file.
                if (data.Any(item => Path.GetExtension(item).Equals(".testset")))
                {
                    if (!this.ConfirmSaveOrContinueOperation())
                        return;
                }

                this.LoadTestSetFile(data);
                this.UpdateStatusBar();
            }
        }

        /// <summary>
        /// Check to see if TotalRunCountTextBoxCommand can be run.
        /// </summary>
        /// <param name="item">Value from TextBox</param>
        /// <returns>Returns true if TotalRunCountTextBoxCommand can be run.</returns>
        public bool TotalRunCountTextBoxCommandCanExecute(string txtValue)
        {
            return true;
        }

        /// <summary>
        /// Change the TotalRunCount value in the .testset file.
        /// </summary>
        /// <param name="item">Value from TextBox</param>
        public void TotalRunCountTextBoxCommandExecuted(string txtValue)
        {
            if (!string.IsNullOrEmpty(txtValue))
            {
                // This is set here instead of in the TotalRunCount PropertyChanged event because,
                // the TotalRunCount is set when application is started so it would set IsChanged to true falsely in the app start.
                //this.TestSetModel.IsChanged = true;
                if (!this.TestSetModel.IsChanged)
                    this.TestSetModel.IsChanged = true;
            }
        }

        /// <summary>
        /// Check to see if TestLabRowExpanderCommand can be run.
        /// </summary>
        /// <param name="item">TestCase item from the root node row.</param>
        /// <returns>Returns true if TestLabRowExpanderCommand can be run.</returns>
        public bool TestLabRowExpanderCommandCanExecute(TestCase item)
        {
            return true;
        }

        /// <summary>
        /// Change the TotalRunCount value in the .testset file.
        /// </summary>
        /// <param name="item">TestCase item from the root node row.</param>
        public void TestLabRowExpanderCommandExecuted(TestCase item)
        {
            this.UpdateResultTree(item);
        }

        /// <summary>
        /// Check to see if EditSelectedTestCommand can be run.
        /// </summary>
        /// <returns>Returns true if EditSelectedTestCommand can be run.</returns>
        public bool EditSelectedTestCommandCanExecute()
        {
            if (this.SelectedTestCase == null) return false;

            // Selected test case can be edited if it is not a CTT or NTH test
            return !CoreTestToolUtilities.IsCoreTestToolTest(this.SelectedTestCase) && !NokiaTestHarnessUtilities.IsNokiaTestHarnessTest(this.SelectedTestCase);
        }

        /// <summary>
        /// Edit the select test.
        /// </summary>
        public void EditSelectedTestCommandExecuted()
        {
            if (this.SelectedTestCase == null) return;

            // Open the text editor to allow the user to edit the test script
            this.OpenSimpleTextEditorCommandExecuted();
        }

        /// <summary>
        /// Checks if test set can be run.
        /// </summary>
        /// <returns>returns true if at least one test case is checked.</returns>
        public bool RunTestSetCommandCanExecute()
        {
            // MTBF Follower mode can start running without any testcases selected
            if (this.settings != null && this.settings.TestRun != null && this.settings.TestRun.ExecutionMode == "Follower")
            {
                return this.MarbleConnector.State != ConnectorState.FrameworkExecuting;
            }

            if (this.TestSetModel.TestCases == null)
                return false;

            if (this.IsTestRunPaused) return true;

            // Play enabled
            ////return (this.FuseClient.MainConnection != null &&
            ////        this.FuseClient.MainConnection.ProductPresent > 0 &&
            ////        (this.MarbleConnector.State == ConnectorState.Idle ||
            ////         this.MarbleConnector.State == ConnectorState.FrameworkReady) &&
            ////        (this.TestSetModel.TestCases.Any(x => x.IsWhiteboxChecked || x.IsBlackboxChecked) ||
            ////         this.SelectedTestCases.Any()) ||
            ////        // Stop enabled
            ////        (this.MarbleConnector.State == ConnectorState.StartingFramework ||
            ////         this.MarbleConnector.State == ConnectorState.SendingCommand ||
            ////         this.MarbleConnector.State == ConnectorState.FrameworkExecuting));

            return ((this.MarbleConnector.State == ConnectorState.Idle ||
                     this.MarbleConnector.State == ConnectorState.FrameworkReady) &&
                    (this.TestSetModel.TestCases.Any(x => x.IsWhiteboxChecked || x.IsBlackboxChecked) ||
                     this.SelectedTestCases.Any()) ||
                // Stop enabled
                    (this.MarbleConnector.State == ConnectorState.StartingFramework ||
                     this.MarbleConnector.State == ConnectorState.SendingCommand ||
                     this.MarbleConnector.State == ConnectorState.FrameworkExecuting));
        }

        /// <summary>
        /// Checks whether the test run can be stopped.
        /// </summary>
        /// <returns>returns true if at least one test case is checked.</returns>
        public bool StopTestRunCommandCanExecute()
        {
            // MTBF Follower mode can be only stopped if running. MTBF Follower cannot be paused.
            if (this.settings != null && this.settings.TestRun != null && this.settings.TestRun.ExecutionMode == "Follower")
            {
                return this.MarbleConnector.State == ConnectorState.FrameworkExecuting;
            }

            if (this.TestSetModel.TestCases == null)
                return false;

            return (this.IsTestRunPaused ||
                    this.MarbleConnector.State == ConnectorState.StartingFramework ||
                    this.MarbleConnector.State == ConnectorState.SendingCommand ||
                    this.MarbleConnector.State == ConnectorState.FrameworkExecuting ||
                    // For emergency stop.
                    this.MarbleConnector.State == ConnectorState.StoppingExecution);
        }

#if FRAMEWORK_SUPPORTS_MARBLE_SETTINGS_DIRECTORY
        /// <summary>
        /// Changes necessary settings locally and updates them to framework if required.
        /// Settings are updated with settings update command if framework is running.
        /// </summary>
        /// <param name="forceSaveAll">If set to <c>true</c> this will force the saving of all settings, otherwise this 
        /// will only save the settings files for those settings that are updated.</param>
        /// <param name="forceSaveSIMSettings">Saves phone number and other SIM settings regardless of the autosave SIM settings system setting.</param>
        public void UpdateSettings(bool forceSaveAll = false, bool forceSaveSIMSettings = false)
        {
            if (_loadSettingsTask == null) return;

            // If the loading of the settings has not yet completed
            if (!_loadSettingsTask.IsCompleted)
            {
                // Wait for the load to complete
                _loadSettingsTask.Wait();
            }

            // Whether settings update request to framework is needed
            bool updateMainNeeded = false;
            bool updateRemoteNeeded = false;
            bool updateTestRunNeeded = false;
            bool updateReferencePhoneNeeded = false;

            // Main connection(s)
            foreach (var mainPhone in DeviceCollection.Where(d => d.IsMain))
            {
                // Determine name of the settings module (Main, Main2, Main3 etc.)
                string settingsModuleName = mainPhone.MainIndex < 2 ? "Main" : "Main" + mainPhone.MainIndex;
                SettingModule module = SettingsManager.Instance.SettingModules.Find(s => s.Name == settingsModuleName);
                if (module == null) continue;

                if (module["Connection"] as string != mainPhone.SerialNumber)
                {
                    module.SetSettingValue("Connection", mainPhone.SerialNumber);
                    updateMainNeeded = true;
                }
            }

            int maxMainIndex = this.DeviceCollection.Any()
                                   ? this.DeviceCollection.Max(d => d.MainIndex)
                                   : 0;

            // Clear unused main connections from settings
            for (int ii = maxMainIndex + 1; ii <= 6; ii++)
            {
                // Determine name of the settings module (Main, Main2, Main3 etc.)
                string settingsModuleName = ii == 1 ? "Main" : "Main" + ii;
                SettingModule module = SettingsManager.Instance.SettingModules.Find(s => s.Name == settingsModuleName);
                if (module == null) continue;

                if (module["Connection"] as string != string.Empty)
                {
                    module.SetSettingValue("Connection", string.Empty);
                    updateMainNeeded = true;
                }
            }


            // TRACING "Test run/tracing enabled" (this is enabled also when memory leak testing is enabled)
            if (settings.TestRun.TracingEnabled != (this.IsTracingEnabledForTestrun || this.IsMemoryLeakTestingEnabledForTestrun))
            {
                settings.TestRun.TracingEnabled = (this.IsTracingEnabledForTestrun || this.IsMemoryLeakTestingEnabledForTestrun);
                updateTestRunNeeded = true;
            }

            // MEMORY LEAK TESTING "Test run/memory leak testing enabled"
            if (settings.TestRun.MemoryLeakTestingEnabled != this.IsMemoryLeakTestingEnabledForTestrun)
            {
                settings.TestRun.MemoryLeakTestingEnabled = IsMemoryLeakTestingEnabledForTestrun;
                updateTestRunNeeded = true;
            }

            // Trace xml path
            if (string.IsNullOrEmpty(this.TraceXmlPath) && !string.IsNullOrEmpty(settings.TestRun.TraceXmlFilePath))
            {
                // Clear 'trace xml-file path' setting
                settings.TestRun.TraceXmlFilePath = string.Empty;
                updateTestRunNeeded = true;
            }
            else if (!string.IsNullOrEmpty(this.TraceXmlPath) && settings.TestRun.TraceXmlFilePath != this.TraceXmlPath)
            {
                // Set 'trace xml-file path' setting
                settings.TestRun.TraceXmlFilePath = this.TraceXmlPath;
                updateTestRunNeeded = true;
            }

            // Disable setup and teardown
            if (settings.TestRun.DisableTestCaseSetupAndTeardown != this.IsSetupAndTearDownDisabled)
            {
                settings.TestRun.DisableTestCaseSetupAndTeardown = this.IsSetupAndTearDownDisabled;
                updateTestRunNeeded = true;
            }

            // BlackBox enabled
            if (settings.TestRun.EnableBlackBox != this.isBlackboxCheckBoxesEnabled)
            {
                settings.TestRun.EnableBlackBox = this.isBlackboxCheckBoxesEnabled;
                updateTestRunNeeded = true;
            }

            // Remote settings
            updateRemoteNeeded = this.SetRemotePhoneSettings(forceSaveSIMSettings);

            // Main PMD file
            //ProductInfo mainProduct = this.FuseClient.MainConnection;
            //string pmdPath = mainProduct != null && !string.IsNullOrEmpty(mainProduct.PMD.FilePath)
            //                     ? mainProduct.PMD.FilePath
            //                     : string.Empty;

            //if (settings.Main.PmdFilePath != pmdPath)
            //{
            //    settings.Main.PmdFilePath = pmdPath;
            //    updateMainNeeded = true;
            //}

            // Trace connection
            // No trace connection selected but settings has a trace connection set
            if (FuseClient.TraceConnection == null && settings.Main.TraceConnection != string.Empty)
            {
                settings.Main.TraceConnection = string.Empty;
                updateMainNeeded = true;
            }
                // Selected trace connection differs from the one in settings
            else if (FuseClient.TraceConnection != null && FuseClient.TraceConnection.Connection.GUID != settings.Main.TraceConnection)
            {
                settings.Main.TraceConnection = FuseClient.TraceConnection.Connection.GUID;
                updateMainNeeded = true;
            }

            // Determine whether any update is needed
            bool updateNeeded = (updateMainNeeded || updateRemoteNeeded || updateTestRunNeeded || updateReferencePhoneNeeded);

            // If we must do a forced save of all settings
            if (forceSaveAll)
            {
                // Save all settings
                SettingsManager.Instance.SaveAll();
            }

                // Else if in an update is needed
            else if (updateNeeded)
            {
                if (updateMainNeeded)
                {                    
                    // Save the main setting modules
                    for (int index = 1; index <= 6 ; index++)
                    {
                        string settingsModuleName = index == 1 ? "Main" : "Main" + index;
                        SettingModule module = SettingsManager.Instance.SettingModules.Find(s => s.Name == settingsModuleName);
                        if (module == null) continue;
                        SettingsManager.Instance.Save(settingsModuleName);
                    }
                }

                if (updateRemoteNeeded)
                {
                    // Save the remote setting modules
                    for (int index = 1;; index++)
                    {
                        string settingsModuleName = index == 1 ? "Remote" : "Remote" + index;
                        SettingModule module = SettingsManager.Instance.SettingModules.Find(s => s.Name == settingsModuleName);
                        if (module == null) break;
                        SettingsManager.Instance.Save(settingsModuleName);
                    }
                }

                if (updateTestRunNeeded)
                {
                    // Save the test run setting module
                    SettingsManager.Instance.Save("TestRun");
                }

                if (updateReferencePhoneNeeded)
                {
                    // Save the reference phone setting module
                    SettingsManager.Instance.Save("Reference");
                }
            }

            // If we have saved all settings or updated some of the settings
            if (forceSaveAll || updateNeeded)
            {
                // Send update command only if framework is currently running
                if (this.MarbleConnector.State != ConnectorState.Idle)
                    this.MarbleConnector.AddToQueue(new SettingsCommand());
            }
        }

        /// <summary>
        /// Copies settings of all remote phones to settings manager.
        /// Affected settings are Connection, PMD, SIM settings.
        /// Connection value is cleared for remote settings modules that are not used.
        /// </summary>
        /// <param name="forceSaveSIMSettings">Saves phone number and other SIM settings regardless of the autosave SIM settings system setting.</param>
        /// <returns>True if some remote module was modified, false otherwise.</returns>
        private bool SetRemotePhoneSettings(bool forceSaveSIMSettings = false)
        {
            forceSaveSIMSettings = false;

            bool updateNeeded = false;

            var remoteConnections = FuseClient.RemoteConnections.Where(p => p.RemoteIndex != 0);
            var remoteConnectionsList = remoteConnections as IList<ProductInfo> ?? remoteConnections.ToList();
            foreach (var remote in remoteConnectionsList)
            {
                // Determine name of the settings module (Remote, Remote1, Remote2 etc.)
                string settingsModuleName = remote.RemoteIndex == 1 ? "Remote" : "Remote" + remote.RemoteIndex;
                SettingModule module = SettingsManager.Instance.SettingModules.Find(s => s.Name == settingsModuleName);
                if (module == null) continue;

                // Connection
                if (module["Connection"] as string != remote.Connection.GUID)
                {
                    module.SetSettingValue("Connection", remote.Connection.GUID);
                    updateNeeded = true;
                }

                // PMD file
                //string remotePMDPath = !string.IsNullOrEmpty(remote.PMD.FilePath)
                //                           ? remote.PMD.FilePath
                //                           : string.Empty;

                //if (module["PmdFilePath"] as string != remotePMDPath)
                //{
                //    module.SetSettingValue("PmdFilePath", remotePMDPath);
                //    updateNeeded = true;
                //}

                // SIM numbers
            }

            // Clear connection of other remote modules
            int index = remoteConnectionsList.Count + 1;
            while (true)
            {
                string moduleName = index == 1 ? "Remote" : "Remote" + index;
                SettingModule remoteModule = SettingsManager.Instance.SettingModules.Find(s => s.Name == moduleName);
                if (remoteModule == null) break;

                if (!string.IsNullOrEmpty(remoteModule["Connection"] as string))
                {
                    remoteModule.SetSettingValue("Connection", string.Empty);
                    updateNeeded = true;
                }
                index++;
            }
            return updateNeeded;
        }

        /// <summary>
        /// Sets the settings for the SIM properties.
        /// </summary>
        /// <returns>Returns <c>true</c> if the 'Main' SIM settings have been updated, otherwise <c>false</c> is returned.</returns>
        private bool SetSettingsForSimProperties(int phoneIndex=0)
        {
            return false;

            if (phoneIndex==0 && FuseClient.MainConnection == null) return false;

            ProductInfo phoneInfo = null;
            // Get productInfo for Remote connection
            if (phoneIndex > 0)
            {
                phoneInfo = FuseClient.RemoteConnections.FirstOrDefault(p => p.RemoteIndex == phoneIndex);
                if (phoneInfo == null) return false;
            }
            // Get productInfo for Main connection
            else
            {
                phoneInfo = FuseClient.MainConnection;
            }

            // Get the main phone - phone that has the same GUID as the selected main connection
            var phoneModel = App.SimManagerViewModel.Phones.FirstOrDefault(phone => phone.ConnectionGuid == phoneInfo.Connection.GUID);
            if (phoneModel == null) return false;

            // Determine name of the settings module (Main, Remote, Remote1, Remote2 etc.)
            string settingsModuleName = "Main";
            if (phoneIndex > 0)
                settingsModuleName = phoneIndex == 1 ? "Remote" : "Remote" + phoneIndex;

            SettingModule module = SettingsManager.Instance.SettingModules.Find(s => s.Name == settingsModuleName);
            if (module == null) return false;

            bool updatePhoneNeeded = false;

            // Save values for SIM1 and SIM2 if possible
            for (int currentSimSlot = 1; currentSimSlot <= 2; currentSimSlot++)
            {
                SimModel simModel = phoneModel.Sims.FirstOrDefault(sim => sim.CurrentSimSlot == currentSimSlot);

                // Preserve existing values if sim not found
                if (simModel == null) continue;

                foreach (string simValue in Enum.GetNames(typeof(SimXmlParser.ChangeableSimValue)))
                {
                    string settingName = string.Format("SIM{0}{1}", currentSimSlot, simValue);

                    SimXmlParser.ChangeableSimValue changeableSimValue;
                    Enum.TryParse(simValue, out changeableSimValue);

                    switch (changeableSimValue)
                    {
                        case SimXmlParser.ChangeableSimValue.PhoneNumber:
                            if (simModel.PhoneNumber == module[settingName] as string) break;

                            module.SetSettingValue(settingName, simModel.PhoneNumber);
                            updatePhoneNeeded = true;
                            break;
                        case SimXmlParser.ChangeableSimValue.PinCode:
                            if (simModel.PinCode == module[settingName] as string) break;

                            module.SetSettingValue(settingName, simModel.PinCode);
                            updatePhoneNeeded = true;
                            break;
                        case SimXmlParser.ChangeableSimValue.Pin2Code:
                            if (simModel.Pin2Code == module[settingName] as string) break;

                            module.SetSettingValue(settingName, simModel.Pin2Code);
                            updatePhoneNeeded = true;
                            break;
                        case SimXmlParser.ChangeableSimValue.Puk1Code:
                            if (simModel.Puk1Code == module[settingName] as string) break;

                            module.SetSettingValue(settingName, simModel.Puk1Code);
                            updatePhoneNeeded = true;
                            break;
                        case SimXmlParser.ChangeableSimValue.Puk2Code:
                            if (simModel.Puk2Code == module[settingName] as string) break;

                            module.SetSettingValue(settingName, simModel.Puk2Code);
                            updatePhoneNeeded = true;
                            break;
                        case SimXmlParser.ChangeableSimValue.ServiceNumber:
                            if (simModel.ServiceNumber == module[settingName] as string) break;

                            module.SetSettingValue(settingName, simModel.ServiceNumber);
                            updatePhoneNeeded = true;
                            break;
                        case SimXmlParser.ChangeableSimValue.VoiceMailNumber:
                            if (simModel.VoiceMailNumber == module[settingName] as string) break;

                            module.SetSettingValue(settingName, simModel.VoiceMailNumber);
                            updatePhoneNeeded = true;
                            break;
                        default:
                            throw new ArgumentOutOfRangeException();
                    }
                }
            }

            return updatePhoneNeeded;
        }

        /// <summary>
        /// Updates changed SIM properties from settings.
        /// </summary>
        /// <returns>Returns <c>true</c> if the 'Main' SIM settings have been updated, otherwise <c>false</c> is returned.</returns>
        public bool UpdateChangedSimPropertiesFromSettings()
        {
            if (FuseClient.MainConnection == null) return false;

            bool updateNeeded = false;
            // Get the main phone - phone that has the same GUID as the selected main connection
            var mainPhone = App.SimManagerViewModel.Phones.FirstOrDefault(phone => phone.ConnectionGuid == FuseClient.MainConnection.Connection.GUID);

            SettingModule module = SettingsManager.Instance.SettingModules.Find(s => s.Name == "Main");

            if (module != null)
            {
                for (int currentSimSlot = 1; currentSimSlot <= 2; currentSimSlot++)
                {
                    IEnumerable<SimModel> sims = mainPhone != null ? mainPhone.Sims.Where(sim => sim.CurrentSimSlot == currentSimSlot) : new List<SimModel>();

                    // Set empty values if sim not found
                    SimModel simModel = sims.Any() ? sims.First() : new SimModel();

                    foreach (string simValue in Enum.GetNames(typeof(SimXmlParser.ChangeableSimValue)))
                    {
                        string settingName = string.Format("SIM{0}{1}", currentSimSlot, simValue);

                        // Empty values are not updated to SIM Manager.
                        if (string.IsNullOrEmpty(module[settingName] as string)) break;

                        SimXmlParser.ChangeableSimValue changeableSimValue;
                        Enum.TryParse(simValue, out changeableSimValue);

                        switch (changeableSimValue)
                        {
                            case SimXmlParser.ChangeableSimValue.PhoneNumber:
                                if (simModel.PhoneNumber == module[settingName] as string) break;

                                simModel.PhoneNumber = module[settingName] as string;
                                updateNeeded = true;
                                break;
                            case SimXmlParser.ChangeableSimValue.PinCode:
                                if (simModel.PinCode == module[settingName] as string) break;

                                simModel.PinCode = module[settingName] as string;
                                updateNeeded = true;
                                break;
                            case SimXmlParser.ChangeableSimValue.Pin2Code:
                                if (simModel.Pin2Code == module[settingName] as string) break;

                                simModel.Pin2Code = module[settingName] as string;
                                updateNeeded = true;
                                break;
                            case SimXmlParser.ChangeableSimValue.Puk1Code:
                                if (simModel.Puk1Code == module[settingName] as string) break;

                                simModel.Puk1Code = module[settingName] as string;
                                updateNeeded = true;
                                break;
                            case SimXmlParser.ChangeableSimValue.Puk2Code:
                                if (simModel.Puk2Code == module[settingName] as string) break;

                                simModel.Puk2Code = module[settingName] as string;
                                updateNeeded = true;
                                break;
                            case SimXmlParser.ChangeableSimValue.ServiceNumber:
                                if (simModel.ServiceNumber == module[settingName] as string) break;

                                simModel.ServiceNumber = module[settingName] as string;
                                updateNeeded = true;
                                break;
                            case SimXmlParser.ChangeableSimValue.VoiceMailNumber:
                                if (simModel.VoiceMailNumber == module[settingName] as string) break;

                                simModel.VoiceMailNumber = module[settingName] as string;

                                updateNeeded = true;
                                break;
                            default:
                                throw new ArgumentOutOfRangeException();
                        }
                    }
                }
            }

            return updateNeeded;
        }

#else
        /// <summary>
        /// Changes necessary settings locally and updates them to framework if required.
        /// Settings are updated with settings update command if framework is running.
        /// </summary>
        public void UpdateSettings()
        {
            // Whether settings update request to framework is needed
            bool updateNeeded = false;

            // Main connection
            if (FuseClient.MainConnection != null && !string.IsNullOrEmpty(FuseClient.MainConnection.Connection.GUID) &&
                this.settingsModel.GetValue(@"Main/connection") != FuseClient.MainConnection.Connection.GUID)
            {
                this.settingsModel.SetValue(@"Main/connection", FuseClient.MainConnection.Connection.GUID);
                updateNeeded = true;
            }

            // TRACING "Test run/tracing enabled" (this is enabled also when memory leak testing is enabled)
            if (bool.Parse(this.settingsModel.GetValue(@"Test run/tracing enabled")) != (this.IsTracingEnabledForTestrun || this.IsMemoryLeakTestingEnabledForTestrun))
            {
                this.settingsModel.SetValue(@"Test run/tracing enabled", (this.IsTracingEnabledForTestrun || this.IsMemoryLeakTestingEnabledForTestrun).ToString());
                updateNeeded = true;
            }

            // MEMORY LEAK TESTING "Test run/memory leak testing enabled"
            if (this.settingsModel.GetValue(@"Test run/memory leak testing enabled") == null ||
                bool.Parse(this.settingsModel.GetValue(@"Test run/memory leak testing enabled")) != this.IsMemoryLeakTestingEnabledForTestrun)
            {
                this.settingsModel.SetValue(@"Test run/memory leak testing enabled", this.IsMemoryLeakTestingEnabledForTestrun.ToString());
                updateNeeded = true;
            }

            // Trace xml path
            if (string.IsNullOrEmpty(this.TraceXmlPath) && !string.IsNullOrEmpty(this.settingsModel.GetValue(@"Test run/trace xml-file path")))
            {   // Clear 'trace xml-file path' setting
                this.settingsModel.SetValue(@"Test run/trace xml-file path", string.Empty);
                updateNeeded = true;
            }
            else if (!string.IsNullOrEmpty(this.TraceXmlPath) && this.settingsModel.GetValue(@"Test run/trace xml-file path") != this.TraceXmlPath)
            {   // Set 'trace xml-file path' setting
                this.settingsModel.SetValue(@"Test run/trace xml-file path", this.TraceXmlPath);
                updateNeeded = true;
            }

            // Disable setup and teardown
            if (this.settingsModel.GetValue(@"Test run/disable test case setup and teardown") == null ||
                bool.Parse(this.settingsModel.GetValue(@"Test run/disable test case setup and teardown")) != this.IsSetupAndTearDownDisabled)
            {
                this.settingsModel.SetValue((@"Test run/disable test case setup and teardown"), (this.IsSetupAndTearDownDisabled).ToString());
                updateNeeded = true;
            }

            // Main PMD file
            if (this.FuseClient.MainConnection != null && !string.IsNullOrEmpty(this.FuseClient.MainConnection.PMD.FilePath) &&
                this.settingsModel.GetValue(@"Main/pmd-file path") != this.FuseClient.MainConnection.PMD.FilePath)
            {
                this.settingsModel.SetValue(@"Main/pmd-file path", this.FuseClient.MainConnection.PMD.FilePath);
                updateNeeded = true;
            }

            // Reference connection
            if (this.FuseClient.ReferenceConnection != null && !string.IsNullOrEmpty(FuseClient.ReferenceConnection.Connection.GUID) &&
                settingsModel.GetValue(@"ReferencePhone/connection") != FuseClient.ReferenceConnection.Connection.GUID)
            {
                settingsModel.SetValue(@"ReferencePhone/connection", FuseClient.ReferenceConnection.Connection.GUID);
                updateNeeded = true;
            }

            ////// Reference PMD file
            ////if (FuseClient.ConnectedProducts.Any(product => product.IsReference))
            ////{
            ////    string pmdPath = FuseClient.ConnectedProducts.First(product => product.IsReference).PMD.FilePath;

            ////    if (this.settingsModel.GetValue(@"Reference/pmd-file path") != pmdPath)
            ////    {
            ////        this.settingsModel.SetValue(@"Reference/pmd-file path", pmdPath);
            ////        updateNeeded = true;
            ////    }
            ////}

            // Trace connection
            // No trace connection selected but settings has a trace connection set
            if (FuseClient.TraceConnection == null && this.settingsModel.GetValue(@"Main/trace connection") != string.Empty)
            {
                this.settingsModel.SetValue(@"Main/trace connection", string.Empty);
                updateNeeded = true;
            }
            // Selected trace connection differs from the one in settings
            else if (FuseClient.TraceConnection != null && FuseClient.TraceConnection.Connection.GUID != this.settings.GetValue(@"Main/trace connection"))
            {
                this.settingsModel.SetValue(@"Main/trace connection", FuseClient.TraceConnection.Connection.GUID);
                updateNeeded = true;
            }

            // Main phone SIM numbers
            if (this.setSettingsForSimProperties()) 
                updateNeeded = true;

            // Reference phone SIM numbers
            // Get the reference phone - phone that has the same GUID as the selected reference connection
            if (this.FuseClient.ReferenceConnection != null)
            {
                var referencePhones =
                    App.SimManagerViewModel.Phones.Where(
                        phone => phone.ConnectionGuid == FuseClient.ReferenceConnection.Connection.GUID);

                if (referencePhones.Any() && referencePhones.First().Sims.Count > 0)
                {
                    // Primary SIM
                    var sims = referencePhones.First().Sims.Where(sim => sim.CurrentSimSlot == 1);
                    string phoneNum = string.Empty;

                    if (sims.Any())
                        phoneNum = sims.First().PhoneNumber;

                    if (phoneNum != this.settingsModel.GetValue("ReferencePhone/Account/phone number"))
                    {
                        this.settingsModel.SetValue("ReferencePhone/Account/phone number", phoneNum);
                        updateNeeded = true;
                    }
                }
            }

            // Save settings
            if (updateNeeded)
                this.settingsModel.Save();

            // Send update command only if framework is currently running
            if (updateNeeded && this.MarbleConnector.State != ConnectorState.Idle)
                this.MarbleConnector.AddToQueue(new SettingsCommand(this.settingsModel.DocumentPath));
        }

        private bool setSettingsForSimProperties()
        {
            if (this.FuseClient.MainConnection == null)
                return false;

            // Get the main phone - phone that has the same GUID as the selected main connection
            var mainPhones = App.SimManagerViewModel.Phones.Where(phone => phone.ConnectionGuid == FuseClient.MainConnection.Connection.GUID);

            if (!mainPhones.Any() || mainPhones.First().Sims.Count <= 0) return false;

            bool updateNeeded = false;

            for (int currentSimSlot = 1; currentSimSlot <= 2; currentSimSlot++)
            {
                var sims = mainPhones.First().Sims.Where(sim => sim.CurrentSimSlot == currentSimSlot);

                if (!sims.Any()) continue;

                SimModel simModel = sims.First();

                foreach (var simValueType in Enum.GetNames(typeof(SimXmlParser.ChangeableSimValue)))
                {
                    SimXmlParser.ChangeableSimValue changeableSimValue;
                    Enum.TryParse(simValueType, out changeableSimValue);
                    string settingValuePath = SimXmlParser.GetSettingValuePath(changeableSimValue, currentSimSlot);

                    switch (changeableSimValue)
                    {
                        case SimXmlParser.ChangeableSimValue.PhoneNumber:
                            if (simModel.PhoneNumber == this.settingsModel.GetValue(settingValuePath)) break;
                            
                            this.settingsModel.SetValue(settingValuePath, simModel.PhoneNumber);
                            updateNeeded = true;
                            break;
                        case SimXmlParser.ChangeableSimValue.PinCode:
                            if (simModel.PinCode == this.settingsModel.GetValue(settingValuePath)) break;
                            
                            this.settingsModel.SetValue(settingValuePath, simModel.PinCode);
                            updateNeeded = true;
                            break;
                        case SimXmlParser.ChangeableSimValue.Pin2Code:
                            if (simModel.Pin2Code == this.settingsModel.GetValue(settingValuePath)) break;
                            
                            this.settingsModel.SetValue(settingValuePath, simModel.Pin2Code);
                            updateNeeded = true;
                            break;
                        case SimXmlParser.ChangeableSimValue.Puk1Code:
                            if (simModel.Puk1Code == this.settingsModel.GetValue(settingValuePath)) break;

                            this.settingsModel.SetValue(settingValuePath, simModel.Puk1Code);
                            updateNeeded = true;
                            break;
                        case SimXmlParser.ChangeableSimValue.Puk2Code:
                            if (simModel.Puk2Code == this.settingsModel.GetValue(settingValuePath)) break;

                            this.settingsModel.SetValue(settingValuePath, simModel.Puk2Code);
                            updateNeeded = true;
                            break;
                        case SimXmlParser.ChangeableSimValue.ServiceNumber:
                            if (simModel.ServiceNumber == this.settingsModel.GetValue(settingValuePath)) break;
                            
                            this.settingsModel.SetValue(settingValuePath, simModel.ServiceNumber);
                            updateNeeded = true;
                            break;
                        case SimXmlParser.ChangeableSimValue.VoiceMailNumber:
                            if (simModel.VoiceMailNumber == this.settingsModel.GetValue(settingValuePath)) break;

                            this.settingsModel.SetValue(settingValuePath, simModel.VoiceMailNumber);
                            updateNeeded = true;
                            break;
                        default:
                            throw new ArgumentOutOfRangeException();
                    }
                }
            }

            return updateNeeded;
        }

#endif

        /// <summary>
        /// Runs the selected test cases.
        /// </summary>
        public void RunTestSetCommandExecuted()
        {
            // MTBF Follower mode can start running without any testcases selected
            if (this.settings != null && this.settings.TestRun != null && this.settings.TestRun.ExecutionMode == "Follower")
            {

                // Unregister from Fuse connection events
                FuseClient.UnRegisterFromProductPresences();
                FuseClient.UnRegisterFromProductIdentifications();
                FuseClient.SaveUsedConnections();

                this.UpdateSettings();

                this.MarbleConnector.StartFrameworkInFollowerMode(!this.IsBlackboxCheckBoxesEnabled, this.IsBltUeTestingEnabledForTestrun);
                
                this.ShowExecutorWindowCommandExecuted();

                return;
            }

            // When test run is paused run for next test case is started.
            if (this.IsTestRunPaused)
            {
                this.IsTestRunPaused = false;
                // Unregister from Fuse connection events
                FuseClient.UnRegisterFromProductPresences();
                FuseClient.UnRegisterFromProductIdentifications();
                FuseClient.SaveUsedConnections();

                this.ResumeTestExecutionStopwatches();
                this.RunNextTestCase();
                MarbleConnector.RaiseConnectorStatePropertyChanged();

                return;
            }

            // Pause for test set run is cancelled if it was already active.
            if (this.IsTestRunPauseRequested)
            {
                this.IsTestRunPauseRequested = false;
                MarbleConnector.RaiseConnectorStatePropertyChanged();

                return;
            }

            // Pause for test set run is requested if connector in running state
            if (this.TestSetModel.CurrentTestCase != null && !this.IsTestRunPauseRequested)
            {
                this.IsTestRunPauseRequested = true;
                MarbleConnector.RaiseConnectorStatePropertyChanged();

                return;
            }

            // Just stop tests if connector in running state
            if (this.TestSetModel.CurrentTestCase != null)
            {
                this.StopTestSet();
                return;
            }

            // Start execution
            this.StoppingExecution = false;
            this.TestSetModel.CurrentTestCase = null;
            this.TestSetModel.CheckedTestCases = 0;
            this.TestSetModel.CurrentIndex = -1;

            // Auto select main phone only when starting new test run
            if (this.TestSetModel.CurrentTestCase == null)
                this.DeviceCollection.AutoSelectMainDevice();

            // Count number of checked test cases
            foreach (TestCase item in this.TestSetModel.TestCases.Where(item => item.IsRoot && (item.IsWhiteboxChecked || item.IsBlackboxChecked)))
                this.TestSetModel.CheckedTestCases += 1;

            // Check selected test cases if no checked test cases exists
            if (this.TestSetModel.CheckedTestCases == 0)
            {
                foreach (TestCase tc in this.SelectedTestCases)
                {
                    if (this.IsBlackboxCheckBoxesEnabled && tc.Result != null && tc.Result.IsBlackboxModeOn)
                        tc.GetRootCase().IsBlackboxChecked = true;
                    else if(this.IsWhiteboxCheckBoxesEnabled)
                        tc.GetRootCase().IsWhiteboxChecked = true;
                    this.TestSetModel.CheckedTestCases++;
                }

                if (this.TestSetModel.CheckedTestCases == 0 && this.SelectedTestCase != null)
                {
                    this.SelectedTestCase.GetRootCase().IsWhiteboxChecked = true;
                    this.TestSetModel.CheckedTestCases++;
                }
            }

            // Clear previous results from checked tests
            // ToList() used because we edit the iterated collection
            //foreach (TestCase testCase in this.TestSetModel.TestCases.Where(tc => tc.IsRoot && (tc.IsWhiteboxChecked || tc.IsBlackboxChecked)).ToList())
                //this.TestSetModel.ClearTestCase(testCase);

            // Show output window
            if (this.logWindow == null || !this.logWindow.IsVisible)
                this.logWindow = new Executor();

            ////this.logWindow.frameworkOutput.Text = string.Empty;
            ////this.logWindow.traceLogOutput.Text = string.Empty;
            this.logWindow.Show();
            this.updateWindowTitle();
            // Unregister from Fuse connection events
            FuseClient.UnRegisterFromProductPresences();
            FuseClient.UnRegisterFromProductIdentifications();
            FuseClient.SaveUsedConnections();

            this.StartTestExecutionStopwatches();
            this.RunNextTestCase();
        }

        /// <summary>
        /// Stops the test set that is running.
        /// </summary>
        public void StopTestSetCommandExecuted()
        {            
            this.StopTestSet(this.StoppingExecution);
        }

        /// <summary>
        /// Stops the test set that is running.
        /// </summary>
        /// <param name="shutdownFramework">Whether to also shutdown the framework.</param>
        public void StopTestSet(bool shutdownFramework = false)
        {
            // MTBF Follower mode is either running or idle. No Marble connector is used
            if (this.settings != null && this.settings.TestRun != null && this.settings.TestRun.ExecutionMode == "Follower")
            {
                this.MarbleConnector.StopFollowerExecution();
                // Register to Fuse connection events
                FuseClient.RegisterToProductPresences();
                FuseClient.RegisterToProductIdentifications();
                return;
            }

            this.StoppingExecution = true;

            if (shutdownFramework)
                this.MarbleConnector.AddToQueue(new EmergencyStop("Ctrl + Break")
                    {
                        CallBackMethod = this.RunTestLabTestCaseCommandDone
                    });
            else
                this.MarbleConnector.AddToQueue(new StopExecution()
                    {
                        CallBackMethod = this.RunTestLabTestCaseCommandDone
                    });

            this.IsTestRunPauseRequested = false;
            this.IsTestRunPaused = false;
        }

        /// <summary>
        /// Check to see if NewTestsetFileCommandExecuted can be run.
        /// </summary>
        public bool NewTestsetFileCommandCanExecute()
        {
            return true;
        }

        /// <summary>
        /// Creates a new empty testset.
        /// </summary>
        public void NewTestsetFileCommandExecuted()
        {
            if (!this.ConfirmSaveOrContinueOperation())
                return;

            // Clear the TestCases collection and DocumentPath.
            this.TestSetModel.TestCases.Clear();
            this.TestSetModel.DocumentPath = string.Empty;
            this.TestSetModel.ShuffleMode = false;
            this.TestSetModel.TimedRunEnabled = this.IsTimedRunStartedForUi = false;
            this.TestSetModel.TestSetRepeatTime = this.TestSetRepeatTimeForUi = 0;
            this.TestSetModel.NextTestSetPath = string.Empty;
            this.TestSetModel.CurrentTestRuntimeUnit = this.CurrentTestRuntimeUnit = TestRuntimeUnit.Hours;
            this.TestSetModel.ScriptPathsRelativeToTestSet = false;
            this.TestSetModel.Save();
            
            this.UpdateStatusBar();
            this.TestSetModel.IsChanged = true;

            if (MarbleMainViewModel.TestReportsTabInitializationNeededEventHandler != null) MarbleMainViewModel.TestReportsTabInitializationNeededEventHandler.Invoke(null, null);

            this.TestSetModel.RefreshResultsCounts();
        }

        /// <summary>
        /// Check to see if NewTestRunCommandExecuted can be run.
        /// </summary>
        public bool NewTestRunCommandCanExecute()
        {
            return true;
        }

        /// <summary>
        /// Creates a new testset with no results from the existing testset.
        /// </summary>
        public void NewTestRunCommandExecuted()
        {
            if (!this.ConfirmSaveOrContinueOperation())
                return;

            // Show the Save File dialog.
            var saveFileDialog = new SaveFileDialog
            {
                Title = "Choose a filename for the new test run.",
                OverwritePrompt = true,
                Filter = "Testset documents|*.testset",
                RestoreDirectory = true
            };

            if (!(bool)saveFileDialog.ShowDialog())
                return; // If user cancelled dialog.

            // Clear results
            var rootCases = this.TestSetModel.TestCases.Where(tc => tc.IsRoot).ToList();
            this.TestSetModel.TestCases.Clear();
            foreach (var tc in rootCases)
            {
                tc.ClearResults();
                this.TestSetModel.TestCases.Add(tc);
            }

            // Save the testcases to the testset xml.
            this.TestSetModel.DocumentPath = saveFileDialog.FileName;
            this.TestSetModel.Save();

            this.UpdateStatusBar();

            if (MarbleMainViewModel.TestReportsTabInitializationNeededEventHandler != null) MarbleMainViewModel.TestReportsTabInitializationNeededEventHandler.Invoke(null, null);

            this.TestSetModel.RefreshResultsCounts();
        }

        /// <summary>
        /// Check to see if OpenTestsetFileCommand can be run.
        /// </summary>
        public bool OpenTestsetFileCommandCanExecute()
        {
            return true;
        }

        /// <summary>
        /// Shows the open testset dialog window.
        /// </summary>
        public void OpenTestsetFileCommandExecuted()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Testset or script documents|*.testset;*.py";
            openFileDialog.Multiselect = true;
            openFileDialog.RestoreDirectory = true;

            // Previously loaded test set is selected by default (but not loaded).
            if (!string.IsNullOrEmpty(MarbleSettingsModel.FileSettings.RecentTestSet) && File.Exists(MarbleSettingsModel.FileSettings.RecentTestSet))
            {
                string initialDirectory = Path.GetDirectoryName(MarbleSettingsModel.FileSettings.RecentTestSet);

                if (initialDirectory != null)
                {
                    openFileDialog.InitialDirectory = Path.GetFullPath(initialDirectory);
                    openFileDialog.FileName = Path.GetFileName(MarbleSettingsModel.FileSettings.RecentTestSet);
                }
            }

            bool? result = openFileDialog.ShowDialog();

            // If user cancelled open, then just return.
            if (result == false)
                return;

            string[] fileNames = openFileDialog.FileNames;

            // If one of the files to be opened is .testset file.
            if (fileNames.Any(item => Path.GetExtension(item).Equals(".testset")))
            {
                if (!this.ConfirmSaveOrContinueOperation())
                    return;
            }

            // Change mouse cursor to busy
            Mouse.OverrideCursor = System.Windows.Input.Cursors.Wait;

            try
            {
                this.LoadTestSetFile(fileNames);
                this.UpdateStatusBar();
                this.TestSetModel.HeaderRunCount = 0;
            }

            finally
            {
                // Reset mouse cursor
                Mouse.OverrideCursor = null;

                if (MarbleMainViewModel.TestReportsTabInitializationNeededEventHandler != null) MarbleMainViewModel.TestReportsTabInitializationNeededEventHandler.Invoke(null, null);

                this.TestSetModel.RefreshResultsCounts();
            }
        }

        /// <summary>
        /// Check to see if SaveTestsetFileCommandCanExecute can be run.
        /// </summary>
        public bool SaveTestsetFileCommandCanExecute()
        {
            return this.TestSetModel.IsChanged || this.TestSetModel.IsSorted;
        }

        /// <summary>
        /// Saves the testset file.
        /// </summary>
        public void SaveTestsetFileCommandExecuted()
        {
            // TempDocumentPath is set on new test set creation.
            // Open Save As -dialog.
            if (!string.IsNullOrEmpty(this.TestSetModel.TempDocumentPath))
            {
                SaveAsTestsetFileCommandExecuted();
                return;
            }

            // Save the testcases to the testset xml.
            this.TestSetModel.Save();
        }

        /// <summary>
        /// Check to see if SaveAsTestsetFileCommand can be run.
        /// </summary>
        public bool SaveAsTestsetFileCommandCanExecute()
        {
            return true;
        }

        /// <summary>
        /// Saves the testset file with new name.
        /// </summary>
        public void SaveAsTestsetFileCommandExecuted()
        {
            // Show the Save File dialog.
            var saveFileDialog = new SaveFileDialog
                {
                    OverwritePrompt = true,
                    Filter = "Testset documents|*.testset",
                    RestoreDirectory = true
                };

            if (!(bool)saveFileDialog.ShowDialog())
                return; // If user cancelled dialog.
            
            // Save the testcases to the testset xml.
            this.TestSetModel.SaveAs(saveFileDialog.FileName);
        }

        /// <summary>
        /// Check to see if ShowReportCommand can be run.
        /// </summary>
        /// <returns>Returns true if SelectedTestCase is not null</returns>
        public bool ShowReportCommandCanExecute()
        {
            this.OnPropertyChanged("SelectedReportsStatus");

            return this.SelectedTestCases.Any() && !string.IsNullOrEmpty(this.SelectedTestCase.Result.ResultPath);
        }

        /// <summary>
        /// Shows the report in default browser.
        /// </summary>
        public void ShowReportCommandExecuted()
        {
            // TODO: this temporarily generates reports from all
            this.GenerateReports(true);
        }

        /// <summary>
        /// Check to see if EmailReportCommand can be run.
        /// </summary>
        public bool EmailReportCommandCanExecute()
        {
            if (this.MainWindowTestReportViewModel == null) return false;
            if (this.SelectedTestCase == null) return false;
            if (string.IsNullOrEmpty(this.SelectedTestCase.Result.ResultPath)) return false;
            if (!File.Exists(this.SelectedTestCase.Result.ResultPath)) return false;

            return true;
        }

        /// <summary>
        /// Emails the report.
        /// </summary>
        public void EmailReportCommandExecuted()
        {
            ////// Generate report before creating mail to make sure that reports from latest results were included.
            ////this.GenerateReports(false);

            CompressWorker.RunCompressWorkerAsync(new TestReportViewModel(this.SelectedTestCase.Result));
        }

        /// <summary>
        /// Check to see if ShowConnectionWindowCommand can be run.
        /// </summary>
        public bool ShowConnectionWindowCommandCanExecute()
        {
            return true;
        }

        /// <summary>
        /// Shows the connection window.
        /// </summary>
        public void ShowConnectionWindowCommandExecuted()
        {
            if (this.connectionWindow == null || !this.connectionWindow.IsVisible)
            {
                this.connectionWindow = new ConnectionSelectionWindow();
                this.connectionWindow.Show();
            }
            else
            {
                // Open window if it was minimized
                if (this.connectionWindow.WindowState == WindowState.Minimized)
                    this.connectionWindow.WindowState = WindowState.Normal;

                this.connectionWindow.Activate();
            }
        }

        /// <summary>
        /// Check to see if ShowExecutorWindowCommand can be run.
        /// </summary>
        public bool ShowExecutorWindowCommandCanExecute()
        {
            return true;
        }

        /// <summary>
        /// Shows the executor window.
        /// </summary>
        public void ShowExecutorWindowCommandExecuted()
        {
            if (this.logWindow == null || !this.logWindow.IsVisible)
            {
                this.logWindow = new Executor();
                this.logWindow.Show();
            }
            else
            {
                // Open window if it was minimized
                if (this.logWindow.WindowState == WindowState.Minimized)
                    this.logWindow.WindowState = WindowState.Normal;

                this.logWindow.Activate();
            }
            this.updateWindowTitle();
        }

        /// <summary>
        /// Check to see if ShowCaptureToolCommand can be run.
        /// </summary>
        public bool ShowCaptureToolCommandCanExecute()
        {
            return true;
        }

        /// <summary>
        /// Shows the capture tool
        /// </summary>
        public void ShowCaptureToolCommandExecuted()
        {
            if (captureTool == null || !captureTool.IsVisible)
            {
                captureTool = new CaptureTool();
                captureTool.Show();
            }
            else
            {
                // Open window if it was minimized
                if (captureTool.WindowState == WindowState.Minimized)
                    captureTool.WindowState = WindowState.Normal;
                captureTool.Activate();
            }
        }

        #endregion

        #region [ Test Execution Timers ]

        #region [ Test Set Settings - Apply Timed Run Changes ]

        private DelegateCommand applyChangesToTimedRun;

        /// <summary>
        /// Gets a value indicating whether the changes can be applied to timed run.
        /// </summary>
        /// <returns>Bool value whether changes can be applied.</returns>
        public bool CanApplyChangesToTimedRun()
        {
            // Repeat time cannot be 0 for applying changes.
            if (this.TestSetRepeatTimeForUi == 0) return false;

            if (this.TestSetModel.TimedRunEnabled != this.IsTimedRunStartedForUi) return true;

            return this.testSetRepeatTimeSpanForUi.Ticks != this.TestSetModel.TestSetRepeatTimeSpan.Ticks;
        }

        /// <summary>
        /// Command for applying changes to timed run.
        /// </summary>
        public ICommand ApplyChangesToTimedRun
        {
            get
            {
                if (applyChangesToTimedRun == null)
                {
                    applyChangesToTimedRun = new DelegateCommand(new Action(this.ApplyChangesToTimedRunCommandExecuted), new Func<bool>(this.CanApplyChangesToTimedRun));
                }

                return applyChangesToTimedRun;
            }
        }

        /// <summary>
        /// Applies changes to timed run.
        /// </summary>
        public void ApplyChangesToTimedRunCommandExecuted()
        {
            this.TestSetModel.TimedRunEnabled = this.IsTimedRunStartedForUi;
            this.TestSetModel.TestSetRepeatTime = this.TestSetRepeatTimeForUi;
            this.TestSetModel.IsChanged = true;
        }

        #endregion [ Test Set Settings - Apply Timed Run Changes ]

        #region [ Test Set Settings - Undo Timed Run Changes ]

        private DelegateCommand undoChangesToTimedRun;

        /// <summary>
        /// Gets a value indicating whether the changes can be undone to timed run.
        /// </summary>
        /// <returns>Bool value whether changes can be undone.</returns>
        public bool CanUndoChangesToTimedRun()
        {
            return this.IsTimedRunStartedForUi != this.TestSetModel.TimedRunEnabled
                    || this.TestSetRepeatTimeForUi != this.TestSetModel.TestSetRepeatTime;
        }

        /// <summary>
        /// Command for undoes changes to timed run.
        /// </summary>
        public ICommand UndoChangesToTimedRun
        {
            get
            {
                if (undoChangesToTimedRun == null)
                {
                    undoChangesToTimedRun = new DelegateCommand(new Action(this.UndoChangesToTimedRunCommandExecuted), new Func<bool>(this.CanUndoChangesToTimedRun));
                }

                return undoChangesToTimedRun;
            }
        }

        /// <summary>
        /// Undoes changes to timed run.
        /// </summary>
        public void UndoChangesToTimedRunCommandExecuted()
        {
            this.IsTimedRunStartedForUi = this.TestSetModel.TimedRunEnabled;
            this.TestSetRepeatTimeForUi = this.TestSetModel.TestSetRepeatTime;
        }

        #endregion [ Test Set Settings - Undo Timed Run Changes ]

        #region [ Test Set Settings - UI Properties ]

        private TimeSpan testSetRepeatTimeSpanForUi;

        /// <summary>
        /// Gets or sets duration for the timed run. Duration is changed after applying the changes for the timed run.
        /// </summary>
        public int TestSetRepeatTimeForUi
        {
            get
            {
                switch (this.TestSetModel.CurrentTestRuntimeUnit)
                {
                    case TestRuntimeUnit.Hours:
                        return Convert.ToInt32(this.testSetRepeatTimeSpanForUi.TotalHours);
                    case TestRuntimeUnit.Days:
                        return Convert.ToInt32(this.testSetRepeatTimeSpanForUi.TotalDays);
                    default:
                        return Convert.ToInt32(this.testSetRepeatTimeSpanForUi.TotalMinutes);
                }
            }
            set
            {
                switch (this.TestSetModel.CurrentTestRuntimeUnit)
                {
                    case TestRuntimeUnit.Minutes:
                        this.testSetRepeatTimeSpanForUi = new TimeSpan(0, 0, value, 0);
                        break;
                    case TestRuntimeUnit.Hours:
                        this.testSetRepeatTimeSpanForUi = new TimeSpan(0, value, 0, 0);
                        break;
                    case TestRuntimeUnit.Days:
                        this.testSetRepeatTimeSpanForUi = new TimeSpan(value, 0, 0, 0);
                        break;
                    default:
                        this.testSetRepeatTimeSpanForUi = new TimeSpan(0, 0, value, 0);
                        break;
                }

                this.OnPropertyChanged("TestSetRepeatTimeForUi");
            }
        }

        /// <summary>
        /// Gets or sets a value indicating the current test runtime unit.
        /// </summary>
        public TestRuntimeUnit CurrentTestRuntimeUnit
        {
            get
            {
                return this.TestSetModel.CurrentTestRuntimeUnit;
            }
            set
            {
                this.TestSetModel.CurrentTestRuntimeUnit = value;
                this.OnPropertyChanged("CurrentTestRuntimeUnit");
                this.OnPropertyChanged("TestSetRepeatTimeForUi");
            }
        }

        /// <summary>
        /// Gets or sets whether the timed run is started. Timed run is enabled/disabled after applying the changes for the timed run.
        /// </summary>
        public bool IsTimedRunStartedForUi
        {
            get
            {
                return this.isTimedRunStartedForUi;
            }
            set
            {
                this.isTimedRunStartedForUi = value;
                this.OnPropertyChanged("IsTimedRunStartedForUi");
            }
        }

        /// <summary>
        /// Gets or sets whether the shuffle mode is enabled. Shuffle mode is enabled/disabled after applying the changes for the timed run.
        /// </summary>
        public bool IsShuffleModeEnabledForUi
        {
            get
            {
                return this.isShuffleModeEnabledForUi;
            }
            set
            {
                this.isShuffleModeEnabledForUi = value;
                this.OnPropertyChanged("IsShuffleModeEnabledForUi");
            }
        }

        #endregion [ Test Set Settings - UI Properties ]

        ////public TimeSpan TestExecutionTimeSpan { get { return new TimeSpan(DateTime.Now.Ticks - this.TestSetModel.TestSetRunStart.Ticks - this.TestExecutionPauseStopwatch.ElapsedTicks); } }

        /// <summary>
        /// Gets the test execution time span.
        /// </summary>
        public TimeSpan TestExecutionTimeSpan { get { return testExecutionStopwatch != null ? this.testExecutionStopwatch.Elapsed : TimeSpan.Zero; } }

        /// <summary>
        /// Gets the test execution time span text.
        /// </summary>
        public string TestExecutionTimeSpanText
        {
            get
            {
                TimeSpan currentTimeSpan = this.TestExecutionTimeSpan;

                if (currentTimeSpan == TimeSpan.Zero) return string.Empty;

                string testExecutionTimeText;

                if (currentTimeSpan.TotalDays >= 1)
                    // Display format: "1d 02:03:04"
                    testExecutionTimeText = currentTimeSpan.ToString(@"d\d\ hh\:mm\:ss");
                else
                    // Display format: "01:02:03"
                    testExecutionTimeText = currentTimeSpan.ToString(@"hh\:mm\:ss");

                if (!this.TestSetModel.TimedRunEnabled) return testExecutionTimeText;

                // When timed run is active also timed run duration is displayed.

                if (this.TestSetModel.TestSetRepeatTimeSpan.TotalDays >= 1)
                    // Display format: "1d 02:03:04"
                    testExecutionTimeText += " / " + this.TestSetModel.TestSetRepeatTimeSpan.ToString(@"d\d\ hh\:mm\:ss");
                else
                    // Display format: "01:02:03"
                    testExecutionTimeText += " / " + this.TestSetModel.TestSetRepeatTimeSpan.ToString(@"hh\:mm\:ss");

                return testExecutionTimeText;
            }
        }

        /// <summary>
        /// Gets the test execution time tool tip.
        /// </summary>
        public string TestExecutionTimeToolTip
        {
            get
            {
                StringBuilder toolTip = new StringBuilder();

                if (this.TestSetModel.TestSetRunStart.Ticks > 0) 
                    toolTip.Append("Test execution started:\t" + this.TestSetModel.TestSetRunStart);

                if (this.TestSetModel.TestSetRunEnd.Ticks > 0)
                    toolTip.Append("\nTest execution ended:\t" + this.TestSetModel.TestSetRunEnd);

                if (this.testExecutionStopwatch.ElapsedTicks > 0)
                {
                    if (this.testExecutionStopwatch.Elapsed.TotalDays >= 1)
                        toolTip.Append("\nTime elapsed:\t\t" + this.testExecutionStopwatch.Elapsed.ToString(@"d\d\ hh\:mm\:ss"));
                    else
                        toolTip.Append("\nTime elapsed:\t\t" + this.testExecutionStopwatch.Elapsed.ToString(@"hh\:mm\:ss"));
                }

                if (this.testExecutionPauseStopwatch.ElapsedTicks > 0)
                {
                    if (this.testExecutionPauseStopwatch.Elapsed.TotalDays >= 1)
                        toolTip.Append("\nTime on pause:\t\t" + this.testExecutionPauseStopwatch.Elapsed.ToString(@"d\d\ hh\:mm\:ss"));
                    else
                        toolTip.Append("\nTime on pause:\t\t" + this.testExecutionPauseStopwatch.Elapsed.ToString(@"hh\:mm\:ss"));
                }

                return toolTip.ToString();

            }
        }

        private Stopwatch testExecutionStopwatch { get; set; }

        private Stopwatch testExecutionPauseStopwatch { get; set; }

        public DispatcherTimer TestExecutionDispatcherTimer;

        /// <summary>
        /// Initializes test execution dispatcher timer and stopwatches.
        /// </summary>
        public void InitializeTestExecutionDispatcherTimer()
        {
            this.TestExecutionDispatcherTimer = new DispatcherTimer();
            this.TestExecutionDispatcherTimer.Tick += new EventHandler(this.testExecutionDispatcherTimerTick);
            this.TestExecutionDispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 500);

            if (this.testExecutionStopwatch == null)
                this.testExecutionStopwatch = new Stopwatch();

            if (this.testExecutionPauseStopwatch == null)
                this.testExecutionPauseStopwatch = new Stopwatch();

            this.testExecutionPauseStopwatch.Reset();
        }

        /// <summary>
        /// Starts test execution stopwatches. Use this instead of individual stopwatch methods.
        /// </summary>
        public void StartTestExecutionStopwatches()
        {
            this.testExecutionStopwatch.Reset();
            this.testExecutionPauseStopwatch.Reset();
            this.TestExecutionDispatcherTimer.Start();
            this.testExecutionStopwatch.Start();

            this.testExecutionDispatcherTimerTick(null, null);
        }

        /// <summary>
        /// Pauses test execution stopwatches. Use this instead of individual stopwatch methods.
        /// </summary>
        public void PauseTestExecutionStopwatches()
        {
            // Register to Fuse connection events
            FuseClient.RegisterToProductPresences();
            FuseClient.RegisterToProductIdentifications();

            this.testExecutionStopwatch.Stop();
            this.testExecutionPauseStopwatch.Start();

            this.testExecutionDispatcherTimerTick(null, null);
        }

        /// <summary>
        /// Resumes test execution stopwatches. Use this instead of individual stopwatch methods.
        /// </summary>
        public void ResumeTestExecutionStopwatches()
        {
            // Unregister from Fuse connection events
            FuseClient.UnRegisterFromProductPresences();
            FuseClient.UnRegisterFromProductIdentifications();

            this.testExecutionPauseStopwatch.Stop();
            this.testExecutionStopwatch.Start();
            
            this.testExecutionDispatcherTimerTick(null, null);
        }

        /// <summary>
        /// Stops test execution stopwatches. Use this instead of individual stopwatch methods.
        /// </summary>
        public void StopTestExecutionStopwatches()
        {
            this.TestSetModel.TestSetRunEnd = DateTime.Now;

            this.testExecutionPauseStopwatch.Stop();
            this.testExecutionStopwatch.Stop();
            this.TestExecutionDispatcherTimer.Stop();

            this.testExecutionDispatcherTimerTick(null, null);
        }

        private void testExecutionDispatcherTimerTick(object sender, EventArgs e)
        {
            this.OnPropertyChanged("TestExecutionTimeSpan");
            this.OnPropertyChanged("TestExecutionTimeSpanText");
            this.OnPropertyChanged("TestExecutionTimeToolTip");
        }

        #endregion [ Test Execution Timers ]

        #region [ Enable Tracing ]

        private DelegateCommand enableTracing;

        public bool CanEnableTracing()
        {
            return true;
        }

        /// <summary>
        /// Command for copying selected test case results to clipboard.
        /// </summary>
        public ICommand EnableTracing
        {
            get {
                return enableTracing ??
                       (enableTracing =
                        new DelegateCommand(new Action(EnableTracingExecuted), new Func<bool>(CanEnableTracing)));
            }
        }

        /// <summary>
        /// Copies all test case results to clipboard.
        /// </summary>
        public void EnableTracingExecuted()
        {
            if (this.IsTracingEnabledForTestrun && this.FuseClient.TraceConnection == null)
                this.ShowConnectionWindowCommand.Execute(null);
        }

        #endregion [ Enable Tracing ]

        #region [ Enable Memory Leak Detection ]

        private DelegateCommand enableMemoryLeakDetection;

        public bool CanEnableMemoryLeakDetection()
        {
            return true;
        }

        /// <summary>
        /// Command for copying selected test case results to clipboard.
        /// </summary>
        public ICommand EnableMemoryLeakDetection
        {
            get
            {
                return enableMemoryLeakDetection ??
                       (enableMemoryLeakDetection =
                        new DelegateCommand(new Action(EnableMemoryLeakDetectionExecuted), new Func<bool>(CanEnableMemoryLeakDetection)));
            }
        }

        /// <summary>
        /// Copies all test case results to clipboard.
        /// </summary>
        public void EnableMemoryLeakDetectionExecuted()
        {
            if (!this.IsMemoryLeakTestingEnabledForTestrun ||
                (this.FuseClient.TraceConnection != null &&
                 (this.FuseClient.TraceConnection.Connection.Type == EnumConnectionType.FIDO ||
                  this.FuseClient.TraceConnection.Connection.Type == EnumConnectionType.MUSTI ||
                  this.FuseClient.TraceConnection.Connection.Type == EnumConnectionType.MUSTI_USB))) return;

            // Get all Fido or Musti type connections
            var traceCons =
                this.FuseClient.Connections.Where(
                    p => p.Connection.Type == EnumConnectionType.FIDO ||
                        p.Connection.Type == EnumConnectionType.MUSTI ||
                        p.Connection.Type == EnumConnectionType.MUSTI_USB).ToList();

            if (traceCons.Count == 1)
            {
                traceCons[0].IsTrace = true;
                // Show pop-up to user
                return;
            }

            // Clear trace connection selection because it may be hidden (mem leak support only musti or fido).
            this.FuseClient.Connections.ClearOthers("Clear all connections", EnumConnectionUsage.Trace);
            this.ShowConnectionWindowCommand.Execute(null);
        }

        #endregion [ Enable Memory Leak Detection ]

        #region [ SIM Manager ]

        ////private DelegateCommand openSimManager;

        ////public bool CanSimManagerWindowOpen()
        ////{
        ////    return true;
        ////}

        /////// <summary>
        /////// Command for opening SIM manager.
        /////// </summary>
        ////public ICommand OpenSimManager
        ////{
        ////    get
        ////    {
        ////        if (openSimManager == null)
        ////        {
        ////            openSimManager = new DelegateCommand(new Action(OpenSimManagerCommandExecuted), new Func<bool>(CanSimManagerWindowOpen));
        ////        }

        ////        return openSimManager;
        ////    }
        ////}

        /////// <summary>
        /////// Shows SIM manager dialog.
        /////// </summary>
        ////public void OpenSimManagerCommandExecuted()
        ////{
        ////    Window simManagerWindow = new Window();
        ////    simManagerWindow.Title = "Marble - SIM Manager";
        ////    simManagerWindow.Icon = new BitmapImage(new Uri("pack://application:,,,/MarbleLibrary;component/Images/Marble.M.Icon.ico", UriKind.RelativeOrAbsolute));
        ////    simManagerWindow.Content = new SimManagerView();
        ////    ((SimManagerView)simManagerWindow.Content).ParentWindow = simManagerWindow;
        ////    simManagerWindow.Width = 640;
        ////    simManagerWindow.Height = double.NaN;
        ////    simManagerWindow.SizeToContent = SizeToContent.Height;

        ////    simManagerWindow.ShowDialog();
        ////}

        #endregion [ SIM Manager ]

        #region [ Flasher ]

        ////private DelegateCommand openFlasher;

        ////public bool CanFlasherWindowOpen()
        ////{
        ////    return true;
        ////}

        /////// <summary>
        /////// Command for opening Flasher.
        /////// </summary>
        ////public ICommand OpenFlasher
        ////{
        ////    get
        ////    {
        ////        if (openFlasher == null)
        ////        {
        ////            openFlasher = new DelegateCommand(new Action(this.OpenFlasherCommandExecuted), new Func<bool>(this.CanFlasherWindowOpen));
        ////        }

        ////        return openFlasher;
        ////    }
        ////}

        /////// <summary>
        /////// Shows Flasher dialog.
        /////// </summary>
        ////public void OpenFlasherCommandExecuted()
        ////{
        ////    Window flasherWindow = new Window();
        ////    flasherWindow.Title = "Marble - Flasher";
        ////    flasherWindow.Icon = new BitmapImage(new Uri("pack://application:,,,/MarbleLibrary;component/Images/Marble.M.Icon.ico", UriKind.RelativeOrAbsolute));
        ////    flasherWindow.Content = new FlasherView();
        ////    ((FlasherView)flasherWindow.Content).ParentWindow = flasherWindow;
        ////    flasherWindow.ResizeMode = ResizeMode.CanMinimize;
        ////    flasherWindow.Width = 640;
        ////    flasherWindow.SizeToContent = SizeToContent.WidthAndHeight;
        ////    //flasherWindow.Height = 250;

        ////    flasherWindow.ShowDialog();
        ////}

        #endregion [ Flasher ]

        #region [ QC Settings ]

        ////private DelegateCommand openQcSettings;

        ////public bool CanQcSettingsWindowOpen()
        ////{
        ////    return true;
        ////}

        /////// <summary>
        /////// Command for opening Flasher.
        /////// </summary>
        ////public ICommand OpenQcSettings
        ////{
        ////    get
        ////    {
        ////        if (openQcSettings == null)
        ////        {
        ////            openQcSettings = new DelegateCommand(new Action(this.OpenQcSettingsCommandExecuted), new Func<bool>(this.CanQcSettingsWindowOpen));
        ////        }

        ////        return openQcSettings;
        ////    }
        ////}

        /////// <summary>
        /////// Shows Flasher dialog.
        /////// </summary>
        ////public void OpenQcSettingsCommandExecuted()
        ////{
        ////    Window qcSettingsWindow = new Window();
        ////    qcSettingsWindow.Title = "Marble - QC Import / Export";
        ////    qcSettingsWindow.Icon = new BitmapImage(new Uri("pack://application:,,,/MarbleLibrary;component/Images/Marble.M.Icon.ico", UriKind.RelativeOrAbsolute));
        ////    qcSettingsWindow.Content = new QcSettingsView();
        ////    ((QcSettingsView)qcSettingsWindow.Content).ParentWindow = qcSettingsWindow;
        ////    qcSettingsWindow.ResizeMode = ResizeMode.CanMinimize;
        ////    qcSettingsWindow.Width = 640;
        ////    qcSettingsWindow.SizeToContent = SizeToContent.WidthAndHeight;
        ////    //flasherWindow.Height = 250;

        ////    qcSettingsWindow.ShowDialog();
        ////}

        #endregion [ QC Settings ]

        #region [ Simple Text Editor ]

        private DelegateCommand openSimpleTextEditor;

        public bool CanSimpleTextEditorWindowOpen()
        {
            return this.SelectedTestCase != null;
        }

        /// <summary>
        /// Command for opening SIM manager.
        /// </summary>
        public ICommand OpenSimpleTextEditor
        {
            get
            {
                if (openSimpleTextEditor == null)
                {
                    openSimpleTextEditor = new DelegateCommand(new Action(OpenSimpleTextEditorCommandExecuted), new Func<bool>(CanSimpleTextEditorWindowOpen));
                }

                return openSimpleTextEditor;
            }
        }

        /// <summary>
        /// Opens simple text editor.
        /// </summary>
        public void OpenSimpleTextEditorCommandExecuted()
        {
            if (this.SelectedTestCase == null) return;

            string testCaseFilePath =
                FileUtilities.MergeFolderAndFileNameToFullFilePath(
                    this.SelectedTestCase.Script.Directory,
                    this.SelectedTestCase.Script.file,
                    ".py");

            SimpleTextEditorView simpleTextEditorWindow = new SimpleTextEditorView(testCaseFilePath);
            simpleTextEditorWindow.Loaded += delegate
                {
                    simpleTextEditorWindow.Width = simpleTextEditorWindow.treeViewCodeStructure.ActualWidth + 700;
                    simpleTextEditorWindow.SelectText(
                        "def " + this.SelectedTestCase.Script.method + "(self):");
                };

            simpleTextEditorWindow.Height = 700;
            simpleTextEditorWindow.Show();
        }

        #endregion [ SIM Manager ]

        #region [ Open Report ]

        private DelegateCommand openReport;

        public bool CanReportOpen()
        {
            return true;
        }

        /// <summary>
        /// Command for opening SIM manager.
        /// </summary>
        public ICommand OpenReportCommand
        {
            get
            {
                if (openReport == null)
                {
                    openReport = new DelegateCommand(new Action(OpenReportCommandExecuted), new Func<bool>(CanReportOpen));
                }

                return openReport;
            }
        }

        /// <summary>
        /// Shows SIM manager dialog.
        /// </summary>
        public void OpenReportCommandExecuted()
        {
            string filePath = FileUtilities.ShowOpenFileDialogForMarbleTestReport();

            if (string.IsNullOrEmpty(filePath)) return;

            Window reportWindow = new Window();
            reportWindow.Title = "Marble - Test Report - " + filePath;
            reportWindow.Icon = new BitmapImage(new Uri("pack://application:,,,/MarbleLibrary;component/Images/Marble.M.Icon.ico", UriKind.RelativeOrAbsolute));
            reportWindow.Content = new TestReportView(filePath, true, true);
            ((TestReportView)reportWindow.Content).ParentWindow = reportWindow;
            reportWindow.Width = 800;
            reportWindow.Height = 600;

            reportWindow.Closing += new CancelEventHandler(this.reportWindow_Closing);

            reportWindow.Show();
        }

        private void reportWindow_Closing(object sender, CancelEventArgs e)
        {
            if (sender == null) return;

            Window reportWindow = sender as Window;

            if (reportWindow == null) return;

            if (((TestReportView)reportWindow.Content) != null)
            {
                ((TestReportView)reportWindow.Content).DisposeAllGraphViews();

                if (TestReportView.WindowedTestReportViews.Contains((TestReportView)reportWindow.Content))
                    TestReportView.WindowedTestReportViews.Remove((TestReportView)reportWindow.Content);

                reportWindow.Content = null;
            }

            reportWindow = null;
            GC.Collect();
        }

        #endregion [ Open Report ]

        #region [ Open Settings ]

        private DelegateCommand openSettings;

        /// <summary>
        /// Determines whether the settings window can be displayed.
        /// </summary>
        /// <returns>Value of <c>true</c> if the window can be displayed, otherwise <c>false</c> is returned.</returns>
        public bool CanSettingsWindowOpen()
        {
            // We can only open the settings window if have some setting modules
            return (SettingsManager.Instance.Count > 0);
        }

        /// <summary>
        /// Command for opening settings.
        /// </summary>
        public ICommand OpenSettings
        {
            get
            {
                if (openSettings == null)
                {
                    openSettings = new DelegateCommand(new Action(this.OpenSettingsCommandExecuted), new Func<bool>(this.CanSettingsWindowOpen));
                }

                return openSettings;
            }
        }

        /// <summary>
        /// Shows the settings dialog.
        /// </summary>
        public void OpenSettingsCommandExecuted()
        {
            // Change mouse cursor to busy
            Mouse.OverrideCursor = System.Windows.Input.Cursors.Wait;

            // Update the settings
            UpdateSettings();

            Window settingsWindow = null;

            try
            {
                settingsWindow = new Window
                    {
                        Title = "Marble - Settings",
                        Icon =
                            new BitmapImage(
                                new Uri("pack://application:,,,/MarbleLibrary;component/Images/Marble.M.Icon.ico",
                                        UriKind.RelativeOrAbsolute)),
                        Width = 740,
                        Height = 520,
                        MinWidth = 240,
                        MinHeight = 220,
                        //WindowStyle = WindowStyle.ToolWindow,
                        //Owner = Application.Current.MainWindow, // "Cannot set Owner property to itself" - Why on earth this doesn't work
                        //ShowInTaskbar = false,
                        Content = new SettingsView(new SettingsViewModel())
                    };
                ((SettingsView)settingsWindow.Content).ParentWindow = settingsWindow;
            }

            finally
            {
                // Reset mouse cursor
                Mouse.OverrideCursor = null;
            }

            if (settingsWindow != null)
            {
                settingsWindow.ShowDialog();

                this.CheckHWControllerTypeAndAvailability();
                this.updateWindowTitle();
                this.StartVideoRecorderIfEnabled();
            }
        }

        #endregion

        #region [ Open Marble Wiki ]

        private DelegateCommand openMarbleWiki;

        public bool CanMarbleWikiOpen()
        {
            return true;
        }

        /// <summary>
        /// Command for opening Marble Wiki.
        /// </summary>
        public ICommand OpenMarbleWikiCommand
        {
            get
            {
                if (openMarbleWiki == null)
                {
                    openMarbleWiki = new DelegateCommand(new Action(OpenMarbleWikiCommandExecuted), new Func<bool>(CanMarbleWikiOpen));
                }

                return openMarbleWiki;
            }
        }

        /// <summary>
        /// Shows Marble Wiki dialog.
        /// </summary>
        public void OpenMarbleWikiCommandExecuted()
        {
            if (marbleWikiWindow != null && marbleWikiWindow.IsVisible)
            {
                marbleWikiWindow.Focus();
                return;
            }

            marbleWikiWindow = new Window();
            marbleWikiWindow.Title = "Marble - Wiki";
            marbleWikiWindow.Icon = new BitmapImage(new Uri("pack://application:,,,/MarbleLibrary;component/Images/Marble.M.Icon.ico", UriKind.RelativeOrAbsolute));
            marbleWikiWindow.Content = new MarbleWikiView();
            ((MarbleWikiView)marbleWikiWindow.Content).ParentWindow = marbleWikiWindow;
            marbleWikiWindow.Width = 800;
            marbleWikiWindow.Height = 600;
            ((MarbleWikiView)marbleWikiWindow.Content).NavigateToMarbleWiki();
            marbleWikiWindow.Show();
        }

        #endregion [ Open Marble Wiki ]

        #region [ Export Test Case Report as Test Case Package ]

        private DelegateCommand exportTestCaseResultAsTestCasePackage;

        public bool CanExportTestCaseResultAsTestCasePackage()
        {
            return this.canExportTestCaseResult();
        }

        private bool canExportTestCaseResult()
        {
            if (this.MainWindowTestReportViewModel == null) return false;
            if (this.SelectedTestCase == null) return false;
            if (string.IsNullOrEmpty(this.SelectedTestCase.Result.ResultPath)) return false;
            if (!File.Exists(this.SelectedTestCase.Result.ResultPath)) return false;

            return true;
        }

        /// <summary>
        /// Command for exporting Test Case package.
        /// </summary>
        public ICommand ExportTestCaseResultAsTestCasePackageCommand
        {
            get
            {
                if (exportTestCaseResultAsTestCasePackage == null)
                {
                    exportTestCaseResultAsTestCasePackage = new DelegateCommand(new Action(ExportTestCaseResultAsTestCasePackageCommandExecuted), new Func<bool>(CanExportTestCaseResultAsTestCasePackage));
                }

                return exportTestCaseResultAsTestCasePackage;
            }
        }

        /// <summary>
        /// Export test report of test case.
        /// </summary>
        public void ExportTestCaseResultAsTestCasePackageCommandExecuted()
        {
            this.MainWindowTestReportViewModel.CompressTestReport();
        }

        #endregion [ Export Test Case Report as Test Case Package ]

        #region [ Export Test Case Report as Document ]

        private DelegateCommand exportTestCaseResultAsDocument;

        public bool CanExportTestCaseResultAsDocument()
        {
            return this.canExportTestCaseResult();
        }

        /// <summary>
        /// Command for exporting Test Case package.
        /// </summary>
        public ICommand ExportTestCaseResultAsDocumentCommand
        {
            get
            {
                if (exportTestCaseResultAsDocument == null)
                {
                    exportTestCaseResultAsDocument = new DelegateCommand(new Action(ExportTestCaseResultAsDocumentCommandExecuted), new Func<bool>(CanExportTestCaseResultAsDocument));
                }

                return exportTestCaseResultAsDocument;
            }
        }

        /// <summary>
        /// Export test report of test case.
        /// </summary>
        public void ExportTestCaseResultAsDocumentCommandExecuted()
        {
            if (App.ViewModel.SelectedTestCase == null) return;

            string filePath = FileUtilities.ShowSaveAsFileDialogForMarbleTestReportPdf(string.Empty, Path.GetFileNameWithoutExtension(App.ViewModel.SelectedTestCase.Result.ResultPath));

            if (string.IsNullOrEmpty(filePath) || filePath == Path.GetFileNameWithoutExtension(App.ViewModel.SelectedTestCase.Result.ResultPath)) return;

            this.MainWindowTestReportViewModel.ExportTestReportAsDocument(filePath);
        }

        #endregion [ Export Test Case Report as Document ]

        #region [ Copy Selected Test Case Results To Clipboard ]

        private DelegateCommand copySelectedTestCaseResultsToClipboardCommand;

        public bool CanCopySelectedTestCaseResultsToClipboard()
        {
            return true;
        }

        /// <summary>
        /// Command for copying selected test case results to clipboard.
        /// </summary>
        public ICommand CopySelectedTestCaseResultsToClipboardCommand
        {
            get
            {
                if (copySelectedTestCaseResultsToClipboardCommand == null)
                {
                    copySelectedTestCaseResultsToClipboardCommand = new DelegateCommand(new Action(CopySelectedTestCaseResultsToClipboardCommandExecuted), new Func<bool>(CanCopySelectedTestCaseResultsToClipboard));
                }

                return copySelectedTestCaseResultsToClipboardCommand;
            }
        }

        /// <summary>
        /// Copies all test case results to clipboard.
        /// </summary>
        public void CopySelectedTestCaseResultsToClipboardCommandExecuted()
        {
            TestCaseUtilities.CopyExcelCompatibleTestCaseResultsToClipboard(this.SelectedTestCases.ToList());
        }

        #endregion [ Copy Selected Test Case Results To Clipboard ]

        #region [ Copy All Test Case Results To Clipboard ]

        private DelegateCommand copyAllTestCaseResultsToClipboardCommand;

        public bool CanCopyAllTestCaseResultsToClipboard()
        {
            return true;
        }

        /// <summary>
        /// Command for copying all test case results to clipboard.
        /// </summary>
        public ICommand CopyAllTestCaseResultsToClipboardCommand
        {
            get
            {
                if (copyAllTestCaseResultsToClipboardCommand == null)
                {
                    copyAllTestCaseResultsToClipboardCommand = new DelegateCommand(new Action(CopyAllTestCaseResultsToClipboardCommandExecuted), new Func<bool>(CanCopyAllTestCaseResultsToClipboard));
                }

                return copyAllTestCaseResultsToClipboardCommand;
            }
        }

        /// <summary>
        /// Copies selected test case results to clipboard.
        /// </summary>
        public void CopyAllTestCaseResultsToClipboardCommandExecuted()
        {
            TestCaseUtilities.CopyExcelCompatibleTestCaseResultsToClipboard(this.TestSetModel.TestCases.ToList());
        }

        #endregion [ Copy All Test Case Results To Clipboard ]

        #region [ Clear results from selected test cases ]

        private DelegateCommand clearResultsFromSelectedTestCases;

        /// <summary>
        /// Command for clearing all results from selected test cases
        /// </summary>
        public ICommand ClearResultsFromSelectedTestCases
        {
            get
            {
                if (clearResultsFromSelectedTestCases == null)
                {
                    clearResultsFromSelectedTestCases = new DelegateCommand(ClearResultsFromSelectedTestCasesExecuted, CanClearResultsFromSelectedTestCases);
                }

                return clearResultsFromSelectedTestCases;
            }
        }

        public bool CanClearResultsFromSelectedTestCases()
        {
            return this.SelectedFirstLevelTestCases.Any(tc => tc.RunCount > 0);
        }

        /// <summary>
        /// Clears all results from selected test cases
        /// </summary>
        public void ClearResultsFromSelectedTestCasesExecuted()
        {
            var result = MessageBox.Show("Are you sure you want to delete all results from selected test cases?",
                                         "Delete all results?", MessageBoxButton.YesNo);
            if (result == MessageBoxResult.Yes)
            {
                foreach (TestCase testCase in this.SelectedFirstLevelTestCases.ToList())
                {
                    this.TestSetModel.ClearTestCase(testCase, true);
                }

                if (MarbleMainViewModel.TestReportsTabInitializationNeededEventHandler != null) MarbleMainViewModel.TestReportsTabInitializationNeededEventHandler.Invoke(null, null);

                this.TestSetModel.RefreshResultsCounts();
            }
        }

        #endregion [ Clear results from selected test cases ]

        #region [ Generate Leader-Follower Test Report ]

        private DelegateCommand generateLeaderFollowerReportFromExistingResults;

        private DelegateCommand generateLeaderFollowerReportFromCurrentResults;

        /// <summary>
        /// Gets whether GenerateLeaderFollowerReportFromExistingResultsCommand can be executed.
        /// </summary>
        /// <returns></returns>
        public bool CanGenerateLeaderFollowerReportFromExistingResults()
        {
            return this.IsMtbfLeaderMode;
        }

        /// <summary>
        /// Command for generating MTBF Leader-Follower report from old test results.
        /// </summary>
        public ICommand GenerateLeaderFollowerReportFromExistingResultsCommand
        {
            get
            {
                if (generateLeaderFollowerReportFromExistingResults == null)
                {
                    generateLeaderFollowerReportFromExistingResults = new DelegateCommand(new Action(this.GenerateLeaderFollowerReportFromExistingResultsCommandExecuted), new Func<bool>(this.CanGenerateLeaderFollowerReportFromExistingResults));
                }

                return generateLeaderFollowerReportFromExistingResults;
            }
        }

        /// <summary>
        /// Gets whether GenerateLeaderFollowerReportFromCurrentResultsCommand can be executed.
        /// </summary>
        /// <returns></returns>
        public bool CanGenerateLeaderFollowerReportFromCurrentResults()
        {
            return this.HasMtbfLeaderFollowerResults;
        }

        /// <summary>
        /// Command for generating MTBF Leader-Follower report from current test results.
        /// </summary>
        public ICommand GenerateLeaderFollowerReportFromCurrentResultsCommand
        {
            get
            {
                if (generateLeaderFollowerReportFromCurrentResults == null)
                {
                    generateLeaderFollowerReportFromCurrentResults = new DelegateCommand(new Action(this.GenerateLeaderFollowerReportFromCurrentResultsCommandExecuted), new Func<bool>(this.CanGenerateLeaderFollowerReportFromCurrentResults));
                }

                return generateLeaderFollowerReportFromCurrentResults;
            }
        }

        /// <summary>
        /// Generates MTBF Leader-Follower report from old existing test results.
        /// </summary>
        public void GenerateLeaderFollowerReportFromExistingResultsCommandExecuted()
        {
            string testSetsPath = Environment.CurrentDirectory.Substring(0, Environment.CurrentDirectory.LastIndexOf(@"\") + 1);
            testSetsPath += @"test_sets";
            
            if (!Directory.Exists(testSetsPath))
                testSetsPath = string.Empty;

            string filePath = FileUtilities.ShowOpenFileDialogForLeaderFollowerTestReport(testSetsPath);

            if (string.IsNullOrEmpty(filePath)) return;

            this.generateLeaderFollowerReport(filePath);
        }

        /// <summary>
        /// Generates MTBF Leader-Follower report from current test results.
        /// </summary>
        public void GenerateLeaderFollowerReportFromCurrentResultsCommandExecuted()
        {
            string testsetDir = Path.GetDirectoryName(TestSetModel.DocumentPath);
            string testsetName = Path.GetFileNameWithoutExtension(TestSetModel.DocumentPath);
            string resultPath = Path.Combine(testsetDir, testsetName + "_results");
            string resultFileName = testsetName + "_results.cache";
            string resultFile = Path.Combine(resultPath, resultFileName);
            if (File.Exists(resultFile))
                this.generateLeaderFollowerReport(resultFile);
        }

        /// <summary>
        /// Gets a value indicating whether running MTBF in Leader mode.
        /// </summary>
        public bool IsMtbfLeaderMode
        {
            get
            {
                if (this.settings != null && this.settings.TestRun != null && this.settings.TestRun.ExecutionMode == "Leader")
                    return true;
                return false;
            }
        }

        /// <summary>
        /// Gets a value indicating whether running MTBF in Leader mode.
        /// </summary>
        public bool HasMtbfLeaderFollowerResults
        {
            get
            {
                try
                {
                    string testsetDir = Path.GetDirectoryName(TestSetModel.DocumentPath);
                    string testsetName = Path.GetFileNameWithoutExtension(TestSetModel.DocumentPath);
                    string resultPath = Path.Combine(testsetDir, testsetName + "_results");
                    string resultFileName = testsetName + "_results.cache";
                    string resultFile = Path.Combine(resultPath, resultFileName);
                    return File.Exists(resultFile) && IsMtbfLeaderMode;
                }
                catch
                {
                    return false;
                }
            }
        }

        public void UpdateMtbReportingRelatedControls()
        {
            this.OnPropertyChanged("IsMtbfLeaderMode");
            this.OnPropertyChanged("HasMtbfLeaderFollowerResults");
        }

        private void generateLeaderFollowerReport(string cachePath)
        {
            // start report generator process
            reportGenerator = new Process();
            reportGenerator.StartInfo.FileName = "ipy";
            string outputFileName = Path.GetFileNameWithoutExtension(cachePath) + "_" + DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss") + ".html";
            string arguments = Path.GetFullPath(@"..\framework\core\reporting\leader_report_generator.py") + " " + cachePath + " " + this.settings.TestRun.LeaderReportingOptions + " -o " + outputFileName;

            reportGenerator.StartInfo.Arguments = arguments;
            reportGenerator.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            reportGenerator.StartInfo.WorkingDirectory = Path.GetFullPath(@"..\framework");
            reportGenerator.Start();
            reportGenerator.WaitForExit();

            string htmlPath = Path.Combine(Path.GetDirectoryName(cachePath), outputFileName);
            if (System.IO.File.Exists(htmlPath))
            {
                if (webBrowser != null)
                {
                    webBrowser.Dispose();
                }

                // open report with a default program for html files
                webBrowser = new Process();
                webBrowser.StartInfo.FileName = htmlPath;
                webBrowser.Start();
            }
        }

        #endregion [ Generate Leader-Follower Test Report ]

        /// <summary>
        /// Initialization that is performed prior to sending a command to the framework.
        /// </summary>
        private void FrameworkInitialization()
        {
            if (logWindow == null || !logWindow.IsVisible)
            {
                logWindow = new Executor();
            }
            ////logWindow.frameworkOutput.Text = string.Empty;
            ////logWindow.traceLogOutput.Text = string.Empty;
            logWindow.Show();
            this.updateWindowTitle();
            // Send new settings file to framework if required
            UpdateSettings();
        }

        #region [ Main Window Commands ]

        /// <summary>
        /// Command for closing the main window.
        /// </summary>
        public ICommand MainWindowClosingCommand
        {
            get
            {
                if (_mainWindowClosing == null)
                {
                    _mainWindowClosing = new DelegateCommand(MainWindowClosingCommandExecuted, MainWindowClosingCommandCanExecute);
                }

                return _mainWindowClosing;
            }
        }

        /// <summary>
        /// Executes the closing command by stopping the framework and closing all child windows.
        /// </summary>
        public void MainWindowClosingCommandExecuted()
        {
            if (this.MarbleConnector != null)
                this.MarbleConnector.StopAndWaitToFinish();
            if (this.logWindow != null && this.logWindow.IsVisible)
                this.logWindow.Close();
            if (this.connectionWindow != null && this.connectionWindow.IsVisible)
                this.connectionWindow.Close();
            if (this.captureTool != null && this.captureTool.IsVisible)
                this.captureTool.Close();
            if (this.marbleWikiWindow != null && this.marbleWikiWindow.IsVisible)
                this.marbleWikiWindow.Close();
            if (this.blackBoxWindow != null && this.blackBoxWindow.IsVisible)
                this.blackBoxWindow.Close();

            TestReportView.CloseAllTestReportWindows();
        }

        /// <summary>
        /// Determines whether the closing command can be executed.
        /// </summary>
        /// <returns>Value of <c>true</c> if the command can be executed, otherwise <c>false</c> is returned.</returns>
        /// <remarks>We only allow the closing command to execute if there are no changes that need to be saved, or the user
        /// is prompted and chooses not to save the changes.</remarks>
        public bool MainWindowClosingCommandCanExecute()
        {
            // Display confirmation dialog if execution is ongoing
            if (this.TestSetModel.CurrentTestCase != null &&
                MessageBox.Show("Execution is ongoing do you really want to quit?",
                                "Confirm quit",
                                MessageBoxButton.YesNo) == MessageBoxResult.No)
                return false;

            bool canExecuteClosingCommand = this.ConfirmSaveOrContinueOperation();

            // Return whether the closing command can execute
            return canExecuteClosingCommand;
        }

        #region [ BLT-UE testing related Commands ]
        
        private bool isBltUeTestingEnabledForTestrun;

        /// <summary>
        /// Gets or sets a value indicating whether the BLT-UE testing is enabled for the testrun.
        /// </summary>
        public bool IsBltUeTestingEnabledForTestrun
        {
            get
            {
                return this.isBltUeTestingEnabledForTestrun;
            }
            set
            {
                this.isBltUeTestingEnabledForTestrun = value;
                this.OnPropertyChanged("IsBltUeTestingEnabledForTestrun");
            }
        }

        private DelegateCommand cmdBltUeGui;

        /// <summary>
        /// Method which returns bool value indicating whether the BLT-UE Settings Dialog can be opened.
        /// </summary>
        /// <returns>Bool value indicating whether the BLT-UE Settings Dialog can be opened.</returns>
        public bool CanInitBltUe()
        {
            if (_loadSettingsTask == null || !_loadSettingsTask.IsCompleted) return false;

            return this.MarbleConnector.State == ConnectorState.FrameworkReady || this.MarbleConnector.State == ConnectorState.Idle;
        }

        /// <summary>
        /// Gets command for opening BLT-UE Settings Dialog.
        /// </summary>
        public ICommand CmdInitBltUe
        {
            get
            {
                if (this.cmdBltUeGui == null)
                {
                    this.cmdBltUeGui = new DelegateCommand(new Action(this.InitBltUeCommandExecuted), new Func<bool>(this.CanInitBltUe));
                }

                return this.cmdBltUeGui;
            }
        }

        /// <summary>
        /// Shows BLT-UE Settings Dialog
        /// </summary>
        public void InitBltUeCommandExecuted()
        {
            // If Marble connector not started e.g. after Framework has been killed, restart is required.
            if (checkMarbleFwStateAndStartIfRequired())
            {
                try
                {
                    // Initialize settingshandler object. If settings file was not found, use hardcoded default settings.
                    BltUeClientSettings s = null;
                    const string filePath = @"..\settings\BltUeGuiClientSettings.xml";
                    if (File.Exists(filePath))
                    {
                        SettingsHandler settingsHandler = new SettingsHandler(new BltUeClientSettings(), filePath);
                        s = settingsHandler.SettingsObject as BltUeClientSettings;
                    }

                    if (s == null)
                    {
                        s = new BltUeClientSettings();
                    }

                    s.ServiceUri.ServicePort = this.settings.System.FrameworkGuiBltUeServicePort;
                    MarbleWcfClient<IBltUeService> client = new MarbleWcfClient<IBltUeService>(s, ServiceDefinitions.BltUeServiceEndpoint);
                    
                    if (!this.isBltUeTestingEnabledForTestrun)
                    {
                        client.DelegateExecutor(proxy => proxy.InitGpib());
                        client.DelegateExecutor(proxy => proxy.InitPsu());
                        this.IsBltUeTestingEnabledForTestrun = true;
                    }
                    else
                    {
                        client.DelegateExecutor(proxy => proxy.Disconnect());
                        this.IsBltUeTestingEnabledForTestrun = false;
                    }
                    client.Dispose();
                }
                catch (Exception ex)
                {
                    System.Windows.Forms.MessageBox.Show(ex.Message, "Setting up BLT-UE failed", MessageBoxButtons.OK,
                                                         MessageBoxIcon.Error);
                    this.IsBltUeTestingEnabledForTestrun = false;
                }
            }
        }

        #endregion [ BLT-UE testing related Commands ]

        /// <summary>
        /// Helper method for commands that needs Marble FW running in the background.
        /// Checks the connector state and starts the FW if required.
        /// </summary>
        /// <returns>True if FW is ready. False if starting FW timeouts.</returns>
        private bool checkMarbleFwStateAndStartIfRequired()
        {
            // If Marble connector not started e.g. after Framework has been killed, restart is required.
            if (this.MarbleConnector.State == ConnectorState.Idle)
            {
                ProgressDialogResult result = ProgressDialog.Execute("Marble Framework not running...", "Starting Marble Framework", (bw, we) =>
                {
                    // If framework does not become ready within 30 seconds --> timeout the operation.
                    const int timeout = 30;
                    MarbleConnector.AddToQueue(new InitMarbleServerCommand());
                    int i = 1;
                    while (App.ViewModel.MarbleConnector.State != ConnectorState.FrameworkReady)
                    {
                        Thread.Sleep(100);
                        i++;
                        if (i == timeout * 10)
                        {
                            throw new Exception("Marble Framework failed to start within " + timeout + " seconds.");
                        }
                    }
                }, ProgressDialogSettings.WithLabelOnly);

                if (result.OperationFailed)
                {
                    System.Windows.Forms.MessageBox.Show(result.Error.Message, "Starting Marble Framework failed!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    this.IsBltUeTestingEnabledForTestrun = false;
                    return false;
                }
            }
            return true;
        }

        #endregion [ Main Window Commands ]

        #region [ Core Test Tool Settings Commands ]

        private DelegateCommand openCoreTestToolSettings;

        public bool CanCoreTestToolSettingsWindowOpen()
        {
            // We can only open the CTT settings if there is at least one CTT test case that has a configuration file with at least one section
            return (TestSetModel.TestCases.FirstOrDefault(n => CoreTestToolUtilities.HasCoreTestToolConfigurationSectionNames(n)) != null);
        }

        /// <summary>
        /// Command for opening Core Test Tool settings.
        /// </summary>
        public ICommand OpenCoreTestToolSettings
        {
            get
            {
                if (openCoreTestToolSettings == null)
                {
                    openCoreTestToolSettings = new DelegateCommand(new Action(this.OpenCoreTestToolSettingsCommandExecuted), new Func<bool>(this.CanCoreTestToolSettingsWindowOpen));
                }

                return openCoreTestToolSettings;
            }
        }

        /// <summary>
        /// Shows the Core Test Tool settings dialog.
        /// </summary>
        public void OpenCoreTestToolSettingsCommandExecuted()
        {
            // Change mouse cursor to busy
            Mouse.OverrideCursor = System.Windows.Input.Cursors.Wait;

            Window settingsWindow = null;

            try
            {
                List<string> assemblyFilePaths = new List<string>();
                List<string> configurationFilePaths = new List<string>();
                List<string> sectionNames = new List<string>();

                foreach (TestCase testCase in TestSetModel.TestCases)
                {
                    // If this test case has configuration section names
                    if (CoreTestToolUtilities.HasCoreTestToolConfigurationSectionNames(testCase))
                    {
                        CoreTestToolConfiguration coreTestConfiguration = testCase.Script.Configuration as CoreTestToolConfiguration;

                        if (coreTestConfiguration != null)
                        {
                            // Get the assembly file path
                            string assemblyFilePath = Path.Combine(FileUtilities.ConvertRelativePathToAbsolutePath(testCase.Script.Directory), testCase.Script.file);

                            // Get the configuration file path
                            string configurationFilePath = Path.Combine(coreTestConfiguration.Directory, coreTestConfiguration.File);

                            // For each section name
                            foreach (string sectionName in ((CoreTestToolConfiguration)testCase.Script.Configuration).SectionNames)
                            {
                                // Assume we have already added this configuration section
                                bool alreadyAdded = false;

                                for (int i = 0; i < assemblyFilePaths.Count; i++)
                                {
                                    // If this section configuration matches one we have already added
                                    if (sectionName == sectionNames[i] &&
                                        assemblyFilePath == assemblyFilePaths[i] &&
                                        configurationFilePath == configurationFilePaths[i])
                                    {
                                        // This section configuration has already been added 
                                        alreadyAdded = true;
                                        break;
                                    }
                                }

                                // If the section configuration information has not already been added and the assembly file exists
                                if (!alreadyAdded &&
                                    File.Exists(assemblyFilePath))
                                {
                                    // Add the configuration section information for the assembly file
                                    assemblyFilePaths.Add(assemblyFilePath);
                                    configurationFilePaths.Add(configurationFilePath);
                                    sectionNames.Add(sectionName);
                                }
                            }
                        }
                    }
                }

                if (assemblyFilePaths.Count > 0)
                {
                    CoreTestToolSettingsModel model = CoreTestToolSettingsModel.Create(assemblyFilePaths.ToArray(), configurationFilePaths.ToArray(), sectionNames.ToArray());
                    CoreTestToolSettingsViewModel viewModel = new CoreTestToolSettingsViewModel(model);

                    settingsWindow = new Window();
                    settingsWindow.Title = "Marble - CTT Settings";
                    settingsWindow.Icon = new BitmapImage(new Uri("pack://application:,,,/MarbleLibrary;component/Images/Marble.M.Icon.ico", UriKind.RelativeOrAbsolute));
                    settingsWindow.Content = new CoreTestToolSettingsView(viewModel);
                    ((CoreTestToolSettingsView)settingsWindow.Content).ParentWindow = settingsWindow;
                    settingsWindow.Width = 740;
                    settingsWindow.Height = 520;
                    settingsWindow.MinWidth = 240;
                    settingsWindow.MinHeight = 220;
                }
            }

            finally
            {
                // Reset mouse cursor
                Mouse.OverrideCursor = null;
            }

            if (settingsWindow != null)
            {
                settingsWindow.ShowDialog();
            }
        }

        private DelegateCommand<CoreTestToolSettingsSection> updateCoreTestToolConfiguration;

        private bool isTestRunPaused;

        private bool isTestRunPauseRequested;

        private bool isTimedRunStartedForUi;

        private bool isShuffleModeEnabledForUi;

        /// <summary>
        /// Determines whether the command to update the Core Test Tool configuration can be executed.
        /// </summary>
        /// <param name="section">Core Test Tool configuration section information.</param>
        /// <returns>Value of <c>true</c> if the command can be executed, otherwise <c>false</c> is returned.</returns>
        public bool CanUpdateCoreTestToolConfiguration(CoreTestToolSettingsSection section)
        {
            return true;
        }

        /// <summary>
        /// Command for updating the Core Test Tool configuration.
        /// </summary>
        public ICommand UpdateCoreTestToolConfiguration
        {
            get
            {
                if (updateCoreTestToolConfiguration == null)
                {
                    updateCoreTestToolConfiguration = new DelegateCommand<CoreTestToolSettingsSection>(UpdateCoreTestToolConfigurationExecuted, CanUpdateCoreTestToolConfiguration);
                }

                return updateCoreTestToolConfiguration;
            }
        }

        /// <summary>
        /// Updates the configuration for a Core Test Tool assembly.
        /// </summary>
        /// <param name="section">Core Test Tool configuration section information.</param>
        public void UpdateCoreTestToolConfigurationExecuted(CoreTestToolSettingsSection section)
        {
            // Perform required initialization prior to sending a framework command
            FrameworkInitialization();

            // Send a command to the framework to update the CTT configuration
            UpdateCoreTestToolConfigurationCommand command = new UpdateCoreTestToolConfigurationCommand(section.AssemblyFilePath, section.SectionName, section.GetSectionXml());
            MarbleConnector.AddToQueue(command);
        }

        #endregion [ Core Test Tool Settings Commands ]

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion

        #region [ HW Assisted WhiteBox related methods ]

        /// <summary>
        /// Check whether IoWarrior based HW / Netduino based HW is used to controll the DUT
        /// </summary>
        public void CheckHWControllerTypeAndAvailability()
        {
            // IO-Warrior vendor & product IDs
            const string ioWarriorVid = "07C0";
            // IO-Warrior 40
            const string ioWarrior40Pid = "1500";
            // IO-Warrior 24
            const string ioWarrior24Pid = "1501";
            // IO-Warrior 56
            const string ioWarrior56Pid = "1503";

            bool netduinoUsbSerialDeviceDetected = false;
            bool ioWarriorDeviceDetected = false;
            ManagementClass mc = new ManagementClass("Win32_PnPEntity");
            ManagementObjectCollection moc = mc.GetInstances();
            foreach (var mo in moc)
            {
                try
                {
                    // Check for FTDI USB Serial Converter containing MARBLEHW configuration
                    string caption = mo["Caption"].ToString();
                    string deviceId = mo["DeviceID"].ToString();
                    if (caption.ToLower().Contains("usb serial port") &&
                        deviceId.Contains("FTDIBUS") && deviceId.Contains("MARBLEHW"))
                    {
                        netduinoUsbSerialDeviceDetected = true;
                    }

                    int vidIndex = deviceId.IndexOf("VID_");
                    string startingAtVid = deviceId.Substring(vidIndex + 4); // + 4 to remove "VID_"              
                    string vid = startingAtVid.Substring(0, 4); // vid is four characters long

                    // Check for IoWarrior Vendor ID
                    if (vid.ToUpper() == ioWarriorVid)
                    {
                        int pidIndex = deviceId.IndexOf("PID_");
                        string startingAtPid = deviceId.Substring(pidIndex + 4); // + 4 to remove "PID_"
                        string pid = startingAtPid.Substring(0, 4); // pid is four characters long
                        if (pid == ioWarrior40Pid || pid == ioWarrior24Pid || pid == ioWarrior56Pid)
                            ioWarriorDeviceDetected = true;
                    }
                }
                catch {/* No actions required */}
            }

            this.IsIoWarriorHWForBlackBoxAvailable = ioWarriorDeviceDetected;

            // Close all services and processes related to blackbox execution (if running) if no IoWarrior devices detected... E.g. if USB cable unplugged while BlackBox UI is visible
            if (!this.IsIoWarriorHWForBlackBoxAvailable)
            {                
                App.closeBlackBoxRelatedProcesses();
                // Also close BlackBox UI if visible
                if (this.blackBoxWindow != null && this.blackBoxWindow.IsVisible)
                {
                    if (this.blackBoxWindow.Dispatcher.CheckAccess())
                        this.blackBoxWindow.Close();
                    else
                        this.blackBoxWindow.Dispatcher.Invoke(new Action(this.blackBoxWindow.Close));
                }
            }

            bool netduinoHWDetected = false; 
            if (settings.System.HWConnectionType == "USB")
            {
                netduinoHWDetected = netduinoUsbSerialDeviceDetected;
            }
            else if (settings.System.HWConnectionType == "TCP" && !string.IsNullOrEmpty(settings.System.HWAssistedWhiteBoxServerAddress))
            {
                if (HWControllerClient.Instance.PingServer(settings.System.HWAssistedWhiteBoxServerAddress) == IPStatus.Success)
                {
                    netduinoHWDetected = true;
                }
            }

            settings.System.HWAssistedWhiteBoxEnabled = netduinoHWDetected;
        }

        public void StartVideoRecorderIfEnabled()
        {
            // Start videoRecorder if enabled in settings
            if (settings.TestRun.EnableVideoRecorder)
            {
                ThreadPool.QueueUserWorkItem(state =>
                {
                    try
                    {
                        string testUnit = string.Empty;
                        if (!this.isIoWarriorHwForBlackBoxAvailable)
                            testUnit = settings.System.TestUnitNumber.ToString();

                        MarbleFwVideoRecorderClient c = new MarbleFwVideoRecorderClient(string.Empty, testUnit);
                        string s = c.TestUnitNumber;
                        if (s != testUnit)
                            c.TestUnitNumber = testUnit;
                        c.Dispose();
                    }
                    catch (Exception) {/* Should not happen */}
                });
            }    
        }

        private void updateWindowTitle()
        {
            if (!this.isIoWarriorHwForBlackBoxAvailable)
            {
                string testUnit = string.Empty;
                if (settings.System.HWConnectionType == "USB" || (settings.System.HWConnectionType == "TCP" && !string.IsNullOrEmpty(settings.System.HWAssistedWhiteBoxServerAddress)))
                {
                    testUnit = settings.System.TestUnitNumber.ToString();
                }

                if (!string.IsNullOrEmpty(testUnit))
                {
                    if (!this.MarbleApplicationTitleText.Contains(" - Test Unit:"))
                    {
                        this.MarbleApplicationTitleText += " - Test Unit:" + testUnit;
                        if (this.logWindow != null)
                            this.logWindow.Title = "Test Unit:" + testUnit;
                    }
                    else
                    {
                        this.MarbleApplicationTitleText = this.MarbleApplicationTitleText.Substring(0, this.MarbleApplicationTitleText.IndexOf(" - Test Unit:"));
                        this.MarbleApplicationTitleText += " - Test Unit:" + testUnit;
                        if (this.logWindow != null)
                            this.logWindow.Title = "Test Unit:" + testUnit;
                    }
                }
            }
        }

        #endregion [ HW Assisted WhiteBox related methods ]

        #region [ Blackbox related Commands ]

        private DelegateCommand cmdBlackboxGui;

        /// <summary>
        /// Method which returns bool value indicating whether the BlackBox GUI can be started.
        /// </summary>
        /// <returns>Bool value indicating whether the BlackBox GUI can be opened.</returns>
        public bool CanInitBlackbox()
        {
            if (_loadSettingsTask == null || !_loadSettingsTask.IsCompleted)
                return false;

            return (this.blackBoxWindow == null || !this.blackBoxWindow.IsVisible);
        }

        /// <summary>
        /// Gets command for opening BlackBox GUI.
        /// </summary>
        public ICommand CmdInitBlackbox
        {
            get
            {
                if (this.cmdBlackboxGui == null)
                {
                    this.cmdBlackboxGui = new DelegateCommand(new Action(this.InitBlackboxCommandExecuted), new Func<bool>(this.CanInitBlackbox));
                }

                return this.cmdBlackboxGui;
            }
        }

        /// <summary>
        /// Shows BlackBox GUI
        /// </summary>
        public void InitBlackboxCommandExecuted()
        {
            this.blackBoxWindow = new Window();
            this.blackBoxWindow.Title = "Marble - BlackBox";
            this.blackBoxWindow.Icon =
                new BitmapImage(new Uri(
                                    "pack://application:,,,/MarbleLibrary;component/Images/Marble.M.Icon.ico",
                                    UriKind.RelativeOrAbsolute));
            this.blackBoxWindow.Content = new BlackBoxView();
            ((BlackBoxView)blackBoxWindow.Content).ParentWindow = blackBoxWindow;
            this.blackBoxWindow.Width = 700;
            this.blackBoxWindow.Height = double.NaN;
            this.blackBoxWindow.SizeToContent = SizeToContent.WidthAndHeight;
            this.blackBoxWindow.ResizeMode = ResizeMode.NoResize;
            // Set BlackBox video frame to null before showing the window. Otherwise the old already disposed Bitmap object may cause an exeption.
            //App.BlackBoxViewModel.VideoFrame = null;
            this.blackBoxWindow.Show();

            ProgressDialogResult result = ProgressDialog.Execute("Marble - BlackBox", "Connecting BlackBox services...", (bw, we) =>
            {
                Action action = () => App.BlackBoxViewModel.ServiceConnect();
                Task t = Task.Factory.StartNew(action);

                //Wait 60 seconds for connection to complete
                if (!t.Wait(60000))
                {
                    throw new InvalidOperationException("Marble was unable to establish connection to BlackBox services within 60 seconds");
                }

                App.BlackBoxViewModel.BlackBoxGuiEnabled = true;
                App.BlackBoxViewModel.UpdateData();
            }, ProgressDialogSettings.WithLabelOnly);
            if (result.OperationFailed)
            {
                MessageBox.Show(result.Error.Message, "Failed to connect to BlackBox Service!", MessageBoxButton.OK, MessageBoxImage.Error);
                this.blackBoxWindow.Close();
            }
        }

        public void UpdateBlackboxRelatedControls()
        {
            this.OnPropertyChanged("CanWhiteboxCheckBoxesBeEnabled");
            this.OnPropertyChanged("CanBlackboxCheckBoxesBeEnabled");
            this.OnPropertyChanged("IsWhiteboxCheckBoxesEnabled");
        }

        #endregion [ Blackbox related Commands ]

        #region IDispose

        /// <summary>
        /// Disposes of this object.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Protected method for disposing this object.
        /// </summary>
        /// <param name="disposing">Flag to indicate whether we are disposing or our
        /// destructor has been called.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    // Dispose of any managed objects

                    if (reportGenerator != null)
                    {
                        // Dispose of the report generator
                        reportGenerator.Dispose();
                    }

                    if (webBrowser != null)
                    {
                        // Dispose of the web browser
                        webBrowser.Dispose();
                    }

#if FRAMEWORK_SUPPORTS_MARBLE_SETTINGS_DIRECTORY
                    // Dispose of the settings manager
                    SettingsManager.Instance.Dispose();

                    if (_loadSettingsTask != null)
                    {
                        // Dispose of the task for loading settings
                        _loadSettingsTask.Dispose();
                    }
#endif
                }

                _disposed = true;
            }
        }

        #endregion IDispose    
    }
}
