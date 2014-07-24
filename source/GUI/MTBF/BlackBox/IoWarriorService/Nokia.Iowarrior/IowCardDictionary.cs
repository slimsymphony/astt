using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using System.Reflection;
using System.Threading;
using System.Diagnostics;
using Nokia.Iowarrior;
using Nokia.Iowarrior.Cards;

namespace Nokia.Iowarrior
{
    /// <summary>
    /// This class implements a Dictionary&lt;String, IowCard&gt; about all connected IowCards.
    /// Each element can be accessed using the serial number of its main Iowarrior device
    /// or the card's logical name (if set).
    /// Generally, all methods throw an exception if they cannot do what they are intended to do.
    /// </summary>
    public class IowCardDictionary : Dictionary<String, IowCard>
    {
        private Dictionary<String, Int32> indexCounter = new Dictionary<string, int>();
        IowDeviceDictionary iowDeviceDictionary;

        XmlDocument klf;
        bool klfLoaded = false;
        Hashtable keyRelayC, keyRelayO, softRelay;

        //Nokia.Tea.Rcms.TypeInterfaces.TouchController.IRcmTouchController touchClient = null;
        //Process touchProc = null;

        /// <summary>
        /// Creates a new, empty instance of IowCardDictionary.
        /// </summary>
        public IowCardDictionary() { }

        /// <summary>
        /// Create new instance of IowCardDictionary. If <paramref name="refresh"/> is true, it will probe for attached cards.
        /// </summary>
        /// <param name="refresh">If true, the constructor will fill the dictionary by calling Refresh().</param>
        public IowCardDictionary(Boolean refresh, string layoutFile = "")
        {
            if (refresh)
                Refresh(true);

            readKeyboardLayoutFile(layoutFile);
        }

        /// <summary>
        /// Create new instance of IowCardDictionary using already existing IowDeviceDictionary.
        /// </summary>
        /// <param name="iowDeviceDictionary">Reference to IowDeviceDictionary to use.</param>
        public IowCardDictionary (IowDeviceDictionary iowDeviceDictionary, string layoutFile = "")
        {
            if (iowDeviceDictionary == null)
            {
                throw new ArgumentNullException("iowDeviceDictionary");
            }

            this.iowDeviceDictionary = iowDeviceDictionary;
            Refresh(false);

            readKeyboardLayoutFile(layoutFile);
        }

        /// <summary>
        /// reads in the keyboardLayoutfile
        /// </summary>
        /// <param name="keyLayoutFile">name of the file.</param>
        /// /// <returns>true if successfull, otherwise false.</returns>
        public bool readKeyboardLayoutFile (string keyLayoutFile = "")
        {
            //read out keyboard layout file if possible
            klfLoaded = false;
            keyRelayC = new Hashtable(); keyRelayO = new Hashtable();
            softRelay = new Hashtable();
            if (keyLayoutFile.Length > 0 && System.IO.File.Exists(keyLayoutFile)) {
                klf = new XmlDocument();
                klf.Load(keyLayoutFile);
                IowCard[] cs = GetCards();
                //check the cards and rename
                foreach (XmlNode n in klf.SelectNodes("/keyboardLayoutFile/cards/*"))
                    for (int i = 0; i < this.Count; i++)
                        if (cs[i].IowCardInfo.SerialNumber.Equals(n.Attributes["id"].Value))
                            Rename(cs[i].CardName, n.SelectSingleNode("alias").InnerText);
                klfLoaded = true;
                return loadKeyboardChapter("global"); ;
            }
            return false;
        }

