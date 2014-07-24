"""Connection interface for opening/closing Granite <-> phone connection and
   handling exceptions.
"""
# Python library module imports
import os, sys, time, types, re, clr, threading
from shutil import copyfile
from System import Byte, Int16, Array, GC, GCCollectionMode
from System.Threading import Thread, ParameterizedThreadStart, ThreadStart

# Granite module imports
import core
from utils import include
from utils.nodeutils import NodeUtils
from core.testcase_exceptions import TestException, StopTestException, SkipTestException
from core import phone, scripting
from core.tracing import Tracing
from interfaces.isimessage import ISIMessage, ISIMessageException
from interfaces.srv_granite_isimessage import inc
from interfaces.fw_connection import fw2guiInfoDict
from interfaces.connection import GraniteConnection, \
                                  GraniteConnectionException, \
                                  GraniteFileSystemException, \
                                  ByteCompareMessageRule
from interfaces.c_srv import srv_mtc, srv_kbd
from srv_granite_isimessage import *             
from interfaces import wbxml_parser
from interfaces.referencephone_interface import GraniteReferencePhoneInterface
from core.leader import LeaderHandler
from extensions.pyevent import pyevent
from interfaces.pox_interface import VirtualPhoneManager


# Local data structures
TIME_STAMP = 0                                     
FILE2 = include.Include('file_isi.h')
pn = include.Include('pn_const.h')

# information dictionary of other servers used from Granite
serverDict = {\
    'PN_COMMGR'         : 'Communication Manager',
    'PN_UPF'            : 'User Profiles',
    'PN_TIME'           : 'Time',
    'PN_MON'            : 'Monitor',
    'PN_PHONEBOOK'      : 'Phonebook',
    'PN_NVD'            : 'Non-Volatile Data',
    'PN_NAMESERVICE'    : 'Name',
    'PN_MTC'            : 'Mobile Terminal Controller',
    'PN_MESSAGING'      : 'Messaging',
    'PN_ISA_SETTINGS'   : 'ISA Settings',
    'PN_CALL'           : 'Call',
    'PN_SIM'            : 'SIM',
    'PN_SECURITY'       : 'Security',
    'PN_PROVISIONING'   : 'Provisioning',
    'PN_MESSAGE_STORAGE': 'Message Storage',
    'PN_MENU'           : 'Menu',
    'PN_KEY'            : 'Keyboard',
    'PN_INFO'           : 'Info',
    'PN_FILE'           : 'File',
    'PN_IMPS'           : 'Instant Messaging and Presence',
    'PN_TOUCHPAD'       : 'Panel' # FIXME: Update if other messages than touch ntf:s will be taken into use
}


# ============================================================================
class ConnectionException(TestException):
    pass
    
# ============================================================================
#class MessageIdRule(ByteCompareMessageRule):
#    def __init__(self, messageId):    
#        self.Conditions.Add(9, messageId)

def FILE2ATTR(fileAttr):
    """Get FILE2 file attribute values"""
    return getattr(FILE2, fileAttr, None)

class Reference(object):
    def __init__(self, val):
        self._value = val

    def get(self):
        return self._value

