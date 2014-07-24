using System;
using System.Windows.Media;

namespace Granite.Converters
{
    /// <summary>
    /// Converts connection state to a color brush.
    /// 2 = Green, 1 = Orange, 0 (and all other) = Red
    /// </summary>
    [System.Windows.Data.ValueConversion(typeof(int), typeof(Brush))]
    public class ConnectionColorConverter : System.Windows.Data.IValueConverter
    {
        readonly Brush [] brushes = {Brushes.Red, Brushes.Orange, Brushes.Green};

        // convert from int to Brush
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if ((int)value >= 0 && (int)value < brushes.Length)
                return brushes[(int)value];
            return brushes[0];
        }

        // convert from Brush to int
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            for (int ii = 0; ii < brushes.Length; ii++)
            {
                if (brushes[ii] == value)
                    return ii;
            }
            return -1;
        }
    }
}