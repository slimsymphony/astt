
import clr;
clr.AddReference('System.Windows.Forms')
clr.AddReference('System.Design')
clr.AddReference('System.Drawing')

from System import Array, Environment, Object, String
from System.ComponentModel import TypeConverter, StringConverter
from System.Windows.Forms.Design import IWindowsFormsEditorService
from System.Drawing.Design import UITypeEditor, UITypeEditorEditStyle

class CustomStringConverter(StringConverter) :
    
    def GetStandardValues(self, context) :
        return TypeConverter.StandardValuesCollection(Array[String](['Normal', 'Leader', 'Follower']))
    
    def GetStandardValuesSupported(self, context) :
        return True
        
class ExecutionMode(object) :
    DisplayName = 'execution mode'
    Description = ' * Normal: Normal, single environment execution. \n' \
                  ' * Leader: Set up service for followers, send execution steps during the execution\n' \
                  ' * Follower: Connect to Leader service and follow execution steps\n'
    Category = 'Execution'
    DefaultValue = 'Normal'
    Converter = CustomStringConverter()
    
class SyncPCDateTime(object) :
    DisplayName = 'sync phone time with PC'
    Description = 'Synchronize phone time from PC in beginning of each test case execution'
    DefaultValue = False
    
class DumpFileFetchInterval(object) :
    DisplayName = 'crashfile fetching interval'
    Category = 'Follower settings'
    Description = "(Only No connection and Follower modes): How many cases will be executed until USB is connected and crash files fetched"
    DefaultValue = 1
    
class QCRamDumpPath(object) :
    DisplayName = 'ram dump path'
    Category = 'Crash dumps'
    Description = "Location where QPST saves ram dumps"
    DefaultValue = 'C:\ProgramData\Qualcomm\QPST\Sahara'

class QCRamDumpPort(object) :
    DisplayName = 'ram dump port'
    Category = 'Crash dumps'
    Description = "Port of current device in QPST Configurator, e.g. COM53"
    DefaultValue = ''

class FailTestIfCrashDumpsFound(object):
    DisplayName = 'fail if crash dumps found'
    Category = 'Crash dumps'
    Description = "Fail test case if crash dump files are found during execution. Default = True"
    DefaultValue = True
    
class NotSoFatalCrashDumps(object):
    DisplayName = 'do not fail to these crash dumps'
    Category = 'Crash dumps'
    Description = "Comma separated list of crash dump file strings. When the string is found from the crash dump file name, only warning will be shown. Default = strictmode, system_server_lowmem, system_app_wtf, .tmp"
    DefaultValue = 'strictmode, system_server_lowmem, system_app_wtf, .tmp'
    
class CreateBugReportOnFailure(object):
    DisplayName = 'bug report when crash dumps are found'
    Category = 'Crash dumps'
    Description = "Create bug report after test case when crash dumps are found. Note: Bug report creation might take few minutes. \nIf HTML formatted report is wanted, java needs to be installed on the test system. Default = False"
    DefaultValue = False
    
class DeleteCrashDumpsFromDevice(object):
    DisplayName = 'delete copied crash dumps from device'
    Category = 'Crash dumps'
    Description = "Delete copied crash dumps from device. Default = False"
    DefaultValue = False

class DeleteRawRamDumpsFromDevice(object):
    DisplayName = 'delete raw ram dumps from device'
    Category = 'Crash dumps'
    Description = "Delete raw ram dumps from device with engineering builds. Default = True"
    DefaultValue = True
    
class CopyRawRamDumpsFromDevice(object):
    DisplayName = 'copy raw ram dumps from device'
    Category = 'Crash dumps'
    Description = "Copy raw ram dumps from device with engineering builds instead of copying Noklog dumps. Default = False"
    DefaultValue = False

class TakeHeapDumps(object):
    DisplayName = 'take heap dumps after test case'
    Category = 'Heap dumps'
    Description = "Take heap dumps after test case. Default = False"
    DefaultValue = False
    
class HeapDumpProcesses(object):
    DisplayName = 'list of heap dump process names'
    Category = 'Heap dumps'
    Description = "Comma separated list of process names from which heap dumps are taken. When empty, heap dumps are taken from all processes. Default = ''"
    DefaultValue = ''
    
class ReportTimeBetweenUIEvents(object):
    DisplayName = 'report time between UI events'
    Category = 'Performance'
    Description = "Report time between UI events. Default = False"
    DefaultValue = False
    
class ReportUIEventFps(object):
    DisplayName = 'report UI event FPS'
    Category = 'Performance'
    Description = "Report UI event FPS. Default = False"
    DefaultValue = False

