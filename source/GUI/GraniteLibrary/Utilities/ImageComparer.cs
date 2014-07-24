using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;
using System.Text;
using System.Windows;
using System.Xml.Serialization;

namespace MarbleLibrary.Utilities
{
    /// <summary>
    /// Class used for image comparison.
    /// </summary>
    public class ImageComparer
    {
        /// <summary>
        /// Class encapsulating the masking shape meta information that is used for serializing
        /// and deserializing masks.
        /// </summary>
        public class MaskMeta
        {
            public MaskMeta() { }
            public MaskMeta(MaskShape maskType, Rect rectangle)
            {
                this.MaskType = maskType;
                this.X = rectangle.X;
                this.Y = rectangle.Y;
                this.Height = rectangle.Height;
                this.Width = rectangle.Width;
            }

            /// <summary>
            /// Determines if a point inside the mask area.
            /// </summary>
            /// <param name="point">The point.</param>
            /// <returns>Returns true if the point inside the mask area, otherwise returns false. </returns>
            public bool IsMaskArea(System.Windows.Point point)
            {
                if (MaskType == MaskShape.Ellipse)
                {
                    /* This is a more general form of the circle equation
                     *
                     * X^2/a^2 + Y^2/b^2 <= 1
                     */

                    System.Windows.Point center = new System.Windows.Point((double)(X + Width / 2), (double)(Y + Height / 2));
                    System.Windows.Point normalized = new System.Windows.Point(point.X - center.X, point.Y - center.Y);
                    return ((double)(normalized.X * normalized.X) / (Width/2 * Width/2)) + ((double)(normalized.Y * normalized.Y) / (Height/2 * Height/2)) <= 1.0;
                }
                else if (MaskType == MaskShape.Rectangle)
                {
                    Rect rect = new Rect(X, Y, Width, Height);
                    return rect.Contains(point);
                }

                return false;
            }

            public MaskShape MaskType { get; set; }
            public double X { get; set; }
            public double Y { get; set; }
            public double Height { get; set; }
            public double Width { get; set; }
        }

        /// <summary>
        /// Types of mask shapes supported
        /// </summary>
        public enum MaskShape
        {
            Rectangle,
            Ellipse
        }

        /// <summary>
        /// Prevent an instance of this class from being created.
        /// </summary>
        private ImageComparer()
        {
        }

        /// <summary>
        /// Compares two bitmaps.
        /// </summary>
        /// <param name="actualImage">Actual display image bitmap from the phone.</param>
        /// <param name="expectedImage">Expected display image bitmap which contains mask data.</param>
        /// <param name="differenceImage">Image bitmap which shows the differences between the actual image and the expected image.
        /// <value>If there are no differences, then this bitmap will be set to <c>null</c>.</value></param>
        /// <param name="difference">The percentage difference.</param>
        /// <returns>Returns true if the actual image is same with the expected image in unmasked area.</returns>
        public static bool Compare(Bitmap actualImage, Bitmap expectedImage, out Bitmap differenceImage, out double difference)
        {
            bool equal = true;

            #region Check the supplied arguments

            if (actualImage == null)
            {
                throw new ArgumentNullException("Failed to compare images since there is no actual image.", "actualImage");
            }

            if (expectedImage == null)
            {
                throw new ArgumentNullException("Failed to compare images since there is no expected image to compare with.", "expectedImage");
            }

            #endregion

            int differentPoints = 0;
            int maskPoints = 0;

            // Create the difference image.
            differenceImage = new Bitmap(Math.Max(actualImage.Width, expectedImage.Width),
                Math.Max(actualImage.Height, expectedImage.Height));

            // Load mask data from the expected image.
            List<MaskMeta> maskMetaList = LoadMaskFromImage(expectedImage);

            // Draw mask areas in the difference image
            System.Drawing.Color differenceColor = System.Drawing.Color.Red;
            Graphics g = Graphics.FromImage(differenceImage);
            g.SmoothingMode = SmoothingMode.AntiAlias;

            SolidBrush redBrush = new SolidBrush(differenceColor);
            HatchBrush hatchBrush = new HatchBrush(HatchStyle.DarkUpwardDiagonal, System.Drawing.Color.FromArgb(180, 170, 0, 0), System.Drawing.Color.FromArgb(180, 0, 170, 0)); 
 
            g.FillRectangle(redBrush, 0, 0, differenceImage.Width, differenceImage.Height);
            g.DrawImage(actualImage, 0, 0);
            if (maskMetaList != null)
            {
                foreach (MaskMeta maskMeta in maskMetaList)
                {
                    if (maskMeta.MaskType == MaskShape.Rectangle)
                    {
                        g.FillRectangle(hatchBrush, (int)maskMeta.X, (int)maskMeta.Y, (int)maskMeta.Width, (int)maskMeta.Height);
                    }
                    else if (maskMeta.MaskType == MaskShape.Ellipse)
                    {
                        g.FillEllipse(hatchBrush, (int)maskMeta.X, (int)maskMeta.Y, (int)maskMeta.Width, (int)maskMeta.Height);
                    }
                }
            }

            hatchBrush.Dispose();
            redBrush.Dispose();
            g.Dispose();

            // Compare 2 bitmaps and set the different area with red in the difference image. 
            for (int y = 0; y < differenceImage.Height; ++y)
            {
                for (int x = 0; x < differenceImage.Width; ++x)
                {
                    if (IsMaskArea(maskMetaList, new System.Windows.Point(x, y)))
                    {
                        maskPoints += 1;
                        continue;
                    }

                    if (x >= Math.Min(actualImage.Width, expectedImage.Width) || y >= Math.Min(actualImage.Height, expectedImage.Height))
                    {
                        equal = false;
                        differenceImage.SetPixel(x,y,differenceColor);
                        differentPoints += 1;
                    }
                    else
                    {
                        System.Drawing.Color actualColour = expectedImage.GetPixel(x, y);
                        System.Drawing.Color expectedColour = actualImage.GetPixel(x, y);
                        if (actualColour != expectedColour)
                        {
                            equal = false;
                            differenceImage.SetPixel(x, y, differenceColor);
                            differentPoints += 1;
                        }
                    }
                }
            }

            if (differenceImage.Width * differenceImage.Height == maskPoints)
            {
                difference = 0;
            }
            else
            {
                difference = (double)differentPoints / (differenceImage.Width * differenceImage.Height - maskPoints);
            }

            return equal;
        }

