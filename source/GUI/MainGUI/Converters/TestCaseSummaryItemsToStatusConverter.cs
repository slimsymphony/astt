using System;
using System.Windows.Data;
using System.Windows.Markup;
using System.Windows.Media;

namespace Marble.Converters
{
    using System.Collections.Generic;
    using System.Collections.ObjectModel;
    using System.Linq;

    using Marble.Model;

    class TestCaseSummaryItemsToStatusConverter : MarkupExtension, IValueConverter
    {
        /// <summary>
        /// The _converter.
        /// </summary>
        private static TestCaseSummaryItemsToStatusConverter _converter = null;

        /// <summary>
        /// The provide value.
        /// </summary>
        /// <param name="serviceProvider">The service provider.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _converter ?? (_converter = new TestCaseSummaryItemsToStatusConverter());
        }

        /// <summary>
        /// The convert.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="targetType">The target type.</param>
        /// <param name="parameter">The parameter.</param>
        /// <param name="culture">The culture.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (value == null) return null;

            var items = value as IList<object>;

            if (items == null) return null;

            if (items.Any(tc => ((TestCase)tc).Result.Result.ToLower() == "error"))
                return "Error";
            if (items.Any(tc => ((TestCase)tc).Result.Result.ToLower().StartsWith("failed")))
                return "Failed";
            if (items.Any(tc => ((TestCase)tc).Result.Result.ToLower() == "no result"))
                return "No Result";
            if (items.Any(tc => ((TestCase)tc).Result.Result.ToLower() == "passed"))
                return "Passed";
            
            return "N/A";
        }

        /// <summary>
        /// The convert back.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="targetType">The target type.</param>
        /// <param name="parameter">The parameter.</param>
        /// <param name="culture">The culture.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }

    class TestCaseSummaryItemsToPassedCountConverter : MarkupExtension, IValueConverter
    {
        /// <summary>
        /// The _converter.
        /// </summary>
        private static TestCaseSummaryItemsToPassedCountConverter _converter = null;

        /// <summary>
        /// The provide value.
        /// </summary>
        /// <param name="serviceProvider">The service provider.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _converter ?? (_converter = new TestCaseSummaryItemsToPassedCountConverter());
        }

        /// <summary>
        /// The convert.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="targetType">The target type.</param>
        /// <param name="parameter">The parameter.</param>
        /// <param name="culture">The culture.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (value == null) return 0;

            var items = value as IList<object>;

            if (items == null) return 0;

            int passedCount = items.Cast<TestCase>().Count(item => item.Result.Result.ToLower() == "passed");

            return passedCount;
        }

        /// <summary>
        /// The convert back.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="targetType">The target type.</param>
        /// <param name="parameter">The parameter.</param>
        /// <param name="culture">The culture.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }

    class TestCaseSummaryItemsToFailedCountConverter : MarkupExtension, IValueConverter
    {
        /// <summary>
        /// The _converter.
        /// </summary>
        private static TestCaseSummaryItemsToFailedCountConverter _converter = null;

        /// <summary>
        /// The provide value.
        /// </summary>
        /// <param name="serviceProvider">The service provider.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _converter ?? (_converter = new TestCaseSummaryItemsToFailedCountConverter());
        }

        /// <summary>
        /// The convert.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="targetType">The target type.</param>
        /// <param name="parameter">The parameter.</param>
        /// <param name="culture">The culture.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (value == null) return 0;

            var items = value as IList<object>;

            if (items == null) return 0;

            int failedCount = items.Cast<TestCase>().Count(item => item.Result.Result.ToLower().StartsWith("failed"));

            return failedCount;
        }

        /// <summary>
        /// The convert back.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="targetType">The target type.</param>
        /// <param name="parameter">The parameter.</param>
        /// <param name="culture">The culture.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }

    class TestCaseSummaryItemsToNoResultCountConverter : MarkupExtension, IValueConverter
    {
        /// <summary>
        /// The _converter.
        /// </summary>
        private static TestCaseSummaryItemsToNoResultCountConverter _converter = null;

        /// <summary>
        /// The provide value.
        /// </summary>
        /// <param name="serviceProvider">The service provider.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _converter ?? (_converter = new TestCaseSummaryItemsToNoResultCountConverter());
        }

        /// <summary>
        /// The convert.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="targetType">The target type.</param>
        /// <param name="parameter">The parameter.</param>
        /// <param name="culture">The culture.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (value == null) return 0;

            var items = value as IList<object>;

            if (items == null) return 0;

            int noResultCount = items.Cast<TestCase>().Count(item => item.Result.Result.ToLower() == "no result");

            return noResultCount;
        }

        /// <summary>
        /// The convert back.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="targetType">The target type.</param>
        /// <param name="parameter">The parameter.</param>
        /// <param name="culture">The culture.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }

    class TestCaseSummaryItemsToNotAvailableCountConverter : MarkupExtension, IValueConverter
    {
        /// <summary>
        /// The _converter.
        /// </summary>
        private static TestCaseSummaryItemsToNotAvailableCountConverter _converter = null;

        /// <summary>
        /// The provide value.
        /// </summary>
        /// <param name="serviceProvider">The service provider.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _converter ?? (_converter = new TestCaseSummaryItemsToNotAvailableCountConverter());
        }

        /// <summary>
        /// The convert.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="targetType">The target type.</param>
        /// <param name="parameter">The parameter.</param>
        /// <param name="culture">The culture.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (value == null) return 0;

            var items = value as IList<object>;

            if (items == null) return 0;

            int passedCount = items.Cast<TestCase>().Count(
                item => item.Result.Result.ToLower() != "passed" &&
                        item.Result.Result.ToLower() != "failed" &&
                        item.Result.Result.ToLower() != "no result");

            return passedCount;
        }

        /// <summary>
        /// The convert back.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="targetType">The target type.</param>
        /// <param name="parameter">The parameter.</param>
        /// <param name="culture">The culture.</param>
        /// <returns>The <see cref="object"/>.</returns>
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
