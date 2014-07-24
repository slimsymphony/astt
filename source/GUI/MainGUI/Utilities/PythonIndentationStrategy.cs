using ICSharpCode.AvalonEdit.Document;
using ICSharpCode.AvalonEdit.Indentation;

namespace Marble.Utilities
{
    /// <summary>
    /// Indentation logic for new lines in Avalon editor at the SimpleTextEditor.
    /// By default indentation is copied from the previous line.
    /// Exceptions:
    /// 1) Extra indentation level is added to lines after colon (:).
    /// 2) Existing indentation is preserved when hitting enter at the beginning of a line.
    /// </summary>
    class PythonIndentationStrategy : IIndentationStrategy
    {
        public virtual void IndentLine(TextDocument document, DocumentLine line)
        {
            if (document == null || line == null) return;

            DocumentLine previousLine = line.PreviousLine;
            if (previousLine == null) return;

            string prevLineText = document.GetText(previousLine);

            // Preserve indentation when hitting enter at the beginning of a line
            if (string.IsNullOrEmpty(prevLineText)) return;

            // Copy indentation from the previous line
            ISegment indentationSegment = TextUtilities.GetWhitespaceAfter(document, previousLine.Offset);
            string indentation = document.GetText(indentationSegment);
            // Add one additional indentation level if previous line ends with colon (:)
            if (prevLineText.TrimEnd().EndsWith(":"))
                indentation += "    ";
            indentationSegment = TextUtilities.GetWhitespaceAfter(document, line.Offset);
            document.Replace(indentationSegment, indentation);
        }

        /// <summary>
        /// Not implemented
        /// </summary>
        public virtual void IndentLines(TextDocument document, int beginLine, int endLine)
        {
        }
    }
}
