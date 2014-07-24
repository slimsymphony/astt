using System;
using System.Collections;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using TestAutomation.Bridge.Tracing;
using TestAutomation.Client;

namespace TestAutomation.Bridge.ScriptingTools
{
    /// <summary>
    /// Equivalent for Pythons TypeError
    /// </summary>
    public class TypeError : Exception
    {
        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="message">Message to throw. Also formatted string accepted</param>
        /// <param name="args">Parameters for formatted string</param>
        public TypeError(string message, params object[] args)
            : base(string.Format(message, args))
        { }
    }

    /// <summary>
    /// Handler delegate to be used for proxying responses from callable members
    /// </summary>
    /// <param name="result">Original result</param>
    /// <returns>Proxied response</returns>
    public delegate object ResponseProxyHandler(object result);

    /// <summary>
    /// Handler delegate to be used for proxying attributes for methods
    /// </summary>
    /// <param name="args">Original arrays of armuments</param>
    /// <returns>List of converted arguments</returns>
    public delegate IList<object> ArgumentProxyHandler(object[] args);

    /// <summary>
    /// Class for proxying dynamic calls to a real, wrapped instance
    /// </summary>
    public sealed class DynamicProxy : DynamicObject
    {
        private Type m_type;
        private object m_instance;
        private Dictionary<string, List<string>> m_aliases;
        private Dictionary<string, ResponseProxyHandler> m_responseProxies;
        private Dictionary<string, ArgumentProxyHandler> m_argumentProxies;
        private List<string> m_hiddenMembers;
        private DynamicInvoker m_callMethod;

        /// <summary>
        /// Private constructor
        /// </summary>
        /// <param name="type">Type of the instance which to proxy</param>
        /// <param name="instance">The instance which to proxy</param>
        private DynamicProxy(Type type, object instance)
        {
            m_type = type;
            m_instance = instance;

            __allow_decapitalize__ = true;
            __allow_alias__ = true;
            __convert_chars__ = true;

            m_aliases = new Dictionary<string, List<string>>();
            m_responseProxies = new Dictionary<string, ResponseProxyHandler>();
            m_argumentProxies = new Dictionary<string, ArgumentProxyHandler>();
            m_hiddenMembers = new List<string>();
        }

