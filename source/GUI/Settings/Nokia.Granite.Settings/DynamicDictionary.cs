using System;
using System.Collections;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq.Expressions;
using System.Reflection;
using System.Runtime.Serialization;
using System.Xml;
using System.Xml.Serialization;

namespace TestAutomation.Gui.Marble.Settings
{
    /// <summary>
    /// Static class with methods for processing dictionaries.
    /// </summary>
    public static class DynamicDictionary
    {
        /// <summary>
        /// Creates a new dynamic dictionary from the dictionary interface.
        /// </summary>
        /// <param name="dictionary">Dictionary interface.</param>
        /// <returns>New dynamic dictionary populated with keys and values.</returns>
        public static object FromDictionary(IDictionary dictionary)
        {
            // Get the type of the keys and values
            Type[] elementTypes = (dictionary as IDictionary).GetMemberTypes();

            // Create a new instance of a dictionary using the specified key and value types
            IDictionary newDictionary = (IDictionary)Activator.CreateInstance(typeof(DynamicDictionary<,>).MakeGenericType(elementTypes));

            // For each key
            foreach (var key in (dictionary as IDictionary).Keys)
            {
                // Add the key and value to the new dictionary 
                newDictionary.Add(Converters.ConvertToDynamic(key), Converters.ConvertToDynamic((dictionary as IDictionary)[key]));
            }

            return newDictionary;
        }
    }

    /// <summary>
    /// Template class for a dynamic dictionary with specified types for the keys and values.
    /// </summary>
    /// <typeparam name="TKey"></typeparam>
    /// <typeparam name="TValue"></typeparam>
    [Serializable()]
    [XmlRoot(XmlTabs.DICTIONARY)]
    public class DynamicDictionary<TKey, TValue> : Dictionary<TKey, TValue>, IDynamicMetaObjectProvider, IXmlSerializableCollection, ISerializable
    {
        /// <summary>
        /// Creates a new empty <see cref="DynamicDictionary"/> object.
        /// </summary>
        public DynamicDictionary()
            : base()
        { 
        }

        /// <summary>
        /// Creates a new empty <see cref="DynamicDictionary"/> object that has the 
        /// specified initial capacity.
        /// </summary>
        /// <param name="capacity">The initial number of elements that the dictionary
        /// can contain.</param>
        public DynamicDictionary(int capacity)
            : base(capacity)
        { }

        /// <summary>
        /// Creates a new <see cref="DynamicDictionary"/> object that contains elements
        /// copied from the specified dictionary interface.
        /// </summary>
        /// <param name="dictionary">The dictionary interface whose elements are
        /// copied to the new dictionary.</param>
        public DynamicDictionary(IDictionary<TKey, TValue> dictionary)
            : base(dictionary)
        { }

        /// <summary>
        /// Creates a new <see cref="DynamicDictionary"/> object with serialized data.
        /// </summary>
        /// <param name="info">A <see cref="System.Runtime.Serialization.SerializationInfo"/> 
        /// object containing the information required to serialize the dictionary.
        /// </param>
        /// <param name="context">A <see cref="System.Runtime.Serialization.StreamingContext"/> 
        /// structure containing the source and destination of the serialized stream 
        /// associated with the dictionary.</param>
        public DynamicDictionary(SerializationInfo info, StreamingContext context) 
            : base(info, context)
        { }

        public new void Add(TKey key, TValue value)
        {
            if (key == null)
                return;

            if (ContainsKey(key))
            {
                this[key] = value;
            }
            else base.Add(key, value);
        }

        public DynamicMetaObject GetMetaObject(System.Linq.Expressions.Expression parameter)
        {
            return new DynamicDictionaryMetaObject(parameter, this);
        }

        private class DynamicDictionaryMetaObject : DynamicMetaObject
        {
            internal DynamicDictionaryMetaObject(Expression parameter,
                DynamicDictionary<TKey, TValue> value)
                : base(parameter, BindingRestrictions.Empty, value)
            { }

            public override DynamicMetaObject BindGetMember(GetMemberBinder binder)
            {
                string methodName = "GetValue";

                // One parameter
                Expression[] parameters = new Expression[]
            {
                Expression.Constant(binder.Name)
            };

                DynamicMetaObject getDictionaryEntry = new DynamicMetaObject(
                    Expression.Call(
                        Expression.Convert(Expression, LimitType),
                        typeof(DynamicDictionary<TKey, TValue>).GetMethod(methodName, BindingFlags.NonPublic | BindingFlags.Instance),
                        parameters),
                    BindingRestrictions.GetTypeRestriction(Expression, LimitType));
                return getDictionaryEntry;
            }

            public override DynamicMetaObject BindSetMember(SetMemberBinder binder, DynamicMetaObject value)
            {
                // Method to call in the containing class:
                string methodName = "SetValue";

                // setup the binding restrictions.
                BindingRestrictions restrictions =
                    BindingRestrictions.GetTypeRestriction(Expression, LimitType);

                // setup the parameters:
                Expression[] args = new Expression[2];
                // First parameter is the name of the property to Set
                args[0] = Expression.Constant(binder.Name);
                // Second parameter is the value
                args[1] = Expression.Convert(value.Expression, typeof(object));

                // Setup the 'this' reference
                Expression self = Expression.Convert(Expression, LimitType);

                // Setup the method call expression
                Expression methodCall = Expression.Call(self,
                        typeof(DynamicDictionary<TKey, TValue>).GetMethod(methodName, BindingFlags.NonPublic | BindingFlags.Instance),
                        args);

                // Create a meta object to invoke Set later:
                DynamicMetaObject setDictionaryEntry = new DynamicMetaObject(
                    methodCall,
                    restrictions);
                // return that dynamic object
                return setDictionaryEntry;
            }
        }

