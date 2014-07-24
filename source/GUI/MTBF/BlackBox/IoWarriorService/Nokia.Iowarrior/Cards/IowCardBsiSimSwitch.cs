// Disable "Missing XML comment for public type or member" warning.
// This file contains only code being accessed through an abstract interface class.
// The public methods are documented in this abstract interface class.
#pragma warning disable 1591

using System;
using System.Collections.Generic;
using System.Text;
using Nokia.Iowarrior;

namespace Nokia.Iowarrior.Cards
{
    public sealed class IowCardBsiSimSwitch : IowCard
    {
        #region Parameter bits definition

        class CardCommand : IowCardCommand
        {
            public CardCommand(String command) : base(command)
            {
                CommandMap["connect:bsi"] = "-2,-3";
                CommandMap["connect:bsi=normal"] = CommandMap["connect:bsi"];
                CommandMap["connect:bsi=local"] = "+2,-3";
                CommandMap["connect:bsi=test"] = "-2,+3";

                CommandMap["connect:power"] = "+4";
                CommandMap["disconnect:power"] = "-4";

                CommandMap["close:emag"] = "+5";
                CommandMap["open:emag"] = "-5";
             
                CommandMap["close:key=pwronx"] = "+11";
                CommandMap["close:key=func_r"] = "+12";
                CommandMap["close:key=navi_r"] = "+13";
                CommandMap["close:key=navi_m"] = "+14";
                CommandMap["close:key=navi_l"] = "+15";

                CommandMap["open:key=pwronx"] = "-11";
                CommandMap["open:key=func_r"] = "-12";
                CommandMap["open:key=navi_r"] = "-13";
                CommandMap["open:key=navi_m"] = "-14";
                CommandMap["open:key=navi_l"] = "-15";

                CommandMap["close:sim=0"] = "+8,-9,+10";
                CommandMap["close:sim=1"] = "-8,-9,-10";
                CommandMap["close:sim=2"] = "+8,-9,-10";
                CommandMap["close:sim=3"] = "-8,+9,-10";
                CommandMap["close:sim=4"] = "+8,+9,-10";
                CommandMap["close:sim=5"] = "-8,-9,+10";
                CommandMap["close:sim=6"] = "+8,-9,10";
                CommandMap["close:sim=none"] = CommandMap["close:sim=0"];
                CommandMap["close:sim=default"] = CommandMap["close:sim=1"];
                CommandMap["open:sim=1"] = CommandMap["open:sim=2"] = CommandMap["open:sim=3"] = CommandMap["open:sim=4"] = CommandMap["open:sim=5"] = CommandMap["open:sim=6"] = CommandMap["close:sim=0"];
            }
        }
        #endregion
        
        public IowCardBsiSimSwitch()
            : base()
        {
        }

        public IowCardBsiSimSwitch(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation)
        {
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
            get
            {
                return new CardCommand("").KnownCommands;
            }
        }

        public override IowCardCommand CheckCommand(String command)
        {
            CardCommand cc = new CardCommand(command);

            cc.IsExecutable = false;

            if (cc.HasName && (cc.NameValue != CardName))
                return cc;

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

            if (cc.IsExecutable)
            {
                switch (cc.Command)
                {
                    case "connect":
                    case "disconnect":
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
    }
}
