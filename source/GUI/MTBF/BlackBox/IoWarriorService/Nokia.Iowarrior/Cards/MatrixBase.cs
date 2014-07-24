// Disable "Missing XML comment for public type or member" warning.
// This file contains only code being accessed through an abstract interface class.
// The public methods are documented in this abstract interface class.
#pragma warning disable 1591

using System;
using System.Collections.Generic;
using System.Text;
using Nokia.Iowarrior;
using System.Threading;
using System.Text.RegularExpressions;

namespace Nokia.Iowarrior.Cards
{
    public abstract class MatrixBase : IowCard
    {   
        private Int32 rMax;
        private Int32 cMax;
        private Int32 rMin = 0;
        private Int32 cMin = 0;        
        private Int32 delay = 0;
        private Int32 startbit;

        protected IowBits iowCommandBits = new IowBits(0); 
        protected String[] commandParameters;
        protected Dictionary<String, Int32> commandMap = new Dictionary<String, Int32>();
                
        public MatrixBase() : base() { }

        public MatrixBase(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation, Int32 rMax, Int32 cMax)
            : base(iowDevice, index, iowCardInformation)                
        {
            this.rMax = rMax;
            this.cMax = cMax;
            Init();
        }

        public MatrixBase(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation, Int32 rMax, Int32 cMax, Int32 rMin, Int32 cMin)
            : base(iowDevice, index, iowCardInformation)
        {
            this.rMax = rMax;
            this.cMax = cMax;
            this.rMin = rMin;
            this.cMin = cMin;
            Init();
        } 

        #region Command: close:key

        public IList<String> Values_Close_Key
        {
            get { return commandParameters; }
        }

        public IDictionary<String, Object> Execute_Close_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count < 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    iowCommandBits[InterpreteKeyParameter(parameter)] = true;
                    // Console.WriteLine(String.Format("Close: key: {0} bit: {1}", parameter, InterpreteKeyParameter(parameter)));
                }

                IowDevice.WriteOutputs(iowCommandBits);
            }
            return EmptyResult;
        }

        #endregion

        #region Command: open:key

        public IList<String> Values_Open_Key
        {
            get { return commandParameters; }
        }

        public IDictionary<String, Object> Execute_Open_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count < 1)
                throw new ArgumentException();
            
            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    iowCommandBits[InterpreteKeyParameter(parameter)] = false;
                    //Console.WriteLine(String.Format("Close: key: {0} bit: {1}", parameter.ToLower(), InterpreteKeyParameter(parameter)));
                }

                IowDevice.WriteOutputs(iowCommandBits);
            }
            return EmptyResult;
        }

        #endregion

        #region Command: press:key

        public IList<String> Values_Press_Key
        {
            get { return new String[] { "rx/cx/delay" }; }
        }

        public IDictionary<String, Object> Execute_Press_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count < 1)
                throw new ArgumentException();

            if (executeIt)
            {
                Int32 iowBit;

                foreach (String parameter in parameters)
                {
                    iowBit = InterpretePressKeyParameter(parameter);
                    
                    iowCommandBits[iowBit] = true;
                    IowDevice.WriteOutputs(iowCommandBits);
                    
                    Thread.Sleep(delay);
                   // Console.WriteLine("Sleep... " + delay);
                    
                    iowCommandBits[iowBit] = false;
                    IowDevice.WriteOutputs(iowCommandBits);
                }                
            }
            return EmptyResult;
        }

        #endregion
               
        #region private methodes

        private void Init()
        {
            startbit = IowDevice.TranslatePortNameToBitNumber("P0.2");
            
            List<String> parameterList = new List<String>();
            for (Int32 c = cMin; c < cMax; c++)
                for (Int32 r = rMin; r < rMax; r++)
                {
                    parameterList.Add(String.Format("r{0}/c{1}", r, c));
                    //Console.WriteLine(String.Format("r{0}/c{1}", r, c));
                }
                        
            commandParameters = parameterList.ToArray();
                        
            //enable bit
            iowCommandBits[1] = true;            
            IowDevice.WriteOutputs(iowCommandBits);
        }

        private Int32 InterpreteKeyParameter(String parameter)
        {
            String pattern = @"(r|R)(\d{1,2})/(c|C)(\d{1,2})";
            Regex reg = new Regex(pattern);
            Match m = reg.Match(parameter);

            if (!m.Success)
                throw new ArgumentException("Invalid parameter format ( rx|Rx/cx|Cx )");

            GroupCollection groups = m.Groups;
            Int32 rx = Int32.Parse(groups[2].Value);
            Int32 cx = Int32.Parse(groups[4].Value);            

            if ((rx < rMin) || (rx > rMax) || (cMin < 0) || (cx > cMax))
                throw new ArgumentException(String.Format("Parameter value out of rage: rx({0}..{1}) cx({2}..{3})", rMin, rMax, cMin, cMax));

            // Console.WriteLine("Command: " + parameter);
            // Console.WriteLine("Bit: " + ((rMax - rMin) * cx + (rx - rMin) + startbit));

            return ((rMax - rMin) * cx + (rx - rMin) + startbit);             
        }

        private Int32 InterpretePressKeyParameter(String parameter)
        {
            String pattern = @"(r|R)(\d{1,2})/(c|C)(\d{1,2})/(\d+)";
            Regex reg = new Regex(pattern);                      
            Match m = reg.Match(parameter);

            if (!m.Success)
                throw new ArgumentException("Invalid parameter format ( rx|Rx/cx|Cx/delay )");

            GroupCollection groups = m.Groups;
            Int32 rx = Int32.Parse(groups[2].Value);
            Int32 cx = Int32.Parse(groups[4].Value);
            delay = Int32.Parse(groups[5].Value);

            if ((rx < rMin) || (rMax > 15) || (cMin < 0) || (cMax > 15))
                throw new ArgumentException(String.Format("Parameter value out of rage: rx({0}..{1}) cx({2}..{3})", rMin, rMax, cMin, cMax));            

            return ((rMax - rMin) * cx + rx + startbit);
        }

        #endregion        

        public override void Shutdown() { }

        public override void Reset()
        {
            iowCommandBits = new IowBits(0);
            IowDevice.WriteOutputs(iowCommandBits);
        }
    }
}

        
