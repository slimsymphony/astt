using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.Design;

namespace TestAutomation.Gui.Marble.Settings
{
    /// <summary>
    /// Custom descriptor for each setting item.
    /// </summary>
    public class SettingDescriptor : PropertyDescriptor
    {
        /// <summary>
        /// The setting item.
        /// </summary>
        private Setting _item;

        /// <summary>
        /// Creates a new <see cref="SettingDescriptor"/> for the setting item.
        /// </summary>
        /// <param name="item">Setting item.</param>
        /// <param name="attributes">Attributes for the setting.</param>
        public SettingDescriptor(ref Setting item, Attribute[] attributes)
            : base(item.Name, attributes)
        {
            // Store the item
            _item = item;
        }

        #region PropertyDescriptor specific

        /// <summary>
        /// Returns whether resetting an object changes its value.
        /// </summary>
        /// <param name="component">The component to test for reset capability.</param>
        /// <returns>Value of <c>false</c>.</returns>
        public override bool CanResetValue(object component)
        {
            return false;
        }

        /// <summary>
        /// Gets the type of the component this property is bound to.
        /// </summary>
        /// <value>A value of <c>null</c> is always returned.</value>
        public override Type ComponentType
        {
            get
            {
                return null;
            }
        }

        /// <summary>
        /// Gets the current value of the property on a component.
        /// </summary>
        /// <param name="component">The component with the property for which to retrieve the value.</param>
        /// <returns>The value of a property for a given component.</returns>
        public override object GetValue(object component)
        {
            return _item.Value;
        }

        /// <summary>
        /// Gets the description of the setting item.
        /// </summary>
        public override string Description
        {
            get
            {
                return _item.Description;
            }
        }

        /// <summary>
        /// Gets the category of the setting item.
        /// </summary>
        public override string Category
        {
            get
            {
                return _item.Category;
            }
        }

        /// <summary>
        /// Gets the display name of the setting item.
        /// </summary>
        public override string DisplayName
        {
            get
            {
                return _item.DisplayName;
            }
        }

        /// <summary>
        /// Gets an editor for the setting.
        /// </summary>
        /// <param name="editorBaseType">The base type of editor, which is used to differentiate between multiple
        /// editors that a property supports.</param>
        /// <returns>An instance of the requested editor type, or <c>null</c> if an editor cannot be
        /// found.</returns>
        public override object GetEditor(Type editorBaseType)
        {
            // If an editor has been specified
            if (_item.Editor != null)
            {
                // Return the editor
                return _item.Editor;
            }

            // Else if the setting value is a list of strings
            else if (_item.Value is List<string>)
            {
                // By default a string collection cannot be modified therefore we will utilize our own string collection editor
                return new StringCollectionEditor(typeof(List<string>));
            }

            // Return the default editor for the type in question
            return base.GetEditor(editorBaseType);
        }

        /// <summary>
        ///  Gets the type converter for this setting.
        /// </summary>
        public override TypeConverter Converter
        {
            get
            {
                // If there is a type converter and an editor specified
                if (_item.Converter != null && _item.Editor == null)
                {
                    // Return the type converter
                    return (TypeConverter)_item.Converter;
                }

                // Return the default converter for the type in question
                return base.Converter;
            }
        }

        /// <summary>
        /// Gets a value indicating whether this setting property is read-only.
        /// </summary>
        /// <value>A value of <c>true</c> is returned if the setting item is read-only for the user, otherwise
        /// <c>false</c> is returned.</value>
        public override bool IsReadOnly
        {
            get
            {
                return _item.ReadOnlyForUser;
            }
        }

        /// <summary>
        /// Determines whether the value of this property needs to be persisted.
        /// </summary>
        /// <param name="component">The component with the property to be examined for persistence.</param>
        /// <value>A value of <c>false</c> is always returned.</value>
        public override bool ShouldSerializeValue(object component)
        {
            return false;
        }

        /// <summary>
        /// Sets the value of the component to a different value.
        /// </summary>
        /// <param name="component">The component with the property value that is to be set.</param>
        /// <param name="value">The new value.</param>
        public override void SetValue(object component, object value)
        {
            // Set the value on the item
            _item.Value = value;
        }
        
        /// <summary>
        /// Gets the type of the property.
        /// </summary>
        public override Type PropertyType
        {
            get 
            { 
                return _item.Value.GetType(); 
            }
        }

        /// <summary>
        /// Resets the value for this property of the component to the default value.
        /// </summary>
        /// <param name="component">The component with the property value that is to be 
        /// reset to the default value.</param>
        /// <remarks>This setting value cannot be reset therefore this method will not perform
        /// any action.</remarks>
        public override void ResetValue(object component) 
        { 
        }

        #endregion
    }

    /// <summary>
    /// Custom string collection editor, which actually allows to edit the collection items
    /// </summary>
    public class StringCollectionEditor : CollectionEditor
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="StringCollectionEditor"/> class.
        /// </summary>
        /// <param name="type">The type of the collection for this editor to edit.</param>
        public StringCollectionEditor(Type type)
            : base(type)
        {
        }

        /// <summary>
        /// Creates a new instance of the specified collection item type.
        /// </summary>
        /// <param name="itemType">The type of item to create.</param>
        /// <returns>A new instance of the specified object.</returns>
        protected override object CreateInstance(Type itemType)
        {
            if (itemType == typeof(String))
                return new String(' ', 0);
            return base.CreateInstance(itemType);
        }
    }
}
