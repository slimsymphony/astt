using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    class ConnectorConnectionsToImageConverter : MarkupExtension, IValueConverter
    {
        private static ConnectorConnectionsToImageConverter _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new ConnectorConnectionsToImageConverter();
            }
            return _converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (value == null)
                return "/MarbleLibrary;component/Images/connection.missing.icon2.32x32.png";

            if ((int)((Communication.ProductInfo)value).ProductPresent > 0)
                return "/MarbleLibrary;component/Images/connection.icon2.32x32.png";

            return "/MarbleLibrary;component/Images/connection.missing.icon2.32x32.png";
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
