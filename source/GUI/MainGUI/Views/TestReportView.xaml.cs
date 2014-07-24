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

namespace Marble.Views
{
    using System.ComponentModel;
    using System.IO;
    using System.Windows.Threading;
    using System.Xml.Linq;

    using Marble.Model;
    using Marble.Templates;
    using Marble.Utilities;
    using Marble.ViewModel;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// Interaction logic for TestReportView.xaml
    /// </summary>
    public partial class TestReportView : UcBase, INotifyPropertyChanged
    {
        /////// <summary>
        /////// Minimum refresh interval for test results in test case summary.
        /////// </summary>
        ////private readonly TimeSpan minRefreshInterval = new TimeSpan(0, 0, 0, 0, 5000);

        ////private DispatcherTimer resfreshDispatcherTimer = null;

        private static List<TestReportView> windowedTestReportViews;

        public static List<TestReportView> WindowedTestReportViews
        {
            get
            {
                return windowedTestReportViews ?? (windowedTestReportViews = new List<TestReportView>());
            }
            set
            {
                windowedTestReportViews = value;
            }
        }

        public static void CloseAllTestReportWindows()
        {
            for (int index = WindowedTestReportViews.Count - 1; index >= 0; index--)
            {
                TestReportView windowedTestReportView = WindowedTestReportViews[index];

                if (windowedTestReportView != null && windowedTestReportView.IsVisible)
                {
                    windowedTestReportView.ParentWindow.Close();
                }
            }
        }

        private double contentMaxWidth;

        public double ContentMaxWidth
        {
            get
            {
                return this.contentMaxWidth;
            }
            set
            {
                this.contentMaxWidth = value;
                this.OnPropertyChanged("ContentMaxWidth");
            }
        }

        private bool isViewModeHorizontal;

        public bool IsViewModeHorizontal
        {
            get
            {
                return this.isViewModeHorizontal;
            }
            set
            {
                this.isViewModeHorizontal = value;
                this.OnPropertyChanged("IsViewModeHorizontal");
            }
        }

        public TestReportView()
        {
            this.InitializeComponent();

            this.DataContext = new TestReportViewModel();
            this.initializeTestReportView();

            this.ShowOrHideTestReport();
            this.Unloaded += new RoutedEventHandler(this.TestReportView_Unloaded);

            this.UcTestReportView_SizeChanged(null, null);
        }

        public TestReportView(TestResult testResult, bool isWindowModeEnabled = false, bool isBottomControlBarVisible = false)
        {
            this.InitializeComponent();

            this.DataContext = new TestReportViewModel(testResult);
            this.initializeTestReportView(isWindowModeEnabled, isBottomControlBarVisible);

            this.ShowOrHideTestReport();
            this.UcTestReportView_SizeChanged(null, null);
        }

        public TestReportView(string filePath, bool isWindowModeEnabled = false, bool isBottomControlBarVisible = false)
        {
            this.InitializeComponent();

            this.DataContext = new TestReportViewModel(filePath);
            this.initializeTestReportView(isWindowModeEnabled, isBottomControlBarVisible, true);

            if (this.viewModel.TestReport == null && this.IsWindowModeEnabled)
                this.Loaded += delegate { this.CloseCommandHandler(this, null); };

            this.ShowOrHideTestReport();
            this.UcTestReportView_SizeChanged(null, null);
        }

        ~TestReportView()
        {
            if (TestReportView.WindowedTestReportViews.Contains(this))
            {
                TestReportView.WindowedTestReportViews.Remove(this);
            }
        }

        private void TestReportView_Unloaded(object sender, RoutedEventArgs e)
        {
            ////if (this.resfreshDispatcherTimer != null)
            ////{
            ////    this.resfreshDispatcherTimer.Stop();
            ////    this.resfreshDispatcherTimer.Tick -= this.resfreshDispatcherTimerOnTick;
            ////}

            this.Unloaded -= this.TestReportView_Unloaded;
            this.DisposeAllGraphViews();
        }

        ////private void initializeRefreshTimer()
        ////{
        ////    if (this.resfreshDispatcherTimer != null)
        ////    {
        ////        this.resfreshDispatcherTimer.Stop();
        ////        this.resfreshDispatcherTimer.Tick -= this.resfreshDispatcherTimerOnTick;
        ////    }

        ////    this.resfreshDispatcherTimer = new DispatcherTimer(DispatcherPriority.Normal);
        ////    this.resfreshDispatcherTimer.Interval = this.minRefreshInterval;
        ////    this.resfreshDispatcherTimer.Tick += resfreshDispatcherTimerOnTick;
        ////}

        ////private void resfreshDispatcherTimerOnTick(object sender, EventArgs eventArgs)
        ////{
        ////    this.resfreshDispatcherTimer.Stop();
        ////    this.updateTestReportViewForTestReportsTab();
        ////}

