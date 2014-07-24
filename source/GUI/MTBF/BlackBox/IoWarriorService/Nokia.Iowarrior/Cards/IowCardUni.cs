// Disable "Missing XML comment for public type or member" warning.
// This file contains only code being accessed through an abstract interface class.
// The public methods are documented in this abstract interface class.
#pragma warning disable 1591

using System;
using System.Collections.Generic;
using System.Text;
using Nokia.Iowarrior;
using System.Text.RegularExpressions;
using System.Threading;

namespace Nokia.Iowarrior.Cards
{
    public sealed class IowCardUniSwitch : IowCard
    {
        private IowBits iowCommandBits = new IowBits(0);
        private String[] commandParameters;       
                      
        public IowCardUniSwitch()
            : base() {}

        public IowCardUniSwitch(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation) { Init(); }
               

        #region Command: open:uni

        public IList<String> Values_Open_Uni
        {
            get { return commandParameters; }
        }

        public IDictionary<String, Object> Execute_Open_Uni(Boolean executeIt, IList<String> parameters)
        {            
            if (executeIt)
            {
                foreach (String parameter in parameters)                
                    SetUniBit(parameter, false);
                                
                IowDevice.WriteOutputs(iowCommandBits);
            }

            return EmptyResult;
        }

        #endregion

        #region Command: close:uni

        public IList<String> Values_Close_Uni
        {
            get { return commandParameters; }
        }

        public IDictionary<String, Object> Execute_Close_Uni(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                foreach (String parameter in parameters)
                    SetUniBit(parameter, true);

                IowDevice.WriteOutputs(iowCommandBits);
            }

            return EmptyResult;
        }

        #endregion

        #region Command: press:uni

        public IList<String> Values_Press_Uni
        {
            get { return new String[] { "relais/delay" }; }
        }

        public IDictionary<String, Object> Execute_Press_Uni(Boolean executeIt, IList<String> parameters)
        {
            Int32 delay = 0;
            String param;
            String pattern = @"(\d{1,2})/(\d+)";
            Regex reg = new Regex(pattern);            
            GroupCollection groups;            
            Match m;            

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    m = reg.Match(parameter);
                    if (!m.Success)
                        throw new ArgumentException(String.Format("Invalid parameter format {0} ( relais Number/delay )", parameter));

                    groups = m.Groups;
                    param = groups[1].Value;
                    delay = Int32.Parse(groups[2].Value);

                    SetUniBit(param, true);
                    IowDevice.WriteOutputs(iowCommandBits);

                    Thread.Sleep(delay);

                    SetUniBit(param, false);
                    IowDevice.WriteOutputs(iowCommandBits);
                }
            }

            return EmptyResult;
        }

        #endregion

        #region private methodes

        private void Init()
        {            
            commandParameters = new String[30];
            for (Int32 i = 0; i < 30; i++)
                commandParameters[i] = (i + 1).ToString();
        }

        private void SetUniBit(String parameter, Boolean value)
        {
            Int32 param = Int32.Parse(parameter);
            if ((param < 0) || (param > 30))
                throw new ArgumentException(String.Format("Parameter value out of rage: {0} (1..30)", param));
            
            iowCommandBits[param + 1] = value;            
        }      
        
        #endregion

        public override void Shutdown() { }

        public override void Reset()
        {
            iowCommandBits = new IowBits(0);
            //enable bit
            iowCommandBits[1] = true;
            IowDevice.WriteOutputs(iowCommandBits);
        }       
    }
}
