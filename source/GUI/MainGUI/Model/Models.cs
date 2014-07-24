using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
// own imports
using System.Xml.Linq;
using System.Xml;
using System.IO;
using System.ComponentModel;
using System.Collections.ObjectModel;
using System.Windows;

using MediatorLib;

/// <summary>
/// Contains models for the Marble UI.
/// </summary>
namespace Marble.Model
{
    using System.Collections.Specialized;
    using System.Diagnostics;
    using System.Globalization;
    using System.Threading;

    using Marble.Utilities;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// Test runtime time units enum.
    /// </summary>
    public enum TestRuntimeUnit
    {
        /// <summary>
        /// Runtime is defined with minutes.
        /// </summary>
        Minutes = 0,

        /// <summary>
        /// Runtime is defined with hours.
        /// </summary>
        Hours = 1,

        /// <summary>
        /// Runtime is defined with days.
        /// </summary>
        Days = 2,
    }

    /// <summary>
    /// Test result enum.
    /// </summary>
    public enum TestResultEnum
    {
        /// <summary>
        /// Result is not available (e.g. test case has not been executed).
        /// </summary>
        NotAvailable = 0,

        /// <summary>
        /// Test case passed test execution.
        /// </summary>
        Passed = 1,

        /// <summary>
        /// Test case failed test execution.
        /// </summary>
        Failed = 2,

        /// <summary>
        /// Test case did not get result (e.g. test case was aborted while test execution).
        /// </summary>
        NoResult = 3
    }

    /// <summary>
    /// Model for individual settings item.
    /// </summary>
    public class SettingsItem : INotifyPropertyChanged
    {
        private string name;

        /// <summary>
        /// Gets or sets the name of the setting.
        /// </summary>
        public string Name
        {
            get { return this.name; }
            set
            {
                this.name = value;
                this.OnPropertyChanged("Name");
            }
        }

        private string type;

        /// <summary>
        /// Gets or sets the type of setting item.
        /// </summary>
        public string Type
        {
            get { return this.type; }
            set
            {
                this.type = value;
                this.OnPropertyChanged("Type");
            }
        }

        private string urlType;

        /// <summary>
        /// Gets or sets the URL type.
        /// </summary>
        public string UrlType
        {
            get { return this.urlType; }
            set
            {
                this.urlType = value;
                this.OnPropertyChanged("UrlType");
            }
        }

        private string hint;

        /// <summary>
        /// Gets or sets a short description of the setting.
        /// </summary>
        public string Hint
        {
            get { return this.hint; }
            set
            {
                this.hint = value;
                this.OnPropertyChanged("Hint");
            }
        }

        private string value;

        /// <summary>
        /// Gets or sets a value of the setting item.
        /// </summary>
        public string Value
        {
            get { return this.value; }
            set
            {
                this.value = value;
                this.OnPropertyChanged("Value");
            }
        }

        private string branch;

        /// <summary>
        /// Gets or sets the branch where setting belongs to.
        /// </summary>
        public string Branch
        {
            get { return this.branch; }
            set
            {
                this.branch = value;
                this.OnPropertyChanged("Branch");
            }
        }

        private string mandatory;

        /// <summary>
        /// Gets or sets a value indicating whether the setting is mandatory.
        /// </summary>
        public string Mandatory
        {
            get { return this.mandatory; }
            set
            {
                this.mandatory = value;
                this.OnPropertyChanged("Mandatory");
            }
        }

        private string validValues;

        /// <summary>
        /// Gets or sets a value indicating the valid values for the setting.
        /// </summary>
        public string ValidValues
        {
            get { return this.validValues; }
            set
            {
                this.validValues = value;
                this.OnPropertyChanged("ValidValues");
            }
        }

        private string minValue;

        /// <summary>
        /// Gets or sets the minimum value for the setting.
        /// </summary>
        public string MinValue
        {
            get { return this.minValue; }
            set
            {
                this.minValue = value;
                this.OnPropertyChanged("MinValue");
            }
        }

        private string maxValue;

        /// <summary>
        /// Gets or sets the maximum value for the setting.
        /// </summary>
        public string MaxValue
        {
            get { return this.maxValue; }
            set
            {
                this.maxValue = value;
                this.OnPropertyChanged("MaxValue");
            }
        }

        private string booleanType;

        /// <summary>
        /// Gets or set the type of boolean field (True|False, On|Off).
        /// </summary>
        public string BooleanType
        {
            get { return this.booleanType; }
            set
            {
                this.booleanType = value;
                this.OnPropertyChanged("BooleanType");
            }
        }

        private int level;

        /// <summary>
        /// Gets or sets the level in the settings tree.
        /// </summary>
        public int Level
        {
            get { return this.level; }
            set
            {
                this.level = value;
                this.OnPropertyChanged("Level");
            }
        }

        private string parentElement;

        /// <summary>
        /// Gets or sets the parent XML element name.
        /// </summary>
        public string ParentElement
        {
            get { return this.parentElement; }
            set
            {
                this.parentElement = value;
                this.OnPropertyChanged("ParentElement");
            }
        }

        private bool isVisible;

        /// <summary>
        /// Gets or sets a value indicating whether the setting is visible.
        /// </summary>
        public bool IsVisible
        {
            get { return this.isVisible; }
            set
            {
                this.isVisible = value;
                this.OnPropertyChanged("IsVisible");
            }
        }

        private bool hasChildren;

        /// <summary>
        /// Gets or sets a value indicating whether the setting has child settings.
        /// </summary>
        public bool HasChildren
        {
            get { return this.hasChildren; }
            set
            {
                this.hasChildren = value;
                this.OnPropertyChanged("HasChildren");
            }
        }

        private bool isExpanded;

