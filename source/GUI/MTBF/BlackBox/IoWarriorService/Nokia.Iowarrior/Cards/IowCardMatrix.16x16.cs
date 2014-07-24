// This file contains only code being accessed through an abstract interface class.
// The public methods are documented in this abstract interface class.
#pragma warning disable 1591

using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Text.RegularExpressions;
using System.IO;

namespace Nokia.Iowarrior.Cards
{
    public sealed class IowCardMatrix_16x16 : IowCard
    {
        #region parameters

        //SMe: changed for testing reworked card:
        //orig: 11: 0x90, 12: 0x92, 17: 0x94
        private const Byte IC11_Address = 0x90;
        private const Byte IC12_Address = 0x92;     
        private const Byte IC17_Address = 0x94;
        private const Byte digitalRAddress = 0x58;
        private const Int32 defaultDelay = 100;

        #endregion

        private IowBits iowCommandBits = new IowBits(0);        
     
        private _8Bit IC11 = new _8Bit();
        private _8Bit IC12 = new _8Bit();       
        private _8Bit IC17 = new _8Bit();

        // matrix variables
        private _16BitMatrixPoolElement[] matrixPool = new _16BitMatrixPoolElement[5];
               
        // variables 
        private String[] keyCommandParameters;        
        private String[] bsiCommandParameters = new String[] { "normal_tabby", "local_tabby", "test_tabby", "normal_lynx", "local_lynx", "test_lynx" };
        private String[] uniCommandParameters = new String[] { "1", "2", "3", "4", "5", "6", "7", "8" };
        
        public IowCardMatrix_16x16() : base() { }

        public IowCardMatrix_16x16(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation) { Init(); }

        #region Command: connect:bsi

        public IList<String> Values_Connect_Bsi
        {
            get { return bsiCommandParameters; }
        }

        public IDictionary<String, Object> Execute_Connect_Bsi(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt) {
                IC11.P00 = false;
                ExecuteIICommand(IC11_Address, IC11.GetBits());

                if (parameters.Count > 0) {
                    if (Array.IndexOf(bsiCommandParameters, parameters[0]) < 0)
                        throw new ArgumentException();

                    Byte[] data = new Byte[2] { 0, 41 };

                    switch (parameters[0]) {
                        case "normal_tabby":
                            break;
                        case "local_tabby":
                            data[1] = (Byte)238;
                            break;
                        case "test_tabby":
                            data[1] = (Byte)224;
                            break;
                        case "normal_lynx":
                            data[1] = (Byte)60;
                            break;
                        case "local_lynx":
                            data[1] = (Byte)249;
                            break;
                        case "test_lynx":
                            data[1] = (Byte)240;
                            break;
                    }
                    ExecuteIICommand(digitalRAddress, data);

                    IC11.P00 = false;
                    ExecuteIICommand(IC11_Address, IC11.GetBits());
                }
            }
            return EmptyResult;
        }

        #endregion

        #region Command: disconnect:bsi

        public IList<String> Values_Disconnect_Bsi
        {
            get { return bsiCommandParameters; }
        }

