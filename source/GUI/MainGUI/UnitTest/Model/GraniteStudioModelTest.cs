using System.Diagnostics;
using System.IO;
using System.Text;
using Granite.Model;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Drawing;
using System.Drawing.Imaging;

namespace Granite.UnitTest.Model
{
    /// <summary>
    ///This is a test class for GraniteStudioModelTest and is intended
    ///to contain all GraniteStudioModelTest Unit Tests
    ///</summary>
    [TestClass()]
    public class GraniteStudioModelTest
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
        ///A test for GraniteStudioModel Constructor
        ///</summary>
        [TestMethod()]
        public void GraniteStudioModelConstructorTest()
        {
            GraniteStudioModel target = new GraniteStudioModel();
        }

        /// <summary>
        ///A test for CleanUp
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void CleanUpTest()
        {
            GraniteStudioModel_Accessor target = new GraniteStudioModel_Accessor();
            target.CleanUp();
        }

        /// <summary>
        ///A test for DeleteDirectory
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void DeleteDirectoryTest()
        {
            // Create a directory
            string directory = Path.Combine(Path.GetTempPath(), "Directory001");
            Directory.CreateDirectory(directory);

            // Create a file in the directory and close it
            FileStream file = File.Create(Path.Combine(directory, "test.txt"));
            file.Dispose();

            GraniteStudioModel_Accessor.DeleteDirectory(directory);
            Assert.IsFalse(Directory.Exists(directory), "The '" + directory + "' should have been deleted.");
        }

        /// <summary>
        ///A test for DeleteFiles
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void DeleteFilesTest()
        {
            // Create a directory
            string directory = Path.Combine(Path.GetTempPath(), "Directory001");
            Directory.CreateDirectory(directory);

            // Create a file in the directory and close it
            string filePath = Path.Combine(directory, "test.txt");
            FileStream file = File.Create(filePath);
            file.Dispose();

            GraniteStudioModel_Accessor.DeleteFiles(directory);
            Assert.IsFalse(File.Exists(filePath), "The '" + filePath + "' file should have been deleted.");
        }

        /// <summary>
        ///A test for GetTemporaryDirectoryPath
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void GetTemporaryDirectoryPath()
        {
            // Get the temporary directory path
            string directory = GraniteStudioModel_Accessor.GetTemporaryDirectoryPath();
            Assert.IsFalse(string.IsNullOrEmpty(directory), "The temporary directory returned should not be a null or empty string.");
        }

        /// <summary>
        ///A test for CreateTemporaryDirectory
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void CreateTemporaryDirectory()
        {
            // Create the temporary directory
            string directory = GraniteStudioModel_Accessor.CreateTemporaryDirectory();
            Assert.IsFalse(string.IsNullOrEmpty(directory), "The temporary directory returned should not be a null or an empty string.");
            Assert.IsTrue(Directory.Exists(directory), "The '" + directory + "' should have been created.");

            // Delete the temporary directory
            Directory.Delete(directory);
        }

        /// <summary>
        ///A test for Dispose
        ///</summary>
        [TestMethod()]
        public void DisposeTest()
        {
            GraniteStudioModel target = new GraniteStudioModel();
            target.Dispose();
        }

        /// <summary>
        ///A test for Finalize
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void FinalizeTest()
        {
            GraniteStudioModel_Accessor target = new GraniteStudioModel_Accessor();
            target.Finalize();
        }

        /// <summary>
        ///A test for FlushXaml
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void FlushXamlTest()
        {
            GraniteStudioModel_Accessor target = new GraniteStudioModel_Accessor();
            target.FlushXaml();
        }

        /// <summary>
        ///A test for GetGraniteStudioFilePath
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void GetGraniteStudioFilePathTest()
        {
            string filePath = GraniteStudioModel_Accessor.GetGraniteStudioFilePath();
            Assert.IsFalse(string.IsNullOrEmpty(filePath), "The Studio file path should not be null or empty.");
        }

        /// <summary>
        ///A test for GetResultsDirectoryPath
        ///</summary>
        [TestMethod()]
        public void GetResultsDirectoryPathTest()
        {
            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                string directoryPath = target.GetResultsDirectoryPath();
                Assert.IsFalse(string.IsNullOrEmpty(directoryPath), "The Studio results directory path should not be null or empty.");
                Assert.IsTrue(Directory.Exists(directoryPath), "The '" + directoryPath + "' Studio results directory path should exist.");
                Assert.IsTrue(directoryPath.EndsWith(@"\"), "The '" + directoryPath + "' Studio results directory path should end with a '\' character since the Framework in IronPython expects this.");              
            }
        }

        /// <summary>
        ///A test for GetFrameworkResultsFilePath
        ///</summary>
        ///<remarks>This provides comprehensive testing of various scenarios, such as where the test case 
        ///has been created and the information in the XAML has subsequently been updated.</remarks>
        [TestMethod()]
        public void GetFrameworkResultsFilePathTest()
        {
            string xaml1 = @"<TestSequenceActivity mc:Ignorable=""sap"" DisplayName=""Studio Test 1"" Feature=""Feature Test 1"" sap:VirtualizedContainerService.HintSize=""200,99"" Name=""Name Test 1"" mva:VisualBasic.Settings=""Assembly references and imported namespaces serialized as XML namespaces"" StartFromIdle=""True"" Subarea=""Subarea Test 1"" xmlns=""clr-namespace:Granite.Studio.ActivityLibrary.Activities;assembly=Granite.Studio.ActivityLibrary"" xmlns:mc=""http://schemas.openxmlformats.org/markup-compatibility/2006"" xmlns:mva=""clr-namespace:Microsoft.VisualBasic.Activities;assembly=System.Activities"" xmlns:sap=""http://schemas.microsoft.com/netfx/2009/xaml/activities/presentation"" />";
            string xaml2 = @"<TestSequenceActivity mc:Ignorable=""sap"" DisplayName=""Studio Test 2"" Feature=""Feature Test 2"" sap:VirtualizedContainerService.HintSize=""200,99"" Name=""Name Test 2"" mva:VisualBasic.Settings=""Assembly references and imported namespaces serialized as XML namespaces"" StartFromIdle=""True"" Subarea=""Subarea Test 2"" xmlns=""clr-namespace:Granite.Studio.ActivityLibrary.Activities;assembly=Granite.Studio.ActivityLibrary"" xmlns:mc=""http://schemas.openxmlformats.org/markup-compatibility/2006"" xmlns:mva=""clr-namespace:Microsoft.VisualBasic.Activities;assembly=System.Activities"" xmlns:sap=""http://schemas.microsoft.com/netfx/2009/xaml/activities/presentation"" />";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                // Get the framework results file path before we have done any updates
                string frameworkResultsFilePath = target.GetFrameworkResultsFilePath();
                Assert.IsFalse(string.IsNullOrEmpty(frameworkResultsFilePath), "The framework results file path should not be null or empty.");
                Assert.IsFalse(string.IsNullOrEmpty(Path.GetFileNameWithoutExtension(frameworkResultsFilePath)), "The framework results file path should have a file name specified.");

                // Update the XAML with a new test case name and get the framework result file path
                target.Xaml = xaml1;
                frameworkResultsFilePath = target.GetFrameworkResultsFilePath();
                Assert.IsFalse(string.IsNullOrEmpty(frameworkResultsFilePath), "The framework results file path should not be null or empty.");
                
                // Verify the file name is the test case name
                string expected = "Name Test 1";
                string actual = Path.GetFileNameWithoutExtension(frameworkResultsFilePath);
                Assert.AreEqual(expected, actual, "Expected the framework result file name to be the same as the test case name.");

                // Get the Studio test case
                TestCase testCase = target.GetStudioTestCase();

                // Get the framework result file path
                frameworkResultsFilePath = target.GetFrameworkResultsFilePath();

                // Verify the file name is the test case name
                expected = "Name Test 1";
                actual = Path.GetFileNameWithoutExtension(frameworkResultsFilePath);
                Assert.AreEqual(expected, actual, "Expected the framework result file name to be the same as the test case name.");

                // Update the XAML with a new test case name and get the framework result file path
                target.Xaml = xaml2;
                frameworkResultsFilePath = target.GetFrameworkResultsFilePath();
                Assert.IsFalse(string.IsNullOrEmpty(frameworkResultsFilePath), "The framework results file path should not be null or empty.");

                // Verify the file name is the test case name from the test case that was created rather than the latest xaml
                expected = "Name Test 1";
                actual = Path.GetFileNameWithoutExtension(frameworkResultsFilePath);
                Assert.AreEqual(expected, actual, "Expected the framework result file name to be the same as the test case name that is specified in the test case rather than the XAML.");

                // Get the Studio test case
                testCase = target.GetStudioTestCase();

                // Get the framework result file path
                frameworkResultsFilePath = target.GetFrameworkResultsFilePath();

                // Verify the file name is the test case name from the test case that was created
                expected = "Name Test 2";
                actual = Path.GetFileNameWithoutExtension(frameworkResultsFilePath);
                Assert.AreEqual(expected, actual, "Expected the framework result file name to be the same as the test case name that is specified in the test case that was generated.");
            }
        }