        /// <summary>
        /// reads in the keyboardLayoutfile chapter
        /// </summary>
        /// <param name="chapter">name of the chapter.</param>
        /// /// <returns>true if successfull, otherwise false.</returns>
        public bool loadKeyboardChapter (string chapter)
        {
            if (klfLoaded && klf.SelectNodes("/keyboardLayoutFile/keys/" + chapter + "/*").Count > 0) {
                string rel, kn = "", prefixC, prefixO;

                foreach (XmlNode n in klf.SelectNodes("/keyboardLayoutFile/keys/" + chapter + "/*"))
                    if (n.SelectSingleNode("relay") != null) {
                        rel = n.SelectSingleNode("relay").InnerText;
                        if (Regex.IsMatch(rel, @"^(r\d/c\d)|func_r|gnd_rel(10|[0-9])|navi_[lmr]|pwronx|arrow(up|down|left|right)|select$")) {
                            prefixC = "close:key=" + rel;
                            prefixO = "open:key=" + rel;
                        }
                        else if (Regex.IsMatch(rel, @"^uni=\d{1,2}|flash(=(all|[123456789]|10))?|sim=([0123456]|none)|emag|discharge$")) {
                            prefixC = "close:" + rel;
                            prefixO = "open:" + rel;
                        }
                        else if (Regex.IsMatch(rel, @"^charger=\d|acc(1|2)=\d{1,2}|(mmc|usb|av)=([01234abcd]|none)|bsi(=(battery|((normal|local|test)(_lynx|_tabby)?)))?|battery|fps|cap|power$")) {
                            prefixC = "connect:" + rel;
                            prefixO = "disconnect:" + rel;
                        }
                        else
                            prefixC = prefixO = ("" + rel);

                        if (n.SelectSingleNode("card") != null) {
                            prefixC += (":name=" + n.SelectSingleNode("card").InnerText);
                            prefixO += (":name=" + n.SelectSingleNode("card").InnerText);
                        }
                        foreach (string nms in n.Attributes["name"].Value.Split(',')) {
                            kn = nms.Trim();
                            if (keyRelayC.ContainsKey(kn)) {
                                keyRelayC.Remove(kn);
                                keyRelayO.Remove(kn);
                            }
                            keyRelayC.Add(kn, prefixC);
                            keyRelayO.Add(kn, prefixO);
                        }

                        if (n.SelectSingleNode("soft") != null) {
                            rel = n.SelectSingleNode("relay").InnerText;
                            if (!softRelay.ContainsKey(rel))
                                softRelay.Add(rel, kn);
                        }
                    }
                return true;
            }
            return false;
        }

        ///// <summary>
        ///// initializes TouchHostTea.exe.
        ///// </summary>
        //public void initTouch (int defaultSpeed = 80)
        //{
        //    if (touchClient != null)
        //        try {
        //            touchProc.CloseMainWindow();
        //            touchProc.Dispose();
        //        }
        //        catch { }

        //    ProcessStartInfo psi = new ProcessStartInfo(Environment.CurrentDirectory + "\\touchHW\\TouchHostTea.exe");
        //    psi.WorkingDirectory = Environment.CurrentDirectory + "\\touchHW";
        //    touchProc = Process.Start(psi);
        //    touchClient = Touch.TouchControllerFactory.CreateInstance();
        //    touchClient.DefaultSpeed = defaultSpeed;
        //}

        ///// <summary>
        ///// touch something.
        ///// </summary>
        //public void touch (string parameters)
        //{
        //    touchClient.Touch(parameters);
        //}


        /// <summary>
        /// Get a list of all supported card type names.
        /// </summary>
        /// <returns>String list of all supported card type name.</returns>
        public static IList<String> GetSupportedCards()
        {
            List<String> l = new List<String>();

            foreach (IowCard c in IowSupportedCardTypes.Cards)
                l.Add(c.CardTypeName);

            return l;
        }

        /// <summary>
        /// Get an IDictionary&lt;String, ICollection&lt;String&gt;&gt; of all commands of all cards supported by Iowarrior.Net.
        /// Card type name is the key (see <seealso cref="GetSupportedCards()"/>) and the value is a list with all commands supported by this card type.
        /// </summary>
        /// <returns>Dictionary filled with card type names and their commands.</returns>
        public static IDictionary<String, ICollection<String>> GetSupportedCommands()
        {
            SortedList<String, ICollection<String>> list = new SortedList<string, ICollection<string>>();
            foreach (IowCard c in IowSupportedCardTypes.Cards)
                list.Add(c.CardTypeName, c.KnownCommands);
            return list;
        }

