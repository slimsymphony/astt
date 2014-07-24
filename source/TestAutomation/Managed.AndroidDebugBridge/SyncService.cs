using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;
using System.Net.Sockets;
using Managed.Adb.IO;

namespace Managed.Adb
{
    public class SyncService : IDisposable
    {
        private const string OKAY = "OKAY";
        private const string FAIL = "FAIL";
        private const string STAT = "STAT";
        private const string RECV = "RECV";
        private const string DATA = "DATA";
        private const string DONE = "DONE";
        private const string SEND = "SEND";
        private const string LIST = "LIST";
        private const string DENT = "DENT";

        [Flags]
        public enum FileMode
        {
            UNKNOWN = 0x0000, // unknown
            Socket = 0xc000, // type: socket
            SymbolicLink = 0xa000, // type: symbolic link
            Regular = 0x8000, // type: regular file
            Block = 0x6000, // type: block device
            Directory = 0x4000, // type: directory
            Character = 0x2000, // type: character device
            FIFO = 0x1000  // type: fifo
        }

        private const int SYNC_DATA_MAX = 64 * 1024;

        private const int REMOTE_PATH_MAX_LENGTH = 1024;

        #region static members

        static SyncService()
        {
            NullProgressMonitor = new NullSyncProgressMonitor();
        }

        public static NullSyncProgressMonitor NullProgressMonitor { get; private set; }

        private static byte[] DataBuffer { get; set; }

