using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml.Linq;

namespace Marble.Utilities
{
    using Marble.Communication;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// Static utility class for acquiring data from SIM related files.
    /// </summary>
    public static class SimXmlParser
    {
        private static string unknownText = "Unknown";

        private static string notAvailableText = "N/A";

        /// <summary>
        /// Gets country name by using country code (MCC) from SimModel.
        /// </summary>
        /// <param name="countryCode">Country code (MCC).</param>
        /// <returns>Country name.</returns>
        public static string GetCountryName(string countryCode)
        {
            string filePath = MarblePaths.SimCountryDataFile;

            if (!File.Exists(filePath)) return notAvailableText;

            XElement rootElement = XElement.Load(filePath);

            string countryName =
                rootElement.Elements().Where(countryElement => countryElement.Name == "country").SelectMany(countryElement => 
                    (from dataElement in countryElement.Elements()                                                                                              
                     where dataElement.Name == "Data"                                                                                            
                     where dataElement.Attributes().Where(attribute => attribute.Name == "Code").Any(attribute => attribute.Value == countryCode)                                                                                            
                     select dataElement.Attribute("Name"))).Select(nameAttribute => nameAttribute != null ? nameAttribute.Value : unknownText).FirstOrDefault();

            return string.IsNullOrEmpty(countryName) ? unknownText : countryName;
        }

        /// <summary>
        /// Gets operator name by using operator code (MNC) and country code (MCC) from SimModel.
        /// </summary>
        /// <param name="operatorCode">Operator code (MNC).</param>
        /// <param name="countryCode">Country code (MCC).</param>
        /// <returns>Operator name.</returns>
        public static string GetOperatorName(string operatorCode, string countryCode)
        {
            string filePath = MarblePaths.SimOperatorDataFile;

            if (!File.Exists(filePath)) return notAvailableText;

            XElement rootElement = XElement.Load(filePath);

            string operatorNameTxt =
                   (from packageElement in rootElement.Elements() 
                    where packageElement.Elements("mnc").Where(networkCodeElement => networkCodeElement.Value == operatorCode).Any(
                        networkCodeElement => packageElement.Elements("mcc").Any(
                            countryCodeElement => countryCodeElement.Value == countryCode)) 
                    select packageElement.Element("providerid") into operatorName 
                    select operatorName != null ? operatorName.Value : unknownText).FirstOrDefault();

            return string.IsNullOrEmpty(operatorNameTxt) ? unknownText : operatorNameTxt;
        }

        public static string GetPhoneNumberForSim(string imsi)
        {
            return SimXmlParser.getChangeableSimValueForSim(ChangeableSimValue.PhoneNumber, imsi);
        }

        public static string GetPinCodeForSim(string imsi)
        {
            return SimXmlParser.getChangeableSimValueForSim(ChangeableSimValue.PinCode, imsi);
        }

        public static string GetPin2CodeForSim(string imsi)
        {
            return SimXmlParser.getChangeableSimValueForSim(ChangeableSimValue.Pin2Code, imsi);
        }

        public static string GetPuk1CodeForSim(string imsi)
        {
            return SimXmlParser.getChangeableSimValueForSim(ChangeableSimValue.Puk1Code, imsi);
        }

        public static string GetPuk2CodeForSim(string imsi)
        {
            return SimXmlParser.getChangeableSimValueForSim(ChangeableSimValue.Puk2Code, imsi);
        }

        public static string GetServiceNumberForSim(string imsi)
        {
            return SimXmlParser.getChangeableSimValueForSim(ChangeableSimValue.ServiceNumber, imsi);
        }

        public static string GetVoiceMailNumberForSim(string imsi)
        {
            return SimXmlParser.getChangeableSimValueForSim(ChangeableSimValue.VoiceMailNumber, imsi);
        }

