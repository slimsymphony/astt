using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    /// <summary>
    /// Class for converting test report result to image file path.
    /// </summary>
    public class PmdMatchLevelToTooltipConverter : MarkupExtension, IValueConverter
    {
        private static PmdMatchLevelToTooltipConverter converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new PmdMatchLevelToTooltipConverter());
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (string.IsNullOrEmpty(value.ToString())) return null;

            switch ((Communication.EnumVersionMatch)value)
            {
                case Communication.EnumVersionMatch.ProductMatch:
                    return "PMD file matches the product type (not version).";
                case Communication.EnumVersionMatch.VersionMatch:
                    return "PMD file matches the product version.";
            }

            return "PMD file doesn't match the product (or the match can't be verified).";
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
