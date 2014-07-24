using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Web;
using System.IO;
using System.Xml;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Xml.Linq;
using System.Xml.XPath;
using System.Collections.Concurrent;

using System.Diagnostics;

namespace TestAutomation.Gui.Marble.QC
{
    public class MarbleQCInterface : IMarbleQCInterface
    {
        private Cookie lwssoCookie = null;
        private Cookie qcSessionCookie = null;

        private string URL = "https://qc11.nokia.com/qcbin/";
        private string username, password;

        ~MarbleQCInterface()
        {
            LogOut();
        }

        /// <summary>
        /// Check whether it is necessary to log in
        /// </summary>
        public bool NeedCredentials()
        {
            HttpWebRequest request;
            HttpWebResponse response;

            request = GetRequest("rest/is-authenticated", "GET");

            try
            {
                response = (HttpWebResponse)request.GetResponse();
            }
            catch (WebException e)
            {

                HttpWebResponse errorResp = e.Response as HttpWebResponse;
                if (errorResp == null)
                {
                    throw e;
                }
                else if (errorResp.StatusCode == HttpStatusCode.Unauthorized)
                {
                    errorResp.Close();
                    return true;
                }
                else
                {
                    errorResp.Close();
                    throw e;
                }
            }
            response.Close();
            return false;
        }

        /// <summary>
        /// Sends authentication to server if needed
        /// </summary>
        /// <param name="username">Username.</param>
        /// <param name="password">Password.</param>
        public string Authenticate(string username = "", string password = "", string url = "")
        {
            string result = "OK";
            HttpWebRequest request;
            HttpWebResponse response;

            if (username != "")
            {
                this.username = username;
                this.password = password;
            }

            if (url != "")
            {
                URL = url;
            }

            if (!NeedCredentials())
            {
                return result;
            }

            request = GetRequest("authentication-point/authenticate", "POST");
            if (username != "")
            {
                request.Credentials = new NetworkCredential(username, password);
            }
            else
            {
                request.Credentials = new NetworkCredential(this.username, this.password);
            }

            try
            {
                response = (HttpWebResponse)request.GetResponse();
                lwssoCookie = response.Cookies["LWSSO_COOKIE_KEY"];
                result = response.StatusCode.ToString();
            }
            catch (WebException e)
            {
                HttpWebResponse errorResp = e.Response as HttpWebResponse;

                if (errorResp.StatusCode == HttpStatusCode.Unauthorized)
                {
                    result = e.Response.Headers["WWW-Authenticate"];
                    result = result.Split('=').Last();
                    errorResp.Close();
                    return result;
                }
                else
                {
                    errorResp.Close();
                    throw e;
                }
            }
            response.Close();
            return result;
        }

        /// <summary>
        /// Downloads Domains and projects from server
        /// </summary>
        public XElement GetDomainsAndProjects()
        {
            HttpWebRequest request;
            HttpWebResponse response;
            XElement returnXml = null;

            Authenticate();
            request = GetRequest("rest/domains?include-projects-info=y", "GET");


            response = (HttpWebResponse)request.GetResponse();

            if (qcSessionCookie == null)
            {
                qcSessionCookie = response.Cookies["QCSession"];
            }
            StreamReader reader = new StreamReader(response.GetResponseStream());
            returnXml = XDocument.Load(reader).Root;
            reader.Dispose();
            response.Close();

            return returnXml;
        }

