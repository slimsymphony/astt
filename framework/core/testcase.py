# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------------
"""Test case class module.
"""

# ============================================================================
# Module Setup

# Python library module imports
import time, getpass, types, os, clr, cPickle
import shutil
from time import gmtime, strftime
from System.Globalization import CultureInfo
from System.Threading import Thread
from System.Net import Dns
from System import Collections
from System.Collections.Generic import Dictionary
from System import DateTime

# Marble module imports
import core
from core.testcase_exceptions import *
from interfaces.isimessage import ISIMessageException
from utils.file_utils import filterValidFilename
from core.leader import executeInFollower
from interfaces.tab_interface import TABInterfaceException
from core.leader import executeInFollower

clr.AddReference('System')
from System import DateTime
# Marble imports
clr.AddReference('TestAutomation.Bridge')
from TestAutomation.Bridge.ScriptingTools import ScriptException


# ============================================================================
class TestCase(object):
    """Base class for all server and UI test case classes.
    """
    def __init__(self, testMethod = "runTest", tcId = ""):
        # set culture to 'en-US' so that .NET modules will always use 'en-US' culture instead of machine culture.
        cultureInfo = CultureInfo('en-US')
        Thread.CurrentThread.CurrentCulture = cultureInfo
        Thread.CurrentThread.CurrentUICulture = cultureInfo

        self.testMethodName = testMethod
        self.tcId = tcId
        # result will be set in __call__
        self.result = None
        self._inSetUp = False
        self._inTestCaseSetUp = False
        self._inPostSetUp = False
        self._inTestCase = False
        self._inTearDown = False
        self._inTestCaseTearDown = False
        self._inPostTearDown = False
