
import clr;
from System import Array, Environment, Object, String
from System.ComponentModel import TypeConverter, StringConverter, Int32Converter

class PhoneReset(object) :
    DisplayName = 'phone reset'
    Category = 'Timeouts'
    Description = "Phone's reset timeout in seconds. Default = 30."
    DefaultValue = 30

class SendAndReceiveMessage(object) :
    DisplayName = 'send and receive message'
    Category = 'Timeouts'
    Description = "Send and receive message timeout in milliseconds. Default = 5000."
    DefaultValue = 5000

class ReceiveMessagesFrom(object) :
    DisplayName = 'receive messages from'
    Category = 'Timeouts'
    Description = "Receive messages from timeout in milliseconds. Default = 5000."
    DefaultValue = 5000

class ExpectTimeout(object) :
    DisplayName = 'expect timeout'
    Category = 'Timeouts'
    Description = "Expect timeout in milliseconds. Default = 8000"
    DefaultValue = 8000

class ExpectLength(object) :
    DisplayName = 'expect length'
    Category = 'Timeouts'
    Description = "Expect length in milliseconds. Default = 0"
    DefaultValue = 0

class ExpectWait(object) :
    DisplayName = 'expect wait'
    Category = 'Timeouts'
    Description = "Expect wait in milliseconds. Default = 0"
    DefaultValue = 0

class InputIntervalStringConverter(StringConverter) :

    def GetStandardValues(self, context) :
        return TypeConverter.StandardValuesCollection(Array[String](['normal', 'slow']))

    def GetStandardValuesSupported(self, context) :
        return True

    def GetStandardValuesExclusive(self, context) :
        return True

class InputInterval(object) :
    DisplayName = 'input interval'
    Category = 'Timeouts'
    Description = "Time between keypresses milliseconds. Use slow if phone SW has issues registering keypresses with normal setting. Default = normal"
    DefaultValue = "normal"
    Converter = InputIntervalStringConverter()

class ResendMessageInUse(object) :
    DisplayName = 'resend message in use'
    Category = 'Message resending'
    Description = "Message resend feature enabled. Default = True"
    DefaultValue = True

class ResendCount(object) :
    DisplayName = 'resend count'
    Category = 'Message resending'
    Description = "Number of times a message is resent. Default = 3"
    DefaultValue = 3

class TimeoutBetweenTries(object) :
    DisplayName = 'timeout between tries'
    Category = 'Message resending'
    Description = "Timeout in seconds between tries. Default = 5"
    DefaultValue = 5

class GuiFrameworkProtocolPort(object) :
    DisplayName = 'gui - fw protocol port'
    Category = 'Port config'
    Description = "Protocol port for GUI - FW communication.\nThe value will be automatically set."
    DefaultValue = 31336
    ReadOnlyForUser = True

class FrameworkGuiLoggerPort(object) :
    DisplayName = 'fw - gui udp logger port'
    Category = 'Port config'
    Description = "Protocol port for FW - GUI UDP logger.\nThe value will be automatically set."
    DefaultValue = 31337
    ReadOnlyForUser = True

class FrameworkGuiBltUeServicePort(object) :
    DisplayName = 'fw - gui blt-ue service port'
    Category = 'Port config'
    Description = "Protocol port for FW - GUI BLT-UE service.\nThe value will be automatically set."
    DefaultValue = 31338
    ReadOnlyForUser = True

class PathForTempFiles(object) :
    DisplayName = 'path for temp files'
    Description = "Path where temporary files are stored. Default = '' (Files are stored under isa_test)"
    DefaultValue = ''

class RecentTestSet(object) :
    DisplayName = 'recent test set'
    Description = 'The current/recent test set used'
    DefaultValue = ''
    ReadOnlyForUser = True

class DisplayUpdateNtfsInUse(object) :
    DisplayName = 'display update ntf messages in use'
    Category = 'Display Update'
    Description = "Use display update ntf messages to determine whether UI has changed or not. Default = False"
    DefaultValue = False
    ReadOnlyForUser = True

class BlackBoxVKBDelayBetweenPresses(object) :
    DisplayName = 'blackbox mode input.write delay between presses'
    Category = 'Timeouts'
    Description = "How many milliseconds will be waited between each key press (BlackBox mode)"
    DefaultValue = 100
    
class AutomaticRootAndRemount(object):
    DisplayName = 'automatic root and remount'
    Description = "Whether root and remount commands will be automatically executed on device after connection creation. Default = True"
    DefaultValue = True

class MaximumExitFailures(object):
    DisplayName = 'maximum number of exit failures'
    Description = "Maximum number of exit failures (unable to reach main menu) until phone is rebooted in order to recover from the situation. Default = 10"
    DefaultValue = 10

class ServerTracesEnabled(object):
    DisplayName = 'server traces enabled'
    Category = 'traces'
    Description = "Whether to show server traces in console log. Default = True"
    DefaultValue = True

class UIEventTracesEnabled(object):
    DisplayName = 'UI event traces enabled'
    Category = 'traces'
    Description = "Whether to show UI event traces in console log. Default = True"
    DefaultValue = True

class HWAssistedWhiteBoxEnabled(object):
    DisplayName = 'HW Assisted WhiteBox Enabled'
    Category = 'HW Assisted WhiteBox (Netduino HW)'
    Description = "True if HW available to assist WhiteBox execution."
    DefaultValue = False

class HWAssistedPowerKey(object):
    DisplayName = 'power key pressed with HW'
    Category = 'HW Assisted WhiteBox (Netduino HW)'
    Description = "True: Power key pressing is done via HW.\nFalse: Power key pressing is done via SW"
    DefaultValue = True

class HWAssistedWhiteBoxServerAddress(object):
    DisplayName = 'HWController server IP'
    Category = 'HW Assisted WhiteBox (Netduino HW)'
    Description = "The IP address of HW Assisted WhiteBox control server"
    DefaultValue = ""

class HWConnectionTypeStringConverter(StringConverter) :

    def GetStandardValues(self, context) :
        return TypeConverter.StandardValuesCollection(Array[String](['USB', 'TCP']))

    def GetStandardValuesSupported(self, context) :
        return True

class HWConnectionType(object) :
    DisplayName = 'HW Assisted WhiteBox Connection Type'
    Category = 'HW Assisted WhiteBox (Netduino HW)'
    Description = 'Connection type to HW Controller. USB or TCP' 
    DefaultValue = 'USB'
    Converter = HWConnectionTypeStringConverter()

class TestUnitNumberToInt32Converter(Int32Converter) :

    def GetStandardValues(self, context) :
        return TypeConverter.StandardValuesCollection(Array[int]([1, 2, 3, 4]))

    def GetStandardValuesSupported(self, context) :
        return True

class TestUnitNumber(object):
    DisplayName = 'HWController TestUnit number'
    Category = 'HW Assisted WhiteBox (Netduino HW)'
    Description = "The TestUnit (DUT, Remote) this Marble instance controls (1-4)"
    DefaultValue = 1
    Converter = TestUnitNumberToInt32Converter()

class PowerOnPhoneSequence(object):
    DisplayName = 'sequence for powering on the phone'
    Description = 'sequence executed when PowerOnPhone command is run'
    Category = 'HW Assisted WhiteBox (Netduino HW)'
    DefaultValue = 'DisconnectUSBMain,DisconnectPower,Sleep:2000,ConnectPower,Sleep:2000,PressKeylockPowerButton:8000,Sleep:2000,ConnectUSBMain'

class DeveloperMode(object):
    DisplayName = 'developer mode'
    Description = "Select True to show IronPython console window in parallel with GUI. Default = False"
    DefaultValue = False