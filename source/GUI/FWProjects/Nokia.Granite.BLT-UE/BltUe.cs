using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.ServiceModel;
using System.Threading;
using System.Windows.Forms;
using TestAutomation.Gui.Marble.IPC.Interfaces;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;
using TestAutomation.Gui.Marble.IPC.Services;
using TestAutomation.Gui.Marble.Settings;
using Nokia.Tea.CommonFramework.Drivers;
using Nokia.Tea.CommonFramework.Rcms;
using Nokia.Tea.CoreFramework.BaseModules.TeaServiceModule;
using Nokia.Tea.CoreFramework.ModuleServices.Implementations;
using Nokia.Tea.CoreFramework.ToolBox.Implementations;
using Nokia.Tea.CoreFramework.ToolBox.Interfaces;
using Nokia.Tea.LowLevelDrivers.Implementations;
using Nokia.Tea.Rcms.TypeInterfaces.DCPowerSupplies;

namespace TestAutomation.Gui.Marble.Currentmeasurement
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single, ConcurrencyMode = ConcurrencyMode.Single)]
    public class BltUe : IBltUeService, IDisposable
    {
        #region Private Members

        private static BltUe instance;
        private static readonly object LockObject = new Object();
        private IToolBox teaToolBox;
        private LowLevelDriverVisaNi gpibDriver;
        private IRcmDcPowerSupply dcPowerSupply;
        private string connectionString;
        private MarbleWcfService service;

        #endregion

        #region Accessors

        /// <summary>
        /// Singleton instance for thread safety
        /// </summary>
        public static BltUe Instance
        {
            get
            {
                if (instance == null)
                {
                    lock (LockObject)
                    {
                        if (instance == null)
                        {
                            instance = new BltUe();
                        }
                    }
                }
                return instance;
            }
        }

        /// <summary>
        /// Returns true if BLT-UE is ready to be controlled.
        /// </summary>
        public bool IsBltUeReady { get; private set;}

        #endregion

        #region Constructors

        /// <summary>
        /// Private constructor for Singleton usage.
        /// </summary>
        private BltUe()
        {
            CultureInfo cultureInfo = new CultureInfo("en-US");

            Thread.CurrentThread.CurrentCulture = cultureInfo;
            Thread.CurrentThread.CurrentUICulture = cultureInfo;
            this.IsBltUeReady = false;
        }

        #endregion

        #region Public methods

        public void StartService(int servicePort = 8052)
        {
            // Initialize settingshandler object. If settings file was not found, use hardcoded default settings.
            BltUeServiceSettings s = null;
            const string filePath = @"..\settings\BltUeFwServiceSettings.xml";
            if (File.Exists(filePath))
            {
                SettingsHandler settingsHandler = new SettingsHandler(new BltUeServiceSettings(), filePath);
                s = settingsHandler.SettingsObject as BltUeServiceSettings;
            }

            if (s == null)
            {
                s = new BltUeServiceSettings();
            }

            s.ServicePort = servicePort;
            List<Tuple<Type, string>> endpoints = new List<Tuple<Type, string>>();
            endpoints.Add(new Tuple<Type, string>(typeof(IBltUeService), ServiceDefinitions.BltUeServiceEndpoint));

            try
            {
                this.service = new MarbleWcfService(this, s.ServicePort, endpoints);
            }
            catch (Exception e)
            {
                MessageBox.Show("Create WCF service for BLT-UE GUI service failed: " + Environment.NewLine + e.Message,
                                "BLT-UE WCF Service Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public void InitGpib()
        {
            this.connectionString = string.Empty;
            this.teaToolBox = new ToolBox();
            this.teaToolBox.Add(CoreServiceModuleKeys.ModuleService, new ModuleService(this.teaToolBox));

            // Create a new Tea configuration class instance for GPIB driver configuration
            LowLevelDriverVisaNiConfiguration gpibDriverConfiguration = new LowLevelDriverVisaNiConfiguration();
            this.teaToolBox.ModuleService.AddModule("GpibDriverConfiguration", gpibDriverConfiguration);

            string[] resources = null;
            try
            {
                // Create a new Tea LowLevelDriver instance. Pass in this.teaToolBox so the driver founds it's configuration
                this.gpibDriver = new LowLevelDriverVisaNi("GpibDriver", this.teaToolBox);

                // Add the actual Tea LowLevelDriver to Tea Module Service
                this.teaToolBox.ModuleService.AddModule("GpibDriver", gpibDriver);
                resources = gpibDriver.DetectResources();
            }
            catch (Exception ex)
            {
                if (ex is FileNotFoundException || (ex.InnerException != null && ex.InnerException is FileNotFoundException))
                {
                    this.IsBltUeReady = false;
                    throw new FaultException("NI Error: Unable to load NI Visa driver. Please refer to Marble wiki for National Instruments Visa driver installation.");
                }
            }

            List<string> gpibResources = resources.Where(res => res.StartsWith("GPIB")).ToList();
            if (gpibResources.Count == 0)
            {
                this.IsBltUeReady = false;
                throw new FaultException("GPIB Error: No GPIB adapter(s) detected! Check your HW configuration.");
            }

            int failCount = 0;
            List<string> gpibAdaptersFound = new List<string>();
            List<string> failList = new List<string>();
            foreach (string res in gpibResources)
            {
                try
                {
                    this.gpibDriver.OpenMessageBasedSession(res);
                    string deviceId = this.gpibDriver.QueryUsingMessageBasedSession("*IDN?");
                    if ((deviceId.ToUpper().Contains("AGILENT") || deviceId.ToUpper().Contains("HEWLETT")) && (deviceId.Contains("663") || deviceId.Contains("661")))
                    {
                        this.connectionString = res;
                        return;
                    }
                }
                catch (InvalidCastException)
                {
                    gpibAdaptersFound.Add(res);
                    failCount++;
                }
                catch (Exception ex)
                {
                    failCount++;
                    failList.Add(ex.Message);
                }
            }
            if (failCount == gpibResources.Count && string.IsNullOrEmpty(this.connectionString))
            {
                string adapterString = gpibAdaptersFound.Aggregate(string.Empty, (current, adapter) => current + (adapter + ", "));
                if (adapterString.EndsWith(", "))
                {
                    adapterString = adapterString.Remove(adapterString.LastIndexOf(','), adapterString.Length - adapterString.LastIndexOf(','));
                }
                this.IsBltUeReady = false;
                throw new FaultException("GPIB Error: No connected GPIB devices detected! Following GPIB adapter(s) detected: " + adapterString + ". Check your HW configuration.");
            }
            if (gpibResources.Count > failCount && string.IsNullOrEmpty(this.connectionString))
            {
                this.IsBltUeReady = false;
                throw new FaultException("No Agilent 663X series GPIB controller detected! Check your HW configuration.");
            }
            if (failList.Count > 0)
            {
                string failString = failList.Aggregate(string.Empty, (current, fail) => current + (fail + ", "));
                if (failString.EndsWith(", "))
                {
                    failString = failString.Remove(0, failString.LastIndexOf(','));
                }
                this.IsBltUeReady = false;
                throw new FaultException("GPIB Error: " + failString);
            }
        }

        public void InitPsu()
        {
            // Create a new Tea configuration class instance for DcPowerSupply driver configuration
            DriverDcPowerSupplyAgilent663XxxConfiguration psuDriverConfiguration = new DriverDcPowerSupplyAgilent663XxxConfiguration();
            psuDriverConfiguration.ConnectionString = this.connectionString;
            psuDriverConfiguration.SafetyMaxVoltageLimit = 4.26;
            psuDriverConfiguration.SafetyMaxCurrentLimit = 2.0;
            psuDriverConfiguration.CurrentLimitValue = 2.0;
            psuDriverConfiguration.VoltageLimitValue = 4.26;
            psuDriverConfiguration.OverCurrentProtectionState = false;
            psuDriverConfiguration.VisaDriverName = "GpibDriver";
            this.teaToolBox.ModuleService.AddModule("PsuDriverConfiguration", psuDriverConfiguration);

            // Create a new Tea Driver instance. Pass in this.teaToolBox so the driver founds it's configuration
            DriverDcPowerSupplyAgilent663Xxx psuDriver = new DriverDcPowerSupplyAgilent663Xxx("PsuDriver", this.teaToolBox);

            // Add the actual Tea Driver to Tea Module Service
            this.teaToolBox.ModuleService.AddModule("PsuDriver", psuDriver);


            // Create a new Tea configuration class instance for Psu RCM configuration
            RcmDcPowerSupplyAgilent663XxxConfiguration rcmConfiguration = new RcmDcPowerSupplyAgilent663XxxConfiguration();
            rcmConfiguration.UsedDriverUid = "PsuDriver";
            this.teaToolBox.ModuleService.AddModule("PsuRcmConfiguration", rcmConfiguration);

            // Create a new Tea RCM instance. Pass in this.teaToolBox so the RCM founds it's configuration
            this.dcPowerSupply = new RcmDcPowerSupplyAgilent663Xxx("PsuRcm", this.teaToolBox);

            // Add the actual Tea Rcm to Tea Module Service
            this.teaToolBox.ModuleService.AddModule("PsuRcm", this.dcPowerSupply);

            this.dcPowerSupply.InitAtStartTest();

            // Set BLT-UE default voltage to DUT
            double outputVoltage = -1;
            try
            {
                dynamic settings = SettingsManager.Instance;
                outputVoltage = settings.TestRun.BLTUEOutputVoltage;
            }
            catch {}
            if (outputVoltage < 0)
                this.dcPowerSupply.ConfigureVoltageLimit(3.83);
            else
                this.dcPowerSupply.ConfigureVoltageLimit(outputVoltage);

            this.dcPowerSupply.SetOutputOn();
            this.IsBltUeReady = true;
        }

        public double MeasureCurrent()
        {
            return this.dcPowerSupply.MeasureAvgCurrent();
        }

        public void SetVoltage(double voltage)
        {
            this.dcPowerSupply.ConfigureVoltageLimit(voltage);
        }

        public void Disconnect()
        {
            this.dcPowerSupply.SetOutputOff();
        }

        public void Dispose()
        {
            if (this.service != null)
            {
                try
                {
                    this.service.Dispose();
                    this.service = null;
                }
                catch { /* Nothing to do... We are closing anyway. GC should handle this if Dispose fails */ }
            }

            if (this.gpibDriver != null)
            {
                try
                {
                    this.gpibDriver.Dispose();
                    GC.SuppressFinalize(this.gpibDriver);
                }
                catch
                {
                    /* Nothing to do... We are closing anyway. GC should handle this if Dispose fails */
                }
            }
        }

        #endregion
    }
}