        /// <summary>
        /// Downloads contents of test-set-folder defined by nodeId
        /// </summary>
        /// <param name="domain">Domain of test-set-folder.</param>
        /// <param name="project">Project of test-set-folder.</param>
        /// <param name="nodeId">Id of the test-set-folder node which contents should be downloaded.</param>
        public XElement GetTestLabViewNode(string domain, string project, string nodeId)
        {
            HttpWebRequest request;
            HttpWebResponse response;
            XmlDocument doc = new XmlDocument();
            XElement returnXml = null;
            XmlElement testSetFolders, testSets, testLabNode;

            Authenticate();

            request = GetRequest(String.Format("rest/domains/{0}/projects/{1}/test-set-folders?query={{parent-id[{2}]}}&fields=name,id", domain, project, nodeId), "GET");



            response = (HttpWebResponse)request.GetResponse();
            if (qcSessionCookie == null)
            {
                qcSessionCookie = response.Cookies["QCSession"];
            }
            using (StreamReader reader = new StreamReader(response.GetResponseStream()) as StreamReader)
            {
                testLabNode = doc.CreateElement("test-lab-node");
                testSetFolders = doc.CreateElement("test-set-folders");
                testSetFolders.InnerXml = reader.ReadToEnd();
            }
            response.Close();

            testSetFolders.InnerXml = testSetFolders.SelectSingleNode("Entities").InnerXml;
            testLabNode.AppendChild(testSetFolders);

            request = GetRequest(String.Format("rest/domains/{0}/projects/{1}/test-sets?query={{parent-id[{2}]}}&fields=name,id", domain, project, nodeId), "GET");

            response = (HttpWebResponse)request.GetResponse();
            using (StreamReader reader = new StreamReader(response.GetResponseStream()) as StreamReader)
            {
                testSets = doc.CreateElement("test-sets");
                testSets.InnerXml = reader.ReadToEnd();
            }
            response.Close();
            testSets.InnerXml = testSets.SelectSingleNode("Entities").InnerXml;
            testLabNode.AppendChild(testSets);


            using (StringReader stringReader = new StringReader(testLabNode.OuterXml) as StringReader)
            {
                returnXml = XDocument.Load(stringReader).Root;
            }

            return returnXml;

        }

        /// <summary>
        /// Downloads test-set which matches testSetID. Downloaded test set is converted to be compatible with Marble
        /// </summary>
        /// <param name="domain">Domain of test-set.</param>
        /// <param name="project">Project of test-set.</param>
        /// <param name="testSetID">Id of the test-set which should be downloaded.</param>
        /// <param name="marbleScriptPath">Path to scripts which should be used to construct the test set.</param>
        public XElement GetTestSet(string domain, string project, string testSetID, string marbleScriptPath)
        {
            HttpWebRequest request;
            HttpWebResponse response;
            XDocument qcTestSet = null;
            XElement marbleTestSet = null;

            Authenticate();

            request = GetRequest(String.Format("rest/domains/{0}/projects/{1}/test-instances?query={{test-set.id[{2}]}}&" +
                "fields=test.user-template-13,test.name,test.user-template-24,test.user-template-09,test.user-template-17,test.user-template-30,id,test-instance,test-order,cycle-id",
                domain, project, testSetID), "GET");

            response = (HttpWebResponse)request.GetResponse();
            if (qcSessionCookie == null)
            {
                qcSessionCookie = response.Cookies["QCSession"];
            }
            using (StreamReader reader = new StreamReader(response.GetResponseStream()) as StreamReader)
            {
                qcTestSet = XDocument.Load(reader);
            }
            response.Close();
            marbleTestSet = convertToMarbleTestSet(qcTestSet, marbleScriptPath);
            if (marbleTestSet == null)
                return null;

            // Add url, domain, project and testSetId to marbleTestSet
            marbleTestSet.SetAttributeValue("server-url", URL);
            marbleTestSet.SetAttributeValue("domain", domain);
            marbleTestSet.SetAttributeValue("project", project);
            marbleTestSet.SetAttributeValue("testSet-id", testSetID);


            return marbleTestSet;
        }


        /// <summary>
        /// Logs out from QC server
        /// </summary>
        public void LogOut()
        {
            HttpWebRequest request;
            HttpWebResponse response;

            request = GetRequest("authentication-point/logout", "GET");
            response = (HttpWebResponse)request.GetResponse();
            response.Close();

        }

        /// <summary>
        /// Builds HttpWebRequest using given url and method
        /// </summary>
        /// <param name="url">suffix to be appended to base url.</param>
        /// <param name="method">HTTP method to be used.</param>
        private HttpWebRequest GetRequest(string url, string method)
        {
            HttpWebRequest request;
            request = (HttpWebRequest)WebRequest.Create(URL + url);

            request.CookieContainer = new CookieContainer();
            request.Method = method;
            request.ContentType = "application/xml";
            request.Accept = "application/xml";
            if (lwssoCookie != null)
            {
                request.CookieContainer.Add(lwssoCookie);
            }
            if (qcSessionCookie != null)
            {
                request.CookieContainer.Add(qcSessionCookie);
            }

            return request;
        }

