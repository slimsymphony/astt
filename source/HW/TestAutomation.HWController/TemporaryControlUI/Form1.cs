using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.NetworkInformation;
using System.Reflection;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using log4net;
using log4net.Appender;
using log4net.Core;
using TestAutomation.Gui.Marble.Settings;
using TestAutomation.HWController.Client;
using TemporaryControlUI.Properties;
using TestAutomation.HWController.Shared;
using System.ComponentModel;

namespace TemporaryControlUI
{
    public partial class Form1 : Form, IHWController
    {
        public class CommunicationModeDataModel : INotifyPropertyChanged
        {
            public int AccessId { get; set; }

            private string communicationMode;

            public string CommunicationMode
            {
                get
                {
                    return communicationMode;
                }

                set
                {
                    communicationMode = value;
                    RaisePropertyChanged("CommunicationMode");
                }
            }

            private void RaisePropertyChanged(string propertyName)
            {
                var temp = PropertyChanged;
                if (temp != null)
                    temp(this, new PropertyChangedEventArgs(propertyName));
            }

            public event PropertyChangedEventHandler PropertyChanged;
        }

        private ILog log = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
        private IPStatus serverStatus;
        private dynamic settings;
        private List<string> powerOnPhoneSequence;
        private readonly BindingList<CommunicationModeDataModel> communicationModes = new BindingList<CommunicationModeDataModel>();

        public Form1()
        {
            InitializeComponent();
            this.communicationModes.Add(new CommunicationModeDataModel() { AccessId = 1, CommunicationMode = "USB" });
            this.communicationModes.Add(new CommunicationModeDataModel() { AccessId = 2, CommunicationMode = "TCP" });
            this.comboBoxConnectionMode.ValueMember = "AccessId";
            this.comboBoxConnectionMode.DisplayMember = "CommunicationMode";
            this.comboBoxConnectionMode.DataSource = this.communicationModes;
        }

        public void Initialize()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.Initialize();
        }

