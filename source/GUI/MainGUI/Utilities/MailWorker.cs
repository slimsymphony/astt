using System;
using System.ComponentModel;
using System.IO;

using Outlook = Microsoft.Office.Interop.Outlook;

namespace Marble.Utilities
{
    using System.Collections.Generic;

    /// <summary>
    /// BackgroundWorker for email operation.
    /// </summary>
    public static class MailWorker
    {
        private static BackgroundWorker backgroundWorker = new BackgroundWorker();

        static MailWorker()
        {
            backgroundWorker.DoWork += BackgroundWorkerDoWork;
            backgroundWorker.RunWorkerCompleted += BackgroundWorkerRunWorkerCompleted;
        }

        /// <summary>
        /// Runs the email operation in a backgroundworker.
        /// </summary>
        public static void RunMailWorkerAsync(List<string> attachmentFiles)
        {
            backgroundWorker.RunWorkerAsync(attachmentFiles);
        }

        /// <summary>
        /// Runs the time consuming operations.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private static void BackgroundWorkerDoWork(object sender, DoWorkEventArgs e)
        {
            try
            {
                // Create the Outlook application.
                Outlook.Application outlookApp = new Outlook.Application();

                // Create a new mail item.
                Outlook.MailItem mailItem = (Outlook.MailItem)outlookApp.CreateItem(Outlook.OlItemType.olMailItem);

                foreach (string filePath in (List<string>)e.Argument)
                {
                    string fullFilePath = Path.GetFullPath(filePath);

                    if (File.Exists(fullFilePath))
                        mailItem.Attachments.Add(filePath);
                }

                // Show the Outlook new mail dialog.
                mailItem.Display(false);

                // Clean up.
                mailItem = null;
                outlookApp = null;
            }
            catch (Exception)
            {
            }
        }

        /// <summary>
        /// Event fired when backgroundworker completes.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private static void BackgroundWorkerRunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            //
        }
    }
}
