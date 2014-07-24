using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using Marble.Model;

namespace Marble.Views
{
    using System;
    using System.Globalization;
    using System.IO;
    using System.Threading;
    using System.Windows.Data;
    using System.Windows.Input;
    using System.Windows.Media;
    using System.Windows.Threading;

    using FuseLib;

    using Marble.Communication;
    using Marble.Converters;
    using Marble.ViewModel;
    using MarbleLibrary.Utilities;
    using MediatorLib;

    public enum TestCaseSearchAreaEnum
    {
        TestCaseName = 0,
        Subarea = 1,
        Feature = 2,
        Result = 3,
        ErrorReason = 4,
        RunTime = 5,
        All = 10
    }

    /// <summary>
    /// Interaction logic for TestLabView.xaml
    /// </summary>
    public partial class TestLabView : UserControl
    {
        private DataGridColumn lastHeaderClicked;
        private ListSortDirection lastDirection = ListSortDirection.Ascending;
        private string contextMenuHeader = string.Empty;

        private readonly LinearGradientBrush errorBackground;

        /// <summary>
        /// Gets or sets whether the auto scrolling is currently enabled.
        /// </summary>
        public bool IsAutoScrollEnabled { get; set; }

        private bool isResizing { get; set; }

        /// <summary>
        /// Dispatcher timer which is used to slow down size changed events.
        /// </summary>
        private DispatcherTimer resizeTimer;

        private ScrollViewer scrollViewerDataGridTestCases;

        public TestLabView()
        {
            this.InitializeComponent();

            this.Loaded += new RoutedEventHandler(TestLabView_Loaded);
            this.Unloaded += TestLabView_Unloaded;
            App.ViewModel.SelectedTestCases.CollectionChanged += this.OnSelectedTestCasesChanged;
            App.ViewModel.Mediator.Register(this);

            ResourceDictionary resourceDictionary = new ResourceDictionary
                { Source = new Uri("pack://application:,,,/MarbleLibrary;component/Templates/MarbleTheme.xaml", UriKind.Absolute) };
            this.errorBackground = (LinearGradientBrush)resourceDictionary["MarbleTextBoxErrorBackground"];
        }

        /// <summary>
        /// Selects all test cases which are checked for testing.
        /// </summary>
        public void SelectAllCheckedTestCases()
        {
            // Selecting checked test cases is disabled when testing is on going.
            if (App.ViewModel.TestSetModel.CurrentTestCase != null) return;

            this.testCaseDataGrid.UnselectAll();

            foreach (TestCase firstLevelTestCase in App.ViewModel.TestSetModel.TestCases.Where(testCase => testCase.Level == 1).Where(firstLevelTestCase => firstLevelTestCase.IsWhiteboxChecked || firstLevelTestCase.IsBlackboxChecked))
            {
                this.testCaseDataGrid.SelectedItems.Add(firstLevelTestCase);
            }
        }

        private void TestLabView_Loaded(object sender, RoutedEventArgs e)
        {
            this.menuItemShowHideResultSummary.IsChecked = false;

            this.advancedGridSplitterHorizontal.Tag = false;
            this.advancedGridSplitterHorizontal.IsCollapsed = true;
            this.advancedGridSplitterHorizontal.IsEnabled = false;
            
            this.resizeTimer = new DispatcherTimer { Interval = new TimeSpan(0, 0, 0, 0, 200), IsEnabled = false };

            this.scrollViewerDataGridTestCases = GuiUtilities.FindVisualChild<ScrollViewer>(this.testCaseDataGrid);

            this.testCaseDataGrid.SizeChanged += this.testCaseDataGrid_SizeChanged;
            this.scrollViewerDataGridTestCases.ScrollChanged += scrollViewerDataGridTestCases_ScrollChanged;

            this.resizeTimer.Tick += this.resizeTimer_Tick;
        }

        private void TestLabView_Unloaded(object sender, RoutedEventArgs e)
        {
            this.resizeTimer.Stop();
            this.resizeTimer.Tick -= this.resizeTimer_Tick;
        }

        private void testCaseDataGrid_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            this.resizeTimer.IsEnabled = true;
            this.resizeTimer.Stop();
            this.resizeTimer.Start();
            this.isResizing = true;
        }

        private void resizeTimer_Tick(object sender, EventArgs e)
        {
            this.resizeTimer.IsEnabled = false;
            this.isResizing = false;

            if (this.IsAutoScrollEnabled && this.scrollViewerDataGridTestCases != null)
            {
                this.scrollViewerDataGridTestCases.ScrollToVerticalOffset(this.scrollViewerDataGridTestCases.ExtentHeight);
            }
        }

