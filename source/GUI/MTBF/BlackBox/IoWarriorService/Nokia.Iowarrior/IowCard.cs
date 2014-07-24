using System;
using System.Collections.Generic;
using System.Text;
using Nokia.Iowarrior;
using Nokia.Iowarrior.Devices;
using Nokia.Iowarrior.Cards;
using System.Reflection;

namespace Nokia.Iowarrior
{
    /// <summary>
    /// This abstract class provides the basic functions which are available for each IowCard.
    /// Further functions are located in the classes of the card variants.
    /// </summary>
    public abstract class IowCard
    {
        /// <summary>
        /// Get an empty result Dictionary.
        /// </summary>
        protected static readonly Dictionary<String, Object> EmptyResult = new Dictionary<string, object>();

        #region Public Static
        /// <summary>
        /// Read card information from a card. Required to be able to select the correct implementation for
        /// a card.
        /// If the information could not be read, an InvalidOperationException is thrown.
        /// </summary>
        /// <param name="iow">IowDevice to read from.</param>
        /// <returns>Type information about this card.</returns>
        public static IowCardInformation ReadCardInformation(IowDevice iow)
        {
            if (iow == null)
                throw new ArgumentNullException("iow");

            switch (iow.ProductId)
            {
                case ProductId.Iowarrior56:
                    return GetCardTypeEEprom(iow);

                case ProductId.Iowarrior40:
                    // Enable reading of ports P0.0 & P0.1
                    IowBits readP00andP01only = iow.LastOutputs;
                    readP00andP01only[0] = true;
                    readP00andP01only[1] = true;
                    iow.WriteOutputs(readP00andP01only);

                    IowBits ports = iow.ReadInputs();

                    // Check P0.1 state
                    if (ports[1] == false)
                    {
                        // P0.1 Low => new card with EEprom configuration
                        return GetCardTypeEEprom(iow);
                    }
                    else
                    {
                        // P0.1 High => old card with resistor network
                        return GetCardTypeResistor(iow);
                    }

                default:
                    throw new InvalidOperationException("Could not read card information: Unsupported Iowarrior Product Id");
            }
        }

        #endregion

        #region Private Static
        /// <summary>
        /// Helper function. Reads information from cards using resistor network to code ID and version.
        /// </summary>
        /// <param name="iow">IowDevice to read from.</param>
        /// <returns>Type information about this card.</returns>
        private static IowCardInformation GetCardTypeResistor(IowDevice iow)
        {
            IowCardInformation iowCardInfo = new IowCardInformation();

            IowBits[] readSequence = { new IowBits(0x0000ff01),
                                       new IowBits(0x00000002)};

            IowBits[] responses = new IowBits[readSequence.Length];

            for (Int32 i = 0; i < readSequence.Length; i++)
            {
                iow.WriteOutputs(readSequence[i]);
                responses[i] = iow.ReadInputs();
            }

            foreach (IowBits b in responses)
            {
                if (b[0] == true && b[1] == false)
                {
                    Int32 x = (BitConverter.GetBytes(b.Value))[1];
                    Int32 id = (x & 0x0fc) >> 2;
                    Int32 ver = x & 0x03;
                    iowCardInfo.CardType = id;
                    iowCardInfo.HardwareRevision = ver;
                }
            }

            if (iowCardInfo.CardType == 0x0c)
            {
                iowCardInfo = GetCardTypeEEprom(iow);
            }

            return iowCardInfo;
        }

