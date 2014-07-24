using System.Xml.Serialization;
using Nokia.Tea.CoreFramework.ToolBox.Interfaces;

namespace Nokia.Tea.CoreFramework.BaseModules.Rcms
{
    /// <summary>
    /// TeaModule inherited base class for all RCM modules.
    /// </summary>
    public class RcmModule : TeaModule
    {
        /// <summary>
        /// Configuration class id suffix.
        /// </summary>
        private const string configuration = "Configuration";

        private RcmStatus status;

        #region Constructors

        /// <summary>
        /// Initializes a new instance of the <see cref="RcmModule"/> class.
        /// </summary>
        /// <param name="moduleId">The unigue id for this module (Defined in configuration store).</param>
        /// <param name="toolBox">The tool box.</param>
        public RcmModule(string moduleId, IToolBox toolBox)
            : base(moduleId, toolBox)
        {
            this.Status = RcmStatus.Ready;
        }

        /// <summary>
        /// Gets or sets a value indicating whether RCM has own specific user control.
        /// </summary>
        public virtual bool HasOwnUserControl { get; protected set; }

        /// <summary>
        /// Gets or sets RCM specific user control.
        /// </summary>
        public object OwnUserControl { get; protected set; }

        /// <summary>
        /// Gets or sets RCM status.
        /// </summary>
        [XmlIgnore]
        public RcmStatus Status
        {
            get
            {
                return status;
            }
            set
            {
                status = value;
            }
        }

        #endregion
             
        /// <summary>
        /// Gets the configuration class module.
        /// </summary>
        /// <returns>Return the configuration object</returns>
        protected object GetConfiguration()
        {
            return base.ToolBox.Get(base.ModuleId + configuration, this.GetType());
        }

        /// <summary>
        /// Enum for RCM status.
        /// </summary>
        public enum RcmStatus
        {
            /// <summary>
            /// RCM is not ready.
            /// </summary>
            NotReady = 0,

            /// <summary>
            /// RCM is ready.
            /// </summary>
            Ready = 1,

            /// <summary>
            /// RCM is loading.
            /// </summary>
            Loading = 2,

            /// <summary>
            /// RCM is disabled.
            /// </summary>
            Disabled = 3,

            /// <summary>
            /// RCM has errors.
            /// </summary>
            Error = 4,
        }
    }
}