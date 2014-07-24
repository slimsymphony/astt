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
    public sealed class IowCardFlash : IowCard
    {
        #region Parameter bits definition

        class CardCommand : IowCardCommand
        {
            public CardCommand(String command)
                : base(command)
            {
                CommandMap["close:flash=1"] = "+24";
                CommandMap["close:flash=2"] = "+25";
                CommandMap["close:flash=3"] = "+26";
                CommandMap["close:flash=4"] = "+27";
                CommandMap["close:flash=5"] = "+28";
                CommandMap["close:flash=6"] = "+29";
                CommandMap["close:flash=7"] = "+30";
                CommandMap["close:flash=8"] = "+31";
                CommandMap["close:flash=9"] = "+23";
                CommandMap["close:flash=10"] = "+22";
                CommandMap["close:flash=all"] = "+22,+23,+24,+25,+26,+27,+28,+29,+30,+31";
                CommandMap["close:flash"] = CommandMap["close:flash=all"];

                CommandMap["open:flash=1"] = "-24";
                CommandMap["open:flash=2"] = "-25";
                CommandMap["open:flash=3"] = "-26";
                CommandMap["open:flash=4"] = "-27";
                CommandMap["open:flash=5"] = "-28";
                CommandMap["open:flash=6"] = "-29";
                CommandMap["open:flash=7"] = "-30";
                CommandMap["open:flash=8"] = "-31";
                CommandMap["open:flash=9"] = "-23";
                CommandMap["open:flash=10"] = "-22";
                CommandMap["open:flash=all"] = "-22,-23,-24,-25,-26,-27,-28,-29,-30,-31";
                CommandMap["open:flash"] = CommandMap["open:flash=all"];
            }
        }
        #endregion
        
        public IowCardFlash()
            : base()
        {
        }

        public IowCardFlash(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
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
            get { return new CardCommand("").KnownCommands; }
        }

        public override IowCardCommand CheckCommand(String command)
        {
            CardCommand cc = new CardCommand(command);

            cc.IsExecutable = false;

            if (cc.HasIndex && (cc.IndexValue != Index))
                return cc;

            if (cc.HasName && (cc.NameValue != CardName))
                return cc;

            switch (cc.Command)
            {
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
