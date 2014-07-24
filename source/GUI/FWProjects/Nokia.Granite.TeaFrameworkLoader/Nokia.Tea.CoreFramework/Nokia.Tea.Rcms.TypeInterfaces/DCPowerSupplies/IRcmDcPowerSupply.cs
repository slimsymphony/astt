using Nokia.Tea.CoreFramework.BaseModules.Rcms.BaseInterfaces;

namespace Nokia.Tea.Rcms.TypeInterfaces.DCPowerSupplies
{
    /// <summary>
    /// Interface for RCM power supply.
    /// </summary>
    public interface IRcmDcPowerSupply : ITeaRcmInstrument
    {
        /// <summary>
        /// Initializes the power supply.
        /// Default initial state (When applicable):
        /// Output off
        /// Voltage limit zero
        /// Current limit zero
        /// Over voltage protection max
        /// Over current protection max
        /// Safety voltage limit max
        /// Safety current limit max
        /// Impedance zero
        /// </summary>
        void InitAtStartTest();

        /// <summary>
        /// Sets voltage limit (V).
        /// </summary>
        /// <param name="voltageLimit">Voltage limit (V)</param>
        void ConfigureVoltageLimit(double voltageLimit);

        /// <summary>
        /// Returns the voltage limit which has been set to resource.
        /// </summary>
        /// <returns>Voltage limit (V).</returns>
        double QueryVoltageLimit();

        /// <summary>
        /// Sets the maximum programmable voltage limit. This can be used to make sure that voltage 
        /// is not set too high accidentally.
        /// </summary>
        /// <param name="voltageLimit">Maximum allowed programmable voltage limit (V). If set to zero, the limit 
        /// is not in use.</param>
        void ConfigureSafetyVoltageLimitMax(double voltageLimit);

        /// <summary>
        /// Returns the maximum voltage which resource is able to produce.
        /// </summary>
        /// <returns>Returns the maximum voltage which can be produced by resource (V).</returns>
        double QueryVoltageLimitMax();

        /// <summary>
        /// Returns the minimum voltage which resource is able to produce.
        /// </summary>
        /// <returns>Returns the minimum voltage which can be produced by resource (V).</returns>
        double QueryVoltageLimitMin();

        /// <summary>
        /// Returns the maximum programmable voltage limit set with ConfigureProgrammableVoltageLimitMax or by configuration.
        /// </summary>
        /// <returns>Returns the maximum programmable current limit (A).</returns>
        double QuerySafetyVoltageLimitMax();

        /// <summary>
        /// Returns the current limit which has been set to resource.
        /// </summary>
        /// <param name="currentLimit">Current limit (A)</param>
        void ConfigureCurrentLimit(double currentLimit);

        /// <summary>
        /// Returns current limit.
        /// </summary>
        /// <returns>Returns current limit (A).</returns>
        double QueryCurrentLimit();

        /// <summary>
        /// Sets the maximum programmable current limit. This can be used to make sure that current is 
        /// not set too high accidentally.
        /// </summary>
        /// <param name="currentLimit">Maximum allowed programmable current limit (A). If set to zero, the limit 
        /// is not in use.</param>
        void ConfigureSafetyCurrentLimitMax(double currentLimit);

        /// <summary>
        /// Returns the maximum current which resource is able to produce.
        /// </summary>
        /// <returns>Returns the maximum current which can be produced by resource (A).</returns>
        double QueryCurrentLimitMax();

        /// <summary>
        /// Returns the minimum current limit which resource is able to produce.
        /// </summary>
        /// <returns>Returns the minumum current which can be produced by resource (A).</returns>
        double QueryCurrentLimitMin();

        /// <summary>
        /// Query Programmed Current Limit Max returns the maximum programmable current limit 
        /// set with ConfigureProgrammableCurrentLimitMax or by configuration.
        /// </summary>
        /// <returns>Returns the maximum programmable current limit (A).</returns>
        double QuerySafetyCurrentLimitMax();

        /// <summary>
        /// Sets the resource output on.
        /// </summary>
        void SetOutputOn();

        /// <summary>
        /// Sets the resource output off.
        /// </summary>
        void SetOutputOff();

        /// <summary>
        /// Returns the output on state of resource.
        /// </summary>
        /// <returns>Returns true if output is on</returns>
        bool QueryIfOutputIsOn();

        /// <summary>
        /// Resets the (output voltage) protection of resource.
        /// </summary>
        void ResetProtection();

        /// <summary>
        /// Measures average current.
        /// </summary>
        /// <returns>Average current (mA)</returns>
        double MeasureAvgCurrent();

        /// <summary>
        /// Measures average voltage.
        /// </summary>
        /// <returns>Average voltage (V)</returns>
        double MeasureAvgVoltage();
    }
}