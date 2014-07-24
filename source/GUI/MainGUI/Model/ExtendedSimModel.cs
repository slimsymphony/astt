using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;
using Marble.Communication;

namespace Marble.Model
{
    using Marble.Utilities;

    public class BaseNotifyPropertyChanged : INotifyPropertyChanged
    {
        #region [ INotifyPropertyChanged Members ]

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        public void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion [ INotifyPropertyChanged Members ]
    }

    public class SimSettingModel : BaseNotifyPropertyChanged
    {
        private IList<SimSettingModel> children;

        /// <summary>
        /// Observable collection containing child SimSettingModel objects.
        /// </summary>
        [XmlIgnore]
        public virtual IList<SimSettingModel> Children
        {
            get { return children; }
            private set
            {
                if (value == children) return;

                children = value;
                base.OnPropertyChanged("Children");
            }
        }

        /// <summary>
        /// Gets whether the SimSettingModel has child objects.
        /// </summary>
        public bool HasChildren
        {
            get
            {
                if (this.Children == null) return false;

                return this.Children.Count > 0;
            }
        }

        /// <summary>
        /// Initializes a new instance of the SimSettingModel class.
        /// </summary>
        public SimSettingModel()
        {
            this.Children = new ObservableCollectionAdv<SimSettingModel>();
        }
    }

    /// <summary>
    /// Model class for SIM.
    /// </summary>
    [Serializable]
    [XmlRoot("Sim")]
    public class ExtendedSimModel : BaseNotifyPropertyChanged
    {

        /// <summary>
        /// Gets or sets SIM ID.
        /// </summary>
        //[XmlAttribute("SimIMSI")]
        [XmlIgnore]
        public string SimImsi
        {
            get { return this.ImsiMcc + this.ImsiMnc + this.ImsiId; }
            //get { return this.simImsi; }
            //set
            //{
            //    if (value == this.simImsi || value != this.ImsiMcc + this.ImsiMnc + this.ImsiId) return;

            //    simImsi = value;
            //    base.OnPropertyChanged("SimImsi");
            //}
        }

        private SimModel simModel;

        [XmlIgnore]
        public SimModel SimModel
        {
            get { return this.simModel; }
            set
            {
                if (value == this.simModel)
                
                this.simModel = value;
                this.OnPropertyChanged("SimModel");

                this.ImsiMcc = value.CountryCode;
                this.ImsiMnc = value.NetworkCode;
                this.ImsiId = value.IdNumber;
            }
        }

        private string imsiMcc;

        /// <summary>
        /// Gets MCC from SimModel. MCC represents country code.
        /// </summary>
        [XmlAttribute("SimModel-MCC")]
        public string ImsiMcc
        {
            get { return this.imsiMcc; }
            set
            {
                if (value == this.imsiMcc) return;

                this.imsiMcc = value;
                this.OnPropertyChanged("ImsiMcc");
            }
        }

        private string imsiMnc;

        /// <summary>
        /// Gets MNC from SimModel. MNC represent operator code.
        /// </summary>
        [XmlAttribute("SimModel-MNC")]
        public string ImsiMnc
        {
            get { return this.imsiMnc; }
            set
            {
                if (value == this.imsiMnc) return;

                this.imsiMnc = value;
                this.OnPropertyChanged("ImsiMnc");
            }
        }

        private string imsiId;

        /// <summary>
        /// Gets ID from SimModel.
        /// </summary>
        [XmlAttribute("SimModel-ID")]
        public string ImsiId
        {
            get { return this.imsiId; }
            set
            {
                if (value == this.imsiId) return;

                this.imsiId = value;
                this.OnPropertyChanged("ImsiId");
            }
        }

        private string name;

        /// <summary>
        /// Gets or sets the name of the SIM.
        /// </summary>
        [XmlElement("SimName")]
        public string Name
        {
            get { return this.name; }
            set
            {
                if (value == this.name) return;

                this.name = value;
                this.OnPropertyChanged("SimName");
            }
        }

        private string phoneNumber;

