// -----------------------------------------------------------------------
// <copyright file="PythonParser.cs" company="NOKIA">
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

    using Marble.Model;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class PythonParser
    {

        public static ObservableCollectionAdv<PythonClassModel> CreateModelCollectionFromPythonCode(string filePath)
        {
            if (!File.Exists(filePath)) return null;

            ObservableCollectionAdv<PythonClassModel> modelCollection = new ObservableCollectionAdv<PythonClassModel>();
            List<int> indentLevels = new List<int>();
            int lineNumber = 0;

            foreach (string lineOfText in File.ReadAllLines(filePath))
            {
                lineNumber++;

                checkIndentLevel(lineOfText, indentLevels);

                string currentLineOfText = lineOfText.Trim();

                if (currentLineOfText.StartsWith("class "))
                {
                    modelCollection.Add(new PythonClassModel(currentLineOfText));
                }
                else if (currentLineOfText.StartsWith("def "))
                {
                    if (modelCollection.Count == 0)
                        modelCollection.Add(new PythonClassModel("class Public Functions"));

                    modelCollection.Last().Methods.Add(new PythonMethodModel(currentLineOfText));
                }
            }

            return modelCollection;
        }

        private static void checkIndentLevel(string lineOfText, List<int> indentLevels)
        {
            if (indentLevels == null)
                indentLevels = new List<int>();

            if (!lineOfText.StartsWith(" ")) return ;

            int currentIndentLevel = 0;

            foreach (char c in lineOfText)
            {
                if (c == ' ')
                {
                    currentIndentLevel++;
                }
                else
                {
                    break;
                }
            }

            if (indentLevels.Count == 0)
                indentLevels.Add(currentIndentLevel);
            else if (indentLevels.Last() < currentIndentLevel)
                indentLevels.Add(currentIndentLevel);
        }
    }
}
