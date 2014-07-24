using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Reflection;
using GraniteLibrary.Utilities;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GraniteLibrary.UnitTest.Utilities
{
    /// <summary>
    ///This is a test class for ImageComparerTest and is intended
    ///to contain all ImageComparerTest Unit Tests
    ///</summary>
    [TestClass()]
    public class ImageComparerTest
    {
        private TestContext testContextInstance;

        /// <summary>
        ///Gets or sets the test context which provides
        ///information about and functionality for the current test run.
        ///</summary>
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                testContextInstance = value;
            }
        }

        #region Additional test attributes
        // 
        //You can use the following additional attributes as you write your tests:
        //
        //Use ClassInitialize to run code before running the first test in the class
        //[ClassInitialize()]
        //public static void MyClassInitialize(TestContext testContext)
        //{
        //}
        //
        //Use ClassCleanup to run code after all tests in a class have run
        //[ClassCleanup()]
        //public static void MyClassCleanup()
        //{
        //}
        //
        //Use TestInitialize to run code before running each test
        //[TestInitialize()]
        //public void MyTestInitialize()
        //{
        //}
        //
        //Use TestCleanup to run code after each test has run
        //[TestCleanup()]
        //public void MyTestCleanup()
        //{
        //}
        //
        #endregion

        /// <summary>
        //A test for Compare with null arguments.
        ///</summary>
        [TestMethod()]
        [ExpectedException(typeof(ArgumentNullException))]
        public void CompareTestWithNullArguments()
        {
            Bitmap actualImage = null;
            Bitmap expectedImage = null;
            Bitmap differenceImage;
            double difference = 0.0;
            ImageComparer.Compare(actualImage, expectedImage, out differenceImage, out difference);
        }

        /// <summary>
        ///A test for Compare with matching images.
        ///</summary>
        [TestMethod()]
        public void CompareTestWithMatchingImages()
        {
            Bitmap actualImage = LoadBitmap("Image001Idle.png");
            Bitmap expectedImage = LoadBitmap("Image001Idle.png");
            Bitmap differenceImage;
            double difference = 1.0;

            bool expected = true;
            bool actual = ImageComparer.Compare(actualImage, expectedImage, out differenceImage, out difference);
            Assert.AreEqual(expected, actual, "The images should be equal.");
            Assert.AreEqual(0.0, difference, 0.001, "The difference should be 0%.");
            Assert.IsNotNull(differenceImage, "Expected a difference image to always be produced.");
        }

        /// <summary>
        ///A test for Compare with matching mask images.
        ///</summary>
        [TestMethod()]
        public void CompareTestWithMatchingMaskImage()
        {
            Bitmap actualImage = LoadBitmap("Image001Idle.png");
            Bitmap expectedImage = LoadBitmap("Image002IdleWithMask.png");
            Bitmap differenceImage;
            double difference = 1.0;

            bool expected = true;
            bool actual = ImageComparer.Compare(actualImage, expectedImage, out differenceImage, out difference);
            Assert.AreEqual(expected, actual, "The images should be equal since there is a mask over the area with the differences.");
            Assert.AreEqual(0.0, difference, 0.001, "The difference should be 0%.");
            Assert.IsNotNull(differenceImage, "Expected a difference image to always be produced.");
        }

        /// <summary>
        ///A test for Compare with matching mask images.
        ///</summary>
        [TestMethod()]
        public void CompareTestWithDifferentImages()
        {
            Bitmap actualImage = LoadBitmap("Image001Idle.png");
            Bitmap expectedImage = LoadBitmap("Image003Idle.png");
            Bitmap differenceImage;
            double difference = 0.0;

            bool expected = false;
            bool actual = ImageComparer.Compare(actualImage, expectedImage, out differenceImage, out difference);
            Assert.AreEqual(expected, actual, "The images should not be equal since there are areas where they are different.");
            Assert.IsTrue(difference > 0.0, "The difference should not be 0% since there are areas where they are different.");
            Assert.IsNotNull(differenceImage, "Expected a difference image to always be produced.");
        }

        /// <summary>
        ///A test for GetMaskXmlFromImage
        ///</summary>
        [TestMethod()]
        [DeploymentItem("GraniteLibrary.dll")]
        public void GetMaskXmlFromImageTest()
        {
            Bitmap expectedImage = LoadBitmap("Image002IdleWithMask.png");
            string actual = ImageComparer_Accessor.GetMaskXmlFromImage(expectedImage);
            Assert.IsFalse(string.IsNullOrEmpty(actual), "Mask XML information should have been retrieved from the masked image.");
        }

        /// <summary>
        ///A test for LoadMaskFromImage
        ///</summary>
        [TestMethod()]
        [DeploymentItem("GraniteLibrary.dll")]
        public void LoadMaskFromImageTest()
        {
            Bitmap image = LoadBitmap("Image002IdleWithMask.png");
            List<ImageComparer.MaskMeta> actual = ImageComparer_Accessor.LoadMaskFromImage(image);
            Assert.IsNotNull(actual, "There should be mask information stored in the masked image therefore it should not be null.");
            Assert.IsTrue(actual.Count > 0, "There should be mask information stored in the masked image therefore the list should be empty.");
        }

        /// <summary>
        /// Loads a bitmap image that is stored as an embedded resource.
        /// </summary>
        /// <param name="imageFileName">Name of the image file.</param>
        /// <returns>Bitmap image that has been loaded.</returns>
        private static Bitmap LoadBitmap(string imageFileName)
        {
            Bitmap bitmap = null;

            string name = "GraniteLibrary.UnitTest.Data." + imageFileName;

            // Get the stream for the embedded resource
            using (Stream resourceStream = Assembly.GetExecutingAssembly().GetManifestResourceStream(name))
            {
                bitmap = Bitmap.FromStream(resourceStream) as Bitmap;
            }

            return bitmap;
        }
    }
}