        /// <summary>
        /// <para>
        /// Get all commands supported by all the cards contained in this dictionary, i.e. currently being connected to the PC.
        /// There are two options:
        /// </para>
        /// <para>withCardName=true: The list contains all card names, i.e. every command in this list addresses a unique card.</para>
        /// <para>withCardName=false: The list does not contain the card names.</para>
        /// </summary>
        /// <param name="withCardName">If true, commands contain a name field filled with the card's name.</param>
        /// <returns>Collection of commands.</returns>
        public ICollection<String> GetAllCommands(Boolean withCardName)
        {
            List<String> result = new List<String>();

            foreach (IowCard card in Values)
                foreach (String cmd in card.KnownCommands)
                    if (withCardName)
                        result.Add(String.Format("{0}:name={1}", cmd, card.CardName));
                    else if (!result.Contains(cmd))
                        result.Add(cmd);

            return result;
        }

        /// <summary>
        /// Return the number of known cards of the given card type.
        /// </summary>
        /// <param name="cardType">Card type to check.</param>
        /// <returns>Number of cards of this type.</returns>
        public Int32 CountCards(String cardType)
        {
            // Card type exists, if an indexCounter entry has been created for it.
            if (indexCounter.ContainsKey(cardType))
                return indexCounter[cardType];
            else
                return 0;
        }

        /// <summary>
        /// Updates the contents of the card dictionary according to the connected devices.
        /// It contains one instance of an IowCard-based object for each detected Iowarrior card.
        /// Note: The number of cards must not necessarily match with the number of Iowarrior devices.
        /// </summary>
        /// <param name="refreshDeviceDictionary">true to refresh the device dictionary.</param>
        /// <returns>IowCardDictionary with instances of subclasses of IowCard.</returns>
        private IowCardDictionary Refresh(Boolean refreshDeviceDictionary)
        {
            if (refreshDeviceDictionary)
                iowDeviceDictionary = new IowDeviceDictionary(true);

            indexCounter.Clear();

            // Get information from all devices.
            foreach (IowDevice iow in iowDeviceDictionary.Values) {
                IowCardInformation iowCardInfo = new IowCardInformation();
                iowCardInfo.SerialNumber = iow.SerialNumber;

                try {
                    iowCardInfo = IowCard.ReadCardInformation(iow);
                }
                catch {
                    // Could not read card info => add it as "invalid card".
                    IowCard newCard = new Cards.IowCardInvalid(iow, 0, iowCardInfo);
                    Add(newCard.CardName, newCard);
                    continue;
                }

                Boolean isSupported;

                // Add all found cards according to information stored in
                // IowSupportedCardTypes to the card dictionary.
                // If card is already known: no action.

                Boolean isKnown = false;
                foreach (IowCard c in Values)
                    if (c.IowDevice.SerialNumber == iow.SerialNumber) {
                        isKnown = true;
                        if (indexCounter.ContainsKey(c.GetType().Name))
                            indexCounter[c.GetType().Name]++;
                        else
                            indexCounter[c.GetType().Name] = 1;
                        c.Refresh();
                        c.Index = indexCounter[c.GetType().Name];
                    }

                if (!isKnown) {
                    // Search for matching card type
                    isSupported = false;
                    foreach (IowCard cc in IowSupportedCardTypes.Cards) {
                        if (iowCardInfo.CardType != 0 && cc.CardId == iowCardInfo.CardId) {
                            // indexCounter is 1-based! The first card gets index value 1!
                            if (indexCounter.ContainsKey(cc.GetType().Name))
                                indexCounter[cc.GetType().Name]++;
                            else
                                indexCounter[cc.GetType().Name] = 1;

                            object[] constructorParam = { iow, indexCounter[cc.GetType().Name], iowCardInfo };
                            IowCard newCard = ObjectFactory<IowCard>.TryNew(cc.GetType(), constructorParam);

                            if (newCard != null) {
                                Add(newCard.CardName, newCard);         // to do elsewhere: replace the access key of the card by something configured by the user
                                isSupported = true;
                            }
                        }
                    }

                    // If the card is not supported, add it as "unknown"
                    if (!isSupported) {
                        IowCard newCard = new Cards.IowCardUnknown(iow, 0, iowCardInfo);
                        Add(newCard.CardName, newCard);
                    }
                }
            }

            // Remove entries of cards not found to be alive.
            Dictionary<String, IowCard> tmpDict = new Dictionary<string, IowCard>();
            foreach (String key in Keys)
                tmpDict[key] = this[key];

            foreach (String key in tmpDict.Keys)
                if (!tmpDict[key].IowDevice.CheckIsAlive())
                    Remove(key);

            return this;
        }

