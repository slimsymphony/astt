// -----------------------------------------------------------------------
// <copyright file="PdfUtilities.cs" company="NOKIA">
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
    using System.Windows;
    using System.Windows.Media.Imaging;

    using org.pdfclown.documents;
    using org.pdfclown.documents.contents.composition;
    using org.pdfclown.files;

    using File = org.pdfclown.files.File;
    using Image = org.pdfclown.documents.contents.entities.Image;
    using Size = System.Drawing.Size;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class PdfUtilities
    {
        /// <summary>
        /// The create PDF document from images.
        /// </summary>
        /// <param name="filePath">The file path.</param>
        /// <param name="imageFilePaths">The image file paths.</param>
        public static void CreatePdfFromImages(string filePath, List<string> imageFilePaths)
        {
            if (string.IsNullOrEmpty(filePath)) return;

            Thickness margin = new Thickness(10, 50, 10, 50);

            File file = new File();
            Document document = file.Document;

            Size maxDimensions = ImageUtilities.GetMaxDimensionsOfImages(imageFilePaths);

            foreach (string imageFilePath in imageFilePaths)
            {
                if (!System.IO.File.Exists(imageFilePath)) continue;

                Page page = new Page(document);
                document.Pages.Add(page);
                page.Size = new Size((int)(maxDimensions.Width + margin.Left + margin.Right), (int)(maxDimensions.Height + margin.Top + margin.Bottom));
                PrimitiveComposer composer = new PrimitiveComposer(page);

                ////BitmapImage backgroundBitmap =
                ////    new BitmapImage(
                ////        new Uri(
                ////            "pack://application:,,,/MarbleLibrary;component/Images/marble.dark.background.1x1024.jpg",
                ////            UriKind.RelativeOrAbsolute));

                ////Stream stream = ImageUtilities.BufferFromJpgImage(backgroundBitmap);

                Image image = Image.Get(imageFilePath);
                ////Image backgroundImage = Image.Get(backgroundBitmap.StreamSource);

                float scaleFactorWidth = (page.Size.Width - (float)margin.Left - (float)margin.Right) / maxDimensions.Width;
                float scaleFactorHeight = (page.Size.Height - (float)margin.Top - (float)margin.Bottom) / maxDimensions.Height;
                float scaleFactor = scaleFactorHeight < scaleFactorWidth ? scaleFactorHeight : scaleFactorWidth;
                
                ////composer.ShowXObject(backgroundImage.ToXObject(document), new PointF(0, 0), new SizeF(page.Size.Width, (float)margin.Top));
                composer.ShowXObject(image.ToXObject(document), new PointF((float)margin.Left, (float)margin.Top), new SizeF(0, 0));

                // Close current page.
                composer.Flush();
            }

            try
            {
                file.Save(filePath, SerializationModeEnum.Standard);
            }
            catch (IOException ioe)
            {
                MessageBox.Show(ioe.Message, "Marble - PDF Exporting Failed");
            }
            
        }
    }
}
