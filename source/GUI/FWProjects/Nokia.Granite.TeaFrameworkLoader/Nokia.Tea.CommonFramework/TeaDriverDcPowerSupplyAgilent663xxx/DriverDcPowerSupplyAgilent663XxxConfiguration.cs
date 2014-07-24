using System;

namespace Nokia.Tea.CommonFramework.Drivers
{
    /// <summary>
    /// Configuration class for DriverDcPowerSupplyAgilent663Xxx
    /// </summary>
    public class DriverDcPowerSupplyAgilent663XxxConfiguration
    {
        /// <summary>
        /// GPIB driver driver name which will be used.
        /// </summary>
        public string VisaDriverName = "TeaLowLevelDriverVisa";

        /// <summary>
        /// The connection string used for connecting to instument through VISA
        /// </summary>
        public string ConnectionString = "GPIB0::5::INSTR";

        /// <summary>
        /// Programmable limit for maximum voltage. Used to ensure that test system doesn't
        /// burn DUT accidentally. Setting value to zero disables this feature. This value is also
        /// used as initial value when instrument is initialized.
        /// </summary>
        public double SafetyMaxVoltageLimit = 4;

        /// <summary>
        /// Programmable limit for maximum current. Used to ensure that test system doesn't
        /// burn DUT accidentally. Setting value to zero disables this feature. This value is also
        /// used as initial value when instrument is initialized.
        /// </summary>
        public double SafetyMaxCurrentLimit = 2;

        /// <summary>
        /// Over voltage protection value (V). This value is 
        /// used as initial value when instrument is initialized.
        /// </summary>
        public double OverVoltageProtectionValue = 20;

        /// <summary>
        /// The over current protection state. This value is
        /// used as initial value when instrument is initialized.
        /// </summary>
        public bool OverCurrentProtectionState = true;

        /// <summary>
        /// The current limit value (A). This value is
        /// used as initial value when instrument is initialized.
        /// </summary>
        public double CurrentLimitValue = 2;

        /// <summary>
        /// The voltage limit value (V). This value is
        /// used as initial value when instrument is initialized.
        /// </summary>
        public double VoltageLimitValue = 4;
    }
}
