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
    using System.IO;
    using System.Linq;
    using System.Text;
    using System.Threading;
    using System.Windows;
    using System.Windows.Input;
    using System.Windows.Threading;

    using Marble.Communication;
    using Marble.Utilities;

    using MarbleLibrary.Commands;
    using MarbleLibrary.Utilities;

    public enum FlashingStatus
    {
        Idle = 0,
        Flashing = 1,
        Succesful = 2,
        Failed = 3
    }

    /// <summary>
    /// FlasherViewModel class.
    /// </summary>
    public class FlasherViewModel : INotifyPropertyChanged
    {
        public FlasherViewModel()
        {
            this.VariantCollection = new ObservableCollectionAdv<KeyValuePair<string, string>>();
            this.ForcedAdlArgumentValue = AdlValueEnum.Adl4;
        }

        public ObservableCollectionAdv<KeyValuePair<string, string>> VariantCollection { get; set; }

        private KeyValuePair<string, string> variant;

        /// <summary>
        /// Gets or sets the variant.
        /// </summary>
        public KeyValuePair<string, string> Variant
        {
            get
            {
                return this.variant;
            }
            set
            {
                this.variant = value;
                this.OnPropertyChanged("Variant");
            }
        }

        private FlashingStatus flashingStatus;

        /// <summary>
        /// Gets or sets FlashingStatus.
        /// </summary>
        public FlashingStatus FlashingStatus
        {
            get
            {
                return this.flashingStatus;
            }
            set
            {
                this.flashingStatus = value;
                this.OnPropertyChanged("FlashingStatus");
                this.OnPropertyChanged("IsFlashingInProgress");
                this.OnPropertyChanged("StatusText");
            }
        }

        public ConnectorState State { get { return App.ViewModel.MarbleConnector.State; } }

        private string consoleOutputText;

        /// <summary>
        /// Gets or sets ConsoleOutputText.
        /// </summary>
        public string ConsoleOutputText
        {
            get
            {
                return this.consoleOutputText;
            }
            set
            {
                this.consoleOutputText = value;
                this.OnPropertyChanged("ConsoleOutputText");
            }
        }

        private readonly Mutex messageMutex = new Mutex();

        /// <summary>
        /// Gets a value indicating whether flashing is currently in progress.
        /// </summary>
        public bool IsFlashingInProgress { get { return this.FlashingStatus == FlashingStatus.Flashing; } }

        private bool isDeadPhoneFlashModeEnabled;

        /// <summary>
        /// Gets or sets a value indicating whether dead phone flash mode is enabled.
        /// </summary>
        public bool IsDeadPhoneFlashModeEnabled
        {
            get
            {
                return this.isDeadPhoneFlashModeEnabled;
            }
            set
            {
                this.isDeadPhoneFlashModeEnabled = value;

                if (value)
                {
                    this.IsFirmwareFlashModeEnabled = false;
                    this.IsMiddlewareOnlyFlashModeEnabled = false;
                }

                if (this.FlashingStatus == FlashingStatus.Succesful ||
                    this.FlashingStatus == FlashingStatus.Failed)
                    this.FlashingStatus = FlashingStatus.Idle;

                this.OnPropertyChanged("IsDeadPhoneFlashModeEnabled");
                this.OnPropertyChanged("Connection");
                this.OnPropertyChanged("IsConnectionSupported");
                this.OnPropertyChanged("ErrorList");
                this.OnPropertyChanged("ErrorText");
                this.OnPropertyChanged("WarningList");
                this.OnPropertyChanged("WarningText");
            }
        }

        private bool isFirmwareFlashModeEnabled;

        /// <summary>
        /// Gets or sets a value indicating whether firmware flash mode is enabled.
        /// </summary>
        public bool IsFirmwareFlashModeEnabled
        {
            get
            {
                return this.isFirmwareFlashModeEnabled;
            }
            set
            {
                this.isFirmwareFlashModeEnabled = value;

                if (value)
                {
                    this.IsDeadPhoneFlashModeEnabled = false;
                    this.IsMiddlewareOnlyFlashModeEnabled = false;
                }

                if (this.FlashingStatus == FlashingStatus.Succesful ||
                    this.FlashingStatus == FlashingStatus.Failed)
                    this.FlashingStatus = FlashingStatus.Idle;

                this.OnPropertyChanged("IsFirmwareFlashModeEnabled");
                this.OnPropertyChanged("Connection");
                this.OnPropertyChanged("IsConnectionSupported");
                this.OnPropertyChanged("ErrorList");
                this.OnPropertyChanged("ErrorText");
                this.OnPropertyChanged("WarningList");
                this.OnPropertyChanged("WarningText");
            }
        }

        private bool isMiddlewareOnlyFlashModeEnabled;

        /// <summary>
        /// Gets or sets a value indicating whether middleware only flash mode is enabled.
        /// </summary>
        public bool IsMiddlewareOnlyFlashModeEnabled
        {
            get
            {
                return this.isMiddlewareOnlyFlashModeEnabled;
            }
            set
            {
                this.isMiddlewareOnlyFlashModeEnabled = value;

                if (value)
                {
                    this.IsDeadPhoneFlashModeEnabled = false;
                    this.IsFirmwareFlashModeEnabled = false;
                }

                if (this.FlashingStatus == FlashingStatus.Succesful ||
                    this.FlashingStatus == FlashingStatus.Failed)
                    this.FlashingStatus = FlashingStatus.Idle;

                this.OnPropertyChanged("IsMiddlewareOnlyFlashModeEnabled");
                this.OnPropertyChanged("Connection");
                this.OnPropertyChanged("IsConnectionSupported");
                this.OnPropertyChanged("ErrorList");
                this.OnPropertyChanged("ErrorText");
                this.OnPropertyChanged("WarningList");
                this.OnPropertyChanged("WarningText");
                this.OnPropertyChanged("IsUserSelectionForAdlValueRequired");
            }
        }

        private bool isPreviousFlashingSuccessful;

        /// <summary>
        /// Gets or sets a value indicating whether is previous flashing successful.
        /// </summary>
        public bool IsPreviousFlashingSuccessful
        {
            get
            {
                return this.isPreviousFlashingSuccessful;
            }
            set
            {
                this.isPreviousFlashingSuccessful = value;
                this.OnPropertyChanged("IsPreviousFlashingSuccessful");
            }
        }

        private ProductInfo connection;

        /// <summary>
        /// Gets or sets ProductInfo of currently selected connection.
        /// </summary>
        public ProductInfo Connection
        {
            get
            {
                return this.connection;
            }
            set
            {
                this.connection = value;

                // Connection is not updated to the GUI when flashing is in progress.
                if (this.IsFlashingInProgress) return;

                this.OnPropertyChanged("Connection");
                this.OnPropertyChanged("IsDeadPhoneFlashModeEnabled");
                this.OnPropertyChanged("IsConnectionSupported");
                this.OnPropertyChanged("IsMcuFilePossiblyWrongFile");
                this.OnPropertyChanged("ErrorList");
                this.OnPropertyChanged("ErrorText");
                this.OnPropertyChanged("WarningList");
                this.OnPropertyChanged("WarningText");
                this.OnPropertyChanged("IsUserSelectionForAdlValueRequired");
            }
        }

        /// <summary>
        /// Gets a value indicating whether currently selected connection is supported.
        /// </summary>
        public bool IsConnectionSupported
        {
            get
            {
                if (this.IsDeadPhoneFlashModeEnabled) return true;

                if (this.Connection == null) return false;

                return this.Connection.Connection.Type == EnumConnectionType.USB ||
                       this.connection.Connection.Type == EnumConnectionType.NFPD_USB || 
                       this.connection.Connection.Type == EnumConnectionType.NFPD_TCP;
            }
        }

        /// <summary>
        /// Gets a value indicating whether is user selection for ADL value is required.
        /// </summary>
        public bool IsUserSelectionForAdlValueRequired
        {
            get
            {
                if (this.IsDeadPhoneFlashModeEnabled)
                {
                    if (this.Connection != null 
                        && this.Connection.Version != null 
                        && !string.IsNullOrEmpty(this.Connection.Version.RMCode)
                        && this.Connection.Connection.Type == EnumConnectionType.USB
                        && !string.IsNullOrEmpty(this.getAdlArgumentAccordingToRmCode(this.Connection.Version.RMCode)))
                    {
                        return false;
                    }

                    if (string.IsNullOrEmpty(this.McuFilePath)) return true;

                    return string.IsNullOrEmpty(this.getAdlArgumentAccordingToMcuFilePath(this.McuFilePath));
                }

                if (this.Connection == null) return false;

                if (this.Connection.Connection.Type != EnumConnectionType.USB) return false;

                return string.IsNullOrEmpty(this.getAdlArgumentAccordingToRmCode());
            }
        }

        private string mcuFilePath;

        /// <summary>
        /// Gets or sets file path of the MCU file.
        /// </summary>
        public string McuFilePath
        {
            get
            {
                return this.mcuFilePath;
            }
            set
            {
                this.mcuFilePath = value;

                if (this.FlashingStatus == FlashingStatus.Succesful ||
                    this.FlashingStatus == FlashingStatus.Failed)
                    this.FlashingStatus = FlashingStatus.Idle;

                this.OnPropertyChanged("McuFilePath");
                this.OnPropertyChanged("McuFileExists");
                this.OnPropertyChanged("HasMcuFileCorrectFileExtension");
                this.OnPropertyChanged("IsMcuFilePossiblyWrongFile");
                this.OnPropertyChanged("ErrorList");
                this.OnPropertyChanged("ErrorText");
                this.OnPropertyChanged("WarningList");
                this.OnPropertyChanged("WarningText");
                this.OnPropertyChanged("IsUserSelectionForAdlValueRequired");
            }
        }

        private string contentFilePath;

        /// <summary>
        /// Gets or sets file path of the content file.
        /// </summary>
        public string ContentFilePath
        {
            get
            {
                return this.contentFilePath;
            }
            set
            {
                this.contentFilePath = value;

                if (this.FlashingStatus == FlashingStatus.Succesful ||
                    this.FlashingStatus == FlashingStatus.Failed)
                    this.FlashingStatus = FlashingStatus.Idle;

                this.OnPropertyChanged("ContentFilePath");
                this.OnPropertyChanged("ContentFileExists");
                this.OnPropertyChanged("HasContentFileCorrectFileExtension");
                this.OnPropertyChanged("ErrorList");
                this.OnPropertyChanged("ErrorText");
                this.OnPropertyChanged("WarningList");
                this.OnPropertyChanged("WarningText");
            }
        }

        private string languageFilePath;

        /// <summary>
        /// Gets or sets file path of the language file.
        /// </summary>
        public string LanguageFilePath
        {
            get
            {
                return this.languageFilePath;
            }
            set
            {
                this.languageFilePath = value;

                if (this.FlashingStatus == FlashingStatus.Succesful ||
                    this.FlashingStatus == FlashingStatus.Failed)
                    this.FlashingStatus = FlashingStatus.Idle;

                this.OnPropertyChanged("LanguageFilePath");
                this.OnPropertyChanged("LanguageFileExists");
                this.OnPropertyChanged("HasLanguageFileCorrectFileExtension");
                this.OnPropertyChanged("ErrorList");
                this.OnPropertyChanged("ErrorText");
                this.OnPropertyChanged("WarningList");
                this.OnPropertyChanged("WarningText");
            }
        }

        private string eraseFilePath;

        /// <summary>
        /// Gets or sets file path of the erase file.
        /// </summary>
        public string EraseFilePath
        {
            get
            {
                return this.eraseFilePath;
            }
            set
            {
                this.eraseFilePath = value;

                if (this.FlashingStatus == FlashingStatus.Succesful ||
                    this.FlashingStatus == FlashingStatus.Failed)
                    this.FlashingStatus = FlashingStatus.Idle;

                this.OnPropertyChanged("EraseFilePath");
                this.OnPropertyChanged("EraseFileExists");
                this.OnPropertyChanged("HasEraseFileCorrectFileExtension");
                this.OnPropertyChanged("ErrorList");
                this.OnPropertyChanged("ErrorText");
                this.OnPropertyChanged("WarningList");
                this.OnPropertyChanged("WarningText");
            }
        }

        private string firmwareDirectoryPath;

        /// <summary>
        /// Gets or sets the firmware directory path.
        /// </summary>
        public string FirmwareDirectoryPath
        {
            get
            {
                return this.firmwareDirectoryPath;
            }
            set
            {
                this.firmwareDirectoryPath = value;

                if (this.FlashingStatus == FlashingStatus.Succesful ||
                    this.FlashingStatus == FlashingStatus.Failed)
                    this.FlashingStatus = FlashingStatus.Idle;

                this.OnPropertyChanged("FirmwareDirectoryPath");
                this.OnPropertyChanged("FirmwareDirectoryPathIsValid");
                this.OnPropertyChanged("HasFirmwareFolderCorrectFiles");
                this.OnPropertyChanged("ErrorList");
                this.OnPropertyChanged("ErrorText");
                this.OnPropertyChanged("WarningList");
                this.OnPropertyChanged("WarningText");
            }
        }

        private AdlValueEnum forcedAdlArgumentValue;

        public AdlValueEnum ForcedAdlArgumentValue
        {
            get
            {
                return this.forcedAdlArgumentValue;
            }
            set
            {
                this.forcedAdlArgumentValue = value;
                this.OnPropertyChanged("ForcedAdlArgumentValue");
            }
        }

        /// <summary>
        /// Gets a value indicating whether MCU file exists.
        /// </summary>
        public bool McuFileExists { get { return File.Exists(this.McuFilePath); } }

        /// <summary>
        /// Gets a value indicating whether content file exists.
        /// </summary>
        public bool ContentFileExists { get { return File.Exists(this.ContentFilePath); } }

        /// <summary>
        /// Gets a value indicating whether language file exists.
        /// </summary>
        public bool LanguageFileExists { get { return File.Exists(this.LanguageFilePath); } }

        /// <summary>
        /// Gets a value indicating whether erase file exists.
        /// </summary>
        public bool EraseFileExists { get { return File.Exists(this.EraseFilePath); } }

        /// <summary>
        /// Gets a value indicating whether MCU file has correct file extension.
        /// </summary>
        public bool HasMcuFileCorrectFileExtension
        {
            get { return FileUtilities.IsMcuswFile(this.mcuFilePath); }
        }

        /// <summary>
        /// Gets a value indicating whether content file has correct file extension.
        /// </summary>
        public bool HasContentFileCorrectFileExtension 
        {
            get { return FileUtilities.IsContentFile(this.contentFilePath); }
        }

        /// <summary>
        /// Gets a value indicating whether language file has correct file extension.
        /// </summary>
        public bool HasLanguageFileCorrectFileExtension
        {
            get { return FileUtilities.IsLanguageFile(this.LanguageFilePath); }
        }

        /// <summary>
        /// Gets a value indicating whether erase file has correct file extension.
        /// </summary>
        public bool HasEraseFileCorrectFileExtension
        {
            get { return FileUtilities.IsEraseFile(this.EraseFilePath); }
        }

        public bool HasFirmwareFolderCorrectFiles
        {
            get
            {
                if (string.IsNullOrEmpty(this.FirmwareDirectoryPath)) return false;
                if (!Directory.Exists(this.FirmwareDirectoryPath)) return false;
                if (this.Connection == null) return false;

                bool hasFolderCorrectFiles = FileUtilities.CheckWhetherDirectoryContainsFirmwareUpdateFiles(this.FirmwareDirectoryPath, this.Connection.Version.RMCode);

                if (!hasFolderCorrectFiles) return false;

                List<KeyValuePair<string, string>> variants =
                    FileUtilities.GetVariantCodesFromDirectoryContainingFirmwareUpdateFiles(
                        this.FirmwareDirectoryPath, this.Connection.Version.RMCode);

                if (this.VariantCollection != null && this.VariantCollection.Count > 0 && this.VariantCollection.Count == variants.Count)
                {
                    //foreach (KeyValuePair<string, string> variant in variants.Where(variant => !this.VariantCollection.Contains(variant)))
                    //{
                    //    this.VariantCollection = new ObservableCollectionAdv<string>(variants);
                    //    break;
                    //}
                }
                else
                {
                    this.VariantCollection = new ObservableCollectionAdv<KeyValuePair<string, string>>(variants);
                    
                    if (this.VariantCollection.Count > 0)
                        this.Variant = this.VariantCollection[0];
                }

                return true;
            }
        }

        /// <summary>
        /// Gets a value indicating whether MCU file is possibly wrong file.
        /// </summary>
        public bool IsMcuFilePossiblyWrongFile
        {
            get
            {
                if (this.Connection == null) return false;

                if (string.IsNullOrEmpty(this.McuFilePath)) return true;
                if (this.McuFilePath.ToLower().Contains(this.Connection.Version.RMCode.ToLower()) ||
                    this.McuFilePath.ToLower().Contains(this.Connection.Version.RMCode.Replace("-", string.Empty).ToLower())) return false;

                return true;
            }
        }

        /// <summary>
        /// Gets a value indicating whether product has native Marble support for USB flashing.
        /// </summary>
        public bool HasProductNativeMarbleSupportForUsbFlashing
        {
            get
            {
                return !string.IsNullOrEmpty(this.getAdlArgumentAccordingToRmCode());
            }
        }

        /// <summary>
        /// Gets message about current status.
        /// </summary>
        public string StatusText
        {
            get
            {
                switch (this.FlashingStatus)
                {
                    case FlashingStatus.Idle:
                        return string.Empty;
                    case FlashingStatus.Flashing:
                        return "Flashing is in progress. Please follow instructions below.";
                    case FlashingStatus.Succesful:
                        return "Flashing completed succesfully.";
                    case FlashingStatus.Failed:
                        return "Flashing failed.";
                }

                return null;
            }
        }

        /// <summary>
        /// Gets the current error messages as one string.
        /// </summary>
        public string ErrorText { get { return this.ErrorList.Aggregate(string.Empty, (current, error) => current + ("- " + error + "\n")).TrimEnd('\n'); } }

        /// <summary>
        /// Gets the list of current error messages.
        /// </summary>
        public List<string> ErrorList
        {
            get
            {
                List<string> errorList = new List<string>();

                if (!this.IsConnectionSupported) 
                    errorList.Add("Connection type is not supported.");
                if (!this.McuFileExists && !string.IsNullOrEmpty(this.McuFilePath)) 
                    errorList.Add("MCU file was not found.");
                if (!this.ContentFileExists && !string.IsNullOrEmpty(this.ContentFilePath)) 
                    errorList.Add("Content file was not found.");

                if (!string.IsNullOrEmpty(this.ContentFilePath))
                {
                    if (string.IsNullOrEmpty(this.LanguageFilePath)) 
                        errorList.Add("Language file is needed when content file is used.");
                    if (!this.LanguageFileExists && !string.IsNullOrEmpty(this.LanguageFilePath)) 
                        errorList.Add("Language file was not found.");
                }

                if (this.IsFirmwareFlashModeEnabled)
                {
                    if (!this.HasFirmwareFolderCorrectFiles) 
                        errorList.Add("Folder doesn't not contain firmware update files or doesn't exist.");
                    if (this.Connection == null) 
                        errorList.Add("Product is not connected or found.");
                }

                if (this.IsMiddlewareOnlyFlashModeEnabled)
                {
                    if (!this.EraseFileExists && !string.IsNullOrEmpty(this.EraseFilePath)) 
                        errorList.Add("Erase file was not found.");
                    if (this.Connection == null) 
                        errorList.Add("Product is not connected or found.");
                }

                return errorList;
            }
        }

        /// <summary>
        /// Gets the current warning messages as one string.
        /// </summary>
        public string WarningText
        {
            get
            {
                return this.WarningList.Aggregate(string.Empty, (current, warning) => current + ("- " + warning + "\n")).TrimEnd('\n');
            }
        }

        /// <summary>
        /// Gets the list of current warning messages.
        /// By default an instructive text is displayed.
        /// </summary>
        public List<string> WarningList
        {
            get
            {
                List<string> warningList = new List<string>();

                if (!this.HasMcuFileCorrectFileExtension && !string.IsNullOrEmpty(this.McuFilePath)) 
                    warningList.Add("MCU file has non-default file extension, check the file.");
                if (!this.HasContentFileCorrectFileExtension && !string.IsNullOrEmpty(this.ContentFilePath)) 
                    warningList.Add("Content file has non-default file extension, check the file.");
                
                if (!string.IsNullOrEmpty(this.EraseFilePath))
                    if (this.HasEraseFileWarning && this.IsMiddlewareOnlyFlashModeEnabled) 
                        warningList.Add("Erase file has non-default file extension, check the file.");

                if (!string.IsNullOrEmpty(this.ContentFilePath))
                    if (!this.HasLanguageFileCorrectFileExtension && !string.IsNullOrEmpty(this.LanguageFilePath)) 
                        warningList.Add("Language file has non-default file extension, check the file.");

                if (this.IsMcuFilePossiblyWrongFile && !string.IsNullOrEmpty(this.McuFilePath) && this.Connection != null) 
                    warningList.Add("MCU file path doesn't contain product type " + this.Connection.Version.RMCode + ", check the file.");

                if (warningList.Count == 0 && !this.McuFileExists && !this.ContentFileExists && !this.IsFirmwareFlashModeEnabled)
                    warningList.Add("Start by dragging and dropping flash files or browse them separately.");
                
                return warningList;
            }
        }

        /// <summary>
        /// Gets a value indicating whether MCU file has warning.
        /// </summary>
        public bool HasMcuFileWarning
        {
            get
            {
                return !this.HasMcuFileCorrectFileExtension && !string.IsNullOrEmpty(this.McuFilePath);
            }
        }

        /// <summary>
        /// Gets a value indicating whether content file has warning.
        /// </summary>
        public bool HasContentFileWarning
        {
            get
            {
                return !this.HasContentFileCorrectFileExtension && !string.IsNullOrEmpty(this.ContentFilePath);
            }
        }

        /// <summary>
        /// Gets a value indicating whether language file has warning.
        /// </summary>
        public bool HasLanguageFileWarning
        {
            get
            {
                if (string.IsNullOrEmpty(this.ContentFilePath)) return false;

                return !this.HasLanguageFileCorrectFileExtension && !string.IsNullOrEmpty(this.LanguageFilePath);
            }
        }

        /// <summary>
        /// Gets a value indicating whether erase file has warning.
        /// </summary>
        public bool HasEraseFileWarning
        {
            get
            {
                return !this.HasEraseFileCorrectFileExtension && !string.IsNullOrEmpty(this.EraseFilePath);
            }
        }

        #region [ Flashing Command ]

        private DelegateCommand cmdStartFlashing;

        /// <summary>
        /// Method which returns bool value indicating whether the flashing can start.
        /// </summary>
        /// <returns>Bool value indicating whether the flashing can start.</returns>
        public bool CanFlashingStart()
        {
            if (this.FlashingStatus == FlashingStatus.Flashing) return false;
            if (this.ErrorList.Count > 0) return false;
            if ((!this.ContentFileExists && !string.IsNullOrEmpty(this.ContentFilePath)) || !this.IsConnectionSupported) return false;
            if (!string.IsNullOrEmpty(this.ContentFilePath) && !this.LanguageFileExists) return false;
            
            if (this.IsFirmwareFlashModeEnabled)
            {
                if (!this.HasFirmwareFolderCorrectFiles || string.IsNullOrEmpty(this.Variant.Value)) return false;
            }
            
            if (this.IsMiddlewareOnlyFlashModeEnabled)
            {
                if (!this.EraseFileExists) return false;
            }

            if (!this.IsFirmwareFlashModeEnabled && !this.IsMiddlewareOnlyFlashModeEnabled)
            {
                if (string.IsNullOrEmpty(this.McuFilePath) || string.IsNullOrEmpty(this.ContentFilePath)) return false;
            }

            return true;
        }

        /// <summary>
        /// Command for start flashing the connected product.
        /// </summary>
        public ICommand CmdStartFlashing
        {
            get
            {
                if (this.cmdStartFlashing == null)
                {
                    this.cmdStartFlashing = new DelegateCommand(new Action(this.StartFlashingCommandExecuted), new Func<bool>(this.CanFlashingStart));
                }

                return this.cmdStartFlashing;
            }
        }

        /// <summary>
        /// Shows Flasher dialog.
        /// </summary>
        public void StartFlashingCommandExecuted()
        {
            Thread flashingThread = this.IsFirmwareFlashModeEnabled ? new Thread(this.startFlashingWithFirmwareUpdate) : new Thread(this.startFlashing);
            flashingThread.Start();
        }

        /// <summary>
        /// Starts the flashing.
        /// </summary>
        private void startFlashing()
        {
            if ((this.Connection == null || this.Connection.Connection == null) && !this.IsDeadPhoneFlashModeEnabled) return;

            string connectionGuid = this.IsDeadPhoneFlashModeEnabled ? "0" : this.Connection.Connection.GUID;

            // Disable product scans during the flashing
            App.ViewModel.FuseClient.AllowProductScan = false;

            this.FlashingStatus = FlashingStatus.Flashing;
            this.ConsoleOutputText = "***Flashing started***\n";

            Process flashingProcess = new Process();

            string arguments = this.getFlasherArguments(connectionGuid);

            flashingProcess.StartInfo.FileName = MarblePaths.MarbleFlasherFilePath;
            flashingProcess.StartInfo.Arguments = arguments;
            flashingProcess.StartInfo.WorkingDirectory = MarblePaths.MarbleFlasherDirectory;
            flashingProcess.StartInfo.UseShellExecute = false;
            flashingProcess.StartInfo.RedirectStandardOutput = true;
            flashingProcess.StartInfo.RedirectStandardError = true;
            flashingProcess.EnableRaisingEvents = true;
            flashingProcess.StartInfo.CreateNoWindow = true;

            flashingProcess.OutputDataReceived += new DataReceivedEventHandler(this.flashingProcess_OutputDataReceived);
            flashingProcess.ErrorDataReceived += new DataReceivedEventHandler(this.flashingProcess_OutputDataReceived);

            flashingProcess.Start();

            flashingProcess.BeginErrorReadLine();
            flashingProcess.BeginOutputReadLine();

            flashingProcess.WaitForExit();

            App.ViewModel.FuseClient.AllowProductScan = true;

            // Flashing status is changed for the first time because connection cannot be changed when flashing status is in progress.
            switch (flashingProcess.ExitCode)
            {
                case 0:
                    this.FlashingStatus = FlashingStatus.Succesful;
                    this.IsPreviousFlashingSuccessful = true;
                    break;
                case 1:
                    this.FlashingStatus = FlashingStatus.Failed;
                    this.IsPreviousFlashingSuccessful = false;
                    break;
            }

            foreach (ProductInfo connectedProduct in App.ViewModel.FuseClient.Connections.Where(connectedProduct => connectedProduct.Connection.GUID == connectionGuid))
                this.Connection = connectedProduct;

            // Flashing status is changed for the second time because changing the connection changes flashing status to idle.
            switch (flashingProcess.ExitCode)
            {
                case 0:
                    this.FlashingStatus = FlashingStatus.Succesful;
                    break;
                case 1:
                    this.FlashingStatus = FlashingStatus.Failed;
                    break;
            }
        }

        private void startFlashingWithFirmwareUpdate()
        {
            if (!this.IsFirmwareFlashModeEnabled) return;
            if (this.Connection == null || this.Connection.Connection == null) return;

            string connectionGuid = this.Connection.Connection.GUID;

            // Disable product scans during the flashing
            App.ViewModel.FuseClient.AllowProductScan = false;

            this.FlashingStatus = FlashingStatus.Flashing;
            this.ConsoleOutputText = "***Firmware Upgrade Started***\n";

            Process flashingProcess = new Process();

            string arguments = this.getFirmwareUpdaterArguments(connectionGuid);

            flashingProcess.StartInfo.FileName = MarblePaths.MarbleFirmwareUpdaterFileName;
            flashingProcess.StartInfo.Arguments = arguments;
            flashingProcess.StartInfo.WorkingDirectory = MarblePaths.MarbleFlasherDirectory;
            flashingProcess.StartInfo.UseShellExecute = false;
            flashingProcess.StartInfo.RedirectStandardOutput = true;
            flashingProcess.StartInfo.RedirectStandardError = true;
            flashingProcess.EnableRaisingEvents = true;
            flashingProcess.StartInfo.CreateNoWindow = true;

            flashingProcess.OutputDataReceived += new DataReceivedEventHandler(this.flashingProcess_OutputDataReceived);
            flashingProcess.ErrorDataReceived += new DataReceivedEventHandler(this.flashingProcess_OutputDataReceived);

            flashingProcess.Start();

            flashingProcess.BeginErrorReadLine();
            flashingProcess.BeginOutputReadLine();

            flashingProcess.WaitForExit();

            App.ViewModel.FuseClient.AllowProductScan = true;

            // Flashing status is changed for the first time because connection cannot be changed when flashing status is in progress.
            switch (flashingProcess.ExitCode)
            {
                case 0:
                    this.FlashingStatus = FlashingStatus.Succesful;
                    this.IsPreviousFlashingSuccessful = true;
                    break;
                case 1:
                    this.FlashingStatus = FlashingStatus.Failed;
                    this.IsPreviousFlashingSuccessful = false;
                    break;
            }

            foreach (ProductInfo connectedProduct in App.ViewModel.FuseClient.Connections.Where(connectedProduct => connectedProduct.Connection.GUID == connectionGuid))
                this.Connection = connectedProduct;

            // Flashing status is changed for the second time because changing the connection changes flashing status to idle.
            switch (flashingProcess.ExitCode)
            {
                case 0:
                    this.FlashingStatus = FlashingStatus.Succesful;
                    break;
                case 1:
                    this.FlashingStatus = FlashingStatus.Failed;
                    break;
            }
        }

        /// <summary>
        /// Gets arguments for Flasher executable.
        /// </summary>
        /// <param name="connectionGuid">The connection guid.</param>
        /// <returns>Flasher arguments.</returns>
        private string getFlasherArguments(string connectionGuid = "")
        {
            if (string.IsNullOrEmpty(connectionGuid))
                connectionGuid = this.IsDeadPhoneFlashModeEnabled ? "0" : this.Connection.Connection.GUID;

            string arguments;

            if (this.IsMiddlewareOnlyFlashModeEnabled)
            {   // Arguments for Middleware Only Flashing mode.
                arguments = string.Format(
                    "{0} {1} {2}",
                    "--guid " + connectionGuid,
                    "--mcusw " + this.McuFilePath,
                    "--erase " + this.EraseFilePath);
            }
            else if (string.IsNullOrEmpty(this.ContentFilePath))
            {   // Arguments for flashing when content file is not used.
                arguments = string.Format(
                    "{0} {1}",
                    "--guid " + connectionGuid,
                    "--mcusw " + this.McuFilePath);
            }
            else
            {   // Arguments for normal flashing.
                arguments = string.Format(
                    "{0} {1} {2} {3}",
                    "--guid " + connectionGuid,
                    "--rofs " + this.LanguageFilePath,
                    "--image " + this.ContentFilePath,
                    "--mcusw " + this.McuFilePath);
            }

            // ADL value is set automatically depending on connection and the product RM code.
            if ((this.Connection != null && this.Connection.Connection.Type == EnumConnectionType.USB) || this.IsDeadPhoneFlashModeEnabled)
            {
                if (this.IsUserSelectionForAdlValueRequired)
                    arguments += " " + "--adl " + (int)this.ForcedAdlArgumentValue;
                else
                    arguments += " " + "--adl " + this.getAdlArgumentAccordingToRmCode();
            }

            return arguments;
        }

        /// <summary>
        /// Gets arguments for FirmwareUpdate executable.
        /// </summary>
        /// <param name="connectionGuid">The connection guid.</param>
        /// <returns>Flasher arguments.</returns>
        private string getFirmwareUpdaterArguments(string connectionGuid = "")
        {
            if (string.IsNullOrEmpty(connectionGuid))
                connectionGuid = this.Connection.Connection.GUID;

            // Arguments for Firmware Update flashing mode.
            string arguments = string.Format(
                "{0} {1}", 
                "--guid " + connectionGuid,
                "--firmware " + this.Variant.Value);

            // ADL value is set automatically depending on connection and the product RM code.
            if (this.Connection != null && this.Connection.Connection.Type == EnumConnectionType.USB)
            {
                if (this.IsUserSelectionForAdlValueRequired)
                    arguments += " " + "--adl " + (int)this.ForcedAdlArgumentValue;
                else
                    arguments += " " + "--adl " + this.getAdlArgumentAccordingToRmCode();
            }

            return arguments;
        }

        private string getAdlArgumentAccordingToRmCode()
        {
            if (this.IsDeadPhoneFlashModeEnabled && !this.IsUserSelectionForAdlValueRequired)
            {
                return this.getAdlArgumentAccordingToMcuFilePath(this.McuFilePath);
            }

            if (this.Connection == null || this.Connection.Version == null || string.IsNullOrEmpty(this.Connection.Version.RMCode)) return null;

            return this.getAdlArgumentAccordingToRmCode(this.Connection.Version.RMCode);
        }

        private string getAdlArgumentAccordingToRmCode(string rmCode)
        {
            if (string.IsNullOrEmpty(rmCode)) return null;

            // Currently natively supported product RM codes for ADL argument when using USB connection.
            switch (rmCode)
            {
                case "RM-902":
                case "RM-919":
                case "RM-921":
                    return "2";
                case "RM-920":
                case "RM-934":
                    return "4";
                default:
                    return null;
            }
        }

        private string getAdlArgumentAccordingToMcuFilePath(string filePath)
        {
            return this.getAdlArgumentAccordingToRmCode(FileUtilities.GetRmCodeFromMcuFilePath(filePath));
        }

        private void flashingProcess_OutputDataReceived(object sender, DataReceivedEventArgs e)
        {
            try
            {
                this.messageMutex.WaitOne();

                Application.Current.Dispatcher.BeginInvoke(
                    DispatcherPriority.Normal,
                    new Action(
                        delegate
                            {
                                this.ConsoleOutputText += e.Data + "\n";
                            }));
            }
            catch (AbandonedMutexException)
            {
            }
            finally
            {
                this.messageMutex.ReleaseMutex();
            }
        }

        #endregion [ Flashing Command ]

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

    /// <summary>
    /// The ADL value enumeration.
    /// </summary>
    public enum AdlValueEnum
    {
        /// <summary>
        /// The ADL 2.
        /// </summary>
        Adl2 = 2,

        /// <summary>
        /// The ADL 4.
        /// </summary>
        Adl4 = 4
    }
}
