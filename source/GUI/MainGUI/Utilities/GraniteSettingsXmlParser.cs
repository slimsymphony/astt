// -----------------------------------------------------------------------
// <copyright file="MarbleSettingsXmlParser.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Utilities
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Text;
    using System.Xml;
    using System.Xml.Linq;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// Static class used for parsing XML of the Marble settings file.
    /// </summary>
    public static class MarbleSettingsXmlParser
    {
        /// <summary>
        /// Initializes static members of the <see cref="MarbleSettingsXmlParser"/> class.
        /// </summary>
        static MarbleSettingsXmlParser()
        {
            if (MarbleSettingsXml == null)
                LoadMarbleSettingsFile();
        }

        /// <summary>
        /// Gets XDocument containing Marble settings.
        /// </summary>
        public static XDocument MarbleSettingsXml { get; private set; }

        /// <summary>
        /// Previously used connections.
        /// key: Connection usage, value: ConnectionIdentifier
        /// e.g. (Main, Reference, Trace, Remote, Remote2, etc.), GConnId_e4ed89e1b44f4b19
        /// </summary>
        public static Dictionary<string, string> RecentConnections
        {
            get
            {
                if (!MarbleSettingsXml.Element("MarbleSettings")
                                      .Element("ConnectionSettings")
                                      .Element("RecentConnections")
                                      .Elements("RecentConnection").Any())
                    return new Dictionary<string, string>();

                return
                    MarbleSettingsXml.Element("MarbleSettings")
                                      .Element("ConnectionSettings")
                                      .Element("RecentConnections")
                                      .Elements("RecentConnection")
                                      .ToDictionary(elem => elem.Attribute("Usage").Value,
                                                    elem => elem.Attribute("Identifier").Value);
            }
        }

        /// <summary>
        /// Saves connection usages to the Marble settings xml file.
        /// </summary>
        /// <param name="connections">Used connections - key: Usage (Main, Reference, Trace, Remote, Remote2 etc.), value: Connection identifier</param>
        public static void UpdateRecentConnections(Dictionary<string, string> connections )
        {
            XElement recentConnectionsElement = MarbleSettingsXml.Element("MarbleSettings").Element("ConnectionSettings").Element("RecentConnections");

            if (recentConnectionsElement == null) return;

            recentConnectionsElement.Elements().Remove();

            foreach (var item in connections)
            {
                var recentConnection = new XElement("RecentConnection");
                recentConnection.Add(new XAttribute("Usage", item.Key));
                recentConnection.Add(new XAttribute("Identifier", item.Value));
                recentConnectionsElement.Add(recentConnection);
            }

            MarbleSettingsXml.Save(MarblePaths.MarbleSettingsFile);
        }

        /// <summary>
        /// Gets list of file paths of most recently loaded test set files.
        /// </summary>
        public static List<string> RecentTestSetFiles
        {
            get
            {
                return (from xElement in MarbleSettingsXml.Element("MarbleSettings").Element("FileSettings").Element("RecentTestSets").Elements("RecentTestSet") 
                        where File.Exists(xElement.Attribute("filepath").Value)
                        select xElement.Attribute("filepath").Value).ToList();
            }
        }

        /// <summary>
        /// Updates most recently loaded test set files to the Marble settings file.
        /// </summary>
        /// <param name="recentTestSetFilePaths">List of recent test set file paths.</param>
        public static void UpdateRecentTestSetFiles(List<string> recentTestSetFilePaths)
        {
            XElement recentTestSetsElement = MarbleSettingsXml.Element("MarbleSettings").Element("FileSettings").Element("RecentTestSets");

            if (recentTestSetsElement == null) return;

            recentTestSetsElement.Elements().Remove();

            foreach (string recentTestSetFilePath in recentTestSetFilePaths)
            {
                XElement recentTestSetElement = new XElement("RecentTestSet");
                recentTestSetElement.Add(new XAttribute("filepath", recentTestSetFilePath));
                recentTestSetsElement.Add(recentTestSetElement);
            }

            MarbleSettingsXml.Save(MarblePaths.MarbleSettingsFile);
        }

        /// <summary>
        /// Gets a list of file paths of most recently trace xml files.
        /// </summary>
        public static List<string> RecentTraceXmlFiles
        {
            get
            {
                return (from xElement in MarbleSettingsXml.Element("MarbleSettings").Element("FileSettings").Element("RecentTraceXmls").Elements("RecentTraceXml")
                        where File.Exists(xElement.Attribute("filepath").Value)
                        select xElement.Attribute("filepath").Value).ToList();
            }
        }

        /// <summary>
        /// Updates most recently used trace xml files to the Marble settings file.
        /// </summary>
        /// <param name="recentTraceXmlFilePaths">List of recent trace xml paths to save.</param>
        public static void UpdateRecentTraceXmlFiles(List<string> recentTraceXmlFilePaths)
        {
            XElement recentTraceXmlsElement = MarbleSettingsXml.Element("MarbleSettings").Element("FileSettings").Element("RecentTraceXmls");

            if (recentTraceXmlsElement == null) return;

            recentTraceXmlsElement.Elements().Remove();

            foreach (string recentTraceXmlFilePath in recentTraceXmlFilePaths)
            {
                XElement recentTraceXmlElement = new XElement("RecentTraceXml");
                recentTraceXmlElement.Add(new XAttribute("filepath", recentTraceXmlFilePath));
                recentTraceXmlsElement.Add(recentTraceXmlElement);
            }

            MarbleSettingsXml.Save(MarblePaths.MarbleSettingsFile);
        }

        /// <summary>
        /// Loads the content of Marble settings file xml to variable MarbleSettingsXml.
        /// Missing elements are created.
        /// </summary>
        private static void LoadMarbleSettingsFile()
        {
            if (!File.Exists(MarblePaths.MarbleSettingsFile))
            {
                MarbleSettingsXmlParser.InitializeMarbleSettingsXml();
                return;
            }

            MarbleSettingsXmlParser.MarbleSettingsXml = XDocument.Load(MarblePaths.MarbleSettingsFile);

            if (MarbleSettingsXml == null || MarbleSettingsXml.Root == null)
                InitializeMarbleSettingsXml();

            if (MarbleSettingsXml.Root.Element("FileSettings") == null)
                MarbleSettingsXml.Root.Add(new XElement("FileSettings"));

            if (MarbleSettingsXml.Root.Element("FileSettings").Element("RecentTraceXmls") == null)
                MarbleSettingsXml.Root.Element("FileSettings").Add(new XElement("RecentTraceXmls"));

            if (MarbleSettingsXml.Root.Element("ConnectionSettings") == null)
                MarbleSettingsXml.Root.Add(new XElement("ConnectionSettings"));

            if (MarbleSettingsXml.Root.Element("ConnectionSettings").Element("RecentConnections") == null)
                MarbleSettingsXml.Root.Element("ConnectionSettings").Add(new XElement("RecentConnections"));

        }

        /// <summary>
        /// Creates new Marble settings XDocument and stores it to variable MarbleSettingsXml.
        /// </summary>
        private static void InitializeMarbleSettingsXml()
        {
            XElement rootElement = new XElement("MarbleSettings");

            // File Settings
            XElement fileSettingsElement = new XElement("FileSettings");
            fileSettingsElement.Add(new XElement("RecentTestSets"));
            fileSettingsElement.Add(new XElement("RecentTraceXmls"));
            rootElement.Add(fileSettingsElement);

            // Connection settings
            var connectionSettings = new XElement("ConnectionSettings");
            connectionSettings.Add(new XElement("RecentConnections"));
            rootElement.Add(connectionSettings);

            MarbleSettingsXmlParser.MarbleSettingsXml = new XDocument(rootElement);
        }
    }
}
