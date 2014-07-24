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
    public sealed class IowCardSim : IowCard
    {
        #region Parameter bits definition

        class CardCommand : IowCardCommand
        {
            public CardCommand(String command) : base(command)
            {
                CommandMap["close:sim=0"] = "+16,+17,+18";
                CommandMap["close:sim=1"] = "-16,-17,-18";
                CommandMap["close:sim=2"] = "+16,-17,-18";
                CommandMap["close:sim=3"] = "-16,17,-18";
                CommandMap["close:sim=4"] = "+16,+17,-18";
                CommandMap["close:sim=5"] = "-16,-17,+18";
                CommandMap["close:sim=6"] = "+16,-17,+18";
                CommandMap["close:sim=none"] = CommandMap["close:sim=0"];
                CommandMap["close:sim=default"] = CommandMap["close:sim=1"];

                CommandMap["open:sim=1"] = CommandMap["open:sim=2"] = CommandMap["open:sim=3"] = CommandMap["open:sim=4"] = CommandMap["open:sim=5"] = CommandMap["open:sim=6"] = CommandMap["close:sim=0"];
            }
        }
        #endregion
        
        public IowCardSim()
            : base()
        {
        }

        public IowCardSim(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation)
        {
            Reset();
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

            if (cc.HasName && (cc.NameValue != CardName))
                return cc;

            switch (cc.Command)
            {
                case "close":
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
                    case "close":
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
