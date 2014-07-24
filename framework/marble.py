"""Marble Framework Launcher

    The module implements the main execution module for the Marble Framework.

Command line parameters

    -h / -?                 -- Print this usage text.

    --settings_dir          -- Set the folder that contains Marble setting files

                                Example: --settings_dir "c:\\marble\\settings"

                                NOTE: When not given, Marble uses default settings directory automatically

    --test_set              -- Path to test set xml file

                                Example: --test_set "c:\\marble\\test.testset"

    --tc_filter             -- String for filtering test case execution
                                * this filter only adds test case(s) to execution
                                * case sensitive, "string in string" type of filter

                                Example: --tc_filter "my test case id"

    --logging               -- For enabling Marble logging

                                Example: --logging

    --test_result_dir       -- Set folder for test results

                                Example: --test_result_dir "c:\\marble\\marble_test_results"

    --repeat                -- Set number of test case or test set repeats

                                Example: --repeat 5

    --connection            -- Used for overriding connection coming from settings

                                Usage:  --connection <serial number>
                                Example: --connection 12345abc

    --debug                 -- Used for overriding debug level coming from settings

                                Example: --debug 3

    --run_hours             -- Set number of hours how long test set will be repeated

                                Example: --run_hours 120

    --blackbox_phonemodel   -- Used when running BlackBox cases from command line. Loads the phone model specific settings for BlackBox.
                                Example: --blackbox_phonemodel "Aqua F1" --blackbox_phonemodel RM-902

    --graybox_enabled       -- For enabling test execution in GrayBox mode. This is currently for CI environment where
                                keypresses are emulated with BlackBox HW and touch presses are simualted with WhiteBox

                                Example: --graybox_enabled

    --test_file_list        -- ascii file containing list of test script file paths to be executed

    --test_file_xml         -- xml file(s) containing list of test script file paths to be executed

                                Example:           --test_file_xml c:\\marble\\test_files.xml
                                Wild card example: --test_file_xml c:\\marble\\test_file*

    --dbg_view              -- For enabling logging with DbgView.exe in CLI mode
                                * creates dbg_view_log.txt file to test result folder

                                Example: --dbg_view

    --ci_enabled            -- Indicates that execution is started from CI environment and
                               Marble QC/ALM account should be used with QC transactions.

    --enable_backend        -- Indicates that Marble POX backend is enabled.
                                When enabled, the reference phone related commands are executed in the backend server.

    --enable_qc             -- Enable test set downloading and result uploading with QC/ALM

    --no_qc_upload          -- Do not upload results to qc after tests have been executed

    --remove_qc_testset     -- Remove QC test set file after test execution

    --qc_domain             -- Domain name for QC/ALM

    --qc_project            -- Project name for QC/ALM

    --qc_db                 -- QC/ALM database which should be used. Possible values are
                               'Training database' or 'Production database'

    --qc_test_set_id        -- QC/ALM test set id which should be executed.

    
    Example launch command: ipy marble.py --test_set c:\\my_test_set.testset --connection 12345abc
"""

# System module imports
import sys, os, getopt, __builtin__, types, subprocess, time
from glob import glob

import clr

from System import GC, GCCollectionMode, DateTime, AppDomain, Environment
from System.IO import File
from System.Net import WebException
from System.CodeDom import Compiler
from Microsoft.CSharp import CSharpCodeProvider

# append needed paths to sys.path
import marble
startupPath = os.path.dirname(marble.__file__)

paths = [ \
    os.path.join(startupPath, 'dlls'),
    os.path.join(startupPath, 'dlls', 'MessageAPI'),
    os.path.join(startupPath, 'dlls', 'corva'),
    os.path.join(startupPath, 'utils', 'corva'),
    ]

# reverse list so that root dll folder will be the first item in sys.path
paths.reverse()

for p in paths:
    if not p in sys.path:
        sys.path.insert(0, p)

