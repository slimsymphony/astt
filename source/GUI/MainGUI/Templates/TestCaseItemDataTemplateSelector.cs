// -----------------------------------------------------------------------
// <copyright file="TestCaseItemDataTemplateSelector.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Templates
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Windows;
    using System.Windows.Controls;

    using Marble.Model;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class TestCaseItemDataTemplateSelector : DataTemplateSelector
    {
        public DataTemplate GenericTestCaseItemTemplate { get; set; }

        public DataTemplate UnknownTestCaseItemTemplate { get; set; }

        public DataTemplate CommentTestCaseItemTemplate { get; set; }

        public DataTemplate DescriptionTestCaseItemTemplate { get; set; }
        
        public DataTemplate TestStepTestCaseItemTemplate { get; set; }

        public DataTemplate SummaryTestCaseItemTemplate { get; set; }

        public DataTemplate ErrorTestCaseItemTemplate { get; set; }

        public DataTemplate WarningTestCaseItemTemplate { get; set; }

        public DataTemplate VideoTestCaseItemTemplate { get; set; }

        public DataTemplate PerfTestStepTestCaseItemTemplate { get; set; }

        public DataTemplate BugReportTestCaseItemTemplate { get; set; }

        public DataTemplate TestCaseReportSummaryItemTemplate { get; set; }

        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            if (item == null || !(item is TestCaseReportItemModel)) return null;

            TestCaseReportItemModel testCaseReportItem = item as TestCaseReportItemModel;

            switch (testCaseReportItem.ItemType)
            {
                case TestCaseReportItemType.Unknown:
                    return this.GenericTestCaseItemTemplate;
                case TestCaseReportItemType.Comment:
                    return this.CommentTestCaseItemTemplate;
                case TestCaseReportItemType.Description:
                    return this.DescriptionTestCaseItemTemplate;
                case TestCaseReportItemType.TestStep:
                    return this.TestStepTestCaseItemTemplate;
                case TestCaseReportItemType.Summary:
                    return this.SummaryTestCaseItemTemplate;
                case TestCaseReportItemType.Error:
                    return this.ErrorTestCaseItemTemplate;
                case TestCaseReportItemType.Warning:
                    return this.WarningTestCaseItemTemplate;
                case TestCaseReportItemType.Videos:
                    return this.VideoTestCaseItemTemplate;
                case TestCaseReportItemType.PerfTestStep:
                    return this.PerfTestStepTestCaseItemTemplate;
                case TestCaseReportItemType.BugReport:
                    return this.BugReportTestCaseItemTemplate;
                case TestCaseReportItemType.TestCaseReportSummary:
                    return this.TestCaseReportSummaryItemTemplate;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        public DataTemplate SelectTemplate(string templateName)
        {
            switch (templateName)
            {
                case "Unknown":
                    return this.GenericTestCaseItemTemplate;
                case "Comment":
                    return this.CommentTestCaseItemTemplate;
                case "Description":
                    return this.DescriptionTestCaseItemTemplate;
                case "TestStep":
                    return this.TestStepTestCaseItemTemplate;
                case "Summary":
                    return this.SummaryTestCaseItemTemplate;
                case "Error":
                    return this.ErrorTestCaseItemTemplate;
                case "Warning":
                    return this.WarningTestCaseItemTemplate;
                case "Videos":
                    return this.VideoTestCaseItemTemplate;
                case "PerfTestStep":
                    return this.PerfTestStepTestCaseItemTemplate;
                case "BugReport":
                    return this.BugReportTestCaseItemTemplate;
                case "TestCaseReportSummary":
                    return this.TestCaseReportSummaryItemTemplate;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }
    }
}
