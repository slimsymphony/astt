using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Imaging;

namespace Marble.Views
{
    using System.IO;
    using System.Text.RegularExpressions;

    using Marble.Model;
    using Marble.Utilities;
    using Marble.ViewModel;
    using Marble.Views.Dialogs;

    using MarbleLibrary.Utilities;

    using ICSharpCode.AvalonEdit;

    using IronPython.Hosting;
    using ICSharpCode.AvalonEdit.Highlighting;
    using ICSharpCode.AvalonEdit.Highlighting.Xshd;
    using Microsoft.Scripting.Hosting;
    using System.Xml;

    /// <summary>
    /// Interaction logic for SimpleTextEditorView.xaml
    /// </summary>
    public partial class SimpleTextEditorView : Window
    {
        public ObservableCollectionAdv<string> FindHistory { get { return this.viewModel.FindHistory; } }
        
        public ObservableCollectionAdv<string> ReplaceHistory { get { return this.viewModel.ReplaceHistory; } }

        private SimpleTextEditorViewModel viewModel { get { return this.DataContext as SimpleTextEditorViewModel; } }

        private DialogFindAndReplace findAndReplaceDialog { get; set; }

        /// <summary>
        /// Helper variable to skip the first text changed notification that is caused by document update.
        /// </summary>
        private bool documentChanged;

        /// <summary>
        /// Initializes a new instance of the <see cref="SimpleTextEditorView"/> class.
        /// </summary>
        /// <param name="filePath">The file path of the file which is loaded to Simple Text Editor. </param>
        /// <param name="closeEditorIfFileNotFound">Whether to close the editor and display message box if source file doesn't exist.</param>
        public SimpleTextEditorView(string filePath = null, bool closeEditorIfFileNotFound = true)
        {
            InitializeComponent();

            this.Title = FileUtilities.GetFileName(filePath) + " - " + TextUtilities.SimpleTextEditorName;
            this.DataContext = new SimpleTextEditorViewModel(filePath);

            if (!File.Exists(filePath) && closeEditorIfFileNotFound)
            {
                this.Loaded += delegate
                    {
                        this.Close();
                        MessageBox.Show("File '" + filePath + "' was not found!", TextUtilities.SimpleTextEditorName);
                    };
            }

            this.MainEditor.TextArea.IndentationStrategy = new PythonIndentationStrategy();
            this.MainEditor.Options.ConvertTabsToSpaces = true;
            this.MainEditor.TextArea.Caret.PositionChanged += new EventHandler(MainEditorPositionChanged);
            this.MainEditor.TextChanged += new EventHandler(MainEditorTextChanged);
            this.MainEditor.DocumentChanged += new EventHandler(MainEditorDocumentChanged);
        }

        /// <summary>
        /// Source document has been reloaded.
        /// Sets helper variable documentChanged to true so MainEditorTextChanged event is skipped properly.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void MainEditorDocumentChanged(object sender, EventArgs e)
        {
            this.documentChanged = true;
        }

        public bool CurrentSelectionMatchesSearchedText(string textToFind, bool isMatchCaseEnabled)
        {
            string selectedText = this.MainEditor.TextArea.Selection.GetText();

            return (isMatchCaseEnabled && selectedText == textToFind) ||
                   (!isMatchCaseEnabled && selectedText.ToLower() == textToFind.ToLower());
        }

        public void FindPrevious(string textToFind, bool isMatchCaseEnabled)
        {
            this.findPrevious(textToFind, isMatchCaseEnabled);
            this.viewModel.AddToFindHistory(textToFind);
        }

        public void FindNext(string textToFind, bool isMatchCaseEnabled)
        {
            this.findNext(textToFind, isMatchCaseEnabled);
            this.viewModel.AddToFindHistory(textToFind);
        }

