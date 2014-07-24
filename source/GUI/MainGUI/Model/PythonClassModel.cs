// -----------------------------------------------------------------------
// <copyright file="PythonClassModel.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Model
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    using Marble.Utilities;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class PythonClassModel
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="PythonClassModel"/> class.
        /// </summary>
        public PythonClassModel(string name = "")
        {
            this.FullName = name;
            this.Methods = new ObservableCollectionAdv<PythonMethodModel>();
        }

        public string DisplayName { get { return this.FullName.Remove(0, "class ".Length); } }
        
        public string FilePath { get; set; }

        public string FullName { get; set; }

        public ObservableCollectionAdv<PythonMethodModel> Methods { get; set; }

        public int MethodCount { get { return this.Methods == null ? 0 : this.Methods.Count; } }
    }

    public class PythonMethodModel
    {
        public PythonMethodModel(string name = "")
        {
            this.FullName = name;
        }

        public string DisplayName { get { return this.FullName.Remove(0, "def ".Length); } }

        public string FullName { get; set; }

        public string Code { get; set; }
    }
}
