using System;
using System.Text;
using Managed.Adb.Logs;

namespace Managed.Adb.Receivers
{
    /// <summary>
    /// Receiver for receiving comple text lines via socket
    /// </summary>
    public abstract class SingleLineReceiver : ITailReceiver, IShellOutputReceiver
    {
        /// <summary>
        /// If used to read shell output; adb adds the line change as \r\n in windows environment. If used 
        /// to tail a file, the line changes are in most of the cases as \n. To keep this generic, we use \n 
        /// as delim, and trim the possible, remaining \r at the end of the message
        /// </summary>
        private const string Newline = "\n";

        private readonly Encoding _encoding;

        /// <summary>
        /// Class constructor
        /// </summary>
        protected SingleLineReceiver()
            : this(Encoding.UTF8)
        {}

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="encoding">Encoding to be used for the raw data</param>
        protected SingleLineReceiver(Encoding encoding)
        {
            if (encoding == null) throw new ArgumentNullException("encoding");
            _encoding = encoding;
        }

        /// <summary>
        /// Called everytime there is a complete line
        /// </summary>
        /// <param name="timeStamp">The time stamp when the firts chunk of the line was received</param>
        /// <param name="line">The complete line</param>
        protected abstract void OnNewLine(DateTime timeStamp, string line);

        /// <summary>
        /// Gets or sets the unfinished line.
        /// </summary>
        /// <value>The unfinished line.</value>
        private string UnfinishedLine { get; set; }

        /// <summary>
        /// The time stamp of the unfinished line
        /// </summary>
        private DateTime UnfinishedTimeStamp { get; set; }

        /// <summary>
        /// Called when data is available
        /// </summary>
        /// <param name="data">Raw data</param>
        /// <param name="offset">Data offset</param>
        /// <param name="length">Length of the data</param>
        public void AddOutput(byte[] data, int offset, int length)
        {
            var timestamp = DateTime.Now;

            if (IsCancelled || data == null || data.Length <= 0) return;
            
            var str = _encoding.GetString(data, offset, length);

            // ok we've got a string
            if (string.IsNullOrEmpty(str)) return;
            
            // if we had an unfinished line we add it.
            if (!string.IsNullOrEmpty(UnfinishedLine))
            {
                str = UnfinishedLine + str;
                UnfinishedLine = null;
                timestamp = UnfinishedTimeStamp;
            }

            // now we split the lines
            var start = 0;
            do
            {
                var index = str.IndexOf(Newline, start, StringComparison.Ordinal);

                // if \n was not found, this is an unfinished line
                // and we store it to be processed for the next packet
                if (index == -1)
                {
                    UnfinishedLine = str.Substring(start);
                    UnfinishedTimeStamp = timestamp;
                    break;
                }

                // so we found a \n;
                // extract the line
                var line = str.Substring(start, index - start).Trim('\r');

                try
                {
                    OnNewLine(timestamp, line);
                }
                catch
                {
                    IsCancelled = true;
                    break;
                }

                // move start to after the \n we found
                start = index + Newline.Length;

            } while (true);
        }

        /// <summary>
        /// Finalize the operation
        /// </summary>
        public void Flush()
        {}

        /// <summary>
        /// Gets or sets a value to indicate if the operation is cancelled
        /// </summary>
        public bool IsCancelled { get; set; }

        /// <summary>
        /// Called when file data is available
        /// </summary>
        /// <param name="data">Raw data</param>
        /// <param name="offset">Data offset</param>
        /// <param name="len">Length of the data</param>
        public void Tail(byte[] data, int offset, int len)
        {
            AddOutput(data, offset, len);
        }
    }
}