        ////public void UpdateTestReportViewForTestReportsTab()
        ////{
        ////    if (this.resfreshDispatcherTimer == null)
        ////    {
        ////        this.initializeRefreshTimer();
        ////    }

        ////    if (this.resfreshDispatcherTimer.IsEnabled)
        ////    {
        ////        // No actions needed, view will be updated when timer finishes.
        ////    }
        ////    else
        ////    {
        ////        this.resfreshDispatcherTimer.Start();
        ////    }
        ////}

        public void SetViewModeToHorizontal()
        {
            this.IsViewModeHorizontal = true;

            // Horizontal view mode.
            this.groupBoxTestCaseSummary.SetValue(Grid.RowProperty, 0);
            this.groupBoxTestCaseSummary.SetValue(Grid.RowSpanProperty, 3);
            this.groupBoxTestCaseSummary.SetValue(Grid.ColumnProperty, 0);
            this.groupBoxTestCaseSummary.SetValue(Grid.ColumnSpanProperty, 1);

            this.advancedGridSplitterTestCaseSummary.SetValue(Grid.RowProperty, 0);
            this.advancedGridSplitterTestCaseSummary.SetValue(Grid.RowSpanProperty, 3);
            this.advancedGridSplitterTestCaseSummary.SetValue(Grid.ColumnProperty, 1);
            this.advancedGridSplitterTestCaseSummary.SetValue(Grid.ColumnSpanProperty, 1);
            this.advancedGridSplitterTestCaseSummary.ResizeDirection = GridResizeDirection.Columns;
            this.advancedGridSplitterTestCaseSummary.Width = 8;
            this.advancedGridSplitterTestCaseSummary.Height = Double.NaN;

            this.borderRightSideErrorInfo.SetValue(Grid.RowProperty, 0);
            this.borderRightSideErrorInfo.SetValue(Grid.RowSpanProperty, 3);
            this.borderRightSideErrorInfo.SetValue(Grid.ColumnProperty, 2);
            this.borderRightSideErrorInfo.SetValue(Grid.ColumnSpanProperty, 1);

            this.groupBoxTestReport.SetValue(Grid.RowProperty, 0);
            this.groupBoxTestReport.SetValue(Grid.RowSpanProperty, 3);
            this.groupBoxTestReport.SetValue(Grid.ColumnProperty, 2);
            this.groupBoxTestReport.SetValue(Grid.ColumnSpanProperty, 1);
        }

        public void SetViewModeToVertical()
        {
            this.IsViewModeHorizontal = false;

            // Vertical view mode.
            this.groupBoxTestCaseSummary.SetValue(Grid.RowProperty, 0);
            this.groupBoxTestCaseSummary.SetValue(Grid.RowSpanProperty, 1);
            this.groupBoxTestCaseSummary.SetValue(Grid.ColumnProperty, 0);
            this.groupBoxTestCaseSummary.SetValue(Grid.ColumnSpanProperty, 99);

            this.advancedGridSplitterTestCaseSummary.SetValue(Grid.RowProperty, 1);
            this.advancedGridSplitterTestCaseSummary.SetValue(Grid.RowSpanProperty, 1);
            this.advancedGridSplitterTestCaseSummary.SetValue(Grid.ColumnProperty, 0);
            this.advancedGridSplitterTestCaseSummary.SetValue(Grid.ColumnSpanProperty, 99);
            this.advancedGridSplitterTestCaseSummary.ResizeDirection = GridResizeDirection.Rows;
            this.advancedGridSplitterTestCaseSummary.Height = 8;
            this.advancedGridSplitterTestCaseSummary.Width = Double.NaN;

            this.borderRightSideErrorInfo.SetValue(Grid.RowProperty, 2);
            this.borderRightSideErrorInfo.SetValue(Grid.RowSpanProperty, 1);
            this.borderRightSideErrorInfo.SetValue(Grid.ColumnProperty, 0);
            this.borderRightSideErrorInfo.SetValue(Grid.ColumnSpanProperty, 99);

            this.groupBoxTestReport.SetValue(Grid.RowProperty, 2);
            this.groupBoxTestReport.SetValue(Grid.RowSpanProperty, 1);
            this.groupBoxTestReport.SetValue(Grid.ColumnProperty, 0);
            this.groupBoxTestReport.SetValue(Grid.ColumnSpanProperty, 99);
        }

        public void RefreshViewMode()
        {
            if (this.IsViewModeHorizontal)
                this.SetViewModeToHorizontal();
            else
                this.SetViewModeToVertical();
        }

        public void ChangeTestReport(TestResult testResult)
        {
            this.viewModel.ChangeTestReport(testResult);
            this.ShowOrHideTestReport();
            this.DisposeAllGraphViews();

            this.UcTestReportView_SizeChanged(null, null);
        }

