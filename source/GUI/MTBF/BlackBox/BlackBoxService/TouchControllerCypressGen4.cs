using System;
using System.Collections.Generic;
using System.Diagnostics;
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
    public class TouchControllerCypressGen4 : ITouchController
    {
        private TouchStateResponse touchStateResponse;
        private const byte capacitiveBackPress = 1;
        private const byte capacitiveBackRelease = 2;
        private const byte capacitiveHomePress = 3;
        private const byte capacitiveHomeRelease = 4;
        private const byte touchPress = 5;
        private const byte touchMove = 6;
        private const byte touchRelease = 7;

        private SerialPort port;
        private TouchControllerCypress touchSettings;
        private Thread receiveThread;
        static AutoResetEvent readytoSendEvent;
        private static object comLock = new object();
        private readonly ILog log;
        private Stopwatch sw;

        // Not needed when touch coordinates equals display coordinates
        //private int stepX;
        //private int stepY;
        //private Stopwatch sw;
        private const int cyMessageLength = 34;
        private string comPort;

        private readonly byte[] loop = { 0x00, 0x40, 0x80, 0xc0 };
        private int loopIndex;
        private string touchVersion;
        public string TouchVersion
        {
            get
            {
                lock (comLock)
                {
                    port.Write(new byte[] {0x03, 0x10}, 0, 2);
                }
                Thread.Sleep(250);
                return this.touchVersion;
            }
        }

        /// <summary>
        /// Initializes the class.
        /// </summary>
        /// <param name="touchSettings"></param>
        public TouchControllerCypressGen4(TouchControllerCypress touchSettings, string comPort)
        {
            this.loopIndex = 0;
            this.touchVersion = "";
            this.log = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
            this.comPort = comPort;
            this.touchSettings = touchSettings;
            // Not needed when touch coordinates equals display coordinates
            //stepX = (touchSettings.PanelSettings.Xmax - touchSettings.PanelSettings.Xmin) / touchSettings.PanelSettings.ScreenWidth;
            //stepY = (touchSettings.PanelSettings.Ymax - touchSettings.PanelSettings.Xmin) / touchSettings.PanelSettings.ScreenHeight;
            this.touchStateResponse = new TouchStateResponse();
            readytoSendEvent = new AutoResetEvent(false);

            this.sw = new Stopwatch();
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

            if (readytoSendEvent != null)
                readytoSendEvent.Dispose();
        }

        /// <summary>
        /// Execute a Move or Press touch command.
        /// </summary>
        /// <param name="marbleTouchData"></param>
        public TouchStateResponse Move(List<MarbleTouchData> marbleTouchData)
        {
            TouchStateResponse resp = new TouchStateResponse();
            // Check whether multi finger touch.
            bool multiFinger = marbleTouchData.Any(data => data.TouchId == "1");
            if (!multiFinger)
            {
                // Do not try to send more than one touch event if touch is in sleepmode or phone vcc low
                int eventCount = 0;
                foreach (MarbleTouchData data in marbleTouchData)
                {
                    int wait = int.Parse(data.Wait);
                    log.Debug(data.EventType + " X: " + data.X + " Y: " + data.Y + " Wait: " + data.Wait);
                    
                    // If power off or sleepmode, return immediately.
                    if (eventCount > 0 && this.touchStateResponse.State == TouchState.PowerOffOrSleepMode)
                        return this.touchStateResponse;

                    this.sw.Restart();
                    readytoSendEvent.Reset();

                    // Write touch data
                    touchEvent(data.EventType, data.X, data.Y);
                    waitForReadyToSend();

                    if (this.touchStateResponse.State == TouchState.Warning)
                        resp = this.touchStateResponse;

                    wait -= (int)this.sw.Elapsed.TotalMilliseconds;
                    if (wait > 0)
                        Thread.Sleep(wait);
                    eventCount++;
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

                // Do not try to send more than one touch event if touch is in sleepmode or phone vcc low
                int eventCount = 0;
                foreach (MarbleTouchData data in marbleTouchData)
                {
                    int wait = int.Parse(data.Wait);
                    // Delay between presses can be set to compensate phone slowliness.
                    // Marble whitebox uses 20ms delay between presses. For real phone sw/hw the delay needs to be longer.
                    // If presses are executed too quickly in e.g. virtual keyboard, mispresses will occur.
                    if (wait > 0 && wait < touchSettings.PanelSettings.DelayBetweenPresses)
                        wait = touchSettings.PanelSettings.DelayBetweenPresses;

                    if (data.TouchId == "1")
                    {
                        // If power off or sleepmode, return immediately.
                        if (eventCount > 0 && this.touchStateResponse.State == TouchState.PowerOffOrSleepMode)
                            return this.touchStateResponse;

                        this.sw.Restart();
                        readytoSendEvent.Reset();

                        // Write touch data
                        touchEvent(data.EventType, x1, y1, data.X, data.Y);
                        x1 = null;
                        y1 = null;
                        waitForReadyToSend();

                        if (this.touchStateResponse.State == TouchState.Warning)
                            resp = this.touchStateResponse;

                        wait -= (int)this.sw.Elapsed.TotalMilliseconds;
                        if (wait > 0)
                            Thread.Sleep(wait);

                        eventCount++;
                    }
                    else
                    {
                        x1 = data.X;
                        y1 = data.Y;
                    }
                }
            }

            return resp;
        }

        public TouchStateResponse CapacitiveBack(bool isAra, int delay)
        {
            //Write Transaction	09
            //Read Transaction	04 40 01 00 FF B4 FF A0 FF 00 00 00 00 77*
            //Read Transaction	04 80 01 00 FF E4 FF D8 FF 00 00 F9 FF EB* -->AOL2.0_swu-140603
            //Write Transaction	03
            //Read Transaction	00 00 00 00 00 00*
            //Write Transaction	71
            //Read Transaction	6A 00*
            //Write Transaction	00 00
            //Write Transaction	00
            //Read Transaction	00 00 40*
            //Write Transaction	09
            //Read Transaction	04 80 00 00 FF B7 FF A2 FF 00 00 00 00 76*
            //Write Transaction	03
            //Read Transaction	00 00 00 00 00 00*
            //Write Transaction	71
            //Read Transaction	00 00*
            TouchStateResponse resp = new TouchStateResponse();
            if (isAra)
            {
                byte[] buffer = this.createNewEmptyTouchMessage();

                // Inform Atmel FW that this touch event is a capacitive back key press
                buffer[8] = capacitiveBackPress;
                buffer[9] = 0x04;
                //buffer[10] = 0x40; updated in createNewEmptyTouchMessage
                buffer[11] = 0x01;
                buffer[12] = 0x00;
                buffer[13] = 0xff;
                buffer[14] = 0xe4;
                buffer[15] = 0xff;
                buffer[16] = 0xd8;
                buffer[17] = 0xff;
                buffer[18] = 0x00;
                buffer[19] = 0x00;
                buffer[20] = 0xf9;
                buffer[21] = 0xff;
                buffer[22] = 0xeb;

                this.sw.Restart();

                readytoSendEvent.Reset();
                this.write(buffer);

                waitForReadyToSend();
                // If power off or sleepmode, return immediately.
                if (this.touchStateResponse.State == TouchState.PowerOffOrSleepMode)
                    return this.touchStateResponse;
                if (this.touchStateResponse.State == TouchState.Warning)
                    resp = this.touchStateResponse;

                // Release
                // Inform Atmel FW that this touch event is a capacitive back key release
                buffer[8] = capacitiveBackRelease;
                buffer[10] = generateTouchReportId();
                buffer[11] = 0x00;

                delay -= (int)this.sw.Elapsed.TotalMilliseconds;
                if (delay > 0)
                    Thread.Sleep(delay);
                Thread.Sleep(delay);

                readytoSendEvent.Reset();
                this.write(buffer);
                this.waitForReadyToSend();
                if (this.touchStateResponse.State == TouchState.Warning)
                    resp = this.touchStateResponse;
            }

            return resp;
        }

        public TouchStateResponse CapacitiveHome(bool isAra, int delay)
        {
            //Write Transaction	09
            //Read Transaction	04 C0 04 00 FF B5 FF A0 FF 00 00 00 00 EB*
            //Read Transaction	04 00 04 00 FF E3 FF DA FF 00 00 F8 FF 77* -->AOL2.0_swu-140603
            //Write Transaction	03
            //Read Transaction	00 00 00 00 00 00*
            //Write Transaction	71
            //Read Transaction	00 52*
            //Write Transaction	00 00
            //Write Transaction	00
            //Read Transaction	00 00 40*
            //Write Transaction	09
            //Read Transaction	04 00 00 00 FF B7 FF 9F FF 00 00 00 00 77*
            //Write Transaction	03
            //Read Transaction	00 00 00 00 00 00*
            //Write Transaction	71
            //Read Transaction	00 00*
            TouchStateResponse resp = new TouchStateResponse();
            if (isAra)
            {
                byte[] buffer = this.createNewEmptyTouchMessage();

                // Inform Atmel FW that this touch event is a capacitive home key press
                buffer[8] = capacitiveHomePress;
                buffer[9] = 0x04;
                //buffer[10] = 0xc0; updated in createNewEmptyTouchMessage
                buffer[11] = 0x04;
                buffer[12] = 0x00;
                buffer[13] = 0xff;
                buffer[14] = 0xe3;
                buffer[15] = 0xff;
                buffer[16] = 0xda;
                buffer[17] = 0xff;
                buffer[18] = 0x00;
                buffer[19] = 0x00;
                buffer[20] = 0xf8;
                buffer[21] = 0xff;
                buffer[22] = 0xeb;

                this.sw.Restart();
                readytoSendEvent.Reset();
                this.write(buffer);

                waitForReadyToSend();
                // If power off or sleepmode, return immediately.
                if (this.touchStateResponse.State == TouchState.PowerOffOrSleepMode)
                    return this.touchStateResponse;
                if (this.touchStateResponse.State == TouchState.Warning)
                    resp = this.touchStateResponse;
                
                // Release
                // Inform Atmel FW that this touch event is a capacitive home key release
                buffer[8] = capacitiveHomeRelease;
                buffer[10] = generateTouchReportId();
                buffer[11] = 0x00;

                delay -= (int)this.sw.Elapsed.TotalMilliseconds;
                if (delay > 0)
                    Thread.Sleep(delay);
                Thread.Sleep(delay);

                readytoSendEvent.Reset();
                this.write(buffer);

                this.waitForReadyToSend();
                if (this.touchStateResponse.State == TouchState.Warning)
                    resp = this.touchStateResponse;
            }

            return resp;
        }

        private void touchEvent(string eventType, string x1, string y1, string x2 = null, string y2 = null)
        {
            //Touch coordinates single touch Ara 13w49 --> 09-22
            //Touch coordinates second finger Ara 13w49 --> 23-32
            byte[] bytesX = BitConverter.GetBytes(int.Parse(x1));
            byte[] bytesY = BitConverter.GetBytes(int.Parse(y1));
            byte[] touchMessage = createNewEmptyTouchMessage();

            // Button/Switch Status/Event Register 00 ==> no capacitive button
            touchMessage[11] = 0x00;
            // TOUCH DATA Xh for first finger
            touchMessage[13] = bytesX[1];
            // TOUCH DATA Xl for first finger
            touchMessage[14] = bytesX[0];
            // TOUCH DATA Yh for first finger
            touchMessage[15] = bytesY[1];
            // TOUCH DATA Yl for first finger
            touchMessage[16] = bytesY[0];
            // TOUCH DATA Z for first finger
            touchMessage[17] = 0x3a;

            //Orientation ==> 0 (circle) for first finger
            touchMessage[21] = 0x00;

            byte amountOfFingers = 1;
            
            if (x2 != null && y2 != null)
            {
                amountOfFingers++;

                bytesX = BitConverter.GetBytes(int.Parse(x2));
                bytesY = BitConverter.GetBytes(int.Parse(y2));

                // TOUCH DATA Xh for second finger
                touchMessage[23] = bytesX[1];
                // TOUCH DATA Xl for second finger
                touchMessage[24] = bytesX[0];
                // TOUCH DATA Yh for second finger
                touchMessage[25] = bytesY[1];
                // TOUCH DATA Yl for second finger
                touchMessage[26] = bytesY[0];
                // TOUCH DATA Z for second finger
                touchMessage[27] = 0x3a;

                //Orientation ==> 0 (circle) for second finger
                touchMessage[31] = 0x00;
            }

            // GESTURE ID. Amount of fingers. 01 for finger 0. 0x00 for release (no fingers). 02 for two fingers.
            touchMessage[12] = amountOfFingers;
            byte messageLength = 0x0e;

            if (amountOfFingers == 2)
            {
                messageLength = 0x18;
            }

            if (eventType == "press")
            {
                // Inform Atmel FW that this touch event is a touch press
                touchMessage[8] = touchPress;

                touchMessage[9] = messageLength;
                // EventID, Touch ID ====> 20 == touch press, 40 = move, 60 = release for first finger (0x20h + touch id 0)
                touchMessage[18] = 0x20;            
                // Major Axis ==> length of major axis in pixels for first finger
                touchMessage[19] = 0x0a;
                //Minor Axis ==> length of minor axis in pixels for first finger
                touchMessage[20] = 0x0a;
                if (amountOfFingers == 2)
                {
                    // EventID, Touch ID ====> 21 == touch press, 41 = move, 61 = release for second finger (0x20h + touch id 1)
                    touchMessage[28] = 0x21;            
                    // Major Axis ==> length of major axis in pixels for second finger
                    touchMessage[29] = 0x0a;
                    //Minor Axis ==> length of minor axis in pixels for second finger
                    touchMessage[30] = 0x0a;
                }
            }
            else if (eventType == "move")
            {
                // Inform Atmel FW that this touch event is a touch move
                touchMessage[8] = touchMove;

                touchMessage[9] = messageLength;
                // EventID, Touch ID ====> 20 == touch 0 press, 40 = move, 60 = release
                touchMessage[18] = 0x40;            
                // Major Axis ==> length of major axis in pixels for first finger
                touchMessage[19] = 0x0a;
                //Minor Axis ==> length of minor axis in pixels for first finger
                touchMessage[20] = 0x0a;
                if (amountOfFingers == 2)
                {
                    // EventID, Touch ID ====> 21 == touch press, 41 = move, 61 = release for second finger (0x40h + touch id 1)
                    touchMessage[28] = 0x41;
                    // Major Axis ==> length of major axis in pixels for second finger
                    touchMessage[29] = 0x0a;
                    //Minor Axis ==> length of minor axis in pixels for second finger
                    touchMessage[30] = 0x0a;
                }
            }
            else if (eventType == "release")
            {
                // Inform Atmel FW that this touch event is a touch move
                touchMessage[8] = touchRelease;

                touchMessage[9] = 0x04;
                touchMessage[12] = 0x00;            // GESTURE ID. Amount of fingers. 01 for finger 0. 0x00 for release (no fingers).
                touchMessage[18] = 0x60;            // EventID, Touch ID ====> 20 == touch 0 press, 40 = move, 60 = release
                if (amountOfFingers == 2)
                {
                    // EventID, Touch ID ====> 21 == touch press, 41 = move, 61 = release for second finger (0x60h + touch id 1)
                    touchMessage[28] = 0x61;
                }
            }

            this.write(touchMessage);

        }

        private byte[] createNewEmptyTouchMessage()
        {
            byte[] touchMessage = new byte[cyMessageLength - 2];
            touchMessage[10] = generateTouchReportId();
            return touchMessage;
        }

        private byte generateTouchReportId()
        {
            //Report Status Register: ID tag attached to the current touch report. Incremented each time a new report is presented.
            if (loopIndex == loop.Length)
                loopIndex = 0;

            loopIndex++;
            return loop[loopIndex - 1];
        }

        private void write(byte[] touchMessage)
        {
            // Clear touch state response for nex touch event
            this.touchStateResponse = new TouchStateResponse();
            byte[] messageLengthInBytes = BitConverter.GetBytes(cyMessageLength);
            List<byte> m = new List<byte>(touchMessage);
            m.Insert(0, messageLengthInBytes[0]);
            m.Insert(0, messageLengthInBytes[1]);
            lock (comLock)
            {
                port.Write(m.ToArray(), 0, cyMessageLength);
            }
        }

        private void waitForReadyToSend()
        {
            if (!readytoSendEvent.WaitOne(2000))
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

        private byte[] readBytes()
        {
            lock (comLock)
            {
                if (port.IsOpen && port.BytesToRead >= 2)
                {
                    byte[] buffer = new byte[2];
                    port.Read(buffer, 0, 2);
                    return buffer;
                }
            }
            return null;
        }

        /// <summary>
        /// A worker thread method for touch return values (touch state) reading.
        /// </summary>
        private void receiveThreadMethod()
        {
            bool touchFwBytes = false;
            string versionString = string.Empty;
            int bytesRead = 0;
            while (true)
            {
                try
                {
                    byte[] buffer = this.readBytes();
                    if (buffer != null)
                    {
                        int response = buffer[1];
                        switch (response)
                        {
                            case 1:
                                readytoSendEvent.Set();
                                this.log.Debug("Atmel ready to send");
                                break;

                            case 2:
                                this.touchStateResponse.State = TouchState.PowerOffOrSleepMode;
                                this.touchStateResponse.StateInfo = "Touch VCC low: Phone powered off, keylock activated or touch reset by phone";
                                break;

                            case 4:
                                this.log.Debug("Touch reset pin pulled low by phone");
                                break;

                            case 6:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied touch press coordinates within 50 ms";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            case 7:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied touch move coordinates within 50 ms";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            case 8:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied touch release coordinates within 50 ms";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            case 9:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied capacitive back key press coordinates within 50 ms";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            case 10:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied capacitive back key release coordinates within 50 ms";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            case 11:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied capacitive home key press coordinates within 50 ms";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            case 12:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied capacitive home key release coordinates within 50 ms";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            case 13:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied touch press coordinates within 500 ms!";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            case 14:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied touch release coordinates within 500 ms!";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            case 15:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied capacitive back key press coordinates within 500";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            case 16:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied capacitive back key release coordinates within 500 ms!";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            case 17:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied capacitive home key press coordinates within 500 ms!";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            case 18:
                                this.touchStateResponse.State = TouchState.Warning;
                                this.touchStateResponse.StateInfo = "Phone did not read the supplied capacitive home key release coordinates within 500 ms!";
                                this.log.Info(this.touchStateResponse.StateInfo);
                                break;

                            default:
                                if (buffer[0] == 'F' && buffer[1] == 'w')
                                {
                                    touchFwBytes = true;
                                    bytesRead = 0;
                                    versionString = string.Empty;
                                }
                                else if (touchFwBytes)
                                {
                                    versionString += new string(new[] { (char)buffer[0], (char)buffer[1] });
                                    bytesRead += 2;
                                    if (bytesRead == 6)
                                    {
                                        this.log.Info("Touch FW Version: " + versionString);
                                        this.touchVersion = versionString;
                                        touchFwBytes = false;
                                    }
                                }
                                else
                                {
                                    this.log.Warn("Unknown command from controller: " + response);
                                }
                                break;
                        }
                    }
                    else
                    {
                        Thread.Sleep(10);
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