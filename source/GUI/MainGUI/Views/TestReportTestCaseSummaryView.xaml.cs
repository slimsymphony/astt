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
    using System.Collections;
    using System.Collections.ObjectModel;
    using System.ComponentModel;
    using System.Globalization;
    using System.IO;
    using System.Windows.Controls.DataVisualization.Charting;
    using System.Windows.Threading;
    using System.Xml.Linq;

    using Marble.Model;
    using Marble.Utilities;
    using Marble.ViewModel;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// Interaction logic for TestReportView.xaml
    /// </summary>
    public partial class TestReportTestCaseSummaryView : UcBase, INotifyPropertyChanged
    {
        public TestReportTestCaseSummaryView(List<TestCase> testCaseList, SummaryMode summaryMode = SummaryMode.MultipleTestCases)
        {
            this.SummaryMode = summaryMode;
            this.DataContext = new TestCaseSummaryModel(testCaseList, summaryMode);

            this.InitializeComponent();

            this.ApplyGrouping();
            this.refreshNavigationButtons();
        }

        public TestReportTestCaseSummaryView(TestCase testCase)
        {
            this.SummaryMode = SummaryMode.SingleTestCase;
            this.DataContext = new TestCaseSummaryModel(new List<TestCase>() { testCase }, SummaryMode.SingleTestCase);

            this.InitializeComponent();

            this.ApplyGrouping();
            this.refreshNavigationButtons();
        }

        private TestReportViewModel viewModel;

        /// <summary>
        /// Gets or sets the view model.
        /// </summary>
        public TestReportViewModel ViewModel
        {
            get
            {
                return this.viewModel;
            }
            set
            {
                this.viewModel = value;
                this.OnPropertyChanged("ViewModel");
            }
        }

        private SummaryMode summaryMode;

        /// <summary>
        /// Gets the summary mode.
        /// </summary>
        public SummaryMode SummaryMode
        {
            get
            {
                return this.summaryMode;
            }
            private set
            {
                this.summaryMode = value;
                this.OnPropertyChanged("SummaryMode");
            }
        }

        private TestReportTestCaseSummaryViewUserPreferences testCaseSummaryViewUserPreferences;

        /// <summary>
        /// Gets or sets the view user preferences.
        /// </summary>
        public TestReportTestCaseSummaryViewUserPreferences TestCaseSummaryViewUserPreferences
        {
            get
            {
                return this.testCaseSummaryViewUserPreferences;
            }
            set
            {
                this.testCaseSummaryViewUserPreferences = value;
                this.TestCaseSummaryViewUserPreferences.LoadTestReportTestCaseSummaryViewPreferences(this);
            }
        }

        /// <summary>
        /// Gets or sets the current group description for sorting the list collection view.
        /// </summary>
        public string CurrentGroupDescription { get; set; }

        private ListCollectionView timeSortedListCollectionView { get; set; }

        /// <summary>
        /// Applies grouping to list collection view.
        /// </summary>
        public void ApplyGrouping()
        {
            List<TestCase> testCases = this.GetTestCaseList();

            this.timeSortedListCollectionView = new ListCollectionView(testCases.OrderBy(testRun => testRun.Result.RunTime).ThenBy(testRun => testRun.Name).ToList());

            ListCollectionView listCollectionView = new ListCollectionView(testCases);

            listCollectionView.Filter = this.testCaseStatusFilter;
            this.safelySetDataGridItemsSource(listCollectionView);
        }

        /// <summary>
        /// Gets the list of test case results.
        /// </summary>
        /// <returns></returns>
        public List<TestCase> GetTestCaseList()
        {
            TestCaseSummaryModel testCaseSummaryModel = this.DataContext as TestCaseSummaryModel;

            List<TestCase> testCases = new List<TestCase>();

            if (testCaseSummaryModel == null) return null;

            foreach (TestCase testCase in testCaseSummaryModel.TestCases)
            {
                if (testCase.Children.Count == 0)
                    testCases.Add(testCase);
                else
                    testCases.AddRange(testCase.Children);
            }

            return testCases;
        }

        /// <summary>
        /// Updates current test case list.
        /// </summary>
        /// <param name="testCaseList"></param>
        public void UpdateTestCaseList(List<TestCase> testCaseList)
        {
            TestCaseSummaryModel testCaseSummaryModel = this.DataContext as TestCaseSummaryModel;

            if (testCaseSummaryModel == null) return;

            this.dataGridTestCases.SelectionChanged -= this.ListView_SelectionChanged;

            testCaseSummaryModel.UpdateTestCases(testCaseList);

            List<TestCase> testCases = new List<TestCase>();

            foreach (TestCase testCase in testCaseList)
            {
                if (testCase.Children.Count == 0)
                    testCases.Add(testCase);
                else
                    testCases.AddRange(testCase.Children);
            }

            var currentlySelectedTestCase = this.dataGridTestCases.SelectedItem;

            this.timeSortedListCollectionView = new ListCollectionView(testCases.OrderBy(testRun => testRun.Result.RunTime).ThenBy(testRun => testRun.Name).ToList());

            ListCollectionView listCollectionView = new ListCollectionView(testCases);

            ////using (listCollectionView.DeferRefresh())
            ////{
                listCollectionView.Filter = this.testCaseStatusFilter;
                this.safelySetDataGridItemsSource(listCollectionView);
                this.ApplyGrouping(this.TestCaseSummaryViewUserPreferences.GroupingMode);
                this.SortTestRuns(this.TestCaseSummaryViewUserPreferences.SortDescription);
            ////}
            
            this.dataGridTestCases.SelectedItem = currentlySelectedTestCase;
            
            this.dataGridTestCases.SelectionChanged += this.ListView_SelectionChanged;
        }

        public void AddTestCaseToTestCaseList(TestCase testCaseToAdd)
        {
            if (testCaseToAdd == null) return;

            ListCollectionView listCollectionView = this.safelyGetDataGridItemsSource();

            if (listCollectionView == null)
            {
                //NOTE: UPDATE WHOLE LIST
                //this.UpdateTestCaseList();
                return;
            }

            this.timeSortedListCollectionView.AddNewItem(testCaseToAdd);
            ////this.timeSortedListCollectionView.



            listCollectionView.AddNewItem(testCaseToAdd);
        }

        private void changeSummaryMode(SummaryMode summaryMode)
        {
            this.SummaryMode = summaryMode;

            switch (summaryMode)
            {
                case SummaryMode.SingleTestCase:
                    this.textBlockSummaryTitle.Text = "Test Case Results Summary";
                    this.textBlockListViewGroupBoxHeader.Text = "Test Runs";
                    break;
                case SummaryMode.MultipleTestCases:
                    this.textBlockSummaryTitle.Text = "Selected Test Cases Summary";
                    this.textBlockListViewGroupBoxHeader.Text = "Test Cases";
                    break;
                case SummaryMode.AllTestCasesInTestSet:
                    this.textBlockSummaryTitle.Text = "Test Set Summary";
                    this.textBlockListViewGroupBoxHeader.Text = "Test Cases";
                    break;
                default:
                    throw new ArgumentOutOfRangeException("summaryMode");
            }
        }

        /// <summary>
        /// Event handler which is fired when selected test case has changed..
        /// </summary>
        /// <param name="sender">Sender object.</param>
        /// <param name="selectedTestCase">Selected TestCase.</param>
        public delegate void SelectedTestCaseChangedEventHandler(object sender, TestCase selectedTestCase);

        public event SelectedTestCaseChangedEventHandler SelectedTestCaseChanged;

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

        private void ListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems == null) return;
            if (e.AddedItems.Count < 1) return;
            if (!(e.AddedItems[0] is TestCase)) return;

            if (this.SelectedTestCaseChanged != null) 
                this.SelectedTestCaseChanged(this, e.AddedItems[0] as TestCase);
        }

        private void checkBoxShowAllTestRuns_Checked(object sender, RoutedEventArgs e)
        {
            this.checkBoxShowPassedTestRuns.Checked -= this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowPassedTestRuns.Unchecked -= this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowFailedTestRuns.Checked -= this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowFailedTestRuns.Unchecked -= this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            ////this.checkBoxShowErrorTestRuns.Checked -= this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            ////this.checkBoxShowErrorTestRuns.Unchecked -= this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowNoResultTestRuns.Checked -= this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowNoResultTestRuns.Unchecked -= this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowCrashTestRuns.Checked -= this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowCrashTestRuns.Unchecked -= this.checkCheckBoxShowAllTestRunsIsCheckedStatus;

            this.checkBoxShowPassedTestRuns.IsChecked = this.checkBoxShowAllTestRuns.IsChecked;
            this.checkBoxShowFailedTestRuns.IsChecked = this.checkBoxShowAllTestRuns.IsChecked;
            ////this.checkBoxShowErrorTestRuns.IsChecked = this.checkBoxShowAllTestRuns.IsChecked;
            this.checkBoxShowNoResultTestRuns.IsChecked = this.checkBoxShowAllTestRuns.IsChecked;
            this.checkBoxShowCrashTestRuns.IsChecked = this.checkBoxShowAllTestRuns.IsChecked;
            this.changeTestRunsGroupBoxVisibility();

            this.checkBoxShowPassedTestRuns.Checked += this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowPassedTestRuns.Unchecked += this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowFailedTestRuns.Checked += this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowFailedTestRuns.Unchecked += this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            ////this.checkBoxShowErrorTestRuns.Checked += this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            ////this.checkBoxShowErrorTestRuns.Unchecked += this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowNoResultTestRuns.Checked += this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowNoResultTestRuns.Unchecked += this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowCrashTestRuns.Checked += this.checkCheckBoxShowAllTestRunsIsCheckedStatus;
            this.checkBoxShowCrashTestRuns.Unchecked += this.checkCheckBoxShowAllTestRunsIsCheckedStatus;

            // Refresh ListCollectionView to apply filters.
            if (this.dataGridTestCases == null) return;
            
            ListCollectionView listCollectionView = this.dataGridTestCases.ItemsSource as ListCollectionView;

            if (listCollectionView == null) return;
                
            listCollectionView.Refresh();
        }

        private void checkCheckBoxShowAllTestRunsIsCheckedStatus(object sender, RoutedEventArgs e)
        {
            this.checkBoxShowAllTestRuns.Checked -= this.checkBoxShowAllTestRuns_Checked;
            this.checkBoxShowAllTestRuns.Unchecked -= this.checkBoxShowAllTestRuns_Checked;

            this.checkBoxShowAllTestRuns.IsChecked = this.checkIsCheckedStatuses(true);
            this.changeTestRunsGroupBoxVisibility();
            //this.updateFilterUserPreferences();

            this.checkBoxShowAllTestRuns.Checked += this.checkBoxShowAllTestRuns_Checked;
            this.checkBoxShowAllTestRuns.Unchecked += this.checkBoxShowAllTestRuns_Checked;

            // Refresh ListCollectionView to apply filters.
            if (this.dataGridTestCases == null) return;

            ListCollectionView listCollectionView = this.dataGridTestCases.ItemsSource as ListCollectionView;

            if (listCollectionView == null) return;

            listCollectionView.Refresh();
            this.refreshNavigationButtons();
        }

        private void refreshNavigationButtons()
        {
            bool isPassedCheckBoxShowPassedTestRuns = this.checkBoxShowPassedTestRuns.Visibility == Visibility.Visible && this.checkBoxShowPassedTestRuns.IsChecked == true;
            bool isPassedCheckBoxShowFailedTestRuns = this.checkBoxShowFailedTestRuns.Visibility == Visibility.Visible && this.checkBoxShowFailedTestRuns.IsChecked == true;
            ////bool isPassedCheckBoxShowErrorTestRuns = this.checkBoxShowErrorTestRuns.Visibility == Visibility.Visible && this.checkBoxShowErrorTestRuns.IsChecked == true;
            bool isPassedCheckBoxShowNoResultTestRuns = this.checkBoxShowNoResultTestRuns.Visibility == Visibility.Visible && this.checkBoxShowNoResultTestRuns.IsChecked == true;

            this.buttonNextFailedTestRun.IsEnabled = isPassedCheckBoxShowFailedTestRuns
                                                     | isPassedCheckBoxShowNoResultTestRuns;
                                                     ////| isPassedCheckBoxShowErrorTestRuns;
            this.buttonPreviousFailedTestRun.IsEnabled = this.buttonNextFailedTestRun.IsEnabled;
            this.buttonNextFailedByTime.IsEnabled = this.buttonNextFailedTestRun.IsEnabled;
            this.buttonPreviousFailedByTime.IsEnabled = this.buttonNextFailedTestRun.IsEnabled;

            this.buttonNextPassedTestRun.IsEnabled = isPassedCheckBoxShowPassedTestRuns;
            this.buttonPreviousPassedTestRun.IsEnabled = isPassedCheckBoxShowPassedTestRuns;
        }

        private bool checkIsCheckedStatuses(bool? expectedIsChecked, bool checkBoxMustBeVisibleToCheck = true)
        {
            if (!checkBoxMustBeVisibleToCheck)
                return this.checkBoxShowPassedTestRuns.IsChecked == expectedIsChecked &&
                       this.checkBoxShowFailedTestRuns.IsChecked == expectedIsChecked &&
                       ////this.checkBoxShowErrorTestRuns.IsChecked == expectedIsChecked &&
                       this.checkBoxShowNoResultTestRuns.IsChecked == expectedIsChecked &&
                       this.checkBoxShowCrashTestRuns.IsChecked == expectedIsChecked;

            bool isPassedCheckBoxShowPassedTestRuns = this.checkBoxShowPassedTestRuns.Visibility != Visibility.Visible || this.checkBoxShowPassedTestRuns.IsChecked == expectedIsChecked;
            bool isPassedCheckBoxShowFailedTestRuns = this.checkBoxShowFailedTestRuns.Visibility != Visibility.Visible || this.checkBoxShowFailedTestRuns.IsChecked == expectedIsChecked;
            ////bool isPassedCheckBoxShowErrorTestRuns = this.checkBoxShowErrorTestRuns.Visibility != Visibility.Visible || this.checkBoxShowErrorTestRuns.IsChecked == expectedIsChecked;
            bool isPassedCheckBoxShowNoResultTestRuns = this.checkBoxShowNoResultTestRuns.Visibility != Visibility.Visible || this.checkBoxShowNoResultTestRuns.IsChecked == expectedIsChecked;
            bool isPassedCheckBoxShowNotAvailableTestRuns = this.checkBoxShowCrashTestRuns.Visibility != Visibility.Visible || this.checkBoxShowCrashTestRuns.IsChecked == expectedIsChecked;

            return isPassedCheckBoxShowPassedTestRuns && 
                isPassedCheckBoxShowFailedTestRuns && 
                ////isPassedCheckBoxShowErrorTestRuns && 
                isPassedCheckBoxShowNoResultTestRuns && 
                isPassedCheckBoxShowNotAvailableTestRuns;
        }

        private void changeTestRunsGroupBoxVisibility()
        {
            if (this.groupBoxTestRuns == null) return;

            this.groupBoxTestRuns.Visibility = this.checkIsCheckedStatuses(false) ? Visibility.Collapsed : Visibility.Visible;
        }

        private DataGridColumn lastHeaderClicked;
        private ListSortDirection lastDirection = ListSortDirection.Ascending;

        private void dataGridTestCases_Sorting(object sender, DataGridSortingEventArgs e)
        {
            // Set Handled to true, since we use our own sorting and this messes up the DataGrid.
            e.Handled = true;

            DataGridColumn headerClicked = e.Column as DataGridColumn;
            ListSortDirection direction;

            if (headerClicked != null)
            {
                if (headerClicked != this.lastHeaderClicked)
                {
                    direction = ListSortDirection.Ascending;

                    // Add the SortDirection manually to get the sort indicating arrow to show.
                    headerClicked.SortDirection = direction;
                }
                else
                {
                    if (this.lastDirection == ListSortDirection.Ascending)
                    {
                        direction = ListSortDirection.Descending;

                        // Add the SortDirection manually to get the sort indicating arrow to show.
                        headerClicked.SortDirection = direction;
                    }
                    else
                    {
                        direction = ListSortDirection.Ascending;

                        // Add the SortDirection manually to get the sort indicating arrow to show.
                        headerClicked.SortDirection = direction;
                    }
                }

                this.SortTestRuns(headerClicked, direction);

                this.lastHeaderClicked = headerClicked;
                this.lastDirection = direction;
            }
        }
        
        /// <summary>
        /// Sorts test runs according to data grid column and direction.
        /// </summary>
        /// <param name="dataGridColumn">Data grid template column.</param>
        /// <param name="direction">List sort direction.</param>
        public void SortTestRuns(DataGridColumn dataGridColumn, ListSortDirection direction)
        {
            ListCollectionView listCollection = this.dataGridTestCases.ItemsSource as ListCollectionView;

            if (listCollection == null) return;

            ////using (listCollection.DeferRefresh())
            ////{
                listCollection.SortDescriptions.Clear();

                // First sorting is added with possible grouping.
                if (listCollection.GroupDescriptions != null && listCollection.GroupDescriptions.Count > 0)
                {
                    listCollection.SortDescriptions.Add(
                        new SortDescription(this.CurrentGroupDescription, ListSortDirection.Ascending));
                }

                SortDescription newSortDescription = new SortDescription();

                if (dataGridColumn == this.dataGridTemplateColumnRuntime)
                {
                    newSortDescription = new SortDescription("Result.RunTime", direction);
                }
                else if (dataGridColumn == this.dataGridTemplateColumnTestCaseName)
                {
                    newSortDescription = new SortDescription("Name", direction);
                }
                else if (dataGridColumn == this.dataGridTemplateColumnResult)
                {
                    newSortDescription = new SortDescription("Result.Result", direction);
                }
                else if (dataGridColumn == this.dataGridTemplateColumnIndex)
                {
                    newSortDescription = new SortDescription("Result.Index", direction);
                }
                else if (dataGridColumn == this.dataGridTemplateColumnWhitebox)
                {
                    newSortDescription = new SortDescription("Result.IsBlackboxModeOn", direction);
                }
                else if (dataGridColumn == this.dataGridTemplateColumnErrorReason)
                {
                    newSortDescription = new SortDescription("Result.ErrorReason", direction);
                }
                else
                {
                    return;
                }

                listCollection.SortDescriptions.Add(newSortDescription);
                this.TestCaseSummaryViewUserPreferences.SortDescription = newSortDescription;

                dataGridColumn.SortDirection = direction;
            ////}
        }

        /// <summary>
        /// Sorts test runs according to sort description.
        /// </summary>
        /// <param name="sortDescription">Sort description.</param>
        public void SortTestRuns(SortDescription sortDescription)
        {
            if (string.IsNullOrEmpty(sortDescription.PropertyName)) return;

            ListCollectionView listCollection = this.dataGridTestCases.ItemsSource as ListCollectionView;

            if (listCollection == null) return;

            ////using (listCollection.DeferRefresh())
            ////{
                listCollection.SortDescriptions.Clear();

                // First sorting is added with possible grouping.
                if (listCollection.GroupDescriptions != null && listCollection.GroupDescriptions.Count > 0)
                {
                    listCollection.SortDescriptions.Add(
                        new SortDescription(this.CurrentGroupDescription, ListSortDirection.Ascending));
                }

                listCollection.SortDescriptions.Add(sortDescription);
                this.TestCaseSummaryViewUserPreferences.SortDescription = sortDescription;

                switch (sortDescription.PropertyName)
                {
                    case "Result.RunTime":
                        this.dataGridTemplateColumnRuntime.SortDirection = sortDescription.Direction;
                        break;
                    case "Name":
                        this.dataGridTemplateColumnTestCaseName.SortDirection = sortDescription.Direction;
                        break;
                    case "Result.Result":
                        this.dataGridTemplateColumnResult.SortDirection = sortDescription.Direction;
                        break;
                    case "Result.Index":
                        this.dataGridTemplateColumnIndex.SortDirection = sortDescription.Direction;
                        break;
                    case "Result.IsBlackboxModeOn":
                        this.dataGridTemplateColumnWhitebox.SortDirection = sortDescription.Direction;
                        break;
                }
            ////}
        }

        /// <summary>
        /// Applies grouping according to grouping mode.
        /// </summary>
        /// <param name="groupingMode">Test report summary grouping mode.</param>
        public void ApplyGrouping(TestReportTestCaseSummaryViewUserPreferences.TestReportSummaryGroupingMode groupingMode)
        {
            switch (groupingMode)
            {
                case TestReportTestCaseSummaryViewUserPreferences.TestReportSummaryGroupingMode.None:
                    this.buttonApplyGrouping_Click(this.buttonNoGrouping, null);
                    break;
                case TestReportTestCaseSummaryViewUserPreferences.TestReportSummaryGroupingMode.Result:
                    this.buttonApplyGrouping_Click(this.buttonGroupByResult, null);
                    break;
                case TestReportTestCaseSummaryViewUserPreferences.TestReportSummaryGroupingMode.TestCaseName:
                    this.buttonApplyGrouping_Click(this.buttonGroupByTestCaseName, null);
                    break;
                case TestReportTestCaseSummaryViewUserPreferences.TestReportSummaryGroupingMode.RunIndex:
                    this.buttonApplyGrouping_Click(this.buttonGroupByRunIndex, null);
                    break;
                default:
                    throw new ArgumentOutOfRangeException("groupingMode");
            }
        }

        private void buttonApplyGrouping_Click(object sender, RoutedEventArgs e)
        {
            ListCollectionView listCollectionView = this.dataGridTestCases.ItemsSource as ListCollectionView;

            if (listCollectionView == null) return;

            ////using (listCollectionView.DeferRefresh())
            ////{
                listCollectionView.GroupDescriptions.Clear();

                if (sender == this.buttonGroupByResult)
                {
                    this.CurrentGroupDescription = "Result.Result";
                    this.TestCaseSummaryViewUserPreferences.GroupingMode =
                        TestReportTestCaseSummaryViewUserPreferences.TestReportSummaryGroupingMode.Result;
                }
                else if (sender == this.buttonGroupByTestCaseName)
                {
                    this.CurrentGroupDescription = "Name";
                    this.TestCaseSummaryViewUserPreferences.GroupingMode =
                        TestReportTestCaseSummaryViewUserPreferences.TestReportSummaryGroupingMode.TestCaseName;
                }
                else if (sender == this.buttonGroupByRunIndex)
                {
                    this.CurrentGroupDescription = "Result.Index";
                    this.TestCaseSummaryViewUserPreferences.GroupingMode =
                        TestReportTestCaseSummaryViewUserPreferences.TestReportSummaryGroupingMode.RunIndex;
                }
                else if (sender == this.buttonNoGrouping)
                {
                    // No grouping is applied.
                    this.CurrentGroupDescription = string.Empty;
                    this.TestCaseSummaryViewUserPreferences.GroupingMode =
                        TestReportTestCaseSummaryViewUserPreferences.TestReportSummaryGroupingMode.None;
                }

                if (!string.IsNullOrEmpty(this.CurrentGroupDescription))
                {
                    listCollectionView.GroupDescriptions.Add(new PropertyGroupDescription(this.CurrentGroupDescription));
                }
            ////}
        }

        private void buttonNextFailedTestRun_Click(object sender, RoutedEventArgs e)
        {
            this.MoveToNextFailedTestRun();
        }

        private void buttonPreviousFailedTestRun_Click(object sender, RoutedEventArgs e)
        {
            this.MoveToPreviousFailedTestRun();
        }

        private void moveToNextTestRun(string[] statusToFindList)
        {
            if (statusToFindList == null || statusToFindList.Length < 1) return;

            ListCollectionView listCollectionView = this.dataGridTestCases.ItemsSource as ListCollectionView;

            if (listCollectionView == null) return;

            for (int i = 0; i < listCollectionView.Count; i++)
            {
                bool canMoveToNext = listCollectionView.MoveCurrentToNext();

                // When list collection view cannot move to the next, list has reached end and first item is selected.
                if (!canMoveToNext)
                    listCollectionView.MoveCurrentToFirst();

                if (statusToFindList.Any(status => ((TestCase)listCollectionView.CurrentItem).Result.Result.ToLower() == status))
                {
                    break;
                }
            }
        }

        private void moveToNextTestRunByTime(string[] statusToFindList)
        {
            if (statusToFindList == null || statusToFindList.Length < 1) return;

            ListCollectionView listCollectionView = this.dataGridTestCases.ItemsSource as ListCollectionView;

            if (listCollectionView == null) return;

            this.timeSortedListCollectionView.MoveCurrentTo(listCollectionView.CurrentItem);

            for (int i = 0; i < this.timeSortedListCollectionView.Count; i++)
            {
                bool canMoveToNext = this.timeSortedListCollectionView.MoveCurrentToNext();

                // When list collection view cannot move to the next, list has reached end and first item is selected.
                if (!canMoveToNext)
                    this.timeSortedListCollectionView.MoveCurrentToFirst();

                if (statusToFindList.Any(status => ((TestCase)this.timeSortedListCollectionView.CurrentItem).Result.Result.ToLower() == status))
                {
                    listCollectionView.MoveCurrentTo(this.timeSortedListCollectionView.CurrentItem);
                    break;
                }
            }
        }

        private void moveToPreviousTestRun(string[] statusToFindList)
        {
            if (statusToFindList == null || statusToFindList.Length < 1) return;

            ListCollectionView listCollectionView = this.dataGridTestCases.ItemsSource as ListCollectionView;

            if (listCollectionView == null) return;

            for (int i = 0; i < listCollectionView.Count; i++)
            {
                bool canMoveToPrevious = listCollectionView.MoveCurrentToPrevious();

                // When list collection view cannot move to the previous, list has reached beginning and last item is selected.
                if (!canMoveToPrevious)
                    listCollectionView.MoveCurrentToLast();

                if (statusToFindList.Any(status => ((TestCase)listCollectionView.CurrentItem).Result.Result.ToLower() == status))
                {
                    break;
                }
            }
        }

        private void moveToPreviousTestRunByTime(string[] statusToFindList)
        {
            if (statusToFindList == null || statusToFindList.Length < 1) return;

            ListCollectionView listCollectionView = this.dataGridTestCases.ItemsSource as ListCollectionView;

            if (listCollectionView == null) return;

            this.timeSortedListCollectionView.MoveCurrentTo(listCollectionView.CurrentItem);

            for (int i = 0; i < this.timeSortedListCollectionView.Count; i++)
            {
                bool canMoveToPrevious = this.timeSortedListCollectionView.MoveCurrentToPrevious();

                // When list collection view cannot move to the previous, list has reached beginning and last item is selected.
                if (!canMoveToPrevious)
                    this.timeSortedListCollectionView.MoveCurrentToLast();

                if (statusToFindList.Any(status => ((TestCase)this.timeSortedListCollectionView.CurrentItem).Result.Result.ToLower() == status))
                {
                    listCollectionView.MoveCurrentTo(this.timeSortedListCollectionView.CurrentItem);
                    break;
                }
            }
        }

        public void MoveToNextFailedTestRun()
        {
            this.moveToNextTestRun(new string[] { "failed", "error", "no result" });
        }

        public void MoveToNextPassedTestRun()
        {
            this.moveToNextTestRun(new string[] { "passed" });
        }

        public void MoveToPreviousFailedTestRun()
        {
            this.moveToPreviousTestRun(new string[] { "failed", "error", "no result" });
        }

        public void MoveToPreviousPassedTestRun()
        {
            this.moveToPreviousTestRun(new string[] { "passed" });
        }

        private void buttonNextPassedTestRun_Click(object sender, RoutedEventArgs e)
        {
            this.MoveToNextPassedTestRun();
        }

        private void buttonPreviousPassedTestRun_Click(object sender, RoutedEventArgs e)
        {
            this.MoveToPreviousPassedTestRun();
        }

        private void buttonNextFailedByTime_Click(object sender, RoutedEventArgs e)
        {
            this.moveToNextTestRunByTime(new string[] { "failed", "error", "no result" });
        }

        private void buttonPreviousFailedByTime_Click(object sender, RoutedEventArgs e)
        {
            this.moveToPreviousTestRunByTime(new string[] { "failed", "error", "no result" });
        }

        private bool testCaseStatusFilter(object item)
        {
            if (item == null) return false;

            TestCase testCase = item as TestCase;

            if (testCase == null) return false;
            if (testCase.Result == null) return false;

            ////if (testCase.Result.Result.ToLower().Contains("error") && this.checkBoxShowErrorTestRuns.IsChecked == false) return false;

            if (this.checkBoxShowCrashTestRuns.IsChecked == true && testCase.HasCrashOrReset) return true;

            switch (testCase.Result.Result.ToLower())
            {
                case "passed":
                    return this.checkBoxShowPassedTestRuns.IsChecked == true;
                case "failed":
                    return this.checkBoxShowFailedTestRuns.IsChecked == true;
                case "no result":
                    return this.checkBoxShowNoResultTestRuns.IsChecked == true;                    
            }

            return false;
        }

        /// <summary>
        /// The change result count collection.
        /// </summary>
        /// <param name="viewMode">The view mode.</param>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public void ChangeResultCountCollection(TestReportViewMode viewMode)
        {
            switch (viewMode)
            {
                case TestReportViewMode.Default:
                    this.pieSeriesSummary.SetBinding(PieSeries.DataContextProperty, new Binding());
                    this.pieSeriesSummary.SetBinding(PieSeries.ItemsSourceProperty, new Binding("ResultCountCollection") { UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged });
                    break;
                case TestReportViewMode.Rsa:
                    this.pieSeriesSummary.SetBinding(PieSeries.DataContextProperty, new Binding() { ElementName = "UcTestReportTestCaseSummaryView" });
                    this.pieSeriesSummary.SetBinding(PieSeries.ItemsSourceProperty, new Binding("RsaResultCountCollection") { UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged });
                    break;
                case TestReportViewMode.Mtbf:
                    this.pieSeriesSummary.SetBinding(PieSeries.DataContextProperty, new Binding() { ElementName = "UcTestReportTestCaseSummaryView" });
                    this.pieSeriesSummary.SetBinding(PieSeries.ItemsSourceProperty, new Binding("RsaResultCountCollection") { UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged });
                    break;
                default:
                    throw new ArgumentOutOfRangeException("viewMode");
            }
        }

        /// <summary>
        /// Gets the passed iteration count.
        /// </summary>
        public int PassedIterationCount { get { return this.getStatusIterationCount("Passed"); } }

        /// <summary>
        /// Gets the failed iteration count.
        /// </summary>
        public int FailedIterationCount { get { return this.getStatusIterationCount("Failed"); } }

        /// <summary>
        /// Gets the error iteration count.
        /// </summary>
        public int ErrorIterationCount { get { return this.getStatusIterationCount("Error"); } }

        /// <summary>
        /// Gets the no result iteration count.
        /// </summary>
        public int NoResultIterationCount { get { return this.getStatusIterationCount("No Result"); } }

        /// <summary>
        /// Gets the not available iteration count.
        /// </summary>
        public int NotAvailableIterationCount { get { return this.getStatusIterationCount("N/A"); } }

        /// <summary>
        /// Gets the total iteration count.
        /// </summary>
        public int TotalIterationCount { get { return this.getTotalIterationCount(); } }

        public double Passrate { get { return this.getIterationPassrate(); } }

        /// <summary>
        /// Gets the rsa result count collection.
        /// </summary>
        public Collection<TestCaseChartDataModel> RsaResultCountCollection
        {
            get
            {
                List<TestCase> testCases = this.GetTestCaseList();

                if (testCases == null) return null;

                int passedTestIterationCount = 0;
                int failedTestIterationCount = 0;
                int errorTestIterationCount = 0;
                int noResultTestIterationCount = 0;
                int notAvailableTestIterationCount = 0;

                CollectionView collectionView = new ListCollectionView(testCases.OrderBy(testRun => testRun.Result.Index).ToList());

                collectionView.GroupDescriptions.Add(new PropertyGroupDescription("Result.Index"));

                if (collectionView.Groups == null) return null;

                foreach (CollectionViewGroup collectionGroup in collectionView.Groups)
                {
                    if (collectionGroup.Items.Any(tc => ((TestCase)tc).Result.Result.ToLower() == "error")) 
                        errorTestIterationCount++;
                    else if (collectionGroup.Items.Any(tc => ((TestCase)tc).Result.Result.ToLower().StartsWith("failed"))) 
                        failedTestIterationCount++;
                    else if (collectionGroup.Items.Any(tc => ((TestCase)tc).Result.Result.ToLower() == "no result")) 
                        noResultTestIterationCount++;
                    else if (collectionGroup.Items.Any(tc => ((TestCase)tc).Result.Result.ToLower() == "passed")) 
                        passedTestIterationCount++;
                    else if (collectionGroup.Items.Any(tc => ((TestCase)tc).Result.Result.ToLower() == "n/a"))
                        notAvailableTestIterationCount++;
                }

                return new Collection<TestCaseChartDataModel>()
                    {
                        new TestCaseChartDataModel("Passed", passedTestIterationCount),
                        new TestCaseChartDataModel("Failed", failedTestIterationCount),
                        new TestCaseChartDataModel("Error", errorTestIterationCount),
                        new TestCaseChartDataModel("No Result", noResultTestIterationCount),
                        new TestCaseChartDataModel("N/A", notAvailableTestIterationCount)
                    };
            }
        }

        private int getStatusIterationCount(string status)
        {
            return this.RsaResultCountCollection.Where(chartData => chartData.Name.ToLower() == status.ToLower()).Select(chartData => chartData.StatusCount).FirstOrDefault();
        }

        private int getTotalIterationCount()
        {
            return this.RsaResultCountCollection.Sum(chartData => chartData.StatusCount);
        }

        private double getIterationPassrate()
        {
            double passrate = (double)this.getStatusIterationCount("passed") / (double)this.getTotalIterationCount() * 100;

            return passrate;
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            if (!(sender is MenuItem)) return;
            if (this.dataGridTestCases.SelectedItem == null) return;

            MenuItem senderMenuItem = sender as MenuItem;

            string newResult;

            TestCase selectedTestCase = this.dataGridTestCases.SelectedItem as TestCase;

            if (selectedTestCase == null) return;

            switch (senderMenuItem.Header.ToString().ToLower())
            {
                case "passed":
                    newResult = "Passed";
                    break;
                case "failed":
                    newResult = "Failed";
                    break;
                case "error":
                    newResult = "Error";
                    break;
                case "no result":
                    newResult = "No Result";
                    break;
                case "n/a":
                    newResult = "N/A";
                    break;
                default:
                    newResult = selectedTestCase.Result.OriginalResult;
                    break;
            }

            if (string.IsNullOrEmpty(newResult)) return;

            if (string.IsNullOrEmpty(selectedTestCase.Result.OriginalResult))
                selectedTestCase.Result.OriginalResult = selectedTestCase.Result.Result;

            selectedTestCase.Result.Result = newResult;
            
            // Test Set file is always saved after user has changed test result.
            App.ViewModel.SaveTestsetFileCommandExecuted();

            this.RefreshSummary();
        }

        /// <summary>
        /// Refreshes summary by forcing OnPropertyChanged for all properties.
        /// </summary>
        public void RefreshSummary()
        {
            if (this.DataContext != null)
                ((TestCaseSummaryModel)this.DataContext).RefreshTestCaseSummaryModelProperties();

            this.OnPropertyChanged("RsaResultCountCollection");
            this.OnPropertyChanged("PassedIterationCount");
            this.OnPropertyChanged("FailedIterationCount");
            this.OnPropertyChanged("ErrorIterationCount");
            this.OnPropertyChanged("NoResultIterationCount");
            this.OnPropertyChanged("NotAvailableIterationCount");
            this.OnPropertyChanged("TotalIterationCount");
            this.OnPropertyChanged("Passrate");
        }

        private void buttonCopyToClipboard_Click(object sender, RoutedEventArgs e)
        {
            TestCaseUtilities.CopyExcelCompatibleTestRunSummaryResultToClipboard(this.dataGridTestCases.ItemsSource);
        }

        /// <summary>
        /// Selects test report by test case.
        /// </summary>
        /// <param name="testCaseToSelect"></param>
        public void SelectTestReport(TestCase testCaseToSelect)
        {
            TestCase testCase = testCaseToSelect;

            if (testCase == null) return;

            if (testCase.HasChildren) testCase = testCase.Children.LastOrDefault();

            if (testCase == null) return;

            if (this.dataGridTestCases.Items.Contains(testCase))
            {
                this.dataGridTestCases.SelectedItem = null;
                this.dataGridTestCases.SelectedItem = testCase;
                this.dataGridTestCases.ScrollIntoView(testCase);
            }
        }

        /// <summary>
        /// Opens selected test report in new window.
        /// </summary>
        public void OpenSelectedTestReport()
        {
            TestCase testCase = this.dataGridTestCases.SelectedItem as TestCase;

            if (testCase == null || testCase.Result == null || string.IsNullOrEmpty(testCase.Result.ResultPath)) return;

            Window reportWindow = new Window();
            reportWindow.Title = "Marble - Test Report - " + Path.GetFullPath(testCase.Result.ResultPath);
            reportWindow.Icon = new BitmapImage(new Uri("pack://application:,,,/MarbleLibrary;component/Images/Marble.M.Icon.ico", UriKind.RelativeOrAbsolute));
            reportWindow.Content = new TestReportView(Path.GetFullPath(testCase.Result.ResultPath), true, false);
            ((TestReportView)reportWindow.Content).ParentWindow = reportWindow;
            reportWindow.Width = 800;
            reportWindow.Height = 600;

            reportWindow.Closing += new CancelEventHandler(this.reportWindow_Closing);

            reportWindow.Show();
        }

        /// <summary>
        /// Creates new test report summary view and displays it in a new window.
        /// </summary>
        public void CreateNewTestReportSummaryView()
        {
            TestCase testCase = this.dataGridTestCases.SelectedItem as TestCase;

            if (testCase == null) return;

            Window reportWindow = new Window();
            reportWindow.Title = "Marble - Test Report - " + Path.GetFullPath(testCase.Result.ResultPath);
            reportWindow.Icon = new BitmapImage(new Uri("pack://application:,,,/MarbleLibrary;component/Images/Marble.M.Icon.ico", UriKind.RelativeOrAbsolute));
            reportWindow.Content = new TestReportView(testCase.Result, true, true);
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

        private void DataGridTestCases_OnMouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            this.OpenSelectedTestReport();
        }

        private void MenuItemOpenReportInNewWindow_OnClick(object sender, RoutedEventArgs e)
        {
            this.OpenSelectedTestReport();
        }

        /// <summary>
        /// Safely sets ItemsSource for test case data grid.
        /// </summary>
        /// <param name="newItemsSource"></param>
        private void safelySetDataGridItemsSource(IEnumerable newItemsSource)
        {
            if (this.dataGridTestCases == null || newItemsSource == null) return;

            if (this.dataGridTestCases.ItemsSource is IEditableCollectionView)
            {
                if (((IEditableCollectionView)this.dataGridTestCases.ItemsSource).IsAddingNew)
                {
                    ((IEditableCollectionView)this.dataGridTestCases.ItemsSource).CommitNew();
                }
                if (((IEditableCollectionView)this.dataGridTestCases.ItemsSource).IsEditingItem)
                {
                    ((IEditableCollectionView)this.dataGridTestCases.ItemsSource).CommitEdit();
                }
            }

            this.dataGridTestCases.ItemsSource = newItemsSource;
        }

        /// <summary>
        /// Safely gets ItemsSource for test case data grid.
        /// </summary>
        private ListCollectionView safelyGetDataGridItemsSource()
        {
            if (this.dataGridTestCases == null) return null;

            if (this.dataGridTestCases.ItemsSource is IEditableCollectionView)
            {
                if (((IEditableCollectionView)this.dataGridTestCases.ItemsSource).IsAddingNew)
                {
                    ((IEditableCollectionView)this.dataGridTestCases.ItemsSource).CommitNew();
                }
                if (((IEditableCollectionView)this.dataGridTestCases.ItemsSource).IsEditingItem)
                {
                    ((IEditableCollectionView)this.dataGridTestCases.ItemsSource).CommitEdit();
                }
            }

            return this.dataGridTestCases.ItemsSource as ListCollectionView;
        }
    }
}
