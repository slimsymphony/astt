using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    public class ConnectorStateToTooltipConverter : MarkupExtension, IValueConverter
    {
        private static ConnectorStateToTooltipConverter _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new ConnectorStateToTooltipConverter();
            }
            return _converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            string tooltip = string.Empty;

            if (App.ViewModel.IsTestRunPaused)
                tooltip = "Resume Execution";
            else if (App.ViewModel.IsTestRunPauseRequested)
                tooltip = "Resume";
            else if ((int)value == (int)Marble.Communication.ConnectorState.Idle || (int)value == (int)Marble.Communication.ConnectorState.FrameworkReady)
                tooltip = "Run Checked Tests";
            else
                tooltip = "Pause Execution after Current Test Case";

            return tooltip;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