        /// <summary>
        /// Draws the masks on the image.
        /// </summary>
        /// <param name="image">Image that may have mask meta-data.</param>
        public static void DrawMasks(Bitmap image)
        {
            #region Check the supplied arguments

            if (image == null)
            {
                throw new ArgumentNullException("Failed to draw the masks since there is no image.", "image");
            }

            #endregion

            // Load mask data from the expected image.
            List<MaskMeta> maskMetaList = LoadMaskFromImage(image);

            if (maskMetaList != null)
            {
                using (Graphics g = Graphics.FromImage(image))
                {
                    // Set the smoothing mode
                    g.SmoothingMode = SmoothingMode.AntiAlias;

                    using (HatchBrush hatchBrush = new HatchBrush(HatchStyle.DarkUpwardDiagonal, System.Drawing.Color.FromArgb(180, 170, 0, 0), System.Drawing.Color.FromArgb(180, 0, 170, 0)))
                    {
                        foreach (MaskMeta maskMeta in maskMetaList)
                        {
                            if (maskMeta.MaskType == MaskShape.Rectangle)
                            {
                                // Draw the rectangular mask
                                g.FillRectangle(hatchBrush, (int)maskMeta.X, (int)maskMeta.Y, (int)maskMeta.Width, (int)maskMeta.Height);
                            }
                            else if (maskMeta.MaskType == MaskShape.Ellipse)
                            {
                                // Draw the ellipse mask
                                g.FillEllipse(hatchBrush, (int)maskMeta.X, (int)maskMeta.Y, (int)maskMeta.Width, (int)maskMeta.Height);
                            }
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Gets mask xml data from an image's property items.
        /// </summary>
        /// <param name="image">The image which contains mask xml data.</param>
        /// <returns>The mask xml data.</returns>
        private static string GetMaskXmlFromImage(Image image)
        {
            if (image != null)
            {
                // Read mask from image's meta data
                foreach (PropertyItem item in image.PropertyItems)
                {
                    if (item.Id == 0x010E /*Image Description*/)
                    {
                        return Encoding.UTF8.GetString(item.Value, 0, item.Len - 1);
                    }
                }
            }

            return null;
        }

        /// <summary>
        /// Gets all mask data from an image.
        /// </summary>
        /// <param name="image">The image which contains mask data.</param>
        /// <returns>A list of all mask data.</returns>
        private static List<MaskMeta> LoadMaskFromImage(Image image)
        {
            List<MaskMeta> maskMetaList = null;

            if (image != null)
            {
                string xml = GetMaskXmlFromImage(image);
                if (!string.IsNullOrEmpty(xml))
                {
                    XmlSerializer xmlserializer = new XmlSerializer(typeof(List<MaskMeta>));

                    StringReader sr = new StringReader(xml);

                    try
                    {
                        maskMetaList = (List<MaskMeta>)xmlserializer.Deserialize(sr);
                    }
                    catch (System.Exception ex)
                    {
                        Debug.WriteLine("Failed to deserialize the string: \"" + xml + "\". The error message: " + ex.Message);
                    }
                }
            }

            return maskMetaList;
        }

        /// <summary>
        /// Determine if a point inside any mask area.
        /// </summary>
        /// <param name="maskMetaList">All mask area.</param>
        /// <param name="point">The point.</param>
        /// <returns>Returns true if the point is inside any mask area, otherwise returns false.</returns>
        private static bool IsMaskArea(List<MaskMeta> maskMetaList, System.Windows.Point point)
        {
            if (maskMetaList == null)
            {
                return false;
            }

            foreach (MaskMeta maskMeta in maskMetaList)
            {
                if (maskMeta.IsMaskArea(point))
                {
                    return true;
                }
            }

            return false;
        }
    }
}
