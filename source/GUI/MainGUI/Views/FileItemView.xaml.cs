using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Marble.Views
{
    using System.ComponentModel;
    using System.IO;
    using System.Timers;
    using System.Windows.Threading;

    using Marble.Model;
    using Marble.ViewModel;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// Interaction logic for FileItemView.xaml
    /// </summary>
    public partial class FileItemView : UcBase, INotifyPropertyChanged
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="FileItemView"/> class.
        /// </summary>
        public FileItemView()
        {
            InitializeComponent();

            //this.DataContext = this.ViewModel;
        }

        //#region [ FileItemReportModel DependencyProperty]

        ///// <summary>
        ///// The FileItemReportModel property.
        ///// </summary>
        //public static readonly DependencyProperty FileItemReportModelProperty = DependencyProperty.Register(
        //    "FileItemReportModel", typeof(BugReportItemReportModel), typeof(FileItemView), new FrameworkPropertyMetadata(null, OnFileItemReportModelPropertyChanged));

        ///// <summary>
        ///// Gets or sets the FileItemReportModel.
        ///// </summary>
        //public BugReportItemReportModel FileItemReportModel
        //{
        //    get { return (BugReportItemReportModel)this.GetValue(FileItemReportModelProperty); }
        //    set { this.SetValue(FileItemReportModelProperty, value); }
        //}

        //private static void OnFileItemReportModelPropertyChanged(DependencyObject source, DependencyPropertyChangedEventArgs e)
        //{
        //    FileItemView control = source as FileItemView;
        //    BugReportItemReportModel fileItemReportModel = e.NewValue as BugReportItemReportModel;

        //    if (control == null || e.NewValue == null) return;

        //    control.ViewModel = new FileItemViewModel(fileItemReportModel);
        //    control.DataContext = control.ViewModel;

        //    control.OnPropertyChanged("FileItemReportModel");
        //    control.OnPropertyChanged("ViewModel");
        //}

        //#endregion [ FileItemReportModel DependencyProperty]

        #region [ FileItemReportModel DependencyProperty]

        /// <summary>
        /// The FileItemReportModel property.
        /// </summary>
        public static readonly DependencyProperty FileItemReportModelProperty = DependencyProperty.Register(
            "FileItemReportModel", typeof(FileItemReportModel), typeof(FileItemView), new FrameworkPropertyMetadata(null, OnFileItemReportModelPropertyChanged));

        /// <summary>
        /// Gets or sets the FileItemReportModel.
        /// </summary>
        public FileItemReportModel FileItemReportModel
        {
            get { return (FileItemReportModel)this.GetValue(FileItemReportModelProperty); }
            set { this.SetValue(FileItemReportModelProperty, value); }
        }

        private static void OnFileItemReportModelPropertyChanged(DependencyObject source, DependencyPropertyChangedEventArgs e)
        {
            FileItemView control = source as FileItemView;
            FileItemReportModel fileItemReportModel = e.NewValue as FileItemReportModel;

            if (control == null || e.NewValue == null) return;

            control.ViewModel = new FileItemViewModel(fileItemReportModel);
            control.DataContext = control.ViewModel;

            control.OnPropertyChanged("FileItemReportModel");
            control.OnPropertyChanged("ViewModel");
        }

        #endregion [ FileItemReportModel DependencyProperty]

        public FileItemViewModel ViewModel { get; private set; }

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
