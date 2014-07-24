using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Data;
using System.Xml;
using System.Xml.Linq;

using Marble;
using Marble.Model;
using MarbleLibrary.Utilities;

namespace Marble.Utilities
{
    using System.IO;

    public class TestsetXmlParser
    {
        /// <summary>
        /// Parses the test case result from the result xml file.
        /// </summary>
        /// <param name="resultFilePath">Path to the result xml file</param>
        /// <returns>Returns TestResult object or null</returns>
        public static TestResult GetTestCaseResult(string resultFilePath)
        {
            if (!File.Exists(resultFilePath)) return null;
            bool isBlackboxModeOn = false;
            string result = "No Result";
            string author = string.Empty;
            string time = string.Empty;
            string description = string.Empty;
            string errorReason = string.Empty;
            string errorTraceback = string.Empty;
            int warningCount = 0;
            bool hasCrashOrReset = false;

            XElement reportElement = FileUtilities.LoadXmlDocumentWithSafeEncoding(resultFilePath);

            if (reportElement.Attribute("author") != null)
                author = reportElement.Attribute("author").Value;

            if (reportElement.Attribute("isblackboxmodeon") != null)
                bool.TryParse(reportElement.Attribute("isblackboxmodeon").Value, out isBlackboxModeOn);

            var tcElement = reportElement.Element("testcase");
            if (tcElement != null)
            {
                if (tcElement.Attribute("result") != null)
                    result = tcElement.Attribute("result").Value;

                if (tcElement.Attribute("date") != null)
                    time = tcElement.Attribute("date").Value;

                if (tcElement.Attribute("time") != null)
                    time += " " + tcElement.Attribute("time").Value;

                var descriptionElement = tcElement.Element("description");
                if (descriptionElement != null && descriptionElement.Attribute("title") != null)
                    description = descriptionElement.Attribute("title").Value;

                warningCount = tcElement.Elements().Count(e => e.Name == "warning");


                // Find the most critical error (crash or reset)
                XElement worstError = null;
                foreach (var errorElem in tcElement.Elements("error"))
                {
                    if (errorElem.Attribute("crashOrReset") == null) continue;

                    bool.TryParse(errorElem.Attribute("crashOrReset").Value, out hasCrashOrReset);

                    if (!hasCrashOrReset) continue;

                    worstError = errorElem;
                    break;
                }

                // Select the first error if no crash or reset error was found
                if (worstError == null)
                    worstError = tcElement.Element("error");

                if (worstError != null)
                {
                    if (worstError.Attribute("reason") != null)
                        errorReason = worstError.Attribute("reason").Value;

                    errorTraceback = worstError.Value;
                }

            }
            if (string.IsNullOrEmpty(result))
                result = "No Result";

            return new TestResult(result, time, resultFilePath, author, isBlackboxModeOn, description, errorReason, errorTraceback, warningCount, hasCrashOrReset);
        }

        /// <summary>
        /// Parses settings data from the Settings file with the given settings name.
        /// </summary>
        /// <param name="settingsFile">settings file</param>
        /// <param name="level">settings tree level</param>
        /// <param name="name">settings name</param>
        /// <returns>returns ObservableCollection of SettingsItem objects</returns>
        public ObservableCollection<SettingsItem> ParseSettingsFile(string settingsFile, int level, string name)
        {
            List<SettingsItem> settingsItemList = new List<SettingsItem>();
            List<SettingsItem> tempList = new List<SettingsItem>();

            try
            {
                System.IO.FileInfo fi = new System.IO.FileInfo(settingsFile);

                XElement rootHierarchy = XElement.Load(settingsFile);

                var results = from property in rootHierarchy.Descendants("property")
                              select property;

                foreach (XElement element in results)
                {
                    if (element.Attribute("name").Value != name)
                    {
                        continue;
                    }

                    SettingsItem settingsItem = new SettingsItem();
                    settingsItem.Name = element.Attribute("name").Value;
                    settingsItem.Type = element.Attribute("type").Value;
                    settingsItem.UrlType = element.Attribute("urlType").Value;
                    settingsItem.Hint = element.Attribute("hint").Value;
                    settingsItem.Value = "";
                    settingsItem.Branch = element.Attribute("branch").Value;
                    settingsItem.Mandatory = element.Attribute("mandatory").Value;
                    settingsItem.BooleanType = element.Attribute("booleanType").Value;
                    settingsItem.ParentElement = "";
                    settingsItem.Level = level;

                    if (level == 1)
                        settingsItem.IsVisible = true;
                    else
                        settingsItem.IsVisible = false;

                    if (settingsItem.Type == "URL")
                        settingsItem.HasChildren = true;
                    else
                        settingsItem.HasChildren = false;

                    settingsItemList.Add(settingsItem);

                    if (element.Elements().Count() > 0)
                    {
                        IEnumerable<XElement> elementList = element.Elements();
                        tempList = ParseSettingsFile(elementList, level + 1, settingsItem.Name);
                        settingsItemList.AddRange(tempList);
                    }

                    break;
                }
            }
            catch (Exception)
            {
                // TODO: Handle exception.
            }

            ObservableCollection<SettingsItem> generalSettingsModelCollection = new ObservableCollection<SettingsItem>(settingsItemList);

            return generalSettingsModelCollection;
        }

