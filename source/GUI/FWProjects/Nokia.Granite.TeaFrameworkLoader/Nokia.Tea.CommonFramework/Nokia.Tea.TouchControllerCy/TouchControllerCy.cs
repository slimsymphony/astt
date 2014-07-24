using System;
using System.Collections.Generic;
using System.Globalization;
using System.Threading;
using Nokia.Tea.CommonFramework.Drivers;
using Nokia.Tea.CoreFramework.BaseModules.Rcms;
using Nokia.Tea.CoreFramework.ToolBox.Interfaces;
using Nokia.Tea.Rcms.TypeInterfaces.TouchController;

namespace Nokia.Tea.CommonFramework.Rcms.TouchControllerCY
{
    public class TouchControllerCy : RcmModule, ITouchController
    {
        private CyMessageData messageData;

        public TouchControllerCy(string moduleId, IToolBox toolBox) : base(moduleId, toolBox)
        {
        }

        public void Close()
        {
            touchControllerDriver.Close();
        }

        public void Open()
        {
            throw new NotImplementedException();
        }

        private int HexStringToInt(string hexVal)
        {
            NumberStyles hexNumber = NumberStyles.HexNumber;
            if (hexVal.StartsWith("0x"))
            {
                hexVal = hexVal.Remove(0, 2);
            }
            return int.Parse(hexVal, hexNumber);
        }

        public override void InitAtLoad()
        {
            string traceMessage = "Cypress Touchcontroller Started";
            Console.WriteLine(traceMessage);
            int xMin = this.HexStringToInt(this.configuration.XMin);
            int xMax = this.HexStringToInt(this.configuration.XMax);
            int yMin = this.HexStringToInt(this.configuration.YMin);
            int yMax = this.HexStringToInt(this.configuration.YMax);
            string[] strArray = this.configuration.ZBytes.Split(new char[] { ',' });
            if (strArray.Length != 4)
            {
                throw new ArgumentException(string.Format("Invalid number of z Bytes: {0} needed: 4", new object[0]));
            }
            List<byte> zList = new List<byte>();
            foreach (string str2 in strArray)
            {
                zList.Add((byte) this.HexStringToInt(str2));
            }
            string hwRevision = string.Empty;
            if (this.configuration.NumberOfFingers == 4)
            {
                hwRevision = "Aqua_F1";
            }

            this.messageData = new CyMessageData(this.configuration.NumberOfFingers, this.configuration.ScreenWidth, this.configuration.ScreenHeight, this.configuration.DisplayOrientation, this.configuration.PulseTime, xMax, xMin, yMax, yMin, zList, hwRevision);
        }

        public IDisposable Lock()
        {
            throw new NotImplementedException();
        }

        public void Move(object[] marbleTouchData)
        {
//            List<MarbleTouchData> touchDataList = new List<MarbleTouchData>();
//            foreach (MarbleTouchData touchData in marbleTouchData)
//            {
//                if (touchData.EventType == "release")
//                {
//#if TRACE_LOG                    
//                    foreach (var data in touchDataList)
//                    {
//                        BlackBox.Log("Executing touch event (X,Y:length): " + data.EventType + " " + data.X + "," + data.Y + ":" + data.Wait);
//                    }
//#endif
//                    this.touchControllerDriver.Send(this.messageData.CalculateMessages(touchDataList.ToArray()));
//                    touchDataList.Clear();
//                    this.touchControllerDriver.Release();
//                    int sleep = int.Parse(touchData.Wait);
//#if TRACE_LOG                    
//                    BlackBox.Log("Wait after touch event: " + sleep);
//#endif
//                    sleep -= 20;
//                    if (sleep > 0)
//                    {
//                        Thread.Sleep(sleep);
//                    }
//                }
//                else
//                {
//                    touchDataList.Add(touchData);
//                }
//            }
        }

        //public void Release(int finger)
        //{
        //    this.touchControllerDriver.Release();
        //}

        public void Reset()
        {
        }

        public void Unlock()
        {
            throw new NotImplementedException();
        }

        private RcmTouchControllerCYConfiguration configuration
        {
            get
            {
                return (base.GetConfiguration() as RcmTouchControllerCYConfiguration);
            }
        }

        public int DefaultSpeed
        {
            get
            {
                return this.messageData.DefaultSpeed;
            }
            set
            {
                this.messageData.DefaultSpeed = value;
            }
        }

        public string Description
        {
            get
            {
                return string.Empty;
            }
        }

        public string Implementation
        {
            get
            {
                return string.Empty;
            }
        }

        public string InstrumentFirmwareRevision
        {
            get
            {
                return string.Empty;
            }
        }

        public string InstrumentModel
        {
            get
            {
                return string.Empty;
            }
        }

        public string IoResourceDescriptor
        {
            get
            {
                return string.Empty;
            }
        }

        public string LogicalName
        {
            get
            {
                return string.Empty;
            }
        }

        public string OwnerIdentification
        {
            get
            {
                return string.Empty;
            }
        }

        public int ScreenHeight
        {
            get
            {
                return this.configuration.ScreenHeight;
            }
        }

        public int ScreenWidth
        {
            get
            {
                return this.configuration.ScreenWidth;
            }
        }

        public string Setup
        {
            get
            {
                return string.Empty;
            }
        }

        private DriverAtmegaCY touchControllerDriver
        {
            get
            {
                return (DriverAtmegaCY)base.GetModule(this.configuration.UsedDriverUid);
            }
        }

        public string Vendor
        {
            get
            {
                return string.Empty;
            }
        }

        public string Version
        {
            get
            {
                return string.Empty;
            }
        }
    }
}