        public void ConnectBatteryCharger()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.ConnectBatteryCharger();
        }
        
        public void ConnectHeadset()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.ConnectHeadset();
        }

        public void ConnectPower()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.ConnectPower();
        }

        public void InsertSIM2()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.InsertSIM2();
        }

        public void ConnectUSBMain()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.ConnectUSBMain();
        }

        public void ConnectUSBChargerMain()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.ConnectUSBChargerMain();
        }

        public void ConnectUSBRemote()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.ConnectUSBRemote();
        }

        public void DisconnectBatteryCharger()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.DisconnectBatteryCharger();
        }

        public void DisconnectHeadset()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.DisconnectHeadset();
        }

        public void DisconnectPower()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.DisconnectPower();
        }

        public void RemoveSIM2()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.RemoveSIM2();
        }

        public void DisconnectUSBMain()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.DisconnectUSBMain();
        }

        public void DisconnectUSBRemote()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.DisconnectUSBRemote();
        }

        public void InsertMemoryCard()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.InsertMemoryCard();
        }

        public void PressKeylockPowerButton(int delay)
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.PressKeylockPowerButton(delay);
        }

        public void RemoveMemoryCard()
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.RemoveMemoryCard();
        }

        public void ConnectExt(int pinId)
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.ConnectExt(pinId);
        }

        public void DisconnectExt(int pinId)
        {
            //this.checkTcpConnection();
            HWControllerClient.Instance.DisconnectExt(pinId);
        }

        public string GetHwStatus()
        {
            //this.checkTcpConnection();
            return HWControllerClient.Instance.GetHwStatus();
        }

        public string GetApplicationVersion()
        {
            //this.checkTcpConnection();
            return HWControllerClient.Instance.GetApplicationVersion();
        }

        private void buttonPingTCP_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(this.textBoxServerIP.Text))
            {
                this.checkTcpConnection();
                this.pingTcp();
            }
            else
            {
                MessageBox.Show("Define IP-Address First!");
            }
        }

        private void textBoxServerIP_TextChanged(object sender, EventArgs e)
        {
            Settings.Default.ServerIP = this.textBoxServerIP.Text;
            Settings.Default.Save();
            if (HWControllerClient.Instance != null)
                HWControllerClient.Instance.ServerAddress = Settings.Default.ServerIP;
        }

        private void numericUpDownTestUnit_ValueChanged(object sender, EventArgs e)
        {
            Settings.Default.TestUnitNumber = (int)this.numericUpDownTestUnit.Value;
            Settings.Default.Save();
            if (HWControllerClient.Instance != null)
                HWControllerClient.Instance.TestUnitNumber = Settings.Default.TestUnitNumber;
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            var textBoxAppender = new TextBoxAppender();
            textBoxAppender.TextBoxName = "textBoxLog";
            textBoxAppender.FormName = "Form1";
            textBoxAppender.Threshold = log4net.Core.Level.All;
            var consoleAppender = new log4net.Appender.ConsoleAppender { Layout = new log4net.Layout.SimpleLayout() };
            var list = new AppenderSkeleton[] { textBoxAppender, consoleAppender };
            log4net.Config.BasicConfigurator.Configure(list);
            this.groupBoxServerCommands.Enabled = false;

            try
            {
                this.settings = SettingsManager.Instance;
                this.startLoadingSettings();
                this.textBoxPowerOnPhoneSequence.Text = this.settings.System.PowerOnPhoneSequence;
                this.powerOnPhoneSequence = this.textBoxPowerOnPhoneSequence.Text.Split(',').ToList();
                this.log.Debug("PowerOnPhoneSequence: " + this.textBoxPowerOnPhoneSequence.Text);
                if (!string.IsNullOrEmpty(this.settings.System.HWAssistedWhiteBoxServerAddress))
                    this.textBoxServerIP.Text = this.settings.System.HWAssistedWhiteBoxServerAddress;
                if (this.settings.System.HWConnectionType == "USB")
                    this.comboBoxConnectionMode.SelectedIndex = 0;
                else
                    this.comboBoxConnectionMode.SelectedIndex = 1;
            }
            catch (Exception)
            {
                this.settings = null;
                // Use hardcoded PowerOnPhoneSequence instead of one from Marble settings
                this.textBoxPowerOnPhoneSequence.Text = "DisconnectUSBMain,DisconnectPower,Sleep:2000,ConnectPower,Sleep:2000,PressKeylockPowerButton:3000,Sleep:2000,ConnectUSBMain";
                this.powerOnPhoneSequence = this.textBoxPowerOnPhoneSequence.Text.Split(',').ToList();
                this.log.Debug("PowerOnPhoneSequence: " + this.textBoxPowerOnPhoneSequence.Text);
                this.log.Info("Marble SettingsManager not available. This is OK if this GUI is being run standalone without Marble.");
                this.textBoxServerIP.Text = Settings.Default.ServerIP;
                this.numericUpDownTestUnit.Value = Settings.Default.TestUnitNumber;
                if (Settings.Default.ConnectionType == "USB")
                    this.comboBoxConnectionMode.SelectedIndex = 0;
                else
                    this.comboBoxConnectionMode.SelectedIndex = 1;
            }

            this.comboBoxConnectionMode_SelectionChangeCommitted(null, null);
        }

        /// <summary>
        /// Begins loading of settings asynchronously.
        /// </summary>
        private void startLoadingSettings()
        {
            string settingsDirectory = System.IO.Path.GetFullPath(@"..\settings");
            Task beginLoadSettingsFromDirectory = SettingsManager.Instance.BeginLoadSettingsFromDirectory(settingsDirectory);
            // Wait for the load to complete
            beginLoadSettingsFromDirectory.Wait();
        }

        private void checkTcpConnection()
        {
            if (!string.IsNullOrEmpty(this.textBoxServerIP.Text))
            {
                HWControllerClient.Instance.Logger = this.log;
                HWControllerClient.Instance.TestUnitNumber = (int)this.numericUpDownTestUnit.Value;
                HWControllerClient.Instance.InitTcpMode(this.textBoxServerIP.Text, 8888);
            }
        }

        private void checkSerialConnection()
        {
            HWControllerClient.Instance.Logger = this.log;
            HWControllerClient.Instance.TestUnitNumber = (int)this.numericUpDownTestUnit.Value;
            try
            {
                string port = HWControllerClient.Instance.InitUsbMode();
                if (!string.IsNullOrEmpty(port))
                {
                    this.log.Info("Auto detected HW Controller USB serial port: " + port);
                }
                else
                {
                    this.log.Error("Unable to auto detect USB serial port. Check connection and drivers");
                }
            }
            catch (Exception ex)
            {
                this.log.Error("Unable to auto detect USB serial port: " + ex.Message);
            }
        }

        private void pingTcp()
        {
            this.log.Info("Ping Server");
            this.serverStatus = HWControllerClient.Instance.PingServer();
            this.groupBoxServerCommands.Enabled = (this.serverStatus == IPStatus.Success);
            this.labelServerStatus.Text = this.serverStatus.ToString();
            if (this.groupBoxServerCommands.Enabled)
            {
                try
                {
                    this.labelApplicationVersion.Text = this.GetApplicationVersion();
                }
                catch (Exception)
                {
                    
                }
            }
        }

        private void pingSerial()
        {
            this.log.Info("Ping USB Serial Port");
            this.labelSerialStatusText.Text = HWControllerClient.Instance.PingUsb();
            if (this.labelSerialStatusText.Text == "OK")
            {
                this.groupBoxServerCommands.Enabled = true;
                try
                {
                    this.labelApplicationVersion.Text = this.GetApplicationVersion();
                }
                catch (Exception)
                {

                }
            }
            else
                this.groupBoxServerCommands.Enabled = true;
        }

        private void buttonTestSerialConnection_Click(object sender, EventArgs e)
        {
            this.checkSerialConnection();
            this.pingSerial();
        }

        private void buttonPowerOnPhone_Click(object sender, EventArgs e)
        {
            foreach (string s in this.powerOnPhoneSequence)
            {
                string[] splitted = s.Split(':');

                if (splitted[0] == "Sleep")
                {
                    this.log.Debug("Sleep " + splitted[1]);
                    Thread.Sleep(int.Parse(splitted[1]));
                }
                else
                {
                    MethodInfo method = this.GetType().GetMethod(splitted[0]);
                    if (splitted.Length == 1)
                        method.Invoke(this, null);
                    else
                        method.Invoke(this, new object[] { int.Parse(splitted[1]) });
                }
            }
        }

        private void buttonInitialize_Click(object sender, EventArgs e)
        {
            this.Initialize();
        }

        private void buttonDisconnectPower_Click(object sender, EventArgs e)
        {
            this.DisconnectPower();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.ConnectPower();
        }

        private void buttonConnectUSBMain_Click(object sender, EventArgs e)
        {
            this.ConnectUSBMain();
        }

        private void buttonDisconnectUSBMain_Click(object sender, EventArgs e)
        {
            this.DisconnectUSBMain();
        }

        private void buttonConnectHeadset_Click(object sender, EventArgs e)
        {
            this.ConnectHeadset();
        }

        private void buttonDisconnectHeadset_Click(object sender, EventArgs e)
        {
            this.DisconnectHeadset();
        }

        private void buttonInsertSIM2_Click(object sender, EventArgs e)
        {
            this.InsertSIM2();
        }

        private void buttonRemoveSIM2_Click(object sender, EventArgs e)
        {
            this.RemoveSIM2();
        }

        private void buttonConnectUSBRemote_Click(object sender, EventArgs e)
        {
            this.ConnectUSBRemote();
        }

        private void buttonDisconnectUSBREmote_Click(object sender, EventArgs e)
        {
            this.DisconnectUSBRemote();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                if (HWControllerClient.Instance != null)
                    HWControllerClient.Instance.Close();
            }
            catch { /* Just let the form close */}
        }

        private void buttonDisconnectBatCardCharger_Click(object sender, EventArgs e)
        {
            this.DisconnectBatteryCharger();
        }

        private void buttonConnectBatCardCharger_Click(object sender, EventArgs e)
        {
            this.ConnectBatteryCharger();
        }

        private void buttonRemoveMemcard_Click(object sender, EventArgs e)
        {
            this.RemoveMemoryCard();
        }

        private void buttonInsertMemcard_Click(object sender, EventArgs e)
        {
            this.InsertMemoryCard();
        }

        private void buttonConnectUSBMainCharger_Click(object sender, EventArgs e)
        {
            this.ConnectUSBChargerMain();
        }

        private void buttonPressKeylockPwrMs_Click(object sender, EventArgs e)
        {
            this.PressKeylockPowerButton((int)this.numericUpDownKeylockPwrMs.Value);
        }

        private void buttonGetHWState_Click(object sender, EventArgs e)
        {
            string hwStatus = this.GetHwStatus();
            if (hwStatus != null)
            {
                var splitted = hwStatus.Split(',');
                foreach (string s in splitted)
                {
                    this.log.Info(s);
                }
            }
        }

        private void buttonDisconnectExt_Click(object sender, EventArgs e)
        {
            this.DisconnectExt((int)this.numericUpDownExt.Value);
        }

        private void buttonConnectExt_Click(object sender, EventArgs e)
        {
            this.ConnectExt((int)this.numericUpDownExt.Value);
        }

        private void textBoxPowerOnPhoneSequence_TextChanged(object sender, EventArgs e)
        {
            this.powerOnPhoneSequence = this.textBoxPowerOnPhoneSequence.Text.Split(',').ToList();
            this.log.Debug("PowerOnPhoneSequence: " + this.textBoxPowerOnPhoneSequence.Text);
        }

        private void comboBoxConnectionMode_SelectionChangeCommitted(object sender, EventArgs e)
        {
            if (this.comboBoxConnectionMode.SelectedIndex == 0)
            {
                this.groupBoxUsbMode.Enabled = true;
                this.groupBoxTcpIpMode.Enabled = false;
                this.checkSerialConnection();
                this.pingSerial();
                Settings.Default.ConnectionType = "USB";
                Settings.Default.Save();
            }
            else
            {
                this.groupBoxTcpIpMode.Enabled = true;
                this.groupBoxUsbMode.Enabled = false;
                this.checkTcpConnection();
                if (!string.IsNullOrEmpty(this.textBoxServerIP.Text))
                    this.pingTcp();
                Settings.Default.ConnectionType = "TCP";
                Settings.Default.Save();
            }
        }
    }

    public class TextBoxAppender : AppenderSkeleton
    {
        private TextBox _textBox;
        public TextBox AppenderTextBox
        {
            get
            {
                return _textBox;
            }
            set
            {
                _textBox = value;
            }
        }
        public string FormName { get; set; }
        public string TextBoxName { get; set; }

        private Control FindControlRecursive(Control root, string textBoxName)
        {
            if (root.Name == textBoxName) return root;
            foreach (Control c in root.Controls)
            {
                Control t = FindControlRecursive(c, textBoxName);
                if (t != null) return t;
            }
            return null;
        }

        protected override void Append(LoggingEvent loggingEvent)
        {
            if (_textBox == null)
            {
                if (String.IsNullOrEmpty(FormName) ||
                    String.IsNullOrEmpty(TextBoxName))
                    return;

                Form form = Application.OpenForms[FormName];
                if (form == null)
                    return;

                _textBox = (TextBox)FindControlRecursive(form, TextBoxName);
                if (_textBox == null)
                    return;

                form.FormClosing += (s, e) => _textBox = null;
            }
            _textBox.Invoke((MethodInvoker)delegate
            {
                _textBox.AppendText(DateTime.Now + ": "  + loggingEvent.RenderedMessage + Environment.NewLine);
            });
        }
    }
}
