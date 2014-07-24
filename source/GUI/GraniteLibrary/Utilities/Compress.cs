namespace MarbleLibrary.Utilities
{
    using System;
    using System.Collections.Generic;
    using System.Collections.ObjectModel;
    using System.IO;
    using System.Linq;

    using SevenZip;

    /// <summary>
    /// Provides 7zip compress function.
    /// </summary>
    public static class Compress
    {
        /// <summary>
        /// Compresses the files in the nominated folder and subfolders, and creates a 7zip (.7z) file on disk named as outputFilePath.
        /// </summary>
        /// <param name="outputFilePath">Name of the 7zip file to be created.</param>
        /// <param name="folderName">Folder name to be compressed.</param>
        /// <param name="testsetFileName">Name of the current testset.</param>
        public static void Create7ZipPackage(string outputFilePath, string folderName, string testsetFileName)
        {
            // Change the paths to absolute paths. Otherwise the directory structure inside archive is not right.
            outputFilePath = Path.GetFullPath(outputFilePath);
            folderName = Path.GetFullPath(folderName);
            testsetFileName = Path.GetFullPath(testsetFileName);

            FileInfo fi = new FileInfo(testsetFileName);
            SevenZipCompressor.SetLibraryPath("7za.dll");
            SevenZipCompressor sevenZipCompressor = new SevenZipCompressor();
            sevenZipCompressor.CompressionMode = CompressionMode.Create;
            sevenZipCompressor.CompressionMethod = SevenZip.CompressionMethod.Lzma2;
            sevenZipCompressor.CompressionLevel = CompressionLevel.Normal;

            try
            {
                sevenZipCompressor.CompressDirectory(folderName, outputFilePath, fi.Name, false);

                string testsetResultFolderName = Path.GetDirectoryName(testsetFileName);
                string testsetResultFolder = Path.GetFileNameWithoutExtension(testsetFileName) + "_results";
                string testsetResultFolderPath = Path.Combine(testsetResultFolderName, testsetResultFolder);
                string[] folders = Directory.GetDirectories(folderName);

                foreach (string folder in folders)
                {
                    // Compress only the current testset_result folder.
                    if (folder == testsetResultFolderPath)
                    {
                        // Change the CompressionMode to append so we won't overwrite the archive, but append to it.
                        sevenZipCompressor.CompressionMode = CompressionMode.Append;
                        sevenZipCompressor.PreserveDirectoryRoot = true;
                        sevenZipCompressor.CompressDirectory(folder, outputFilePath, true);
                        break;
                    }
                }
            }
            catch (Exception)
            {
                Console.WriteLine("Compressing results failed!");
            }
        }

        public static void Create7ZipPackage(string outputFilePath, List<string> filePathList)
        {
            if (string.IsNullOrEmpty(outputFilePath)) return;

            // Change the paths to absolute paths. Otherwise the directory structure inside archive is not right.
            outputFilePath = Path.GetFullPath(outputFilePath);
            FileUtilities.CheckFilePathListForAbsolutePaths(filePathList);

            SevenZipCompressor.SetLibraryPath("7za.dll");
            SevenZipCompressor sevenZipCompressor = new SevenZipCompressor();
            sevenZipCompressor.CompressionMode = CompressionMode.Create;
            sevenZipCompressor.CompressionMethod = SevenZip.CompressionMethod.Lzma2;
            sevenZipCompressor.CompressionLevel = CompressionLevel.Normal;

            try
            {
                sevenZipCompressor.CompressFiles(outputFilePath, filePathList.ToArray());
            }
            catch (Exception)
            {
                Console.WriteLine("Compression failed!");
            }
        }

        public static void Extract7ZipPackage(string archiveFilePath, string outputDirectoryPath)
        {
            if (string.IsNullOrEmpty(archiveFilePath)) return;

            archiveFilePath = Path.GetFullPath(archiveFilePath);
            outputDirectoryPath = Path.GetFullPath(outputDirectoryPath);
            
            SevenZipExtractor.SetLibraryPath("7za.dll");
            SevenZipExtractor sevenZipExtractor = new SevenZipExtractor(archiveFilePath);

            try
            {
                sevenZipExtractor.ExtractArchive(outputDirectoryPath);
            }
            catch(IOException ioException)
            {
                
            }
            catch (Exception)
            {
                Console.WriteLine("Extraction failed!");
                throw;
            }
        }

        public static List<string> GetFileNamesFrom7ZipPackage(string archiveFilePath)
        {
            archiveFilePath = Path.GetFullPath(archiveFilePath);

            SevenZipExtractor.SetLibraryPath("7za.dll");
            SevenZipExtractor sevenZipExtractor = new SevenZipExtractor(archiveFilePath);

            try
            {
                return sevenZipExtractor.ArchiveFileNames.ToList();
            }
            catch (Exception)
            {
                Console.WriteLine("Extraction failed!");
                throw;
            }
        }
    }
}