        public void ChangeTestReport(string testResultFilePath)
        {
            this.viewModel.ChangeTestReport(testResultFilePath);
            this.initializeTestReportView(isWindowModeEnabled, isBottomControlBarVisible, true);

            if (this.viewModel.TestReport == null && this.IsWindowModeEnabled)
                this.Loaded += delegate { this.CloseCommandHandler(this, null); };

            this.ShowOrHideTestReport();
        }

        /// <summary>
        /// Changes test report and initializes the view.
        /// </summary>
        /// <param name="testResult"></param>
        /// <param name="showAllAvailableTestCases">True when all available test cases need to be displayed.</param>
        public void ChangeTestReportAndInitializeView(TestResult testResult, bool showAllAvailableTestCases = false)
        {
            this.ChangeTestReport(testResult);

            if (showAllAvailableTestCases)
                this.initializeTestReportViewToShowAllTestCases();
            else
                this.initializeTestReportView(isWindowModeEnabled, isBottomControlBarVisible);
        }

        /// <summary>
        /// Test report view is updated when new results are added.
        /// </summary>
        public void UpdateTestReportViewForTestReportsTab()
        {
            //this.initializeTestReportViewToShowAllTestCases();

            this.storeViewSizePreferences();

            List<TestCase> allFirstLevelTestCases = App.ViewModel.TestSetModel.TestCases.Where(tc => tc.Level == 1).ToList();

            TestReportTestCaseSummaryView testCaseSummary = this.scrollViewerTestCaseSummary.Content as TestReportTestCaseSummaryView;

            if (testCaseSummary != null)
                testCaseSummary.UpdateTestCaseList(allFirstLevelTestCases);

            TestReportTestCaseSummaryView multipleTestCaseSummary = this.scrollViewerMultipleTestCaseSummary.Content as TestReportTestCaseSummaryView;

            if (multipleTestCaseSummary != null)
                multipleTestCaseSummary.UpdateTestCaseList(allFirstLevelTestCases);
            
            this.RefreshViewMode();
        }

        public void ExpandAllGroupBoxes()
        {
            for (int i = 0; i < this.itemsControlTestCaseReportItems.Items.Count; i++)
            {
                ContentPresenter childItem = itemsControlTestCaseReportItems.ItemContainerGenerator.ContainerFromIndex(i) as ContentPresenter;

                if (childItem == null) continue;

                // All expandable containers are expanded for the screenshot.
                GroupBox groupBox = GuiUtilities.FindVisualChild<GroupBox>(childItem);

                if (groupBox != null) 
                    groupBox.Tag = "IsExpandedOnStart";
            }
        }

        public void DisposeAllGraphViews()
        {
            for (int i = 0; i < this.itemsControlTestCaseReportItems.Items.Count; i++)
            {
                ContentPresenter childItem = itemsControlTestCaseReportItems.ItemContainerGenerator.ContainerFromIndex(i) as ContentPresenter;

                if (childItem == null) continue;

                // All expandable containers are expanded for the screenshot.
                GraphView graphView = GuiUtilities.FindVisualChild<GraphView>(childItem);

                if (graphView != null)
                    graphView.chartGraph.Dispose();
            }

            GC.Collect();
        }

        public void ShowOrHideTestReport()
        {
            if (!this.IsLoaded) return;
            if (this.viewModel == null) return;

            if (this.viewModel.TestReport == null)
                this.ShowFileNotFoundPanel(this.viewModel.TestResult.ResultPath);
            else if (File.Exists(this.viewModel.TestReport.TestResultXmlFilePath))
                this.HideFileNotFoundPanel();
            else
                this.ShowFileNotFoundPanel();
        }

        public void ShowFileNotFoundPanel(string fileNotFoundPath = "")
        {
            this.textBlockRightSideInfoHeader.Text = "File Not Found";

            string fixedFileNotFoundPath = fileNotFoundPath;

            if (!Path.IsPathRooted(fixedFileNotFoundPath) && !string.IsNullOrEmpty(fixedFileNotFoundPath))
            {
                fixedFileNotFoundPath = Path.GetFullPath(fixedFileNotFoundPath);
            }

            if (this.viewModel.TestReport == null || string.IsNullOrEmpty(this.viewModel.TestReport.TestResultXmlFilePath))
                this.textBlockRightSideInfoText.Text = "File '" + fixedFileNotFoundPath + "' was not found.";
            else if (string.IsNullOrEmpty(fileNotFoundPath))
                this.textBlockRightSideInfoText.Text = "File '" + this.viewModel.TestReport.TestResultXmlFilePath + "' was not found.";
            else
                this.textBlockRightSideInfoText.Text = "File '" + fixedFileNotFoundPath + "' was not found.";

            this.borderRightSideErrorInfo.ToolTip = new TextBlock()
            {
                Text = this.textBlockRightSideInfoHeader.Text + "\n\n" + this.textBlockRightSideInfoText.Text,
                TextWrapping = TextWrapping.Wrap
            };

            this.borderRightSideErrorInfo.Visibility = Visibility.Visible;
            this.groupBoxTestReport.Visibility = Visibility.Collapsed;
        }

