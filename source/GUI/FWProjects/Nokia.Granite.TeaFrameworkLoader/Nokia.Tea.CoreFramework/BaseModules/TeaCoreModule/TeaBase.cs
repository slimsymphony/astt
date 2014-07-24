using System;
using System.Reflection;
using System.Threading;
using Nokia.Tea.CoreFramework.Diagnostics.Implementations;
using Nokia.Tea.CoreFramework.Diagnostics.Interfaces;
using Nokia.Tea.CoreFramework.ToolBox.Interfaces;

namespace Nokia.Tea.CoreFramework.BaseModules.TeaCoreModule
{
    /// <summary>
    /// A base module for all Tea classes.
    /// </summary>
    public class TeaBase : IDisposable
    {
        #region Constructors

        /// <summary>
        /// Initializes a new instance of the <see cref="TeaBase"/> class. 
        /// </summary>
        /// <param name="toolBox">The tool box.</param>
        public TeaBase(IToolBox toolBox)
        {
            this.ToolBox = toolBox;
            Thread.CurrentThread.CurrentCulture = this.ToolBox.Culture;
            this.Logger = new TraceLoggerServiceClient(null, this);
        }
        
        #endregion

        #region AssemblyInformationMethods

        /// <summary>
        /// Gets the file location of the assembly that hosts this module.
        /// </summary>
        /// <returns>FilePath location of the assembly.</returns>
        public String GetAssemblyLocation()
        {
            var assembly = GetHostingAssembly();
            return assembly.Location;
        }

        /// <summary>
        /// Gets the name of the assembly that hosts this module.
        /// </summary>
        /// <returns>Name of the assembly as String.</returns>
        public String GetAssemblyName()
        {
            var assembly = GetHostingAssembly();
            return assembly.FullName.Split(',')[0];
        }

        /// <summary>
        /// Gets the version of the assembly that hosts this module.
        /// </summary>
        /// <returns>Version of the assembly as String.</returns>
        public String GetAssemblyVersion()
        {
            var assembly = GetHostingAssembly();
            return (assembly.FullName.Split(',')[1]).Split('=')[1];
        }

        /// <summary>
        /// Gets the object of the assembly that hosts this module.
        /// </summary>
        /// <returns>Assembly object.</returns>
        public Assembly GetHostingAssembly()
        {
            return Assembly.GetAssembly(this.GetType());
        }

        #endregion

        #region Accessors

        /// <summary>
        /// Gets or sets TraceLoggerServiceClient object.
        /// </summary>
        public ITraceLoggerServiceClient Logger
        {
            get; protected set;
        }

        /// <summary>
        /// Gets or sets toolbox.
        /// </summary>
        public IToolBox ToolBox { get; protected set; }

        #endregion

        #region IDisposable Members

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public virtual void Dispose()
        {
        }

        #endregion

        #region Initialization methods

        /// <summary>
        /// Initialization method which is called while test system is loading modules in memory.
        /// </summary>
        public virtual void InitAtLoad()
        {
        }

        /// <summary>
        /// Clearing method which is called when user exit from applications.
        /// </summary>
        public virtual void ClearAtUnLoad()
        {
            this.Dispose();
        }

        #endregion
    }
}