        /// <summary>
        /// Method converts a test set downloaded from QC to Marble test set format
        /// </summary>
        /// <param name="qcTestSet">Test set downloaded from QC</param>
        /// <param name="marbleScriptPath">Path to root folder of scripts which are going to be used in Marble test set</param>
        /// <returns>Test set in Marble format</returns>
        private XElement convertToMarbleTestSet(XDocument qcTestSet, string marbleScriptPath)
        {
            XElement convertedTestSet = null;
            Regex reUcId = new Regex(@"(?<=@ucId )([A-Za-z0-9]*)", RegexOptions.Compiled);
            Regex reMethod = new Regex(@"(?<=def )([A-Za-z0-9]*)", RegexOptions.Compiled);
            Regex reClass = new Regex(@"(?<=class )([A-Za-z0-9]*)", RegexOptions.Compiled);


            if (!Directory.Exists(marbleScriptPath))
            {
                throw new DirectoryNotFoundException(String.Format("Directory {0} not found", marbleScriptPath));
            }

            int testsInSet = 0;
            convertedTestSet = new XElement("testset");
            string[] testScripts = Directory.GetFiles(marbleScriptPath, "*.py", SearchOption.AllDirectories);

            // Loop through all test script files to find test cases with ucId-attribute.
            // When test case with ucId is found check if matching ucId is found from qcTestSet.
            // If ucId is found from qcTestSet also add new node to convertedTestSet

            ConcurrentStack<Dictionary<string, string>> testCaseStack = new ConcurrentStack<Dictionary<string, string>>();

            Parallel.ForEach(testScripts, scriptPath =>
            {
                MatchCollection matchingLines = null;
                Match ucIdMatch, methodMatch, classMatch;

                int ucIdLinesFound = 0;

                string[] scriptLines = File.ReadAllLines(scriptPath);
                string scriptText = File.ReadAllText(scriptPath);
                matchingLines = reUcId.Matches(scriptText);
                ucIdLinesFound = matchingLines.Count;
                XElement qcTestCase = null;


                if (ucIdLinesFound > 0)
                {
                    List<Dictionary<string, string>> scriptsToTestSet = new List<Dictionary<string, string>>();
                    Dictionary<string, string> testCaseInfo = null;

                    for (int i = scriptLines.Length - 1; i >= 0 && ucIdLinesFound > 0; i--)
                    {
                        ucIdMatch = reUcId.Match(scriptLines[i]);
                        methodMatch = reMethod.Match(scriptLines[i]);
                        classMatch = reClass.Match(scriptLines[i]);


                        if (ucIdMatch.Length > 0)
                        {
                            IEnumerable<XElement> qcsearchResult = qcTestSet.XPathSelectElements(String.Format("Entities/Entity//Field[@Name='user-template-30' and Value='{0}']/ancestor::Entity", ucIdMatch.Value));

                            if (qcsearchResult.Count() > 0)
                            {
                                qcTestCase = qcsearchResult.ElementAt(0);

                                testCaseInfo = new Dictionary<string, string>();
                                testCaseInfo.Add("path", scriptPath);
                                testCaseInfo.Add("ucId", ucIdMatch.Value);
                                testCaseInfo.Add("subarea", qcTestCase.XPathSelectElement("RelatedEntities//Field[@Name='user-template-09']/Value").Value); //Feature group from QC

                                string qcFeature, qcSubfeature;
                                qcSubfeature = qcTestCase.XPathSelectElement("RelatedEntities//Field[@Name='user-template-17']/Value").Value; // Subfeature from QC
                                if (qcSubfeature != "Not Assigned" && qcSubfeature != "")
                                {
                                    qcFeature = qcTestCase.XPathSelectElement("RelatedEntities//Field[@Name='user-template-24']/Value").Value + " - " + qcSubfeature;
                                }
                                else
                                {
                                    qcFeature = qcTestCase.XPathSelectElement("RelatedEntities//Field[@Name='user-template-24']/Value").Value; //Feature from QC
                                }

                                testCaseInfo.Add("feature", qcFeature);
                                testCaseInfo.Add("name", qcTestCase.XPathSelectElement("RelatedEntities//Field[@Name='name']/Value").Value);
                                testCaseInfo.Add("identifier", qcTestCase.XPathSelectElement("RelatedEntities//Field[@Name='user-template-30']/Value").Value);
                                testCaseInfo.Add("instance-id", qcTestCase.XPathSelectElement("Fields/Field[@Name='id']/Value").Value);
                                testCaseInfo.Add("test-id", qcTestCase.XPathSelectElement("RelatedEntities//Field[@Name='id']/Value").Value);
                            }
                        }
                        else if (methodMatch.Length > 0 && testCaseInfo != null)
                        {
                            testCaseInfo.Add("method", methodMatch.Value);
                            scriptsToTestSet.Add(testCaseInfo);
                            testCaseInfo = null;
                        }
                        else if (classMatch.Length > 0 && scriptsToTestSet.Count > 0)
                        {
                            foreach (Dictionary<string, string> tc in scriptsToTestSet)
                            {
                                tc.Add("class", classMatch.Value);
                                testCaseStack.Push(tc);
                            }
                            // Add found test cases to Marble test set then set scriptsToTestSet as null
                            scriptsToTestSet = null;

                        }

                    }
                }

            }); //parallel for each

            foreach (Dictionary<string, string> tc in testCaseStack.ToArray())
            {
                XElement testScriptElement = new XElement("testscript");
                testScriptElement.SetAttributeValue("directory", Path.GetDirectoryName(tc["path"]));
                testScriptElement.SetAttributeValue("file", Path.GetFileNameWithoutExtension(tc["path"]));
                testScriptElement.SetAttributeValue("class", tc["class"]);
                testScriptElement.SetAttributeValue("method", tc["method"]);

                XElement testCaseElement = new XElement("testcase");
                testCaseElement.SetAttributeValue("name", tc["name"]);
                testCaseElement.SetAttributeValue("feature", tc["feature"]);
                testCaseElement.SetAttributeValue("subarea", tc["subarea"]);
                testCaseElement.SetAttributeValue("ucid", tc["identifier"]);

                testCaseElement.SetAttributeValue("instance-id", tc["instance-id"]);
                testCaseElement.SetAttributeValue("test-id", tc["test-id"]);


                testCaseElement.Add(testScriptElement);
                convertedTestSet.Add(testCaseElement);
                testsInSet += 1;
            }
            if (testsInSet < 1)
                return null;
            else
                return convertedTestSet;
        }
        /// <summary>
        /// Sends results from Marble test set to QC
        /// </summary>
        /// <param name="testSetPath">Path and filename of Marble test set with results</param>
        /// <param name="username"></param>
        /// <param name="password"></param>
        /// <returns></returns>
        public bool SendResults(string testSetPath, string username, string password)
        {
            bool result = false;
            string domain, project, serverUrl, testCaseResult;

            XElement marbleTestSet = XElement.Load(testSetPath);

            if (marbleTestSet.Attribute("server-url") == null)
            {
                return result;
            }
            // Create list of identifiers in test set. HashSet makes values unique.
            var identifierList = new HashSet<string>((from testCase in marbleTestSet.Elements("testcase") select testCase.Attribute("ucid").Value).ToArray());
            if (identifierList.Count() < 1)
            {
                return result;
            }

            serverUrl = marbleTestSet.Attribute("server-url").Value;
            this.URL = serverUrl;
            Authenticate(username, password, serverUrl);

            domain = marbleTestSet.Attribute("domain").Value;
            project = marbleTestSet.Attribute("project").Value;

            foreach (string id in identifierList)
            {
                var resultList = (from testCase in marbleTestSet.Elements("testcase") where testCase.Attribute("ucid").Value == id && testCase.Element("testresult") != null select testCase.Element("testresult").Attribute("result").Value).ToArray<string>();
                if (resultList.Count() == 0)
                {
                    // Skip test case if it has no result
                    continue;
                }

                testCaseResult = getQCResult(resultList);

                if (CreateRun(id, marbleTestSet, testCaseResult))
                {
                    UpdateTestInstance(id, marbleTestSet, testCaseResult);
                    result = true;
                }
            }

            return result;
        }

