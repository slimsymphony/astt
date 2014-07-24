using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    /// <summary>
    /// Class for converting test report result to image file path.
    /// </summary>
    public class PmdMatchLevelToImageConverter : MarkupExtension, IValueConverter
    {
        private static PmdMatchLevelToImageConverter converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new PmdMatchLevelToImageConverter());
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (string.IsNullOrEmpty(value.ToString())) return null;

            switch ((Communication.EnumVersionMatch)value)
            {
                case Communication.EnumVersionMatch.ProductMatch:
                    return "/MarbleLibrary;component/Images/no.resolution.circle.icon.16x16.png";
                case Communication.EnumVersionMatch.VersionMatch:
                    return "/MarbleLibrary;component/Images/passed.circle.icon.16x16.png";
            }

            return "/MarbleLibrary;component/Images/failed.circle.icon.16x16.png";
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
