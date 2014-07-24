using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Marble.Communication;

namespace Marble.Views
{
    using System.IO;
    using System.Threading.Tasks;
    using System.Windows.Forms;
    using System.Windows.Threading;

    using Marble.Model;
    using Marble.ViewModel;

    using MarbleLibrary.Commands;
    using MarbleLibrary.Utilities;

    using DataFormats = System.Windows.DataFormats;
    using DragDropEffects = System.Windows.DragDropEffects;
    using DragEventArgs = System.Windows.DragEventArgs;

    /// <summary>
    /// Interaction logic for FlasherView.xaml
    /// </summary>
    public partial class TestReportsTabView : UcBase
    {
        /// <summary>
        /// Minimum refresh interval for test results in test case summary.
        /// </summary>
        private readonly TimeSpan minRefreshInterval = new TimeSpan(0, 0, 0, 0, 5000);

        private DispatcherTimer refreshDispatcherTimer = null;

        /// <summary>
        /// Initializes a new instance of the <see cref="FlasherView"/> class.
        /// </summary>
        public TestReportsTabView()
        {
            this.InitializeComponent();

            this.InitializeTestReportTabView();

            MarbleMainViewModel.TestResultHandledEventHandler += MarbleMainViewModel_TestResultHandledEventHandler;
            MarbleMainViewModel.TestReportsTabInitializationNeededEventHandler += MarbleMainViewModel_TestReportsTabInitializationNeededEventHandler;
        }

        ~TestReportsTabView()
        {
            if (this.refreshDispatcherTimer != null)
            {
                this.refreshDispatcherTimer.Stop();
                this.refreshDispatcherTimer.Tick -= this.refreshDispatcherTimerOnTick;
            }
        }

        private void initializeRefreshTimer()
        {
            if (this.refreshDispatcherTimer != null)
            {
                this.refreshDispatcherTimer.Stop();
                this.refreshDispatcherTimer.Tick -= this.refreshDispatcherTimerOnTick;
            }

            this.refreshDispatcherTimer = new DispatcherTimer(DispatcherPriority.Normal);
            this.refreshDispatcherTimer.Interval = this.minRefreshInterval;
            this.refreshDispatcherTimer.Tick += this.refreshDispatcherTimerOnTick;
        }

        private void refreshDispatcherTimerOnTick(object sender, EventArgs eventArgs)
        {
            var dispatcherTimer = sender as DispatcherTimer;
            if (dispatcherTimer != null)
            {
                dispatcherTimer.Stop();
            }
            else
            {
                this.refreshDispatcherTimer.Stop();    
            }
            
            ////this.updateTestReportViewForTestReportsTab();
            this.updateTestResults();
        }

        private void updateTestResults()
        {
            lock (this.testCaseResultsToAddToSummary)
            {
                // Check whether there is test case results.
                if (this.borderErrorInfo.Visibility == Visibility.Visible
                    && App.ViewModel.TestSetModel.TestCases.Where(tc => tc.Level == 1)
                          .ToList()
                          .Any(firstLevelTestCase => !string.IsNullOrEmpty(firstLevelTestCase.Result.Result)))
                {
                    this.InitializeTestReportTabView();
                }
                else
                {
                    //if (this.testCaseResultsToAddToSummary.Count > 0)
                    //{
                    //    foreach (TestCase testCase in this.testCaseResultsToAddToSummary)
                    //    {
                    //        this.testCaseSummary.AddTestCaseToTestCaseList(testCase);
                    //    }
                    //}
                    //else
                    //{
                    //    this.testReportViewTestReportTab.UpdateTestReportViewForTestReportsTab();
                    //}

                    ////TestCase testCaseToAdd = sender as TestCase;

                    ////if (testCaseToAdd != null)
                    ////{
                    ////    this.testCaseSummary.AddTestCaseToTestCaseList(testCaseToAdd);
                    ////}
                    ////else
                    ////{
                    ////this.testReportViewTestReportTab.UpdateTestReportViewForTestReportsTab();
                    this.testReportViewTestReportTab.UpdateTestReportViewForTestReportsTab();
                    ////}


                }


                this.testCaseResultsToAddToSummary.Clear();
            }
        }

        private List<TestCase> testCaseResultsToAddToSummary = new List<TestCase>();

        ////public void UpdateTestReportViewForTestReportsTab()
        ////{
        ////    if (this.refreshDispatcherTimer == null)
        ////    {
        ////        this.initializeRefreshTimer();
        ////    }

