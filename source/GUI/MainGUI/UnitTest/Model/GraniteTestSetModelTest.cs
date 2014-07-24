using System.IO;
using System.Text;
using Granite.Model;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Granite.UnitTest.Model
{
    /// <summary>
    ///This is a test class for GraniteTestSetModelTest and is intended
    ///to contain all GraniteTestSetModelTest Unit Tests
    ///</summary>
    [TestClass()]
    public class GraniteTestSetModelTest
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
        ///A test for GraniteTestSetModel Constructor
        ///</summary>
        [TestMethod()]
        public void GraniteTestSetModelConstructorTest()
        {
            string emptyTestSetXml = @"<?xml version=""1.0"" encoding=""utf-8""?>" +
                                     @"<testset />";

            // Create a temporary file
            string filePath = Path.GetTempFileName();

            try
            {
                using (StreamWriter writer = new StreamWriter(filePath, false, Encoding.UTF8))
                {
                    // Write the test set XML to the file
                    writer.Write(emptyTestSetXml);
                }

                GraniteTestSetModel target = new GraniteTestSetModel(filePath);
            }

            finally
            {
                if (File.Exists(filePath))
                {
                    File.Delete(filePath);
                }
            }
        }

        /// <summary>
        ///A test for HasCoreTestToolTest
        ///</summary>
        [TestMethod()]
        public void HasCoreTestToolTestTest()
        {
            string emptyTestSetXml = @"<?xml version=""1.0"" encoding=""utf-8""?>" +
                                     @"<testset />";

            // Create a temporary file
            string filePath = Path.GetTempFileName();

            try
            {
                using (StreamWriter writer = new StreamWriter(filePath, false, Encoding.UTF8))
                {
                    // Write the test set XML to the file
                    writer.Write(emptyTestSetXml);
                }

                GraniteTestSetModel target = new GraniteTestSetModel(filePath);

                bool expected = false;
                bool actual = target.HasCoreTestToolTest;
                Assert.AreEqual(expected, actual, "There should not be a Core Test Tool test in an empty test set.");

                // Create a Core Test Tool test
                TestScript script = new TestScript("class", @"c:\temp", "assembly.dll", "method");
                TestCase testCase = new TestCase("Test case name", script, null, "CTT", "Unit Test");

                // Add the Core Test Tool test to the test set
                target.TestCases.Add(testCase);
                target.IsChanged = true;
                expected = true;
                actual = target.HasCoreTestToolTest;
                Assert.AreEqual(expected, actual, "The test set should have a Core Test Tool test since one has been added.");

                // Add a test case that is not a Core Test Tool test
                target.TestCases.Add(new TestCase("Not a CTT test", new TestScript("class", @"c:\temp", "test.py", "method")));
                target.IsChanged = true;

                expected = true;
                actual = target.HasCoreTestToolTest;
                Assert.AreEqual(expected, actual, "The test set should have a Core Test Tool test since one was originally added.");

                // Remove the Core Test Tool test
                target.TestCases.Remove(testCase);
                target.IsChanged = true;

                expected = false;
                actual = target.HasCoreTestToolTest;
                Assert.AreEqual(expected, actual, "The test set should not have a Core Test Tool test since it was removed.");
            }

            finally
            {
                if (File.Exists(filePath))
                {
                    File.Delete(filePath);
                }
            }
        }

        /// <summary>
        ///A test for IsCoreTestToolOnlyTestSet
        ///</summary>
        [TestMethod()]
        public void IsCoreTestToolOnlyTestSetTest()
        {
            string emptyTestSetXml = @"<?xml version=""1.0"" encoding=""utf-8""?>" +
                                     @"<testset />";

            // Create a temporary file
            string filePath = Path.GetTempFileName();

            try
            {
                using (StreamWriter writer = new StreamWriter(filePath, false, Encoding.UTF8))
                {
                    // Write the test set XML to the file
                    writer.Write(emptyTestSetXml);
                }

                GraniteTestSetModel target = new GraniteTestSetModel(filePath);

                bool expected = false;
                bool actual = target.IsCoreTestToolOnlyTestSet;
                Assert.AreEqual(expected, actual, "This should not be a test set with only Core Test Tool tests since it is empty.");

                // Create a Core Test Tool test
                TestScript script = new TestScript("class", @"c:\temp", "assembly.dll", "method");
                TestCase testCase = new TestCase("Test case name", script, null, "CTT", "Unit Test");

                // Add the Core Test Tool test to the test set
                target.TestCases.Add(testCase);
                target.IsChanged = true;
                expected = true;
                actual = target.IsCoreTestToolOnlyTestSet;
                Assert.AreEqual(expected, actual, "This should be a test set with only Core Test Tool tests since it contains only a single Core Test Tool test.");

                // Add a test case that is not a Core Test Tool test
                target.TestCases.Add(new TestCase("Not a CTT test", new TestScript("class", @"c:\temp", "test.py", "method")));
                target.IsChanged = true;

                expected = false;
                actual = target.IsCoreTestToolOnlyTestSet;
                Assert.AreEqual(expected, actual, "This should not be a test set with only Core Test Tool tests since it contains a mixture of tests (i.e. hybrid test set).");

                // Remove the Core Test Tool test
                target.TestCases.Remove(testCase);
                target.IsChanged = true;

                expected = false;
                actual = target.IsCoreTestToolOnlyTestSet;
                Assert.AreEqual(expected, actual, "This should not be a test set with only Core Test Tool tests since it does not contain any Core Test Tool tests.");
            }

            finally
            {
                if (File.Exists(filePath))
                {
                    File.Delete(filePath);
                }
            }
        }
    }
}