        /// <summary>
        /// Gets or sets the phone number of the SIM.
        /// </summary>
        [XmlElement("SimPhoneNumber")]
        public string PhoneNumber
        {
            get { return this.phoneNumber; }
            set
            {
                if (value == this.phoneNumber) return;

                this.phoneNumber = value;
                this.OnPropertyChanged("PhoneNumber");
            }
        }

        private string simOperator;

        /// <summary>
        /// Gets or sets the operator of the SIM.
        /// </summary>
        [XmlElement("SimOperator")]
        public string SimOperator
        {
            get { return this.simOperator; }
            set
            {
                if (value == this.simOperator) return;

                this.simOperator = value;
                this.OnPropertyChanged("SimOperator");
            }
        }

        private string simCountry;

        /// <summary>
        /// Gets or sets the country of the SIM.
        /// </summary>
        [XmlElement("SimCountry")]
        public string SimCountry
        {
            get { return this.simCountry; }
            set
            {
                if (value == this.simCountry) return;

                this.simCountry = value;
                this.OnPropertyChanged("SimCountry");
            }
        }

        private string operatorFile { get; set; }

        private SimAccountSettingsModel accountSettings;

        /// <summary>
        /// Gets or sets SIM account settings.
        /// </summary>
        [XmlElement("SimAccountSettings")]
        public SimAccountSettingsModel AccountSettings
        {
            get { return this.accountSettings; }
            set
            {
                if (value == this.accountSettings) return;

                this.accountSettings = value;
                this.OnPropertyChanged("AccountSettings");
            }
        }

        private int currentSimSlot;

        /// <summary>
        /// Gets or sets SIM slot where SIM is currently inserted.
        /// </summary>
        [XmlIgnore]
        public int CurrentSimSlot
        {
            get { return this.currentSimSlot; }
            set
            {
                if (value == this.currentSimSlot) return;
                
                this.currentSimSlot = value;
                this.OnPropertyChanged("CurrentSimSlot");
            }
        }

        /// <summary>
        /// Gets or sets whether the curren SIM is selected.
        /// </summary>
        [XmlIgnore]
        public bool IsSelected { get; set; }

        /// <summary>
        /// Creates a new instance of the ExtendedSimModel class.
        /// </summary>
        public ExtendedSimModel()
        {
            this.AccountSettings = new SimAccountSettingsModel();
        }
    }

    [Serializable]
    public class SimAccountSettingsModel : SimSettingModel
    {
        /// <summary>
        /// Observable collection containing child SimSettingModel objects.
        /// </summary>
        [XmlIgnore]
        public override IList<SimSettingModel> Children
        {
            get
            {
                return new List<SimSettingModel>
                           {
                               this.wapSettings, 
                               this.mmsSettings
                           };
            }
        }

        private ObservableCollectionAdv<BaseAccountSettingModel> availableSettings;

        [XmlIgnore]
        public ObservableCollectionAdv<BaseAccountSettingModel> AvailableSettings
        {
            get { return this.availableSettings; }
            set
            {
                if (value == this.availableSettings) return;

                this.availableSettings = value;
                base.OnPropertyChanged("AvailableSettings");
            }
        }

        private WapSettingsModel wapSettings;

        /// <summary>
        /// Gets or sets the WAP settings model.
        /// </summary>
        [XmlElement("WapSettings")]
        public WapSettingsModel WapSettings
        {
            get { return this.wapSettings; }
            set
            {
                if (value == this.wapSettings) return;

                this.wapSettings = value;
                base.OnPropertyChanged("WapSettings");

                //if (!this.Children.Contains(this.wapSettings)) this.Children.Add(this.wapSettings);
            }
        }

        private MmsSettingsModel mmsSettings;

        /// <summary>
        /// Gets or sets the MMS settings model.
        /// </summary>
        [XmlElement("MmsSettings")]
        public MmsSettingsModel MmsSettings
        {
            get { return this.mmsSettings; }
            set
            {
                if (value == this.mmsSettings)

                    this.mmsSettings = value;
                base.OnPropertyChanged("MmsSettings");

                //if (!this.Children.Contains(this.mmsSettings)) this.Children.Add(this.mmsSettings);
            }
        }

