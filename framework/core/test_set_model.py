# -*- coding: ascii -*-
# ============================================================================
#
#
# %full_filespec:   test_set_model.py
#                   ----------------------------------------------------------
#                   Granite Python Module
#
#
# Copyright (c)     Nokia. All rights reserved.
#
# ----------------------------------------------------------------------------
"""Test set model."""

# ============================================================================
# Module Setup

import os, shutil, time, errno

from core.settings.settings_data import test_set_template_name
from utils.file_utils import filterString, \
                             filterValidFilename

from utils.nodeutils import NodeUtils

# result variables which are used in GUI
FAILED = 'Failed'
PASSED = 'Passed'
NA = 'N/A'
NO_RESULT = 'No Result'
NO_RUN = 'No Run'
NOT_PASSED = 'Not passed'
FAILED_IN_TD = 'Failed in tearDown'
FAILED_IN_SETUP = 'Failed in setUp'
REMOTE_FAILED = 'Remote failed'
TRAINING_RUN = 'Training run'

P1 = 'P1'
P2 = 'P2'
P3 = 'P3'
P4 = 'P4'
P5 = 'P5'
# ============================================================================
class TestSetModelException(Exception):
    """Exception class for test set model exceptions."""
    def __init__(self, errorString):
        Exception.__init__(self)
        self._errorString = errorString

    def __str__(self):
        return '%s' % self._errorString

class OldTestSetVersionException(TestSetModelException):
    """This exception is raised if version number of settings file to be
    loaded is older that used settings model uses."""
    pass

