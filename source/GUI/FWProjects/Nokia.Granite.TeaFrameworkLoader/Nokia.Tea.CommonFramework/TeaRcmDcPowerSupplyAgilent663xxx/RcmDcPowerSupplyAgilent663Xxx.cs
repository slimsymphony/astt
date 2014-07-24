using Nokia.Tea.Drivers.TypeInterfaces.PowerSupplies;
using Nokia.Tea.Rcms.TypeInterfaces.DCPowerSupplies;

namespace Nokia.Tea.CommonFramework.Rcms
{
    using System;
    using CoreFramework.BaseModules.Rcms;
    using CoreFramework.ToolBox.Interfaces;

    /// <summary>
    /// Role Control Module for Agilent 663 series power supply
    /// </summary>
    public class RcmDcPowerSupplyAgilent663Xxx : RcmModule, IRcmDcPowerSupply
    {
        /// <summary>
        /// The logical name of the RCM
        /// </summary>
        private const string logicalName = "DC-power supply";

        /// <summary>
        /// RCM Vendor
        /// </summary>
        private const string vendor = "Nokia";

        /// <summary>
        /// RCM version
        /// </summary>
        private const string version = "0.0.1";

        /// <summary>
        /// Implementation details
        /// </summary>
        private const string implementationDetails = "";

        /// <summary>
        /// Role Control Module description
        /// </summary>
        private const string description = "Role Control Module for controlling DC-Power supply";

        /// <summary>
        /// RCM owner identification string
        /// </summary>
        private const string ownerIdentification = "Tea.Framework group, Mailing list: I_EXT_TEAPLATFORM_GMS DG";

        /// <summary>
        /// Gets the vendor of the resource. Will very often be either company name or name of internal group in Nokia
        /// </summary>
        public string Vendor
        {
            get 
            { 
                return "RCM: " + vendor + " Driver: " 
                + this.driver.Vendor;
            }
        }

        /// <summary>
        /// Gets description of the RCM
        /// </summary>
        public string Description
        {
            get { return description; }
        }

        /// <summary>
        /// Gets version on the form : major.minor.revision e.g. 2.1.15
        /// </summary>
        public string Version
        {
            get 
            {
                return "RCM: " + version + " Driver: "
                + this.driver.Version;
            }
        }

        /// <summary>
        /// Gets implementation details
        /// </summary>
        public string Implementation
        {
            get 
            {
                return "Rcm: " + implementationDetails
                + " Driver: " + this.driver.Implementation;
            }
        }

        /// <summary>
        /// Gets details about the owner of the resource. Should contain name and email at least.
        /// </summary>
        public string OwnerIdentification
        {
            get 
            {
                return "Rcm: " + ownerIdentification
                + " Driver: " + this.driver.OwnerIdentification;
            }
        }

        /// <summary>
        /// Gets the logical name for the resource. e.g. for a power supply output the logical name could be "DutPower"
        /// </summary>
        public string LogicalName
        {
            get { return logicalName; }
        }

        /// <summary>
        /// Gets the resource set up information e.g. connection type, state and other setup properties
        /// </summary>
        public string Setup
        {
            get 
            {
                return "Rcm: Used driver ID: " + this.configuration.UsedDriverUid
                + " Driver: " + this.driver.Setup;
            }
        }

        /// <summary>
        /// Resets the RCM back to its initial state.
        /// </summary>
        public void Reset()
        {
            this.driver.Reset(this);
        }

        /// <summary>
        /// Closes the RCM
        /// </summary>
        public void Close()
        {
            this.driver.Close(this);
        }

        /// <summary>
        /// Clearing method which is called when user exit from applications.
        /// </summary>
        public override void ClearAtUnLoad()
        {
            base.ClearAtUnLoad();

            this.Close();
        }


        /// <summary>
        /// Gets the model name of the instrument
        /// </summary>
        public string InstrumentModel
        {
            get { return this.driver.InstrumentModel; }
        }

        /// <summary>
        /// Gets the resource descriptor which specifies the connection to a physical device.
        /// </summary>
        public string IoResourceDescriptor
        {
            get { return this.driver.IoResourceDescriptor; }
        }

