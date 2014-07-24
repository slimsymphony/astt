using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using AForge.Video.DirectShow;
using TestAutomation.Gui.Marble.IPC.Interfaces;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;

namespace TestAutomation.Gui.Marble
{
    public partial class CameraSettings : Form
    {
        #region DirectShow wrapper for camera properties

        /// <summary>
        /// See http://msdn.microsoft.com/query/dev10.query?appId=Dev10IDEF1&l=EN-US&k=k(VIDEOPROCAMPPROPERTY);k(SOLUTIONITEMSPROJECT);k(TargetFrameworkMoniker-%22.NETFRAMEWORK%2cVERSION%3dV4.0%22);k(DevLang-CSHARP)&rd=true
        /// </summary>
        public enum VideoProcAmpProperty
        {
            /// <summary>
            /// Specifies the brightness, also called the black level. For NTSC, the value is expressed in IRE units * 100.
            /// For non-NTSC sources, the units are arbitrary, with zero representing blanking and 10,000 representing pure white.
            /// Values range from –10,000 to 10,000.
            /// </summary>
            Brightness,
            
            /// <summary>
            /// Specifies the contrast, expressed as gain factor * 100. Values range from zero to 10,000. 
            /// </summary>
            Contrast,

            /// <summary>
            /// Specifies the hue, in degrees * 100. Values range from -180,000 to 180,000 (-180 to +180 degrees).
            /// </summary>
            Hue,

            /// <summary>
            /// Specifies the saturation. Values range from 0 to 10,000.
            /// </summary>
            Saturation,

            /// <summary>
            /// Specifies the sharpness. Values range from 0 to 100.
            /// </summary>
            Sharpness,

            /// <summary>
            /// Specifies the gamma, as gamma * 100. Values range from 1 to 500. 
            /// </summary>
            Gamma,

            /// <summary>
            /// Specifies the color enable setting. The possible values are 0 (off) and 1 (on).
            /// </summary>
            ColorEnable,

            /// <summary>
            /// Specifies the white balance, as a color temperature in degrees Kelvin. The range of values depends on the device.
            /// </summary>
            WhiteBalance,

            /// <summary>
            /// Specifies the backlight compensation setting. Possible values are 0 (off) and 1 (on).
            /// For Logitech cameras this should be the automatic light setting and should be turned off.
            /// </summary>
            BacklightCompensation,

            /// <summary>
            /// Specifies the gain adjustment. Zero is normal. Positive values are brighter and negative values are darker. The range of values depends on the device.
            /// </summary>
            Gain
        }

        /// <summary>
        /// From VideoProcAmpFlags
        /// </summary>
        [Flags]
        public enum VideoProcAmpFlags
        {
            None = 0,

            /// <summary>
            /// The setting is controlled automatically.
            /// </summary>
            Auto = 0x0001,

            /// <summary>
            /// The setting is controlled manually.
            /// </summary>
            Manual = 0x0002
        }

        /// <summary>
        /// From CameraControlProperty
        /// </summary>
        public enum CameraControlProperty
        {
            Pan = 0,
            Tilt,
            Roll,
            Zoom,
            Exposure,
            Iris,
            Focus
        }

        /// <summary>
        /// From CameraControlFlags
        /// </summary>
        [Flags]
        public enum CameraControlFlags
        {
            None = 0x0,
            Auto = 0x0001,
            Manual = 0x0002
        }