class LogFormatStringConverter(StringConverter):
    
    def GetStandardValues(self, context) :
        return TypeConverter.StandardValuesCollection(Array[String](['Brief', 'Process', 'Tag', 'Raw', 'Time', 'ThreadTime', 'Long']))
    
    def GetStandardValuesSupported(self, context) :
        return True

    def GetStandardValuesExclusive(self, context) :
        return True

class LogFormat(object):
    DisplayName = 'log format'
    Category = 'Log'
    Description = "Used log format. Supports same formats as logcat (Brief, Process, Tag, Raw, Time, ThreadTime, Long). Default = ThreadTime"
    DefaultValue = 'ThreadTime'
    Converter = LogFormatStringConverter()
    
class LoggingEnabled(object):
    DisplayName = 'logging'
    Category = 'Log'
    Description = "Whether logcat output will be stored during test execution. Default = False"
    DefaultValue = False
    
class MTBFServiceURL(object) :
    DisplayName = 'leader Service URL'
    Description = 'URL / IP address of Leader'
    Category = 'Follower settings'
    DefaultValue = '4FID12345'
    
class DebugLevel(object) :
    DisplayName = 'debug level'
    Description = "Select how much debug info you want to get to main/remote console. 1 = lowest, 4 = highest"
    DefaultValue = 2

class EnableBlackBox(object) :
    DisplayName = 'enable blackbox'
    Description = "Setting for enabling or disabling blackbox"
    DefaultValue = False
    ReadOnlyForUser = True

class EnableVideoRecorder(object) :
    DisplayName = 'video recording'
    Description = "Setting for enabling or disabling video recording from external video source"
    DefaultValue = False
    
class DisableTestCaseSetupAndTeardown(object) :
    DisplayName = 'disable test case setup and teardown'
    Description = "Setting for enabling or disabling test case setup and teardown. If enabled, test cases will give warning and No result will be given"
    DefaultValue = False
    ReadOnlyForUser = True

class EnableMonkeyTesting(object) :
    DisplayName = 'enable monkey testing'
    Description = "Disable certain framework features for monkey testing"
    DefaultValue = False

class TracingEnabled(object) :
    DisplayName = 'tracing enabled'
    Description = "Setting for enabling or disabling tracing"
    DefaultValue = False
    ReadOnlyForUser = True

class MemoryLeakTestingEnabled(object) :
    DisplayName = 'memory leak testing enabled'
    Description = "Setting for enabling or disabling memory leak analysis"
    DefaultValue = False
    ReadOnlyForUser = True

class DeleteSuccessBlx(object) :
    DisplayName = 'delete success blx'
    Description = "enable deletion of successful testcase result blx"
    DefaultValue = False

class TraceXmlFilePath(object) :
    DisplayName = 'trace xml-file path'
    Description = "Xml-file for enabling phone traces"
    DefaultValue = ''
    ReadOnlyForUser = True

class AutomaticRejectCallForReferencePhone(object) :
    DisplayName = 'enable automatic reject call for reference phone'
    Description = "Granite will automatically reject calls for reference phone before and after test case"
    DefaultValue = True
    
class AutomaticProvisioningSettingsWrite(object) :
    DisplayName = 'enable automatic ntn/btn provisioning settings writing'
    Description = "Granite will automatically write provisioning settings to phone's ntn/btn sim card(s)"
    DefaultValue = True    

class QCAddressStringConverter(StringConverter) :
    
    def GetStandardValues(self, context) :
        return TypeConverter.StandardValuesCollection(Array[String](['Training database', 'Production database']))
    
    def GetStandardValuesSupported(self, context) :
        return True

    def GetStandardValuesExclusive(self, context) :
        return True


class QCAddress(object):
    DisplayName = 'qc address'
    Category = 'QC/ALM'
    Description = "URL to QC server"
    DefaultValue = 'Training database'
    Converter = QCAddressStringConverter()

class QCDomain(object):
    DisplayName = 'qc domain'
    Category = 'QC/ALM'
    Description = "QC Domain name"
    DefaultValue = ''

class QCProject(object):
    DisplayName = 'qc project'
    Category = 'QC/ALM'
    Description = "QC Project name"
    DefaultValue = ''

class QCTestSet(object):
    DisplayName = 'qc test set id'
    Category = 'QC/ALM'
    Description = "QC Test Set Id"
    DefaultValue = ''

class QCUsername(object):
    DisplayName = 'qc username'
    Category = 'QC/ALM'
    Description = "Username for QC"
    DefaultValue = ''

class QCPassword(object):
    DisplayName = 'qc password'
    Category = 'QC/ALM'
    Description = "Password for QC"
    DefaultValue = ''
    
class BLTUEMeasureInterval(object):
    DisplayName = 'measure interval'
    Category = 'BLTUE'
    Description = "Interval in milliseconds how ofter current is measured"
    DefaultValue = 200

