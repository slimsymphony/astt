using System.Diagnostics;
using System.Linq;
using System.Windows;
using System.Windows.Forms;
using log4net;
using log4net.Appender;
using log4net.Repository.Hierarchy;

namespace BlackBoxService
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool closing;
        public MainWindow()
        {
            this.closing = false;
            InitializeComponent();
            App.notifyIcon.Icon = Properties.Resources.App;
            App.notifyIcon.Text = "BlackBox Service";
            App.notifyIcon.BalloonTipText = "BlackBox Service";
            App.notifyIcon.Visible = true;
            App.notifyIcon.MouseDoubleClick += notifyIcon_MouseDoubleClick;
            this.WindowState = WindowState.Minimized;
        }

        void notifyIcon_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.WindowState = WindowState.Normal;
            this.Show();
            App.notifyIcon.Visible = false;
        }

        private void buttonCloseService_Click(object sender, RoutedEventArgs e)
        {
            this.closing = true;
            this.Close();
        }

        private void buttonOpenLog_Click(object sender, RoutedEventArgs e)
        {
            var rootAppender = ((Hierarchy)LogManager.GetRepository()).Root.Appenders.OfType<RollingFileAppender>().FirstOrDefault();
            string filename = rootAppender != null ? rootAppender.File : string.Empty;
            Process.Start("Notepad", filename);
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            // HACK: Using Process PriorityClass to identify that the process main window is closed from external source
            // rather than pressing the "Close Service" button
            if (!this.closing && Process.GetCurrentProcess().PriorityClass != ProcessPriorityClass.RealTime)
            {
                App.notifyIcon.Visible = true;
                e.Cancel = true;
                this.Hide();
            }
        }
    }
}