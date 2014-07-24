using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml.Linq;
using System.Globalization;
using System.Text.RegularExpressions;

namespace Nokia.Tea.Rcms.TypeInterfaces.TouchController
{
    /// <summary>
    /// RMI 4 Paramter
    /// </summary>
    public class RMI4Parameters
    {
        private Byte[] defaultValues;
        private Byte interruptStateRegister;
        private Byte interruptEnableRegister;
        private Byte fingerStateRegister;        
        private Byte deviceCommandRegister;       
        private Byte deviceControlRegister;      
        private Byte deviceStatusRegister;        
        private Int32 numberOfFingers;        
        private Byte manufacturerId;
        private Int32 serialNumber;                
        private Int32 interruptSource;
        private Int32 pulseTime;

        /// <summary>
        /// Initializes a new instance of the <see cref="RMI4Parameters"/> class.
        /// </summary>
        public RMI4Parameters() { }

        /// <summary>
        /// Loads the default values.
        /// </summary>
        /// <param name="registerFile">The register file.</param>
        public void LoadDefaultValues(String registerFile)
        {           

            if (!File.Exists(registerFile))
                throw new FileNotFoundException(registerFile);

            String[] split = registerFile.Split(new Char[] { '.' });

            if (split.Last() == "xml")
                defaultValues = LoadRegisterValues(XElement.Load(registerFile));
            else if (split.Last() == "html")
                defaultValues = LoadDefaultRegisterValues(registerFile);
            else
                throw new ArgumentException("Unknown file format: " + split.Last());

            
            Int32 startpoint = 238;
            List<RMI4Function> functions = new List<RMI4Function>();
            RMI4Function function = null;
            Int32 offset = 0;
            
            for (Int32 i = startpoint; i >= 0; i--)
            {
                if (defaultValues[i] > 0 && (offset == 0))
                {
                    function = new RMI4Function(defaultValues[i]);
                    offset++;
                }
                else
                {
                    if (offset == 0)
                        break;
                    
                    switch (offset)
                    {
                        case 1:
                            function.NumberOfInterruptSources = defaultValues[i];                            
                            offset++;
                            break;
                        case 2:
                            function.DataRegister = defaultValues[i];
                            offset++;
                            break;
                        case 3:
                            function.ControlRegister = defaultValues[i];
                            offset++;
                            break;
                        case 4:
                            function.CommandRegister = defaultValues[i];
                            offset++;
                            break;
                        case 5:
                            function.QueryRegister = defaultValues[i];
                            functions.Add(function);
                            offset = 0;
                            break;
                    }
                }
            }

            foreach (RMI4Function fct in functions)
            {
                switch (fct.Function)
                {
                    // function 11
                    case 17:
                        numberOfFingers = defaultValues[fct.QueryRegister + 1] & 7;
                        fingerStateRegister = fct.DataRegister;

                        break;
                    case 1:
                        deviceStatusRegister = fct.DataRegister;
                        interruptStateRegister = (Byte)(fct.DataRegister + (Byte)1);
                        deviceControlRegister = fct.ControlRegister;
                        interruptEnableRegister = (Byte)(fct.ControlRegister + (Byte)1);
                        deviceCommandRegister = fct.CommandRegister;
                        manufacturerId = defaultValues[fct.QueryRegister];
                        
                        // komisches Format: jeweils 7 bit
                        Int32 sn = defaultValues[fct.QueryRegister + 10];
                        sn = sn << 1;

                        Int32 tmp = defaultValues[fct.QueryRegister + 9];
                        tmp = tmp << 8;

                        sn = sn | tmp;
                        sn = sn >> 1;

                        serialNumber = sn;
                        break;
                }
            }
        }

        /// <summary>
        /// Gets the default register values.
        /// </summary>
        public Byte[] DefaultRegisterValues
        {
            get { return defaultValues; }
        }

        /// <summary>
        /// Gets the interrupt state register.
        /// </summary>
        public Byte InterruptStateRegister
        {
            get { return interruptStateRegister; } 
        }

        /// <summary>
        /// Gets the interrupt enable register.
        /// </summary>
        public Byte InterruptEnableRegister
        {
            get { return interruptEnableRegister; }
        }

        /// <summary>
        /// Gets the finger state register.
        /// </summary>
        public Byte FingerStateRegister
        {
            get { return fingerStateRegister; }
        }

        /// <summary>
        /// Gets the device command register.
        /// </summary>
        public Byte DeviceCommandRegister
        {
            get { return deviceCommandRegister; }
        }

        /// <summary>
        /// Gets the device control register.
        /// </summary>
        public Byte DeviceControlRegister
        {
            get { return deviceControlRegister; }
        }

        /// <summary>
        /// Gets the device status register.
        /// </summary>
        public Byte DeviceStatusRegister
        {
            get { return deviceStatusRegister; }
        }

        /// <summary>
        /// Gets the manufacturer id.
        /// </summary>
        public Byte ManufacturerId
        {
            get { return manufacturerId; }
        }

        /// <summary>
        /// Gets the serial number.
        /// </summary>
        public Int32 SerialNumber
        {
            get { return serialNumber; }
        }

