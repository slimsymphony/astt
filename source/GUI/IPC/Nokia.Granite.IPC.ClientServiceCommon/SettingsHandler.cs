using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.Serialization;
using System.Xml;
using System.Xml.Serialization;

namespace TestAutomation.Gui.Marble.IPC.ServiceClientCommon
{
    #region Parameter class that stores the common base settings

    [DataContract]
    public class BaseSettings
    {
        [DataMember]
        [XmlElement]
        public XmlElement Logging { get; set; }

        public BaseSettings()
        {
            this.Logging = null;
        }
    }

    [DataContract]
    public class ClientSettings : BaseSettings
    {
        [DataMember]
        [XmlElement]
        public string ServiceExecutable { get; set; }

        [DataMember]
        [XmlElement]
        public string ServiceExecutableArgs { get; set; }

        [DataMember]
        [XmlElement]
        public ServiceUri ServiceUri { get; set; }

        public ClientSettings()
        {
            this.ServiceExecutable = string.Empty;
            this.ServiceExecutableArgs = string.Empty;
            this.ServiceUri = new ServiceUri();
        }
    }

    /// <summary>
    /// ServiceUri parameterclass
    /// </summary>
    [DataContract]
    public class ServiceUri
    {
        [DataMember]
        [XmlAttribute]
        public string HostAddress { get; set; }

        [DataMember]
        [XmlAttribute]
        public int ServicePort { get; set; }

        public ServiceUri()
        {
            this.HostAddress = "localhost";
            this.ServicePort = -1;
        }
    }

    #endregion

    /// <summary>
    /// Settings handler for xml based settings.
    /// </summary>
    public class SettingsHandler
    {
        #region Private members

        private FileSystemWatcher watcher;
        private readonly string settingsFilePath;
        private readonly object saveLock = new object();
        private readonly object readLock = new object();

        #endregion

        #region Properties

        public object SettingsObject { get; set; }

        public string SettingsFilePath { get { return this.settingsFilePath; } }

        #endregion

        #region Constructors

        public SettingsHandler(object settingsObject) : this(settingsObject, Environment.CurrentDirectory + "\\Settings.xml") { }

        public SettingsHandler(object settingsObject, string settingsPath)
        {           
            this.settingsFilePath = settingsPath;
            this.SettingsObject = settingsObject;

            if (File.Exists(this.settingsFilePath))
            {
                // Add filesystem watcher for watching whether settings are changed by manually editing the file.
                this.watcher = new FileSystemWatcher(settingsPath.Substring(0, settingsPath.LastIndexOf('\\')),
                                                     settingsPath.Substring(settingsPath.LastIndexOf('\\') + 1));
                watcher.Changed += (watcher_Changed);

                this.loadSettings();
            }
        }

        #endregion

        #region Public methods

        /// <summary>
        /// Serializes the settings to xml
        /// </summary>
        public void SaveSettings()
        {
            if (this.watcher != null)
                watcher.EnableRaisingEvents = false;

            lock (this.saveLock)
            {
                const int tryCount = 10;
                for (int i = 0; i < tryCount; i++)
                {
                    try
                    {
                        XmlSerializer x = new XmlSerializer(this.SettingsObject.GetType(), new XmlRootAttribute("Settings"));
                        StreamWriter writer = new StreamWriter(this.settingsFilePath);
                        x.Serialize(writer, this.SettingsObject);
                        writer.Close();
                        break;
                    }
                    catch (Exception ex)
                    {
                        if (i == tryCount - 1)
                        {
                            writeEventLog("SaveSettings to " + this.SettingsFilePath + " failed: " + ex.Message);
                        }
                    }
                }
            }
            if (this.watcher != null)
                watcher.EnableRaisingEvents = true;
        }

        #endregion

        #region Private methods

        /// <summary>
        /// Loads settings from xml file.
        /// </summary>
        private void loadSettings()
        {
            watcher.EnableRaisingEvents = false;

            lock (this.readLock)
            {
                // Try to load settings from xml. Upon error, try again.
                const int tryCount = 10;
                for (int i = 0; i < tryCount; i++)
                {
                    try
                    {
                        if (!File.Exists(this.settingsFilePath))
                        {
                            this.SaveSettings();
                        }
                        else
                        {
                            XmlSerializer x = new XmlSerializer(this.SettingsObject.GetType(), new XmlRootAttribute("Settings"));
                            StreamReader reader = new StreamReader(this.settingsFilePath);
                            this.SettingsObject = x.Deserialize(reader);
                            reader.Close();
                        }
                        break;
                    }
                    catch (Exception ex)
                    {
                        if (i == tryCount -1)
                        {
                            writeEventLog("LoadSettings from " + this.SettingsFilePath + " failed: " + ex.Message);
                        }
                    }
                }
            }

            watcher.EnableRaisingEvents = true;
        }

        private void writeEventLog(string error)
        {
            string sSource = "Marble ClientServiceCommon Settingshandler";
            string sLog = "Application";

            if (!EventLog.SourceExists(sSource))
                EventLog.CreateEventSource(sSource, sLog);

            EventLog.WriteEntry(sSource, error, EventLogEntryType.Error);
        }

        /// <summary>
        /// Event handler for filesystemwatcher
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void watcher_Changed(object sender, FileSystemEventArgs e)
        {
            this.loadSettings();
        }

        #endregion
    }
}