        /// <summary>
        /// Get names of all cards.
        /// </summary>
        public ICollection<String> Names
        {
            get {
                String[] names = new String[Count];
                int index = 0;
                foreach (String name in Keys)
                    names[index++] = name;
                return names;
            }
        }

        /// <summary>
        /// Rename IowCard. The new name must be unique in the dictionary.
        /// </summary>
        /// <param name="oldName">Old name of IowCard.</param>
        /// <param name="newName">New name of IowCard.</param>
        public void Rename(String oldName, String newName) {

            newName = newName.ToLower();

            if (this.ContainsKey(newName))
                throw new ArgumentException("New name already present in dictionary.", "newName");

            if (!this.ContainsKey(oldName))
                throw new ArgumentException("Old name not existing in dictionary.", "oldName");

            IowCard c = this[oldName];

            c.CardName = newName;
            this[newName] = c;
            this.Remove(oldName);
        }

        /// <summary>
        /// Shut down all cards contained in this dictionary.
        /// </summary>
        public void ShutdownCards()
        {
            if (this.Count > 0)
                foreach (IowCard c in this.Values)
                    c.Shutdown();
        }

        /// <summary>
        /// Resets all cards contained in this dictionary.
        /// </summary>
        public void ResetCards()
        {
            if (this.Count > 0)
                foreach (IowCard c in this.Values)
                    c.Reset();
        }

        /// <summary>
        /// Get all cards as array.
        /// </summary>
        /// <returns>IowCard[] of all identified cards.</returns>
        public IowCard[] GetCards()
        {
            IowCard[] cards = new IowCard[Count];
            int index = 0;
            foreach (IowCard c in Values)
                cards[index++] = c;
            return cards;
        }

        /// <summary>
        /// Get all cards of given cardId as array.
        /// </summary>
        /// <param name="cardId">Card type identfiction number.</param>
        /// <returns></returns>
        public IowCard[] GetCards(Int32 cardId)
        {
            if (this.Count == 0)
                return new IowCard[0];

            int counter = 0;

            foreach (IowCard ioc in Values)
            {
                if (ioc.CardId == cardId)
                    counter++;
            }

            IowCard[] result = new IowCard[counter];

            counter = 0;
            foreach (IowCard ioc in Values)
            {
                if (ioc.CardId == cardId)
                    result[counter++] = ioc;
            }

            return result;
        }

        /// <summary>
        /// Get card with the given name.
        /// </summary>
        /// <param name="cardName">Logical name of the card.</param>
        /// <returns>Reference to IowCard object.</returns>
        public IowCard GetCard(String cardName)
        {
            return this[cardName];
        }

        /// <summary>
        /// Get first matching card of the given cardId from IowCardDictionary.
        /// Be aware that the order inside a dictionary is not defined.
        /// </summary>
        /// <param name="cardId"></param>
        /// <exception cref="ArgumentException"></exception>
        /// <returns>Reference to IowCard object.</returns>
        public IowCard GetCard(Int32 cardId)
        {
            if (this.Count > 0)
                foreach (IowCard ioc in Values)
                    if (ioc.CardId == cardId)
                        return ioc;

            throw new ArgumentException("IowCard with the given Id not found.", "cardId");
        }

        /// <summary>
        /// Searches for a IowCard from the IowCardDictionary which would be able to execute the given command.
        /// Returns the reference to the first matching card in the IowDictionary or null if there is none.
        /// Be aware that the IowCardDictionary is a hash table: the order of the cards is undefined.
        /// </summary>
        /// <param name="command">Command to the IowCard.</param>
        /// <param name="foundCard">Reference to the found IowCard instance.</param>
        /// <returns>Reference to the IowCard or null, if something failed.</returns>
        //TODO: find better name for this method.
        public Boolean TryFindCardForCommand(String command, out IowCard foundCard)
        {
            foundCard = null;

            if (Count == 0)
                return false;

            IowCardCommand c = new IowCardCommand(command);

            // The command defines the name of the card => directly check on this card
            if (c.HasName)
                return TryFindCardForCommand(command, c.NameValue, out foundCard);

            // The command defines the index number of the card => directly check on this card instance.
            if (c.HasIndex)
                return TryFindCardForCommand(command, c.IndexValue, out foundCard);

            // Search for a matching card
            foreach (IowCard ioc in Values)
            {
                if (ioc.CheckCommand(command).IsExecutable)
                {
                    foundCard = ioc;
                    return true;
                }
            }

            foundCard = null;
            return false;
        }