        ////    if (this.refreshDispatcherTimer.IsEnabled)
        ////    {
        ////        // No actions needed, view will be updated when timer finishes.
        ////    }
        ////    else
        ////    {
        ////        this.refreshDispatcherTimer.Start();
        ////    }
        ////}

        private TestReportTestCaseSummaryView testCaseSummary
        {
            get
            {
                return this.testReportViewTestReportTab.scrollViewerTestCaseSummary.Content as TestReportTestCaseSummaryView;
            }
        }

        /// <summary>
        /// Initializes test report tab view.
        /// </summary>
        public void InitializeTestReportTabView()
        {
            if (App.ViewModel.TestSetModel.TestCases.Count(tc => tc.Level == 1) >= 1)
            {
                List<TestCase> allFirstLevelTestCases =
                    App.ViewModel.TestSetModel.TestCases.Where(tc => tc.Level == 1).ToList();

                // When there are no test case results.
                if (allFirstLevelTestCases.Any(firstLevelTestCase => !string.IsNullOrEmpty(firstLevelTestCase.Result.Result)))
                {
                    // Test report tab user control is shown and error message is hidden.
                    this.borderErrorInfo.Visibility = Visibility.Collapsed;
                    this.testReportViewTestReportTab.Visibility = Visibility.Visible;

                    TestResult testResult = allFirstLevelTestCases.Where(firstLevelTestCase => firstLevelTestCase.Result != null).Select(firstLevelTestCase => firstLevelTestCase.Result).FirstOrDefault();

                    this.testReportViewTestReportTab.ChangeTestReportAndInitializeView(testResult, true);
                    this.testReportViewTestReportTab.SetViewModeToHorizontal();

                    return;
                }
            }

            // Test report tab user control is hidden and error message is displayed.
            this.testReportViewTestReportTab.Visibility = Visibility.Collapsed;
            this.borderErrorInfo.Visibility = Visibility.Visible;
        }

        /// <summary>
        /// Updates error message visibility.
        /// </summary>
        public void UpdateErrorMessageVisibility()
        {
            if (App.ViewModel.TestSetModel.TestCases.Count(tc => tc.Level == 1) >= 1)
            {
                // Check whether there is test case results.
                if (App.ViewModel.TestSetModel.TestCases.Where(tc => tc.Level == 1).ToList().Any(firstLevelTestCase => !string.IsNullOrEmpty(firstLevelTestCase.Result.Result)))
                {
                    // Test report tab user control is shown and error message is hidden.
                    this.borderErrorInfo.Visibility = Visibility.Collapsed;
                    this.testReportViewTestReportTab.Visibility = Visibility.Visible;

                    return;
                }
            }

            // Test report tab user control is hidden and error message is displayed.
            this.testReportViewTestReportTab.Visibility = Visibility.Collapsed;
            this.borderErrorInfo.Visibility = Visibility.Visible;
        }

        /// <summary>
        /// Selects test report from test case summary by test case.
        /// </summary>
        /// <param name="testCaseToSelect"></param>
        public void SelectTestReportFromTestCaseSummary(TestCase testCaseToSelect)
        {
            if (this.testCaseSummary == null) return;

            this.testCaseSummary.SelectTestReport(testCaseToSelect);
        }

        /// <summary>
        /// Updates test report tab.
        /// </summary>
        /// <param name="sender">When sender is TestCase, it is added to summary. Otherwise summary is initialized.</param>
        /// <param name="e"></param>
        private void MarbleMainViewModel_TestResultHandledEventHandler(object sender, EventArgs e)
        {
            TestCase testCaseToAdd = sender as TestCase;

            if (testCaseToAdd != null)
            {
                lock (this.testCaseResultsToAddToSummary)
                {
                    this.testCaseResultsToAddToSummary.Add(testCaseToAdd);
                }
            }

            if (this.refreshDispatcherTimer == null)
            {
                this.initializeRefreshTimer();
            }

            if (this.refreshDispatcherTimer.IsEnabled)
            {
                // No actions needed, view will be updated when timer finishes.
            }
            else
            {
                this.refreshDispatcherTimer.Start();
                
            }

            ////// Check whether there is test case results.
            ////if (this.borderErrorInfo.Visibility == Visibility.Visible &&
            ////    App.ViewModel.TestSetModel.TestCases.Where(tc => tc.Level == 1).ToList().Any(firstLevelTestCase => !string.IsNullOrEmpty(firstLevelTestCase.Result.Result)))
            ////{
            ////    this.InitializeTestReportTabView();
            ////}
            ////else
            ////{
            ////    TestCase testCaseToAdd = sender as TestCase;

            ////    if (testCaseToAdd != null)
            ////    {
            ////        this.testCaseSummary.AddTestCaseToTestCaseList(testCaseToAdd);
            ////    }
            ////    else
            ////    {
            ////        ////this.testReportViewTestReportTab.UpdateTestReportViewForTestReportsTab();
                    
            ////    }
            ////}
        }