        /// <summary>
        /// Initializes available SIM settings collection.
        /// </summary>
        public void InitializeAvailableSettingsCollection()
        {
            this.AvailableSettings = new ObservableCollectionAdv<BaseAccountSettingModel>();

            foreach (SimSettingModel childSetting in this.Children)
            {
                //this.AvailableSettings.Add(childSetting);

                this.fetchAvailableSettingsFromChildSettings(childSetting);
            }
        }

        private void fetchAvailableSettingsFromChildSettings(SimSettingModel parentSetting)
        {
            if (parentSetting == null) return;
            if (!parentSetting.HasChildren) return;

            foreach (var childSetting in parentSetting.Children)
            {
                this.fetchAvailableSettingsFromChildSettings(childSetting);

                if (childSetting is BaseAccountSettingModel)
                    this.AvailableSettings.Add(childSetting as BaseAccountSettingModel);

            }
        }

        /// <summary>
        /// Creates a new instance of the SimAccountSettingsModel class.
        /// </summary>
        public SimAccountSettingsModel()
        {
            this.WapSettings = new WapSettingsModel();
            this.MmsSettings = new MmsSettingsModel();
        }
    }

    [Serializable]
    public class WapSettingsModel : SimSettingModel
    {
        /// <summary>
        /// Observable collection containing child SimSettingModel objects.
        /// </summary>
        [XmlIgnore]
        public override IList<SimSettingModel> Children
        {
            get
            {
                return new List<SimSettingModel>
                           {
                               this.gprsSettings, 
                               this.settingsName, 
                               this.homepage, 
                               this.dataBearer
                           };
            }
        }

        private BaseAccountSettingModel settingsName;

        /// <summary>
        /// Gets or sets the name of the WAP settings.
        /// </summary>
        [XmlElement("WapSettingsName")]
        public BaseAccountSettingModel SettingsName
        {
            get { return this.settingsName; }
            set
            {
                if (value == this.settingsName) return;

                this.settingsName = value;
                base.OnPropertyChanged("SettingsName");
            }
        }

        private BaseAccountSettingModel homepage;

        /// <summary>
        /// Gets or sets the homepage for WAP.
        /// </summary>
        [XmlElement("WapHomepage")]
        public BaseAccountSettingModel Homepage
        {
            get { return this.homepage; }
            set
            {
                if (value == this.homepage) return;

                this.homepage = value;
                base.OnPropertyChanged("Homepage");
            }
        }

        private BaseAccountSettingModel dataBearer;

        /// <summary>
        /// Gets or sets the data bearer for WAP
        /// </summary>
        [XmlElement("WapDataBearer")]
        public BaseAccountSettingModel DataBearer
        {
            get { return this.dataBearer; }
            set
            {
                if (value == this.dataBearer) return;

                this.dataBearer = value;
                base.OnPropertyChanged("DataBearer");
            }
        }

        private GprsSettingsModel gprsSettings;

        /// <summary>
        /// Gets or sets the GPRS settings for WAP.
        /// </summary>
        [XmlElement("WapGprsSettings")]
        public GprsSettingsModel GprsSettings
        {
            get { return this.gprsSettings; }
            set
            {
                if (value == this.gprsSettings) return;

                this.gprsSettings = value;
                base.OnPropertyChanged("GprsSettings");
            }
        }

        /// <summary>
        /// Creates a new instance of the WapSettingsModel class.
        /// </summary>
        public WapSettingsModel()
        {
            this.GprsSettings = new GprsSettingsModel();
            this.SettingsName = new BaseAccountSettingModel() { Name = "WAP Settings Name" };
            this.Homepage = new BaseAccountSettingModel() { Name = "WAP Homepage" };
            this.DataBearer = new BaseAccountSettingModel() { Name = "WAP Data Bearer" };
        }
    }

    [Serializable]
    public class MmsSettingsModel : SimSettingModel
    {
        /// <summary>
        /// Observable collection containing child SimSettingModel objects.
        /// </summary>
        [XmlIgnore]
        public override IList<SimSettingModel> Children
        {
            get
            {
                return new List<SimSettingModel> 
                           { 
                               this.gprsSettings, 
                               this.settingsName, 
                               this.homepage 
                           };
            }
        }

