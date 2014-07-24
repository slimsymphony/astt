using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using TestAutomation.Bridge.ScriptingTools;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// SqLite exception class
    /// </summary>
    public sealed class SqliteException : Exception
    {
        public SqliteException(string message) : base(message)
        { }
    }

    /// <summary>
    /// Class for wrapping the SqLite3 in the device
    /// </summary>
    public sealed class SqLite : PythonCallable
    {
        private TABConnection m_tab;

        /// <summary>
        /// Internal class constructor
        /// </summary>
        /// <param name="tab">Tab inatance</param>
        internal SqLite(TABConnection tab)
        {
            m_tab = tab;
        }

        /// <summary>
        /// Creates a connection to a database file
        /// </summary>
        /// <param name="databaseLocation">Location of a database file</param>
        /// <returns>Database instance</returns>
        public SqLiteDatabase Connect(string databaseLocation)
        {
            if (string.IsNullOrEmpty(databaseLocation))
            {
                throw new ArgumentNullException("databaseLocation");
            }

            if (!m_tab.FileSystem.Exists(databaseLocation))
            {
                throw new FileNotFoundException(databaseLocation);
            }

            return new SqLiteDatabase(this, databaseLocation);
        }

        /// <summary>
        /// Executes an SqLite command in the device
        /// </summary>
        /// <param name="databaseLocation">Location of the database file</param>
        /// <param name="commandString">SqLite command string</param>
        /// <returns>Sqlite response</returns>
        public string[] ExecuteCommand(string databaseLocation, string commandString)
        {
            return ExecuteCommand(databaseLocation, commandString, true);
        }

        /// <summary>
        /// Executes an SqLite command in the device
        /// </summary>
        /// <param name="databaseLocation">Location of the database file</param>
        /// <param name="commandString">SqLite command string</param>
        /// <param name="checkFile">Value indicating whether to check if the database file exists in the device</param>
        /// <returns>Sqlite response</returns>
        internal string[] ExecuteCommand(string databaseLocation, string commandString, bool checkFile)
        {
            if (string.IsNullOrEmpty(databaseLocation))
            {
                throw new ArgumentNullException("databaseLocation");
            }

            if (string.IsNullOrEmpty(commandString))
            {
                throw new ArgumentNullException("commandString");
            }

            if (checkFile && !m_tab.FileSystem.Exists(databaseLocation))
            {
                throw new FileNotFoundException(databaseLocation);
            }

            commandString = commandString.Trim(' ', '\"');

            if (!commandString.EndsWith(";"))
            {
                commandString += ";";
            }

            var lines = m_tab.ShellCommand(string.Format("sqlite3 {0} \"{1}\"", databaseLocation, commandString));

            if (lines.Length == 1 && lines[0].ToLower().StartsWith("error:"))
            {
                var message = lines[0].Substring(6).TrimStart();
                throw new SqliteException(message);
            }

            return lines;
        }
    }

    /// <summary>
    /// Class presenting a database connection to a database file
    /// </summary>
    public sealed class SqLiteDatabase : PythonCallable
    {
        private string[] m_tableNames = null;

        /// <summary>
        /// internal class constructor
        /// </summary>
        /// <param name="parent">'Parent' via whom we can execute commands</param>
        /// <param name="databaseLocation">the location of this database file</param>
        internal SqLiteDatabase(SqLite parent, string databaseLocation)
        {
            Parent = new WeakReference(parent, false);
            Location = databaseLocation;
            Init();
        }

        /// <summary>
        /// Gets the location of this database file
        /// </summary>
        public string Location { get; private set; }

        /// <summary>
        /// Gets the 'Parent' via whom we can execute commands
        /// </summary>
        internal WeakReference Parent { get; private set; }

        /// <summary>
        /// Gets the available table names in this database file
        /// </summary>
        public string[] TableNames
        {
            get
            {
                return m_tableNames;
            }
        }

        /// <summary>
        /// Gets a table by its name
        /// </summary>
        /// <param name="tableName">Name of the table</param>
        /// <returns>Table</returns>
        public SqLiteTable GetTable(string tableName)
        {
            if (string.IsNullOrEmpty(tableName))
            {
                throw new ArgumentNullException("tableName");
            }

            if (!TableNames.Contains(tableName))
            {
                throw new Exception(string.Format("{0} does not have table with name {1}", Path.GetFileName(Location), tableName));
            }

            return new SqLiteTable(this, tableName);
        }

        /// <summary>
        /// Reads the table names
        /// </summary>
        private void Init()
        {
            var names = (Parent.Target as SqLite).ExecuteCommand(Location, "select name from sqlite_master where type = 'table';", false);

            if (names.Length > 0)
            {
                var trimmed = new List<string>();

                for (int i = 0; i < names.Length; i++)
                {
                    names[i] = names[i].Trim('\r', '\n');

                    if (!string.IsNullOrEmpty(names[i]))
                    {
                        trimmed.Add(names[i]);
                    }
                }
                m_tableNames = trimmed.ToArray();
            }
            else
            {
                m_tableNames = new string[0];
            }
        }
    }

    /// <summary>
    /// Class prenting a database table in a database file
    /// </summary>
    public sealed class SqLiteTable : PythonCallable
    {
        private WeakReference m_parent;
        private Dictionary<string, Type> m_dataTypes;

        /// <summary>
        /// Internal class constructor
        /// </summary>
        /// <param name="parent">Parent database instance</param>
        /// <param name="name">Name of the table</param>
        internal SqLiteTable(SqLiteDatabase parent, string name)
        {
            m_parent = new WeakReference(parent, false);
            Name = name;
            Init();
        }

        /// <summary>
        /// Gets the name of the table
        /// </summary>
        public string Name { get; private set; }

        /// <summary>
        /// Gets data types used in this table
        /// </summary>
        public Dictionary<string, Type> DataTypes
        {
            get
            {
                return m_dataTypes;
            }
        }

        /// <summary>
        /// Gets column names used in this table
        /// </summary>
        public string[] ColumNames
        {
            get
            {
                return DataTypes.Keys.ToArray();
            }
        }

        /// <summary>
        /// Gets the number of records in the table
        /// </summary>
        public int RecordCount
        {
            get
            {
                var parent = m_parent.Target as SqLiteDatabase;
                var granma = parent.Parent.Target as SqLite;
                var countStr = granma.ExecuteCommand(parent.Location,
                    string.Format("select count(*) from '{0}'", Name), false);

                int count;
                if (int.TryParse(countStr.First().Trim(), out count))
                {
                    return count;
                }
                return GetRawRecords().Length;
            }
        }

        /// <summary>
        /// Gets all the records in this table in raw, string format, each as separate array item
        /// </summary>
        /// <returns>Array of records in raw, string format</returns>
        public string[] GetRawRecords()
        {
            var parent = m_parent.Target as SqLiteDatabase;
            var granma = parent.Parent.Target as SqLite;

            return granma.ExecuteCommand(parent.Location, 
                string.Format("select * from '{0}'", Name), false);
        }

        /// <summary>
        /// Gets a record from this table, selected by conditional key-value -pair
        /// </summary>
        /// <param name="conditionKey">Condition key name</param>
        /// <param name="conditionValue">Condition value</param>
        /// <returns>A record from this table</returns>
        public SqLiteRecord GetRecord(string conditionKey, object conditionValue)
        {
            CheckColumn(conditionKey);

            var values = GetRecordValues(conditionKey, conditionValue);

            return values == null ? null : new SqLiteRecord(this, conditionKey, conditionValue);
        }

        /// <summary>
        /// Gets all the values in a record in a table in a database file
        /// </summary>
        /// <param name="conditionKey">Condition key name</param>
        /// <param name="conditionValue">Condition value</param>
        /// <returns>All the values in a record in a table in a database file</returns>
        public Dictionary<string, object> GetRecordValues(string conditionKey, object conditionValue)
        {
            CheckColumn(conditionKey);

            var types = DataTypes;

            var dataRow = GetUnformattedRecord(conditionKey, conditionValue);

            if (dataRow == null)
            {
                return null;
            }

            var items = dataRow.Split('|');

            if (types.Count != items.Length)
            {
                return null;
            }

            var dict = new Dictionary<string, object>();

            for (int i = 0; i < items.Length; i++)
            {
                string key = types.Keys.ElementAt(i);
                Type type = types[key];
                string itemStr = items[i];
                object value = string.Empty;

                if (type == null)
                {
                    value = null;
                }
                else if (type == typeof(string))
                {
                    value = itemStr;
                }
                else if (type == typeof(int))
                {
                    value = !string.IsNullOrEmpty(itemStr) ? int.Parse(itemStr) : 0;
                }
                else if (type == typeof(float))
                {
                    value = !string.IsNullOrEmpty(itemStr) ? float.Parse(itemStr) : (float)0;
                }
                else if (type == typeof(bool))
                {
                    value = (itemStr == "1" || itemStr.ToLower() == "true") ? true : false;
                }

                dict.Add(key, value);
            }

            return dict;
        }

        /// <summary>
        /// Inserts a new record in a table in a database file
        /// </summary>
        /// <param name="values">Values for a new record. All values needs to defined and in correct order</param>
        public void InsertNewRecord(params object[] values)
        {
            if (values == null)
            {
                throw new ArgumentNullException("values");
            }

            if (DataTypes.Count != values.Length)
            {
                throw new SqliteException(string.Format("Record in {0} -table requires {1} values to be defined; got {2}", 
                    Name, DataTypes.Count, values.Length));
            }

            var dict = new Dictionary<string, object>();

            for (int i = 0; i < DataTypes.Count; i++)
            {
                var key = DataTypes.Keys.ElementAt(i);
                var value = values[i];
                dict.Add(key, value);
            }

            InsertNewRecord(dict);
        }

        /// <summary>
        /// Inserts a new record in a table in a database file
        /// </summary>
        /// <param name="values">Values for a new record. Values which are not defined in the dictionary will be left empty</param>
        public void InsertNewRecord(IDictionary<string, object> values)
        {
            if (values == null)
            {
                throw new ArgumentNullException("values");
            }

            foreach (var key in values.Keys)
            {
                var value = values[key];

                if (!DataTypes.ContainsKey(key))
                {
                    throw new SqliteException(string.Format("{0} -table does not contain column with name '{1}'", Name, key));
                }
                
                if (!DataTypes[key].Equals(value.GetType()))
                {
                    throw new SqliteException(string.Format("In {0} -table, the data type for column {1} should be {2}; got {3}",
                        Name, key, DataTypes[key].Name, value.GetType().Name));
                }
            }

            var commandBuilder = new StringBuilder();

            commandBuilder.Append(string.Format("insert into {0}(", Name));

            var keys = values.Keys.ToList();

            foreach (var key in keys)
            {
                commandBuilder.Append(key);

                if (keys.IndexOf(key) < (keys.Count - 1))
                {
                    commandBuilder.Append(", ");
                }
            }

            commandBuilder.Append(") VALUES(");

            var valueList = values.Values.ToList();

            int index = 0;

            foreach (var value in valueList)
            {
                commandBuilder.Append(SqlFormat(value));

                if (index < (valueList.Count - 1))
                {
                    commandBuilder.Append(", ");
                }
                index++;
            }

            commandBuilder.Append(")");

            var command = commandBuilder.ToString();

            var parent = m_parent.Target as SqLiteDatabase;
            var granma = parent.Parent.Target as SqLite;

            granma.ExecuteCommand(parent.Location, command);
        }

        /// <summary>
        /// Deletes a record from a table in a database file
        /// </summary>
        /// <param name="conditionKey">Condition key name</param>
        /// <param name="conditionValue">Condition value</param>
        public void DeleteRecord(string conditionKey, object conditionValue)
        {
            CheckColumn(conditionKey);

            conditionValue = SqlFormat(conditionValue);

            var command = string.Format("delete from {0} where {1}={2}", Name, conditionKey, conditionValue);

            var parent = m_parent.Target as SqLiteDatabase;
            var granma = parent.Parent.Target as SqLite;

            granma.ExecuteCommand(parent.Location, command);
        }

        /// <summary>
        /// Gets a value from a table in a database file by its column name
        /// </summary>
        /// <param name="conditionKey">Condition key name</param>
        /// <param name="conditionValue">Condition value</param>
        /// <param name="columnName">Name of the column whose value to get</param>
        /// <returns>Value in the column</returns>
        internal object GetValue(string conditionKey, object conditionValue, string columnName)
        {
            CheckColumn(conditionKey);

            var values = GetRecordValues(conditionKey, conditionValue);

            if (values != null && values.ContainsKey(columnName))
            {
                return values[columnName];
            }

            return null;
        }

        /// <summary>
        /// Sets/updates a value in a table in a database file
        /// </summary>
        /// <param name="conditionKey">Condition key name</param>
        /// <param name="conditionValue">Condition value</param>
        /// <param name="columnName">Name of the column whose value to set</param>
        /// <param name="value">Value to set</param>
        internal void SetValue(string conditionKey, object conditionValue, string columnName, object value)
        {
            CheckColumn(conditionKey);

            var current = GetValue(conditionKey, conditionValue, columnName);

            value = SqlFormat(value);
            conditionValue = SqlFormat(conditionValue);

            if (((current != null && value != null) && (current.GetType().Equals(value.GetType()))) ||
                (current == null && value.Equals("NULL")))
            {
                var command = string.Format("update {0} set {1}={2} where {3}={4}",
                    Name, columnName, value, conditionKey, conditionValue);

                var parent = m_parent.Target as SqLiteDatabase;
                var granma = parent.Parent.Target as SqLite;

                granma.ExecuteCommand(parent.Location, command, false);
            }
        }

        /// <summary>
        /// Verifies that a column with given name exists
        /// </summary>
        /// <param name="columnName">Name of the column</param>
        internal void CheckColumn(string columnName)
        {
            if (string.IsNullOrEmpty(columnName))
            {
                throw new ArgumentNullException("columnName");
            }

            if (!ColumNames.Contains(columnName))
            {
                throw new SqliteException(string.Format("{0} -table does not contain column with name '{1}'",
                    Name, columnName));
            }
        }

        /// <summary>
        /// Gets raw, string presentation of a record in a table in a database file, selected by conditional key-value -pair
        /// </summary>
        /// <param name="conditionKey">Condition key name</param>
        /// <param name="conditionValue">Condition value</param>
        /// <returns>Raw, string presentation of a record in a table in a database file</returns>
        private string GetUnformattedRecord(string conditionKey, object conditionValue)
        {
            conditionValue = SqlFormat(conditionValue);

            var parent = m_parent.Target as SqLiteDatabase;
            var granma = parent.Parent.Target as SqLite;

            var rows = granma.ExecuteCommand(parent.Location,
                string.Format("select * from '{0}' where {1}={2}", Name, conditionKey, conditionValue), false);

            if (rows.Length == 1)
            {
                return rows[0];
            }
            else
            {
                var builder = new StringBuilder();

                foreach (var row in rows)
                {
                    builder.Append(row);
                }
                return builder.ToString();
            }
        }

        /// <summary>
        /// Reads the datatypes
        /// </summary>
        private void Init()
        {
            var parent = m_parent.Target as SqLiteDatabase;
            var granma = parent.Parent.Target as SqLite;

            var columns = granma.ExecuteCommand(parent.Location, string.Format("PRAGMA table_info('{0}');", Name), false);

            var trimmed = new List<string>();

            foreach (var col in columns)
            {
                trimmed.AddRange(col.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries));
            }

            var types = new Dictionary<string, Type>();

            foreach (var col in trimmed)
            {
                var items = col.Split('|');

                if (items.Length > 2)
                {
                    var name = items[1];
                    var typeStr = items[2];

                    if (typeStr == "TEXT")
                    {
                        types.Add(name, typeof(string));
                    }
                    else if (typeStr == "INTEGER")
                    {
                        types.Add(name, typeof(int));
                    }
                    else if (typeStr == "REAL")
                    {
                        types.Add(name, typeof(float));
                    }
                    else if (typeStr == "BOOLEAN")
                    {
                        types.Add(name, typeof(bool));
                    }
                    else if (typeStr == "NULL")
                    {
                        types.Add(name, null);
                    }
                    else
                    {
                        types.Add(name, null);
                    }
                }
            }

            m_dataTypes = types;
        }

        /// <summary>
        /// Formats a value in its SqLite presentation
        /// </summary>
        /// <param name="obj">An object to format</param>
        /// <returns>Formatted value</returns>
        private object SqlFormat(object obj)
        {
            if (obj == null)
            {
                return "NULL";
            }
            else if (obj is string)
            {
                return "'" + (obj as string).Trim('\'') + "'";
            }
            else if (obj is bool)
            {
                return obj.Equals(true) ? 1 : 0;
            }

            return obj;
        }
    }

    /// <summary>
    /// Class presenting a record in a table in a database file
    /// </summary>
    public sealed class SqLiteRecord : PythonCallable
    {
        private WeakReference m_parent;
        private string m_conditionKey;
        private object m_conditionValue;

        /// <summary>
        /// Internal class constructor
        /// </summary>
        /// <param name="parent">Table</param>
        /// <param name="conditionKey">Column name</param>
        /// <param name="conditionValue">Filter value for identifying the correct record</param>
        internal SqLiteRecord(SqLiteTable parent, string conditionKey, object conditionValue)
        {
            m_parent = new WeakReference(parent, false);
            m_conditionKey = conditionKey;
            m_conditionValue = conditionValue;
        }

        /// <summary>
        /// Gets the values in this record
        /// </summary>
        public Dictionary<string, object> Values
        {
            get
            {
                return (m_parent.Target as SqLiteTable).GetRecordValues(m_conditionKey, m_conditionValue);
            }
        }
        
        /// <summary>
        /// Gets an integer value from a given column
        /// </summary>
        /// <param name="columnName">Name of the column</param>
        /// <returns>An integer value from a given column</returns>
        public int GetInt(string columnName)
        {
            return GetValue<int>(columnName);
        }

        /// <summary>
        /// Gets a float value from a given column
        /// </summary>
        /// <param name="columnName">Name of the column</param>
        /// <returns>A float value from a given column</returns>
        public float GetReal(string columnName)
        {
            return GetValue<float>(columnName);
        }

        /// <summary>
        /// Gets a string value from a given column
        /// </summary>
        /// <param name="columnName">Name of the column</param>
        /// <returns>A string value from a given column</returns>
        public string GetString(string columnName)
        {
            return GetValue<string>(columnName);
        }

        /// <summary>
        /// Gets a boolean value from a given column
        /// </summary>
        /// <param name="columnName">Name of the column</param>
        /// <returns>A boolean value from a given column</returns>
        public bool GetBoolean(string columnName)
        {
            return GetValue<bool>(columnName);
        }

        /// <summary>
        /// Sets an integer value to a given column
        /// </summary>
        /// <param name="columName">Name of the column</param>
        /// <param name="value">Integer to set</param>
        public void SetInt(string columName, int value)
        {
            SetValue(columName, value);
        }

        /// <summary>
        /// Sets a float value to a given column
        /// </summary>
        /// <param name="columName">Name of the column</param>
        /// <param name="value">Float to set</param>
        public void SetReal(string columName, float value)
        {
            SetValue(columName, value);
        }

        /// <summary>
        /// Sets a boolean value to a given column
        /// </summary>
        /// <param name="columName">Name of the column</param>
        /// <param name="value">Boolean to set</param>
        public void SetBoolean(string columName, bool value)
        {
            SetValue(columName, value);
        }

        /// <summary>
        /// Sets a string value to a given column
        /// </summary>
        /// <param name="columName">Name of the column</param>
        /// <param name="value">String to set</param>
        public void SetString(string columName, string value)
        {
            SetValue(columName, value);
        }

        /// <summary>
        /// Sets null to a given column
        /// </summary>
        /// <param name="columnName">Name of the column</param>
        public void SetNull(string columnName)
        {
            SetValue(columnName, null);
        }

        /// <summary>
        /// Gets a value from a given column
        /// </summary>
        /// <param name="columnName">Name of the column</param>
        /// <returns>Value from a given column</returns>
        private object GetValue(string columnName)
        {
            return (m_parent.Target as SqLiteTable).GetValue(m_conditionKey, m_conditionValue, columnName);
        }

        /// <summary>
        /// Gets a value from a given column
        /// </summary>
        /// <typeparam name="T">Type in which to cast</typeparam>
        /// <param name="columnName">Name of the column</param>
        /// <returns>Casted value from a given column</returns>
        private T GetValue<T>(string columnName)
        {
            var value = GetValue(columnName);
            if (value != null)
            {
                return (T)value;
            }
            return default(T);
        }

        /// <summary>
        /// Sets a value to a given column
        /// </summary>
        /// <param name="columName">Name of the column</param>
        /// <param name="value">Value to set</param>
        private void SetValue(string columName, object value)
        {
            (m_parent.Target as SqLiteTable).CheckColumn(columName);

            (m_parent.Target as SqLiteTable).SetValue(m_conditionKey, m_conditionValue, columName, value);

            if (columName.Equals(m_conditionKey))
            {
                m_conditionValue = value;
            }
        }
    }
}
