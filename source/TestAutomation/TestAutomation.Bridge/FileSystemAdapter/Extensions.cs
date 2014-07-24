using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// 
    /// </summary>
    internal static class FileExtensions
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="fi"></param>
        /// <returns></returns>
        internal static bool DirectoryExists(this FileInfo fi)
        {
            return (int)fi.Attributes != -1 && fi.Attributes.HasFlag(FileAttributes.Directory);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="fi"></param>
        /// <returns></returns>
        internal static string GetExtension(this FileInfo fi)
        {
            var dotIndex = fi.Name.LastIndexOf(".");
            if (dotIndex <= 0) return string.Empty;
            return fi.Name.Substring(dotIndex).TrimStart('.');
        }
    }
}
