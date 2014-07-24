using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Numerics;
using System.Reflection;

namespace TestAutomation.Gui.Marble.Settings
{
    /// <summary>
    /// Extension class used to determine whether a type is a dictionary or collection.
    /// </summary>
    internal static class TypeExtensions
    {
        /// <summary>
        /// Determines whether the type is a dictionary.
        /// </summary>
        /// <param name="type">The type.</param>
        /// <returns>Value of <c>true</c> if the type is a dictionary, otherwise <c>false</c> is returned.</returns>
        internal static bool IsDictionary(this Type type)
        {
            return typeof(IDictionary).IsAssignableFrom(type);
        }

        /// <summary>
        /// Determines whether the type is a collection.
        /// </summary>
        /// <param name="type">The type.</param>
        /// <returns>Value of <c>true</c> if the type is a collection, otherwise <c>false</c> is returned.</returns>
        internal static bool IsCollection(this Type type)
        {
            return typeof(ICollection).IsAssignableFrom(type) && !IsDictionary(type);
        }
    }

    /// <summary>
    /// Delegate used to invoke a method with a number of arguments.
    /// </summary>
    /// <param name="args">Argument to supply.</param>
    /// <returns>Return value from invoking the method.</returns>
    internal delegate object InvokeDelegate(params object[] args);

    /// <summary>
    /// Class used to help identify whether a member name is a fixed member call, method, property or field.
    /// </summary>
    internal static class MemberBinder
    {
        public static bool IsFixedMemberCall(string memberName, object target, out object value)
        {
            value = null;

            if (IsPropertyCall(memberName, target, out value))
            {
                return true;
            }
            InvokeDelegate invoker;
            if (IsMethodCall(memberName, target, out invoker))
            {
                value = invoker;
                return true;
            }
            if (IsFieldCall(memberName, target, out value))
            {
                return true;
            }

            return false;

        }

        private static bool IsMethodCall(string memberName, object target, out InvokeDelegate invoker)
        {
            invoker = null;

            var method = target.GetType().GetMethod(memberName);

            if (method != null)
            {
                invoker = new InvokeDelegate((args) =>
                {
                    var expectedParams = method.GetParameters();

                    if (expectedParams.Length > args.Length)
                    {
                        var newParams = args.ToList();

                        for (int i = args.Length; i < expectedParams.Length; i++)
                        {
                            if (expectedParams[i].Attributes.HasFlag(ParameterAttributes.Optional) &&
                                expectedParams[i].Attributes.HasFlag(ParameterAttributes.HasDefault))
                            {
                                newParams.Add(expectedParams[i].DefaultValue);
                            }
                        }

                        args = newParams.ToArray();
                    }

                    return method.Invoke(target, args);
                });

                return true;
            }

            return false;
        }

        private static bool IsPropertyCall(string memberName, object target, out object value)
        {
            value = null;

            var property = target.GetType().GetProperty(memberName);

            if (property != null)
            {
                value = property.GetValue(target, null);
                return true;
            }

            return false;
        }

        private static bool IsFieldCall(string memberName, object target, out object value)
        {
            value = null;

            var field = target.GetType().GetField(memberName);

            if (field != null)
            {
                value = field.GetValue(target);
                return true;
            }

            return false;
        }
    }

    /// <summary>
    /// Extension class to process dictionaries and collections.
    /// </summary>
    internal static class CollectionExtensions
    {
        /// <summary>
        /// Gets the type of the keys and values.
        /// </summary>
        /// <param name="dictionary">Dictionary.</param>
        /// <returns>Array containing the type for the keys and the type for the values.</returns>
        public static Type[] GetMemberTypes(this IDictionary dictionary)
        {
            // Get the type of the keys
            var keyType = GetMemberType(dictionary.Keys);

            // Get the type of the values
            var valueType = GetMemberType(dictionary.Values);

            return new Type[] { keyType, valueType };
        }

