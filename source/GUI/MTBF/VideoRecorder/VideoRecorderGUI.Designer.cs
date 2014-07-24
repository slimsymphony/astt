namespace TestAutomation.Gui.Marble
{
    partial class VideoRecorderGUI
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(VideoRecorderGUI));
            this.groupBoxImageSettings = new System.Windows.Forms.GroupBox();
            this.groupBoxVideoAndPictures = new System.Windows.Forms.GroupBox();
            this.buttonCameraSettings = new System.Windows.Forms.Button();
            this.buttonStartStopRecording = new System.Windows.Forms.Button();
            this.buttonTakeAnImage = new System.Windows.Forms.Button();
            this.groupBoxMotionDetection = new System.Windows.Forms.GroupBox();
            this.checkBoxViewMotionHistory = new System.Windows.Forms.CheckBox();
            this.checkBoxViewMotionImage = new System.Windows.Forms.CheckBox();
            this.groupBoxFlip = new System.Windows.Forms.GroupBox();
            this.checkBoxFlipY = new System.Windows.Forms.CheckBox();
            this.checkBoxFlipX = new System.Windows.Forms.CheckBox();
            this.groupBoxImageRotation = new System.Windows.Forms.GroupBox();
            this.radioButton270 = new System.Windows.Forms.RadioButton();
            this.radioButton180 = new System.Windows.Forms.RadioButton();
            this.radioButton90 = new System.Windows.Forms.RadioButton();
            this.radioButton0 = new System.Windows.Forms.RadioButton();
            this.statisticsTimer = new System.Windows.Forms.Timer(this.components);
            this.groupBoxStatus = new System.Windows.Forms.GroupBox();
            this.checkBoxTopmost = new System.Windows.Forms.CheckBox();
            this.textBoxMotionDetected = new System.Windows.Forms.TextBox();
            this.labelMotionDetected = new System.Windows.Forms.Label();
            this.textBoxVideoFps = new System.Windows.Forms.TextBox();
            this.labelVideoPath = new System.Windows.Forms.Label();
            this.textBoxVideoPath = new System.Windows.Forms.TextBox();
            this.labelFps = new System.Windows.Forms.Label();
            this.devicesCombo = new System.Windows.Forms.ComboBox();
            this.groupBoxVideoDevice = new System.Windows.Forms.GroupBox();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.videoFrameCallbackTimer = new System.Windows.Forms.Timer(this.components);
            this.videoSourcePlayer = new AForge.Controls.VideoSourcePlayer();
            this.groupBoxVideo = new System.Windows.Forms.GroupBox();
            this.groupBoxImageSettings.SuspendLayout();
            this.groupBoxVideoAndPictures.SuspendLayout();
            this.groupBoxMotionDetection.SuspendLayout();
            this.groupBoxFlip.SuspendLayout();
            this.groupBoxImageRotation.SuspendLayout();
            this.groupBoxStatus.SuspendLayout();
            this.groupBoxVideoDevice.SuspendLayout();
            this.groupBoxVideo.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxImageSettings
            // 
            this.groupBoxImageSettings.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxImageSettings.Controls.Add(this.groupBoxVideoAndPictures);
            this.groupBoxImageSettings.Controls.Add(this.groupBoxMotionDetection);
            this.groupBoxImageSettings.Controls.Add(this.groupBoxFlip);
            this.groupBoxImageSettings.Controls.Add(this.groupBoxImageRotation);
            this.groupBoxImageSettings.Location = new System.Drawing.Point(253, 3);
            this.groupBoxImageSettings.Name = "groupBoxImageSettings";
            this.groupBoxImageSettings.Size = new System.Drawing.Size(151, 296);
            this.groupBoxImageSettings.TabIndex = 15;
            this.groupBoxImageSettings.TabStop = false;
            this.groupBoxImageSettings.Text = "Image Settings";
            // 
            // groupBoxVideoAndPictures
            // 
            this.groupBoxVideoAndPictures.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxVideoAndPictures.Controls.Add(this.buttonCameraSettings);
            this.groupBoxVideoAndPictures.Controls.Add(this.buttonStartStopRecording);
            this.groupBoxVideoAndPictures.Controls.Add(this.buttonTakeAnImage);
            this.groupBoxVideoAndPictures.Location = new System.Drawing.Point(6, 184);
            this.groupBoxVideoAndPictures.Name = "groupBoxVideoAndPictures";
            this.groupBoxVideoAndPictures.Size = new System.Drawing.Size(137, 106);
            this.groupBoxVideoAndPictures.TabIndex = 15;
            this.groupBoxVideoAndPictures.TabStop = false;
            this.groupBoxVideoAndPictures.Text = "Video && Images";
            // 
            // buttonCameraSettings
            // 
            this.buttonCameraSettings.Location = new System.Drawing.Point(7, 75);
            this.buttonCameraSettings.Name = "buttonCameraSettings";
            this.buttonCameraSettings.Size = new System.Drawing.Size(123, 25);
            this.buttonCameraSettings.TabIndex = 2;
            this.buttonCameraSettings.Text = "Camera settings";
            this.buttonCameraSettings.UseVisualStyleBackColor = true;
            this.buttonCameraSettings.Click += new System.EventHandler(this.buttonCameraSettings_Click);
            // 
            // buttonStartStopRecording
            // 
            this.buttonStartStopRecording.FlatAppearance.BorderColor = System.Drawing.Color.Green;
            this.buttonStartStopRecording.FlatAppearance.BorderSize = 2;
            this.buttonStartStopRecording.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.buttonStartStopRecording.Location = new System.Drawing.Point(7, 46);
            this.buttonStartStopRecording.Name = "buttonStartStopRecording";
            this.buttonStartStopRecording.Size = new System.Drawing.Size(123, 25);
            this.buttonStartStopRecording.TabIndex = 1;
            this.buttonStartStopRecording.Text = "Start recording";
            this.buttonStartStopRecording.UseVisualStyleBackColor = true;
            this.buttonStartStopRecording.Click += new System.EventHandler(this.buttonStartStopRecording_Click);
            // 
            // buttonTakeAnImage
            // 
            this.buttonTakeAnImage.Location = new System.Drawing.Point(7, 17);
            this.buttonTakeAnImage.Name = "buttonTakeAnImage";
            this.buttonTakeAnImage.Size = new System.Drawing.Size(123, 25);
            this.buttonTakeAnImage.TabIndex = 0;
            this.buttonTakeAnImage.Text = "Take an image";
            this.buttonTakeAnImage.UseVisualStyleBackColor = true;
            this.buttonTakeAnImage.Click += new System.EventHandler(this.buttonTakeAnImage_Click);
            // 
            // groupBoxMotionDetection
            // 
            this.groupBoxMotionDetection.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxMotionDetection.Controls.Add(this.checkBoxViewMotionHistory);
            this.groupBoxMotionDetection.Controls.Add(this.checkBoxViewMotionImage);
            this.groupBoxMotionDetection.Location = new System.Drawing.Point(6, 120);
            this.groupBoxMotionDetection.Name = "groupBoxMotionDetection";
            this.groupBoxMotionDetection.Size = new System.Drawing.Size(137, 61);
            this.groupBoxMotionDetection.TabIndex = 14;
            this.groupBoxMotionDetection.TabStop = false;
            this.groupBoxMotionDetection.Text = "Motion Detection";
            // 
            // checkBoxViewMotionHistory
            // 
            this.checkBoxViewMotionHistory.AutoSize = true;
            this.checkBoxViewMotionHistory.Location = new System.Drawing.Point(14, 39);
            this.checkBoxViewMotionHistory.Name = "checkBoxViewMotionHistory";
            this.checkBoxViewMotionHistory.Size = new System.Drawing.Size(119, 17);
            this.checkBoxViewMotionHistory.TabIndex = 3;
            this.checkBoxViewMotionHistory.Text = "View Motion History";
            this.checkBoxViewMotionHistory.UseVisualStyleBackColor = true;
            // 
            // checkBoxViewMotionImage
            // 
            this.checkBoxViewMotionImage.AutoSize = true;
            this.checkBoxViewMotionImage.Location = new System.Drawing.Point(14, 16);
            this.checkBoxViewMotionImage.Name = "checkBoxViewMotionImage";
            this.checkBoxViewMotionImage.Size = new System.Drawing.Size(116, 17);
            this.checkBoxViewMotionImage.TabIndex = 2;
            this.checkBoxViewMotionImage.Text = "View Motion Image";
            this.checkBoxViewMotionImage.UseVisualStyleBackColor = true;
            // 
            // groupBoxFlip
            // 
            this.groupBoxFlip.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxFlip.Controls.Add(this.checkBoxFlipY);
            this.groupBoxFlip.Controls.Add(this.checkBoxFlipX);
            this.groupBoxFlip.Location = new System.Drawing.Point(6, 78);
            this.groupBoxFlip.Name = "groupBoxFlip";
            this.groupBoxFlip.Size = new System.Drawing.Size(137, 38);
            this.groupBoxFlip.TabIndex = 13;
            this.groupBoxFlip.TabStop = false;
            this.groupBoxFlip.Text = "Flip";
            // 
            // checkBoxFlipY
            // 
            this.checkBoxFlipY.AutoSize = true;
            this.checkBoxFlipY.Location = new System.Drawing.Point(67, 16);
            this.checkBoxFlipY.Name = "checkBoxFlipY";
            this.checkBoxFlipY.Size = new System.Drawing.Size(52, 17);
            this.checkBoxFlipY.TabIndex = 3;
            this.checkBoxFlipY.Text = "Flip Y";
            this.checkBoxFlipY.UseVisualStyleBackColor = true;
            this.checkBoxFlipY.CheckedChanged += new System.EventHandler(this.imgRotationOrFlip_CheckedChanged);
            // 
            // checkBoxFlipX
            // 
            this.checkBoxFlipX.AutoSize = true;
            this.checkBoxFlipX.Location = new System.Drawing.Point(14, 16);
            this.checkBoxFlipX.Name = "checkBoxFlipX";
            this.checkBoxFlipX.Size = new System.Drawing.Size(52, 17);
            this.checkBoxFlipX.TabIndex = 2;
            this.checkBoxFlipX.Text = "Flip X";
            this.checkBoxFlipX.UseVisualStyleBackColor = true;
            this.checkBoxFlipX.CheckedChanged += new System.EventHandler(this.imgRotationOrFlip_CheckedChanged);
            // 
            // groupBoxImageRotation
            // 
            this.groupBoxImageRotation.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxImageRotation.Controls.Add(this.radioButton270);
            this.groupBoxImageRotation.Controls.Add(this.radioButton180);
            this.groupBoxImageRotation.Controls.Add(this.radioButton90);
            this.groupBoxImageRotation.Controls.Add(this.radioButton0);
            this.groupBoxImageRotation.Location = new System.Drawing.Point(6, 17);
            this.groupBoxImageRotation.Name = "groupBoxImageRotation";
            this.groupBoxImageRotation.Size = new System.Drawing.Size(137, 59);
            this.groupBoxImageRotation.TabIndex = 10;
            this.groupBoxImageRotation.TabStop = false;
            this.groupBoxImageRotation.Text = "Image Rotation";
            // 
            // radioButton270
            // 
            this.radioButton270.AutoSize = true;
            this.radioButton270.Location = new System.Drawing.Point(67, 38);
            this.radioButton270.Name = "radioButton270";
            this.radioButton270.Size = new System.Drawing.Size(47, 17);
            this.radioButton270.TabIndex = 3;
            this.radioButton270.Text = "270°";
            this.radioButton270.UseVisualStyleBackColor = true;
            this.radioButton270.CheckedChanged += new System.EventHandler(this.imgRotationOrFlip_CheckedChanged);
            // 
            // radioButton180
            // 
            this.radioButton180.AutoSize = true;
            this.radioButton180.Location = new System.Drawing.Point(67, 15);
            this.radioButton180.Name = "radioButton180";
            this.radioButton180.Size = new System.Drawing.Size(47, 17);
            this.radioButton180.TabIndex = 2;
            this.radioButton180.Text = "180°";
            this.radioButton180.UseVisualStyleBackColor = true;
            this.radioButton180.CheckedChanged += new System.EventHandler(this.imgRotationOrFlip_CheckedChanged);
            // 
            // radioButton90
            // 
            this.radioButton90.AutoSize = true;
            this.radioButton90.Location = new System.Drawing.Point(15, 38);
            this.radioButton90.Name = "radioButton90";
            this.radioButton90.Size = new System.Drawing.Size(41, 17);
            this.radioButton90.TabIndex = 1;
            this.radioButton90.Text = "90°";
            this.radioButton90.UseVisualStyleBackColor = true;
            this.radioButton90.CheckedChanged += new System.EventHandler(this.imgRotationOrFlip_CheckedChanged);
            // 
            // radioButton0
            // 
            this.radioButton0.AutoSize = true;
            this.radioButton0.Checked = true;
            this.radioButton0.Location = new System.Drawing.Point(15, 15);
            this.radioButton0.Name = "radioButton0";
            this.radioButton0.Size = new System.Drawing.Size(35, 17);
            this.radioButton0.TabIndex = 0;
            this.radioButton0.TabStop = true;
            this.radioButton0.Text = "0°";
            this.radioButton0.UseVisualStyleBackColor = true;
            this.radioButton0.CheckedChanged += new System.EventHandler(this.imgRotationOrFlip_CheckedChanged);
            // 
            // statisticsTimer
            // 
            this.statisticsTimer.Interval = 1000;
            this.statisticsTimer.Tick += new System.EventHandler(this.statisticsTimer_Tick);
            // 
            // groupBoxStatus
            // 
            this.groupBoxStatus.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxStatus.Controls.Add(this.checkBoxTopmost);
            this.groupBoxStatus.Controls.Add(this.textBoxMotionDetected);
            this.groupBoxStatus.Controls.Add(this.labelMotionDetected);
            this.groupBoxStatus.Controls.Add(this.textBoxVideoFps);
            this.groupBoxStatus.Controls.Add(this.labelVideoPath);
            this.groupBoxStatus.Controls.Add(this.textBoxVideoPath);
            this.groupBoxStatus.Controls.Add(this.labelFps);
            this.groupBoxStatus.Location = new System.Drawing.Point(4, 388);
            this.groupBoxStatus.Name = "groupBoxStatus";
            this.groupBoxStatus.Size = new System.Drawing.Size(400, 71);
            this.groupBoxStatus.TabIndex = 17;
            this.groupBoxStatus.TabStop = false;
            this.groupBoxStatus.Text = "Status && Statistics";
            // 
            // checkBoxTopmost
            // 
            this.checkBoxTopmost.AutoSize = true;
            this.checkBoxTopmost.Location = new System.Drawing.Point(298, 42);
            this.checkBoxTopmost.Name = "checkBoxTopmost";
            this.checkBoxTopmost.Size = new System.Drawing.Size(92, 17);
            this.checkBoxTopmost.TabIndex = 7;
            this.checkBoxTopmost.Text = "Always on top";
            this.checkBoxTopmost.UseVisualStyleBackColor = true;
            this.checkBoxTopmost.CheckedChanged += new System.EventHandler(this.checkBoxTopmost_CheckedChanged);
            // 
            // textBoxMotionDetected
            // 
            this.textBoxMotionDetected.BackColor = System.Drawing.SystemColors.Menu;
            this.textBoxMotionDetected.Location = new System.Drawing.Point(250, 39);
            this.textBoxMotionDetected.Name = "textBoxMotionDetected";
            this.textBoxMotionDetected.ReadOnly = true;
            this.textBoxMotionDetected.Size = new System.Drawing.Size(42, 20);
            this.textBoxMotionDetected.TabIndex = 6;
            // 
            // labelMotionDetected
            // 
            this.labelMotionDetected.AutoSize = true;
            this.labelMotionDetected.Location = new System.Drawing.Point(132, 42);
            this.labelMotionDetected.Name = "labelMotionDetected";
            this.labelMotionDetected.Size = new System.Drawing.Size(121, 13);
            this.labelMotionDetected.TabIndex = 5;
            this.labelMotionDetected.Text = "Motion frames detected:";
            // 
            // textBoxVideoFps
            // 
            this.textBoxVideoFps.BackColor = System.Drawing.SystemColors.Menu;
            this.textBoxVideoFps.Location = new System.Drawing.Point(69, 39);
            this.textBoxVideoFps.Name = "textBoxVideoFps";
            this.textBoxVideoFps.ReadOnly = true;
            this.textBoxVideoFps.Size = new System.Drawing.Size(57, 20);
            this.textBoxVideoFps.TabIndex = 4;
            // 
            // labelVideoPath
            // 
            this.labelVideoPath.AutoSize = true;
            this.labelVideoPath.Location = new System.Drawing.Point(8, 19);
            this.labelVideoPath.Name = "labelVideoPath";
            this.labelVideoPath.Size = new System.Drawing.Size(61, 13);
            this.labelVideoPath.TabIndex = 3;
            this.labelVideoPath.Text = "Video path:";
            // 
            // textBoxVideoPath
            // 
            this.textBoxVideoPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxVideoPath.BackColor = System.Drawing.SystemColors.Menu;
            this.textBoxVideoPath.Location = new System.Drawing.Point(69, 16);
            this.textBoxVideoPath.Name = "textBoxVideoPath";
            this.textBoxVideoPath.ReadOnly = true;
            this.textBoxVideoPath.Size = new System.Drawing.Size(323, 20);
            this.textBoxVideoPath.TabIndex = 2;
            // 
            // labelFps
            // 
            this.labelFps.AutoSize = true;
            this.labelFps.Location = new System.Drawing.Point(8, 42);
            this.labelFps.Name = "labelFps";
            this.labelFps.Size = new System.Drawing.Size(54, 13);
            this.labelFps.TabIndex = 1;
            this.labelFps.Text = "Video fps:";
            // 
            // devicesCombo
            // 
            this.devicesCombo.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.devicesCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.devicesCombo.FormattingEnabled = true;
            this.devicesCombo.Location = new System.Drawing.Point(6, 19);
            this.devicesCombo.Name = "devicesCombo";
            this.devicesCombo.Size = new System.Drawing.Size(306, 21);
            this.devicesCombo.TabIndex = 18;
            this.devicesCombo.Click += new System.EventHandler(this.devicesCombo_Click);
            // 
            // groupBoxVideoDevice
            // 
            this.groupBoxVideoDevice.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxVideoDevice.Controls.Add(this.buttonRefresh);
            this.groupBoxVideoDevice.Controls.Add(this.devicesCombo);
            this.groupBoxVideoDevice.Location = new System.Drawing.Point(4, 332);
            this.groupBoxVideoDevice.Name = "groupBoxVideoDevice";
            this.groupBoxVideoDevice.Size = new System.Drawing.Size(400, 50);
            this.groupBoxVideoDevice.TabIndex = 21;
            this.groupBoxVideoDevice.TabStop = false;
            this.groupBoxVideoDevice.Text = "Video Device";
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.buttonRefresh.Location = new System.Drawing.Point(318, 17);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(75, 23);
            this.buttonRefresh.TabIndex = 19;
            this.buttonRefresh.Text = "Refresh";
            this.buttonRefresh.UseVisualStyleBackColor = true;
            this.buttonRefresh.Click += new System.EventHandler(this.buttonRefresh_Click);
            // 
            // videoFrameCallbackTimer
            // 
            this.videoFrameCallbackTimer.Interval = 200;
            this.videoFrameCallbackTimer.Tick += new System.EventHandler(this.videoFrameCallbackTimer_Tick);
            // videoSourcePlayer
            // 
            this.videoSourcePlayer.AutoSizeControl = true;
            this.videoSourcePlayer.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.videoSourcePlayer.ForeColor = System.Drawing.Color.White;
            this.videoSourcePlayer.Location = new System.Drawing.Point(-36, 40);
            this.videoSourcePlayer.Name = "videoSourcePlayer";
            this.videoSourcePlayer.Size = new System.Drawing.Size(322, 242);
            this.videoSourcePlayer.TabIndex = 16;
            this.videoSourcePlayer.TabStop = false;
            this.videoSourcePlayer.VideoSource = null;
            // 
            // groupBoxVideo
            // 
            this.groupBoxVideo.Controls.Add(this.videoSourcePlayer);
            this.groupBoxVideo.Location = new System.Drawing.Point(4, 3);
            this.groupBoxVideo.Name = "groupBoxVideo";
            this.groupBoxVideo.Size = new System.Drawing.Size(249, 323);
            this.groupBoxVideo.TabIndex = 22;
            this.groupBoxVideo.TabStop = false;
            // 
            // VideoRecorderGUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(411, 463);
            this.Controls.Add(this.groupBoxVideo);
            this.Controls.Add(this.groupBoxVideoDevice);
            this.Controls.Add(this.groupBoxStatus);
            this.Controls.Add(this.groupBoxImageSettings);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "VideoRecorderGUI";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "Video Recorder";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.videoRecorder_FormClosing);
            this.Shown += new System.EventHandler(this.VideoRecorderGUI_Shown);
            this.groupBoxImageSettings.ResumeLayout(false);
            this.groupBoxVideoAndPictures.ResumeLayout(false);
            this.groupBoxMotionDetection.ResumeLayout(false);
            this.groupBoxMotionDetection.PerformLayout();
            this.groupBoxFlip.ResumeLayout(false);
            this.groupBoxFlip.PerformLayout();
            this.groupBoxImageRotation.ResumeLayout(false);
            this.groupBoxImageRotation.PerformLayout();
            this.groupBoxStatus.ResumeLayout(false);
            this.groupBoxStatus.PerformLayout();
            this.groupBoxVideoDevice.ResumeLayout(false);
            this.groupBoxVideo.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxImageSettings;
        private System.Windows.Forms.GroupBox groupBoxFlip;
        private System.Windows.Forms.CheckBox checkBoxFlipY;
        private System.Windows.Forms.CheckBox checkBoxFlipX;
        private System.Windows.Forms.GroupBox groupBoxImageRotation;
        private System.Windows.Forms.RadioButton radioButton270;
        private System.Windows.Forms.RadioButton radioButton180;
        private System.Windows.Forms.RadioButton radioButton90;
        private System.Windows.Forms.RadioButton radioButton0;
        private AForge.Controls.VideoSourcePlayer videoSourcePlayer;
        private System.Windows.Forms.GroupBox groupBoxMotionDetection;
        private System.Windows.Forms.CheckBox checkBoxViewMotionHistory;
        private System.Windows.Forms.CheckBox checkBoxViewMotionImage;
        private System.Windows.Forms.GroupBox groupBoxVideoAndPictures;
        private System.Windows.Forms.Button buttonStartStopRecording;
        private System.Windows.Forms.Button buttonTakeAnImage;
        private System.Windows.Forms.Button buttonCameraSettings;
        private System.Windows.Forms.Timer statisticsTimer;
        private System.Windows.Forms.GroupBox groupBoxStatus;
        private System.Windows.Forms.Label labelFps;
        private System.Windows.Forms.Label labelVideoPath;
        private System.Windows.Forms.TextBox textBoxVideoPath;
        private System.Windows.Forms.TextBox textBoxVideoFps;
        private System.Windows.Forms.TextBox textBoxMotionDetected;
        private System.Windows.Forms.Label labelMotionDetected;
        private System.Windows.Forms.CheckBox checkBoxTopmost;
        private System.Windows.Forms.ComboBox devicesCombo;
        private System.Windows.Forms.GroupBox groupBoxVideoDevice;
        private System.Windows.Forms.Button buttonRefresh;
        private System.Windows.Forms.Timer videoFrameCallbackTimer;
        private System.Windows.Forms.GroupBox groupBoxVideo;
    }
}

