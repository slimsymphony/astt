using Granite.Model;
using Granite.ViewModel;
using Granite.Views;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Granite.UnitTest.Views
{
    /// <summary>
    ///This is a test class for CoreTestToolSettingsViewTest and is intended
    ///to contain all CoreTestToolSettingsViewTest Unit Tests
    ///</summary>
    [TestClass()]
    public class CoreTestToolSettingsViewTest
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
        ///A test for CoreTestToolSettingsView Constructor
        ///</summary>
        [TestMethod()]
        public void CoreTestToolSettingsViewConstructorTest()
        {
            string[] assemblyFilePaths = new string[] {};
            string[] configurationFilePaths = new string[] {};
            string[] sectionNames = new string[] {};

            CoreTestToolSettingsModel model = CoreTestToolSettingsModel.Create(assemblyFilePaths, configurationFilePaths, sectionNames);
            CoreTestToolSettingsViewModel viewModel = new CoreTestToolSettingsViewModel(model);
            CoreTestToolSettingsView target = new CoreTestToolSettingsView(viewModel);
        }

        /// <summary>
        ///A test for InitializeComponent
        ///</summary>
        [TestMethod()]
        public void InitializeComponentTest()
        {
            string[] assemblyFilePaths = new string[] { };
            string[] configurationFilePaths = new string[] { };
            string[] sectionNames = new string[] { };

            CoreTestToolSettingsModel model = CoreTestToolSettingsModel.Create(assemblyFilePaths, configurationFilePaths, sectionNames);
            CoreTestToolSettingsViewModel viewModel = new CoreTestToolSettingsViewModel(model);
            CoreTestToolSettingsView target = new CoreTestToolSettingsView(viewModel); 
            target.InitializeComponent();
        }
    }
}
