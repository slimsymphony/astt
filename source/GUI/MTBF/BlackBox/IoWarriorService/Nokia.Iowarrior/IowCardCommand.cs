using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

namespace Nokia.Iowarrior
{
    /// <summary>
    /// IowCardCommand is used to do all command string parsing and syntax check, match with list of supported commands and result handling.
    /// </summary>
    public class IowCardCommand
    {
        List<String> ignoredFieldNames = new List<String>();
        String commandString;
        String[] tokens;
        Boolean executionSuccess;
        Boolean isExecutable;
        IDictionary returnValues = new SortedDictionary<String, object>();
        Dictionary<String, String> commandMap = new Dictionary<string,string>();
        List<String> executionList = new List<String>();

        #region -----Constructors-----

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="command">Command string to be analysed or executed.</param>
        public IowCardCommand(String command)
        {
            // Remember command
            commandString = command;

            // Split up command
            Tokenize(command);

            // Define field names to be ignored in command handling
            ignoredFieldNames.Add("index");
            ignoredFieldNames.Add("name");

            CreateExecutionListFromCommand();
        }

        #endregion

        #region -----Internal-----

        /// <summary>
        /// Get reference of the command map.
        /// </summary>
        internal Dictionary<String, String> CommandMap
        {
            get { return commandMap; }
        }

        /// <summary>
        /// Checks, if the given command(s) can be found in the CommandMap.
        /// </summary>
        /// <returns>True, if all commands are in the CommandMap. False, otherwise.</returns>
        internal Boolean DefinesCommand()
        {
            this.IsExecutable = true;

            foreach (String cmd in executionList)
            {
                if (!commandMap.ContainsKey(cmd))
                    this.IsExecutable = false;
            }

            return this.IsExecutable;
        }

        /// <summary>
        /// Calculates new IowBits bitvector from given input bitvector and all given commands.
        /// </summary>
        /// <param name="bv">IowBits representing the current state of the Iowarrior output pins.</param>
        /// <returns>IowBits changed by the commands.</returns>
        internal IowBits UpdateIowBits(IowBits bv)
        {
            foreach (String cmd in executionList)
            {
                foreach (String value in commandMap[cmd].Split(','))
                {
                    int i = int.Parse(value);
                    bv[Math.Abs(i)] = (i > 0);
                }
            }
            return bv;
        }

        #endregion

        #region -----Private-----

        /// <summary>
        /// Creates list of single, atomic commands to be used for iteration in other methods.
        /// </summary>
        private void CreateExecutionListFromCommand()
        {
            List<String> fieldNames = this.GetFieldNamesAsList();

            foreach (String ignoredFieldName in ignoredFieldNames)
                fieldNames.Remove(ignoredFieldName);

            foreach (String fieldName in fieldNames)
            {
                if (this.HasFieldValue(fieldName))
                {
                    foreach (String value in this.GetFieldValues(fieldName))
                    {
                        executionList.Add(String.Format("{0}:{1}={2}", this.Command, fieldName, value));
                    }
                }
                else
                {
                    executionList.Add(String.Format("{0}:{1}", this.Command, fieldName));
                }
            }
        }

        /// <summary>
        /// Splits a command string into tokens.
        /// </summary>
        /// <param name="command">Command string.</param>
        private void Tokenize(String command)
        {
            if (command == null)
                throw new ArgumentNullException("command");

            // Remove all white spaces
            StringBuilder sb = new StringBuilder();
//            foreach (Char c in command.ToLower(System.Globalization.CultureInfo.InvariantCulture))
            foreach (Char c in command)
                    if (!Char.IsWhiteSpace(c))
                    sb = sb.Append(c);

            // Split at colons
            tokens = sb.ToString().Split(':');
        }

        /// <summary>
        /// Extract all field names from the command string.
        /// </summary>
        /// <returns></returns>
        private List<String> GetFieldNamesAsList()
        {
            List<String> fieldNames = new List<string>();
            for (int i = 1; i < tokens.Length; i++)
            {
                String[] fields = tokens[i].Split("=".ToCharArray(),2);
                if (!fieldNames.Contains(fields[0]))
                    fieldNames.Add(fields[0]);
            }
            return fieldNames;
        }

        #endregion

        #region -----Public-----

        /// <summary>
        /// Returns all field names in this command.
        /// </summary>
        public ICollection<String> FieldNames
        {
            get { return GetFieldNamesAsList(); }
        }

