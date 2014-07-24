// Disable "Missing XML comment for public type or member" warning.
// This file contains only code being accessed through an abstract interface class.
// The public methods are documented in this abstract interface class.
#pragma warning disable 1591

using System;
using System.Threading;
using System.Collections.Generic;

namespace Nokia.Iowarrior.Cards
{
    public sealed class IowCarduSDSwitch : IowCard
    {
        #region parameters

        private const Byte switchAddress = 0x90;

        private const Byte cmdA_on = 0x01;
        private const Byte cmdA_off = 0x11;

        private const Byte cmdB_on = 0x42;
        private const Byte cmdB_off = 0x52;

        private const Byte cmdC_on = 0x24;
        private const Byte cmdC_off = 0x34;

        private const Byte cmdD_on = 0xA8;
        private const Byte cmdD_off = 0xB8;

        private const Byte cmd_none = 0x00;

        #endregion

        public IowCarduSDSwitch() : base() { }

        public IowCarduSDSwitch(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation)
        {
            ExecuteIICCommand(cmdA_off);
            Thread.Sleep(50);
            ExecuteIICCommand(cmdA_on);
            SetIowBit(IowDevice.TranslatePortNameToBitNumber("P0.0"));
        } 
                
        #region Command: connect:mmc
        public IList<String> Values_Connect_Mmc
        {
            get { return new String[] { "1", "a", "2", "b", "3", "c", "4", "d", "0", "none" }; }
        }

        public IDictionary<String, Object> Execute_Connect_Mmc (Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (!Values_Connect_Mmc.Contains(parameters[0]))
                throw new ArgumentException();

            if (executeIt)
            {
                _8Bit bits = new _8Bit();
                
                switch (parameters[0].ToLower())
                {
                    case "1":
                    case "a":
                        ExecuteIICCommand(cmdA_off);
                        Thread.Sleep(50);
                        ExecuteIICCommand(cmdA_on);
                        SetIowBit(IowDevice.TranslatePortNameToBitNumber("P0.0"));
                        break;
                    case "2":
                    case "b":
                        ExecuteIICCommand(cmdB_off);
                        Thread.Sleep(50);
                        ExecuteIICCommand(cmdB_on);
                        SetIowBit(IowDevice.TranslatePortNameToBitNumber("P0.3"));
                        break;
                    case "3":
                    case "c":
                        ExecuteIICCommand(cmdC_off);
                        Thread.Sleep(50);
                        ExecuteIICCommand(cmdC_on);
                        SetIowBit(IowDevice.TranslatePortNameToBitNumber("P0.1"));
                        break;
                    case "4":
                    case "d":
                        ExecuteIICCommand(cmdD_off);
                        Thread.Sleep(50);
                        ExecuteIICCommand(cmdD_on);
                        SetIowBit(IowDevice.TranslatePortNameToBitNumber("P0.2"));   
                        break;  
                    case "0":
                    case "none":
                        ExecuteIICCommand(cmd_none);
                        break;
                    default:
                        throw new ArgumentException();
                }
            }
            return EmptyResult;
        }
        #endregion

        #region Command: disconnect:mmc

        public IDictionary<String, Object> Execute_Disconnect_Mmc(Boolean executeIt, IList<String> parameters)
        {
            return Execute_Connect_Mmc(true, new List<String>() { "0" });
        }

        #endregion

        public override void Shutdown()
        {
            throw new System.NotImplementedException();
        }

        public override void Reset()
        {
            throw new System.NotImplementedException();
        }

        #region private methodes

        private void ExecuteIICCommand(Byte command)
        {
            IowDevice.EnableIic();
            IowDevice.WriteIic(switchAddress, command);
            IowDevice.DisableIic();
        }

        private void SetIowBit(Int32 bit)
        {
            IowBits bits = new IowBits(0);
            bits[bit] = true;
            IowDevice.WriteOutputs(bits);
        }

        #endregion
    }
}
