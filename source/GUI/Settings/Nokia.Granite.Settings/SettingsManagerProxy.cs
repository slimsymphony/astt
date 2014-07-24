using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace TestAutomation.Gui.Marble.Settings
{
    /// <summary>
    /// Proxy class that performs the work to manage all of the settings.
    /// </summary>
    internal sealed class SettingsManagerProxy : MarshalByRefObject, IEnumerable, IDisposable
    {
        /// <summary>
        /// Locker object to control access.
        /// </summary>
        private static object _locker = new object();

        /// <summary>
        /// Collection of setting modules.
        /// </summary>
        private SettingModuleCollection _settingModules = null;

        /// <summary>
        /// List of file system watchers that watch directories.
        /// </summary>
        private List<FileSystemWatcher> _watchers = null;

        /// <summary>
        /// Flag that overrides normal behaviour so that we can perform all unit tests from a child unit test AppDomain as though we were executing from the main AppDomain.
        /// </summary>
        private bool _unitTesting;

        /// <summary>
        /// Flag that indicates whether this object has been disposed.
        /// </summary>
        private bool _disposed;

#if SUPPORT_DEFAULT_SUBDIRECTORY
        /// <summary>
        /// Name of the special 'default' subdirectory which allows IronPython setting modules to store their saved XML settings file in 
        /// the parent directory rather than in the same directory.
        /// </summary>
        private const string _defaultDirectoryName = "default";
#endif

        /// <summary>
        /// Flag that indicates whether setting values are read-only or whether they can be changed.
        /// </summary>
        private bool _readOnly = true;

        /// <summary>
        /// Creates a new <see cref="SettingsManagerProxy"/> object.
        /// </summary>
        internal SettingsManagerProxy()
        {
            _settingModules = new SettingModuleCollection();

#if SETTINGS_MANAGER_PROXY_ASSEMBLY_RESOLVER
            AppDomain.CurrentDomain.AssemblyResolve += new ResolveEventHandler(AssemblyResolve);
#endif
        }

        /// <summary>
        /// Destructor.
        /// </summary>
        ~SettingsManagerProxy()
        {
            // Dispose of this object
            Dispose(false);
        }

        /// <summary>
        /// Disposes of this object.
        /// </summary>
        /// <remarks>This object should not be used again after calling this method. If you instead want to clear out all
        /// settings that were loaded and reset the object to its initial state then call <see cref="Reset"/> instead of 
        /// <see cref="Dispose"/>.</remarks>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Disposes of this object.
        /// </summary>
        /// <param name="disposing">Set to <c>true</c> to release both managed and unmanaged resources, or 
        /// <c>false</c> to release only unmanaged resources.</param>
        private void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    if (Watchers != null)
                    {
                        Watchers.ForEach(w =>
                        {
                            w.EnableRaisingEvents = false;
                            w.Created -= new FileSystemEventHandler(OnSettingModuleChanged);
                            w.Deleted -= new FileSystemEventHandler(OnSettingModuleChanged);
                            w.Changed -= new FileSystemEventHandler(OnSettingModuleChanged);
                            w.Renamed -= new RenamedEventHandler(OnSettingModuleRenamed);
                            w.Dispose();
                            w = null;
                        });
                        Watchers = null;
                    }

                    if (_settingModules != null)
                    {
                        _settingModules.Clear();
                        _settingModules = null;
                    }

#if SETTINGS_MANAGER_PROXY_ASSEMBLY_RESOLVER
                    AppDomain.CurrentDomain.AssemblyResolve -= new ResolveEventHandler(AssemblyResolve);
#endif
                }

                // We have disposed of this object
                _disposed = true;
            }
        }

        /// <summary>
        /// Returns an enumerator that iterates through the setting modules.
        /// </summary>
        /// <returns>Enumerator interface.</returns>
        public IEnumerator GetEnumerator()
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            return _settingModules.GetEnumerator();
        }

        /// <summary>
        /// Obtains a lifetime service object to control the lifetime policy for this
        /// instance.
        /// </summary>
        /// <returns>Returns a <c>null</c> value.</returns>
        public override object InitializeLifetimeService()
        {
            return null;
        }

        /// <summary>
        /// Event for when a setting module has been added.
        /// </summary>
        internal event SettingModuleAddedEventHandler SettingModuleAdded;

        /// <summary>
        /// Event for when a setting module has been removed.
        /// </summary>
        internal event SettingModuleRemovedEventHandler SettingModuleRemoved;

        /// <summary>
        /// Event for when a setting module has been renamed.
        /// </summary>
        internal event SettingModuleRenamedEventHandler SettingModuleRenamed;

        /// <summary>
        /// Event for when a setting value has been changed.
        /// </summary>
        internal event SettingPropertyChangedEventHandler SettingValueChanged;

        /// <summary>
        /// Event for when a setting has been added.
        /// </summary>
        internal event SettingAddedEventHandler SettingAdded;

        /// <summary>
        /// Event for when a setting has been removed.
        /// </summary>
        internal event SettingRemovedEventHandler SettingRemoved;

        /// <summary>
        /// Event for indicating when a setting value query occurs.
        /// </summary>
        internal event SettingPropertyQueryEventHandler SettingPropertyQuery
        {
            add
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                {
                    settingPropertyQueryHandlerRef = value;
                    // For each of the setting modules
                    foreach (var enumerator in _settingModules)
                    {
                        var module = enumerator as SettingModule;
                        if (module != null)
                        {
                            module.SettingPropertyQuery += value;
                        }
                    }
                }
            }
            remove
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                {
                    settingPropertyQueryHandlerRef = null;
                    // For each of the setting modules
                    foreach (var enumerator in _settingModules)
                    {
                        var module = enumerator as SettingModule;
                        if (module != null)
                        {
                            module.SettingPropertyQuery -= value;
                        }
                    }
                }
            }
        }

        private SettingPropertyQueryEventHandler settingPropertyQueryHandlerRef;

        /// <summary>
        /// Flag that overrides normal behaviour so that we can perform all unit tests from a child unit test AppDomain as though we were executing from the main AppDomain.
        /// </summary>
        internal bool UnitTesting
        {
            get
            {
                return _unitTesting;
            }

            set
            {
                // If the value is being changed
                if (_unitTesting != value)
                {
                    // Store the new value
                    _unitTesting = value;

                    // For each of the setting modules
                    foreach (var enumerator in _settingModules)
                    {
                        var module = enumerator as SettingModule;
                        if (module != null)
                        {
                            // Update the setting module with the same flag value
                            module.UnitTesting = _unitTesting;
                        }
                    }
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
                if (_disposed)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }

                return _readOnly;
            }

            set
            {
                if (_disposed)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }

                // If the value is being changed
                if (_readOnly != value)
                {
                    // Store the new value
                    _readOnly = value;

                    // For each of the setting modules
                    foreach (var enumerator in _settingModules)
                    {
                        var module = enumerator as SettingModule;
                        if (module != null)
                        {
                            // Update the setting module with the same flag value
                            module.ReadOnly = _readOnly;
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Collection of setting modules.
        /// </summary>
        internal SettingModuleCollection SettingModules
        {
            get
            {
                if (_disposed)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }

                return _settingModules;
            }
        }

        /// <summary>
        /// Synchronously saves all of the settings.
        /// </summary>
        internal void SaveAll()
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            IsSaving = true;
            try
            {
#if USE_SINGLE_CPU
                foreach (SettingModule module in _settingModules)
                {
                    module.Save();
                }
#else
                Parallel.ForEach(_settingModules, s => s.Save());
#endif
            }
            finally
            {
                IsSaving = false;
            }
        }

        /// <summary>
        /// Synchronously saves the setting module with the specified name.
        /// </summary>
        /// <param name="name">Name of the setting module.</param>
        internal void Save(string name)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            // Find the setting module with the name
            SettingModule module = _settingModules.Find(s => s.Name == name);

            if (module != null)
            {
                IsSaving = true;
                try
                {
                    // Save the setting module
                    module.Save();
                }
                finally
                {
                    IsSaving = false;
                }
            }
        }

        /// <summary>
        /// Synchronously sets cancel values to all settings.
        /// </summary>
        internal void SetCancelValuesToAll()
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            try
            {
#if USE_SINGLE_CPU
                foreach (SettingModule module in _settingModules)
                {
                    module.SetCancelValuesToAll();
                }
#else
                Parallel.ForEach(_settingModules, s => s.SetCancelValuesToAll());
#endif
            }
            finally { }
        }

        /// <summary>
        /// Synchronously cancels all changes made to settings.
        /// </summary>
        internal void CancelAll()
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            try
            {
#if USE_SINGLE_CPU
                foreach (SettingModule module in _settingModules)
                {
                    module.CancelAllValues();
                }
#else
                Parallel.ForEach(_settingModules, s => s.CancelAllValues());
#endif
            }
            finally { }
        }

        /// <summary>
        /// Synchronously loads all of the settings files in a directory.
        /// </summary>
        /// <param name="directory">Directory where the settings file are located.</param>
        /// <param name="includeSubdirectories">Flag to indicate whether to include settings files in sub-directories.</param>
        internal void LoadSettingsFromDirectory(string directory, bool includeSubdirectories = false)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            if (!Directory.Exists(directory))
            {
                return;
            }

            SearchOption searchOption = includeSubdirectories ? SearchOption.AllDirectories : SearchOption.TopDirectoryOnly;

            List<string> files = Directory.GetFiles(directory, "*" + Extensions.PYTHON, searchOption).ToList();
            files.AddRange(Directory.GetFiles(directory, "*" + Extensions.JSON, searchOption));
            files.AddRange(Directory.GetFiles(directory, "*" + Extensions.XML, searchOption));

