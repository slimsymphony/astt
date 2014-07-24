using System;
using System.Runtime.Serialization;
using Nokia.Tea.CoreFramework.ToolBox.Interfaces;

// ReSharper disable CheckNamespace
namespace Nokia.Tea.CoreFramework.BaseModules.LowLevelDrivers
// ReSharper restore CheckNamespace
{
    /// <summary>
    /// TeaModule inherited base class for all low level driver modules.
    /// </summary>
    public class LowLevelDriverModule : TeaModule
    {
        /// <summary>
        /// Configuration class id suffix.
        /// </summary>
        private const string conf = "Configuration";

        #region Constructors

        /// <summary>
        /// Initializes a new instance of the <see cref="LowLevelDriverModule"/> class.
        /// </summary>
        /// <param name="moduleId">The module id.</param>
        /// <param name="toolBox">The tool Box.</param>
        public LowLevelDriverModule(string moduleId, IToolBox toolBox)
            : base(moduleId, toolBox)
        {
        }


        #endregion

        /// <summary>
        /// Gets the configuration class module.
        /// </summary>
        /// <returns>Configuration</returns>
        protected object GetConfiguration()
        {
            return base.ToolBox.Get(base.ModuleId + conf, this.GetType());
        }
    }
}