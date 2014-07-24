using System;
using System.Collections;
using System.IO;
using System.Threading;
using IronPython.Hosting;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace TestAutomation.Gui.Marble.Settings.UnitTest
{
    /// <summary>
    ///This is a test class for SettingManagerTest and is intended
    ///to contain all SettingManagerTest Unit Tests
    ///</summary>
    [TestClass()]
    public class SettingsManagerTest
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
        ///A test for Instance
        ///</summary>
        [TestMethod()]
        public void InstanceTest()
        {
            SettingsManager firstInstance = SettingsManager.Instance;
            Assert.IsNotNull(firstInstance);

            // The same instance should be returned
            SettingsManager secondInstance = SettingsManager.Instance;
            Assert.AreEqual(secondInstance, secondInstance);
        }

        /// <summary>
        ///A test for Dispose
        ///</summary>
        [TestMethod()]
        public void DisposeTest()
        {
            using (SettingsManager target = SettingsManager.Instance)
            {
                Assert.IsNotNull(target);
            }

            // Reset the instance so that additional unit tests can be performed
            SettingsManager.Instance.Reset();
        }

        /// <summary>
        ///A test for calling Dispose multiple times.
        ///</summary>
        [TestMethod()]
        public void DisposeMultipleTimesTest()
        {
            SettingsManager target = SettingsManager.Instance;
            Assert.IsNotNull(target);
            target.Dispose();
            target.Dispose();
        }

        /// <summary>
        ///A test for Dispose and accessing the Count property afterwards.
        ///</summary>
        [TestMethod()]
        public void DisposeAndCountTest()
        {
            using (SettingsManager target = SettingsManager.Instance)
            {
                Assert.IsNotNull(target);
            }

            int expected = 0;
            int actual = SettingsManager.Instance.Count;
            Assert.AreEqual(expected, actual, "We should still be able to access the Count property after the SettingsManager has been disposed and it should be set to zero.");

            // Reset the instance so that additional unit tests can be performed
            SettingsManager.Instance.Reset();
        }

        /// <summary>
        /// A test for Dispose and then calling GetValue.
        /// </summary>
        [TestMethod()]
        [ExpectedException(typeof(ObjectDisposedException))]
        public void DisposeFollowedByGetValueTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.getValue("ModemSettings/Phone/PhoneNumber"), "Expected the phone number setting value to match that specified in the IronPython settings file.");

                // Dispose of settings manager
                SettingsManager.Instance.Dispose();

                // This should fail since the settings manager has been disposed
                string actualPhoneNumberValue = settings.getValue("ModemSettings/Phone/PhoneNumber");
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
        /// A test for Dispose and then getting a setting value using the dynamic behaviour.
        /// </summary>
        [TestMethod()]
        [ExpectedException(typeof(ObjectDisposedException))]
        public void DisposeFollowedByGettingSettingValueTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.ModemSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the IronPython settings file.");

                // Dispose of settings manager
                SettingsManager.Instance.Dispose();

                // This should fail since the settings manager has been disposed
                string actualPhoneNumberValue = settings.settings.ModemSettings.PhoneNumber;
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
        ///A test that we can use the settings module instance from IronPython and access a property.
        ///</summary>
        [TestMethod()]
        public void AccessSettingsModuleInstanceFromIronPythonTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

            // Verify we can access the settings manager and check the count value
            string ironPythonCode = "import clr\r\n" +
                                    "clr.AddReference('TestAutomation.Gui.Marble.Settings')\r\n" +
                                    "from TestAutomation.Gui.Marble.Settings import SettingsManager\r\n" +
                                    "assert SettingsManager.Instance.Count == 0, 'Expected to get the Count property on the SettingsManager instance and for it to be set to 0.'\r\n";
            Python.CreateEngine().Execute(ironPythonCode);
        }

        /// <summary>
        /// A test for LoadSettingsFromDirectory using an empty directory.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromEmptyDirectoryTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 0;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has no files so there should be no setting module.");
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
        /// A test for LoadSettingsFromDirectory using a directory containing invalid setting files.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromDirectoryWithInvalidFilesTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                // Create some invalid settings files
                using (var file = File.Create(Path.Combine(settingsDirectoryPath, "empty.xml")))
                {
                }
                using (var file = File.CreateText(Path.Combine(settingsDirectoryPath, "invalid.xml")))
                {
                    file.Write("<tag>This is invalid XML<>");
                }
                using (var file = File.CreateText(Path.Combine(settingsDirectoryPath, "readme.txt")))
                {
                    file.Write("This is file containing some text.");
                }
                using (var file = File.CreateText(Path.Combine(settingsDirectoryPath, "default.settings")))
                {
                    file.Write("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n" +
                               "<configuration version=\"50\"> <!-- Remove this element when framework supports it -->\r\n" +
                               "	<property branch=\"No\" hint=\"\" mandatory=\"False\" max_value=\"\" min_value=\"\" name=\"Settings\" type=\"Str\" urlType=\"\" val=\"\" valid_values=\"\">\r\n" +
                               "		<!-- TEST RUN -->\r\n" +
                               "		<property name=\"Test run\" booleanType=\"TrueFalse\" branch=\"Open\" hint=\"Common test run settings\" mandatory=\"False\" max_value=\"\" min_value=\"\" type=\"URL\" urlType=\"test run\" val=\"test_run.xml\" valid_values=\"\">\r\n" +
                               "			<property name=\"debug level\" booleanType=\"TrueFalse\" branch=\"No\" hint=\"Select how much debug info you want to get to main/remote console. 1 = lowest, 4 = highest\" mandatory=\"False\" max_value=\"\" min_value=\"\" type=\"Int\" urlType=\"\" val=\"2\" valid_values=\"1;2;3;4\"/>\r\n" +
                               "			<property name=\"enable blackbox\" booleanType=\"TrueFalse\" branch=\"No\" hint=\"Setting for enabling or disabling blackbox\" mandatory=\"True\" max_value=\"\" min_value=\"\" type=\"Bool\" urlType=\"\" val=\"False\" valid_values=\"\"/>\r\n" +
                               "			<property name=\"enable graybox\" booleanType=\"TrueFalse\" branch=\"No\" hint=\"Setting for enabling whitebox touch and key simulation in blackbox mode\" mandatory=\"True\" max_value=\"\" min_value=\"\" type=\"Bool\" urlType=\"\" val=\"False\" valid_values=\"\" />\r\n" +
                               "			<property name=\"enable setup teardown exit\" booleanType=\"TrueFalse\" branch=\"No\" hint=\"Setting for enabling or disabling exit before and after case execution. If not enabled, test cases will give warning and No result will be given\" mandatory=\"True\" max_value=\"\" min_value=\"\" type=\"Bool\" urlType=\"\" val=\"True\" valid_values=\"\"/>\r\n" +
                               "			<property name=\"tracing enabled\" booleanType=\"TrueFalse\" branch=\"No\" hint=\"Setting for enabling or disabling tracing\" mandatory=\"True\" max_value=\"\" min_value=\"\" type=\"Bool\" urlType=\"\" val=\"False\" valid_values=\"\"/>\r\n" +
                               "	  		<property name=\"memory leak testing enabled\" booleanType=\"TrueFalse\" branch=\"No\" hint=\"Setting for enabling or disabling memory leak analysis\" mandatory=\"False\" max_value=\"\" min_value=\"\" type=\"Bool\" urlType=\"\" val=\"False\" valid_values=\"\" />\r\n" +
                               "			<property name=\"delete success blx\" booleanType=\"TrueFalse\" branch=\"No\" hint=\"enable deletion of succesful testcase result blx\" mandatory=\"False\" max_value=\"\" min_value=\"\" type=\"Bool\" urlType=\"\" val=\"False\" valid_values=\"\" />\r\n" +
                               "			<property name=\"trace xml-file path\" booleanType=\"TrueFalse\" branch=\"No\" hint=\"Xml-file for enabling phone traces\" mandatory=\"False\" max_value=\"\" min_value=\"\" type=\"Str\" urlType=\"\" val=\"\" valid_values=\"\"/>\r\n" +
                               "		</property>\r\n" +
                               "	</property>\r\n" +
                               "</configuration>\r\n");
                }
                using (var file = File.CreateText(Path.Combine(settingsDirectoryPath, "invalid.py")))
                {
                    file.WriteLine("import clr;");
                    file.WriteLine("class Invalid /*&£ $ Class Name!(object) :");
                    file.WriteLine("    DisplayName = 'Nokia account username'");
                    file.WriteLine("    Category = 'Account settings'");
                    file.WriteLine("    DefaultValue = ''");
                }
                using (var file = File.CreateText(Path.Combine(settingsDirectoryPath, "invalid.json")))
                {
                    file.WriteLine("{\"nameWithMissingQuote:\"899889\",\"messages\":[\"msg 1\",\"msg 2\"],\"ega\":100}");
                }

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 0;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has no valid settings files so there should be no setting modules.");
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
        /// A test for LoadSettingsFromDirectory using a directory that does not exist.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromDirectoryDoesNotExistTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

            // Construct a directory path for the settings
            string settingsDirectoryPath = Path.Combine(Path.GetTempPath(), Path.GetFileNameWithoutExtension(Path.GetRandomFileName()));

            if (Directory.Exists(settingsDirectoryPath))
            {
                // Delete the entire directory if it already exists
                Directory.Delete(settingsDirectoryPath, true);
            }

            // Load settings from the directory that does not exist
            SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

            int expected = 0;
            Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory does not exist so there should be no setting modules.");
        }

        /// <summary>
        /// A test for LoadSettingsFromFile using a file that does not exist.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromFileDoesNotExistTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

            // Construct a directory path for the settings
            string settingsDirectoryPath = Path.Combine(Path.GetTempPath(), Path.GetFileNameWithoutExtension(Path.GetRandomFileName()));

            if (Directory.Exists(settingsDirectoryPath))
            {
                // Delete the entire directory if it already exists
                Directory.Delete(settingsDirectoryPath, true);
            }

            string settingsFilePath = Path.Combine(settingsDirectoryPath, "MySettingsFileThatDoesNotExist.xml");

            // Load settings from a file that does not exist
            SettingsManager.Instance.LoadSettingsFromFile(settingsFilePath);

            int expected = 0;
            Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory does not exist so there should be no setting modules.");

            // Create a new directory for this test
            Directory.CreateDirectory(settingsDirectoryPath);

            try
            {
                // Load settings from a file that does not exist but the directory does exist
                SettingsManager.Instance.LoadSettingsFromFile(settingsFilePath);

                expected = 0;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory exists but the settings file does not exist so there should be no setting modules.");
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
        /// A test for LoadSettingsFromDirectory using an XML settings file.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromDirectoryWithXmlSettingsFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");
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
        /// A test for LoadSettingsFromDirectory using an IronPython settings file.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromDirectoryWithIronPythonSettingsFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.ModemSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the IronPython settings file.");
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
        /// A test for LoadSettingsFromDirectory using the same IronPython settings file name in two directories.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromDirectoriesWithSameIronPythonSettingFileNameTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

            // Construct a directory path for the settings
            string firstSettingsDirectoryPath = Path.Combine(Path.GetTempPath(), Path.GetFileNameWithoutExtension(Path.GetRandomFileName()));

            if (Directory.Exists(firstSettingsDirectoryPath))
            {
                // Delete the entire directory if it already exists
                Directory.Delete(firstSettingsDirectoryPath, true);
            }

            // Create a new directory for this test
            Directory.CreateDirectory(firstSettingsDirectoryPath);

            // Construct a directory path for the settings
            string secondSettingsDirectoryPath = Path.Combine(Path.GetTempPath(), Path.GetFileNameWithoutExtension(Path.GetRandomFileName()));

            if (Directory.Exists(secondSettingsDirectoryPath))
            {
                // Delete the entire directory if it already exists
                Directory.Delete(secondSettingsDirectoryPath, true);
            }

            // Create a new directory for this test
            Directory.CreateDirectory(secondSettingsDirectoryPath);

            try
            {
                string fileName = "ModemSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(firstSettingsDirectoryPath, fileName));

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(secondSettingsDirectoryPath, fileName));

                string overrideFileName = "ModemSettings.xml";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideFileName, Path.Combine(secondSettingsDirectoryPath, overrideFileName));

                // Load settings from the first directory
                SettingsManager.Instance.LoadSettingsFromDirectory(firstSettingsDirectoryPath);

                // Load settings from the second directory
                SettingsManager.Instance.LoadSettingsFromDirectory(secondSettingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.ModemSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the IronPython settings file.");
            }

            finally
            {
                if (Directory.Exists(firstSettingsDirectoryPath))
                {
                    // Clean up by deleting the entire directory 
                    Directory.Delete(firstSettingsDirectoryPath, true);
                }

                if (Directory.Exists(secondSettingsDirectoryPath))
                {
                    // Clean up by deleting the entire directory 
                    Directory.Delete(secondSettingsDirectoryPath, true);
                }
            }
        }

        /// <summary>
        /// A test for LoadSettingsFromDirectory using an IronPython settings file and an XML file containing overrides.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromDirectoryWithIronPythonSettingsAndOverrideFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                string overrideFileName = "ModemSettings.xml";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideFileName, Path.Combine(settingsDirectoryPath, overrideFileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+358050505094594599";
                Assert.AreEqual(expectedPhoneNumberValue, settings.ModemSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML override file for the IronPython settings file.");
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
        /// A test for LoadSettingsFromDirectory using an IronPython settings file and an XML file containing overrides
        /// with empty string values.
        /// </summary>
        [TestMethod()]
        public void IronPythonSettingsAndOverrideFileContainingEmptyStringValuesTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string fileName = "DefaultSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                string overrideFileName = "DefaultSettings.xml";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideFileName, Path.Combine(settingsDirectoryPath, overrideFileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                expected = 40;
                Assert.AreEqual(expected, settings.DefaultSettings.PhoneReset, "Expected the phone reset setting value to match that specified in the XML override file (which also contains settings with empty string values) for the IronPython settings file.");

                // Verify we can access a single dictionary setting value that is empty
                string expectedDictionaryValue = string.Empty;
                Assert.AreEqual(expectedDictionaryValue, settings.DefaultSettings.DictionarySetting.Root.Child.EmptyChild, "Expected the dictionary to contain an empty child element.");
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
        /// A test for LoadSettingsFromDirectory using an IronPython settings file and an older XML file containing overrides.
        /// </summary>
        [TestMethod()]
        public void IronPythonSettingsAndOldOverrideFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string overrideFileName = "DefaultSettings.xml";
                string overrideFilePath = Path.Combine(settingsDirectoryPath, overrideFileName);

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideFileName, overrideFilePath);

                // Wait a while
                Thread.Sleep(2000);

                string fileName = "DefaultSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                expected = 40;
                Assert.AreEqual(expected, settings.DefaultSettings.PhoneReset, "Expected the phone reset setting value to match that specified in the older override file rather than the new IronPython file since we should preserve user's settings.");

                Assert.IsTrue(File.Exists(overrideFilePath), "Expected the '" + overrideFilePath + "' file to not be deleted since we should preserve user's settings.");
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
        /// A test for LoadSettingsFromDirectory using an IronPython settings file and an XML file with a missing setting.
        /// </summary>
        [TestMethod()]
        public void IronPythonSettingsAndOverrideFileWithMissingSettingTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string fileName = "DefaultSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                string overrideInvalidFileName = "DefaultSettingsWithMissingSetting.xml";
                string overrideFilePath = Path.Combine(settingsDirectoryPath, "DefaultSettings.xml");

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideInvalidFileName, overrideFilePath);

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                expected = 40;
                Assert.AreEqual(expected, settings.DefaultSettings.PhoneReset, "Expected the phone reset setting value to match the XML override file even though it contains an additional element, since we will try and preserve any user's changes.");

                Assert.IsTrue(File.Exists(overrideFilePath), "Expected the '" + overrideFilePath + "' file to not be deleted since we will try and preserve any user's changes even if the number of elements in the XML file does not match.");
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
        /// A test for LoadSettingsFromDirectory using an IronPython settings file and an XML file with a setting value that is of a 
        /// different type.
        /// </summary>
        [TestMethod()]
        public void IronPythonSettingsAndOverrideFileWithDifferentValueTypeTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string fileName = "DefaultSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                string overrideInvalidFileName = "DefaultSettingsWithDifferentValueType.xml";
                string overrideFilePath = Path.Combine(settingsDirectoryPath, "DefaultSettings.xml");

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideInvalidFileName, overrideFilePath);

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                expected = 55;
                Assert.AreEqual(expected, settings.DefaultSettings.PhoneReset, "Expected the phone reset setting value to match the XML override file even though it contains an element with a different value type, since we will try and preserve any user's changes.");

                Assert.IsTrue(File.Exists(overrideFilePath), "Expected the '" + overrideFilePath + "' file to not be deleted since we will try and preserve any user's changes even if the an element has a different value type in the XML file.");

                string expectedTextValue = "MOTU Analog 5";
                Assert.AreEqual(expectedTextValue, settings.DefaultSettings.Earpiece, "Expected the earpiece setting value to match the original value in the IronPython setting file, since the value in the XML override file is not of the correct type and therefore should not be used.");
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
        /// A test for LoadSettingsFromDirectory using an IronPython settings file and an XML file with invalid XML.
        /// </summary>
        [TestMethod()]
        public void IronPythonSettingsAndInvalidOverrideFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string fileName = "DefaultSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                string overrideInvalidFileName = "DefaultSettingsInvalid.xml";
                string overrideFilePath = Path.Combine(settingsDirectoryPath, "DefaultSettings.xml");

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideInvalidFileName, overrideFilePath);

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                expected = 30;
                Assert.AreEqual(expected, settings.DefaultSettings.PhoneReset, "Expected the phone reset setting value to match that in the IronPython settings file since the XML override file contains invalid XML.");

                Assert.IsTrue(File.Exists(overrideFilePath), "Expected the '" + overrideFilePath + "' file to not be deleted since we will try and preserve any user's changes even if we cannot successfully read the file.");
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
        /// A test for LoadSettingsFromDirectory using an IronPython settings file and an XML file with an additional setting.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromDirectoryWithIronPythonSettingsAndOverrideFileWithAdditionalSettingTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string fileName = "DefaultSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                string overrideInvalidFileName = "DefaultSettingsWithAdditionalSetting.xml";
                string overrideFilePath = Path.Combine(settingsDirectoryPath, "DefaultSettings.xml");

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideInvalidFileName, overrideFilePath);

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                expected = 45;
                Assert.AreEqual(expected, settings.DefaultSettings.PhoneReset, "Expected the phone reset setting value to match the XML override file even though it contains an additional element, since we will try and preserve any user's changes.");

                Assert.IsTrue(File.Exists(overrideFilePath), "Expected the '" + overrideFilePath + "' file to not be deleted since we will try and preserve any user's changes even if the number of elements in the XML file does not match.");
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
        /// A test for LoadSettingsFromDirectory using a JSON settings file.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromDirectoryWithJsonSettingsFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedValue = "899889";
                Assert.AreEqual(expectedValue, settings.SettingsInJsonFormat.name, "Expected the name setting value to match that specified in the JSON settings file.");
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
        /// A test for calling LoadSettingsFromDirectory multiple times, referring to the same directory using an XML settings file.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromSameDirectoryTwiceTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                // Load settings from the directory again
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");
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
        /// A test for LoadSettingsFromFile using an XML settings file.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromFileWithXmlSettingsFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the file
                SettingsManager.Instance.LoadSettingsFromFile(Path.Combine(settingsDirectoryPath, fileName));

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");
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
        /// A test for LoadSettingsFromFile using an IronPython settings file.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromFileWithIronPythonSettingsFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the file
                SettingsManager.Instance.LoadSettingsFromFile(Path.Combine(settingsDirectoryPath, fileName));

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.ModemSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the IronPython settings file.");

                fileName = "EntertainmentSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the file
                SettingsManager.Instance.LoadSettingsFromFile(Path.Combine(settingsDirectoryPath, fileName));

                expected = 2;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "Two settings file have been added so there should be two setting modules.");

                settings = SettingsManager.Instance;
                int expectedValue = 16;
                Assert.AreEqual(expectedValue, settings.EntertainmentSettings.DictionarySetting.Granma.Child.GrandChild, "Expected the entertainment setting value to match that specified in the IronPython settings file.");
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
        /// A test for LoadSettingsFromFile using a JSON settings file.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromFileWithJsonSettingsFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the file
                SettingsManager.Instance.LoadSettingsFromFile(Path.Combine(settingsDirectoryPath, fileName));

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedValue = "899889";
                Assert.AreEqual(expectedValue, settings.SettingsInJsonFormat.name, "Expected the name setting value to match that specified in the JSON settings file.");
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
        /// A test for LoadSettingsFromFile using an IronPython settings file and an XML file containing overrides.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromFileWithIronPythonSettingsAndOverrideFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                string overrideFileName = "ModemSettings.xml";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideFileName, Path.Combine(settingsDirectoryPath, overrideFileName));

                // Load settings from the file
                SettingsManager.Instance.LoadSettingsFromFile(Path.Combine(settingsDirectoryPath, fileName));

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+358050505094594599";
                Assert.AreEqual(expectedPhoneNumberValue, settings.ModemSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML override file for the IronPython settings file.");
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
        /// A test for LoadSettingsFromFile using an IronPython settings file and an XML file containing overrides which is deleted.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromFileWithIronPythonSettingsAndOverrideFileDeletedTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                string overrideFileName = "ModemSettings.xml";
                string overrideFilePath = Path.Combine(settingsDirectoryPath, overrideFileName);

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideFileName, overrideFilePath);

                // Load settings from the file
                SettingsManager.Instance.LoadSettingsFromFile(Path.Combine(settingsDirectoryPath, fileName));

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+358050505094594599";
                Assert.AreEqual(expectedPhoneNumberValue, settings.ModemSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML override file for the IronPython settings file.");

                AutoResetEvent removedEventRaised = new AutoResetEvent(false);

                int numberTimesSettingModuleRemovedEventRaised = 0;

                SettingsManager.Instance.SettingModuleRemoved += (args) => { numberTimesSettingModuleRemovedEventRaised++; removedEventRaised.Set(); };

                // Delete the override XML file
                File.Delete(overrideFilePath);

                // Wait to see if a deleted setting module occurs (it should not)
                removedEventRaised.WaitOne(3000);

                expected = 0;
                Assert.AreEqual(expected, numberTimesSettingModuleRemovedEventRaised, "The XML settings file has been removed but the IronPython file is still there so the event that indicates a setting module has been removed should not have fired.");

                expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory still has one IronPython settings file so there should be one setting module.");

                expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.ModemSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the original IronPython file since the XML override file was deleted.");
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
        /// A test for LoadSettingsFromDirectory using IronPython.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromDirectoryUsingIronPythonTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Convert the file path so that it is in the format for IronPython
                string settingsDirectoryPathForIronPython = settingsDirectoryPath.Replace(@"\", @"\\");

                string expectedPhoneNumberValue = "+3580505050945945849";

                // Verify we can add the settings directory and access the setting from IronPython code
                string ironPythonCode = string.Format("import clr\r\n" +
                                                      "clr.AddReference('TestAutomation.Gui.Marble.Settings')\r\n" +
                                                      "from TestAutomation.Gui.Marble.Settings import SettingsManager\r\n" +
                                                      "assert SettingsManager.Instance.Count == 0, 'Expected to get the Count property on the SettingsManager instance and for it to be set to 0.'\r\n" +
                                                      "SettingsManager.Instance.LoadSettingsFromDirectory('{0}')\r\n" +
                                                      "assert SettingsManager.Instance.Count == 1, 'The settings directory has one settings file so there should be one setting module.'\r\n" +
                                                      "assert SettingsManager.Instance.MySettings.PhoneNumber == '{1}', 'Expected the phone number setting value to match that specified in the XML settings file.'\r\n", 
                                                      settingsDirectoryPathForIronPython, expectedPhoneNumberValue);
                Python.CreateEngine().Execute(ironPythonCode);
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
        /// A test where we call LoadSettingsFromDirectory twice and want to verify we do not create duplicate SettingModules.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromSameDirectoryWithXmlSettingsFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");

                // Load settings from the same directory again
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory which we have added twice only has one settings file so there should be one setting module.");

                expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");
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
        /// A test for LoadSettingsFromDirectory using recursive search.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromDirectoryUsingRecursiveSearchTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Construct a sub-directory path for the settings
                string settingsSubDirectoryPath = Path.Combine(settingsDirectoryPath, Path.GetFileNameWithoutExtension(Path.GetRandomFileName()));

                // Create a new sub-directory for this test
                Directory.CreateDirectory(settingsSubDirectoryPath);

                fileName = "ModemSettings.py";

                // Create the settings file in the sub-directory
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsSubDirectoryPath, fileName));

                // Load settings from the directory do a recursive search
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath, true);

                int expected = 2;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file in the root directory and another one in a sub-directory so there should be two setting modules.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");

                expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.ModemSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the IronPython settings file.");

                // Reset the settings manager
                SettingsManager.Instance.Reset();
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
        /// A test to change an XML setting.
        /// </summary>
        [TestMethod()]
        public void ChangeXmlSettingsTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");

                // Change the setting
                expectedPhoneNumberValue = "+3580505050945945849";
                settings.MySettings.PhoneNumber = "+44123456790";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "In the current implementation, expected the phone number setting value to remain unchanged even after an attempt is made to change it. Changes are currently only allowed via the GUI or editing the settings file.");
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
        /// A test to change an IronPython setting from a child AppDomain.
        /// </summary>
        [TestMethod()]
        public void ChangeIronPythonSettingsFromChildAppDomainTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedValue = "This is a Nokia test message from Marble";
                Assert.AreEqual(expectedValue, settings.ModemSettings.SmsText, "Expected the SMS text value to match that specified in the IronPython settings file.");

                if (AppDomain.CurrentDomain.IsDefaultAppDomain())
                {
                    Assert.Inconclusive("Unable to run this unit test since the unit test is running in the default application domain. Expected it to run in a child application domain be default.");
                }

                // Turn off the unit testing flag so we can run this test without being in the main application domain
                SettingsManager.Instance.UnitTesting = false;

                // Change the setting
                expectedValue = "This is a Nokia test message from Marble";
                settings.ModemSettings.SmsText = "This is a Nokia test message from Marble that has been changed";
                Assert.AreEqual(expectedValue, settings.ModemSettings.SmsText, "In the current implementation, expected the SMS text value to remain unchanged from a child application domain even after an attempt is made to change it. Changes are currently only allowed via the GUI or editing the settings file.");
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
        /// A test for LoadSettingsFromDirectory using an XML settings file that is renamed.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromDirectoryAndRenameSettingsFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");

                AutoResetEvent renamedEventRaised = new AutoResetEvent(false);
                int numberTimesSettingModuleRenamedEventRaised = 0;

                SettingsManager.Instance.SettingModuleRenamed += (args) => { numberTimesSettingModuleRenamedEventRaised++; renamedEventRaised.Set(); };

                // Rename the settings file
                string newFileName = "MyNewSettings.xml";
                File.Move(Path.Combine(settingsDirectoryPath, fileName), Path.Combine(settingsDirectoryPath, newFileName));

                // Wait for the renamed file to be processed
                renamedEventRaised.WaitOne(5000);

                expected = 1;
                Assert.AreEqual(expected, numberTimesSettingModuleRenamedEventRaised, "A settings file has been renamed so the event that indicates a setting module has been renamed should have fired once.");

                expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                // Verify we can access the setting using the renamed setting module
                expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MyNewSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file and the session module to have changed names since the setting file name has been renamed.");

                // Verify we can no longer access the old setting module name
                Assert.IsNull(settings.MySettings, "Expected a the setting module to be null when trying to access the old setting module after the setting file has been renamed.");
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
        /// A test for SaveAll after renaming and then deleting an XML settings file.
        /// </summary>
        [TestMethod()]
        public void SaveAllAfterRenameAndDeleteSettingsFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");

                AutoResetEvent renamedEventRaised = new AutoResetEvent(false);
                AutoResetEvent removedEventRaised = new AutoResetEvent(false);
                int numberTimesSettingModuleRenamedEventRaised = 0;
                int numberTimesSettingModuleRemovedEventRaised = 0;

                SettingsManager.Instance.SettingModuleRenamed += (args) => { numberTimesSettingModuleRenamedEventRaised++; renamedEventRaised.Set(); };
                SettingsManager.Instance.SettingModuleRemoved += (args) => { numberTimesSettingModuleRemovedEventRaised++; removedEventRaised.Set(); };

                // Rename the settings file
                string newFileName = "MyNewSettings.xml";
                string newFilePath = Path.Combine(settingsDirectoryPath, newFileName); 
                File.Move(filePath, newFilePath);

                // Wait for the renamed file to be processed
                renamedEventRaised.WaitOne(5000);

                expected = 1;
                Assert.AreEqual(expected, numberTimesSettingModuleRenamedEventRaised, "A settings file has been renamed so the event that indicates a setting module has been renamed should have fired once.");

                expected = 0;
                Assert.AreEqual(expected, numberTimesSettingModuleRemovedEventRaised, "A settings file has been renamed, but we do not expect an event that the setting file has been removed.");

                expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                // Verify we can access the setting using the renamed setting module
                expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MyNewSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file and the session module to have changed names since the setting file name has been renamed.");

                // Verify we can no longer access the old setting module name
                Assert.IsNull(settings.MySettings, "Expected a the setting module to be null when trying to access the old setting module after the setting file has been renamed.");

                // Delete the settings file
                File.Delete(newFilePath);

                // Wait for the deleted file to be processed
                removedEventRaised.WaitOne(5000);

                expected = 1;
                Assert.AreEqual(expected, numberTimesSettingModuleRemovedEventRaised, "A settings file has been renamed and then deleted so the event that indicates a setting module has been removed should have fired once.");

                expected = 0;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has no settings file so there should not be any setting modules.");

                // Save all settings
                SettingsManager.Instance.SaveAll();

                // Wait a while
                Thread.Sleep(1500);

                Assert.IsFalse(File.Exists(filePath), "The original settings file should not exist since it was renamed and then we saved all settings.");
                Assert.IsFalse(File.Exists(newFilePath), "The new settings file should not exist since it was deleted and then we saved all settings.");
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
        /// A test to save an XML settings file with some changes that have been made.
        /// </summary>
        [TestMethod()]
        public void SaveXmlSettingsFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");

                // Change the setting
                expectedPhoneNumberValue = "+3580505050945945849"; 
                settings.MySettings.PhoneNumber = "+44123456790";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "In the current implementation, expected the phone number setting value to remain unchanged even after an attempt is made to change it. Changes are currently only allowed via the GUI or editing the settings file.");

                // Save all of the settings
                SettingsManager.Instance.SaveAll();

                // Verify the setting value is still unchanged
                expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to remain unchanged after saving the settings.");

                // Reset the settings manager for this test
                SettingsManager.Instance.Reset();

                // Set the unit testing flag so we can run this test as though we were running from the main application domain
                SettingsManager.Instance.UnitTesting = true;

                expected = 0;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "There should be no setting modules after we have done a reset.");

                // Load settings from the directory again
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module after we have saved and loaded again.");

                // Verify the setting value is still unchanged
                expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to remain unchanged after saving the settings and loading them again.");
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
        /// A test to save an XML settings file with some changes and verify that the settings file can be loaded again afterwards.
        /// </summary>
        [TestMethod()]
        public void SavingAndLoadingXmlSettingsFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");

                // Change the setting
                expectedPhoneNumberValue = "+3580505050945945849";
                settings.MySettings.PhoneNumber = "+44123456790";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "In the current implementation, expected the phone number setting value to remain unchanged even after an attempt is made to change it. Changes are currently only allowed via the GUI or editing the settings file.");

                // Save all of the settings
                SettingsManager.Instance.SaveAll();

                // Verify the setting value is still unchanged
                expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to remain unchanged after saving the settings.");

                // Reset the settings manager for this test
                SettingsManager.Instance.Reset();

                // Set the unit testing flag so we can run this test as though we were running from the main application domain
                SettingsManager.Instance.UnitTesting = true;

                expected = 0;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "There should be no setting modules after we have done a reset.");

                // Load settings from the directory again
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module after we have saved and loaded again.");

                // Verify the setting value is still unchanged
                expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to remain unchanged after saving the settings and loading them again.");
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
        /// A test for SettingModuleAdded event.
        /// </summary>
        [TestMethod()]
        public void SettingModuleAddedEventTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                AutoResetEvent addedEventRaised = new AutoResetEvent(false);

                int numberTimesSettingModuleAddedEventRaised = 0;

                SettingsManager.Instance.SettingModuleAdded += (args) => { numberTimesSettingModuleAddedEventRaised++; addedEventRaised.Set(); };

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                // Wait a while
                Thread.Sleep(1000);

                int expected = 0;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has no settings file so there should not be any setting modules.");

                string fileName = "MySettings.xml";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Wait for the new file to be identified
                addedEventRaised.WaitOne(60000);

                expected = 1;
                Assert.AreEqual(expected, numberTimesSettingModuleAddedEventRaised, "A settings file has been added so the event that indicates a setting module has been added should have fired once.");

                expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");

                // Reset the settings manager
                SettingsManager.Instance.Reset();
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
        /// A test for SettingValueChanged event using an IronPython settings file and an XML file that is later created containing overrides.
        /// </summary>
        [TestMethod()]
        public void SettingValueChangedUsingIronPythonSettingsAndOverrideFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                AutoResetEvent settingChangedEventRaised = new AutoResetEvent(false);

                int numberTimesSettingChangedEventRaised = 0;

                SettingsManager.Instance.SettingValueChanged += (args) => 
                {
                    Console.WriteLine(args.SettingName + " has changed from " + args.OldValue + " to " + args.NewValue);
                    numberTimesSettingChangedEventRaised++; 
                    settingChangedEventRaised.Set(); 
                };

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                // Wait a while
                Thread.Sleep(1500);

                string overrideFileName = "ModemSettings.xml";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideFileName, Path.Combine(settingsDirectoryPath, overrideFileName));

                // Wait a while for the change events
                Thread.Sleep(5000);

                // Wait for at least one change event to occur
                settingChangedEventRaised.WaitOne(20000);

                expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "There is still one IronPython settings file and an XML file with overrides, so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+358050505094594599";
                Assert.AreEqual(expectedPhoneNumberValue, settings.ModemSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML override file for the IronPython settings file.");

                // Reset the settings manager after this test
                SettingsManager.Instance.Reset();
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
        /// A test for SettingModuleRemoved event when the settings file is deleted.
        /// </summary>
        [TestMethod()]
        public void SettingModuleRemovedEventWhenFileDeletedTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                AutoResetEvent removedEventRaised = new AutoResetEvent(false);

                int numberTimesSettingModuleRemovedEventRaised = 0;

                SettingsManager.Instance.SettingModuleRemoved += (args) => { numberTimesSettingModuleRemovedEventRaised++; removedEventRaised.Set(); };

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");

                // Delete the settings file
                File.Delete(Path.Combine(settingsDirectoryPath, fileName));

                // Wait for the deleted file to be identified
                removedEventRaised.WaitOne(20000);

                expected = 1;
                Assert.AreEqual(expected, numberTimesSettingModuleRemovedEventRaised, "A settings file has been removed so the event that indicates a setting module has been removed should have fired once.");

                expected = 0;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory had one settings file that was deleted so there should be no setting modules.");
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
        /// A test that SaveAll does not create any settings files if all settings files were deleted beforehand.
        /// </summary>
        [TestMethod()]
        public void SaveAllAfterDeletingSettingFilesCreatesNoFilesTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                AutoResetEvent removedEventRaised = new AutoResetEvent(false);

                int numberTimesSettingModuleRemovedEventRaised = 0;

                SettingsManager.Instance.SettingModuleRemoved += (args) => { numberTimesSettingModuleRemovedEventRaised++; removedEventRaised.Set(); };

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");

                // Delete the settings file
                File.Delete(Path.Combine(settingsDirectoryPath, fileName));

                // Wait for the deleted file to be identified
                removedEventRaised.WaitOne(20000);

                expected = 1;
                Assert.AreEqual(expected, numberTimesSettingModuleRemovedEventRaised, "A settings file has been removed so the event that indicates a setting module has been added should only have fired once.");

                expected = 0;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory had one settings file that was deleted so there should be no setting modules.");

                expected = 0;
                string[] files = Directory.GetFiles(settingsDirectoryPath);
                if (expected != files.Length)
                {
                    Assert.Inconclusive("Cannot perform this test since there should be no files in this directory if we deleted the only file that was created.");
                }

                // Save all setting files
                SettingsManager.Instance.SaveAll();

                expected = 0;
                files = Directory.GetFiles(settingsDirectoryPath);
                Assert.AreEqual(expected, files.Length, "Saving all settings files should not create any files if we originally deleted all setting files, causing all setting modules to be removed beforehand.");
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
        /// A test for SettingModuleRemoved event when the directory is deleted.
        /// </summary>
        [TestMethod()]
        public void SettingModuleRemovedEventWhenDirectoryDeletedTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                AutoResetEvent removedEventRaised = new AutoResetEvent(false);

                int numberTimesSettingModuleRemovedEventRaised = 0;

                SettingsManager.Instance.SettingModuleRemoved += (args) => { numberTimesSettingModuleRemovedEventRaised++; removedEventRaised.Set(); };

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");

                try
                {
                    // Delete the entire directory
                    Directory.Delete(settingsDirectoryPath, true);
                }

                catch (Exception ex)
                {
                    Assert.Inconclusive("Cannot delete the directory with the settings file therefore we cannot run this test: " + ex.Message);
                }

                // Wait for the deleted file to be identified
                removedEventRaised.WaitOne(20000);

                expected = 1;
                Assert.AreEqual(expected, numberTimesSettingModuleRemovedEventRaised, "A settings file has been removed so the event that indicates a setting module has been added should only have fired once.");

                expected = 0;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory had one settings file and the directory was deleted so there should be no setting modules.");
            }

            finally
            {
                // Reset the settings manager
                SettingsManager.Instance.Reset();

                if (Directory.Exists(settingsDirectoryPath))
                {
                    // Clean up by deleting the entire directory 
                    Directory.Delete(settingsDirectoryPath, true);
                }
            }
        }

        /// <summary>
        /// A test for SettingModuleRenamed event.
        /// </summary>
        [TestMethod()]
        public void SettingModuleRenamedEventTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                AutoResetEvent renamedEventRaised = new AutoResetEvent(false);

                int numberTimesSettingModuleRenamedEventRaised = 0;

                SettingsManager.Instance.SettingModuleRenamed += (args) => { numberTimesSettingModuleRenamedEventRaised++; renamedEventRaised.Set(); };

                string fileName = "MySettings.xml";
                string settingsFilePath = Path.Combine(settingsDirectoryPath, fileName);

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, settingsFilePath);

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file so there should be one setting module.");

                // Rename the file
                File.Move(settingsFilePath, Path.Combine(settingsDirectoryPath, "MySettings2.xml"));

                // Wait for the new file to be identified
                renamedEventRaised.WaitOne(20000);

                expected = 1;
                Assert.AreEqual(expected, numberTimesSettingModuleRenamedEventRaised, "A settings file has been renamed so the event that indicates a setting module has been added renamed should have fired once.");

                expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file that has been renamed so there should be one setting module.");

                // Verify we can get the setting value using the renamed setting module
                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+3580505050945945849";
                Assert.AreEqual(expectedPhoneNumberValue, settings.MySettings2.PhoneNumber, "Expected the phone number setting value to match that specified in the XML settings file.");

                // Verify the original setting module is not returned
                Assert.IsNull(settings.MySettings, "Expected the old setting module to no longer be available after the setting file was renamed.");

                Assert.IsNotNull(SettingsManager.Instance.GetSettings("MySettings2"), "Expected to be able to get the settings module using the new name.");
                Assert.IsNull(SettingsManager.Instance.GetSettings("MySettings"), "Expected not to be able to get the settings module using the old name.");
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
        ///A test for Count
        ///</summary>
        [TestMethod()]
        public void CountTest()
        {
            int expected = 0;
            int actual = SettingsManager.Instance.Count;
            Assert.AreEqual(expected, actual, "Expected the settings manager to initially not contain any setting modules.");
        }

        /// <summary>
        ///A test for GetSettings
        ///</summary>
        [TestMethod()]
        public void GetSettingsTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string settingsFilePath = Path.Combine(settingsDirectoryPath, fileName);

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, settingsFilePath);

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                Assert.IsNotNull(SettingsManager.Instance.GetSettings("MySettings"), "Expected to be able to get the settings module using the name.");
                Assert.IsNull(SettingsManager.Instance.GetSettings("DoesNotExist"), "Expected not to be able to get the settings module using a name that does not exist.");
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
        ///A test for Item
        ///</summary>
        [TestMethod()]
        public void ItemTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                Assert.IsNotNull(SettingsManager.Instance["MySettings"], "Expected to be able to get the item using the name.");
                Assert.IsNull(SettingsManager.Instance["DoesNotExist"], "Expected not to be able to get the item using a name that does not exist.");
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
        ///A test for SaveAll
        ///</summary>
        [TestMethod()]
        public void SaveAllTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                fileName = "SettingsInJsonFormat.json";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                fileName = "ModemSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 3;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has three settings file so there should be three setting modules.");

                // Save all of the settings
                SettingsManager.Instance.SaveAll();

                // Reset the settings manager for this test
                SettingsManager.Instance.Reset();

                // Set the unit testing flag so we can run this test as though we were running from the main application domain
                SettingsManager.Instance.UnitTesting = true;

                // Load settings from the directory to load the saved files
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                expected = 3;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has three settings file that were saved so there should be three setting modules.");
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
        ///A test for concurrent BeginLoadSettingsFromDirectory and LoadSettingsFromDirectory followed by concurrently getting a setting value.
        ///</summary>
        [TestMethod()]
        public void ConcurrentLoadSettingsFromDirectoryAndGetSettingValueTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string[] fileNames = new string[] { "MySettings.xml", "SettingsInJsonFormat.json", "ModemSettings.py", "ModemSettings.xml", "EntertainmentSettings.py" };

                foreach (string fileName in fileNames)
                {
                    // Create the settings file
                    UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));
                }

                // Start an asynchronous and asynchronous load from different threads
                System.Threading.Tasks.Parallel.For(0, 10, t =>
                    {
                        if (t < 5)
                        {
                            SettingsManager.Instance.BeginLoadSettingsFromDirectory(settingsDirectoryPath);
                        }
                        else
                        {
                            SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);
                        }
                    });

                // Wait a while for the loading to complete
                Thread.Sleep(3000);

                int expected = 4;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has four settings file that were saved so there should be four setting modules.");

                // Attempt to get a setting from different threads
                System.Threading.Tasks.Parallel.For(0, 10, t=> 
                    {
                        dynamic settings = SettingsManager.Instance;
                        string expectedPhoneNumberValue = "+358050505094594599";
                        Assert.AreEqual(expectedPhoneNumberValue, settings.ModemSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the IronPython settings file.");
                    });

                // Allow updated to be made
                SettingsManager.Instance.ReadOnly = false;

                // Read and update the same setting concurrently
                System.Threading.Tasks.Parallel.For(0, 10, t =>
                {
                    if (t % 2 == 0)
                    {
                        dynamic settings = SettingsManager.Instance;
                        Assert.IsNotNull(settings.ModemSettings.PhoneNumber, "Expected the phone number setting value not to be null.");
                        Assert.IsFalse(string.IsNullOrEmpty(settings.ModemSettings.PhoneNumber), "Expected the phone number setting value not to be empty.");
                    }
                    else
                    {
                        dynamic settings = SettingsManager.Instance;
                        settings.ModemSettings.PhoneNumber = "+358050505094594599" + t.ToString();
                        Assert.IsNotNull(settings.ModemSettings.PhoneNumber, "Expected the phone number setting value not to be null.");
                        Assert.IsFalse(string.IsNullOrEmpty(settings.ModemSettings.PhoneNumber), "Expected the phone number setting value not to be empty.");
                    }
                });

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
        ///A test for BeginSaveAll
        ///</summary>
        [TestMethod()]
        public void BeginSaveAllTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                fileName = "SettingsInJsonFormat.json";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                fileName = "ModemSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 3;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has three settings file so there should be three setting modules.");

                // Asynchronously save all of the settings
                SettingsManager.Instance.BeginSaveAll();

                // Wait for the files to be saved
                Thread.Sleep(5000);

                // Reset the settings manager for this test
                SettingsManager.Instance.Reset();

                // Set the unit testing flag so we can run this test as though we were running from the main application domain
                SettingsManager.Instance.UnitTesting = true;

                // Load settings from the directory to load the saved files
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                expected = 3;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has three settings file that were saved so there should be three setting modules.");
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
        ///A test for BeginLoadSettingsFromDirectory
        ///</summary>
        [TestMethod()]
        public void BeginLoadSettingsFromDirectoryTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                fileName = "SettingsInJsonFormat.json";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                fileName = "ModemSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Asynchronously add settings from the directory
                SettingsManager.Instance.BeginLoadSettingsFromDirectory(settingsDirectoryPath);

                // Wait for the files to be added
                Thread.Sleep(5000);

                int expected = 3;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has three settings file so there should be three setting modules.");
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
        ///A test for BeginLoadSettingsFromFile
        ///</summary>
        [TestMethod()]
        public void BeginLoadSettingsFromFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Asynchronously add settings from the file
                SettingsManager.Instance.BeginLoadSettingsFromFile(filePath);

                // Wait for the settings from the file to be added
                Thread.Sleep(2000);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file was added so there should be one setting module.");
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
        ///A test for SettingModules
        ///</summary>
        [TestMethod()]
        public void SettingModulesTest()
        {
            Assert.IsNotNull(SettingsManager.Instance.SettingModules, "Expected the setting modules property to return a setting module collection that is not null.");
        }

        /// <summary>
        ///A test for GetEnumerator
        ///</summary>
        [TestMethod()]
        public void GetEnumeratorTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                if (SettingsManager.Instance.Count != 1)
                {
                    Assert.Inconclusive("The settings file was added so there should be one setting module. If that has not happened we cannot run this test.");
                }

                IEnumerator enumerator = SettingsManager.Instance.GetEnumerator();
                Assert.IsNotNull(enumerator, "Expected the enumerator to return an enumerator that is not null.");
                bool expected = true;
                bool actual = enumerator.MoveNext();
                Assert.AreEqual(expected, actual, "Expected the enumerator to be able to move to the first element since we have read one setting file.");
                Assert.IsNotNull(enumerator.Current, "Expected the enumerator current element to not be null since we have read a setting file");

                expected = false;
                actual = enumerator.MoveNext();
                Assert.AreEqual(expected, actual, "Expected the enumerator to not be able to move to the next element since we have read only one setting file.");
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
        ///A test for to process all test scripts for settings test.
        ///</summary>
        ///<remarks>This is not a true unit test but is useful to get the performance when processing lots of IronPython files.</remarks>
        //[TestMethod()]
        public void ProcessAllTestScriptsForSettingsTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

            try
            {
                // The specified directory to use where the test scripts or framework files are located is user-specific.

                string settingsDirectoryPath = @"C:\Users\mfreed\My Code\Marble\GUI\MainGUI\bin\test_scripts";
                //string settingsDirectoryPath = @"C:\Users\mfreed\My Code\Marble\GUIRelease\MainGUI\bin\framework";

                if (!Directory.Exists(settingsDirectoryPath))
                {
                    Assert.Inconclusive(string.Format("The '{0}' directory does not exist therefore we cannot run the test to process all setting files.", settingsDirectoryPath));
                }

                bool includeSubdirectories = true;

                DateTime startTime = DateTime.Now;

                // Load settings from the directory and recursively search
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath, includeSubdirectories);

                TimeSpan duration = DateTime.Now - startTime;
                SearchOption searchOption = includeSubdirectories ? SearchOption.AllDirectories : SearchOption.TopDirectoryOnly;
                int numberOfFiles = Directory.GetFiles(settingsDirectoryPath, "*.py", searchOption).Length +
                                    Directory.GetFiles(settingsDirectoryPath, "*.xml", searchOption).Length +
                                    Directory.GetFiles(settingsDirectoryPath, "*.json", searchOption).Length;
                Console.WriteLine(string.Format("It took {0} seconds to process {1} files in the '{2}' directory.", duration.TotalSeconds, numberOfFiles, settingsDirectoryPath));

                int expected = 0;
                int actual = SettingsManager.Instance.Count;
                Assert.AreEqual(expected, actual, "Expected to find no settings files in the test scripts directory.");
            }

            finally
            {
                // Reset the settings manager after this test
                SettingsManager.Instance.Reset();
            }
        }

        /// <summary>
        /// A test for GetSettings using a string containing the full setting name path (e.g. 'MySettings/MySettingName').
        /// </summary>
        [TestMethod()]
        public void GetSettingsUsingSettingPathStringTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string fileName = "EntertainmentSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the file
                SettingsManager.Instance.LoadSettingsFromFile(Path.Combine(settingsDirectoryPath, fileName));

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                // Verify we can access a single setting value
                string settingPath = @"EntertainmentSettings/MP3FileToPlay";
                object objectValue = SettingsManager.Instance.GetSettings(settingPath);
                Assert.IsNotNull(objectValue, "Unable to get to '" + settingPath + "' setting value.");
                Assert.AreEqual(typeof(string), objectValue.GetType(), "Expected the '" + settingPath + "' setting value to be a string.");
                string expectedTextValue = @"c:\David Hasselhoff - Jump in my car.mp3";
                Assert.AreEqual(expectedTextValue, objectValue, "The '" + settingPath + "' setting value was not as expected.");

                // Verify we can access a single dictionary setting value
                settingPath = @"EntertainmentSettings/DictionarySetting";
                objectValue = SettingsManager.Instance.GetSettings(settingPath);
                Assert.IsNotNull(objectValue, "Unable to get to '" + settingPath + "' setting value.");
                Assert.AreEqual(typeof(DynamicDictionary<string, IDictionary>), objectValue.GetType(), "Expected the '" + settingPath + "' setting value to be a dynamic dictionary.");
                DynamicDictionary<string, IDictionary> dictionary = (DynamicDictionary<string, IDictionary>)objectValue;
                Assert.IsTrue(dictionary.ContainsKey("Granma"), "Expected the '" + settingPath + "' setting value to be a dynamic dictionary containing a 'Granma' key.");

                // Verify we can access a full dictionary setting value
                settingPath = @"EntertainmentSettings/DictionarySetting/Granma/Child/GrandChild";
                objectValue = SettingsManager.Instance.GetSettings(settingPath);
                Assert.IsNotNull(objectValue, "Unable to get to '" + settingPath + "' setting value.");
                Assert.AreEqual(typeof(int), objectValue.GetType(), "Expected the '" + settingPath + "' setting value to be an integer.");
                int expectedValue = 16;
                Assert.AreEqual(expectedValue, objectValue, "The '" + settingPath + "' setting value was not as expected.");

