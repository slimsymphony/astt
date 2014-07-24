using System;
using System.Collections.Generic;
using Marble.Model;
using System.Text.RegularExpressions;

namespace Marble.Utilities
{
    /// <summary>
    /// Class for parsing test cases from a python script file
    /// </summary>
    public class TestCasePyParser
    {
        /// <summary>
        /// Parses all test cases from a python script file
        /// </summary>
        /// <param name="filePath">File system path to the script file</param>
        /// <returns>List of found test cases</returns>
        public static List<TestCase> GetTestCases(string filePath)
        {
            var testCases = new List<TestCase>();
            if(!System.IO.File.Exists(filePath)) return testCases;

            using (var reader = new System.IO.StreamReader(filePath))
            {
                string line;
                string subarea = "";
                string feature = "";
                string className = "";
                string testMethod = "";
                bool parseWintermuteCase = false;

                while ((line = reader.ReadLine()) != null)
                {
                    // Wintermute test case
                    // e.g. class WmFavorites01(FunctionalTestCase):
                    if (line.StartsWith("class") && line.TrimEnd().EndsWith("FunctionalTestCase):") )
                    {
                        parseWintermuteCase = true;
                        className = line.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)[1];
                        className = className.Substring(0, className.IndexOf('('));
                        subarea = "";
                        feature = "";
                        testMethod = "";
                    }
                    // Test class
                    // e.g. class CIRFA_Functional_MessageManagementTest(u_art.UITestCase):
                    else if (line.StartsWith("class") && (line.TrimEnd().EndsWith("UITestCase):") 
                             || (line.TrimEnd().EndsWith("MarbleTestCase):"))
                             || (line.TrimEnd().EndsWith("MiddlewareTestCase):"))))
                    {
                        parseWintermuteCase = false;
                        className = line.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)[1];
                        className = className.Substring(0, className.IndexOf('('));
                        subarea = "";
                        feature = "";
                        testMethod = "";
                    }

                    // subarea
                    // e.g. subarea = "Functional Tests"
                    else if (line.StartsWith("    subarea"))
                    {
                        subarea = line.Split(new[] { '=' })[1].Trim(new[] { ' ', '"', '\'' });
                    }

                    // feature
                    // e.g. feature = "Message Management"
                    else if (line.StartsWith("    feature"))
                    {
                        feature = line.Split(new[] { '=' })[1].Trim(new[] { ' ', '"', '\'' });
                    }

                    // method
                    // e.g. def testCIRFASendAndReceiveSMSinGSMSingleSim(self):
                    else if (line.StartsWith("    def") && line.TrimEnd().EndsWith("(self):") && !parseWintermuteCase) // if we are parsing wm case, ignore methods
                    {
                        testMethod = line.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)[1];
                        testMethod = testMethod.Substring(0, testMethod.IndexOf('('));
                    }

                    // case name
                    // e.g. @tcId CIRFA Send and receive SMS in GSM mode - Single SIM
                    else if (line.TrimStart().StartsWith("@tcId"))
                    {
                        string testCase = line.Substring(line.IndexOf("@tcId", StringComparison.Ordinal) + 5).Trim();
                        string directory = System.IO.Path.GetDirectoryName(filePath);
                        testCases.Add(new TestCase(testCase,
                                        new TestScript(className,
                                            directory,
                                            System.IO.Path.GetFileNameWithoutExtension(filePath),
                                            testMethod),
                                    feature: feature,
                                    subarea: subarea));
                    }
                    // if this is a wintermute test case, case name is inside the comment
                    else if (parseWintermuteCase && line.TrimStart().StartsWith("\"\"\"")) 
                    {
                        string details = Regex.Match(line, @"\""\""\""\s*((.|^\s)*)\s*\""\""\""").Groups[1].Value;
                        if (details != "")
                        {
                            string testCase = details;
                            string directory = System.IO.Path.GetDirectoryName(filePath);
                            testCases.Add(new TestCase(testCase,
                                        new TestScript(className,
                                            directory,
                                            System.IO.Path.GetFileNameWithoutExtension(filePath),
                                            testMethod),
                                    feature: "Browser",
                                    subarea: "(Wintermute)"));
                        }
                    }

                }
            }
            return testCases;
        }
    }
}
