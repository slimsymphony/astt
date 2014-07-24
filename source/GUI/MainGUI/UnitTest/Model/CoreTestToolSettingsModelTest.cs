using System;
using Granite.Model;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Granite.UnitTest.Model
{
    /// <summary>
    ///This is a test class for CoreTestToolSettingsModelTest and is intended
    ///to contain all CoreTestToolSettingsModelTest Unit Tests
    ///</summary>
    [TestClass()]
    public class CoreTestToolSettingsModelTest
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
        ///A test for Create
        ///</summary>
        [TestMethod()]
        public void CreateTest()
        {
            string[] assemblyFilePaths = new string[] { @"C:\temp\assembly1.dll", @"C:\temp\assembly2.dll" };
            string[] configurationFilePaths = new string[] { @"C:\temp\assembly1.dll.config", @"C:\temp\assembly2.dll.config" };
            string[] sectionNames = new string[] { "TestSection1", "TestSection2" };
            CoreTestToolSettingsModel target = CoreTestToolSettingsModel.Create(assemblyFilePaths, configurationFilePaths, sectionNames);
            
            int count = 0;
            foreach (var section in target.SettingsSections)
            {
                count++;
            }

            Assert.AreEqual(assemblyFilePaths.Length, count, "The number of settings sections should match the number of assembly file paths.");
        }

        /// <summary>
        ///A test for Create with empty arrays
        ///</summary>
        [TestMethod()]
        public void CreateTestWithEmptyArrays()
        {
            string[] assemblyFilePaths = new string[] { };
            string[] configurationFilePaths = new string[] { };
            string[] sectionNames = new string[] { };
            CoreTestToolSettingsModel target = CoreTestToolSettingsModel.Create(assemblyFilePaths, configurationFilePaths, sectionNames);

            int count = 0;
            foreach (var section in target.SettingsSections)
            {
                count++;
            }

            Assert.AreEqual(assemblyFilePaths.Length, count, "The number of settings sections should match the number of assembly file paths.");
        }

        /// <summary>
        ///A test for Create with null arguments
        ///</summary>
        [TestMethod()]
        [ExpectedException(typeof(ArgumentNullException))]
        public void CreateTestWithNullArguments()
        {
            CoreTestToolSettingsModel target = CoreTestToolSettingsModel.Create(null, null, null);
        }

        /// <summary>
        ///A test for Create with arguments of different lengths
        ///</summary>
        [TestMethod()]
        [ExpectedException(typeof(ArgumentException))]
        public void CreateTestWithArgumentsDifferentLengths()
        {
            string[] assemblyFilePaths = new string[] { @"C:\temp\assembly1.dll", @"C:\temp\assembly2.dll" };
            string[] configurationFilePaths = new string[] { @"C:\temp\assembly1.dll.config" };
            string[] sectionNames = new string[] { "TestSection1", "TestSection2" };
            CoreTestToolSettingsModel target = CoreTestToolSettingsModel.Create(assemblyFilePaths, configurationFilePaths, sectionNames);
        }
    }
}
