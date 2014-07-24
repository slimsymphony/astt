"""Communication server module for Marble Framework.

    Interpretes messages coming from gui to fw and acts according to them.
"""

# ============================================================================
# Module Setup

import sys, os, traceback, time

import clr
from System import Threading
from System.Threading.Tasks import Task
from System.Threading import CancellationTokenSource, Thread, ParameterizedThreadStart

# Marble module imports
import core
from core import testrunner, debug, phone, remote_phone
from interfaces.fw_connection import FWServer, \
                                     ProtocolMessages
from core.testcase_exceptions import TestException
from utils.nodeutils import NodeUtils
from extensions.pyevent import pyevent

clr.AddReference("Nokia.Granite.HtmlReporting")
from Nokia.Granite.HtmlReporting import HtmlReporting

clr.AddReference('LeaderFollowerInterface')
from LeaderFollowerInterface import FolderShare

class FW_Exception(Exception):
    """Exception class for test FW exceptions with traceback info.
    """
    def __init__(self, command = None, testException = None):
        Exception.__init__(self)

        # with TestException we just use error string
        if testException:
            self._errorString = testException
        # from other exception we dig out also traceback
        else:
            et, ev, tb = sys.exc_info()
            self._errorString = ''.join(traceback.format_exception(et, ev, tb))

        self._command = command

    def __unicode__(self):
        return '\n%s\nwhen executing command "%s"' % \
            (self._errorString, self._command)


