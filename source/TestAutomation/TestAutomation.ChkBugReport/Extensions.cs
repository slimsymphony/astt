using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace TestAutomation.BugReporter
{
    public static class Extensions
    {
        /// <summary>
        /// Extracts a zip file from assembly's manifest stream to a target folder
        /// </summary>
        /// <param name="ass">Assembly whose manifest stream to search</param>
        /// <param name="zipName">Name of the zip file</param>
        /// <param name="targetFolder">Folder into which to extract</param>
        public static void ExtractManifestResourceZip(this Assembly ass, string zipName, string targetFolder)
        {
            using (var zipToOpen = ass.GetManifestResourceStream(ass.
                GetManifestResourceNames().ToList().Find(n => n.EndsWith(zipName))))
            {
                using (var archive = new ZipArchive(zipToOpen, ZipArchiveMode.Read))
                {
                    archive.ExtractToDirectory(targetFolder);
                }
            }
        }

        /// <summary>
        /// Copies a manifest resource to a folder
        /// </summary>
        /// <param name="ass">Assembly from which to look for the resource</param>
        /// <param name="name">Name of the resource</param>
        /// <param name="targetFolder">Folder into which to copy</param>
        public static void CopyManifestResourceToFolder(this Assembly ass, string name, string targetFolder)
        {
            using (var resource = ass.GetManifestResourceStream(ass.
                GetManifestResourceNames().ToList().Find(n => n.EndsWith(name))))
            {
                using (var file =  File.OpenWrite(Path.Combine(targetFolder, name)))
                {
                    resource.CopyTo(file);
                }
            }
        }
    }
}
