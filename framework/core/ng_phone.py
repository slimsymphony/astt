# -*- coding: utf-8 -*-
"""Marble FW <-> NG Phone controller module

   Contains functions for controlling the remote NG phone.
"""

import sys, types, time, os, glob, shutil, zipfile, zlib, re

import clr
clr.AddReference('System.Drawing')
clr.AddReference('MarbleLibrary')
clr.AddReference('System.Xml.Linq')

import System
from System.Drawing import Bitmap
from System.Drawing.Imaging import ImageFormat
from MarbleLibrary.Utilities import ImageComparer

from os import path
import core
from core import debug, scripting
from core.testcase_exceptions import TestException, StopTestException, SkipTestException
from interfaces.c_srv import srv_mtc
from utils.texts import Texts
from interfaces.srv_granite import GraniteServerInterface
from core.touch import Touch
from core.ng_scripting import NGInput, NGSelect, NGUIState, NGNavigate, NGExpect, NGNotExpect, \
                           Gesture, NGTryExpect, NGExit, NGClear, Post, NGBack, NGCheck, AdjustVolume, NGRead, NGDatePicker, NGTimePicker, escape
from utils.middleware import MiddlewareComponents
from utils.phone_file_dumper import CommonFileDumper
from utils.monkey import Monkey
from utils.sx_utils import SxUtils
from utils.nodeutils import NodeUtils
from utils.sx_helpers import SX_Helper
from interfaces import timeoutparser, wbxml_encoder
from extensions.django.utils.encoding import smart_str, smart_unicode
from interfaces.c_srv import srv_info
import leader
from leader import step_interval_counter
from core.leader import executeInFollower
from System.Xml.Linq import XDocument, XElement
from System.Collections.Generic import List
from utils.file_utils import filterValidFilename
from utils.provisioning import ProvisioningManager


