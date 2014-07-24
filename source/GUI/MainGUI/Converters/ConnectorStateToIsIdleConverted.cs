using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    public class ConnectorStateToIsIdleConverter : MarkupExtension, IValueConverter
    {
        private static ConnectorStateToIsIdleConverter _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new ConnectorStateToIsIdleConverter();
            }
            return _converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if ((int)value == (int)Marble.Communication.ConnectorState.Idle || (int)value == (int)Marble.Communication.ConnectorState.FrameworkReady)
                return true;

            return false;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