# core's configuration dictionary to be used throughout FW
import core
core.FW_conf = {'connection'                :  None,
                'current_connection'        :  "",
#                'recorder'                 :  False,
                'settings'                  :  None, # settings manager instance
                'old_settings'              :  None, # old settings model instance
                                                     # FIXME: Remove this when C.I no longer needs to give old .settings files
                'settings_dir'              :  os.path.normpath(os.path.join(startupPath, '..\\settings\default')),
                'gui_server_conf'           :  None,
                'com_int'                   :  None,
                'encoder_isi_length'        :  32768, #DO NOT TOUCH!!!  #16384,
                'decoder_isi_length'        :  49152, #DO NOT TOUCH!!!
                'header_dir'                :  os.path.join(startupPath, 'include'),
                'cache_dir'                 :  os.path.join(startupPath, '.cache'),
                'test_result_name'          :  "",
                'test_result_dir'           :  os.path.join(startupPath, 'test_results'),
                'test_set_xml'              :  None,
                'startup_path'              :  startupPath,
                'tc_filter'                 :  "",
                'cli_mode'                  :  True,
                'trace'                     :  None,
                'tracing_enabled'           :  False,
                'memory_leak_detection'     :  False,
                'memory_leak_current_loop'  :  1,
                'trace_set_xml'             :  "",
                'delete_success_blx'        :  False,
                'repeat'                    :  1,
                'repeat_index'              :  0,
                'blackbox'                  :  None,
                'blackbox_enabled'          :  None,
                'graybox_enabled'           :  None, # Set to true if in BlackBox mode touch & key presses are simulated instead of using HW emulation cards (BlackBox default)
                'blackbox_phonemodel'       :  "",
                'flash_diff'                :  "",
                'param_connection'          :  "",
                'param_connection_refphone' :  "",
                'param_pmd'                 :  "",
                'param_debug'               :  False,
                'error_capture'             :  False, # Framework in capturing display from error situation
                'run_hours'                 :  0,
                'test_file_list'            :  "",    # ascii file containing list of test script file paths to be executed
                'test_file_xml'             :  "",    # xml file containing list of test script file paths to be executed
                'remote_connection'         :  None,
                'remote_method'             :  False, #set to True if scripting method is executed in remote phone.
                'std_stream_service'        :  None,
                'audio_devices'             :  [],    # list to keep track of opened audio devices
                'should_stop'               :  False,  # will be set to True by when testing should be stopped (user abort)
                'blt_ue'                    :  None,
                'bltue_enabled'             :  False,
                'dbg_view_enabled'          :  False,
                'enable_qc'                 :  False,
                'no_qc_upload'              :  False,
                'remove_qc_testset'         :  False,
                'wintermute'                :  False,
                'ci_enabled'                :  False,
                'follower'                  :  False,
                'qc_domain'                 :  None,
                'qc_project'                :  None,
                'qc_db'                     :  None,
                'qc_test_set_id'            :  None,
                'testrunner'                :  None,
                'backend_enabled'           :  None,
                'granite_server_activated'  :  False,
                'prov_settings_written'     :  False,
                'connection_manager'        :  None,
                'crash_fetch_interval'      :  None,      # blackbox testing fetches crashfiles after defined amount of tc executions
                'initial_crash_fetch_done'  :  False,
                'ramdump_method'            :  None,      # ram dumps can be fetched from sdcard or via USB.
                'cli_logging'               :  False      # flag for enabling logging from command line
               }

# Marble modules and imports
from core.settings.settings_model import ReadOnlySettingsModel
from core import debug, testrunner, phone, remote_phone
from core.reporting.xslt_report_generator import XSLTTestReportGenerator
from interfaces.fw_communication_server import FWCommunicationServer
from interfaces.blackbox_interface import MarbleBlackBoxInterface
from interfaces.blt_ue_interface import GraniteBltUeInterface
from interfaces.qc_interface import QCInterface
from utils.file_utils import getFileList
clr.AddReference('TestAutomation.Gui.Marble.Settings')
from TestAutomation.Gui.Marble.Settings import SettingsManager
from core.leader import LeaderHandler, GraniteLeadService
from utils.email_sender import EmailSender
clr.AddReference("Nokia.Granite.HtmlReporting")
from Nokia.Granite.HtmlReporting import HtmlReporting
# create builtin resources instance to be used from scripts
from utils.resources import Resources
resources = Resources()
__builtin__.resources = resources


# register unhandled exception handler
def reportUnhandledException(sender, event):
    exceptionReportFolder = os.path.join(core.FW_conf['test_result_dir'], 'framework_crashes')
    exceptionReportPath = os.path.join(exceptionReportFolder, 'MarbleFrameworkCrash%s.txt' % DateTime.Now.ToString("yyyyMMddHHmmss"))

    # create folder is necessary
    if not os.path.isdir(exceptionReportFolder):
        os.makedirs(exceptionReportFolder)

    if event.ExceptionObject:
        try:
            oFile = open(exceptionReportPath, 'w')
            oFile.write(event.ExceptionObject.ToString())
            oFile.close()
        except:
            pass

    Environment.Exit(1)

AppDomain.CurrentDomain.UnhandledException += reportUnhandledException

