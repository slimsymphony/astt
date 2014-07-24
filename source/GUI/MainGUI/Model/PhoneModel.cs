using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Marble.Model
{
    using Marble.Communication;
    using Marble.Utilities;

    public class PhoneModel : BaseNotifyPropertyChanged
    {
        private SimModel selectedSim;

        /// <summary>
        /// Gets or sets currently selected SIM.
        /// </summary>
        public SimModel SelectedSim
        {
            get { return this.selectedSim; }
            set
            {
                if (value == this.selectedSim) return;

                this.selectedSim = value;
                this.OnPropertyChanged("SelectedSim");
                
                if (SelectedSimChanged != null) SelectedSimChanged(null, new EventArgs());
            }
        }

        public static EventHandler<EventArgs> SelectedSimChanged;

        private string name;

        /// <summary>
        /// Gets or sets the name of the phone.
        /// </summary>
        public string Name
        {
            get { return this.name; }
            set
            {
                if (value == this.name) return;
                
                this.name = value;
                this.OnPropertyChanged("Name");
                this.OnPropertyChanged("DisplayName");
            }
        }

        /// <summary>
        /// Gets the display name for GUI of the Phone.
        /// </summary>
        public string DisplayName { get { return this.Name + " - " + this.ProductType; } }

        private string productType;

        /// <summary>
        /// Gets or sets the product code of the phone.
        /// </summary>
        public string ProductType
        {
            get { return this.productType; }
            set
            {
                if (value == this.productType) return;
                
                this.productType = value;
                this.OnPropertyChanged("ProductType");
                this.OnPropertyChanged("DisplayName");
            }
        }

        private string connectionGuid;

        /// <summary>
        /// Gets or sets the connection GUID.
        /// </summary>
        public string ConnectionGuid
        {
            get { return this.connectionGuid; }
            set
            {
                if (value == this.connectionGuid) return;

                this.connectionGuid = value;
                this.OnPropertyChanged("ConnectionGuid");
            }
        }

        private int simSlots;

        /// <summary>
        /// Gets or sets the number of SIM slots the phone contains. 1 is minimum value for the SIM slots.
        /// </summary>
        public int SimSlots
        {
            get { return this.simSlots; }
            set
            {
                if (value == this.simSlots || value < 1) return;
                
                this.simSlots = value;
                this.OnPropertyChanged("SimSlots");
            }
        }

        private int phoneIndex;
        
        /// <summary>
        /// Gets or sets the index number of the phone. This is used for listing phones. 1 is minimum value.
        /// </summary>
        public int PhoneIndex
        {
            get { return this.phoneIndex; }
            set
            {
                if (value == this.phoneIndex || value < 1) return;

                this.phoneIndex = value;
                this.OnPropertyChanged("PhoneIndex");
            }
        }

        public ObservableCollectionAdv<SimModel> Sims { get; set; }

        public PhoneModel()
        {
            this.Sims = new ObservableCollectionAdv<SimModel>();
            this.SimSlots = 1;

            if (this.Sims.Count > 0)
                this.SelectedSim = this.Sims[0];
        }
    }
}
