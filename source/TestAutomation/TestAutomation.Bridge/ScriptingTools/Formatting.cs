using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestAutomation.Bridge.ScriptingTools
{
    /// <summary>
    /// Class for formatting objects to their string presentation.
    /// Mainly used by PythonCallble and DynamicProxy
    /// </summary>
    public static class Formatting
    {
        /// <summary>
        /// Formats any object to it's string presentation
        /// </summary>
        /// <param name="arg">Object to format</param>
        /// <returns>String presentation of the object</returns>
        public static string ToString(object arg)
        {
            return ToString(new object[] { arg });
        }

        /// <summary>
        /// Formats any collection of objects to it's string presentation
        /// </summary>
        /// <param name="args">Object to format</param>
        /// <returns>String presentation of the collection</returns>
        public static string ToString(ICollection<object> args)
        {
            if (args == null)
            {
                return "None";
            }

            var builder = new StringBuilder();

            for (int i = 0; i < args.Count; i++)
            {
                var item = args.ElementAt(i);
                builder.Append(item != null ? item.ToString() : "None");
                if (i < (args.Count - 1))
                {
                    builder.Append(", ");
                }
            }

            return builder.ToString();
        }
    }
}
