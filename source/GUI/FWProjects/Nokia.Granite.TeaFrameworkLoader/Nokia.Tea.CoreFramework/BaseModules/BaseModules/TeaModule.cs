using System;
using Nokia.Tea.CoreFramework.BaseModules.TeaCoreModule;
using Nokia.Tea.CoreFramework.ToolBox.Interfaces;

// ReSharper disable CheckNamespace
namespace Nokia.Tea.CoreFramework.BaseModules
// ReSharper restore CheckNamespace
{
    /// <summary>
    /// A base module for all RCMs, Drivers, Low Level Drivers, Steps and Utilities.
    /// </summary>
    public class TeaModule : TeaBase
    {
        #region Constructors

        /// <summary>
        /// The suffix when configuration is fetched.
        /// </summary>
        private const string conf = "Configuration";

        /// <summary>
        /// Initializes a new instance of the <see cref="TeaModule"/> class.
        /// </summary>
        /// <param name="moduleId">The module id.</param>
        /// <param name="toolBox">The tool box.</param>
        public TeaModule(string moduleId, IToolBox toolBox)
            : base(toolBox)
        {
            this.ModuleId = moduleId;
            SimulationMode = false;
        }

        #endregion

        #region Accessors
       
        /// <summary>
        /// Gets or sets ModuleId. A Unified Identifier that maps the module specific 
        /// configuration with the module configuration class. Get is public so that 
        /// test system can collect module information to end user
        /// if needed.
        /// </summary>
        /// <value>The module id.</value>
        public string ModuleId { get; protected set; }

        #endregion

        /// <summary>
        /// Gets or sets Name.
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether simulation mode is on.
        /// </summary>
        /// <value>
        ///   <c>true</c> if simulation mode; otherwise, <c>false</c>.
        /// </value>
        public static bool SimulationMode { get; set; }

        #region Protected methods

        /// <summary>
        /// Returns queried module object.
        /// </summary>
        /// <param name="moduleName">The module name.</param>
        /// <returns>Object of module.</returns>
        /// <exception cref="ArgumentException">If module is not found from configurations.</exception>
        protected object GetModule(string moduleName)
        {
            return base.ToolBox.Get(moduleName, this.GetType());
        }
       
        /// <summary>
        /// Saves the configuration (configuration class) back to Configuration Service.
        /// </summary>
        protected void SaveConfiguration()
        {
        }

        /// <summary>
        /// Saves the configuration back to Configuration Service.
        /// </summary>
        /// <param name="obj">The class object to be saved to configuration service.</param>
        protected void SaveConfiguration(object obj)
        {
        }

        #endregion
    }
}