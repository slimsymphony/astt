using System;
using System.IO;
using System.Runtime.Serialization;
using System.Threading;
using Nokia.Tea.CoreFramework.BaseModules.TeaCoreModule;
using Nokia.Tea.CoreFramework.Diagnostics.Interfaces;

namespace Nokia.Tea.CoreFramework.Diagnostics.Implementations
{
    public class StreamWriterLogger : ITraceLogger, IDisposable
    {
        private bool disposed;
        private StreamWriter streamWriter;
        protected SerializationInfo StreamWriterLoggerSerializationInfo;

        public StreamWriterLogger()
        {
            TeaGlobalization globalization = new TeaGlobalization();
            Thread.CurrentThread.CurrentCulture = globalization.TeaCultureInfo;
        }

        protected StreamWriterLogger(SerializationInfo info, StreamingContext context)
        {
            this.StreamWriterLoggerSerializationInfo = info;
        }

        private void dispose(bool disposing)
        {
            if (!this.disposed)
            {
                if (disposing && (this.streamWriter != null))
                {
                    this.streamWriter.Dispose();
                    this.streamWriter = null;
                }
                this.disposed = true;
            }
        }

        public void Dispose()
        {
            this.dispose(true);
            GC.SuppressFinalize(this);
        }

        public void GetObjectData(SerializationInfo info, StreamingContext context)
        {
        }

        public void Initialize(object streamOutput)
        {
            if (streamOutput is string)
            {
                this.streamWriter = new StreamWriter(streamOutput.ToString());
            }
            else if (streamOutput is Stream)
            {
                this.streamWriter = new StreamWriter((Stream) streamOutput);
            }
            this.streamWriter.AutoFlush = true;
        }

        public void Log(string traceMessage)
        {
            if (this.streamWriter != null)
            {
                this.streamWriter.WriteLine(traceMessage);
            }
            else if (!this.disposed)
            {
                throw new NullReferenceException("StreamWriterLogger.Log(): Stream writer is null.");
            }
        }
    }
}

