namespace MarbleLibrary.Utilities
{
    using System;
    using System.Windows;
    using System.Windows.Forms;
    using System.Windows.Interop;
    using System.Windows.Threading;

    using Microsoft.SqlServer.MessageBox;

    /// <summary>
    /// Handles any unexpected exceptions and displays them to the user.
    /// </summary>
    /// <example>
    /// Below is an example showing how to use this class, which is simply to create an instance of this class in your main window
    /// and pass in the Window object as the owner. By default the exception handler will then be enabled. To trial it, throw an
    /// exception from anywhere within your code.
    /// <code>
    /// using Marble.Utilities;
    /// 
    /// public partial class MainWindow : Window
    /// {
    ///    /// &lt;summary&gt;
    ///    /// Handles any unexpected exceptions and displays them to the user.
    ///    /// &lt;/summary&gt;
    ///    private ExceptionHandler _exceptionHandler;
    ///
    ///    public MainWindow()
    ///    {
    ///        // Create the exception handler to handle any unexpected exceptions
    ///        _exceptionHandler = new ExceptionHandler(this);
    ///        
    ///        ...
    ///    }
    ///
    ///    ...
    /// }
    /// </code>
    /// </example>
    public class ExceptionHandler
    {
        /// <summary>
        /// Default title to display.
        /// </summary>
        private const string _defaultErrorTitle = "Error";

        /// <summary>
        /// Default main error message to display.
        /// </summary>
        private const string _defaultErrorMessage = "An unexpected error has occurred.";

        /// <summary>
        /// Advanced information name used when adding information to an exception.
        /// </summary>
        private const string _advancedInformationPrefix = "AdvancedInformation.";

        /// <summary>
        /// Owner window.
        /// </summary>
        private Window _ownerWindow;

        /// <summary>
        /// Flag to indicate whether the exception handler is enabled or not.
        /// </summary>
        private bool _enabled;

        /// <summary>
        /// Prevent the default constructor from being called.
        /// </summary>
        private ExceptionHandler()
        {
        }

        /// <summary>
        /// Creates a new <see cref="ExceptionHandler"/> object.
        /// </summary>
        /// <param name="ownerWindow">Main window that is the owner of the message box used to display the error.</param>
        /// <param name="errorTitle">A custom error title can optionally be specified.</param>
        /// <param name="errorMessage">A custom error message can optionally be specified.</param>
        /// <exception cref="ArgumentNullException">Thrown if a <c>null</c> <paramref name="ownerWindow"/> is supplied.</exception>
        public ExceptionHandler(Window ownerWindow, string errorTitle = _defaultErrorTitle, string errorMessage = _defaultErrorMessage)
        {
            if (ownerWindow == null)
            {
                throw new ArgumentNullException("ownerWindow", "An owner window must be supplied in order to display the exception message to the user.");
            }

            // Initialize the settings
            this.ErrorTitle = errorTitle;
            this.ErrorMesage = errorMessage;

            // Store the owner window and hook up for when it is closed
            this._ownerWindow = ownerWindow;
            this._ownerWindow.Closed += this.OnOwnerWindowClosed;

            // Enable this exception handler
            this.Enabled = true;
        }

        /// <summary>
        /// Title to display when an error occurs.
        /// </summary>
        public string ErrorTitle
        {
            get;
            set;
        }

        /// <summary>
        /// Main error message to display when an error occurs.
        /// </summary>
        public string ErrorMesage
        {
            get;
            set;
        }

        /// <summary>
        /// Property to enable or disable the exception handling.
        /// </summary>
        /// <value>The default value for this property is <c>true</c>.</value>
        public bool Enabled
        {
            get
            {
                return this._enabled;
            }

            set
            {
                if (value != this._enabled)
                {
                    if (value)
                    {
                        // Hook up to events that are generated when there are unhandled exceptions
                        Dispatcher.CurrentDispatcher.UnhandledException += this.OnDispatcherUnhandledException;
                        AppDomain.CurrentDomain.UnhandledException += this.OnDomainUnhandledException;
                    }

                    else
                    {
                        // Unhook from the events that are generated when there are unhandled exceptions
                        Dispatcher.CurrentDispatcher.UnhandledException -= this.OnDispatcherUnhandledException;
                        AppDomain.CurrentDomain.UnhandledException -= this.OnDomainUnhandledException;
                    }

                    // Store the new value
                    this._enabled = value;
                }
            }
        }

