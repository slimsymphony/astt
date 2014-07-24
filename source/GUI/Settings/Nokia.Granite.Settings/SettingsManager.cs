using System;
using System.Collections;
using System.Dynamic;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;
using System.Threading.Tasks;

namespace TestAutomation.Gui.Marble.Settings
{
    /// <summary>
    /// Class that provides a Singleton instance used to access and manage all settings.
    /// </summary>
    [Serializable()]
    public sealed class SettingsManager : IDynamicMetaObjectProvider, IDisposable, IEnumerable
    {
        /// <summary>
        /// Singleton instance of this class that is created when accessed. 
        /// </summary>
        /// <remarks><para>Uses a lambda expression to construct since the constructor is private.</para>
        /// <para>This code guarantees thread-safe lazy-construction.</para></remarks>
        private static readonly Lazy<SettingsManager> _instance = new Lazy<SettingsManager>(() => new SettingsManager());

        /// <summary>
        /// Proxy used to perform the actions.
        /// </summary>
        private SettingsManagerProxy _proxy;

        /// <summary>
        /// Flag that indicates whether this object has been disposed.
        /// </summary>
        private bool _disposed;

        /// <summary>
        /// Flag that overrides normal behaviour so that we can perform all unit tests from a child unit test AppDomain as though we were executing from the main AppDomain.
        /// </summary>
        private bool _unitTesting;

        /// <summary>
        /// Prevent an instance of this class from being created externally.
        /// </summary>
        private SettingsManager()
        {
            // Create the proxy
            _proxy = new SettingsManagerProxy();
        }

        /// <summary>
        /// Destructor.
        /// </summary>
        ~SettingsManager()
        {
            // Dispose of this object
            Dispose(false);
        }

        /// <summary>
        /// Returns the single instance of the <see cref="SettingsManager"/>.
        /// </summary>
        public static SettingsManager Instance
        {
            get
            {
                return _instance.Value;
            }
        }

