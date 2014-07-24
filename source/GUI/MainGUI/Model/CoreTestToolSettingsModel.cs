using System;
using System.Collections.Generic;
using System.Configuration;
using System.IO;
using System.Reflection;

namespace Marble.Model
{
    /// <summary>
    /// Class used to hold the information about the Core Test Tool an individual configuration setting section.
    /// </summary>
    public sealed class CoreTestToolSettingsSection
    {
        /// <summary>
        /// The initial XML for the configuration when it was loaded.
        /// </summary>
        private string _defaultSectionXml;

        /// <summary>
        /// Prevent an instance of this class from being created using the default constructor.
        /// </summary>
        private CoreTestToolSettingsSection()
        {
        }

        /// <summary>
        /// Creates a new <see cref="CoreTestToolSettingsSection"/> object.
        /// </summary>
        /// <param name="assemblyFilePath">File path of the Core Test Tool assembly that contains the test cases.</param>
        /// <param name="configurationFilePath">File path of the Core Test Tool configuration file.</param>
        /// <param name="sectionName">Name of the configuration section.</param>
        public CoreTestToolSettingsSection(string assemblyFilePath, string configurationFilePath, string sectionName)
        {
            // Set the initial values
            _defaultSectionXml = null;

            // Store the information
            AssemblyFilePath = assemblyFilePath;
            ConfigurationFilePath = configurationFilePath;
            SectionName = sectionName;
        }

        /// <summary>
        /// File path of the Core Test Tool assembly that contains the test cases.
        /// </summary>
        public string AssemblyFilePath
        {
            get;
            private set;
        }

        /// <summary>
        /// File path of the Core Test Tool configuration file.
        /// </summary>
        public string ConfigurationFilePath
        {
            get;
            private set;
        }

        /// <summary>
        /// Name of the configuration section.
        /// </summary>
        public string SectionName
        {
            get;
            private set;
        }

        /// <summary>
        /// Configuration section information for the assembly.
        /// </summary>
        public ConfigurationSection Section
        {
            get;
            private set;
        }

        /// <summary>
        /// Loads the configuration section information.
        /// </summary>
        public void Load()
        {
            // Load the configuration section
            Section = GetConfigurationSection();

            // Store the initial section XML
            _defaultSectionXml = GetSectionXml();
        }

        /// <summary>
        /// Flag that indicates whether a <see cref="Load"/> has been performed.
        /// </summary>
        public bool IsLoaded
        {
            get
            {
                return (Section != null);
            }
        }

        /// <summary>
        /// Flag that indicates whether the <see cref="Section"/> information has been changed after it was loaded.
        /// </summary>
        public bool IsDirty
        {
            get
            {
                // Get the current section XML information
                string sectionXml = GetSectionXml();

                // The information is dirty if it has been changed since it was loaded
                return (sectionXml != _defaultSectionXml);
            }
        }

        /// <summary>
        /// Gets the configuration section as a serialized XML string.
        /// </summary>
        /// <returns>Configuration section XML string.</returns>
        /// <remarks>The <see cref="Load"/> method should be called to load the configuration section 
        /// prior to calling this method.</remarks>
        public string GetSectionXml()
        {
            string sectionXml = null;

            if (Section != null)
            {
                MethodInfo methodInfo = Section.GetType().GetMethod("SerializeSection", BindingFlags.NonPublic | BindingFlags.Instance);
                if (methodInfo != null)
                {
                    sectionXml = methodInfo.Invoke(Section, new object[] { null, Section.GetType().Name, ConfigurationSaveMode.Full }) as string;
                }
            }

            return sectionXml;
        }

        /// <summary>
        /// Gets the configuration section.
        /// </summary>
        /// <returns><see cref="System.Configuration.ConfigurationSection"/> for the Core Test Tool assembly configuration section.</returns>
        private ConfigurationSection GetConfigurationSection()
        {
            ConfigurationSection settingsSection = null;

            // If the assembly file exists
            if (File.Exists(AssemblyFilePath))
            {
                // Add the assembly resolver
                AppDomain.CurrentDomain.AssemblyResolve += OnAssemblyResolve;

                try
                {
                    // Open the assembly configuration file
                    ExeConfigurationFileMap map = new ExeConfigurationFileMap() { ExeConfigFilename = ConfigurationFilePath };
                    Configuration configuration = ConfigurationManager.OpenMappedExeConfiguration(map, ConfigurationUserLevel.None);

                    foreach (ConfigurationSection section in configuration.Sections)
                    {
                        // If this matches the required section name
                        if (section.SectionInformation.Name == SectionName)
                        {
                            // Use this section
                            settingsSection = section;
                            break;
                        }
                    }
                }

                finally
                {
                    // Remove the assembly resolver
                    AppDomain.CurrentDomain.AssemblyResolve -= OnAssemblyResolve;
                }
            }

            return settingsSection;
        }

