using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Marble.Model
{
    using System.Collections;
    using System.Collections.ObjectModel;
    using System.Collections.Specialized;
    using System.ComponentModel;
    using System.Threading;
    using System.Windows;
    using System.Windows.Data;
    using System.Windows.Threading;

    using Marble.Communication;
    using Marble.Utilities;

    using MarbleLibrary.CustomControls;
    using MarbleLibrary.Utilities;


    /// <summary>
    /// NOTE: Create viewmodel later from this.
    /// </summary>
    public class MarbleLogModel : INotifyPropertyChanged
    {
        private const int defaultMaxDisplayedEntries = 2000;

        private const int minDisplayedEntries = 100;

        private const int excessiveEntriesUntilFlush = 500;

        private const int absoluteMaxPossibleEntries = 10000;

        private static readonly TimeSpan minEntryLiveTime = new TimeSpan(0, 5, 0);

        private static readonly TimeSpan flushInterval = new TimeSpan(0, 2, 0);

        private DateTime previousFlushTime;

        private int maxDisplayedEntries = defaultMaxDisplayedEntries;

        public int MaxDisplayedEntries
        {
            get
            {
                return this.maxDisplayedEntries;
            }
            set
            {
                this.maxDisplayedEntries = value < minDisplayedEntries ? minDisplayedEntries : value;

                this.removeExcessiveLogEntriesTimeBased();
            }
        }

        private DispatcherTimer updateMarbleLogEntriesDispatchTimer;

        ////private BindingList<MarbleLogEntry> marbleLogEntries;

        /// <summary>
        /// Lock object for synchronization.
        /// </summary>
        private static readonly object syncLock = new object();

        private static readonly object collectionAddLock = new object();

        public MarbleLogModel()
        {
            this.MarbleLogEntries = new FastObservableCollection<MarbleLogEntry>();
            this.bufferLogEntryCollection = new ObservableCollection<MarbleLogEntry>();
            ////this.MarbleLogEntries = new BindingList<MarbleLogEntry>();
            ////this.MarbleLogEntries.AllowEdit = true;
            ////this.MarbleLogEntries.AllowNew = true;
            ////this.MarbleLogEntries.AllowRemove = true;
            
            this.updateMarbleLogEntriesDispatchTimer = new DispatcherTimer(DispatcherPriority.Normal);
            this.updateMarbleLogEntriesDispatchTimer.Interval = new TimeSpan(0, 0, 0, 0, 200);
            this.updateMarbleLogEntriesDispatchTimer.Tick += updateMarbleLogEntriesDispatchTimer_Tick;

            // Enable the cross thread access to observablection collection from other threads.
            BindingOperations.EnableCollectionSynchronization(this.MarbleLogEntries, syncLock);
        }

        ~MarbleLogModel()
        {
            this.updateMarbleLogEntriesDispatchTimer.Tick -= this.updateMarbleLogEntriesDispatchTimer_Tick;
            this.updateMarbleLogEntriesDispatchTimer.Stop();
        }

        public FastObservableCollection<MarbleLogEntry> MarbleLogEntries { get; private set; }

        ////public BindingList<MarbleLogEntry> MarbleLogEntries
        ////{
        ////    get
        ////    {
        ////        return this.marbleLogEntries;
        ////    }
        ////    private set
        ////    {
        ////        this.marbleLogEntries = value;
        ////        this.OnPropertyChanged("MarbleLogEntries");
        ////    }
        ////}

        /// <summary>
        /// ObservableCollection which is used for buffering log entries to restrain MarbleLogEntries update interval.
        /// </summary>
        private ObservableCollection<MarbleLogEntry> bufferLogEntryCollection { get; set; }

        public string GetCopyDataFromLogEntries(IList logEntries)
        {
            if (logEntries == null) return string.Empty;

            StringBuilder stringBuilder = new StringBuilder();

            foreach (MarbleLogEntry marbleLogEntry in logEntries)
            {
                stringBuilder.AppendLine(marbleLogEntry.EntryCopyContent);
            }

            return stringBuilder.ToString();
        }

        public void AddMarbleLogEntry(MarbleLogEntry marbleLogEntry)
        {
            lock (collectionAddLock)
            {
                if (marbleLogEntry == null) return;

                this.addLogEntryUsingBuffer(marbleLogEntry);

                ////if (!this.groupSameTypeMessage(marbleLogEntry))
                ////{
                ////    this.MarbleLogEntries.Add(marbleLogEntry);
                ////}

                ////this.removeExcessiveLogEntriesTimeBased();

                //this.OnPropertyChanged("MarbleLogEntries");

            }
        }

        internal void AddMarbleLogEntry(Log4NetProvider.LogEntry log4NetLogEntry)
        {
            if (log4NetLogEntry == null) return;

            this.AddMarbleLogEntry(new MarbleLogEntry(log4NetLogEntry));
        }

        private void addLogEntryUsingBuffer(MarbleLogEntry marbleLogEntry)
        {
            if (this.updateMarbleLogEntriesDispatchTimer.IsEnabled)
            {
                lock (this.bufferLogEntryCollection)
                {
                    this.bufferLogEntryCollection.Add(marbleLogEntry);
                }
            }
            else
            {
                lock (this.bufferLogEntryCollection)
                {
                    this.bufferLogEntryCollection.Add(marbleLogEntry);
                    this.updateMarbleLogEntriesDispatchTimer.Start();
                }
            }
        }

        private void updateMarbleLogEntriesDispatchTimer_Tick(object sender, EventArgs e)
        {
            lock (this.bufferLogEntryCollection)
            {
                if (this.bufferLogEntryCollection.Count > 20)
                {
                    this.MarbleLogEntries.SuspendCollectionChangeNotification();
                }

                foreach (MarbleLogEntry marbleLogEntry in bufferLogEntryCollection)
                {
                    if (!this.groupSameTypeMessage(marbleLogEntry))
                    {
                        this.MarbleLogEntries.Add(marbleLogEntry);
                    }
                }

                this.removeExcessiveLogEntriesTimeBased();


                if (this.bufferLogEntryCollection.Count > 20)
                {
                    this.MarbleLogEntries.ResumeCollectionChangeNotification();
                    this.MarbleLogEntries.NotifyChanges();
                }

                this.bufferLogEntryCollection.Clear();

                this.updateMarbleLogEntriesDispatchTimer.Stop();
            }
        }

        /// <summary>
        /// Groups same type messages.
        /// </summary>
        /// <param name="marbleLogEntry"></param>
        /// <returns>Returns true when message was grouped.</returns>
        private bool groupSameTypeMessage(MarbleLogEntry marbleLogEntry)
        {
            if (this.MarbleLogEntries.Count <= 0) return false;

            ////this.MarbleLogEntries.RaiseListChangedEvents = true;

            ////MarbleLogEntry lastEntry = this.MarbleLogEntries.Last();
            MarbleLogEntry lastEntry = this.MarbleLogEntries[this.MarbleLogEntries.Count - 1];

            if (lastEntry == null) return false;

            if (lastEntry.Message != marbleLogEntry.Message) return false;

            if (marbleLogEntry.LogEntryType != lastEntry.LogEntryType
                || marbleLogEntry.LogEntryType != MarbleLogEntryType.Event) 
                return false;
            
            if (lastEntry.GroupedTimeStamps == null)
                lastEntry.GroupedTimeStamps = new ObservableCollection<DateTime>();

            // First entries own time stamp is added to the list.
            if (lastEntry.GroupedTimeStamps.Count == 0)
                lastEntry.GroupedTimeStamps.Add(lastEntry.TimeStamp);

            lastEntry.GroupedTimeStamps.Add(marbleLogEntry.TimeStamp);

            ////this.MarbleLogEntries.RaiseListChangedEvents = false;

            // Log entry is removed and readded because log control intentionally binds one time only.
            this.MarbleLogEntries.Remove(lastEntry);
            this.MarbleLogEntries.Add(lastEntry);

            ////this.MarbleLogEntries.RaiseListChangedEvents = true;

            return true;
        }

        private void removeExcessiveLogEntries()
        {
            if (this.MarbleLogEntries.Count <= 0 && this.MarbleLogEntries.Count < minDisplayedEntries) return;

            if (this.MarbleLogEntries.Count > maxDisplayedEntries + excessiveEntriesUntilFlush)
            {
                int itemCountToRemove = this.MarbleLogEntries.Count - maxDisplayedEntries;

                this.MarbleLogEntries.RemoveRange(0, itemCountToRemove);

                ////this.MarbleLogEntries.RaiseListChangedEvents = false;

                ////for (int i = 0; i < itemCountToRemove; i++)
                ////{
                ////    this.MarbleLogEntries.RemoveAt(0);
                ////}

                ////this.MarbleLogEntries.RaiseListChangedEvents = true;
                
                GC.Collect();
            }
        }

        private void removeExcessiveLogEntriesTimeBased()
        {
            if (this.MarbleLogEntries.Count <= 0 && this.MarbleLogEntries.Count < minDisplayedEntries) return;

            if (this.previousFlushTime.Ticks == 0) this.previousFlushTime = MarbleLogEntries.First().TimeStamp;

            if (DateTime.Now.Ticks - this.previousFlushTime.Ticks < flushInterval.Ticks) return;

            this.previousFlushTime = DateTime.Now;

            MarbleLogEntry lastEntryToRemove = this.MarbleLogEntries.LastOrDefault(marbleLogEntry => marbleLogEntry.TimeStamp.Ticks < DateTime.Now.Ticks - minEntryLiveTime.Ticks);

            int lastIndexToRemove = lastEntryToRemove != null ? this.MarbleLogEntries.IndexOf(lastEntryToRemove) : -1;

            if (lastIndexToRemove < 0 || this.MarbleLogEntries.Count < maxDisplayedEntries) return;

            if ((this.MarbleLogEntries.Count - lastIndexToRemove) > maxDisplayedEntries)
            {
                this.MarbleLogEntries.RemoveRange(0, lastIndexToRemove);

                ////this.MarbleLogEntries.RaiseListChangedEvents = false;

                ////for (int i = 0; i < lastIndexToRemove; i++)
                ////{
                ////    this.MarbleLogEntries[0] = null;
                ////    this.MarbleLogEntries.RemoveAt(0);
                ////}

                ////this.MarbleLogEntries.RaiseListChangedEvents = true;
            }
            else
            {
                this.MarbleLogEntries.RemoveRange(0, this.MarbleLogEntries.Count - maxDisplayedEntries);

                ////this.MarbleLogEntries.RaiseListChangedEvents = false;

                ////for (int i = 0; i < this.MarbleLogEntries.Count - maxDisplayedEntries; i++)
                ////{
                ////    this.MarbleLogEntries[0] = null;
                ////    this.MarbleLogEntries.RemoveAt(0);
                ////}

                ////this.MarbleLogEntries.RaiseListChangedEvents = true;
            }

            GC.Collect();
        }

        private void generateRandomTestData()
        {
            this.generateRandomTestData(100000);
        }

        private void generateRandomTestData(int numberOfRows)
        {


            for (int i = 0; i < numberOfRows; i++)
            {
                //List<MarbleLogEntry> bufferList = new List<MarbleLogEntry>();

                //for (int j = 0; j < 5; j++)
                //{

                    MarbleLogEntry testLogEntry = new MarbleLogEntry(new Log4NetProvider.LogEntry() { DateTime = DateTime.Now, Description = "jfsaoijfsiaojfdosiajd"});

                    Array values = Enum.GetValues(typeof(MarbleLogEntryType));
                    Random random = new Random((int)DateTime.Now.Ticks);
                    testLogEntry.LogEntryType = (MarbleLogEntryType)values.GetValue(random.Next(values.Length));

                    //testLogEntry.TimeStamp = DateTime.Now;
                    testLogEntry.Message = "[" + i + "] " +
                        TextUtilities.GenerateRandomStringWithWhiteSpaces(
                            Convert.ToInt32(random.NextDouble() * (30 - 1) + 1), 1, 30);

                    ////this.AddMarbleLogEntry(testLogEntry);

                    App.ViewModel.MarbleConnector.WriteTestDataToLogs(testLogEntry);

                    //bufferList.Add(testLogEntry);
                //}

                ////foreach (var marbleLogEntry in bufferList)
                ////{
                ////    this.AddMarbleLogEntry(marbleLogEntry);
                ////}

                Thread.Sleep(2);
            }
        }

        public void GenerateRandomTestData(int numberOfRows = 100000)
        {
            Action action = () => this.generateRandomTestData(numberOfRows);
            Task.Factory.StartNew(action); 
        }

        public void FlushEntries()
        {
            //lock (collectionAddLock)
            //{
                this.removeExcessiveLogEntries();
                GC.Collect();
            //}
        }

        public void ClearEntries()
        {
            //lock (collectionAddLock)
            //{
                this.MarbleLogEntries.Clear();
                GC.Collect();
            //}
        }

        #region INotifyPropertyChanged Members

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }

    public enum MarbleLogEntryType
    {
        Generic = 0,
        GuiMessage = 1,
        Event,
        Info,
        Warning,
        Error,
        Failure,
        Fatal,
        StageStart,
        FrameworkResponse,
        FrameworkRequest,
    }

    public class MarbleLogEntry : INotifyPropertyChanged
    ////public class MarbleLogEntry
    {
        private string originalMessage;

        internal MarbleLogEntry(Log4NetProvider.LogEntry log4NetLogEntry)
        {
            this.GroupedTimeStamps = new ObservableCollection<DateTime>();

            this.TimeStamp = log4NetLogEntry.DateTime;
            this.OriginalMessage = log4NetLogEntry.Description;
            this.MetaData = log4NetLogEntry.MetaData;
            this.parseTypeAndMessage(log4NetLogEntry.Description);

            this.ProductId = this.getProductIdFromMetaData();
        }

        internal MarbleLogEntry(string guiMessage)
        {
            this.GroupedTimeStamps = new ObservableCollection<DateTime>();

            this.TimeStamp = DateTime.Now;
            this.OriginalMessage = guiMessage;
            this.LogEntryType = MarbleLogEntryType.GuiMessage;
            this.Message = guiMessage;
        }

        internal MarbleLogEntry(MarbleLogEntryType logEntryType, string message)
        {
            this.GroupedTimeStamps = new ObservableCollection<DateTime>();

            this.TimeStamp = DateTime.Now;
            this.OriginalMessage = message;
            this.LogEntryType = logEntryType;
            this.Message = message;
        }

        public MarbleLogEntry()
        {
            this.GroupedTimeStamps = new ObservableCollection<DateTime>();
        }

        public DateTime TimeStamp { get; set; }

        public MarbleLogEntryType LogEntryType { get; set; }

        public bool IsGrouped 
        { 
            get
            {
                return this.GroupedTimeStamps != null && this.GroupedTimeStamps.Count > 1;
            }
        }

        public ObservableCollection<DateTime> GroupedTimeStamps { get; internal set; }

        public string Message { get; set; }

        /// <summary>
        /// Gets the string content which is copied to clipboard from log entry.
        /// </summary>
        public string EntryCopyContent
        {
            get
            {
                if (!this.IsGrouped)
                    return this.TimeStamp.ToString("dd.MM.yyyy HH:mm:ss.fff ") + this.OriginalMessage;

                return this.getGroupedMessageEntryCopyContent();
            }
        }

        /// <summary>
        /// Gets the original log message.
        /// </summary>
        public string OriginalMessage
        {
            get
            {
                if (this.originalMessage == null)
                    return this.Message ?? string.Empty;

                return this.originalMessage;
            }
            private set
            {
                this.originalMessage = value;
            }
        }

        /// <summary>
        /// Gets the product ID.
        /// </summary>
        public string ProductId { get; private set; }

        /// <summary>
        /// Gets the log entry meta data.
        /// </summary>
        internal object MetaData { get; private set; }

        private void parseTypeAndMessage(string logEntryMessage)
        {
            this.LogEntryType = this.getLogEntryTypeFromMessage(logEntryMessage);

            this.Message = this.removeLogEntryTypeMessageFromString(logEntryMessage);
        }

        private MarbleLogEntryType getLogEntryTypeFromMessage(string logEntryMessage)
        {
            string typeParsingText = logEntryMessage.Replace(" ", string.Empty).ToLower();

            if (typeParsingText.StartsWith("!"))
            {
                ////if (typeParsingText.StartsWith("!error"))
                ////{
                ////    return MarbleLogEntryType.Error;
                ////}
                if (typeParsingText.StartsWith("!warning"))
                {
                    return MarbleLogEntryType.Warning;
                }
                else if (typeParsingText.StartsWith("!failure"))
                {
                    return MarbleLogEntryType.Failure;
                }

                return MarbleLogEntryType.Error;
            }
            else if (typeParsingText.StartsWith("-"))
            {
                if (typeParsingText.StartsWith("-__"))
                {
                    return MarbleLogEntryType.Event;
                }
                else if (typeParsingText.Contains("==="))
                {
                    return MarbleLogEntryType.StageStart;
                }

                return MarbleLogEntryType.Info;
            }

            return MarbleLogEntryType.Generic;
        }

        private string removeLogEntryTypeMessageFromString(string logEntryMessage)
        {
            string cleanLogEntryMessage = logEntryMessage;

            switch (LogEntryType)
            {
                case MarbleLogEntryType.Generic:
                    return logEntryMessage;
                case MarbleLogEntryType.GuiMessage:
                    return logEntryMessage;
                case MarbleLogEntryType.Event:
                    cleanLogEntryMessage = cleanLogEntryMessage.TrimStart(new[] { '-', ' ', '_' });
                    break;
                case MarbleLogEntryType.Info:
                    cleanLogEntryMessage = cleanLogEntryMessage.TrimStart('-');
                    break;
                case MarbleLogEntryType.Warning:
                    cleanLogEntryMessage = cleanLogEntryMessage.TrimStart('!');
                    cleanLogEntryMessage = cleanLogEntryMessage.TrimStart();
                    break;
                case MarbleLogEntryType.Error:
                    cleanLogEntryMessage = cleanLogEntryMessage.TrimStart('!');
                    cleanLogEntryMessage = cleanLogEntryMessage.TrimStart();
                    break;
                case MarbleLogEntryType.Failure:
                    cleanLogEntryMessage = cleanLogEntryMessage.TrimStart('!');
                    cleanLogEntryMessage = cleanLogEntryMessage.TrimStart();
                    break;
                case MarbleLogEntryType.Fatal:
                    break;
                case MarbleLogEntryType.StageStart:
                    cleanLogEntryMessage = cleanLogEntryMessage.TrimStart('-');
                    cleanLogEntryMessage = cleanLogEntryMessage.Trim(new[] { '-', ' ', '=' });
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }

            return cleanLogEntryMessage.Trim();
        }

        private string getProductIdFromMetaData()
        {
            if (this.MetaData == null || !(this.MetaData is IEnumerable)) return string.Empty;
                
            string productId = string.Empty;

            foreach (var metaDataSlot in (IEnumerable)this.MetaData)
            {

                KeyValuePair<string, object>? keyValuePair = metaDataSlot as KeyValuePair<string, object>?;
            }

            return productId;
        }

        private string getGroupedMessageEntryCopyContent()
        {
            StringBuilder stringBuilder = new StringBuilder();

            foreach (DateTime groupedTimeStamp in GroupedTimeStamps)
            {
                stringBuilder.AppendLine(groupedTimeStamp.ToString("dd.MM.yyyy HH:mm:ss.fff ") + this.OriginalMessage);
            }

            return stringBuilder.ToString().TrimEnd('\n');
        }

        #region INotifyPropertyChanged Members

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }
}
