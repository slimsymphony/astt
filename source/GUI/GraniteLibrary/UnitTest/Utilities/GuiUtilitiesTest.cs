using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using GraniteLibrary.Utilities;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GraniteLibrary.UnitTest.Utilities
{
    /// <summary>
    ///This is a test class for GuiUtilitiesTest and is intended
    ///to contain all GuiUtilitiesTest Unit Tests
    ///</summary>
    [TestClass()]
    public class GuiUtilitiesTest
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
        ///A test for GetOperatingSystemVersion
        ///</summary>
        [TestMethod()]
        public void GetOperatingSystemVersionTest()
        {
            string actual = GuiUtilities.GetOperatingSystemVersion();
            Assert.IsFalse(string.IsNullOrEmpty(actual), "The operating system version returned should not be null or empty.");
        }

        /// <summary>
        ///A test for HasOperatingSystemSupportForLargeIcons
        ///</summary>
        [TestMethod()]
        public void HasOperatingSystemSupportForLargeIconsTest()
        {
            GuiUtilities.HasOperatingSystemSupportForLargeIcons();
        }

        /// <summary>
        ///A test for UpdateSourceOnControlWithKeyboardFocus
        ///</summary>
        [TestMethod()]
        public void UpdateSourceOnControlWithKeyboardFocusTest()
        {
            GuiUtilities.UpdateSourceOnControlWithKeyboardFocus();
        }
    }
}
