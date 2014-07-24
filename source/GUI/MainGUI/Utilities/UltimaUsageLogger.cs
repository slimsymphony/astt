using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;

namespace Marble.Utilities
{
    public class UltimaUsageLogger
    {
        private static bool ValidateRemoteCertificat‌e(Object sender, System.Security.Cryptography.X509Certificates.X509Certificate certificate, System.Security.Cryptography.X509Certificates.X509Chain chain, System.Net.Security.SslPolicyErrors sslPolicyErrors)
        {
            return true;
        }

        public static bool SendMarbleUsageToUltima(string version)
        {
            DateTime timeStamp = DateTime.Now;
            string user = Environment.UserName;
            string host = Environment.MachineName;
            string time = timeStamp.Hour.ToString("D2") + timeStamp.Minute.ToString("D2") + timeStamp.Second.ToString("D2");
            string date = Convert.ToString(timeStamp.Year) + timeStamp.Month.ToString("D2") + timeStamp.Day.ToString("D2");
            string application = "Ultima Usage Collector"; 
            string tool = "Marble";
            string[] splitStrings = new string[] { "Marble -", " - " };
            version = version.Split(splitStrings, System.StringSplitOptions.RemoveEmptyEntries)[0].Trim();
            string ultimaAPIKey = "553aa300c55f131484eb5fc2296e0ffc";
            string md5Check = string.Empty;

            string fileContents = String.Format("USER:{0},APPLICATION:{1},APPLICATION_VERSION:1.0,HOST:{2},TOOL:{3},TOOL_VERSION:{4},DATE:{5},TIME:{6}", user, application, host, tool, version, date, time);
            try
            {
                System.IO.File.WriteAllText("ultima.txt", fileContents);

                using (var md5 = System.Security.Cryptography.MD5.Create())
                {
                    using (var stream = File.OpenRead("ultima.txt"))
                    {
                        md5Check = BitConverter.ToString(md5.ComputeHash(stream)).Replace("-", string.Empty).ToLower();
                    }

                    md5Check = BitConverter.ToString(md5.ComputeHash(Encoding.UTF8.GetBytes(ultimaAPIKey + md5Check))).Replace("-", string.Empty).ToLower();
                }
            }
            catch
            {
                return false;
            }

            // Set callback-method to handle possible expired certificate-error
            ServicePointManager.ServerCertificateValidationCallback += new System.Net.Security.RemoteCertificateValidationCallback(ValidateRemoteCertificat‌e);

            WebClient webClient = new System.Net.WebClient();

            try
            {
                webClient.UploadFile(String.Format("https://ultima.nokia.com/eedb/usageFileEndpoint.action?app={0}&check={1}", application, md5Check), "ultima.txt");
            }
            catch (WebException e)
            {
                return false;
            }
            return true;
        }
    }
}
