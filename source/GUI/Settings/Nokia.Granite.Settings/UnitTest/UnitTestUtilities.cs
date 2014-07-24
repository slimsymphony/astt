using System.IO;
using System.Reflection;
using System.Text;

namespace TestAutomation.Gui.Marble.Settings.UnitTest
{
    /// <summary>
    /// Utilities class that contains common methods used for unit testing.
    /// </summary>
    internal static class UnitTestUtilities
    {
        /// <summary>
        /// Namespace prefix used for the embedded resources names.
        /// </summary>
        static readonly string _dataNamespacePrefix = "TestAutomation.Gui.Marble.Settings.UnitTest.Data.";

        /// <summary>
        /// Extracts an embedded resource settings file and creates the specified the target file.
        /// </summary>
        /// <param name="embeddedResourceFileName">Name of the embedded resource (e.g. 'MySettings.xml').</param>
        /// <param name="targetFilePath">Target file to created from the embedded resource.</param>
        internal static void CreatingSettingsFile(string embeddedResourceFileName, string targetFilePath)
        {
            string embeddedResourceName = _dataNamespacePrefix + embeddedResourceFileName;

            // Get the stream for the embedded resource
            using (Stream resourceStream = Assembly.GetExecutingAssembly().GetManifestResourceStream(embeddedResourceName))
            {
                // Read the contents
                byte[] contents = new byte[resourceStream.Length];
                resourceStream.Read(contents, 0, contents.Length);

                // Write the contents to the target file
                using (FileStream targetFile = new FileStream(targetFilePath, FileMode.Create))
                {
                    targetFile.Write(contents, 0, contents.Length);
                }
            }
        }

        /// <summary>
        /// Gets the contents of an embedded resource.
        /// </summary>
        /// <param name="embeddedResourceFileName">Name of the embedded resource (e.g. 'MySettings.xml').</param>
        /// <returns>Contents of the embedded resource.</returns>
        internal static string GetEmbeddedResourceContents(string embeddedResourceFileName)
        {
            string textContents = null;
            string embeddedResourceName = _dataNamespacePrefix + embeddedResourceFileName;

            // Get the stream for the embedded resource
            using (Stream resourceStream = Assembly.GetExecutingAssembly().GetManifestResourceStream(embeddedResourceName))
            {
                // Read the contents
                byte[] contents = new byte[resourceStream.Length];
                resourceStream.Read(contents, 0, contents.Length);

                // Convert the contents to text
                textContents = UTF8Encoding.UTF8.GetString(contents);
            }

            return textContents;
        }
    }
}