class BLTUEAverageInterval(object):
    DisplayName = 'average interval'
    Category = 'BLTUE'
    Description = "Interval in milliseconds how ofter periodic average value and total average value are measured"
    DefaultValue = 5000
    
class BLTUEOutputModeStringConverter(StringConverter) :
    
    def GetStandardValues(self, context) :
        return TypeConverter.StandardValuesCollection(Array[String](['only averages', 'full', 'off']))
    
    def GetStandardValuesSupported(self, context) :
        return True

    def GetStandardValuesExclusive(self, context) :
        return True

class BLTUEOutputMode(object) :
    DisplayName = 'output mode'
    Category = 'BLTUE'
    Description = 'BLTUE console output mode. Use "full" to get all current measurement data.\n"only averages" will only print average values.'
    DefaultValue = "only averages"
    Converter = BLTUEOutputModeStringConverter()
    
class BLTUEOutputVoltage(object):
    DisplayName = 'output voltage'
    Category = 'BLTUE'
    Description = 'The DUT battery voltage / Output voltage of PSU. Max value: 4.25 V'
    DefaultValue = 3.83

class POXSIPProxyStringConverter(StringConverter) :
    
    def GetStandardValues(self, context) :
        return TypeConverter.StandardValuesCollection(Array[String](['SIPMGW', 'OpenSIPS']))
    
    def GetStandardValuesSupported(self, context) :
        return True
        
class EnablePOXBackend(object) :
    DisplayName = 'enable pox backend'
    Category = 'POX Backend'
    Description = 'Setting for enabling or disabling POX backend for VirtualPhone / virtual ReferencePhone usage\nAccess path: TestRun.EnablePOXBackend'
    DefaultValue = False

class EnableVirtualReferencePhone(object) :
    DisplayName = 'enable virtual reference phone'
    Category = 'POX Backend'
    Description = 'Setting for using POX backend as virtual ReferencePhone\nAccess path: TestRun.EnableVirtualReferencePhone'
    DefaultValue = False
    
class POXBackendServerUri(object) :
    DisplayName = 'pox server uri'
    Category = 'POX Backend'
    Description = 'Server uri of POX Backend\nAccess path: TestRun.POXBackendServerUri'
    DefaultValue = 'http://10.36.66.10:8003'

class POXSIPProxy(object) :
    DisplayName = 'pox sip proxy'
    Description = 'Configures POX to use the specified SIP Proxy\nThe configuration is done automatically by Granite'
    Category = 'POX Backend'
    DefaultValue = 'SIPMGW'
    ReadOnlyForUser = True
    Converter = POXSIPProxyStringConverter()
   
class POXmlRpcProxyTimeout(object):
    DisplayName = 'xml-rpc proxy timeout'
    Category = 'POX Backend'
    Description = 'HTTP timeout in seconds to wait for XML-RPC command to execute\nAccess path: TestRun.POXmlRpcProxyTimeout'
    DefaultValue = 25
    
class POXmlRpcCommandRetryCount(object):
    DisplayName = 'xml-rpc command retry-count'
    Category = 'POX Backend'
    Description = 'The amount of retries to execute upon failure\nAccess path: TestRun.POXmlRpcCommandRetryCount'
    DefaultValue = 3
    
class POXmlRpcDelayBetweenRetries(object):
    DisplayName = 'xml-rpc delay between retries'
    Category = 'POX Backend'
    Description = 'The delay in seconds to wait before re-trying in XML-RPC failure situation'
    DefaultValue = 10

class POXFailAmountMax(object):
    DisplayName = 'max amount of consecutive pox failures'
    Category = 'POX Backend'
    Description = 'the maximum amount of consecutive failures to occur before giving up'
    DefaultValue = 3    
    
class AllowPhoneReset(object):
    DisplayName = 'phone reset allowed'
    Description = 'True: Reset the phone in freeze situation. False: execution will be paused and e-mail is sent to e-mail addresses defined\nAccess path: TestRun.AllowPhoneReset'
    Category = 'Phone freeze reset settings'
    DefaultValue = True

class UseLongHWPressToReset(object):
    DisplayName = 'use long power key press to reset phone (HW assisted whitebox only)'
    Description = 'True: Reset is done via KEYCODE_POWER press. False: Reset is done by removing battery '
    Category = 'Phone freeze reset settings'
    DefaultValue = False

class LongHWPressToResetPhoneLength(object):
    DisplayName = 'long power key press to reset phone length (HW assisted whitebox only)'
    Description = 'Length(ms) of HW press executed to reset phone. Default = 20 000 ms.'
    Category = 'Phone freeze reset settings'
    DefaultValue = 20000

class UserInformation(object):
    DisplayName = 'E-mail addresses of test engineer(s)'
    Description = 'If something goes wrong during the execution, hold the execution and send mail to these addresses'
    Category = 'Phone freeze reset settings'
    DefaultValue = 'test_engineer@nokia.com, test_engineer2@nokia.com'