        /// <summary>
        /// Gets or sets a value indicating whether the setting is expanded.
        /// </summary>
        public bool IsExpanded
        {
            get { return this.isExpanded; }
            set
            {
                this.isExpanded = value;
                this.OnPropertyChanged("IsExpanded");
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

    /// <summary>
    /// Encapsulates settings related operations.
    /// </summary>
    public class SettingsModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Settings element of the settings file.
        /// </summary>
        private XElement settingsRoot;

        /// <summary>
        /// Whole loaded settings document.
        /// </summary>
        private XDocument settingsDocument;

        /// <summary>
        /// Gets the file path of the loaded settings file.
        /// </summary>
        public string DocumentPath { get; private set; }

        /// <summary>
        /// Gets or sets object which holds the latest selected SettingsItem from UI.
        /// </summary>
        public SettingsItem SelectedSettingsItem { get; set; }

        /// <summary>
        /// Gets or sets observable collection holding all valid_values strings for SettingsItems.
        /// </summary>
        public ObservableCollectionAdv<string> SettingsComboBoxCollection { get; set; }

        private ObservableCollectionAdv<SettingsItem> _changedSettingsItem;

        /// <summary>
        /// Gets or sets observable collection containing changed settings items.
        /// </summary>
        public ObservableCollectionAdv<SettingsItem> ChangedSettingsitemsCollection
        {
            get { return this._changedSettingsItem; }
            set
            {
                this._changedSettingsItem = value;
                this.OnPropertyChanged("ChangedSettingsitemsCollection");
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SettingsModel"/> class. 
        /// Loads an existing settings file
        /// </summary>
        /// <param name="path">File system path of the existing settings file to load</param>
        public SettingsModel(string path)
        {
            this.SettingsComboBoxCollection = new ObservableCollectionAdv<string>();
            this.ChangedSettingsitemsCollection = new ObservableCollectionAdv<SettingsItem>();
            this.Load(path);
        }

        /// <summary>
        /// Looks for an element from the settings tree and returns it
        /// </summary>
        /// <param name="settingPath">Xml tree path to the wanted element</param>
        /// <returns>Matching element or null</returns>
        public XElement GetSettingElement(string settingPath)
        {
            // split path elements
            string[] steps = settingPath.Split(new char[] { '/', '\\', ',', '|', '.' });

            // traverse the tree element a time to the wanted element
            XElement currentElement = settingsRoot;

            foreach (string t in steps)
            {
                // select the child element that matches the name of the current step
                var query = from property in currentElement.Elements("property")
                            where (string)property.Attribute("name") == t
                            select property;

                // match found
                if (query.Any())
                    currentElement = query.First();
                else
                    return null;
            }

            return currentElement;
        }

        /// <summary>
        /// Returns the value of a single setting item
        /// </summary>
        /// <param name="settingPath">Xml tree path to the desired setting</param>
        /// <returns>The value of the desired setting or null</returns>
        public string GetValue(string settingPath)
        {
            XElement setting = this.GetSettingElement(settingPath);

            return setting != null ? setting.Attribute("val").Value : null;
        }

        /// <summary>
        /// Sets the value of a single setting item
        /// </summary>
        /// <param name="settingPath">Xml tree path to the setting item to be set</param>
        /// <param name="newValue">New value of the setting item</param>
        /// <returns>True if setting was found and set otherwise false</returns>
        public bool SetValue(string settingPath, string newValue)
        {
            if (newValue == null)
                newValue = string.Empty;

            XElement setting = this.GetSettingElement(settingPath);

            if (setting == null)
            {
                this.CreateNewSetting(settingPath);
                setting = this.GetSettingElement(settingPath);

                if (setting == null) return false;
            }

            XAttribute attribute = setting.Attribute("val");

            if (attribute != null)
            {
                attribute.Value = newValue;
            }

            return true;
        }

        public void CreateNewSetting(string settingPath)
        {
            // split path elements
            string[] steps = settingPath.Split(new char[] { '/', '\\', ',', '|', '.' });

            // traverse the tree element a time to the wanted element
            XElement currentElement = settingsRoot;

            foreach (string t in steps)
            {
                // select the child element that matches the name of the current step
                var query = from property in currentElement.Elements("property")
                            where (string)property.Attribute("name") == t
                            select property;

                // match found
                if (query.Any())
                    currentElement = query.First();
                else
                {
                    XElement newSettingElement = SettingsModel.createNewSettingXElement(t);
                    currentElement.Add(newSettingElement);
                    currentElement = newSettingElement;
                }
            }
        }

        /// <summary>
        /// Loads an existing settings file.
        /// </summary>
        /// <param name="path">File system path of the existing settings file to load</param>
        public void Load(string path)
        {
            if (File.Exists(path))
            {
                this.settingsDocument = XDocument.Load(path);
                this.DocumentPath = path;

                // get the settings root from the document
                var query = from property in this.settingsDocument.Root.Elements("property")
                            where (string)property.Attribute("name") == "Settings"
                            select property;

                this.settingsRoot = query.First();
            }
            else
            {
                // TODO: Remove this MessageBox and the Exit(0) after missing settings file situation is fixed.
                System.Windows.MessageBox.Show(
                    path + " was not found. Please include it and restart Marble.",
                    "Missing settings file",
                    System.Windows.MessageBoxButton.OK);

                // Environment.Exit(0) used because we don't need to do any preparations before killing the application.
                // This will terminate all threads, so nothing should be left behind.
                Environment.Exit(0);

                // Create XDocument with empty settings element if settings file doesn't exist.
                XElement configurationElement = new XElement("configuration");
                configurationElement.SetAttributeValue("version", "50");

                XElement settingsElement = new XElement("property");
                settingsElement.SetAttributeValue("booleanType", "TrueFalse");
                settingsElement.SetAttributeValue("branch", "No");
                settingsElement.SetAttributeValue("hint", string.Empty);
                settingsElement.SetAttributeValue("mandatory", "False");
                settingsElement.SetAttributeValue("max_value", string.Empty);
                settingsElement.SetAttributeValue("min_value", string.Empty);
                settingsElement.SetAttributeValue("name", "Settings");
                settingsElement.SetAttributeValue("type", "Str");
                settingsElement.SetAttributeValue("urlType", string.Empty);
                settingsElement.SetAttributeValue("val", string.Empty);
                settingsElement.SetAttributeValue("valid_values", string.Empty);

                configurationElement.Add(settingsElement);

                settingsDocument = new XDocument(new XDeclaration("1.0", "utf-8", "yes"), configurationElement);

                // get the settings root from the document
                var query = from property in settingsDocument.Root.Elements("property")
                            where (string)property.Attribute("name") == "Settings"
                            select property;

                settingsRoot = query.First();

                this.DocumentPath = path;
            }
        }

        /// <summary>
        /// Saves the current settings document to a file
        /// </summary>
        /// <param name="path">File system path to the resulting settings file. If empty same path used as on load.</param>
        public void Save(string path = "")
        {
            if (this.settingsDocument == null)
                return;

            if (path.Length > 0)
                this.DocumentPath = path;

            this.settingsDocument.Save(this.DocumentPath);
        }

        /// <summary>
        /// Parses settings data from the Settings file with the given settings name.
        /// </summary>
        /// <param name="settingsFile">Settings file</param>
        /// <param name="level">Settings tree level</param>
        /// <param name="name">Settings name</param>
        /// <returns>Returns ObservableCollection of SettingsItem objects</returns>
        public ObservableCollection<SettingsItem> GetSettingsItemCollection(string settingsFile, int level, string name)
        {
            List<SettingsItem> settingsItemList = new List<SettingsItem>();
            List<SettingsItem> tempList = new List<SettingsItem>();

            // Add the boolean types to collection.
            this.SettingsComboBoxCollection.Add("True;False");
            this.SettingsComboBoxCollection.Add("On;Off");

            try
            {
                FileInfo fi = new FileInfo(settingsFile);

                XElement rootHierarchy = XElement.Load(settingsFile);

                var results = from property in rootHierarchy.Descendants("property")
                              select property;

                foreach (XElement element in results)
                {
                    XAttribute attribute = element.Attribute("name");

                    if (attribute != null && attribute.Value != name)
                    {
                        continue;
                    }

                    if (!SettingsComboBoxCollection.Contains(element.Attribute("valid_values").Value) && element.Attribute("valid_values").Value.Length > 0)
                        SettingsComboBoxCollection.Add(element.Attribute("valid_values").Value);

                    SettingsItem settingsItem = new SettingsItem();
                    settingsItem.BooleanType = element.Attribute("booleanType").Value;
                    settingsItem.Branch = element.Attribute("branch").Value;
                    settingsItem.Hint = element.Attribute("hint").Value;
                    settingsItem.Mandatory = element.Attribute("mandatory").Value;
                    settingsItem.MaxValue = element.Attribute("max_value").Value;
                    settingsItem.MinValue = element.Attribute("min_value").Value;
                    settingsItem.Name = element.Attribute("name").Value;
                    settingsItem.Type = element.Attribute("type").Value;
                    settingsItem.UrlType = element.Attribute("urlType").Value;
                    settingsItem.Value = "";
                    settingsItem.ValidValues = element.Attribute("valid_values").Value;
                    settingsItem.ParentElement = "";
                    settingsItem.Level = level;
                    settingsItem.IsVisible = level == 1;
                    settingsItem.HasChildren = settingsItem.Type == "URL";

                    settingsItemList.Add(settingsItem);

                    if (element.Elements().Any())
                    {
                        IEnumerable<XElement> elementList = element.Elements();
                        tempList = this.GetSettingsItemCollection(elementList, level + 1, settingsItem.Name);
                        settingsItemList.AddRange(tempList);
                    }

                    break;
                }
            }
            catch
            {
                // TODO: Handle exception.
            }

            ObservableCollection<SettingsItem> generalSettingsModelCollection = new ObservableCollection<SettingsItem>(settingsItemList);

            return generalSettingsModelCollection;
        }

        private static XElement createNewSettingXElement(string name)
        {
            if (string.IsNullOrEmpty(name)) return null;

            XElement newSettingElement = new XElement("property");
            newSettingElement.SetAttributeValue("booleanType", "TrueFalse");
            newSettingElement.SetAttributeValue("branch", "No");
            newSettingElement.SetAttributeValue("hint", string.Empty);
            newSettingElement.SetAttributeValue("mandatory", "False");
            newSettingElement.SetAttributeValue("max_value", string.Empty);
            newSettingElement.SetAttributeValue("min_value", string.Empty);
            newSettingElement.SetAttributeValue("name", name);
            newSettingElement.SetAttributeValue("type", "Str");
            newSettingElement.SetAttributeValue("urlType", string.Empty);
            newSettingElement.SetAttributeValue("val", string.Empty);
            newSettingElement.SetAttributeValue("valid_values", string.Empty);

            return newSettingElement;
        }

        /// <summary>
        /// Parses settings data from the settings elements.
        /// </summary>
        /// <param name="elements">XElement collection</param>
        /// <param name="level">Settings tree level</param>
        /// <param name="parentElement">Parent element name</param>
        /// <returns>Returns a list of SettingsItem objects</returns>
        private List<SettingsItem> GetSettingsItemCollection(IEnumerable<XElement> elements, int level, string parentElement)
        {
            List<SettingsItem> settingsItemList = new List<SettingsItem>();
            List<SettingsItem> tempList = new List<SettingsItem>();

            foreach (XElement element in elements)
            {
                if (!this.SettingsComboBoxCollection.Contains(element.Attribute("valid_values").Value) && element.Attribute("valid_values").Value != string.Empty)
                    SettingsComboBoxCollection.Add(element.Attribute("valid_values").Value);

                SettingsItem settingsItem = new SettingsItem();
                settingsItem.BooleanType = element.Attribute("booleanType").Value;
                settingsItem.Branch = element.Attribute("branch").Value;
                settingsItem.Hint = element.Attribute("hint").Value;
                settingsItem.Mandatory = element.Attribute("mandatory").Value;
                settingsItem.MaxValue = element.Attribute("max_value").Value;
                settingsItem.MinValue = element.Attribute("min_value").Value;
                settingsItem.Name = element.Attribute("name").Value;
                settingsItem.Type = element.Attribute("type").Value;
                settingsItem.UrlType = element.Attribute("urlType").Value;

                settingsItem.Value = element.Attribute("val") != null ? element.Attribute("val").Value : "";

                settingsItem.ValidValues = element.Attribute("valid_values").Value;
                settingsItem.ParentElement = parentElement;
                settingsItem.Level = level;

                settingsItem.IsVisible = level == 1;

                if (element.Elements().Any())
                {
                    settingsItem.HasChildren = true;
                    settingsItem.Value = string.Empty;
                }
                else
                {
                    settingsItem.HasChildren = false;
                }

                settingsItemList.Add(settingsItem);

                if (element.Elements().Any())
                {
                    IEnumerable<XElement> elementList = element.Elements();
                    tempList = this.GetSettingsItemCollection(elementList, level + 1, parentElement + @"\" + settingsItem.Name);
                    settingsItemList.AddRange(tempList);
                }
            }

            return settingsItemList;
        }

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }

    /// <summary>
    /// Encapsulates product specific information from a test package.
    /// </summary>
    public class TestPackageModel
    {
        // example of each attribute provided
        // s40_11_2_cs16_family
        public string productFamilyConfig { get; private set; }
        // s40_11_2_cs16
        public string productFamilyName { get; private set; }
        // gaia_ds_config
        public string productConfig { get; private set; }
        // Gaia DS
        public string productName { get; private set; }
        // RM-766
        public string productType { get; private set; }
        // Vp gad12w02
        public string version { get; private set; }
        // 13-01-12
        public string date { get; private set; }
        // C:\apps\Marble\Vp gad12w02\
        public string path { get; private set; }

        /// <summary>
        /// Extracts information from a test package
        /// </summary>
        /// <param name="testPackagePath">File system path of the test package to open</param>
        public TestPackageModel(string testPackagePath)
        {
            this.productFamilyConfig = string.Empty;
            this.productFamilyName = string.Empty;
            this.productConfig = string.Empty;
            this.productName = string.Empty;
            this.productType = string.Empty;
            this.version = string.Empty;
            this.date = string.Empty;
            this.path = string.Empty;

            this.path = testPackagePath;
            this.getProductAndFamilyConfigs();
            this.getVersionInfo();
        }

        /// <summary>
        /// Forms a path to be used to start the Marble framework
        /// </summary>
        /// <returns>File system path from which Marble framework can be started</returns>
        /// <example>C:\apps\Marble\gaia_ds_Vp_gad11w52\isa_test\s40_11_2_cs16_family\gaia_ds_config\gaia_ds.py</example>
        public string getStartupFilePath()
        {
            // extract the product name part of the product config
            string productFile = this.productConfig.Substring(0, this.productConfig.LastIndexOf("_config"));
            return Path.Combine(this.path, "isa_test", this.productFamilyConfig, this.productConfig, productFile + ".py");
        }

        /// <summary>
        /// Reads version string from the test package and stores its information to local attributes
        /// (version, date, productType).
        /// </summary>
        private void getVersionInfo()
        {
            // Form a path to version file
            string ppmPath = Path.Combine(this.path, "ppm", "version.c");

            if (!File.Exists(ppmPath)) return;

            using (StreamReader sr = new StreamReader(ppmPath))
            {
                // go through whole file line by line
                String line;

                while ((line = sr.ReadLine()) != null)
                {
                    // correct line found, example line below:
                    // const char *const dev_sw_version = "Vp gad11w52\n30-12-11\nRM-766\n(c) Nokia        ";
                    if (line.StartsWith("const char *const dev_sw_version ="))
                    {
                        // extract and store version information items
                        line = line.Substring("const char *const dev_sw_version =".Length).TrimStart(new char[] {'"', ' '});
                        string [] items = line.Split(new string[] { @"\n" }, StringSplitOptions.None);
                        this.version = items.ElementAtOrDefault(0);
                        this.date = items.ElementAtOrDefault(1);
                        this.productType = items.ElementAtOrDefault(2);

                        break;
                    }
                }
            }
        }

        /// <summary>
        /// Reads product specific information from the test package and stores it to local attributes
        /// (productFamilyConfig, productFamilyName, productConfig, productName).
        /// </summary>
        private void getProductAndFamilyConfigs()
        {
            string includePath = Path.Combine(path, "include");

            if (!Directory.Exists(includePath)) return;

            string[] fileList = Directory.GetFiles(includePath, "*env.txt");

            if (fileList.Length <= 0) return;

            using (StreamReader sr = new StreamReader(fileList[0]))
            {
                string line;

                while ((line = sr.ReadLine()) != null)
                {
                    if (line.StartsWith("export FAMILY_CONFIGURATION="))
                    {
                        // extract the name of the last directory without quote(s), example line below:
                        // export FAMILY_CONFIGURATION='/nokia/ou_nmp/groups/mcl_rel_wa1/work/timoojal/timoojal2/s40_sw/product_config/s40_11_2_cs16_family'
                        this.productFamilyConfig = line.Split(new[] { '/', '\\' }, StringSplitOptions.RemoveEmptyEntries).Last().Trim(new[] { '\'', '"' });
                        this.productFamilyName = this.productFamilyConfig.Substring(0, this.productFamilyConfig.LastIndexOf("_family"));
                    }
                    else if (line.StartsWith("export PRODUCT_CONFIGURATION="))
                    {
                        // extract the name of the last directory without quote(s), example line below:
                        // export PRODUCT_CONFIGURATION='/nokia/ou_nmp/groups/mcl_rel_wa1/work/timoojal/timoojal2/s40_sw/product_config/s40_11_2_cs16_family/gaia_ds_config'
                        this.productConfig = line.Split(new[] { '/', '\\' }, StringSplitOptions.RemoveEmptyEntries).Last().Trim(new[] { '\'', '"' });                            
                    }

                    // productFamilyConfig and productConfig found get also the name of the product
                    if (!string.IsNullOrEmpty(this.productFamilyConfig) && !string.IsNullOrEmpty(this.productConfig))
                    {
                        this.getProductName();
                        break;
                    }

                }
            }
            // raise error ?
        }

        /// <summary>
        /// Reads product name from the isa_test package and stores it to local attribute (productName).
        /// </summary>
        private void getProductName()
        {
            //D:\apps\Marble\gaia_ds_Vp_gad11w52\isa_test\s40_11_2_cs16_family\gaia_ds_config\d_product\__init__.py
            string initPath = Path.Combine(this.path, "isa_test", this.productFamilyConfig, this.productConfig, "d_product", "__init__.py");

            if (!File.Exists(initPath)) return;

            using (StreamReader sr = new StreamReader(initPath))
            {
                string line;

                while ((line = sr.ReadLine()) != null)
                {
                    // PRODUCT_NAME = 'Gaia DS'
                    if (!line.StartsWith("PRODUCT_NAME")) continue;

                    string[] items = line.Split(new[] { '=' });

                    if (items.Length > 1)
                    {
                        this.productName = items[1].Trim(new[] { ' ', '\'', '"' });
                        break;
                    }
                }
            }
        }
    }

    /// <summary>
    /// Encapsulates test set specific operations.
    /// </summary>
    public class MarbleTestSetModel : MediatorModel, INotifyPropertyChanged
    {
        /// <summary>
        /// Gets or sets the miscellaneous XML attribute list for the test set. 
        /// This list contains XML attributes which aren't used by test set model, but are needed for the XML.
        /// e.g. QC attributes are stored in this list.
        /// </summary>
        public List<XAttribute> MiscXmlAttributeListForTestSet { get; set; }

        private int totalTestCases;

        /// <summary>
        /// Gets or sets number of cases in current testset.
        /// </summary>
        public int TotalTestCases
        {
            get { return this.totalTestCases; }
            set
            {
                this.totalTestCases = value;
                this.OnPropertyChanged("TotalTestCases");
            }
        }

        private int passedTestCases;

        /// <summary>
        /// Gets or sets number of passed tests on current/previous run.
        /// </summary>
        public int PassedTestCases
        {
            get { return this.passedTestCases; }
            set
            {
                this.passedTestCases = value;
                this.OnPropertyChanged("PassedTestCases");
            }
        }

        private int failedTestCases;

        /// <summary>
        /// Gets or sets number of failed tests on current/previous run.
        /// </summary>
        public int FailedTestCases
        {
            get { return this.failedTestCases; }
            set
            {
                this.failedTestCases = value;
                this.OnPropertyChanged("FailedTestCases");
            }
        }

        private int noResultTestCases;

        /// <summary>
        /// Gets or sets number of tests that were not run on current/previous run.
        /// </summary>
        public int NoResultTestCases
        {
            get { return this.noResultTestCases; }
            set
            {
                this.noResultTestCases = value;
                this.OnPropertyChanged("NoResultTestCases");
            }
        }

        public int PassedResultsCount { get { return this.countResultsForTestCases(TestResultEnum.Passed); } }

        public int FailedResultsCount { get { return this.countResultsForTestCases(TestResultEnum.Failed); } }

        public int NoResultResultsCount { get { return this.countResultsForTestCases(TestResultEnum.NoResult); } }

        public void RefreshResultsCounts()
        {
            this.OnPropertyChanged("PassedResultsCount");
            this.OnPropertyChanged("FailedResultsCount");
            this.OnPropertyChanged("NoResultResultsCount");
        }

        private int countResultsForTestCases(TestResultEnum result)
        {
            int resultCount = 0;

            //string resultText = result.ToLower().Replace(" ", string.Empty);

            foreach (TestCase testCase in this.TestCases.Where(testCase => testCase.Level == 1))
            {
                switch (result)
                {
                    case TestResultEnum.NotAvailable:
                        if (testCase.HasChildren) resultCount += testCase.NotAvailableTestCaseCount;
                        else if (string.IsNullOrEmpty(testCase.Result.Result)) resultCount++;
                        break;
                    case TestResultEnum.Passed:
                        if (testCase.HasChildren) resultCount += testCase.PassedTestCaseCount;
                        else if (testCase.Result.Result.ToLower() == "passed") resultCount++;
                        break;
                    case TestResultEnum.Failed:
                        if (testCase.HasChildren) resultCount += testCase.FailedTestCaseCount;
                        else if (testCase.Result.Result.ToLower() == "failed") resultCount++;
                        break;
                    case TestResultEnum.NoResult:
                        if (testCase.HasChildren) resultCount += testCase.NoResultTestCaseCount;
                        else if (testCase.Result.Result.ToLower() == "no result") resultCount++;
                        break;
                    default:
                        throw new ArgumentOutOfRangeException("result");
                }

                //if (testCase.HasChildren)
                //{
                //    ////foreach (TestCase child in testCase.Children)
                //    ////{
                //    ////    if (child.Result == null || string.IsNullOrEmpty(child.Result.Result)) continue;

                //    ////    if (child.Result.Result.ToLower() == resultText) resultCount++;
                //    ////}

                //    resultCount += testCase.Children.Where(child => child.Result != null && !string.IsNullOrEmpty(child.Result.Result)).Count(child => child.Result.Result.ToLower() == resultText);
                //}
                //else
                //{
                //    if (testCase.Result == null || string.IsNullOrEmpty(testCase.Result.Result)) continue;

                //    if (testCase.Result.Result.ToLower() == resultText) resultCount++;
                //}
            }

            return resultCount;
        }

        private int checkedTestCases;

        /// <summary>
        /// Gets or sets number of checked test cases at the beginning of test execution.
        /// Used to calculate the value for progress bar.
        /// </summary>
        public int CheckedTestCases
        {
            get { return this.checkedTestCases; }
            set
            {
                this.checkedTestCases = value;
                this.OnPropertyChanged("CheckedTestCases");
            }
        }

        private double testRunProgressValue;

        /// <summary>
        /// Gets or sets current test case run total progress.
        /// </summary>
        public double TestRunProgressValue
        {
            get { return this.testRunProgressValue; }
            set
            {
                this.testRunProgressValue = value;
                this.OnPropertyChanged("TestRunProgressValue");
            }
        }

        private bool isChanged;

        /// <summary>
        /// Gets or sets a value indicating whether the test set state has changed.
        /// </summary>
        public bool IsChanged
        {
            get { return this.isChanged; }
            set
            {
                if (this.isChanged == value) return;

                this.isChanged = value;
                this.OnPropertyChanged("IsChanged");

                // Inform MarbleMainViewModel to update the application title.
                this.Mediator.NotifyColleagues<bool>("UpdateApplicationTitle", this.isChanged);

                // Update our property that indicates whether this is a test set containing CTT tests
                UpdateCoreTestToolProperties();
            }
        }

        private bool isSorted;

        /// <summary>
        /// Gets or sets a value indicating whether the test set is sorted.
        /// </summary>
        public bool IsSorted
        {
            get { return this.isSorted; }
            set
            {
                this.isSorted = value;
                this.OnPropertyChanged("IsSorted");
            }
        }

        private bool isCoreTestToolOnlyTestSet;

        /// <summary>
        /// Read-only property that indicates whether this test set contains only Core Test Tool (CTT) tests.
        /// </summary>
        public bool IsCoreTestToolOnlyTestSet
        {
            get { return this.isCoreTestToolOnlyTestSet; }
            private set
            {
                if (this.isCoreTestToolOnlyTestSet != value)
                {
                    this.isCoreTestToolOnlyTestSet = value;
                    this.OnPropertyChanged("IsCoreTestToolOnlyTestSet");
                }
            }
        }

        private bool hasCoreTestToolTest;

        /// <summary>
        /// Read-only property that indicates whether this test set contains at least one Core Test Tool (CTT) test.
        /// </summary>
        public bool HasCoreTestToolTest
        {
            get { return this.hasCoreTestToolTest; }
            private set
            {
                if (this.hasCoreTestToolTest != value)
                {
                    this.hasCoreTestToolTest = value;
                    this.OnPropertyChanged("HasCoreTestToolTest");
                }
            }
        }

        private TestCase currentTestCase;

        /// <summary>
        /// Gets or sets the last returned test with GetNextCheckedTestCase().
        /// </summary>
        public TestCase CurrentTestCase
        {
            get { return this.currentTestCase; }
            set
            {
                this.currentTestCase = value;
                this.OnPropertyChanged("CurrentTestCase");
            }
        }

        private string documentPath;

        /// <summary>
        /// Gets or sets file system path of the test set file.
        /// If value is null or empty TempDocumentPath is returned in getter.
        /// </summary>
        public string DocumentPath
        {
            get
            {
                // Return temp path for new test sets
                return string.IsNullOrEmpty(this.documentPath) ? this.TempDocumentPath : this.documentPath;
            }
            set
            {
                this.documentPath = value;

                // Clear the temporary path
                this.TempDocumentPath = string.Empty;
                this.OnPropertyChanged("DocumentPath");

                // Inform MarbleMainViewmodel to update the application title.
                this.Mediator.NotifyColleagues<bool>("UpdateApplicationTitle", false);
            }
        }

        private int headerRunCount;

        /// <summary>
        /// Gets or sets the header count of the test set.
        /// This property is done as temporary fix for NumericTextBox bug.
        /// NumericTextBox Text property must be bound to something, otherwise it raises an error.
        /// </summary>
        public int HeaderRunCount
        {
            get { return this.headerRunCount; }
            set
            {
                if (this.headerRunCount == value) return;

                this.headerRunCount = value;
                this.OnPropertyChanged("HeaderRunCount");

                if (this.HeaderRunCount <= 0 &&
                    !this.TestCases.Any(tc => tc.IsRoot && tc.TotalRunCount != this.HeaderRunCount)) return;

                // Go through all the root TestCases and change their TotalRunCount to the same as HeaderRunCount
                var results = this.TestCases.Where(tCase => tCase.IsRoot && tCase.TotalRunCount != this.HeaderRunCount);

                foreach (TestCase testCase in results)
                    testCase.TotalRunCount = this.HeaderRunCount;

                this.IsChanged = true;
            }
        }

        private int testSetTimesToRepeat;

        /// <summary>
        /// Gets or sets TestSetTimesToRepeat.
        /// </summary>
        public int TestSetTimesToRepeat
        {
            get { return this.testSetTimesToRepeat; }
            set
            {
                this.testSetTimesToRepeat = value;
                this.OnPropertyChanged("TestSetTimesToRepeat");
            }
        }

        private int testSetCurrentRepeatCycle;

        /// <summary>
        /// Gets or sets TestSetCurrentRepeatCycle.
        /// </summary>
        public int TestSetCurrentRepeatCycle
        {
            get { return this.testSetCurrentRepeatCycle; }
            set
            {
                this.testSetCurrentRepeatCycle = value;
                this.OnPropertyChanged("TestSetCurrentRepeatCycle");
            }
        }

        /// <summary>
        /// Indicates whether test set repeat times was greater than zero when execution started.
        /// </summary>
        public bool RepeatRunStarted { get; set; }

        private TestRuntimeUnit currentTestRuntimeUnit = TestRuntimeUnit.Hours;

        public TestRuntimeUnit CurrentTestRuntimeUnit
        {
            get
            {
                return this.currentTestRuntimeUnit;
            }
            set
            {
                this.currentTestRuntimeUnit = value;
                this.OnPropertyChanged("CurrentTestRuntimeUnit");
                this.OnPropertyChanged("TestSetRepeatTime");
            }
        }

        private TimeSpan testSetRepeatTime = new TimeSpan();

        /// <summary>
        /// Test set repeat time as a time span object (not settable).
        /// </summary>
        public TimeSpan TestSetRepeatTimeSpan { get { return this.testSetRepeatTime; } }

        /// <summary>
        /// Test set repeat time as an integer.
        /// </summary>
        public int TestSetRepeatTime
        {
            get
            {
                switch (this.CurrentTestRuntimeUnit)
                {
                    case TestRuntimeUnit.Hours:
                        return Convert.ToInt32(this.testSetRepeatTime.TotalHours);
                    case TestRuntimeUnit.Days:
                        return Convert.ToInt32(this.testSetRepeatTime.TotalDays);
                    default:
                        return Convert.ToInt32(this.testSetRepeatTime.TotalMinutes);
                }
            }
            set
            {
                switch (this.CurrentTestRuntimeUnit)
                {
                    case TestRuntimeUnit.Minutes:
                        this.testSetRepeatTime = new TimeSpan(0, 0, value, 0);
                        break;
                    case TestRuntimeUnit.Hours:
                        this.testSetRepeatTime = new TimeSpan(0, value, 0, 0);
                        break;
                    case TestRuntimeUnit.Days:
                        this.testSetRepeatTime = new TimeSpan(value, 0, 0, 0);
                        break;
                    default:
                        this.testSetRepeatTime = new TimeSpan(0, 0, value, 0);
                        break;
                }

                this.OnPropertyChanged("TestSetRepeatTime");
            }
        }

        /// <summary>
        /// Indicates whether repeat by time is enabled.
        /// </summary>
        public bool TimedRunEnabled { get; set; }

        private bool shuffleMode;

        /// <summary>
        /// Indicates whether to use shuffling when choosing next test case to run.
        /// Next test case is chosen randomly among the total iterations left for this round.
        /// </summary>
        public bool ShuffleMode
        {
            get
            {
                return this.shuffleMode;
            }
            set
            {
				if (this.shuffleMode == value) return;
							
                this.shuffleMode = value;
				this.IsChanged = true;
                this.OnPropertyChanged("ShuffleMode");
            }
        }

        private DateTime testSetRunStart;

        /// <summary>
        /// Start time of the current test execution.
        /// </summary>
        public DateTime TestSetRunStart
        {
            get { return this.testSetRunStart; }
            set
            {
                this.testSetRunStart = value;
                this.OnPropertyChanged("TestSetRunStart");
            }
        }

        private DateTime testSetRunEnd;

        /// <summary>
        /// End time of the current test execution.
        /// </summary>
        public DateTime TestSetRunEnd
        {
            get
            {
                return this.testSetRunEnd;
            }
            set
            {
                this.testSetRunEnd = value;
                this.OnPropertyChanged("TestSetRunEnd");
            }
        }

        /// <summary>
        /// Gets or sets temporary testset document path created when New testset is created.
        /// </summary>
        public string TempDocumentPath { get; set; }

        /// <summary>
        /// Gets or sets zero-based index of the current test case.
        /// Indicates how many test cases have been executed (for the progress bar).
        /// </summary>
        public int CurrentIndex { get; set; }

        /// <summary>
        /// Collection that contains all visible test cases.
        /// Contains at least all root test cases.
        /// Also contains children of the root test cases if they are expanded.
        /// </summary>
        public ObservableCollectionAdv<TestCase> TestCases { get; private set; }

        private readonly Random randomizer = new Random();

        private string nextTestSetPath;

        /// <summary>
        /// Path of the test set that is opened and executed after this test set.
        /// </summary>
        public string NextTestSetPath
        {
            get
            {
                return this.nextTestSetPath;
            }
            set
            {
                if (this.nextTestSetPath == value) return;

                this.nextTestSetPath = value;
                this.IsChanged = true;
                this.OnPropertyChanged("NextTestSetPath");
            }
        }

        private bool scriptPathsRelativeToTestSet;

        public bool ScriptPathsRelativeToTestSet
        {
            get { return this.scriptPathsRelativeToTestSet; }

            set
            {                
                if (this.scriptPathsRelativeToTestSet == value) return;

                this.scriptPathsRelativeToTestSet = value;
                this.isChanged = true;
                this.OnPropertyChanged("ScriptPathsRelativeToTestSet");
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="MarbleTestSetModel"/> class. 
        /// Loads an existing test set file
        /// </summary>
        /// <param name="path">File system path of the existing test set file to load.</param>
        public MarbleTestSetModel(string path)
        {
            this.MiscXmlAttributeListForTestSet = new List<XAttribute>();
            this.TestCases = new ObservableCollectionAdv<TestCase>();

            this.DocumentPath = path;
            this.LoadFromXml(path);

            this.TestSetRunEnd = new DateTime(0);
        }

        /// <summary>
        /// Reads the contents of the gui xml file to ObservableCollectionAdv.
        /// </summary>
        /// <param name="testSetPath">testset file path</param>
        public void LoadFromXml(string testSetPath)
        {
            if (!File.Exists(testSetPath)) return;

            // Load the test cases from the file
            TestCase[] testCases = TestsetXmlParser.ParseTestsetFile(testSetPath);

            // Read all attributes from the test set file
            var attributes = TestsetXmlParser.ReadTestSetAttributes(testSetPath);

            // Load known attributes
            var tempAttribute = attributes.FirstOrDefault(attrib => attrib.Name == "timedrunenabled");
            bool enableTimedRun = false;
            if (tempAttribute != null && bool.TryParse(tempAttribute.Value, out enableTimedRun))
                attributes.Remove(tempAttribute);
            this.TimedRunEnabled = enableTimedRun;

            tempAttribute = attributes.FirstOrDefault(attrib => attrib.Name == "shuffle");
            bool enableShuffling = false;
            if (tempAttribute != null && bool.TryParse(tempAttribute.Value, out enableShuffling))
                attributes.Remove(tempAttribute);
            this.ShuffleMode = enableShuffling;

            tempAttribute = attributes.FirstOrDefault(attrib => attrib.Name == "nexttestsetpath");
            if (tempAttribute != null)
            {
                this.NextTestSetPath = tempAttribute.Value;
                attributes.Remove(tempAttribute);
            }
            else
            {
                this.nextTestSetPath = string.Empty;
            }

            tempAttribute = attributes.FirstOrDefault(attrib => attrib.Name == "repeattime");
            TimeSpan repeatTime;
            if (tempAttribute != null && TimeSpan.TryParse(tempAttribute.Value, out repeatTime))
            {
                if (repeatTime.Minutes > 0)
                {
                    this.CurrentTestRuntimeUnit = TestRuntimeUnit.Minutes;
                    this.TestSetRepeatTime = (int)repeatTime.TotalMinutes;
                }
                else if (repeatTime.Hours > 0)
                {
                    this.CurrentTestRuntimeUnit = TestRuntimeUnit.Hours;
                    this.TestSetRepeatTime = (int)repeatTime.TotalHours;
                }
                else if (repeatTime.Days > 0)
                {
                    this.CurrentTestRuntimeUnit = TestRuntimeUnit.Days;
                    this.TestSetRepeatTime = (int)repeatTime.TotalDays;
                }
                else
                {
                    this.CurrentTestRuntimeUnit = TestRuntimeUnit.Hours;
                    this.TestSetRepeatTime = 0;
                }

                attributes.Remove(tempAttribute);
            }
            else
            {
                this.CurrentTestRuntimeUnit = TestRuntimeUnit.Minutes;
                this.TestSetRepeatTime = 0;
            }

            tempAttribute = attributes.FirstOrDefault(attrib => attrib.Name == "scriptsrelativetotestset");
            bool relativeScripts = false;
            if (tempAttribute != null && bool.TryParse(tempAttribute.Value, out relativeScripts))
                attributes.Remove(tempAttribute);
            this.ScriptPathsRelativeToTestSet = relativeScripts;

            this.MiscXmlAttributeListForTestSet = attributes;

            // Clear TestCases collection and then insert the test cases.
            // This is done so TestCases (ObservableCollection) would notify changes and UI would update.
            this.TestCases.Clear();
            this.TestCases.InsertRange(0, testCases);

            this.DocumentPath = testSetPath;

            // Update our property that indicates whether this is a test set containing CTT tests
            this.UpdateCoreTestToolProperties();
            this.IsChanged = false;
        }

        /// <summary>
        /// Saves the current test set document to a file
        /// </summary>
        /// <param name="path">File system path to the resulting test set file. If empty same path used as on load.</param>
        public void Save(string path = "")
        {
            // Path not given
            if (string.IsNullOrEmpty(path))
            {
                // Both paths (DocumentPath and TempDocumentPath) are empty
                if (string.IsNullOrEmpty(this.DocumentPath))
                    this.TempDocumentPath = @"..\test_sets\new_testset.testset";

                // Use DocumentPath (or TempDocumentPath if DocumentPath is empty)
                path = this.DocumentPath;
            }

            if (this.ScriptPathsRelativeToTestSet)
                this.MakeScriptPathsRelativeToTestset();
            else
                this.MakeScriptPathsRelativeToMarble();

            XElement testSetElement = new XElement("testset");

            testSetElement.SetAttributeValue("timedrunenabled", this.TimedRunEnabled.ToString());
            testSetElement.SetAttributeValue("repeattime", this.TestSetRepeatTimeSpan.ToString());
            testSetElement.SetAttributeValue("shuffle", this.shuffleMode.ToString());
            testSetElement.SetAttributeValue("nexttestsetpath", this.NextTestSetPath);
            testSetElement.SetAttributeValue("scriptsrelativetotestset", this.ScriptPathsRelativeToTestSet.ToString());

            // Possible miscellaneous attributes are added to test set element.
            foreach (XAttribute miscAttribute in this.MiscXmlAttributeListForTestSet)
            {
                XAttribute existingAttribute = testSetElement.Attribute(miscAttribute.Name.ToString());

                // If attribute is already found from test set element but has no value, miscellaneous attribute value is used instead.
                // Otherwise miscellaneous attribute is added to test set element.
                if (existingAttribute != null && string.IsNullOrEmpty(existingAttribute.Value) && !string.IsNullOrEmpty(miscAttribute.Value))
                    existingAttribute.Value = miscAttribute.Value;
                else
                    testSetElement.SetAttributeValue(miscAttribute.Name.ToString(), miscAttribute.Value);
            }

            XDocument newTestset = new XDocument(testSetElement);
            
            foreach (TestCase testCase in this.TestCases.Where(tc => tc.Level == 1))
            {
                XElement rootTestCaseElement = testCase.toXML();

                if (testCase.HasChildren)
                {
                    // Remove the result element of this root test case of multirun test case.
                    rootTestCaseElement.Elements().First(item => item.Name.ToString() == "testresult").Remove();

                    // Add consecutive run results under the same testcase element.
                    foreach (TestCase childTestCase in testCase.Children)
                    {
                        XElement testCaseElement = childTestCase.toXML();
                        foreach (XElement element in testCaseElement.Elements())
                        {
                            if (element.Name.ToString() == "testresult")
                                rootTestCaseElement.Add(element);
                        }
                    }
                }
                
                newTestset.Root.Add(rootTestCaseElement);
            }

            if (this.EnsureSave(newTestset, path))
            {
                this.IsChanged = false;
                this.IsSorted = false;
            }
        }

        /// <summary>
        /// Tries to save given XDocument to the given path.
        /// Saves with a _backup extension if the save fails for 10 times.
        /// </summary>
        /// <param name="doc">Document to save</param>
        /// <param name="path">File system path where the document is saved</param>
        /// <returns>True if the original file can be saved otherwise false</returns>
        private bool EnsureSave(XDocument doc, string path)
        {
            if (doc == null || string.IsNullOrEmpty(path))
                return false;

            const string backupExtension = "_backup";
            string backupPath = path + backupExtension;
            bool success = false;

            // Try to save the original file
            for (int tryCount = 0; tryCount < 10; tryCount++ )
            {
                try
                {
                    doc.Save(path);
                    success = true;
                    if (File.Exists(backupPath))
                        File.Delete(backupPath);
                    return true;
                }
                catch (IOException)
                {
                    if (success) return true;
                    Thread.Sleep(200);
                }
            }

            // Failed to save the original file, try to save with a backup filename
            for (int tryCount = 0; tryCount < 10; tryCount++)
            {
                try
                {
                    doc.Save(backupPath);
                    return false;
                }
                catch (IOException)
                {
                    Thread.Sleep(200);
                }
            }

            return false;
        }

        /// <summary>
        /// Saves the created new test set to a file.
        /// </summary>
        /// <param name="newFileName">The new File Name.</param>
        public void SaveAs(string newFileName)
        {
            // If new test set created, rename the temporary .testset file.
            if (File.Exists(this.TempDocumentPath))
                FileUtilities.RenameFile(this.TempDocumentPath, newFileName);

            // TempDocumentPath is set on new test set creation.
            if (!string.IsNullOrEmpty(this.TempDocumentPath))
                // Rename the temporary results directory.
                this.RenameResultDirectory(newFileName);
            else
                // Copy the previously opened test sets results directory.
                this.CopyResultDirectory(newFileName);

            // Make path to relative
            string relativeTestSetName = FileUtilities.GetRelativePath(Directory.GetCurrentDirectory(), newFileName);

            // Set the testset documentpath to one user set in File Dialog.
            // This also clears the TempDocumentPath
            this.DocumentPath = newFileName;

            //string strt = reportPath;
            this.Save(relativeTestSetName);
        }

        /// <summary>
        /// Copies the previously opened test set results directory to new path.
        /// Also changes the reportpath to point to the new path.
        /// </summary>
        /// <param name="newFileName">The new File Name.</param>
        private void CopyResultDirectory(string newFileName)
        {
            string previousTestsetName = Path.GetFileNameWithoutExtension(this.DocumentPath);
            string testsetName = Path.GetFileNameWithoutExtension(newFileName);
            string testsetDir = Path.GetDirectoryName(newFileName);
            string testsetPreviousResultDir = Path.Combine(testsetDir, previousTestsetName + "_results");
            string testsetResultDir = Path.Combine(testsetDir, testsetName + "_results");

            FileUtilities.CopyDirectory(testsetPreviousResultDir, testsetResultDir);
        }

        /// <summary>
        /// Renames the created new_testset_results folder with the new test set name.
        /// Also changes the reportpath to point to the new path.
        /// </summary>
        /// <param name="newFileName">new test set file name</param>
        private void RenameResultDirectory(string newFileName)
        {
            string tempTestsetName = Path.GetFileNameWithoutExtension(this.TempDocumentPath);
            string testsetName = Path.GetFileNameWithoutExtension(newFileName);
            string testsetDir = Path.GetDirectoryName(newFileName);
            
            if (testsetDir == null) return; 

            string testsetTempResultDir = Path.Combine(testsetDir, tempTestsetName + "_results");
            string testsetResultDir = Path.Combine(testsetDir, testsetName + "_results");

            // If temporary test set result directory exists.
            if (Directory.Exists(testsetTempResultDir))
            {
                if (!FileUtilities.RenameDirectory(testsetTempResultDir, testsetResultDir))
                    return; // If result directory rename fails, no use to change the reportpath in .testset file either, so just return.

                XDocument newTestset = new XDocument(new XElement("testset"));
                
                foreach (TestCase tc in this.TestCases)
                {
                    if (!string.IsNullOrEmpty(tc.Result.ResultPath))
                    {
                        // Rename the reportpath with the new name.
                        int index = tc.Result.ResultPath.IndexOf(@"_results\", System.StringComparison.Ordinal);
                        tc.Result.ResultPath = testsetName + tc.Result.ResultPath.Substring(index);
                    }

                    if (newTestset.Root != null)
                        newTestset.Root.Add(tc.toXML());
                }

                newTestset.Save(newFileName);
            }
            else
            {
                XDocument newTestset = new XDocument(new XElement("testset"));

                foreach (TestCase tc in this.TestCases)
                {
                    if (newTestset.Root == null) continue; 

                    newTestset.Root.Add(tc.toXML());
                }

                newTestset.Save(newFileName);
            }
        }

        /// <summary>
        /// Gets next test case to run depending of the run mode.
        /// a) Another instance of the same test case if repeat test case defined.
        /// b) Next checked test case in the test set.
        /// c) Random checked test case in the test set.
        /// </summary>
        /// <returns>Next checked test case or null.</returns>
        public TestCase GetNextTestCaseToRun(bool selectNextTestCaseForRun = true)
        {
            // New execution sequence started
            if (this.currentTestCase == null)
            {
                this.TestSetRunStart = DateTime.Now;
                this.TestSetRunEnd = new DateTime(0);
            }

            // Checked whether to continue execution
            if (!this.ShouldRunContinue())
                return null;

            // Increase the executed test cases count for the progress bar
            this.CurrentIndex = this.CurrentIndex < 0 ? 0 : this.CurrentIndex + 1;

            // Get next test case for timed repeat run
            if (this.TimedRunEnabled)
                return this.GetNextTestCaseForTimedRepeat(selectNextTestCaseForRun);

            // Get next test case for shuffled normal run
            if (!this.TimedRunEnabled && this.shuffleMode)
                return this.GetNextTestCaseShuffled(selectNextTestCaseForRun);

            // First test case of the new execution sequence
            if (this.currentTestCase == null)
                this.currentTestCase =
                    this.TestCases.FirstOrDefault(
                        tc =>
                        tc.IsRoot && (tc.IsWhiteboxChecked || tc.IsBlackboxChecked));

            if (this.currentTestCase == null)
                return null;

            // Check if current test case has already been run specified amount of times.
            // If not, create a new TestCase based on CurrentTestCase.
            // New test case is not created when selectNextTestCaseForRun is false.
            if (this.CurrentTestCase.GetRunCountFromTime(this.TestSetRunStart) < this.CurrentTestCase.TotalRunCount)
            {
                TestCase rootCase = this.CurrentTestCase.GetRootCase();

                if (!selectNextTestCaseForRun) return rootCase;

                // On first run return self
                if (rootCase.RunCount == 0)
                    return rootCase;
                // On subsequent runs return new child
                TestCase newCase = rootCase.CreateNewChildTestCase();
                if (rootCase.IsExpanded)
                    this.MakeChildVisible(newCase);
                return newCase;
            }

            // After previous TestCase and it's consecutive runs have been completed, fetch next checked TestCase.
            TestCase nextCase = null;
            List<TestCase> checkedCases = this.TestCases.Where(tc => tc.IsRoot && (tc.IsWhiteboxChecked || tc.IsBlackboxChecked)).ToList();
            int currentIndex = checkedCases.IndexOf(this.CurrentTestCase.GetRootCase());

            // Search for next case to run (loop all checked test cases once from the current index)
            for (int ii = currentIndex + 1; ii < currentIndex + checkedCases.Count; ii++)
            {
                TestCase testCase = checkedCases[ii % checkedCases.Count];
                // Check if this case has already been run enough times
                if (testCase.GetRunCountFromTime(this.TestSetRunStart) >= testCase.TotalRunCount)
                    continue;

                // Test Case is only returned to check whether there are test cases still to continue test run.
                if (!selectNextTestCaseForRun) return testCase;

                testCase.IsRunning = true;
                // On first run use root case
                if (testCase.RunCount == 0)
                {
                    nextCase = testCase;
                }
                // On subsequent runs use new child
                else
                {
                    TestCase newCase = testCase.CreateNewChildTestCase();
                    if (testCase.IsExpanded)
                        this.MakeChildVisible(newCase);
                    nextCase = newCase;
                }
                break;
            }

            this.currentTestCase.GetRootCase().IsWhiteboxChecked = false;
            this.currentTestCase.GetRootCase().IsBlackboxChecked = false;
            return nextCase;
        }

        /// <summary>
        /// Determinates whether to continue execution to next case.
        /// Checks that run time is not exceeded.
        /// </summary>
        /// <returns>true if execution is to be continued otherwise false</returns>
        private bool ShouldRunContinue()
        {
            return !this.TimedRunEnabled || this.TestSetRepeatTimeSpan.Ticks >= App.ViewModel.TestExecutionTimeSpan.Ticks;
        }

        /// <summary>
        /// Returns next test case for normal shuffled run.
        /// </summary>
        /// <returns>Next test case to run or null.</returns>
        private TestCase GetNextTestCaseShuffled(bool selectNextTestCaseForRun = true)
        {
            var testCasesStillToBeExecuted = new List<TestCase>();
            int totalIterationCount = 0;

            // Count the remaining total iterations from all test cases
            foreach (var testCase in this.TestCases.Where(tc => tc.IsRoot && (tc.IsWhiteboxChecked || tc.IsBlackboxChecked) && tc.TotalRunCount > tc.GetRunCountFromTime(this.TestSetRunStart)))
            {
                totalIterationCount += testCase.TotalRunCount - testCase.GetRunCountFromTime(this.TestSetRunStart);
                testCasesStillToBeExecuted.Add(testCase);
            }

            // Randomly select the next iteration
            int indexOfNextTestIteration = this.randomizer.Next(totalIterationCount) + 1;


            TestCase selectedTestCase = null;

            // Determine the test case this iteration belongs to
            foreach (TestCase tc in testCasesStillToBeExecuted)
            {
                indexOfNextTestIteration -= tc.TotalRunCount - tc.GetRunCountFromTime(this.TestSetRunStart);
                if (indexOfNextTestIteration > 0) continue;

                selectedTestCase = tc;
                break;
            }

            if (selectedTestCase == null)
                return null;

            if (!selectNextTestCaseForRun) return selectedTestCase;

            selectedTestCase.IsRunning = true;

            // On first run use root case
            if (selectedTestCase.RunCount == 0)
                return selectedTestCase;

            // On subsequent runs use new child
            TestCase newCase = selectedTestCase.CreateNewChildTestCase();
            if (selectedTestCase.IsExpanded)
                this.MakeChildVisible(newCase);
            return newCase;
        }

        /// <summary>
        /// Returns next checked test case to run (in timed repeat runs).
        /// Test case is selected from the ones with the same smallest run count.
        /// Selection is random if shuffling is enabled.
        /// </summary>
        /// <returns>Next test case to run or null.</returns>
        private TestCase GetNextTestCaseForTimedRepeat(bool selectNextTestCaseForRun = true)
        {
            IList<TestCase> checkedCases =
                this.TestCases.Where(
                    tc => tc.IsRoot && (tc.IsWhiteboxChecked || tc.IsBlackboxChecked) && tc.TotalRunCount > 0).ToList();

            // No checked cases
            if (checkedCases.Count == 0)
                return null;

            // Get smallest run round of all checked test cases
            // New round begins when all test cases have been run the given amount (TotalRunCount)
            int smallestRound = int.MaxValue;
            foreach (TestCase checkedCase in checkedCases)
            {
                if (smallestRound > (int)(checkedCase.RunCount / (double) checkedCase.TotalRunCount))
                    smallestRound = (int)(checkedCase.RunCount / (double) checkedCase.TotalRunCount);

                // Can't get smaller than zero so break
                if (smallestRound == 0) break;
            }

            // Get test cases that are in the smallest run round (still to be executed before starting the next complete round)
            IList<TestCase> casesInSmallestRound =
                checkedCases.Where(tc => (int)(tc.RunCount/(double) tc.TotalRunCount) == smallestRound).ToList();

            TestCase nextCase = null;

            // Select next case randomly from the cases in the smallest run round
            if (this.ShuffleMode)
            {
                int totalIterationCount = 0;

                // Count the total iterations from all test cases left for this round
                foreach (TestCase tc in casesInSmallestRound)
                    totalIterationCount += tc.TotalRunCount * (smallestRound + 1) - tc.RunCount;

                // Randomly select the next iteration
                int indexOfNextTestIteration = this.randomizer.Next(totalIterationCount) + 1;

                // Determine the test case this iteration belongs to
                foreach (TestCase tc in casesInSmallestRound)
                {
                    indexOfNextTestIteration -= tc.TotalRunCount * (smallestRound + 1) - tc.RunCount;
                    if (indexOfNextTestIteration <= 0)
                    {
                        nextCase = tc;
                        break;
                    }
                }
            }

            // Select the next test case in order
            else
            {
                // Get smallest run count from the cases in the smallest run round
                int smallestCount = int.MaxValue;
                foreach (TestCase testCase in casesInSmallestRound)
                {
                    if (smallestCount > testCase.RunCount % testCase.TotalRunCount)
                        smallestCount = testCase.RunCount % testCase.TotalRunCount;

                    if (smallestCount == 0) break;
                }

                // Get the first test case that have the smallest run count (int the smallest run round)
                nextCase = casesInSmallestRound.FirstOrDefault(tc => tc.RunCount == smallestCount + smallestRound * tc.TotalRunCount);
            }

            // Highly unlikely scenario - all checked test cases have been run int.MaxValue times
            if (nextCase == null)
                return null;

            if (!selectNextTestCaseForRun) return nextCase;

            // First run of the selected case
            if (nextCase.RunCount == 0)
                return nextCase;

            // Subsequent run of the selected case
            TestCase childCase = nextCase.CreateNewChildTestCase();
            if (nextCase.IsExpanded)
                this.MakeChildVisible(childCase);
            return childCase;
        }

        /// <summary>
        /// Clears old results (created by previous execution sequence) from checked tests.
        /// </summary>
        private void ClearOldResults()
        {
            // ToList() used because we edit the iterated collection
            foreach (TestCase testCase in this.TestCases.Where(tc => tc.IsRoot && (tc.IsWhiteboxChecked || tc.IsBlackboxChecked)).ToList())
                if (testCase.Result.RunTime != DateTime.MinValue && testCase.Result.RunTime < this.TestSetRunStart ||
                    testCase.HasChildren && testCase.Children[0].Result.RunTime != DateTime.MinValue && testCase.Children[0].Result.RunTime < this.TestSetRunStart)
                    this.ClearTestCase(testCase);
        }

        /// <summary>
        /// Inserts a child test case to visible test cases collection.
        /// </summary>
        /// <param name="childCase">Test case to be added to collection.</param>
        private void MakeChildVisible(TestCase childCase)
        {
            TestCase lastVisibleChild = this.TestCases.LastOrDefault(tc => tc.Parent == childCase.Parent);
            if (lastVisibleChild == null)
                return;

            this.TestCases.Insert(this.TestCases.IndexOf(lastVisibleChild) + 1, childCase);
        }

        /// <summary>
        /// Removes all results from a test case.
        /// </summary>
        /// <param name="rootCase">Test case to clear</param>
        /// <param name="deleteResultFiles">Whether to also delete the result xml files from the hard drive.</param>
        public void ClearTestCase(TestCase rootCase, bool deleteResultFiles = false)
        {
            //NOTE: OPTIMIZE THIS METHOD.

            // Remove child results from visible test cases collection
            foreach (var testCase in this.TestCases.Where(tc => tc.Parent == rootCase).ToList())
                this.TestCases.Remove(testCase);

            rootCase.ClearResults(deleteResultFiles);

            GC.Collect();
        }

        /// <summary>
        /// Returns test case with the given name.
        /// </summary>
        /// <param name="testCaseName">Name of the wanted test case.</param>
        /// <returns>Wanted TestCase object or null object.</returns>
        public TestCase GetTestCase(string testCaseName)
        {
            TestCase testCase = null;
            
            // Fetch the testcase from the collection.
            var result = this.TestCases.Where(item => item.Name == testCaseName);

            foreach (TestCase item in result)
                testCase = item;

            return testCase;
        }

        /// <summary>
        /// Stores the given result to test case item.
        /// </summary>
        /// <param name="testCase">TestCase object.</param>
        /// <param name="testResult">Test case run result.</param>
        public void SetResult(TestCase testCase, TestResult testResult)
        {
            if (testCase == null || testResult == null)
            {
                Console.Write("MarbleTestSetModel.SetResult failed! Argument(s) cannot be null!");
                return;
            }
            testCase.Result = testResult;
            testCase.IsRunning = false;
            if (testCase.Parent != null)
            {
                testCase.Parent.IsRunning = false;
                testCase.Result.Index = testCase.Parent.RunCount;
            }
        }

        /// <summary>
        /// Writes the results of the test case run to .testset file.
        /// </summary>
        /// <param name="testCase">TestCase object.</param>
        public void WriteTestResultToXml(TestCase testCase)
        {
            if (testCase == null)
            {
                Console.Write("MarbleTestSetModel.WriteTestResultToXml failed! Argument 'testCase' cannot be null!");
                return;
            }

            TestResult results = testCase.Result;

            XDocument xmlDocument;

            // Load the test set xml document
            xmlDocument = XDocument.Load(this.DocumentPath);

            // Fetch the wanted testcase element from specified testset file.
            var result = from test in xmlDocument.Elements("testset").Elements("testcase")
                         let attribute = test.Attribute("name")
                         where attribute != null && attribute.Value == testCase.Name
                         select test;

            // Write the results to the fetched testcase element.
            foreach (XElement testCaseElement in result)
            {
                // Remove possible previous testresult elements from the result xml file, if it's the first time case is run.
                if (testCase.RunCount == 1)
                {
                    if (testCaseElement.Elements().Any(item => item.Name == "testresult"))
                        testCaseElement.Elements().Where(element => element.Name == "testresult").Remove();
                }

                testCaseElement.Add(results.ToXml());
            }

            try
            {
                // Save the document to file system
                xmlDocument.Save(this.DocumentPath);
            }
            catch (IOException ioe)
            {
                for (int saveAttempt = 0; saveAttempt <= 10; saveAttempt++)
                {
                    Thread.Sleep(250);

                    try
                    {
                        // Save the document to file system
                        xmlDocument.Save(this.DocumentPath);
                    }
                    catch (IOException)
                    {
                        if (saveAttempt >= 10)
                            MessageBox.Show("MarbleTestSetModel.WriteTestResultToXml failed! Test set file may be used by another process.");
                    }
                }
            }
        }

        /// <summary>
        /// Converts all script paths in this testset to be relative to the path of this testset.
        /// </summary>
        /// <returns></returns>
        public bool MakeScriptPathsRelativeToTestset()
        {
            string testsetPath = Path.GetFullPath(this.DocumentPath);
            bool success = true;

            foreach (var tc in this.TestCases.Where(tc => tc.IsRoot))
            {
                if (!tc.Script.IsRelativeToTestset)
                {
                    tc.Script.IsRelativeToTestset = true;
                    tc.Script.AbsolutePath = Path.GetFullPath(tc.Script.Directory);
                }

                tc.Script.Directory = FileUtilities.GetRelativePath(testsetPath, tc.Script.AbsolutePath);

                if (Path.IsPathRooted(tc.Script.Directory))
                    success = false;
            }
            return success;
        }

        /// <summary>
        /// Converts all script paths in this testset to be relative to the path of Marble (current working dir).
        /// </summary>
        /// <returns></returns>
        public bool MakeScriptPathsRelativeToMarble()
        {
            bool success = true;

            foreach (var tc in this.TestCases.Where(tc => tc.IsRoot))
            {
                if (tc.Script.IsRelativeToTestset)
                {
                    tc.Script.IsRelativeToTestset = false;
                    tc.Script.Directory = tc.Script.AbsolutePath;
                }

                if (Path.IsPathRooted(tc.Script.Directory))
                    success = false;
            }
            return success;            
        }

        /// <summary>
        /// Removes test case and possible children from the test set.
        /// </summary>
        /// <param name="testCase">Test case to remove.</param>
        public void RemoveTestCaseAndChildren(TestCase testCase)
        {
            if (testCase == null) return;
            if (!this.TestCases.Contains(testCase)) return;

            if (testCase.Children != null)
            {
                foreach (TestCase childTestCase in testCase.Children.Where(childTestCase => this.TestCases.Contains(childTestCase)))
                {
                    this.TestCases.Remove(childTestCase);
                }

                testCase.Children.Clear();
            }
            
            this.TestCases.Remove(testCase);
            this.IsChanged = true;
        }

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion

        /// <summary>
        /// Evaluates whether the test set contains Core Test Tool (CTT) tests and
        /// updates the <see cref="IsCoreTestToolOnlyTestSet"/> property and
        /// <see cref="HasCoreTestToolTest"/> property accordingly.
        /// </summary>
        private void UpdateCoreTestToolProperties()
        {
            bool coreTestToolOnlyTestSet = false;
            bool hasCoreTestToolTest = false;

            // If there are test cases
            if (this.TestCases != null && this.TestCases.Count > 0)
            {
                // If all test cases are CTT test case (i.e. there are none that are not CTT test cases)
                if (this.TestCases.FirstOrDefault(tc => !CoreTestToolUtilities.IsCoreTestToolTest(tc)) == null)
                {
                    // This is a test set containing only CTT test cases
                    coreTestToolOnlyTestSet = true;

                    // Since all test cases are CTT test cases we have at least one CTT test case
                    hasCoreTestToolTest = true;
                }

                // Else if we can find a CTT test case
                else if (this.TestCases.FirstOrDefault(tc => CoreTestToolUtilities.IsCoreTestToolTest(tc)) != null)
                {
                    // We have at least one CTT test case
                    hasCoreTestToolTest = true;
                }
            }

            // Update the properties
            IsCoreTestToolOnlyTestSet = coreTestToolOnlyTestSet;
            HasCoreTestToolTest = hasCoreTestToolTest;
        }
    }

    /// <summary>
    /// Interface that is used to convert objects to XML.
    /// </summary>
    public interface IXmlConverter
    {
        /// <summary>
        /// Converts the object to XML and returns a <see cref="System.Xml.Linq.XElement"/>.
        /// </summary>
        /// <returns><see cref="System.Xml.Linq.XElement"/> XML element.</returns>
        XElement ToXml();
    }

    /// <summary>
    /// Helper class to store test script information
    /// </summary>
    public class TestScript
    {
        public string className;

        /// <summary>
        /// Absolute path of the directory of this script file.
        /// </summary>
        public string AbsolutePath { get; set; }

        /// <summary>
        /// Whether the Directory property is relative to the path of the test set this script is contained in.
        /// </summary>
        public bool IsRelativeToTestset { get; set; }

        private string directory;

        /// <summary>
        /// Relative file system path to the directory of the script file.
        /// Set value is converted to relative path to the current working directory
        /// if this script is not relative to a test set file.
        /// </summary>
        public string Directory
        {
            get { return directory; }
            set
            {
                // Given path is already relative
                if (!Path.IsPathRooted(value) || this.IsRelativeToTestset)
                {
                    this.directory = value;
                    return;
                }
                // Make path to relative
                this.directory = FileUtilities.GetRelativePath(System.IO.Directory.GetCurrentDirectory(), value);
            }
        }

        public string file;
        public string method;

        /// <summary>
        /// Stores test script information
        /// </summary>
        /// <param name="className">Name of the class containing the executed test method.</param>
        /// <param name="directory">Directory that contains the script file.</param>
        /// <param name="file">File that contains the script class.</param>
        /// <param name="method">Method to be executed when running this test case.</param>
        /// <param name="testsetPath">Path of the testset file for which this script path is relative to.
        /// IsRelativeToTestset is set to true if a valid path is given.</param>
        public TestScript(string className, string directory, string file, string method, string testsetPath=null)
        {
            this.IsRelativeToTestset = false;
            this.AbsolutePath = Path.Combine(System.IO.Directory.GetCurrentDirectory(), directory);
            this.className = className;
            this.Directory = directory;
            this.file = file;
            this.method = method;

            if (!string.IsNullOrEmpty(testsetPath) && File.Exists(testsetPath))
            {
                this.AbsolutePath = Path.Combine(Path.GetDirectoryName(testsetPath), directory);
                this.Directory = FileUtilities.GetRelativePath(testsetPath, this.AbsolutePath);
                this.IsRelativeToTestset = true;
            }            
        }

        /// <summary>
        /// Returns all members as a string array in hierarchical order.
        /// </summary>
        /// <returns>All members in hierarchical order</returns>
        public string[] getValues()
        {
            return new string[] { AbsolutePath, file, className, method };
        }

        public XElement toXML()
        {
            // create attributes
            XAttribute[] attArray = {
                new XAttribute("directory", this.Directory),
                new XAttribute("file", this.file),
                new XAttribute("class", this.className),
                new XAttribute("method", this.method),
                new XAttribute("relativetotestset", this.IsRelativeToTestset) };

            XElement element = new XElement("testscript", attArray);

            if (Configuration != null)
                element.Add(Configuration.ToXml());

            return element;
        }

        public XElement ToXmlWithAbsolutePath()
        {
            // create attributes
            XAttribute[] attArray = {
                new XAttribute("directory", this.AbsolutePath),
                new XAttribute("file", this.file),
                new XAttribute("class", this.className),
                new XAttribute("method", this.method),
                new XAttribute("relativetotestset", false) };

            XElement element = new XElement("testscript", attArray);

            if (this.Configuration != null)
                element.Add(this.Configuration.ToXml());

            return element;
        }

        /// <summary>
        /// Compares two TestScript objects.
        /// </summary>
        /// <param name="testScript1">First TestScript object</param>
        /// <param name="testScript2">Second TestScript object</param>
        /// <returns>Returns true if objects are identical otherwise false</returns>
        public static bool Compare(TestScript testScript1, TestScript testScript2)
        {
            if (string.CompareOrdinal(testScript1.Directory, testScript2.Directory) == 0
                && string.CompareOrdinal(testScript1.file, testScript2.file) == 0
                && string.CompareOrdinal(testScript1.className, testScript2.className) == 0
                && string.CompareOrdinal(testScript1.method, testScript2.method) == 0)
                return true;

            return false;
        }

        /// <summary>
        /// Additional configuration information that can optionally be associated with the test script.
        /// </summary>
        public IXmlConverter Configuration
        {
            get;
            set;
        }
    }

    /// <summary>
    /// Class that stores the Core Test Tool configuration information associated with
    /// a Core Test Tool assembly.
    /// </summary>
    public class CoreTestToolConfiguration : IXmlConverter
    {
        private List<string> _sectionNames;

        /// <summary>
        /// Prevent an instance of this class from being created using the default constructor.
        /// </summary>
        private CoreTestToolConfiguration()
        {
        }

        /// <summary>
        /// Creates a new <see cref="CoreTestToolConfiguration"/> object.
        /// </summary>
        /// <param name="directory">Directory where the configuration file is located.</param>
        /// <param name="file">File name of the configuration file.</param>
        /// <param name="sectionNames">Names of the sections in the configuration file.</param>
        public CoreTestToolConfiguration(string directory, string file, IEnumerable<string> sectionNames)
        {
            // Store the information
            Directory = directory;
            File = file;

            // Create a list of section names
            _sectionNames = new List<string>();

            if (sectionNames != null)
            {
                foreach (string name in sectionNames)
                {
                    // Add each section name to the list
                    _sectionNames.Add(name);
                }
            }
        }

        /// <summary>
        /// Enumerator to iterate through the section names.
        /// </summary>
        public IEnumerable<string> SectionNames
        {
            get
            {
                return _sectionNames;
            }
        }

        /// <summary>
        /// Directory where the configuration file is located.
        /// </summary>
        public string Directory
        {
            get;
            private set;
        }

        /// <summary>
        /// File name of the configuration file.
        /// </summary>
        public string File
        {
            get;
            private set;
        }

        /// <summary>
        /// Converts the Core Test Tool configuration information to XML and returns a <see cref="System.Xml.Linq.XElement"/>.
        /// </summary>
        /// <returns><see cref="System.Xml.Linq.XElement"/> XML element.</returns>
        public XElement ToXml()
        {
            // Create attributes for the directory and file name
            XAttribute[] attributes = {
                new XAttribute("directory", Directory),
                new XAttribute("file", File)};

            // Create an element containing the attributes
            XElement element = new XElement("configuration", attributes);

            foreach (string name in _sectionNames)
            {
                // Add a child section containing the section name
                XElement sectionElement = new XElement("section", new XAttribute[] { new XAttribute("name", name) });
                element.Add(sectionElement);
            }

            return element;
        }
    }

    /// <summary>
    /// Test result model.
    /// </summary>
    public class TestResult : INotifyPropertyChanged
    {
        private bool isBlackboxModeOn;

        /// <summary>
        /// Gets or sets a value indicating whether the Blackbox mode was on when result was generated.
        /// </summary>
        public bool IsBlackboxModeOn
        {
            get { return this.isBlackboxModeOn; }
            set
            {
                this.isBlackboxModeOn = value;
                this.OnPropertyChanged("IsBlackboxModeOn");
            }
        }

        /// <summary>
        /// Contains the previous result.
        /// </summary>
        public string PreviousResult { get; set; }

        private string result = string.Empty;

        /// <summary>
        /// Contains the result of TestCase run.
        /// </summary>
        public string Result
        {
            get { return this.result; }
            set
            {
                if (this.result == value) return;

                this.PreviousResult = this.result ?? string.Empty;
                this.result = value;
                this.OnPropertyChanged("Result");
                this.OnPropertyChanged("IsOriginalResult");
            }
        }

        private string originalResult = string.Empty;

        /// <summary>
        /// Gets or sets the original result.
        /// </summary>
        public string OriginalResult
        {
            get
            {
                return this.originalResult;
            }
            set
            {
                // Original result can only be set once.
                if (!string.IsNullOrEmpty(this.originalResult)) return;

                this.originalResult = value;
                this.OnPropertyChanged("OriginalResult");
                this.OnPropertyChanged("IsOriginalResult");
            }
        }

        /// <summary>
        /// Gets a value indicating whether the result is original result.
        /// </summary>
        public bool IsOriginalResult 
        { 
            get
            {
                // When original result has not been set Result property is original.
                if (string.IsNullOrEmpty(this.OriginalResult)) return true;

                return this.Result == this.OriginalResult;
            }
        }

        public string Author = string.Empty;

        private DateTime runTime = DateTime.MinValue;

        /// <summary>
        /// Execution completion time of the result.
        /// </summary>
        public DateTime RunTime
        {
            get { return this.runTime; }
            set
            {
                this.runTime = value;
                this.OnPropertyChanged("RunTime");
            }
        }
        public string Description = string.Empty;
        private string resultPath = string.Empty;

        /// <summary>
        /// Relative file system path of the execution result file generated by the framework.
        /// Set value is always converted to relative path to the current working directory.
        /// </summary>
        public string ResultPath
        {
            get { return this.resultPath; }
            set
            {
                // Given path is already relative
                if (!Path.IsPathRooted(value))
                {
                    this.resultPath = value;
                    return;
                }

                // Make path to relate
                this.resultPath = MarbleLibrary.Utilities.FileUtilities.GetRelativePath(System.IO.Directory.GetCurrentDirectory(), value);
            }
        }

        private string errorReason = string.Empty;

        /// <summary>
        /// Contains the short description of the error that occurred during execution.
        /// </summary>
        public string ErrorReason
        {
            get { return this.errorReason; }
            set
            {
                this.errorReason = value;
                this.OnPropertyChanged("ErrorReason");
            }
        }

        private string errorTraceback = string.Empty;

        /// <summary>
        /// Contains the call stack of the error that occurred during execution.
        /// </summary>
        public string ErrorTraceback
        {
            get { return this.errorTraceback; }
            set
            {
                this.errorTraceback = value;
                this.OnPropertyChanged("ErrorTraceback");
            }
        }

        private bool hasCrashOrReset;

        /// <summary>
        /// Indicates whether this result contains one or more errors that occurred because of application crash or phone reset.
        /// </summary>
        public bool HasCrashOrReset
        {
            get { return this.hasCrashOrReset; }
            set
            {
                if (this.hasCrashOrReset == value) return;

                this.hasCrashOrReset = value;
                this.OnPropertyChanged("HasCrashOrReset");
            }
        }

        private int index;

        /// <summary>
        /// Sequence number of this result (if multiple results exist).
        /// </summary>
        public int Index
        {
            get { return this.index; }
            set
            {
                this.index = value;
                this.OnPropertyChanged("Index");
            }
        }

        private int warningCount;

        /// <summary>
        /// Number of warnings in this test result.
        /// </summary>
        public int WarningCount
        {
            get { return this.warningCount; }
            set
            {                
                if (this.warningCount == value) return;
                this.warningCount = value;
                this.OnPropertyChanged("WarningCount");
                this.OnPropertyChanged("WarningCountInfoString");
            }
        }

        /// <summary>
        /// 0 warnings, 1 warning, 2 warnings, etc.
        /// </summary>
        public string WarningCountInfoString
        {
            get { return this.WarningCount.ToString(CultureInfo.InvariantCulture) + (this.WarningCount == 1 ? " warning" : " warnings"); }
        }

        /// <summary>
        /// Empty constructor.
        /// Sets RunTime to DateTime.Now
        /// </summary>
        public TestResult()
        {
            this.Index = 1;
            this.RunTime = DateTime.Now;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="TestResult"/> class.
        /// </summary>
        /// <param name="result">The result.</param>
        /// <param name="time">The time.</param>
        /// <param name="reportPath">The report path.</param>
        /// <param name="author">The author.</param>
        /// <param name="isBlackboxModeOn"> </param>
        /// <param name="description">The description.</param>
        /// <param name="errorReason">The error reason.</param>
        /// <param name="errorTraceback">The error traceback.</param>
        public TestResult(
            string result,
            string time = "",
            string reportPath = "",
            string author = "",
            bool isBlackboxModeOn = false,
            string description = "",
            string errorReason = "",
            string errorTraceback = "",
            int warningCount = 0,
            bool hasCrashOrReset = false)
        {
            this.Index = 1;

            this.Result = result;
            DateTime tempRunTime;
            this.RunTime = !DateTime.TryParse(time, out tempRunTime) ? DateTime.Now : tempRunTime;

            // store parameters or String.Empty as a default
            this.ResultPath = reportPath ?? string.Empty;
            this.Author = author ?? string.Empty;
            this.IsBlackboxModeOn = isBlackboxModeOn;
            this.Description = description ?? string.Empty;
            this.ErrorReason = errorReason ?? string.Empty;
            this.ErrorTraceback = errorTraceback ?? string.Empty;
            this.WarningCount = warningCount;
            this.HasCrashOrReset = hasCrashOrReset;

        }

        /// <summary>
        /// Initializes a new instance of the TestResult class from the testresult element.
        /// </summary>
        /// <param name="xmlTestResult">Testresult element</param>
        public TestResult(XElement xmlTestResult)
        {
            this.Index = 1;

            // If testcase in .testset doesn't have a result element.
            if (xmlTestResult == null)
            {
                this.ResultPath = string.Empty;
                this.Result = string.Empty;
                this.RunTime = DateTime.Now;
                this.Description = string.Empty;
                this.Author = string.Empty;
                this.IsBlackboxModeOn = false;

                return;
            }

            // Report path
            XAttribute reportAttribute = xmlTestResult.Attribute("reportpath");
            if (reportAttribute != null)
                this.ResultPath = reportAttribute.Value;

            // Result
            XAttribute resultAttribute = xmlTestResult.Attribute("result");
            if (resultAttribute != null)
                this.Result = resultAttribute.Value;

            // Time
            XAttribute timeAttribute = xmlTestResult.Attribute("time");
            if (timeAttribute != null)
            {
                DateTime tempRunTime;
                this.RunTime = !DateTime.TryParse(timeAttribute.Value, out tempRunTime) ? DateTime.Now : tempRunTime;
            }

            // Description
            XAttribute descriptionAttribute = xmlTestResult.Attribute("description");
            if (descriptionAttribute != null)
                this.Description = descriptionAttribute.Value;

            // Author
            XAttribute authorAttribute = xmlTestResult.Attribute("author");
            if (authorAttribute != null)
                this.Author = authorAttribute.Value;

            // IsBlackboxModeOn
            XAttribute isBlackboxModeOnAttribute = xmlTestResult.Attribute("isblackboxmodeon");
            if (isBlackboxModeOnAttribute != null)
                this.IsBlackboxModeOn = bool.Parse(isBlackboxModeOnAttribute.Value);

            // Error reason
            XAttribute errorReasonAttribute = xmlTestResult.Attribute("errorreason");
            if (errorReasonAttribute != null)
                this.ErrorReason = errorReasonAttribute.Value;

            // Error traceback
            XAttribute errorTraceBackAttribute = xmlTestResult.Attribute("errortraceback");
            if (errorTraceBackAttribute != null)
                this.ErrorTraceback = errorTraceBackAttribute.Value;

            // Original Result
            XAttribute originalResultAttribute = xmlTestResult.Attribute("originalresult");
            if (originalResultAttribute != null)
                this.OriginalResult = originalResultAttribute.Value;

            // Warning count
            XAttribute warningCountAttribute = xmlTestResult.Attribute("warningcount");
            if (warningCountAttribute != null)
            {
                int value;
                if (int.TryParse(warningCountAttribute.Value, out value))
                    this.WarningCount = value;
            }

            // HasCrashOrReset
            XAttribute crashOrResetAttribute = xmlTestResult.Attribute("hascrashorreset");
            if (crashOrResetAttribute != null)
                this.HasCrashOrReset = bool.Parse(crashOrResetAttribute.Value);
        }

        public XElement ToXml()
        {
            // create attributes
            XAttribute[] attArray = {
                                        new XAttribute("result", this.Result), 
                                        new XAttribute("time", this.RunTime.ToString(CultureInfo.InvariantCulture)),
                                        //new XAttribute("description", description),
                                        new XAttribute("author", this.Author), 
                                        new XAttribute("isblackboxmodeon", this.IsBlackboxModeOn), 
                                        new XAttribute("reportpath", this.ResultPath),
                                        new XAttribute("errorreason", this.ErrorReason),
                                        new XAttribute("errortraceback", this.ErrorTraceback),
                                        new XAttribute("originalresult", this.OriginalResult),
                                        new XAttribute("warningcount", this.WarningCount),
                                        new XAttribute("hascrashorreset", this.HasCrashOrReset)
                                    };

            return new XElement("testresult", attArray);
        }

        /// <summary>
        /// Deletes the result file and resets all properties.
        /// </summary>
        public void ClearResult()
        {
            // Delete result file
            this.DeleteResultFile();

            this.ResultPath = string.Empty;
            this.Result = string.Empty;
            this.ErrorReason = string.Empty;
            this.ErrorTraceback = string.Empty;
            this.Author = string.Empty;
            this.RunTime = DateTime.MinValue;
            this.Description = string.Empty;
            this.IsBlackboxModeOn = false;
            this.WarningCount = 0;
            this.HasCrashOrReset = false;

            // Field is set to empty string because original result property can be only set once.
            this.originalResult = string.Empty;
        }

        /// <summary>
        /// Removes the result xml file from the file system.
        /// </summary>
        public void DeleteResultFile()
        {
            if (File.Exists(this.ResultPath))
            {
                try { File.Delete(this.ResultPath); }
                catch { }
            }
        }

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }

    /// <summary>
    /// Single test case model.
    /// </summary>
    public class TestCase : MediatorModel, INotifyPropertyChanged
    {
        /// <summary>
        /// Gets or sets the feature name of the test case.
        /// </summary>
        public string Feature { get; set; }

        /// <summary>
        /// Gets or sets the subarea name of the test case.
        /// </summary>
        public string Subarea { get; set; }

        private string name;

        /// <summary>
        /// Gets or sets the name of the test case.
        /// Vertical bar (pipe) '|' characters are replaces with slash '/'
        /// because pipe char has a special meaning in GUI to FW communication protocol.
        /// </summary>
        public string Name
        {
            get { return name; }
            set
            {
                if (name == value) return;

                name = value.Replace('|', '/');
                this.OnPropertyChanged("Name");
            }
        }

        /// <summary>
        /// Gets or sets the TestScript object of the test case.
        /// </summary>
        public TestScript Script { get; set; }

        /// <summary>
        /// Gets or sets the child Test Cases.
        /// </summary>
        public ObservableCollectionAdv<TestCase> Children { get; set; }

        private TestResult result;

        /// <summary>
        /// Gets or sets the test result of the test case.
        /// </summary>
        public TestResult Result
        {
            get { return this.result; }
            set
            {
                if (this.result == value)
                    return;

                if (this.result != null)
                    value.PreviousResult = this.result.Result;

                this.result = value;
                this.OnPropertyChanged("Result");

                // Root (summary) result changed, update status bar
                if (this.IsRoot && this.result.Result != this.result.PreviousResult)
                    this.Mediator.NotifyColleagues<TestCase>("UpdateStatusBar", this);
                // Update root (summary) result if needed
                else if (value.Result != string.Empty && this.Parent != null && this.Parent.Result.Result != value.Result)
                    this.Parent.SetResultSummary();

                // Update run time of the parent if required
                if (!this.IsRoot && this.Parent != null && this.Parent.Result.RunTime < value.RunTime)
                    this.Parent.Result.RunTime = value.RunTime;

                this.result.PropertyChanged += this.OnResultValueChanged;
            }
        }

        /// <summary>
        /// Root (summary) test case if this test case is a child result.
        /// </summary>
        public TestCase Parent { get; set;}

        private bool whiteboxChecked;

        /// <summary>
        /// Gets or sets whether the whitebox mode is enabled for the test case.
        /// </summary>
        public bool IsWhiteboxChecked
        {
            get { return this.whiteboxChecked; }
            set
            {
                if (this.whiteboxChecked == value) return;

                // Whitebox and Blackbox modes cannot be currently enabled simultaneously.
                if (value)
                {
                    if (this.IsBlackboxChecked) this.IsBlackboxChecked = false;
                }

                this.whiteboxChecked = value;
                this.OnPropertyChanged("IsWhiteboxChecked");
            }
        }

        private bool isBlackboxChecked;

        /// <summary>
        /// Gets or sets whether the blackbox mode is enabled for the test case.
        /// </summary>
        public bool IsBlackboxChecked
        {
            get
            {
                return this.isBlackboxChecked;
            }
            set
            {
                if (this.isBlackboxChecked == value) return;

                // Whitebox and Blackbox modes cannot be currently enabled simultaneously.
                if (value)
                {
                    if (this.IsWhiteboxChecked) this.IsWhiteboxChecked = false;
                }

                this.isBlackboxChecked = value;
                this.OnPropertyChanged("IsBlackboxChecked");
            }
        }

        private bool isRunning;

        /// <summary>
        /// Gets or sets a value indicating whether the test case is being executed.
        /// </summary>
        public bool IsRunning
        {
            get { return this.isRunning; }
            set
            {
                this.isRunning = value;
                this.OnPropertyChanged("IsRunning");

                if (App.ViewModel.SelectedTestCases.Contains(this))
                    this.Mediator.NotifyColleagues<TestCase>("SelectedTestCaseChanged", this);
            }
        }

        /// <summary>
        /// Indicates if the test case has children. (TestCase needs to be run multiple times)
        /// </summary>
        public bool HasChildren
        {
            get { return this.Children.Any(); }
        }

        private bool isExpanded;

        /// <summary>
        /// Indicates if the root test case result is expanded.
        /// </summary>
        public bool IsExpanded
        {
            get { return this.isExpanded; }
            set
            {
                this.isExpanded = value;
                this.OnPropertyChanged("IsExpanded");
            }
        }

        private bool isRoot;

        /// <summary>
        /// Indicates if the test case is the root TestCase.
        /// </summary>
        public bool IsRoot
        {
            get { return this.isRoot; }
            set
            {
                this.isRoot = value;
                this.OnPropertyChanged("IsRoot");
            }
        }

        private bool isVisible;

        /// <summary>
        /// Indicates if the test case should be visible in the UI.
        /// </summary>
        public bool IsVisible
        {
            get { return this.isVisible; }
            set
            {
                this.isVisible = value;
                this.OnPropertyChanged("IsVisible");
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether is absolute path needed for the XML.
        /// </summary>
        public bool IsAbsolutePathNeeded { get; set; }

        private int level;

        /// <summary>
        /// Level in the Results "tree".
        /// </summary>
        public int Level
        {
            get { return this.level; }
            set
            {
                this.level = value;
                this.OnPropertyChanged("Level");
            }
        }

        private int totalRunCount;

        /// <summary>
        /// Total amount of times that TestCase is supposed to be run.
        /// </summary>
        public int TotalRunCount
        {
            get { return this.totalRunCount; }
            set
            {
                if (this.totalRunCount == value) return;

                this.totalRunCount = value;
                this.OnPropertyChanged("TotalRunCount");
            }
        }

        /// <summary>
        /// Number of times this test case has been executed.
        /// Returns the amount of results in a root test case.
        /// </summary>
        public int RunCount
        {
            get
            {
                TestCase rootCase = this.GetRootCase();
                int count = rootCase.Children.Count;
                if (count == 0 && rootCase.Result.Result != string.Empty)
                    count = 1;
                return count;
            }
        }

        /// <summary>
        /// Gets or sets the miscellaneous XML attribute list for the test case. 
        /// This list contains XML attributes which aren't used by test case model, but are needed for the XML.
        /// </summary>
        public List<XAttribute> MiscXmlAttributeListForTestCase { get; set; }

        /// <summary>
        /// Gets number of results generated after defined time.
        /// </summary>
        /// <param name="startTime"></param>
        /// <returns></returns>
        public int GetRunCountFromTime(DateTime startTime)
        {
            TestCase rootCase = this.GetRootCase();
            // Just one result - no children results
            if (rootCase.Children.Count == 0 && rootCase.Result.RunTime > startTime)
                return 1;
            
            return rootCase.Children.Count(tc => tc.Result.RunTime > startTime);
        }

        public int FailedTestCaseCount { get { return this.Children.Count(child => child.Result.Result.ToLower().StartsWith("failed")); } }

        public int ErrorTestCaseCount { get { return this.Children.Count(child => child.Result.Result.ToLower() == "error"); } }

        public int PassedTestCaseCount { get { return this.Children.Count(child => child.Result.Result.ToLower() == "passed"); } }

        public int NoResultTestCaseCount { get { return this.Children.Count(child => child.Result.Result.ToLower() == "no result"); } }

        public int NotAvailableTestCaseCount
        {
            get
            {
                return
                    this.Children.Count(
                        child =>
                            !child.Result.Result.StartsWith("failed") 
                            && child.Result.Result.ToLower() != "error"
                            && child.Result.Result.ToLower() != "passed" 
                            && child.Result.Result.ToLower() != "no result");
            }
        }

        /// <summary>
        /// Number of warnings in this test case result or sum of all warnings in child test case results.
        /// </summary>
        public int WarningCount
        {
            get
            {
                if (this.IsRoot && this.Children.Count > 1)
                    return Children.Sum(child => child.Result.WarningCount);

                return this.Result.WarningCount;
            }
        }

        /// <summary>
        /// 0 warnings, 1 warning, 2 warnings, etc.
        /// </summary>
        public string WarningCountInfoString
        {
            get { return this.WarningCount.ToString(CultureInfo.InvariantCulture) + (this.WarningCount == 1 ? " Warning" : " Warnings"); }
        }

        /// <summary>
        /// Whether this testcase result or any of it's child results have application crashes or phone resets.
        /// </summary>
        public bool HasCrashOrReset
        {
            get { return this.Result.HasCrashOrReset || this.Children.Any(child => child.HasCrashOrReset); }
        }

        public int TotalTestCaseCount { get { return this.Children.Count; } }

        public Collection<TestCaseChartDataModel> ResultCountCollection
        {
            get
            {
                //Stopwatch stopwatch = new Stopwatch();

                //List<TimeSpan> timeSpans = new List<TimeSpan>();

                //stopwatch.Start();

                //for (int i = 0; i < 300; i++)
                //{
                //    object obj1 = this.Children.Count(child => child.Result.Result.ToLower().StartsWith("failed"));
                //    object obj2 = this.Children.Count(child => child.Result.Result.ToLower().StartsWith("error"));
                //    object obj3 = this.Children.Count(child => child.Result.Result.ToLower().StartsWith("passed"));
                //    object obj4 = this.Children.Count(child => child.Result.Result.ToLower().StartsWith("no result"));

                //    timeSpans.Add(stopwatch.Elapsed);
                //}

                //stopwatch.Stop();

                //MessageBox.Show(timeSpans.ToString());

                return new Collection<TestCaseChartDataModel>()
                    {
                        new TestCaseChartDataModel("Passed", this.PassedTestCaseCount),
                        new TestCaseChartDataModel("Failed", this.FailedTestCaseCount),
                        new TestCaseChartDataModel("Error", this.ErrorTestCaseCount),
                        new TestCaseChartDataModel("No Result", this.NoResultTestCaseCount)
                    };
            }
        }

        /// <summary>
        /// Initializes a new instance of the TestCase class.
        /// </summary>
        /// <param name="name">Testcase name.</param>
        /// <param name="script">TestScript</param>
        /// <param name="result">TestResult</param>
        /// <param name="feature">Feature</param>
        /// <param name="subarea">Subarea</param>
        public TestCase(string name, TestScript script, TestResult result = null, string feature = "", string subarea = "", string totalruncount = "", TestCase parent=null)
        {
            this.MiscXmlAttributeListForTestCase = new List<XAttribute>();

            int parseResult;
            this.TotalRunCount = int.TryParse(totalruncount, out parseResult) ? parseResult : 1;

            this.Name = name;
            this.Script = script;
            this.Result = result ?? new TestResult();
            this.Feature = feature;
            this.Subarea = subarea;
            this.Children = new ObservableCollectionAdv<TestCase>();
            this.IsRoot = true; // Set IsRoot true to the initial (first) TestCase item.
            this.IsVisible = true; // Set IsVisible true to the initial (first) TestCase item. This will always be visible.
            this.Level = 1; // Set the Level to 1 for the initial (first) TestCase item.
            this.Parent = parent;

            this.Children.CollectionChanged += ChildrenOnCollectionChanged;
        }

        private void ChildrenOnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            // HasChildren property is changed if
            // a) Collection reseted
            // b) Items added and collection was empty
            // c) Items removed and collection is now empty
            if (e.Action == NotifyCollectionChangedAction.Reset ||
                e.Action == NotifyCollectionChangedAction.Add && this.Children.Count == e.NewItems.Count ||
                e.Action == NotifyCollectionChangedAction.Remove && this.Children.Count == 0)
                this.OnPropertyChanged("HasChildren");

            // Update result when some of the child results may have been changed
            if (this.IsRoot && e.Action != NotifyCollectionChangedAction.Move)
                this.SetResultSummary();

            // Get new possible latest run time from the added child results
            if (this.IsRoot && (e.Action == NotifyCollectionChangedAction.Add || e.Action == NotifyCollectionChangedAction.Replace))
            {
                DateTime latestRunTime = DateTime.MinValue;
                foreach (TestCase testCase in e.NewItems)
                    if (testCase.Result.RunTime > latestRunTime)
                        latestRunTime = testCase.Result.RunTime;

                if (latestRunTime > this.Result.RunTime)
                    this.Result.RunTime = latestRunTime;
            }
            // Get latest run time from remaining children and update if needed
            else if (this.IsRoot && (e.Action == NotifyCollectionChangedAction.Remove || e.Action == NotifyCollectionChangedAction.Reset))
            {
                DateTime latestRunTime = DateTime.MinValue;
                foreach (TestCase testCase in this.Children)
                    if (testCase.Result.RunTime > latestRunTime)
                        latestRunTime = testCase.Result.RunTime;

                if (latestRunTime > this.Result.RunTime)
                    this.Result.RunTime = latestRunTime;                
            }

            this.updateChildrenRelatedInfo();
        }

        private void OnResultValueChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "Result")
            {
                // Child result changed, update root (summary) result
                if (!this.IsRoot && this.Parent != null)
                    this.Parent.SetResultSummary();
                this.Mediator.NotifyColleagues<TestCase>("UpdateStatusBar", this.GetRootCase());
            }
            else if (e.PropertyName == "RunTime")
            {
                // Update run time to parent if the parent run time is older
                if (!this.IsRoot && this.Parent != null && this.Parent.Result.RunTime < this.Result.RunTime)
                    this.Parent.Result.RunTime = this.Result.RunTime;
            }
        }

        public XElement toXML()
        {
            XElement xmlTestCase = new XElement(
                "testcase",
                new XAttribute("name", this.Name),
                new XAttribute("feature", this.Feature),
                new XAttribute("subarea", this.Subarea),
                new XAttribute("ucid", string.Empty),
                new XAttribute("totalruncount", this.TotalRunCount.ToString(CultureInfo.InvariantCulture)));

            // Possible miscellaneous attributes are added to test case element.
            foreach (XAttribute miscAttribute in this.MiscXmlAttributeListForTestCase)
            {
                XAttribute existingAttribute = xmlTestCase.Attribute(miscAttribute.Name.ToString());

                // If attribute is already found from test case element but has no value, miscellaneous attribute value is used instead.
                // Otherwise miscellaneous attribute is added to test case element.
                if (existingAttribute != null && string.IsNullOrEmpty(existingAttribute.Value)
                    && !string.IsNullOrEmpty(miscAttribute.Value)) existingAttribute.Value = miscAttribute.Value;
                else xmlTestCase.SetAttributeValue(miscAttribute.Name.ToString(), miscAttribute.Value);
            }

            XElement xmlTestScript = this.IsAbsolutePathNeeded ? this.Script.ToXmlWithAbsolutePath() : this.Script.toXML();
            XElement xmlTestResult = this.Result.ToXml();
            xmlTestCase.Add(xmlTestScript);
            xmlTestCase.Add(xmlTestResult);

            return xmlTestCase;
        }

        /// <summary>
        /// Determinates the result from all the child results and sets it as the result for this test case.
        /// </summary>
        public void SetResultSummary()
        {
            if (!this.isRoot)
                return;

            if (this.Children.Any(tc => tc.Result.Result.ToLower() == "error"))
                this.Result.Result = "Error";
            else if (this.Children.Any(tc => tc.Result.Result.ToLower().StartsWith("failed")))
                this.Result.Result = "Failed";
            else if (this.Children.Any(tc => tc.Result.Result.ToLower() == "no result"))
                this.Result.Result = "No Result";
            else if (this.Children.Any(tc => tc.Result.Result.ToLower() == "passed"))
                this.Result.Result = "Passed";
            else
                this.Result.Result = "N/A";
        }

        /// <summary>
        /// Creates a new runnable test case as a child result of this test case.
        /// </summary>
        /// <returns>Newly added test case to be executed next.</returns>
        public TestCase CreateNewChildTestCase()
        {
            if (!this.IsRoot)
                return null;

            if (this.Children.Count == 0)
                this.ConvertToSummaryCase();

            // Create a new TestCase
            TestCase testCase = new TestCase(
                this.Name,
                this.Script,
                null,
                this.Feature,
                this.Subarea,
                this.TotalRunCount.ToString(),
                this);

            testCase.IsVisible = this.IsExpanded;
            testCase.IsWhiteboxChecked = this.IsWhiteboxChecked;
            testCase.IsBlackboxChecked = this.IsBlackboxChecked;
            testCase.IsRoot = false;
            testCase.IsRunning = true;
            testCase.Level = 2; // Consecutive TestCases are level 2 (child node) in results tree.
            testCase.Result.Index = this.Children.Count + 1;

            this.Children.Add(testCase);
            this.Result.Result = this.RunCount.ToString();
            this.IsRunning = true;
            return testCase;
        }

        /// <summary>
        /// Converts normal single result test case to multiple result one.
        /// Current result is added as a first child test case of this test case.
        /// </summary>
        public void ConvertToSummaryCase()
        {
            TestCase testCase = new TestCase(
                this.Name,
                this.Script,
                this.Result,
                this.Feature,
                this.Subarea,
                this.TotalRunCount.ToString(),
                this);

            testCase.IsWhiteboxChecked = this.IsWhiteboxChecked;
            testCase.IsBlackboxChecked = this.IsBlackboxChecked;
            testCase.IsRoot = false;
            testCase.Level = 2;
            testCase.Result.Index = 1;

            this.Children.Add(testCase);
            this.Result = new TestResult(this.Result.Result);
        }

        /// <summary>
        /// Returns the root case of this test case (may be itself).
        /// </summary>
        /// <returns></returns>
        public TestCase GetRootCase()
        {
            return this.IsRoot ? this : this.Parent;
        }

        /// <summary>
        /// Clears all results from this test case.
        /// Result files are deleted from the file system.
        /// </summary>
        /// <param name="deleteResultFiles">Whether to also delete the result xml files from the hard drive.</param>
        public void ClearResults(bool deleteResultFiles = false)
        {
            // Remove child results
            if (deleteResultFiles)
                foreach (var testCase in this.Children)
                    testCase.Result.DeleteResultFile();

            this.Children.Clear();

            this.Result.ClearResult();
            this.IsExpanded = false;
        }

        private void updateChildrenRelatedInfo()
        {
            this.OnPropertyChanged("FailedTestCaseCount");
            this.OnPropertyChanged("ErrorTestCaseCount");
            this.OnPropertyChanged("PassedTestCaseCount");
            this.OnPropertyChanged("TotalTestCaseCount");
            this.OnPropertyChanged("WarningCount");
            this.OnPropertyChanged("HasCrashOrReset");
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