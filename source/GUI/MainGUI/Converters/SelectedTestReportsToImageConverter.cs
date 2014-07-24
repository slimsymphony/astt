using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    using Marble.ViewModel;

    /// <summary>
    /// Class for converting SelectedReportsEnum to image file path.
    /// </summary>
    public class SelectedTestReportsToImageConverter : MarkupExtension, IValueConverter
    {
        private static SelectedTestReportsToImageConverter converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new SelectedTestReportsToImageConverter());
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            const string DefaultIcon = "/MarbleLibrary;component/Images/empty.report.icon.32x32.png";

            if (!(value is MarbleMainViewModel.SelectedReportsEnum)) return DefaultIcon;

            switch ((MarbleMainViewModel.SelectedReportsEnum)value)
            {
                case MarbleMainViewModel.SelectedReportsEnum.None:
                    return "/MarbleLibrary;component/Images/empty.report.icon.32x32.png";
                case MarbleMainViewModel.SelectedReportsEnum.UnresolvedReport:
                    return "/MarbleLibrary;component/Images/empty.report.icon.32x32.png";
                case MarbleMainViewModel.SelectedReportsEnum.FailedReport:
                    return "/MarbleLibrary;component/Images/failed.report.icon.32x32.png";
                case MarbleMainViewModel.SelectedReportsEnum.PassedReport:
                    return "/MarbleLibrary;component/Images/report.icon2.32x32.png";
                case MarbleMainViewModel.SelectedReportsEnum.MultipleContainingFailedReport:
                    return "/MarbleLibrary;component/Images/multiple.failed.reports.icon.32x32.png";
                case MarbleMainViewModel.SelectedReportsEnum.MultipleAllPassedReports:
                    return "/MarbleLibrary;component/Images/multiple.passed.reports.icon.32x32.png";
            }

            return DefaultIcon;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
