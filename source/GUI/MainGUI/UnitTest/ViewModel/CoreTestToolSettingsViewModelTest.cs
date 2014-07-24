using Granite.Model;
using Granite.ViewModel;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Granite.UnitTest.ViewModel
{
    /// <summary>
    ///This is a test class for CoreTestToolSettingsViewModelTest and is intended
    ///to contain all CoreTestToolSettingsViewModelTest Unit Tests
    ///</summary>
    [TestClass()]
    public class CoreTestToolSettingsViewModelTest
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
        ///A test for CoreTestToolSettingsViewModel Constructor
        ///</summary>
        [TestMethod()]
        public void CoreTestToolSettingsViewModelConstructorTest()
        {
            string[] assemblyFilePaths = new string[] {};
            string[] configurationFilePaths = new string[] {};
            string[] sectionNames = new string[] {};

            CoreTestToolSettingsModel model = CoreTestToolSettingsModel.Create(assemblyFilePaths, configurationFilePaths, sectionNames);
            CoreTestToolSettingsViewModel target = new CoreTestToolSettingsViewModel(model);
        }

        /// <summary>
        ///A test for Model
        ///</summary>
        [TestMethod()]
        public void ModelTest()
        {
            string[] assemblyFilePaths = new string[] { };
            string[] configurationFilePaths = new string[] { };
            string[] sectionNames = new string[] { };

            CoreTestToolSettingsModel model = CoreTestToolSettingsModel.Create(assemblyFilePaths, configurationFilePaths, sectionNames);
            CoreTestToolSettingsViewModel target = new CoreTestToolSettingsViewModel(model);
            Assert.IsNotNull(target.Model);
            Assert.AreEqual(model, target.Model);
        }

    }
}