# hide IronPython crashes coming from unmanaged code
def hideUnmanagedCodeCrashes():
    unmanagedCode = \
    """
    using System;
    using System.Runtime.InteropServices;

    namespace UnmanagedCode
    {
        public class Errors
        {
            [DllImport("kernel32.dll")]
            static extern ErrorModes SetErrorMode(ErrorModes uMode);

            [Flags]
            public enum ErrorModes : uint
            {
                SYSTEM_DEFAULT = 0x0,
                SEM_FAILCRITICALERRORS = 0X0001,
                SEM_NOALIGNMENTFAULTEXCEPT = 0X0004,
                SEM_NOGPFAULTERRORBOX = 0x0002,
                SEM_NOOPENFILEERRORBOX = 0x0008
            }

            public static void Hide()
            {
                var mode = SetErrorMode(ErrorModes.SEM_NOGPFAULTERRORBOX);
                SetErrorMode(mode | ErrorModes.SEM_NOGPFAULTERRORBOX | ErrorModes.SEM_NOOPENFILEERRORBOX | ErrorModes.SEM_FAILCRITICALERRORS);
            }
        }
    }
    """
    # set compiler parameters
    compilerParams = Compiler.CompilerParameters()
    compilerParams.GenerateInMemory = True
    compilerParams.TreatWarningsAsErrors = False
    compilerParams.GenerateExecutable = False
    compilerParams.CompilerOptions = "/optimize"

    # compile C# code
    provider = CSharpCodeProvider()
    compile = provider.CompileAssemblyFromSource(compilerParams, unmanagedCode)

    # report compilation errors if any
    if compile.Errors.HasErrors:
        raise Exception("Compile error: %s" % '\n'.join(str(error) for error in compile.Errors))

    # add compiled assembly reference
    clr.AddReference(compile.CompiledAssembly)

    # import code and execute in IronPython
    from UnmanagedCode import Errors
    Errors.Hide()

hideUnmanagedCodeCrashes()

if not globals().has_key('orig_stdout'):
    orig_stdout = sys.stdout
    debug.init(orig_stdout)
    __builtin__.debug = debug

    # Install hooks
    sys.stderr = debug.err
    sys.stdout = debug.out

    debug.setLevel(2) # Brief

# ============================================================================
def usage():
# ----------------------------------------------------------------------------
    """Print usage info.
    """
    debug.brf(__doc__)

# ============================================================================
def parseCommandLine():
# ----------------------------------------------------------------------------
    """Parse command line parameters. """
    try:
        options, arguments = getopt.getopt(sys.argv[1:], "?h:", \
                                           ['recorder', 'settings=', 'settings_dir=', 'test_set=', 'tc_filter=', \
                                            'trace', 'trace_xml=', 'test_result_dir=', 'repeat=', \
                                            'connection=', 'connectionrefphone=','flash_diff=', 'debug=', 'run_hours=', 'blackbox_phonemodel=', \
                                            'graybox_enabled', 'test_file_list=', 'test_file_xml=', 'dbg_view','enable_qc',
                                            'no_qc_upload','remove_qc_testset', 'wintermute','ci_enabled','qc_domain=','qc_project=', \
                                            'qc_db=','qc_test_set_id=','follower=','enable_backend', 'logging'])

        for option, argument in options:
            if option in ['-h', '-?']:
                usage()
                sys.exit()