# ============================================================================
class TestSetModel(object):
    """Model class for handling testset xml document."""
    TEST_SET_XML_VERSION = '8'
    # FIXME: version converter must be done
    def __init__(self):
        self._testSetDocument = None
        self._testSetFileName = None
        self._treeIdDict = {}
        self._testSetStatistics = {}
        self._initialize()

    def _initialize(self):
        """Initializes variables.

            Needed because the document can be loaded several times.
        """
        self._testSetDocument = None
        self._testSetFileName = None
        self._initializeTestSetStatistics()
        self._treeIdDict = {}

    def _selectTestCaseByPath(self, path):
        """Select test case nodes from test set based on path

        Parameters

            path : string : name of TestSetNodeBase nodes

        Returns

            TestCase node or None.
        """
        # FIXME: Change path handling from string to list
        pathL = path.split('/')
        assert len(pathL) >= 1,'Invalid path "%s"' % path

        # build xpath expression in 3 steps
        xpath = '/testset/'                                 # testset

        for hierarchy in pathL[:-1]:                       # hierarchy
            xpath += 'hierarchy[@name="%s"]/' % hierarchy
        xpath += 'testcase[@name="%s"]' % pathL[-1]         # testcase

        domObject = self._testSetDocument.find(xpath)
        if domObject:
            return TestCaseNode(domObject, self)

        return None

    def _selectTestCaseByNameAndUcid(self, name,ucid):
        """Select test case nodes from test set based on use case id
           and possible description part.

        Parameters

            name : string : name of TestSetNodeBase nodes
            ucid : string : use case id of TestSetNodeBase nodes

        Returns

            TestCase node or None.
        """

        xpath = '//testcase[@ucid = "%s"]' % ucid
        domObject = None
        descriptionIndex = name.find('*')
        if descriptionIndex > -1:
            tcDescription = name[descriptionIndex:]
            domObjectList = self._testSetDocument.findall(xpath)
            for node in domObjectList:
                if tcDescription in node['name']:
                    domObject = node
                    break

        else:
            domObject = self._testSetDocument.find(xpath)

        if domObject:
            return TestCaseNode(domObject, self)

        return None

    def _getHierarchyDict(self):
        """Returns existing hierarchy nodes

            Keys of result dictionary are path strings and
            values are XMLDOMnode instances.

        """
        hierarchyDOMNodes = self.getRootNode().\
                            getDomInstance().findall('//hierarchy')

        parentNodesInModel = {}

        for domNode in hierarchyDOMNodes:
            parentNodesInModel[TestSetNodeBase(\
                               domNode, self).getPath()] = domNode

        return parentNodesInModel

    def _filterTestCaseNodes(self, nodeList):
        """Filters out other than test case nodes

        Parameters
            nodeList        python list of TestSetNodeBase nodes to be filtered

        Returns python list python list of TestCase nodes
        """
        return [x for x in nodeList if type(x) in [TestCaseNode]]

    def _getParentNodes(self, node):
        """Returns list of XMLDom parent nodes

            Parameters
                node XMLDom node

            Returns
                list of IXMLDOMElement nodes, from root to given node
        """
        # check parent nodes
        parentNodes = []

        # loop until testset node comes
        tmpNode = node
        while 1:
            parent = tmpNode.parent()

            if parent.getName() == "testset":
                break
            else:
                parentNodes.insert(0, parent)
                tmpNode = tmpNode.parent()

        return parentNodes

    def _addMissingParents(self,
                           testSetDoc,
                           parentNodesInModel,
                           parentNodes):
        """Add missing parents of test case node to given test set model.

        Parameters
            testSetDoc
                XMLDom test set document

            parentNodesInModel
                dictionary {'path string':XMLDom }

            parentNodes
                list of XMLDom nodes which will be added if them does
                not exist in the testSetDoc
            """
        for parent in parentNodes:
            if not TestSetNodeBase(parent, self).getPath() in \
                parentNodesInModel.keys():
                hierarchy = NodeUtils('hierarchy', True)
                hierarchy.setAttribute('name',
                                       parent.getAttribute('name'))

                # append first to root
                if parentNodes.index(parent) == 0:
                    testSetDoc.append(hierarchy)
                else:
                    parentOfParent = parent.parent()

                    parentNodesInModel[
                        TestSetNodeBase(parentOfParent, self).getPath()\
                        ].append(hierarchy)

                parentNodesInModel[\
                    TestSetNodeBase(parent, self).getPath()] = \
                    hierarchy

    def _mergeNodesToDocument(self, nodeList):
        """Copies nodes from nodeList to document

        parameters

            nodeList        python list of TestSetNodeBase nodes to be merged

        Returns list of overwritten test results as list of tuples.
        Each tuple contains (path, old result, new result)
        """
        #list of tuples (path, testresult) where is listed these test
        #cases which test result value has chandes during merge operation
        changedList = []

        newTestSetDoc = self._testSetDocument

        # dict for parent nodes which are added to new test set model
        # key 'path' string , value XMLDOM node
        parentNodesInModel = self._getHierarchyDict()

        # filter hierarchy nodes out from the list
        nodeList = self._filterTestCaseNodes(nodeList)

        for node in nodeList:
            # NOTE this allows that there is same test case name under
            # different hierarchy node
            existingNode = self._selectTestCaseByPath(node.getPath())

            if existingNode:
                newTestResult = node.getTestResult()
                # test case node already exists in test set
                if not newTestResult or \
                   newTestResult.getResult() == NO_RUN :
                    # no new results
                    continue
                else:
                    # if test result has been changed, append it to
                    # list
                    existingTestResult = existingNode.getTestResult()
                    if existingTestResult and \
                       existingTestResult.getResult() != \
                       newTestResult.getResult():
                        changedList.append((existingNode.getPath(),
                                            existingTestResult.getResult(),
                                            newTestResult.getResult(),
                            ))

                    # new node has test result, replace existing
                    # test case node with new test case node
                    # -> test results will be also replaced that way

                    # Note : new node will be _moved_ to this report
                    # no need to copy here.

                    # Note : result node is moved even testResult is same
                    # because there may be tother data which is updated.
                    # this may be misleading because these nodes are not listed
                    # to changedList

                    parentDOMObject = existingNode.getDomInstance().parent()

                    parentDOMObject.replaceChild(existingNode.getDomInstance(),
                                                 node.getDomInstance())

                    # FIXME: Delete art2testresult node???
                    # NOTE art2testscript node must be saved???

            else: # new test case node

                self._appendNodesToDocument(node)

        return changedList

    def _appendNodesToDocument(self, nodeList):
        """Copies nodes from nodeList to document

        parameters

            nodeList        python list of TestSetNodeBase nodes to be merged

        Returns list of overwritten test results as list of tuples.
        Each tuple contains (path, old result, new result)
        """

        if type(nodeList)!= type([]):
            nodeList = [nodeList]
        # dict for parent nodes which are added to new test set model
        # key 'path' string , value XMLDOM node
        parentNodesInModel = self._getHierarchyDict()
        # filter hierarchy nodes out from the list
        nodeList = self._filterTestCaseNodes(nodeList)
        newTestSetDoc = self._testSetDocument

        for node in nodeList:
            # dom instance of node
            nodeDomOrig = node.getDomInstance()

            # make new node inscance, which will be put in new document
            nodeDomCopy = nodeDomOrig.clone()

            parentNodes = self._getParentNodes(nodeDomOrig)
            self._addMissingParents(newTestSetDoc,
                                    parentNodesInModel,
                                    parentNodes)

            # append test case node
            # FIXME: should all hierarchy nodes, which will have
            # new test cases, be open
            parentNodesInModel[\
                TestSetNodeBase(parentNodes[-1], self).getPath()\
                ].append(nodeDomCopy)


    def _replaceModelDom(self, newTestSetDom, fname = None):
        """Replaces current dom object with new one.

            Parameters
            newTestSetDom  : xml dom document object
            fname : string : file name of xml document
                (default None) which means, use current file name

        """
        if fname is None:
            fname = self._testSetFileName

        assert fname, 'File name not defined.'

        # if file is successfully loaded, take it in use
        self._initialize()
        self._testSetDocument = newTestSetDom
        # save file name
        self._testSetFileName = fname
        # FIXME: consider using only art2gui settings to store fname.
        # now _testSetFileName is invalid after user makes save as

        # read test set statistics from new dom
        self._readTestSetStatistics()

    def _loadTestSet(self, fname):
        """Load test set file

            Parameters

            fname       File name with full path where test set will be loaded

            Returns tuple
                new test set dom document (xml dom)
                file name : string
        """
        # FIXME: Harmonize interfaces in loadTestSet and loadSettings
        try:
            testSetDocument = NodeUtils(fname)
        except Exception, exception:
            raise TestSetModelException(str(exception))

        # typecheck XML file
        if testSetDocument.getName() != 'testset':
            raise TestSetModelException('Invalid testset file')
        if testSetDocument.getAttribute('version') \
                                            != self.TEST_SET_XML_VERSION:
            raise OldTestSetVersionException('Invalid testset version: %s. '
                                        'Expected: %s' % \
                (testSetDocument.getAttribute('version'),
                self.TEST_SET_XML_VERSION))
        # check duplicate test cases
        duplicateTestCases = self.checkDuplicateTestCases(testSetDocument)

        if duplicateTestCases:
            raise TestSetModelException('Unable to load test set!\n' \
                                        'Duplicate test cases found: \n' \
                                        '%s' % '\n'.join(duplicateTestCases))

        return (testSetDocument, fname)

    def _initializeTestSetStatistics(self):
        """Initializes test set statistics dict values."""
        self._testSetStatistics = {FAILED: 0,
                                   PASSED: 0,
                                   NA: 0,
                                   NO_RESULT: 0,
                                   FAILED_IN_TD: 0,
                                   FAILED_IN_SETUP:0,
                                   REMOTE_FAILED:0,
                                   TRAINING_RUN:0}

    def _readTestSetStatistics(self):
        """Reads test set statistics dict values from dom.

            This method is called in self._replaceModelDom and in
            self.deleteNodes
        """
        self._testSetStatistics[FAILED] = \
            len(self.selectTestCasesByResult(FAILED))
        self._testSetStatistics[PASSED] = \
            len(self.selectTestCasesByResult(PASSED))
        self._testSetStatistics[NA] = \
            len(self.selectTestCasesByResult(NA))
        self._testSetStatistics[NO_RESULT] = \
            len(self.selectTestCasesByResult(NO_RESULT))
        self._testSetStatistics[FAILED_IN_TD] = \
            len(self.selectTestCasesByResult(FAILED_IN_TD))
        self._testSetStatistics[FAILED_IN_SETUP] = \
            len(self.selectTestCasesByResult(FAILED_IN_SETUP))
        self._testSetStatistics[REMOTE_FAILED] = \
            len(self.selectTestCasesByResult(REMOTE_FAILED))
        self._testSetStatistics[TRAINING_RUN] = \
            len(self.selectTestCasesByResult(TRAINING_RUN))

    def _updateTestSetStatistics(self, oldResult, newResult):
        """Updates test set statistics dict.

            Parameters

                oldResult       result which have been changed
                newResult       result which replaces oldResult
        """
        if oldResult != NO_RUN:
            # decrease oldResult's value
            self._testSetStatistics[oldResult] -= 1

        if newResult != NO_RUN:
            # increase newResult's value
            self._testSetStatistics[newResult] += 1

    def _hasART2TestResultNodes(self):
        """Check if test set model has ART2TestResultNodes.

            Returns True if yes, otherwise False
        """
        if self._testSetDocument.find('//art2testresult') == None:
            return False
        else:
            return True
        
    def isValidTestSetFile(self, path):
        """ Checks whether given path is valid test set file.
        
        Parameters:
        
        path    str    absolute path to the file being tested
        
        Returns True if the file is a valid test set file.
        """
        
        # open the file as a NodeUtils instance
        try:
            testSetDocument = NodeUtils(path)
        except Exception:
            return

        # typecheck XML file
        if testSetDocument.getName() != 'testset' or \
            testSetDocument.getAttribute('version') \
            != self.TEST_SET_XML_VERSION:
            return
        
        # check duplicate test cases
        duplicateTestCases = self.checkDuplicateTestCases(testSetDocument)
        if not duplicateTestCases:
            return True       

    def setTreeIdForNode(self, node, treeId):
        """Stores tree id which corresponds test set node.

            When node value is updated it's needed to know which
            tree item must be updated.

            Parameters

            node       TestSetNodeBase object
            treeID     GUI specific tree id
        """
        self._treeIdDict[node.getPath()] = treeId


    def getTreeIdForNode(self, node):
        """Returns tree id for test set node.

           Parameters

           node       TestSetNodeBase object
        """
        return self._treeIdDict[node.getPath()]

    def getTreeIdForNodePath(self, nodePath):
        """Returns tree id for test set node path.

           Parameters

           nodePath       path to test set node
        """
        if nodePath in self._treeIdDict:
            return self._treeIdDict[nodePath]
        else:
            return None

    def saveTestSet(self, fname, setAsCurrent=True, processInfo=False, processInfoAddress = None):
        """Saves current test set model.

            Parameters

            fname   File name with full path where test set will be saved

            Raises TestSetModelException if save fails.
        """
        testSetNode = self.getRootNode()

        if not processInfoAddress:
            processInfo = False

        # store old name in case of errors
        oldName = testSetNode.getName()
        # set new name for saved file
        testSetNode.setName(os.path.splitext(os.path.basename(fname))[0])
        # save file
        try:
            self._testSetDocument.save(fname, processInfo=processInfo, processInfoAddress=processInfoAddress)
        except Exception, exception:
            # revert old test set name to DOM
            testSetNode.setName(oldName)
            raise TestSetModelException(unicode(exception))

        # save file name
        if setAsCurrent:
            self._testSetFileName = fname

    def saveTestSetBackup(self):
        """Saves a backup of test set model."""
        try:
            fileName = self.getFileName()
            self._testSetDocument.save(os.path.join(\
                os.path.dirname(fileName),
                os.path.splitext(os.path.basename(fileName))[0] + \
                '.testset_backup'))
        except Exception, error:
            print'Error in saving test set backup: %s' % str(error)
            #debug('Error in saving test set backup: %s' % str(error))


    def _checkBackupDate(self, fileName):
        """Checks if test set backup exists and is newer than test set.

        """
        backupPath = os.path.splitext(fileName)[0] + \
                '.testset_backup'

        if os.path.exists(backupPath):
            if os.path.getmtime(backupPath)>os.path.getmtime(fileName):
                return backupPath

        return False

    def mergeTestResults(self, sourceTestSet):
        """Merge test set to current test set document

            Parameters
                sourceTestSet : test set model instance, which is a test set
                                to be merged to current test set.

            Deletes art2testresults from sourceTestSet before merge.
            Returns list of overwritten test results as list of tuples.
            Each tuple contains (path, old result, new result)

        """
        # delete art2testresults from sourceTestSet
        testedTestCasesFromSource = sourceTestSet.selectTestedTestCases()

        for testCase in testedTestCasesFromSource:
            for testScript in testCase.getART2TestScripts():
                testScript.removeART2TestResults()

        # FIXME: view may have links to nodes which will be deleted during
        # this operation

        # FIXME: how to merge if manual and automated test case has same name?
        sourceTestSetNode = sourceTestSet.getRootNode()
        thisTestSetNode = self.getRootNode()

        # assert that documents has same name
        if thisTestSetNode.getName() != sourceTestSetNode.getName():
            raise TestSetModelException(
                'Report names does not match. "%s" != "%s" ' % \
                (self.getRootNode().getName(), sourceTestSetNode.getName() ))

        # assert that documents has same PUT
        if thisTestSetNode.getPUT() != sourceTestSetNode.getPUT():
            raise TestSetModelException(
                'PUT names does not match. "%s" != "%s" ' % \
                (self.getRootNode().getPUT(), sourceTestSetNode.getPUT() ))

        sourceNodeList = sourceTestSet.selectChildNodes(sourceTestSetNode)

        return self._mergeNodesToDocument(sourceNodeList)

    def getEmptyHierarchyNodes(self):
        """Returns list of empty hierarchy nodes"""
        result = []
        nodes = self._testSetDocument.findall('//hierarchy')
        nodes = [node for node in nodes if not node.hasChildNodes()]

        for node in nodes:
            result.append(HierarchyNode(node, self))

        return result

    def saveAll(self, fname):
        """Saves test set to file and copies whole detailed report folder
           content to a new location if location changes .

            Parameters

                fname   File name with full path where test set will be saved

            Raises TestSetModelException if save fails.
        """
        # store old name before saving
        sourcePath = self.getReportFolder()

        # save new .testset
        self.saveTestSet(fname)

        # get new name after saving
        targetPath = self.getReportFolder()

        return sourcePath, targetPath

    def saveSelection(self, fname, nodeList):
        """Saves copy of selected nodes to file.

            Parameters

            fname       File name with full path where test set will be saved
            nodeList    List of selected node instances to be saved

            Returns     New newTestSetModel object
        """
        newTestSetModel = TestSetModel()
        # load test set template
        newTestSetModel.loadTestSet(test_set_template_name)
        newTestSetModel._mergeNodesToDocument(nodeList)

        # FIXME: This setName is useless, because the name is then
        # overwritten in saveTestSet
        # Should this be removed?
        newTestSetModel.getRootNode().setName(
            'selection_from_%s' % self.getRootNode().getName())
            
        # save root node attributes
        newRootNode = newTestSetModel.getRootNode().getDomInstance()
        origRootNode = self.getRootNode().getDomInstance()
            
        for attr in origRootNode.getAttributes():
            newRootNode.setAttribute(attr, origRootNode.getAttribute(attr))

        # save file to a new location
        newTestSetModel.saveTestSet(fname)

        return newTestSetModel

    def getModelFromSelection(self, nodeList):
        """Get copy of selected nodes.

            Parameters

            nodeList    List of nodes to be copied to new test set model

            Returns     New TestSetModel object
        """
        newTestSetModel = TestSetModel()
        # load test set template
        newTestSetModel.loadTestSet(test_set_template_name)
        newTestSetModel._appendNodesToDocument(nodeList)
        newTestSetModel.getRootNode().setName(
            'selection_from_%s' % self.getRootNode().getName())

        return newTestSetModel

    def loadTestSet(self, fname):
        """Load test set file.

            Parameters

            fname       File name with full path where test set will be loaded
        """
