using Managed.Adb;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace TestAutomation.Bridge
{
    /* Backgrounds: time sync. from shell with Android devices is the devil.
     * 1) Setting date and/or time by using date, does change the time and date
     * 2) Setting time zone from console via system property persist.sys.timezone does not change the time zone in the UI
     * 3) Windows does not follow POSIX/Olson timezone formats, so when synchronizing the time zone, we need to use GMT+-AB:CD format
     * 4) persist.sys.timezone needs to be set, in order to receive the time from the system correctly
     * 5) When persist.sys.timezone or UI time zone is being set in format GMT+-AB:CD, the shell variable TZ gets a negative value:
     *    E.g. GMT-02:00 turn to be GMT+02:00. But if the time zone in persist.sys.timezone is formatted as 'Europe/Helsinki' it works correctly.
     *    shell date call reads the variable TZ when it's presenting the time, so we need to take this into account
     * 6) Setting the timezone for UI as well (from shell) we need to call IAlarmManager (http://grepcode.com/file/repository.grepcode.com/java/ext/com.google.android/android/4.3_r1/android/app/IAlarmManager.java/)
     *      - These kind of interfaces can be called from shell with some limitations: from shell you can pass only integers (32-bit) and strings as parameter
     *      - Each Service interface has a name which can be checked with command: adb shell service list
     *          - Name for IAlarmManager is 'alarm'
     *      - Each public method in these interfaces has a unique number, which may changes from SDK version to SDK version
     *          - Method number for setTimeZone in API version <= 18 is TRANSACTION_setTimeZone = (android.os.IBinder.FIRST_CALL_TRANSACTION + 4) => 5;
     *      - Setting the time zone: adb shell service call alarm 5 s16 "GMT+02:00"
     */

    /// <summary>
    /// Class for setting and getting date and time
    /// </summary>
    [Serializable]
    public sealed class Time //create the python style by using DynamicProxy
    {
        private const string TIME_ZONE_TAG = "persist.sys.timezone";
        private const string AUTO_TIME_ZONE_TAG = "auto_time_zone";
        private const string AUTO_TIME_TAG = "auto_time";
        private const string VERSION_TAG = "ro.build.version.release";

        private TABConnection m_tab;

        /// <summary>
        /// Internal class constructor
        /// </summary>
        /// <param name="tab"></param>
        internal Time(TABConnection tab)
        {
            m_tab = tab;
        }

        /// <summary>
        /// Synchronizes the PC time to the device
        /// </summary>
        /// <returns>True if successfully synchronized; false otherwise</returns>
        public bool SyncPcDateTime()
        {
            return SyncPcDateTime(true);
        }

        /// <summary>
        /// Synchronizes the PC time to the device
        /// </summary>
        /// <param name="disableNetworkTime">Whether to disable network time updating</param>
        /// <returns>True if successfully synchronized; false otherwise</returns>
        public bool SyncPcDateTime(bool disableNetworkTime)
        {
            return SetSystemDateTime(DateTime.Now, true, true);
        }

        /// <summary>
        /// Sets the given time to the device
        /// </summary>
        /// <param name="dateTime">The time to set</param>
        /// <returns>True is successfully set; false otherwise</returns>
        public bool SetSystemDateTime(DateTime dateTime)
        {
            return SetSystemDateTime(dateTime, false, true);
        }

        /// <summary>
        /// Sets the given time to the device
        /// </summary>
        /// <param name="dateTime">The time to set</param>
        /// <param name="disableNetworkTime">Whether to disable network time updating</param>
        /// <returns>True is successfully set; false otherwise</returns>
        public bool SetSystemDateTime(DateTime dateTime, bool disableNetworkTime)
        {
            return SetSystemDateTime(dateTime, false, disableNetworkTime);
        }

        /// <summary>
        /// Sets the given time to the device
        /// </summary>
        /// <param name="dateTime">The time to set</param>
        /// <param name="syncTimeZone">Whether to sync timezone</param>
        /// <param name="disableNetworkTime">Whether to disable network time updating</param>
        /// <returns>True is successfully set; false otherwise</returns>
        private bool SetSystemDateTime(DateTime dateTime, bool syncTimeZone, bool disableNetworkTime)
        {
            var command = "";
            if (syncTimeZone)
            {
                command = CreateTimeSyncCommand(dateTime);
            }
            else
            {
                command = string.Format("date -s {0}", dateTime.ToString("yyyyMMdd.HHmmss"));
            }

            var receiver = new DateTimeReceiver();
            m_tab.ExecuteShellCommand(command, receiver, TABInterface.DEFAULT_ADB_TIMEOUT);
            var success = receiver.SystemTime.Subtract(dateTime).TotalSeconds <= 5;

            if (disableNetworkTime && CanAccessTimeSettings)
            {
                var body = "settings put global {0} {1} > /dev/null 2>&1";
                var disabler = string.Format(body, "auto_time", 0) + " && " + string.Format(body, "auto_time_zone", 0);
                m_tab.ExecuteShellCommand(disabler, NullOutputReceiver.Instance);
            }

            return success;
        }

        /// <summary>
        /// Gets the time zone offset
        /// </summary>
        /// <returns>The time zone offset</returns>
        public TimeSpan GetTimeZoneOffset()
        {
            var offsetRe = new Regex(@"([+-]*)([0-9]{2}):([0-9]{2})", RegexOptions.Compiled);

            //First, try from 
            var zone = InternalGetCurrentTimeZone();

            var m = offsetRe.Match(zone);

            if (m.Success)
            {
                var isnegative = m.Groups[0].Value == "-";

                var minutes = int.Parse(m.Groups[3].Value);
                var hours = int.Parse(m.Groups[2].Value);
                minutes += hours * 60;
                if (isnegative) minutes *= -1;

                return new TimeSpan(0, minutes, 0);
            }
            else
            {
                var receiver = new TimeZoneOffsetReceiver();
                m_tab.ExecuteShellCommand("date \"+%z\"", receiver, TABInterface.DEFAULT_ADB_TIMEOUT);
                return receiver.Offset;
            }
        }

        /// <summary>
        /// Gets the delta between PC clock and device clock: as accurately as is't possible via default shell
        /// </summary>
        /// <returns>Delta time as TimeSpan structure</returns>
        public TimeSpan GetTimeDiffToLocalPc()
        {
            return GetTimeDiffToLocalPc(true);
        }

        /// <summary>
        /// Gets the delta between PC clock and device clock: as accurately as is't possible via default shell
        /// </summary>
        /// <param name="utc">Value indicating whether to use utc time from both ends</param>
        /// <returns>Delta time as TimeSpan structure</returns>
        public TimeSpan GetTimeDiffToLocalPc(bool utc)
        {
            var epoc = new DateTime(1970, 1, 1, 0, 0, 0);
            var now = DateTime.Now;
            
            if (utc)
            {
                now = now.ToUniversalTime();
            }
           
            var localUptime = now.Subtract(epoc);

            var command = "pc=" + localUptime.TotalSeconds +
                "; b=($(grep ^btime /proc/stat)); echo ${{b[1]}}'+'$(grep -o '^[^ ]*' /proc/uptime)';'$pc";

            var resp = m_tab.Shell.ExecuteCommand(command).FirstOrDefault();

            if (!string.IsNullOrEmpty(resp))
            {
                try
                {
                    var tokens = resp.Trim().Split('+', ';');
                    var bootTime = double.Parse(tokens[0], CultureInfo.InvariantCulture);
                    var upTime = double.Parse(tokens[1], CultureInfo.InvariantCulture);
                    var local = double.Parse(tokens[2].Replace(",", "."), CultureInfo.InvariantCulture);
                    return TimeSpan.FromSeconds(local - (bootTime + upTime));
                }
                catch (Exception e)
                {
                    //Log e
                }
            }
            
            return TimeSpan.Zero;
        }

        /// <summary>
        /// Gets the version of the platform of the device under test
        /// </summary>
        /// <returns>The version of the platform of the device under test</returns>
        private Version GetPlatformVersion()
        {
            var vstr = (m_tab.GetProperty(VERSION_TAG) ?? "1.0").Replace(",", ".");
            Version version = null;
            if (!Version.TryParse(vstr, out version))
            {
                return Version.Parse("1.0");   
            }
            return version;
        }

        /// <summary>
        /// Creates the shell command for setting the time and and time zone and receiving the new time in correct format
        /// </summary>
        /// <param name="dateTime">Datetime with which to create the command</param>
        /// <returns>The command</returns>
        private string CreateTimeSyncCommand(DateTime dateTime)
        {
            var diff = TimeZoneInfo.Local.GetUtcOffset(dateTime);
            var isNegative = diff < TimeSpan.Zero;
            var methodNumber = TRANSACTION_setTimeZone;
            var command = string.Format("service call alarm {0} s16 \"GMT{1}{2}\" > /dev/null 2>&1; export TZ={3}{4}; date -s {5} \"+%Y%m%d.%H%M%S\"",
                methodNumber, (isNegative ? "-" : "+"), diff.ToString(@"hh\:mm"), (isNegative ? "+" : "-"), diff.ToString(@"hh\:mm"), dateTime.ToString("yyyyMMdd.HHmmss"));
            return command;
        }

        /// <summary>
        /// Gets the method number for IAlarmmanager's setTimeZone
        /// </summary>
        private int TRANSACTION_setTimeZone
        {
            get
            {
                if (GetPlatformVersion() < Version.Parse("4.4"))
                {
                    return 5;
                }
                else
                {
                    return 3;
                }
            }
        }

        /// <summary>
        /// Gets a value indicating whether the settings api is available in the device
        /// </summary>
        private bool CanAccessTimeSettings
        {
            get
            {
                return GetPlatformVersion() >= Version.Parse("4.2");
            }
        }

        /// <summary>
        /// Enables or disables automatic time updates via network. Works from 4.2 Devices onwards
        /// </summary>
        /// <param name="enable">Enableor disable</param>
        public void EnableAutomaticNetworkTime(bool enable)
        {
            if (CanAccessTimeSettings)
            {
                if (GetTimeSettingValue(AUTO_TIME_TAG) != enable)
                {
                    SetTimeSettingValue(AUTO_TIME_TAG, enable);
                }
            }
        }

        /// <summary>
        /// Sets a time setting value
        /// </summary>
        /// <param name="settingName">Name of the setting</param>
        /// <param name="value">The value to set</param>
        private void SetTimeSettingValue(string settingName, bool value)
        {
            m_tab.Shell.ExecuteCommand(string.Format("settings put global {0} {1} > /dev/null 2>&1", settingName, value ? 1 : 0));
        }

        /// <summary>
        /// Gets a time setting value
        /// </summary>
        /// <param name="settingName">Name of the settings</param>
        /// <returns>Time setting value</returns>
        private bool GetTimeSettingValue(string settingName)
        {
            var lines = m_tab.Shell.ExecuteCommand(string.Format("settings get global {0} > /dev/null 2>&1", settingName));
            if (lines.Count == 1)
            {
                return lines[0].Trim() == "1" || lines[0].Trim().ToLower() == "true" ? true : false;
            }
            return false;
        }

        /// <summary>
        /// Enables or disables automatic time zone updates via network. Works from 4.2 Devices onwards
        /// </summary>
        /// <param name="enable">Enable or disable</param>
        public void EnableAutomaticNetworkTimeZone(bool enable)
        {
            if (CanAccessTimeSettings)
            {
                if (GetTimeSettingValue(AUTO_TIME_ZONE_TAG) != enable)
                {
                    SetTimeSettingValue(AUTO_TIME_ZONE_TAG, enable);
                }
            }
        }

        /// <summary>
        /// Sets the system's time zone to UTC
        /// </summary>
        public void SetUtcTimeZone()
        {
            SetTimeZone("GMT");
        }

        /// <summary>
        /// Sets the system's time zone
        /// </summary>
        /// <param name="timeZone">Time zone in which to change</param>
        public void SetTimeZone(string timeZone)
        {
            if (string.IsNullOrEmpty(timeZone)) return;
            
            timeZone = timeZone.ToUpper();

            if (timeZone != "GMT" && timeZone != "UTC")
            {
                var offsetRe = new Regex(@"GMT([+-]+)([0-9]{2}):([0-9]{2})", RegexOptions.Compiled | RegexOptions.IgnoreCase);

                var m = offsetRe.Match(timeZone);

                if (!m.Success) return;

                var isminus = m.Groups[1].Value == "-";
                var hour = int.Parse(m.Groups[2].Value);
                var minutes = int.Parse(m.Groups[3].Value);
                if (isminus) hour *= -1;

                if (hour > 13 || hour < -11 || (minutes != 0 && minutes != 30)) return;

                timeZone = m.Value.ToUpper();
            }
            
            var command = string.Format("service call alarm {0} s16 \"{1}\" > /dev/null 2>&1; setprop {2} \"{1}\"",
                TRANSACTION_setTimeZone, timeZone, TIME_ZONE_TAG);

            m_tab.ExecuteShellCommand(command, NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
        }

        /// <summary>
        /// Gets the current time zon in the device
        /// </summary>
        public string TimeZone
        {
            get
            {
                var offset = GetTimeZoneOffset();
                if (offset == TimeSpan.Zero) return "GMT";
                return string.Format("GMT{0}{1}", (offset < TimeSpan.Zero ? "-" : "+"), offset.ToString(@"hh\:mm"));
            }
        }

        /// <summary>
        /// Gets the datais of the current time zone in the device
        /// </summary>
        public string TimeZoneDetails
        {
            get
            {
                var builder = new StringBuilder();
                var offset = GetTimeZoneOffset();
                TimeZoneInfo.GetSystemTimeZones().ToList().FindAll(tz => tz.BaseUtcOffset == offset).ForEach(tz =>
                    {
                        builder.AppendLine(tz.DisplayName.Replace("UTC", "GMT")); //linux style: UTC -> GMT...
                    });
                return builder.ToString();
            }
        }

        /// <summary>
        /// Gets the system's current time zone
        /// </summary>
        /// <returns>System's current time zone</returns>
        private string InternalGetCurrentTimeZone()
        {
            m_tab.RefreshProperties();

            if (m_tab.Properties.ContainsKey(TIME_ZONE_TAG))
            {
                return m_tab.Properties[TIME_ZONE_TAG];
            }
            return string.Empty;
        }

        /// <summary>
        /// Gets the device system time
        /// </summary>
        /// <returns>The device system time</returns>
        public DateTime GetSystemDateTime()
        {
            return GetSystemDateTime(false);
        }

        /// <summary>
        /// Gets the device system time
        /// </summary>
        /// <param name="asLocal">True to convert to local time; False to keep in UTC</param>
        /// <returns>The device system time</returns>
        public DateTime GetSystemDateTime(bool asLocal)
        {
            var command = "date -u \"+%Y%m%d.%H%M%S\"";
            var receiver = new DateTimeReceiver();
            m_tab.ExecuteShellCommand(command, receiver, TABInterface.DEFAULT_ADB_TIMEOUT);
            var remoteTime = receiver.SystemTime.Add(GetTimeZoneOffset());
            return asLocal ? receiver.SystemTime.ToLocalTime() : remoteTime;
        }

        /// <summary>
        /// Sets the system time by keeping its current date
        /// </summary>
        /// <param name="hour">Hour</param>
        /// <param name="minute">Minute</param>
        /// <param name="second">Second</param>
        /// <returns>True is success; False otherwise</returns>
        public bool SetSystemTime(int hour, int minute, int second)
        {
            if (hour > 23 || minute > 59 || second > 59 || hour < 0 || minute < 0 || second < 0) return false;

            var zoneDiff = GetTimeZoneOffset();
            var isnegative = zoneDiff < TimeSpan.Zero;
            var command = string.Format("export TZ=GMT{0}{1}; date -s $(date \"+%Y%m%d\").{2}{3}{4} \"+%Y%m%d.%H%M%S\"", (isnegative ? "+" : "-"),
                zoneDiff.ToString(@"hh\:mm"), hour.ToString().PadLeft(2, '0'), minute.ToString().PadLeft(2, '0'), second.ToString().PadLeft(2, '0'));

            var receiver = new DateTimeReceiver();
            m_tab.ExecuteShellCommand(command, receiver, TABInterface.DEFAULT_ADB_TIMEOUT);
            return receiver.SystemTime.Hour == hour && receiver.SystemTime.Minute == minute &&
                Math.Abs(receiver.SystemTime.Second - second) < 5;
        }

        /// <summary>
        /// Sets the system date by keeping its current time
        /// </summary>
        /// <param name="year">Year</param>
        /// <param name="month">Month</param>
        /// <param name="day">Day</param>
        /// <returns>True is success; False otherwise</returns>
        public bool SetSystemDate(int year, int month, int day)
        {
            if (year < 0 || month < 1 || month > 12 || day < 1) return false;

            try
            {
                if (day > DateTime.DaysInMonth(year, month)) return false;
            }
            catch (ArgumentOutOfRangeException)
            {
                return false;
            }

            var command = string.Format("date -s {0}{1}{2}.$(date \"+%H%M%S\") \"+%Y%m%d.%H%M%S\"", year, month.ToString().PadLeft(2, '0'),
                day.ToString().PadLeft(2, '0'));
            var receiver = new DateTimeReceiver();
            m_tab.ExecuteShellCommand(command, receiver, TABInterface.DEFAULT_ADB_TIMEOUT);
            return receiver.SystemTime.Year == year && receiver.SystemTime.Month == month &&
                receiver.SystemTime.Day == day;
        }

        /// <summary>
        /// Class for reading the the time zone offset
        /// </summary>
        private class TimeZoneOffsetReceiver : IShellOutputReceiver
        {
            private static Regex offsetRe = new Regex(@"([+-]*)([0-9]{2})([0-9]{2})", RegexOptions.Compiled);

            /// <summary>
            /// Class constructor
            /// </summary>
            public TimeZoneOffsetReceiver()
            {
                Offset = new TimeSpan(0);
            }

            /// <summary>
            /// Shell output is redirected here. We parse the incoming timezone string from raw data
            /// </summary>
            /// <param name="data">String data in raw bytes</param>
            /// <param name="offset">Offset</param>
            /// <param name="length">Length of the string</param>
            public void AddOutput(byte[] data, int offset, int length)
            {
                var offsetStr = Encoding.Default.GetString(data, offset, length).Trim('\r', '\n', ' ', '\t');

                var m = offsetRe.Match(offsetStr);

                if (m.Success)
                {
                    var isminus = m.Groups[1].Value == "-";
                    var hours = int.Parse(m.Groups[2].Value);
                    var minutes = int.Parse(m.Groups[3].Value);
                    minutes += hours * 60;
                    if (isminus) minutes *= -1;
                    Offset = new TimeSpan(0, minutes, 0);
                }
            }

            /// <summary>
            /// The time zone offset
            /// </summary>
            public TimeSpan Offset { get; private set; }

            /// <summary>
            /// Not used.
            /// </summary>
            public void Flush()
            { }

            /// <summary>
            /// Not used.
            /// </summary>
            public bool IsCancelled
            {
                get { return false; }
            }
        }

        /// <summary>
        /// Class for receiving date time from the device
        /// </summary>
        private class DateTimeReceiver : IShellOutputReceiver
        {
            private const string SYSTEM_DATE_FORMAT = "yyyyMMdd.HHmmss";

            /// <summary>
            /// Shell output is redirected here. We parse the incoming date time string from raw data
            /// </summary>
            /// <param name="data">String data in raw bytes</param>
            /// <param name="offset">Offset</param>
            /// <param name="length">Length of the string</param>
            public void AddOutput(byte[] data, int offset, int length)
            {
                if (!Success && length > 2)
                {
                    var timeStr = Encoding.Default.GetString(data, offset, length).Trim('\r', '\n', ' ', '\t');

                    DateTime time;

                    if (DateTime.TryParseExact(
                        timeStr,
                        SYSTEM_DATE_FORMAT,
                        CultureInfo.InvariantCulture,
                        DateTimeStyles.None,
                        out time))
                    {
                        SystemTime = time;
                        Success = true;
                    }
                }
            }

            /// <summary>
            /// Current/new system time
            /// </summary>
            public DateTime SystemTime { get; private set; }

            /// <summary>
            /// Gets a value indicating whether the time was successfully received from the system
            /// </summary>
            public bool Success { get; private set; }

            /// <summary>
            /// Not used.
            /// </summary>
            public void Flush()
            { }

            /// <summary>
            /// Not used.
            /// </summary>
            public bool IsCancelled
            {
                get { return false; }
            }
        }
    }
}