#if SUPPORT_DEFAULT_SUBDIRECTORY

            // We only attempt to use this feature of checking files in a 'default' subdirectory if we are not including files in all subdirectories.

            bool checkDefaultSubdirectory = false;
            string defaultSubdirectory = Path.Combine(directory, _defaultDirectoryName);

            if (!includeSubdirectories)
            {
                // If there is a 'default' subdirectory
                if (Directory.Exists(defaultSubdirectory))
                {
                    // Include setting files in this directory
                    files.AddRange(Directory.GetFiles(defaultSubdirectory, "*" + Extensions.PYTHON, searchOption));
                    files.AddRange(Directory.GetFiles(defaultSubdirectory, "*" + Extensions.JSON, searchOption));
                    files.AddRange(Directory.GetFiles(defaultSubdirectory, "*" + Extensions.XML, searchOption));

                    // We will need to check the default subdirectory
                    checkDefaultSubdirectory = true;
                }
            }
#endif

            foreach (string file in files.ToArray())
            {
                if (Path.GetExtension(file).ToLower() == Extensions.XML)
                {
#if SUPPORT_DEFAULT_SUBDIRECTORY
                    // If an IronPython file exists with the same file name in the same directory or the default subdirectory
                    if (File.Exists(Path.ChangeExtension(file, Extensions.PYTHON)) ||
                        (checkDefaultSubdirectory && File.Exists(Path.ChangeExtension(Path.Combine(defaultSubdirectory, Path.GetFileName(file)), Extensions.PYTHON))))
                    {
                        files.Remove(file);
                    }
#else
                    // If an IronPython file exists with the same file name in the same directory
                    if (File.Exists(Path.ChangeExtension(file, Extensions.PYTHON)))
                    {
                        files.Remove(file);
                    }
#endif
                }
            }

