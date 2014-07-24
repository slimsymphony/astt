// -----------------------------------------------------------------------
// <copyright file="FileUtilities.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace MarbleLibrary.Utilities
{
    using System;
    using System.Collections.Generic;
    using System.Globalization;
    using System.IO;
    using System.Linq;
    using System.Security;
    using System.Text;
    using System.Reflection;
    using System.Text.RegularExpressions;
    using System.Xml;
    using System.Xml.Linq;

    using Microsoft.Win32;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public static class FileUtilities
    {
        private const string ParentFolderText = "..\\";

        private const string FolderSeparatorText = "\\";

        private const string DriveLetterSymbolText = ":";

        private const string ComputerNamePrefix = @"\\";

        public const string McuswFileIdentifier = ".mcusw";

        public const string ContentFileIdentifier = ".image";

        public const string LanguageFileIdentifier = ".rofs";

        public const string EraseFileIdentifier = "erase";

        public const string EraseFileExtension = ".bin";

        public const string OldMcuswFileExtension = ".mcusw";

        public const string OldContentFileExtension = "content.image*";

        public const string OldLanguageFileExtension = "rofs.image*";

        public const string DefaultMarbleTestReportFileExtension = ".xml";

        public const string DefaultMarbleTestSetFileExtension = ".testset";

        public const string DefaultMarbleTestReportPackageFileExtension = ".Marble.Test.Report.7z";

        public const string DefaultMarbleTestReportPdfFileExtension = ".pdf";

        public const string DefaultFirmwareVariantPackageLoaderFile = ".vpl";

        public const string DefaultTraceXmlDirectory = @"..\framework\core\data";

        public const string VersionFilePath = @"..\MarbleVersion.txt";

        private static readonly string[] FlashFileExts = {".fpsx", ".fls", ".ima"};
        private static readonly IList<string> FlashFileExtsReadOnly = Array.AsReadOnly(FlashFileExts);

        /// <summary>
        /// Returns a list of allowed flash file extensions.
        /// </summary>
        public static IList<string> FlashFileExtensions
        {
            get { return FlashFileExtsReadOnly; }
        }

        /// <summary>
        /// Returns a filter string for allowed MCUSW files in Open file dialog.
        /// <example>".mcusw;*.mcusw*.fpsx;*.mcusw*.fls;*.mcusw*.ima;"</example>
        /// </summary>
        /// <returns></returns>
        public static string GetMcuswFilter()
        {
            var filter = new StringBuilder(McuswFileIdentifier);
            foreach (string ext in FlashFileExtensions)
                filter.Append(";*" + McuswFileIdentifier + "*" + ext);
            return filter.ToString();
        }

        /// <summary>
        /// Returns a filter string for allowed content files in Open file dialog.
        /// <example>"content.image*;*.image*.fpsx;*.image*.fls;*.image*.ima;"</example>
        /// </summary>
        /// <returns></returns>
        public static string GetContentFilter()
        {
            var filter = new StringBuilder(OldContentFileExtension);
            foreach (string ext in FlashFileExtensions)
                filter.Append(";*" + ContentFileIdentifier + "*" + ext);
            return filter.ToString();
        }

        /// <summary>
        /// Returns a filter string for allowed language files in Open file dialog.
        /// <example>"rofs.image*;*.rofs*.fpsx;*.rofs*.fls;*.rofs*.ima;"</example>
        /// </summary>
        /// <returns></returns>
        public static string GetLanguageFilter()
        {
            var filter = new StringBuilder(OldLanguageFileExtension);
            foreach (string ext in FlashFileExtensions)
                filter.Append(";*" + LanguageFileIdentifier + "*" + ext);
            return filter.ToString();
        }

        /// <summary>
        /// Returns a filter string for allowed erase files in Open file dialog.
        /// <example>"rofs.image*;*.rofs*.fpsx;*.rofs*.fls;*.rofs*.ima;"</example>
        /// </summary>
        /// <returns></returns>
        public static string GetEraseFilter()
        {
            var filter = new StringBuilder(EraseFileIdentifier + "*" + EraseFileExtension);
            
            return filter.ToString();
        }

        /// <summary>
        /// Checks whether given filename qualifies for MCUSW file naming rules.
        /// </summary>
        /// <param name="filename">Filename or filepath to check.</param>
        /// <returns>True if given filename is a properly named MCUSW file, otherwise false.</returns>
        public static bool IsMcuswFile(string filename)
        {
            if (string.IsNullOrEmpty(filename)) return false;

            // Old format
            if (filename.EndsWith(OldMcuswFileExtension)) return true;

            // New format
            return FlashFileExtensions.Contains(Path.GetExtension(filename)) && filename.Contains(McuswFileIdentifier);
        }

        /// <summary>
        /// Checks whether given filename qualifies for content file naming rules.
        /// </summary>
        /// <param name="filename">Filename or filepath to check.</param>
        /// <returns>True if given filename is a properly named content file, otherwise false.</returns>
        public static bool IsContentFile(string filename)
        {
            if (string.IsNullOrEmpty(filename)) return false;

            // Old format
            if (filename.Contains(OldContentFileExtension.Replace("*", string.Empty))) return true;

            // New format
            return FlashFileExtensions.Contains(Path.GetExtension(filename)) && filename.Contains(ContentFileIdentifier);
        }

        /// <summary>
        /// Checks whether given filename qualifies for language file naming rules.
        /// </summary>
        /// <param name="filename">Filename or filepath to check.</param>
        /// <returns>True if given filename is a properly named language file, otherwise false.</returns>
        public static bool IsLanguageFile(string filename)
        {
            if (string.IsNullOrEmpty(filename)) return false;

            // Old format
            if (filename.Contains(OldLanguageFileExtension.Replace("*", string.Empty))) return true;

            // New format
            return FlashFileExtensions.Contains(Path.GetExtension(filename)) && filename.Contains(LanguageFileIdentifier);
        }

        /// <summary>
        /// Checks whether given filename qualifies for erase file naming rules.
        /// </summary>
        /// <param name="filename">Filename or filepath to check.</param>
        /// <returns>True if given filename is a properly named erase file, otherwise false.</returns>
        public static bool IsEraseFile(string filename)
        {
            if (string.IsNullOrEmpty(filename)) return false;

            return filename.EndsWith(EraseFileExtension);
        }

        /// <summary>
        /// Checks whether given filename qualifies for any flash file naming rules.
        /// </summary>
        /// <param name="filename">Filename or filepath to check.</param>
        /// <returns>True if given filename is a properly named flash file, otherwise false.</returns>
        public static bool IsFlashFile(string filename)
        {
            return IsMcuswFile(filename) || IsContentFile(filename) || IsLanguageFile(filename);
        }

        /// <summary>
        /// Replaces invalid characters from a given filename with an underscore '_'.
        /// </summary>
        /// <param name="filename">Filename to convert to a valid one.</param>
        /// <returns>Valid filename with all forbidden characters replaced.</returns>
        public static string GetValidFilename(string filename)
        {
            // Following LINQ expression converted by Resharper from foreach loop
            return Path.GetInvalidFileNameChars().Aggregate(filename, (current, invalidChar) => current.Replace(invalidChar, '_'));
        }

        /// <summary>
        /// Merges folder and file name to full file path.
        /// e.g. "C:\\Temp" as directoryPath, "cache" as file name and ".bin" returns "C:\\Temp\\cache.bin".
        /// </summary>
        /// <param name="directoryPath">Directory path. Can also be relative.</param>
        /// <param name="fileName">File name.</param>
        /// <param name="fileExtension">File extension. Used when file name does not contain file extension.</param>
        /// <returns>Merged file path.</returns>
        public static string MergeFolderAndFileNameToFullFilePath(string directoryPath, string fileName, string fileExtension = null)
        {
            string folder = RemoveFolderSeparatorFromEndOfFolderPath(Directory.GetCurrentDirectory());
            directoryPath = RemoveFolderSeparatorFromEndOfFolderPath(directoryPath);

            if (!String.IsNullOrEmpty(fileExtension))
                if (!fileExtension.StartsWith(".")) fileExtension = "." + fileExtension;

            if (directoryPath.StartsWith(ParentFolderText))
            {
                string tempFolder = directoryPath;

                while (tempFolder.StartsWith(ParentFolderText))
                {
                    tempFolder = tempFolder.Remove(0, ParentFolderText.Count());
                    folder = folder.Remove(folder.LastIndexOf(FolderSeparatorText));
                }

                return folder + FolderSeparatorText + tempFolder + FolderSeparatorText + fileName + fileExtension;
            }

            return (directoryPath.Contains(DriveLetterSymbolText) || directoryPath.StartsWith(ComputerNamePrefix))
                       ? directoryPath + FolderSeparatorText + fileName + fileExtension
                       : folder + FolderSeparatorText + directoryPath + FolderSeparatorText + fileName + fileExtension;
        }

        public static string RemoveFolderSeparatorFromEndOfFolderPath(string folderPath)
        {
            return folderPath.EndsWith(FolderSeparatorText) ? folderPath.Remove(folderPath.LastIndexOf(FolderSeparatorText)) : folderPath;
        }

        /// <summary>
        /// Checks whether the directory exists.
        /// </summary>
        /// <param name="directoryPath">Directory path.</param>
        /// <param name="createDirectoryIfDoesNotExist">Bool indicating whether to create directory if it does not exist.</param>
        /// <returns>Bool indicating whether the directory exists. When directory creation parameter is used, also indicates whether the directory creation was succesful.</returns>
        public static bool CheckDirectory(string directoryPath, bool createDirectoryIfDoesNotExist = false)
        {
            if (Directory.Exists(directoryPath)) return true;
            if (!createDirectoryIfDoesNotExist) return false;

            try
            {
                Directory.CreateDirectory(directoryPath);
            }
            catch (Exception)
            {
                return false;
            }

            return true;
        }

        /// <summary>
        /// Determines whether a file is read-only.
        /// </summary>
        /// <param name="filePath">File path for the file.</param>
        /// <returns>Returns <c>true</c> if the file is read-only otherwise <c>false</c> is returned.</returns>
        public static bool IsFileReadOnly(string filePath)
        {
            bool readOnly = ((File.GetAttributes(filePath) & FileAttributes.ReadOnly) == FileAttributes.ReadOnly);
            return readOnly;
        }

        /// <summary>
        /// Makes a read-only file writable.
        /// </summary>
        /// <param name="filePath">Path for the file to make writable.</param>
        public static void MakeFileWritable(string filePath)
        {
            // Get the file attributes
            FileAttributes attributes = File.GetAttributes(filePath);

            // Remove the read-only attribute from the file
            attributes &= ~FileAttributes.ReadOnly;
            File.SetAttributes(filePath, attributes);
        }

        /// <summary>
        /// Copies directory and all its content including subdirectories.
        /// </summary>
        /// <param name="sourceDirectory">The name of the directory to be copied.</param>
        /// <param name="targetDirectory">The new path for the directory.</param>
        /// <returns>Returns true if operation succeeded.</returns>
        public static bool CopyDirectory(string sourceDirectory, string targetDirectory)
        {
            if (sourceDirectory.Equals(targetDirectory))
                return false;

            DirectoryInfo sourceDirectoryInfo = new DirectoryInfo(sourceDirectory);
            DirectoryInfo targetDirectoryInfo = new DirectoryInfo(targetDirectory);

            // Check if the source directory exists, if not, create it.
            if (!CheckDirectory(sourceDirectoryInfo.FullName, true))
                return false;

            // Check if the target directory exists, if not, create it.
            if (!CheckDirectory(targetDirectoryInfo.FullName, true))
                return false;

            // Copy each file into it's new directory.
            foreach (FileInfo fileInfo in sourceDirectoryInfo.GetFiles())
                fileInfo.CopyTo(Path.Combine(targetDirectoryInfo.ToString(), fileInfo.Name), true);

            // Copy each subdirectory using recursion.
            foreach (DirectoryInfo sourceSubDirectoryInfo in sourceDirectoryInfo.GetDirectories())
            {
                DirectoryInfo nextTargetSubDir = targetDirectoryInfo.CreateSubdirectory(sourceSubDirectoryInfo.Name);
                if (!CopyDirectory(sourceSubDirectoryInfo.FullName, nextTargetSubDir.FullName))
                    return false;
            }

            return true;
        }

        /// <summary>
        /// Renames the source file name with given target file name.
        /// </summary>
        /// <param name="sourceFileName">The name of the file to be renamed.</param>
        /// <param name="targetFileName">The new name for the file.</param>
        /// <returns>Returns true if operation succeeded.</returns>
        public static bool RenameFile(string sourceFileName, string targetFileName)
        {
            try
            {
                // Rename the file. (Move == Rename)
                File.Move(sourceFileName, targetFileName);
            }
            catch (Exception)
            {
                return false;
            }

            return true;
        }

        /// <summary>
        /// Renames the source directory name with given target directory name.
        /// </summary>
        /// <param name="sourceDirectoryName">The name of the directory to be renamed.</param>
        /// <param name="targetDirectoryName">The new name for the directory.</param>
        /// <returns>Returns true if operation succeeded.</returns>
        public static bool RenameDirectory(string sourceDirectoryName, string targetDirectoryName)
        {
            if (sourceDirectoryName.Equals(targetDirectoryName))
                return false;

            try
            {
                // Rename the directory. (Move == Rename)
                Directory.Move(sourceDirectoryName, targetDirectoryName);
            }
            catch (Exception)
            {
                return false;
            }

            return true;
        }

        public static string ShowOpenFileDialogForMcuFile(string directoryPath = "")
        {
            string[] defaultExt = { GetMcuswFilter(), ".*" };
            string[] filterText = { "MCUSW Files", "All Files" };
            return showOpenDialog(directoryPath, defaultExt, filterText);
        }

        public static string ShowOpenFileDialogForContentFile(string directoryPath = "")
        {
            string[] defaultExt = { GetContentFilter(), ".*" };
            string[] filterText = { "Content Files", "All Files" };
            return showOpenDialog(directoryPath, defaultExt, filterText);
        }

        public static string ShowOpenFileDialogForLanguageFile(string directoryPath = "")
        {
            string[] defaultExt = { GetLanguageFilter(), ".*" };
            string[] filterText = { "Language Files", "All Files" };
            return showOpenDialog(directoryPath, defaultExt, filterText);
        }

        public static string ShowOpenFileDialogForEraseFile(string directoryPath = "")
        {
            string[] defaultExt = { GetEraseFilter(), ".*" };
            string[] filterText = { "Erase Files", "All Files" };
            return showOpenDialog(directoryPath, defaultExt, filterText);
        }

        public static string ShowOpenFileDialogForMarbleTestReport(string directoryPath = "")
        {
            string[] defaultExt = { DefaultMarbleTestReportFileExtension + ";*" + DefaultMarbleTestReportPackageFileExtension, ".*" };
            string[] filterText = { "Marble Test Report", "All Files" };
            return showOpenDialog(directoryPath, defaultExt, filterText);
        }

        public static string ShowOpenFileDialogForMarbleTestSet(string directoryPath = "", string defaultSelectedFile = "")
        {
            string[] defaultExt = { DefaultMarbleTestSetFileExtension, ".*" };
            string[] filterText = { "Marble Test Set", "All Files" };
            return showOpenDialog(directoryPath, defaultExt, filterText, defaultSelectedFile);
        }

        public static string ShowOpenFileDialogForLeaderFollowerTestReport(string directoryPath = "")
        {
            string[] defaultExt = { ".cache" };
            string[] filterText = { "Leader-Follower Cache Files" };
            return showOpenDialog(directoryPath, defaultExt, filterText);
        }

        public static string ShowSaveAsFileDialogForMarbleTestReportPackage(string directoryPath = "", string initialFileName = "")
        {
            string[] defaultExt = { DefaultMarbleTestReportPackageFileExtension, ".*" };
            string[] filterText = { "Marble Test Report Package", "All Files" };
            return showSaveAsDialog(directoryPath, defaultExt, filterText, initialFileName);
        }

        public static string ShowSaveAsFileDialogForMarbleTestReportPdf(string directoryPath = "", string initialFileName = "")
        {
            string[] defaultExt = { DefaultMarbleTestReportPdfFileExtension, ".*" };
            string[] filterText = { "PDF Files", "All Files" };
            return showSaveAsDialog(directoryPath, defaultExt, filterText, initialFileName);
        }

        /// <summary>
        /// Opens save file dialog and return file path.
        /// </summary>
        /// <param name="initialFileName"></param>
        /// <param name="defaultExt">File extension (e.g. '.xml').</param>
        /// <param name="filterText">Filter text (e.g. 'Sequence XML').</param>
        /// <param name="initialDirectory"></param>
        /// <returns>File path string.</returns>
        private static string showSaveAsDialog(string initialDirectory, string[] defaultExt, string[] filterText, string initialFileName = "")
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.DefaultExt = defaultExt[0];
            saveFileDialog.FileName = initialFileName;
            
            string filters = string.Empty;
            int index = 0;
            
            foreach (string filter in filterText)
            {
                filters += filter + "|*" + defaultExt[index] + "|";
                index++;
            }

            filters = filters.Remove(filters.Length - 1);
            saveFileDialog.Filter = filters;

            if (!string.IsNullOrEmpty(initialDirectory))
            {
                if (!initialDirectory.EndsWith("\\")) 
                    saveFileDialog.InitialDirectory = initialDirectory + "\\";
                else saveFileDialog.InitialDirectory = 
                    initialDirectory;
            }

            bool? result = saveFileDialog.ShowDialog();

            return result == true ? saveFileDialog.FileName : string.Empty;
        }

        /// <summary>
        /// Opens open file dialog and returns file path.
        /// </summary>
        /// <param name="defaultExt">File extension (e.g. '.xml').</param>
        /// <param name="filterText">Filter text (e.g. 'Sequence XML').</param>
        /// <param name="initialDirectory"></param>
        /// <returns>File path string.</returns>
        private static string showOpenDialog(string initialDirectory, string[] defaultExt, string[] filterText, string defaultSelectedFile = "")
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.DefaultExt = defaultExt[0];
            openFileDialog.RestoreDirectory = true;
            openFileDialog.FileName = defaultSelectedFile;

            string filters = string.Empty;
            int index = 0;

            foreach (string filter in filterText)
            {
                filters += filter + "|*" + defaultExt[index] + "|";
                index++;
            }

            filters = filters.Remove(filters.Length - 1);
            openFileDialog.Filter = filters;

            if (!string.IsNullOrEmpty(initialDirectory))
                openFileDialog.InitialDirectory = initialDirectory;

            bool? result = openFileDialog.ShowDialog();

            return result == true ? openFileDialog.FileName : string.Empty;
        }

        /// <summary>
        /// Forms a relative path between two absolute paths.
        /// </summary>
        /// <param name="fromPath">Start path (e.g. current working directory) as absolute path</param>
        /// <param name="toPath">Target path as absolute path</param>
        /// <returns>Relative path from start path to target path.
        /// Or target path as it is if paths don't share a common prefix.</returns>
        public static string GetRelativePath(string fromPath, string toPath)
        {
            if (string.IsNullOrEmpty(fromPath) || Path.GetPathRoot(fromPath) != Path.GetPathRoot(toPath)) return toPath;

            // Remove possible filename part of the fromPath
            if (Path.GetExtension(fromPath) != string.Empty)
                fromPath = Path.GetDirectoryName(fromPath);

            string[] absoluteDirectories = fromPath.Split('\\');
            string[] relativeDirectories = toPath.Split('\\');

            // Get the shortest of the two paths
            int length = absoluteDirectories.Length < relativeDirectories.Length ? absoluteDirectories.Length : relativeDirectories.Length;

            // Use to determine where in the loop we exited
            int lastCommonRoot = -1;
            int index;

            // Find common root
            for (index = 0; index < length; index++)
                if (absoluteDirectories[index] == relativeDirectories[index])
                    lastCommonRoot = index;
                else
                    break;

            // If we didn't find a common prefix then return the absolute path as it is
            if (lastCommonRoot == -1)
                return toPath;

            // Build up the relative path
            var relativePath = new StringBuilder();

            // Add on the ..
            for (index = lastCommonRoot + 1; index < absoluteDirectories.Length; index++)
                if (absoluteDirectories[index].Length > 0)
                    relativePath.Append("..\\");

            // Add on the folders
            for (index = lastCommonRoot + 1; index < relativeDirectories.Length - 1; index++)
                relativePath.Append(relativeDirectories[index] + "\\");

            if (lastCommonRoot + 1 < relativeDirectories.Length)
                relativePath.Append(relativeDirectories[relativeDirectories.Length - 1]);

            return relativePath.ToString();
        }

        public static string MergeRelativePathToAbsolutePath(string relativePath, string absolutePath, bool endWithBackslash = true)
        {
            if (endWithBackslash)
            {
                if (!relativePath.EndsWith("\\")) relativePath = relativePath + "\\";
            }

            if (absolutePath.EndsWith("\\")) absolutePath = absolutePath.Remove(absolutePath.LastIndexOf("\\"));

            while (relativePath.StartsWith("..\\"))
            {
                relativePath = relativePath.Remove(0, "..\\".Length);

                if (absolutePath.Contains("\\")) absolutePath = absolutePath.Remove(absolutePath.LastIndexOf("\\"));
            }

            return absolutePath + "\\" + relativePath;
        }

        public static string ConvertRelativePathToAbsolutePath(string relativePath, bool endsWithBackslash = false)
        {
            return MergeRelativePathToAbsolutePath(relativePath, Directory.GetCurrentDirectory(), endsWithBackslash);
        }

        public static string GetFileName(string filePath)
        {
            return !filePath.Contains("\\") ? filePath : filePath.Substring(filePath.LastIndexOf("\\") + 1);
        }

        public static bool CheckFilePathListForAbsolutePaths(List<string> filePathList, bool changeRelativePathsToAbsolutePaths = true)
        {
            if (filePathList == null) return false;

            bool wasEveryPathAbsolute = true;

            for (int i = 0; i < filePathList.Count; i++)
            {
                if (Path.IsPathRooted(filePathList[i])) continue;

                if (!changeRelativePathsToAbsolutePaths) return false;

                if (wasEveryPathAbsolute)
                    wasEveryPathAbsolute = false;

                filePathList[i] = Path.GetFullPath(filePathList[i]);
            }

            return wasEveryPathAbsolute;
        }

        public static bool CheckWhetherFileIsMarbleTestReportPackage(string filePath)
        {
            if (string.IsNullOrEmpty(filePath)) return false;
            if (!filePath.EndsWith(DefaultMarbleTestReportPackageFileExtension)) return false;
            if (!File.Exists(filePath)) return false;

            return true;
        }

        /// <summary>
        /// The make relative path.
        /// </summary>
        /// <param name="fromPath">
        /// The from path.
        /// </param>
        /// <param name="toPath">
        /// The to path.
        /// </param>
        /// <returns>
        /// The System.String.
        /// </returns>
        public static string MakeRelativePath(string fromPath, string toPath)
        {
            if (string.IsNullOrEmpty(fromPath)) return null;
            if (string.IsNullOrEmpty(toPath)) return null;

            Uri fromUri = new Uri(fromPath);
            Uri toUri = new Uri(toPath);

            Uri relativeUri = fromUri.MakeRelativeUri(toUri);
            string relativePath = Uri.UnescapeDataString(relativeUri.ToString());

            return relativePath.Replace('/', Path.DirectorySeparatorChar);
        }

        public static bool CheckWhetherDirectoryContainsFirmwareUpdateFiles(string directoryPath, string productRmCode)
        {
            if (string.IsNullOrEmpty(directoryPath)) return false;
            if (string.IsNullOrEmpty(productRmCode)) return false;
            if (!Directory.Exists(directoryPath)) return false;

            string productCodeWithOutSeparator = productRmCode;

            while (productCodeWithOutSeparator.Contains("-"))
            {
                productCodeWithOutSeparator = productCodeWithOutSeparator.Replace("-", string.Empty);
            }

            List<string> fileList =
                Directory.GetFiles(
                    directoryPath, "*" + FileUtilities.DefaultFirmwareVariantPackageLoaderFile, SearchOption.TopDirectoryOnly)
                    .ToList();

            return fileList.Select(Path.GetFileName).Where(
                fileName => !string.IsNullOrEmpty(fileName)).Any(
                    fileName => fileName.ToLower().StartsWith(productCodeWithOutSeparator.ToLower()) || fileName.ToLower().StartsWith(productRmCode.ToLower()));
        }

        public static List<KeyValuePair<string, string>> GetVariantCodesFromDirectoryContainingFirmwareUpdateFiles(string directoryPath, string productRmCode)
        {
            if (!FileUtilities.CheckWhetherDirectoryContainsFirmwareUpdateFiles(directoryPath, productRmCode)) return null;

            string fileNameInfoSeparator = "_";
            string productCodeWithOutSeparator = productRmCode;

            while (productCodeWithOutSeparator.Contains("-"))
            {
                productCodeWithOutSeparator = productCodeWithOutSeparator.Replace("-", string.Empty);
            }

            List<string> fileList =
                Directory.GetFiles(
                    directoryPath, "*" + FileUtilities.DefaultFirmwareVariantPackageLoaderFile, SearchOption.TopDirectoryOnly)
                    .ToList();

            List<KeyValuePair<string, string>> variantCodes = new List<KeyValuePair<string, string>>();

            foreach (string filePath in fileList)
            {
                string fileName = Path.GetFileName(filePath);

                if (fileName.ToLower().StartsWith(productCodeWithOutSeparator.ToLower()) || fileName.ToLower().StartsWith(productRmCode.ToLower()))
                {
                    List<string> fileNameInfo = fileName.Split(new string[] { fileNameInfoSeparator }, StringSplitOptions.RemoveEmptyEntries).ToList();

                    // 2nd part of file name is the variant code.
                    variantCodes.Add(new KeyValuePair<string, string>(fileNameInfo[1], filePath));
                }
            }

            return variantCodes;
        }

        public static string GetRmCodeFromMcuFilePath(string mcuFilePath)
        {
            if (string.IsNullOrEmpty(mcuFilePath)) return string.Empty;

            string fileName = Path.GetFileName(mcuFilePath);
            string rmCode;

            if (string.IsNullOrEmpty(fileName) || !fileName.ToLower().Contains("rm")) return string.Empty;

            if (fileName.ToLower().Contains("rm-"))
            {
                foreach (Match match in Regex.Matches(fileName, "rm-"))
                {
                    int rmCodeNumber;

                    if (int.TryParse(fileName.ToLower().Substring(match.Index + "rm-".Length, 3), out rmCodeNumber))
                    {
                        return "RM-" + rmCodeNumber;
                    }
                }
            }
            else if (fileName.ToLower().Contains("rm"))
            {
                foreach (Match match in Regex.Matches(fileName, "rm"))
                {
                    int rmCodeNumber;

                    if (int.TryParse(fileName.ToLower().Substring(match.Index + "rm".Length, 3), out rmCodeNumber))
                    {
                        return "RM-" + rmCodeNumber;
                    }
                }
            }

            return string.Empty;
        }

        /// <summary>
        /// Load XML document with safe encoding. This prevents XmlExceptions when document contains invalid characters.
        /// </summary>
        /// <param name="filePath">XML document file path.</param>
        /// <returns>The <see cref="XElement"/>.</returns>
        public static XElement LoadXmlDocumentWithSafeEncoding(string filePath)
        {
            XElement xElement = null;

            // Prevents XmlException when document contains invalid characters.
            using (StreamReader streamReader = new StreamReader(filePath, Encoding.GetEncoding("ISO-8859-1")))
            {
                string xmlDocString = string.Empty;

                try
                {
                    xmlDocString = streamReader.ReadToEnd();

                    xElement = XElement.Parse(xmlDocString);
                }
                catch (XmlException xe)
                {
                    try
                    {
                        // Hex values are made safe from XML.
                        string secureString = FileUtilities.ReplaceHexValuesFromXmlString(xmlDocString);

                        xElement = XElement.Parse(secureString);
                    }
                    catch (XmlException)
                    {
                        return null;
                    }
                }
            }

            return xElement;
        }

        /// <summary>
        /// Replaces illegal file name characters in file name with defined text.
        /// </summary>
        /// <param name="fileName">File name.</param>
        /// <param name="replacementTxt">Illegal character replacement text.</param>
        /// <returns>Fixed file name.</returns>
        public static string ReplaceIllegalFileNameChars(string fileName, string replacementTxt = "")
        {
            if (string.IsNullOrEmpty(fileName)) return fileName;

            string fixedFileName = fileName;

            foreach (char c in Path.GetInvalidFileNameChars().Where(c => fixedFileName.Contains(c)))
            {
                fixedFileName = fixedFileName.Replace(c.ToString(CultureInfo.InvariantCulture), replacementTxt);
            }

            return fixedFileName;
        }

        /// <summary>
        /// Returns whether the character is legal or not.
        /// </summary>
        /// <param name="character"></param>
        /// <returns></returns>
        public static bool IsLegalXmlChar(int character)
        {
            return 
                (character == 0x9 ||
                 character == 0xA ||
                 character == 0xD ||
                 (character >= 0x20 && character <= 0xD7FF) ||
                 (character >= 0xE000 && character <= 0xFFFD) ||
                 (character >= 0x10000 && character <= 0x10FFFF));
        }

        /// <summary>
        /// Replaces hex values from XML string with safe values. Values like '&#x8;' cause exceptions in XML.
        /// </summary>
        /// <param name="xmlAsString"></param>
        /// <returns></returns>
        public static string ReplaceHexValuesFromXmlString(string xmlAsString)
        {
            return xmlAsString.Replace("&#x", SecurityElement.Escape("&#x"));
        }
    }

    public static class MarblePaths
    {
        #region [ Marble Directory Paths ]

        public static string LocalAppDataDirectory = Environment.GetEnvironmentVariable("LocalAppData");

        public static string DefaultMarbleDataDirectory = Environment.GetEnvironmentVariable("LocalAppData") + "\\Nokia\\Marble";

        public static string SimDataDirectory { get; private set; }

        public static string SimOperatorDataDirectory { get; private set; }

        public static string SimCountryDataDirectory { get; private set; }

        public static string MarbleDataFilesDirectory { get; private set; }

        public static string CaptureToolTemp { get; private set; }

        public static string ReferenceImagesDirectory { get; private set; }

        public static string ReferenceFilesDirectory { get; private set; }

        public static string MarbleTestReportPackageTempDirectory { get; private set; }

        public static string MarbleTestReportScreenshotTempDirectory { get; private set; }

        public static string MarbleTestReportPackageEmailTempDirectory { get; private set; }

        public static string DefaultMarbleTestScriptsDirectory { get; private set; }

        public static string DefaultMarbleTestSetsDirectory { get; private set; }

        public static string MarbleQcTestSetImportDirectory { get; private set; }

        #endregion [ Marble Directoy Paths ]

        #region [ Marble File Paths ]

        public static string MarbleSettingsFile { get; private set; }

        public static string SimDataFile { get; private set; }

        public static string SimOperatorDataFile { get; private set; }

        public static string SimCountryDataFile { get; private set; }

        public static string PythonSyntaxHighlightingDataFile { get; private set; }

        #endregion [ Marble File Paths ]

        #region [ Marble Executables ]

        public static string MarbleFlasherDirectory { get; private set; }

        public static string MarbleFlasherFilePath { get; private set; }

        public const string MarbleFlasherFileName = "Marble_flash.exe";

        public const string MarbleFirmwareUpdaterFileName = "FirmwareUpdate.exe";

        #endregion [ Marble Executables ]

        static MarblePaths()
        {
            initializeDirectoryPaths();
            initializeFilePaths();

            CheckAllMarbleDirectories();
        }

        /// <summary>
        /// Checks all Marble directories and creates them if they do not exist.
        /// </summary>
        public static void CheckAllMarbleDirectories()
        {
            FileUtilities.CheckDirectory(MarblePaths.LocalAppDataDirectory);
            FileUtilities.CheckDirectory(MarblePaths.DefaultMarbleDataDirectory, true);
            FileUtilities.CheckDirectory(MarblePaths.SimDataDirectory, true);
            FileUtilities.CheckDirectory(MarblePaths.SimOperatorDataDirectory);
            FileUtilities.CheckDirectory(MarblePaths.SimCountryDataDirectory);
            FileUtilities.CheckDirectory(MarblePaths.MarbleFlasherDirectory);
            FileUtilities.CheckDirectory(MarblePaths.ReferenceFilesDirectory, true);
            FileUtilities.CheckDirectory(MarblePaths.ReferenceImagesDirectory, true);
            FileUtilities.CheckDirectory(MarblePaths.MarbleTestReportPackageTempDirectory, true);
            FileUtilities.CheckDirectory(MarblePaths.MarbleTestReportScreenshotTempDirectory, true);
            FileUtilities.CheckDirectory(MarblePaths.MarbleTestReportPackageEmailTempDirectory, true);
            FileUtilities.CheckDirectory(MarblePaths.DefaultMarbleTestScriptsDirectory);
            FileUtilities.CheckDirectory(MarblePaths.MarbleQcTestSetImportDirectory, true);
        }

        private static void initializeDirectoryPaths()
        {
            MarblePaths.SimDataDirectory = MarblePaths.DefaultMarbleDataDirectory;
            MarblePaths.MarbleDataFilesDirectory = AppDomain.CurrentDomain.BaseDirectory + "DataFiles";
            MarblePaths.SimOperatorDataDirectory = MarblePaths.MarbleDataFilesDirectory;
            MarblePaths.SimCountryDataDirectory = MarblePaths.MarbleDataFilesDirectory;
            MarblePaths.MarbleFlasherDirectory = Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory);
            MarblePaths.CaptureToolTemp = @"Capture tool\temp";

            // Get the directory where we are executing
            DirectoryInfo executingDirectory = Directory.GetParent(Assembly.GetExecutingAssembly().Location);

            // If we are executing in the workflow directory of the framework
            if (executingDirectory.Name == "workflow")
            {
                // Move up to the framework directory
                executingDirectory = executingDirectory.Parent.Parent;
            }

            MarblePaths.ReferenceFilesDirectory = executingDirectory.Parent.FullName + @"\reference_files";
            MarblePaths.ReferenceImagesDirectory = MarblePaths.ReferenceFilesDirectory + @"\images";
            MarblePaths.MarbleTestReportPackageTempDirectory = Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory).TrimEnd('\\') + "\\test_reports_temp";
            MarblePaths.MarbleTestReportPackageEmailTempDirectory = Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory).TrimEnd('\\') + "\\test_reports_temp\\EmailTemp";
            MarblePaths.MarbleTestReportScreenshotTempDirectory = Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory).TrimEnd('\\') + "\\test_reports_temp\\ScreenshotTemp";

            MarblePaths.DefaultMarbleTestScriptsDirectory = executingDirectory.Parent.FullName + @"\test_scripts";
            MarblePaths.DefaultMarbleTestSetsDirectory = executingDirectory.Parent.FullName + @"\test_sets";
            MarblePaths.MarbleQcTestSetImportDirectory = MarblePaths.DefaultMarbleTestSetsDirectory + @"\qc_import";
        }

        private static void initializeFilePaths()
        {
            MarblePaths.MarbleSettingsFile = MarblePaths.DefaultMarbleDataDirectory + "\\MarbleSettings.xml";
            MarblePaths.SimDataFile = MarblePaths.SimDataDirectory + "\\MarbleSimData.xml";
            MarblePaths.SimOperatorDataFile = MarblePaths.SimOperatorDataDirectory + "\\bootstrap.xml";
            MarblePaths.SimCountryDataFile = MarblePaths.SimCountryDataDirectory + "\\country_list.xml";
            MarblePaths.PythonSyntaxHighlightingDataFile = MarblePaths.MarbleDataFilesDirectory + "\\ICSharpCode.PythonBinding.Resources.Python.xshd";
            MarblePaths.MarbleFlasherFilePath = MarblePaths.MarbleFlasherDirectory + "\\" + MarblePaths.MarbleFlasherFileName;
        }
    }
}
