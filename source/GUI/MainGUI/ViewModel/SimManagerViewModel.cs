using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Globalization;
using System.Windows.Controls;

using Marble.Communication;
using Marble.Utilities;
using Marble.Model;

namespace Marble.ViewModel
{
    using MarbleLibrary.Commands;

    public class SimManagerViewModel : System.ComponentModel.INotifyPropertyChanged
    {
        public PhoneViewModel PhoneViewModel { get; set; }

        public ObservableCollectionAdv<SimModel> Sims { get; set; }

        public ObservableCollectionAdv<PhoneModel> Phones { get; set; }

        private SimModel selectedSim;

        public SimModel SelectedSim
        {
            get { return this.selectedSim; }
            set
            {
                if (value == this.selectedSim) return;

                this.selectedSim = value;
                OnPropertyChanged("SelectedSim");
            }
        }

        private PhoneModel selectedPhone;

        public PhoneModel SelectedPhone
        {
            get { return this.selectedPhone; }
            set
            {
                if (value == this.selectedPhone) return;

                this.selectedPhone = value;
                OnPropertyChanged("SelectedPhone");

                if (PhoneModel.SelectedSimChanged != null) PhoneModel.SelectedSimChanged(null, new EventArgs());
            }
        }

        private DelegateCommand cmdSaveAndClose;

        private DelegateCommand cmdCancelAndClose;

        public bool CanSaveAndClose()
        {
            return !this.PhoneViewModel.HasSimErrors();
        }

        public bool CanClose()
        {
            return true;
        }

        /// <summary>
        /// Command for opening SIM manager.
        /// </summary>
        public ICommand CmdSaveAndClose
        {
            get
            {
                if (cmdSaveAndClose == null)
                    cmdSaveAndClose = new DelegateCommand(new Action(this.SaveCommandExecuted), new Func<bool>(this.CanSaveAndClose));

                return cmdSaveAndClose;
            }
        }

        /// <summary>
        /// Command for opening SIM manager.
        /// </summary>
        public ICommand CmdCancelAndClose
        {
            get
            {
                if (cmdCancelAndClose == null)
                    cmdCancelAndClose = new DelegateCommand(new Action(this.CancelCommandExecuted), new Func<bool>(this.CanClose));

                return cmdCancelAndClose;
            }
        }

        /// <summary>
        /// Saves current SIM settings and closes SIM manager dialog.
        /// </summary>
        public void SaveCommandExecuted()
        {
            List<SimModel> simModels = new List<SimModel>();

            foreach (PhoneModel phoneModel in this.Phones)
            {
                simModels.AddRange(phoneModel.Sims);
            }

            SimXmlParser.AddSimToSimList(simModels);

            App.ViewModel.UpdateSettings(forceSaveSIMSettings:true);
        }

        /// <summary>
        /// Cancels changes to SIMs.
        /// </summary>
        public void CancelCommandExecuted()
        {
            this.PhoneViewModel.CancelChangesToSims();
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SimManagerViewModel"/> class.
        /// </summary>
        public SimManagerViewModel()
        {
            this.PhoneViewModel = new PhoneViewModel();
            this.Phones = this.PhoneViewModel.PhoneModels;

            if (this.Phones.Count > 0)
                this.SelectedPhone = this.Phones[0];

            if (this.SelectedPhone != null)
                if (this.SelectedPhone.Sims.Count > 0)
                    this.SelectedSim = this.SelectedPhone.Sims[0];

            PhoneModel.SelectedSimChanged += delegate { this.SelectedSim = this.SelectedPhone != null ? this.SelectedPhone.SelectedSim : null; };
        }

        #region [ INotifyPropertyChanged Members ]

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion [ INotifyPropertyChanged Members ]
    }
}
