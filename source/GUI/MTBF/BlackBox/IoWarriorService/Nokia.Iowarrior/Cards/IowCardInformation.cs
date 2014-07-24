using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Iowarrior
{
    /// <summary>
    /// Provides assembly-wide zero-based named counters.
    /// </summary>
    internal static class NamedCountersSingleton
    {
        private static Dictionary<String, Int32> namedCountersDictionary = new Dictionary<string, int>();

        /// <summary>
        /// Get next value for given named counter.
        /// </summary>
        /// <param name="counterName">Name of the counter.</param>
        /// <returns>Next value (increments by 1).</returns>
        public static Int32 GetNext(String counterName)
        {
            lock (namedCountersDictionary)
            {
                // Increment, if existing
                if (namedCountersDictionary.ContainsKey(counterName))
                    namedCountersDictionary[counterName]++;
                else
                    namedCountersDictionary[counterName] = 0;

                return namedCountersDictionary[counterName];
            }
        }

        /// <summary>
        /// Clears given counter by removing it from the known named counters collection.
        /// </summary>
        /// <param name="counterName">Name of the counter.</param>
        internal static void Clear(String counterName)
        {
            lock (namedCountersDictionary)
            {
                if (namedCountersDictionary.ContainsKey(counterName))
                    namedCountersDictionary.Remove(counterName);
            }
        }

        /// <summary>
        /// Clears all counters by emptying the named counters collection.
        /// </summary>
        internal static void Clear()
        {
            lock (namedCountersDictionary)
            {
                namedCountersDictionary.Clear();
            }
        }
    }

    /// <summary>
    /// This class implements a container for all relevant information to identify a given IowCard.
    /// </summary>
    public sealed class IowCardInformation
    {
        /// <summary>
        /// Numeric type identifier of this card read from the card's hardware.
        /// </summary>
        public Int32 CardType { get { return cardType; } set { cardType = value; } }
        private Int32 cardType;     // will be read from the card later.

        /// <summary>
        /// Numeric sub-type of the card read from the card's hardware.
        /// </summary>
        public Int32 CardSubtype { get { return cardSubtype; } set { cardSubtype = value; } }
        private Int32 cardSubtype;  // will be read from the card later.

        /// <summary>
        /// Serial number read from the card. If none is specified in EEprom, Iowarrior serial number is used.
        /// </summary>
        public String SerialNumber
        {
            get
            {
                if (serialNumber == null)
                    return "HASH" + this.GetHashCode().ToString("X");
                else
                    return serialNumber;
            }
            set
            {
                serialNumber = value;
            }
        }

        private String serialNumber;    // of the card, not the one of the Iowarrior device

        /// <summary>
        /// Hardware revision of this card.
        /// </summary>
        public Int32 HardwareRevision { get { return hardwareRevision; } set { hardwareRevision = value; } }
        private Int32 hardwareRevision;

        /// <summary>
        /// Logical name for this card. Useful for readability.
        /// </summary>
        public String LogicalName { get { return logicalName; } set { logicalName = value; } }
        private String logicalName;     // logical name of this card

        /// <summary>
        /// Name of the product this card is made for. Leave "" for generic cards.
        /// </summary>
        public String ProductName { get { return productName; } set { productName = value; } }
        private String productName = ""; // will be read from EEPROM later

        /// <summary>
        /// Get the index of this card for cards with the same type.
        /// </summary>
        public Int32 Index { get { return iowCardIndex; } set { iowCardIndex = value; } }
        private Int32 iowCardIndex;

        /// <summary>
        /// Get an identifier combined from CardType, CardSubtype and HardwareRevision.
        /// </summary>
        public Int32 CardId
        {
            get { return (CardType << 20) + (CardSubtype << 4) + HardwareRevision; }
        }

        /// <summary>
        /// Construct empty IowCardType object.
        /// Property serialNumber is the hash code of the object.
        /// Property accessMethod is unknown.
        /// The other properties are 0 or "".
        /// </summary>
        public IowCardInformation()
        {
            serialNumber = "HASH" + GetType().GetHashCode().ToString("X");
            productName = "";
        }

        /// <summary>
        /// Returns System.String representation of this object instance.
        /// </summary>
        /// <returns>System.String representation of this object instance.</returns>
        public override String ToString()
        {
            StringBuilder sb = new StringBuilder();

            sb.Append(this.GetType().Name);
            sb.Append("[");
            sb.AppendFormat("CardName=\"{0}\"", LogicalName);
            sb.AppendFormat(", ProductName=\"{0}\"", ProductName);
            sb.AppendFormat(", Index={0}", Index);
            sb.AppendFormat(", CardType=0x{0}", CardType.ToString("X"));
            sb.AppendFormat(", CardSubtype=0x{0}", CardSubtype.ToString("X"));
            sb.AppendFormat(", Revision={0}", HardwareRevision);
            sb.AppendFormat(", SerialNumber={0}", SerialNumber);
            sb.Append("]");
            return sb.ToString();
        }
    };
}