        /// <summary>
        /// Called when CLR probing failed to find the assembly and we are trying to resolve the assembly.
        /// </summary>
        /// <returns>Assembly that has been loaded, or <c>null</c> if the assembly was not found.</returns>
        private System.Reflection.Assembly OnAssemblyResolve(object sender, ResolveEventArgs args)
        {
            System.Reflection.Assembly assembly = null;

            // Get the friendly name of the assembly
            string friendlyName = args.Name.Split(',')[0];

            string assemblyDirectoryPath = Path.GetDirectoryName(AssemblyFilePath);

            if (!string.IsNullOrEmpty(assemblyDirectoryPath))
            {
                // Construct the assembly file path
                string assemblyFilePath = System.IO.Path.Combine(assemblyDirectoryPath, friendlyName + ".dll");

                if (File.Exists(assemblyFilePath))
                {
                    // Load the assembly
                    assembly = System.Reflection.Assembly.LoadFrom(assemblyFilePath);
                }
            }

            return assembly;
        }
    }

    /// <summary>
    /// Model for the Core Test Tool settings.
    /// </summary>
    public sealed class CoreTestToolSettingsModel
    {
        /// <summary>
        /// List of Core Test Tool setting sections.
        /// </summary>
        private List<CoreTestToolSettingsSection> _settingSections;

        /// <summary>
        /// Prevent an instance of this class from being created using the default constructor.
        /// </summary>
        private CoreTestToolSettingsModel()
        {
        }

        /// <summary>
        /// Private constructor that allows the list of Core Test Tool settings sections to be specified.
        /// </summary>
        /// <param name="settingSections">List of Core Test Tool setting sections.</param>
        private CoreTestToolSettingsModel(List<CoreTestToolSettingsSection> settingSections)
        {
            // Store the setting sections
            _settingSections = settingSections;
        }

        /// <summary>
        /// Creates a new <see cref="CoreTestToolSettingsModel"/> from the supplied arguments.
        /// </summary>
        /// <param name="assemblyFilePaths">Array of assembly file paths.</param>
        /// <param name="configurationFilePaths">Array of configuration file paths.</param>
        /// <param name="sectionNames">Array of section names.</param>
        /// <returns></returns>
        /// <exception cref="ArgumentNullException">Thrown if any of the arguments are <c>null</c>.</exception>
        /// <exception cref="ArgumentException">Thrown if the supplied array arguments do have the same lengths.</exception>
        public static CoreTestToolSettingsModel Create(string[] assemblyFilePaths, string[] configurationFilePaths, string[] sectionNames)
        {
            #region Check parameters

            if (assemblyFilePaths == null)
            {
                throw new ArgumentNullException("assemblyFilePaths", "No assembly files paths have been specified.");
            }

            if (configurationFilePaths == null)
            {
                throw new ArgumentNullException("configurationFilePaths", "No configuration files paths have been specified.");
            }

            if (sectionNames == null)
            {
                throw new ArgumentNullException("sectionNames", "No section names have been specified.");
            }

            if (assemblyFilePaths.Length != configurationFilePaths.Length ||
                configurationFilePaths.Length != sectionNames.Length)
            {
                throw new ArgumentException("The number of assembly file paths, configuration file paths and section names do not match.");
            }

            #endregion

            List<CoreTestToolSettingsSection> settingSections = new List<CoreTestToolSettingsSection>();

            for (int i = 0; i < assemblyFilePaths.Length; i++)
            {
                settingSections.Add(new CoreTestToolSettingsSection(assemblyFilePaths[i], configurationFilePaths[i], sectionNames[i]));
            }

            // Create the model
            CoreTestToolSettingsModel model = new CoreTestToolSettingsModel(settingSections);

            return model;
        }

        /// <summary>
        /// Enumerator to iterate through the Core Test Tool setting sections.
        /// </summary>
        public IEnumerable<CoreTestToolSettingsSection> SettingsSections
        {
            get
            {
                return _settingSections;
            }
        }
    }
}
