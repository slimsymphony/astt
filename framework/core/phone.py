# -*- coding: utf-8 -*-
"""Marble FW <-> Phone controller module.

   Contains functions for controlling the phone.
"""

import sys, types, time, os, glob, re, clr, shutil, zipfile
from os import path

clr.AddReference('System.Drawing')
clr.AddReference('MarbleLibrary')
clr.AddReference('System.Xml.Linq')
clr.AddReference('System')

import System
from System import DateTime
from System.Drawing import Bitmap
from System.Drawing.Imaging import ImageFormat
from MarbleLibrary.Utilities import ImageComparer

import core
from core import debug, scripting, testresult, decorator
from core.testcase_exceptions import TestException, StopTestException, SkipTestException
from utils.texts import Texts
from interfaces.tab_interface import TestAutomationBridge
from core.touch import Touch
from core.scripting import UIState, Select, Navigate, Expect, Exit, Check, Input, Clear, Back, Read, NotExpect, TryExpect, Kill, DatePicker, TimePicker, \
                           Time, Toggle, Orientation, Volume, Pinch, Swipe, Drag, Flick, DoubleTap, _GestureWrapper, Device, Shell, State, Home, GetItem, GetItems
from utils.nodeutils import NodeUtils

clr.AddReference('TestAutomation.Bridge')
from TestAutomation.Bridge import OutputType

import leader
from leader import step_interval_counter
from core.leader import executeInFollower
from System.Xml.Linq import XDocument, XElement
from System.Collections.Generic import List
from utils.file_utils import filterValidFilename

from System import Diagnostics
from System.Diagnostics import Process
from System import Array, String

