using System;
using System.Windows;
using System.Windows.Media.Animation;

namespace Marble
{
    using System.Text;
    using System.Threading;
    using System.Windows.Threading;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// Interaction logic for Executor.xaml
    /// </summary>
    public partial class Executor : Window
    {
        public Executor()
        {
            InitializeComponent();

            ExecutorGrid.DataContext = App.ViewModel;
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            App.ViewModel.MarbleConnector.MarbleLogModel.GenerateRandomTestData(int.Parse(this.numericTextBoxRows.Text));
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            App.ViewModel.MarbleConnector.MarbleLogModel.FlushEntries();
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            App.ViewModel.MarbleConnector.MarbleLogModel.ClearEntries();
        }
    }
}