#         try:
        newTestSetDom, fname = self._loadTestSet(fname)
#         except OldTestSetVersionException:
            # Note :
            # if "initialise()" and "self._testSetDocument = None" is not done,
            # old test set stays valid when loading fails
##            self._initialize()
##            self._testSetDocument = None
#             raise

        self._replaceModelDom(newTestSetDom, fname)

    def getRootNode(self):
        """Returns testset node."""
        if self._testSetDocument:
            return TestSetNode(self._testSetDocument, self)
        else:
            raise TestSetModelException('No xml document available ' \
                                        'for getting root node!')

    def getFileName(self):
        """Returns the file name of test set."""
        if self._testSetFileName:
            return self._testSetFileName
        else:
            return None

    def getDocument(self):
        """Returns the DOM doument object of test set."""
        if self._testSetDocument:
            return self._testSetDocument
        else:
            return None

    def getReportFolder(self):
        """Returns detailed report foldername."""
        # Create detailed test result folder name.
        testSetPath = self.getFileName()
        baseName =  os.path.splitext(testSetPath)[0]
        folderName = os.path.join(os.path.dirname(baseName),
                                  os.path.basename(baseName) + \
                                  '_detailed_report')

        return folderName

    def updateTestResultFromART2TestResult(self, testCase, memLeak, leakFiles=[]):
        """Updates test case's results from ART2TestResult

            Parameters:
             testCase : TestCaseNode instance of which result to update
        """
        testResult = testCase.getTestResult()
        art2TestResult = self._resolveTestResult(testCase, memLeak)

        if art2TestResult and art2TestResult.isDetailedReportFile():
            art2DetailedReport = art2TestResult.getDetailedReport()
            testResult.setResult(art2DetailedReport.getResult())
            testResult.setAuthor(art2DetailedReport.getAuthor())
            testResult.setTestTime(art2DetailedReport.getTestTime())
            testResult.setTestDate(art2DetailedReport.getTestDate())
            testResult.setErrorTitle(art2DetailedReport.getFailReason())
            testResult.setDescription(unicode('\n'.join(art2DetailedReport.getWarnings())))
            warnings = art2DetailedReport.getGeneralWarnings()
        else:
            testResult.setAuthor(os.environ.get('USERNAME') or 'John Doe')
            testResult.setTestTime(time.strftime("%H:%M:%S"))
            testResult.setTestDate(time.strftime("%Y-%m-%d"))
            testResult.setErrorTitle('Fatal error occurred!')
            testResult.setResult(NO_RESULT)
            testResult.setDescription('Detailed report file was not found!')
            warnings = []

        if memLeak:
            testCase.setLeakRun(True)
            if testResult.setLeakFile(leakFiles) and \
               testResult.getResult() == FAILED:
                testResult.deleteLeakFile()

        return warnings
    
    def updateArtTestCaseStatics(self):      
        """Update test set statistics
		"""	
        statVariables = ['passed', 'failed', 'na','noresult','norun']
        #add empty attributes to rood node
        for attribute in statVariables:
            self._testSetDocument.setAttribute(attribute, '0')
        
        #add empty attributes to hierarchy nodes
        for node in self._testSetDocument.findall('//hierarchy'):
            for attribute in statVariables:
                node.setAttribute(attribute, '0')
        #add  test statistics to hierarchy nodes and root node
        for result in self._testSetDocument.findall('//testresult'):
            TestResultNode(result.parent().parent(), self).updateResultStatistic(result.getAttribute('result'))        
            self.getRootNode().updateResultStatistic(result.getAttribute('result'),recursive=False)

    def _resolveTestResult(self, testCase, memLeak):
        """ Helper to resolve result.
        """
        validTestResult = None
        art2TestResults = testCase.getART2TestScripts()[0].getART2TestResults()

        for art2TestResult in art2TestResults:
            if art2TestResult.isDetailedReportFile():
                art2DetailedReport = art2TestResult.getDetailedReport()
                art2TestResult.setResult(art2DetailedReport.getResult())
                if memLeak:
                    if art2TestResult.getResult() != PASSED:
                        validTestResult = art2TestResult

        if not validTestResult:
            validTestResult = art2TestResults[-1]

        return validTestResult

    def selectTestCasesByResult(self, result):
        """Returns a list of test case node instances which test result nodes
           have the given test result value.

            Parameters

            result      One of the valid test results
                                    or
                        'Tested' which means that all test results except
                        'No Run' are returned
        """
        testCaseNodes = []

        # define search string
        if result == 'Tested':
            searchString = '//testresult[@result!="%s"]' % NO_RUN
        elif result == 'Not passed':
            searchString = '//testresult[@result!="%s" and @result!="%s"]' % (NO_RUN,PASSED)
        else:
            searchString = '//testresult[@result = "%s"]' % result

        for testResultNode in self._testSetDocument.findall(searchString):
            testCaseNodes.append(TestCaseNode(testResultNode.parent(), self))

        return testCaseNodes

    def selectTestCaseByName(self, name):
        """Returns test case node instances which has the given name value.

            Parameters

            name        'One of the valid name values
        """
        # define search string
        searchString = '//testcase[@name="%s"]' % name
        testCase = self._testSetDocument.find(searchString)


        return testCase and TestCaseNode(testCase, self) or None

    def selectTestCasesByPriority(self, priority):
        """Returns a list of test case node instances which
           have the given priority value.

            Parameters

            priority    'One of the valid priority values
        """
        testCaseNodes = []

        # define search string
        searchString = '//testcase[@priority="%s"]' % priority

        for testCase in self._testSetDocument.findall(searchString):
            testCaseNodes.append(TestCaseNode(testCase, self))

        return testCaseNodes

    def selectTestedTestCases(self):
        """Returns a list of test case node instances which have been tested.

            selectTestCasesByResult function is called with parameter
            'Tested'.
        """
        return self.selectTestCasesByResult('Tested')

    def selectTestCasesWithNewErrors(self):
        """Returns a list of test case node instances which test result nodes'
           new_error attribute is True.
        """
        testCaseNodes = []

        for testResultNode in self._testSetDocument.findall(\
                                    '//testresult[@new_error = "True"]'):
            testCaseNodes.append(TestCaseNode(testResultNode.parent(), self))

        return testCaseNodes

    def selectTestCasesWithLeaks(self):
        """Returns a list of test case node instances which test result nodes'
           new_error attribute is True.
        """
        testCaseNodes = []

        for testResultNode in self._testSetDocument.findall(\
                                    '//testresult[@leak_found = "True"]'):
            testCaseNodes.append(TestCaseNode(testResultNode.parent(), self))

        return testCaseNodes

    def selectChildNodes(self, parentNode):
        """Returns a list of child hierarchy and testcase node instances for
           a given parent node.

            Parameters

            node        TestCaseNode, TestSetNode or HierarchyNode instance
        """
        nodeName = parentNode.getDomInstance().getName()

        if not nodeName in ['testset', 'hierarchy', 'testcase']:
            raise TestSetModelException('parentNode parameter is not a '
                                        'TestSetNode, a HierarchyNode or'
                                        'a TestCaseNode instance!')

        childNodeList = []

        nodeDom = parentNode.getDomInstance()
        name = parentNode.getName()

        # FIXME: there should be way to select without using
        # hierarchy[@name="%s"]

        if nodeName=='testcase':
            nodeList = nodeDom.findall(\
                       '//%s[@name="%s"]//art2testscript//art2testresult' % (nodeName, name))

            for node in nodeList:
                childNodeList.append(ART2TestResultNode(node, self))
        else:
            nodeList = nodeDom.findall(\
                       '//%s[@name="%s"]//testcase' % (nodeName, name))
            for node in nodeList:
                childNodeList.append(TestCaseNode(node, self))

            nodeList = nodeDom.findall(\
                       '//%s[@name="%s"]//hierarchy' % (nodeName, name))

            for node in nodeList:
                childNodeList.append(HierarchyNode(node, self))

        return childNodeList

    def deleteNodes(self, nodeList):
        """Deletes given nodes from test set model.

            Parameters

            nodeList    List of selected node instances to be deleted
        """
        try:
            assert nodeList, 'nodeList parameter empty!'

            # loop through nodes and delete them
            for node in nodeList:
                assert isinstance(node, TestSetNodeBase)

                # if node has a path (= GUI has set it),
                # remove node reference from self._treeIdDict
                if node._path and self._treeIdDict.has_key(node.getPath()):
                    self._treeIdDict.pop(node.getPath())

                nodeDom = node.getDomInstance()
                # remove node's dom object
                nodeDom.parent().remove(nodeDom)

            # read test set statistics from new dom
            self._readTestSetStatistics()

        except Exception, exception:
            raise TestSetModelException(str(exception))

    def getAllTestCases(self):
        """Returns a list of all case node instances.

            Parameters
            None

            Returns

            Test case node instance list.
        """
        testCaseNodes = []

        if self._testSetDocument:
            for testCase in self._testSetDocument.findall('//testcase'):
                testCaseNodes.append(TestCaseNode(testCase, self))

        return testCaseNodes

    def getManualTestCases(self):
        """Returns a list of manual test case node instances.

            Parameters
            None

            Returns

            Test case node instance list.
        """
        testCaseNodes = []

        for testCase in self._testSetDocument.findall('//testcase'):
            if not testCase.find('art2testscript'):
                testCaseNodes.append(TestCaseNode(testCase, self))

        return testCaseNodes

    def getAutomatedTestCases(self):
        """Returns a list of automated test case node instances.

            Parameters
            None

            Returns

            Test case node instance list.
        """
        testCaseNodes = []

        for testCase in self._testSetDocument.findall('//testcase'):
            if testCase.find('art2testscript'):
                testCaseNodes.append(TestCaseNode(testCase, self))

        return testCaseNodes

    def getTestCase(self, subarea, feature, tcid):
        """Returns a test case node instance.

            Parameters:
            subarea
            feature
            tcid

            Returns

            Test case node instance.
        """

        for testCase in self._testSetDocument.findall('//testcase[@name="%s"]'%tcid):
            if testCase.parent().parent().getAttribute('name')==subarea and testCase.parent().getAttribute('name')==feature:
                return TestCaseNode(testCase, self)

        return None

    def getTestSetStatistics(self):
        """Returns test set statistics dict."""
        return self._testSetStatistics

    def makeTestSet(self, testCaseList, testSetName, includeScriptNodes,
                    removeDuplicateTestCases = False, testGroup=None):
        """Makes new test set.

            Parameters

            testCaseList                list of test cases, each in own
                                        dictionary
            testSetName                 name of the test set to be made
            includeScriptNodes          include script nodes
                                        (= automated test set)
                                        or not (= manual test set)
            removeDuplicateTestCases    remove duplicate test cases
                                        (default = False)
            testGroup                   List of the test group names if test
                                        case was created using __init__-files.

            Returns
            None
        """
        self._testSetDocument = NodeUtils(test_set_template_name)

        # set name of the test set
        self.getRootNode().setName(\
            os.path.splitext(os.path.basename(testSetName))[0])
        if testGroup is not None:
            self.getRootNode().setGenTestset(testGroup)

        addedTestCases = []

        # add test cases
        for testCase in testCaseList:
            if removeDuplicateTestCases:
                if testCase in addedTestCases:
                    continue

            self.addTestCase(testCase,
                             includeScriptNodes and 'automated' or 'manual')

            if removeDuplicateTestCases:
                addedTestCases.append(testCase)

        # sort and save the xml document
        if testGroup and \
         ('MENU_STABILITY_TEST' in testGroup or \
          'MENU_STABILITY_AND_PERFORMANCE_TEST' in testGroup or \
          'MENU_STRUCTURE_TEST' in testGroup):            
            # skip sorting with menu test sets
            self._testSetDocument.save(testSetName)
        else:
            # FIXME: sortGUITestsetXML's transform will remove doctype
            #        Solve this and take sorting back into use or find some other way
            self._testSetDocument.save(testSetName)

    def addTestCase(self, testCase, testCaseType = 'automated'):
        """Adds new test case to test set.

           Subarea and feature are also added if they don't already exist.
           Currently used only in test set generating.

            Parameters

            testCase        test case dictionary
                            e.g.
                            {'subarea': 'Other Features',
                             'feature': 'Alarm Clock',
                             'module': 't_manual_tests_from_excel.tests_from_excel',
                             'class': 'OtherFeaturesAlarmClockTest',
                             'tcid': '2.5 Alarm expiry',
                             'method': 'testAC56'
                             'ucid':'UCID1234566'}
            testCaseType    test case type ('automated' or 'manual')

            Returns
            None
        """
        assert testCaseType in ['automated', 'manual'], \
            'Invalid testCaseType parameter given!'

        try:
            lastDotIndex = testCase['module'].rfind('.')
            foldername = testCase['module'][:lastDotIndex]
            filename = testCase['module'][lastDotIndex + 1:]
        except IndexError, err:
            raise TestSetModelException(\
                "Syntax error in testCase['module']: " \
                "%s, %s" % (testCase['module'], str(err)))

        testSetNode = self.getRootNode().getDomInstance()                
                
        # create testcase element
        testcase = NodeUtils('testcase', True)
        testcase.setAttribute('name', filterString(testCase['tcid']))
        # check if testCase dict has priority and add it to result
        if testCase.has_key('priority'):
            testcase.setAttribute('priority', testCase['priority'])

        # create testresult element
        testresult = NodeUtils('testresult', True)
        if testCase.has_key('result'):
            testresult.setAttribute('result', testCase["result"])
        else:
            testresult.setAttribute('result', 'No Run')

        # check if testCase dict has description and add it to result
        if testCase.has_key('description'):
            testresult.setAttribute('description', testCase['description'])

        # check if testCase dict has use case id and add it to test case
        if testCase.has_key('ucid'):
            testcase.setAttribute('ucid', testCase['ucid'])

        testcase.append(testresult)

        if testCaseType == 'automated':
            # create art2testscript element
            art2testscript = NodeUtils('art2testscript', True)
            art2testscript.setAttribute('directory', foldername)
            art2testscript.setAttribute('file', filename)
            art2testscript.setAttribute('class', testCase['class'])
            art2testscript.setAttribute('method', testCase['method'])
            testcase.append(art2testscript)

        # search for test case's parent
        parent = self._testSetDocument.findall(\
                '/testset/hierarchy[@name = "%s"]/hierarchy[@name = "%s"]' % \
                (filterString(testCase['subarea']),
                 filterString(testCase['feature'])))

        # parent subarea/feature hierarchy node found
        if len(parent) == 1:
            parent = parent[0]
        # parent subarea/feature hierarchy node not found
        else:
            assert len(parent) == 0, 'Invalid parent length: %s' % len(parent)

            # look for subarea hierarchy node
            subarea = self._testSetDocument.findall(\
                      '/testset/hierarchy[@name = "%s"]' % \
                      filterString(testCase['subarea']))

            # subarea hierarchy not found
            if len(subarea) != 1:
                assert len(subarea) == 0, 'Invalid subarea length: %s' % \
                                            str(len(subarea))
                # create subarea hierarchy to dom
                subarea = NodeUtils('hierarchy', True)
                subarea.setAttribute('name', filterString(testCase['subarea']))
                subarea.setAttribute('passed', '0')
                subarea.setAttribute('failed', '0')
                subarea.setAttribute('noresult', '0')
                subarea.setAttribute('norun', '0')
                subarea.setAttribute('na', '0')
                
                # append subarea node to test set root
                testSetNode.append(subarea)     
            # subarea hierarchy node exists
            else:
                subarea = subarea[0]

            # create new feature node and append it to subarea node
            featureNode = NodeUtils('hierarchy', True)
            featureNode.setAttribute('name', filterString(testCase['feature']))
            featureNode.setAttribute('passed', '0')
            featureNode.setAttribute('failed', '0')
            featureNode.setAttribute('noresult', '0')
            featureNode.setAttribute('norun', '0')
            featureNode.setAttribute('na', '0')
            subarea.append(featureNode)            

            # find updated feature node to parent
            parent = subarea.find(\
                      'hierarchy[@name = "%s"]' % \
                        filterString(testCase['feature']))

        # append new test case node to feature level and update test case count
        parent.append(testcase)
        parent.setAttribute('norun',str(int(parent.getAttribute('norun'))+1))
        
        # update test case count to subarea level
        subarea = self._testSetDocument.find(\
                '/testset/hierarchy[@name = "%s"]' % \
                filterString(testCase['subarea']))
        subarea.setAttribute('norun',str(int(subarea.getAttribute('norun'))+1))
        
        # update test case count to root level
        testSetNode.setAttribute('norun',str(int(testSetNode.getAttribute('norun'))+1))

    def checkDuplicateTestCases(self, testSetDocument):
        """Checks if there are duplicate test case names in test set model.

            Parameters

            testSetDocument    xml dom document object

            Returns list of duplicates if found, otherwise False
        """
        # get all test case nodes
        testCases = testSetDocument.findall('//testcase')

        # loop through the list and save paths to a list
        testCasePaths = []
        for testCase in testCases:
            testCasePaths.append(TestSetNodeBase(testCase, self).getPath())

        # loop through the path list and save duplicates to a dict
        duplicateDict = {}
        keys = {}

        for testCasePath in testCasePaths:
            # get hierarchy path and test case name from testCasePath
            hierarchyPath = testCasePath[:(testCasePath.rfind('/'))]
            testCaseName = testCasePath[(testCasePath.rfind('/')):].strip('/')

            # if test case path in keys --> duplicate found
            if testCasePath in keys:
                # make duplicate dict in the first time
                if not hierarchyPath in duplicateDict:
                    duplicateDict[hierarchyPath] = []

                # append duplicate test case information to dict
                duplicateDict[hierarchyPath].append(testCaseName)
            else:
                keys[testCasePath] = 1

        if duplicateDict:
            duplicateList = []

            for item in duplicateDict.items():
                # make test case list
                testCaseList = []

                for testCase in item[1]:
                    testCaseList.append('"%s"' % testCase)

                # append test case information to duplicate list
                duplicateList.append('%s in\n%s \n' % \
                    (',\n'.join(testCaseList), item[0]))

            return duplicateList
        else:
            return False

    def testSetConverter(self, fname):
        """ Converts old test set file to latest format

            fname   file name of the test set to be converted

        """

        resultRenameDict =  {
                                'Skipped':NA,
                                'Test env. error':NO_RESULT,
                                'Not tested':NO_RUN
                            }

        # get all test case nodes
        testCases = []
        testCases.extend(self.getManualTestCases())
        testCases.extend(self.getAutomatedTestCases())
        #Create a new test set so that the doctype is updated        
        newTestSet = self.getModelFromSelection(testCases)
        newTestModel = newTestSet.getRootNode()
        currentTestModel = self.getRootNode()
        newTestModel.setPUT(currentTestModel.getPUT())
        newTestModel.setGenTestset(currentTestModel.getGenTestset())
        newTestModel.setQCXml(currentTestModel.getQCXml())
        newTestModel.setName(currentTestModel.getName())
        self = newTestSet
        
        # loop through the list and convert results
        for testCase in testCases:
            result = testCase.getTestResult().getResult()
            if result in resultRenameDict.keys():
                testCase.getTestResult().setResult(resultRenameDict[result],False, True)
        
        # Add new test_type tags to art2testresult if they are missing.
        for testCase in self._testSetDocument.findall('//art2testresult'):
            if not 'test_type' in testCase.getAttributes():
                testCase.setAttribute('test_type', 'UI Test')
                        
        #Update test set version
        self._testSetDocument.setAttribute('version', \
            self.TEST_SET_XML_VERSION)
        #Update statistics
        self._readTestSetStatistics()
        self.updateArtTestCaseStatics()

        try:
            self._testSetDocument.save(fname)
        except Exception, exception:
            raise TestSetModelException(unicode(exception))

    def getItemCount(self):
        """Return the count of items (hierarchy + testcase) nodes."""
        if self._testSetDocument:
            hierarchies = self._testSetDocument.findall('//hierarchy')
            testCases = self._testSetDocument.findall('//testcase')
            
            return len(hierarchies) + len(testCases)
        else:
            return 0
        