        private static string getChangeableSimValueForSim(ChangeableSimValue changeableSimValue, string imsi)
        {
            string filePath = MarblePaths.SimDataFile;

            if (!File.Exists(filePath)) return null;

            XElement rootElement = XElement.Load(filePath);

            return (from simElement in rootElement.Elements("Sim")
                    let imsiAttribute = simElement.Attribute("Imsi")
                    where imsiAttribute != null && imsiAttribute.Value == imsi
                    select simElement.Attribute(changeableSimValue.ToString()) into changeableSimValueAttribute
                    where changeableSimValueAttribute != null
                    select changeableSimValueAttribute.Value).FirstOrDefault();
        }

        /// <summary>
        /// Adds SIM to the file containing all found SIMs.
        /// </summary>
        /// <param name="simModel">SimModel object.</param>
        /// <param name="changeValuesForExisting">Bool value indicating whether change values for SIM which already exists in the SIM file.</param>
        /// <returns>Value indicating whether saving changes succeeded.</returns>
        public static bool AddSimToSimList(SimModel simModel, bool changeValuesForExisting = true)
        {
            string filePath = MarblePaths.SimDataFile;

            if (!createSimDataFile()) return false;

            XElement rootElement = XElement.Load(filePath);

            removeEmptyPhoneNumberFromSimList(simModel, rootElement);
            addSimElementToSimList(simModel, rootElement, changeValuesForExisting);
            simModel.UpdateCancelValues();
            
            rootElement.Save(filePath);

            return true;
        }

        /// <summary>
        /// Adds SIMs to the file containing all found SIMs.
        /// </summary>
        /// <param name="simModels">List of SimModel object.</param>
        /// <param name="changeValuesForExisting">Bool value indicating whether change values for SIM which already exists in the SIM file.</param>
        /// <returns>Value indicating whether saving changes succeeded.</returns>
        public static bool AddSimToSimList(List<SimModel> simModels, bool changeValuesForExisting = true)
        {
            string filePath = MarblePaths.SimDataFile;

            if (!createSimDataFile()) return false;

            XElement rootElement = XElement.Load(filePath);

            foreach (SimModel simModel in simModels)
            {
                removeEmptyPhoneNumberFromSimList(simModel, rootElement);
                addSimElementToSimList(simModel, rootElement, changeValuesForExisting);
                simModel.UpdateCancelValues();
            }

            rootElement.Save(filePath);

            return true;
        }

        /// <summary>
        /// Checks whether the phone number in SimModel exists in SIM list.
        /// </summary>
        /// <param name="simModel">SimModel object.</param>
        /// <returns>Bool value indicating whether the phone number exists in SIM list.</returns>
        public static bool CheckPhoneNumberExistanceInSimList(SimModel simModel)
        {
            return CheckPhoneNumberExistanceInSimList(simModel.PhoneNumber, simModel.Imsi);
        }

        /// <summary>
        /// Checks whether the phone number exists in SIM list.
        /// </summary>
        /// <param name="phoneNumber">Phone number as a string.</param>
        /// <param name="imsi">IMSI of the SIM.</param>
        /// <returns>Bool value indicating whether the phone number exists in SIM list.</returns>
        public static bool CheckPhoneNumberExistanceInSimList(string phoneNumber, string imsi)
        {
            string filePath = MarblePaths.SimDataFile;

            if (!File.Exists(filePath)) return false;

            XElement rootElement = XElement.Load(filePath);

            return rootElement.Elements("Sim").Where(
                simElement => simElement.Attribute("Imsi").Value != imsi).Any(
                simElement => simElement.Attribute("PhoneNumber").Value == phoneNumber);
        }

