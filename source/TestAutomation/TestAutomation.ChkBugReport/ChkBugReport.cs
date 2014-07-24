using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestAutomation.BugReporter
{
    /// <summary>
    /// Error types
    /// </summary>
    public enum ErrorCause
    {
        /// <summary>
        /// No Java was found
        /// </summary>
        NoJavaFound,
        
        /// <summary>
        /// No parser was found
        /// </summary>
        NoParserFound,
        
        /// <summary>
        /// Failed during parsing
        /// </summary>
        FailedParsing,
        
        /// <summary>
        /// invalid input
        /// </summary>
        InvalidInput,
        
        /// <summary>
        /// Parser timed out
        /// </summary>
        Timeout,
        
        /// <summary>
        /// No error
        /// </summary>
        None
    }

    /// <summary>
    /// Class for parser results
    /// </summary>
    public sealed class ParserOutput
    {
        /// <summary>
        /// Class constructor
        /// </summary>
        internal ParserOutput()
        { }

        /// <summary>
        /// Reporter output file location
        /// </summary>
        public string OutputLocation { get; internal set; }
        
        /// <summary>
        /// Value indicating whether the output file is a zip
        /// </summary>
        public bool IsZip { get; internal set; }
        
        /// <summary>
        /// Value indicating whether the output file is a html file
        /// </summary>
        public bool IsHtml { get { return !IsZip; } }
        
        /// <summary>
        /// Value indicating whether the parser completed successfully
        /// </summary>
        public bool Success { get { return Cause == ErrorCause.None; } }
        
        /// <summary>
        /// Parser error cause
        /// </summary>
        public ErrorCause Cause { get; internal set; }
    }

    /// <summary>
    /// Wrapper class for ChkBugReport java lib file
    /// </summary>
    /// <see cref="https://github.com/sonyxperiadev/ChkBugReport"/>
    [ArchiveInfo("chkbugreport-0.5-211.jar", "7215fe551b48fc26949264b9cacfdff5")]
    public static class ChkBugReport
    {
        private const int DEFAULT_PARSER_TIMEOUT = 10 * 60 * 1000;
        
        /// <summary>
        /// Static constructor for extracting the reporter archive
        /// </summary>
        static ChkBugReport()
        {
            ExtractReporterBinary();
        }

        /// <summary>
        /// Gets a value indicating whether we can run the reporter
        /// </summary>
        public static bool CanRun
        {
            get
            {
                return Java.IsInstalled;
            }
        }

        /// <summary>
        /// Runs the reporter
        /// </summary>
        /// <param name="rawReportLocation">Location of the data to be parsed</param>
        /// <returns>ParserOutput object</returns>
        public static ParserOutput Run(string rawReportLocation)
        {
            return Run(rawReportLocation, true, TimeSpan.FromMilliseconds(DEFAULT_PARSER_TIMEOUT));
        }

        /// <summary>
        /// Runs the reporter
        /// </summary>
        /// <param name="rawReportLocation">Location of the data to be parsed</param>
        /// <param name="zip">Zip the generated folder</param>
        /// <returns>ParserOutput object</returns>
        public static ParserOutput Run(string rawReportLocation, bool zip)
        {
            return Run(rawReportLocation, zip, TimeSpan.FromMilliseconds(DEFAULT_PARSER_TIMEOUT));
        }

        /// <summary>
        /// Runs the reporter
        /// </summary>
        /// <param name="rawReportLocation">Location of the data to be parsed</param>
        /// <param name="timeout">Parser timeout</param>
        /// <returns>ParserOutput object</returns>
        public static ParserOutput Run(string rawReportLocation, TimeSpan timeout)
        {
            return Run(rawReportLocation, true, timeout);
        }

        /// <summary>
        /// Runs the reporter
        /// </summary>
        /// <param name="rawReportLocation">Location of the data to be parsed</param>
        /// <param name="zip">Zip the generated folder</param>
        /// <param name="timeout">Parser timeout</param>
        /// <returns>ParserOutput object</returns>
        public static ParserOutput Run(string rawReportLocation, bool zip, TimeSpan timeout)
        {
            var output = new ParserOutput() { IsZip = zip };

            if (!CanRun)
            {
                output.Cause = ErrorCause.NoJavaFound;
                return output;
            }
            
            if (!ReporterArchiveExists)
            {
                output.Cause = ErrorCause.NoParserFound;
                return output;
            }

            if (string.IsNullOrEmpty(rawReportLocation))
            {
                output.Cause = ErrorCause.InvalidInput;
                return output;
            }

            var fi = new FileInfo(rawReportLocation);

            if (!fi.Exists || fi.Length == 0)
            {
                output.Cause = ErrorCause.InvalidInput;
                return output;
            }

            var proc = new Process();
            proc.StartInfo.FileName = ReporterArchiveLocation;
            proc.StartInfo.Arguments = string.Format("\"{0}\" --silent", rawReportLocation);
            proc.StartInfo.UseShellExecute = true;
            proc.StartInfo.CreateNoWindow = true;
            proc.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;

            var outputFolder = Path.Combine(Path.GetDirectoryName(rawReportLocation), Path.GetFileNameWithoutExtension(rawReportLocation) + "_out");
            var outPutZip = Path.ChangeExtension(outputFolder.Replace("_out", "_html"), "zip");

            if (Directory.Exists(outputFolder))
            {
                try
                {
                    Directory.Delete(outputFolder, true);
                }
                catch { }
            }

            if (File.Exists(outPutZip))
            {
                try
                {
                    File.Delete(outPutZip);
                }
                catch { }
            }

            if (proc.StartJar())
            {
                proc.WaitForExit((int)timeout.TotalMilliseconds);

                if (proc.HasExited && proc.ExitCode == 0 && Directory.Exists(outputFolder))
                {
                    if (zip) 
                    {
                        try
                        {
                            ZipFile.CreateFromDirectory(outputFolder, outPutZip, CompressionLevel.Optimal, true);
                            Directory.Delete(outputFolder, true);
                        }
                        catch { }
                    }
                    output.OutputLocation = zip ? outPutZip : Path.Combine(outputFolder, "index.html");
                    output.Cause = ErrorCause.None;
                    return output;
                }
            }
            
            output.Cause = ErrorCause.FailedParsing;
            return output;
        }

        /// <summary>
        /// Extracts the correct reporter archive file into the disk
        /// </summary>
        private static void ExtractReporterBinary()
        {
            if (ReporterArchiveExists && !HasCorrectArchiveVersion)
            {
                    try
                    {
                        File.Delete(ReporterArchiveLocation);
                    }
                    catch { }
            }
            
            if (!ReporterArchiveExists)
            {
                var root = Path.GetDirectoryName(typeof(ChkBugReport).Assembly.Location);
                typeof(ChkBugReport).Assembly.CopyManifestResourceToFolder(GetArchiveName(), root);
            }
        }

        /// <summary>
        /// Checks if the reporter jar in disk is the version we reuire
        /// </summary>
        private static bool HasCorrectArchiveVersion
        {
            get
            {
                return ReporterArchiveExists && string.Compare(GetReporterBinaryHash(), GetRequiredHash(), false) == 0;
            }
        }

        /// <summary>
        /// Gets a value indicating whether the reporter arcvive exists in its default location
        /// </summary>
        private static bool ReporterArchiveExists
        {
            get
            {
                return File.Exists(ReporterArchiveLocation);
            }
        }

        /// <summary>
        /// Gets the default location for the reporter archive file
        /// </summary>
        private static string ReporterArchiveLocation
        {
            get
            {
                var root = Path.GetDirectoryName(typeof(ChkBugReport).Assembly.Location);
                return Path.Combine(root, GetArchiveName());
            }
        }

        /// <summary>
        /// Calculates MD5 hash for the reporter binary
        /// </summary>
        /// <returns>MD5 hash for the reporter binary</returns>
        private static string GetReporterBinaryHash()
        {
            using (var md5 = System.Security.Cryptography.MD5.Create())
            {
                using (var inStream = File.OpenRead(ReporterArchiveLocation))
                {
                    var hash = md5.ComputeHash(inStream);
                    var builder = new StringBuilder();
                    for (int i = 0; i < hash.Length; i++)
                    {
                        builder.Append(hash[i].ToString("X2"));
                    }
                    var hashStr = builder.ToString().ToLower();
                    return hashStr;
                }
            }
        }

        /// <summary>
        /// Gets the required reporter archive hash
        /// </summary>
        /// <returns>The required reporter archive hash</returns>
        private static string GetRequiredHash()
        {
            var attr = typeof(ChkBugReport).GetCustomAttributes(typeof(ArchiveInfo), false).FirstOrDefault() as ArchiveInfo;
            if (attr != null) return attr.Hash;
            return null;
        }

        /// <summary>
        /// Gets the reporter archive file name
        /// </summary>
        /// <returns>The reporter archive file name</returns>
        private static string GetArchiveName()
        {
            var attr = typeof(ChkBugReport).GetCustomAttributes(typeof(ArchiveInfo), false).FirstOrDefault() as ArchiveInfo;
            if (attr != null) return attr.Name;
            return null;
        }
    }

    /// <summary>
    /// Class for searching the Java installation from the machine
    /// </summary>
    public static class Java
    {
        /// <summary>
        /// Gets a value indicating if the Java is installed in this machine
        /// </summary>
        public static bool IsInstalled
        {
            get
            {
                var location = Location;
                return location != null && File.Exists(location);
            }
        }

        /// <summary>
        /// Gets the Java.exe location; returns null if not found
        /// </summary>
        public static string Location
        {
            get
            {
                try
                {
                    string javahome = "";

                    string environmentPath = Environment.GetEnvironmentVariable("JAVA_HOME");
                    if (!string.IsNullOrEmpty(environmentPath))
                    {
                        javahome = environmentPath;
                    }

                    if (string.IsNullOrEmpty(javahome))
                    {
                        string javaKey = "SOFTWARE\\JavaSoft\\Java Runtime Environment\\";
                        using (Microsoft.Win32.RegistryKey rk = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(javaKey))
                        {
                            string currentVersion = rk.GetValue("CurrentVersion").ToString();
                            using (Microsoft.Win32.RegistryKey key = rk.OpenSubKey(currentVersion))
                            {
                                javahome = key.GetValue("JavaHome").ToString();
                            }
                        }
                    }

                    if (!string.IsNullOrEmpty(javahome))
                    {
                        return Directory.GetFiles(javahome, "*.exe", SearchOption.AllDirectories).ToList().Find(f => Path.GetFileName(f).ToLower() == "java.exe");
                    }
                }
                catch { }
                return null;
            }
        }
    }

    /// <summary>
    /// Archive info attribute
    /// </summary>
    public class ArchiveInfo : Attribute
    {
        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="name">Name of the archive</param>
        /// <param name="hash">MD5 of the archive</param>
        public ArchiveInfo(string name, string hash)
        {
            Name = name;
            Hash = hash;
        }

        /// <summary>
        /// Gets the name of the archive
        /// </summary>
        public string Name { get; private set; }

        /// <summary>
        /// Gets the md5 hash of the archive
        /// </summary>
        public string Hash { get; private set; }
    }

    /// <summary>
    /// Extensions for the Process class
    /// </summary>
    public static class ProcessExtensions
    {
        /// <summary>
        /// Starts executing a jar file with Java
        /// </summary>
        /// <param name="process">The process</param>
        /// <returns>True is the process was successfully started; otherwise, false</returns>
        public static bool StartJar(this Process process)
        {
            if (!Java.IsInstalled)
            {
                return false;
            }

            var jar = process.StartInfo.FileName;

            if (string.IsNullOrEmpty(jar))
            {
                return false;
            }

            var fi = new FileInfo(jar);

            if (!fi.Exists || fi.Length == 0)
            {
                return false;
            }

            process.StartInfo.FileName = Java.Location;
            process.StartInfo.Arguments = string.Format(" -jar \"{0}\" {1}", jar.Trim('\"'), process.StartInfo.Arguments);

            return process.Start();
        }
    }
}