# ============================================================================
class TestSetNodeBase(object):
    """Common node class for all testset nodes."""
    def __init__(self, nodeInstance, testSetModel):
        """Initialize TestSetNodeBase."""
        # store DOM instance of this node
        self._domInstance = nodeInstance
        # stote testSetModel instance
        self._testSetModel = testSetModel
        self._path = None
        #self._initTestSetStatistics()

##    def _cloneNode(self):
##        """Clone node.
##
##            Returns new, cloned node"""
##        clone = TestSetNodeBase(self.getDomInstance().clone())
##        clone._path = self.getPath()
##        return clone

    def _returnNodeClass(self, nodeInstance):
        """Initializes the right node class according to nodeName and
           returns it.
        """
        if nodeInstance.getName() == u'hierarchy':
            nodeClass = HierarchyNode(nodeInstance, self._testSetModel)
        elif nodeInstance.getName() == u'testcase':
            nodeClass = TestCaseNode(nodeInstance, self._testSetModel)
        elif nodeInstance.getName() == u'testresult':
            nodeClass = TestResultNode(nodeInstance, self._testSetModel)
        elif nodeInstance.getName() == u'art2testscript':
            nodeClass = ART2TestScriptNode(nodeInstance, self._testSetModel)
        elif nodeInstance.getName() == u'art2testresult':
            nodeClass = ART2TestResultNode(nodeInstance, self._testSetModel)
        else:
            nodeClass = None

        return nodeClass

    def getDomInstance(self):
        """Returns self._domInstance."""
        return self._domInstance

    def getName(self):
        """Returns name attribute."""
        return self._domInstance.getAttribute('name')

    def setName(self, name):
        """Sets name attribute"""
        self._domInstance.setAttribute('name', name)

    def getPath(self):
        """Returns position of node as xpath like string."""
        # speedup, path is generated only once.
        if self._path:
            return self._path

        returnValue = [self.getName()]

        domNode = self._domInstance

        while domNode.getName() != 'testset':
            domNode = domNode.parent()
            name = domNode.getAttribute('name')
            returnValue.insert(0, name)
        # pop root item away
        returnValue.pop(0)

        path = '/'.join(returnValue)

        self._path = path

        return path

    def getParent(self):
        """Returns first sibling node or None if no sibling nodes."""
        parentNode = None

        if self._domInstance.parent():
            parentNode = self._returnNodeClass(self._domInstance.parent())

        return parentNode

    def getNextSibling(self):
        """Returns first sibling node or None if no sibling nodes."""
        nextSibling = None

        if self._domInstance.next():
            nextSibling = self._returnNodeClass(self._domInstance.next())

        return nextSibling

    def getFirstChild(self):
        """Returns first child node or None if no child nodes."""
        firstChild = None

        if self._domInstance.first():
            firstChild = self._returnNodeClass(self._domInstance.first())

        return firstChild

    def isOpen(self):
        """Returns node's open status."""
        return self._domInstance.getAttribute('open') == \
               'True' and True or False

    def setOpenStatus(self, status):
        """Sets node's open status."""
        assert status in [True, False], 'status attribute must be True or False'
        self._domInstance.setAttribute('open', str(status))
    
    def updateResultStatistic(self, newvalue, oldvalue = None, recursive=True):
        """ Decrease statistics recursevely"""
        #assert newvalue in self._testSetNodeStatistics.keys(), "could not find key %s from hierarchy" % newvalue
        if oldvalue:
            if oldvalue == PASSED:
                self.setPassedCount(self.getPassedCount()-1)
            elif oldvalue in [FAILED,FAILED_IN_TD, FAILED_IN_SETUP]:
                self.setFailedCount(self.getFailedCount()-1)
            elif oldvalue == NO_RUN:
                self.setNoRunCount(self.getNoRunCount()-1)
            elif oldvalue in [NO_RESULT]:
                self.setNoResultCount(self.getNoResultCount()-1)
            elif oldvalue in [NA]:
                self.setNACount(self.getNACount()-1)
            
        if newvalue == PASSED:
            self.setPassedCount(self.getPassedCount()+1)
        elif newvalue in [FAILED,FAILED_IN_TD, FAILED_IN_SETUP]:
            self.setFailedCount(self.getFailedCount()+1)
        elif newvalue == NO_RUN:
            self.setNoRunCount(self.getNoRunCount()+1)
        elif newvalue in [NO_RESULT]:
            self.setNoResultCount(self.getNoResultCount()+1)
        elif newvalue in [NA]:
            self.setNACount(self.getNACount()+1)
            
        if recursive:
            parent =  self._returnNodeClass(self._domInstance.parent())
            if parent:
                parent.updateResultStatistic(newvalue, oldvalue)
            
    def setPassedCount(self,value):
        """ SetPassedCount"""
        self._domInstance.setAttribute('passed', str(value))
    
    def setFailedCount(self,value):
        """ SetPassedCount"""
        self._domInstance.setAttribute('failed', str(value))

    def setNoRunCount(self,value):
        """ SetPassedCount"""
        self._domInstance.setAttribute('norun', str(value))
        
    def setNoResultCount(self,value):
        """ SetPassedCount"""
        self._domInstance.setAttribute('noresult', str(value))
        
    def setNACount(self,value):
        """ SetPassedCount"""
        self._domInstance.setAttribute('na', str(value))

    def getPassedCount(self):
        """Returns passed count."""
        return int(self._domInstance.getAttribute('passed'))

    def getFailedCount(self):
        """Returns passed count."""
        return int(self._domInstance.getAttribute('failed'))

    def getNoRunCount(self):
        """Returns passed count."""
        return int(self._domInstance.getAttribute('norun'))

    def getNoResultCount(self):
        """Returns passed count."""
        return int(self._domInstance.getAttribute('noresult'))
        
    def getNACount(self):
        """Returns passed count."""
        return int(self._domInstance.getAttribute('na'))

    def initTestSetStatistics(self):
        """Initializes test set statistics dict values."""
        self.setPassedCount(0)
        self.setFailedCount(0)
        self.setNoRunCount(0)
        self.setNoResultCount(0)

        
