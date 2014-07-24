namespace Nokia.Tea.Drivers.TypeInterfaces.LowLevelDrivers
{
    using System;

    /// <summary>
    /// Interface for Visa low level driver.
    /// </summary>
    public interface ILowLevelDriverVisa : IDisposable
    {
        /// <summary>
        /// Opens Message based session
        /// </summary>
        /// <param name="resource">The resource to be used e.g. "GPIB0::1::INSTR"</param>
        /// <exception cref="ApplicationException">Thrown if opening session fails</exception>
        void OpenMessageBasedSession(string resource);

        /// <summary>
        /// Open message based session with parameters.
        /// </summary>
        /// <param name="resource">Resource to open session.</param>
        /// <param name="timeout">Timeout to cut connection.</param>
        void OpenMessageBasedSession(string resource, int timeout);

        /// <summary>
        /// Queries from instrument using message based session.
        /// </summary>
        /// <param name="query">The string to query</param>
        /// <returns>Answer to query</returns>
        string QueryUsingMessageBasedSession(string query);

        /// <summary>
        /// Reads from instrument using message based session.
        /// </summary>
        /// <returns>Answer from instrument</returns>
        string ReadUsingMessageBasedSession();

        /// <summary>
        /// Writes using message based session.
        /// </summary>
        /// <param name="write">string to write</param>
        void WriteUsingMessageBasedSession(string write);

        /// <summary>
        /// Sets a termination character. Only needed if termination character is differnet from /n.
        /// </summary>
        void SetStringTerminationCharacter(byte character);

        /// <summary>
        /// This metohde will clear the GPIB Bus.
        /// </summary>
        void ClearGpibBus();
    }
}