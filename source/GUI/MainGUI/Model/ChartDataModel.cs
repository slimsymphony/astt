// -----------------------------------------------------------------------
// <copyright file="ChartDataModel.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Model
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class TestCaseChartDataModel
    {
        public TestCaseChartDataModel(string name = "", int statusCount = 0, string toolTipText = "")
        {
            this.Name = name;
            this.StatusCount = statusCount;
            this.ToolTipText = string.IsNullOrEmpty(toolTipText) ? name + "\n" + statusCount : toolTipText;
        }

        public string Name { get; set; }

        public int StatusCount { get; set; }

        public string ToolTipText { get; set; }
    }
}
