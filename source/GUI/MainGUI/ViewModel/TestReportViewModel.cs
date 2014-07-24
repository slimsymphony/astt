// -----------------------------------------------------------------------
// <copyright file="TestReportViewModel.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.ViewModel
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.IO;
    using System.Linq;
    using System.Text;
    using System.Windows;

    using Marble.Model;
    using Marble.Utilities;
    using Marble.Views;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// ViewModel class for the test reports.
    /// </summary>
    public class TestReportViewModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="TestReportViewModel"/> class.
        /// </summary>
        public TestReportViewModel()
        {
            this.TestReportViewUserPreferences = new TestReportViewUserPreferences();
            this.ChangeTestReport(null as TestResult);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="TestReportViewModel"/> class.
        /// </summary>
        /// <param name="testResult">The test result.</param>
        public TestReportViewModel(TestResult testResult = null)
        {
            this.TestReportViewUserPreferences = new TestReportViewUserPreferences();
            this.ChangeTestReport(testResult);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="TestReportViewModel"/> class.
        /// </summary>
        /// <param name="testReportFilePath">The test report file path.</param>
        public TestReportViewModel(string testReportFilePath = "")
        {
            this.TestReportViewUserPreferences = new TestReportViewUserPreferences();
            this.ChangeTestReport(testReportFilePath);
        }

        public TestReportViewUserPreferences TestReportViewUserPreferences { get; set; }

        public void ChangeTestReport(TestResult testResult = null)
        {
            this.TestResult = null;
            this.TestResult = testResult;

            if (testResult == null) return;

            this.TestReport = TestResultXmlParser.CreateTestReport(FileUtilities.ConvertRelativePathToAbsolutePath(testResult.ResultPath));
        }

        public void ChangeTestReport(string testReportFilePath = null)
        {
            this.TestResult = null;

            if (FileUtilities.CheckWhetherFileIsMarbleTestReportPackage(testReportFilePath))
            {
                List<string> fileList = Compress.GetFileNamesFrom7ZipPackage(testReportFilePath);
                string outputDirectory = MarblePaths.MarbleTestReportPackageTempDirectory + "\\"
                                         +
                                         FileUtilities.GetFileName(testReportFilePath.Remove(testReportFilePath.LastIndexOf(FileUtilities.DefaultMarbleTestReportPackageFileExtension, System.StringComparison.Ordinal)));

                Compress.Extract7ZipPackage(testReportFilePath, outputDirectory);

                foreach (string filePath in fileList.Where(filePath => filePath.EndsWith(FileUtilities.DefaultMarbleTestReportFileExtension)))
                {
                    testReportFilePath = outputDirectory + "\\" + filePath;
                    break;
                }
            }

            this.TestReport = TestResultXmlParser.CreateTestReport(testReportFilePath);
        }

        private TestResult testResult;

        /// <summary>
        /// Gets or sets the test result.
        /// </summary>
        public TestResult TestResult
        {
            get { return this.testResult; }
            set
            {
                this.testResult = value;
                this.OnPropertyChanged("TestResult");
            }
        }

        private TestReportModel testReport;

        /// <summary>
        /// Gets or sets the test report.
        /// </summary>
        public TestReportModel TestReport
        {
            get { return this.testReport; }
            set
            {
                this.testReport = value;
                this.OnPropertyChanged("TestReport");
            }
        }

        private TestReportViewMode viewMode;

        public TestReportViewMode ViewMode
        {
            get
            {
                return this.viewMode;
            }
            set
            {
                this.viewMode = value;
                this.OnPropertyChanged("ViewMode");
            }
        }
        
        /// <summary>
        /// The compress test report to 7zip package.
        /// </summary>
        /// <param name="saveAsFilePath">The save as file path.</param>
        /// <returns>File path where compressed test report was saved.</returns>
        public string CompressTestReport(string saveAsFilePath = "")
        {
            if (this.TestReport == null) return null;

            if (string.IsNullOrEmpty(saveAsFilePath))
            {
                saveAsFilePath = FileUtilities.ShowSaveAsFileDialogForMarbleTestReportPackage(
                    this.TestReport.TestResultXmlFilePath.Remove(this.TestReport.TestResultXmlFilePath.LastIndexOf("\\", System.StringComparison.Ordinal)), 
                    this.TestReport.DefaultTestReportPackageFileName);
            }

            if (saveAsFilePath == this.TestReport.DefaultTestReportPackageFileName) return null;

            string testReportPlaylistFilePath = 
                MarblePaths.MarbleTestReportPackageTempDirectory 
                + "\\" + this.TestReport.DefaultTestReportPackageFileName.Remove(
                    this.TestReport.DefaultTestReportPackageFileName.LastIndexOf("."))
                + FileUtilities.DefaultMarbleTestReportFileExtension;

            TestResultXmlParser.CreateTestReportPlaylistXml(this.TestReport, testReportPlaylistFilePath);

            Compress.Create7ZipPackage(saveAsFilePath, this.TestReport.TestCaseReport.NeededFiles);

            return saveAsFilePath;
        }

        /// <summary>
        /// The export test report as document.
        /// </summary>
        /// <param name="saveAsFilePath">The save as file path.</param>
        /// <param name="exportedTestReportFilePath">The exported test report file path.</param>
        public void ExportTestReportAsDocument(string saveAsFilePath, string exportedTestReportFilePath = "")
        {
            if (string.IsNullOrEmpty(saveAsFilePath)) return;

            Window screencaptureWindow = new Window();
            TestReportView testReportView;
            
            if (string.IsNullOrEmpty(exportedTestReportFilePath))
                testReportView = new TestReportView(this.TestResult, false, false);
            else
                testReportView = new TestReportView(exportedTestReportFilePath, false, false);

            testReportView.ParentWindow = screencaptureWindow;
            screencaptureWindow.Content = testReportView;
            screencaptureWindow.SizeToContent = SizeToContent.Height;
            screencaptureWindow.Width = 800;

            // Wíndow startup location is set to position where user can't see it.
            screencaptureWindow.WindowStartupLocation = WindowStartupLocation.Manual;
            screencaptureWindow.Left = 2000;
            screencaptureWindow.Top = 2000;
            screencaptureWindow.Show();

            PdfUtilities.CreatePdfFromImages(saveAsFilePath, testReportView.SaveReportToScreenshotImages());

            screencaptureWindow.Close();
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
    }

    public enum TestReportViewMode
    {
        Default = 0,
        Rsa = 1,
        Mtbf = 2
    }
}
