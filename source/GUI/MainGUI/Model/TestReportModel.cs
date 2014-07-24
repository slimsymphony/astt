// -----------------------------------------------------------------------
// <copyright file="TestReportModel.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

using System.Collections.Specialized;

namespace Marble.Model
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Drawing;
    using System.IO;
    using System.Linq;
    using System.Text;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Media;
    using System.Windows.Media.Imaging;
    using System.Xml.Linq;

    using Marble.Utilities;

    using MarbleLibrary.Utilities;

    using Visiblox.Charts;

    /// <summary>
    /// The test report result.
    /// </summary>
    public enum TestReportResult
    {
        /// <summary>
        /// Failed test report result status.
        /// </summary>
        Failed = 0,

        /// <summary>
        /// Passed test report result status.
        /// </summary>
        Passed = 1,

        /// <summary>
        /// No result test report result status.
        /// </summary>
        NoResult = 2,
    }

    /// <summary>
    /// The test case report item type.
    /// </summary>
    public enum TestCaseReportItemType
    {
        /// <summary>
        /// Unknown test case report item type.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// The comment.
        /// </summary>
        Comment = 0,

        /// <summary>
        /// The description.
        /// </summary>
        Description = 1,

        /// <summary>
        /// The test step.
        /// </summary>
        TestStep = 2,

        /// <summary>
        /// The summary.
        /// </summary>
        Summary = 3,

        /// <summary>
        /// The error.
        /// </summary>
        Error = 4,

        /// <summary>
        /// Videos test case report item type.
        /// </summary>
        Videos = 5,

        /// <summary>
        /// Performance measurement test step.
        /// </summary>
        PerfTestStep = 6,

        /// <summary>
        /// Warning element.
        /// </summary>
        Warning = 7,

        /// <summary>
        /// Bugreport element.
        /// </summary>
        //[Description("")]
        BugReport = 8,

        /// <summary>
        /// Whole test case report summary item type.
        /// </summary>
        TestCaseReportSummary = 99,
    }

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class TestReportModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="TestReportModel"/> class.
        /// </summary>
        public TestReportModel()
        {
            this.TestCaseReportSummaryItemModel = new TestCaseReportSummaryItemModel(this);

            this.TestCaseReport = new TestCaseReportModel();
            this.TestReportProduct = new TestReportProductModel();
        }

        public TestCaseReportSummaryItemModel TestCaseReportSummaryItemModel { get; set; }

        private string testResultXmlFilePath;

        /// <summary>
        /// Gets or sets the test result xml file path.
        /// </summary>
        public string TestResultXmlFilePath
        {
            get { return this.testResultXmlFilePath; }
            set
            {
                this.testResultXmlFilePath = value;
                this.TestCaseReport.TestResultXmlFilePath = this.testResultXmlFilePath;
                this.OnPropertyChanged("TestResultXmlFilePath");
                this.OnPropertyChanged("TestResultXmlFileName");
            }
        }

        /// <summary>
        /// Gets the test result xml file name.
        /// </summary>
        public string TestResultXmlFileName { get { return FileUtilities.GetFileName(this.TestResultXmlFilePath); } }

        private string testGroupFilter;

        /// <summary>
        /// Gets or sets the test group filter.
        /// </summary>
        public string TestGroupFilter
        {
            get { return this.testGroupFilter; }
            set
            {
                this.testGroupFilter = value;
                this.OnPropertyChanged("TestGroupFilter");
            }
        }

        private DateTime startTime;

        /// <summary>
        /// Gets or sets the start time when test was started.
        /// </summary>
        public DateTime StartTime
        {
            get { return this.startTime; }
            set
            {
                this.startTime = value;
                this.OnPropertyChanged("StartTime");
            }
        }

        private string author;

        /// <summary>
        /// Gets or sets the author of the test report.
        /// </summary>
        public string Author
        {
            get { return this.author; }
            set
            {
                this.author = value;
                this.OnPropertyChanged("Author");
            }
        }

        private TestCaseReportModel testCaseReport;

        /// <summary>
        /// Gets or sets the test case report model object.
        /// </summary>
        public TestCaseReportModel TestCaseReport
        {
            get { return this.testCaseReport; }
            set
            {
                this.testCaseReport = value;

                if (!this.testCaseReport.Items.Contains(this.TestCaseReportSummaryItemModel))
                {
                    this.testCaseReport.Items.Insert(0, this.TestCaseReportSummaryItemModel);
                }

                this.OnPropertyChanged("TestCaseReport");
            }
        }

        private TestReportProductModel testReportProduct;

        /// <summary>
        /// Gets or sets the test report product model object.
        /// </summary>
        public TestReportProductModel TestReportProduct
        {
            get { return this.testReportProduct; }
            set
            {
                this.testReportProduct = value;
                this.OnPropertyChanged("TestReportProduct");
            }
        }

        /// <summary>
        /// Gets the result of the test report.
        /// </summary>
        public TestReportResult Result { get { return this.TestCaseReport.Result; } }

        /// <summary>
        /// Gets the result image source.
        /// </summary>
        public string ResultImageSource
        {
            get
            {
                switch (this.Result)
                {
                    case TestReportResult.Passed:
                        return "/MarbleLibrary;component/Images/passed.circle.icon.32x32.png";

                    case TestReportResult.NoResult:
                        return "/MarbleLibrary;component/Images/no.resolution.circle.icon.32x32.png";

                    default:
                    case TestReportResult.Failed:
                        return "/MarbleLibrary;component/Images/failed.circle.icon.32x32.png";
                }
            }
        }

        private string summary;

        /// <summary>
        /// Gets or sets the summary text of the test report.
        /// </summary>
        public string Summary
        {
            get { return this.summary; }
            set
            {
                this.summary = value;
                this.OnPropertyChanged("Summary");
            }
        }

        /// <summary>
        /// Gets the default test report package file name.
        /// </summary>
        public string DefaultTestReportPackageFileName
        {
            get
            {
                return TextUtilities.AddDateTimeToFileName(
                    FileUtilities.GetFileName(this.TestResultXmlFilePath),
                    this.StartTime,
                    "-",
                    ".xml",
                    FileUtilities.DefaultMarbleTestReportPackageFileExtension).Replace(" ", ".");
            }
        }

        #region [ INotifyPropertyChanged Members ]

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion [ INotifyPropertyChanged Members ]
    }

    /// <summary>
    /// The test report product model.
    /// </summary>
    public class TestReportProductModel
    {
        private string name;

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        public string Name
        {
            get { return this.name; }
            set
            {
                this.name = value;
                this.OnPropertyChanged("Name");
            }
        }

        private string mainDisplay;

        /// <summary>
        /// Gets or sets the main display resolution of the tested product.
        /// </summary>
        public string MainDisplay
        {
            get { return this.mainDisplay; }
            set
            {
                this.mainDisplay = value;
                this.OnPropertyChanged("MainDisplay");
            }
        }

        private string imei;

        /// <summary>
        /// Gets or sets the IMEI code of the tested product.
        /// </summary>
        public string Imei
        {
            get { return this.imei; }
            set
            {
                this.imei = value;
                this.OnPropertyChanged("Imei");
            }
        }

        private string softwareVersion;

        /// <summary>
        /// Gets or sets the software version of the tested product.
        /// </summary>
        public string SoftwareVersion
        {
            get { return this.softwareVersion; }
            set
            {
                this.softwareVersion = value;
                this.OnPropertyChanged("SoftwareVersion");
            }
        }

        private string hardwareVersion;

        /// <summary>
        /// Gets or sets the hardware version of the tested product.
        /// </summary>
        public string HardwareVersion
        {
            get { return this.hardwareVersion; }
            set
            {
                this.hardwareVersion = value;
                this.OnPropertyChanged("HardwareVersion");
            }
        }

        private string marbleServerVersion;

        /// <summary>
        /// Gets or sets the marble server version.
        /// </summary>
        public string MarbleServerVersion
        {
            get { return this.marbleServerVersion; }
            set
            {
                this.marbleServerVersion = value;
                this.OnPropertyChanged("MarbleServerVersion");
            }
        }

        #region [ INotifyPropertyChanged Members ]

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion [ INotifyPropertyChanged Members ]
    }

    /// <summary>
    /// The test case report model.
    /// </summary>
    public class TestCaseReportModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="TestCaseReportModel"/> class.
        /// </summary>
        public TestCaseReportModel()
        {
            this.Items = new ObservableCollectionAdv<TestCaseReportItemModel>();
            this.Items.CollectionChanged += ItemsOnCollectionChanged;
            this.NeededFiles = new List<string>();
        }

        private void ItemsOnCollectionChanged(object sender, NotifyCollectionChangedEventArgs eventArgs)
        {
            if (eventArgs.Action != NotifyCollectionChangedAction.Move)
                this.OnPropertyChanged("Warnings");
        }

        private TestReportResult result;

        /// <summary>
        /// Gets or sets the result.
        /// </summary>
        public TestReportResult Result
        {
            get { return this.result; }
            set
            {
                this.result = value;
                this.OnPropertyChanged("Result");
            }
        }

        private string testResultXmlFilePath;

        /// <summary>
        /// Gets or sets the test result XML file path.
        /// </summary>
        public string TestResultXmlFilePath
        {
            get { return this.testResultXmlFilePath; }
            set
            {
                if (!string.IsNullOrEmpty(value) && !this.NeededFiles.Contains(value))
                {
                    if (this.NeededFiles.Contains(this.testResultXmlFilePath))
                        this.NeededFiles.Remove(this.testResultXmlFilePath);

                    this.NeededFiles.Add(value);
                }

                this.testResultXmlFilePath = value;
                this.OnPropertyChanged("TestResultXmlFilePath");
            }
        }

        private string id;

        /// <summary>
        /// Gets or sets the ID.
        /// </summary>
        public string Id
        {
            get { return this.id; }
            set
            {
                this.id = value;
                this.OnPropertyChanged("Id");
            }
        }

        private string testCaseType;

        /// <summary>
        /// Gets or sets the test case type.
        /// </summary>
        public string TestCaseType
        {
            get { return this.testCaseType; }
            set
            {
                this.testCaseType = value;
                this.OnPropertyChanged("TestCaseType");
            }
        }

        private string subarea;

        /// <summary>
        /// Gets or sets the subarea.
        /// </summary>
        public string Subarea
        {
            get { return this.subarea; }
            set
            {
                this.subarea = value;
                this.OnPropertyChanged("Subarea");
            }
        }

        private string feature;

        /// <summary>
        /// Gets or sets the feature.
        /// </summary>
        public string Feature
        {
            get { return this.feature; }
            set
            {
                this.feature = value;
                this.OnPropertyChanged("Feature");
            }
        }

        private DateTime startTime;

        /// <summary>
        /// Gets or sets the start time.
        /// </summary>
        public DateTime StartTime
        {
            get { return this.startTime; }
            set
            {
                this.startTime = value;
                this.OnPropertyChanged("StartTime");
            }
        }

        private DateTime endTime;

        /// <summary>
        /// Gets or sets the end time.
        /// </summary>
        public DateTime EndTime
        {
            get { return this.endTime; }
            set
            {
                this.endTime = value;
                this.OnPropertyChanged("EndTime");
            }
        }

        private TimeSpan duration;

        /// <summary>
        /// Gets or sets the duration of test.
        /// </summary>
        public TimeSpan Duration
        {
            get { return this.duration; }
            set
            {
                this.duration = value;
                this.OnPropertyChanged("Duration");
            }
        }

        /// <summary>
        /// Gets or sets the items.
        /// </summary>
        public ObservableCollectionAdv<TestCaseReportItemModel> Items { get; set; }

        /// <summary>
        /// Gets or sets list of file paths for the needed files to display test report properly.
        /// </summary>
        public List<string> NeededFiles { get; set; }

        private string descriptionTitle;

        /// <summary>
        /// Gets or sets the description title.
        /// </summary>
        public string DescriptionTitle
        {
            get { return this.descriptionTitle; }
            set
            {
                this.descriptionTitle = value;
                this.OnPropertyChanged("DescriptionTitle");
            }
        }

        private string description;

        /// <summary>
        /// Gets or sets the description.
        /// </summary>
        public string Description
        {
            get { return this.description; }
            set
            {
                this.description = value;
                this.OnPropertyChanged("Description");
            }
        }

        /// <summary>
        /// Gets all the warnings in the report.
        /// </summary>
        public IEnumerable<TestCaseReportItemModel> Warnings { get { return this.Items.Where(i => i.ItemType == TestCaseReportItemType.Warning); } }

        /// <summary>
        /// Gets or sets the summary.
        /// </summary>
        public string Summary { get; set; }

        #region [ INotifyPropertyChanged Members ]

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion [ INotifyPropertyChanged Members ]
    }

    /// <summary>
    /// The test case report item model.
    /// </summary>
    public class TestCaseReportItemModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="TestCaseReportItemModel"/> class.
        /// </summary>
        /// <param name="itemType">The item type.</param>
        public TestCaseReportItemModel(TestCaseReportItemType itemType = TestCaseReportItemType.Comment)
        {
            this.ItemType = itemType;
        }

        private string text;

        /// <summary>
        /// Gets or sets the text.
        /// </summary>
        public virtual string Text
        {
            get { return this.text; }
            set
            {
                this.text = value;
                this.OnPropertyChanged("Text");
            }
        }

        private TestCaseReportItemType itemType;

        /// <summary>
        /// Gets or sets the item type.
        /// </summary>
        public TestCaseReportItemType ItemType
        {
            get { return this.itemType; }
            protected set
            {
                this.itemType = value;
                this.OnPropertyChanged("ItemType");
            }
        }

        private DateTime timeStamp;

        /// <summary>
        /// Gets or sets the time stamp.
        /// </summary>
        public DateTime TimeStamp
        {
            get
            {
                return this.timeStamp;
            }
            set
            {
                this.timeStamp = value;
                this.OnPropertyChanged("TimeStamp");
            }
        }

        #region [ INotifyPropertyChanged Members ]

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string propertyName)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion [ INotifyPropertyChanged Members ]
    }

    //public class ProductSummaryItemModel : TestCaseReportItemModel
    //{
    //    public ProductSummaryItemModel(TestReportProductModel parentTestReportProductModel = null)
    //    {
    //        this.ParentTestReportProductModel = parentTestReportProductModel;
    //    }

    //    public TestReportProductModel ParentTestReportProductModel { get; private set; }
    //}

    public class TestCaseReportSummaryItemModel : TestCaseReportItemModel
    {
        public TestCaseReportSummaryItemModel(TestReportModel parentTestReportModel = null) : base(TestCaseReportItemType.TestCaseReportSummary)
        {
            this.TestReport = parentTestReportModel;
        }

        public TestReportModel TestReport { get; private set; }
    }

    /// <summary>
    /// The comment report item model.
    /// </summary>
    public class CommentReportItemModel : TestCaseReportItemModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CommentReportItemModel"/> class.
        /// </summary>
        /// <param name="reason">Reason/text for the comment.</param>
        public CommentReportItemModel(string reason = "") : base(TestCaseReportItemType.Comment)
        {
            this.Reason = reason;
        }

        private string reason;

        /// <summary>
        /// Gets or sets the reason.
        /// </summary>
        public string Reason
        {
            get { return this.reason; }
            set
            {
                base.Text = value;
                this.reason = value;
                this.OnPropertyChanged("Text");
                this.OnPropertyChanged("Reason");
            }
        }

        /// <summary>
        /// Gets or sets the text.
        /// </summary>
        public override string Text
        {
            get { return this.Reason; }
            set
            {
                base.Text = value;
                this.Reason = value;
                this.OnPropertyChanged("Text");
                this.OnPropertyChanged("Reason");
            }
        }
    }

    /// <summary>
    /// The error report item model.
    /// </summary>
    public class ErrorReportItemModel : CommentReportItemModel
    {
        private string traceBack;

        /// <summary>
        /// Stack trace of the exception provided by the Marble framework.
        /// </summary>
        public string TraceBack
        {
            get { return this.traceBack; }
            set
            {
                if (value == this.traceBack) return;

                this.traceBack = value;
                this.OnPropertyChanged("TraceBack");
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ErrorReportItemModel"/> class.
        /// </summary>
        /// <param name="text">Error text.</param>
        public ErrorReportItemModel(string text = "")
        {
            this.ItemType = TestCaseReportItemType.Error;
            base.Text = text;
        }
    }

    /// <summary>
    /// The warning report item model.
    /// </summary>
    public class WarningReportItemModel : CommentReportItemModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="WarningReportItemModel"/> class.
        /// </summary>
        /// <param name="text">Error text.</param>
        public WarningReportItemModel(string text = "")
        {
            this.ItemType = TestCaseReportItemType.Warning;
            base.Text = text;
        }
    }

    /// <summary>
    /// The description report item model.
    /// </summary>
    public class DescriptionReportItemModel : TestCaseReportItemModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="DescriptionReportItemModel"/> class.
        /// </summary>
        /// <param name="title">The title text.</param>
        /// <param name="text">The text.</param>
        public DescriptionReportItemModel(string title = "", string text = "") : base(TestCaseReportItemType.Description)
        {
            this.ItemType = TestCaseReportItemType.Description;
            this.Title = title;
            base.Text = text.StartsWith("\n") ? text.TrimStart('\n') : text;
        }

        private string title;

        /// <summary>
        /// Gets or sets the title.
        /// </summary>
        public string Title
        {
            get { return this.title; }
            set
            {
                this.title = value;
                this.OnPropertyChanged("Title");
            }
        }
    }

    /// <summary>
    /// The summary report item model.
    /// </summary>
    public class SummaryReportItemModel : TestCaseReportItemModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="SummaryReportItemModel"/> class.
        /// </summary>
        /// <param name="name">The name.</param>
        public SummaryReportItemModel(string name = "") : base(TestCaseReportItemType.Summary)
        {
            this.ItemType = TestCaseReportItemType.Summary;
            this.Name = name;
        }

        private string name;

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        public string Name
        {
            get { return this.name; }
            set
            {
                base.Text = value;
                this.name = value;
                this.OnPropertyChanged("Text");
                this.OnPropertyChanged("Name");
            }
        }

        private int id;

        /// <summary>
        /// Gets or sets the ID.
        /// </summary>
        public int Id
        {
            get { return this.id; }
            set
            {
                this.id = value;
                this.OnPropertyChanged("Id");
            }
        }

        private int stepId;

        /// <summary>
        /// Gets or sets the step id.
        /// </summary>
        public int StepId
        {
            get { return this.stepId; }
            set
            {
                this.stepId = value;
                this.OnPropertyChanged("StepId");
            }
        }

        /// <summary>
        /// Gets or sets the text.
        /// </summary>
        public override string Text
        {
            get { return this.Name; }
            set
            {
                base.Text = value;
                this.Name = value;
                this.OnPropertyChanged("Text");
                this.OnPropertyChanged("Name");
            }
        }

        private CaptureItemReportModel captureItemReport;

        /// <summary>
        /// Gets or sets the capture item report.
        /// </summary>
        public CaptureItemReportModel CaptureItemReport
        {
            get
            {
                return this.captureItemReport;
            }
            set
            {
                this.captureItemReport = value;
                this.OnPropertyChanged("CaptureItemReport");
                this.OnPropertyChanged("HasCaptureItemReport");
            }
        }

        /// <summary>
        /// Gets a value indicating whether has capture item report.
        /// </summary>
        public bool HasCaptureItemReport { get { return this.CaptureItemReport != null; } }
    }

    /// <summary>
    /// The test step report model.
    /// </summary>
    public class TestStepReportModel : TestCaseReportItemModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="TestStepReportModel"/> class.
        /// </summary>
        public TestStepReportModel() : base(TestCaseReportItemType.TestStep)
        {
            this.Items = new ObservableCollectionAdv<TestCaseReportItemModel>();
        }

        /// <summary>
        /// Gets or sets the items.
        /// </summary>
        public ObservableCollectionAdv<TestCaseReportItemModel> Items { get; set; }

        private string name;

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        public string Name
        {
            get { return this.name; }
            set
            {
                this.name = value;
                this.OnPropertyChanged("Name");
            }
        }

        private int timeout;

        /// <summary>
        /// Gets or sets the timeout.
        /// </summary>
        public int Timeout
        {
            get { return this.timeout; }
            set
            {
                this.timeout = value;
                this.OnPropertyChanged("Timeout");
            }
        }

        private string id;

        /// <summary>
        /// Gets or sets the ID.
        /// </summary>
        public string Id
        {
            get { return this.id; }
            set
            {
                this.id = value;
                this.OnPropertyChanged("Id");
            }
        }

        private string stepId;

        /// <summary>
        /// Gets or sets the step ID.
        /// </summary>
        public string StepId
        {
            get { return this.stepId; }
            set
            {
                this.stepId = value;
                this.OnPropertyChanged("StepId");
            }
        }

        /// <summary>
        /// Gets the tool tip summary.
        /// </summary>
        public string ToolTipSummary
        {
            get
            {
                string toolTipSummary = this.Items.Cast<TestStepItemReportModel>().Aggregate(string.Empty, (current, testStepItemReportModel) => current + (testStepItemReportModel.Id + ". " + testStepItemReportModel.Name + "\n\t" + testStepItemReportModel.Text + "\n"));

                return toolTipSummary.EndsWith("\n") ? toolTipSummary.TrimEnd('\n') : toolTipSummary;
            }
        }
    }

    /// <summary>
    /// The test step item report model.
    /// </summary>
    public class TestStepItemReportModel : TestCaseReportItemModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="TestStepItemReportModel"/> class.
        /// </summary>
        public TestStepItemReportModel() : base(TestCaseReportItemType.Unknown)
        {

        }

        private string name;

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        public string Name
        {
            get { return this.name; }
            set
            {
                this.name = value;
                this.OnPropertyChanged("Name");
            }
        }

        private string id;

        /// <summary>
        /// Gets or sets the id.
        /// </summary>
        public string Id
        {
            get { return this.id; }
            set
            {
                this.id = value;
                this.OnPropertyChanged("Id");
            }
        }
    }

    /// <summary>
    /// The capture item report model.
    /// </summary>
    public class CaptureItemReportModel : TestCaseReportItemModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CaptureItemReportModel"/> class.
        /// </summary>
        public CaptureItemReportModel()
        {
            this.DisplayElements = new ObservableCollectionAdv<DisplayElement>();
        }

        private ObservableCollectionAdv<DisplayElement> displayElements;

        /// <summary>
        /// Collection for the captured display elements.
        /// </summary>
        public ObservableCollectionAdv<DisplayElement> DisplayElements
        {
            get
            {
                return this.displayElements;
            }
            set
            {
                this.displayElements = value;
                this.OnPropertyChanged("DisplayElements");
            }
        }

        private string captureBitmapFileName;

        /// <summary>
        /// Gets or sets the capture bitmap file name.
        /// </summary>
        public string CaptureBitmapFileName
        {
            get
            {
                return this.captureBitmapFileName;
            }
            set
            {
                this.captureBitmapFileName = value;
                this.OnPropertyChanged("CaptureBitmapFilePath");
                this.OnPropertyChanged("CaptureBitmapFileName");
                this.OnPropertyChanged("CaptureBitmapImageSource");
            }
        }

        private string captureBitmapFilePath;

        /// <summary>
        /// Gets or sets the capture bitmap file path.
        /// </summary>
        public string CaptureBitmapFilePath
        {
            get
            {
                return this.captureBitmapFilePath;
            }
            set
            {
                this.captureBitmapFilePath = value;
                this.OnPropertyChanged("CaptureBitmapFilePath");
                this.OnPropertyChanged("CaptureBitmapFileName");
                this.OnPropertyChanged("CaptureBitmapImageSource");
            }
        }

        /// <summary>
        /// Gets the capture bitmap image source.
        /// </summary>
        public ImageSource CaptureBitmapImageSource
        {
            get
            {
                Uri sourcePath;
                if (File.Exists(this.CaptureBitmapFilePath))
                    sourcePath = new Uri(this.CaptureBitmapFilePath, UriKind.RelativeOrAbsolute);
                else
                    sourcePath = new Uri("pack://application:,,,/MarbleLibrary;component/Images/image.not.found.240x203.png", UriKind.RelativeOrAbsolute);

                // Set cache option to onload so image handle is released after load.
                BitmapImage image = new BitmapImage();
                image.BeginInit();
                image.CacheOption = BitmapCacheOption.OnLoad;
                image.CreateOptions = BitmapCreateOptions.IgnoreImageCache;
                image.UriSource = sourcePath;
                image.EndInit();

                return image;
            }
        }
    }

    /// <summary>
    /// The videos item report model.
    /// </summary>
    public class VideosItemReportModel : TestCaseReportItemModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="VideosItemReportModel"/> class.
        /// </summary>
        public VideosItemReportModel() : base(TestCaseReportItemType.Videos)
        {
            this.VideoFilePaths = new ObservableCollectionAdv<string>();
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="VideosItemReportModel"/> class.
        /// </summary>
        /// <param name="videoFilePaths">The collection containing video file paths.</param>
        public VideosItemReportModel(List<string> videoFilePaths) : base(TestCaseReportItemType.Videos)
        {
            if (videoFilePaths == null || videoFilePaths.Count == 0)
                this.VideoFilePaths = new ObservableCollectionAdv<string>();
            else
                this.VideoFilePaths = new ObservableCollectionAdv<string>(videoFilePaths);
        }

        private ObservableCollectionAdv<string> videoFilePaths;

        /// <summary>
        /// Gets or sets the collection containing video file paths.
        /// </summary>
        public ObservableCollectionAdv<string> VideoFilePaths
        {
            get
            {
                return this.videoFilePaths;
            }
            set
            {
                this.videoFilePaths = value;
                this.OnPropertyChanged("VideoFilePaths");
            }
        }
    }

    public class PerformanceReportItemReportModel : TestCaseReportItemModel
    {
        public PerformanceReportItemReportModel()
        {
            this.PerfTestSteps = new ObservableCollectionAdv<GraphModel.PerfTestStepItemReportModel>();
            this.ItemType = TestCaseReportItemType.PerfTestStep;
        }

        public PerformanceReportItemReportModel(XElement performanceReportElement) : this()
        {
            this.PerformanceReportXml = performanceReportElement;
            this.CreatePerfTestStepsFromXml(performanceReportElement);
        }

        private XElement performanceReportXml;

        /// <summary>
        /// Gets or sets the performance report xml.
        /// </summary>
        public XElement PerformanceReportXml
        {
            get
            {
                return this.performanceReportXml;
            }
            set
            {
                this.performanceReportXml = value;
                this.OnPropertyChanged("PerformanceReportXml");
            }
        }

        private ObservableCollectionAdv<GraphModel.PerfTestStepItemReportModel> perfTestSteps;

        /// <summary>
        /// Gets or sets the perf test steps.
        /// </summary>
        public ObservableCollectionAdv<GraphModel.PerfTestStepItemReportModel> PerfTestSteps
        {
            get
            {
                return this.perfTestSteps;
            }
            set
            {
                this.perfTestSteps = value;
                this.OnPropertyChanged("PerfTestSteps");
            }
        }

        public void CreatePerfTestStepsFromXml(XElement performanceReportElement)
        {
            if (performanceReportElement == null) return;

            if (performanceReportElement.Name == "test_step_perf")
            {
                this.PerfTestSteps.Add(GraphModel.PerfTestStepItemReportModel.CreatePerfTestStepItemFromXml(performanceReportElement));
            }
            else
            {
                foreach (var childElement in performanceReportElement.Elements("test_step_perf"))
                {
                    this.PerfTestSteps.Add(
                        GraphModel.PerfTestStepItemReportModel.CreatePerfTestStepItemFromXml(childElement));
                }
            }
        }
    }

    public class FileItemReportModel : TestCaseReportItemModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="FileItemReportModel"/> class.
        /// </summary>
        public FileItemReportModel() : base(TestCaseReportItemType.Unknown)
        {
            
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="FileItemReportModel"/> class.
        /// </summary>
        /// <param name="filePath">The file path of the bugreport.</param>
        public FileItemReportModel(string filePath) : base(TestCaseReportItemType.Unknown)
        {
            this.FilePath = filePath;
        }

        private string filePath;

        /// <summary>
        /// Gets or sets the file path of the bugreport.
        /// </summary>
        public string FilePath
        {
            get
            {
                return this.filePath;
            }
            set
            {
                this.filePath = value;

                if (filePath.ToLower().StartsWith("bug_reports"))
                {
                    string testSetResultsDirectory = App.ViewModel.TestSetModel.DocumentPath;

                    if (testSetResultsDirectory.ToLower().EndsWith(".testset"))
                        testSetResultsDirectory = testSetResultsDirectory.Substring(
                            0, testSetResultsDirectory.Length - ".testset".Length) + "_results";

                    this.filePath = testSetResultsDirectory + "\\" + this.filePath;
                }
                
                this.IsFileFound = File.Exists(filePath);

                if (this.IsFileFound)
                {
                    this.FileInfo = new FileInfo(filePath);
                    this.FileIconImage = ImageUtilities.ImageFromIconFromFilePath(filePath);
                }

                this.OnPropertyChanged("FilePath");
                this.OnPropertyChanged("IsFileFound");
                this.OnPropertyChanged("FileIconImage");
            }
        }

        public FileInfo FileInfo { get; private set; }

        public bool IsFileFound { get; private set; }

        public System.Windows.Controls.Image FileIconImage { get; private set; }
    }

    /// <summary>
    /// The videos item report model.
    /// </summary>
    public class BugReportItemReportModel : FileItemReportModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="BugReportItemReportModel"/> class.
        /// </summary>
        public BugReportItemReportModel() : base()
        {
            this.ItemType = TestCaseReportItemType.BugReport;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="BugReportItemReportModel"/> class.
        /// </summary>
        /// <param name="filePath">The file path of the bugreport.</param>
        public BugReportItemReportModel(string filePath) : base(filePath)
        {
            this.FilePath = filePath;
            this.ItemType = TestCaseReportItemType.BugReport;
        }
    }
}
