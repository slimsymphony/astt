using Managed.Adb;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using TestAutomation.BugReporter;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Report type
    /// </summary>
    public enum OutputType
    {
        /// <summary>
        /// Plain text; just as it's received from the device
        /// </summary>
        PlainText,
        
        /// <summary>
        /// Html (ChkBugReport) format
        /// </summary>
        Html,
        
        /// <summary>
        /// Zipped plain text; just as it's received from the device
        /// </summary>
        ZippedPlainText,
        
        /// <summary>
        /// Zipped html (ChkBugReport) format
        /// </summary>
        ZippedHtml
    }

    /// <summary>
    /// Class for iterating the bugreporter output
    /// </summary>
    public sealed class BugReportIterator : MarshalByRefObject, IDisposable
    {
        /// <summary>
        /// Internal class constructor
        /// </summary>
        internal BugReportIterator()
        { }

        /// <summary>
        /// Gets or sets the report output line queue
        /// </summary>
        internal BlockingCollection<string> Lines { get; set; }

        /// <summary>
        /// Gets a value indicating whether the report reading is comleted (or cancelled)
        /// </summary>
        public bool IsCompleted { get { return Lines == null || Lines.IsCompleted; } }

        /// <summary>
        /// Gets a value indicating whether the reading is ongoing
        /// </summary>
        public bool IsReading { get { return !IsCompleted; } }

        /// <summary>
        /// Gets or sets the cancel action
        /// </summary>
        internal Action CancelAction { get; set; }

        /// <summary>
        /// Gets or sets the wait function
        /// </summary>
        internal Func<int, bool> WaitFunc { get; set; }

        /// <summary>
        /// Gets the next line in the report data. Blocks for 10 seconds if no data available
        /// </summary>
        /// <returns>Next report line; null if no data available</returns>
        public string GetNextLine()
        {
            return GetNextLine(10000);
        }

        /// <summary>
        /// Gets the next line in the report data. Blocks for given period of time if no data available
        /// </summary>
        /// <param name="timeout">Maximum time to wait for the data to arrive</param>
        /// <returns>Next report line; null if no data available</returns>
        public string GetNextLine(int timeout)
        {
            if (Lines == null) return null;

            string line;
            if (Lines.TryTake(out line, timeout))
            {
                return line;
            }

            return null;
        }

        /// <summary>
        /// Cancel the fetcing operation
        /// </summary>
        public void Cancel()
        {
            if (CancelAction != null)
            {
                try
                {
                    CancelAction.Invoke();
                }
                catch { }
            }
        }

        /// <summary>
        /// Blocks until the read operation is complete
        /// </summary>
        public void Wait()
        {
            Wait(int.MaxValue);
        }

        /// <summary>
        /// Blocks until the read operation is complete, or if the timeout expires
        /// </summary>
        /// <param name="timeout">Maximum time to wait</param>
        /// <returns>True if the operation returned before the timeout expired</returns>
        public bool Wait(int timeout)
        {
            if (WaitFunc != null)
            {
                return WaitFunc.Invoke(timeout);
            }
            return false;
        }

        /// <summary>
        /// Disposes the object and frees the resources
        /// </summary>
        public void Dispose()
        {
            if (Lines != null)
            {
                try
                {
                    Lines.Dispose();
                    Lines = null;
                }
                catch { }
            }
        }

        /// <summary>
        /// Infinite life time
        /// </summary>
        /// <returns>null</returns>
        public override object InitializeLifetimeService()
        {
            return null;
        }
    }

    /// <summary>
    /// Class for fetching a bugreport out from the device
    /// </summary>
    public sealed class BugReport : MarshalByRefObject
    {
        private const string KILL_REMOTE_REPORTER = "proc=$(ps | grep dumpstate); items=($proc); kill ${{items[1]}}";

        private static int DEFAULT_TIME_OUT = 2 * TABInterface.DEFAULT_ADB_TIMEOUT;

        private TABConnection m_tab;

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="tab">The device from which the fetch the report</param>
        public BugReport(TABConnection tab)
        {
            m_tab = tab;
        }

        /// <summary>
        /// Kill the remote dumpstate process if exists (NOTE: if there is multiple dumpstate processes, this kills just the first one)
        /// </summary>
        private void KillRemoteReporter()
        {
            if (m_tab.IsOnline)
            {
                m_tab.ExecuteShellCommand(KILL_REMOTE_REPORTER, NullOutputReceiver.Instance, TABInterface.DEFAULT_ADB_TIMEOUT);
            }
        }

        /// <summary>
        /// Save the report into a stream
        /// </summary>
        /// <param name="stream">The stream to write into</param>
        public void Save(Stream stream)
        {
            Save(stream, DEFAULT_TIME_OUT);
        }

        /// <summary>
        /// Save the report into a stream
        /// </summary>
        /// <param name="stream">The stream to write into</param>
        /// <param name="timeout">Timeout for the operation</param>
        public void Save(Stream stream, int timeout)
        {
            if (stream == null)
            {
                throw new ArgumentNullException("stream");
            }

            using (var writer = new BinaryWriter(stream))
            {
                var fetcher = new ReportWriter(writer);
                m_tab.RunBugReporterService(fetcher, timeout);
            }

            const string tracesTxtFilePath = "/data/anr/traces.txt";

            // update the size of /data/anr/traces.txt file, because BugReport will write into this file
            if (m_tab.File.FileExists(tracesTxtFilePath))
            {
                TABInterface.AnrTracesFileSize = m_tab.File.GetFileSize(tracesTxtFilePath);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="localFileName"></param>
        /// <returns></returns>
        public string SaveAs(string localFileName)
        {
            return SaveAs(localFileName, DEFAULT_TIME_OUT, OutputType.PlainText);
        }

        /// <summary>
        /// Saves the report into a local file
        /// </summary>
        /// <param name="localFileName">Local file name</param>
        public string SaveAs(string localFileName, OutputType format)
        {
            return SaveAs(localFileName, DEFAULT_TIME_OUT, format);
        }

        /// <summary>
        /// Saves the report into a local file
        /// </summary>
        /// <param name="localFileName">Local file name</param>
        /// <param name="timeout">Timeout for the operation</param>
        public string SaveAs(string localFileName, int timeout, OutputType format)
        {
            using (var stream = File.Open(localFileName, FileMode.Create, FileAccess.Write, FileShare.Read))
            {
                Save(stream, timeout);
            }
            //Reading/writing the report has failed
            if (!File.Exists(localFileName))
            {
                return null;
            }
            //It's already a plain text file
            if (format == OutputType.PlainText)
            {
                return localFileName;
            }
            //Html is requested (Java is needed)
            if (format == OutputType.ZippedHtml || format == OutputType.Html)
            {
                var result = ChkBugReport.Run(localFileName, (format == OutputType.ZippedHtml));
                //ChkBugReport failed (e.g. Java is not installed)
                if (!result.Success)
                {
                    //Log.Warning("ChkBugReport error: " + result.Cause)
                    var title = string.Format("ERROR_{0}.txt", result.Cause);
                    var data = result.Cause == ErrorCause.NoJavaFound ? string.Format("ERROR: {0}; in order to get html reports, make sure that Java is properly installed to your machine", result.Cause) :
                        string.Format("ERROR: {0}", result.Cause);
                    //Let's at least zip the original file
                    if (DoZipFile(localFileName, true, title, data))
                    {
                        return Path.ChangeExtension(localFileName, "zip");
                    }
                    //Zipping failed
                    return localFileName;
                }
                else
                {
                    try
                    {
                        File.Delete(localFileName);
                    }
                    catch { }
                    return result.OutputLocation;
                }
            }
            else if (format == OutputType.ZippedPlainText)
            {
                if (DoZipFile(localFileName, true))
                {
                    return Path.ChangeExtension(localFileName, "zip");
                }
                else
                {
                    return localFileName;
                }
            }

            return null;
        }

        /// <summary>
        /// Zips a file
        /// </summary>
        /// <param name="fileName">Name of the file to compress</param>
        /// <param name="deleteSource">Delete the source file after compressing</param>
        /// <param name="errorTitle">[Optional] Error title</param>
        /// <param name="errormessage">[Optional] Error message</param>
        /// <returns></returns>
        private bool DoZipFile(string fileName, bool deleteSource, string errorTitle = null, string errormessage = null)
        {
            var zipName = Path.ChangeExtension(fileName, "zip");

            if (File.Exists(zipName))
            {
                try
                {
                    File.Delete(zipName);
                }
                catch { }
            }

            using (ZipArchive newFile = ZipFile.Open(zipName, ZipArchiveMode.Create))
            {
                newFile.CreateEntryFromFile(fileName, Path.GetFileName(fileName), CompressionLevel.Optimal);

                if (errorTitle != null)
                {
                    var entry = newFile.CreateEntry(errorTitle, CompressionLevel.Optimal);
                    if (errormessage != null)
                    {
                        using (var stream = entry.Open())
                        {
                            var data = Encoding.Default.GetBytes(errormessage);
                            stream.Write(data, 0, data.Length);
                        }
                    }
                }
            }
            //Delete only if compression succeeds
            if (deleteSource && File.Exists(zipName))
            {
                try
                {
                    File.Delete(fileName);
                }
                catch { }
            }

            return File.Exists(zipName);
        }

        /// <summary>
        /// Begins fetching the report data asynchronously. NOTE: the caller is responsible for disposing the iterator
        /// </summary>
        /// <returns>Iterator for reading the output</returns>
        public BugReportIterator BeginFetching()
        {
            return BeginFetching(Encoding.Default);
        }

        /// <summary>
        /// Begins fetching the report data asynchronously. NOTE: the caller is responsible for disposing the iterator
        /// </summary>
        /// <param name="encoding">Encoding the be used</param>
        /// <returns>Iterator for reading the output</returns>
        public BugReportIterator BeginFetching(Encoding encoding)
        {
            var collection = new BlockingCollection<string>();
            var collector = new ReportCollector(collection, Encoding.Default);

            var iterator = new BugReportIterator()
            {
                Lines = collection,
                CancelAction = new Action(() =>
                {
                    //The cancel action
                    if (collector != null)
                    {
                        //cancel reading
                        collector.IsCancelled = true;
                        //compelete adding
                        collection.CompleteAdding();
                        //kill the remote reporter process
                        KillRemoteReporter();
                    }
                })
            };

            var task = Task.Factory.StartNew(() =>
            {
                try
                {
                    m_tab.RunBugReporterService(collector, DEFAULT_TIME_OUT);
                }
                finally
                {
                    try
                    {
                        collection.CompleteAdding();
                    }
                    catch { }
                }
            });

            iterator.WaitFunc = new Func<int, bool>((timeout) =>
            {
                if (task != null)
                {
                    try
                    {
                        return task.Wait(timeout);
                    }
                    catch { }
                }
                return false;
            });

            return iterator;
        }

        /// <summary>
        /// Infinite life time
        /// </summary>
        /// <returns>null</returns>
        public override object InitializeLifetimeService()
        {
            return null;
        }

        /// <summary>
        /// Collector which adds complete lines to a given collection
        /// </summary>
        private class ReportCollector : IShellOutputReceiver
        {
            private const string NEWLINE = "\r\n";

            private BlockingCollection<string> m_collection;
            private Encoding m_encoding;

            /// <summary>
            /// Class constructor
            /// </summary>
            /// <param name="collection">The collection in which to insert the lines</param>
            /// <param name="encoding">Encoding to be used for the raw data</param>
            public ReportCollector(BlockingCollection<string> collection, Encoding encoding)
            {
                m_collection = collection;
                m_encoding = encoding;
            }

            /// <summary>
            /// Gets or sets the unfinished line.
            /// </summary>
            /// <value>The unfinished line.</value>
            protected string UnfinishedLine { get; set; }

            /// <summary>
            /// Called when data is available
            /// </summary>
            /// <param name="data">Raw data</param>
            /// <param name="offset">Data offset</param>
            /// <param name="length">Length of the data</param>
            public void AddOutput(byte[] data, int offset, int length)
            {
                if (!IsCancelled && data != null && data.Length > 0)
                {
                    var str = m_encoding.GetString(data, offset, length);

                    // ok we've got a string
                    if (!string.IsNullOrEmpty(str))
                    {
                        // if we had an unfinished line we add it.
                        if (!string.IsNullOrEmpty(UnfinishedLine))
                        {
                            str = UnfinishedLine + str;
                            UnfinishedLine = null;
                        }

                        // now we split the lines
                        var start = 0;
                        do
                        {
                            int index = str.IndexOf(NEWLINE, start);

                            // if \r\n was not found, this is an unfinished line
                            // and we store it to be processed for the next packet
                            if (index == -1)
                            {
                                UnfinishedLine = str.Substring(start);
                                break;
                            }

                            // so we found a \r\n;
                            // extract the line
                            var line = str.Substring(start, index - start);

                            try
                            {
                                m_collection.Add(line);
                            }
                            catch
                            {
                                IsCancelled = true;
                                break;
                            }

                            // move start to after the \r\n we found
                            start = index + 2;

                        } while (true);
                    }
                }
            }

            /// <summary>
            /// Finalize the operation
            /// </summary>
            public void Flush()
            {
                try
                {
                    m_collection.CompleteAdding();
                }
                catch { }
            }

            /// <summary>
            /// Gets or sets a value to indicate if the operation is cancelled
            /// </summary>
            public bool IsCancelled { get; set; }
        }

        /// <summary>
        /// Class for writing the data to a binaryWriter
        /// </summary>
        private class ReportWriter : IShellOutputReceiver
        {
            private BinaryWriter m_writer;

            /// <summary>
            /// Class constructor
            /// </summary>
            /// <param name="writer">The writer to be used</param>
            public ReportWriter(BinaryWriter writer)
            {
                m_writer = writer;
            }

            /// <summary>
            /// Called when data is available
            /// </summary>
            /// <param name="data">Raw data</param>
            /// <param name="offset">Data offset</param>
            /// <param name="length">Length of the data</param>
            public void AddOutput(byte[] data, int offset, int length)
            {
                m_writer.Write(data, offset, length);
            }

            /// <summary>
            /// Flushes the writer
            /// </summary>
            public void Flush()
            {
                m_writer.Flush();
            }

            /// <summary>
            /// Gets or sets a value to indicate if the operation is cancelled
            /// </summary>
            public bool IsCancelled { get; set; }
        }
    }
}
