import sys, os, os.path, re, time, clr
import types
import traceback, string
clr.AddReference('System')
from System import DateTime

# Marble module imports
import core
from core.test_set_model import NO_RESULT, NA
from core.testcase_exceptions import TestException, \
        getCurrentExceptionReason, getReasonAndStackTraceFromCurrentException
from utils.nodeutils import NodeUtils
from utils import file_utils


class MarbleTestResultElement:

    def __init__(self):
        self.timestamp = time.time()

    def toxmlelement(self, element):
        """Get an XML element version of the object.

        Returned element must be suitable for test result DOM append.
        """
        try:
            oElement = NodeUtils(str(element), True)
        except:
            oElement = NodeUtils(repr(element), True)

        return oElement

# ============================================================================
#   3.2     MarbleTestResult class
# ----------------------------------------------------------------------------
class MarbleTestResult(object):
    """A test result class that can print formatted results to the stream.

    """
    def __init__(self):
        self.na = []
        self._testCounter = 0
        self.match_id = re.compile('(.*?)(;unknown$|;to be scripted$|;manual$|$)').match
        self._allTest = 0

        self.report = NodeUtils('testreport', True)
        self.tcReport = NodeUtils('testcase', True)

        self.__testStepNameIndex = 1
        self.traceFile = None
        self.memoryFile = None

        # self.duration tells how many seconds test suite execution
        # has taken this far
        self.duration = 0.0
        self.testStepCount = 0
        self.remotePhoneExecution = False

        # for performance report
        self.currentTestStep = None

    def setCurrentTestStep(self, testStepName):
        """Saves current test step name to self."""
        self.clearCurrentTestStep()
        self.currentTestStep = testStepName
        
        #if core.FW_conf['settings'].TestRun.PerformanceTesting:
        #    with core.FW_conf['connection'].perfReportLock:
        #        core.FW_conf['connection'].testStepPerfNode = NodeUtils('test_step_perf', True)
        #        core.FW_conf['connection'].testStepPerfNode.setAttribute('name', testStepName)

    def clearCurrentTestStep(self):
        """Clears current test step name from self. Creates performance test report if needed."""
        self.currentTestStep = None

        #if core.FW_conf['settings'].TestRun.PerformanceTesting:
        #    # calculate average before returning
        #    screenFpsCount = 0
        #    commonFpsCount = 0
        #    sumOfScreenFps = 0
        #    sumOfCommonFps = 0

        #    with core.FW_conf['connection'].perfReportLock:
        #        if core.FW_conf['connection'].perfReport and core.FW_conf['connection'].testStepPerfNode:                
        #            # clone node so that measuring can continue in the background
        #            testStepPerfNode = core.FW_conf['connection'].testStepPerfNode.clone()
        #            core.FW_conf['connection'].testStepPerfNode = None

        #            firstTimeStamp = 0
        #            lastTimeStamp = 0

        #            for fpsNode in testStepPerfNode.findall('//screen_update'):
        #                #if int(fpsNode.getAttribute('width')) >= core.FW_conf['settings'].TestRun.MinimumWidthInFpsMeasuring:
        #                if int(fpsNode.getAttribute('width')) >= 240:
        #                    screenFpsCount += 1
        #                    sumOfScreenFps += int(fpsNode.getAttribute('fps'))

        #                if firstTimeStamp == 0:
        #                    firstTimeStamp = int(fpsNode.getAttribute('time_stamp'))
        #                else:
        #                    lastTimeStamp = int(fpsNode.getAttribute('time_stamp'))

        #                commonFpsCount += 1
        #                sumOfCommonFps += int(fpsNode.getAttribute('fps'))

        #            if commonFpsCount:
        #                testStepPerfNode.setAttribute('average_fps', screenFpsCount and (sumOfScreenFps / screenFpsCount) or 0)
        #                testStepPerfNode.setAttribute('common_average_fps', commonFpsCount and (sumOfCommonFps / commonFpsCount) or 0)
        #                testStepPerfNode.setAttribute('duration', lastTimeStamp and lastTimeStamp - firstTimeStamp or 0)
                                
        #                core.FW_conf['connection'].perfReport.append(testStepPerfNode.clone())

        #                # append also to test execution report
        #                self.tcReport.append(testStepPerfNode.clone())

    def setProductDetails(self, details):
        """Set necessary product details"""
        self.report.setAttribute('author', os.environ.get('USERNAME') or '')

        product = NodeUtils('product', True)
        product.setAttribute('name', details['name'])
        product.setAttribute('main_display', details['main_display'])
        product.setAttribute('imei', details['imei'])
        product.setAttribute('imsi1', details['imsi1'])
        product.setAttribute('imsi2', details['imsi2'])
        product.setAttribute('sim1', details['sim1'])
        product.setAttribute('sim2', details['sim2'])
        product.setAttribute('fw_version', details['fw_version'])
        product.setAttribute('rmcode', details['rmcode'])
        product.setAttribute('lang', details['lang'])
        product.setAttribute('connection', details['connection'])

        for verType in ['sw', 'hw', 'marble server']:
            version = NodeUtils('version', True)
            version.setAttribute('type', verType)
            version['text'] = details[verType].strip('\0')
            product.append(version)
            
        self.report.append(product)

    def setTestSettingDetails(self, settings):
        """Set necessary test setting details"""
        settingElement = NodeUtils('settings', True)
        settingNames = settings.keys()
        settingNames.sort()
        for setting in settingNames:
            settingTag = NodeUtils('setting', True)
            settingTag.setAttribute('name', setting)
            if isinstance(settings[setting], (str, unicode)):
                settingTag['text'] = settings[setting]
            else:
                settingTag['text'] =  repr(settings[setting])
            settingElement.append(settingTag)

        self.report.append(settingElement)

    def setTestIgnoreflagsDetails(self, ignoreFlags):
        """Set necessary test ignore flags details"""
        ignoreflagslement = NodeUtils('ignore_flags', True)
        ignoreFlagNames = ignoreFlags.keys()
        ignoreFlagNames.sort()

        for ignoreFlag in ignoreFlagNames:
            ignoreFlagTag = NodeUtils('ignore_flag', True)
            ignoreFlagTag.setAttribute('name', ignoreFlag)
            value = ignoreFlags.get(ignoreFlag)

            if not isinstance(value, bool):
                ignoreFlagTag.setAttribute('state', 'True')
                value = isinstance(value, list) and ', '.join(value) or value
                ignoreFlagTag.setAttribute('text', value)
            else:
                ignoreFlagTag.setAttribute('state', value and 'True' or 'False')

            ignoreflagslement.append(ignoreFlagTag)

        self.report.append(ignoreflagslement)

    def setDuration(self, sec):
        """ Sets test suite total execution time variable """
        self.duration = sec

    def addProcInst(self):
        """ Creates / adds processing instruction fields. """
        # Create processing instruction fields.
        self.report.addProcInst("xml-stylesheet",
                                "type='text/xsl' " \
                                "href='../xslt/test_report_xml_to_html.xslt'")

    def addStepComment(self, content):
        if type(content) != types.ListType:
            content = [content]

        comment = NodeUtils('comment', True)
        comment.setAttribute('time_stamp', DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff"))

        commentReason = content[0]
        if not isinstance(commentReason, unicode):
            commentReason = unicode(commentReason, 'Latin-1')

        comment.setAttribute('reason', commentReason)

        if len(content) > 1:
            text = content[1]
            if not isinstance(text, unicode):
                text = unicode(text, 'Latin-1')
            comment['text'] = text

        self.tcReport.append(comment)

    def addStepWarning(self, warningText=''):
        if type(warningText) != types.ListType:
            warningText = [warningText]

        for i in range(len(warningText)):
            comment = NodeUtils('warning', True)
            commentReason = warningText[i]
            if not isinstance(commentReason, unicode):
                commentReason = unicode(commentReason, 'Latin-1')

            comment.setAttribute('reason', commentReason)
            comment['text'] = commentReason
            self.tcReport.append(comment)

    def addGeneralWarning(self, warningText=''):
        # check if 'general_warnings' tag already exists in report
        generalWarnings = self.report.find('/testreport/general_warnings')

        if not generalWarnings:
            # create new tag
            generalWarnings = NodeUtils('general_warnings', True)
            # append it to test report
            self.report.append(generalWarnings)

        # create 'warning' tag under 'general_warnings' tag
        warning = NodeUtils('warning', True)
        warning['text'] = warningText
        # add warning into tag as a text node
        generalWarnings.append(warning)

    def startTest(self, test):
        self._testCounter += 1
        debug.brf("Start test case: %s\n\n" % test.tcId)
        self.tcReport.setAttribute('start_time', time.strftime("%H:%M:%S"))

        if test.description():
            try:
                desc = NodeUtils('description', True)
                desc.setAttribute('title', test.tcId)
                desc['text'] = unicode(test.description().rstrip() or '(not defined)', 'Latin-1')
            except UnicodeError:
                test.fail('Unsuitable docstring in test method %s:%s' % \
                            (test.testMethodName, repr(test.description())))
            else:
                self.tcReport.append(desc)

    def stopTest(self, test):
        """Called when the given test has been run.
        """
        debug.brf("Stop test case: %s\n\n" % test.tcId)

        self.clearCurrentTestStep()
        
        # end server test sequence
        self.endSequence()
        testId, testType = self.match_id(test.tcId).groups()
        testType = testType.replace(';', '')
        testCaseName = ""
        try:
            testCaseName = unicode(testId, 'Latin-1')+"#"+str(core.FW_conf['repeat_index'])
        except UnicodeEncodeError:
            testCaseName = testId +"#"+str(core.FW_conf['repeat_index'])
        self.tcReport.setAttribute('id', testCaseName)

        self.tcReport.setAttribute('date', time.strftime("%Y-%m-%d"))
        self.tcReport.setAttribute('time', time.strftime("%H:%M:%S"))
        self.tcReport.setAttribute('stop_time', time.strftime("%H:%M:%S"))

        try:
            self.tcReport.setAttribute('subarea', test.subarea)
            self.tcReport.setAttribute('feature', test.feature)
        except:
            self.tcReport.setAttribute('subarea', 'not available')
            self.tcReport.setAttribute('feature', 'not available')

            debug.err('Warning: subarea and feature should be defined in the '
                      'test case: "%s"' % test.tcId )

        if self.memoryFile:
            self.tcReport.setAttribute('memory', self.memoryFile)
            self.memoryFile = None

        if self.traceFile:
            self.tcReport.setAttribute('trace', self.traceFile)
            self.traceFile = None

    def addBlock(self, oBlock):
        self.tcReport.append(oBlock)

    def addError(self):        
        errorTag = NodeUtils('error', True)
        if not self.tcReport.getAttribute('result'):
            self.tcReport.setAttribute('result', NO_RESULT)
            
        reason, traceText = getReasonAndStackTraceFromCurrentException()

        debug.brf("Error! (%s)\n%s\n\n" % (reason, traceText))
                    
        errorTag['text'] = unicode(traceText, 'Latin-1')
        errorTag.setAttribute('reason', unicode(reason, 'Latin-1'))
        self.tcReport.append(errorTag)

    def addFailure(self, failure = None, crashOrReset = False):
        """Add failure to report

            Parameters

            failure             failure message (optional)
            crashOrReset        whether error type is crash or reset (default = False)
        """
        self.__failureToReport(failure, crashOrReset)

    def addStop(self, reason = None):
        # if reason has not been set or it differs from 'Test execution terminated'
        # --> test execution stopped to tool error --> we need to get both reason and traceback
        if not reason:
            reason = getCurrentExceptionReason()

        if reason != 'Test execution terminated':
            reason, traceText = getReasonAndStackTraceFromCurrentException()
        else:
            traceText = ""
                    
        debug.out(reason)
        
        self.tcReport.setAttribute('result', NA)

        errorTag = NodeUtils('error', True)
        errorTag.setAttribute('reason', reason)

        # append traceback if available
        if traceText:
            errorTag['text'] = unicode(traceText, 'Latin-1')

        self.tcReport.append(errorTag)

    def addSkip(self):
        reason = getCurrentExceptionReason()
        #debug.err("N/A! (%s)\n\n" % err)
        errorTag = NodeUtils('error', True)

        if not self.tcReport.getAttribute('result'):
            self.tcReport.setAttribute('result', NA)
        
        errorTag.setAttribute('reason', unicode(reason, 'Latin-1'))
        self.tcReport.append(errorTag)

    def addISIMessageFailure(self):
        self.__failureToReport()

    def __failureToReport(self, failure = None, crashOrReset = False):
        """Adds failure to report
                
            Parameters

            failure             error string (default = None)
                                when None, error reason and traceback is taken from current exception
            crashOrReset        whether error type is crash or reset (default = False)
        """
        if failure:
            reason = failure
            traceText = ''
        else:
            # get failure reason and only test script related stack trace line
            reason, traceText = getReasonAndStackTraceFromCurrentException(True)

        debug.err("Failure! (%s)\n\n" % reason)

        errorTag = NodeUtils('error', True)
        
        self.tcReport.setAttribute('result', 'Failed')

        errorTag.setAttribute('reason', unicode(reason, 'Latin-1'))

        if traceText:
            # add traceback to errorTag
            errorTag['text'] = unicode(traceText, 'Latin-1')

        if crashOrReset:
            # place crashOrReset attribute
            errorTag.setAttribute('crashOrReset', 'true')

        self.tcReport.append(errorTag)
        core.FW_conf['connection'].sendWaitMessageToMarbleGUI(1,
                                             'Previous step failed')

    def addSuccess(self, test):
        debug.brf("Success!\n\n")
        self.tcReport.setAttribute('result', 'Passed')

    def wasSuccessful(self):
        return self.tcReport.getAttribute('result') == 'Passed'

    def wasSkipped(self):
        return self.tcReport.getAttribute('result') == NA

    def getResult(self):
        """Returns test case's result."""
        return self.tcReport.getAttribute('result')

    def getError(self):
        """Returns test case's error node."""
        errorNode = self.tcReport.find('//error')
        return errorNode or None        
        
    def __repr__(self):
        return "<%s>" % self.__class__

    def addTestStep(self, teststep):
        teststep.setAttribute("stepId", str(self.testStepCount))
        self.tcReport.append(teststep)

    def endSequence(self):
       """ Ending teststep. Called from test scripts.
       """
       if not getattr(self, 'sequenceRunning', None): return

       # add elements
       self.__addSequenceMsgs()         # <input> <outcome>
       self.__addSequenceExpect()       # <expect>
       self.__addSequenceSummary()      # <summary>

       # clean memory
       del self.sequenceElement
       self.sequenceMsgs = None
       self.isi_message_fields = None
       self.isi_message_errors = None
       self.msg_index = None
       self.sequenceRunning = None

    def addSequenceInput(self, request, timeout):
        """ Build <input> element.
        """
        self.__messageToSequence(request, timeout, 'input')

    def addSequenceOutcome(self, response, timeout):
        """ Build <outcome> element.
        """
        self.__messageToSequence(response, timeout, 'outcome')

    def __messageToSequence(self, message, timeout, element):
        if not getattr(self, 'sequenceRunning', None): return

        self.__addSequenceMsgs()
        xml_message = message.toxmlelement(element)
        xml_message.setAttribute('timeout', str(timeout))
        self.sequenceMsgs.append(xml_message)

    def __addSequenceMsgs(self):
        """ Add <input> + <outcome> elements sequentially
            to test sequence (=teststep).
        """
        if getattr(self, 'sequenceMsgs', None) != None:
            msg_index = 1  # index = msg number
            for msg in self.sequenceMsgs:
                if msg.getName() == 'outcome':
                    msg.setAttribute('index_', str(msg_index))
                    msg_index += 1

                self.sequenceElement.append(msg)

        self.sequenceMsgs = [] # empty the sequence

    def __addSequenceExpect(self):
        """ Add <expected> element to test sequence (=teststep).
        """
        # assertMsgFields not used !!
        if getattr(self, 'isi_message_fields', None) == None: return

        if getattr(self, 'expect_doc', None) == None:
            self.expect_elem = NodeUtils('expect', True)

        expList = []
        for key, value in self.isi_message_fields.items():
            if key not in ('resource', 'utid', 'msg_id'):
                expList.append(key + ': ' + str(value))

        outcome = NodeUtils('outcome', True)
        outcome['text'] = ', '.join(expList)

        for key in ('resource', 'utid', 'msg_id'):
            value = self.isi_message_fields.get(key)
            if value:
                outcome.setAttribute(key, str(value))

        if getattr(self, 'msg_index', None) != None:
            outcome.setAttribute('index', str(self.msg_index[1]))

        self.expect_elem.append(outcome)

        self.sequenceElement.append(self.expect_elem)
        self.__id = 0
        self.__addId(self.sequenceElement)

        self.addTestStep(self.sequenceElement.clone())

    def __addId(self, element):
        """Add Id's to the document of test sequence (=teststep)."""

        if element.hasChildNodes():
            child = element.first()
            while(child):
                self.__id += 1
                child.setAttribute("id", str(self.__id))
                self.__addId(child)
                child = child.next()

    def __addSequenceSummary(self):
        """Add <summary> element to test sequence (=teststep).
        """
        if getattr(self, 'isi_message_errors', None) == None: return

        error_root = NodeUtils('summary', True)
        error_expect = NodeUtils('expect', True)
        error_root.append(error_expect)
        expectList = self.sequenceElement.findall('//expect')
        error_expect.setAttribute('id', expectList[0].getAttribute('id'))

        error_expect.append(self.__sequenceFailedSummary())
        #FIXME: is there need for passed summary ?
        #       error_expect.append(self.__sequencePassedSummary())

        self.addTestStep(error_root)

    def __sequenceFailedSummary(self):
        """ Build content of summary element after fail.
        """
        if getattr(self, 'expect_elem', None) != None:
            outcome = self.isi_message_errors.toxmlelement('outcome')

            outcomeList = self.expect_elem.findall('//outcome')

            for oOutcome in outcomeList:
                # get the current msg_index
                if getattr(self, 'msg_index', None) != None:
                    if oOutcome.getAttribute('index') == str(self.msg_index[1]):
                        outcome.setAttribute('id', oOutcome.getAttribute('id'))
                        break
                else:
                    outcome.setAttribute('id', oOutcome.getAttribute('id'))

            return outcome

    def __sequencePassedSummary(self):
        """ Build content of summary element after pass.
        """
        expect = NodeUtils('expect', True)
        # FIXME: remove this if it isn't needed..
        outcomeList = self.expect_elem.findall('//outcome')
        for oOutcome in outcomeList:
            outcome = NodeUtils('outcome', True)
            expect.append(outcome)
            outcome.setAttribute('id', oOutcome.Attribute('id'))

        return expect
        
    def __getXMLReportFilename(self):
        """ Returns a path to a report XML file

        Returns:

            - A string representing XML file under product report path

        """
        if not core.FW_conf['test_result_dir'] or not core.FW_conf['test_result_name']:
            return None

        # check whether result name already has suffix
        if os.path.splitext(core.FW_conf['test_result_name'])[-1] == '':
            suffix = '.xml'
        else:           
            suffix = ''
            
        # check whether result dir ends to xml folder or not
        if os.path.split(core.FW_conf['test_result_dir'])[-1] == 'xml':
            testResultDir = core.FW_conf['test_result_dir']
        else:
            testResultDir = os.path.join(core.FW_conf['test_result_dir'], 'xml')
        
        # use hasSuffix to determine if .xml is needed or not
        if core.FW_conf['repeat'] > 1 or core.FW_conf['run_hours'] > 0:        
            return os.path.join(testResultDir, core.FW_conf['test_result_name'] + '#%s' % core.FW_conf['repeat_index']) + suffix
        else:
            return os.path.join(testResultDir, core.FW_conf['test_result_name']) + suffix

    def save(self):
        """ Saves test report XML to a file

        This is called to save the final test report.
        """
        # append test case report node to main report
        self.report.append(self.tcReport)

        fname = self.__getXMLReportFilename()

        if not fname:
            return

        folderName = os.path.dirname(fname)

        if not os.path.isdir(folderName):
            os.makedirs(folderName)        
        
        try:       
            self.report.save(fname, processInfo = True)
        except Exception:
            # Saving didn't succeed --> try again one more time
            debug.err("Saving of %s didn't succeed. Trying again..." % str(fname))
            time.sleep(3)
            self.report.save(fname, processInfo = True)

        #if core.FW_conf['settings'].TestRun.PerformanceTesting:
        #    # save performance report
        #    with core.FW_conf['connection'].perfReportLock:
        #        if core.FW_conf['connection'].perfReport:
        #            perfResultFolder = os.path.join(core.FW_conf['test_result_dir'], 'performance')
        #            perfResultFile = os.path.splitext(os.path.basename(fname))[0] + '_performance.xml'

        #            if not os.path.isdir(perfResultFolder):
        #                os.makedirs(perfResultFolder)        

        #            core.FW_conf['connection'].perfReport.save(os.path.join(perfResultFolder, perfResultFile))
        #            core.FW_conf['connection'].perfReport = None

        return fname

