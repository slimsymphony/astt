using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Xml;
using System.Xml.Serialization;

namespace TestAutomation.Gui.Marble.Settings
{
    /// <summary>
    /// Static class used to provide functionality for a list that can be serialized.
    /// </summary>
    public static class SerializableList
    {
        /// <summary>
        /// Creates a new list from the collection interface.
        /// </summary>
        /// <param name="collection">Collection interface.</param>
        /// <returns>New list populated with items.</returns>
        public static object FromCollection(ICollection collection)
        {
            // Get the type of the items
            Type elementType = (collection as ICollection).GetMemberType();

            // Get the type for the list
            Type listType = typeof(SerializableList<>).MakeGenericType(elementType);

            // Create a new instance of a list using the specified list type
            IList list = (IList)Activator.CreateInstance(listType);

            // For each item
            foreach (var item in (collection as ICollection))
            {
                // Add the item to the new list
                list.Add(Converters.ConvertToDynamic(item));
            }

            return list;
        }
    }

    /// <summary>
    /// Template class for a list which can be serialized with a specified type for the item.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    [Serializable()]
    [XmlRoot(XmlTabs.LIST)]
    public class SerializableList<T> : List<T>, IXmlSerializableCollection
    {
        /// <summary>
        /// Creates a new empty <see cref="SerializableList"/> object.
        /// </summary>
        public SerializableList()
            : base()
        { 
        }

        /// <summary>
        /// Creates a new empty <see cref="SerializableList"/> object that has the 
        /// specified initial capacity.
        /// </summary>
        /// <param name="capacity">The initial number of items that the list
        /// can contain.</param>
        public SerializableList(int capacity)
            : base(capacity)
        { 
        }

        /// <summary>
        /// Creates a new <see cref="SerializableList"/> object that contains elements 
        /// copied from the specified collection.
        /// </summary>
        /// <param name="collection">The collection whose elements are copied to the new list.</param>
        public SerializableList(IEnumerable<T> collection)
            : base(collection)
        { 
        }

        /// <summary>
        /// Creates a new <see cref="SerializableList"/> object with serialized data.
        /// </summary>
        /// <param name="info">A <see cref="System.Runtime.Serialization.SerializationInfo"/> 
        /// object containing the information required to serialize the list.
        /// </param>
        /// <param name="context">A <see cref="System.Runtime.Serialization.StreamingContext"/> 
        /// structure containing the source and destination of the serialized stream 
        /// associated with the list.</param>
        public SerializableList(SerializationInfo info, StreamingContext context)
        { 
        }

        public System.Xml.Schema.XmlSchema GetSchema()
        {
            return null;
        }

        /// <summary>
        /// Clears the list then reads the XML content and adds the items to this list.
        /// </summary>
        /// <param name="reader">XML reader used to read the XML elements.</param>
        public void ReadXml(XmlReader reader)
        {
            Clear();

            bool isEmpty = reader.IsEmptyElement;
            reader.Read();

            if (isEmpty)
                return;

            while (reader.NodeType != XmlNodeType.EndElement)
            {
                string type = reader.Name;

                if (type == XmlTabs.LIST)
                {
                    SerializableList<object> list = new SerializableList<object>();
                    list.ReadXml(reader);
                    this.Add((T)Converters.ConvertToDynamic(list));
                }
                else if (type == XmlTabs.DICTIONARY)
                {
                    var dictionary = new DynamicDictionary<object, object>();
                    dictionary.ReadXml(reader);
                    this.Add((T)Converters.ConvertToDynamic(dictionary));
                }
                else
                {
                    string itemContent = reader.ReadString();
                    this.Add((T)Converters.ConvertFromString(itemContent, type));
                    reader.Read();
                }
            }
            reader.ReadEndElement();
        }

        /// <summary>
        /// Writes the dictionary to XML.
        /// </summary>
        /// <param name="writer">XML writer used to write the XML elements.</param>
        public void WriteXml(XmlWriter writer)
        {
            foreach (var item in this)
            {
                Type itemType = item.GetType();
                if (typeof(IXmlSerializableCollection).IsAssignableFrom(itemType))
                {
                    XmlSerializer serializer = new XmlSerializer(itemType);
                    serializer.Serialize(writer, item);
                }
                else
                {
                    writer.WriteStartElement(Converters.GetAlias(itemType));
                    writer.WriteString(Converters.ConvertToString(item, itemType));
                    writer.WriteEndElement();
                }
            }
        }
    }
}
