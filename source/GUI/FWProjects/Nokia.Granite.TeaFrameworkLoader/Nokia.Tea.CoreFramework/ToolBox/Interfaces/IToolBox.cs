using System;
using System.Globalization;
using Nokia.Tea.CoreFramework.BaseModules.TeaServiceModule;
using Nokia.Tea.CoreFramework.ModuleServices.Implementations;

namespace Nokia.Tea.CoreFramework.ToolBox.Interfaces
{
    /// <summary>
    /// Interface for ToolBox usage
    /// </summary>
    public interface IToolBox
    {
        /// <summary>
        /// Gets culture information. 
        /// </summary>
        CultureInfo Culture { get; }

        /// <summary>
        /// Gets or sets the module service.
        /// </summary>
        /// <value>The module service.</value>
        ModuleService ModuleService { get; set; }

        /// <summary>
        /// Returns module object according to given unique module identification string.
        /// </summary>
        /// <param name="moduleId">The unique module identifiation string</param>
        /// <param name="requestorType">The type of requestor module</param>
        /// <returns>Handle to the module.</returns>
        object Get(string moduleId, Type requestorType);

        /// <summary>
        /// Adds services.
        /// </summary>
        /// <param name="serviceIdentifier">The service Identifier.</param>
        /// <param name="service">The service.</param>
        void Add(CoreServiceModuleKeys serviceIdentifier, object service);
    }
}