        /// <summary>
        /// Creates new run to QC
        /// </summary>
        /// <param name="id">Identifier-value of test case</param>
        /// <param name="marbleTestSet">Marble test set</param>
        /// <param name="result">result of the test case</param>
        /// <returns>True if run was created succesfylly, otherwise false</returns>
        private bool CreateRun(string id, XElement marbleTestSet, string result)
        {

            string domain, project;
            HttpWebRequest request;
            HttpWebResponse response = null;

            XElement qcTestCaseRun, fieldsNode, fieldNode, valueNode, testCaseNode;

            domain = marbleTestSet.Attribute("domain").Value;
            project = marbleTestSet.Attribute("project").Value;

            // Other values than test result can be taken from first occurance of identifier
            testCaseNode = marbleTestSet.XPathSelectElement(String.Format("testcase[@ucid='{0}']", id));

            qcTestCaseRun = new XElement("Entity");
            qcTestCaseRun.SetAttributeValue("Type", "run");

            fieldsNode = new XElement("Fields");

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("PhysicalName", "RN_STATUS");
            fieldNode.SetAttributeValue("Name", "status");
            fieldNode.SetAttributeValue("Label", "Status");
            valueNode = new XElement("Value");
            valueNode.Value = result;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("PhysicalName", "RN_RUN_NAME");
            fieldNode.SetAttributeValue("Name", "name");
            fieldNode.SetAttributeValue("Label", "Run Name");
            valueNode = new XElement("Value");
            valueNode.Value = "MARBLE_RUN";
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("PhysicalName", "RN_TEST_ID");
            fieldNode.SetAttributeValue("Name", "test-id");
            fieldNode.SetAttributeValue("Label", "Test");
            valueNode = new XElement("Value");
            valueNode.Value = testCaseNode.Attribute("test-id").Value;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("PhysicalName", "RN_TESTCYCL_ID");
            fieldNode.SetAttributeValue("Name", "testcycl-id");
            fieldNode.SetAttributeValue("Label", "Test Instance");
            valueNode = new XElement("Value");
            valueNode.Value = testCaseNode.Attribute("instance-id").Value;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("PhysicalName", "RN_CYCLE_ID");
            fieldNode.SetAttributeValue("Name", "cycle-id");
            fieldNode.SetAttributeValue("Label", "Cycle ID");
            valueNode = new XElement("Value");
            valueNode.Value = marbleTestSet.Attribute("testSet-id").Value;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("PhysicalName", "RN_TESTER_NAME");
            fieldNode.SetAttributeValue("Name", "owner");
            fieldNode.SetAttributeValue("Label", "Tester");
            valueNode = new XElement("Value");
            valueNode.Value = testCaseNode.Element("testresult").Attribute("author").Value;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "subtype-id");
            valueNode = new XElement("Value");
            valueNode.Value = "hp.qc.run.MANUAL";
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            string[] dateTime = testCaseNode.Element("testresult").Attribute("time").Value.Split();
            string[] newDate = new string[3];
            string[] newTime = new string[3];

