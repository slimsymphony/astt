using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MarbleLibrary.Converters
{
    using System.Windows.Data;
    using System.Windows.Markup;

    /// <summary>
    /// Converts DateTime to Visibility.Visible when DateTime Ticks are higher than 0. Otherwise return Visibility.Hidden.
    /// </summary>
    public class DateTimeToVisibilityHiddenConverter : MarkupExtension, IValueConverter
    {
        private static DateTimeToVisibilityHiddenConverter _converter;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _converter ?? (_converter = new DateTimeToVisibilityHiddenConverter());
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            DateTime dateTime;

            if (DateTime.TryParse(value.ToString(), out dateTime) && dateTime.Ticks > 0) return System.Windows.Visibility.Visible;
            return System.Windows.Visibility.Hidden;
        }

        public object ConvertBack(
            object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