        public void HideFileNotFoundPanel()
        {
            this.borderRightSideErrorInfo.Visibility = Visibility.Collapsed;
            this.groupBoxTestReport.Visibility = Visibility.Visible;
        }

        private void initializeTestReportViewToShowAllTestCases()
        {
            if (TestReportView.WindowedTestReportViews == null)
                TestReportView.WindowedTestReportViews = new List<TestReportView>();

            if (isWindowModeEnabled)
                TestReportView.WindowedTestReportViews.Add(this);

            this.storeViewSizePreferences();

            this.IsWindowModeEnabled = false;
            this.IsBottomControlBarVisible = false;
            this.ContentMaxWidth = 800;

            if (App.ViewModel.TestSetModel.TestCases.Count(tc => tc.Level == 1) >= 1)
            {
                List<TestCase> allFirstLevelTestCases = App.ViewModel.TestSetModel.TestCases.Where(tc => tc.Level == 1).ToList();

                // When there are no test case results.
                if (allFirstLevelTestCases.All(firstLevelTestCase => string.IsNullOrEmpty(firstLevelTestCase.Result.Result)))
                {
                    this.hideTestCaseSummaryView();
                    
                    return;
                }

                TestReportTestCaseSummaryView testCaseSummaryView = new TestReportTestCaseSummaryView(allFirstLevelTestCases, SummaryMode.AllTestRuns)
                {
                    Width = double.NaN,
                    Height = double.NaN,
                    TestCaseSummaryViewUserPreferences = this.GetCurrentTestCaseSummaryViewUserPreferences(),
                    ViewModel = this.viewModel
                };
                
                this.setBindingsForTestCaseSummaryCheckboxes(testCaseSummaryView);

                // Test cases are sorted descending by time.
                testCaseSummaryView.SortTestRuns(testCaseSummaryView.dataGridTemplateColumnRuntime, ListSortDirection.Descending);

                this.scrollViewerTestCaseSummary.Content = testCaseSummaryView;

                testCaseSummaryView.SelectedTestCaseChanged += this.testCaseSummaryView_SelectedTestCaseChanged;

                // Latest test result is selected first by default.
                testCaseSummaryView.dataGridTestCases.SelectedIndex = 0;

                this.showTestCaseSummaryView();
            }
            else
            {
                this.hideTestCaseSummaryView();
            }

            this.UcTestReportView_SizeChanged(null, null);
        }
        