        /// <summary>
        /// Gets or sets the number of fingers.
        /// </summary>
        /// <value>
        /// The number of fingers.
        /// </value>
        public Int32 NumberOfFingers
        {
            set { numberOfFingers = value; }
            get { return numberOfFingers; }
        }

        /// <summary>
        /// Gets or sets the interrupt source.
        /// </summary>
        /// <value>
        /// The interrupt source.
        /// </value>
        public Int32 InterruptSource
        {
            set { interruptSource = value; }
            get { return interruptSource; }
        }

        /// <summary>
        /// Gets or sets the pulse time.
        /// </summary>
        /// <value>
        /// The pulse time.
        /// </value>
        public Int32 PulseTime
        {
            set { pulseTime = value; }
            get { return pulseTime; }
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine("Manufacturer Id:          \t" + manufacturerId.ToString("X"));
            sb.AppendLine("Serial number:            \t" + serialNumber);
            sb.AppendLine("Interrupt state register: \t" + interruptStateRegister.ToString("X"));
            sb.AppendLine("Interrupt enable register:\t" + interruptEnableRegister.ToString("X"));
            sb.AppendLine("Finger state register:    \t" + fingerStateRegister.ToString("X"));
            sb.AppendLine("Device command register:  \t" + deviceCommandRegister.ToString("X"));
            sb.AppendLine("Device control register:  \t" + deviceControlRegister.ToString("X"));
            sb.AppendLine("Device status register:   \t" + deviceStatusRegister.ToString("X"));
            sb.AppendLine("Interrupt Source:         \t" + interruptSource);
            sb.AppendLine("Number of fingers:        \t" + numberOfFingers);
            sb.AppendLine("Pulse Time:               \t" + pulseTime);     

            return sb.ToString();
        }

        /// <summary>
        /// Loads the register values.
        /// </summary>
        /// <param name="data">The data.</param>
        /// <returns></returns>
        private Byte[] LoadRegisterValues(XElement data)
        {
            Byte[] defaultRegisterValues = new Byte[256];

            NumberStyles style = NumberStyles.HexNumber;
            Byte address, registerContent;

            foreach (XElement register in data.Elements())
            {
                address = Byte.Parse(register.Element("Address").Value.Remove(0, 2), style);
                registerContent = Byte.Parse(register.Element("Reset").Value.Remove(0, 2), style);
                defaultRegisterValues[address] = registerContent;
            }

            return defaultRegisterValues;
        }

        private Byte[] LoadDefaultRegisterValues(String fileName)
        {
            Byte[] defaultRegisterValues = new Byte[256*5];//we have 5 pages registers
            NumberStyles style = NumberStyles.HexNumber;
            Regex reg = new Regex(@"<CENTER\b[^>]*>(.*?)</CENTER>");

            String line, val;
            MatchCollection matchList;
            Byte newReg = 0;
            int nPage = 0;
            using (StreamReader sr = new StreamReader(fileName))
            {
                while ((line = sr.ReadLine()) != null)
                {
                    try
                    {
                        if (line.StartsWith(" <TD  title=\"Address"))
                        {
                            matchList = reg.Matches(line);
                            val = matchList[0].Value.Replace("<CENTER>", "").Replace("</CENTER>", "").Remove(0, 2);
                            
                            val = val.Replace("-", "");
                            if (val.Length > 0)
                            {
                                if (val.Substring(0, 2) == "00")//first page
                                {
                                    nPage = 1;
                                    newReg = Byte.Parse(val, style);
                                }
                                else if (val.Substring(0, 2) == "01")//second page
                                {
                                    nPage = 2;
                                    newReg = Byte.Parse(val.Substring(2), style);
                                }
                                else if (val.Substring(0, 2) == "02")//third page
                                {
                                    nPage = 3;
                                    newReg = Byte.Parse(val.Substring(2), style);
                                }
                                else if (val.Substring(0, 2) == "03")//forth page
                                {
                                    nPage = 4;
                                    newReg = Byte.Parse(val.Substring(2), style);
                                }
                                else if (val.Substring(0, 2) == "04")//fifth page
                                {
                                    nPage = 5;
                                    newReg = Byte.Parse(val.Substring(2), style);
                                }                                
                            }
                        }
                        if (line.Contains("title=\"The default value of this register is"))
                        {
                            matchList = reg.Matches(line);
                            val = matchList[0].Value.Replace("<CENTER>", "").Replace("</CENTER>", "").Replace(" ","").Remove(0, 2);
                            
                            val = val.Replace("-", "");

                            if (nPage > 0)
                            {
                                if (val.Length > 0)
                                {
                                    defaultRegisterValues[newReg + (nPage - 1) * 256] = Byte.Parse(val, style);
                                }
                                else
                                {
                                    defaultRegisterValues[newReg + (nPage - 1) * 256] = 0;
                                }
                            }

                            nPage = 0;
                            newReg = 0;
                        }
                    }
                    catch (Exception e)
                    {
                        string str = e.Message;
                    }
                }
            }
            return defaultRegisterValues;
        }
    }    
}
