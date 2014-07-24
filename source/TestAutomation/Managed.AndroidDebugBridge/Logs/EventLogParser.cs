using Managed.Adb;
using Managed.Adb.Logs;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace Managed.Adb.Logs
{
    /// <summary>
    /// Receiver for tag names - for event log
    /// </summary>
    public class TagReceiver : MultiLineReceiver
    {
        private Action<string> m_action;

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="lineProcessor">Call back action for processing lines</param>
        public TagReceiver (Action<string> lineProcessor)
        {
            m_action = lineProcessor;
        }

        /// <summary>
        /// Called when multiline data is available
        /// </summary>
        /// <param name="lines">Mulyiline data</param>
        protected override void ProcessNewLines(string[] lines)
        {
            foreach (var line in lines)
	        {
                m_action.Invoke(line);
	        }
        }
    }

    /// <summary>
    /// Parser for the "event" log.
    /// 
    /// /sdk/ddms/libs/ddmlib/src/com/android/ddmlib/log/EventLogParser.java
    /// </summary>
    public class EventLogParser
    {
        // Location of the tag map file on the device
        private const string EVENT_TAG_MAP_FILE = "/system/etc/event-log-tags"; //$NON-NLS-1$
    
        //Event log entry types.  These must match up with the declarations in
        //java/android/android/util/EventLog.java.
        private const int EVENT_TYPE_INT      = 0;
        private const int EVENT_TYPE_LONG     = 1;
        private const int EVENT_TYPE_STRING   = 2;
        private const int EVENT_TYPE_LIST     = 3;

        private Regex PATTERN_SIMPLE_TAG = new Regex("^(\\d+)\\s+([A-Za-z0-9_]+)\\s*$", RegexOptions.Compiled); //$NON-NLS-1$
        private Regex PATTERN_TAG_WITH_DESC = new Regex("^(\\d+)\\s+([A-Za-z0-9_]+)\\s*(.*)\\s*$", RegexOptions.Compiled); //$NON-NLS-1$
        private Regex PATTERN_DESCRIPTION = new Regex("\\(([A-Za-z0-9_\\s]+)\\|(\\d+)(\\|\\d+){0,1}\\)", RegexOptions.Compiled); //$NON-NLS-1$

        private Dictionary<int, string> mTagMap = new Dictionary<int, string>();
        private Dictionary<int, EventValueDescription[]> mValueDescriptionMap = new Dictionary<int,EventValueDescription[]>();
       
        /// <summary>
        /// Inits the parser for a specific Device.
        /// 
        /// This methods reads the event-log-tags located on the device to find out
        /// what tags are being written to the event log and what their format is.
        /// </summary>
        /// <param name="device">The device</param>
        /// <returns>True if success, false if failure or cancellation.</returns>
        public bool Init(Device device) {
            // read the event tag map file on the device.
            try 
            {
                device.ExecuteShellCommand("cat " + EVENT_TAG_MAP_FILE, new TagReceiver(new Action<string>(ProcessTagLine)), DdmPreferences.LongTimeout);
                if (!mTagMap.ContainsKey(GcEventContainer.GC_EVENT_TAG))
                {
                    mTagMap.Add(GcEventContainer.GC_EVENT_TAG, "GC");
                }
            } 
            catch (Exception) 
            {
                // catch all possible exceptions and return false.
                return false;
            }

            return true;
        }

        /// <summary>
        /// Gets the Tag mappings
        /// </summary>
        public Dictionary<int, string> TagMap
        {
            get
            {
                return mTagMap;
            }
        }

        /// <summary>
        /// Gets the event info mappings
        /// </summary>
        public Dictionary<int, EventValueDescription[]> ValueDescriptionMap
        {
            get
            {
                return mValueDescriptionMap;
            }
        }

        /// <summary>
        /// Processes a line from the event-log-tags file.
        /// </summary>
        /// <param name="line">The line to process</param>
        private void ProcessTagLine(string line)
        {
            // ignore empty lines and comment lines
            if (!string.IsNullOrEmpty(line) && line[0] != '#')
            {
                Match m = PATTERN_TAG_WITH_DESC.Match(line);
                if (m.Success)
                {
                    try
                    {
                        int value = int.Parse(m.Groups[1].Value);
                        string name = m.Groups[2].Value;
                        if (name != null && !mTagMap.ContainsKey(value))
                        {
                            mTagMap.Add(value, name);
                        }

                        // special case for the GC tag. We ignore what is in the file,
                        // and take what the custom GcEventContainer class tells us.
                        // This is due to the event encoding several values on 2 longs.
                        // @see GcEventContainer
                        if (value == GcEventContainer.GC_EVENT_TAG)
                        {
                            mValueDescriptionMap.Add(value, GcEventContainer.ValueDescriptions);
                        }
                        else
                        {
                            string description = m.Groups[3].Value;
                            if (!string.IsNullOrEmpty(description))
                            {
                                EventValueDescription[] desc = ProcessDescription(description);

                                if (desc != null && !mValueDescriptionMap.ContainsKey(value))
                                {
                                    mValueDescriptionMap.Add(value, desc);
                                }
                            }
                        }
                    }
                    catch (Exception)
                    {
                        // failed to convert the number into a string. just ignore it.
                    }
                }
                else
                {
                    m = PATTERN_SIMPLE_TAG.Match(line);
                    if (m.Success)
                    {
                        int value = int.Parse(m.Groups[1].Value);
                        string name = m.Groups[2].Value;
                        if (name != null && !mTagMap.ContainsKey(value))
                        {
                            mTagMap.Add(value, name);
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Processes descriptions from the description string
        /// </summary>
        /// <param name="description">A description string</param>
        /// <returns>List of descriptions</returns>
        private EventValueDescription[] ProcessDescription(string description)
        {
            string[] descriptions = Regex.Split(description, "\\s*,\\s*", RegexOptions.Compiled); //$NON-NLS-1$
            List<EventValueDescription> list = new List<EventValueDescription>();

            foreach (string desc in descriptions)
            {
                Match m = PATTERN_DESCRIPTION.Match(desc);
                if (m.Success)
                {
                    try
                    {
                        string name = m.Groups[1].Value;
                        string typeString = m.Groups[2].Value;
                        int typeValue = int.Parse(typeString);
                        EventValueType eventValueType = (EventValueType)typeValue;

                        typeString = m.Groups[3].Value;
                        if (!string.IsNullOrEmpty(typeString))
                        {
                            //skip the |
                            typeString = typeString.Substring(1);

                            typeValue = int.Parse(typeString);
                            ValueType valueType = (ValueType)typeValue;

                            list.Add(new EventValueDescription(name, eventValueType, valueType));
                        }
                        else
                        {
                            list.Add(new EventValueDescription(name, eventValueType));
                        }
                    }
                    catch (FormatException)
                    {
                        // just ignore this description if one number is malformed.
                        // TODO: log the error.
                    }
                    catch (Exception)
                    {
                        // just ignore this description if data type and data unit don't match
                        // TODO: log the error.
                    }
                }
            }
            
            return list.Count == 0 ? null : list.ToArray();
        }

        /// <summary>
        /// Recursively convert binary log data to printable form.
        /// 
        /// This needs to be recursive because you can have lists of lists.
        /// 
        /// If we run out of room, we stop processing immediately.  It's important
        /// for us to check for space on every output element to avoid producing
        /// garbled output.
        /// 
        /// </summary>
        /// <param name="eventData">Raw data</param>
        /// <param name="dataOffset">Raw data offset</param>
        /// <param name="list">List in which to parse the data</param>
        /// <returns>Returns the amount read on success, -1 on failure.</returns>
        private int ParseBinaryEvent(byte[] eventData, int dataOffset, List<object> list)
        {
            if ((eventData.Length - dataOffset) < 1)
                return -1;

            int offset = dataOffset;

            int type = eventData[offset++];

            switch (type)
            {
                case EVENT_TYPE_INT:
                    { /* 32-bit signed int */
                        if ((eventData.Length - offset) < 4)
                            return -1;
                        int ival = BitConverter.ToInt32(eventData, offset);
                        offset += 4;

                        list.Add(ival);
                    }
                    break;
                case EVENT_TYPE_LONG:
                    { /* 64-bit signed long */
                        if ((eventData.Length) - offset < 8)
                            return -1;
                        long lval = BitConverter.ToInt64(eventData, offset);
                        offset += 8;
                        list.Add(lval);
                    }
                    break;
                case EVENT_TYPE_STRING:
                    { /* UTF-8 chars, not NULL-terminated */
                        if ((eventData.Length - offset) < 4)
                            return -1;
                        int strLen = BitConverter.ToInt32(eventData, offset);
                        offset += 4;

                        if ((eventData.Length - offset) < strLen)
                            return -1;

                        // get the string
                        try
                        {
                            string str = Encoding.GetEncoding("UTF-8").GetString(eventData, offset, strLen); //$NON-NLS-1$
                            list.Add(str);
                        }
                        catch (Exception) { }
                        offset += strLen;
                        break;
                    }
                case EVENT_TYPE_LIST:
                    { /* N items, all different types */

                        if ((eventData.Length - offset) < 1)
                            return -1;

                        int count = eventData[offset++];

                        // make a new temp list
                        List<object> subList = new List<object>();
                        for (int i = 0; i < count; i++)
                        {
                            int result = ParseBinaryEvent(eventData, offset, subList);
                            if (result == -1)
                            {
                                return result;
                            }

                            offset += result;
                        }

                        list.AddRange(subList);
                    }
                    break;
                default:
                    return -1;
            }

            return offset - dataOffset;
        }

        /// <summary>
        /// Parses the event container data from LogEntry instance
        /// </summary>
        /// <param name="entry">LogEntry instance from wwhich to parse</param>
        /// <returns>EventContainer instance</returns>
        public EventContainer Parse(LogEntry entry)
        {
            if (entry.Length < 4)
            {
                return null;
            }

            int inOffset = 0;

            int tagValue = BitConverter.ToInt32(entry.Data, inOffset);
            inOffset += 4;
            
            string tagName = mTagMap.ContainsKey(tagValue) ? tagName = mTagMap[tagValue] : tagValue.ToString();

            List<object> list = new List<object>();
            if (ParseBinaryEvent(entry.Data, inOffset, list) == -1)
            {
                return null;
            }

            object data = list.Count == 1 ? list[0] : list.ToArray();

            return (tagValue == GcEventContainer.GC_EVENT_TAG) ? new GcEventContainer(entry, tagValue, tagName, data) :
                new EventContainer(entry, tagValue, tagName, data);
        }
    }
}