#            if option in ['--recorder']:
#                core.FW_conf['recorder'] = True

            if option in ['--settings']:
                core.FW_conf['old_settings'] = argument

            if option in ['--settings_dir']:
                assert os.path.isdir(argument), \
                    'Invalid settings directory (%s) given!' % str(argument)
                core.FW_conf['settings_dir'] = argument

            if option in ['--enable_qc']:
                core.FW_conf['enable_qc'] = True

            if option in ['--test_set']:
                assert os.path.isfile(argument), 'Invalid test set xml given!'

                core.FW_conf['test_set_xml'] = argument

            if option in ['--tc_filter']:
                core.FW_conf['tc_filter'] = argument

            if option in ['--trace']:
                core.FW_conf['tracing_enabled'] = True

            if option in ['--trace_xml']:
                assert os.path.isfile(argument), '--trace_xml parameter is not a valid file!'
                core.FW_conf['trace_set_xml'] = argument

            if option in ['--test_result_dir']:
                assert os.path.isdir(argument), \
                    'Invalid test result directory (%s) given!' % str(argument)
                core.FW_conf['test_result_dir'] = argument

            if option in ['--repeat']:
                assert type(eval(argument)) == types.IntType and \
                       eval(argument) > 0, 'Invalid repeat value given!'

                core.FW_conf['repeat'] = int(argument)

            if option in ['--connection']:
                core.FW_conf['param_connection'] = argument

            if option in ['--connectionrefphone']:
                core.FW_conf['param_connection_refphone'] = argument

            if option in ['--flash_diff']:
                core.FW_conf['flash_diff'] = argument

            if option in ['--debug']:
                assert type(eval(argument)) == types.IntType and \
                    4 >= eval(argument) >= 0, 'Invalid debug level value given!'
                debug.setLevel(eval(argument))
                core.FW_conf['param_debug'] = True

            if option in ['--run_hours']:
                assert type(eval(argument)) == types.IntType and \
                       eval(argument) > 0, 'Invalid run_hours value given!'

                core.FW_conf['run_hours'] = int(argument)

            # Also set blackbox_enabled to True if blackbox_phonemodel given.
            if option in ['--blackbox_phonemodel']:
                core.FW_conf['blackbox_phonemodel'] = argument
                core.FW_conf['blackbox_enabled'] = True

            if option in ['--graybox_enabled']:
                core.FW_conf['graybox_enabled'] = True

            if option in ['--test_file_list']:
                assert os.path.isfile(argument), 'Invalid test file list given!'

                core.FW_conf['test_file_list'] = argument

            if option in ['--test_file_xml']:
                assert os.path.isfile(argument) or len(glob(argument)) >= 1, 'Invalid test file xml given!'

                core.FW_conf['test_file_xml'] = argument

            if option in ['--dbg_view']:
                core.FW_conf['dbg_view_enabled'] = True

            if option in ['--follower']:
                if not argument in ['true', 'True']:
                    core.FW_conf['follower'] = argument
                else:
                    debug.brf('Using leader service settings')
                    core.FW_conf['follower'] = True

            if option in ['--no_qc_upload']:
                core.FW_conf['no_qc_upload'] = True

            if option in ['--remove_qc_testset']:
                core.FW_conf['remove_qc_testset'] = True

            if option in ['--wintermute']:
                core.FW_conf['wintermute'] = True

            if option in ['--ci_enabled']:
                core.FW_conf['ci_enabled'] = True

            if option in ['--qc_domain']:
                core.FW_conf['qc_domain'] = argument

            if option in ['--qc_project']:
                core.FW_conf['qc_project'] = argument

            if option in ['--qc_db']:
                assert argument in ['Training database','Production database'], "Invalid database name given. Database must be either 'Training database' or 'Production database'"

                core.FW_conf['qc_db'] = argument

            if option in ['--qc_test_set_id']:
                assert type(eval(argument)) == types.IntType, 'Invalid qc_test_set_id value given!'

                core.FW_conf['qc_test_set_id'] = argument

            if option in ['--enable_backend']:
                core.FW_conf['backend_enabled'] = True

            if option in ['--bltue_enabled']:
                core.FW_conf['bltue_enabled'] = True

            if option in ['--logging']:
                core.FW_conf['cli_logging'] = True

    except getopt.GetoptError, e:
        print e
        usage()
        sys.exit(2)

    if not core.FW_conf['settings_dir']:
        assert core.FW_conf['old_settings'], '--settings or --settings_dir parameter is mandatory'
    if core.FW_conf['old_settings']:
        assert os.path.isfile(core.FW_conf['old_settings']), '--settings parameters is not a valid file'

    assert core.FW_conf['encoder_isi_length'] <= 65535, \
        'Invalid encoder_isi_length configured!'
    assert core.FW_conf['decoder_isi_length'] <= 65535, \
        'Invalid decoder_isi_length configured!'

    if core.FW_conf['run_hours']:
        assert core.FW_conf['repeat'] == 1, "--repeat can't be used together with --run_hours!"

    if core.FW_conf['test_set_xml']:
        assert core.FW_conf['test_file_list'] == "", "--test_file_list can't be used together with --test_set!"
        assert core.FW_conf['test_file_xml'] == "", "--test_file_xml can't be used together with --test_set!"

    if core.FW_conf['test_file_list']:
        assert core.FW_conf['test_file_xml'] == "", "--test_file_xml can't be used together with --test_file_list!"

    if core.FW_conf['test_file_xml']:
        assert core.FW_conf['test_file_list'] == "", "--test_file_list can't be used together with --test_file_xml!"

