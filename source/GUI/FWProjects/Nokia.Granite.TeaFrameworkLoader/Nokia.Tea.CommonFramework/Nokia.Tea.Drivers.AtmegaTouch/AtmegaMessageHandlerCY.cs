using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO.Ports;
using System.Threading;

namespace Nokia.Tea.CommonFramework.Drivers
{
    internal class AtmegaMessageHandlerCY : BackgroundWorker
    {
        // TODO: Commented out return value handling for speed improvements. If return value handling is needed
        // this needs to be implemented properly
        public delegate void ReturnValueEventHandler(object sender, AtmegeMessageEventArgs e);
        public event ReturnValueEventHandler ReturnValue;

        private SerialPort port;
        private Object lockObject = new Object();
        private Queue<Byte[]> messageQueue = new Queue<Byte[]>();
        private List<Byte> received = new List<Byte>();
        private string hwRevision;

        public AtmegaMessageHandlerCY(string portName, int baudRate, string hwRevision)
        {
            //Thread.CurrentThread.CurrentCulture = BlackBox.GetCulture();
            //Thread.CurrentThread.CurrentUICulture = BlackBox.GetCulture();
            this.port = new SerialPort(portName, baudRate, Parity.None, 8, StopBits.One);
            this.port.Handshake = Handshake.None;
            this.port.Open();
            base.WorkerSupportsCancellation = true;
            this.hwRevision = hwRevision;
        }

        protected override void OnDoWork(DoWorkEventArgs e)
        {
            //Thread.CurrentThread.CurrentCulture = BlackBox.GetCulture();
            //Thread.CurrentThread.CurrentUICulture = BlackBox.GetCulture();
            int num = 0;
            do
            {
                lock (this.lockObject)
                {
                    if (this.messageQueue.Count > 0 && !base.CancellationPending)
                    {
                        byte[] source = this.messageQueue.Dequeue();
#if TRACE_LOG || TRACE_CONSOLE
                        string str = "";
                        foreach (byte num2 in source)
                        {
                            str = str + num2.ToString() + ",";
                        }
#endif
#if TRACE_CONSOLE
                         Console.WriteLine("Touch event to Atmel: " + str);
#endif
#if TRACE_LOG
                        BlackBox.Log("Touch event to Atmel: " + str);
#endif
                        this.port.Write(source, 0, source.Length);
                    }
                }
                if (this.port.BytesToRead > 0 && !base.CancellationPending)
                {
                    this.received.Add((byte) this.port.ReadByte());
                    if (this.received.Count >= 2)
                    {
                        if (num != 0)
                        {
                            if (this.received.Count == num)
                            {
                                Console.WriteLine("Data package received completely");
                                this.received.Clear();
                                num = 0;
                            }
                        }
                        else
                        {
                            int num3 = this.received[0] & 0x80;
                            if (num3 == 0)
                            {
                                num |= this.received[0];
                                num = num << 8;
                                num |= this.received[1];
                            }
                            else
                            {
                                int num4 = this.received[1];
                                switch (num4)
                                {
                                    case 1:
#if TRACE_LOG
                                        BlackBox.Log("Atmel ready to send");
#endif
#if TRACE_CONSOLE
                                        Console.WriteLine("Atmel ready to send");                         
#endif
                                        this.ReturnValue(this, new AtmegeMessageEventArgs(num4));
                                        break;

                                    case 2:
#if TRACE_LOG
                                        BlackBox.Log("Atmel: phone VCC low");
#endif
#if TRACE_CONSOLE
                                        Console.WriteLine("Atmel: phone VCC low");
#endif
                                        //this.ReturnValue(this, new AtmegeMessageEventArgs(num4));
                                        break;

                                    case 3:
#if TRACE_LOG
                                        BlackBox.Log("Atmel reset pin");
#endif
#if TRACE_CONSOLE
                                        Console.WriteLine("Atmel reset pin");
#endif
                                        //this.ReturnValue(this, new AtmegeMessageEventArgs(num4));
                                        break;

                                    case 4:
#if TRACE_LOG
                                        BlackBox.Log("Atmel reset command");
#endif
#if TRACE_CONSOLE
                                        Console.WriteLine("Atmel reset command");
#endif
                                        //this.ReturnValue(this, new AtmegeMessageEventArgs(num4));
                                        break;

                                    case 5:
#if TRACE_LOG
                                        BlackBox.Log("Atmel Error: I2C timeout");
#endif
#if TRACE_CONSOLE
                                        Console.WriteLine("Atmel I2C timeout");
#endif
                                        this.ReturnValue(this, new AtmegeMessageEventArgs(num4));
                                        break;

                                    case 6:
#if TRACE_LOG
                                        BlackBox.Log("Atmel Error: RS232 timeout");
#endif
#if TRACE_CONSOLE
                                        Console.WriteLine("Atmel RS232 timeout");
#endif
                                        //this.ReturnValue(this, new AtmegeMessageEventArgs(num4));
                                        break;

                                    case 7:
#if TRACE_LOG
                                        BlackBox.Log("Atmel sleep mode");
#endif
#if TRACE_CONSOLE
                                        Console.WriteLine("Atmel sleep mode");
#endif
                                        //this.ReturnValue(this, new AtmegeMessageEventArgs(num4));
                                        break;

                                    default:
#if TRACE_LOG
                                        BlackBox.Log("WARNING unknown command from controller: " + num4);
#endif
#if TRACE_CONSOLE
                                        Console.WriteLine("WARNING unknown command from controller: " + num4);
#endif

                                        break;
                                }
                                this.received.Clear();
                                num = 0;
                            }
                        }
                    }
                }
            }
            while (!base.CancellationPending);
            this.received.Clear();
            e.Cancel = true;
        }

        public void Release()
        {
            lock (this.lockObject)
            {
                byte[] item;
                if (this.hwRevision == "Aqua_F1")
                {
                    item = new byte[0x20];
                }
                else
                {
                    item = new byte[0x12];
                }
                item[1] = 0x12;
                this.messageQueue.Enqueue(item);
            }
        }

        public void Send(bool isCommandPackage, byte[] data)
        {
            int num = 2 + data.Length;
            int num2 = 0;
            if (num > 0x8000)
            {
                throw new ArgumentException(string.Format("Can't send more then {0} Bytes", num));
            }
            if (isCommandPackage)
            {
                num2 = 0x8000;
            }
            num2 |= num;
            byte[] bytes = BitConverter.GetBytes(num2);
            List<byte> list = new List<byte>();
            list.Add(bytes[1]);
            list.Add(bytes[0]);
            list.AddRange(data);
            lock (this.lockObject)
            {
                this.messageQueue.Enqueue(list.ToArray());
            }
        }

        public void Close()
        {
            if (port != null)
            {
                port.Close();
                port = null;
            }
        }
    }
}