#if IMPLEMENTED_DISPLAY_NAME_AND_CATEGORY_SUPPORT_FOR_GETTING_SETTINGS
                
                // Verify we can access a property using a category
                settingPath = @"EntertainmentSettings/Musick/MP3FileToPlay";
                objectValue = SettingsManager.Instance.GetSettings(settingPath);
                Assert.IsNotNull(objectValue, "Unable to get to '" + settingPath + "' setting value.");
                Assert.AreEqual(typeof(string), objectValue.GetType(), "Expected the '" + settingPath + "' setting value to be a string.");
                expectedTextValue = @"c:\David Hasselhoff - Jump in my car.mp3";
                Assert.AreEqual(expectedTextValue, objectValue, "The '" + settingPath + "' setting value was not as expected.");

                // Verify we can access a property using a display name
                settingPath = @"EntertainmentSettings/MP3 File to be played";
                objectValue = SettingsManager.Instance.GetSettings(settingPath);
                Assert.IsNotNull(objectValue, "Unable to get to '" + settingPath + "' setting value.");
                Assert.AreEqual(typeof(string), objectValue.GetType(), "Expected the '" + settingPath + "' setting value to be a string.");
                expectedTextValue = @"c:\David Hasselhoff - Jump in my car.mp3";
                Assert.AreEqual(expectedTextValue, objectValue, "The '" + settingPath + "' setting value was not as expected.");

                // Verify we can access a property using a category and display name
                settingPath = @"EntertainmentSettings/Musick/MP3 File to be played";
                objectValue = SettingsManager.Instance.GetSettings(settingPath);
                Assert.IsNotNull(objectValue, "Unable to get to '" + settingPath + "' setting value.");
                Assert.AreEqual(typeof(string), objectValue.GetType(), "Expected the '" + settingPath + "' setting value to be a string.");
                expectedTextValue = @"c:\David Hasselhoff - Jump in my car.mp3";
                Assert.AreEqual(expectedTextValue, objectValue, "The '" + settingPath + "' setting value was not as expected.");