def configureSettings():
    """Load settings model instance for Framework."""
    # settings has been given with --settings (OLD STYLE)
    if core.FW_conf['old_settings']:
        # create the settings model
        settingsModel = ReadOnlySettingsModel()

        debug.vrb('Loading settings from: %s' % core.FW_conf['old_settings'])
        # update d_product.SETTING from testware settings
        settingsModel.loadSettings(\
                            os.path.basename(core.FW_conf['old_settings']),
                            os.path.dirname(core.FW_conf['old_settings']) + '\\')

        # testware settings instance
        core.FW_conf['old_settings'] = settingsModel

    # settings directory has been given with --settings_dir (usually from GUI)
    if core.FW_conf['settings_dir']:
        # set settings manager to testware settings instance
        core.FW_conf['settings'] = SettingsManager.Instance

        debug.vrb('Loading settings from: %s' % core.FW_conf['settings_dir'])
        try:
            core.FW_conf['settings'].LoadSettingsFromDirectory(core.FW_conf['settings_dir'])
        except Exception, e:
            debug.err("Exception in loading settings: %s"%str(e))
            raise SystemExit('Fatal settings error, unable to continue!')


    # we must have settings manager instance here
    if not core.FW_conf['settings']:
        raise SystemExit('Fatal settings error, unable to continue!')

    # take values from settings
    core.FW_conf['gui_server_conf'] = \
        core.FW_conf['settings'].System.GuiFrameworkProtocolPort

    if not core.FW_conf['param_debug']:
        debug.setLevel(core.FW_conf['settings'].TestRun.DebugLevel)

    # take initial graybox enabled value from settings if not given in commandline with --graybox_enabled
    # the System.HWAssistedWhiteBoxEnabled flag is automatically set if Netduino based HW is found by Marble GUI
    if core.FW_conf['graybox_enabled'] is None:
        core.FW_conf['graybox_enabled'] = core.FW_conf['settings'].System.HWAssistedWhiteBoxEnabled

    # take initial tracing enabled value from settings
    # let's not disable traces it they are already enabled with --trace
    if not core.FW_conf['tracing_enabled']:
        core.FW_conf['tracing_enabled'] = core.FW_conf['settings'].TestRun.TracingEnabled

    #take initial memory leak detection value from settings
    if core.FW_conf['settings'].TestRun.MemoryLeakTestingEnabled and core.FW_conf['tracing_enabled']:
        core.FW_conf['memory_leak_detection'] = True

    #take inital value for deleting successfully executed testcase blx
    if core.FW_conf['settings'].TestRun.DeleteSuccessBlx and core.FW_conf['tracing_enabled'] and not core.FW_conf['memory_leak_detection']:
        core.FW_conf['delete_success_blx'] = True

    # take initial backend enabled value from settings if not given in commandline with --enable_backend
    if core.FW_conf['backend_enabled'] is None:
        core.FW_conf['backend_enabled'] = core.FW_conf['settings'].TestRun.EnablePOXBackend

def startSocketInterface():
    if sys.flags.debug:
        from System.Diagnostics import Debugger
        if not Debugger.IsAttached:
            Debugger.Launch()

    debug.addGuiAppender(core.FW_conf['settings'].System.FrameworkGuiLoggerPort)
    # take initial blackbox enabled value from settings if not given in commandline
    if core.FW_conf['blackbox_enabled'] is None:
        core.FW_conf['blackbox_enabled'] = core.FW_conf['settings'].TestRun.EnableBlackBox

    if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader': # wrap blackbox in leader mode
        core.FW_conf['blackbox'] = LeaderHandler(MarbleBlackBoxInterface())
    else: # create blackbox interface and start WCF service for GUI
        core.FW_conf['blackbox'] = MarbleBlackBoxInterface()

    # For HW Assisted WhiteBox set blackbox_enabled to True 
    if core.FW_conf['graybox_enabled'] and core.FW_conf['blackbox'].isHwAssistedWhiteBox():
        core.FW_conf['blackbox_enabled'] = True
    
    # create BLT-UE interface and start WCF service for GUI
    core.FW_conf['blt_ue'] = GraniteBltUeInterface()
    core.FW_conf['blt_ue'].startBltUeGuiInterfaceService()

    core.FW_conf['cli_mode'] = False

    # set up GUI <--> Framework communication interface
    core.FW_conf['com_int'] = FWCommunicationServer(\
            core.FW_conf['gui_server_conf'])

    debug.out('Started Marble Framework socket interface')

    core.FW_conf['com_int'].FWCommandLoop()

    # Dispose blackbox object. Also stops video recording if running.
    core.FW_conf['blackbox'].Dispose()

    core.FW_conf['blt_ue'].Dispose()

    # exit with return code 0
    sys.exit(0)

def closeConnections():
    """Close main and possible remote phone connections."""
    # Close remote connections before closing main connection. Closing main connection
    # calls Dispose for connection manager!
    for remote in core.FW_conf['remote_connection']:
        remote.closeConnection(True)

    if core.FW_conf['connection']:
        core.FW_conf['connection'].closeConnections(True)


###########################
#    MARBLE STARTUP      #
###########################

