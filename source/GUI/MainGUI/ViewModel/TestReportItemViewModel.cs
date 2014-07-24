using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Marble.ViewModel
{
    using System.Diagnostics;
    using System.Windows.Input;

    using Marble.Model;

    using MarbleLibrary.Commands;

    public class FileItemViewModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="FileItemViewModel"/> class.
        /// </summary>
        public FileItemViewModel()
        {

        }

        /// <summary>
        /// Initializes a new instance of the <see cref="FileItemViewModel"/> class.
        /// </summary>
        /// <param name="filePath">The file path of the bugreport.</param>
        public FileItemViewModel(string filePath)
        {
            //this.FilePath = filePath;

            this.Model = new BugReportItemReportModel(filePath);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="FileItemViewModel"/> class.
        /// </summary>
        /// <param name="fileItemReportModel">The BugReportItemReportModel.</param>
        public FileItemViewModel(FileItemReportModel fileItemReportModel)
        {
            this.Model = fileItemReportModel;
        }

        public FileItemReportModel Model { get; set; }

        private DelegateCommand openFileCommand;

        /// <summary>
        /// 
        /// </summary>
        public ICommand OpenFileCommand
        {
            get
            {
                return this.openFileCommand ?? (this.openFileCommand = new DelegateCommand(this.openFileCommandExecuted, this.openFileCommandCanExecute));
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private bool openFileCommandCanExecute()
        {
            if (this.Model == null) return false;

            return this.Model.IsFileFound;
        }

        /// <summary>
        /// 
        /// </summary>
        private void openFileCommandExecuted()
        {
            if (this.Model == null) return;

            System.Diagnostics.Process.Start(this.Model.FilePath);
        }

        private DelegateCommand openFolderCommand;

        /// <summary>
        /// 
        /// </summary>
        public ICommand OpenFolderCommand
        {
            get
            {
                return this.openFolderCommand ?? (this.openFolderCommand = new DelegateCommand(this.openFolderCommandExecuted, this.openFolderCommandCanExecute));
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private bool openFolderCommandCanExecute()
        {
            if (this.Model == null || this.Model.FileInfo == null || this.Model.FileInfo.Directory == null) return false;

            return this.Model.IsFileFound;
        }

        /// <summary>
        /// 
        /// </summary>
        private void openFolderCommandExecuted()
        {
            if (this.Model == null) return;

            //string sfsfsdf = "explorer.exe /select,\"" + this.Model.FilePath + "\"";

            //System.Diagnostics.Process.Start("explorer.exe /select," + this.Model.FilePath);
            
            var process = new Process
                {
                    StartInfo = { FileName = "explorer.exe", Arguments = "/select,\"" + this.Model.FilePath + "\"" }
                };
            process.Start();
        }
    }
}
