using Managed.Adb;
using Managed.Adb.Exceptions;
using Managed.Adb.IO;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using TestAutomation.Bridge.ScriptingTools;
using TestAutomation.Client;

/*
 * Exceptions:
 *  DEviceNotFound for all
 */

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Class for performing file operations in the remote device
    /// </summary>
    [Serializable]
    public sealed class FileSystemAdapter
    {
        #region "Constants"

        private const string FILE_REFRESH_COMMAND = "am broadcast -a android.intent.action.MEDIA_SCANNER_SCAN_FILE -d file:///{0}";
        private const string DIRECTORY_REFRESH_COMMAND = "am broadcast -a android.intent.action.MEDIA_MOUNTED -d file:///{0}";

        private const string EXTERNAL_STORAGE_KEY = "EXTERNAL_STORAGE";
        private const string SECONDARY_STORAGE_KEY = "SECONDARY_STORAGE";
        
        private const string DATA_KEY = "ANDROID_DATA";
        private const string ROOT_KEY = "ANDROID_ROOT";
        private const string STORAGE_KEY = "ANDROID_STORAGE";
        private const string ASSETS_KEY = "ANDROID_ASSETS";
        private const string TEMP_DIRECTORY = "local/tmp";

        private const string DEFAULT_EXTERNAL_STORAGE = "/storage/emulated/legacy";
        private const string DEFAULT_DATA = "/data";
        private const string DEFAULT_ROOT = "/system";
        private const string DEFAULT_STORAGE = "/storage";

        private const int LINUX_PATH_MAX = 4096;
        private const int LINUX_FILE_NAME_MAX = 255;
        private const int WINDOWS_PATH_MAX = 248;
        private const int WINDOWS_FILE_NAME_MAX = 260;

        #endregion

        #region "Private fields"

        private static Regex m_sdMountPattern = new Regex(@"/storage/.*sdcard[0-9]*", RegexOptions.Compiled | RegexOptions.IgnoreCase);

        private TABConnection m_tab;

        #endregion

        #region "Constructor"

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="tab">Tab instance</param>
        internal FileSystemAdapter(TABConnection tab)
        {
            m_tab = tab;
            AutoRefresh = true;
        }

        #endregion

        #region "Public properties"

        /// <summary>
        /// Gets or sets a value indicating whether to automatically refresh the file system after certain file oprations: e.g. file pushed to sdcard
        /// won't get visible in the gallery in not automatically refreshed
        /// </summary>
        public bool AutoRefresh { get; set; }

        /// <summary>
        /// Gets the External storage location
        /// </summary>
        /// <returns></returns>
        public string ExternalStorage
        {
            get
            {
                return FormatDirectoryPath(m_tab.EnvironmentVariables.ContainsKey(EXTERNAL_STORAGE_KEY) ? m_tab.EnvironmentVariables[EXTERNAL_STORAGE_KEY] : DEFAULT_EXTERNAL_STORAGE);
            }
        }

        /// <summary>
        /// Gets the sdcard location; null if not found
        /// </summary>
        public string SdCard
        {
            get
            {
                if (m_tab.EnvironmentVariables.ContainsKey(SECONDARY_STORAGE_KEY))
                {
                    var externalStorages = m_tab.EnvironmentVariables[SECONDARY_STORAGE_KEY];

                    var m = m_sdMountPattern.Match(externalStorages);
                    if (m.Success && DirectoryExists(m.Value))
                    {
                        return FormatDirectoryPath(m.Value);
                    }
                }
                return null;
            }
        }

        /// <summary>
        /// Gets a value indicating whther the device has sdcard mounted
        /// </summary>
        public bool HasSdCard
        {
            get
            {
                if (m_tab.IsOnline)
                {
                    m_tab.RefreshEnvironmentVariables();
                }
                if (!string.IsNullOrEmpty(SdCard))
                {
                    var entry = GetFileInfo(SdCard);

                    if (entry != null)
                    {
                        return string.Compare(entry.Permissions.ToChmod(), "000") != 0;
                    }
                }

                return false;
            }
        }

        /// <summary>
        /// Gets free space on the sdcard; 0 if the sdcard is not mounted
        /// </summary>
        public double FreeSpaceOnSdCard
        {
            get
            {
                if (m_tab.IsOnline)
                {
                    m_tab.RefreshEnvironmentVariables();
                }
                if (!string.IsNullOrEmpty(SdCard))
                {
                    var entry = GetFileInfo(SdCard);

                    if (entry != null && string.Compare(entry.Permissions.ToChmod(), "000") != 0)
                    {
                        return GetFreeDiskSpace(SdCard);
                    }
                }
                return 0;
            }
        }

        /// <summary>
        /// Gets the sdcard size; 0 if the sdcard is not mounted
        /// </summary>
        public double SdCardSize
        {
            get
            {
                if (m_tab.IsOnline)
                {
                    m_tab.RefreshEnvironmentVariables();
                }
                if (!string.IsNullOrEmpty(SdCard))
                {
                    var entry = GetFileInfo(SdCard);

                    if (entry != null && string.Compare(entry.Permissions.ToChmod(), "000") != 0)
                    {
                        return GetFreeDiskSpace(SdCard);
                    }
                }
                return 0;
            }
        }

        /// <summary>
        /// Gets the used space in the sdcard; 0 if the sdcard is not mounted
        /// </summary>
        public double UsedSdCardSpace
        {
            get
            {
                if (m_tab.IsOnline)
                {
                    m_tab.RefreshEnvironmentVariables();
                }
                if (!string.IsNullOrEmpty(SdCard))
                {
                    var entry = GetFileInfo(SdCard);

                    if (entry != null && string.Compare(entry.Permissions.ToChmod(), "000") != 0)
                    {
                        return GetUsedDiskSpace(SdCard);
                    }
                }
                return 0;
            }
        }

        /// <summary>
        /// Gets the data directory
        /// </summary>
        public string Data
        {
            get
            {
                return FormatDirectoryPath(m_tab.EnvironmentVariables.ContainsKey(DATA_KEY) ? m_tab.EnvironmentVariables[DATA_KEY] : DEFAULT_DATA);
            }
        }

        /// <summary>
        /// Gets the home directory
        /// </summary>
        public string Home
        {
            get
            {
                return Data;
            }
        }

        /// <summary>
        /// Gets the root directory
        /// </summary>
        public string Root
        {
            get
            {
                return FormatDirectoryPath(m_tab.EnvironmentVariables.ContainsKey(ROOT_KEY) ? m_tab.EnvironmentVariables[ROOT_KEY] : DEFAULT_ROOT);
            }
        }

        /// <summary>
        /// Gets the temp directory
        /// </summary>
        public string Temp
        {
            get
            {
                return FormatDirectoryPath(LinuxPath.Combine(Data, TEMP_DIRECTORY));
            }
        }

        /// <summary>
        /// Gets the storage location
        /// </summary>
        public string Storage
        {
            get
            {
                return FormatDirectoryPath(m_tab.EnvironmentVariables.ContainsKey(STORAGE_KEY) ? m_tab.EnvironmentVariables[STORAGE_KEY] : DEFAULT_STORAGE);
            }
        }

        #endregion

        #region "Touch"

        /// <summary>
        /// Touches a file
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public void TouchFile(string remotePath)
        {
            TouchFile(remotePath, default(DateTime));
        }

        /// <summary>
        /// Touches a file
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <param name="time">Time of the touch</param>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public void TouchFile(string remotePath, DateTime time)
        {
            ValidateRemotePath(remotePath);

            var epoc = new DateTime(1970, 1, 1, 0, 0, 0);
            long t = -1;
            if (time > epoc) //also greater than default(DateTime), which is [1.1.0001 0:00:00]
            {
                var offset = m_tab.Time.GetTimeZoneOffset();

                t = (long)Math.Round(time.Subtract(epoc).Add(offset).TotalSeconds, 0);
            }

            var command = string.Format("dir=$(realpath {0}); if [ -f $dir ] && [ ! -d $dir ]; then touch {1} $dir; fi",
                    FormatFilePath(remotePath), (t != -1 ? string.Format("-t {0}", t) : ""));
            
            ExecuteFileCommand(command);
        }

        /// <summary>
        /// Touches any file system item
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public void Touch(string remotePath)
        {
            Touch(remotePath, default(DateTime));
        }

        /// <summary>
        /// Touches any file system item
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <param name="time">Time of the touch</param>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public void Touch(string remotePath, DateTime time)
        {
            var epoc = new DateTime(1970, 1, 1, 0, 0, 0);
            long t = -1;
            if (time > epoc)
            {
                var offset = m_tab.Time.GetTimeZoneOffset();

                t = (long)Math.Round(time.Subtract(epoc).Subtract(offset).TotalSeconds, 0);
            }

            var command = string.Format("dir=$(realpath {0}); if [ -e $dir ] && [ -w $dir ]; then touch {1} $dir; fi",
                    FormatPath(remotePath), (t != -1 ? string.Format("-t {0}", t) : ""));

            ExecuteFileCommand(command);
        }

        /// <summary>
        /// Touches a directory
        /// </summary>
        /// <param name="remotePath">Path to the remote directory</param>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public void TouchDirectory(string remotePath)
        {
            TouchDirectory(remotePath, default(DateTime));
        }

        /// <summary>
        /// Touches a directory
        /// </summary>
        /// <param name="remotePath">Path to the remote directory</param>
        /// <param name="time">Time of the touch</param>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public void TouchDirectory(string remotePath, DateTime time)
        {
            ValidateRemotePath(remotePath);

            var epoc = new DateTime(1970, 1, 1, 0, 0, 0);
            long t = -1;
            if (time > epoc)
            {
                var offset = m_tab.Time.GetTimeZoneOffset();

                t = (long)Math.Round(time.Subtract(epoc).Subtract(offset).TotalSeconds, 0);
            }

            var command = string.Format("dir=$(realpath {0}); if [ -d $dir ] && [ -w $dir ]; then touch {1} $dir; fi",
                    FormatDirectoryPath(remotePath), (t != -1 ? string.Format("-t {0}", t) : ""));

            ExecuteFileCommand(command);
        }

        #endregion

        #region "Disk space"

        /// <summary>
        /// Gets the total disk space in the given mount point
        /// </summary>
        /// <param name="remoteMount">The mount point</param>
        /// <returns>Total space in bytes</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        /// <exception cref="IOException">No disk space info received</exception>
        public long GetTotalDiskSpace(string remoteMount)
        {
            ValidateRemotePath(remoteMount);
            
            var formatted = FormatPath(remoteMount);
            var command = string.Format("dir=$(realpath {0}); if [ -e $dir ]; then df $dir; fi", formatted);
            var receiver = new DiskSpaceInfoReceiver();

            ExecuteFileCommand(command, receiver);

            if (receiver.DiskSpace.Count == 0)
            {
                throw new IOException("No disk space info received for " + remoteMount);
            }
            return (long)receiver.DiskSpace.First().Size;
        }

        /// <summary>
        /// Gets the used disk space in the given mount point
        /// </summary>
        /// <param name="remoteMount">The mount point</param>
        /// <returns>Used space in bytes</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        /// <exception cref="IOException">No disk space info received</exception>
        public long GetUsedDiskSpace(string remoteMount)
        {
            ValidateRemotePath(remoteMount);
            
            var formatted = FormatPath(remoteMount);
            var command = string.Format("dir=$(realpath {0}); if [ -e $dir ]; then df $dir; fi", formatted);
            var receiver = new DiskSpaceInfoReceiver();

            ExecuteFileCommand(command, receiver);

            if (receiver.DiskSpace.Count == 0)
            {
                throw new IOException("No disk space info received for " + remoteMount);
            }
            return (long)receiver.DiskSpace.First().Used;
        }

        /// <summary>
        /// Gets the free disk space in the given mount point
        /// </summary>
        /// <param name="remoteMount">The mount point</param>
        /// <returns>Free space in bytes</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        /// <exception cref="IOException">No disk space info received</exception>
        public long GetFreeDiskSpace(string remoteMount)
        {
            ValidateRemotePath(remoteMount);

            var formatted = FormatPath(remoteMount);
            var command = string.Format("dir=$(realpath {0}); if [ -e $dir ]; then df $dir; fi", formatted);
            var receiver = new DiskSpaceInfoReceiver();

            ExecuteFileCommand(command, receiver);

            if (receiver.DiskSpace.Count == 0)
            {
                throw new IOException("No disk space info received for " + remoteMount);
            }
            return (long)receiver.DiskSpace.First().Free;
        }

        #endregion

        #region "File listing"

        /// <summary>
        /// Gets all the file system items under a given directory
        /// </summary>
        /// <param name="remotePath">Path to the remote directory</param>
        /// <returns>All the file system items under a given directory</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="System.UnauthorizedAccessException">The caller does not have the required permission to
        /// read the directory from the specified location.</exception>
        /// <exception cref="DirectoryNotFoundException">Directory was not found</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public List<RemoteFileInfo> GetFileSystemItems(string remotePath)
        {
            ValidateRemotePath(remotePath);

            var formatted = FormatDirectoryPath(remotePath);

            var receiver = new LsReceiver(formatted, true);

            var command = string.Format("dir=$(realpath {0}); if [ -d $dir ] && [ -r $dir ]; then ls -la $dir; elif [ ! -d $dir ]; then echo NOT_FOUND; elif [ ! -r $dir ]; then echo NO_ACCESS; fi", formatted);

            ExecuteFileCommand(command, receiver);

            if (receiver.DirectoryNotFound)
            {
                throw new DirectoryNotFoundException(remotePath);
            }

            if (!receiver.PermissionDenied)
            {
                var tzoffset = m_tab.Time.GetTimeZoneOffset();

                receiver.Entries.ForEach(e => e.LastAccessTimeUtc = e.LastAccessTime.Subtract(tzoffset));

                return receiver.Entries;
            }

            throw new UnauthorizedAccessException(remotePath);
        }

        #endregion

        #region "File information"

        /// <summary>
        /// Gets a file system item type
        /// </summary>
        /// <param name="remotePath">Path to the remote file system item</param>
        /// <returns>A file system item type</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        public RemoteFileType GetType(string remotePath)
        {
            ValidateRemotePath(remotePath);

            var formatted = FormatPath(remotePath);

            var entry = GetFileInfo(formatted);

            if (entry == null)
            {
                throw new FileNotFoundException(formatted);
            }

            return entry.FileType;
        }

        /// <summary>
        /// Gets a file system item info
        /// </summary>
        /// <param name="remotePath">Path to the remote file system item</param>
        /// <returns>A file system item info</returns>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public RemoteFileInfo GetFileInfo(string remotePath)
        {
            return GetFileInfo(remotePath, TimeSpan.Zero);
        }

        /// <summary>
        /// Gets a file system item info
        /// </summary>
        /// <param name="remotePath">Path to the remote file system item</param>
        /// <param name="timeZoneOffset">Timzone offset to be used for file times</param>
        /// <returns>A file system item info; null if not found</returns>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        private RemoteFileInfo GetFileInfo(string remotePath, TimeSpan timeZoneOffset)
        {
            var receiver = new LsReceiver(remotePath, false, timeZoneOffset);
            var command = string.Format("if [ -e {0} ]; then ls -ld {0}; fi", remotePath.TrimEnd('/'));
            ExecuteFileCommand(command, receiver);
            return receiver.Entries.FirstOrDefault();
        }

        #endregion

        #region "Exists"

        /// <summary>
        /// Gets a value indicating whether a file exists or not
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <returns>True if exists; otherwise, false</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public bool FileExists(string remotePath)
        {
            ValidateRemotePath(remotePath);

            var command = string.Format("if [ -f {0} ]; then echo true; fi", FormatFilePath(remotePath));
            var receiver = new IOReceiver();
            ExecuteFileCommand(command, receiver);
            return receiver.Success;
        }

        /// <summary>
        /// Gets a value indicating whether a directory exists or not
        /// </summary>
        /// <param name="remotePath">Path to the remote directory</param>
        /// <returns>True if exists; otherwise, false</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public bool DirectoryExists(string remotePath)
        {
            ValidateRemotePath(remotePath);
            
            var command = string.Format("if [ -d {0} ]; then echo true; fi", FormatDirectoryPath(remotePath));
            var receiver = new IOReceiver();
            ExecuteFileCommand(command, receiver);
            return receiver.Success;
        }

        #endregion

        #region "Date & time"

        /// <summary>
        /// Gets a file system item modification date&time as device time
        /// </summary>
        /// <param name="remotePath">Path to the remote file system item</param>
        /// <returns>File system item modification date&time</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public DateTime GetDate(string remotePath)
        {
            return GetDate(remotePath, false);
        }

        /// <summary>
        /// Gets a file system item modification date&time as utc time
        /// </summary>
        /// <param name="remotePath">Path to the remote file system item</param>
        /// <returns>File system item modification date&time</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public DateTime GetUtcTime(string remotePath)
        {
            return GetDate(remotePath, true);
        }

        /// <summary>
        /// Gets a file system item modification date&time
        /// </summary>
        /// <param name="remotePath">Path to the remote file system item</param>
        /// <param name="utc">True to convert the date&time to utc time</param>
        /// <returns>File system item modification date&time</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public DateTime GetDate(string remotePath, bool utc)
        {
            ValidateRemotePath(remotePath);

            var formatted = FormatPath(remotePath);
               
            var file = GetFileInfo(formatted, utc ? m_tab.Time.GetTimeZoneOffset() : TimeSpan.Zero);

            if (file == null)
            {
                throw new FileNotFoundException(formatted);
            }

            return utc ? file.LastAccessTimeUtc : file.LastAccessTime;
        }

        #endregion

        #region "Size"

        /// <summary>
        /// Gets the size of the file system item
        /// </summary>
        /// <param name="remotePath">Path to the remote file system item</param>
        /// <returns>The size of the file system item</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public long GetSize(string remotePath)
        {
            ValidateRemotePath(remotePath);

            var formatted = FormatFilePath(remotePath);

            var entry = GetFileInfo(formatted);

            if (entry == null)
            {
                throw new FileNotFoundException(formatted);
            }

            return entry.Length;
        }

        #endregion

        #region "Attributes"

        /// <summary>
        /// Gets attributes from a file system item
        /// </summary>
        /// <param name="remotePath">Path of the file item</param>
        /// <returns>Attributes as Tuple(int->user, int->group, int->other)</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public Tuple<int, int, int> GetAttributes(string remotePath)
        {
            ValidateRemotePath(remotePath);

            var formatted = FormatPath(remotePath);

            var entry = GetFileInfo(formatted);

            if (entry == null)
            {
                throw new FileNotFoundException(formatted);
            }

            return new Tuple<int, int, int>
                (
                    (int)entry.Permissions.User.ToChmod(),
                    (int)entry.Permissions.Group.ToChmod(),
                    (int)entry.Permissions.Other.ToChmod()
                );
        }

        /// <summary>
        /// Sets attributes for a file system item
        /// </summary>
        /// <param name="remotePath">Path of the file item</param>
        /// <param name="attributes">Attributes as int list</param>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null; or attributes is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public void SetAttributes(string remotePath, IList attributes)
        {
            if (attributes == null)
            {
                throw new ArgumentNullException("attributes");
            }

            if (attributes.Count == 1)
            {
                if (attributes[0] is int)
                {
                    int all = (int)attributes[0];
                    SetAttributes(remotePath, all);
                }
            }
            if (attributes.Count == 3)
            {
                if ((attributes[0] is int) && (attributes[1] is int) && (attributes[2] is int))
                {
                    int user = (int)attributes[0];
                    int group = (int)attributes[1];
                    int other = (int)attributes[2];
                    SetAttributes(remotePath, user, group, other);
                }
            }
        }

        /// <summary>
        /// Sets attributes for a file system item
        /// </summary>
        /// <param name="remotePath">Path of the file item</param>
        /// <param name="all">integer to be applied to all: user, group, other</param>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public void SetAttributes(string remotePath, int all)
        {
            SetAttributes(remotePath, all, all, all);
        }

        /// <summary>
        /// Sets attributes for a file system item
        /// </summary>
        /// <param name="remotePath">Path of the file item</param>
        /// <param name="user">Value for user</param>
        /// <param name="group">Value for group</param>
        /// <param name="other">Value for other</param>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public void SetAttributes(string remotePath, int user, int group, int other)
        {
            ValidateRemotePath(remotePath);
            user = user < 0 ? 0 : (user > 7 ? 7 : user);
            group = group < 0 ? 0 : (group > 7 ? 7 : group);
            other = other < 0 ? 0 : (other > 7 ? 7 : other);
            SetAttributes(FormatPath(remotePath), string.Format("{0}{1}{2}", user, group, other));
        }

        /// <summary>
        /// Sets attributes for a file system item
        /// </summary>
        /// <param name="remotePath">Path of the file item</param>
        /// <param name="chmod">chmod string</param>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        private void SetAttributes(string remotePath, string chmod)
        {
            var command = string.Format("if [ -e {1} ]; then chmod {0} {1}; fi", chmod, remotePath);
            ExecuteFileCommand(command);
            RefreshDirectory(LinuxPath.GetDirectoryName(remotePath.TrimEnd('/')));
        }

        #endregion

        #region "Push & Pull"

        /// <summary>
        /// Pulls a file or directory from the device, to the local machine
        /// </summary>
        /// <param name="remotePath">Path to the remote file or directory</param>
        /// <param name="localPath">Path to the local folder/file</param>
        public void Pull(string remotePath, string localPath)
        {
            Pull(remotePath, localPath, true);
        }

        /// <summary>
        /// Pulls a file or directory from the device, to the local machine
        /// </summary>
        /// <param name="remotePath">Path to the remote file or directory</param>
        /// <param name="localPath">Path to the local folder/file</param>
        /// <param name="sync"></param>
        public void Pull(string remotePath, string localPath, bool sync)
        {
            Pull(remotePath, localPath, sync, false);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="remotePath"></param>
        /// <param name="localPath"></param>
        private void Pull(string remotePath, string localPath, bool sync, bool internalCall)
        {
            ValidateRemotePath(remotePath);
            ValidateLocalPath(localPath);

            var formatted = FormatFilePath(remotePath);
            var original = formatted;

            var entry = GetFileInfo(formatted);

            //Remote file entry not found
            if (entry == null)
            {
                throw new FileNotFoundException(formatted);
            }

            if (entry.IsLink)
            {
                var realPath = ResolveLink(formatted);
                entry = GetFileInfo(realPath);
                formatted = realPath;
            }

            //No permissions to read the remote entry
            if (!entry.Permissions.Group.CanRead && !entry.Permissions.User.CanRead)
            {
                throw new UnauthorizedAccessException(formatted);
            }

            var fsi = new FileInfo(localPath);
            
            //We're about to copy a directory
            if (entry.IsDirectory)
            {
                //Source is a directory, but destination is file, and we should be synching
                if (fsi.Exists && !fsi.Attributes.HasFlag(FileAttributes.Directory) && sync)
                {
                    throw new IOException(string.Format("Source ({0}) is a directory; target ({1}) is a file",
                        formatted, fsi.FullName));
                }
                else if (!fsi.DirectoryExists())
                {
                    //Create the base directory
                    Directory.CreateDirectory(fsi.FullName); //might end up having a directory with file extension...
                }
                
                //Name of the directorry we're about to pull
                var newDir = LinuxPath.GetFileName(original.TrimEnd('/'));
                //Combine with base directory
                newDir = Path.Combine(fsi.FullName, newDir);
                var di = new DirectoryInfo(newDir);
                if (!di.Exists || !sync)
                {
                    if (!sync && di.Exists)
                    {
                        try
                        {
                            di.Delete(true);
                        }
                        catch (Exception e)
                        {
                            //log e
                        }
                    }
                    di.Create();
                }

                var contents = GetFileSystemItems(formatted);

                if (contents != null)
                {
                    contents.ForEach(item =>
                        {
                            try
                            {
                                Pull(item.FullName, di.FullName, sync, true);
                            }
                            catch (Exception e)
                            {
                                //log e
                            }
                        });
                }
            }
            //Source is a file; and destination exists
            else if (fsi.Exists)
            {
                var isDirectory = fsi.Attributes.HasFlag(FileAttributes.Directory);

                if (isDirectory)
                {
                    localPath = Path.Combine(localPath, LinuxPath.GetFileName(formatted.TrimEnd('/')));
                }
            }
            //Destination does not exist
            else
            {
                //destination is a directory, and source is any file
                if (fsi.DirectoryExists() && !entry.IsDirectory)
                {
                    localPath = Path.Combine(fsi.FullName, entry.Name);
                }
                
                if (File.Exists(localPath))
                {
                    if (sync && IsSame(localPath, formatted))
                    {
                        return;
                    }
                    else
                    {
                        File.Delete(localPath);
                    }
                }

                var drive = new DriveInfo(new FileInfo(localPath).FullName[0].ToString());
                if (drive.AvailableFreeSpace < entry.Length)
                {
                    throw new IOException(string.Format("Not enough disk space in {0}", drive));
                }

                using (var outStream = File.Open(localPath, FileMode.Create, FileAccess.Write, FileShare.Read))
                {
                    CopyTo(formatted, outStream);
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="localPath"></param>
        /// <param name="remotePath"></param>
        public void Push(string localPath, string remotePath)
        {
            Push(localPath, remotePath, true, false);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="localPath"></param>
        /// <param name="remotePath"></param>
        /// <param name="sync"></param>
        public void Push(string localPath, string remotePath, bool sync)
        {
            Push(localPath, remotePath, sync, false);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="localPath"></param>
        /// <param name="formatted"></param>
        private void Push(string localPath, string remotePath, bool sync, bool dirCopy)
        {
            ValidateLocalPath(localPath);
            ValidateRemotePath(remotePath);

            var fsi = new FileInfo(localPath);

            var directoryCopy = fsi.DirectoryExists();

            if (!fsi.Exists && !directoryCopy)
            {
                throw new FileNotFoundException(fsi.FullName);
            }

            var formatted = FormatPath(remotePath);

            var remoteInfo = GetFileInfo(formatted);

            if (remoteInfo != null && remoteInfo.IsLink)
            {
                var realPath = ResolveLink(formatted);
                remoteInfo = GetFileInfo(realPath);
                formatted = realPath;
            }

            //is directory
            if (remoteInfo != null && remoteInfo.IsDirectory)
            {
                //no access to the directory
                if (!remoteInfo.Permissions.Group.CanWrite && !remoteInfo.Permissions.User.CanWrite)
                {
                    throw new UnauthorizedAccessException(remoteInfo.DirectoryName);
                }
                
                if (!dirCopy)
                    formatted = LinuxPath.Combine(formatted, fsi.Name);
            }
            //is not directory, link nor file
            else if (remoteInfo != null && !remoteInfo.IsFile && !remoteInfo.IsLink)
            {
                throw new FileNotFoundException(remoteInfo.FullName);
            }
            //file exists
            else if (remoteInfo != null && (remoteInfo.IsFile || remoteInfo.IsExecutable))
            {
                //Can't write a folder contents into a file
                if (directoryCopy)
                {
                    throw new IOException(string.Format("Source ({0}) is directory; destination ({1}) is a file", formatted, remoteInfo.FullName));
                }
                //Check if the file is the same
                if (sync && IsSame(fsi.FullName, remoteInfo.FullName))
                {
                    return;
                }
                //We're overwriting, so let's check the permissions
                if (!remoteInfo.Permissions.Group.CanWrite && !remoteInfo.Permissions.User.CanWrite)
                {
                    throw new UnauthorizedAccessException(remoteInfo.FullName);
                }
            }
            //is file, which does not exist
            else if (remoteInfo == null)
            {
                var parentPath = LinuxPath.GetDirectoryName(formatted.TrimEnd('/'));

                var parentInfo = GetFileInfo(parentPath);

                //There is no parent directory, or the parent is something else than a directory or a link to a directory
                if (parentInfo == null || (!parentInfo.IsDirectory && !parentInfo.IsLink))
                {
                    throw new DirectoryNotFoundException(parentPath);
                }

                var realPath = ResolveLink(parentPath);
                parentInfo = GetFileInfo(realPath);
                if (parentInfo == null)
                {
                    throw new DirectoryNotFoundException(realPath);
                }
                
                formatted = LinuxPath.Combine(realPath, LinuxPath.GetFileName(formatted.TrimEnd('/')));

                //no access to write into the parent directory
                if (!parentInfo.Permissions.Group.CanWrite && !parentInfo.Permissions.User.CanWrite)
                {
                    throw new UnauthorizedAccessException(parentInfo.FullName);
                }
            }

            if (directoryCopy)
            { 
                try
                {
                    if (CreateDirectory(formatted))
                    {
                        Directory.GetFileSystemEntries(fsi.FullName).ToList().ForEach(file =>
                            {
                                try
                                {
                                    Push(file, LinuxPath.Combine(formatted, Path.GetFileName(file)), sync, true);
                                }
                                catch (Exception e)
                                {
                                    //log e
                                }
                            });
                    }
                }
                catch (Exception e)
                {
                    //log e
                }
            }
            else
            {
                //There is isn't enough space to write the file into the destination partition
                if (GetFreeDiskSpace(LinuxPath.GetDirectoryName(formatted.TrimEnd('/'))) < fsi.Length)
                {
                    throw new IOException(string.Format("Not enough disk space in {0}", formatted));
                }

                //With unrooted devices, it successfully writes the file, but then, calls the chmod from FileSystem, which, due
                //to bad implementation, throws an exception that one of the sub folders requires permission
                try
                {
                    var result = m_tab.SyncService.PushFile(fsi.FullName, formatted, new NullSyncProgressMonitor());

                    if (result.Code != 0)
                    {
                        throw new IOException(result.Message ?? "Unknown exception occured when pushing a file into the remote device");
                    }                    
                }
                catch (PermissionDeniedException)
                {
                    //SetAttributes(formatted, 6);
                }
                catch (FileNotFoundException) { } //FileListing service throws these as well...

                RefreshDirectory(LinuxPath.GetDirectoryName(formatted.TrimEnd('/')));
            }
        }

        #endregion

        #region "Read file contents"

        /// <summary>
        /// Reads all the text from a remote file
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <returns>All the text from a remote file; or null</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="UnauthorizedAccessException">no permission to read the remote file contents</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public string ReadAllText(string remotePath)
        {
            return ReadAllText(remotePath, Encoding.Default);
        }

        /// <summary>
        /// Reads all the text from a remote file
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <param name="encoding">Encoding to be used</param>
        /// <returns>All the text from a remote file; or null</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="UnauthorizedAccessException">no permission to read the remote file contents</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public string ReadAllText(string remotePath, Encoding encoding)
        {
            var bytes = ReadAllBytes(remotePath);

            if (bytes == null) return null;

            return encoding.GetString(bytes);
        }

        /// <summary>
        /// Reads all the lines from a remote file
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <returns>Array of lines; or null</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="UnauthorizedAccessException">no permission to read the remote file contents</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public string[] ReadAllLines(string remotePath)
        {
            return ReadAllLines(remotePath, Encoding.Default);
        }

        /// <summary>
        /// Reads all the lines from a remote file
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <param name="encoding">Encoding to be used</param>
        /// <returns>Array of lines; or null</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="UnauthorizedAccessException">no permission to read the remote file contents</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public string[] ReadAllLines(string remotePath, Encoding encoding)
        {
            var allText = ReadAllText(remotePath, encoding);
            
            if (allText == null) return null;
            
            return allText.Split(new string[] { "\n", "\r\n" }, StringSplitOptions.None);
        }

        /// <summary>
        /// Reads all the bytes from a remote file
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <returns>All the bytes from a remote file</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="UnauthorizedAccessException">no permission to read the remote file contents</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public byte[] ReadAllBytes(string remotePath)
        {
            ValidateRemotePath(remotePath);

            var formatted = FormatFilePath(remotePath);

            var entry = GetFileInfo(formatted);

            if (entry == null || entry.IsDirectory || entry.IsRoot)
            {
                throw new FileNotFoundException(formatted);
            }

            if (!entry.Permissions.Group.CanRead && !entry.Permissions.User.CanRead)
            {
                throw new UnauthorizedAccessException(formatted);
            }

            using (var inStream = OpenRead(formatted) as MemoryStream)
            {
                return inStream != null ? inStream.ToArray() : null;
            }
        }

        /// <summary>
        /// Opens a remote file as stream
        /// </summary>
        /// <param name="remotePath">Path to thre remote file</param>
        /// <returns>File stream</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="UnauthorizedAccessException">no permission to read the remote file contents</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public Stream OpenRead(string remotePath)
        {
            ValidateRemotePath(remotePath);

            var formatted = FormatFilePath(remotePath);

            var entry = GetFileInfo(formatted);

            if (entry == null || entry.IsDirectory || entry.IsRoot)
            {
                throw new FileNotFoundException(formatted);
            }

            if (!entry.Permissions.Group.CanRead && !entry.Permissions.User.CanRead)
            {
                throw new UnauthorizedAccessException(formatted);
            }

            return m_tab.RunDevService(formatted);
        }

        /// <summary>
        /// Copies a remote file to a stream
        /// </summary>
        /// <param name="remotePath">Path to thre remote file</param>
        /// <param name="target">The stream to copy into</param>
        /// <returns>File stream</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null or target stream is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="UnauthorizedAccessException">no permission to read the remote file contents</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public void CopyTo(string remotePath, Stream target)
        {
            if (target == null)
            {
                throw new ArgumentNullException("target");
            }

            ValidateRemotePath(remotePath);

            var formatted = FormatFilePath(remotePath);

            var entry = GetFileInfo(formatted);

            if (entry == null || entry.IsDirectory || entry.IsRoot)
            {
                throw new FileNotFoundException(formatted);
            }

            if (!entry.Permissions.User.CanRead && !entry.Permissions.Group.CanRead)
            {
                throw new UnauthorizedAccessException(formatted);
            }

            m_tab.RunDevService(formatted, target);
        }

        #endregion

        #region "Legacy"

        /// <summary>
        /// Gets all the files and directories under a given directory
        /// </summary>
        /// <param name="remotePath">Path to the remote directory</param>
        /// <returns>Directory contents as a tuple: Tuple(list->files, list->directories)"</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="System.UnauthorizedAccessException">The caller does not have the required permission to
        /// read the directory from the specified location.</exception>
        /// <exception cref="DirectoryNotFoundException">Directory was not found</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public Tuple<List<string>, List<string>> GetFolderContent(string remotePath)
        {
            var ret = new Tuple<List<string>, List<string>>(new List<string>(), new List<string>());

            var entries = GetFileSystemItems(remotePath);

            if (entries != null)
            {
                entries.ForEach(e =>
                {
                    if (e.IsDirectory)
                    {
                        ret.Item2.Add(e.FullName);
                    }
                    else if (!e.IsRoot)
                    {
                        ret.Item1.Add(e.FullName);
                    }
                });
            }
            return ret;
        }

        /// <summary>
        /// Pulls a file or directory from the device to the local machine
        /// </summary>
        /// <param name="remotePath">Path to the remote file/directory</param>
        /// <param name="localPath">Path to the local folder/file</param>
        public void ReadFile(string remotePath, string localPath)
        {
            Pull(remotePath, localPath);
        }

        /// <summary>
        /// Reads all the lines from a remote file
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <returns>Array of lines; or null</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="FileNotFoundException">Remote file item was not found</exception>
        /// <exception cref="UnauthorizedAccessException">no permission to read the remote file contents</exception>
        /// <exception cref="DeviceNotFoundException">Device is not found or is in offline state</exception>
        public string[] Cat(string remotePath)
        {
            return ReadAllLines(remotePath);
        }
       
        /// <summary>
        /// Writes a local file or folder to a remote file/directory.
        /// </summary>
        /// <param name="localPath">Local file/folder</param>
        /// <param name="remotePath">Remote directory/file</param>
        public void WriteFile(string localPath, string remotePath)
        {
            Push(localPath, remotePath);
        }

        /// <summary>
        /// Writes a local file or folder to a remote file/directory
        /// </summary>
        /// <param name="localPath">Local file/folder</param>
        /// <param name="remotePath">Remote directory/file</param>
        /// <param name="sync">Value indicating whether to sync the file if exists</param>
        public void WriteFile(string localPath, string remotePath, bool sync)
        {
            Push(localPath, remotePath, sync, false);
        }

        /// <summary>
        /// Gets the size of the file
        /// </summary>
        /// <param name="remotePath">Path to the remote file system item</param>
        /// <returns>The size of the file system item</returns>
        public long GetFileSize(string remotePath)
        {
            return GetSize(remotePath);
        }

        #endregion

        #region "Path validation"

        /// <summary>
        /// Validates a local file path
        /// </summary>
        /// <param name="path">Local file path</param>
        /// <exception cref="ArgumentNullException">Path is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.
        private void ValidateLocalPath(string path)
        {
            if (path == null)
            {
                throw new ArgumentNullException("path");
            }

            if (Path.GetDirectoryName(path).Length >= WINDOWS_PATH_MAX)
            {
                throw new PathTooLongException("Path too long: " + path.Length.ToString());
            }
            if (Path.GetFileName(path).Length >= WINDOWS_FILE_NAME_MAX)
            {
                throw new PathTooLongException("File name too long: " + Path.GetFileName(path).Length);
            }
            if (string.IsNullOrEmpty(path) || 
                path.ToCharArray().All(ch => ch == ' ') ||
                Path.GetInvalidPathChars().Any(ch => Path.GetDirectoryName(path).Contains(ch)) ||
                Path.GetInvalidFileNameChars().Any(ch => Path.GetFileName(path).Contains(ch)))
            {
                throw new ArgumentException(string.Format("Invalid path: {0}", path));
            }
        }

        /// <summary>
        /// Validates a remote file path
        /// </summary>
        /// <param name="remotePath">Remote file path</param>
        /// <exception cref="ArgumentNullException">Path is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.
        private void ValidateRemotePath(string remotePath)
        {
            if (remotePath == null)
            {
                throw new ArgumentNullException("remotePath");
            }
            if (remotePath.Length > (LINUX_PATH_MAX - 1)) // 1 for NULL
            {
                throw new PathTooLongException("Path too long: " + remotePath.Length.ToString());
            }
            if (LinuxPath.GetFileName(remotePath.TrimEnd('/')).Length > (LINUX_FILE_NAME_MAX - 1))
            {
                throw new PathTooLongException("File name too long: " + LinuxPath.GetFileName(remotePath.TrimEnd('/')).Length);
            }
            
            var path = LinuxPath.GetDirectoryName(remotePath.TrimEnd('/'));
            var filename = LinuxPath.GetFileName(remotePath.TrimEnd('/'));
            var isValid = true;
            if (string.IsNullOrEmpty(remotePath) ||
                remotePath.ToCharArray().All(ch => ch == ' ') ||
                LinuxPath.GetInvalidPathChars().Any(ch => path.Contains(ch)) ||
                LinuxPath.GetInvalidFileNameChars().Any(ch => ch != '\\' && filename.Contains(ch)))
            {
                isValid = false;
            }
            else if (filename.Contains('\\'))
            {
                for (int i = 0; i < filename.Length; i++)
                {
                    if (filename[i] == '\\' && (i == filename.Length - 1 || filename[i + 1] != ' '))
                    {
                        isValid = false;
                    }
                }
            }
            if (!isValid)
            {
                throw new ArgumentException(string.Format("Invalid remote path: {0}", remotePath));
            }
        }

        #endregion

        #region "Link resolving"

        /// <summary>
        /// Resolves a link path
        /// </summary>
        /// <param name="remotePath">remote link path to be resolved</param>
        /// <returns>Resolved link path</returns>
        /// <exception cref="ArgumentNullException">Path is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.
        public string ResolveLink(string remotePath)
        {
            ValidateRemotePath(remotePath);

            var formatted = FormatPath(remotePath);
            var receiver = new LinkResolverReceiver(formatted);
            var command = string.Format("realpath {0}", formatted);
            ExecuteFileCommand(command, receiver);
            return receiver.RealPath;
        }

        #endregion

        #region "Move & Copy"

        /// <summary>
        /// Moves a specified file to a new location, providing the option to specify
        /// a new file name. Overwriting a file of the same name is not allowed.
        /// </summary>
        /// <param name="remoteSource">The name of the file to move.</param>
        /// <param name="remoteDestination">The new path for the file.</param>
        /// <exception cref="System.ArgumentException">remoteSource or remoteDestination is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remoteSource or remoteDestination is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="System.IO.FileNotFoundException">The file specified in remoteSource.</exception>
        /// <exception cref="System.IO.DirectoryNotFoundException">The path specified in remoteSource or remoteDestination 
        /// is invalid</exception>
        /// <exception cref="System.UnauthorizedAccessException">The caller does not have the required permission eiher to read the source
        /// or to write to destinaton or to replace an existing destination file.</exception>
        /// <returns>true if the operation was succefully performed; otherwise, false</returns>
        public bool Move(string remoteSource, string remoteDestination)
        {
            return Move(remoteSource, remoteDestination, false);
        }

        /// <summary>
        /// Moves a specified file to a new location, providing the option to specify
        /// a new file name. Overwriting a file of the same name is allowed.
        /// </summary>
        /// <param name="remoteSource">The name of the file to move.</param>
        /// <param name="remoteDestination">The new path for the file.</param>
        /// <param name="overwrite">true if the destination file can be overwritten; otherwise, false.</param>
        /// <exception cref="System.ArgumentException">remoteSource or remoteDestination is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remoteSource or remoteDestination is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="System.IO.FileNotFoundException">The file specified in remoteSource.</exception>
        /// <exception cref="System.IO.DirectoryNotFoundException">The path specified in remoteSource or remoteDestination 
        /// is invalid</exception>
        /// <exception cref="System.UnauthorizedAccessException">The caller does not have the required permission eiher to read the source
        /// or to write to destinaton or to replace an existing destination file.</exception>
        /// <returns>true if the operation was succefully performed; otherwise, false</returns>
        public bool Move(string remoteSource, string remoteDestination, bool overwrite)
        {
            ValidateRemotePath(remoteSource);
            ValidateRemotePath(remoteDestination);
            
            var source = FormatPath(remoteSource);
            var destination = FormatPath(remoteDestination);
            var sourceFolder = FormatDirectoryPath(LinuxPath.GetDirectoryName(remoteSource));
            var destinationFolder = FormatDirectoryPath(LinuxPath.GetDirectoryName(remoteDestination));

            var command = string.Format("do_move=0; if [[ -r {0} && -w {2} ]] && [ -d {2} -o -L {2} ]; then if [ -e {1} ] && [ -w {1} ] && {3}; then do_move=1; elif [ ! -e {1} ]; then do_move=1; elif [ -e {1} ] && [ ! -w {1} ] && {3}; then echo WRITE_DENIED; fi; elif [ ! -f {0} ]; then echo FILE_NOT_FOUND; elif [ ! -d {2} ]; then echo DIRECTORY_NOT_FOUND; elif [ ! -r {0} ]; then echo READ_DENIED; elif [ ! -w {2} ]; then echo WRITE_DENIED; fi; if [ $do_move == 1 ]; then mv {0} {1}; fi && if [ -e {1} ]; then echo true; fi",
                source, destination, destinationFolder, overwrite.ToString().ToLower());
            var receiver = new IOReceiver();

            ExecuteFileCommand(command, receiver);

            if (receiver.Success)
            {
                RefreshDirectory(sourceFolder);
                RefreshDirectory(destinationFolder);
                return true;
            }

            if (receiver.FileNotFound)
            {
                throw new FileNotFoundException(remoteSource);
            }

            if (receiver.DirectoryNotFound)
            {
                throw new DirectoryNotFoundException(destinationFolder);
            }

            if (receiver.ReadDenied)
            {
                throw new UnauthorizedAccessException(remoteSource);
            }

            if (receiver.WriteDenied)
            {
                throw new UnauthorizedAccessException(remoteDestination);
            }

            return false;
        }

        /// <summary>
        ///  Copies an existing file to a new file. Overwriting a file of the same name
        ///  is not allowed.
        /// </summary>
        /// <param name="remoteSource">The file to copy.</param>
        /// <param name="remoteDestination">The name of the destination file. This cannot be a directory.</param>
        /// <exception cref="System.ArgumentException">remoteSource or remoteDestination is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remoteSource or remoteDestination is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="System.IO.FileNotFoundException">The file specified in remoteSource.</exception>
        /// <exception cref="System.IO.DirectoryNotFoundException">The path specified in remoteSource or remoteDestination 
        /// is invalid</exception>
        /// <exception cref="System.UnauthorizedAccessException">The caller does not have the required permission eiher to read the source
        /// or to write to destinaton or to replace an existing destination file.</exception>
        /// <returns>true if the operation was succefully performed; otherwise, false</returns>
        public bool Copy(string remoteSource, string remoteDestination)
        {
            return Copy(remoteSource, remoteDestination, false);
        }

        /// <summary>
        ///  Copies an existing file to a new file. Overwriting a file of the same name
        ///  is allowed.
        /// </summary>
        /// <param name="remoteSource">The file to copy.</param>
        /// <param name="remoteDestination">The name of the destination file. This cannot be a directory.</param>
        /// <param name="overwrite">true if the destination file can be overwritten; otherwise, false.</param>
        /// <exception cref="System.ArgumentException">remoteSource or remoteDestination is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remoteSource or remoteDestination is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="System.IO.FileNotFoundException">The file specified in remoteSource.</exception>
        /// <exception cref="System.IO.DirectoryNotFoundException">The path specified in remoteSource or remoteDestination 
        /// is invalid</exception>
        /// <exception cref="System.UnauthorizedAccessException">The caller does not have the required permission eiher to read the source
        /// or to write to destinaton or to replace an existing destination file.</exception>
        /// <returns>true if the operation was succefully performed; otherwise, false</returns>
        public bool Copy(string remoteSource, string remoteDestination, bool overwrite)
        {
            ValidateRemotePath(remoteSource);
            ValidateRemotePath(remoteDestination);

            var source = FormatFilePath(remoteSource);
            var destination = FormatFilePath(remoteDestination);
            var destinationFolder = FormatDirectoryPath(LinuxPath.GetDirectoryName(remoteDestination));

            var command = string.Format("do_copy=0; if [[ -d {2} && -f {0} && -r {0} && -w {2} ]]; then if [ -f {1} ] && {3}; then do_copy=1; elif [ ! -f {1} ]; then do_copy=1; fi; elif [ ! -f {0} ]; then echo FILE_NOT_FOUND; elif [ ! -d {2} ]; then echo DIRECTORY_NOT_FOUND; elif [ ! -r {0} ]; then echo READ_DENIED; elif [[ -d {2} && ! -w {2} ]]; then echo WRITE_DENIED; fi; if [ $do_copy == 1 ]; then cp {0} {1}; fi && if [[ -f {0} && -f {1} ]]; then echo true; fi",
                source, destination, destinationFolder, overwrite.ToString().ToLower());
            var receiver = new IOReceiver();

            ExecuteFileCommand(command, receiver);

            if (receiver.Success)
            {
                RefreshDirectory(destinationFolder);
                return true;
            }

            if (receiver.FileNotFound)
            {
                throw new FileNotFoundException(remoteSource);
            }

            if (receiver.DirectoryNotFound)
            {
                throw new DirectoryNotFoundException(destinationFolder);
            }

            if (receiver.ReadDenied)
            {
                throw new UnauthorizedAccessException(remoteSource);
            }

            if (receiver.WriteDenied)
            {
                throw new UnauthorizedAccessException(remoteDestination);
            }

            return false;
        }

        #endregion

        #region "Create"

        /// <summary>
        /// Creates a new file
        /// </summary>
        /// <param name="remotePath">Remote file path</param>
        /// <param name="overwrite">Whether to overwrite an existing file</param>
        /// <returns>True is operation was successfully performed; otherwise, false</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="System.UnauthorizedAccessException">The caller does not have the required permission to
        /// create the directory to specified location.</exception>
        public bool CreateFile(string remotePath)
        {
            return CreateFile(remotePath, true, null);
        }

        /// <summary>
        /// Creates a new file
        /// </summary>
        /// <param name="remotePath">Remote file path</param>
        /// <param name="overwrite">Whether to overwrite an existing file</param>
        /// <returns>True is operation was successfully performed; otherwise, false</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="System.UnauthorizedAccessException">The caller does not have the required permission to
        /// create the directory to specified location.</exception>
        public bool CreateFile(string remotePath, bool overwrite)
        {
            return CreateFile(remotePath, overwrite, null);
        }

        /// <summary>
        /// Creates a new file
        /// </summary>
        /// <param name="remotePath">Remote file path</param>
        /// <param name="overwrite">Whether to overwrite an existing file</param>
        /// <param name="text">Text to write/append to a new/existing file</param>
        /// <returns>True is operation was successfully performed; otherwise, false</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="System.UnauthorizedAccessException">The caller does not have the required permission to
        /// create the directory to specified location.</exception>
        private bool CreateFile(string remotePath, bool overwrite, string text)
        {
            ValidateRemotePath(remotePath);

            var append = !overwrite && !string.IsNullOrEmpty(text);

            var formatted = FormatFilePath(remotePath);
            var parent = LinuxPath.GetDirectoryName(formatted.TrimEnd('/'));
            var receiver = new IOReceiver();
            var command = string.Format("do_create=0; if [ -d {1} ]; then if [[ -f {0} && -w {0} ]] && ( {2} || {5} ); then do_create=1; elif [[ ! -f {0} && -w {1} ]]; then do_create=1; elif [[ -f {0} && ! -w {0} ]] || [ ! -w {1} ]; then echo WRITE_DENIED; fi; elif [ ! -d {1} ]; then echo DIRECTORY_NOT_FOUND; fi; if [ $do_create == 1 ]; then {3} {4} {0}; fi; if [ -f {0} ]; then echo true; fi",
                formatted, parent, overwrite.ToString().ToLower(),
                string.IsNullOrEmpty(text) ? "" : string.Format("echo \"{0}\"", text), (append ? ">>" : ">"), append.ToString().ToLower());

            ExecuteFileCommand(command, receiver);

            if (receiver.Success)
            {
                if (append) RefreshDirectory(parent);
                return true;
            }

            if (receiver.WriteDenied)
            {
                throw new UnauthorizedAccessException(formatted);
            }

            if (receiver.DirectoryNotFound)
            {
                throw new DirectoryNotFoundException(parent);
            }

            return false;
        }

        /// <summary>
        /// Creates all directories and subdirectories in the specified path.
        /// </summary>
        /// <param name="remotePath">The directory path to create.</param>
        /// <param name="overwrite">true if the directory was successfully created or already exists</param>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="System.UnauthorizedAccessException">The caller does not have the required permission to
        /// create the directory to specified location.</exception>
        public bool CreateDirectory(string remotePath)
        { 
            ValidateRemotePath(remotePath);

            var formatted = FormatDirectoryPath(remotePath);

            var delim = '|';
            var command = string.Format("path=\"{1}\"; items=(${{path//{2}/ }}); parent=\"\"; for x in \"${{items[@]}}\"; do if [ -d $parent/$x ]; then parent=$parent/$x; else break; fi; done; parent=$parent/; if [ ! -w $parent ]; then echo WRITE_DENIED:$parent; else mkdir -p {0}; fi; if [ -d {0} ]; then echo true; fi",
                formatted, formatted.TrimEnd('/').Replace('/', delim), delim);
            command = command.Replace("{", "{{").Replace("}", "}}");
            var receiver = new IOReceiver();

            ExecuteFileCommand(command, receiver);

            if (receiver.Success)
            {
                RefreshDirectory(FormatDirectoryPath(remotePath));
                return true;
            }

            else if (receiver.WriteDenied)
            {
                throw new UnauthorizedAccessException(receiver.Message??remotePath);
            }

            return false;

        }

        #endregion

        #region "Write text"

        /// <summary>
        /// Writes all the text lines into a file. If the file exists, it is overwritten.
        /// </summary>
        /// <param name="remotePath">Path to a remote file</param>
        /// <param name="contents">Lines to write</param>
        /// <returns>True is operation was successfully performed; otherwise, false</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null; or contents is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="System.UnauthorizedAccessException">The caller does not have the required permission to
        /// create the directory to specified location.</exception>
        public bool WriteAllLines(string remotePath, IEnumerable<string> contents)
        {
            ValidateRemotePath(remotePath);

            if (contents == null)
            {
                throw new ArgumentNullException("contents");
            }

            var builder = new StringBuilder();
            contents.ToList().ForEach(line => builder.AppendLine(line));

            return CreateFile(remotePath, true, builder.ToString());
        }

        /// <summary>
        /// Writes all the text into a file. If the file exists, it is overwritten.
        /// </summary>
        /// <param name="remotePath">Path to a remote file</param>
        /// <param name="contents">Text to write</param>
        /// <returns>True is operation was successfully performed; otherwise, false</returns>
        /// <exception cref="System.ArgumentException">remotePath is a zero-length string, contains only white
        /// space, or contains invalid characters</exception>
        /// <exception cref="System.ArgumentNullException">remotePath is null</exception>
        /// <exception cref="System.IO.PathTooLongException">The specified path, file name, or both exceed the 
        /// system-defined maximum length.</exception>
        /// <exception cref="System.UnauthorizedAccessException">The caller does not have the required permission to
        /// create the directory to specified location.</exception>
        public bool WriteAllText(string remotePath, string contents)
        {
            ValidateRemotePath(remotePath);

            if (contents == null)
            {
                throw new ArgumentNullException("contents");
            }
            return CreateFile(remotePath, true, contents);
        }

        #endregion

        #region "Append"

        /// <summary>
        /// Appends all the text to a remote file; creates the file if does not exist
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <param name="text">Text to append</param>
        /// <returns>True if successfully appended; otherwise, false</returns>
        /// <exception cref="ArgumentNullException">Path is null or text is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.
        public bool AppendAllText(string remotePath, string text)
        {
            ValidateRemotePath(remotePath);

            if (text == null)
            {
                throw new ArgumentNullException("text");
            }
            return CreateFile(remotePath, false, text);
        }

        /// <summary>
        /// Appends all lines to a remote file; creates the file if does not exist
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <param name="contents">Lines to append</param>
        /// <returns>True if successfully appended; otherwise, false</returns>
        /// <exception cref="ArgumentNullException">Path is null or contents is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.
        public bool AppendAllLines(string remotePath, IEnumerable<string> contents)
        {
            ValidateRemotePath(remotePath);

            if (contents == null)
            {
                throw new ArgumentNullException("contents");
            }
            var builder = new StringBuilder();
            contents.ToList().ForEach(line => builder.AppendLine(line));
            return AppendAllText(remotePath, builder.ToString());
        }

        #endregion

        #region "Remove"

        /// <summary>
        /// Removes a remote file
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <returns>True is operation was successfully performed; otherwise, false</returns>
        /// <exception cref="ArgumentNullException">Path is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.</exception>
        /// <exception cref="UnauthorizedAccessException">No permission to remove the file</exception>
        public bool RemoveFile(string remotePath)
        {
            return RemoveFile(remotePath, false);
        }

        /// <summary>
        /// Removes a remote file
        /// </summary>
        /// <param name="remotePath">Path to the remote file</param>
        /// <param name="forced">Whether to try force</param>
        /// <returns>True if operation was successfully performed; otherwise, false</returns>
        /// <exception cref="ArgumentNullException">Path is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.</exception>
        /// <exception cref="UnauthorizedAccessException">No permission to remove the file</exception>
        public bool RemoveFile(string remotePath, bool forced)
        {
            ValidateRemotePath(remotePath);

            var formatted = FormatFilePath(remotePath);
            if (forced)
            {
                SetAttributes(formatted, 7);
            }
            if (Remove(formatted))
            {
                RefreshDirectory(LinuxPath.GetDirectoryName(formatted.TrimEnd('/')));
                return true;
            }

            return false;
        }

        /// <summary>
        /// Removes a remote directory
        /// </summary>
        /// <param name="remotePath">Path to the remote directory</param>
        /// <returns>True if operation was successfully performed; otherwise, false</returns>
        /// <exception cref="ArgumentNullException">Path is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.</exception>
        /// <exception cref="UnauthorizedAccessException">No permission to remove the file</exception>
        public bool RemoveDirectory(string remotePath)
        {
            return RemoveDirectory(remotePath, false);
        }

        /// <summary>
        /// Removes a remote directory
        /// </summary>
        /// <param name="remotePath">Path to the remote directory</param>
        /// <param name="forced">Whether to try force</param>
        /// <returns>True if operation was successfully performed; otherwise, false</returns>
        /// <exception cref="ArgumentNullException">Path is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.</exception>
        /// <exception cref="UnauthorizedAccessException">No permission to remove the file</exception>
        public bool RemoveDirectory(string remotePath, bool forced)
        {
            ValidateRemotePath(remotePath);

            var formatted = FormatDirectoryPath(remotePath);

            if (forced)
            {
                SetAttributes(formatted, 7);
            }

            if (Remove(formatted))
            {
                RefreshDirectory(LinuxPath.GetDirectoryName(formatted.TrimEnd('/')));
                return true;
            }

            return false;
        }

        /// <summary>
        /// Removes a remote file item
        /// </summary>
        /// <param name="remotePath">Path to the remote file item</param>
        /// <returns>True if operation was successfully performed; otherwise, false</returns>
        /// <exception cref="UnauthorizedAccessException">No permission to remove the file item</exception>
        private bool Remove(string remotePath)
        {
            var receiver = new IOReceiver();
            var command = string.Format("if [ -d {0} ] && [ -w {0} ]; then rm -f -r {0}; elif [[ -f {0} || -x {0} || -L {0} ]] && [ -w {0} ]; then rm -f {0}; elif [ -e {0} ] && [ ! -w {0} ]; then echo WRITE_DENIED; fi && if [ ! -e {0} ]; then echo true; fi", 
                remotePath);

            ExecuteFileCommand(command, receiver);

            if (receiver.Success) return true;
            
            else if (receiver.WriteDenied)
            {
                throw new UnauthorizedAccessException(remotePath);
            }
                       
            return false;
        }

        /// <summary>
        /// Removes a remote file item
        /// </summary>
        /// <param name="remotePath">Path to the remote directory</param>
        /// <returns>True if operation was successfully performed; otherwise, false</returns>
        /// <exception cref="ArgumentNullException">Path is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.</exception>
        /// <exception cref="UnauthorizedAccessException">No permission to remove the file item</exception>
        public bool RemoveItem(string remotePath)
        {
            return RemoveItem(remotePath, false);
        }

        /// <summary>
        /// Removes a remote file item
        /// </summary>
        /// <param name="remotePath">Path to the remote directory</param>
        /// <param name="forced">Whether to try force</param>
        /// <returns>True if operation was successfully performed; otherwise, false</returns>
        /// <exception cref="ArgumentNullException">Path is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.</exception>
        /// <exception cref="UnauthorizedAccessException">No permission to remove the file item</exception>
        public bool RemoveItem(string remotePath, bool forced)
        {
            ValidateRemotePath(remotePath);

            var formatted = FormatPath(remotePath);
            if (forced)
            {
                SetAttributes(formatted, 7);
            }
            if (Remove(formatted))
            {
                RefreshDirectory(LinuxPath.GetDirectoryName(formatted.TrimEnd('/')));
                return true;
            }

            return false;
        }

        /// <summary>
        /// Removes remote file items under a given directory
        /// </summary>
        /// <param name="remotePath">Path to the remote directory</param>
        /// <returns>True if all the operations were successfully performed; otherwise, false</returns>
        /// <exception cref="ArgumentNullException">Path is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.</exception>
        /// <exception cref="UnauthorizedAccessException">No permission to remove a file item</exception>
        public bool RemoveItems(string remotePath)
        {
            return RemoveItems(remotePath, false, true);
        }

        /// <summary>
        /// Removes remote file items under a given directory
        /// </summary>
        /// <param name="remotePath">Path to the remote directory</param>
        /// <param name="forced">Whether to try force</param>
        /// <returns>True if all the operations were successfully performed; otherwise, false</returns>
        /// <exception cref="ArgumentNullException">Path is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.</exception>
        /// <exception cref="UnauthorizedAccessException">No permission to remove a file item</exception>
        public bool RemoveItems(string remotePath, bool forced)
        {
            return RemoveItems(remotePath, forced, true);
        }

        /// <summary>
        /// Removes remote file items under a given directory
        /// </summary>
        /// <param name="remotePath">Path to the remote directory</param>
        /// <param name="forced">Whether to try force</param>
        /// <returns>True if all the operations were successfully performed; otherwise, false</returns>
        /// <exception cref="ArgumentNullException">Path is null</exception>
        /// <exception cref="PathTooLongException">Path is too long</exception>
        /// <exception cref="System.ArgumentException">Path is a zero-length string, contains only white space, 
        /// or contains invalid characters.
        /// <exception cref="UnauthorizedAccessException">No permission to remove a file item</exception>
        public bool RemoveItems(string remotePath, bool forced, bool recursive)
        {
            ValidateRemotePath(remotePath);

            var success = false;

            var contents = GetFileSystemItems(remotePath);
                
            if (contents == null) return false;

            contents.ForEach(c =>
                {
                    if (!c.IsRoot && !c.IsRoot)
                    {
                        success &= RemoveFile(c.FullName, forced);
                    }

                    else if (c.IsDirectory && recursive)
                    {
                        success &= RemoveFile(c.FullName, forced);
                    }
                });

            return success;
        }

        #endregion

        #region "Device communication"

        /// <summary>
        /// Executes a file command a remote device
        /// </summary>
        /// <param name="command">Command to execute</param>
        private void ExecuteFileCommand(string command)
        {
            ExecuteFileCommand(command, NullOutputReceiver.Instance);
        }

        /// <summary>
        /// Executes a file command a remote device
        /// </summary>
        /// <param name="command">Command to execute</param>
        /// <param name="receiver">Output receiver</param>
        /// <exception cref="DeviceNotFoundException">If the device is not found or is in offline state</exception>
        private void ExecuteFileCommand(string command, IShellOutputReceiver receiver)
        {
            if (m_tab.IsOnline)
            {
                try
                {
                    m_tab.ExecuteShellCommand(command, receiver, TABInterface.DEFAULT_ADB_TIMEOUT);
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                    //log e
                }
            }
            else
            {
                throw new DeviceNotFoundException(m_tab.SerialNumber);
            }
        }

        #endregion

        #region "File comparison"

        /// <summary>
        /// Checks if the local and remote file contents are the same
        /// </summary>
        /// <param name="localPath">Local file path</param>
        /// <param name="remotePath">Remote file path</param>
        /// <returns>True is same; otherwise, false</returns>
        private bool IsSame(string localPath, string remotePath)
        {
            var hashLocal = MD5.CalculateLocal(localPath);
            var hashRemote = MD5.CalculateRemote(m_tab, remotePath);
            return string.Compare(hashLocal, hashRemote, true) == 0;
        }

        #endregion

        #region "Directory refresh"

        /// <summary>
        /// Refreshes a directory
        /// </summary>
        /// <param name="directoryPath">The path of the directory to be refreshed</param>
        private void RefreshDirectory(string directoryPath)
        {
            if (AutoRefresh)
            {
                var command = string.Format(DIRECTORY_REFRESH_COMMAND, directoryPath.TrimStart('/'));

                Task.Factory.StartNew(() =>
                    {
                        ExecuteFileCommand(command);
                    });
            }
        }

        #endregion

        #region "Path formatting"

        /// <summary>
        /// Formats file path
        /// </summary>
        /// <param name="filePath">File path to format</param>
        /// <returns>Formatted file path</returns>
        internal string FormatFilePath(string filePath)
        {
            return '/' + Format(filePath);
        }

        /// <summary>
        /// Formats directory path
        /// </summary>
        /// <param name="filePath">Directory path to format</param>
        /// <returns>Formatted directory path</returns>
        internal string FormatDirectoryPath(string directoryPath)
        {
            return '/' + Format(directoryPath) + '/';
        }

        /// <summary>
        /// Formats any file path
        /// </summary>
        /// <param name="path">The path to format</param>
        /// <returns>Formatted path</returns>
        private string FormatPath(string path)
        {
            return '/' + Format(path) + (path.EndsWith("/") ? "/" : "");
        }

        /// <summary>
        /// Formats any file path
        /// </summary>
        /// <param name="path">The path to format</param>
        /// <returns>Formatted path</returns>
        private string Format(string path)
        {
            //Remove white spaces from start and end
            path = path.Trim();

            //It's uri: remove the file-prefix, and let's handle the slashes afterwards
            if (path.ToLower().StartsWith("file:"))
            {
                path = path.substring(5);
            }
            
            //It's home: let's replace is with the real home
            else if (path.StartsWith("~"))
            {
                path = Home.TrimEnd('/') + (path.Length > 1 ? path.substring(1) : "");
            }

            //Let's temporarily replace '\ ' (linux white space in file name) with normal white space
            while (path.Contains("\\ "))
            {
                path = path.Replace("\\ ", " ");
            }

            //Let's replace the windows directory separators with ones used in Linux
            path = path.Replace("\\", "/");

            //Let's replace double slashes by single ones
            while (path.Contains("//"))
            {
                path = path.Replace("//", "/");
            }

            //now, replace known white spaces, with linux file name white spaces
            path = path.Replace(" ", "\\ ");

            //Let's replace the slashes from beginning and from end
            path = path.Trim('/');

            return path;
        }

        #endregion
    }
}