# ============================================================================
class GraniteConnectionInterface(object):
    """Granite connection interface class."""
    def __init__(self):
        """Initialize variables."""
        if type(self) == GraniteConnectionInterface:
            raise Exception("<GraniteConnectionInterface> must be subclassed.")

        self.graniteConnection = None
        self.__checkingPhoneConnection = False
        self._latestWaitMessage = ''
        self._latestWaitMessageSendTime = 0
        
        #self.__multipleResponsesPossible = False
        self.__graniteMessageIterator = None
        
        # this will be set to True when connection has been created
        self.__connectionCreated = False
        self.__connectionCreatedInEnsureConnection = False
        # this will be set to False when connection is already active
        # (for actions to be done only right away after connection creation)
        self.newConnection = True
        
        # variables for phone freeze detection 
        self.__freezeLimit = 15  # this is used for determining phone freeze (seconds)
        self.__freezeStartupTime = 0

        self.__waitMessageSenderThread = None
        self.__sendingMessageToGraniteServer = False
        self.__GraniteServerMessageSentCount = 0        
        self.__GraniteServerMessageSentLimit = 10
        self._name = ''
        self.__uiEnabledValue = False
        self.current_connection = None
        self.__timeoutMultiplier = 1

        # for display update ntf messages and performance measuring
        self.__ntfListenerThread = None
        self.__uiMovementNode = None
        self.perfReport = None
        self.testStepPerfNode = None
        self.perfReportLock = threading.Lock()
                
        # event for display updates
        self.UI_CHANGED, self.THROW_UI_CHANGED = pyevent.make_event()

        # referencephone access
        self.referencePhone = None

        # virtual phone access
        self.virtualPhone = None
        self.backendAvailable = Reference(core.FW_conf['settings'].TestRun.BackendAvailable)

    def __graniteMessageListenerSet(self, expectedResp):
        """Creates Granite message iterator. If it already exists, move pointer to end.
        
            Parameters
            
            expectedResp        expected response message in string to be iterated
        """
        # dispose and delete previous iterator
        self.__graniteMessageListenerDestroy()
            
        # create new iterator for specific response message
        
        #print '************************** expectedResp:  ', expectedResp
        
        self.__graniteMessageIterator = \
            self.graniteConnection.MessageApiSender.Iterator.CreatePrivate("PN_PRIVATE_GRANITE", expectedResp)

        #debug.brf('self.__graniteMessageIterator: %s' % self.__graniteMessageIterator)
            
        #messageIdRule = MessageIdRule(clr.Convert(expectedResp, Int16))        
        #self.__graniteMessageIterator = \
        #    self.graniteConnection.IteratorFactory.Create(messageIdRule)
        
        # ** OLD WAY **
        #self.__graniteMessageIterator = \
        #    self.graniteConnection.MessageSender.Iterator.CreatePrivate("PN_PRIVATE_GRANITE", )
            #print 'self.__graniteMessageIterator: ', self.__graniteMessageIterator
        #else:
            # move existing iterator to the end
            #print '**************moved to the end'
        #    self.__graniteMessageIterator.MoveEnd()
        # ** OLD WAY ENDS **
                
    #def __getNextGraniteMessageFromIterator(self, timeout):
    #    """Returns next Granite message using iterator.
        
    #        Parameters      timeout     timeout in milliseconds
    #    """
    #    startTime = time.clock()
                
    #    #print 'timeout: ', timeout
            
    #    while True:
    #        self.__graniteMessageIterator.Timeout = timeout
                           
    #        message = self.__graniteMessageIterator.GetNextPhonet()
            
    #        if not message:            
    #            # HACK BECAUSE OF BUG IN ITERATOR TIMEOUT HANDLING
    #            timeSpent = time.clock() - startTime
    #            if timeSpent < timeout:
    #                time.sleep(1)
    #                continue
                    
    #            #print 'no message **********************************: ', time.clock() - startTime                    
    #            return None, None
    #        else:
    #            # convert message to Granite message (list of ints)
    #            graniteMessage = [int(x) for x in message.ToArray()]
                
    #            #print 'graniteMessage: ', graniteMessage
    #            # check that message is a valid Granite message
    #            #if graniteMessage[3] == inc.PN_PRIVATE and \
    #            #   graniteMessage[9] in [inc.GRN_TEST_RESP,
    #            #                      inc.GRN_ABORT_RESP,
    #            #                      inc.GRN_TERM_RESP,
    #            #                      inc.GRN_CLEAR_RESP,
    #            #                     inc.GRN_CLEAR_TESTCASE_RESP,
    #            #                      inc.GRN_TEST_NTF,
    #            #                      inc.GRN_ABORT_NTF,
    #            #                      inc.GRN_TERM_NTF,
    #            #                      inc.GRN_CLEAR_NTF,
    #            #                      inc.GRN_CLEAR_TESTCASE_NTF]:
    #            #print 'message received **********************************: ', time.clock() - startTime        
    #            return message.Count, graniteMessage
    #                #print 'valid message: ', message
    #            #else:
    #            #    print 'INVALID MESSAGE: ', message
    #                #self.__graniteMessageIterator.WhatTheFxxx()

    #            #if graniteMessage[9] in [inc.GRN_TEST_RESP,
    #            #                      inc.GRN_ABORT_RESP,
    #            #                      inc.GRN_TERM_RESP,
    #            #                      inc.GRN_CLEAR_RESP,
    #            #                      inc.GRN_CLEAR_TESTCASE_RESP]:
    #            #    break
               
    def getConnectionBusName(self):
        """Returns the bus name of lower level connection."""
        return self.graniteConnection and self.graniteConnection.connBusName or None
                                            
    def __graniteMessageListenerDestroy(self):
        """Destroy Granite message iterators."""
        if self.__graniteMessageIterator:
            try:
                self.__graniteMessageIterator.MoveEnd() # maybe this is not needed at all?               
            except StandardError:
                # StandardError is thrown is binary log (connection has already been closed)
                pass
                
            self.__graniteMessageIterator.Dispose()
            self.__graniteMessageIterator = None
                                
    def __executeConnectionOperation(self, method, *args, **kwargs):
        """Executes connection operation and catches exceptions.

            Returns True, params if method was executed successfully,
            False, exception if not.
        """

        if self.isFullBlackBox():
            return

        if self.isFollower():
            if core.FW_conf['current_testcase'] == None or not core.FW_conf['current_testcase'].follower.allowUsbConnection:
                debug.vrb('Follower mode, no permission to execute __executeConnectionOperation')
                return
            else:
                debug.out('Follower mode, __executeConnectionOperation')

        try:
            params = method(*args, **kwargs)

            # clear phone freeze measuring if send method was successful            
            if method == self.graniteConnection.send:
                self._clearPhoneFreeze(True)
        except GraniteConnectionException, connException:
            # we only need the error reason from exception
            connectionException = str(connException)

            # delete exception instance
            del connException

            debug.vrb('Connection exception: %s occurred with method: %s' % \
                      (connectionException, str(method)))
                      
            # in case of Timeout error we may have phone freeze at hand
            if 'Timeout' in connectionException:
                self.addPhoneFreezeEvent()

                # increase timeout multiplier when timeout occurs
                if self.__timeoutMultiplier < 16 and self.graniteConnection.defaultTimeout < 30000:
                    self.__timeoutMultiplier *= 2
                    self.graniteConnection.defaultTimeout *= self.__timeoutMultiplier
                      
            return False, connectionException
        except GraniteFileSystemException, fsException:
            # we only need the error reason from exception
            fileSystemException = str(fsException)

            # delete exception instance
            del fsException

            debug.vrb('File System exception: %s occurred with method: %s' % \
                      (fileSystemException, str(method)))
            return False, fileSystemException
        except Exception, exception:
            # we only need the error reason from exception
            unExpectedException = str(exception)

            # delete exception instance
            del exception

            debug.dumpMemoryUsage()
            # NOTE: This exception should never happen!
            # don't show errors if we are stopping FW execution
            if not core.FW_conf['should_stop']:
                debug.err('Unexpected connection exception: "%s" when executing: "%s"' % (unExpectedException, str(method)))

            # re-create reference phone connection
            # NOTE: This has to be done, because ReferencePhone library doesn't recover from Fuse crashes
            try:
                if self.referencePhone != None:
                    del self.referencePhone
                    time.sleep(2)
                    self.referencePhone = None
                    self.createReferencePhoneConnection()
            except Exception, err:
                debug.err('Failed to re-create reference phone connection: %s' % str(err))

            raise ConnectionException(unExpectedException)

        return True, params

    def _ensureBlackBoxUsbAccessoryConnection(self):
        """Ensure that when running on BlackBox mode, default USB connector is always connected.
            A try-catch clause is preferred due to there might be no USBAccessoryCard to execute this operation in some cases.

            Returns True if USB accessory connector has been changed from E.g. None to Usb1,
            False, if no connector change.
        """
        if core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox_enabled'] and \
            ( (self.getConnectionBusName() == 'USB' and self.getName() == "Main") or self.isFollower() ) :
            result = False
            try:
                result = core.FW_conf['blackbox'].connectDefaultAccessoryUsb()
            except Exception, ex:
                debug.err('_ensureBlackBoxUsbAccessoryConnection: %s' %str(ex))
            
            if result == True:
                # Accessory connector changed: Wait a while for windows to detect the connection
                time.sleep(5)
            return result

    def _blackBoxResetPhonePower(self):
        
        debug.brf('Reset requested, but blackbox reset is not available for remote phone')
        return

        # if reset in follower mode, do not create connection, just reset
        if core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox_enabled'] and self.isFollower():
            debug.brf('BlackBox: Reset phone power in blackbox mode...')
            self.sendWaitMessageToGraniteGUI(300, 'Resetting phone power')
            core.FW_conf['blackbox'].resetPhonePower()

        #If running on BlackBox: disconnect / reconnect phone power to fully reset the connection
        elif core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox_enabled'] and self.getName() == "Main":
            debug.brf('BlackBox: Reset phone power...')
            try:
                self.sendWaitMessageToGraniteGUI(300, 'Resetting phone power')
                if not self.isFullBlackBox():
                    self.closeConnection(True)
                    core.FW_conf['blackbox'].resetPhonePower()
                    self.createConnection(ensureConnection = False)
                else:
                    core.FW_conf['blackbox'].resetPhonePower()

                if self.getName() != 'Main' and self.isConnected():
                    # run activation code so that we put server back to idle state
                    self.activateGraniteServer(forced = True, ensureConnection = False)
            except Exception, ex:
                debug.err('_blackBoxResetPhonePower: %s' %str(ex))

    def __blackBoxResetPhoneUsbConnection(self):
        ret = False
        #If running on BlackBox: disconnect / reconnect phone USB connection and reconnect phone if needed
        if core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox_enabled'] and self.getConnectionBusName() == 'USB' and self.getName() == "Main":
            try:
                self.sendWaitMessageToGraniteGUI(60, 'Resetting phone USB')
                core.FW_conf['blackbox'].connectUsb('None')
                
                # Wait 5 seconds after USB disconnected
                time.sleep(5)
                
                # Reconnect default USB accessory connector
                self._ensureBlackBoxUsbAccessoryConnection()
                
                # Wait 15 seconds after USB reconnected to ensure windows has time to detect the phone
                time.sleep(15)
                ret = self.isConnected()

                # If still not connected, also close phone connection and recreate phone connection after USB reconnected
                if not ret:
                    self.sendWaitMessageToGraniteGUI(60, 'Resetting phone USB with disconnect reconnect phone')
                    self.closeConnection(True)
                    core.FW_conf['blackbox'].connectUsb('None')
                
                    # Wait 5 seconds after USB disconnected
                    time.sleep(5)
                
                    # Reconnect default USB accessory connector
                    self._ensureBlackBoxUsbAccessoryConnection()
                
                    # Wait 15 seconds after USB reconnected
                    time.sleep(15)
                    self.createConnection(ensureConnection = False)
                    
                    # Wait additional 2 seconds
                    time.sleep(2)
                    ret = self.isConnected()
            except Exception, ex:
                debug.err('__blackBoxResetPhoneUsbConnection: %s' %str(ex))
        return ret

    def ensureConnection(self):
        """Make sure that phone connection is ok and working.
        
            Returns True if connection is ok, False if not.
        """
        if self.isFollower():
            debug.out('ensureConnection: Follower mode')
            return True

        # if test execution has been aborted, connection checks are not necessary
        if core.FW_conf['should_stop']:
            return False

        # just return if remote has been dropped
        if self.getName() != "Main" and not self in core.FW_conf['remote_connection']:
            return False

        self.sendWaitMessageToGraniteGUI(300, 'Ensuring phone connection')

        # if connection hasn't been created, try first to create it
        if not self.__connectionCreated:
            try:
                self.createConnection(ensureConnection = False)
            except Exception, err:
                debug.out('Error in ensureConnection --> createConnection: %s' % str(err))
                # pass connection exception here, because we are solving the problem and
                # we can't stop to exception
                self.__connectionCreatedInEnsureConnection = False
            else:
                self.__connectionCreatedInEnsureConnection = True

        firstTryCount, secondTryCount = 2, 2
        
        # first check with check phone connection
        connectionOK = self.__checkPhoneConnection(1)

        # try plain connect
        if not connectionOK and self.__connectionCreated and self.graniteConnection.CommunicationAdapter:
            try:
                self.__executeConnectionOperation(self.graniteConnection.CommunicationAdapter.Connect)
            except Exception, err:
                debug.err('Fatal error in phone connection layer or Fuse when calling Connect: %s' % str(err))
                connectionOK = False

            connectionOK = self.isConnected()
            if connectionOK and core.FW_conf['trace']:
                core.FW_conf['trace'].graniteTraceConnection.StopRecording()
                core.FW_conf['trace'].graniteTraceConnection.CloseConnection()
                core.FW_conf['trace'] = None
                core.FW_conf['trace'] = Tracing()

        # if connection is not ok, try reconnect
        if not connectionOK and self.__connectionCreated:
            connectionOK = self.__tryReconnect()

        # if connection is not ok right away, reconnect in a loop
        #if not connectionOK:        
        #    for i in range(firstTryCount):
        #        self.sendWaitMessageToGraniteGUI(300, 'Ensuring phone connection')
        #        connectionOK = self.__tryReconnect()
        #        if connectionOK:
        #            break
        
        if not connectionOK and not self.__checkPhoneConnection(firstTryCount):
            if not self.__connectionCreated or not self.__tryReconnect():
                if not self.__checkPhoneConnection(secondTryCount):
                    # if test execution has been aborted, connection checks are not necessary
                    if core.FW_conf['should_stop']:
                        return False

                    # close and reopen the connection
                    debug.out('Closing and reopening the connection...')
                    self.closeConnection(True)
                    
                    try:
                        self.createConnection(ensureConnection = False)
                    except Exception, err:
                        debug.out('Error in ensureConnection --> createConnection: %s' % str(err))
                        # pass connection exception here, because we are solving the problem and
                        # we can't stop to exception
                        self.__connectionCreatedInEnsureConnection = False
                    else:
                        self.__connectionCreatedInEnsureConnection = True

                    if not self.__checkPhoneConnection(firstTryCount):                    
                        
                        if self.getName() == "Main": # use blackbox reset only for Main connection
                            #If running on BlackBox: disconnect / reconnect phone power to fully reset the connection
                            self._blackBoxResetPhonePower()
                        else:
                            debug.err('Blackbox phone reset requested, but cannot do blackbox reset for %s' % self.getName())

                    if not self.isConnected():
                        if self.getName() == "Main":
                            errorMessage = 'Unable to restore phone connection, terminating test execution!'
                        else:
                            errorMessage = 'Remote phone (%s) dropped due to connection error' % self.getName()
                        
                        # close phone connection
                        self.closeConnection(True)

                        if self.getName() == "Main" and core.FW_conf['cli_mode']:
                            debug.err(errorMessage)
                            raise SystemExit(errorMessage)
                        else:
                            if self.getName() == "Main":
                                debug.err(errorMessage)
                                # send error to Granite GUI
                                core.FW_conf['com_int'].sendErrorMessage(errorMessage)
                            
                                # execute CMD_STOP event --> stops test execution                            
                                core.FW_conf['com_int'].connectionCreationOngoing = False
                                core.FW_conf['com_int'].CMD_STOP(None)
                                return False
                            else:
                                self.warn(errorMessage)
                                # delete remote phone instance from remote phone manager
                                if self in core.FW_conf['remote_connection']:
                                    del core.FW_conf['remote_connection'][core.FW_conf['remote_connection'].index(self)]
            else:
                connectionOK = True
        else:
            debug.out('Connection is ok!')
        
        return connectionOK

    def __tryReconnect(self):
        """Try reconnecting to device. Return True if connection is ok, False if not."""
        # if test execution has been aborted, connection checks are not necessary
        if core.FW_conf['should_stop']:
            return False

        if self.isFollower():
            debug.out('Follower mode on.. __tryReconnect, returning')
            return True

        if not self.isConnected():
            # phone message traffic is dead --> clear phone freeze measuring
            self._clearPhoneFreeze()
            
            # on BlackBox mode try to restore the connection by disconnecting / reconnecting phone USB cable.
            # If connection is restored and test case is running on BlackBox mode, method will return True
            # on WhiteBox mode, the method will always return False.
            if self.__blackBoxResetPhoneUsbConnection():
                return True

            debug.dumpMemoryUsage()
            phoneName = self.getName() != 'Main' and 'Remote phone' or 'Phone'

            debug.err('%s connection lost, restoring connection...' % phoneName)
            self.sendWaitMessageToGraniteGUI(300, '%s connection lost, restoring connection' % phoneName)
            
            # call TryReconnect to re-establish connection to the phone
            if self.graniteConnection.CommunicationAdapter:
                try:
                    result, reconnSuccessful = self.__executeConnectionOperation(self.graniteConnection.CommunicationAdapter.TryReconnect)
                except Exception, err:
                    debug.err('Fatal error in phone connection layer or Fuse when calling TryReconnect: %s' % str(err))
                    reconnSuccessful = False
            else:
                reconnSuccessful = False

            debug.dumpMemoryUsage()
            return self.isConnected() and reconnSuccessful
        else:
            debug.dumpMemoryUsage()
            return True            
        
    def __checkPhoneConnection(self, tryCount):
        """Checks phone connection for the amount of tryCount."""        

        if self.isFollower():
            debug.out('Follower mode on.. checkPhoneConnection, returning')
            return True

        # if test execution has been aborted, connection checks are not necessary
        if core.FW_conf['should_stop']:
            return False

        if not self.isConnected():
            return False
        
        phoneName = self.getName() != 'Main' and 'Remote phone' or 'Phone'

        tries = 1
        sleepTime = 2
        debug.dumpMemoryUsage()
        
        while tries <= tryCount:
            self.__checkingPhoneConnection = True

            # send wait message from main FW process to GUI
            self.sendWaitMessageToGraniteGUI(\
                100, 'Check phone connection')

            debug.out('Checking phone connection.. %u/%u (st:%2.1fs)' % \
                        (tries, tryCount, sleepTime))
            try:
                resp = srv_mtc.MtcStateQueryResp(isi_message=\
                    self.transferMsg(srv_mtc.MtcStateQueryReq(utid = tries),
                                     callEnsureConnection = False))
            except ConnectionException, err:
                debug.vrb('ConnectionException:%s' % err)
            except ISIMessageException, err:
                debug.vrb('ISIMessageException:%s' % err)
            except TestException, err:
                debug.vrb('TestException:%s' % err)
                
                # terminate loop when phone freeze has been detected
                if str(err) == 'Phone freeze detected':
                    return False
            else:
                # FIXME: you shouldn't need to access msg_data directly!
                # current and target state is normal
                if resp.msg_data == 2*[srv_mtc.mtc.MTC_NORMAL]:
                    break
                # if current or target state is power off, send a 'end' key
                # press keyboard server
                #elif srv_mtc.mtc.MTC_POWER_OFF in resp.msg_data[:2]:
                #    debugString = ''

                #    if resp.msg_data[0] == srv_mtc.mtc.MTC_POWER_OFF:
                #        debugString += 'mtc in power off state. '
                #    else:
                #        debugString += 'mtc target state is power off. '

                #    debugString += 'Sending a end key press...'
                #    debug.vrb(debugString)

                #    self.sendEndKeyPress()
                # current state is normal and target state something else
                # (which doesn't cause any action)
                elif resp.msg_data[0] == srv_mtc.mtc.MTC_NORMAL:
                    debug.vrb('Warning: strange mtc target state: %s' % \
                              resp.toxml())
                    break
                # if current state is charging and connection is usb, fbus,
                # musti_tcpip, musti_usb or shared,
                # send a power on request to mtc
                elif resp.msg_data[0] == srv_mtc.mtc.MTC_CHARGING:
                    # kick start the phone
                    if core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox_enabled'] and self.getName() == "Main":
                        self._blackBoxResetPhonePower()
                        errorString = '%s has shutdown but was repowered ' \
                                      'by Granite' % phoneName
                        debug.err(errorString)
                    else:
                        debug.vrb('mtc in charging state. Sending a power on '
                                   'message...')
                        errorString = '%s has shutdown but was kickstarted ' \
                                      'by Granite' % phoneName
                        debug.err(errorString)
                        resp = srv_mtc.mtcPowerOn(self)
                        debug.vrb('mtc power on resp: %s' % str(resp))
                        time.sleep(30)

                    # add warning to test case                    
                    self.warn(errorString)
                else:
                    debug.vrb('Reply from mtc: %s' % resp.toxml())
            finally:
                self.__checkingPhoneConnection = False

            time.sleep(sleepTime)
            tries += 1
            sleepTime += 0.25
        debug.dumpMemoryUsage()

        if tries > tryCount:
            return False
        else:
            return True

    def sendEndKeyPress(self):
        """Send a 'end' - key press to keyboard server."""
        # key down message
        isi_message_fields = {
            'sub_blocks' : \
                [{'block_id' : srv_kbd.kbd.KBD_SINGLE_PRESS_KEY_EVENT_INFO,
                  'key_code' : srv_kbd.kbd.KBD_KEY_END,
                  'key_state' : srv_kbd.kbd.KBD_KEY_DOWN}]}
        # Sending message
        retData = srv_kbd.kbdEventSimulation(**isi_message_fields)

        # Checking response
        if retData.get('status') != srv_kbd.kbd.KBD_OK:
            debug.err('Sending key down message failed!. ' \
                      'Status = ' + str(retData.get('status')))

        # key up message
        isi_message_fields = {
            'sub_blocks' : \
                [{'block_id' : srv_kbd.kbd.KBD_SINGLE_PRESS_KEY_EVENT_INFO,
                  'key_code' : srv_kbd.kbd.KBD_KEY_END,
                  'key_state' : srv_kbd.kbd.KBD_KEY_UP}]}
        # Sending message
        retData = srv_kbd.kbdEventSimulation(**isi_message_fields)

        # Checking response
        if retData.get('status') != srv_kbd.kbd.KBD_OK:
            debug.err('Sending key up message failed!. ' \
                      'Status = ' + str(retData.get('status')))

    def createConnection(self, connSettings, ensureConnection = True):
        """Creates phone connection.

            Parameters

            ensureConnection    call ensureConnection if connection creation fails
                                (default = True)

            Returns True if connection was created, False if not
        """
        connectionCreated = True

        # is set to True if exception occurs with create connection
        exceptionOccurred = None

        phoneName = self.getName() != 'Main' and 'Remote phone' or 'Phone'

        # if connection already exists, return False right away
        if self.graniteConnection and self.__connectionCreated:
            self.newConnection = False
            return False

        # Ensure that when running on BlackBox mode, default USB connector is always connected
        # A try-catch clause is preferred due to there might be no USBAccessoryCard to execute this operation in some cases. 
        self._ensureBlackBoxUsbAccessoryConnection()
        if self.isFollower():
            self.sendWaitMessageToGraniteGUI(5, 'Opening phone connection in follower mode')
            debug.brf('5 sec sleep skip')
            #time.sleep(5)
                        
        # FIXME: Remove this if when C.I no longer uses old settings
        if core.FW_conf['settings'] and not core.FW_conf['old_settings']:
            connGuid = connSettings.Connection
        else:
            connParamList = core.FW_conf['old_settings'].getValue('Main/connection').split(':')
                    
            if len(connParamList) == 2:
                connGuid = connParamList[-1]
            else:
                connGuid = connParamList[0]

        # define used PMD file
        if core.FW_conf['param_pmd']:
            # if PMD has been given with --pmd, always use it
            pmdFilePath = core.FW_conf['param_pmd']
        elif self.isFollower():
            pmdFilePath = os.path.join(core.FW_conf['startup_path'], '..', 'phone_packages', 'local.pmd')
        else:
            # by default take PMD from settings
            # FIXME: Remove this if when C.I no longer uses old settings
            if core.FW_conf['settings'] and not core.FW_conf['old_settings']:
                pmdFilePath = connSettings.PmdFilePath
            else:
                pmdFilePath = core.FW_conf['old_settings'].getValue('Main/pmd-file path')

        if not os.path.isfile(pmdFilePath):
            if self.isFollower():
                raise ConnectionException('Follower mode requires local.pmd in phone_packages folder. Unable to create phone connection!')
            raise ConnectionException('Invalid PMD file (%s) given, unable to create phone connection!' % pmdFilePath)

        # create a new connection
        self.graniteConnection = GraniteConnection(pmdFilePath)

        # set default values from settings
        self.graniteConnection.defaultTimeout = \
            core.FW_conf['settings'].System.SendAndReceiveMessage

        # increase default timeout if we are tracing
        if core.FW_conf['tracing_enabled']:
            self.graniteConnection.defaultTimeout *= 5
                                    
        # get tracing connection ConnGuid
        # FIXME: Remove this if when C.I no longer uses old settings
        if core.FW_conf['settings'] and not core.FW_conf['old_settings']:
            traceConnGuid = connSettings.TraceConnection
        else:
            traceConnGuid = core.FW_conf['old_settings'].getValue(\
                'Main/trace connection').split(':')[-1]
        
        # use connection Guid by default, but in phone capture use Fuse connection name
        phoneConn = connGuid
        
        if core.FW_conf['tracing_enabled'] and core.FW_conf['trace'] == None:
            core.FW_conf['trace'] = Tracing()
        
        try:
            self.sendWaitMessageToGraniteGUI(240, 'Creating connection and loading PMD file...')
             
            # use trace connection guid if tracing is enabled
            if not self.isFullBlackBox():
                if traceConnGuid != '' and core.FW_conf['tracing_enabled']:
                    self.graniteConnection.connect(self, phoneConn, traceConnGuid) 
                else:
                    self.graniteConnection.connect(self, phoneConn)
            else:
                debug.brf('No connection mode, skip connection creation')
        
        except Exception, err:  # because of weird Fuse errors, everything must be catched here!!!
            debug.err('%s phone connection ' \
                      'failed: %s' % (self._name, str(err)))
        
            exceptionOccurred = True

            # close phone connection (to ensure that everything is disposed)
            self.closeConnection(True)

            if self.isFollower():
                debug.err('Warning: Follower mode, could not create the connection for X-files fetching')
                raise ConnectionException('Follower mode, Unable to create phone connection!')

            connectionCreated = False
        else:
            exceptionOccurred = False
            debug.brf('%s connection ok' % phoneName)
            
            # store reference to connection manager
            core.FW_conf['connection_manager'] = self.graniteConnection.ConnectionManager.Instance

        if not self.isConnected() or \
           exceptionOccurred:
            errorMessage = 'Could not open %s phone connection!'%self._name
            debug.err(errorMessage)

            try:
                if ensureConnection:
                    self.ensureConnection()
                else:
                    raise ConnectionException(errorMessage)
            finally:
                # NOTE: connection can be created by calling createConnection in ensureConnection
                connectionCreated = self.__connectionCreatedInEnsureConnection

        #self.graniteConnection.startBlxRecording('Granite_test_run.blx')
        
        # collect garbage after connection creation
        #GC.Collect()
        GC.Collect(GC.MaxGeneration, GCCollectionMode.Optimized)
        GC.WaitForPendingFinalizers()

        # set connection creation flag according to local variable
        self.__connectionCreated = connectionCreated

        # if Follower execution, disconnect USB after connection creation
        if self.isFollower() and core.FW_conf['blackbox_enabled']:
            core.FW_conf['blackbox'].connectUsb('None')

        return connectionCreated
 
    def uiEnabled(self):
        return self.__uiEnabledValue
        
    def setUiEnabled(self, value):
        self.__uiEnabledValue = value

    def closeConnection(self, forced = False):
        """Closes phone connection.
        
            Parameters
            
            forced (boolean)        call lower level close by force
        """
        if self.virtualPhone is not None:
            try:
                # Close the Virtual Phone POX connection and set reference to None
                self.virtualPhone.close()
                self.virtualPhone = None
            except Exception, err:
                debug.err('Error in stopping the Granite Virtual Phone POX Backend: %s' % str(err))

        # set reference to reference_phone to None (uses lower level connection)
        self.referencePhone = None

        if self.graniteConnection and (self.isConnected() or forced):
            # reset phone freeze when closing connection
            self._clearPhoneFreeze()
        
            # destroy granite message listener (iterator)
            self.__stopNtfListener()
            self.__graniteMessageListenerDestroy()

            #Save currently recorded blx file before closing connection
            if core.FW_conf['memory_leak_detection'] and core.FW_conf['trace']:
                core.FW_conf['trace'].traceSaveBlxAndResumeTracing(memoryLeakDetection = True, uiEnabled=self.uiEnabled())
            elif core.FW_conf['trace']:
                core.FW_conf['trace'].traceSaveBlxAndResumeTracing(uiEnabled=self.uiEnabled())
            
            if self.isFullBlackBox():
                self.__connectionCreated = False
                self.newConnection = True
                return

            result, params = \
                self.__executeConnectionOperation(self.graniteConnection.close, self.getName())

            if result == True:
                debug.brf("%s phone connection closed"%self._name)
                self.__connectionCreated = False
                self.newConnection = True
            else:
                raise ConnectionException(params)
        # just dispose connection manager when closing non-existing main connection
        elif self.getName() == 'Main' and core.FW_conf['connection_manager']:
            # NOTE: ConnectionManager's Dispose will take care of disposing everything underneath
            # NOTE2: This can be done only once!!! Otherwise it will mess up the connection layer!
            core.FW_conf['connection_manager'].Dispose()
            core.FW_conf['connection_manager'] = None

    def createReferencePhoneConnection(self):
        if core.FW_conf['backend_enabled']:
            if not self.virtualPhone:
                
                if self.isFollower() or self.isLeader():
                    core.FW_conf['settings'].TestRun.POXSIPProxy = 'SIPMGW'

                # Start the Virtual Phone POX Connection
                try:
                    self.virtualPhone = VirtualPhoneManager()
                except Exception, err:
                    debug.err('Error in initializing Granite Virtual Phone POX Backend: %s' % str(err))

        if not self.referencePhone:
            connGuid = None
            # Use commandline parameter if given.
            if core.FW_conf['param_connection_refphone']:
                connGuid = core.FW_conf['param_connection_refphone']

            # No commandline parameter given. Use parameter from settings file instead.
            if connGuid is None:
                try:
                    connGuid = core.FW_conf['settings'].Reference.Connection
                except Exception, ex:
                    debug.err('Error in reference phone settings: %s' %str(ex))

            if (connGuid != '-1' and connGuid != '' and connGuid is not None) and \
                not self.graniteConnection.ConnectionManager is None and \
                self.isConnected():
                debug.brf('Opening reference phone connection...')

                if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
                    self.referencePhone = LeaderHandler(GraniteReferencePhoneInterface(self.graniteConnection.ConnectionManager.Instance, connGuid))
                else:
                    self.referencePhone = GraniteReferencePhoneInterface(self.graniteConnection.ConnectionManager.Instance, connGuid)

                if self.referencePhone:
                    debug.brf('Reference phone connection ok')
                else:
                    debug.err("Reference phone connection couldn't be created!")
            else:
                if self.virtualPhone and core.FW_conf['settings'].TestRun.EnableVirtualReferencePhone: 
                    debug.brf('Opening reference phone connection using virtual phone interface...')
                    self.referencePhone = GraniteReferencePhoneInterface()

                    if self.referencePhone:
                        debug.brf('Virtual reference phone connection ok')
                    else:
                        debug.err("Virtual reference phone connection couldn't be created!")

        if self.isFollower() and (not self.referencePhone and len(core.FW_conf['remote_connection']) == 0):
            debug.err('WARNING: No reference/remote phone connection!')

    def startWaitMessageSender(self, comment = ''):
        """ Starts thread which sends wait messages to GUI until it is stopped

        """
        self.__waitMessageSenderThread = Thread(ParameterizedThreadStart(self.__sendWaitMessages))
        self.__waitMessageSenderThread.IsBackground = True
        self.__waitMessageSenderThread.Start(comment)

    def stopWaitMessageSender(self):
        """ Stops thread which is sending wait messages to GUI

        """
        if self.__waitMessageSenderThread and \
           self.__waitMessageSenderThread.IsAlive:
            self.__waitMessageSenderThread.Abort()

        self.__waitMessageSenderThread = None

    def startNtfListener(self):
        """Starts listener thread for display update ntf messages."""
        #if not self.__ntfListenerThread and (core.FW_conf['settings'].System.DisplayUpdateNtfsInUse or core.FW_conf['settings'].TestRun.PerformanceTesting):
        #    self.__ntfListenerThread = Thread(ThreadStart(self.__ntfListener))
        #    self.__ntfListenerThread.IsBackground = True
        #    self.__ntfListenerThread.Start()

    def __stopNtfListener(self):
        """Stops listener thread for display update ntf messages."""
        if self.__ntfListenerThread and \
           self.__ntfListenerThread.IsAlive:
            self.__ntfListenerThread.Abort()

        self.__ntfListenerThread = None

    def sendWaitMessageToGraniteGUI(self, timeout, comment):
        """Sends wait message to Granite GUI.

            Parameters
                timeout     timeout in seconds (int or float)
                comment     comment in string
        """
        assert isinstance(timeout, int) or \
               isinstance(timeout, float) or \
               isinstance(timeout, long), \
            'Invalid timeout parameter given! (%s, %s)' % (str(timeout), type(timeout))
        if isinstance(timeout, float): # round if timeout is float
            timeout = round(timeout, 3)
        if isinstance(timeout, long): # long --> int
            timeout = int(timeout)

        # multiple timeout when we are in debugging mode
        if sys.flags.debug:
            timeout *= 1000

        if comment.startswith('Info message:'):
            assert ":".join(comment.split(':')[:2])+":" in fw2guiInfoDict.values(), 'Invalid info message'
        minWaitMessageSendInterval = 2 # interval in seconds
        sendMessage = True

        # send wait message from main FW process to GUI
        # if FW is controlled by GUI
        if core.FW_conf['com_int']:
            timeToSend = time.clock()

            if self._latestWaitMessageSendTime and \
               self._latestWaitMessage == comment and \
               (timeToSend - self._latestWaitMessageSendTime) < minWaitMessageSendInterval:
                sendMessage = False

            self._latestWaitMessage = comment

            if sendMessage:
                self._latestWaitMessageSendTime = timeToSend
                core.FW_conf['com_int'].sendWaitMessage(timeout, comment)
            
    def getCommunicationAdapterInstance(self):
        """Returns CA instance from lower level."""
        return self.graniteConnection.CommunicationAdapter

