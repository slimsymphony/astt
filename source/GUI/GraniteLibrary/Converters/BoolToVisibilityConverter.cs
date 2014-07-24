namespace MarbleLibrary.Converters
{
    using System;
    using System.Windows.Data;
    using System.Windows.Markup;

    /// <summary>
    /// Converts bool true to Visibility.Visible and bool false to Visibility.Hidden.
    /// </summary>
    public class BoolToVisibilityHiddenConverter : MarkupExtension, IValueConverter
    {
        private static BoolToVisibilityHiddenConverter _converter;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _converter ?? (_converter = new BoolToVisibilityHiddenConverter());
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if ((bool)value)
                return System.Windows.Visibility.Visible;
            return System.Windows.Visibility.Hidden;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }

    /// <summary>
    /// Converts bool true to Visibility.Visible and bool false to Visibility.Collapsed.
    /// </summary>
    public class BoolToVisibilityCollapsedConverter : MarkupExtension, IValueConverter
    {
        private static BoolToVisibilityCollapsedConverter _converter;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _converter ?? (_converter = new BoolToVisibilityCollapsedConverter());
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if ((bool)value)
                return System.Windows.Visibility.Visible;
            return System.Windows.Visibility.Collapsed;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
