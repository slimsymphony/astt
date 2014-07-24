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
    public sealed class IowCardCapacitiveKeys : IowCard
    {
        public IowCardCapacitiveKeys()
            : base()
        {
        }

        public IowCardCapacitiveKeys(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation)
        {
            // Because we do not know the status of the IOW pins: Reset the outputs of IoWarrior.
            Reset();
        }

        public override void Shutdown()
        {
            Reset();
        }

        public override void Reset()
        {
            // Open all relays
            IowBits bv = IowDevice.LastOutputs;
            for (int i = 2; i < 32; i++)
                bv[i] = false;

            IowDevice.WriteOutputs(bv);
        }

        #region Command: reset:card
        public Dictionary<String, Object> Execute_Reset_Card(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                Reset();
            }

            return EmptyResult;
        }

        #endregion

        #region Command: close:uni
        public IList<String> Values_Close_Uni
        {
            get { 
                List<String> switchList = new List<string>();

                for (int c = 1; c <= 30; c++)
                {
                    switchList.Add(c.ToString());
                }
                return switchList;
            }
        }

        public IDictionary<String, Object> Execute_Close_Uni(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (!Values_Close_Uni.Contains(parameters[0]))
                throw new ArgumentException();

            if (executeIt)
            {
                IowDevice.WriteOutput(Int32.Parse(parameters[0]) + 1, true);
            }

            return EmptyResult;
        }
        #endregion

        #region Command: open:uni
        public IList<String> Values_Open_Uni
        {
            get
            {
                List<String> switchList = new List<string>();

                for (int c = 1; c <= 30; c++)
                {
                    switchList.Add(c.ToString());
                }
                return switchList;
            }
        }

        public IDictionary<String, Object> Execute_Open_Uni(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (!Values_Open_Uni.Contains(parameters[0]))
                throw new ArgumentException();

            if (executeIt)
            {
                IowDevice.WriteOutput(Int32.Parse(parameters[0]) + 1, false);
            }

            return EmptyResult;
        }
        #endregion

        #region Command: close:key
        public IList<String> Values_Close_Key
        {
            get { return new String[] { "arrowup", "arrowdown", "arrowleft", "arrowright"}; }
        }

        public IDictionary<String, Object> Execute_Close_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (!Values_Close_Key.Contains(parameters[0]))
                throw new ArgumentException();

            if (executeIt)
            {
                int bit1 = 0, bit2 = 0;
                switch (parameters[0])
                {
                    case "arrowup":
                        bit1 = 27;
                        bit2 = 28;
                        break;
                    case "arrowdown":
                        bit1 = 29;
                        bit2 = 30;
                        break;
                    case "arrowleft":
                        bit1 = 28;
                        bit2 = 30;
                        break;
                    case "arrowright":
                        bit1 = 27;
                        bit2 = 29;
                        break;
                }
                // Press specific key
                IowBits bv = IowDevice.LastOutputs;
                bv[bit1 + 1] = true;
                bv[bit2 + 1] = true;
                IowDevice.WriteOutputs(bv);

                // Press capacitive keys
                bv[2] = true;
                bv[3] = true;
                IowDevice.WriteOutputs(bv);
            }

            return EmptyResult;
        }
        #endregion

        #region Command: open:key
        public IList<String> Values_Open_Key
        {
            get { return new String[] { "arrowup", "arrowdown", "arrowleft", "arrowright", "select"}; }
        }

        public IDictionary<String, Object> Execute_Open_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (!Values_Open_Key.Contains(parameters[0]))
                throw new ArgumentException();

            if (executeIt)
            {
                int bit1 = 0, bit2 = 0; 
                switch (parameters[0])
                {
                    case "arrowup":
                        bit1 = 27;
                        bit2 = 28;
                        break;
                    case "arrowdown":
                        bit1 = 29;
                        bit2 = 30;
                        break;
                    case "arrowleft":
                        bit1 = 28;
                        bit2 = 30;
                        break;
                    case "arrowright":
                        bit1 = 27;
                        bit2 = 29;
                        break;
                }
                // Release capacitive keys
                IowBits bv = IowDevice.LastOutputs;
                bv[2] = false;
                bv[3] = false;
                IowDevice.WriteOutputs(bv);

                // Release key
                bv[bit1 + 1] = false;
                bv[bit2 + 1] = false;
                IowDevice.WriteOutputs(bv);
            }

            return EmptyResult;
        }

        #endregion
   }
}