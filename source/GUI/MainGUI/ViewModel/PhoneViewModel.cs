using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Xml.Serialization;
using Marble.Communication;
using Marble.Model;
using Marble.Utilities;

using System.Windows.Controls;

namespace Marble.ViewModel
{
    /// <summary>
    /// View model class for the SIM operations.
    /// </summary>
    public class PhoneViewModel : BaseNotifyPropertyChanged
    {
        /// <summary>
        /// Observable collection containing PhoneModel objects.
        /// </summary>
        public ObservableCollectionAdv<PhoneModel> PhoneModels { get; set; }

        /// <summary>
        /// Initializes a new instance of the PhoneViewModel class.
        /// </summary>
        public PhoneViewModel()
        {
            this.PhoneModels = new ObservableCollectionAdv<PhoneModel>();

            this.LoadConnectedPhones();

            App.ViewModel.FuseClient.Connections.ProductPresenceChanged += delegate { this.LoadConnectedPhones(); };
        }

        /// <summary>
        /// Loads connected phones.
        /// </summary>
        /// <returns></returns>
        public bool LoadConnectedPhones()
        {
            if (this.PhoneModels.Count > 0)
                this.removeDisconnectedPhones();

            int index = 1;
            List<int> indexes = this.PhoneModels.Select(phoneModel => phoneModel.PhoneIndex).ToList();

            foreach (ProductInfo productInfo in App.ViewModel.FuseClient.Connections.Where(p => p.ProductPresent != EnumProductPresence.NotPresent))
            {
                // If PhoneModel is already listed, it isn't added to the connected products.
                if (this.PhoneModels.Any(phoneModel => phoneModel.ConnectionGuid == productInfo.Connection.GUID)) continue;

                ObservableCollectionAdv<SimModel> connectedSims = new ObservableCollectionAdv<SimModel>();
                
                this.addSimToPhone(productInfo.SIM1, connectedSims, 1);
                this.addSimToPhone(productInfo.SIM2, connectedSims, 2);

                while (indexes.Contains(index))
                    index++;
                indexes.Add(index);

                this.PhoneModels.Add(new PhoneModel()
                                         {
                                             Name = productInfo.Connection.Name,
                                             PhoneIndex = index,
                                             ProductType = productInfo.Version.RMCode,
                                             ConnectionGuid = productInfo.Connection.GUID,
                                             Sims = connectedSims,
                                         });

                productInfo.ProductScanned += delegate(object sender, EventArgs args) { this.reloadProduct(sender as ProductInfo); };
            }

            return true;
        }

        /// <summary>
        /// Cancels changes made to SIMs.
        /// </summary>
        public void CancelChangesToSims()
        {
            foreach (PhoneModel phoneModel in this.PhoneModels)
            {
                foreach (SimModel simModel in phoneModel.Sims)
                {
                    simModel.CancelChanges();
                }
            }
        }

        /// <summary>
        /// Forces validation check for all phones and SIMs.
        /// </summary>
        public void ForceValidationToSims()
        {
            foreach (PhoneModel phoneModel in this.PhoneModels)
            {
                foreach (SimModel simModel in phoneModel.Sims)
                {
                    simModel.ForceValidation();
                }
            }
        }

        /// <summary>
        /// Gets value indicating whether the there are any SIM(s) containing errors.
        /// </summary>
        /// <returns></returns>
        public bool HasSimErrors()
        {
            return this.PhoneModels.SelectMany(phoneModel => phoneModel.Sims).Any(simModel => simModel.HasErrors);
        }

        private void reloadProduct(ProductInfo productInfo)
        {
            foreach (PhoneModel phoneModel in this.PhoneModels.Where(phoneModel => phoneModel.ConnectionGuid == productInfo.Connection.GUID))
            {
                phoneModel.ProductType = productInfo.Version.RMCode;

                this.reloadSims(phoneModel, productInfo);
            }
        }

        private void reloadSims(PhoneModel phoneModel, ProductInfo productInfo)
        {
            phoneModel.Sims.Clear();
            this.addSimToPhone(productInfo.SIM1, phoneModel.Sims, 1);
            this.addSimToPhone(productInfo.SIM2, phoneModel.Sims, 2);
        }

        private bool addSimToPhone(SimModel simModel, ObservableCollectionAdv<SimModel> connectedSims, int simSlot)
        {
            if (simModel == null) return false;
            if (string.IsNullOrEmpty(simModel.ToString())) return false;

            SimModel newSimModel =
                new SimModel()
                    {
                        CurrentSimSlot = simSlot,
                        CountryCode = simModel.CountryCode,
                        NetworkCode = simModel.NetworkCode,
                        IdNumber = simModel.IdNumber,
                        CountryName = SimXmlParser.GetCountryName(simModel.CountryCode) ?? string.Empty,
                        OperatorName = SimXmlParser.GetOperatorName(simModel.NetworkCode, simModel.CountryCode) ?? string.Empty,
                        PhoneNumber = SimXmlParser.GetPhoneNumberForSim(simModel.Imsi) ?? string.Empty,
                        PinCode = SimXmlParser.GetPinCodeForSim(simModel.Imsi) ?? string.Empty,
                        Pin2Code = SimXmlParser.GetPin2CodeForSim(simModel.Imsi) ?? string.Empty,
                        Puk1Code = SimXmlParser.GetPuk1CodeForSim(simModel.Imsi) ?? string.Empty,
                        Puk2Code = SimXmlParser.GetPuk2CodeForSim(simModel.Imsi) ?? string.Empty,
                        ServiceNumber = SimXmlParser.GetServiceNumberForSim(simModel.Imsi) ?? string.Empty,
                        VoiceMailNumber = SimXmlParser.GetVoiceMailNumberForSim(simModel.Imsi) ?? string.Empty
                    };
            
            newSimModel.UpdateCancelValues();
            connectedSims.Add(newSimModel);

            return true;
        }

        private void removeDisconnectedPhones()
        {
            List<PhoneModel> disconnectedPhones = new List<PhoneModel>();

            // PhoneModels are checked whether they still exist in connected products.
            foreach (PhoneModel phoneModel in this.PhoneModels)
            {
                bool isPhoneConnected =
                    App.ViewModel.FuseClient.Connections.Any(
                        productInfo =>
                        phoneModel.ConnectionGuid == productInfo.Connection.GUID &&
                        productInfo.ProductPresent != EnumProductPresence.NotPresent);

                // If PhoneModel doesn't exist in connected products, it is added to disconnected phones list.
                if (!isPhoneConnected) disconnectedPhones.Add(phoneModel);
            }

            // All PhoneModel in the disconnected phones list are removed from PhoneModels.
            foreach (PhoneModel disconnectedPhone in disconnectedPhones)
            {
                this.PhoneModels.Remove(disconnectedPhone);
            }
        }
    }
}
