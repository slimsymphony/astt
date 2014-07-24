""" Granite internal

    Granite Framework <-> Granite Server traffic module.

    This module implements Python interface for Granite Framework <-> Granite
    ISA Server message traffic.

    Information about the PhoNet PN_PRIVATE interface and PhoNet Name
    Service can be found from here:
    http://cowww02.europe.nokia.com/projects/isacoresw/cl/pn_private.htm
"""
# ============================================================================
#   MODULE CODE
# ----------------------------------------------------------------------------

# Python library module imports
from struct import *
import time, os, types, functools, sys, inspect, clr

# Granite module imports
import core
from core import teststep_analyzer
from core.testcase_exceptions import TestException, StopTestException
from interfaces import wbxml_encoder, wbxml_parser
from interfaces.isimessage import ISIMessageException
from srv_granite_isimessage import *
from interfaces.c_srv.srv_name import queryName
from utils.nodeutils import NodeUtils
from utils import include
from interfaces.connection_interface import GraniteConnectionInterface

reset_inc = include.Include('kernel_hal_chipset_api.h')


# ----------------------------------------------------------------------------
class GraniteServerInterface(GraniteConnectionInterface):

    def __init__(self):
        if type(self) == GraniteServerInterface:
            raise Exception("<GraniteServerInterface> must be subclassed.")

        # Local data structures
        GraniteConnectionInterface.__init__(self)
        self.objectId = None

        self.server_version = {}

    def testReq(self, testStepReporting = True):
        """Main function for sending and receiving ISI-messages between
           Granite Framework and Granite Server.

           Analyzes response data with UITestStepAnalyzer.

            Parameters

            testStepReporting   add test step and result to report
                                (default = True)
        """
        if self.isFollower():
            debug.vrb('testReq to grn_server: Follower mode, return')
            return

        assert type(self.objectId) == types.IntType, \
            "Granite server's object id is not known!"
    
        startTime = time.time()
            
        analyze, result, cause = None, None, None

        dataList = wbxml_encoder.parse(self)
    
        dataList = self.__checkMessageLength(dataList)
    
        self.addId(self.teststep)

        clonedTestStep = self.teststep.clone()

        if testStepReporting:
            self.result.addTestStep(clonedTestStep)

        testReqSends = 5  # number of try times in test request message resending

        # force server to idle state before test request
        self.clearGraniteServer()

        # send test request with __sendSplitMessage    
        response = self.__sendSplitMessage(dataList)
    
        wbxmlData = []
        continueFlag, msg_id, msg_data = None, None, None
        tryCounter = 0

        while 1:
            try:
                tryCounter += 1
                # Wait for a response until test step's timeout
                grnRespMessage = grnISIResp(self, isi_message = response)

                msg_id = grnRespMessage.msg_id
                msg_data = grnRespMessage.msg_data

                if msg_id == inc.GRN_TEST_RESP:
                    continueFlag = grnRespMessage.continue_flag
                    result = grnRespMessage.response
                    cause = grnRespMessage.cause

            except TestException, err:
                # send wait message to GUI, because this can take a while
                self.sendWaitMessageToGraniteGUI(\
                    int(long(self.teststep['timeout'])) / 1000 + 60,
                    'Test response receiving failed! Trying again...')
                debug.vrb('Receiving failed: %s' % str(err))
                debug.vrb('Sending GRN_STATUS_REQ...')
                statusRequest = GRNStatusReq(recv_obj = self.objectId)
                grnRespMessage = grnISIResp(self, isi_message = \
                        self.transferMsg(statusRequest))

                if grnRespMessage.msg_id == inc.GRN_TEST_RESP:
                    debug.out('Late GRN_TEST_RESP arrived. '
                                'Now waiting for the GRN_STATUS_RESP')
                    temp = self.recvMsg(long(self.teststep['timeout']))
                    debug.vrb('GRN_STATUS_RESP: %s' % str(temp))

                if grnRespMessage.msg_id == inc.GRN_STATUS_RESP:
                    debug.vrb("Warning: Teststep timeout was not enough. "
                                "Granite server's status: %s" % \
                                inc.lookup('GRN_SERVER_STATE_', \
                                grnRespMessage.state, \
                                default = ['GRN_SERVER_STATE_unknown']) \
                                [0].split('STATE_')[1])

                    # Get details of last runned tag
                    lastTagElement = \
                    self.teststep.lookup('id',
                        str(grnRespMessage.latest_known_id), 1)

                    testReqSends -= 1
                    if testReqSends and \
                        self.getConnectionBusName() in ['FIDO', 'MUSTI', 'MUSTI_USB']:
                        msg_id, result, cause = \
                            self.__handleGraniteTestReqMessagingError(\
                                1, dataList, lastTagElement,
                                grnRespMessage.latest_known_id)
                    else:
                        # resolve occurred error and print proper error message
                        self.__resolveError(grnRespMessage.state,
                                        lastTagElement,
                                        grnRespMessage.latest_known_id)

                # if server gives an illegal response, break from the loop
                if grnRespMessage.msg_id != inc.GRN_TEST_RESP and \
                    grnRespMessage.msg_id != inc.GRN_STATUS_RESP:
                    debug.err('Fatal error: Illegal response received: %s' \
                                % str(grnRespMessage))
                    if tryCounter == 5:
                        raise TestException('Phone UI freeze: Receiving test response data ' \
                                            'failed!', self)
                    else:
                        debug.out('Trying to receive test response...')

            # Check that received message is the right one
            if msg_id == inc.GRN_TEST_RESP:
                # write performance test data
                #if testStepReporting:
                #    phone.performanceTest.endTestStep()

                # Check that message is either ok or failed.
                # If it's failed, error message is checked.
                # If some other error than the one on screen occurs,
                # break away from the eternity loop.
                if result == 0 and cause == inc.GRN_CAUSE_NOTEXPECTED_RESULT \
                    or result == 1:# Wbxml-data come only these cases.
                    # check if it's necessary to send GRN_RESULT_REQ messages
                    # --> synchronized handling of test responses
                    if grnRespMessage.msg_id == inc.GRN_STATUS_RESP or \
                        grnRespMessage.number_of_sub_blocks == 0:
                        wbxmlData, msg_id, msg_data = \
                            self.__sendResultReqMessages()
                        # put 0 to continueFlag --> data is ready to be analyzed
                        continueFlag = 0
                    if (getattr(grnRespMessage, 'sub_block', None) and \
                        grnRespMessage.sub_block == inc.GRN_WBXML_RESP_INFO) or \
                        msg_id == inc.GRN_RESULT_RESP: # "new format" included
                        # send GRNClearReq to server so that it goes back
                        # to idle
                        #self.clearGraniteServer()
                        # Collect wbxml-data to wbxmlData variable.
                        # This is not done if data has already been collected
                        # in synchronized handling of test responses
                        if msg_id != inc.GRN_RESULT_RESP:
                            wbxmlData.extend(grnRespMessage.wbxml_data)
                        # This is a check flag, which tells if Granite server's
                        # response is splitted or not.
                        # If continueFlag is on, jump to the beginning of loop.
                        if continueFlag == 0:
                            # Call for wbxml-parser, which returns xml in
                            # readable form
                            respTeststep = wbxml_parser.parseWbxml(wbxmlData, self.getName())
                            del wbxmlData
                                                        
                            analyze = \
                                teststep_analyzer.UITestStepAnalyzer()

                            #Set current ui state
                            respXml = respTeststep.find('//xml')
                            spXmlNode = None

                            if respXml: 
                                # save received xml for debugging purposes
                                self.__saveResponseXml(respXml, self.getName())

                                # update UI state if we got new widget dump
                                if respXml.find('container') or respXml.find('root-container'):
                                    self.uiState.setNewState(respXml)
                                    spXmlNode = self.uiState.currentState

                                    # save updated full xml for debugging purposes
                                    self.__saveResponseXml(respXml, self.getName(), 'full')

                            # Call for analyzer class.
                            # NOTICE! The document instance created in
                            # uitestcase will be sent to analyzer.
                            # NOTE: Use cloned test step, because setNewState will wipe out original one
                            analyze.parseResp(respTeststep, clonedTestStep, spXmlNode)
                           
                            # add summary to test case's result when
                            # testStepReporting is True or test step fails
                            if testStepReporting or result == 0:
                                #if testStepReporting:
                                #    analyze.parsedSummary['duration'] = \
                                #        str(testcase.performanceTest.getTestStepDuration())
                                #else:
                                #    # add test step to result when test case
                                #    # fails and testStepReporting is False
                                #    testcase.result.addTestStep(clonedTestStep)

                                # calculate test step duration (milliseconds)
                                analyze.parsedSummary['duration'] = "%.0f" % (1000 * (time.time() - startTime))

                                self.result.addTestStep(analyze.parsedSummary.clone())
                            break
                    else:
                        debug.vrb('Response msg_id: %s' % str(msg_id))

                        if getattr(grnRespMessage, 'sub_block', None):
                            debug.vrb('Response sub_block: %s' % \
                                str(grnRespMessage.sub_block))

                        raise TestException('Phone UI freeze: Receiving test response data ' \
                                            'failed!', self)
                else:
                    break

        # Search all succeeded displays and return them if there's no errors.
        displaysAndCaptures = {}
        if analyze:
            displaysAndCaptures = analyze.passedDisplaysAndCaptures()
            del analyze

        if result != None and cause != None:
            # check error reported by Granite server
            if result == 0:
                errorString = ''
            
                if cause == inc.GRN_CAUSE_NOTEXPECTED_RESULT:
                    errorString = 'Not expected result'
                elif cause == inc.GRN_CAUSE_STATE_INACTIVE:
                    # FIXME: Remove test case failing with this cause
                    #        when x-file related failing is working                
                    errorString = 'Remote phone reset detected'
                elif cause == inc.GRN_CAUSE_MEMORY_FULL:
                    errorString = 'Phone memory full'
                elif cause in [inc.GRN_CAUSE_STATE_RUNNING,
                               inc.GRN_CAUSE_STATE_REPORTING]:
                    if self.isPhoneUIFrozen():
                        errorString = 'Phone UI freeze detected'
                else:
                    # get failure cause
                    failureCause = inc.lookup('GRN_CAUSE_',
                        cause)[0].split('CAUSE_')[1].replace('_',' ')
                    errorString = 'Granite tool error: Granite server was in invalid state: %s' % failureCause

                # put server back to idle state
                self.clearGraniteServer()

                # fail test case with correct error string
                if errorString:
                    self.fail(errorString)
                
        return displaysAndCaptures

    # ----------------------------------------------------------------------------
    def getObjectId(self, forced = False):
        """Ask Granite server's 10 bit object id from the PhoNet's Name Service.

           Raises TestException if Granite server is not found from the phone.

           This must be done once before sending any messages to the Granite server.
           As the value given in the pn_obj_auto.h depends on the build, we must
           ask the real value from the PhoNet's Name Service.

           10 bit object id is calculated this way:

               device id   object id
               ---------   ---------
               DDDDDD OO   OOOOOOOO
                       |
                      +- two LSBs of device id become two MSBs of the object id

           FIXME: What about moving this into its own SRV PTC?
           forced = forced object id checking
        """
        # if granite_object_id has already been queried, just return it
        if self.objectId and not forced:
            return self.objectId

        # check which include file is in use and query server's object id
        name_list = queryName(self, inc.GRANITE, 0xFFFFFFFFL)

        if not name_list:
            raise TestException('Granite server was NOT FOUND from the phone!', self)

        grn_name, dev_id, object_id, rec_flags = name_list[0]

        # check which include file is in use and verify that received object id
        # matches with the one in the header file
        errorString = "Fatal error occurred: Granite server's object id doesn't " \
                      "match with the one in the header file!"

        assert grn_name == inc.GRANITE, errorString

        # check whether product has changed
        if self.objectId != None and self.objectId != object_id:
            # clear dictionary so that product details will be read again
            self.productDetails = {}

        # put value to global variable
        self.objectId = object_id
        
        return object_id

    # ----------------------------------------------------------------------------
    def getStatus(self, returnOldState = False):
        """Get Granite server's status and return server's state.

           returnOldState = return also server's old state if possible
        """
        assert type(self.objectId) == types.IntType, \
            "Granite server's object id is not known!"
    
        debug.out('Checking Granite server status...')
        statusRequest = GRNStatusReq(recv_obj = self.objectId)

        try:
            response = GRNStatusResp(isi_message = \
                        self.transferMsg(statusRequest))
            state = inc.lookup('GRN_SERVER_STATE_',
                        response.state, \
                        default = ['GRN_SERVER_STATE_unknown']) \
                        [0].split('STATE_')[1].lower()

            # FIXME: Remove this when GRN_SERVER_STATE_INFO and GRN_SERVER_STATE_REPORTING no longer
            #        collide in granite_p_isi.h
            if state == 'info':
                state = 'reporting'
        
            debug.out('Status: %s' % state)

            self.server_version = {"zzz":response.version_zzz,
                                   "yyy":response.version_yyy,
                                   "xxx":response.version_xxx}

            # start display update ntf listener if server is new enough
            if self.getName() == "Main" and self.server_version['yyy'] >= 5:
                self.startNtfListener()

            if getattr(response, 'err_cause', None) != None:
                # prompt server reported error if necessary
                if response.err_cause != inc.GRN_CAUSE_NONE:
                    debug.err('Granite server reported an error!')
                    debug.err('Transaction ID of the last received test or ' \
                              'result request: %s' % response.last_tid)
                    debug.err('Cause of error: %s' % response.err_cause)
                    debug.err('State of the server when error occurred: %s' % \
                              response.err_state)
                    debug.err('Transaction ID of the last received test or ' \
                              'result request when the error occurred: %s' % \
                              response.err_tid)

            # return also old_state if wanted
            if returnOldState and getattr(response, 'old_state', None) != None:
                try:
                    oldState = inc.lookup('GRN_SERVER_STATE_',
                                    response.old_state)[0].split('STATE_')[1].lower()
                                
                    # FIXME: Remove this when GRN_SERVER_STATE_INFO and GRN_SERVER_STATE_REPORTING no longer
                    #        collide in granite_p_isi.h                                
                    if oldState == 'info':
                        oldState = 'reporting'                
                                
                except IndexError:
                    oldState = None

                if not oldState:
                    oldState = 'unknown (%s)' % str(response.old_state)

                debug.vrb('Old state: %s' % oldState)
                return (state, oldState)
            else:
                return state
        except ISIMessageException, err:
            debug.out("Invalid message received: %s" % str(err))
        except TestException, err:
            debug.out("Getting Granite server's status failed: %s" % str(err))

    # ----------------------------------------------------------------------------
    def clearGraniteServer(self):
        """Send GRNClearReq messages to Granite Server. It puts server to idle status."""   
        assert type(self.objectId) == types.IntType, \
            "Granite server's object id is not known!"
    
        response = None

        clearRequest = GRNClearReq(recv_obj = self.objectId)
    
        self.sendWaitMessageToGraniteGUI(30,
            'Clearing Granite server')

        for i in range(10):
            try:
                response = self.transferMsg(\
                    clearRequest, 10000, expectedResp = inc.GRN_CLEAR_RESP)
            except ISIMessageException, err:
                debug.err('Something wrong with the response: %s ' \
                          % str(err))
                debug.vrb('Response: %s' % str(response))
                self.__handleGraniteServerClearingError(\
                    'clearGraniteServer: GRNClearResp was not received correctly!')
                time.sleep(1)
            except TestException, err:
                debug.out('Clearing Granite server failed: %s' % str(err))
                time.sleep(1)
            except Exception, err:
                debug.err('Fatal function error in clearGraniteServer: %s' % str(err))
                time.sleep(1)
            else:
                break

    # ----------------------------------------------------------------------------
    def termGraniteServer(self):
        """Send GRNTermReq message to Granite Server. It puts server to inactive
           status.
        """
        assert type(self.objectId) == types.IntType, \
            "Granite server's object id is not known!"
    
        response = None

        termRequest = GRNTermReq(recv_obj = self.objectId)
    
        self.sendWaitMessageToGraniteGUI(30,
                                             'Terminating Granite server')

        for i in range(10):
            try:
                response = self.transferMsg(\
                    termRequest, 10000, expectedResp = inc.GRN_TERM_RESP)
            except ISIMessageException, err:
                debug.err('Something wrong with the response: %s ' \
                          % str(err))
                debug.vrb('Response: %s' % str(response))
            except TestException, err:
                debug.out('Deactivating Granite server failed: %s' % str(err))
            except Exception, err:
                debug.err('GRNTermResp could not be received: %s. Granite server was '
                          'left to idle state.' % str(err))
            else:
                break    
    
    # ----------------------------------------------------------------------------
    def clearTestCase(self):
        """Send GRNClearTestCaseReq messages to Granite Server. It clears server's
           data structures after test case and puts server to idle state.
        """
        assert type(self.objectId) == types.IntType, \
            "Granite server's object id is not known!"
    
        response = None

        clearTestCaseRequest = GRNClearTestCaseReq(recv_obj = self.objectId)
    
        self.sendWaitMessageToGraniteGUI(30,
            'Clearing test case data structures in Granite server')
        
        for i in range(10):
            try:
                response = self.transferMsg(\
                    clearTestCaseRequest, 10000, expectedResp = inc.GRN_CLEAR_TESTCASE_RESP)
            except ISIMessageException, err:
                debug.err('Something wrong with the response: %s ' \
                          % str(err))
                debug.vrb('Response: %s' % str(response))
                self.__handleGraniteServerClearingError(\
                    'clearTestCase: GRNClearTestCaseResp was not received ' \
                    'correctly!')
            except TestException, err:
                debug.out('Clearing test case failed: %s' % str(err))
            except Exception, err:
                debug.err('Fatal function error in clearTestCase: %s' % str(err))
                time.sleep(1)
            else:
                break

    ## ----------------------------------------------------------------------------
    def __checkMessageLength(self, dataList):
        """Check that message is not too big to be sent."""
        length = 0
        for i in dataList:
            length += len(i)

        stepSize = int(core.FW_conf['encoder_isi_length']) - 200
    
        # set special test step size when using Fido/Musti connection
        if self.getConnectionBusName() in ['FIDO', 'MUSTI', 'MUSTI_USB']:
            stepSize = 2048

        if length > stepSize:
            # if message length exceed maximum value, clip message accordingly
            return self.__clipDataList(dataList, (length / stepSize) + 1)
        else:
            return dataList

    # ----------------------------------------------------------------------------
    def __sendSplitMessage(self, dataList, calledFromHandleGraniteTestReqMessagingError = False):
        """Send GRN_TEST_REQ messages.

           Several messages will be sent if data doesn't fit to one message.

           Returns response in byte list
        """
        index = 0

        # send multiple test request messages if dataList have more than one item
        while index < len(dataList) - 1:
            tcRequest = GRNTestReq(wbxml_data = dataList[index],
                                   continue_flag = 1,
                                   recv_obj = self.objectId)

            index += 1

            try:
                # FIXME: remove asyncSend and dummy wait when TEST_NTF is taken back into use                        
                self.sendMsg(tcRequest, asyncSend = True)                        
            except TestException, err:
                if calledFromHandleGraniteTestReqMessagingError or \
                   not self.getConnectionBusName() in ['FIDO', 'MUSTI', 'MUSTI_USB']:
                    raise
                else:
                    response = self.__handleGraniteTestReqMessagingError(3, tcRequest)

            #if response and response.msg_id != inc.GRN_TEST_NTF or \
            #   getattr(response, 'notify', None) != inc.GRN_NTF_PARSE_CONTINUE:
            #    debug.err('Illegal response to GRN_TEST_REQ: %s' % str(response))
            #   testcase.warn('Illegal response to GRN_TEST_REQ.')
            #   errorFlag = 1
            #    break
        
        # send test request in one message or the end part of the message
        tcRequest = GRNTestReq(wbxml_data = dataList[-1],
                                continue_flag = 0,
                                recv_obj = self.objectId)

        try:
            response = self.transferMsg(tcRequest,
                long(self.teststep['timeout']),
                expectedResp = inc.GRN_TEST_RESP)
        except TestException:
            if calledFromHandleGraniteTestReqMessagingError or \
                not self.getConnectionBusName() in ['FIDO', 'MUSTI', 'MUSTI_USB']:
                raise
            else:
                response = self.__handleGraniteTestReqMessagingError(2, tcRequest)

        return response

    # ----------------------------------------------------------------------------
    def __sendResultReqMessages(self):
        """Send GRN_RESULT_REQ messages and receive GRN_RESULT_RESP messages.

           This function implements synchronized handling of test responses.
        """
        sendCounter, loopCounter, sendFlag =  0, 0, 1
        wbxmlData, msg_id, msg_data, resultResponse = [], None, None, None

        while 1:

            loopCounter += 1
            sendCounter = 0

            debug.vrb('Main loop counter = %s' % str(loopCounter))
            debug.vrb('Length of wbxmlData = %s' % str(len(wbxmlData)))

            while sendCounter < 10:

                try:
                    sendCounter += 1
                    debug.vrb('sendCounter = %s' % str(sendCounter))
                    debug.vrb('sendFlag = %s' % str(sendFlag))

                    if sendFlag:
                        resultRequest = GRNResultReq(index = len(wbxmlData),
                                                     recv_obj = self.objectId)
                        self.sendMsg(resultRequest)

                    debug.vrb('resultRequest.data_index_1 = %s' \
                              % str(resultRequest.data_index_1))
                    debug.vrb('resultRequest.data_index_2 = %s' \
                              % str(resultRequest.data_index_2))
                    debug.vrb('resultRequest.data_index_3 = %s' \
                              % str(resultRequest.data_index_3))
                    debug.vrb('resultRequest.data_index_4 = %s' \
                              % str(resultRequest.data_index_4))

                    try:
                        # 5 second default timeout in recvMsg
                        resultResponse = GRNResultResp(isi_message = \
                                            self.recvMsg(long(self.teststep['timeout'])))

                        debug.vrb('resultResponse.data_index_1 = %s' \
                                  % str(resultResponse.data_index_1))
                        debug.vrb('resultResponse.data_index_2 = %s' \
                                  % str(resultResponse.data_index_2))
                        debug.vrb('resultResponse.data_index_3 = %s' \
                                  % str(resultResponse.data_index_3))
                        debug.vrb('resultResponse.data_index_4 = %s' \
                                  % str(resultResponse.data_index_4))

                        msg_id = resultResponse.msg_id
                        msg_data = resultResponse.wbxml_data

                        # msg_id is correct, but index is wrong
                        # --> received data was wrong
                        if (msg_id == inc.GRN_RESULT_RESP and \
                            (resultRequest.data_index_1 != resultResponse.data_index_1 or \
                            resultRequest.data_index_2 != resultResponse.data_index_2 or \
                            resultRequest.data_index_3 != resultResponse.data_index_3 or \
                            resultRequest.data_index_4 != resultResponse.data_index_4)):
                            debug.vrb('Received GRN_RESULT_RESP response, '
                                      'but the data was wrong. Trying again...')
                            # don't send a request next time,
                            # just wait for the response
                            sendFlag = 0
                        # message receiving went ok and we can now exit the loop
                        else:
                            sendFlag = 1 # send a request next time
                            # collect wbxml to wbxmlData variable
                            wbxmlData.extend(msg_data)
                            # break away from the loop
                            break

                    except ISIMessageException, (err):
                        debug.vrb("GRN_RESULT_RESP response wasn't received "
                                  "correctly from Granite server: %s. Trying "
                                  "again..." % str(err))
                        debug.vrb('Response: %s' % str(resultResponse))
                        # msg_id is wrong or msg_data is empty
                        if msg_id != inc.GRN_RESULT_RESP or \
                           (msg_id == inc.GRN_RESULT_RESP and \
                           not getattr(resultResponse, 'wbxml_data', None)):
                            # don't send a request next time,
                            # just wait for the response
                            sendFlag = 0
                        # something wrong with msg_data (message length was wrong)
                        else:
                            sendFlag = 1 # send a request next time
                except TestException,(e):
                    # send wait message to GUI, because this can take a while
                    self.sendWaitMessageToGraniteGUI(60,
                        'Test result response receiving failed! Trying again...')

                    # send GRN_STATUS_REQ in the last time only
                    if sendCounter == 10:
                        try:
                            debug.out('Sending GRN_STATUS_REQ...')
                            statusRequest = GRNStatusReq(recv_obj = self.objectId)
                            grnRespMessage = \
                                grnISIResp(self, isi_message = self.transferMsg(statusRequest))

                            debug.vrb(str(grnRespMessage))

                            if grnRespMessage.msg_id == inc.GRN_RESULT_RESP:
                                debug.out('Late GRN_RESULT_RESP arrived. '
                                          'Now waiting for the GRN_STATUS_RESP...')
                                temp = self.recvMsg(\
                                    long(self.teststep['timeout']) + 10000)
                                debug.vrb('GRN_STATUS_RESP: %s' % str(temp))

                            if grnRespMessage.msg_id == inc.GRN_STATUS_RESP:
                                debug.vrb("Warning: Teststep timeout was not "
                                          "enough. Granite server's status: %s" % \
                                          inc.lookup('GRN_SERVER_STATE_', \
                                          grnRespMessage.state, \
                                          default = ['GRN_SERVER_STATE_unknown']) \
                                          [0].split('STATE_')[1])

                                # Get details of last runned tag
                                lastTagElement = \
                                self.teststep.lookup('id',
                                        str(grnRespMessage.latest_known_id), 1)
                                # resolve occurred error and print proper
                                # error message
                                self.__resolveError(grnRespMessage.state,
                                               lastTagElement,
                                               grnRespMessage.latest_known_id)

                            # report if server gives an illegal response
                            if grnRespMessage.msg_id != inc.GRN_RESULT_RESP and \
                               grnRespMessage.msg_id != inc.GRN_STATUS_RESP:
                                debug.err('Fatal error: Illegal response from '
                                          'Granite server, msg_id: %s' % str(msg_id))
                        except TestException,(e):
                            debug.out('Sending GRN_STATUS_REQ failed: %s' % str(e))
                            wbxmlData, msg_id, msg_data = None, None, None
                    else:
                        debug.vrb('Receiving GRN_RESULT_RESP response failed. '
                                  'Trying again...')
                        time.sleep(2) # wait for a while before sending a new request
                        sendFlag = 1 # send a request next time

            if sendCounter < 10:
                debug.vrb('GRN_OPTION_END = %s' % str(resultResponse.end_of_data))
                # check if data block was the last
                # break away from the loop if it was
                if resultResponse.end_of_data == inc.GRN_OPTION_END:
                    break
                else:
                    debug.vrb("Received data block wasn't the last --> continue "
                              "asking for data blocks ")
            # break away from loop also if sendCounter == 10
            elif sendCounter == 10:
                debug.vrb("Granite framework was unable to get wanted data from "\
                          "Granite server.")
                wbxmlData, msg_id, msg_data = None, None, None
                break

        return wbxmlData, msg_id, msg_data

    # ----------------------------------------------------------------------------
    def __resolveError(self, state, lastTagElement, lastTag):
        """Resolves occured error and prints proper error message."""
        if core.FW_conf['should_stop']:
            return

        if isinstance(lastTagElement, NodeUtils):
            lastTagName = lastTagElement.getName()
            figuredDom = teststep_analyzer.evaluateTestStep(\
                self.teststep.clone(), lastTag)
            tagInfo = "Last running tag was: id: " + str(lastTag) + \
                    " name: " + lastTagName + ". "
        else:
            tagInfo = "Can't resolve which was the last running tag. "

        if isinstance(state, basestring):
            stateName = state.upper()
        else:
            stateName = inc.lookup('GRN_SERVER_STATE_', state, default = \
                ['GRN_SERVER_STATE_unknown'])[0].split('STATE_')[1]

        # clear Granite server and report error
        self.clearGraniteServer()

        errorReason = 'Message traffic between Granite Framework and Server was interrupted. ' \
                      'This is probably a result of a phone reset during test execution.'

        if stateName == 'RUNNING':
            if self.isPhoneUIFrozen():
                errorReason = 'Phone UI freeze detected'
            else:
                errorReason = 'Granite Server was left in running state after test step. ' \
                              'This is probably a result of UI task resource exhaustion.'
        elif stateName == 'INACTIVE':
            debug.vrb('Granite server inactive. Call checkPhoneStatus to detect ' \
                      'phone reset.')
            if not self.checkPhoneStatus():
                raise TestException(errorReason, self)
        elif stateName == 'IDLE':
            debug.out('Granite server is in idle state, raise exception') 
            raise TestException(errorReason, self)
        else:
            errorReason = "Granite server's status is %s. Unable to continue." % stateName

        self.resetPhone(errorReason)

    # ----------------------------------------------------------------------------
    def __handleGraniteServerClearingError(self, exception):
        """Check Granite server's status and raise
           TestException if necessary.

           exception = exception string for TestException
        """
        debug.vrb('Sending status request...')
        status = self.getStatus()

        if status:
            debug.vrb('Granite server status: %s' % status)
        else:
            debug.out("Getting Granite server's status failed --> trying again...")
            # wait for a while and ask status again
            time.sleep(15)
            status = self.getStatus()

        if status == 'starting':
            debug.vrb('Granite server still starting. Waiting for a while...')
            time.sleep(15)
        elif status == 'inactive':
            debug.vrb('Granite server inactive. Call checkPhoneStatus to detect ' \
                      'phone reset.')
            self.checkPhoneStatus()
        elif status == None:
            debug.err("Unable to get Granite server's status due to a communication error")
            raise TestException(exception, self)

    # ----------------------------------------------------------------------------
    def __handleGraniteTestReqMessagingError(self, callLocation, reqMessage,
                                          lastTagElement = None, lastTag = None):
        """Will be called when problems in sending GRN_TEST_REQ or receiving
           GRN_TEST_RESP. Checks Granite server's status and acts according to that.

           callLocation = 1 = (from testReq)
                          2 = (from _sendSplitMessage with whole wbxml data)
                          3 = (from _sendSplitMessage with unfinished wbxml data)
           reqMessage = request message to be sent
           lastTagElement = last tag element from the test case
           lastTag = last tag id from the test case
        """
        response, status, msg_id  = None, None, None
        result, cause = None, None

        messageDivider = 1

        # send wait message to GUI, because this will take a while
        # convert timeout from milliseconds to seconds
        self.sendWaitMessageToGraniteGUI(\
            2 * int(long(self.teststep['timeout'])) / 1000,
            'Handling Granite test request messaging error')
    
        if type(reqMessage) == types.ListType:
            origReqMessageData = reqMessage[:]
        else:
            origReqMessageData = reqMessage.wbxml_data[:]

        for loopCounter in range(5):
            # make a copy from req message which we can then clip
            reqMessageData = origReqMessageData[:]
        
            debug.vrb('Sending status request...')

            # get Granite server's status
            for statusCounter in range(5):
                status = self.getStatus()

                if status:
                    break
                else:
                    if statusCounter < 4:
                        debug.out('Getting Granite server status failed. Trying '
                                  'again...')
                        time.sleep(2)

            debug.vrb('Granite server status: %s' % status)

            if not status:
                self.resetPhone(\
                    "Getting Granite server's status failed! " \
                    "This is probably a result of UI task resource exhaustion.")

            try:
                if status in ['idle', 'parsing']:
                    # increase messageDivider
                    messageDivider *= 2

                    if status == 'parsing':
                        debug.vrb('Clearing Granite server and sending message again.')
                        self.clearGraniteServer()
                    else:
                        debug.vrb('Sending message again...')

                    # add warning to test report
                    #testcase.warn('Granite Test request was resended due to '
                    #              'messaging problems.')

                    if callLocation == 1:
                        self.__sendSplitMessage(self.__clipDataList(reqMessage, messageDivider), True)
                    else:
                        dataList = self.__clipDataList(reqMessageData,
                                                  messageDivider)

                        for data in dataList:
                            if callLocation == 2 and \
                               dataList.index(data) == dataList.index(dataList[-1]):
                                tcRequest = GRNTestReq(wbxml_data = data,
                                                       continue_flag = 0,
                                                       recv_obj = self.objectId)
                            else:
                                tcRequest = GRNTestReq(wbxml_data = data,
                                                       continue_flag = 1,
                                                       recv_obj = self.objectId)

                            if tcRequest.continue_flag == 1:
                                # FIXME: remove asyncSend and dummy wait when TEST_NTF is taken back into use                            
                                self.sendMsg(tcRequest, asyncSend = True)
                                time.sleep(1)
                            else:
                                response = self.transferMsg(\
                                        tcRequest, expectedResp = inc.GRN_TEST_RESP)
                elif status == 'reporting':
                    debug.vrb('Proceed to sending result req messages.')
                    if response:
                        msg_id = response.msg_id
                        result = response.response
                        cause = response.cause
                    else:
                        # no response received, so these values are hard coded
                        msg_id = inc.GRN_TEST_RESP
                        result = 0
                        cause = inc.GRN_CAUSE_NOTEXPECTED_RESULT
                break

            except TestException, err:
                debug.vrb('Error in handling messaging error: %s' % str(err))
                if loopCounter < 4:
                    time.sleep(2)
                else:
                    raise TestException('Phone UI freeze: Unable to send test request to Granite '
                                        'server: %s' % str(err), self)

        # handle errors in other states with __resolveError
        if not status in ['idle', 'reporting', 'parsing']:
            return self.__resolveError(status, lastTagElement, lastTag)
        else:
            if callLocation == 1:
                return msg_id, result, cause
            else:
                return response

    # ----------------------------------------------------------------------------
    def __clipDataList(self, dataList, messageDivider):
        """Clips wbxml data list to pieces.

            Data list length is divided with messageDivider. dataList may contain
            several data lists.
        """
        clippedDataList, tempDataList = [], []

        # if several lists in dataList, combine them
        if type(dataList[0]) == types.ListType:
            # define clip length from the first data list
            clipLength = len(dataList[0]) / messageDivider

            dataList2 = []

            for dl in dataList:
                dataList2.extend(dl)

            dataList = dataList2
        else:
            # define clip length
            clipLength = len(dataList) / messageDivider

        # minimum clip length is 20
        if clipLength < 20:
            clipLength = 20

        # split message to clipLength byte lists
        while len(dataList) > 0:
            tempDataList = dataList[:clipLength]
            dataList = dataList[clipLength:]

            # check that the last list is not too short
            if len(dataList) < 20:
                # append it to the current
                tempDataList.extend(dataList)
                dataList = []

            clippedDataList.append(tempDataList)

        return clippedDataList

