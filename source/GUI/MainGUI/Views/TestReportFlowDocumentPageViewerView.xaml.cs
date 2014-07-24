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
    using System.ComponentModel;
    using System.IO;
    using System.Xml.Linq;

    using Marble.Model;
    using Marble.Utilities;
    using Marble.ViewModel;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// Interaction logic for TestReportView.xaml
    /// </summary>
    public partial class TestReportFlowDocumentPageViewerView : UcBase, INotifyPropertyChanged
    {
        public TestReportFlowDocumentPageViewerView(TestResult testResult, bool isWindowModeEnabled = false, bool isBottomControlBarVisible = false)
        {
            InitializeComponent();

            this.DataContext = new TestReportViewModel(testResult);
            this.IsWindowModeEnabled = isWindowModeEnabled;
            this.IsBottomControlBarVisible = isBottomControlBarVisible;

            //this.flowDocumentPageViewer.Document =
            //    TestResultToFlowDocument.CreateFlowDocumentFromTestReportModel(
            //        ((TestReportViewModel)this.DataContext).TestReport);
        }

        private bool isWindowModeEnabled;

        public bool IsWindowModeEnabled
        {
            get
            {
                return this.isWindowModeEnabled;
            }
            set
            {
                this.isWindowModeEnabled = value;
                this.OnPropertyChanged("IsWindowModeEnabled");

                this.updateWindowMode();
            }
        }

        private bool isBottomControlBarVisible;

        public bool IsBottomControlBarVisible
        {
            get
            {
                return this.isBottomControlBarVisible;
            }
            set
            {
                this.isBottomControlBarVisible = value;
                this.OnPropertyChanged("IsBottomControlBarVisible");

                this.updateBottomControlBarVisibility();
            }
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

        private void buttonOpenTestResult_Click(object sender, RoutedEventArgs e)
        {
            string filePath = FileUtilities.ShowOpenFileDialogForContentFile(Directory.GetCurrentDirectory());

            this.DataContext = new TestReportViewModel(filePath);
        }

        private void updateWindowMode()
        {
            Visibility visibility = this.IsWindowModeEnabled ? Visibility.Visible : Visibility.Collapsed;

            this.buttonCancel.Visibility = visibility;
        }

        private void updateBottomControlBarVisibility()
        {
            Visibility visibility = this.IsBottomControlBarVisible ? Visibility.Visible : Visibility.Collapsed;

            this.gridBottomControlBar.Visibility = visibility;
        }

        #region [ INotifyPropertyChanged Members ]

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion [ INotifyPropertyChanged Members ]

        private void buttonExportToRtf_Click(object sender, RoutedEventArgs e)
        {
            TestResultToFlowDocument.SaveFlowDocumentAsRtf(
                this.flowDocumentTestReport, @"C:\Temp\rtf.test.flowdocument.rtf");
            TestResultToFlowDocument.SaveFlowDocument(this.flowDocumentTestReport, @"C:\Temp\rtf.test.flowdocument.bmp", DataFormats.Bitmap);
        }
    }
}
