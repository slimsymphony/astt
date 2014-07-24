import core
from core import debug, FW_conf
from core.testcase_exceptions import TestException, StopTestException, POXRobotException, BackendConnectionException, TestCaseWarning
from core.leader import needsEvaluation

# .NET Imports
import clr
clr.AddReference('TestAutomation.Gui.Marble.PoxBackend')
from TestAutomation.Gui.Marble.PoxBackend import XmlRpcClient, PoxConnectionException, PoxRobotException
clr.AddReference('System')
from System import Collections
from System.Collections.Generic import Dictionary, List

class VirtualPhoneManager(object):
    """ Manager-class for virtual phones

    """
    def __init__(self):
        self.__poxInterface = POXInterface()

    def close(self):
        self.__poxInterface.close()

    def __getitem__(self, key):
        """ Add support for accessing virtual phones by using indexes."""
        self.__poxInterface.virtualPhoneIndex = key
        return self.__poxInterface

    def __getattr__(self, attr, *args, **kwargs):
        """ Create access to first virtual phone"""
        self.__poxInterface.virtualPhoneIndex = 1
        if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
            # Leader mode will send the remote method/parameters to follower
            def wrapper(*args, **kw):
                core.FW_conf['leader'].currentTestStep = 'self.virtualPhone.%s -- %r %r' % (attr, args, kw)
                arglist = List[object](args)
                kwdict = Dictionary[object, object](kw)

                argEvalIndex = List[int]()
                kwargEvalIndex = List[int]()

                # check arguments which needs to be evaluated in follower. array will contain index numbers of to-be-evaluated args
                for i in range(len(args)):
                    ret = needsEvaluation(args[i])
                    if ret and ret[1]:
                        debug.brf('Parameter %s will be evaluated in Follower' % ret[1])
                        argEvalIndex.Add(i)
                        arglist[i] = ret[1]
                
                for i in range(len(kwargs)):
                    ret = needsEvaluation(kwargs.values()[i])
                    if ret and ret[1]:
                        debug.brf('Keyword parameter %s will be evaluated in Follower' % ret[1])
                        kwargEvalIndex.Add(i)
                        kwdict[k] = ret[1]
                
                debug.brf('self.virtualPhone.%s -- %r %r' % (attr, arglist, kwdict))
                core.FW_conf['leader'].VirtualPhoneExecute(attr, arglist, argEvalIndex, kwdict, kwargEvalIndex)
                return getattr(self.__poxInterface, attr)(*args, **kw)
            return wrapper
                    
        else:
            return getattr(self.__poxInterface, attr)

