using System;

namespace TestAutomation.Gui.Marble.Settings
{
    /// <summary>
    /// Delegate for when a setting module is added.
    /// </summary>
    /// <param name="args">Arguments for the event.</param>
    public delegate void SettingModuleAddedEventHandler(SettingModuleAddedEventArgs args);

    /// <summary>
    /// Delegate for when a setting module is removed.
    /// </summary>
    /// <param name="args">Arguments for the event.</param>
    public delegate void SettingModuleRemovedEventHandler(SettingModuleRemovedEventArgs args);

    /// <summary>
    /// Delegate for when a setting module is renamed.
    /// </summary>
    /// <param name="args">Arguments for the event.</param>
    public delegate void SettingModuleRenamedEventHandler(SettingModuleRenamedEventArgs args);

    /// <summary>
    /// Delegate for when a setting is added.
    /// </summary>
    /// <param name="args">Arguments for the event.</param>
    public delegate void SettingAddedEventHandler(SettingAddedEventArgs args);

    /// <summary>
    /// Delegate for when a setting is removed.
    /// </summary>
    /// <param name="args">Arguments for the event.</param>
    public delegate void SettingRemovedEventHandler(SettingRemovedEventArgs args);

    /// <summary>
    /// Delegate for when a setting property has changed.
    /// </summary>
    /// <param name="args">Arguments for the event.</param>
    public delegate void SettingPropertyChangedEventHandler(SettingPropertyChangedEventArgs args);

    /// <summary>
    /// Delegate for indicating when a setting property query occurs.
    /// </summary>
    /// <param name="args">Arguments for the event.</param>
    public delegate void SettingPropertyQueryEventHandler(SettingPropertyQueryEventArgs args);

    /// <summary>
    /// Event arguments containing information about the setting property that has changed.
    /// </summary>
    [Serializable()]
    public class SettingPropertyChangedEventArgs : EventArgs
    {
        /// <summary>
        /// Creates a new <see cref="SettingPropertyChangedEventArgs"/> object.
        /// </summary>
        /// <param name="settingModuleName">Name of the setting module.</param>
        /// <param name="settingName">Name of the setting.</param>
        /// <param name="oldValue">Original value of the setting.</param>
        /// <param name="newValue">New value of the setting.</param>
        internal SettingPropertyChangedEventArgs(string settingModuleName, string settingName,
            object oldValue, object newValue)
        {
            // Store the values
            SettingModuleName = settingModuleName;
            SettingName = settingName;
            OldValue = oldValue;
            NewValue = newValue;
        }

        /// <summary>
        /// Name of the setting module.
        /// </summary>
        public string SettingModuleName
        {
            get;
            private set;
        }

        /// <summary>
        /// Name of the setting.
        /// </summary>
        public string SettingName
        {
            get;
            private set;
        }

        /// <summary>
        /// Original value of the setting.
        /// </summary>
        public object OldValue
        {
            get;
            private set;
        }

        /// <summary>
        /// New value of the setting.
        /// </summary>
        public object NewValue
        {
            get;
            private set;
        }
    }

    /// <summary>
    /// Event arguments containing information about the setting property that has been added.
    /// </summary>
    [Serializable()]
    public class SettingAddedEventArgs : EventArgs
    {
        /// <summary>
        /// Creates a new <see cref="SettingAddedEventArgs"/> object.
        /// </summary>
        /// <param name="settingModuleName">Name of the setting module.</param>
        /// <param name="settingName">Name of the setting.</param>
        internal SettingAddedEventArgs(string settingModuleName, string settingName)
        {
            SettingModuleName = settingModuleName;
            SettingName = settingName;
        }

        /// <summary>
        /// Name of the setting module.
        /// </summary>
        public string SettingModuleName
        {
            get;
            private set;
        }

        /// <summary>
        /// Name of the setting.
        /// </summary>
        public string SettingName
        {
            get;
            private set;
        }
    }

