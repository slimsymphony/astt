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
    /// Interaction logic for MarbleWikiView.xaml
    /// </summary>
    public partial class MarbleWikiView : UcBase
    {
        public MarbleWikiView()
        {
            this.InitializeComponent();
        }

        private void closeWindow_Click(object sender, RoutedEventArgs e)
        {
            base.CloseCommandHandler(this, null);
        }

        public void NavigateToMarbleWiki()
        {
            this.webBrowserMarbleWiki.Navigate("http://wikis.in.nokia.com/Marble/WebHome");
        }
    }
}
