using Granite.Model;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Configuration;
using System.IO;

namespace Granite.UnitTest.Model
{
    /// <summary>
    ///This is a test class for CoreTestToolSettingsSectionTest and is intended
    ///to contain all CoreTestToolSettingsSectionTest Unit Tests
    ///</summary>
    [TestClass()]
    public class CoreTestToolSettingsSectionTest
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
        ///A test for CoreTestToolSettingsSection Constructor
        ///</summary>
        [TestMethod()]
        public void CoreTestToolSettingsSectionConstructorTest()
        {
            string assemblyFilePath = @"c:\temp\assembly.dll";
            string configurationFilePath = @"c:\temp\assembly.dll.config";
            string sectionName = "TestSettings";
            CoreTestToolSettingsSection target = new CoreTestToolSettingsSection(assemblyFilePath, configurationFilePath, sectionName);
        }

        /// <summary>
        ///A test for GetSectionXml where the section name does not exist
        ///</summary>
        [TestMethod()]
        public void GetSectionXmlSectionNameDoesNotExistTest()
        {
            string assemblyFilePath = GetType().Assembly.Location;
            string configurationFilePath = assemblyFilePath + ".config";
            string sectionName = "TestSettings";
            CoreTestToolSettingsSection target = new CoreTestToolSettingsSection(assemblyFilePath, configurationFilePath, sectionName);
            string actual = target.GetSectionXml();
            Assert.IsNull(actual, "There should be no section XML information since this assembly does not have the '" + sectionName + "' configuration section name.");
        }

        /// <summary>
        ///A test for GetSectionXml where the assembly does not exist
        ///</summary>
        [TestMethod()]
        public void GetSectionXmlAssemblyDoesNotExistTest()
        {
            string assemblyFilePath = @"c:\temp\assemblyDoesNotExist.dll";
            string configurationFilePath = @"c:\temp\assemblyDoesNotExist.dll.config";
            string sectionName = "TestSettings";
            if (File.Exists(assemblyFilePath))
            {
                // Make sure the assembly file does not exist
                File.Delete(assemblyFilePath);
            }
            CoreTestToolSettingsSection target = new CoreTestToolSettingsSection(assemblyFilePath, configurationFilePath, sectionName);
            string actual = target.GetSectionXml();
            Assert.IsNull(actual, "There should be no section XML information since this '" + assemblyFilePath + " assembly does not exist.");
        }

        /// <summary>
        ///A test for Load where the section name does not exist
        ///</summary>
        [TestMethod()]
        public void LoadSectionNameDoesNotExistTest()
        {
            string assemblyFilePath = GetType().Assembly.Location;
            string configurationFilePath = assemblyFilePath + ".config";
            string sectionName = "TestSettings";
            CoreTestToolSettingsSection target = new CoreTestToolSettingsSection(assemblyFilePath, configurationFilePath, sectionName);
            target.Load();
        }

        /// <summary>
        ///A test for Load where the assembly does not exist
        ///</summary>
        [TestMethod()]
        public void LoadAssemblyDoesNotExistTest()
        {
            string assemblyFilePath = @"c:\temp\assemblyDoesNotExist.dll";
            string configurationFilePath = @"c:\temp\assemblyDoesNotExist.dll.config";
            string sectionName = "TestSettings";
            if (File.Exists(assemblyFilePath))
            {
                // Make sure the assembly file does not exist
                File.Delete(assemblyFilePath);
            }
            CoreTestToolSettingsSection target = new CoreTestToolSettingsSection(assemblyFilePath, configurationFilePath, sectionName);
            target.Load();
        }

        /// <summary>
        ///A test for IsDirty
        ///</summary>
        [TestMethod()]
        public void IsDirtyTest()
        {
            string assemblyFilePath = GetType().Assembly.Location;
            string configurationFilePath = assemblyFilePath + ".config";
            string sectionName = "TestSettings";
            CoreTestToolSettingsSection target = new CoreTestToolSettingsSection(assemblyFilePath, configurationFilePath, sectionName);
            bool expected = false;
            bool actual = target.IsDirty;
            Assert.AreEqual(expected, actual, "The Core Test Tool settings section should not be dirty if we have made no changes.");

            target.Load();
            expected = false;
            actual = target.IsDirty;
            Assert.AreEqual(expected, actual, "The Core Test Tool settings section should not be dirty if we have made no changes.");
        }

        /// <summary>
        ///A test for IsLoaded
        ///</summary>
        [TestMethod()]
        public void IsLoadedTest()
        {
            string assemblyFilePath = GetType().Assembly.Location;
            string configurationFilePath = assemblyFilePath + ".config";
            string sectionName = "TestSettings";
            CoreTestToolSettingsSection target = new CoreTestToolSettingsSection(assemblyFilePath, configurationFilePath, sectionName);
            bool expected = false;
            bool actual = target.IsLoaded;
            Assert.AreEqual(expected, actual, "The Core Test Tool settings section should initially not be loaded.");

            target.Load();
            expected = false;
            actual = target.IsLoaded;
            Assert.AreEqual(expected, actual, "Even though we have done a Load the Core Test Tool settings section should initially not be loaded since we have specified a section name that does not exist and therefore cannot load.");
        }
    }
}