        private BaseAccountSettingModel settingsName;

        /// <summary>
        /// Gets or sets the name of the settings for MMS.
        /// </summary>
        [XmlElement("MmsSettingsName")]
        public BaseAccountSettingModel SettingsName
        {
            get { return this.settingsName; }
            set
            {
                if (value == this.settingsName) return;

                this.settingsName = value;
                base.OnPropertyChanged("SettingsName");
            }
        }

        private BaseAccountSettingModel homepage;

        /// <summary>
        /// Gets or sets the homepage for MMS.
        /// </summary>
        [XmlElement("MmsHomepage")]
        public BaseAccountSettingModel Homepage
        {
            get { return this.homepage; }
            set
            {
                if (value == this.homepage) return;

                this.homepage = value;
                base.OnPropertyChanged("Homepage");
            }
        }

        private GprsSettingsModel gprsSettings;

        /// <summary>
        /// Gets or sets the GPRS settings for WAP.
        /// </summary>
        [XmlElement("MmsGprsSettings")]
        public GprsSettingsModel GprsSettings
        {
            get { return this.gprsSettings; }
            set
            {
                if (value == this.gprsSettings) return;

                this.gprsSettings = value;
                base.OnPropertyChanged("GprsSettings");
            }
        }

        /// <summary>
        /// Creates a new instance of the MmsSettingsModel class.
        /// </summary>
        public MmsSettingsModel()
        {
            this.GprsSettings = new GprsSettingsModel();
            this.SettingsName = new BaseAccountSettingModel();
            this.Homepage = new BaseAccountSettingModel();
        }
    }

    [Serializable]
    public class GprsSettingsModel : SimSettingModel
    {
        /// <summary>
        /// Observable collection containing child SimSettingModel objects.
        /// </summary>
        [XmlIgnore]
        public override IList<SimSettingModel> Children
        {
            get
            {
                return new List<SimSettingModel>
                           {
                               this.authenticationType, 
                               this.accessPoint, 
                               this.username, 
                               this.password
                           };
            }
        }

        private BaseAccountSettingModel authenticationType;

        /// <summary>
        /// Gets or sets the authentication type for GPRS.
        /// </summary>
        [XmlElement("GprsAuthenticationType")]
        public BaseAccountSettingModel AuthenticationType
        {
            get { return this.authenticationType; }
            set
            {
                if (value == this.authenticationType) return;

                this.authenticationType = value;
                base.OnPropertyChanged("AuthenticationType");
            }
        }

        private BaseAccountSettingModel accessPoint;

        /// <summary>
        /// Gets or sets the access point for GPRS.
        /// </summary>
        [XmlElement("GprsAccessPoint")]
        public BaseAccountSettingModel AccessPoint
        {
            get { return this.accessPoint; }
            set
            {
                if (value == this.accessPoint) return;

                this.accessPoint = value;
                base.OnPropertyChanged("AccessPoint");
            }
        }

        private BaseAccountSettingModel username;

        /// <summary>
        /// Gets or sets the username for GPRS.
        /// </summary>
        [XmlElement("GprsUsername")]
        public BaseAccountSettingModel Username
        {
            get { return this.username; }
            set
            {
                if (value == this.username) return;

                this.username = value;
                base.OnPropertyChanged("Username");
            }
        }

        private BaseAccountSettingModel password;

        /// <summary>
        /// Gets or sets the password for GPRS.
        /// </summary>
        [XmlElement("GprsPassword")]
        public BaseAccountSettingModel Password
        {
            get { return this.password; }
            set
            {
                if (value == this.password) return;

                this.password = value;
                base.OnPropertyChanged("Password");
            }
        }

        /// <summary>
        /// Creates a new intance of the GprsSettingsModel class.
        /// </summary>
        public GprsSettingsModel()
        {
            this.AuthenticationType = new BaseAccountSettingModel() { Name = "GPRS Authentication Type" };
            this.AccessPoint = new BaseAccountSettingModel() { Name = "GPRS AccessPoint" };
            this.Username = new BaseAccountSettingModel() { Name = "GPRS Username" };
            this.Password = new BaseAccountSettingModel() { Name = "GPRS Password" };
        }
    }

