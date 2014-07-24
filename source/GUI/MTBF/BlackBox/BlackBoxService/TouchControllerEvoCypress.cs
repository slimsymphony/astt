using System;
using System.Collections.Generic;
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
    public class TouchControllerEvoCypress : ITouchController
    {
        private SerialPort port;
        private TouchControllerCypress touchSettings;
        private Thread receiveThread;
        static AutoResetEvent autoEvent;
        private static object comLock = new object();
        private readonly ILog log;

        private int stepX;
        private int stepY;
        //private Stopwatch sw;
        private const int cyMessageLength = 34;

        private string comPort;

        /// <summary>
        /// Initializes the class.
        /// </summary>
        /// <param name="touchSettings"></param>
        public TouchControllerEvoCypress(TouchControllerCypress touchSettings, string comPort)
        {
            this.log = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
            this.comPort = comPort;
            this.touchSettings = touchSettings;
            stepX = (touchSettings.PanelSettings.Xmax - touchSettings.PanelSettings.Xmin) / touchSettings.PanelSettings.ScreenWidth;
            stepY = (touchSettings.PanelSettings.Ymax - touchSettings.PanelSettings.Xmin) / touchSettings.PanelSettings.ScreenHeight;
            autoEvent = new AutoResetEvent(false);

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
                            port.Write(createNewEmptyTouchMessage(), 0, cyMessageLength);
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
                            port.Write(createNewEmptyTouchMessage(), 0, cyMessageLength);
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

        private void touchEvent(string x1, string y1, string x2 = null, string y2 = null)
        {
            byte[] touchMessage = createNewEmptyTouchMessage();
            int rawCoordinatesX = touchSettings.PanelSettings.Xmin + (int.Parse(x1) * stepX);
            int rawCoordinatesY = touchSettings.PanelSettings.Ymin + (int.Parse(y1) * stepY);
            byte[] bytesX = BitConverter.GetBytes(rawCoordinatesX);
            byte[] bytesY = BitConverter.GetBytes(rawCoordinatesY);

            // Add coordinates for finger 1
            touchMessage[5] = bytesX[1];
            touchMessage[6] = bytesX[0];
            touchMessage[7] = bytesY[1];
            touchMessage[8] = bytesY[0];
            // End of finger 1 coordinates.
            touchMessage[9] = 0x15;

            byte amountOfFingers = 1;
            if (x2 != null && y2 != null)
            {
                amountOfFingers++;

                rawCoordinatesX = touchSettings.PanelSettings.Xmin + (int.Parse(x2) * stepX);
                rawCoordinatesY = touchSettings.PanelSettings.Ymin + (int.Parse(y2) * stepY);
                bytesX = BitConverter.GetBytes(rawCoordinatesX);
                bytesY = BitConverter.GetBytes(rawCoordinatesY);

                // Add coordinates for finger 2
                touchMessage[11] = bytesX[1];
                touchMessage[12] = bytesX[0];
                touchMessage[13] = bytesY[1];
                touchMessage[14] = bytesY[0];
                // End of finger 2 coordinates.
                touchMessage[15] = 0x15;
            }

            // Add amount of fingers. If x2 and y2 given, there are two fingers in use.
            touchMessage[4] = amountOfFingers;
            touchMessage[10] = (byte)(0xF + amountOfFingers); // For finger 1, 0x10. For finger 2, 0x11.

            lock (comLock)
            {
                port.Write(touchMessage, 0, cyMessageLength);
            }
        }

        private byte[] createNewEmptyTouchMessage()
        {
            byte[] touchMessage = new byte[cyMessageLength];
            byte[] messageLengthInBytes = BitConverter.GetBytes(cyMessageLength);
            touchMessage[0] = messageLengthInBytes[1];
            touchMessage[1] = messageLengthInBytes[0];
            return touchMessage;
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
            while (true)
            {
                try
                {
                    if (port.BytesToRead >= 2)
                    {
                        byte[] buffer = new byte[2];
                        lock (comLock)
                        {
                            port.Read(buffer, 0, 2);
                        }
                        int response = buffer[1];
                        switch (response)
                        {
                            case 1:
                                autoEvent.Set();
                                this.log.Debug("Atmel ready to send");
                                break;

                            case 2:
                                this.log.Info("Atmel: phone VCC low! PHONE RESET???");
                                break;

                            case 3:
                                this.log.Debug("Atmel reset pin");
                                break;

                            case 4:
                                this.log.Debug("Atmel reset command");
                                break;

                            case 5:
                                this.log.Error("Atmel Error: I2C timeout");
                                Thread.Sleep(1000);
                                autoEvent.Set();
                                break;

                            case 6:
                                this.log.Error("Atmel Error: RS232 timeout");
                                break;

                            case 7:
                                this.log.Info("Atmel sleep mode! PHONE KEYB LOCK ACTIVE???");
                                break;

                            default:
                                this.log.Warn("Unknown command from controller: " + response);
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