#if USE_SINGLE_CPU
            files.ForEach(f => LoadSettingsFromFile(f));
#else
            Parallel.ForEach(files, f => LoadSettingsFromFile(f));
#endif

            // We may not have necessarily have found any settings files but we still add a settings watcher in case settings files are later added
            AddSettingsWatcher(new DirectoryInfo(directory));

#if SUPPORT_DEFAULT_SUBDIRECTORY
            if (checkDefaultSubdirectory)
            {
                // Add a settings watcher to also watch the 'default' subdirectory
                AddSettingsWatcher(new DirectoryInfo(defaultSubdirectory));
            }
#endif
        }

        /// <summary>
        /// Synchronously loads all the settings from a settings files.
        /// </summary>
        /// <param name="filePath">File path to the settings file.</param>
        internal void LoadSettingsFromFile(string filePath)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            if (string.IsNullOrEmpty(filePath))
            {
                return;
            }

            var file = new FileInfo(filePath);

            if (!file.Exists || file.Length == 0)
            {
                return;
            }

            var extension = file.Extension.ToLower();

            SettingModule settingModule = null;

            if (extension == Extensions.PYTHON)
            {
                settingModule = SettingModule.GetSettingsFromPythonFile(file.FullName);
            }

            else if (extension == Extensions.JSON)
            {
                settingModule = SettingModule.GetSettingsFromJsonFile(filePath);
            }

            else if (extension == Extensions.XML && !File.Exists(Path.ChangeExtension(file.FullName, Extensions.PYTHON)))
            {
                settingModule = SettingModule.GetSettingsFromXmlFile(filePath);
            }

            if (settingModule == null)
            {
                return;
            }

            // Set the flag to indicate whether we are unit testing
            settingModule.UnitTesting = UnitTesting;

            // Set the flag to indicate whether the setting module is read-only
            settingModule.ReadOnly = ReadOnly;

            if (_settingModules.Add(settingModule))
            {
#if SUPPORT_DEFAULT_SUBDIRECTORY
                // Add a file system watcher for the directory of the saved file since it may be a different directory
                AddSettingsWatcher(new DirectoryInfo(Path.GetDirectoryName(settingModule.SavedSettingsFilePath)));
#endif

                // Add a file system watcher for the directory of this file
                AddSettingsWatcher(file.Directory);

                if (SettingModuleAdded != null)
                {
                    // Raise the event that a setting module has been added
                    SettingModuleAdded(new SettingModuleAddedEventArgs(settingModule.Name, settingModule.SettingFilePath));
                }
            }
        }

        /// <summary>
        /// Get the value of a setting.
        /// </summary>
        /// <param name="name">Name of the setting.</param>
        /// <returns>Value of the setting or <c>null</c> if the setting value could not be obtained.</returns>
        internal object GetSettings(string name)
        {
            lock (_locker)
            {
                if (_disposed)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }

                if (string.IsNullOrEmpty(name))
                {
                    return null;
                }

                // Separate the tokens
                string[] tokens = name.Split(new char[] { '\\', '/', '.', ':' }, StringSplitOptions.RemoveEmptyEntries);

                // Find the setting module with the name of the first token
                SettingModule module = _settingModules.Find(s => s.Name == tokens[0]);

                if (module == null)
                {
                    // When Marble POX Backend is in use, Marble is able to add new VirtualPhones dynamically.
                    if (name.StartsWith("Virtual"))
                    {
                        module = new SettingModule();
                        module.Name = name;
                        // Generate Setting class instances for the settings
                        module.Add(new Setting { Name = "PhoneNumber", Value = "", Category = "VoIP", Description = "Access path: " + name + ".PhoneNumber", DisplayName = "phone number", ReadOnlyForUser = true });

                        // Add SettingPropertyQuery eventhandler
                        module.SettingPropertyQuery += this.settingPropertyQueryHandlerRef;
                        _settingModules.Add(module);
                    }
                    else
                    {
                        return null;
                    }
                }

                // Check whether Main phone settings query. If so, add VoipAccount to settings dynamically
                if (name == "Main")
                {
                    module.FireSettingsPropertyQuery = false;
                    if (module["VoIPAccount"] == null)
                    {
                        module.Add(new Setting { Name = "VoIPAccount", Value = "", Category = "VoIP", Description = "Access path: Main.VoIPAccount", DisplayName = "voip account", ReadOnlyForUser = true });
                    }
                    if (module["VoIPPassword"] == null)
                    {
                        module.Add(new Setting { Name = "VoIPPassword", Value = "", Category = "VoIP", Description = "Access path: Main.VoIPPassword", DisplayName = "voip password", ReadOnlyForUser = true });
                    }
                    module.FireSettingsPropertyQuery = true;
                }
                else if (name == "TestRun")
                {
                    module.FireSettingsPropertyQuery = false;
                    if (module["POXSIPRegistrarServerUri"] == null)
                    {
                        module.Add(new Setting { Name = "POXSIPRegistrarServerUri", Value = "", Category = "POX Backend", Description = "Server uri of POX SIP Registrar\nAccess path: TestRun.POXSIPRegistrarServerUri", DisplayName = "pox sip registrar uri", ReadOnlyForUser = true });
                    }
                    if (module["BackendAvailable"] == null)
                    {
                        module.Add(new Setting { Name = "BackendAvailable", Value = false, Category = "POX Backend", Description = "Indicates whether POX Backend is available for use.\nOn error situations this flag will be automatically set to false", DisplayName = "pox backend available", ReadOnlyForUser = true });
                    }
                    module.FireSettingsPropertyQuery = true;
                }
                // If there is more than one token
                if (tokens.Length > 1)
                {
                    // Get the setting value for the setting that has the name of the second token
                    var settingValue = module[tokens[1]];

                    if (settingValue == null)
                    {
                        return null;
                    }

                    // If only the session module name and setting name was supplied or more tokens were supplied and we do not have a dictionary
                    if (tokens.Length == 2 || !typeof(IDictionary).IsAssignableFrom(settingValue.GetType()))
                    {
                        return settingValue;
                    }

                    // Determine if this setting value is a dictionary
                    IDictionary dictionary = settingValue as IDictionary;

                    for (int i = 2; i < tokens.Length; i++)
                    {
                        if (dictionary.Contains(tokens[i]))
                        {
                            var value = dictionary[tokens[i]];

                            if (i == (tokens.Length - 1))
                            {
                                return Converters.ConvertToDynamic(value);
                            }

                            if (typeof(IDictionary).IsAssignableFrom(value.GetType()))
                            {
                                dictionary = value as IDictionary;
                            }
                            else
                            {
                                return null;
                            }
                        }
                        else
                        {
                            return null;
                        }
                    }

                }
                return module;
            }
        }

        /// <summary>
        /// Get the value of a setting using the setting category and display name.
        /// </summary>
        /// <param name="settingPath">Full setting path (e.g. 'SettingModuleName/Category/DisplayName').</param>
        /// <returns>Value of the setting.</returns>
        /// <remarks>This method is only provided for backwards compatibility with the original .settings file functionality.
        /// To access settings either using the dynamic functionality (e.g. <c>settingValue = SettingsManager.Instance.MySettings.SettingName</c>)
        /// or access the settings from the <see cref="SettingModules"/> property.</remarks>
        /// <returns>Value of the setting or <c>null</c> if the setting value could not be obtained.</returns>
        public object GetValue(string settingPath)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            if (string.IsNullOrEmpty(settingPath))
            {
                return null;
            }

            // Separate the tokens
            string[] tokens = settingPath.Split(new char[] { '\\', '/' }, StringSplitOptions.RemoveEmptyEntries);

            // Convert the first token to a valid setting module name
            string settingModuleName = GetSettingModuleNameFromGetValueToken(tokens[0]);

            // Find the setting module with the setting module name
            SettingModule module = _settingModules.Find(s => s.Name == settingModuleName);

            if (module == null)
            {
                return null;
            }

            // If there is more than one token
            if (tokens.Length > 1)
            {
                // If we only have a setting name or setting display name
                if (tokens.Length == 2)
                {
                    // Get the display name of the setting
                    string settingName = tokens[1];

                    // Get the setting with that display name if it has one, or if not use the name
                    Setting setting = module.SingleOrDefault(s => s.DisplayName == settingName || s.Name == settingName);

                    if (setting == null)
                    {
                        return null;
                    }

                    else
                    {
                        return setting.Value;
                    }
                }

                // Else we have a category and a setting name or display name
                else
                {

                    //TODO: Remove this on wk06
                    // Temporary support for old 'Account' named settings instead of 'SIM'
                    if (tokens[1].StartsWith("Account2"))
                        tokens[1] = tokens[1].Replace("Account2", "SIM2");
                    else if (tokens[1].StartsWith("Account"))
                        tokens[1] = tokens[1].Replace("Account", "SIM1");

                    // Get the category and display name of the setting
                    string settingCategory = tokens[1];
                    string settingName = tokens[2];

                    // Get the setting with that category and display name if it has one, or if not use the name
                    Setting setting = module.SingleOrDefault(s => s.Category == settingCategory && (s.DisplayName == settingName || s.Name == settingName));

                    if (setting == null)
                    {
                        return null;
                    }

                    else
                    {
                        return setting.Value;
                    }
                }
            }

            return module;
        }


        /// <summary>
        /// Constructs a setting module name from the first token used in the <see cref="GetValue"/>
        /// method that provides backwards compatibility with the old .settings file functionality.
        /// </summary>
        /// <param name="token">First token (i.e. root) of the settings path.</param>
        /// <returns>The token converted to a name that is compatible with the session module names.</returns>
        /// <example>This method would convert <c>"Test run"</c> to <c>"TestRun"</c>.</example>
        private static string GetSettingModuleNameFromGetValueToken(string token)
        {
            string settingModuleName = token;

            if (!string.IsNullOrEmpty(token))
            {
                // Trim the name
                settingModuleName = settingModuleName.Trim();

                // Determine the index of the first space
                int index = settingModuleName.IndexOf(' ');

                // While there is a space
                while (index >= 0)
                {
                    // Remove the space and capitalize the next word
                    settingModuleName = settingModuleName.Substring(0, index) +
                                        settingModuleName.Substring(index + 1, 1).ToUpper() +
                                        (index + 2 < settingModuleName.Length ? settingModuleName.Substring(index + 2) : string.Empty);

                    // Determine the index of the next space
                    index = settingModuleName.IndexOf(' ', index);
                }

                if (!string.IsNullOrEmpty(token))
                {
                    // Get the setting module class to remove any invalid characters
                    settingModuleName = SettingModule.GenerateSettingModuleName(settingModuleName);
                }
            }

            return settingModuleName;
        }

        /// <summary>
        /// Gets the setting value with the specified name.
        /// </summary>
        /// <param name="name">Name of the setting.</param>
        /// <returns>Value of the setting.</returns>
        internal object this[string name]
        {
            get
            {
                if (_disposed)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }

                return GetSettings(name);
            }
        }

        /// <summary>
        /// Gets the setting module at the specified index.
        /// </summary>
        /// <param name="index">Index in the settings module array.</param>
        /// <returns>Setting module.</returns>
        internal SettingModule this[int index]
        {
            get
            {
                if (_disposed)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }

                return _settingModules[index];
            }
        }

        /// <summary>
        /// Number of setting modules.
        /// </summary>
        internal int Count
        {
            get
            {
                return (_settingModules != null ? _settingModules.Count : 0);
            }
        }

        /// <summary>
        /// File system watches that are watching the directories.
        /// </summary>
        private List<FileSystemWatcher> Watchers
        {
            get
            {
                lock (_locker)
                {
                    return _watchers;
                }
            }
            set
            {
                lock (_locker)
                {
                    _watchers = value;
                }
            }
        }

        /// <summary>
        /// Adds a file system watcher for the specified directory.
        /// </summary>
        /// <param name="directory">Directory to add a file system watcher for.</param>
        /// <remarks>The file system watcher is only added if the directory exists and there is not already a
        /// file system watcher for this directory.</remarks>
        private void AddSettingsWatcher(DirectoryInfo directory)
        {
            if (directory.Exists)
            {
                // If we have not yet created the list of file system watches
                if (Watchers == null)
                {
                    // Create the list
                    Watchers = new List<FileSystemWatcher>();
                }

                // If we do not already have a file system watcher for this directory
                if (!Watchers.Exists(w => w.Path == directory.FullName))
                {
                    // Create a file system watcher to watch the directory
                    var watcher = new FileSystemWatcher(directory.FullName);
                    watcher.Created += new FileSystemEventHandler(OnSettingModuleChanged);
                    watcher.Deleted += new FileSystemEventHandler(OnSettingModuleChanged);
                    watcher.Changed += new FileSystemEventHandler(OnSettingModuleChanged);
                    watcher.Renamed += new RenamedEventHandler(OnSettingModuleRenamed);
                    watcher.EnableRaisingEvents = true;

                    // Add the new file system watcher to our list
                    Watchers.Add(watcher);
                }
            }
        }