        /// <summary>
        ///A test for GetStudioTestCase
        ///</summary>
        [TestMethod()]
        public void GetStudioTestCaseTest()
        {
            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                TestCase testCase = target.GetStudioTestCase();
                Assert.IsNotNull(testCase, "The Studio test case should not be null.");
                Assert.IsNotNull(testCase.Script, "The Studio test case script should not be null.");
                Assert.IsFalse(string.IsNullOrEmpty(testCase.Script.file), "The Studio test case script should have a file.");
                Assert.IsFalse(string.IsNullOrEmpty(testCase.Script.Directory), "The Studio test case script should have a directory.");
                Assert.IsFalse(string.IsNullOrEmpty(testCase.Name), "The Studio test case script should have a name.");
                Assert.IsFalse(string.IsNullOrEmpty(testCase.Feature), "The Studio test case script should have a feature.");
                Assert.IsFalse(string.IsNullOrEmpty(testCase.Subarea), "The Studio test case script should have a sub-area.");
                Assert.IsTrue(testCase.IsWhiteboxChecked, "The Studio test case should support white box testing.");
                Assert.IsFalse(testCase.IsBlackboxChecked, "The Studio test case should not support black box testing.");
                Assert.IsFalse(testCase.IsRunning, "The Studio test case should not be running.");
                Assert.IsTrue(testCase.IsRoot, "The Studio test case should be the root test case.");
                Assert.IsFalse(testCase.HasChildren, "The Studio test case should not have any children.");
                Assert.AreEqual(1, testCase.Level, "The Studio test case should have level set to 1 (i.e. root test case).");
            }
        }

        /// <summary>
        ///A test for CreateStudioTestCaseClone
        ///</summary>
        [TestMethod()]
        public void CreateStudioTestCaseCloneTest()
        {
            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                TestCase testCase = target.CreateStudioTestCaseClone();
                Assert.IsNotNull(testCase, "The Studio test case clone should not be null.");
                Assert.IsNotNull(testCase.Script, "The Studio test case script clone should not be null.");
                Assert.IsFalse(string.IsNullOrEmpty(testCase.Script.file), "The Studio test case script clone should have a file.");
                Assert.IsFalse(string.IsNullOrEmpty(testCase.Script.Directory), "The Studio test case script clone should have a directory.");
                Assert.IsFalse(string.IsNullOrEmpty(testCase.Name), "The Studio test case script clone should have a name.");
                Assert.IsFalse(string.IsNullOrEmpty(testCase.Feature), "The Studio test case script clone should have a feature.");
                Assert.IsFalse(string.IsNullOrEmpty(testCase.Subarea), "The Studio test case script clone should have a sub-area.");
                Assert.IsTrue(testCase.IsWhiteboxChecked, "The Studio test case clone should support white box testing.");
                Assert.IsFalse(testCase.IsBlackboxChecked, "The Studio test case clone should not support black box testing.");
                Assert.IsFalse(testCase.IsRunning, "The Studio test case clone should not be running.");
                Assert.IsTrue(testCase.IsRoot, "The Studio test case clone should be the root test case.");
                Assert.IsFalse(testCase.HasChildren, "The Studio test case clone should not have any children.");
                Assert.AreEqual(1, testCase.Level, "The Studio test case clone should have level set to 1 (i.e. root test case).");
            }
        }

        /// <summary>
        ///A test for IsStudioTestCase
        ///</summary>
        [TestMethod()]
        public void IsStudioTestCaseTest()
        {
            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                TestCase testCase = target.GetStudioTestCase();

                // Test a test case created by studio
                bool expected = true;
                bool actual = target.IsStudioTestCase(testCase);
                Assert.AreEqual(expected, actual, "The test case created by studio must be a studio test case.");

                // Test a test case that was not created by studio
                testCase = new TestCase("MyTest", new TestScript("MyClass", @"c:\temp", "test.ipy", "MyMethod"));
                expected = false;
                actual = target.IsStudioTestCase(testCase);
                Assert.AreEqual(expected, actual, "The test case created by this test should not be a studio test case.");
            }
        }

        /// <summary>
        ///A test for IsCurrentStudioTestCase
        ///</summary>
        [TestMethod()]
        public void IsCurrentStudioTestCaseTest()
        {
            string filePath = null;

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                TestCase testCase = target.GetStudioTestCase();

                // Test the test case created by studio
                bool expected = true;
                bool actual = target.IsCurrentStudioTestCase(testCase);
                Assert.AreEqual(expected, actual, "The test case created by studio must be the current studio test case.");

                // Test a test case that was not created by studio and is not a studio test
                testCase = new TestCase("MyTest", new TestScript("MyClass", @"c:\temp", "test.ipy", "MyMethod"));
                expected = false;
                actual = target.IsCurrentStudioTestCase(testCase);
                Assert.AreEqual(expected, actual, "The test case created by this test should not be the current studio test case.");

                TestCase studioTestCase = target.GetStudioTestCase();
                testCase = new TestCase("MyTest", new TestScript("MyClass", studioTestCase.Script.Directory.ToUpper(), studioTestCase.Script.file.ToLower(), "MyMethod"));
                expected = true;
                actual = target.IsCurrentStudioTestCase(testCase);
                Assert.AreEqual(expected, actual, "The test case created with the same directory and file name as the current studio test should be treated as the current studio test case.");

                filePath = Path.Combine(Path.GetTempPath(), string.Format("Test{0}{1}", Process.GetCurrentProcess().Id, GraniteStudioModel.TestFileExtension));
                target.Save(filePath);
                testCase = new TestCase("MyTest", new TestScript("MyClass", Path.GetDirectoryName(filePath), Path.GetFileName(filePath), null));
                expected = true;
                actual = target.IsCurrentStudioTestCase(testCase);
                Assert.AreEqual(expected, actual, "The test case created with the same directory and file name as the studio test case that was saved should be treated as the current studio test case.");
            }

            if (filePath != null)
            {
                if (File.Exists(filePath))
                {
                    File.Delete(filePath);
                }
            }
        }

        /// <summary>
        ///A test for the GetStudioTestCase attributes with updated XAML.
        ///</summary>
        [TestMethod()]
        public void GetStudioTestCaseAttributesTestWithUpdatedXaml()
        {
            string xaml = @"<TestSequenceActivity mc:Ignorable=""sap"" DisplayName=""Studio Test"" Feature=""FeatureTest"" sap:VirtualizedContainerService.HintSize=""200,99"" Name=""NameTest"" mva:VisualBasic.Settings=""Assembly references and imported namespaces serialized as XML namespaces"" StartFromIdle=""True"" Subarea=""SubareaTest"" xmlns=""clr-namespace:Granite.Studio.ActivityLibrary.Activities;assembly=Granite.Studio.ActivityLibrary"" xmlns:mc=""http://schemas.openxmlformats.org/markup-compatibility/2006"" xmlns:mva=""clr-namespace:Microsoft.VisualBasic.Activities;assembly=System.Activities"" xmlns:sap=""http://schemas.microsoft.com/netfx/2009/xaml/activities/presentation"" />";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                // Update the xaml
                target.Xaml = xaml;

                TestCase testCase = target.GetStudioTestCase();
                Assert.IsNotNull(testCase, "The Studio test case should not be null.");
                Assert.IsNotNull(testCase.Script, "The Studio test case script should not be null.");

                string expected = "NameTest";
                string actual = testCase.Name;
                Assert.AreEqual(expected, actual, "The test case name does not match that of the Name attribute in the supplied XAML.");

                expected = "FeatureTest";
                actual = testCase.Feature;
                Assert.AreEqual(expected, actual, "The test case feature does not match that of the Feature attribute in the supplied XAML.");

                expected = "SubareaTest";
                actual = testCase.Subarea;
                Assert.AreEqual(expected, actual, "The test case sub-area does not match that of the Subarea attribute in the supplied XAML.");
            }
        }

        /// <summary>
        ///A test for the GetStudioTestCase attributes with updated XAML after getting the test the first time.
        ///</summary>
        [TestMethod()]
        public void GetStudioTestCaseAttributesTestWithUpdatedXamlAfterGettingTest()
        {
            string xaml = @"<TestSequenceActivity mc:Ignorable=""sap"" DisplayName=""Studio Test"" Feature=""FeatureTest"" sap:VirtualizedContainerService.HintSize=""200,99"" Name=""NameTest"" mva:VisualBasic.Settings=""Assembly references and imported namespaces serialized as XML namespaces"" StartFromIdle=""True"" Subarea=""SubareaTest"" xmlns=""clr-namespace:Granite.Studio.ActivityLibrary.Activities;assembly=Granite.Studio.ActivityLibrary"" xmlns:mc=""http://schemas.openxmlformats.org/markup-compatibility/2006"" xmlns:mva=""clr-namespace:Microsoft.VisualBasic.Activities;assembly=System.Activities"" xmlns:sap=""http://schemas.microsoft.com/netfx/2009/xaml/activities/presentation"" />";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                TestCase testCase = target.GetStudioTestCase();
                Assert.IsNotNull(testCase, "The Studio test case should not be null.");
                Assert.IsNotNull(testCase.Script, "The Studio test case script should not be null.");

                Assert.IsFalse(string.IsNullOrEmpty(testCase.Name), "The default test case name should not be null or empty.");
                Assert.IsFalse(string.IsNullOrEmpty(testCase.Feature), "The default test case feature should not be null or empty.");
                Assert.IsFalse(string.IsNullOrEmpty(testCase.Subarea), "The default test case sub-area should not be null or empty.");

                // Update the xaml
                target.Xaml = xaml;

                testCase = target.GetStudioTestCase();
                Assert.IsNotNull(testCase, "The Studio test case should not be null.");
                Assert.IsNotNull(testCase.Script, "The Studio test case script should not be null.");

                string expected = "NameTest";
                string actual = testCase.Name;
                Assert.AreEqual(expected, actual, "The test case name does not match that of the Name attribute in the supplied XAML.");

                expected = "FeatureTest";
                actual = testCase.Feature;
                Assert.AreEqual(expected, actual, "The test case feature does not match that of the Feature attribute in the supplied XAML.");

                expected = "SubareaTest";
                actual = testCase.Subarea;
                Assert.AreEqual(expected, actual, "The test case sub-area does not match that of the Subarea attribute in the supplied XAML.");
            }
        }

        /// <summary>
        ///A test for GetXamlFilePath
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void GetXamlFilePathTest()
        {
            GraniteStudioModel_Accessor target = new GraniteStudioModel_Accessor();
            string filePath = target.GetXamlFilePath();
            Assert.IsFalse(string.IsNullOrEmpty(filePath), "The Studio XAML file path should not be null or empty.");
            Assert.IsTrue(Path.IsPathRooted(filePath), "The '" + filePath + "' Studio XAML file path should not be a relative file path.");
        }

        /// <summary>
        ///A test for Load
        ///</summary>
        [TestMethod()]
        public void LoadTest()
        {
            string xaml = @"<Sequence mc:Ignorable=""sap"" DisplayName=""Sequence"" sap:VirtualizedContainerService.HintSize=""200,99"" mva:VisualBasic.Settings=""Assembly references and imported namespaces serialized as XML namespaces"" xmlns=""http://schemas.microsoft.com/netfx/2009/xaml/activities"" xmlns:mc=""http://schemas.openxmlformats.org/markup-compatibility/2006"" xmlns:mva=""clr-namespace:Microsoft.VisualBasic.Activities;assembly=System.Activities"" xmlns:sap=""http://schemas.microsoft.com/netfx/2009/xaml/activities/presentation"" xmlns:scg=""clr-namespace:System.Collections.Generic;assembly=mscorlib"" xmlns:x=""http://schemas.microsoft.com/winfx/2006/xaml"">\r\n" +
                          @"  <sap:WorkflowViewStateService.ViewState>" +
                          @"    <scg:Dictionary x:TypeArguments=""x:String, x:Object"">" +
                          @"      <x:Boolean x:Key=""IsExpanded"">True</x:Boolean>" +
                          @"    </scg:Dictionary>" +
                          @"  </sap:WorkflowViewStateService.ViewState>" +
                          @"</Sequence>";

            // Create a workflow file
            string filePath = Path.GetTempFileName();

            try
            {
                using (StreamWriter writer = new StreamWriter(filePath, false, Encoding.UTF8))
                {
                    // Write the XAML to the file
                    writer.Write(xaml);
                }

                using (GraniteStudioModel target = new GraniteStudioModel())
                {
                    target.Load(filePath);
                }
            }

            finally
            {
                if (File.Exists(filePath))
                {
                    File.Delete(filePath);
                }
            }
        }

        /// <summary>
        ///A test for LoadXaml
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void LoadXamlTest()
        {
            string xaml = @"<Sequence mc:Ignorable=""sap"" DisplayName=""Sequence"" sap:VirtualizedContainerService.HintSize=""200,99"" mva:VisualBasic.Settings=""Assembly references and imported namespaces serialized as XML namespaces"" xmlns=""http://schemas.microsoft.com/netfx/2009/xaml/activities"" xmlns:mc=""http://schemas.openxmlformats.org/markup-compatibility/2006"" xmlns:mva=""clr-namespace:Microsoft.VisualBasic.Activities;assembly=System.Activities"" xmlns:sap=""http://schemas.microsoft.com/netfx/2009/xaml/activities/presentation"" xmlns:scg=""clr-namespace:System.Collections.Generic;assembly=mscorlib"" xmlns:x=""http://schemas.microsoft.com/winfx/2006/xaml"">\r\n" +
                          @"  <sap:WorkflowViewStateService.ViewState>" +
                          @"    <scg:Dictionary x:TypeArguments=""x:String, x:Object"">" +
                          @"      <x:Boolean x:Key=""IsExpanded"">True</x:Boolean>" +
                          @"    </scg:Dictionary>" +
                          @"  </sap:WorkflowViewStateService.ViewState>" +
                          @"</Sequence>";

            // Create a workflow file
            string filePath = Path.GetTempFileName();

            try
            {
                using (StreamWriter writer = new StreamWriter(filePath, false, Encoding.UTF8))
                {
                    // Write the XAML to the file
                    writer.Write(xaml);
                }

                string actual = GraniteStudioModel_Accessor.LoadXaml(filePath);
                Assert.AreEqual(xaml, actual, "Expected the XAML that was loaded to match the XAML that was originally written to the file.");
            }

            finally
            {
                if (File.Exists(filePath))
                {
                    File.Delete(filePath);
                }
            }
        }

        /// <summary>
        ///A test for Reset
        ///</summary>
        [TestMethod()]
        public void ResetTest()
        {
            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                // Reset all data
                target.Reset();
            }
        }

        /// <summary>
        ///A test for ResetPhoneDataTest
        ///</summary>
        [TestMethod()]
        public void ResetPhoneDataTest()
        {
            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                // Reset the phone data
                target.ResetPhoneData();

                // Create some phone data
                string filePath = target.MenuXmlFilePath;
                File.Create(filePath).Close();

                // Reset the phone data
                target.ResetPhoneData();

                Assert.IsFalse(File.Exists(filePath), "The phone data files should be deleted if we have reset the phone data.");
            }
        }

        /// <summary>
        ///A test for ResetXaml
        ///</summary>
        [TestMethod()]
        public void ResetXamlTest()
        {
            string xaml = @"<Sequence mc:Ignorable=""sap"" DisplayName=""Sequence"" sap:VirtualizedContainerService.HintSize=""200,99"" mva:VisualBasic.Settings=""Assembly references and imported namespaces serialized as XML namespaces"" xmlns=""http://schemas.microsoft.com/netfx/2009/xaml/activities"" xmlns:mc=""http://schemas.openxmlformats.org/markup-compatibility/2006"" xmlns:mva=""clr-namespace:Microsoft.VisualBasic.Activities;assembly=System.Activities"" xmlns:sap=""http://schemas.microsoft.com/netfx/2009/xaml/activities/presentation"" xmlns:scg=""clr-namespace:System.Collections.Generic;assembly=mscorlib"" xmlns:x=""http://schemas.microsoft.com/winfx/2006/xaml"">\r\n" +
                          @"  <sap:WorkflowViewStateService.ViewState>" +
                          @"    <scg:Dictionary x:TypeArguments=""x:String, x:Object"">" +
                          @"      <x:Boolean x:Key=""IsExpanded"">False</x:Boolean>" +
                          @"    </scg:Dictionary>" +
                          @"  </sap:WorkflowViewStateService.ViewState>" +
                          @"</Sequence>";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                // Initial test
                target.ResetXaml();

                // Change the XAML
                target.Xaml = xaml;

                // Reset the XAML
                target.ResetXaml();

                Assert.AreEqual(target.DefaultXaml, target.Xaml, "The XAML should have been reset back to the default.");
            }
        }

        /// <summary>
        ///A test for Reset supplying some default XAML.
        ///</summary>
        [TestMethod()]
        public void ResetWithDefaultXamlTest()
        {
            string expectedXaml = @"<Sequence mc:Ignorable=""sap"" DisplayName=""Sequence"" sap:VirtualizedContainerService.HintSize=""200,99"" mva:VisualBasic.Settings=""Assembly references and imported namespaces serialized as XML namespaces"" xmlns=""http://schemas.microsoft.com/netfx/2009/xaml/activities"" xmlns:mc=""http://schemas.openxmlformats.org/markup-compatibility/2006"" xmlns:mva=""clr-namespace:Microsoft.VisualBasic.Activities;assembly=System.Activities"" xmlns:sap=""http://schemas.microsoft.com/netfx/2009/xaml/activities/presentation"" xmlns:scg=""clr-namespace:System.Collections.Generic;assembly=mscorlib"" xmlns:x=""http://schemas.microsoft.com/winfx/2006/xaml"">\r\n" +
                                  @"  <sap:WorkflowViewStateService.ViewState>" +
                                  @"    <scg:Dictionary x:TypeArguments=""x:String, x:Object"">" +
                                  @"      <x:Boolean x:Key=""IsExpanded"">False</x:Boolean>" +
                                  @"    </scg:Dictionary>" +
                                  @"  </sap:WorkflowViewStateService.ViewState>" +
                                  @"</Sequence>";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                string actualXaml = target.Xaml;
                Assert.AreNotEqual(expectedXaml, actualXaml,
                                   "We are going to supply different XAML compared with the default XAML, so initially they should not match.");

                // Reset the default xaml
                target.ResetXaml(expectedXaml);
                actualXaml = target.Xaml;
                Assert.AreEqual(expectedXaml, actualXaml,
                                "If the default XAML has been updated then the model should return this new default XAML in the Xaml property.");
                Assert.AreEqual(expectedXaml, target.DefaultXaml,
                                "If the default XAML has been updated then the model should return this in the DefaultXaml property.");
            }
        }

        /// <summary>
        ///A test for Save
        ///</summary>
        [TestMethod()]
        public void SaveTest()
        {
            string filePath = Path.GetTempFileName();

            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                target.Save(filePath);
            }

            Assert.IsTrue(File.Exists(filePath), "Expected the Studio file to be created when saving.");

            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }
        }

        /// <summary>
        ///A test for CreateTestCase
        ///</summary>
        [TestMethod()]
        public void CreateTestCaseTest()
        {
            string filePath = Path.GetTempFileName();

            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }

            TestCase expected;

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                target.Save(filePath);
                expected = target.GetStudioTestCase();
            }

            // Create a test case from the file
            TestCase actual = GraniteStudioModel.CreateTestCase(filePath);
            Assert.IsNotNull(actual, "Expected to be able to create a test case from the Studio file that was saved.");
            Assert.AreEqual(expected.Name, actual.Name, "Expected the test case Name to match that of the test case that was saved.");
            Assert.AreEqual(expected.Feature, actual.Feature, "Expected the test case Feature to match that of the test case that was saved.");
            Assert.AreEqual(expected.Subarea, actual.Subarea, "Expected the test case Subarea to match that of the test case that was saved.");
            Assert.IsNotNull(actual.Script, "Expected to be able to create a test case with a Script from the Studio file that was saved.");
            Assert.AreEqual(expected.Script.Directory, actual.Script.Directory, "Expected the test case script Directory to match that of the test case that was saved.");
            Assert.AreEqual(expected.Script.file, actual.Script.file, "Expected the test case script File to match that of the test case that was saved.");

            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }
        }

        /// <summary>
        ///A test for SaveXaml
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void SaveXamlTest()
        {
            string filePath = Path.GetTempFileName();
            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }

            string xaml = @"<Sequence mc:Ignorable=""sap"" DisplayName=""Sequence"" sap:VirtualizedContainerService.HintSize=""200,99"" mva:VisualBasic.Settings=""Assembly references and imported namespaces serialized as XML namespaces"" xmlns=""http://schemas.microsoft.com/netfx/2009/xaml/activities"" xmlns:mc=""http://schemas.openxmlformats.org/markup-compatibility/2006"" xmlns:mva=""clr-namespace:Microsoft.VisualBasic.Activities;assembly=System.Activities"" xmlns:sap=""http://schemas.microsoft.com/netfx/2009/xaml/activities/presentation"" xmlns:scg=""clr-namespace:System.Collections.Generic;assembly=mscorlib"" xmlns:x=""http://schemas.microsoft.com/winfx/2006/xaml"">\r\n" +
                          @"  <sap:WorkflowViewStateService.ViewState>" +
                          @"    <scg:Dictionary x:TypeArguments=""x:String, x:Object"">" +
                          @"      <x:Boolean x:Key=""IsExpanded"">True</x:Boolean>" +
                          @"    </scg:Dictionary>" +
                          @"  </sap:WorkflowViewStateService.ViewState>" +
                          @"</Sequence>";
            GraniteStudioModel_Accessor.SaveXaml(filePath, xaml);

            Assert.IsTrue(File.Exists(filePath), "Expected the Studio file to be created when saving the XAML.");

            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }
        }

        /// <summary>
        ///A test for SaveXamlToTemporaryFile
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void SaveXamlToTemporaryFileTest()
        {
            GraniteStudioModel_Accessor target = new GraniteStudioModel_Accessor();
            target.SaveXamlToTemporaryFile();

            Assert.IsFalse(string.IsNullOrEmpty(target._xamlTemporaryFilePath), "Expected the XAML temporary file path to be updated after saving the XAML to a temporary file.");
            Assert.IsTrue(File.Exists(target._xamlTemporaryFilePath), "Expected the XAML temporary file to exist after saving the XAML to a temporary file, but the '" + target._xamlTemporaryFilePath + "' file does not exist.");

            if (File.Exists(target._xamlTemporaryFilePath))
            {
                File.Delete(target._xamlTemporaryFilePath);
            }
        }

        /// <summary>
        ///A test for IsDirty
        ///</summary>
        [TestMethod()]
        public void IsDirtyTest()
        {
            string xaml = @"<Sequence mc:Ignorable=""sap"" DisplayName=""Sequence"" sap:VirtualizedContainerService.HintSize=""200,99"" mva:VisualBasic.Settings=""Assembly references and imported namespaces serialized as XML namespaces"" xmlns=""http://schemas.microsoft.com/netfx/2009/xaml/activities"" xmlns:mc=""http://schemas.openxmlformats.org/markup-compatibility/2006"" xmlns:mva=""clr-namespace:Microsoft.VisualBasic.Activities;assembly=System.Activities"" xmlns:sap=""http://schemas.microsoft.com/netfx/2009/xaml/activities/presentation"" xmlns:scg=""clr-namespace:System.Collections.Generic;assembly=mscorlib"" xmlns:x=""http://schemas.microsoft.com/winfx/2006/xaml"">\r\n" +
                          @"  <sap:WorkflowViewStateService.ViewState>" +
                          @"    <scg:Dictionary x:TypeArguments=""x:String, x:Object"">" +
                          @"      <x:Boolean x:Key=""IsExpanded"">True</x:Boolean>" +
                          @"    </scg:Dictionary>" +
                          @"  </sap:WorkflowViewStateService.ViewState>" +
                          @"  <Sequence />" +
                          @"</Sequence>";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                bool expected = false;
                bool actual = target.IsDirty;
                Assert.AreEqual(expected, actual, "Initially since there have been no changes made, the model data should not be dirty.");

                // Modify the XAML
                target.Xaml = xaml;

                expected = true;
                actual = target.IsDirty;
                Assert.AreEqual(expected, actual, "After changing the XAML the model data should be dirty.");
            }
        }

        /// <summary>
        ///A test for OnPropertyChanged
        ///</summary>
        [TestMethod()]
        public void OnPropertyChangedTest()
        {
            string xaml = @"<Sequence mc:Ignorable=""sap"" DisplayName=""Sequence"" sap:VirtualizedContainerService.HintSize=""200,99"" mva:VisualBasic.Settings=""Assembly references and imported namespaces serialized as XML namespaces"" xmlns=""http://schemas.microsoft.com/netfx/2009/xaml/activities"" xmlns:mc=""http://schemas.openxmlformats.org/markup-compatibility/2006"" xmlns:mva=""clr-namespace:Microsoft.VisualBasic.Activities;assembly=System.Activities"" xmlns:sap=""http://schemas.microsoft.com/netfx/2009/xaml/activities/presentation"" xmlns:scg=""clr-namespace:System.Collections.Generic;assembly=mscorlib"" xmlns:x=""http://schemas.microsoft.com/winfx/2006/xaml"">\r\n" +
                          @"  <sap:WorkflowViewStateService.ViewState>" +
                          @"    <scg:Dictionary x:TypeArguments=""x:String, x:Object"">" +
                          @"      <x:Boolean x:Key=""IsExpanded"">True</x:Boolean>" +
                          @"    </scg:Dictionary>" +
                          @"  </sap:WorkflowViewStateService.ViewState>" +
                          @"  <Sequence />" +
                          @"</Sequence>";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                bool xamlPropertyChanged = false;

                target.PropertyChanged += (sender, args) => 
                {
                    if (args.PropertyName == "Xaml")
                    {
                        xamlPropertyChanged = true;
                    }
                };

                // Modify the XAML
                target.Xaml = xaml;

                bool expected = true;
                Assert.AreEqual(expected, xamlPropertyChanged, "When modifying the XAML, a property changed event should have been generated.");
            }
        }

        /// <summary>
        ///A test for TestFileExtension
        ///</summary>
        [TestMethod()]
        public void TestFileExtensionTest()
        {
            string testFileExtension = GraniteStudioModel.TestFileExtension;
            Assert.IsFalse(string.IsNullOrEmpty(testFileExtension), "The Studio test file extension should not be null or empty.");
        }

        /// <summary>
        ///A test for TestFilePath
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void TestFilePathTest()
        {
            string filePath = Path.GetTempFileName();
            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                string testFilePath = target.TestFilePath;
                Assert.IsNull(testFilePath, "Initially when no Studio XAML test file has been saved, the test file path should be null.");

                // Save the Studio test case
                target.Save(filePath);

                testFilePath = target.TestFilePath;
                Assert.AreSame(filePath, testFilePath, "After saving the Studio XAML test file, the test file path property should match the file path used when saving.");
            }

            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }
        }

        /// <summary>
        ///A test for UseTemporaryXamlFilePath
        ///</summary>
        [TestMethod()]
        [DeploymentItem("Granite.exe")]
        public void UseTemporaryXamlFilePathTest()
        {
            string filePath = Path.GetTempFileName();
            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }

            GraniteStudioModel_Accessor target = new GraniteStudioModel_Accessor();
            bool expected = true;
            bool actual = target.UseTemporaryXamlFilePath;
            Assert.AreEqual(expected, actual, "Initially the Studio model should use a temporary XAML file path.");

            // Save the Studio test case
            target.Save(filePath);

            expected = false;
            actual = target.UseTemporaryXamlFilePath;
            Assert.AreEqual(expected, actual, "After saving the XAML the Studio model should no longer use a temporary XAML file path.");

            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }
        }

        /// <summary>
        ///A test for Xaml
        ///</summary>
        [TestMethod()]
        public void XamlTest()
        {
            string xaml = @"<Sequence mc:Ignorable=""sap"" DisplayName=""Sequence"" sap:VirtualizedContainerService.HintSize=""200,99"" mva:VisualBasic.Settings=""Assembly references and imported namespaces serialized as XML namespaces"" xmlns=""http://schemas.microsoft.com/netfx/2009/xaml/activities"" xmlns:mc=""http://schemas.openxmlformats.org/markup-compatibility/2006"" xmlns:mva=""clr-namespace:Microsoft.VisualBasic.Activities;assembly=System.Activities"" xmlns:sap=""http://schemas.microsoft.com/netfx/2009/xaml/activities/presentation"" xmlns:scg=""clr-namespace:System.Collections.Generic;assembly=mscorlib"" xmlns:x=""http://schemas.microsoft.com/winfx/2006/xaml"">\r\n" +
                          @"  <sap:WorkflowViewStateService.ViewState>" +
                          @"    <scg:Dictionary x:TypeArguments=""x:String, x:Object"">" +
                          @"      <x:Boolean x:Key=""IsExpanded"">True</x:Boolean>" +
                          @"    </scg:Dictionary>" +
                          @"  </sap:WorkflowViewStateService.ViewState>" +
                          @"  <Sequence />" +
                          @"</Sequence>";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                string actual = target.Xaml;
                Assert.IsFalse(string.IsNullOrEmpty(actual), "Initially the Studio model should have valid default XAML.");

                bool propertyChanged = false;
                target.PropertyChanged += (s, e) =>
                {
                    if (e.PropertyName == "Xaml")
                    {
                        propertyChanged = true;
                    }
                };

                // Update the XAML
                propertyChanged = false;
                target.Xaml = xaml;

                actual = target.Xaml;
                Assert.AreEqual(xaml, actual, "The Studio model XAML property should return the same XAML string as what it was set to.");
                Assert.IsTrue(propertyChanged, "The Studio model XAML property should have changed.");

                // Update the XAML to the same value as before
                propertyChanged = false;
                target.Xaml = xaml;

                actual = target.Xaml;
                Assert.AreEqual(xaml, actual, "The Studio model XAML property should still return the same XAML string as what it was set to.");
                Assert.IsFalse(propertyChanged, "The Studio model XAML property should not have changed since it was set to the same value as before.");
            }
        }

        /// <summary>
        ///A test for State.
        ///</summary>
        [TestMethod()]
        public void StateTest()
        {
            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                StudioState expected = StudioState.Idle;
                StudioState actual = target.State;
                Assert.AreEqual(expected, actual, "Initially the Studio model should be in the " + expected.ToString() + " state.");

                bool propertyChanged = false;
                target.PropertyChanged += (s, e) =>
                {
                    if (e.PropertyName == "State")
                    {
                        propertyChanged = true;
                    }
                };

                propertyChanged = false;
                expected = StudioState.RefreshingPhoneData;
                target.State = StudioState.RefreshingPhoneData;
                actual = target.State;
                Assert.AreEqual(expected, actual, "The Studio model state should have changed to the " + expected.ToString() + " state.");
                Assert.IsTrue(propertyChanged , "The Studio model state property should have changed.");

                propertyChanged = false;
                expected = StudioState.RunningTest;
                target.State = StudioState.RunningTest;
                actual = target.State;
                Assert.AreEqual(expected, actual, "The Studio model state should have changed to the " + expected.ToString() + " state.");
                Assert.IsTrue(propertyChanged , "The Studio model state property should have changed.");

                propertyChanged = false;
                expected = StudioState.Idle;
                target.State = StudioState.Idle;
                actual = target.State;
                Assert.AreEqual(expected, actual, "The Studio model state should have changed to the " + expected.ToString() + " state.");
                Assert.IsTrue(propertyChanged , "The Studio model state property should have changed.");

                propertyChanged = false;
                expected = StudioState.Idle;
                target.State = StudioState.Idle;
                actual = target.State;
                Assert.AreEqual(expected, actual, "The Studio model state should still be in the " + expected.ToString() + " state.");
                Assert.IsFalse(propertyChanged, "The Studio model state property should not have changed since it was set to the same value as before.");
            }
        }

        /// <summary>
        ///A test for RefreshPhoneData
        ///</summary>
        [TestMethod()]
        public void RefreshPhoneDataTest()
        {
            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                target.RefreshPhoneData();
            }
        }

        /// <summary>
        ///A test for RefreshPhoneDataRequired
        ///</summary>
        [TestMethod()]
        public void RefreshPhoneDataRequiredTest()
        {
            string invalidMenuXml = @"<?xml version=""1.0"" encoding=""utf-8""?>" +
                                    @"<teststep>" +
                                    @"  <capture>" +
                                    @"    <xml>#void</xml>" +
                                    @"  </capture>" +
                                    @"</teststep>";

            string validMenuXml = @"<?xml version=""1.0"" encoding=""utf-8""?>" +
                                   @"<teststep>" +
                                   @"  <capture>" +
                                   @"    <xml>" +
                                   @"      <mainmenu>" +
                                   @"        <item name=""contact-list"" title=""Contacts"" uri=""x-contacts:list"" />" +
                                   @"        <item name=""calendar-nokia"" title=""Calendar"" uri=""x-calendar-nokia:"" />" +
                                   @"        <item name=""conversations"" title=""Messages"" uri=""x-messaging:threads"" />" +
                                   @"      </mainmenu>" +
                                   @"    </xml>" +
                                   @"  </capture>" +
                                   @"</teststep>";

            string validCaptureXml = @"<?xml-stylesheet type='text/xsl' href='../xslt/test_report_xml_to_html.xslt'?>" +
                                     @"<testreport test_group_filter="""" time=""19:50:17"" date=""2012-06-13"" author=""mfreed"">" +
                                     @"  <product name=""S40 eVo"" main_display=""MD240X320"" imei=""004402133756902"">" +
                                     @"    <version type=""sw"">Vp gadCEX1215_01" +
                                     @"11-04-12" +
                                     @"RM-766" +
                                     @"(c) Nokia   </version>" +
                                     @"    <version type=""hw"">not available</version>" +
                                     @"    <version type=""granite server"">1.001</version>" +
                                     @"  </product>" +
                                     @"  <testcase result=""Passed"" id=""capture.xml"" type=""scripted"" date=""2012-06-13"" time=""19:50:19"" subarea=""Display"" feature=""Capture"">" +
                                     @"    <description title=""Test case for taking phone display capture"">Test case for taking phone display capture</description>" +
                                     @"    <teststep name=""'phone_display_capture'"" timeout=""10000"" id=""1"" stepId=""1"">" +
                                     @"      <config max_isi_data_length=""49152"" bitmap_capture=""yes"" keypress_wait=""100"" keypress_length=""100"" background=""no"" id=""2"" />" +
                                     @"      <sx id=""3"">dump</sx>" +
                                     @"      <capture name=""phone_display_capture"" id=""4"" />" +
                                     @"    </teststep>" +
                                     @"    <summary id=""1"" name=""'phone_display_capture'"" stepId=""1"">" +
                                     @"      <capture>" +
                                     @"        <xml>" +
                                     @"          <container name=""primary-root-container"" coords=""0,0,240,320"" alignments=""start,start"" autosize=""false,false"" visible=""true"" handled-touch-events="""" has-local-focus=""false"" has-global-focus=""false"">" +
                                     @"            <stacked-container name=""subroot"" coords=""0,0,240,320"" alignments=""start,start"" autosize=""false,false"" visible=""true"" handled-touch-events="""" has-local-focus=""true"" has-global-focus=""false"">" +
                                     @"            </stacked-container>" +
                                     @"          </container>" +
                                     @"        </xml>" +
                                     @"      </capture>" +
                                     @"      <capture id=""4"">" +
                                     @"        <bitmap format=""13"" little_endian_cpu=""yes"" screen=""1"" x=""0"" y=""0"" width=""240"" height=""320"" background=""no"" name=""capture_1.png"" />" +
                                     @"        <animation name=""evo_menu_grid_radio.png"" x=""12"" y=""304"" width=""56"" height=""56"" />" +
                                     @"        <animation name=""evo_menu_grid_settings.png"" x=""92"" y=""304"" width=""56"" height=""56"" />" +
                                     @"        <animation name=""evo_menu_grid_filemanager.png"" x=""172"" y=""304"" width=""56"" height=""56"" />" +
                                     @"        <animation name=""evo_options_breathing_line.png"" x=""0"" y=""310"" width=""240"" height=""10"" />" +
                                     @"        <animation name=""evo_status_signals_4.png"" x=""0"" y=""4"" width=""14"" height=""10"" />" +
                                     @"        <animation name=""evo_status_simcard1.png"" x=""16"" y=""4"" width=""15"" height=""10"" />" +
                                     @"        <animation name=""evo_status_simcard2.png"" x=""49"" y=""4"" width=""15"" height=""10"" />" +
                                     @"        <animation name=""normal.png"" x=""66"" y=""1"" width=""15"" height=""15"" />" +
                                     @"        <animation name=""memory_card.png"" x=""83"" y=""1"" width=""15"" height=""15"" />" +
                                     @"        <animation name=""qgn_stat_edge.png"" x=""161"" y=""4"" width=""24"" height=""10"" />" +
                                     @"        <animation name=""evo_status_battery_100.png"" x=""187"" y=""4"" width=""15"" height=""10"" />" +
                                     @"        <text x=""4"" y=""94"" width=""72"" height=""20"">Contacts</text>" +
                                     @"        <text x=""84"" y=""94"" width=""72"" height=""20"">Calendar</text>" +
                                     @"        <text x=""164"" y=""94"" width=""72"" height=""20"">Messages</text>" +
                                     @"        <text x=""4"" y=""185"" width=""72"" height=""20"">Phone</text>" +
                                     @"        <text x=""84"" y=""185"" width=""72"" height=""20"">Camera</text>" +
                                     @"        <text x=""164"" y=""185"" width=""72"" height=""20"">Music</text>" +
                                     @"        <text x=""4"" y=""276"" width=""72"" height=""20"">Calculator</text>" +
                                     @"        <text x=""84"" y=""276"" width=""72"" height=""20"">Clock</text>" +
                                     @"        <text x=""164"" y=""276"" width=""72"" height=""20"">Countdown</text>" +
                                     @"        <text x=""204"" y=""-1"" width=""36"" height=""20"">12:47</text>" +
                                     @"      </capture>" +
                                     @"    </summary>" +
                                     @"  </testcase>" +
                                     @"  <summary>Ran 1 tests in 2.835 s </summary>" +
                                     @"</testreport>";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                bool expected = true;
                bool actual = target.RefreshPhoneDataRequired;
                Assert.AreEqual(expected, actual, "Initially a refresh of the phone data should be required.");

                // Refresh the phone data
                target.RefreshPhoneData();

                // We still expect a refresh of the phone data to be required since no framework files exists
                expected = true;
                actual = target.RefreshPhoneDataRequired;
                Assert.AreEqual(expected, actual, "We expect a refresh of the phone data to be required after performing the refresh, since no framework files exists.");

                // Create the menu file with invalid data
                File.WriteAllText(target.MenuXmlFilePath, invalidMenuXml);

                // Refresh the phone data
                target.RefreshPhoneData();

                // We still expect a refresh of the phone data to be required since an invalid menu file was created
                expected = true;
                actual = target.RefreshPhoneDataRequired;
                Assert.AreEqual(expected, actual, "We expect a refresh of the phone data to be required since we supplied an invalid menu framework file.");

                // Note: 
                // If additional framework data is require we will need to generate sample
                // files for all framework files.

                // Create the menu file with valid data
                File.WriteAllText(target.MenuXmlFilePath, validMenuXml);

                // Create the capture file with valid data
                File.WriteAllText(target.CaptureXmlFilePath, validCaptureXml);

                // Refresh the phone data
                target.RefreshPhoneData();

                // We expect a refresh of the phone data to be required since the capture data is currently always considered to be out-of-date
                expected = true;
                actual = target.RefreshPhoneDataRequired;
                Assert.AreEqual(expected, actual, "We expect a refresh of the phone data to be required since the phone display element data is always considered out-of-date since the user may change the phone display.");
            }
        }

        /// <summary>
        ///A test for PhoneMenuTitles
        ///</summary>
        [TestMethod()]
        public void PhoneMenuTitlesTest()
        {
            string invalidMenuXml = @"<?xml version=""1.0"" encoding=""utf-8""?>" +
                                    @"<teststep>" +
                                    @"  <capture>" +
                                    @"    <xml>#void</xml>" +
                                    @"  </capture>" +
                                    @"</teststep>";

            string validMenuXml = @"<?xml version=""1.0"" encoding=""utf-8""?>" +
                                   @"<teststep>" +
                                   @"  <capture>" +
                                   @"    <xml>" +
                                   @"      <mainmenu>" +
                                   @"        <item name=""contact-list"" title=""Contacts"" uri=""x-contacts:list"" />" +
                                   @"        <item name=""calendar-nokia"" title=""Calendar"" uri=""x-calendar-nokia:"" />" +
                                   @"        <item name=""conversations"" title=""Messages"" uri=""x-messaging:threads"" />" +
                                   @"      </mainmenu>" +
                                   @"    </xml>" +
                                   @"  </capture>" +
                                   @"</teststep>";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                // Initially try and get the phone menu titles
                var phoneMenuTitles = target.PhoneMenuTitles;

                // Create the menu file with invalid data
                File.WriteAllText(target.MenuXmlFilePath, invalidMenuXml);

                // Refresh the phone data
                target.RefreshPhoneData();

                // Get the phone menu titles
                phoneMenuTitles = target.PhoneMenuTitles;
                Assert.IsTrue(phoneMenuTitles == null || phoneMenuTitles.Count == 0, "There should be no phone menu titles if we have written invalid menu XML data.");

                // Create the menu file with valid data
                File.WriteAllText(target.MenuXmlFilePath, validMenuXml);

                // Refresh the phone data
                target.RefreshPhoneData();

                // Get the phone menu titles
                phoneMenuTitles = target.PhoneMenuTitles;
                Assert.IsNotNull(phoneMenuTitles, "There should be phone menu titles if we have written valid menu XML data.");

                int expected = 3;
                int actual = phoneMenuTitles.Count;
                Assert.AreEqual(expected, actual, "The number of titles should match the menu XML data we have written.");
            }
        }

        /// <summary>
        ///A test for PhoneDisplayTextElements
        ///</summary>
        [TestMethod()]
        public void PhoneDisplayTextElementsTest()
        {
            string validCaptureXml = @"<?xml-stylesheet type='text/xsl' href='../xslt/test_report_xml_to_html.xslt'?>" +
                                     @"<testreport test_group_filter="""" time=""19:50:17"" date=""2012-06-13"" author=""mfreed"">" +
                                     @"  <product name=""S40 eVo"" main_display=""MD240X320"" imei=""004402133756902"">" +
                                     @"    <version type=""sw"">Vp gadCEX1215_01" +
                                     @"11-04-12" +
                                     @"RM-766" +
                                     @"(c) Nokia   </version>" +
                                     @"    <version type=""hw"">not available</version>" +
                                     @"    <version type=""granite server"">1.001</version>" +
                                     @"  </product>" +
                                     @"  <testcase result=""Passed"" id=""capture.xml"" type=""scripted"" date=""2012-06-13"" time=""19:50:19"" subarea=""Display"" feature=""Capture"">" +
                                     @"    <description title=""Test case for taking phone display capture"">Test case for taking phone display capture</description>" +
                                     @"    <teststep name=""'phone_display_capture'"" timeout=""10000"" id=""1"" stepId=""1"">" +
                                     @"      <config max_isi_data_length=""49152"" bitmap_capture=""yes"" keypress_wait=""100"" keypress_length=""100"" background=""no"" id=""2"" />" +
                                     @"      <sx id=""3"">dump</sx>" +
                                     @"      <capture name=""phone_display_capture"" id=""4"" />" +
                                     @"    </teststep>" +
                                     @"    <summary id=""1"" name=""'phone_display_capture'"" stepId=""1"">" +
                                     @"      <capture>" +
                                     @"        <xml>" +
                                     @"          <container name=""primary-root-container"" coords=""0,0,240,320"" alignments=""start,start"" autosize=""false,false"" visible=""true"" handled-touch-events="""" has-local-focus=""false"" has-global-focus=""false"">" +
                                     @"            <stacked-container name=""subroot"" coords=""0,0,240,320"" alignments=""start,start"" autosize=""false,false"" visible=""true"" handled-touch-events="""" has-local-focus=""true"" has-global-focus=""false"">" +
                                     @"            </stacked-container>" +
                                     @"          </container>" +
                                     @"        </xml>" +
                                     @"      </capture>" +
                                     @"      <capture id=""4"">" +
                                     @"        <bitmap format=""13"" little_endian_cpu=""yes"" screen=""1"" x=""0"" y=""0"" width=""240"" height=""320"" background=""no"" name=""capture_1.png"" />" +
                                     @"        <animation name=""evo_menu_grid_radio.png"" x=""12"" y=""304"" width=""56"" height=""56"" />" +
                                     @"        <animation name=""evo_menu_grid_settings.png"" x=""92"" y=""304"" width=""56"" height=""56"" />" +
                                     @"        <animation name=""evo_menu_grid_filemanager.png"" x=""172"" y=""304"" width=""56"" height=""56"" />" +
                                     @"        <animation name=""evo_options_breathing_line.png"" x=""0"" y=""310"" width=""240"" height=""10"" />" +
                                     @"        <animation name=""evo_status_signals_4.png"" x=""0"" y=""4"" width=""14"" height=""10"" />" +
                                     @"        <animation name=""evo_status_simcard1.png"" x=""16"" y=""4"" width=""15"" height=""10"" />" +
                                     @"        <animation name=""evo_status_simcard2.png"" x=""49"" y=""4"" width=""15"" height=""10"" />" +
                                     @"        <animation name=""normal.png"" x=""66"" y=""1"" width=""15"" height=""15"" />" +
                                     @"        <animation name=""memory_card.png"" x=""83"" y=""1"" width=""15"" height=""15"" />" +
                                     @"        <animation name=""qgn_stat_edge.png"" x=""161"" y=""4"" width=""24"" height=""10"" />" +
                                     @"        <animation name=""evo_status_battery_100.png"" x=""187"" y=""4"" width=""15"" height=""10"" />" +
                                     @"        <text x=""4"" y=""94"" width=""72"" height=""20"">Contacts</text>" +
                                     @"        <text x=""84"" y=""94"" width=""72"" height=""20"">Calendar</text>" +
                                     @"        <text x=""164"" y=""94"" width=""72"" height=""20"">Messages</text>" +
                                     @"        <text x=""4"" y=""185"" width=""72"" height=""20"">Phone</text>" +
                                     @"        <text x=""84"" y=""185"" width=""72"" height=""20"">Camera</text>" +
                                     @"        <text x=""164"" y=""185"" width=""72"" height=""20"">Music</text>" +
                                     @"        <text x=""4"" y=""276"" width=""72"" height=""20"">Calculator</text>" +
                                     @"        <text x=""84"" y=""276"" width=""72"" height=""20"">Clock</text>" +
                                     @"        <text x=""164"" y=""276"" width=""72"" height=""20"">Countdown</text>" +
                                     @"        <text x=""204"" y=""-1"" width=""36"" height=""20"">12:47</text>" +
                                     @"      </capture>" +
                                     @"    </summary>" +
                                     @"  </testcase>" +
                                     @"  <summary>Ran 1 tests in 2.835 s </summary>" +
                                     @"</testreport>";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                // Initially try and get the phone display text elements
                var phoneDisplayTextElements = target.PhoneDisplayTextElements;
                Assert.IsTrue(phoneDisplayTextElements == null || phoneDisplayTextElements.Count == 0, "There should be no phone display text elements initially.");

                // Refresh the phone data
                target.RefreshPhoneData();

                // Try and get the phone display text elements
                phoneDisplayTextElements = target.PhoneDisplayTextElements;
                Assert.IsTrue(phoneDisplayTextElements == null || phoneDisplayTextElements.Count == 0, "There should be no phone display text if there is no capture XML file.");

                // Create the capture file with valid data
                File.WriteAllText(target.CaptureXmlFilePath, validCaptureXml);

                // Refresh the phone data
                target.RefreshPhoneData();

                // Get the phone display text elements
                phoneDisplayTextElements = target.PhoneDisplayTextElements;
                Assert.IsNotNull(phoneDisplayTextElements, "There should be phone display text elements if we have written valid capture XML data.");

                int expected = 10;
                int actual = phoneDisplayTextElements.Count;
                Assert.AreEqual(expected, actual, "The number of phone display text elements should match the capture XML data we have written.");
            }
        }

        /// <summary>
        ///A test for PhoneDisplayAnimationElements
        ///</summary>
        [TestMethod()]
        public void PhoneDisplayAnimationElementsTest()
        {
            string validCaptureXml = @"<?xml-stylesheet type='text/xsl' href='../xslt/test_report_xml_to_html.xslt'?>" +
                                     @"<testreport test_group_filter="""" time=""19:50:17"" date=""2012-06-13"" author=""mfreed"">" +
                                     @"  <product name=""S40 eVo"" main_display=""MD240X320"" imei=""004402133756902"">" +
                                     @"    <version type=""sw"">Vp gadCEX1215_01" +
                                     @"11-04-12" +
                                     @"RM-766" +
                                     @"(c) Nokia   </version>" +
                                     @"    <version type=""hw"">not available</version>" +
                                     @"    <version type=""granite server"">1.001</version>" +
                                     @"  </product>" +
                                     @"  <testcase result=""Passed"" id=""capture.xml"" type=""scripted"" date=""2012-06-13"" time=""19:50:19"" subarea=""Display"" feature=""Capture"">" +
                                     @"    <description title=""Test case for taking phone display capture"">Test case for taking phone display capture</description>" +
                                     @"    <teststep name=""'phone_display_capture'"" timeout=""10000"" id=""1"" stepId=""1"">" +
                                     @"      <config max_isi_data_length=""49152"" bitmap_capture=""yes"" keypress_wait=""100"" keypress_length=""100"" background=""no"" id=""2"" />" +
                                     @"      <sx id=""3"">dump</sx>" +
                                     @"      <capture name=""phone_display_capture"" id=""4"" />" +
                                     @"    </teststep>" +
                                     @"    <summary id=""1"" name=""'phone_display_capture'"" stepId=""1"">" +
                                     @"      <capture>" +
                                     @"        <xml>" +
                                     @"          <container name=""primary-root-container"" coords=""0,0,240,320"" alignments=""start,start"" autosize=""false,false"" visible=""true"" handled-touch-events="""" has-local-focus=""false"" has-global-focus=""false"">" +
                                     @"            <stacked-container name=""subroot"" coords=""0,0,240,320"" alignments=""start,start"" autosize=""false,false"" visible=""true"" handled-touch-events="""" has-local-focus=""true"" has-global-focus=""false"">" +
                                     @"            </stacked-container>" +
                                     @"          </container>" +
                                     @"        </xml>" +
                                     @"      </capture>" +
                                     @"      <capture id=""4"">" +
                                     @"        <bitmap format=""13"" little_endian_cpu=""yes"" screen=""1"" x=""0"" y=""0"" width=""240"" height=""320"" background=""no"" name=""capture_1.png"" />" +
                                     @"        <animation name=""evo_menu_grid_radio.png"" x=""12"" y=""304"" width=""56"" height=""56"" />" +
                                     @"        <animation name=""evo_menu_grid_settings.png"" x=""92"" y=""304"" width=""56"" height=""56"" />" +
                                     @"        <animation name=""evo_menu_grid_filemanager.png"" x=""172"" y=""304"" width=""56"" height=""56"" />" +
                                     @"        <animation name=""evo_options_breathing_line.png"" x=""0"" y=""310"" width=""240"" height=""10"" />" +
                                     @"        <animation name=""evo_status_signals_4.png"" x=""0"" y=""4"" width=""14"" height=""10"" />" +
                                     @"        <animation name=""evo_status_simcard1.png"" x=""16"" y=""4"" width=""15"" height=""10"" />" +
                                     @"        <animation name=""evo_status_simcard2.png"" x=""49"" y=""4"" width=""15"" height=""10"" />" +
                                     @"        <animation name=""normal.png"" x=""66"" y=""1"" width=""15"" height=""15"" />" +
                                     @"        <animation name=""memory_card.png"" x=""83"" y=""1"" width=""15"" height=""15"" />" +
                                     @"        <animation name=""qgn_stat_edge.png"" x=""161"" y=""4"" width=""24"" height=""10"" />" +
                                     @"        <animation name=""evo_status_battery_100.png"" x=""187"" y=""4"" width=""15"" height=""10"" />" +
                                     @"        <text x=""4"" y=""94"" width=""72"" height=""20"">Contacts</text>" +
                                     @"        <text x=""84"" y=""94"" width=""72"" height=""20"">Calendar</text>" +
                                     @"        <text x=""164"" y=""94"" width=""72"" height=""20"">Messages</text>" +
                                     @"        <text x=""4"" y=""185"" width=""72"" height=""20"">Phone</text>" +
                                     @"        <text x=""84"" y=""185"" width=""72"" height=""20"">Camera</text>" +
                                     @"        <text x=""164"" y=""185"" width=""72"" height=""20"">Music</text>" +
                                     @"        <text x=""4"" y=""276"" width=""72"" height=""20"">Calculator</text>" +
                                     @"        <text x=""84"" y=""276"" width=""72"" height=""20"">Clock</text>" +
                                     @"        <text x=""164"" y=""276"" width=""72"" height=""20"">Countdown</text>" +
                                     @"        <text x=""204"" y=""-1"" width=""36"" height=""20"">12:47</text>" +
                                     @"      </capture>" +
                                     @"    </summary>" +
                                     @"  </testcase>" +
                                     @"  <summary>Ran 1 tests in 2.835 s </summary>" +
                                     @"</testreport>";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                // Initially try and get the phone display animation elements
                var phoneDisplayAnimationElements = target.PhoneDisplayAnimationElements;
                Assert.IsTrue(phoneDisplayAnimationElements == null || phoneDisplayAnimationElements.Count == 0, "There should be no phone display animation elements initially.");

                // Refresh the phone data
                target.RefreshPhoneData();

                // Try and get the phone display animation elements
                phoneDisplayAnimationElements = target.PhoneDisplayAnimationElements;
                Assert.IsTrue(phoneDisplayAnimationElements == null || phoneDisplayAnimationElements.Count == 0, "There should be no phone display animation if there is no capture XML file.");

                // Create the capture file with valid data
                File.WriteAllText(target.CaptureXmlFilePath, validCaptureXml);

                // Refresh the phone data
                target.RefreshPhoneData();

                // Get the phone display animation elements
                phoneDisplayAnimationElements = target.PhoneDisplayAnimationElements;
                Assert.IsNotNull(phoneDisplayAnimationElements, "There should be phone display animation elements if we have written valid capture XML data.");

                int expected = 11;
                int actual = phoneDisplayAnimationElements.Count;
                Assert.AreEqual(expected, actual, "The number of phone display animation elements should match the capture XML data we have written.");
            }
        }

        /// <summary>
        ///A test for PhoneDisplayImage
        ///</summary>
        [TestMethod()]
        public void PhoneDisplayImageTest()
        {
            string validCaptureXml = @"<?xml-stylesheet type='text/xsl' href='../xslt/test_report_xml_to_html.xslt'?>" +
                                     @"<testreport test_group_filter="""" time=""19:50:17"" date=""2012-06-13"" author=""mfreed"">" +
                                     @"  <product name=""S40 eVo"" main_display=""MD240X320"" imei=""004402133756902"">" +
                                     @"    <version type=""sw"">Vp gadCEX1215_01" +
                                     @"11-04-12" +
                                     @"RM-766" +
                                     @"(c) Nokia   </version>" +
                                     @"    <version type=""hw"">not available</version>" +
                                     @"    <version type=""granite server"">1.001</version>" +
                                     @"  </product>" +
                                     @"  <testcase result=""Passed"" id=""capture.xml"" type=""scripted"" date=""2012-06-13"" time=""19:50:19"" subarea=""Display"" feature=""Capture"">" +
                                     @"    <description title=""Test case for taking phone display capture"">Test case for taking phone display capture</description>" +
                                     @"    <teststep name=""'phone_display_capture'"" timeout=""10000"" id=""1"" stepId=""1"">" +
                                     @"      <config max_isi_data_length=""49152"" bitmap_capture=""yes"" keypress_wait=""100"" keypress_length=""100"" background=""no"" id=""2"" />" +
                                     @"      <sx id=""3"">dump</sx>" +
                                     @"      <capture name=""phone_display_capture"" id=""4"" />" +
                                     @"    </teststep>" +
                                     @"    <summary id=""1"" name=""'phone_display_capture'"" stepId=""1"">" +
                                     @"      <capture>" +
                                     @"        <xml>" +
                                     @"          <container name=""primary-root-container"" coords=""0,0,240,320"" alignments=""start,start"" autosize=""false,false"" visible=""true"" handled-touch-events="""" has-local-focus=""false"" has-global-focus=""false"">" +
                                     @"            <stacked-container name=""subroot"" coords=""0,0,240,320"" alignments=""start,start"" autosize=""false,false"" visible=""true"" handled-touch-events="""" has-local-focus=""true"" has-global-focus=""false"">" +
                                     @"            </stacked-container>" +
                                     @"          </container>" +
                                     @"        </xml>" +
                                     @"      </capture>" +
                                     @"      <capture id=""4"">" +
                                     @"        <bitmap format=""13"" little_endian_cpu=""yes"" screen=""1"" x=""0"" y=""0"" width=""240"" height=""320"" background=""no"" name=""capture_1.png"" />" +
                                     @"        <animation name=""evo_menu_grid_radio.png"" x=""12"" y=""304"" width=""56"" height=""56"" />" +
                                     @"        <animation name=""evo_menu_grid_settings.png"" x=""92"" y=""304"" width=""56"" height=""56"" />" +
                                     @"        <animation name=""evo_menu_grid_filemanager.png"" x=""172"" y=""304"" width=""56"" height=""56"" />" +
                                     @"        <animation name=""evo_options_breathing_line.png"" x=""0"" y=""310"" width=""240"" height=""10"" />" +
                                     @"        <animation name=""evo_status_signals_4.png"" x=""0"" y=""4"" width=""14"" height=""10"" />" +
                                     @"        <animation name=""evo_status_simcard1.png"" x=""16"" y=""4"" width=""15"" height=""10"" />" +
                                     @"        <animation name=""evo_status_simcard2.png"" x=""49"" y=""4"" width=""15"" height=""10"" />" +
                                     @"        <animation name=""normal.png"" x=""66"" y=""1"" width=""15"" height=""15"" />" +
                                     @"        <animation name=""memory_card.png"" x=""83"" y=""1"" width=""15"" height=""15"" />" +
                                     @"        <animation name=""qgn_stat_edge.png"" x=""161"" y=""4"" width=""24"" height=""10"" />" +
                                     @"        <animation name=""evo_status_battery_100.png"" x=""187"" y=""4"" width=""15"" height=""10"" />" +
                                     @"        <text x=""4"" y=""94"" width=""72"" height=""20"">Contacts</text>" +
                                     @"        <text x=""84"" y=""94"" width=""72"" height=""20"">Calendar</text>" +
                                     @"        <text x=""164"" y=""94"" width=""72"" height=""20"">Messages</text>" +
                                     @"        <text x=""4"" y=""185"" width=""72"" height=""20"">Phone</text>" +
                                     @"        <text x=""84"" y=""185"" width=""72"" height=""20"">Camera</text>" +
                                     @"        <text x=""164"" y=""185"" width=""72"" height=""20"">Music</text>" +
                                     @"        <text x=""4"" y=""276"" width=""72"" height=""20"">Calculator</text>" +
                                     @"        <text x=""84"" y=""276"" width=""72"" height=""20"">Clock</text>" +
                                     @"        <text x=""164"" y=""276"" width=""72"" height=""20"">Countdown</text>" +
                                     @"        <text x=""204"" y=""-1"" width=""36"" height=""20"">12:47</text>" +
                                     @"      </capture>" +
                                     @"    </summary>" +
                                     @"  </testcase>" +
                                     @"  <summary>Ran 1 tests in 2.835 s </summary>" +
                                     @"</testreport>";

            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                // Initially try and get the phone display image
                var phoneDisplayImage = target.PhoneDisplayImage;
                var phoneDisplayImageFilePath = target.PhoneDisplayImageFilePath;
                Assert.IsNull(phoneDisplayImage, "There should be no phone display image initially.");
                Assert.IsNull(phoneDisplayImageFilePath, "There should be no phone display image file path initially.");

                // Refresh the phone data
                target.RefreshPhoneData();

                // Try and get the phone display image
                phoneDisplayImage = target.PhoneDisplayImage;
                phoneDisplayImageFilePath = target.PhoneDisplayImageFilePath;
                Assert.IsNull(phoneDisplayImage, "There should be no phone display image if there is no capture XML file.");
                Assert.IsNull(phoneDisplayImageFilePath, "There should be no phone display image file path if there is no capture XML file.");

                // Create the capture file with valid data
                File.WriteAllText(target.CaptureXmlFilePath, validCaptureXml);

                // Refresh the phone data
                target.RefreshPhoneData();

                // Try and get the phone display image
                phoneDisplayImage = target.PhoneDisplayImage;
                phoneDisplayImageFilePath = target.PhoneDisplayImageFilePath;
                Assert.IsNull(phoneDisplayImage, "There should be no phone display image if there is no phone display image file.");
                Assert.IsNotNull(phoneDisplayImageFilePath, "There should be a phone display image file path if the capture XML contains the file name.");

                // Create an image to be used as the phone display image
                using (Bitmap bitmap = new Bitmap(200, 400))
                {
                    // Create the directory for the display image file
                    string directory = Path.GetDirectoryName(target.PhoneDisplayImageFilePath);
                    Directory.CreateDirectory(directory);

                    // Save the phone display image
                    bitmap.Save(target.PhoneDisplayImageFilePath, ImageFormat.Png);

                    // Create the capture file again with valid data
                    File.WriteAllText(target.CaptureXmlFilePath, validCaptureXml);

                    // Refresh the phone data
                    target.RefreshPhoneData();

                    // Try and get the phone display image
                    phoneDisplayImage = target.PhoneDisplayImage;
                    phoneDisplayImageFilePath = target.PhoneDisplayImageFilePath;
                    Assert.IsNotNull(phoneDisplayImage, "There should be a phone display image since the image file was created by this unit test.");
                    Assert.IsNotNull(phoneDisplayImageFilePath, "There should be a phone display image file path if the capture XML contains the file name.");
                    Assert.AreEqual(bitmap.Width, phoneDisplayImage.Width, "The phone display image width should match the one created by the unit test.");
                    Assert.AreEqual(bitmap.Height, phoneDisplayImage.Height, "The phone display image height should match the one created by the unit test.");
                }
            }
        }

        /// <summary>
        ///A test for CanGenerateReport
        ///</summary>
        [TestMethod()]
        public void CanGenerateReportTest()
        {
            using (GraniteStudioModel target = new GraniteStudioModel())
            {
                bool expected = false;
                bool actual = target.CanGenerateReport();
                Assert.AreEqual(expected, actual, "The report should not be able to be generated prior to running any tests.");
            }
        }

        /// <summary>
        ///A test for TrackingEndpoint
        ///</summary>
        [TestMethod()]
        public void TrackingEndpointTest()
        {
            GraniteStudioModel target = new GraniteStudioModel();
            string actual = target.TrackingEndpoint;
            Assert.IsFalse(string.IsNullOrEmpty(actual), "The tracking endpoint should not be null or empty.");

            string expected = "http://localhost:8000/Granite/UnitTestTrackingEndpoint";
            target.TrackingEndpoint = expected;
            actual = target.TrackingEndpoint;
            Assert.AreEqual(expected, actual, string.Format("Then tracking endpoint should be set to '{0}'.", expected));
        }
    }
}
