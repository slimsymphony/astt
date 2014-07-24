import time,random, os, string
from System.Diagnostics import Process

import core
from core import uitestcase,phone
from utils.nodeutils import NodeUtils
from datetime import date, datetime

from core import phone
from core.testcase_exceptions import TestException

class ScriptingSelfTests(uitestcase.UITestCase):

    subarea = "Self Tests"
    feature = "Scripting"


    def setUp(self):
        """ test case specific setup"""
        pass


    def tearDown(self):
        """ test case specific teardown"""
        pass


    def testSelect(self):
        """

        @tcId Test selection
        """
        self.select('Gallery')
        self.select('KEYCODE_BACK')
        self.select('Phone')

    def testNotExpectAndCheck(self):
        """

        @tcId Test check and notExpect
        """
        self.navigate('Downloads')
        # test check
        if self.check('No downloads'):
            self.comment('Not any downloads done yet')

        # test not expect
        self.back()
        self.navigate('Settings')
        self.notExpect('not on screen')
        self.expect('Display')


    def testSelectWithCoordinates(self):
        """

        @tcId Test select with coordinates
        """

        #Make sure we are on top of screen
        self.navigate('Settings')
        if self.tryExpect('Sounds', fromArea =(20, 500, 180, 160)):
            self.comment('Sounds found from area 20, 500, 180, 160')
            #relative coordinates used, absolute coordinates (100, 535)
            self.comment('select Sounds with coordinates')
            self.select((0.2083, 0.6687)) #relative coordinates used
        else:
            self.fail('Failed to found Sounds from area 20, 500, 180, 160')

    def testNavigate(self):
        """
        @tcId Test navigate
        """
        apps = ["Phone", "Messaging", "People",
                  "Gallery", "Music", "Store", "Calculator",
                  "Settings", "Downloads"]
        self.comment('Navigate to apps: %r' % apps)
        for i in range(len(apps)):

            self.navigate(apps[len(apps)-1-i])
            self.capture()
            self.comment(self.state.get())

            if apps[len(apps)-1-i] == 'Phone' and 'dialer' not in self.state.get():
                self.fail('Failed to navigate to Phone')
            elif apps[len(apps)-1-i] == 'Messaging' and 'mms' not in self.state.get():
                self.fail('Failed to navigate to Messaging')
            elif apps[len(apps)-1-i] == 'People' and 'contacts' not in self.state.get():
                self.fail('Failed to navigate to People')
            elif apps[len(apps)-1-i] == 'Gallery' and 'gallery' not in self.state.get():
                self.fail('Failed to navigate to Gallery')
            elif apps[len(apps)-1-i] == 'Music' and 'music' not in self.state.get():
                self.fail('Failed to navigate to Music')
            elif apps[len(apps)-1-i] == 'Store' and 'store' not in self.state.get():
                self.fail('Failed to navigate to Store')
            elif apps[len(apps)-1-i] == 'Calculator' and 'calculator' not in self.state.get():
                self.fail('Failed to navigate to Calculator')
            elif apps[len(apps)-1-i] == 'Settings' and 'settings' not in self.state.get():
                self.fail('Failed to navigate to Settings')
            elif apps[len(apps)-1-i] == 'Downloads' and 'download' not in self.state.get():
                self.fail('Failed to navigate to Downloads')

            self.back()


    def testNavigateDoNotSelect(self):
        """

        @tcId test navigate - do not select
        """
        self.comment('Navigate Gallery,but do not select it')
        self.navigate('Gallery', doNotSelect=True)
        self.comment('Galley icon should be visible on screen')
        self.expect('Gallery')
        if 'gallery' in self.state.get():
            self.fail("Navigated to Music and selected it doNotSelect not working")


    def testNavigateJump(self):
        """
        @tcId Test navigate jump
        """
        #self.comment(self.device.getLaunchableApplications())
        self.navigate.jump('Phone')
        self.select.resourceId('com.android.dialer:id/tabs', index=1)
        self.expect.description('Dial')
        self.back()
        self.comment('Navigate.jump to People')
        self.navigate.jump('com.android.contacts/activities.PeopleActivity')
        if 'contacts' not in self.state.get():
            self.fail('Failed to navigate.jump to People')
        self.back()

    def testNavigateFromRecent(self):
        """

        @tcId test navigate - from recent apps
        """
        self.comment('navigate normally to Phone')
        self.navigate('Phone')
        if not 'dialer' in self.state.get():
            self.fail('Failed to navigate to Phone')
        self.back()

        self.comment('navigate to Phone from recent apps')
        self.navigate('Phone', fromRecent = True)
        if not 'dialer' in self.state.get():
            self.fail('Failed to navigate to Phone')
        self.back()

        self.comment('clear Phone from recent apps and navigate to Phone to normally')
        self.navigate('Phone', fromRecent = False)
        if not 'dialer' in self.state.get():
            self.fail('Failed to navigate to Phone')

    def testCheck(self):
        """

        @tcId test check
        """
        self.navigate('Settings')
        self.select('Display')
        # test check
        if self.check.text('Brightness'):
            self.comment('Brightness found from screen')
        if self.check('asdfasdfasdf', timeout=1000):
            self.fail('asdfasdfasdf should not be found from here')
        if not self.check.description('Display, Navigate up'):
            self.fail('Failed to check description')
        self.comment('Verify that check also scrolls to upwards')
        self.back(2)
        self.flick(direction='left')
        self.navigate('Settings')
        self.back()
        if not self.check('Calculator'):
            self.fail('Failed to scroll up to Calculator')
        self.navigate('Phone')
        self.select.resourceId('com.android.dialer:id/tabs', index=1) # Dialer screen
        if not self.check.resourceId('com.android.dialer:id/dialButton', timeout=1000):
            self.fail('Failed to check resourceId')

    def testExpect(self):
        """

        @tcId Test expect
        """
        self.navigate('Settings')
        self.expect('Display')
        self.select('Display')
        self.expect.text('*screen*', occurrence = 2)
        self.back()
        self.select('Sounds')
        self.select('Volume')
        self.expect(['Alarms','Ringtone*', 'OK'])


    def testnotExpect(self):
        """

        @tcId Test notExpect
        """

        self.navigate('Alarms')
        self.expect('Alarms')
        self.notExpect('Clock')


    def testSwipe(self):
        """

        @tcId Test swipe
        """
        self.navigate('Messaging')
        self.delay(1000)
        self.comment('Swipe to open message settings')
        self.swipe((235,795), (235,350))
        self.delay(500)
        if not self.tryExpect('Settings'):
            self.fail('Message Settings not opened')
        self.navigate('Settings')
        self.back(2)
        self.comment('Swipe from top to down')
        self.swipe((235,1), (235,700))
        self.expect.resourceId('com.android.systemui:id/notification_text')


    def testDoubleTap(self):
        """

        @tcId Test double tap
        """
        self.comment('DoubleTap under construction')
        self.navigate('Alarms')
        return
        i = 0
        self.select('KEYCODE_POWER')
        self.comment('Wait until glancescreen is on')
        self.delay(5000)
        while 'glancescreen' not in self.state.get() and i < 10:
            self.delay(1000, doNotReport = True)
            self.comment(i)
            i += 1

        self.comment('test double tap, by tapping in middle of screen')
        self.doubleTap((0.500, 0.500))
        self.doubleTap((0.500, 0.500))
        self.doubleTap((0.500, 0.500))



    def testTryExpect(self):
        """

        @tcId Test tryExpect
        """
        self.navigate('Settings')
        self.select('Time and date')
        result1 = self.tryExpect([['Set time','Set date'],['dsagsagd','sadfsadg']])
        self.comment('Result: %s'%result1)
        result2 = self.tryExpect([['Bluetooth','Ring tone'],['Set time','Set date']])
        self.comment('Result: %s'%result2)
        result3 = self.tryExpect([['Set time','Set date'],['!dsagsagd','!sadfsadg']])
        self.comment('Result: %s'%result3)
        result4 = self.tryExpect([['!Set time','!Set date'],['Set time','Set date']]) # (Time) # (Date)
        self.comment('Result: %s'%result4)
        result5 = self.tryExpect([['!Set date']])
        self.comment('Result: %s'%result5)

        if result1!=[0] or result2!=[1] or result3!=[0,1] or result4!=[1] or result5!=[]:
            self.fail('Selftest failed!')


    def testInput(self):
        """
        @tcId Test input
        """
        self.navigate('Messaging')
        self.select.resourceId('android:id/toolbar_btn1')
        # Message editor is opened automatically
        self.state.wait()
        self.input.push('Marble rulez OK!')
        self.expect('Marble rulez OK!')
        self.clear()

        self.comment('Input using virtual keyboard')
        self.input.write('Marble rulez OK!')
        self.expect('Marble rulez OK!')
        self.clear()

        self.back(2)

    def testClear(self):
        """
        @tcId Test clear
        """
        self.comment('test clear')
        self.navigate('Messaging')
        self.select.resourceId('android:id/toolbar_btn1')
        self.select((0.4999, 0.9499)) #(240,760)
        #self.select.resourceId('com.android.mms:id/embedded_text_editor')
        self.select('Tap to write your message')
        self.input.push('Testing clear')
        self.clear()
        self.expect('Tap to write your message')
        self.input('add some more text')
        self.expect('add some more text')
        self.clear()
        self.input('yet another text addition')
        self.expect('yet another text addition')

    def testSelectLong(self):
        """

        @tcId Test selectLong
        """

        return
        self.comment('Long  press icon on main menu')
        items = self.read.resourceId()

        self.select.long((70,95))
        if self.tryExpect.resourceId('com.nokia.homescreen:id/button_size') != [0]:
            self.fail('Failed to long press icon')
        self.back()
        self.navigate('Music')
        self.select((420,765))
        if not self.expect('Recently added'):
            return
        self.select.long('Recently added', length=3500)
        if self.tryExpect('Play') != [0]:
            self.fail('Long press failed')

    def testLandscapeAndPortrait(self):
        """

        @tcId Test Landscape and Portrait
        """
        self.navigate('Settings')
        self.comment(self.orientation.get())
        self.orientation.setLandscape()
        self.comment(self.orientation.get())
        self.orientation.setPortrait()
        self.comment(self.orientation.get())


    def testTime(self):
        """

        @tcId Test Time
        """
        systemDateTime = self.time.getSystemDateTime()
        self.comment('System Date and Time %s' %systemDateTime)
        self.time.setSystemTime(hour = 15, minute = 45, second = 45)
        self.time.setSystemDate(2013,10,15)
        self.time.setSystemDateTime(datetime(2013, 10, 25, 15, 45, 45))
        systemDateTime = self.time.getSystemDateTime()
        self.comment('System Date and Time %s' %systemDateTime)
        self.delay(2500, False)
        self.comment('setsystemtime %s' %self.time.setSystemTime(hour = 22, minute = 05, second = 12))
        self.comment('setsystemdate %s' %self.time.setSystemDate(2014,06,11))
        systemDateTime = self.time.getSystemDateTime()
        self.comment('System Date and Time %s' %systemDateTime)
        self.comment(self.time.synchPcDateTime())
        systemDateTime = self.time.getSystemDateTime()
        self.comment('PC time to System Date and Time %s' %systemDateTime)


    def testCapture(self):
        """

        @tcId Test Capture
        """
        self.capture()
        self.capture(savePath = os.path.normpath(os.path.join(core.FW_conf['test_result_dir'], 'captured bitmaps', 'capture_test_1.png')))
        self.capture(savePath = 'capture_test_2.png')

    def testFail(self):
        """

        @tcId Test Fail
        """
        self.comment('Step 1. Call self.fail() and catch TestException')
        passed = False
        try:
            self.fail('Fail on purpose')
        except TestException:
            passed = True

        if not passed:
            assert 0, 'Case did not fail although self.fail() was called'


    def testFlick(self):
        """

        @tcId test flick
        """
        self.flick(direction='right')
        self.delay(1000)
        self.flick(direction='left')
        self.delay(1000)
        self.flick(direction='left')
        self.delay(1000)
        self.flick(direction='up')
        self.delay(1000)
        self.flick()
        self.delay(1000)
        self.flick(direction='down')
        self.delay(1000)
        self.flick((0.9, 0.8), 'up')
        self.delay(1000)
        self.flick((150, 150), 'down')
        self.delay(1000)
        items = self.read()
        self.flick(items[3])
        self.delay(1000)
        items = self.read()
        self.flick(items[5], 'down')
        self.delay(1000)
        items = self.read()
        self.flick(items[2], direction='right')
        self.delay(1000)

    def testToggle(self):
        """

        @tcId test toggle
        """
        self.navigate('Settings')
        self.toggle('Wi-Fi')
        self.comment(self.toggle.get('Wi-Fi'))
        self.toggle.set('Wi-Fi', False)
        self.comment(self.toggle.get('Wi-Fi'))

    def testGestureDrag(self):
        """

        @tcId test drag
        """
        # NOTE: loop twice so that original main menu item order is restored
        for i in range(2):
            self.drag('Messaging', 'Phone')
            self.back()
            self.drag('Messaging', (375, 67))
            self.back()

    def testReboot(self):
        """

        @tcId Test reboot device
        """
        self.reboot()

    def testVolume(self):
        """

        @tcId Test Volume changes
        """
        #self.comment(self.volume.getMedia())
        #self.comment(self.volume.getRinger())
        self.volume.setMedia(7)
        self.volume.setRinger(3)
        self.comment('step 1')
        self.comment(self.volume.getMedia())
        self.comment(self.volume.getRinger())
        if self.volume.getMedia() != 7:
            self.fail('Failed to set Media volume to 7')
        if self.volume.getRinger() != 3:
            self.fail('Failed to set Ringer volume to 3')
        self.volume.up() #ringer -> 4
        if self.volume.getRinger() != 4:
            self.fail('Failed to use volume up')
        self.volume.up(2) #ringer -> 6
        if self.volume.getRinger() != 6:
            self.fail('Failed to use volume up')
        self.volume.down() #ringer -> 5 or Media -> 9
        if self.volume.getRinger() != 5:
            self.fail('Failed to use volume down')
        self.volume.down(4) #ringer -> 1
        if self.volume.getRinger() != 1:
            self.fail('Failed to se volume down')

    def testWildCards(self):
        """

        @tcId Test wildcards
        """
        self.navigate('?ettings') #Settings
        self.state.wait()
        self.back()
        self.navigate('*cula*') #Calculator
        self.state.wait()
        self.back()
        self.notExpect('Cal?culator')
        self.navigate('Sett*ings')
        if not self.check('D[khfsiKASD]sp?a*'): #display
            self.fail('Failed to find D[khfsiKASD]sp?a* from screen')
        self.back()
        self.navigate('Calculator', doNotSelect=True)
        if not 0 in self.tryExpect('Cal[oiCcu]ulator'):
            self.fail('Failed to find Cal[oiCcu]ulator from screen')
        if not 0 in self.tryExpect('Cal[!lkfdsi]ulator'):
            self.fail('failed to expect Cal[!lkfdsi]ulator')


    def testRamDump(self):
        """

        @tcId Test ram dump
        """
        if Process.GetProcessesByName("QPSTConfig"):
            self.comment(self.shell('adb root'))
            self.shell("echo c> /proc/sysrq-trigger")
        else:
            self.fail('QPST not running, cannot get RAM dumps')


    def testFileCopy(self):
        """

        @tcId Test file write
        """
        FILE_STORAGE = self.file.temp
        self.file.createDirectory(FILE_STORAGE + 'test')
        #self.comment(FILE_STORAGE)
        try:
            self.file.writeFile(resources('capture.png'), FILE_STORAGE + 'test/capture.png')
        except Exception, e:
            self.comment(e)

        if not self.file.fileExists(FILE_STORAGE + 'test/capture.png'):
            self.fail('Creating file to phone memory failed!')
        self.comment('Succesfully created file to phone memory')
        self.delay(1000, False)
        self.file.removeFile(FILE_STORAGE +'test/capture.png')
        self.file.removeDirectory(FILE_STORAGE + 'test')


    def testCreateFolder(self):
        """

        @tcId Test create folder
        """
        FILE_STORAGE = self.file.temp
        self.file.createDirectory(FILE_STORAGE + 'test')
        if not self.file.directoryExists(FILE_STORAGE + 'test'):
            self.fail('Creating file to phone memory failed!')
        self.comment('Succesfully created directory to phone memory, now remove it ')
        self.delay(1000, False)
        self.file.removeDirectory(FILE_STORAGE + 'test')


    def testFileDate(self):
        """

        @tcId Test file date
        """
        FILE_STORAGE = self.file.temp
        self.file.createDirectory(FILE_STORAGE + 'test')
        #self.comment(FILE_STORAGE)
        self.file.writeFile(resources('capture.png'), FILE_STORAGE + 'test/capture.png')
        self.delay(1500)
        if not self.file.fileExists(FILE_STORAGE + 'test/capture.png'):
            self.fail('Creating file to phone memory failed!')
        self.comment(self.file.getDate(FILE_STORAGE + 'test/capture.png'))
        self.delay(1000, False)
        self.file.removeFile(FILE_STORAGE +'test/capture.png')
        self.file.removeDirectory(FILE_STORAGE + 'test')


    def testGetFolderContent(self):
        """

        @tcId Test get folder content
        """
        FILE_STORAGE = self.file.externalStorage
        folderContent = self.file.getFolderContent(FILE_STORAGE)
        for i in range(len(folderContent[1])):
            self.comment(folderContent[1][i])

    def testTimePicker(self):
        """

        @tcId Test time picker
        """

        self.navigate('Alarms')
        self.select.resourceId('android:id/toolbar_btn1')
        for i in range(5):
            randH = random.randint(0,23)
            randM = random.randint(0,59)
            self.time.pickTime(randH, randM)
            currentTime = self._pickTime._TimePicker__getTimeFromScreen()
            if randH != currentTime[0] or randM != currentTime[1]:
                self.fail('time %s:%s was not picked correctly! (%s:%s)' % (randH, randM, currentTime[0], currentTime[1] ))

    def testDatePicker(self):
        """

        @tcId Test date picker
        """

        self.navigate('Settings')
        self.select('Time and date')
        self.toggle.set('Automatic date and time', False) # toggle automatic date and time off
        self.select.text('Set date')

        startDate = self._pickDate._readCurrentDate()

        i = 0
        while i < 3:
            randY = random.randint(1970,2037)
            randM = random.randint(1,12)
            randD = random.randint(1,31)
            try:
                getThis = date(randY, randM, randD)
            except:
                debug.brf('cannot create date %s %s %s. next ->' % (randY, randM, randD))
                continue
            i += 1
            debug.brf('test selecting date %s -- iteration %s' % (getThis, i))
            self.time.pickDate(randY, randM, randD)
            selected = self._pickDate._readCurrentDate()
            self.failIf( randY != selected.year, "year was not valid in selected date (%s vs %s)" % (getThis, selected))
            self.failIf( randM != selected.month, "month was not valid in selected date (%s vs %s)" % (getThis, selected))
            self.failIf( randD != selected.day, "day was not valid in selected date (%s vs %s)" % (getThis, selected))

        self.time.pickDate(selectdate=startDate) # back to original time

    def testFileMove(self):
       """
       @tcId Test file move
       """
       FILE_STORAGE = self.file.temp
       self.file.createDirectory(FILE_STORAGE + 'test')
       #self.comment(FILE_STORAGE)
       self.file.writeFile(resources('capture.png'), FILE_STORAGE + 'test/capture.png')
       self.file.move(FILE_STORAGE + 'test/capture.png', FILE_STORAGE + 'capture.png')
       if not self.file.fileExists(FILE_STORAGE + 'capture.png'):
           self.fail('Creating file to phone memory failed!')
       self.file.removeFile(FILE_STORAGE + 'capture.png')
       self.file.removeDirectory(FILE_STORAGE + 'test')


    def testFileRead(self):
        """

        @tcId Test file read
        """
        self.comment
        self.comment(self.currentTcId)
        FILE_STORAGE = self.file.temp
        self.file.createDirectory(FILE_STORAGE + 'test')
        self.file.writeFile(resources('capture.png'), FILE_STORAGE + 'test/capture.png')
        if not self.file.fileExists(FILE_STORAGE + 'test/capture.png'):
            self.fail('Creating file to phone memory failed!')
        self.file.readFile(FILE_STORAGE + 'test/capture.png', '..//test_scripts//self_tests//capture_copy.png')
        self.delay(5000)
        if os.path.isfile('..//test_scripts//self_tests//capture_copy.png'):
            self.delay(2000)
            os.remove('..//test_scripts//self_tests//capture_copy.png')


    def testFileAttributes(self):
        """

        @tcId Test file attributes
        """
        FILE_STORAGE = self.file.temp
        self.file.createDirectory(FILE_STORAGE + 'test')
        self.file.writeFile(resources('capture.png'), FILE_STORAGE + 'test/capture.png')
        if not self.file.fileExists(FILE_STORAGE + 'test/capture.png'):
            self.fail('Creating file to phone memory failed!')
        self.comment('Original file attributes for' + str(FILE_STORAGE) + 'test/capture.png ' + str(self.file.getAttributes(FILE_STORAGE + 'test/capture.png')))
        self.comment(self.file.setAttributes(FILE_STORAGE + 'test/capture.png',7))
        self.comment(self.file.getAttributes(FILE_STORAGE + 'test/capture.png'))
        if self.file.getAttributes(FILE_STORAGE + 'test/capture.png') != (7, 7, 7):
            self.fail('Failed to set file attributes')
        self.file.setAttributes(FILE_STORAGE + 'test/capture.png',6,5,0)
        if self.file.getAttributes(FILE_STORAGE + 'test/capture.png') != (6, 5, 0):
            self.fail('Failed to set file attributes')
        self.file.setAttributes(FILE_STORAGE + 'test/capture.png',9,5,-2)
        self.comment(self.file.getAttributes(FILE_STORAGE + 'test/capture.png'))
        if self.file.getAttributes(FILE_STORAGE + 'test/capture.png') != (7, 5, 0):
            self.fail('Failed to set file attributes')
        self.file.removeFile(FILE_STORAGE + 'test/capture.png')
        self.file.removeDirectory(FILE_STORAGE + 'test')



    def testPackages(self):
        """

        @tcId Test packages
        """
        self.comment('List of installed packages on device:')
        packagesDict = self.packages.listPackages()
        for item in packagesDict.iteritems() :
            self.comment('%s - %s' % (item[0], item[1]))

        #Install new package
        apkLocation, package = self.packages.installPackage(resources('NnaTestTool-release.apk'))
        apkTime = self.file.getDate(apkLocation)
        self.navigate('NNA Test App')
        self.back()
        #wait 60sec so we can check if don't reinstall if apk package already exits works
        self.delay(60000)
        #check if
        apkLocation, package = self.packages.installPackage(resources('NnaTestTool-release.apk'), False)
        if apkTime == self.file.getDate(apkLocation):
            self.comment('Package already existed on device so reinstall was not needed')

        self.comment('Remove installed package' + package)
        success = self.packages.uninstallPackage(package)


    def testFolderRemoveItems(self):
        """

        @tcId Test folder remove items
        """
        FILE_STORAGE = self.file.temp
        self.file.createDirectory(FILE_STORAGE + 'test')
        for i in range(10):
            self.file.writeFile(resources('capture.png'), FILE_STORAGE + 'test/capture_' + str(i) + '.png')
        self.file.removeItems(FILE_STORAGE + 'test')
        for i in range(10):
            if self.file.fileExists(FILE_STORAGE + 'test/capture_' + str(i) + '.png'):
                self.fail('failed to remove file: ' + FILE_STORAGE + 'test/capture_' + str(i) + '.png')
        self.file.removeDirectory(FILE_STORAGE + 'test')


    def testFileSize(self):
        """
        @tcId Test file size
        """
        FILE_STORAGE = self.file.temp
        self.file.createDirectory(FILE_STORAGE + 'test')
        self.file.writeFile(resources('capture.png'), FILE_STORAGE + 'test/capture.png')
        if self.file.getFileSize(FILE_STORAGE + 'test/capture.png') != 0:
            self.comment(self.file.getFileSize(FILE_STORAGE + 'test/capture.png'))
        else:
            self.fail('Failed to get file size')
        self.file.removeFile(FILE_STORAGE + 'test/capture.png')
        self.file.removeDirectory(FILE_STORAGE + 'test')


    def testFileType(self):
        """

        @tcId Test file type
        """
        FILE_STORAGE = self.file.temp
        self.file.createDirectory(FILE_STORAGE + 'test')
        self.file.writeFile(resources('capture.png'), FILE_STORAGE + 'test/capture.png')
        self.comment(self.file.getType(FILE_STORAGE + 'test/capture.png'))
        self.comment(self.file.getType(FILE_STORAGE + 'test/'))
        self.file.removeDirectory(FILE_STORAGE + 'test')

    def testFileCat(self):
        """

        @tcId Test file cat
        """
        FILE_STORAGE = self.file.temp
        self.file.createDirectory(FILE_STORAGE + 'test')
        self.file.writeFile(resources('Marble_text.txt'), FILE_STORAGE + 'test/Marble_text.txt')
        content = self.file.cat(self.file.temp + 'test/Marble_text.txt')
        for line in content:
            self.comment(line)

    def testGetItem(self):
        """

        @tcId Test get item
        """
        self.navigate('Calculator', doNotSelect = True)

        self.comment('Get calculator item')
        origNode = self.getItem('Calculator', autoRefresh = False)
        node = self.getItem('Calculator', area = (0, 0, 480, 800))

        self.comment('Calculator item: %s' % str(node))

        #self.comment('description: %s' % node.getDescription())
        #self.comment('text: %s' % node.getText())
        #self.comment('resource id: %s' % node.getResourceId())
        #self.comment('index tree: %s' % node.getIndexTree())
        #self.comment('bounds: %s' % str(node.getBounds()))
        #self.comment('center point: %s' % str(node.getCenterPoint()))
        #self.comment('isChecked: %s' % node.isChecked())
        #self.comment('isCheckable: %s' % node.isCheckable())
        #self.comment('isClickable: %s' % node.isClickable())

        self.comment('Select Calculator item')
        node.select()
        self.back()

        self.comment('Swipe screen a bit')
        self.swipe((0.5, 0.5), (0.5, 0.4))

        self.comment('Check that coordinates changed')
        if (origNode.getCenterPoint() == node.getCenterPoint()):
            self.fail('Item center point did not change after swipe')

        # test getItems
        foundNodes = self.getItems('com.nokia.homescreen:id/app_name')

        self.failIf(len(foundNodes) == 0, 'getItems did not find any nodes!')

        self.comment('getItems returned:')
        for foundNode in foundNodes:
            self.comment(str(foundNode))


