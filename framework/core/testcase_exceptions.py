# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------------
"""Granite test case exceptions module.
    This module implements exception classes and functions for Granite FW.
"""

# Python library module imports
import sys, traceback

# Granite module imports
from utils.nodeutils import NodeUtils

# Local data structures

# ============================================================================
# TestException
# ----------------------------------------------------------------------------
class TestException(AssertionError):
    """Base class for all test case related exceptions."""
    def __init__(self, error, phone = None, takeErrorCapture = True, crashOrReset = False):
        AssertionError.__init__(self, error)
        self.phone = phone
        self.takeErrorCapture = takeErrorCapture
        self.crashOrReset = crashOrReset

    def tracebackToXml(self):
        # FIXME: Get rid of this when test scripts no longer use it!!!
        #raise DeprecationWarning('tracebackToXml method is deprecated!')

        # get only test script related stack trace line
        reason, traceText = getReasonAndStackTraceFromCurrentException(True)

        # create NodeUtils object
        tracebackTag = NodeUtils('traceback', True)
        tracebackTag['text'] = unicode(traceText, 'Latin-1')

        return tracebackTag

# ============================================================================
# SkipTestException
# ----------------------------------------------------------------------------
class SkipTestException(TestException):
    """Exception class for reporting skipped test cases."""
    pass

# ============================================================================
# StopTestException
# ----------------------------------------------------------------------------
class StopTestException(TestException):
    """Exception class for reporting fatal test results.

    If this is raised, the whole test execution must be terminated.
    """
    pass

# ============================================================================
# RemoteConnectionException
# ----------------------------------------------------------------------------
class RemoteConnectionException(TestException):
    """Exception class for errors with main <-> remote phone connection.

        These are reported as test environment errors.
    """
    pass

# ============================================================================
# BlackBoxException
# ----------------------------------------------------------------------------
class BlackBoxException(TestException):
    """Exception class for errors with main <-> blackbox connection.

        When this exception is catched the code should try to reinitialize or reset the blackbox driver.
    """
    pass

# ============================================================================
# ReferencePhonenException
# ----------------------------------------------------------------------------
class ReferencePhoneException(TestException):
    """Exception class for errors with reference phone connection.

    """
    pass

# ============================================================================
# RemotePhoneException
# ----------------------------------------------------------------------------
class RemotePhoneException(TestException):
    """Exception class for errors with remote phone execution.

    """
    pass

# ============================================================================
# TestCaseWarning
# ----------------------------------------------------------------------------
class TestCaseWarning(TestException):
    """Class for test case related warnings thrown by other modules

    """
    pass

# ============================================================================
# BltUeException
# ----------------------------------------------------------------------------
class BltUeException(TestException):
    """Exception class for errors thrown from BLT-UE inteface.

    """
    pass

# ============================================================================
# POXRobotException
# ----------------------------------------------------------------------------
class POXRobotException(TestException):
    """Exception class for errors in POX robot.

    """
    pass

# ============================================================================
# BackendConnectionException
# ----------------------------------------------------------------------------
class BackendConnectionException(TestException):
    """Exception class for errors with connection between Granite FW and Backend server.

    """
    pass

def getCurrentExceptionReason():
    """Gets reason from latest exception"""
    exception = sys.exc_info()[1]

    # store exception reason string
    reason = str(exception)

    # delete exception instance
    del exception

    return reason

def getReasonAndStackTraceFromCurrentException(onlyTestRelated = False):
    """Gets reason and stack trace lines from the latest exception.

    
        Parameters

        onlyTestRelated         return only test script related stack trace line
                                (default = False)
    """
    # get current exception reason
    reason = getCurrentExceptionReason()

    # get current exception traceback object
    traceback = sys.exc_info()[2]

    stackTrace = []
    
    # loop through stack trace and append trace lines to list
    while traceback is not None:
        frame = traceback.tb_frame
        lineno = traceback.tb_lineno
        code = frame.f_code
        filename = code.co_filename
        name = code.co_name
        stackTrace.append((filename, lineno, name))
        traceback = traceback.tb_next

    # clear current exception information
    sys.exc_clear()
    
    # delete traceback object after use
    if traceback:
        del traceback

    traceText = ""

    # search first non granite fw related stack trace line if needed
    if onlyTestRelated and stackTrace:
        for data in stackTrace:
            # first index has file path
            if not 'marble\\framework' in data[0]:
                stackTrace = [data]
                break

    # create trace text from traceback list
    for data in stackTrace:
        filePath, lineNumber, function = data
        traceText += "%s%s, %s, line: %s\n" % (\
            stackTrace.index(data) * '  ',
            filePath, function, lineNumber)

    return reason, traceText


