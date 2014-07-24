using Granite.Model;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Linq;
using System.Xml.Linq;
using System.Collections.Generic;

namespace Granite.UnitTest.Model
{
    
    
    /// <summary>
    ///This is a test class for CoreTestToolConfigurationTest and is intended
    ///to contain all CoreTestToolConfigurationTest Unit Tests
    ///</summary>
    [TestClass()]
    public class CoreTestToolConfigurationTest
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
        ///A test for CoreTestToolConfiguration Constructor
        ///</summary>
        [TestMethod()]
        public void CoreTestToolConfigurationConstructorTest()
        {
            string directory = @"C:\temp";
            string file = @"assembly.dll";

            // Test with a null section names enumerator
            CoreTestToolConfiguration target = new CoreTestToolConfiguration(directory, file, null);

            // Test with an empty list of section names
            List<string> sectionNames = new List<string>();
            target = new CoreTestToolConfiguration(directory, file, sectionNames);

            // Test with some section names
            sectionNames = new List<string>();
            sectionNames.Add("section1");
            sectionNames.Add("section2");
            target = new CoreTestToolConfiguration(directory, file, sectionNames);
        }

        /// <summary>
        ///A test for ToXml
        ///</summary>
        [TestMethod()]
        public void ToXmlTest()
        {
            string directory = @"C:\temp";
            string file = @"assembly.dll";

            // Test with an empty list of section names
            List<string> sectionNames = new List<string>();
            CoreTestToolConfiguration target = new CoreTestToolConfiguration(directory, file, sectionNames);
            XElement actual = target.ToXml();
            Assert.AreEqual(actual.Attribute("directory").Value, directory);
            Assert.AreEqual(actual.Attribute("file").Value, file);
            Assert.IsNull(actual.Elements("section").FirstOrDefault(), "There should be no section child elements.");

            // Test with some section names
            sectionNames = new List<string>();
            sectionNames.Add("section1");
            sectionNames.Add("section2");
            target = new CoreTestToolConfiguration(directory, file, sectionNames);
            actual = target.ToXml();
            Assert.AreEqual(actual.Attribute("directory").Value, directory);
            Assert.AreEqual(actual.Attribute("file").Value, file);
            Assert.IsNotNull(actual.Elements("section").FirstOrDefault(), "There should be section child elements.");
        }

        /// <summary>
        ///A test for SectionNames
        ///</summary>
        [TestMethod()]
        public void SectionNamesTest()
        {
            string directory = @"C:\temp";
            string file = @"assembly.dll";

            // Test with a null section names enumerator
            CoreTestToolConfiguration target = new CoreTestToolConfiguration(directory, file, null);
            Assert.IsNotNull(target.SectionNames, "The enumerator for the section names should not be null.");
            Assert.IsNull(target.SectionNames.FirstOrDefault(), "There should be no section names.");

            // Test with an empty list of section names
            List<string> sectionNames = new List<string>();
            target = new CoreTestToolConfiguration(directory, file, sectionNames);
            Assert.IsNotNull(target.SectionNames, "The enumerator for the section names should not be null.");
            Assert.IsNull(target.SectionNames.FirstOrDefault(), "There should be no section names.");

            // Test with some section names
            sectionNames = new List<string>();
            sectionNames.Add("section1");
            sectionNames.Add("section2");
            target = new CoreTestToolConfiguration(directory, file, sectionNames);
            Assert.IsNotNull(target.SectionNames, "The enumerator for the section names should not be null.");
            Assert.IsNotNull(target.SectionNames.FirstOrDefault(), "There should be some section names.");
        }

        /// <summary>
        ///A test for Directory
        ///</summary>
        [TestMethod()]
        public void DirectoryTest()
        {
            string directory = @"C:\temp";
            string file = @"assembly.dll";
            List<string> sectionNames = new List<string>();

            CoreTestToolConfiguration target = new CoreTestToolConfiguration(directory, file, sectionNames);
            string actual = target.Directory;
            Assert.AreEqual(directory, actual);
        }

        /// <summary>
        ///A test for File
        ///</summary>
        [TestMethod()]
        public void FileTest()
        {
            string directory = @"C:\temp";
            string file = @"assembly.dll";
            List<string> sectionNames = new List<string>();

            CoreTestToolConfiguration target = new CoreTestToolConfiguration(directory, file, sectionNames);
            string actual = target.File;
            Assert.AreEqual(file, actual);
        }
    }
}