        /// <summary>
        /// Searches for a IowCard from the IowCardDictionary which would be able to execute the given command.
        /// Returns the reference to the first matching card in the IowDictionary or null if there is none.
        /// Be aware that the IowCardDictionary is a hash table: the order of the cards is undefined.
        /// </summary>
        /// <param name="command">Command to the IowCard.</param>
        /// <returns>Reference to the first found IowCard.</returns>
        /// <exception cref="InvalidOperationException">Thrown if no attached card has validated this command successfully.</exception>
        public IowCard FindCardForCommand(String command)
        {
            IowCard result;

            if (TryFindCardForCommand(command, out result))
                return result;

            throw new InvalidOperationException(String.Format("No matching card found for command {0}", command));
        }

        /// <summary>
        /// Searches for a IowCard from the IowCardDictionary which would be able to execute the given command.
        /// Returns the reference to the first matching card in the IowDictionary or null if there is none.
        /// Be aware that the IowCardDictionary is a hash table: the sequence of the cards is undefined.
        /// </summary>
        /// <param name="command">Command to the IowCard.</param>
        /// <param name="cardIndex">Index of the IowCard.</param>
        /// <param name="foundCard">Reference to the found IowCard instance.</param>
        /// <returns>Reference to the IowCard or null, if something failed.</returns>
        private Boolean TryFindCardForCommand(String command, Int32 cardIndex, out IowCard foundCard)
        {
            foundCard = null;

            // No card in dictionary => return immediately.
            if (Count == 0)
                return false;

            foreach (IowCard ioc in Values)
                try {
                    if (ioc.Index == cardIndex && ioc.CheckCommand(command).IsExecutable) {
                        foundCard = ioc;
                        return true;
                    }
                }
                catch {
                    // ignore any error and continue with next card.
                }

            return false;
        }

        /// <summary>
        /// Searches the IowCardDictionary for the card with the logical name cardName and checks whether
        /// this card could execute the command.
        /// Return the reference to this card, if the check is passed.
        /// Return null, if the card was not found or the check failed.
        /// </summary>
        /// <param name="command">Command to the IowCard.</param>
        /// <param name="cardName">Name of the IowCard.</param>
        /// <param name="foundCard">Reference to the found IowCard instance.</param>
        /// <returns>Reference to the IowCard or null, if something failed.</returns>
        private Boolean TryFindCardForCommand(String command, String cardName, out IowCard foundCard)
        {
            try {
                // Check the dictionary. Key should be the card name.
                if (this.ContainsKey(cardName)) {
                    IowCard ioc = this[cardName];

                    if (ioc.CheckCommand(command).IsExecutable) {
                        foundCard = ioc;
                        return true;
                    }
                }

                // Not found via dictionary key.
                // Walk again through dictionary.
                // The user might have changed CardName property directly without having updating the dictionary.
                // This loop returns the first matching card. Be aware that the dictionary is not sorted.
                foreach (IowCard ioc in Values) {
                    if (ioc.CardName == cardName && ioc.CheckCommand(command).IsExecutable) {
                        foundCard = ioc;
                        return true;
                    }
                }
            }
            catch {
                // ignore any error
            }

            foundCard = null;
            return false;
        }

        /// <summary>
        /// Searches for a IowCard which accepts the command and executes it on this card.
        /// Be aware that the IowCardDictionary is a hash table: the sequence of the cards is undefined.
        /// </summary>
        /// <param name="command">Command to execute.</param>
        /// <returns>True, if a card was found and the command has been executed successfully. False, in case of any error.</returns>
        public Boolean TryExecuteCommand(String command)
        {
            IowCardCommand result;
            return TryExecuteCommand(command, out result);
        }

