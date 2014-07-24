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
using System.Windows.Shapes;

namespace Marble.Views.Dialogs
{
    using MarbleLibrary.CustomControls;
    using MarbleLibrary.Utilities;

    /// <summary>
    /// Interaction logic for DialogNumericValue.xaml
    /// </summary>
    public partial class DialogNumericValue : Window
    {
        public DialogNumericValue()
        {
            InitializeComponent();

            this.numericTextBox.Focus();
            this.CancelValue = -1;
        }

        public double ShowDialogWithResult()
        {
            this.ShowDialog();
            return this.Result;
        }

        public double Result
        {
            get
            {
                double result;

                return double.TryParse(this.numericTextBox.Text, out result) ? result : -1;
            }
        }

        public object DialogTitle
        {
            get { return this.groupBoxDialog.Header; }
            set { this.groupBoxDialog.Header = value; }
        }

        public string DialogMessage
        {
            get { return this.textBlockDialogMessage.Text; }
            set { this.textBlockDialogMessage.Text = value; }
        }

        public NumberMode NumberMode
        {
            get { return this.numericTextBox.NumberMode; }
            set { this.numericTextBox.NumberMode = value; }
        }

        public double DefaultValue
        {
            get
            {
                double defaultValue = 0;

                return double.TryParse(this.numericTextBox.Text, out defaultValue) ? defaultValue : 0;
            }
            set
            {
                this.numericTextBox.Text = value.ToString();
            }
        }

        public double CancelValue { get; set; }

        public int MinValue
        {
            get { return this.numericTextBox.MinValue; }
            set { this.numericTextBox.MinValue = value; }
        }

        public int MaxValue
        {
            get { return this.numericTextBox.MaxValue; }
            set { this.numericTextBox.MaxValue = value; }
        }

        private void Window_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.Enter:
                    GuiUtilities.PerformClick(this.buttonOk);
                    break;
                case Key.Escape:
                    GuiUtilities.PerformClick(this.buttonCancel);
                    break;
            }
        }

        private void buttonOk_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void buttonCancel_Click(object sender, RoutedEventArgs e)
        {
            this.numericTextBox.Text = this.CancelValue.ToString();

            this.Close();
        }
    }
}
