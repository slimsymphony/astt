// -----------------------------------------------------------------------
// <copyright file="ChartConverters.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Converters
{
    using System;
    using System.Collections.Generic;
    using System.Globalization;
    using System.Linq;
    using System.Text;
    using System.Windows.Controls.DataVisualization;
    using System.Windows.Data;
    using System.Windows.Markup;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class TestCaseResultToPieChartColorConverter : MarkupExtension, IValueConverter
    {
        private static TestCaseResultToPieChartColorConverter converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new TestCaseResultToPieChartColorConverter());
        }

        #region IValueConverter Members

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            ResourceDictionaryCollection colorsList = parameter as ResourceDictionaryCollection;

            if (colorsList == null) return null;

            switch (value.ToString().ToLower())
            {
                case "passed":
                    return colorsList[0]["Background"];
                case "failed":
                    return colorsList[1]["Background"];
                case "error":
                    return colorsList[2]["Background"];
                case "no result":
                    return colorsList[3]["Background"];
            }

            return null;
        }

        /// <summary>
        /// Converts a value back.
        /// </summary>
        /// <param name="value">The value that is produced by the binding target.</param>
        /// <param name="targetType">The type to convert to.</param>
        /// <param name="parameter">The converter parameter to use.</param>
        /// <param name="culture">The culture to use in the converter.</param>
        /// <returns>
        /// A converted value. If the method returns null, the valid null value is used.
        /// </returns>
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}