        public void ReplaceSelection(string newText, string textToReplace, bool isMatchCaseEnabled)
        {
            string selectedText = this.MainEditor.TextArea.Selection.GetText();

            if (this.CurrentSelectionMatchesSearchedText(textToReplace, isMatchCaseEnabled))
            {
                this.MainEditor.TextArea.Selection.ReplaceSelectionWithText(newText);
                this.viewModel.AddToFindHistory(textToReplace);
                this.viewModel.AddToReplaceHistory(newText);
            }
        }

        public int ReplaceAll(string textToReplace, string newText, bool isMatchCaseEnabled)
        {
            int replaceCount = this.CountTextOccurances(textToReplace, isMatchCaseEnabled);

            this.MainEditor.TextArea.Document.Text = this.MainEditor.TextArea.Document.Text.Replace(textToReplace, newText);
            this.viewModel.AddToFindHistory(textToReplace);
            this.viewModel.AddToReplaceHistory(newText);

            return replaceCount;
        }

        public int CountTextOccurances(string textToFind, bool isMatchCaseEnabled)
        {
            string text = this.MainEditor.Text;

            textToFind = TextUtilities.ConvertRegexSpecialCharactersToText(textToFind);

            return isMatchCaseEnabled ? new Regex(@textToFind).Matches(@text).Count : new Regex(@textToFind, RegexOptions.IgnoreCase).Matches(@text).Count;
        }

        public void AddToFindHistory(string textToAdd)
        {
            this.viewModel.AddToFindHistory(textToAdd);
        }

        /// <summary>
        /// Handler for the TextChanged event of the main editor.
        /// Sets IsTextChanged property of the model view to true if this event is not triggered by source document update.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MainEditorTextChanged(object sender, EventArgs e)
        {
            if (this.documentChanged)
                // Skip first change notification that is cause by document update
                this.documentChanged = false;
            else
                ((SimpleTextEditorViewModel)this.DataContext).IsTextChanged = true;
        }

        /// <summary>
        /// Updates caret position to view model.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MainEditorPositionChanged(object sender, EventArgs e)
        {
            this.UpdateCaretPosition();   
        }

        /// <summary>
        /// Updates caret position to view model.
        /// </summary>
        private void UpdateCaretPosition()
        {
            this.viewModel.CurrentLineIndex = this.MainEditor.TextArea.Caret.Location.Line;
            this.viewModel.CurrentColumnIndex = this.MainEditor.TextArea.Caret.Location.Column;
        }

        /// <summary>
        /// Selects text in text editor.
        /// </summary>
        /// <param name="textToSelect">Text to select.</param>
        public void SelectText(string textToSelect)
        {
            if (this.checkBoxMatchCase.IsChecked == true && !this.MainEditor.Text.Contains(textToSelect)) return;
            if (this.checkBoxMatchCase.IsChecked == false && !this.MainEditor.Text.ToLower().Contains(textToSelect.ToLower())) return;

            this.MainEditor.Focus();

            if (this.checkBoxMatchCase.IsChecked == true)
                this.MainEditor.Select(this.MainEditor.Text.IndexOf(textToSelect), textToSelect.Count());
            else
                this.MainEditor.Select(this.MainEditor.Text.ToLower().IndexOf(textToSelect.ToLower()), textToSelect.Count());

            this.MainEditor.ScrollToLine(this.viewModel.CurrentLineIndex);
            this.UpdateCaretPosition();
        }

        private void CloseCommandHandler(object sender, ExecutedRoutedEventArgs e)
        {
            this.Close();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (!this.viewModel.IsTextChanged) return;

            switch (this.messageBoxSaveChanges())
            {
                case MessageBoxResult.Yes:
                    this.viewModel.Save();
                    break;
                case MessageBoxResult.No:
                    break;
                default:
                    e.Cancel = true;
                    return;
            }
        }

        private MessageBoxResult messageBoxSaveChanges()
        {
            return MessageBox.Show(
                    "Current file has been changed.\n\n" + "Do you want to save changes?",
                    "Save Changes?",
                    MessageBoxButton.YesNoCancel);
        }

