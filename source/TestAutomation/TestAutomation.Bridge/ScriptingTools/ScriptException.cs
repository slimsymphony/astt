using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestAutomation.Bridge.ScriptingTools
{
    /// <summary>
    /// Exception class for capsulating Exceptions
    /// Used with PythonCallable and DynamicProxy
    /// </summary>
    public sealed class ScriptException : Exception
    {
        /// <summary>
        /// Private class constructor
        /// </summary>
        /// <param name="ex">The exception object</param>
        private ScriptException(Exception ex) : base(ex.Message ?? string.Empty)
        { }

        /// <summary>
        /// Creates a ScriptException instance from any exception
        /// </summary>
        /// <param name="ex">The exception to capsulate</param>
        /// <returns>A ScriptException instance</returns>
        internal static ScriptException FromException(Exception ex)
        {
            return new ScriptException(ex);
        }
    }
}