class StationDescription(object):
    DisplayName = 'Station description'
    Description = 'Station ID, or other free description that will be included in the Subject field of the e-mail message.'
    Category = 'Phone freeze reset settings'
    DefaultValue = ''

class VideoStillImageCaptureInterval(object):
    DisplayName = 'image taking interval'
    Description = 'Take still image from video after every N step. Comments and delays are not affecting the interval.'
    Category = 'Leader settings'
    DefaultValue = 3
    
class PhoneLockEnabled(object):
    DisplayName = 'phone lock is enabled'
    Description = 'Phone lock code needs to be entered when the display locks'
    Category = 'Follower settings'
    DefaultValue = True
    
class CustomMultilineEditor(UITypeEditor) :
           
    def GetEditStyle(self, context) :

        return UITypeEditorEditStyle.DropDown
    
    def EditValue(self, context, provider, value) :

        service = provider.GetService(clr.GetClrType(IWindowsFormsEditorService))

        if service != None :
            tb = TextBox()
            tb.Multiline = True
            tb.Text = value
            f = Form()
            f.Controls.Add(tb)
            f.FormBorderStyle = FormBorderStyle.None
            f.TopLevel = False
            tb.Dock = DockStyle.Fill
            service.DropDownControl(f)
            value = tb.Text
        
        return value


class EvaluateSettings(object):
    DisplayName = 'settings specific to Follower'
    Description = 'These setting names will be sent to follower instead of sending the values'
    Category = 'Leader settings'
    Editor = CustomMultilineEditor()
    DefaultValue = 'self.settings.BT.BTName,\n\
self.settings.RemoteMisc.BTName,\n\
self.settings.Accounts.FacebookPassword,\n\
self.settings.Accounts.FacebookUsername,\n\
self.settings.Accounts.GoogleEmailPassword,\n\
self.settings.Accounts.GoogleEmailUsername,\n\
self.settings.Accounts.NokiaAccountPassword,\n\
self.settings.Accounts.NokiaAccountUsername,\n\
self.settings.Accounts.NokiaEmailPassword,\n\
self.settings.Accounts.NokiaEmailUsername,\n\
self.settings.Accounts.OtherEmailPassword,\n\
self.settings.Accounts.OtherEmailUsername,\n\
self.settings.Accounts.TwitterPassword,\n\
self.settings.Accounts.TwitterUsername,\n\
self.settings.Accounts.VkontaktePassword,\n\
self.settings.Accounts.VkontakteUsername,\n\
self.settings.Accounts.WindowsEmailPassword,\n\
self.settings.Accounts.WindowsEmailUsername,\n\
self.settings.Accounts.YahooEmailPassword,\n\
self.settings.Accounts.YahooEmailUsername,\n\
self.settings.Main.SIM1PhoneNumber,\n\
self.settings.Main.SIM2PhoneNumber,\n\
self.settings.Reference.PhoneNumber,\n\
self.settings.Remote.SIM1PhoneNumber,\n\
self.settings.Remote.SIM2PhoneNumber,\n\
self.settings.Virtual.PhoneNumber,\n\
self.settings.Main.VoIPAccount,\n\
self.settings.Main.VoIPPassword'

class WaitFollowersToFinishTimeout(object):
    DisplayName = 'wait timeout in teardown'
    Description = 'When testcase has been finished, followers might still process their execution. This timeout defines how long followers will be waited'
    Category = 'Leader settings'
    DefaultValue = 360

class RequiredFollowers(object):
    DisplayName = 'number of required followers'
    Description = 'How many followers are required at least to start execution. If some followers are offline, they will be waited for defined timeout (Wait timeout in setup). This setting defines how many at least has to be online.'
    Category = 'Leader settings'
    DefaultValue = 1

class FollowersCount(object):
    DisplayName = 'number of followers'
    Description = 'How many followers in total are in execution'
    Category = 'Leader settings'
    DefaultValue = 1

class WaitForFollowers(object):
    DisplayName = 'wait timeout in setup'
    Description = 'How long leader will wait for all followers to join for execution of a test case'
    Category = 'Leader settings'
    DefaultValue = 10
    
class UseSearchWithNavigate(object):
    DisplayName = 'use search when navigating'
    Description = 'Search is opened from application list and given app name is searched when selecting'
    Category = 'Leader settings'
    DefaultValue = False
    
class BLTEnabledInFollower(object):
    DisplayName = 'enable BLT measument in follower'
    Description = ''
    Category = 'Leader settings'
    DefaultValue = False

class LeaderReportingOptions(object) :
    DisplayName = 'reporting options'
    Description = '-i  add images to report. -l  add links to report.\n-s  single html (cannot be used with images).'
    Category = 'Leader settings'
    DefaultValue = '-i -l'
