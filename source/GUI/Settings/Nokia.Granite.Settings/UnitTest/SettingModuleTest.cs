using System.Collections.Generic;
using System.IO;
using System.Reflection;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace TestAutomation.Gui.Marble.Settings.UnitTest
{
    /// <summary>
    ///This is a test class for SettingModuleTest and is intended
    ///to contain all SettingModuleTest Unit Tests
    ///</summary>
    [TestClass()]
    public class SettingModuleTest
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
        ///A test for SettingModule Constructor
        ///</summary>
        [TestMethod()]
        [DeploymentItem("TestAutomation.Gui.Marble.Settings.dll")]
        public void SettingModuleConstructorTest()
        {
            SettingModule_Accessor target = new SettingModule_Accessor();
        }

        /// <summary>
        ///A test for Add
        ///</summary>
        [TestMethod()]
        public void AddTest()
        {
            SettingModule_Accessor target = new SettingModule_Accessor();
            Setting setting = new Setting();
            setting.Name = "Test";
            setting.DisplayName ="Test display name";
            setting.Description = "Test description";
            setting.Value = "TestValue";
            target.Add(setting);

            string expected = "TestValue";
            string actual = target.GetSettingValue("Test") as string;
            Assert.AreEqual(expected, actual, "Expected to be able to get the setting value for the setting we added.");
        }

        /// <summary>
        ///A test for AddRange
        ///</summary>
        [TestMethod()]
        public void AddRangeTest()
        {
            SettingModule_Accessor target = new SettingModule_Accessor();

            List<Setting> list = new List<Setting>();

            Setting setting1 = new Setting();
            setting1.Name = "Test 1";
            setting1.DisplayName = "Test display name 1";
            setting1.Description = "Test description 1";
            setting1.Value = "TestValue 1";
            list.Add(setting1);

            Setting setting2 = new Setting();
            setting2.Name = "Test 2";
            setting2.DisplayName = "Test display name 2";
            setting2.Description = "Test description 2";
            setting2.Value = "TestValue 2";
            list.Add(setting2);

            target.AddRange(list);

            string expected = "TestValue 1";
            string actual = target.GetSettingValue("Test 1") as string;
            Assert.AreEqual(expected, actual, "Expected to be able to get the setting value for the first setting we added.");

            expected = "TestValue 2";
            actual = target.GetSettingValue("Test 2") as string;
            Assert.AreEqual(expected, actual, "Expected to be able to get the setting value for the second setting we added.");
        }

        /// <summary>
        ///A test for FromJson
        ///</summary>
        [TestMethod()]
        public void FromJsonTest()
        {
            // Get the contents of an embedded resource setting file
            string data = UnitTestUtilities.GetEmbeddedResourceContents("SettingsInJsonFormat.json");

            SettingModule actual = SettingModule.FromJson(data);
            Assert.IsNotNull(actual, "Expected to be able to create a setting module from the supplied setting data.");

            // Construct some invalid data
            data = "This is data that is not in the valid format.";

            actual = SettingModule.FromJson(data);
            Assert.IsNull(actual, "Expected not to be able to create a setting module from invalid setting data.");
        }

        /// <summary>
        ///A test for FromXml
        ///</summary>
        [TestMethod()]
        public void FromXmlTest()
        {
            // Get the contents of an embedded resource setting file
            string data = UnitTestUtilities.GetEmbeddedResourceContents("MySettings.xml");

            SettingModule actual = SettingModule.FromXml(data);
            Assert.IsNotNull(actual, "Expected to be able to create a setting module from the supplied setting data.");

            // Construct some invalid data
            data = "This is data that is not in the valid format.";

            actual = SettingModule.FromXml(data);
            Assert.IsNull(actual, "Expected not to be able to create a setting module from invalid setting data.");
        }

        /// <summary>
        ///A test for GetSettingValue
        ///</summary>
        [TestMethod()]
        public void GetSettingValueTest()
        {
            SettingModule_Accessor target = new SettingModule_Accessor();
            Setting setting = new Setting();
            setting.Name = "Test";
            setting.DisplayName = "Test display name";
            setting.Description = "Test description";
            setting.Value = "TestValue";
            target.Add(setting);

            string expected = "TestValue";
            string actual = target.GetSettingValue("Test") as string;
            Assert.AreEqual(expected, actual, "Expected to be able to get the setting value for the setting we added.");

            expected = null;
            actual = target.GetSettingValue("DoesNotExist") as string;
            Assert.AreEqual(expected, actual, "Expected not to be able to get the setting value for a setting that does not exist.");
        }

        /// <summary>
        ///A test for GetSettingsFromJsonFile
        ///</summary>
        [TestMethod()]
        public void GetSettingsFromJsonFileTest()
        {
            // Construct a directory path for the settings
            string settingsDirectoryPath = Path.Combine(Path.GetTempPath(), Path.GetFileNameWithoutExtension(Path.GetRandomFileName()));

            if (Directory.Exists(settingsDirectoryPath))
            {
                // Delete the entire directory if it already exists
                Directory.Delete(settingsDirectoryPath, true);
            }

            // Create a new directory for this test
            Directory.CreateDirectory(settingsDirectoryPath);

            try
            {
                string fileName = "SettingsInJsonFormat.json";
                string filePath = Path.Combine(settingsDirectoryPath, fileName);

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, filePath);

                // Get the settings from the file
                SettingModule settingModule = SettingModule.GetSettingsFromJsonFile(filePath);

                Assert.IsNotNull(settingModule, "Expected to be able to get a setting module created from the settings file.");

                string expected = "899889";
                string actual = settingModule["name"] as string;
                Assert.AreEqual(expected, actual, "Expected to be able to get a setting value from the setting module.");
            }

            finally
            {
                if (Directory.Exists(settingsDirectoryPath))
                {
                    // Clean up by deleting the entire directory 
                    Directory.Delete(settingsDirectoryPath, true);
                }
            }
        }

        /// <summary>
        ///A test for GetSettingsFromPythonFile
        ///</summary>
        [TestMethod()]
        public void GetSettingsFromPythonFileTest()
        {
            // Construct a directory path for the settings
            string settingsDirectoryPath = Path.Combine(Path.GetTempPath(), Path.GetFileNameWithoutExtension(Path.GetRandomFileName()));

            if (Directory.Exists(settingsDirectoryPath))
            {
                // Delete the entire directory if it already exists
                Directory.Delete(settingsDirectoryPath, true);
            }

            // Create a new directory for this test
            Directory.CreateDirectory(settingsDirectoryPath);

            try
            {
                string fileName = "ModemSettings.py";
                string filePath = Path.Combine(settingsDirectoryPath, fileName);

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, filePath);

                // Get the settings from the file
                SettingModule settingModule = SettingModule.GetSettingsFromPythonFile(filePath);

                Assert.IsNotNull(settingModule, "Expected to be able to get a setting module created from the settings file.");

                string expected = "This is a Nokia test message from Marble";
                string actual = settingModule["SmsText"] as string;
                Assert.AreEqual(expected, actual, "Expected to be able to get a setting value from the setting module.");
            }

            finally
            {
                if (Directory.Exists(settingsDirectoryPath))
                {
                    // Clean up by deleting the entire directory 
                    Directory.Delete(settingsDirectoryPath, true);
                }
            }
        }

        /// <summary>
        ///A test for GetSettingsFromXmlFile
        ///</summary>
        [TestMethod()]
        public void GetSettingsFromXmlFileTest()
        {
            // Construct a directory path for the settings
            string settingsDirectoryPath = Path.Combine(Path.GetTempPath(), Path.GetFileNameWithoutExtension(Path.GetRandomFileName()));

            if (Directory.Exists(settingsDirectoryPath))
            {
                // Delete the entire directory if it already exists
                Directory.Delete(settingsDirectoryPath, true);
            }

            // Create a new directory for this test
            Directory.CreateDirectory(settingsDirectoryPath);

            try
            {
                string fileName = "MySettings.xml";
                string filePath = Path.Combine(settingsDirectoryPath, fileName);

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, filePath);

                // Get the settings from the file
                SettingModule settingModule = SettingModule.GetSettingsFromXmlFile(filePath);

                Assert.IsNotNull(settingModule, "Expected to be able to get a setting module created from the settings file.");

                string expected = "+3580505050945945849";
                string actual = settingModule["PhoneNumber"] as string;
                Assert.AreEqual(expected, actual, "Expected to be able to get a setting value from the setting module.");
            }

            finally
            {
                if (Directory.Exists(settingsDirectoryPath))
                {
                    // Clean up by deleting the entire directory 
                    Directory.Delete(settingsDirectoryPath, true);
                }
            }
        }

        /// <summary>
        ///A test for GetSettingsByFileExtension
        ///</summary>
        [TestMethod()]
        public void GetSettingsByFileExtensionTest()
        {
            // Construct a directory path for the settings
            string settingsDirectoryPath = Path.Combine(Path.GetTempPath(), Path.GetFileNameWithoutExtension(Path.GetRandomFileName()));

            if (Directory.Exists(settingsDirectoryPath))
            {
                // Delete the entire directory if it already exists
                Directory.Delete(settingsDirectoryPath, true);
            }

            // Create a new directory for this test
            Directory.CreateDirectory(settingsDirectoryPath);

            try
            {
                string fileName = "SettingsInJsonFormat.json";
                string filePath = Path.Combine(settingsDirectoryPath, fileName);

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, filePath);

                // Get the settings from the file
                SettingModule settingModule = SettingModule.GetSettingsByFileExtension(filePath);

                Assert.IsNotNull(settingModule, "Expected to be able to get a setting module created from the settings file.");

                string expected = "899889";
                string actual = settingModule["name"] as string;
                Assert.AreEqual(expected, actual, "Expected to be able to get a setting value from the setting module.");

                fileName = "ModemSettings.py";
                filePath = Path.Combine(settingsDirectoryPath, fileName);

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, filePath);

                // Get the settings from the file
                settingModule = SettingModule.GetSettingsByFileExtension(filePath);

                Assert.IsNotNull(settingModule, "Expected to be able to get a setting module created from the settings file.");

                expected = "This is a Nokia test message from Marble";
                actual = settingModule["SmsText"] as string;
                Assert.AreEqual(expected, actual, "Expected to be able to get a setting value from the setting module.");

                fileName = "MySettings.xml";
                filePath = Path.Combine(settingsDirectoryPath, fileName);

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, filePath);

                // Get the settings from the file
                settingModule = SettingModule.GetSettingsByFileExtension(filePath);

                Assert.IsNotNull(settingModule, "Expected to be able to get a setting module created from the settings file.");

                expected = "+3580505050945945849";
                actual = settingModule["PhoneNumber"] as string;
                Assert.AreEqual(expected, actual, "Expected to be able to get a setting value from the setting module.");
            }

            finally
            {
                if (Directory.Exists(settingsDirectoryPath))
                {
                    // Clean up by deleting the entire directory 
                    Directory.Delete(settingsDirectoryPath, true);
                }
            }
        }

        /// <summary>
        ///A test for IndexOf
        ///</summary>
        [TestMethod()]
        public void IndexOfTest()
        {
            SettingModule_Accessor target = new SettingModule_Accessor();

            Setting setting1 = new Setting();
            setting1.Name = "Test 1";
            setting1.DisplayName = "Test display name 1";
            setting1.Description = "Test description 1";
            setting1.Value = "TestValue 1";
            target.Add(setting1);

            Setting setting2 = new Setting();
            setting2.Name = "Test 2";
            setting2.DisplayName = "Test display name 2";
            setting2.Description = "Test description 2";
            setting2.Value = "TestValue 2";
            target.Add(setting2);

            int expected = 0;
            int actual = target.IndexOf(setting1);
            Assert.AreEqual(expected, actual, "Expected the first setting to have an index of 0.");

            expected = 1;
            actual = target.IndexOf(setting2);
            Assert.AreEqual(expected, actual, "Expected the second setting to have an index of 1.");

            Setting setting3 = new Setting();
            setting3.Name = "Not Added";
            expected = -1;
            actual = target.IndexOf(setting3);
            Assert.AreEqual(expected, actual, "Expected the index of a setting that has not been added to be -1.");
        }

        /// <summary>
        ///A test for Remove
        ///</summary>
        [TestMethod()]
        public void RemoveTest()
        {
            SettingModule_Accessor target = new SettingModule_Accessor();

            Setting setting1 = new Setting();
            setting1.Name = "Test 1";
            setting1.DisplayName = "Test display name 1";
            setting1.Description = "Test description 1";
            setting1.Value = "TestValue 1";
            target.Add(setting1);

            Setting setting2 = new Setting();
            setting2.Name = "Test 2";
            setting2.DisplayName = "Test display name 2";
            setting2.Description = "Test description 2";
            setting2.Value = "TestValue 2";
            target.Add(setting2);

            int expected = 0;
            int actual = target.IndexOf(setting1);
            Assert.AreEqual(expected, actual, "Expected the first setting to have an index of 0.");

            expected = 1;
            actual = target.IndexOf(setting2);
            Assert.AreEqual(expected, actual, "Expected the second setting to have an index of 1.");

            // Remove a setting
            target.Remove(setting2);

            expected = -1;
            actual = target.IndexOf(setting2);
            Assert.AreEqual(expected, actual, "Expected the second setting to have an index of -1 since it was removed.");
        }

        /// <summary>
        ///A test for ToJson
        ///</summary>
        [TestMethod()]
        public void ToJsonTest()
        {
            // Get the contents of an embedded resource setting file
            string data = UnitTestUtilities.GetEmbeddedResourceContents("SettingsInJsonFormat.json");

            SettingModule settingModule = SettingModule.FromJson(data);
            Assert.IsNotNull(settingModule, "Expected to be able to create a setting module from the supplied setting data.");

            string expected = data;
            string actual = settingModule.ToJson();
            Assert.AreEqual(expected, actual, "Expected the setting data to match that of the setting data used to create the setting module.");
        }

        /// <summary>
        ///A test for ToXml
        ///</summary>
        [TestMethod()]
        public void ToXmlTest()
        {
            // Get the contents of an embedded resource setting file
            string data = UnitTestUtilities.GetEmbeddedResourceContents("MySettings.xml");

            SettingModule settingModule = SettingModule.FromXml(data);
            Assert.IsNotNull(settingModule, "Expected to be able to create a setting module from the supplied setting data.");

            string expected = data;
            string actual = settingModule.ToXml();
            Assert.AreEqual(expected, actual, "Expected the setting data to match that of the setting data used to create the setting module.");
        }

        /// <summary>
        ///A test for Name
        ///</summary>
        [TestMethod()]
        [DeploymentItem("TestAutomation.Gui.Marble.Settings.dll")]
        public void NameTest()
        {
            SettingModule_Accessor target = new SettingModule_Accessor();
            string expected = "My Name";
            target.Name = expected;
            string actual = target.Name;
            Assert.AreEqual(expected, actual);
        }

        /// <summary>
        ///A test for Name being derived from the setting file name.
        ///</summary>
        [TestMethod()]
        public void NameFromSettingFilePathTest()
        {
            SettingModule_Accessor target = new SettingModule_Accessor();
            target.SettingFilePath = @"c:\temp\MySettings.py";
            string expected = "MySettings";
            string actual = target.Name;
            Assert.AreEqual(expected, actual, "Expected the name to be derived from the setting file name.");

            target.SettingFilePath = @"c:\temp\My Settings 2.py";
            expected = "MySettings2";
            actual = target.Name;
            Assert.AreEqual(expected, actual, "Expected the name to be derived from the setting file name.");
        }

        /// <summary>
        ///A test for SavedSettingsFilePath.
        ///</summary>
        [TestMethod()]
        public void SaveSettingFilePathFromSettingFilePathTest()
        {
            SettingModule_Accessor target = new SettingModule_Accessor();
            target.SettingFilePath = @"c:\temp\MySettings1.xml";
            string expected = @"c:\temp\MySettings1.xml";
            string actual = target.SavedSettingsFilePath;
            Assert.AreEqual(expected, actual, "Expected the saved setting file path to be the same as the setting file path for XML files.");

            target.SettingFilePath = @"c:\temp\MySettings.py";
            expected = @"c:\temp\MySettings.xml";
            actual = target.SavedSettingsFilePath;
            Assert.AreEqual(expected, actual, "Expected the saved setting file path to be the XML file for IronPython setting files.");
        }