# ----------------------------------------------------------------------------
    def __saveResponseXml(self, respXml, prefix, suffix = ''):
        """Saves SP XML response to file.
    
            Parameters

            respXml     response xml (NodeUtils instance)
            suffix      suffix for file
        """                        
        appNodeList = respXml.findall('//application') 
        applicationNode = len(appNodeList) and appNodeList[-1] or None

        if applicationNode == None:
            # if we got response to menu XML, save it as menu.xml
            if respXml.find('mainmenu'):
                applicationName = 'menu'
            elif respXml.find('images'):
                applicationName = 'images'
            elif respXml.find('texts'):
                applicationName = 'texts'
            else:                
                applicationName = "unknown"
        else:
            applicationName = applicationNode.getAttribute("name")
                
        if core.FW_conf['test_result_dir'] and os.path.isdir(core.FW_conf['test_result_dir']):
            if not os.path.exists(os.path.join(core.FW_conf["test_result_dir"],'application_xml')):
                os.makedirs(os.path.join(core.FW_conf["test_result_dir"],'application_xml'))
                
            respXml.save(os.path.join(core.FW_conf["test_result_dir"],'application_xml',"%s_%s%s.xml" % (prefix,applicationName, suffix and '_%s' % suffix or '')))

# ----------------------------------------------------------------------------
    def provisioningDeleteReq(self, sim_id, delete_all, configuration_context):
        """Sends GRNProvisioningDeleteReq to Granite server to delete provisioning
           settings data from given configuration context, with given SIM

            Parameters                      Data type
            - sim_id                        int
            - delete_all                    bool
            - configuration_context         int (do not care if delete_all is set to True)

            Returns                         Data type
            - 'ok'/'fail'/'not_supported'   str

        """
        assert type(self.objectId) == types.IntType, \
            "Granite server's object id is not known!"

        if not isinstance(sim_id, int):
            raise TestException('Unsupported object type passed as sim_id; expecting int', self)
        if not isinstance(delete_all, bool):
            raise TestException('Unsupported object type passed as delete_all; expecting bool', self)
        if not isinstance(configuration_context, int):
            raise TestException('Unsupported object type passed as configuration_context; expecting int', self)
    
        if sim_id < 1 or sim_id > 2 :
            raise TestException('sim_id value must be between 1 and 2', self)

        req = GRNProvisioningDeleteReq(0, int(delete_all), configuration_context, sim_id,recv_obj = self.objectId)
        grnRespMessage = grnISIResp(self, isi_message = self.transferMsg(req))

        if grnRespMessage.response == 0:
            return 'ok'
        elif grnRespMessage.response == 1:
            return 'fail'
        else:
            return 'not_supported'

    # ----------------------------------------------------------------------------
    def provisioningSelectReq(self, sim_id, configuration_context):
        """Sends GRNProvisioningSelectReq to Granite server to select provisioning
           settings data from given configuration context, with given SIM

            Parameters                      Data type
            - sim_id                        int
            - configuration_context         int (do not care if delete_all is set to True)

            Returns                         Data type
            - 'ok'/'fail'/'not_supported'   str

        """
        assert type(self.objectId) == types.IntType, \
            "Granite server's object id is not known!"

        if not isinstance(sim_id, int):
            raise TestException('Unsupported object type passed as sim_id; expecting int', self)
        if not isinstance(configuration_context, int):
            raise TestException('Unsupported object type passed as configuration_context; expecting int', self)
    
        if sim_id < 1 or sim_id > 2 :
            raise TestException('sim_id value must be between 1 and 2', self)

        req = GRNProvisioningSelectReq(0, configuration_context, sim_id, recv_obj = self.objectId)
        grnRespMessage = grnISIResp(self, isi_message = self.transferMsg(req))

        if grnRespMessage.response == 0:
            return 'ok'
        elif grnRespMessage.response == 1:
            return 'fail'
        else:
            return 'not_supported'

    # ----------------------------------------------------------------------------
    def provisioningReadReq(self, sim_id, data_type, configuration_context):
        """Sends GRNProvisioningReadReq to Granite server to read provisioning
           settings data from given configuration context, with given SIM

            Parameters                              Data type
            - sim_id                                int
            - data_type                             str ('json'/'xml'/'wbxml')
            - configuration_context                 int (do not care if delete_all is set to True)

            Returns                                  Data type
            - 'ok'/'fail'/'not_supported' and data   tuple (str, list[int])

        """
        assert type(self.objectId) == types.IntType, \
            "Granite server's object id is not known!"

        if isinstance(data_type, str):
            if data_type.lower() == 'json':
                data_type = 0
            elif data_type.lower() == 'xml':
                data_type = 1
            elif data_type.lower() == 'wbxml':
                data_type = 2
            else:
                raise TestException('Unknown data type given: ' + data_type, self)
        elif not isinstance(data_type, int):
            raise TestException('Unsupported object type passed as data_type; expecting str or int', self)

        if data_type < 0 or data_type > 2 :
            raise TestException('data_type value must be between 0 and 2', self)

        if not isinstance(sim_id, int) :
            raise TestException('Unsupported object type passed as sim_id; expecting int', self)

        if not isinstance(configuration_context, int) :
            raise TestException('Unsupported object type passed as configuration_context; expecting int', self)

        if sim_id < 1 or sim_id > 2 :
            raise TestException('sim_id value must be between 1 and 2', self)

        req = GRNProvisioningReadReq(0, configuration_context, sim_id, data_type, recv_obj = self.objectId)
        grnRespMessage = grnISIResp(self, isi_message = self.transferMsg(req))

        if grnRespMessage.response == 0:
            return ('ok', grnRespMessage.data)
        elif grnRespMessage.response == 1:
            return ('fail', None)
        else:
            return ('not_supported', None)

    # ----------------------------------------------------------------------------
    def provisioningWriteReq(self, sim_id, data_type, data):
        """Sends GRNProvisioningWriteReq to Granite server to write provisioning
           settings data to given SIM

            Parameters                              Data type
            - sim_id                                int
            - data_type                             str ('json'/'xml'/'wbxml')
            - data                                  file content

            Returns                                  Data type
            - 'ok'/'fail'/'not_supported' and data   tuple (str, list[int])

        """
        assert type(self.objectId) == types.IntType, \
            "Granite server's object id is not known!"

        if isinstance(data_type, str):
            if data_type.lower() == 'json':
                data_type = 0
            elif data_type.lower() == 'xml':
                data_type = 1
            elif data_type.lower() == 'wbxml':
                data_type = 2
            else:
                raise TestException('Unknown data type given: ' + data_type, self)
        elif not isinstance(data_type, int):
            raise TestException('Unsupported object type passed as data_type; expecting str or int', self)

        if data_type < 0 or data_type > 2 :
            raise TestException('data_type value must be between 0 and 2', self)

        if not isinstance(sim_id, int) :
            raise TestException('Unsupported object type passed as sim_id; expecting int', self)

        if sim_id < 1 or sim_id > 2 :
            raise TestException('sim_id value must be between 1 and 2', self)

        if not isinstance(data, list) :
            raise TestException('Unsupported object type passed as data; expecting list (bytes)', self)

        req = GRNProvisioningWriteReq(sim_id, data_type, 0, data, recv_obj = self.objectId)
        grnRespMessage = grnISIResp(self, isi_message = self.transferMsg(req))

        if grnRespMessage.response == 0:
            return ('ok', grnRespMessage.configuration_context)
        elif grnRespMessage.response == 1:
            return ('fail', 0)
        else:
            return ('not_supported', 0)

    def checkPhoneStatus(self):
        """Check Granite server's status and whether phone have reseted or not.
        
            Returns True if phone reset was detected, otherwise False
        """
        if self.isFollower():
            debug.out('checkPhoneStatus: Follower mode, not checking anything, return')
            return False

        # check connection before further actions
        self.ensureConnection()

        if not core.FW_conf['granite_server_activated']:
            debug.out("checkPhoneStatus: Granite server is not activated, not checking Granite Server's state, return")
            return False

        returnValue = False

        # request Granite Server's state
        serverStatus = None

        for counter in range (5):
            debug.vrb('Granite status request counter: %s' \
                      % str(counter + 1))
            try:
                serverStatus = self.getStatus(returnOldState = True)
                debug.vrb('serverStatus: %s ' % str(serverStatus))
                break
            except TestException, err:
                debug.err('Granite status request failed: %s' \
                          % str(err))

        # put Granite Server to idle state if necessary
        if type(serverStatus) == types.TupleType and serverStatus[0] != 'idle':
            try:
                if serverStatus[0] in ['inactive', 'starting']:
                    errorString = 'Granite Server was not in idle state --> the phone ' \
                                  'had rebooted itself. Current state: %s, ' \
                                  'State when reset occurred: %s' \
                                   % (serverStatus[0], serverStatus[1])
                    debug.out(errorString)

                    returnValue = True
            
                    # FIXME: Remove test case failing with this cause
                    #        when x-file related failing is working
                    raise TestException('Remote phone reset detected', self)
                elif serverStatus[0] == 'running':
                    if self.isPhoneUIFrozen():
                        raise TestException('Phone UI freeze detected', self)
                    else:
                        debug.out("Granite Server was left in running state after test step.")
                else:
                    errorString = 'Granite Server was in %s state when it ' \
                                  'should have been in idle state.' \
                                   % serverStatus[0]
        
                    debug.out(errorString)
            finally:
                # put server back to idle state
                self.clearGraniteServer()

        return returnValue

