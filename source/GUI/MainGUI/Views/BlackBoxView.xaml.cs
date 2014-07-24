using System.Windows;
using System.Windows.Controls;
using TestAutomation.Gui.Marble.IPC.Interfaces;

namespace Marble.Views
{
    /// <summary>
    /// Interaction logic for BlackBoxView.xaml
    /// </summary>
    public partial class BlackBoxView : UcBase
    {
        private bool buttonVisible;
        //private Point touchCoordinate;
        //private Boolean mouseDown = false;
        //private Stopwatch sw;
        //private int startX;
        //private int startY;

        public BlackBoxView()
        {
            InitializeComponent();
            this.DataContext = App.BlackBoxViewModel;
            //this.sw = new Stopwatch();
        }

        //private int actualX
        //{
        //    get
        //    {
        //        double screenResolutionX = App.BlackBoxViewModel.ScreenResolution.Item1;
        //        double factorX = screenResolutionX / 240;
        //        return (int)(this.touchCoordinate.X * factorX);
        //    }
        //}

        //private int actualY
        //{
        //    get
        //    {
        //        double screenResolutionY = App.BlackBoxViewModel.ScreenResolution.Item2;
        //        double imageY = (int)imageVideoFrame.Source.Height;
        //        double factorY = screenResolutionY / 320;
        //        return(int)(this.touchCoordinate.Y * factorY);
        //    }
        //}

        private void Expander_ToolTipOpening(object sender, ToolTipEventArgs e)
        {
            if (((System.Windows.Controls.Expander)sender).IsExpanded)
            {
                e.Handled = true;
            }
        }

        public void InitBlackBox_Click(object sender, RoutedEventArgs e)
        {
            App.BlackBoxViewModel.InitBlackBox();
        }

        private void PowerOnPhone_Click(object sender, RoutedEventArgs e)
        {
            App.BlackBoxViewModel.PowerOnPhone();
        }

        private void ClearRequirements_Click(object sender, RoutedEventArgs e)
        {
            App.BlackBoxViewModel.ClearRequirements();
            App.BlackBoxViewModel.UpdateData();
        }

        private void ExecuteCommand_Click(object sender, RoutedEventArgs e)
        {
            App.BlackBoxViewModel.ExecuteCommand(((CommandMapping)this.cardMapping.SelectedItem).MarbleCommand);
            this.buttonVisible = false;
        }

        private void DataGrid_LostFocus(object sender, RoutedEventArgs e)
        {
            this.buttonVisible = false;
        }

        private void DataGrid_GotFocus(object sender, RoutedEventArgs e)
        {
            this.buttonVisible = true;
        }

        private void UcBase_GotFocus(object sender, RoutedEventArgs e)
        {
            App.BlackBoxViewModel.CardSelected = buttonVisible;
            if (!buttonVisible)
            {
                this.cardMapping.UnselectAll();
            }
        }

        private void ExecuteCommand_GotFocus(object sender, RoutedEventArgs e)
        {
            this.buttonVisible = true;
        }

        private void UcBase_Unloaded(object sender, RoutedEventArgs e)
        {
            App.BlackBoxViewModel.ServiceDisconnect();
        }

        private void UcBase_Loaded(object sender, RoutedEventArgs e)
        {
            //ProgressDialogResult result = ProgressDialog.Execute("Marble - BlackBox", "Connecting BlackBox services...", (bw, we) =>
            //{
            //    Action action = () => App.BlackBoxViewModel.ServiceConnect();
            //    Task t = Task.Factory.StartNew(action);

            //    //Wait 60 seconds for connection to complete
            //    if (!t.Wait(60000))
            //    {
            //        throw new InvalidOperationException("Marble was unable to establish connection to BlackBox services within 60 seconds");
            //    }

            //    App.BlackBoxViewModel.BlackBoxGuiEnabled = true;
            //}, ProgressDialogSettings.WithLabelOnly);
            //if (result.OperationFailed)
            //{
            //    MessageBox.Show(result.Error.Message, "Failed to connect to BlackBox Service!", MessageBoxButton.OK, MessageBoxImage.Error);
            //    base.ParentWindow.Close();
            //}
        }

        //private void Image_MouseLeave(object sender, System.Windows.Input.MouseEventArgs e)
        //{
        //    if (this.mouseDown)
        //        this.release();
        //}

        //private void Image_MouseMove(object sender, MouseEventArgs e)
        //{
        //    if (!mouseDown) 
        //        return;

        //    this.touchCoordinate = e.GetPosition(sender as Image);
        //    this.touchEvent();
        //}

        //private void Image_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        //{
        //    this.touchCoordinate = e.GetPosition(sender as Image);
        //    this.touchEvent();
        //}

        //private void Image_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        //{
        //    this.release();
        //}

        //private void release()
        //{
        //    this.sw.Stop();
        //    if (App.BlackBoxViewModel.IsTouchEmulationEnabled)
        //    {

        //        if (this.startX != this.actualX && this.startY != this.actualY)
        //        {
        //            this.writeText("self.gesture.swipe((" + this.startX + ", " + this.startY + "), (" + this.actualX + ", " + this.actualY + "))");
        //        }
        //        else
        //        {
        //            if (this.sw.Elapsed.TotalMilliseconds <= 1000)
        //                this.writeText("self.select((" + this.startX + ", " + this.startY + "))");
        //            else
        //                this.writeText("self.select.long((" + this.startX + ", " + this.startY + "))");
        //        }
        //    }
        //    App.BlackBoxViewModel.TouchEvent("release", this.actualX.ToString(), this.actualY.ToString());
        //    mouseDown = false;
        //    this.sw.Restart();
        //}
        
