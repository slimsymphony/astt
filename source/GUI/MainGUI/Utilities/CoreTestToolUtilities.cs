using System.IO;
using System.Linq;
using Marble.Model;

namespace Marble.Utilities
{
    /// <summary>
    /// Class that is used to store all of the logic that is specific to handling Core Test Tool (CTT) test cases in Marble.
    /// </summary>
    static public class CoreTestToolUtilities
    {
        /// <summary>
        /// Determines whether this test case is a Core Test Tool (CTT) test case.
        /// </summary>
        /// <param name="testCase">Test case.</param>
        /// <returns>Value of <c>true</c> if the test case is a CTT test case, otherwise <c>false</c> is returned.</returns>
        static public bool IsCoreTestToolTest(TestCase testCase)
        {
            bool coreTestToolTest = false;

            // If this test case has a script and it is a CTT script
            if (testCase != null &&
                testCase.Script != null &&
                IsCoreTestToolScript(testCase.Script))
            {
                // This is a core test tool test
                coreTestToolTest = true;
            }

            return coreTestToolTest;
        }

        /// <summary>
        /// Determines whether this is a Core Test Tool (CTT) script.
        /// </summary>
        /// <param name="testScript">Test script.</param>
        /// <returns>Value of <c>true</c> if the test script is a CTT test script, otherwise <c>false</c> is returned.</returns>
        static public bool IsCoreTestToolScript(TestScript testScript)
        {
            bool coreTestToolScript = false;

            // If this test script file is an assembly
            if (testScript != null &&
                Path.HasExtension(testScript.file) &&
                Path.GetExtension(testScript.file) == ".dll")
            {
                // This is a core test tool script
                coreTestToolScript = true;
            }

            return coreTestToolScript;
        }

        /// <summary>
        /// Determines whether the test case has any CTT configuration sections.
        /// </summary>
        /// <param name="testCase">Test case.</param>
        /// <returns>Value of <c>true</c> if the test case has at least one configuration section, otherwise <c>false</c> is returned.</returns>
        static public bool HasCoreTestToolConfigurationSectionNames(TestCase testCase)
        {
            bool hasCoreTestToolConfigurationSectionNames = false;

            if (IsCoreTestToolTest(testCase))
            {
                // Determine whether the test script has an associated configuration sections
                hasCoreTestToolConfigurationSectionNames = HasCoreTestToolConfigurationSectionNames(testCase.Script);
            }

            return hasCoreTestToolConfigurationSectionNames;
        }

        /// <summary>
        /// Determines whether the test script has any CTT configuration sections.
        /// </summary>
        /// <param name="testScript">Test script.</param>
        /// <returns>Value of <c>true</c> if the test script has at least one configuration section, otherwise <c>false</c> is returned.</returns>
        static public bool HasCoreTestToolConfigurationSectionNames(TestScript testScript)
        {
            bool hasCoreTestToolConfigurationSectionNames = false;

            if (IsCoreTestToolScript(testScript))
            {
                // Determine whether the test script has any CTT configuration information
                CoreTestToolConfiguration configuration = testScript.Configuration as CoreTestToolConfiguration;

                // If the test script does have configuration information and at least one section name
                if (configuration != null &&
                    configuration.SectionNames.FirstOrDefault() != null)
                {
                    // This test script has at least one section name
                    hasCoreTestToolConfigurationSectionNames = true;
                }
            }

            return hasCoreTestToolConfigurationSectionNames;
        }
    }
}