        /// <summary>
        /// Get all known commands of this IowCardCommand object. This list represents all commands which would pass the syntax check.
        /// </summary>
        public ICollection<String> KnownCommands
        {
            get
            {
                SortedList s = new SortedList();
                foreach (String cmd in commandMap.Keys)
                    s.Add(cmd, null);
                String[] result = new String[s.Count];
                s.Keys.CopyTo(result, 0);

                return result;
            }
        }

        /// <summary>
        /// Get the command string this IowCardCommand object is valid for.
        /// </summary>
        public String CommandString
        {
            get { return commandString; }
        }

        /// <summary>
        /// True, if the command was checked and regarded as executable.
        /// </summary>
        public Boolean IsExecutable
        {
            get { return isExecutable; }
            set { isExecutable = value; }
        }

        /// <summary>
        /// Get command execution success status: True, if it was executed successfully.
        /// </summary>
        public Boolean ExecutionSuccess
        {
            get { return executionSuccess; }
            set { executionSuccess = value; }
        }

        /// <summary>
        /// Non-generic dictionary (=Hashtable) of return values provided by the command.
        /// </summary>
        public IDictionary ReturnValues
        {
            get
            {
                if (returnValues != null) return returnValues;
                else return new Hashtable();
            }
        }

        /// <summary>
        /// Get the command token from the whole command string.
        /// </summary>
        public String Command
        {
            get { return tokens[0]; }
        }

        /// <summary>
        /// Get the index value from the Command string if there is one set. If there is none set, it returns 0.
        /// </summary>
        /// <returns>Index value from the Command.</returns>
        public int IndexValue
        {
            get
            {
                if (HasIndex)
                    return int.Parse(GetFieldValues("index")[0]);
                else
                    return 0;
            }
        }

        /// <summary>
        /// Get indication whether there is a field named "index" in the command string or not.
        /// </summary>
        public Boolean HasIndex
        {
            get { return ContainsField("index"); }
        }

        /// <summary>
        /// Returns the value of the "name" field from the Command if there is one set. If there is none it returns "".
        /// </summary>
        /// <returns>Value of "name" field value from the Command.</returns>
        public String NameValue
        {
            get
            {
                if (HasName)
                    return GetFieldValues("name")[0];
                else
                    return "";
            }
        }

        /// <summary>
        /// Get indication whether there is a field named "name" in the command string or not.
        /// </summary>
        public Boolean HasName
        {
            get { return ContainsField("name"); }
        }

        /// <summary>
        /// Checks, if the field "FieldName" is defined in the command.
        /// </summary>
        /// <param name="fieldName">Name of the field</param>
        /// <returns>True, if the fieldname contains one or more field</returns>
        public Boolean ContainsField(String fieldName)
        {
            return GetFieldNamesAsList().Contains(fieldName);
        }

        /// <summary>
        /// Checks, if the field with the name "FieldName" has a value
        /// </summary>
        /// <param name="fieldName">Name of the field</param>
        /// <returns>True, if the fieldname has a value </returns>
        public Boolean HasFieldValue(String fieldName)
        {
            return GetFieldValues(fieldName).Length != 0;
        }

        /// <summary>
        /// Returns the first value of the field with the name "FieldName".
        /// </summary>
        /// <param name="fieldName">Name of the field.</param>
        /// <returns>First value of the field.</returns>
        public String GetFieldValue(String fieldName)
        {
            return GetFieldValues(fieldName)[0];
        }

        /// <summary>
        /// Returns all values of the field with the name "FieldName".
        /// </summary>
        /// <param name="fieldName">Name of the field.</param>
        /// <returns>All values of the field.</returns>
        public String[] GetFieldValues(String fieldName)
        {
            List<String> valuesList = new List<string>();
            for (int i = 1; i < tokens.Length; i++)
            {
                String[] fields = tokens[i].Split("=".ToCharArray(),2);
                if ((fields[0] == fieldName) && (fields.Length == 2))
                {
                    String[] values = fields[1].Split(',');
                    foreach (String s in values)
                    {
                        String[] numbers = s.Split('-');
                        if (numbers.Length > 1)
                        {
                            for (int j = Int32.Parse(numbers[0]); j <= Int32.Parse(numbers[1]); j++)
                                valuesList.Add(Convert.ToString(j));
                        }
                        else
                        {
                            valuesList.Add(s);
                        }
                    }
                }
            }

            return valuesList.ToArray();
        }
        #endregion
    }

}
