// -----------------------------------------------------------------------
// <copyright file="TestCaseUtilities.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Utilities
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Globalization;
    using System.Linq;
    using System.Text;
    using System.Windows;

    using Marble.Model;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class TestCaseUtilities
    {
        /// <summary>
        /// The create test case results text from test case list.
        /// </summary>
        /// <param name="testCaseList">
        /// The test case list.
        /// </param>
        public static string CreateExcelCompatibleTestCaseResultsTextFromTestCaseList(List<TestCase> testCaseList)
        {
            StringBuilder stringBuilder = new StringBuilder();
            int passedCaseCount = 0, failedCaseCount = 0, errorCaseCount = 0, noResultCaseCount = 0;

            foreach (TestCase selectedTestCase in testCaseList)
            {
                switch (selectedTestCase.Result.Result.ToLower())
                {
                    case "passed":
                        passedCaseCount++;
                        break;
                    case "failed":
                        failedCaseCount++;
                        break;
                    case "error":
                        errorCaseCount++;
                        break;
                    case "no result":
                        noResultCaseCount++;
                        break;
                }

                stringBuilder.Append(
                    selectedTestCase.Subarea + "\t" + selectedTestCase.Feature + "\t" + selectedTestCase.Name + "\t"
                    + selectedTestCase.Result.Result + "\n");
            }

            stringBuilder.Insert(0, "Subarea" + "\t" + "Feature" + "\t" + "Name" + "\t" + "Result" + "\n");
            stringBuilder.Insert(0, "Passed\t" + passedCaseCount + "\nFailed\t" + failedCaseCount + "\nError\t" + errorCaseCount + "\nNo Result\t" + noResultCaseCount + "\n\n");

            return stringBuilder.ToString();
        }

        public static void CopyExcelCompatibleTestCaseResultsToClipboard(List<TestCase> testCaseList)
        {
            ////Clipboard.SetText(TestCaseUtilities.CreateExcelCompatibleTestCaseResultsTextFromTestCaseList(testCaseList));
            Clipboard.SetDataObject(TestCaseUtilities.CreateExcelCompatibleTestCaseResultsTextFromTestCaseList(testCaseList));
        }

        /// <summary>
        /// Creates Excel compatible test run summary result from test cases.
        /// </summary>
        /// <param name="testCases">The test cases.</param>
        /// <returns>The <see cref="string"/>.</returns>
        public static string CreateExcelCompatibleTestRunSummaryResultFromTestCases(IEnumerable testCases)
        {
            if (testCases == null) return string.Empty;

            StringBuilder stringBuilder = new StringBuilder();

            stringBuilder.Append(
                "Index / Iteration\t" + "Result\t" + "Runtime\t" + "Test Case\t" + "Error Reason\n");

            foreach (TestCase testCase in testCases)
            {
                if (testCase == null) continue;

                stringBuilder.Append(
                    testCase.Result.Index + "\t" +
                    testCase.Result.Result + "\t" +
                    testCase.Result.RunTime.ToString(CultureInfo.InvariantCulture) + "\t" +
                    testCase.Name + "\t" +
                    testCase.Result.ErrorReason.Replace("\n", " ").Replace("\r", "") + "\n");
            }

            return stringBuilder.ToString();
        }

        public static void CopyExcelCompatibleTestRunSummaryResultToClipboard(IEnumerable testCases)
        {
            Clipboard.SetDataObject(TestCaseUtilities.CreateExcelCompatibleTestRunSummaryResultFromTestCases(testCases));
        }

        public static string CreateExcelCompatibleTestSetTestRunResultSummary(TestCaseSummaryModel testCaseSummaryModel)
        {
            if (testCaseSummaryModel == null) return string.Empty;

            StringBuilder stringBuilder = new StringBuilder();

            stringBuilder.Append("Result Type\t" + "Count\n");

            stringBuilder.Append("Passed\t" + testCaseSummaryModel.PassedResultCount + "\n");
            stringBuilder.Append("Failed\t" + testCaseSummaryModel.FailedResultCount + "\n");
            stringBuilder.Append("No Result\t" + testCaseSummaryModel.NoResultResultCount + "\n");
            stringBuilder.Append("Crash or Reset\t" + testCaseSummaryModel.CrashResultCount + "\n");
            stringBuilder.Append("Total\t" + testCaseSummaryModel.TotalResultCount + "\n");

            return stringBuilder.ToString();
        }

        ////public static TestResult GetEarliestTestResultByDateTime(IEnumerable testCases)
        ////{
        ////    if (testCases == null) return null;

        ////    DateTime earliestDateTime = testCases.AsQueryable().agg
        ////}
    }
}
