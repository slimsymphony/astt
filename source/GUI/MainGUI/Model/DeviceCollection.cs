using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Runtime.CompilerServices;
using System.Text.RegularExpressions;
using System.Reflection;
using System.Threading;
using System.Net.Sockets;
using System.Net;
using System.IO;
using System.Windows;
using System.Windows.Threading;
using MarbleLibrary.CustomControls;

namespace Marble.Model
{
    /// <summary>
    /// 
    /// </summary>
    internal static class Extensions
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="dict"></param>
        /// <param name="dict2"></param>
        /// <returns></returns>
        public static bool IsSame(this Dictionary<string, string> dict, Dictionary<string, string> dict2)
        {
            if (dict == null && dict2 == null)
                return true;

            if (dict == null || dict2 == null)
                return false;

            if (dict.Count != dict2.Count)
                return false;

            return dict.Keys.All(key => dict2.ContainsKey(key) && String.CompareOrdinal(dict[key], dict2[key]) == 0);
        }

        /// <summary>
        /// Gets the string from a byte array.
        /// </summary>
        /// <param name="bytes">The bytes.</param>
        /// <param name="index">The index.</param>
        /// <param name="count">The count.</param>
        /// <param name="encoding">The encoding.</param>
        /// <returns></returns>
        public static string GetString(this byte[] bytes, int index, int count, Encoding encoding)
        {
            return encoding.GetString(bytes, index, count);
        }

        /// <summary>
        /// Gets the string from a byte array.
        /// </summary>
        /// <param name="bytes">The bytes.</param>
        /// <param name="index">The index.</param>
        /// <param name="count">The count.</param>
        /// <param name="encoding">The encoding.</param>
        /// <returns></returns>
        public static string GetString(this byte[] bytes, int index, int count, string encoding)
        {
            Encoding enc = Encoding.GetEncoding(encoding);
            return GetString(bytes, index, count, enc);
        }

        /// <summary>
        /// Gets the bytes from a string.
        /// </summary>
        /// <param name="str">The string.</param>
        /// <returns></returns>
        public static byte[] GetBytes(this string str)
        {
            return GetBytes(str, Encoding.Default);
        }

        /// <summary>
        /// Gets the bytes from a string.
        /// </summary>
        /// <param name="str">The string.</param>
        /// <param name="encoding">The encoding.</param>
        /// <returns></returns>
        public static byte[] GetBytes(this string str, Encoding encoding)
        {
            return encoding.GetBytes(str);
        }