class PhoneConnection(GraniteServerInterface):

    def __init__(self, connSettings):
        if type(self) == PhoneConnection:
            raise Exception("<PhoneConnection> must be subclassed.")

        GraniteServerInterface.__init__(self)

        self._activatingGraniteServer = False

        self.image_dict = {}
        self.text_dict = {}
        self.java_image_dict = {}

        self.old_texts_instance = None

        self.settings = core.FW_conf['settings']
        self.connSettings = connSettings
        self.currentConnection = None

        # interface to server component library
        # Initialize in createConnection
        self.srv = None

        self.MessageSender = None
        self._fileDumper = None

    def isFollower(self):
        """ Returns true if Main phone and Follower mode is activated """
        return False

    def isFullBlackBox(self):
        return False

    def setName(self, name):
        """ Method for setting phone name"""
        self._name = name

    def getName(self):
        """ Method for getting phone name"""
        return self._name

    def isLeader(self):
        """ Returns true if Main phone and Leader mode is activated """
        return False

    def closeConnection(self, forced = False):
        """ Closes the phone connection """
        super(PhoneConnection, self).closeConnection(forced)

    def createConnection(self, ensureConnection = True,):
        """ This method is needed also in PhoneConnection class to create object instances in correct phase"""
        # create connection only for remote phones
        connectionCreated = super(PhoneConnection, self).createConnection(self.connSettings, ensureConnection)

        if connectionCreated:
            self.srv = MiddlewareComponents(self, self.graniteConnection.CommunicationAdapter)
            self.MessageSender = self.graniteConnection.MessageApiSender
            self._fileDumper = CommonFileDumper(self)

        return connectionCreated

    def activateGraniteServer(self, forced = False, ensureConnection = True):
        """Activates Granite server by resetting the phone and gets server's object id.
           In simulation server is activated by default so reset is not needed.

            Parameters

            forced              forced object id query (default = False)
            ensureConnection    call ensureConnection from this function
                                (default = True)
        """
        # just return if not connected
        if not self.isConnected():
            return

        if self.isFollower():
            debug.out('activateGraniteServer: follower mode')
            return

        try:
            self._activatingGraniteServer = True

            if ensureConnection:
                # check connection before further actions
                self.ensureConnection()

            if self.isConnected():
                # if on BlackBox mode, disable USB charging. Also if running with simulated battery/current measurement, USB charging needs to be disabled:
                # If the battery is also charged via the USB cable, the current consumption seen from the battery will be negative.
                if ((core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox_enabled']) or (core.FW_conf['blt_ue'] is not None and core.FW_conf['blt_ue'].isEnabled())) and self.getName() == "Main":
                    try:
                        self.srv.Energy.disableUSBCharging()
                    except Exception, error:
                        debug.err('Error when setting USB charging mode to off: %s' % \
                                   str(error))


                if self.getConnectionBusName() == 'TCP':
                    for i in range(3):
                        try:
                            # get Granite server's object id
                            # this will also update the value to interfaces module
                            self.getObjectId(forced)
                            core.FW_conf['granite_server_activated'] = True
                        # if it's not active getObjectId will raise TestException
                        except Exception, error:
                            debug.err('Error occurred in Granite object id query: %s' % \
                                       str(error))

                            if i == 2:
                                self.closeConnection()
                                sys.exit()
                            else:
                                time.sleep(2)
                        else:
                            self.clearGraniteServer()
                            self.checkPhoneStatus()
                            break
                else:
                    # startup file name and path definition
                    startupFileName = u'granite.startup'
                    startupFilePath = os.path.abspath(os.path.join(\
                                            core.FW_conf['startup_path'],
                                            'core/data',
                                            startupFileName))
                    predefHidden = 'C:\\predefhiddenfolder'

                    if not os.path.isfile(startupFilePath):
                        debug.err('%s does not exist. Impossible to continue.' % startupFilePath)
                        sys.exit()

                    for i in range(10):
                        # check if Granite server is already active
                        try:
                            # get Granite server's object id
                            # this will also update the value to interfaces module
                            self.getObjectId(forced)
                            core.FW_conf['granite_server_activated'] = True
                        # if it's not active getObjectId will raise TestException
                        except TestException:
                            try:
                                # check if startup file is found
                                # NOTE: file list is in the first index,
                                #       directory list in the second one
                                if not self.fileExists(\
                                   os.path.join(predefHidden, startupFileName)):
                                    # create file
                                    self.createFile(\
                                               startupFilePath, predefHidden)
                                    # set attributes
                                    #self.setAttribute(,
                                    #             ('FILE2_ARDONLY, ' \
                                    #              'FILE2_AHIDDEN, ' \
                                    #              'FILE2_ASYSTEM', True),
                                    #             startupFileName)
                                else:
                                    debug.out('Granite startup file found from the phone.')

                                debug.brf("Activating Granite Server by resetting the phone...")
                                # server can't be cleared here, because object id is not known yet
                                self.resetTarget(clearGraniteServer = False)
                            except Exception, error:
                                debug.err('Error occurred in Granite startup: %s' % \
                                          str(error))

                                # ensure phone connection
                                if i == 9:
                                    if self.getName() == "Main":
                                        # in the last loop round we must give up
                                        errorMessage = 'Unable to activate Granite server, terminating test execution!'
                                    else:
                                        errorMessage = 'Remote phone (%s) dropped due to connection error' % self.getName()

                                    # try to close the phone connection
                                    try:
                                        self.closeConnection(True)
                                    except Exception, ex:
                                        debug.err('Error in closing the Granite connection: %s' % \
                                        str(ex))

                                    debug.err(errorMessage)

                                    if core.FW_conf['cli_mode']:
                                        raise SystemExit(errorMessage)
                                    else:
                                        if self.getName() == "Main":
                                            # send error to Granite GUI
                                            core.FW_conf['com_int'].sendErrorMessage(errorMessage)

                                            # execute CMD_STOP event --> stops test execution
                                            core.FW_conf['com_int'].connectionCreationOngoing = False
                                            core.FW_conf['com_int'].CMD_STOP(None)
                                            break
                                        else:
                                            self.warn(errorMessage)
                                            # delete remote phone instance from remote phone manager
                                            if self in core.FW_conf['remote_connection']:
                                                del core.FW_conf['remote_connection'][core.FW_conf['remote_connection'].index(self)]
                                else:
                                    # wait for a while and then check phone connection
                                    time.sleep(2)
                                    if ensureConnection:
                                        self.ensureConnection()
                        else:
                            # everything ok, clear Granite server and break from the loop
                            self.clearGraniteServer()
                            self.checkPhoneStatus()
                            break
        finally:
            self._activatingGraniteServer = False

    def resetTarget(self, timeout = None, clearGraniteServer = True):
        """ Performs hidden reset to phone under test.

            Reset the phone under test by sending an MTC_RESET_GENERATE_REQ. While
            its resetting, give it some time to recover, then start querying MTC's
            status until it reaches NORMAL.

            Parameters

            timeout             reset timeout in seconds (default = None)
            clearGraniteServer  whether to clear Granite server or not (default = True)
        """

        # define timeout
        if timeout is None:
            timeout = core.FW_conf['settings'].System.PhoneReset

        assert isinstance(timeout, int), 'Timeout parameter not an integer!'

        try:
            resetReq = srv_mtc.MtcResetGenerateReq(\
                                type = srv_mtc.mtc.MTC_HIDDEN_RESET,
                                state = srv_mtc.mtc.MTC_RESET_SW_RESET)

            resp = srv_mtc.MtcResetGenerateResp(\
                isi_message = self.transferMsg(resetReq))

        except TestException, err:
            debug.exception(err)
            raise TestException('Could not reset the phone: %s' % err, self)

        if resp.status != srv_mtc.mtc.MTC_OK:
            raise TestException('Invalid response for phone reset ' \
                                'command: %s' % resp.toxml(), self)

        debug.brf('The phone is now resetting. %d second delay..' % timeout)

        # send wait message from main FW process to GUI
        self.sendWaitMessageToGraniteGUI(\
             timeout, 'Phone reset')

        time.sleep(timeout)

        if clearGraniteServer:
            # put Granite server to idle state
            self.clearGraniteServer()
            self.checkPhoneStatus()

    def setupPhoneForUITesting(self):
        """Sets up phone for UI testing
            - Modifies certain settings with SX
            - Creates image dictionaries
        """
        if core.FW_conf['should_stop']:
            return

        if self.isFollower():
            # Todo: Change when server_version is moved to Phone. Follower mode does not need it, but
            # remote phone executions will fail if server_version is not defined
            self.server_version = {"zzz":4,
                                   "yyy":4,
                                   "xxx":4}
            return # follower does not need setup

        # modify needed phone settings
        self.modifyPhoneSettings()

        if self.image_dict == {}:
            self.createImageDictionary()

        if self.text_dict == {}:
            succeeded = self.createTextDictionary()
        else:
            succeeded = True

        if self.server_version['yyy'] > 4 or (self.server_version['yyy'] == 4 and self.server_version['xxx'] >= 4):
            pass
        else:
            if self.java_image_dict == {}:
                self.createJavaImageDict()

        if not succeeded and not self.old_texts_instance:
            if not core.FW_conf['should_stop']:
                debug.err('Logical text dictionary missing! Using logical texts from zip file.')

            self.old_texts_instance = Texts()

    def modifyPhoneSettings(self):
        """Modify phone settings which cause problems for test automation. Use SX commands for modifications.

            Parameters

            testCase        test case instance
        """
        if core.FW_conf['should_stop']:
            return

        settingValues = \
            ['"./yapas/privacy/phone-lock-enabled" false',      # disable device-lock API
             '"./yapas/keylock/autolock" 3600000',              # set screen saver timeout to 1 hour
             '"./yapas/input/FTU-accepted" "yes"',              # disable input variant change popup dialog
             '"./yapas/debug/fps"',                             # for fps measuring
            ]

        #for settingValue in settingValues:
        #    try:
        #        # fps measuring not activated for NoSE
        #        if settingValue == '"./yapas/debug/fps"':
        #            if core.FW_conf['settings'].TestRun.PerformanceTesting and \
        #               self.getConnectionBusName() != 'TCP':
        #                settingValue += ' 1'
        #            else:
        #                # in Aqua disable value is 'false', in other products 0
        #                if self.product_name.startswith('Aqua'):
        #                    settingValue += ' false'
        #                else:
        #                    settingValue += ' 0'

        #        self.sx('(send config-manager set-setting %s)' % settingValue)
        #    except:
        #        debug.err('Unable to modify phone setting: "%s"' % settingValue)

        # delete FTU-tip setting for disabling popup dialogs and tips in input (phone SW change)
        try:
            self.sx('(send config-manager delete-setting "./yapas/input/FTU-tip")')
        except:
            debug.err('Unable to delete phone setting: "./yapas/input/FTU-tip"')

        try:
            self.sx('(define test-automation-input "")', doNotReport=True)
        except:
            debug.err('Unable to define variable: test-automation-input')

    def createImageDictionary(self):
        """Create image dictionary to translate logical image names to png filenames

            Parameters

            testCase        test case instance
        """
        if core.FW_conf['should_stop']:
            return

        try:
            result = self.sx(self._GraniteSX.IMAGE_METADATA, doNotReport = True, timeout = 30000)

            if isinstance(result, NodeUtils):
                images = result.findall("//image")
            else:
                debug.err('Invalid response to image metadata: %s' % repr(result))
                images = []

            if not images:
                debug.err('No images found from image metadata xml!')
            else:
                lost = {}
                debug.out("Creating image library...")

                for image in images:
                    id = image.getAttribute("id")
                    path = image.getAttribute("path")
                    r = os.path.split(path)[1]
                    if r != "":
                        if self.image_dict.has_key(id):
                            debug.err("Warning: Error when creating image dictionary. Dictionary has already key %s (%s)" % (id, self.image_dict[id]))
                        else:
                            self.image_dict[id] = r
                    else:
                        debug.vrb("error with image dictionary, could not parse image %s with path: %s" % (id,path))
                        if lost.has_key(id):
                            debug.vrb("error: failed image dictionary already has key %s" % id)
                        else:
                            lost[id] = path
        except Exception, err:
            if not core.FW_conf['should_stop']:
                debug.err('Unable to create image dictionary: %s' % str(err))

    def getImageFilename(self, id):
        """Get image png-filename with logical id. Returns the found png filename or "id" untouched if not found.
           Dictionary lookup is called from testcase getImage

            Parameters

            id(string)  :   logical id to be searched from image dictionary

        """
        if self.image_dict.has_key(id):
            return self.image_dict[id]
        return id # if dictionary fetch failed, return id untouched

    def getLogicalImageName(self, pngName):
        """ Get logical ids for given png image name.

            Parameters
            pngName(str)     :     name of the image e.g. evo_icon_call_addcontact_l_light.png

            Returns list of logical ids if found, otherwise None
        """

        returnValues = []

        if self.image_dict:
            [returnValues.append(id) for id, png in self.image_dict.iteritems() if (png == pngName)]

        if returnValues != []:
            return returnValues
        else:
            return None

    def saveImageToDictionary(self, id, filename):
        """Saves image to dictionary. Only used to have backwards compatibility if dictionary creation does not work with evo sw (feature in wk35/2012 sw)

            Parameters

            id(string)            :   Logical image name (eg. 'options/indicator')
            filename (string)     :   Filename
        """
        if not self.image_dict.has_key(id) and filename != None:
            self.image_dict[id] = filename

    def createJavaImageDict(self):
        """ Copy midlets from C:\sp\system_files\_system_applications-folder in phone, calculate adler32-checksum for each image in midlets
            and store information in self.java_image_dict

        """
        if core.FW_conf['should_stop']:
            return

        try:
            files = self.getFolderContent(r'C:\sp\system_files\_system_applications')[0]
            if not files:
                debug.out("No midlets found from phone...")
                return

            phoneName = self.getName() != 'Main' and 'remote phone' or 'phone'
            debug.brf("Copying midlets from %s and calculating checksums..." % phoneName)
            for f in files:
                if f.endswith('.jar'):
                    debug.out("copying %s..."%f)
                    tempDataPath = os.path.abspath(os.path.join(core.FW_conf['test_result_dir'],'temp','java_transfer'))
                    if not os.path.isdir(tempDataPath):
                        os.makedirs(tempDataPath)
                    self.readFile(r'C:\sp\system_files\_system_applications\%s'%f, os.path.join(tempDataPath,f))

            jarList = []
            log = []
            buildJarList = []


            #Loop through jar-files and extract images to memory and calculate adler32-checksum for each image

            jarList = glob.glob('%s/*.jar'%tempDataPath)
            debug.out(jarList)

            for f in jarList:
                try:
                    jarFile = zipfile.ZipFile(f)
                    debug.out("JarFile: %s"%f)
                except Exception, e:
                    #debug.err(e)
                    #log.append('Error in opening file %s, %s'%(f,e))
                    continue

                for image in [i for i in jarFile.namelist() if os.path.splitext(i)[1] in ['.png','.fif']]:
                    f = os.path.normpath(f)
                    imagePath = os.path.join(os.path.split(f)[0],os.path.split(image)[0])
                    imageName = os.path.split(image)[1].lower()

                    checksum = zlib.adler32(jarFile.read(image)) & 0xffffffffL
                    debug.out(imageName+":"+str(checksum))

                    self.java_image_dict[checksum] = imageName

                jarFile.close()

            debug.out(self.java_image_dict)
        except Exception, e:
            self.warn('Getting reference data for Java midlets failed: %s'%str(e))

        if 0: # For debugging purpose!!!
            dictFile = open(os.path.join(tempDataPath, "java_dict.txt"),'w')
            for k in self.java_image_dict.keys():
                dictFile.write("%s : %s\n"%(k, self.java_image_dict[k]))
            dictFile.close()

        else:
            #Wait for last jar-file to be closed before removing directory
            time.sleep(1)

            # step one level up to "temp" directory
            tempDataPath = os.path.split(tempDataPath)[0]

            try:
                shutil.rmtree(tempDataPath)
            except Exception:
                try:
                    time.sleep(1)
                    shutil.rmtree(tempDataPath)
                except Exception:
                    pass

    def getJavaImageFilename(self, id):
        """ Returns filename which matches given id. If if id is not found empty string is returned

        """
        try:
            id = int(id)
            debug.out("getJavaImageFilename")
            debug.out(len(self.java_image_dict.keys()))
            debug.out(id)
            if self.java_image_dict.has_key(id):
                debug.out(self.java_image_dict[id])
                return self.java_image_dict[id]
        except Exception, err:
            debug.out('Error in getJavaImageFilename: %s' % str(err))

        return '' # if dictionary fetch failed, return id untouched

    def createTextDictionary(self):
        """Create text dictionary to map logical text ids to translations

            Parameters

            testCase        test case instance

            Returns True if text dictionary creation succeeded, otherwise False
        """
        if core.FW_conf['should_stop']:
            return

        try:
            returnValue = False

            result = self.sx(self._GraniteSX.TEXT_METADATA, doNotReport = True, timeout = 30000)

            if isinstance(result, NodeUtils):
                texts = result.findall("//text")
            else:
                debug.err('Invalid response to text metadata: %s' % repr(result))
                texts = []

            if not texts:
                debug.err('No texts found from text metadata xml!')
            else:
                debug.out("Creating text library...")

                self.text_dict = {}
                for text in texts:
                    id = text.getAttribute("id")
                    translation = text.getAttribute("translation")

                    # skip texts that don's have translation
                    if id == translation:
                        continue

                    if not self.text_dict.has_key(translation):
                        self.text_dict[translation] = id

                returnValue = True
        except Exception, err:
            if not core.FW_conf['should_stop']:
                debug.err('Unable to create text dictionary: %s' % str(err))

        return returnValue

    def getTranslation(self, id):
        """Get logical text translation.

            Parameters

            id      logical id
        """
        returnValue = None

        if self.text_dict != {}:
            for key, value in self.text_dict.iteritems():
                if value == id:
                    returnValue = key
                    break

            return returnValue
        elif self.old_texts_instance:
            return self.old_texts_instance.getTranslation('en_GB', id)
        else:
            raise TestException('Logical text dictionary missing!', self)

    def isLogicalText(self, text):
        """Return whether given text is logical text or not

            Parameters

            text      text to be checked
        """
        if self.text_dict != {}:
            return text in self.text_dict.values()
        elif self.old_texts_instance:
            return self.old_texts_instance.isLogicalText('en_GB', text)
        else:
            raise TestException('Logical text dictionary missing!', self)

    def getLogicalText(self, text):
        """Get logical text translation.

            Parameters

            text      translated text
        """
        if self.text_dict != {}:
            return self.text_dict.get(text, None)
        elif self.old_texts_instance:
            return self.old_texts_instance.getLogicalText('en_GB', text)
        else:
            raise TestException('Logical text dictionary missing!', self)

class NGPhone(PhoneConnection):
    def __init__(self, connSettings, name = ""):
        PhoneConnection.__init__(self, connSettings)

        # set instance name if given
        self._name = name
        self.__testStepNameIndex = 1
        self.__captureNameIndex = 1

        # menu xml instance
        self.menu = None

        # Result is needed for adding comments
        self.result = None

        # variable for language variant in the phone
        self.phoneLanguage = 'undefined'

        self.product_name = 'unknown'

        self.file = None
        self.__failureCaptureTaken = False
        self.keysOnHold = [] # list for keys that are on hold during test case
        self._initTestStep()

        self._GraniteSX = GraniteSXScripts
        self._touch = Touch(self)
        self.uiState = NGUIState(self)
        self.select = NGSelect(self)
        self.navigate = NGNavigate(self)
        self.expect = NGExpect(self)
        self.notExpect = NGNotExpect(self)
        self.gesture = Gesture(self)
        self.tryExpect = NGTryExpect(self)
        self.exit = NGExit(self)
        self.input = NGInput(self)
        self.clear = NGClear(self)
        self.post = Post(self)
        self.back = NGBack(self)
        self.check = NGCheck(self)
        self.adjustVolume = AdjustVolume(self)
        self.translate = self.getTranslation
        self.isLogicalText = self.isLogicalText
        self.getLogicalText = self.getLogicalText
        self.read = NGRead(self)
        self.selectTime = NGTimePicker(self)
        self.selectDate = NGDatePicker(self)
        self.monkey = Monkey(self)

        self.__setFileAccessMethods()

        # SX utils instance
        self.sxUtils = SxUtils()
        self.sxHelpers = SX_Helper(self)
        self.battery = None
        self.currentTcId = None
        self.__leaderTouchIntervalTimer = 0
        self._capturedStillImages = []

        # initialize Provisioning manager
        self.__provManager = ProvisioningManager()

    def _setUp(self):
        """ Setup to be called from TestCase setUp"""
        if core.FW_conf['should_stop']:
            return

        # create referencephone connection after provisioning settings has been written to the main phone in testcase.py _setUp
        # this is because if POX server is used as reference phone, VoIP SIP proxy will be selected based on the SIM card used in the main phone
        if self.getName() == 'Main':
            self.createReferencePhoneConnection()

        if self.isFollower():
            if core.FW_conf['remote_connection'] != None:
                for remote in core.FW_conf['remote_connection']:
                    remote.checkPhoneStatus() # Move this to Phone.setup

        else:
            # USB charging needs to be disabled in order to get proper current measurement results with USB cable connected to PC
            if self.battery is not None and self.battery.isEnabled():
                # FIXME!!! Should USB charging be disabled from main phone only
                self.srv.Energy.disableUSBCharging()

            if self.getConnectionBusName() != 'TCP':
                # passing True so that we won't fail the test case, only warning is thrown
                resp = self._fileDumper.extractDumpFiles(True)
                if resp == False:
                    self.warn('Getting X-files (before setup) failed: %s.' % resp)

            self.checkPhoneStatus()

            if core.FW_conf['remote_connection'] != None:
                for remote in core.FW_conf['remote_connection']:
                    remote.checkPhoneStatus() # Move this to Phone.setup

            # Start testcase tracing if UI not enabled in phone SW.
            if core.FW_conf['trace']:
                #save previously runned testcase blx file
                if core.FW_conf['repeat'] > 1:
                    traceFileName = core.FW_conf['test_result_name'] + '#%s' % core.FW_conf['repeat_index']
                else:
                    traceFileName = core.FW_conf['test_result_name']

                if core.FW_conf['memory_leak_detection']:
                    traceFileName = filterValidFilename(self.currentTcId)
                    core.FW_conf['trace'].traceSaveBlxAndResumeTracing(traceFileName, memoryLeakDetection = True, uiEnabled=self.uiEnabled())
                else:
                    core.FW_conf['trace'].traceSaveBlxAndResumeTracing(traceFileName, uiEnabled=self.uiEnabled())

    def _uiSetUp(self, tc):
        """ Setup to be called from UITestCase setUp"""
        if core.FW_conf['should_stop']:
            return

        if not self.isFollower():
            # disable phone lock via SX
            self.__disableSecurityLock()

            # get language from phone
            previousLanguage = self.phoneLanguage
            self.phoneLanguage = self.getLanguage()

            # check if language has changed
            if previousLanguage != 'undefined' and \
               previousLanguage != self.phoneLanguage:
                self.languageChanged(self.phoneLanguage)

            self.cancelIndications()
        else:
            self.phoneLanguage = 'en_GB' # TODO: remove hardcoded language

        if core.FW_conf['remote_connection'] != None:
            for remote in core.FW_conf['remote_connection']:
                remote.cancelIndications() # Move this to Phone.setup

        # Ensure that test are started in portrait-mode - unless user skips setup and teardown
        try:
            self.srv.Sensor.setPortrait()
        except Exception, ex:
            debug.err('Testcase setup: %s' %str(ex))

        # if test case setup/teardown has been disabled, warning is printed. if execution happens with monkey, do not warn about skipping exit.
        if core.FW_conf['settings'].TestRun.DisableTestCaseSetupAndTeardown:
            self.warn('Exit skipped!')
        
        self.getMenu()

    def _tearDown(self, tc):
        """ Teardown to be called from TestCase _tearDown"""

        self.checkPhoneStatus()
        self.cancelIndications()

    def _uiTearDown(self, tc):
        """ Teardown to be called from UITestCase _tearDown"""
        if core.FW_conf['blackbox'] != None and core.FW_conf['blackbox_enabled'] and self.getName() == "Main":
            core.FW_conf['blackbox'].videoRecording_SetText('Granite test teardown')

        self.__checkIfKeysAreOnHold()
        self._initTestStep()

        # exit to idle, fail test case if setup & teardown has been skipped unless execution happens with monkey
        assert not core.FW_conf['settings'].TestRun.DisableTestCaseSetupAndTeardown, 'Test case setUp and tearDown disabled!'

    def resetPhone(self, errorReason = ''):
        """Reset phone (whitebox) or disconnect/connect power (blackbox) in order to recover from invalid phone state.
           Exception will be raised (result == NO RESULT)

            Parameters

            errorReason         error reason string
        """
        # if test execution has been aborted, reset phone will not be performed
        if core.FW_conf['should_stop']:
            return

        return super(GraniteServerInterface, self).resetPhone()

    def _ensureBlackBoxUsbAccessoryConnection(self):
        """Ensure that when running on BlackBox mode, default USB connector is always connected.
            A try-catch clause is preferred due to there might be no USBAccessoryCard to execute this operation in some cases.

            Returns True if USB accessory connector has been changed from E.g. None to Usb1,
            False, if no connector change.
        """

        if self.getName() != "Main":
            return super(GraniteServerInterface, self)._ensureBlackBoxUsbAccessoryConnection()

        if core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox_enabled'] and \
            ( self.getName() == "Main" or self.isFollower() ) :
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

        if self.getName() != "Main":
            return super(GraniteServerInterface, self)._blackBoxResetPhonePower()

        if not core.FW_conf['settings'].TestRun.AllowPhoneReset:
            message = self.getName()
            if self.isFollower():
                message += ' phone power reset is needed but reset is not allowed in Follower'
            else:
                message += ' phone reset is needed but reset is not allowed. Execution is on hold'
            core.FW_conf['mail_sender'].holdExecutionAndSendMail(message, subject='GRANITE EXECUTION ON HOLD')
            return

        # if reset in follower mode, do not create connection, just reset
        if core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox_enabled'] and self.isFollower():
            debug.brf('BlackBox: Reset phone power in blackbox mode...')
            self.sendWaitMessageToGraniteGUI(300, 'Resetting phone power')
            core.FW_conf['blackbox'].resetPhonePower()
        
    def __blackBoxResetPhoneUsbConnection(self):
        return super(GraniteConnectionInterface, self).__blackBoxResetPhoneUsbConnection()

    def setResult(self, result):
        """ Set result instance for phone. Result is needed for adding comments to report

        """
        self.result = result

    def _clearStillImageArray(self):
        """ Clears the image array of video stream images. Called when test case is stopped. """
        self._capturedStillImages = []

    def __setFileAccessMethods(self):
        """Creates self.file class which has all needed file operation methods from connection_interface.py

            internal parameter is set to False so that actions will be added to test report.
        """
        class fileAccess(object):
            def __init__(self, phone):
                self.phone = phone

            def createFile(self, localData, phoneFilePath):
                self.phone.createFile(localData, phoneFilePath, internal = False)

            def createFolder(self, phoneFolderPath):
                self.phone.createFolder(phoneFolderPath, internal = False)

            def fileExists(self, targetFilePath):
                return self.phone.fileExists(targetFilePath, internal = False)

            def getAttribute(self, phoneItemPath):
                return self.phone.getAttribute(phoneItemPath, internal = False)

            def getFolderContent(self, phoneFolderPath, recursive = True):
                return self.phone.getFolderContent(phoneFolderPath, recursive, internal = False)

            def readFile(self, phoneFilePath, localFilePath):
                return self.phone.readFile(phoneFilePath, localFilePath, internal = False)

            def setAttribute(self, phoneItemPath, itemAttribute):
                self.phone.setAttribute(phoneItemPath, itemAttribute, internal = False)

            def getAvailableFreeSpace(self, drive):
                return self.phone.getAvailableFreeSpace(drive, internal = False)

            def fill(self, path, freemem = 0, filesize = 10):
                return self.phone.fill(path, freemem, filesize, internal = False)

            def hasMemoryCard(self):
                return self.phone.hasMemoryCard(internal = False)

            def removeFile(self, phoneFilePath, forced = False):
                self.phone.removeFile(phoneFilePath, forced, internal = False)

            def removeFolder(self, phoneFolderPath, forced = False):
                self.phone.removeFolder(phoneFolderPath, forced, internal = False)

            def removeItem(self, phoneItemPath, forced = False):
                self.phone.removeItem(phoneItemPath, forced, internal = False)

            def removeItems(self, phoneFolderPath, recursive = True, forced = False):
                self.phone.removeItems(phoneFolderPath, recursive, forced, internal = False)

            def fillMemory(self,drive, free):
                """
                    Fills phone memory. Free space amount can be set with a parameter.

                    Note that you need to delete files after test case is run.

                    Parameters:
                        drive   e.g. 'c' or 'e'
                        free    Free memory after fill memory operation.

                    Usage:
                        files = self.file.fillMemory('c', 1024*5)
                        for file in files:
                            self.file.removeFile(file)

                """
                self.phone.comment('fillMemory(%s, %s)' % (drive, free))

                files = []
                freeMem = self.phone.getAvailableFreeSpace(drive)

                freeMem -= free # subtract the amount of wanted free space

                phoneFolder = 'C:\predeftemp'
                if 'drive' != 'c':
                    phoneFolder = drive + ':\\'

                tempFolder = tempfile.mkdtemp()

                # how many big files are needed
                numberOfTempFiles = int(freeMem / 10485760) # 10MB files

                #size of the last file
                lastFileSize = freeMem % 10485760 # 10*1024*1024 bytes

                if numberOfTempFiles > 0:
                    fileName = os.path.join(tempFolder, 'tempfile0.dat')

                    tempFile = open(fileName, 'w')
                    for i in range(10485760):
                        tempFile.write('X')
                    tempFile.close()

                    for i in range(numberOfTempFiles):
                        self.createFile(fileName, os.path.join(phoneFolder, "tempfile%i.dat" % i))
                        files.append(os.path.join(phoneFolder, "tempfile%i.dat" % i))
                    os.remove(fileName)

                if lastFileSize > 0:
                    fileName = os.path.join(tempFolder, 'lastTemp.dat')
                    tempFile = open(fileName, 'w')

                    for i in range(lastFileSize):
                        tempFile.write('X')
                    tempFile.close()

                    self.createFile(fileName, os.path.join(phoneFolder, "tempfile%i.dat" % (numberOfTempFiles+1)))
                    files.append(os.path.join(phoneFolder, "tempfile%i.dat" % (numberOfTempFiles+1)))
                    os.remove(fileName)

                freeMem = self.phone.getAvailableFreeSpace(drive)

                self.phone.comment("Drive %s has %i bytes of free memory after fillMemory operation" %(drive, freeMem))
                return files

        self.file = fileAccess(self)

    def writeNokiaProvisioningSettings(self):
        """Writes NTN/BTN provisioning settings to all sims in the phone."""
        try:
            self.__provManager.writeFromJsonFileToDefinedSims(self)
        except Exception, err:
            debug.err('Error in writing NTN provisioning settings: %s' % str(err))

    def writeProvisioningSettings(self, provSettingsFile, sim = 'all'):
        """Writes given provisioning settings to defined sims in the phone.

            Parameters

            provSettingsFile            provisioning settings json file path
            sim                         1, 2 or 'all'
        """
        self.__provManager.writeFromJsonFileToDefinedSims(self, provSettingsFile, sim)

    def capture(self, name=None, screen=None,savePath=None, onlyImage=False):
        """ Take screen capture from phone

        Parameters:
            name        :   Name of the test step in test report
            screen      :   Number of display to capture
            savePath    :   Path where bitmap will be copied
            onlyImage   :   Set to True if xml-dump is not needed

        """
        if name == 'capture from failure':
            self.comment('capture() from failure')
        else:
            self.comment('capture()')

        if not name:
            name = 'capture screen content'

        # different interface for tab
        self.__capture(name, screen, savePath=savePath, onlyImage=onlyImage)

        # savePath must be returned
        if not savePath:
            if self._name!='Main':
                resultDir = os.path.join(core.FW_conf['test_result_dir'],self._name)
            else:
                resultDir = core.FW_conf['test_result_dir']
            savePath = os.path.join(resultDir,'captured bitmaps')
        from interfaces.wbxml_parser import captureIndex
        return os.path.join(savePath, "capture_%s.png" % str(captureIndex))

    def sx(self, sxCommand, convertToString=False, doNotReport=False, timeout=None):
        """Execute sx script."""
        # if test execution is aborted, don't run any SX anymore
        if core.FW_conf['should_stop']:
            return None

        if not self.uiEnabled():
            debug.err("SX execution not enabled in non UITestCase based testcase")
            return None

        if self.isFollower():
            debug.vrb('SX call: Follower mode, return')
            return

        internalSXCommands = [\
           'menu', 'dump',
           '(send (get-image-metadata) get-data)',
           'get-granite-image-metadata',
           'get-granite-text-metadata',
           '(send config-manager get-setting',
           '(send config-manager set-setting',
           '(send config-manager delete-setting',
           '(application-invoke',
           '(send primary-root-container get-children-by-type',
           '(send (send (get-app-manager) get-topmost-application) kill)',
           '(get-meta-icon-name',
           '(send (send (get-input-locale-manager) get-current-locale) get-iso)',
           '(send (get-text-editor-manager) get-edit-mode)',
           '(send (send (send (send primary-root-container get-focused) get-focused) get-focused) is-textinput)',
           '(send lcdmanager get-orientation)',
           '(send sensor-manager submit-rotation',
           self.uiState.vkb.getStatusSxString,
           self.uiState.vkb.getLocaleFeaturesString]

        self.__purgeKeyPresses()
        self.__purgeExpectedItems()

        # check whether sx command is a file in PC
        try:
            if os.path.isfile(sxCommand):
                # use sxUtils for getting sx file content
                sxCommand = self.sxUtils.ReadFromLocalFile(sxCommand)
        except Exception, err:
            debug.err('SX file existence check failed: %s' % str(err))

        if convertToString:
            sxCommand = "(send %s ->string)"%sxCommand

        sxProp = NodeUtils('<sx>%s</sx>' % escape(sxCommand))
        self.teststep.append(sxProp)

        # set timeout if given
        if timeout:
            self.teststep['timeout'] = timeout

        # put sx command to report
        if not True in [x in sxCommand for x in internalSXCommands] and not doNotReport:
            self.comment('sx(%s)' % sxCommand)

        # NOTE: Take this back into use when all problems with display update ntfs are fixed
        #if sxCommand == 'dump':
            # Set uiChanged to False only when server sends ntf-messages from ui updates
        #    if self.server_version['yyy'] >= 5 and core.FW_conf['settings'].System.DisplayUpdateNtfsInUse:
        #        self.uiState.setUIChanged(False)

        result = self._run('run sx: "%s"' % sxCommand, testStepReporting = False)

        if result.has_key(''):
            if result[''] == None or len(result['']) == 0:
                return None
            if isinstance(result[''][0], NodeUtils):
                responseNode = result[''][0]

                # return NodeUtils instance for commands that return XML
                if responseNode.getChildNodes():
                    return responseNode
                else:
                    if responseNode['text']:
                        return responseNode['text']
                    else:
                        return ""
        else:
            return None

    def comment(self, comment):
        """Add comment to the test result.

        FIXME: Replace 'comment' attribute with '*comments'
        """

        if not isinstance(comment, basestring):
            comment = str(comment)

        # Remote phone comment
        if self._name != 'Main':
            comment = self._name + " : " + comment

            if self.result:
                # clear current test step for performance measuring
                self.result.clearCurrentTestStep()

        debug.brf(comment)
        if core.FW_conf['blackbox'] != None and core.FW_conf['blackbox'].isVideoRecorderAvailable():
            core.FW_conf['blackbox'].videoRecording_SetText(comment)

        if self.result:
            # FIXME: Remove list approach from addStepComment
            comment = [comment]
            self.result.addStepComment(comment)

    def __capture(self, name=None, screen=None, onlyItems=False, savePath=None,onlyImage=False):
        """Add capture tag into teststep"""
        self.__purgeKeyPresses()
        self.__purgeExpectedItems()

        sxProp = NodeUtils('<sx>dump</sx>')
        capture = NodeUtils('capture', makeNewNode = True)

        if screen: capture['screen'] = screen
        if savePath: capture['save'] = savePath

        #if items:
        #    capture['items'] = items
        if not name:
            name = 'capture_%u' % (self.__captureNameIndex)

        self.__captureNameIndex += 1
        capture['name'] = name
        # Take in use when support more than 1 display.
        #if len([ x for x in display if x > 0]) > 0:
        #    capture.root.setAttribute('displays', '%s' % \
        #            ','.join([str(x) for x in displays if x > 0]))

        # no need for SX dump when in capture display mode
        if not onlyImage:
            self.teststep.append(sxProp)

        # no need for bitmap capture when only items
        if not onlyItems:
            self.teststep.append(capture)

        self._run(name)

    def captureItems(self, name=None, screen=None):
        # FIXME: Test report is not showing items when image is not included
        self.comment('captureItems()')

        if not name:
            name = 'capture items'

        self.__capture(name, screen, True)

    def _initTestStep(self):
        """Initialize new test step."""
        self.teststep = NodeUtils('teststep', makeNewNode = True)

        self.__expectTimeout = core.FW_conf['settings'].System.ExpectTimeout
        self.__expectLength = core.FW_conf['settings'].System.ExpectLength
        self.__expectWait = core.FW_conf['settings'].System.ExpectWait

        self.expectedItems = []
        self.keyPresses = []

        self.__teststepConfiguration()

    def __teststepConfiguration(self):
        """Generate config-block."""
        config = NodeUtils('config', makeNewNode = True)

        config['max_isi_data_length'] = core.FW_conf['decoder_isi_length']
        config['bitmap_capture'] = 'yes'

        # str needed, because values are encoded from string in wbxml_encoder.py
        config['keypress_wait'] = '100'
        config['keypress_length'] = '100'

        ## enable display update ntf sending if server version is new enough and setting is enabled
        #if self.server_version and core.FW_conf['settings'] != None and \
        #   self.server_version['yyy'] >= 5 and (core.FW_conf['settings'].System.DisplayUpdateNtfsInUse or core.FW_conf['settings'].TestRun.PerformanceTesting):
        #    config['ntf_sending'] = 'yes'

        self.teststep.append(config)

    def __purgeKeyPresses(self):
        """Generate key_in-block with required keypress-elements."""

        if self.keyPresses:

            try:
                key_in = NodeUtils('key_in', makeNewNode = True)

                for keypress in self.keyPresses:
                    key_in.append(keypress)

                self.teststep.append(key_in)

            finally:
                self.keyPresses = []

    def __purgeExpectedItems(self):
        """Generate expect-block with display blocks."""
        if self.expectedItems:
            try:
                expect = NodeUtils('expect', makeNewNode = True)
                expect['timeout'] = self.__expectTimeout
                if self.__expectLength: expect['length'] = self.__expectLength
                if self.__expectWait: expect['wait'] = self.__expectWait

                for name, layoutName, items in self.expectedItems:
                    display = NodeUtils('display', makeNewNode = True)
                    display['name'] = name
                    if len(layoutName) != 0 and layoutName[0] != None:
                        display['layoutName'] = ', '.join(layoutName)

                    for item in items:
                        if len(layoutName) > 1:
                            display.append(item)
                        else:
                            for attribute in item.getAttributes():
                                if attribute == 'layoutName':
                                    item.removeAttribute(attribute)

                            display.append(item)

                    expect.append(display)

                self.teststep.append(expect)
            finally:
                self.expectedItems = []

    def delay(self, delayInMS, testStepReporting = True):
        """Stop test step execution for given time (milliseconds).

            The delay is executed by the Granite server.
        """
        assert type(delayInMS) == types.IntType, \
            'parameter for delay must be integer!'

        if testStepReporting:
            self.comment('delay(%s)' % delayInMS)

        #self.__purgeKeyPresses()
        #self.__purgeExpectedItems()

        #delay = NodeUtils('<delay wait="%s"/>' % delayInMS)
        #self.teststep.append(delay)
        #
        #self._run('wait for %s ms' % delayInMS, testStepReporting = testStepReporting)

        # call sleep from delay
        # FIXME: remove this when sleep method is removed
        self.sleep(delayInMS, calledFromDelay = True)

    def sleep(self, sleepInMS, calledFromDelay = False):
        """Sleep during test step execution for given time (milliseconds).

            The sleep is done with time.sleep and all communication with the phone is in halt during that time.
        """
        assert type(sleepInMS) == types.IntType, \
            'parameter for sleep must be integer!'

        if not calledFromDelay:
            self.comment('sleep(%s)' % sleepInMS)
            self.warn('self.sleep method is deprecated, please use self.delay instead!')

        if sleepInMS < 1000:
            sleepInSeconds = float(sleepInMS) / 1000
        else:
            sleepInSeconds = sleepInMS / 1000

        self.sendWaitMessageToGraniteGUI(sleepInSeconds, 'Test execution sleeping for %s seconds' % sleepInSeconds)

        time.sleep(sleepInSeconds)

    def _releaseKey(self, key, wait=None):
        """Release holded key."""
        self.__pressKeyHelper(key, wait=wait, releaseKey=1)

    def _pressKey(self, key, length=None, repeat=None, wait=None, hold=None,
                 releaseKey=None, killTimeOut=True, repeatLength=None,
                 longPressLength=None, shortPressLength=None, keysIdleLength=None):
        """Presses a key.

        Usage

           key             the name of the key, mandatory
                           (type=String)

           length          the length of key press
                           (type=Integer, default=None)

           repeat          the number of key presses
                           (type=Integer, default=None)

           wait            the wait time of key press
                           (type=Integer, default=None)

           hold            hold key
                           (type=Boolean, default=None)

           releaseKey      release key
                           (type=Boolean, default=None)

           killTimeOut     kill multitap timeout with scroll key
                           (type=Boolean, default=True)

           repeatLength    the length of repeat
                           (type=Integer, default=None)

           longPressLength the length of long press
                           (type=Integer, default=None)

           shortPressLength the length of short key event
                           (type=Integer, default=None)
                            short event will not be sent, if it hasn't been
                            given.

           keysIdleLength   the length of idle key event
                           (type=Integer, default=None)
                            idle event will not be sent, if it hasn't been
                            given.
        """
        #FIXME: Prohibit using this from test script level!

        self.__purgeExpectedItems()
        uiKey = ''
        if repeat == 1: repeat = None

        if not type(key) in [types.StringType, types.UnicodeType]:
            raise KeyError('Invalid key (%s) given!' % str(key))

        if hold and releaseKey:
            self.fail("Can't hold and release keys simultaneously!")

        if key.startswith('KBD_KEY') or key.startswith('KEYCODE'):

            # convert KEYCODE_ to KBD_ for HW and Remote phone
            if key.startswith('KEYCODE'):
                if key == 'KEYCODE_BACK':
                    key = 'KBD_KEY_BACK'
                elif key == 'KEYCODE_POWER':
                    key = 'KBD_KEY_KEYLOCK_TOGGLE'
                elif key == 'KEYCODE_VOLUME_DOWN':
                    key = 'KBD_KEY_VOL_DOWN'
                elif key == 'KEYCODE_VOLUME_UP':
                    key = 'KBD_KEY_VOL_UP'

            keyCode = {'key':key}

            k = NodeUtils('keypress', makeNewNode = True)

            if releaseKey or hold:
                k = self.__handleKeyHoldAndRelease(k, keyCode, releaseKey, hold)
            k['key'] = keyCode['key']
            if length:
                k['length'] = length
            if repeat: k['repeat'] = repeat
            if wait:
                k['wait'] = wait
            elif keyCode['key']=='KBD_KEY_END':
                k['wait'] = 150
            if longPressLength:
                k['long_press_length'] = longPressLength
            if repeatLength:
                k['repeat_length'] = repeatLength
            if shortPressLength:
                k['short_press_length'] = shortPressLength
            else:
                # put short press length to volume up key
                # NOTE: 250 ms is the default value, but short
                #       event has effect only with values 50 and
                #       below
                # FIXME: use the key specific value
                if keyCode['key'] == 'KBD_KEY_VOL_UP':
                    k['short_press_length'] = 50

            if keysIdleLength:
                k['keys_idle_length'] = keysIdleLength

            self.keyPresses.append(k)
        else:
            raise KeyError('Invalid key (%s) given!' % str(key))

    def __handleKeyHoldAndRelease(self, keyTag, keyCode, releaseKey, hold):
        """Function for handling the holding and releasing of keys."""
        if releaseKey:
            # check that key is on hold before releasing
            if keyCode['key'] in self.keysOnHold:
                keyTag['action'] = 'release'
                self.keysOnHold = []
            else:
                self.warn(\
                "%s can't be released, because it's not " \
                "on hold." % keyCode['key'])
        if hold:
            # check that no other keys are on hold
            if not self.keysOnHold:
                keyTag['action'] = 'hold'
                self.keysOnHold.append(keyCode['key'])
            else:
                self.__checkIfKeysAreOnHold(keyPressed=True)

        return keyTag

    def __checkIfKeysAreOnHold(self, keyPressed=None):
        """Check that keys aren't left on hold when they should have been released.

           keyPressed is True if function from a press key related function
        """
        # check that there's not any key on hold
        # if there is, generate a warning
        if self.keysOnHold:
            if keyPressed:
                self.warn(\
                    "%s was left on hold before pressing a key. " \
                    "Holded key was automatically released." \
                    % self.keysOnHold[0])
                self.keysOnHold = []
            else:
                self.warn(\
                    "%s was left on hold in the end of the test case's " \
                    "tearDown. Holded key was automatically released." \
                    % self.keysOnHold[0])
                self.keysOnHold = []
                # press 'end' - key twice in tearDown to release holded key
                self._pressKey('end', repeat = 2)
                self._run('Press end key twice to release holded key')

    def _timeout(self, length=None):
        """Purge both keypress and expected-buffers."""
        self.__purgeKeyPresses()
        self.__purgeExpectedItems()

    def _setExpectTimes(self, timeout=None, length=None):
        """Set timeout and/or length of next expectXXXX blocks.

            These values are automatically restored to their default values
            in the beginning of the next test step.
        """
        if timeout: self.__expectTimeout = timeout
        if length: self.__expectLength = length

    def __disableSecurityLock(self):
        try:
            result = self.sx('''(begin
(when (string=? (send (get-phone-lock-manager) get-state) "phone-lock-enabled")
(send (get-phone-lock-manager) disable "25057")
else
    "false"
)
)
''', doNotReport  = True)
            if result != "false":
                self.comment("Phone lock security code disabled")
        except:
            debug.err('Failed to disable phone security lock!')

    def _expectText(self, textProperties, zoneData=None, font=None,
                   highlighted=None, valid=None, truncated=None,
                   zoneName=None, layoutName=None, screen=1,
                   dimmed=None, expandZone=0, wildcard=None,
                   relativeLayout=None,background=None):
        self.__purgeKeyPresses()
        #if d_product.FEA._touch_UI:
        #    highlighted=None
        if type(textProperties) != types.ListType:
            textProperties = [textProperties]

        for text in textProperties:
            #if isinstance(text, Properties):
            #    text = text.propertiesToNodeUtils() # Leave original alone..
            #
            #    self.expectedItems[-1][2].append(text)
            #    return # FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            if isinstance(text, NodeUtils):
                text = text.clone() # Leave original alone..
            else:
                text = self.__toTextTag(text)

            text.setName('text')    # set node name

            if 1: # 0 = old, 1 = new
                # NOTE: this block may be removed in future versions
                # when the server is fixed
                if not text['text']:
                    text['text'] = "?*"
                    if valid == 'no':
                        valid = None
                    else:
                        valid = 'no'
                    wildcard = None

            # Filter out special characters when server version
            # is 3.5.5 (7.2 branch) or 3.6.1 (R&D) or higher
            # FIXME: Remove this when permanent solution is available
            #if c_srv.GraniteServerVersion >= 3.005005 and text['text']:
            #    text['text'] = \
            #        text['text'].replace(u"\N{NOMINAL DIGIT SHAPES}", '').\
            #                     replace(u"\N{NATIONAL DIGIT SHAPES}", '').\
            #                     replace(u"\N{LEFT-TO-RIGHT MARK}", '').\
            #                     replace(u"\N{RIGHT-TO-LEFT MARK}", '').\
            #                     replace(u"\N{LEFT-TO-RIGHT EMBEDDING}", '').\
            #                     replace(u"\N{RIGHT-TO-LEFT EMBEDDING}", '').\
            #                     replace(u"\N{LEFT-TO-RIGHT OVERRIDE}", '').\
            #                     replace(u"\N{RIGHT-TO-LEFT OVERRIDE}", '')

            if type(zoneName) == type("") and type(layoutName) == type("") and zoneData is None:
                text['zoneName'] = zoneName
                text['layoutName'] = layoutName
                zoneData = layouts.getZone(layoutName, zoneName, expandZone, relativeLayout)

            elif zoneData is not None:
                text['zoneName'] = None
                text['layoutName'] = None

            if zoneData: # (x, y, width, height)
                if not (isinstance(zoneData, tuple) or isinstance(zoneData, list)):
                    zoneData = eval(zoneData)
                if not zoneData[0] is None:
                    text['x'] = zoneData[0]
                if not zoneData[1] is None:
                    text['y'] = zoneData[1]
                if not zoneData[2] is None:
                    text['width'] = zoneData[2]
                if not zoneData[3] is None:
                    text['height'] = zoneData[3]

            if font: text['font'] = font
            if highlighted: text['highlighted'] = highlighted
            if valid == 'no': text['valid'] = 'no'
            if truncated: text['truncated'] = truncated
            if dimmed: text['dimmed'] = dimmed
            if screen: text['screen'] = screen
            if wildcard: text['wildcard'] = wildcard
            if background: text['background'] = background

            # Make sure we have a display defined
            if len(self.expectedItems) == 0:
                self._setupDisplay('default', layoutName)
            else:
                if layoutName:
                    if not self.expectedItems[-1][1][0]:
                        self.expectedItems[-1][1][0] = layoutName
                    elif layoutName not in self.expectedItems[-1][1]:
                        self.expectedItems[-1][1].append(layoutName)

            # Add item to the last display-element:
            # (tuple: [0]=name, [1]=display layoutName, [2]=display items)
            self.expectedItems[-1][2].append(text)

    def _expectAnimation(self, animationProperties=None, animationId=None, zoneData=None,
                        highlighted=None, valid=None, zoneName=None,
                        layoutName=None, screen=1, expandZone=0,
                        relativeLayout=None, background=None, dimmed=None):

        self.__purgeKeyPresses()

        #if d_product.FEA._touch_UI:
        #    highlighted=None
        assert animationProperties is not None, \
            "UITestCase : expectAnimation : animationProperties should be given"

        if not animationProperties:
            animationProperties = ['']

        if type(animationProperties) != types.ListType:
            animationProperties = [animationProperties]
        for animation in animationProperties:
            #if isinstance(animation, Properties):
            #    animation = animation.propertiesToNodeUtils()
            if isinstance(animation, NodeUtils):
                animation = animation.clone()
            elif isinstance(animation, str) or isinstance(animation, unicode):
                animation = NodeUtils('<animation>%s</animation>' % animation)
            else:
                if animation.find('<') == -1:
                    animationName = animation
                    animation = '<animation name="%s"/>' % animation
                animation = NodeUtils(animation)

            #if animation['text']:
            #    animation['name'] = animation['text']
            #    del animation['text']

            #if animation['name']:
            #    try:
            #        animation['animation_id'] = str(getattr(\
            #            d_product.ANIMATIONS, animation['name'].upper()))
            #    except AttributeError:
            #        self.fail('Animation was not found: "%s"' % animation['name'])
            #elif not animation['animation_id']:
            #    del animation['name']
            #    animation['animation_id'] = 0 # the Granite server needs this!

            if type(zoneName) == type("") and type(layoutName) == type("") and zoneData is None:
                animation['zoneName'] = zoneName
                animation['layoutName'] = layoutName
                zoneData = layouts.getZone(layoutName, zoneName, expandZone, relativeLayout)
            elif zoneData is not None:
                animation['zoneName'] = None
                animation['layoutName'] = None

            if zoneData:
                if not (isinstance(zoneData, tuple) or isinstance(zoneData, list)):
                    zoneData = eval(zoneData)
                if not zoneData[0] is None:
                    animation['x'] = zoneData[0]
                if not zoneData[1] is None:
                    animation['y'] = zoneData[1]
                if not zoneData[2] is None:
                    animation['width'] = zoneData[2]
                if not zoneData[3] is None:
                    animation['height'] = zoneData[3]

            if highlighted: animation['highlighted'] = highlighted
            if valid == 'no': animation['valid'] = 'no'
            if screen: animation['screen'] = screen
            if background: animation['background'] = background
            if dimmed: animation['dimmed'] = dimmed

            # Make sure we have a display defined
            if len(self.expectedItems) == 0:
                self._setupDisplay('default', layoutName)
            else:
                if layoutName:
                    if not self.expectedItems[-1][1][0]:
                        self.expectedItems[-1][1][0] = layoutName
                    elif layoutName not in self.expectedItems[-1][1]:
                        self.expectedItems[-1][1].append(layoutName)

            # Add item to the last display-element:
            # (tuple: [0]=name, [1]=display layoutName, [2]=display items)
            self.expectedItems[-1][2].append(animation)

    def __toTextTag(self, text):
        try:
            textTag = NodeUtils(text)
        except (AssertionError, SAXParseException, TypeError, UnicodeEncodeError):
            textTag = NodeUtils('text', makeNewNode = True)

            if type(text) != types.UnicodeType:
                try:
                    text = unicode(text, 'Latin-1')
                except UnicodeError, e:
                    assert 0,'%s: %s' % (e, repr(text))

            textTag['text'] = text

        return textTag

    def expectReset(self, timeout = 30, writeProv=True):
        """Method for verifying phone's reset. Checks that Granite server is
           in inactive state after given timeout. If no, raises TestException.

            Parameters

                timeout     timeout in which phone reset is expected to occur
                            (default: 30 seconds)
                writeProv   Set to false if Granite must not overwrite provisioning settings
        """
        assert type(timeout) == types.IntType, \
            'timeout parameter must be integer!'

        # send wait message to Granite GUI
        commentText = 'expectReset(%s)' % timeout
        self.sendWaitMessageToGraniteGUI(timeout, commentText)
        # and add comment to test report
        self.comment(commentText)

        # sleep for given timeout
        time.sleep(timeout)

        # ensure connection
        self.ensureConnection()

        # verify Granite server's status
        status = None
        for counter in range(5):
            status = self.getStatus()

            if status:
                break
            else:
                if counter < 4:
                    debug.err('Getting Granite server status failed. Trying '
                              'again...')
                    # send wait message to Granite GUI
                    self.sendWaitMessageToGraniteGUI(15,
                        'Getting Granite server status in expectReset...')
                    time.sleep(5)
                else:
                    raise TestException("expectReset: Getting Granite server's "
                                        "status failed!", self)

        if status != 'idle':
            # put Granite server back to idle with clear request
            self.clearGraniteServer()

        if writeProv:
            self.writeNokiaProvisioningSettings()

        if status != 'inactive':
            self.fail("Phone didn't reset when expected")

    def waitForReconnection(self, timeout = 30):
        """Method for waiting until phone connection is restored.

            Parameters

                timeout     timeout how long we wait until connection will be restored
                            (default: 30 seconds)
        """
        assert type(timeout) == types.IntType, \
            'timeout parameter must be integer!'

        # send wait message to Granite GUI
        commentText = 'waitForReconnection(%s)' % timeout
        self.sendWaitMessageToGraniteGUI(timeout, commentText)
        # and add comment to test report
        self.comment(commentText)

        # sleep for given timeout
        time.sleep(timeout)

        # ensure connection
        self.ensureConnection()

        if not self._activatingGraniteServer:
            # activate Granite server
            self.activateGraniteServer(forced = True)

        # put Granite server back to idle
        self.clearGraniteServer()

        # go back to idle (handles also usb-manager killing)
        self.exit()

    def addId(self, element):
        """Add id number(running number) all teststep tags"""
        if element.getName() == 'teststep':
            self.__id += 1
            element['id'] = str(self.__id)

        if element.getChildNodes():
            for child in element.getChildNodes():
                self.__id += 1
                child['id'] = str(self.__id)
                self.addId(child)

    def __checkExpects(self):
        expectList = self.teststep.findall('expect')
        for expect in expectList:
            if 'timeout' not in expect.getAttributes():
                expect['timeout'] = '5000'

    def _setupDisplay(self, displayName, layoutName=None):
        """Setup new display inside same expect block.

           Name of the matched display will be returned from the run-method.
        """
        self.expectedItems.append((displayName, [layoutName], []))

    def _launchApp(self, appTitle):
        """Launch application with its uri.

            Parameters

            appTitle        SP application name (e.g. "Contacts")

            Returns True if application was launched, False if not.
        """
        assert self.menu, 'Launching applications require menu xml!'

        appNode = self.menu.find('//item[@title="%s"]' % appTitle)
        if not appNode:
            appNode = self.menu.find('//setting[@title="%s"]' % appTitle)

        if appNode:
            if appNode['uri']:
                sxResp = self.sx('(application-invoke \"%s\")' % appNode['uri'])

                if sxResp is None or 'error' in sxResp:
                    return False
                else:
                    return True
            else:
                #debug.err("Application doesn't have uri in menu xml!")
                return False
        else:
            raise TestException('Application "%s" not found from menu xml!' % appTitle, self)

    def getMenu(self):
        """Get menu xml from the the phone with SX."""
        if self.getConnectionBusName() == 'TCP':
            self.menu = self.sx(self.product_name.startswith('Aqua') and self._GraniteSX.MENU_FOR_SIMULATION or self._GraniteSX.MENU_FOR_SIMULATION_2, doNotReport = True)
        else:
            self.menu = self.sx('menu', doNotReport = True)

        # if menu xml is not valid, use static one from data folder
        if not self.menu or not isinstance(self.menu, NodeUtils) or not self.menu.find('//mainmenu'):
            self.warn("Could not generate menu xml! Using static menu from %s" % os.path.join(core.FW_conf['startup_path'], 'core\\data\\aqua_ds_menu.xml'))
            self.menu = NodeUtils(\
                os.path.join(core.FW_conf['startup_path'], 'core\\data\\aqua_ds_menu.xml'))

        # remove category items from settings branch
        # FIXME: Remove this temporary code block when menu xml SX script has been corrected
        settingsNode = self.menu.find('//item[@id="nP6YDmTdaqE2U0eXQBadWwg"]')

        # create clone from settings node
        newSettingsNode = settingsNode.clone()
        firstSettingsNode = newSettingsNode.first()
        newSettingsNode.remove(firstSettingsNode)

        # go through settings items and remove non-category category items. Thus flattening the settings menu
        for settingNode in firstSettingsNode.findall('//*'):
            # Connections, Personalisation, General, Apps and unclassified are not real category items
            if (settingNode.getAttribute('type') != 'category') or \
                (settingNode.getAttribute('type') == 'category' and \
                ((not settingNode.getAttribute('title-string-id') in \
                ['nB2nzrzzqnRXUi4XXpaQbwO', 'nqsYitlTLZE6IwHOKQs6RGg',
                'nKK1EQWPsu0yMrB4aNQ3zag', 'n2CoiuOmZm0qSEwLpSqL5ZQ']) and \
                (not 'unclassified' in settingNode.getAttribute('title-string-id')))):
                newSettingsNode.append(settingNode)

        # replace original settings node with the new one
        settingsNode.parent().replaceChild(settingsNode, newSettingsNode)

        # copy to module variable
        # FIXME: remove this when it's no longer in use
        #uitestcase.menuXml = self.menu

    def compareImage(self, expectedImage, maxDifference=2.0, timeout=None):
        """ Compare current display to image or series of images created with
            Display Image Comparer activity in Granite Studio

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

                        # The Granite framework processes this test failure
                        message = "The phone display image does not match the '%s' reference image."% refImageName
                        self.fail(message)

                        #Code ported from DisplayImageComparer-activity ends here
                else:
                    continue

                # New report xml starts here
                '''
                with  Bitmap.FromFile(referenceImagesList[indexCompared]) as referenceImage:
                    # Draw the masks on the reference image
                    ImageComparer.DrawMasks(referenceImage)

                    # Save the reference image with the masks drawn
                    referenceImageWithMasksFilePath = Path.Combine(Path.GetDirectoryName(displayImageFilePath), Path.GetFileNameWithoutExtension(displayImageFilePath) + "_reference" + Path.GetExtension(displayImageFilePath))
                    referenceImage.Save(referenceImageWithMasksFilePath, ImageFormat.Png)

                    # If the images match
                    if resultCompared == True:
                        # Generate the test case report information containing each of the images
                        # Create a test step for the image comparison\
                        teststep = NodeUtils('teststep', makeNewNode = True)
                        teststep['name'] = 'Display image comparison teststep'

                        # Create a displayimagecomparison
                        displayimagecomparison = NodeUtils('displayimagecomparison', makeNewNode = True)
                        displayimagecomparison['name'] = 'Display image comparison'
                        displayimagecomparison['result'] = 'Passed'

                        # Add the actual image
                        actualImage = NodeUtils('image', makeNewNode = True)
                        actualImage['name'] = 'Actual image'
                        actualImage['type'] = 'ActualImage'
                        actualImage['filename'] = '" + Path.GetFileName(displayImageFilePath) + "'
                        displayimagecomparison.append(actualImage)

                        # Add the reference image
                        referenceImage = NodeUtils('image', makeNewNode = True)
                        referenceImage['name'] = '\\' + expectedImage + "\\' " + indexString + " reference image"
                        referenceImage['type'] = 'ReferenceImage'
                        referenceImage['filename'] = '" + Path.GetFileName(referenceImageWithMasksFilePath) + "'
                        displayimagecomparison.append(referenceImage)

                        teststep.append(displayimagecomparison)

                        # Add the test step to the test case report
                        self.result.tcReport.append(teststep)

                        # Log a comment
                        message = ("The phone display image matches the '%s' %s reference image."% (ReferenceImage, indexString))
                        self.comment(\"%s\")"% message)
                    else:
                        # Save the image showing the differences
                        string differenceImageFilePath = Path.Combine(Path.GetDirectoryName(displayImageFilePath), Path.GetFileNameWithoutExtension(displayImageFilePath) + "_difference" + Path.GetExtension(displayImageFilePath))
                        differenceImage.Save(differenceImageFilePath, ImageFormat.Png);

                        // Generate the test case report information containing each of the images
                        ironPythonCode = "# Create a test step for the image comparison\n" +
                                            "teststep = NodeUtils('teststep', makeNewNode = True)\n" +
                                            "teststep['name'] = 'Display image comparison teststep'\n" +
                                            "\n" +
                                            "# Create a displayimagecomparison\n" +
                                            "displayimagecomparison = NodeUtils('displayimagecomparison', makeNewNode = True)\n" +
                                            "displayimagecomparison['name'] = 'Display image comparison'\n" +
                                            "displayimagecomparison['result'] = 'Failed'\n" +
                                            "\n" +
                                            "# Add the actual image\n" +
                                            "actualImage = NodeUtils('image', makeNewNode = True)\n" +
                                            "actualImage['name'] = 'Actual image'\n" +
                                            "actualImage['type'] = 'ActualImage'\n" +
                                            "actualImage['filename'] = '" + Path.GetFileName(displayImageFilePath) + "'\n" +
                                            "displayimagecomparison.append(actualImage)\n" +
                                            "\n" +
                                            "# Add the difference image\n" +
                                            "diffrenceImage = NodeUtils('image', makeNewNode = True)\n" +
                                            "diffrenceImage['name'] = 'Image showing differences with the reference image'\n" +
                                            "diffrenceImage['type'] = 'DifferenceImage'\n" +
                                            "diffrenceImage['filename'] = '" + Path.GetFileName(differenceImageFilePath) + "'\n" +
                                            "displayimagecomparison.append(diffrenceImage)\n" +
                                            "\n" +
                                            "# Add the reference image\n" +
                                            "referenceImage = NodeUtils('image', makeNewNode = True)\n" +
                                            "referenceImage['name'] = '\\'" + expectedImage + "\\' " + indexString + " reference image'\n" +
                                            "referenceImage['type'] = 'ReferenceImage'\n" +
                                            "referenceImage['filename'] = '" + Path.GetFileName(referenceImageWithMasksFilePath) + "'\n" +
                                            "displayimagecomparison.append(referenceImage)\n" +
                                            "\n" +
                                            "teststep.append(displayimagecomparison)" +
                                            "\n" +
                                            "# Add the test step to the test case report\n" +
                                            "self.result.tcReport.append(teststep)\n";

                        client.ExecuteIronPythonCode(ironPythonCode);

                        // The Granite framework processes this test failure
                        string message = string.Format("The phone display image does not match the '{0}' reference image.", ReferenceImage);
                        ironPythonCode = string.Format("self.executeTestStep(self.fail,\"{0}\")", message);
                        client.ExecuteIronPythonCode(ironPythonCode);
                    }
                }

                '''

#-------------------------------------------------------------------------------------------------------------------------
#============================== Stuff from TestCase
#-------------------------------------------------------------------------------------------------------------------------
    def fail(self, message, takeErrorCapture = True, crashOrReset = False):
        """Fail the test, with the given message.

            message             error reason string
            takeErrorCapture    whether error capture is taken or not (default = True)
            crashOrReset        whether error type is crash or reset (default = False)
        """
        raise TestException(repr(message), self, takeErrorCapture, crashOrReset)

    def takeVideoStillImage(self, imagename=None):
        """ If Video recording is available, this method will take a still image from video stream """

        if core.FW_conf['blackbox'] is not None and core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.getName() == "Main":

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

            core.FW_conf['blackbox'].takePicture(os.path.join(imgPath, imgname))

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
                self.clearGraniteServer()
                self.capture('capture from failure')
            except Exception:
                debug.err('Unable to take capture from failure!')
            finally:
                # error_capture flag must always be set back to False
                core.FW_conf['error_capture'] = False

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
        if self.result:
            # increase test step count
            self.result.testStepCount += 1

        # if test execution is aborted, do it with StopTestException
        if core.FW_conf['should_stop']:
            raise StopTestException('Test execution terminated')

        try:
            # disable bitmap_capture in system's ensure idle state step
            if not testStepReporting and testStepName == 'ensure idle state':
                self.teststep.config['bitmap_capture'] = 'no'

            self.__purgeKeyPresses()
            self.__purgeExpectedItems()

            if not testStepName:
                testStepName = 'Step #%u' % (self.__testStepNameIndex)

            if self._name!='Main':
                testStepName = self._name + " : " + testStepName

            self.__testStepNameIndex += 1

            try:
                if isinstance(testStepName, unicode):
                    testStepName = smart_unicode(testStepName, 'utf-8', errors='replace')
                else:
                    try:
                        testStepName = unicode(testStepName, 'utf-8')
                    except Exception:
                        testStepName = unicode(testStepName, 'Latin-1', 'replace')
            except Exception:
                testStepName = 'Test step %s' % str(self.__testStepNameIndex)

            self.teststep['name'] = u"%s" % testStepName

            self.__checkExpects()

            if not self.teststep['timeout']:
                self.teststep['timeout'] = str(timeoutparser.getTimeout(self.teststep))

            self.__id = 0

            # send wait message from main FW process to GUI
            # convert timeout from milliseconds to seconds
            timeout = int(self.teststep['timeout']) / 1000
            self.sendWaitMessageToGraniteGUI(timeout,
                smart_str(self.teststep['name'], 'ascii', errors='replace'))

            debug.out(self.teststep.toprettyxml())

            # execute test step
            result = self.testReq(testStepReporting)

            return result
        finally:
            self._initTestStep()

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
        # Remote phone comment
        if warning and self._name != 'Main':
            warning = self._name + " : " + warning

        debug.err('Warning: %s' % warning)
        if type(warning) != types.ListType:
            warning = [warning]

        if self.result:
            self.result.addStepWarning(warning)

    def getLanguage(self):
        """Get current phone language with SX."""
        # get language variant from phone
        self.phoneLanguage = \
            self.sx('(send config-manager get-setting "./yapas/display/language")')

        # FIXME: Remove this when SP is returning correct english variant
        if self.phoneLanguage == 'en':
            self.phoneLanguage = 'en_GB'

        return self.phoneLanguage

    def languageChanged(self, language = None):
        """Tell Granite FW that language has changed in the phone.
           This results to logical text translation dictionary re-generation.

           Parameters

           language         current language (if not given, it will be asked with SX)
        """
        self.createTextDictionary()

        if language:
            self.phoneLanguage = language
        else:
            self.phoneLanguage = self.getLanguage()


class GraniteSXScripts:
    """Defines the SX scripts used in Granite Framework"""
    IMAGE_METADATA = \
        """
        (begin
            (define (get-granite-image-metadata)
                (define mk "")
                (define icon-dict "")
                (define out-xml (create-builtin-xml-builder))

                (send out-xml open-element "images")

                (dictionary-for-each meta-dict
                    (lambda (key value)
                        (dictionary-for-each value
                            (lambda (key2 value2)
                                (when (equal? key2 'meta-key)
                                    (set! mk value2)
                                )
                                (when (equal? key2 'icons)
                                    (set! icon-dict value2)
                                )
                            )
                        )
                        (when (not (equal? icon-dict ""))
                            (dictionary-for-each icon-dict
                                (lambda (icon-key icon-value)
                                    (when (string-ends-with? icon-value ".png")
                                        (send out-xml open-element "image")
                                        (send out-xml add-attribute "app" (send key ->string))
                                        (send out-xml add-attribute "id" (string-append (send mk ->string) "/" (send icon-key ->string)))
                                        (send out-xml add-attribute "path" (send icon-value ->string))
                                        (send out-xml close-element)
                                    )
                                )
                            )
                            (set! mk "")
                            (set! icon-dict "")
                        )
                    )
                )

                (send out-xml close-element)

                out-xml
            )

            (send (get-granite-image-metadata) get-data)
        )
        """

    TEXT_METADATA = \
        """
        (begin
            (define (granite-list-to-string translationlist)
                (define result "")

                (when (pair? translationlist)
                    (let loop ((tl translationlist))
                        (when (pair? tl)
                            (begin
                                (define value (car tl))

                                (when (number? value)
                                    (set! result (string-append result "%s"))
                                else
                                    (set! result (string-append result value))
                                )
                            )
                            (loop (cdr tl))
                        )
                    )
                    else
                    (set! result  "")
                )
                result
            )

            (define (get-granite-text-metadata)
                (define text-dict "")
                (define out-xml (create-builtin-xml-builder))

                (send out-xml open-element "texts")

                (dictionary-for-each meta-dict
                (lambda (key value)
                    (dictionary-for-each value
                    (lambda (key2 value2)
                        (when (equal? key2 'texts)
                        (set! text-dict value2)
                        )
                    )
                    )
                    (when (not (equal? text-dict ""))
                    (dictionary-for-each text-dict
                        (lambda (text-key text-value)
                        (define text-id (send text-value ->string))
                        (define text-translation (send (xlate text-value) ->string))
                        (when (not (equal? text-id text-translation))
                            (send out-xml open-element "text")
                            (send out-xml add-attribute "app" (send key ->string))
                            (send out-xml add-attribute "id" text-id)
                            (send out-xml add-attribute "translation" text-translation)
                            (send out-xml close-element)
                        )
                        )
                    )
                    (set! text-dict "")
                    )
                )
                )

                (dictionary-for-each xlate-db
                (lambda (key value)
                    (define translation "")
                    (send out-xml open-element "text")
                    (send out-xml add-attribute "app" "common")
                    (send out-xml add-attribute "id" (send key ->string))

                    (when (not (string? value))
                        (set! translation (granite-list-to-string value))
                    else
                        (set! translation value)
                    )

                    (send out-xml add-attribute "translation" translation)
                    (send out-xml close-element)
                )
                )

                (send out-xml close-element)

                out-xml
            )

            (send (get-granite-text-metadata) get-data)
        )
        """

    MENU_FOR_SIMULATION = \
        """
        (begin
            (define (granite-get-settings . args)
                (define opt (optional args 'key 'settings-categories 'xml-builder false))
                (define key (send opt ref 'key))
                (define type (get-meta-data key 'type))
                (define title (get-meta-text key 'title))
                (define id (get-meta-text-id key 'title))

                (define out-xml (send opt ref 'xml-builder))
                (when (not out-xml)
                    (set! out-xml (create-builtin-xml-builder))
                )

                (send out-xml open-element "setting")
                (send out-xml add-attribute "name" (send key ->string))
                (send out-xml add-attribute "type" (send type ->string))
                (when title
                    (send out-xml add-attribute "title" (get-meta-text key 'title))
                    (send out-xml add-attribute "title-string-id"
                        (send (get-meta-text-id key 'title) ->string))
                )

                (case type
                    ((category)
                        (send out-xml add-attribute "uri" (string-append "x-settings:" key))
                        (for-each
                            (lambda (sub-key)
                                (granite-get-settings
                                    'key sub-key
                                    'xml-builder out-xml
                                )
                            )
                            (get-meta-data key 'sub-settings)
                        )
                    )
                    (else
                        (when (not (equal? type 'smsc-sim))
                            (define setting (create-setting key (dictionary (sim-slot 0))))
                            (when (object? setting)
                                (define path (send setting get-path))
                                (when (equal? path ".")
                                    (set! path "")
                                )

                                (send out-xml add-attribute "path" path)
                            )
                        )
                    )
                )
                (send out-xml close-element)

                out-xml
            )

            (define (granite-get-mainmenu)
                (define app-keys
                    (ensure-valid-meta-menu
                        (get-meta-data
                            (get-mainmenu-meta-key
                                (send config-manager get-setting "./yapas/display/mainmenu/style")
                            )
                            'menu
                        )
                    )
                )

                (define out-xml (create-builtin-xml-builder))

                (send out-xml open-element "mainmenu")
                (for-each
                    (lambda (key)
                        (define title (get-meta-text key 'grid-menu))
                        (define id (get-meta-text-id key 'grid-menu))
                        (when (not title)
                            (set! title (get-meta-text key 'title))
                            (set! id (get-meta-text-id key 'title))
                        )

                        (send out-xml open-element "item")
                        (send out-xml add-attribute "name" "settings")
                        (send out-xml add-attribute "title" title)
                        (send out-xml add-attribute "id" (send id ->string))
                        (send out-xml add-attribute "uri" (get-meta-data key 'uri))
                        (when (equal? key 'settings)
                            (granite-get-settings 'xml-builder out-xml)
                        )
                        (send out-xml close-element)
                    )
                    app-keys
                )
                (send out-xml close-element)

                out-xml
            )

            (send (granite-get-mainmenu) get-data)
        )
        """

    MENU_FOR_SIMULATION_2 = \
        """
        (begin
            (define (granite-get-settings . args)
                (define opt (optional args 'key 'settings-categories 'xml-builder false))
                (define key (send opt ref 'key))
                (define type (get-meta-data key 'type))
                (define title (get-meta-text key 'title))
                (define id (get-meta-text-id key 'title))

                (define out-xml (send opt ref 'xml-builder))
                (when (not out-xml)
                    (set! out-xml (create-builtin-xml-builder))
                )

                (send out-xml open-element "setting")
                (send out-xml add-attribute "name" (send key ->string))
                (send out-xml add-attribute "type" (send type ->string))
                (when title
                    (send out-xml add-attribute "title" (get-meta-text key 'title))
                    (send out-xml add-attribute "title-string-id"
                        (send (get-meta-text-id key 'title) ->string))
                )

                (case type
                    ((category)
                        (send out-xml add-attribute "uri" (string-append "x-settings:" key))
                        (for-each
                            (lambda (sub-key)
                                (granite-get-settings
                                    'key sub-key
                                    'xml-builder out-xml
                                )
                            )
                            (get-meta-data key 'sub-settings)
                        )
                    )
                    (else
                        (when (not (equal? type 'smsc-sim))
                            (define setting (create-setting key (dictionary (sim-slot 0))))
                            (when (object? setting)
                                (define path (send setting get-path))
                                (when (equal? path ".")
                                    (set! path "")
                                )

                                (send out-xml add-attribute "path" path)
                            )
                        )
                    )
                )
                (send out-xml close-element)

                out-xml
            )

            (define (granite-get-mainmenu)
                (define app-keys
                    (ensure-valid-meta-menu
                        (get-meta-data
                            (get-mainmenu-meta-key)
                            'menu
                        )
                    )
                )

                (define out-xml (create-builtin-xml-builder))

                (send out-xml open-element "mainmenu")
                (for-each
                    (lambda (key)
                        (define title (get-meta-text key 'grid-menu))
                        (define id (get-meta-text-id key 'grid-menu))
                        (when (not title)
                            (set! title (get-meta-text key 'title))
                            (set! id (get-meta-text-id key 'title))
                        )

                        (send out-xml open-element "item")
                        (send out-xml add-attribute "name" "settings")
                        (send out-xml add-attribute "title" title)
                        (send out-xml add-attribute "id" (send id ->string))
                        (send out-xml add-attribute "uri" (get-meta-data key 'uri))
                        (when (equal? key 'settings)
                            (granite-get-settings 'xml-builder out-xml)
                        )
                        (send out-xml close-element)
                    )
                    app-keys
                )
                (send out-xml close-element)

                out-xml
            )

            (send (granite-get-mainmenu) get-data)
        )
        """
