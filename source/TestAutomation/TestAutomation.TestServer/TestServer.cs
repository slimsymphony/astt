using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Security.Cryptography;
using System.Text;

namespace TestAutomation.TestServer
{
    internal static class TestServer
    {
        private const string TaServer = "TAServer.jar";

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        internal static Stream GetServerStream()
        {
            VerifyCaller(Assembly.GetCallingAssembly());
            return GetStream(TaServer);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        internal static string GetServerHash()
        {
            VerifyCaller(Assembly.GetCallingAssembly());
            return GetStreamHash(TaServer);
        }

        /// <summary>
        /// Keep the fuckers away from me
        /// </summary>
        /// <param name="callingAssembly"></param>
        private static void VerifyCaller(Assembly callingAssembly)
        {
            if (callingAssembly == typeof(TestServer).Assembly) return;
            var caller = callingAssembly.GetName().Name;
            var friendDefinifion = typeof(TestServer).Assembly.CustomAttributes.FirstOrDefault(ca => ca.AttributeType == typeof(InternalsVisibleToAttribute));
            if (friendDefinifion == null) return;
            var friendAttribute = friendDefinifion.ConstructorArguments.First();
            var friendName = friendAttribute.Value as string;
            if (friendName == null) return;
            if (string.CompareOrdinal(caller, friendName) == 0) return;
            Process.GetCurrentProcess().Kill();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        private static Stream GetStream(string name)
        {
            VerifyCaller(Assembly.GetCallingAssembly());
            var ms = typeof(TestServer).Assembly.GetManifestResourceNames().ToList().FirstOrDefault(n => n.EndsWith(name));
            return typeof(TestServer).Assembly.GetManifestResourceStream(ms);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        private static string GetStreamHash(string name)
        {
            VerifyCaller(Assembly.GetCallingAssembly());
            var stream = GetStream(name);
            if (stream == null) return null;
            using (stream)
            {
                using (var md5Hash = MD5.Create())
                {
                    var data = md5Hash.ComputeHash(stream);
                    var sBuilder = new StringBuilder();
                    foreach (var t in data)
                    {
                        sBuilder.Append(t.ToString("x2"));
                    }
                    return sBuilder.ToString();
                }
            }
        }
    }
}
