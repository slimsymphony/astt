using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TestAutomation.Bridge.ScriptingTools;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Stayon modes for the display
    /// </summary>
    public enum StayOnMode
    {
        /// <summary>
        /// Stay always on
        /// </summary>
        Always,
        
        /// <summary>
        /// Don't stay on
        /// </summary>
        Disable,
        
        /// <summary>
        /// Stay on when USB connected
        /// </summary>
        Usb,
        
        /// <summary>
        /// Stay on when crager connected
        /// </summary>
        Charger
    }

    /// <summary>
    /// Power manager interface for the device
    /// </summary>
    public sealed class PowerManager : PythonCallable
    {
        private const string CMD_FORMAT = "svc power stayon {0}";

        private TABConnection m_tab;

        /// <summary>
        /// Internal class constructor
        /// </summary>
        /// <param name="tab"></param>
        internal PowerManager(TABConnection tab)
        {
            m_tab = tab;
        }

        /// <summary>
        /// Sets the display stayon mode for the device.
        /// </summary>
        /// <param name="mode">Stayon moded to use</param>
        public void SetDisplayStayOnMode(StayOnMode mode)
        {
            string modeStr = null;

            switch (mode)
            {
                case StayOnMode.Always :
                    modeStr = "true";
                    break;
                case StayOnMode.Disable :
                    modeStr = "false";
                    break;
                case StayOnMode.Usb :
                    modeStr = "usb";
                    break;
                case StayOnMode.Charger :
                    modeStr = "ac";
                    break;
            }

            var command = string.Format(CMD_FORMAT, modeStr);
            m_tab.Shell.ExecuteCommand(command);
        }
    }
}