        private void initializeTestReportView(bool isWindowModeEnabled = false, bool isBottomControlBarVisible = false, bool exportedFileOpened = false)
        {
            if (TestReportView.WindowedTestReportViews == null)
                TestReportView.WindowedTestReportViews = new List<TestReportView>();

            if (isWindowModeEnabled)
                TestReportView.WindowedTestReportViews.Add(this);

            this.storeViewSizePreferences();

            this.IsWindowModeEnabled = isWindowModeEnabled;
            this.IsBottomControlBarVisible = isBottomControlBarVisible;
            this.ContentMaxWidth = 800;

            if (exportedFileOpened)
            {
                this.hideTestCaseSummaryView();
                return;
            }

            if (App.ViewModel.SelectedTestCase == null) return;

            if (App.ViewModel.SelectedFirstLevelTestCases.Count() > 1)
            {
                List<TestCase> testCases = new List<TestCase>();

                foreach (TestCase testCase in App.ViewModel.SelectedFirstLevelTestCases.ToList())
                {
                    testCases.AddRange(testCase.Children);
                }

                //TestReportTestCaseSummaryView testCaseSummaryView = new TestReportTestCaseSummaryView(App.ViewModel.SelectedFirstLevelTestCases.ToList(), SummaryMode.SingleTestCase) { Width = double.NaN, Height = double.NaN };
                TestReportTestCaseSummaryView testCaseSummaryView = new TestReportTestCaseSummaryView(App.ViewModel.SelectedFirstLevelTestCases.ToList(), SummaryMode.AllTestRuns)
                    {
                        Width = double.NaN,
                        Height = double.NaN,
                        TestCaseSummaryViewUserPreferences = this.GetCurrentTestCaseSummaryViewUserPreferences(),
                        ViewModel = this.viewModel
                    };
                //TestReportTestCaseSummaryView testCaseSummaryView = new TestReportTestCaseSummaryView(testCases, SummaryMode.AllTestRuns) { Width = double.NaN, Height = double.NaN };
                this.setBindingsForTestCaseSummaryCheckboxes(testCaseSummaryView);
                this.scrollViewerTestCaseSummary.Content = testCaseSummaryView;

                TestReportTestCaseSummaryView multipleTestCaseSummaryView = new TestReportTestCaseSummaryView(App.ViewModel.SelectedFirstLevelTestCases.ToList(), SummaryMode.MultipleTestCases)
                    {
                        Width = double.NaN,
                        Height = double.NaN
                    };
                this.scrollViewerMultipleTestCaseSummary.Content = multipleTestCaseSummaryView;

                testCaseSummaryView.SelectedTestCaseChanged += this.testCaseSummaryView_SelectedTestCaseChanged;

                this.showTestCaseSummaryView();
            }
            else if (App.ViewModel.SelectedTestCase.TotalTestCaseCount > 1)
            {
                TestReportTestCaseSummaryView testCaseSummaryView = new TestReportTestCaseSummaryView(App.ViewModel.SelectedTestCase)
                    {
                        Width = double.NaN,
                        Height = double.NaN,
                        TestCaseSummaryViewUserPreferences = this.GetCurrentTestCaseSummaryViewUserPreferences(),
                        ViewModel = this.viewModel
                    };
                this.setBindingsForTestCaseSummaryCheckboxes(testCaseSummaryView);
                this.scrollViewerTestCaseSummary.Content = testCaseSummaryView;
                testCaseSummaryView.SelectedTestCaseChanged += this.testCaseSummaryView_SelectedTestCaseChanged;

                this.showTestCaseSummaryView();
            }
            else
            {
                this.hideTestCaseSummaryView();
            }

            this.UcTestReportView_SizeChanged(null, null);
        }

        private void setBindingsForTestCaseSummaryCheckboxes(TestReportTestCaseSummaryView testCaseSummaryView)
        {
            if (testCaseSummaryView == null) return;

            testCaseSummaryView.checkBoxShowPassedTestRuns.SetBinding(
                    CheckBox.IsCheckedProperty,
                    new Binding("IsPassedResultsDisplayed") { Mode = BindingMode.TwoWay, UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged, Source = this.viewModel.TestReportViewUserPreferences.DefaultTestCaseSummaryPreferences });
            testCaseSummaryView.checkBoxShowFailedTestRuns.SetBinding(
                    CheckBox.IsCheckedProperty,
                    new Binding("IsFailedResultsDisplayed") { Mode = BindingMode.TwoWay, UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged, Source = this.viewModel.TestReportViewUserPreferences.DefaultTestCaseSummaryPreferences });
            ////testCaseSummaryView.checkBoxShowErrorTestRuns.SetBinding(
            ////        CheckBox.IsCheckedProperty,
            ////        new Binding("IsErrorResultsDisplayed") { Mode = BindingMode.TwoWay, UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged, Source = this.viewModel.TestReportViewUserPreferences.DefaultTestCaseSummaryPreferences });
            testCaseSummaryView.checkBoxShowNoResultTestRuns.SetBinding(
                    CheckBox.IsCheckedProperty,
                    new Binding("IsNoResultResultsDisplayed") { Mode = BindingMode.TwoWay, UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged, Source = this.viewModel.TestReportViewUserPreferences.DefaultTestCaseSummaryPreferences });
            testCaseSummaryView.checkBoxShowCrashTestRuns.SetBinding(
                    CheckBox.IsCheckedProperty,
                    new Binding("IsCrashResultsDisplayed") { Mode = BindingMode.TwoWay, UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged, Source = this.viewModel.TestReportViewUserPreferences.DefaultTestCaseSummaryPreferences });
        }

        private void hideTestCaseSummaryView()
        {
            this.removeTestCaseSummaryViewSelectedTestCaseChangedEventHandler();
            this.storeViewSizePreferences();

            this.scrollViewerTestCaseSummary.Content = null;
            this.groupBoxTestCaseSummary.Visibility = Visibility.Collapsed;

            // Grid splitter is deliberately Hidden (not Collapsed). Because collapsed state causes sometimes to hide test report view.
            this.advancedGridSplitterTestCaseSummary.Visibility = Visibility.Hidden;
            this.advancedGridSplitterTestCaseSummary.Height = 0;

            this.rowDefinitionTestCaseSummary.MinHeight = 0;
            this.rowDefinitionTestCaseSummary.Height = GridLength.Auto;
            this.rowDefinitionTestReport.Height = new GridLength(1, GridUnitType.Star);
        }