        /// <summary>
        /// Gets the instrument firmware revision information.
        /// </summary>
        public string InstrumentFirmwareRevision
        {
            get { return this.driver.InstrumentFirmwareRevision; }
        }

        /// <summary>
        /// Gets bool which states if Phone Information has own specific user control.
        /// </summary>
        public override bool HasOwnUserControl { get { return this.configuration.HasOwnUserControl; } }

        /// <summary>
        /// Gets configuration.
        /// A private accessor to cast the base class
        /// configuration Object to configuration class specific
        /// Object instance.
        /// </summary>
        /// <value>
        /// The configuration.
        /// </value>
        private RcmDcPowerSupplyAgilent663XxxConfiguration configuration
        {
            get { return GetConfiguration() as RcmDcPowerSupplyAgilent663XxxConfiguration; }
        }

        /// <summary>
        /// Gets driver handle. Used because driver cannot be set in constructor since
        /// driver might not exist yet
        /// </summary>
        private IDriverDcPowerSupplyAgilent663Xxx driver
        {
            get
            {
                return (IDriverDcPowerSupplyAgilent663Xxx)base.GetModule(this.configuration.UsedDriverUid);
            }
        }
   
        /// <summary>
        /// Initializes a new instance of the <see cref="RcmDcPowerSupplyAgilent663Xxx"/> class.
        /// </summary>
        /// <param name="moduleId">
        /// The module id.
        /// </param>
        /// <param name="toolBox">
        /// The toolbox inteface Object.
        /// </param>
        public RcmDcPowerSupplyAgilent663Xxx(string moduleId, IToolBox toolBox)
            : base(moduleId, toolBox)
        {
            base.HasOwnUserControl = this.configuration.HasOwnUserControl;
        }

        /// <summary>
        /// Locks the instrument and returns object which keeps the lock. Preferred
        /// way of locking is by having the using method. E.g. using (RcmExample.Lock) {...}
        /// </summary>
        /// <returns>
        /// Object which holds the lock. Lock can be unlocked by disposing this object
        /// </returns>
        public IDisposable Lock()
        {
            return this.driver.Lock(this);
        }

        /// <summary>
        /// Unlocks instrument.
        /// </summary>
        public void Unlock()
        {
            this.driver.Unlock(this);
        }

        public void InitAtStartTest()
        {
           this.driver.Initialize(this);
        }

        /// <summary>
        /// Sets voltage limit (V)
        /// </summary>
        /// <param name="voltageLimit">Voltage limit (V)</param>
        public void ConfigureVoltageLimit(double voltageLimit)
        {
            this.driver.ConfigureVoltageLimit(this, voltageLimit);
        }

        /// <summary>
        /// Returns the voltage limit which has been set to resource.
        /// </summary>
        /// <returns>
        /// Voltage limit (V).
        /// </returns>
        public double QueryVoltageLimit()
        {
            return this.driver.QueryVoltageLimit(this);
        }

        /// <summary>
        /// Sets the maximum programmable voltage limit. This can be used to make sure that voltage is not set too high accidentally.
        /// </summary>
        /// <param name="voltageLimit">Maximum allowed programmable voltage limit (V). If set to zero, the limit is not in use.</param>
        public void ConfigureSafetyVoltageLimitMax(double voltageLimit)
        {
            this.driver.ConfigureSafetyVoltageLimitMax(this, voltageLimit);
        }

        /// <summary>
        /// Returns the maximum voltage which resource is able to produce.
        /// </summary>
        /// <returns>
        /// Returns the maximum voltage which can be produced by resource (V).
        /// </returns>
        public double QueryVoltageLimitMax()
        {
            return this.driver.QueryVoltageLimitMax(this);
        }

        /// <summary>
        /// Returns the minimum voltage which resource is able to produce.
        /// </summary>
        /// <returns>
        /// Returns the minimum voltage which can be produced by resource (V).
        /// </returns>
        public double QueryVoltageLimitMin()
        {
            return this.driver.QueryVoltageLimitMin(this);
        }

