using NationalInstruments.VisaNS;
using Nokia.Tea.Drivers.TypeInterfaces.LowLevelDrivers;

// ReSharper disable CheckNamespace
namespace Nokia.Tea.LowLevelDrivers.Implementations
// ReSharper restore CheckNamespace
{
    using System;
    using System.Reflection;
    using CoreFramework.BaseModules.LowLevelDrivers;
    using CoreFramework.ToolBox.Interfaces;

    /// <summary>
    /// This class uses NI VISA driver
    /// </summary>
    public class LowLevelDriverVisaNi : LowLevelDriverModule, ILowLevelDriverVisa
    {
        #region Private members

        /// <summary>
        /// Private variable for stroging message based session Object
        /// </summary>
        private MessageBasedSession messageBasedSession;

        private object thisLock = new object();

        

        /// <summary>
        /// Gets configuration.
        /// A private accessor to cast the base class
        /// configuration Object to configuration class specific
        /// Object instance.
        /// </summary>
        /// <value>
        /// The configuration.
        /// </value>
        private LowLevelDriverVisaNiConfiguration configuration
        {
            get { return GetConfiguration() as LowLevelDriverVisaNiConfiguration; }
        }

        #endregion

        /// <summary>
        /// Initializes a new instance of the <see cref="LowLevelDriverVisaNi"/> class.
        /// </summary>
        /// <param name="moduleId">The unique id for this module.</param>
        /// <param name="toolBox">A handle to tool box.</param>
        public LowLevelDriverVisaNi(string moduleId, IToolBox toolBox)
            : base(moduleId, toolBox)
        {
        }

        /// <summary>
        /// Opens Message based session
        /// </summary>
        /// <param name="resource">The resource to be used e.g. "GPIB0::1::INSTR"</param>
        /// <exception cref="T:System.ApplicationException">Thrown if opening session fails</exception>
        public void OpenMessageBasedSession(string resource)
        {
            lock (thisLock)
            {
                this.messageBasedSession = (MessageBasedSession)ResourceManager.GetLocalManager().Open(resource);
            }
        }

        public string[] DetectResources()
        {
            lock (thisLock)
            {
                ResourceManager manager = ResourceManager.GetLocalManager();
                return manager.FindResources("?*");
            }
        }


        /// <summary>
        /// Open message based session with parameters.
        /// </summary>
        /// <param name="resource">Resource to open session.</param>
        /// <param name="timeout">Timeout to cut connection.</param>
        public void OpenMessageBasedSession(string resource, int timeout)
        {
            lock (thisLock)
            {
                this.messageBasedSession = (MessageBasedSession)ResourceManager.GetLocalManager().Open(resource);
                this.messageBasedSession.Timeout = timeout;
            }
       }

        /// <summary>
        /// Sets a termination character. Only needed if termination character is differnet from /n
        /// </summary>
        /// <param name="character"></param>
        public void SetStringTerminationCharacter(byte character)
        {
            lock (thisLock)
            {
                if (messageBasedSession == null)
                {
                    throw new Exception("You have tried to set the String Termination Character on the GPIB session before the session itself was opened");
                }
                messageBasedSession.GetType().GetProperty("TerminationCharacterEnabled").SetValue(messageBasedSession, true, null);
                messageBasedSession.GetType().GetProperty("TerminationCharacter").SetValue(messageBasedSession, character, null);
            }
        }

        /// <summary>
        /// Queries from instrument using message based session
        /// </summary>
        /// <param name="query">The string to query</param>
        /// <returns>
        /// Answer to query
        /// </returns>
        public string QueryUsingMessageBasedSession(string query)
        {
            lock (thisLock)
            {
                try
                {
                    return (string)messageBasedSession.GetType().InvokeMember("Query", BindingFlags.InvokeMethod, null, messageBasedSession, new object[] { query }, this.ToolBox.Culture);
                }
                catch (Exception ex1)
                {

                    throw new Exception("QueryUsingMessageBasedSession() Failed to Query from instrument. It it on? Cable on? Address correct?", ex1);
                }
            }
        }

        /// <summary>
        /// Reads from instrument using message based session
        /// </summary>
        /// <returns>
        /// Answer from instrument
        /// </returns>
        public string ReadUsingMessageBasedSession()
        {
            lock (thisLock)
            {
                try
                {
                    return (string)messageBasedSession.GetType().InvokeMember("ReadString", BindingFlags.InvokeMethod, null, messageBasedSession, null, this.ToolBox.Culture);
                }
                catch (Exception ex1)
                {

                    throw new Exception("ReadUsingMessageBasedSession() Failed to Read from instrument. It it on? Cable on? Address correct?", ex1);
                }
            }
        }

        /// <summary>
        /// Writes using message based session
        /// </summary>
        /// <param name="write">string to write</param>
        public void WriteUsingMessageBasedSession(string write)
        {
            lock (thisLock)
            {

                try
                {
                    messageBasedSession.GetType().InvokeMember("Write", BindingFlags.InvokeMethod, null, messageBasedSession, new object[] { write }, this.ToolBox.Culture);
                }
                catch (Exception ex1)
                {

                    throw new Exception("WriteUsingMessageBasedSession() Failed to write to instrument. It it on? Cable on? Address correct?  String for instrument was: " + write, ex1);
                }
            }
           
        }


        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public override void Dispose()
        {
            // Check to prevent null object reference
            if (messageBasedSession != null)
            {
                this.messageBasedSession.Dispose();
            }
        }

        /// <summary>
        /// This metohde will clear the GPIB Bus
        /// </summary>
        public void ClearGpibBus()
        {
            lock (thisLock)
            {
                this.messageBasedSession.Clear();
            }
        }
    }
}
