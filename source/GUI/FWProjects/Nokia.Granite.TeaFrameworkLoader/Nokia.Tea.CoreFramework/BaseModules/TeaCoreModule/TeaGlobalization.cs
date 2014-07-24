using System.Globalization;

namespace Nokia.Tea.CoreFramework.BaseModules.TeaCoreModule
{
    /// <summary>
    /// Defines the default culture configuration for all TeaModules.
    /// </summary>
    public class TeaGlobalization
    {
        #region Private members

        /// <summary>
        /// A private readonly object that defines
        /// the culture configuration for all TeaModules.
        /// </summary>
        private readonly CultureInfo cultureInfo;

        #endregion

        #region Constructors

        /// <summary>
        /// Initializes a new instance of the <see cref="TeaGlobalization"/> class.
        /// </summary>
        public TeaGlobalization()
        {
            NumberFormatInfo provider = new NumberFormatInfo
                                            {
                                                NumberDecimalSeparator = "."
                                            };
            this.cultureInfo = new CultureInfo("en-US")
                                   {
                                       DateTimeFormat =
                                           {
                                               ShortDatePattern = "dd.MM.yyyy",
                                               LongDatePattern = "dd.MM.yyyy",
                                               ShortTimePattern = "HH:mm:ss",
                                               LongTimePattern = "HH:mm:ss"
                                           },
                                       NumberFormat =
                                           {
                                               NumberDecimalSeparator = provider.NumberDecimalSeparator
                                           }
                                   };
        }

        #endregion

        #region Accessors

        /// <summary>
        /// Gets TeaCultureInfo.
        /// </summary>
        /// <value>
        /// The tea culture info.
        /// </value>
        public CultureInfo TeaCultureInfo
        {
            get { return this.cultureInfo; }
        }

        #endregion
    }
}