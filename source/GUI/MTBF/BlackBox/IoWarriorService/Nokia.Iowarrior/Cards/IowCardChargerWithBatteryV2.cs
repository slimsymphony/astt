using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Nokia.Iowarrior.Cards
{
    public class IowCardChargerWithBatteryV2 : IowCard
    {
        private String[] chargerSelectionParameters = new String[] { "1", "2", "3", "4", "5", "6"};
        IowBits iowBits;
        Object thisLock = new Object();

        AD7995 ad7995;
        Double voltatgeToCurrentFactor = 0.448;

        public IowCardChargerWithBatteryV2()
            : base()
        {
        }

        public IowCardChargerWithBatteryV2(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation)
        {
            iowBits = IowDevice.ReadInputs();
            //Initialize ADCs
            ad7995 = new AD7995(IowDevice, 0x50, thisLock);
        }

        public override void Shutdown()
        {
            return;
        }

        public override void Reset()
        {
            return;
        }

        #region Command connect:charger
        public IList<String> Values_Connect_Charger
        {
            get { return chargerSelectionParameters; }
        }

        public IDictionary<String, Object> Execute_Connect_Charger(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                Int32 channelNumber = Convert.ToInt32(parameters[0]);

                iowBits = IowDevice.ReadInputs();
                switch (channelNumber) {
                    case 1:
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = false;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = false;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = false;
                        break;
                    case 2:
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = true;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = false;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = false;
                        break;
                    case 3:
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = false;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = true;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = false;
                        break;
                    case 4:
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = true;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = true;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = false;
                        break;
                    case 5:
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = false;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = false;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = true;
                        break;
                    case 6:
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = true;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = false;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = true;
                        break;
                }
                IowDevice.WriteOutputs(iowBits);
            }
            return EmptyResult;
        }
        #endregion

        #region Command disconnect:charger
        public IList<String> Values_Disconnect_Charger
        {
            get { return chargerSelectionParameters; }
        }

        public IDictionary<String, Object> Execute_Disconnect_Charger(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                Int32 channelNumber = Convert.ToInt32(parameters[0]);

                switch (channelNumber)
                {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        iowBits = IowDevice.ReadInputs();
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = true;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = true;
                        iowBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = true;
                        IowDevice.WriteOutputs(iowBits);
                        break;
                }

            }
            return EmptyResult;
        }
        #endregion

        #region Command connect:power
        public IDictionary<String, Object> Execute_Connect_Power(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                iowBits = IowDevice.ReadInputs();
                iowBits[IowDevice.TranslatePortNameToBitNumber("P4.7")] = true;
                iowBits[IowDevice.TranslatePortNameToBitNumber("P2.1")] = false;
                IowDevice.WriteOutputs(iowBits);
            }

            return EmptyResult;
        }
        #endregion

        #region Command disconnect:power
        public IDictionary<String, Object> Execute_Disconnect_Power(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                iowBits = IowDevice.ReadInputs();
                iowBits[IowDevice.TranslatePortNameToBitNumber("P4.7")] = true;
                iowBits[IowDevice.TranslatePortNameToBitNumber("P2.1")] = true;
                IowDevice.WriteOutputs(iowBits);
            }

            return EmptyResult;
        }
        #endregion

        #region Command connect:fps
        public IDictionary<String, Object> Execute_Connect_Fps(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                iowBits = IowDevice.ReadInputs();
                iowBits[IowDevice.TranslatePortNameToBitNumber("P4.7")] = false;
                iowBits[IowDevice.TranslatePortNameToBitNumber("P2.1")] = false;
                IowDevice.WriteOutputs(iowBits);
            }

            return EmptyResult;
        }
        #endregion

        #region Command disconnect:fps
        public IDictionary<String, Object> Execute_Disconnect_Fps(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt) {
                iowBits = IowDevice.ReadInputs();
                iowBits[IowDevice.TranslatePortNameToBitNumber("P4.7")] = true;
                iowBits[IowDevice.TranslatePortNameToBitNumber("P2.1")] = true;
                IowDevice.WriteOutputs(iowBits);
            }

            return EmptyResult;
        }
        #endregion

        #region Command connect:battery
        public IDictionary<String, Object> Execute_Connect_Battery(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt) {
                iowBits = IowDevice.ReadInputs();
                iowBits[IowDevice.TranslatePortNameToBitNumber("P4.7")] = false;
                iowBits[IowDevice.TranslatePortNameToBitNumber("P2.1")] = true;
                IowDevice.WriteOutputs(iowBits);
            }

            return EmptyResult;
        }
        #endregion

        #region Command disconnect:battery
        public IDictionary<String, Object> Execute_Disconnect_Battery(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt) {
                iowBits = IowDevice.ReadInputs();
                iowBits[IowDevice.TranslatePortNameToBitNumber("P4.7")] = true;
                iowBits[IowDevice.TranslatePortNameToBitNumber("P2.1")] = true;
                IowDevice.WriteOutputs(iowBits);
            }

            return EmptyResult;
        }
        #endregion

        #region Command connect:bsi
        public IDictionary<String, Object> Execute_Connect_Bsi(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P3.3"), false);
            return EmptyResult;
        }
        #endregion

        #region Command disconnect:bsi
        public IDictionary<String, Object> Execute_Disconnect_Bsi(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P3.3"), true);
            return EmptyResult;
        }

        #endregion

        #region Command close:discharge
        public IDictionary<String, Object> Execute_Close_Discharge(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt) {
                iowBits = IowDevice.ReadInputs();
                iowBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = false;
                iowBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = true;
                iowBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = true;
                IowDevice.WriteOutputs(iowBits);
            }

            return EmptyResult;
        }

        #endregion

        #region Command open:discharge
        public IDictionary<String, Object> Execute_Open_Discharge(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                iowBits = IowDevice.ReadInputs();
                iowBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = true;
                iowBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = true;
                iowBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = true;
                IowDevice.WriteOutputs(iowBits);
            }
            return EmptyResult;
        }
        #endregion

        #region Command Get:Powermeasurement
        public IDictionary<String, Object> Execute_Get_Powermeasurement(Boolean executeIt, IList<String> parameters)
        {
            Dictionary<String, Object> result = new Dictionary<String, Object>();

            if (executeIt)
            {
                PowerMeasurement measurement = GetPowerMeasurement();

                result["Voltage"] = measurement.Voltage;
                result["Current"] = measurement.Current;
            }
            return result;
        }

        private PowerMeasurement GetPowerMeasurement()
        {
            PowerMeasurement powerMeasurement = new PowerMeasurement(0, 0);
            powerMeasurement.Voltage = Math.Round(ad7995.ReadADCValue((byte)152), 2);

            if (powerMeasurement.Voltage > 3)
            {
                // Get charger current VIN1
                Double chargerVoltageVin1 = Math.Round(ad7995.ReadADCValue((byte)168), 3);
                Double chargerCurrentVin1 = (chargerVoltageVin1 * voltatgeToCurrentFactor) * -1;

                // Get current on VIN2
                Double voltageVin2 = Math.Round(ad7995.ReadADCValue((byte)200), 3);
                Double currentVin2 = voltageVin2 * voltatgeToCurrentFactor;

                if (currentVin2 > 0)
                {
                    powerMeasurement.Current = Math.Round(currentVin2 * 1000, 2);
                }
                else if (chargerCurrentVin1 < 0)
                {
                    powerMeasurement.Current = Math.Round(chargerCurrentVin1 * 1000, 2);
                }
            }

            return powerMeasurement;
        }
        #endregion
    }

    public class PowerMeasurement
    {
        public double Voltage { get; set; }
        public double Current { get; set; }

        public PowerMeasurement(double voltage, double current)
        {
            this.Voltage = voltage;
            this.Current = current;
        }
    }
}
