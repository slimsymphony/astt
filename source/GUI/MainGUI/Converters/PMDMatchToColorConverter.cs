using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Data;
using System.Windows.Markup;
using System.Windows.Media;

namespace Marble.Converters
{
    class PMDMatchToColorConverter : MarkupExtension, IValueConverter
    {
        private static PMDMatchToColorConverter _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new PMDMatchToColorConverter();
            }
            return _converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if ((Communication.EnumVersionMatch)value == Communication.EnumVersionMatch.ProductMatch)
                return Brushes.Blue;
            if ((Communication.EnumVersionMatch)value == Communication.EnumVersionMatch.VersionMatch)
                return Brushes.Green;
            return Brushes.Red;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
