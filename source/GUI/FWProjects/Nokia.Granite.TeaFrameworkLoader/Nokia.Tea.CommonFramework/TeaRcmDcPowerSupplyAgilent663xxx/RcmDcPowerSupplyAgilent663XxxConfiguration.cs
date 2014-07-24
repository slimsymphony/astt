using System;

namespace Nokia.Tea.CommonFramework.Rcms
{
    /// <summary>
    /// Configuration for Dc Power Supply Agilent 663Xxx
    /// </summary>
    public class RcmDcPowerSupplyAgilent663XxxConfiguration
    {
        /// <summary>
        /// The unique ID default value of the used driver.
        /// </summary>
        public string UsedDriverUid = "RcmDcPowerSupplyAgilent663X" + "xx";

        public string ConfigurationInterface;

        #region ITeaModuleConfigurationcs Members

        /// <summary>
        /// Gets the name of the get interface.
        /// </summary>
        /// <value>
        /// The name of the get interface.
        /// </value>
        public string GetInterfaceName
        {
            get
            {
                if (this.ConfigurationInterface != null || this.ConfigurationInterface != string.Empty)
                {
                    return this.ConfigurationInterface;
                }

                return string.Empty;
            }
        }

        #endregion

        /// <summary>
        /// States if RCM has own User Control GUI.
        /// </summary>
        public bool HasOwnUserControl = false;

        /// <summary>
        /// States if own User Control of RCM is shown in Test Information view of the test system GUI.
        /// </summary>
        public bool ShowUserControlInTestInformation = false;
    }
}
