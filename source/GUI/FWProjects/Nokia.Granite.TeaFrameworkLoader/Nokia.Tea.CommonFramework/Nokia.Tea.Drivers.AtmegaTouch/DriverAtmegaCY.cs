using System;
using System.Collections.Generic;
using System.Threading;
using Nokia.Tea.CoreFramework.BaseModules.Drivers;
using Nokia.Tea.CoreFramework.ToolBox.Interfaces;

namespace Nokia.Tea.CommonFramework.Drivers
{
    public class DriverAtmegaCY : DriverModule
    {
        private AtmegaMessageHandlerCY atmega;
        private object lockAtmel;
        private object lockCancel;
        private bool cancel;
        private int retVal;
        private string failReason;
        public string HwRevision;

        public DriverAtmegaCY(string moduleId, IToolBox toolBox) : base(moduleId, toolBox)
        {
            this.lockAtmel = new object();
            this.lockCancel = new object();
            this.cancel = false;
            this.retVal = -1;
            this.failReason = string.Empty;
            this.HwRevision = string.Empty;
        }

        private void atmega_ReturnValue(object sender, AtmegeMessageEventArgs eArgs)
        {
            lock (this.lockAtmel)
            {
                // If I2C timeout, but next value is ready to send. Ignore this.
                if (this.retVal == 5 && eArgs.Message == 1)
                {
                    return;
                }
                this.retVal = eArgs.Message;
            }
        }

        public void Close()
        {
            lock (this.lockCancel)
            {
                this.cancel = true;
            }
            if (atmega != null)
            {
                atmega.CancelAsync();
                atmega.Close();
                atmega.ReturnValue -= atmega_ReturnValue;
            }
        }

        public override void InitAtLoad()
        {
            string traceMessage = "Initialize atmega Cypress driver";
            traceMessage += Environment.NewLine + "PortName: " + this.configuration.PortName + Environment.NewLine + "BaudRate: " + this.configuration.BaudRate;
#if TRACE_LOG
            BlackBox.Log(traceMessage);
#endif
            Console.WriteLine(traceMessage);
            this.atmega = new AtmegaMessageHandlerCY(this.configuration.PortName, this.configuration.BaudRate, this.HwRevision);
            this.atmega.ReturnValue += new AtmegaMessageHandlerCY.ReturnValueEventHandler(this.atmega_ReturnValue);
            this.atmega.RunWorkerAsync();
        }

        public int Release()
        {
            // Retry if release fails due to I2C timeout.
            for (int i = 0; i < 50; i++)
            {
                lock (this.lockAtmel)
                {
                    this.retVal = 0;
#if TRACE_LOG
                    BlackBox.Log("Atmega Release");
#endif
                    this.atmega.Release();
                }

                // Implement a timeout for the touch message: If nothing happens within 100 ms, Resend the message.
                int timeOutValue = 0;
                const int sleepMs = 5;
                while (true)
                {
                    lock (this.lockCancel)
                    {
                        if (this.cancel)
                        {
                            return 0;
                        }
                    }
                    lock (this.lockAtmel)
                    {
                        // Ready to send 1
                        if (this.retVal == 1)
                        {
                            return 0;
                        }
                        // I2C Timeout return value = 5
                        if (retVal == 5)
                        {
#if TRACE_LOG || TRACE_LOG_CRITICAL
                            BlackBox.Log("DriverAtmegaCY: I2C timeout in touch release.");
#endif
                            break;
                        }
                        if (timeOutValue >= 200)
                        {
#if TRACE_LOG || TRACE_LOG_CRITICAL
                            BlackBox.Log("DriverAtmegaCY: Send took over 100 ms in touch release.");
#endif
                            break;
                        }
                    }
                    Thread.Sleep(sleepMs);
                    timeOutValue += sleepMs;
                }
            }
            lock (this.lockAtmel)
            {
                retVal = 0;
            }

            return 0;
        }

        private bool sendHelper(byte[] buffer)
        {
            int i2cTimeoutCount = 0;
            int messageTimeoutCount = 0;
            for (int i = 0; i < 50; i++)
            {
                lock (this.lockAtmel)
                {
                    this.retVal = 0;
                    this.atmega.Send(false, buffer);
                }

                // Implement a timeout for the touch message: If nothing happens within 100 ms, Resend the message.
                int timeOutValue = 0;
                const int sleepMs = 5;
                while (true)
                {
                    Thread.Sleep(sleepMs);
                    lock (this.lockAtmel)
                    {
                        // Ready to send 1
                        if (this.retVal == 1)
                        {
                            failReason = string.Empty;
                            return true;
                        }
                        // I2C Timeout return value = 5
                        if (retVal == 5)
                        {
#if TRACE_LOG || TRACE_LOG_CRITICAL
                            BlackBox.Log("DriverAtmegaCY: I2C timeout in sendHelper. buffer = " + buffer);
#endif
                            i2cTimeoutCount++;
                            break;
                        }
                        if (timeOutValue >= 200)
                        {
#if TRACE_LOG || TRACE_LOG_CRITICAL
                            BlackBox.Log("DriverAtmegaCY: Send took over 100 ms in sendHelper. buffer = " + buffer);
#endif
                            messageTimeoutCount++;
                            break;
                        }
                    }
                    timeOutValue += sleepMs;
                }
            }

            lock (this.lockAtmel)
            {
                retVal = 0;
            }
            this.failReason = "ERROR! Atmel driver failed to send touch event! Reason:"; 
            if (i2cTimeoutCount > 0)
            {
                failReason += " I2C timeout occurred " + i2cTimeoutCount + " times.";
            }
            if (messageTimeoutCount > 0)
            {
                failReason += " No 'ready to send' received from Atmel within 200 ms " + messageTimeoutCount + " times.";
            }
            failReason += " Tried to resend the message 50 times.";
            return false;
        }

        public int Send(List<byte[]> messages)
        {
            foreach (byte[] buffer in messages)
            {
                lock (this.lockCancel)
                {
                    if (this.cancel)
                    {
                        return 0;
                    }
                }
                if (!sendHelper(buffer))
                {
                    Console.WriteLine(failReason);
                }
            }

            return 0;
        }

        private DriverAtmegaCYConfiguration configuration
        {
            get
            {
                return (base.GetConfiguration() as DriverAtmegaCYConfiguration);
            }
        }
    }
}

