# -*- coding: utf-8 -*-
"""Interface for wrapping Test Automation Bridge on top of ADB for Marble.
"""
# Python library module imports
import clr, os, sys, time, traceback, types, datetime, string, threading, fnmatch
from System.Collections.Generic import List
from System import MulticastDelegate, ObjectDisposedException, DateTime, TimeSpan
from System.Text import Encoding
from System.Threading import Thread, ParameterizedThreadStart, Monitor

import collections
from collections import deque

clr.AddReference('TestAutomation.Bridge')
from TestAutomation.Bridge import TABInterface, TABException, OutputFormat
from TestAutomation.Bridge.ScriptingTools import *
from TestAutomation.Bridge.Tracing import *

# Marble module imports
import core
from core.testcase_exceptions import TestException
from utils.nodeutils import NodeUtils

# XML functions
def unescape(t):
    """Revert HTML-escape the text in `t`."""
    return (t
        .replace("&amp;", "&").replace("&lt;", "<").replace("&gt;", ">")
        .replace("&#39;", "´").replace("&quot;", '"').replace('&apos;',"'")
        )

def escape(t):
    """HTML-escape the text in `t`."""
    return (t
        .replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
        .replace("´", "&#39;").replace('"', "&quot;").replace("'",'&apos;')
        )

def getXpathLiteral(string):
    """If string contains both single and double quotes it must be splitted."""
    if not '"' in string:
        return '"' + string + '"'
    if not "'" in string:
        return "'" + string + "'"

    #if the value contains both single and double quotes, construct an
    #expression that concatenates all non-double-quote substrings with
    #the quotes, e.g.:
    #concat("foo", '"', "bar")

    sb = "concat("
    substrings = string.split('"')
    for i in range(len(substrings)):
        needComma = (i>0);
        if substrings[i] != "":
            if i > 0:
                sb += ", "

            sb += "\""
            sb += substrings[i]
            sb += '"'
            needComma = True
        if i < (len(substrings) - 1):
            if needComma:
                sb += ", "
            sb += "'\"'"

    sb += ")"

    return sb


class TABInterfaceException(Exception):
    """Exception class for test TAB interface exceptions with traceback info.
    """
    def __init__(self, error = ''):
        Exception.__init__(self, error)

        # dig out traceback
        et, ev, tb = sys.exc_info()
        self._errorString = error + ':\n' + ''.join(traceback.format_exception(et, ev, tb))

    def __unicode__(self):
        return '\n%s\n' % self._errorString


class UIEventParams(object):
    """Parameters class for UI event thread."""
    eventInterval = 800
    maximumDuration = 3000
    usePageFlipCount = False

class TouchParameters(object):
    """Parameters class for touch pressing in background thread """
    x = None
    y = None

class FlickParameters(object):
    """Parameters class for performing flick for fast scroll """
    xCoord = None
    yDown = None
    yUp = None
    speed = None

