using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO.Ports;
using System.Linq;
using System.Reflection;
using System.Threading;
using BlackBoxService;
using TestAutomation.Gui.Marble.IPC.Interfaces;
using Nokia.Tea.Rcms.TypeInterfaces.TouchController;
using log4net;

namespace TestAutomation.Gui.Marble.Drivers
{
    public class TouchControllerRMI4 : ITouchController
    {
        private SerialPort port;
        private TouchControllerSynaptics touchSettings;
        private Thread receiveThread;
        static AutoResetEvent autoEvent;
        private static object comLock = new object();
        private readonly ILog log;

        private double stepX;
        private double stepY;
        //private Stopwatch sw;
        private const int cyMessageLength = 34;
        private bool skipMessage = false;

        private RMI4Parameters parameters;

        private string comPort;
        private Byte wPressed = 0x00;
        private Byte zPressed = 0x00;
        private Byte HexStringToByte(String hexVal)
        {
            NumberStyles style = NumberStyles.HexNumber;

            if (hexVal.StartsWith("0x"))
                hexVal = hexVal.Remove(0, 2);

            return Byte.Parse(hexVal, style);
        }

        /// <summary>
        /// Initializes the class.
        /// </summary>
        /// <param name="touchSettings"></param>
        public TouchControllerRMI4(TouchControllerSynaptics touchSettings, string comPort)
        {
            this.log = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
            this.comPort = comPort;
            this.touchSettings = touchSettings;
            stepX = ((double)touchSettings.PanelSettings.Xmax - (double)touchSettings.PanelSettings.Xmin) / (double)touchSettings.PanelSettings.ScreenWidth;
            stepY = ((double)touchSettings.PanelSettings.Ymax - (double)touchSettings.PanelSettings.Xmin) / (double)touchSettings.PanelSettings.ScreenHeight;
            autoEvent = new AutoResetEvent(false);

            this.parameters = new RMI4Parameters();
            parameters.LoadDefaultValues(@"RegisterFiles\" + touchSettings.PanelSettings.RegisterFile);
            parameters.PulseTime = touchSettings.PanelSettings.PulseTime;
            parameters.InterruptSource = touchSettings.PanelSettings.InterruptSource;
            parameters.NumberOfFingers = touchSettings.PanelSettings.NumberOfFingers;

            wPressed = HexStringToByte(touchSettings.PanelSettings.WPressed);
            zPressed = HexStringToByte(touchSettings.PanelSettings.ZPressed);
            
            //sw = new Stopwatch();
            receiveThread = new Thread(receiveThreadMethod);
            receiveThread.CurrentCulture = App.GetCulture();
            receiveThread.CurrentUICulture = App.GetCulture();
            receiveThread.IsBackground = true;
        }

        /// <summary>
        /// Open COM port and start send and receive threads.
        /// </summary>
        public void Open()
        {
            port = new SerialPort(this.comPort, touchSettings.PortSettings.BaudRate, Parity.None, 8, StopBits.One);
            port.Handshake = Handshake.None;
            port.Open();

            if (!receiveThread.IsAlive)
            {
                receiveThread.Start();
            }
        }

        /// <summary>
        /// Close everything: Abort all the threads, close COM port, Dispose AutoResetEvent.
        /// </summary>
        public void Close()
        {
            if (this.receiveThread != null && this.receiveThread.IsAlive)
                receiveThread.Abort();

            if (port != null && port.IsOpen)
                port.Close();

            if (autoEvent != null)
                autoEvent.Dispose();
        }

        /// <summary>
        /// Execute a Move or Press touch command.
        /// </summary>
        /// <param name="marbleTouchData"></param>
        public void Move(List<MarbleTouchData> marbleTouchData)
        {            
            // Check whether multi finger touch.
            bool multiFinger = marbleTouchData.Any(data => data.TouchId == "1");
            if (!multiFinger)
            {
                foreach (MarbleTouchData data in marbleTouchData)
                {
                    int wait = int.Parse(data.Wait);
                    log.Debug(data.EventType + " X: " + data.X + " Y: " + data.Y + " Wait: " + data.Wait);
                    
                    // Delay between presses can be set to compensate phone slowliness.
                    // Marble whitebox uses 20ms delay between presses. For real phone sw/hw the delay needs to be longer.
                    // If presses are executed too quickly in e.g. virtual keyboard, mispresses will occur.
                    if (wait > 0 && wait < touchSettings.PanelSettings.DelayBetweenPresses)
                        wait = touchSettings.PanelSettings.DelayBetweenPresses;

                    if (data.EventType == "release")
                    {
                        // Release all fingers is just an empty touch message.
                        lock (comLock)
                        {
                            touchEvent(data.X, data.Y, null, null, false);
                        }
                        autoEvent.Reset();
                        waitForReadyToSend();
                        Thread.Sleep(wait);
                    }
                    else
                    {             
                        touchEvent(data.X, data.Y);
                        autoEvent.Reset();
                        waitForReadyToSend();
                        Thread.Sleep(wait);
                    }
                }
            }
            else
            {
                // Marble writes multi touch events like this:
                //<press x=\"160\" y=\"160\" touch_id=\"0\" wait=\"0\" /><press x=\"80\" y=\"160\" touch_id=\"1\" wait=\"20\" /><move x=\"143\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"97\" y=\"160\" touch_id=\"1\" wait=\"20\" />
                //<move x=\"142\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"98\" y=\"160\" touch_id=\"1\" wait=\"20\" /><move x=\"141\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"99\" y=\"160\" touch_id=\"1\" wait=\"20\" />
                //<move x=\"140\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"100\" y=\"160\" touch_id=\"1\" wait=\"20\" /><move x=\"139\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"101\" y=\"160\" touch_id=\"1\" wait=\"20\" />
                //<move x=\"138\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"102\" y=\"160\" touch_id=\"1\" wait=\"20\" /><move x=\"137\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"103\" y=\"160\" touch_id=\"1\" wait=\"20\" />
                //<move x=\"136\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"104\" y=\"160\" touch_id=\"1\" wait=\"20\" /><move x=\"135\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"105\" y=\"160\" touch_id=\"1\" wait=\"20\" />
                //<move x=\"134\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"106\" y=\"160\" touch_id=\"1\" wait=\"20\" /><move x=\"133\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"107\" y=\"160\" touch_id=\"1\" wait=\"20\" />
                //<move x=\"132\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"108\" y=\"160\" touch_id=\"1\" wait=\"20\" /><move x=\"131\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"109\" y=\"160\" touch_id=\"1\" wait=\"20\" />
                //<move x=\"130\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"110\" y=\"160\" touch_id=\"1\" wait=\"20\" /><move x=\"129\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"111\" y=\"160\" touch_id=\"1\" wait=\"20\" />
                //<move x=\"128\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"112\" y=\"160\" touch_id=\"1\" wait=\"20\" /><move x=\"127\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"113\" y=\"160\" touch_id=\"1\" wait=\"20\" />
                //<move x=\"126\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"114\" y=\"160\" touch_id=\"1\" wait=\"20\" /><move x=\"125\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"115\" y=\"160\" touch_id=\"1\" wait=\"20\" />
                //<move x=\"124\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"116\" y=\"160\" touch_id=\"1\" wait=\"20\" /><move x=\"123\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"117\" y=\"160\" touch_id=\"1\" wait=\"20\" />
                //<move x=\"122\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"118\" y=\"160\" touch_id=\"1\" wait=\"20\" /><move x=\"121\" y=\"160\" touch_id=\"0\" wait=\"0\" /><move x=\"119\" y=\"160\" touch_id=\"1\" wait=\"20\" />
                //<release x=\"120\" y=\"160\" touch_id=\"0\" wait=\"0\" /><release x=\"120\" y=\"160\" touch_id=\"1\" wait=\"200\" />"

                string x1 = null, y1 = null;
                foreach (MarbleTouchData data in marbleTouchData)
                {
                    int wait = int.Parse(data.Wait);
                    // Delay between presses can be set to compensate phone slowliness.
                    // Marble whitebox uses 20ms delay between presses. For real phone sw/hw the delay needs to be longer.
                    // If presses are executed too quickly in e.g. virtual keyboard, mispresses will occur.
                    if (wait > 0 && wait < touchSettings.PanelSettings.DelayBetweenPresses)
                        wait = touchSettings.PanelSettings.DelayBetweenPresses;

                    if (data.EventType == "release" && data.TouchId == "1")
                    {
                        // Release all fingers is just an empty touch message.
                        lock (comLock)
                        {
                            touchEvent(x1, y1, data.X, data.Y, false);
                        }
                        autoEvent.Reset();
                        waitForReadyToSend();
                        Thread.Sleep(wait);
                    }
                    else
                    {
                        if (data.TouchId == "1")
                        {
                            touchEvent(x1, y1, data.X, data.Y);
                            x1 = null;
                            y1 = null;
                            autoEvent.Reset();
                            waitForReadyToSend();
                            Thread.Sleep(wait);
                        }
                        else
                        {
                            x1 = data.X;
                            y1 = data.Y;
                        }
                    }
                }
            }
        }

        private void touchEvent(string x1, string y1, string x2 = null, string y2 = null, bool pressOrMove = true)
        {
            byte[] touchMessage = createNewEmptyTouchMessage();
            int rawCoordinatesX = (int)((int.Parse(x1) * stepX));
            int rawCoordinatesY = (int)((int.Parse(y1) * stepY));

            byte[] fingerData = CalculateMessageValue(rawCoordinatesX, rawCoordinatesY, this.wPressed, this.zPressed);

            // Finger 1 pressed 0x01h = 0001b
            if (pressOrMove)
            {
                // One finger
                touchMessage[1] = 1;
                touchMessage[3] = fingerData[0];
                touchMessage[4] = fingerData[1];
                touchMessage[5] = fingerData[2];
                touchMessage[6] = fingerData[3];
                touchMessage[7] = fingerData[4];
            }
            else
            {
                touchMessage[1] = 0;
                touchMessage[3] = fingerData[0];
                touchMessage[4] = fingerData[1];
                touchMessage[5] = fingerData[2];
            }
            // Add coordinates for finger 2
            if (x2 != null && y2 != null)
            {
                rawCoordinatesX = (int)((int.Parse(x2) * stepX));
                rawCoordinatesY = (int)((int.Parse(y2) * stepY));

                fingerData = CalculateMessageValue(rawCoordinatesX, rawCoordinatesY, this.wPressed, this.zPressed);
                if (pressOrMove)
                {
                    //Two fingers pressed 0x05h = 0101b
                    touchMessage[1] = 5;
                    touchMessage[8] = fingerData[0];
                    touchMessage[9] = fingerData[1];
                    touchMessage[10] = fingerData[2];
                    touchMessage[11] = fingerData[3];
                    touchMessage[12] = fingerData[4];
                }
                else
                {
                    touchMessage[1] = 0;
                    touchMessage[8] = fingerData[0];
                    touchMessage[8] = fingerData[1];
                    touchMessage[10] = fingerData[2];
                }

                //if (pressOrMove)
                //{
                //    //Two fingers
                //    touchMessage[1] = 4;
                //    touchMessage[9] = fingerData[0];
                //    touchMessage[10] = fingerData[1];
                //    touchMessage[11] = fingerData[2];
                //    touchMessage[12] = fingerData[3];
                //    touchMessage[13] = fingerData[4];
                //}
                //else
                //{
                //    touchMessage[1] = 0;
                //    touchMessage[8] = fingerData[0];
                //    touchMessage[8] = fingerData[1];
                //    touchMessage[10] = fingerData[2];
                //}
            }
            lock (comLock)
            {
                if (!skipMessage)
                {
                    port.Write(touchMessage, 0, this.touchSettings.PortSettings.MessageLength);
                }
                else
                {
                    this.log.Warn("Skip message");
                }
            }
        }

        private byte[] createNewEmptyTouchMessage()
        {
            byte[] touchMessage = new byte[this.touchSettings.PortSettings.MessageLength];
            touchMessage[0] = (Byte)parameters.InterruptSource;
            return touchMessage;
        }

        private Byte[] CalculateMessageValue(Int32 xRaw, Int32 yRaw, Byte w, Byte z)
        {
            Int32 xCoord = (Int32)xRaw << 4;
            Int32 yCoord = (Int32)yRaw << 4;

            Byte[] xBytes = BitConverter.GetBytes(xCoord);
            Byte[] yBytes = BitConverter.GetBytes(yCoord);

            Int32 xLow = xBytes[0] & 240;
            xLow = xLow >> 4;

            Int32 xy = yBytes[0] | xLow;
            Byte[] xyBytes = BitConverter.GetBytes(xy);

            return new Byte[] { xBytes[1], yBytes[1], xyBytes[0], w, z };
        }

        private void waitForReadyToSend()
        {
            if (!autoEvent.WaitOne(3000))
            {
                closeReopenAtmelComPort();
            }
        }

        /// <summary>
        /// Close and reopen COM port on error. Upon failure exception will be thrown.
        /// </summary>
        private void closeReopenAtmelComPort()
        {
            lock (comLock)
            {
                try
                {
                    port.Close();
                }
                catch (Exception ex)
                {

                    string errorMessage = "Atmel COM port error. Unable to close COM port: " + ex.Message;
                    this.log.Error(errorMessage, ex);
                }
                try
                {
                    Open();
                }
                catch (Exception ex)
                {

                    string errorMessage = "Atmel COM port error. Unable to open COM port: " + ex.Message;
                    this.log.Error(errorMessage, ex);
                }
            }
        }

        /// <summary>
        /// A worker thread method for touch return values (touch state) reading.
        /// </summary>
        private void receiveThreadMethod()
        {
            string msg;
            while (true)
            {
                try
                {
                    if (port.BytesToRead > 0)
                    {
                        int response;
                        lock (comLock)
                        {
                            response = port.ReadByte();
                        }
                        switch (response)
                        {
                            case 1:
                                msg = "Controller started";
                                this.log.Debug(msg);
                                break;
                            case 2:
                                msg = "Set startup values, 1 page";
                                if (parameters.DefaultRegisterValues.Count() > 256)
                                {
                                    port.Write(parameters.DefaultRegisterValues, 0, 256);
                                }
                                else
                                {
                                    port.Write(parameters.DefaultRegisterValues, 0, parameters.DefaultRegisterValues.Count());
                                }
                                this.log.Debug(msg);
                                break;
                            case 11:
                                msg = "Set startup values, 5 pages";
                                port.Write(parameters.DefaultRegisterValues, 0, parameters.DefaultRegisterValues.Count());
                                this.log.Debug(msg);
                                break;
                            case 3:
                                msg = "Set special addresses";
                                var special = new Byte[]
                                              {
                                                  parameters.InterruptStateRegister, parameters.FingerStateRegister,
                                                  touchSettings.PortSettings.MessageLength, parameters.InterruptEnableRegister,
                                                  parameters.DeviceCommandRegister, parameters.DeviceControlRegister,
                                                  parameters.DeviceStatusRegister
                                              };
                                port.Write(special, 0, special.Length);
                                this.log.Debug(msg);
                                break;
                            case 4:
                                msg = "VCC Master high detected";
                                this.log.Debug(msg);
                                skipMessage = false;
                                break;
                            case 5:
                                Console.WriteLine("Ready to send");
                                autoEvent.Set();
                                skipMessage = false;
                                break;
                            case 6:
                                msg = "VCC Master low";
                                this.log.Debug(msg);
                                //just print VCC low, don't skip message anymore
                                //skipMessage = true;
                                break;
                            case 7:
                                msg = "Master reset on touch controller";
                                this.log.Debug(msg);
                                skipMessage = true;
                                break;
                            case 8:
                                msg = "Interrupts disabled";
                                Console.WriteLine(msg);
                                break;
                            case 9:
                                //msg = "Timeout: Phone didn't pick up the message in time.";
                                msg = "Sleep mode";
                                this.log.Debug(msg);
                                break;
                            case 10:
                                //msg = "Attention Line Timeout";
                                msg = "I2C Timeout";
                                this.log.Debug(msg);
                                break;
                            case 12:
                                //msg = "reset pin";
                                msg = "Reset pin";
                                this.log.Debug(msg);
                                skipMessage = true;
                                break;
                            case 16://firmware version
                                {
                                    List<byte> buffer2 = new List<byte>();
                                    buffer2.Add((byte)this.port.ReadByte());
                                    buffer2.Add((byte)this.port.ReadByte());
                                    buffer2.Add((byte)this.port.ReadByte());
                                    buffer2.Add((byte)this.port.ReadByte());

                                    //get firmware version
                                    int nProduct = 0;
                                    nProduct |= (int)buffer2[0];
                                    nProduct <<= 8;
                                    nProduct |= (int)buffer2[1];

                                    //third byte: high 4 bit is atmega info; low 4 bit is main version info
                                    int nAtmega = (int)buffer2[2] >> 4;
                                    int nMainVersion = 0x0F & (int)buffer2[2];
                                    int nAtmegaId = 16;
                                    if (nAtmega == 1)
                                    {
                                        nAtmegaId = 32;
                                    }
                                    else if (nAtmega == 2)
                                    {
                                        nAtmegaId = 128;
                                    }
                                    string value = string.Format("Firmware vresion: RM - {0}, V{1}.{2}, Atmega{3}", nProduct, nMainVersion, buffer2[3], nAtmegaId);
                                    this.log.Info(value);
    
                                    break;
                                }
                            //====================the following code just for debug===============
                            case 170://0xAA
                                {
                                    int iRead = port.ReadByte();
                                    string s = string.Format("170(0xAA): 0x{0:X2}", iRead);

                                    this.log.Debug(s);
                                }
                                break;
                            case 85://0x55
                                {
                                    int iRead = port.ReadByte();
                                    string s = string.Format("85(0x55): 0x{0:X2}", iRead);
                                    this.log.Debug(s);
                                }
                                break;
                            //===================================================================
                            default:
                                msg = ("WARNING unknown command from controller: " + response);
                                this.log.Warn(msg);
                                break;

                        }
                    }
                }
                catch (ThreadAbortException)
                {
                    return;
                }
                catch (Exception ex)
                {
                    string errorMessage = "Atmel COM port error. Unable to read from COM port: " + ex.Message;
                    this.log.Error(errorMessage, ex);
                    closeReopenAtmelComPort();
                }
            }
        }
    }
}