        [ComImport, System.Security.SuppressUnmanagedCodeSecurity, Guid("C6E13360-30AC-11d0-A18C-00A0C9118956"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
        public interface IAMVideoProcAmp
        {
            [PreserveSig]
            int GetRange(
                [In] VideoProcAmpProperty Property,
                [Out] out int pMin,
                [Out] out int pMax,
                [Out] out int pSteppingDelta,
                [Out] out int pDefault,
                [Out] out VideoProcAmpFlags pCapsFlags
                );

            [PreserveSig]
            int Set(
                [In] VideoProcAmpProperty Property,
                [In] int lValue,
                [In] VideoProcAmpFlags Flags
                );

            [PreserveSig]
            int Get(
                [In] VideoProcAmpProperty Property,
                [Out] out int lValue,
                [Out] out VideoProcAmpFlags Flags
                );
        }

        [ComImport, System.Security.SuppressUnmanagedCodeSecurity, Guid("C6E13370-30AC-11d0-A18C-00A0C9118956"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
        public interface IAMCameraControl
        {
            [PreserveSig]
            int GetRange(
                [In] CameraControlProperty Property,
                [Out] out int pMin,
                [Out] out int pMax,
                [Out] out int pSteppingDelta,
                [Out] out int pDefault,
                [Out] out CameraControlFlags pCapsFlags
                );

            [PreserveSig]
            int Set(
                [In] CameraControlProperty Property,
                [In] int lValue,
                [In] CameraControlFlags Flags
                );

            [PreserveSig]
            int Get(
                [In] CameraControlProperty Property,
                [Out] out int lValue,
                [Out] out CameraControlFlags Flags
                );
        }

        #endregion

        private readonly string videoSource;
        private SettingsHandler settingsHandler;
        private VideoRecorderServiceSettings settings
        {
            get { return (VideoRecorderServiceSettings)this.settingsHandler.SettingsObject; }
        }

        public CameraSettings(string videoSource, SettingsHandler settingsHandler)
        {
            this.videoSource = videoSource;
            this.settingsHandler = settingsHandler;

            InitializeComponent();
            lock (this)
            {
                object tempSourceObject = null;

                // create source device's object
                try
                {
                    tempSourceObject = FilterInfo.CreateFilter(this.videoSource);
                }
                catch
                {
                    throw new ApplicationException("Failed creating device object for moniker.");
                }
                if (tempSourceObject != null)
                {
                    IAMCameraControl cControl = tempSourceObject as IAMCameraControl;
                    if (cControl != null)
                    {
                        int valMin = 0;
                        int valMax = 0;
                        int steppingDelta = 0;
                        int defaultVal = 0;
                        int currVal = 0;
                        CameraControlFlags flags;

                        cControl.GetRange(CameraControlProperty.Exposure, out valMin, out valMax, out steppingDelta,
                                          out defaultVal, out flags);
                        if (this.settings.CameraSpecific.CameraName == "Logitech Webcam Pro 9000")
                            valMax -= 2;
                        cControl.Get(CameraControlProperty.Exposure, out currVal, out flags);

                        this.ExposureScrollBar.Maximum = valMax;
                        this.ExposureScrollBar.Minimum = valMin;
                        this.ExposureScrollBar.LargeChange = steppingDelta;
                        this.ExposureScrollBar.SmallChange = steppingDelta;
                        this.ExposureScrollBar.Value = currVal;

                        cControl.GetRange(CameraControlProperty.Focus, out valMin, out valMax,
                                          out steppingDelta, out defaultVal, out flags);

                        cControl.Get(CameraControlProperty.Focus, out currVal, out flags);

                        this.FocusScrollBar.Maximum = valMax;
                        this.FocusScrollBar.Minimum = valMin;
                        this.FocusScrollBar.LargeChange = steppingDelta;
                        this.FocusScrollBar.SmallChange = steppingDelta;
                        this.FocusScrollBar.Value = currVal;
                    }

                    IAMVideoProcAmp vProc = tempSourceObject as IAMVideoProcAmp;
                    if (vProc != null)
                    {
                        // Disable automatic light control
                        vProc.Set(CameraSettings.VideoProcAmpProperty.BacklightCompensation, 0,
                                  CameraSettings.VideoProcAmpFlags.Manual);

                        int valMin = 0;
                        int valMax = 0;
                        int steppingDelta = 0;
                        int defaultVal = 0;
                        int currVal = 0;
                        VideoProcAmpFlags flags;

                        vProc.GetRange(VideoProcAmpProperty.Gain, out valMin, out valMax,
                                       out steppingDelta, out defaultVal, out flags);

                        vProc.Get(VideoProcAmpProperty.Gain, out currVal, out flags);

                        this.GainScrollBar.Maximum = valMax;
                        this.GainScrollBar.Minimum = valMin;
                        this.GainScrollBar.LargeChange = steppingDelta;
                        this.GainScrollBar.SmallChange = steppingDelta;
                        this.GainScrollBar.Value = currVal;

                        // This disables the automatic gain control
                        vProc.Set(VideoProcAmpProperty.Gain, 0, CameraSettings.VideoProcAmpFlags.Manual);
                        vProc.Set(VideoProcAmpProperty.Gain, this.GainScrollBar.Value, CameraSettings.VideoProcAmpFlags.Manual);

                        vProc.GetRange(VideoProcAmpProperty.Brightness, out valMin, out valMax,
                                       out steppingDelta, out defaultVal, out flags);

                        vProc.Get(VideoProcAmpProperty.Brightness, out currVal, out flags);

                        this.BrightnessScrollBar.Maximum = valMax;
                        this.BrightnessScrollBar.Minimum = valMin;
                        this.BrightnessScrollBar.LargeChange = steppingDelta;
                        this.BrightnessScrollBar.SmallChange = steppingDelta;
                        this.BrightnessScrollBar.Value = currVal;

                        vProc.GetRange(VideoProcAmpProperty.Contrast, out valMin, out valMax,
                                       out steppingDelta, out defaultVal, out flags);

                        vProc.Get(VideoProcAmpProperty.Contrast, out currVal, out flags);

                        this.ContrastScrollBar.Maximum = valMax;
                        this.ContrastScrollBar.Minimum = valMin;
                        this.ContrastScrollBar.LargeChange = steppingDelta;
                        this.ContrastScrollBar.SmallChange = steppingDelta;
                        this.ContrastScrollBar.Value = currVal;

                        vProc.GetRange(VideoProcAmpProperty.WhiteBalance, out valMin, out valMax,
                                       out steppingDelta, out defaultVal, out flags);

                        vProc.Get(VideoProcAmpProperty.WhiteBalance, out currVal, out flags);
                        
                        this.WhiteBalanceScrollBar.Maximum = valMax;
                        this.WhiteBalanceScrollBar.Minimum = valMin;
                        this.WhiteBalanceScrollBar.LargeChange = steppingDelta;
                        this.WhiteBalanceScrollBar.SmallChange = steppingDelta;
                        this.WhiteBalanceScrollBar.Value = currVal;
                    }

                    Marshal.ReleaseComObject(tempSourceObject);
                }
            }

            this.ExposureScrollBar.ValueChanged += new System.EventHandler(this.ExposureScrollBar_ValueChanged);
            this.GainScrollBar.ValueChanged += new System.EventHandler(this.GainScrollBar_ValueChanged);
            this.BrightnessScrollBar.ValueChanged += new System.EventHandler(this.BrightnessScrollBar_ValueChanged);
            this.ContrastScrollBar.ValueChanged += new System.EventHandler(this.ContrastScrollBar_ValueChanged);
            this.WhiteBalanceScrollBar.ValueChanged += new System.EventHandler(this.WhiteBalanceScrollBar_ValueChanged);
            this.FocusScrollBar.ValueChanged += new System.EventHandler(this.FocusScrollBar_ValueChanged);
        }

        private void ExposureScrollBar_ValueChanged(object sender, EventArgs e)
        {
            lock (this)
            {
                object tempSourceObject = null;

                // create source device's object
                try
                {
                    tempSourceObject = FilterInfo.CreateFilter(this.videoSource);
                }
                catch
                {
                    throw new ApplicationException("Failed creating device object for moniker.");
                }
                if (tempSourceObject != null)
                {
                    IAMCameraControl cControl = tempSourceObject as IAMCameraControl;
                    if (cControl != null)
                    {
                        cControl.Set(CameraControlProperty.Exposure, this.ExposureScrollBar.Value,
                                     CameraControlFlags.Manual);
                    }

                    Marshal.ReleaseComObject(tempSourceObject);
                }
            }
        }

        private void GainScrollBar_ValueChanged(object sender, EventArgs e)
        {
            lock (this)
            {
                object tempSourceObject = null;

                // create source device's object
                try
                {
                    tempSourceObject = FilterInfo.CreateFilter(this.videoSource);
                }
                catch
                {
                    throw new ApplicationException("Failed creating device object for moniker.");
                }
                if (tempSourceObject != null)
                {
                    IAMVideoProcAmp vProc = tempSourceObject as IAMVideoProcAmp;
                    if (vProc != null)
                    {
                        vProc.Set(VideoProcAmpProperty.Gain, this.GainScrollBar.Value,
                                  VideoProcAmpFlags.Manual);
                    }

                    Marshal.ReleaseComObject(tempSourceObject);
                }
            }
        }

        private void BrightnessScrollBar_ValueChanged(object sender, EventArgs e)
        {
            lock (this)
            {
                object tempSourceObject = null;

                // create source device's object
                try
                {
                    tempSourceObject = FilterInfo.CreateFilter(this.videoSource);
                }
                catch
                {
                    throw new ApplicationException("Failed creating device object for moniker.");
                }
                if (tempSourceObject != null)
                {
                    IAMVideoProcAmp vProc = tempSourceObject as IAMVideoProcAmp;
                    if (vProc != null)
                    {
                        vProc.Set(VideoProcAmpProperty.Brightness, this.BrightnessScrollBar.Value,
                                  VideoProcAmpFlags.Manual);
                    }

                    Marshal.ReleaseComObject(tempSourceObject);
                }
            }
        }

        private void ContrastScrollBar_ValueChanged(object sender, EventArgs e)
        {
            lock (this)
            {
                object tempSourceObject = null;

                // create source device's object
                try
                {
                    tempSourceObject = FilterInfo.CreateFilter(this.videoSource);
                }
                catch
                {
                    throw new ApplicationException("Failed creating device object for moniker.");
                }
                if (tempSourceObject != null)
                {
                    IAMVideoProcAmp vProc = tempSourceObject as IAMVideoProcAmp;
                    if (vProc != null)
                    {
                        vProc.Set(VideoProcAmpProperty.Contrast, this.ContrastScrollBar.Value,
                                  VideoProcAmpFlags.Manual);
                    }

                    Marshal.ReleaseComObject(tempSourceObject);
                }
            }
        }


        private void WhiteBalanceScrollBar_ValueChanged(object sender, EventArgs e)
        {
            lock (this)
            {
                object tempSourceObject = null;

                // create source device's object
                try
                {
                    tempSourceObject = FilterInfo.CreateFilter(this.videoSource);
                }
                catch
                {
                    throw new ApplicationException("Failed creating device object for moniker.");
                }
                if (tempSourceObject != null)
                {
                    IAMVideoProcAmp vProc = tempSourceObject as IAMVideoProcAmp;
                    if (vProc != null)
                    {
                        vProc.Set(VideoProcAmpProperty.WhiteBalance, this.WhiteBalanceScrollBar.Value,
                                  VideoProcAmpFlags.Manual);
                    }

                    Marshal.ReleaseComObject(tempSourceObject);
                }
            }
        }

        private void FocusScrollBar_ValueChanged(object sender, EventArgs e)
        {
            lock (this)
            {
                object tempSourceObject = null;

                // create source device's object
                try
                {
                    tempSourceObject = FilterInfo.CreateFilter(this.videoSource);
                }
                catch
                {
                    throw new ApplicationException("Failed creating device object for moniker.");
                }
                if (tempSourceObject != null)
                {
                    IAMCameraControl cControl = tempSourceObject as IAMCameraControl;
                    if (cControl != null)
                    {
                        cControl.Set(CameraControlProperty.Focus, this.FocusScrollBar.Value,
                                     CameraControlFlags.Manual);
                    }

                    Marshal.ReleaseComObject(tempSourceObject);
                }
            }
        }

        private void CameraSettings_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Save currently selected device to settings.
            this.settings.ImageSettings.Brightness = this.BrightnessScrollBar.Value;
            this.settings.ImageSettings.Contrast = this.ContrastScrollBar.Value;
            this.settings.ImageSettings.Exposure = this.ExposureScrollBar.Value;
            this.settings.ImageSettings.Focus = this.FocusScrollBar.Value;
            this.settings.ImageSettings.Gain = this.GainScrollBar.Value;
            this.settings.ImageSettings.WhiteBalance = this.WhiteBalanceScrollBar.Value;
            this.settingsHandler.SaveSettings();
        }
    }
}
