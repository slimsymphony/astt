using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Runtime.Serialization;

namespace TestAutomation.Gui.Marble.Settings
{
    /// <summary>
    /// Class representing an individual setting.
    /// </summary>
    [Serializable()]
    public class Setting : ISerializable
    {
        /// <summary>
        /// Object used for synchronization.
        /// </summary>
        private static object _locker = new object();

        /// <summary>
        /// Name of the setting.
        /// </summary>
        private string _name = null;

        /// <summary>
        /// Display name of the setting.
        /// </summary>
        private string _displayName = null;

        /// <summary>
        /// Description of the setting.
        /// </summary>
        private string _description = null;

        /// <summary>
        /// Category for the setting.
        /// </summary>
        private string _category = null;

        /// <summary>
        /// Value of the setting.
        /// </summary>
        private object _value = null;

        /// <summary>
        /// Editor to be used to view or edit the setting.
        /// </summary>
        private object _editor = null;

        /// <summary>
        /// Converter to convert the setting value.
        /// </summary>
        private object _converter = null;

        /// <summary>
        /// Flag that indicates whether this setting is read-only for the user.
        /// </summary>
        private bool _readOnlyForUser = false;

        /// <summary>
        /// Cancel value of the setting.
        /// </summary>
        private object _cancelValue = null;

        /// <summary>
        /// Prevent an instance of this object from being created externally.
        /// </summary>
        internal Setting()
        {
        }

        /// <summary>
        /// Creates a new <see cref="Setting"/> object from the serialization information.
        /// </summary>
        /// <param name="info">Holds the data for the setting.</param>
        /// <param name="context">Describes the serialization stream.</param>
        public Setting(SerializationInfo info, StreamingContext context)
        {
            // Get the type and value of the setting
            Type type = (Type)info.GetValue("Type", typeof(Type));
            Value = info.GetValue("Value", type);

            this.CancelValue = Value;

            // Get the name of the setting
            Name = (string)info.GetValue("Name", typeof(string));
        }

        /// <summary>
        /// Gets the data from the setting and adds it to the serialization information.
        /// </summary>
        /// <param name="info">Holds the data for the setting.</param>
        /// <param name="context">Describes the serialization stream.</param>
        public void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            // Add the type and value of the setting
            info.AddValue("Type", Value.GetType());
            info.AddValue("Value", Value);

            // Add the name of the setting
            info.AddValue("Name", Name);
        }
        
        /// <summary>
        /// Name of the setting.
        /// </summary>
        public string Name
        {
            get
            {
                lock (_locker)
                {
                    return _name;
                }
            }
            internal set
            {
                lock (_locker)
                {
                    _name = value;
                }
            }
        }

        /// <summary>
        /// Value of the setting.
        /// </summary>
        public object Value
        {
            get
            {
                lock (_locker)
                {
                    return _value;
                }
            }
            internal set
            {
                lock (_locker)
                {
                    _value = value;

                    if (this.CancelValue == null) this.CancelValue = value;
                }
            }
        }

        /// <summary>
        /// Description of the setting.
        /// </summary>
        public string Description
        {
            get
            {
                lock (_locker)
                {
                    return _description;
                }
            }
            internal set
            {
                lock (_locker)
                {
                    _description = value;
                }
            }
        }

        /// <summary>
        /// Display name of the setting.
        /// </summary>
        public string DisplayName
        {
            get
            {
                lock (_locker)
                {
                    return _displayName;
                }
            }
            internal set
            {
                lock (_locker)
                {
                    _displayName = value;
                }
            }
        }

        /// <summary>
        /// Category for the setting.
        /// </summary>
        public string Category
        {
            get
            {
                lock (_locker)
                {
                    return _category;
                }
            }
            internal set
            {
                lock (_locker)
                {
                    _category = value;
                }
            }
        }

        /// <summary>
        /// Editor to be used to view or edit the setting.
        /// </summary>
        public object Editor
        {
            get
            {
                lock (_locker)
                {
                    return _editor;
                }
            }
            internal set
            {
                lock (_locker)
                {
                    _editor = value;
                }
            }
        }

        /// <summary>
        /// Converter to convert the setting value.
        /// </summary>
        public object Converter
        {
            get
            {
                lock (_locker)
                {
                    return _converter;
                }
            }
            internal set
            {
                lock (_locker)
                {
                    _converter = value;
                }
            }
        }

        /// <summary>
        ///  Flag that indicates whether this setting is read-only for the user.
        /// </summary>
        public bool ReadOnlyForUser
        {
            get
            {
                lock (_locker)
                {
                    return _readOnlyForUser;
                }
            }
            internal set
            {
                lock (_locker)
                {
                    _readOnlyForUser = value;
                }
            }
        }


        /// <summary>
        /// Gets the cancel value for the setting.
        /// </summary>
        public object CancelValue
        {
            get
            {
                lock (_locker)
                {
                    return _cancelValue;
                }
            }
            internal set
            {
                lock (_locker)
                {
                    _cancelValue = value;
                }
            }
        }
    }
}
