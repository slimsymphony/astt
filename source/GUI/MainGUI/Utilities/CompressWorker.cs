using System.ComponentModel;

namespace Marble.Utilities
{
    using System.Collections.Generic;

    using Marble.ViewModel;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// BackgroundWorker for compress operation.
    /// </summary>
    public static class CompressWorker
    {
        private static readonly BackgroundWorker backgroundWorker = new BackgroundWorker();

        static CompressWorker()
        {
            backgroundWorker.DoWork += BackgroundWorkerDoWork;
            backgroundWorker.RunWorkerCompleted += BackgroundWorkerRunWorkerCompleted;
        }

        /////// <summary>
        /////// Runs the compress operation in a backgroundworker.
        /////// </summary>
        ////public static void RunCompressWorkerAsync(string documentPath)
        ////{
        ////    // Change mouse cursor to busy
        ////    System.Windows.Input.Mouse.OverrideCursor = System.Windows.Input.Cursors.Wait;

        ////    backgroundWorker.RunWorkerAsync(documentPath);
        ////}

        /// <summary>
        /// Runs the compress operation in a backgroundworker.
        /// </summary>
        public static void RunCompressWorkerAsync(TestReportViewModel testReportViewModel)
        {
            // Change mouse cursor to busy
            System.Windows.Input.Mouse.OverrideCursor = System.Windows.Input.Cursors.Wait;

            backgroundWorker.RunWorkerAsync(testReportViewModel);
        }

        /////// <summary>
        /////// Runs the time consuming operations.
        /////// </summary>
        /////// <param name="sender"></param>
        /////// <param name="e"></param>
        ////private static void BackgroundWorkerDoWork(object sender, DoWorkEventArgs e)
        ////{
        ////    string testsetDir = System.IO.Path.GetDirectoryName((string)e.Argument);
        ////    string testsetPackageName = System.IO.Path.GetFileNameWithoutExtension((string)e.Argument) + ".7z";
        ////    string testsetPackagePath = System.IO.Path.Combine(@"..\", testsetPackageName);

        ////    Compress.Create7ZipPackage(testsetPackagePath, testsetDir, (string)e.Argument);
        ////}

        /// <summary>
        /// Runs the time consuming operations.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private static void BackgroundWorkerDoWork(object sender, DoWorkEventArgs e)
        {
            TestReportViewModel testReportViewModel = ((TestReportViewModel)e.Argument);

            string testReportPackageFilePath = MarblePaths.MarbleTestReportPackageTempDirectory + "\\EmailTemp\\"
                                               + testReportViewModel.TestReport.DefaultTestReportPackageFileName;

            testReportViewModel.CompressTestReport(testReportPackageFilePath);

            //string testsetDir = System.IO.Path.GetDirectoryName((string)e.Argument);
            //string testsetPackageName = System.IO.Path.GetFileNameWithoutExtension((string)e.Argument) + ".7z";
            //string testsetPackagePath = System.IO.Path.Combine(@"..\", testsetPackageName);

            //Compress.Create7ZipPackage(testsetPackagePath, testsetDir, (string)e.Argument);
            e.Result = testReportPackageFilePath;
        }

        /// <summary>
        /// Event fired when backgroundworker completes.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private static void BackgroundWorkerRunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            // Reset mouse cursor
            System.Windows.Input.Mouse.OverrideCursor = null;

            List<string> listOfFiles = new List<string>();
            listOfFiles.Add(e.Result.ToString());

            // When Compress operation is done, call the MailWorker for displaying the Outlook New Mail dialog.
            MailWorker.RunMailWorkerAsync(listOfFiles);
        }
    }
}
