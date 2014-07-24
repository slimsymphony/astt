namespace TestAutomation.Gui.Marble.IPC.Interfaces
{
    public class ServiceDefinitions
    {
        /// <summary>
        /// Service EndPoint name for BlackBoxRemoteGuiService.
        /// </summary>
        public const string BlackBoxRemoteGuiServiceEndpoint = "BlackBoxRemoteGuiService";

        /// <summary>
        /// Service EndPoint name for BlackBoxService.
        /// </summary>
        public const string BlackBoxServiceEndpoint = "BlackBoxService";

        /// <summary>
        /// Service EndPoint name for VideoRecorderService.
        /// </summary>
        public const string VideoRecorderServiceEndpoint = "VideoRecorderService";

        /// <summary>
        /// Service EndPoint name for VideoRecorderService.
        /// </summary>
        public const string VideoRecorderRemoteServiceEndpoint = "VideoRecorderRemoteService";

        /// <summary>
        /// Service EndPoint name for local IoWarriorService.
        /// </summary>
        public const string IoWarriorServiceEndpoint = "IoWarriorService";

        /// <summary>
        /// Service EndPoint name for BltUeService.
        /// </summary>
        public const string BltUeServiceEndpoint = "BltUeService";

        # region Fault codes

        /// <summary>
        /// Fault code for internal IoWarrior fault that cannot be handled on the service side.
        /// </summary>
        public const string IoWarriorFault = "IoWarriorFault";

        /// <summary>
        /// Fault code for illegal configuration E.g. client calls a method that tries to access a card
        /// that is not connected to the IoWarrior HW.
        /// </summary>
        public const string IoWarriorConfigurationFault = "IoWarriorConfigurationFault";
        
        #endregion
    }
}