        public IDictionary<String, Object> Execute_Disconnect_Bsi(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IC11.P00 = true;
                ExecuteIICommand(IC11_Address, IC11.GetBits());
            }
            return EmptyResult;
        }

        #endregion

        #region Command: close:emag

        public IDictionary<String, Object> Execute_Close_Emag(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IC11.P01 = true;
                ExecuteIICommand(IC11_Address, IC11.GetBits());
            }
            return EmptyResult;
        }

        #endregion

        #region Command: open:emag

        public IDictionary<String, Object> Execute_Open_Emag(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IC11.P01 = false;
                ExecuteIICommand(IC11_Address, IC11.GetBits());
            }
            return EmptyResult;
        }

        #endregion

        #region Command: connect:cap

        public IDictionary<String, Object> Execute_Connect_Cap(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IC11.P02 = true;
                ExecuteIICommand(IC11_Address, IC11.GetBits());
            }
            return EmptyResult;
        }

        #endregion

        #region Command: disconnect:cap

        public IDictionary<String, Object> Execute_Disconnect_Cap(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IC11.P02 = false;
                ExecuteIICommand(IC11_Address, IC11.GetBits());
            }
            return EmptyResult;
        }

        #endregion

        #region Command: connect:power

        public IDictionary<String, Object> Execute_Connect_Power(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IC11.P03 = true;
                ExecuteIICommand(IC11_Address, IC11.GetBits());
            }
            return EmptyResult;
        }

        #endregion

        #region Command: disconnect:power

        public IDictionary<String, Object> Execute_Disconnect_Power(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IC11.P03 = false;
                ExecuteIICommand(IC11_Address, IC11.GetBits());
            }
            return EmptyResult;
        }

        #endregion

        #region Command: connect:helppower

        public IDictionary<String, Object> Execute_Connect_Helppower(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IC11.P04 = true;
                ExecuteIICommand(IC11_Address, IC11.GetBits());
            }
            return EmptyResult;
        }

        #endregion

        #region Command: disconnect:helppower

        public IDictionary<String, Object> Execute_Disconnect_Helppower(Boolean executeIt, IList<String> parameters)
        {
            if (executeIt)
            {
                IC11.P04 = false;
                ExecuteIICommand(IC11_Address, IC11.GetBits());
            }
            return EmptyResult;
        }

        #endregion

        #region Command: close:key

        public IList<String> Values_Close_Key
        {
            get { return keyCommandParameters; }
        }

        public IDictionary<String, Object> Execute_Close_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count < 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    InterpreteParameter(parameter, true);
                }
            }
            return EmptyResult;
        }

        #endregion

        #region Command: open:key

        public IList<String> Values_Open_Key
        {
            get { return keyCommandParameters; }
        }

        public IDictionary<String, Object> Execute_Open_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count < 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    InterpreteParameter(parameter.ToString(), false);
                }
            }
            return EmptyResult;
        }

        #endregion

        #region Command: press:key

        public IList<String> Values_Press_Key
        {
            get { return keyCommandParameters; }
        }

        public IDictionary<String, Object> Execute_Press_Key(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count < 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    Int32 delay = defaultDelay;
                    String[] split = parameter.Split(new Char[] { '/' });

                    if ((split.Length == 3) && (parameter.StartsWith("r")))
                        delay = Int32.Parse(split[2]);
                    else if ((split.Length == 2) && (parameter.StartsWith("r")))
                        delay = defaultDelay;
                    else if (split.Length == 2)
                        delay = Int32.Parse(split[1]);
                    
                    InterpreteParameter(parameter, true);
                    Thread.Sleep(delay);
                    InterpreteParameter(parameter, false);                    
                }
            }
            return EmptyResult;
        }

        #endregion
        
        #region Command: close:uni

        public IList<String> Values_Close_Uni
        {
            get { return uniCommandParameters; }
        }

        public IDictionary<String, Object> Execute_Close_Uni(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count < 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    ExecuteUniCommand(parameter, true);
                }                
            }
            return EmptyResult;
        }

        #endregion

        #region Command: open:uni

        public IList<String> Values_Open_Uni
        {
            get { return uniCommandParameters; }
        }

        public IDictionary<String, Object> Execute_Open_Uni(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count < 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    ExecuteUniCommand(parameter, false);                    
                }
            }
            return EmptyResult;
        }

        #endregion

        #region Command: press:uni

        public IList<String> Values_Press_Uni
        {
            get { return uniCommandParameters; }
        }

        public IDictionary<String, Object> Execute_Press_Uni(Boolean executeIt, IList<String> parameters)
        {
            if (parameters.Count < 1)
                throw new ArgumentException();

            if (executeIt)
            {
                foreach (String parameter in parameters)
                {
                    Int32 delay = defaultDelay;
                    String[] split = parameter.Split(new Char[] { '/' });

                    if (split.Length == 2)
                        delay = Int32.Parse(split[1]);

                    ExecuteUniCommand(parameter, true);          
                    Thread.Sleep(delay);
                    ExecuteUniCommand(parameter, false);          
                }
            }
            return EmptyResult;
        }

        #endregion
                
        public override void Shutdown()
        {
        }

        public override void Reset()
        {
        }

        #region private methodes

        private void Init()
        {               
            Int32 P00 = IowDevice.TranslatePortNameToBitNumber("P0.0");
            Int32 P10 = IowDevice.TranslatePortNameToBitNumber("P1.0");
            Int32 P20 = IowDevice.TranslatePortNameToBitNumber("P2.0");
            Int32 P30 = IowDevice.TranslatePortNameToBitNumber("P3.0");
            Int32 P40 = IowDevice.TranslatePortNameToBitNumber("P4.0");
            Int32 P50 = IowDevice.TranslatePortNameToBitNumber("P5.0");

            matrixPool[0] = new _16BitMatrixPoolElement(new _16BitMatrix(P30, P50 + 6, P50 + 4, P30 + 2, P10, P10 + 2, P10 + 4, P50 + 2, P10 + 6));
            matrixPool[1] = new _16BitMatrixPoolElement(new _16BitMatrix(P40 + 2, P40, P30 + 6, P40 + 4, P20 + 2, P20, P40 + 6, P30 + 4, P20 + 4));
            matrixPool[2] = new _16BitMatrixPoolElement(new _16BitMatrix(P00 + 4, P00 + 2, P00, P00 + 7, P00 + 1, P00 + 3, P00 + 5, P20 + 6, P00 + 6));
            matrixPool[3] = new _16BitMatrixPoolElement(new _16BitMatrix(P20 + 3, P20 + 5, P20 + 7, P40 + 5, P30 + 7, P40 + 1, P40 + 3, P40 + 7, P20 + 1));
            matrixPool[4] = new _16BitMatrixPoolElement(new _16BitMatrix(P30 + 1, P30 + 3, P30 + 5, P50 + 3, P10 + 1, P10 + 3, P50 + 1, P50 + 5, P50 + 7));
            
            // create parameter list for key parameters 
            List<String> commandList = new List<String>();

            for (Int32 i = 1; i < 9; i++)
            {
                commandList.Add("gnd_rel" + i);                
            }
                        
            commandList.Add("rx/cx");
            commandList.Add("pwronx");

            keyCommandParameters = commandList.ToArray();
                        
            IowDevice.WriteOutputs(iowCommandBits);
            IowDevice.EnableIic();

            // disable BSI
            IC11.P00 = true;
            ExecuteIICommand(IC11_Address, IC11.GetBits());
        }
               
        private void InterpreteParameter(String parameter, Boolean isCloseCommand)
        {
            if (parameter.StartsWith("r"))
            {
                ExecuteMatrixCommand(parameter, isCloseCommand);
            }
            else if (parameter.StartsWith("gnd_rel"))
            {
                ExecuteGndCommand(parameter, isCloseCommand);
            }
            else if (parameter == "pwronx")
            {
                ExecuteGndCommand("gnd_rel1", isCloseCommand);
            }
            else
                throw new Exception();
        }
                     
        private void ExecuteMatrixCommand(String parameter, Boolean isCloseCommand)
        {

            String pattern = @"(r|R)(\d{1,2})/(c|C)(\d{1,2})";
            Regex reg = new Regex(pattern);
            Match m = reg.Match(parameter);

            if (!m.Success)
                throw new ArgumentException("Invalid matrix parameter format ( rx|Rx/cx|Cx )");

            GroupCollection groups = m.Groups;
            Int32 rx = Int32.Parse(groups[2].Value);
            Int32 cx = Int32.Parse(groups[4].Value);

            if ((rx < 0) || (rx > 15) || (cx < 0) || (cx > 15))
                throw new ArgumentException("Matrix parameter value out of rage: rx(0..15) cx(0..15)");

            if (isCloseCommand)
            {
                if (IsMatrixPoolFull())
                {
                    throw new Exception("Only 5 matrices available");
                }

                for (Int32 i = 0; i < matrixPool.Length; i++)
                {
                    if (!matrixPool[i].IsActive)
                    {
                        matrixPool[i].Key = parameter;
                        matrixPool[i].IsActive = true;
                        matrixPool[i].Matrix.SetCodeBit((Byte)rx, (Byte)cx);
                        iowCommandBits[matrixPool[i].Matrix.MatixEnableBit] = true;

                        foreach (var codeBit in matrixPool[i].Matrix.CodeBits)
                        {
                            iowCommandBits[codeBit.Key] = codeBit.Value;
                        }
                        IowDevice.WriteOutputs(iowCommandBits);
                        break;
                    }
                }                
            }
            else
            {
                for (Int32 i = 0; i < matrixPool.Length; i++)
                {
                    if (matrixPool[i].Key == parameter)
                    {
                        matrixPool[i].Key = "";
                        matrixPool[i].IsActive = false;
                        iowCommandBits[matrixPool[i].Matrix.MatixEnableBit] = false;
                        IowDevice.WriteOutput(matrixPool[i].Matrix.MatixEnableBit, false);
                        break;
                    }
                }
            }
        }

        private void ExecuteGndCommand(String parameter, Boolean isCloseCommand)
        {
            Int32 relais = Int32.Parse(parameter.Remove(0, 7));

            if ((relais < 1) || (relais > 8))
                throw new ArgumentException("Parameter value out of rage: (1..8)");

            IC17.SetBit((relais - 1), isCloseCommand);
            ExecuteIICommand(IC17_Address, IC17.GetBits());
        }

        private void ExecuteUniCommand(String parameter, Boolean isCloseCommand)
        {
            try
            {
                Int32 relais = Int32.Parse(parameter);

                if ((relais < 1) || (relais > 8))
                    throw new ArgumentException("Parameter value out of rage: (1..8)");

                IC12.SetBit((relais - 1), isCloseCommand);
                ExecuteIICommand(IC12_Address, IC12.GetBits());
            }
            catch
            {
                throw new ArgumentException();
            }
        }

        private Boolean IsMatrixPoolFull()
        {
            Boolean result = true;           

            foreach(_16BitMatrixPoolElement element in matrixPool)
            {                
                if (!element.IsActive)
                {
                    result = false;
                    break;
                }                
            }           
            
            return result;
        }      

        // -- Vorsicht prüfen, ob IIC enabled
                     
        private void ExecuteIICommand(Byte iicAddress, Byte data)
        {
            if (!IowDevice.IsInSpecialModeIic)
                IowDevice.EnableIic();

            IowDevice.WriteIic(iicAddress, data);            
        }

        private void ExecuteIICommand(Byte iicAddress, Byte[] data)
        {
            if (!IowDevice.IsInSpecialModeIic)
                IowDevice.EnableIic();

            IowDevice.WriteIic(iicAddress, data);         
        }        

        #endregion      
    }
}



