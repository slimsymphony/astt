import core
from core import uitestcase

class testBed(uitestcase.UITestCase):

    subarea = "Self tests"
    feature = "Read tests"

    def testRead(self):
        """
        @tcId Read
        """
        self.flick(direction='left')
        content = self.read()
        if not content:
            self.fail('Read did not return any values')

    def testReadFullInfo(self):
        """
        @tcId Read - Full info
        """
        self.flick(direction='left')
        textItems = self.read(fullInfo=True)
        for item in textItems:
            self.comment('%s | x=%s y=%s w=%s h=%s' % (item[0], item[1][0], item[1][1], item[1][2], item[1][3]))
        if not textItems:
            self.fail('Read did not return any values')

    def testReadDescription(self):
        """
        @tcId Read - Content description
        """
        self.navigate('Messaging')
        self.select.resourceId('android:id/toolbar_btn1')
        self.state.wait()
        content = self.read(checkedAttribute='content-desc')
        self.comment(content)
        if not content:
            self.fail('Read did not return any values')

    def testReadResourceId(self):
        """
        @tcId Read - Resource Id
        """
        self.flick(direction='left')
        content = self.read(checkedAttribute='resource-id')
        self.comment(content)
        if not content:
            self.fail('Read did not return any values')

    def testReadIndex(self):
        """
        @tcId Read - IndexTree
        """
        self.flick(direction='left')
        content = self.read(checkedAttribute='index')
        self.comment(content)
        if not content:
            self.fail('Read did not return any values')

    def testReadMultipleTypes(self):
        """
        @tcId Read - Multiple types
        """
        self.flick(direction='left')
        content = self.read(checkedAttribute=['text', 'resource-id'])
        self.comment(content)
        if not content:
            self.fail('Read did not return any values')

    def testReadMultipleTypesSearchString(self):
        """
        @tcId Read - Multiple types and search string
        """
        self.flick(direction='left')
        content = self.read('*a*', checkedAttribute=('text', 'resource-id'))
        self.comment(content)
        if not content:
            self.fail('Read did not return any values')

    def testReadSearchString(self):
        """
        @tcId Read - Search string
        """
        self.flick(direction='left')
        content = self.read('*arms')
        self.comment(content)
        if not content:
            self.fail('Read did not return any values')

    def testReadArea(self):
        """
        @tcId Read - Area
        """
        self.flick(direction='left')
        content = self.read(area=(5, 200, 400, 400))
        self.comment(content)
        if not content:
            self.fail('Read did not return any values')

    def testReadNotifications(self):
        """
        @tcId Read - Notifications
        """
        self.device.makeToast('Hi, I am a short notification')
        self.waitForEvent('TYPE_NOTIFICATION_STATE_CHANGED', timeout=5000)
        self.device.makeToast('Hi, I am the second short notification')
        self.waitForEvent('TYPE_NOTIFICATION_STATE_CHANGED', timeout=5000)
        self.device.makeToast('Hi, I am the third short notification')
        self.waitForEvent('TYPE_NOTIFICATION_STATE_CHANGED', timeout=5000)

        resp = self.read.notifications()
        for note in resp:
            self.comment('%s : %s' % (note[0], note[1]))

        if len(resp) < 3:
            self.fail('Atleast three notifications should be found, got %s instead' % len(resp))

    def testReadNotificationsFiltered(self):
        """
        @tcId Read - Notifications (filtered)
        """
        self.device.makeToast('Hi, I am a short notification')
        self.waitForEvent('TYPE_NOTIFICATION_STATE_CHANGED', timeout=5000)
        self.device.makeToast('Hi, I am the second short notification')
        self.waitForEvent('TYPE_NOTIFICATION_STATE_CHANGED', timeout=5000)
        self.device.makeToast('Hi, I am the third short notification')
        self.waitForEvent('TYPE_NOTIFICATION_STATE_CHANGED', timeout=5000)

        resp = self.read.notifications('*second*')
        for note in resp:
            self.comment('%s : %s' % (note[0], note[1]))

        if len(resp) != 1:
            self.fail('Only one notification should be matched, found %s instead' % len(resp))

    def testReadNotificationsFilterTime(self):
        """
        @tcId Read - Notifications (filtered by time)
        """
        self.device.makeToast('Hi, I am a short notification')
        self.waitForEvent('TYPE_NOTIFICATION_STATE_CHANGED', timeout=5000)
        self.device.makeToast('Hi, I am the second short notification')
        self.waitForEvent('TYPE_NOTIFICATION_STATE_CHANGED', timeout=5000)
        self.device.makeToast('Hi, I am the third short notification')
        self.waitForEvent('TYPE_NOTIFICATION_STATE_CHANGED', timeout=5000)

        resp = self.read.notifications(bestBefore = 200)
        for note in resp:
            self.comment('%s : %s' % (note[0], note[1]))

        if len(resp) != 1:
            self.fail('Only one notification should be matched, found %s instead' % len(resp))