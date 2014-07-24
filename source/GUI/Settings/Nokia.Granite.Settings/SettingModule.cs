using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing.Design;
using System.Dynamic;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;
using System.Web.Script.Serialization;
using System.Xml;
using System.Xml.Serialization;
using IronPython.Compiler;
using IronPython.Hosting;
using IronPython.Runtime;
using IronPython.Runtime.Types;
using Microsoft.Scripting.Hosting;

namespace TestAutomation.Gui.Marble.Settings
{
    /// <summary>
    /// Class for the setting module that represents a single settings file.
    /// </summary>
    [Serializable]
    [XmlRoot(XmlTabs.SETTINGS)]
    public sealed class SettingModule : CollectionBase, IEnumerable, IEnumerable<Setting>, ICustomTypeDescriptor, IDynamicMetaObjectProvider, IXmlSerializable
    {
        /// <summary>
        /// Locking object used for synchronization.
        /// </summary>
        private static object _locker = new object();

        /// <summary>
        /// Script engine used to process IronPython source files.
        /// </summary>
        private static ScriptEngine _engine = null;

        /// <summary>
        /// File path to file containing the settings
        /// </summary>
        private string _settingFilePath = null;

        /// <summary>
        /// Name of the setting module.
        /// </summary>
        private string _name = null;

        /// <summary>
        /// Flag that overrides normal behaviour so that we can perform all unit tests from a child unit test AppDomain as though we were executing from the main AppDomain.
        /// </summary>
        private bool _unitTesting;

        /// <summary>
        /// Flag that indicates whether setting values are read-only or whether they can be changed.
        /// </summary>
        private bool _readOnly = true;

        /// <summary>
        /// Indicates whether module should fire SettingPropertyQuery event
        /// </summary>
        internal bool FireSettingsPropertyQuery = true;

        /// <summary>
        /// Event for indicating when a setting value query occurs.
        /// </summary>
        internal event SettingPropertyQueryEventHandler SettingPropertyQuery;

#if SUPPORT_DEFAULT_SUBDIRECTORY
        /// <summary>
        /// Name of the special 'default' subdirectory which allows IronPython setting modules to store their saved XML settings file in 
        /// the parent directory rather than in the same directory.
        /// </summary>
        private const string _defaultDirectoryName = "default";
#endif

        /// <summary>
        /// Prevent an instance of this class from being created directly.
        /// </summary>
        internal SettingModule() 
        {
        }

        /// <summary>
        /// Name of the setting module.
        /// </summary>
        public string Name
        {
            get
            {
                lock (_locker)
                {
                    return _name;
                }
            }
            internal set
            {
                lock (_locker)
                {
                    _name = value;
                }
            }
        }

        /// <summary>
        /// File path to the file containing the settings.
        /// </summary>
        /// <remarks>When this setting file path is changed the <see cref="Name"/> property will automatically
        /// be updated.</remarks>
        public string SettingFilePath
        {
            get
            {
                lock (_locker)
                {
                    return _settingFilePath;
                }
            }
            internal set
            {
                lock (_locker)
                {
                    _settingFilePath = value;
                }
                SetName();
            }
        }

        /// <summary>
        /// File path to the serialized settings file.
        /// </summary>
        /// <remarks>This read-only property will match the <see cref="SettingFilePath"/> unless
        /// the setting file path is an IronPython file, in which case this property is the 
        /// file path for the associated XML file.</remarks>
        internal string SavedSettingsFilePath
        {
            get
            {
                if (Path.GetExtension(SettingFilePath).ToLower() == Extensions.PYTHON)
                {
#if SUPPORT_DEFAULT_SUBDIRECTORY
                    DirectoryInfo directoryInformation = new DirectoryInfo(Path.GetDirectoryName(SettingFilePath));
                    
                    // If the name of the directory is the special 'default' directory
                    if (directoryInformation.Name == _defaultDirectoryName)
                    {
                        // The saved XML settings file is store in the parent directory
                        return Path.ChangeExtension(Path.Combine(directoryInformation.Parent.FullName, Path.GetFileName(SettingFilePath)), Extensions.XML);
                    }
#endif
                    return Path.ChangeExtension(SettingFilePath, Extensions.XML);
                }
                return SettingFilePath;
            }
        }

        /// <summary>
        /// Script engine used to process IronPython source files.
        /// </summary>
        internal static ScriptEngine Engine
        {
            get
            {
                lock (_locker)
                {
                    return _engine;
                }
            }
            private set
            {
                lock (_locker)
                {
                    _engine = value;
                }
            }
         }