# ================================ Message sending and receiving functions

    def __toISIMessage(self, *fields):
        """Convert given request fields to tuple of (ISIMessage, timeout).

           *fields: (ISIMessage instance, timeout) or
                    (receiver, request_data, timeout, utid)

           receiver is allowed to be resource id or tuple of (resource, recv_obj)
           request_data = msg_id + msg_data

           timeout and utid are optional.

           This function is needed until there is no one using the old message
           sending interface anymore.
        """
        items = len(fields)
        if not items:
             # return an empty message
            return (ISIMessage(), self.graniteConnection.defaultTimeout)

        if isinstance(fields[0], ISIMessage):
            if items > 1:
                return tuple(fields[0:2]) # just return them back..

            return (fields[0], self.graniteConnection.defaultTimeout)

        assert items > 1, 'Required fields are missing!'
        assert fields[1] is not None, 'Message id is missing!'

        # --- Handle request_data from fields[1]
        msg_id = fields[1][0]
        if type(msg_id) == type(''):
            msg_id = ord(msg_id) # FIXME: ISIMessage should handle this..
        msg = ISIMessage(msg_id=msg_id, msg_data=fields[1][1:] or None)

        # --- Handle receiver from fields[0]
        if type(fields[0]) == type(()):
            msg.resource = fields[0][0]
            msg.recv_obj = fields[0][1]
        else:
            msg.resource = fields[0]

        # --- Handle timeout from fields[2] and utid from fields[3]
        timeout = items > 2 and fields[2] or \
                  self.graniteConnection.defaultTimeout
        msg.utid = items > 3 and fields[3] or 1 # default utid is 1

        return (msg, timeout)

    def __determineServerName(self, receiver):
        """Determines ISA Server's name where message is being sent to.

            Parameters

            receiver         (resource, recv_obj)

            Returns server's name in string
        """
        serverName = ''

        # different handling for private interfaces
        #if receiver[0] == pn.PN_PRIVATE:
        #    from c_srv import srv_sapi_test
        #
        #    if receiver[1] == srv_sapi_test.sapi_private_id:
        #        serverName = 'SAPI Test server'
        #    # FIXME: Check if PN_OBJ_IM_ENGINE is changed to PN_OBJ_IMS_SERV
        #    elif receiver[1] == getattr(pn, 'PN_OBJ_IM_ENGINE', None):
        #        serverName = 'IM Engine server'
        #    else:
        #        serverName = 'Unknown private server'
        #else:
        pnNames = pn.lookup('PN_', receiver[0])

        for pnName in pnNames:
            if pnName in serverDict:
                serverName = serverDict[pnName] + ' server'
                break

        if not serverName:
            serverName = 'Unknown ISA server'

        return serverName

    def sendMsg(self, *fields, **kwargs):
        """Send ISI message to the phone.

           *fields: (ISIMessage instance, timeout) or
                    (receiver, request_data, timeout, utid)

           **kwargs: may contain
                    callEnsureConnection
                        whether ensureConnection is called in error situations or not (boolean)
                    expectedResp
                        expected response message from Granite server
                            valid values GRN_TEST_RESP, GRN_ABORT_RESP, GRN_TERM_RESP,
                            GRN_CLEAR_RESP and GRN_CLEAR_TESTCASE_RESP
                    asyncSend
                        whether message is send on async mode, no response expected (boolean)
                        used only with messages sent to other servers than Granite

           receiver is allowed to be resource id or tuple of (resource, recv_obj)
           request_data = msg_id + msg_data

           timeout and utid are optional.
        """
        req, timeout = self.__toISIMessage(*fields)

        # check if callEnsureConnection is given in kwargs
        if 'callEnsureConnection' in kwargs:
            callEnsureConnection = kwargs['callEnsureConnection']
            assert callEnsureConnection in [True, False], \
                'Valid values for callEnsureConnection are True/False'
        else:
            callEnsureConnection = True
            
        # check if expectedResp is given in kwargs
        if 'expectedResp' in kwargs:
            expectedResp = kwargs['expectedResp']
            assert expectedResp in [inc.GRN_TEST_RESP,
                                    inc.GRN_ABORT_RESP,
                                    inc.GRN_TERM_RESP,
                                    inc.GRN_CLEAR_RESP,
                                    inc.GRN_CLEAR_TESTCASE_RESP], \
                'Valid values for expectedResp are ' \
                'GRN_TEST_RESP, GRN_ABORT_RESP, GRN_TERM_RESP, '\
                'GRN_CLEAR_RESP and GRN_CLEAR_TESTCASE_RESP as integer'
                
            if expectedResp == inc.GRN_TEST_RESP:
                expectedResp = "GRN_TEST_RESP"
            elif expectedResp == inc.GRN_ABORT_RESP:
                expectedResp = "GRN_ABORT_RESP"
            elif expectedResp == inc.GRN_TERM_RESP:
                expectedResp = "GRN_TERM_RESP"
            elif expectedResp == inc.GRN_CLEAR_RESP:
                expectedResp = "GRN_CLEAR_RESP"
            elif expectedResp == inc.GRN_CLEAR_TESTCASE_RESP:
                expectedResp = "GRN_CLEAR_TESTCASE_RESP"
        else:
            expectedResp = None           

        # check if asyncSend is given in kwargs
        if 'asyncSend' in kwargs:
            asyncSend = kwargs['asyncSend']
        else:
            asyncSend = False
            
        #if u_art.purifyOnUse: # FIXME: timeout calculations should not be here!
        #    timeout *= 10

        debug.vrb("resource:%s recv_obj:%s, length:%s utid:%s msg_id:%s" % \
            (req.resource_str, req.recv_obj_str, req.length,
             req.utid, req.msg_id))

        receiver = (req.resource, req.recv_obj)

        #self.__multipleResponsesPossible = False
        
        # check if message is being sent to Granite server
        # NOTE: Variable GRN_object_id can be used directly, because object
        #              id has been queried in the beginning of test run
        # Version query is handled differently
        if receiver == (pn.PN_PRIVATE, self.objectId):
            self.__sendingMessageToGraniteServer = True
            self.__GraniteServerMessageSentCount += 1
            
            # if req.msg_id in [inc.GRN_TEST_REQ,
                              # inc.GRN_ABORT_REQ,
                              # inc.GRN_TERM_REQ,
                              # inc.GRN_CLEAR_REQ,
                              # inc.GRN_CLEAR_TESTCASE_REQ]:
                # #print '***************** sendMsg, msg_id: ', req.msg_id
                # self.__multipleResponsesPossible = True
                # self.__graniteMessageListenerSet(expectedResp)
        else:
            self.__sendingMessageToGraniteServer = False
            self.__GraniteServerMessageSentCount = 0

        #print 'sendMsg, multipleResponsesPossible: ', self.__multipleResponsesPossible
                                
        requestData = req.isi_message[9:]
        utid = req.utid

        recvDev = 0
        if req.recv_dev != None:
            recvDev = req.recv_dev
        
        resendInUse = core.FW_conf['settings'].System.ResendMessageInUse
        resendCount = core.FW_conf['settings'].System.ResendCount
        waitTimeout = core.FW_conf['settings'].System.TimeoutBetweenTries
        
        # check if message resending is enabled
        if resendInUse:     
            for i in range(resendCount):
                # if sending message to other server than Granite, send wait
                # message to GUI
                if not self.__sendingMessageToGraniteServer:
                    # send wait message from main FW process to GUI
                    self.sendWaitMessageToGraniteGUI(\
                        2 * (timeout / 1000),
                        'Communicating with %s' % \
                        self.__determineServerName(receiver))
                                
                #if self.__multipleResponsesPossible or asyncSend:
                if asyncSend:
                    # send specific messages asynchronously
                    result, params = self.__executeConnectionOperation(\
                        self.graniteConnection.sendAsynchronously,
                        receiver, requestData, utid, recv_dev = recvDev)

                    #print 'sendMsg, async send'
                else:
                    #startTime = time.clock()
                
                    result, params = self.__executeConnectionOperation(\
                        self.graniteConnection.send,
                        receiver, requestData,
                        timeout, utid, recv_dev = recvDev)

                    #print 'send  **********************************: ', time.clock() - startTime
                    #print 'sendMsg,  normal send'                
                                        
                if result == True:
                    break
                else:
                    if not self.__checkingPhoneConnection and \
                       callEnsureConnection:
                        # if connection is not ok, message resending is not worth doing anymore
                        if not self.ensureConnection():
                            # check if phone is frozen
                            self.isPhoneFrozen()
                                
                            raise ConnectionException(params)

                    # we don't send message again in the last loop time or
                    # when we don't have connection or 
                    # when we have FIDO or MUSTI connection and message length exceeds 2048
                    if (i == resendCount - 1) or \
                        not self.isConnected() or \
                        (self.getConnectionBusName() in ['FIDO', 'MUSTI', 'MUSTI_USB'] and len(req) >= 2048):
                        # check if phone is frozen
                        self.isPhoneFrozen()
                        
                        # raise ConnectionException in the last time or when connection is not open anymore
                        # if message resending doesn't help
                        raise ConnectionException(params)
                    else:
                        debug.vrb('Message sending failed: %s '
                                  'Resending message in %d seconds' % \
                                  (str(params), waitTimeout))

                        # send wait message from main FW process to GUI
                        self.sendWaitMessageToGraniteGUI(\
                            waitTimeout,
                            'Message sending failed! Resending message...')

                        time.sleep(waitTimeout)
        else:
            # if sending message to other server than Granite, send wait message
            # to GUI
            if not self.__sendingMessageToGraniteServer:
                # send wait message from main FW process to GUI
                self.sendWaitMessageToGraniteGUI(\
                    2 * (timeout / 1000),
                    'Communicating with %s' % \
                    self.__determineServerName(receiver))

            if asyncSend:
                result, params = self.__executeConnectionOperation(\
                    self.graniteConnection.sendAsynchronously,
                    receiver, requestData, utid, recv_dev = recvDev)
            else:            
                result, params = self.__executeConnectionOperation(\
                    self.graniteConnection.send,
                    receiver, requestData,
                    timeout, utid, recv_dev = recvDev)

            if result == False:
                if not self.__checkingPhoneConnection and \
                   callEnsureConnection:
                    # call ensureConnection to verify that connection is ok
                    self.ensureConnection()
                
                # check if phone is frozen
                self.isPhoneFrozen()
                    
                # raise exception which caused the error
                raise ConnectionException(params)

        debug.vrb("ok")

        return req, timeout

    def sendCommonMsg(self, commonMessageData, callEnsureConnection = True):
        """Send a common ISI message to the phone.

           Parameters

           commonMessageData        common ISI message data which is ready to
                                    be sent
           callEnsureConnection     whether connection is ensured in fail
                                    situation or not
        """
        timeout = self.graniteConnection.defaultTimeout

        # check if message resending is enabled
        if core.FW_conf['settings'].System.ResendMessageInUse:
            resendCount = core.FW_conf['settings'].System.ResendCount
            waitTimeout = core.FW_conf['settings'].System.TimeoutBetweenTries

            for i in range(resendCount):
                # send wait message from main FW process to GUI
                self.sendWaitMessageToGraniteGUI(\
                    2 * (timeout / 1000),
                    'Sending a common ISI message...')

                result, params = self.__executeConnectionOperation(\
                    self.graniteConnection.send,
                    commonMessageData = commonMessageData)

                if result == True:
                    break
                else:
                    if not self.__checkingPhoneConnection and \
                       callEnsureConnection:
                        # if connection is not ok, message resending is not worth doing anymore
                        if not self.ensureConnection():
                            # check if phone is frozen
                            self.isPhoneFrozen()
                                
                            raise ConnectionException(params)
                
                    # we don't send message again in the last loop time or
                    # when we don't have connection or 
                    # when we have FIDO or MUSTI connection and message length exceeds 2048
                    if (i == resendCount - 1) or \
                       not self.isConnected() or \
                       (self.getConnectionBusName() in ['FIDO', 'MUSTI', 'MUSTI_USB'] and len(commonMessageData) >= 2048):
                        # raise ConnectionException in the last time or when connection is not open anymore
                        # if message resending doesn't help
                        
                        # check if phone is frozen
                        self.isPhoneFrozen()
                        
                        raise ConnectionException(params)
                    else:                    
                        debug.vrb('Message sending failed: %s '
                                  'Resending message in %d seconds' % \
                                  (str(params), waitTimeout))

                        # send wait message from main FW process to GUI
                        self.sendWaitMessageToGraniteGUI(\
                            waitTimeout,
                            'Message sending failed! Resending message...')

                        time.sleep(waitTimeout)
        else:
            # send wait message from main FW process to GUI
            self.sendWaitMessageToGraniteGUI(\
                2 * (timeout / 1000),
                'Sending a common ISI message...')

            result, params = self.__executeConnectionOperation(\
                self.graniteConnection.send,
                commonMessageData = commonMessageData)

            if result == False:
                if not self.__checkingPhoneConnection and \
                   callEnsureConnection:
                    # call ensureConnection to verify that connection is ok
                    self.ensureConnection()
                    
                # check if phone is frozen
                self.isPhoneFrozen()
                    
                # raise exception which caused the error
                raise ConnectionException(params)

        debug.vrb("ok")

    def recvMsg(self, timeout = None, callEnsureConnection = True):
        """Receive ISI message from the phone.

           Parameters

           timeout                  receive timeout in milliseconds
           callEnsureConnection     whether connection is ensured in fail
                                    situation or not

           FIXME: This function should return ISIMessage instances!
        """
        #startTime = time.clock()
               
        if timeout is None:
            timeout = self.graniteConnection.defaultTimeout
            
        #print 'timeout: ', timeout

        #if u_art.purifyOnUse == 1:
        #    timeout *= 10

        debug.vrb("timeout: %u" % timeout)

        result, params = False, ()
                
        # if multiple responses possible, use iterator to get next message
        #if self.__multipleResponsesPossible:
        #    result, params = self.__executeConnectionOperation(\
        #            self.__getNextGraniteMessageFromIterator,
        #            timeout)
        #else:
        result, params = self.__executeConnectionOperation(\
                            self.graniteConnection.recv,
                            timeout)

        if result == True:
            length, data = params
        else:
            if not self.__checkingPhoneConnection and \
               callEnsureConnection:
                # call ensureConnection to verify that connection is ok
                self.ensureConnection()

            # raise exception which caused the error
            raise ConnectionException(params)

        resp = ISIMessage(isi_message=data)

        debug.vrb("ok resource:%s length:%s utid:%s msg_id:%s\n" % \
            (resp.resource_str,resp.length, resp.utid, resp.msg_id))

        # clear phone UI freeze counter if message is coming from Granite server
        if resp.resource == pn.PN_PRIVATE and resp.send_obj == self.objectId:
            self.__GraniteServerMessageSentCount = 0

        #print 'message received **********************************: ', time.clock() - startTime         
            
        return data

    def recvMsgFrom(self, sender, timeout = None):
        """Receive one ISI message from the phone (by sender).

           sender attribute: sender | (sender, object_id)
           Return value: (msg)
        """
        if timeout is None:
            timeout = self.graniteConnection.defaultTimeout

        debug.vrb("recvMsgFrom: %s" % (str(sender)))

        while 1:
            data = self.recvMsg(timeout) # raises ConnectionExceptions

            # filter command doesn't filter already received
            # messages so we must filter here again..
            if type(sender) == type(()):
                if data[3] != sender[0] or data[7] != sender[1]:
                    continue
            elif data[3] != sender:
                continue

            return data

    def recvMsgs(self, timeout = None):
        """Receive all ISI messages from the phone within timeout."""
        responses = []

        if timeout is None:
            timeout = core.FW_conf['settings'].System.ReceiveMessagesFrom

        while 1:
            try:
                responses.append(\
                    ISIMessage(isi_message = self.recvMsg(timeout)))
            except ConnectionException, e:
                if not responses:
                    raise
                else:
                    return responses

    def recvMsgsFrom(self, sender, timeout = None):
        """Receive ISI messages from the phone (by sender) within timeout.

           Caveat: each received message restarts the timeout.

           sender attribute: sender | (sender, object_id)
           Return value: [(msg_1), (msg_2) ... (msg_n)]
        """
        debug.vrb("recvMsgsFrom:%s" % str(sender))

        if timeout is None:
            timeout = core.FW_conf['settings'].System.ReceiveMessagesFrom

        responses = []

        while 1:
            try:
                resp = ISIMessage(isi_message = self.recvMsg(timeout))

                # filter command doesn't filter already received
                # messages, so we must filter here again.
                if type(sender) == type(()):
                    if resp.resource != sender[0] or resp.send_obj != sender[1]:
                        continue
                elif resp.resource != sender:
                    continue

                responses.append(resp)

            except ConnectionException, e:
                if not responses:
                    raise
                else:
                    return responses

    def transferMsg(self, *request_fields, **kwargs):
        """Transfer ISI messages.

           *request_fields: (ISIMessage_instance, timeout) OR
                            (receiver, requestData, timeout, utid)
        
           **kwargs: may contain callEnsureConnection and/or expectedResp and/or asyncSend        

           Note: timeout and utid are optional.
        """
        req, timeout = self.__toISIMessage(*request_fields)

        debug.vrb("resource:%s recv_obj:%s" % \
            (req.resource_str, req.recv_obj_str))
            
        self.sendMsg(req, timeout, **kwargs)
        return self.recvMsg(timeout)

    def queryIndications(self, servers):
        """Order indicatios from the server(s).

           Note: Several servers must be given in a list.
        """
        if type(servers) != type([]):
            servers = [servers]

        self.__executeConnectionOperation(\
            self.graniteConnection.subscribeIndications, servers)
            
    def hiddenResetAndWait(self):
        """ Performs hidden reset and waits for the phone to startup
        
            Utilizes product API to reset phone and wait
        """        
        self.__executeConnectionOperation(\
            self.graniteConnection.hiddenResetAndWait)
        
    def waitForPhoneStartup(self, timeout=60000):
        """ Waits for the phone to startup
        
            Utilizes product API to wait until phone is online
            
            Parameters:
            timeout    integer    maximum time to wait in milliseconds
                                  PAPI: Value 0 will wait the default time,
                                  other values will be added to default value
            
            Returns online state of the phone or error code, see PAPI help.
            None is returned if exception occurred.
        """          
        success, state = self.__executeConnectionOperation(\
            self.graniteConnection.waitForPhoneStartup, timeout)
        
        if success:
            return state

    def cancelIndications(self):
        """Cancel all indication orders."""
        if self.graniteConnection:
            self.__executeConnectionOperation(\
                self.graniteConnection.unsubscribeAllIndications)
                        
    def addPhoneFreezeEvent(self):
        """Function for adding phone freeze event. Usually this is message send/recv gone to timeout."""
        # start measuring phone freeze time
        if not self.__freezeStartupTime:
            self.__freezeStartupTime = time.clock()
            
        # check if phone is frozen
        self.isPhoneFrozen()
        
    def _clearPhoneFreeze(self, noUI = False):
        """Function for clearing phone freeze measuring.
        
            Parameters

            noUI        don't clear UI freeze measuring (default = False)
        """
        self.__freezeStartupTime = 0

        if not noUI:
            self.__GraniteServerMessageSentCount = 0

    def _isPhoneFrozen(self):
        """Method for checking whether phone is frozen or not.
        """
        if self.__freezeStartupTime and \
           (time.clock() - self.__freezeStartupTime) >= self.__freezeLimit:
            return True
        else:
            return False

    def isPhoneFrozen(self):
        """Check is phone frozen and test case will be failed according to that.
        """
        if self._isPhoneFrozen():
            debug.brf('Phone freeze detected')

            #If running on BlackBox: disconnect / reconnect phone power to fully reset the connection
            #self._blackBoxResetPhonePower()
           
            # if phone is frozen, fail the test case        
            raise TestException('Remote phone freeze detected', self)

    def isPhoneUIFrozen(self):
        """Method for checking whether phone UI is frozen or not.
        """
        # if we haven't been able to communicate with Granite server for a while --> phone UI freeze
        if self.__GraniteServerMessageSentCount > self.__GraniteServerMessageSentLimit:
            return True
        else:
            return False

    def isConnected(self):
        """Returns lower level phone connection status."""
        connected = False

        try:
            if self.graniteConnection:
                result, connected = self.__executeConnectionOperation(self.graniteConnection.isConnected)
        except Exception, err:
            debug.err('Fatal error in phone connection layer or Fuse when calling isConnected: %s' % str(err))
            
        return connected

    def resetPhone(self, errorReason = ''):
        """Reset phone (whitebox) or disconnect/connect power (blackbox) in order to recover from invalid phone state.
           Exception will be raised (result == NO RESULT)

            Parameters

            errorReason         error reason string
        """
        # if test execution has been aborted, reset phone will not be performed
        if core.FW_conf['should_stop']:
            return

        if not core.FW_conf['settings'].TestRun.AllowPhoneReset and self.getName() == 'Main':
            message = self.getName()
            if self.isFollower():
                message += ' phone power reset is needed but reset is not allowed in Follower. Exit.'
                debug.brf(message)
                # fc = core.FW_conf['follower_client'].gfc
                # fc.ClientFiasco(fc.GetClientId(), "\n\n ** Phone reset required but reset is not allowed. Exit. **\n\n", fc.CurrentTestCase[0])
                sys.exit()
            else:
                message += ' phone reset is needed but reset is not allowed. Execution is on hold'
                core.FW_conf['mail_sender'].holdExecutionAndSendMail(message, subject='Marble execution paused')
            return

        if core.FW_conf['blackbox_enabled'] and self.getName() == "Main":
            errorReason += '\nMarble had to disconnect and connect the power in order to recover from the situation!'
            self._blackBoxResetPhonePower()
            self.warn(errorReason)
        elif self.isFollower() and not self.isFullBlackBox():
            errorReason += '\nReset requested but in Follower mode, cannot do sw reset!'
            self.warn(errorReason)
        else:
            errorReason += '\nMarble will reset the phone in order to recover from the situation!'
            self.warn(errorReason)
            self.resetTarget()

        # ensure connection
        self.ensureConnection()
        
        if self.isConnected():
            # activate Granite server
            self.activateGraniteServer(forced = True, ensureConnection = False)

        raise Exception(errorReason)

    def __sendWaitMessages(self, comment):
        """Sends wait messages to Granite UI in a loop. Started in a thread.
        
            Parameters

            comment         comment string to be sent
        """
        while True:
            try:
                self.sendWaitMessageToGraniteGUI(10, comment)
                time.sleep(10)
            except Exception:
                # in case of exception, just break from the loop
                break

    def __ntfListener(self):
        """Starts message iterator for display update ntf messages. """
        self.__graniteMessageListenerSet('GRN_DISPLAY_UPDATE_NTF')

        while True:
            msg = None

            try:
                msg = self.__getNextDisplayUpdateMessageFromIterator()

                if msg:                
                    with self.perfReportLock:
                        #debug.brf('msg: %s' % msg)
                        grnNtf = GRNDisplayUpdateNtf(isi_message = msg)

                        ## create performance report instance
                        #if core.FW_conf['settings'].TestRun.PerformanceTesting:
                        #    if not self.perfReport:
                        #        self.perfReport = NodeUtils('performance_report', True)

                        #debug.brf('grnNtf.x: %s' % grnNtf.x)
                        #debug.brf('grnNtf.y: %s' % grnNtf.y)
                        #debug.brf('grnNtf.width: %s' % grnNtf.width)
                        #debug.brf('grnNtf.height: %s' % grnNtf.height)
                        #debug.brf('grnNtf.fps: %s' % grnNtf.fps)
                        #debug.brf('grnNtf.time_stamp: %s' % grnNtf.time_stamp)
                        #debug.brf('grnNtf.type: %s' % grnNtf.type)

                        # check that we have screen update data
                        if grnNtf.type.startswith('y_screen_update') and \
                            (grnNtf.x != 0 or grnNtf.y != 0 or grnNtf.width != 0 or grnNtf.height != 0):
                            screenUpdateNode = NodeUtils('screen_update', True)
                            screenUpdateNode.setAttribute('x', grnNtf.x)
                            screenUpdateNode.setAttribute('y', grnNtf.y)
                            screenUpdateNode.setAttribute('width', grnNtf.width + 1) # +1, because it seems to be 239 instead of 240
                            screenUpdateNode.setAttribute('height', grnNtf.height + 1) # +1, because it seems to be 319 instead of 320
                            screenUpdateNode.setAttribute('fps', grnNtf.fps)
                            screenUpdateNode.setAttribute('time_stamp', grnNtf.time_stamp)
                        else:
                            screenUpdateNode = None

                        uiChanged = False

                        # start UI movement logging
                        if grnNtf.type == 'physics;start':
                            #debug.brf('physics;start')

                            if self.__uiMovementNode:
                                self.__uiMovementNode.setAttribute('duration', grnNtf.time_stamp - long(self.__uiMovementNode.getAttribute('start')))                            
                                self.__uiMovementNode.setAttribute('stop', grnNtf.time_stamp)
                                #debug.brf('physics;start, uiChanged --> True')
                                if self.__uiMovementNode.getChildNodes():
                                    if self.testStepPerfNode:
                                        self.testStepPerfNode.append(self.__uiMovementNode.clone())
                                    elif self.perfReport:
                                        self.perfReport.append(self.__uiMovementNode.clone())

                                uiChanged = True

                            self.__uiMovementNode = NodeUtils('ui_movement', True)
                            self.__uiMovementNode.setAttribute('start', grnNtf.time_stamp)
                        elif grnNtf.type == 'physics;stop':
                            if self.__uiMovementNode:
                                self.__uiMovementNode.setAttribute('duration', grnNtf.time_stamp - long(self.__uiMovementNode.getAttribute('start')))
                                self.__uiMovementNode.setAttribute('stop', grnNtf.time_stamp)
                                #debug.brf('physics;stop, uiChanged --> True')
                                uiChanged = True
                        elif screenUpdateNode:
                            #if not self.__uiMovementNode:
                            #debug.brf('y_screen_update, uiChanged --> True')
                            uiChanged = True
                        elif grnNtf.type == 'topmost-screen-changed':
                            appChanged = NodeUtils('application_changed', True)
                            appChanged.setAttribute('time', grnNtf.time_stamp)

                            if self.testStepPerfNode:
                                self.testStepPerfNode.append(appChanged)
                            elif self.perfReport:
                                self.perfReport.append(appChanged)

                            uiChanged = True
                        else:
                            #debug.brf('%s, uiChanged --> True' % grnNtf.type)
                            uiChanged = True

                        # set UI changed to scripting level and throw UI changed event
                        if uiChanged:
                            #debug.brf('%s, uiChanged --> True' % grnNtf.type)
                            self.uiState.setUIChanged(True)
                            self.THROW_UI_CHANGED()

                        # add screen update node to movement node
                        if screenUpdateNode and self.__uiMovementNode and \
                            not self.__uiMovementNode.getAttribute('stop'):
                            self.__uiMovementNode.append(screenUpdateNode.clone())
                            screenUpdateNode = None

                        # add screen update node to performance report
                        if screenUpdateNode:
                            if self.testStepPerfNode:
                                self.testStepPerfNode.append(screenUpdateNode.clone())
                            elif self.perfReport:
                                self.perfReport.append(screenUpdateNode.clone())
                
                        # add movement node to performance report
                        if self.__uiMovementNode and self.__uiMovementNode.getAttribute('stop'):
                            if self.__uiMovementNode.getChildNodes():                        
                                if self.testStepPerfNode:
                                    self.testStepPerfNode.append(self.__uiMovementNode.clone())
                                elif self.perfReport:
                                    self.perfReport.append(self.__uiMovementNode.clone())

                            #debug.brf('self.__uiMovementNode: %s' % self.__uiMovementNode.toprettyxml())
                            self.__uiMovementNode = None
            except Exception, err:
                debug.out('Error in NTF message iterator: %s, message: %s' % (str(err), msg))

        self.__graniteMessageListenerDestroy()
                
    def __getNextDisplayUpdateMessageFromIterator(self, timeout = 9999999):
        """Returns next Granite message using iterator.
        
            Timeout is handled here because there's no possibility to interrupt the iterator.
            Iterator timeout should be increased if too much performance is lost!

            Parameters
            
            timeout     timeout in milliseconds
        """
        startTime = time.clock()
                
        while True:
            # just wait if there's no connection
            if not self.isConnected():
                time.sleep(0.1)
                continue

            self.__graniteMessageIterator.Timeout = 100
            message = self.__graniteMessageIterator.GetNextPhonet()
            
            if not message:            
                # This is needed to prevent error message when closing the connection
                timeSpent = time.clock() - startTime
                if timeSpent < timeout:
                    continue
                    
                return None
            else:
                # convert message to Granite message (list of ints)
                graniteMessage = [int(x) for x in message.ToArray()]

                #message.Dispose()

                return graniteMessage


