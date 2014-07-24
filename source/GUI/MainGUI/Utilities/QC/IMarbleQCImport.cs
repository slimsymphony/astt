namespace TestAutomation.Gui.Marble.QC
{
    using System.Xml;
    using System.Xml.Linq;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public interface IMarbleQCInterface
    {
        /// <summary>
        /// Check whether it is necessary to log in
        /// </summary>
        /// <returns>The System.Boolean.</returns>
        bool NeedCredentials();

        /// <summary>
        /// Sends authentication to server if needed
        /// </summary>
        /// <param name="username">Username.</param>
        /// <param name="password">Password.</param>
        /// <returns>The System.String.</returns>
        string Authenticate(string username, string password, string url);

        /// <summary>
        /// Downloads Domains and projects from server
        /// </summary>
        /// <returns>The System.Xml.XmlDocument.</returns>
        XElement GetDomainsAndProjects();

        /// <summary>
        /// Downloads contents of test-set-folder defined by nodeId
        /// </summary>
        /// <param name="domain">Domain of test-set-folder.</param>
        /// <param name="project">Project of test-set-folder.</param>
        /// <param name="nodeId">Id of the test-set-folder node which contents should be downloaded.</param>
        /// <returns>The System.Xml.XmlElement.</returns>
        XElement GetTestLabViewNode(string domain, string project, string nodeId);

        /// <summary>
        /// Downloads test-set which matches testSetID. Downloaded test set is converted to be compatible with Marble
        /// </summary>
        /// <param name="domain">Domain of test-set.</param>
        /// <param name="project">Project of test-set.</param>
        /// <param name="testSetID">Id of the test-set which should be downloaded.</param>
        /// <param name="marbleScriptPath">Path to scripts which should be used to construct the test set.</param>
        /// <returns>The System.Xml.XmlDocument.</returns>
        XElement GetTestSet(string domain, string project, string testSetID, string marbleScriptPath);

        /// <summary>
        /// Logs out from QC server
        /// </summary>
        void LogOut();

        /// <summary>
        /// Sends results from Marble test set to QC
        /// </summary>
        /// <param name="testSetPath">Path and filename of Marble test set with results</param>
        /// <param name="username"></param>
        /// <param name="password"></param>
        /// <returns></returns>
        bool SendResults(string testSetPath, string username, string password);

        /// <summary>
        /// This method is for testing purposes
        /// </summary>
        /// <param name="testString"></param>
        /// <returns></returns>
        string TestAPI(string testString);

    }
}
