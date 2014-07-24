using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

// Configure log4net using the .config file
[assembly: log4net.Config.XmlConfigurator(Watch = true)]
namespace TemporaryControlUI
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
