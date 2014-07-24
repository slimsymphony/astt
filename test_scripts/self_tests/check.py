import core
from core import uitestcase
from core.testcase_exceptions import TestException

class testBed(uitestcase.UITestCase):

    subarea = "Self tests"
    feature = "Check tests"

    def testCheckNotification(self):
        """
        @tcId Check notification - wild cards
        """
        mainNumber = self.settings.Main.SIM1PhoneNumber
        assert mainNumber, 'Phone number of SIM1 for the main phone is not defined in settings'

        self.comment('Step 1. Send message from the remote phone to main phone')
        self.remote.srv.messaging.generateMessage(text="Hellow", recipient=self.settings.Main.SIM1PhoneNumber, type="sms", state="pending", location="outbox")

        self.comment('Step 2. Wait for the message to be received')
        resp = self.waitForEvent('TYPE_NOTIFICATION_STATE_CHANGED', timeout=20000)
        if not resp:
            self.fail('Could not receive new notification event')
        else:
            # Save notification to report for easier debugging if the texts are changed
            self.capture()
            self.comment(self.read.notifications())

        # The displayed notification has two alternatives:
        #'New messages (17)' or '+358 50 48xxxxx: SUB1-Hello'
        self.comment('Step 3. Verify if \'New messages*\' or longer format notification is displayed')
        success = self.check.notification(['New messages*', '*Hellow*'], bestBefore=5000, timeout=0)

        if not success:
            self.fail('Could not match new message notification')

    def testCheckNotificationToast(self):
        """
        @tcId Check notification toast
        """
        self.device.makeToast('Hi, I am a short notification')
        if not self.check.notification('Hi, I am a short notification'):
            self.fail('Could not verify toast')

    def testCheckNotificationToastWildcard(self):
        """
        @tcId Check notification toast - wild cards
        """
        self.device.makeToast('Hi, I am a short notification')
        if not self.check.notification('*short*'):
            self.fail('Could not verify toast')

    def testCheckNotificationToastBestBefore(self):
        """
        @tcId Check notification toast - best before
        """
        self.comment('Step 1. Create toast notification')
        self.device.makeToast('Hi, I am a short notification')

        self.comment('Step 2. Wait for notification to expire and test that check fails')
        self.delay(2000)
        if self.check.notification('Hi, I am a short notification', bestBefore=1000, timeout=0):
            self.fail('Toast is verified although it has expired')

    def testCheckNotificationToastBestBeforeZero(self):
        """
        @tcId Check notification toast - best before zero
        """
        self.comment('Step 1. Create toast notification and wait for it to expire')
        self.device.makeToast('Check notification toast - best before zero')
        self.delay(2000)

        self.comment('Step 2. Create another toast notification and try to verify it')
        passed = False
        tryCount = 0
        while not passed and tryCount < 3:
            if tryCount:
                self.comment('Trying again (%s of 3)' % (tryCount+1))
            tryCount += 1
            self.device.makeToast('Check notification toast - best before zero')
            if self.check.notification('Check notification toast - best before zero', bestBefore=0):
                passed = True
                break

            if self.read.notifications('Check notification toast - best before zero', bestBefore=6000):
                self.comment('Toast was displayed before the check.')
            else:
                self.comment('Toast was not displayed at all.')

        if not passed:
            self.comment(self.read.notifications())
            notes = self.read.notifications('Check notification toast - best before zero', bestBefore=6000)
            if notes:
                self.fail('Could not verify toast although it was displayed')
            else:
                self.fail('Could not verify toast because it was displayed before the check or not displayed at all')

    def testExpectNotificationToast(self):
        """
        @tcId Expect notification toast
        """
        self.device.makeToast('Hi, I am a short notification')
        self.expect.notification('Hi, I am a short notification')

        passed = False

        try:
            self.expect.notification('Non existing notification')
        except TestException:
            passed = True

        if not passed:
            self.fail('Expect passed although corresponding notification was not displayed')

    def testNotExpectNotificationToast(self):
        """
        @tcId NotExpect notification toast
        """
        self.device.makeToast('Hi, I am a short notification')
        self.notExpect.notification('*long*')

        passed = False

        try:
            self.notExpect.notification('*short*')
        except TestException:
            passed = True

        if not passed:
            self.fail('NotExpect passed although corresponding notification was displayed')
