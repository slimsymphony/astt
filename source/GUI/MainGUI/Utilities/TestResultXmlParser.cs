// -----------------------------------------------------------------------
// <copyright file="TestResultXmlParser.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Utilities
{
    using System;
    using System.Collections.Generic;
    using System.Globalization;
    using System.IO;
    using System.Linq;
    using System.Text;
    using System.Windows;
    using System.Xml.Linq;

    using Marble.Model;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public static class TestResultXmlParser
    {
        /// <summary>
        /// The value not found text.
        /// </summary>
        public static string ValueNotFoundText = "N/A";

        /// <summary>
        /// The test case report item element type dictionary.
        /// </summary>
        public static Dictionary<TestCaseReportItemType, string> TestCaseReportItemElementTypeDictionary = new Dictionary<TestCaseReportItemType, string>()
            {
                { TestCaseReportItemType.Comment, "comment" },
                { TestCaseReportItemType.Description, "description" },
                { TestCaseReportItemType.TestStep, "teststep" },
                { TestCaseReportItemType.Summary, "summary" },
                { TestCaseReportItemType.Error, "error" },
                { TestCaseReportItemType.Warning, "warning" },
                { TestCaseReportItemType.Videos, "videos" },
                { TestCaseReportItemType.PerfTestStep, "test_step_perf" },
                { TestCaseReportItemType.BugReport, "bug_report" },
            };

        /// <summary>
        /// Creates new TestReportModel from test result XML file.
        /// </summary>
        /// <param name="testResultXmlFilePath">The test result xml file path.</param>
        /// <returns>The Marble.Model.TestReportModel.</returns>
        public static TestReportModel CreateTestReport(string testResultXmlFilePath)
        {
            if (!File.Exists(testResultXmlFilePath)) return null;

            XElement testReportElement = FileUtilities.LoadXmlDocumentWithSafeEncoding(testResultXmlFilePath);

            if (testReportElement == null)
            {
                MessageBox.Show("Marble Test Result file loading failed!", "Marble - Loading Failed!");

                return null;
            }

            if (testReportElement.Name != "testreport")
            {
                MessageBox.Show("File is not valid Marble Test Result file!", "Marble - Loading Failed!");
                
                return null;
            }

            TestReportModel testReportModel = new TestReportModel
                {
                    TestResultXmlFilePath = testResultXmlFilePath,
                    Author = testReportElement.Attribute("author") != null ? testReportElement.Attribute("author").Value : ValueNotFoundText,
                    TestGroupFilter = testReportElement.Attribute("test_group_filter") != null ? testReportElement.Attribute("test_group_filter").Value : ValueNotFoundText
                };

            DateTime startTime, endTime;

            if (testReportElement.Attribute("date") != null && testReportElement.Attribute("time") != null &&
                DateTime.TryParse(testReportElement.Attribute("date").Value + " " + testReportElement.Attribute("time").Value, out startTime))
                testReportModel.StartTime = startTime;

            parseProductElement(testReportElement, testReportModel);
            parseTestCaseElement(testReportElement, testReportModel);

            testReportModel.Summary = testReportElement.Attribute("summary") != null ? testReportElement.Attribute("summary").Value : ValueNotFoundText;

            TestResultXmlParser.GetListOfNeededFiles(testReportModel);

            return testReportModel;
        }

        /// <summary>
        /// Gets element name according to test case report item type.
        /// </summary>
        /// <param name="itemType">Test case report item type.</param>
        /// <returns>Element name as a string.</returns>
        public static string GetElementName(TestCaseReportItemType itemType)
        {
            return TestCaseReportItemElementTypeDictionary.ContainsKey(itemType) ? TestCaseReportItemElementTypeDictionary[itemType] : string.Empty;
        }

        /// <summary>
        /// Gets test case report item type by element name.
        /// </summary>
        /// <param name="elementName">The element name.</param>
        /// <returns>The Marble.Model.TestCaseReportItemType.</returns>
        public static TestCaseReportItemType GetReportItemType(string elementName)
        {
            if (TestCaseReportItemElementTypeDictionary.ContainsValue(elementName))
            {
                foreach (KeyValuePair<TestCaseReportItemType, string> keyValuePair in TestCaseReportItemElementTypeDictionary.Where(keyValuePair => keyValuePair.Value == elementName))
                {
                    return keyValuePair.Key;
                }
            }

            return TestCaseReportItemType.Unknown;
        }

        /// <summary>
        /// The string to test report result.
        /// </summary>
        /// <param name="testReportResult">The test report result.</param>
        /// <returns>TestReportResult enum.</returns>
        public static TestReportResult StringToTestReportResult(string testReportResult)
        {
            switch (testReportResult.ToLower())
            {
                case "failed":
                    return TestReportResult.Failed;
                case "passed":
                    return TestReportResult.Passed;
                case "no result":
                    return TestReportResult.NoResult;
            }

            return TestReportResult.Failed;
        }

        /// <summary>
        /// Gets the list of file paths containing needed files to display test report properly.
        /// </summary>
        /// <param name="testReportModel">The test report model.</param>
        /// <returns>List of file paths containing needed files.</returns>
        public static List<string> GetListOfNeededFiles(TestReportModel testReportModel)
        {
            if (!File.Exists(testReportModel.TestResultXmlFilePath)) return null;

            XElement testReportElement = FileUtilities.LoadXmlDocumentWithSafeEncoding(testReportModel.TestResultXmlFilePath);

            List<string> foundBitmapFilePaths = new List<string>();
            TestResultXmlParser.findElementAttributeValuesRecursively(testReportElement, "bitmap", "name", foundBitmapFilePaths);

            for (int i = 0; i < foundBitmapFilePaths.Count; i++)
            {
                string absoluteFilePathOfBitmapFile = CreateFilePathFromCaptureFileName(foundBitmapFilePaths[i], testReportModel.TestResultXmlFilePath);

                if (testReportModel.TestCaseReport.NeededFiles.Contains(absoluteFilePathOfBitmapFile)) continue;

                testReportModel.TestCaseReport.NeededFiles.Add(absoluteFilePathOfBitmapFile);
            }

            return testReportModel.TestCaseReport.NeededFiles;
        }

        /// <summary>
        /// Creates test report playlist XML file which is used to locate needed files in compressed test results package.
        /// </summary>
        /// <param name="testReportModels">The test report models.</param>
        /// <param name="filePath">File path of the generated playlist XML file.</param>
        public static void CreateTestReportPlaylistXml(List<TestReportModel> testReportModels, string filePath)
        {
            XDocument doc = new XDocument();
            XElement rootElement = new XElement("MarbleTestReports");

            foreach (TestReportModel testReportModel in testReportModels)
            {
                XElement testReportElement = new XElement(
                    "TestReport",
                        new XAttribute("filePath", "xml\\" + FileUtilities.GetFileName(testReportModel.TestResultXmlFilePath)),
                        new XAttribute("id", testReportModel.TestCaseReport.Id));

                foreach (string neededFile in testReportModel.TestCaseReport.NeededFiles)
                {
                    if (FileUtilities.GetFileName(neededFile) == FileUtilities.GetFileName(testReportModel.TestResultXmlFilePath)) continue;

                    testReportElement.Add(new XElement("NeededFile", new XAttribute("filePath", FileUtilities.GetFileName(neededFile))));
                }

                rootElement.Add(testReportElement);
            }

            doc.Add(rootElement);
            doc.Save(filePath);
        }

        /// <summary>
        /// Creates test report playlist XML file which is used to locate needed files in compressed test results package.
        /// </summary>
        /// <param name="testReportModel">The test report model.</param>
        /// <param name="filePath">File path of the generated playlist XML file.</param>
        public static void CreateTestReportPlaylistXml(TestReportModel testReportModel, string filePath)
        {
            CreateTestReportPlaylistXml(new List<TestReportModel>() { testReportModel }, filePath);
        }

        private static void parseProductElement(XElement testReportElement, TestReportModel testReportModel)
        {
            XElement productElement = testReportElement.Element("product");

            if (productElement == null) return;

            testReportModel.TestReportProduct.Name = productElement.Attribute("name") != null ? productElement.Attribute("name").Value : ValueNotFoundText;
            testReportModel.TestReportProduct.MainDisplay = productElement.Attribute("main_display") != null ? productElement.Attribute("main_display").Value : ValueNotFoundText;
            testReportModel.TestReportProduct.Imei = productElement.Attribute("imei") != null ? productElement.Attribute("imei").Value : ValueNotFoundText;

            foreach (XElement versionElement in productElement.Elements("version"))
            {
                XAttribute attribute = versionElement.Attribute("type");
                if (attribute == null) continue;

                string versionType = attribute.Value;

                switch (versionType)
                {
                    case "sw":
                        testReportModel.TestReportProduct.SoftwareVersion = versionElement.Value;
                        break;
                    case "hw":
                        testReportModel.TestReportProduct.HardwareVersion = versionElement.Value;
                        break;
                    case "marble server":
                        testReportModel.TestReportProduct.MarbleServerVersion = versionElement.Value;
                        break;
                }
            }
        }

        private static void parseTestCaseElement(XElement testReportElement, TestReportModel testReportModel)
        {
            XElement testCaseElement = testReportElement.Element("testcase");

            if (testCaseElement == null) return;

            testReportModel.TestCaseReport.Result =
                TestResultXmlParser.StringToTestReportResult(testCaseElement.Attribute("result") != null
                                                                 ? testCaseElement.Attribute("result").Value
                                                                 : string.Empty);
            testReportModel.TestCaseReport.Id = testCaseElement.Attribute("id") != null
                                                    ? testCaseElement.Attribute("id").Value
                                                    : ValueNotFoundText;
            testReportModel.TestCaseReport.TestCaseType = testCaseElement.Attribute("type") != null
                                                              ? testCaseElement.Attribute("type").Value
                                                              : ValueNotFoundText;

            if (testCaseElement.Attribute("date") != null && testCaseElement.Attribute("start_time") != null)
            {
                string startTimeText = testCaseElement.Attribute("date").Value + " " + testCaseElement.Attribute("start_time").Value;
                DateTime startTime;

                if (DateTime.TryParse(startTimeText, out startTime))
                    testReportModel.TestCaseReport.StartTime = startTime;
            }

            if (testCaseElement.Attribute("date") != null && testCaseElement.Attribute("stop_time") != null)
            {
                string endTimeText = testCaseElement.Attribute("date").Value + " " + testCaseElement.Attribute("stop_time").Value;
                DateTime endTime;

                if (DateTime.TryParse(endTimeText, out endTime))
                {
                    testReportModel.TestCaseReport.EndTime = endTime;

                    //NOTE: Currently there is no end date recorded to result. Meanwhile when end date time is smaller than start date time
                    // (e.g. test started before midnight and ended after), one day is added to date time. This also assumes that test case doesn't last
                    // over one day.
                    if (testReportModel.TestCaseReport.EndTime.Ticks < testReportModel.TestCaseReport.StartTime.Ticks)
                    {
                        testReportModel.TestCaseReport.EndTime = new DateTime(testReportModel.TestCaseReport.EndTime.Ticks + TimeSpan.TicksPerDay);
                    }

                    testReportModel.TestCaseReport.Duration = new TimeSpan(testReportModel.TestCaseReport.EndTime.Ticks - testReportModel.TestCaseReport.StartTime.Ticks);
                }
            }

            testReportModel.TestCaseReport.Subarea = testCaseElement.Attribute("subarea") != null ? testCaseElement.Attribute("subarea").Value : ValueNotFoundText;
            testReportModel.TestCaseReport.Feature = testCaseElement.Attribute("feature") != null ? testCaseElement.Attribute("feature").Value : ValueNotFoundText;

            foreach (XElement testCaseItemElement in testCaseElement.Elements())
            {
                TestCaseReportItemModel reportItem = parseTestCaseItemElement(testCaseItemElement, testReportModel.TestResultXmlFilePath);

                if (reportItem == null) continue;
                    
                testReportModel.TestCaseReport.Items.Add(reportItem);
            }
        }

        private static TestCaseReportItemModel parseTestCaseItemElement(XElement testCaseItemElement, string testResultXmlFilePath)
        {
            TestCaseReportItemModel testCaseReportItem = null;

            switch (GetReportItemType(testCaseItemElement.Name.ToString()))
            {
                case TestCaseReportItemType.Comment:
                    testCaseReportItem = new CommentReportItemModel(testCaseItemElement.Attribute("reason").Value);
                    break;
                case TestCaseReportItemType.Description:
                    testCaseReportItem = new DescriptionReportItemModel(testCaseItemElement.Attribute("title").Value, testCaseItemElement.Value.ToString(CultureInfo.InvariantCulture));
                    break;
                case TestCaseReportItemType.TestStep:
                    // Test Step items are not currently displayed.
                    break;
                    testCaseReportItem = parseTestStepReportElement(testCaseItemElement);
                    break;
                case TestCaseReportItemType.Summary:
                    testCaseReportItem = new SummaryReportItemModel(testCaseItemElement.Attribute("name").Value)
                        {
                            Id = int.Parse(testCaseItemElement.Attribute("id").Value),
                            StepId = int.Parse(testCaseItemElement.Attribute("stepId").Value)
                        };

                    CaptureItemReportModel captureItemReport = parseSummaryForCaptureReportItem(testCaseItemElement);

                    if (captureItemReport != null)
                    {
                        captureItemReport.CaptureBitmapFilePath = CreateFilePathFromCaptureFileName(captureItemReport.CaptureBitmapFileName, testResultXmlFilePath);
                        ((SummaryReportItemModel)testCaseReportItem).CaptureItemReport = captureItemReport;
                    }

                    break;
                case TestCaseReportItemType.Error:
                    testCaseReportItem = new ErrorReportItemModel(testCaseItemElement.Attribute("reason").Value)
                        {
                            TraceBack = testCaseItemElement.Value
                        };
                    break;
                case TestCaseReportItemType.Warning:
                    testCaseReportItem = new WarningReportItemModel(testCaseItemElement.Attribute("reason").Value);
                    break;
                case TestCaseReportItemType.Videos:

                    string videoFilePath = testResultXmlFilePath.Remove(testResultXmlFilePath.LastIndexOf("\\"));
                    videoFilePath = videoFilePath.Remove(videoFilePath.LastIndexOf("\\"));
                    //videoFilePath += "\\" + testCaseItemElement.Element("video").Attribute("name").Value;

                    List<string> videoFilePaths = (from videoElement in testCaseItemElement.Elements("video") 
                                                   select videoElement.Attribute("name") 
                                                   into xAttribute 
                                                   where xAttribute != null && !string.IsNullOrEmpty(xAttribute.Value) 
                                                   select videoFilePath + "\\" + xAttribute.Value).ToList();

                    testCaseReportItem = new VideosItemReportModel(videoFilePaths);
                    break;
                case TestCaseReportItemType.PerfTestStep:
                    testCaseReportItem = new PerformanceReportItemReportModel(testCaseItemElement);
                    break;
                case TestCaseReportItemType.BugReport:
                    testCaseReportItem = new BugReportItemReportModel(testCaseItemElement.Attribute("path").Value);
                    break;
                case TestCaseReportItemType.Unknown:
                    testCaseReportItem = createGenericTestCaseReportItem(testCaseItemElement);
                    break;
                default:
                    break;
            }

            DateTime timeStamp;

            if (testCaseItemElement.Attribute("time_stamp") != null && 
                DateTime.TryParse(testCaseItemElement.Attribute("time_stamp").Value, out timeStamp))
            {
                testCaseReportItem.TimeStamp = timeStamp;
            }

            return testCaseReportItem;
        }

        private static TestStepReportModel parseTestStepReportElement(XElement testStepReportElement)
        {
            TestStepReportModel testStepReport = new TestStepReportModel
                {
                    Name = testStepReportElement.Attribute("name") != null ? testStepReportElement.Attribute("name").Value : ValueNotFoundText,
                    Id = testStepReportElement.Attribute("id") != null ? testStepReportElement.Attribute("id").Value : ValueNotFoundText,
                    Timeout = testStepReportElement.Attribute("timeout") != null ? int.Parse(testStepReportElement.Attribute("timeout").Value) : 0,
                    StepId = testStepReportElement.Attribute("stepId") != null ? testStepReportElement.Attribute("stepId").Value : ValueNotFoundText
                };

            foreach (XElement childElement in testStepReportElement.Elements())
            {
                parseTestStepReportChildItems(childElement, testStepReport);
            }

            return testStepReport;
        }

        private static void parseTestStepReportChildItems(XElement testStepReportElement, TestStepReportModel testStepReportModel)
        {
            testStepReportModel.Items.Add(createGenericTestStepItemReportItem(testStepReportElement));

            foreach (XElement childElement in testStepReportElement.Elements())
            {
                parseTestStepReportChildItems(childElement, testStepReportModel);
            }
        }

        private static TestCaseReportItemModel createGenericTestCaseReportItem(XElement testCaseItemElement)
        {
            StringBuilder itemText = new StringBuilder();

            itemText.AppendLine(testCaseItemElement.Name + " - " + testCaseItemElement.Value.ToString(CultureInfo.InvariantCulture));

            foreach (XAttribute attribute in testCaseItemElement.Attributes())
            {
                itemText.AppendLine(attribute.Name + ": " + attribute.Value.ToString(CultureInfo.InvariantCulture));
            }

            return new TestCaseReportItemModel() { Text = itemText.ToString() };
        }

        private static TestStepItemReportModel createGenericTestStepItemReportItem(XElement testStepItemReportItem)
        {
            TestStepItemReportModel testStepItemReport = new TestStepItemReportModel { Name = testStepItemReportItem.Name.ToString() };
            StringBuilder itemText = new StringBuilder();

            XAttribute idAttribute = testStepItemReportItem.Attribute("id");

            if (idAttribute != null) testStepItemReport.Id = idAttribute.Value;

            foreach (XAttribute attribute in testStepItemReportItem.Attributes().Where(attribute => attribute != idAttribute))
            {
                itemText.Append("[" + attribute.Name + ": " + attribute.Value.ToString(CultureInfo.InvariantCulture) + "] ");
            }

            testStepItemReport.Text = itemText.ToString();

            return testStepItemReport;
        }

        private static CaptureItemReportModel parseSummaryForCaptureReportItem(XElement summaryTestStepReportItem)
        {
            CaptureItemReportModel captureItemReport = new CaptureItemReportModel();
            XElement captureElement = null;

            foreach (XElement captureElementCandidate in summaryTestStepReportItem.Elements("capture"))
            {
                XAttribute idAttribute = captureElementCandidate.Attribute("id");

                if (idAttribute == null) continue;

                // Current specification of test result XML files have ID attribute with value of 4 which contain capture element table.
                if (idAttribute.Value == "4")
                {
                    captureElement = captureElementCandidate;
                    break;
                }
            }

            if (captureElement == null) return null;

            foreach (XElement element in captureElement.Elements())
            {
                if (element.Name == "bitmap")
                {
                    captureItemReport.CaptureBitmapFileName = captureElement.Element("bitmap").Attribute("name").Value;
                }
                else
                {
                    DisplayElement displayElement = new DisplayElement(element);
                    captureItemReport.DisplayElements.Add(displayElement);
                }
            }

            return captureItemReport;
        }

        /// <summary>
        /// Constructs correct path for the captured image. Result xml contains only filename or partial path of the image.
        /// </summary>
        /// <param name="captureFileName">Filename or path of the image from the result xml.</param>
        /// <param name="testResultFilePath">Path of the result xml.</param>
        /// <returns>Full path of the captured image.</returns>
        /// <example>testResultFilePath = "C:\\git_master\\GraniteGUI\\MainGUI\\bin\\test_sets\\GUI_tests_new_results\\xml\\Fails case_2.xml"
        /// newFilePath = "C:\\git_master\\GraniteGUI\\MainGUI\\bin\\test_sets\\GUI_tests_new_results\\error bitmaps\\error_bitmap_3.png"</example>
        private static string CreateFilePathFromCaptureFileName(string captureFileName, string testResultFilePath)
        {
            if (string.IsNullOrEmpty(captureFileName) || string.IsNullOrEmpty(testResultFilePath)) return null;

            // Normal capture
            if (captureFileName.ToLower().StartsWith("capture"))
                return Path.GetFullPath(Path.Combine(testResultFilePath, "..\\..", "captured bitmaps", captureFileName));

            // Error capture
            if (captureFileName.ToLower().StartsWith("error"))
                return Path.GetFullPath(Path.Combine(testResultFilePath, "..\\..", "error bitmaps", captureFileName));

            // Relative path
            if (!Path.IsPathRooted(captureFileName))
                return Path.GetFullPath(Path.Combine(testResultFilePath, "..", captureFileName));

            return null;
        }

        private static void findElementAttributeValuesRecursively(XElement element, string elementName, string attributeName, List<string> attributeValueList, bool allowSameValues = false)
        {
            if (element.Name.ToString() == elementName)
            {
                XAttribute attribute = element.Attribute(attributeName);

                if (attribute != null)
                {
                    if (allowSameValues)
                        attributeValueList.Add(attribute.Value);
                    else if (!attributeValueList.Contains(attribute.Value))
                        attributeValueList.Add(attribute.Value);
                }
            }

            foreach (XElement childElement in element.Elements())
            {
                findElementAttributeValuesRecursively(childElement, elementName, attributeName, attributeValueList);
            }
        }
    }
}
