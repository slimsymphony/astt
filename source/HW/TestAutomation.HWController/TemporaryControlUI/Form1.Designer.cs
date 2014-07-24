namespace TemporaryControlUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.textBoxServerIP = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.textBoxLog = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.numericUpDownTestUnit = new System.Windows.Forms.NumericUpDown();
            this.groupBoxServerCommands = new System.Windows.Forms.GroupBox();
            this.textBoxPowerOnPhoneSequence = new System.Windows.Forms.TextBox();
            this.buttonGetHWState = new System.Windows.Forms.Button();
            this.numericUpDownKeylockPwrMs = new System.Windows.Forms.NumericUpDown();
            this.buttonPressKeylockPwrMs = new System.Windows.Forms.Button();
            this.buttonConnectExt = new System.Windows.Forms.Button();
            this.buttonDisconnectExt = new System.Windows.Forms.Button();
            this.numericUpDownExt = new System.Windows.Forms.NumericUpDown();
            this.buttonConnectUSBMainCharger = new System.Windows.Forms.Button();
            this.buttonInsertMemcard = new System.Windows.Forms.Button();
            this.buttonRemoveMemcard = new System.Windows.Forms.Button();
            this.buttonConnectBatCardCharger = new System.Windows.Forms.Button();
            this.buttonDisconnectBatCardCharger = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.buttonDisconnectPower = new System.Windows.Forms.Button();
            this.buttonRemoveSIM2 = new System.Windows.Forms.Button();
            this.buttonInsertSIM2 = new System.Windows.Forms.Button();
            this.buttonDisconnectHeadset = new System.Windows.Forms.Button();
            this.buttonConnectHeadset = new System.Windows.Forms.Button();
            this.buttonDisconnectUSBREmote = new System.Windows.Forms.Button();
            this.buttonConnectUSBRemote = new System.Windows.Forms.Button();
            this.buttonDisconnectUSBMain = new System.Windows.Forms.Button();
            this.buttonConnectUSBMain = new System.Windows.Forms.Button();
            this.buttonInitialize = new System.Windows.Forms.Button();
            this.buttonPowerOnPhone = new System.Windows.Forms.Button();
            this.labelApplicationVersion = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.labelServerStatus = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBoxTcpIpMode = new System.Windows.Forms.GroupBox();
            this.groupBoxStatus = new System.Windows.Forms.GroupBox();
            this.groupBoxUsbMode = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.labelSerialStatusText = new System.Windows.Forms.Label();
            this.buttonTestSerialConnection = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.comboBoxConnectionMode = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTestUnit)).BeginInit();
            this.groupBoxServerCommands.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownKeylockPwrMs)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownExt)).BeginInit();
            this.groupBoxTcpIpMode.SuspendLayout();
            this.groupBoxStatus.SuspendLayout();
            this.groupBoxUsbMode.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBoxServerIP
            // 
            this.textBoxServerIP.Location = new System.Drawing.Point(11, 34);
            this.textBoxServerIP.Name = "textBoxServerIP";
            this.textBoxServerIP.Size = new System.Drawing.Size(221, 20);
            this.textBoxServerIP.TabIndex = 0;
            this.textBoxServerIP.TextChanged += new System.EventHandler(this.textBoxServerIP_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(170, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "IP Address of HWController Server";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(238, 30);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 24);
            this.button1.TabIndex = 2;
            this.button1.Text = "Ping Server";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.buttonPingTCP_Click);
            // 
            // textBoxLog
            // 
            this.textBoxLog.Location = new System.Drawing.Point(12, 266);
            this.textBoxLog.Multiline = true;
            this.textBoxLog.Name = "textBoxLog";
            this.textBoxLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxLog.Size = new System.Drawing.Size(1088, 449);
            this.textBoxLog.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(7, 12);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(90, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Test Unit Number";
            // 
            // numericUpDownTestUnit
            // 
            this.numericUpDownTestUnit.Location = new System.Drawing.Point(10, 31);
            this.numericUpDownTestUnit.Maximum = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.numericUpDownTestUnit.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownTestUnit.Name = "numericUpDownTestUnit";
            this.numericUpDownTestUnit.Size = new System.Drawing.Size(58, 20);
            this.numericUpDownTestUnit.TabIndex = 6;
            this.numericUpDownTestUnit.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownTestUnit.ValueChanged += new System.EventHandler(this.numericUpDownTestUnit_ValueChanged);
            // 
            // groupBoxServerCommands
            // 
            this.groupBoxServerCommands.Controls.Add(this.textBoxPowerOnPhoneSequence);
            this.groupBoxServerCommands.Controls.Add(this.buttonGetHWState);
            this.groupBoxServerCommands.Controls.Add(this.numericUpDownKeylockPwrMs);
            this.groupBoxServerCommands.Controls.Add(this.buttonPressKeylockPwrMs);
            this.groupBoxServerCommands.Controls.Add(this.buttonConnectExt);
            this.groupBoxServerCommands.Controls.Add(this.buttonDisconnectExt);
            this.groupBoxServerCommands.Controls.Add(this.numericUpDownExt);
            this.groupBoxServerCommands.Controls.Add(this.buttonConnectUSBMainCharger);
            this.groupBoxServerCommands.Controls.Add(this.buttonInsertMemcard);
            this.groupBoxServerCommands.Controls.Add(this.buttonRemoveMemcard);
            this.groupBoxServerCommands.Controls.Add(this.buttonConnectBatCardCharger);
            this.groupBoxServerCommands.Controls.Add(this.buttonDisconnectBatCardCharger);
            this.groupBoxServerCommands.Controls.Add(this.button2);
            this.groupBoxServerCommands.Controls.Add(this.buttonDisconnectPower);
            this.groupBoxServerCommands.Controls.Add(this.buttonRemoveSIM2);
            this.groupBoxServerCommands.Controls.Add(this.buttonInsertSIM2);
            this.groupBoxServerCommands.Controls.Add(this.buttonDisconnectHeadset);
            this.groupBoxServerCommands.Controls.Add(this.buttonConnectHeadset);
            this.groupBoxServerCommands.Controls.Add(this.buttonDisconnectUSBREmote);
            this.groupBoxServerCommands.Controls.Add(this.buttonConnectUSBRemote);
            this.groupBoxServerCommands.Controls.Add(this.buttonDisconnectUSBMain);
            this.groupBoxServerCommands.Controls.Add(this.buttonConnectUSBMain);
            this.groupBoxServerCommands.Controls.Add(this.buttonInitialize);
            this.groupBoxServerCommands.Controls.Add(this.buttonPowerOnPhone);
            this.groupBoxServerCommands.Location = new System.Drawing.Point(12, 66);
            this.groupBoxServerCommands.Name = "groupBoxServerCommands";
            this.groupBoxServerCommands.Size = new System.Drawing.Size(1088, 194);
            this.groupBoxServerCommands.TabIndex = 7;
            this.groupBoxServerCommands.TabStop = false;
            // 
            // textBoxPowerOnPhoneSequence
            // 
            this.textBoxPowerOnPhoneSequence.Location = new System.Drawing.Point(11, 164);
            this.textBoxPowerOnPhoneSequence.Name = "textBoxPowerOnPhoneSequence";
            this.textBoxPowerOnPhoneSequence.Size = new System.Drawing.Size(1071, 20);
            this.textBoxPowerOnPhoneSequence.TabIndex = 33;
            this.textBoxPowerOnPhoneSequence.TextChanged += new System.EventHandler(this.textBoxPowerOnPhoneSequence_TextChanged);
            // 
            // buttonGetHWState
            // 
            this.buttonGetHWState.Location = new System.Drawing.Point(680, 123);
            this.buttonGetHWState.Name = "buttonGetHWState";
            this.buttonGetHWState.Size = new System.Drawing.Size(119, 23);
            this.buttonGetHWState.TabIndex = 32;
            this.buttonGetHWState.Text = "Get HW State";
            this.buttonGetHWState.UseVisualStyleBackColor = true;
            this.buttonGetHWState.Click += new System.EventHandler(this.buttonGetHWState_Click);
            // 
            // numericUpDownKeylockPwrMs
            // 
            this.numericUpDownKeylockPwrMs.Location = new System.Drawing.Point(455, 135);
            this.numericUpDownKeylockPwrMs.Maximum = new decimal(new int[] {
            30000,
            0,
            0,
            0});
            this.numericUpDownKeylockPwrMs.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.numericUpDownKeylockPwrMs.Name = "numericUpDownKeylockPwrMs";
            this.numericUpDownKeylockPwrMs.Size = new System.Drawing.Size(116, 20);
            this.numericUpDownKeylockPwrMs.TabIndex = 31;
            this.numericUpDownKeylockPwrMs.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // buttonPressKeylockPwrMs
            // 
            this.buttonPressKeylockPwrMs.Location = new System.Drawing.Point(322, 132);
            this.buttonPressKeylockPwrMs.Name = "buttonPressKeylockPwrMs";
            this.buttonPressKeylockPwrMs.Size = new System.Drawing.Size(127, 23);
            this.buttonPressKeylockPwrMs.TabIndex = 30;
            this.buttonPressKeylockPwrMs.Text = "Press Keylock Pwr (ms)";
            this.buttonPressKeylockPwrMs.UseVisualStyleBackColor = true;
            this.buttonPressKeylockPwrMs.Click += new System.EventHandler(this.buttonPressKeylockPwrMs_Click);
            // 
            // buttonConnectExt
            // 
            this.buttonConnectExt.Location = new System.Drawing.Point(172, 132);
            this.buttonConnectExt.Name = "buttonConnectExt";
            this.buttonConnectExt.Size = new System.Drawing.Size(91, 23);
            this.buttonConnectExt.TabIndex = 29;
            this.buttonConnectExt.Text = "Connect Ext";
            this.buttonConnectExt.UseVisualStyleBackColor = true;
            this.buttonConnectExt.Click += new System.EventHandler(this.buttonConnectExt_Click);
            // 
            // buttonDisconnectExt
            // 
            this.buttonDisconnectExt.Location = new System.Drawing.Point(11, 135);
            this.buttonDisconnectExt.Name = "buttonDisconnectExt";
            this.buttonDisconnectExt.Size = new System.Drawing.Size(91, 23);
            this.buttonDisconnectExt.TabIndex = 28;
            this.buttonDisconnectExt.Text = "Disconnect Ext";
            this.buttonDisconnectExt.UseVisualStyleBackColor = true;
            this.buttonDisconnectExt.Click += new System.EventHandler(this.buttonDisconnectExt_Click);
            // 
            // numericUpDownExt
            // 
            this.numericUpDownExt.Location = new System.Drawing.Point(108, 135);
            this.numericUpDownExt.Maximum = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.numericUpDownExt.Name = "numericUpDownExt";
            this.numericUpDownExt.Size = new System.Drawing.Size(58, 20);
            this.numericUpDownExt.TabIndex = 27;
            // 
            // buttonConnectUSBMainCharger
            // 
            this.buttonConnectUSBMainCharger.Location = new System.Drawing.Point(680, 77);
            this.buttonConnectUSBMainCharger.Name = "buttonConnectUSBMainCharger";
            this.buttonConnectUSBMainCharger.Size = new System.Drawing.Size(165, 23);
            this.buttonConnectUSBMainCharger.TabIndex = 26;
            this.buttonConnectUSBMainCharger.Text = "Connect USB Main As Charger";
            this.buttonConnectUSBMainCharger.UseVisualStyleBackColor = true;
            this.buttonConnectUSBMainCharger.Click += new System.EventHandler(this.buttonConnectUSBMainCharger_Click);
            // 
            // buttonInsertMemcard
            // 
            this.buttonInsertMemcard.Location = new System.Drawing.Point(322, 106);
            this.buttonInsertMemcard.Name = "buttonInsertMemcard";
            this.buttonInsertMemcard.Size = new System.Drawing.Size(127, 23);
            this.buttonInsertMemcard.TabIndex = 25;
            this.buttonInsertMemcard.Text = "Insert MemCard";
            this.buttonInsertMemcard.UseVisualStyleBackColor = true;
            this.buttonInsertMemcard.Click += new System.EventHandler(this.buttonInsertMemcard_Click);
            // 
            // buttonRemoveMemcard
            // 
            this.buttonRemoveMemcard.Location = new System.Drawing.Point(455, 106);
            this.buttonRemoveMemcard.Name = "buttonRemoveMemcard";
            this.buttonRemoveMemcard.Size = new System.Drawing.Size(116, 23);
            this.buttonRemoveMemcard.TabIndex = 24;
            this.buttonRemoveMemcard.Text = "Remove MemCard";
            this.buttonRemoveMemcard.UseVisualStyleBackColor = true;
            this.buttonRemoveMemcard.Click += new System.EventHandler(this.buttonRemoveMemcard_Click);
            // 
            // buttonConnectBatCardCharger
            // 
            this.buttonConnectBatCardCharger.Location = new System.Drawing.Point(170, 106);
            this.buttonConnectBatCardCharger.Name = "buttonConnectBatCardCharger";
            this.buttonConnectBatCardCharger.Size = new System.Drawing.Size(140, 23);
            this.buttonConnectBatCardCharger.TabIndex = 23;
            this.buttonConnectBatCardCharger.Text = "Connect BatCard Charger";
            this.buttonConnectBatCardCharger.UseVisualStyleBackColor = true;
            this.buttonConnectBatCardCharger.Click += new System.EventHandler(this.buttonConnectBatCardCharger_Click);
            // 
            // buttonDisconnectBatCardCharger
            // 
            this.buttonDisconnectBatCardCharger.Location = new System.Drawing.Point(11, 106);
            this.buttonDisconnectBatCardCharger.Name = "buttonDisconnectBatCardCharger";
            this.buttonDisconnectBatCardCharger.Size = new System.Drawing.Size(153, 23);
            this.buttonDisconnectBatCardCharger.TabIndex = 22;
            this.buttonDisconnectBatCardCharger.Text = "Disconnect BatCard Charger";
            this.buttonDisconnectBatCardCharger.UseVisualStyleBackColor = true;
            this.buttonDisconnectBatCardCharger.Click += new System.EventHandler(this.buttonDisconnectBatCardCharger_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(170, 77);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(140, 23);
            this.button2.TabIndex = 21;
            this.button2.Text = "Connect Phone Battery";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // buttonDisconnectPower
            // 
            this.buttonDisconnectPower.Location = new System.Drawing.Point(11, 77);
            this.buttonDisconnectPower.Name = "buttonDisconnectPower";
            this.buttonDisconnectPower.Size = new System.Drawing.Size(153, 23);
            this.buttonDisconnectPower.TabIndex = 20;
            this.buttonDisconnectPower.Text = "Disconnect Phone Battery";
            this.buttonDisconnectPower.UseVisualStyleBackColor = true;
            this.buttonDisconnectPower.Click += new System.EventHandler(this.buttonDisconnectPower_Click);
            // 
            // buttonRemoveSIM2
            // 
            this.buttonRemoveSIM2.Location = new System.Drawing.Point(455, 77);
            this.buttonRemoveSIM2.Name = "buttonRemoveSIM2";
            this.buttonRemoveSIM2.Size = new System.Drawing.Size(127, 23);
            this.buttonRemoveSIM2.TabIndex = 19;
            this.buttonRemoveSIM2.Text = "Remove SIM2";
            this.buttonRemoveSIM2.UseVisualStyleBackColor = true;
            this.buttonRemoveSIM2.Click += new System.EventHandler(this.buttonRemoveSIM2_Click);
            // 
            // buttonInsertSIM2
            // 
            this.buttonInsertSIM2.Location = new System.Drawing.Point(322, 77);
            this.buttonInsertSIM2.Name = "buttonInsertSIM2";
            this.buttonInsertSIM2.Size = new System.Drawing.Size(116, 23);
            this.buttonInsertSIM2.TabIndex = 18;
            this.buttonInsertSIM2.Text = "Insert SIM2";
            this.buttonInsertSIM2.UseVisualStyleBackColor = true;
            this.buttonInsertSIM2.Click += new System.EventHandler(this.buttonInsertSIM2_Click);
            // 
            // buttonDisconnectHeadset
            // 
            this.buttonDisconnectHeadset.Location = new System.Drawing.Point(455, 48);
            this.buttonDisconnectHeadset.Name = "buttonDisconnectHeadset";
            this.buttonDisconnectHeadset.Size = new System.Drawing.Size(127, 23);
            this.buttonDisconnectHeadset.TabIndex = 17;
            this.buttonDisconnectHeadset.Text = "Disconnect Headset";
            this.buttonDisconnectHeadset.UseVisualStyleBackColor = true;
            this.buttonDisconnectHeadset.Click += new System.EventHandler(this.buttonDisconnectHeadset_Click);
            // 
            // buttonConnectHeadset
            // 
            this.buttonConnectHeadset.Location = new System.Drawing.Point(322, 48);
            this.buttonConnectHeadset.Name = "buttonConnectHeadset";
            this.buttonConnectHeadset.Size = new System.Drawing.Size(116, 23);
            this.buttonConnectHeadset.TabIndex = 16;
            this.buttonConnectHeadset.Text = "Connect Headset";
            this.buttonConnectHeadset.UseVisualStyleBackColor = true;
            this.buttonConnectHeadset.Click += new System.EventHandler(this.buttonConnectHeadset_Click);
            // 
            // buttonDisconnectUSBREmote
            // 
            this.buttonDisconnectUSBREmote.Location = new System.Drawing.Point(768, 19);
            this.buttonDisconnectUSBREmote.Name = "buttonDisconnectUSBREmote";
            this.buttonDisconnectUSBREmote.Size = new System.Drawing.Size(138, 23);
            this.buttonDisconnectUSBREmote.TabIndex = 15;
            this.buttonDisconnectUSBREmote.Text = "Disconnect USB Remote";
            this.buttonDisconnectUSBREmote.UseVisualStyleBackColor = true;
            this.buttonDisconnectUSBREmote.Click += new System.EventHandler(this.buttonDisconnectUSBREmote_Click);
            // 
            // buttonConnectUSBRemote
            // 
            this.buttonConnectUSBRemote.Location = new System.Drawing.Point(635, 19);
            this.buttonConnectUSBRemote.Name = "buttonConnectUSBRemote";
            this.buttonConnectUSBRemote.Size = new System.Drawing.Size(127, 23);
            this.buttonConnectUSBRemote.TabIndex = 14;
            this.buttonConnectUSBRemote.Text = "Connect USB Remote";
            this.buttonConnectUSBRemote.UseVisualStyleBackColor = true;
            this.buttonConnectUSBRemote.Click += new System.EventHandler(this.buttonConnectUSBRemote_Click);
            // 
            // buttonDisconnectUSBMain
            // 
            this.buttonDisconnectUSBMain.Location = new System.Drawing.Point(455, 19);
            this.buttonDisconnectUSBMain.Name = "buttonDisconnectUSBMain";
            this.buttonDisconnectUSBMain.Size = new System.Drawing.Size(127, 23);
            this.buttonDisconnectUSBMain.TabIndex = 13;
            this.buttonDisconnectUSBMain.Text = "Disconnect USB Main";
            this.buttonDisconnectUSBMain.UseVisualStyleBackColor = true;
            this.buttonDisconnectUSBMain.Click += new System.EventHandler(this.buttonDisconnectUSBMain_Click);
            // 
            // buttonConnectUSBMain
            // 
            this.buttonConnectUSBMain.Location = new System.Drawing.Point(322, 19);
            this.buttonConnectUSBMain.Name = "buttonConnectUSBMain";
            this.buttonConnectUSBMain.Size = new System.Drawing.Size(116, 23);
            this.buttonConnectUSBMain.TabIndex = 12;
            this.buttonConnectUSBMain.Text = "Connect USB Main";
            this.buttonConnectUSBMain.UseVisualStyleBackColor = true;
            this.buttonConnectUSBMain.Click += new System.EventHandler(this.buttonConnectUSBMain_Click);
            // 
            // buttonInitialize
            // 
            this.buttonInitialize.Location = new System.Drawing.Point(11, 19);
            this.buttonInitialize.Name = "buttonInitialize";
            this.buttonInitialize.Size = new System.Drawing.Size(102, 23);
            this.buttonInitialize.TabIndex = 11;
            this.buttonInitialize.Text = "Initialize Defaults";
            this.buttonInitialize.UseVisualStyleBackColor = true;
            this.buttonInitialize.Click += new System.EventHandler(this.buttonInitialize_Click);
            // 
            // buttonPowerOnPhone
            // 
            this.buttonPowerOnPhone.Location = new System.Drawing.Point(130, 19);
            this.buttonPowerOnPhone.Name = "buttonPowerOnPhone";
            this.buttonPowerOnPhone.Size = new System.Drawing.Size(102, 23);
            this.buttonPowerOnPhone.TabIndex = 10;
            this.buttonPowerOnPhone.Text = "Power on Phone";
            this.buttonPowerOnPhone.UseVisualStyleBackColor = true;
            this.buttonPowerOnPhone.Click += new System.EventHandler(this.buttonPowerOnPhone_Click);
            // 
            // labelApplicationVersion
            // 
            this.labelApplicationVersion.AutoSize = true;
            this.labelApplicationVersion.Location = new System.Drawing.Point(6, 35);
            this.labelApplicationVersion.Name = "labelApplicationVersion";
            this.labelApplicationVersion.Size = new System.Drawing.Size(0, 13);
            this.labelApplicationVersion.TabIndex = 15;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 14);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(200, 13);
            this.label4.TabIndex = 14;
            this.label4.Text = "HW Controller Server Application Version";
            // 
            // labelServerStatus
            // 
            this.labelServerStatus.AutoSize = true;
            this.labelServerStatus.Location = new System.Drawing.Point(324, 35);
            this.labelServerStatus.Name = "labelServerStatus";
            this.labelServerStatus.Size = new System.Drawing.Size(0, 13);
            this.labelServerStatus.TabIndex = 13;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(324, 14);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(71, 13);
            this.label3.TabIndex = 12;
            this.label3.Text = "Server Status";
            // 
            // groupBoxTcpIpMode
            // 
            this.groupBoxTcpIpMode.Controls.Add(this.button1);
            this.groupBoxTcpIpMode.Controls.Add(this.label1);
            this.groupBoxTcpIpMode.Controls.Add(this.label3);
            this.groupBoxTcpIpMode.Controls.Add(this.labelServerStatus);
            this.groupBoxTcpIpMode.Controls.Add(this.textBoxServerIP);
            this.groupBoxTcpIpMode.Location = new System.Drawing.Point(416, 3);
            this.groupBoxTcpIpMode.Name = "groupBoxTcpIpMode";
            this.groupBoxTcpIpMode.Size = new System.Drawing.Size(402, 64);
            this.groupBoxTcpIpMode.TabIndex = 16;
            this.groupBoxTcpIpMode.TabStop = false;
            this.groupBoxTcpIpMode.Text = "TCP/IP Mode";
            // 
            // groupBoxStatus
            // 
            this.groupBoxStatus.Controls.Add(this.labelApplicationVersion);
            this.groupBoxStatus.Controls.Add(this.label4);
            this.groupBoxStatus.Location = new System.Drawing.Point(824, 3);
            this.groupBoxStatus.Name = "groupBoxStatus";
            this.groupBoxStatus.Size = new System.Drawing.Size(276, 64);
            this.groupBoxStatus.TabIndex = 17;
            this.groupBoxStatus.TabStop = false;
            // 
            // groupBoxUsbMode
            // 
            this.groupBoxUsbMode.Controls.Add(this.label5);
            this.groupBoxUsbMode.Controls.Add(this.labelSerialStatusText);
            this.groupBoxUsbMode.Controls.Add(this.buttonTestSerialConnection);
            this.groupBoxUsbMode.Location = new System.Drawing.Point(215, 3);
            this.groupBoxUsbMode.Name = "groupBoxUsbMode";
            this.groupBoxUsbMode.Size = new System.Drawing.Size(195, 64);
            this.groupBoxUsbMode.TabIndex = 18;
            this.groupBoxUsbMode.TabStop = false;
            this.groupBoxUsbMode.Text = "Serial Mode";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(116, 12);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(37, 13);
            this.label5.TabIndex = 14;
            this.label5.Text = "Status";
            // 
            // labelSerialStatusText
            // 
            this.labelSerialStatusText.AutoSize = true;
            this.labelSerialStatusText.Location = new System.Drawing.Point(117, 30);
            this.labelSerialStatusText.Name = "labelSerialStatusText";
            this.labelSerialStatusText.Size = new System.Drawing.Size(0, 13);
            this.labelSerialStatusText.TabIndex = 15;
            // 
            // buttonTestSerialConnection
            // 
            this.buttonTestSerialConnection.Location = new System.Drawing.Point(13, 28);
            this.buttonTestSerialConnection.Name = "buttonTestSerialConnection";
            this.buttonTestSerialConnection.Size = new System.Drawing.Size(94, 23);
            this.buttonTestSerialConnection.TabIndex = 2;
            this.buttonTestSerialConnection.Text = "Test Connection";
            this.buttonTestSerialConnection.UseVisualStyleBackColor = true;
            this.buttonTestSerialConnection.Click += new System.EventHandler(this.buttonTestSerialConnection_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.numericUpDownTestUnit);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Location = new System.Drawing.Point(107, 3);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(102, 64);
            this.groupBox2.TabIndex = 19;
            this.groupBox2.TabStop = false;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.comboBoxConnectionMode);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Location = new System.Drawing.Point(9, 3);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(102, 64);
            this.groupBox3.TabIndex = 20;
            this.groupBox3.TabStop = false;
            // 
            // comboBoxConnectionMode
            // 
            this.comboBoxConnectionMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxConnectionMode.FormattingEnabled = true;
            this.comboBoxConnectionMode.Items.AddRange(new object[] {
            "USB",
            "TCP"});
            this.comboBoxConnectionMode.Location = new System.Drawing.Point(10, 31);
            this.comboBoxConnectionMode.MaxDropDownItems = 2;
            this.comboBoxConnectionMode.Name = "comboBoxConnectionMode";
            this.comboBoxConnectionMode.Size = new System.Drawing.Size(82, 21);
            this.comboBoxConnectionMode.TabIndex = 6;
            this.comboBoxConnectionMode.SelectionChangeCommitted += new System.EventHandler(this.comboBoxConnectionMode_SelectionChangeCommitted);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(7, 12);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(88, 13);
            this.label7.TabIndex = 5;
            this.label7.Text = "Connection Type";
            // 
            // Form1
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
            this.ClientSize = new System.Drawing.Size(1112, 727);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBoxUsbMode);
            this.Controls.Add(this.groupBoxStatus);
            this.Controls.Add(this.groupBoxTcpIpMode);
            this.Controls.Add(this.groupBoxServerCommands);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.textBoxLog);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Temporary Control UI";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Shown += new System.EventHandler(this.Form1_Shown);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTestUnit)).EndInit();
            this.groupBoxServerCommands.ResumeLayout(false);
            this.groupBoxServerCommands.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownKeylockPwrMs)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownExt)).EndInit();
            this.groupBoxTcpIpMode.ResumeLayout(false);
            this.groupBoxTcpIpMode.PerformLayout();
            this.groupBoxStatus.ResumeLayout(false);
            this.groupBoxStatus.PerformLayout();
            this.groupBoxUsbMode.ResumeLayout(false);
            this.groupBoxUsbMode.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxServerIP;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox textBoxLog;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numericUpDownTestUnit;
        private System.Windows.Forms.GroupBox groupBoxServerCommands;
        private System.Windows.Forms.Button buttonPowerOnPhone;
        private System.Windows.Forms.Button buttonInitialize;
        private System.Windows.Forms.Button buttonDisconnectUSBMain;
        private System.Windows.Forms.Button buttonConnectUSBMain;
        private System.Windows.Forms.Button buttonDisconnectUSBREmote;
        private System.Windows.Forms.Button buttonConnectUSBRemote;
        private System.Windows.Forms.Button buttonRemoveSIM2;
        private System.Windows.Forms.Button buttonInsertSIM2;
        private System.Windows.Forms.Button buttonDisconnectHeadset;
        private System.Windows.Forms.Button buttonConnectHeadset;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button buttonDisconnectPower;
        private System.Windows.Forms.Button buttonConnectBatCardCharger;
        private System.Windows.Forms.Button buttonDisconnectBatCardCharger;
        private System.Windows.Forms.Button buttonInsertMemcard;
        private System.Windows.Forms.Button buttonRemoveMemcard;
        private System.Windows.Forms.Button buttonConnectUSBMainCharger;
        private System.Windows.Forms.Button buttonConnectExt;
        private System.Windows.Forms.Button buttonDisconnectExt;
        private System.Windows.Forms.NumericUpDown numericUpDownExt;
        private System.Windows.Forms.NumericUpDown numericUpDownKeylockPwrMs;
        private System.Windows.Forms.Button buttonPressKeylockPwrMs;
        private System.Windows.Forms.Button buttonGetHWState;
        private System.Windows.Forms.TextBox textBoxPowerOnPhoneSequence;
        private System.Windows.Forms.Label labelApplicationVersion;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label labelServerStatus;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBoxTcpIpMode;
        private System.Windows.Forms.GroupBox groupBoxStatus;
        private System.Windows.Forms.GroupBox groupBoxUsbMode;
        private System.Windows.Forms.Button buttonTestSerialConnection;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label labelSerialStatusText;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ComboBox comboBoxConnectionMode;
        private System.Windows.Forms.Label label7;
    }
}

