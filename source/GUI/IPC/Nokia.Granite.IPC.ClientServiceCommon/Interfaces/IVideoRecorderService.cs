using System.Drawing;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Xml.Serialization;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;

namespace TestAutomation.Gui.Marble.IPC.Interfaces
{
    /// <summary>
    /// </summary>
    [ServiceContract]
    public interface IVideoRecorderService
    {
        [OperationContract]
        void RecordVideo(string path);

        [OperationContract]
        void TakePicture(string path);

        [OperationContract]
        void StopRecording();

        [OperationContract]
        void SetOverlayTextToVideo(string text);

        [OperationContract]
        int GetCountMotionFrames();

        /// <summary>
        /// Checks whether service is available
        /// </summary>
        /// <returns>Empty string if service is available. Otherwise a reason why service is not available.</returns>
        [OperationContract]
        string IsServiceAvailable();

        string TestUnitNumber
        {
            [OperationContract]
            get;

            [OperationContract]
            set;
        }

        /// <summary>
        /// Get the camera model currently in use by an instance of VideoRecorder
        /// Set the camera model currently in use by an instance of VideoRecorder
        /// </summary>
        VideoRecorderInfo RecorderInfo
        {
            [OperationContract]
            get;

            [OperationContract]
            set;
        }

        /// <summary>
        /// Requests VideoRecorder to disconnect the camera currently in use so that another instance of VideoRecorder can use the camera.
        /// </summary>
        [OperationContract]
        void DisconnectCamera();
    }

    #region DataContract for VideoRecorder WCF methods

    [DataContract]
    public class VideoRecorderInfo
    {
        public VideoRecorderInfo(string marbleInstanceNumber, string cameraId)
        {
            this.MarbleInstanceNumber = marbleInstanceNumber;
            this.CameraId = cameraId;
        }

        [DataMember]
        public string MarbleInstanceNumber;

        [DataMember]
        public string CameraId;
    }

    #endregion

    #region VideoRecorder Settings

    [DataContract]
    public enum RotateImage
    {
        [EnumMember]
        Rotate0,
        [EnumMember]
        Rotate90,
        [EnumMember]
        Rotate180,
        [EnumMember]
        Rotate270
    }

    /// <summary>
    /// The VideoRecorderServiceSettings parameterclass.
    /// The class needs to be public for xml serializer to work.
    /// </summary>
    public class VideoRecorderServiceSettings : BaseSettings
    {
        [XmlElement]
        public bool AlwaysOnTop { get; set; }

        [XmlElement]
        public ImageOrientation ImageOrientation { get; set; }

        [XmlElement]
        public CameraSpecific CameraSpecific { get; set; }

        [XmlElement]
        public ImageSettings ImageSettings { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="VideoRecorderServiceSettings"/> class.
        /// </summary>
        public VideoRecorderServiceSettings()
        {
            this.AlwaysOnTop = true;
            this.ImageOrientation = new ImageOrientation();
            this.CameraSpecific = new CameraSpecific();
            this.ImageSettings = new ImageSettings();
        }
    }

    /// <summary>
    /// Class for image orientation settings
    /// </summary>
    public class ImageOrientation
    {
        [XmlAttribute]
        public RotateImage RotateImage { get; set; }

        [XmlAttribute]
        public bool FlipX { get; set; }

        [XmlAttribute]
        public bool FlipY { get; set; }

        public ImageOrientation()
        {
            this.RotateImage = RotateImage.Rotate0;
            this.FlipX = false;
            this.FlipY = false;
        }
    }

    /// <summary>
    /// Class for camera specific settings
    /// </summary>
    public class CameraSpecific
    {
        [XmlAttribute]
        public string CameraName { get; set; }

        [XmlAttribute]
        public string MonikerString { get; set; }

        public CameraSpecific()
        {
            this.CameraName = string.Empty;
            this.MonikerString = string.Empty;
        }
    }

    /// <summary>
    /// Class for image settings
    /// </summary>
    public class ImageSettings
    {
        [XmlAttribute]
        public int Exposure { get; set; }

        [XmlAttribute]
        public int Gain { get; set; }

        [XmlAttribute]
        public int Brightness { get; set; }

        [XmlAttribute]
        public int Contrast { get; set; }

        [XmlAttribute]
        public int WhiteBalance { get; set; }

        [XmlAttribute]
        public int Focus { get; set; }

        public ImageSettings()
        {
            this.Exposure = -1;
            this.Gain = -1;
            this.Brightness = -1;
            this.Contrast = -1;
            this.WhiteBalance = -1;
            this.Focus = -1;
        }
    }

    #endregion
}