        private void textBoxSearch_TextChanged(object sender, TextChangedEventArgs e)
        {
            bool searchedTextIsFound = this.checkWhetherSearchedTextIsFound();

            if (this.MainEditor.SelectedText == this.textBoxSearch.Text && this.checkBoxMatchCase.IsChecked == true) return;
            if (this.MainEditor.SelectedText.ToLower() == this.textBoxSearch.Text.ToLower() && this.checkBoxMatchCase.IsChecked == false) return;

            if (searchedTextIsFound)
            {
                this.SelectText(this.textBoxSearch.Text);
                this.textBoxSearch.Focus();
            }
        }

        private void buttonFindPrevious_Click(object sender, RoutedEventArgs e)
        {
            this.findPrevious(this.textBoxSearch.Text, this.checkBoxMatchCase.IsChecked == true, true);
        }

        private void buttonFindNext_Click(object sender, RoutedEventArgs e)
        {
            string selectedText = this.MainEditor.Document.GetText(this.MainEditor.SelectionStart, this.MainEditor.SelectionLength);
            if (!string.IsNullOrEmpty(this.textBoxSearch.Text) && (this.textBoxSearch.Text == selectedText))
                this.findNext(this.textBoxSearch.Text, this.checkBoxMatchCase.IsChecked == true, true);
            else
                this.FindContexMenuItemClick(null, null);
        }

        private void findPrevious(string textToFind, bool isMatchCaseEnabled = false, bool useFocusToEditor = false)
        {
            if (string.IsNullOrEmpty(textToFind)) return;
            if (!this.MainEditor.Text.Contains(textToFind) && isMatchCaseEnabled) return;
            if (!this.MainEditor.Text.ToLower().Contains(textToFind.ToLower()) && !isMatchCaseEnabled) return;

            if (useFocusToEditor)
                this.MainEditor.Focus();

            int currentIndex = this.MainEditor.TextArea.Caret.Offset;
            int searchedTextLenght = textToFind.Count();
            int lastIndexOfSearchedText;

            if (currentIndex - searchedTextLenght < 0) currentIndex = this.MainEditor.Text.Length - 1;

            if (isMatchCaseEnabled)
            {
                lastIndexOfSearchedText = this.MainEditor.Text.Substring(0, currentIndex).LastIndexOf(textToFind);

                if (lastIndexOfSearchedText == currentIndex - searchedTextLenght)
                    lastIndexOfSearchedText = this.MainEditor.Text.Substring(0, currentIndex - searchedTextLenght).LastIndexOf(textToFind);
            }
            else
            {
                lastIndexOfSearchedText = this.MainEditor.Text.Substring(0, currentIndex).ToLower().LastIndexOf(textToFind.ToLower());

                if (lastIndexOfSearchedText == currentIndex - searchedTextLenght)
                    lastIndexOfSearchedText = this.MainEditor.Text.Substring(0, currentIndex - searchedTextLenght).ToLower().LastIndexOf(textToFind.ToLower());
            }

            // Text is found before the current caret index.
            if (lastIndexOfSearchedText >= 0)
            {
                this.MainEditor.Select(lastIndexOfSearchedText, searchedTextLenght);
            }
            // Text is found after the current caret index.
            else
            {
                if (isMatchCaseEnabled)
                    lastIndexOfSearchedText = this.MainEditor.Text.Substring(currentIndex).LastIndexOf(textToFind) + currentIndex;
                else
                    lastIndexOfSearchedText = this.MainEditor.Text.Substring(currentIndex).ToLower().LastIndexOf(textToFind.ToLower()) + currentIndex;

                if (lastIndexOfSearchedText >= currentIndex)
                    this.MainEditor.Select(lastIndexOfSearchedText, searchedTextLenght);
                else
                    return;
            }

            this.MainEditor.ScrollToLine(this.viewModel.CurrentLineIndex);
            this.UpdateCaretPosition();
        }

