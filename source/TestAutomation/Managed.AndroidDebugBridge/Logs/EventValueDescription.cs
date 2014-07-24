using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Managed.Adb.Logs
{
    /// <summary>
    /// Represents the type of a numerical value. This is used to display values of vastly different
    /// type/range in graphs.
    /// </summary>
    public enum ValueType
    {
        /// <summary>
        /// Value type is not applicable
        /// </summary>
        NOT_APPLICABLE = 0,
        
        /// <summary>
        /// Value type is objects
        /// </summary>
        OBJECTS = 1,
        
        /// <summary>
        /// Value type is bytes
        /// </summary>
        BYTES = 2,
        
        /// <summary>
        /// Value type is milliseconds
        /// </summary>
        MILLISECONDS = 3,
        
        /// <summary>
        /// Value type is allocations
        /// </summary>
        ALLOCATIONS = 4,
        
        /// <summary>
        /// Value type is ID
        /// </summary>
        ID = 5,
        
        /// <summary>
        /// Value type is percent
        /// </summary>
        PERCENT = 6,
    }

    /// <summary>
    /// Extension class for extending the ValueType enum
    /// </summary>
    [Serializable]
    public static class ValueTypeMethods
    {
        /// <summary>
        /// Checks that the EventValueType is compatible with the ValueType
        /// </summary>
        /// <param name="vt">Value type</param>
        /// <param name="type">Event value type</param>
        /// <exception cref="ArgumentException">If the types are not compatible</exception>
        public static void CheckType(this ValueType vt, EventValueType type)
        {
            if ((type != EventValueType.INT && type != EventValueType.LONG)
                && vt != ValueType.NOT_APPLICABLE)
            {
                throw new ArgumentException(string.Format("{0} doesn't support type {1}", type, vt));
            }
        }
    }

    /// <summary>
    /// Describes an EventContainer value.
    /// This is a stand-alone object, not linked to a particular Event. It describes the value, by
    /// name, type EventValueType, and (if needed) value unit ValueType.
    /// 
    /// The index of the value is not contained within this class, and is instead dependent on the
    /// index of this particular object in the array of EventValueDescription returned by
    /// EventLogParser#ValueDescriptionMap when queried for a particular event tag.
    /// 
    /// sdk/ddms/libs/ddmlib/src/com/android/ddmlib/log/EventValueDescription.java
    /// </summary>
    [Serializable]
    public class EventValueDescription
    {
        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="name">Name of the event</param>
        /// <param name="type">Type of the event value</param>
        public EventValueDescription(string name, EventValueType type)
        {
            Name = name;
            EventValueType = type;
            ValueType = (EventValueType == EventValueType.INT || EventValueType == EventValueType.LONG) ? 
                ValueType.BYTES : ValueType.NOT_APPLICABLE;
        }

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="name">Name of the event</param>
        /// <param name="type">Type of the event value</param>
        /// <param name="valueType">Type of the value</param>
        public EventValueDescription(string name, EventValueType type, ValueType valueType)
        {
            Name = name;
            EventValueType = type;
            ValueType = valueType;
            ValueType.CheckType(EventValueType);
        }

        /// <summary>
        /// Gets the name of the event description
        /// </summary>
        public string Name { get; private set; }

        /// <summary>
        /// Gets the event value type
        /// </summary>
        public EventValueType EventValueType { get; private set; }

        /// <summary>
        /// Gets the value type
        /// </summary>
        public ValueType ValueType { get; private set; }

        /// <summary>
        /// Formats the object to its string presentation
        /// </summary>
        /// <returns>Sting presentation of the object</returns>
        public override string ToString()
        {
            if (ValueType != ValueType.NOT_APPLICABLE)
            {
                return string.Format("{0} ({1}, {2})", Name, EventValueType.ToString().ToLower(), ValueType.ToString().ToLower());
            }

            return string.Format("{0} ({1})", Name, EventValueType.ToString());
        }

        /// <summary>
        /// Check the type agains the event value type
        /// </summary>
        /// <param name="value">Object which to check</param>
        /// <returns>True if match; false otherwise</returns>
        public bool CheckForType(object value) 
        {
            switch (EventValueType) 
            {
                case EventValueType.INT:
                    return value is int;
                case EventValueType.LONG:
                    return value is long;
                case EventValueType.STRING:
                    return value is string;
                case EventValueType.LIST:
                    return value is object[];
            }

            return false;
        }

        /// <summary>
        /// Gets the object from string
        /// </summary>
        /// <param name="value">String presentatation of the object</param>
        /// <returns>Object with type of: int, long, or string</returns>
        public object GetObjectFromString(string value)
        {
            switch (EventValueType)
            {
                case EventValueType.INT:
                    try
                    {
                        return int.Parse(value);
                    }
                    catch (FormatException)
                    {
                        return null;
                    }
                case EventValueType.LONG:
                    try
                    {
                        return long.Parse(value);
                    }
                    catch (FormatException)
                    {
                        return null;
                    }
                case EventValueType.STRING:
                    return value;
            }

            return null;
        }
    }
}