        /// <summary>
        /// Gets dictionary where IMSI is the key and phone number is the value.
        /// </summary>
        /// <returns>Dictionary containing phone numbers.</returns>
        public static Dictionary<string, string> GetPhoneNumberDictionaryFromSimList()
        {
            string filePath = MarblePaths.SimDataFile;

            if (!File.Exists(filePath)) return null;

            XElement rootElement = XElement.Load(filePath);

            return rootElement.Elements("Sim").Where(
                simElement => !string.IsNullOrEmpty(simElement.Attribute("Imsi").Value) && 
                    !string.IsNullOrEmpty(simElement.Attribute("PhoneNumber").Value)).ToDictionary(
                    simElement => simElement.Attribute("Imsi").Value, simElement => simElement.Attribute("PhoneNumber").Value);
        }

        public static string GetSettingValuePath(ChangeableSimValue changeableSimValue, int simSlot = 1)
        {
            if (simSlot < 1) simSlot = 1;

            string settingValuePathRoot = simSlot == 1 ? "Main/Account/" : "Main/Account" + simSlot + "/";

            switch (changeableSimValue)
            {
                case ChangeableSimValue.PhoneNumber:
                    return settingValuePathRoot + "phone number";
                case ChangeableSimValue.PinCode:
                    return settingValuePathRoot + "pin code";
                case ChangeableSimValue.Pin2Code:
                    return settingValuePathRoot + "pin2 code";
                case ChangeableSimValue.Puk1Code:
                    return settingValuePathRoot + "puk1 code";
                case ChangeableSimValue.Puk2Code:
                    return settingValuePathRoot + "puk2 code";
                case ChangeableSimValue.ServiceNumber:
                    return settingValuePathRoot + "service number";
                case ChangeableSimValue.VoiceMailNumber:
                    return settingValuePathRoot + "voice mail number";
                default:
                    throw new ArgumentOutOfRangeException("changeableSimValue");
            }
        }

        private static bool addSimElementToSimList(SimModel simModel, XElement rootElement, bool changeValuesForExisting = true)
        {
            if (string.IsNullOrEmpty(simModel.PhoneNumber)) return false;

            bool imsiExists = false;

            foreach (
                XElement simElement in
                    rootElement.Elements("Sim").Where(
                        simElement => simElement.Attribute("Imsi").Value == simModel.Imsi))
            {
                imsiExists = true;

                if (changeValuesForExisting)
                {
                    foreach (var simValueType in Enum.GetNames(typeof(ChangeableSimValue)))
                    {
                        ChangeableSimValue changeableSimValue;
                        Enum.TryParse(simValueType, out changeableSimValue);

                        SimXmlParser.setSimElementAttributeValue(simElement, simModel, changeableSimValue);
                    }
                }

                break;
            }

            if (!imsiExists)
            {
                rootElement.Add(SimXmlParser.CreateSimElementFromSimModel(simModel));
            }

            return true;
        }

        /// <summary>
        /// Returns new XElement containing SIM information from SimModel object.
        /// </summary>
        /// <param name="simModel">SimModel object.</param>
        /// <returns>New XElement containing SimModel information.</returns>
        public static XElement CreateSimElementFromSimModel(SimModel simModel)
        {
            XElement simElement = new XElement("Sim");

            simElement.SetAttributeValue("Imsi", simModel.Imsi);
            simElement.SetAttributeValue("CountryCode", simModel.CountryCode);
            simElement.SetAttributeValue("NetworkCode", simModel.NetworkCode);
            simElement.SetAttributeValue("IdNumber", simModel.IdNumber);
            simElement.SetAttributeValue("PhoneNumber", simModel.PhoneNumber);
            simElement.SetAttributeValue("PinCode", simModel.PinCode);
            simElement.SetAttributeValue("Pin2Code", simModel.Pin2Code);
            simElement.SetAttributeValue("Puk1Code", simModel.Puk1Code);
            simElement.SetAttributeValue("Puk2Code", simModel.Puk2Code);
            simElement.SetAttributeValue("ServiceNumber", simModel.ServiceNumber);
            simElement.SetAttributeValue("VoiceMailNumber", simModel.VoiceMailNumber);

            return simElement;
        }

