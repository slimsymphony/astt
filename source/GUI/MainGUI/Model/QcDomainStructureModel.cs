// -----------------------------------------------------------------------
// <copyright file="QcTestSetStructureModel.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Model
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Globalization;
    using System.Linq;
    using System.Text;
    using System.Xml.Linq;

    using Marble.Utilities;

    using TestAutomation.Gui.Marble.QC;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class QcDomainStructureModel : INotifyPropertyChanged
    {
        public const string ExampleXml = @"<?xml version=""1.0"" encoding=""UTF-8"" standalone=""yes""?>
<Domains>
    <Domain Name=""REPORTING"">
        <Projects>
            <Project Name=""PCDW_S40PROD_TB11_2"" />
        </Projects>
    </Domain><Domain Name=""MP_S40"">
        <Projects>
            <Project Name=""S40PROD_TB11_2"" />
        </Projects>
    </Domain>
</Domains>";

        /// <summary>
        /// Gets or sets the domains.
        /// </summary>
        public ObservableCollectionAdv<QcDomainModel> Domains { get; set; }

        public MarbleQCInterface MarbleQc { get; set; } 

        private QcDomainModel selectedDomain;

        public QcDomainModel SelectedDomain
        {
            get
            {
                return this.selectedDomain;
            }
            set
            {
                this.selectedDomain = value;
                this.OnPropertyChanged("SelectedDomain");
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="QcDomainStructureModel"/> class.
        /// </summary>
        public QcDomainStructureModel()
        {
            this.Domains = new ObservableCollectionAdv<QcDomainModel>();
        }

        /// <summary>
        /// The create qc test set structure model from xml.
        /// </summary>
        /// <param name="qcTestSetStructureXml">
        /// The qc test set structure xml.
        /// </param>
        /// <returns>
        /// The Marble.Model.QcDomainStructureModel.
        /// </returns>
        public static QcDomainStructureModel CreateQcDomainStructureModelFromXml(XElement qcTestSetStructureXml)
        {
            if (qcTestSetStructureXml == null) return null;

            QcDomainStructureModel qcDomainStructure = new QcDomainStructureModel();

            if (qcTestSetStructureXml.Name != "Domains") return null;

            foreach (XElement domainElement in qcTestSetStructureXml.Elements("Domain"))
            {
                QcDomainModel qcDomainModel = new QcDomainModel(domainElement.Attribute("Name") != null ? domainElement.Attribute("Name").Value : string.Empty) { ParentDomainStructure = qcDomainStructure };

                foreach (QcProjectModel qcProjectModel in domainElement.Elements("Projects").Elements("Project").Select(projectElement => new QcProjectModel(projectElement.Attribute("Name") != null ? projectElement.Attribute("Name").Value : string.Empty)))
                {
                    qcProjectModel.ParentDomain = qcDomainModel;
                    qcDomainModel.Projects.Add(qcProjectModel);
                }
                
                qcDomainStructure.Domains.Add(qcDomainModel);
            }

            // When there's only one domain available, it is selected by default.
            if (qcDomainStructure.Domains != null && qcDomainStructure.Domains.Count == 1)
            {
                qcDomainStructure.SelectedDomain = qcDomainStructure.Domains[0];
                qcDomainStructure.SelectedDomain.SelectedProject = qcDomainStructure.SelectedDomain.SelectedProject;
            }

            return qcDomainStructure;
        }

        public static QcDomainStructureModel CreateExampleDomainStructure()
        {
            XElement exampleXml = XElement.Parse(QcDomainStructureModel.ExampleXml);

            return QcDomainStructureModel.CreateQcDomainStructureModelFromXml(exampleXml);
        }

        #region INotifyPropertyChanged Members

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }

    /// <summary>
    /// The qc domain model.
    /// </summary>
    public class QcDomainModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="QcDomainModel"/> class.
        /// </summary>
        /// <param name="name">
        /// The name.
        /// </param>
        public QcDomainModel(string name = "")
        {
            this.Projects = new ObservableCollectionAdv<QcProjectModel>();
            this.Name = string.IsNullOrEmpty(name) ? string.Empty : name;
        }

        public QcDomainStructureModel ParentDomainStructure { get; set; }

        private QcProjectModel selectedProject;

        public QcProjectModel SelectedProject
        {
            get
            {
                return this.selectedProject;
            }
            set
            {
                this.selectedProject = value;
                this.OnPropertyChanged("SelectedProject");
            }
        }

        /// <summary>
        /// Gets or sets the projects.
        /// </summary>
        public ObservableCollectionAdv<QcProjectModel> Projects { get; set; }

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        public string Name { get; set; }

        private bool isSelected;

        /// <summary>
        /// Gets or sets a value indicating whether is selected.
        /// </summary>
        public bool IsSelected
        {
            get
            {
                return this.isSelected;
            }
            set
            {
                this.isSelected = value;
                this.OnPropertyChanged("IsSelected");

                if (this.isSelected && this.ParentDomainStructure != null) 
                    this.ParentDomainStructure.SelectedDomain = this;
            }
        }

        #region INotifyPropertyChanged Members

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }

    /// <summary>
    /// The qc project model.
    /// </summary>
    public class QcProjectModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="QcProjectModel"/> class.
        /// </summary>
        /// <param name="name">
        /// The name.
        /// </param>
        public QcProjectModel(string name = "")
        {
            this.Name = string.IsNullOrEmpty(name) ? string.Empty : name;
        }

        public QcDomainModel ParentDomain { get; set; }

        private QcTestSetEntity selectedEntity;

        public QcTestSetEntity SelectedEntity
        {
            get
            {
                return this.selectedEntity;
            }
            set
            {
                this.selectedEntity = value;
                this.OnPropertyChanged("SelectedEntity");
            }
        }

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        public string Name { get; set; }

        private bool isSelected;

        /// <summary>
        /// Gets or sets a value indicating whether is selected.
        /// </summary>
        public bool IsSelected
        {
            get
            {
                return this.isSelected;
            }
            set
            {
                this.isSelected = value;
                this.OnPropertyChanged("IsSelected");

                if (this.isSelected)
                {
                    this.PopulateTestSetStructure();
                    ////this.ProjectTestSetStructure = QcTestSetEntity.CreateExampleTestSetStructure();
                }
            }
        }

        private QcTestSetStructure projectTestSetStructure;

        public QcTestSetStructure ProjectTestSetStructure
        {
            get
            {
                return this.projectTestSetStructure;
            }
            set
            {
                this.projectTestSetStructure = value;
                this.OnPropertyChanged("ProjectTestSetStructure");
            }
        }

        public void PopulateTestSetStructure()
        {
            if (this.ParentDomain != null)
            {
                this.ParentDomain.SelectedProject = this;

                if (this.ParentDomain.ParentDomainStructure != null &&
                    this.ParentDomain.ParentDomainStructure.MarbleQc != null &&
                    !string.IsNullOrEmpty(this.ParentDomain.Name) &&
                    !string.IsNullOrEmpty(this.Name))
                {
                    this.ProjectTestSetStructure = QcTestSetEntity.CreateQcTestSetStructure(this, this.ParentDomain.ParentDomainStructure.MarbleQc.GetTestLabViewNode(this.ParentDomain.Name, this.Name, "0"));
                }
            }
        }

        #region INotifyPropertyChanged Members

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }

    public class QcTestSetStructure : QcTestSetEntity
    {
        public const string exampleTestSetStructureXml =
            @"<test-lab-node>
  <test-set-folders>
    <Entity Type=""test-set-folder"">
      <Fields>
        <Field Name=""id"">
          <Value>162</Value>
        </Field>
        <Field Name=""name"">
          <Value>_TrashBin_</Value>
        </Field>
      </Fields>
      <RelatedEntities />
    </Entity>
    <Entity Type=""test-set-folder"">
      <Fields>
        <Field Name=""id"">
          <Value>285</Value>
        </Field>
        <Field Name=""name"">
          <Value>Demo</Value>
        </Field>
      </Fields>
      <RelatedEntities />
    </Entity>
    <Entity Type=""test-set-folder"">
      <Fields>
        <Field Name=""id"">
          <Value>4</Value>
        </Field>
        <Field Name=""name"">
          <Value>P4364 Gaia DS</Value>
        </Field>
      </Fields>
      <RelatedEntities />
    </Entity>
    <Entity Type=""test-set-folder"">
      <Fields>
        <Field Name=""id"">
          <Value>174</Value>
        </Field>
        <Field Name=""name"">
          <Value>P4364 Gaia SS</Value>
        </Field>
      </Fields>
      <RelatedEntities />
    </Entity>
    <Entity Type=""test-set-folder"">
      <Fields>
        <Field Name=""id"">
          <Value>83</Value>
        </Field>
        <Field Name=""name"">
          <Value>P4382 Hawaii</Value>
        </Field>
      </Fields>
      <RelatedEntities />
    </Entity>
    <Entity Type=""test-set-folder"">
      <Fields>
        <Field Name=""id"">
          <Value>1</Value>
        </Field>
        <Field Name=""name"">
          <Value>temp</Value>
        </Field>
      </Fields>
      <RelatedEntities />
    </Entity>
    <Entity Type=""test-set-folder"">
      <Fields>
        <Field Name=""id"">
          <Value>282</Value>
        </Field>
        <Field Name=""name"">
          <Value>Test_BB</Value>
        </Field>
      </Fields>
      <RelatedEntities />
    </Entity>
    <Entity Type=""test-set-folder"">
      <Fields>
        <Field Name=""id"">
          <Value>281</Value>
        </Field>
        <Field Name=""name"">
          <Value>TEST_Milan</Value>
        </Field>
      </Fields>
      <RelatedEntities />
    </Entity>
    <Entity Type=""test-set-folder"">
      <Fields>
        <Field Name=""id"">
          <Value>82</Value>
        </Field>
        <Field Name=""name"">
          <Value>To Be Deleted</Value>
        </Field>
      </Fields>
      <RelatedEntities />
    </Entity>
  </test-set-folders>
  <test-sets></test-sets>
</test-lab-node>";

        public QcTestSetStructure(QcProjectModel parentProject) : base(parentProject)
        {
            this.Children = new ObservableCollectionAdv<QcTestSetEntity>();
            this.ParentProject = parentProject;
        }

        public new QcTestSetEntityType Type { get { return QcTestSetEntityType.TestSetStructureRoot; } }
    }

    public enum QcTestSetEntityType
    {
        Unknown = 0,
        TestSetStructureRoot = 1,
        TestSetFolder = 2,
        TestSet = 3,
        Dummy = 4,
    }

    public class QcTestSetFolderEntity : QcTestSetEntity
    {
        public QcTestSetFolderEntity(QcProjectModel parentProject) : base(parentProject)
        {
            if (this.Children == null)
                this.Children = new ObservableCollectionAdv<QcTestSetEntity>();

            this.Children.Add(QcTestSetEntity.DummyChild);
        }

        public new QcTestSetEntityType Type { get { return QcTestSetEntityType.TestSetFolder; } }
    }

    public class QcTestSetEntity : INotifyPropertyChanged
    {
        public static QcTestSetEntity DummyChild = new QcTestSetEntity(null, QcTestSetEntityType.Dummy);

        public QcTestSetEntity(QcProjectModel parentProject)
        {
            this.ParentProject = parentProject;
        }

        public QcTestSetEntity(QcProjectModel parentProject, QcTestSetEntityType type, int id = -1, string name = "")
        {
            this.ParentProject = parentProject;
            this.Type = type;
            this.Id = id;
            this.Name = String.IsNullOrEmpty(name) ? String.Empty : name;
        }

        public QcProjectModel ParentProject { get; set; }

        private ObservableCollectionAdv<QcTestSetEntity> children;

        public ObservableCollectionAdv<QcTestSetEntity> Children
        {
            get
            {
                return this.children;
            }
            set
            {
                this.children = value;
                this.OnPropertyChanged("Children");
                this.OnPropertyChanged("IsCollapsibleIndicatorVisible");
            }
        }

        private bool isChildrenLoaded;

        public bool IsChildrenLoaded
        {
            get
            {
                return this.isChildrenLoaded;
            }
            private set
            {
                this.isChildrenLoaded = value;
                this.OnPropertyChanged("IsChildrenLoaded");
                this.OnPropertyChanged("IsCollapsibleIndicatorVisible");
            }
        }

        private bool isSelected;

        public bool IsSelected
        {
            get
            {
                return this.isSelected;
            }
            set
            {
                this.isSelected = value;
                this.OnPropertyChanged("IsSelected");

                if (this.isSelected)
                {
                    this.ParentProject.SelectedEntity = this;
                }
            }
        }

        private bool isExpanded;

        public bool IsExpanded
        {
            get
            {
                return this.isExpanded;
            }
            set
            {
                this.isExpanded = value;
                this.OnPropertyChanged("IsExpanded");

                if (this.HasDummyChild)
                {
                    this.populateChildEntities();
                    //this.Children.Remove(QcTestSetEntity.DummyChild);
                    //this.Children = QcTestSetEntity.CreateExampleTestSetStructure().Children;
                }
            }
        }

        public bool IsCollapsibleIndicatorVisible
        {
            get
            {
                if (this.IsChildrenLoaded && this.Children.Count > 0)
                    return true;

                return !this.IsChildrenLoaded;
            }
        }

        public bool HasDummyChild
        {
            get { return this.Children.Count == 1 && this.Children[0] == QcTestSetEntity.DummyChild; }
        }

        private QcTestSetEntityType type;

        public QcTestSetEntityType Type
        {
            get
            {
                return this.type;
            }
            set
            {
                this.type = value;
                this.OnPropertyChanged("Type");
            }
        }

        private int id;

        public int Id
        {
            get
            {
                return this.id;
            }
            set
            {
                this.id = value;
                this.OnPropertyChanged("Id");
            }
        }

        private string name;

        public string Name
        {
            get
            {
                return this.name;
            }
            set
            {
                this.name = value;
                this.OnPropertyChanged("Name");
            }
        }

        public static string GetTypeXmlName(QcTestSetEntityType type)
        {
            switch (type)
            {
                case QcTestSetEntityType.Unknown:
                    return String.Empty;
                case QcTestSetEntityType.TestSetStructureRoot:
                    return String.Empty;
                case QcTestSetEntityType.TestSetFolder:
                    return "test-set-folder";
                case QcTestSetEntityType.TestSet:
                    return "test-set";
                default:
                    throw new ArgumentOutOfRangeException("type");
            }
        }

        public static QcTestSetStructure CreateQcTestSetStructure(QcProjectModel parentProject, XElement testSetStructureXml)
        {
            if (testSetStructureXml == null) return null;

            QcTestSetStructure testSetStructure = new QcTestSetStructure(parentProject);

            List<XElement> xElements = new List<XElement>();
            xElements.AddRange(testSetStructureXml.Element("test-set-folders").Elements("Entity"));
            xElements.AddRange(testSetStructureXml.Element("test-sets").Elements("Entity"));

            foreach (XElement entityElement in xElements)
            {
                QcTestSetEntity testSetEntity = new QcTestSetEntity(parentProject);
                XAttribute attribute = entityElement.Attribute("Type");

                if (attribute == null) continue;

                switch (attribute.Value)
                {
                    case "test-set-folder":
                        testSetEntity = new QcTestSetFolderEntity(parentProject);
                        //testSetEntity.Type = QcTestSetEntityType.TestSetFolder;
                        break;
                    case "test-set":
                        testSetEntity.Type = QcTestSetEntityType.TestSet;
                        break;
                    default:
                        continue;
                }

                foreach (XElement fieldElement in entityElement.Element("Fields").Elements("Field"))
                {
                    XAttribute nameAttribute = fieldElement.Attribute("Name");

                    if (nameAttribute == null) continue;

                    switch (nameAttribute.Value)
                    {
                        case "id":
                            testSetEntity.Id = fieldElement.Element("Value") != null ? int.Parse(fieldElement.Element("Value").Value) : -1;
                            break;
                        case "name":
                            testSetEntity.Name = fieldElement.Element("Value") != null ? fieldElement.Element("Value").Value : string.Empty;
                            break;
                        default:
                            continue;
                    }
                }

                testSetStructure.Children.Add(testSetEntity);
            }

            return testSetStructure;
        }

        public static QcTestSetStructure CreateExampleTestSetStructure()
        {
            XElement exampleXml = XElement.Parse(QcTestSetStructure.exampleTestSetStructureXml);

            return QcTestSetStructure.CreateQcTestSetStructure(null, exampleXml);
        }

        private void populateChildEntities()
        {
            if (this.ParentProject == null) return;
            if (this.ParentProject.ParentDomain == null) return;
            if (this.ParentProject.ParentDomain.ParentDomainStructure == null) return;
            if (this.ParentProject.ParentDomain.ParentDomainStructure.MarbleQc == null) return;

            this.Children.Remove(QcTestSetEntity.DummyChild);

            this.Children = QcTestSetStructure.CreateQcTestSetStructure(
                this.ParentProject,
                this.ParentProject.ParentDomain.ParentDomainStructure.MarbleQc.GetTestLabViewNode(
                    this.ParentProject.ParentDomain.Name,
                    this.ParentProject.Name,
                    this.Id.ToString(CultureInfo.InvariantCulture))).Children;
        }

        #region INotifyPropertyChanged Members

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }
}
