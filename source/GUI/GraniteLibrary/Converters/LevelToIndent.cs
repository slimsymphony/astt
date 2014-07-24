namespace MarbleLibrary.Converters
{
    using System;

    public class LevelToIndent : System.Windows.Markup.MarkupExtension, System.Windows.Data.IValueConverter
    {
        private const double IndentSize = 12.0;

        private static LevelToIndent _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new LevelToIndent();
            }
            return _converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return new System.Windows.Thickness((int)value * IndentSize, 0, 0, 0);
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
