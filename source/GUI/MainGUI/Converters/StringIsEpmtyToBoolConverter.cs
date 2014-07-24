using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    /// <summary>
    /// Returns true if given value is null or its ToString() returns empty otherwise false.
    /// </summary>
    public class StringIsEmptyToBoolConverter : MarkupExtension, IValueConverter
    {
        private static StringIsEmptyToBoolConverter _converter;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _converter ?? (_converter = new StringIsEmptyToBoolConverter());
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (value != null && value.ToString() != String.Empty)
                return false;
            return true;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