        /// <summary>
        /// Gets or sets a value indicating whether to introduce the decapitalized 
        /// member names of the proxied object (Python naming convensions)
        /// </summary>
        public bool __allow_decapitalize__ { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether to allow use of aliases for the 
        /// members in the proxied object
        /// </summary>
        public bool __allow_alias__ { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether to automatically convert all the 
        /// returning char objects into a string (Python does not have char)
        /// </summary>
        public bool __convert_chars__ { get; set; }

        /// <summary>
        /// Gets the type of the proxied object
        /// </summary>
        public Type __target_type__
        {
            get
            {
                return m_type;
            }
        }

        /// <summary>
        /// Gets the proxied object
        /// </summary>
        public object __target_instance__
        {
            get
            {
                return m_instance;
            }
        }

        /// <summary>
        /// Equivalent for __call__() -method in Python
        /// </summary>
        /// <param name="args"></param>
        /// <returns></returns>
        public object __call__(params object[] args)
        {
            if (m_callMethod != null)
            {
                return m_callMethod(args);
            }

            var method = __get_member__("__call__");

            if (method != null && method.MemberType == MemberTypes.Method)
            {
                return ((MethodInfo)method).Invoke(m_instance, args, true);
            }

            throw new TypeError("{0} is not callable", m_type.Name);
        }

        /// <summary>
        /// Provides the dir in Python
        /// </summary>
        public List<string> __dir__()
        {
            var list = new List<string>();

            var members = (new List<MemberInfo>(m_type.GetMembers(__get_flags__()))).ConvertAll<string>(m => m.Name);

            members.RemoveAll(m => m_hiddenMembers.Contains(m));

            members.Sort();

            if (__allow_decapitalize__)
            {
                var members2 = (new List<MemberInfo>(m_type.GetMembers(__get_flags__()))).ConvertAll<string>(m => __decapitialize__(m.Name));
                members2.Sort();
                members2.RemoveAll(m => m_hiddenMembers.Contains(m));
                members.AddRange(members2);
            }
            if (__allow_alias__)
            {
                m_aliases.Values.ToList().ForEach(l => members.AddRange(l));
            }

            members.RemoveAll(m => string.Compare(m, ".ctor", true) == 0);

            foreach (var member in members)
            {
                if (!list.Contains(member))
                {
                    list.Add(member);
                }
            }

            return list;
        }

        /// <summary>
        /// Equivalent for __len__() -method in Python
        /// </summary>
        /// <returns>Length of the proxied object - if object is not unsized</returns>
        public int __len__()
        {
            var len = m_type.GetProperties().ToList().Find(p => p.Name == "Length" || p.Name == "Count");

            if (len != null)
            {
                return (int)len.GetValue(m_instance);
            }

            throw new TypeError("len() of unsized object");
        }

        /// <summary>
        /// Allows to redirect the __call__() -method to elsewhere
        /// </summary>
        /// <param name="method">Methdod for which to route the __call__() -method</param>
        public void __set_call__(DynamicInvoker method)
        {
            m_callMethod = method;
        }

        /// <summary>
        /// Removes the __call__() -method redirection (if any)
        /// </summary>
        public void __remove_call__()
        {
            m_callMethod = null;
        }

        /// <summary>
        /// Sets an alias for a member in the proxied object
        /// </summary>
        /// <param name="memberName">Name of the member for which to introduce the aliases</param>
        /// <param name="value">Either a string or a collection of strings</param>
        public void __alias__(string memberName, object value)
        {
            __alias__(new Dictionary<object, object>() { { memberName, value } });
        }

        /// <summary>
        /// Sets aliases for members in the proxied object
        /// </summary>
        /// <param name="value">A dictionary in which the key is a member name; and value 
        /// is either a string or a collection of strings</param>
        public void __alias__(IDictionary<object, object> value)
        {
            if (value == null || value.Count == 0)
            {
                return;
            }
            foreach (var key in value.Keys)
            {
                var member = __get_member__(key as string);

                if (member == null)
                {
                    continue;
                }

                var alias = value[key as string];

                var list = (alias is string) ? new List<string>(new string[] { alias as string }) :
                    (typeof(IList<object>).IsAssignableFrom(alias.GetType()) ? (alias as IList<object>).Cast<string>().ToList() :
                    null);

                if (list != null)
                {
                    foreach (var reserved in m_aliases.Values.ToList())
                    {
                        foreach (var reservedAlias in reserved)
                        {
                            if (list.Contains(reservedAlias))
                            {
                                throw new ArgumentException(string.Format("Alias: {0} is already in use", reservedAlias));
                            }
                        }
                    }


                    if (m_aliases.ContainsKey(key as string))
                    {
                        m_aliases[key as string] = list;
                    }
                    else
                    {
                        m_aliases.Add(key as string, list);
                    }
                }
            }
        }

        /// <summary>
        /// Hides the given members by name
        /// </summary>
        /// <param name="memberName">Names of members to hide</param>
        public void __hide__(params string[] memberNames)
        {
            foreach (var memberName in memberNames)
            {
                if (!m_hiddenMembers.Contains(memberName))
                {
                    m_hiddenMembers.Add(memberName);
                }
            }
        }

        /// <summary>
        /// Sets a proxy via which to route any response from a given callable member
        /// </summary>
        /// <param name="memberName">Name of the callable member</param>
        /// <param name="proxy">Handler for the reponses</param>
        public void __set_response_proxy__(string memberName, ResponseProxyHandler proxy)
        {
            if (proxy != null)
            {
                if (m_responseProxies.ContainsKey(memberName))
                {
                    m_responseProxies[memberName] = proxy;
                }
                else
                {
                    m_responseProxies.Add(memberName, proxy);
                }
            }
        }

        /// <summary>
        /// Removes any response proxy from a member by its name
        /// </summary>
        /// <param name="memberName">Name of the callable member</param>
        public void __remove_response_proxy__(string memberName)
        {
            if (m_responseProxies.ContainsKey(memberName))
            {
                m_responseProxies.Remove(memberName);
            }
        }

        /// <summary>
        /// Sets a proxy via which to route any set of arguments from a given callable method
        /// </summary>
        /// <param name="methodName">Name of the method</param>
        /// <param name="proxy">Handler for the arguments</param>
        public void __set_argument_proxy__(string methodName, ArgumentProxyHandler proxy)
        {
            if (proxy != null)
            {
                if (m_argumentProxies.ContainsKey(methodName))
                {
                    m_argumentProxies[methodName] = proxy;
                }
                else
                {
                    m_argumentProxies.Add(methodName, proxy);
                }
            }
        }

        /// <summary>
        /// Removes any argument proxy from a method by its name
        /// </summary>
        /// <param name="methodName">Name of the method</param>
        public void __remove_argument_proxy__(string methodName)
        {
            if (m_argumentProxies.ContainsKey(methodName))
            {
                m_argumentProxies.Remove(methodName);
            }
        }

        /// <summary>
        /// Presents the __call__() -method 
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="args"></param>
        /// <param name="result"></param>
        /// <returns></returns>
        public override bool TryCreateInstance(CreateInstanceBinder binder, object[] args, out object result)
        {
            result = __call__(args);
            return true;
        }

        /// <summary>
        /// Sets an value to property/field/event in the proxied object
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public override bool TrySetMember(SetMemberBinder binder, object value)
        {
            var member = __get_member__(binder.Name);

            if (member != null)
            {
                if (member.MemberType == MemberTypes.Property)
                {
                    var property = (PropertyInfo)member;
                    property.SetValue(m_instance, value, null);
                    return true;
                }
                else if (member.MemberType == MemberTypes.Field)
                {
                    var field = (FieldInfo)member;
                    field.SetValue(m_instance, value);
                    return true;
                }
                else if (member.MemberType == MemberTypes.Event && (value is EventProxy))
                {
                    return true;
                }
            }

            return false;
        }

        /// <summary>
        /// With Python, most of the calls goes via member call, even the method invokes
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="result"></param>
        /// <returns></returns>
        public override bool TryGetMember(GetMemberBinder binder, out object result)
        {
            result = null;

            var name = binder.Name;

            var member = __get_member__(name);

            if (member != null)
            {
                if (member.MemberType == MemberTypes.Event)
                {
                    var @event = (EventInfo)member;
                    result = EventProxy.Create(@event, m_instance);
                    return true;
                }
                else if (member.MemberType == MemberTypes.Property)
                {
                    var property = (PropertyInfo)member;
                    result = property.GetValue(m_instance, null);
                    name = property.Name;
                }
                else if (member.MemberType == MemberTypes.Field)
                {
                    var field = (FieldInfo)member;
                    result = field.GetValue(m_instance);
                    name = field.Name;
                }
                else if (member.MemberType == MemberTypes.Method)
                {
                    var method = (MethodInfo)member;

                    result = new DynamicInvoker((args) =>
                    {
                        if (m_argumentProxies.ContainsKey(binder.Name))
                        {
                            args = m_argumentProxies[binder.Name](args).ToArray();
                        }

                        SelectOverload(ref method, args);

                        Trace.WriteMessage(m_instance, "{0}({1})", binder.Name, Formatting.ToString(args));

                        var resp = method.Invoke(m_instance, args, true);

                        if (m_responseProxies.ContainsKey(binder.Name))
                        {
                            resp = m_responseProxies[binder.Name](resp);
                        }

                        else if ((resp is char) && __convert_chars__)
                        {
                            resp = ((char)resp).ToString();
                        }

                        return resp;
                    });

                    return true;
                }
            }

            if (result != null)
            {
                if (m_responseProxies.ContainsKey(name))
                {
                    result = m_responseProxies[name](result);
                }
                else if ((result is char) && __convert_chars__)
                {
                    result = ((char)result).ToString();
                }
                return true;
            }

            return false;
        }

        /// <summary>
        /// Gets an object in the given index (if indexer implmented) from the proxied object
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="indexes"></param>
        /// <param name="result"></param>
        /// <returns></returns>
        public override bool TryGetIndex(GetIndexBinder binder, object[] indexes, out object result)
        {
            if (m_instance != null && (typeof(ICollection).IsAssignableFrom(m_type) || m_type.IsArray))
            {
                var len = m_type.IsArray ? ((Array)m_instance).Length : (m_instance as ICollection).Count;
                if (indexes[0] is int)
                {
                    int index = (int)indexes[0];

                    if (index < 0)
                    {
                        index = len - Math.Abs(index);
                        indexes = new object[] { index };
                    }

                    if (index > (len - 1))
                    {
                        throw new ArgumentOutOfRangeException("index");
                    }
                }
            }

            var indexers = m_type.GetProperties(__get_flags__()).ToList().FindAll(p => p.GetIndexParameters().Length > 0);
            if (indexers != null)
            {
                var indexer = indexers.Find(i =>
                {
                    return i.GetIndexParameters().ToList().Exists(p => p.ParameterType.Equals(indexes[0].GetType()));
                });

                if (indexer != null)
                {
                    result = indexer.GetValue(m_instance, indexes);
                    return true;
                }
            }

            result = null;
            return false;
        }

        /// <summary>
        /// Sets an object for the given index (if indexer implmented) in the proxied object
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="indexes"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public override bool TrySetIndex(SetIndexBinder binder, object[] indexes, object value)
        {
            if (m_instance != null && (typeof(ICollection).IsAssignableFrom(m_type) || m_type.IsArray))
            {
                var len = m_type.IsArray ? ((Array)m_instance).Length : (m_instance as ICollection).Count;
                if (indexes.Length == 1 && indexes[0] is int)
                {
                    int index = (int)indexes[0];

                    if (index < 0)
                    {
                        index = len - Math.Abs(index);
                        indexes = new object[] { index };
                    }

                    if (index > (len - 1))
                    {
                        throw new ArgumentOutOfRangeException("index");
                    }
                }
            }

            var indexers = m_type.GetProperties(__get_flags__()).ToList().FindAll(p => p.GetIndexParameters().Length > 0);
            if (indexers != null)
            {
                var indexer = indexers.Find(i =>
                {
                    return i.GetIndexParameters().ToList().Exists(p => p.ParameterType.Equals(indexes[0].GetType()));
                });

                if (indexer != null)
                {
                    indexer.SetValue(m_instance, value, indexes);
                    return true;
                }
            }

            return false;
        }

        /// <summary>
        /// Handles the Enumerator queries for the proxied object
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="result"></param>
        /// <returns></returns>
        public override bool TryConvert(ConvertBinder binder, out object result)
        {
            if ((binder.Type.Equals(typeof(IEnumerable)) && m_instance is IEnumerable) ||
                (binder.Type.Equals(typeof(IEnumerator)) && m_instance is IEnumerable))
            {
                result = binder.Type.Equals(typeof(IEnumerable)) ? m_instance : (m_instance as IEnumerable).GetEnumerator();
                return true;
            }

            return base.TryConvert(binder, out result);
        }

        /// <summary>
        /// Handles the unary operations for the proxied object
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="result"></param>
        /// <returns></returns>
        public override bool TryUnaryOperation(UnaryOperationBinder binder, out object result)
        {
            if (m_instance != null)
            {
                bool success = true;
                dynamic instance = m_instance as dynamic;

                if (binder.Operation == System.Linq.Expressions.ExpressionType.Increment)
                {
                    instance++;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.Decrement)
                {
                    instance--;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.OnesComplement)
                {
                    instance = m_type.Equals(typeof(bool)) ? !instance : ~instance;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.Not)
                {
                    instance = !instance;
                }
                else
                {
                    success = false;
                }

                if (success)
                {
                    result = instance;
                    return true;
                }
            }

            return base.TryUnaryOperation(binder, out result);
        }

        /// <summary>
        /// Handles the binary operations for the proxied object
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="arg"></param>
        /// <param name="result"></param>
        /// <returns></returns>
        public override bool TryBinaryOperation(BinaryOperationBinder binder, object arg, out object result)
        {
            if (m_instance != null)
            {
                bool success = true;
                dynamic instance = (dynamic)(object)m_instance;
                dynamic value = (dynamic)arg;

                if (binder.Operation == System.Linq.Expressions.ExpressionType.Add)
                {
                    instance = instance + value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.AddAssign)
                {
                    instance += value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.Subtract)
                {
                    instance = instance - value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.SubtractAssign)
                {
                    instance -= value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.Multiply)
                {
                    instance = instance * value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.MultiplyAssign)
                {
                    instance *= value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.Divide)
                {
                    instance = instance / value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.DivideAssign)
                {
                    instance /= value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.Modulo)
                {
                    instance = instance % value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.ModuloAssign)
                {
                    instance %= value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.And)
                {
                    instance = instance & value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.AndAssign)
                {
                    instance &= value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.Or)
                {
                    instance = instance | value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.OrAssign)
                {
                    instance |= value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.GreaterThan)
                {
                    instance = (instance > value);
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.GreaterThanOrEqual)
                {
                    instance = (instance >= value);
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.LessThan)
                {
                    instance = (instance < value);
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.LessThanOrEqual)
                {
                    instance = (instance <= value);
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.Equal)
                {
                    instance = (instance == value);
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.NotEqual)
                {
                    instance = (instance != value);
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.ExclusiveOr)
                {
                    instance = instance ^ value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.ExclusiveOrAssign)
                {
                    instance = instance ^= value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.LeftShift)
                {
                    instance = instance << value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.LeftShiftAssign)
                {
                    instance = instance <<= value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.RightShift)
                {
                    instance = instance >> value;
                }
                else if (binder.Operation == System.Linq.Expressions.ExpressionType.RightShiftAssign)
                {
                    instance = instance >>= value;
                }
                else
                {
                    success = false;
                }

                if (success)
                {
                    result = instance;
                    return true;
                }
            }

            return base.TryBinaryOperation(binder, arg, out result);
        }

        /// <summary>
        /// Calls the ToString/__str__ -method from the proxied object 
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return m_instance != null ? m_instance.ToString() : string.Format("<type '{0}'>", m_type.Name);
        }

        /// <summary>
        /// Calls the Equals -method from the proxied object 
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        public override bool Equals(object obj)
        {
            return m_instance != null ? m_instance.Equals(obj) : false;
        }

        /// <summary>
        /// Calls the GetHashCode -method from the proxied object 
        /// </summary>
        /// <returns></returns>
        public override int GetHashCode()
        {
            return m_instance != null ? m_instance.GetHashCode() : 0;
        }

        /// <summary>
        /// Calls the GetType -method from the proxied object 
        /// </summary>
        /// <returns></returns>
        public new Type GetType()
        {
            return m_type;
        }

        /// <summary>
        /// Creates a new proxy object for static calls
        /// </summary>
        /// <param name="type">Type of class whose static calls are about to be proxied</param>
        /// <returns>New dynamic proxy object for the static calls of the given type</returns>
        public static DynamicProxy __create__(Type type)
        {
            return __create__(type, null);
        }

        /// <summary>
        /// Creates a new proxy object for non-static calls
        /// </summary>
        /// <param name="instance">The object to be proxied</param>
        /// <returns>New dynamic proxy object for the non-static calls for the object</returns>
        public static DynamicProxy __create__(object instance)
        {
            return __create__(instance.GetType(), instance);
        }

        /// <summary>
        /// Creates a new proxy object either for static or non-static calls
        /// </summary>
        /// <param name="type">Type of class whose calls are about to be proxied</param>
        /// <param name="instance">The object to be proxied; null if static calls are about to be proxied</param>
        /// <returns>New dynamic proxy object for either the static or non-static calls</returns>
        private static DynamicProxy __create__(Type type, object instance)
        {
            return new DynamicProxy(type, instance);
        }

        /// <summary>
        /// Gets a member whith a given name from the proxied object
        /// </summary>
        /// <param name="name">Name of the member to get</param>
        /// <returns>Ifo of the member if found; null otherwise</returns>
        private MemberInfo __get_member__(string name)
        {
            //Is hidden
            if (m_hiddenMembers.Contains(name))
            {
                return null;
            }

            var members = new List<MemberInfo>(m_type.GetMembers(__get_flags__()));

            //Is found directly without tricks
            var member = members.Find(m =>
            {
                return (m.MemberType == MemberTypes.Method ||
                       m.MemberType == MemberTypes.Field ||
                       m.MemberType == MemberTypes.Property ||
                       m.MemberType == MemberTypes.Event) &&
                       m.Name.Equals(name);
            });
            //Is found by de-capitalizing the member name (C# -> Python -naming conventions)
            if (member == null && __allow_decapitalize__)
            {
                member = members.Find(m =>
                {
                    return (m.MemberType == MemberTypes.Method ||
                           m.MemberType == MemberTypes.Field ||
                           m.MemberType == MemberTypes.Property ||
                           m.MemberType == MemberTypes.Event) &&
                           __decapitialize__(m.Name).Equals(name);
                });
            }
            //Is found by alias
            if (member == null && __allow_alias__)
            {
                member = members.Find(m =>
                {
                    return (m.MemberType == MemberTypes.Method ||
                        m.MemberType == MemberTypes.Field ||
                        m.MemberType == MemberTypes.Property ||
                        m.MemberType == MemberTypes.Event) &&
                        (m_aliases.ContainsKey(m.Name) && m_aliases[m.Name].Contains(name));
                });
            }
            //Is found by de-capitalized alias
            if (member == null && __allow_alias__ && __allow_decapitalize__)
            {
                member = members.Find(m =>
                {
                    return (m.MemberType == MemberTypes.Method ||
                        m.MemberType == MemberTypes.Field ||
                        m.MemberType == MemberTypes.Property ||
                        m.MemberType == MemberTypes.Event) &&
                        (m_aliases.ContainsKey(__decapitialize__(m.Name)) && m_aliases[__decapitialize__(m.Name)].Contains(name));
                });
            }
            //Is getter or setter for a property
            if (member == null && name.Length > 3)
            {
                if (__allow_decapitalize__)
                {
                    name = __decapitialize__(name);
                }

                if (name.StartsWith("get"))
                    name = "get_" + name.Substring(3);
                else if (name.StartsWith("set"))
                    name = "set_" + name.Substring(3);

                member = members.Find(m =>
                {
                    return name.Equals(m.Name);
                });
            }

            return member;
        }

        /// <summary>
        /// Selects a correct overload for the method: based on the given set of parameters
        /// </summary>
        /// <param name="method">A method for which to search for the overload</param>
        /// <param name="args">Arguments for which the overload should match</param>
        private void SelectOverload(ref MethodInfo method, object[] args)
        {
            var name = method.Name;

            var overload = m_instance.GetType().GetMethods(__get_flags__()).ToList().Find(m =>
            {
                if (string.Compare(m.Name, name, false) == 0)
                {
                    var @params = m.GetParameters().ToList();
                    if (@params.Count == args.Length)
                    {
                        var paramTypes = @params.ConvertAll<Type>(p => p.ParameterType);

                        for (int i = 0; i < paramTypes.Count; i++)
                        {
                            if (paramTypes[i].Equals(typeof(object)))
                            {
                                continue;
                            }
                            var canBeNull = !paramTypes[i].IsValueType || (Nullable.GetUnderlyingType(paramTypes[i]) != null);
                            if ((args[i] == null && !canBeNull) ||
                                (args[i] != null && !args[i].GetType().Equals(paramTypes[i]) &&
                                (!paramTypes[i].IsAssignableFrom(args[i].GetType()))))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }
                return false;
            });

            if (overload == null)
            {
                throw new TargetParameterCountException("Could not found method supporting parameters: " + Formatting.ToString(args));
            }

            method = overload;
        }

        /// <summary>
        /// Gets binding flags to use when navigating for the members in the proxied object
        /// Static flag is activated automatically when the proxied object is null
        /// </summary>
        /// <returns>Appropriate flasg</returns>
        private BindingFlags __get_flags__()
        {
            BindingFlags flags = BindingFlags.Public | BindingFlags.Instance;

            if (m_instance == null)
            {
                flags |= BindingFlags.Static;
            }

            return flags;
        }

        /// <summary>
        /// Decapitalizes a given string
        /// </summary>
        /// <param name="str">A string to decapitalize</param>
        /// <returns>Decapitalized string</returns>
        private string __decapitialize__(string str)
        {
            if (string.IsNullOrEmpty(str))
            {
                return str;
            }

            return char.ToLower(str[0]) + (str.Length > 1 ? str.Substring(1) : "");
        }
    }
}
