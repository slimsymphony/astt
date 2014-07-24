using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    /// <summary>
    /// Class for converting test report result to image file path.
    /// </summary>
    public class TestReportResultToImageConverter : MarkupExtension, IValueConverter
    {
        private static TestReportResultToImageConverter converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new TestReportResultToImageConverter());
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (value == null)
                return null;
            if (string.IsNullOrEmpty(value.ToString())) return null;

            switch (value.ToString().ToLower())
            {
                case "no result":
                    return "/MarbleLibrary;component/Images/no.resolution.circle.icon.16x16.png";
                case "error":
                    return "/MarbleLibrary;component/Images/error.icon.16x16.png";
                case "failed":
                case "failed in teardown":
                case "failed in setup":
                    return "/MarbleLibrary;component/Images/failed.circle.icon.16x16.png";
                case "passed":
                    return "/MarbleLibrary;component/Images/passed.circle.icon.16x16.png";
            }

            return null;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
