"""Connection interface for opening/closing Marble <-> BlackBox service connection and
   handling exceptions.
"""
# Python library module imports
import clr, time, core
from core.testcase_exceptions import TestException, StopTestException, BlackBoxException, TestCaseWarning

clr.AddReference('TestAutomation.Gui.Marble.IPC.ClientServiceCommon')
from TestAutomation.Gui.Marble.IPC.Clients import MarbleFwBlackBoxClient
from TestAutomation.Gui.Marble.IPC.Clients import MarbleFwVideoRecorderClient
from System.Collections.Generic import List
from TestAutomation.Gui.Marble.IPC.Interfaces import SimCard
from TestAutomation.Gui.Marble.IPC.Interfaces import MemoryCard
from TestAutomation.Gui.Marble.IPC.Interfaces import UsbPort
from TestAutomation.Gui.Marble.IPC.Interfaces import AvPlug
from TestAutomation.Gui.Marble.IPC.Interfaces import MarbleTouchData
from TestAutomation.Gui.Marble.IPC.Interfaces import TouchState
from TestAutomation.Gui.Marble.IPC.Interfaces import TouchStateResponse
clr.AddReference('TestAutomation.HWController.Client')
from TestAutomation.HWController.Client import HWControllerClient
from core import debug

class MarbleBlackBoxInterface:
    """Marble black box interface class."""
    def __init__(self):
        """Initialize variables."""

        self.client = None
        self.videoClient = None
        self.grayboxClient = None
        self.powerOnPhoneSequence = None
        #the amount of retries if TCP/USB communication between HWController and Marble fails
        self.connectionRetries = 3
        self.delayBetweenRetries = 5
        self.currentUsb = ''

        if core.FW_conf['graybox_enabled'] and (core.FW_conf['settings'].System.HWConnectionType == 'USB' or \
            (core.FW_conf['settings'].System.HWConnectionType == 'TCP' and core.FW_conf['settings'].System.HWAssistedWhiteBoxServerAddress is not '')):
            self.powerOnPhoneSequence = core.FW_conf['settings'].System.PowerOnPhoneSequence.split(',')
            for i in range(self.connectionRetries):
                try:
                    self.grayboxClient = HWControllerClient.Instance
                    self.grayboxClient.Logger = debug.log
                    self.grayboxClient.TestUnitNumber = core.FW_conf['settings'].System.TestUnitNumber
                    if core.FW_conf['settings'].System.HWConnectionType == 'USB':
                        self.grayboxClient.InitUsbMode()
                        self.grayboxClient.PingUsb()
                    else:
                        self.grayboxClient.InitTcpMode(core.FW_conf['settings'].System.HWAssistedWhiteBoxServerAddress)
                    self.grayboxClient.Initialize()
                    self.currentUsb = 'Usb1'
                    break
                except Exception, ex:
                    if i == self.connectionRetries -1:
                        self.grayboxClient = None
                        raise StopTestException('HW Assisted WhiteBox: Create TCP connection to HWController server failed after %d retries: %s' % (self.connectionRetries, ex))
                    else:
                        debug.err('HW Assisted WhiteBox: TCP connection to HWController server failed. Retrying in %d second.' % self.delayBetweenRetries)
                        time.sleep(self.delayBetweenRetries)
            if core.FW_conf['settings'].TestRun.EnableVideoRecorder:
                self.initVideoRecorderClient()
        else:
            if core.FW_conf['blackbox_enabled']:
                self.initBlackBoxClient()

            if core.FW_conf['settings'].TestRun.EnableVideoRecorder or \
                core.FW_conf['settings'].TestRun.ExecutionMode == 'Follower' or \
                core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
                self.initVideoRecorderClient()

    def initBlackBoxClient(self):
        try:
            self.client = MarbleFwBlackBoxClient()
        except Exception, ex:
            debug.exception(ex)
            raise StopTestException('Unable to create the BlackBox WCF client object: %s' % ex)

    def initVideoRecorderClient(self):
        try:
            self.videoClient = MarbleFwVideoRecorderClient(args = core.FW_conf['settings'].System.TestUnitNumber.ToString())
        except Exception, ex:
            debug.exception(ex)
            raise BlackBoxException('Unable to create the VideoRecorder WCF client object: %s' % ex)

    def connectPower(self):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None:
            self.__checkUsbSerialConnection()
            for i in range(self.connectionRetries):
                try:
                    self.grayboxClient.ConnectPower()
                    break
                except Exception, ex:
                    if i == self.connectionRetries -1:
                        raise TestCaseWarning('HW Assisted WhiteBox: connectPower failed after %d retries: %s' % (self.connectionRetries, ex))
                    else:
                        debug.brf('HW Assisted WhiteBox: connectPower failed. Retrying in %d second.' % self.delayBetweenRetries)
                        time.sleep(self.delayBetweenRetries)
        else:
            if core.FW_conf['blackbox_enabled']:
                try:
                    self.client.ConnectPower()
                except Exception, ex:
                    debug.exception(ex)
                    raise BlackBoxException('Unable to execute connectPower command on the BlackBox device: %s' % ex)
            else:
                raise TestCaseWarning('Unable to execute connectPower command in WhiteBox mode')

    def disconnectPower(self):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None:
            self.__checkUsbSerialConnection()
            for i in range(self.connectionRetries):
                try:
                    self.grayboxClient.DisconnectPower()
                    break
                except Exception, ex:
                    if i == self.connectionRetries -1:
                        raise TestCaseWarning('HW Assisted WhiteBox: disconnectPower failed after %d retries: %s' % (self.connectionRetries, ex))
                    else:
                        debug.brf('HW Assisted WhiteBox: disconnectPower failed. Retrying in %d second.' % self.delayBetweenRetries)
                        time.sleep(self.delayBetweenRetries)
        else:
            if core.FW_conf['blackbox_enabled']:
                try:
                    self.client.DisconnectPower()
                except Exception, ex:
                    debug.exception(ex)
                    raise BlackBoxException('Unable to execute disconnectPower command on the BlackBox device: %s' % ex)
            else:
                raise TestCaseWarning('Unable to execute disconnectPower command in WhiteBox mode')

    # Values: 'None', 'Sim1', 'Sim2', 'Sim3', 'Sim4', 'Sim5', 'Sim6'
    def connectSim(self, sim):
        if core.FW_conf['blackbox_enabled']:
            try:
                simCard = SimCard.Parse(SimCard, sim)
                self.client.ConnectSim(simCard)
            except Exception, ex:
                debug.exception(ex)
                raise BlackBoxException('Unable to execute connectSim command on the BlackBox device: %s' % ex)
        else:
            raise TestCaseWarning('Unable to execute connectSim(' + sim + ') command in WhiteBox mode')

    #Values: 'None', 'CardA', 'CardB', 'CardC', 'CardD'
    def connectMemoryCard(self, card):
        if core.FW_conf['blackbox_enabled']:
            try:
                memoryCard = MemoryCard.Parse(MemoryCard, card)
                self.client.ConnectMemoryCard(memoryCard)
            except Exception, ex:
                debug.exception(ex)
                raise BlackBoxException('Unable to execute connectMemoryCard command on the BlackBox device: %s' % ex)
        else:
            raise TestCaseWarning('Unable to execute connectMemoryCard(' + card + ') command in WhiteBox mode')


    # Connects USB accessory card default connector to phone
    def connectDefaultAccessoryUsb(self):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None:
            self.__checkUsbSerialConnection()
            for i in range(self.connectionRetries):
                try:
                    self.grayboxClient.ConnectUSBMain()
                    self.currentUsb = 'Usb1'
                    break
                except Exception, ex:
                    if i == self.connectionRetries -1:
                        raise TestCaseWarning('HW Assisted WhiteBox: connectDefaultAccessoryUsb failed after %d retries: %s' % (self.connectionRetries, ex))
                    else:
                        debug.brf('HW Assisted WhiteBox: connectDefaultAccessoryUsb failed. Retrying in %d second.' % self.delayBetweenRetries)
                        time.sleep(self.delayBetweenRetries)
        else:
            if core.FW_conf['blackbox_enabled']:
                try:
                    return self.client.ConnectDefaultUsbAccessoryConnector()
                except Exception, ex:
                    debug.exception(ex)
                    raise BlackBoxException('Unable to execute connectDefaultAccessoryUsb command on the BlackBox device: %s' % ex)
            else:
                raise TestCaseWarning('Unable to execute connectDefaultAccessoryUsb command in WhiteBox mode')

    # Values: 'None', 'Usb1', 'Usb2', 'Usb3', 'Usb4'
    def connectUsb(self, port):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None:
            self.__checkUsbSerialConnection()
            for i in range(self.connectionRetries):
                try:
                    if port == 'None':
                        self.grayboxClient.DisconnectUSBMain()
                    else:
                        self.grayboxClient.ConnectUSBMain()
                    self.currentUsb = port
                    break
                except Exception, ex:
                    if i == self.connectionRetries -1:
                        raise TestCaseWarning('HW Assisted WhiteBox: connectUsb %s failed after %d retries: %s' % (port, self.connectionRetries, ex))
                    else:
                        debug.brf('HW Assisted WhiteBox: connectUsb %s failed. Retrying in %d second.' % (port, self.delayBetweenRetries))
                        time.sleep(self.delayBetweenRetries)
        else:
            if core.FW_conf['blackbox_enabled']:
                try:
                    usbPort = UsbPort.Parse(UsbPort, port)
                    self.client.ConnectUsb(usbPort)
                except Exception, ex:
                    debug.exception(ex)
                    raise BlackBoxException('Unable to execute connectUsb command on the BlackBox device: %s' % ex)
            else:
                raise TestCaseWarning('Unable to execute connectUsb(' + port + ') command in WhiteBox mode')

    # Values: 'None', 'Av1', 'Av2', 'Av3', 'Av4'
    def connectAvPlug(self, port):
        if core.FW_conf['blackbox_enabled']:
            try:
                avPort = AvPlug.Parse(AvPlug, port)
                self.client.ConnectAvPlug(avPort)
            except Exception, ex:
                debug.exception(ex)
                raise BlackBoxException('Unable to execute connectAvPlug command on the BlackBox device: %s' % ex)
        else:
            raise TestCaseWarning('Unable to execute connectAvPlug(' + port + ') command in WhiteBox mode')
    
    # Value: An array of keypresses and touchpresses
    def pressEvent(self, pressData):
        if core.FW_conf['blackbox_enabled'] or (core.FW_conf['graybox_enabled'] and self.grayboxClient is not None):
            self.__checkUsbSerialConnection()
            touchState = TouchStateResponse()
            keyPresses = []
            touchPresses = []
            for press in pressData:
                if press.getName() == 'keypress':
                    # Execute touchresses
                    if len(touchPresses) > 0:
                        s = self.__touchEvent(touchPresses)
                        if s.State != TouchState.Normal:
                            touchState = s
                        touchPresses = []
                    # Collect keypresses
                    keyPresses.append(press)
                elif press.getName() == 'touch':
                    # Execute keypresses
                    if len(keyPresses) > 0:
                        s = self.__keyEvent(keyPresses)
                        if s.State != TouchState.Normal:
                            touchState = s
                        keyPresses = []
                    # Collect touchpresses
                    touchPresses.append(press)

            # Execute rest of the presses if not yet executed within the loop above
            if len(keyPresses) > 0:
                s = self.__keyEvent(keyPresses)
                if s.State != TouchState.Normal:
                    touchState = s
            elif len(touchPresses) > 0:
                s = self.__touchEvent(touchPresses)
                if s.State != TouchState.Normal:
                    touchState = s

            # if phone powered down, or touch coordinates has not been read properly, return this information
            # values for State enum: Normal, PowerOffOrSleepMode, Warning
            return (touchState.State.ToString(), touchState.StateInfo)
        else:
            raise TestCaseWarning('Unable to execute pressEvent command in WhiteBox mode')

    # Values: operation: string (e.g. Connect_Headset, Disconnect_Headset)
    def executeHwOperation(self, operation):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None:
            self.__checkUsbSerialConnection()
            for i in range(self.connectionRetries):
                try:
                    if operation == 'Connect_Headset':
                        self.grayboxClient.ConnectHeadset()
                    elif operation == 'Disconnect_Headset':
                        self.grayboxClient.DisconnectHeadset()
                    elif operation == 'Connect_SIM':
                        self.grayboxClient.InsertSIM2()
                    elif operation == 'Disconnect_SIM':
                        self.grayboxClient.RemoveSIM2()
                    elif operation == 'Connect_MMC':
                        self.grayboxClient.InsertMemoryCard()
                    elif operation == 'Disconnect_MMC':
                        self.grayboxClient.RemoveMemoryCard()
                    elif operation.startswith('KEYCODE_POWER'):
                        pressLength = operation.split(':')[1]
                        self.grayboxClient.PressKeylockPowerButton(int.Parse(pressLength))
                    break
                except Exception, ex:
                    if i == self.connectionRetries -1:
                        raise TestCaseWarning('HW Assisted WhiteBox: executeHwOperation %s failed after %d retries: %s' % (operation, self.connectionRetries, ex))
                    else:
                        debug.brf('HW Assisted WhiteBox: executeHwOperation %s failed. Retrying in %d second.' % (operation, self.delayBetweenRetries))
                        time.sleep(self.delayBetweenRetries)
        else:
            if core.FW_conf['blackbox_enabled']:
                try:
                    self.client.ExecuteHwOperation(operation)
                except Exception, ex:
                    debug.exception(ex)
                    raise BlackBoxException('Unable to execute executeHwOperation command on the BlackBox device: %s' % ex)
            else:
                raise TestCaseWarning('Unable to execute executeHwOperation(' + operation + ') command in WhiteBox mode')

    def powerOnPhone(self):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None and self.powerOnPhoneSequence is not None:
            self.__checkUsbSerialConnection()
            #'DisconnectUSBMain,DisconnectPower,Sleep:2000,ConnectPower,Sleep:2000,PressKeylockPowerButton:3000,Sleep:2000,ConnectUSBMain'
            for i in range(self.connectionRetries):
                try:
                    for operation in self.powerOnPhoneSequence:
                        if operation == 'DisconnectUSBMain':
                            self.grayboxClient.DisconnectUSBMain()
                        elif operation == 'ConnectUSBMain':
                            self.grayboxClient.ConnectUSBMain()
                        elif operation == 'DisconnectPower':
                            self.grayboxClient.DisconnectPower()
                        elif operation == 'ConnectPower':
                            self.grayboxClient.ConnectPower()
                        else:
                            op, length = operation.split(':')
                            if op == 'Sleep':
                                time.sleep(int(length) / 1000)
                            elif op == 'PressKeylockPowerButton':
                                self.grayboxClient.PressKeylockPowerButton(int.Parse(length))
                    break
                except Exception, ex:
                    if i == self.connectionRetries -1:
                        raise TestCaseWarning('HW Assisted WhiteBox: powerOnPhone failed after %d retries: %s' % (self.connectionRetries, ex))
                    else:
                        debug.brf('HW Assisted WhiteBox: powerOnPhone failed. Retrying in %d second.' % self.delayBetweenRetries)
                        time.sleep(self.delayBetweenRetries)
        else:
            if core.FW_conf['blackbox_enabled']:
                self.client.PowerOnPhone()
            else:
                raise TestCaseWarning('Unable to execute powerOnPhone command in WhiteBox mode')

    def resetPhonePower(self):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None and self.powerOnPhoneSequence is not None:
            self.powerOnPhone()
        else:
            if core.FW_conf['blackbox_enabled']:
                self.client.ResetPhonePower()
            else:
                raise TestCaseWarning('Unable to execute resetPhonePower command in WhiteBox mode')

    # Helper method for setting up the BlackBox testing with single method only.
    def setupBlackBoxTesting(self, phoneModel = None):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None:
            self.client.Initialize()
        else:
            if phoneModel is not None and phoneModel is not self.client.CurrentConfiguredPhoneModel:
                try:
                    self.client.ConfigureBlackBox(phoneModel)
                except Exception, ex:
                    debug.exception(ex)
                    raise StopTestException('FATAL ERROR! Unable to setup BlackBox testing mode: %s' % ex)
            if not self.client.IsRequiredIoWCardsFound:
                try:
                    self.client.InitIoWarrior(core.FW_conf['graybox_enabled']) # Pass enablegraybox value to BlackBoxService
                except Exception, ex:
                    debug.exception(ex)
                    raise StopTestException('FATAL ERROR! Unable to setup BlackBox testing mode: %s' % ex)
                try:
                    self.client.CheckIoWarriorCards()
                except Exception, ex:
                    debug.exception(ex)
                    raise StopTestException('FATAL ERROR! Unable to setup BlackBox testing mode: %s' % ex)

            # TEMPORARY: If running in graybox mode without touch emulation card, do not try to initialize the card here.
            if not core.FW_conf['graybox_enabled'] and not self.client.IsTouchReady:
                try:
                    self.client.InitTouch()
                except Exception, ex:
                    debug.exception(ex)
                    raise StopTestException('FATAL ERROR! Unable to setup BlackBox testing mode: %s' % ex)
            
            try:
                # Re-tries on error = 1
                self.client.ConnectPower(1)
            except Exception, ex:
                debug.exception(ex)
                raise StopTestException('FATAL ERROR! Unable to setup BlackBox testing mode: %s' % ex)
            try:
                # Re-tries on error = 1
                self.client.ConnectDefaultUsbAccessoryConnector(1)
            except Exception, ex:
                debug.exception(ex)
                raise StopTestException('FATAL ERROR! Unable to setup BlackBox testing mode: %s' % ex)

    # 'Portrait' or 'Landscape'
    def setOrientation(self, orientation):
        return

    def recordVideo(self, path):
        if self.videoClient:
            self.videoClient.RecordVideo(path)
    
    def takePicture(self, path):
        if self.videoClient:
            self.videoClient.TakePicture(path)

    def stopRecording(self):
        if self.videoClient:
            self.videoClient.StopRecording()

    def videoRecording_SetText(self, text):
        if self.videoClient:
            self.videoClient.SetOverlayTextToVideo(text)

    def isVideoRecorderAvailable(self):
        # return False right away if setting is not enabled
        if not core.FW_conf['settings'].TestRun.EnableVideoRecorder:
            return False

        if self.videoClient:
            return self.videoClient.IsVideoRecorderAvailable
        else:
            return False   # gets the current amount of frames that has contained some motion.
    # the frame counter is automatically reset when new video recording is started
    # this method returns the value of frames containing motion as integer (int)
    def getCountMotionFrames(self):
        if self.videoClient:
            return self.videoClient.GetCountMotionFrames()

    def isTouchEmulationEnabled(self):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None:
            return False
        else:
            return self.client.IsTouchEmulationEnabled

    def isAccelerometerEmulationEnabled(self):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None:
            return False
        else:
            return self.client.IsAccelerometerEmulationEnabled

    def getDefaultUsbAccessoryConnector(self):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None:
            return 'Usb1'
        else:
            return self.client.DefaultUsbAccessoryConnector

    def getCurrentUsbAccessoryConnector(self):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None:
            return self.currentUsb
        else:
            return self.client.CurrentUsbAccessoryConnector

    def Dispose(self):
        if self.client:
            self.client.Dispose()
        if self.videoClient:
            self.videoClient.Dispose()
        if self.grayboxClient:
            try:
                self.grayboxClient.Close()
            finally: #No actions required if closing TCP socket fails
                return

    def isHwAssistedWhiteBox(self):
        """ Returns true if Netduino based HW Assisted WhiteBox HW is in use """
        if self.grayboxClient is not None:
            return True
        else:
            return False

    def __keyEvent(self, keyData):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None:
            for i in range(self.connectionRetries):
                try:
                    for press in keyData:
                        key = press['key']
                        length = press['length']
                        if length == '':
                            length = '100'
                        wait = press['wait']
                        if wait == '':
                            wait = '100'
                        if key == 'KEYCODE_POWER':
                            self.grayboxClient.PressKeylockPowerButton(int.Parse(length))
                            time.sleep(int(wait) / 1000)
                            return TouchStateResponse()
                        else:
                            raise TestCaseWarning('HW Assisted WhiteBox: cannot execute % with HWController' % key)
                except TestCaseWarning, warn:
                    raise
                except Exception, ex:
                    if i == self.connectionRetries -1:
                        raise TestCaseWarning('HW Assisted WhiteBox: select %s failed after %d retries: %s' % (key, self.connectionRetries, ex))
                    else:
                        debug.brf('HW Assisted WhiteBox: select %s failed. Retrying in %d second.' % (key, self.delayBetweenRetries))
                        time.sleep(self.delayBetweenRetries)
        else:
            if core.FW_conf['blackbox_enabled']:
                try:
                    for press in keyData:
                        key = press['key']
                        length = press['length']
                        if length == '':
                            length = '100'
                        wait = press['wait']
                        if wait == '':
                            wait = '100'
                        # TODO: FIXME --> move keypress_wait and keypress_length to core configuration
                        return self.client.PressKey(key, int(length))
                        time.sleep(int(wait) / 1000)
                except Exception, ex:
                    debug.exception(ex)
                    raise BlackBoxException('Unable to execute keyPress command on the BlackBox device: %s' % ex)
            else:
                raise TestCaseWarning('Unable to execute keyEvent command in WhiteBox mode')
    
    def __touchEvent(self, touchData):
        if core.FW_conf['blackbox_enabled']:
            try:
                l = List[MarbleTouchData]()
                for x in touchData:
                    for y in x.getItems():
                        if y.getName() == 'press':
                            l.Add(MarbleTouchData('press', y['x'], y['y'], y['touch_id'], y['length']))
                        elif y.getName() == 'move':
                            l.Add(MarbleTouchData('move', y['x'], y['y'], y['touch_id'], y['wait']))
                        elif y.getName() == 'release':
                            l.Add(MarbleTouchData('release', y['x'], y['y'], y['touch_id'], y['wait']))
                return self.client.TouchEvent(l)
            except Exception, ex:
                debug.exception(ex)
                raise BlackBoxException('Unable to execute touchEvent command on the BlackBox device: %s' % ex)
        else:
            raise TestCaseWarning('Unable to execute touchEvent command in WhiteBox mode')

    def __checkUsbSerialConnection(self):
        if core.FW_conf['graybox_enabled'] and self.grayboxClient is not None and core.FW_conf['settings'].System.HWConnectionType == 'USB':
            devices = self.grayboxClient.DetectDevices()
            if devices.Count == 0:
                raise TestCaseWarning('HW Assisted WhiteBox: Connection Type USB selected but no HWController devices detected')