#endif
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
        /// A test for GetValue using a string containing the full setting name path (e.g. 'MySettings/MyCategory/MySettingDisplayName').
        /// </summary>
        [TestMethod()]
        public void GetValueTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string fileName = "EntertainmentSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the file
                SettingsManager.Instance.LoadSettingsFromFile(Path.Combine(settingsDirectoryPath, fileName));

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                // Verify we can access a property using a category and display name
                string settingPath = @"EntertainmentSettings/Musick/MP3 File to be played";
                object objectValue = SettingsManager.Instance.getValue(settingPath);
                Assert.IsNotNull(objectValue, "Unable to get to '" + settingPath + "' setting value.");
                Assert.AreEqual(typeof(string), objectValue.GetType(), "Expected the '" + settingPath + "' setting value to be a string.");
                string expectedTextValue = @"c:\David Hasselhoff - Jump in my car.mp3";
                Assert.AreEqual(expectedTextValue, objectValue, "The '" + settingPath + "' setting value was not as expected.");

                // Verify we can access a property using a category and setting name without a display name
                settingPath = @"EntertainmentSettings/Musick/AACFileToPlay";
                objectValue = SettingsManager.Instance.getValue(settingPath);
                Assert.IsNotNull(objectValue, "Unable to get to '" + settingPath + "' setting value.");
                Assert.AreEqual(typeof(string), objectValue.GetType(), "Expected the '" + settingPath + "' setting value to be a string.");
                expectedTextValue = @"c:\Nirvana - Smells Like Teen Spirit.aac";
                Assert.AreEqual(expectedTextValue, objectValue, "The '" + settingPath + "' setting value was not as expected.");

                // Verify we can access a property using a display name only
                settingPath = @"EntertainmentSettings/MP3 File to be played";
                objectValue = SettingsManager.Instance.getValue(settingPath);
                Assert.IsNotNull(objectValue, "Unable to get to '" + settingPath + "' setting value.");
                Assert.AreEqual(typeof(string), objectValue.GetType(), "Expected the '" + settingPath + "' setting value to be a string.");
                expectedTextValue = @"c:\David Hasselhoff - Jump in my car.mp3";
                Assert.AreEqual(expectedTextValue, objectValue, "The '" + settingPath + "' setting value was not as expected.");

                // Verify we can access a property using a name only
                settingPath = @"EntertainmentSettings/AACFileToPlay";
                objectValue = SettingsManager.Instance.getValue(settingPath);
                Assert.IsNotNull(objectValue, "Unable to get to '" + settingPath + "' setting value.");
                Assert.AreEqual(typeof(string), objectValue.GetType(), "Expected the '" + settingPath + "' setting value to be a string.");
                expectedTextValue = @"c:\Nirvana - Smells Like Teen Spirit.aac";
                Assert.AreEqual(expectedTextValue, objectValue, "The '" + settingPath + "' setting value was not as expected.");
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
        /// A test for GetSettings using a string containing an invalid full setting name path (e.g. 'MySettings/MySettingName/Invalid').
        /// </summary>
        [TestMethod()]
        public void GetSettingsUsingInvalidSettingPathStringTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string fileName = "EntertainmentSettings.py";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));

                // Load settings from the file
                SettingsManager.Instance.LoadSettingsFromFile(Path.Combine(settingsDirectoryPath, fileName));

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                // Verify no exceptions thrown when accessing an invalid setting path
                string settingPath = @"EntertainmentSettings/MP3FileToPlay/ThisIsInvalid";
                object objectValue = SettingsManager.Instance.GetSettings(settingPath);
                string expectedTextValue = @"c:\David Hasselhoff - Jump in my car.mp3";
                Assert.AreEqual(expectedTextValue, objectValue, "Although the '" + settingPath + "' contains some tokens at the end that are invalid we expected it to still return the correct setting value.");

                // Verify no exception thrown when accessing an invalid setting path for a dictionary
                settingPath = @"EntertainmentSettings/DictionarySetting/Granma/Child/GrandChild/ThisIsInvalid";
                objectValue = SettingsManager.Instance.GetSettings(settingPath);
                Assert.IsNull(objectValue, "Expected to not be able to get the '" + settingPath + "' setting value.");

                // Verify no exception thrown when accessing a completely invalid setting path
                settingPath = @"DoesNotExist/ThisIsInvalid";
                objectValue = SettingsManager.Instance.GetSettings(settingPath);
                Assert.IsNull(objectValue, "Expected to not be able to get the '" + settingPath + "' setting value.");
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
        /// A test that we can get each of the Marble settings as was originally specified in the default.settings and modified.settings file.
        /// </summary>
        [TestMethod()]
        public void BackwardsCompatibilityTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string[] fileNames = new string[] { "Accounts.py", "Main.py", "ReferencePhone.py", "Remote.py", "System.py", "TestRun.py" };

                foreach (string fileName in fileNames)
                {
                    // Create the settings file
                    UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));
                }

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                Assert.AreEqual(fileNames.Length, SettingsManager.Instance.Count, "The settings files have been saved and there should be a setting module for each file.");

                string[] settingNames = new string[] 
                {
                    "Accounts/nokia account username",
			        "Accounts/nokia account password",
			        "Accounts/facebook username",
			        "Accounts/facebook password",
			        "Accounts/google email username",
			        "Accounts/google email password",
			        "Accounts/nokia email username",
			        "Accounts/nokia email password",
			        "Accounts/other email username",
			        "Accounts/other email password",
			        "Accounts/twitter username",
			        "Accounts/twitter password",
			        "Accounts/vkontakte username",
			        "Accounts/vkontakte password",
			        "Accounts/windows email username",
			        "Accounts/windows email password",
			        "Accounts/yahoo email username",
			        "Accounts/yahoo email password",
                    "Main/Account/phone number",
                    "Main/Account/pin code",
                    "Main/Account/pin2 code",
                    "Main/Account/puk1 code",
                    "Main/Account/puk2 code",
                    "Main/Account/service number",
                    "Main/Account/voice mail number",
                    "Main/Account2/phone number",
                    "Main/Account2/pin code",
                    "Main/Account2/pin2 code",
                    "Main/Account2/puk1 code",
                    "Main/Account2/puk2 code",
                    "Main/Account2/service number",
                    "Main/Account2/voice mail number",
                    "Main/connection",
                    "Main/CorVA/AccessoryBoxConnected",
                    "Main/CorVA/AudioTestDataFolder",
                    "Main/CorVA/CorVAEnabled",
                    "Main/CorVA/DefaultAudioRecordingTime",
                    "Main/CorVA/DefaultActionOnFail",
                    "Main/CorVA/Framesize",
                    "Main/CorVA/MaxRecordTime",
                    "Main/CorVA/Mode",
                    "Main/CorVA/Noiselevel",
                    "Main/CorVA/ReferenceAudioPath",
                    "Main/CorVA/StartChannel",
                    "Main/CorVA/SavePassedRecordings",
                    "Main/CorVA/Threshold",
                    "Main/M3W/DefaultOutput",
                    "Main/M3W/BaseDirectoryInPhone",
                    "Main/M3W/LibrarySearchPath",
                    "Main/M3W/TestDataPathPC",
                    "Main/M3W/TestDataPathPhone",
                    "Main/M3W/DefaultActionOnFail",
                    "Main/M3W/DefaultOutput",
                    "Main/M3W/DefaultVolume",
                    "Main/M3W/UnloadLibrariesAfterTC",
                    "Main/pmd-file path",
                    "Main/trace connection",
                    "ReferencePhone/Account/phone number",
                    "ReferencePhone/connection",
                    "Remote/pmd-file path",
                    "Remote/connection",
                    "System/Message resending/resend count",
                    "System/Message resending/resend message in use",
                    "System/Message resending/timeout between tries",
                    "System/path for temp files",
                    "System/Port config/gui - fw protocol port",
                    "System/Timeouts/expect length",
                    "System/Timeouts/expect timeout",
                    "System/Timeouts/expect wait",
                    "System/Timeouts/phone reset",
                    "System/Timeouts/receive messages from",
                    "System/Timeouts/send and receive message",
                    "Test run/debug level",
                    "Test run/delete success blx",
                    "Test run/disable test case setup and teardown",
                    "Test run/enable blackbox",
                    "Test run/enable graybox",
                    "Test run/enable monkey testing",
                    "Test run/memory leak testing enabled",
                    "Test run/tracing enabled",
                    "Test run/trace xml-file path"
                };

                dynamic settings = SettingsManager.Instance;

                foreach (string name in settingNames)
                {
                    // Get the setting value
                    object settingValue = settings.getValue(name);

                    Assert.IsNotNull(settingValue, "The setting value for '" + name + "' is null. Expected to be able to get a value for each setting path.");
                }

                // Check some of the default values

                object expected = true;
                string settingPath = "Main/CorVA/CorVAEnabled";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = 10;
                settingPath = "Main/CorVA/Threshold";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = 3;
                settingPath = "Main/CorVA/Mode";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = 4000;
                settingPath = "Main/CorVA/Framesize";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = 0.01;
                settingPath = "Main/CorVA/Noiselevel";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = 10;
                settingPath = "Main/CorVA/DefaultAudioRecordingTime";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = "Fail case";
                settingPath = "Main/CorVA/DefaultActionOnFail";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = false;
                settingPath = "Main/CorVA/SavePassedRecordings";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = @"C:\marble_103\test_data";
                settingPath = "Main/M3W/TestDataPathPC";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = @"Z:\s40ng\s40_sw\test_tools\s40_tdk\tmp";
                settingPath = "Main/M3W/LibrarySearchPath";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = @"e:\test_data";
                settingPath = "Main/M3W/TestDataPathPhone";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = "Fail case";
                settingPath = "Main/M3W/DefaultActionOnFail";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = 150;
                settingPath = "Main/M3W/DefaultVolume";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = 30;
                settingPath = "System/Timeouts/phone reset";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = 5000;
                settingPath = "System/Timeouts/send and receive message";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = true;
                settingPath = "System/Message resending/resend message in use";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");
                
                expected = 5000;
                settingPath = "System/Timeouts/receive messages from";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = 31336;
                settingPath = "System/Port config/gui - fw protocol port";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = false;
                settingPath = "Test run/memory leak testing enabled";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");

                expected = false;
                settingPath = "Test run/disable test case setup and teardown";
                Assert.AreEqual(expected, settings.getValue(settingPath), "Unexpected default setting value for the '" + settingPath + "' setting.");
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
        /// A test for LoadSettingsFromDirectory when called from a child application domain.
        /// </summary>
        [TestMethod()]
        public void LoadSettingsFromDirectoryAndFileFromChildAppDomainTest()
        {
            if (AppDomain.CurrentDomain.IsDefaultAppDomain())
            {
                Assert.Inconclusive("Unable to run this unit test since the unit test is running in the default application domain. Expected it to run in a child application domain be default.");
            }

            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag off so we can run the code from this child application domain as it would normally run
            SettingsManager.Instance.UnitTesting = false;

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

                // Attempt to load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 0;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings directory has one settings file but we should not be able to load settings from a child application domain so there should be no setting modules after attempting a load.");

                // Attempt to load settings from the file
                SettingsManager.Instance.LoadSettingsFromFile(filePath);

                expected = 0;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "An attempt was made to load the settings file but we should not be able to load settings from a child application domain so there should be no setting modules after attempting a load.");
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
        /// A test that we can update a setting value and save the settings.
        /// </summary>
        [TestMethod()]
        public void UpdateAndSaveSettingsTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string[] fileNames = new string[] { "Accounts.py", "Main.py", "ReferencePhone.py", "Remote.py", "System.py", "TestRun.py" };

                foreach (string fileName in fileNames)
                {
                    // Create the settings file
                    UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDirectoryPath, fileName));
                }

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                Assert.AreEqual(fileNames.Length, SettingsManager.Instance.Count, "The settings files have been saved and there should be a setting module for each file.");

                // Change the read-only setting
                SettingsManager.Instance.ReadOnly = false;

                // Get the dynamic object
                dynamic settings = SettingsManager.Instance;

                // Set a setting value
                object expected = true;
                settings.TestRun.TracingEnabled = true;
                Assert.AreEqual(expected, settings.TestRun.TracingEnabled, "Expected to be able to enable tracing.");

                // Get a setting value
                double expectedLevel = 0.01;
                Assert.AreEqual(expectedLevel, settings.Main.NoiseLevel, "Expected the noise level to be set to 0.01.");

                // Save all of the settings
                SettingsManager.Instance.SaveAll();

                // Set a setting value
                expected = true;
                Assert.AreEqual(expected, settings.TestRun.TracingEnabled, "Expected tracing to be enabled after saving this change.");

                // Get a setting value
                expectedLevel = 0.01;
                Assert.AreEqual(expectedLevel, settings.Main.NoiseLevel, "Expected the noise level to be set to 0.01.");

                // Reset the settings manager for this test
                SettingsManager.Instance.Reset();

                // Set the unit testing flag so we can run this test as though we were running from the main application domain
                SettingsManager.Instance.UnitTesting = true;

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                Assert.AreEqual(fileNames.Length, SettingsManager.Instance.Count, "The settings have all been saved and there should be a setting module for each file.");

                // Get a setting value
                expected = true;
                Assert.AreEqual(expected, settings.TestRun.TracingEnabled, "Expected tracing to be enabled after loading the settings with the change.");

                // Get a setting value
                expectedLevel = 0.01;
                Assert.AreEqual(expectedLevel, settings.Main.NoiseLevel, "Expected the noise level to be set to 0.01.");
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

