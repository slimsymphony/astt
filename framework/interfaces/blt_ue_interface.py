"""Interface for wrapping BLT-UE currentmeasurement module and WCF inteface for GUI.
"""
# Python library module imports
import clr, time, getpass, os, socket, datetime

from System import Double
from System.Threading import Thread, ThreadStart, ThreadAbortException, ReaderWriterLock
from System.Globalization import CultureInfo

import core
from core import debug
from core.testcase_exceptions import BltUeException
from utils.nodeutils import NodeUtils
clr.AddReference('TestAutomation.Gui.Marble.Currentmeasurement.BltUe')
from TestAutomation.Gui.Marble.Currentmeasurement import BltUe

class GraniteBltUeInterface:
    """Granite BLT-UE interface class."""
    def __init__(self):
        """Initialize variables."""
        try:
            self.bltUe = BltUe.Instance
            self.__currentMeasuringThread = None
            self.__bltueReport = None
            self.__bltueTestCase = None
            self.__bltueTestStep = None
            self.__reportLock = ReaderWriterLock()
            self.__allCurrents = []
            self.__testCaseCurrents = []
            self.__testStepCurrents = []
            self.__testRunNodeAdded = False
        except Exception, ex:
            debug.exception(ex)
            raise BltUeException('Unable to create the BLT-UE object: %s' % ex)

    def startBltUeGuiInterfaceService(self):
        try:
            self.bltUe.StartService(core.FW_conf['settings'].System.FrameworkGuiBltUeServicePort)
        except Exception, ex:
            debug.exception(ex)
            raise BltUeException('Unable to start the BLT-UE GUI Inteface service: %s' % ex)

    def initGpib(self):
        try:
            self.bltUe.InitGpib()
        except Exception, ex:
            debug.exception(ex)
            raise BltUeException('BLT-UE GPIB connectivity: Init GPIB failed %s' % ex)

    def initPsu(self):
        try:
            self.bltUe.InitPsu()
        except Exception, ex:
            debug.exception(ex)
            raise BltUeException('BLT-UE PowerSupply: Init PowerSupply failed %s' % ex)

    def setVoltage(self, voltage):
        try:
            self.bltUe.SetVoltage(Double(voltage))
        except Exception, ex:
            debug.exception(ex)
            raise BltUeException('BLT-UE PowerSupply: Set Voltage failed %s' % ex)

    def measureCurrent(self):
        try:
            return self.bltUe.MeasureCurrent()
        except Exception, ex:
            #debug.exception(ex)
            raise BltUeException('BLT-UE PowerSupply: Measure Current failed %s' % ex)

    def isEnabled(self):
        return self.bltUe.IsBltUeReady

    # Helper method for setting up the BLT-UE testing with single method only.
    def setupBltUeTesting(self):
        self.initGpib()
        self.initPsu()

    def __measureInThread(self):
        """Reads current in a loop, executed in thread."""        
        self.__allCurrents = []
        periodicCurrents = []
        startTime = time.time()

        while self.__currentMeasuringThread and self.__currentMeasuringThread.IsAlive:
            try:
                current = self.measureCurrent()
                self.__allCurrents.append(current)
                self.__testCaseCurrents.append(current)
                self.__testStepCurrents.append(current)
                periodicCurrents.append(current)

                if core.FW_conf['settings'].TestRun.BLTUEOutputMode == 'full':
                    debug.brf('CURRENT: %s' % current)

                currentNode = NodeUtils('current', True)
                now = datetime.datetime.now()
                currentNode.setAttribute('timestamp', '%s:%s:%s:%s' % (now.hour, now.minute, now.second, str(now.microsecond)[:2]))
                currentNode.setAttribute('interval', core.FW_conf['settings'].TestRun.BLTUEMeasureInterval)
                currentNode['text'] = '%.2f' % float(current)
                self.addBltueNode(currentNode)

                if ((time.time() - startTime) * 1000) >= core.FW_conf['settings'].TestRun.BLTUEAverageInterval:
                    periodicAverage = self.__calculateAverage(periodicCurrents)
                    totalAverage = self.__calculateAverage(self.__allCurrents)

                    if core.FW_conf['settings'].TestRun.BLTUEOutputMode in ['full', 'only averages']:
                        debug.brf('PERIODIC AVERAGE: %s' % periodicAverage)
                        debug.brf('TOTAL AVERAGE: %s' % totalAverage)

                    averageNode = NodeUtils('average', True)
                    now = datetime.datetime.now()
                    averageNode.setAttribute('timestamp', '%s:%s:%s:%s' % (now.hour, now.minute, now.second, str(now.microsecond)[:2]))
                    averageNode.setAttribute('periodic', periodicAverage)
                    averageNode.setAttribute('total', totalAverage)
                    averageNode.setAttribute('interval', core.FW_conf['settings'].TestRun.BLTUEAverageInterval)
                    self.addBltueNode(averageNode)

                    startTime = time.time()
                    periodicCurrents = []

                measureInterval = float(float(core.FW_conf['settings'].TestRun.BLTUEMeasureInterval) / float(1000))
                time.sleep(measureInterval)            
            except BltUeException:
                # measureCurrent may throw this error when thread is aborting
                break
            except ThreadAbortException:
                break
            except Exception, err:
                debug.err('Error in current measurement thread: %s' % str(err))
                break

    def __calculateAverage(self, currentList):
        """Calculate average from given current list."""
        if currentList:
            average = sum(currentList) / float(len(currentList))
            return '%.2f' % average
        else:
            return 0

    def __addTestCaseNode(self):
        """Add test case node to BLTUE report."""
        if self.__bltueTestCase and self.__testCaseCurrents:
            totalAverage = self.__calculateAverage(self.__testCaseCurrents)
            self.__bltueTestCase.setAttribute('total_average', totalAverage)

            if core.FW_conf['settings'].TestRun.BLTUEOutputMode in ['full', 'only averages']:
                debug.brf('TEST CASE TOTAL AVERAGE: %s' % totalAverage)

            self.__bltueReport.append(self.__bltueTestCase)
            self.__testCaseCurrents = []

    def __addTestStepNode(self):
        """Add test step node to BLTUE report."""
        if self.__bltueTestStep and self.__testStepCurrents:
            totalAverage = self.__calculateAverage(self.__testStepCurrents)
            self.__bltueTestStep.setAttribute('total_average', totalAverage)

            if core.FW_conf['settings'].TestRun.BLTUEOutputMode in ['full', 'only averages']:
                debug.brf('TEST STEP TOTAL AVERAGE: %s' % totalAverage)

            self.__bltueTestCase.append(self.__bltueTestStep)
            self.__testStepCurrents = []

    def addTestRunBltueNode(self, productDetails):
        """Add testrun node to BLTUE report.
        
            Parameters

            productDetails      product details node coming from testcase.py
        """
        if self.__bltueReport and productDetails and \
           not self.__testRunNodeAdded:
            testRunNode = NodeUtils('testrun', True)
            testRunNode['time'] = time.strftime("%Y-%m-%d %H:%M:%S")
            try:
                testRunNode['author'] = unicode(getpass.getuser(), 'Latin-1')
            except:
                testRunNode['author'] = ""
            testRunNode.setAttribute('hostname', socket.gethostname())
            testRunNode.setAttribute('baseline', 'NG 1.0')
            testRunNode.setAttribute('product', productDetails['name'])
            testRunNode.setAttribute('imei', productDetails['imei'])
            testRunNode.setAttribute('sw', productDetails['sw'].strip('\0').strip())
            testRunNode.setAttribute('hw', productDetails['hw'].strip('\0').strip())
            self.addBltueNode(testRunNode)
            self.__testRunNodeAdded = True

    def addBltueNode(self, bltueNode):
        """Add node to bltue report in thread safe mode.

            Parameters

            bltueNode       NodeUtils instance to be added
        """
        self.__reportLock.AcquireWriterLock(1000)

        if not self.__bltueReport:
            self.__bltueReport = NodeUtils('granite_bltue', True)

        try:
            if bltueNode.getName() == 'testrun':
                self.__bltueReport.append(bltueNode)
            elif bltueNode.getName() == 'testcase':
                self.__addTestCaseNode()
                self.__bltueTestCase = bltueNode
            elif bltueNode.getName() == 'teststep':
                self.__addTestStepNode()
                self.__bltueTestStep = bltueNode
            else:
                if self.__bltueTestStep and bltueNode.getName() != 'average':
                    self.__bltueTestStep.append(bltueNode)
                else:
                    self.__bltueReport.append(bltueNode)
        finally:
            self.__reportLock.ReleaseWriterLock()
            
    def startCurrentMeasuring(self):
        """ Starts thread for measuring current."""
        if not self.__currentMeasuringThread:
            assert core.FW_conf['settings'].TestRun.BLTUEMeasureInterval > 0, \
                'Invalid current measurement interval given! (%s)' % core.FW_conf['settings'].TestRun.BLTUEMeasureInterval
            assert core.FW_conf['settings'].TestRun.BLTUEAverageInterval > 0, \
                'Invalid average measurement interval given! (%s)' % core.FW_conf['settings'].TestRun.BLTUEAverageInterval

            cultureInfo = CultureInfo('en-US')

            self.__currentMeasuringThread = Thread(ThreadStart(self.__measureInThread))

            # set correct culture info for the thread and set it as a background thread
            self.__currentMeasuringThread.CurrentCulture = cultureInfo
            self.__currentMeasuringThread.CurrentUICulture = cultureInfo
            self.__currentMeasuringThread.IsBackground = True

            self.__currentMeasuringThread.Start()

    def stopCurrentMeasuring(self):
        """ Stops thread for measuring current."""
        if self.__currentMeasuringThread and \
           self.__currentMeasuringThread.IsAlive:
            self.__currentMeasuringThread.Abort()

        self.__currentMeasuringThread = None

        if self.__bltueReport:
            # add total average for testrun node
            testRunNode = self.__bltueReport.find('//testrun')
            if testRunNode:
                testRunNode.setAttribute('total_average', self.__calculateAverage(self.__allCurrents))

            # add last test step and test case to report
            self.__addTestStepNode()
            self.__addTestCaseNode()

            # save test report
            bltueReportPath = os.path.join(core.FW_conf['test_result_dir'], 'bltue', '%s_%s.xml' % (core.FW_conf['test_result_name'], time.strftime("%Y%m%d%H%M%S")))
            bltueReportFolder = os.path.dirname(bltueReportPath)

            if not os.path.isdir(bltueReportFolder):
                os.makedirs(bltueReportFolder)
            
            self.__bltueReport.save(bltueReportPath)
            self.__bltueReport = None
            self.__bltueTestCase = None
            self.__bltueTestStep = None
            self.__allCurrents = []
            self.__testCaseCurrents = []
            self.__testStepCurrents = []
            self.__testRunNodeAdded = False

    def Dispose(self):
        self.bltUe.Dispose()