        /// <summary>
        /// Parses settings data from the Settings file.
        /// </summary>
        /// <param name="elements">XElement collection</param>
        /// <param name="settingsFile">Settings file</param>
        /// <param name="level">Settings tree level</param>
        /// <param name="parentElement">Parent element name</param>
        /// <returns>Returns a list of SettingsItem objects</returns>
        public List<SettingsItem> ParseSettingsFile(IEnumerable<XElement> elements, int level, string parentElement)
        {
            List<SettingsItem> settingsItemList = new List<SettingsItem>();
            List<SettingsItem> tempList = new List<SettingsItem>();

            foreach (XElement element in elements)
            {
                SettingsItem settingsItem = new SettingsItem();
                settingsItem.Name = element.Attribute("name").Value;
                settingsItem.Type = element.Attribute("type").Value;
                settingsItem.UrlType = element.Attribute("urlType").Value;
                settingsItem.Hint = element.Attribute("hint").Value;

                if (element.Attribute("val") != null)
                    settingsItem.Value = element.Attribute("val").Value;
                else
                    settingsItem.Value = "";

                settingsItem.Branch = element.Attribute("branch").Value;
                settingsItem.Mandatory = element.Attribute("mandatory").Value;
                settingsItem.BooleanType = element.Attribute("booleanType").Value;
                settingsItem.ParentElement = parentElement;
                settingsItem.Level = level;

                if (level == 1)
                    settingsItem.IsVisible = true;
                else
                    settingsItem.IsVisible = false;

                if (element.Elements().Count() > 0)
                {
                    settingsItem.HasChildren = true;
                    settingsItem.Value = "";
                }
                else
                {
                    settingsItem.HasChildren = false;
                }

                settingsItemList.Add(settingsItem);

                if (element.Elements().Count() > 0)
                {
                    IEnumerable<XElement> elementList = element.Elements();
                    tempList = ParseSettingsFile(elementList, level + 1, parentElement + @"\" + settingsItem.Name);
                    settingsItemList.AddRange(tempList);
                }
            }

            return settingsItemList;
        }

        /// <summary>
        /// Gets XAttributes value from XElement with the given attribute name.
        /// </summary>
        /// <param name="element">Xml element from which the attribute value is to be fetched.</param>
        /// <param name="attributeName">Attribute name to get value from.</param>
        /// <returns>Returns attribute value as string. Empty string is returned if attribute value is null.</returns>
        public static string GetAttributeValue(XElement element, string attributeName)
        {
            try
            {
                if (element == null) return string.Empty;

                var attribute = element.Attribute(attributeName);

                return attribute != null ? attribute.Value : string.Empty;
            }
            catch
            {
                return string.Empty;
            }
        }

        /// <summary>
        /// Gets XAttributes value from XElement with the given attribute name.
        /// </summary>
        /// <param name="element">Xml element from which the attribute value is to be fetched.</param>
        /// <param name="attributeName">Attribute name to get value from.</param>
        /// <returns>Returns attribute value as string. Empty string is returned if attribute value is null.</returns>
        public static List<string> GetAttributeValues(XElement element, List<string> attributeNames)
        {
            try
            {
                return element == null ? null : attributeNames.Select(attributeName => element.Attribute(attributeName)).Select(attribute => attribute != null ? attribute.Value : string.Empty).ToList();
            }
            catch
            {
                return null;
            }
        }

        public static List<XAttribute> ReadTestSetAttributes(string testSetFilePath)
        {
            if (!File.Exists(testSetFilePath)) return new List<XAttribute>();

            XDocument xmlDocument = XDocument.Load(testSetFilePath);
            XElement testSetElement = xmlDocument.Element("testset");

            if (testSetElement == null) return new List<XAttribute>();

            return testSetElement.Attributes().ToList();
        }

        public static List<XAttribute> GetMiscXmlAttributesFromTestCaseElement(XElement testCaseElement)
        {
            List<XAttribute> miscXmlAttributeList = new List<XAttribute>();

            if (testCaseElement == null) return new List<XAttribute>();

            foreach (XAttribute xAttribute in testCaseElement.Attributes())
            {
                switch (xAttribute.Name.ToString())
                {
                    // XML attributes needed by the test case model.
                    case "name":
                    case "feature":
                    case "subarea":
                    case "totalruncount":
                        continue;
                    default:
                        if (string.IsNullOrEmpty(xAttribute.Name.ToString())) continue;

                        miscXmlAttributeList.Add(xAttribute);
                        break;
                }
            }

            return miscXmlAttributeList;
        }

        /// <summary>
        /// Parses the test cases from a test set file.
        /// </summary>
        /// <param name="testSetFilePath">Test set file path.</param>
        /// <returns>Array of test cases.</returns>
        public static TestCase[] ParseTestsetFile(string testSetFilePath)
        {
            List<TestCase> testCaseList = new List<TestCase>();

            try
            {
                XDocument xmlDocument = XDocument.Load(testSetFilePath);

                // Fetch all test case elements from specified xml file.
                var results = from test in xmlDocument.Element("testset").Elements("testcase")
                              select test;

                bool isQcTestSet = TestsetXmlParser.IsQcTestSet(xmlDocument.Element("testset"));

                foreach (XElement element in results)
                {
                    if (element.Elements("testresult").Count() > 1)
                    {
                        TestCase parentTestCase = new TestCase(string.Empty, null);
                        bool parentTestCaseFound = false;

                        parentTestCase.IsAbsolutePathNeeded = isQcTestSet;

                        for (int i = 0; i < element.Elements("testresult").Count(); i++)
                        {
                            TestResult testResult = new TestResult(element.Elements("testresult").ElementAt(i));

                            // For QC test sets absolute file path is used instead of relative one.
                            TestScript testScript = CreateTestScript(element, isQcTestSet ? Path.GetFullPath(testSetFilePath) : testSetFilePath);

                            TestCase testCase = new TestCase(TestsetXmlParser.GetAttributeValue(element, "name"),
                                testScript, testResult,
                                TestsetXmlParser.GetAttributeValue(element, "feature"),
                                TestsetXmlParser.GetAttributeValue(element, "subarea"),
                                TestsetXmlParser.GetAttributeValue(element, "totalruncount"));

                            if (i == 0)
                            {
                                parentTestCase = testCase;
                                parentTestCaseFound = true;

                                testCase.IsRoot = true; // Set IsRoot to true if first TestCase. Otherwise it defaults to false.
                                testCase.IsVisible = true; // Set IsVisible to true if first TestCase. First TestCase is always visible.
                                testCase.Level = 1; // First TestCase is level 1 (root level) in the results tree.
                                testCaseList.Add(testCase); // Add the summary row TestCase

                                // Create a new TestCase for the first TestCase to be run.
                                TestResult childTestResult = new TestResult(element.Elements("testresult").ElementAt(i));
                                TestCase childTestCase = new TestCase(
                                    testCase.Name,
                                    testCase.Script,
                                    childTestResult,
                                    testCase.Feature,
                                    testCase.Subarea,
                                    testCase.TotalRunCount.ToString(),
                                    parentTestCase);

                                childTestCase.IsRoot = false;
                                childTestCase.IsVisible = false; // Consecutive (child) TestCases are initially hidden.
                                childTestCase.Level = 2; // Consecutive TestCases are level 2 (child node) in results tree.

                                parentTestCase.Children.Add(childTestCase);
                                childTestCase.Result.Index = parentTestCase.Children.Count;
                            }
                            else
                            {
                                // Update the summary rows Result if any child cases Result differs from it.
                                // This is done so the root (summary) rows Result column would have correct value depending of the results of it's children.
                                if (!testCaseList.First(item => item.Name.Equals(testCase.Name)).Result.Result.Equals(testCase.Result.Result)
                                    && !testCaseList.First(item => item.Name.Equals(testCase.Name)).Result.Result.StartsWith("Failed"))
                                    testCaseList.First(item => item.Name.Equals(testCase.Name)).Result.Result = testCase.Result.Result;

                                testCase.IsRoot = false;
                                testCase.IsVisible = false;
                                testCase.Level = 2; // Consecutive TestCases are level 2 (child node) in results tree.

                                if (parentTestCaseFound)
                                {
                                    testCase.Parent = parentTestCase;
                                    parentTestCase.Children.Add(testCase);
                                    testCase.Result.Index = parentTestCase.Children.Count;
                                }
                            }
                        }
                    }
                    else
                    {
                        TestResult testResult = new TestResult(element.Element("testresult"));

                        // For QC test sets absolute file path is used instead of relative one.
                        TestScript testScript = CreateTestScript(element, isQcTestSet ? Path.GetFullPath(testSetFilePath) : testSetFilePath);

                        TestCase testCase = new TestCase(
                            TestsetXmlParser.GetAttributeValue(element, "name"),
                            testScript,
                            testResult,
                            TestsetXmlParser.GetAttributeValue(element, "feature"),
                            TestsetXmlParser.GetAttributeValue(element, "subarea"),
                            TestsetXmlParser.GetAttributeValue(element, "totalruncount"));

                        testCase.MiscXmlAttributeListForTestCase = TestsetXmlParser.GetMiscXmlAttributesFromTestCaseElement(element);
                        testCase.IsAbsolutePathNeeded = isQcTestSet;

                        testCase.IsRoot = true; // Set IsRoot to true if first TestCase. Otherwise it defaults to false.
                        testCase.IsVisible = true; // Set IsVisible to true if first TestCase. First TestCase is always visible.
                        testCase.Level = 1; // First TestCase is level 1 (root level) in the results tree.
                        testCaseList.Add(testCase);
                    }
                }
            }
            catch
            {
                // TODO: Do something about the exception.
            }

            return testCaseList.ToArray();
        }

        /// <summary>
        /// Creates a test script from the test case XML element.
        /// </summary>
        /// <param name="testCaseElement">Test case XML element.</param>
        /// <returns>Test script.</returns>
        private static TestScript CreateTestScript(XElement testCaseElement, string testsetPath=null)
        {
            TestScript testScript;

            // Determine if there is a core test tool element that was created by the framework
            XElement coreTestToolElement = testCaseElement.Element("ctt_test");

            XElement configurationElement = null;

            // If this is not a CTT test created by the framework
            if (coreTestToolElement == null)
            {
                XElement testScriptElement = testCaseElement.Element("testscript");

                // Check if script path is relative to the test set path
                if (GetAttributeValue(testScriptElement, "relativetotestset").ToLower() != "true")
                    testsetPath = null;

                // Create the standard test script
                testScript =
                    new TestScript(
                        GetAttributeValue(testScriptElement, "class"),
                        GetAttributeValue(testScriptElement, "directory"),
                        GetAttributeValue(testScriptElement, "file"),
                        GetAttributeValue(testScriptElement, "method"),
                        testsetPath);

                // Determine if there is configuration information
                configurationElement = testScriptElement.Element("configuration");
            }

            // Else this is a CTT test created by the framework
            else
            {
                // Create a test script from the CTT test information
                testScript =
                    new TestScript(
                        TestsetXmlParser.GetAttributeValue(coreTestToolElement, "class"),
                        TestsetXmlParser.GetAttributeValue(coreTestToolElement, "directory"),
                        TestsetXmlParser.GetAttributeValue(coreTestToolElement, "file"),
                        TestsetXmlParser.GetAttributeValue(testCaseElement, "ucid"));

                // Store the assembly file as the sub-area and the test case id as the feature

                // If there is no sub-area
                if (string.IsNullOrEmpty(TestsetXmlParser.GetAttributeValue(testCaseElement, "subarea")))
                {
                    // Use the assembly file as the sub-area
                    testCaseElement.SetAttributeValue("subarea", Path.GetFileNameWithoutExtension(TestsetXmlParser.GetAttributeValue(testCaseElement.Element("ctt_test"), "file")));
                }

                // If there is no feature
                if (string.IsNullOrEmpty(TestsetXmlParser.GetAttributeValue(testCaseElement, "feature")))
                {
                    // Use the test case id as the feature
                    testCaseElement.SetAttributeValue("feature", TestsetXmlParser.GetAttributeValue(testCaseElement, "ucid"));
                }

                // Determine if there is configuration information
                configurationElement = coreTestToolElement.Element("configuration");
            }

            if (configurationElement != null)
            {
                List<string> configurationSectionNames = new List<string>();
                foreach (XElement sectionElement in configurationElement.Elements("section"))
                {
                    string name = TestsetXmlParser.GetAttributeValue(sectionElement, "name");

                    if (!string.IsNullOrEmpty(name))
                    {
                        configurationSectionNames.Add(name);
                    }
                }

                CoreTestToolConfiguration configuration = new CoreTestToolConfiguration(
                    TestsetXmlParser.GetAttributeValue(configurationElement, "directory"),
                    TestsetXmlParser.GetAttributeValue(configurationElement, "file"),
                    configurationSectionNames);

                // Add the configuration information
                testScript.Configuration = configuration;
            }

            return testScript;
        }

        public static bool IsQcTestSet(XElement testSetElement)
        {
            if (testSetElement == null || testSetElement.Name != "testset") return false;

            return testSetElement.Attribute("server-url") != null
                    && !string.IsNullOrEmpty(testSetElement.Attribute("server-url").Value)
                    && testSetElement.Attribute("domain") != null
                    && !string.IsNullOrEmpty(testSetElement.Attribute("domain").Value)
                    && testSetElement.Attribute("project") != null
                    && !string.IsNullOrEmpty(testSetElement.Attribute("project").Value)
                    && testSetElement.Attribute("testSet-id") != null
                    && !string.IsNullOrEmpty(testSetElement.Attribute("testSet-id").Value);
        }
    }
}