        /// <summary>
        /// Helper function. Reads information from cards using resistor network to code ID and version.
        /// </summary>
        /// <param name="iow">IowDevice to read from.</param>
        /// <returns>Type information about this card.</returns>
        private static IowCardInformation GetCardTypeEEprom(IowDevice iow)
        {
            IowCardInformation iowCardInfo = null;

            // IowBits outputs = new IowBits(0);
            // IowBits outputs = iow.LastOutputs;
            IowBits outputs = iow.ReadInputs();

            // Set P0.0 to high: Connect IIC-EEprom to Iowarrior
            outputs[0] = true;
            iow.WriteOutputs(outputs);

            // read data from EEprom
            iowCardInfo = IowCard.ReadCardInfoFromEEprom(iow);

            // Set P0.0 to low again: Disconnect IIC-EEProm from Iowarrior
            outputs[0] = false;
            iow.WriteOutputs(outputs);

            return iowCardInfo;
        }

        /// <code>
        /// EEPROM data structure
        /// Address	Length	Content
        /// [hex]	[byte]
        /// ======================================
        /// 00      1       Bit 0..3: Header structure version; Bit 4..7 HW revision
        /// 01      1       HW type
        /// 02      2       HW sub-type
        /// 04      3       Unique serial number [0xxxxx => Iowarrior, F0xxxx => RAPT fixture]
        /// 07      1       Product name length n [ n==0 => no product name => generic HW]
        /// 08      n       Product name [ASCII; fields separated by "/"; format e.g.: "xxx-yyyy/hhhh" => sample: "RM-313/1012"]
        /// 08+n..2F        reserved for header structure [=0]
        /// ---------------------------------------
        /// 30..FF          reserved [=0xFF]. HW type/sub-type specific data.
        /// </code>
        /// <summary>
        /// Helper function. Reads information from EEprom on the card.
        /// </summary>
        /// <param name="iow">IowDevice to read from.</param>
        /// <returns>Type information about this card.</returns>
        private static IowCardInformation ReadCardInfoFromEEprom(IowDevice iow)
        {
            IowCardInformation iowCardInfo = new IowCardInformation();
            Byte[] eepromInfo = new Byte[0x30];

            try
            {
                // Enable IIC function
                iow.EnableIic();

                // Read information
                eepromInfo = iow.ReadEEpromBytes(0, 0x30);
            }
            finally
            {
                // Disable IIC function / enable hidden I/O ports again
                iow.DisableIic();
            }

            if (eepromInfo.Length != 0x30)
            {
                throw new InvalidOperationException("Could not read IowCard information from EEProm");
            }

            iowCardInfo.HardwareRevision = (eepromInfo[0] & 0xf0) >> 4;
            iowCardInfo.CardType = eepromInfo[1];
            iowCardInfo.CardSubtype = eepromInfo[2] + (eepromInfo[3] << 8);
            iowCardInfo.SerialNumber = "0x"+(eepromInfo[4]
                                       + (eepromInfo[5] << 8)
                                       + (eepromInfo[6] << 16)).ToString("X8");
            iowCardInfo.ProductName = "";
            for (byte i = 0; i < Math.Min(eepromInfo[7], (byte)0x27); i++)
                iowCardInfo.ProductName += (char)eepromInfo[8 + i];

            return iowCardInfo;
        }

        #endregion

        #region Private
        private Boolean isInitialized;

        /// <summary>
        /// The main IowDevice on this card.
        /// </summary>
        private IowDevice iowDevice;

        /// <summary>
        /// Contains valid information for this card.
        /// </summary>
        private IowCardInformation iowCardInfo;

        /// <summary>
        /// Initializes all important internal variables which can be read from the card using iowDevice.
        /// IowCard internal use only!
        /// </summary>
        private void Initialize()
        {
            if (isInitialized)
                return;

            if (iowCardInfo == null)
            {
                iowCardInfo = ReadCardInformation(iowDevice);
            }

            iowCardInfo.LogicalName = CardTypeName + "_" + Index.ToString("00");
            iowCardInfo.CardType = 0xff & (CardId >> 20);
            iowCardInfo.CardSubtype = 0xffff & (CardId >> 4);
            iowCardInfo.HardwareRevision = 0xf & CardId;
            if (iowCardInfo.SerialNumber.StartsWith("HASH"))
                iowCardInfo.SerialNumber = IowDevice.SerialNumber;

            isInitialized = true;
        }

