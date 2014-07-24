using System.Reflection;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace TestAutomation.Gui.Marble.Settings.UnitTest
{
    /// <summary>
    ///This is a test class for SettingsManagerProxyTest and is intended
    ///to contain all SettingsManagerProxyTest Unit Tests
    ///</summary>
    [TestClass()]
    public class SettingsManagerProxyTest
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
        ///A test for SettingsManagerProxy Constructor
        ///</summary>
        [TestMethod()]
        public void SettingsManagerProxyConstructorTest()
        {
            SettingsManagerProxy target = new SettingsManagerProxy();
        }

        /// <summary>
        ///A test for Dispose
        ///</summary>
        [TestMethod()]
        public void DisposeTest()
        {
            SettingsManagerProxy target = new SettingsManagerProxy();
            target.Dispose();
        }

        /// <summary>
        ///A test for calling Dispose multiple times.
        ///</summary>
        [TestMethod()]
        public void DisposeMultipleTimesTest()
        {
            SettingsManagerProxy target = new SettingsManagerProxy();
            target.Dispose();
            target.Dispose();
        }

        /// <summary>
        ///A test for SaveAll
        ///</summary>
        [TestMethod()]
        public void SaveAllTest()
        {
            SettingsManagerProxy target = new SettingsManagerProxy();

            // Verify we can perform a save all even though we have not loaded or modified any settings
            target.SaveAll();
        }

        /// <summary>
        ///A test for Count
        ///</summary>
        [TestMethod()]
        public void CountTest()
        {
            SettingsManagerProxy target = new SettingsManagerProxy();
            int expected = 0;
            int actual = target.Count;
            Assert.AreEqual(expected, actual, "Initially the count of setting modules should be set to zero.");
        }

        /// <summary>
        ///A test for IsSaving
        ///</summary>
        [TestMethod()]
        [DeploymentItem("TestAutomation.Gui.Marble.Settings.dll")]
        public void IsSavingTest()
        {

            SettingsManagerProxy_Accessor target = new SettingsManagerProxy_Accessor();
            bool expected = false;
            bool actual = target.IsSaving;
            Assert.AreEqual(expected, actual, "Initially no settings should be being saved.");

            expected = true;
            target.IsSaving = expected;
            actual = target.IsSaving;
            Assert.AreEqual(expected, actual, "The setting to indicate the settings are being saved should be able to be set (but the property is private).");
        }

        /// <summary>
        ///A test for SettingModules
        ///</summary>
        [TestMethod()]
        public void SettingModulesTest()
        {
            SettingsManagerProxy target = new SettingsManagerProxy();
            Assert.IsNotNull(target.SettingModules, "There should initially be a setting module collection.");
            int expected = 0;
            int actual = target.SettingModules.Count;
            Assert.AreEqual(expected, actual, "There should initially not be any setting modules in the collection.");
        }

        /// <summary>
        ///A test for Watchers
        ///</summary>
        [TestMethod()]
        [DeploymentItem("TestAutomation.Gui.Marble.Settings.dll")]
        public void WatchersTest()
        {
            SettingsManagerProxy_Accessor target = new SettingsManagerProxy_Accessor();
            Assert.IsNull(target.Watchers, "Initially the list of watchers should be set to null.");
        }

        /// <summary>
        ///A test for GetSettingModuleNameFromGetValueToken
        ///</summary>
        [TestMethod()]
        public void GetSettingModuleNameFromGetValueTokenTest()
        {
            MethodInfo method = typeof(SettingsManagerProxy).GetMethod("GetSettingModuleNameFromGetValueToken", BindingFlags.Static | BindingFlags.NonPublic);
            if (method == null)
            {
                Assert.Inconclusive("Cannot unit test the 'GetSettingModuleNameFromGetValueToken' method since it is no longer implemented.");
            }
            else
            {
                string token = "Main";
                string expected = "Main";
                string actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The token from GetValue() has not correctly been converted to a format required for a setting module name.");

                token = "Test run";
                expected = "TestRun";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The token from GetValue() has not correctly been converted to a format required for a setting module name.");

                token = " ABC ";
                expected = "ABC";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The token from GetValue() has not correctly been converted to a format required for a setting module name.");

                token = "def hij k";
                expected = "defHijK";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The token from GetValue() has not correctly been converted to a format required for a setting module name.");

                token = " a ";
                expected = "a";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The token from GetValue() has not correctly been converted to a format required for a setting module name.");

                token = "  ";
                expected = "";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The token from GetValue() has not correctly been converted to a format required for a setting module name.");

                token = "Abc $%^£& def";
                expected = "AbcDef";
                actual = method.Invoke(null, new object[] { token }) as string;
                Assert.AreEqual(expected, actual, "The token from GetValue() has not correctly been converted to a format required for a setting module name.");
            }
        }
    }
}
