using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
    using MarbleLibrary.Utilities;

    /// <summary>
    /// Interaction logic for SimManagerView.xaml
    /// </summary>
    public partial class SimManagerView : UcBase
    {
        public SimManagerView()
        {
            InitializeComponent();

            this.DataContext = App.SimManagerViewModel;
            App.ViewModel.FuseClient.ScanPhones();
        }

        private void ListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (App.SimManagerViewModel == null) return;
            if (App.SimManagerViewModel.SelectedPhone == null) return;

            App.SimManagerViewModel.SelectedSim = App.SimManagerViewModel.SelectedPhone.SelectedSim;
        }

        private void closeWindow_Click(object sender, RoutedEventArgs e)
        {
            base.CloseCommandHandler(this, null);
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            App.SimManagerViewModel.PhoneViewModel.ForceValidationToSims();
        }


    }
}