# ================================ file system operations

    def __getFolderContentPath(self, fileSystemPath):
        """Prepare path definitions for getFolderContent.
            Backslash is added at the end if folder path is passed.

            Parameters

            fileSystemPath      file or folder path in the phone
                                (+ file path with wildcard)

            Return value:       Proper path for getFolderContent call
        """
        rAsterisk = re.compile(r'^[*]$', re.I)
        rFile = re.compile(r'^[a-z_0-9*?]+\.[a-z_0-9*?]+$', re.I)

        # add backslash if folder path was passed
        fileSystemItem = fileSystemPath.split('\\').pop()
        if not rFile.match(fileSystemItem) and \
           not rAsterisk.match(fileSystemItem):
            fileSystemPath += '\\'

        return fileSystemPath

    def createFile(self, localData, phoneFilePath, internal = True):
        """Creates file to the phone.

            Parameters

            localData           local file path in format
                                'C:\\TEMP\\test.txt'
                                or data bytes in a list
            phoneFilePath       file path in the phone in format
                                'C:\\predefgallery\\test.txt'
        """
        try:
            sourcePath = ""
            if not internal:
                self.comment('createFile(%s, %s)' % (localData, phoneFilePath))

            # start sending wait messages to GUI, because this may take a while
            self.startWaitMessageSender('Writing file into the phone...')

            # create file using data from a local file
            if isinstance(localData, (str, unicode)):
                sourcePath = localData
                
                assert os.path.isfile(sourcePath), 'Invalid file / directory: "%s" given!' % localData

                # separate file name and directory
                if '.' in phoneFilePath:
                    phoneDirPath, phoneFileName = os.path.split(phoneFilePath)
                else:
                    phoneDirPath = phoneFilePath
                    phoneFileName = None
            
                # check whether file names are different
                # if they differ, copy of the original file will be made and removed afterwards
                # FIXME: REMOVE THIS WHEN LOWER LAYER SUPPORTS GIVING DESTINATION NAME
                tempFilePath = None
            
                if phoneFileName and \
                   os.path.basename(sourcePath) != phoneFileName:
                    tempFilePath = os.path.join(core.FW_conf['settings'].System.PathForTempFiles,
                                                phoneFileName)
                    copyfile(sourcePath, tempFilePath)
                    sourcePath = tempFilePath
                        
                result, returnValue = \
                    self.__executeConnectionOperation(
                                                self.graniteConnection.writeFile,
                                                sourcePath, phoneDirPath)
                                            
                # remove temporary file                                                    
                if tempFilePath:
                    os.remove(tempFilePath)
                                            
                if not result:
                    if isinstance(returnValue, GraniteFileSystemException):
                        #if int(returnValue) == constants.FILETRANSFER_E_ENOSPC:
                        #    # remove incomplete file from the phone
                        #    self.removeFile(phoneFilePath)
                        #    raise ConnectionException('Memory Full: %s' % returnValue)
                        #else:
                        pass # FIXME: TEMPORARILY pass these exceptions
                        #raise ConnectionException('createFile(1): FAILED, '
                        #                          'target: %s, reason: %s' %
                        #                          (phoneFilePath, returnValue))
                    else:
                        raise ConnectionException('createFile(1): FAILED, '
                                                  'target: %s, reason: %s' %
                                                  (phoneFilePath, returnValue))
            # create file using data bytes from a list
            elif isinstance(localData, (list, file)):
                result, returnValue = \
                    self.__executeConnectionOperation(
                                            self.graniteConnection.createFileData)
                if not result:
                    raise ConnectionException('createFile(2): FAILED, '
                                              'target: %s, reason: %s' %
                                              (phoneFilePath, returnValue))
                else:
                    fileData = returnValue
                    fileTime = fileData.GetCurrentTimeItem()
                    fileTime.Year, fileTime.Month, fileTime.Day, fileTime.Hour, \
                        fileTime.Minute, fileTime.Second = self.getTimeStamp()

                    if isinstance(localData, file):
                        data = map(ord, localData.read())
                        localData.close()
                        localData = data

                    for byte in localData:
                        fileData.Write(byte, 1)

                    result, returnValue = \
                        self.__executeConnectionOperation(
                                            self.graniteConnection.writeFromBuffer,
                                            phoneFilePath, fileData)
                    if not result:
                        if isinstance(returnValue, GraniteFileSystemException):
                            if int(returnValue) == constants.FILETRANSFER_E_ENOSPC:
                                # remove incomplete file from the phone
                                self.removeFile(phoneFilePath, internal = internal)
                                raise ConnectionException('Memory Full: %s' %
                                                          returnValue)
                            else:
                                raise ConnectionException('createFile(3): FAILED, '
                                                          'target: %s, reason: %s' %
                                                          (phoneFilePath, returnValue))
                        else:
                            raise ConnectionException('createFile(3): FAILED, '
                                                      'target: %s, reason: %s' %
                                                      (phoneFilePath, returnValue))
            else:
                raise ConnectionException('createFile: FAILED, target: %s '
                                          'reason: invalid data' % phoneFilePath)

            # run also SX code if creation was not internal one
            if not internal and self.uiEnabled():
                if sourcePath:
                    fileName = os.path.basename(sourcePath)
                    if '.' in os.path.basename(phoneFilePath):
                        phoneFilePath = os.path.dirname(phoneFilePath)
                    self.srv.gallery.updateMetadata(os.path.join(phoneFilePath,fileName))
                else:
                    self.srv.gallery.updateMetadata(phoneFilePath)
                self.delay(200)
        finally:
            # stop sending wait messages to GUI
            self.stopWaitMessageSender()

    def createFolder(self, phoneFolderPath, internal = True):
        """Create folder to phone.

            Parameters

            phoneFolderPath     folder path in the phone in format
                                'C:\\predefgallery\\testFolder'
        """
        try:
            if not internal:
                self.comment('createFolder(%s)' % phoneFolderPath)

            # start sending wait messages to GUI, because this may take a while
            self.startWaitMessageSender('Creating folder into the phone...')

            result, returnValue = \
                self.__executeConnectionOperation(
                                            self.graniteConnection.createFolder,
                                            phoneFolderPath)
            if not result:
                raise ConnectionException('createFolder: FAILED, target: %s, '
                                    'reason: %s' % (phoneFolderPath, returnValue))
        finally:
            # stop sending wait messages to GUI
            self.stopWaitMessageSender()

    def fileExists(self, targetFilePath, internal = True):
        """Check file existence from the phone.
             files/folders.

            Parameters

            targetFilePath      phone's file path in format
                                ('C:\\predefhiddenfolder\\granite.startup')
        """
        if not internal:
            self.comment('fileExists(%s)' % targetFilePath)

        self.sendWaitMessageToGraniteGUI(10,
                                'Checking file existence from the phone...')

        result, returnValue = \
            self.__executeConnectionOperation(
                                        self.graniteConnection.fileExists,
                                        targetFilePath)
        if not result:
            raise ConnectionException('fileExists: FAILED, target: %s, '
                                'reason: %s' % (targetFilePath, returnValue))
                                
        return returnValue

    def getAttribute(self, phoneItemPath, internal = True):
        """Get file or folder attribute from the phone.

            Parameters

            phoneItemPath       file or folder path in the phone in format
                                'C:\\predefgallery\\testFolder\\test.txt',
                                'C:\\predefgallery\\testFolder'

            Return value:       file system item attribute value
        """
        if not internal:
            self.comment('getAttribute(%s)' % phoneItemPath)

        self.sendWaitMessageToGraniteGUI(10,
                                'Getting file attributes from the phone...')

        fileAttribute = FILE2ATTR('FILE2_ANORMAL')
                                
        # put file to search pattern
        if '.' in phoneItemPath:
            result, returnValue = \
                self.__executeConnectionOperation(
                                            self.graniteConnection.getFolderContent,
                                            os.path.dirname(phoneItemPath),
                                            os.path.basename(phoneItemPath))
        else:                               
            result, returnValue = \
                self.__executeConnectionOperation(
                                            self.graniteConnection.getFolderContent,
                                            phoneItemPath)
                                            
        if not result or not returnValue.Count:
            raise ConnectionException('getAttribute: FAILED, target: %s, '
                                'reason: %s' % (phoneItemPath, returnValue))
        else:
            itemContent = returnValue
            # if itemContent[0].AttributeArchive == constants.eFileSystemSet:
                # fileAttribute |= constants.eFileAttributeArchive
            # if itemContent[0].AttributeCopyright == constants.eFileSystemSet:
                # fileAttribute |= constants.eFileAttributeCopyright
            # if itemContent[0].AttributeDirectory == constants.eFileSystemSet:
                # fileAttribute |= constants.eFileAttributeDirectory
            # if itemContent[0].AttributeHidden == constants.eFileSystemSet:
                # fileAttribute |= constants.eFileAttributeHidden
            # if itemContent[0].AttributeReadOnly == constants.eFileSystemSet:
                # fileAttribute |= constants.eFileAttributeReadOnly
            # if itemContent[0].AttributeSystem == constants.eFileSystemSet:
                # fileAttribute |= constants.eFileAttributeSystem        
                
            if itemContent[0].AttributeArchive == self.graniteConnection.EnumFileSystemItemAttributeType.eFileSystemSet:
                fileAttribute |= FILE2ATTR('FILE2_ARCHIVE')
            if itemContent[0].AttributeCopyright == self.graniteConnection.EnumFileSystemItemAttributeType.eFileSystemSet:
                fileAttribute |= FILE2ATTR('FILE2_ACOPYRIGHT')
            if itemContent[0].AttributeDirectory == self.graniteConnection.EnumFileSystemItemAttributeType.eFileSystemSet:
                fileAttribute |= FILE2ATTR('FILE2_ADIRENT')
            if itemContent[0].AttributeHidden == self.graniteConnection.EnumFileSystemItemAttributeType.eFileSystemSet:
                fileAttribute |= FILE2ATTR('FILE2_AHIDDEN')
            if itemContent[0].AttributeReadOnly == self.graniteConnection.EnumFileSystemItemAttributeType.eFileSystemSet:
                fileAttribute |= FILE2ATTR('FILE2_ARDONLY')
            if itemContent[0].AttributeSystem == self.graniteConnection.EnumFileSystemItemAttributeType.eFileSystemSet:
                fileAttribute |= FILE2ATTR('FILE2_ASYSTEM')
            if itemContent[0].AttributeVolume == self.graniteConnection.EnumFileSystemItemAttributeType.eFileSystemSet:
                fileAttribute |= FILE2ATTR('FILE2_AVOLUME')
                
        return fileAttribute

    def getFolderContent(self, phoneFolderPath, recursive = True, internal = True):
        """Get folder content from the phone and separate files and folders.

            Parameters

            phoneFolderPath     folder path in the phone in format
                                'C:\\predefgallery'

            recursive           recursive flag

            Return value:       tuple of file and folder name lists
        """
        fileItems, folderItems = [], []

        try:
            if not internal:
                self.comment('getFolderContent(%s)' % phoneFolderPath)

            # start sending wait messages to GUI, because this may take a while
            self.startWaitMessageSender('Getting folder content from the phone...')

            phoneFolderPath = self.__getFolderContentPath(phoneFolderPath)
                               
            # check if search pattern was given
            if os.path.splitext(phoneFolderPath)[-1] != '':
                phoneFolderPath, searchPattern = os.path.split(phoneFolderPath)
            
                result, returnValue = \
                    self.__executeConnectionOperation(
                                                self.graniteConnection.getFolderContent,
                                                phoneFolderPath, searchPattern)
            else:    
                searchPattern = None
            
                result, returnValue = \
                    self.__executeConnectionOperation(
                                                self.graniteConnection.getFolderContent,
                                                phoneFolderPath)
                                            
            if not result:
                raise ConnectionException('getFolderContent: FAILED, target: %s, '
                                    'reason: %s' % (phoneFolderPath, returnValue))
            elif returnValue.Count == 0:
                return fileItems, folderItems
            else:
                folderContent = returnValue
                for index in range(folderContent.Count):
                    if folderContent[index].AttributeDirectory == \
                       self.graniteConnection.EnumFileSystemItemAttributeType.eFileSystemSet:
                        folderItems.append(folderContent[index].Name)
                        if recursive:
                            subFiles, subFolders = self. \
                                getFolderContent(folderContent[index].FullName)
                            fileItems.extend(subFiles)
                            folderItems.extend(subFolders)
                    else:
                        fileItems.append(folderContent[index].Name)

            return fileItems, folderItems
        finally:
            # stop sending wait messages to GUI
            self.stopWaitMessageSender()

    def getAvailableFreeSpace(self, drive, internal = True):
        if not internal:
            self.comment('getAvailableFreeSpace(%s)' % drive)
        
        result, returnValue = \
            self.__executeConnectionOperation(
                                        self.graniteConnection.getAvailableFreeSpace,
                                        drive)

        if not result and \
           isinstance(returnValue, GraniteFileSystemException):
            return # FIXME: TEMPORARILY pass these exceptions

        if not result:
            raise ConnectionException('readFile: FAILED, target: %s, '
                                'reason: %s' % (drive, returnValue))
    
        return returnValue
        
    def hasMemoryCard(self, internal = True):
        if not internal:
            self.comment('hasMemoryCard()')

        result, returnValue = \
            self.__executeConnectionOperation(
                                        self.graniteConnection.hasMemoryCard)
        if not result and \
           isinstance(returnValue, GraniteFileSystemException):
            return # FIXME: TEMPORARILY pass these exceptions

        if not result:
            raise ConnectionException('hasMemoryCard: FAILED')
        return returnValue

    def fill(self, path, freemem = 0, filesize = 10, internal = True):
        if not internal:
            self.comment('fill(%s, %s, %s)' % (path, freemem, filesize))

        result, returnValue = \
            self.__executeConnectionOperation(
                                        self.graniteConnection.fill,
                                        path,freemem,filesize)

        if not result and \
           isinstance(returnValue, GraniteFileSystemException):
            return # FIXME: TEMPORARILY pass these exceptions

        if not result:
            raise ConnectionException('fill: FAILED, target: %s, '
                                'reason: %s' % (path, returnValue))
        list = []
        for item in returnValue:
            list.append(item.ToString())
    
        return list 

    def readFile(self, phoneFilePath, localFilePath, internal = True):
        """Read file from the phone.

            Parameters

            phoneFilePath   file path in the phone in format
                            'C:\\predefgallery\\test.txt'

            localFilePath   local file path in format
                            'C:\\TEMP\\test.txt'
        """
        try:
            if not internal:
                self.comment('readFile(%s, %s)' % (phoneFilePath, localFilePath))

            # start sending wait messages to GUI, because this may take a while
            self.startWaitMessageSender('Reading file from the phone...')

            result, returnValue = \
                self.__executeConnectionOperation(
                                            self.graniteConnection.readFile,
                                            phoneFilePath, localFilePath)

            if not result and \
               isinstance(returnValue, GraniteFileSystemException):
                return # FIXME: TEMPORARILY pass these exceptions
                                        
            if not result:
                raise ConnectionException('readFile: FAILED, target: %s, '
                                    'reason: %s' % (phoneFilePath, returnValue))
        finally:
            # stop sending wait messages to GUI
            self.stopWaitMessageSender()

    def removeFile(self, phoneFilePath, forced = False, internal = True):
        """Removes file from the phone.

            Parameters

            phoneFilePath   file path in the phone in format
                            'C:\\predefgallery\\test.txt'

            forced          Defines if deletion is also forced for readonly,
                            system and copyrighted files.
        """
        protected = 0
        errorString = 'File %r NOT removed from the phone!' % phoneFilePath

        try:
            if not internal:
                self.comment('removeFile(%s)' % phoneFilePath)

            # start sending wait messages to GUI, because this may take a while
            self.startWaitMessageSender('Removing file from the phone...')

            if not self.fileExists(phoneFilePath):
                errorString = 'File %s NOT existing on the phone!' % phoneFilePath
                debug.err(errorString)
            else:
                if not forced:     
                    fileAttribute = self.getAttribute(phoneFilePath)
                    protected = fileAttribute & (FILE2ATTR('FILE2_ACOPYRIGHT') | \
                                                 FILE2ATTR('FILE2_AHIDDEN') | \
                                                 FILE2ATTR('FILE2_ARDONLY') | \
                                                 FILE2ATTR('FILE2_ASYSTEM'))
                # file is not protected.
                if not protected:
                    self.setAttribute(phoneFilePath, FILE2ATTR('FILE2_ANORMAL'))

                    result, returnValue = \
                        self.__executeConnectionOperation(
                                                self.graniteConnection.removeFile,
                                                phoneFilePath)
                    if not result:
                        errorString = 'removeFile: FAILED, target: %s, reason: %s' % \
                                      (phoneFilePath, returnValue)

                        #debug.err(errorString)
                        self.warn(errorString)

                # file is protected
                elif protected:
                    self.warn(errorString)
                # file is protected
                else:
                    debug.err(errorString)

            # run also SX code if removal was not internal one
            if not internal and self.uiEnabled():
                self.srv.gallery.removeMetadataFromCache(phoneFilePath)
        finally:
            # stop sending wait messages to GUI
            self.stopWaitMessageSender()

    def removeFolder(self, phoneFolderPath, forced = False, internal = True):
        """Remove folder from the phone.

            Parameters

            phoneFolderPath     folder path in the phone in format
                                'C:\\predefgallery\\testFolder'

            forced              Defines if deletion is also forced for
                                readonly, system and copyrighted folders.
        """
        protected = 0
        errorString = \
                    'Folder %r NOT removed from the phone!' % phoneFolderPath

        try:
            if not internal:
                self.comment('removeFolder(%s)' % phoneFolderPath)

            # start sending wait messages to GUI, because this may take a while
            self.startWaitMessageSender('Removing folder from the phone...')

            if not forced:
                fileAttribute = self.getAttribute(phoneFolderPath)
                protected = fileAttribute & (FILE2ATTR('FILE2_ACOPYRIGHT') | \
                                             FILE2ATTR('FILE2_AHIDDEN') | \
                                             FILE2ATTR('FILE2_ARDONLY') | \
                                             FILE2ATTR('FILE2_ASYSTEM'))
            # file is not protected.
            if not protected:
                self.setAttribute(phoneFolderPath, FILE2ATTR('FILE2_ADIRENT'))

                result, returnValue = \
                    self.__executeConnectionOperation(
                                                self.graniteConnection.removeFolder,
                                                phoneFolderPath)
                if not result:
                    errorString = 'removeFolder: FAILED, target: %s, reason: %s' % \
                                   (phoneFolderPath, returnValue)

                    debug.err(errorString)
                    self.warn(errorString)
            # file is protected
            elif protected:
                self.warn(errorString)
            # file is protected
            else:
                debug.err(errorString)
        finally:
            # stop sending wait messages to GUI
            self.stopWaitMessageSender()

    def removeItem(self, phoneItemPath, forced = False, internal = True):
        """Removes file or folder from the phone.

            Parameters

            phoneItemPath   file or folder path in the phone in format
                            'C:\\predefgallery\\testFolder\\test.txt',
                            'C:\\predefgallery\\testFolder

            forced          Defines if deletion is also forced for readonly,
                            system and copyrighted items.
        """
        if not internal:
            self.comment('removeItem(%s)' % phoneItemPath)

        # put file to search pattern
        if '.' in phoneItemPath:
            result, returnValue = \
                self.__executeConnectionOperation(
                                            self.graniteConnection.getFolderContent,
                                            os.path.dirname(phoneItemPath),
                                            os.path.basename(phoneItemPath))
        else:                               
            result, returnValue = \
                self.__executeConnectionOperation(
                                            self.graniteConnection.getFolderContent,
                                            phoneItemPath)

        if not result:
            raise ConnectionException('removeItem: FAILED, target: %s, '
                                'reason: %s' % (phoneItemPath, returnValue))
        elif not returnValue.Count:
            debug.err('Folder %s already empty' % phoneFolderPath)
        else:
            fileSystemItem = returnValue
            if fileSystemItem[0].AttributeDirectory == \
               self.graniteConnection.EnumFileSystemItemAttributeType.eFileSystemSet:
                result = self.removeFolder(phoneItemPath, forced)
            else:
                result = self.removeFile(phoneItemPath, forced, internal)

    def removeItems(self, phoneFolderPath, recursive = True, forced = False, internal = True):
        """Removes items from a folder in the phone.

            Parameters

            phoneFolderPath     folder path in the phone in format
                                'C:\\predefgallery\\testFolder'

            forced              Defines if deletion is also forced for
                                readonly, system and copyrighted items.
        """
        if not internal:
            self.comment('removeItems(%s)' % phoneFolderPath)

        phoneFolderPath = self.__getFolderContentPath(phoneFolderPath)

        if self.fileExists(phoneFolderPath):

            result, returnValue = \
                self.__executeConnectionOperation(
                                            self.graniteConnection.getFolderContent,
                                            phoneFolderPath)

            if not result:
                raise ConnectionException('removeItems: FAILED, target: %s, '
                                    'reason: %s' % (phoneFolderPath, returnValue))
            elif not returnValue.Count:
                debug.err('Folder %s already empty' % phoneFolderPath)
            else:
                folderContent = returnValue
                for index in range(folderContent.Count):
                    if folderContent[index].AttributeDirectory == \
                       self.graniteConnection.EnumFileSystemItemAttributeType.eFileSystemSet:
                        if recursive:
                            result = self.removeFolder(
                                            folderContent[index].FullName, forced)
                    else:
                        result = self.removeFile(
                                            folderContent[index].FullName, forced, internal)
        else:
            debug.err('There is no folder %s in phone!' % phoneFolderPath)

    def setAttribute(self, phoneItemPath, itemAttribute, internal = True):
        """Set file or folder attributes from the phone.

            Parameters

            phoneItemPath   file path in the phone in format
                            'C:\\predefgallery\\test.txt'

            itemAttribute   see file server's constants
        """
        if not internal:
            self.comment('setAttribute(%s, %s)' % (phoneItemPath, itemAttribute))

        self.sendWaitMessageToGraniteGUI(10,
                                'Setting file attributes from the phone...')

        result, returnValue = \
            self.__executeConnectionOperation(
                                        self.graniteConnection.setAttribute,
                                        phoneItemPath, itemAttribute)
        if not result:
            raise ConnectionException('setAttribute: FAILED, target: %s, '
                                'reason: %s' % (phoneItemPath, returnValue))

    def getTimeStamp(self, unique = True):
        global TIME_STAMP

        newStamp = time.localtime()
        newStamp = [int(item) for item in newStamp]
        newStamp = time.mktime(newStamp)
        if unique and newStamp <= TIME_STAMP:
            newStamp = TIME_STAMP + 1
            if newStamp % 2:
                newStamp += 1

        TIME_STAMP = newStamp

        return time.localtime(newStamp)[:6]


