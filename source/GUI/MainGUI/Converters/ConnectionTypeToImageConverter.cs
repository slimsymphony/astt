using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    /// <summary>
    /// Class for converting test report result to image file path.
    /// </summary>
    public class ConnectionTypeToImageConverter : MarkupExtension, IValueConverter
    {
        private static ConnectionTypeToImageConverter converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new ConnectionTypeToImageConverter());
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (string.IsNullOrEmpty(value.ToString())) return "/MarbleLibrary;component/Images/empty.label.32x16.png";

            if (value.ToString().ToLower().StartsWith("usb"))
                return "/MarbleLibrary;component/Images/usb.label.32x16.png";
            if (value.ToString().ToLower().Equals("tcp"))
                return "/MarbleLibrary;component/Images/tcp.label.32x16.png";

            return "/MarbleLibrary;component/Images/empty.label.32x16.png";
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
