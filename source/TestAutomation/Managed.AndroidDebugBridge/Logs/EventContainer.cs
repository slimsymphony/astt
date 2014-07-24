using Managed.Adb.Logs;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace Managed.Adb.Logs
{
    /// <summary>
    /// Type for event data
    /// </summary>
    public enum EventValueType
    {
        /// <summary>
        /// Unknown
        /// </summary>
        UNKNOWN = 0,
        
        /// <summary>
        /// 32-bit Integer
        /// </summary>
        INT = 1,
        
        /// <summary>
        /// 64-bit Integer
        /// </summary>
        LONG = 2,
        
        /// <summary>
        /// String
        /// </summary>
        STRING = 3,
        
        /// <summary>
        /// List/array
        /// </summary>
        LIST = 4,
        
        /// <summary>
        /// List containing an inner list
        /// </summary>
        TREE = 5
    }

    /// <summary>
    /// Represents an event and its data.
    /// 
    /// sdk/ddms/libs/ddmlib/src/com/android/ddmlib/log/EventContainer.java
    /// </summary>
    [Serializable]
    public class EventContainer
    {
        private static Regex STORAGE_PATTERN = new Regex("^(\\d+)@(.*)$", RegexOptions.Compiled); //$NON-NLS-1$
        private DateTime m_epoc = new DateTime(1970, 1, 1, 0, 0, 0);
        
        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="entry">LogEntry from in which the event data is stored</param>
        /// <param name="tag">Numeric tag of the event</param>
        /// <param name="tagName">Readable tag of the event</param>
        /// <param name="data">Event data</param>
        public EventContainer(LogEntry entry, int tag, string tagName, object data)
        {
            Data = data;
            Tag = tag;
            TagName = tagName;
            ProcessId = entry.ProcessId;
            ThreadId = entry.ThreadId;
            Second = entry.Seconds;
            Nanosecond = entry.NanoSeconds;
        }

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="tag">Numeric tag of the event</param>
        /// <param name="tagName">Readable tag of the event</param>
        /// <param name="pid">Source process</param>
        /// <param name="tid">Source thread</param>
        /// <param name="sec">Event timestamp seconds</param>
        /// <param name="nsec">Event timestamp nanoseconds</param>
        /// <param name="data">Event data</param>
        public EventContainer(int tag, string tagName, int pid, int tid, int sec, int nsec, object data)
        {
            Data = data;
            Tag = tag;
            TagName = tagName;
            ProcessId = pid;
            ThreadId = tid;
            Second = sec;
            Nanosecond = nsec;
        }

        /// <summary>
        /// Gets the event data
        /// </summary>
        public object Data { get; private set; }

        /// <summary>
        /// Gets the tag
        /// </summary>
        public int Tag { get; private set; }

        /// <summary>
        /// Gets the tag name
        /// </summary>
        public string TagName { get; private set; }

        /// <summary>
        /// Gets the process id
        /// </summary>
        public int ProcessId { get; private set; }
        
        /// <summary>
        /// Gets the thread id
        /// </summary>
        public int ThreadId { get; private set; }
        
        /// <summary>
        /// Gets the event timestamp: seconds after epoc
        /// </summary>
        public int Second { get; private set; }
        
        /// <summary>
        /// Nanoseond part of the timestam: addition to Second -propery
        /// </summary>
        public int Nanosecond { get; private set; }

        /// <summary>
        /// Gets the event timestamp as local time
        /// </summary>
        public DateTime Timestamp
        {
            get
            {
                return m_epoc.AddSeconds(Second).AddTicks(Nanosecond / 100).ToLocalTime();
            }
        }

        /// <summary>
        /// Gets the data as int
        /// </summary>
        /// <returns>Data casted to int; if value type is else than int: InvalidCastException will be thrown</returns>
        public int GetInt()
        {
            if (GetType(Data) == EventValueType.INT) {
                return (int)Data;
            }

            throw new InvalidCastException();
        }

        /// <summary>
        /// Gets the data as long
        /// </summary>
        /// <returns>Data casted to long; if value type is else than long: InvalidCastException will be thrown</returns>
        public long GetLong()
        {
            if (GetType(Data) == EventValueType.LONG)
            {
                return (long)Data;
            }

            throw new InvalidCastException();
        }

        /// <summary>
        /// Gets the data as string
        /// </summary>
        /// <returns>Data casted to string; if value type is else than string: InvalidCastException will be thrown</returns>
        public string GetString()
        {
            if (GetType(Data) == EventValueType.STRING)
            {
                return (string)Data;
            }

            throw new InvalidCastException();
        }

        /// <summary>
        /// Gets a value from index: presuming the type of the data intance is a collection
        /// </summary>
        /// <param name="valueIndex">Index from which the read the data</param>
        /// <returns>Object in the given instance</returns>
        public virtual object GetValue(int valueIndex)
        {
            return GetValue(Data, valueIndex, true);
        }

        /// <summary>
        /// Gets a value from index: presuming the type of the data intance is a collection
        /// </summary>
        /// <param name="valueIndex">Index from which the read the data</param>
        /// <returns>Double value in the given instance</returns>
        public virtual double GetValueAsDouble(int valueIndex)
        {
            return GetValueAsDouble(Data, valueIndex, true);
        }

        /// <summary>
        /// Gets a value from index: presuming the type of the data intance is a collection
        /// </summary>
        /// <param name="valueIndex">Index from which the read the data</param>
        /// <returns>String value in the given instance</returns>
        public virtual string GetValueAsString(int valueIndex)
        {
            return GetValueAsString(Data, valueIndex, true);
        }

        /// <summary>
        /// Gets a value from index: presuming the type of the data intance is a collection
        /// </summary>
        /// <param name="data">Data object from which to read</param>
        /// <param name="valueIndex">Index from which the read the data</param>
        /// <param name="recursive">Value indicating whether to read recursively</param>
        /// <returns>Object in the given instance</returns>
        private object GetValue(object data, int valueIndex, bool recursive) 
        {
            EventValueType type = GetType(data);

            switch (type) {
                case EventValueType.INT:
                case EventValueType.LONG:
                case EventValueType.STRING:
                    return data;
                case EventValueType.LIST:
                    {
                        if (recursive)
                        {
                            object[] list = (object[])data;
                            if (valueIndex >= 0 && valueIndex < list.Length)
                            {
                                return GetValue(list[valueIndex], valueIndex, false);
                            }
                        }
                    }
                    break;
            }

            return null;
        }

        /// <summary>
        /// Gets a value from index: presuming the type of the data intance is a collection
        /// </summary>
        /// <param name="data">Data object from which to read</param>
        /// <param name="valueIndex">Index from which the read the data</param>
        /// <param name="recursive">Value indicating whether to read recursively</param>
        /// <returns>Double value in the given instance</returns>
        private double GetValueAsDouble(object data, int valueIndex, bool recursive)
        {
            EventValueType type = GetType(data);

            switch (type) 
            {
                case EventValueType.INT:
                case EventValueType.LONG:
                    return (double)data;
                case EventValueType.STRING:
                    throw new InvalidCastException();
                case EventValueType.LIST:
                    {
                        if (recursive)
                        {
                            object[] list = (object[])data;
                            if (valueIndex >= 0 && valueIndex < list.Length)
                            {
                                return GetValueAsDouble(list[valueIndex], valueIndex, false);
                            }
                        }
                    }
                    break;
            }

            throw new InvalidCastException();
        }

        /// <summary>
        /// Gets a value from index: presuming the type of the data intance is a collection
        /// </summary>
        /// <param name="data">Data object from which to read</param>
        /// <param name="valueIndex">Index from which the read the data</param>
        /// <param name="recursive">Value indicating whether to read recursively</param>
        /// <returns>String value in the given instance</returns>
        private string GetValueAsString(object data, int valueIndex, bool recursive)
        {
            EventValueType type = GetType(data);

            switch (type) 
            {
                case EventValueType.INT:
                case EventValueType.LONG:
                case EventValueType.STRING:
                    return data.ToString();
                case EventValueType.LIST:
                    {
                        if (recursive)
                        {
                            object[] list = (object[])data;
                            if (valueIndex >= 0 && valueIndex < list.Length)
                            {
                                return GetValueAsString(list[valueIndex], valueIndex, false);
                            }
                        }
                        else
                        {
                            throw new InvalidCastException("getValueAsString() doesn't support EventValueType.TREE");
                        }
                    }
                    break;
            }

            throw new InvalidCastException("getValueAsString() unsupported type:" + type);
        }

        /// <summary>
        /// Gets the event value type of the data
        /// </summary>
        public virtual EventValueType EventValueType
        {
            get
            {
                return GetType(Data);
            }
        }

        /// <summary>
        /// Gets the .NET type of the data object
        /// </summary>
        public Type DataType
        {
            get
            {
                return Data.GetType();
            }
        }

        /// <summary>
        /// Gets the event value type of a data object
        /// </summary>
        /// <param name="data">Data from which to check the event value type</param>
        /// <returns>The event value type of a data object</returns>
        protected virtual EventValueType GetType(object data) 
        {
            if (data is int) 
            {
                return EventValueType.INT;
            }
            else if (data is long) 
            {
                return EventValueType.LONG;
            }
            else if (data is string) 
            {
                return EventValueType.STRING;
            }
            else if (data is object[]) 
            {
                // loop through the list to see if we have another list
                object[] objects = (object[])data;
                foreach (object obj in objects) 
                {
                    EventValueType type = GetType(obj);
            
                    if (type == EventValueType.LIST || type == EventValueType.TREE) {
                        return EventValueType.TREE;
                    }
                }
                return EventValueType.LIST;
            }

            return EventValueType.UNKNOWN;
        }
        
        /// <summary>
        /// Returns a storage string for an object of type supported by EventValueType.
        /// Strings created by this method can be reloaded with GetObjectFromStorageString.
        /// NOTE: for now, only STRING, INT, and LONG are supported.
        /// </summary>
        /// <param name="obj">The object to "convert" into a storage string.</param>
        /// <returns>A string storing the object and its type or null if the type was not recognized.</returns>
        public static string GetStorageString(object obj) {
                
            if (obj is string) {
                return EventValueType.STRING + "@" + obj.ToString(); //$NON-NLS-1$
            } 
            else if (obj is int) {
                return EventValueType.INT + "@" + obj.ToString(); //$NON-NLS-1$
            } 
            else if (obj is long) {
                return EventValueType.LONG + "@" + obj.ToString(); //$NON-NLS-1$
            }

            return null;
        }

        /// <summary>
        /// Creates an object from a storage string created with GetStorageString.
        /// </summary>
        /// <param name="value">The storage string</param>
        /// <returns>An object or null if the string or type were not recognized.</returns>
        public static object GetObjectFromStorageString(string value)
        {
            Match m = STORAGE_PATTERN.Match(value);

            if (m.Success)
            {
                try
                {
                    EventValueType type;
                    if (!Enum.TryParse<EventValueType>(m.Groups[1].Value, out type))
                    {
                        return null;
                    }

                    switch (type)
                    {
                        case EventValueType.STRING:
                            return m.Groups[2].Value;
                        case EventValueType.INT:
                            return int.Parse(m.Groups[2].Value);
                        case EventValueType.LONG:
                            return long.Parse(m.Groups[2].Value);
                    }
                }
                catch (Exception)
                {
                    return null;
                }
            }

            return null;
        }

        /// <summary>
        /// Formats an object to its string presentation
        /// </summary>
        /// <param name="obj">Object to format</param>
        /// <returns>String presentation of an object</returns>
        protected virtual string ObjectToString(object obj)
        {
            if (!(obj is object[]))
            {
                return obj.ToString();
            }

            var collection = obj as object[];
            var builder = new StringBuilder("[");
            for (int i = 0; i < collection.Length; i++)
            {
                builder.Append(ObjectToString(collection[i]));
                if (i < (collection.Length - 1))
                {
                    builder.Append(",");
                }
            }
            builder.Append("]");

            return builder.ToString();
        }

        /// <summary>
        /// Formats the instance to its string presentation
        /// </summary>
        /// <returns>String presentation of the instance</returns>
        public override string ToString()
        {
            return ObjectToString(Data);
        }
    }
}