#class DisplayUpdateNtfListener(Thread):

#    def __init__(self, timeout):
#        Thread.__init__(self)

#        self.__graniteMessageIterator = None
#        self.setDaemon(True)
#        self.timeout = timeout
#        self.shouldStop = False
#        self.isRunning = False
#        self.start()

#    def run(self):
#        """ Notify listener main-loop 

#            This method starts message listener and receives notifications from Granite server. 
#            If data has been splitted in several notifications, all data is gathered and parsed.

#            Handling function is then called with xml-data as attribute.

#        """
#        self.__graniteMessageListenerSet('GRN_DISPLAY_UPDATE_NTF')
#        wbxml = []
#        prevUtid = None
#        self.isRunning = True
#        while not self.shouldStop:
#            msg = self.__getNextDisplayUpdateMessageFromIterator(self.timeout)
#            if msg:
#                grnNtf = grnISINtf(isi_message = msg[1])
#                if grnNtf == None: #Continue listening if unknown message is received
#                    continue

#                #Index is unsigned long integer which is packed in 4 bytes. Combine index data from signed short integers.
#                currentIndex = ((grnNtf.data_index_1<<24)&0xffffffffL)+((grnNtf.data_index_2<<16)&0xffffffffL) + (grnNtf.data_index_3<<8)+grnNtf.data_index_4

