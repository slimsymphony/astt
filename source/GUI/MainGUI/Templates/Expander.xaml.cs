using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;

using Marble.Model;

namespace Marble
{
    public partial class Expander : UserControl
    {
        public Expander()
        {
            InitializeComponent();

            if (App.ViewModel.ActiveView.Equals("TestLab"))
                ExpandRow.Command = App.ViewModel.TestLabRowExpanderCommand;
        }
    }
}
