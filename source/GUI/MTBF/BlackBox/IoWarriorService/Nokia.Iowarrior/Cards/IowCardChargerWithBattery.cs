// Disable "Missing XML comment for public type or member" warning.
// This file contains only code being accessed through an abstract interface class.
// The public methods are documented in this abstract interface class.
#pragma warning disable 1591

using System;
using System.Collections.Generic;
using System.Text;
using Nokia.Iowarrior;
using System.Threading;

namespace Nokia.Iowarrior.Cards
{
    public sealed class IowCardChargerWithBattery: IowCard
    {
        public IowCardChargerWithBattery() : base() { TurnOnVrel(); }

        public IowCardChargerWithBattery(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation) { TurnOnVrel(); } // Turn on Vrel TurnOnVrel(); 


        #region Command: open:key

        public IList<String> Values_Open_Key
        {
            get { return new String[] { "pwronx" }; }
        }

        public IDictionary<String, Object> Execute_Open_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    if (parameter.StartsWith("pwronx"))
                    {
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.5"), false);
                    }                  
                }
            }
            return EmptyResult;
        }

        #endregion

        #region Command: close:key

        public IList<String> Values_Close_Key
        {
            get { return new String[] { "pwronx" }; }
        }

        public IDictionary<String, Object> Execute_Close_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    if (parameter.StartsWith("pwronx"))
                    {
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.5"), true);
                    }
                }
            }
            return EmptyResult;
        }

        #endregion

        #region Command: press:key

        public IList<String> Values_Press_Key
        {
            get { return new String[] { "pwronx/delay" }; }
        }

        public IDictionary<String, Object> Execute_Press_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (executeIt)
            {
                Console.WriteLine(parameters[0]);
                String[] split = parameters[0].Split(new Char[] {'/'});
                if (split.Length != 2)
                    throw new ArgumentException();

                Int32 delay = Int32.Parse(split[1]);

                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.5"), true);
                Thread.Sleep(delay);
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.5"), false);
            }
            return EmptyResult;
        }

        #endregion
        
        #region Command: connect:power
                
        public IDictionary<String, Object> Execute_Connect_Power(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P2.2"), true);             
            }
            return EmptyResult;
        }

        #endregion

        #region Command: disconnect:power

        public IDictionary<String, Object> Execute_Disconnect_Power(Boolean executeIt, IList<String> parameters)
        {          
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P2.2"), false);
            }
            return EmptyResult;
        }

        #endregion

        #region Command: connect:cap

        public IDictionary<String, Object> Execute_Connect_Cap(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P2.3"), true);
            }
            return EmptyResult;
        }

        #endregion

        #region Command: disconnect:cap

        public IDictionary<String, Object> Execute_Disconnect_Cap(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P2.3"), false);
            }
            return EmptyResult;
        }

        #endregion

        #region Command: connect:battery

        public IDictionary<String, Object> Execute_Connect_Battery(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P2.0"), true);
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P2.1"), false);
            }
            return EmptyResult;
        }

        #endregion

        #region Command: disconnect:battery

        public IDictionary<String, Object> Execute_Disconnect_Battery(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P2.0"), false);
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P2.1"), false);
            }
            return EmptyResult;
        }

        #endregion

        #region Command: close:discharge

        public IDictionary<String, Object> Execute_Close_Discharge(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P2.0"), false);
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P2.1"), true);
            }
            return EmptyResult;
        }

        #endregion

        #region Command: connect:charger

        public IList<String> Values_Connect_Charger
        {
            get { return  new String[] { "1", "2", "3", "4", "5", "6", "7", "8" }; }
        }

        public IDictionary<String, Object> Execute_Connect_Charger(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    Int32 charger = Int32.Parse(parameter);
                    if ((charger < 1) || (charger > 8))
                        throw new ArgumentException();

                    IowBits inputs = IowDevice.ReadInputs();
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.0")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.1")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.2")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.3")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.4")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.5")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.6")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.7")] = false;

                    switch (charger)
                    {
                        case 1:
                            inputs[IowDevice.TranslatePortNameToBitNumber("P3.0")] = true;
                            break;
                        case 2:
                            inputs[IowDevice.TranslatePortNameToBitNumber("P3.1")] = true;
                            break;
                        case 3:
                            inputs[IowDevice.TranslatePortNameToBitNumber("P3.2")] = true;
                            break;
                        case 4:
                            inputs[IowDevice.TranslatePortNameToBitNumber("P3.3")] = true;
                            break;
                        case 5:
                            inputs[IowDevice.TranslatePortNameToBitNumber("P3.4")] = true;
                            break;
                        case 6:
                            inputs[IowDevice.TranslatePortNameToBitNumber("P3.5")] = true;
                            break;
                        case 7:
                            inputs[IowDevice.TranslatePortNameToBitNumber("P3.6")] = true;
                            break;
                        case 8:
                            inputs[IowDevice.TranslatePortNameToBitNumber("P3.7")] = true;
                            break;
                    }
                    IowDevice.WriteOutputs(inputs);
                }
            }
            return EmptyResult;
        }

        #endregion

        #region Command: disconnect:charger

        public IList<String> Values_Disconnect_Charger
        {
            get { return new String[] { "1", "2", "3", "4", "5", "6", "7", "8" }; }
        }

        public IDictionary<String, Object> Execute_Disconnect_Charger(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    Int32 charger = Int32.Parse(parameter);
                    if ((charger < 1) || (charger > 8))
                        throw new ArgumentException();

                    IowBits inputs = IowDevice.ReadInputs();
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.0")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.1")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.2")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.3")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.4")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.5")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.6")] = false;
                    inputs[IowDevice.TranslatePortNameToBitNumber("P3.7")] = false;                   
                    IowDevice.WriteOutputs(inputs);
                }
            }
            return EmptyResult;
        }

        #endregion

        #region Command: connect:bsi
        public IList<String> Values_Connect_Bsi
        {
            get { return new String[] { "normal_tabby", "local_tabby", "test_tabby", "normal_lynx", "local_lynx", "test_lynx" }; }
        }

        public IDictionary<String, Object> Execute_Connect_Bsi(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt) {
                IowBits inputs = IowDevice.ReadInputs();
                inputs[IowDevice.TranslatePortNameToBitNumber("P1.0")] = false;
                inputs[IowDevice.TranslatePortNameToBitNumber("P1.1")] = false;
                inputs[IowDevice.TranslatePortNameToBitNumber("P1.2")] = false;
                inputs[IowDevice.TranslatePortNameToBitNumber("P1.3")] = false;
                inputs[IowDevice.TranslatePortNameToBitNumber("P1.4")] = false;

                if (parameters.Count > 0) {
                    if (!Values_Connect_Bsi.Contains(parameters[0]))
                        throw new ArgumentException();

                    switch (parameters[0]) {
                        case "normal_tabby":
                            break;
                        case "local_tabby":
                            inputs[IowDevice.TranslatePortNameToBitNumber("P1.0")] = true;
                            break;
                        case "test_tabby":
                            inputs[IowDevice.TranslatePortNameToBitNumber("P1.1")] = true;
                            break;
                        case "normal_lynx":
                            inputs[IowDevice.TranslatePortNameToBitNumber("P1.2")] = true;
                            break;
                        case "local_lynx":
                            inputs[IowDevice.TranslatePortNameToBitNumber("P1.3")] = true;
                            break;
                        case "test_lynx":
                            inputs[IowDevice.TranslatePortNameToBitNumber("P1.4")] = true;
                            break;
                    }
                }
                IowDevice.WriteOutputs(inputs);
            }
            return EmptyResult;
        }
        #endregion

        #region Command: disconnect:bsi
        public IList<String> Values_Disconnect_Bsi
        {
            get { return new String[] { "" }; }
        }

        public IDictionary<String, Object> Execute_Disconnect_Bsi(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt) {
                IowBits inputs = IowDevice.ReadInputs();
                inputs[IowDevice.TranslatePortNameToBitNumber("P1.0")] = false;
                inputs[IowDevice.TranslatePortNameToBitNumber("P1.1")] = false;
                inputs[IowDevice.TranslatePortNameToBitNumber("P1.2")] = false;
                inputs[IowDevice.TranslatePortNameToBitNumber("P1.3")] = false;
                inputs[IowDevice.TranslatePortNameToBitNumber("P1.4")] = false;
                IowDevice.WriteOutputs(inputs);
            }
            return EmptyResult;
        }
        #endregion
        
        public override void Shutdown()
        {
            TurnOffVrel();
        }

        public override void Reset()
        {

        }              
                
        private void TurnOnVrel()
        {
            IowDevice.EnableIic();
            IowDevice.WriteIic(0x40, 0);
            IowDevice.DisableIic();
            
        }

        private void TurnOffVrel()
        {
            IowDevice.EnableIic();
            IowDevice.WriteIic(0x40, 1);
            IowDevice.DisableIic();
        }
    }
}


