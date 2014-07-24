using System.IO;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GraniteLibrary.UnitTest.Utilities
{
    using GraniteLibrary.Utilities;

    /// <summary>
    ///This is a test class for FileUtilitiesTest and is intended
    ///to contain all FileUtilitiesTest Unit Tests
    ///</summary>
    [TestClass()]
    public class FileUtilitiesTest
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
        ///A test for MakeFileWritable
        ///</summary>
        [TestMethod()]
        public void MakeFileWritableTest()
        {
            // Create a temporary file
            string filePath = Path.GetTempFileName();

            // Get the file attributes
            FileAttributes attributes = File.GetAttributes(filePath);

            // Attempt make a file writable that is already writable
            FileUtilities.MakeFileWritable(filePath);

            // Get the file attributes after making it writable
            FileAttributes attributesAfterWritable = File.GetAttributes(filePath);

            Assert.AreEqual(attributes, attributesAfterWritable, "The file attributes should not change if we have a writable file and then attempt to make it writable.");

            // Add the read-only attribute on the file
            FileAttributes readOnlyAttributes = attributes | FileAttributes.ReadOnly;
            File.SetAttributes(filePath, readOnlyAttributes);

            // Attempt to make a file writable that is set to being read-only
            FileUtilities.MakeFileWritable(filePath);

            // Get the file attributes after making it writable
            attributesAfterWritable = File.GetAttributes(filePath);

            Assert.AreEqual(attributes, attributesAfterWritable, "The file attributes should match that of the original attributes if we have made a file read-only and then called the method to make it writable.");

            // Delete the file
            File.Delete(filePath);
        }

        /// <summary>
        ///A test for IsFileReadOnly
        ///</summary>
        [TestMethod()]
        public void IsFileReadOnlyTest()
        {
            // Create a temporary file
            string filePath = Path.GetTempFileName();

            // Check a new file is not read-only
            bool expected = false;
            bool actual = FileUtilities.IsFileReadOnly(filePath);
            Assert.AreEqual(expected, actual, "The temporary file created should not be read-only.");

            // Get the file attributes
            FileAttributes attributes = File.GetAttributes(filePath);

            // Add the read-only attribute on the file
            FileAttributes readOnlyAttributes = attributes | FileAttributes.ReadOnly;
            File.SetAttributes(filePath, readOnlyAttributes);

            // Check a file with the read-only attribute is read-only
            expected = true;
            actual = FileUtilities.IsFileReadOnly(filePath);
            Assert.AreEqual(expected, actual, "The temporary file created had its read-only flag set so it should be read-only.");

            // Set the file attributes back and delete the file
            File.SetAttributes(filePath, attributes);
            File.Delete(filePath);
        }

        /// <summary>
        ///A test for GetRelativePath
        ///</summary>
        [TestMethod()]
        public void GetRelativePathTest()
        {
            string actual = FileUtilities.GetRelativePath(@"C:\Documents and Settings\username\Desktop", @"C:\Documents and Settings\username\Desktop");
            string expected = string.Empty;
            Assert.AreEqual(expected, actual, "The relative path of two paths that are exactly the same should be an empty directory, since no relative directory needs to be specified.");

            actual = FileUtilities.GetRelativePath(@"C:\Documents and Settings\username\Desktop", @"C:\Documents and Settings\username");
            expected = "..\\";
            Assert.AreEqual(expected, actual, "The relative path when going one level up should be '" + expected + "'.");

            actual = FileUtilities.GetRelativePath(@"C:\Documents and Settings\username", @"C:\Documents and Settings\username\Desktop");
            expected = "Desktop";
            Assert.AreEqual(expected, actual, "The relative path when going one level down should be the sub-directory name.");

            actual = FileUtilities.GetRelativePath(@"C:\Documents and Settings\username\Desktop", @"D:\Documents and Settings\username\Desktop");
            expected = @"D:\Documents and Settings\username\Desktop";
            Assert.AreEqual(expected, actual, "The relative path when each path is on different drives should be the absolute path.");
        }

        /// <summary>
        ///A test for MergeFolderAndFileNameToFullFilePath
        ///</summary>
        [TestMethod()]
        public void MergeFolderAndFileNameToFullFilePathTest()
        {
            string actual = FileUtilities.MergeFolderAndFileNameToFullFilePath(@"C:\Temp", "MyTest", ".py");
            string expected = @"C:\Temp\MyTest.py";
            Assert.AreEqual(expected, actual);

            actual = FileUtilities.MergeFolderAndFileNameToFullFilePath(@"C:\Temp\", "MyTest", ".py");
            expected = @"C:\Temp\MyTest.py";
            Assert.AreEqual(expected, actual);

            actual = FileUtilities.MergeFolderAndFileNameToFullFilePath(@"C:\Temp", "MyTest");
            expected = @"C:\Temp\MyTest";
            Assert.AreEqual(expected, actual);

            actual = FileUtilities.MergeFolderAndFileNameToFullFilePath(@"C:\Temp", "MyTest.xaml");
            expected = @"C:\Temp\MyTest.xaml";
            Assert.AreEqual(expected, actual);

            actual = FileUtilities.MergeFolderAndFileNameToFullFilePath(@"\\server001\shared", "MyTest.xaml");
            expected = @"\\server001\shared\MyTest.xaml";
            Assert.AreEqual(expected, actual);

            actual = FileUtilities.MergeFolderAndFileNameToFullFilePath(@"..\", "MyTest.py");
            expected = Path.Combine(Directory.GetCurrentDirectory(), @"..\MyTest.py");
            Assert.AreEqual(expected, actual);
        }
    }
}
