using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestAutomation.Client
{
    /// <summary>
    /// Implements a remote class base for FileSystem RPC
    /// </summary>
    public sealed class RemoteFileSystem : RemoteClassBase
    {
        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="tcs">Instance of test server client class</param>
        internal RemoteFileSystem(TestServerClient tcs) : base(tcs)
        { }

        /// <summary>
        /// "FileSystem"
        /// </summary>
        protected override string RemoteClassName
        {
            get { return "FileSystem"; }
        }
    }
}