#if SUPPORT_DEFAULT_SUBDIRECTORY
        /// <summary>
        /// A test that we can update a setting value and save the settings when using the special 'default' directory.
        /// </summary>
        [TestMethod()]
        public void SpecialDefaultDirectoryUpdateAndSaveSettingsTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string[] fileNames = new string[] { "Accounts.py", "Main.py", "ReferencePhone.py", "Remote.py", "System.py", "TestRun.py" };

                string settingsDefaultDirectoryPath = Path.Combine(settingsDirectoryPath, "default");

                // Create the special 'default' subdirectory for this test
                Directory.CreateDirectory(settingsDefaultDirectoryPath);

                foreach (string fileName in fileNames)
                {
                    // Create the settings file in the special 'default' subdirectory
                    UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDefaultDirectoryPath, fileName));
                }

                // Load settings from the settings directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                Assert.AreEqual(fileNames.Length, SettingsManager.Instance.Count, "The settings files have been saved to the special 'default' subdirectory and there should be a setting module for each file.");

                // Change the read-only setting
                SettingsManager.Instance.ReadOnly = false;

                // Get the dynamic object
                dynamic settings = SettingsManager.Instance;

                // Set a setting value
                object expected = true;
                settings.TestRun.TracingEnabled = true;
                Assert.AreEqual(expected, settings.TestRun.TracingEnabled, "Expected to be able to enable tracing.");

                // Save all of the settings
                SettingsManager.Instance.SaveAll();

                // Set a setting value
                expected = true;
                Assert.AreEqual(expected, settings.TestRun.TracingEnabled, "Expected tracing to be enabled after saving this change.");

                // Reset the settings manager for this test
                SettingsManager.Instance.Reset();

                // Set the unit testing flag so we can run this test as though we were running from the main application domain
                SettingsManager.Instance.UnitTesting = true;

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                Assert.AreEqual(fileNames.Length, SettingsManager.Instance.Count, "The settings have all been saved and there should be a setting module for each file.");

                // Set a setting value
                expected = true;
                Assert.AreEqual(expected, settings.TestRun.TracingEnabled, "Expected tracing to be enabled after loading the settings with the change.");

                // Reset the settings manager
                SettingsManager.Instance.Reset();
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
        /// A test for LoadSettingsFromDirectory using an IronPython settings file in the special 'default' directory and an XML file containing overrides.
        /// </summary>
        [TestMethod()]
        public void SpecialDefaultDirectoryLoadSettingsFromDirectoryWithIronPythonSettingsAndOverrideFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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

                string settingsDefaultDirectoryPath = Path.Combine(settingsDirectoryPath, "default");

                // Create the special 'default' subdirectory for this test
                Directory.CreateDirectory(settingsDefaultDirectoryPath);

                // Create the settings file in the special 'default' directory
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDefaultDirectoryPath, fileName));

                string overrideFileName = "ModemSettings.xml";

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideFileName, Path.Combine(settingsDirectoryPath, overrideFileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                string expectedPhoneNumberValue = "+358050505094594599";
                Assert.AreEqual(expectedPhoneNumberValue, settings.ModemSettings.PhoneNumber, "Expected the phone number setting value to match that specified in the XML override file for the IronPython settings file.");

                // Reset the settings manager
                SettingsManager.Instance.Reset();
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
        /// A test for LoadSettingsFromDirectory using an IronPython settings file in the special 'default' directory and an older XML file containing overrides.
        /// </summary>
        [TestMethod()]
        public void SpecialDefaultDirectoryIronPythonSettingsAndOldOverrideFileTest()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

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
                string settingsDefaultDirectoryPath = Path.Combine(settingsDirectoryPath, "default");

                // Create the special 'default' subdirectory for this test
                Directory.CreateDirectory(settingsDefaultDirectoryPath);

                string overrideFileName = "DefaultSettings.xml";
                string overrideFilePath = Path.Combine(settingsDirectoryPath, overrideFileName);

                // Create the settings file
                UnitTestUtilities.CreatingSettingsFile(overrideFileName, overrideFilePath);

                // Wait a while
                Thread.Sleep(2000);

                string fileName = "DefaultSettings.py";

                // Create the settings file in the special 'default' directory
                UnitTestUtilities.CreatingSettingsFile(fileName, Path.Combine(settingsDefaultDirectoryPath, fileName));

                // Load settings from the directory
                SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

                int expected = 1;
                Assert.AreEqual(expected, SettingsManager.Instance.Count, "The settings file has been added so there should be one setting module.");

                dynamic settings = SettingsManager.Instance;
                expected = 40;
                Assert.AreEqual(expected, settings.DefaultSettings.PhoneReset, "Expected the phone reset setting value to match that specified in the older override file rather than the new IronPython file since we should preserve user's settings.");

                Assert.IsTrue(File.Exists(overrideFilePath), "Expected the '" + overrideFilePath + "' file to not be deleted since we should preserve user's settings.");

                // Reset the settings manager
                SettingsManager.Instance.Reset();
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
        /// A test for LoadSettingsFromDirectory using an IronPython settings file and an XML file containing overrides.
        /// </summary>
        //[TestMethod()]
        public void LoadSettingsFromLocalDirectory()
        {
            // Reset the settings manager for this test
            SettingsManager.Instance.Reset();

            // Set the unit testing flag so we can run this test as though we were running from the main application domain
            SettingsManager.Instance.UnitTesting = true;

            // Construct a directory path for the settings
            string settingsDirectoryPath = @"C:\Users\mfreed\My Code\Marble\GUI\MainGUI\bin\settings";

            // Load settings from the directory
            SettingsManager.Instance.LoadSettingsFromDirectory(settingsDirectoryPath);

            Assert.IsTrue(SettingsManager.Instance.Count > 0, "The settings file has been added so there should be one setting module.");

            dynamic settings = SettingsManager.Instance;
            string pmdFilePath = settings.Main.PmdFilePath;

            Assert.IsFalse(string.IsNullOrEmpty(pmdFilePath), "Expected to be able to have a PMD file path that is not empty.");
        }

#endif

    }
}
