using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Iowarrior.Cards
{
    /// <summary>
    /// IMPORTANT: This is the one and only place to add new supported IowCards.
    /// </summary>
    public static class IowSupportedCardTypes
    {
        /// <summary>
        /// Initializes all cards in the dictionary before first access.
        /// All cards are in Dummy mode, hence the time of initialization is not critical.
        /// </summary>
        static IowSupportedCardTypes()
        {
            // BEGIN ADDING SUPPORTED CARD CLASSES: cards[cardId] = new Cards.CardClass();
            // The index is calculated according to this formula:
            // (CardType<<20) + (CardSubtype<<4) + HardwareRevision

            cards[  (0 << 20) + (0000 << 4) + 00] = new Cards.IowCardUnknown();          // Id==0 => unknown card!!
            cards[  (1 << 20) + (0000 << 4) + 00] = new Cards.IowCardMatrix_5x6();
            cards[  (2 << 20) + (0000 << 4) + 00] = new Cards.IowCardMatrix2_5x6();
            cards[  (6 << 20) + (0000 << 4) + 00] = new Cards.IowCardBsiSimSwitch();
            cards[  (6 << 20) + (0000 << 4) + 01] = new Cards.IowCardBsiSimSwitchV1();
            cards[ (12 << 20) + (0000 << 4) + 00] = new Cards.IowCardAudio();
            cards[ (16 << 20) + (0000 << 4) + 00] = new Cards.IowCardAccessory();
            cards[ (21 << 20) + (0000 << 4) + 00] = new Cards.IowCardCharger();
            cards[ (22 << 20) + (0000 << 4) + 00] = new Cards.IowCardChargerWithBattery();            
            cards[ (26 << 20) + (0000 << 4) + 00] = new Cards.IowCardMatrix_4x7();
            cards[ (28 << 20) + (0000 << 4) + 00] = new Cards.IowCardMatrix2_4x7();
            cards[ (31 << 20) + (0000 << 4) + 00] = new Cards.IowCardUniSwitch();            
            cards[ (41 << 20) + (0000 << 4) + 00] = new Cards.IowCardFlash();
            cards[ (46 << 20) + (0000 << 4) + 00] = new Cards.IowCardSim();
            cards[ (51 << 20) + (0000 << 4) + 00] = new Cards.IowCardCapacitiveKeys();
            cards[ (66 << 20) + (0000 << 4) + 00] = new Cards.IowCardTouchRC();            
            cards[ (69 << 20) + (0000 << 4) + 00] = new Cards.IowCarduSDSwitch();
            cards[ (70 << 20) + (0000 << 4) + 00] = new Cards.IowCardMatrix_16x16();
            cards[ (73 << 20) + (0000 << 4) + 00] = new Cards.IowCardUSBAccessory();
            cards[ (74 << 20) + (0000 << 4) + 00] = new Cards.IowCardChargerWithBatteryV2();
            cards[(255 << 20) + (0000 << 4) + 00] = new Cards.IowCardExperimental();

            // cards with ID >=10000000 are not ready yet

            // END ADDING SUPPORTED CARD CLASSES
            // DO NOT CHANGE ANY CODE BELOW!
        }

        /// <summary>
        /// Just add an instance of any supported card type in this dictionary in the static constructor above.
        /// </summary>
        private static Dictionary<Int32, IowCard> cards = new Dictionary<int, IowCard>();

        /// <summary>
        /// Get a collection of all available card implementations.
        /// </summary>
        public static ICollection<IowCard> Cards
        {
            get { return cards.Values; }
        }

        /// <summary>
        /// Get the Id of a given IowCard object.
        /// </summary>
        /// <param name="iowCard">Reference to IowCard.</param>
        /// <returns>CardId of the given card or 0, if unknown.</returns>
        internal static Int32 GetIdOfIowCard(IowCard iowCard)
        {
            foreach (Int32 id in cards.Keys)
            {
                if (cards[id].GetType() == iowCard.GetType())
                    return id;
            }

            // ID=0 indicates unknown card.
            return 0;
        }
    }
}
