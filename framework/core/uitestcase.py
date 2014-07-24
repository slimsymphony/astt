# -*- coding: utf-8 -*-
"""UI Test Case module.

    Utility functions and a base class to be used in UI test cases.
"""

# ============================================================================
# Module Setup

import core, uitestcase
from core.testcase import TestCase

from Nokia.Granite.IPC.Interfaces import FiascoTask, FailureTask


# ============================================================================
class UITestCase(TestCase):
# ----------------------------------------------------------------------------
    """Common base class for UI test scripts.
    """
    def __init__(self, methodName = None, tcId = ""):
        TestCase.__init__(self, methodName, tcId)
        self.__testStepNameIndex = 1
        self.__captureNameIndex = 1

    def _setUp(self):
        """Setup step called before an UI test case is run.

        This method verifies that both the phone and the Granite server are ready
        to receive the next UI test step(s).
        """
        TestCase._setUp(self, uiEnabled=True)

        debug.out("UITestCase setUp start")
        if core.FW_conf['blackbox'] != None and core.FW_conf['blackbox_enabled']:
            core.FW_conf['blackbox'].videoRecording_SetText('Marble test setup')
        if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
            core.FW_conf['leader'].currentTestStep = 'Marble test setup'

        if len(core.FW_conf['remote_connection']) > 0:
            core.FW_conf['remote_connection'].setupRemotePhonesForUITesting()

        # Ensure that there is no call ongoing on the reference phone when testcase starts running - unless user skips setup and teardown
        if self.referencePhone is not None and \
            core.FW_conf['settings'].TestRun.AutomaticRejectCallForReferencePhone:
            try:
                self.referencePhone.rejectCall(doNotReport = True)
            except Exception, ex:
                debug.err('Testcase setup: %s' %str(ex))

        core.FW_conf['connection']._uiSetUp(self) # Move this to Phone.setup

        for remote in core.FW_conf['remote_connection']:
            remote._uiSetUp(self) # Move this to Phone.setup

    def _tearDown(self):
        """Steps which are executed after UI test case run."""
        TestCase._tearDown(self)

        debug.out("UITestCase tearDown start")

        self.logApply(core.FW_conf['connection']._uiTearDown, self)

        for remote in core.FW_conf['remote_connection']:
            self.logApply(remote._uiTearDown, self)
        
        if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader' and core.FW_conf['leader'].LeaderExecutionQueueLen() > 0:
            self.__purgeFollowerRequests()
        
    def __purgeFollowerRequests(self):
        """ Follower failures / requests are processed via this method """
        
        limit = 200
        fail = False
        while core.FW_conf['leader'].LeaderExecutionQueueLen() > 0:
            task = core.FW_conf['leader'].serviceClass.LeaderExecutionQueue
            debug.out("task type: %s" % type(task))
            
            # String Tasks will be executed as string
            if type(task) == FiascoTask:
                self._warn("Client %s failed miserably on step %s. Reason %s" % (task.ClientId, task.Step, task.Reason))
                fail = True

            if type(task) == FailureTask:
                self._warn("Client %s failed on step %s. Reason %s" % (task.ClientId, task.Step, task.Reason))

            else:
                debug.brf("type %s task does not have handler" % type(task))

            limit -= 1
            if limit < 0:
                debug.err('too many follower requests in pipe, purge loop limit reached. continuing execution..')
                break

        if fail: 
            self.fail('Case failed in Follower. Check warnings.')
