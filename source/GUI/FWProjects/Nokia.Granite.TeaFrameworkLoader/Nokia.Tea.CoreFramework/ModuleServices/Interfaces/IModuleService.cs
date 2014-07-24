using System.Collections.Concurrent;

namespace Nokia.Tea.CoreFramework.ModuleServices.Interfaces
{
    /// <summary>
    /// Interface to describe module service.
    /// </summary>
    public interface IModuleService
    {
        /// <summary>
        /// Gets or sets module dictionary.
        /// </summary>
        ConcurrentDictionary<string, object> Modules { get; set; }

        /// <summary>
        /// Adds module to module collection.
        /// </summary>
        /// <param name="uid">Identifier for module.</param>
        /// <param name="module">Module object.</param>
        void AddModule(string uid, object module);
    }
}