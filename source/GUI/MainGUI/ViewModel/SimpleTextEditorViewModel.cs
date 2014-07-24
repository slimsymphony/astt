// -----------------------------------------------------------------------
// <copyright file="SimpleTextEditorViewModel.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.ViewModel
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Text;
    using System.Windows.Input;

    using Marble.Model;
    using Marble.Utilities;

    using MarbleLibrary.Commands;

    using Microsoft.Win32;

    using ICSharpCode.AvalonEdit.Document;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class SimpleTextEditorViewModel : BaseNotifyPropertyChanged
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="SimpleTextEditorViewModel"/> class.
        /// </summary>
        /// <param name="filePath">File path of the file which is loaded to the text editor on start up.</param>
        public SimpleTextEditorViewModel(string filePath = null)
        {
            if (string.IsNullOrEmpty(filePath)) return;

            this.FilePath = filePath;

            if (!this.Load(filePath)) return;

            this.PythonClasses = PythonParser.CreateModelCollectionFromPythonCode(this.FilePath);
        }

        public ObservableCollectionAdv<PythonClassModel> PythonClasses { get; set; }

        public ObservableCollectionAdv<string> FindHistory { get; set; }

        public ObservableCollectionAdv<string> ReplaceHistory { get; set; }

        private TextDocument document;

        /// <summary>
        /// The content of the loaded source file.
        /// Only bindable property of the Avalon editor.
        /// </summary>
        public TextDocument Document
        {
            get { return this.document; }
            set
            {
                if (this.document == value) return;

                this.document = value;
                this.OnPropertyChanged("Document");
            }
        }

        private bool isTextChanged;

        /// <summary>
        /// Gets or sets a value indicating whether the text has changed.
        /// </summary>
        public bool IsTextChanged
        {
            get { return this.isTextChanged; }
            set
            {
                if (this.isTextChanged == value) return;

                this.isTextChanged = value;
                if (value) this.InfoText = string.Empty;

                this.OnPropertyChanged("IsTextChanged");
                this.OnPropertyChanged("HeaderText");
            }
        }

        private bool isSearchCaseSensitive;

        /// <summary>
        /// Gets or sets a value indicating whether the search is case sensitive.
        /// </summary>
        public bool IsSearchCaseSensitive
        {
            get { return this.isSearchCaseSensitive; }
            set
            {
                this.isSearchCaseSensitive = value;
                this.OnPropertyChanged("IsSearchCaseSensitive");
            }
        }

        private bool isSearchedTextFound;

        public bool IsSearchedTextFound
        {
            get { return this.isSearchedTextFound; }
            set
            {
                this.isSearchedTextFound = value;
                this.OnPropertyChanged("IsSearchedTextFound");
            }
        }

        private string filePath;

        /// <summary>
        /// Gets or sets the file path of the file which is currently loaded in the text editor.
        /// </summary>
        public string FilePath
        {
            get { return this.filePath; }
            set
            {
                this.filePath = value;
                this.OnPropertyChanged("FilePath");
                this.OnPropertyChanged("HeaderText");
            }
        }

        /// <summary>
        /// Gets the file name of the current file in the text editor.
        /// </summary>
        public string FileName { get { return this.FilePath.Substring(this.FilePath.LastIndexOf("\\") + 1); } }

        /// <summary>
        /// Gets the folder path of the current file in the text editor.
        /// </summary>
        public string FolderPath { get { return this.FilePath.Substring(0, this.FilePath.LastIndexOf("\\")); } }

        /// <summary>
        /// Gets the header text.
        /// </summary>
        public string HeaderText
        {
            get
            {
                return this.IsTextChanged ? "*" + this.FilePath : this.FilePath;
            }
        }

        private string infoText;

        /// <summary>
        /// Gets or sets info text.
        /// </summary>
        public string InfoText
        {
            get { return this.infoText; }
            set
            {
                this.infoText = value;
                this.OnPropertyChanged("InfoText");
            }
        }

        private int currentLineIndex;

        /// <summary>
        /// Gets or sets the current line index where text editor caret is.
        /// </summary>
        public int CurrentLineIndex
        {
            get { return this.currentLineIndex; }
            set
            {
                this.currentLineIndex = value;
                this.OnPropertyChanged("CurrentLineIndex");
            }
        }

        private int currentColumnIndex;

        /// <summary>
        /// Gets or sets the current column index where text editor caret is.
        /// </summary>
        public int CurrentColumnIndex
        {
            get { return this.currentColumnIndex; }
            set
            {
                this.currentColumnIndex = value;
                this.OnPropertyChanged("CurrentColumnIndex");
            }
        }

        private int selectionStart;

        /// <summary>
        /// Offset of the start of the selection (relative to the whole document).
        /// </summary>
        public int SelectionStart
        {
            get { return this.selectionStart; }
            set
            {
                if (this.selectionStart == value) return;

                this.selectionStart = value;
                this.OnPropertyChanged("SelectionStart");
            }
        }

        private int selectionLength;

        /// <summary>
        /// Length of the selection.
        /// </summary>
        public int SelectionLength
        {
            get { return this.selectionLength; }
            set
            {
                if (this.selectionLength == value) return;

                this.selectionLength = value;
                this.OnPropertyChanged("SelectionLength");
            }
        }

        private DelegateCommand cmdSave;

        private DelegateCommand cmdSaveAs;

        public bool CanSave() { return this.IsTextChanged; }

        public bool CanSaveAs() { return true; }

        /// <summary>
        /// Command for saving the current document.
        /// </summary>
        public ICommand CmdSave
        {
            get
            {
                if (cmdSave == null)
                {
                    cmdSave = new DelegateCommand(new Action(this.Save), new Func<bool>(this.CanSave));
                }

                return cmdSave;
            }
        }

        /// <summary>
        /// Command for saving the current document with a specific file name.
        /// </summary>
        public ICommand CmdSaveAs
        {
            get
            {
                if (cmdSaveAs == null)
                {
                    cmdSaveAs = new DelegateCommand(new Action(this.SaveAs), new Func<bool>(this.CanSaveAs));
                }

                return cmdSaveAs;
            }
        }

        /// <summary>
        /// Opens Save as dialog and saves the current document.
        /// </summary>
        public void SaveAs()
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.OverwritePrompt = true;
            saveFileDialog.InitialDirectory = this.FolderPath;
            saveFileDialog.FileName = this.FileName;
            saveFileDialog.RestoreDirectory = true;

            if ((bool)saveFileDialog.ShowDialog() && !string.IsNullOrEmpty(saveFileDialog.FileName))
                this.save(saveFileDialog.FileName);
        }

        /// <summary>
        /// Saves changes to the file in the text editor.
        /// </summary>
        public void Save()
        {
            this.save(this.FilePath);
        }

        private void save(string filePath, bool createBackup = false)
        {
            if (createBackup)
                File.Copy(filePath, filePath + "_backup", true);

            // Erase trailing white space and convert tabs to spaces
            this.CleanText();
            
            File.WriteAllText(filePath, this.Document.Text);
            this.InfoText = "File saved succesfully.";
            this.IsTextChanged = false;
        }

        /// <summary>
        /// Reads content of a text document to this.Document.
        /// </summary>
        /// <param name="filePath">File system path of the source file.</param>
        /// <returns>True on success otherwise false.</returns>
        private bool Load(string filePath)
        {
            if (string.IsNullOrEmpty(filePath) || !File.Exists(filePath)) return false;

            this.Document = new TextDocument();
            this.Document.Text = File.ReadAllText(filePath);
            this.IsTextChanged = false;
            return true;
        }

        /// <summary>
        /// Converts tabs to spaces and erases trailing white space from each line of this.Document.
        /// </summary>
        private void CleanText()
        {
            DocumentLine line = this.Document.GetLineByNumber(1);
            while (line != null)
            {
                this.document.Replace(line.Offset, line.Length,
                                      this.Document.GetText(line).TrimEnd().Replace("\t", "    "));
                line = line.NextLine;
            }
        }

        public void AddToFindHistory(string textSearched)
        {
            this.FindHistory = this.addToHistory(textSearched, this.FindHistory, true);
        }

        public void AddToReplaceHistory(string textReplacement)
        {
            this.ReplaceHistory = this.addToHistory(textReplacement, this.ReplaceHistory, true);
        }

        private ObservableCollectionAdv<string> addToHistory(string text, ObservableCollectionAdv<string> history, bool movePreviouslyUsedToTop = false)
        {
            if (string.IsNullOrEmpty(text)) return history;
            if (history == null) history = new ObservableCollectionAdv<string>();

            if (!history.Contains(text))
            {
                history.Insert(0, text);
            }
            else
            {
                history.Move(history.IndexOf(text), 0);
            }

            return history;
        }
    }
}