        /// <summary>
        /// Processes any exception and displays the error information to the user.
        /// </summary>
        /// <param name="ex">Exception to be displayed.</param>
        /// <remarks>This method is called in order to handle any unhandled exceptions, but it can also be called from
        /// external code if the exception has already been caught and is to be displayed to the user.</remarks>
        public void HandleException(Exception ex)
        {
            // If we are enabled and have an owner window
            if (this.Enabled && this._ownerWindow != null)
            {
                // Create a top-level exception that contains all necessary information
                ApplicationException topLevelException = this.CreateTopLevelException(ex);

                // Get a windows form handle
                WindowInteropHelper windowInterop = new System.Windows.Interop.WindowInteropHelper(this._ownerWindow);
                Control windowsForm = Form.FromHandle(windowInterop.Handle);

                // Display the error to the user
                ExceptionMessageBox messageBox = new ExceptionMessageBox(topLevelException, ExceptionMessageBoxButtons.OK, ExceptionMessageBoxSymbol.Error);
                messageBox.Caption = this.ErrorTitle;
                messageBox.Beep = true;
                messageBox.Show(windowsForm);
            }
        }

        /// <summary>
        /// Creates a top-level exception with all required information about the application and environment.
        /// </summary>
        /// <param name="ex">Exception that has occurred.</param>
        /// <returns>A top-level <see cref="ApplicationException"/> with the supplied exception as an inner exception.</returns>
        private ApplicationException CreateTopLevelException(Exception ex)
        {
            // Add the new top-level message to the handled exception
            ApplicationException topLevelException = new ApplicationException(this.ErrorMesage, ex);

            string sourceText = null;

            // If we have an owner window
            if (this._ownerWindow != null)
            {
                // Use the title from the owner window as the source
                sourceText = this._ownerWindow.Title;
            }

            // If there is owner window or it has no title
            if (string.IsNullOrEmpty(sourceText))
            {
                // Use the product name as the source
                sourceText = System.Windows.Forms.Application.ProductName;
            }

            // Add information to indicate it is an error
            sourceText = sourceText + " Error";
            sourceText = sourceText.Trim();

            // Store this source information
            topLevelException.Source = sourceText;

            try
            {
                System.Reflection.Assembly assembly = System.Reflection.Assembly.GetExecutingAssembly();

                // Add information useful in diagnosing the fault
                topLevelException.Data.Add(_advancedInformationPrefix + "CommandLine", System.Environment.CommandLine);
                topLevelException.Data.Add(_advancedInformationPrefix + "CurrentDirectory", System.Environment.CurrentDirectory);
                topLevelException.Data.Add(_advancedInformationPrefix + "AssemblyName", assembly.GetName().FullName);
                topLevelException.Data.Add(_advancedInformationPrefix + "ProductName", assembly.GetName().Name);
                topLevelException.Data.Add(_advancedInformationPrefix + "ProductVersion", assembly.GetName().Version.ToString());
                topLevelException.Data.Add(_advancedInformationPrefix + "Date", DateTime.Now.ToString());
                topLevelException.Data.Add(_advancedInformationPrefix + "MachineName", System.Environment.MachineName);
                topLevelException.Data.Add(_advancedInformationPrefix + "UserName", System.Environment.UserName);
                topLevelException.Data.Add(_advancedInformationPrefix + "UserDomainName", System.Environment.UserDomainName);
                topLevelException.Data.Add(_advancedInformationPrefix + "OSVersion.Version", System.Environment.OSVersion.VersionString);
                topLevelException.Data.Add(_advancedInformationPrefix + "ProcessorCount", System.Environment.ProcessorCount.ToString());
                topLevelException.Data.Add(_advancedInformationPrefix + "64BitProcess", System.Environment.Is64BitProcess.ToString());
                topLevelException.Data.Add(_advancedInformationPrefix + "64BitOperatingSystem", System.Environment.Is64BitOperatingSystem.ToString());
            }

            catch (Exception additionalInformationException)
            {
                // Add the exception information as additional information
                topLevelException.Data.Add(_advancedInformationPrefix + "AdditionalInformationException", additionalInformationException.ToString());
            }

            return topLevelException;
        }

        /// <summary>
        /// Called when the dispatcher has an unhandled exception.
        /// </summary>
        /// <param name="sender">Sender of the event.</param>
        /// <param name="e">Arguments for the event.</param>
        private void OnDispatcherUnhandledException(object sender, DispatcherUnhandledExceptionEventArgs e)
        {
            if (!e.Handled)
            {
                // We are handling this exception
                e.Handled = true;

                // Handle the exception
                this.HandleException(e.Exception);
            }
        }

        /// <summary>
        /// Called when there is an unhandled excpetion
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnDomainUnhandledException(object sender, UnhandledExceptionEventArgs e)
        {
            // Handle the exception
            this.HandleException((Exception)e.ExceptionObject);
        }

        /// <summary>
        /// Called when the owner window is closed.
        /// </summary>
        /// <param name="sender">Sender of the event.</param>
        /// <param name="e">Arguments for the event.</param>
        private void OnOwnerWindowClosed(object sender, EventArgs e)
        {
            // Disable exception handling
            this.Enabled = false;

            if (this._ownerWindow != null)
            {
                // Unhook from the event
                this._ownerWindow.Closed -= this.OnOwnerWindowClosed;

                // We no longer require the owner window
                this._ownerWindow = null;
            }
        }
    }
}
