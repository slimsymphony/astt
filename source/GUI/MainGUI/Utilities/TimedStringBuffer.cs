using System;
using System.Text;
using System.Timers;

namespace Marble.Utilities
{
    /// <summary>
    /// Buffer that flushes its content on regular intervals.
    /// Content is written to outputMethod in any of the following conditions:
    /// - Appending new content would exceed the buffer capacity (BufferSize).
    /// - New content haven't been appended for a while (MinWait). Timer reset on append and on flush.
    /// - Existing content haven't been flushed for some time (MaxWait). Timer reset on flush.
    /// </summary>
    public class TimedStringBuffer
    {
        /// <summary>
        /// Maximum capacity of the buffer (65536 chars).
        /// </summary>
        const int BufferSize = 65536;
        /// <summary>
        /// Minimum time to wait before flushing (100 ms).
        /// </summary>
        const double MinWait = 100;
        /// <summary>
        /// Maximum time to wait before flushing (500 ms).
        /// </summary>
        const double MaxWait = 500;

        /// <summary>
        /// Text content of the buffer.
        /// </summary>
        private readonly StringBuilder content;

        /// <summary>
        /// Controls minimum wait time.
        /// </summary>
        private readonly Timer lastAppend;

        /// <summary>
        /// Controls maximum wait time.
        /// </summary>
        private readonly Timer lastFlush;

        /// <summary>
        /// Method that is called on flush.
        /// </summary>
        private readonly Communication.AppendLog outputMethod;

        /// <summary>
        /// Parameter for the output method.
        /// 1 = status updates and framework output, 2 = trace output
        /// </summary>
        private readonly int logIndex;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="output">Method that is called on flush.</param>
        /// <param name="logIndex">Parameter for the ouput method. 1 = status updates and framework output, 2 = trace output</param>
        public TimedStringBuffer(Communication.AppendLog output, int logIndex=1)
        {
            this.outputMethod = output;
            this.logIndex = logIndex;
            this.content = new StringBuilder(BufferSize);

            // Min wait timer
            this.lastAppend = new Timer(MinWait);
            this.lastAppend.Elapsed += this.LastAppendElapsed;
            this.lastAppend.Start();

            // Max wait timer
            this.lastFlush = new Timer(MaxWait);
            this.lastFlush.Elapsed += this.LastFlushElapsed;
            this.lastFlush.AutoReset = true;
            this.lastFlush.Start();
        }

        /// <summary>
        /// Adds text content after existing text content.
        /// </summary>
        /// <param name="text">Text to append.</param>
        public void Append(string text)
        {
            // reset minimum wait timer
            this.lastAppend.Stop();
            this.lastAppend.Start();

            // ensure proper syncronization
            lock (this.content)
            {
                // check if there is enough capacity for the new content
                if (this.content.Length + text.Length > this.content.Capacity)
                    this.Flush();

                this.content.Append(text);
            }

            // Timer gets occasionally disposed when stopped
            GC.KeepAlive(this.lastAppend);
        }

        /// <summary>
        /// Writes content to output method and clears the buffer.
        /// </summary>
        private void Flush()
        {
            // reset both min and max timers
            this.lastAppend.Stop();
            this.lastAppend.Start();
            this.lastFlush.Stop();
            this.lastFlush.Start();

            // syncronize
            lock (this.content)
            {
                // output only if buffer is non empty
                if (this.content.Length > 0)
                {
                    outputMethod(this.content.ToString(), this.logIndex);
                    this.content.Clear();
                }
            }

            // Timers gets occasionally disposed when stopped
            GC.KeepAlive(this.lastAppend);
            GC.KeepAlive(this.lastFlush);
        }

        /// <summary>
        /// Event handler for minimum time has been passed.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LastAppendElapsed(Object sender, ElapsedEventArgs e)
        {
            this.Flush();
        }

        /// <summary>
        /// Event handler for maximum time has been passed.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LastFlushElapsed(Object sender, ElapsedEventArgs e)
        {
            this.Flush();
        }

    }
}
