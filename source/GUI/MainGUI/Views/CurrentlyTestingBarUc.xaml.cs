using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Marble.Views
{
    using System.Windows.Threading;

    /// <summary>
    /// Interaction logic for CurrentlyTestingBarUc.xaml
    /// </summary>
    public partial class CurrentlyTestingBarUc : UserControl
    {
        public string IsCurrentTimeDisplayEnabled
        {
            get { return (string)GetValue(IsCurrentTimeDisplayEnabledProperty); }
            set { SetValue(IsCurrentTimeDisplayEnabledProperty, value); }
        }

        public static readonly DependencyProperty IsCurrentTimeDisplayEnabledProperty = DependencyProperty.Register(
            "IsCurrentTimeDisplayEnabled",
            typeof(bool),
            typeof(CurrentlyTestingBarUc),
            new PropertyMetadata(false));

        private DispatcherTimer currentTimeTimer;

        public CurrentlyTestingBarUc()
        {
            InitializeComponent();

            this.DataContext = App.ViewModel;

            //currentTimeTimer = new DispatcherTimer(
            //    new TimeSpan(0, 0, 0, 0, 500), 
            //    DispatcherPriority.Normal, 
            //    delegate { this.TextBlockCurrentTime.Text = DateTime.Now.ToString("HH:mm:ss"); }, 
            //    this.Dispatcher);
            
            currentTimeTimer = new DispatcherTimer(DispatcherPriority.Normal, this.Dispatcher);
            currentTimeTimer.Tick += currentTimeTimer_Tick;
            currentTimeTimer.Interval = new TimeSpan(0, 0, 0, 0, 500);
            currentTimeTimer.Start();
        }

        void currentTimeTimer_Tick(object sender, EventArgs e)
        {
            this.TextBlockCurrentTime.Text = DateTime.Now.ToString("HH:mm:ss");
        }

        private void UcCurrentlyTestingBar_Unloaded(object sender, RoutedEventArgs e)
        {
            currentTimeTimer.Tick -= this.currentTimeTimer_Tick;
            currentTimeTimer.Stop();
        }
    }
}
