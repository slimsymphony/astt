using Granite.Model;
using Granite.ViewModel;
using Granite.Views;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Granite.UnitTest.Views
{
    /// <summary>
    ///This is a test class for SettingsViewTest and is intended
    ///to contain all SettingsViewTest Unit Tests
    ///</summary>
    [TestClass()]
    public class SettingsViewTest
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
        ///A test for SettingsView Constructor
        ///</summary>
        [TestMethod()]
        public void SettingsViewConstructorTest()
        {
            SettingsViewModel viewModel = new SettingsViewModel();
            SettingsView target = new SettingsView(viewModel);
        }

        /// <summary>
        ///A test for InitializeComponent
        ///</summary>
        [TestMethod()]
        public void InitializeComponentTest()
        {
            SettingsViewModel viewModel = new SettingsViewModel();
            SettingsView target = new SettingsView(viewModel);
            target.InitializeComponent();
        }
    }
}