# parse command line parameters
try:
    params = parseCommandLine()

    startupInfoString = "MARBLE FRAMEWORK STARTED"
    versionInfoFilePath = os.path.join(os.path.split(startupPath)[0], 'MarbleVersion.txt')
    if os.path.isfile(versionInfoFilePath):
        versionInfoFile = open(versionInfoFilePath, 'r')
        startupInfoString += ' (%s)' % versionInfoFile.read().strip('\n')
        versionInfoFile.close()

    debug.brf(startupInfoString)

    # configure settings
    configureSettings()
    debug.out("Configuring settings")

    # Create EmailSender for automatic phone freeze email notifications (if enabled)
    core.FW_conf['mail_sender'] = EmailSender()

    if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader': # start the leader service
        core.FW_conf['leader'] = GraniteLeadService.Instance
        core.FW_conf['leader'].ServiceStart()
        debug.brf('MTBF Leader mode started')

    # create phone manager instance
    core.FW_conf['connection'] = phone.PhoneManager()

    if core.FW_conf['follower']:

        # add the Log4Net GUI appender
        debug.addGuiAppender(core.FW_conf['settings'].System.FrameworkGuiLoggerPort)

        if core.FW_conf['settings'].TestRun.ExecutionMode != 'Follower':
            debug.brf('MTBF mode has not been set from GUI settings')
            os._exit(1)

        debug.brf('Follower mode..')

        # Create blackbox interface
        core.FW_conf['blackbox'] = MarbleBlackBoxInterface()
        if core.FW_conf['blackbox_enabled']:
            # Set up black box with proper phone settings
            core.FW_conf['blackbox'].setupBlackBoxTesting(core.FW_conf['blackbox_phonemodel'])

        # For HW Assisted WhiteBox set blackbox_enabled to True 
        if core.FW_conf['graybox_enabled'] and core.FW_conf['blackbox'].isHwAssistedWhiteBox():
            core.FW_conf['blackbox_enabled'] = True

        # create phone connections
        core.FW_conf['connection'].connect()
        core.FW_conf['connection'].closeConnection()
        core.FW_conf['remote_connection'] = remote_phone.RemotePhoneManager()
        core.FW_conf['remote_connection'].connect()

        # initialize test runner
        testRunner = testrunner.MarbleTestRunner()

        #create folder share for report
        clr.AddReference('LeaderFollowerInterface')
        from LeaderFollowerInterface import FolderShare
        share = os.path.abspath(core.FW_conf['test_result_dir'])
        debug.brf('Sharing %s as %s' % (share, os.path.split(share)[1]))
        try:
            FolderShare.CreateShare(str.replace(share, "\\", "\\"), os.path.split(share)[1])
        except Exception as e:
            debug.brf('Could not create test result share %s: %s' % (share, e.message))

        core.FW_conf['blt_ue'] = GraniteBltUeInterface()
        core.FW_conf['blt_ue'].startBltUeGuiInterfaceService()
        if core.FW_conf['bltue_enabled']:
            core.FW_conf['blt_ue'].setupBltUeTesting()

        from core.follower import Follower
        core.FW_conf['follower_client'] = Follower(testRunner)
        core.FW_conf['follower_client'].executionLoop()

        core.FW_conf['connection'].closeConnections()

        # Dispose blackbox object. Also stops video recording if running.
        core.FW_conf['blackbox'].Dispose()
        core.FW_conf['blt_ue'].Dispose()

        # exit with return code 0
        debug.brf('exit success')
        os._exit(0)

    # test set given with "test_set_xml" parameter
    # or ascii/xml file containing test case list
    if core.FW_conf['test_set_xml'] or core.FW_conf['test_file_list'] or core.FW_conf['test_file_xml'] or core.FW_conf['wintermute']:
        if sys.flags.debug:
            from System.Diagnostics import Debugger
            if not Debugger.IsAttached:
                Debugger.Launch()

        # start logging with Dbgview.exe if necessary
        if core.FW_conf['dbg_view_enabled']:
            dbgViewFilePath = os.path.join(startupPath, 'apps\\Dbgview.exe')
            if os.path.isfile(dbgViewFilePath):
                dbgViewProcess = subprocess.Popen('%s /t /l %s' % \
                    (dbgViewFilePath, os.path.join(core.FW_conf['test_result_dir'], 'dbg_view_log.txt')))
            else:
                dbgViewProcess = None

        # Create blackbox interface
        if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
            core.FW_conf['blackbox'] = LeaderHandler(MarbleBlackBoxInterface())
        else:
            core.FW_conf['blackbox'] = MarbleBlackBoxInterface()

        if core.FW_conf['blackbox_enabled']:
            # Set up black box with proper phone settings
            core.FW_conf['blackbox'].setupBlackBoxTesting(core.FW_conf['blackbox_phonemodel'])

        # create phone connection
        # NOTE: When param_connection is empty, serial will be taken from settings
        core.FW_conf['connection'].connect(serialNumber = core.FW_conf['param_connection'])

        # check device status
        core.FW_conf['connection']._tab._checkDeviceStatus()

        if core.FW_conf['flash_diff'] != "":
            try:
                if not core.FW_conf['connection'].srv.adl.flashDiff(core.FW_conf['flash_diff'], console=True):
                    debug.err("ADL diff flashing failed. Stopping test execution")
                    closeConnections()
                    sys.exit(2)
            except Exception, e:
                debug.err("ADL Flash diff failed! %s"%str(e))
                closeConnections()
                sys.exit(2)

        core.FW_conf['remote_connection'] = remote_phone.RemotePhoneManager()
        core.FW_conf['remote_connection'].connect()

        #activate traces from trace xml
        if core.FW_conf['trace_set_xml']:
            core.FW_conf['trace'].traceActivation(core.FW_conf['trace_set_xml'])
        elif core.FW_conf['tracing_enabled'] and core.FW_conf['settings'].TestRun.TraceXmlFilePath:
            traceXml = core.FW_conf['settings'].TestRun.TraceXmlFilePath
            core.FW_conf['trace'].traceActivation(traceXml)

        if core.FW_conf['tracing_enabled'] and core.FW_conf['memory_leak_detection']:
            traceXml = os.path.join(core.FW_conf['startup_path'], 'core\\data\\OS_Monitor_Block_hooks.xml')
            core.FW_conf['trace'].traceActivation(traceXml)

        # initialize test runner
        testRunner = testrunner.MarbleTestRunner()
        core.FW_conf['testrunner'] = testRunner

        # Create QC test set
        if core.FW_conf['enable_qc']:
            if not core.FW_conf['ci_enabled']:
                assert core.FW_conf['settings'].TestRun.QCAddress, "Check settings for QC access"
                assert core.FW_conf['settings'].TestRun.QCDomain, "Check settings for QC access"
                assert core.FW_conf['settings'].TestRun.QCPassword, "Check settings for QC access"
                assert core.FW_conf['settings'].TestRun.QCProject, "Check settings for QC access"
                assert core.FW_conf['settings'].TestRun.QCTestSet, "Check settings for QC access"
                assert core.FW_conf['settings'].TestRun.QCUsername, "Check settings for QC access"

                qc_addr = core.FW_conf['settings'].TestRun.QCAddress
                qc_domain = core.FW_conf['settings'].TestRun.QCDomain
                qc_project = core.FW_conf['settings'].TestRun.QCProject
                qc_pass = core.FW_conf['settings'].TestRun.QCPassword
                qc_user = core.FW_conf['settings'].TestRun.QCUsername
                qc_testset = core.FW_conf['settings'].TestRun.QCTestSet
            else:
                assert core.FW_conf['qc_domain'], "Check command-line options for QC access"
                assert core.FW_conf['qc_project'], "Check command-line options for QC access"
                assert core.FW_conf['qc_db'], "Check command-line options for QC access"
                assert core.FW_conf['qc_test_set_id'], "Check command-line options for QC access"

                qc_addr = core.FW_conf['qc_db']
                qc_domain = core.FW_conf['qc_domain']
                qc_project = core.FW_conf['qc_project']
                qc_pass = None
                qc_user = None
                qc_testset = core.FW_conf['qc_test_set_id']

            try:
                qcInterface = QCInterface()
                connectResult = qcInterface.connect(qc_addr,\
                    qc_user,\
                    qc_pass)
                if connectResult!="OK":
                    debug.err("Connection to QC failed! %s"%connectResult)
                    closeConnections()
                    sys.exit(2)
                else:
                    debug.brf("Connected to %s(%s)"%(qc_addr,qcInterface.qcAddressess[qc_addr]))

            except Exception, e:
                debug.err("Connection to QC failed! %s"%str(e))
                closeConnections()
                sys.exit(2)

            tempTestSetFileName = os.path.abspath(os.path.join(core.FW_conf['startup_path'],"..", 'test_sets', "qc_testset_%s.testset"%time.strftime("%m%d%Y_%H%M")))

            try:
                debug.brf("Downloading test set from QC, domain: %s, project: %s"%(qc_domain,qc_project))
                testset = qcInterface.getTestSet(qc_domain,\
                        qc_project,\
                        qc_testset,
                        os.path.join( os.path.abspath(os.path.split(core.FW_conf['test_file_xml'])[0]), os.path.split(core.FW_conf['test_file_xml'])[1]) )

                testset.Save(tempTestSetFileName)
                debug.brf("Test set loaded from QC.")
            except Exception,e:
                debug.err("Downloading test set from QC failed! %s"%str(e))
                closeConnections()

                if core.FW_conf['ci_enabled']:
                    debug.err("Test set might have been empty because of load balancing in CI. Exiting without error code.")
                    # Create empty NJUNIT report!!!
                    testRunner.addEmptyNjunitReport()
                    testRunner.saveNjunitReport()
                    sys.exit(0)
                else:
                    sys.exit(2)

            core.FW_conf['test_set_xml'] = tempTestSetFileName

        if core.FW_conf['wintermute']:
            debug.brf('Wintermute listener starting..')
            testRunner.run(('..\\test_sets\\', 'wmlistener', None, None))
        else:
            # Run test cases from test set
            testRunner.run(core.FW_conf['test_set_xml'] or core.FW_conf['test_file_list'] or core.FW_conf['test_file_xml'], core.FW_conf['tc_filter'])

        #For framework test_set runs stop trace blx recording here
        if core.FW_conf['memory_leak_detection'] and core.FW_conf['trace']:
            traceFileName = core.FW_conf['test_result_name'] + '_Memory_Leak'
            core.FW_conf['trace'].traceSaveBlxAndResumeTracing(traceFileName, memoryLeakDetection = True, uiEnabled=core.FW_conf['connection'].uiEnabled())
            core.FW_conf['trace'].graniteTraceConnection.StopRecording()
            core.FW_conf['trace'].graniteTraceConnection.CloseConnection()
        elif core.FW_conf['trace']:
            core.FW_conf['trace'].traceSaveBlxAndResumeTracing(uiEnabled=core.FW_conf['connection'].uiEnabled())
            core.FW_conf['trace'].graniteTraceConnection.StopRecording()
            core.FW_conf['trace'].graniteTraceConnection.CloseConnection()

        # create XSLT transformer
        generator = XSLTTestReportGenerator()

        # generate HTML report from all executed test cases
        generator.createReport(getFileList(os.path.join(core.FW_conf['test_result_dir'], 'xml'), fileExt = '.xml'),
                               core.FW_conf['test_result_dir'])

        # Generate new HTML report
        parser = HtmlReporting()
        try:
            parser.Generate(os.path.join(core.FW_conf['test_result_dir'], 'xml'))
        except Exception as e:
            debug.err("Exception happened in report generating: " + str(e))
        parser = None

        # Close remote connections before closing main connection. Closing main connection
        # calls Dispose for connection manager!
        for remote in core.FW_conf['remote_connection']:
            try:
                remote.termGraniteServer()
                remote.closeConnection(True)
            except AssertionError:
                pass

        # Memory card formatting disabled beacause of issues in CI
        #try:
        #    if core.FW_conf['ci_enabled']:
        #        if core.FW_conf['connection'].graniteConnection.fileSystem.PhoneHasMemoryCard():
        #            debug.brf("Formatting memory card")
        #            core.FW_conf['connection'].graniteConnection.fileSystem.Format("e")
        #except:
        #    debug.err("Memory card formatting operation failed")

        core.FW_conf['connection'].closeConnections()

        # Dispose blackbox object. Also stops video recording if running.
        if core.FW_conf['blackbox_enabled']:
            core.FW_conf['blackbox'].blackBox.Dispose()

        # save NJUNIT report for C.I
        testRunner.saveNjunitReport()

        # terminate DbgView.exe if necessary
        if core.FW_conf['dbg_view_enabled'] and dbgViewProcess:
            dbgViewProcess.terminate()

        if core.FW_conf['enable_qc']:
            if not core.FW_conf['no_qc_upload']:
                #Delete temporary test set after results are uploaded
                try:
                    debug.brf("Uploading test set to QC...")
                    if qcInterface.sendResults(tempTestSetFileName):
                        debug.brf("Test set uploaded to QC.")
                    else:
                        debug.brf("Test set uploading to QC failed!")
                except WebException, e:
                    debug.err("Uploading test results to QC failed! %s"%str(e))
                    debug.err(str(e.InnerException))
                    sys.exit(2)
                except Exception, e:
                    debug.err("Uploading test results to QC failed! %s"%str(e))
                    sys.exit(2)
            else:
                debug.brf("Uploading test results to QC skipped.")

            if core.FW_conf['remove_qc_testset']:
                try:
                    debug.brf("Remove QC test set")
                    File.Delete(tempTestSetFileName);
                except Exception, e:
                    debug.err("Removing temporary test set failed! %s"%str(e))
                    sys.exit(2)



        # exit with return code 0
        sys.exit(0)
    # socket interface launch for GUI control
    else:
        startSocketInterface()
except KeyboardInterrupt:
    debug.err("Stopping Marble execution")
    closeConnections()
    sys.exit(2)