        private void showTestCaseSummaryView()
        {
            this.groupBoxTestCaseSummary.Visibility = Visibility.Visible;

            // Grid splitter is set back to the default height.
            this.advancedGridSplitterTestCaseSummary.Visibility = Visibility.Visible;
            this.advancedGridSplitterTestCaseSummary.Height = 8;
            
            this.restoreViewSizePreferences();
        }

        private void storeViewSizePreferences()
        {
            // Row definition Tag property is used for storing previous height when summary view is hidden.
            this.rowDefinitionTestCaseSummary.Tag = this.rowDefinitionTestCaseSummary.Height;
            this.rowDefinitionTestReport.Tag = this.rowDefinitionTestReport.Height;
        }

        private void restoreViewSizePreferences()
        {
            if (this.rowDefinitionTestCaseSummary.Tag == null && !(this.rowDefinitionTestCaseSummary.Tag is GridLength))
                this.rowDefinitionTestCaseSummary.Height = new GridLength(2, GridUnitType.Star);
            else
                this.rowDefinitionTestCaseSummary.Height = (GridLength)this.rowDefinitionTestCaseSummary.Tag;

            if (this.rowDefinitionTestReport.Tag == null && !(this.rowDefinitionTestReport.Tag is GridLength))
                this.rowDefinitionTestReport.Height = new GridLength(3, GridUnitType.Star);
            else
                this.rowDefinitionTestReport.Height = (GridLength)this.rowDefinitionTestReport.Tag;
        }

        private void removeTestCaseSummaryViewSelectedTestCaseChangedEventHandler()
        {
            if (this.scrollViewerTestCaseSummary.Content == null) return;

            TestReportTestCaseSummaryView testReportTestCaseSummaryView = this.scrollViewerTestCaseSummary.Content as TestReportTestCaseSummaryView;

            if (testReportTestCaseSummaryView != null)
                testReportTestCaseSummaryView.SelectedTestCaseChanged -= this.testCaseSummaryView_SelectedTestCaseChanged;
        }

        void testCaseSummaryView_SelectedTestCaseChanged(object sender, TestCase selectedTestCase)
        {
            if (sender == null || selectedTestCase == null) return;
            if (sender != this.scrollViewerTestCaseSummary.Content) return;

            this.ChangeTestReport(selectedTestCase.Result);
        }

        private TestReportViewModel viewModel
        {
            get
            {
                if (this.DataContext is TestReportViewModel) return this.DataContext as TestReportViewModel;

                return null;
            }
        }

        private bool isWindowModeEnabled;

        public bool IsWindowModeEnabled
        {
            get
            {
                return this.isWindowModeEnabled;
            }
            set
            {
                this.isWindowModeEnabled = value;
                this.OnPropertyChanged("IsWindowModeEnabled");

                this.updateWindowMode();
            }
        }

        private bool isBottomControlBarVisible;

        public bool IsBottomControlBarVisible
        {
            get
            {
                return this.isBottomControlBarVisible;
            }
            set
            {
                this.isBottomControlBarVisible = value;
                this.OnPropertyChanged("IsBottomControlBarVisible");

                this.updateBottomControlBarVisibility();
            }
        }

        public void SaveReportAsPngImage()
        {
            this.saveItemsControlItemsToScreenShots();
        }

        public List<string> SaveReportToScreenshotImages()
        {
            string testCaseScreenshotFilePath = MarblePaths.MarbleTestReportScreenshotTempDirectory + "\\" + this.viewModel.TestReport.TestResultXmlFileName + ".summary.screenshot.jpg";

            this.createScreenshotFromTestReportSummary(testCaseScreenshotFilePath);
            
            this.ExpandAllGroupBoxes();
            this.UpdateLayout();
            
            List<string> fileNames = this.saveItemsControlItemsToScreenShots();
            fileNames.Insert(0, testCaseScreenshotFilePath);

            return fileNames;
        }

        private void saveReportAsPngImage()
        {
            SizeToContent tempSizeToContent = this.ParentWindow.SizeToContent;
            double tempHeight = this.ParentWindow.Height;
            double tempWidth = this.ParentWindow.Width;

            this.ParentWindow.SizeToContent = SizeToContent.Height;
            this.ParentWindow.Width = 800;
            byte[] screenshot = this.groupBoxTestReport.GetPngImage(1.0);
            this.ParentWindow.SizeToContent = tempSizeToContent;
            this.ParentWindow.Height = tempHeight;
            this.ParentWindow.Width = tempWidth;

            string filePath = FileUtilities.ShowSaveAsFileDialogForMarbleTestReportPdf();

            if (string.IsNullOrEmpty(filePath)) return;

            try
            {
                FileStream fileStream = new FileStream(filePath, FileMode.Create, FileAccess.ReadWrite);
                BinaryWriter binaryWriter = new BinaryWriter(fileStream);
                binaryWriter.Write(screenshot);
                binaryWriter.Close();
            }
            catch (IOException ioe)
            {
                MessageBox.Show(ioe.Message, "Marble - PDF Exporting Failed");
            }
        }

