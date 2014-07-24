using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Text;

namespace TestAutomation.Client
{
    /// <summary>
    /// Abstract base class for implementing a invoker for a remote class for RPC
    /// </summary>
    public abstract class RemoteClassBase : DynamicObject
    {
        private TestServerClient m_tsc;

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="tcs">Instance of test server client class</param>
        internal RemoteClassBase(TestServerClient tcs)
        {
            m_tsc = tcs;
        }

        /// <summary>
        /// Name of the remote class available for RPC
        /// </summary>
        protected abstract string RemoteClassName { get; }

        /// <summary>
        /// Does the dynamic invoking from remote server
        /// </summary>
        /// <param name="binder">Binder which provides the method name of the dynamic call</param>
        /// <param name="args">Arguments for the method</param>
        /// <param name="result">Object</param>
        /// <returns>Always true</returns>
        public override bool TryInvokeMember(InvokeMemberBinder binder, object[] args, out object result)
        {
            result = m_tsc.RemoteInvoke(RemoteClassName, binder.Name, args);
            return true;
        }

        /// <summary>
        /// Returns a delegate for invoking from remote server. This is done as such due to IronPython's inability to distinguish 
        /// a dynamic property getter and dynamic method
        /// </summary>
        /// <param name="binder">Binder which provides the method name of the dynamic call</param>
        /// <param name="result">A delegate for invoking from remote server</param>
        /// <returns>Always true</returns>
        public override bool TryGetMember(GetMemberBinder binder, out object result)
        {
            result = new DynamicInvoker((args) =>
            {
                return m_tsc.RemoteInvoke(RemoteClassName, binder.Name, args);
            });
            return true;
        }
    }
}