        private void scrollViewerDataGridTestCases_ScrollChanged(object sender, ScrollChangedEventArgs e)
        {
            if (this.scrollViewerDataGridTestCases == null) return;

            if (e.ExtentHeightChange == 0 && !this.isResizing)
            {
                if (this.scrollViewerDataGridTestCases.VerticalOffset + 2 >= this.scrollViewerDataGridTestCases.ScrollableHeight)
                {
                    this.IsAutoScrollEnabled = true;
                }
                else
                {
                    this.IsAutoScrollEnabled = false;
                }
            }

            if (this.IsAutoScrollEnabled && e.ExtentHeightChange != 0)
            {
                this.scrollViewerDataGridTestCases.ScrollToVerticalOffset(this.scrollViewerDataGridTestCases.ExtentHeight);
            }
        }

        private void OnTestCaseDataGridSorting(object sender, DataGridSortingEventArgs e)
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

                string header = headerClicked.Header as string;

                List<TestCase> caseList = App.ViewModel.TestSetModel.TestCases.ToList();
                // Collapse all test cases when sorting.
                foreach (TestCase tCase in caseList)
                {
                    tCase.IsExpanded = false;

                    if (!tCase.IsRoot)
                    {
                        tCase.IsVisible = false;

                        // Remove the child test case from the collection that's shown in UI.
                        App.ViewModel.TestSetModel.TestCases.Remove(tCase);
                    }
                }

                App.ViewModel.TestSetModel.TestCases.SortTestset(ConvertHeaderToTestCaseProperty(header), direction);

                this.lastHeaderClicked = headerClicked;
                this.lastDirection = direction;

