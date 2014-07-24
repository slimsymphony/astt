using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Marble.Converters
{
    /// <summary>
    /// Converts ConnectorState (int) to a corresponding string representation and vice versa.
    /// </summary>
    /// 
    //[System.Windows.Data.ValueConversion(typeof(Communication.ConnectorState), typeof(String))]
    public class ConnectorStateToString : System.Windows.Markup.MarkupExtension, System.Windows.Data.IValueConverter
    {
        private static ConnectorStateToString _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new ConnectorStateToString();
            }
            return _converter;
        }

        readonly string[] stateNames = { "No framework", "Starting framework", "Framework ready", "Sending command", "Executing command", "Quitting framework", "Stopping execution" };

        // convert from int to string
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return stateNames.ElementAtOrDefault((int)value);
        }

        // convert from string to int
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            for (int ii = 0; ii < stateNames.Length; ii++)
            {
                if (stateNames[ii] == (string)value)
                    return ii;
            }
            return -1;
        }
    }

    public class ConnectorStateToGuiStateString : System.Windows.Markup.MarkupExtension, System.Windows.Data.IValueConverter
    {
        private static ConnectorStateToGuiStateString _converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new ConnectorStateToGuiStateString();
            }
            return _converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            string imagePath = string.Empty;

            if (App.ViewModel.IsTestRunPauseRequested) 
                return "PauseRequested";
            if ((int)value == (int)Marble.Communication.ConnectorState.Idle
                || (int)value == (int)Marble.Communication.ConnectorState.FrameworkReady) 
                return "Ready";
            
            return "Running";
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
