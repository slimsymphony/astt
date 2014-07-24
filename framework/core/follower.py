import core
from core import phone
from core import uitestcase

import clr, time, os, types
from time import gmtime, strftime
from utils.nodeutils import NodeUtils
from core.reporting.xslt_report_generator import XSLTTestReportGenerator
from utils.file_utils import getFileList

clr.AddReference('LeaderFollowerInterface')
from Nokia.Granite.IPC.Clients.LeadFollower import GraniteFollowerClient
from Nokia.Granite.IPC.Interfaces import *

clr.AddReference('System.ServiceModel')
clr.AddReference('System.Net')
from System.Net import Dns

clr.AddReference('System')
from System import DateTime

RESULT_UIFREEZE = 'UI Freeze'
RESULT_FREEZE = 'Freeze'
RESULT_PASSED = 'Passed'
RESULT_NORUN = 'No run'
RESULT_RESET = 'Dump files'
RESULT_FETCHING_XFILES = 'Crashfiles fetching not finished'

class Follower(object):

    def __init__(self, testRunner):
        """ initialize follower instance """

        self.serviceUrl = None
        self.serviceIps = []
        self.gfc = GraniteFollowerClient()
        self.runner = testRunner
        self.__resultGenerator = XSLTTestReportGenerator()
        self.allowUsbConnection = False
        
        # if executed from cmd line
        if core.FW_conf['follower'] != True:
            self.serviceUrl = core.FW_conf['follower']
            debug.brf('Connecting Leader @ %s' % self.serviceUrl)
            
        else:
            if len(core.FW_conf['settings'].TestRun.MTBFServiceURL) < 1:
                debug.brf('Service URL not defined, cannot initialize')
                raise Exception('No MTBF service address defined')

            try:
                debug.brf('Connecting Leader @ %s' % core.FW_conf['settings'].TestRun.MTBFServiceURL)
                self.serviceIps = Dns.GetHostAddresses(core.FW_conf['settings'].TestRun.MTBFServiceURL)
                for ip in self.serviceIps:
                    debug.out('Service ip %s' % ip.ToString())
            except:
                debug.brf('Could not find service with address %s' % core.FW_conf['settings'].TestRun.MTBFServiceURL)

            debug.out("net.tcp://%s:8022/GraniteLeadService" % core.FW_conf['settings'].TestRun.MTBFServiceURL)
            if len(self.serviceIps) > 0:
                self.serviceUrl = self.serviceIps[0].ToString()
                debug.out('Using %s for service url' % self.serviceUrl)
            else:
                self.serviceUrl = core.FW_conf['settings'].TestRun.MTBFServiceURL

    def connectToService(self):
        """ connects to Granite Leader Service """

        self.gfc.Connect("net.tcp://%s:8022/GraniteLeadService" % self.serviceUrl)
        self.gfc.SubscribeToService(Dns.GetHostName())
        #self.gfc.AddTaskToLeaderQueue(ConfigurationRequestTask(str(id(self))))
        debug.brf('Follower connected to Leader and waiting for test cases')

    def executionLoop(self):
        """ after connection has been established, execution loop will listen to service and execute cases/steps """ 
        
        debug.out("Granite follower@" + Dns.GetHostName() + " connecting to " + self.serviceUrl)

        connected = False
        keepAliveInterval = 10 # counter
        keepAlive = 10           # keepalive reset value
        while True:
            core.FW_conf['connection'].sendWaitMessageToMarbleGUI(1, 'Follower execution loop..')
            
            if not connected:
                core.FW_conf['connection'].sendWaitMessageToMarbleGUI(30, 'Connecting to service')
                try:
                    self.connectToService()
                    connected = True
                except Exception as e:
                    debug.brf('Could not connect to Granite Lead Service. Trying again..')
                    core.FW_conf['connection'].sendWaitMessageToMarbleGUI(1, 'Test execution sleeping for %s seconds' % 1)
                    time.sleep(1)
            
            # Wait for test case, keep connection alive
            elif self.gfc.IsConnectedToService == False or self.gfc.CurrentTestCase[0] == None:

                time.sleep(1)
                if keepAliveInterval <= 0:

                    reconnect = False
                    if self.gfc.IsConnectedToService == False:
                        debug.brf('Not connected to service, trying to reconnect')
                        reconnect = True
                        ret = -1
                    else:
                        ret = self.gfc.KeepAlive()

                    if ret == -1:
                        debug.brf('Communication channel was lost, reconnecting..')
                        reconnect = True

                    elif ret == 1:
                        debug.brf('Communication channel OK, not registered..')
                        reconnect = True

                    if reconnect:
                        if self.gfc.Reconnect():
                            debug.brf('Reconnected.')
                        else:
                            debug.brf('Could not reconnect.. trying again in 1 sec')
                            keepAliveInterval = 0
                    else:
                        keepAliveInterval = keepAlive

                else:
                    keepAliveInterval -= 1
                continue

            else:
                self.gfc.ScreenCaptures.Clear()
                self.gfc.CaseResult = "Not executed";
                self.gfc.ResultLink = "";
                self.gfc.ResultDir = "";
                self.gfc.ExecutionTime = "0";
                
                self.runner._MarbleTestRunner__runObject(self, self.gfc.CurrentTestCase, core.FW_conf['tc_filter'])
                debug.brf('====== finished tc object =======')
                
                if not self.gfc.ExecutionSuccess: # if execution queue processing had problems, abort the case
                    self.abortCurrentTestCase('Test case was not finished successfully')

                self.gfc.TearDownFinished = True # needs to be set here as remote phone teardown will take some time

                # generate HTML report from all executed test cases
                self.__resultGenerator.createReport(getFileList(os.path.join(core.FW_conf['test_result_dir'], 'xml'), fileExt = '.xml'),
                                       core.FW_conf['test_result_dir'])

    def isConnected(self):
        return self.gfc.IsConnectedToService

    def currentTestCase(self):
        return self.gfc.CurrentTestCase[0]

    def abortCurrentTestCase(self, msg=None):
        """ handles abortion of the testcase """
        self.gfc.AbortCurrentTestCase()
        # add captured images to result
        phone = core.FW_conf['connection']
        for i in range(1, len(phone._capturedStillImages) + 1 ):
            debug.brf(phone._capturedStillImages[i-1])
            relativeFileName = os.path.join('videos',phone._capturedStillImages[i-1])
            core.FW_conf['follower_client'].ScreenCaptures.Add(relativeFileName)
        phone._clearStillImageArray()
        if msg:
            debug.err('Case aborted: %s' % msg)
        else:
            debug.err('Case aborted')

    
    def initializeTestCase(self, tc_attrs):
        """ Initializes a test case object
        
        Parameters
        tc_attrs (tuple of strings)    :     [class, subarea , feature, method, tcId, docstring]
        
        Returns
        test case object

        """
        
        if len(tc_attrs) != 6:
            debug.brf('Failed to create test case, not enough attributes')
            return False

        debug.brf('Test %s' % tc_attrs[4])
        
        # this is the method structure for to-be created test case object
        def structure(self):
            import core
            import time, re
            execution_start_time = time.time()
            debug.out(self.subarea)
            debug.out(self.feature)
            
            keepAliveInterval = 10
            keepAlive = 10
            printWait = False
            leader_touch_interval_timer = None

            fc = self.followerClient

            fc.CaseResult = RESULT_NORUN
            fc.ExecutionTime = "0"
            fc.ResultLink = ''
            fc.ResultDir = os.path.split(core.FW_conf['test_result_dir'])[1] # save folder name as result dir

            

            path, folder = os.path.split(core.FW_conf['test_result_dir'])  # get the result folder name
            try:
                relativeFileName = os.path.join('videos',os.path.splitext(core.FW_conf['test_result_name'])[0] + '.avi')
                videoFile = os.path.join(core.FW_conf['test_result_dir'], relativeFileName)
                if os.path.isfile(videoFile): # change video address if video file is found
                    fc.ResultLink = relativeFileName
            except Exception as e:
                debug.brf('Could not add video to result: %s' % e.message)

            self.follower_touch_interval_timer = 0
            
            if core.FW_conf['blackbox'] != None and core.FW_conf['blackbox'].isVideoRecorderAvailable():
                self.motionFrames = core.FW_conf['blackbox'].getCountMotionFrames()
                self.motionFramesLast = self.motionFrames
                self.uiFreezeDetected = False
            else:
                self.motionFrames = None
                self.uiFreezeDetected = False

            step = ''
            while True:
                
                # if stop is requested, finish the queue
                if fc.StopCurrentTestCase:
                    if fc.ExecutionQueueLen > 0:
                        debug.brf('Testcase stop requested. Processing Execution queue (%s tasks left) .. ' % fc.ExecutionQueueLen)

                    else: # execution will be stopped to this
                        debug.brf('Testcase stop requested, teardown execution..')
                        fc.StopCurrentTestCase = False
                        
                        if self.uiFreezeDetected:
                            # swipe a bit to see if it causes motion

                            yCoordinate = int(800/2.5)
                            self._touch.drawLine((480 -2, yCoordinate), (480 - 100, yCoordinate), stepSize = 30)
                            self._run('Move screen a bit to see is UI freezed', testStepReporting = False)
                            self.delay(1000)

                            # try keylock toggle
                            if self.motionFramesLast == core.FW_conf['blackbox'].getCountMotionFrames():
                                self.select('KEYCODE_POWER')
                                self.delay(3000)

                            # if potentially a freeze, press back still to see if it wakes the phone
                            if self.motionFramesLast == core.FW_conf['blackbox'].getCountMotionFrames():
                                self.select('KEYCODE_BACK')
                                self.delay(2000)    
                            
                            # if back / keylock toggle does not help, then it's a freeze
                            if self.motionFramesLast == core.FW_conf['blackbox'].getCountMotionFrames():
                                self.warn('UI Freeze detected')
                                fc.CaseResult = RESULT_UIFREEZE
                                try:
                                    self.resetPhone('Freeze detected in Follower')
                                except:
                                    pass # resetPhone raises testexception, which is not wanted here.
                           
                        if int(core.FW_conf['settings'].TestRun.DumpFileFetchInterval) > 0:
                            # fetch Dump files. allow USB connection temporarily
                            self.follower.allowUsbConnection = True

                            if fc.CaseResult == RESULT_NORUN:
                                fc.CaseResult = RESULT_FETCHING_XFILES

                            dumpStatus, dumpfiles = self.follower.getDumpFiles()

                            self.follower.allowUsbConnection = False

                            if dumpStatus == 1:
                                if int(core.FW_conf['settings'].TestRun.DumpFileFetchInterval) == 1:
                                    self.warn('Dump files found after execution of current case')
                                else:
                                    self.warn('Dump files were generated during the execution of last %s cases' % str(core.FW_conf['settings'].TestRun.DumpFileFetchInterval))
                                    
                                # Dump files found, set result as 'Reset'
                                if fc.CaseResult in [RESULT_PASSED, RESULT_NORUN, RESULT_FETCHING_XFILES]:
                                    fc.CaseResult = RESULT_RESET
                                else:
                                    fc.CaseResult = fc.CaseResult + ' with ' + RESULT_RESET

                            elif dumpStatus == -1:
                                self.warn('Dump files check could not be done, no connection')
                                if fc.CaseResult == RESULT_UIFREEZE:
                                    fc.CaseResult = fc.CaseResult + ' and could not create connection to phone'
                                else:
                                    fc.CaseResult = RESULT_FREEZE

                        debug.brf('TC Execution stopped')
                        
                        if fc.CaseResult == RESULT_NORUN or fc.CaseResult == RESULT_FETCHING_XFILES:
                           fc.CaseResult = RESULT_PASSED
                           
                        m, s = divmod((time.time() - execution_start_time), 60)
                        h, m = divmod(m, 60)
                        debug.brf("Execution took %d:%02d:%02d" % (h, m, s))
                        #et = '%d:%02d:%02d' % (h, m, s)
                        fc.ExecutionTime = '%02d' % (time.time() - execution_start_time)
                        fc.EndTime =  DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss")
                        #machine_name = Dns.GetHostName()

                        # add captured images to result
                        for i in range(1, len(self._capturedStillImages) + 1 ):
                            debug.brf(self._capturedStillImages[i-1])
                            relativeFileName = os.path.join('videos',self._capturedStillImages[i-1])
                            fc.ScreenCaptures.Add(relativeFileName)
                        self._clearStillImageArray()

                        #self.follower.blindExit()
                        fc.CurrentTestCase = None
                        fc.ExecutionSuccess = True 
                        break

                if fc.ExecutionQueueLen > 0:
                    keepAliveInterval = keepAlive # reset keepalive counter
                    executionData = fc.ExecutionQueue
                    debug.out("Task: %s / Step: %s" % (type(executionData), executionData.TestStep))
                    
                    # print out test step if changed
                    if step != executionData.TestStep:
                        step = executionData.TestStep
                        if not ('delay' in step or 'sleep' in step or 'comment' in step): # avoid excess debug
                            self.comment(step)

                    if core.FW_conf['blackbox'] != None and executionData.TestStep != '':
                        core.FW_conf['blackbox'].videoRecording_SetText(executionData.TestStep)
                    
                    # String Tasks will be executed as string
                    if type(executionData) == StringTask:
                        try:
                            exec(executionData.ExecString)
                            # if exec went fine, check if it was new variable and inform service that it's here
                            r = re.match('([\w\.]*) *(=)?[^==]', executionData.ExecString)
                            if r and r.group(1) and r.group(2):
                                debug.out('registering variable %s' % r.group(1))
                                try:
                                    fc.AddVariable(r.group(1))
                                except:
                                    debug.err('exception, tried to register a variable to leader. %s' % e.message)

                        except Exception as e:
                            debug.err('exception with string "%s" execution: %s' % (executionData.ExecString, e.message))

                            if executionData.ExecString.startswith('self.referencePhone') or \
                               executionData.ExecString.startswith('self.blackbox'):
                                fc.ClientFail(fc.GetClientId(), "Failed: referencePhone/blackbox command failed tried to exec(%s)" % executionData.ExecString, executionData.TestStep)

                    # input task will load received xml and try using input
                    elif type(executionData) == InputTask:
                        try:
                            inputmode = executionData.Mode
                            phoneOrientation = executionData.Orientation
                            delayBetween = executionData.DelayBetweenPresses
                            if executionData.Evaluate:
                                evaluated = self.follower.getEvaluatedString(executionData.InputString, executionData.ToBeEvaluatedSettings)
                                if len(evaluated) == 0:
                                    self.warn("\n\n *** Input string evaluate failed. Check does client have settings defined for inputting %s ** \n\n" % executionData.InputString)
                                    fc.ClientFiasco(fc.GetClientId(), "Input string evaluate failed. Check does client have settings defined for inputting %s " % executionData.InputString, executionData.TestStep)
                                else:
                                    self.input(evaluated, mode=inputmode, orientation=phoneOrientation, delayBetweenPresses=delayBetween)
                            else:
                                self.input(executionData.InputString, mode=inputmode, orientation=phoneOrientation, delayBetweenPresses=delayBetween)

                        except Exception as e:
                            self.warn('exception with input execution: %s' % e.message)
                            fc.ClientFiasco(fc.GetClientId(), "\n\n ** Input string failed. Reason %s **\n\n" % e.message, executionData.TestStep)

                    elif type(executionData) == TouchTask:
                        
                        if self.motionFrames != None:
                            self.motionFrames = core.FW_conf['blackbox'].getCountMotionFrames()

                        # delay between touches not in use (False). 
                        if executionData.Interval != 0 and self.follower_touch_interval_timer != 0: 
                            follower_interval = time.time() - self.follower_touch_interval_timer
                            debug.out('Leader   touch interval %f' % executionData.Interval)
                            debug.out('Follower touch interval %f' % follower_interval)
                            if follower_interval < executionData.Interval:
                                debug.brf('Touch execution. Delayed %d ms (step: %s)' % (int(( executionData.Interval - follower_interval )*1000), executionData.TestStep))
                                self.delay(int(( executionData.Interval - follower_interval )*1000), False)
                            else:
                                debug.brf('Touch execution. (step: %s)' % executionData.TestStep)
                                
                        self.keyPresses.append(NodeUtils(executionData.TouchData.ToString()))
                        core.FW_conf['connection']._Phone__purgeKeyPresses()
                        # self._run('purge keypresses',testStepReporting=False) # wont do anything in blackbox mode?
                        self.follower_touch_interval_timer = time.time() # reset interval counter

                        if self.motionFrames != None:
                            framesAfter = core.FW_conf['blackbox'].getCountMotionFrames() 
                            if self.motionFrames == framesAfter and framesAfter == self.motionFramesLast:
                                self.uiFreezeDetected = True
                            else:
                                self.uiFreezeDetected = False

                            self.motionFramesLast = self.motionFrames
                        
                    elif type(executionData) == ImageDictSaveTask:
                        try:
                            for kvp in executionData.ImageDict:
                                phone.image_dict[kvp.Key] = kvp.Value
                            
                        except Exception as e:
                            debug.brf('error with image dict load: %s'  % e.message)

                    elif type(executionData) == LayoutMapSaveTask:
                        try:
                            debug.out(executionData.LayoutRepresentation.ToString())
                            d = eval(executionData.LayoutRepresentation.ToString())
                            self.uiState.vkb._VirtualKeyboard__layoutMaps = d

                        except Exception as e:
                            debug.brf('error with layout maps save: %s'  % e.message)

                    elif type(executionData) == RemotePhoneTask:
                        try:
                            if len(self.remote) > 0:
                                debug.out('remote task: %s, %r (%s) %r (%s)' % (executionData.Method.ToString(), \
                                                                                 executionData.Args, type(executionData.Args.ToString()), \
                                                                                 executionData.Kwargs, type(executionData.Kwargs.ToString()) ) )

                                ar = [] # collect tuple type of args for method call
                                for j in range(len(executionData.Args)):
                                    if j in executionData.ArgsEvalIndex:  # if argument needs to be evaluated
                                        debug.brf('Getting values for %s from settings..' % executionData.Args[j])
                                        evaluated = self.follower.getEvaluatedString(executionData.Args[j], executionData.ToBeEvaluatedSettings)
                                        debug.brf('%s = "%s"' % (executionData.Args[j], evaluated))
                                        if len(evaluated) == 0:
                                            self.warn("\n\n *** self.remote call argument evaluation failed. Check does client have all settings defined (%s) ** \n\n" % executionData.Args[j])
                                            fc.ClientFiasco(fc.GetClientId(), "self.remote call argument evaluation failed. Check does client have all settings defined (%s)" % executionData.Args[j], executionData.TestStep)
                                        else:
                                            ar.append(evaluated)
                                    else:
                                        # check if param needs to be converted to a tuple
                                        a = executionData.Args[j]
                                        if type(a) == types.StringType and len(a) > 0 and "(" in a[0] and ")" in a[-1] and "," in a:
                                            try:
                                                e = eval(tuple([a])[0])
                                                if type(e) == types.TupleType:
                                                    ar.append(e)
                                                else:
                                                    ar.append(a)
                                            except:
                                                fc.ClientFiasco(fc.GetClientId(), "self.remote call argument \"%s\" evaluation failed on step %s" % a, executionData.TestStep)
                                        else:
                                            ar.append(a)

                                kwa = {} # extract kwargs as python dict
                                i = 0
                                for j in executionData.Kwargs:
                                    if i in executionData.KwargsEvalIndex: # if argument needs to be evaluated
                                        debug.brf('Getting value of %s from settings..' % i.Value)
                                        evaluated = self.follower.getEvaluatedString(i.Value, executionData.ToBeEvaluatedSettings)
                                        debug.brf('%s = "%s"' % (i.Value, evaluated))
                                        if len(evaluated) == 0:
                                            self.warn("\n\n *** self.remote kwargument call evaluation failed. Check does client have all settings defined (%s) ** \n\n" % i.Value)
                                            fc.ClientFiasco(fc.GetClientId(), "self.remote call kwargument evaluation failed. Check does client have all settings defined (%s)" % i.Value, executionData.TestStep)
                                        else:
                                            kwa[j.Key] = evaluated
                                    else:
                                        kwa[j.Key] = j.Value
                                    i += 1

                                # get the method (last) via the call chain
                                method = None
                                for m in executionData.Method.ToString().split('.'):
                                    if method:
                                        method = getattr(method, m)
                                    else:
                                        method = getattr(self.remote, m)

                                method(*ar, **kwa)

                            else:
                                self.warn("\n\n *** Remote phone method execution, but no remotes found")
                                fc.ClientFail(fc.GetClientId(), "Remote phone method execution, but no remotes found", executionData.TestStep)
                            
                        except Exception as e:
                            debug.brf('error with remote phone method execution: %s'  % e.message)
                            fc.ClientFail(fc.GetClientId(), "Failed: Remote phone: %s" % e.message, executionData.TestStep)
                            
                    elif type(executionData) == VirtualPhoneTask:
                        try:
                            if self.backendAvailable:
                                debug.brf('virtual phone task: %s, %r (%s) %r (%s)' % (executionData.Method.ToString(), \
                                                                                 executionData.Args, type(executionData.Args.ToString()), \
                                                                                 executionData.Kwargs, type(executionData.Kwargs.ToString()) ) )


                                ar = [] # collect tuple type of args for method call
                                for j in range(len(executionData.Args)):
                                    if j in executionData.ArgsEvalIndex:  # if argument needs to be evaluated
                                        debug.brf('Getting value of %s from settings..' % executionData.Args[j])
                                        evaluated = eval(executionData.Args[j])
                                        debug.brf('%s = "%s"' % (executionData.Args[j], evaluated))
                                        if len(evaluated) == 0:
                                            self.warn("\n\n *** self.virtualPhone argument evaluation failed. Check does client have setting %s ** \n\n" % executionData.Args[j])
                                            fc.ClientFiasco(fc.GetClientId(), "self.virtualPhone argument evaluation failed. Check does client have setting %s" % executionData.Args[j], executionData.TestStep)
                                        else:
                                            ar.append(evaluated)
                                    else:
                                        ar.append(executionData.Args[j])

                                kwa = {} # extract kwargs as python dict
                                i = 0
                                for j in executionData.Kwargs:
                                    if i in executionData.KwargsEvalIndex: # if argument needs to be evaluated
                                        debug.brf('Getting value of %s from settings..' % i.Value)
                                        evaluated = eval(i.Value)
                                        debug.brf('%s = "%s"' % (i.Value, evaluated))
                                        if len(evaluated) == 0:
                                            self.warn("\n\n *** self.virtualPhone kwargument evaluation failed. Check does client have setting %s ** \n\n" % i.Value)
                                            fc.ClientFiasco(fc.GetClientId(), "self.virtualPhone kwargument evaluation failed. Check does client have setting %s" % i.Value, executionData.TestStep)
                                        else:
                                            kwa[j.Key] = evaluated
                                    else:
                                        kwa[j.Key] = j.Value
                                    i += 1

                                method = getattr(self.virtualPhone, executionData.Method.ToString())
                                method(*ar, **kwa)

                            else:
                                self.warn("\n\n *** Virtual Phone method execution, but Virtual Phone not enabled")
                                fc.ClientFail(fc.GetClientId(), "Virtual Phone method execution, but Virtual Phone not enabled", executionData.TestStep)
                            
                        except Exception as e:
                            debug.brf('error with virtual phone method execution: %s'  % e.message)
                            fc.ClientFail(fc.GetClientId(), "Failed: Virtual Phone: %s" % e.message, executionData.TestStep)
                            
                    else:
                        debug.err('execution data type %s does not have handler' % type(executionData))
                        fc.StopCurrentTestCase = True
                        fc.CaseResult = 'No handler for %s' % type(executionData)
                        
                else:
                    if printWait and keepAliveInterval <= 0:
                        debug.brf('waiting for execution steps..')
                        printWait = False

                    if keepAliveInterval <= 0:
                        core.FW_conf['connection'].sendWaitMessageToMarbleGUI(10, 'Leader service ping..')
                        
                        try:
                            subscribed = fc.KeepAlive()
                            if subscribed == 1:
                                debug.brf('Communication channel OK, but not subscribed. Stop case and subscribe..')
                                self.gfc.SubscribeToService(Dns.GetHostName())
                                fc.StopCurrentTestCase = True
                                fc.CaseResult = 'Interrupted'
                            elif subscribed == -1:
                                debug.brf('Communication channel lost. Stop case..')
                                self.gfc.SubscribeToService(Dns.GetHostName())
                                fc.StopCurrentTestCase = True
                                fc.CaseResult = 'Interrupted'
                            else:
                                keepAliveInterval = keepAlive
                                printWait = True
                        except:
                            debug.brf('Communication channel was lost. Stopping test case.')
                            fc.StopCurrentTestCase = True

                    core.FW_conf['connection'].sendWaitMessageToMarbleGUI(1, 'Test execution sleeping for %s seconds' % 1)
                    time.sleep(0.2)
                    keepAliveInterval -= 0.2
                    
        # create a test case object        
        tc = type(tc_attrs[0], (uitestcase.UITestCase,), {\
            'subarea': tc_attrs[1], \
            'feature': tc_attrs[2] \
        })
        
        structure.__name__ = tc_attrs[3]
        self.tcId = tc_attrs[4]
        structure.__doc__ = '%s\n\n%s' % (tc_attrs[5], self.tcId)
        setattr(tc, structure.__name__, structure) # give name to test method
        setattr(tc, 'tcId', tc_attrs[4])  # test case id
        setattr(tc, 'followerClient', self.gfc)  # saves reference to followerclient instance
        setattr(tc, 'follower', self) # save reference to this instance for getting the Dump files
        
        debug.out('initialized test case %s' % self.tcId)
        # self.tc = tc # this does not contain scripting methods / uiState, tc will be set again in test case to this callback interface
        self.tcDetails = tc_attrs
        return tc

    def getEvaluatedString(self, aString, toBeEvaluatedSettings):
        """ translates any found settings from a string and replaces them with environment setting """
        tc = core.FW_conf['current_testcase']
        toBeEvaluated = toBeEvaluatedSettings.replace(' ', '')
        toBeEvaluated = toBeEvaluated.replace('\n', '')
        toBeEvaluated = toBeEvaluated.split(',')

        debug.brf('evaluate %s' % aString)
        
        for setting in toBeEvaluated:
            if setting in aString:
                evaluated = eval(setting.replace('self.', 'tc.'))
                if len(evaluated) == 0:
                    return ""
                else:
                    aString = aString.replace(setting, evaluated)
            
        return aString


    def getDumpFiles(self):
        """ Create connection to phone, fetch Dump files and close the connection """
        #this requires core.FW_conf['current_testcase'].follower.allowUsbConnection to be enabled
        dumpFiles = []
        
        ret = 0 # 0 = No Dump files, 1 = Dump files found, -1 = No connection could be made

        if core.FW_conf['blackbox'] and core.FW_conf['blackbox_enabled']:
            debug.brf('Creating connection and fetching Dump files in Follower mode..')
        else:
            debug.brf('Whitebox mode. Creating connection and fetching Dump files in Follower mode..')

        ret, dumpFiles = core.FW_conf['current_testcase']._getCrashDumpsInBlackBox()
        
        if ret == None:
            core.FW_conf['connection'].comment('Dump files have not been fetched')    

        if ret == 1:
            core.FW_conf['connection'].comment('Dump files found')    
        elif ret == 0:
            core.FW_conf['connection'].comment('Dump files not found')    
        elif ret == None: # dumps not fetched, eiher because those are disabled or fetching interval is not met
            core.FW_conf['connection'].comment('Dump files have not been fetched')    
        else:
            debug.err('WARNING: Could not create connection for Dump files fetching!')

        return ret, dumpFiles

    def __pressBackInLoop(self, presses=10):
        """ Press back until no movement in screen 
            Param
                presses :     how many times at maximum back will be pressed
            Return:
                True    :     no movement after n back presses
                False   :     maximum presses reached and still movement
        
        """

        for i in range(presses):
            motionFramesStart = core.FW_conf['blackbox'].getCountMotionFrames()
            core.FW_conf['connection'].comment('Back press..')
            core.FW_conf['connection']._pressKey('KEYCODE_BACK', waitUntilNoUIevents=False)
            core.FW_conf['connection']._run('follower exit: back press')
            core.FW_conf['connection'].delay(500)
            if core.FW_conf['blackbox'].getCountMotionFrames() == motionFramesStart: # no movement
                return True

        return False

    def __closeLastAppFromAppSwitcher(self):
        """ open app switcher and close last application """
        # open app switcher
        core.FW_conf['connection'].comment('Closing last application from application switcher')
        core.FW_conf['connection'].comment('Long back press..')
        core.FW_conf['connection']._pressKey('KEYCODE_BACK', 1500, waitUntilNoUIevents=False)
        core.FW_conf['connection']._run('follower exit: long back press')
        core.FW_conf['connection'].delay(1000)
        # swipe to close last app
        core.FW_conf['connection'].comment('Swipe to close last app..')
        y = self.__getScreenDimensions()[0] - 10
        fromPoint= (10, y)
        core.FW_conf['connection']._touch.drawLine( fromPoint, (self.__getScreenDimensions()[1] -2, y) )
        core.FW_conf['connection']._run('follower exit: gesture.swipe(%s,%s)'%( str(fromPoint), str(toPoint)))
        core.FW_conf['connection'].comment('Back press..')
        core.FW_conf['connection']._pressKey('KEYCODE_BACK', 500, waitUntilNoUIevents=False)
        core.FW_conf['connection']._run('follower exit: back press')

    def __getScreenDimensions(self):
        """ return height and width of the screen """
        return (800, 480)

    def exit(self, maxAttemps=5):

        for i in range(maxAttemps):

            if i >= maxAttemps-1:
                self.gfc.ClientFail(self.gfc.GetClientId(), "Follower exit maximum iteration reached", "follower.exit()")
                return

            if not self.__pressBackInLoop():
                self.__closeLastAppFromAppSwitcher()
        
            core.FW_conf['connection'].home()
            core.FW_conf['connection'].delay(4000)
       
            core.FW_conf['connection'].comment('Swipe a bit..')
            for j in range(2):
                yCoordinate = int(self.__getScreenDimensions()[0] / 2)
                fromPoint= (2, yCoordinate)
                toPoint = (30 , yCoordinate)
                core.FW_conf['connection']._touch.drawLine(fromPoint, toPoint, holdPenToStopScroll=True)
                core.FW_conf['connection']._run('follower exit: gesture.swipe(%s,%s)'%( str(fromPoint), str(toPoint)))
                core.FW_conf['connection'].delay(1000)
                core.FW_conf['connection']._touch.drawLine(fromPoint, toPoint, holdPenToStopScroll=True)
                core.FW_conf['connection']._run('follower exit: gesture.swipe(%s,%s)'%( str(fromPoint), str(toPoint)))
                if j == 0: 
                    core.FW_conf['connection'].delay(1000)
                    motionFramesStart = core.FW_conf['blackbox'].getCountMotionFrames()

            core.FW_conf['connection'].delay(1000)
            debug.brf('moves: %s' % str(core.FW_conf['blackbox'].getCountMotionFrames() - motionFramesStart))
            if core.FW_conf['blackbox'].getCountMotionFrames() - motionFramesStart >= 8: # @home
                core.FW_conf['connection'].home()
                return

            # lock screen?
            core.FW_conf['connection'].select('KEYCODE_POWER')
            core.FW_conf['connection'].delay(5000) # phone should be either on glance screen or standby screen
            motionFramesStart = core.FW_conf['blackbox'].getCountMotionFrames()
            core.FW_conf['connection'].select('KEYCODE_BACK')
            core.FW_conf['connection'].delay(2000)

            if motionFramesStart == core.FW_conf['blackbox'].getCountMotionFrames():
                # in glance screen, press lock again
                core.FW_conf['connection'].comment('Glance screen..')
                core.FW_conf['connection'].select('KEYCODE_POWER')
                core.FW_conf['connection'].delay(1000)
                core.FW_conf['connection'].select('KEYCODE_BACK')
                core.FW_conf['connection'].delay(1000)

            # not (anymore) in glance screen, flick up and enter code
            core.FW_conf['connection'].comment('Flick up')
            xCoordinate = int(self.__getScreenDimensions()[1] / 2)
            fromPoint = (xCoordinate, self.__getScreenDimensions()[0] - 10)
            toPoint = (xCoordinate, 10)
            core.FW_conf['connection']._touch.drawLine(fromPoint, toPoint)
            core.FW_conf['connection']._run('follower exit: gesture.swipe(%s,%s)'%( str(fromPoint), str(toPoint)))

            if core.FW_conf['settings'].TestRun.PhoneLockEnabled:
                core.FW_conf['connection'].delay(500)
                core.FW_conf['connection'].input.write('201426', mode='pin')

            core.FW_conf['connection'].delay(1000)
        