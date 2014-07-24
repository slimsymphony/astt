using System;
using System.Windows;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GraniteLibrary.UnitTest.Utilities
{
    using GraniteLibrary.Utilities;

    /// <summary>
    ///This is a test class for ExceptionHandlerTest and is intended
    ///to contain all ExceptionHandlerTest Unit Tests
    ///</summary>
    [TestClass()]
    public class ExceptionHandlerTest
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
        ///A test for ExceptionHandler Constructor with null owner window.
        ///</summary>
        [TestMethod()]
        [ExpectedException(typeof(ArgumentNullException))]
        public void ExceptionHandlerConstructorTestNullOwnerWindow()
        {
            Window ownerWindow = null;
            ExceptionHandler target = new ExceptionHandler(ownerWindow);
        }

        /// <summary>
        ///A test for ExceptionHandler Constructor
        ///</summary>
        [TestMethod()]
        public void ExceptionHandlerConstructorTest()
        {
            Window ownerWindow = new Window();
            string errorTitle = "Title";
            string errorMessage = "Message";
            ExceptionHandler target = new ExceptionHandler(ownerWindow, errorTitle, errorMessage);
            Assert.AreEqual(errorTitle, target.ErrorTitle, "Expected the ErrorTitle property to have the same value as was passed in on the constructor.");
            Assert.AreEqual(errorMessage, target.ErrorMesage, "Expected the ErrorTitle property to have the same value as was passed in on the constructor.");
            ownerWindow.Close();
        }

        /// <summary>
        ///A test for CreateTopLevelException
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void CreateTopLevelExceptionTest()
        {
            ExceptionHandler_Accessor target = new ExceptionHandler_Accessor();
            Exception ex = new ArgumentNullException("param1", "Example exception where param1 is null.");
            ApplicationException topLevelException = target.CreateTopLevelException(ex);
            Assert.IsNotNull(topLevelException);
            Assert.AreEqual(ex, topLevelException.InnerException, "Expected the supplied exception to be an inner-exception of the top-level exception.");
            Assert.IsFalse(string.IsNullOrEmpty(topLevelException.Source), "Expected the source to be in the top-level exception.");
            Assert.IsTrue(topLevelException.Data.Count > 0, "Expected the top-level exception to contain additional data.");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.CommandLine");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.CurrentDirectory");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.AssemblyName");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.ProductName");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.ProductVersion");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.Date");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.MachineName");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.UserName");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.UserDomainName");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.OSVersion.Version");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.ProcessorCount");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.64BitProcess");
            CheckTopLevelExceptionHasData(topLevelException, "AdvancedInformation.64BitOperatingSystem");
        }

        /// <summary>
        /// Checks the contents of the data in the exception.
        /// </summary>
        /// <param name="topLevelException">The top-level exception to check.</param>
        /// <param name="name">Name of the data.</param>
        private static void CheckTopLevelExceptionHasData(Exception topLevelException, string name)
        {
            object data = topLevelException.Data[name];
            Assert.IsNotNull(data, "Expected the top-level exception to contain data for '" + name + "', but it does not contain this data.");

            string text = data as string;

            if (text != null)
            {
                Assert.IsFalse(string.IsNullOrEmpty(text), "Expected the top-level exception to contain data for '" + name + "' and not be set to an empty string.");
            }
        }

        /// <summary>
        ///A test for Enabled
        ///</summary>
        [TestMethod()]
        public void EnabledTest()
        {
            Window ownerWindow = new Window();
            ExceptionHandler target = new ExceptionHandler(ownerWindow);

            bool expected = true;
            bool actual = target.Enabled;
            Assert.AreEqual(expected, actual, "Expected the ExceptionHandler to be enabled by default.");

            expected = false;
            target.Enabled = expected;
            actual = target.Enabled;
            Assert.AreEqual(expected, actual, "Expected the ExceptionHandler to be disabled after setting it to false.");

            expected = true;
            target.Enabled = expected;
            actual = target.Enabled;
            Assert.AreEqual(expected, actual, "Expected the ExceptionHandler to be enabled after setting it to true.");

            ownerWindow.Close();
        }

        /// <summary>
        ///A test for OnOwnerWindowClosed
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void OnOwnerWindowClosedTest()
        {
            ExceptionHandler_Accessor target = new ExceptionHandler_Accessor();
            object sender = this;
            EventArgs e = new EventArgs();
            target.OnOwnerWindowClosed(sender, e);
        }

        /// <summary>
        ///A test for ErrorMesage
        ///</summary>
        [TestMethod()]
        public void ErrorMesageTest()
        {
            Window ownerWindow = new Window();
            ExceptionHandler target = new ExceptionHandler(ownerWindow);

            string expected = "Message";
            target.ErrorMesage = expected;
            string actual = target.ErrorMesage;
            Assert.AreEqual(expected, actual);

            ownerWindow.Close();
        }

        /// <summary>
        ///A test for ErrorTitle
        ///</summary>
        [TestMethod()]
        public void ErrorTitleTest()
        {
            Window ownerWindow = new Window();
            ExceptionHandler target = new ExceptionHandler(ownerWindow);

            string expected = "Title";
            target.ErrorTitle = expected;
            string actual = target.ErrorTitle;
            Assert.AreEqual(expected, actual);

            ownerWindow.Close();
        }
    }
}
