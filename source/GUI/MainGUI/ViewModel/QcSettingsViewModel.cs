// -----------------------------------------------------------------------
// <copyright file="FlasherViewModel.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.ViewModel
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Globalization;
    using System.IO;
    using System.Linq;
    using System.Net;
    using System.Text;
    using System.Threading;
    using System.Windows;
    using System.Windows.Input;
    using System.Windows.Threading;
    using System.Xml.Linq;

    using Marble.Communication;
    using Marble.Model;
    using Marble.Utilities;

    using MarbleLibrary.Commands;
    using MarbleLibrary.Utilities;

    using Microsoft.Win32;

    using TestAutomation.Gui.Marble.QC;

    public enum QcLoginStatus
    {
        Idle = 0,
        LoginInProgress = 1,
        LoginSuccessful = 2,
        LoginFailed = 3,
        LoggedOut = 4
    }

    /// <summary>
    /// QcSettingsViewModel class.
    /// </summary>
    public class QcSettingsViewModel : INotifyPropertyChanged
    {
        private MarbleQCInterface marbleQc { get; set; }

        private QcLoginStatus qcLoginStatus;

        /// <summary>
        /// Gets or sets FlashingStatus.
        /// </summary>
        public QcLoginStatus QcLoginStatus
        {
            get
            {
                return this.qcLoginStatus;
            }
            set
            {
                this.qcLoginStatus = value;
                this.OnPropertyChanged("QcLoginStatus");
                this.OnPropertyChanged("QcStatusMessage");
            }
        }

        private QcDomainStructureModel qcDomainStructure;

        /// <summary>
        /// Gets or sets the qc domain structure.
        /// </summary>
        public QcDomainStructureModel QcDomainStructure
        {
            get
            {
                return this.qcDomainStructure;
            }
            set
            {
                this.qcDomainStructure = value;
                this.OnPropertyChanged("QcDomainStructure");
            }
        }

        public QcTestSetStructure QcTestSetStructure { get; set; }

        private string username;

        /// <summary>
        /// Gets or sets the username.
        /// </summary>
        public string Username
        {
            get
            {
                return this.username;
            }
            set
            {
                this.username = value;
                this.OnPropertyChanged("Username");
            }
        }

        private string password;

        /// <summary>
        /// Gets or sets the password.
        /// </summary>
        public string Password
        {
            get
            {
                return this.password;
            }
            set
            {
                this.password = value;
                this.OnPropertyChanged("Password");
            }
        }

        private string qcServerUrl;

        /// <summary>
        /// Gets or sets the QC server URL.
        /// </summary>
        public string QcServerUrl
        {
            get
            {
                return this.qcServerUrl;
            }
            set
            {
                this.qcServerUrl = value;
                this.OnPropertyChanged("QcServerUrl");
            }
        }

        /// <summary>
        /// Gets the qc status message.
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">
        /// </exception>
        public string QcStatusMessage
        {
            get
            {
                switch (QcLoginStatus)
                {
                    case QcLoginStatus.Idle:
                        return string.Empty;
                    case QcLoginStatus.LoginInProgress:
                        return "Logging in to \"" + this.lastLoginUrl + "\" ...";
                    case QcLoginStatus.LoginSuccessful:
                        return "Logged in successfully to \"" + this.lastLoginUrl + "\".";
                    case QcLoginStatus.LoginFailed:
                        return "Login failed to \"" + this.lastLoginUrl + "\".";
                    case QcLoginStatus.LoggedOut:
                        return "Logged out.";
                    default:
                        throw new ArgumentOutOfRangeException();
                }

                return string.Empty;
            }
        }

        private string qcStatusMessageExtended;

        /// <summary>
        /// Gets the qc status message extended.
        /// </summary>
        public string QcStatusMessageExtended
        {
            get
            {
                return this.qcStatusMessageExtended;
            }
            private set
            {
                this.qcStatusMessageExtended = value;
                this.OnPropertyChanged("QcStatusMessageExtended");
            }
        }

        /// <summary>
        /// Gets or sets the qc server urls.
        /// </summary>
        public ObservableCollectionAdv<string> QcServerUrls { get; set; }

        private string lastLoginUrl { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="QcSettingsViewModel"/> class.
        /// </summary>
        public QcSettingsViewModel()
        {
            this.marbleQc = new MarbleQCInterface();

            this.QcServerUrl = "https://qc11.nokia.com/qcbin/";
            this.QcServerUrls = new ObservableCollectionAdv<string>();
            this.QcServerUrls.Add(this.QcServerUrl);
        }

        #region [ QC Settings Commands - QC Login ]

        private DelegateCommand cmdLoginToQc;

        /// <summary>
        /// Method which returns bool value indicating whether the login to QC can start.
        /// </summary>
        /// <returns>Bool value indicating whether the login to QC can start.</returns>
        public bool CanLoginToQcStart()
        {
            //if (this.marbleQc.NeedCredentials()) return true;
            if (string.IsNullOrEmpty(this.QcServerUrl) || string.IsNullOrEmpty(this.Username)) return false;
            if (this.QcLoginStatus == QcLoginStatus.LoginInProgress) return false;

            return true;
        }

        /// <summary>
        /// Command for start login to QC.
        /// </summary>
        public ICommand CmdLoginToQc
        {
            get
            {
                if (this.cmdLoginToQc == null)
                {
                    this.cmdLoginToQc = new DelegateCommand(new Action(this.LoginToQcCommandExecuted), new Func<bool>(this.CanLoginToQcStart));
                }

                return this.cmdLoginToQc;
            }
        }

        /// <summary>
        /// Login to QC.
        /// </summary>
        public void LoginToQcCommandExecuted()
        {
            Thread loginToQcThread = new Thread(this.loginToQc);
            loginToQcThread.Start();
        }

        /// <summary>
        /// Starts the login to QC.
        /// </summary>
        private void loginToQc()
        {
            try
            {
                this.lastLoginUrl = this.QcServerUrl;
                this.QcLoginStatus = QcLoginStatus.LoginInProgress;
                this.QcStatusMessageExtended = string.Empty;

                if (!this.QcServerUrls.Contains(this.QcServerUrl))
                {
                    this.QcServerUrls.Add(this.QcServerUrl);
                }

                string resultTxt = this.marbleQc.Authenticate(this.Username, this.Password, this.QcServerUrl);

                if (resultTxt == "OK")
                {
                    QcDomainStructureModel qcDomainStructure = new QcDomainStructureModel();
                    qcDomainStructure =
                        QcDomainStructureModel.CreateQcDomainStructureModelFromXml(
                            this.marbleQc.GetDomainsAndProjects());
                    qcDomainStructure.MarbleQc = this.marbleQc;
                    this.QcDomainStructure = qcDomainStructure;

                    this.QcLoginStatus = QcLoginStatus.LoginSuccessful;
                }
                else
                {
                    this.QcLoginStatus = QcLoginStatus.LoginFailed;
                }
            }
            catch (WebException e)
            {
                this.QcLoginStatus = QcLoginStatus.LoginFailed;
                this.QcStatusMessageExtended = e.Message;

                ////MessageBox.Show(e.Message + "\n\n" + e.InnerException);
            }
        }

        #endregion [ QC Settings Commands - QC Login ]

        #region [ QC Settings Commands - QC Logout ]

        private DelegateCommand cmdLogoutFromQc;

        /// <summary>
        /// Method which returns bool value indicating whether the logout from QC can start.
        /// </summary>
        /// <returns>Bool value indicating whether the login to QC can start.</returns>
        public bool CanLogoutFromQcStart()
        {
            if (this.QcLoginStatus != QcLoginStatus.LoginSuccessful) return false;

            return true;
        }

        /// <summary>
        /// Command for start logout from QC.
        /// </summary>
        public ICommand CmdLogoutFromQc
        {
            get
            {
                if (this.cmdLogoutFromQc == null)
                {
                    this.cmdLogoutFromQc = new DelegateCommand(new Action(this.LogoutFromQcCommandExecuted), new Func<bool>(this.CanLogoutFromQcStart));
                }

                return this.cmdLogoutFromQc;
            }
        }

        /// <summary>
        /// Logout from QC.
        /// </summary>
        public void LogoutFromQcCommandExecuted()
        {
            Thread logoutFromQcThread = new Thread(this.logoutFromQc);
            logoutFromQcThread.Start();
        }

        /// <summary>
        /// Starts the logout from QC.
        /// </summary>
        private void logoutFromQc()
        {
            try
            {
                this.marbleQc.LogOut();
                this.QcLoginStatus = QcLoginStatus.LoggedOut;
            }
            catch (WebException e)
            {
                MessageBox.Show(e.Message + "\n\n" + e.InnerException);
                //this.QcLoginStatus = QcLoginStatus.LoginFailed;
            }
        }

        #endregion [ QC Settings Commands - QC Logout ]

        #region [ QC Settings Commands - Retrieve Test Set ]

        private DelegateCommand cmdRetrieveTestSet;

        /// <summary>
        /// Method which returns bool value indicating whether the login to QC can start.
        /// </summary>
        /// <returns>Bool value indicating whether the login to QC can start.</returns>
        public bool CanRetrieveTestSetStart()
        {
            if (this.QcDomainStructure != null &&
                this.QcDomainStructure.SelectedDomain != null &&
                this.QcDomainStructure.SelectedDomain.SelectedProject != null &&
                this.QcDomainStructure.SelectedDomain.SelectedProject.SelectedEntity != null &&
                this.QcDomainStructure.SelectedDomain.SelectedProject.SelectedEntity.Type == QcTestSetEntityType.TestSet)
                return true;

            return false;
        }

        /// <summary>
        /// Command for start login to QC.
        /// </summary>
        public ICommand CmdRetrieveTestSet
        {
            get
            {
                if (this.cmdRetrieveTestSet == null)
                {
                    this.cmdRetrieveTestSet = new DelegateCommand(new Action(this.RetrieveTestSetCommandExecuted), new Func<bool>(this.CanRetrieveTestSetStart));
                }

                return this.cmdRetrieveTestSet;
            }
        }

        /// <summary>
        /// Login to QC.
        /// </summary>
        public void RetrieveTestSetCommandExecuted()
        {
            Thread retrieveTestSetThread = new Thread(this.retrieveTestSet);
            retrieveTestSetThread.Start();
        }

        /// <summary>
        /// Starts the retrieving selected test set.
        /// </summary>
        private void retrieveTestSet()
        {
            try
            {
                if (!this.CanRetrieveTestSetStart()) return;

                string relativeTestScriptsPath = FileUtilities.MakeRelativePath(
                    AppDomain.CurrentDomain.BaseDirectory, MarblePaths.DefaultMarbleTestScriptsDirectory);

                string fileName = MarblePaths.MarbleQcTestSetImportDirectory + @"\"
                                  + FileUtilities.ReplaceIllegalFileNameChars(this.QcDomainStructure.SelectedDomain.SelectedProject.SelectedEntity.Name, "-")
                                  + FileUtilities.DefaultMarbleTestSetFileExtension;

                XElement acquiredTestSet = null;

                List<string> testScriptDirectories = Directory.GetDirectories(MarblePaths.DefaultMarbleTestScriptsDirectory).ToList();
                testScriptDirectories.Insert(0, MarblePaths.DefaultMarbleTestScriptsDirectory);

                foreach (string directory in testScriptDirectories)
                {
                    acquiredTestSet = this.marbleQc.GetTestSet(
                        this.QcDomainStructure.SelectedDomain.Name,
                        this.QcDomainStructure.SelectedDomain.SelectedProject.Name,
                        this.QcDomainStructure.SelectedDomain.SelectedProject.SelectedEntity.Id.ToString(
                            CultureInfo.InvariantCulture),
                        directory);

                    if (acquiredTestSet != null) break;
                }

                if (acquiredTestSet == null)
                {
                    MessageBox.Show("Test scripts for selected test set could not be found from default test script directories.\n\n" + 
                                    "Test set importing failed.", "Marble - QC Import Failed!");

                    return;
                }

                acquiredTestSet.Save(fileName);

                if (MessageBox.Show(
                        "Test Set imported to \n\"" + fileName + "\"" + "\n\n" + "Load test set now?",
                        "Marble - Load Imported Test Set?",
                        MessageBoxButton.YesNo) == MessageBoxResult.Yes)
                {
                    App.ViewModel.LoadTestSetFile(new[] { fileName });
                }
            }
            catch (Exception e)
            {
                MessageBox.Show("Test set importing failed.\n\n" + e.Message, "Marble - QC Import Failed!");
            }
        }

        #endregion [ QC Settings Commands - Retrieve Test Set ]

        #region [ QC Settings Commands - Export Test Set ]

        private DelegateCommand cmdExportTestSet;

        /// <summary>
        /// Method which returns bool value indicating whether the login to QC can start.
        /// </summary>
        /// <returns>Bool value indicating whether the login to QC can start.</returns>
        public bool CanExportTestSetStart()
        {
            if (this.QcLoginStatus == QcLoginStatus.LoginSuccessful) return true;

            return false;
        }

        /// <summary>
        /// Command for start login to QC.
        /// </summary>
        public ICommand CmdExportTestSet
        {
            get
            {
                if (this.cmdExportTestSet == null)
                {
                    this.cmdExportTestSet = new DelegateCommand(new Action(this.ExportTestSetCommandExecuted), new Func<bool>(this.CanExportTestSetStart));
                }

                return this.cmdExportTestSet;
            }
        }

        /// <summary>
        /// Login to QC.
        /// </summary>
        public void ExportTestSetCommandExecuted()
        {
            Thread exportTestSetThread = new Thread(this.exportTestSet);
            exportTestSetThread.Start();
        }

        /// <summary>
        /// Starts the exporting selected test set.
        /// </summary>
        private void exportTestSet()
        {
            try
            {
                if (!this.CanExportTestSetStart()) return;

                string testSetFilePath = FileUtilities.ShowOpenFileDialogForMarbleTestSet(
                    "", Path.GetFullPath(App.ViewModel.TestSetModel.DocumentPath));

                if (!File.Exists(testSetFilePath)) return;

                bool exportSucceeded = this.marbleQc.SendResults(testSetFilePath, this.Username, this.Password);

                if (exportSucceeded)
                {
                    MessageBox.Show("Test set was successfully exported to QC.");
                }
                else
                {
                    MessageBox.Show("Exporting failed. Please check the test set results.", "Marble - QC Export Failed!");
                }
            }
            catch (Exception e)
            {
                MessageBox.Show("Exporting failed. Please check the test set results.\n\n" + e.Message, "Marble - QC Export Failed!");
            }
        }

        #endregion [ QC Settings Commands - Export Test Set ]

        #region INotifyPropertyChanged Members

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }
}