        /// <summary>
        /// Event for when a setting module has been added.
        /// </summary>
        public event SettingModuleAddedEventHandler SettingModuleAdded
        {
            add
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingModuleAdded += value;
            }
            remove
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingModuleAdded -= value;
            }
        }

        /// <summary>
        /// Event for when a setting module is removed.
        /// </summary>
        public event SettingModuleRemovedEventHandler SettingModuleRemoved
        {
            add
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingModuleRemoved += value;
            }
            remove
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingModuleRemoved -= value;
            }
        }

        /// <summary>
        /// Event for when a setting module is renamed.
        /// </summary>
        public event SettingModuleRenamedEventHandler SettingModuleRenamed
        {
            add
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingModuleRenamed += value;
            }
            remove
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingModuleRenamed -= value;
            }
        }

        /// <summary>
        /// Event for when a setting value has been changed.
        /// </summary>
        public event SettingPropertyChangedEventHandler SettingValueChanged
        {
            add
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingValueChanged += value;
            }
            remove
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingValueChanged -= value;
            }
        }

        /// <summary>
        /// Event for when a setting has been added.
        /// </summary>
        public event SettingAddedEventHandler SettingAdded
        {
            add
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingAdded += value;
            }
            remove
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingAdded -= value;
            }
        }

        /// <summary>
        /// Event for when a setting has been removed.
        /// </summary>
        public event SettingRemovedEventHandler SettingRemoved
        {
            add
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingRemoved += value;
            }
            remove
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingRemoved -= value;
            }
        }

        /// <summary>
        /// Event for indicating when a setting value query occurs.
        /// </summary>
        public event SettingPropertyQueryEventHandler SettingPropertyQuery
        {
            add
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingPropertyQuery += value;
            }
            remove
            {
                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                    _proxy.SettingPropertyQuery -= value;
            }
        }

        /// <summary>
        /// Collection of setting modules.
        /// </summary>
        public SettingModuleCollection SettingModules
        {
            get
            {
                if (_disposed)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }

                return _proxy.SettingModules;
            }
        }

        /// <summary>
        /// Number of setting modules.
        /// </summary>
        public int Count
        {
            get
            {
                return (_proxy != null ? _proxy.Count : 0);
            }
        }

        /// <summary>
        /// Get the value of a setting.
        /// </summary>
        /// <param name="name">Name of the setting.</param>
        /// <returns>Value of the setting or <c>null</c> if the setting value could not be obtained.</returns>
        public object GetSettings(string name)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            return _proxy.GetSettings(name);
        }

        /// <summary>
        /// Get the value of a setting using the setting category and display name.
        /// </summary>
        /// <param name="settingPath">Full setting path (e.g. 'SettingModuleName/Category/DisplayName').</param>
        /// <returns>Value of the setting.</returns>
        /// <remarks><para>This method is only provided for backwards compatibility with the original .settings file functionality.
        /// To access settings either using the dynamic functionality (e.g. <c>settingValue = SettingsManager.Instance.MySettings.SettingName</c>)
        /// or access the settings from the <see cref="SettingModules"/> property.</para>
        /// <para>This method name is the same as the IronPython method name used in the SettingsModel class.</para></remarks>
        /// <returns>Value of the setting or <c>null</c> if the setting value could not be obtained.</returns>
        public object getValue(string settingPath)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            return _proxy.GetValue(settingPath);
        }

        /// <summary>
        /// Synchronously loads all of the settings files in a directory.
        /// </summary>
        /// <param name="directory">Directory where the settings file are located.</param>
        /// <param name="includeSubdirectories">Flag to indicate whether to include settings files in sub-directories.</param>
        public void LoadSettingsFromDirectory(string directory, bool includeSubdirectories = false)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
            {
                _proxy.LoadSettingsFromDirectory(directory, includeSubdirectories);
            }
        }

        /// <summary>
        /// Asynchronously loads all of the settings files in a directory.
        /// </summary>
        /// <param name="directory">Directory where the settings file are located.</param>
        /// <param name="includeSubdirectories">Flag to indicate whether to include settings files in sub-directories.</param>
        public Task BeginLoadSettingsFromDirectory(string directory, bool includeSubdirectories = false)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            return Task.Factory.StartNew(() =>
                {
                    LoadSettingsFromDirectory(directory, includeSubdirectories);
                });
        }

        /// <summary>
        /// Synchronously loads all the settings from a settings files.
        /// </summary>
        /// <param name="filePath">File path to the settings file.</param>
        public void LoadSettingsFromFile(string filePath)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
            {
                _proxy.LoadSettingsFromFile(filePath);
            }
        }

        /// <summary>
        /// Asynchronously loads all the settings from a settings files.
        /// </summary>
        /// <param name="filePath">File path to the settings file.</param>
        public Task BeginLoadSettingsFromFile(string filePath)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            return Task.Factory.StartNew(() =>
                {
                    LoadSettingsFromFile(filePath);
                });
        }

        /// <summary>
        /// Synchronously saves all of the settings.
        /// </summary>
        public void SaveAll()
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
            {
                _proxy.SaveAll();
            }
        }

        /// <summary>
        /// Synchronously saves the setting module with the specified name.
        /// </summary>
        /// <param name="name">Name of the setting module.</param>
        public void Save(string name)
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
            {
                _proxy.Save(name);
            }
        }

        /// <summary>
        /// Asynchronously saves all of the settings.
        /// </summary>
        public Task BeginSaveAll()
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            return Task.Factory.StartNew(() =>
                {
                    SaveAll();
                });
        }

        /// <summary>
        /// Synchronously sets cancel values to all settings.
        /// </summary>
        public void SetCancelValuesToAll()
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
            {
                _proxy.SetCancelValuesToAll();
            }
        }

        /// <summary>
        /// Synchronously cancels all changes made for all of the settings.
        /// </summary>
        public void CancelAll()
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().FullName);
            }

            if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
            {
                _proxy.CancelAll();
            }
        }

        /// <summary>
        /// Gets the setting value with the specified name.
        /// </summary>
        /// <param name="name">Name of the setting.</param>
        /// <returns>Value of the setting.</returns>
        public object this[string name]
        {
            get
            {
                if (_disposed)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }

                return _proxy[name];
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

            return _proxy.GetEnumerator();
        }

        /// <summary>
        /// Disposes of this object.
        /// </summary>
        /// <remarks>This object should not be used again after calling this method. If you instead want to clear out all
        /// settings that were loaded and reset the object to its initial state then call <see cref="Reset"/> instead of 
        /// <see cref="Dispose"/>.</remarks>
        public void Dispose()
        {
            if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
            {
                Dispose(true);
                GC.SuppressFinalize(this);
            }
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
                    // Dispose of managed resources

                    if (_proxy != null)
                    {
                        // Dispose of the proxy
                        _proxy.Dispose();
                        _proxy = null;
                    }
                }

                // We have disposed of this object
                _disposed = true;
            }
        }

        /// <summary>
        /// Resets this this object back to its initial state.
        /// </summary>
        /// <remarks>Calling this method will get rid of all settings that have previously been loaded.</remarks>
        public void Reset()
        {
            if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
            {
                if (_proxy != null)
                {
                    // Dispose of the proxy
                    _proxy.Dispose();
                    _proxy = null;
                }

                // Create the proxy
                _proxy = new SettingsManagerProxy();

                // Set the flag to indicate whether we are unit testing
                _proxy.UnitTesting = UnitTesting;

                if (UnitTesting && _disposed)
                {
                    // Allow us to re-use the object when unit testing
                    _disposed = false;
                }

                // Reset the flag to indicate whether we are providing read-only settings
                ReadOnly = true;
            }
        }

        /// <summary>
        /// Flag that indicates whether setting values are read-only or whether they can be changed.
        /// </summary>
        public bool ReadOnly
        {
            get
            {
                if (_disposed)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }

                return _proxy.ReadOnly;
            }

            set
            {
                if (_disposed)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }

                if (AppDomain.CurrentDomain.IsDefaultAppDomain() || UnitTesting)
                {
                    _proxy.ReadOnly = value;
                }
            }
        }

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

                    if (_proxy != null)
                    {
                        // Update the proxy
                        _proxy.UnitTesting = _unitTesting;
                    }
                }
            }
        }

        #region IDynamicMetaObjectProvider Members

        /// <summary>
        /// Nested class representing the dynamic binding and binding logic.
        /// </summary>
        private class SettingsManagerMetaObject : DynamicMetaObject
        {
            /// <summary>
            /// Prevent an instance of the class from being created externally.
            /// </summary>
            /// <param name="expression">The expression representing this <see cref="SettingsManagerMetaObject"/> during the dynamic binding process.</param>
            /// <param name="value">The runtime value represented by the <see cref="SettingsManagerMetaObject"/>.</param>
            internal SettingsManagerMetaObject(System.Linq.Expressions.Expression expression,
                SettingsManager value)
                : base(expression, BindingRestrictions.Empty, value)
            {
            }

            /// <summary>
            /// Performs the binding of the dynamic get member operation.
            /// </summary>
            /// <param name="binder">An instance of the <see cref="System.Dynamic.GetMemberBinder"/> that represents the details of the dynamic operation.</param>
            /// <returns>The new <see cref="System.Dynamic.DynamicMetaObject"/> representing the result of the binding.</returns>
            public override DynamicMetaObject BindGetMember(GetMemberBinder binder)
            {
                // Get the methods
                MethodInfo[] methods = typeof(SettingsManager).GetMethods();

                // Get the properties
                PropertyInfo[] properties = typeof(SettingsManager).GetProperties();

                // Get the fields
                FieldInfo[] fields = typeof(SettingsManager).GetFields();

                // If this is not the name of a public method or the name of a property with a public get or set or a public field
                if (methods.FirstOrDefault(m => (m.Name == binder.Name) &&
                                                ((m.Attributes & MethodAttributes.Public) == MethodAttributes.Public)) == null &&
                    properties.FirstOrDefault(p => (p.Name == binder.Name) &&
                                                   ((p.GetGetMethod() != null && (p.GetGetMethod().Attributes & MethodAttributes.Public) == MethodAttributes.Public) ||
                                                   ((p.GetSetMethod() != null && (p.GetSetMethod().Attributes & MethodAttributes.Public) == MethodAttributes.Public)))) == null &&
                    fields.FirstOrDefault(f => (f.Name == binder.Name && 
                                               ((f.Attributes & FieldAttributes.Public) == FieldAttributes.Public))) == null)
                {
                    // Assume the name being called is the name of the setting module therefore use the method to get the setting module
                    string methodName = "GetSettings";

                    // Specify the name of the setting module as the parameter
                    Expression[] parameters = new Expression[]
                    {
                        Expression.Constant(binder.Name)
                    };

                    // Create the dynamic binding and a binding logic to get the setting module
                    DynamicMetaObject getDictionaryEntry = new DynamicMetaObject(
                        Expression.Call(
                            Expression.Convert(Expression, LimitType),
                            typeof(SettingsManager).GetMethod(methodName),
                            parameters),
                        BindingRestrictions.GetTypeRestriction(Expression, LimitType));

                    return getDictionaryEntry;
                }

                // Else this is the name of a public method, property or field
                else
                {
                    // There is no need to dynamically bind this to a different method
                    return base.BindGetMember(binder);
                }
            }
        }

        /// <summary>
        /// Returns the <see cref="System.Dynamic.DynamicMetaObject"/> responsible for binding operations performed on this object.
        /// </summary>
        /// <param name="parameter">The expression tree representation of the runtime value.</param>
        /// <returns>The <see cref="System.Dynamic.DynamicMetaObject"/> to bind this object.</returns>
        public DynamicMetaObject GetMetaObject(Expression parameter)
        {
            // Create a new setting manager meta object for the binding
            return new SettingsManagerMetaObject(parameter, this);
        }

        #endregion
    }
}