        /// <summary>
        /// Searches for a IowCard which accepts the command and executes it on this card.
        /// Be aware that the IowCardDictionary is a hash table: the sequence of the cards is undefined.
        /// </summary>
        /// <param name="command">Command to execute.</param>
        /// <param name="result">IowCardCommand object which has been executed.</param>
        /// <returns>True, if a card was found and the command has been executed successfully. False, in case of any error.</returns>
        public Boolean TryExecuteCommand(String command, out IowCardCommand result)
        {
            //command = command.ToLower();
            result = new IowCardCommand(command);
            IowCard iow;

            if (TryFindCardForCommand(command, out iow)) {
                try {
                    result = iow.ExecuteCommand(command);
                    return result.ExecutionSuccess;
                }
                catch { return false; }
            }
            return false;
        }

        /// <summary>
        /// Searches for a IowCard which accepts the command and executes it on this card.
        /// Be aware that the IowCardDictionary is a hash table: the sequence of the cards is undefined.
        /// </summary>
        /// <param name="cmd">Command to execute.</param>
        /// <returns>IowCardCommand object which has been executed.</returns>
        /// <exception cref="InvalidOperationException">Thrown if no attached card has executed this command successfully.</exception>
        public IowCardCommand ExecuteCommand(String cmd)
        {
            IowCardCommand cc;

            if (TryExecuteCommand(cmd, out cc))
                    return cc;

            throw new InvalidOperationException(String.Format("Command \"{0}\" could not be executed on any attached card.", cmd));
        }

        /// <summary>
        /// Searches for a IowCard which accepts the command and executes it on this card.
        /// Be aware that the IowCardDictionary is a hash table: the sequence of the cards is undefined.
        /// </summary>
        /// <param name="cmd0">1st Command to execute.</param>
        /// <param name="delay">Delay to wait in between 1 and 2.</param>
        /// <param name="cmd1">2nd Command to execute.</param>
        /// <returns>IowCardCommand object which has been executed.</returns>
        /// <exception cref="InvalidOperationException">Thrown if no attached card has executed this command successfully.</exception>
        public IowCardCommand ExecuteCommand(String cmd0, int delay = 0, String cmd1 = "")
        {
            IowCardCommand cc;

            if (TryExecuteCommand(cmd0, out cc)) {
                if (delay != 0)
                    Thread.Sleep(delay);
                if (cmd1.Length > 0) {
                    if (TryExecuteCommand(cmd1, out cc))
                        return cc;
                }
                else
                    return cc;
            }
            if (cmd1.Length > 0)
                throw new InvalidOperationException(String.Format("Command \"{0}\" or \"{1}\" could not be executed on any attached card.", cmd0, cmd1));
            else
                throw new InvalidOperationException(String.Format("Command \"{0}\" could not be executed on any attached card.", cmd0));
        }

        /// <summary>
        /// closes an relay for given key from klf
        /// </summary>
        /// <param name="key">key name.</param>
        public void closeKey (string key)
        {
            ExecuteCommand((string)keyRelayC[key.ToLower()]);
        }

        /// <summary>
        /// opens an relay for given key from klf
        /// </summary>
        /// <param name="key">key name.</param>
        public void openKey (string key)
        {
            ExecuteCommand((string)keyRelayO[key.ToLower()]);
        }

        /// <summary>
        /// presses an relay for given key from klf
        /// </summary>
        /// <param name="key">key name.</param>
        public void pressKey(string key, int delay = 0)
        {
            ExecuteCommand((string)keyRelayC[key]);
            Thread.Sleep(delay);
            ExecuteCommand((string)keyRelayO[key]);
        }

        /// <summary>
        /// closes an relay for given soft key from klf
        /// </summary>
        /// <param name="key">soft key name.</param>
        public void closeSoft (string key)
        {
            ExecuteCommand((string)keyRelayC[softRelay[key.ToLower()]]);
        }

        /// <summary>
        /// opens an relay for given soft key from klf
        /// </summary>
        /// <param name="key">soft key name.</param>
        public void openSoft (string key)
        {
            ExecuteCommand((string)keyRelayO[softRelay[key.ToLower()]]);
        }

        /// <summary>
        /// presses an relay for given soft key from klf
        /// </summary>
        /// <param name="key">soft key name.</param>
        public void pressSoft (string key, int delay = 0)
        {
            ExecuteCommand((string)keyRelayC[softRelay[key]]);
            Thread.Sleep(delay);
            ExecuteCommand((string)keyRelayO[softRelay[key]]);
        }
    }
}
