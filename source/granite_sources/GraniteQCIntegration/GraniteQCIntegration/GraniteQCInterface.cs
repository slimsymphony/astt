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

namespace Nokia.Granite.QC
{
    public class GraniteQCInterface : IGraniteQCInterface
    {
        private Cookie lwssoCookie = null;
        private Cookie qcSessionCookie = null;

        private string URL = "https://qc11qa.nokia.com/qcbin/";
        private string username, password;

        ~GraniteQCInterface()
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
        public string Authenticate(string username="", string password="", string url="")
        {
            string result="OK";
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

            request = GetRequest(String.Format("rest/domains/{0}/projects/{1}/test-set-folders?query={{parent-id[{2}]}}&fields=name,id", domain, project,nodeId), "GET");



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
        /// Downloads test-set which matches testSetID. Downloaded test set is converted to be compatible with Granite
        /// </summary>
        /// <param name="domain">Domain of test-set.</param>
        /// <param name="project">Project of test-set.</param>
        /// <param name="testSetID">Id of the test-set which should be downloaded.</param>
        /// <param name="graniteScriptPath">Path to scripts which should be used to construct the test set.</param>
        public XElement GetTestSet(string domain, string project, string testSetID, string graniteScriptPath)
        {
            HttpWebRequest request;
            HttpWebResponse response;
            XDocument qcTestSet = null;
            XElement graniteTestSet = null;

            Authenticate();

            request = GetRequest(String.Format("rest/domains/{0}/projects/{1}/test-instances?query={{test-set.id[{2}]}}&" +
                "fields=test.user-template-13,test.name,test.user-template-24,test.user-template-09,test.user-template-17,test.user-template-30,id,test-instance,test-order,cycle-id&page-size=max", 
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
            graniteTestSet = convertToGraniteTestSet(qcTestSet, graniteScriptPath);
            if (graniteTestSet == null)
                return null;

            // Add url, domain, project and testSetId to graniteTestSet
            graniteTestSet.SetAttributeValue("server-url",URL);
            graniteTestSet.SetAttributeValue("domain", domain);
            graniteTestSet.SetAttributeValue("project", project);
            graniteTestSet.SetAttributeValue("testSet-id", testSetID);


            return graniteTestSet;
        }


        /// <summary>
        /// Logs out from QC server
        /// </summary>
        public void LogOut()
        {
            HttpWebRequest request;
            HttpWebResponse response;

            request = GetRequest("authentication-point/logout","GET");
            response = (HttpWebResponse)request.GetResponse();
            response.Close();
            lwssoCookie = null;
            qcSessionCookie = null;

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

        private XElement getTestsFromXMLFiles(XDocument qcTestSet, string xmlPath)
        {
            XElement convertedTestSet = null;
            convertedTestSet = new XElement("testset");
            Dictionary<string, string>[] testCaseDict;

            ConcurrentStack<string> testScriptFiles = new ConcurrentStack<string>();
            ConcurrentStack<string> testSetFiles = new ConcurrentStack<string>();

            //XElement testXml = XElement.Load(xmlPath);

            Parallel.ForEach(Directory.GetFiles(Path.GetDirectoryName(xmlPath), Path.GetFileName(xmlPath)), testXmlPath =>
            {
                XElement testXml = XElement.Load(testXmlPath);
                //string[] testScripts;
                //string[] testScripts = (from testCase in testXml.Elements("tests").Elements("test") where testCase.Attribute("path").Value.EndsWith(".py") select testCase.Attribute("path").Value).ToArray();
                //string[] testSets = (from testCase in testXml.Elements("tests").Elements("test") where testCase.Attribute("path").Value.EndsWith(".testest") select testCase.Attribute("path").Value).ToArray();
                foreach (XElement testNode in testXml.XPathSelectElements("//test"))
                {
                    if (testNode.Attribute("path").Value.EndsWith(".py"))
                        testScriptFiles.Push(testNode.Attribute("path").Value);
                    else if (testNode.Attribute("path").Value.EndsWith(".testset"))
                        testSetFiles.Push(testNode.Attribute("path").Value);
                }

                //string[] testScripts = (from testCase in testXml.Elements("tests").Elements("test") where testCase.Attribute("path").Value.EndsWith(".py") select testCase.Attribute("path").Value).ToArray();
                //string[] testSets = (from testCase in testXml.Elements("tests").Elements("test") where testCase.Attribute("path").Value.EndsWith(".testest") select testCase.Attribute("path").Value).ToArray();

                //if (testScripts.Length > 0)
                //{
                //    testScriptFiles.PushRange(testScripts);
                //}

                //if (testSets.Length > 0)
                //{
                //    testSetFiles.PushRange(testSets);
                //}
                //foreach (XElement scriptNode in testXml.XPathSelectElements("//test"))
            });

            //Add test cases from script files to test case dictionary which is later converted to Granite test set
            testCaseDict = getQCCasesFromScriptFiles(qcTestSet, testScriptFiles.ToArray());

            // Test set support not implemented yet!!!
            //// Collect all script files and test cases used in test sets
            //Parallel.ForEach(testSetFiles.ToArray(), testSetPath =>
            //{
            //    XElement testSetXml = XElement.Load(testSetPath);
                
            //    string[] list = (from testCase in testSetXml.Elements("testcase") select Path.Combine(testCase.Element("testscript").Attribute("directory").Value, testCase.Element("testscript").Attribute("file").Value)).ToArray();
            //    var scriptFilesInTestSetList = new HashSet<string>(list);
            //});

            //// Get all test cases with ucid from test script file found from test set. Then take only test cases in test set.
            //Parallel.ForEach(testSetFiles.ToArray(), testSetPath =>
            //{
            //    XElement testSetXml = XElement.Load(testSetPath);

            //    testScriptFiles.PushRange((from testCase in testSetXml.Elements("tests").Elements("test") where testCase.Attribute("path").Value.EndsWith(".py") select testCase.Attribute("path").Value).ToArray());
            //    //foreach (XElement scriptNode in testXml.XPathSelectElements("//test"))
            //});

            return generateGraniteTestSet(testCaseDict);

        }

        /// <summary>
        /// Method converts a test set downloaded from QC to Granite test set format
        /// </summary>
        /// <param name="qcTestSet">Test set downloaded from QC</param>
        /// <param name="graniteScriptPath">Path to root folder of scripts which are going to be used in Granite test set</param>
        /// <returns>Test set in Granite format</returns>
        private XElement convertToGraniteTestSet(XDocument qcTestSet, string graniteScriptPath)
        {
            //string[] testScripts = null;
            Dictionary<string, string>[] testCaseDict;

            if (graniteScriptPath.EndsWith(".xml"))
            {
                return getTestsFromXMLFiles(qcTestSet, graniteScriptPath);
            }
            else
            {
                if (!Directory.Exists(graniteScriptPath))
                {
                    throw new DirectoryNotFoundException(String.Format("Directory {0} not found", graniteScriptPath));
                }

                //return Directory.GetFiles(graniteScriptPath, "*.py", SearchOption.AllDirectories);
                testCaseDict = getQCCasesFromScriptFiles(qcTestSet, Directory.GetFiles(graniteScriptPath, "*.py", SearchOption.AllDirectories));
                return generateGraniteTestSet(testCaseDict);
            }

        }

        /// <summary>
        /// Collect test cases from testScripts list which have ucId found from qcTestSet
        /// </summary>
        /// <param name="qcTestSet"></param>
        /// <param name="testScripts"></param>
        /// <returns></returns>
        private Dictionary<string, string>[] getQCCasesFromScriptFiles(XDocument qcTestSet, string[] testScripts)
        {
            // Loop through all test script files to find test cases with ucId-attribute.
            // When test case with ucId is found check if matching ucId is found from qcTestSet.
            // If ucId is found from qcTestSet also add new node to convertedTestSet

            Regex reTcId = new Regex(@"(?<=@tcId)( [A-Za-z0-9]*)+", RegexOptions.Compiled);
            Regex reUcId = new Regex(@"(?<=@ucId)( [A-Za-z0-9]*)+", RegexOptions.Compiled);
            Regex reAuId = new Regex(@"(?<=@auId )([A-Za-z0-9]*)", RegexOptions.Compiled);
            Regex reMethod = new Regex(@"(?<=def )([A-Za-z0-9]*)", RegexOptions.Compiled);
            Regex reClass = new Regex(@"(?<=class )([A-Za-z0-9]*)", RegexOptions.Compiled);
            Regex reSubarea = new Regex("(?<=subarea.+\\\")(.+)(\\\")", RegexOptions.Compiled);
            Regex reFeature = new Regex("(?<=feature.+\\\")(.+)(\\\")", RegexOptions.Compiled);

            ConcurrentStack<Dictionary<string, string>> testCaseStack = new ConcurrentStack<Dictionary<string, string>>();
            
            Parallel.ForEach(testScripts, scriptPath =>
            {
                MatchCollection matchingLines = null;
                Match methodMatch, classMatch, ucIdMatch, auIdMatch, tcIdMatch, subareaMatch, featureMatch;

                int ucIdLinesFound = 0;

                string[] scriptLines = File.ReadAllLines(scriptPath);
                string scriptText = File.ReadAllText(scriptPath);
                matchingLines = reUcId.Matches(scriptText);
                ucIdLinesFound = matchingLines.Count;
                XElement qcTestCase = null;


                if (ucIdLinesFound > 0)
                {
                    List<Dictionary<string, string>> scriptsToTestSet = new List<Dictionary<string, string>>();
                    Dictionary<string,string> testCaseInfo = null;

                    string currentTcId = null; 
                    string currentAuId = null;
                    string feature = null;
                    string subarea = null;

                    for (int i = scriptLines.Length - 1; i >= 0 && ucIdLinesFound>0; i--)
                    {
                        ucIdMatch = reUcId.Match(scriptLines[i]);
                        auIdMatch = reAuId.Match(scriptLines[i]);
                        tcIdMatch = reTcId.Match(scriptLines[i]);
                        methodMatch = reMethod.Match(scriptLines[i]);
                        classMatch = reClass.Match(scriptLines[i]);
                        featureMatch = reFeature.Match(scriptLines[i]);
                        subareaMatch = reSubarea.Match(scriptLines[i]);

                        
                        if (ucIdMatch.Length > 0)
                        {
                            string qcTestCaseSearchString = "Entities/Entity/RelatedEntities/Relation/Entity/Fields/Field[@Name='user-template-30' and ({0})]/ancestor::Entity[last()]";
                            List<string> searchStrings = new List<string>();
                            foreach (string ucId in ucIdMatch.Value.Split())
                            {
                                if (ucId.Length>0)
                                {
                                    searchStrings.Add(String.Format("Value='{0}'", ucId));
                                }
                            }

                            qcTestCaseSearchString = String.Format(qcTestCaseSearchString, String.Join(" or ",searchStrings));
                            IEnumerable<XElement> qcsearchResult = qcTestSet.XPathSelectElements(qcTestCaseSearchString);
                            
                            if (qcsearchResult.Count() > 0)
                            {
                                List<string> instanceIds = new List<string>();
                                List<string> testIds = new List<string>();
                                List<string> ucIds = new List<string>();
                                foreach (XElement qcTc in qcsearchResult)
                                {
                                    ucIds.Add(qcTc.XPathSelectElement("RelatedEntities//Field[@Name='user-template-30']/Value").Value);
                                    testIds.Add(qcTc.XPathSelectElement("RelatedEntities//Field[@Name='id']/Value").Value);
                                    instanceIds.Add(qcTc.XPathSelectElement("Fields/Field[@Name='id']/Value").Value);
                                }


                                qcTestCase = qcsearchResult.ElementAt(0);

                                testCaseInfo = new Dictionary<string, string>();
                                testCaseInfo.Add("path", scriptPath);
                                testCaseInfo.Add("ucId", "|" + String.Join("|", ucIds) + "|");
                                testCaseInfo.Add("instance-id", "|" + String.Join("|", instanceIds) + "|");
                                testCaseInfo.Add("test-id", "|" + String.Join("|", testIds) + "|");
                                if (currentTcId != null)
                                {
                                    testCaseInfo.Add("name", currentTcId);
                                    currentTcId = null;
                                }
                                if (currentAuId != null)
                                {
                                    testCaseInfo.Add("auId", currentAuId);
                                    currentAuId = null;
                                }
                            }
                        }
                        else if (auIdMatch.Length>0)
                        {
                            if (testCaseInfo!=null)
                            {
                                testCaseInfo.Add("auId", auIdMatch.Value.Trim());
                            }
                            else
                            {
                                currentAuId = auIdMatch.Value.Trim();
                            }

                        }
                        else if (tcIdMatch.Length>0)
                        {
                            if (testCaseInfo!=null)
                            {
                                testCaseInfo.Add("tcId", tcIdMatch.Value.Trim());
                            }
                            else
                            {
                                currentTcId = tcIdMatch.Value.Trim();
                            }

                        }

                        else if (subareaMatch.Length > 0)
                        {
                            subarea = subareaMatch.Groups[1].Value;
                        }

                        else if (featureMatch.Length > 0)
                        {
                            feature = featureMatch.Groups[1].Value;
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
                                if (feature != null)
                                {
                                    tc.Add("feature", feature);
                                }
                                else
                                {
                                    tc.Add("feature", "No Feature");
                                }

                                if (subarea != null)
                                {
                                    tc.Add("subarea", subarea);
                                }
                                else
                                {
                                    tc.Add("subarea", "No Subarea");
                                }


                                testCaseStack.Push(tc);
                            }
                            // Add found test cases to Granite test set then set scriptsToTestSet as null
                            scriptsToTestSet = null;

                        }
                        
                    }
                }

            }); //parallel for each

            return testCaseStack.ToArray();
        }

        /// <summary>
        /// Generate Granite test set xml from list containing dictionaries
        /// </summary>
        /// <param name="testCaseDict"></param>
        /// <returns></returns>
        private XElement generateGraniteTestSet(Dictionary<string, string>[] testCaseDict)
        {
            XElement convertedTestSet = null;
            int testsInSet = 0;
            convertedTestSet = new XElement("testset");

            foreach (Dictionary<string, string> tc in testCaseDict)
            {
                XElement testScriptElement = new XElement("testscript");
                testScriptElement.SetAttributeValue("directory",Path.GetDirectoryName(tc["path"]));
                testScriptElement.SetAttributeValue("file", Path.GetFileNameWithoutExtension(tc["path"]));
                testScriptElement.SetAttributeValue("class", tc["class"]);
                testScriptElement.SetAttributeValue("method", tc["method"]);

                XElement testCaseElement = new XElement("testcase");
                testCaseElement.SetAttributeValue("name", tc["name"]);
                testCaseElement.SetAttributeValue("feature", tc["feature"]);
                testCaseElement.SetAttributeValue("subarea", tc["subarea"]);
                testCaseElement.SetAttributeValue("ucid", tc["ucId"]);

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
        /// Sends results from Granite test set to QC
        /// </summary>
        /// <param name="testSetPath">Path and filename of Granite test set with results</param>
        /// <param name="username"></param>
        /// <param name="password"></param>
        /// <returns></returns>
        public bool SendResults(string testSetPath, string username, string password)
        {
            bool result = false;
            string domain, project, serverUrl, testCaseResult;

            XElement graniteTestSet = XElement.Load(testSetPath);

            if (graniteTestSet.Attribute("server-url")==null)
            {
                return result;
            }
            // Create list of identifiers in test set. HashSet makes values unique.
            var identifierList = (from testCase in graniteTestSet.Elements("testcase") select testCase.Attribute("ucid").Value).ToArray();

            List<string> allIdentifiers = new List<string>();

            foreach (string id in identifierList)
            {
                foreach (string i in id.Split('|'))
                {
                    if (i.Length > 0)
                    {
                        allIdentifiers.Add(i);
                    }
                }
            }

            var uniqueIdentifierList = new HashSet<string>(allIdentifiers.ToArray());
            if (uniqueIdentifierList.Count()<1)
            {
                return result;
            }

            serverUrl = graniteTestSet.Attribute("server-url").Value;
            this.URL = serverUrl;
            Authenticate(username, password, serverUrl);

            domain = graniteTestSet.Attribute("domain").Value;
            project = graniteTestSet.Attribute("project").Value;
            DateTime runTimeStamp = DateTime.Now;
            foreach (string id in uniqueIdentifierList)
            {
                var resultList = (from testCase in graniteTestSet.Elements("testcase") where testCase.Attribute("ucid").Value.Contains(id) && testCase.Element("testresult") !=null select testCase.Element("testresult").Attribute("result").Value).ToArray<string>();
                if (resultList.Count() == 0)
                {
                    // Skip test case if it has no result
                    continue;
                }

                testCaseResult = getQCResult(resultList);

                if (CreateRun(id, graniteTestSet, testCaseResult, runTimeStamp))
                {
                    UpdateTestInstance(id, graniteTestSet, testCaseResult, runTimeStamp);
                    result = true;
                }
            }

            return result;
        }

        /// <summary>
        /// Creates new run to QC
        /// </summary>
        /// <param name="id">Identifier-value of test case</param>
        /// <param name="graniteTestSet">Granite test set</param>
        /// <param name="result">result of the test case</param>
        /// <returns>True if run was created succesfylly, otherwise false</returns>
        private bool CreateRun(string id, XElement graniteTestSet, string result, DateTime timestamp)
        {

            string domain, project;
            HttpWebRequest request;
            HttpWebResponse response = null;

            XElement qcTestCaseRun, fieldsNode, fieldNode, valueNode, testCaseNode;

            domain = graniteTestSet.Attribute("domain").Value;
            project = graniteTestSet.Attribute("project").Value;

            // Other values than test result can be taken from first occurance of identifier
            testCaseNode = graniteTestSet.XPathSelectElement(String.Format("testcase[contains(@ucid,'{0}')]", "|" + id + "|"));

            var ucIdList = testCaseNode.Attribute("ucid").Value.Trim('|').Split('|').ToArray();
            var instanceIdList = testCaseNode.Attribute("instance-id").Value.Trim('|').Split('|').ToArray();
            var testIdList = testCaseNode.Attribute("test-id").Value.Trim('|').Split('|').ToArray();

            int idIndex = Array.FindIndex(ucIdList, x => x == id);

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
            valueNode.Value = "GRANITE_RUN_" + String.Format(@"{0}-{1}_{2}-{3}-{4}", timestamp.Month, timestamp.Day, timestamp.Hour, timestamp.Minute, timestamp.Second);
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("PhysicalName", "RN_TEST_ID");
            fieldNode.SetAttributeValue("Name", "test-id");
            fieldNode.SetAttributeValue("Label", "Test");
            valueNode = new XElement("Value");
            valueNode.Value = testIdList[idIndex];
            //valueNode.Value = testCaseNode.Attribute("test-id").Value;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("PhysicalName", "RN_TESTCYCL_ID");
            fieldNode.SetAttributeValue("Name", "testcycl-id");
            fieldNode.SetAttributeValue("Label", "Test Instance");
            valueNode = new XElement("Value");
            valueNode.Value = instanceIdList[idIndex];
            //valueNode.Value = testCaseNode.Attribute("instance-id").Value;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("PhysicalName", "RN_CYCLE_ID");
            fieldNode.SetAttributeValue("Name", "cycle-id");
            fieldNode.SetAttributeValue("Label", "Cycle ID");
            valueNode = new XElement("Value");
            valueNode.Value = graniteTestSet.Attribute("testSet-id").Value;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("PhysicalName", "RN_TESTER_NAME");
            fieldNode.SetAttributeValue("Name", "owner");
            fieldNode.SetAttributeValue("Label", "Tester");
            valueNode = new XElement("Value");
            valueNode.Value = this.username;
            //valueNode.Value = testCaseNode.Element("testresult").Attribute("author").Value;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "subtype-id");
            valueNode = new XElement("Value");
            valueNode.Value = "hp.qc.run.MANUAL";
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            //string[] dateTime = testCaseNode.Element("testresult").Attribute("time").Value.Split();
            //string[] newDate = new string[3];
            //string[] newTime = new string[3];

            //newDate[0] = dateTime[0].Split('/')[2];
            //newDate[1] = dateTime[0].Split('/')[0];
            //newDate[2] = dateTime[0].Split('/')[1];

            //newTime = dateTime[1].Split(':');
            //if (dateTime[2] == "PM")
            //{
            //    if (newTime[0] == "12")
            //    {
            //        newTime[0] = "0";
            //    }
            //    else
            //    {
            //        newTime[0] = Convert.ToString(Convert.ToInt16(newTime[0]) + 12);
            //    }
            //}

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "execution-time");
            valueNode = new XElement("Value");
            valueNode.Value = timestamp.Hour + ":" + timestamp.Minute + ":" + timestamp.Second;
            //valueNode.Value = String.Join(":", newTime);
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "execution-date");
            valueNode = new XElement("Value");
            valueNode.Value = timestamp.Year + "-" + timestamp.Month + "-" + timestamp.Day;
            //valueNode.Value = String.Join("-", newDate);
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
                    string error;
                    using (StreamReader reader = new StreamReader(errorResp.GetResponseStream()) as StreamReader)
                    {
                        error = XDocument.Load(reader).Root.ToString();
                    }

                    throw new WebException(error, e);
                    //return false;
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
        /// <param name="graniteTestSet">Granite test set</param>
        /// <returns>True if test instance is updated succesfully, otherwise false</returns>
        private bool UpdateTestInstance(string id, XElement graniteTestSet, string result, DateTime timestamp)
        {

            HttpWebRequest request;
            HttpWebResponse response = null;
            XElement qcTestCaseInstance, fieldsNode, fieldNode, valueNode, testCaseNode;
            string domain = graniteTestSet.Attribute("domain").Value;
            string project = graniteTestSet.Attribute("project").Value;

            // Other values than test result can be taken from first occurance of identifier
            testCaseNode = graniteTestSet.XPathSelectElement(String.Format("testcase[contains(@ucid,'{0}')]", "|" + id + "|"));

            var ucIdList = testCaseNode.Attribute("ucid").Value.Trim('|').Split('|').ToArray();
            var testIdList = testCaseNode.Attribute("test-id").Value.Trim('|').Split('|').ToArray();
            var instanceIdList = testCaseNode.Attribute("instance-id").Value.Trim('|').Split('|').ToArray();

            int idIndex = Array.FindIndex(ucIdList, x => x == id);

            qcTestCaseInstance = new XElement("Entity");
            qcTestCaseInstance.SetAttributeValue("Type", "test-instance");

            fieldsNode = new XElement("Fields");

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "test-id");
            valueNode = new XElement("Value");
            valueNode.Value = testIdList[idIndex];
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
            valueNode.Value = graniteTestSet.Attribute("testSet-id").Value;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "status");
            valueNode = new XElement("Value");
            valueNode.Value = result;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            //// Get latest test-order value from test-instance
            //int testOrder = 0;

            //// Send
            //request = GetRequest(String.Format("rest/domains/{0}/projects/{1}/test-instances/{2}", domain, project, instanceIdList[idIndex]), "GET");

            //try
            //{
            //    response = (HttpWebResponse)request.GetResponse();
            //    if (qcSessionCookie == null)
            //    {
            //        qcSessionCookie = response.Cookies["QCSession"];
            //    }

            //    XElement respXml = null;
            //    using (StreamReader reader = new StreamReader(response.GetResponseStream()) as StreamReader)
            //    {
            //        respXml = XDocument.Load(reader).Root;
            //    }
            //    response.Close();
            //    testOrder = Convert.ToInt32(respXml.XPathSelectElement("//Field[@Name='testcycle-ver-stamp']/Value").Value);
            //    //testSets.InnerXml = testSets.SelectSingleNode("Entities").InnerXml;            
            //}
            //catch (WebException e)
            //{

            //    HttpWebResponse errorResp = e.Response as HttpWebResponse;
            //    if (errorResp.StatusCode == HttpStatusCode.Created)
            //    {
            //        return true;
            //    }
            //    else
            //    {
            //        return false;
            //    }
            //}
            //finally
            //{
            //    if (response != null)
            //    {
            //        response.Close();
            //        response = null;
            //    }
            //}

            // test-order END

            //fieldNode = new XElement("Field");
            //fieldNode.SetAttributeValue("Name", "testcycle-ver-stamp");
            //valueNode = new XElement("Value");
            //valueNode.Value = Convert.ToString(testOrder + 1);
            //fieldNode.Add(valueNode);
            //fieldsNode.Add(fieldNode);


            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "exec-time");
            valueNode = new XElement("Value");
            valueNode.Value = timestamp.Hour + ":" + timestamp.Minute + ":" + timestamp.Second;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);

            fieldNode = new XElement("Field");
            fieldNode.SetAttributeValue("Name", "exec-date");
            valueNode = new XElement("Value");
            valueNode.Value = timestamp.Year + "-" + timestamp.Month + "-" + timestamp.Day;
            fieldNode.Add(valueNode);
            fieldsNode.Add(fieldNode);


            qcTestCaseInstance.Add(fieldsNode);


            // Send
            request = GetRequest(String.Format("rest/domains/{0}/projects/{1}/test-instances/{2}", domain, project, instanceIdList[idIndex]), "PUT");

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
        /// <param name="graniteResult">list of results in Granite run</param>
        /// <returns>Result of test case for QC</returns>
        private string getQCResult(string[] graniteResult)
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
            Dictionary<string, string> qcGraniteResultMapDict = new Dictionary<string, string>();
            qcGraniteResultMapDict.Add("Failed", "Failed");
            qcGraniteResultMapDict.Add("Passed", "Passed");
            qcGraniteResultMapDict.Add("N/A", "N/A");
            qcGraniteResultMapDict.Add("No Result", "No Result");
            qcGraniteResultMapDict.Add("No Run", "Not Completed");
            qcGraniteResultMapDict.Add("Failed in tearDown", "Failed");
            qcGraniteResultMapDict.Add("Failed in setUp", "Failed");
            qcGraniteResultMapDict.Add("Remote failed", "Failed");
            qcGraniteResultMapDict.Add("Training run", "N/A");

            if (graniteResult.Count() > 1)
            {
                foreach (string tempResult in resultPriority)
                {
                    if (graniteResult.Contains(tempResult))
                    {
                        result = tempResult;
                        break;
                    }
                }
            }
            else
            {
                result = graniteResult[0];
            }


            return qcGraniteResultMapDict[result];
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
