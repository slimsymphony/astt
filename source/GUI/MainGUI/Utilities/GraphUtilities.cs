// -----------------------------------------------------------------------
// <copyright file="GraphUtilities.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Utilities
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Text;
    using System.Windows;
    using System.Windows.Media;
    using System.Windows.Media.Imaging;
    using System.Xml.Linq;

    using MarbleLibrary.Utilities;

    using Microsoft.Win32;

    using Visiblox.Charts;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class GraphUtilities
    {
        ////public object ScreenUpdateElementToFpsGraphNode(XElement screenUpdateElement)
        ////{
        ////    ////<screen_update x="168" y="0" width="238" height="18" fps="4" time_stamp="354890" />

        ////    string toolTipText;
        ////}
        
        public static void SaveChartScreenshot(Chart visibloxChart, string saveFilePath)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.FileName = "Exported Chart";
            dlg.Filter = "PNG File|*.png";

            if (dlg.ShowDialog() == true)
            {
                // Save the current layout transform before clearing it
                Transform transform = visibloxChart.LayoutTransform;
                visibloxChart.LayoutTransform = null;

                int width = (int)visibloxChart.ActualWidth;
                int height = (int)visibloxChart.ActualHeight;

                // Note: You only really need to do this bit if the chart isn't part of the UI (ie: a chart you create in memory)
                Size size = new Size(width, height);
                visibloxChart.Measure(size);
                visibloxChart.Arrange(new Rect(size));
                visibloxChart.UpdateLayout();

                // Create a render bitmap and push the surface to it
                RenderTargetBitmap rtb = new RenderTargetBitmap(width, height, 96, 96, PixelFormats.Pbgra32);
                rtb.Render(visibloxChart);

                // Note: Change the encoder and frame for different image types
                PngBitmapEncoder encoder = new PngBitmapEncoder();
                encoder.Frames.Add(BitmapFrame.Create(rtb));

                // Save the image
                Stream stream = dlg.OpenFile();
                encoder.Save(stream);
                stream.Flush();
                stream.Close();

                // Restore previously saved layout transform
                visibloxChart.LayoutTransform = transform;
            }
        }

        public static BitmapImage CreateScreenshotFromChart(Chart visibloxChart)
        {
            // Save the current layout transform before clearing it
            Transform transform = visibloxChart.LayoutTransform;
            visibloxChart.LayoutTransform = null;

            int width = (int)visibloxChart.ActualWidth;
            int height = (int)visibloxChart.ActualHeight;

            // Note: You only really need to do this bit if the chart isn't part of the UI (ie: a chart you create in memory)
            Size size = new Size(width, height);
            visibloxChart.Measure(size);
            visibloxChart.Arrange(new Rect(size));
            visibloxChart.UpdateLayout();

            // Create a render bitmap and push the surface to it
            RenderTargetBitmap rtb = new RenderTargetBitmap(width, height, 96, 96, PixelFormats.Pbgra32);
            rtb.Render(visibloxChart);

            // Note: Change the encoder and frame for different image types
            PngBitmapEncoder encoder = new PngBitmapEncoder();
            encoder.Frames.Add(BitmapFrame.Create(rtb));

            MemoryStream memoryStream = new MemoryStream();
            encoder.Save(memoryStream);
            BitmapImage bitmapImage = ImageUtilities.LoadImage(memoryStream.ToArray());

            //// Save the image
            //Stream stream = dlg.OpenFile();
            //encoder.Save(stream);
            //stream.Flush();
            //stream.Close();

            // Restore previously saved layout transform
            visibloxChart.LayoutTransform = transform;

            return bitmapImage;
        }
    }
}
