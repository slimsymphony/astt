using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.ServiceModel;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using AForge;
using AForge.Imaging;
using AForge.Video;
using AForge.Video.DirectShow;
using AForge.Video.FFMPEG;
using AForge.Vision.Motion;
using TestAutomation.Gui.Marble.IPC.Clients;
using TestAutomation.Gui.Marble.IPC.Interfaces;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;
using TestAutomation.Gui.Marble.IPC.Services;
using log4net;

namespace TestAutomation.Gui.Marble
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single, ConcurrencyMode = ConcurrencyMode.Multiple)]
    public partial class VideoRecorderGUI : Form, IVideoRecorderService
    {
        #region Data Bindings

        public class DeviceDataModel : INotifyPropertyChanged
        {
            public int AccessId { get; set; }

            private string cameraModel;

            public string CameraModel
            {
                get
                {
                    return cameraModel;
                }

                set
                {
                    cameraModel = value;
                    RaisePropertyChanged("CameraModel");
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

        #endregion

        #region Private members

        private SettingsHandler settingsHandler;
        private VideoRecorderServiceSettings settings
        {
            get { return (VideoRecorderServiceSettings)this.settingsHandler.SettingsObject; }
        }

        private readonly ILog log;
        private bool updatingUiSettings;
        private Stopwatch stopWatch;
        private RotateFlipType rotate;
        private VideoFileWriter writer;
        private Queue<string> snapshotQueue;
        private object snapShotLock = new object();
        private string overlayText = string.Empty;
        private bool stoppingCamera;
        private List<CameraSpecific> captureDevices;
        private string currentDevice = string.Empty;
        private string currentDeviceId = string.Empty;
        private int captureHeight = 640;
        private int captureWidth = 480;
        private static int desiredCameraFps = 10;
        private static int videoBitrate = 65536; //64kbps

        // motion detector
        private MotionDetector detector;
        private Bitmap currentVideoFrame;
        private readonly object currentVideoFrameLock = new object();
        private readonly object guiUpdateLock = new object();
        
        // motion detection and processing algorithm
        private int mCount = 0;
        private int motionCount
        {
            get { return mCount; }
            set
            {
                this.mCount = value;
                if (textBoxMotionDetected.InvokeRequired)
                {
                    this.Invoke(new Action(() => this.textBoxMotionDetected.Text = mCount.ToString()));
                }
                else
                {
                    this.textBoxMotionDetected.Text = mCount.ToString();
                }
            }
        }

        private float motionAlarmLevel = 0.010f;

        private List<float> motionHistory = new List<float>();
        private VideoRecorderInfo myRecorderInfo;
        private List<VideoRecorderInfo> activeVideoRecorders;
        private readonly BindingList<DeviceDataModel> cameraList = new BindingList<DeviceDataModel>();
        private string recorderTitle = "Video Recorder";

        #endregion

        #region Constructor(s)

        public VideoRecorderGUI(SettingsHandler settingsHandler)
        {
            this.activeVideoRecorders = new List<VideoRecorderInfo>();
            // Got handle to settingsHandler and get log4net logger
            this.settingsHandler = settingsHandler;
            this.log = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);

            InitializeComponent();
            this.devicesCombo.ValueMember = "AccessId";
            this.devicesCombo.DisplayMember = "CameraModel";
            this.devicesCombo.DataSource = this.cameraList;
            this.groupBoxVideo.Size = this.videoSourcePlayer.Size;
            updateWindowSize();
            this.captureDevices = new List<CameraSpecific>();

            this.updateUiFromSettings();
            this.imgRotationOrFlip_CheckedChanged(this, null);

            this.motionCount = 0;
            this.snapshotQueue = new Queue<string>();
            //this.checkOrNotifyOtherVideoRecorders(false);
            log.Info("VideoRecorder GUI Object Created");
        }

        #endregion

        #region Private methods

        private void updateWindowSize()
        {
            int heightValue = 0;
            heightValue = this.videoSourcePlayer.Height > this.groupBoxImageSettings.Height ? videoSourcePlayer.Height : this.groupBoxImageSettings.Height;

            this.Height = (heightValue + this.groupBoxVideoDevice.Height + this.groupBoxStatus.Height + 50);
            this.Width = (this.videoSourcePlayer.Width + this.groupBoxImageSettings.Width + 25);
            if (this.detector != null)
                this.detector.Reset();
            
        }

        private Bitmap drawToBitmap(Bitmap fromSource)
        {
            Bitmap image = (Bitmap)fromSource.Clone();

            DateTime now = DateTime.Now;
            Graphics g = Graphics.FromImage(image);

            // paint current time
            SolidBrush brush = new SolidBrush(Color.Red);
            int fontHeight;
            if (image.Height > image.Width)
                fontHeight = (int)(image.Height * 0.035);
            else
            {
                fontHeight = (int)(image.Width * 0.035);
            }

            Font f = new Font("Arial", fontHeight, FontStyle.Regular);
            g.DrawString(now.ToString(), f, brush, new PointF(5, 5));

            if (!string.IsNullOrEmpty(this.overlayText))
            {
                List<string> lines = new List<string>();
                string line = string.Empty;
                foreach (char s in this.overlayText)
                {
                    if (TextRenderer.MeasureText(line + s, f).Width <
                        image.Width - (TextRenderer.MeasureText(new string(s, 1), f).Width + 5))
                    {
                        line += s;
                    }
                    else
                    {
                        lines.Add(line);
                        line = string.Empty;
                    }
                }

                if (!string.IsNullOrEmpty(line))
                {
                    lines.Add(line);
                    line = string.Empty;
                }

                int startPoint = image.Height - (lines.Count * f.Height);
                foreach (string t in lines)
                {
                    g.DrawString(t, f, brush, new PointF(5, startPoint));
                    startPoint += f.Height;
                }
            }

            f.Dispose();
            brush.Dispose();
            g.Dispose();
            return image;
        }

        // New frame received by the player
        private void videoSourcePlayer_NewFrame(object sender, ref Bitmap image)
        {
            // If camera is stopping, do not try to handle the event. This might deadlock the camera according to
            // https://code.google.com/p/aforge/issues/detail?id=276
            if (this.stoppingCamera)
                return;

            if (!this.currentDevice.ToLower().Contains("opal kelly"))
            {
                int newWidth = image.Width / 2;
                int newHeight = image.Height / 2;
                Bitmap result = new Bitmap(newWidth, newHeight);
                using (Graphics gr = Graphics.FromImage(result))
                {
                    gr.DrawImage(image, 0, 0, newWidth, newHeight);
                    image = result;
                }
            }
            
            image.RotateFlip(rotate);
            
            if (this.groupBoxVideo.Size != this.videoSourcePlayer.Size)
            {
                this.Invoke(new Action(() =>
                {
                    this.groupBoxVideo.Size = this.videoSourcePlayer.Size;
                    updateWindowSize();
                }));
            }

            lock (this.snapShotLock)
            {
                if (this.snapshotQueue.Count > 0)
                {
                    string snapshotPath = this.snapshotQueue.Dequeue();
                    ImageFormat format = ImageFormat.Jpeg;
                    if (snapshotPath.ToLower().EndsWith(".png"))
                    {
                        format = ImageFormat.Png;
                    }
                    image.Save(snapshotPath, format);
                }
            }

            Bitmap motionBitmap = (Bitmap)image.Clone();

            lock (this.currentVideoFrameLock)
            {
                if (this.currentVideoFrame != null)
                {
                    this.currentVideoFrame.Dispose();
                    this.currentVideoFrame = null;
                }

                this.currentVideoFrame = (Bitmap)image.Clone();
            }

            if (detector != null)
            {               
                float motionLevel = detector.ProcessFrame(motionBitmap);
                if (motionLevel > 0)
                {
                    this.motionCount++;
                }

                // accumulate history
                motionHistory.Add(motionLevel);
                if (motionHistory.Count > 300)
                {
                    motionHistory.RemoveAt(0);
                }

                if (this.checkBoxViewMotionImage.Checked)
                {
                    image = (Bitmap)motionBitmap.Clone();
                }

                if (this.checkBoxViewMotionHistory.Checked)
                    drawMotionHistory(image);
            }

            motionBitmap.Dispose();
            image = this.drawToBitmap(image);
        }

        // Draw motion history
        private void drawMotionHistory(Bitmap image)
        {
            Color greenColor = Color.FromArgb(128, 0, 255, 0);
            Color yellowColor = Color.FromArgb(128, 255, 255, 0);
            Color redColor = Color.FromArgb(128, 255, 0, 0);

            BitmapData bitmapData = image.LockBits(new Rectangle(0, 0, image.Width, image.Height),
                ImageLockMode.ReadWrite, image.PixelFormat);

            int t1 = (int)(motionAlarmLevel * 500);
            int t2 = (int)(0.075 * 500);

            for (int i = 1, n = motionHistory.Count; i <= n; i++)
            {
                int motionBarLength = (int)(motionHistory[n - i] * 500);

                if (motionBarLength == 0)
                    continue;

                if (motionBarLength > 50)
                    motionBarLength = 50;

                Drawing.Line(bitmapData,
                    new IntPoint(image.Width - i, image.Height - 1),
                    new IntPoint(image.Width - i, image.Height - 1 - motionBarLength),
                    greenColor);

                if (motionBarLength > t1)
                {
                    Drawing.Line(bitmapData,
                        new IntPoint(image.Width - i, image.Height - 1 - t1),
                        new IntPoint(image.Width - i, image.Height - 1 - motionBarLength),
                        yellowColor);
                }

                if (motionBarLength > t2)
                {
                    Drawing.Line(bitmapData,
                        new IntPoint(image.Width - i, image.Height - 1 - t2),
                        new IntPoint(image.Width - i, image.Height - 1 - motionBarLength),
                        redColor);
                }
            }

            image.UnlockBits(bitmapData);
        }

        // Open video source
        private void openVideoSource(IVideoSource source)
        {
            // set busy cursor
            this.Cursor = Cursors.WaitCursor;

            // stop current video source
            this.closeCurrentVideoSource();

            // start new video source
            this.videoSourcePlayer.NewFrame += videoSourcePlayer_NewFrame;
            this.videoSourcePlayer.VideoSource = source;
            this.videoSourcePlayer.Start();

            this.detector = new MotionDetector(new TwoFramesDifferenceDetector(false), new MotionAreaHighlighting());
            this.statisticsTimer.Start();
            this.videoFrameCallbackTimer.Start();

            this.Cursor = Cursors.Default;
            this.Text = this.recorderTitle + " - Camera ID:" + this.currentDeviceId;
        }

        private void updateUiFromSettings()
        {
            this.updatingUiSettings = true;
            this.checkBoxFlipX.Checked = this.settings.ImageOrientation.FlipX;
            this.checkBoxFlipY.Checked = this.settings.ImageOrientation.FlipY;

            switch (settings.ImageOrientation.RotateImage)
            {
                case RotateImage.Rotate0:
                    this.radioButton0.Checked = true;
                    break;

                case RotateImage.Rotate90:
                    this.radioButton90.Checked = true;
                    break;

                case RotateImage.Rotate180:
                    this.radioButton180.Checked = true;
                    break;

                case RotateImage.Rotate270:
                    this.radioButton270.Checked = true;
                    break;
            }

            this.TopMost = this.checkBoxTopmost.Checked = this.settings.AlwaysOnTop;
            this.updatingUiSettings = false;
        }

        private void imgRotationOrFlip_CheckedChanged(object sender, EventArgs e)
        {
            if (this.updatingUiSettings)
                return;

            if (this.radioButton0.Checked)
            {
                if (!this.checkBoxFlipX.Checked && !this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.RotateNoneFlipNone;
                else if (this.checkBoxFlipX.Checked && !this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.RotateNoneFlipX;
                else if (!this.checkBoxFlipX.Checked && this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.RotateNoneFlipY;
                else if (this.checkBoxFlipX.Checked && this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.RotateNoneFlipXY;

                // Save to settings class
                this.settings.ImageOrientation.RotateImage = RotateImage.Rotate0;
            }
            else if (this.radioButton90.Checked)
            {
                if (!this.checkBoxFlipX.Checked && !this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.Rotate90FlipNone;
                else if (this.checkBoxFlipX.Checked && !this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.Rotate90FlipX;
                else if (!this.checkBoxFlipX.Checked && this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.Rotate90FlipY;
                else if (this.checkBoxFlipX.Checked && this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.Rotate90FlipXY;

                // Save to settings class
                this.settings.ImageOrientation.RotateImage = RotateImage.Rotate90;
            }
            else if (this.radioButton180.Checked)
            {
                if (!this.checkBoxFlipX.Checked && !this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.Rotate180FlipNone;
                else if (this.checkBoxFlipX.Checked && !this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.Rotate180FlipX;
                else if (!this.checkBoxFlipX.Checked && this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.Rotate180FlipY;
                else if (this.checkBoxFlipX.Checked && this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.Rotate180FlipXY;

                // Save to settings class
                this.settings.ImageOrientation.RotateImage = RotateImage.Rotate180;
            }
            else if (this.radioButton270.Checked)
            {
                if (!this.checkBoxFlipX.Checked && !this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.Rotate270FlipNone;
                else if (this.checkBoxFlipX.Checked && !this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.Rotate270FlipX;
                else if (!this.checkBoxFlipX.Checked && this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.Rotate270FlipY;
                else if (this.checkBoxFlipX.Checked && this.checkBoxFlipY.Checked)
                    this.rotate = RotateFlipType.Rotate270FlipXY;

                // Save to settings class
                this.settings.ImageOrientation.RotateImage = RotateImage.Rotate270;
            }

            // reset motion detector
            if (detector != null)
                detector.Reset();

            this.motionCount = 0;
            this.motionHistory.Clear();
            this.overlayText = string.Empty;

            // Save settings to xml.
            this.settings.ImageOrientation.FlipX = this.checkBoxFlipX.Checked;
            this.settings.ImageOrientation.FlipY = this.checkBoxFlipY.Checked;
            this.settingsHandler.SaveSettings();
        }

        private void buttonStartStopRecording_Click(object sender, EventArgs e)
        {
            // Record a video using the same method WCF service uses
            Button b = (Button)sender;
            if (b.Text == "Start recording")
            {
                this.RecordVideo(Environment.CurrentDirectory + "\\Videos\\" + Guid.NewGuid() + ".avi");
            }
            else
            {
                this.StopRecording();
            }
        }

        private void buttonTakeAnImage_Click(object sender, EventArgs e)
        {
            // Take a picture using the same method WCF service uses
            this.TakePicture(Environment.CurrentDirectory + "\\Videos\\" + Guid.NewGuid() + ".jpg");
        }

        private void buttonCameraSettings_Click(object sender, EventArgs e)
        {
            CameraSettings s = new CameraSettings(this.videoSourcePlayer.VideoSource.Source, this.settingsHandler);
            s.ShowDialog();
        }

        // On statisticsTimer event - gather statistics
        private void statisticsTimer_Tick(object sender, EventArgs e)
        {
            IVideoSource videoSource = videoSourcePlayer.VideoSource;

            if (videoSource != null)
            {
                // get number of frames since the last statisticsTimer tick
                int framesReceived = videoSource.FramesReceived;

                if (stopWatch == null)
                {
                    stopWatch = new Stopwatch();
                    stopWatch.Start();
                }
                else
                {
                    stopWatch.Stop();

                    float fps = 1000.0f * framesReceived / stopWatch.ElapsedMilliseconds;
                    textBoxVideoFps.Text = fps.ToString("F2") + " fps";

                    stopWatch.Reset();
                    stopWatch.Start();
                }
            }
            // Instruct GC to clean the memory allocated for the in-memory bitmaps.
            GC.Collect();
        }

        private void videoFrameCallbackTimer_Tick(object sender, EventArgs e)
        {
            lock (this.currentVideoFrameLock)
            {
                if (this.currentVideoFrame != null)
                {
                    if (writer != null && writer.IsOpen)
                    {
                        try
                        {
                            writer.WriteVideoFrame(this.drawToBitmap(this.currentVideoFrame));
                        }
                        catch (Exception ex)
                        {
                            this.log.Warn("WriteVideoFrame failed: ", ex);
                        }
                    }
                }
            }
        }
        // Close video source if it is running
        private void closeCurrentVideoSource()
        {
            this.statisticsTimer.Stop();
            this.videoFrameCallbackTimer.Stop();
            this.stoppingCamera = true;
            
            // Stop recording if ongoing
            this.StopRecording();
            
            if (this.videoSourcePlayer != null)
            {
                this.videoSourcePlayer.NewFrame -= videoSourcePlayer_NewFrame;

                if (this.videoSourcePlayer.VideoSource != null)
                {
                    this.videoSourcePlayer.SignalToStop();
                    // wait ~ 5 seconds
                    for (int i = 0; i < 30; i++)
                    {
                        if (!this.videoSourcePlayer.IsRunning)
                            break;
                        Thread.Sleep(100);
                    }

                    if (this.videoSourcePlayer.IsRunning)
                    {
                        this.videoSourcePlayer.Stop();
                    }
                }
            }
            this.motionHistory.Clear();

            // reset motion detector
            if (this.detector != null)
                this.detector.Reset();

            this.motionCount = 0;

            this.stoppingCamera = false;
        }

        private void videoRecorder_FormClosing(object sender, FormClosingEventArgs e)
        {
            VideoRecorderService.videoRecorderExit();
        }

        private void checkBoxTopmost_CheckedChanged(object sender, EventArgs e)
        {
            this.TopMost = ((CheckBox)sender).Checked;
            this.settings.AlwaysOnTop = this.TopMost;
            this.settingsHandler.SaveSettings();
        }

        private void refreshCaptureDevices()
        {
            if (this.videoSourcePlayer != null && this.videoSourcePlayer.IsRunning)
                this.closeCurrentVideoSource();

            // Clear the list of old devices first.
            this.captureDevices.Clear();

            // Check for video devices
            try
            {
                // enumerate video devices
                FilterInfoCollection videoDevices = new FilterInfoCollection(FilterCategory.VideoInputDevice);
                foreach (FilterInfo device in videoDevices)
                {
                    var captureDevice = new CameraSpecific
                    {
                        CameraName = device.Name,
                        MonikerString = device.MonikerString
                    };
                    this.captureDevices.Add(captureDevice);
                }
            }
            catch (Exception ex)
            {
                log.Warn("refreshCaptureDevices: Scan for video devices failed", ex);
            }
            //this.checkOrNotifyOtherVideoRecorders(false);
            this.updateDeviceList();
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            this.refreshCaptureDevices();
            if (this.captureDevices.Count > 0)
            {
                foreach (var videoDevice in captureDevices)
                {
                    if (videoDevice.MonikerString.Contains(this.currentDeviceId))
                    {
                        this.selectVideoDevice(videoDevice.CameraName, videoDevice.MonikerString);
                        break;
                    }
                }
            }
        }

        private void devicesCombo_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.devicesCombo.SelectedIndex == 0)
            {
                this.closeCurrentVideoSource();
                this.myRecorderInfo = new VideoRecorderInfo(this.recorderTitle, string.Empty);
                this.currentDeviceId = "Not Selected";
                this.Text = this.recorderTitle + " - Camera ID:" + this.currentDeviceId;
                //this.checkOrNotifyOtherVideoRecorders(true);
                return;
            }
            DeviceDataModel m = (DeviceDataModel)this.devicesCombo.SelectedItem;
            string camId = m.CameraModel.Substring(m.CameraModel.IndexOf(":") + 1);
            if (camId.Contains(" ("))
                camId = camId.Substring(0, camId.IndexOf(' '));
            try
            {
                // enumerate video devices
                FilterInfoCollection videoDevices = new FilterInfoCollection(FilterCategory.VideoInputDevice);
                foreach (FilterInfo device in videoDevices)
                {
                    var captureDevice = new CameraSpecific
                    {
                        CameraName = device.Name,
                        MonikerString = device.MonikerString
                    };
                    if (captureDevice.MonikerString.Contains(camId))
                    {
                        foreach (var ar in this.activeVideoRecorders)
                        {
                            // If camera already in use in another videorecorder, close it and take the camera in use
                            if (ar.CameraId == camId)
                            {
                                this.disconnectRemoteCamera(ar);
                                break;
                            }
                        }
                        this.selectVideoDevice(captureDevice.CameraName, captureDevice.MonikerString);
                        DeviceDataModel item = (DeviceDataModel)this.devicesCombo.SelectedItem;
                        if (item.CameraModel.Contains(" ("))
                        {
                            item.CameraModel = item.CameraModel.Substring(0, item.CameraModel.IndexOf(" ("));
                        }
                        break;
                    }
                }
            }
            catch (Exception ex)
            {
                log.Warn("refreshCaptureDevices: Scan for video devices failed", ex);
            }
        }

        private void disconnectRemoteCamera(VideoRecorderInfo info)
        {
            // Check whether another instance of VideoRecorder is running
            Process[] processes = Process.GetProcessesByName("VideoRecorder");
            foreach (Process p in processes)
            {
                try
                {
                    if (p.Id != Process.GetCurrentProcess().Id)
                    {
                        if (p.MainWindowTitle.Contains(info.MarbleInstanceNumber) && p.MainWindowTitle.Contains(info.CameraId))
                        {
                            try
                            {
                                string path = Path.GetDirectoryName(p.MainModule.FileName);
                                MarbleFwVideoRecorderClient c = new MarbleFwVideoRecorderClient(path, string.Empty, false);
                                c.DisconnectCamera();
                                c.Dispose();
                                VideoRecorderService.bringToFront(p.MainWindowHandle);
                            }
                            catch (Exception) {/* Should not happen */}
                        }
                    }
                    p.Close();
                    p.Dispose();
                }
                catch (Exception ex)
                {
                    log.Warn("disconnectRemoteCamera failed: " + ex.Message);
                }
            }
        }

        private void devicesCombo_Click(object sender, EventArgs e)
        {
            this.devicesCombo.SelectedIndexChanged -= this.devicesCombo_SelectedIndexChanged;
            //this.checkOrNotifyOtherVideoRecorders(false);
            this.updateDeviceList();
            foreach (DeviceDataModel m in this.devicesCombo.Items)
            {
                if (m.CameraModel.Contains(this.currentDeviceId))
                    this.devicesCombo.SelectedItem = m;
            }
            this.devicesCombo.SelectedIndexChanged += this.devicesCombo_SelectedIndexChanged;
        }

        private void selectVideoDevice(string deviceName, string deviceMoniker)
        {
            if (this.videoSourcePlayer != null && this.videoSourcePlayer.IsRunning)
                this.closeCurrentVideoSource();

            VideoCaptureDevice d = new VideoCaptureDevice(deviceMoniker);
            d.DesiredFrameRate = desiredCameraFps;
            d.DesiredFrameSize = new Size(this.captureHeight, this.captureWidth);
            this.currentDevice = deviceName;
            // Parse device id from moniker string
            string s1 = deviceMoniker.Substring(deviceMoniker.IndexOf("mi_00"));
            string s2 = s1.Substring(s1.IndexOf("&") + 1);
            this.currentDeviceId = s2.Substring(0, s2.IndexOf("&"));
            this.openVideoSource(d);

            if (this.videoSourcePlayer.IsRunning)
            {
                Action action = () =>
                {
                    if (this.InvokeRequired)
                        this.Invoke(new Action(() => this.buttonCameraSettings.Enabled = false));
                    else
                        this.buttonCameraSettings.Enabled = false;

                    Thread.Sleep(2000);
                    this.disableCameraAutoProperties();
                    if (this.InvokeRequired)
                        this.Invoke(new Action(() => this.buttonCameraSettings.Enabled = true));
                    else
                        this.buttonCameraSettings.Enabled = true;
                };
                Task t = Task.Factory.StartNew(action);
            }

            foreach (DeviceDataModel m in this.devicesCombo.Items)
            {
                if (m.CameraModel.Contains(this.currentDeviceId))
                {
                    this.devicesCombo.SelectedItem = m;
                }
            }

            // Save currently selected device to settings.
            this.settings.CameraSpecific.MonikerString = deviceMoniker;
            this.settings.CameraSpecific.CameraName = deviceName;
            this.settingsHandler.SaveSettings();
            //Save recorder info so that other VideoRecordes can read it if required (e.g. when a new instance of VideoRecorder is started)
            this.myRecorderInfo = new VideoRecorderInfo(this.recorderTitle, this.currentDeviceId);
            //this.checkOrNotifyOtherVideoRecorders(true);
        }

        private void readCaptureDeviceFromSettings()
        {
            if (this.captureDevices != null && this.captureDevices.Count > 0)
            {
                foreach (CameraSpecific device in this.captureDevices)
                {
                    if (device.CameraName == settings.CameraSpecific.CameraName && device.MonikerString == settings.CameraSpecific.MonikerString)
                    {
                        bool cameraAvailable = true;
                        foreach (VideoRecorderInfo i in this.activeVideoRecorders)
                        {
                            if (device.MonikerString.Contains(i.CameraId))
                                cameraAvailable = false;
                        }
                        if (cameraAvailable)
                        {
                            this.selectVideoDevice(device.CameraName, device.MonikerString);
                            return;
                        }
                        this.devicesCombo.SelectedIndex = 0;
                    }
                }

                // If only one device found, use it
                if (this.captureDevices.Count == 1)
                {
                    this.selectVideoDevice(captureDevices[0].CameraName, captureDevices[0].MonikerString);
                }
            }
        }

        private void disableCameraAutoProperties()
        {
            lock (this)
            {
                object tempSourceObject = null;

                // create source device's object
                try
                {
                    tempSourceObject = FilterInfo.CreateFilter(this.videoSourcePlayer.VideoSource.Source);
                }
                catch
                {
                    throw new ApplicationException("Failed creating device object for moniker.");
                }
                if (tempSourceObject != null)
                {
                    CameraSettings.IAMVideoProcAmp vProc = tempSourceObject as CameraSettings.IAMVideoProcAmp;
                    if (vProc != null)
                    {
                        // Disable automatic light control
                        vProc.Set(CameraSettings.VideoProcAmpProperty.BacklightCompensation, 0,
                                  CameraSettings.VideoProcAmpFlags.Manual);

                        // Read current settings from camera
                        int gainCurrent = 0;
                        CameraSettings.VideoProcAmpFlags flags;

                        vProc.Get(CameraSettings.VideoProcAmpProperty.Gain, out gainCurrent, out flags);


                        vProc.Set(CameraSettings.VideoProcAmpProperty.Gain, 0,
                                  CameraSettings.VideoProcAmpFlags.Manual);

                        // Set imagesettings from settings (if existing)
                        if (this.settings.ImageSettings.Brightness != -1 && this.settings.ImageSettings.Contrast != -1 && this.settings.ImageSettings.Exposure != -1 && 
                            this.settings.ImageSettings.Focus != -1 && this.settings.ImageSettings.Gain != -1 && this.settings.ImageSettings.WhiteBalance != -1)
                        {
                            vProc.Set(CameraSettings.VideoProcAmpProperty.Brightness, this.settings.ImageSettings.Brightness, CameraSettings.VideoProcAmpFlags.Manual);
                            vProc.Set(CameraSettings.VideoProcAmpProperty.Contrast, this.settings.ImageSettings.Contrast, CameraSettings.VideoProcAmpFlags.Manual);

                            vProc.Set(CameraSettings.VideoProcAmpProperty.Gain, this.settings.ImageSettings.Gain, CameraSettings.VideoProcAmpFlags.Manual);
                            vProc.Set(CameraSettings.VideoProcAmpProperty.WhiteBalance, this.settings.ImageSettings.WhiteBalance, CameraSettings.VideoProcAmpFlags.Manual);
                        }
                        else
                        {
                            vProc.Set(CameraSettings.VideoProcAmpProperty.Gain, gainCurrent, CameraSettings.VideoProcAmpFlags.Manual);
                        }
                    }

                    CameraSettings.IAMCameraControl cControl = tempSourceObject as CameraSettings.IAMCameraControl;
                    if (cControl != null)
                    {
                        // Read current settings from camera
                        int focusCurrent = 0;
                        int exposureCurrent = 0;
                        CameraSettings.CameraControlFlags flags;

                        cControl.Get(CameraSettings.CameraControlProperty.Focus, out focusCurrent, out flags);
                        cControl.Get(CameraSettings.CameraControlProperty.Exposure, out exposureCurrent, out flags);

                        // Set imagesettings from settings (if existing)
                        if (this.settings.ImageSettings.Brightness != -1 && this.settings.ImageSettings.Contrast != -1 && this.settings.ImageSettings.Exposure != -1 &&
                            this.settings.ImageSettings.Focus != -1 && this.settings.ImageSettings.Gain != -1 && this.settings.ImageSettings.WhiteBalance != -1)
                        {
                            cControl.Set(CameraSettings.CameraControlProperty.Focus, this.settings.ImageSettings.Focus, CameraSettings.CameraControlFlags.Manual);
                            cControl.Set(CameraSettings.CameraControlProperty.Exposure, this.settings.ImageSettings.Exposure, CameraSettings.CameraControlFlags.Manual);
                        }
                        else
                        {
                            cControl.Set(CameraSettings.CameraControlProperty.Focus, focusCurrent,
                                         CameraSettings.CameraControlFlags.Manual);

                            cControl.Set(CameraSettings.CameraControlProperty.Exposure, exposureCurrent,
                                         CameraSettings.CameraControlFlags.Manual);
                        }
                    }

                    Marshal.ReleaseComObject(tempSourceObject);
                }
            }
        }

        private void VideoRecorderGUI_Shown(object sender, EventArgs e)
        {
            this.devicesCombo.SelectedIndexChanged += this.devicesCombo_SelectedIndexChanged;
            this.refreshCaptureDevices();
            this.readCaptureDeviceFromSettings();
            this.updateWindowSize();
        }

        private void updateDeviceList()
        {
            lock (this.guiUpdateLock)
            {
                this.cameraList.Clear();
                if (this.captureDevices.Count > 0)
                {
                    int accessId = 1;
                    this.cameraList.Add(new DeviceDataModel() {AccessId = accessId, CameraModel = "Not Selected"});
                    accessId++;
                    foreach (var videoDevice in captureDevices)
                    {
                        // Parse device id from moniker string
                        string s1 = videoDevice.MonikerString.Substring(videoDevice.MonikerString.IndexOf("mi_00"));
                        string s2 = s1.Substring(s1.IndexOf("&") + 1);
                        string id = s2.Substring(0, s2.IndexOf("&"));
                        string videoRecorderInstance = string.Empty;
                        foreach (var recorder in this.activeVideoRecorders)
                        {
                            if (recorder.CameraId == id)
                                videoRecorderInstance = " (" + recorder.MarbleInstanceNumber + ")";
                        }
                        this.cameraList.Add(new DeviceDataModel()
                        {
                            AccessId = accessId,
                            CameraModel = videoDevice.CameraName + ":" + id + videoRecorderInstance
                        });
                        accessId++;
                    }
                }
                else
                {
                    this.cameraList.Add(new DeviceDataModel() {AccessId = 1, CameraModel = "No Devices"});
                    devicesCombo.Enabled = false;
                }
            }
        }

        private void checkOrNotifyOtherVideoRecorders(bool notify)
        {
            if (!notify)
                this.activeVideoRecorders.Clear();

            // Check whether another instance of VideoRecorder is running
            Process[] processes = Process.GetProcessesByName("VideoRecorder");
            foreach (Process p in processes)
            {
                try
                {
                    if (p.Id != Process.GetCurrentProcess().Id)
                    {
                        try
                        {
                            string path = Path.GetDirectoryName(p.MainModule.FileName);
                            MarbleFwVideoRecorderClient c = new MarbleFwVideoRecorderClient(path, string.Empty, false);
                            if (notify)
                                c.RecorderInfo = this.myRecorderInfo;
                            else
                            {
                                VideoRecorderInfo remoteRecorderInfo = c.RecorderInfo;
                                this.updateActiveVideoRecorderList(remoteRecorderInfo);
                            }
                            c.Dispose();
                        }
                        catch (Exception ex) {/* Should not happen */}
                    }
                    p.Close();
                    p.Dispose();
                }
                catch (Exception ex)
                {
                    log.Warn("checkOrNotifyOtherVideoRecorders failed: " + ex.Message);
                }
            }
        }

        private void updateActiveVideoRecorderList(VideoRecorderInfo recorder)
        {
            bool recorderFound = false;
            foreach (VideoRecorderInfo i in this.activeVideoRecorders)
            {
                if (i.MarbleInstanceNumber == recorder.MarbleInstanceNumber)
                {
                    i.CameraId = recorder.CameraId;
                    recorderFound = true;
                    break;
                }
            }
            if (!recorderFound)
                this.activeVideoRecorders.Add(recorder);
        }

        #endregion

        #region IVideoRecorderService methods

        public void RecordVideo(string path)
        {
            this.log.Debug("RecordVideo: " + path);
            this.motionCount = 0;
            string videoDir = path.Substring(0, path.LastIndexOf('\\'));
            if (!Directory.Exists(videoDir))
            {
                Directory.CreateDirectory(videoDir);
            }
            if (this.writer != null)
            {
                if (this.writer.IsOpen)
                {
                    this.writer.Close();
                }
            }
            else
            {
                this.writer = new VideoFileWriter();
            }

            // create new video file
            if (this.videoSourcePlayer != null && this.videoSourcePlayer.IsRunning)
            {
                // Start recording when first video frame is received
                Action action = () =>
                {
                    while (true)
                    {
                        lock (this.currentVideoFrameLock)
                        {
                            if (this.currentVideoFrame != null)
                            {
                                this.Invoke(new Action(() =>
                                {
                                    this.writer.Open(path, currentVideoFrame.Size.Width, currentVideoFrame.Size.Height,
                                        5,
                                        VideoCodec.MSMPEG4v3, videoBitrate);
                                    this.groupBoxVideoDevice.Enabled =
                                        this.groupBoxImageRotation.Enabled = groupBoxFlip.Enabled = false;
                                    this.buttonStartStopRecording.Text = "Stop recording";
                                    this.buttonStartStopRecording.FlatAppearance.BorderColor = Color.Red;
                                    textBoxVideoPath.Text = path;
                                    this.overlayText = string.Empty;
                                }));
                                break;
                            }
                            Thread.Sleep(50);
                        }
                    }
                };
                Task t = Task.Factory.StartNew(action);
            }
        }

        public void TakePicture(string path)
        {
            this.log.Debug("TakePicture: " + path);
            lock (this.snapShotLock)
            {
                this.snapshotQueue.Enqueue(path);
            }
        }

        public void StopRecording()
        {
            this.log.Debug("StopRecording");
            if (this.writer != null)
            {
                if (this.writer.IsOpen)
                {
                    try
                    {
                        this.writer.Close();
                    }
                    catch (Exception e)
                    {
                        this.log.Error("VideoRecorder writer close failed: ", e);
                    }
                }
            }
            this.groupBoxVideoDevice.Enabled = this.groupBoxImageRotation.Enabled = groupBoxFlip.Enabled = true;
            this.buttonStartStopRecording.Text = "Start recording";
            this.buttonStartStopRecording.FlatAppearance.BorderColor = Color.Green;
            textBoxVideoPath.Text = string.Empty;
            this.overlayText = string.Empty;
        }

        public void SetOverlayTextToVideo(string text)
        {
            if (!string.IsNullOrEmpty(text))
            {
                this.overlayText = text;
            }
        }

        public int GetCountMotionFrames()
        {
            return this.motionCount;
        }

        public string IsServiceAvailable()
        {
            string errorString = string.Empty;
            if (this.captureDevices != null && this.captureDevices.Count > 0)
            {
                if (this.videoSourcePlayer != null && this.videoSourcePlayer.IsRunning)
                {
                    this.log.Debug("IsServiceAvailable: True");
                    return errorString;
                }
                errorString = "Video Device Not Running";
                this.log.Warn("IsServiceAvailable: " + errorString);
                return errorString;
            }

            errorString = "No Connected Video Devices";
            this.log.Warn("IsServiceAvailable: " + errorString);
            return errorString;
        }

        private string testUnitNumber = string.Empty;
        public string TestUnitNumber
        {
            get { return this.testUnitNumber; }
            set
            {
                this.testUnitNumber = value;
                this.recorderTitle = "Video Recorder " + this.testUnitNumber;
                this.Text = this.recorderTitle + " - Camera ID:" + this.currentDeviceId;
            }
        }

        public VideoRecorderInfo RecorderInfo
        {
            get
            {
                return this.myRecorderInfo;
            }
            set
            {
                var recorder = value;
                log.Info("Active video recorder notification received: " + recorder.MarbleInstanceNumber + " " + recorder.CameraId);
                this.updateActiveVideoRecorderList(recorder);
            }
        }

        public void DisconnectCamera()
        {
            this.devicesCombo.SelectedIndexChanged -= this.devicesCombo_SelectedIndexChanged;
            this.closeCurrentVideoSource();
            this.myRecorderInfo = new VideoRecorderInfo(this.recorderTitle, string.Empty);
            this.devicesCombo.SelectedItem = this.cameraList[0];
            this.devicesCombo.SelectedIndexChanged += this.devicesCombo_SelectedIndexChanged;
        }

        #endregion
    }
}