        void MarbleMainViewModel_TestReportsTabInitializationNeededEventHandler(object sender, EventArgs e)
        {
            this.InitializeTestReportTabView();
        }

        public void PrevFailedTestCase_Click(object sender, RoutedEventArgs e)
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonPreviousFailedTestRun);
        }

        public void NextFailedTestCase_Click(object sender, RoutedEventArgs e)
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonNextFailedTestRun);
        }

        public void PrevPassedTestCase_Click(object sender, RoutedEventArgs e)
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonPreviousPassedTestRun);
        }

        public void NextPassedTestCase_Click(object sender, RoutedEventArgs e)
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonNextPassedTestRun);
        }

        public void PrevFailedTestCaseByTime_Click(object sender, RoutedEventArgs e)
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonPreviousFailedByTime);
        }

        public void NextFailedTestCaseByTime_Click(object sender, RoutedEventArgs e)
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonNextFailedByTime);
        }

        #region [ Select Previous Failed Test Case ]

        private DelegateCommand selectPrevFailedTestCase;

        public bool CanSelectPrevFailedTestCase()
        {
            if (this.testCaseSummary == null) return false;

            return this.testCaseSummary.buttonPreviousFailedTestRun.IsEnabled;
        }

        /// <summary>
        /// Command for selecting previous failed test case.
        /// </summary>
        public ICommand SelectPrevFailedTestCaseCommand
        {
            get
            {
                if (selectPrevFailedTestCase == null)
                {
                    selectPrevFailedTestCase = new DelegateCommand(new Action(SelectPrevFailedTestCaseCommandExecuted), new Func<bool>(CanSelectPrevFailedTestCase));
                }

                return selectPrevFailedTestCase;
            }
        }

        /// <summary>
        /// Select previous failed test case.
        /// </summary>
        public void SelectPrevFailedTestCaseCommandExecuted()
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonPreviousFailedTestRun);
        }

        #endregion [ Select Previous Failed Test Case ]

        #region [ Select Next Failed Test Case ]

        private DelegateCommand selectNextFailedTestCase;

        public bool CanSelectNextFailedTestCase()
        {
            if (this.testCaseSummary == null) return false;

            return this.testCaseSummary.buttonNextFailedTestRun.IsEnabled;
        }

        /// <summary>
        /// Command for selecting next failed test case.
        /// </summary>
        public ICommand SelectNextFailedTestCaseCommand
        {
            get
            {
                if (selectNextFailedTestCase == null)
                {
                    selectNextFailedTestCase = new DelegateCommand(new Action(SelectNextFailedTestCaseCommandExecuted), new Func<bool>(CanSelectNextFailedTestCase));
                }

                return selectNextFailedTestCase;
            }
        }

        /// <summary>
        /// Select next failed test case.
        /// </summary>
        public void SelectNextFailedTestCaseCommandExecuted()
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonNextFailedTestRun);
        }

        #endregion [ Select Next Failed Test Case ]

        #region [ Select Previous Passed Test Case ]

        private DelegateCommand selectPrevPassedTestCase;

        public bool CanSelectPrevPassedTestCase()
        {
            if (this.testCaseSummary == null) return false;

            return this.testCaseSummary.buttonPreviousPassedTestRun.IsEnabled;
        }

        /// <summary>
        /// Command for selecting previous passed test case.
        /// </summary>
        public ICommand SelectPrevPassedTestCaseCommand
        {
            get
            {
                if (selectPrevPassedTestCase == null)
                {
                    selectPrevPassedTestCase = new DelegateCommand(new Action(SelectPrevPassedTestCaseCommandExecuted), new Func<bool>(CanSelectPrevPassedTestCase));
                }

                return selectPrevPassedTestCase;
            }
        }

        /// <summary>
        /// Select previous passed test case.
        /// </summary>
        public void SelectPrevPassedTestCaseCommandExecuted()
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonPreviousPassedTestRun);
        }

        #endregion [ Select Previous Passed Test Case ]

        #region [ Select Next Passed Test Case ]

        private DelegateCommand selectNextPassedTestCase;

        public bool CanSelectNextPassedTestCase()
        {
            if (this.testCaseSummary == null) return false;

            return this.testCaseSummary.buttonNextPassedTestRun.IsEnabled;
        }

        /// <summary>
        /// Command for selecting next passed test case.
        /// </summary>
        public ICommand SelectNextPassedTestCaseCommand
        {
            get
            {
                if (selectNextPassedTestCase == null)
                {
                    selectNextPassedTestCase = new DelegateCommand(new Action(SelectNextPassedTestCaseCommandExecuted), new Func<bool>(CanSelectNextPassedTestCase));
                }

                return selectNextPassedTestCase;
            }
        }

        /// <summary>
        /// Select next passed test case.
        /// </summary>
        public void SelectNextPassedTestCaseCommandExecuted()
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonNextPassedTestRun);
        }

        #endregion [ Select Next Passed Test Case ]

        #region [ Select Previous Failed ByTime]

        private DelegateCommand selectPrevFailedByTime;

        public bool CanSelectPrevFailedByTime()
        {
            if (this.testCaseSummary == null) return false;

            return this.testCaseSummary.buttonPreviousFailedByTime.IsEnabled;
        }

        /// <summary>
        /// Command for selecting previous failed test case by time.
        /// </summary>
        public ICommand SelectPrevFailedByTimeCommand
        {
            get
            {
                if (selectPrevFailedByTime == null)
                {
                    selectPrevFailedByTime = new DelegateCommand(new Action(SelectPrevFailedByTimeCommandExecuted), new Func<bool>(CanSelectPrevFailedByTime));
                }

                return selectPrevFailedByTime;
            }
        }

        /// <summary>
        /// Select previous failed test case by time.
        /// </summary>
        public void SelectPrevFailedByTimeCommandExecuted()
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonPreviousFailedByTime);
        }

        #endregion [ Select Previous Failed By Time ]

        #region [ Select Next Failed By Time ]

        private DelegateCommand selectNextFailedByTime;

        public bool CanSelectNextFailedByTime()
        {
            if (this.testCaseSummary == null) return false;

            return this.testCaseSummary.buttonNextFailedByTime.IsEnabled;
        }

        /// <summary>
        /// Command for selecting next failed test case by time.
        /// </summary>
        public ICommand SelectNextFailedByTimeCommand
        {
            get
            {
                if (selectNextFailedByTime == null)
                {
                    selectNextFailedByTime = new DelegateCommand(new Action(SelectNextFailedByTimeCommandExecuted), new Func<bool>(CanSelectNextFailedByTime));
                }

                return selectNextFailedByTime;
            }
        }

        /// <summary>
        /// Select next failed test case by time.
        /// </summary>
        public void SelectNextFailedByTimeCommandExecuted()
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonNextFailedByTime);
        }

        #endregion [ Select Next Failed By Time ]

        #region [ Group By Result ]

        private DelegateCommand groupByResult;

        public bool CanGroupByResult()
        {
            if (this.testCaseSummary == null) return false;

            return this.testCaseSummary.buttonGroupByResult.IsEnabled;
        }

        /// <summary>
        /// Command for grouping by test case result.
        /// </summary>
        public ICommand GroupByResultCommand
        {
            get
            {
                if (groupByResult == null)
                {
                    groupByResult = new DelegateCommand(new Action(GroupByResultCommandExecuted), new Func<bool>(CanGroupByResult));
                }

                return groupByResult;
            }
        }

        /// <summary>
        /// Group by test case result.
        /// </summary>
        public void GroupByResultCommandExecuted()
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonGroupByResult);
        }

        #endregion [ Group By Result ]

        #region [ Group By Test Case Name ]

        private DelegateCommand groupByTestCaseName;

        public bool CanGroupByTestCaseName()
        {
            if (this.testCaseSummary == null) return false;

            return this.testCaseSummary.buttonGroupByTestCaseName.IsEnabled;
        }

        /// <summary>
        /// Command for grouping by test case name.
        /// </summary>
        public ICommand GroupByTestCaseNameCommand
        {
            get
            {
                if (groupByTestCaseName == null)
                {
                    groupByTestCaseName = new DelegateCommand(new Action(GroupByTestCaseNameCommandExecuted), new Func<bool>(CanGroupByTestCaseName));
                }

                return groupByTestCaseName;
            }
        }

        /// <summary>
        /// Group by test case name.
        /// </summary>
        public void GroupByTestCaseNameCommandExecuted()
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonGroupByTestCaseName);
        }

        #endregion [ Group By Test Case Name ]

        #region [ Group By Run Index ]

        private DelegateCommand groupByRunIndex;

        public bool CanGroupByRunIndex()
        {
            if (this.testCaseSummary == null) return false;

            return this.testCaseSummary.buttonGroupByRunIndex.IsEnabled;
        }

        /// <summary>
        /// Command for grouping by run index.
        /// </summary>
        public ICommand GroupByRunIndexCommand
        {
            get
            {
                if (groupByRunIndex == null)
                {
                    groupByRunIndex = new DelegateCommand(new Action(GroupByRunIndexCommandExecuted), new Func<bool>(CanGroupByTestCaseName));
                }

                return groupByRunIndex;
            }
        }

        /// <summary>
        /// Group by run index.
        /// </summary>
        public void GroupByRunIndexCommandExecuted()
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonGroupByRunIndex);
        }

        #endregion [ Group By Run Index ]

        #region [ Apply No Grouping ]

        private DelegateCommand applyNoGrouping;

        public bool CanApplyNoGrouping()
        {
            if (this.testCaseSummary == null) return false;

            return this.testCaseSummary.buttonNoGrouping.IsEnabled;
        }

        /// <summary>
        /// Command for applying no grouping.
        /// </summary>
        public ICommand ApplyNoGroupingCommand
        {
            get
            {
                if (applyNoGrouping == null)
                {
                    applyNoGrouping = new DelegateCommand(new Action(ApplyNoGroupingCommandExecuted), new Func<bool>(CanApplyNoGrouping));
                }

                return applyNoGrouping;
            }
        }

        /// <summary>
        /// Apply no grouping.
        /// </summary>
        public void ApplyNoGroupingCommandExecuted()
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonNoGrouping);
        }

        #endregion [ Apply No Grouping ]

        #region [ Copy Test Case Information To Clipboard ]

        private DelegateCommand copyToClipboard;

        public bool CanCopyToClipboard()
        {
            if (this.testCaseSummary == null) return false;

            return this.testCaseSummary.buttonCopyToClipboard.IsEnabled;
        }

        /// <summary>
        /// Command for copying test case information to clipboard.
        /// </summary>
        public ICommand CopyToClipboardCommand
        {
            get
            {
                if (copyToClipboard == null)
                {
                    copyToClipboard = new DelegateCommand(new Action(CopyToClipboardCommandExecuted), new Func<bool>(CanCopyToClipboard));
                }

                return copyToClipboard;
            }
        }

        /// <summary>
        /// Copy test case information to clipboard.
        /// </summary>
        public void CopyToClipboardCommandExecuted()
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonCopyToClipboard);
        }

        #endregion [ Copy Test Case Information To Clipboard ]

        #region [ Open Selected Test Report In New Window ]

        private DelegateCommand openSelectedTestReportInNewWindow;

        public bool CanOpenSelectedTestReportInNewWindow()
        {
            if (this.testCaseSummary == null) return false;

            return this.testCaseSummary.buttonOpenSelectedTestReportInNewWindow.IsEnabled;
        }

        /// <summary>
        /// Command for opening selected test report in new window.
        /// </summary>
        public ICommand OpenSelectedTestReportInNewWindowCommand
        {
            get
            {
                if (openSelectedTestReportInNewWindow == null)
                {
                    openSelectedTestReportInNewWindow = new DelegateCommand(new Action(OpenSelectedTestReportInNewWindowCommandExecuted), new Func<bool>(CanOpenSelectedTestReportInNewWindow));
                }

                return openSelectedTestReportInNewWindow;
            }
        }

        /// <summary>
        /// Open selected test report in new window.
        /// </summary>
        public void OpenSelectedTestReportInNewWindowCommandExecuted()
        {
            if (this.testCaseSummary != null) GuiUtilities.PerformClick(this.testCaseSummary.buttonOpenSelectedTestReportInNewWindow);
        }

        #endregion [ Open Selected Test Report In New Window ]
    }
}