# ============================================================================
class TestSetNode(TestSetNodeBase):
    """Class for testset node."""
    def setPUT(self, putName):
        """Set name of the product under test.

        Parameters

            PUTName (String) application spesific description of the product
            under test.
        """
        self._domInstance.setAttribute('PUT', putName)

    def getPUT(self):
        """Get name of the product under test

        Returns (string) application spesific description about product under
        test.
        """
        return self._domInstance.getAttribute('PUT')

    def setGenTestset(self, genTestset):
        """Set list of the testset which set was generated from.

        Parameters

            genTestset (list) list of the testsets
            which set was generated from.
        """
        self._domInstance.setAttribute('gen_testset', str(genTestset))

    def getGenTestset(self):
        """Get list of the testsets which set was generated from.

        Returns evaluated list of the testsets which set
        was generated from.
        """
        nodeValue = self._domInstance.getAttribute('gen_testset')
        if nodeValue:
            return eval(nodeValue)
        else:
            return None

    def setQCXml(self, qcXmlName):
        """Set name of the xml-file which set was generated from.

        Parameters

            qcXmlName (String) name of the xml-file which set was generated from.
        """
        self._domInstance.setAttribute('qc_xml_name', qcXmlName)

    def getQCXml(self):
        """Get name of the xml-file which set was generated from.

        Returns (string) name of the xml-file which set was generated from.
        """
        return self._domInstance.getAttribute('qc_xml_name')

