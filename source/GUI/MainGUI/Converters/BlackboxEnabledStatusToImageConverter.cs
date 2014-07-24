using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    public class BlackboxEnabledStatusToImageConverter : MarkupExtension, IValueConverter
    {
        private static BlackboxEnabledStatusToImageConverter _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new BlackboxEnabledStatusToImageConverter();
            }
            return _converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if ((bool)value)
                return "/MarbleLibrary;component/Images/toggle_on.png";

            return "/MarbleLibrary;component/Images/toggle_off.png";
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
