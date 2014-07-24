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
    using System.IO;
    using System.Windows.Forms;

    using MarbleLibrary.Utilities;

    using DataFormats = System.Windows.DataFormats;
    using DragDropEffects = System.Windows.DragDropEffects;
    using DragEventArgs = System.Windows.DragEventArgs;

    /// <summary>
    /// Interaction logic for FlasherView.xaml
    /// </summary>
    public partial class FlasherView : UcBase
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="FlasherView"/> class.
        /// </summary>
        public FlasherView()
        {
            InitializeComponent();

            this.DataContext = App.FlasherViewModel;

            if (App.ViewModel.FuseClient.ConnectionsSupportedByFlasher != null && App.ViewModel.FuseClient.ConnectionsSupportedByFlasher.Count > 0)
                App.FlasherViewModel.Connection = App.ViewModel.FuseClient.ConnectionsSupportedByFlasher.First();

            if (App.FlasherViewModel.Connection != null && App.FlasherViewModel.Connection.Version != null && !string.IsNullOrEmpty(App.FlasherViewModel.Connection.Version.RMCode))
                App.FlasherViewModel.FirmwareDirectoryPath = @"C:\ProgramData\Nokia\Packages\Products\" + App.FlasherViewModel.Connection.Version.RMCode;
            else 
                App.FlasherViewModel.FirmwareDirectoryPath = @"C:\ProgramData\Nokia\Packages\Products";

            this.comboBoxVariants.ItemsSource = App.FlasherViewModel.VariantCollection;
        }

        private void buttonBrowseMcuFile_Click(object sender, RoutedEventArgs e)
        {
            string mcuFilePath = FileUtilities.ShowOpenFileDialogForMcuFile(string.Empty);

            if (!string.IsNullOrEmpty(mcuFilePath))
                App.FlasherViewModel.McuFilePath = mcuFilePath;
        }

        private void buttonBrowseContentFile_Click(object sender, RoutedEventArgs e)
        {
            string contentFilePath = FileUtilities.ShowOpenFileDialogForContentFile(string.Empty);

            if (!string.IsNullOrEmpty(contentFilePath)) App.FlasherViewModel.ContentFilePath = contentFilePath;
        }

        private void buttonBrowseLanguageFile_Click(object sender, RoutedEventArgs e)
        {
            string languageFilePath = FileUtilities.ShowOpenFileDialogForLanguageFile(string.Empty);

            if (!string.IsNullOrEmpty(languageFilePath)) App.FlasherViewModel.LanguageFilePath = languageFilePath;
        }

        private void buttonBrowseEraseFile_Click(object sender, RoutedEventArgs e)
        {
            string eraseFilePath = FileUtilities.ShowOpenFileDialogForEraseFile(string.Empty);

            if (!string.IsNullOrEmpty(eraseFilePath)) App.FlasherViewModel.EraseFilePath = eraseFilePath;
        }

        private void buttonBrowseFirmwareFolder_Click(object sender, RoutedEventArgs e)
        {
            string firmwareFolder;
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            fbd.ShowNewFolderButton = false;
            fbd.Description = "Select Folder with Firmware Files";

            if (Directory.Exists(App.FlasherViewModel.FirmwareDirectoryPath))
            {
                fbd.SelectedPath = App.FlasherViewModel.FirmwareDirectoryPath;
            }

            fbd.ShowDialog();

            App.FlasherViewModel.FirmwareDirectoryPath = fbd.SelectedPath;

            this.ClickSelectTextBox_TextChanged(this, null);
        }

        private void textBlockConsoleOutput_TextChanged(object sender, TextChangedEventArgs e)
        {
            // Scrolls text box to end when last visible line is the last line.
            if (this.textBlockConsoleOutput.GetLastVisibleLineIndex() >= this.textBlockConsoleOutput.LineCount - 1)
            {
                this.textBlockConsoleOutput.ScrollToEnd();
            }
        }

        /// <summary>
        /// Checks if any of the dragged files is a flash file.
        /// Changes DragEventArgs.Effects to Copy if a flash file is found.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onFlashingFileDragEnter(object sender, DragEventArgs e)
        {
            e.Effects = DragDropEffects.None;
            if (!e.Data.GetDataPresent(DataFormats.FileDrop)) return;
            var data = e.Data.GetData(DataFormats.FileDrop) as string[];
            if (data == null) return;

            foreach (string filepath in data)
                if (!string.IsNullOrEmpty(filepath) && FileUtilities.IsFlashFile(filepath))
                {
                    e.Effects = DragDropEffects.Copy;
                    break;
                }
        }

        /// <summary>
        /// Checks if any of the dragged files is a flash file.
        /// Changes DragEventArgs.Effects to Copy if a flash file is found.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onFlashingFileDragOver(object sender, DragEventArgs e)
        {
            e.Effects = DragDropEffects.None;
            if (!e.Data.GetDataPresent(DataFormats.FileDrop)) return;
            var data = e.Data.GetData(DataFormats.FileDrop) as string[];
            if (data == null) return;

            foreach (string filepath in data)
                if (!string.IsNullOrEmpty(filepath) && FileUtilities.IsFlashFile(filepath))
                {
                    e.Effects = DragDropEffects.Copy;
                    break;
                }
        }

        /// <summary>
        /// Finds allowed flash files from the dropped files.
        /// The first occurrence of each flash file type (mcusw, content, language) is taken into use.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LayoutRoot_Drop(object sender, DragEventArgs e)
        {
            e.Effects = DragDropEffects.None;
            if (!e.Data.GetDataPresent(DataFormats.FileDrop)) return;

            bool mcuFileFound = false;
            bool contentFileFound = false;
            bool languageFileFound = false;

            var data = e.Data.GetData(DataFormats.FileDrop) as string[];

            if (data == null) return;

            foreach (string dataText in data)
            {
                if (FileUtilities.IsMcuswFile(dataText) && !mcuFileFound)
                {
                    App.FlasherViewModel.McuFilePath = dataText;
                    mcuFileFound = true;
                }
                else if (FileUtilities.IsContentFile(dataText) && !contentFileFound)
                {
                    App.FlasherViewModel.ContentFilePath = dataText;
                    contentFileFound = true;
                }
                else if (FileUtilities.IsLanguageFile(dataText) && !languageFileFound)
                {
                    App.FlasherViewModel.LanguageFilePath = dataText;
                    languageFileFound = true;
                }

                if (mcuFileFound && contentFileFound && languageFileFound) break;
            }

            // Updates button IsEnabled bindings.
            CommandManager.InvalidateRequerySuggested();
        }

        private void StackPanel_IsEnabledChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            // Updates button IsEnabled bindings.
            CommandManager.InvalidateRequerySuggested();
        }

        private void ClickSelectTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (App.FlasherViewModel.IsFirmwareFlashModeEnabled && !Directory.Exists(App.FlasherViewModel.FirmwareDirectoryPath)) return;

            this.comboBoxVariants.ItemsSource = App.FlasherViewModel.VariantCollection;
        }

        private void comboBoxConnections_IsEnabledChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            if (App.ViewModel.FuseClient.ConnectionsSupportedByFlasher == null || 
                App.ViewModel.FuseClient.ConnectionsSupportedByFlasher.Count != 1 || 
                App.FlasherViewModel.IsFlashingInProgress) return;

            App.FlasherViewModel.Connection = App.ViewModel.FuseClient.ConnectionsSupportedByFlasher[0];
        }
    }
}