        #endregion

        #region Protected

        // Constructors & Initialization

        /// <summary>
        /// Creates a dummy IowCard object which does not have any connection to a physical device.
        /// </summary>
        protected IowCard()
        {
            iowDevice = new IowDevice();
        }

        /// <summary>
        /// Creates an IowCard object which uses the given iowDevice.
        /// </summary>
        /// <param name="iowDevice">Reference to IowDevice on this card.</param>
        /// <param name="index">Index number of this card (one-based). Used to distinguish cards of the same type.</param>
        protected internal IowCard(IowDevice iowDevice, Int32 index)
        {
            this.iowDevice = iowDevice;
            iowCardInfo.Index = index;
            Initialize();
        }

        /// <summary>
        /// Creates an IowCard object which uses the given iowDevice.
        /// </summary>
        /// <param name="iowDevice">Reference to IowDevice on this card.</param>
        /// <param name="index">Index number of this card (one-based). Used to distinguish cards of the same type.</param>
        /// <param name="iowCardInformation">Reference to IowCardInformation read from this card.</param>
        protected internal IowCard(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
        {
            this.iowDevice = iowDevice;
            this.iowCardInfo = iowCardInformation;
            iowCardInfo.Index = index;
            Initialize();
        }

        #endregion

        #region Internal
        /// <summary>
        /// Calls a given parameterless method of the given iowCard object.
        /// </summary>
        /// <param name="methodName">Name of the method to be called.</param>
        /// <returns>Returns the return value of the called method.</returns>
        internal object CallMethod(String methodName)
        {
            try
            {
                return this.GetType().InvokeMember(methodName,
                    System.Reflection.BindingFlags.Instance
                        | System.Reflection.BindingFlags.NonPublic
                        | System.Reflection.BindingFlags.InvokeMethod
                        | System.Reflection.BindingFlags.Public,
                    null, this, null, System.Globalization.CultureInfo.InvariantCulture);
            }
            catch (Exception ex)
            {
                if (ex.InnerException != null)
                    throw ex.InnerException;
                else
                    throw;
            }
        }

        /// <summary>
        /// Calls a given method of the given iowCard object with parameters.
        /// </summary>
        /// <param name="methodName">Name of the method to be called.</param>
        /// <param name="parameters">Calling parameters for the given method.</param>
        /// <returns>Returns the return value of the called method.</returns>
        internal object CallMethod(String methodName, params object[] parameters)
        {
            try
            {
                return this.GetType().InvokeMember(methodName,
                        System.Reflection.BindingFlags.Instance
                            | System.Reflection.BindingFlags.NonPublic
                            | System.Reflection.BindingFlags.InvokeMethod
                            | System.Reflection.BindingFlags.Public,
                        null, this, parameters);
            }
            catch (Exception ex)
            {
                if (ex.InnerException != null)
                    throw ex.InnerException;
                else
                    throw;
            }
        }

        #endregion

        #region Public
        /// <summary>
        /// Reads again complete card information.
        /// </summary>
        public void Refresh()
        {
            iowCardInfo = null;
            isInitialized = false;

            Initialize();
        }

        /// <summary>
        /// Get list of supported commands.
        /// </summary>
        public virtual ICollection<String> KnownCommands
        {
            get { return GetKnownCommands(); }
        }

        // Accessors

        /// <summary>
        /// Get/set the IowDevice which is on this IowCard.
        /// </summary>
        public IowDevice IowDevice
        {
            get { return iowDevice; }
            set { this.iowDevice = value; Initialize(); }
        }

        /// <summary>
        /// Get/set the logical name of the card. This name can be used in *Command() methods to identify the
        /// destination card for the commands.
        /// </summary>
        public String CardName
        {
            get { return iowCardInfo.LogicalName; }
            set { iowCardInfo.LogicalName = value; }
        }

        /// <summary>
        /// Get/set the instance counter index of this IowCard. Index counters start with 1.
        /// </summary>
        public Int32 Index
        {
            get { return iowCardInfo.Index; }
            set { iowCardInfo.Index = value; }
        }

        /// <summary>
        /// Get the type information of this card.
        /// </summary>
        public IowCardInformation IowCardInfo
        {
            get { return iowCardInfo; }
            set { iowCardInfo = value; isInitialized = (value != null); }
        }

        /// <summary>
        /// True, if IowCardInformation has been read from the card and assigned to IowCardInfo property.
        /// </summary>
        public Boolean IsInitialized { get { return isInitialized; } }

        // Abstract accessors

        /// <summary>
        /// Get Hardware-ID of this card.
        /// </summary>
        public Int32 CardId
        {
            get { return IowSupportedCardTypes.GetIdOfIowCard(this); }
        }

        /// <summary>
        /// Get type name of this card without leading "IowCard".
        /// </summary>
        public String CardTypeName
        {
            get { return this.GetType().Name.Remove(0,7); }
        }

        #endregion

        #region Public Abstract
        /// <summary>
        /// Virtual. Checks the syntax and semantics of the command.
        /// IowCardCommand.IsExecutable is set to true, if the command is valid and known and could be executed on this card.
        /// IowCardCommand.IsExecutable is set to false, if the command is invalid or could not be executed on this card.
        /// </summary>
        /// <param name="command">Command to check.</param>
        /// <returns>IowCardCommand object holding the command and executio success.</returns>
        public virtual IowCardCommand CheckCommand(String command)
        {
            return CheckOrExecute(command, false);
        }

        /// <summary>
        /// Virtual. Execute the given command.
        /// First performs a CheckCommand() on this command to check and parse it, then it
        /// is executed.
        /// IowCardCommand.ExecutionSuccess is set to true, if the command was executed successfully.
        /// IowCardCommand.ExecutionSuccess is set to false, otherwise.
        /// </summary>
        /// <param name="command">True, if the command was executed successfully.</param>
        /// <returns>IowCardCommand object holding the command and executio success.</returns>
        public virtual IowCardCommand ExecuteCommand(String command)
        {
            return CheckOrExecute(command, true);
        }

        /// <summary>
        /// Gets a string representation of this IowCard object.
        /// </summary>
        /// <returns>String containing CardTypeName, Type, SubType and HardwareRevision.</returns>
        public override string ToString()
        {
            StringBuilder s = new StringBuilder();
            s.Append("IowCard{");
            s.Append("TypeName=").Append(CardTypeName);
            s.Append(", Type=").Append(CardType);
            s.Append(", SubType=").Append(CardSubType);
            s.Append(", HwRev=").Append(HardwareRevision);
            s.Append("}");
            return s.ToString();
        }

        /// <summary>
        /// Get CardType of this IowCard instance.
        /// </summary>
        public Int32 CardType
        {
            get { return (CardId >> 20) & 0xFF; }
        }

        /// <summary>
        /// Get CardSubType of this IowCard instance.
        /// </summary>
        public Int32 CardSubType
        {
            get { return (CardId >> 4) & 0xFFFF; }
        }

        /// <summary>
        /// Get HardwareRevision of this IowCard instance.
        /// </summary>
        public Int32 HardwareRevision
        {
            get { return (CardId & 0xF); }
        }


        /// <summary>
        /// Abstract. Bring the card in a safe state.
        /// </summary>
        public abstract void Shutdown();

        /// <summary>
        /// Abstract. Reset the card to Power Up state. Normally all relays will be opened.
        /// </summary>
        public abstract void Reset();

        #endregion

        /// <summary>
        /// Retrieves the known commands of this card instance from its
        /// public method names.
        /// The method names do have to follow a name scheme: "Execute_Verb_Noun", e.g.
        /// "Execute_Set_Bsi".
        /// Second, there can optionally be a property defined per execution method. The
        /// naming scheme here is "Verb_Noun_Values", e.g. "Set_Bsi_Values".
        /// It must return an String-typed IList. All entries of this list will be prefixed
        /// with "verb:noun=" to build a valid command.
        /// </summary>
        /// <returns>List of known commands of this card.</returns>
        internal String[] GetKnownCommands()
        {
            MethodInfo[] methodInfos = GetType().GetMethods();
            PropertyInfo[] propertyInfos = GetType().GetProperties();
            List<String> result = new List<string>();

            foreach (MethodInfo m in methodInfos)
            {
                if (m.Name.StartsWith("Execute_"))
                {
                    String[] names = m.Name.Split('_');
                    String verb = names[1].ToLower();
                    String noun = names[2].ToLower();
                    String property = m.Name.Replace("Execute_", "Values_");

                    Boolean hasValues = false;

                    foreach (PropertyInfo p in propertyInfos)
                    {
                        if (p.Name.Contains(property))
                        {
                            Object _x = p.GetValue(this, null);
                            IList<String> values = _x as IList<String>;

                            foreach (String s in values)
                            {
                                result.Add(verb + ":" + noun + "=" + s);
                                hasValues = true;
                            }
                        }
                    }

                    if (!hasValues)
                        if (noun != "")
                            result.Add(verb + ":" + noun);
                }
            }
            String[] resultArray = new String[result.Count];
            result.CopyTo(resultArray);
            return resultArray;
        }

        /// <summary>
        /// First letter of input string becomes capital letter, all others will become lower case letters.
        /// </summary>
        /// <param name="s">Input string.</param>
        /// <returns>Pascal-cased input string.</returns>
        private String Pascalize(String s)
        {
            return char.ToUpper(s[0]) + s.ToLower().Substring(1);
        }

        /// <summary>
        /// Checks or executes a given command string. Command strings are like this:
        /// verb:noun=value:noun=value:noun=value...
        /// </summary>
        /// <param name="command">Command string.</param>
        /// <param name="executeIt">If true, execute the action on real hardware. Otherwise just check the command string.</param>
        /// <returns>IowCardCommand object.</returns>
        private IowCardCommand CheckOrExecute(String command, Boolean executeIt)
        {
            IowCardCommand cc = new IowCardCommand(command);
            String verb = cc.Command;

            // Quickly return if name or index does not match: The command is not for this card.
            if (cc.HasName && (cc.NameValue != CardName))
                return cc;
            if (cc.HasIndex && (cc.IndexValue != Index))
                return cc;

            // It's still unknown whether the command matches to the card.
            // So loop over all nouns in the command and try to check/execute them.
            foreach (String noun in cc.FieldNames)
            {
                // The method name to look for.
                String methodName = "Execute_" + Pascalize(verb) + "_" + Pascalize(noun);
                // The results of the method call will be stored here.
                IDictionary<String, Object> methodResult = new Dictionary<String, Object>();

                // Ignore "index" and "name" nouns. They have been handled already above.
                if (noun == "index" || noun == "name")
                    continue;

                // Try to call the given method.
                try
                {
                    methodResult = (IDictionary<String,Object>)CallMethod(methodName, executeIt, cc.GetFieldValues(noun) as IList<String>);
                    cc.IsExecutable = true;
                    if (executeIt)
                    {
                        foreach (String key in methodResult.Keys)
                            cc.ReturnValues[key] = methodResult[key];
                        cc.ExecutionSuccess = true;
                    }
                }
                catch (MissingMethodException)
                {
                    // Method not found => the command is not for this card.
                    cc.IsExecutable = false;
                    cc.ExecutionSuccess = false;
                    return cc;
                }
                catch (ArgumentException)
                {
                    // There was an error during the command check => the command is not accepted by this card.
                    cc.IsExecutable = false;
                    cc.ExecutionSuccess = false;
                }
            }

            return cc;
        }
    }

}

