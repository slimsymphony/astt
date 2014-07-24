using System;
using System.Windows.Data;
using System.Windows.Markup;
using System.Windows.Media;

namespace Marble.Converters
{
    class StatusToColorConverter : MarkupExtension, IValueConverter
    {
        private static StatusToColorConverter _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new StatusToColorConverter();
            }
            return _converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (value == null)
                return Brushes.Black;

            string status = (string)value;

            if (status.Contains("Passed"))
                return Brushes.DarkGreen;
            else if (status.Contains("Failed") || status.Contains("Error"))
                return Brushes.Firebrick;
            else
                return Brushes.Blue;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