        private static bool createSimDataFile(bool overwrite = false)
        {
            if (File.Exists(MarblePaths.SimDataFile))
            {
                if (new FileInfo(MarblePaths.SimDataFile).Length <= 0)
                    File.Delete(MarblePaths.SimDataFile);
            }

            if (File.Exists(MarblePaths.SimDataFile) && !overwrite) return true;

            if (!File.Exists(MarblePaths.SimDataFile) || overwrite)
            {
                XDocument simDataDocument = new XDocument(new XElement("SimDataRecords"));
                simDataDocument.Save(MarblePaths.SimDataFile);
            }

            return true;
        }

        private static void removeEmptyPhoneNumberFromSimList(SimModel simModel, XElement rootElement)
        {
            if (!string.IsNullOrEmpty(simModel.PhoneNumber)) return;

            foreach (XElement simElement in from simElement in rootElement.Elements("Sim") let imsiAttribute = simElement.Attribute("Imsi") where imsiAttribute != null && imsiAttribute.Value == simModel.Imsi select simElement)
            {
                simElement.Remove();
                return;
            }
        }

        private static void setSimElementAttributeValue(XElement simElement, SimModel simModel, ChangeableSimValue changeableSimValue)
        {
            XAttribute attribute = simElement.Attribute(changeableSimValue.ToString());

            if (attribute == null)
            {
                simElement.SetAttributeValue(changeableSimValue.ToString(), string.Empty);
                attribute = simElement.Attribute(changeableSimValue.ToString());
            }

            switch (changeableSimValue)
            {
                case ChangeableSimValue.PhoneNumber:
                    attribute.SetValue(!string.IsNullOrEmpty(simModel.PhoneNumber) ? simModel.PhoneNumber : string.Empty);
                    break;
                case ChangeableSimValue.PinCode:
                    attribute.SetValue(!string.IsNullOrEmpty(simModel.PinCode) ? simModel.PinCode : string.Empty);
                    break;
                case ChangeableSimValue.Pin2Code:
                    attribute.SetValue(!string.IsNullOrEmpty(simModel.Pin2Code) ? simModel.Pin2Code : string.Empty);
                    break;
                case ChangeableSimValue.Puk1Code:
                    attribute.SetValue(!string.IsNullOrEmpty(simModel.Puk1Code) ? simModel.Puk1Code : string.Empty);
                    break;
                case ChangeableSimValue.Puk2Code:
                    attribute.SetValue(!string.IsNullOrEmpty(simModel.Puk2Code) ? simModel.Puk2Code : string.Empty);
                    break;
                case ChangeableSimValue.VoiceMailNumber:
                    attribute.SetValue(!string.IsNullOrEmpty(simModel.VoiceMailNumber) ? simModel.VoiceMailNumber : string.Empty);
                    break;
                case ChangeableSimValue.ServiceNumber:
                    attribute.SetValue(!string.IsNullOrEmpty(simModel.ServiceNumber) ? simModel.ServiceNumber : string.Empty);
                    break;
                default:
                    throw new ArgumentOutOfRangeException("changeableSimValue");
            }
        }

        #region [ Operator Specific Settings from WBXML files ]

        /// <summary>
        /// Gets operator specific SIM settings file name by using operator code (MNC) and country code (MCC) from SimModel.
        /// </summary>
        /// <param name="operatorCode">Operator code (MNC).</param>
        /// <param name="countryCode">Country code (MCC).</param>
        /// <returns>Operator specific SIM settings file name.</returns>
        public static string GetOperatorSimSettingsFileName(string operatorCode, string countryCode)
        {
            string filePath = MarblePaths.SimOperatorDataFile;

            if (!File.Exists(filePath)) return null;

            XElement rootElement = XElement.Load(filePath);

            return (from packageElement in rootElement.Elements()
                    where packageElement.Elements("mnc").Where(networkCodeElement => networkCodeElement.Value == operatorCode).Any(
                        networkCodeElement => packageElement.Elements("mcc").Any(
                            countryCodeElement => countryCodeElement.Value == countryCode))
                    select packageElement.Element("providerid") into operatorSimSettingsFileName
                    select operatorSimSettingsFileName != null ? operatorSimSettingsFileName.Value : null).FirstOrDefault();
        }

