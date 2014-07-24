using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using Managed.Adb.Conversion;
using System.Reflection;

namespace Managed.Adb
{
    /// <summary>
    /// Data representing an image taken from a device frame buffer.
    /// </summary>
    public class RawImage
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="RawImage"/> class.
        /// </summary>
        public RawImage()
        {
            Red = new ColorData();
            Blue = new ColorData();
            Green = new ColorData();
            Alpha = new ColorData();
        }

        /// <summary>
        /// Gets or sets the version.
        /// </summary>
        /// <value>
        /// The version.
        /// </value>
        public int Version { get; private set; }
        
        /// <summary>
        /// Gets or sets the BPP.
        /// </summary>
        /// <value>
        /// The BPP.
        /// </value>
        public int Bpp { get; private set; }
        
        /// <summary>
        /// Gets or sets the size.
        /// </summary>
        /// <value>
        /// The size.
        /// </value>
        public int Size { get; private set; }
        
        /// <summary>
        /// Gets or sets the width.
        /// </summary>
        /// <value>
        /// The width.
        /// </value>
        public int Width { get; private set; }
        
        /// <summary>
        /// Gets or sets the height.
        /// </summary>
        /// <value>
        /// The height.
        /// </value>
        public int Height { get; private set; }
        
        /// <summary>
        /// Gets or sets the red.
        /// </summary>
        /// <value>
        /// The red.
        /// </value>
        public ColorData Red { get; private set; }
        
        /// <summary>
        /// Gets or sets the blue.
        /// </summary>
        /// <value>
        /// The blue.
        /// </value>
        public ColorData Blue { get; private set; }
        
        /// <summary>
        /// Gets or sets the green.
        /// </summary>
        /// <value>
        /// The green.
        /// </value>
        public ColorData Green { get; private set; }
        
        /// <summary>
        /// Gets or sets the alpha.
        /// </summary>
        /// <value>
        /// The alpha.
        /// </value>
        public ColorData Alpha { get; private set; }

        /// <summary>
        /// Gets or sets the data.
        /// </summary>
        /// <value>
        /// The data.
        /// </value>
        public byte[] Data { get; set; }

        /// <summary>
        /// Reads the header of a RawImage from a {@link ByteBuffer}.
        /// <p/>The way the data is sent over adb is defined in system/core/adb/framebuffer_service.c
        /// </summary>
        /// <param name="version">The version of the protocol.</param>
        /// <param name="data">The data to read from</param>
        /// <returns>True if success</returns>
        public bool ReadHeader(int version, byte[] data)
        {
            Version = version;

            int index = 0;
            int step = sizeof(Int32);

            if (version == 16)
            {
                // compatibility mode with original protocol
                Bpp = 16;
                // read actual values.
                Size = data.ReadInt32(index);
                index += step;
                Width = data.ReadInt32(index);
                index += step;
                Height = data.ReadInt32(index);
                index += step;
                // create default values for the rest. Format is 565
                Red.Offset = 11;
                Red.Length = 5;
                Green.Offset = 5;
                Green.Length = 6;
                Blue.Offset = 0;
                Blue.Length = 5;
                Alpha.Offset = 0;
                Alpha.Length = 0;
            }
            else if (version == 1)
            {
                // https://github.com/android/platform_system_core/blob/master/adb/framebuffer_service.c
                // this should be changed to support the other versions.
                Bpp = data.ReadInt32(index);
                index += step;
                Size = data.ReadInt32(index);
                index += step;
                Width = data.ReadInt32(index);
                index += step;
                Height = data.ReadInt32(index);
                index += step;
                Red.Offset = data.ReadInt32(index);
                index += step;
                Red.Length = data.ReadInt32(index);
                index += step;
                Blue.Offset = data.ReadInt32(index);
                index += step;
                Blue.Length = data.ReadInt32(index);
                index += step;
                Green.Offset = data.ReadInt32(index);
                index += step;
                Green.Length = data.ReadInt32(index);
                index += step;
                Alpha.Offset = data.ReadInt32(index);
                index += step;
                Alpha.Length = data.ReadInt32(index);
                index += step;
            }
            else
            {
                // unsupported protocol!
                return false;
            }

            return true;
        }