        /// <summary>
        /// Gets a setting value by its name or display name.
        /// </summary>
        /// <param name="name">Setting name.</param>
        /// <returns>Setting value if found; otherwise <c>null</c> is returned.</returns>
        public object this[string name]
        {
            get
            {
                Setting setting = Find(s => s.Name == name);
                
                if (setting != null)
                {
                    // Check whether Reference / Main phone settings query. If so, add settings dynamically
                    if ((this.Name == "TestRun" && name == "POXSIPRegistrarServerUri") ||
                        (this.Name == "Main" && (name == "VoIPAccount" || name == "VoIPPassword")) ||
                        ((this.Name.StartsWith("Virtual") || this.Name == "Reference") && name == "PhoneNumber"))
                    {
                        if (this.SettingPropertyQuery != null && this.FireSettingsPropertyQuery)
                        {
                            SettingPropertyQueryEventArgs args = new SettingPropertyQueryEventArgs(this.Name, name, setting.Value, string.Empty);
                            this.SettingPropertyQuery(args);

                            if (args.NewValue != null && !string.IsNullOrEmpty((string)args.NewValue) && (string)args.NewValue != (string)setting.Value)
                            {
                                setting.Value = args.NewValue;
                            }
                        }
                    }
                }

                return setting != null ? setting.Value : null;
            }
        }

        /// <summary>
        /// Gets a setting value by its name or display name.
        /// </summary>
        /// <param name="settingName">Setting name.</param>
        /// <returns>Setting value if found; otherwise <c>null</c> is returned.</returns>
        public object GetSettingValue(string settingName)
        {
            object value;
            if (MemberBinder.IsFixedMemberCall(settingName, this, out value))
            {
                return value;
            }

            return this[settingName];
        }

        /// <summary>
        /// Sets a setting value by its name or display name.
        /// </summary>
        /// <param name="settingName">Setting name.</param>
        /// <param name="value">Value of the setting.</param>
        /// <returns>Value of <c>null</c>.</returns>
        /// <remarks>The default is for this method to not update the setting value.</remarks>
        public object SetSettingValue(string settingName, object value)
        {
            if (!ReadOnly || ((this.Name == "Reference" && settingName == "PhoneNumber") || (this.Name == "TestRun" && settingName == "POXSIPProxy") || (this.Name == "TestRun" && settingName == "BackendAvailable")))
            {
                lock (_locker)
                {
                    Setting setting = Find(s => s.Name == settingName);

                    if (setting != null)
                    {
                        setting.Value = value;
                    }
                }
            }

            return null;
        }

        /// <summary>
        /// Sets cancel values to all settings.
        /// </summary>
        public void SetCancelValuesToAll()
        {
            foreach (Setting item in this)
            {
                item.CancelValue = item.Value;
            }
        }

        /// <summary>
        /// Cancels all value changes by setting cancel value to value.
        /// </summary>
        public void CancelAllValues()
        {
            foreach (Setting item in this)
            {
                item.Value = item.CancelValue;
            }
        }

        /// <summary>
        /// Saves the setting module to file.
        /// </summary>
        internal void Save()
        {
            if (!AppDomain.CurrentDomain.IsDefaultAppDomain() && !UnitTesting)
            {
                return;
            }

            FileInfo fileInfo = new FileInfo(SavedSettingsFilePath);

            // Convert the settings to either JSON or XML format
            var data = fileInfo.Extension.ToLower() == Extensions.JSON ? ToJson() : ToXml();

            if (string.IsNullOrEmpty(data))
            {
                return;
            }

            try
            {
                if (fileInfo.Exists)
                {
                    fileInfo.Delete();
                }

                // Write the data contents to file
                using (FileStream fileStream = fileInfo.Open(FileMode.OpenOrCreate, FileAccess.Write, FileShare.ReadWrite))
                {
                    using (StreamWriter streamWriter = new StreamWriter(fileStream))
                    {
                        streamWriter.Write(data);
                    }
                }
            }
            catch
            {
            }
        }

        /// <summary>
        /// Gets a generic enumerator for the settings.
        /// </summary>
        /// <returns>Enumerator interface.</returns>
        public new IEnumerator GetEnumerator()
        {
            lock (_locker)
            {
                return InnerList.ToArray().GetEnumerator();
            }
        }

        /// <summary>
        /// Flag that overrides normal behaviour so that we can perform all unit tests from a child unit test AppDomain as though we were executing from the main AppDomain.
        /// </summary>
        internal bool UnitTesting
        {
            get
            {
                lock (_locker)
                {
                    return _unitTesting;
                }
            }
            set
            {
                lock (_locker)
                {
                    _unitTesting = value;
                }
            }
        }

        /// <summary>
        /// Flag that indicates whether setting values are read-only or whether they can be changed.
        /// </summary>
        internal bool ReadOnly
        {
            get
            {
                lock (_locker)
                {
                    return _readOnly;
                }
            }
            set
            {
                lock (_locker)
                {
                    _readOnly = value;
                }
            }
        }

