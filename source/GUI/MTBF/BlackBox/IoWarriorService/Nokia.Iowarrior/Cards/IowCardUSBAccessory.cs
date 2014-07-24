// Disable "Missing XML comment for public type or member" warning.
// This file contains only code being accessed through an abstract interface class.
// The public methods are documented in this abstract interface class.
#pragma warning disable 1591

using System;
using System.Threading;
using System.Collections.Generic;

namespace Nokia.Iowarrior.Cards
{
    public sealed class IowCardUSBAccessory : IowCard
    {
        private IowBits commandBits = new IowBits(0);
        private string currentUsbAcc = string.Empty;

        public IowCardUSBAccessory() : base() { }

        public IowCardUSBAccessory(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation)
        {
            //Reset();
        } 

        #region Command: connect:usb

        public IList<String> Values_Connect_Usb
        {
            get { return new String[] { "1", "a", "2", "b", "3", "c", "4", "d", "0", "none" }; }
        }

        public IDictionary<String, Object> Execute_Connect_Usb(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (!Values_Connect_Usb.Contains(parameters[0]))
                throw new ArgumentException();

            if (executeIt)
            {
                string param = parameters[0];
                if (this.currentUsbAcc != param)
                {
                    switch (param)
                    {
                        case "1":
                        case "a":
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.1")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.3")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.1")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.7")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.5")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.1")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.3")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.5")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.7")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P4.7")] = true;
                            IowDevice.WriteOutputs(commandBits);
                            break;
                        case "2":
                        case "b":
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.1")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.3")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.1")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.7")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.5")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.1")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.3")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.5")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.7")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P4.7")] = true;
                            IowDevice.WriteOutputs(commandBits);
                            break;
                        case "3":
                        case "c":
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.1")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.3")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.1")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.7")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.5")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.1")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.3")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.5")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.7")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P4.7")] = true;
                            IowDevice.WriteOutputs(commandBits);
                            break;
                        case "4":
                        case "d":
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.1")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.3")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.1")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.7")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.5")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.1")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.3")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.5")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.7")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P4.7")] = true;
                            IowDevice.WriteOutputs(commandBits);
                            break;
                        case "0":
                        case "none":
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.1")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.3")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.1")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.7")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.5")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.1")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.3")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.5")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.7")] = true;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = false;
                            commandBits[IowDevice.TranslatePortNameToBitNumber("P4.7")] = false;
                            IowDevice.WriteOutputs(commandBits);
                            break;
                    }
                }
                this.currentUsbAcc = param;
            }
            return EmptyResult;
        }

        #endregion

        #region Command: disconnect:usb

        public IDictionary<String, Object> Execute_Disconnect_Usb (Boolean executeIt, IList<String> parameters)
        {
            return Execute_Connect_Usb(true, new List<String>() { "0" });
        }

        #endregion

        #region Command: connect:av

        public IList<String> Values_Connect_Av
        {
            get { return new String[] { "1", "a", "2", "b", "3", "c", "4", "d", "0", "none" }; }
        }

        public IDictionary<String, Object> Execute_Connect_Av(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (!Values_Connect_Av.Contains(parameters[0].ToLower()))
                throw new ArgumentException();

            if (executeIt)
            {
                switch (parameters[0].ToLower())
                {
                    case "1":
                    case "a":
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.1")] = false;
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.3")] = true;
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.5")] = true;                       
                        IowDevice.WriteOutputs(commandBits);
                        break;
                    case "2":
                    case "b":
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.1")] = false;
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.3")] = false;
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.5")] = true;
                        IowDevice.WriteOutputs(commandBits);
                        break;
                    case "3":
                    case "c":
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.1")] = true;
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.3")] = true;
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.5")] = true;
                        IowDevice.WriteOutputs(commandBits);
                        break;
                    case "4":
                    case "d":
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.1")] = true;
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.3")] = false;
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.5")] = true;
                        IowDevice.WriteOutputs(commandBits);
                        break;
                    case "0":
                    case "none":
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.1")] = false;
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.3")] = false;
                        commandBits[IowDevice.TranslatePortNameToBitNumber("P4.5")] = false;
                        IowDevice.WriteOutputs(commandBits);
                        break;
                }
            }
            return EmptyResult;
        }

        #endregion

        #region command disconnect:av

        public IDictionary<String, Object> Execute_Disconnect_Av (Boolean executeIt, IList<String> parameters)
        {
            return Execute_Connect_Av(true, new List<String>() { "0" });
        }

        #endregion

        public override void Shutdown()
        {
        }

        public override void Reset()
        {
            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.1")] = true;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.3")] = false;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.1")] = true;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.3")] = false;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.7")] = true;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P3.5")] = false;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.1")] = true;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.3")] = true;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.5")] = true;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P5.7")] = true;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.5")] = false;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P2.7")] = false;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P4.7")] = false;

            commandBits[IowDevice.TranslatePortNameToBitNumber("P4.1")] = false;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P4.3")] = false;
            commandBits[IowDevice.TranslatePortNameToBitNumber("P4.5")] = false;
            
            IowDevice.WriteOutputs(commandBits);
        }
    }
}