        /// <summary>
        /// Gets the bytes from a string.
        /// </summary>
        /// <param name="str">The string.</param>
        /// <param name="encoding">The encoding.</param>
        /// <returns></returns>
        public static byte[] GetBytes(this string str, string encoding)
        {
            Encoding enc = Encoding.GetEncoding(encoding);
            return GetBytes(str, enc);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sck"></param>
        /// <param name="wait"></param>
        public static void Close(this Socket sck, bool wait)
        {
            if (!wait)
            {
                sck.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, new LingerOption(true, 0));
            }
            sck.Close();
        }
    }

    /// <summary>
    /// Helper class for simplifying the implementation of interface INotifyPropertyChanged.
    /// </summary>
    [AttributeUsage(AttributeTargets.Property)]
    internal class Notify : Attribute { }

    /// <summary>
    /// Represents information about a device (emulator or hardware) connected to ADB (Android Development Bridge).
    /// </summary>
    public class DeviceInfo : INotifyPropertyChanged
    {
        // Example values from both HW and emulator
        private const string RE_EMU = @"emulator-(\d+)";
        private const string BUILD_LABEL = "ro.build.version.release"; // 4.1.2, 4.3
        private const string SDK_LABEL = "ro.build.version.sdk"; // 16, 18
        private const string BUILD_DATE_LABEL = "ro.build.date.utc"; // 1382514931
        private const string FIRST_BOOT_LABEL = "ro.runtime.firstboot"; // 315964833171
        private const string HARDWARE_LABEL = "ro.hardware"; // qcom, goldfish
        //private const string PRODUCT_LABEL = "ro.product.name"; // msm8625, nokia_emu
        private const string PRODUCT_LABEL = "ro.build.product"; // Ara
        //private const string MODEL_LABEL = "ro.product.model"; // RM-980, nokia generic emulator config
        private const string MODEL_LABEL = "ro.product.usb.name"; // generic model (RM-1013)
        //private const string BAND_LABEL = "ro.boot.bom"; // rel1.db.ds
        
        //private const string DEVICE_LABEL = "ro.product.device"; // msm8625, generic

        // Exists only in HW
        //private const string SW_VERSION_LABEL = "apps.setting.product.swversion"; // 0.1342.031
        private const string SW_VERSION_LABEL = "apps.setting.product.outswver"; // eng.ourbu039.20140217.060741
        private const string HW_BUILD_ID_LABEL = "ro.product.hw.id"; // 0203
        //private const string IMEI1_LABEL = "ro.ril.deviceID"; // 004402475312082
        //private const string IMEI2_LABEL = "ro.ril.deviceID1"; // 004402475312090
        private const string IMEI1_LABEL = "ro.device.imei"; // 004402475312082
        private const string IMEI2_LABEL = "ro.device.imei2"; // 004402475312090

        //private const string SIM_OPERATOR_NAME_LABEL = "gsm.sim.operator.alpha"; // elisa
        //private const string SIM_OPERATOR_COUNTRY = "gsm.sim.operator.iso-country"; // fi
        //private const string SIM_OPERATOR_CODE = "gsm.sim.operator.numeric"; // 24405
        //private const string SIM_STATE = "gsm.sim.state"; // READY

        private const string SIM_OPERATOR_NAME_LABEL = "gsm.operator.alpha"; // [NOKIA,elisa]
        private const string SIM_OPERATOR_COUNTRY = "gsm.operator.iso-country"; // [fi,fi]
        private const string SIM_OPERATOR_CODE = "gsm.operator.numeric"; // [24407,24405]
        private const string SIM_STATE = "gsm.sim.state"; // [READY,READY]

        //private const string SIM2_OPERATOR_NAME_LABEL = "gsm.sim2.operator.alpha"; // NOKIA
        //private const string SIM2_OPERATOR_COUNTRY = "gsm.sim2.operator.iso-country"; // fi
        //private const string SIM2_OPERATOR_CODE = "gsm.sim2.operator.numeric"; // 24407
        //private const string SIM2_STATE = "gsm.sim2.state"; // READY

        private DeviceState mState;
        private Dictionary<string, string> mProperties;

        /// <summary>
        /// Instantiates new DeviceInfo with empty properties and State=Unknown.
        /// </summary>
        internal DeviceInfo()
        {
            mState = DeviceState.Unknown;
            mProperties = new Dictionary<string, string>();
        }

        private bool isMain;

        /// <summary>
        /// Indicates whether this device is selected as the main phone.
        /// </summary>
        public bool IsMain
        {
            get { return isMain; }
            set
            {
                if (isMain == value) return;

                isMain = value;
                this.NotifyPropertyChanged();
            }
        }

        private int mainIndex;

        /// <summary>
        /// Sequence number of this main phone among all the main phones.
        /// </summary>
        public int MainIndex
        {
            get { return mainIndex; }
            set
            {                
                if (mainIndex == value) return;

                mainIndex = value;
                this.NotifyPropertyChanged();
            }
        }

        /// <summary>
        /// Returns true when State is Online otherwise false is returned.
        /// </summary>
        public bool IsOnline
        {
            get { return State == DeviceState.Online; }
        }

        /// <summary>
        /// Device identifier e.g. "1a306d4" for HW and "emulator-5554" for emulator.
        /// </summary>
        public string SerialNumber { get; internal set; }

        /// <summary>
        /// Gets SW version, null if not available. e.g. 0.1342.031
        /// </summary>
        [Notify]
        public string SWVersion
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(SW_VERSION_LABEL))                
                    return Properties[SW_VERSION_LABEL];

                return null;
            }
        }

        /// <summary>
        /// Gets HWID, null if not available. e.g. 0203
        /// </summary>
        [Notify]
        public string HWVersion
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(HW_BUILD_ID_LABEL))
                    return Properties[HW_BUILD_ID_LABEL];

                return null;
            }
        }

        /// <summary>
        /// Gets IMEI (International Mobile Equipment Identity) number of the primary radio, null if not available. e.g. 004402475312082
        /// </summary>
        [Notify]
        public string IMEI1
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(IMEI1_LABEL))
                    return Properties[IMEI1_LABEL];

                return null;
            }
        }

        /// <summary>
        /// Gets IMEI (International Mobile Equipment Identity) number of the secondary radio, null if not available. e.g. 004402475312082
        /// </summary>
        [Notify]
        public string IMEI2
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(IMEI2_LABEL))
                    return Properties[IMEI2_LABEL];

                return null;
            }
        }

        /// <summary>
        /// Gets the operator name of the primary SIM card, null if not available. e.g. "elisa"
        /// </summary>
        [Notify]
        public string SIM1OperatorName
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(SIM_OPERATOR_NAME_LABEL))
                    // Values for both sims are stored in the same element a list [NOKIA,elisa]
                    return Properties[SIM_OPERATOR_NAME_LABEL].Split(new[] { ',' })[0];

                return null;
            }
        }

        /// <summary>
        /// Gets the operator country abbreviation (ISO format) of the primary SIM card, null if not available. e.g. "fi"
        /// </summary>
        [Notify]
        public string SIM1OperatorCountry
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(SIM_OPERATOR_COUNTRY))
                    return Properties[SIM_OPERATOR_COUNTRY].Split(new[] { ',' })[0];


                return null;
            }
        }

        /// <summary>
        /// Gets the operator code (MCC + MNC) of the primary SIM card, null if not available. e.g. 24405
        /// </summary>
        [Notify]
        public string SIM1OperatorCode
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(SIM_OPERATOR_CODE))
                    return Properties[SIM_OPERATOR_CODE].Split(new[] { ',' })[0];

                return null;
            }
        }

        // TODO: What other states are available?
        /// <summary>
        /// Gets the state of the primary SIM card, null if not available. e.g. READY
        /// </summary>
        [Notify]
        public string SIM1State
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(SIM_STATE))
                    return Properties[SIM_STATE].Split(new[] { ',' })[0];

                return null;
            }
        }

        /// <summary>
        /// Gets the operator name of the secondary SIM card, null if not available. e.g. "elisa"
        /// </summary>
        [Notify]
        public string SIM2OperatorName
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(SIM_OPERATOR_NAME_LABEL))
                {
                    string value = Properties[SIM_OPERATOR_NAME_LABEL];
                    if (value.Contains(","))
                        return value.Split(new[] { ',' })[1].Trim();
                }

                return null;
            }
        }

        /// <summary>
        /// Gets the operator country abbreviation (ISO format) of the secondary SIM card, null if not available. e.g. "fi"
        /// </summary>
        [Notify]
        public string SIM2OperatorCountry
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(SIM_OPERATOR_COUNTRY))
                {
                    string value = Properties[SIM_OPERATOR_COUNTRY];
                    if (value.Contains(","))
                        return value.Split(new[] { ',' })[1].Trim();
                }

                return null;
            }
        }

        /// <summary>
        /// Gets the operator code (MCC + MNC) of the secondary SIM card, null if not available. e.g. 24405
        /// </summary>
        [Notify]
        public string SIM2OperatorCode
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(SIM_OPERATOR_CODE))
                {
                    string value = Properties[SIM_OPERATOR_CODE];
                    if (value.Contains(","))
                        return value.Split(new[] { ',' })[1].Trim();
                }

                return null;
            }
        }

        /// <summary>
        /// Gets the state of the secondary SIM card, null if not available. e.g. READY
        /// </summary>
        [Notify]
        public string SIM2State
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(SIM_STATE))
                {
                    string value = Properties[SIM_STATE];
                    if (value.Contains(","))
                        return value.Split(new[] { ',' })[1].Trim();
                }

                return null;
            }
        }

        /// <summary>
        /// Gets platform SW version, null if not available. e.g. 4.1.2 or 4.3
        /// </summary>
        [Notify]
        public Version PlatformVersion
        {
            get
            {
                Version version;
                if (Properties != null && Properties.ContainsKey(BUILD_LABEL) && Version.TryParse(Properties[BUILD_LABEL], out version))
                {
                    return version;
                }
                return null;
            }
        }

        /// <summary>
        /// Gets SDK version, null if not available. e.g. 16 or 18
        /// </summary>
        [Notify]
        public int? SdkVersion
        {
            get
            {
                int version;
                if (Properties != null && Properties.ContainsKey(SDK_LABEL) && int.TryParse(Properties[SDK_LABEL], out version))
                {
                    return version;
                }
                return null;
            }
        }

        /// <summary>
        /// Gets manufacturer of the HW, "Unknown" if not available. e.g. qcom or goldfish
        /// </summary>
        [Notify]
        public string HWType
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(HARDWARE_LABEL))
                {
                    return Properties[HARDWARE_LABEL];
                }
                return "Unknown";
            }
        }

        /// <summary>
        /// Gets the software build date and time, null if not available. e.g. 10/29/2013 2:43:56 PM
        /// </summary>
        [Notify]
        public DateTime? SWBuildDate
        {
            get
            {
                double date;
                if (Properties != null && Properties.ContainsKey(BUILD_DATE_LABEL) && double.TryParse(Properties[BUILD_DATE_LABEL], out date))
                    return UnixTimeStampToDateTime(date * 1000);

                return null;
            }
        }

        /// <summary>
        /// Gets the date and time of the first software boot, null if not available. e.g. 11/4/2013 11:44:44 AM
        /// </summary>
        [Notify]
        public DateTime? SWFirstBoot
        {
            get
            {
                double date;
                if (Properties != null && Properties.ContainsKey(FIRST_BOOT_LABEL) && double.TryParse(Properties[FIRST_BOOT_LABEL], out date))
                    return UnixTimeStampToDateTime(date);

                return null;
            }
        }

        /// <summary>
        /// Returns true if the device is emulator, otherwise false is returned.
        /// </summary>
        [Notify]
        public bool IsEmulator
        {
            get
            {
                return !string.IsNullOrEmpty(this.SerialNumber) && Regex.IsMatch(SerialNumber, RE_EMU, RegexOptions.Compiled | RegexOptions.IgnoreCase);
            }
        }

        /// <summary>
        /// Gets the product name, null if not available. .e.g msm8625 or nokia_emu
        /// </summary>
        [Notify]
        public string ProductName
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(PRODUCT_LABEL))
                {
                    return Properties[PRODUCT_LABEL];
                }
                return null;
            }
        }

        /// <summary>
        /// Gets the RM-code of the product, null if not available. e.g. RM-980
        /// </summary>
        [Notify]
        public string ProductModel
        {
            get
            {
                if (Properties != null && Properties.ContainsKey(MODEL_LABEL))
                {
                    return Properties[MODEL_LABEL];
                }
                return null;
            }
        }


        /// <summary>
        /// Current state of the device. Usually Online or Offline.
        /// </summary>
        public DeviceState State
        {
            get { return mState; }
            internal set
            {
                if (mState != value)
                {
                    mState = value;
                    NotifyPropertyChanged();
                    NotifyPropertyChanged("IsOnline");
                }
            }
        }

        /// <summary>
        /// All the available properties gotten via adb.
        /// </summary>
        public Dictionary<string, string> Properties
        {
            get { return mProperties; }
            internal set
            {
                if (!mProperties.IsSame(value))
                {
                    mProperties = value;
                    NotifyPropertyChanged();
                    NotifyProperties();
                }
            }
        }

        /// <summary>
        /// Returns a listing of most important properties and their values.
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            var properties = new Dictionary<string, string>
                {
                    { "Serial", this.SerialNumber},
                    { "Device", this.IsEmulator ? "Emulator" : "Hardware" },
                    { "State", this.State.ToString() },
                    { "SWVersion", this.SWVersion },
                    { "BuildDate", this.SWBuildDate != null ? this.SWBuildDate.ToString() : string.Empty },
                    { "HWType", this.HWType },
                    { "HWID", this.HWVersion },
                    { "IMEI1", this.IMEI1 },
                    { "IMEI2", this.IMEI2 },
                    { "PlatformVersion", this.PlatformVersion != null ? this.PlatformVersion.ToString() : string.Empty },
                    { "SdkVersion", this.SdkVersion != null ? this.SdkVersion.ToString() : string.Empty},
                    { "SIM1Status", this.SIM1State },
                    { "SIM1Operator", this.SIM1OperatorName },
                    { "SIM1Country", this.SIM1OperatorCountry },
                    { "SIM2Status", this.SIM2State },
                    { "SIM2Operator", this.SIM2OperatorName },
                    { "SIM2Country", this.SIM2OperatorCountry },
                };

            var strBuilder = new StringBuilder();
            foreach (var item in properties)
                strBuilder.Append(string.Format("{0}: {1}{2}", item.Key, item.Value, Environment.NewLine));

            return strBuilder.ToString();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        public override bool Equals(object obj)
        {
 	        if (obj is DeviceInfo)
                return String.Compare((obj as DeviceInfo).SerialNumber, SerialNumber, StringComparison.OrdinalIgnoreCase) == 0;
            
            return false;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        /// <summary>
        /// Implements INotifyPropertyChanged.
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Implements INotifyPropertyChanged.
        /// </summary>
        /// <param name="propertyName">Defaults to the name of the caller method or caller property.</param>
        private void NotifyPropertyChanged([CallerMemberName] string propertyName = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        /// <summary>
        /// Triggers PropertyChanged event for all properties of this class marked with Notify tag.
        /// </summary>
        private void NotifyProperties()
        {
            foreach (var prop in GetType().GetProperties(BindingFlags.Public|BindingFlags.Instance))
            {
                if (prop.GetCustomAttribute<Notify>() != null)
                    NotifyPropertyChanged(prop.Name);
            }
        }

        /// <summary>
        /// Converts time in milliseconds to DateTime object (in local format).
        /// </summary>
        /// <param name="unixTimeStamp">Time in milliseconds.</param>
        /// <returns></returns>
        private DateTime UnixTimeStampToDateTime(double unixTimeStamp)
        {
            // Unix timestamp is seconds past epoch
            return new DateTime(1970, 1, 1, 0, 0, 0, 0).AddMilliseconds(unixTimeStamp).ToLocalTime();
        }
    }

    /// <summary>
    /// Maintains up-to-date information about all the connected devices.
    /// Connects (with DeviceListener) to socket channel provided by ADB (Android Development Bridge).
    /// Changes in device connection, status or other information are updated to collection.
    /// </summary>
    public class DeviceCollection : ObservableCollection<DeviceInfo>, IDisposable
    {
        private DeviceListener mListener;
        private bool mIsDisposed;
        private readonly Dispatcher mainDispatcher;

        /// <summary>
        /// Creates new instance of DeviceCollection.
        /// Reference to the dispatcher object of the caller is stored.
        /// So future modifications to the collection can be executed in that context.
        /// Instantiates also new DeviceListener.
        /// </summary>
        public DeviceCollection()
        {
            mainDispatcher = Application.Current.Dispatcher;
            mListener = new DeviceListener(this);
        }

        /// <summary>
        /// Disposes previous device listener and creates a new device listener instance.
        /// Can be used when connection to adb service is lost.
        /// </summary>
        public void ReCreateListener()
        {
            if (mListener != null)
                mListener.Dispose();

            this.isAdbConnected = false;
            mListener = new DeviceListener(this);
        }

        private bool isAdbConnected;

        /// <summary>
        /// Indicates whether device listener is correctly connected to ADB server and providing device updates.
        /// </summary>
        public bool IsAdbConnected
        {
            get { return this.isAdbConnected; }

            set
            {
                if (this.isAdbConnected == value) return;

                this.isAdbConnected = value;
                this.OnPropertyChanged(new PropertyChangedEventArgs("IsAdbConnected"));
                this.OnPropertyChanged(new PropertyChangedEventArgs("TooltipText"));
            }
        }

        private string adbVersion = string.Empty;

        /// <summary>
        /// Version number of the ADB server currently (or lastly) connected to.
        /// </summary>
        public string AdbVersion
        {
            get { return this.adbVersion; }

            set
            {
                if (this.adbVersion == value) return;

                this.adbVersion = value;
                this.OnPropertyChanged(new PropertyChangedEventArgs("AdbVersion"));
                this.OnPropertyChanged(new PropertyChangedEventArgs("TooltipText"));
            }
        }

        /// <summary>
        /// Tooltip of the button for re-creating device listener.
        /// </summary>
        public string TooltipText
        {
            get
            {
                return string.Format("Re-creates the device listener and ADB server if it's not running.\n" +
                                     "ADB version: {0}{2}\n" +
                                     "Connected: {1}",
                                     this.AdbVersion, this.IsAdbConnected, this.adbVersion == "0.4.0.29" ? " (for Normandy)" : string.Empty);
            }
        }

        /// <summary>
        /// Device that is currently selected as the main device.
        /// </summary>
        public DeviceInfo MainConnection
        {
            get { return this.FirstOrDefault(d => d.IsMain && d.MainIndex==1); }
        }

        /// <summary>
        /// 
        /// </summary>
        public void Refresh()
        {
            mListener.GetDevices();
        }

        /// <summary>
        /// Automatically selects the main device to use if main device is not already set.
        /// This method is a wrapper to forward calls from other threads to main dispacther for execution.
        /// </summary>
        public void AutoSelectMainDevice()
        {
            mainDispatcher.Invoke(DispatcherPriority.Normal,
                (ThreadStart)(this.AutoSelectMainDevicePrivate)
                );
        }

        /// <summary>
        /// Automatically selects the main device to use if main device is not already set.
        /// </summary>
        private void AutoSelectMainDevicePrivate()
        {
            if (this.MainConnection != null) return;

            int hwDeviceCount = this.Count(d => !d.IsEmulator);
            DeviceInfo selectedDevice = null;

            // Auto select hw device if only one hw device is connected
            if (hwDeviceCount == 1)
                selectedDevice = this.FirstOrDefault(d => !d.IsEmulator);

            // Auto select emulator if no hw devices are connected and only one emulator is connected
            else if (hwDeviceCount == 0 && this.Count(d => d.IsEmulator) == 1)
                selectedDevice = this.FirstOrDefault(d => d.IsEmulator);

            if (selectedDevice == null) return;

            selectedDevice.IsMain = true;     
        }

        /// <summary>
        /// Adds new device to the collection. Registers to property changed events of the added device.
        /// Selects added device as main device if it was recently used as main.
        /// </summary>
        /// <param name="device"></param>
        public new void Add(DeviceInfo device)
        {
            if (device == null || this.Any(d => d.Equals(device))) return;

            base.Add(device);
            device.PropertyChanged += DeviceOnPropertyChanged;
        }

        /// <summary>
        /// Unsets IsMain for all other devices if some device is set as main.
        /// Also stores the serial number of the main device to RecentMainDevice property.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="eventArgs"></param>
        private void DeviceOnPropertyChanged(object sender, PropertyChangedEventArgs eventArgs)
        {
            if (eventArgs.PropertyName != "IsMain") return;

            var changedDevice = sender as DeviceInfo;
            if (changedDevice == null) return;

            // Device was unset from bein main phone
            if (!changedDevice.IsMain)
            {
                // Decrease main index from other main devices after this
                foreach (var device in this.Items.Where(d => d.IsMain && d.MainIndex > changedDevice.MainIndex))
                    device.MainIndex--;

                // Remove device if it disconnected (and no longer main phone)
                if (changedDevice.State == DeviceState.Disconnected)
                    this.Remove(changedDevice);
                else
                    changedDevice.MainIndex = 0;
            }
            else
            {
                // Set main index (Max call causes exception on empty sequence)
                changedDevice.MainIndex = this.Any() ? this.Max(d => d.MainIndex) + 1 : 1;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="device"></param>
        public new void Remove(DeviceInfo device)
        {
            if (device == null || !this.Any(d => d.Equals(device))) return;

            device.PropertyChanged -= DeviceOnPropertyChanged;
            base.Remove(device);
        }

        public new void Clear()
        {
            foreach (var deviceInfo in Items)
                deviceInfo.PropertyChanged -= DeviceOnPropertyChanged;
            base.Clear();
        }

        private string errorDescription;

        public string ErrorDescription
        {
            get { return errorDescription; }
            set
            {
                if (value == errorDescription) return;

                errorDescription = value;
                this.OnPropertyChanged(new PropertyChangedEventArgs("ErrorDescription"));
            }
        }

        private Exception errorException;

        public Exception ErrorException
        {
            get { return errorException; }
            set
            {
                if (value == errorException) return;

                errorException = value;
                this.OnPropertyChanged(new PropertyChangedEventArgs("ErrorException"));
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void Dispose()
        {
            if (mIsDisposed) return;

            mListener.Dispose();
            Clear();
            mIsDisposed = true;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    internal class DeviceListener : IDisposable
    {
        private const int DEFAULT_ADB_PORT = 5037;
        private const string DEFAULT_ENCODING = "ISO-8859-1";

        private readonly DeviceCollection mCollection;
        private Thread mEventListenerThread;
        private Socket mEventListenerSocket;
        private bool errorMessageDisplayed;

        private static readonly object mFetchLocker = new object();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="collection"></param>
        internal DeviceListener(DeviceCollection collection)
        {
            mCollection = collection;
            StartListenDeviceEvents();
        }

        /// <summary>
        /// 
        /// </summary>
        internal bool IsListening
        {
            get;
            private set;
        }

        /// <summary>
        /// 
        /// </summary>
        internal void GetDevices()
        {
            GetDevices(new IPEndPoint(IPAddress.Loopback, DEFAULT_ADB_PORT));
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="address"></param>
        internal void GetDevices(IPEndPoint address)
        {
            if (!IsListening)
                StartListenDeviceEvents();

            lock (mFetchLocker)
            {
                const string REQ = "host:devices";

                byte[] request = FormAdbRequest(REQ);
                using (var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                {
                    try
                    {
                        socket.SendTimeout = 5000;
                        socket.Connect(address);
                        socket.Blocking = true;

                        if (!Write(socket, request))
                        {
                            return;
                        }

                        var data = new byte[4];
                        var len = socket.Receive(data);

                        if (len <= 0)
                        {
                            return;
                        }

                        var resp = data.GetString(0, len, DEFAULT_ENCODING);

                        if (String.Compare(resp, "OKAY", StringComparison.OrdinalIgnoreCase) != 0)
                        {
                            return;
                        }

                        len = socket.Receive(data);

                        if (len <= 0)
                        {
                            return;
                        }

                        var hex = data.GetString(0, len, DEFAULT_ENCODING);

                        int chCount;
                        if (!int.TryParse(hex, System.Globalization.NumberStyles.HexNumber, null, out chCount))
                        {
                            return;
                        }

                        data = new byte[chCount];

                        len = socket.Receive(data);

                        if (len != chCount)
                        {
                            return;
                        }

                        var devices = new List<DeviceInfo>();

                        data.GetString(0, chCount, DEFAULT_ENCODING).Split(new[] { "\r\n", "\n" }, StringSplitOptions.RemoveEmptyEntries).ToList().ForEach(d =>
                        {
                            var re = new Regex(@"^([^\s]+)\s+(device|offline|unknown|bootloader|recovery|download).*$", RegexOptions.Compiled | RegexOptions.IgnoreCase);
                            Match m = re.Match(d);
                            if (m.Success)
                            {
                                var serial = m.Groups[1].Value;
                                var state = m.Groups[2].Value;

                                if (String.Compare(state, "device", StringComparison.OrdinalIgnoreCase) == 0)
                                {
                                    state = "online";
                                }

                                DeviceState ds;
                                if (Enum.TryParse(state, true, out ds))
                                {
                                    var device = new DeviceInfo {SerialNumber = serial, State = ds};
                                    if (device.State != DeviceState.Offline)
                                    {
                                        device.Properties = GetProperties(device.SerialNumber) ?? new Dictionary<string, string>();
                                    }
                                    devices.Add(device);
                                }
                            }
                        });
                        Refresh(devices);
                    }
                    catch (SocketException)
                    {
                        mCollection.IsAdbConnected = false;
                        this.Refresh(new List<DeviceInfo>());
                    }
                    finally
                    {
                        socket.Close(false);
                    }
                }
            }
        }

        /// <summary>
        /// Updates DeviceCollection with given devices.
        /// </summary>
        /// <param name="devices">List of currently connected devices</param>
        private void Refresh(List<DeviceInfo> devices)
        {
            // Remove previous device records that are not valid anymore
            foreach (var record in mCollection.ToList())
            {
                if (!devices.Exists(d => String.Compare(d.SerialNumber, record.SerialNumber, StringComparison.OrdinalIgnoreCase) == 0))
                {
                    if (record.IsMain)
                        record.State = DeviceState.Disconnected;
                    else
                        mCollection.Remove(record);
                }
            }

            // Add or update currently connected devices
            foreach (var device in devices)
            {
                var ext = mCollection.FirstOrDefault(d => String.Compare(d.SerialNumber, device.SerialNumber, StringComparison.OrdinalIgnoreCase) == 0);
                if (ext != null)
                {
                    ext.State = device.State;
                    ext.Properties = device.Properties;
                }
                else
                {
                    mCollection.Add(device);
                }
            }
        }

        /// <summary>
        /// Queries the version of the currently running ADB server.
        /// "OKAY0004001f" = 0.4.0.31 (Ara)
        /// "OKAY0004001d" = 0.4.0.29 (Normandy)
        /// </summary>
        /// <returns></returns>
        private string GetAdbVersion()
        {
            const int MAX_RETRY_COUNT = 2;

            var address = new IPEndPoint(IPAddress.Loopback, DEFAULT_ADB_PORT);
            var request = FormAdbRequest("host:version");
            Socket socket = null;

            int retryCount = 0;
            while (retryCount <= MAX_RETRY_COUNT)
            {
                try
                {
                    socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp)
                        {
                            Blocking = true,
                            SendTimeout = 5000
                        };

                    socket.Connect(address);

                    if (!Write(socket, request)) throw new SocketException(0);

                    var data = new byte[12];
                    socket.Receive(data);

                    return string.Format("{0}.{1}.{2}.{3}",
                                         Convert.ToInt32(data.GetString(4, 2, DEFAULT_ENCODING), 16),
                                         Convert.ToInt32(data.GetString(6, 2, DEFAULT_ENCODING), 16),
                                         Convert.ToInt32(data.GetString(8, 2, DEFAULT_ENCODING), 16),
                                         Convert.ToInt32(data.GetString(10, 2, DEFAULT_ENCODING), 16));

                }
                catch (SocketException)
                {

                }
                finally
                {
                    retryCount++;
                    if (socket != null)
                        socket.Close();
                }
            }

            return string.Empty;
        }

        /// <summary>
        /// Starts the ADB server (for Ara) that is distributed with the Marble framework.
        /// </summary>
        private void StartAdbServer()
        {
            // Don't start ADB server if any version of it is currently running
            if (Process.GetProcessesByName("adb").Any()) return;

            if (!File.Exists(@"..\framework\dlls\adb.exe")) return;

            var adbProcess = new Process
                {
                    StartInfo =
                        {
                            FileName = @"..\framework\dlls\adb.exe",
                            Arguments = "start-server",
                            WindowStyle = ProcessWindowStyle.Hidden
                        }
                };

            adbProcess.Start();
            adbProcess.WaitForExit(5000);
        }

        /// <summary>
        /// Starts listening device tracking data from ADB server
        /// </summary>
        private void StartListenDeviceEvents()
        {
            StartListenDeviceEvents(new IPEndPoint(IPAddress.Loopback, DEFAULT_ADB_PORT));
        }

        /// <summary>
        /// Starts listening device tracking data from ADB server
        /// </summary>
        /// <param name="address">Address of the ADB server</param>
        private void StartListenDeviceEvents(IPEndPoint address)
        {
            var request = FormAdbRequest("host:track-devices");
            mEventListenerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp)
                {
                    SendTimeout = 5000
                };

            this.StartAdbServer();
            mCollection.AdbVersion = this.GetAdbVersion();            

            try
            {
                if (!mEventListenerSocket.Connected)
                    mEventListenerSocket.Connect(address);
                //mEventListenerSocket.Blocking = true;

                if (!Write(mEventListenerSocket, request)) return;

                var data = new byte[4];
                var len = mEventListenerSocket.Receive(data);

                if (len != 4) return;

                var resp = data.GetString(0, len, DEFAULT_ENCODING);

                if (String.Compare(resp, "OKAY", StringComparison.OrdinalIgnoreCase) != 0) return;

                mEventListenerThread = new Thread(DoListenDeviceEvents) {IsBackground = true};
                mEventListenerThread.Start();
            }
            catch (SocketException)
            {
                mCollection.IsAdbConnected = false;
                this.Refresh(new List<DeviceInfo>());
                //mCollection.ErrorDescription = string.Format("{0}\n{1}\nError code: {2}",
                //                                    "Error occurred when trying to create a connection to ADB server.",
                //                                    "Make sure that the adb server is running by executing \"adb devices\"",
                //                                    e.ErrorCode);
                //mCollection.ErrorException = e;
            }
        }

        /// <summary>
        /// Does the actual event listening
        /// </summary>
        private void DoListenDeviceEvents()
        {
            mCollection.IsAdbConnected = true;
            IsListening = true;
            GetDevices();
            // Select main connection automatically if not set
            mCollection.AutoSelectMainDevice();

            while (true)
            {
                try
                {
                    var data = new byte[4];
                    var len = mEventListenerSocket.Receive(data); //blocking call
                    int count;
                    if (int.TryParse(data.GetString(0, len, DEFAULT_ENCODING), System.Globalization.NumberStyles.HexNumber, null, out count))
                    {
                        if (count > 0)
                        {
                            data = new byte[count];
                            mEventListenerSocket.Receive(data);
                        }
                        GetDevices();
                    }
                }
                catch (SocketException)
                {
                    mCollection.IsAdbConnected = false;
                    this.Refresh(new List<DeviceInfo>());
                    break;
                }
                // catch (Exception) { }
            }
            IsListening = false;
        }

        /// <summary>
        /// Retrieves the device properties 
        /// </summary>
        /// <param name="serial">Device serial</param>
        /// <returns>Property dictionary</returns>
        private Dictionary<string, string> GetProperties(string serial)
        {
            const string REQ = "shell:getprop";
            var request = FormAdbRequest(REQ);
            using(var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                socket.SendTimeout = 5000;
                var props = new Dictionary<string, string>();

                try
                {
                    socket.Connect(IPAddress.Loopback, DEFAULT_ADB_PORT);
                    socket.Blocking = true;
                    socket.ReceiveTimeout = 10000;

                    if (!SetDevice(socket, serial))
                    {
                        return null;
                    }

                    if (!Write(socket, request))
                    {
                        return null;
                    }

                    var reGetProp = new Regex("^\\[([^]]+)\\]\\:\\s*\\[(.*)\\]$", RegexOptions.Compiled);

                    var data = new byte[16384];

                    int count;
                    while ((count = socket.Receive(data)) > 0)
                    {
                        var sdata = data.GetString(0, count, DEFAULT_ENCODING);

                        foreach (var line in sdata.Split(new[] { "\n", "\r\n" }, StringSplitOptions.RemoveEmptyEntries))
                        {
                            if (string.IsNullOrEmpty(line) || line.StartsWith("#") || line.StartsWith("$"))
                            {
                                continue;
                            }
                            var m = reGetProp.Match(line);
                            if (m.Success)
                            {
                                string label = m.Groups[1].Value.Trim();
                                string value = m.Groups[2].Value.Trim();

                                if (label.Length > 0 && !props.ContainsKey(label))
                                {
                                    props.Add(label, value);
                                }
                            }
                        }
                    }

                    return props;
                }
                catch (SocketException e)
                {
                    if (e.SocketErrorCode == SocketError.TimedOut && !this.errorMessageDisplayed)
                    {
                        this.errorMessageDisplayed = true;
                        MessageBox.Show(
                            "Get device properties failed.\nADB service did not respond within given timeout.\nPlease restart the ADB service to get the connected devices and their properties.",
                            "ADB service not responding.", MessageBoxButton.OK, MessageBoxImage.Error);
                    }
                    return null;
                }
                finally
                {
                    socket.Close(false);
                }
            }
        }

        /// <summary>
        /// Redirects socket to a specific device
        /// </summary>
        /// <param name="socket">Socket to redirect</param>
        /// <param name="serial">Serial to which redirect</param>
        /// <returns>True if successfully redirected; False otherwise</returns>
        private bool SetDevice(Socket socket, string serial)
        {
            var req = string.Format("host:transport:{0}", serial);
            var request = FormAdbRequest(req);

            try
            {
                if (!Write(socket, request))
                {
                    return false;
                }

                var data = new byte[16384];

                int len = socket.Receive(data);
                if (len <= 0)
                {
                    return false;
                }

                var resp = data.GetString(0, len, DEFAULT_ENCODING);
                return String.CompareOrdinal(resp, "OKAY") == 0;
            }
            catch (SocketException)
            {
                return false;
            }
            //DO NOT CLOSE THE SOCKET IN THIS METHOD
        }
        
        /// <summary>
        /// Forms the adb request.
        /// </summary>
        /// <param name="req">Request command string</param>
        /// <returns></returns>
        private byte[] FormAdbRequest(string req)
        {
            string resultStr = string.Format("{0}{1}\n", req.Length.ToString("X4"), req);
            byte[] result;
            try
            {
                result = resultStr.GetBytes(DEFAULT_ENCODING);
            }
            catch (EncoderFallbackException)
            {
                return null;
            }
            return result;
        }

        /// <summary>
        /// Writes the specified data to the specified socket.
        /// </summary>
        /// <param name="socket">The socket.</param>
        /// <param name="data">The data.</param>
        /// <returns></returns>
        private bool Write(Socket socket, byte[] data)
        {
            try
            {
                socket.Send(data, 0, data.Length, SocketFlags.None);
            }
            catch (IOException)
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// 
        /// </summary>
        public void Dispose()
        {
            try
            {
                mEventListenerSocket.Close(false);
            }
            catch (SocketException) { }
        }
    }
}