# ============================================================================
class HierarchyNode(TestSetNodeBase):
    """Class for hierarchy nodes."""

# ============================================================================
class TestCaseNode(TestSetNodeBase):
    """Class for testcase nodes."""
    def __init__(self, nodeInstance, testSetModel):
        """Initialize TestCaseNode."""
        TestSetNodeBase.__init__(self, nodeInstance, testSetModel)
        self._testResult = None

    def getTestResult(self):
        """Returns testcase's testresult node."""
        if self._testResult:
            return self._testResult

        nodes = self._domInstance.findall('testresult')

        if len(nodes) == 0:
            self._testResult = None
        else:
            self._testResult = TestResultNode(nodes[0], self._testSetModel)

        return self._testResult

    def getART2TestScripts(self):
        """Returns test case's ART2 test script nodes."""
        art2TestScriptNodes = []

        for node in self._domInstance.findall('art2testscript'):
            art2TestScriptNodes.append(ART2TestScriptNode(node,
                                                          self._testSetModel))

        return art2TestScriptNodes

    def getLeakRun(self):
        """ Return true if test case has been run with mem leak setting """
        return self._domInstance.getAttribute('leak_run') == \
               'True' and True or False

    def getRetest(self):
        """ Return true if test case has been run with retest setting """
        return self._domInstance.getAttribute('retest_on') == \
               'True' and True or False

    def getRepeat(self):
        """ Return true if test case has been run with repeat setting """
        return int(self._domInstance.getAttribute('repeats') or '1')

    def isAutomated(self):
        """Returns True if test case has art2testscript nodes."""
        if self._domInstance.find('art2testscript'):
            return True
        else:
            return False

    def isManual(self):
        """Returns True if test case is a manual one."""
        return not self.isAutomated()

    def setUCID(self, ucid):
        """Set use case id of the test case.

        Parameters

            ucid (String) use case id of the test case.
        """
        self._domInstance.setAttribute('ucid', ucid)

    def getUCID(self):
        """Get use case id of the test case.

        Returns (string) use case id of the test case.
        """
        return self._domInstance.getAttribute('ucid')

    def getPriority(self):
        """Returns test case's priority value."""
        return self._domInstance.getAttribute('priority')

    def setLeakRun(self, leakRun):
        """Sets the value of leak_run attribute."""
        assert leakRun in [True, False], \
            'leakRun attribute must be True or False'
        return self._domInstance.setAttribute('leak_run', str(leakRun))

    def setRetest(self, retestOn):
        """Sets the value of retest_on attribute."""
        assert retestOn in [True, False], \
            'retestOn attribute must be True or False'
        return self._domInstance.setAttribute('retest_on', str(retestOn))

    def setRepeat(self, repeats):
        """Sets the value of repeats attribute."""
        assert type(repeats)==int , \
            'repeats attribute must be integer'
        return self._domInstance.setAttribute('repeats', str(repeats))

# ============================================================================
class TestResultNode(TestSetNodeBase):
    """Class for testresult nodes."""
    def getName(self):
        """Returns nodeName."""
        return self._domInstance.getName()

    def getResult(self):
        """Gets the value of result attribute."""
        return self._domInstance.getAttribute('result')

    def getNewError(self):
        """Gets the value of new_error attribute."""
        return self._domInstance.getAttribute('new_error') == \
               'True' and True or False

    def getErrorID(self):
        """Gets the value of error_id attribute."""
        return self._domInstance.getAttribute('error_id')

    def getErrorTitle(self):
        """Gets the value of error_title attribute."""
        return self._domInstance.getAttribute('error_title')

    def getDescription(self):
        """Gets the value of description attribute."""
        return self._domInstance.getAttribute('description')

    def getAuthor(self):
        """Gets the name of tester

        Returns string
        """
        return self._domInstance.getAttribute('author')

    def getTestTime(self):
        """Gets time when test was tested

        Returns (string) test time in application spesific format.
        """
        return self._domInstance.getAttribute('time')

    def getTestDate(self):
        """Gets time when test was tested

        Returns (string) test date in application spesific format.
        """
        return self._domInstance.getAttribute('date')

    def getLeakFound(self):
        """Gets leak status of test case
        """
        return self._domInstance.getAttribute('leak_found') == \
               'True' and True or False

    def getLeakFile(self):
        """Gets memory leak file

        Returns (string) path to memory leak file or empty string.
        """
        return self._domInstance.getAttribute('leak_file')

    def setResult(self, result, deleteDetailedReports = True, versionUpdate=False):
        """Sets the value of result attribute.

            Parameters:
             result : new result, must be in FAILED, PASSED, NA,
                                    NO_RESULT, NO_RUN
             deleteDetailedReports : If set to True, deletes detailed
                 reports when result is changed to NO_RUN, otherwise not,
                 defaults to True
            versionUpdate : set to true if called when updating test set
        """
        
        assert result in \
               [FAILED, PASSED, NA, NO_RESULT, NO_RUN,\
                FAILED_IN_TD,FAILED_IN_SETUP,REMOTE_FAILED,TRAINING_RUN], \
                'result must be in FAILED, PASSED, NA, ' \
                'NO_RESULT, NO_RUN, FAILED_IN_TD,'\
                'FAILED_IN_SETUP,REMOTE_FAILED,TRAINING_RUN. Got "%s".' % \
                result
        try:
            if 'norun' in self._domInstance.parent().parent().getAttributes() and self._domInstance.parent().parent()['norun'] != '':
                self._returnNodeClass(self._domInstance.parent().parent()).updateResultStatistic(result, self.getResult())
                self._testSetModel.getRootNode().updateResultStatistic(result, self.getResult(), recursive=False)
        except:
            print('Could not add statistics to hierarchy nodes')

        if result == NO_RUN and deleteDetailedReports:
            self.deleteLeakFile()
            parentTestCase = TestCaseNode(self._domInstance.parent(),
                                          self._testSetModel)
            for testScript in parentTestCase.getART2TestScripts():
                for testResult in testScript.getART2TestResults():
                    if testResult.isDetailedReportFile():
                        reportNode = testResult.getDetailedReport()
                        reportNode.removeDetailedTestReportFiles()
                testScript.removeART2TestResults()

        # call self._updateTestSetStatistics
        if not versionUpdate:
            self._testSetModel._updateTestSetStatistics(\
                self._domInstance.getAttribute('result'),
                result)

        return self._domInstance.setAttribute('result', result)

    def setNewError(self, newError):
        """Sets the value of new_error attribute."""
        assert newError in [True, False], \
            'newError attribute must be True or False'
        return self._domInstance.setAttribute('new_error', str(newError))

    def setErrorID(self, errorId):
        """Sets the value of error_id attribute."""
        return self._domInstance.setAttribute('error_id', errorId)

    def setErrorTitle(self, errorTitle):
        """Sets the value of error_title attribute."""
        return self._domInstance.setAttribute('error_title', errorTitle)

    def setDescription(self, description):
        """Sets the value of description attribute."""
        return self._domInstance.setAttribute('description', description)

    def setAuthor(self, testAuthor):
        """Sets the name of tester"""
        return self._domInstance.setAttribute('author', testAuthor)

    def setTestTime(self, testTime):
        """Sets time when test was tested

        parameters

            testTime (string) time in application spesific string format

        """
        return self._domInstance.setAttribute('time', testTime)

    def setTestDate(self, testDate):
        """Sets time when test was tested

        parameters

            testDate (string) date in application spesific string format

        """
        return self._domInstance.setAttribute('date', testDate)

    def setLeakFound(self, leakFound):
        """Sets leak status of test case
        """
        assert leakFound in [True, False], \
            'leakFound attribute must be True or False'
        return self._domInstance.setAttribute('leak_found', str(leakFound))

    def setLeakFile(self, leakFiles=[]):
        """Sets memory leak file

        parameters

            leakFiles (list) path to memory leak files or empty list.
        """

        if leakFiles:
                self._domInstance.setAttribute('leak_file', leakFiles)
                return True
        else:
            testCaseNode = self.getParent()
            reportFolder = self._testSetModel.getReportFolder()

            mustiLogFile = 'MustiLog%s.txt' % \
                    filterValidFilename(testCaseNode.getName().replace(' ', ''))
            leakFile = os.path.join('musti_logs', mustiLogFile)
            leakPath = os.path.join(reportFolder, leakFile)

            if os.path.isfile(leakPath):
                self._domInstance.setAttribute('leak_file', leakFile)
                return True
            else:
                self._domInstance.setAttribute('leak_file', '')
                return False

    def isOpen(self):
        """Overrides base node's isOpen method."""
        return False

    def setOpenStatus(self, status):
        """Overrides base node's setOpenStatus method."""
        assert 0, 'Illegal function call: setOpenStatus(%s) for ' \
                  'TestResultNode.' % status

    def deleteLeakFile(self):
        """ Deletes leak files from test case """
        leakFile = self.getLeakFile()
        reportFolder = self._testSetModel.getReportFolder()

        if leakFile:
            leakPath = os.path.join(reportFolder, leakFile)
            if os.path.isfile(leakPath):
                try:
                    os.remove(leakPath)
                    if os.path.isfile(leakPath):
                        raise OSError
                except OSError, err:
                    raise TestSetModelException(str(err))
                else:
                    self.setLeakFile()

