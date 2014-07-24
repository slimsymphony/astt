using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    using Marble.ViewModel;

    class ConnectorStateToRunStopText : MarkupExtension, IValueConverter
    {
        private static ConnectorStateToRunStopText _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new ConnectorStateToRunStopText();
            }
            return _converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            string buttonText = "";

            if (App.ViewModel.IsTestRunPaused || App.ViewModel.IsTestRunPauseRequested) 
                buttonText = "Resume";
            else if ((int)value == (int)Marble.Communication.ConnectorState.Idle || (int)value == (int)Marble.Communication.ConnectorState.FrameworkReady)
                buttonText = "Run";
            else 
                buttonText = "Pause";

            return buttonText;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