        private List<string> saveItemsControlItemsToScreenShots(int heightThreshold = 800)
        {
            List<string> screenshotFilePaths = new List<string>();
            double tempWidth = this.ParentWindow.Width;

            this.ParentWindow.Width = heightThreshold;

            double childItemsHeightTemp = 0;
            List<ItemsControl> itemsControls = new List<ItemsControl>();

            for (int i = 0; i < this.itemsControlTestCaseReportItems.Items.Count; i++)
            {
                ContentPresenter childItem = itemsControlTestCaseReportItems.ItemContainerGenerator.ContainerFromIndex(i) as ContentPresenter;

                // Control height must be fitted to single screenshot.
                if (childItem != null && childItem.ActualHeight >= heightThreshold)
                {
                    // Start new screenshot items control.
                    itemsControls.Add(new ItemsControl() { Width = this.itemsControlTestCaseReportItems.ActualWidth });
                    itemsControls.Last().Items.Add(childItem);
                    childItemsHeightTemp = 0;

                    continue;
                }

                // New items control for screen shot is created when child items height exceeds threshold or no child items are in the current items control exceeding threshold.
                if (childItemsHeightTemp.Equals(0) || childItemsHeightTemp + childItem.ActualHeight > heightThreshold)
                {
                    itemsControls.Add(new ItemsControl() { Width = this.itemsControlTestCaseReportItems.ActualWidth });
                    itemsControls.Last().Items.Add(childItem);
                    childItemsHeightTemp = childItem.ActualHeight;

                    continue;
                }

                itemsControls.Last().Items.Add(childItem);
                childItemsHeightTemp += childItem.ActualHeight;
            }

            int screenshotIndex = 1;

            // Screenshot is created from every temporary items control.
            foreach (ItemsControl itemsControl in itemsControls)
            {
                Window newWindow = new Window();
                newWindow.Content = itemsControl;
                newWindow.SizeToContent = SizeToContent.Height;
                newWindow.Width = 800;

                // Wíndow startup location is set to position where user can't see it.
                newWindow.WindowStartupLocation = WindowStartupLocation.Manual;
                newWindow.Left = 2000;
                newWindow.Top = 2000;

                newWindow.Show();

                itemsControl.Height = (int)itemsControl.ActualHeight;

                screenshotFilePaths.Add(MarblePaths.MarbleTestReportScreenshotTempDirectory + "\\screenshot." + screenshotIndex + ".jpg");

                byte[] screenshot = newWindow.GetJpgImage(1.0, 95);

                try
                {
                    FileStream fileStream = new FileStream(screenshotFilePaths.Last(), FileMode.Create, FileAccess.ReadWrite);
                    BinaryWriter binaryWriter = new BinaryWriter(fileStream);
                    binaryWriter.Write(screenshot);
                    binaryWriter.Close();
                }
                catch (IOException ioe)
                {
                    MessageBox.Show(ioe.Message, "Marble - PDF Exporting Failed");
                }
                finally
                {
                    screenshotIndex++;

                    newWindow.Close();    
                }
            }

            this.ParentWindow.Width = tempWidth;

            return screenshotFilePaths;
        }

        private void createScreenshotFromTestReportSummary(string testReportScreenshotFilePath)
        {
            if (string.IsNullOrEmpty(testReportScreenshotFilePath)) return;

            this.itemsControlTestCaseReportItems.Visibility = Visibility.Collapsed;
            ////this.scrollViewerTestCaseReport.VerticalScrollBarVisibility = ScrollBarVisibility.Hidden;
            this.UpdateLayout();

            byte[] screenshot = this.groupBoxTestReport.GetJpgImage(1.0, 95);

            if (screenshot == null) return;

            try
            {
                FileStream fileStream = new FileStream(testReportScreenshotFilePath, FileMode.Create, FileAccess.ReadWrite);
                BinaryWriter binaryWriter = new BinaryWriter(fileStream);
                binaryWriter.Write(screenshot);
                binaryWriter.Close();
            }
            catch (IOException ioe)
            {
                MessageBox.Show(ioe.Message, "Marble - PDF Exporting Failed");
            }
            finally
            {
                ////this.scrollViewerTestCaseReport.VerticalScrollBarVisibility = ScrollBarVisibility.Auto;
                this.itemsControlTestCaseReportItems.Visibility = Visibility.Visible;
            }
        }

        private void buttonOpenTestResult_Click(object sender, RoutedEventArgs e)
        {
            string filePath = FileUtilities.ShowOpenFileDialogForMarbleTestReport(Directory.GetCurrentDirectory());

            this.viewModel.ChangeTestReport(filePath);
        }