#if SETTINGS_MANAGER_PROXY_ASSEMBLY_RESOLVER
        private Assembly AssemblyResolve(object sender, ResolveEventArgs args)
        {
            var location = Path.GetDirectoryName(GetType().Assembly.Location);

            var assembly = AppDomain.CurrentDomain.GetAssemblies().ToList().Find(a =>
            {
                return a.GetName().Name == args.Name;
            });

            if (assembly != null)
            {
                return assembly;
            }

            var assemblyFile = Directory.GetFiles(location).ToList().Find(file =>
            {
                return Path.GetFileNameWithoutExtension(file) == args.Name;
            });

            return assemblyFile != null ? Assembly.LoadFrom(assemblyFile) : null;
        }
#endif

        /// <summary>
        /// Called whenever a file or sub-directory in the directory being watched is renamed.
        /// </summary>
        /// <param name="sender">Sender of the event.</param>
        /// <param name="e">Arguments for the event.</param>
        private void OnSettingModuleRenamed(object sender, RenamedEventArgs e)
        {
            var oldFileExtension = Path.GetExtension(e.OldFullPath).ToLower();
            var newFileExtension = Path.GetExtension(e.FullPath).ToLower();

            if (oldFileExtension != newFileExtension)
            {
                return;
            }

            // Find the setting module for the original file name
            SettingModule setting = _settingModules.Find(s => s.SettingFilePath == e.OldFullPath);
            
            // If we have a setting module for this file
            if (setting != null)
            {
                // If the saved setting file path differs from the setting file path used to read the settings
                if (setting.SettingFilePath != setting.SavedSettingsFilePath)
                {
                    // If the save setting file path exists
                    if (File.Exists(setting.SavedSettingsFilePath))
                    {
                        try
                        {
                            // Rename the associated saved setting file path
                            File.Move(setting.SavedSettingsFilePath, Path.ChangeExtension(e.FullPath, Extensions.XML));
                        }
                        catch 
                        { 
                        }
                    }
                }

                // Get the original setting module name
                string oldName = setting.Name;

                // We are about to change the setting file path, which will also change the setting module
                // name. The collection of setting modules is internally using a dictionary with the setting 
                // module name as the key, therefore we need to remove the setting module from the collection
                // and then add it again once it has its new name.

                // Remove the setting module from the collection
                _settingModules.Remove(setting);

                // Update the setting file path which will also update the setting module name
                setting.SettingFilePath = e.FullPath;

                // Add the setting module to the collection again
                _settingModules.Add(setting);

                if (SettingModuleRenamed != null)
                {
                    // Raise an event that the setting module has been renamed
                    SettingModuleRenamed(new SettingModuleRenamedEventArgs(oldName, setting.Name));
                }
            }

            // Else we have no setting module for this file but if it is an XML file
            else if (oldFileExtension == Extensions.XML)
            {
                // If there is an associated IronPython file for the original XML name before it was renamed
                if (File.Exists(Path.ChangeExtension(e.OldFullPath, Extensions.PYTHON)))
                {
                    // Treat this XML file that was renamed as though it is a new file that has been created
                    OnSettingModuleChanged(null, new FileSystemEventArgs(WatcherChangeTypes.Created, Path.GetDirectoryName(e.FullPath), e.Name));
                }
            }
        }

        /// <summary>
        /// Called whenever a file or sub-directory in the directory being watched is added, changed or deleted.
        /// </summary>
        /// <param name="sender">Sender of the event.</param>
        /// <param name="e">Arguments for the event.</param>
        /// <remarks>When a new file is created we may receive an event that it has been created, but it may have only 
        /// been created and not all content may have been written to the file. We then later get a file changed event 
        /// after the file content is all written. The logic in this method must cater for this and treat the file 
        /// changed event as a file created event if we do not already have a section module for the file.</remarks>
        private void OnSettingModuleChanged(object sender, FileSystemEventArgs e)
        {
            // Ignore this event while we are busy saving
            if (IsSaving)
                return;

            // Get the file information for this change
            FileInfo file = new FileInfo(e.FullPath);

            // If the file has been created or has changed
            if (e.ChangeType != WatcherChangeTypes.Deleted || e.ChangeType == WatcherChangeTypes.Renamed)
            {
                if (!file.Exists || file.Length == 0)
                {
                    // Ignore the event if the file does not exist or is empty
                    return;
                }
            }

            // Store the type of change
            WatcherChangeTypes changeType = e.ChangeType;

            // Get the file extension for the file or directory
            string fileExtension = file.Extension.ToLower();

            // If the XML file has been added or updated
            if (fileExtension == Extensions.XML)
            {
#if SUPPORT_DEFAULT_SUBDIRECTORY
                // Construct the directory path for the special 'default' directory
                string defaultSubdirectory = Path.Combine(file.DirectoryName, _defaultDirectoryName);

                // Construct the file path for an associated IronPython file in the special 'default' directory
                string ironPythonFilePath = Path.ChangeExtension(Path.Combine(defaultSubdirectory, file.Name), Extensions.PYTHON);

                // If there is no IronPython file in the 'default' subdirectory
                if (!File.Exists(ironPythonFilePath))
                {
                    // Construct the file path for an associated IronPython file in the same directory
                    ironPythonFilePath = Path.ChangeExtension(file.FullName, Extensions.PYTHON);
                }
#else
                // Construct the file path for an associated IronPython file
                string ironPythonFilePath = Path.ChangeExtension(file.FullName, Extensions.PYTHON);
#endif

                // If there is an IronPython file
                if (File.Exists(ironPythonFilePath))
                {
                    // Use the IronPython file as the master and the code will automatically override the settings based on the xml file
                    file = new FileInfo(ironPythonFilePath);
                    fileExtension = file.Extension.ToLower();

                    if (!file.Exists || file.Length == 0)
                    {
                        // Ignore the event if the file does not exist or is empty
                        return;
                    }

                    // If we received this notification because the XML file was created or deleted
                    if (changeType == WatcherChangeTypes.Created || changeType == WatcherChangeTypes.Deleted)
                    {
                        // Treat this as a change since the settings have been changed
                        changeType = WatcherChangeTypes.Changed;
                    }
                }
            }

            // If a new file that has been created
            if (changeType == WatcherChangeTypes.Created)
            {
                // If it has a valid file extension
                if (fileExtension == Extensions.PYTHON || fileExtension == Extensions.JSON || fileExtension == Extensions.XML)
                {
                    // Create and add a new setting module for this setting file
                    Task.Factory.StartNew(() => LoadSettingsFromFile(file.FullName));
                }
            }

            // Else if the file has been changed
            else if (changeType == WatcherChangeTypes.Changed)
            {
                // If it has a valid file extension
                if (fileExtension == Extensions.PYTHON || fileExtension == Extensions.JSON || fileExtension == Extensions.XML)
                {
                    Task.Factory.StartNew(() =>
                        {
                            try
                            {
                                // Find the section module associated with this file
                                SettingModule module = _settingModules.Find(s => s.SettingFilePath == file.FullName);

                                // If there is a section module
                                if (module != null)
                                {
                                    // Construct a new setting module from the updated setting file
                                    SettingModule updated = SettingModule.GetSettingsByFileExtension(file.FullName);

                                    if (updated != null)
                                    {
                                        // Update the existing setting module with any changes and raise the events
                                        module.ReplaceBy(updated, SettingValueChanged, SettingAdded, SettingRemoved);
                                    }
                                }

                                // Else there is no section module
                                else
                                {
                                    // This file was most likely was created and then updated with its file contents
                                    LoadSettingsFromFile(file.FullName);
                                }
                            }
                            catch 
                            { 
                            }
                        });
                }
            }

            // Else if the file has been deleted
            else if (changeType == WatcherChangeTypes.Deleted)
            {
                // If it has a valid file extension
                if (fileExtension == Extensions.PYTHON || fileExtension == Extensions.JSON || fileExtension == Extensions.XML)
                {
                    // Find the setting module that has a matching setting file
                    SettingModule settings = _settingModules.Find(s => s.SettingFilePath == e.FullPath);

                    if (settings != null)
                    {
                        // If this setting module is for an IronPython file and it has an associated XML file
                        if (fileExtension == Extensions.PYTHON && 
                            File.Exists(settings.SavedSettingsFilePath))
                        {
                            try
                            {
                                // Delete the associated XML file
                                File.Delete(settings.SavedSettingsFilePath);
                            }
                            catch 
                            { 
                            }
                        }

                        // Remove the setting module
                        _settingModules.Remove(settings);

                        if (SettingModuleRemoved != null)
                        {
                            SettingModuleRemoved(new SettingModuleRemovedEventArgs(settings.Name));
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Flag that indicates whether the settings are being saved.
        /// </summary>
        private bool IsSaving
        {
            get;
            set;
        }
    }
}
