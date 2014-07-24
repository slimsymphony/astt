namespace Nokia.Tea.CoreFramework.BaseModules.Rcms.BaseInterfaces
{
    /// <summary>
    /// The base Role Control Module interface
    /// </summary>
    public interface ITeaRcm
    {
        /// <summary>
        /// Gets the vendor of the resource. Will very often be either company name or name of internal group in Nokia
        /// </summary>
        string Vendor { get; }

        /// <summary>
        /// Gets description of the RCM
        /// </summary>
        string Description { get; }

        /// <summary>
        /// Gets version on the form : major.minor.revision e.g. 2.1.15
        /// </summary>
        string Version { get; }

        /// <summary>
        /// Gets implementation details
        /// </summary>
        string Implementation { get; }

        /// <summary>
        /// Gets details about the owner of the resource. Should contain name and email at least.
        /// </summary>
        string OwnerIdentification { get; }

        /// <summary>
        /// Gets the logical name for the resource. e.g. for a power supply output the logical name could be "DutPower"
        /// </summary>
        string LogicalName { get; }

        /// <summary>
        /// Gets the resource set up information e.g. connection type, state and other setup properties
        /// </summary>
        string Setup { get; }

        /// <summary>
        /// Resets the RCM back to its initial state.
        /// </summary>
        void Reset();

        /// <summary>
        /// Closes the RCM
        /// </summary>
        void Close();
    }
}