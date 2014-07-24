using System.Collections.Generic;
using Granite.Model;
using Granite.Utilities;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Granite.UnitTest.Utilities
{
    /// <summary>
    ///This is a test class for CoreTestToolUtilitiesTest and is intended
    ///to contain all CoreTestToolUtilitiesTest Unit Tests
    ///</summary>
    [TestClass()]
    public class CoreTestToolUtilitiesTest
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
        ///A test for IsCoreTestToolTest
        ///</summary>
        [TestMethod()]
        public void IsCoreTestToolTestTest()
        {
            string name = "Test case name";
            TestScript script = null;
            TestResult result = null;
            string subarea = "Unit Test";
            string feature = "CTT";
            TestCase testCase = new TestCase(name, script, result, feature, subarea);

            bool expected = false;
            bool actual = CoreTestToolUtilities.IsCoreTestToolTest(testCase);
            Assert.AreEqual(expected, actual);

            script = new TestScript("class", @"c:\temp", "filename", "method");
            testCase = new TestCase(name, script, result, feature, subarea);
            expected = false;
            actual = CoreTestToolUtilities.IsCoreTestToolTest(testCase);
            Assert.AreEqual(expected, actual);

            script = new TestScript("class", @"c:\temp", "assembly.dll", "method");
            testCase = new TestCase(name, script, result, feature, subarea);
            expected = true;
            actual = CoreTestToolUtilities.IsCoreTestToolTest(testCase);
            Assert.AreEqual(expected, actual);
        }

        /// <summary>
        ///A test for IsCoreTestToolScript
        ///</summary>
        [TestMethod()]
        public void IsCoreTestToolScriptTest()
        {
            TestScript script = null;
            bool expected = false;
            bool actual = CoreTestToolUtilities.IsCoreTestToolScript(script);
            Assert.AreEqual(expected, actual);

            script = new TestScript("class", @"c:\temp", "filename", "method");
            expected = false;
            actual = CoreTestToolUtilities.IsCoreTestToolScript(script);
            Assert.AreEqual(expected, actual);

            script = new TestScript("class", @"c:\temp", "assembly.dll", "method");
            expected = true;
            actual = CoreTestToolUtilities.IsCoreTestToolScript(script);
            Assert.AreEqual(expected, actual);
        }

        /// <summary>
        ///A test for HasCoreTestToolConfigurationSectionNames for a test case.
        ///</summary>
        [TestMethod()]
        public void HasCoreTestToolConfigurationSectionNamesForTestCaseTest()
        {
            // Test for a test case that is not a CTT test case
            string name = "Test case name";
            TestScript script = null;
            TestResult result = null;
            string subarea = "Unit Test";
            string feature = "CTT";
            TestCase testCase = new TestCase(name, script, result, feature, subarea);
            bool expected = false;
            bool actual = CoreTestToolUtilities.HasCoreTestToolConfigurationSectionNames(testCase);
            Assert.AreEqual(expected, actual);

            // Test for a test case that has no configuration
            script = new TestScript(string.Empty, @"c:\temp", "assembly.dll", string.Empty);
            testCase = new TestCase(name, script, result, feature, subarea);
            expected = false;
            actual = CoreTestToolUtilities.HasCoreTestToolConfigurationSectionNames(testCase);
            Assert.AreEqual(expected, actual);

            // Test without any sections
            script = new TestScript(string.Empty, @"c:\temp", "assembly.dll", string.Empty);
            testCase = new TestCase(name, script, result, feature, subarea);
            List<string> sectionNames = new List<string>();
            CoreTestToolConfiguration configuration = new CoreTestToolConfiguration(@"c:\temp", @"assembly.dll.config", sectionNames);
            script.Configuration = configuration;
            expected = false;
            actual = CoreTestToolUtilities.HasCoreTestToolConfigurationSectionNames(testCase);
            Assert.AreEqual(expected, actual);

            // Test with some section names
            script = new TestScript(string.Empty, @"c:\temp", "assembly.dll", string.Empty);
            testCase = new TestCase(name, script, result, feature, subarea);
            sectionNames = new List<string>();
            sectionNames.Add("section1");
            sectionNames.Add("section2");
            configuration = new CoreTestToolConfiguration(@"c:\temp", @"assembly.dll.config", sectionNames);
            script.Configuration = configuration;
            expected = true;
            actual = CoreTestToolUtilities.HasCoreTestToolConfigurationSectionNames(testCase);
            Assert.AreEqual(expected, actual);
        }

        /// <summary>
        ///A test for HasCoreTestToolConfigurationSectionNames for a test script.
        ///</summary>
        [TestMethod()]
        public void HasCoreTestToolConfigurationSectionNamesForTestScriptTest()
        {
            // Test for a test script that has no configuration
            TestScript script = new TestScript(string.Empty, @"c:\temp", "assembly.dll", string.Empty);
            bool expected = false;
            bool actual = CoreTestToolUtilities.HasCoreTestToolConfigurationSectionNames(script);
            Assert.AreEqual(expected, actual);

            // Test without any sections
            script = new TestScript(string.Empty, @"c:\temp", "assembly.dll", string.Empty);
            List<string> sectionNames = new List<string>();
            CoreTestToolConfiguration configuration = new CoreTestToolConfiguration(@"c:\temp", @"assembly.dll.config", sectionNames);
            script.Configuration = configuration;
            expected = false;
            actual = CoreTestToolUtilities.HasCoreTestToolConfigurationSectionNames(script);
            Assert.AreEqual(expected, actual);

            // Test with some section names
            script = new TestScript(string.Empty, @"c:\temp", "assembly.dll", string.Empty);
            sectionNames = new List<string>();
            sectionNames.Add("section1");
            sectionNames.Add("section2");
            configuration = new CoreTestToolConfiguration(@"c:\temp", @"assembly.dll.config", sectionNames);
            script.Configuration = configuration;
            expected = true;
            actual = CoreTestToolUtilities.HasCoreTestToolConfigurationSectionNames(script);
            Assert.AreEqual(expected, actual);
        }
    }
}
