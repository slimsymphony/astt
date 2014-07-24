using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Marble.Views
{
    using System.ComponentModel;
    using System.IO;
    using System.Timers;
    using System.Windows.Threading;

    public enum VideoPlayerStatus
    {
        Stopped = 1,
        Playing = 2,
        Paused = 3,
    }

    /// <summary>
    /// Interaction logic for VideoPlayerView.xaml
    /// </summary>
    public partial class VideoPlayerView : UcBase, INotifyPropertyChanged
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="VideoPlayerView"/> class.
        /// </summary>
        public VideoPlayerView()
        {
            InitializeComponent();

            this.mediaElementVideo.MediaOpened += new RoutedEventHandler(mediaElementVideo_MediaOpened);
            this.mediaElementVideo.MediaEnded += new RoutedEventHandler(mediaElementVideo_MediaEnded);
        }

        #region [ VideoFilePath DependencyProperty]

        /// <summary>
        /// The video file path property.
        /// </summary>
        public static readonly DependencyProperty VideoFilePathProperty = DependencyProperty.Register(
            "VideoFilePath", typeof(string), typeof(VideoPlayerView), new FrameworkPropertyMetadata(string.Empty, OnVideoFilePathPropertyChanged));

        /// <summary>
        /// Gets or sets the video file path.
        /// </summary>
        public string VideoFilePath
        {
            get { return (string)this.GetValue(VideoFilePathProperty); }
            set { this.SetValue(VideoFilePathProperty, value); }
        }

        private static void OnVideoFilePathPropertyChanged(DependencyObject source, DependencyPropertyChangedEventArgs e)
        {
            VideoPlayerView control = source as VideoPlayerView;
            string filePath = e.NewValue.ToString();

            if (control == null) return;

            control.OnPropertyChanged("VideoFilePath");
            control.ChangeVideo(filePath);
        }

        #endregion [ VideoFilePath DependencyProperty]

        /// <summary>
        /// Gets or sets a value indicating whether is seek bar dragging.
        /// </summary>
        public bool IsSeekBarDragging { get; set; }

        /// <summary>
        /// Gets or sets the timer.
        /// </summary>
        public Timer Timer { get; set; }

        private VideoPlayerStatus playerStatus;

        /// <summary>
        /// Gets or sets the player status.
        /// </summary>
        public VideoPlayerStatus PlayerStatus
        {
            get
            {
                return this.playerStatus;
            }
            set
            {
                this.playerStatus = value;
                this.OnPropertyChanged("PlayerStatus");
            }
        }

        /// <summary>
        /// Gets the current time.
        /// </summary>
        public TimeSpan CurrentTime
        {
            get
            {
                return !this.IsSeekBarDragging ? 
                    this.mediaElementVideo.Position : 
                    new TimeSpan(TimeSpan.FromSeconds(this.sliderSeekBar.Value).Ticks);
            }
        }

        /// <summary>
        /// Gets the time left.
        /// </summary>
        public TimeSpan TimeLeft
        {
            get
            {
                if (!this.mediaElementVideo.NaturalDuration.HasTimeSpan) return new TimeSpan();

                return !this.IsSeekBarDragging ? 
                    new TimeSpan(this.mediaElementVideo.NaturalDuration.TimeSpan.Ticks - this.mediaElementVideo.Position.Ticks) : 
                    new TimeSpan(this.mediaElementVideo.NaturalDuration.TimeSpan.Ticks - TimeSpan.FromSeconds(this.sliderSeekBar.Value).Ticks);
            }
        }

        /// <summary>
        /// Gets the video file name.
        /// </summary>
        public string VideoFileName
        {
            get
            {
                if (this.mediaElementVideo == null || this.mediaElementVideo.Source == null || !this.mediaElementVideo.Source.IsFile) return string.Empty;

                return Path.GetFileName(this.mediaElementVideo.Source.LocalPath);
            }
        }

        /// <summary>
        /// Changes currently loaded video file.
        /// </summary>
        /// <param name="filePath">The file path of the video. </param>
        public void ChangeVideo(string filePath)
        {
            if (string.IsNullOrEmpty(filePath) || !File.Exists(filePath)) return;

            this.mediaElementVideo.Stop();
            this.PlayerStatus = VideoPlayerStatus.Stopped;
            this.mediaElementVideo.Source = new Uri(filePath);
            this.OnPropertyChanged("VideoFileName");

            this.initializeTimer();
        }

        private void mediaElementVideo_MediaEnded(object sender, RoutedEventArgs e)
        {
            if (this.IsSeekBarDragging) return;

            this.PlayerStatus = VideoPlayerStatus.Stopped;
        }

        private void mediaElementVideo_MediaOpened(object sender, RoutedEventArgs e)
        {
            if (!this.mediaElementVideo.NaturalDuration.HasTimeSpan) return;

            // Initializes seek bar.
            TimeSpan timeSpan = this.mediaElementVideo.NaturalDuration.TimeSpan;
            this.sliderSeekBar.Maximum = timeSpan.TotalSeconds;
            this.sliderSeekBar.SmallChange = 1;
            this.sliderSeekBar.LargeChange = Math.Min(10, timeSpan.Seconds / 10);
        }

        private void initializeTimer()
        {
            this.Timer = new Timer();
            this.Timer.Interval = 500;
            this.Timer.Elapsed += new ElapsedEventHandler(Timer_Elapsed);
            this.Timer.Start();
        }

        private void Timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            this.OnPropertyChanged("CurrentTime");
            this.OnPropertyChanged("TimeLeft");

            if (!this.IsSeekBarDragging)
                this.Dispatcher.Invoke(DispatcherPriority.Normal, new Action(this.updateSeekBar));
        }

        private void updateSeekBar()
        {
            if (this.IsSeekBarDragging) return;

            this.sliderSeekBar.Value = this.mediaElementVideo.Position.TotalSeconds;
        }

        private void buttonRewind_Click(object sender, RoutedEventArgs e)
        {

        }

        private void buttonPlayFromStart_Click(object sender, RoutedEventArgs e)
        {

        }

        private void buttonPlayPause_Click(object sender, RoutedEventArgs e)
        {
            if (this.PlayerStatus == VideoPlayerStatus.Playing && this.mediaElementVideo.CanPause)
            {
                this.mediaElementVideo.Pause();
                this.PlayerStatus = VideoPlayerStatus.Paused;
            }
            else
            {
                if (this.PlayerStatus == VideoPlayerStatus.Stopped)
                    this.mediaElementVideo.Position = new TimeSpan(0);

                this.mediaElementVideo.Play();
                this.PlayerStatus = VideoPlayerStatus.Playing;
            }
        }

        private void buttonStop_Click(object sender, RoutedEventArgs e)
        {
            this.mediaElementVideo.Stop();
            this.PlayerStatus = VideoPlayerStatus.Stopped;
        }

        private void buttonFastForward_Click(object sender, RoutedEventArgs e)
        {
            
        }

        private void sliderSeekBar_DragStarted(object sender, System.Windows.Controls.Primitives.DragStartedEventArgs e)
        {
            this.IsSeekBarDragging = true;
            this.PlayerStatus = VideoPlayerStatus.Paused;
            this.Timer.Interval = 100;
        }

        private void sliderSeekBar_DragCompleted(object sender, System.Windows.Controls.Primitives.DragCompletedEventArgs e)
        {
            this.IsSeekBarDragging = false;
            this.mediaElementVideo.Position = TimeSpan.FromSeconds(this.sliderSeekBar.Value);
            this.Timer.Interval = 500;
        }

        private void buttonNextFrame_Click(object sender, RoutedEventArgs e)
        {
            this.mediaElementVideo.Pause();
            this.PlayerStatus = VideoPlayerStatus.Paused;

            this.mediaElementVideo.Position = TimeSpan.FromMilliseconds(this.mediaElementVideo.Position.TotalMilliseconds + 200);
        }

        private void buttonPreviousFrame_Click(object sender, RoutedEventArgs e)
        {
            this.mediaElementVideo.Pause();
            this.PlayerStatus = VideoPlayerStatus.Paused;

            this.mediaElementVideo.Position = TimeSpan.FromMilliseconds(this.mediaElementVideo.Position.TotalMilliseconds - 200);
        }

        private void sliderSeekBar_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (this.IsSeekBarDragging) this.mediaElementVideo.Position = TimeSpan.FromSeconds(this.sliderSeekBar.Value);
        }

        #region INotifyPropertyChanged Members

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }
}
