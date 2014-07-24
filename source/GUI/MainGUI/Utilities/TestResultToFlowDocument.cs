// -----------------------------------------------------------------------
// <copyright file="TestResultToFlowDocument.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Utilities
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Text;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Documents;
    using System.Windows.Media;

    using Marble.Model;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class TestResultToFlowDocument
    {
        public static FlowDocument CreateFlowDocumentFromTestReportModel(TestReportModel testReportModel)
        {
            FlowDocument flowDoc = new FlowDocument();
            flowDoc.Background = Brushes.White;

            Paragraph paragraph = new Paragraph();
            paragraph.Inlines.Add( testReportModel.Author);

            Table table = new Table();

            for (int i = 0; i < 2; i++)
                table.Columns.Add(new TableColumn());

            TableRow row = new TableRow();
            row.Cells.Add(new TableCell(new Paragraph(new Run("Author"))));
            row.Cells.Add(new TableCell(new Paragraph(new Run(testReportModel.Author))));

            TableRowGroup rowGroup = new TableRowGroup();
            rowGroup.Rows.Add(row);
            table.RowGroups.Add(rowGroup);
            flowDoc.Blocks.Add(table);

            

            return flowDoc;
        }

        public static bool SaveFlowDocumentAsRtf(FlowDocument flowDocument, string filePath)
        {
            return TestResultToFlowDocument.SaveFlowDocument(flowDocument, filePath, DataFormats.Rtf);
        }

        public static bool SaveFlowDocument(FlowDocument flowDocument, string filePath, string dataFormat)
        {
            var content = new TextRange(flowDocument.ContentStart, flowDocument.ContentEnd);

            if (content.CanSave(dataFormat))
            {
                using (var stream = new FileStream(filePath, FileMode.Create))
                {
                    content.Save(stream, dataFormat);
                }

                return true;
            }

            return false;
        }
    }
}
