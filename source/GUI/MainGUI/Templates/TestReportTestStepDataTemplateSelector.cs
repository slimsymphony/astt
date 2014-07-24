// -----------------------------------------------------------------------
// <copyright file="TestReportTestStepDataTemplateSelector.cs" company="NOKIA">
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

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class TestReportTestStepDataTemplateSelector : DataTemplateSelector
    {
        public DataTemplate GenericTestStepTemplate { get; set; }

        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            return this.GenericTestStepTemplate;
        }
    }
}