#if SUPPORT_DEFAULT_SUBDIRECTORY
        /// <summary>
        ///A test for SavedSettingsFilePath when a 'default' special directory has been used.
        ///</summary>
        [TestMethod()]
        public void SaveSettingFilePathFromSettingFilePathInSpecialDefaultDirectoryTest()
        {
            SettingModule_Accessor target = new SettingModule_Accessor();
            target.SettingFilePath = @"c:\temp\default\MySettings.py";
            string expected = @"c:\temp\MySettings.xml";
            string actual = target.SavedSettingsFilePath;
            Assert.AreEqual(expected, actual, "Expected the saved setting file path to be in the parent for IronPython setting files in the special 'default' directory.");

            target.SettingFilePath = @"c:\temp\directory1\MySettings.py";
            expected = @"c:\temp\directory1\MySettings.xml";
            actual = target.SavedSettingsFilePath;
            Assert.AreEqual(expected, actual, "Expected the saved setting file path to be in the same directory for IronPython setting files not in the special 'default' directory.");

            target.SettingFilePath = @"c:\temp\default\MySettings.xml";
            expected = @"c:\temp\default\MySettings.xml";
            actual = target.SavedSettingsFilePath;
            Assert.AreEqual(expected, actual, "Expected the saved setting file path to be in the same directory for XML setting files even if they are in the special 'default' directory.");
        }
