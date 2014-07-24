// -----------------------------------------------------------------------
// <copyright file="ImageUtilities.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace MarbleLibrary.Utilities
{
    using System;
    using System.Collections.Generic;
    using System.Drawing;
    using System.IO;
    using System.Linq;
    using System.Text;
    using System.Windows.Media.Imaging;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public static class ImageUtilities
    {
        public static Size GetMinDimensionsOfImages(List<string> imageFilePaths)
        {
            int minWidth = 0;
            int minHeight = 0;

            foreach (string imageFilePath in imageFilePaths)
            {
                if (!System.IO.File.Exists(imageFilePath)) continue;

                System.Drawing.Image img = System.Drawing.Image.FromFile(imageFilePath);

                if (img.Width < minWidth && minWidth > 0 && img.Width > 0)
                    minWidth = img.Width;
                if (img.Height < minHeight && minHeight > 0 && img.Height > 0)
                    minHeight = img.Height;
            }

            return new Size(minWidth, minHeight);
        }

        public static Size GetMaxDimensionsOfImages(List<string> imageFilePaths)
        {
            int maxWidth = 0;
            int maxHeight = 0;

            foreach (string imageFilePath in imageFilePaths)
            {
                if (!System.IO.File.Exists(imageFilePath)) continue;

                System.Drawing.Image img = System.Drawing.Image.FromFile(imageFilePath);

                if (img.Width > maxWidth)
                    maxWidth = img.Width;
                if (img.Height > maxHeight)
                    maxHeight = img.Height;
            }

            return new Size(maxWidth, maxHeight);
        }

        public static byte[] BufferFromJpgImage(BitmapImage img)
        {
            byte[] result;

            if (img == null) return null;

            using (MemoryStream memStream = new MemoryStream())
            {
                JpegBitmapEncoder encoder = new JpegBitmapEncoder();
                encoder.Frames.Add(BitmapFrame.Create(img));
                encoder.Save(memStream);

                result = memStream.ToArray();
            }

            return result;
        }

        public static BitmapImage LoadImage(byte[] imageData)
        {
            if (imageData == null || imageData.Length == 0) return null;

            BitmapImage image = new BitmapImage();

            using (MemoryStream memoryStream = new MemoryStream(imageData))
            {
                memoryStream.Position = 0;
                image.BeginInit();
                image.CreateOptions = BitmapCreateOptions.PreservePixelFormat;
                image.CacheOption = BitmapCacheOption.OnLoad;
                image.UriSource = null;
                image.StreamSource = memoryStream;
                image.EndInit();
            }

            image.Freeze();

            return image;
        }

        public static Icon IconFromFilePath(string filePath)
        {
            Icon fileIcon = null;

            try
            {
                fileIcon = Icon.ExtractAssociatedIcon(filePath);
            }
            catch (Exception) { }

            return fileIcon;
        }

        public static System.Windows.Controls.Image ImageFromIconFromFilePath(string filePath)
        {
            var iconAsImage = new System.Windows.Controls.Image();

            System.Windows.Media.ImageSource icon = null;

            if (System.IO.File.Exists(filePath))
            {
                using (System.Drawing.Icon sysicon = System.Drawing.Icon.ExtractAssociatedIcon(filePath))
                {
                    icon = System.Windows.Interop.Imaging.CreateBitmapSourceFromHIcon(
                      sysicon.Handle,
                      System.Windows.Int32Rect.Empty,
                      System.Windows.Media.Imaging.BitmapSizeOptions.FromEmptyOptions());
                }
            }

            iconAsImage.Source = icon;

            return iconAsImage;
        }
    }
}