class Phone(object):
    def __init__(self, name = ""):

        # set instance name if given
        self._name = name

        # Test Automation Bridge instance
        self._tab = TestAutomationBridge(self)

        self.__captureNameIndex = 0
        self.__productDetails = {}
        self._latestWaitMessage = ''
        self._latestWaitMessageSendTime = 0
        self.referencePhone = None
        self.motionStart = None
        self._createBugReport = False

        self.result = None
        self._initTestStep()
        self.__failureCaptureTaken = False
        self.battery = None
        self.currentTcId = None
        self.__leaderTouchIntervalTimer = 0
        self._capturedStillImages = []
        self._touch = Touch(self)
        self._pickTime = TimePicker(self)
        self._pickDate = DatePicker(self)

        # scripting interfaces
        self.uiState = UIState(self)
        self.select = Select(self)
        self.navigate = Navigate(self)
        self.expect = Expect(self)
        self.notExpect = NotExpect(self)
        self.tryExpect = TryExpect(self)
        self.exit = Exit(self)
        self.input = Input(self)
        self.clear = Clear(self)
        self.back = Back(self)
        self.check = Check(self)
        self.read = Read(self)
        self.time = Time(self)
        self.toggle = Toggle(self)
        self.orientation = Orientation(self)
        self.volume = Volume(self)
        self.reboot = self._tab.reboot
        self.kill = Kill(self)
        self.pinch = Pinch(self)
        self.pinchOut = self.pinch._pinchOut
        self.pinchIn = self.pinch._pinchIn
        self.swipe = Swipe(self)
        self.drag = Drag(self)
        self.flick = Flick(self)
        self.doubleTap = DoubleTap(self)
        self.shell = Shell(self)
        self.device = Device(self)
        self.state = State(self)
        self.waitForEvent = self._tab.waitForEvent
        self.deviceInfo = self._tab.deviceInfo
        self.environmentInfo = self._tab.environmentInfo
        self.home = Home(self)
        self.getItem = GetItem(self)
        self.getItems = GetItems(self)

        # old gesture shortcuts
        self.gesture = _GestureWrapper()
        self.gesture.swipe = self.swipe
        self.gesture.drag = self.drag
        self.gesture.flick = self.flick
        self.gesture.doubleTap = self.doubleTap

        # access to settings
        self.settings = core.FW_conf['settings']

    def _setUp(self):
        """ Setup to be called from MarbleTestCase setUp"""
        if core.FW_conf['should_stop']:
            return

        # create referencephone connection after provisioning settings has been written to the main phone in testcase.py _setUp
        # this is because if POX server is used as reference phone, VoIP SIP proxy will be selected based on the SIM card used in the main phone
        #if self.getName() == 'Main':
        #    self.createReferencePhoneConnection()

        # get and set product information to test report for main phone
        if self.isMain():
            try:
                self.getProductDetails()
            except:
                debug.err('Unable to get product details!')

        if self.isFollower():
            if core.FW_conf['remote_connection'] != None:
                for remote in core.FW_conf['remote_connection']:
                    remote.checkPhoneStatus()

    def _uiSetUp(self, tc):
        """ Setup to be called from UITestCase setUp"""
        if core.FW_conf['should_stop']:
            return

        self.phoneLanguage = 'en_GB' # TODO: remove hardcoded language

        if core.FW_conf['remote_connection'] != None:
            for remote in core.FW_conf['remote_connection']:
                remote.cancelIndications() # Move this to Phone.setup

        if not (self.isFullBlackBox() or self.isFollower() or self.isLeader()):
            # set display orientation to portrait
            self.orientation.setPortrait(doNotReport = True)

            # synch PC time to device if wanted
            if core.FW_conf['settings'].TestRun.SyncPCDateTime:
                self.time.synchPcDateTime()

        # get motion count at startup. run freeze detection if no motion during the test case
        if core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.isMain():
            self.motionStart = core.FW_conf['blackbox'].getCountMotionFrames()

        # if test case setup/teardown has been disabled, warning is printed
        if core.FW_conf['settings'].TestRun.DisableTestCaseSetupAndTeardown:
            self.warn('Exit skipped in setup and teardown!')
        elif not self.isFollower() or self.isFullBlackBox():
            # exit to idle
            self.exit()

    def _tearDown(self, tc):
        """ Teardown to be called from MarbleTestCase _tearDown"""
        pass

    def _uiTearDown(self, tc):
        """ Teardown to be called from UITestCase _tearDown"""
        if core.FW_conf['blackbox'] != None and core.FW_conf['blackbox_enabled']:
            core.FW_conf['blackbox'].videoRecording_SetText('Marble test teardown')

        if self.isLeader():
            self.takeVideoStillImage()
            core.FW_conf['leader'].currentTestStep = 'Marble test teardown'

        self._initTestStep()

        if not core.FW_conf['settings'].TestRun.DisableTestCaseSetupAndTeardown and \
           (not self.isFollower() or self.isFullBlackBox()):
            self.exit()
            # get motion count at startup. run freeze detection if no motion during the test case
            if core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.isMain():
                if self.motionStart != None and core.FW_conf['blackbox'].getCountMotionFrames() == self.motionStart:
                    self.comment('No motion detected during the testcase, detecting freezes..')
                    self.exit._checkUiFreeze()
                elif self.motionStart == None:
                    self.warn('Freeze detection not functional!')

    def isFollower(self):
        """ Returns true if Follower mode is activated """
        if self.getName() == 'Main' and (core.FW_conf['settings'].TestRun.ExecutionMode == 'Follower' or \
           self.isFullBlackBox()): # fullblackbox is treated like follower
            return True
        else:
            return False

    def isFullBlackBox(self):
        """ Returns true if Full Blackbox mode is activated """
        return False

    def isGrayBox(self):
        """ Returns true if phone instance is graybox """
        if self.getName() == 'Main' and core.FW_conf['graybox_enabled'] and core.FW_conf['blackbox_enabled']:
            return True
        else:
            return False

    def isBlackBox(self):
        """ returns true if execution happens in blackbox (not in graybox) """
        if self.getName() == 'Main' and core.FW_conf['blackbox_enabled'] and not self.isGrayBox():
            return True
        else:
            return False

    def isWhiteBox(self):
        """ return True if execution happens in whitebox for current phone """
        if self.getName() != 'Main': # all remotes are whitebox currently
            return True
        elif self.getName() == 'Main' and not core.FW_conf['blackbox_enabled']:
            return True
        else:
            return False

    def setName(self, name):
        """ Method for setting phone name"""
        self._name = name

    def getName(self):
        """ Method for getting phone name"""
        return self._name

    def isMain(self):
        if self.getName() == 'Main':
            return True
        else:
            return False

    def isLeader(self):
        """ Returns true if Leader mode is activated """
        if self.getName() == 'Main' and core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
            return True
        else:
            return False

    def closeConnection(self):
        """ Closes the phone connection """
        # clear dictionary so that product details will be read again
        self.__productDetails = {}
        self._tab._closeConnection(sleepAfterClose = False)

        if self.isFullBlackBox() or self.isFollower():
            self.comment('Disconnecting USB..')
            core.FW_conf['blackbox'].connectUsb('None')

    def createConnection(self, serialNumber = ""):
        """ Create connection to phone

            Parameters

            serialNumber        serial number of the device
        """
        if sys.flags.debug:
            from System.Diagnostics import Debugger
            if not Debugger.IsAttached:
                Debugger.Launch()

        # full blackbox: connect usb for connection creation
        if core.FW_conf['blackbox_enabled'] and self.isMain():
            self.comment('Ensuring default USB connection (%s)' % core.FW_conf['blackbox'].getDefaultUsbAccessoryConnector())
            self._ensureBlackBoxUsbAccessoryConnection()

        # create Test Automation Bridge connection
        try:
            # get serial number from settings
            if serialNumber == "":
                serialNumber = core.FW_conf['settings'].Main.Connection

            # if serial number is not given, raise exception
            assert serialNumber, 'No serial number found for creating connection to device!'

            #self._tab._createConnection(serialNumber = '0123456789ABCDEF')
            #self._tab._createConnection(serialNumber = '35359577CE9700EC')
            #self._tab._createConnection(serialNumber = 'a3c660ec')
            #self._tab._createConnection(serialNumber = 'emulator-5556')
            #self._tab._createConnection(self._tab.HW) # --> to first available hw device
            #self._tab._createConnection(self._tab.HW, serverLevelInUse = False) # --> to first available hw device without server level
            #self._tab._createConnection(self._tab.EMULATOR) # --> to first available emulator device
            if self.isFollower() or (self.isFullBlackBox() and core.FW_conf['blackbox_enabled']):
                self._tab._createConnection(serialNumber = serialNumber, serverLevelInUse = False) # --> to first available device
            else:
                #self._tab._createConnection(serialNumber = '0123456789ABCDEF')
                #self._tab._createConnection(serialNumber = '35359577CE9700EC')
                #self._tab._createConnection(serialNumber = 'a3c660ec')
                #self._tab._createConnection(serialNumber = 'emulator-5556')

                #self._tab._createConnection(self._tab.HW) # --> to first available hw device
                #self._tab._createConnection(self._tab.HW, serverLevelInUse = False) # --> to first available hw device without server level
                #self._tab._createConnection(self._tab.EMULATOR) # --> to first available emulator device
                #self._tab._createConnection() # --> to first available device
                self._tab._createConnection(serialNumber = serialNumber) # --> to wanted device

                # get accesses to sql, media, packages and file functionalities
                # FIXME: Find a way to renew these accesses if it's disconnected/connected
                self.sql = self._tab._sqlLite
                self.media = self._tab._mediaPlayer
                self.file = self._tab._file
                self.packages = self._tab._packageManager

            if self.isBlackBox() and False:
                debug.brf('Set disallowed binders')
                self._tab._setDisallowedBinderNames()
            else:
                self._tab._tabConn.DisAllowedBinderNames.Clear()

            decorator.checkConfigurations(self)

        except Exception as e:
            if self.isFullBlackBox():
                self.comment('Connection creation failed in full blackbox mode: %s' % e.message)
            else:
                raise e

    def resetPhone(self, errorReason = '', waitBeforeReset = False):
        """Reset phone (whitebox) or disconnect/connect power (blackbox) in order to recover from invalid phone state.
           Test case will be failed or exception will be raised (result == NO RESULT) depending on the situation.

            Parameters

            errorReason         error reason string
            waitBeforeReset     boolean, wait before resetting the phone to be sure that dumps are not being generated
        """
        # if test execution has been aborted, reset phone will not be performed
        if core.FW_conf['should_stop']:
            return

        if not core.FW_conf['settings'].TestRun.AllowPhoneReset:
            message = self.getName()
            if self.isFollower() and not self.isFullBlackBox():
                message += ' phone power reset is needed but reset is not allowed in Follower. Exit.'
                self.warn(message)
                sys.exit()
            else:
                message += ' phone reset is needed but reset is not allowed. Execution is on hold'
                core.FW_conf['mail_sender'].holdExecutionAndSendMail(message, subject = core.FW_conf['settings'].TestRun.StationDescription + ' Marble execution paused')
            return

        if self.isBlackBox() or self.isGrayBox():
            if waitBeforeReset:
                self._waitBeforeReset()

            if core.FW_conf['settings'].TestRun.UseLongHWPressToReset:
                pressLen = core.FW_conf['settings'].TestRun.LongHWPressToResetPhoneLength
                dumpCheckOk = False
                try:
                    self.select.long('KEYCODE_POWER', length=pressLen)
                    errorReason += '\nMarble pressed long KEYCODE_POWER to reset phone!'
                    dumpCheckOk = self.checkQCRamdumps(True)[0] # freeze=True so check will wait for UI movement
                except:
                    errorReason += '\nresetPhone: Failed to press long KEYCODE_POWER to force ram dump in %s mode' % (self.isFullBlackBox() and 'full blackbox' or core.FW_conf['blackbox_enabled'] and 'blackbox' or 'whitebox')
                    self.comment(errorReason)
            else:
                errorReason += '\nMarble had to disconnect and connect the power in order to recover from the situation!'
                self._blackBoxResetPhonePower()

            self.fail(errorReason, crashOrReset = True)
        elif self.isFollower() and not self.isFullBlackBox():
            errorReason += '\nReset requested but in Follower mode, cannot do sw reset!'
            debug.err(errorReason)
        else:
            if waitBeforeReset:
                self._waitBeforeReset()
            errorReason += '\nMarble had to reboot the phone in order to recover from the situation!'
            self._tab.reboot()
            self.fail(errorReason, crashOrReset = True)

        raise Exception(errorReason)

    def __isProcessRunning(self, name):
        """ check whether there's process running with certain name """
        pname = Process.GetProcessesByName(name)
        if (pname.Length == 0):
            return False
        return True

    def _waitBeforeReset(self):
        """ wait before resetting the phone
            timeout will be determined by ram dump fetching method. If connection can be created, waiting will be stopped
        """
        if core.FW_conf['ramdump_method'] == "USB":
            timeout = 60
        else:
            timeout = 360 # if ram dump method is unknown or SD card, wait at least 6 minutes

        # check that connection is ok. if the connection cannot be established, the device might be in download mode.
        checkStart = time.time()
        printInfo = True
        while (time.time() < checkStart + timeout):
            connected, ready = self._tab._isConnectedAndReady()

            if connected:
                break

            else:  # if not connected, continue looping. RAM dumps should get copied during this time
                self._tab._waitForDeviceOnline(timeout = 60)
                if printInfo:
                    self.comment('Waiting for device to get online before reset (timeout %s)..' % str(timeout))
                    printInfo = False
                self.sendWaitMessageToMarbleGUI(1, 'Waiting tab connection for %s second' % 1)
                self.delay(1000, False)

    def _getCrashDumps(self):
        """Get crash dumps from the phone. Test case will be failed or warning will be thrown according to settings.
           Return
                []    :    list of serious dumps found, including QC dumps
        """
        qcDumps = self.checkQCRamdumps()[2]
        crashDumpDir = os.path.join(core.FW_conf['test_result_dir'], 'crash_dumps', filterValidFilename(core.FW_conf['connection'].currentTcId))

        currentCrashDumps = []
        seriousCrashDumps = []
        notSoFatalCrashDumps = []

        if os.path.isdir(crashDumpDir):
            for directory, folders, files in os.walk(crashDumpDir):
                for crashDumpFile in files:
                    # anr/traces.txt file is an exception
                    if directory != 'anr' and crashDumpFile != 'traces.txt':
                        currentCrashDumps.append(crashDumpFile)

        # get crash dumps with tab NOTE: if dump fetching changes, CHANGE also blackbox dump fetching!
        # NOTE: getCrashDumps method is responsible for creating the crash dump directory, but checking it here just in case
        success, crashDumpsFound = self._tab._executeTabOperation(\
            self._tab.getCrashDumps, crashDumpDir, deleteFiles = core.FW_conf['settings'].TestRun.DeleteCrashDumpsFromDevice)

        if (success and crashDumpsFound) and os.path.isdir(crashDumpDir):
            if core.FW_conf['settings'].TestRun.FailTestIfCrashDumpsFound:
                # get serious and not so fatal crash dump files

                # evaluate setting
                try:
                    doNotFailToThese = [x.strip() for x in core.FW_conf['settings'].TestRun.NotSoFatalCrashDumps.split(',')]
                except Exception:
                    debug.err("Unable to evaluate 'do not fail to these crash dumps' - setting. Please check setting content: %s" % str(core.FW_conf['settings'].TestRun.NotSoFatalCrashDumps))
                    doNotFailToThese = []

                # loop through new crash dumps and determine severity according to setting
                for directory, folders, files in os.walk(crashDumpDir):
                    for crashDump in files:
                        if not crashDump in currentCrashDumps:
                            # get package name from crash dump
                            success, packageName = self._tab._executeTabOperation(\
                                self._tab._tabConn.GetPackageFromCrashDump, os.path.join(directory, crashDump))

                            crashDumpWithPath = os.path.join(os.path.split(directory)[-1], crashDump)
                            # append package name if found
                            if success and packageName:
                                crashDumpWithPath += ', Package: %s' % packageName

                            for doNotFailToThis in doNotFailToThese:
                                if doNotFailToThis in crashDump:
                                    notSoFatalCrashDumps.append(crashDumpWithPath)
                                    break

                            if not crashDumpWithPath in notSoFatalCrashDumps:
                                seriousCrashDumps.append(crashDumpWithPath)

                if notSoFatalCrashDumps:
                    self.warn('Not so fatal crash dumps found: %s' % '\n'.join(notSoFatalCrashDumps))

                if seriousCrashDumps and self.isMain():
                    self.result.addFailure('Crash dumps found: %s' % '\n'.join(seriousCrashDumps), crashOrReset = True)
                elif seriousCrashDumps:
                    self.warn('Not so fatal crash dumps found: %s' % '\n'.join(notSoFatalCrashDumps))
            else:
                newCrashDumps = []

                for directory, folders, files in os.walk(crashDumpDir):
                    for crashDump in files:
                        if not crashDump in currentCrashDumps:
                            newCrashDumps.append(os.path.join(os.path.split(directory)[-1], crashDump))

                self.warn('Crash dumps found: %s' % '\n'.join(newCrashDumps))

        if seriousCrashDumps and not qcDumps and core.FW_conf['settings'].TestRun.CreateBugReportOnFailure:
            self._createBugReport = True
        else:
            self._createBugReport = False

        seriousCrashDumps.extend(qcDumps)
        return seriousCrashDumps

    def _getCrashDumpsInBlackBox(self, getAllDumps=False):
        """ If defined amount of cases have been executed, connect USB cable and get the dump files
            Params:
                getAllDumps     :      if False, only new dump files are fetched
            Return:
                None, []            :      Dump fetching is disabled from settings or Interval limit has not been reached (dumps not fetched)
                -1, []              :      No connection could be made for fetching dump files
                1, []               :      Found dumps, list of dumps

        """

        foundDumps = []

        if not core.FW_conf['crash_fetch_interval']:
            core.FW_conf['crash_fetch_interval'] = int(core.FW_conf['settings'].TestRun.DumpFileFetchInterval)

        if int(core.FW_conf['settings'].TestRun.DumpFileFetchInterval) == 0:
            self.comment('Crash dump fetching has been disabled from settings')
            core.FW_conf['crash_fetch_interval'] = None
            return None, foundDumps

        # check interval
        if core.FW_conf['crash_fetch_interval'] <= 1 or getAllDumps:
            core.FW_conf['crash_fetch_interval'] = int(core.FW_conf['settings'].TestRun.DumpFileFetchInterval)

            self.comment('Fetching crash files in full blackbox mode..')

            # create connection (connects USB)
            core.FW_conf['connection'].createConnection()

            # get dumps
            dumpsFetched = False
            retrys = 3
            for i in range(retrys):
                try:
                    foundDumps = self._getCrashDumps()
                    dumpsFetched = True

                except Exception as e:
                    debug.err('Could not create connection for fetching crash files: %s' % e.message)
                    if i <= retrys - 1:
                        # disconnect and re-connect (USB also)
                        self.closeConnection()
                        self.delay(1000)
                        debug.brf('Trying re-creating connection for crash dump fetching..')
                        self.createConnection()
                if dumpsFetched:
                    break

            # close connection and disconnect USB
            if self.isFullBlackBox() or self.isFollower():
                self.closeConnection()

            if not dumpsFetched:
                core.FW_conf['connection'].result.addFailure('Could not create connection for fetching crash dumps')
                return -1, foundDumps

            if len(foundDumps):
                return 1, foundDumps
            else:
                return 0, foundDumps

        else:
            core.FW_conf['crash_fetch_interval'] -= 1
            msg = 'Crash files will be checked after next case' if core.FW_conf['crash_fetch_interval'] <= 1 else 'Crash file check will be done after execution of %s cases' % str(core.FW_conf['crash_fetch_interval'])
            self.comment(msg)
            return None, foundDumps

    def checkQCRamdumps(self, freezed=False):
        """ check from user definable location whether QC ram dumps exist
            Params
                freezed(bool)  :   If called from checkUiFreeze, blackbox mode will wait default timeout for movement
            Returns
                False, False, []   :   Unable to fetch ram dump
                True, False, []    :   Dumps fetched and no failures
                True, True, []     :   Dumps fetched and failures added to report, list of dumps
        """

        foundDumps = []

        if not self.isMain():
            return False, False, foundDumps

        if core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.isMain():
            motionCountStart = core.FW_conf['blackbox'].getCountMotionFrames()

        if core.FW_conf['blackbox_enabled'] and self.isMain(): # if blackbox execution, make sure that USB is connected
            usb = core.FW_conf['blackbox'].getCurrentUsbAccessoryConnector()
            if usb != core.FW_conf['blackbox'].getDefaultUsbAccessoryConnector():
                core.FW_conf['blackbox'].connectDefaultAccessoryUsb()

        try: # re-check ramdump method each time called
            if self._tab._tabConn.File.FileExists(os.path.join(self.file.sdCard,'rdcookie.txt')):
                core.FW_conf['ramdump_method'] = "SDCARD"
            else:
                core.FW_conf['ramdump_method'] = "USB"
        except:
            pass

        # if QPSTConfig is not running while USB is the fetch method, return to save timeout time
        if core.FW_conf['initial_crash_fetch_done'] and core.FW_conf['ramdump_method'] == "USB":
            if (not self.__isProcessRunning("QPSTConfig")):
                debug.err('To enable RAM dump fetching, launch QPST Configurator or create file rdcookie.txt to memory card root')
                return False, False, foundDumps

        if core.FW_conf['ramdump_method'] == "USB":
            timeout = 60
        else:
            timeout = 360 # if ram dump method is unknown, wait at least 6 minutes for connection to be created. dumping to sdcard might take even this long

        connected = False
        printInfo = True

        if freezed and core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.isMain():
            for i in range(timeout):
                if core.FW_conf['blackbox'].getCountMotionFrames() == motionCountStart:
                    if printInfo:
                        self.comment('Waiting %s seconds for UI movement to get RAM dumps..' % str(timeout))
                        printInfo = False
                    self.sendWaitMessageToMarbleGUI(1, 'Waiting %s seconds for UI movement to get RAM dumps' % 1)
                    self.delay(1000, False)
                else:
                    break # movement detected -> release waiting

        # check that connection is ok. if the connection cannot be established, the device might be in download mode.
        checkStart = time.time()

        while (time.time() < checkStart + timeout):
            connected, ready = self._tab._isConnectedAndReady()

            if connected:
                if not core.FW_conf['initial_crash_fetch_done']: # if we yet don't know the crash fetch method, check it
                    try:
                        if self.file.fileExists(os.path.join(self.file.sdCard,'rdcookie.txt')):
                            core.FW_conf['ramdump_method'] = "SDCARD"

                            success, ramDumpCount = self._tab._executeTabOperation(self._tab.CheckRamDumps, True,
                                core.FW_conf['settings'].TestRun.DeleteRawRamDumpsFromDevice,
                                core.FW_conf['settings'].TestRun.CopyRawRamDumpsFromDevice)

                            if success:
                                if ramDumpCount > 0:
                                    warning = "RAM dumps found from SD card on initial fetch"
                                    self.warn(warning)
                            else:
                                self.warn("Could not perform initial ram dump check!")
                        else:
                            core.FW_conf['ramdump_method'] = "USB"
                        debug.brf('RAM dumps fetching method: %s' % core.FW_conf['ramdump_method'])
                        core.FW_conf['initial_crash_fetch_done'] = True
                    except:
                        debug.err('Could not check the RAM dumping method (SDCARD/USB)')
                break

            else:  # if not connected, continue looping. RAM dumps should get copied during this time
                # recreate connection to device again if necessary
                self._tab._waitForDeviceOnline(timeout = 60)

                if printInfo:
                    self.comment('Waiting %s seconds for device to get RAM dumps..' % str(timeout))
                    printInfo = False
                self.sendWaitMessageToMarbleGUI(1, 'Waiting tab connection for %s second' % 1)
                self.delay(1000, False)

        failMsg = ""

        if core.FW_conf['ramdump_method'] == "SDCARD":
            if not connected:
                debug.err('Could not create connection to device for RAM dump fetching from SD Card')
            else:
                success, ramDumpCount = self._tab._executeTabOperation(self._tab.CheckRamDumps, False,
                    core.FW_conf['settings'].TestRun.DeleteRawRamDumpsFromDevice,
                    core.FW_conf['settings'].TestRun.CopyRawRamDumpsFromDevice)

                if success:
                    if ramDumpCount > 0:
                        failMsg = 'New RAM dumps found from SDCARD '
                        infoMsg = 'Copying RAM dumps from SDCARD to PC...'
                        debug.brf(infoMsg)
                        # reserve 10 minutes for each RAM dump
                        self.sendWaitMessageToMarbleGUI(600 * ramDumpCount, infoMsg)

                        success, response = self._tab._executeTabOperation(\
                            self._tab.GetNewRamDumps,
                            os.path.join(core.FW_conf['test_result_dir'], 'crash_dumps', filterValidFilename(core.FW_conf['connection'].currentTcId), 'ram'),
                            core.FW_conf['settings'].TestRun.DeleteCrashDumpsFromDevice)

                        if success and response:
                            foundDumps.append('New RAM dumps found from %s' % os.path.join(core.FW_conf['test_result_dir'], 'crash_dumps', filterValidFilename(core.FW_conf['connection'].currentTcId), 'ram'))
                        else:
                            self.warn("Could not get new ram dumps!")
                else:
                    self.warn("Could not check ram dumps!")

        if (core.FW_conf['ramdump_method'] == "USB" and not self.__isProcessRunning("QPSTConfig")):
            debug.err('QPST not running, cannot get RAM dumps via USB connection !')

        # even SDCARD is the method, QPST can still fetch dumps / release Sahara Download mode. This block will report dumps found from PC
        elif self.__isProcessRunning("QPSTConfig"):
            # fetch ram dumps from directory in PC file system
            p = os.path.abspath(core.FW_conf['settings'].TestRun.QCRamDumpPath)
            port = core.FW_conf['settings'].TestRun.QCRamDumpPort
            if len(Process.GetProcessesByName('Marble')) > 1:
                if not port:
                    self.warn('Multiple Marble running and no QPST COM port defined in settings! Check that found dump is from correct phone!')

            if os.path.exists(p):
                for path, dirs, files in os.walk(p):
                    if len(dirs): # there's dump directories under ram dump folder
                        self.sendWaitMessageToMarbleGUI(10, 'Copying ram dumps, timeout %s second' % 10)
                        ready = False
                        for i in range(15): # wait for last file to appear in QPST folder (currently any found load.cmm will release)
                            for path, dirs, files in os.walk(p):
                                if 'load.cmm' in files:
                                    ready = True
                                    break
                                else:
                                    self.delay(1000, False)
                            if ready:
                                break

                for path, dirs, files in os.walk(p):
                    for d in dirs:

                        # port defined and directory does not end with port name, continue to next
                        if port and d[-len(port):].lower() != port.lower():
                            continue

                        out_folder = os.path.join(core.FW_conf['test_result_dir'], 'crash_dumps', filterValidFilename(core.FW_conf['connection'].currentTcId))
                        if not os.path.exists(out_folder):
                            try:
                                os.makedirs(out_folder)
                            except Exception as e:
                                debug.err('Could not create directory for RAM dump: %s' % e.message)

                        # new_folder = os.path.join(core.FW_conf['test_result_dir'], 'crash_dumps', DateTime.Now.ToString("yyyyMMddHHmmss") + '_' + d + '_' + filterValidFilename(core.FW_conf['connection'].currentTcId))
                        dumpFolderName = DateTime.Now.ToString("yyyyMMddHHmmss") + '_' + d
                        failMsg += 'Ramdump generated during testcase execution (%s)' % dumpFolderName
                        self.sendWaitMessageToMarbleGUI(10, 'Copying ram dumps, timeout %s second' % 10)
                        foundDumps.append(dumpFolderName)
                        try:
                            shutil.move(os.path.join(p, d), os.path.join(out_folder, dumpFolderName) )
                        except Exception as e:
                            debug.err('Could not move ram dumps to result folder: %s' % e.message)
                            failMsg += ' ERROR: Could not move ram dumps to result folder: %s' % e.message

        if failMsg != "":
            self.result.addFailure(failMsg)

        if core.FW_conf['ramdump_method'] == "SDCARD" and not connected: # could not fetch dump from SDCard due to connection error
            return False, False, foundDumps
        elif core.FW_conf['ramdump_method'] == "USB" and not self.__isProcessRunning("QPSTConfig"):
            return False, False, foundDumps

        if failMsg != "":
            # restart logging without clearing buffers
            self._tab._stopLogging(clearBuffer = False)
            self._tab._startLogging(clearBuffer = False)

            return True, True, foundDumps

        return True, False, foundDumps

    def createBugReport(self, path=None):

        """ creates bug report from phone """

        self.comment('createBugReport()')

        if not path:
            path = os.path.join(core.FW_conf['test_result_dir'], 'bug_reports_%s' % self.getName())
            if not os.path.isdir(path):
                os.makedirs(path)

        filename = os.path.splitext(core.FW_conf['test_result_name'])[0]

        try:
            self.sendWaitMessageToMarbleGUI(60, 'creating bugreport')
            savedfile = self._tab._tabConn.BugReport.SaveAs(os.path.join(path, filename), OutputType.ZippedHtml)
            absPath = os.path.abspath(savedfile)
            self.comment('Bug report saved to %s' % absPath)

            reportNode = NodeUtils('bug_report', True)
            relativePath = os.path.split(os.path.split(absPath)[0])[1]
            filename = os.path.basename(os.path.normpath(absPath))
            reportNode.setAttribute('path', os.path.join(relativePath, filename))
            self.result.addBlock(reportNode)

        except Exception as e:
            debug.err('Failed to create bugreport: %s' % e.message)

    def takeHeapDumps(self, processList = []):
        """Takes heap dump(s) from processes.

            Parameters

            processList         list of process names from which heap dumps are taken
                                NOTE: Overrides TestRun.HeapDumpProcesses setting values
        """
        assert type(processList) == types.ListType, \
            'processList parameter must be list!'

        destinationDir = os.path.join(core.FW_conf['test_result_dir'], 'heap_dumps')
        if not os.path.isdir(destinationDir):
            os.makedirs(destinationDir)

        commentString = 'Taking heap dumps from device...'
        self.comment(commentString)

        if len(processList) == 0:
            # evaluate setting
            try:
                for value in core.FW_conf['settings'].TestRun.HeapDumpProcesses.split(','):
                    processName = value.strip()
                    if processName:
                        processList.append(processName)
            except Exception:
                self.warn("Unable to evaluate 'list of heap dump process names' - setting. Please check setting content: %s" % str(core.FW_conf['settings'].TestRun.HeapDumpProcesses))

        # tell GUI that we are taking heap dumps
        self.sendWaitMessageToMarbleGUI((len(processList) == 0 and 10 or len(processList)) * 60, commentString)

        # take heap dump(s)
        success, succeeded = self._tab._executeTabOperation(self._tab.GetHeapDumps, Array[String](processList), destinationDir)

        if not success or not succeeded:
            self.warn('Taking heap dumps failed!')

    def _ensureBlackBoxUsbAccessoryConnection(self):
        """Ensure that when running on BlackBox mode, default USB connector is always connected.
            A try-catch clause is preferred due to there might be no USBAccessoryCard to execute this operation in some cases.

            Returns True if USB accessory connector has been changed from E.g. None to Usb1,
            False, if no connector change.
        """
        if core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox_enabled'] and self.isMain():
            result = False

            try:
                result = core.FW_conf['blackbox'].connectDefaultAccessoryUsb()
            except Exception, ex:
                debug.err('Phone._ensureBlackBoxUsbAccessoryConnection: %s' %str(ex))

            if result == True:
                # Accessory connector changed: Wait a while for windows to detect the connection
                time.sleep(5)

            return result

    def _blackBoxResetPhonePower(self):

        if not self.isMain():
            debug.err('Blackbox reset is supported only in Main connection')
            return

        if not core.FW_conf['settings'].TestRun.AllowPhoneReset:
            message = self.getName()
            if self.isFollower():
                message += ' phone power reset is needed but reset is not allowed in Follower'
            else:
                message += ' phone reset is needed but reset is not allowed. Execution is on hold'
            core.FW_conf['mail_sender'].holdExecutionAndSendMail(message, subject='MARBLE EXECUTION ON HOLD')
            return

        # if reset in follower mode, do not create connection, just reset
        if core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox_enabled'] and self.isFollower():
            self.comment('BlackBox: Reset phone power in follower mode...')
            self.sendWaitMessageToMarbleGUI(300, 'Resetting phone power')
            core.FW_conf['blackbox'].resetPhonePower()

        #If running on BlackBox: disconnect / reconnect phone power to fully reset the connection
        elif core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox_enabled']:
            self.comment('BlackBox: Reset phone power...')
            try:
                timeout = int(core.FW_conf['settings'].System.PhoneReset)
                self.sendWaitMessageToMarbleGUI(int(timeout), 'Resetting phone power')
                if not (self.isFullBlackBox() or self.isFollower()):
                    self.closeConnection()
                    core.FW_conf['blackbox'].resetPhonePower()
                    self.comment('Sleeping %s seconds after phone reset' % str(timeout))
                    self.delay(timeout * 1000)
                    self.createConnection()
                else:
                    core.FW_conf['blackbox'].resetPhonePower()
                    self.comment('Sleeping %s seconds after phone reset' % str(timeout))
                    self.delay(timeout * 1000)

            except Exception, ex:
                debug.err('Phone._blackBoxResetPhonePower: %s' %str(ex))

    def _blackBoxResetPhoneUsbConnection(self, createConnection = True):
        """Resets USB connection with blackbox

            Parameters

            createConnection            whether connection is created after usb connection reset
        """
        ret = False
        #If running on BlackBox: disconnect / reconnect phone USB connection and reconnect phone if needed
        if core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox_enabled'] and self.isMain():
            try:
                self.sendWaitMessageToMarbleGUI(60, 'Resetting phone USB')
                core.FW_conf['blackbox'].connectUsb('None')

                # Wait 5 seconds after USB disconnected
                time.sleep(5)

                if createConnection:
                    self.createConnection() # connects the usb in blackbox mode

                    ret = self._tab.isConnected()

            except Exception, ex:
                debug.err('Phone.__blackBoxResetPhoneUsbConnection: %s' %str(ex))
        return ret

    def _setResult(self, result):
        """ Set result instance for phone. Result is needed for adding comments to report

        """
        if result == None:
            del self.result
        self.result = result

    def getResult(self):
        """ Get always Main(1) phone's result instance """
        return core.FW_conf['connection'].result

    def _clearStillImageArray(self):
        """ Clears the image array of video stream images. Called when test case is stopped. """
        self._capturedStillImages = []

    def capture(self, name=None, savePath=None, onlyImage=False):
        """ Take screen capture from phone

        Parameters:
            name        :   Name of the test step in test report
            savePath    :   Path where bitmap will be copied
                            Can be either full path or name only
            onlyImage   :   Set to True if xml-dump is not needed

        """
        if name == 'capture from failure':
            self.comment('capture() from failure')
        else:
            self.comment('capture()')

        if savePath:
            if os.path.dirname(savePath) and os.path.basename(savePath):
                imagePath = savePath
            else:
                imagePath = os.path.normpath(os.path.join(core.FW_conf['test_result_dir'], 'captured bitmaps', savePath))

            self.comment('Saving image to %s' % imagePath)
        else:
            self.__captureNameIndex += 1

            imagePath = os.path.normpath(os.path.join(core.FW_conf['test_result_dir'],
                                     'captured bitmaps',
                                     "capture_%s%s_%s.png" % \
                                     ((self.getName() != 'Main' and (self.getName() + '_') or ''),
                                      (core.FW_conf['connection'].currentTcId != None and filterValidFilename(core.FW_conf['connection'].currentTcId) or ''), str(self.__captureNameIndex))))

        # FIXME: Figure out how to make difference for capture and error bitmap names
        if self.isFullBlackBox():
            if not core.FW_conf['blackbox'].isVideoRecorderAvailable():
                debug.err('Video recorder is not available in Full Blackbox mode')
            assert core.FW_conf['blackbox'].isVideoRecorderAvailable(), "Video recorder is not available in Full Blackbox mode"
            core.FW_conf['blackbox'].takePicture(imagePath)
            return imagePath
        else:
            if name == 'capture from failure':
                return self._tab.capture(imagePath, onlyImage = onlyImage, useExistingDump=True)
            else:
                return self._tab.capture(imagePath, onlyImage = onlyImage)

    def comment(self, comment):
        """Add comment to the test result.

        FIXME: Replace 'comment' attribute with '*comments'
        """

        if not isinstance(comment, basestring):
            comment = str(comment)

        # Main phone comment
        if self.isLeader():
            executeInFollower("self.comment('%s')" % comment)

        if '(' in comment:
            # write test step name to bltue report if necessary
            self.addBltueTestStep(comment)

            # set test step name marker using TAB
            self._tab._addLogMarker('TEST STEP: %s' % comment)

            if self.result:
                # add current test step for performance measuring
                self.result.setCurrentTestStep(comment)

            # provide test step to video recording in MTBF leader mode
            if self.isLeader() and core.FW_conf['blackbox'] != None \
               and core.FW_conf['current_testcase'] != None:
                global step_interval_counter
                core.FW_conf['leader'].currentTestStep = comment
                interval = core.FW_conf['settings'].TestRun.VideoStillImageCaptureInterval
                if interval > 0:
                    step_interval_counter = step_interval_counter % interval
                    if step_interval_counter == 0:
                        tempstep = core.FW_conf['leader'].currentTestStep
                        core.FW_conf['current_testcase'].takeVideoStillImage()
                        core.FW_conf['leader'].currentTestStep = tempstep
                        step_interval_counter = 1
                    else:
                        step_interval_counter += 1

        if self.getName() != 'Main':
            comment = self.getName() + ': ' + comment

        debug.brf(comment)

        if core.FW_conf['blackbox'] != None and core.FW_conf['blackbox'].isVideoRecorderAvailable():
            core.FW_conf['blackbox'].videoRecording_SetText(comment)

        if self.result:
            comment = [comment]
            # FIXME: Remove list approach from addStepComment
            self.result.addStepComment(comment)

    def _initTestStep(self):
        """Initialize new test step."""
        self.keyPresses = []

    def __purgeKeyPresses(self):
        """Generate key_in-block with required keypress-elements."""
        if self.keyPresses:

            if self.isBlackBox() or self.isGrayBox():
                bbPresses = []

            if self.isLeader():
                followerPresses = List[XElement]()

            try:
                key_in = NodeUtils('key_in', makeNewNode = True)

                for keypress in self.keyPresses:

                    # execute power key via bb in graybox mode
                    if self.isGrayBox() and keypress.getAttribute('key') == 'KEYCODE_POWER' and core.FW_conf['settings'].System.HWAssistedPowerKey == True:
                        bbPresses.append(keypress)
                    else:
                        if self.isBlackBox():
                            bbPresses.append(keypress)
                        elif 'Main' in self.getName():
                            # execute touch action with tab
                            self._tab._controlAction(keypress)
                        else:
                            key_in.append(keypress)

                    if self.isLeader() and core.FW_conf['leader'].sendTouches:
                        doc = XDocument.Parse(keypress.toxml())
                        xelement = doc.Root
                        followerPresses.Add(xelement)

                if self.isBlackBox() or self.isGrayBox():
                    if len(bbPresses) > 0:
                        # for sending the delay to followers. counter must be here since it needs to be reseted even touches are not sent
                        if self.isLeader():
                            if self.__leaderTouchIntervalTimer != 0:
                                interval = time.time() - self.__leaderTouchIntervalTimer
                            else:
                                interval = 0
                            self.__leaderTouchIntervalTimer = time.time()

                            if len(followerPresses) > 0:
                                core.FW_conf['leader'].TouchEvent(followerPresses, interval)

                        try:
                            # wait for UI events if we are not in full blackbox mode
                            if not self.isFullBlackBox():
                                self._tab._startUIEventThread()

                            # raise a warning if phone powered down, or touch coordinates has not been read properly
                            pressState = core.FW_conf['blackbox'].pressEvent(bbPresses)
                            if pressState[0] != 'Normal':
                                self.warn(pressState[1])
                        finally:
                            if not self.isFullBlackBox():
                                self._tab._joinUIEventThread()
                                self._tab._stopUIEventThread()

                elif 'Main' in self.getName():
                    # touch action executed with tab, just return
                    return
                else:
                    self.teststep.append(key_in)
                    if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader' and self.getName() != "Main": # if executing steps in Leader mode for remote, leader touch interval counter can be reseted
                        self.__leaderTouchIntervalTimer = time.time()

            finally:
                self.keyPresses = []

    def delay(self, delayInMS, testStepReporting = True, disconnectUsb = False):
        """Stop test step execution for given time (milliseconds).

            Parameters

            delayInMS               delay time in milliseconds
            testStepReporting       whether delay is put to test report (default = True)
            disconnectUsb           disconnect USB with blackbox (default = False)
        """
        assert type(delayInMS) == types.IntType, \
            'parameter for delay must be integer!'

        if testStepReporting:
            self.comment('delay(%s)' % delayInMS)

            # send delay to follower only when reporting is true
            if self.isLeader():
                core.FW_conf['leader'].ExecuteString('self.delay(%s)' % delayInMS)

        if delayInMS < 1000:
            sleepInSeconds = float(delayInMS) / 1000
        else:
            sleepInSeconds = delayInMS / 1000

        self.sendWaitMessageToMarbleGUI(sleepInSeconds, 'Test execution sleeping for %s seconds' % sleepInSeconds)

        if disconnectUsb:
            assert self.isMain(), 'USB disconnection is available only for Main connection'
            assert core.FW_conf['blackbox_enabled'], 'No blackbox available for disconnecting usb!'

            # set marker for usb disconnect
            self._tab._addLogMarker('USB WILL BE DISCONNECTED INTENTIONALLY')

            # stop logging and clear buffers
            self._tab._stopLogging(clearBuffer = True)

            # close connection and disconnect services
            self._tab._closeConnection(disconnectServices = True)

            # disconnect usb
            self.comment('Disconnecting USB...')
            self._blackBoxResetPhoneUsbConnection(createConnection = False)

            self.comment('Sleeping for given time...')
            # sleep for given time
            time.sleep(sleepInSeconds)

            # connect usb
            self.comment('Reconnecting USB...')
            self._ensureBlackBoxUsbAccessoryConnection()

            # create connection
            self._tab._createConnection(serialNumber = self._tab._serialNumber, serverLevelInUse = self._tab.serverLevelInUse)

            # check crash dumps
            core.FW_conf['current_testcase'].getCrashDumps()

            # start logging without clearing buffers
            self._tab._startLogging(clearBuffer = False)
            self._tab._addLogMarker('USB RECONNECTED INTENTIONALLY')

            # ensure server connection
            self._tab._connectServer()
        else:
            time.sleep(sleepInSeconds)

    def compareImage(self, expectedImage, maxDifference=2.0, timeout=None):
        """ Compare current display to image or series of images created with
            Display Image Comparer activity

            parameters:
                expectedImage   :   name of the image or series of images expected to be on the screen.
                                    File extension is not needed. Path to image location can be given.
                                    Default location is reference_files\images-folder.
                maxDifference   :   Maximum difference allowed in comparison. CURRENTLY NOT IN USE!
                timeout         :   Time in milliseconds to wait for correct screen before test is failed.

        """

        if timeout==None:
            timeout=core.FW_conf['settings'].System.ExpectTimeout

        referenceImagesPath, refImageName = os.path.split(expectedImage)
        expectedImageName = os.path.splitext(refImageName)[0]
        reRefImageName = re.compile('%s\.png|%s~\d+\.png'%(expectedImageName,expectedImageName))
        differenceImage = None
        difference = clr.Reference[System.Double](0)

        if not referenceImagesPath:
            referenceImagesPath = os.path.abspath(os.path.join(core.FW_conf['startup_path'], '..','reference_files','images'))
        else:
            referenceImagesPath = os.path.abspath(referenceImagesPath)

        referenceImagesList = [image for image in glob.glob(referenceImagesPath+'/*.png') if reRefImageName.search(image)]

        if len(referenceImagesList)==0:
            self.comment("Reference image '%s' was not found from '%s'" % (expectedImageName,referenceImagesPath))
            self.fail("Reference image was not found.")

        resultCompared = False
        startTime = time.time()
        shouldStop = False

        while not resultCompared and not shouldStop:
            #Make comparison
            capturedImagePath = self.capture(onlyImage=True)
            with Bitmap(capturedImagePath) as actualImage:
                indexCompared = 0

                for expectedImageName in referenceImagesList:
                    debug.out(expectedImageName)
                    tempDifferenceImage = clr.Reference[Bitmap]()
                    tempDifference = clr.Reference[System.Double](0)
                    with Bitmap(expectedImageName) as expectedImageBitmap:
                        result = ImageComparer.Compare(actualImage, expectedImageBitmap, tempDifferenceImage, tempDifference)

                    debug.out("differenceImage: %s"%tempDifferenceImage)
                    debug.out("difference: %s"%tempDifference)
                    if result:
                        indexCompared = referenceImagesList.index(expectedImageName)
                        resultCompared = True
                        if differenceImage != None:
                            differenceImage.Dispose()
                            differenceImage = None

                        differenceImage = tempDifferenceImage
                        break
                    else:
                        # using the closer match
                        if tempDifference < maxDifference:
                            maxDifference = tempDifference
                            indexCompared = referenceImagesList.index(expectedImageName)
                            if differenceImage != None:
                                differenceImage.Dispose()
                                differenceImage = None
                            differenceImage = tempDifferenceImage
                        else:
                            if tempDifferenceImage != None:
                                tempDifferenceImage.Dispose()
                                tempDifferenceImage = None

                # Add result
                indexString = "(" + str(indexCompared + 1) + " of " + str(len(referenceImagesList)) + ")";
                # If the images match
                if resultCompared:
                    # Log a comment
                    message = "The phone display image matches the '%s' %s reference image."% (refImageName, indexString)
                    self.comment('\"%s\"'% message)

                # Else the images do not match
                elif time.time()-startTime > timeout/1000.0:
                    debug.out(time.time()-startTime)
                    shouldStop = True

                    # Following code is ported directly from DisplayImageComparer-activity
                    with Bitmap.FromFile(referenceImagesList[indexCompared]) as referenceImage:
                        # Draw the masks on the reference image
                        ImageComparer.DrawMasks(referenceImage)

                        # Save the reference image with the masks drawn
                        referenceImageWithMasksFilePath = os.path.join(os.path.split(capturedImagePath)[0] ,"%s_reference%s"% os.path.splitext(os.path.split(capturedImagePath)[-1]))
                        referenceImage.Save(referenceImageWithMasksFilePath, ImageFormat.Png);

                        # Save the image showing the differences
                        differenceImageFilePath = os.path.join(os.path.split(capturedImagePath)[0] ,"%s_difference%s"% os.path.splitext(os.path.split(capturedImagePath)[-1]))
                        differenceImage.Save(differenceImageFilePath, ImageFormat.Png)

                        # Generate the test case report information containing each of the images
                        # Create a test step for the image comparison
                        teststepId = "1"
                        teststepStepId = "0"
                        teststep = NodeUtils('teststep', makeNewNode = True)
                        teststep['name'] = 'display image comparison'
                        teststep['id'] = teststepId
                        teststep['stepId'] = teststepStepId
                        teststep['timeout'] = "0"
                        captureId = "4"
                        testStepCapture = NodeUtils('capture', makeNewNode = True)
                        testStepCapture['name'] = "'display image comparison'"
                        testStepCapture['id'] = captureId
                        teststep.append(testStepCapture)

                        # Add the test step to the test case report
                        self.result.tcReport.append(teststep)

                        # Create a summary
                        summary = NodeUtils('summary', makeNewNode = True)
                        summary['name'] = "'display image comparison'"
                        summary['id'] = teststepId
                        summary['stepId'] = teststepStepId

                        # Add the image showing the differences
                        differenceCapture = NodeUtils('capture', makeNewNode = True)
                        differenceCapture['id'] = captureId
                        differenceCapture['name'] = 'Image showing differences with the reference image'
                        differenceBitmap = NodeUtils('bitmap', makeNewNode = True)
                        differenceBitmap['name'] = os.path.split(differenceImageFilePath)[-1]
                        differenceBitmap['format'] ='13'
                        differenceBitmap['screen']='1'
                        differenceBitmap['x']='0'
                        differenceBitmap['y']='0'
                        differenceBitmap['width']= str(differenceImage.Width)
                        differenceBitmap['height']=str(differenceImage.Height)
                        differenceBitmap['background']='no'
                        differenceCapture.append(differenceBitmap)
                        summary.append(differenceCapture)

                        # Add the actual image
                        actualCapture = NodeUtils('capture', makeNewNode = True)
                        actualCapture['id'] = captureId
                        actualCapture['name'] = 'Actual image'
                        actualBitmap = NodeUtils('bitmap', makeNewNode = True)
                        actualBitmap['name'] = os.path.split(capturedImagePath)[-1]
                        actualBitmap['format'] ='13'
                        actualBitmap['screen']='1'
                        actualBitmap['x']='0'
                        actualBitmap['y']='0'
                        actualBitmap['width']= str(actualImage.Width)
                        actualBitmap['height']= str(actualImage.Height)
                        actualBitmap['background']='no'
                        actualCapture.append(actualBitmap)
                        summary.append(actualCapture)

                        # Add the reference image
                        referenceCapture = NodeUtils('capture', makeNewNode = True)
                        referenceCapture['id'] = captureId
                        referenceCapture['name'] = "'" + refImageName + "' " + indexString + " reference image"
                        referenceBitmap = NodeUtils('bitmap', makeNewNode = True)
                        referenceBitmap['name'] = os.path.split(referenceImageWithMasksFilePath)[-1]
                        referenceBitmap['format'] ='13'
                        referenceBitmap['screen']='1'
                        referenceBitmap['x']='0'
                        referenceBitmap['y']='0'
                        referenceBitmap['width']= str(referenceImage.Width)
                        referenceBitmap['height']= str(referenceImage.Height)
                        referenceBitmap['background']='no'
                        referenceCapture.append(referenceBitmap)
                        summary.append(referenceCapture)

                        # Add the summary to the report
                        self.result.tcReport.append(summary)

                        message = "The phone display image does not match the '%s' reference image."% refImageName
                        self.fail(message)

                        #Code ported from DisplayImageComparer-activity ends here
                else:
                    continue

    def fail(self, message, takeErrorCapture = True, crashOrReset = False):
        """Fail the test, with the given message.

            message             error reason string
            takeErrorCapture    whether error capture is taken or not (default = True)
            crashOrReset        whether error type is crash or reset (default = False)
        """
        raise TestException(repr(message), self, takeErrorCapture, crashOrReset)

    def takeVideoStillImage(self, imagename=None):
        """ If Video recording is available, this method will take a still image from video stream """

        if core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.isMain():

            if imagename == None:
                imgname = '%s_%s' % (os.path.splitext(core.FW_conf['test_result_name'])[0], str(len(self._capturedStillImages) + 1))
            else:
                imgname = imagename

            imgPath = os.path.join(core.FW_conf['test_result_dir'], 'videos')
            if not os.path.isdir(imgPath):
                os.makedirs(imgPath)

            imgname = filterValidFilename(imgname)
            if not imagename:
                imgname += '.jpg'

            if not imgname in self._capturedStillImages:
                self._capturedStillImages.append(imgname)

            self.delay(300, False)
            core.FW_conf['blackbox'].takePicture(os.path.join(imgPath, imgname))

            if self.isLeader():
                if imagename != None:
                    core.FW_conf['leader'].ExecuteString("self.takeVideoStillImage('%s')" % imagename )
                else:
                    core.FW_conf['leader'].ExecuteString('self.takeVideoStillImage()')

    def takeCaptureFromFailure(self):
        """Takes capture from error situation."""
        # just return if we don't have capture method to execute
        # this is normal situation when test case inherits TestCase instead of UITestCase
        if not hasattr(self, 'capture'):
            return

        # perform failure capture only once,
        # because it may be that the capture also fails
        if not self.__failureCaptureTaken:
            self.__failureCaptureTaken = True

            # reset current test step
            self._initTestStep()

            # set error_capture flag to True so that image will be named as error
            core.FW_conf['error_capture'] = True

            try:
                if self.isFullBlackBox():
                    self.takeVideoStillImage()

                # empty current dump buffer
                try:
                    self._flushDumpBuffer()
                except Exception as e:
                    debug.out('Unable to flush dump buffer: %s' % e.message)

                self.capture('capture from failure')
            except Exception:
                debug.err('Unable to take capture from failure!')
            finally:
                # error_capture flag must always be set back to False
                core.FW_conf['error_capture'] = False

    def _flushDumpBuffer(self):
        """ flush buffer of dumps to disk """

        dumpFiles = []
        prefix = os.path.splitext(core.FW_conf['test_result_name'])[0]
        for i in range(len(self._tab._dumpBuffer)):
            dumpFiles.append(self._tab._TestAutomationBridge__saveDump(self._tab._dumpBuffer.pop(), '%s_%s' % (prefix, i)))

        if dumpFiles:
            zipFilePath = os.path.split(dumpFiles[0])[0]
            zipf = zipfile.ZipFile(os.path.join(zipFilePath, '%s.zip' % prefix), 'w')
            try:
                for file in dumpFiles:
                    zipf.write(file, os.path.split(file)[1])
                    os.remove(file)
            finally:
                zipf.close()

    def setFailureCaptureTaken(self, value):
        self.__failureCaptureTaken = value

    def failIf(self, expr, message):
        """Fail the test if the expression is true."""
        if expr: self.fail(message)

    def failIfEqual(self, first, second, message):
        """Fail the test if the two objects are equal."""
        if first == second:
            self.fail(message or ('%s != %s' % (`first`, `second`),))

    def failUnless(self, expr, message):
        """Fail the test unless the expression is true."""
        if not expr: self.fail(message)

    def failUnlessEqual(self, first, second, message):
        """Fail the test if the two objects are unequal."""
        if first != second:
            self.fail(message or ('%s != %s' % (`first`, `second`),))

    def failUnlessRaises(self, excClass, callableObj, *args, **kwargs):
        """Fail unless an exception of class excClass is thrown."""
        try:
            apply(callableObj, args, kwargs)
        except excClass:
            return
        else:
            excName = getattr(excClass, '__name__', str(excClass))
            self.fail('Expected exception was not raised: %s' % excName)

    def skip(self, message):
        """Skip the test immediately, with the given message."""
        raise SkipTestException(message)

    def skipIf(self, expr, message):
        """Skip the test if the expression is true."""
        if expr: self.skip(message)

    def skipUnless(self, expr, message):
        """Skip the test unless the expression is true."""
        if not expr: self.skip(message)

    def _run(self, testStepName = None, testStepReporting = True):
        """Run the created test step."""
        # if test execution is aborted, do it with StopTestException
        if core.FW_conf['should_stop']:
            raise StopTestException('Test execution terminated')

        # only purge key presses list (key presses and touches)
        self.__purgeKeyPresses()
        self._initTestStep()

    def _pressKey(self, key, length=None, waitUntilNoUIevents=True, \
                  timeout = 500, maximumDuration = 3000):
        """ Constructs NodeUtils instance to keyPresses.

        Usage

           key                  the name of the key, mandatory
                                (type=String)

           length               the length of key press
                                (type=Integer, default=None)

           waitUntilNoUIevents  Wait after execution for ui events to finish. Only in tab execution

           timeout              UI event wait timeout. Only in tab execution

           maximumDuration      Max UI event wait. Only in tab execution

        """

        if not type(key) in [types.StringType, types.UnicodeType]:
            raise KeyError('Invalid key (%s) given!' % str(key))

        if key.startswith('KEYCODE'):

            keyCode = {'key':key}

            k = NodeUtils('keypress', makeNewNode = True)

            k['key'] = keyCode['key']
            k['length'] = length
            k['timeout'] = timeout
            k['waitUntilNoUIevents'] = waitUntilNoUIevents
            k['maximumDuration'] = maximumDuration

            self.keyPresses.append(k)
        else:
            raise KeyError('Invalid key (%s) given!' % str(key))

    def addBltueTestStep(self, testStepName):
        """Write test step name to bltue report if necessary

            Parameters

            testStepName        test step name in string
        """
        if self.battery is not None and self.battery.isEnabled():
            bltueTestStep = NodeUtils('teststep', makeNewNode = True)
            bltueTestStep.setAttribute('name', testStepName)
            self.battery.addBltueNode(bltueTestStep)

    def warn(self, warning=None):
        """Add warning to the test result.

        This method does not stop the test execution.

        FIXME: Replace 'warning' attribute with '*warnings'
        """

        if self.getName() != 'Main':
            warning = self.getName() + ': ' + warning

        debug.err('Warning: %s' % warning)
        if type(warning) != types.ListType:
            warning = [warning]

        if self.result:
            self.result.addStepWarning(warning)

    def sendWaitMessageToMarbleGUI(self, timeout, comment):
        """Sends wait message to Marble GUI.

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

    def getProductDetails(self):
        # just return dictionary if details have already been read
        if self.__productDetails.keys():
            if self.result:
                self.result.setProductDetails(self.__productDetails)
            return self.__productDetails

        deviceInfo = self.deviceInfo(doNotReport = True)

        self.__productDetails['imei'] = deviceInfo.has_key('ro.device.imei') and deviceInfo['ro.device.imei'] or ''
        self.__productDetails['sw'] = deviceInfo.has_key('ro.build.fingerprint') and deviceInfo['ro.build.fingerprint'] or ''
        self.__productDetails['hw'] = deviceInfo.has_key('hw.cabl.version') and deviceInfo['hw.cabl.version'] or ''
        self.__productDetails['lang'] = deviceInfo.has_key('persist.sys.language') and deviceInfo['persist.sys.language'] or ''
        self.__productDetails['imsi1'] = ''
        self.__productDetails['imsi2'] = ''
        self.__productDetails['sim1'] = self.settings.Main.SIM1PhoneNumber
        self.__productDetails['sim2'] = self.settings.Main.SIM2PhoneNumber
        self.__productDetails['connection'] = self.settings.Main.Connection
        self.__productDetails['rmcode'] = deviceInfo.has_key('ro.product.device') and deviceInfo['ro.product.device'] or ''
        self.__productDetails['name'] = deviceInfo.has_key('ro.product.name') and deviceInfo['ro.product.name'] or ''
        self.__productDetails['main_display'] = '%sX%s' % (self.uiState.getScreenWidth(), self.uiState.getScreenHeight())

        versionInfoFilePath = os.path.join(os.path.split(os.path.dirname(__file__))[0],'..', 'MarbleVersion.txt')
        if os.path.isfile(versionInfoFilePath):
            versionInfoFile = open(versionInfoFilePath, 'r')
            self.__productDetails['fw_version'] = versionInfoFile.read()
            versionInfoFile.close()

        if self._tab._tabConn and (self._tab._isServerAvailable() and self._tab._isServerConnected()):
            success, serverVersion = self._tab._executeTabOperation(\
                self._tab._tabConn.TestServerClient.getServerVersion)

            if success and serverVersion:
                self.__productDetails['marble server'] = serverVersion

        if self.result:
            self.result.setProductDetails(self.__productDetails)

        return self.__productDetails


class PhoneManager(object):
    """ Manager-class for phones used in testing

    """
    def __init__(self):
        self.__phones = []
        self.__connSerials = self.__getConnections()
        self.__setAccess()
        self.__initialConnectionsCreated = False
        # Result is initialized for making comments before TC initialization
        self.result = testresult.MarbleTestResult()

    def __getConnections(self):
        """ Get phone connections from settings. """
        connSerials = []

        try:
            index = 1

            while True: # Break with exception or when connection is empty
                settings = eval("core.FW_conf['settings'].Main%s" % (index != 1 and index or ""))

                if not settings.Connection:
                    break

                connSerials.append(settings.Connection)
                #debug.brf('connection appended: %s' % settings.Connection)

                index += 1
        except Exception, e:
            pass

        #debug.brf('connSerials: %s' % connSerials)

        return connSerials

    def __setAccess(self):
        """ Set access to phone instances. """
        index = 1

        for connSerial in self.__connSerials:
            phone = Phone("Main%s" % (index != 1 and index or ""))
            self.append(phone)
            index += 1

    def connect(self, serialNumber = ""):
        """ Connect all phones at once. When we already have connections, check do we have to close some connections.

            Parameters

            serialNumber        optional serial number which can be given mainly from command line
        """
        if not self.__initialConnectionsCreated:
            if serialNumber:
                self.__phones = []
                self.__connSerials = []
                phone = Phone("Main")
                self.append(phone)
                phone.createConnection(serialNumber = serialNumber)
            else:
                for connSerial in self.__connSerials:
                    #debug.brf('connSerial: %s' % connSerial)
                    self.__phones[self.__connSerials.index(connSerial)].createConnection(serialNumber = connSerial)

            self.__initialConnectionsCreated = True
        else:
            newConnSerials = self.__getConnections()

            # connection serials changed
            if newConnSerials != self.__connSerials:
                #debug.brf('newConnSerials: %s' % newConnSerials)
                #debug.brf('self.__connSerials: %s' % self.__connSerials)

                for oldConnSerial in self.__connSerials:
                    # close connection(s) which are no longer in use
                    if not oldConnSerial in newConnSerials:
                        self.__phones[self.__connSerials.index(oldConnSerial)].closeConnection()

                index = 1
                phones = []

                for newConnSerial in newConnSerials:
                    # take existing phone class instance
                    if newConnSerial in self.__connSerials:
                        phone = self.__phones[self.__connSerials.index(newConnSerial)]
                        phone.setName("Main%s" % (index != 1 and index or ""))
                    # create new phone class instance
                    else:
                        phone = Phone("Main%s" % (index != 1 and index or ""))

                    phones.append(phone)
                    # NOTE: createConnection just returns if connection already made
                    phone.createConnection(serialNumber = newConnSerial)

                    index += 1

                self.__phones = phones
                self.__connSerials = newConnSerials
            # serials same --> call createConnection to ensure phone connections
            else:
                for connSerial in self.__connSerials:
                    phone = self.__phones[self.__connSerials.index(connSerial)]
                    # NOTE: createConnection just returns if connection already made
                    phone.createConnection(serialNumber = connSerial)

        # set result for all connections
        self.setResult(self.result)

    def __call__(self, funcName, *args, **kwargs):
        """ Access first phone directly by calling manager instance.

            parameters:
                funcName : name of the method in phone module to be called

        """
        if not len(self.__phones):
            raise SkipTestException('Phone not found!')

        return self.__phones[0](funcName, *args, **kwargs)

    def __len__(self):
        """ Add support for len() - call."""
        return len(self.__phones)

    def __iter__(self):
        return self.__phones

    def __getitem__(self, key):
        """ Add support for accessing phone instances by using indexes. """
        assert isinstance(key, int) and key > 0, 'Phone index must be greater than zero!'

        # minus one so that we use correct indexes
        key = key - 1

        if key > len(self.__phones) - 1:
            raise SkipTestException('Phone %s not found!' % (key + 1))

        return self.__phones[key]

    def ___setitem__(self, key, value):
        """ Add support for setting phone instance by using index """
        self.__phones[key] = value

    def __delitem__(self, key):
        """ Add support for deleting items"""
        self.__phones.pop(key)

    def __getattr__(self, attr, *args, **kwargs):
        """ Create access to first phone instance. """
        if not attr in dir(self):
            if len(self.__phones):
                return self.__phones[0].__getattribute__(attr)
            else:
                self.connect()

                if len(self.__phones):
                    return self.__phones[0].__getattribute__(attr)
                else:
                    raise TestException('No phones found! Please check phone connection settings!')
        else:
            return getattr(self, attr)

    def append(self, item):
        self.__phones.append(item)

    def __contains__(self, item):
        return self.__phones.__contains__(item)

    def index(self, item):
        return self.__phones.index(item)

    def closeConnections(self):
        for phone in self.__phones:
            phone.closeConnection()

    def setResult(self, result):
        """ Set result instance to all phones. """
        if result == None:
            del self.result
        self.result = result

        for phone in self.__phones:
            phone._setResult(result)

    def getResult(self):
        """ Get the phone managers result instance """
        return self.result

    def _makeResult(self):
        """Creates test result instance for phone manager """
        self.setResult(None) # delete existing result
        self.setResult(testresult.MarbleTestResult())