/*

 #region Parameter bits definition

        class CardCommand : IowCardCommand
        {
            public CardCommand(String command) : base(command)
            {
                CommandMap["set:bsi=1"] = "-8,-9,-10,-11,-12";  // Normal mode for all battery types
                CommandMap["set:bsi=2"] = "+8,-9,-10,-11,-12";  // Local tabby
                CommandMap["set:bsi=3"] = "-8,+9,-10,-11,-12";  // Test tabby
                CommandMap["set:bsi=4"] = "-8,-9,+10,-11,-12";  // Local lynx
                CommandMap["set:bsi=5"] = "-8,-9,-10,+11,-12";  // Test lynx
                CommandMap["set:bsi=6"] = "-8,-9,-10,-11,+12";  // Bsi variable
                CommandMap["set:bsi=normal_tabby"] = CommandMap["set:bsi=1"];
                CommandMap["set:bsi=local_tabby"] = CommandMap["set:bsi=2"];
                CommandMap["set:bsi=test_tabby"] = CommandMap["set:bsi=3"];
                CommandMap["set:bsi=normal_lynx"] = CommandMap["set:bsi=1"];
                CommandMap["set:bsi=local_lynx"] = CommandMap["set:bsi=4"];
                CommandMap["set:bsi=test_lynx"] = CommandMap["set:bsi=5"];
                CommandMap["connect:power"] = "+18";
                CommandMap["disconnect:power"] = "-18";
                CommandMap["connect:cap"] = "+19";
                CommandMap["disconnect:cap"] = "-19";
                CommandMap["connect:battery"] = "+16,-17"; // equal to battery=charge
                CommandMap["disconnect:battery"] = "-16,-17";
                CommandMap["discharge:battery"] = "-16,+17";

                CommandMap["connect:charger=1"] = "+24,-25,-26,-27,-28,-29,-30,-31";
                CommandMap["connect:charger=2"] = "-24,+25,-26,-27,-28,-29,-30,-31";
                CommandMap["connect:charger=3"] = "-24,-25,+26,-27,-28,-29,-30,-31";
                CommandMap["connect:charger=4"] = "-24,-25,-26,+27,-28,-29,-30,-31";
                CommandMap["connect:charger=5"] = "-24,-25,-26,-27,+28,-29,-30,-31";
                CommandMap["connect:charger=6"] = "-24,-25,-26,-27,-28,+29,-30,-31";
                CommandMap["connect:charger=7"] = "-24,-25,-26,-27,-28,-29,+30,-31";
                CommandMap["connect:charger=8"] = "-24,-25,-26,-27,-28,-29,-30,+31";

                CommandMap["disconnect:charger=1"] = "-24,-25,-26,-27,-28,-29,-30,-31";
                CommandMap["disconnect:charger=2"] = "-24,-25,-26,-27,-28,-29,-30,-31";
                CommandMap["disconnect:charger=3"] = "-24,-25,-26,-27,-28,-29,-30,-31";
                CommandMap["disconnect:charger=4"] = "-24,-25,-26,-27,-28,-29,-30,-31";
                CommandMap["disconnect:charger=5"] = "-24,-25,-26,-27,-28,-29,-30,-31";
                CommandMap["disconnect:charger=6"] = "-24,-25,-26,-27,-28,-29,-30,-31";
                CommandMap["disconnect:charger=7"] = "-24,-25,-26,-27,-28,-29,-30,-31";
                CommandMap["disconnect:charger=8"] = "-24,-25,-26,-27,-28,-29,-30,-31";

                CommandMap["close:key=pwronx"] = "+13";
                CommandMap["open:key=pwronx"] = "-13";

                CommandMap["close:emag"] = "+20";
                CommandMap["open:emag"] = "-20";
            }
        }
        #endregion
        
        public IowCardChargerWithBatteryV1()
            : base()
        {
        }

        public IowCardChargerWithBatteryV1(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation)
        {
            // Turn on Vrel
            TurnOnVrel();
        }

        public override void Shutdown()
        {
            // Do all required to get card in safe state.
        }

        public override void Reset()
        {
            // Open all relays
            IowBits bv = IowDevice.LastOutputs;
            for (int i = 2; i < 32; i++)
                bv[i] = false;

            IowDevice.WriteOutputs(bv);
        }

        public override ICollection<String> KnownCommands
        {
            get { return new CardCommand("").KnownCommands; }
        }

        public override IowCardCommand CheckCommand(String command)
        {
            CardCommand cc = new CardCommand(command);

            cc.IsExecutable = false;

            switch (cc.Command)
            {
                case "connect":
                case "disconnect":
                case "set":
                case "close":
                case "open":
                    cc.IsExecutable = cc.DefinesCommand();
                    break;
                default:
                    break;
            }

            return cc;
        }

        public override IowCardCommand ExecuteCommand(String command)
        {
            IowCardCommand cc = CheckCommand(command);
            IowBits bv = IowDevice.LastOutputs;
            cc.ExecutionSuccess = false;

            if (Index > 1)
                return cc;

            if (cc.HasName && (cc.NameValue != CardName))
                return cc;

            if (cc.IsExecutable)
            {
                switch (cc.Command)
                {
                    case "connect":
                    case "disconnect":
                    case "set":
                    case "close":
                    case "open":
                        bv = cc.UpdateIowBits(bv);
                        break;
                    default:
                        throw new ArgumentException(command, "ExecuteCommand: Invalid command");
                }
                IowDevice.WriteOutputs(bv);
                cc.ExecutionSuccess = true;
            }

            return cc;
        }

        
        private void TurnOnVrel()
        {
            IowDevice.EnableIic();
            IowDevice.WriteIic(0x40, 0);
            IowDevice.DisableIic();
            
        }

        private void TurnOffVrel()
        {
            IowDevice.EnableIic();
            IowDevice.WriteIic(0x40, 1);
            IowDevice.DisableIic();
        }
    }
*/