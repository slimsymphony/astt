using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Marble
{
    using System.IO;

    using Marble.Communication;

    using MarbleLibrary.Utilities;

    using Microsoft.Win32;

    /// <summary>
    /// Interaction logic for ConnectionSelectionWindow.xaml
    /// </summary>
    public partial class ConnectionSelectionWindow : Window
    {
        public ConnectionSelectionWindow()
        {
            InitializeComponent();
            //connectionsDatagrid.ItemsSource = App.ViewModel.FuseClient.ConnectedProducts;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            OpenFuseUI();
        }

        private void OpenFuseUI()
        {
            try
            {
                string dataFromRegistry = GetDataFromRegistry("HKEY_LOCAL_MACHINE\\SOFTWARE\\Nokia\\Fuse", "InstPath");
                string text = dataFromRegistry + "\\fuse.exe";
                if (!System.IO.File.Exists(text))
                {
                    MessageBox.Show("Cannot find Fuse.exe\nSearch path: " + dataFromRegistry, "No Fuse");
                }
                else
                {
                    new System.Diagnostics.Process
                    {
                        StartInfo = 
                        {
                            FileName = text
                        }
                    }.Start();
                }
            }
            catch (Exception)
            {
                MessageBox.Show("Could not start Fuse.exe", "Unable to start Fuse");
            }
        }

        private string GetDataFromRegistry(string strPath, string strValue)
        {
            string result;
            try
            {
                result = (string)Microsoft.Win32.Registry.GetValue(strPath, strValue, null);
            }
            catch (Exception)
            {
                result = "";
            }
            return result;
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            App.ViewModel.FuseClient.ScanPhones();
        }

        private void buttonClose_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            if (!(sender is Button)) return;

            Button senderButton = sender as Button;
            string productInfoConnectionGuid = senderButton.Tag.ToString();
            ProductInfo productInfoToChange = new ProductInfo();

            foreach (ProductInfo productInfo in App.ViewModel.FuseClient.Connections.Where(productInfo => productInfo.Connection.GUID == productInfoConnectionGuid))
            {
                productInfoToChange = productInfo;
                break;
            }

            if (productInfoToChange == null) return;

            OpenFileDialog openFileDialog = new OpenFileDialog();

            if (productInfoToChange.PMD.FilePath.StartsWith(".."))
            {
                string currentPdmFileDirectoryPath =
                    FileUtilities.MergeRelativePathToAbsolutePath(
                        productInfoToChange.PMD.FilePath.Substring(0, productInfoToChange.PMD.FilePath.LastIndexOf("\\")),
                        Directory.GetCurrentDirectory());

                if (Directory.Exists(currentPdmFileDirectoryPath)) openFileDialog.InitialDirectory = currentPdmFileDirectoryPath;
            }

            openFileDialog.Filter = "PMD File|*.pmd";
            openFileDialog.Multiselect = false;
            openFileDialog.RestoreDirectory = true;

            bool? result = openFileDialog.ShowDialog();

            if (result == false) return;

            string relativeFolderPath = FileUtilities.GetRelativePath(
                Directory.GetCurrentDirectory(),
                openFileDialog.FileName.Substring(0, openFileDialog.FileName.LastIndexOf("\\")));

            productInfoToChange.PMD.FilePath = relativeFolderPath + openFileDialog.FileName.Substring(openFileDialog.FileName.LastIndexOf("\\"));
            productInfoToChange.PMD.IsUserSelected = true;
        }

    }
}
