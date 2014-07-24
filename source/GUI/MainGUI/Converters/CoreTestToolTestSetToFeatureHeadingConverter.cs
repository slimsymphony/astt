using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    /// <summary>
    /// Class that converts a Core Test Tool test set flag to a feature heading.
    /// </summary>
    public class CoreTestToolTestSetToFeatureHeadingConverter : MarkupExtension, IValueConverter
    {
        private static CoreTestToolTestSetToFeatureHeadingConverter _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new CoreTestToolTestSetToFeatureHeadingConverter();
            }
            return _converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            string header;

            if ((bool)value)
                header = "ID";
            else
                header = "Feature";

            return header;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