# ============================================================================
class ART2TestScriptNode(TestSetNodeBase):
    """Class for art2testscript nodes."""
    def __init__(self, nodeInstance, testSetModel):
        """Initialize ART2TestScriptNode."""
        TestSetNodeBase.__init__(self, nodeInstance, testSetModel)

    def getName(self):
        """Returns nodeName."""
        return self._domInstance.getName()

    def getDirectory(self):
        """Gets the value of directory attribute."""
        return self._domInstance.getAttribute('directory')

    def getFile(self):
        """Gets the value of file attribute."""
        return self._domInstance.getAttribute('file')

    def getClass(self):
        """Gets the value of class attribute."""
        return self._domInstance.getAttribute('class')

    def getMethod(self):
        """Gets the value of method attribute."""
        return self._domInstance.getAttribute('method')

    def setDirectory(self, directory):
        """Sets the value of directory attribute."""
        return self._domInstance.setAttribute('directory', directory)

    def setFile(self, fileName):
        """Sets the value of file attribute."""
        return self._domInstance.setAttribute('file', fileName)

    def setClass(self, className):
        """Sets the value of class attribute."""
        return self._domInstance.setAttribute('class', className)

    def setMethod(self, method):
        """Sets the value of method attribute."""
        return self._domInstance.setAttribute('method', method)

    def getART2TestResults(self):
        """Returns child art2testresults as a list of ART2TestResultNode
           instances.
        """
        art2TestResultNodes = []

        for node in self._domInstance.findall('art2testresult'):
            art2TestResultNodes.append(ART2TestResultNode(node,
                                                          self._testSetModel))

        return art2TestResultNodes

    def removeART2TestResults(self):
        """Removes ART2TestResultNode instances.
        """
        for resultNode in self._domInstance.findall('art2testresult'):
            resultNode.parent().remove(resultNode)

    def isART2TestResult(self):
        """Returns True if test case has art2testscript nodes."""
        if self.getART2TestResults():
            return True
        else:
            return False

    def isOpen(self):
        """Overrides base node's isOpen method."""
        return False

    def setOpenStatus(self, status):
        """Overrides base node's setOpenStatus method."""
        assert 0, 'Illegal function call: setOpenStatus(%s) for ' \
                  'ART2TestScriptNode.' % status

    def createART2TestResult(self, resultFile = '', result= ''):
        """Creates new art2testresult node.

            Parameters
                resultFile      ART2 test result xml file
        """
        # make art2testresult xml element
        art2testresult = NodeUtils('art2testresult', True)
        art2testresult.setAttribute('report_file', resultFile)
        art2testresult.setAttribute('test_type', 'UI Test')
        art2testresult.setAttribute('result', result)
        # append it to art2testscript
        self._domInstance.append(art2testresult)

    def testScriptExists(self, isaTestPath):
        """Check if test script file exists and all necessary attributes are
           found.

           Parameters

                isaTestPath     isa_test path

           Returns True if test script exists, otherwise False.
        """
        scriptFound = False

        # check variables
        if self.getDirectory() and self.getFile() and \
           self.getClass() and self.getMethod():

            directory = self.getDirectory()
            # if '.' is not in directory path, it means that test case is from
            # isa_common_test
            # if this is the case, isa_common_test has to be added to path
            if '.' in directory:
                # replace '.' signs with '\\'
                directory = directory.replace('.', '\\')
            else:
                directory = os.path.join('isa_common_test', directory)

            # check that test script file exists
            if os.path.isfile(os.path.join(isaTestPath,
                                           directory,
                                           self.getFile() + '.py')):
                scriptFound = True

        return scriptFound

# ============================================================================
class ART2TestResultNode(TestSetNodeBase):
    """Class for art2testresult nodes."""
    def __init__(self, nodeInstance, testSetModel):
        """Initialize ART2TestResultNode."""
        TestSetNodeBase.__init__(self, nodeInstance, testSetModel)

    def isDetailedReportFile(self):
        """Check detailed report XML file existence."""
        reportPath = self.getDetailedReportPath()
        if os.path.isfile(reportPath):
            return True
        else:
            return False

    def getDetailedReportFileName(self):
        """Gets the value of report_file attribute."""
        return self._domInstance.getAttribute('report_file')

    def setDetailedReportFileName(self, reportFile):
        """Sets the value of report_file attribute."""
        return self._domInstance.setAttribute('report_file', reportFile)

    def getDetailedReportPath(self):
        """Get detailed report XML file path."""
        reportFile = self.getDetailedReportFileName()
        reportFolder = self._testSetModel.getReportFolder()
        reportPath = os.path.join(reportFolder, reportFile)

        return reportPath

    def getResult(self):
        """Gets the value of result attribute."""
        return self._domInstance.getAttribute('result')

    def getDetailedReport(self):
        """Updates class data variables from detailed report file.

           Parameters

                reportFolder     Absolute path for detailed report folder.
        """
        try:
            art2ReportDom = NodeUtils(self.getDetailedReportPath())
        except AssertionError, err:
            raise TestSetModelException(str(err))
        else:
            return ART2DetailedReportNode(art2ReportDom,
                                          self._testSetModel,
                                          self.getDetailedReportFileName())
    def setResult(self, result):
        """Sets the value of result attribute."""
        
        #Updates the parent statistics        
        
        return self._domInstance.setAttribute('result', result)
    
    def setTestType(self,testType):
        return self._domInstance.setAttribute('test_type', testType)
        
    def getTestType(self):
        """Gets the value of test_type attribute."""
        return self._domInstance.getAttribute('test_type')

