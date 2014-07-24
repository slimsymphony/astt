using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    public class ConnectorStateToVisibilityConverter : MarkupExtension, IValueConverter
    {
        private static ConnectorStateToVisibilityConverter _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new ConnectorStateToVisibilityConverter();
            }
            return _converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if ((int)value == (int)Marble.Communication.ConnectorState.Idle || (int)value == (int)Marble.Communication.ConnectorState.FrameworkReady)
                return System.Windows.Visibility.Visible;
            
            return System.Windows.Visibility.Collapsed;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
