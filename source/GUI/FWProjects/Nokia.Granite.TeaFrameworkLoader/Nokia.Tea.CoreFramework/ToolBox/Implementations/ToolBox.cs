using System;
using System.Collections.Concurrent;
using System.Globalization;
using Nokia.Tea.CoreFramework.BaseModules.TeaCoreModule;
using Nokia.Tea.CoreFramework.BaseModules.TeaServiceModule;
using Nokia.Tea.CoreFramework.ModuleServices.Implementations;
using Nokia.Tea.CoreFramework.ToolBox.Interfaces;

namespace Nokia.Tea.CoreFramework.ToolBox.Implementations
{
    /// <summary>
    /// The toolbox class is used to give modules all needed tools. E.g. gets module according to ID.
    /// </summary>
    public sealed class ToolBox : IToolBox
    {
        /// <summary>
        /// Configuration string
        /// </summary>
        private const string configurationString = "Configuration";

        /// <summary>
        /// Culture settings to be used in system.
        /// </summary>
        private static readonly TeaGlobalization cultureInfo = new TeaGlobalization();

        /// <summary>
        /// Stores all services into this dictionary.
        /// </summary>
        private readonly ConcurrentDictionary<CoreServiceModuleKeys, object> services;

        /// <summary>
        /// Contruct toolBox object 
        /// </summary>
        public ToolBox()
        {
            this.services = new ConcurrentDictionary<CoreServiceModuleKeys, object>();
        }

        /// <summary>
        /// Gets the instance of this object.
        /// </summary>
        public static IToolBox Instance
        {
            get { return new ToolBox(); }
        }

        /// <summary>
        /// Gets Toolbox.
        /// </summary>
        public IToolBox Toolbox
        {
            get { return this; }
        }

        #region IToolBox Members

        /// <summary>
        /// Gets culture information to be added on threads. 
        /// Use GetThread methods to create Thread with Tea culture info instead of creating thread and 
        /// setting this information to it. 
        /// </summary>
        public CultureInfo Culture
        {
            get { return cultureInfo.TeaCultureInfo; }
        }

        /// <summary>
        /// Module service to get modules.
        /// </summary>
        private ModuleService moduleService;
        
        /// <summary>
        /// Gets the module service.
        /// </summary>
        public ModuleService ModuleService
        {
            get
            {
                if (this.moduleService == null)
                {
                    var module = this.Get(CoreServiceModuleKeys.ModuleService);
                    if (module != null)
                    {
                        this.moduleService = module as ModuleService;
                    }
                    else
                    {
                        throw new ApplicationException(
                            "ToolBox: Cannot access to module service.");
                    }
                }
                return this.moduleService;
            }

            set
            {
                this.moduleService = value;
            }
        }

        /// <summary>
        /// Add's service to service collections.
        /// </summary>
        /// <param name="serviceIdentifier">The service identifier.</param>
        /// <param name="service">The service.</param>
        public void Add(CoreServiceModuleKeys serviceIdentifier, object service)
        {
            services.TryAdd(serviceIdentifier, service);
        }

        /// <summary>
        /// Get's service with Id from toolbox.
        /// </summary>
        /// <param name="id">The id of service which is gathered.</param>
        /// <returns>Service is returned and if not found null.</returns>
        public object Get(CoreServiceModuleKeys id)
        {
            object service;
            this.services.TryGetValue(id, out service);
            return service;
        }

        /// <summary>
        /// Get's module from module store.
        /// </summary>
        /// <param name="moduleId">The module id.</param>
        /// <param name="requestorType">The requestor type.</param>
        /// <returns>Module as object if found otherwise null.</returns>
        /// <exception cref="ApplicationException"> if module service is not available.</exception>
        public object Get(string moduleId, Type requestorType)
        {
            return this.ModuleService.Modules[moduleId];
        }

        #endregion
    }
}