        public static string GetSimSetting(string settingName)
        {
            switch (settingName.ToLower())
            {
                case "mms-gprs-access point":
                    return getSimSetting(
                        "access point",
                        @"C:\Temp\operators\omadm_settings\cc2204_sonera_fi.settings",
                        new List<string>() { "MMS", "GPRS" });
                default:
                    return null;

            }
        }

        private static string getSimSetting(string settingName, string settingsFileName, List<string> branchNames)
        {
            string filePath = MarblePaths.SimOperatorDataFile;

            filePath = @"C:\Temp\operators\omadm_settings\cc2204_sonera_fi.settings";

            if (!File.Exists(filePath)) return null;

            XElement simSettingElement = getChildBranchSimSetting(settingName, branchNames, 0, XElement.Load(filePath).Element("property"));
            XAttribute attribute = simSettingElement.Attribute("val");

            return attribute != null ? attribute.Value : null;
        }

        private static XElement getChildBranchSimSetting(string settingName, List<string> branchNames, int currentLevel, XElement parentElement)
        {
            if (currentLevel < 0) return null;
            if (branchNames == null) return null;
            if (branchNames.Count < currentLevel) return null;

            foreach (XElement childElement in parentElement.Elements("property"))
            {
                if (currentLevel == branchNames.Count)
                {
                    XAttribute propertyNameAttribute = childElement.Attribute("name");

                    if (propertyNameAttribute == null) continue;
                    if (propertyNameAttribute.Value != settingName) continue;

                    return childElement;
                }

                XAttribute branchAttribute = childElement.Attribute("branch");
                
                if (branchAttribute == null) continue;

                XAttribute branchNameAttribute = childElement.Attribute("name");

                if (branchNameAttribute == null) continue;
                if (branchNameAttribute.Value != branchNames[currentLevel]) continue;

                currentLevel++;

                return getChildBranchSimSetting(settingName, branchNames, currentLevel, childElement);
            }

            return null;
        }

        private static string getSimSetting(string settingName, string settingsFileName, string settingType = null)
        {
            string filePath = MarblePaths.SimOperatorDataFile;

            if (!File.Exists(filePath)) return null;

            XElement rootElement = XElement.Load(filePath);

            foreach (XElement characteristicElement in rootElement.Elements())
            {
                foreach (XElement childElement in characteristicElement.Elements())
                {
                    
                }
            }

            return null;
        }

        private static string getFirstParamNameByCharacteristicType(string characteristicType)
        {
            switch (characteristicType)
            {
                case "PXLOGICAL":
                    return "PROXY-ID";
                case "PXPHYSICAL":
                    return "PHYSICAL-PROXY-ID";
                case "PORT":
                    return "PORTNBR";
                case "NAPDEF":
                    return "NAPID";
                case "NAPAUTHINFO":
                    return "AUTHTYPE";
                case "APPLICATION":
                    return "APPID";
                case "RESOURCE":
                    return "URI";
                default:
                    return null;
            }
        }

        #endregion [ Operator Specific Settings from WBXML files ]

        #region [ Enums ]

        /// <summary>
        /// The changeable SIM value, values which user can change from SIM. 
        /// </summary>
        public enum ChangeableSimValue
        {
            PhoneNumber = 0,
            PinCode = 1,
            Pin2Code = 2,
            Puk1Code = 3,
            Puk2Code = 4,
            ServiceNumber = 5,
            VoiceMailNumber = 6,
        }

        #endregion [ Enums ]
    }
}
