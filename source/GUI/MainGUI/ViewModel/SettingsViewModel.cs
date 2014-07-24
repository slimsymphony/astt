using System.ComponentModel;
using System.Windows.Input;
using Marble.Communication;
using MarbleLibrary.Commands;
using TestAutomation.Gui.Marble.Settings;

namespace Marble.ViewModel
{
    /// <summary>
    /// Settings view model that acts as an intermediary between the view and the model.
    /// </summary>
    public class SettingsViewModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Command to save the settings.
        /// </summary>
        private DelegateCommand _saveCommand;

        /// <summary>
        /// Command to canceling changes made in the settings.
        /// </summary>
        private DelegateCommand _cancelCommand;

        /// <summary>
        /// Creates a new <see cref="SettingsViewModel"/> object.
        /// </summary>
        public SettingsViewModel()
        {
        }

        /// <summary>
        /// Model used for the settings.
        /// </summary>
        public SettingsManager Model
        {
            get
            {
                return SettingsManager.Instance;
            }
        }

        /// <summary>
        /// Command for saving the settings.
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
            // Update the settings and force the saving of all settings
            App.ViewModel.UpdateSettings(true);
        }

        /// <summary>
        /// Command for canceling changes made in the settings.
        /// </summary>
        public ICommand CancelCommand
        {
            get
            {
                if (_cancelCommand == null)
                {
                    _cancelCommand = new DelegateCommand(CancelAllCommandExecuted, CancelAllCommandCanExecute);
                }

                return _saveCommand;
            }
        }

        /// <summary>
        /// Check to see if the <see cref="SaveCommand"/> can be run.
        /// </summary>
        public bool CancelAllCommandCanExecute()
        {
            return true;
        }

        /// <summary>
        /// Cancels all changes made to settings.
        /// </summary>
        public void CancelAllCommandExecuted()
        {
            this.Model.CancelAll();
        }

        /// <summary>
        /// Sets cancel values to all settings.
        /// </summary>
        public void SetCancelValuesToAll()
        {
            this.Model.SetCancelValuesToAll();
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
