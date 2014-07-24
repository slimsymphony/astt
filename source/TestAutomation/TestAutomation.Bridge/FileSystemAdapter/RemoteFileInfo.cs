using Managed.Adb;
using Managed.Adb.IO;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// 
    /// </summary>
    [Serializable]
    public sealed class RemoteFileInfo
    {
        private const string LS_PATTERN_EX = @"^([bcdlsp-][-r][-w][-xsS][-r][-w][-xsS][-r][-w][-xstST])\s+(?:\d{0,})?\s*(\S+)\s+(\S+)\s+(?:\d{1,},\s+)?(\d{1,}|\s)\s+(\w{3}|\d{4})[\s-](?:\s?(\d{1,2})\s?)[\s-]\s?(?:(\d{2}|\d{4}|\s)\s*)?(\d{2}:\d{2}|\s)\s*(.*?)([/@=*\|]?)$";

        private static Regex m_matcher = new Regex(LS_PATTERN_EX, RegexOptions.Compiled);

        /// <summary>
        /// 
        /// </summary>
        public RemoteFileType FileType { get; internal set; }

        /// <summary>
        /// 
        /// </summary>
        public bool IsLink { get { return FileType == RemoteFileType.Link || FileType == RemoteFileType.DirectoryLink; } }
        
        /// <summary>
        /// 
        /// </summary>
        public bool IsDirectory { get { return FileType == RemoteFileType.Directory; } }

        /// <summary>
        /// 
        /// </summary>
        public bool IsFile { get { return FileType == RemoteFileType.File; } }

        /// <summary>
        /// 
        /// </summary>
        public bool IsRoot { get { return !string.IsNullOrEmpty(Name) && Name.Length == 1 && Name[0] == LinuxPath.DirectorySeparatorChar; } }

        /// <summary>
        /// 
        /// </summary>
        public long Length { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public string Extension
        {
            get
            {
                return !string.IsNullOrEmpty(Name) ? LinuxPath.GetExtension(Name) : "";
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public DateTime LastAccessTimeUtc { get; internal set; }

        /// <summary>
        /// 
        /// </summary>
        public DateTime LastAccessTime { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public string Name { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public string FullName
        {
            get
            {
                return !string.IsNullOrEmpty(DirectoryName) && !string.IsNullOrEmpty(Name) ? LinuxPath.Combine(DirectoryName.TrimEnd('/'), Name) :
                    !string.IsNullOrEmpty(Name) ? Name : "";
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public string DirectoryName { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public string LinkName { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public string Info { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public string Group { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public string Owner { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public bool IsExecutable { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public FilePermissions Permissions { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="lsLine"></param>
        /// <param name="directoryName"></param>
        /// <returns></returns>
        internal static RemoteFileInfo Parse(string lsLine, string directoryName)
        {
            return Parse(lsLine, directoryName, TimeSpan.Zero);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="lsLine"></param>
        /// <param name="directoryName"></param>
        /// <param name="timeZoneOffset"></param>
        /// <returns></returns>
        internal static RemoteFileInfo Parse(string lsLine, string directoryName, TimeSpan timeZoneOffset)
        {
            if (string.IsNullOrEmpty(lsLine)) return null;

            var fileInfo = new RemoteFileInfo();

            var m = m_matcher.Match(lsLine.Trim());
            if (!m.Success)
            {
                return null;
            }

            fileInfo.DirectoryName = directoryName;
            fileInfo.Name = m.Groups[9].Value;

            if (string.Compare(fileInfo.Name, ".", true) == 0 || string.Compare(fileInfo.Name, "..", true) == 0)
            {
                // we don't care if the entry is a "." or ".."
                return null;
            }

            // get the rest of the groups
            var permissions = m.Groups[1].Value;
            var owner = m.Groups[2].Value;
            var group = m.Groups[3].Value;
            var isExec = string.Compare(m.Groups[10].Value, "*", true) == 0;

            var sizeData = m.Groups[4].Value.Trim();
            long size = 0;

            if (long.TryParse(string.IsNullOrEmpty(sizeData) ? "0" : sizeData, out size))
            {
                fileInfo.Length = size;
            }

            var date1 = m.Groups[5].Value.Trim();
            var date2 = m.Groups[6].Value.Trim();
            var date3 = m.Groups[7].Value.Trim();

            var date = new DateTime(1970, 1, 1, 0, 0, 0);
            var time = m.Groups[8].Value.Trim();
            if (string.IsNullOrEmpty(time))
            {
                time = date.ToString("HH:mm");
            }
            if (date1.Length == 3)
            {
                // check if we don't have a year and use current if we don't
                var tyear = string.IsNullOrEmpty(date3) ? DateTime.Now.Year.ToString() : date3;
                if (DateTime.TryParseExact(string.Format("{0}-{1}-{2} {3}", date1, date2.PadLeft(2, '0'), tyear, time),
                    "MMM-dd-yyyy HH:mm",
                    CultureInfo.GetCultureInfo("en-us"),
                    DateTimeStyles.None,
                    out date))
                {
                    fileInfo.LastAccessTime = date;
                    fileInfo.LastAccessTimeUtc = date.Subtract(timeZoneOffset);
                }
            }
            else if (date1.Length == 4)
            {
                if (DateTime.TryParseExact(
                    string.Format("{0}-{1}-{2} {3}", date1, date2.PadLeft(2, '0'), date3, time),
                    "yyyy-MM-dd HH:mm",
                    CultureInfo.GetCultureInfo("en-us"),
                    DateTimeStyles.None,
                    out date))
                {
                    fileInfo.LastAccessTime = date;
                    fileInfo.LastAccessTimeUtc = date.Subtract(timeZoneOffset);
                }
            }

            string info = null;
            string linkName = null;

            fileInfo.FileType = RemoteFileType.Other;
            switch (permissions[0])
            {
                case '-':
                    fileInfo.FileType = RemoteFileType.File;
                    break;
                case 'b':
                    fileInfo.FileType = RemoteFileType.Block;
                    break;
                case 'c':
                    fileInfo.FileType = RemoteFileType.Character;
                    break;
                case 'd':
                    fileInfo.FileType = RemoteFileType.Directory;
                    break;
                case 'l':
                    fileInfo.FileType = RemoteFileType.Link;
                    break;
                case 's':
                    fileInfo.FileType = RemoteFileType.Socket;
                    break;
                case 'p':
                    fileInfo.FileType = RemoteFileType.FIFO;
                    break;
            }

            // now check what we may be linking to
            if (fileInfo.FileType == RemoteFileType.Link)
            {
                var segments = fileInfo.Name.Split(new string[] { " -> " }, StringSplitOptions.RemoveEmptyEntries);
                // we should have 2 segments
                if (segments.Length == 2)
                {
                    // update the entry name to not contain the link
                    fileInfo.Name = segments[0];
                    // and the link name
                    info = segments[1];

                    // now get the path to the link
                    var pathSegments = info.Split(new char[] { '/' }, StringSplitOptions.RemoveEmptyEntries);
                    if (pathSegments.Length == 1)
                    {
                        // the link is to something in the same directory,
                        // unless the link is ..
                        if (string.Compare("..", pathSegments[0], false) == 0)
                        {
                            // set the type and we're done.
                            fileInfo.FileType = RemoteFileType.DirectoryLink;
                        }
                        else
                        {
                            // either we found the object already
                            // or we'll find it later.
                        }
                    }
                }

                linkName = info;
                // add an arrow in front to specify it's a link.
                info = string.Format("-> {0}", info);
            }

            //Change the constructor visibility for Marble 2
            fileInfo.Permissions = (FilePermissions)typeof(FilePermissions).GetConstructor(System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance,
                null, new Type[] { typeof(string) }, null).Invoke(new object[] { permissions });

            fileInfo.Owner = owner;
            fileInfo.Group = group;
            fileInfo.IsExecutable = isExec;
            fileInfo.LinkName = linkName;

            if (fileInfo.FileType == RemoteFileType.Link)
            {
                fileInfo.Info = info;
            }

            return fileInfo;
        }
    }
}
