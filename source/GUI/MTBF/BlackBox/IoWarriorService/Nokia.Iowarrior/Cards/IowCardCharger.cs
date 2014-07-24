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
    public sealed class IowCardCharger : IowCard
    {
        #region Parameter bits definition

        class CardCommand : IowCardCommand
        {
            public CardCommand(String command) : base(command)
            {
                CommandMap["connect:charger=1"] = "+24,+25,-26,-27,-28,-29,-30,-31";
                CommandMap["connect:charger=2"] = "-24,-25,+26,+27,-28,-29,-30,-31";
                CommandMap["connect:charger=3"] = "-24,-25,-26,-27,+28,+29,-30,-31";
                CommandMap["connect:charger=4"] = "-24,-25,-26,-27,-28,-29,+30,+31";
                CommandMap["disconnect:charger=1"] = "-24,-25";
                CommandMap["disconnect:charger=2"] = "-26,-27";
                CommandMap["disconnect:charger=3"] = "-28,-29";
                CommandMap["disconnect:charger=4"] = "-30,-31";
                CommandMap["disconnect:charger=all"] = "-24,-25,-26,-27,-28,-29,-30,-31";
            }
        }
        #endregion
        
        public IowCardCharger()
            : base()
        {
        }

        public IowCardCharger(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
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
                case "connect":
                case "disconnect":
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