        private void findNext(string textToFind, bool isMatchCaseEnabled = false, bool useFocusToEditor = false)
        {
            if (string.IsNullOrEmpty(textToFind)) return;
            if (isMatchCaseEnabled && !this.MainEditor.Text.Contains(textToFind)) return;
            if (!isMatchCaseEnabled && !this.MainEditor.Text.ToLower().Contains(textToFind.ToLower())) return;

            if (useFocusToEditor)
                this.MainEditor.Focus();

            int currentIndex = this.MainEditor.TextArea.Caret.Offset;
            int searchedTextLenght = textToFind.Length;
            int firstIndexOfSearchedText;

            if (currentIndex >= this.MainEditor.Text.Length - searchedTextLenght) currentIndex = 0;

            if (isMatchCaseEnabled)
                firstIndexOfSearchedText = this.MainEditor.Text.Substring(currentIndex + searchedTextLenght).IndexOf(textToFind) + currentIndex + searchedTextLenght;
            else
                firstIndexOfSearchedText = this.MainEditor.Text.Substring(currentIndex + searchedTextLenght).ToLower().IndexOf(textToFind.ToLower()) + currentIndex + searchedTextLenght;

            // Text is found after the current caret index.
            if (firstIndexOfSearchedText > currentIndex + searchedTextLenght)
            {
                this.MainEditor.Select(firstIndexOfSearchedText, searchedTextLenght);
            }
            // Text is found before the current caret index.
            else
            {
                if (isMatchCaseEnabled)
                    firstIndexOfSearchedText = this.MainEditor.Text.Substring(0, currentIndex).IndexOf(textToFind);
                else
                    firstIndexOfSearchedText = this.MainEditor.Text.Substring(0, currentIndex).ToLower().IndexOf(textToFind.ToLower());

                if (firstIndexOfSearchedText < currentIndex && firstIndexOfSearchedText >= 0)
                    this.MainEditor.Select(firstIndexOfSearchedText, searchedTextLenght);
                else
                    return;
            }

            this.MainEditor.ScrollToLine(this.viewModel.CurrentLineIndex);
            this.UpdateCaretPosition();
        }

        private void FindCommandHandler(object sender, ExecutedRoutedEventArgs e)
        {
            string selectedText = this.MainEditor.Document.GetText(this.MainEditor.SelectionStart, this.MainEditor.SelectionLength);
            string parsedText = this.ParseTextToFind(this.MainEditor.SelectionStart);
            if (string.IsNullOrEmpty(this.textBoxSearch.Text) && string.IsNullOrEmpty(selectedText) && string.IsNullOrEmpty(parsedText))
                this.textBoxSearch.Focus();
            else
                this.buttonFindNext_Click(null, null);
        }

        private void GoToLineCommandHandler(object sender, ExecutedRoutedEventArgs e)
        {
            DialogNumericValue dialogNumericValue = new DialogNumericValue
                {
                    Title = "Go To Line - " + TextUtilities.SimpleTextEditorName,
                    Icon = new BitmapImage(new Uri("pack://application:,,,/MarbleLibrary;component/Images/go.to.line.icon.16x16.png", UriKind.RelativeOrAbsolute)),
                    DialogTitle = "Go To Line...", 
                    MinValue = 1, 
                    MaxValue = this.MainEditor.LineCount,
                    DefaultValue = this.MainEditor.TextArea.Caret.Line,
                    CancelValue = -1
                };
            dialogNumericValue.DialogMessage = "Go to Line (" + dialogNumericValue.MinValue + "-" + dialogNumericValue.MaxValue + "):";

            int result = Convert.ToInt32(dialogNumericValue.ShowDialogWithResult());

            if (result == Convert.ToInt32(dialogNumericValue.CancelValue)) return;

            this.MainEditor.ScrollToLine(result);
            this.MainEditor.TextArea.Caret.Position = new TextViewPosition(result, 0);
        }

