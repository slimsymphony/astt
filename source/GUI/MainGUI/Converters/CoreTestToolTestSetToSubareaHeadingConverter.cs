using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    /// <summary>
    /// Class that converts a Core Test Tool test set flag to a sub-area heading.
    /// </summary>
    public class CoreTestToolTestSetToSubareaHeadingConverter : MarkupExtension, IValueConverter
    {
        private static CoreTestToolTestSetToSubareaHeadingConverter _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new CoreTestToolTestSetToSubareaHeadingConverter();
            }
            return _converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            string header;

            if ((bool)value)
                header = "CTT Test Application File";
            else
                header = "Subarea";

            return header;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
