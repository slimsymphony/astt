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
    public sealed class IowCardAudio : IowCard
    {
        private String mic1Channel = "disconnect";
        private String mic2Channel = "disconnect";
        
        public IowCardAudio()
            : base()
        {
        }

        public IowCardAudio(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation)
        {
        }

        public override void Shutdown()
        {
            // Do all required to get card in safe state.
        }

        public override void Reset()
        {
            TurnOffVrel();

            // Open all relays
            IowBits bv = IowDevice.LastOutputs;
            for (int i = 2; i < 32; i++)
                bv[i] = false;

            // Close VSense
            bv[29] = true;

            IowDevice.WriteOutputs(bv);
        }

        public IDictionary<String, Object> Execute_Enable_Relays(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                TurnOnVrel();
            }

            return EmptyResult;
        }

        public IDictionary<String, Object> Execute_Disable_Relays(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                TurnOffVrel();
            }

            return EmptyResult;
        }

        public IDictionary<String, Object> Execute_Reset_Card(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                Reset();
            }

            return EmptyResult;
        }

        public IList<String> Values_Loopback_Right
        {
            get { return new String[] { "on", "off" }; }
        }

        public IDictionary<String, Object> Execute_Loopback_Right(Boolean executeIt, IList<String> parameters)
        {
            foreach (String s in parameters)
            {
                if (!Values_Loopback_Right.Contains(s))
                    throw new ArgumentException();
            }

            if (executeIt)
            {
                if (parameters[0] == "on")
                {
                    IowDevice.WriteOutput(16, true);
                }
                else
                {
                    IowDevice.WriteOutput(16, false);
                }
            }

            return EmptyResult;
        }

        public IList<String> Values_Loopback_Left
        {
            get { return new String[] { "on", "off" }; }
        }

        public IDictionary<String, Object> Execute_Loopback_Left(Boolean executeIt, IList<String> parameters)
        {
            foreach (String s in parameters)
            {
                if (!Values_Loopback_Left.Contains(s))
                    throw new ArgumentException();
            }

            if (executeIt)
            {
                if (parameters[0] == "on")
                {
                    IowDevice.WriteOutput(17, true);
                }
                else
                {
                    IowDevice.WriteOutput(17, false);
                }
            }

            return EmptyResult;
        }

        public IList<String> Values_Set_Volume
        {
            get { return new String[] { "outleft,0", "outright,0", "mic1,0", "mic2,0", "outleft,1", "outright,1", "mic1,1", "mic2,1", "outleft,3", "outright,3", "mic1,3", "mic2,3" }; }
        }

        public IDictionary<String, Object> Execute_Set_Volume(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 2)
                throw new ArgumentException("set:volume command needs exactly 2 parameters (target, level)");

            if (!Values_Set_Volume.Contains(parameters[0]+","+parameters[1]))
                throw new ArgumentException();

            Int32 value = Convert.ToInt32(parameters[1]) * 10;

            if (executeIt)
            {
                IowDevice.EnableIic();

                switch (parameters[0])
                {
                    case "mic1":
                        SetMicrophoneVolume(0x50, mic1Channel, value);
                        break;
                    case "mic2":
                        SetMicrophoneVolume(0x54, mic2Channel, value);
                        break;
                    case "outleft":
                        IowDevice.WriteIic(0x52, (byte)(0x21 - (value)));
                        break;
                    case "outright":
                        IowDevice.WriteIic(0x52, (byte)(0x40 + (byte)(0x21 - (value))));
                        break;
                    default:
                        throw (new ArgumentException("Wrong command. Source for volume command was not correct: " + parameters[0]));
                }

                IowDevice.DisableIic();
            }

            return EmptyResult;
        }

        public IList<String> Values_Set_Mic1
        {
            get { return new String[] { "both", "left", "right", "disconnect" }; }
        }

        public IDictionary<String, Object> Execute_Set_Mic1(Boolean executeIt, IList<String> parameters)
        {
            foreach (String s in parameters)
            {
                if (!Values_Set_Mic1.Contains(s))
                    throw new ArgumentException();
            }

            if (executeIt)
            {
                mic1Channel = parameters[0];
            }

            return EmptyResult;
        }

        public IList<String> Values_Set_Mic2
        {
            get { return new String[] { "both", "left", "right", "disconnect" }; }
        }

        public IDictionary<String, Object> Execute_Set_Mic2(Boolean executeIt, IList<String> parameters)
        {
            foreach (String s in parameters)
            {
                if (!Values_Set_Mic2.Contains(s))
                    throw new ArgumentException();
            }

            if (executeIt)
            {
                mic2Channel = parameters[0];
            }

            return EmptyResult;
        }

        private void SetMicrophoneVolume(byte microphone, String channel, Int32 value)
        {
            switch (channel)
            {
                case "both":
                    IowDevice.WriteIic(microphone, (byte)(0x21 - value));
                    IowDevice.WriteIic(microphone, (byte)(0x40 + (0x21 - value)));
                    break;
                case "left":
                    IowDevice.WriteIic(microphone, (byte)(0x21 - value));
                    IowDevice.WriteIic(microphone, (byte)(0x40 + (0x21)));
                    break;
                case "right":
                    IowDevice.WriteIic(microphone, (byte)(0x21));
                    IowDevice.WriteIic(microphone, (byte)(0x40 + (0x21 - value)));
                    break;
                case "disconnect":
                    IowDevice.WriteIic(microphone, (byte)(0x40 + (0x21)));
                    IowDevice.WriteIic(microphone, (byte)(0x21));
                    break;
                default:
                    throw (new ArgumentException("Wrong command. Value for channel was not correct: " + channel));
            }
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

 
            

   