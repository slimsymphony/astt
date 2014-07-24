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
    public sealed class IowCardExperimental : IowCard
    {
        public IowCardExperimental()
            : base()
        {
        }

        public IowCardExperimental(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation)
        {
        }

        public override void Shutdown()
        {
            IowDevice.WriteOutputs(new IowBits(0));
        }

        public override void Reset()
        {
            // Do all required to reset the card.
        }

        public IDictionary<String, Object> Execute_Shutdown_Card(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                Shutdown();
            }

            return EmptyResult;
        }

        public IList<String> Values_On_Led
        {
            get { return new String[] { "0", "1", "2", "3", "4", "5", "6", "7" }; }
        }

        public IList<String> Values_Off_Led
        {
            get { return new String[] { "0", "1", "2", "3", "4", "5", "6", "7" }; }
        }

        public IDictionary<String, Object> Execute_On_Led(Boolean executeIt, IList<String> parameters)
        {
            foreach (String s in parameters)
            {
                if (!Values_On_Led.Contains(s))
                    throw new ArgumentException();
            }

            if (executeIt)
            {
                IowBits b = IowDevice.LastOutputs;

                foreach (String s in parameters)
                {
                    Int32 bitNumber = Int32.Parse(s) + 0x20;
                    b[bitNumber] = false;
                }

                IowDevice.WriteOutputs(b);
            }
            return EmptyResult;
        }

        public IDictionary<String, Object> Execute_Off_Led(Boolean executeIt, IList<String> parameters)
        {
            foreach (String s in parameters)
            {
                if (!Values_On_Led.Contains(s))
                    throw new ArgumentException();
            }

            if (executeIt)
            {
                IowBits b = IowDevice.LastOutputs;

                foreach (String s in parameters)
                {
                    Int32 bitNumber = Int32.Parse(s) + 0x20;
                    b[bitNumber] = true;
                }

                IowDevice.WriteOutputs(b);

            }
            
            return EmptyResult;
        }
    }
}