class POXInterface:
    def __init__(self):
        self.poxServer = None
        self.virtualPhoneIndex = -1
        
        # Set backendAvailable to False if failAmountMax amount of POX commands fails consecutively
        self.failAmountMax = core.FW_conf['settings'].TestRun.POXFailAmountMax
        self.failAmountCurrent = 0

        # Get main phone numbers from FW_conf
        self.mainsim1 = core.FW_conf['settings'].Main.SIM1PhoneNumber
        self.mainsim2 = core.FW_conf['settings'].Main.SIM2PhoneNumber

        if self.mainsim1 == '' and self.mainsim2 == '':
            #raise StopTestException('Unable to start the Granite Backend client: The phonenumbers of SIM1 and SIM2 cannot be empty!')
            core.FW_conf['connection'].warn('Granite Backend client: The phonenumbers of SIM1 and SIM2 cannot be empty!')
            core.FW_conf['settings'].TestRun.BackendAvailable = False
            return

        if self.mainsim1 != '' and not self.mainsim1.startswith('+') and self.mainsim1.startswith('0'):
            #raise StopTestException('Unable to start the Granite Backend client: The phonenumber of SIM1 ''%s'' is not given in the international format(e.g. +358501234567)' % (self.mainsim1))
            core.FW_conf['connection'].warn('Granite Backend client: POX server requires that the phonenumbers are given in the international format (e.g. +358501234567). Check the phonenumber of SIM1 ''%s''.' % (self.mainsim1))
            core.FW_conf['settings'].TestRun.BackendAvailable = False
            return

        if self.mainsim2 != '' and not self.mainsim2.startswith('+') and self.mainsim2.startswith('0'):
            #raise StopTestException('Unable to start the Granite Backend client: The phonenumber of SIM2 ''%s'' is not given in the international format(e.g. +358501234567)' % (self.mainsim2))
            core.FW_conf['connection'].warn('Granite Backend client: POX server requires that the phonenumbers are given in the international format (e.g. +358501234567). Check the phonenumber of SIM2 ''%s''.' % (self.mainsim2))
            core.FW_conf['settings'].TestRun.BackendAvailable = False
            return
        
        if core.FW_conf['settings'].TestRun.POXBackendServerUri == None:
            core.FW_conf['settings'].TestRun.BackendAvailable = False
            raise StopTestException('Unable to start the Granite Backend client: The POXBackend Uri has not been specified)')

        if core.FW_conf['settings'].TestRun.POXBackendServerUri == '':
            core.FW_conf['settings'].TestRun.BackendAvailable = False
            raise StopTestException('Unable to start the Granite Backend client: The POXBackend Uri is empty')
            
        # Try to create connection to POX server
        try:
            self.poxServer = XmlRpcClient(core.FW_conf['settings'].TestRun.POXBackendServerUri)
            core.FW_conf['settings'].TestRun.BackendAvailable = True
        except Exception, ex:
            self.poxServer = None
            core.FW_conf['settings'].TestRun.BackendAvailable = False
            debug.err('Unable to initialize Granite POX Backend: ' + str(ex.message))
            return

        debug.brf("POX System running")

    def close(self):
        if self.poxServer and self.poxServer.JobId > 0:
            debug.brf('Stopping POX job %s...' % self.poxServer.JobId)
            try:
                self.poxServer.Close()
            except PoxConnectionException, ex:
                debug.err(str(ex.Message))

            debug.brf('Stopping done.')
            core.FW_conf['settings'].TestRun.BackendAvailable = False

    def createCall(self, phoneNumber):      
        # Create a call on POX robot
        if core.FW_conf['settings'].TestRun.BackendAvailable == True:
            try:
                self.poxServer.CreateCall(phoneNumber, self.virtualPhoneIndex)
                self.failAmountCurrent = 0
            except PoxConnectionException, ex:
                self.__checkFailAmount()
                raise BackendConnectionException(str(ex.Message))
            except PoxRobotException, ex:
                self.__checkFailAmount()
                raise POXRobotException(str(ex.Message))
        else:
            raise TestCaseWarning('Unable to create call via POX. Backend not available!')

    def voipCreateCall(self, account):      
        # Create a VoIP call on POX robot
        if core.FW_conf['settings'].TestRun.BackendAvailable == True:
            try:
                self.poxServer.CreateCall(account, self.virtualPhoneIndex, True)
                self.failAmountCurrent = 0
            except PoxConnectionException, ex:
                self.__checkFailAmount()
                raise BackendConnectionException(str(ex.Message))
            except PoxRobotException, ex:
                self.__checkFailAmount()
                raise POXRobotException(str(ex.Message))
        else:
            raise TestCaseWarning('Unable to create VoIP call via POX. Backend not available!')
    
    def rejectCall(self):
        if core.FW_conf['settings'].TestRun.BackendAvailable == True:
            self.releaseCall()
        else:
            raise TestCaseWarning('Unable to reject call via POX. Backend not available!')
                
    def releaseCall(self):
        # Granite calls releaseCall automatically every time testcase setup is being ran.
        # If no POX job has been started, this method call can be ignored.
        if core.FW_conf['settings'].TestRun.BackendAvailable == True:
            self.__checkFailAmount()
            if self.poxServer and self.poxServer.JobId < 0:
                return

            # Release a call on POX robot
            try:
                self.poxServer.ReleaseCall(self.virtualPhoneIndex)
                self.failAmountCurrent = 0
            except PoxConnectionException, ex:
                self.__checkFailAmount()
                raise BackendConnectionException(str(ex.Message))
            except PoxRobotException, ex:
                self.__checkFailAmount()
                raise POXRobotException(str(ex.Message))
        else:
            raise TestCaseWarning('Unable to release call via POX. Backend not available!')

    def voipRejectCall(self):
        if core.FW_conf['settings'].TestRun.BackendAvailable == True:
            self.voipReleaseCall()
        else:
            raise TestCaseWarning('Unable to reject VoIP call via POX. Backend not available!')

    def voipReleaseCall(self):
        # Granite calls releaseCall automatically every time testcase setup is being ran.
        # If no POX job has been started, this method call can be ignored.
        if core.FW_conf['settings'].TestRun.BackendAvailable == True:
            if self.poxServer and self.poxServer.JobId < 0:
                return

            # Release a VoIP call on POX robot
            try:
                self.poxServer.ReleaseCall(self.virtualPhoneIndex, True)
                self.failAmountCurrent = 0
            except PoxConnectionException, ex:
                self.__checkFailAmount()
                raise BackendConnectionException(str(ex.Message))
            except PoxRobotException, ex:
                self.__checkFailAmount()
                raise POXRobotException(str(ex.Message))
        else:
            raise TestCaseWarning('Unable to release VoIP call via POX. Backend not available!')
            
    def answerCall(self):
        # Answer a call on POX robot
        if core.FW_conf['settings'].TestRun.BackendAvailable == True:
            try:
                self.poxServer.AnswerCall(self.virtualPhoneIndex)
                self.failAmountCurrent = 0
            except PoxConnectionException, ex:
                self.__checkFailAmount()
                raise BackendConnectionException(str(ex.Message))
            except PoxRobotException, ex:
                self.__checkFailAmount()
                raise POXRobotException(str(ex.Message))
        else:
            raise TestCaseWarning('Unable to answer call via POX. Backend not available!')

    def voipAnswerCall(self):
        # Answer a VoIP call on POX robot
        if core.FW_conf['settings'].TestRun.BackendAvailable == True:
            try:
                self.poxServer.AnswerCall(self.virtualPhoneIndex, True)
                self.failAmountCurrent = 0
            except PoxConnectionException, ex:
                self.__checkFailAmount()
                raise BackendConnectionException(str(ex.Message))
            except PoxRobotException, ex:
                self.__checkFailAmount()
                raise POXRobotException(str(ex.Message))
        else:
            raise TestCaseWarning('Unable to answer VoIP call via POX. Backend not available!')

    def __checkFailAmount(self):
        self.failAmountCurrent += 1
        if (self.failAmountCurrent >= self.failAmountMax) or (self.poxServer is not None and self.poxServer.FailAmount >= self.failAmountMax):
            debug.err('Amount of consecutive fails exceeded ' + str(self.failAmountMax) + '. Setting backend_available to False')
            core.FW_conf['settings'].TestRun.BackendAvailable = False