        private void FindAndReplaceCommandHandler(object sender, ExecutedRoutedEventArgs e)
        {
            if (this.findAndReplaceDialog != null)
            {
                this.findAndReplaceDialog.Focus();
                return;
            }

            this.findAndReplaceDialog = new DialogFindAndReplace(this, this.MainEditor.TextArea.Selection.GetText());
            this.findAndReplaceDialog.Icon =
                new BitmapImage(
                    new Uri(
                        "pack://application:,,,/MarbleLibrary;component/Images/search.icon.16x16.png",
                        UriKind.RelativeOrAbsolute));
            this.findAndReplaceDialog.Closed += delegate { this.findAndReplaceDialog = null; };
            this.findAndReplaceDialog.Show();
        }

        private void checkBoxMatchCase_IsCheckedChanged(object sender, RoutedEventArgs e)
        {
            this.SelectText(this.textBoxSearch.Text);
        }

        private bool checkWhetherSearchedTextIsFound()
        {
            this.viewModel.IsSearchedTextFound = this.checkBoxMatchCase.IsChecked == true ? this.MainEditor.Text.Contains(this.textBoxSearch.Text) : this.MainEditor.Text.ToLower().Contains(this.textBoxSearch.Text.ToLower());

            return this.viewModel.IsSearchedTextFound;
        }

        private ScriptEngine engine;
        private ScriptScope scope;

        private void Window_Initialized(object sender, EventArgs e)
        {
            this.engine = Python.CreateEngine();
            this.scope = this.engine.CreateScope();

            ScriptRuntime runtime = this.engine.Runtime;
            runtime.LoadAssembly(typeof(String).Assembly);
            runtime.LoadAssembly(typeof(Uri).Assembly);
            //runtime.LoadAssembly(typeof(Source).Assembly);

            this.MainEditor.SyntaxHighlighting = HighlightingLoader.Load(new XmlTextReader(MarblePaths.PythonSyntaxHighlightingDataFile), HighlightingManager.Instance);
        }

        private void checkBoxWordWrap_IsCheckedChanged(object sender, RoutedEventArgs e)
        {
            this.MainEditor.WordWrap = this.checkBoxWordWrap.IsChecked == true;
        }