    [Serializable]
    public class BaseAccountSettingModel : SimSettingModel, IXmlSerializable
    {
        private string name;

        /// <summary>
        /// Gets or sets the name for the setting.
        /// </summary>
        [XmlIgnore]
        public string Name
        {
            get { return this.name; }
            internal set
            {
                if (value == this.name) return;

                this.name = value;
                base.OnPropertyChanged("Name");
            }
        }

        private string displayName;

        /// <summary>
        /// Gets or sets the display name for the value.
        /// </summary>
        [XmlAttribute("DisplayName")]
        public string DisplayName
        {
            get { return string.IsNullOrEmpty(this.displayName) ? this.Name : this.displayName; }
            set
            {
                if (value == this.displayName) return;
   
                this.displayName = value;
                base.OnPropertyChanged("DisplayName");
            }
        }

        private string value;

        /// <summary>
        /// Gets or sets the value for the setting.
        /// </summary>
        [XmlAttribute("Value")]
        public string Value
        {
            get { return this.value; }
            set
            {
                if (value == this.value) return;

                this.value = value;
                base.OnPropertyChanged("Value");
            }
        }

        private object minValue;

        /// <summary>
        /// Gets or sets the minimum value for the setting.
        /// </summary>
        [XmlAttribute("MinValue")]
        protected object MinValue
        {
            get { return this.minValue; }
            set
            {
                if (value == this.minValue) return;

                this.minValue = value;
                base.OnPropertyChanged("MinValue");
            }
        }

        private object maxValue;

        /// <summary>
        /// Gets or sets the maximum value for the setting.
        /// </summary>
        [XmlAttribute("MaxValue")]
        protected object MaxValue
        {
            get { return this.maxValue; }
            set
            {
                if (value == this.maxValue) return;

                this.maxValue = value;
                base.OnPropertyChanged("MaxValue");
            }
        }

        private bool isMandatory;

        /// <summary>
        /// Gets or sets whether the setting is mandatory.
        /// </summary>
        [XmlAttribute("IsMandatory")]
        public bool IsMandatory
        {
            get { return this.isMandatory; }
            set
            {
                if (value == this.isMandatory) return;

                this.isMandatory = value;
                base.OnPropertyChanged("IsMandatory");
            }
        }

        private string description;

        /// <summary>
        /// Gets or sets the description for the setting.
        /// </summary>
        [XmlAttribute("Description")]
        public string Description
        {
            get { return this.description; }
            set
            {
                if (value == this.description) return;

                this.description = value;
                base.OnPropertyChanged("Description");
            }
        }

        private ValueTypeEnum valueType;

        /// <summary>
        /// Gets or sets the value type for the setting.
        /// </summary>
        [XmlAttribute("ValueType")]
        public ValueTypeEnum ValueType
        {
            get { return valueType; }
            set
            {
                if (value == this.valueType) return;

                valueType = value;
                base.OnPropertyChanged("ValueType");
            }
        }

        /// <summary>
        /// Gets whether the setting has a value.
        /// </summary>
        public bool HasValue { get { return this.Value != null && string.IsNullOrEmpty(this.Value.ToString()); } }

        /// <summary>
        /// Gets whether the setting has a minimum value.
        /// </summary>
        public bool HasMinValue { get { return this.MinValue != null && string.IsNullOrEmpty(this.MinValue.ToString()); } }

        /// <summary>
        /// Gets whether the setting has a maximum value.
        /// </summary>
        public bool HasMaxValue { get { return this.MaxValue != null && string.IsNullOrEmpty(this.MaxValue.ToString()); } }

        /// <summary>
        /// Gets whether the setting has a description.
        /// </summary>
        public bool HasDescription { get { return this.Description != null && string.IsNullOrEmpty(this.Description); } }

        /// <summary>
        /// Enum for the possible value types.
        /// </summary>
        public enum ValueTypeEnum
        {
            String = 0,
            Int = 1,
            Double = 2,
            Boolean = 3,
        }

