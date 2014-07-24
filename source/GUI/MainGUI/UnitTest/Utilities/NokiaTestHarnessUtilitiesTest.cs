using System;
using System.IO;
using Granite.Model;
using Granite.Utilities;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Granite.UnitTest.Utilities
{
    /// <summary>
    ///This is a test class for NokiaTestHarnessUtilitiesTest and is intended
    ///to contain all NokiaTestHarnessUtilitiesTest Unit Tests
    ///</summary>
    [TestClass()]
    public class NokiaTestHarnessUtilitiesTest
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
        ///A test for IsNokiaTestHarnessTest
        ///</summary>
        [TestMethod()]
        public void IsNokiaTestHarnessTestTest()
        {
            string name = "Test case name";
            TestScript script = null;
            TestResult result = null;
            string subarea = "Unit Test";
            string feature = "NTH";
            TestCase testCase = new TestCase(name, script, result, feature, subarea);

            bool expected = false;
            bool actual = NokiaTestHarnessUtilities.IsNokiaTestHarnessTest(testCase);
            Assert.AreEqual(expected, actual);

            script = new TestScript("class", @"c:\temp", "filename", "method");
            testCase = new TestCase(name, script, result, feature, subarea);
            expected = false;
            actual = NokiaTestHarnessUtilities.IsNokiaTestHarnessTest(testCase);
            Assert.AreEqual(expected, actual);

            script = new TestScript("class", @"c:\temp", "midlet.jad", "method");
            testCase = new TestCase(name, script, result, feature, subarea);
            expected = true;
            actual = NokiaTestHarnessUtilities.IsNokiaTestHarnessTest(testCase);
            Assert.AreEqual(expected, actual);

            script = new TestScript("class", @"c:\temp", "midlet.jar", "method");
            testCase = new TestCase(name, script, result, feature, subarea);
            expected = true;
            actual = NokiaTestHarnessUtilities.IsNokiaTestHarnessTest(testCase);
            Assert.AreEqual(expected, actual);
        }

        /// <summary>
        ///A test for IsNokiaTestHarnessScript
        ///</summary>
        [TestMethod()]
        public void IsNokiaTestHarnessScriptTest()
        {
            TestScript script = null;
            bool expected = false;
            bool actual = NokiaTestHarnessUtilities.IsNokiaTestHarnessScript(script);
            Assert.AreEqual(expected, actual);

            script = new TestScript("class", @"c:\temp", "filename", "method");
            expected = false;
            actual = NokiaTestHarnessUtilities.IsNokiaTestHarnessScript(script);
            Assert.AreEqual(expected, actual);

            script = new TestScript("class", @"c:\temp", "midlet.jad", "method");
            expected = true;
            actual = NokiaTestHarnessUtilities.IsNokiaTestHarnessScript(script);
            Assert.AreEqual(expected, actual);

            script = new TestScript("class", @"c:\temp", "midlet.jar", "method");
            expected = true;
            actual = NokiaTestHarnessUtilities.IsNokiaTestHarnessScript(script);
            Assert.AreEqual(expected, actual);
        }

        /// <summary>
        ///A test for CreateTestCase with a <c>null</c> file path
        ///</summary>
        [TestMethod()]
        [ExpectedException(typeof(ArgumentNullException))]
        public void CreateTestCaseWithNullFilePathTest()
        {
            NokiaTestHarnessUtilities.CreateTestCase(null);
        }

        /// <summary>
        ///A test for CreateTestCase with a file path that has an incorrect file extension
        ///</summary>
        [TestMethod()]
        [ExpectedException(typeof(ArgumentException))]
        public void CreateTestCaseWithInvalidFileExtensionTest()
        {
            NokiaTestHarnessUtilities.CreateTestCase(@"c:\temp\document.txt");
        }

        /// <summary>
        ///A test for CreateTestCase with a file path to a Java archive file.
        ///</summary>
        [TestMethod()]
        public void CreateTestCaseWithJavaArchiveFileTest()
        {
            string filePath = @"c:\temp\midlet.jar";
            TestCase testCase = NokiaTestHarnessUtilities.CreateTestCase(filePath);
            Assert.IsNotNull(testCase, "A test case should be created.");
            Assert.IsNotNull(testCase.Script, "The test case created should contain a script.");
            string expected = Path.GetFileName(filePath);
            Assert.AreEqual(expected, testCase.Script.file, "Expected the script file to be the '" + expected + "' file name.");
        }

        /// <summary>
        ///A test for CreateTestCase with a file path to a Java application descriptor file.
        ///</summary>
        [TestMethod()]
        public void CreateTestCaseWithJavaApplicationDescriptorFileTest()
        {
            string filePath = @"c:\temp\midlet.jad";
            TestCase testCase = NokiaTestHarnessUtilities.CreateTestCase(filePath);
            Assert.IsNotNull(testCase, "A test case should be created.");
            Assert.IsNotNull(testCase.Script, "The test case created should contain a script.");
            string expected = Path.GetFileNameWithoutExtension(filePath) + ".jar";
            Assert.AreEqual(expected, testCase.Script.file, "Expected the script file to be the '" + expected + "' Java archive file name.");
        }
    }
}
