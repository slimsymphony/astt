using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace TestAutomation.Bridge.ScriptingTools
{
    /// <summary>
    /// Class extensions for classes under ScriptingTools namespace
    /// </summary>
    internal static class Extensions
    {
        /// <summary>
        /// Invokes a method normally, but in case of TargetInvocationException, throws the original exception
        /// </summary>
        /// <param name="methodInfo"></param>
        /// <param name="obj"></param>
        /// <param name="parameters"></param>
        /// <param name="throwOriginalException"></param>
        /// <returns></returns>
        internal static object Invoke(this MethodInfo methodInfo, object obj, object[] parameters, bool throwOriginalException)
        {
            try
            {
                return methodInfo.Invoke(obj, parameters);
            }
            catch (TargetInvocationException tie)
            {
                if (throwOriginalException)
                {
                    throw ScriptException.FromException(tie.InnerException ?? tie);
                }
                else
                {
                    throw ScriptException.FromException(tie);
                }
            }
            catch (Exception ex)
            {
                throw ScriptException.FromException(ex);
            }
        }
    }
}
