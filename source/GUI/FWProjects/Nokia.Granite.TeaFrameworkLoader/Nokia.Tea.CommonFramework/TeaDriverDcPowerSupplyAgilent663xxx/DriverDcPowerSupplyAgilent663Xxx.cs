using System.Runtime.Serialization;
using Nokia.Tea.Drivers.TypeInterfaces.LowLevelDrivers;
using Nokia.Tea.Drivers.TypeInterfaces.PowerSupplies;

namespace Nokia.Tea.CommonFramework.Drivers
{
    using System;
    using CoreFramework.BaseModules.Drivers;
    using CoreFramework.ToolBox.Interfaces;

    /// <summary>
    /// Driver for Agilent 663x
    /// </summary>
    public class DriverDcPowerSupplyAgilent663Xxx : DriverModule, IDriverDcPowerSupplyAgilent663Xxx
    {
        /// <summary>
        /// The vendor of the device.
        /// N/A if not available.
        /// </summary>
        public string Vendor { get { return vendor; } }

        /// <summary>
        /// Version number of the driver on the form : major.minor.revision e.g. 2.1.15
        /// N/A if not available.
        /// </summary>
        public string Version { get { return version; } }

        /// <summary>
        /// Gets the implementation details
        /// </summary>
        public string Implementation { get { return implementationDetails; } }

        /// <summary>
        /// Gets Details about the owner of the driver. Should contain name and email at least.
        /// </summary>
        public string OwnerIdentification { get { return ownerIdentification; } }

        /// <summary>
        /// Setup of driver.
        /// </summary>
        public string Setup { get { return "Connection String: " + this.configuration.ConnectionString; } }

        /// <summary>
        /// Model name of the instrument.
        /// N/A if not available.
        /// </summary>
        public string InstrumentModel { get { return this.idnResult ?? "NA"; } }

        /// <summary>
        /// The resource descriptor specifies the connection to a physical device.
        /// E.g. USB, GPIB.
        /// N/A if not available.
        /// </summary>
        public string IoResourceDescriptor { get { return this.configuration.ConnectionString; } }

        /// <summary>
        /// Firmware version of the device this driver is controlling.
        /// N/A if not available.
        /// </summary>
        public string InstrumentFirmwareRevision { get { return this.idnResult ?? "NA"; } }

        /// <summary>
        /// Driver Vendor
        /// </summary>
        private const string vendor = "Nokia";

        /// <summary>
        /// Driver version
        /// </summary>
        private const string version = "0.0.1";

        /// <summary>
        /// Implementation details
        /// </summary>
        private const string implementationDetails = "";

        /// <summary>
        /// RCM owner identification string
        /// </summary>
        private const string ownerIdentification = "Tea.Framework group, Mailing list: I_EXT_TEAPLATFORM_GMS DG";

        /// <summary>
        /// Inidcates if power supply is initialised already.
        /// </summary>
        private bool initialized;

        /// <summary>
        /// Introduces private Object for locking mechanism.
        /// </summary>
        private readonly object lockObject;

        /// <summary>
        /// Introduces variable for maximum voltage limit value.
        /// </summary>
        private double voltageLimitMax;

        /// <summary>
        /// Introduces variable for minimum voltage limit value.
        /// </summary>
        private double voltageLimitMin;

        /// <summary>
        /// Introduces variable for maximum OVP limit value.
        /// </summary>
        private double ovpLimitMax;

        /// <summary>
        /// Introduces variable for minumum OVP limit value.
        /// </summary>
        private double ovpLimitMin;

        /// <summary>
        /// Introduces variable for maximum current limit value.
        /// </summary>
        private double currentLimitMax;

        /// <summary>
        /// Introduces variable for minumum current limit value.
        /// </summary>
        private double currentLimitMin;

        /// <summary>
        /// Result for IDN query
        /// </summary>
        private string idnResult;

        /// <summary>
        /// Original value for reuse in reset
        /// </summary>
        private double originalSafetyMaxCurrentLimit;

        /// <summary>
        /// Original value for reuse in reset
        /// </summary>
        private double originalSafetyMaxVoltageLimit;