        /// <summary>
        /// Returns the maximum programmable voltage limit set with ConfigureProgrammableVoltageLimitMax or by configuration.
        /// </summary>
        /// <returns>
        /// Returns the maximum programmable current limit (A).
        /// </returns>
        public double QuerySafetyVoltageLimitMax()
        {
            return this.driver.QuerySafetyVoltageLimitMax(this);
        }

        /// <summary>
        /// Returns the current limit which has been set to resource.
        /// </summary>
        /// <param name="currentLimit">Current limit (A)</param>
        public void ConfigureCurrentLimit(double currentLimit)
        {
            this.driver.ConfigureCurrentLimit(this, currentLimit);
        }

        /// <summary>
        /// Returns current limit.
        /// </summary>
        /// <returns>
        /// Returns current limit (A).
        /// </returns>
        public double QueryCurrentLimit()
        {
            return this.driver.QueryCurrentLimit(this);
        }

        /// <summary>
        /// Sets the maximum programmable current limit. This can be used to make sure that current is not set too high accidentally.
        /// </summary>
        /// <param name="currentLimit">Maximum allowed programmable current limit (A). If set to zero, the limit is not in use.</param>
        public void ConfigureSafetyCurrentLimitMax(double currentLimit)
        {
            this.driver.ConfigureSafetyCurrentLimitMax(this, currentLimit);
        }

        /// <summary>
        /// Returns the maximum current which resource is able to produce.
        /// </summary>
        /// <returns>
        /// Returns the maximum current which can be produced by resource (A).
        /// </returns>
        public double QueryCurrentLimitMax()
        {
            return this.driver.QueryCurrentLimitMax(this);
        }

        /// <summary>
        /// Returns the minimum current limit which resource is able to produce.
        /// </summary>
        /// <returns>
        /// Returns the minumum current which can be produced by resource (A).
        /// </returns>
        public double QueryCurrentLimitMin()
        {
            return this.driver.QueryCurrentLimitMin(this);
        }

        /// <summary>
        /// Query Programmed Current Limit Max returns the maximum programmable current limit set with ConfigureProgrammableCurrentLimitMax or by configuration.
        /// </summary>
        /// <returns>
        /// Returns the maximum programmable current limit (A).
        /// </returns>
        public double QuerySafetyCurrentLimitMax()
        {
            return this.driver.QuerySafetyCurrentLimitMax(this);
        }

        /// <summary>
        /// Sets the resource output on.
        /// </summary>
        public void SetOutputOn()
        {
            this.driver.SetOutputOn(this);
        }

        /// <summary>
        /// Sets the resource output off.
        /// </summary>
        public void SetOutputOff()
        {
            this.driver.SetOutputOff(this);
        }

        /// <summary>
        /// Returns the output on state of resource.
        /// </summary>
        /// <returns>
        /// Returns true if output is on
        /// </returns>
        public bool QueryIfOutputIsOn()
        {
            return this.driver.QueryIsOutputOn(this);
        }

        /// <summary>
        /// Resets the (output voltage) protection of resource.
        /// </summary>
        public void ResetProtection()
        {
            this.driver.ResetProtection(this);
        }

        /// <summary>
        /// Measures Average current
        /// </summary>
        /// <returns>
        /// Average current (mA)
        /// </returns>
        public double MeasureAvgCurrent()
        {
            return this.driver.MeasureCurrent(this);
        }

        /// <summary>
        /// Measures average voltage
        /// </summary>
        /// <returns>
        /// Average voltage (V)
        /// </returns>
        public double MeasureAvgVoltage()
        {
            return this.driver.MeasureVoltage(this);
        }

        #region IRcmDummyBattery Members

        /// <summary>
        /// Connects the battery
        /// </summary>
        public void ConnectBattery()
        {
            this.driver.Initialize(this);
            this.driver.SetOutputOn(this);
        }

        /// <summary>
        /// Disconnects the battery
        /// </summary>
        public void DisconnectBattery()
        {
            this.driver.SetOutputOff(this);
        }

        #endregion
    }
}
