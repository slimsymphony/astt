using MarbleLibrary.Commands;

namespace MarbleLibrary.CustomControls
{
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Controls.Primitives;
    using System.Windows.Input;
    using System.Windows.Media;

    /// <summary>
    /// Status of the connected device (usually Offline or Online).
    /// </summary>
    public enum DeviceState
    {
        /// <summary>
        /// 
        /// </summary>
        Recovery,

        /// <summary>
        /// 
        /// </summary>
        BootLoader,

        /// <summary>
        /// Device is connected but offline.
        /// </summary>
        Offline,

        /// <summary>
        /// Device is connected and online.
        /// </summary>
        Online,

        /// <summary>
        /// 
        /// </summary>
        Download,

        /// <summary>
        /// 
        /// </summary>
        Unknown,

        /// <summary>
        /// Device has previously been connected but is now disconnected.
        /// Device is not removed from the list if it is selected as the main phone.
        /// </summary>
        Disconnected
    }

    public class MarbleMainMenuItem : Button
    {
        ////LargeImageSource="/MarbleLibrary;component/Images\save.icon.32x32.png" Foreground="White" 
        ////                                      SmallImageSource="/MarbleLibrary;component/Images\save.icon.16x16.png"
        ////                                      Label="Save" Margin="0,5,0,0"
        ////                                      ToolTipTitle="Save changes to testset" 
        ////                                      ToolTipDescription="Saves changes to currently open testset file."
        ////                                      DropDownToolTipTitle="Save changes to testset"
        ////                                      DropDownToolTipDescription="Click here for option to save testset with different name."
        ////                                      Command="{Binding SaveTestsetFileCommand}"

        public string Label
        {
            get { return (string)GetValue(LabelProperty); }
            set { SetValue(LabelProperty, value); }
        }

        public static readonly DependencyProperty LabelProperty = DependencyProperty.Register(
            "Label",
            typeof(string),
            typeof(MarbleMainMenuItem),
            new PropertyMetadata(null));

        public string ToolTipTitle
        {
            get { return (string)GetValue(ToolTipTitleProperty); }
            set { SetValue(ToolTipTitleProperty, value); }
        }

        public static readonly DependencyProperty ToolTipTitleProperty = DependencyProperty.Register(
            "ToolTipTitle",
            typeof(string),
            typeof(MarbleMainMenuItem),
            new PropertyMetadata(null));

        public string ToolTipDescription
        {
            get { return (string)GetValue(ToolTipDescriptionProperty); }
            set { SetValue(ToolTipDescriptionProperty, value); }
        }

        public static readonly DependencyProperty ToolTipDescriptionProperty = DependencyProperty.Register(
            "ToolTipDescription",
            typeof(string),
            typeof(MarbleMainMenuItem),
            new PropertyMetadata(null));

        public ImageSource LargeImageSource
        {
            get { return (ImageSource)GetValue(LargeImageSourceProperty); }
            set { SetValue(LargeImageSourceProperty, value); }
        }

        public static readonly DependencyProperty LargeImageSourceProperty = DependencyProperty.Register(
            "LargeImageSource",
            typeof(ImageSource),
            typeof(MarbleMainMenuItem),
            new PropertyMetadata(null));

        public ImageSource SmallImageSource
        {
            get { return (ImageSource)GetValue(SmallImageSourceProperty); }
            set { SetValue(SmallImageSourceProperty, value); }
        }

        public static readonly DependencyProperty SmallImageSourceProperty = DependencyProperty.Register(
            "SmallImageSource",
            typeof(ImageSource),
            typeof(MarbleMainMenuItem),
            new PropertyMetadata(null));

        public bool IsSelected
        {
            get { return (bool)GetValue(IsSelectedProperty); }
            set { SetValue(IsSelectedProperty, value); }
        }

        public static readonly DependencyProperty IsSelectedProperty = DependencyProperty.Register(
            "IsSelected",
            typeof(bool),
            typeof(MarbleMainMenuItem),
            new PropertyMetadata(false));
    }

    public class MarbleMainMenuToggleItem : ToggleButton
    {
        public string Label
        {
            get { return (string)GetValue(LabelProperty); }
            set { SetValue(LabelProperty, value); }
        }

        public static readonly DependencyProperty LabelProperty = DependencyProperty.Register(
            "Label",
            typeof(string),
            typeof(MarbleMainMenuToggleItem),
            new PropertyMetadata(null));

        public string ToolTipTitle
        {
            get { return (string)GetValue(ToolTipTitleProperty); }
            set { SetValue(ToolTipTitleProperty, value); }
        }

        public static readonly DependencyProperty ToolTipTitleProperty = DependencyProperty.Register(
            "ToolTipTitle",
            typeof(string),
            typeof(MarbleMainMenuToggleItem),
            new PropertyMetadata(null));

        public string ToolTipDescription
        {
            get { return (string)GetValue(ToolTipDescriptionProperty); }
            set { SetValue(ToolTipDescriptionProperty, value); }
        }

        public static readonly DependencyProperty ToolTipDescriptionProperty = DependencyProperty.Register(
            "ToolTipDescription",
            typeof(string),
            typeof(MarbleMainMenuToggleItem),
            new PropertyMetadata(null));

        public ImageSource LargeImageSource
        {
            get { return (ImageSource)GetValue(LargeImageSourceProperty); }
            set { SetValue(LargeImageSourceProperty, value); }
        }

