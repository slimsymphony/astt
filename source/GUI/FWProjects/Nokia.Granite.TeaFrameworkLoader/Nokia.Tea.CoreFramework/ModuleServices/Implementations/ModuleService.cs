using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using Nokia.Tea.CoreFramework.BaseModules.TeaServiceModule;
using Nokia.Tea.CoreFramework.ModuleServices.Interfaces;
using Nokia.Tea.CoreFramework.ToolBox.Interfaces;

namespace Nokia.Tea.CoreFramework.ModuleServices.Implementations
{
    /// <summary>
    /// Module service class for accessing the system modules
    /// and to provide the UI the means to access the modules by type.
    /// </summary>
    public class ModuleService : TeaService, IModuleService
    {
        private readonly object lockObject = new object();

        /// <summary>
        /// Initializes a new instance of the <see cref="ModuleService"/> class.
        /// </summary>
        /// <param name="toolBox">The tool Box.</param>
        public ModuleService(IToolBox toolBox) 
            : base(toolBox)
        {
            Modules = new ConcurrentDictionary<string, object>();
            ModulesList = new List<String>();
        }

        #region IModuleService Members

        /// <summary>
        /// Gets or sets Modules. This is the main dictionary that could be used to store
        /// all the TeaModules.
        /// </summary>
        public ConcurrentDictionary<string, object> Modules { get; set; }

        /// <summary>
        /// Get list of items in Modules dictionary. List is sorted by add order.
        /// </summary>
        public List<string> ModulesList { get; set; }

        /// <summary>
        /// Add's new module to module service.
        /// </summary>
        /// <param name="uid">
        /// The uid of module.
        /// </param>
        /// <param name="module">
        /// The module be added.
        /// </param>
        /// <exception cref="ArgumentException">
        /// </exception>
        public void AddModule(string uid, object module)
        {
            lock (lockObject)
            {
                if (Modules.ContainsKey(uid) == false)
                {
                    Modules.TryAdd(uid, module);
                    ModulesList.Add(uid);
                }
                else
                {
                    throw new ArgumentException(
                        "ModuleService.AddModule(): Module with same identifier already exists in the module storage.");
                }
            }
        }

        #endregion
    }
}