#                if len(wbxml) and prevUtid!=grnNtf.utid and currentIndex:#Discard data if messages have been lost
#                    wbxml = []
#                    if currentIndex!=0:
#                        continue

#                wbxml.extend(grnNtf.wbxml_data)
#                if grnNtf.continue_flag:#More data should be received before it can be parsed
#                    prevIndex = currentIndex
#                    prevUtid = grnNtf.utid
#                    continue
#                else:#All data is received
#                    prevIndex, currentIndex, prevUtid = None,None,None
#                    try:#Parsing fails if some part(s) of the message are lost
#                        respTeststep = wbxml_parser.parseWbxml(wbxml)
#                        wbxml = []
                        
#                        # call handler function
#                        self.setUIChanged(respTeststep["text"])
#                    except Exception, e:
#                        continue #Continue listening for notifications if parsing fails

#        debug.out("DisplayUpdateNtfListener stopped")
#        self.isRunning = False
#        self.displayUpdateMessageListenerDestroy()


#    def stop(self):
#        self.shouldStop = True
#        time.sleep(0.2)#Wait for GetNextPhonet-timeout before exiting

#    def __graniteMessageListenerSet(self, expectedResp):
#        """Creates Granite message iterator. If it already exists, move pointer to end.
        
#            Parameters
            
