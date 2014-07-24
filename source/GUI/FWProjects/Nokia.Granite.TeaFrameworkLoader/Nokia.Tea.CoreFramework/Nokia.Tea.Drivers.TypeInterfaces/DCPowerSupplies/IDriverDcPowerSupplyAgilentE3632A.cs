using System;
using Nokia.Tea.CoreFramework.BaseModules.Drivers.BaseInterfaces;

// ReSharper disable CheckNamespace
namespace Nokia.Tea.Drivers.TypeInterfaces.PowerSupplies
// ReSharper restore CheckNamespace
{
    /// <summary>
    /// Interface for Agilent Dc power supply.
    /// </summary>
    public interface IDriverDcPowerSupplyAgilentE3632A : ITeaDriverLocking, IDisposable, ITeaDriverInfo
    {
        /// <summary>
        /// Gets the implementation details
        /// </summary>
        string Implementation { get; }

        /// <summary>
        /// Gets Details about the owner of the driver. Should contain name and email at least.
        /// </summary>
        string OwnerIdentification { get; }

        /// <summary>
        /// Intializes the TeaDriverDcPowerSupplyAgilent663xxx
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        void Initialize(object source);

        /// <summary>
        /// Configures over voltage protection 
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <param name="ovp">Over voltage protection value</param>
        void ConfigureOvp(object source, double ovp);

        /// <summary>
        /// Configures over current protection limit.
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <param name="ocpState">If true the ocpState will be set on, otherwise it will be set off</param>
        void ConfigureOcpState(object source, bool ocpState);

        /// <summary>
        /// Returns the over current protection status.
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>Returns the output state. True if output is on</returns>
        bool QueryOcpState(object source);

        /// <summary>
        /// Resets protections.
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <exception cref="ApplicationException">Thrown if driver is locked by another object</exception>
        void ResetProtection(object source);

        /// <summary>
        /// Sets current limit value
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <param name="current">Current limit value (A)</param>
        /// <exception cref="ApplicationException">Thrown if driver is locked by another object</exception>
        void ConfigureCurrentLimit(object source, double current);

        /// <summary>
        /// Reads set voltage limit value from power supply
        /// </summary>
        /// <returns>Set voltage value (V)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QueryVoltageLimit(object source);

        /// <summary>
        /// Returns the maximum allowed voltage limit
        /// </summary>
        /// <returns>Maximum allowed voltage value (V)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QueryVoltageLimitMax(object source);

        /// <summary>
        /// Returns the minimum allowed voltage limit
        /// </summary>
        /// <returns>Minimum allowed voltage value (V)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QueryVoltageLimitMin(object source);

        /// <summary>
        /// Returns the maximum allowed over voltage protection limit
        /// </summary>
        /// <returns>Maximum allowed over voltage protection value (V)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QueryOvpLimitMax(object source);

        /// <summary>
        /// Returns the minimum allowed over voltage protection limit
        /// </summary>
        /// <returns>Maximum allowed over voltage protection value (V)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QueryOvpLimitMin(object source);

        /// <summary>
        /// Returns the maximum allowed current limit
        /// </summary>
        /// <returns>Maximum allowed current value (A)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QueryCurrentLimitMax(object source);

        /// <summary>
        /// Returns the minimum allowed current limit
        /// </summary>
        /// <returns>Minimum allowed current value (A)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QueryCurrentLimitMin(object source);

        /// <summary>
        /// Returns the maximum allowed current protection limit
        /// </summary>
        /// <returns>Maximum allowed current protection value (A)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QueryOcpLimitMax(object source);

        /// <summary>
        /// Returns the minimum allowed current protection limit
        /// </summary>
        /// <returns>Maximum allowed current protection value (A)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QueryOcpLimitMin(object source);

        /// <summary>
        /// Returns the set value for maximum allowed voltage limit which can be set programmatically
        /// </summary>
        /// <returns>Maximum allowed voltage value (V)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QuerySafetyVoltageLimitMax(object source);

        /// <summary>
        /// Returns the set value for maximum allowed current limit which can be set programmatically
        /// </summary>
        /// <returns>Maximum allowed current value (A)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QuerySafetyCurrentLimitMax(object source);

        /// <summary>
        /// Reads set current value from power supply
        /// </summary>
        /// <returns>Set current value (A)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QueryCurrentLimit(object source);

        /// <summary>
        /// Reads set over voltage protection limit value from power supply
        /// </summary>
        /// <returns>Set over voltage protection value (V)</returns>
        /// <exception cref="ApplicationException">Thrown if driver is locked by another object</exception>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double QueryOverVoltageProtectionLimit(object source);

        /// <summary>
        /// Sets voltage limit  to power supply
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <param name="voltage">Voltage (V)</param>
        /// <exception cref="ApplicationException">Thrown if driver is locked by another object</exception>
        void ConfigureVoltageLimit(object source, double voltage);

        /// <summary>
        /// Sets programmable voltage limit to power supply
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <param name="voltage">Voltage (V)</param>
        /// <exception cref="ApplicationException">Thrown if driver is locked by another object</exception>
        void ConfigureSafetyVoltageLimitMax(object source, double voltage);

        /// <summary>
        /// Sets programmable current limit to power supply
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <param name="current">Current (A)</param>
        /// <exception cref="ApplicationException">Thrown if driver is locked by another object</exception>
        void ConfigureSafetyCurrentLimitMax(object source, double current);

        /// <summary>
        /// Measures current
        /// </summary>
        /// <returns>Current (mA)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double MeasureCurrent(object source);

        /// <summary>
        /// Measures voltage
        /// </summary>
        /// <returns>Voltage (V)</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        double MeasureVoltage(object source);

        /// <summary>
        /// Sets output off
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <exception cref="ApplicationException">Thrown if driver is locked by another object</exception>
        void SetOutputOff(object source);

        /// <summary>
        /// Sets output on
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <exception cref="ApplicationException">Thrown if driver is locked by another object</exception>
        void SetOutputOn(object source);

        /// <summary>
        /// Queries the output state
        /// </summary>
        /// <returns>True if output is on</returns>
        /// <param name="source">The caller obect (for locking purposes)</param>
        bool QueryIsOutputOn(object source);

        /// <summary>
        /// Resets the driver back to its initial state.
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        void Reset(object source);

        /// <summary>
        /// Closes the driver
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        void Close(object source);
    }
}