class TestAutomationBridge(object):
    """Marble Test Automation Bridge interface class."""
    def __init__(self, phone):
        """Initialization of TAB class.

            Parameters

            phoneName           Main/Main2/Main3...
        """

        self.phone = phone
        self.__phoneName = phone.getName()

        # dump NodeUtils instances
        self._currentDump = None
        self.__currentVisible = None
        self._dumpBuffer = deque(maxlen=10)

        # device types
        self.HW = TABInterface.DeviceType.HW
        self.EMULATOR = TABInterface.DeviceType.EMULATOR
        self.ANY = TABInterface.DeviceType.ANY

        # path to ADB executable
        self.__adbPath = os.path.normpath(os.path.join(core.FW_conf['startup_path'],  'dlls\\adb.exe'))

        # saved when connection is created
        self._serialNumber = ""
        self._tabConn = None
        self.__screenWidth  = 480
        self.__screenHeight = 800
        self._screenDimensionsQueried = False

        # dynamic list of test server client methods
        self.__testServerClientMethods = []

        # flag whether to use server level or ADB level for dump, touch etc
        self.serverLevelInUse = True

        # event threads
        self.__UIEventThread = None
        self.__scrollEventThread = None
        self.__specificUIEventThread = None
        self.__mObject = object()

        # variables for UI event handling
        self.__windowStateChanged = False

        #self.itemWasClicked = False
        self.__screenScrolled = None
        self.averageScrollEventInterval = 0
        self.__scrollEventCount = 0
        self.__scrollEventSum = 0
        self.__scrollEventTime = 0
        self.__scrollEventInterval = 0

        # last C# dict of launchable applications
        self.__launchableApplications = None

        # will be increased if testing against emulator
        self._timeoutMultiplier = 1

        # access to media player functionality
        self._mediaPlayer = None

        # access to sql lite functionality
        self._sqlLite = None

        # access to file functionalities
        self._file = None

        # access to package manager functionalities
        self._packageManager = None

        # access to time manager functionalities
        self._time = None

        # for specific event waitings
        self.__waitSpecificEvent = ""

        # whether logging is enabled or not
        self.__logging = False
        self.__logFileDir = ""

        # dynamic dict of key codes (will be set when using sendKey)
        self.__keyCodes = None

        # True when waiting for device to get back online
        self.__waitingForDeviceOnline = False
        # True when checking device connection status
        self.__checkingDeviceConnectionStatus = False
        # True when connecting server
        self.__connectingServer = False

        # the topmost notification/toast
        self.__notifications = []

        # the maximum capacity of the notifications buffer
        self.__notificationsCapacity = 30

        # lock for setting getting topmostNotification
        self.__notificationLock = threading.Lock()

        # set trace listener only for main phone
        if self.__phoneName == 'Main':
            TraceListener.AddListener(self.__trace)

        # default timeouts for ui event waiting
        self.__eventInterval = 800
        self.__maximumDuration = 3000
        self.overrideEventInterval = 0

        # flag whether UI events are waiting or not (can be turned off by select)
        self.waitUntilNoUIevents = True

        # counter for device connection failures
        self.__connectionFailures = 0
        self.__maxNumberOfConnectionFailures = 10

        # variable for current page flip count
        self.__pageFlipCount = 0
        self.__pageFlipCountSuccess = False
        self.__lastPageFlipEventTime = 0
        self.__pageFlipsSpeedLimit = 1

        # for calculating time between UI events and fps
        self.__firstUIEventPageFlipCount = 0
        self.__lastUIEventPageFlipCount = 0
        self.__firstUIEventTimeStamp = 0
        self.__UIeventTimeStamp = 0
        self.__lastUIEventType = ''

        # dynamic list for packages that send empty dump
        self.__packagesWithEmptyLayout = []

        # variable for storing sw type ("eng" / "user")
        self.swType = "eng"
        
        # for controlling flick thread for fast scroll
        self._flickThreadRunning = True
        self._flickThread = None

    def _executeTabOperation(self, method, *args, **kwargs):
        """Executes tab operation and catches exceptions.

            Returns True, params if method was executed successfully,
            False, exception if not.
        """
        # just return if test execution is stopping
        if core.FW_conf['should_stop']:
            return False, None

        succeeded = False
        unExpectedExceptionOccurred = False
        errorReason = ""
        tryingAgain = False
        dynamicInvoker = False
        sendKwArgs = False

        try:
            self.phone.sendWaitMessageToMarbleGUI(60, 'TAB executing: %s' % str(method))
            #debug.brf('*** _executeTabOperation: %s' % str(method))

            # check logging status
            self.__checkLogging()

            # check do we need to send kwargs to method or not
            for key in kwargs.keys():
                if not key in ['tryAgain', 'dynamicInvoker']:
                    sendKwArgs = True
                elif key == 'tryAgain':
                    tryingAgain = True
                elif key == 'dynamicInvoker':
                    dynamicInvoker = True

            # clear temporary kwargs so that they won't be passed to actual method
            for key in ['tryAgain', 'dynamicInvoker']:
                if kwargs.has_key(key):
                    del kwargs[key]

            # if we already have multicast delegate at hand coming via try again, kwargs can't be passed anymore
            if dynamicInvoker:
                params = method(*args)
            else:
                # call method
                if sendKwArgs:
                    params = method(*args, **kwargs)
                else:
                    params = method(*args)

            #debug.brf('method: %s' % method)
            #debug.brf('args: %s' % args)
            #debug.brf('kwargs: %s' % kwargs)

            succeeded = True
        except TABException, tabException:
            # we only need the error reason from exception
            errorReason = str(tabException)

            # delete exception instance
            del tabException

            self._debugErr('TAB exception: %s occurred with method: %s' % \
                      (errorReason, str(method)))
        except Exception, exception:
            unExpectedExceptionOccurred = True

            # we only need the error reason from exception
            errorReason = str(exception)

            # delete exception instance
            del exception

            self._debugErr('Unexpected exception: "%s" when executing: "%s"' % (errorReason, str(method)))

            self.__connectionFailures += 1
        finally:
            if not succeeded:
                if tryingAgain:
                    # if operation failed with the second try, raise interface exception
                    raise TABInterfaceException(errorReason)
                else:
                    #debug.brf('trying again...')
                    # check connection
                    self.__reCreateConnection()

                    # check phone side ADB status
                    if not self.__checkPhoneAdbStatus():
                        errorMessage = 'ADB connection to device lost!'
                        self.phone.warn(errorMessage)
                        errorMessage += ' Terminating test execution!'

                        if core.FW_conf['cli_mode'] and not core.FW_conf['settings'].TestRun.ExecutionMode == 'Follower':
                            self._debugErr(errorMessage)

                            # close phone connetion
                            self._closeConnection()

                            sys.exit(1)
                        else:
                            if not self.__restartADB():
                                # send error to Marble GUI
                                core.FW_conf['com_int'].sendErrorMessage(errorMessage)
                                # execute CMD_STOP event --> quit Marble Framework
                                core.FW_conf['com_int'].connectionCreationOngoing = False
                                core.FW_conf['com_int'].CMD_QUIT(None)

                                return False, None

                    # tryAgain to kwargs for second execute try
                    kwargs['tryAgain'] = True

                    # dynamic calls must be flagged
                    if isinstance(method, MulticastDelegate):
                        kwargs['dynamicInvoker'] = True

                    return self._executeTabOperation(method, *args, **kwargs)
            else:
                return True, params

    def __reCreateConnection(self):
        """Re-create TAB connection."""
        # check status of connections
        connected, serverConnected = self.__isConnected()

        # recreate connection(s) if needed
        try:
            if not connected:
                self._closeConnection()  # this will also disconnect server and scripting service
                self._createConnection(serialNumber = self._serialNumber)
                debug.brf('Device connection recreated')

            if serverConnected == False:
                self._disconnectServer()
                time.sleep(5)
                self._connectServer()
                debug.brf('TA server connection recreated')
        except Exception, err:
            self._debugErr('Unable to recreate device connection: %s' % str(err))

    def __checkPhoneAdbStatus(self):
        """Check phone side ADB status by trying run "shell ps" command.

            Returns True if ADB is running ok, False if not.
        """
        if self._tabConn:
            try:
                self._tabConn.ShellCommand("ps")
                return True
            except Exception, err:
                self._debugErr('Error when checking phone side ADB status: %s' % str(err))
                return False
        else:
            return False

    def _checkDeviceStatus(self):
        """Checks device status whether it's ready to test execution."""
        # FIXME: Handle also situation where uiautomator process is not starting at all
        if self._tabConn:
            try:
                deviceStatus = self._tabConn.CheckDeviceStatus()
            except Exception, err:
                try:
                    self.__checkDeviceConnectionStatus(str(err))
                except TABInterfaceException:
                    # if not called from checkUiFreeze
                    if not self.phone.exit.uiFreezeDetectionOngoing:
                        # if video recorder available, check UI freeze when TAB is reporting interface exception
                        if core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.phone.isMain():
                            self.phone.exit._checkUiFreeze()

                except TestException:
                    raise # just raise TestException coming from __checkDeviceConnectionStatus
                except Exception, err:
                    self._debugErr('Error occurred in checking device connection status: %s' % str(err))
                    self.__connectionFailures += 1
            else:
                if deviceStatus == 1:
                    errorMessage = 'systemui process is no longer running!'

                    # if not called from checkUiFreeze
                    if not self.phone.exit.uiFreezeDetectionOngoing:
                        if core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.phone.isMain():
                            self.phone.exit._checkUiFreeze()

                    self.phone.warn(errorMessage)
                    self.__connectionFailures += 1
                elif deviceStatus == 2:
                    errorMessage = 'ADB connection to device lost!'
                    self.phone.warn(errorMessage)

                    if not core.FW_conf['ci_enabled']:
                        if not self.__restartADB():
                            self.__connectionFailures += 1
                        else:
                            self.__connectionFailures = 0
                    else:
                        self.__connectionFailures += 1
                        raise TABInterfaceException(errorMessage)

    def __trace(self, msg):
        """Trace method for directing trace messages from dynamic proxies to test report.

            Parameters

            msg             trace message string
        """
        self.phone.sendWaitMessageToMarbleGUI(60, 'Executing operation: %s' % msg)
        self.phone.comment(msg)

    def __convertTupleWithList(self, cSharpTuple):
        """Convert method for converting C# tuple with list to Python tuple with Python list

            Parameters

            cSharpTuple     C# tuple with list
        """
        if cSharpTuple != None:
            return (list(cSharpTuple.Item1), list(cSharpTuple.Item2))
        else:
            return (None, None)

    def __convertTuple(self, cSharpTuple):
        """Convert method for converting C# tuple to Python tuple

            Parameters

            cSharpTuple     C# tuple
        """
        if cSharpTuple != None:
            return ( cSharpTuple.Item1, cSharpTuple.Item2 )
        return None

    def __convertAttributesTuple(self, cSharpAttributesTuple):
        """Convert method for converting C# 3-elements tuple to Python tuple

            Parameters

            cSharpAttributesTuple     C# 3-elements tuple
        """
        if cSharpAttributesTuple != None:
            return ( cSharpAttributesTuple.Item1, cSharpAttributesTuple.Item2, cSharpAttributesTuple.Item3 )
        return ( None, None, None )

    def __convertDictionary(self, cSharpDictionary):
        """Convert method for converting C# dictionary to Python dictionary

            Parameters

            cSharpDictionary     C# tuple
        """
        if cSharpDictionary != None:
            return dict(cSharpDictionary)
        return None

    def __convertDate(self, cSharpDate):
        """Convert method for converting C# DateTime to Python datetime.datetime

            Parameters

            cSharpDate     C# DateTime
        """
        return datetime.datetime(cSharpDate)

    def __convertDateArg(self, *args):
        """Convert method for converting Python style arguments for Time.SetSystemDateTime(DateTime, bool) -method

            Parameters

            args     Python style arguments for the method
        """
        if args == None:
            return None
        _args = list(args)
        if len(_args) > 0 and isinstance(_args[0], datetime.datetime):
            dt = _args[0]
            _args[0] = DateTime(dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second, int(dt.microsecond / 1000))
        return _args

    def __convertTimeSpan(self, cSharpTimeSpan):
        """Convert method for converting C# TimeSpan to Python datetime.timedelta

            Parameters

            cSharpList     C# TimeSpan
        """

        return datetime.timedelta(seconds = cSharpTimeSpan.TotalSeconds)

    def __convertList(self, cSharpList):
        """Convert method for converting C# List<T> to Python list

            Parameters

            cSharpList     C# List<T>
        """
        if cSharpList != None:
            return list(cSharpList)
        return None

    def __convertArray(self, cSharpArray):
        """Convert method for converting C# array T[] to Python list

            Parameters

            cSharpArray     C# Array T[]
        """
        if cSharpArray != None:
            return list(cSharpArray)
        return None

    def __convertTouchArgs(self, *args):
        """Convert method for converting Python style arguments for File.Touch(file, date) -method

            Parameters

            args     Python style arguments for the method
        """
        if args == None:
            return None
        _args = list(args)
        if len(_args) == 2 and isinstance(_args[1], datetime.datetime):
            dt = _args[1]
            _args[1] = DateTime(dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second, int(dt.microsecond / 1000))
        return _args

    def __convertReadArgs(self, *args):
        """Convert method for converting Python style arguments to for File.Read*(file, encoding) -methods

            Parameters

            args     Python style arguments for the methods
        """
        if args == None:
            return None
        _args = list(args)
        if len(_args) == 2 and isinstance(_args[1], str):
            _args[1] = Encoding.GetEncoding(_args[1])
        return _args

    def __getattr__(self, attr, *args, **kwargs):
        """Map lower C# levels to self."""
        #return getattr(self._tabConn, attr)
        #debug.brf('attr: %s' % attr)

        function = None

        # first search from TABConnection
        function = getattr(self._tabConn, attr, None)

        if self.serverLevelInUse:
            # then from TestServerClient
            if not function and self._isServerAvailable() and \
               attr in self.__testServerClientMethods:
                function = getattr(self._tabConn.TestServerClient, attr, None)

            # and finally from ScriptingServiceClient
            if not function and getattr(self._tabConn, 'ScriptingServiceClient', None):
                function = getattr(self._tabConn.ScriptingServiceClient, attr, None)

        if not function:
            raise AttributeError("%s not available!" % str(attr))
        else:
            #debug.brf('function: %s' % function)
            #debug.brf('function xx: %s' % function.Method)
            return function

    def _appendGalleryData(self, mainView):
        """ Adds gallery data on top of the OpenGL view.
        """
        viewNode =  mainView.find('//node["com.android.gallery3d:id/gl_root_view"=@resource-id]')
        if viewNode != None:
            if self._tabConn.TestServerClient.GalleryAlbumset:
                i = 0
                for album in self._tabConn.TestServerClient.GalleryAlbumset.Albums:
                    node = NodeUtils('<node index="0" text="" resource-id="com.android.gallery3d:id/album/%i" class="android.widget.ImageView" package="com.android.gallery3d" content-desc="" checkable="false" checked="false" clickable="false" enabled="true" focusable="false" focused="false" scrollable="false" long-clickable="false" password="false" selected="false" bounds="" />' % i, True)
                    node.setAttribute('bounds',"[%i,%i][%i,%i]" % (int(album.X), int(album.Y), int(album.X)+int(album.W), int(album.Y)+int(album.H)))
                    node.setAttribute('text', album.Album)
                    viewNode.append(node)
                    i += 1
            if self._tabConn.TestServerClient.GalleryAlbum:
                i = 0
                for album in self._tabConn.TestServerClient.GalleryAlbum.Thumbnails:
                    node = NodeUtils('<node index="%i" text="" resource-id="com.android.gallery3d:id/item/%i" class="android.widget.ImageView" package="com.android.gallery3d" content-desc="" checkable="false" checked="false" clickable="false" enabled="true" focusable="false" focused="false" scrollable="false" long-clickable="false" password="false" selected="false" bounds="" />' % (i, i), True)
                    node.setAttribute('bounds',"[%i,%i][%i,%i]" % (int(album.X), int(album.Y), int(album.X)+int(album.W), int(album.Y)+int(album.H)))
                    node.setAttribute('content-desc', album.Thumbnail)
                    viewNode.append(node)
                    i += 1

    def _getDump(self):
        """Get XML dump from the device.

            Returns dump node (NodeUtils instance)
        """
        # for returning empty hierarchy node if dump is None
        dumpNode = NodeUtils('hierarchy', True)

        problemsGettingDump = False

        if self._tabConn:
            # use server dump if available and used
            if self._isServerAvailable():
                if self._isServerConnected():
                    maxAttemps = 20
                    for i in range(maxAttemps):
                        success, response = self._executeTabOperation(self._tabConn.TestServerClient.getDump, True)

                        #if response:
                        #    faili = open('dump.xml', 'w')
                        #    faili.write(response.encode('utf-8'))
                        #    faili.close()
                        #debug.brf('dump response: %s' % response)

                        if success and response:
                            dumpNode = NodeUtils(response)

                            # get package name
                            firstNode = dumpNode.find('node')
                            packageName = None
                            if firstNode:
                                packageName = firstNode.getAttribute('package')

                            # append gallery data if package is gallery
                            if firstNode != None and packageName != None and packageName == "com.android.gallery3d":
                                self._appendGalleryData(firstNode)
                                break

                            # start checking that does dump contain empty layouts
                            layoutChildNodes = dumpNode.findall("//node[not(contains(@class,'Layout')) and ancestor::node[contains(@class,'Layout')] and not(descendant::node[contains(@class, 'Layout')])]")

                            if not layoutChildNodes and i <= 15: # empty layouts got, start looping
                                if packageName and packageName in self.__packagesWithEmptyLayout and i >= 3: # this package has been checked previously, check only few times before giving up
                                    # self.phone.warn('giving up for package %s' % packageName)
                                    break

                                if i > 10: # if problem has occurred multiple times, save dump and print warning
                                    self.phone.warn('Multiple incomplete dumps received from phone. Saved to %s' % self.__saveDump(dumpNode, 'empty_%s' % time.time()))

                                time.sleep(0.1)

                            elif not layoutChildNodes and packageName and \
                                not packageName in self.__packagesWithEmptyLayout and \
                                i == maxAttemps - 1: # give up permanently for this package, dump is not getting better
                                # self.phone.warn('adding %s to packagesWithEmptyLayout' % packageName)
                                self.__packagesWithEmptyLayout.append(packageName)
                                break

                            elif layoutChildNodes and packageName and packageName in self.__packagesWithEmptyLayout: # dump normal, package can be removed from empty layout list
                                self.__packagesWithEmptyLayout.remove(packageName)
                                break

                            else:
                                break # layout nodes found with content, dump seem normal. break the loop

                        else:
                            problemsGettingDump = True
                            # wait for a while and take dump again
                            time.sleep(0.1)

                        # restart server when we are not getting xml dump
                        if problemsGettingDump and i == 10:
                            self._restartServer()
            else:
                dumpFilePath = os.path.join(core.FW_conf['test_result_dir'], 'dump.xml')

                success, response = self._executeTabOperation(self._tabConn.GetXMLDump, dumpFilePath)

                if os.path.isfile(dumpFilePath):
                    dumpNode = NodeUtils(dumpFilePath)
                    os.remove(dumpFilePath)

        self.__createIndexTree(dumpNode)

        # store current dump to speed up analyzing
        self._currentDump = dumpNode

        # store dump in ring buffer so last states can be saved in case of failure
        self._dumpBuffer.append(dumpNode)

        # save dump to file
        self.__saveDump(dumpNode)

        #debug.brf('DUMP TAKEN!')

        if problemsGettingDump and not core.FW_conf['should_stop']:
            debug.err('There were problems getting xml dump from the phone!')

        if not core.FW_conf['should_stop']:
            if problemsGettingDump and not dumpNode.getChildNodes():
                errorString = 'Unable to get XML dump from the phone!'
                debug.err(errorString)

                # NOTE: timeout 5, because we don't need to wait for boot flags
                connected, booted = self._isConnectedAndReady(timeout = 5)

                if not connected:
                    if self._waitForDeviceOnline():
                        self.phone.warn('Device went to offline state during test execution, but is back online again')
                    else:
                        self.phone.result.addFailure('Device went to offline state during test execution', crashOrReset = True)
                else:
                    # restart server when we are not getting xml dump
                    self._restartServer()

                    raise TABInterfaceException(errorString)

        return dumpNode

    def _getCoordsFromBounds(self, bounds):
        """Get coordinate list from bounds.

            Parameters

            bounds          bounds coordinate string
        """
        boundCoords = []

        for coord in bounds.replace('[', ',').replace(']', ',').split(','):
            if coord != '':
                boundCoords.append(int(coord))

        return boundCoords

    def _getCenterCoordsFromBoundCoords(self, boundCoords):
        """Get center coordinates from bound coordinate list.

            Parameters

            boundCoords     bounds coordinate list
        """
        centerX = boundCoords[0] + ((boundCoords[2] - boundCoords[0]) / 2)
        centerY = boundCoords[1] + ((boundCoords[3] - boundCoords[1]) / 2)

        return (centerX, centerY)

    def _convertRelative(self, point):
        """Convert relative coordinates to absolute if needed.

            Parameters

            point               coordinate point
        """
        if not isinstance(point, tuple) or len(point) != 2:
            return point

        x = point[0]
        y = point[1]

        if isinstance(x, float) and x <= 1.0:
            w = self.getScreenWidth()
            x = int(round((float(w) * x), 0))

        if isinstance(y, float) and y <= 1.0:
            h = self.getScreenHeight()
            y = int(round((float(h) * y), 0))

        return (x, y)

    def _getNotifications(self, bestBefore, includeTimeStamp=False):
        """ Gets the valid notifications from the buffer """
        with self.__notificationLock:
            notifications = []
            for text, timestamp in self.__notifications:
                #debug.brf('%s - %s' % (int((datetime.datetime.now() - timestamp).total_seconds() * 1000), bestBefore))
                if int((datetime.datetime.now() - timestamp).total_seconds() * 1000) > bestBefore or len(text) == 0:
                    continue
                if includeTimeStamp:
                    notifications.append((timestamp, text[0]))
                else:
                    notifications.append(text[0])
            return notifications

    def __getTestServerClientMethods(self):
        """Get list of available test server client methods."""
        # NOTE: This is done only once, because method list is stored
        if self.serverLevelInUse and self._tabConn and not self.__testServerClientMethods:
            if self._isServerAvailable() and self._isServerConnected():
                #doc = self._tabConn.TestServerClient.getDoc()
                #for value in doc.split():
                #    if '(' in value:
                #        self.__testServerClientMethods.append(value.split('(')[0])
                try:
                    success, response = self._executeTabOperation(self._tabConn.TestServerClient.getAvailableMethodNames, 'TAServer')

                    if success:
                        self.__testServerClientMethods = response
                except Exception, err:
                    pass

            #debug.brf('self.__testServerClientMethods: %s' % self.__testServerClientMethods)

    def __registerEvents(self):
        """Register to events provided by lower level TAB."""
        if self._isServerAvailable():
            try:
                self._tabConn.TestServerClient.UiEvent += self.__UIEvent
                self._tabConn.TestServerClient.ServerTrace += self.__ServerTrace
                self._tabConn.TestServerClient.EnableRemoteEvents = True
            except:
                pass

    def __unRegisterEvents(self):
        """Unregister from events provided by lower level TAB."""
        if self._isServerAvailable():
            try:
                self._tabConn.TestServerClient.UiEvent -= self.__UIEvent
                self._tabConn.TestServerClient.ServerTrace -= self.__ServerTrace
            except:
                pass

    def __UIEvent(self, event, *args, **kwargs):
        """UI event coming from lower level TAB."""
        try:
            if core.FW_conf['settings'].System.UIEventTracesEnabled:
                debug.brf('%s__UIEvent: %s' % ((self.__phoneName != 'Main' and self.__phoneName + ': ' or ''), event.EventType))

            if str(event.EventType) == 'TYPE_NOTIFICATION_STATE_CHANGED' :
                self.__appendNotification(event)

            # store page flip count from event
            self.__setPageFlipCount(event)

            # report UI event interval and fps
            if self.phone.isMain() and \
               (event.EventType == TABInterface.TABEvents.TYPE_WINDOW_CONTENT_CHANGED or \
               event.EventType == TABInterface.TABEvents.TYPE_WINDOW_STATE_CHANGED or \
               event.EventType == TABInterface.TABEvents.TYPE_VIEW_TEXT_CHANGED or \
               event.EventType == TABInterface.TABEvents.TYPE_VIEW_SCROLLED):
                timeBetweenEvents = ''

                # report time between UI events
                if self.__UIeventTimeStamp != 0 and core.FW_conf['settings'].TestRun.ReportTimeBetweenUIEvents:
                    timeBetweenEvents = 'TIME BETWEEN %s and %s: %s' % (self.__lastUIEventType, event.EventType, str(event.EventTime - self.__UIeventTimeStamp))

                self.__lastUIEventType = str(event.EventType)

                # store time stamp and page flip count for first event
                if self.__firstUIEventTimeStamp == 0:
                    self.__firstUIEventTimeStamp = event.EventTime
                    if getattr(event, 'PageFlipCount', None):
                        self.__firstUIEventPageFlipCount = event.PageFlipCount

                self.__UIeventTimeStamp = event.EventTime

                fps = self._getUIEventFps()

                if core.FW_conf['settings'].TestRun.ReportUIEventFps:
                    uiEventFps = 'UI EVENT FPS: %s' % fps
                    if timeBetweenEvents:
                        self.phone.comment('%s\n%s' % (timeBetweenEvents, uiEventFps))
                    else:
                        self.phone.comment(uiEventFps)
                elif timeBetweenEvents:
                    self.phone.comment(timeBetweenEvents)

            #for func in dir(event):
            #    debug.brf('__UIEvent, %s: %s' % (func, str(getattr(event, func))))
        except Exception, err:
            self._debugErr('Error in UI event handling: %s' % str(err))

    def _getUIEventFps(self):
        """Returns current UI event fps"""
        fps = 0

        #debug.brf('self.__pageFlipCount: %s' % self.__pageFlipCount)
        #debug.brf('self.__firstUIEventPageFlipCount: %s' % self.__firstUIEventPageFlipCount)
        #debug.brf('self.__lastUIEventPageFlipCount: %s' % self.__lastUIEventPageFlipCount)

        if self.phone.isMain() and \
           not self.__firstUIEventPageFlipCount in [-1, 0, self.__pageFlipCount] and \
           self.__pageFlipCount != self.__lastUIEventPageFlipCount and \
           self.__UIeventTimeStamp != self.__firstUIEventTimeStamp:
            #debug.brf('self.__UIeventTimeStamp: %s' % self.__UIeventTimeStamp)
            #debug.brf('self.__firstUIEventTimeStamp: %s' % self.__firstUIEventTimeStamp)

            difference = (self.__UIeventTimeStamp - self.__firstUIEventTimeStamp) / 1000.0
            #debug.brf('difference: %s' % difference)
            #debug.brf('self.__pageFlipCount: %s' % self.__pageFlipCount)
            #debug.brf('self.__firstUIEventPageFlipCount: %s' % self.__firstUIEventPageFlipCount)

            fps = int((self.__pageFlipCount - self.__firstUIEventPageFlipCount) / difference)

            # when frame ends store current data as first
            if difference > 1:
                #debug.brf('fps frame change')
                self.__firstUIEventTimeStamp = self.__UIeventTimeStamp
                self.__firstUIEventPageFlipCount = self.__pageFlipCount

            self.__lastUIEventPageFlipCount = self.__pageFlipCount

        return fps

    def __appendNotification(self, notification):
        """ Appends a notification into notifications buffer """
        if notification.Text != None and len(notification.Text):
            with self.__notificationLock:
                if len(self.__notifications) > self.__notificationsCapacity:
                    self.__notifications.pop(0)
                self.__notifications.append(( list(notification.Text), datetime.datetime.now() ))

    def __ServerTrace(self, trace, *args, **kwargs):
        """Server trace coming from lower level TAB."""
        if core.FW_conf['settings'].System.ServerTracesEnabled:
            if not trace.Contains("INSTRUMENTATION") and \
               not trace.Contains("ECONNRESET"):
                debug.brf('%s__ServerTrace: %s' % ((self.__phoneName != 'Main' and self.__phoneName + ': ' or ''), trace))

    #def __connectServices(self):
    #    """Connect to test server client and scripting service client."""
    #    if self.serverLevelInUse and not (self.__phoneName == 'Main' and \
    #                (self.phone.isLeader() or self.phone.isFollower() ) ):
    #        self._connectServer()
    #        self.__connectScriptingService()

    def _disconnectServices(self, dispose = False):
        """Disconnect from test server client and scripting service client."""
        if self.serverLevelInUse:
            self._disconnectServer(dispose)
            self.__disconnectScriptingService()

    def __checkDeviceConnectionStatus(self, errorInfo):
        """Check device connection status from exception and try reconnecting to device

            Parameters

            errorInfo           error information coming in exception string
        """
        exceptionToBeRaised = None

        if self.__waitingForDeviceOnline:
            debug.out('Waiting for device to get back online...')
            return

        # no execution if we are already checking the status
        if self.__checkingDeviceConnectionStatus:
            return

        try:
            # just return if test execution is stopping
            if core.FW_conf['should_stop']:
                return

            self.__checkingDeviceConnectionStatus = True

            if "The device '%s' was not found" % self._serialNumber in errorInfo or \
               'device offline' in errorInfo or \
               'is not online' in errorInfo:
                # device went to offline state
                errorString = 'Device went to offline state during test execution'
                self.phone.warn('%s, reconnecting...' % errorString)
                self._closeConnection(sleepAfterClose = False, disconnectServices = False)

                # reset usb connection (usually it restores device to online state)
                if core.FW_conf['blackbox_enabled'] and self.phone.isMain():
                    self.phone._blackBoxResetPhoneUsbConnection(createConnection = False)
                    self.phone.comment('Disconnect and connect USB connection (%s) in order to get device back online' % core.FW_conf['blackbox'].getDefaultUsbAccessoryConnector())
                    self.phone._ensureBlackBoxUsbAccessoryConnection()

                if self._waitForDeviceOnline():
                    self.__connectionFailures = 0
                    self.phone.warn('Device went to offline state during test execution, but is back online again')
                else:
                    self.__connectionFailures += 1
                    self.phone.result.addFailure('Device went to offline state during test execution', crashOrReset = True)
            elif 'The shell command has become unresponsive' in errorInfo:
                errorMessage = 'ADB connection to device lost!'
                self.phone.warn(errorMessage)

                if not core.FW_conf['ci_enabled']:
                    if not self.__restartADB():
                        self.__connectionFailures += 1
                        raise TABInterfaceException(errorMessage)
                    else:
                        self.__connectionFailures = 0
                else:
                    self.__connectionFailures += 1
                    raise TABInterfaceException(errorMessage)
            elif 'Unable to start TA server process' in errorInfo:
                exceptionToBeRaised = 'Unable to start TA server process!'
                self._debugErr(exceptionToBeRaised)
            elif 'sad result from adb' in errorInfo:
                exceptionToBeRaised = 'Device ADB daemon process is not responding!'
                self._debugErr(exceptionToBeRaised)
            elif 'Expected header data' in errorInfo:
                self._debugErr('Server reported: %s' % errorInfo)
            elif 'forcibly closed by the remote host' in errorInfo:
                self._debugErr(errorInfo)
                self._restartServer()
            elif 'Not connected to the test server' in errorInfo:
                if not self.__connectingServer:
                    self._debugErr(errorInfo)
                    self._restartServer()
                else:
                    self._debugErr(errorInfo)
            else:
                exceptionToBeRaised = 'Unable to connect to device: %s' % errorInfo
                self._debugErr(exceptionToBeRaised)

            if exceptionToBeRaised:
                self.__connectionFailures += 1
                raise TABInterfaceException(exceptionToBeRaised)

            # raise exception if connection failures reach the maximum
            if self.__connectionFailures >= self.__maxNumberOfConnectionFailures:
                raise TABInterfaceException('Device connection failures reached the maximum: 10!')
        finally:
            self.__checkingDeviceConnectionStatus = False

    def __restartADB(self):
        """Restart ADB in order to get connection(s) back online.

            Returns True if connection is back online, False if not.
        """
        self.phone.warn('Restarting ADB...')
        self._closeConnection(sleepAfterClose = False, disconnectServices = False)

        adbRestartSucceeded = False

        for i in range(3):
            if TABInterface.RestartAdbServer():
                adbRestartSucceeded = True
                break

        if not adbRestartSucceeded:
            self.phone.warn('Restarting ADB did not work!')

        return self._waitForDeviceOnline()

    def __ensureDeviceRootAndRemount(self):
        """Check that device is rooted and remounted."""
        # check root and remount status
        if self._tabConn and core.FW_conf['settings'].System.AutomaticRootAndRemount:
            rootOK = False
            remountOK = False

            for i in range(5):
                # if we lose connection, break from the loop
                if not self._tabConn:
                    break

                try:
                    if not rootOK and not (self._tabConn.RootSuccess or self._tabConn.IsRooted):
                        self._executeTabOperation(self._tabConn.RootDevice)
                        debug.brf('Device rooted')
                    else:
                        rootOK = True
                except Exception, err:
                    self._debugErr('Error in checking device rooting status: %s'  % str(err))
                else:
                    try:
                        if not remountOK and not self._tabConn.RemountSuccess:
                            self._executeTabOperation(self._tabConn.RemountDevice)
                            debug.brf('Device remounted')
                        else:
                            remountOK = True
                    except Exception, err:
                        self._debugErr('Error in checking device remount status: %s'  % str(err))

                if rootOK and remountOK:
                    break
                else:
                    time.sleep(2)

            if not rootOK:
                self.phone.warn('Device is not rooted! Phone side ADB daemon may have serious problems!')

            if not remountOK:
                self.phone.warn('Device is not remounted! Phone side ADB daemon may have serious problems!')
        else:
            self.phone.warn('Automatic device rooting and remounting switched off')

    def _connectServer(self):
        """Connect to test server client."""
        # just return to avoid recursion
        if self.__connectingServer:
            return

        try:
            self.__connectingServer = True

            connected = self._isServerAvailable() and self._isServerConnected()

            for i in range(20):
                # just break if test execution is stopping
                if core.FW_conf['should_stop']:
                    break

                # break if too much connection errors
                if self.__connectionFailures >= self.__maxNumberOfConnectionFailures:
                    break

                try:
                    if self._isServerAvailable():
                        self._tabConn.TestServerClient.Connect()
                except Exception, err:
                    try:
                        self.__checkDeviceConnectionStatus(str(err))
                    except TABInterfaceException:
                        # if not called from checkUiFreeze
                        if not self.phone.exit.uiFreezeDetectionOngoing:
                            # if video recorder available, check UI freeze when TAB is reporting interface exception
                            if core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.phone.isMain():
                                self.phone.exit._checkUiFreeze()
                    except TestException:
                        raise # just raise TestException coming from __checkDeviceConnectionStatus
                    except Exception, err:
                        self._debugErr('Error occurred in checking device connection status: %s' % str(err))
                        self.__connectionFailures += 1
                finally:
                    if not (self._isServerAvailable() and self._isServerConnected()):
                        # first we try to just disconnect
                        self._disconnectServer()
                        time.sleep(2)

                        # connect if not connected
                        if not self.__isConnected(True):
                            self._closeConnection()  # this will also disconnect server and scripting service
                            self._createConnection(serialNumber = self._serialNumber)

                        # check root and remount status
                        self.__ensureDeviceRootAndRemount()

                        # in the end rounds we try to close and create connection again
                        if i > 10:
                            self._closeConnection(sleepAfterClose = False)
                            self._createConnection(serialNumber = self._serialNumber)
                    else:
                        connected = True
                        break

            if core.FW_conf['should_stop']:
                return

            if connected:
                self.__connectionFailures = 0
                self.__getTestServerClientMethods()
            else:
                self.__connectionFailures += 1

            # when connection failures reach the maximum, reboot the phone
            if self.__connectionFailures >= self.__maxNumberOfConnectionFailures:
                self.__connectionFailures = 0

                # if not called from checkUiFreeze, do ui freeze check
                if not self.phone.exit.uiFreezeDetectionOngoing and core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.phone.isMain():
                    self.phone.exit._checkUiFreeze()
                self.phone.resetPhone('Device connection failures reached the maximum: 10!', True) # True: wait for ram dump generation

            if not connected:
                raise TABInterfaceException('Device connection is not working! Cannot connect to test server!')
        finally:
            self.__connectingServer = False

    def _disconnectServer(self, dispose = False):
        """Disconnect from test server client."""
        try:
            if self._isServerAvailable():
                try:
                    # disconnect makes sure that all connection between PC and server are closed
                    if not self._tabConn.TestServerClient.Disconnect(True, True):
                        self._debugErr('TA server disconnect failed!')
                except ObjectDisposedException:
                    pass
                else:
                    if dispose:
                        self._tabConn.TestServerClient.Dispose()
        except Exception, err:
            try:
                self.__checkDeviceConnectionStatus(str(err))
            except TABInterfaceException:
                # if not called from checkUiFreeze
                if not self.phone.exit.uiFreezeDetectionOngoing:
                    # if video recorder available, check UI freeze when TAB is reporting interface exception
                    if core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.phone.isMain():
                        self.phone.exit._checkUiFreeze()
            except TestException:
                raise # just raise TestException coming from __checkDeviceConnectionStatus
            except Exception, err:
                self._debugErr('Error occurred in checking device connection status: %s' % str(err))
                self.__connectionFailures += 1

    def _restartServer(self):
        """Disconnect&connect server."""
        self._disconnectServer()
        self._connectServer()

    def __connectScriptingService(self):
        """Connect to scripting service client.

            Returns True if scripting service connected, if not False.
        """
        connected = False

        for i in range(3):
            try:
                if self._tabConn and getattr(self._tabConn, 'ScriptingServiceClient', None):
                    connected = self._tabConn.ScriptingServiceClient.Connect()
                    if connected:
                        break
            except Exception, err:
                self._debugErr('Unable to connect to scripting service: %s' % str(err))

                self.__disconnectScriptingService()
                time.sleep(2)
            else:
                scriptingServiceConnected = self.__scriptingServiceConnected()

                if not scriptingServiceConnected:
                    self.__disconnectScriptingService()
                    time.sleep(2)
                else:
                    connected = True
                    break

        return connected

    def __disconnectScriptingService(self):
        """Disconnect from scripting service client."""
        try:
            if getattr(self._tabConn, 'ScriptingServiceClient', None):
                self._tabConn.ScriptingServiceClient.Disconnect()
        except Exception, err:
            self._debugErr('Unable to disconnect scripting service: %s' % str(err))

    def _checkScriptingServiceConnection(self):
        """Check scripting service connection and reconnect if necessary."""
        scriptingServiceConnected = self.__scriptingServiceConnected()

        #debug.brf('scriptingServiceConnected: %s' % scriptingServiceConnected)

        if not scriptingServiceConnected:
            scriptingServiceConnected = self.__connectScriptingService()

            if scriptingServiceConnected:
                debug.brf('Scripting service connection created')
            else:
                self._debugErr('Unable to create scripting service connection!')

    def __scriptingServiceConnected(self):
        """Returns True if scripting service connected, False if not."""
        if self.serverLevelInUse and getattr(self._tabConn, 'ScriptingServiceClient', None):
            try:
                scriptingServiceConnected = self._tabConn.ScriptingServiceClient.IsConnected
            except Exception:
                scriptingServiceConnected = False
        else:
            scriptingServiceConnected = False

        return scriptingServiceConnected

    def __saveDump(self, dumpNode, prefix=''):
        """Save xml dump to file.

            Parameters

            dumpNode        dump node (NodeUtils instance)
            prefix        optional prefix name for saved dump file

            Return          path of the saved dump file
        """
        # create directory if needed
        dumpDir = os.path.join(core.FW_conf['test_result_dir'], 'xml_dumps')
        if not os.path.isdir(dumpDir):
            os.makedirs(dumpDir)

        firstNode = dumpNode.find('node')

        # get package name
        if firstNode:
            packageName = firstNode.getAttribute('package')
        else:
            packageName = 'unknown'

        if prefix:
            packageName = prefix + '_' + packageName

        # check if we have "visible" dump
        if dumpNode.getName() == 'visible_nodes':
            packageName = packageName + '_VISIBLE'

        dumpFilePath = os.path.join(dumpDir, '%s%s.xml' % (self.__phoneName != 'Main' and (self.__phoneName + '_') or '', packageName))

        dumpNode.save(dumpFilePath)
        return dumpFilePath

    def __saveCaptureNode(self, imageName, onlyImage, useExistingDump=False):
        """Saves capture node to test report.

            Parameters

            imageName          capture image name
            onlyImage          whether only image and no dump is generated
        """
        # to make sure that we always get right dimensions to image
        self._screenDimensionsQueried = False

        testStepNode = NodeUtils('teststep', True) # dummy test step needed by test report viewer
        testStepNode.setAttribute('name', 'display_capture')
        testStepNode.setAttribute('id', 1)
        testStepNode.setAttribute('stepId', 1)
        captureNode = NodeUtils('capture', True)
        captureNode.setAttribute('name', 'display_capture')
        captureNode.setAttribute('id', 4)
        testStepNode.append(captureNode)
        self.phone.result.tcReport.append(testStepNode)

        summaryNode = NodeUtils('summary', True) # capture tag needs to be under summary tag for Capture tool
        summaryNode.setAttribute('name', 'display_capture')
        summaryNode.setAttribute('id', 1)
        summaryNode.setAttribute('stepId', 1)
        captureNode = NodeUtils('capture', True)
        captureNode.setAttribute('id', 4) # dummy id needed by Capture tool, id 4 used be test report viewer

        bitmapNode = NodeUtils('bitmap', True)
        bitmapNode.setAttribute('x', 0)
        bitmapNode.setAttribute('y', 0)
        bitmapNode.setAttribute('width', self.getScreenWidth())
        bitmapNode.setAttribute('height', self.getScreenHeight())
        bitmapNode.setAttribute('name', imageName)
        captureNode.append(bitmapNode)

        if not onlyImage:
            for node in self._getVisibleNodes(useExistingDump).findall('//node'):
                # set coordinates
                coords = self._getCoordsFromBounds(node.getAttribute('bounds'))
                node.setAttribute('x', coords[0])
                node.setAttribute('y', coords[1])
                node.setAttribute('width', coords[2] - coords[0])
                node.setAttribute('height', coords[3] - coords[1])

                ## check if node is a text node
                #if node.getAttribute('text') != "" or node.getAttribute('content-desc') != "":
                #    textNode = NodeUtils('text', True)

                #    # set coordinates
                #    for attr in ['x', 'y', 'width', 'height']:
                #        textNode.setAttribute(attr, node.getAttribute(attr))

                #    # set text
                #    if node.getAttribute('text') != "":
                #        textNode['text'] = node.getAttribute('text')
                #    else:
                #        textNode['text'] = node.getAttribute('content-desc')

                #    captureNode.append(textNode)

                # add plain node by default
                captureNode.append(node.clone())

        summaryNode.append(captureNode)
        self.phone.result.tcReport.append(summaryNode)

        #debug.brf('test result: %s' % self.phone.result.tcReport.toprettyxml())

    def __replaceUnwantedCharacters(self, text):
        """Replaces special lines, dots, etc. with normal ones from given text."""
        text = text.replace(u"\N{HYPHEN}", '-').\
                    replace(u"\N{NON-BREAKING HYPHEN}", '-').\
                    replace(u"\N{FIGURE DASH}", '-').\
                    replace(u"\N{EN DASH}", '-').\
                    replace(u"\N{EM DASH}", '-').\
                    replace(u"\N{HORIZONTAL BAR}", '-').\
                    replace(u"\N{ONE DOT LEADER}", '.').\
                    replace(u"\N{HYPHENATION POINT}", '.').\
                    replace(u"\N{TWO DOT LEADER}", '..').\
                    replace(u"\N{HORIZONTAL ELLIPSIS}", '...')

        return text


    #def __waitForUIStateChange(self):
    #    """Wait for UI state change using events."""
    #    startTime = time.time()
    #    maximumDuration = 10000 # millisseconds
    #    eventInterval = 50 # millisseconds

    #    if self._tabConn and self.serverLevelInUse and getattr(self._tabConn, 'TestServerClient', None):
    #        while (time.time() < startTime + maximumDuration/1000):
    #            debug.brf('in loop')
    #            windowContentChanged = self._tabConn.TestServerClient.WaitForEventType(TABInterface.TABEvents.TYPE_WINDOW_CONTENT_CHANGED, eventInterval)
    #            viewScrolled = self._tabConn.TestServerClient.WaitForEventType(TABInterface.TABEvents.TYPE_VIEW_SCROLLED, eventInterval)
    #            textChanged = self._tabConn.TestServerClient.WaitForEventType(TABInterface.TABEvents.TYPE_VIEW_TEXT_CHANGED, eventInterval)

    #            # break when no more events
    #            if not windowContentChanged[0] and not viewScrolled[0] and not textChanged[0]:
    #                debug.brf('NO MORE EVENTS!')
    #                break

    #            if windowContentChanged[0]:
    #                debug.brf('windowContentChanged: %s' % str(windowContentChanged))
    #            if viewScrolled[0]:
    #                debug.brf('viewScrolled: %s' % str(viewScrolled))
    #            if textChanged[0]:
    #                debug.brf('textChanged: %s' % str(textChanged))

    def __waitForUIEvents(self, uiEventParams):
        """Wait for UI state change events in a separate thread.
           It will break away from the loop when UI events are no longer received or maximum timeout expires.

            Parameters

            uiEventParams           containing:

                                    eventInterval           event interval in milliseconds
                                    maximumDuration         maximum duration in milliseconds
                                    usePageFlipCount        whether page flip count information is used or not
        """
        eventInterval = uiEventParams.eventInterval
        maximumDuration = uiEventParams.maximumDuration
        usePageFlipCount = uiEventParams.usePageFlipCount

        #debug.brf('__waitForUIEvents: eventInterval: %s' % eventInterval)
        #debug.brf('__waitForUIEvents: maximumDuration: %s' % maximumDuration)
        #debug.brf('__waitForUIEvents: usePageFlipCount: %s' % usePageFlipCount)

        startTime = time.time()
        self.__windowStateChanged = False

        # use multiplier
        eventInterval *= self._timeoutMultiplier
        maximumDuration *= self._timeoutMultiplier

        def predicate(event):
            #debug.brf('event.EventType: %s' % event.EventType)

            if event.EventType == TABInterface.TABEvents.TYPE_WINDOW_CONTENT_CHANGED or \
               event.EventType == TABInterface.TABEvents.TYPE_WINDOW_STATE_CHANGED or \
               event.EventType == TABInterface.TABEvents.TYPE_VIEW_SCROLLED or \
               event.EventType == TABInterface.TABEvents.TYPE_VIEW_TEXT_CHANGED:
                #debug.brf('UI EVENT: %s' % event.EventType)
                self.__windowStateChanged = True
                return True
            else:
                return False

        if self._isServerAvailable():
            while (time.time() < startTime + float(maximumDuration)/1000):
                try:
                    # just break if test execution is stopping
                    if core.FW_conf['should_stop']:
                        break

                    if not self._tabConn.TestServerClient.WaitForEvent(predicate, eventInterval) and self.__windowStateChanged:
                        #debug.brf('NO MORE UI EVENTS!')

                        if usePageFlipCount and self.__pageFlipsIncoming():
                            continue

                        break
                    #else:
                    #    debug.brf('ui event')
                except Exception, err:
                    #self._debugErr('Exception in UI event thread: %s' % str(err))

                    # if connection is gone, exit from thread
                    if not (self._isServerAvailable() and self._isServerConnected()):
                        break

            #debug.brf('__waitForUIEvents: exit -->')

    def __waitForScrollEvents(self, uiEventParams):
        """Wait for scroll events in a separate thread.
           It will break away from the loop when scroll events are no longer received or maximum timeout expires.

            Parameters

            uiEventParams           containing:

                                    eventInterval           event interval in milliseconds
                                    maximumDuration         maximum duration in milliseconds
        """
        # NOTE: Page flip count is always used in scroll by default
        #debug.brf('__waitForScrollEvents')

        maximumDuration = uiEventParams.maximumDuration
        eventInterval = uiEventParams.eventInterval
        self.__screenScrolled = None

        # wait value for the first scroll event
        # NOTE: quite big initial wait used here in case that scroll events are not arriving in sync with the movement or not at all
        initialWait = 3000 + eventInterval
        # wait value when no more scroll events so that we'll get updated xml dump for sure
        waitAfterScroll = 1000 + eventInterval

        initialWaitUsed = False
        startTime = time.time()

        # use multiplier
        eventInterval *= self._timeoutMultiplier
        maximumDuration *= self._timeoutMultiplier
        initialWait *= self._timeoutMultiplier

        # NOTE: Must be multiplied by 2 because getting event to PC side takes time. Also we want always to wait some extra
        eventInterval *= 2

        #debug.brf('__waitForScrollEvents: eventInterval: %s' % eventInterval)
        #debug.brf('__waitForScrollEvents: initialWait: %s' % initialWait)
        #debug.brf('__waitForScrollEvents: waitAfterScroll: %s' % waitAfterScroll)

        self.__scrollEventTime = 0
        self.__scrollEventInterval = 0

        def predicate(event):
            if event.EventType == TABInterface.TABEvents.TYPE_VIEW_SCROLLED:
                # calculate scroll event interval from event timestamp
                if self.__scrollEventTime != 0:
                    self.__scrollEventInterval = event.EventTime - self.__scrollEventTime

                self.__scrollEventTime = event.EventTime
                return True
            else:
                return False

        if self._isServerAvailable():
            while (time.time() < startTime + maximumDuration/1000):
                #debug.brf('scroll event loop')

                try:
                    # just break if test execution is stopping
                    if core.FW_conf['should_stop']:
                        break

                    #debug.brf('self.__screenScrolled: %s' % self.__screenScrolled)

                    if not initialWaitUsed:
                        interval = initialWait
                        initialWaitUsed = True
                    else:
                        interval = eventInterval

                    #debug.brf('scroll event interval: %s' % interval)

                    if not self._tabConn.TestServerClient.WaitForEvent(predicate, interval):
                        # continue if page flips coming
                        if self.__pageFlipsIncoming():
                            #debug.err('pageFlips incoming')
                            continue

                        if self.__screenScrolled == None:
                            self.__screenScrolled = False
                        # NOTE: page flip count is -1 when device is not rooted and page flip count is not available
                        elif not self.__pageFlipCountSuccess:
                            #debug.err('pageFlipsCount was not success')
                            # wait after scroll to ensure that we get correct display dump afterwards
                            #debug.brf('waiting for %s after scroll...' % float(float(waitAfterScroll) / float(1000)))
                            time.sleep(float(float(waitAfterScroll) / float(1000)))

                            prevXmlDump = None

                            # loop to ensure that UI stabilizes
                            for i in range(10):
                                xmlDump = self._getDump()

                                if xmlDump and prevXmlDump == xmlDump:
                                    #debug.brf('DUMPS SAME!!!')
                                    break
                                #elif prevXmlDump != None:
                                    #debug.brf('DUMPS DIFFERENT!!!')

                                prevXmlDump = xmlDump
                                time.sleep(0.2)

                        #debug.brf('self.__screenScrolled --> %s' % self.__screenScrolled)
                        #debug.brf('NO MORE SCROLL EVENTS!')
                        break
                    else:
                        self.__screenScrolled = True
                        #debug.brf('self.__screenScrolled --> %s' % self.__screenScrolled)

                        if self.__scrollEventInterval != 0:
                            self.__scrollEventCount += 1

                            #debug.brf('scroll event interval: %s' % self.__scrollEventInterval)
                            #debug.brf('scroll event count: %s' % self.__scrollEventCount)

                            self.__scrollEventSum += self.__scrollEventInterval
                            self.averageScrollEventInterval = int(self.__scrollEventSum / self.__scrollEventCount)

                            #debug.brf('average scroll event interval: %s' % self.averageScrollEventInterval)

                        #debug.brf('scroll event')
                except Exception, err:
                    self._debugErr('Exception in scroll event thread: %s' % str(err))

                    # if connection is gone, exit from thread
                    if not (self._isServerAvailable() and self._isServerConnected()):
                        break

            #debug.brf('__waitForScrollEvents: exit -->')

    def __waitForSpecificEvent(self, eventInterval, maximumDuration = 30000):
        """Wait for specific event in a separate thread.
           It will break away from the loop when event is received or maximum timeout expires.

            Parameters

            eventInterval           event interval in milliseconds
            maximumDuration         maximum duration in milliseconds
        """
        startTime = time.time()

        def predicate(event):
            if event.EventType == getattr(TABInterface.TABEvents, self.__waitSpecificEvent, None):
                return True
            else:
                return False

        if self._isServerAvailable():
            while (time.time() < startTime + maximumDuration/1000):
                try:
                    # just break if test execution is stopping
                    if core.FW_conf['should_stop']:
                        break

                    if not self._tabConn.TestServerClient.WaitForEvent(predicate, eventInterval):
                        break
                except Exception, err:
                    #self._debugErr('Exception in specific event thread: %s' % str(err))

                    # if connection is gone, exit from thread
                    if not (self._isServerAvailable() and self._isServerConnected()):
                        break

    def _startUIEventThread(self, eventInterval=None, maximumDuration=None, usePageFlipCount=False):
        """Starts thread for UI events.

            eventInterval           event interval in milliseconds
            maximumDuration         maximum duration in milliseconds
            usePageFlipCount        whether page flip count information is used or not
        """
        self._stopUIEventThread()

        if self.overrideEventInterval != 0:
            eventInterval = self.overrideEventInterval

        if not eventInterval:
            eventInterval = self.__eventInterval

        if not maximumDuration:
            maximumDuration = self.__maximumDuration

        if not self.__UIEventThread:
            uiEventParams = UIEventParams()
            uiEventParams.eventInterval = eventInterval
            uiEventParams.maximumDuration = maximumDuration
            uiEventParams.usePageFlipCount = usePageFlipCount

            self.__UIEventThread = Thread(ParameterizedThreadStart(self.__waitForUIEvents))
            self.__UIEventThread.IsBackground = True
            self.__UIEventThread.Start(uiEventParams)

    def __startScrollEventThread(self, eventInterval = 500, maximumDuration = 10000):
        """Starts thread for scroll events.

            eventInterval           event interval in milliseconds
            maximumDuration         maximum duration in milliseconds
        """
        #debug.brf('__startScrollEventThread')
        self.__stopScrollEventThread()

        if not self.__scrollEventThread:
            uiEventParams = UIEventParams()

            # use automatic interval if available
            if self.averageScrollEventInterval != 0:
                #debug.brf('Using automatic scroll event interval: %s' % (self.averageScrollEventInterval))
                uiEventParams.eventInterval = self.averageScrollEventInterval
            else:
                uiEventParams.eventInterval = eventInterval

            uiEventParams.maximumDuration = maximumDuration

            self.__scrollEventThread = Thread(ParameterizedThreadStart(self.__waitForScrollEvents))
            self.__scrollEventThread.IsBackground = True
            self.__scrollEventThread.Start(uiEventParams)

    def __startSpecificEventThread(self, eventInterval = 2000):
        """Starts thread for specific events.

            eventInterval           event interval in milliseconds
        """
        self.__stopSpecificUIEventThread()

        if not self.__specificUIEventThread:
            self.__specificUIEventThread = Thread(ParameterizedThreadStart(self.__waitForSpecificEvent))
            self.__specificUIEventThread.IsBackground = True
            self.__specificUIEventThread.Start(eventInterval)

    def _joinUIEventThread(self):
        """Joins thread for UI events to main."""
        if self.__UIEventThread and \
           self.__UIEventThread.IsAlive:
            self.__UIEventThread.Join()

    def __joinScrollEventThread(self):
        """Joins thread for scroll events to main."""
        if self.__scrollEventThread and \
           self.__scrollEventThread.IsAlive:
            self.__scrollEventThread.Join()

    def _joinSpecificUIEventThread(self):
        """Joins specific thread for UI events to main."""
        if self.__specificUIEventThread and \
           self.__specificUIEventThread.IsAlive:
            self.__specificUIEventThread.Join()

    def _stopUIEventThread(self):
        """Stops thread for UI events."""
        # NOTE: this is just in case here, thread is joined every time so it should not be alive anymore here
        if self.__UIEventThread and \
           self.__UIEventThread.IsAlive:
            self.__UIEventThread.Abort()

        self.__UIEventThread = None

    def __stopScrollEventThread(self):
        """Stops thread for scroll events."""
        # NOTE: this is just in case here, thread is joined every time so it should not be alive anymore here
        if self.__scrollEventThread and \
           self.__scrollEventThread.IsAlive:
            self.__scrollEventThread.Abort()

        self.__scrollEventThread = None

    def __stopSpecificUIEventThread(self):
        """Stops specific thread for UI events."""
        # NOTE: this is just in case here, thread is joined every time so it should not be alive anymore here
        if self.__specificUIEventThread and \
           self.__specificUIEventThread.IsAlive:
            self.__specificUIEventThread.Abort()

        self.__specificUIEventThread = None

    def _stopEventThreads(self):
        """Stops all possible running event threads."""
        self._stopUIEventThread()
        self.__stopScrollEventThread()
        self.__stopSpecificUIEventThread()

    def __inListViewBounds(self, node):
        """Checks if given point is in current list view's bounds or not.

            Parameters

            node            dump node (NodeUtils instance)

            Returns True, if node's center point is in list view's bounds
            Returns False, if node's center point is not in list view's bounds
            Returns None, list view is not found or node is not under list view
        """
        listViewNode = node.find('ancestor::node[@scrollable="true"][1]')

        if listViewNode:
            left, top, right, bottom = self._getCoordsFromBounds(listViewNode.getAttribute('bounds'))
            itemLeft, itemTop, itemRight, itemBottom = self._getCoordsFromBounds(node.getAttribute('bounds'))
            centerX, centerY = self._getCenterCoordsFromBoundCoords([itemLeft, itemTop, itemRight, itemBottom])

            # node's center point is in list view bounds
            if centerX > left and centerX < right and \
               centerY > top and centerY < bottom:
                return True
            # node's center point is not in list view bounds
            else:
                return False
        else:
            return None

    def _getLaunchableApplications(self):
        """Get C# dict of launchable applications."""
        self._checkScriptingServiceConnection()

        success = False

        for i in range(10):
            try:
                # get launchable applications
                success, response = self._executeTabOperation(self._tabConn.ScriptingServiceClient.getLaunchableApplications)
                break
            except Exception, err:
                self._debugErr('Error when executing getLaunchableApplications: %s' % str(err))

                self.__disconnectScriptingService()
                time.sleep(2)
                self.__connectScriptingService()

        if success:
            launchableApplications = response
            self.__launchableApplications = launchableApplications
        else:
            self._debugErr('Unable to get launchable applications, using previous dict..')
            launchableApplications = self.__launchableApplications

        return launchableApplications

    def _getCurrentPackageName(self):
        """Returns current package name using TA server."""
        currentPackage = ''

        if self._isServerAvailable() and self._isServerConnected():
            success, response = self._executeTabOperation(self._tabConn.TestServerClient.getCurrentPackageName)

            if success:
                currentPackage = response

        return currentPackage

    def __wildcardSearch(self, expression, visibleItems):
        """ Check if wildcard search matches with visible item(s)

            Parameters

            expression (str)        Searched expression e.g. 'Mess?ges' or *ssag* etc.
            visibleItems (dict)     Dictionary of visible items

            Returns list of found nodes' coordinates
        """
        coordsOfNodesFound = []

        if "*" in expression or "?" in expression or ("[" in expression and "]" in expression):
            for visibleItem in visibleItems.keys():
                # NOTE: fnmatch doesn't work if item contains "\n" - marks
                if fnmatch.fnmatch(visibleItem.replace('\n', ' '), expression):
                    # add found node's coordinate point to the list
                    coordsOfNodesFound.append(visibleItems[visibleItem])

        return coordsOfNodesFound

    def _setDisallowedBinderNames(self):
        if self._tabConn:

            self._tabConn.DisAllowedBinderNames.Clear()

            names = ("Touch", "DisableLockScreen", "Back", "Input", \
                     "TouchAction", "tap", "longTap", "tapSequence", "volDown", \
                     "volUp", "pressHome", "swipeRegion", \
                     "sendKey", "sendLongKey", "touchMove", "touchUp", "touchDown", \
                     "swipe", "scrollSwipe", "drag", "pinch", "pinchOut", "pinchIn", "curvedSwipe" )

            for s in names:
                self._tabConn.DisAllowedBinderNames.Add(s)

    def _isServerAvailable(self):
        """Returns TA server's availability."""
        try:
            if self._tabConn and self.serverLevelInUse and getattr(self._tabConn, 'TestServerClient', None):
                return True
            else:
                return False
        except Exception:
            # TestServerClient can be disposed here
            return False

    def _isServerConnected(self):
        """Returns TA server's connection status."""
        serverConnected = False

        try:
            #debug.brf('----: %s' % self._tabConn.TestServerClient.ConnectionState)
            #debug.brf('----: %s' % self._tabConn.TestServerClient.ConnectionState.Connected)

            serverConnected = self._tabConn.TestServerClient.IsConnected
        except Exception, err:
            #self._debugErr('Server no longer connected, exception: %s' % str(err))
            # catch all exceptions --> serverConnected = False
            pass

        return serverConnected

    def isConnected(self):
        """ return True if phone is connected, otherwise False """
        return self._isConnectedAndReady()[0]

    def _isConnectedAndReady(self, bootCheckOnly = False, timeout = 120):
        """ return whether device is connected and boot finished

            Parameters

            bootCheckOnly           perform boot check only (default = False)
            timeout                 timeout in seconds how long we will wait

            Return
                True, True  :   Connected, boot finished
                True, False :   Connected, still booting up
                False, False:   Not connected
        """
        if not bootCheckOnly and not self.__isConnected(True):
            return False, False

        # TODO: when isOnline works, this check can be removed
        # NOTE: Can't use _executeTabOperation here, because it's starts to check connection/remount etc. statuses which are not needed
        try:
            if not self._serialNumber in TABInterface.GetDevices(TABInterface.DeviceType.ANY):
                return False, False
        except Exception:
            return False, False

        # perform boot check with WaitBooted
        if self._tabConn:
            success, booted = self._executeTabOperation(self._tabConn.WaitBooted, TimeSpan(0, 0, 0, timeout, 0))

            if success and booted:
                return True, True
            else:
                return True, False
        else:
            return True, False

        #deviceInfo = self.deviceInfo(doNotReport = True)

        #bootCompleteFlag = None
        #bootCompletedFlag = None
        #bootAnimFlag = None

        #if deviceInfo.has_key('dev.bootcomplete'):
        #    if deviceInfo['dev.bootcomplete'] == '1':
        #        bootCompleteFlag = True
        #    else:
        #        bootCompleteFlag = False

        #if deviceInfo.has_key('sys._boot_completed'):
        #    if deviceInfo['sys._boot_completed'] == '1':
        #        bootCompletedFlag = True
        #    else:
        #        bootCompletedFlag = False

        #if deviceInfo.has_key('init.svc.bootanim'):
        #    if deviceInfo['init.svc.bootanim'] == 'stopped':
        #        bootAnimFlag = True
        #    else:
        #        bootAnimFlag = False

        ##debug.brf('bootCompleteFlag: %s' % bootCompleteFlag)
        ##debug.brf('bootCompletedFlag: %s' % bootCompletedFlag)
        ##debug.brf('bootAnimFlag: %s' % bootAnimFlag)

        #booted = (bootCompleteFlag == None or bootCompleteFlag == True) and \
        #         (bootCompletedFlag == None or bootCompletedFlag == True) and \
        #         (bootAnimFlag == None or bootAnimFlag == True)

        ##debug.brf('booted: %s' % booted)

        #return True, booted

    def __isConnected(self, connectionOnly = False):
        """Return connection status.

            Parameters

            connectionOnly      Return only main connection status

            Returns tuple (connection status (True/False), server connected (True/False/None)
        """
        if self._tabConn:
            try:
                connected = self._tabConn.IsOnline
            except Exception:
                connected = False

            if connectionOnly:
                return connected
            else:
                if self.serverLevelInUse:
                    serverConnected = self._isServerAvailable() and self._isServerConnected()

                    #if not serverConnected:
                    #    self._debugErr('Test server no longer connected!')

                    #debug.brf('connected: %s' % connected)
                    #debug.brf('serverConnected: %s' % serverConnected)

                    return (connected, serverConnected)
                else:
                    return (connected, None)
        else:
            if connectionOnly:
                return False
            else:
                return (False, None)

    def ___pressHWKeyInLoop(self, hwKey):
        """Press HW key in a loop. Used in clear thread.

            Parameters

            hwKey           HW key value
        """
        while True:
            Monitor.Enter(self.__mObject)
            try:
                self._executeTabOperation(self._tabConn.TestServerClient.sendKey, hwKey, 0)
            finally:
                Monitor.Exit(self.__mObject)

    def ___pressTouchCoordsInLoop(self, params):
        """Press touch point in loop. Used in clear thread.

            Parameters

            x,y           Touch coordinates
        """
        while True:
            Monitor.Enter(self.__mObject)
            try:
                self._touchWithCoords(params.x, params.y)
            finally:
                Monitor.Exit(self.__mObject)

    def _touchWithCoords(self, x, y, long=False):
        """Touch given coordinate point.

            Parameters

            x           x coordinate
            y           y coordinate
        """
        debug.out('tab_interface: Press to coordinates: %s,%s. Long: %s' % (x, y, long))
        if long:
            length = 1500 # default long press delay
        else:
            length = None

        self.phone._touch.press((x,y), length)
        self.phone._run('tab_interface: Press to coordinates: %s,%s' % (x,y))

    def _touchWithResourceId(self, resourceId, useExistingDump = True, longTap = False):
        """Touch coordinate point of given resource id

            Parameters

            resourceId          resource id
            useExistingDump     use existing dump (default = True)
            longTap             use long tap (default = False)
        """
        try:
            x, y = 0, 0

            for textDict in self._getVisibleTexts(useExistingDump = useExistingDump):
                if textDict['resource-id'] == resourceId:
                    x = textDict['center_x']
                    y = textDict['center_y']
                    break
            debug.out('_touchWithResourceId %s to coordinates: %s %s' % (resourceId, x, y))
            if x != 0 and y != 0:
                if longTap:
                    self._touchWithCoords(x,y, long=True)
                else:
                    self._touchWithCoords(x,y)

            #else:
            #    self._debugErr('Resource id: "%s" not found!' % resourceId)
        except Exception, err:
            self._debugErr('Exception during touch with coords: %s' % str(err))

    def _getVisibleNodes(self, useExistingDump = False):
        """Get visible nodes using XML dump from the phone.

            Parameters

            useExistingDump         use existing dump (default = False)

            Returns NodeUtils instance containing visible nodes
        """
        if useExistingDump:
            dumpNode = self._currentDump
        else:
            # get display dump in XML
            dumpNode = self._getDump()

        # get display width and height from first node
        firstNode = dumpNode.find('//node')
        if firstNode:
            boundCoords = self._getCoordsFromBounds(firstNode.getAttribute('bounds'))

            # if server interface not available, get screen width and height from the dump
            if not self._isServerAvailable():
                self.__screenWidth = boundCoords[2]
                self.__screenHeight = boundCoords[3]

        #debug.brf('***: %s' % dumpNode.toprettyxml())
        searchString = '//node'

        visibleNodes = NodeUtils('visible_nodes', True)

        for node in dumpNode.findall(searchString):
            if node.getAttribute('bounds') != "":
                left, top, right, bottom = self._getCoordsFromBounds(node.getAttribute('bounds'))
                centerX, centerY = self._getCenterCoordsFromBoundCoords([left, top, right, bottom])

                # leave item which is not in list bounds away
                if self.__inListViewBounds(node) == False:
                    continue

                # leave out of the screen nodes away
                if top < 0 or bottom > self.getScreenHeight():
                    # check if clickable item's center point is in screen area
                    # if yes, let's keep the node
                    if node.getAttribute('clickable') == 'true':
                        if centerX >= self.getScreenWidth() or \
                            centerY >= self.getScreenHeight():
                            continue
                    else:
                        continue

                # leave out if width or height is 0 or below
                if ((right - left) <= 0) or ((bottom - top) <= 0):
                    continue

                # leave not supported nodes away (preserve nodes having text or content description)
                if node.getAttribute('class') in ['android.widget.FrameLayout', 'android.widget.RelativeLayout', 'android.widget.LinearLayout', 'android.widget.ListView',
                                                  'android.widget.GridView', 'android.widget.ScrollView', 'android.support.v4.view.ViewPager', 'android.widget.TabWidget', 'android.view.View'] and \
                   node.getAttribute('text') == "" and node.getAttribute('content-desc') == "" and node.getAttribute('resource-id') == "":
                    continue

                # place coordinate attributes
                node.setAttribute('left', left)
                node.setAttribute('top', top)
                node.setAttribute('right', right)
                node.setAttribute('bottom', bottom)
                node.setAttribute('center-x', centerX)
                node.setAttribute('center-y', centerY)

                # replace unwanted characters in text attribute
                if node.getAttribute('text') != "":
                    node.setAttribute('text', self.__replaceUnwantedCharacters(node.getAttribute('text')))
                    #debug.brf('text node: %s' % node.toprettyxml())

                # switch button, checkbox or radio button can have related item
                if node.getAttribute('class') in ['android.widget.Switch', 'android.widget.CheckBox', 'android.widget.RadioButton']:
                    parentNode = node.parent().clone()
                    # if closest parent has no text, get it from parents parent
                    if not parentNode.findall('//node[@class="android.widget.TextView"]'):
                        parentNode = node.parent().parent().clone()

                    siblingTextNode = None

                    # find sibling node so that we can find related text / content
                    for parNode in parentNode.findall('//node'):
                        if parNode.getAttribute('class') == 'android.widget.TextView':
                            siblingTextNode = parNode
                            break

                    if siblingTextNode:
                        #debug.brf('siblingTextNode: %s' % siblingTextNode.toprettyxml())

                        if siblingTextNode.getAttribute('text') != "":
                            node.setAttribute('related_text', siblingTextNode.getAttribute('text'))
                        elif siblingTextNode.getAttribute('content-desc') != "":
                            node.setAttribute('related_content', siblingTextNode.getAttribute('content-desc'))

                # append supported node (add only node itself, no child nodes)
                visibleNodes.append(node.clone(deep = False))

        # store visible nodes
        self.__currentVisible = visibleNodes

        # save dump to file
        self.__saveDump(visibleNodes)

        return visibleNodes

    def _getVisibleTexts(self, returnAsDict = True, useExistingDump = False):
        """Get visible texts using XML dump from the phone.

            Parameters

            returnAsDict            If True, returns list of dictionaries {<text> : (<centerX>, <centerY>)}
                                    If False, returns list of texts
            useExistingDump         use existing dump (default = False)
        """
        textList = []

        for node in self._getVisibleNodes(useExistingDump).findall('//node'):
            # check if node is a text node
            if node.getAttribute('text') != "" or node.getAttribute('content-desc') != "":
                textDict = {}
                #debug.brf('***: %s' % node.toprettyxml())

                coords = self._getCoordsFromBounds(node.getAttribute('bounds'))
                centerX, centerY = self._getCenterCoordsFromBoundCoords(coords)

                text = node.getAttribute('text')

                textDict['text'] = text
                textDict['center_x'] = centerX
                textDict['center_y'] = centerY
                textDict['x'] = coords[0]
                textDict['y'] = coords[1]
                textDict['width'] = coords[2] - coords[0]
                textDict['height'] = coords[3] - coords[1]
                textDict['package'] = node.getAttribute('package')
                textDict['resource-id'] = node.getAttribute('resource-id')
                textDict['content-desc'] = node.getAttribute('content-desc')

                if returnAsDict:
                    textList.append(textDict)
                else:
                    if text != "":
                        textList.append(text)

        return textList

    def __createIndexTree(self, dumpNode):
        """Adds index tree and layer attributes to xml dump.

            Parameters

            dumpNode        xml dump node (NodeUtils)
        """
        if dumpNode.getAttributes():
            index = dumpNode.getAttribute("index")

            if index != "":
                indexTree = str(index)

                parentNode = dumpNode.parent()

                if parentNode:
                    parentIndexTree = parentNode.getAttribute("index")

                    if parentIndexTree != "":
                        indexTree = parentIndexTree + '-' + indexTree

                dumpNode.setAttribute('index', indexTree)
                dumpNode.setAttribute('layer', len(indexTree.split('-')))

        if dumpNode.getChildNodes():
            for childNode in dumpNode.getChildNodes():
                self.__createIndexTree(childNode)

    def _waitUntilNoUIEvents(self, eventInterval = 800, maximumDuration = 3000, usePageFlipCount=False):
        """Wait until there's no UI events

            Parameters

            eventInterval           event interval in milliseconds
            maximumDuration         maximum duration in milliseconds
            usePageFlipCount        whether page flip count information is used or not
        """
        try:
            self._startUIEventThread(eventInterval, maximumDuration, usePageFlipCount)
        finally:
            self._joinUIEventThread()
            self._stopUIEventThread()

    def _waitForDeviceOnline(self, timeout = 120):
        """Wait until device is back online.

            Parameters

            timeout         timeout in seconds how long we will wait

            Returns True if device is connected, raises TABInterfaceException if not
        """
        debug.brf('Waiting for device to get back online...')

        wasOffline = False
        connectionCreated = False
        connected = False

        # just return to avoid recursion
        if self.__waitingForDeviceOnline:
            return

        try:
            # set flag to True to avoid unnecessary error prompts during loop
            self.__waitingForDeviceOnline = True

            waitStart = time.time()

            while (time.time() < waitStart + timeout):
                try:
                    self.phone.sendWaitMessageToMarbleGUI(timeout, 'Waiting for device to get back online...')

                    connected, booted = self._isConnectedAndReady(bootCheckOnly = True, timeout = timeout)

                    #debug.brf('connected: %s' % connected)
                    #debug.brf('booted: %s' % booted)
                    #debug.brf('wasOffline: %s' % wasOffline)

                    if connected and booted and wasOffline:
                        #debug.brf('back online!')
                        # restart logging when device is back online
                        self._startLogging()
                        break
                    elif connected and booted:
                        #debug.brf('device online!')
                        break
                    elif connected and not booted and wasOffline and not connectionCreated:
                        debug.brf('Device online, recreating connection...')

                        self._createConnection(serialNumber = self._serialNumber)
                        connectionCreated = True
                    elif not connected:
                        #debug.brf('device offline')
                        if not wasOffline:
                            # stop logging when device goes offline
                            self._stopLogging()

                            # initial sleep
                            time.sleep(20)

                        wasOffline = True
                except Exception, err:
                    self._debugErr('Exception: "%s" when checking device connection' % str(err))
                    # exceptions don't matter here, just ask again
                    pass

                time.sleep(1)
        finally:
            self.__waitingForDeviceOnline = False

        if not connected:
            self.__connectionFailures += 1
            self._debugErr('Device "%s" is no longer connected!' % self._serialNumber)

        return connected

    def _startLogging(self, clearBuffer = True):
        """Start logging

            Parameters

            clearBuffer     Value indicating whether to clear the log before
        """
        if self.phone.isMain() and self._tabConn and not self.__logging and (core.FW_conf['settings'].TestRun.LoggingEnabled or core.FW_conf['cli_logging']):
            logFilePath = os.path.join(core.FW_conf['test_result_dir'], 'logging', 'MarbleLog%s.txt' % DateTime.Now.ToString("yyyyMMddHHmmss"))

            try:
                # set log format
                self._tabConn.Logger.OutputFormat = getattr(OutputFormat, core.FW_conf['settings'].TestRun.LogFormat)

                self._tabConn.StartLogging(logFilePath, clearBuffer)

                # store log file directory so that we know to restart logging if path changes
                self.__logFileDir = core.FW_conf['test_result_dir']

                self.__logging = True
            except Exception, err:
                self._debugErr('Unable to start logging: %s' % str(err))

    def _stopLogging(self, clearBuffer = False):
        """Stop logging.

            Parameters

            clearBuffer     Value indicating whether to clear the log before
        """
        if self._tabConn and self.__logging:
            try:
                self._tabConn.StopLogging(clearBuffer)
                self.__logging = False
            except Exception, err:
                self._debugErr('Unable to stop logging: %s' % str(err))

    def __checkLogging(self):
        """Check logging status."""
        if self._tabConn:
            # start logging
            if (core.FW_conf['settings'].TestRun.LoggingEnabled or core.FW_conf['cli_logging']) and not self.__logging:
                self._startLogging()
            # stop logging
            elif not (core.FW_conf['settings'].TestRun.LoggingEnabled or core.FW_conf['cli_logging']) and self.__logging:
                self._stopLogging()
            # restart logging with different log format
            elif (core.FW_conf['settings'].TestRun.LoggingEnabled or core.FW_conf['cli_logging']) and self.__logging and \
                 self._tabConn.Logger.OutputFormat != getattr(OutputFormat, core.FW_conf['settings'].TestRun.LogFormat):
                self._stopLogging()
                self._startLogging()
            # restart logging if directory has changed
            elif self.__logFileDir != '' and self.__logFileDir != core.FW_conf['test_result_dir']:
                self._stopLogging()
                self._startLogging()

    def __exitFromLetterView(self, itemName, visibleTexts):
        """Exit from letter view in homescreen's application list.

            Parameters

            itemName            item name which we are searching
            visibleTexts        dict of currently visible texts
        """
        textToTap = None

        # check that does the first letter of searched item match to any of the visible texts
        for visibleText in visibleTexts.keys():
            if itemName[0] == visibleText:
                textToTap = visibleText
                break

        # if first letter doesn't match, let's just select the first letter
        if not textToTap:
            for visibleText in visibleTexts.keys():
                if len(visibleText) == 1:
                    textToTap = visibleText
                    break

        if textToTap:
            self.phone.comment('Pressing "%s" in order to exit from letter view in application list' % textToTap)
            self._touchWithCoords(visibleTexts[textToTap][0], visibleTexts[textToTap][1])
        else:
            self.phone.warn('Unable to determine which letter to press in __exitFromLetterView')

    def _backSwipe(self, reverse = False, light = False):
        """Perform back swipe to change status of the phone."""

        yCoordinate = int(self.getScreenHeight() / 1.5)

        if reverse:
            fromPoint = (2, yCoordinate)

            if light:
                toPoint = ((self.getScreenWidth() / 2)-2, yCoordinate)
            else:
                toPoint = (self.getScreenWidth()-2, yCoordinate)
        else:
            fromPoint = (self.getScreenWidth()-2, yCoordinate)

            if light:
                toPoint = ((self.getScreenWidth() / 2)+2, yCoordinate)
            else:
                toPoint = (2, yCoordinate)

        debug.out('tab_interface: drawLine %s -> %s' % (str(fromPoint), str(toPoint)) )
        self.phone._touch.drawLine(fromPoint, toPoint, stepSize = 100)
        self.phone._run('tab_interface: gesture.swipe(%s,%s)'%( str(fromPoint), str(toPoint)))

        self._waitUntilNoUIEvents(eventInterval = 1000, usePageFlipCount = True)

    def __getKeyCodes(self):
        """Get device's key codes and store them if needed."""
        if not self.__keyCodes:
            success, keyCodes = self._executeTabOperation(self._tabConn.TestServerClient.getKeyCodes)

            if success:
                self.__keyCodes = keyCodes
            else:
                self._debugErr('Unable to retrieve key codes with getKeyCodes!')

    def _debugErr(self, errorMessage):
        """debug.err given error message."""
        if not core.FW_conf['should_stop'] and errorMessage:
            debug.err(errorMessage)

    def _addLogMarker(self, marker):
        """Add marker to log file

            Parameters

            marker      marker string to be added to log
        """
        assert isinstance(marker, str) and marker != "", 'Invalid marker string given: %s' % str(marker)

        self.__checkLogging()

        if self._tabConn and self.__logging:
            try:
                self._tabConn.Logger.AddMarkerToLogFile(marker)
            except Exception, err:
                self._debugErr('Unable to set marker to log file: %s' % str(err))

    def __getScreenDimensions(self):
        """Get screen width and height."""
        # ask dimensions from server if available
        if self._isServerAvailable() and not self._screenDimensionsQueried:
            success, screenWidth = self._executeTabOperation(self._tabConn.TestServerClient.getDisplayWidth)
            if success:
                self.__screenWidth = screenWidth

            success, screenHeight = self._executeTabOperation(self._tabConn.TestServerClient.getDisplayHeight)
            if success:
                self.__screenHeight = screenHeight

            self._screenDimensionsQueried = True

    def getScreenWidth(self):
        """Returns device's screen width."""
        self.__getScreenDimensions()

        return self.__screenWidth

    def getScreenHeight(self):
        """Returns device's screen height"""
        self.__getScreenDimensions()

        return self.__screenHeight

    def _createConnection(self, deviceType = TABInterface.DeviceType.ANY, serialNumber = "", serverLevelInUse = True):
        """Create TAB connection

            Parameters

            deviceType          HW, EMULATOR, ANY
            serialNumber        serial number of the device (if given, deviceType doesn't count)
            serverLevelInUse    use TA server level (default = True)
        """
        assert serverLevelInUse in [True, False], 'serverLevelInUse is boolean parameter!'

        self.serverLevelInUse = serverLevelInUse

        # just return if already connected
        if self.__isConnected(True):
            # close existing connection if serial number has changed
            if self._serialNumber and self._serialNumber != serialNumber:
                self._closeConnection()
            else:
                return

        try:
            debug.brf('Opening connection%s...' % (serialNumber != "" and ' to device: %s' % serialNumber or ''))

            # set ADB path so that TABInterface can restart ADB if needed
            TABInterface.SetADBPath(self.__adbPath)

            if serialNumber != "":
                self._serialNumber = serialNumber
                self._tabConn = TABInterface.CreateConnectionWithSerial(serialNumber, core.FW_conf['settings'].System.AutomaticRootAndRemount, self.serverLevelInUse, core.FW_conf['ci_enabled'])
            else:
                assert deviceType in [self.HW, self.EMULATOR, self.ANY], 'Wrong deviceType parameter given!'

                self._tabConn = TABInterface.CreateConnection(deviceType, core.FW_conf['settings'].System.AutomaticRootAndRemount, self.serverLevelInUse, core.FW_conf['ci_enabled'])

                if self._tabConn:
                    self._serialNumber = self._tabConn.SerialNumber
        except TABException, err:
            self._debugErr('Unable to create connection to device! Error: %s' % str(err))
            self._tabConn = None
            self.__connectionFailures += 1

            # reset usb connection (usually it restores device to online state)
            if core.FW_conf['blackbox_enabled'] and self.phone.isMain():
                self.phone._blackBoxResetPhoneUsbConnection(createConnection = False)
                self.phone.comment('Disconnect and connect USB connection (%s) in order to get device back online' % core.FW_conf['blackbox'].getDefaultUsbAccessoryConnector())
                self.phone._ensureBlackBoxUsbAccessoryConnection()

            raise
        except Exception, err:
            self._debugErr('Unknown exception in connection creation! Error: %s' % str(err))
            self._tabConn = None
            self.__connectionFailures += 1
            raise
        else:
            if self.serverLevelInUse:
                self.__registerEvents()
                #self.__connectServices()
                #self.__getTestServerClientMethods()
        finally:
            if not self._tabConn:
                if core.FW_conf['blackbox_enabled'] and self.phone.isMain():
                    # when connection failures reach the maximum, reboot the phone
                    if self.__connectionFailures >= self.__maxNumberOfConnectionFailures:
                        self.__connectionFailures = 0

                        # if not called from checkUiFreeze
                        if not self.phone.exit.uiFreezeDetectionOngoing:
                            # if video recorder available, check UI freeze
                            if core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.phone.isMain():
                                self.phone.exit._checkUiFreeze()
                            self.phone.resetPhone('Device connection failures reached the maximum: 10!', True) # True: wait for ram dump generation
                            return

                errorMessage = "Unable to create connection to device! " \
                               "Please check that device is connected and it's visible in device manager."
                self._debugErr(errorMessage)
                raise TABException(errorMessage)

        if self._tabConn:
            # check whether device is online
            if not self._tabConn.IsOnline:
                self._debugErr('Device status is offline! Phone side ADB has serious problems!')
                return

            # check root and remount status
            self.__ensureDeviceRootAndRemount()

            # raise ADB daemon process priority to ensure stable test execution
            try:
                if self._tabConn.IsRooted:
                    self._tabConn.RaiseAdbdPriority()
            except Exception, err:
                debug.out('Error in raising ADB daemon process priority: %s' % str(err))

            # use bigger timeout multiplier if emulator is in use
            if self._tabConn.IsEmulator:
                self._timeoutMultiplier = 3
            else:
                self._timeoutMultiplier = 1

            # reset scroll event variables
            self.averageScrollEventInterval = 0
            self.__scrollEventCount = 0
            self.__scrollEventSum = 0

            # start logging if necessary
            self._startLogging()

            # check SW type
            try:
                deviceInfo = self.deviceInfo(doNotReport = True)

                if deviceInfo.has_key('ro.build.type'):
                    self.swType = deviceInfo['ro.build.type']
            except Exception, err:
                debug.out('Error in checking SW type: %s' % str(err))

            if self.serverLevelInUse:
                # set access to media player and sqLite
                self._mediaPlayer = self._tabConn.MediaPlayer
                self._sqlLite = self._tabConn.SqLite

                # create dynamic proxy for file operations
                self._file = DynamicProxy.__create__(self._tabConn.File)
                self._file.__alias__( {'GetFolderContent' : 'getDirectoryContent'})
                self._file.__set_response_proxy__('getFolderContent', self.__convertTupleWithList)
                self._file.__set_response_proxy__('getDirectoryContent', self.__convertTupleWithList)
                self._file.__set_response_proxy__('getDate', self.__convertDate)
                self._file.__set_response_proxy__('getAttributes', self.__convertAttributesTuple)
                self._file.__set_response_proxy__('getFileSystemItems', self.__convertList)
                self._file.__set_response_proxy__('getUtcTime', self.__convertDate)
                self._file.__set_response_proxy__('readAllLines', self.__convertArray)
                self._file.__set_response_proxy__('readAllBytes', self.__convertArray)
                self._file.__set_response_proxy__('readAllLines', self.__convertArray)
                self._file.__set_argument_proxy__('touchFile', self.__convertTouchArgs)
                self._file.__set_argument_proxy__('touch', self.__convertTouchArgs)
                self._file.__set_argument_proxy__('touchDirectory', self.__convertTouchArgs)
                self._file.__set_argument_proxy__('readAllText', self.__convertReadArgs)
                self._file.__set_argument_proxy__('readAllLines', self.__convertReadArgs)

                # create dynamic proxy for package manager operations
                self._packageManager = DynamicProxy.__create__(self._tabConn.Packages)
                self._packageManager.__set_response_proxy__('installPackage', self.__convertTuple)
                self._packageManager.__set_response_proxy__('listPackages', self.__convertDictionary)

                # set access to activity manager
                self._activityManager = self._tabConn.ActivityManager

                # create dynamic proxy for time manager
                self._time = DynamicProxy.__create__(self._tabConn.Time)
                self._time.__set_argument_proxy__('setSystemDateTime', self.__convertDateArg)
                self._time.__set_response_proxy__('getTimeZoneOffset', self.__convertTimeSpan)
                self._time.__set_response_proxy__('getTimeDiffToLocalPc', self.__convertTimeSpan)
                self._time.__set_response_proxy__('getSystemDateTime', self.__convertDate)

                # run svc power stayon usb so that device won't turn off lights
                try:
                    self._tabConn.ShellCommand("svc power stayon usb")
                except Exception, err:
                    debug.out('Error when running svc stayon: %s' % str(err))

            debug.brf('Device connection ok')

    def _closeConnection(self, sleepAfterClose = True, disconnectServices = True):
        """Close existing TAB connection.

            Parameters

            sleepAfterClose         sleep for a while after connection close so that next create connection won't
                                    come too soon (default = True)
            disconnectServices      disconnect services (default = True)
        """
        if getattr(self, '_tabConn', None):
            debug.brf('Closing device connection...')

            # stop logging if necessary
            self._stopLogging()

            # stop possible event threads
            self._stopEventThreads()

            if disconnectServices:
                # disconnect from services
                self._disconnectServices(True)

            if self.serverLevelInUse:
                # disconnect from events
                self.__unRegisterEvents()

            if sleepAfterClose:
                # sleep for a while after close so that create connection won't come too soon
                time.sleep(5)

            debug.brf('Device connection closed')

        self._tabConn = None
        self._screenDimensionsQueried = False

    def getAvailableDevices(self, deviceType = TABInterface.DeviceType.ANY):
        """Get list of available device names

            Parameters

            deviceType          HW, EMULATOR, ANY
        """
        assert deviceType in [self.HW, self.EMULATOR, self.ANY], 'Wrong deviceType parameter given!'

        success, response = self._executeTabOperation(TABInterface.GetDevices, deviceType)

        if success:
            return response
        else:
            self._debugErr('Unable to get devices list!')

            if not self.__checkPhoneAdbStatus():
                self.phone.warn('ADB connection to device lost!')

                # restart ADB with force (kill existing ADB process(es))
                if not self.__restartADB():
                    self.phone.result.addFailure('ADB non-responsive, ADB get devices is not working!')

                success, response = self._executeTabOperation(TABInterface.GetDevices, deviceType)

                if success:
                    return response

            return []

    def getCrashDumps(self, destinationDir, retrieveAllFiles = False, deleteFiles = False):
        """Get crash dumps from the phone.

            Parameters

            destinationDir          directory where found crash dumps will be copied
            retrieveAllFiles        retrieve all crash dumps (default = False)
            deleteFiles             Whether crash dump files are deleted after copying or not (default = False)

            Returns True if new crash dumps were found, False if not
        """
        if self._tabConn:
            success, response = self._executeTabOperation(self._tabConn.GetCrashDumps, destinationDir, retrieveAllFiles, deleteFiles)

            if success:
                return response
            else:
                return False
        else:
            self._debugErr('No device connection available for getting crash dumps!')
            return False

    def _controlAction(self, actionNode):
        """ check wether the given action is for touch or for hw keys
            use ONLY from phone purgeKeyPresses

            actionNode  :   keyPress NodeUtils
        """
        if actionNode.getAttribute('key'):
            self.__hwKeyAction(actionNode)
        else:
            self.__touchAction(actionNode)

    def __getActionUiEventWaitParams(self, actionNode):
        """ extract parameters related to ui event waiting
        Parameters
            actionNode  NodeUtils containing touch or keypress information
        Return
            (waitUntilNoUIEvents, timeout, maximumDuration)
        """
        maximumDuration = self.__maximumDuration

        if self.overrideEventInterval != 0:
            timeout = self.overrideEventInterval
        else:
            timeout = self.__eventInterval

        waitUntilNoUIevents = self.waitUntilNoUIevents

        if actionNode.getAttribute('waitUntilNoUIevents') and actionNode.getAttribute('waitUntilNoUIevents') == 'False':
            waitUntilNoUIevents = False

        if actionNode.getAttribute('timeout'):
            timeout = int(actionNode.getAttribute('timeout'))

        if actionNode.getAttribute('maximumDuration'):
            maximumDuration = int(actionNode.getAttribute('maximumDuration'))

        return waitUntilNoUIevents, timeout, maximumDuration

    def __touchAction(self, touchNode):
        """Perform touch action having list of coordinates (e.g swipe)
           use ONLY via phone module purgeKeyPresses / _controlAction
            Parameters

            touchNode       NodeUtils instance containing touch press, move and release values

            Returns True if action succeeded, False if not
        """
        assert isinstance(touchNode, NodeUtils), 'Invalid touch node given!'

        # list of x, y, wait values
        valueList = []
        coordinates = []
        wait = 0
        length = 0
        touchActionSucceeded = False
        performDrag = False

        waitUntilNoUIevents, timeout, maximumDuration = self.__getActionUiEventWaitParams(touchNode)

        # get dragHold value for touch item
        if touchNode.getAttribute('dragHold'):
            performDrag = touchNode.getAttribute('dragHold') == 'True'

        if self._tabConn:
            # debug.brf('touchNode: %s' % touchNode.toprettyxml())

            if not touchNode.getAttribute('key'): # touch coordinates
                for node in touchNode.getChildNodes():
                    valueList.append(int(node.getAttribute('x')))
                    coordinates.append(int(node.getAttribute('x')))
                    valueList.append(int(node.getAttribute('y')))
                    coordinates.append(int(node.getAttribute('y')))
                    valueList.append(int(node.getAttribute('wait')))

                    wait = int(node.getAttribute('wait'))

                    # FIXME: change lower level to support different waits between coordinate points
                    # FIXME: figure out a better way to support drag and its speed
                    if performDrag:
                        length = 1500
                        wait = 50
                    else:
                        length = int(node.getAttribute('length'))

                try:
                    if waitUntilNoUIevents:
                        self._startUIEventThread(timeout, maximumDuration)

                    # try to touch for a few times before giving up
                    for i in range(10):
                        if core.FW_conf['should_stop']:
                            break

                        # if TestServerClient is available, perform touch actions with it
                        if self._isServerAvailable():
                            if self._isServerConnected():
                                #return self._tabConn.TestServerClient.swipeRegion(coordinates, wait / 5)

                                if len(coordinates) == 4:
                                    #debug.brf('touch tap: %s, %s' % (coordinates[0], coordinates[1]))

                                    # NOTE: This is temporary solution, because tap sometimes generates long press
                                    #touchDownSucceeded = self._tabConn.TestServerClient.touchDown(coordinates[0], coordinates[1])
                                    #touchUpSucceeded = self._tabConn.TestServerClient.touchUp(coordinates[0], coordinates[1])
                                    #touchActionSucceeded = touchDownSucceeded and touchUpSucceeded

                                    success, touchActionSucceeded = self._executeTabOperation(self._tabConn.TestServerClient.tap, coordinates[0], coordinates[1], length)
                                    time.sleep(wait/1000.0)
                                    #debug.brf('touchActionSucceeded: %s' % touchActionSucceeded)
                                    #debug.brf('touch tap took: %s' % str(time.time() - startTime))
                                else:
                                    if performDrag:
                                        success, touchActionSucceeded = self._executeTabOperation(self._tabConn.TestServerClient.drag, coordinates[0], coordinates[1], coordinates[-2], coordinates[-1], wait)
                                    else:
                                        success, touchActionSucceeded = self._executeTabOperation(self._tabConn.TestServerClient.swipe, coordinates[0], coordinates[1], coordinates[-2], coordinates[-1], wait)
                        else:
                            if len(coordinates) == 4:
                                touchActionSucceeded = self._tabConn.Touch(coordinates[0], coordinates[1])
                            else:
                                touchActionSucceeded = self._tabConn.TouchAction(List[int](valueList))

                        if touchActionSucceeded:
                            break
                        else:
                            if not core.FW_conf['should_stop']:
                                self.phone.warn('Unable to perform touch action!')
                                time.sleep(0.5)
                            else:
                                break
                except Exception, err:
                    self._debugErr('Exception during touch action: %s' % str(err))
                finally:
                    self._joinUIEventThread()
                    self._stopUIEventThread()
                    #debug.brf('touch action done')

        if not touchActionSucceeded:
            self.phone.fail("Unable to perform touch action! Device is not responding to touch commands!")

        return touchActionSucceeded

    def __hwKeyAction(self, keyNode):
        """Perform hw key action with given keyNode containing keycode (eg. KEYCODE_BACK)
           use ONLY via phone module purgeKeyPresses / _controlAction

            Parameters

            keyNode       NodeUtils instance containing touch press, move and release values

            Returns True if action succeeded, False if not
        """

        keyCode = keyNode.getAttribute('key')
        debug.out('keyNode: %s' % keyNode.toprettyxml())
        debug.out('tab_interface: _hwKeyAction %s' % keyCode)

        # get enclosed parameters
        waitUntilNoUIevents, timeout, maximumDuration = self.__getActionUiEventWaitParams(keyNode)

        if self._isServerAvailable():
            if self._isServerConnected():
                self.__getKeyCodes()

                if self.__keyCodes and keyCode in self.__keyCodes.Keys:
                    try:
                        if waitUntilNoUIevents:
                            self._startUIEventThread(timeout, maximumDuration)

                        if keyNode.getAttribute('length'):
                            length = int(keyNode.getAttribute('length'))
                        else:
                            length = 0

                        if length >= 1500:
                            self._executeTabOperation(self._tabConn.TestServerClient.sendLongKey, self.__keyCodes[keyCode], 0)
                        else:
                            self._executeTabOperation(self._tabConn.TestServerClient.sendKey, self.__keyCodes[keyCode], 0)
                    finally:
                        self._joinUIEventThread()
                        self._stopUIEventThread()
                else:
                    if self.__keyCodes:
                        self._debugErr('Given key code: "%s" is not correct. Available key codes: %s' % (keyCode, [x for x in self.__keyCodes.Keys]))
                    else:
                        self._debugErr('Unable to press key code: "%s". Available key codes could not be retrieved!' % keyCode)
            else:
                self._debugErr('Server not connected for _hwKeyAction')

    def capture(self, imagePath, onlyImage = False, useExistingDump=False):
        """Capture screen

            Parameters

            imagePath          image path where image will be saved
            onlyImage          whether only image and no dump is generated (default = False)

            Returns saved file path
        """
        if self._tabConn:
            imageFolder = os.path.dirname(imagePath)

            # make sure that directory exists
            if not os.path.isdir(imageFolder):
                os.makedirs(imageFolder)

            #startTime = time.time()
            success, response = self._executeTabOperation(self._tabConn.Capture, imagePath)
            #debug.brf('capture took: %s' % str(time.time() - startTime))

            if not success:
                self._debugErr('Unable to capture screen!')

            # save capture node to test result
            self.__saveCaptureNode(os.path.basename(imagePath), onlyImage, useExistingDump)

            return imagePath

    def input(self, text):
        """Pushes given text to focused text input field."""
        if self._tabConn:
            try:
                self._startUIEventThread()

                if self._isServerAvailable():
                    if self._isServerConnected():
                        success, response = self._executeTabOperation(self._tabConn.TestServerClient.pushText, text)
                    else:
                        success = False
                else:
                    success, response = self._executeTabOperation(self._tabConn.Input, text)

                if not success:
                    self._debugErr('Unable to perform input!')
            except Exception, err:
                self._debugErr('Exception during input action: %s' % str(err))
                self._stopUIEventThread()
            finally:
                self._joinUIEventThread()
                self._stopUIEventThread()
                #debug.brf('input action done')

    def _scroll(self, itemName, maximumScroll = None, fromLetterView = False, fast = False):
        """Scrolls to given item

            Parameters

            itemName                    item name in string
            maximumScroll               maximum scroll timeout
                                        (default = None --> 5 minutes)
            fromLetterView (bool):      When True, item is searched using letter view
                                        When False, item is searched using normal view (default)
            fast (bool)                 When True, use fast scrolling when searching
                                        When False, use normal speed scroll when searching (default)

            returns item coordinates if item was found, None if not
        """
        assert fromLetterView == False or fast == False, 'fromLetterView and fast parameters cannot be given simultaneously!'

        coords = None
        wait = 20
        previousItems = []
        scrolledDown = False
        scrolledUp = False
        scrollingDown = True
        afterScrollSwitch = False
        self.__screenScrolled = None
        scrollEventsMissingCount = 0
        uppercaseLetters = [x for x in string.ascii_uppercase]

        if maximumScroll == None:
            maximumScroll = 60000 * 5   # default maximum scroll timeout is 5 minutes
        else:
            assert type(maximumScroll) == types.IntType, 'Invalid maximumScroll parameter given!'

        itemName = unescape(itemName)

        scrollStart = time.time()

        while (time.time() < scrollStart + maximumScroll/1000):
            # just return if test execution is stopping
            if core.FW_conf['should_stop']:
                return

            visibleItems = {}
            visibleTexts = {}
            visibleItemCount = 0
            nodesFoundWithWildcards = []
            currentUppercaseLetters = []
            highestUppercaseLetter = None
            lowestUppercaseLetter = None
            lowestItem = None
            fastScrollingDown = None
            fastDifference = 0

            if scrollEventsMissingCount > 5 and not core.FW_conf['should_stop']:
                debug.out('Scroll events are not arriving from the device!')
                self._waitUntilNoUIEvents()

            # get visible nodes
            for visibleNode in self._getVisibleNodes().findall('//node'):
                if visibleNode.getAttribute('class') == "android.widget.Button":
                    # debug.brf('ignoring %s' % visibleNode.getAttribute('text'))
                    continue
                visibleItemCount += 1

                # add all possible attributes used for scroll
                for attr in ['text', 'index', 'content-desc', 'resource-id', 'related_text', 'related_content']:
                    if visibleNode.getAttribute(attr) != "":
                        centerX = int(visibleNode.getAttribute('center-x'))
                        centerY = int(visibleNode.getAttribute('center-y'))

                        visibleItems[visibleNode.getAttribute(attr)] = (centerX, centerY)

                        # add text to separate dict
                        if attr == 'text':
                            itemText = visibleNode.getAttribute(attr)
                            visibleTexts[itemText] = (centerX, centerY)

                            # get y coordinate of the lowest text item
                            if not lowestItem:
                                lowestItem = visibleNode
                            else:
                                if int(lowestItem.getAttribute('center-y')) < centerY:
                                    lowestItem = visibleNode
                                    # debug.brf('lowestItemY %s taken from text: %s' % (lowestItem.getAttribute('center-y'), visibleNode.getAttribute('text')))

                            # add uppercase item to current uppercase letters
                            if itemText in uppercaseLetters:
                                currentUppercaseLetters.append(itemText)

                                # store highest and lowest upper case letter nodes
                                if not highestUppercaseLetter or \
                                   int(highestUppercaseLetter.getAttribute('center-y')) > int(visibleNode.getAttribute('center-y')):
                                    highestUppercaseLetter = visibleNode
                                if not lowestUppercaseLetter or \
                                   int(lowestUppercaseLetter.getAttribute('center-y')) < int(visibleNode.getAttribute('center-y')):
                                    lowestUppercaseLetter = visibleNode

            #debug.brf('previousItems: %s' % previousItems)
            #debug.brf('visibleItems.keys(): %s' % visibleItems.keys())
            #debug.brf('visibleItems: %s' % visibleItems)
            #debug.brf('visibleTexts: %s' % visibleTexts)
            #debug.brf('visibleTexts.keys(): %s' % visibleTexts.keys())
            #debug.brf('self.__screenScrolled: %s' % self.__screenScrolled)
            #debug.brf('previousItems == visibleItems.keys(): %s' % (previousItems == visibleItems.keys()))

            # check that are we in "letter view" and we are not searching one of the letters
            if self._getCurrentPackageName() == 'com.nokia.homescreen' and \
               not itemName in uppercaseLetters and len(visibleTexts.keys()) > 0:
                uppercaseLettersFound = [x in uppercaseLetters for x in visibleTexts.keys()].count(True)
                #debug.brf('uppercaseLettersFound: %s' % uppercaseLettersFound)
                #debug.brf('text count: %s' % len(visibleTexts.keys()))

                percentage = float(100.0 * (float(uppercaseLettersFound) / float(len(visibleTexts.keys()))))
                #debug.brf('percentage: %s' % percentage)

                if percentage >= 88:
                    self.phone.warn('Letter view detected in application list!')
                    self.__exitFromLetterView(itemName, visibleTexts)
                    continue

            if self.__screenScrolled == True:
                scrollEventsMissingCount = 0
            elif self.__screenScrolled == False:
                scrollEventsMissingCount += 1

            # try searching with wildcards if not is not visible
            if not itemName in visibleItems.keys():
                nodesFoundWithWildcards = self.__wildcardSearch(itemName, visibleItems)

            if (not itemName in visibleItems.keys() and not nodesFoundWithWildcards) and \
               previousItems == visibleItems.keys():
               #(previousItems == visibleItems.keys() or self.__screenScrolled == False):
                if scrollingDown:
                    # we are in the end of list and item was not found --> switch scrolling
                    #debug.brf('Switch scrolling...')
                    scrollingDown = False
                    afterScrollSwitch = True
                else:
                    if fastScrollingDown != None:
                        # when fast scrolling is in use, quit when both directions have been scrolled
                        if scrolledDown and scrolledUp:
                            return None
                    else:
                        # we have seen all items, item can't be found
                        #debug.brf('All items seen, quit')
                        return None

                if not previousItems and not visibleItems.keys():
                    #debug.brf('No items seen, quit!')
                    return None

            if afterScrollSwitch:
                # after scroll switch it may be that items are the same
                afterScrollSwitch = False
                previousItems = []
            else:
                previousItems = visibleItems.keys()

            if itemName in visibleItems.keys():
                coords = visibleItems[itemName]
                break
            elif nodesFoundWithWildcards:
                #debug.brf('nodesFoundWithWildcards: %s' % nodesFoundWithWildcards)
                #debug.brf('node found with wild card')
                # FIXME: Now returning always the first node. Create support for using indexes coming from calling layer
                coords = nodesFoundWithWildcards[0]
                break
            else:
                #debug.brf('visibleItemCount: %s' % visibleItemCount)

                # if we only have one visible item, scroll is not possible
                if visibleItemCount <= 1:
                    break

                #debug.brf('currentUppercaseLetters: %s' % currentUppercaseLetters)
                itemUppercaseLetter = itemName[0].upper()

                # "letter view" search
                if fromLetterView:
                    fromLetterView = False

                    if len(currentUppercaseLetters) == 0:
                        self.phone.warn('No letters found for letter view navigation!')
                    else:
                        if not itemUppercaseLetter in currentUppercaseLetters:
                            self.phone.select(currentUppercaseLetters[0])

                        # select corresponding letter
                        self.phone.select(itemUppercaseLetter)

                        # continue so that visible items will be searched again
                        continue

                # when upper case letters visible, determine direction
                if len(currentUppercaseLetters) == 0 or highestUppercaseLetter == None or lowestUppercaseLetter == None:
                    debug.out('No letters found for fast scroll!')
                elif itemUppercaseLetter in uppercaseLetters:
                    letterPosition = uppercaseLetters.index(itemUppercaseLetter) + 1
                    upperPosition = uppercaseLetters.index(highestUppercaseLetter.getAttribute('text')) + 1
                    lowerPosition = uppercaseLetters.index(lowestUppercaseLetter.getAttribute('text')) + 1
                    #debug.brf('letterPosition: %s' % letterPosition)
                    #debug.brf('upperPosition: %s' % upperPosition)
                    #debug.brf('lowerPosition: %s' % lowerPosition)

                    if letterPosition >= lowerPosition:
                        #debug.brf('scroll down to reach item!')
                        fastDifference = letterPosition - lowerPosition
                        fastScrollingDown = True
                        scrolledDown = True
                    else:
                        #debug.brf('scroll up to reach item!')
                        if upperPosition > letterPosition:
                            fastDifference = upperPosition - letterPosition
                        else:
                            fastDifference = letterPosition - upperPosition

                        fastScrollingDown = False
                        scrolledUp = True

                    #debug.brf('fastDifference: %s' % fastDifference)

                xCoord = self.getScreenWidth() / 4 # grap always from the left side

                if not lowestItem or int(lowestItem.getAttribute('center-y')) == 0:
                    # if text items not found, grab from bottom of the screen
                    lowestItemY = self.getScreenHeight() - 200
                else:
                    lowestItemY = int(lowestItem.getAttribute('center-y'))
                    if lowestItemY > (self.getScreenHeight() / 2):
                        # minus 20 so that we won't accidentally grab options bar
                        lowestItemY -= 20

                #debug.brf('lowestItemY: %s' % lowestItemY)

                # lowest visible item coordinate point or bottom of the screen
                yDown = lowestItemY

                # FIXME: How to avoid hitting message boxes in the middle of the screen?
                yUp = (self.getScreenHeight() / 2)

                # check difference between up and down (if too small, swipe would turn into click)
                minimumDifference = 200

                if yUp >= yDown or (yDown - yUp) <= minimumDifference:
                    # move yUp upper to ensure minimum difference
                    if yUp >= 250:
                        yUp -= minimumDifference
                    else:
                        # just in case that screen height is really small
                        yUp = 100

                    # check minimum difference again
                    if yUp >= yDown:
                        yDown = yUp + minimumDifference
                    elif (yDown - yUp) <= minimumDifference:
                        if (yUp + minimumDifference) >= self.getScreenHeight():
                            # just in case that screen height is really small
                            yDown = self.getScreenHeight() - ((self.getScreenHeight() - yUp) / 2)
                        else:
                            yDown = yUp + minimumDifference

                #debug.brf('xCoord: %s' % xCoord)
                #debug.brf('yUp: %s' % yUp)
                #debug.brf('yDown: %s' % yDown)

                # when fast scrolling is in use, we know which direction to use
                if fastScrollingDown != None:
                    if fastScrollingDown:
                        # perform down swipe
                        touchCoords = [xCoord, yDown, xCoord, yUp]
                    else:
                        # perform up swipe
                        touchCoords = [xCoord, yUp, xCoord, yDown]
                else:
                    if scrollingDown:
                        #debug.brf('scrolling down')
                        # perform down swipe
                        touchCoords = [xCoord, yDown, xCoord, yUp]
                    else:
                        #debug.brf('scrolling up')
                        # perform up swipe
                        touchCoords = [xCoord, yUp, xCoord, yDown]

                touchActionSucceeded = False

                # fast scrolling
                if fast and fastScrollingDown != None:
                    try:
                        self._flickThreadRunning = True

                        # start listening to scroll if server available
                        if self._isServerAvailable() and self._isServerConnected():
                            self.__startScrollEventThread(eventInterval = 1800)

                        # start dump thread
                        dumpThread = Thread(ParameterizedThreadStart(self.___searchItemFromDumpInALoop))
                        dumpThread.IsBackground = True
                        dumpThread.Start(itemName)

                        if fastScrollingDown:
                            self._flickThread = Thread(ParameterizedThreadStart(self.__flickUp))
                        else:
                            self._flickThread = Thread(ParameterizedThreadStart(self.__flickDown))

                        self._flickThread.IsBackground = True
                        # determine flick speed
                        if fastDifference < 5:
                            flickSpeed = 40
                        elif 5 < fastDifference <= 10:
                            flickSpeed = 100
                        else:
                            flickSpeed = 290

                        #debug.brf('flickSpeed: %s' % flickSpeed)

                        flickParams = FlickParameters()
                        flickParams.xCoord = xCoord
                        flickParams.yDown = self.getScreenHeight() - 100
                        flickParams.yUp = 100
                        flickParams.speed = flickSpeed

                        # start flick thread
                        self._flickThread.Start(flickParams)

                        # join dump thread
                        dumpThread.Join()
                        
                        # join flick thread
                        self._flickThread.Join()                       
                    except Exception, err:
                        debug.err('Error in fast scrolling: %s' % str(err))
                    finally:
                        # abort threads if needed
                        if dumpThread.IsAlive:
                            dumpThread.Abort()
                        if self._flickThread.IsAlive:
                            self._flickThread.Abort()
                        
                        self._flickThread = None

                        # wait for scroll to end
                        self.__joinScrollEventThread()                        
                        self.__stopScrollEventThread()
                # normal scrolling
                else:
                    # try to scroll for a few times before giving up
                    for i in range(10):
                        if core.FW_conf['should_stop']:
                            break

                        try:
                            # start listening to scroll if server available
                            if self._isServerAvailable() and self._isServerConnected():
                                self.__startScrollEventThread()

                            if self.phone.isMain() and core.FW_conf['blackbox_enabled'] and not core.FW_conf['graybox_enabled']:
                                try:
                                    self.phone._touch.drawLine((touchCoords[0], touchCoords[1]), (touchCoords[2], touchCoords[3]), stepSize = 60, holdPenToStopScroll = False)
                                    self.phone._run('scroll')

                                    touchActionSucceeded = True
                                except Exception, err:
                                    self._debugErr('Error in performing scroll action in blackbox: %s' % str(err))
                            else:
                                try:
                                    if self._isServerAvailable():
                                        assert self._isServerConnected(), 'Server must be connected in order to perform scroll!'
                                        success, touchActionSucceeded = self._executeTabOperation(self._tabConn.TestServerClient.swipe, touchCoords[0], touchCoords[1], touchCoords[2], touchCoords[3], wait)
                                        #success, touchActionSucceeded = self._executeTabOperation(self._tabConn.TestServerClient.scrollSwipe, touchCoords[0], touchCoords[1], touchCoords[2], touchCoords[3], wait)
                                    else:
                                        success, touchActionSucceeded = self._executeTabOperation(self._tabConn.TouchAction, List[int](touchCoords))

                                        # wait for a while after scroll
                                        time.sleep(2)
                                except Exception, err:
                                    self._debugErr('Exception during touch scroll swipe: %s' % str(err))
                        finally:
                            self.__joinScrollEventThread()
                            self.__stopScrollEventThread()

                        if touchActionSucceeded:
                            #debug.brf('scroll done')
                            #debug.brf('*** self.__windowStateChanged: %s' % self.__windowStateChanged)
                            #debug.brf('*** self.__screenScrolled: %s' % self.__screenScrolled)
                            break
                        else:
                            if not core.FW_conf['should_stop']:
                                self.phone.warn('Error in scroll, unable to perform touch action!')
                                time.sleep(0.5)
                            else:
                                break

                    if not touchActionSucceeded:
                        self.phone.fail("Error in scroll, unable to perform touch action! Device is not responding to touch commands!")

        if not coords and time.time() >= scrollStart + maximumScroll/1000:
            debug.err('Maximum scroll timeout exceeced!')

        #self.phone.capture()
        #self.phone.comment('coords: %s' % str(coords))

        return coords

    def ___searchItemFromDumpInALoop(self, item):
        """Search item from XML dump in a loop

            Parameters

            item           item to be searched
        """
        startTime = time.time()

        previousTexts = []

        # NOTE: Maximum time is 10 seconds
        while (time.time() < startTime + 10):            
            try:
                visibleTexts = self._getVisibleTexts(returnAsDict = False)

                if item in visibleTexts:
                    #debug.brf('dump loop: item found')
                    self._flickThreadRunning = False
                    
                    for i in range(10):
                        if self._flickThread and self._flickThread.Alive:
                            time.sleep(0.2)
                        else:
                            break
                            #debug.brf('flick thread exited')

                    # tap screen to stop flick operation
                    success, response = self._executeTabOperation(self._tabConn.TestServerClient.tap, self.getScreenWidth() / 2, 2, 0)
                    #debug.brf('dump loop: tap, %s, %s' % (success, response))
                    break
            except:
                break

            if previousTexts == visibleTexts:
                #debug.brf('screen content not changing --> breaking from dump thread...')
                break

            previousTexts = visibleTexts
            
        #debug.brf('___searchItemFromDumpInALoop exit')

    def __flickUp(self, flickParams):
        """ Flick up in separate thread."""
        try:
            steps = self.phone._touch._calcRoute((flickParams.xCoord, flickParams.yDown), (flickParams.xCoord, flickParams.yUp), stepSize = flickParams.speed)
            #debug.brf('__flickUp: steps: %s' % steps)
            self.__flickForScroll(steps)
        except:
            pass

    def __flickDown(self, flickParams):
        """ Flick down in separate thread."""
        try:
            steps = self.phone._touch._calcRoute((flickParams.xCoord, flickParams.yUp), (flickParams.xCoord, flickParams.yDown), stepSize = flickParams.speed)
            #debug.brf('__flickDown: steps: %s' % steps)
            self.__flickForScroll(steps)
        except:
            pass

    def __flickForScroll(self, steps):
        """ Flick for scroll in separate thread. Uses __flickUp / __flickDown """
        for step in steps:
            if steps.index(step) == 0:
                self._executeTabOperation(self._tabConn.TestServerClient.touchDown, step[0], step[1])
                #debug.brf('__flickForScroll: touchDown')
            elif steps.index(step) == len(steps) - 1:
                self._executeTabOperation(self._tabConn.TestServerClient.touchUp, step[0], step[1])
                #debug.brf('__flickForScroll: touchUp')
            else:
                self._executeTabOperation(self._tabConn.TestServerClient.touchMove, step[0], step[1])
                #debug.brf('__flickForScroll: touchMove')

            if not self._flickThreadRunning:
                #debug.brf('breaking from flick thread...')
                self._executeTabOperation(self._tabConn.TestServerClient.touchUp, step[0], step[1])                
                #debug.brf('__flickForScroll: final touchUp')
                break
            
        #self._executeTabOperation(self._tabConn.TestServerClient.tap, self.getScreenWidth() / 2, self.getScreenHeight() / 2, 0)                    
        #debug.brf('__flickForScroll exit')

    def _disableLockScreen(self):
        """Disables lock screen by modifying database and rebooting device."""
        if self._tabConn:
            debug.brf('Disabling lock screen from the device...')

            # stop possible event threads
            self._stopUIEventThread()
            self.__stopScrollEventThread()

            # disconnect from services
            self._disconnectServices()

            # disable lock screen (also reboots device)
            try:
                if self._tabConn.DisableLockScreen():
                    debug.brf('Lock screen disabled')
                else:
                    debug.brf('Unable to disable lock screen!')
            except Exception, err:
                deviceInfo = self.deviceInfo(doNotReport = True)

                try:
                    if deviceInfo.has_key('ro.build.product') and deviceInfo['ro.build.product'] == 'msm8625':
                        self._debugErr('Lock screen disable does not support Normandy!')
                    else:
                        self._debugErr('Error when trying to disable lock screen: %s' % str(err))
                except:
                    self._debugErr('Error when trying to disable lock screen: %s' % str(err))

                #self.__connectServices()
            else:
                # close connection
                self._closeConnection(disconnectServices = False)

                # wait for device to get back online and re-create connection
                self._waitForDeviceOnline()

    def _navigateJump(self, item):
        """Navigate jump to given item by launching application directly.

            Parameters

            item            item string

            Returns True if jump succeeded, False if not
        """
        jumpSucceeded = False

        if self.serverLevelInUse:
            currentPackage = None
            wantedPackage = None
            wantedPackageName = None

            # get current package name
            currentPackage = self._getCurrentPackageName()

            # get wanted package name
            if '.' in item:
                wantedPackage = item
                wantedPackageName = item.split('/')[0]
            else:
                if getattr(self._tabConn, 'ScriptingServiceClient', None):
                    # get launchable applications
                    launchableApplications = self._getLaunchableApplications()

                    if launchableApplications and item in launchableApplications.Keys:
                        # FIXME: Change this if scripting service returns launchable applications in different format
                        splittedLaunchAppData = launchableApplications[item].split('.')
                        wantedPackage = '.'.join(splittedLaunchAppData[:-1]) + '/' + splittedLaunchAppData[-1]
                        wantedPackageName = '.'.join(splittedLaunchAppData[:-1])

            #debug.brf('currentPackage: %s' % currentPackage)
            #debug.brf('wantedPackage: %s' % wantedPackage)
            #debug.brf('wantedPackageName: %s' % wantedPackageName)

            # check if already in wanted package
            if currentPackage == wantedPackageName:
                jumpSucceeded = True
            else:
                # check item type and use proper launcher
                if getattr(self._tabConn, 'ActivityManager', None):
                    try:
                        self._tabConn.ActivityManager.StartActivity(wantedPackage)
                        jumpSucceeded = True
                    except Exception:
                        jumpSucceeded = False

                #else:
                #    if getattr(self._tabConn, 'ScriptingServiceClient', None):
                #        # get launchable applications
                #        launchableApplications = self._getLaunchableApplications()

                #        if launchableApplications and item in launchableApplications.Keys:
                #            # FIXME: There's no way to know if launch succeeded or not with scripting service
                #            jumpSucceeded = True
                #            self._tabConn.ScriptingServiceClient.launch(launchableApplications[item])

                # wait until no more UI events
                self._waitUntilNoUIEvents()

                # check that jump succeeded
                return jumpSucceeded

        return jumpSucceeded

    def __pressHWKey(self, keyCode, long = False,
                     waitUntilNoUIevents = True, timeout = 1000,
                     maximumDuration = 3000):
        """Presses HW key. Redirects to phone module which handles execution in BlackBox or
           redirection back to this module

            Parameters

            keyCode                 key code string
            long                    long press (default = False)
            waitUntilNoUIevents     wait until there are no UI events (default = True)
            timeout                 UI event wait timeout (in milliseconds)
            maximumDuration         maximum waiting duration for UI events (in milliseconds)
        """
        if long:
            hold = 1500
        else:
            hold = 20

        self.phone._pressKey(keyCode, hold, timeout=timeout, maximumDuration=maximumDuration)
        self.phone._run('tab_interface: Press HW Key %s, length %s' % (keyCode, hold))

    def reboot(self):
        """Reboot device. """
        if self._tabConn:
            self.phone.comment('reboot()')

            # stop possible event threads
            self._stopUIEventThread()
            self.__stopScrollEventThread()

            # disconnect from services
            self._disconnectServices()

            debug.brf('Rebooting device...')
            self._tabConn.Reboot()

            # close connection
            self._closeConnection(disconnectServices = False)

            # wait for device to get back online and re-create connection
            self._waitForDeviceOnline()

            if self.serverLevelInUse:
                self._connectServer()

    def addLogMarker(self, marker):
        """Add marker to log file

            Parameters

            marker      marker string to be added to log
        """
        assert self.__logging, 'Logging must be enabled in order to use addLogMarker!'

        self.phone.comment('addLogMarker(%s)' % str(marker))
        self._addLogMarker(marker)

    def deviceInfo(self, doNotReport = False, refresh = True):
        """Returns device information dictionary (including product name etc.).

            Parameters

            doNotReport     whether action is not to be reported (default = False)
            refresh         refresh dictionary (default = True)
        """
        if not doNotReport:
            self.phone.comment('deviceInfo()')

        deviceInfo = {}

        if self._tabConn:
            try:
                if refresh:
                    self._tabConn.RefreshProperties()

                deviceInfo = dict(self._tabConn.Properties)
            except Exception, err:
                self._debugErr('Error getting device information: %s' % str(err))

        return deviceInfo

    def environmentInfo(self):
        """Returns device environment information dictionary"""
        self.phone.comment('environmentInfo()')

        environmentInfo = {}

        if self._tabConn:
            try:
                self._tabConn.RefreshEnvironmentVariables()

                environmentInfo = dict(self._tabConn.EnvironmentVariables)
            except Exception, err:
                self._debugErr('Error getting environment information: %s' % str(err))

        return environmentInfo

    def _clear(self, number = 0, clearButtonCoords=None):
        """Clear characters in backspace style.

            Parameters

            number(int or string)       Number of times to press backspace or string 'all' to clear all
            clearButtonCoords           Coordinates to clear on VKB. If None, KEYCODE_DEL will be used
        """
        if number == 0:
            number = 'all'

        # empty parameter means all
        if number in ['all', None]:
            self.__waitSpecificEvent = 'TYPE_VIEW_TEXT_CHANGED'
            self.__getKeyCodes()

            if self.__keyCodes or clearButtonCoords:
                try:
                    self.__startSpecificEventThread(3000)
                    # start thread for pressing del
                    if clearButtonCoords:
                        #debug.brf('start touch coords thread. %s' % (clearButtonCoords,))
                        pressThread = Thread(ParameterizedThreadStart(self.___pressTouchCoordsInLoop))
                        pressThread.IsBackground = True
                        p = TouchParameters()
                        p.x = clearButtonCoords[0]
                        p.y = clearButtonCoords[1]
                        pressThread.Start(p)
                    else:
                        #debug.brf('start hw key thread. %r' % self.__keyCodes['KEYCODE_DEL'])
                        pressThread = Thread(ParameterizedThreadStart(self.___pressHWKeyInLoop))
                        pressThread.IsBackground = True
                        pressThread.Start(self.__keyCodes['KEYCODE_DEL'])
                finally:
                    # wait until no more events
                    self._joinSpecificUIEventThread()

                    # abort pressing thread
                    Monitor.Enter(self.__mObject)
                    if pressThread.IsAlive:
                        try:
                            pressThread.Abort()
                        finally:
                            Monitor.Exit(self.__mObject)

                    pressThread = None
                    self.__waitSpecificEvent = ''
        else:
            for i in range(number):
                if clearButtonCoords:
                    self._touchWithCoords(clearButtonCoords[0], clearButtonCoords[1])
                else:
                    self.__pressHWKey('KEYCODE_DEL', waitUntilNoUIevents = False)

    def waitForEvent(self, eventNames, timeout = 1000):
        """Wait for given event(s)

            Parameters

            eventNames          event name string or list of strings
                                (e.g. 'TYPE_VIEW_TEXT_CHANGED' or ['TYPE_VIEW_TEXT_CHANGED', 'TYPE_WINDOW_CONTENT_CHANGED'])
            timeout             timeout for event waiting (default = 1000 ms)

            Returns True if event(s) was/were received, False if not.
        """
        self.phone.comment('waitForEvent(%s)' % str(eventNames))

        if not type(eventNames) == types.ListType:
            eventNames = [eventNames]

        timeSpent = 0
        timeLeft = 0
        startTime = time.time()
        for eventName in eventNames:
            def predicate(event):
                if event.EventType == getattr(TABInterface.TABEvents, eventName, None):
                    return True
                else:
                    return False

            timeLeft = int(timeout - timeSpent)
            #debug.brf('timeLeft: %s' % timeLeft)

            # return false if we don't have time anymore
            if timeSpent >= timeout:
                return False

            if self._isServerAvailable():
                # return False right away when event is not received
                if not self._tabConn.TestServerClient.WaitForEvent(predicate, timeLeft):
                    return False
            else:
                return False

            # calculate time spent
            timeSpent = (time.time() - startTime) * 1000
            #debug.brf('timeSpent: %s' % timeSpent)

        return True

    def __setPageFlipCount(self, event):
        """Stores current page flip count from event."""
        if getattr(event, 'PageFlipCount', None):
            self.__pageFlipCount = event.PageFlipCount
            self.__pageFlipCountSuccess = True
            #debug.brf('self.__pageFlipCount: %s' % self.__pageFlipCount)
        else:
            self.__pageFlipCountSuccess = False

        if getattr(event, 'EventTime', None):
            self.__lastPageFlipEventTime = event.EventTime
            #debug.brf('self.__lastPageFlipEventTime: %s' % self.__lastPageFlipEventTime)

    def __pageFlipsIncoming(self):

        if not self.__pageFlipCount:
            #debug.err('no pageFlipCount from events')
            self.__pageFlipCountSuccess = False
            return False

        if not self.__lastPageFlipEventTime:
            #debug.err('no pageFlipcountTime available')
            self.__pageFlipCountSuccess = False
            return False

        ct = time.time()
        success, pageFlipCount = self._executeTabOperation(self._tabConn.TestServerClient.getPageFlipCount)

        ret = False
        if success and pageFlipCount != -1:
            if (pageFlipCount - self.__pageFlipCount)/(ct - self.__lastPageFlipEventTime) > self.__pageFlipsSpeedLimit:
                #debug.brf('pageFlipCount speeding (%s)' % str((pageFlipCount - self.__pageFlipCount)/(ct - self.__lastPageFlipEventTime)))
                ret = True
            else:
                #debug.brf('pageFlipCount stable (%s)' % str((pageFlipCount - self.__pageFlipCount)/(ct - self.__lastPageFlipEventTime)))
                pass

            self.__pageFlipCount = pageFlipCount
            self.__lastPageFlipEventTime = ct
            self.__pageFlipCountSuccess = True

        elif success and pageFlipCount == -1:
            #debug.err('no pageFlipCount available')
            self.__pageFlipCountSuccess = False
        elif not success:
            #debug.err('failed to get pageFlipCount')
            self.__pageFlipCountSuccess = False

        return ret