        /// <summary>
        /// Creates a new instance of the BaseAccountSettingsModel.
        /// </summary>
        public BaseAccountSettingModel()
        {
            this.ValueType = ValueTypeEnum.String;
            this.IsMandatory = false;
        }

        /// <summary>
        /// Creates a new instance of the BaseAccountSettingsModel.
        /// </summary>
        public BaseAccountSettingModel(string name)
        {
            this.Name = name;
            this.ValueType = ValueTypeEnum.String;
            this.IsMandatory = false;
        }

        /// <summary>
        /// Creates a new instance of the BaseAccountSettingsModel.
        /// </summary>
        /// <param name="valueType">Value type of the setting.</param>
        public BaseAccountSettingModel(ValueTypeEnum valueType = ValueTypeEnum.String)
        {
            this.ValueType = valueType;
            this.IsMandatory = false;
        }

        #region [ IXmlSerializable Members ]

        public XmlSchema GetSchema() { return null; }

        public void ReadXml(XmlReader reader)
        {
            reader.MoveToContent();
            this.Name = reader.Name;
            this.Value = reader.GetAttribute("Value");
            this.MinValue = reader.GetAttribute("MinValue");
            this.MaxValue = reader.GetAttribute("MaxValue");

            //    Boolean isEmptyElement = reader.IsEmptyElement; // (1)
            //    reader.ReadStartElement();
            //    if (!isEmptyElement) // (1)
            //    {
            //        Birthday = DateTime.ParseExact(reader.
            //            ReadElementString("Birthday"), "yyyy-MM-dd", null);
            //        reader.ReadEndElement();
            //    }

        }

        public void WriteXml(XmlWriter writer)
        {
            writer.WriteAttributeString("Value", this.Value);
        }

        #endregion [ IXmlSerializable Members ]
    }

    public class StringAccountSettingModel : BaseAccountSettingModel
    {
        /// <summary>
        /// Gets or sets the string value of the setting.
        /// </summary>
        public new string Value
        {
            get { return (string)base.Value; }
            set { base.Value = value; }
        }

        /// <summary>
        /// Creates a new instance of the StringAccountSettingModel.
        /// </summary>
        public StringAccountSettingModel()
        {

        }
    }

    //public class IntAccountSettingModel : BaseAccountSettingModel
    //{
    //    /// <summary>
    //    /// Gets or sets the integer value of the setting.
    //    /// </summary>
    //    public new int Value
    //    {
    //        get { return (int)base.Value; }
    //        set { base.Value = value; }
    //    }

    //    /// <summary>
    //    /// Gets or sets the minimum integer value of the setting.
    //    /// </summary>
    //    public new int MinValue
    //    {
    //        get { return (int)base.MinValue; }
    //        set { base.MinValue = value; }
    //    }

    //    /// <summary>
    //    /// Gets or sets the minimum integer value of the setting.
    //    /// </summary>
    //    public new int MaxValue
    //    {
    //        get { return (int)base.MaxValue; }
    //        set { base.MaxValue = value; }
    //    }

    //    /// <summary>
    //    /// Creates a new instance of the IntAccountSettingModel.
    //    /// </summary>
    //    public IntAccountSettingModel()
    //    {

    //    }
    //}

    //public class DoubleAccountSettingModel : BaseAccountSettingModel
    //{
    //    /// <summary>
    //    /// Gets or sets the double value of the setting.
    //    /// </summary>
    //    public new double Value
    //    {
    //        get { return (double)base.Value; }
    //        set { base.Value = value; }
    //    }

    //    /// <summary>
    //    /// Gets or sets the minimum double value of the setting.
    //    /// </summary>
    //    public new double MinValue
    //    {
    //        get { return (double)base.MinValue; }
    //        set { base.MinValue = value; }
    //    }

    //    /// <summary>
    //    /// Gets or sets the maximum double value of the setting.
    //    /// </summary>
    //    public new double MaxValue
    //    {
    //        get { return (double)base.MaxValue; }
    //        set { base.MaxValue = value; }
    //    }

    //    /// <summary>
    //    /// Creates a newinstance of the DoubleAccountSettingModel.
    //    /// </summary>
    //    public DoubleAccountSettingModel()
    //    {

    //    }
    //}
}
