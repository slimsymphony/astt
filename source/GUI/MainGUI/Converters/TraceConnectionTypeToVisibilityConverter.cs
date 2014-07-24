using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    public class TraceConnectionTypeToVisibilityConverter : MarkupExtension, IValueConverter
    {
        private static TraceConnectionTypeToVisibilityConverter _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _converter ?? (_converter = new TraceConnectionTypeToVisibilityConverter());
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (App.ViewModel.IsMemoryLeakTestingEnabledForTestrun && value.ToString().ToUpper() != "FIDO" && value.ToString().ToUpper() != "MUSTI")
                return System.Windows.Visibility.Collapsed;    

            return System.Windows.Visibility.Visible;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
