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
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Text.RegularExpressions;

    using Marble.Utilities;
    using Marble.ViewModel;

    using MarbleLibrary.CustomControls;
    using MarbleLibrary.Utilities;

    /// <summary>
    /// Interaction logic for DialogFindAndReplace.xaml
    /// </summary>
    public partial class DialogFindAndReplace : Window, INotifyPropertyChanged
    {
        public DialogFindAndReplace(SimpleTextEditorView parentEditorView, string textSelection = "")
        {
            InitializeComponent();
            
            this.DataContext = this;
            this.ParentEditorView = parentEditorView;
            this.comboBoxFindWhat.Text = textSelection;
            this.ParentEditorView.AddToFindHistory(textSelection);
        }

        public SimpleTextEditorView ParentEditorView { get; private set; }

        public bool CanFind { get { return this.ParentEditorView.CountTextOccurances(this.comboBoxFindWhat.Text, this.checkBoxMatchCase.IsChecked == true) > 0; } }

        public bool CanReplace { get { return this.ParentEditorView.CurrentSelectionMatchesSearchedText(this.comboBoxFindWhat.Text, this.checkBoxMatchCase.IsChecked == true); } }

        private void buttonFindPrevious_Click(object sender, RoutedEventArgs e)
        {
            this.ParentEditorView.FindPrevious(this.comboBoxFindWhat.Text, this.checkBoxMatchCase.IsChecked == true);
            this.buttonFindPrevious.Focus();
        }

        private void buttonFindNext_Click(object sender, RoutedEventArgs e)
        {
            this.ParentEditorView.FindNext(this.comboBoxFindWhat.Text, this.checkBoxMatchCase.IsChecked == true);
            this.buttonFindNext.Focus();
        }

        private void buttonClose_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void buttonReplace_Click(object sender, RoutedEventArgs e)
        {
            this.ParentEditorView.ReplaceSelection(this.comboBoxReplaceWith.Text, this.comboBoxFindWhat.Text, this.checkBoxMatchCase.IsChecked == true);
            this.buttonFindNext_Click(null, null);
            this.buttonReplace.Focus();
            this.updateTextBlockInfo();
        }

        private void buttonReplaceAll_Click(object sender, RoutedEventArgs e)
        {
            int replaceCount = this.ParentEditorView.ReplaceAll(this.comboBoxFindWhat.Text, this.comboBoxReplaceWith.Text, this.checkBoxMatchCase.IsChecked == true);

            MessageBox.Show(replaceCount + " occurrences were replaced.", "Replace All - Marble");

            this.buttonReplaceAll.Focus();
            this.updateTextBlockInfo();
        }

        private void comboBoxFindWhat_TextChanged(object sender, TextChangedEventArgs e)
        {
            this.updateTextBlockInfo();
        }

        private void checkBoxMatchCase_CheckedChanged(object sender, RoutedEventArgs e)
        {
            this.updateTextBlockInfo();
        }

        private void updateTextBlockInfo()
        {
            this.textBlockInfo.Text = this.ParentEditorView.CountTextOccurances(this.comboBoxFindWhat.Text, this.checkBoxMatchCase.IsChecked == true)
                                         + " occurrence(s) found.";
            this.OnPropertyChanged("CanFind");
            this.OnPropertyChanged("CanReplace");
        }

        private void comboBox_GotFocus_UpdateBinding(object sender, RoutedEventArgs e)
        {
            if (!(sender is ComboBox)) return;

            ComboBox comboBox = sender as ComboBox;

            BindingExpression binding = BindingOperations.GetBindingExpression(comboBox, ComboBox.ItemsSourceProperty);

            if (binding != null)
                binding.UpdateTarget();
        }

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }
}
