using Nokia.Tea.CoreFramework.BaseModules.TeaCoreModule;
using Nokia.Tea.CoreFramework.ToolBox.Interfaces;

namespace Nokia.Tea.CoreFramework.BaseModules.TeaServiceModule
{
    /// <summary>
    /// Defines a default keys that should be used when adding
    /// Core services to the object dictionaries.
    /// </summary>
    public enum CoreServiceModuleKeys
    {
        /// <summary>
        /// Configuration service UID
        /// </summary>
        ConfigurationService,

        /// <summary>
        /// Module invoker service client UID
        /// </summary>
        ModuleInvokerService,

        /// <summary>
        /// Module invoker service client UID
        /// </summary>
        ModuleService,

        /// <summary>
        /// Trace logger service UID
        /// </summary>
        TraceLoggerService,

        /// <summary>
        /// Result logger service UID
        /// </summary>
        ResultLoggerService,

        ///<summary>
        /// Runtime storage service UID
        ///</summary>
        RuntimeStorageService
    } 

    /// <summary>
    /// Defines a base class for all "core" services - The services that are meant for all.
    /// A trace logger service is a good example of a core service. All modules should be able
    /// to write log messages.
    /// </summary>
    public class TeaService : TeaBase
    {      
        /// <summary>
        /// Initializes a new instance of the <see cref="TeaService"/> class. 
        /// </summary>
        /// <param name="toolbox">Toolbox for service.</param>
        public TeaService(IToolBox toolbox) : base(toolbox)
        {
        }
    }
}