# ----------------------------------------------------------------------------
class FWCommunicationServer(object):
    """Communication server class for Marble Framework.

        Includes command loop for receiving commands from gui to fw. Has also
        methods for executing actions.
    """
    def __init__(self, serverPort):
        """Initialize variables.

            Parameters

            serverPort      server port number
        """
        self.fwConn = FWServer()
        self.__serverPort = serverPort
        self.__testRunner = testrunner.MarbleTestRunner()
        core.FW_conf['testrunner'] = self.__testRunner
        self.__commandDict = {}
        self.__currentCommand = ''
        self.__stopCommand = ''
        self.__cancelationToken = CancellationTokenSource()
        self.__executionOngoing = False
        self._parser = HtmlReporting()
        self.__runThread = None

        # create events for protocol messages
        for key, value in ProtocolMessages.__dict__.iteritems():
            if key.startswith('CMD_'):
                # create event for command
                exec("self.%s_EVENT, self.THROW_%s = pyevent.make_event()" % (key, key))
                # assign speficic method for created event
                exec("self.%s_EVENT += self.%s" % (key, key))
                # store command value, key pair to dict for further usage
                self.__commandDict[value] = key

    def __executeCommand(self, method, *args):
        """Executes command operation and catches exceptions."""
        try:
            self.__executionOngoing = True
            params = method(*args)
        # on system exit terminate task
        except SystemExit:
            self.__cancelationToken.Cancel()
        except Exception, err:
            if isinstance(err, TestException):
                errString = unicode(FW_Exception(self.__currentCommand or self.__stopCommand, str(err)))
            else:
                errString = unicode(FW_Exception(self.__currentCommand or self.__stopCommand))

            self.sendErrorMessage(errString)

            # reset test runner's repeat index here so that
            # next test case is always started from scratch
            core.FW_conf['repeat_index'] = 0
        else:
            # don't send ready message after connection creation
            # check that we don't send ready message when execution has stopped
            if method != self.__createPhoneConnection and \
               (self.__currentCommand == '' or self.__stopCommand == ''):
                self.fwConn.sendReadyMessage(self.__currentCommand and self.__currentCommand or self.__stopCommand)
        finally:
            self.__executionOngoing = False

            # don't clear current command after connection creation
            if method != self.__createPhoneConnection:
                self.__currentCommand = ''

    def __createPhoneConnection(self):
        """Creates phone connection."""
        try:
            if core.FW_conf['connection'] == None:
                core.FW_conf['connection'] = phone.PhoneManager()

            if not (core.FW_conf['connection'].isFullBlackBox() and core.FW_conf['blackbox_enabled']):
                # NOTE: this is called before every test case execution, but phone instance(s) createConnection just returns if connection is already made
                # create connection(s) to phone(s)
                core.FW_conf['connection'].connect()

                # check device statu(es)
                for phone in core.FW_conf['connection']:
                    phone._tab._checkDeviceStatus()

                # connect TA server(s)
                for phone in core.FW_conf['connection']:
                    phone._tab._connectServer()

            # create remote phone connections
            if core.FW_conf['remote_connection'] == None:
                core.FW_conf['remote_connection'] = remote_phone.RemotePhoneManager()
                core.FW_conf['remote_connection'].connect()

            # activate Granite server for remote phone(s)
            if core.FW_conf['remote_connection'] != None:
                for remote in core.FW_conf['remote_connection']:
                    remote.activateGraniteServer(forced = True)
        except Exception, err:
            debug.err("Error occurred in phone connection creation: %s" % str(err))
            raise

    def __handleReportPath(self, reportPath):
        """Sets core.FW_conf['test_result_dir'] and possible also core.FW_conf['test_result_name']
           depending on given report path.

            Parameters

            reportPath          report directory / report file path
        """
        # check whether reportPath is directory or file and act accordingly
        if os.path.isdir(reportPath):
            core.FW_conf['test_result_dir'] = reportPath
        else:
            core.FW_conf['test_result_dir'], core.FW_conf['test_result_name'] = os.path.split(reportPath)

            # check whether result dir ends to xml folder or not
            # take xml away here so that other files than test result xml go to root test result folder
            if os.path.split(core.FW_conf['test_result_dir'])[-1] == 'xml':
                core.FW_conf['test_result_dir'] = os.path.split(core.FW_conf['test_result_dir'])[0]

        if not os.path.isabs(core.FW_conf['test_result_dir']):
            core.FW_conf['test_result_dir'] = os.path.join(core.FW_conf['startup_path'], core.FW_conf['test_result_dir'])

        if ((core.FW_conf['connection'].isLeader() or core.FW_conf['connection'].isFollower()) and not core.FW_conf['connection'].isFullBlackBox()):
            share = os.path.abspath(core.FW_conf['test_result_dir'])
            debug.out('Sharing %s as %s' % (share, os.path.split(share)[1]))
            try:
                FolderShare.CreateShare(str.replace(share, "\\", "\\"), os.path.split(share)[1])
            except Exception as e:
                debug.brf('Could not create test result share %s: %s' % (share, e.message))

    def __prepareForRun(self, reportPath, blackboxEnabled = None, bltueEnabled = None):
        """Does needed actions before running IronPython or XAML test case.

            Parameters

            reportPath          test result directory or file path
            blackboxEnabled     whether blackbox is enabled/disabled
            bltueEnabled        whether bltue is enabled/disabled
        """
        self.__handleReportPath(reportPath)

        # For HW Assisted WhiteBox (Netduino based HW) set blackbox_enabled to True 
        if core.FW_conf['graybox_enabled'] and core.FW_conf['blackbox'].isHwAssistedWhiteBox():
            core.FW_conf['blackbox_enabled'] = True
        else:
            # set blackbox_enabled on the fly with eval
            if blackboxEnabled != None:
                try:
                    core.FW_conf['blackbox_enabled'] = eval(blackboxEnabled)
                    # For HW Assisted WhiteBox also set graybox_enabled when using IoWarrior based HW
                    core.FW_conf['graybox_enabled'] = core.FW_conf['blackbox_enabled']
                except:
                    debug.err('Unable to evaluate blackboxEnabled parameter (%s)' % str(blackboxEnabled))

        # check bltueEnabled on the fly with eval
        if bltueEnabled != None:
            bltueBool = None
            try:
                bltueBool = eval(bltueEnabled)
            except:
                debug.err('Unable to evaluate bltueEnabled parameter (%s)' % str(bltueEnabled))

            if bltueBool is not None and bltueBool:
                self.__initBltUe()

        # create phone connection and perform needed actions after that
        self.__createPhoneConnection()

        # if in MTBF leader mode, wait for subscribers
        if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
            debug.brf('Ping followers..')
            core.FW_conf['leader'].PingFollowers() # ensure connections by pinging the followers
            c = 0
            enoughwaiting = int(core.FW_conf['settings'].TestRun.WaitForFollowers)
            followersRequired = int(core.FW_conf['settings'].TestRun.RequiredFollowers)
            followersCount = int(core.FW_conf['settings'].TestRun.FollowersCount)
            while core.FW_conf['leader'].serviceClass.Followers.Count < followersCount:
                if c == 0:
                    debug.brf('Waiting for subscribers (%s/%s) subscribed)' % (core.FW_conf['leader'].serviceClass.Followers.Count, followersCount))
                    enoughwaiting -= 1
                core.FW_conf['connection'].sendWaitMessageToMarbleGUI(1, 'Waiting subscribers. Sleep for %s seconds' % 1)
                c += 1
                c = c % 10
                time.sleep(1)
                if core.FW_conf['leader'].serviceClass.Followers.Count >= followersRequired and enoughwaiting < 0:
                    debug.brf('Waiting timeout. Execution starts..')
                    break

    def CMD_RUN(self, params):
        """CMD_RUN event method. Runs the test case and writes test case specific report.

            Parameters

            params can be one of following lists:

            1. <tc dir> <tc module> <tc class> <tc method> <tc id> <report directory / report file path> <blackbox enabled/disabled> <bltue enabled/disabled>
            2. <xaml path> <report path> or
               <xaml path> <report path> <blackbox enabled/disabled>

            Usage

            run <parameters>

            NOTE: "blackbox enabled/disabled" must be either "True" or "False"
                  "bltue enabled/disabled" must be either "True" or "False"
        """
        # check parameter list length and call proper run method

        # option 1 (run IronPython test case)
        if len(params) == 8:
            self.__executeCommand(self.__runTC, params)
        # option 2 (run workflow XAML test case)
        elif len(params) == 3 or len(params) == 4:
            self.__executeCommand(self.__runXAML, params)

    def CMD_QUIT(self, params):
        """CMD_QUIT event method. Quits Framework process."""
        self.__executeCommand(self.__quit)

    def CMD_STOP(self, params):
        """CMD_STOP event method. Stops test execution."""
        self.__executeCommand(self.__stop)

    def CMD_SETTINGS(self, params):
        """CMD_SETTINGS event method. Updates given settings to FW core."""
        # FIXME: Validate settings file before calling self.settings
        self.__executeCommand(self.__settings, params)

    def CMD_CAPTURE(self, params):
        """CMD_CAPTURE event method. Gets display capture from the phone"""
        # create phone connection and perform needed actions after that
        self.__executeCommand(self.__createPhoneConnection)

        self.__executeCommand(self.__capture, params)

    def CMD_TESTRUN_END(self, params):
        """CMD_TESTRUN_END event method. Gives information when test run ends."""
        self.__executeCommand(self.__testRunEnd)

    def CMD_INIT_SERVER(self, params):
        """CMD_INIT_SERVER event method. Initializes the socket server module"""
        self.fwConn.sendReadyMessage(ProtocolMessages.CMD_INIT_SERVER)

    def CMD_DISABLE_LOCK_SCREEN(self, params):
        """CMD_DISABLE_LOCK_SCREEN event method. Disables lock screen by modifying database and rebooting device."""
        self.__executeCommand(self.__createPhoneConnection)

        self.__executeCommand(self.__disableLockScreen)

    def CMD_EXECUTE(self, params):
        """CMD_EXECUTE event method. Executes given test step."""
        self.__executeCommand(self.__createPhoneConnection)

        self.__executeCommand(self.__executeStep, params)

    def __runTC(self, params):
        """Commands test runner to run given test case

            Parameters

            params contains a list of

            tcDir               test case directory
            tcModule            test case module
            tcClass             test case class
            tcMethod            test case method
            tcId                test case id
            reportPath          test result directory or file path
            blackboxEnabled     whether blackbox is enabled/disabled
            bltueEnabled        whether bltue is enabled/disabled
        """
        # get test data parameters
        tcDir           = params[0]
        tcModule        = params[1]
        tcClass         = params[2]
        tcMethod        = params[3]
        tcId            = params[4]
        reportPath      = params[5]
        blackboxEnabled = params[6]
        bltueEnabled    = params[7]

        self.__prepareForRun(reportPath, blackboxEnabled, bltueEnabled)

        if ".xml" in reportPath:
            self._parser.AddTestResult(reportPath)

        # run IronPython, NTH or SX test case
        self.__testRunner.run([tcDir, tcModule, tcClass, tcMethod, tcId])

    def __runXAML(self, params):
        """Commands test runner to run given workflow XAML

            Parameters

            params contains a list of

            xamlPath            workflow XAML file path
            reportPath          test result file path
            blackboxEnabled     whether blackbox is enabled/disabled
            trackingEndpoint    workflow tracking endpoint address
        """
        # get test data parameters
        xamlPath        = params[0]
        reportPath      = params[1]
        blackboxEnabled = params[2]

        # trackingEndpoint is optional
        if len(params) >= 4:
            trackingEndpoint = params[3]
        else:
            trackingEndpoint = None

        self.__prepareForRun(reportPath, blackboxEnabled)

        # run XAML test case
        self.__testRunner.run([xamlPath, trackingEndpoint])

    def __quit(self):
        """Performs all actions required for terminating Framework."""
        # when quitting we don't need to store current command
        self.__currentCommand = ''

        # terminate test execution if necessary
        self.__stop()

        # close phone connetions
        # Close remote connections before closing main connection. Closing main connection
        # calls Dispose for connection manager!
        if core.FW_conf['remote_connection'] != None:
            for remote in core.FW_conf['remote_connection']:
                remote.closeConnection(forced = True)

        if core.FW_conf['connection']:
            core.FW_conf['connection'].closeConnections()

        # disconnect socket
        self.fwConn.disconnect()

        # cancel task token so that message listener task shutdowns
        self.__cancelationToken.Cancel()

    def __stop(self):
        """Stops current test execution."""
        # tell test runner to stop
        core.FW_conf['should_stop'] = True

        # test execution flag --> False
        self.__executionOngoing = False

        # call test run end because when stop or quit comes, test run end command is missing
        self.__testRunEnd()

    def __settings(self, params):
        """Action for ProtocolMessages.CMD_SETTINGS.

            Parameters

            params contains

            settingsFile    settings file name (this can be set to '' if there is no setting file that needs to be loaded)
        """
        time.sleep(1) # Wait for settings to be fully updated

        settingsFile = params[0]
        if (settingsFile != ''):
            core.FW_conf['settings'].loadSettings(\
                    os.path.basename(settingsFile),
                    os.path.dirname(settingsFile) + '\\')

        # update debug level from new settings
        debug.setLevel(core.FW_conf['settings'].TestRun.DebugLevel)

        # Initialize BlackBox wcf client if blackbox enbabled
        if core.FW_conf['settings'].TestRun.EnableBlackBox and core.FW_conf['blackbox'].client is None:
            core.FW_conf['blackbox'].initBlackBoxClient()

        if core.FW_conf['settings'].TestRun.EnableVideoRecorder and core.FW_conf['blackbox'].videoClient is None:
            core.FW_conf['blackbox'].initVideoRecorderClient()

        # check whether remote phone connection(s) has changed
        # if it has, close connection so that it will be reopened in the next
        # command that requires connection
        if core.FW_conf['remote_connection'] != None and len(core.FW_conf['remote_connection']) > 0:
            for remote in core.FW_conf['remote_connection']:
                if not remote.current_connection or remote.current_connection != remote.connSettings.Connection:
                    remote.closeConnection(True)

        # update backend_enabled value so that it will be properly handled on the next testcase setup
        core.FW_conf['backend_enabled'] = core.FW_conf['settings'].TestRun.EnablePOXBackend

    def __capture(self, params):
        """Action for ProtocolMessages.CMD_CAPTURE.

            Parameters

            params contains

            resultPath    path where result xml must be stored
        """
        resultPath = params[0]

        core.FW_conf['test_result_dir'], core.FW_conf['test_result_name'] = os.path.split(resultPath)

        self.__testRunner.runDisplayCapture()

    def __testRunEnd(self):
        """Performs all test run end related actions."""
        # stop current measurement if battery is available
        if core.FW_conf['blt_ue'] is not None and core.FW_conf['blt_ue'].isEnabled():
            core.FW_conf['blt_ue'].stopCurrentMeasuring()

        self._parser.Generate()

        # stop logging
        if not (core.FW_conf['connection'].isFullBlackBox() and core.FW_conf['blackbox_enabled']) and \
           core.FW_conf['connection']._tab:
            core.FW_conf['connection']._tab._stopLogging()

        # set Granite Server to inactive state
        # NOTE: AssertionError may come when FW is shutting down
        if core.FW_conf['remote_connection'] != None:
            for remote in core.FW_conf['remote_connection']:
                try:
                    remote.termGraniteServer()
                except AssertionError:
                    pass

    def __initBltUe(self):
        """Initializes BLT-UE if not already initialized.

            Parameters

            If FW has been killed, testing using GPIB/PowerSupplies needs to be reinitialized.
        """
        if core.FW_conf['blt_ue']:
            if not core.FW_conf['blt_ue'].isEnabled():
                core.FW_conf['blt_ue'].setupBltUeTesting()

    def __disableLockScreen(self):
        """Disables lock screen by modifying database and rebooting device.
        """
        core.FW_conf['connection']._tab._disableLockScreen()

    def __executeStep(self, params):
        """Executes given test step.
        """
        testStep = params[0]

        try:
            # set minimal interval to UI event waiting
            core.FW_conf['connection']._tab.overrideEventInterval = 200

            exec(testStep.replace("self.", "core.FW_conf['connection']."))
        except Exception, err:
            debug.err('Unable to execute: "%s", Error: "%s"' % (testStep, str(err)))
        finally:
            core.FW_conf['connection']._tab.overrideEventInterval = 0

    def __messageListener(self):
        """Task for listening in socket for new protocol commands."""
        while True:
            command, params = self.fwConn.receiveMessage()

            if self.__commandDict.has_key(command):
                # create execution method name
                executionCommand = eval('self.THROW_%s' % self.__commandDict[command])

                # wait for text execution to stop with other commands than quit and stop
                if not command in [ProtocolMessages.CMD_QUIT,
                                   ProtocolMessages.CMD_STOP]:
                    # store current command for later GUI response
                    self.__currentCommand = command
                    self.__stopCommand = ''

                    while self.__executionOngoing:
                        time.sleep(1)

                    # execute command in run thread
                    self.__createRunThread()

                    runParameters = RunParameters()
                    runParameters.command = executionCommand
                    runParameters.params = params
                    self.__runThread.Start(runParameters)
                else:
                    # store quit/stop command for later GUI response
                    self.__stopCommand = command

                    # execute command in thread pool (non-blocking)
                    Threading.ThreadPool.QueueUserWorkItem(Threading.WaitCallback(executionCommand), params)

            # we have to wait until quit is finished
            if command == ProtocolMessages.CMD_QUIT:
                while not self.__cancelationToken.Token.IsCancellationRequested:
                    time.sleep(0.1)

            # exit from task if cancellation was requested
            if self.__cancelationToken.Token.IsCancellationRequested:
                self.__cancelationToken.Token.ThrowIfCancellationRequested()
                break

    def __createRunThread(self):
        """Creates run thread."""
        self.__stopRunThread()

        if not self.__runThread:
            self.__runThread = Thread(ParameterizedThreadStart(runCommand))
            self.__runThread.IsBackground = True

    def __joinRunThread(self):
        """Joins run thread to main thread."""
        if self.__runThread and \
           self.__runThread.IsAlive:
            self.__runThread.Join()

    def __stopRunThread(self):
        """Stops run thread."""
        # NOTE: this is just in case here, thread is finished every time so it should not be alive anymore here
        if self.__runThread and \
           self.__runThread.IsAlive:
            self.__runThread.Abort()

        self.__runThread = None

    def FWCommandLoop(self):
        """Runs message listener in own Task."""
        self.fwConn.startServer(port = self.__serverPort)

        # start message listener in own Task
        task = Task(self.__messageListener)
        task.Start()

        try:
            task.Wait(86400000, self.__cancelationToken.Token)
        except Exception, err:
            if not task.Exception is None:
                debug.out('Error in message listener task: %s' % task.Exception.GetBaseException())
            else:
                debug.out('Message listener terminated: %s' % str(err))

    def sendWaitMessage(self, timeout, comment):
        """Sends wait message to GUI.

            Parameters

                timeout     timeout in seconds
                comment     comment in string
        """
        self.fwConn.sendWaitMessage(timeout, comment)

    def sendErrorMessage(self, message):
        """Sends error message to GUI.

            Parameters

                message     error message in string
        """
        self.fwConn.sendErrorMessage(message)


class RunParameters(object):
    """Parameters class for run thread."""
    command = None
    params = None

def runCommand(runParameters):
    """Function for running commands in separate run thread."""
    runParameters.command(runParameters.params)


