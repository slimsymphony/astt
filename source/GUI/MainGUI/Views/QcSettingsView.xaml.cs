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
using Marble.Communication;

namespace Marble.Views
{
    using Marble.Model;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// Interaction logic for QcSettingsView.xaml
    /// </summary>
    public partial class QcSettingsView : UcBase
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="QcSettingsView"/> class.
        /// </summary>
        public QcSettingsView()
        {
            InitializeComponent();

            this.DataContext = App.QcSettingsViewModel;
        }

        private void login_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                GuiUtilities.PerformClick(this.buttonQcLogin);
            }
        }
    }
}
