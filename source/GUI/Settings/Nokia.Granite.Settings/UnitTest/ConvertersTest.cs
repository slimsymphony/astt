using System;
using System.Globalization;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace TestAutomation.Gui.Marble.Settings.UnitTest
{
    /// <summary>
    ///This is a test class for ConvertersTest and is intended
    ///to contain all ConvertersTest Unit Tests
    ///</summary>
    [TestClass()]
    public class ConvertersTest
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
        ///A test for ObjectsMatch
        ///</summary>
        [TestMethod()]
        public void ObjectsMatchTest()
        {
            bool firstObject = true;
            bool secondObject = true;
            bool expected = true;
            bool actual = Converters.ObjectsMatch(firstObject, secondObject);
            Assert.AreEqual(expected, actual, "The Boolean objects should match since they have been set to the same value.");

            firstObject = true;
            secondObject = false;
            expected = false;
            actual = Converters.ObjectsMatch(firstObject, secondObject);
            Assert.AreEqual(expected, actual, "The Boolean objects should not match since they have been set to different values.");

            string firstString = "This is some value.";
            string secondString = "This is some value.";
            expected = true;
            actual = Converters.ObjectsMatch(firstString, secondString);
            Assert.AreEqual(expected, actual, "The String objects should match since they have been set to the same value.");

            firstString = "This is some value.";
            secondString = "This is a different value.";
            expected = false;
            actual = Converters.ObjectsMatch(firstString, secondString);
            Assert.AreEqual(expected, actual, "The String objects should not match since they have been set to the different values.");

            string[] firstTextArray = new string[] { "This is the first value.", "This is the second value." };
            string[] secondTextArray = new string[] { "This is the first value.", "This is the second value." };
            expected = true;
            actual = Converters.ObjectsMatch(firstTextArray, secondTextArray);
            Assert.AreEqual(expected, actual, "The String array objects should match since they contain the same values.");

            firstTextArray = new string[] { "This is the first value.", "This is the second value." };
            secondTextArray = new string[] { "This is the first value.", "This is the second value that is different." };
            expected = false;
            actual = Converters.ObjectsMatch(firstTextArray, secondTextArray);
            Assert.AreEqual(expected, actual, "The String array objects should not match since they contain different values.");

            firstObject = true;
            secondString = "This is some value.";
            expected = false;
            actual = Converters.ObjectsMatch(firstObject, secondObject);
            Assert.AreEqual(expected, actual, "The Boolean and String objects should not match since they are different types.");
        }

        /// <summary>
        ///A test for ConvertFromString using a date.
        ///</summary>
        [TestMethod()]
        public void ConvertFromStringDateTimeTest()
        {
            // Convert the date using the current culture
            DateTime expected = DateTime.Now;
            string value = expected.ToString();
            DateTime actual = (DateTime)Converters.ConvertFromString(value, expected.GetType());
            Assert.AreEqual(expected.ToString(), actual.ToString(), "Expected the date converted to a string and back to give the original date.");

            // Convert the date using the invariant culture
            value = expected.ToString(CultureInfo.InvariantCulture);
            actual = (DateTime)Converters.ConvertFromString(value, expected.GetType());
            Assert.AreEqual(expected.ToString(), actual.ToString(), "Expected the date converted to a string using an invariant culture and back to give the original date.");
        }

        /// <summary>
        ///A test for ConvertFromString using a double.
        ///</summary>
        [TestMethod()]
        public void ConvertFromStringDoubleTest()
        {
            // Convert the double using the current culture
            double expected = 1.1;
            string value = expected.ToString();
            double actual = (double)Converters.ConvertFromString(value, expected.GetType());
            Assert.AreEqual(expected, actual, "Expected the double converted to a string and back to give the original date.");

            // Convert the double using the invariant culture
            value = expected.ToString(CultureInfo.InvariantCulture);
            actual = (double)Converters.ConvertFromString(value, expected.GetType());
            Assert.AreEqual(expected, actual, "Expected the double converted to a string using an invariant culture and back to give the original date.");
        }


        /// <summary>
        ///A test for ConvertToString using a date.
        ///</summary>
        [TestMethod()]
        public void ConvertToStringDateTimeTest()
        {
            // Convert the date to a string
            DateTime expected = DateTime.Now;
            string actual = Converters.ConvertToString(expected, expected.GetType());
            Assert.AreEqual(expected.ToString(CultureInfo.InvariantCulture), actual.ToString(), "Expected the date converted to a string to return an invariant culture string.");
        }

        /// <summary>
        ///A test for ConvertFromString using a double.
        ///</summary>
        [TestMethod()]
        public void ConvertToStringDoubleTest()
        {
            // Convert the double to a string
            double expected = 1.1;
            string actual = Converters.ConvertToString(expected, expected.GetType());
            Assert.AreEqual(expected.ToString(CultureInfo.InvariantCulture), actual.ToString(), "Expected the double converted to a string to return an invariant culture string.");
        }

        /// <summary>
        ///A test for ConvertToString and ConvertFromString using a date.
        ///</summary>
        [TestMethod()]
        public void ConvertToAndFromStringDateTimeTest()
        {
            // Convert the date to a string and back
            DateTime expected = DateTime.Now;
            DateTime actual = (DateTime)Converters.ConvertFromString(Converters.ConvertToString(expected, expected.GetType()), expected.GetType());
            Assert.AreEqual(expected.ToString(), actual.ToString(), "Expected the date converted to and from a string to return the same date.");
        }

        /// <summary>
        ///A test for ConvertToString and ConvertFromString using a double.
        ///</summary>
        [TestMethod()]
        public void ConvertToAndFromStringDoubleTest()
        {
            // Convert the double to a string and back
            double expected = -1.25;
            double actual = (double)Converters.ConvertFromString(Converters.ConvertToString(expected, expected.GetType()), expected.GetType());
            Assert.AreEqual(expected, actual, "Expected the double converted to and from a string to return the same number.");
        }

    }
}