        /// <summary>
        /// Original value for reuse in reset
        /// </summary>
        private double originalOvpValue;

        /// <summary>
        /// Original value for reuse in reset
        /// </summary>
        private double originalCurrentLimitValue;

        /// <summary>
        /// Original value for reuse in reset
        /// </summary>
        private bool originalOcpState;

        /// <summary>
        /// Gets configuration.
        /// A private accessor to cast the base class
        /// configuration Object to configuration class specific
        /// Object instance.
        /// </summary>
        /// <value>
        /// The configuration.
        /// </value>
        private DriverDcPowerSupplyAgilent663XxxConfiguration configuration { get { return GetConfiguration() as DriverDcPowerSupplyAgilent663XxxConfiguration; } }

        /// <summary>
        /// Gets property for getting driver. Used because driver cannot be set in constructor since
        /// driver might not exist yet
        /// </summary>
        private ILowLevelDriverVisa visaDriver { get { return (ILowLevelDriverVisa)GetModule(this.configuration.VisaDriverName); } }

        /// <summary>
        /// Initializes a new instance of the <see cref="DriverDcPowerSupplyAgilent663Xxx"/> class.
        /// </summary>
        /// <param name="moduleId">The unique id of this module</param>
        /// <param name="toolBox">A handle to tool box.</param>
        public DriverDcPowerSupplyAgilent663Xxx(string moduleId, IToolBox toolBox)
            : base(moduleId, toolBox)
        {
            // Create Object for thread safe locking purposes
            this.lockObject = new object();
            this.initialized = false;
        }


        #region Public methods

        /// <summary>
        /// Initialization method which is called while test system is loading modules in memory.
        /// </summary>
        public override void InitAtLoad()
        {
            this.Logger.TracePrintToUi("DcPowerSupply Agilent633 driver - INIT");
            base.InitAtLoad();

            if (!SimulationMode)
                Initialize(this);
            else initialized = true;
        }

        /// <summary>
        /// Intializes the TeaDriverDcPowerSupplyAgilent663xxx
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        public void Initialize(object source)
        {
            lock (this.lockObject)
            {
                CheckIfUsableByCaller(source);
                
                // At the momentthe powerSupplyAgilent have to be initialized everytime,
                // otherwise it can be a conflict between the cmu200 during using..
                //Todo: Check better solution and why there is an conflict between those devices

                if (!this.initialized)
                {
                    if (!SimulationMode)
                        this.visaDriver.OpenMessageBasedSession(this.configuration.ConnectionString);
                    base.Logger.TracePrintToUi("DcPowerSupplyAgilent663Xxx - INIT");
                    this.initialized = true;
                    try
                    {
                        this.write("*CLS");

                        //this.SetOutputOff(source);

                        this.voltageLimitMax = this.QueryVoltageLimitMax(source);
                        this.voltageLimitMin = this.QueryVoltageLimitMin(source);

                        this.currentLimitMax = this.QueryCurrentLimitMax(source);
                        this.currentLimitMin = this.QueryCurrentLimitMin(source);

                        this.ovpLimitMax = this.QueryOvpLimitMax(source);
                        this.ovpLimitMin = this.QueryOvpLimitMin(source);

                        this.originalSafetyMaxCurrentLimit = this.configuration.SafetyMaxCurrentLimit;
                        this.originalSafetyMaxVoltageLimit = this.configuration.SafetyMaxVoltageLimit;

                        this.originalOvpValue = this.configuration.OverVoltageProtectionValue;

                        this.originalCurrentLimitValue = this.configuration.CurrentLimitValue;
                        this.originalOcpState = this.configuration.OverCurrentProtectionState;

                        this.ConfigureSafetyCurrentLimitMax(source, this.configuration.SafetyMaxCurrentLimit);
                        this.ConfigureSafetyVoltageLimitMax(source, this.configuration.SafetyMaxVoltageLimit);

                        this.ConfigureOvp(source, this.configuration.OverVoltageProtectionValue);

                        this.ConfigureOcpState(source, this.configuration.OverCurrentProtectionState);
                        this.ConfigureCurrentLimit(source, this.configuration.CurrentLimitValue);

                        this.ConfigureVoltageLimit(source, this.configuration.VoltageLimitValue);
                        
                        this.ResetProtection(source);
                        this.idnResult = this.query("*IDN?");
                    }
                    catch (Exception e)
                    {
                        Logger.TraceError("DriverDcPowerSupplyAgilent663Xxx initialization failed", e.Message);
                        this.initialized = false;
                        throw;
                    }
                }
                else
                {
                    this.write("*CLS");
                }
            }
        }