        private void updateWindowMode()
        {
            Visibility visibility = this.IsWindowModeEnabled ? Visibility.Visible : Visibility.Collapsed;

            this.buttonCancel.Visibility = visibility;
        }

        private void updateBottomControlBarVisibility()
        {
            Visibility visibility = this.IsBottomControlBarVisible ? Visibility.Visible : Visibility.Collapsed;

            this.gridBottomControlBar.Visibility = visibility;
        }

        #region [ INotifyPropertyChanged Members ]

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion [ INotifyPropertyChanged Members ]

        private void buttonExportTestReport_Click(object sender, RoutedEventArgs e)
        {
            string defaultFileName = this.viewModel.TestReport.TestResultXmlFileName;
            if (defaultFileName.EndsWith(FileUtilities.DefaultMarbleTestReportFileExtension))
                defaultFileName = defaultFileName.Substring(0, defaultFileName.Length - FileUtilities.DefaultMarbleTestReportFileExtension.Length) + FileUtilities.DefaultMarbleTestReportPdfFileExtension;

            string filePath = FileUtilities.ShowSaveAsFileDialogForMarbleTestReportPdf(string.Empty, defaultFileName);

            if (string.IsNullOrEmpty(filePath) || filePath == defaultFileName) return;

            this.viewModel.ExportTestReportAsDocument(filePath, this.viewModel.TestReport.TestResultXmlFilePath);
        }

        private void radioButtonMtbfView_Click(object sender, RoutedEventArgs e)
        {
            TestReportTestCaseSummaryView testCaseSummaryView = this.scrollViewerTestCaseSummary.Content as TestReportTestCaseSummaryView;

            if (testCaseSummaryView == null) return;

            testCaseSummaryView.ChangeResultCountCollection(this.viewModel.ViewMode);
            testCaseSummaryView.TestCaseSummaryViewUserPreferences = this.GetCurrentTestCaseSummaryViewUserPreferences();
        }

        public TestReportTestCaseSummaryViewUserPreferences GetCurrentTestCaseSummaryViewUserPreferences()
        {
            switch (this.viewModel.ViewMode)
            {
                case TestReportViewMode.Default:
                    return this.viewModel.TestReportViewUserPreferences.DefaultTestCaseSummaryPreferences;
                case TestReportViewMode.Rsa:
                    return this.viewModel.TestReportViewUserPreferences.RsaTestCaseSummaryPreferences;
                case TestReportViewMode.Mtbf:
                    return this.viewModel.TestReportViewUserPreferences.MtbfTestCaseSummaryPreferences;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        public void UpdateTestReportViewSize()
        {
            this.UcTestReportView_SizeChanged(null, null);
        }

        private void UcTestReportView_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            double newHeight = this.groupBoxTestReport.ActualHeight - 30;

            if (newHeight > 0)
            {
                this.itemsControlTestCaseReportItems.Height = newHeight;
            }

            TestReportTestCaseSummaryView testReportTestCaseSummaryView = this.scrollViewerTestCaseSummary.Content as TestReportTestCaseSummaryView;

            if (testReportTestCaseSummaryView == null) return;

            double newTestCaseDataGridHeight = this.rowDefinitionTestCaseSummary.ActualHeight - 120;

            if (newTestCaseDataGridHeight <= 100) return;

            ////testReportTestCaseSummaryView.dataGridTestCases.Height = newTestCaseDataGridHeight;
            ////testReportTestCaseSummaryView.dataGridTestCases.MaxHeight = newTestCaseDataGridHeight;

            if (this.IsViewModeHorizontal)
            {
                testReportTestCaseSummaryView.dataGridTestCases.Height = this.ActualHeight - 120;
                testReportTestCaseSummaryView.dataGridTestCases.MaxHeight = this.ActualHeight - 120;

                this.groupBoxTestCaseSummary.Height = this.ActualHeight;
                this.groupBoxTestCaseSummary.MaxHeight = this.ActualHeight;
            }
            else
            {
                testReportTestCaseSummaryView.dataGridTestCases.Height = newTestCaseDataGridHeight;
                testReportTestCaseSummaryView.dataGridTestCases.MaxHeight = newTestCaseDataGridHeight;

                this.groupBoxTestCaseSummary.Height = this.rowDefinitionTestCaseSummary.ActualHeight;
                this.groupBoxTestCaseSummary.MaxHeight = this.rowDefinitionTestCaseSummary.ActualHeight;
            }
        }

        private void AdvancedGridSplitterTestCaseSummary_OnIsCollapsedValueChanged(object sender, RoutedEventArgs e)
        {
            this.UcTestReportView_SizeChanged(null, null);
        }
    }
}