# ============================================================================
class ART2DetailedReportNode(TestSetNodeBase):
    """Class for art2testresult nodes."""
    def __init__(self, nodeInstance, testSetModel, reportFile):
        """Initialize ART2TestResultNode."""
        self._reportFile = reportFile
        TestSetNodeBase.__init__(self, nodeInstance, testSetModel)

    def getAuthor(self):
        """Gets the value of author variable."""
        author = self._domInstance.getAttribute('author')

        return author or os.environ.get('USERNAME') or 'John Doe'

    def getTestTime(self):
        """Gets the value of self._testTime variable."""
        self._testTime = self._domInstance.getAttribute('time')

        return self._testTime or time.strftime("%H:%M:%S")

    def getTestDate(self):
        """Gets the value of testDate variable."""
        testDate = self._domInstance.getAttribute('date')

        return testDate or time.strftime("%Y-%m-%d")

    def getResult(self):
        """Gets the value of result variable."""
        testCaseDom = self._domInstance.find('/testreport/testcase')
        if testCaseDom:
            # get result from testcase
            result = testCaseDom.getAttribute('result')
        else:
            result = NO_RESULT

        return result or NO_RESULT

    def getFailReason(self):
        """Gets the value of failReason variable.
           # FIXME: support needed for multiple error reasons
        """
        testCaseDom = self._domInstance.find('/testreport/testcase')
        if testCaseDom:
            errorDomList = testCaseDom.findall('error')
            if errorDomList:
                for errorDom in errorDomList:
                    reason = errorDom.getAttribute('reason')
                    if not reason.startswith('Remote:'):
                        failReason = errorDom.getAttribute('reason')

                if not vars().has_key('failReason'):
                    failReason = errorDomList[0].getAttribute('reason')

            else:
                failReason = ''
        else:
            failReason = 'testcase element was not found from ' \
                         'detailed report!'

        return failReason

    def getWarnings(self):
        """Gets the value of warnings variable."""
        warnings = []

        warningDomList = self._domInstance.findall(\
                '/testreport/testcase/comment[@reason = "Warning!"]')
        for warningDom in warningDomList:
            warnings.append(warningDom['text'])

        return warnings

    def getGeneralWarnings(self):
        """Get possible general warnings."""
        generalWarnings = []

        warningsDomList = self._domInstance. \
                       findall('/testreport/general_warnings/warning')
        for warningDom in warningsDomList:
            generalWarnings.append(warningDom['text'])

        return generalWarnings

    def getDurations(self, phone = 'main'):
        """Gets the value of durationList variable."""
        durationList, stepList = [], []

        if phone == 'all':
            xpath = '//testcase/summary'
        elif phone == 'main':
            xpath = '/testreport/testcase/summary'
        elif phone == 'remote':
            xpath = '//remote/testcase/summary'

        for oSummary in self._domInstance.findall(xpath):
            name = oSummary.getAttribute('name')
            duration = oSummary.getAttribute('duration')
            stepList.append(name)
            durationList.append(duration)

        return stepList, durationList

    def getBitmapFiles(self):
        """Parse relative bimap paths from detailed report."""
        bitmapFiles = []

        # Parse error bitmap names.
        for oBitmap in \
            self._domInstance.findall('//summary/expect/display/bitmap[@name]'):
            bitmapFile = os.path.join('error bitmaps', oBitmap['name'])
            if bitmapFile not in bitmapFiles:
                bitmapFiles.append(bitmapFile)

        # Parse capture bitmap names.
        for oBitmap in \
            self._domInstance.findall('//summary/capture/bitmap[@name]'):
            bitmapFile = \
                os.path.join('captured bitmaps', oBitmap['name'])
            if bitmapFile not in bitmapFiles:
                bitmapFiles.append(bitmapFile)

        # Parse error bitmap names.
        for oBitmap in self._domInstance.findall('//bitmap[@error_name]'):
            bitmapFile = oBitmap['error_name']
            if bitmapFile not in bitmapFiles:
                bitmapFiles.append(bitmapFile)

        # Parse reference bitmap names.
        for oBitmap in self._domInstance.findall('//bitmap[@reference_name]'):
            bitmapFile = oBitmap['reference_name']
            if bitmapFile not in bitmapFiles:
                bitmapFiles.append(bitmapFile)

        return bitmapFiles

    def getXFiles(self, extendedInfo = False):
        """Gets the value of x-files."""
        xfFiles = []

        # Parse X-file names.
        for oXFile in self._domInstance.findall('//dump_files/x_file'):
            phone = oXFile.parent().getAttribute('phone')
            comment = oXFile.parent().getAttribute('comment')
            reason = oXFile.getAttribute('reason')
            # Append mulder file.
            mulder = oXFile.getAttribute('mulder')
            scully = oXFile.getAttribute('scully')
            if extendedInfo:
                xfFiles.append((mulder, scully, phone, comment, reason))
            else:
                for fileName in filter(lambda l: l, (mulder, scully)):
                    filePath = os.path.join('x_files', phone, fileName)
                    xfFiles.append(filePath)

        return xfFiles

    def getATHFiles(self, extendedInfo = False):
        """Gets the value of ath-files."""
        athFiles = []

        for oATHFile in self._domInstance.findall('//dump_files/ath_file'):
            phone = oATHFile.parent().getAttribute('phone')
            comment = oATHFile.parent().getAttribute('comment')
            fileName = oATHFile.getAttribute('name')
            filePath = os.path.join('ath_files', phone, fileName)
            if extendedInfo:
                athFiles.append((fileName, phone, comment))
            else:
                athFiles.append(filePath)

        return athFiles

    def getTraceFiles(self):
        """Gets the value of trace-files."""
        traceFiles = []

        for oTrace in self._domInstance.findall('//testcase[@trace]'):
            traceFile =  os.path.join('traces', oTrace['trace'])
            # Extend list with trace files.
            traceFiles.append(traceFile)

        return traceFiles

    def getMemoryFiles(self):
        """Gets the value of memory info files."""
        memFiles = []

        for oMemory in self._domInstance.findall('//testcase[@memory]'):
            memoryFile = os.path.join('memory', oMemory['memory'])
            # Extend list with memory files.
            memFiles.append(memoryFile)

        return memFiles

    def getVideoFiles(self):
        """Gets the value of video files."""
        videoFiles = []

        for oVideo in self._domInstance.findall('//testcase[@video]'):
            videoFile = os.path.join('camera', oVideo['video'])
            # Extend list with video files.
            videoFiles.append(videoFile)

        return videoFiles

    def getExternalFiles(self, fileMask = 255):
        """Gets detailed test report files(relative path(s)).

           Parameters

                reportFolder     Absolute path for detailed report folder.
        """
        fileList = []

        if fileMask & 1:
            # Parse bitmap names.
            fileList.extend(self.getBitmapFiles())
        if fileMask & 2:
            # Parse x-file names.
            fileList.extend(self.getXFiles())
        if fileMask & 4:
            # Parse ath-file names.
            fileList.extend(self.getATHFiles())
        if fileMask & 8:
            # Parse trace file names.
            fileList.extend(self.getTraceFiles())
        if fileMask & 16:
            # Parse memory file names.
            fileList.extend(self.getMemoryFiles())
        if fileMask & 32:
            # Parse video file names.
            fileList.extend(self.getVideoFiles())

        return fileList

    def removeDetailedTestReportFiles(self, fileMask = 255):
        """ Delete detailed report files.

        Parameters
            fileMask    Filetype filtering bitmask.
        """
        errorFiles = []
        reportFolder = self._testSetModel.getReportFolder()

        for reportFile in self.getExternalFiles(fileMask):
            reportPath = os.path.join(reportFolder, reportFile)
            try:
                os.remove(reportPath)
            except (OSError, WindowsError), err:
                #skip if 'No such file or directory' errors
                if err.errno != errno.ENOENT:
                    errorFiles.append(reportPath)

        # Remove detailed XML file.
        reportPath = os.path.join(reportFolder, self._reportFile)
        try:
            os.remove(reportPath)
        except (OSError, WindowsError), err:
            errorFiles.append(reportPath)

        return errorFiles

    def copyDetailedTestReportFiles(self, targetFolder, fileMask = 255):
        """ Delete detailed report files.

        Parameters
            targetFolder    Source folder where detailed report files are
                            copied from.
            fileMask        Filetype filtering bitmask.
        """
        sourceFolder = self._testSetModel.getReportFolder()

        # Copy ART2 common trace files.
        if fileMask & 8:
            traceFiles = []
            for phone in ('main', 'remote'):
                traceFile = os.path.join('traces', 'art2_traces_%s.xml' % phone)
                sourceTrace = os.path.join(sourceFolder, traceFile)
                targetTrace = os.path.join(targetFolder, traceFile)
                if os.path.isfile(sourceTrace) and not \
                   os.path.isfile(targetTrace):
                    traceFiles.append(traceFile)
            if traceFiles:
                self.__copyFiles(sourceFolder, targetFolder, traceFiles)

        #  Copy detailed report XML file.
        errorFiles, missingFiles = \
                self.__copyFiles(sourceFolder, targetFolder, self._reportFile)

        # Parse detailed report XML files for additional files and copy them.
        reportFiles = self.getExternalFiles(fileMask)
        errorFiles2, missingFiles2 = \
                self.__copyFiles(sourceFolder, targetFolder, reportFiles)

        return (errorFiles + errorFiles2), (missingFiles + missingFiles2)

    def __copyFiles(self, sourceFolder, targetFolder, reportFileList):
        """Copies selected files to a new location if location is different.

        Parameters
            sourceFolder    Source folder where detailed report files are
                            copied from.
            targetFolder    Target folder where detailed report files are
                            copied into.
            reportFileList  Relative paths of files in source folder.
        """
        errorFiles, missingFiles = [], []

        if isinstance(reportFileList, (str, unicode)):
            reportFileList = [reportFileList]

        # Check that locations are different.
        if (sourceFolder != targetFolder):
            # Loop through all files and copy them.
            for relPath in reportFileList:
                # Create absolute source and target paths.
                sourcePath = os.path.join(sourceFolder, relPath)
                targetPath = os.path.join(targetFolder, relPath)

                # Make sure target folder is created before file copying.
                newFolder = os.path.dirname(targetPath)
                if not os.path.isdir(newFolder):
                    os.makedirs(newFolder)

                if os.path.isfile(sourcePath):
                    try:
                        # Copy file.
                        shutil.copy2(sourcePath, targetPath)
                    except (IOError, WindowsError), err:
                        errorFiles.append(sourcePath)
                else:
                    missingFiles.append(sourcePath)

        return errorFiles, missingFiles