#        self.remotePhoneExecution = False

        # attribute for raising systemExit and skipping actions during it
        self._raiseSystemExit = False

        # FIXME: Get rid of these in testcase.py level and move them to phone.py
        #        core.FW_conf flags need to be changed/removed accordingly
        # add blackbox and simulated battery instance variables
        self.blackBox = core.FW_conf['blackbox']
        self.blackBoxEnabled = core.FW_conf['blackbox_enabled']
        core.FW_conf['connection'].battery = core.FW_conf['blt_ue'] # Set battery for main phone

        self.leader_start_time = 0

        # access to remote phone manager
        self.remote = core.FW_conf['remote_connection']

        try:
            self.__testMethodDoc = getattr(self, testMethod).__doc__
            if self.__testMethodDoc == None:
                self.__testMethodDoc = 'Doc string missing \n@tcid undefined'
        except:
            self.__testMethodDoc = None

    def __getattr__(self, attr, *args, **kwargs):
        """ Map main phone to self """
        return getattr(core.FW_conf['connection'],attr)

    def __getitem__(self, key):
        """ When using indexes provide access to phones."""
        assert isinstance(key, int) and key > 0, 'Phone index must be above zero!'

        assert key <= len(core.FW_conf['connection']), \
            'Phone not found with index: %s!' % key

        return core.FW_conf['connection'][key]

    def logApply(self, function, *args, **kwargs):
        """Call the function and catch all exceptions. Do not raise any other
           exceptions than SystemExit.

        Returns the result of the function call if everything goes well, otherwise False
        """
        result = False

        if core.FW_conf['should_stop']:
            self.result.addStop("Test execution terminated")
        else:
            try:
                result = apply(function, args, kwargs)
            except SystemExit:
                self._raiseSystemExit = True
                # just raise SystemExit
                raise
            except TestCaseWarning, warning:
                self._warn(str(warning))
                sys.exc_clear() # clear TestCaseWarning exception from system
            except SkipTestException:
                self.result.addSkip()
            except ISIMessageException:
                self.result.addISIMessageFailure()
            except StopTestException:
                self.result.addStop()
            #except RemoteConnectionException:
            #    raise
            except TestException, e:
                # error capture is taken from TestException
                if not core.FW_conf['should_stop']:
                    # If phone is not given to exception, take capture from main phone
                    if e.phone:
                        try:
                            if e.takeErrorCapture:
                                e.phone.takeCaptureFromFailure()
                        finally:
                            e.phone.setFailureCaptureTaken(False)
                    else:
                        try:
                            if e.takeErrorCapture:
                                self.takeCaptureFromFailure()
                        finally:
                            self.setFailureCaptureTaken(False)

                    # add failure to test result and output error message, do not fail case during test case specific teardown
                    if not self._inTestCaseTearDown:
                        self.result.addFailure()
            except KeyboardInterrupt:
                self.result.addError()
            except ScriptException, err:
                # failure coming from TA bridge
                self.result.addFailure(err.Message)
            except TABInterfaceException, err:
                # if video recorder available, check UI freeze when TAB is reporting interface exception
                # FIXME: check which Main throw the exception (Main/Main2/..)
                if core.FW_conf['blackbox'].isVideoRecorderAvailable():
                    core.FW_conf['connection'].exit._checkUiFreeze()

                self.result.addError()
            except Exception, err:
                if not core.FW_conf['should_stop']:
                    debug.err('Error during test case execution: %s' % str(err))
                    self.result.addError()

            return result

    def addMarkerToBlx(self, message):
        """Add Marker text to blx log
            Parameters: message, Message added to blx log
        """
        if core.FW_conf['tracing_enabled']:
            core.FW_conf['trace'].markerToBlx(message)

    def yapasGarbageCollectorReq(self):
        """ Execute Yapas grabage collector
        """
        if core.FW_conf['tracing_enabled']:
            core.FW_conf['trace'].yapasGarbageCollector()

    def traceXml(self, traceConfXml):
        """ Activates/deactivates traces based on given xml
            Parameters:
                traceConfXml, xml containing information about wanted traces
        """
        if core.FW_conf['tracing_enabled']:
            core.FW_conf['trace'].traceActivation(traceConfXml, scriptActivation = True )

    def _setUp(self, uiEnabled=False, graniteServerEnabled=True):
        """Private test case setup."""
        if graniteServerEnabled:
            # activate Granite server for remote phones
            for remote in core.FW_conf['remote_connection']:
                remote.activateGraniteServer(forced=True)

            # after connection creation write NTN/BTN provisioning settings for remote phone(s) or
            # only once in CLI mode
            if not core.FW_conf['prov_settings_written']:
                for remote in core.FW_conf['remote_connection']:
                    remote.writeNokiaProvisioningSettings()

                core.FW_conf['prov_settings_written'] = True

        if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
            self.leader_start_time = time.time()

        if core.FW_conf['connection'].currentTcId:
            if not core.FW_conf['connection'].isLeader() and \
               not core.FW_conf['connection'].isFollower() and \
               not core.FW_conf['connection'].isFullBlackBox():
                # connect TA server(s)
                for phone in core.FW_conf['connection']:
                    phone._tab._connectServer()

            # set test case marker using TAB
            core.FW_conf['connection']._tab._addLogMarker('TEST CASE: %s' % core.FW_conf['connection'].currentTcId)

        self.logApply(core.FW_conf['connection']._setUp)

        for remote in core.FW_conf['remote_connection']:
            remote.setUiEnabled(uiEnabled)
            self.logApply(remote._setUp)

        # Ensure that when running on BlackBox mode, default USB connector is always connected
        # A try-catch clause is preferred due to there might be no USBAccessoryCard to execute this operation in some cases.
        if self.blackBox is not None and self.blackBox.isVideoRecorderAvailable():
            videoPath = os.path.join(core.FW_conf['test_result_dir'], 'videos')
            if not os.path.isdir(videoPath):
                os.makedirs(videoPath)
            self.blackBox.recordVideo(os.path.join(videoPath, os.path.splitext(core.FW_conf['test_result_name'])[0]) + '.avi')

        if self.blackBox is not None and \
            core.FW_conf['blackbox_enabled'] and \
            not core.FW_conf['connection'].isFollower():
            try:
                self.blackBox.connectDefaultAccessoryUsb()
            except Exception, ex:
                debug.err('Testcase setup: %s' %str(ex))

        debug.out("MarbleTestCase setUp")

        for remote in core.FW_conf['remote_connection']:
            remote.cancelIndications() # Move this to Phone.setup
            remote.checkPhoneStatus() # Move this to Phone.setup

    def _postSetUp(self):
        """Private test case post setup. Actions which are done after setup."""
        if core.FW_conf['connection'].currentTcId and not core.FW_conf['should_stop']:
            if not (core.FW_conf['connection'].isFullBlackBox() or core.FW_conf['connection'].isFollower()):
                core.FW_conf['connection']._getCrashDumps()

            # if executing with full blackbox, fetch dumps only for first case setup and fetch all dumps available
            elif (core.FW_conf['connection'].isFullBlackBox() or core.FW_conf['connection'].isFollower()) and \
                not core.FW_conf['initial_crash_fetch_done'] and int(core.FW_conf['settings'].TestRun.DumpFileFetchInterval) > 0:
                core.FW_conf['connection']._getCrashDumpsInBlackBox(getAllDumps=True)
                core.FW_conf['initial_crash_fetch_done'] = True  # blackbox mode does not fetch anymore dump files at startup

            # get x-files from remote phone(s)
            for remote in core.FW_conf['remote_connection']:
                resp = self.logApply(remote._fileDumper.extractDumpFiles)
                if resp == False:
                    remote.warn('Getting X-files (in setup) failed: %s.' % resp)

            # start current measurement if battery is available
            if core.FW_conf['connection'].battery is not None and core.FW_conf['connection'].battery.isEnabled():
                core.FW_conf['connection'].battery.startCurrentMeasuring()
            if core.FW_conf['connection'].isLeader() and core.FW_conf['settings'].TestRun.BLTEnabledInFollower:
                executeInFollower("core.FW_conf['connection'].battery.startCurrentMeasuring()")

    def _tearDown(self):
        """Private test case teardown."""

        if core.FW_conf['connection'].isLeader() and core.FW_conf['settings'].TestRun.BLTEnabledInFollower:
            executeInFollower("core.FW_conf['blt_ue'].stopCurrentMeasuring()")

        # stop current measurement if battery is available
        if core.FW_conf['connection'].battery is not None and core.FW_conf['connection'].battery.isEnabled():
            core.FW_conf['connection'].battery.stopCurrentMeasuring()

        # skip tearDown if systemExit exception has occurred or
        # we are stopping execution or teardown skipping is wanted
        if not self._raiseSystemExit and not core.FW_conf['should_stop']:
            debug.out("MarbleTestCase tearDown")

            self.logApply(core.FW_conf['connection']._tearDown, self)

            for remote in core.FW_conf['remote_connection']:
                self.logApply(remote._tearDown, self)

    def _postTearDown(self):
        """Private test case post teardown. Actions done after teardown should be listed here."""
        if not core.FW_conf['should_stop'] and \
           (not core.FW_conf['connection'].isFollower() or core.FW_conf['connection'].isFullBlackBox()):
            if core.FW_conf['connection'].currentTcId:
                if not (core.FW_conf['connection'].isFullBlackBox() or core.FW_conf['connection'].isFollower()):
                    core.FW_conf['connection']._getCrashDumps()
                elif not core.FW_conf['connection'].isFollower():
                    core.FW_conf['connection']._getCrashDumpsInBlackBox()

            if not core.FW_conf['connection'].isLeader() and \
               not core.FW_conf['connection'].isFollower():
                # disconnect TA server(s) and scripting service(s)
                for phone in core.FW_conf['connection']:
                    phone._tab._disconnectServices()

            # get and remove x-files from remote phone(s)
            for remote in core.FW_conf['remote_connection']:
                resp = self.logApply(remote._fileDumper.extractDumpFiles)
                if resp == False:
                    remote.warn('Getting X-files (in tearDown) failed: %s.' % resp)

                resp = self.logApply(remote._fileDumper.removeDumpFiles)
                if resp == False:
                    remote.warn('Removing X-files(in tearDown) failed: %s.' % resp)

    def _stopTest(self):
        """Private test case stop functionality."""
        try:
            if core.FW_conf['should_stop']:
                return

            if self.result.wasSuccessful() or self.result.wasSkipped():
                return

        finally:
            # If recording video, stop recording and store video path to results.
            if self.blackBox is not None and self.blackBox.isVideoRecorderAvailable():

                if core.FW_conf['connection'].isFollower():
                    debug.out('Follower, record video still few seconds')
                    self.delay(3000, False)

                self.blackBox.stopRecording()

                relativeFileName = os.path.join('videos',os.path.splitext(core.FW_conf['test_result_name'])[0] + '.avi')
                videoFile = os.path.join(core.FW_conf['test_result_dir'], relativeFileName)
                if os.path.isfile(videoFile):
                    videoRes = NodeUtils('videos', True)
                    videoElement = NodeUtils('video', True)
                    videoElement.setAttribute('name', relativeFileName)
                    videoRes.append(videoElement)
                    self.result.addBlock(videoRes)

            # if in leader mode, request case stop and wait for followers to finish test case
            if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
                core.FW_conf['leader'].StopTest()

                # wait for followers to complete execution
                try:
                    waitSeconds = int(core.FW_conf['settings'].TestRun.WaitFollowersToFinishTimeout)
                except:
                    debug.err('Could not get waiting time from settings')
                    waitSeconds = 250

                debug.brf('Waiting 5 seconds for followers..')
                self.delay(5000, False)

                while waitSeconds >= 0:
                    # Dictinary <string clientId, Dictionary<string result, int status> followerStatuses
                    followerStatuses = core.FW_conf['leader'].GetStatus()
                    readyToContinue = True
                    for status in followerStatuses:
                        if status.Value == 0:
                            debug.brf('follower %s ready (%d..)' % (status.Key, waitSeconds))
                        elif status.Value == -1:
                            debug.brf('follower %s has not initialized test case (%d..)' % (status.Key, waitSeconds))
                        elif status.Value == -2:
                            debug.brf('follower %s is tearing execution down (%d..)' % (status.Key, waitSeconds))
                            readyToContinue = False
                        else:
                            debug.brf('follower %s queue length %s (%d..)' % (status.Key, status.Value, waitSeconds) )
                            readyToContinue = False
                    if readyToContinue:
                        break
                    waitSeconds -= 1
                    core.FW_conf['connection'].sendWaitMessageToMarbleGUI(1, 'Test execution sleeping for %s seconds' % 1)
                    time.sleep(1)

            # Testcase is stopping. End referencePhone call (if running)
            if self.referencePhone is not None and \
               core.FW_conf['settings'].TestRun.AutomaticRejectCallForReferencePhone:
                try:
                    self.referencePhone.rejectCall(doNotReport = True)
                except Exception, ex:
                    debug.err('Testcase stop: %s' %str(ex))

            # delete not needed objects from test case instance
            # take class objects names from self to a list
            classObjectNames = [x for x in vars(self)]

            # preserved objects
            preservedObjects = ['result']

            # if there's audio devices playing or recording audio, shut them down
            for audiodevice in core.FW_conf['audio_devices'][:]: # use copy of list since dispose
                audiodevice.dispose()                            # will remove the device from core.FW_conf['audio_devices'] list

            if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
                self.__processFollowerResults()

            self._clearStillImageArray()

            # delete all instances from self for avoiding circular references
            for name in classObjectNames:
                if not type(vars(self)[name]) in [types.StringType,
                                                  types.IntType,
                                                  types.BooleanType]:
                    if not name in preservedObjects:
                        del vars(self)[name]
                        debug.vrb('object deleted from self: %s' % name)

            # Make sure this gets called last
            self.result.stopTest(self)

    def __processFollowerResults(self):
        """ loads existing results from cache and adds test round results to it. """

        resultCacheFileName = os.path.join(core.FW_conf['test_result_dir'], os.path.split(core.FW_conf['test_result_dir'])[1] + ".cache" )
        if os.path.isfile(resultCacheFileName):
            resultDict = cPickle.load(open(resultCacheFileName, 'rb'))
            debug.brf('Loading existing results from cache...')
        else:
            resultDict = {}

        # read which iteration this was
        if not resultDict.has_key(self.tcId):
            resultDict[self.tcId] = {}
        iteration = len(resultDict[self.tcId]) + 1
        resultDict[self.tcId][iteration] = {} # new iteration for the result dictionary

        leaderResult = Dictionary[str, str]()
        res = self.result.getResult()

        try:
            if str(res) == 'Failed':
                errornode = self.result.getError()
                if errornode != None and errornode.getAttribute('reason') == 'X-Files generated during testcase execution' or \
                    errornode.getAttribute('reason') == 'Phone reset detected':
                    leaderResult.Add('Result', 'X-files')
                elif errornode != None:
                    leaderResult.Add('Result', str(errornode.getAttribute('reason')))
        except:
            debug.err('error reading result node')
            leaderResult.Add('Result', str(res))

        if not leaderResult.ContainsKey('Result'): # if result was not added
            leaderResult.Add('Result', str(res))

        folder = os.path.split(core.FW_conf['test_result_dir'])[1]

        leaderResult.Add('ResultDir', folder)
        leaderResult.Add('Duration', str( int( time.time() - self.leader_start_time )) )
        #leaderResult.Add('EndTime', strftime("%Y-%m-%d %H:%M:%S", gmtime()))
        leaderResult.Add('EndTime', DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"))
        for i in range(1, len(self._capturedStillImages) + 1 ):
            debug.out(self._capturedStillImages[i-1])
            relativeFileName = os.path.join('videos',self._capturedStillImages[i-1])
            leaderResult.Add('Capture%s' % str(i), relativeFileName)

        try:
            relativeFileName = os.path.join('videos',os.path.splitext(core.FW_conf['test_result_name'])[0] + '.avi')
            videoFile = os.path.join(core.FW_conf['test_result_dir'], relativeFileName)
            if os.path.isfile(videoFile): # change video address if video file is found
                leaderResult.Add('Video', str(relativeFileName))
                #debug.brf('Added leader Video: %s' % str(videoFile))
        except Exception as e:
            debug.brf('Could not add Leader video to result: %s' % e.message)

        leaderResult.Add('Machine', str(Dns.GetHostName())) # add Leader machine name

        followerResults = core.FW_conf['leader'].GetResults()
        followerResults.Add('Leader', leaderResult) # Add leader result to dictionary

        for followerRes in followerResults:
            clientId = followerRes.Key # string client id
            result = followerRes.Value # dictionary of result, link

            if not resultDict[self.tcId][iteration].has_key(clientId):
                resultDict[self.tcId][iteration][clientId] = {}
            else:
                debug.err('\n**** %s has already result for iteration %s on test case %s. Will not override.\n ***' % (clientId, iteration, self.tcId))
                continue

            # loop through result
            debug.brf('Results for client %s' % clientId)
            for res in result:
                debug.brf('Adding %s %s' % (str(res.Key), str(res.Value)) )
                resultDict[self.tcId][iteration][clientId][str(res.Key)] = str(res.Value)

        if resultDict:
            # dump resultDict to cache
            try:
                cacheFile = open(resultCacheFileName, 'wb')
                cPickle.dump(resultDict, cacheFile, 0)
                cacheFile.close()
            except:
                for i in range(10):
                    debug.err('*' * 40 + ' FAILED TO FLUSH RESULTS TO DISK! ' + '*' * 40)

    def getCrashDumps(self):
        """ Return True if crash dumps are found, otherwise False """

        if len(core.FW_conf['connection']._getCrashDumps()):
            return True
        else:
            return False

    def __call__(self, result = None):
        """Execute the test case and log the results."""
        if result != None:
            self.result = result
        else:
            self.result = core.FW_conf['connection'].getResult()
            assert self.result, 'Internal error: test result is missing from Phone Manager instance!'

        core.FW_conf['connection'].currentTcId = self.tcId
        for remote in core.FW_conf['remote_connection']:
            remote.setResult(self.result)
            remote.currentTcId = self.tcId

        self.result.startTest(self)

        # add comment to test report whether we are in WhiteBox/HW Assisted WhiteBox mode
        self.comment('Executing test case in %s mode' % (core.FW_conf['blackbox_enabled'] and 'HW Assisted WhiteBox' or 'WhiteBox'))

        # add test case information for bltue report
        self.addBltueTestCase(self.tcId)

        try:
            # Code inside the next try-except -block must not raise exceptions.
            # All exception handling must be done within the logApply method.
            try:
                # return if test execution should be stopped
                if core.FW_conf['should_stop']:
                    return

                # execute _setUp
                self.comment('%s MARBLE SETUP %s' % ((15 * '='), (15 * '=')))
                try:
                    self._inSetUp = True
                    resp = self.logApply(self._setUp)
                finally:
                    self._inSetUp = False

                # return if test execution should be stopped
                if core.FW_conf['should_stop']:
                    return

                if resp == False or self.result.wasSkipped():
                    # execute _tearDown
                    self.comment('%s MARBLE TEARDOWN %s' % ((15 * '='), (15 * '=')))
                    try:
                        self._inTearDown = True
                        resp = self.logApply(self._tearDown)
                    finally:
                        self._inTearDown = False

                    # return because setup failed
                    return

                # return if test execution should be stopped
                if core.FW_conf['should_stop']:
                    return

                # execute possible test case's setUp
                if 'setUp' in dir(self):
                    self.comment('%s TEST CASE SETUP %s' % ((15 * '='), (15 * '=')))
                    try:
                        self._inTestCaseSetUp = True
                        resp = self.logApply(self.setUp)
                    finally:
                        self._inTestCaseSetUp = False

                    # return if test execution should be stopped
                    if core.FW_conf['should_stop']:
                        return

                    if resp == False or self.result.wasSkipped():
                        # test case setup failed

                        # execute _tearDown
                        self.comment('%s MARBLE TEARDOWN %s' % ((15 * '='), (15 * '=')))
                        try:
                            self._inTearDown = True
                            resp = self.logApply(self._tearDown)
                        finally:
                            self._inTearDown = False

                        # return if test execution should be stopped
                        if core.FW_conf['should_stop']:
                            return

                        # execute _postTearDown
                        try:
                            self._inPostTearDown = True
                            resp = self.logApply(self._postTearDown)
                        finally:
                            self._inPostTearDown = False

                        # return if test execution should be stopped
                        if core.FW_conf['should_stop']:
                            return

                        # execute possible test case's tearDown
                        if 'tearDown' in dir(self):
                            self.comment('%s TEST CASE TEARDOWN %s' % ((15 * '='), (15 * '=')))
                            try:
                                self._inTestCaseTearDown = True
                                resp = self.logApply(self.tearDown)
                            finally:
                                self._inTestCaseTearDown = False

                            if resp == False:
                                self._warn('Failure during test case teardown!')

                        # return because test case setup failed
                        return

                # return if test execution should be stopped
                if core.FW_conf['should_stop']:
                    return

                # execute _postSetUp
                try:
                    self._inPostSetUp = True
                    resp = self.logApply(self._postSetUp)
                finally:
                    self._inPostSetUp = False

                # return if post setup fails
                if resp == False:
                    self._warn('Failure during post setup!')
                    return

                # return if test execution should be stopped
                if core.FW_conf['should_stop']:
                    return

                # execute the test method
                testMethod = getattr(self, self.testMethodName)
                self.comment('%s TEST CASE %s' % ((15 * '='), (15 * '=')))
                try:
                    self._inTestCase = True
                    resp = self.logApply(testMethod)
                finally:
                    self._inTestCase = False

                ok = resp != False

                # return if test execution should be stopped
                if core.FW_conf['should_stop']:
                    return

                # execute _tearDown
                self.comment('%s MARBLE TEARDOWN %s' % ((15 * '='), (15 * '=')))
                try:
                    self._inTearDown = True
                    resp = self.logApply(self._tearDown)
                finally:
                    self._inTearDown = False

                if ok: ok = resp != False

                # return if test execution should be stopped
                if core.FW_conf['should_stop']:
                    return

                # execute possible test case's tearDown
                if 'tearDown' in dir(self):
                    self.comment('%s TEST CASE TEARDOWN %s' % ((15 * '='), (15 * '=')))
                    try:
                        self._inTestCaseTearDown = True
                        resp = self.logApply(self.tearDown)
                    finally:
                        self._inTestCaseTearDown = False

                    if resp == False:
                        self._warn('Failure during test case teardown!')

                    # return if test execution should be stopped
                    if core.FW_conf['should_stop']:
                        return

                # execute _postTearDown
                try:
                    self._inPostTearDown = True
                    resp = self.logApply(self._postTearDown)
                finally:
                    self._inPostTearDown = False

                if ok: ok = resp != False

                # return if test execution should be stopped
                if core.FW_conf['should_stop']:
                    return

                # Success!
                if not self.result.getError():
                    if ok:
                        self.result.addSuccess(self)
                        if core.FW_conf['delete_success_blx'] and core.FW_conf['tracing_enabled'] and not core.FW_conf['memory_leak_detection']:
                            #Delete successfull testcase blx if user doesn't need those
                            core.FW_conf['trace'].deleteBlx = True
            except SystemExit:
                # put self._raiseSystemExit flag to True so that SystemExit
                # can be raised in finally:
                self._raiseSystemExit = True
            except Exception, e:
                # This is usually caused by an internal error, but could also
                # be a KeyboardInterrupt. In either case, stop testing is
                # needed here.
                self.logApply(self.stop, e)
        finally:
            # raise SystemExit if needed
            if self._raiseSystemExit:
                raise

            for phone in core.FW_conf['connection']:
                if phone._createBugReport:
                    phone.createBugReport()

            if core.FW_conf['settings'].TestRun.TakeHeapDumps:
                core.FW_conf['connection'].takeHeapDumps()

            self._stopTest()

    def description(self):
        """Return description of the test."""
        if self.__testMethodDoc:
            desc = self.__testMethodDoc
            if self.__testMethodDoc.find('@tcId') > -1:
                desc = self.__testMethodDoc.split('@tcId ')[0]
                if len(self.__testMethodDoc.split('@tcId ')[1].split('\n')) > 1:
                    desc = "%s%s%s" % (desc,'\n',
                           self.__testMethodDoc.split('@tcId ')[1].split('\n')[1])
        else:
            desc = ""

        return desc


    # ============================================= Common assertion functions

    def stop(self, message):
        """Stop the testing immediately, with the given message."""
        raise StopTestException(message)

    def stopIf(self, expr, message):
        """Stop the testing if the expression is true."""
        if expr: self.stop(message)

    def stopUnless(self, expr, message):
        """Stop the testing unless the expression is true."""
        if not expr: self.stop(message)


    def assertMsgFields(self, message, **isi_message_fields):
        """Verify isi_message fields for expected values.

        Raises single ISIMessageException if errors were found.

        FIXME: Consider removing this method..
        """
        try:
            # index is the reserved word, and it isn't one of the isi_message_fields
            fields = []
            for value in isi_message_fields.items():
                if value[0]!='index_':  fields.append(value)
                else: self.result.msg_index = value

            self.result.isi_message_fields = dict(fields)
            message.assertFields(**self.result.isi_message_fields)
        except ISIMessageException, errors:
            self.result.isi_message_errors = errors
            raise

    def _warn(self, warning=None):
        """Add warning to the test result.

        This method does not stop the test execution.

        FIXME: Replace 'warning' attribute with '*warnings'
        """
        debug.err('Warning: %s' % warning)

        if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader' and warning != None:
            executeInFollower("self.warn('%s')" % (warning,))

        if type(warning) != types.ListType:
            warning = [warning]

        self.result.addStepWarning(warning)

    def warnIf(self, expr, warning=None):
        """Add warning to the test result if the expression is true.

        This method does not stop the test execution.

        FIXME: Replace 'warning' attribute with '*warnings'
        """
        if expr: self._warn(warning)

    def warnUnless(self, expr, warning=None):
        """Add warning to the test result unless the expression is true.

        This method does not stop the test execution.

        FIXME: Replace 'warning' attribute with '*warnings'
        """
        if not expr: self._warn(warning)

    def addBltueTestCase(self, testCaseName):
        """Write test case name to bltue report if necessary

            Parameters

            testStepName        test case name in string
        """
        if core.FW_conf['connection'].battery is not None and core.FW_conf['connection'].battery.isEnabled():
            bltueTestCase = NodeUtils('testcase', makeNewNode = True)
            bltueTestCase.setAttribute('name', testCaseName)
            core.FW_conf['connection'].battery.addBltueNode(bltueTestCase)

    def comment(self, comment):
        """Add comment to the test result. This just calls main phone's comment method."""

        core.FW_conf['connection'].comment(comment)