        public static readonly DependencyProperty LargeImageSourceProperty = DependencyProperty.Register(
            "LargeImageSource",
            typeof(ImageSource),
            typeof(MarbleMainMenuToggleItem),
            new PropertyMetadata(null));

        public ImageSource SmallImageSource
        {
            get { return (ImageSource)GetValue(SmallImageSourceProperty); }
            set { SetValue(SmallImageSourceProperty, value); }
        }

        public static readonly DependencyProperty SmallImageSourceProperty = DependencyProperty.Register(
            "SmallImageSource",
            typeof(ImageSource),
            typeof(MarbleMainMenuToggleItem),
            new PropertyMetadata(null));
    }

    /// <summary>
    /// UI element for displaying main (adb) devices at the menu of Marble main window.
    /// </summary>
    public class MarbleMainDeviceItem : ToggleButton
    {
        /// <summary>
        /// Text to display.
        /// </summary>
        public string Label
        {
            get { return (string)GetValue(LabelProperty); }
            set { SetValue(LabelProperty, value); }
        }

        public static readonly DependencyProperty LabelProperty = DependencyProperty.Register(
            "Label",
            typeof(string),
            typeof(MarbleMainDeviceItem),
            new PropertyMetadata(null));

        /// <summary>
        /// Whether this device is selected as the main device or not.
        /// </summary>
        public bool IsSelected
        {
            get { return (bool)GetValue(IsSelectedProperty); }
            set { SetValue(IsSelectedProperty, value); }
        }

        public static readonly DependencyProperty IsSelectedProperty = DependencyProperty.Register(
            "IsSelected",
            typeof (bool),
            typeof (MarbleMainDeviceItem),
            new PropertyMetadata(false));

        /// <summary>
        /// State of this device.
        /// </summary>
        public DeviceState State
        {
            get { return (DeviceState)GetValue(StateProperty); }
            set { SetValue(StateProperty, value); }
        }

        public static readonly DependencyProperty StateProperty = DependencyProperty.Register(
            "State",
            typeof(DeviceState),
            typeof(MarbleMainDeviceItem),
            new PropertyMetadata(DeviceState.Unknown));


        /// <summary>
        /// Sequence number of this main device among the selected main devices.
        /// </summary>
        public int MainIndex
        {
            get { return (int)GetValue(MainIndexProperty); }
            set { SetValue(MainIndexProperty, value); }
        }

        public static readonly DependencyProperty MainIndexProperty = DependencyProperty.Register(
            "MainIndex",
            typeof(int),
            typeof(MarbleMainDeviceItem),
            new PropertyMetadata(0));

        /// <summary>
        /// Header text of the tooltip.
        /// </summary>
        public string ToolTipTitle
        {
            get { return (string)GetValue(ToolTipTitleProperty); }
            set { SetValue(ToolTipTitleProperty, value); }
        }

        public static readonly DependencyProperty ToolTipTitleProperty = DependencyProperty.Register(
            "ToolTipTitle",
            typeof(string),
            typeof(MarbleMainDeviceItem),
            new PropertyMetadata(null));

        /// <summary>
        /// Body text of the tooltip.
        /// </summary>
        public string ToolTipDescription
        {
            get { return (string)GetValue(ToolTipDescriptionProperty); }
            set { SetValue(ToolTipDescriptionProperty, value); }
        }

        public static readonly DependencyProperty ToolTipDescriptionProperty = DependencyProperty.Register(
            "ToolTipDescription",
            typeof(string),
            typeof(MarbleMainDeviceItem),
            new PropertyMetadata(null));

        /// <summary>
        /// Image to be displayed at the left side of the text.
        /// </summary>
        public ImageSource LargeImageSource
        {
            get { return (ImageSource)GetValue(LargeImageSourceProperty); }
            set { SetValue(LargeImageSourceProperty, value); }
        }

        public static readonly DependencyProperty LargeImageSourceProperty = DependencyProperty.Register(
            "LargeImageSource",
            typeof(ImageSource),
            typeof(MarbleMainDeviceItem),
            new PropertyMetadata(null));

        public ICommand DisableLockScreenCommand
        {
            get { return (ICommand)GetValue(DisableLockScreenCommandProperty); }
            set { SetValue(DisableLockScreenCommandProperty, value); }
        }

        public static readonly DependencyProperty DisableLockScreenCommandProperty = DependencyProperty.Register(
            "DisableLockScreenCommand",
            typeof(ICommand),
            typeof(MarbleMainDeviceItem),
            new PropertyMetadata(null));

        private DelegateCommand<object> copyInformationToClipboard;

        /// <summary>
        /// Copies all information from the datacontext to clipboard.
        /// </summary>
        public ICommand CopyInformationToClipboard
        {
            get
            {
                if (copyInformationToClipboard == null)
                    copyInformationToClipboard = new DelegateCommand<object>(CopyInformationToClipboardCommandExecuted, CopyInformationToClipboardCommandCanExecute);

                return copyInformationToClipboard;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public bool CopyInformationToClipboardCommandCanExecute(object dataContext)
        {
            return true;
        }

        /// <summary>
        /// Copies dataContext.ToString() to clipboard. "No data available" if datacontext is null.
        /// </summary>
        public void CopyInformationToClipboardCommandExecuted(object dataContext)
        {
            // Error handling may need to be added if clipboard can't be accessed
            Clipboard.SetDataObject(dataContext == null ? "No data available" : dataContext.ToString());
        }

    }
}