        /// <summary>
        /// Checks the result array starts with the provided code
        /// </summary>
        /// <param name="result">The result array to check</param>
        /// <param name="code">The 4 byte code.</param>
        /// <returns>true if the code matches.</returns>
        private static bool CheckResult(byte[] result, byte[] code)
        {
            if (result.Length >= code.Length)
            {
                for (int i = 0; i < code.Length; i++)
                {
                    if (result[i] != code[i])
                    {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        /// <summary>
        /// Gets the file type from the mode
        /// </summary>
        /// <param name="mode">the file mode flags</param>
        /// <returns></returns>
        private static FileListingService.FileTypes GetFileType(FileMode mode)
        {
            if ((mode & FileMode.Socket) == FileMode.Socket)
            {
                return FileListingService.FileTypes.Socket;
            }

            if ((mode & FileMode.SymbolicLink) == FileMode.SymbolicLink)
            {
                return FileListingService.FileTypes.Link;
            }

            if ((mode & FileMode.Regular) == FileMode.Regular)
            {
                return FileListingService.FileTypes.File;
            }

            if ((mode & FileMode.Block) == FileMode.Block)
            {
                return FileListingService.FileTypes.Block;
            }

            if ((mode & FileMode.Directory) == FileMode.Directory)
            {
                return FileListingService.FileTypes.Directory;
            }

            if ((mode & FileMode.Character) == FileMode.Character)
            {
                return FileListingService.FileTypes.Character;
            }

            if ((mode & FileMode.FIFO) == FileMode.FIFO)
            {
                return FileListingService.FileTypes.FIFO;
            }

            return FileListingService.FileTypes.Other;
        }

        /// <summary>
        /// Create a command with a code and an int values
        /// </summary>
        /// <param name="command">the 4 byte command(STAT, RECV, ...).</param>
        /// <param name="value"></param>
        /// <returns>the byte[] to send to the device through adb</returns>
        private static byte[] CreateRequest(string command, int value)
        {
            return CreateRequest(Encoding.Default.GetBytes(command), value);
        }

        /// <summary>
        /// Create a command with a code and an int values
        /// </summary>
        /// <param name="command">the 4 byte command(STAT, RECV, ...).</param>
        /// <param name="value"></param>
        /// <returns>the byte[] to send to the device through adb</returns>
        private static byte[] CreateRequest(byte[] command, int value)
        {
            byte[] array = new byte[8];

            Array.Copy(command, 0, array, 0, 4);
            value.Swap32bitsToArray(array, 4);

            return array;
        }

        /// <summary>
        /// Creates the data array for a file request. This creates an array with a 4 byte command + the remote file name.
        /// </summary>
        /// <param name="command">the 4 byte command(STAT, RECV, ...).</param>
        /// <param name="path">The path, as a byte array, of the remote file on which to execute the command</param>
        /// <returns>the byte[] to send to the device through adb</returns>
        private static byte[] CreateFileRequest(string command, string path)
        {
            return CreateFileRequest(Encoding.Default.GetBytes(command), Encoding.Default.GetBytes(path));
        }

        /// <summary>
        /// Creates the data array for a file request. This creates an array with a 4 byte command + the remote file name.
        /// </summary>
        /// <param name="command">the 4 byte command(STAT, RECV, ...).</param>
        /// <param name="path">he path, as a byte array, of the remote file on which to execute the command</param>
        /// <returns>the byte[] to send to the device through adb</returns>
        private static byte[] CreateFileRequest(byte[] command, byte[] path)
        {
            byte[] array = new byte[8 + path.Length];

            Array.Copy(command, 0, array, 0, 4);
            path.Length.Swap32bitsToArray(array, 4);
            Array.Copy(path, 0, array, 8, path.Length);

            return array;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="command"></param>
        /// <param name="path"></param>
        /// <param name="mode"></param>
        /// <returns></returns>
        private static byte[] CreateSendFileRequest(string command, string path, FileMode mode)
        {
            return CreateSendFileRequest(Encoding.Default.GetBytes(command), Encoding.Default.GetBytes(path), (int)mode);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="command"></param>
        /// <param name="path"></param>
        /// <param name="mode"></param>
        /// <returns></returns>
        private static byte[] CreateSendFileRequest(byte[] command, byte[] path, int mode)
        {
            string modeString = string.Format(",{0}", OctetAnd(mode, 0777));
            byte[] modeContent = null;
            try
            {
                modeContent = Encoding.Default.GetBytes(modeString);
            }
            catch (EncoderFallbackException)
            {
                return null;
            }

            byte[] array = new byte[8 + path.Length + modeContent.Length];
            Array.Copy(command, 0, array, 0, 4);
            (path.Length + modeContent.Length).Swap32bitsToArray(array, 4);
            Array.Copy(path, 0, array, 8, path.Length);
            Array.Copy(modeContent, 0, array, 8 + path.Length, modeContent.Length);

            return array;
        }

        #endregion

        /// <summary>
        /// 
        /// </summary>
        /// <param name="device"></param>
        public SyncService(Device device)
            : this(AndroidDebugBridge.SocketAddress, device)
        { }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="address"></param>
        /// <param name="device"></param>
        public SyncService(IPEndPoint address, Device device)
        {
            Address = address;
            Device = device;
            Open();
        }

        /// <summary>
        /// 
        /// </summary>
        public IPEndPoint Address { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        private Device Device { get; set; }

        /// <summary>
        /// 
        /// </summary>
        private Socket Channel { get; set; }

        /// <summary>
        /// 
        /// </summary>
        public bool IsOpen
        {
            get
            {
                return Channel != null && Channel.Connected;
            }
        }

        /// <summary>
        /// Opens the connection.
        /// </summary>
        /// <returns></returns>
        public bool Open()
        {
            if (IsOpen)
            {
                return true;
            }

            try
            {
                Channel = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                Channel.Connect(this.Address);
                Channel.Blocking = true;

                // target a specific device
                AdbHelper.Instance.SetDevice(Channel, Device);

                byte[] request = AdbHelper.Instance.FormAdbRequest("sync:");
                AdbHelper.Instance.Write(Channel, request, -1, DdmPreferences.Timeout);

                AdbResponse resp = AdbHelper.Instance.ReadAdbResponse(Channel, false);

                if (!resp.IOSuccess || !resp.Okay)
                {
                    Log.w("ddms:syncservice", "Got timeout or unhappy response from ADB sync req: {0}", resp.Message);
                    Channel.Close();
                    Channel = null;
                    return false;
                }
            }
            catch (IOException)
            {
                Close();
                throw;
            }

            return true;
        }

        /// <summary>
        /// Closes the connection.
        /// </summary>
        public void Close()
        {
            if (Channel != null)
            {
                try
                {
                    Channel.Close();
                }
                catch (IOException)
                { }
                Channel = null;
            }
        }

        /// <summary>
        /// Pulls file(s) or folder(s).
        /// </summary>
        /// <param name="entries">The remote item(s) to pull</param>
        /// <param name="localPath">The local destination. If the entries count is > 1 or if the unique entry is a 
        /// folder, this should be a folder.</param>
        /// <param name="monitor">The progress monitor. Cannot be null.</param>
        /// <returns>a SyncResult object with a code and an optional message.</returns>
        /// <exception cref="ArgumentNullException">Throws if monitor is null</exception>
        public SyncResult Pull(IEnumerable<FileEntry> entries, string localPath, ISyncProgressMonitor monitor)
        {
            if (monitor == null)
            {
                throw new ArgumentNullException("monitor", "Monitor cannot be null");
            }

            // first we check the destination is a directory and exists
            DirectoryInfo d = new DirectoryInfo(localPath);
            if (!d.Exists)
            {
                return new SyncResult(ErrorCodeHelper.RESULT_NO_DIR_TARGET);
            }

            if (!d.IsDirectory())
            {
                return new SyncResult(ErrorCodeHelper.RESULT_TARGET_IS_FILE);
            }

            // get a FileListingService object
            FileListingService fls = new FileListingService(Device);

            // compute the number of file to move
            long total = GetTotalRemoteFileSize(entries, fls);

            // start the monitor
            monitor.Start(total);

            SyncResult result = DoPull(entries, localPath, fls, monitor);

            monitor.Stop();

            return result;
        }

        /// <summary>
        /// Pulls a single file.
        /// </summary>
        /// <param name="remote">remote the remote file</param>
        /// <param name="localFilename">The local destination.</param>
        /// <param name="monitor">The progress monitor. Cannot be null.</param>
        /// <returns>a SyncResult object with a code and an optional message.</returns>
        /// <exception cref="ArgumentNullException">Throws if monitor is null</exception>
        public SyncResult PullFile(FileEntry remote, string localFilename, ISyncProgressMonitor monitor)
        {
            if (monitor == null)
            {
                throw new ArgumentNullException("monitor", "Monitor cannot be null");
            }

            long total = remote.Size;
            monitor.Start(total);

            SyncResult result = DoPullFile(remote.FullPath, localFilename, monitor);

            monitor.Stop();
            return result;
        }

        /// <summary>
        /// Pulls a single file.
        /// <para>Because this method just deals with a string for the remote file instead of FileEntry, 
        /// the size of the file being pulled is unknown and the ISyncProgressMonitor will not properly 
        /// show the progress</para>
        /// </summary>
        /// <param name="remoteFilepath">the full path to the remote file</param>
        /// <param name="localFilename">The local destination.</param>
        /// <param name="monitor">The progress monitor. Cannot be null.</param>
        /// <returns>a SyncResult object with a code and an optional message.</returns>
        /// <exception cref="ArgumentNullException">Throws if monitor is null</exception>
        public SyncResult PullFile(string remoteFilepath, string localFilename, ISyncProgressMonitor monitor)
        {
            if (monitor == null)
            {
                throw new ArgumentNullException("monitor", "Monitor cannot be null");
            }

            long totalWork = 0;
            try
            {
                FileListingService fls = new FileListingService(Device);
                FileEntry remoteFileEntry = fls.FindFileEntry(remoteFilepath);
                totalWork = remoteFileEntry.Size;
            }
            catch (FileNotFoundException ffe)
            {
                Log.w("ddms", ffe);
            }

            monitor.Start(totalWork);

            SyncResult result = DoPullFile(remoteFilepath, localFilename, monitor);

            monitor.Stop();
            return result;
        }

        /// <summary>
        /// Push several files.
        /// </summary>
        /// <param name="local">An array of loca files to push</param>
        /// <param name="remote">the remote FileEntry representing a directory.</param>
        /// <param name="monitor">The progress monitor. Cannot be null.</param>
        /// <returns>a SyncResult object with a code and an optional message.</returns>
        /// <exception cref="ArgumentNullException">Throws if monitor is null</exception>
        public SyncResult Push(IEnumerable<String> local, FileEntry remote, ISyncProgressMonitor monitor)
        {
            if (monitor == null)
            {
                throw new ArgumentNullException("monitor", "Monitor cannot be null");
            }

            if (!remote.IsDirectory)
            {
                return new SyncResult(ErrorCodeHelper.RESULT_REMOTE_IS_FILE);
            }

            // make a list of File from the list of string
            List<FileSystemInfo> files = new List<FileSystemInfo>();
            foreach (string path in local)
            {
                files.Add(path.GetFileSystemInfo());
            }

            // get the total count of the bytes to transfer
            long total = GetTotalLocalFileSize(files);

            monitor.Start(total);
            SyncResult result = DoPush(files, remote.FullPath, monitor);
            monitor.Stop();

            return result;
        }

        /// <summary>
        /// Push a single file.
        /// </summary>
        /// <param name="local">the local filepath.</param>
        /// <param name="remote">The remote filepath.</param>
        /// <param name="monitor">The progress monitor. Cannot be null.</param>
        /// <returns>a SyncResult object with a code and an optional message.</returns>
        /// <exception cref="ArgumentNullException">Throws if monitor is null</exception>
        public SyncResult PushFile(string local, string remote, ISyncProgressMonitor monitor)
        {
            if (monitor == null)
            {
                throw new ArgumentNullException("monitor", "Monitor cannot be null");
            }

            FileInfo f = new FileInfo(local);
            if (!f.Exists)
            {
                return new SyncResult(ErrorCodeHelper.RESULT_NO_LOCAL_FILE);
            }

            if (f.IsDirectory())
            {
                return new SyncResult(ErrorCodeHelper.RESULT_LOCAL_IS_DIRECTORY);
            }

            monitor.Start(f.Length);
            SyncResult result = DoPushFile(local, remote, monitor);
            monitor.Stop();

            return result;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="local"></param>
        /// <param name="remotePath"></param>
        /// <param name="monitor"></param>
        /// <returns></returns>
        private SyncResult DoPushFile(string local, string remotePath, ISyncProgressMonitor monitor)
        {
            // this shouldn't happen but still...
            if (!File.Exists(local))
            {
                return new SyncResult(ErrorCodeHelper.RESULT_NO_LOCAL_FILE);
            }

            using (var stream = File.OpenRead(local))
            {
                return PushStream(stream, remotePath, monitor);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="stream"></param>
        /// <param name="remotePath"></param>
        /// <returns></returns>
        public SyncResult PushStream(Stream stream, string remotePath)
        {
            return PushStream(stream, remotePath, new NullSyncProgressMonitor());
        }


        /// <summary>
        /// Push a single file
        /// </summary>
        /// <param name="stream"></param>
        /// <param name="remotePath">the remote file(length max is 1024)</param>
        /// <param name="monitor">the monitor. The monitor must be started already.</param>
        /// <returns>a SyncResult object with a code and an optional message.</returns>
        /// <exception cref="ArgumentNullException">Throws if monitor is null</exception>
        public SyncResult PushStream(Stream stream, string remotePath, ISyncProgressMonitor monitor)
        {
            if (monitor == null)
            {
                throw new ArgumentNullException("monitor", "Monitor cannot be null");
            }

            byte[] msg;

            int timeOut = DdmPreferences.Timeout;

            try
            {
                byte[] remotePathContent = remotePath.GetBytes(AdbHelper.DEFAULT_ENCODING);

                if (remotePathContent.Length > REMOTE_PATH_MAX_LENGTH)
                {
                    return new SyncResult(ErrorCodeHelper.RESULT_REMOTE_PATH_LENGTH);
                }

                // create the header for the action
                msg = CreateSendFileRequest(SEND.GetBytes(), remotePathContent, 0644);
            }
            catch (EncoderFallbackException e)
            {
                return new SyncResult(ErrorCodeHelper.RESULT_REMOTE_PATH_ENCODING, e);
            }
            catch (FileNotFoundException e)
            {
                return new SyncResult(ErrorCodeHelper.RESULT_FILE_READ_ERROR, e);
            }

            // and send it. We use a custom try/catch block to make the difference between
            // file and network IO exceptions.
            try
            {
                AdbHelper.Instance.Write(Channel, msg, -1, timeOut);
            }
            catch (IOException e)
            {
                return new SyncResult(ErrorCodeHelper.RESULT_CONNECTION_ERROR, e);
            }

            // create the buffer used to read.
            // we read max SYNC_DATA_MAX, but we need 2 4 bytes at the beginning.
            if (DataBuffer == null)
            {
                DataBuffer = new byte[SYNC_DATA_MAX + 8];
            }
            byte[] bDATA = DATA.GetBytes();
            Array.Copy(bDATA, 0, DataBuffer, 0, bDATA.Length);

            // look while there is something to read
            while (true)
            {
                // check if we're canceled
                if (monitor.IsCanceled)
                {
                    return new SyncResult(ErrorCodeHelper.RESULT_CANCELED);
                }

                // read up to SYNC_DATA_MAX
                int readCount = 0;
                try
                {
                    readCount = stream.Read(DataBuffer, 8, SYNC_DATA_MAX);
                }
                catch (IOException e)
                {
                    return new SyncResult(ErrorCodeHelper.RESULT_FILE_READ_ERROR, e);
                }

                if (readCount == 0)
                {
                    // we reached the end of the file
                    break;
                }

                // now send the data to the device
                // first write the amount read
                ArrayHelper.Swap32bitsToArray(readCount, DataBuffer, 4);

                // now write it
                try
                {
                    AdbHelper.Instance.Write(Channel, DataBuffer, readCount + 8, timeOut);
                }
                catch (IOException e)
                {
                    return new SyncResult(ErrorCodeHelper.RESULT_CONNECTION_ERROR, e);
                }

                // and advance the monitor
                monitor.Advance(readCount);
            }

            try
            {
                // create the DONE message
                long time = DateTime.Now.CurrentTimeMillis() / 1000;
                msg = CreateRequest(DONE, (int)time);

                // and send it.
                AdbHelper.Instance.Write(Channel, msg, -1, timeOut);

                // read the result, in a byte array containing 2 ints
                //(id, size)
                byte[] result = new byte[8];
                AdbHelper.Instance.Read(Channel, result, -1, timeOut);

                if (!CheckResult(result, OKAY.GetBytes()))
                {
                    if (CheckResult(result, FAIL.GetBytes()))
                    {
                        // read some error message...
                        int len = ArrayHelper.Swap32bitFromArray(result, 4);

                        AdbHelper.Instance.Read(Channel, DataBuffer, len, timeOut);

                        // output the result?
                        string message = DataBuffer.GetString(0, len);
                        Log.e("ddms", "transfer error: " + message);
                        return new SyncResult(ErrorCodeHelper.RESULT_UNKNOWN_ERROR, message);
                    }

                    return new SyncResult(ErrorCodeHelper.RESULT_UNKNOWN_ERROR);
                }
            }
            catch (IOException e)
            {
                return new SyncResult(ErrorCodeHelper.RESULT_CONNECTION_ERROR, e);
            }

            // files pushed have no permissions...
            //Device.FileSystem.Chmod(remotePath, "0666");

            return new SyncResult(ErrorCodeHelper.RESULT_OK);
        }

        /// <summary>
        ///  
        /// </summary>
        /// <param name="files"></param>
        /// <param name="remotePath"></param>
        /// <param name="monitor"></param>
        /// <returns></returns>
        private SyncResult DoPush(IEnumerable<FileSystemInfo> files, string remotePath, ISyncProgressMonitor monitor)
        {
            if (monitor == null)
            {
                throw new ArgumentNullException("monitor", "Monitor cannot be null");
            }

            // check if we're canceled
            if (monitor.IsCanceled)
            {
                return new SyncResult(ErrorCodeHelper.RESULT_CANCELED);
            }

            foreach (FileSystemInfo f in files)
            {
                // check if we're canceled
                if (monitor.IsCanceled)
                {
                    return new SyncResult(ErrorCodeHelper.RESULT_CANCELED);
                }
                // append the name of the directory/file to the remote path
                string dest = LinuxPath.Combine(remotePath, f.Name);

                if (f.Exists)
                {
                    if (f.IsDirectory())
                    {
                        DirectoryInfo fsiDir = f as DirectoryInfo;
                        monitor.StartSubTask(f.FullName, dest);
                        SyncResult result = DoPush(fsiDir.GetFileSystemInfos(), dest, monitor);

                        if (result.Code != ErrorCodeHelper.RESULT_OK)
                        {
                            return result;
                        }

                        monitor.Advance(1);
                    }
                    else if (f.IsFile())
                    {
                        monitor.StartSubTask(f.FullName, dest);
                        SyncResult result = DoPushFile(f.FullName, dest, monitor);
                        if (result.Code != ErrorCodeHelper.RESULT_OK)
                        {
                            return result;
                        }
                    }
                }
            }

            return new SyncResult(ErrorCodeHelper.RESULT_OK);
        }

        /// <summary>
        /// Pulls a remote file
        /// </summary>
        /// <param name="remotePath">the remote file(length max is 1024)</param>
        /// <param name="localPath">the local destination</param>
        /// <param name="monitor">the monitor. The monitor must be started already.</param>
        /// <returns>a SyncResult object with a code and an optional message.</returns>
        /// <exception cref="ArgumentNullException">Throws if monitor is null</exception>
        private SyncResult DoPullFile(string remotePath, string localPath, ISyncProgressMonitor monitor)
        {
            if (monitor == null)
            {
                throw new ArgumentNullException("monitor", "Monitor cannot be null");
            }


            byte[] msg = null;
            byte[] pullResult = new byte[8];

            int timeOut = DdmPreferences.Timeout;

            try
            {
                byte[] remotePathContent = remotePath.GetBytes(AdbHelper.DEFAULT_ENCODING);

                if (remotePathContent.Length > REMOTE_PATH_MAX_LENGTH)
                {
                    return new SyncResult(ErrorCodeHelper.RESULT_REMOTE_PATH_LENGTH);
                }

                // create the full request message
                msg = CreateFileRequest(RECV.GetBytes(), remotePathContent);

                // and send it.
                AdbHelper.Instance.Write(Channel, msg, -1, timeOut);

                // read the result, in a byte array containing 2 ints
                //(id, size)
                AdbHelper.Instance.Read(Channel, pullResult, -1, timeOut);

                // check we have the proper data back
                if (!CheckResult(pullResult, DATA.GetBytes()) && !CheckResult(pullResult, DONE.GetBytes()))
                {
                    return new SyncResult(ErrorCodeHelper.RESULT_CONNECTION_ERROR);
                }
            }
            catch (EncoderFallbackException e)
            {
                return new SyncResult(ErrorCodeHelper.RESULT_REMOTE_PATH_ENCODING, e);
            }
            catch (IOException e)
            {
                return new SyncResult(ErrorCodeHelper.RESULT_CONNECTION_ERROR, e);
            }

            // access the destination file
            FileInfo f = new FileInfo(localPath);

            // create the stream to write in the file. We use a new try/catch block to differentiate
            // between file and network io exceptions.
            FileStream fos = null;
            try
            {
                fos = new FileStream(f.FullName, System.IO.FileMode.Create, FileAccess.Write);
            }
            catch (FileNotFoundException e)
            {
                return new SyncResult(ErrorCodeHelper.RESULT_FILE_WRITE_ERROR, e);
            }

            // the buffer to read the data
            byte[] data = new byte[SYNC_DATA_MAX];

            using (fos)
            {
                // loop to get data until we're done.
                while (true)
                {
                    // check if we're cancelled
                    if (monitor.IsCanceled)
                    {
                        return new SyncResult(ErrorCodeHelper.RESULT_CANCELED);
                    }

                    // if we're done, we stop the loop
                    if (CheckResult(pullResult, DONE.GetBytes()))
                    {
                        break;
                    }
                    if (!CheckResult(pullResult, DATA.GetBytes()))
                    {
                        // hmm there's an error
                        return new SyncResult(ErrorCodeHelper.RESULT_CONNECTION_ERROR);
                    }

                    int length = ArrayHelper.Swap32bitFromArray(pullResult, 4);

                    if (length > SYNC_DATA_MAX)
                    {
                        // buffer overrun!
                        // error and exit
                        return new SyncResult(ErrorCodeHelper.RESULT_BUFFER_OVERRUN);
                    }

                    try
                    {
                        // now read the length we received
                        AdbHelper.Instance.Read(Channel, data, length, timeOut);

                        // get the header for the next packet.
                        AdbHelper.Instance.Read(Channel, pullResult, -1, timeOut);
                    }
                    catch (IOException e)
                    {
                        return new SyncResult(ErrorCodeHelper.RESULT_CONNECTION_ERROR, e);
                    }
                    // write the content in the file
                    try
                    {
                        //fos.Write(data, 0, data.Length);
                        // CHANGE FOR Test Automation Bridge
                        fos.Write(data, 0, length);
                    }
                    catch (IOException e)
                    {
                        return new SyncResult(ErrorCodeHelper.RESULT_FILE_WRITE_ERROR, e);
                    }

                    monitor.Advance(length);
                }

                try
                {
                    fos.Flush();
                }
                catch (IOException e)
                {
                    return new SyncResult(ErrorCodeHelper.RESULT_FILE_WRITE_ERROR, e);
                }
            }
            return new SyncResult(ErrorCodeHelper.RESULT_OK);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="entries"></param>
        /// <param name="localPath"></param>
        /// <param name="fls"></param>
        /// <param name="monitor"></param>
        /// <returns></returns>
        /// <exception cref="System.IO.IOException">Throws if unable to create a file or folder</exception>
        /// <exception cref="System.ArgumentNullException">Throws if the ISyncProgressMonitor is null</exception>
        private SyncResult DoPull(IEnumerable<FileEntry> entries, string localPath, FileListingService fileListingService, ISyncProgressMonitor monitor)
        {
            if (monitor == null)
            {
                throw new ArgumentNullException("monitor", "Monitor cannot be null");
            }

            // check if we're cancelled
            if (monitor.IsCanceled)
            {
                return new SyncResult(ErrorCodeHelper.RESULT_CANCELED);
            }

            // check if we need to create the local directory
            DirectoryInfo localDir = new DirectoryInfo(localPath);

            if (!localDir.Exists)
            {
                localDir.Create();
            }

            foreach (FileEntry e in entries)
            {
                // check if we're cancelled
                if (monitor.IsCanceled)
                {
                    return new SyncResult(ErrorCodeHelper.RESULT_CANCELED);
                }

                // the destination item(folder or file)


                string dest = Path.Combine(localPath, e.Name);

                // get type(we only pull directory and files for now)
                FileListingService.FileTypes type = e.Type;

                if (type == FileListingService.FileTypes.Directory)
                {
                    monitor.StartSubTask(e.FullPath, dest);
                    // then recursively call the content. Since we did a ls command
                    // to get the number of files, we can use the cache
                    FileEntry[] children = fileListingService.GetChildren(e, true, null);
                    SyncResult result = DoPull(children, dest, fileListingService, monitor);
                    if (result.Code != ErrorCodeHelper.RESULT_OK)
                    {
                        return result;
                    }
                    monitor.Advance(1);
                }
                else if (type == FileListingService.FileTypes.File)
                {
                    monitor.StartSubTask(e.FullPath, dest);
                    SyncResult result = DoPullFile(e.FullPath, dest, monitor);
                    if (result.Code != ErrorCodeHelper.RESULT_OK)
                    {
                        return result;
                    }
                }
                else if (type == FileListingService.FileTypes.Link)
                {
                    monitor.StartSubTask(e.FullPath, dest);
                    SyncResult result = DoPullFile(e.FullResolvedPath, dest, monitor);
                    if (result.Code != ErrorCodeHelper.RESULT_OK)
                    {
                        return result;
                    }
                }
                else
                {
                    Log.d("ddms-sync", string.Format("unknown type to transfer: {0}", type));
                }
            }

            return new SyncResult(ErrorCodeHelper.RESULT_OK);
        }

        /// <summary>
        /// compute the recursive file size of all the files in the list. Folder have a weight of 1.
        /// </summary>
        /// <param name="entries">The remote files</param>
        /// <param name="fls">The FileListingService</param>
        /// <returns>The total number of bytes of the specified remote files</returns>
        private long GetTotalRemoteFileSize(IEnumerable<FileEntry> entries, FileListingService fls)
        {
            long count = 0;
            foreach (FileEntry e in entries)
            {
                FileListingService.FileTypes type = e.Type;
                if (type == FileListingService.FileTypes.Directory)
                {
                    // get the children
                    IEnumerable<FileEntry> children = fls.GetChildren(e, false, null);
                    count += GetTotalRemoteFileSize(children, fls) + 1;
                }
                else if (type == FileListingService.FileTypes.File)
                {
                    count += e.Size;
                }
            }

            return count;
        }

        /// <summary>
        /// compute the recursive file size of all the files in the list. Folders have a weight of 1.
        /// </summary>
        /// <param name="files">The local files / folders</param>
        /// <returns>The total number of bytes</returns>
        /// <remarks>This does not check for circular links.</remarks>
        private long GetTotalLocalFileSize(IEnumerable<FileSystemInfo> fsis)
        {
            long count = 0;

            foreach (FileSystemInfo fsi in fsis)
            {
                if (fsi.Exists)
                {
                    if (fsi is DirectoryInfo)
                    {
                        return GetTotalLocalFileSize((fsi as DirectoryInfo).GetFileSystemInfos()) + 1;
                    }
                    else if (fsi is FileInfo)
                    {
                        count += (fsi as FileInfo).Length;
                    }
                }
            }

            return count;
        }

        /// <summary>
        /// Returns the mode of the remote file.
        /// </summary>
        /// <param name="path">the remote file</param>
        /// <returns>the mode if all went well; otherwise, FileMode.UNKNOWN</returns>
        private FileMode ReadMode(string path)
        {
            try
            {
                // create the stat request message.
                byte[] msg = CreateFileRequest(STAT, path);

                AdbHelper.Instance.Write(Channel, msg, -1, DdmPreferences.Timeout);

                // read the result, in a byte array containing 4 ints
                //(id, mode, size, time)
                byte[] statResult = new byte[16];
                AdbHelper.Instance.Read(Channel, statResult, -1, DdmPreferences.Timeout);

                // check we have the proper data back
                if (!CheckResult(statResult, Encoding.Default.GetBytes(STAT)))
                {
                    return FileMode.UNKNOWN;
                }

                // we return the mode(2nd int in the array)
                return (FileMode)statResult.Swap32bitFromArray(4);
            }
            catch (IOException e)
            {
                Log.w("SyncService", e);
                return FileMode.UNKNOWN;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        private static int OctetAnd(int x, int y)
        {
            return Convert.ToInt32(x.ToString(), 8) & Convert.ToInt32(y.ToString(), 8);
        }

        /// <summary>
        /// 
        /// </summary>
        public void Dispose()
        {
            if (IsOpen)
            {
                Close();
            }
        }
    }
}