                App.ViewModel.TestSetModel.IsSorted = true;
            }
        }

        /// <summary>
        /// Converts the name of the header to a name of a test case property.
        /// </summary>
        /// <param name="headerName">Name of the header.</param>
        /// <returns>Name of the test case property.</returns>
        private string ConvertHeaderToTestCaseProperty(string headerName)
        {
            string propertyName = headerName;

            CoreTestToolTestSetToSubareaHeadingConverter subareaHeadingConverter = new CoreTestToolTestSetToSubareaHeadingConverter();
            CoreTestToolTestSetToFeatureHeadingConverter featureHeadingConverter = new CoreTestToolTestSetToFeatureHeadingConverter();

            // If we have a subarea header for a Core Test Tool test set
            if (propertyName == (string)subareaHeadingConverter.Convert(true, typeof(string), null, Thread.CurrentThread.CurrentUICulture))
            {
                // Convert the subarea header to its standard name 
                propertyName = (string)subareaHeadingConverter.Convert(false, typeof(string), null, Thread.CurrentThread.CurrentUICulture);
            }

            // Else if we have a feature header for a Core Test Tool test set
            else if (propertyName == (string)featureHeadingConverter.Convert(true, typeof(string), null, Thread.CurrentThread.CurrentUICulture))
            {
                // Convert the feature header to its standard name 
                propertyName = (string)featureHeadingConverter.Convert(false, typeof(string), null, Thread.CurrentThread.CurrentUICulture);
            }

            return propertyName;
        }

        private void OnDataGridLoaded(object sender, RoutedEventArgs e)
        {
            // Set SelectedIndex to -1 initially.
            testCaseDataGrid.SelectedIndex = -1;
        }

        public void SearchAndSelectTestCases(string searchText, TestCaseSearchAreaEnum searchArea = TestCaseSearchAreaEnum.TestCaseName, bool caseSensitive = false, bool clearSelectionsBeforeNewOnes = true)
        {
            bool searchedTextFound = false;

            foreach (TestCase testCase in App.ViewModel.TestSetModel.TestCases)
            {
                switch (searchArea)
                {
                    case TestCaseSearchAreaEnum.TestCaseName:
                        if (caseSensitive)
                        { if (!testCase.Name.Contains(searchText)) continue; }
                        else
                        { if (!testCase.Name.ToLower().Contains(searchText.ToLower())) continue; }
                        break;
                    case TestCaseSearchAreaEnum.Subarea:
                        if (caseSensitive)
                        { if (!testCase.Subarea.Contains(searchText)) continue; }
                        else
                        { if (!testCase.Subarea.ToLower().Contains(searchText.ToLower())) continue; }
                        break;
                    case TestCaseSearchAreaEnum.Feature:
                        if (caseSensitive)
                        { if (!testCase.Feature.Contains(searchText)) continue; }
                        else
                        { if (!testCase.Feature.ToLower().Contains(searchText.ToLower())) continue; }
                        break;
                    case TestCaseSearchAreaEnum.Result:
                        if (caseSensitive)
                        { if (!testCase.Result.Result.Contains(searchText)) continue; }
                        else
                        { if (!testCase.Result.Result.ToLower().Contains(searchText.ToLower())) continue; }
                        break;
                    case TestCaseSearchAreaEnum.ErrorReason:
                        if (caseSensitive)
                        { if (!testCase.Result.ErrorReason.Contains(searchText)) continue; }
                        else
                        { if (!testCase.Result.ErrorReason.ToLower().Contains(searchText.ToLower())) continue; }
                        break;
                    case TestCaseSearchAreaEnum.RunTime:
                        if (caseSensitive) 
                        { if (!testCase.Result.RunTime.ToString(CultureInfo.InvariantCulture).Contains(searchText)) continue; }
                        else 
                        { if (!testCase.Result.RunTime.ToString(CultureInfo.InvariantCulture).ToLower().Contains(searchText.ToLower())) continue; }
                        break;
                    case TestCaseSearchAreaEnum.All:
                        if (caseSensitive)
                        {
                            if (!testCase.Name.Contains(searchText) &&
                                !testCase.Subarea.Contains(searchText) &&
                                !testCase.Feature.Contains(searchText) &&
                                !testCase.Result.Result.Contains(searchText) &&
                                !testCase.Result.ErrorReason.Contains(searchText) &&
                                !testCase.Result.RunTime.ToString(CultureInfo.InvariantCulture).Contains(searchText)) continue;   
                        }
                        else
                        {
                            if (!testCase.Name.ToLower().Contains(searchText.ToLower()) &&
                                !testCase.Subarea.ToLower().Contains(searchText.ToLower()) &&
                                !testCase.Feature.ToLower().Contains(searchText.ToLower()) &&
                                !testCase.Result.Result.ToLower().Contains(searchText.ToLower()) &&
                                !testCase.Result.ErrorReason.ToLower().Contains(searchText.ToLower()) &&
                                !testCase.Result.RunTime.ToString(CultureInfo.InvariantCulture).ToLower().Contains(searchText.ToLower())) continue;
                        }
                        break;
                    default:
                        throw new ArgumentOutOfRangeException("searchArea");
                }

                if (!searchedTextFound && clearSelectionsBeforeNewOnes)
                {
                    searchedTextFound = true;
                    this.testCaseDataGrid.UnselectAll();
                }

                this.testCaseDataGrid.SelectedItems.Add(testCase);
            }

            if (this.testCaseDataGrid.SelectedItems.Count <= 0) return;

            this.testCaseDataGrid.ScrollIntoView(this.testCaseDataGrid.SelectedItems[0]);
        }

        /// <summary>
        /// Searches text from test cases.
        /// </summary>
        /// <param name="searchText">Text to search.</param>
        /// <param name="searchArea">Area of the test case where text is searched.</param>
        /// <param name="caseSensitive">Is case sensitive.</param>
        /// <returns>Returns whether the text was found.</returns>
        public bool SearchTextFromTestCases(string searchText, TestCaseSearchAreaEnum searchArea = TestCaseSearchAreaEnum.TestCaseName, bool caseSensitive = false)
        {
            switch (searchArea)
            {
                case TestCaseSearchAreaEnum.TestCaseName:
                    return !caseSensitive
                        ? App.ViewModel.TestSetModel.TestCases.Any(testCase => testCase.Name.ToLower().Contains(searchText.ToLower()))
                        : App.ViewModel.TestSetModel.TestCases.Any(testCase => testCase.Name.Contains(searchText));
                case TestCaseSearchAreaEnum.Subarea:
                    return !caseSensitive
                        ? App.ViewModel.TestSetModel.TestCases.Any(testCase => testCase.Subarea.ToLower().Contains(searchText.ToLower()))
                        : App.ViewModel.TestSetModel.TestCases.Any(testCase => testCase.Subarea.Contains(searchText));
                case TestCaseSearchAreaEnum.Feature:
                    return !caseSensitive
                        ? App.ViewModel.TestSetModel.TestCases.Any(testCase => testCase.Feature.ToLower().Contains(searchText.ToLower()))
                        : App.ViewModel.TestSetModel.TestCases.Any(testCase => testCase.Feature.Contains(searchText));
                case TestCaseSearchAreaEnum.Result:
                    return !caseSensitive
                        ? App.ViewModel.TestSetModel.TestCases.Any(testCase => testCase.Result.Result.ToLower().Contains(searchText.ToLower()))
                        : App.ViewModel.TestSetModel.TestCases.Any(testCase => testCase.Result.Result.Contains(searchText));
                case TestCaseSearchAreaEnum.ErrorReason:
                    return !caseSensitive
                        ? App.ViewModel.TestSetModel.TestCases.Any(testCase => testCase.Result.ErrorReason.ToLower().Contains(searchText.ToLower()))
                        : App.ViewModel.TestSetModel.TestCases.Any(testCase => testCase.Result.ErrorReason.Contains(searchText));
                case TestCaseSearchAreaEnum.RunTime:
                    return !caseSensitive
                        ? App.ViewModel.TestSetModel.TestCases.Any(testCase => testCase.Result.RunTime.ToString(CultureInfo.InvariantCulture).ToLower().Contains(searchText.ToLower()))
                        : App.ViewModel.TestSetModel.TestCases.Any(testCase => testCase.Result.RunTime.ToString(CultureInfo.InvariantCulture).Contains(searchText));
                case TestCaseSearchAreaEnum.All:
                    break;
                default:
                    throw new ArgumentOutOfRangeException("searchArea");
            }

            return false;
        }

        /// <summary>
        /// Sets the _contextMenuHeader variable for column resize event.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnContextMenuOpening(object sender, ContextMenuEventArgs e)
        {
            DependencyObject dep = (DependencyObject)e.OriginalSource;

            // Iteratively traverse the visual tree.
            while ((dep != null) && !(dep is DataGridColumnHeader))
            {
                // Prevents replacing the ContextMenu of TextBlocks.
                if (dep is TextBlock)
                {
                    TextBlock textBlock = dep as TextBlock;
                    TestCase testCase = textBlock.DataContext as TestCase;

                    if (testCase != null)
                        break;
                }

                dep = System.Windows.Media.VisualTreeHelper.GetParent(dep);
            }

            if (dep == null)
            {
                // If dep == null, right-click happened outside of DataGrid header, so we ignore it.
                e.Handled = true;

                return;
            }

            if (dep is DataGridColumnHeader)
            {
                DataGridColumnHeader columnHeader = dep as DataGridColumnHeader;

                if (columnHeader.Content == null)
                    return;

                this.contextMenuHeader = columnHeader.Content.ToString();
            }
        }

        /// <summary>
        /// Sizes the right-clicked columns width to it's cells content width.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnContextMenuSizeColumnClicked(object sender, RoutedEventArgs e)
        {
            foreach (DataGridColumn dgc in testCaseDataGrid.Columns)
            {
                if (dgc.Header == null)
                    continue;

                if (dgc.Header.ToString() == this.contextMenuHeader)
                {
                    dgc.Width = DataGridLength.SizeToCells;
                    this.contextMenuHeader = string.Empty;
                }
            }
        }

        /// <summary>
        /// Sizes all columns widths to their cells content width.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnContextMenuSizeAllColumnsClicked(object sender, RoutedEventArgs e)
        {
            foreach (DataGridColumn dgc in testCaseDataGrid.Columns)
            {
                // Only size column if it's one of the named columns except the last column.
                if (dgc.Header != null && dgc != testCaseDataGrid.Columns.Last())
                    dgc.Width = DataGridLength.SizeToCells;
            }
        }

        /// <summary>
        /// Set hidden column visible.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnContextMenuItemChecked(object sender, RoutedEventArgs e)
        {
            this.changeDataGridTemplateVisibility(sender, e, Visibility.Visible);
        }

        /// <summary>
        /// Hide column.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnContextMenuItemUnChecked(object sender, RoutedEventArgs e)
        {
            this.changeDataGridTemplateVisibility(sender, e, Visibility.Collapsed);
        }

        private void changeDataGridTemplateVisibility(object sender, RoutedEventArgs e, Visibility visibility)
        {
            if (sender == null) return;
            if (testCaseDataGrid.Columns.Count == 0) return;

            if (sender == menuItemShowHideSubarea)
                dataGridTemplateColumnSubarea.Visibility = visibility;
            else if (sender == menuItemShowHideFeature)
                dataGridTemplateColumnFeature.Visibility = visibility;
            else if (sender == menuItemShowHideTestCase)
                dataGridTemplateColumnTestCase.Visibility = visibility;
            else if (sender == menuItemShowHideResult)
                dataGridTemplateColumnResult.Visibility = visibility;
            else if (sender == menuItemShowHideResultSummary)
                dataGridTemplateColumnResultSummary.Visibility = visibility;
            else if (sender == menuItemShowHideErrorReason)
                dataGridTemplateColumnErrorReason.Visibility = visibility;
            else if (sender == menuItemShowHideRunTime)
                dataGridTemplateColumnRunTime.Visibility = visibility;
        }

        /// <summary>
        /// Checks all rows.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WhiteboxCheckAllRows(object sender, RoutedEventArgs e)
        {
            foreach (TestCase testCase in App.ViewModel.TestSetModel.TestCases.Where(item => item.IsRoot && !item.IsWhiteboxChecked))
                testCase.IsWhiteboxChecked = true;
        }

        /// <summary>
        /// Checks all rows.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BlackboxCheckAllRows(object sender, RoutedEventArgs e)
        {
            foreach (TestCase testCase in App.ViewModel.TestSetModel.TestCases.Where(item => !item.IsBlackboxChecked))
                testCase.IsBlackboxChecked = true;
        }

        /// <summary>
        /// Unchecks all rows.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WhiteboxUnCheckAllRows(object sender, RoutedEventArgs e)
        {
            foreach (TestCase testCase in App.ViewModel.TestSetModel.TestCases.Where(item => item.IsRoot && item.IsWhiteboxChecked))
                testCase.IsWhiteboxChecked = false;
        }

        /// <summary>
        /// Unchecks all rows.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BlackboxUnCheckAllRows(object sender, RoutedEventArgs e)
        {
            foreach (TestCase testCase in App.ViewModel.TestSetModel.TestCases.Where(item => item.IsBlackboxChecked))
                testCase.IsBlackboxChecked = false;
        }

        /// <summary>
        /// Removes previous checks and checks the selected rows.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WhiteboxOnSelectionMenuSelectSelectedClick(object sender, RoutedEventArgs e)
        {
            // First remove all checks from all rows.
            foreach (TestCase model in App.ViewModel.TestSetModel.TestCases)
            {
                model.IsWhiteboxChecked = false;
            }

            // Check the selected rows.
            foreach (TestCase testCase in testCaseDataGrid.SelectedItems)
            {
                testCase.IsWhiteboxChecked = true;
            }
        }

        /// <summary>
        /// Removes previous checks and checks the selected rows.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BlackboxOnSelectionMenuSelectSelectedClick(object sender, RoutedEventArgs e)
        {
            // First remove all checks from all rows.
            foreach (TestCase model in App.ViewModel.TestSetModel.TestCases)
            {
                model.IsBlackboxChecked = false;
            }

            // Check the selected rows.
            foreach (TestCase testCase in testCaseDataGrid.SelectedItems)
            {
                testCase.IsBlackboxChecked = true;
            }
        }

        /// <summary>
        /// Checks selected rows.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WhiteboxOnSelectionMenuAddSelectedClick(object sender, RoutedEventArgs e)
        {
            // Check the selected rows.
            foreach (TestCase testCase in testCaseDataGrid.SelectedItems)
            {
                testCase.IsWhiteboxChecked = true;
            }
        }

        /// <summary>
        /// Checks selected rows.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BlackboxOnSelectionMenuAddSelectedClick(object sender, RoutedEventArgs e)
        {
            // Check the selected rows.
            foreach (TestCase testCase in testCaseDataGrid.SelectedItems)
            {
                testCase.IsBlackboxChecked = true;
            }
        }


        /// <summary>
        /// Reverses checked rows to unchecked and vice versa.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WhiteboxOnSelectionMenuInvertSelectionClick(object sender, RoutedEventArgs e)
        {
            foreach (TestCase testCase in App.ViewModel.TestSetModel.TestCases)
            {
                testCase.IsWhiteboxChecked = !testCase.IsWhiteboxChecked;
            }
        }

        /// <summary>
        /// Reverses checked rows to unchecked and vice versa.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BlackboxOnSelectionMenuInvertSelectionClick(object sender, RoutedEventArgs e)
        {
            foreach (TestCase testCase in App.ViewModel.TestSetModel.TestCases)
            {
                testCase.IsBlackboxChecked = !testCase.IsBlackboxChecked;
            }
        }

        private void OnSelectionMenuSortClick(object sender, RoutedEventArgs e)
        {

        }

        private void OnTestCaseDragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                // show preview or something
            }
        }

        private void OnTestCaseDragOver(object sender, DragEventArgs e)
        {
            e.Effects = DragDropEffects.None;
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                string[] data = e.Data.GetData(DataFormats.FileDrop) as string[];
                if (data != null && data[0].EndsWith(".testset"))
                    e.Effects = DragDropEffects.Copy;
            }
        }

        public ICommand OpenSimpleTextEditor { get { return App.ViewModel.OpenSimpleTextEditor; } }

        /// <summary>
        /// Navigates only from root row to root row with PageDown/PageUp arrow keys.
        /// Home/End keys will go straight to first/last row.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnTestCaseDataGridPreviewKeyDown(object sender, KeyEventArgs e)
        {
            DataGrid dataGrid = sender as DataGrid;
            TestCase testCase = dataGrid.CurrentItem as TestCase;

            if (testCase == null)
                return;

            int currCellIndex = testCaseDataGrid.CurrentCell.Column.DisplayIndex;
            int index = App.ViewModel.TestSetModel.TestCases.IndexOf(testCase);

            switch (e.Key)
            {
                case Key.PageDown:
                    for (int i = index + 1; i < App.ViewModel.TestSetModel.TestCases.Count; i++)
                    {
                        if (!App.ViewModel.TestSetModel.TestCases[i].IsRoot) continue;

                        this.testCaseDataGrid.CurrentCell = new DataGridCellInfo(App.ViewModel.TestSetModel.TestCases[i], dataGrid.Columns[currCellIndex]);
                        this.testCaseDataGrid.SelectedIndex = i;
                        //App.ViewModel.TestSetModel.SelectedTestCase = App.ViewModel.TestSetModel.TestCases[i];
                        e.Handled = true;
                        break;
                    }

                    break;

                case Key.PageUp:
                    if (index == 0) return;

                    for (int i = index - 1; i < App.ViewModel.TestSetModel.TestCases.Count; i--)
                    {
                        if (!App.ViewModel.TestSetModel.TestCases[i].IsRoot) continue;

                        this.testCaseDataGrid.CurrentCell = new DataGridCellInfo(App.ViewModel.TestSetModel.TestCases[i], dataGrid.Columns[currCellIndex]);
                        this.testCaseDataGrid.SelectedIndex = i;
                        //App.ViewModel.TestSetModel.SelectedTestCase = App.ViewModel.TestSetModel.TestCases[i];
                        e.Handled = true;
                        break;
                    }

                    break;

                case Key.Home:
                    if (index == 0) return;

                    this.testCaseDataGrid.CurrentCell = new DataGridCellInfo(App.ViewModel.TestSetModel.TestCases[0], dataGrid.Columns[currCellIndex]);
                    this.testCaseDataGrid.SelectedIndex = 0;
                    //App.ViewModel.TestSetModel.SelectedTestCase = App.ViewModel.TestSetModel.TestCases[0];
                    e.Handled = true;
                    break;

                case Key.End:
                    this.testCaseDataGrid.CurrentCell = new DataGridCellInfo(App.ViewModel.TestSetModel.TestCases.Last(), dataGrid.Columns[currCellIndex]);
                    this.testCaseDataGrid.SelectedIndex = this.testCaseDataGrid.Items.Count - 1;
                    //App.ViewModel.TestSetModel.SelectedTestCase = App.ViewModel.TestSetModel.TestCases.Last();
                    e.Handled = true;
                    break;

                case Key.Delete:
                    if (!App.ViewModel.SelectedTestCases.Any()) return;

                    if (MessageBox.Show("Are you sure you want to remove selected test case(s) from the test set?",
                                         "Remove selected test case(s)?", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
                        foreach (TestCase testCaseToRemove in App.ViewModel.SelectedTestCases.Where(tc => tc.IsRoot && !tc.IsRunning).ToList())
                            App.ViewModel.TestSetModel.RemoveTestCaseAndChildren(testCaseToRemove);    

                    break;
            }
        }

        private void OnSelectedTestCasesChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            return;

            this.UpdateTestReportView(App.ViewModel.SelectedTestCase);
        }

        [MediatorMessageSink("SelectedTestCaseChanged", ParameterType = typeof(TestCase))]
        public void UpdateTestReportView(TestCase testCase)
        {
            return;

            if (!this.IsLoaded) return;

            // Test Case parameter not found. Report is not shown.
            if (testCase == null)
            {
                return;

                this.advancedGridSplitterHorizontal.IsCollapsed = true;
                this.advancedGridSplitterHorizontal.IsEnabled = false;
                
                return;
            }

            if (!App.ViewModel.SelectedTestCases.Contains(testCase)) return;

            // Result path is not found from the Test Case. Child Test Cases are inspected.
            if (string.IsNullOrEmpty(testCase.Result.ResultPath) || testCase.Children.Count > 0)
            {
                // Test Case has no child Test Cases.
                if (testCase.Level == 1 && testCase.Children.Count <= 0 && App.ViewModel.SelectedFirstLevelTestCases.Count() <= 1)
                {
                    this.advancedGridSplitterHorizontal.IsCollapsed = true;
                    this.advancedGridSplitterHorizontal.IsEnabled = false;
                    
                    return;
                }

                TestCase testCaseToDisplay = null;

                // When the first of selected Test Cases does not contain results, the first case containing results is used.
                if (testCase.Children.Count <= 0 && App.ViewModel.SelectedFirstLevelTestCases.Count() > 1)
                {
                    testCaseToDisplay = App.ViewModel.SelectedFirstLevelTestCases.FirstOrDefault(tc => tc.Children.Count > 0);
                }

                if (testCaseToDisplay == null) 
                    testCaseToDisplay = testCase;

                // Test Case has child Test Case(s) and result file is found.
                var lastNonRunningChild = testCaseToDisplay.Children.LastOrDefault(tc => !tc.IsRunning);
                if (testCaseToDisplay.Level == 1 && lastNonRunningChild != null)
                {
                    ////this.testReportViewMainWindow.ChangeTestReportAndInitializeView(lastNonRunningChild.Result);
                    this.storeOrRestoreAdvancedGridSplitterIsCollapsed();

                    return;
                }

                this.advancedGridSplitterHorizontal.IsCollapsed = true;
                this.advancedGridSplitterHorizontal.IsEnabled = false;

                return;
            }

            ////this.testReportViewMainWindow.ChangeTestReportAndInitializeView(testCase.Result);
            this.storeOrRestoreAdvancedGridSplitterIsCollapsed();
        }

        private void loadMultipleTestCaseSummary()
        {
            if (!this.IsLoaded) return;
            if (App.ViewModel.SelectedFirstLevelTestCases.Count() <= 1) return;

            // Currently displayed report is cleared.
            ////this.setRightSideInfoMessage(string.Empty, string.Empty, false);
            ////this.gridTestReport.Children.Clear();
            ////App.ViewModel.MainWindowTestReportViewModel = null;

            List<TestCase> testCases = new List<TestCase>();

            foreach (TestCase testCase in App.ViewModel.SelectedFirstLevelTestCases.ToList())
            {
                testCases.AddRange(testCase.Children);
            }

            this.gridTestReport.Children.Add(new TestReportTestCaseSummaryView(testCases, SummaryMode.SingleTestCase));
            TestReportView mainWindowTestReportView = new TestReportView(testCases[0].Result, false, false);

            this.gridTestReport.Children.Add(mainWindowTestReportView);
            App.ViewModel.MainWindowTestReportViewModel = mainWindowTestReportView.DataContext as TestReportViewModel;
            this.storeOrRestoreAdvancedGridSplitterIsCollapsed();
        }

        private void storeOrRestoreAdvancedGridSplitterIsCollapsed()
        {
            if (!this.advancedGridSplitterHorizontal.IsEnabled && this.advancedGridSplitterHorizontal.Tag != null)
            {
                this.advancedGridSplitterHorizontal.IsEnabled = true;
                this.advancedGridSplitterHorizontal.IsCollapsed = (bool)this.advancedGridSplitterHorizontal.Tag;
            }
            else if (this.advancedGridSplitterHorizontal.IsEnabled)
            {
                this.advancedGridSplitterHorizontal.Tag = this.advancedGridSplitterHorizontal.IsCollapsed;
            }

            if (this.advancedGridSplitterHorizontal.IsEnabled && this.columnDefinitionTestReport.ActualWidth <= 10)
            {
                this.columnDefinitionTestReport.Width = new GridLength(300);
            }
        }

        /// <summary>
        /// Handler for the trace xml browse button click.
        /// Displays open file dialog and updates selected file combo box and to recent list.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Browse_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog openFileDialog = new Microsoft.Win32.OpenFileDialog();
            openFileDialog.Filter = "Extensible Markup Language|*.xml";
            openFileDialog.InitialDirectory = System.IO.Path.GetFullPath(FileUtilities.DefaultTraceXmlDirectory);

            // Set previously used trace file directory as the initial directory
            if (!string.IsNullOrEmpty(App.ViewModel.TraceXmlPath) && System.IO.File.Exists(App.ViewModel.TraceXmlPath))
                openFileDialog.InitialDirectory = System.IO.Path.GetFullPath(System.IO.Path.GetDirectoryName(App.ViewModel.TraceXmlPath));

            // Show open file dialog and check if OK was pressed and filename was selected
            if ((bool)openFileDialog.ShowDialog() && !string.IsNullOrEmpty(openFileDialog.FileName))
            {
                if (!System.IO.File.Exists(openFileDialog.FileName)) return;
                MarbleFileSettingsModel.AddTraceXmlToRecentList(openFileDialog.FileName);
                ComboboxTraceFiles.SelectedItem = openFileDialog.FileName;
            }
        }

        /// <summary>
        /// Handler for the next test set browse button click.
        /// Displays open file dialog and updates the next test set text box.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BrowseNextTestSet_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog openFileDialog = new Microsoft.Win32.OpenFileDialog();
            openFileDialog.Filter = "Marble testset|*.testset";
            openFileDialog.InitialDirectory = System.IO.Path.GetFullPath(@"..\test_sets\");

            // Set previously used testset file directory as the initial directory
            if (!string.IsNullOrEmpty(App.ViewModel.TestSetModel.NextTestSetPath) && System.IO.File.Exists(App.ViewModel.TestSetModel.NextTestSetPath))
                openFileDialog.InitialDirectory = System.IO.Path.GetFullPath(System.IO.Path.GetDirectoryName(App.ViewModel.TestSetModel.NextTestSetPath));

            // Show open file dialog and check if OK was pressed and filename was selected
            if ((bool)openFileDialog.ShowDialog() && !string.IsNullOrEmpty(openFileDialog.FileName))
            {
                if (!System.IO.File.Exists(openFileDialog.FileName)) return;
                App.ViewModel.TestSetModel.NextTestSetPath = openFileDialog.FileName;
            }
        }

        private void TestCaseDataGridSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            App.ViewModel.SelectedTestCases.RemoveRange(e.RemovedItems.Cast<TestCase>());
            App.ViewModel.SelectedTestCases.InsertRange(App.ViewModel.SelectedTestCases.Count, e.AddedItems.Cast<TestCase>());
        }

        private void ButtonSearchTestCase_OnClick(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(this.textBoxSearch.Text)) return;

            TestCaseSearchAreaEnum searchArea = TestCaseSearchAreaEnum.TestCaseName;

            if (this.comboBoxItemSearchTestCase.IsSelected)
                searchArea = TestCaseSearchAreaEnum.TestCaseName;
            else if (this.comboBoxItemSearchSubarea.IsSelected)
                searchArea = TestCaseSearchAreaEnum.Subarea;
            else if (this.comboBoxItemSearchFeature.IsSelected)
                searchArea = TestCaseSearchAreaEnum.Feature;
            else if (this.comboBoxItemSearchResult.IsSelected)
                searchArea = TestCaseSearchAreaEnum.Result;
            else if (this.comboBoxItemSearchErrorReason.IsSelected)
                searchArea = TestCaseSearchAreaEnum.ErrorReason;
            else if (this.comboBoxItemSearchRunTime.IsSelected)
                searchArea = TestCaseSearchAreaEnum.RunTime;
            else if (this.comboBoxItemSearchAll.IsSelected)
                searchArea = TestCaseSearchAreaEnum.All;

            this.SearchAndSelectTestCases(this.textBoxSearch.Text, searchArea, this.checkBoxSearchMatchCase.IsChecked == true);
        }

        private void TextBoxSearch_OnPreviewKeyDown(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.Enter:
                    this.ButtonSearchTestCase_OnClick(null, null);
                    this.textBoxSearch.Focus();
                    break;
            }
        }

        private void TextBoxSearch_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            if (string.IsNullOrEmpty(this.textBoxSearch.Text)) return;

            TestCaseSearchAreaEnum searchArea = TestCaseSearchAreaEnum.TestCaseName;

            if (this.comboBoxItemSearchTestCase.IsSelected)
                searchArea = TestCaseSearchAreaEnum.TestCaseName;
            else if (this.comboBoxItemSearchSubarea.IsSelected)
                searchArea = TestCaseSearchAreaEnum.Subarea;
            else if (this.comboBoxItemSearchFeature.IsSelected)
                searchArea = TestCaseSearchAreaEnum.Feature;
            else if (this.comboBoxItemSearchResult.IsSelected)
                searchArea = TestCaseSearchAreaEnum.Result;
            else if (this.comboBoxItemSearchErrorReason.IsSelected)
                searchArea = TestCaseSearchAreaEnum.ErrorReason;
            else if (this.comboBoxItemSearchRunTime.IsSelected)
                searchArea = TestCaseSearchAreaEnum.RunTime;
            else if (this.comboBoxItemSearchAll.IsSelected)
                searchArea = TestCaseSearchAreaEnum.All;

            this.textBoxSearch.Background = this.SearchTextFromTestCases(this.textBoxSearch.Text, searchArea, this.checkBoxSearchMatchCase.IsChecked == true)
                                                ? (Brush)Brushes.White
                                                : this.errorBackground;
        }

        private void ComboBoxSearchArea_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            this.TextBoxSearch_OnTextChanged(null, null);
        }

        private void CheckBoxSearchMatchCase_OnCheckedChanged(object sender, RoutedEventArgs e)
        {
            this.TextBoxSearch_OnTextChanged(null, null);
        }

        private void NumericTextBoxRepeat_OnPreviewKeyDown(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.Enter:
                    GuiUtilities.PerformClick(this.buttonApplyChangesToTimedRun);
                    this.numericTextBoxRepeat.Focus();
                    break;
            }
        }
    }
}
