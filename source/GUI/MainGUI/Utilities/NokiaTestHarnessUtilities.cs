using System;
using System.IO;
using Marble.Model;

namespace Marble.Utilities
{
    /// <summary>
    /// Class that is used to store the logic that is specific to handling Nokia Test Harness (NTH) test cases in Marble.
    /// </summary>
    static public class NokiaTestHarnessUtilities
    {
        /// <summary>
        /// File extension for the Java application descriptor files.
        /// </summary>
        private const string _javaApplicationDescriptorFileExtension = ".jad";

        /// <summary>
        /// File extension for the Java archive files.
        /// </summary>
        private const string _javaArchiveFileExtension = ".jar";

        /// <summary>
        /// Determines whether this test case is a Nokia Test Harness (NTH) test case.
        /// </summary>
        /// <param name="testCase">Test case.</param>
        /// <returns>Value of <c>true</c> if the test case is a NTH test case, otherwise <c>false</c> is returned.</returns>
        static public bool IsNokiaTestHarnessTest(TestCase testCase)
        {
            bool nokiaTestHarnessTest = false;

            // If this test case has a script and it is a NTH script
            if (testCase != null &&
                testCase.Script != null &&
                IsNokiaTestHarnessScript(testCase.Script))
            {
                // This is a nokia test harness test
                nokiaTestHarnessTest = true;
            }

            return nokiaTestHarnessTest;
        }

        /// <summary>
        /// Determines whether this is a Nokia Test Harness (NTH) script.
        /// </summary>
        /// <param name="testScript">Test script.</param>
        /// <returns>Value of <c>true</c> if the test script is a NTH test script, otherwise <c>false</c> is returned.</returns>
        static public bool IsNokiaTestHarnessScript(TestScript testScript)
        {
            bool nokiaTestHarnessScript = false;

            // If this test script file is an assembly
            if (testScript != null &&
                Path.HasExtension(testScript.file) &&
                (Path.GetExtension(testScript.file) == _javaApplicationDescriptorFileExtension ||
                 Path.GetExtension(testScript.file) == _javaArchiveFileExtension))
            {
                // This is a nokia test harness script
                nokiaTestHarnessScript = true;
            }

            return nokiaTestHarnessScript;
        }

        /// <summary>
        /// Creates a new Nokia Test Harness test case.
        /// </summary>
        /// <param name="filePath">File path to the Java .jad or .jar midlet file.</param>
        /// <returns>Test case.</returns>
        /// <exception cref="ArgumentNullException">Thrown if a <c>null</c> file path is specified.</exception>
        /// <exception cref="ArgumentException">Thrown if the file path does not have a valid file extension.</exception>
        public static TestCase CreateTestCase(string filePath)
        {
            #region Check arguments

            if (filePath == null)
            {
                throw new ArgumentNullException("filePath", "Cannot create a test case since no file path has been specified.");
            }

            string fileExtension = Path.GetExtension(filePath);

            // If this is not a valid file extension
            if (fileExtension != _javaApplicationDescriptorFileExtension && 
                fileExtension != _javaArchiveFileExtension)
            {
                throw new ArgumentException("The '" + filePath + "' file does not have a file extension of '" + _javaApplicationDescriptorFileExtension +"' or '" + _javaArchiveFileExtension + "'.");
            }

            #endregion

            if (fileExtension == _javaApplicationDescriptorFileExtension)
            {
                // Use the archive file instead of the application descriptor file
                filePath = Path.Combine(Path.GetDirectoryName(filePath), Path.GetFileNameWithoutExtension(filePath) + _javaArchiveFileExtension);
            }

            TestScript script = new TestScript(string.Empty, Path.GetDirectoryName(filePath), Path.GetFileName(filePath), string.Empty);
            TestCase testCase = new TestCase(Path.GetFileNameWithoutExtension(filePath), script, null, "Java", "NTH");
            return testCase;
        }
    }
}
