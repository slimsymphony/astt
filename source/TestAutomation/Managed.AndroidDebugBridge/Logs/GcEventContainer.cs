using Managed.Adb.Logs;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Managed.Adb.Logs
{
    /// <summary>
    /// Custom Event Container for the Gc event since this event doesn't simply output data in
    /// int or long format, but encodes several values on 4 longs.
    /// 
    /// The array of EventValueDescriptions parsed from the "event-log-tags" file must
    /// be ignored, and instead, the array returned from #getValueDescriptions() must be used.
    /// 
    /// sdk/ddms/libs/ddmlib/src/com/android/ddmlib/log/GcEventContainer.java
    /// </summary>
    [Serializable]
    public class GcEventContainer : EventContainer
    {
        /// <summary>
        /// Tag number for GC events
        /// </summary>
        public const int GC_EVENT_TAG = 20001;

        private string processId;
        private long gcTime;
        private long bytesFreed;
        private long objectsFreed;
        private long actualSize;
        private long allowedSize;
        private long softLimit;
        private long objectsAllocated;
        private long bytesAllocated;
        private long zActualSize;
        private long zAllowedSize;
        private long zObjectsAllocated;
        private long zBytesAllocated;
        private long dlmallocFootprint;
        private long mallinfoTotalAllocatedSpace;
        private long externalLimit;
        private long externalBytesAllocated;

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="entry">LogEntry from in which the event data is stored</param>
        /// <param name="tag">Numeric tag of the event</param>
        /// <param name="tagName">Readable tag of the event</param>
        /// <param name="data">Event data</param>
        public GcEventContainer(LogEntry entry, int tag, string tagName, object data) : 
            base(entry, tag, tagName, data)
        {
            Init(data);
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
        public GcEventContainer(int tag, string tagName, int pid, int tid, int sec, int nsec, object data) :
            base(tag, tagName, pid, tid, sec, nsec, data)
        {
            Init(data);
        }

        /// <summary>
        /// Inits the instance
        /// </summary>
        /// <param name="data">Event data</param>
        private void Init(object data) 
        {
            if (data is object[]) {
                object[] values = (object[])data;
                for (int i = 0; i < values.Length; i++) {
                    if (values[i] is long) {
                        ParseDvmHeapInfo((long)values[i], i);
                    }
                }
            }
        }

        /// <summary>
        /// Gets the event value type of the data
        /// </summary>
        public override EventValueType EventValueType
        {
            get
            {
                return EventValueType.LIST;
            }
        }

        /// <summary>
        /// Gets a value from index: presuming the type of the data intance is a collection
        /// </summary>
        /// <param name="valueIndex">Index from which the read the data</param>
        /// <returns>Object in the given instance</returns>
        public override object GetValue(int valueIndex)
        {
            if (valueIndex == 0)
            {
                return processId;
            }

            try
            {
                return GetValueAsLong(valueIndex);
            }
            catch (Exception)
            {
                // this would only happened if valueIndex was 0, which we test above.
            }

            return null;
        }

        /// <summary>
        /// Gets a value from index: presuming the type of the data intance is a collection
        /// </summary>
        /// <param name="valueIndex">Index from which the read the data</param>
        /// <returns>Double value in the given instance</returns>
        public override double GetValueAsDouble(int valueIndex)
        {
            return (double)GetValueAsLong(valueIndex);
        }

        /// <summary>
        /// Gets a value from index: presuming the type of the data intance is a collection
        /// </summary>
        /// <param name="valueIndex">Index from which the read the data</param>
        /// <returns>String value in the given instance</returns>
        public override string GetValueAsString(int valueIndex)
        {
            switch (valueIndex)
            {
                case 0:
                    return processId;
                default:
                    {
                        try
                        {
                            return GetValueAsLong(valueIndex).ToString();
                        }
                        catch (Exception)
                        {
                            // we shouldn't stop there since we test, in this method first.
                        }
                    }
                    break;
            }

            throw new ArgumentOutOfRangeException();
        }

        /// <summary>
        /// Gets a value from a given index
        /// </summary>
        /// <param name="valueIndex">Index from which to check the value</param>
        /// <returns>Value from a given index</returns>
        private long GetValueAsLong(int valueIndex)
        {
            switch (valueIndex) 
            {
                case 0:
                    throw new InvalidCastException();
                case 1:
                    return gcTime;
                case 2:
                    return objectsFreed;
                case 3:
                    return bytesFreed;
                case 4:
                    return softLimit;
                case 5:
                    return actualSize;
                case 6:
                    return allowedSize;
                case 7:
                    return objectsAllocated;
                case 8:
                    return bytesAllocated;
                case 9:
                    return actualSize - zActualSize;
                case 10:
                    return allowedSize - zAllowedSize;
                case 11:
                    return objectsAllocated - zObjectsAllocated;
                case 12:
                    return bytesAllocated - zBytesAllocated;
                case 13:
                   return zActualSize;
                case 14:
                    return zAllowedSize;
                case 15:
                    return zObjectsAllocated;
                case 16:
                    return zBytesAllocated;
                case 17:
                    return externalLimit;
                case 18:
                    return externalBytesAllocated;
                case 19:
                    return dlmallocFootprint;
                case 20:
                    return mallinfoTotalAllocatedSpace;
            }

            throw new ArgumentOutOfRangeException();
        }

        /// <summary>
        /// Returns a custom array of EventValueDescription since the actual content of this
        /// event (list of (long, long) does not match the values encoded into those longs.
        /// </summary>
        public static EventValueDescription[] ValueDescriptions
        {
            get
            {
                try
                {
                    return new EventValueDescription[] {
                        new EventValueDescription("Process Name", EventValueType.STRING),
                        new EventValueDescription("GC Time", EventValueType.LONG, ValueType.MILLISECONDS),
                        new EventValueDescription("Freed Objects", EventValueType.LONG, ValueType.OBJECTS),
                        new EventValueDescription("Freed Bytes", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("Soft Limit", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("Actual Size (aggregate)", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("Allowed Size (aggregate)", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("Allocated Objects (aggregate)", EventValueType.LONG, ValueType.OBJECTS),
                        new EventValueDescription("Allocated Bytes (aggregate)", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("Actual Size", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("Allowed Size", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("Allocated Objects", EventValueType.LONG, ValueType.OBJECTS),
                        new EventValueDescription("Allocated Bytes", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("Actual Size (zygote)", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("Allowed Size (zygote)", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("Allocated Objects (zygote)", EventValueType.LONG, ValueType.OBJECTS),
                        new EventValueDescription("Allocated Bytes (zygote)", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("External Allocation Limit", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("External Bytes Allocated", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("dlmalloc Footprint", EventValueType.LONG, ValueType.BYTES),
                        new EventValueDescription("Malloc Info: Total Allocated Space", EventValueType.LONG, ValueType.BYTES),
                    };
                }
                catch (InvalidCastException)
                {
                    // this shouldn't happen since we control manual the EventValueType and the ValueType
                    // values. For development purpose, we assert if this happens.
                }

                // this shouldn't happen, but the compiler complains otherwise.
                return null;
            }
        }

        /// <summary>
        /// Formats an object to its string presentation
        /// </summary>
        /// <param name="obj">Object to format</param>
        /// <returns>String presentation of an object</returns>
        protected override string ObjectToString(object obj)
        {
            var list = new List<object>();
            list.Add(processId);
            for (int i = 1; i < 20; i++)
            {
                list.Add(GetValueAsLong(i));
            }
            return base.ObjectToString(list.ToArray());
        }

        /// <summary>
        /// Formats the instance to its string presentation
        /// </summary>
        /// <returns>String presentation of the instance</returns>
        public override string ToString()
        {
            return ObjectToString(null);
        }

        /// <summary>
        /// Parses Dvm heap info
        /// </summary>
        /// <param name="data"></param>
        /// <param name="index"></param>
        private void ParseDvmHeapInfo(long data, int index)
        {
            switch (index)
            {
                case 0:
                    //    [63   ] Must be zero
                    //    [62-24] ASCII process identifier
                    //    [23-12] GC time in ms
                    //    [11- 0] Bytes freed

                    gcTime = Float12ToInt((int)((data >> 12) & 0xFFFL));
                    bytesFreed = Float12ToInt((int)(data & 0xFFFL));

                    // convert the long into an array, in the proper order so that we can convert the
                    // first 5 char into a string.
                    byte[] dataArray = Put64bitsToArray(data);

                    // get the name from the string
                    processId = Encoding.Default.GetString(dataArray, 0, 5);
                    break;
                case 1:
                    //    [63-62] 10
                    //    [61-60] Reserved; must be zero
                    //    [59-48] Objects freed
                    //    [47-36] Actual size (current footprint)
                    //    [35-24] Allowed size (current hard max)
                    //    [23-12] Objects allocated
                    //    [11- 0] Bytes allocated
                    objectsFreed = Float12ToInt((int)((data >> 48) & 0xFFFL));
                    actualSize = Float12ToInt((int)((data >> 36) & 0xFFFL));
                    allowedSize = Float12ToInt((int)((data >> 24) & 0xFFFL));
                    objectsAllocated = Float12ToInt((int)((data >> 12) & 0xFFFL));
                    bytesAllocated = Float12ToInt((int)(data & 0xFFFL));
                    break;
                case 2:
                    //    [63-62] 11
                    //    [61-60] Reserved; must be zero
                    //    [59-48] Soft limit (current soft max)
                    //    [47-36] Actual size (current footprint)
                    //    [35-24] Allowed size (current hard max)
                    //    [23-12] Objects allocated
                    //    [11- 0] Bytes allocated
                    softLimit = Float12ToInt((int)((data >> 48) & 0xFFFL));
                    zActualSize = Float12ToInt((int)((data >> 36) & 0xFFFL));
                    zAllowedSize = Float12ToInt((int)((data >> 24) & 0xFFFL));
                    zObjectsAllocated = Float12ToInt((int)((data >> 12) & 0xFFFL));
                    zBytesAllocated = Float12ToInt((int)(data & 0xFFFL));
                    break;
                case 3:
                    //    [63-48] Reserved; must be zero
                    //    [47-36] dlmallocFootprint
                    //    [35-24] mallinfo: total allocated space
                    //    [23-12] External byte limit
                    //    [11- 0] External bytes allocated
                    dlmallocFootprint = Float12ToInt((int)((data >> 36) & 0xFFFL));
                    mallinfoTotalAllocatedSpace = Float12ToInt((int)((data >> 24) & 0xFFFL));
                    externalLimit = Float12ToInt((int)((data >> 12) & 0xFFFL));
                    externalBytesAllocated = Float12ToInt((int)(data & 0xFFFL));
                    break;
                default:
                    break;
            }
        }

        /// <summary>
        /// Converts a 12 bit float representation into an unsigned int (returned as a long)
        /// </summary>
        /// <param name="f12"></param>
        /// <returns></returns>
        private static long Float12ToInt(int f12) {
            return (f12 & 0x1ff) << ((f12 >> 9) * 4);
        }

        /// <summary>
        /// Puts an unsigned value in an array
        /// </summary>
        /// <param name="value">The value to put</param>
        /// <returns></returns>
        private static byte[] Put64bitsToArray(long value)
        {
            var array = BitConverter.GetBytes(value);
            Array.Reverse(array);
            return array;
        }
    }
}
