using System;
using System.Collections;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Reflection;
using System.Text;
using TestAutomation.Bridge.Tracing;
using TestAutomation.Client;

namespace TestAutomation.Bridge.ScriptingTools
{
    /// <summary>
    /// Class which, when derived, allows ironPython to call members with de-capitalized names
    /// </summary>
    public abstract class PythonCallable : DynamicObject
    {
        /// <summary>
        /// Tries to get a member: property, field, or event
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="result"></param>
        /// <returns></returns>
        public override bool TryGetMember(GetMemberBinder binder, out object result)
        {
            var members = GetType().GetMembers(BindingFlags.Public | BindingFlags.Instance).ToList();

            var member = members.Find(m =>
                {
                    return __decapitalize__(m.Name).Equals(binder.Name);
                });

            if (member == null && binder.Name.Length > 3)
            {
                var name = binder.Name;
                if (name.StartsWith("get"))
                    name = "get_" + name.Substring(3);
                else if (name.StartsWith("set"))
                    name = "set_" + name.Substring(3);

                member = members.Find(m =>
                {
                    return name.Equals(m.Name);
                });
            }

            if (member != null)
            {
                if (member.MemberType == MemberTypes.Method)
                {
                    result = new DynamicInvoker((args) =>
                        {
                            var method = member as MethodInfo;

                            SelectOverload(ref method, args);

                            Trace.WriteMessage(this, "{0}({1})", binder.Name, Formatting.ToString(args));
                            return method.Invoke(this, args, true);
                        });
                    return true;
                }
                else if (member.MemberType == MemberTypes.Property)
                {
                    result = (member as PropertyInfo).GetValue(this, null);
                    return true;
                }
                else if (member.MemberType == MemberTypes.Field)
                {
                    result = (member as FieldInfo).GetValue(this);
                    return true;
                }
                else if (member.MemberType == MemberTypes.Event)
                {
                    result = EventProxy.Create((member as EventInfo), this);
                }
            }

            return base.TryGetMember(binder, out result);
        }

        /// <summary>
        /// Tries to set a member: property or field or event
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public override bool TrySetMember(SetMemberBinder binder, object value)
        {
            var member = GetType().GetMembers(BindingFlags.Public | BindingFlags.Instance).ToList().Find(m =>
            {
                return __decapitalize__(m.Name).Equals(binder.Name);
            });

            if (member != null)
            {
                if (member.MemberType == MemberTypes.Property)
                {
                    (member as PropertyInfo).SetValue(this, value, null);
                    return true;
                }
                else if (member.MemberType == MemberTypes.Field)
                {
                    (member as FieldInfo).SetValue(this, value);
                    return true;
                }
                else if (member.MemberType == MemberTypes.Event && (value is EventProxy))
                {
                    return true;
                }
            }

            return base.TrySetMember(binder, value);
        }

        /// <summary>
        /// Selects a correct overload for the method: based on the given set of parameters
        /// </summary>
        /// <param name="method">A method for which to search for the overload</param>
        /// <param name="args">Arguments for which the overload should match</param>
        private void SelectOverload(ref MethodInfo method, object[] args)
        {
            var name = method.Name;

            var overload = GetType().GetMethods().ToList().Find(m =>
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
        /// De-capitalizes a string
        /// </summary>
        /// <param name="str">A string to de-capitalize</param>
        /// <returns>Da-capitalized string</returns>
        private string __decapitalize__(string str)
        {
            if (string.IsNullOrEmpty(str))
            {
                return str;
            }

            return char.ToLower(str[0]) + (str.Length > 1 ? str.substring(1) : "");
        }

        /// <summary>
        /// Provides the dir in Python
        /// </summary>
        public virtual List<string> __dir__()
        {
            var members = (new List<MemberInfo>(GetType().GetMembers())).ConvertAll<string>(m => m.Name);
            members.RemoveAll(m => typeof(PythonCallable).GetMembers().Any((pm => pm.Name == m)));
            members.RemoveAll(m => string.Compare(m, ".ctor", true) == 0 || m.StartsWith("__") || 
                ((m.StartsWith("get_") || m.StartsWith("set_")) && members.Contains(m.Substring(4))));
            members = members.ConvertAll<string>(m => __decapitalize__(m));
            members.Sort();
            return members;
        }

        /// <summary>
        /// Equivalent for __len__() -method in Python
        /// </summary>
        /// <returns>Length of the object - if object is not unsized</returns>
        public virtual int __len__()
        {
            var len = GetType().GetProperties().ToList().Find(p => p.Name == "Length" || p.Name == "Count");

            if (len != null)
            {
                return (int)len.GetValue(this);
            }

            throw new TypeError("len() of unsized object");
        }
    }
}