        /// <summary>
        /// Returns the size of the header for a specific version of the framebuffer adb protocol.
        /// </summary>
        /// <param name="version">The version of the protocol</param>
        /// <returns>The number of int that makes up the header</returns>
        public static int GetHeaderSize(int version)
        {
            if (version == 1)
                return 12;
            else if (version == 16)
                return 3;
            return 0;
        }

        /// <summary>
        /// Returns a rotated version of the image.
        /// The image is rotated counter-clockwise.
        /// </summary>
        /// <returns>A rotated version of the image</returns>
        public RawImage GetRotated()
        {
            RawImage rotated = new RawImage();
            rotated.Version = Version;
            rotated.Bpp = Bpp;
            rotated.Size = Size;
            rotated.Red.Offset = Red.Offset;
            rotated.Red.Length = Red.Length;
            rotated.Green.Offset = Green.Offset;
            rotated.Green.Length = Green.Length;
            rotated.Blue.Offset = Blue.Offset;
            rotated.Blue.Length = Blue.Length;
            rotated.Alpha.Offset = Alpha.Offset;
            rotated.Alpha.Length = Alpha.Length;

            rotated.Width = Height;
            rotated.Height = Width;

            int count = Data.Length;
            rotated.Data = new byte[count];

            int byteCount = Bpp >> 3; // bpp is in bits, we want bytes to match our array
            int w = Width;
            int h = Height;
            for (int y = 0; y < h; y++)
            {
                for (int x = 0; x < w; x++)
                {
                    Array.Copy(Data, (y * w + x) * byteCount,
                        rotated.Data, ((w - x - 1) * h + y) * byteCount,
                        byteCount);
                }
            }

            return rotated;
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public override string ToString()
        {
            return string.Format("height: {0}\nwidth: {1}\nbpp: {2}\nro: {3}\nrl: {4}\ngo: {5}\ngl: {6}\nbo: {7}\nbl: {8}\nao: {9}\nal: {10}\ns: {11}",
                Height, Width, Bpp, Red.Offset, Red.Length, Green.Offset, Green.Length, Blue.Offset, Blue.Length,
                Alpha.Offset, Alpha.Length, Size);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="filename"></param>
        public void Save(string filename)
        {
            Save(filename, ImageFormat.Png);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="filename"></param>
        /// <param name="imageFormat"></param>
        public void Save(string filename, string imageFormat)
        {
            Save(filename, ImageFormatFromString(imageFormat));
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="filename"></param>
        /// <param name="imageFormat"></param>
        public void Save(string filename, ImageFormat imageFormat)
        {
            using (Bitmap image = ToImage())
            {
                image.Save(filename, imageFormat);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="imageFormat"></param>
        /// <returns></returns>
        private ImageFormat ImageFormatFromString(string imageFormat)
        {
            return (ImageFormat)typeof(ImageFormat).GetProperty(imageFormat, BindingFlags.Public | BindingFlags.Static | BindingFlags.Instance | BindingFlags.IgnoreCase).GetValue(null, null);
        }

        /// <summary>
        /// Converts this raw image to an Image
        /// </summary>
        /// <param name="format">The format.</param>
        /// <returns></returns>
        public Bitmap ToImage(PixelFormat format)
        {
            Bitmap bitmap = null;
            BitmapData bitmapdata = null;

            try
            {
                bitmap = new Bitmap(Width, Height, format);
                bitmapdata = bitmap.LockBits(new Rectangle(0, 0, Width, Height), ImageLockMode.WriteOnly, format);
                var tdata = Data;
                if (Bpp == 32)
                {
                    tdata = Swap(tdata);
                }

                Marshal.Copy(tdata, 0, bitmapdata.Scan0, Size);
                bitmap.UnlockBits(bitmapdata);
                return bitmap;
            }
            catch (Exception)
            {
                throw;
            }
        }

        /// <summary>
        /// Converts this raw image to an Image
        /// </summary>
        /// <returns></returns>
        public Bitmap ToImage()
        {
            return ToImage(Bpp == 32 ? PixelFormat.Format32bppArgb : PixelFormat.Format16bppRgb565);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="b"></param>
        /// <returns></returns>
        private byte[] Swap(byte[] b)
        {
            var clone = new List<byte>();
            b.IntReverseForRawImage(bitem =>
            {
                clone.AddRange(bitem);
            });
            return clone.ToArray();
        }
    }
}
