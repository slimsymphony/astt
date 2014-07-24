# ============================================================================
#
#                       Marble Framework Test Runner
#
#@author: Risto Pakanen
# ============================================================================

import time, sys, os, types, socket
import random, string # for follower result filename
from copy import copy
from glob import glob

from System import GC, GCCollectionMode, Security, IO
from System.Threading import Thread
from System.Globalization import CultureInfo

import core
from core.testcase_exceptions import TestException
from core.testcase_exceptions import getCurrentExceptionReason
from core import testresult, phone
from core.test_set_model import NA
from utils.nodeutils import NodeUtils
from utils.file_utils import filterValidFilename


class MarbleTestRunner:
    """Test runner class that runs the tests and reports results.

    """
    def __init__(self):
        # variables for run hours functionality
        self.__startTimeForRunHours = 0
        self.__runHoursInSeconds = 0

        # njunit report instance
        self.__njunitTestSuites = None

        # test case data list (needed for njunit report)
        self.__testCaseData = []

        # test file data dict (needed for module importing/reloading)
        self.__testFileData = {}

        core.FW_conf['current_testcase'] = None

    def __collectGarbage(self):
        """Performs garbage collection."""
        GC.Collect()
        #GC.Collect(GC.MaxGeneration, GCCollectionMode.Optimized)
        GC.WaitForPendingFinalizers()

    def __getTcIdFromDocString(self, testClass, testMethod, filterWs = False):
        """Parse tcId from the test's docstring.

         The function digs out testcase id from docstring.
        """
        testMethod = getattr(testClass, testMethod)

        try:
            if not getattr(testMethod, '__doc__', None):
                return ''

            try:
                tcId = testMethod.__doc__.split('@tcId ')[1].split('\n')[0].strip()
            except IndexError:
                return ''

            if filterWs:
                rExpWS = re.compile(r'\s{2,}')
                tcId = rExpWS.sub(' ', tcId)

            return tcId
        finally:
            if testMethod:
                del testMethod

    def __convertTimeTaken(self, timeTaken):
        """Convert seconds to string or hour(s), minute(s) and second(s). """
        # to 3 decimals
        timeTaken = float("%.3f" % timeTaken)

        timeString, hoursFromDays = '', 0

        # hours
        # check if days have gone by
        if time.gmtime(timeTaken)[2] > 1:
            hoursFromDays = (time.gmtime(timeTaken)[2] - 1) * 24

        if time.gmtime(timeTaken)[3]:
            if hoursFromDays:
                timeString = str(time.gmtime(timeTaken)[3] + hoursFromDays) + ' h '
            else:
                timeString = str(time.gmtime(timeTaken)[3]) + ' h '

        # minutes
        if time.gmtime(timeTaken)[4]:
            timeString += str(time.gmtime(timeTaken)[4]) + ' m '
        # seconds
        if time.gmtime(timeTaken)[5]:
            timeString += str(time.gmtime(timeTaken)[5])
            # put decimals and 's'
            timeString += '.' + str(timeTaken).split('.')[1] + ' s'

        # milliseconds
        if timeString == '':
            timeString = str(timeTaken) + ' s'

        return timeString

    def __isXml(self, testData):
        """Checks if testData is valid xml or not.

            Returns 1 if testData is testset xml,
                    2 if testData is workflow xaml,
                    3 if testData is test file xml
                    False if it's not xml at all
        """
        returnValue = False

        if type(testData) == types.StringType and \
           (os.path.isfile(testData) or len(glob(testData)) >= 1):
            try:
                if len(glob(testData)) >= 1:
                    xmlNode = NodeUtils(glob(testData)[0])
                else:
                    xmlNode = NodeUtils(testData)
            except Exception, err:
                # this means that testData was not valid xml
                debug.out('Invalid xml: "%s", "%s"' % (testData, str(err)))
            else:
                # this means that testData was valid xml
                if xmlNode.getName() == 'testset':
                    # if testset node is found from xml, file is testset xml
                    returnValue = 1
                elif xmlNode.getName() in ['Sequence', 'TestSequenceActivity']:
                    # workflow xaml detected
                    returnValue = 2
                elif xmlNode.getName() == 'tests':
                    # if tests node is found from xml, file is test file xml
                    returnValue = 3
                else:
                    errorMessage = 'Invalid input xml given to Marble test runner!'
                    debug.err(errorMessage)

                    if core.FW_conf['cli_mode']:
                        self.__closeConnections()
                        raise SystemExit(errorMessage)
                    else:
                        raise AssertionError(errorMessage)
        elif len(testData) == 2:
            xamlFile, trackingEndpoint = testData
            if type(xamlFile) == types.StringType and os.path.isfile(xamlFile):
                try:
                    xmlNode = NodeUtils(xamlFile)
                except Exception, err:
                    # this means that testData was not valid xml
                    debug.err('Invalid xaml: "%s", "%s"' % (xamlFile, str(err)))
                else:
                    if xmlNode.getName() in ['Sequence', 'TestSequenceActivity']:
                        # workflow xaml detected
                        returnValue = 2
                    else:
                        errorMessage = 'Invalid xaml given to Marble test runner!'

                        if core.FW_conf['cli_mode']:
                            self.__closeConnections()
                            raise SystemExit(errorMessage)
                        else:
                            raise AssertionError(errorMessage)

        return returnValue

    def __isAsciiFile(self, testData):
        """Checks if testData is valid ascii file.

            Returns True if yes, False if not
        """
        if type(testData) == types.StringType and os.path.isfile(testData):
            return True
        else:
            return False

    def __repeatOrNot(self):
        """Returns whether we need to repeat or not.
           If there's no repeat, True will be returned once.
        """
        # run specific amount of hours
        if core.FW_conf['run_hours'] > 0:
            if not self.__startTimeForRunHours:
                self.__startTimeForRunHours = time.clock()

            if not self.__runHoursInSeconds:
                self.__runHoursInSeconds = \
                    core.FW_conf['run_hours'] * 60 * 60

            # calculate whether we have run long enough or not
            if time.clock() - self.__startTimeForRunHours >= self.__runHoursInSeconds:
                core.FW_conf['repeat_index'] = 0
                return False
            else:
                core.FW_conf['repeat_index'] += 1
                return True
        # either single test case run or repeat has been set
        else:
            core.FW_conf['repeat_index'] += 1

            if core.FW_conf['repeat_index'] > core.FW_conf['repeat']:
                core.FW_conf['repeat_index'] = 0
                return False
            elif core.FW_conf['should_stop']:
                core.FW_conf['should_stop'] = False
                return False
            # NOTE: This if is to detect shutdown sequence of Granite FW
            # (values in core.FW_conf dict are out of sync)
            #elif core.FW_conf['granite_server_activated'] and not core.FW_conf['connection'].objectId:
            #    return False
            else:
                return True

    def __quitBecauseOfMemoryFull(self):
        """Terminate test case execution because MemoryFull exception."""
        errorMessage = 'Memory full, terminating test execution!'
        debug.err(errorMessage)

        if core.FW_conf['cli_mode']:
            # close phone connetion
            if core.FW_conf['connection']:
                self.__closeConnections()

            sys.exit(1)
        else:
            # send error to Marble GUI
            core.FW_conf['com_int'].sendErrorMessage(errorMessage)

            # execute CMD_STOP event --> quit Marble Framework
            core.FW_conf['com_int'].connectionCreationOngoing = False
            core.FW_conf['com_int'].CMD_QUIT(None)

    def __importModule(self, directory, module):
        """Imports given module on the fly.

            Parameters

            directory           module directory path
            module              module to be imported
        """
        if not os.path.isdir(directory):
            errorString = 'Invalid test case directory "%s"' % directory
            debug.err(errorString)
            raise TestException(errorString)

        importedModule = None
        dirsToBeAppended = []

        try:
            # set test script directory to resources
            resources._setScriptFolder(directory)

            # test case directory and one directory above will be appended to sys.path
            dirsToBeAppended = [directory, os.path.split(directory)[0]]

            # put directories to sys.path if needed
            for tcDir in dirsToBeAppended:
                if not tcDir in sys.path:
                    sys.path.append(tcDir)

            # import the module
            importedModule = __import__(module, globals(), locals())
        except MemoryError:
            self.__quitBecauseOfMemoryFull()
        except Exception, importError:
            errorString = 'Unable to import module "%s" from "%s"!\n%s' % \
                          (module, directory, self.__getExceptionDetails(importError))
            debug.err(errorString)
            raise TestException(errorString)
        else:
            return importedModule
        finally:
            if importedModule:
                del importedModule

            for tcDir in dirsToBeAppended:
                # remove import directories from sys.path if needed
                if tcDir in sys.path:
                    sys.path.remove(tcDir)

    def __configureAndRun(self, testData, filter = None):
        """Configures test case(s) according to given test data and runs it/them.

            Parameters

            testData        test set xml or
                            test case info [tcDir, tcModule, tcClass, tcMethod, (tcId)] or
            filter          optional filter string (default = None)
        """
        while (self.__repeatOrNot()):
            # check whether test data is some supported xml
            xmlType = self.__isXml(testData)

            # test set xml
            if xmlType == 1:
                self.__runTestSet(testData, filter)
            # workflow xaml
            elif xmlType == 2:
                raise Exception('XAML EXECUTION NOT SUPPORTED ANYMORE!')
            # test file xml(s)
            elif xmlType == 3:
                self.__runTestFileXML(testData, filter)
            # test file list (ascii)
            elif self.__isAsciiFile(testData):
                self.__runTestAsciiFile(testData, filter)
            else:
                # execute single IronPython test script (given by GUI)
                self.__run(testData)

    def __runObject(self, followerController, testData, filter=None):
        """Runs given test case object and its test method

            Parameters

            followerController      follower instance from follower.py module
            testData                test case info [tcDir, tcModule, tcClass, tcMethod, tcId, tcDoc]

            Raises TestException from import or instance creation errors
        """
        # create test object
        classToBeExecuted = followerController.initializeTestCase(testData)

        # just return None if we should stop
        if core.FW_conf['should_stop']:
            core.FW_conf['should_stop'] = False
            return None

        assert testData and len(testData) in [6], \
            'Invalid testData received! %s' % len(testData)

        # store test case data for NJUNIT report
        self.__testCaseData = testData

        tcClass, tcSubArea, tcFreature, tcMethod, tcId, tcDoc = testData

        if not filter or (filter == tcId or filter in tcId):
            # save test result name for xml saving
            if core.FW_conf['test_result_name'] == '':
                # update test result name
                core.FW_conf['test_result_name'] = filterValidFilename(tcId)

            # create test case instance
            try:
                testInstance = classToBeExecuted(tcMethod, tcId)
                core.FW_conf['current_testcase'] = testInstance
            except Exception, classError:
                raise TestException('Unable to create test case class instance "%s, %s"!\n%s' % \
                                    (tcMethod, tcId, self.__getExceptionDetails(classError)))
            finally:
                del classToBeExecuted

            # variable for raising SystemExit from try <-> finally block
            raiseSystemExit = False
            try:
                try:

                    # record start time
                    startTime = time.time()

                    # call test case instance to start execution
                    testInstance()

                except SystemExit:
                    # put raiseSystemExit flag to True so that SystemExit
                    # can be raised in finally:
                    raiseSystemExit = True
                except Exception, e:
                    debug.exception(e)
                    raise
            finally:
                # raise SystemExit if needed
                core.FW_conf['current_testcase'] = None
                if raiseSystemExit:
                    raise

                stopTime = time.time()
                timeTaken = float(stopTime - startTime)

                debug.brf("%s" % ('=' * 80))
                timeString = self.__convertTimeTaken(timeTaken)
                debug.brf("Ran test case in %s" % timeString)

                debug.dumpMemoryUsage()

                result = core.FW_conf['connection'].getResult()

                # add test case result to NJUNIT report
                self.__addTestCaseNjunitNode(result, testInstance.tcId, timeString, testInstance)

                # save result
                if result:
                    result.setDuration(timeString)
                    result.save()

                    # clear test result name for next test case
                    core.FW_conf['test_result_name'] = ''

                    # destroy result instance
                    del result
                    core.FW_conf['connection'].setResult(None)

                # destroy test case instance
                if testInstance:
                    del testInstance
                #if classToBeExecuted:
                #    del classToBeExecuted

                core.FW_conf['should_stop'] = False

                # perform garbage collection in the end of each test case run
                self.__collectGarbage()
                # create a new result for phone after garbage collection
                core.FW_conf['connection']._makeResult()
        else:
            # test case won't be executed --> delete all instances
            if importedModule:
                del importedModule

            if classToBeExecuted:
                del classToBeExecuted

    def __run(self, testData, filter = None, relativeToPath = ""):
        """Runs IronPython test case

            Parameters

            testData            test case data list
                                    tcDir
                                    tcModule
                                    tcClass
                                    tcMethod
                                    tcId    (optional)
            filter              optional filter string (default = None)
            relativeToPath      path to which test case directory relates to (default = "")

            Raises TestException from import or instance creation errors
        """
        # set culture to 'en-US' so that .NET modules will always use 'en-US' culture instead of machine culture.
        cultureInfo = CultureInfo('en-US')
        Thread.CurrentThread.CurrentCulture = cultureInfo
        Thread.CurrentThread.CurrentUICulture = cultureInfo

        # just return None if we should stop
        if core.FW_conf['should_stop']:
            core.FW_conf['should_stop'] = False
            return None

        if len(testData) < 4:
            errorMessage = 'Invalid testData "%s" received!' % testData

            if core.FW_conf['cli_mode']:
                self.__closeConnections()
                raise SystemExit(errorMessage)
            else:
                raise AssertionError(errorMessage)

        importedModule, classToBeExecuted = None, None

        # store test case data for NJUNIT report
        self.__testCaseData = testData

        # get test data parameters
        tcDir    =  testData[0]
        tcModule =  testData[1]
        tcClass  =  testData[2]
        tcMethod =  testData[3]

        # tcId is optional
        if len(testData) >= 5:
            tcId = testData[4]
        else:
            tcId = None

        # update tcDir if related to path has been given
        if relativeToPath:
            tcDir = os.path.normpath(os.path.join(relativeToPath, tcDir))

        testScriptFile = os.path.abspath(os.path.normpath(os.path.join(tcDir, tcModule) + '.py'))
        lastWriteTime = IO.File.GetLastWriteTime(testScriptFile).ToString()

        # check that do we need to unload test script from memory
        # either module by the same name but different file path or test script has actually been updated
        if (self.__testFileData.has_key(tcModule) and \
           sys.modules.has_key(tcModule)) and \
           (self.__testFileData[tcModule][0] != testScriptFile or \
           self.__testFileData[tcModule][1] != lastWriteTime):
            del self.__testFileData[tcModule]
            del sys.modules[tcModule]

        reloadedModules = []

        # check do we need to unload test files from memory
        # NOTE: iterating copied dict so that we can modify original
        for moduleName, fileData in copy(self.__testFileData).iteritems():
            # if file has been modified, delete data from dict and unload module from memory
            if (not os.path.isfile(fileData[0]) or \
               not sys.modules.has_key(moduleName)) or \
               (os.path.isfile(fileData[0]) and \
               IO.File.GetLastWriteTime(fileData[0]).ToString() != fileData[1]):
                del self.__testFileData[moduleName]

                if sys.modules.has_key(moduleName):
                    reload(sys.modules[moduleName])
                    reloadedModules.append(moduleName)

        # import specific file on the fly
        importedModule = self.__importModule(tcDir, tcModule)

        # reload test script if reloaded module has been imported from test script
        for reloadedModule in reloadedModules:
            if reloadedModule in vars(importedModule):
                reload(importedModule)
                break

        # store imported test file data into dict
        # NOTE: IronPython and Framework files are not handled
        for key in sys.modules.keys():
            if not self.__testFileData.has_key(key) and \
               sys.modules[key] and \
               hasattr(sys.modules[key],'__file__') and \
               not 'IronPython' in sys.modules[key].__file__ and \
               not 'marble\\framework' in sys.modules[key].__file__ and \
               os.path.isfile(sys.modules[key].__file__):
                self.__testFileData[key] = (os.path.normpath(sys.modules[key].__file__),
                                            IO.File.GetLastWriteTime(sys.modules[key].__file__).ToString())

        try:
            # get class from the imported module
            classToBeExecuted = getattr(importedModule, tcClass)
        except Exception, classError:
            errorString = 'Unable to get test case class "%s" from "%s"!\n%s' % \
                          (tcClass, importedModule, self.__getExceptionDetails(classError))
            debug.err(errorString)
            raise TestException(errorString)
        finally:
            del importedModule

        try:
            if not tcId:
                # get tcId from doc string if needed
                tcId = self.__getTcIdFromDocString(classToBeExecuted, tcMethod)
        except Exception, classError:
            errorString = 'Unable to find tcId from test case class "%s"!\n%s' % \
                          (tcMethod, self.__getExceptionDetails(classError))
            debug.err(errorString)
            raise TestException(errorString)

        if not filter or (filter == tcId or filter in tcId):
            # save test result name for xml saving
            if core.FW_conf['test_result_name'] == '':
                # update test result name
                if core.FW_conf['cli_mode']:
                    # filter out not valid characters in CLI mode
                    core.FW_conf['test_result_name'] = filterValidFilename(tcId)
                else:
                    core.FW_conf['test_result_name'] = tcId

            # create test case instance
            try:
                testInstance = classToBeExecuted(tcMethod, tcId)
                core.FW_conf['current_testcase'] = testInstance
            except MemoryError:
                self.__quitBecauseOfMemoryFull()
            except Exception, classError:
                errorString = 'Unable to create test case class instance "%s, %s"!\n%s' % \
                              (tcMethod, tcId, self.__getExceptionDetails(classError))
                debug.err(errorString)
                raise TestException(errorString)
            finally:
                del classToBeExecuted

            # variable for raising SystemExit from try <-> finally block
            raiseSystemExit = False

            try:
                try:
                    resultForCLI = None

                    if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
                        # set random chars after tcId in followers, otherwise results might be overriden
                        tcId = '%s_%s' % (tcId, ''.join(random.choice(string.ascii_uppercase + string.digits) for x in range(6)))

                        tc_attrs = (tcClass, testInstance.subarea , testInstance.feature, tcMethod, tcId, testInstance.description())
                        debug.brf('Initializing case in followers: %s' % tcId)
                        core.FW_conf['leader'].InitializeTestCase(tc_attrs)

                    # record start time
                    startTime = time.time()

                    # call test case instance to start execution
                    testInstance()
                except MemoryError:
                    self.__quitBecauseOfMemoryFull()
                except SystemExit:
                    # put raiseSystemExit flag to True so that SystemExit
                    # can be raised in finally:
                    raiseSystemExit = True
                except Exception, e:
                    debug.exception(e)
                    raise
            finally:
                core.FW_conf['current_testcase'] = None
                # raise SystemExit if needed
                if raiseSystemExit:
                    if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
                        core.FW_conf['leader'].AbortCurrentTestCase()
                    raise

                stopTime = time.time()
                timeTaken = float(stopTime - startTime)

                debug.brf("%s" % ('=' * 80))
                timeString = self.__convertTimeTaken(timeTaken)
                debug.brf("Ran test case in %s" % timeString)

                debug.dumpMemoryUsage()

                result = core.FW_conf['connection'].getResult()

                # add test case result to NJUNIT report
                self.__addTestCaseNjunitNode(result, core.FW_conf['test_result_name'], timeString, testInstance)

                # save result
                if result:
                    result.setDuration(timeString)
                    result.save()

                    if core.FW_conf['cli_mode']:
                        productNode = result.report.find("//product")
                        resultForCLI = (result.getResult(), productNode and productNode.getAttribute("name") or 'unknown')

                    # remove test result link from Phone-instances
                    if core.FW_conf['remote_connection']:
                        core.FW_conf['remote_connection'].setResult(None)

                    # destroy result instance
                    del result
                    core.FW_conf['connection'].setResult(None) # this will also delete the result from phone

                # clear test result name for next test case
                core.FW_conf['test_result_name'] = ''

                # destroy test case instance
                if testInstance:
                    del testInstance

                core.FW_conf['should_stop'] = False

                # perform garbage collection in the end of each test case run
                self.__collectGarbage()

                # create a new result after garbage collection
                core.FW_conf['connection']._makeResult()

                return resultForCLI
        else:
            # test case won't be executed --> delete instance
            if classToBeExecuted:
                del classToBeExecuted

    def __runTestSet(self, testSetFilePath, filter):
        """Runs test cases from test set file

            Parameters

            testSetFilePath         path to test set file (.testset)
            filter                  test case filter string
        """
        debug.dumpMemoryUsage()
        # write main NJUNIT node to report
        self.__addMainNjunitNode(testSetFilePath)

        # test cases from test set xml file
        testSetNode = NodeUtils(testSetFilePath)
        debug.dumpMemoryUsage()

        # variable for test script node search
        scriptNodeName = ''

        if testSetNode.find('//testscript'):
            pass
        elif testSetNode.find('//ctt_test'):
            self.__runCTTTestSet(testSetNode, filter)
        else:
            errorMessage = 'No test scripts found from given test set!'

            if core.FW_conf['cli_mode']:
                self.__closeConnections()
                raise SystemExit(errorMessage)
            else:
                raise AssertionError(errorMessage)

        for testCaseNode in testSetNode.findall('//testscript'):
            # run each test case from xml
            testCaseInstance = None

            # get the test case file name and directory
            testCaseFile = testCaseNode.getAttribute('file')
            testCaseDir = testCaseNode.getAttribute('directory')

            # get whether importing must be relative to test set or not
            if testCaseNode.getAttribute('relativetotestset'):
                relativeToPath = os.path.dirname(testSetFilePath)
            else:
                relativeToPath = ""

            result = None

            try:
                if testCaseNode.getAttribute('method') != '':
                    result = self.__run(\
                        [testCaseDir,
                            testCaseFile,
                            testCaseNode.getAttribute('class'),
                            testCaseNode.getAttribute('method')],
                            filter, relativeToPath)
            except Exception, err:
                # put failure to njunit test report and continue to next test case
                # NOTE: We don't have test case instance, thus test result instance is also missing here!
                self.__addTestCaseNjunitNode(str(err), testCaseNode.getAttribute('method'), '0')

            if result:
                resultNode = NodeUtils("testresult",True)
                resultNode.setAttribute("result",result[0])
                resultNode.setAttribute("time",time.strftime("%m/%d/%Y %I:%M:%S %p"))
                resultNode.setAttribute("author",Security.Principal.WindowsIdentity.GetCurrent().Name.split("\\")[-1])
                resultNode.setAttribute("isblackboxmodeon",core.FW_conf["blackbox_enabled"])
                resultNode.setAttribute("product",result[1])
                #resultNode.setAttribute("reportpath","")
                #resultNode.setAttribute("errorreason","")
                #resultNode.setAttribute("errortraceback","")
                #result="" time="1/16/2013 9:38:48 AM" author="" isblackboxmodeon="false" reportpath="" errorreason="" errortraceback=""
                testCaseNode.parent().append(resultNode)
                testSetNode.save(testSetFilePath)

    def __runTestFileXML(self, testFileXmlPath, filter):
        """Runs test cases from test file xml(s)

            Parameters

            testFileXmlPath         path to test file xml(s) (glob syntax)
            filter                  test case filter string
        """
        # write main NJUNIT node to report
        self.__addMainNjunitNode(testFileXmlPath)

        # loop test file xmls with glob
        for testFileXml in glob(testFileXmlPath):
            try:
                # execute test cases from test file list xml file
                testsNode = NodeUtils(testFileXml)
            except Exception, err:
                debug.err('Error when reading "%s": %s' % (testFileXml, str(err)))
                continue

            for testNode in testsNode.findall('//test'):
                testFilePath = testNode.getAttribute('path')

                # skip invalid file paths
                if not testFilePath or not os.path.isfile(testFilePath):
                    debug.err('Invalid file path: "%s"' % testFilePath)
                    continue

                testCaseDir, testCaseFile = os.path.split(testFilePath)

                # run IronPython test(s)
                if testFilePath.endswith('.py'):
                    # split test case directory and file
                    testCaseDir, testCaseFile = os.path.split(testFilePath)
                    # .py suffix is not needed
                    testCaseFile = testCaseFile.split('.py')[0]

                    # import specific file on the fly
                    try:
                        importedModule = self.__importModule(testCaseDir, testCaseFile)
                    except Exception, importError:
                        errorString = 'Error "%s" when importing module "%s" from "%s"' % (str(importError), testCaseFile, testCaseDir)
                        debug.err(errorString)

                        # in command line mode we want to put error to njunit report
                        if core.FW_conf['cli_mode']:
                            self.__addTestCaseNjunitNode(errorString, testCaseFile, '0')

                        # continue to next line
                        continue

                    # loop through all modules from imported module
                    for module in dir(importedModule):
                        # we are not interested in possible internal methods
                        if not module.startswith('__'):
                            try:
                                moduleItem = getattr(importedModule, module)
                            except Exception, err:
                                debug.err('Error when getting test case class "%s" from "%s"' % (module, importedModule))

                                if importedModule:
                                    del importedModule

                                # continue to next possible test case
                                continue

                            # if module item has file name in it --> we found the test case class
                            if testCaseFile in str(moduleItem):
                                for item in dir(moduleItem):
                                    try:
                                        # if item is a method with @tcId --> it's Marble test case method
                                        tcId = self.__getTcIdFromDocString(moduleItem, item)
                                    except Exception, err:
                                        tcId = None
                                    else:
                                        # run test case if tcId was found and it matches with possible filter
                                        if tcId and (not filter or (filter == tcId or filter in tcId)):
                                            # store test case data for NJUNIT report
                                            self.__testCaseData = [testCaseDir, testCaseFile, module, item, tcId]

                                            try:
                                                # execute test case
                                                self.__run([testCaseDir, testCaseFile, module, item, tcId], filter)
                                            except Exception, err:
                                                # put failure to njunit test report and continue to next test case
                                                # NOTE: We don't have test case instance, thus test result instance is also missing here!
                                                self.__addTestCaseNjunitNode(str(err), filterValidFilename(tcId), '0')
                # run given test set
                elif (testFilePath.endswith('.testset')):
                    self.__runTestSet(testFilePath, filter)

    def __runTestAsciiFile(self, testAsciiFilePath, filter):
        """Runs test cases from ascii test file. Supports only IronPython scripts.

            Parameters

            testAsciiFilePath       path to test ascii file
            filter                  test case filter string
        """
        # write main NJUNIT node to report
        self.__addMainNjunitNode(testAsciiFilePath)

        # execute test cases from test file list ascii file
        tcListFile = open(testAsciiFilePath)

        for line in tcListFile:
            # strip end of line mark away
            line = line.strip()

            # skip invalid file paths
            if not os.path.isfile(line):
                debug.err('Invalid file path: "%s"' % line)
                continue

            # split test case directory and file
            tcDir, fileName = os.path.split(line)
            # .py suffix is not needed
            fileName = fileName.split('.py')[0]

            # import specific file on the fly
            try:
                importedModule = self.__importModule(tcDir, fileName)
            except Exception, importError:
                errorString = 'Error "%s" when importing module "%s" from "%s"' % (str(importError), fileName, tcDir)
                debug.err(errorString)

                # in command line mode we want to put error to njunit report
                if core.FW_conf['cli_mode']:
                    self.__addTestCaseNjunitNode(errorString, fileName, '0')

                # continue to next line
                continue

            # loop through all modules from imported module
            for module in dir(importedModule):
                # we are not interested in possible internal methods
                if not module.startswith('__'):
                    try:
                        moduleItem = getattr(importedModule, module)
                    except Exception, err:
                        debug.err('Error when getting test case class "%s" from "%s"' % (module, importedModule))

                        if importedModule:
                            del importedModule

                        # continue to next possible test case
                        continue

                    # if module item has filename in it --> we found the test case class
                    if fileName in str(moduleItem):
                        for item in dir(moduleItem):
                            try:
                                # if item is a method with @tcId --> it's Marble test case method
                                tcId = self.__getTcIdFromDocString(moduleItem, item)
                            except Exception, err:
                                tcId = None
                            else:
                                # run test case if tcId was found and it matches with possible filter
                                if tcId and (not filter or (filter == tcId or filter in tcId)):
                                    # store test case data for NJUNIT report
                                    self.__testCaseData = [tcDir, fileName, module, item, tcId]

                                    try:
                                        # execute test case
                                        self.__run([tcDir, fileName, module, item, tcId], filter)
                                    except Exception, err:
                                        # put failure to njunit test report and continue to next test case
                                        # NOTE: We don't have test case instance, thus test result instance is also missing here!
                                        self.__addTestCaseNjunitNode(str(err), filterValidFilename(tcId), '0')
        tcListFile.close()

    def addEmptyNjunitReport(self):
        """ Adds empty NJUNIT report

            This is needed if empty test set is generated from QC due to load balancing in CI

        """
        self.__addMainNjunitNode('NotFound')

    def __addMainNjunitNode(self, testData):
        """Add main and testsuite nodes for NJUNIT report, which is generated for C.I in CLI mode.

            Parameters

            testData        test set xml
        """
        if core.FW_conf['cli_mode'] and not self.__njunitTestSuites:
            self.__njunitTestSuites = NodeUtils('testsuites', True)
            self.__njunitTestSuites.setAttribute('name', os.path.split(testData)[-1])

    def __addTestCaseNjunitNode(self, result, testCaseName, timeString, testCaseInstance = None):
        """Add test case node to NJUNIT report, which is generated for C.I in CLI mode.

            Parameters

            result              test result instance or error string
            testCaseName        test case name
            timeString          test execution time in string
            testCaseInstance    test case instance (if available)
        """
        if core.FW_conf['cli_mode'] and self.__njunitTestSuites:
            # add test case information
            testCaseNode = NodeUtils('testcase', True)

            # IronPython test case data is in self.__testCaseData
            if self.__testCaseData:
                testCaseNode.setAttribute('script', '.'.join(self.__testCaseData[:4]))

            # if we have test case instance, set feature as classname
            if testCaseInstance:
                testCaseNode.setAttribute('classname', testCaseInstance.feature)
            else:
                testCaseNode.setAttribute('classname', 'unknown')

            testCaseNode.setAttribute('name', testCaseName)
            testCaseNode.setAttribute('time', timeString)

            # add date and start/stop time from test result
            if isinstance(result, testresult.MarbleTestResult) and result.tcReport != None:
                for attr in ['date', 'start_time', 'stop_time']:
                    testCaseNode.setAttribute(attr, result.tcReport.getAttribute(attr))

            # add failure node if test case failed
            if isinstance(result, testresult.MarbleTestResult) and not result.wasSuccessful():
                testResult = result.getResult()

                # failure node is named according to result
                if testResult == NA:
                    failureNode = NodeUtils('na', True)
                else:
                    failureNode = NodeUtils('failure', True)

                errorNode = result.getError()
                failureNode.setAttribute('message', errorNode['reason'])
                failureNode.setAttribute('detail', errorNode['text'])
                testCaseNode.append(failureNode)
            elif type(result) == types.StringType:
                failureNode = NodeUtils('failure', True)
                failureNode.setAttribute('message', 'Test execution failure')
                failureNode.setAttribute('detail', result)
                testCaseNode.append(failureNode)

            # use existing testsuite node if found
            if testCaseInstance and self.__njunitTestSuites.find('//testsuite[@name="%s"]' % testCaseInstance.subarea):
                testSuite = self.__njunitTestSuites.find('//testsuite[@name="%s"]' % testCaseInstance.subarea)

                # append test case to testsuite node
                testSuite.append(testCaseNode)
            # create new testsuite node
            else:
                testSuite = NodeUtils('testsuite', True)
                if not testCaseInstance:
                    testSuite.setAttribute('name', 'unknown')
                else:
                    testSuite.setAttribute('name', testCaseInstance.subarea)

                deviceInfo = core.FW_conf['connection'].deviceInfo(doNotReport = True)
                # add properties node
                propertiesNode = NodeUtils('properties', True)
                propertiesNode.setAttribute('organization', 'MP') # FIXME: Hard-coded
                propertiesNode.setAttribute('testlevel', 'System')
                propertiesNode.setAttribute('testtool', 'Marble')
                propertiesNode.setAttribute('target',
                    (core.FW_conf['connection']._tab._tabConn and core.FW_conf['connection']._tab._tabConn.IsEmulator) and 'EMULATOR' or 'HW')
                propertiesNode.setAttribute('product',
                    deviceInfo.has_key('ro.build.product') and deviceInfo['ro.build.product'] or 'unknown')
                propertiesNode.setAttribute('hostname', socket.gethostname())
                testSuite.append(propertiesNode)

                # append test case to testsuite node
                testSuite.append(testCaseNode)

                # append testsuite to testsuites
                self.__njunitTestSuites.append(testSuite)

            # save current status to disk
            self.saveNjunitReport()

    def saveNjunitReport(self):
        """Saves Njunit report to disk."""
        if self.__njunitTestSuites:
            njunitReportDir = os.path.join(core.FW_conf['test_result_dir'], 'njunit')
            # create directory for njunit report if it doesn't exist
            if not os.path.isdir(njunitReportDir):
                os.mkdir(njunitReportDir)

            self.__njunitTestSuites.save(os.path.join(njunitReportDir, 'Marble_njunit.xml'))

    def __getExceptionDetails(self, exception):
        """Digs outs details from given exception and returns error string."""
        errorString = '%sError: "%s"\n' % (4*' ', getCurrentExceptionReason())

        try:
            errorString += '%sFile: "%s"\n' % (4*' ', exception.filename)
            errorString += '%sCode block: "%s"\n' % (4*' ', exception.text.strip())
            errorString += '%sLine number: %s' % (4*' ', exception.lineno)
        except:
            pass

        return errorString

    def __closeConnections(self):
        """Close main and possible remote phone connections."""
        # Close remote connections before closing main connection. Closing main connection
        # calls Dispose for connection manager!
        for remote in core.FW_conf['remote_connection']:
            remote.closeConnection(True)
        core.FW_conf['connection'].closeConnection(True)

    def run(self, testData, filter = None):
        """Runs test case(s) according to given test data.

            Parameters

            testData        test set xml or
                            test case info [tcDir, tcModule, tcClass, tcMethod, (tcId)] or
                            ascii file containing the list of test cases
            filter          optional filter string (default = None)
        """
        self.__configureAndRun(testData, filter)

    def runDisplayCapture(self):
        """Runs display capture test case."""
        # set debug level to minimun to save time
        debug.setLevel(1)

        # create test result and stub needed attributes
        result = core.FW_conf['connection'].getResult()
        core.FW_conf['connection'].subarea = 'Display'
        core.FW_conf['connection'].feature = 'Capture'
        core.FW_conf['connection'].tcId = 'phone_display_capture'
        result.tcReport = NodeUtils('testcase', True)

        try:
            core.FW_conf['connection'].capture()
        finally:
            result.stopTest(core.FW_conf['connection'])
            # save result and destroy it
            result.save()
            del result
            core.FW_conf['connection'].setResult(None)

        core.FW_conf['connection']._makeResult()

        # reset debug level to setting value
        debug.setLevel(core.FW_conf['settings'].TestRun.DebugLevel)

    def runMainMenuStabilityInLoop(self):
        """Runs main menu stability test case in loop."""
        while True:
            self.__run(\
                [os.path.join(core.FW_conf['startup_path'], '..', 'test_scripts', 'tool_stability'), \
                'tool_stability', 'ToolStability', 'mainMenuStability', 'Main menu stability'])