        /// <summary>
        /// Gets the types of the members in the collection.
        /// </summary>
        /// <param name="collection">Collection from which to get its member types.</param>
        /// <returns>Type of the members in the collection.</returns>
        public static Type GetMemberType(this ICollection collection)
        {
            if (collection.Count == 0)
            {
                var t = collection.GetType();

                var elementType = t.HasElementType ? t.GetElementType() : (t.IsGenericType ? t.GetGenericArguments().First() : null );

                if (elementType == null)
                {
                    var ti = t.GetInterfaces().ToList().Find(i => i.IsGenericType);
                    if (ti != null)
                    {
                        elementType = ti.GetGenericArguments().First();
                    }
                }

                return elementType ?? typeof(object);
            }

            var types = new List<Type>();
            bool containsNull = false;
            foreach (var item in collection)
            {
                if (item != null)
                {
                    var type = item.GetType();

                    if (!types.Contains(type))
                    {
                        types.Add(type);
                    }
                }
                else
                {
                    containsNull = true;
                }
            }

            if (types.TrueForAll(type => typeof(IDictionary).IsAssignableFrom(type)))
            {
                return typeof(IDictionary);
            }

            if (types.TrueForAll(type => typeof(ICollection).IsAssignableFrom(type)))
            {
                return typeof(ICollection);
            }

            if (types.Count > 0 && types.TrueForAll(type => type == types[0]))
            {
                if (types[0].IsValueType && containsNull)
                {
                    return typeof(object);
                }
                return types[0];
            }

            return typeof(object);
        }
    }

    /// <summary>
    /// Class used to perform type conversion to and from their alias names.
    /// </summary>
    internal static class Converters
    {
        /// <summary>
        /// Compares two objects and determines whether they match or not.
        /// </summary>
        /// <param name="firstObject">First object.</param>
        /// <param name="secondObject">Second object.</param>
        /// <returns>Value of <c>true</c> if they match, otherwise false is returned.</returns>
        internal static bool ObjectsMatch(object firstObject, object secondObject)
        {
            if (firstObject == null && secondObject == null)
            {
                return true;
            }

            if (firstObject == null || secondObject == null)
            {
                return false;
            }

            if (firstObject.GetType() != secondObject.GetType())
            {
                return false;
            }

            if (firstObject.GetType().IsDictionary())
            {
                var keys1 = ((IDictionary)firstObject).Keys;
                var values1 = ((IDictionary)firstObject).Values;

                var keys2 = ((IDictionary)secondObject).Keys;
                var values2 = ((IDictionary)secondObject).Values;

                return ObjectsMatch(keys1, keys2) && ObjectsMatch(values1, values2);
            }
            else if (!firstObject.GetType().IsCollection())
            {
                return firstObject.Equals(secondObject);
            }
            else
            {
                if (((ICollection)firstObject).Count != ((ICollection)secondObject).Count)
                {
                    return false;
                }

                IEnumerator firstEnumerator = ((ICollection)firstObject).GetEnumerator();
                IEnumerator secondEnumerator = ((ICollection)secondObject).GetEnumerator();

                while (firstEnumerator.MoveNext() && secondEnumerator.MoveNext())
                {
                    if (!ObjectsMatch(firstEnumerator.Current, secondEnumerator.Current))
                    {
                        return false;
                    }
                }

                return true;
            }
        }

        internal static object ConvertToDynamic(object obj)
        {
            if (obj == null)
            {
                return null;
            }

            if (obj.GetType().IsDictionary())
            {
                return DynamicDictionary.FromDictionary(obj as IDictionary);
            }
            else if (obj.GetType().IsCollection())
            {
                return SerializableList.FromCollection(obj as ICollection);
            }

            return ConvertBig(obj);
        }

        /// <summary>
        /// Dictionary that converts the .NET types to an alias name.
        /// </summary>
        private static readonly Dictionary<Type, string> Aliases =
            new Dictionary<Type, string>()
        {
            { typeof(byte), "byte" },
            { typeof(sbyte), "sbyte" },
            { typeof(short), "short" },
            { typeof(ushort), "ushort" },
            { typeof(int), "int" },
            { typeof(uint), "uint" },
            { typeof(long), "long" },
            { typeof(ulong), "ulong" },
            { typeof(float), "float" },
            { typeof(double), "double" },
            { typeof(decimal), "decimal" },
            { typeof(object), "object" },
            { typeof(bool), "bool" },
            { typeof(char), "char" },
            { typeof(string), "string" },
            { typeof(BigInteger), "bigInt" },
            { typeof(DateTime), "date" }
        };

