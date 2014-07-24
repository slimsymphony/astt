using System;
using System.Windows.Data;
using System.Windows.Markup;

namespace Marble.Converters
{
    class ConnectorStateToImageConverter : MarkupExtension, IValueConverter
    {
        private static ConnectorStateToImageConverter converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (converter == null)
            {
                converter = new ConnectorStateToImageConverter();
            }
            return converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            string imagePath = string.Empty;

            if (App.ViewModel.IsTestRunPauseRequested) 
                ////imagePath = "/MarbleLibrary;component/Images/play.gray.icon.32x32.png";
                imagePath = "/MarbleLibrary;component/Images/playing.icon.20x20.png";
            else if ((int)value == (int)Marble.Communication.ConnectorState.Idle || (int)value == (int)Marble.Communication.ConnectorState.FrameworkReady) 
                ////imagePath = "/MarbleLibrary;component/Images/play.icon.32x32.png";
                imagePath = "/MarbleLibrary;component/Images/playing.icon.20x20.png";
            else 
                ////imagePath = "/MarbleLibrary;component/Images/pause.with.delay.icon.32x32.png";
                imagePath = "/MarbleLibrary;component/Images/paused.icon.20x20.png";

            return imagePath;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }

    class ConnectorStateToCircleMarbleButtonImageConverter : MarkupExtension, IValueConverter
    {
        private static ConnectorStateToCircleMarbleButtonImageConverter converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (converter == null)
            {
                converter = new ConnectorStateToCircleMarbleButtonImageConverter();
            }
            return converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            string imagePath = string.Empty;

            if (App.ViewModel.IsTestRunPauseRequested)
                imagePath = "/MarbleLibrary;component/Images/play.marble.icon.64x64.png";
            else if ((int)value == (int)Marble.Communication.ConnectorState.Idle || (int)value == (int)Marble.Communication.ConnectorState.FrameworkReady)
                imagePath = "/MarbleLibrary;component/Images/play.marble.icon.64x64.png";
            else
                imagePath = "/MarbleLibrary;component/Images/pause.marble.icon.64x64.png";

            return imagePath;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }

    class ConnectorStateToCurrentTestingStateImageConverter : MarkupExtension, IValueConverter
    {
        private static ConnectorStateToCurrentTestingStateImageConverter converter = null;
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (converter == null)
            {
                converter = new ConnectorStateToCurrentTestingStateImageConverter();
            }
            return converter;
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            string imagePath = string.Empty;

            if (App.ViewModel.StoppingExecution)
                imagePath = "/MarbleLibrary;component/Images/stopping.icon.20x20.png";
            else if (App.ViewModel.IsTestRunPaused)
                imagePath = "/MarbleLibrary;component/Images/paused.icon.20x20.png";
            else if (App.ViewModel.IsTestRunPauseRequested)
                imagePath = "/MarbleLibrary;component/Images/paused.icon.20x20.png";
            else if ((int)value == (int)Marble.Communication.ConnectorState.Idle || (int)value == (int)Marble.Communication.ConnectorState.FrameworkReady)
                imagePath = "";
            else
                imagePath = "/MarbleLibrary;component/Images/playing.icon.20x20.png";

            return imagePath;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }
}
