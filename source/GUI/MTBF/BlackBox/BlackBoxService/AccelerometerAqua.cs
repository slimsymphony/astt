using System.IO.Ports;

namespace TestAutomation.Gui.Marble.Drivers
{
    public class AccelerometerAqua
    {
        public enum PhoneOrientation
        {
            Portrait,
            Landscape
        }

        public AccelerometerAqua(string comPort, string orientation)
        {
            using (SerialPort port = new SerialPort(comPort, 38400, Parity.None, 8, StopBits.One))
            {
                port.Handshake = Handshake.None;
                port.Open();

                if (port.IsOpen)
                {
                    byte[] bytesToWrite = new byte[8];
                    bytesToWrite[1] = 8;
                    if (orientation == PhoneOrientation.Landscape.ToString())
                    {
                        bytesToWrite[2] = 63;
                    }
                    else
                    {
                        bytesToWrite[3] = 63;
                    }
                    port.Write(bytesToWrite, 0, bytesToWrite.Length);
                    port.Close();
                }
            }
        }
    }
}