        /// <summary>
        /// Dictionary that converts the alias names to a .NET type.
        /// </summary>
        private static readonly Dictionary<string, Type> RealTypes =
            new Dictionary<string, Type>()
        {
            { "byte", typeof(byte) },
            { "sbyte", typeof(sbyte) },
            { "short", typeof(short) },
            { "ushort", typeof(ushort) },
            { "int", typeof(int) },
            { "uint", typeof(uint) },
            { "long", typeof(long) },
            { "ulong", typeof(ulong) },
            { "float", typeof(float) },
            { "double", typeof(double) },
            { "decimal", typeof(decimal) },
            { "object", typeof(object) },
            { "bool", typeof(bool) },
            { "char", typeof(char) },
            { "string", typeof(string) },
            { "bigInt", typeof(BigInteger) },
            { "date", typeof(DateTime) }
        };

        /// <summary>
        /// Converts a string value to a specified target type name.
        /// </summary>
        /// <param name="value">Value to be converted.</param>
        /// <param name="targetTypeName">Target type name.</param>
        /// <returns>Value converted to the specified type, or <c>null</c> if the value could not be converted.</returns>
        public static object ConvertFromString(string value, string targetTypeName)
        {
            Type type = Type.GetType(targetTypeName);

            if (type == null)
            {
                if (!RealTypes.TryGetValue(targetTypeName, out type))
                {
                    type = typeof(string);
                }
            }

            return ConvertFromString(value, type);
        }

        /// <summary>
        /// Converts a string value to a specified target type.
        /// </summary>
        /// <param name="value">Value to be converted.</param>
        /// <param name="targetType">Target type.</param>
        /// <returns>Value converted to the specified type, or the supplied <paramref name="value"/> string if the value could not be converted.</returns>
        public static object ConvertFromString(string value, Type targetType)
        {
            try
            {
                // Convert the invariant string to a value
                return TypeDescriptor.GetConverter(targetType).ConvertFromInvariantString(value);
            }

            catch (Exception ex)
            {
                if (ex is NotSupportedException)
                {
                    return value;
                }

                return TypeDescriptor.GetConverter(targetType).ConvertFromString(value);
            }
        }

        /// <summary>
        /// Converts a value of a specified type to a string.
        /// </summary>
        /// <param name="value">Value to be converted.</param>
        /// <param name="type">Value type.</param>
        /// <returns>Value converted to a string.</returns>
        public static string ConvertToString(object value, Type type)
        {
            // Convert the value to an invariant string
            return TypeDescriptor.GetConverter(type).ConvertToInvariantString(value);
        }

        /// <summary>
        /// Gets the alias name for the specified type.
        /// </summary>
        /// <param name="type">Type to convert to an alias.</param>
        /// <returns>Alias name if the type could be converted, otherwise the original type name is returned.</returns>
        public static string GetAlias(Type type)
        {
            string name;
            if (Aliases.TryGetValue(type, out name))
            {
                return name;
            }
            return type.Name;
        }

        /// <summary>
        /// /// Gets the alias name for the template type.
        /// </summary>
        /// <typeparam name="T">Template type.</typeparam>
        /// <returns>Alias name if the type could be converted, otherwise the original type name is returned.</returns>
        public static string GetAlias<T>()
        {
            return GetAlias(typeof(T));
        }

        /// <summary>
        /// Converts a <see cref="BigInteger"/> to an integer, long, unsigned long or float
        /// depending on its value.
        /// </summary>
        /// <param name="value">Value of the number.</param>
        /// <returns>Number converted to an integer, long, unsigned long or float value.</returns>
        public static object ConvertBig(object value)
        {
            if (value.GetType() == typeof(BigInteger))
            {
                var big = (BigInteger)value;

                if (big.IsZero)
                {
                    return 0;
                }

                if (big >= int.MinValue && big <= int.MaxValue)
                {
                    return (int)big;
                }
                else if (big >= long.MinValue && big <= long.MaxValue)
                {
                    return (long)big;
                }
                else if (big.Sign > 0 && big <= ulong.MaxValue)
                {
                    return (ulong)big;
                }
                else
                {
                    return (float)big;
                }
            }

            return value;
        }
    }
}
