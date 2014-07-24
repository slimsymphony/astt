namespace Marble.Communication
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Linq;
    using System.Xml.Serialization;

    using Marble.Model;
    using Marble.Utilities;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// Model for International Mobile Subscriber Identity.
    /// 15 digit format: 3(MCC) 2-3(MNC) 10-9(MSIN)
    /// </summary>
    public class SimModel : BaseNotifyPropertyChanged, IDataErrorInfo
    {
        public static Dictionary<string, string> RegisteredPhoneNumbers { get; private set; } 

        private string countryCode;

        /// <summary>
        /// Gets or sets Mobile Country Code (MCC).
        /// </summary>
        public string CountryCode
        {
            get { return this.countryCode; }
            set
            {
                this.countryCode = value;
                this.OnPropertyChanged("CountryCode");
            }
        }

        private string countryName;

        /// <summary>
        /// Gets country name.
        /// </summary>
        public string CountryName
        {
            get { return this.countryName; }
            set
            {
                this.countryName = value;
                this.OnPropertyChanged("CountryName");
            }
        }

        private string networkCode;

        /// <summary>
        /// Gets or sets Mobile Network Code (MNC).
        /// </summary>
        public string NetworkCode
        {
            get { return this.networkCode; }
            set
            {
                this.networkCode = value;
                this.OnPropertyChanged("NetworkCode");
            }
        }

        private string operatorName;

        /// <summary>
        /// Gets operator name.
        /// </summary>
        public string OperatorName
        {
            get { return this.operatorName; }
            set
            {
                this.operatorName = value;
                this.OnPropertyChanged("OperatorName");
            }
        }

        private string idNumber;

        /// <summary>
        /// Gets or sets Mobile Subscription Identification Number (MSIN).
        /// </summary>
        public string IdNumber
        {
            get { return this.idNumber; }
            set
            {
                this.idNumber = value;
                this.OnPropertyChanged("IdNumber");
            }
        }

        private string phoneNumber;

        /// <summary>
        /// Gets or sets the phone number for the SIM.
        /// </summary>
        public string PhoneNumber
        {
            get { return this.phoneNumber; }
            set
            {
                this.phoneNumber = value;
                this.OnPropertyChanged("PhoneNumber");

                if (!string.IsNullOrEmpty(this.Imsi))
                    this.updatePhoneNumberRegistration();
            }
        }

        private int currentSimSlot;

        /// <summary>
        /// Gets or sets the current SIM slot where SIM is located in the product.
        /// </summary>
        public int CurrentSimSlot
        {
            get { return this.currentSimSlot; }
            set
            {
                this.currentSimSlot = value;
                this.OnPropertyChanged("CurrentSimSlot");
            }
        }

        private string pinCode;

        /// <summary>
        /// Gets or sets the PIN code.
        /// </summary>
        public string PinCode
        {
            get
            {
                return this.pinCode;
            }
            set
            {
                this.pinCode = value;
                this.OnPropertyChanged("PinCode");
            }
        }

        private string pin2Code;

        /// <summary>
        /// Gets or sets the PIN2 code.
        /// </summary>
        public string Pin2Code
        {
            get
            {
                return this.pin2Code;
            }
            set
            {
                this.pin2Code = value;
                this.OnPropertyChanged("Pin2Code");
            }
        }

        private string puk1Code;

        /// <summary>
        /// Gets or sets the PUK1 code.
        /// </summary>
        public string Puk1Code
        {
            get
            {
                return this.puk1Code;
            }
            set
            {
                this.puk1Code = value;
                this.OnPropertyChanged("Puk1Code");
            }
        }

        private string puk2Code;

        /// <summary>
        /// Gets or sets the PUK2 code.
        /// </summary>
        public string Puk2Code
        {
            get
            {
                return this.puk2Code;
            }
            set
            {
                this.puk2Code = value;
                this.OnPropertyChanged("Puk2Code");
            }
        }

        private string voiceMailNumber;

        /// <summary>
        /// Gets or sets the voice mail number.
        /// </summary>
        public string VoiceMailNumber
        {
            get
            {
                return this.voiceMailNumber;
            }
            set
            {
                this.voiceMailNumber = value;
                this.OnPropertyChanged("VoiceMailNumber");
            }
        }

        private string serviceNumber;

        /// <summary>
        /// Gets or sets the service number.
        /// </summary>
        public string ServiceNumber
        {
            get
            {
                return this.serviceNumber;
            }
            set
            {
                this.serviceNumber = value;
                this.OnPropertyChanged("ServiceNumber");
            }
        }

        /// <summary>
        /// Gets International Mobile Subscriber Identity (IMSI).
        /// 15 digit format: 3(MCC) 2-3(MNC) 10-9(MSIN).
        /// </summary>
        public string Imsi { get { return this.ToString(); } }

        /// <summary>
        /// Gets value indicating whether SIM has errors.
        /// </summary>
        public bool HasErrors { get; private set; }

        private string previousPhoneNumber { get; set; }

        private string previousPinCode { get; set; }

        private string previousPin2Code { get; set; }

        private string previousPuk1Code { get; set; }

        private string previousPuk2Code { get; set; }

        private string previousServiceNumber { get; set; }

        private string previousVoiceMailNumber { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="SimModel"/> class. 
        /// </summary>
        public SimModel()
        {
            this.initializeRegisteredPhoneNumbers();
            this.initializeProperties();
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SimModel"/> class. 
        /// </summary>
        /// <param name="imsi">SimModel number as a string. Must be over 14 digits long.</param>
        /// <param name="mncLength">Length of the MNC part (variable).</param>
        public SimModel(string imsi, int mncLength = 2)
        {
            this.initializeRegisteredPhoneNumbers();
            this.initializeProperties();

            if (imsi.Length >= 15)
            {
                // use only the last 15 characters
                imsi = imsi.Substring(imsi.Length - 15);

                this.CountryCode = imsi.Substring(0, 3);
                this.NetworkCode = imsi.Substring(3, mncLength);
                this.IdNumber = imsi.Substring(3 + mncLength);
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SimModel"/> class. 
        /// </summary>
        /// <param name="countryCode">MCC as a string. Must be 3 digits long.</param>
        /// <param name="networkCode">MCC as a string. Must be 2 or 3 digits long.</param>
        /// <param name="idNumber">MSIN as a string. Must be 9 or 10 digits long.</param>
        public SimModel(string countryCode, string networkCode, string idNumber)
        {
            this.initializeRegisteredPhoneNumbers();
            this.initializeProperties();

            if (countryCode.Length == 3)
                this.CountryCode = countryCode;
            if (networkCode.Length == 2 || networkCode.Length == 3)
                this.NetworkCode = networkCode;
            if (idNumber.Length == 9 || idNumber.Length == 10)
                this.IdNumber = idNumber;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SimModel"/> class. 
        /// </summary>
        /// <param name="countryCode">MCC as a string. Must be 3 digits long.</param>
        /// <param name="networkCode">MCC as a string. Must be 2 or 3 digits long.</param>
        /// <param name="idNumber">MSIN as a string. Must be 9 or 10 digits long.</param>
        /// <param name="phoneNumber">Phone number as a string.</param>
        public SimModel(string countryCode, string networkCode, string idNumber, string phoneNumber)
        {
            this.initializeRegisteredPhoneNumbers();
            this.initializeProperties();

            if (countryCode.Length == 3)
                this.CountryCode = countryCode;
            if (networkCode.Length == 2 || networkCode.Length == 3)
                this.NetworkCode = networkCode;
            if (idNumber.Length == 9 || idNumber.Length == 10)
                this.IdNumber = idNumber;

            this.PhoneNumber = phoneNumber;
        }

        /// <summary>
        /// Whole SimModel in one 15 digit string: MCC + MNN + MSIN
        /// </summary>
        /// <returns>IMSI as a string.</returns>
        public override string ToString()
        {
            return this.CountryCode + this.NetworkCode + this.IdNumber;
        }

        /// <summary>
        /// Cancels changes to phone number.
        /// </summary>
        public void CancelChanges()
        {
            this.PhoneNumber = this.previousPhoneNumber;
            this.PinCode = this.previousPinCode;
            this.Pin2Code = this.previousPin2Code;
            this.Puk1Code = this.previousPuk1Code;
            this.Puk2Code = this.previousPuk2Code;
            this.ServiceNumber = this.previousServiceNumber;
            this.VoiceMailNumber = this.previousVoiceMailNumber;
        }

        /// <summary>
        /// When phone number changes are saved, cancel value of the phone number is updated.
        /// </summary>
        public void UpdateCancelValues()
        {
            this.previousPhoneNumber = this.PhoneNumber;
            this.previousPinCode = this.PinCode;
            this.previousPin2Code = this.Pin2Code;
            this.previousPuk1Code = this.Puk1Code;
            this.previousPuk2Code = this.Puk2Code;
            this.previousServiceNumber = this.ServiceNumber;
            this.previousVoiceMailNumber = this.VoiceMailNumber;
        }

        public void ForceValidation()
        {
            this.OnPropertyChanged("PhoneNumber");
            this.OnPropertyChanged("PinCode");
            this.OnPropertyChanged("Pin2Code");
            this.OnPropertyChanged("Puk1Code");
            this.OnPropertyChanged("Puk2Code");
            this.OnPropertyChanged("ServiceNumber");
            this.OnPropertyChanged("VoiceMailNumber");
        }

        private void initializeRegisteredPhoneNumbers()
        {
            if (SimModel.RegisteredPhoneNumbers != null) return;

            SimModel.RegisteredPhoneNumbers = SimXmlParser.GetPhoneNumberDictionaryFromSimList()
                                              ?? new Dictionary<string, string>();
        }

        private void initializeProperties()
        {
            this.CountryCode = string.Empty;
            this.NetworkCode = string.Empty;
            this.IdNumber = string.Empty;
            this.PhoneNumber = string.Empty;
            this.CountryName = string.Empty;
            this.OperatorName = string.Empty;
            this.PinCode = string.Empty;
            this.Pin2Code = string.Empty;
            this.Puk1Code = string.Empty;
            this.Puk2Code = string.Empty;
            this.ServiceNumber = string.Empty;
            this.VoiceMailNumber = string.Empty;
            this.previousPhoneNumber = string.Empty;
            this.previousPinCode = string.Empty;
            this.previousPin2Code = string.Empty;
            this.previousPuk1Code = string.Empty;
            this.previousPuk2Code = string.Empty;
            this.previousServiceNumber = string.Empty;
            this.previousVoiceMailNumber = string.Empty;
        }

        private void updatePhoneNumberRegistration()
        {
            // When there's no phone number, SIM is unregistered.
            if (string.IsNullOrEmpty(this.PhoneNumber))
            {
                if (SimModel.RegisteredPhoneNumbers.ContainsKey(this.Imsi)) 
                    SimModel.RegisteredPhoneNumbers.Remove(this.Imsi);
            }
            // When SIM is not already registered, it is registered.
            else if (!SimModel.RegisteredPhoneNumbers.ContainsKey(this.Imsi) &&
                !SimModel.RegisteredPhoneNumbers.ContainsValue(this.PhoneNumber))
            {
                    SimModel.RegisteredPhoneNumbers.Add(this.Imsi, this.PhoneNumber);
            }
            // When SIM is registered and phone number has changed, new phone number is registered for the SIM if the phone number doesn't exist.
            else if (SimModel.RegisteredPhoneNumbers.ContainsKey(this.Imsi) &&
                     !SimModel.RegisteredPhoneNumbers.ContainsValue(this.PhoneNumber))
            {
                SimModel.RegisteredPhoneNumbers[this.Imsi] = this.PhoneNumber;
            }
            // When new phone number already is registered for some other SIM, the old number is unregistered from the current SIM.
            else if (SimModel.RegisteredPhoneNumbers.ContainsKey(this.Imsi))
            {
                if (SimModel.RegisteredPhoneNumbers[this.Imsi] != this.PhoneNumber &&
                    RegisteredPhoneNumbers.Where(registeredPhoneNumber => registeredPhoneNumber.Key != this.Imsi).Any(registeredPhoneNumber => registeredPhoneNumber.Value == this.PhoneNumber))
                {
                    SimModel.RegisteredPhoneNumbers.Remove(this.Imsi);
                }
            }
        }

        #region [ IDataErrorInfo Members ]

        /// <summary>
        /// Checks whether the property value contains errors.
        /// </summary>
        /// <param name="propertyName">Name of the property to check.</param>
        /// <returns>Error text when property value contains errors.</returns>
        public string this[string propertyName]
        {
            get
            {
                string result = null;

                switch (propertyName)
                {
                    case "PhoneNumber":
                        if (SimModel.RegisteredPhoneNumbers.ContainsKey(this.Imsi))
                        {
                            if (SimModel.RegisteredPhoneNumbers[this.Imsi] != this.PhoneNumber)
                            {
                                if (SimModel.RegisteredPhoneNumbers.ContainsValue(this.PhoneNumber)) 
                                    result = "Phone number already exists.";
                            }
                        }
                        else
                        {
                            if (SimModel.RegisteredPhoneNumbers.ContainsValue(this.PhoneNumber))
                                result = "Phone number already exists.";
                        }

                        break;
                    case "PinCode":
                        if (!TextUtilities.IsDigitsOnly(this.PinCode)) 
                            result = "PIN code can only contain digits.\n";
                        if (this.PinCode.Length > 0 && this.PinCode.Length < 4)
                            result = "PIN code must be 4-8 digits.\n";
                        break;
                    case "Pin2Code":
                        if (!TextUtilities.IsDigitsOnly(this.Pin2Code))
                            result = "PIN2 code can only contain digits.\n";
                        if (this.Pin2Code.Length > 0 && this.Pin2Code.Length < 4)
                            result = "PIN2 code must be 4-8 digits.\n";
                        break;
                    case "Puk1Code":
                        if (!TextUtilities.IsDigitsOnly(this.Puk1Code))
                            result = "PUK1 code can only contain digits.\n";
                        if (this.Puk1Code.Length > 0 && this.Puk1Code.Length < 4)
                            result = "PUK1 code must be 4-8 digits.\n";
                        break;
                    case "Puk2Code":
                        if (!TextUtilities.IsDigitsOnly(this.Puk2Code))
                            result = "PUK2 code can only contain digits.\n";
                        if (this.Puk2Code.Length > 0 && this.Puk2Code.Length < 4)
                            result = "PUK2 code must be 4-8 digits.\n";
                        break;
                }

                this.HasErrors = !string.IsNullOrEmpty(result);

                if (!string.IsNullOrEmpty(result))
                    result = result.TrimEnd('\n');

                return result;
            }
        }

        /// <summary>
        /// Gets error. This is null by default.
        /// </summary>
        public string Error { get { return null; } }

        #endregion [ IDataErrorInfo Members ]
    }
}