        private object GetValue(TKey key)
        {
            return base[key];
        }

        private object SetValue(TKey key, TValue value)
        {
            base[key] = value;
            return null;
        }

        public System.Xml.Schema.XmlSchema GetSchema()
        {
            return null;
        }

        /// <summary>
        /// Reads the XML content and adds the keys and values to this dictionary.
        /// </summary>
        /// <param name="reader">XML reader used to read the XML elements.</param>
        public void ReadXml(XmlReader reader)
        {
            bool isEmpty = reader.IsEmptyElement;
            reader.Read();

            if (isEmpty)
                return;

            while (reader.NodeType != XmlNodeType.EndElement)
            {
                object key = new object();
                object value = new object();

                // Read the dictionary item start element
                reader.ReadStartElement(XmlTabs.DICTIONARY_ITEM);

                // Read the dictionary item key start element
                reader.ReadStartElement(XmlTabs.DICTIONARY_ITEM_KEY);
                var keyType = reader.Name;

                if (keyType == XmlTabs.LIST)
                {
                    SerializableList<object> list = new SerializableList<object>();
                    list.ReadXml(reader);
                    key = Converters.ConvertToDynamic(list);
                }
                else if (keyType == XmlTabs.DICTIONARY)
                {
                    var dictionary = new DynamicDictionary<object, object>();
                    dictionary.ReadXml(reader);
                    key = Converters.ConvertToDynamic(dictionary);
                }
                else
                {
                    isEmpty = reader.IsEmptyElement;
                    string keyContent = reader.ReadString();
                    key = Converters.ConvertFromString(keyContent, keyType);
                    if (isEmpty)
                    {
                        // Move on to the next node
                        reader.Read();
                    }

                    else
                    {
                        // Read the key type end element
                        reader.ReadEndElement();
                    }
                }

                // Read the dictionary item key end element
                reader.ReadEndElement();

                // Read the dictionary item value start element
                reader.ReadStartElement(XmlTabs.DICTIONARY_ITEM_VALUE);
                var valueType = reader.Name;

                if (valueType == XmlTabs.LIST)
                {
                    SerializableList<object> list = new SerializableList<object>();
                    list.ReadXml(reader);
                    value = Converters.ConvertToDynamic(list);
                }
                else if (valueType == XmlTabs.DICTIONARY)
                {
                    var dictionary = new DynamicDictionary<object, object>();
                    dictionary.ReadXml(reader);
                    value = Converters.ConvertToDynamic(dictionary);
                }
                else
                {
                    isEmpty = reader.IsEmptyElement;
                    string valueContent = reader.ReadString();
                    value = Converters.ConvertFromString(valueContent, valueType);
                    if (isEmpty)
                    {
                        // Move on to the next node
                        reader.Read();
                    }

                    else
                    {
                        // Read the key type end element
                        reader.ReadEndElement();
                    }
                }

                // Read the dictionary item value end element
                reader.ReadEndElement();

                // Add the key and value to the dictionary
                Add((TKey)key, (TValue)value);

                reader.Read();
            }

            reader.ReadEndElement();
        }

        /// <summary>
        /// Writes the dictionary to XML.
        /// </summary>
        /// <param name="writer">XML writer used to write the XML elements.</param>
        public void WriteXml(XmlWriter writer)
        {
            foreach (TKey key in this.Keys)
            {
                // Write the dictionary item start element
                writer.WriteStartElement(XmlTabs.DICTIONARY_ITEM);

                // Write the dictionary item key start element
                writer.WriteStartElement(XmlTabs.DICTIONARY_ITEM_KEY);

                // Write the dictionary key
                writer.WriteStartElement(Converters.GetAlias(key.GetType()));
                writer.WriteString(Converters.ConvertToString(key, key.GetType()));
                writer.WriteEndElement();

                // Write the dictionary item key end element
                writer.WriteEndElement();

                // Get the value
                TValue value = this[key];

                // Write the dictionary item value start element
                writer.WriteStartElement(XmlTabs.DICTIONARY_ITEM_VALUE);

                // Get the value type
                Type valueType = value.GetType();

                // If this value type is a collection that we can serialize
                if (typeof(IXmlSerializableCollection).IsAssignableFrom(valueType))
                {
                    // Serialize the collection
                    XmlSerializer serializer = new XmlSerializer(valueType);
                    serializer.Serialize(writer, value);
                }

                // Else this value type is not a collection
                else
                {
                    // Write the value
                    writer.WriteStartElement(Converters.GetAlias(valueType));
                    writer.WriteString(Converters.ConvertToString(value, valueType));
                    writer.WriteEndElement();
                }

                // Write the dictionary item value end element
                writer.WriteEndElement();

                // Write the dictionary item end element
                writer.WriteEndElement();
            }
        }
    }

}
