"""Connection interface for communicating with reference phone and
   handling exceptions.
"""
# Python library module imports

import clr
clr.AddReference('Nokia.Granite.Connection.ReferencePhone')

from Nokia.Granite.Connection.ReferencePhone import ReferencePhone
import core
from core import debug, FW_conf
from core.testcase_exceptions import TestException, StopTestException, ReferencePhoneException

class GraniteReferencePhoneInterface(object):
    """Granite referencephone interface class."""
    # Uses instance of ConnectionManager. E.g. graniteConnection.ConnectionManager. connectionIdentifier: name or guid
    def __init__(self, connectionManager = None, connectionIdentifier = None):
        """Initialize variables."""
        self.refPhone = None
        if connectionManager is not None and connectionIdentifier is not None:
            try:
                self.refPhone = ReferencePhone(connectionManager, connectionIdentifier)
                self.callId = None
            except Exception, ex:
                raise SystemExit('Unable to create the ReferencePhone object: %s' % ex)

    def createCall(self, phoneNumber):
        try:
            debug.brf('Creating a call with reference phone to number: %s' % phoneNumber)
            if core.FW_conf['connection'].virtualPhone is not None and core.FW_conf['settings'].TestRun.EnableVirtualReferencePhone:
                core.FW_conf['connection'].virtualPhone.createCall(phoneNumber)
            else:
                self.callId = self.refPhone.CreateCall(phoneNumber)
        except Exception, ex:
            raise ReferencePhoneException('Unable to execute createCall command on the ReferencePhone: %s' % ex.message)

    def releaseCall(self):
        try:
            debug.brf('Releasing a call on the reference phone')
            if core.FW_conf['connection'].virtualPhone is not None and core.FW_conf['settings'].TestRun.EnableVirtualReferencePhone:
                core.FW_conf['connection'].virtualPhone.releaseCall()
            else:
                if self.callId != None:
                    self.refPhone.ReleaseCall(self.callId)
        except Exception, ex:
            raise ReferencePhoneException('Unable to execute releaseCall command on the ReferencePhone: %s' % ex.message)
      
    def answerCall(self):
        try:
            debug.brf('Answering a call on the reference phone')
            if core.FW_conf['connection'].virtualPhone is not None and core.FW_conf['settings'].TestRun.EnableVirtualReferencePhone:
                core.FW_conf['connection'].virtualPhone.answerCall()
            else:
                self.callId = self.refPhone.AnswerCall()
        except Exception, ex:
            raise ReferencePhoneException('Unable to execute answerCall command on the ReferencePhone: %s' % ex.message)

    def rejectCall(self, doNotReport = False):
        try:
            if not doNotReport:
                debug.brf('Rejecting a call on the reference phone')

            if core.FW_conf['connection'].virtualPhone is not None and core.FW_conf['settings'].TestRun.EnableVirtualReferencePhone:
                core.FW_conf['connection'].virtualPhone.releaseCall()
            else:
                self.refPhone.RejectCall()
        except Exception, ex:
            raise ReferencePhoneException('Unable to execute rejectCall command on the ReferencePhone: %s' % ex.message)
          
    def sendSms(self, phoneNumber):
        if core.FW_conf['connection'].virtualPhone is not None and core.FW_conf['settings'].TestRun.EnableVirtualReferencePhone:
            raise TestCaseWarning('sendSms not yet supported by Virtual Phone')
        else:
            try:
                self.refPhone.SendSMS(phoneNumber)
            except Exception, ex:
                raise ReferencePhoneException('Unable to execute sendSms command on the ReferencePhone: %s' % ex.message)

    def sendMms(self, phoneNumber, msgType=""):
        assert(msgType in ["", "contact", "calendar"], "Unknown msgType entered")
        if core.FW_conf['connection'].virtualPhone is not None and core.FW_conf['settings'].TestRun.EnableVirtualReferencePhone:
            raise TestCaseWarning('sendMms not yet supported by Virtual Phone')
        else:
            try:
                self.refPhone.SendMMS(phoneNumber,msgType)
            except Exception, ex:
                raise ReferencePhoneException('Unable to execute sendMms command on the ReferencePhone: %s' % ex)

    def touch(self, x, y):
        if core.FW_conf['connection'].virtualPhone is not None and core.FW_conf['settings'].TestRun.EnableVirtualReferencePhone:
            raise TestCaseWarning('touch command not supported by Virtual Phone')
        else:
            try:
                self.refPhone.Touch(x,y)
            except Exception, ex:
                raise ReferencePhoneException('Unable to execute touch command on the ReferencePhone: %s' % ex)