        private void pythonCodeStackPanel_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ClickCount >= 2)
            {
                if (sender == null) return;
                if (!(sender is Panel)) return;
                if (((Panel)sender).Tag == null) return;

                if (((Panel)sender).Tag is PythonMethodModel)
                {
                    PythonMethodModel pythonMethodModel = ((Panel)sender).Tag as PythonMethodModel;

                    this.SelectText(pythonMethodModel.FullName);
                }
                else if (((Panel)sender).Tag is PythonClassModel)
                {
                    // Prevents TreeViewItem from collapsing/expanding when double clicked.
                    TreeViewItem parent = GuiUtilities.FindParent(sender as Panel, typeof(TreeViewItem)) as TreeViewItem;
                    
                    if (parent != null) 
                        parent.IsExpanded = !parent.IsExpanded;

                    PythonClassModel pythonClassModel = ((Panel)sender).Tag as PythonClassModel;

                    this.SelectText(pythonClassModel.FullName);
                }
            }
        }

        private void textBoxSearch_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.Enter:
                    this.buttonFindNext_Click(null, null);
                    this.textBoxSearch.Focus();
                    break;
            }
        }

        /// <summary>
        /// Handles commenting/uncommenting of the selected lines.
        /// All uncommented lines in the selection are commented.
        /// If all lines are already commented all lines are uncommented.
        /// <remarks>This has to be done here because Avalon edit is not MVVM compatible out of the box.
        /// Hence accesses to selectionStart and selectionLength aren't possible from the view model.</remarks>
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CommentContexMenuItemClick(object sender, RoutedEventArgs e)
        {
            var line = this.MainEditor.Document.GetLineByOffset(this.MainEditor.SelectionStart);
            int selectionEnd = this.MainEditor.SelectionStart + this.MainEditor.SelectionLength;

            // Dictionary to store the absolute offset of the comment mark and whether this line is commented
            var commentIndexes = new Dictionary<int, bool>();
            bool allCommented = true;

            // Iterate all lines in the selection, check if all lines are already commented
            // and store comment mark positions so we don't need to iterate again
            while (line != null && line.Offset <= selectionEnd)
            {
                string lineText = this.MainEditor.Document.GetText(line);
                int index = lineText.IndexOf('#');
                if (index >= 0 && lineText.TrimStart().StartsWith("#"))
                    commentIndexes.Add(line.Offset + index, true);
                else
                {   // No comment yet: add absolute position of the possible comment mark
                    // i.e. Offset of the first non-white space character at the line
                    commentIndexes.Add(
                        ICSharpCode.AvalonEdit.Document.TextUtilities.GetWhitespaceAfter(
                            this.MainEditor.Document, line.Offset).EndOffset, false);
                    allCommented = false;
                }
                line = line.NextLine;
            }

            // Counter to correct the position of the latter additions or removals
            int counter = 0;

            // Add or remove comment marks to needed positions
            foreach (KeyValuePair<int, bool> position in commentIndexes)
            {
                if (allCommented && position.Value)
                {   // Remove comment mark
                    this.MainEditor.Document.Remove(position.Key + counter, 1);
                    counter--;
                }
                else if (!allCommented && !position.Value)
                {   // Add comment mark
                    this.MainEditor.Document.Insert(position.Key + counter, "#");
                    counter++;
                }
            }
        }

        /// <summary>
        /// Performs find using the current selection as a search string.
        /// If nothing is selected a search for continuous text is done before the find.
        /// Case matching for find is set to enabled.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FindContexMenuItemClick(object sender, RoutedEventArgs e)
        {
            if (this.MainEditor.SelectionLength > 0)
                this.textBoxSearch.Text = this.MainEditor.Document.GetText(this.MainEditor.SelectionStart,
                                                                         this.MainEditor.SelectionLength);
            else
                this.textBoxSearch.Text = this.ParseTextToFind(this.MainEditor.SelectionStart);

            this.checkBoxMatchCase.IsChecked = true;
            this.FindNext(this.textBoxSearch.Text, this.checkBoxMatchCase.IsChecked == true);            
        }

        /// <summary>
        /// Searches for the longest continuous block of letters and/or digits from the given position.
        /// Search is performed backwards and forwards from the current position.
        /// If current character is not letter or number (and not dot) search is started from one character backwards.
        /// In case of dot character search is expanded over the dot (resulting e.g. 'car.throttle')
        /// </summary>
        /// <param name="offset">Cursor position in the whole document.</param>
        /// <returns>Resulting uniform block of letters and/or digits.</returns>
        private string ParseTextToFind(int offset)
        {
            var line = this.MainEditor.Document.GetLineByOffset(offset);
            string lineText = this.MainEditor.Document.GetText(line);
            if (string.IsNullOrEmpty(lineText))
                return string.Empty;

            int origIndex = offset - line.Offset;

            // Index is past the last character in the line
            if (origIndex > lineText.Length - 1)
                origIndex = lineText.Length - 1;

            // Current character is not letter, number or dot
            if (!char.IsLetterOrDigit(lineText[origIndex]) && lineText[origIndex] != '.' && origIndex > 0)
                origIndex--;

            // Search backwards
            int index = origIndex;
            while (index > 0)
            {
                if (!char.IsLetterOrDigit(lineText[index - 1])) break;
                index--;
            }
            int startIndex = index;

            // Search forwards
            index = origIndex;
            while (index < lineText.Length - 1)
            {
                if (!char.IsLetterOrDigit(lineText[index + 1])) break;
                index++;                
            }

            return lineText.Substring(startIndex, index + 1 - startIndex);
        }
    }
}
