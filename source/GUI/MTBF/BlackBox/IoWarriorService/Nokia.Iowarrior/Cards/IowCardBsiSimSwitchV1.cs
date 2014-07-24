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
    public sealed class IowCardBsiSimSwitchV1 : IowCard
    {
        #region parameters

        private String[] ocParameters = { "gnd_rel1", "gnd_rel2", "gnd_rel3", "gnd_rel4", "gnd_rel5", "gnd_rel6", "gnd_rel7", "gnd_rel8", 
                                            "gnd_rel9", "gnd_rel10", "pwronx", "func_r", "navi_r", "navi_m", "navi_l" };

        #endregion
        
        public IowCardBsiSimSwitchV1()
            : base() { Reset(); }

        public IowCardBsiSimSwitchV1(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation) { Reset(); }
        
        #region Command: open:key

        public IList<String> Values_Open_Key
        {
            get { return ocParameters; }
        }

        public IDictionary<String, Object> Execute_Open_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count < 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    if (parameter.StartsWith("gnd_"))
                    {
                        Int32 numberOfRelais = (Int32.Parse(parameter.Remove(0, 7))) - 1;

                        if ((numberOfRelais < 0) || (numberOfRelais > 10))
                            throw new ArgumentException();

                        Int32 commandBit = IowDevice.TranslatePortNameToBitNumber("P1.0") + numberOfRelais;
                        IowDevice.WriteOutput(commandBit, false);
                    }
                    else if (parameter == "func_r")
                    {
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P2.0"), false);
                    }
                    else if (parameter == "navi_r")
                    {
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.6"), false);
                    }
                    else if (parameter == "navi_m")
                    {
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.4"), false);
                    }
                    else if (parameter == "navi_l")
                    {
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.2"), false);
                    }
                    else if (parameter.StartsWith("pwronx"))
                    {
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.0"), false);
                    }
                }
            }
            return EmptyResult;
        }

        #endregion

        #region Command: close:key

        public IList<String> Values_Close_Key
        {
            get { return ocParameters; }
        }

        public IDictionary<String, Object> Execute_Close_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count < 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    if (parameter.StartsWith("gnd_"))
                    {
                        Int32 numberOfRelais = Int32.Parse(parameter.Remove(0, 7)) - 1;

                        if ((numberOfRelais < 0) || (numberOfRelais > 10))
                            throw new ArgumentException();

                        Int32 commandBit = IowDevice.TranslatePortNameToBitNumber("P1.0") + numberOfRelais;
                        IowDevice.WriteOutput(commandBit, true);
                    }
                    else if (parameter == "func_r")
                    {
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P2.0"), true);
                    }
                    else if (parameter == "navi_r")
                    {
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.6"), true);
                    }
                    else if (parameter == "navi_m")
                    {
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.4"), true);
                    }
                    else if (parameter == "navi_l")
                    {
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.2"), true);
                    }
                    else if (parameter.StartsWith("pwronx"))
                    {
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.0"), true);
                    }                  
                }
            }
            return EmptyResult;
        }

        #endregion

        #region Command: press:key

        public IList<String> Values_Press_Key
        {
            get { return new String[] { "pwronx/delay" }; }
        }

        public IDictionary<String, Object> Execute_Press_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            if (executeIt)
            {
                Console.WriteLine(parameters[0]);
                String[] split = parameters[0].Split(new Char[] {'/'});
                if (split.Length != 2)
                    throw new ArgumentException();

                Int32 delay = Int32.Parse(split[1]);

                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.0"), true);
                Thread.Sleep(delay);
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.0"), false);
            }
            return EmptyResult;
        }

        #endregion
        
        #region Command: connect:power
                
        public IDictionary<String, Object> Execute_Connect_Power(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P0.4"), true);             
            }
            return EmptyResult;
        }

        #endregion

        #region Command: disconnect:power

        public IDictionary<String, Object> Execute_Disconnect_Power(Boolean executeIt, IList<String> parameters)
        {          
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P0.4"), false);
            }
            return EmptyResult;
        }

        #endregion

        #region Command: connect:cap

        public IDictionary<String, Object> Execute_Connect_Cap(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P0.6"), true);
            }
            return EmptyResult;
        }

        #endregion

        #region Command: disconnect:cap

        public IDictionary<String, Object> Execute_Disconnect_Cap(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P0.6"), false);
            }
            return EmptyResult;
        }

        #endregion

        #region Command: connect:bsi
        public IList<String> Values_Connect_Bsi
        {
            get { return new String[] { "normal", "local", "test" }; }
        }

        public IDictionary<String, Object> Execute_Connect_Bsi(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count == 0)
                parameters = new String[] { "normal" };

            if (!Values_Connect_Bsi.Contains(parameters[0]))
                throw new ArgumentException();

            if (executeIt) { 
                switch (parameters[0]) {
                    case "normal":
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P0.3"), false);
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P0.2"), false);
                        break;
                    case "local":
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P0.3"), false);
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P0.2"), true);
                        break;
                    case "test":
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P0.3"), true);
                        IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P0.2"), false);
                        break;
                }                
            }
            return EmptyResult;
        }
        #endregion

        #region Command: open:emag

        public IDictionary<String, Object> Execute_Open_Emag(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.2"), false);
            }
            return EmptyResult;
        }

        #endregion

        #region Command: close:emag

        public IDictionary<String, Object> Execute_Close_Emag(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P1.2"), true);
            }
            return EmptyResult;
        }

        #endregion

        public override void Shutdown()
        {
            // Do all required to get card in safe state.
        }

        public override void Reset()
        {
            IowBits bits = new IowBits(0);
            IowDevice.WriteOutputs(bits);
            IowDevice.WriteOutput(IowDevice.TranslatePortNameToBitNumber("P0.1"), true);            
        }        
    }
}