        /// <summary>
        /// Adds a setting to the collection.
        /// </summary>
        /// <param name="setting">Setting to add.</param>
        internal void Add(Setting setting)
        {
            lock (_locker)
            {
                InnerList.Add(setting);
            }
        }

        /// <summary>
        /// Adds a range of settings to the collection.
        /// </summary>
        /// <param name="collection">Collection of settings to add.</param>
        internal void AddRange(IEnumerable<Setting> collection)
        {
            foreach (Setting item in collection)
            {
                Add(item);
            }
        }

        /// <summary>
        /// Determines whether a setting exists or not.
        /// </summary>
        /// <param name="match">Method that determines whether the setting matches some criteria or not.</param>
        /// <returns>Value of <c>true</c> if the setting matches, otherwise <c>false</c> is returned.</returns>
        internal bool Exists(Predicate<Setting> match)
        {
            foreach (Setting item in this)
            {
                if (match(item))
                {
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// Finds a setting that matches some criteria.
        /// </summary>
        /// <param name="match">Method that determines whether the setting matches some criteria or not.</param>
        /// <returns>Setting that matches the criteria or <c>null</c> if there is no setting that matches the criteria.</returns>
        internal Setting Find(Predicate<Setting> match)
        {
            foreach (Setting item in this)
            {
                if (match(item))
                {
                    return item;
                }
            }

            return null;
        }

        /// <summary>
        /// Find all settings that match some criteria.
        /// </summary>
        /// <param name="match">Method that determines whether the setting matches some criteria or not.</param>
        /// <returns>List of settings that match the criteria.</returns>
        internal List<Setting> FindAll(Predicate<Setting> match)
        {
            var items = new List<Setting>();

            foreach (Setting item in this)
            {
                if (match(item))
                {
                    items.Add(item);
                }
            }

            return items;
        }

        /// <summary>
        /// Removes the specified setting.
        /// </summary>
        /// <param name="setting">Setting to remove.</param>
        internal void Remove(Setting setting)
        {
            lock (_locker)
            {
                InnerList.Remove(setting);
            }
        }

        /// <summary>
        /// Removes all settings that match a specified criteria.
        /// </summary>
        /// <param name="match">Method that determines whether the setting matches some criteria or not.</param>
        internal void RemoveAll(Predicate<Setting> match)
        {
            foreach (Setting item in this)
            {
                if (match(item))
                {
                    Remove(item);
                }
            }
        }

        /// <summary>
        /// Retrieves the index of the setting.
        /// </summary>
        /// <param name="setting">Setting to get the index for.</param>
        /// <returns>Index of the setting if it was found, otherwise -1 is returned.</returns>
        internal int IndexOf(Setting setting)
        {
            int i = 0;

            foreach (var item in this)
            {
                if (item.Equals(setting))
                {
                    return i;
                }
                i++;
            }

            return -1;
        }

        /// <summary>
        /// Gets an enumerator for the settings.
        /// </summary>
        /// <returns>Enumerator interface for settings.</returns>
        IEnumerator<Setting> IEnumerable<Setting>.GetEnumerator()
        {
            lock (_locker)
            {
                return InnerList.OfType<Setting>().GetEnumerator();
            }
        }

        /// <summary>
        /// Creates a new setting module by reading the setting file based on its file extension.
        /// </summary>
        /// <param name="filePath">File path for the settings file.</param>
        /// <returns>New setting module created from reading the settings in the file.</returns>
        internal static SettingModule GetSettingsByFileExtension(string filePath)
        {
            if (string.IsNullOrEmpty(filePath))
            {
                return null;
            }

            FileInfo fileInfo = new FileInfo(filePath);

            if (!fileInfo.Exists)
            {
                return null;
            }

            var fileExtension = fileInfo.Extension.ToLower();

            // Return a new setting module by calling the appropriate method to read this type of setting file
            return fileExtension == Extensions.PYTHON ? GetSettingsFromPythonFile(fileInfo.FullName) : (fileExtension == Extensions.JSON ?
                GetSettingsFromJsonFile(fileInfo.FullName) : GetSettingsFromXmlFile(fileInfo.FullName));
        }

        /// <summary>
        /// Constructs a setting module from the JSON (JavaScript Object Notation) file.
        /// </summary>
        /// <param name="jsonFilePath">File path to the JSON file.</param>
        /// <returns>Setting module if the settings were successfully read, otherwise <c>null</c> is returned.</returns>
        internal static SettingModule GetSettingsFromJsonFile(string jsonFilePath)
        {
            FileInfo fileInfo = new FileInfo(jsonFilePath);

            if (fileInfo.Length == 0)
            {
                return null;
            }

            if (fileInfo.Extension.ToLower() != Extensions.JSON)
            {
                return null;
            }

            using (FileStream fileStream = fileInfo.Open(FileMode.Open, FileAccess.Read, FileShare.ReadWrite))
            {
                using(StreamReader streamReader = new StreamReader(fileStream))
                {
                    SettingModule module = SettingModule.FromJson(streamReader.ReadToEnd());

                    if (module != null)
                    {
                        module.SettingFilePath = fileInfo.FullName;

                        return module;
                    }
                }
            }

            return null;
        }

        /// <summary>
        /// Constructs a setting module from the IronPython file.
        /// </summary>
        /// <param name="ironPythonFilePath">File path to the IronPython file.</param>
        /// <returns>Setting module if the settings were successfully read, otherwise <c>null</c> is returned.</returns>
        /// <remarks>The settings are read from the IronPython file and if an associated XML file exists, the settings
        /// are overridden using the values in the XML file.</remarks>
        internal static SettingModule GetSettingsFromPythonFile(string ironPythonFilePath)
        {
            FileInfo file = new FileInfo(ironPythonFilePath);

            if (!file.Exists || file.Length == 0)
            {
                return null;
            }

            try
            {
                string source = null;

                // Read the contents of the file
                using (FileStream fileStream = file.Open(FileMode.Open, FileAccess.Read, FileShare.ReadWrite))
                {
                    using (StreamReader streamReader = new StreamReader(fileStream))
                    {
                        source = streamReader.ReadToEnd();
                    }
                }

                // If there is no default value token
                if (!source.Contains("DefaultValue"))
                {
                    // This file cannot contain settings
                    return null;
                }

                if (Engine == null)
                {
                    Engine = Python.CreateEngine(new Dictionary<string, object>()
                    {
                        { "LightweightScopes", true }
                    });
                }

                // Compile the code so that we can retrieve the classes and their properties
                PythonCompilerOptions pythonCompilerOptions = (PythonCompilerOptions)Engine.GetCompilerOptions();
                pythonCompilerOptions.Module &= ~ModuleOptions.Optimized;
                CompiledCode code = Engine.CreateScriptSourceFromString(source).Compile(pythonCompilerOptions);
                code.Execute();
                Engine.Runtime.Shutdown();

                // Create a new setting module for this IronPython file
                SettingModule settingModule = new SettingModule();
                settingModule.SettingFilePath = file.FullName;

                foreach (var settingClass in code.DefaultScope.GetItems())
                {
                    if (settingClass.Value is PythonType && settingClass.Value.__module__ == "<module>")
                    {
                        dynamic instance = settingClass.Value;

                        Type valueClrType = instance.__clrtype__();

                        if (valueClrType.IsSubclassOf(typeof(UITypeEditor)))
                        {
                            continue;
                        }

                        if (valueClrType.IsSubclassOf(typeof(TypeConverter)))
                        {
                            continue;
                        }

                        var setting = new Setting();

                        // Use the name of the class as the setting name
                        setting.Name = settingClass.Key;

                        // The default value is a mandatory field
                        try
                        {
                            setting.Value = instance.DefaultValue;

                            if (setting.Value != null)
                            {
                                setting.Value = Converters.ConvertToDynamic(setting.Value);
                            }
                        }
                        catch
                        {
                            continue;
                        }

                        // The display name is not a mandatory field
                        try
                        {
                            setting.DisplayName = instance.DisplayName.ToString();
                        }
                        catch
                        {
                            // Use the setting name as the display name since there was no valid display name specified
                            setting.DisplayName = setting.Name;
                        }

                        // The description is not a mandatory field
                        try
                        {
                            setting.Description = instance.Description.ToString();
                        }
                        catch
                        {
                            // Specify an empty description
                            setting.Description = string.Empty;
                        }

                        // The category is not a mandatory field
                        try
                        {
                            setting.Category = instance.Category.ToString();
                        }
                        catch
                        {
                            setting.Category = null;
                        }

                        // The editor is not a mandatory field
                        try
                        {
                            object editor = instance.Editor;

                            if (editor != null)
                            {
                                if (editor.GetType().IsSubclassOf(typeof(UITypeEditor)))
                                {
                                    setting.Editor = editor;
                                }
                            }
                        }
                        catch 
                        { 
                        }

                        // The converter is not a mandatory field
                        try
                        {
                            object converter = instance.Converter;

                            if (converter != null)
                            {
                                if (converter.GetType().IsSubclassOf(typeof(TypeConverter)))
                                {
                                    setting.Converter = converter;
                                }
                            }
                        }
                        catch 
                        { 
                        }

                        // The read-only for user is not a mandatory field
                        try
                        {
                            setting.ReadOnlyForUser = instance.ReadOnlyForUser;
                        }
                        catch
                        {
                        }

                        // Add the setting that was read from the IronPython file
                        settingModule.Add(setting);
                    }
                }

                // Update the settings since there may be an XML file with updated settings
                UpdateSavedPythonSettings(ref settingModule);     
           
                // Return the setting module if it has any settings
                return settingModule.Count > 0 ? settingModule : null;
            }
            catch
            {
                // If we encounter any error do not use the setting module or any settings
                return null;
            }
        }

        /// <summary>
        /// Constructs a setting module from the XML file.
        /// </summary>
        /// <param name="xmlFilePath">File path to the XML file.</param>
        /// <returns>Setting module if the settings were successfully read, otherwise <c>null</c> is returned.</returns>
        internal static SettingModule GetSettingsFromXmlFile(string xmlFilePath)
        {
            FileInfo xml = new FileInfo(xmlFilePath);

            if (!xml.Exists || xml.Length == 0)
            {
                return null;
            }

            FileInfo python = new FileInfo(Path.ChangeExtension(xmlFilePath, Extensions.PYTHON));

            if (python.Exists && python.Length > 0)
            {
                return null;
            }

            FileInfo json = new FileInfo(Path.ChangeExtension(xmlFilePath, Extensions.JSON));

            if (json.Exists && json.Length > 0)
            {
                return null;
            }

            using (FileStream fs = xml.Open(FileMode.Open, FileAccess.Read, FileShare.ReadWrite))
            {
                using (StreamReader sr = new StreamReader(fs))
                {
                    var module = SettingModule.FromXml(sr.ReadToEnd());

                    if (module != null)
                    {
                        module.SettingFilePath = xml.FullName;
                        foreach (Setting setting in module)
                        {
                            setting.Category = "Xml";
                        }

                        return module;
                    }
                }
            }

            return null;
        }

        /// <summary>
        /// Compares all settings in this setting module with the new supplied setting module and
        /// raises events as a result of doing the comparison.
        /// </summary>
        /// <param name="newModule">New setting module to compare settings with.</param>
        /// <param name="settingPropertyChangedEventHandler">Event to invoke when a property has changed.</param>
        /// <param name="settingAddedEventHandler">Event to invoke when a property has been added.</param>
        /// <param name="settingRemovedEventHandler">Event to invoke when a property has been removed.</param>
        internal void ReplaceBy(SettingModule newModule,
                                SettingPropertyChangedEventHandler settingPropertyChangedEventHandler,
                                SettingAddedEventHandler settingAddedEventHandler,
                                SettingRemovedEventHandler settingRemovedEventHandler)
        {
#if !USE_SINGLE_CPU
            // Process all settings that have been removed
            var remover = Task.Factory.StartNew(() =>
            {
#endif
                // For all existing settings
                foreach (Setting oldSetting in this)
                {
                    // If the setting no longer exists in the new setting module
                    if (!newModule.Exists(newSetting => newSetting.Name == oldSetting.Name))
                    {
                        // Get the name of the setting that has been removed
                        string name = oldSetting.Name;

                        // Remove the setting
                        Remove(oldSetting);

                        if (settingRemovedEventHandler != null)
                        {
                            // Raise the event that a setting has been removed
                            settingRemovedEventHandler(new SettingRemovedEventArgs(this.Name, name));
                        }
                    }
                }
#if !USE_SINGLE_CPU
            });

            // Process all settings that have been added or changed
            var adderAndChanger = Task.Factory.StartNew(() =>
            {
#endif
                // For all settings in the new module
                foreach (Setting setting in newModule)
                {
                    // Try and find the same setting in this setting module
                    Setting oldSetting = Find(os => os.Name == setting.Name);

                    // If we have this setting
                    if (oldSetting != null)
                    {
                        if (settingPropertyChangedEventHandler != null)
                        {
                            // If the setting values, description, category or display name has changed
                            if (!Converters.ObjectsMatch(oldSetting.Value, setting.Value) ||
                                (oldSetting.Description != setting.Description) ||
                                (oldSetting.Category != setting.Category) ||
                                (oldSetting.DisplayName != setting.DisplayName))
                            {
                                // Raise the event that a setting has been changed
                                settingPropertyChangedEventHandler(new SettingPropertyChangedEventArgs(Name, setting.Name, oldSetting.Value, setting.Value));
                            }
                        }

                        // Update our setting
                        oldSetting.Value = setting.Value;
                        oldSetting.Description = setting.Description;
                        oldSetting.Category = setting.Category;
                        oldSetting.DisplayName = setting.DisplayName;
                        oldSetting.Editor = setting.Editor;
                        oldSetting.Converter = setting.Converter;
                    }

                    // Else we do not have this setting
                    else
                    {
                        // Add this setting
                        Add(setting);

                        if (settingAddedEventHandler != null)
                        {
                            // Raise the event that a setting has been added
                            settingAddedEventHandler(new SettingAddedEventArgs(this.Name, setting.Name));
                        }
                    }
                }
#if !USE_SINGLE_CPU
            });

            // Wait for all removed settings to be identified
            remover.Wait();

            // Wait for all added or changed settings to be identified
            adderAndChanger.Wait();
#endif
        }

        /// <summary>
        /// Serializes this setting module to XML format.
        /// </summary>
        /// <returns>String containing the XML settings.</returns>
        internal string ToXml()
        {
            try
            {
                XmlSerializer serializer = new XmlSerializer(GetType());

                using (StringWriter stringWriter = new StringWriter())
                {
                    serializer.Serialize(stringWriter, this);
                    return stringWriter.ToString();
                }
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Serializes this setting module to JSON format.
        /// </summary>
        /// <returns>String containing the JSON settings.</returns>
        internal string ToJson()
        {
            try
            {
                Dictionary<string, object> objects = new Dictionary<string, object>();

                foreach (Setting setting in base.InnerList)
                {
                    objects.Add(setting.Name, setting.Value);
                }

                var serializer = new JavaScriptSerializer();

                return serializer.Serialize(objects);
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// De-serializes this setting module from XML format.
        /// </summary>
        /// <param name="json">String containing the XML settings.</param>
        /// <returns>New setting module.</returns>
        internal static SettingModule FromXml(string xmlData)
        {
            try
            {
                XmlSerializer serializer = new XmlSerializer(typeof(SettingModule));
                using (StringReader stringReader = new StringReader(xmlData))
                {
                    return serializer.Deserialize(stringReader) as SettingModule;
                }
            }
            catch(Exception)
            {
                return null;
            }
        }

        /// <summary>
        /// De-serializes this setting module from JSON format.
        /// </summary>
        /// <param name="jsonData">String containing the JSON settings.</param>
        /// <returns>New setting module.</returns>
        internal static SettingModule FromJson(string jsonData)
        {
            try
            {
                JavaScriptSerializer serializer = new JavaScriptSerializer();
                var settingDictionary = serializer.Deserialize<IDictionary<string, object>>(jsonData);

                if (settingDictionary == null || settingDictionary.Count == 0)
                {
                    return null;
                }

                SettingModule settings = new SettingModule();

                foreach (string key in settingDictionary.Keys)
                {
                    Setting setting = new Setting();
                    setting.Name = setting.DisplayName = key;
                    setting.Value = Converters.ConvertToDynamic(settingDictionary[key]);
                    setting.Category = "Json";
                    settings.Add(setting);
                }

                return settings;
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Generates a valid setting module name from the supplied name.
        /// </summary>
        /// <param name="name">Name to use.</param>
        /// <returns>A setting module name that does not contain an invalid characters.</returns>
        internal static string GenerateSettingModuleName(string name)
        {
            // Get rid of any full stops or spaces
            name = name.Replace(".", "").Replace(" ", "");

            // Remove any leading numbers from the name
            for (int i = 0; (i < name.Length && char.IsNumber(name[i])); i++)
            {
                name = name.Remove(i, 1);
                i--;
            }

            for (int i = 0; i < name.Length; i++)
            {
                // Remove any characters that are not letter or numbers or the '@' character
                if (!char.IsLetter(name[i]) && !char.IsNumber(name[i]) && name[i] != '@')
                {
                    name = name.Remove(i, 1);
                    i--;
                }
            }

            return name;
        }

        /// <summary>
        /// Gets the setting at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the setting to get.</param>
        /// <returns>Setting at the specified index.</returns>
        private Setting this[int index]
        {
            get
            {
                lock (_locker)
                {
                    return (Setting)InnerList.ToArray()[index];
                }
            }
        }

        /// <summary>
        /// Updates the settings in the supplied setting module with any settings in the associated XML file if it exists.
        /// </summary>
        /// <param name="pythonModule">Setting module to be updated.</param>
        private static void UpdateSavedPythonSettings(ref SettingModule pythonModule)
        {
            FileInfo xmlFile = new FileInfo(pythonModule.SavedSettingsFilePath);

            if (!xmlFile.Exists || xmlFile.Length == 0)
            {
                return;
            }

            SettingModule xmlSettingModule = null;

            // Read the contents of the XML file and create a setting module from it
            using(FileStream fileStream = xmlFile.Open(FileMode.Open, FileAccess.Read, FileShare.ReadWrite))
            {
                using (StreamReader streamReader = new StreamReader(fileStream))
                {
                    xmlSettingModule = SettingModule.FromXml(streamReader.ReadToEnd());
                }
            }

            if (xmlSettingModule != null)
            {
                // For each setting in the setting module
                foreach (Setting pythonSetting in pythonModule)
                {
                    // Find an XML setting with the same name
                    Setting xmlSetting = xmlSettingModule.Find(setting => setting.Name == pythonSetting.Name);

                    // If we found a setting with the same name
                    if (xmlSetting != null)
                    {
                        // If the setting values do not match
                        if (!Converters.ObjectsMatch(pythonSetting.Value, xmlSetting.Value))
                        {
                            // If these setting values are of the same type
                            if (pythonSetting.Value == null || xmlSetting.Value == null ||
                                (pythonSetting.Value.GetType() == xmlSetting.Value.GetType()))
                            {
                                // Update the setting value with that of the XML setting
                                pythonSetting.Value = xmlSetting.Value;
                            }
                        }
                    }
                }

                // Clear out the XML settings
                xmlSettingModule.Clear();
                xmlSettingModule = null;
            }
        }

        /// <summary>
        /// Updates the setting module name bases on the setting file name.
        /// </summary>
        private void SetName()
        {
            // Get the file name without any extension
            string name = Path.GetFileNameWithoutExtension(SettingFilePath);

            // Generate a setting module name from the file name (without extension)
            name = GenerateSettingModuleName(name);

            // Update the setting module name
            Name = name;
        }

        #region IXmlSerializable Members

        /// <summary>
        /// This method is reserved and should always return <c>null</c>.
        /// </summary>
        /// <returns>Value of <c>null</c>.</returns>
        public System.Xml.Schema.XmlSchema GetSchema()
        {
            return null;
        }

        /// <summary>
        /// Clears out all settings and then reads the XML content and adds the settings to this setting module.
        /// </summary>
        /// <param name="reader">XML reader used to read the XML elements.</param>
        public void ReadXml(XmlReader reader)
        {
            base.Clear(); 

            bool wasEmpty = reader.IsEmptyElement;
            reader.Read();

            if (wasEmpty)
                return;

            while (reader.NodeType != XmlNodeType.EndElement)
            {
                var setting = new Setting();

                setting.Name = setting.DisplayName = reader.GetAttribute(XmlTabs.SETTING_NAME);
                reader.ReadStartElement(XmlTabs.SETTING);
                string type = reader.GetAttribute(XmlTabs.SETTING_VALUE_TYPE);

                if (type == XmlTabs.DICTIONARY)
                {
                    var dict = new DynamicDictionary<object, object>();
                    dict.ReadXml(reader);
                    setting.Value = Converters.ConvertToDynamic(dict);
                }
                
                else if (type == XmlTabs.LIST)
                {
                    var list = new SerializableList<object>();
                    list.ReadXml(reader);
                    setting.Value = Converters.ConvertToDynamic(list);
                }
                
                else
                {
                    bool isEmpty = reader.IsEmptyElement;
                    reader.ReadStartElement(XmlTabs.SETTING_VALUE);
                    var content = reader.ReadString();
                    setting.Value = Converters.ConvertFromString(content, type);
                    if (!isEmpty)
                    {
                        reader.ReadEndElement();
                    }
                }
                
                reader.ReadEndElement();

                base.InnerList.Add(setting);
            }
            reader.ReadEndElement();
        }

        /// <summary>
        /// Writes the settings to XML.
        /// </summary>
        /// <param name="writer">XML writer used to write the XML elements.</param>
        public void WriteXml(XmlWriter writer)
        {
            foreach (Setting setting in InnerList)
            {
                Type valueType = setting.Value.GetType();

                writer.WriteStartElement(XmlTabs.SETTING);
                writer.WriteAttributeString(XmlTabs.SETTING_NAME, setting.Name);
                writer.WriteStartElement(XmlTabs.SETTING_VALUE);

                if (!(setting.Value is IXmlSerializableCollection))
                {
                    writer.WriteAttributeString(XmlTabs.SETTING_VALUE_TYPE, Converters.GetAlias(valueType));
                    writer.WriteString(Converters.ConvertToString(setting.Value, valueType));
                }
                else
                {
                    string collectionType = ((XmlRootAttribute)valueType.GetCustomAttributes(typeof(XmlRootAttribute), 
                        false).First()).ElementName;

                    writer.WriteAttributeString(XmlTabs.SETTING_VALUE_TYPE, collectionType);
                    var serializable = (IXmlSerializableCollection)setting.Value;
                    serializable.WriteXml(writer);
                }

                writer.WriteEndElement();
                writer.WriteEndElement();
            }
        }

        #endregion

        #region ICustomTypeDescriptor Members

        public AttributeCollection GetAttributes()
        {
            return TypeDescriptor.GetAttributes(this, true);
        }

        public string GetClassName()
        {
            return TypeDescriptor.GetClassName(this, true);
        }

        public string GetComponentName()
        {
            return TypeDescriptor.GetComponentName(this, true);
        }

        public TypeConverter GetConverter()
        {
            return TypeDescriptor.GetConverter(this, true);
        }

        public EventDescriptor GetDefaultEvent()
        {
            return TypeDescriptor.GetDefaultEvent(this, true);
        }

        public PropertyDescriptor GetDefaultProperty()
        {
            return TypeDescriptor.GetDefaultProperty(this, true);
        }

        public object GetEditor(Type editorBaseType)
        {
            return TypeDescriptor.GetEditor(this, editorBaseType, true);
        }

        public EventDescriptorCollection GetEvents(Attribute[] attributes)
        {
            return TypeDescriptor.GetEvents(this, attributes, true);
        }

        public EventDescriptorCollection GetEvents()
        {
            return TypeDescriptor.GetEvents(this, true);
        }

        public PropertyDescriptorCollection GetProperties(Attribute[] attributes)
        {
            PropertyDescriptor[] newProperties = new PropertyDescriptor[this.Count];
            for (int i = 0; i < this.Count; i++)
            {

                Setting setting = (Setting)this[i];
                newProperties[i] = new SettingDescriptor(ref setting, attributes);
            }

            return new PropertyDescriptorCollection(newProperties);
        }

        public PropertyDescriptorCollection GetProperties()
        {
            return TypeDescriptor.GetProperties(this, true);
        }

        public object GetPropertyOwner(PropertyDescriptor propertyDescriptor)
        {
            return this;
        }

        #endregion

        #region IDynamicMetaObjectProvider Members

        /// <summary>
        /// Nested class representing the dynamic binding and binding logic.
        /// </summary>
        private class SettingModuleMetaObject : DynamicMetaObject
        {
            /// <summary>
            /// Prevent an instance of the class from being created externally.
            /// </summary>
            /// <param name="expression">The expression representing this <see cref="SettingModuleMetaObject"/> during the dynamic binding process.</param>
            /// <param name="value">The runtime value represented by the <see cref="SettingModuleMetaObject"/>.</param>
            internal SettingModuleMetaObject(System.Linq.Expressions.Expression parameter,
                SettingModule value)
                : base(parameter, BindingRestrictions.Empty, value)
            { 
            }

            /// <summary>
            /// Performs the binding of the dynamic get member operation.
            /// </summary>
            /// <param name="binder">An instance of the <see cref="System.Dynamic.GetMemberBinder"/> that represents the details of the dynamic operation.</param>
            /// <returns>The new <see cref="System.Dynamic.DynamicMetaObject"/> representing the result of the binding.</returns>
            public override DynamicMetaObject BindGetMember(GetMemberBinder binder)
            {
                // Assume the name being called is the name of the setting value
                string methodName = "GetSettingValue";

                // Specify the name of the setting as the parameter
                Expression[] parameters = new Expression[]
                {
                    Expression.Constant(binder.Name)
                };

                // Create the dynamic binding and a binding logic to get the setting module
                DynamicMetaObject getDictionaryEntry = new DynamicMetaObject(
                    Expression.Call(
                        Expression.Convert(Expression, LimitType),
                        typeof(SettingModule).GetMethod(methodName),
                        parameters),
                    BindingRestrictions.GetTypeRestriction(Expression, LimitType));

                return getDictionaryEntry;
            }

            /// <summary>
            /// Performs the binding of the dynamic set member operation.
            /// </summary>
            /// <param name="binder">An instance of the <see cref="System.Dynamic.GetMemberBinder"/> that represents the details of the dynamic operation.</param>
            /// <returns>The new <see cref="System.Dynamic.DynamicMetaObject"/> representing the result of the binding.</returns>
            public override DynamicMetaObject BindSetMember(SetMemberBinder binder, DynamicMetaObject value)
            {
                // Assume the name being called is the name of the setting therefore use the method to set the setting value
                string methodName = "SetSettingValue";

                // Setup the binding restrictions
                BindingRestrictions restrictions = BindingRestrictions.GetTypeRestriction(Expression, LimitType);

                // Specify the name of the property to set and the second parameter is the value
                Expression[] parameters = new Expression[]
                    {
                        Expression.Constant(binder.Name),
                        Expression.Convert(value.Expression, typeof(object))
                    };

                // Setup the 'this' reference
                Expression self = Expression.Convert(Expression, LimitType);

                // Setup the method call expression
                Expression methodCall = Expression.Call(self,
                        typeof(SettingModule).GetMethod(methodName),
                        parameters);

                // Create a meta object to invoke Set later:
                DynamicMetaObject setDictionaryEntry = new DynamicMetaObject(
                    methodCall,
                    restrictions);

                // Return that dynamic object
                return setDictionaryEntry;
            }
        }

        /// <summary>
        /// Returns the <see cref="System.Dynamic.DynamicMetaObject"/> responsible for binding operations performed on this object.
        /// </summary>
        /// <param name="parameter">The expression tree representation of the runtime value.</param>
        /// <returns>The <see cref="System.Dynamic.DynamicMetaObject"/> to bind this object.</returns>
        public DynamicMetaObject GetMetaObject(Expression parameter)
        {
            // Create a new setting module meta object for the binding
            return new SettingModuleMetaObject(parameter, this);
        }

        #endregion
    }
}
