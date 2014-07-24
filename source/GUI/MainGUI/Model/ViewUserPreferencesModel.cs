// -----------------------------------------------------------------------
// <copyright file="ViewUserPreferencesModel.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Model
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Linq;
    using System.Text;
    using System.Windows;

    using Marble.Views;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// The UcBaseUserPreferences interface.
    /// </summary>
    public interface IUcBaseUserPreferences
    {
        /// <summary>
        /// The store uc base user preferences.
        /// </summary>
        /// <param name="ucBase">The uc base.</param>
        void StoreUcBaseUserPreferences(UcBase ucBase);

        /// <summary>
        /// The restore uc base user preferences.
        /// </summary>
        /// <param name="ucBase">The uc base.</param>
        void RestoreUcBaseUserPreferences(UcBase ucBase);
    }

    /// <summary>
    /// The test report view user preferences.
    /// </summary>
    public class TestReportViewUserPreferences : IUcBaseUserPreferences
    {
        /// <summary>
        /// Gets or sets the default test case summary preferences.
        /// </summary>
        public TestReportTestCaseSummaryViewUserPreferences DefaultTestCaseSummaryPreferences { get; set; }

        /// <summary>
        /// Gets or sets the rsa test case summary preferences.
        /// </summary>
        public TestReportTestCaseSummaryViewUserPreferences RsaTestCaseSummaryPreferences { get; set; }

        /// <summary>
        /// Gets or sets the mtbf test case summary preferences.
        /// </summary>
        public TestReportTestCaseSummaryViewUserPreferences MtbfTestCaseSummaryPreferences { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="TestReportViewUserPreferences"/> class.
        /// </summary>
        public TestReportViewUserPreferences()
        {
            // Default view settings for the Default view mode.
            this.DefaultTestCaseSummaryPreferences = new TestReportTestCaseSummaryViewUserPreferences()
                {
                    IsPassedResultsDisplayed = true,
                    IsFailedResultsDisplayed = true,
                    IsErrorResultsDisplayed = true,
                    IsNoResultResultsDisplayed = true,
                    IsCrashResultsDisplayed = true,
                    GroupingMode = TestReportTestCaseSummaryViewUserPreferences.TestReportSummaryGroupingMode.None
                };
            
            // Default view settings for the RSA view mode.
            this.RsaTestCaseSummaryPreferences = new TestReportTestCaseSummaryViewUserPreferences()
                {
                    IsPassedResultsDisplayed = true,
                    IsFailedResultsDisplayed = true,
                    IsErrorResultsDisplayed = true,
                    IsNoResultResultsDisplayed = true,
                    IsCrashResultsDisplayed = false,
                    GroupingMode = TestReportTestCaseSummaryViewUserPreferences.TestReportSummaryGroupingMode.RunIndex
                };

            // Default view settings for the MTBF view mode.
            this.MtbfTestCaseSummaryPreferences = new TestReportTestCaseSummaryViewUserPreferences();
        }

        /// <summary>
        /// The store uc base user preferences.
        /// </summary>
        /// <param name="ucBase">
        /// The uc base.
        /// </param>
        /// <exception cref="NotImplementedException">
        /// </exception>
        public void StoreUcBaseUserPreferences(UcBase ucBase)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// The restore uc base user preferences.
        /// </summary>
        /// <param name="ucBase">
        /// The uc base.
        /// </param>
        /// <exception cref="NotImplementedException">
        /// </exception>
        public void RestoreUcBaseUserPreferences(UcBase ucBase)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// The store user preferences.
        /// </summary>
        /// <param name="testReportView">
        /// The test report view.
        /// </param>
        public void StoreUserPreferences(TestReportView testReportView)
        {
            
        }
    }

    /// <summary>
    /// The test report test case summary view user preferences.
    /// </summary>
    public class TestReportTestCaseSummaryViewUserPreferences : IUcBaseUserPreferences
    {
        /// <summary>
        /// Gets or sets the test case summary height.
        /// </summary>
        public GridLength TestCaseSummaryHeight { get; set; }

        /// <summary>
        /// Gets or sets the test report height.
        /// </summary>
        public GridLength TestReportHeight { get; set; }

        /// <summary>
        /// Gets or sets the grouping mode.
        /// </summary>
        public TestReportSummaryGroupingMode GroupingMode { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether is passed results displayed.
        /// </summary>
        public bool IsPassedResultsDisplayed { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether is failed results displayed.
        /// </summary>
        public bool IsFailedResultsDisplayed { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether is error results displayed.
        /// </summary>
        public bool IsErrorResultsDisplayed { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether is no result results displayed.
        /// </summary>
        public bool IsNoResultResultsDisplayed { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether is not available results displayed.
        /// </summary>
        public bool IsNotAvailableResultsDisplayed { get; set; }

        public bool IsCrashResultsDisplayed { get; set; }

        /// <summary>
        /// Gets or sets the sort description.
        /// </summary>
        public SortDescription SortDescription { get; set; }

        /// <summary>
        /// The store uc base user preferences.
        /// </summary>
        /// <param name="ucBase">
        /// The uc base.
        /// </param>
        /// <exception cref="NotImplementedException">
        /// </exception>
        public void StoreUcBaseUserPreferences(UcBase ucBase)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// The restore uc base user preferences.
        /// </summary>
        /// <param name="ucBase">
        /// The uc base.
        /// </param>
        /// <exception cref="NotImplementedException">
        /// </exception>
        public void RestoreUcBaseUserPreferences(UcBase ucBase)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// The load test report test case summary view preferences.
        /// </summary>
        /// <param name="testCaseSummaryView">
        /// The test case summary view.
        /// </param>
        public void LoadTestReportTestCaseSummaryViewPreferences(TestReportTestCaseSummaryView testCaseSummaryView)
        {
            testCaseSummaryView.ApplyGrouping(this.GroupingMode);
            testCaseSummaryView.SortTestRuns(this.SortDescription);
        }

        /// <summary>
        /// The store test report test case summary view preferences.
        /// </summary>
        /// <param name="testCaseSummaryView">
        /// The test case summary view.
        /// </param>
        public void StoreTestReportTestCaseSummaryViewPreferences(TestReportTestCaseSummaryView testCaseSummaryView)
        {
            
        }

        /// <summary>
        /// The test report summary grouping mode.
        /// </summary>
        public enum TestReportSummaryGroupingMode
        {
            /// <summary>
            /// The none.
            /// </summary>
            None = 0,

            /// <summary>
            /// The result.
            /// </summary>
            Result = 1,

            /// <summary>
            /// The test case name.
            /// </summary>
            TestCaseName = 2,

            /// <summary>
            /// The run index.
            /// </summary>
            RunIndex = 3,
        }    
    }
}