            newDate[0] = dateTime[0].Split('/')[2];
            newDate[1] = dateTime[0].Split('/')[0];
            newDate[2] = dateTime[0].Split('/')[1];

            newTime = dateTime[1].Split(':');
            if (dateTime[2] == "PM")
            {
                if (newTime[0] == "12")
                {
                    newTime[0] = "0";
                }
                else
                {
                    newTime[0] = Convert.ToString(Convert.ToInt16(newTime[0]) + 12);
                }
            }

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "execution-time");
            valueNode = new XElement("Value");
            valueNode.Value = String.Join(":", newTime);
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "execution-date");
            valueNode = new XElement("Value");
            valueNode.Value = String.Join("-", newDate);
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "user-template-03");
            valueNode = new XElement("Value");
            valueNode.Value = testCaseNode.Element("testresult").Attribute("product").Value;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "user-template-02");
            valueNode = new XElement("Value");
            valueNode.Value = "SW Update";
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);


            qcTestCaseRun.Add(fieldsNode);

            // Send
            request = GetRequest(String.Format("rest/domains/{0}/projects/{1}/runs", domain, project), "POST");

            byte[] byteArray = Encoding.UTF8.GetBytes(qcTestCaseRun.ToString());
            Stream dataStream = request.GetRequestStream();
            // Write the data to the request stream.
            dataStream.Write(byteArray, 0, byteArray.Length);
            // Close the Stream object.
            dataStream.Close();
            dataStream.Dispose();

            try
            {
                response = (HttpWebResponse)request.GetResponse();
                if (qcSessionCookie == null)
                {
                    qcSessionCookie = response.Cookies["QCSession"];
                }
            }
            catch (WebException e)
            {

                HttpWebResponse errorResp = e.Response as HttpWebResponse;
                if (errorResp.StatusCode == HttpStatusCode.Created)
                {
                    // This code might not be reached
                    return true;
                }
                else
                {
                    //throw e;
                    return false;
                }
            }
            finally
            {
                if (response != null)
                {
                    response.Close();
                    response = null;
                }
            }

            return true;
        }

        /// <summary>
        /// Updates test instance status in QC
        /// </summary>
        /// <param name="id">Identifier value of test instance</param>
        /// <param name="marbleTestSet">Marble test set</param>
        /// <returns>True if test instance is updated succesfully, otherwise false</returns>
        private bool UpdateTestInstance(string id, XElement marbleTestSet, string result)
        {

            HttpWebRequest request;
            HttpWebResponse response = null;
            XElement qcTestCaseInstance, fieldsNode, fieldNode, valueNode, testCaseNode;
            string domain = marbleTestSet.Attribute("domain").Value;
            string project = marbleTestSet.Attribute("project").Value;

            // Other values than test result can be taken from first occurance of identifier
            testCaseNode = marbleTestSet.XPathSelectElement(String.Format("testcase[@ucid='{0}']", id));

            qcTestCaseInstance = new XElement("Entity");
            qcTestCaseInstance.SetAttributeValue("Type", "test-instance");

            fieldsNode = new XElement("Fields");

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "test-id");
            valueNode = new XElement("Value");
            valueNode.Value = testCaseNode.Attribute("test-id").Value;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "test-order");
            valueNode = new XElement("Value");
            valueNode.Value = "1";
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "cycle-id");
            valueNode = new XElement("Value");
            valueNode.Value = marbleTestSet.Attribute("testSet-id").Value;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "status");
            valueNode = new XElement("Value");
            valueNode.Value = result;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);


            qcTestCaseInstance.Add(fieldsNode);


            // Send
            request = GetRequest(String.Format("rest/domains/{0}/projects/{1}/test-instances/{2}", domain, project, testCaseNode.Attribute("instance-id").Value), "PUT");

            byte[] byteArray = Encoding.UTF8.GetBytes(qcTestCaseInstance.ToString());
            Stream dataStream = request.GetRequestStream();
            // Write the data to the request stream.
            dataStream.Write(byteArray, 0, byteArray.Length);
            // Close the Stream object.
            dataStream.Close();
            dataStream.Dispose();

            try
            {
                response = (HttpWebResponse)request.GetResponse();
                if (qcSessionCookie == null)
                {
                    qcSessionCookie = response.Cookies["QCSession"];
                }
            }
            catch (WebException e)
            {

                HttpWebResponse errorResp = e.Response as HttpWebResponse;
                if (errorResp.StatusCode == HttpStatusCode.Created)
                {
                    // This code might not be reached
                    return true;
                }
                else
                {
                    return false;
                }
            }
            finally
            {
                if (response != null)
                {
                    response.Close();
                    response = null;
                }
            }


            return true;
        }

        /// <summary>
        /// Resolves test result it test case has multiple results
        /// </summary>
        /// <param name="marbleResult">list of results in Marble run</param>
        /// <returns>Result of test case for QC</returns>
        private string getQCResult(string[] marbleResult)
        {

            string result = "";

            string[] resultPriority = {
                            "Failed",
                            "Failed in tearDown",
                            "Failed in setUp",
                            "Remote failed",
                            "No Run",
                            "No Result",
                            "Passed",
                            "N/A",
                            "Training run"
                                      };
            Dictionary<string, string> qcMarbleResultMapDict = new Dictionary<string, string>();
            qcMarbleResultMapDict.Add("Failed", "Failed");
            qcMarbleResultMapDict.Add("Passed", "Passed");
            qcMarbleResultMapDict.Add("N/A", "N/A");
            qcMarbleResultMapDict.Add("No Result", "No Result");
            qcMarbleResultMapDict.Add("No Run", "Not Completed");
            qcMarbleResultMapDict.Add("Failed in tearDown", "Failed");
            qcMarbleResultMapDict.Add("Failed in setUp", "Failed");
            qcMarbleResultMapDict.Add("Remote failed", "Failed");
            qcMarbleResultMapDict.Add("Training run", "N/A");

            if (marbleResult.Count() > 1)
            {
                foreach (string tempResult in resultPriority)
                {
                    if (marbleResult.Contains(tempResult))
                    {
                        result = tempResult;
                        break;
                    }
                }
            }
            else
            {
                result = marbleResult[0];
            }


            return qcMarbleResultMapDict[result];
        }

        /// <summary>
        /// This method is for testing purposes
        /// </summary>
        /// <param name="testString"></param>
        /// <returns></returns>
        public string TestAPI(string testString)
        {
            HttpWebRequest request;
            HttpWebResponse response;
            XDocument TESTqcTestSet;

            request = GetRequest(testString, "GET");
            try
            {
                response = (HttpWebResponse)request.GetResponse();
                using (StreamReader reader = new StreamReader(response.GetResponseStream()) as StreamReader)
                {
                    TESTqcTestSet = XDocument.Load(reader);
                }
            }
            catch (WebException e)
            {
                return "";
            }
            return TESTqcTestSet.ToString();

        }



    }
}
