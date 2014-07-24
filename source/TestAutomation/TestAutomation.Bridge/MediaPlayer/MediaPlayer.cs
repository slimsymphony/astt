using Managed.Adb;
using Managed.Adb.IO;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;
using TestAutomation.Bridge.ScriptingTools;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Different media types
    /// </summary>
    public enum MediaType
    {
        /// <summary>
        /// Audio
        /// </summary>
        Audio,
        
        /// <summary>
        /// Image
        /// </summary>
        Image,
        
        /// <summary>
        /// Video
        /// </summary>
        Video,

        /// <summary>
        /// WebUrl
        /// </summary>
        WebUrl
    }

    /// <summary>
    /// Media player class for starting media files directly by passing the media file location
    /// </summary>
    public sealed class MediaPlayer : PythonCallable
    {
        private TABConnection m_tab;

        private const string COMMAND_FORMAT = "am start -a android.intent.action.VIEW -d \"file:///{0}\" -t {1}";
        private const string COMMAND_FORMAT_MUSIC_PLAYER = "am start -n com.android.music/.MediaPlaybackActivity -d \"file:///{0}\"";
        private const string COMMAND_FORMAT_WEB_LINK = "am start -a android.intent.action.VIEW -d {0}";
        private const string COMMAND_HEADSET_PLUG = "am broadcast -a android.intent.action.HEADSET_PLUG --ei state {0}";
        private const string DefaultImageViewer = "com.android.gallery3d/.app.Gallery";
        private const string DefaultVideoPlayer = "com.android.gallery3d/.app.MovieActivity";

        private Regex m_weburlPattern = new Regex(@"^((http|ftp)(s)*://)", RegexOptions.Compiled | RegexOptions.IgnoreCase);

        #region "Image MIME Types"

        /// <summary>
        /// Predefined mime types fro image files
        /// </summary>
        private Dictionary<string, string> m_imageMimeTypes = new Dictionary<string, string>
        {
            {"3ds", "image/x-3ds"},
            {"art", "image/x-jg"},
            {"bm", "image/bmp"},
            {"bmp", "image/bmp"}, //image/x-windows-bmp
            {"btif", "image/prs.btif"},
            {"cgm", "image/cgm"},
            {"cmx", "image/x-cmx"},
            {"djv", "image/vnd.djvu"},
            {"djvu", "image/vnd.djvu"},
            {"dwg", "image/vnd.dwg"}, //image/x-dwg
            {"dxf", "image/vnd.dxf"}, //image/x-dwg
            {"fbs", "image/vnd.fastbidsheet"},
            {"fh", "image/x-freehand"},
            {"fhc", "image/x-freehand"},
            {"fh4", "image/x-freehand"},
            {"fh5", "image/x-freehand"},
            {"fh7", "image/x-freehand"},
            {"fif", "image/fif"},
            {"flo", "image/florian"},
            {"fpx", "image/vnd.fpx"}, //image/vnd.net-fpx
            {"fst", "image/vnd.fst"},
            {"g3", "image/g3fax"},
            {"gif", "image/gif"},
            {"ico", "image/x-icon"},
            {"ief", "image/ief"},
            {"iefs", "image/ief"},
            {"jfif", "image/jpeg"}, //image/pjpeg
            {"jfif-tbnl", "image/jpeg"},
            {"jpe", "image/jpeg"}, //image/pjpeg
            {"jpeg", "image/jpeg"}, //image/pjpeg
            {"jpg", "image/jpeg"}, //image/pjpeg
            {"jps", "image/x-jps"},
            {"jut", "image/jutvision"},
            {"ktx", "image/ktx"},
            {"mcf", "image/vasa"},
            {"mdi", "image/vnd.ms-modi"},
            {"mmr", "image/vnd.fujixerox.edmics-mmr"},
            {"nap", "image/naplps"},
            {"naplps", "image/naplps"},
            {"nif", "image/x-niff"},
            {"niff", "image/x-niff"},
            {"npx", "image/vnd.net-fpx"},
            {"pbm", "image/x-portable-bitmap"},
            {"pct", "image/x-pict"},
            {"pcx", "image/x-pcx"},
            {"pgm", "image/x-portable-graymap"},
            {"pic", "image/pict"},
            {"pict", "image/pict"},
            {"pm", "image/x-xpixmap"},
            {"png", "image/png"},
            {"pnm", "image/x-portable-anymap"},
            {"ppm", "image/x-portable-pixmap"},
            {"psd", "image/vnd.adobe.photoshop"},
            {"qif", "image/x-quicktime"},
            {"qit", "image/x-quicktime"},
            {"qitf", "image/x-quicktime"},
            {"ras", "image/cmu-raster"}, //image/x-cmu-raster
            {"rast", "image/cmu-raster"},
            {"rf", "image/vnd.rn-realflash"},
            {"rgb", "image/x-rgb"},
            {"rlc", "image/vnd.fujixerox.edmics-rlc"},
            {"rp", "image/vnd.rn-realpix"},
            {"sid", "image/x-mrsid-image"},
            {"sgi", "image/sgi"},
            {"sub", "image/vnd.dvb.subtitle"},
            {"svf", "image/vnd.dwg"}, //image/x-dwg
            {"svg", "image/svg+xml"},
            {"svgz", "image/svg+xml"},
            {"tga", "image/x-tga"},
            {"tif", "image/tiff"}, //image/x-tiff
            {"tiff", "image/tiff"}, //image/x-tiff
            {"turbot", "image/florian"},
            {"uvi", "image/vnd.dece.graphic"},
            {"uvvi", "image/vnd.dece.graphic"},
            {"uvg", "image/vnd.dece.graphic"},
            {"uvvg", "image/vnd.dece.graphic"},
            {"wbmp", "image/vnd.wap.wbmp"},
            {"wdp", "image/vnd.ms-photo"},
            {"webp", "image/webp"},
            {"xbm", "image/x-xbitmap"}, //image/x-xbm, image/xbm
            {"xif", "image/vnd.xiff"},
            {"xpm", "image/x-xpixmap"}, //image/xpm
            {"x-png", "image/png"},
            {"xwd", "image/x-xwd"} //image/x-xwindowdump
        };

        #endregion

        #region "Video MIME Types"

        /// <summary>
        /// Predefined mime types fro video files
        /// </summary>
        private Dictionary<string, string> m_videoMimeTypes = new Dictionary<string, string>
        {
            {"3gp", "video/3gpp"},
            {"3g2", "video/3gpp2"},
            {"afl", "video/animaflex"},
            {"asf", "video/x-ms-asf"},
            {"asx", "video/x-ms-asf"}, //video/x-ms-asf-plugin
            {"avi", "video/x-msvideo"}, //video/avi, video/x-msvideo
            {"avs", "video/avs-video"},
            {"cim", "video/cim"},
            {"dfi", "video/x-dv"},
            {"dl", "video/dl"}, //video/x-dl
            {"dv", "video/x-dv"},
            {"dvb", "video/vnd.dvb.file"},
            {"f4v", "video/x-f4v"},
            {"fli", "video/fli"}, //video/x-fli
            {"flv", "video/x-flv"},
            {"fvt", "video/vnd.fvt"},
            {"fmf", "video/x-atomic3d-feature"},
            {"gl", "video/gl"}, //video/x-gl
            {"h261", "video/h261"},
            {"h263", "video/h263"},
            {"h264", "video/h264"},
            {"isu", "video/x-isvideo"},
            {"jpgv", "video/jpeg"},
            {"jpm", "video/jpm"},
            {"jpgm", "video/jpm"},
            {"m1v", "video/mpeg"},
            {"m2v", "video/mpeg"},
            {"m4u", "video/vnd.mpegurl"},
            {"m4v", "video/x-m4v"},
            {"mj2", "video/mj2"},
            {"mjp2", "video/mj2"},
            {"mjpg", "video/x-motion-jpeg"},
            {"mkv", "video/x-matroska"},
            {"mk3d", "video/x-matroska"},
            {"mks", "video/x-matroska"},
            {"mng", "video/x-mng"},
            {"moov", "video/quicktime"},
            {"mov", "video/quicktime"},
            {"movie", "video/x-sgi-movie"},
            {"mp2", "video/mpeg"}, //video/x-mpeg, video/x-mpeq2a
            {"mp3", "video/mpeg"}, //video/x-mpeg
            {"mp4", "video/mp4"},
            {"mp4v", "video/mp4"},
            {"mpg4", "video/mp4"},
            {"mpa", "video/mpeg"},
            {"mpe", "video/mpeg"},
            {"mpg", "video/mpeg"},
            {"mpeg", "video/mpeg"},
            {"mpeg4", "video/mpeg4"},
            {"mv", "video/x-sgi-movie"},
            {"mxu", "video/vnd.mpegurl"},
            {"ogg", "video/ogg"},
            {"ogv", "video/ogg"},
            {"pyv", "video/vnd.ms-playready.media.pyv"},
            {"pvp", "video/mp4"},
            {"pvs", "video/mp4"},
            {"pvx", "video/mp4"},
            {"qt", "video/quicktime"},
            {"qtc", "video/x-qtc"},
            {"rm", "video/vnd.rn-realvideo"},
            {"rmvb", "video/vnd.rn-realvideo"},
            {"rv", "video/vnd.rn-realvideo"},
            {"scm", "video/x-scm"},
            {"smv", "video/x-smv"},
            {"ts", "video/mp2t"},
            {"uvh", "video/vnd.dece.hd"},
            {"uvvh", "video/vnd.dece.hd"},
            {"uvm", "video/vnd.dece.mobile"},
            {"uvvm", "video/vnd.dece.mobile"},
            {"uvp", "video/vnd.dece.pd"},
            {"uvvp", "video/vnd.dece.pd"},
            {"uvs", "video/vnd.dece.sd"},
            {"uvvs", "video/vnd.dece.sd"},
            {"uvu", "video/vnd.uvvu.mp4"},
            {"uvvu", "video/vnd.uvvu.mp4"},
            {"uvv", "video/vnd.dece.video"},
            {"uvvv", "video/vnd.dece.video"},
            {"vdo", "video/vdo"},
            {"viv", "video/vivo"}, //video/vnd.vivo
            {"vivo", "video/vivo"}, //video/vnd.vivo
            {"vob", "video/x-ms-vob"},
            {"vos", "video/vosaic"},
            {"webm", "video/webm"},
            {"wm", "video/x-ms-wm"},
            {"wmv", "video/x-ms-wmv"},
            {"wmx", "video/x-ms-wmx"},
            {"wvx", "video/x-ms-wvx"},
            {"xdr", "video/x-amt-demorun"},
            {"xsr", "video/x-amt-showrun"},       
        };

        #endregion

        #region "Audio MIME Types"

        /// <summary>
        /// Predefined mime types fro audio files
        /// </summary>
        private Dictionary<string, string> m_audioMimeTypes = new Dictionary<string, string>
        {
            {"3ga", "audio/mp4"}, //audio/3gpp
            {"3gp", "audio/3gpp"},
            {"aac", "audio/x-aac"},
            {"eaac", "audio/x-aac"},
            {"adp", "audio/adpcm"},
            {"aif", "audio/aiff"}, //audio/x-aiff
            {"aifc", "audio/aiff"}, //audio/x-aiff
            {"aiff", "audio/aiff"}, //audio/x-aiff
            {"amr", "audio/AMR"}, //audio/3gpp
            {"au", "audio/basic"}, //audio/x-au
            {"caf", "audio/x-caf"},
            {"dra", "audio/vnd.dra"},
            {"dts", "audio/vnd.dts"},
            {"dtshd", "audio/vnd.dts.hd"},
            {"ecelp4800", "audio/vnd.nuera.ecelp4800"},
            {"ecelp7470", "audio/vnd.nuera.ecelp7470"},
            {"ecelp9600", "audio/vnd.nuera.ecelp9600"},
            {"eol", "audio/vnd.digital-winds"},
            {"flac", "audio/x-flac"},
            {"func", "audio/make"},
            {"gsd", "audio/x-gsm"},
            {"gsm", "audio/x-gsm"},
            {"imy", "audio/midi"},
            {"it", "audio/it"},
            {"jam", "audio/x-jam"},
            {"kar", "audio/midi"},
            {"l16", "audio/L24"},
            {"la", "audio/nspaudio"}, //audio/x-nspaudio
            {"lam", "audio/x-liveaudio"},
            {"lma", "audio/nspaudio"}, //audio/x-nspaudio
            {"lvp", "audio/vnd.lucent.voice"},
            {"m2a", "audio/mpeg"},
            {"m3a", "audio/mpeg"},
            {"m3u", "audio/x-mpequrl"},
            {"m4a", "audio/mp4"}, //audio/m4a
            {"m4b", "audio/mp4"},
            {"m4p", "audio/mp4"},
            {"mid", "audio/midi"}, //audio/x-mid, audio/x-midi
            {"midi", "audio/midi"}, //audio/x-mid, audio/x-midi
            {"mjf", "audio/x-vnd.audioexplosion.mjuicemediafile"},
            {"mka", "audio/x-matroska"}, //audio/ogg
            {"mkv", "audio/x-matroska"}, //audio/ogg
            {"mmf", "audio/mmf"},
            {"mod", "audio/mod"}, //audio/x-mod
            {"mp2", "audio/mpeg"}, //audio/x-mpeg
            {"mp2a", "audio/mpeg"},
            {"mp3", "audio/mpeg3"}, //audio/x-mpeg-3
            {"mp4", "audio/mp4"},
            {"mp4a", "audio/mp4"},
            {"mpa", "audio/mpeg"},
            {"mpg", "audio/mpeg"},
            {"mpga", "audio/mpeg"},
            {"mxmf", "audio/midi"},
            {"my", "audio/make"},
            {"ogg", "audio/ogg"},
            {"oga", "audio/ogg"},
            {"ota", "audio/midi"},
            {"pcm", "audio/L24"},
            {"pfunk", "audio/make"}, //audio/make.my.funk
            {"pya", "audio/vnd.ms-playready.media.pya"},
            {"qcp", "audio/vnd.qcelp"},
            {"ra", "audio/x-pn-realaudio"}, //audio/x-pn-realaudio-plugin, audio/x-realaudio
            {"ram", "audio/x-pn-realaudio"},
            {"rip", "audio/vnd.rip"},
            {"rm", "audio/x-pn-realaudio"},
            {"rmi", "audio/mid"},
            {"rmm", "audio/x-pn-realaudio"},
            {"rmp", "audio/x-pn-realaudio"}, //audio/x-pn-realaudio-plugin
            {"rpm", "audio/x-pn-realaudio-plugin"},
            {"rtx", "audio/midi"},
            {"rtttl", "audio/midi"},
            {"s3m", "audio/s3m"},
            {"sid", "audio/x-psid"},
            {"sil", "audio/silk"},
            {"snd", "audio/basic"}, //audio/x-adpcm
            {"spx", "audio/ogg"},
            {"ts", "video/mp2t"},
            {"tsi", "audio/tsp-audio"},
            {"tsp", "audio/tsplayer"},
            {"uva", "audio/vnd.dece.audio"},
            {"uvva", "audio/vnd.dece.audio"},
            {"voc", "audio/voc"}, //audio/x-voc
            {"vox", "audio/voxware"},
            {"vqe", "audio/x-twinvq-plugin"},
            {"vqf", "audio/x-twinvq"},
            {"vql", "audio/x-twinvq-plugin"},
            {"wav", "audio/wav"}, //audio/x-wav
            {"wax", "audio/x-ms-wax"},
            {"weba", "audio/webm"},
            {"wma", "audio/x-ms-wma"},
            {"xm", "audio/xm"},
            {"xmf", "audio/midi"}
        };

        #endregion

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="tab">Instnece of a device in which to play the media files</param>
        internal MediaPlayer(TABConnection tab)
        {
            m_tab = tab;
        }

        /// <summary>
        /// Launches a web url with the default browser
        /// </summary>
        /// <param name="url"></param>
        public void LaunchWebUrl(string url)
        {
            PlayMedia(MediaType.WebUrl, url, null);
        }

        /// <summary>
        /// Shows an image file with the default image viewer
        /// </summary>
        /// <param name="remoteImagePath">Location of the image file in the device</param>
        /// <param name="viewer">The viewer activity to be used</param>
        public void ShowImage(string remoteImagePath, string viewer = DefaultImageViewer)
        {
            ShowImage(remoteImagePath, null, viewer);
        }

        /// <summary>
        /// Shows an image file with the default image viewer
        /// </summary>
        /// <param name="remoteImagePath">Location of the image file in the device</param>
        /// <param name="mimeType">Mime type of the image file</param>
        /// <param name="viewer">The viewer activity to be used</param>
        public void ShowImage(string remoteImagePath, string mimeType, string viewer)
        {
            PlayMedia(MediaType.Image, remoteImagePath, mimeType, viewer);
        }

        /// <summary>
        /// Plays a video file with the default video player
        /// </summary>
        /// <param name="remoteVideoPath">Location of the video file in the device</param>
        /// <param name="viewer">The viewer activity to be used</param>
        public void PlayVideo(string remoteVideoPath, string viewer = DefaultVideoPlayer)
        {
            PlayVideo(remoteVideoPath, null, viewer);
        }

        /// <summary>
        /// Plays a video file with the default video player
        /// </summary>
        /// <param name="remoteVideoPath">Location of the video file in the device</param>
        /// <param name="mimeType">Mime type of the video file</param>
        /// <param name="viewer">The viewer activity to be used</param>
        public void PlayVideo(string remoteVideoPath, string mimeType, string viewer)
        {
            PlayMedia(MediaType.Video, remoteVideoPath, mimeType, viewer);
        }

        /// <summary>
        /// Plays an audio file with the default audio player
        /// </summary>
        /// <param name="remoteAudioPath">Location of the audio file in the device</param>
        public void PlayAudio(string remoteAudioPath)
        {
            PlayAudio(remoteAudioPath, null);
        }

        /// <summary>
        /// Plays an audio file with the default audio player
        /// </summary>
        /// <param name="remoteAudioPath">Location of the audio file in the device</param>
        /// <param name="mimeType">Mime type of the audio file</param>
        public void PlayAudio(string remoteAudioPath, string mimeType)
        {
            PlayMedia(MediaType.Audio, remoteAudioPath, mimeType);
        }

        /// <summary>
        /// Plays an audio file with the music player
        /// </summary>
        /// <param name="remoteAudioPath">Location of the audio file in the device</param>
        public void PlayWithMusicPlayer(string remoteAudioPath)
        {
            if (string.IsNullOrEmpty(remoteAudioPath))
            {
                throw new ArgumentNullException("remoteAudioPath");
            }

            if (!m_tab.File.FileExists(remoteAudioPath))
            {
                throw new FileNotFoundException(remoteAudioPath);
            }

            var command = string.Format(COMMAND_FORMAT_MUSIC_PLAYER, m_tab.File.FormatFilePath(remoteAudioPath));
            var error = GetError(m_tab.ShellCommand(command));
            if (error != null)
            {
                throw error;
            }
        }

        /// <summary>
        /// Plays a media file with the default media player dedicated for a given media type
        /// </summary>
        /// <param name="mediaType">Type of the media: audio, image or video</param>
        /// <param name="mediaPath">Location of the media file in the device</param>
        /// <param name="mimeType">Mime type of the media file</param>
        /// <param name="activity">Name of the activity with which to launch</param>
        private void PlayMedia(MediaType mediaType, string mediaPath, string mimeType, string activity = null)
        {
            if (string.IsNullOrEmpty(mediaPath))
            {
                throw new ArgumentNullException("mediaPath");
            }

            string command = null;

            if (mediaType == MediaType.WebUrl)
            {
                if (!IsIPAddress(mediaPath) && !m_weburlPattern.IsMatch(mediaPath))
                {
                    mediaPath = "http://" + mediaPath.TrimStart('/');
                }
                command = string.Format(COMMAND_FORMAT_WEB_LINK, mediaPath);
            }
            else
            {
                mediaPath = mediaPath.Replace("file:", "").Trim('/');

                if (!m_tab.File.FileExists(mediaPath))
                {
                    throw new FileNotFoundException(mediaPath);
                }

                if (!string.IsNullOrEmpty(mimeType))
                {
                    var items = mimeType.Split(new char[] { '/' }, StringSplitOptions.RemoveEmptyEntries);

                    if (items.Length == 1)
                    {
                        mimeType = mediaType.ToString().ToLower() + '/' + mimeType;
                    }
                }

                var mime = !string.IsNullOrEmpty(mimeType) ? mimeType : GetMimeType(mediaType, mediaPath);

                if (mime == null)
                {
                    throw new Exception(string.Format("Couldn't figure out a MIME type for {0}", LinuxPath.GetFileName(mediaPath)));
                }

                command = string.Format(COMMAND_FORMAT, m_tab.File.FormatFilePath(mediaPath), mime);
            }
            if (command != null)
            {
                if (!string.IsNullOrEmpty(activity)) command += string.Format(" -n {0}", activity);
                var error = GetError(m_tab.ShellCommand(command));
                if (error != null)
                {
                    throw error;
                }
            }
        }

        /// <summary>
        /// Simulates headset plugging in
        /// </summary>
        public void ConnectHeadset()
        {
            ConnectHeadset(true);
        }

        /// <summary>
        /// Simulates headset plugging out
        /// </summary>
        public void DisconnectHeadset()
        {
            ConnectHeadset(false);
        }

        /// <summary>
        /// Simulates plugging headset in/out
        /// </summary>
        /// <param name="enable">True for in; false for out</param>
        private void ConnectHeadset(bool enable)
        {
            var command = string.Format(COMMAND_HEADSET_PLUG, (enable ? 1 : 0));
            m_tab.Shell.ExecuteCommand(command);
        }

        /// <summary>
        /// Gets the mime type of the media file based on its file extension
        /// </summary>
        /// <param name="mediaType">Type of the media: audio, image or video</param>
        /// <param name="remotePath">Location of the media file in the device</param>
        /// <returns>Mime type, or null if not found</returns>
        private string GetMimeType(MediaType mediaType, string remotePath)
        {
            string ext = Path.GetExtension(remotePath).Trim('.').ToLower();

            var dict = (mediaType == MediaType.Audio) ? m_audioMimeTypes : ((mediaType == MediaType.Image) ? m_imageMimeTypes : m_videoMimeTypes);

            if (dict.ContainsKey(ext))
            {
                return dict[ext];
            }

            return null;
        }

        /// <summary>
        /// Gets error from response lines in the receiver
        /// </summary>
        /// <param name="data">Data from which to search an error</param>
        /// <returns>Exception intance which to throw</returns>
        private Exception GetError(string[] data)
        {
            var lines = data.ToList();
            var error = lines.Find(l => l.Trim().ToLower().StartsWith("error:"));
            if (error != null)
            {
                var builder = new StringBuilder();
                int errorLine = lines.IndexOf(error);
                for (int i = errorLine; i < lines.Count; i++)
                {
                    if (i == errorLine)
                    {
                        lines[i] = lines[i].Replace("error:", "").Replace("Error:", "");
                    }
                    builder.AppendLine(lines[i].Trim());
                }
                var message = builder.ToString();
                return new Exception(message);
            }
            return null;
        }

        /// <summary>
        /// Checks if the string is an ip address - either v4 or v6
        /// </summary>
        /// <param name="str">Input string</param>
        /// <returns>True is valid ip address</returns>
        private bool IsIPAddress(string str)
        {
            IPAddress tmp;
            return IPAddress.TryParse(str, out tmp);
        }
    }
}
