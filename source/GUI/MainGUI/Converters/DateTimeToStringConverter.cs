using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Marble.Converters
{
    /// <summary>
    /// Converts DateTime to a string representation and vice versa.
    /// If given date is today only time component is returned.
    /// In case of DateTime.MinValue string.Empty is returned.
    /// </summary>
    /// 
    //[System.Windows.Data.ValueConversion(typeof(Communication.ConnectorState), typeof(String))]
    public class DateTimeToStringConverter : System.Windows.Markup.MarkupExtension, System.Windows.Data.IValueConverter
    {
        private static DateTimeToStringConverter _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
                _converter = new DateTimeToStringConverter();

            return _converter;
        }

        // Convert from DateTime to string
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            DateTime input = (DateTime) value;
            if (input.Date == DateTime.Now.Date)
                return string.Format("{0:HH:mm:ss}", input);

            ////return input == DateTime.MinValue ? string.Empty : input.ToString(culture);

            return input == DateTime.MinValue ? string.Empty : input.ToString("yyyy.MM.dd HH:mm:ss");
        }

        // Convert from string to DateTime
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            DateTime input;
            return DateTime.TryParse((string) value, out input) ? input : DateTime.MinValue;
        }
    }
}