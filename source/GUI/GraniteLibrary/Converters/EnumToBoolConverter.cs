namespace MarbleLibrary.Converters
{
    using System;
    using System.Windows;
    using System.Windows.Data;
    using System.Windows.Markup;

    public class EnumToBoolConverter : MarkupExtension, IValueConverter
    {
        private static EnumToBoolConverter _converter;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _converter ?? (_converter = new EnumToBoolConverter());
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            string parameterString = parameter as string;

            if (parameterString == null)
                return DependencyProperty.UnsetValue;

            if (Enum.IsDefined(value.GetType(), value) == false)
                return DependencyProperty.UnsetValue;

            object parameterValue = Enum.Parse(value.GetType(), parameterString);

            return parameterValue.Equals(value);
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            string parameterString = parameter as string;

            return parameterString == null ? DependencyProperty.UnsetValue : Enum.Parse(targetType, parameterString);
        }
    }

    public class EnumToBoolWithEnumParameterConverter : MarkupExtension, IValueConverter
    {
        private static EnumToBoolWithEnumParameterConverter _converter;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _converter ?? (_converter = new EnumToBoolWithEnumParameterConverter());
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return value.Equals(parameter);
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return value.Equals(true) ? parameter : Binding.DoNothing;
        }
    }
}