        //private void touchEvent()
        //{
        //    if (!mouseDown)
        //    {
        //        this.calculateDelay();
        //        this.startX = this.actualX;
        //        this.startY = this.actualY;
        //        App.BlackBoxViewModel.TouchEvent("press", this.startX.ToString(), this.startY.ToString());
        //        this.sw.Restart();
        //        mouseDown = true;
        //    }
        //    else
        //    {
        //        App.BlackBoxViewModel.TouchEvent("move", this.actualX.ToString(), this.actualY.ToString());
        //    }
        //}

        //private void buttonShowHideTouchScreen_Click(object sender, RoutedEventArgs e)
        //{
        //    //if (!App.BlackBoxViewModel.TouchScreenVisible)
        //    //    App.BlackBoxViewModel.ExpanderExpanded = true;
        //    //App.BlackBoxViewModel.TouchScreenVisible = !App.BlackBoxViewModel.TouchScreenVisible;
        //    //if (App.BlackBoxViewModel.TouchScreenVisible)
        //    //{
        //    //    App.BlackBoxViewModel.VideoFrameCallbackClientSubscribe();
        //    //}
        //    //else
        //    //{
        //    //    App.BlackBoxViewModel.VideoFrameCallbackClientUnSubscribe();
        //    //}
        //}

        //private void buttonVolUp_Click(object sender, RoutedEventArgs e)
        //{
        //    this.calculateDelay();
        //    App.BlackBoxViewModel.PressKey("KEYCODE_VOLUME_UP", 100);
        //    this.writeText("self.select('KEYCODE_VOLUME_UP')");
        //    this.sw.Restart();
        //}

        //private void buttonVolDown_Click(object sender, RoutedEventArgs e)
        //{
        //    this.calculateDelay();
        //    App.BlackBoxViewModel.PressKey("KEYCODE_VOLUME_DOWN", 100);
        //    this.writeText("self.select('KEYCODE_VOLUME_DOWN')");
        //    this.sw.Restart();
        //}

        //private void buttonKeyLockToggle_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        //{
        //    this.calculateDelay();
        //}
       
        //private void buttonKeyLockToggle_PreviewMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        //{
        //    this.sw.Stop();
        //    if (this.sw.Elapsed.TotalSeconds <= 1)
        //    {
        //        App.BlackBoxViewModel.PressKey("KEYCODE_POWER", 100);
        //        this.writeText("self.select('KEYCODE_POWER')");
        //    }
        //    else
        //    {
        //        App.BlackBoxViewModel.PressKey("KEYCODE_POWER", (int)this.sw.Elapsed.TotalMilliseconds);
        //        this.writeText("self.select.long('KEYCODE_POWER')");
        //    }
        //    this.sw.Restart();
        //}

        //private void buttonBack_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        //{
        //    this.calculateDelay();
        //}

        //private void buttonBack_PreviewMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        //{
        //    this.sw.Stop();
        //    if (this.sw.Elapsed.TotalSeconds <= 1)
        //    {
        //        App.BlackBoxViewModel.PressKey("KEYCODE_BACK", 100);
        //        this.writeText("self.select('KEYCODE_BACK')");
        //    }
        //    else
        //    {
        //        App.BlackBoxViewModel.PressKey("KEYCODE_BACK", (int)this.sw.Elapsed.TotalMilliseconds);
        //        this.writeText("self.select.long('KEYCODE_BACK')");
        //    }
        //    this.sw.Restart();
        //}

        //private void buttonHome_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        //{
        //    this.calculateDelay();
        //}

        //private void buttonHome_PreviewMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        //{
        //    this.sw.Stop();
        //    if (this.sw.Elapsed.TotalSeconds <= 1)
        //    {
        //        App.BlackBoxViewModel.PressKey("KEYCODE_HOME", 100);
        //        this.writeText("self.select('KEYCODE_HOME')");
        //    }
        //    else
        //    {
        //        App.BlackBoxViewModel.PressKey("KEYCODE_HOME", (int)this.sw.Elapsed.TotalMilliseconds);
        //        this.writeText("self.select.long('KEYCODE_HOME')");
        //    }
        //    this.sw.Restart();
        //}

        //private void stackPanelTouch_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        //{
        //    if ((bool)e.NewValue == true)
        //        this.textBoxScriptBox.Height = 280;
        //}
        
        //private void calculateDelay()
        //{
        //    if (this.sw.Elapsed.TotalSeconds >= 1)
        //    {
        //        this.writeText("self.delay(" + ((Math.Floor(this.sw.Elapsed.TotalSeconds / 0.5) * 0.5) * 1000) + ")");
        //    }
        //    this.sw.Restart();
        //}

        //private void writeText(string text)
        //{
        //    this.textBoxScriptBox.Text += text + Environment.NewLine;
        //    this.textBoxScriptBox.ScrollToEnd();
        //}

        //private void mouseRightButtonDown(object sender, MouseButtonEventArgs e)
        //{
        //    this.textBoxScriptBox.Undo();
        //    this.sw.Restart();
        //}

        //private void OnTargetUpdated(object sender, System.Windows.Data.DataTransferEventArgs e)
        //{
        //    TextBlock block = (TextBlock)sender;
        //    string pCodes = App.BlackBoxViewModel.ProductCodesSelectedProduct;
        //    if (pCodes != null)
        //    {
        //        if (!pCodes.Contains(block.Text))
        //        {
        //            block.Foreground = Brushes.Red;
        //        }
        //    }
        //    if (block.Text == string.Empty)
        //    {
        //        block.Text = App.ViewModel.FuseClient.MainProduct.ConnectionFriendlyName;
        //        block.Foreground = Brushes.Red;
        //    }
        //}
    }
}
