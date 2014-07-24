// -----------------------------------------------------------------------
// <copyright file="MarbleSettingsModel.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

using System.Xml.Serialization;
using Marble.Communication;

namespace Marble.Model
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Text;

    using Marble.Utilities;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// Static class containing settings used in Marble.
    /// </summary>
    public static class MarbleSettingsModel
    {
        /// <summary>
        /// Initializes static members of the <see cref="MarbleSettingsModel"/> class.
        /// </summary>
        static MarbleSettingsModel()
        {
            FileSettings = new MarbleFileSettingsModel();
            RecentConnections = MarbleSettingsXmlParser.RecentConnections;
        }

        /// <summary>
        /// Gets Marble file settings model object.
        /// </summary>
        public static MarbleFileSettingsModel FileSettings { get; private set; }

        /// <summary>
        /// Previously used connections.
        /// key: Connection usage, value: ConnectionIdentifier
        /// e.g. (Main, Reference, Trace, Remote, Remote2, etc.), GConnId_e4ed89e1b44f4b19
        /// </summary>
        public static Dictionary<string, string> RecentConnections { get; private set; }

        public static void UpdateRecentConnections()
        {
            MarbleSettingsXmlParser.UpdateRecentConnections(RecentConnections);
        }
    }

    /// <summary>
    /// Class containing information about file settings in Marble.
    /// </summary>
    public class MarbleFileSettingsModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="MarbleFileSettingsModel"/> class.
        /// </summary>
        public MarbleFileSettingsModel()
        {
            this.RecentTestSets = new List<string>();

            this.loadMarbleFileSettings();
        }

        /// <summary>
        /// Gets a value indicating maximum amount of recent files which are kept in the settings file.
        /// </summary>
        public int MaxAmountOfRecentFilesToKeep { get { return 10; } }

        /// <summary>
        /// Gets a list containing recently loaded test sets. Last loaded test set is the first one.
        /// </summary>
        public List<string> RecentTestSets { get; private set; }

        /// <summary>
        /// Gets file path of the most recent test set.
        /// </summary>
        public string RecentTestSet
        {
            get
            {
                if (this.RecentTestSets == null) return null;
                if (this.RecentTestSets.Count <= 0) return null;

                return this.RecentTestSets.FirstOrDefault(File.Exists);
            }
        }

        /// <summary>
        /// Gets a list containing recently used trace xml file paths (in descending order).
        /// First item of the list is an empty string (for simpler usage with combobox).
        /// So user can select empty value (this is tricky to implement in the view side).
        /// </summary>
        public ObservableCollectionAdv<string> RecentTraceFiles { get; private set; }

        /// <summary>
        /// Gets file path of the most recent trace xml file.
        /// </summary>
        public string RecentTraceFile
        {
            get
            {
                if (this.RecentTraceFiles == null || this.RecentTraceFiles.Count <= 0) return null;
                return this.RecentTraceFiles.FirstOrDefault(File.Exists);
            }
        }

        /// <summary>
        /// Adds loaded test set file path to the list of most recently loaded test sets.
        /// </summary>
        /// <param name="filePath">File path of the test set file.</param>
        /// <param name="updateSettingsFile">Whether to update settings file.</param>
        public static void AddLoadedTestSetToRecentTestSets(string filePath, bool updateSettingsFile = true)
        {
            if (string.IsNullOrEmpty(filePath)) return;
            if (!File.Exists(filePath)) return;
            if (Path.GetExtension(filePath) == null) return;
            if (!Path.GetExtension(filePath).Equals(".testset")) return;

            while (MarbleSettingsModel.FileSettings.RecentTestSets.Contains(filePath))
                MarbleSettingsModel.FileSettings.RecentTestSets.Remove(filePath);

            MarbleSettingsModel.FileSettings.RecentTestSets.Insert(0, filePath);

            // Remove entries from the end so that maximum history length is not exceeded
            if (MarbleSettingsModel.FileSettings.RecentTestSets.Count > MarbleSettingsModel.FileSettings.MaxAmountOfRecentFilesToKeep)
                MarbleSettingsModel.FileSettings.RecentTestSets.RemoveRange(
                    MarbleSettingsModel.FileSettings.MaxAmountOfRecentFilesToKeep,
                    MarbleSettingsModel.FileSettings.RecentTestSets.Count - MarbleSettingsModel.FileSettings.MaxAmountOfRecentFilesToKeep);

            if (updateSettingsFile)
                MarbleSettingsXmlParser.UpdateRecentTestSetFiles(MarbleSettingsModel.FileSettings.RecentTestSets);
        }

        /// <summary>
        /// Adds loaded test set file paths to the list of most recently loaded test sets.
        /// </summary>
        /// <param name="filePaths">List of file paths of the test set files.</param>
        public static void AddLoadedTestSetToRecentTestSets(List<string> filePaths)
        {
            foreach (string filePath in filePaths.Where(File.Exists))
                MarbleFileSettingsModel.AddLoadedTestSetToRecentTestSets(filePath, true);
        }

        private void loadMarbleFileSettings()
        {
            this.RecentTestSets = MarbleSettingsXmlParser.RecentTestSetFiles;
            this.RecentTraceFiles = new ObservableCollectionAdv<string>(MarbleSettingsXmlParser.RecentTraceXmlFiles);
            this.RecentTraceFiles.Insert(0, string.Empty);
        }

        /// <summary>
        /// Adds trace xml file path to the list of recently used trace xml files.
        /// </summary>
        /// <param name="filePath">File path of the trace xml file.</param>
        /// <param name="updateSettingsFile">Whether to update settings file.</param>
        public static void AddTraceXmlToRecentList(string filePath, bool updateSettingsFile = true)
        {
            if (string.IsNullOrEmpty(filePath)) return;
            if (!File.Exists(filePath)) return;
            if (Path.GetExtension(filePath) == null) return;
            if (!Path.GetExtension(filePath).Equals(".xml")) return;

            while (MarbleSettingsModel.FileSettings.RecentTraceFiles.Contains(filePath))
                MarbleSettingsModel.FileSettings.RecentTraceFiles.Remove(filePath);

            MarbleSettingsModel.FileSettings.RecentTraceFiles.Insert(0, filePath);

            // Remove entries from the end so that maximum history length is not exceeded
            if (MarbleSettingsModel.FileSettings.RecentTraceFiles.Count > MarbleSettingsModel.FileSettings.MaxAmountOfRecentFilesToKeep)
                MarbleSettingsModel.FileSettings.RecentTraceFiles.RemoveRange(
                    MarbleSettingsModel.FileSettings.MaxAmountOfRecentFilesToKeep,
                    MarbleSettingsModel.FileSettings.RecentTraceFiles.Count - MarbleSettingsModel.FileSettings.MaxAmountOfRecentFilesToKeep);

            if (updateSettingsFile)
                MarbleSettingsXmlParser.UpdateRecentTraceXmlFiles(MarbleSettingsModel.FileSettings.RecentTraceFiles.ToList());
        }

    }
}
