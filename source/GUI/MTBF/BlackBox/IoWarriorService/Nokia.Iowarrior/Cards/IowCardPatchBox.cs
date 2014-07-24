// Disable "Missing XML comment for public type or member" warning.
// This file contains only code being accessed through an abstract interface class.
// The public methods are documented in this abstract interface class.
#pragma warning disable 1591

using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.IO;

namespace Nokia.Iowarrior.Cards
{
    public sealed class IowCardPatchBox : IowCard
    {
        public IowCardPatchBox() : base() { }

        public IowCardPatchBox(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation)
        {
            InitCard();
        }

        private void InitCard()
        {
            IowBits bits = new IowBits(0);
            IowDevice.WriteOutputs(bits);
        }
              
        #region Command: close:relay
        public IDictionary<String, Object> Execute_Close_Relay(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            Int32 relay = Int32.Parse(parameters[0]);

            if ((relay < 1) || (relay > 30))
                throw new Exception(String.Format("Number of relay (1..30) is not in range: {0} ", relay));
            
            if (executeIt)
            {
                relay++;
                IowDevice.WriteOutput(relay, true);
            }
            return EmptyResult;
        }
        #endregion     

        #region Command: open:relay
        public IDictionary<String, Object> Execute_Open_Relay(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();

            Int32 relay = Int32.Parse(parameters[0]);

            if ((relay < 1) || (relay > 30))
                throw new Exception(String.Format("Number of relay (1..30) is not in range: {0} ", relay));

            if (executeIt)
            {                
                relay++;
                IowDevice.WriteOutput(relay, false);
            }
            return EmptyResult;
        }
        #endregion     

        #region Command: read:lightbarrier
        public IDictionary<String, Object> Execute_Read_Lightbarrier(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 0)
                throw new ArgumentException();

            if (executeIt)
            {
                Int32 countTrue = 0;
                Int32 countFalse = 0;
                                
                IowDevice.WriteOutput(31, true);                
                Thread.Sleep(100);
                
                for (Int32 i = 0; i < 5; i++)
                {
                    if (IowDevice.ReadInput(31))
                        countTrue++;
                    else
                        countFalse++;

                    Thread.Sleep(100);
                }
//--------- remove it ----------------------------------------------------------------------------------------------

                String logFile = @"c:\temp\voter.txt";

                if (!File.Exists(logFile))
                {
                    using (FileStream fs = File.Create(logFile)) { }
                }

                using (StreamWriter sw = File.AppendText(logFile))
                {
                    String date = DateTime.Now.ToString("yyyy-MM-dd HH.mm.ss.ff");
                    sw.WriteLine(String.Format("{0}:\ttrue: {1}\t\tfalse: {2}", date, countTrue, countFalse));                                    
                }               

//--------- remove it ----------------------------------------------------------------------------------------------

                Dictionary<String, Object> result = new Dictionary<String, Object>();
                // voter: validate result
                if (countTrue > countFalse)
                    result["IsInterrupted"] = false;
                else
                    result["IsInterrupted"] = true;               
               
                return result;
            }
            return EmptyResult;            
        }
        #endregion

        #region Command: read:locksensor
        public IDictionary<String, Object> Execute_Read_Locksensor(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count != 1)
                throw new ArgumentException();
                       
            if (executeIt)
            {
                IowBits bits = IowDevice.LastOutputs;

                for (Int32 i = 24; i <= 29; i++)
                    bits[i] = true;

                IowDevice.WriteOutputs(bits);

                Thread.Sleep(100);                    

                Boolean status1 = false, status2 = false, lockState = false;

                for (Int32 i = 0; i < 10; i++)
                {
                    bits = IowDevice.ReadInputs();

                    switch (Int32.Parse(parameters[0]))
                    {
                        case 1:
                            status1 = bits[24];
                            status2 = bits[25];
                            break;
                        case 2:
                            status1 = bits[26];
                            status2 = bits[27];
                            break;
                        case 3:
                            status1 = bits[28];
                            status2 = bits[29];
                            break;                          
                    }

                    if (status1 && !status2)
                    {                        
                        lockState = true;
                        break;   
                    }

                    if (i == 10)
                        throw new Exception("Can't identify lock sensor state");

                    Thread.Sleep(100);
                }
                Dictionary<String, Object> result = new Dictionary<string, object>();
                result["IsLocked"] = lockState;
                return result;                                   
            }
            return EmptyResult;    
        }
        #endregion
           
        public override void Shutdown()
        {
          
        }

        public override void Reset()
        {
            InitCard();    
        }
    }
}
