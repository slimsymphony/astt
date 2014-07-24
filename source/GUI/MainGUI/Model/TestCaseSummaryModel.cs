// -----------------------------------------------------------------------
// <copyright file="TestCaseSummaryModel.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Model
{
    using System;
    using System.Collections.Generic;
    using System.Collections.ObjectModel;
    using System.ComponentModel;
    using System.Linq;
    using System.Text;

    using Marble.Utilities;

    public enum SummaryMode
    {
        SingleTestCase = 0,
        MultipleTestCases = 1,
        AllTestCasesInTestSet = 2,
        AllTestRuns = 3,
    }

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class TestCaseSummaryModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="TestCaseSummaryModel"/> class.
        /// </summary>
        /// <param name="testCaseList">
        /// The test case list.
        /// </param>
        /// <param name="summaryMode">
        /// The summary mode.
        /// </param>
        public TestCaseSummaryModel(List<TestCase> testCaseList, SummaryMode summaryMode)
        {
            if (testCaseList == null)
                testCaseList = new List<TestCase>();

            this.TestCases = new ObservableCollectionAdv<TestCase>(testCaseList);
            this.SummaryMode = summaryMode;
        }

        private ObservableCollectionAdv<TestCase> testCases;

        /// <summary>
        /// Gets or sets the test cases.
        /// </summary>
        public ObservableCollectionAdv<TestCase> TestCases
        {
            get { return this.testCases; }
            set
            {
                this.testCases = value;
                this.RefreshTestCaseSummaryModelProperties();
            }
        }

        /// <summary>
        /// Gets the child test cases.
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">
        /// </exception>
        public ObservableCollectionAdv<TestCase> ChildTestCases
        {
            get
            {
                if (this.TestCases == null) return null;
                if (this.TestCases.Count < 1) return null;

                switch (SummaryMode)
                {
                    case SummaryMode.SingleTestCase:
                        return this.TestCases[0].Children;
                    case SummaryMode.MultipleTestCases:
                    case SummaryMode.AllTestCasesInTestSet:
                        return this.TestCases;
                    case SummaryMode.AllTestRuns:
                        ObservableCollectionAdv<TestCase> allTestRuns = new ObservableCollectionAdv<TestCase>();

                        foreach (TestCase testCase in this.TestCases)
                        {
                            if (testCase.Children.Count == 0 && testCase.Level == 1)
                                allTestRuns.Insert(allTestRuns.Count, testCase);
                            else
                                allTestRuns.InsertRange(allTestRuns.Count, testCase.Children);
                        }

                        return allTestRuns;
                    default:
                        throw new ArgumentOutOfRangeException();
                }
            }
        }

        /// <summary>
        /// Gets the result.
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">
        /// </exception>
        public string Result
        {
            get
            {
                if (this.TestCases == null) return null;
                if (this.TestCases.Count < 1) return null;

                switch (SummaryMode)
                {
                    case SummaryMode.SingleTestCase:
                        return this.TestCases[0].Result.Result;
                    case SummaryMode.MultipleTestCases:
                    case SummaryMode.AllTestCasesInTestSet:
                    case SummaryMode.AllTestRuns:
                        return "No Result";
                    default:
                        throw new ArgumentOutOfRangeException();
                }
            }
        }

        private SummaryMode summaryMode;

        /// <summary>
        /// Gets or sets the summary mode.
        /// </summary>
        public SummaryMode SummaryMode
        {
            get
            {
                return this.summaryMode;
            }
            set
            {
                this.summaryMode = value;
                this.OnPropertyChanged("SummaryMode");
                this.OnPropertyChanged("ChildTestCases");
                this.OnPropertyChanged("Result");
                this.OnPropertyChanged("SummaryTitle");
                this.OnPropertyChanged("ListTitle");
            }
        }

        /// <summary>
        /// Gets the passed result count.
        /// </summary>
        public int PassedResultCount { get
        {
            var childTestCases = this.ChildTestCases;
            if (childTestCases != null)
            {
                return childTestCases.Count(testCase => testCase.Result.Result == "Passed");
            }

            return 0;
        }
        }

        /// <summary>
        /// Gets the failed result count.
        /// </summary>
        public int FailedResultCount { get { return this.ChildTestCases == null ? 0 : this.ChildTestCases.Count(testCase => testCase.Result.Result == "Failed"); } }

        /// <summary>
        /// Gets the error result count.
        /// </summary>
        public int ErrorResultCount { get { return this.ChildTestCases == null ? 0 : this.ChildTestCases.Count(testCase => testCase.Result.Result == "Error"); } }

        /// <summary>
        /// Gets the no result result count.
        /// </summary>
        public int NoResultResultCount { get { return this.ChildTestCases == null ? 0 : this.ChildTestCases.Count(testCase => testCase.Result.Result == "No Result"); } }

        /// <summary>
        /// Gets the not avalaible result count.
        /// </summary>
        //public int NotAvailableResultCount { get { return this.ChildTestCases == null ? 0 : this.ChildTestCases.Count(testCase => testCase.Result.Result == "N/A"); } }

        /// <summary>
        /// Gets crash result count.
        /// </summary>
        public int CrashResultCount { get { return this.ChildTestCases == null ? 0 : this.ChildTestCases.Count(testCase => testCase.Result.HasCrashOrReset); } }

        /// <summary>
        /// Gets the total result count.
        /// </summary>
        public int TotalResultCount { get { return this.ChildTestCases == null ? 0 : this.ChildTestCases.Count; } }

        //public DateTime TestSetStartDateTime { get { return li } }


        /// <summary>
        /// Gets the result count collection.
        /// </summary>
        public Collection<TestCaseChartDataModel> ResultCountCollection
        {
            get
            {
                return new Collection<TestCaseChartDataModel>()
                    {
                        new TestCaseChartDataModel("Passed", this.PassedResultCount),
                        new TestCaseChartDataModel("Failed", this.FailedResultCount),
                        new TestCaseChartDataModel("No Result", this.NoResultResultCount)
                    };
            }
        }

        /// <summary>
        /// Gets the summary title.
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">
        /// </exception>
        public string SummaryTitle
        {
            get
            {
                switch (SummaryMode)
                {
                    case SummaryMode.SingleTestCase:
                        return "Test Case Results Summary";
                    case SummaryMode.MultipleTestCases:
                        return "Selected Test Cases Summary";
                    case SummaryMode.AllTestCasesInTestSet:
                        return "Test Set Summary";
                    case SummaryMode.AllTestRuns:
                        return "All Test Runs Summary";
                    default:
                        throw new ArgumentOutOfRangeException();
                }
            }
        }

        /// <summary>
        /// Gets the list title.
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">
        /// </exception>
        public string ListTitle
        {
            get
            {
                switch (SummaryMode)
                {
                    case SummaryMode.SingleTestCase:
                        return "Test Runs";
                    case SummaryMode.MultipleTestCases:
                    case SummaryMode.AllTestCasesInTestSet:
                        return "Test Cases";
                    case SummaryMode.AllTestRuns:
                        return "All Test Runs";
                    default:
                        throw new ArgumentOutOfRangeException();
                }
            }
        }

        /// <summary>
        /// Refreshes test case summary model properties.
        /// </summary>
        public void RefreshTestCaseSummaryModelProperties()
        {
            this.OnPropertyChanged("TestCases");
            this.OnPropertyChanged("SummaryMode");
            this.OnPropertyChanged("ChildTestCases");
            this.OnPropertyChanged("Result");
            this.OnPropertyChanged("SummaryTitle");
            this.OnPropertyChanged("ListTitle");

            this.OnPropertyChanged("PassedResultCount");
            this.OnPropertyChanged("FailedResultCount");
            this.OnPropertyChanged("ErrorResultCount");
            this.OnPropertyChanged("NoResultResultCount");
            this.OnPropertyChanged("NotAvalaibleResultCount");
            this.OnPropertyChanged("TotalResultCount");

            this.OnPropertyChanged("ResultCountCollection");
        }

        /// <summary>
        /// Updates test cases.
        /// </summary>
        /// <param name="testCaseList"></param>
        public void UpdateTestCases(List<TestCase> testCaseList)
        {
            if (testCaseList == null)
                testCaseList = new List<TestCase>();

            this.TestCases = new ObservableCollectionAdv<TestCase>(testCaseList);

            this.RefreshTestCaseSummaryModelProperties();
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
    }
}