#endif

        /// <summary>
        ///A test for GenerateSettingModuleName
        ///</summary>
        [TestMethod()]
        public void GenerateSettingModuleNameTest()
        {
            MethodInfo method = typeof(SettingModule).GetMethod("GenerateSettingModuleName", BindingFlags.Static | BindingFlags.NonPublic);
            if (method == null)
            {
                Assert.Inconclusive("Cannot unit test the 'GenerateSettingModuleName' method since it is no longer implemented.");
            }
            else
            {
                string token = "Main";
                string expected = "Main";
                string actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The name has not correctly been converted to a setting module name.");

                token = "Test run";
                expected = "Testrun";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The name has not correctly been converted to a setting module name.");

                token = " ABC ";
                expected = "ABC";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The name has not correctly been converted to a setting module name.");

                token = "def hij k";
                expected = "defhijk";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The name has not correctly been converted to a setting module name.");

                token = " a ";
                expected = "a";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The name has not correctly been converted to a setting module name.");

                token = "  ";
                expected = "";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The name has not correctly been converted to a setting module name.");

                token = "Abc $%^£& def";
                expected = "Abcdef";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The name has not correctly been converted to a setting module name.");

                token = "1. xyz";
                expected = "xyz";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The name has not correctly been converted to a setting module name.");

                token = "abc_def";
                expected = "abcdef";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The name has not correctly been converted to a setting module name.");

                token = " a/b\\c";
                expected = "abc";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The name has not correctly been converted to a setting module name.");
            }
        }
    }
}