class ScriptingRemoteTests(uitestcase.UITestCase):

    subarea = "Remote Tests"
    feature = "Scripting"


    def setUp(self):
        """ test case specific setup"""
        pass

    def tearDown(self):
        """ test case specific teardown"""
        self.remote.srv.call.end()

    def testRemoteMOCall(self):
        """

        @tcId Test create call to remote
        """
        remoteNumber = self.settings.Remote.SIM1PhoneNumber
        assert remoteNumber, 'Phone number of SIM1 for the remote phone is not defined in settings'

        self.select('Phone')
        if self.tryExpect.text('Use keypad', timeout=1000):
            self.select.text('Use keypad')
        self.input(remoteNumber)
        #self.select.resourceId('com.android.dialer:id/digits')
        self.select.description('Dial')
        self.delay(15000)
        self.remote.srv.call.answer()
        self.comment('Remote phone answering call')
        self.delay(15000)
        self.select.resourceId('com.android.phone:id/endButton')
        self.back()

    def testRemoteMTCall(self):
        """

        @tcId Test MT call from remote
        """
        mainNumber = self.settings.Main.SIM1PhoneNumber
        assert mainNumber, 'Phone number of SIM1 for the main phone is not defined in settings'

        self.comment('Create call from remote')
        #self.comment(self.settings.Main.SIM1PhoneNumber)
        self.remote.srv.call.create(self.settings.Main.SIM1PhoneNumber)
        if self.tryExpect('Incoming call', timeout = 15000):
            self.delay(500)
            self.comment('Swipe to answer call')
            self.swipe((0.5,0.83), (0.5,1.0))
            # Try to hit to the moving 'Swipe down to answer' bar
            while self.tryExpect.text('Incoming call', timeout=1000):
                self.delay(random.randint(200, 500))
                self.swipe((0.5,0.83), (0.5,1.0))
            # TODO: Bug in the phone: sometimes the call can't be answered at all
            self.select.resourceId('com.android.phone:id/endButton')
            self.back()
        else:
            self.fail('Failed to receive call from remote phone')

    def testReceiveSMS(self):
        """

        @tcId Test receive SMS
        """
        mainNumber = self.settings.Main.SIM1PhoneNumber
        assert mainNumber, 'Phone number of SIM1 for the main phone is not defined in settings'

        self.comment('Step 1. Send a message from remote phone to main phone')
        messageContent = str(time.time())
        self.remote.srv.messaging.generateMessage(text=messageContent, recipient=mainNumber, type="sms", state="pending", location="outbox")

        self.comment('Step 2. Wait for the message to be received')
        resp = self.waitForEvent('TYPE_NOTIFICATION_STATE_CHANGED', timeout=20000)

        self.comment('Step 3. Verify that message is found from Messaging')
        self.navigate('Messaging')
        self.expect.text(messageContent)

    def testSendSMS(self):
        """

        @tcId Test send SMS
        """
        pass

