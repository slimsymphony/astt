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
    public sealed class IowCardAccessory : IowCard
    {
        #region Parameter bits definition

        class CardCommand : IowCardCommand
        {
            public CardCommand(String command)
                : base(command)
            {
                String acc1StringCon = "";
                String acc1StringDisCon = "";
                String acc2StringCon = "";
                String acc2StringDisCon = "";

                for (int pins = 1; pins <= 14; pins++)
                {
                    CommandMap[String.Format("connect:acc1={0}", pins)] = Convert.ToString(pins + 1);
                    CommandMap[String.Format("disconnect:acc1={0}", pins)] = Convert.ToString(-(pins + 1));
                    CommandMap[String.Format("connect:acc2={0}", pins)] = Convert.ToString(pins + 17);
                    CommandMap[String.Format("disconnect:acc2={0}", pins)] = Convert.ToString(-(pins + 17));
                    acc1StringCon += Convert.ToString(pins + 1) + ",";
                    acc1StringDisCon += Convert.ToString(-(pins + 1)) + ",";
                    acc2StringCon += Convert.ToString(pins + 17) + ",";
                    acc2StringDisCon += Convert.ToString(-(pins + 17)) + ",";
                }

                CommandMap["connect:acc=1"] = acc1StringCon.TrimEnd(',');
                CommandMap["disconnect:acc=1"] = acc1StringDisCon.TrimEnd(',');
                CommandMap["connect:acc=2"] = acc2StringCon.TrimEnd(',');
                CommandMap["disconnect:acc=2"] = acc2StringDisCon.TrimEnd(',');
                CommandMap["disconnect:acc=all"] = acc1StringDisCon + acc2StringDisCon.TrimEnd(',');
            }
        }
        #endregion
        
        public IowCardAccessory()
            : base()
        {
        }

        public IowCardAccessory(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
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