    /// <summary>
    /// Event arguments containing information about the setting property that has been removed.
    /// </summary>
    [Serializable()]
    public class SettingRemovedEventArgs : EventArgs
    {
        /// <summary>
        /// Creates a new <see cref="SettingRemovedEventArgs"/> object.
        /// </summary>
        /// <param name="settingModuleName">Name of the setting module.</param>
        /// <param name="settingName">Name of the setting.</param>
        internal SettingRemovedEventArgs(string settingModuleName, string settingName)
        {
            SettingModuleName = settingModuleName;
            SettingName = settingName;
        }

        /// <summary>
        /// Name of the setting module.
        /// </summary>
        public string SettingModuleName
        {
            get;
            private set;
        }

        /// <summary>
        /// Name of the setting.
        /// </summary>
        public string SettingName
        {
            get;
            private set;
        }
    }

    /// <summary>
    /// Event arguments containing information about the setting module that has been added.
    /// </summary>
    [Serializable()]
    public class SettingModuleAddedEventArgs : EventArgs
    {
        /// <summary>
        /// Creates a new <see cref="SettingModuleAddedEventArgs"/> object.
        /// </summary>
        /// <param name="settingModuleName">Name of the setting module.</param>
        /// <param name="filePath">File path for the setting module.</param>
        internal SettingModuleAddedEventArgs(string settingModuleName, string filePath)
        {
            SettingModuleName = settingModuleName;
            FilePath = filePath;
        }

        /// <summary>
        /// Name of the setting module.
        /// </summary>
        public string SettingModuleName
        {
            get;
            private set;
        }

        /// <summary>
        /// File path for the setting module.
        /// </summary>
        public string FilePath
        {
            get;
            private set;
        }
    }

    /// <summary>
    /// Event arguments containing information about the setting module that has been removed.
    /// </summary>
    [Serializable()]
    public class SettingModuleRemovedEventArgs : EventArgs
    {
        /// <summary>
        /// Creates a new <see cref="SettingModuleRemovedEventArgs"/> object.
        /// </summary>
        /// <param name="settingModuleName">Name of the setting module.</param>
        internal SettingModuleRemovedEventArgs(string settingModuleName)
        {
            SettingModuleName = settingModuleName;
        }

        /// <summary>
        /// Name of the setting module.
        /// </summary>
        public string SettingModuleName
        {
            get;
            private set;
        }
    }

    /// <summary>
    /// Event arguments containing information about the setting module that has been renamed.
    /// </summary>
    [Serializable()]
    public class SettingModuleRenamedEventArgs : EventArgs
    {
        /// <summary>
        /// Creates a new <see cref="SettingModuleRenamedEventArgs"/> object.
        /// </summary>
        /// <param name="oldName">Original name of the setting module.</param>
        /// <param name="newName">New name of the setting module.</param>
        internal SettingModuleRenamedEventArgs(string oldName, string newName)
        {
            OldName = oldName;
            NewName = newName;
        }

        /// <summary>
        /// Original name of the setting module.
        /// </summary>
        public string OldName
        {
            get;
            private set;
        }

        /// <summary>
        /// New name of the setting module.
        /// </summary>
        public string NewName
        {
            get;
            private set;
        }
    }

    /// <summary>
    /// Event arguments for indicating about a setting value query.
    /// </summary>
    [Serializable()]
    public class SettingPropertyQueryEventArgs : SettingPropertyChangedEventArgs
    {
        /// <summary>
        /// Creates a new <see cref="SettingPropertyChangedEventArgs"/> object.
        /// </summary>
        /// <param name="settingModuleName">Name of the setting module.</param>
        /// <param name="settingName">Name of the setting.</param>
        /// <param name="oldValue">Original value of the setting.</param>
        /// <param name="newValue">New value of the setting.</param>
        internal SettingPropertyQueryEventArgs(string settingModuleName, string settingName, object oldValue, object newValue) : base(settingModuleName, settingName, oldValue, newValue)
        {
        }

        /// <summary>
        /// New value of the setting.
        /// </summary>
        public object NewValue
        {
            get;
            set;
        }
    }
}
