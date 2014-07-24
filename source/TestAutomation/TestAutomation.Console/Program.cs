using Managed.Adb;
using Managed.Adb.Logs;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using TestAutomation.Bridge;
using TestAutomation.Bridge.ScriptingTools;


namespace TestAutomation.Console
{
    class Program
    {
        static TABConnection con;

        static void Main(string[] args)
        {
            /*
            //var deviceList = TABInterface.GetDevices();

            TABConnection tabConn = TABInterface.CreateConnection(TABInterface.DeviceType.EMULATOR);
            //TABConnection tabConn = TABInterface.CreateConnection(TABInterface.DeviceType.HW);

            //tabConn.Touch(298, 192);
            //tabConn.Touch(100, 500);
            //tabConn.Touch(240, 760);

            //tabConn.Input("hello");
            //tabConn.Back();

            //int loops = 2;

            //for (int i = 0; i < loops; i++)
            //{
            //    tabConn.TouchAction(new List<int> { 457, 407, 20, 456, 409, 20, 425, 415, 20, 387, 415, 20, 339, 415, 20, 290, 420, 20, 250, 422, 20, 211, 423, 20, 170, 424, 20, 160, 425, 20 });
            //}

            //return;

            tabConn.GetXMLDump("z:/AoL/shots/display_dump.xml");
            //tabConn.Capture("z:/AoL/shots/shot.png");

            return;
            */

            con = TABInterface.CreateConnection(TABInterface.DeviceType.ANY, true, false, false);

            con.Logger.LogDataReceived += (ld) => System.Console.WriteLine(ld.LocalTimestamp.ToString("HH:mm:ss.ffffff"));

            con.Logger.Start(LogBuffer.All);

            System.Console.ReadKey();

            con.Logger.Stop();

            return;

            var pro = con.ActivityManager.GetActivityByName("com.nokia.pushnotifications.storage");

            var st = DateTime.Now;
            var heap = pro.DumpHeapToStream();// (@"C:\Android\HPROF\storage.hprof");
            System.Console.WriteLine(DateTime.Now.Subtract(st).TotalMilliseconds);
            System.Console.ReadKey();
            return;
            //con = TABInterface.CreateConnection(TABInterface.DeviceType.HW);
            //con = TABInterface.CreateConnection(TABInterface.DeviceType.EMULATOR);
            //con = TABInterface.CreateConnectionWithSerial("35359577CE9700EC");
            //con = TABInterface.CreateConnectionWithSerial("0123456789ABCDEF");
            
            //con.Capture(@"C:\Marble\TestAutomation.Console\bin\Debug\plap.png");
            //con.TestServerClient.Options.LocalArchiveLocation = @"..\..\..\TestAutomation.Server\16\TAServer.jar";
            //con.TestServerClient.Options.ShutDownOnUsbDisconnect = true;
            //con.TestServerClient.ServerPushProgress += TestServerClient_ServerPushProgress;
            
            con.TestServerClient.UiEvent += TestServerClient_UiEvent;
            con.TestServerClient.ServerTrace += TestServerClient_ServerTrace;
            con.TestServerClient.EnableRemoteEvents = true;
            if (con.TestServerClient.Connect())// && con.ScriptingServiceClient.Connect())
            {
                
                dynamic t = con.TestServerClient;
                //System.Console.ReadKey();
              //  System.Console.WriteLine(t.getDoc() as string);
                //t.setOrientationNatural();
                for (int i = 0; i < 1000000; i++ )
                {
                    t.swipe(200, 50, 200, 350, 20);
                    string dump = t.getDump() as string;
                    Thread.Sleep(50);
                    t.swipe(200, 350, 200, 50, 20);

                }
                con.TestServerClient.Disconnect(true);
            }
        }

        static void TestServerClient_ServerPushProgress(int percentage, long transferred, long total)
        {
            System.Console.WriteLine(percentage + "%");
        }

        static void TestServerClient_ServerTrace(string args)
        {
            System.Console.WriteLine("S:" + args);
        }

        static void TestServerClient_UiEvent(Client.AccessibilityEvent args)
        {
            System.Console.WriteLine(args.EventType);
            //args.Text.ForEach(t => System.Console.WriteLine(t));
            //System.Console.WriteLine(args.EventType);
            /*if (true)
            {
                dynamic t = con.TestServerClient;
                System.Console.WriteLine(t.getDump() as string);
            }*/
        }
    }
}
