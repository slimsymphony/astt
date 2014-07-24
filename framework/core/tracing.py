""" Tracing for Granite """""

# Python library module imports
import sys, types, os, datetime, shutil, time
import clr
import random

from System import String, Char, DateTime


clr.AddReference('GraniteTraceConnection')
clr.AddReference('Nokia.RD.Framework')
clr.AddReference('Nokia.RD.Tracing')

from Nokia.RD.Tracing.TraceActivation import TraceActivator
from Nokia.RD import TextMessage
from Nokia.Granite.TraceConnection import GraniteTraceConnection

# Granite modules
import core
from core import debug
from interfaces.connection import GraniteConnectionException
from core.testcase_exceptions import StopTestException
#from interfaces.connection_interface import DisplayUpdateNtfListener




class Tracing(object):
    """Tracing features for Granite"""

    def __init__(self):
        """
            Create independent Granite trace connection and start recording that connection
        """
        self.graniteTraceConnection = GraniteTraceConnection()
        if not os.path.isdir(os.path.join(core.FW_conf['startup_path'], 'tempBLX')):
                os.makedirs(os.path.join(core.FW_conf['startup_path'], 'tempBLX'))
        self.binaryLog = os.path.join(core.FW_conf['startup_path'], 'tempBLX\\graniteLog.blx')
        self.graniteTraceConnection.CreateConnection(core.FW_conf['settings'].Main.TraceConnection, self.binaryLog)
        debug.brf('Start tracing connection %s' % core.FW_conf['settings'].Main.TraceConnection)
        self.counter = 0
        self.previousTestCase = None
        self.traceBlxDir = None
        self.taskCallDepthSet = None
        # monkey testing will not delete the log files
        if core.FW_conf['delete_success_blx'] and not core.FW_conf['memory_leak_detection'] and not core.FW_conf['settings'].TestRun.EnableMonkeyTesting:
            self.deleteBlx = True
        else:
            self.deleteBlx = None
                               
    def traceSaveBlxAndResumeTracing(self, caseId = None, memoryLeakDetection = None, testRunEnd = None, uiEnabled=True):
        """ Save recorded blx file and resume recording.  
            If there are USB and trace box connected only trace box BLX is saved.
            
            Parameters: caseId, testcase name which is used to name blx
                        testRunEnd, set this to True when last testcase of testrun is executed.
                        memoryLeakDetection, used to identify if memory leak detection is used
                        if memoryleak detection is enabled do not delete those successfull testcase blx files
                                                                    
        """
        if not self.previousTestCase: #if this is first testcase create new folder for trace data
            if core.FW_conf['settings'].TestRun.EnableMonkeyTesting:
                self.traceBlxDir = os.path.join(core.FW_conf['test_result_dir'], 'trace_data', 'monkey_testing') 
            else:
                # create folder for current test runs saved blx files, format YearMonthDayHourMinuteSecond
                dateTime = DateTime.Now.ToString("yyyyMMddHHmmss")
                self.traceBlxDir = os.path.join(core.FW_conf['test_result_dir'], 'trace_data', dateTime) 
            if not os.path.isdir(self.traceBlxDir):
                os.makedirs(self.traceBlxDir)

        else: #start splitting blx files
            resultBlx = ''
            if not memoryLeakDetection:
                resultBlx = os.path.join(self.traceBlxDir, self.previousTestCase)
            else:
                resultBlx = os.path.join(self.traceBlxDir, self.previousTestCase + '_Memory_Leak')
            
            if core.FW_conf['settings'].TestRun.EnableMonkeyTesting:
                monkeyRandomFile = '_'
                for i in range(7):
                    monkeyRandomFile = monkeyRandomFile + chr(random.randint(97,122))
                resultBlx = resultBlx + monkeyRandomFile

            #Check if this is last case of test set and if memoryleak detection is enabled
            if testRunEnd and memoryLeakDetection:
                if uiEnabled:
                    self.yapasGarbageCollector()
                    self.clearActivityScreen()
                self.markerToBlx(str(self.previousTestCase) + ' end iteration: ' + str(core.FW_conf['memory_leak_current_loop']))
                core.FW_conf['memory_leak_current_loop'] =  1
                self.graniteTraceConnection.SplitBlxFile()

                if self.counter == 0:
                    if not core.FW_conf['settings'].TestRun.EnableMonkeyTesting:
                        shutil.copy(self.binaryLog, resultBlx +'.blx')
                    self.counter = 2
                else:
                    filename = os.path.join(os.path.splitext(self.binaryLog)[0] + '_part_' + str(self.counter).zfill(2) + '.blx')
                    shutil.copy(filename, resultBlx +'.blx')
            elif not self.previousTestCase == caseId and memoryLeakDetection: #start of testrun or test loop
                if uiEnabled:
                    self.yapasGarbageCollector()
                    self.clearActivityScreen()
                if self.counter == 0:
                    self.markerToBlx(str(self.previousTestCase) + ' end iteration: ' + str(core.FW_conf['memory_leak_current_loop']))
                    core.FW_conf['memory_leak_current_loop'] =  1
                    self.graniteTraceConnection.SplitBlxFile()
                    shutil.copy(self.binaryLog, resultBlx +'.blx')
                    self.counter = 2
                else:
                    self.markerToBlx(str(self.previousTestCase) + ' end iteration: ' + str(core.FW_conf['memory_leak_current_loop']))
                    core.FW_conf['memory_leak_current_loop'] =  1
                    self.graniteTraceConnection.SplitBlxFile()
                    fileName = os.path.join(os.path.splitext(self.binaryLog)[0] + '_part_' + str(self.counter).zfill(2) + '.blx')
                    shutil.copy(fileName, resultBlx +'.blx')
                    self.counter += 1
            elif not memoryLeakDetection:  #'normal' testrun
                self.graniteTraceConnection.SplitBlxFile()
                if self.counter == 0:
                    shutil.copy(self.binaryLog, resultBlx +'.blx')
                    self.counter = 1
                else:
                    filename = os.path.join(os.path.splitext(self.binaryLog)[0] + '_part_' + str(self.counter).zfill(2) + '.blx')
                    shutil.copy(filename, resultBlx +'.blx')
        
        if memoryLeakDetection:
            if uiEnabled:
                self.yapasGarbageCollector()
            #check if we have not looped through test cases
            if self.previousTestCase == caseId:
                if uiEnabled:
                    self.clearActivityScreen()
                self.markerToBlx(str(caseId) + ' end iteration: ' + str(core.FW_conf['memory_leak_current_loop']))
                core.FW_conf['memory_leak_current_loop'] += 1
                self.markerToBlx(str(caseId) + ' start iteration: ' + str(core.FW_conf['memory_leak_current_loop']))
            if not self.previousTestCase == caseId:
                self.markerToBlx(str(caseId) + ' start iteration: ' + str(core.FW_conf['memory_leak_current_loop']))     
                
        #save next test caseID for next run. If this is last testcase from GUI set it to None
        if testRunEnd:
            self.previousTestCase = None
            self.counter = 0
        else:
            if not self.previousTestCase == None and not memoryLeakDetection:
                self.counter += 1
            self.previousTestCase = caseId


    def traceActivation(self, traceXML, scriptActivation = None):
        """ Activate traces in phone
            Traces are visible through connection that was used to activate them.
            If there is USB connection and also trace box connected to phone trace box is used to activate traces
        """
        #intitialize trace activator, to be moved __init__ when trace activation from GUI is available
        #FIXME self.traceActivator -> traceActivator?

        if scriptActivation or not self.taskCallDepthSet:
            if not os.path.isfile(traceXML):
                debug.brf("Invalid trace_xml file %s" %traceXML)
            else:
                self.traceActivator = TraceActivator.Instance(core.FW_conf['connection'].graniteConnection.PMDLoader, self.graniteTraceConnection.MessageSender)
                registerId = self.traceActivator.Register()
                #read trace activation string from file and send it to phone
                traceConf = open(traceXML).read()
                self.traceActivator.AddConfiguration(registerId, traceConf)
                self.traceActivator.Activate()
                debug.brf("Using trace_xml file %s" %traceXML)
                self.traceActivator.Dispose()
           

        #set task call stack depth to 8 if memory leak detection is enabled
        if core.FW_conf['memory_leak_detection'] and not self.taskCallDepthSet:
            core.FW_conf['connection'].getProductDetails()
            self.setTaskCallDepth()

    def markerToBlx(self, message):
        """ Add Marker to Blx
            
            Parameters: message, user defined message from test script
                        
        """
        #blxMarkerMsg = TextMessage(message)
        self.graniteTraceConnection.SetMarker(message)

    def yapasGarbageCollector(self):
        """ Call Yapas garbage Collector from Granite
        """
        core.FW_conf['connection'].sendCommonMsg([0x00,0x00,0x10,0x38,0x00,0x06,0x00,0x01,0x01,0x5e,0x00,0x00])  #UI_FORCE_GARBAGE_COLLECTION_REQ
        if not core.FW_conf['connection'].recvMsg():
            raise GraniteConnectionException('Failed to receive UI_FORCE_GARBAGE_COLLECTION_RESP')

    def setTaskCallDepth(self):
        
        """ set all tasks call depth to 8
            
            This only need to be done once, after setting is done call depth is set to 8
            If call depth is not changed it remais as it is until next phone flashing.
        """
        if core.FW_conf['connection'].graniteConnection.connBusName in  ['FIDO', 'MUSTI', 'MUSTI_USB']:
            if core.FW_conf['connection'].product_name.startswith('Lanai'):
                debug.brf('For Lanai Memoryleak testing set only UI task call depth to 8')
                msgFile = os.path.join(core.FW_conf['startup_path'], 'core\\data\\UI_task_call_depth_8.txt')
            else:
                debug.brf('Starting to set all tasks call depth to 8...')
                msgFile = os.path.join(core.FW_conf['startup_path'], 'core\\data\\task_call_depth_8.txt')
            for line in open(msgFile, 'r'):
                if not 'MON_OS_TRACE_CALL_STACK_DEPTH_SET_REQ' in line:
                    line = line.strip().split(',')
                    msg = [int(x, 0) for x in line]
                    core.FW_conf['connection'].sendCommonMsg(msg)
                else:
                    debug.out('sending message: %s' %line)
        
            debug.brf('Finished setting task call depths')
            #set this true so this is only need to be done once
            self.taskCallDepthSet = True

    def clearActivityScreen(self):
        """
            Clears activity screen by using sx 'spell'
        """
        sxString = \
        """
        (define evo-app (send (get-app-manager) find-singleton-app "x-evo-home")) (define evo-screen (send evo-app get-screen))
        """

        core.FW_conf['connection'].sx(sxString, doNotReport = True)
        sxString = \
        """
        (send evo-screen warp-to-screen 'activities) (send evo-screen switch-clearing-mode true) (send evo-screen do-action 'delete-all)
        """
        core.FW_conf['connection'].sx(sxString, doNotReport = True)
        core.FW_conf['connection'].exit()
        self.markerToBlx('Activity screen cleared')
        core.FW_conf['connection'].delay(100, False)
