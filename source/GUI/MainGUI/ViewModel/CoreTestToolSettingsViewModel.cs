using System;
using System.ComponentModel;
using System.Windows.Input;
using Marble.Model;
using MarbleLibrary.Commands;

namespace Marble.ViewModel
{
    /// <summary>
    /// Core Test Tool settings view model that acts as an intermediary between the view and the model.
    /// </summary>
    public class CoreTestToolSettingsViewModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Command to save the Core Test Tool settings.
        /// </summary>
        private DelegateCommand _saveCommand;

        /// <summary>
        /// Prevent an instance of this class being created without a model.
        /// </summary>
        private CoreTestToolSettingsViewModel()
        {
        }

        /// <summary>
        /// Creates a new <see cref="CoreTestToolSettingsViewModel"/> that uses the supplied model.
        /// </summary>
        /// <param name="model">Model to use for the Core Test Tool settings.</param>
        /// <exception cref="ArgumentNullException">Thrown if the <paramref name="model"/> is <c>null</c>.</exception>
        public CoreTestToolSettingsViewModel(CoreTestToolSettingsModel model)
        {
            #region Check the arguments

            if (model == null)
            {
                throw new ArgumentNullException("model", "Cannot create a Core Test Tool settings view model without a model.");
            }

            #endregion

            // Store the model
            Model = model;

            foreach (var settingsSection in Model.SettingsSections)
            {
                // If the settings section has not been loaded
                if (!settingsSection.IsLoaded)
                {
                    // Load the settings section so that it is ready for the view
                    settingsSection.Load();
                }
            }
        }

        /// <summary>
        /// Model to be used for the Core Test Tool settings.
        /// </summary>
        public CoreTestToolSettingsModel Model
        {
            get;
            private set;
        }

        /// <summary>
        /// Command for saving the Core Test Tool settings.
        /// </summary>
        public ICommand SaveCommand
        {
            get
            {
                if (_saveCommand == null)
                {
                    _saveCommand = new DelegateCommand(SaveCommandExecuted, SaveCommandCanExecute);
                }

                return _saveCommand;
            }
        }

        /// <summary>
        /// Check to see if the <see cref="SaveCommand"/> can be run.
        /// </summary>
        public bool SaveCommandCanExecute()
        {
            return true;
        }

        /// <summary>
        /// Saves the Core Test Tool settings that have changed.
        /// </summary>
        public void SaveCommandExecuted()
        {
            foreach (CoreTestToolSettingsSection settingsSection in Model.SettingsSections)
            {
                // If this section has been changed
                if (settingsSection.IsDirty)
                {
                    // Execute the command to update this configuration section
                    App.ViewModel.UpdateCoreTestToolConfiguration.Execute(settingsSection);
                }
            }
        }

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