#            expectedResp        expected response to be iterated
#        """
#        # dispose and delete previous iterator
#        self.displayUpdateMessageListenerDestroy()
            
#        # create new iterator for specific response message
        
#        self.__graniteMessageIterator = \
#            core.FW_conf['connection'].graniteConnection.MessageSender.Iterator.CreatePrivate("PN_PRIVATE_GRANITE", expectedResp)        
                
#    def __getNextDisplayUpdateMessageFromIterator(self, timeout):
#        """Returns next Granite message using iterator.
        
#            Timeout is handled here because there's no possibility to interrupt the iterator.
#            Iterator timeout should be increased if too much performance is lost!

#            Parameters      timeout     timeout in milliseconds
#        """
#        startTime = time.clock()
                
#        i = 0    
#        while True and not self.shouldStop:
#            self.__graniteMessageIterator.Timeout = 100
#            i+=1
#            message = self.__graniteMessageIterator.GetNextPhonet()
            
#            if not message:            
#                # This is needed to prevent error message when closing the connection
#                timeSpent = time.clock() - startTime
#                if timeSpent < timeout:
#                    continue
                    
#                return None, None
#            else:
#                # convert message to Granite message (list of ints)
#                graniteMessage = [int(x) for x in message.ToArray()]
#                count = message.Count
                
#                message.Dispose()
#                return count, graniteMessage

#    def displayUpdateMessageListenerDestroy(self):
#        """Destroy Granite message iterators."""
#        if self.__graniteMessageIterator:
#            try:
#                self.__graniteMessageIterator.MoveEnd() # maybe this is not needed at all?               
#            except StandardError:
#                # StandardError is thrown is binary log (connection has already been closed)
#                pass
                
#            self.__graniteMessageIterator.Dispose()
#            self.__graniteMessageIterator = None
                     
#    def setUIChanged(self, box):
#        """ This method sets scripting module's uiChanged flag to True to indicate that
#            new UI dump should be requested from server.

#        """
#        debug.out("setUIChanged: %s"% box)
#        if "," in box:
#            boxX, boxY, boxW, boxH = [int(c) for c in box.split(",")]
#            # Filter breathing line animation away
#            if not (boxY>=310 and boxH==scripting.SCREEN_HEIGHT and boxX==0 and boxW==scripting.SCREEN_WIDTH):
#                scripting.uiChanged = True
#        else:
#            scripting.uiChanged = True