        /// <summary>
        /// Configures over voltage protection
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <param name="ovp">Over voltage protection value</param>
        public void ConfigureOvp(object source, double ovp)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                CheckIfUsableByCaller(source);

                if (this.ovpLimitMin > ovp)
                {
                    throw new ArgumentOutOfRangeException("Trying to set over voltage protection too low"
                                                          + " Limit: " + this.ovpLimitMin.ToString() + " Tried to set: " +
                                                          ovp.ToString());
                }

                if (this.ovpLimitMax < ovp)
                {
                    throw new ArgumentOutOfRangeException("Trying to set over voltage protection too high"
                                                          + " Limit: " + this.ovpLimitMax.ToString() + " Tried to set: " +
                                                          ovp.ToString());
                }

                this.write("VOLTage:PROTection " + ovp.ToString() + " V");
            }
        }

        /// <summary>
        /// Configures over current protection limit.
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <param name="ocpState">If true the ocpState will be set on, otherwise it will be set off</param>
        public void ConfigureOcpState(object source, bool ocpState)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                CheckIfUsableByCaller(source);
                if (ocpState)
                {
                    this.write("CURRent:PROTection:STATe ON");
                }
                else
                {
                    this.write("CURRent:PROTection:STATe OFF");                    
                }
            }
        }

        /// <summary>
        /// Returns the over current protection status.
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Returns the output state. True if output is on
        /// </returns>
        public bool QueryOcpState(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                CheckIfUsableByCaller(source);
                string result;
                result = this.query("CURRent:PROTection:STATe?");
                if ("1" == result)
                {
                    return true;
                }

                if ("0" == result)
                {
                    return false;
                }

                throw new ApplicationException("Unexpected output state result received: " + result);
            }
        }

        /// <summary>
        /// Resets protections.
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <exception cref="T:System.ApplicationException">Thrown if driver is locked by another object</exception>
        public void ResetProtection(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                CheckIfUsableByCaller(source);

                this.write("OUTPut:PROTection:CLEar");
            }
        }

        /// <summary>
        /// Sets current limit value
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <param name="current">Current limit value (A)</param>
        /// <exception cref="T:System.ApplicationException">Thrown if driver is locked by another object</exception>
        public void ConfigureCurrentLimit(object source, double current)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                CheckIfUsableByCaller(source);

                if (this.configuration.SafetyMaxCurrentLimit < current)
                {
                    throw new ArgumentOutOfRangeException("Trying to set current limit abowe range. "
                        + "Limit: " + this.configuration.SafetyMaxCurrentLimit.ToString()
                        + " Tried to set: " + current.ToString());
                }

                if (this.currentLimitMin > current)
                {
                    throw new ArgumentOutOfRangeException(
                        "Trying to set current limit too low. "
                        + "Limit: " + this.currentLimitMin.ToString()
                        + " Tried to set: " + current.ToString());
                }

                this.write("CURRent " + current.ToString()); 
            }
        }

        /// <summary>
        /// Reads set voltage limit value from power supply
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Set voltage value (V)
        /// </returns>
        public double QueryVoltageLimit(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return Convert.ToDouble(this.query("VOLTage?")); 
            }
        }

        /// <summary>
        /// Returns the maximum allowed voltage limit
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Maximum allowed voltage value (V)
        /// </returns>
        public double QueryVoltageLimitMax(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return Convert.ToDouble(this.query("VOLTage? MAXimum")); 
            }
        }

        /// <summary>
        /// Returns the minimum allowed voltage limit
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Minimum allowed voltage value (V)
        /// </returns>
        public double QueryVoltageLimitMin(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return Convert.ToDouble(this.query("VOLTage? MINimum")); 
            }
        }

        /// <summary>
        /// Returns the maximum allowed over voltage protection limit
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Maximum allowed over voltage protection value (V)
        /// </returns>
       public double QueryOvpLimitMax(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return Convert.ToDouble(this.query("VOLTage:PROTection? MAXimum"));
            }
        }

       /// <summary>
       /// Returns the minimum allowed over voltage protection limit
       /// </summary>
       /// <param name="source">The caller obect (for locking purposes)</param>
       /// <returns>
       /// Maximum allowed over voltage protection value (V)
       /// </returns>
        public double QueryOvpLimitMin(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return Convert.ToDouble(this.query("VOLTage:PROTection? MINimum"));
            }
        }

        /// <summary>
        /// Returns the maximum allowed current limit
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Maximum allowed current value (A)
        /// </returns>
        public double QueryCurrentLimitMax(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return Convert.ToDouble(this.query("CURRent? MAXimum")); 
            }
        }

        /// <summary>
        /// Returns the minimum allowed current limit
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Minimum allowed current value (A)
        /// </returns>
        public double QueryCurrentLimitMin(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return Convert.ToDouble(this.query("CURRent? MINimum")); 
            }
        }

        /// <summary>
        /// Returns the maximum allowed current protection limit
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Maximum allowed current protection value (A)
        /// </returns>
        public double QueryOcpLimitMax(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                // Same as current min because power supply doesn't have query for this
                return Convert.ToDouble(this.query("CURRent? MAXimum"));
            }
        }

        /// <summary>
        /// Returns the minimum allowed current protection limit
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Maximum allowed current protection value (A)
        /// </returns>
        public double QueryOcpLimitMin(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                // Same as current min because power supply doesn't have query for this
                return Convert.ToDouble(this.query("CURRent? MINimum"));
            }
        }

        /// <summary>
        /// Returns the set value for maximum allowed voltage limit which can be set programmatically
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Maximum allowed voltage value (V)
        /// </returns>
        public double QuerySafetyVoltageLimitMax(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return this.configuration.SafetyMaxVoltageLimit;
            }
        }

        /// <summary>
        /// Returns the set value for maximum allowed current limit which can be set programmatically
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Maximum allowed current value (A)
        /// </returns>
        public double QuerySafetyCurrentLimitMax(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return this.configuration.SafetyMaxCurrentLimit; 
            }
        }

        /// <summary>
        /// Reads set current value from power supply
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Set current value (A)
        /// </returns>
        public double QueryCurrentLimit(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return Convert.ToDouble(this.query("CURRent?")); 
            }
        }

        /// <summary>
        /// Reads set over voltage protection limit value from power supply
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Set over voltage protection value (V)
        /// </returns>
        /// <exception cref="T:System.ApplicationException">Thrown if driver is locked by another object</exception>
        public double QueryOverVoltageProtectionLimit(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return Convert.ToDouble(this.query("VOLTage:PROTection:LEVel?")); 
            }
        }

        /// <summary>
        /// Sets voltage limit  to power supply
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <param name="voltage">Voltage (V)</param>
        /// <exception cref="T:System.ApplicationException">Thrown if driver is locked by another object</exception>
        public void ConfigureVoltageLimit(object source, double voltage)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                CheckIfUsableByCaller(source);

                if (this.configuration.SafetyMaxVoltageLimit < voltage)
                {
                    throw new ArgumentOutOfRangeException("Trying to set voltage limit abowe range. Limit:" +
                                                          this.configuration.SafetyMaxVoltageLimit.ToString() +
                                                          "Trying to set:" + voltage.ToString());
                }

                if (0 > voltage)
                {
                    throw new ArgumentOutOfRangeException(
                        "Trying to set voltage limit too low Limit: 0 Trying to set:" + voltage.ToString());
                }

                this.write(":VOLTage " + Convert.ToString(voltage)); 
            }
        }

        /// <summary>
        /// Sets programmable voltage limit to power supply
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <param name="voltage">Voltage (V)</param>
        /// <exception cref="T:System.ApplicationException">Thrown if driver is locked by another object</exception>
        public void ConfigureSafetyVoltageLimitMax(object source, double voltage)
        {
             lock (this.lockObject)
            {
                 this.isInitialized();
                 CheckIfUsableByCaller(source);

                if (this.voltageLimitMax < voltage)
                {
                    throw new ArgumentOutOfRangeException("Trying to set the programmable limited value too high."
                        + " Limit: " + this.voltageLimitMax.ToString() + " Tried to set: " + voltage.ToString());
                }

                if (this.voltageLimitMin > voltage)
                {
                    throw new ArgumentOutOfRangeException("Trying to set the programmable limited value too low."
                        + " Limit: " + this.voltageLimitMin.ToString() + " Tried to set: " + voltage.ToString());
                }

                this.configuration.SafetyMaxVoltageLimit = voltage; 
            }
        }

        /// <summary>
        /// Sets programmable current limit to power supply
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <param name="current">Current (A)</param>
        /// <exception cref="T:System.ApplicationException">Thrown if driver is locked by another object</exception>
        public void ConfigureSafetyCurrentLimitMax(object source, double current)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                CheckIfUsableByCaller(source);

                if (this.currentLimitMax < current)
                {
                    throw new ArgumentOutOfRangeException("Trying to set the programmable limited value too high."
                        + " Limit: " + this.currentLimitMax.ToString() + " Tried to set: " + current.ToString());
                }

                if (this.currentLimitMin > current)
                {
                    throw new ArgumentOutOfRangeException("Trying to set the programmable limited value too low."
                        + " Limit: " + this.currentLimitMin.ToString() + " Tried to set: " + current.ToString());
                }

                this.configuration.SafetyMaxCurrentLimit = current; 
            }
        }

        /// <summary>
        /// Measures current
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Current (mA)
        /// </returns>
        public double MeasureCurrent(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return Convert.ToDouble(this.query("MEASure:CURRent?")) * 1000;   
            }
        }

        /// <summary>
        /// Measures voltage
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// Voltage (V)
        /// </returns>
        public double MeasureVoltage(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                return Convert.ToDouble(this.query("MEASure:VOLTage?"));
            }
        }

        /// <summary>
        /// Sets output off
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <exception cref="T:System.ApplicationException">Thrown if driver is locked by another object</exception>
        public void SetOutputOff(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                CheckIfUsableByCaller(source);

                this.write("OUTPut OFF"); 
            }
        }

        /// <summary>
        /// Sets output on
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <exception cref="T:System.ApplicationException">Thrown if driver is locked by another object</exception>
        public void SetOutputOn(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                CheckIfUsableByCaller(source);
                this.write("OUTPut ON"); 
            }
        }

        /// <summary>
        /// Queries the output state
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        /// <returns>
        /// True if output is on
        /// </returns>
        public bool QueryIsOutputOn(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                string result = this.query("OUTPut?");
                if (result == "1")
                {
                    return true;
                }

                if (result == "0")
                {
                    return false;
                }

                throw new ApplicationException("Unexpected output state result received: " + result); 
            }
        }

        /// <summary>
        /// Resets the driver back to its initial state.
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        public void Reset(object source)
        {
            lock (this.lockObject)
            {
                this.isInitialized();
                CheckIfUsableByCaller(source);

                this.write("*CLS");
                this.ResetProtection(source);

                this.ConfigureCurrentLimit(source, this.currentLimitMin);
                this.ConfigureVoltageLimit(source, this.voltageLimitMin);

                this.ConfigureSafetyCurrentLimitMax(source, this.originalSafetyMaxCurrentLimit);
                this.ConfigureSafetyVoltageLimitMax(source, this.originalSafetyMaxVoltageLimit);

                this.ConfigureOvp(source, this.originalOvpValue);

                this.ConfigureOcpState(source, this.originalOcpState);
                this.ConfigureCurrentLimit(source, this.originalCurrentLimitValue);
            }
        }

        /// <summary>
        /// Closes the driver
        /// </summary>
        /// <param name="source">The caller obect (for locking purposes)</param>
        public void Close(object source)
        {
            lock (this.lockObject)
            {
                this.Reset(source);
                this.initialized = false;
                this.visaDriver.Dispose();
            }
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
        }

        #endregion

        /// <summary>
        /// An overridable implementation of Dispose(bool). Call Dispose(false) to clean up native
        /// resources. Call Dispose(true) to clean up both managed and native resources.
        /// </summary>
        /// <param name="disposing">disposing (boolean)</param>
        protected virtual void Dispose(bool disposing) { if (disposing) { this.visaDriver.Dispose(); } }

        #region Private methods

        /// <summary>
        /// Driver's internal method for setting commands to the gpib driver.
        /// </summary>
        /// <param name="message">The String to the device</param>
        /// <exception cref="ApplicationException">Method execution failed</exception>
        private void write(string message)
        {
            if (!SimulationMode)
            {
                try
                {
                    this.writeDebugString(this + ".write", message);
                    //before send msg to this Device, the address of this device must be reset, 
                    //because there are more Devices work together of GPIB(visaDrivers)
                    this.visaDriver.OpenMessageBasedSession(this.configuration.ConnectionString);
                    this.visaDriver.WriteUsingMessageBasedSession(message);
                    this.checkErrors();
                }
                catch (Exception ex)
                {
                    base.Logger.TraceError(ex.Message);
                    throw new ApplicationException("Write failed", ex);
                }
            }
            else
            {
                this.writeDebugString(this + ".simulatedWrite", message);
            }
        }

        /// <summary>
        /// Driver's internal method for query information from device.
        /// </summary>
        /// <param name="message">The String to the device (i.e. "ID?")</param>
        /// <returns>String from device</returns>
        private string query(string message)
        {
            try
            {
                this.writeDebugString(this + ".query", message);
                var queryStartTime = DateTime.Now;
                string retVal = this.visaDriver.QueryUsingMessageBasedSession(message);
                var queryTimeout = Convert.ToInt32((DateTime.Now - queryStartTime).TotalMilliseconds);
                retVal = retVal.Trim();
                //AddSimulatedQueryResponse(message, queryTimeout, retVal);
                this.checkErrors();
                return retVal;
            }
            catch (Exception ex)
            {
                base.Logger.TraceError(ex.Message);
                throw new ApplicationException("Query failed", ex);
            }
            //try
            //{
            //    this.writeDebugString(this + ".simulatedQuery", message);
            //    var timeoutAndResponse = GetSimulatedQueryResponse(message);
            //    System.Threading.Thread.Sleep(timeoutAndResponse.Item1);
            //    return timeoutAndResponse.Item2;
            //}
            //catch (Exception ex)
            //{
            //    base.Logger.TraceError(ex.Message);
            //    throw new ApplicationException("Simulated Query failed", ex);
            //}
        }


        /// <summary>
        /// This method writes given string into the log.
        /// </summary>
        /// <param name="source">The source.</param>
        /// <param name="message">The message.</param>
        private void writeDebugString(string source, string message)
        {
            base.Logger.TraceInformation(source + " : " + message);
        }

        /// <summary>
        /// Driver's internal method for error checking
        /// </summary>
        private void checkErrors()
        {
            string check = this.visaDriver.QueryUsingMessageBasedSession("SYSTem:ERR?");
            check = check.Trim();
            if (!check.StartsWith("+0"))
            {
                throw new ApplicationException("Agilent error: " + check);
            }
        }

        /// <summary>
        /// Checks if driver is initialized. If not an exception is thrown
        /// </summary>
        /// <exception cref="ApplicationException">Driver is not initialized</exception>
        private void isInitialized() { if (!this.initialized) { throw new InvalidOperationException("Driver is not initialized"); } }

        #endregion

        #region ITeaDriverInfo Members

        /// <summary>
        /// Description of the device.
        /// N/A if not available.
        /// </summary>
        public string Description { get { return "This is the DC Power Supply for Agilent 663Xxx"; } }

        #endregion
    }
}
