using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;
using Marble.Model;
using Marble.Utilities;
using MarbleLibrary.Utilities;

namespace Marble.Communication
{

    /// <summary>
    /// Specifies the format of the function to be called after command has been executed.
    /// </summary>
    /// <param name="command"></param>
    public delegate void CommandExecutedCallBack(BaseCommand command);

    /// <summary>
    /// Abstract base class that all connector commands inherit.
    /// </summary>
    public abstract class BaseCommand
    {
        /// <summary>
        /// The number of times this command has been tried to execute.
        /// Zero meaning this command hasn't been in execution yet.
        /// </summary>
        public int TryCount = 0;

        /// <summary>
        /// Error reason if the command couldn't be executed properly.
        /// </summary>
        public string Error = string.Empty;

        /// <summary>
        /// Command string that instructs the framework to act.
        /// </summary>
        public string Command = "";

        /// <summary>
        /// Whether this command is created by connector itself.
        /// On true this command is handled internally and connector done event is not triggered
        /// after successful execution of this command.
        /// </summary>
        public bool IsConnectorOriginated;

        /// <summary>
        /// Method to be called after this command has been executed.
        /// </summary>
        public CommandExecutedCallBack CallBackMethod;

        /// <summary>
        /// This method should return the specific command string that is sent to framework.
        /// </summary>
        /// <returns></returns>
        public abstract string CreateCommand();

        /// <summary>
        /// This method should return short information string that is printed to console when executing this command.
        /// </summary>
        /// <returns></returns>
        public abstract string GetInfoString();
    }

    /// <summary>
    /// Encapsulates information required to send an images fetch command to framework.
    /// Resulting file contains image (png) names paired with the logical path.
    /// </summary>
    public class ImagesCommand : BaseCommand
    {
        public string ResultPath { get; set; }
        const string CommandName = "images";

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="resultPath">File system path for the resulting file.</param>
        public ImagesCommand(string resultPath)
        {
            this.ResultPath = resultPath;
            this.Command = CommandName;
        }

        /// <summary>
        /// Creates a string that instructs framework to perform images fetch
        /// </summary>
        /// <returns>String that can be sent to framework</returns>
        public override string CreateCommand()
        {
            String[] strParams = { Command, this.ResultPath };
            return String.Join("|", strParams) + "\n";
        }

        /// <summary>
        /// Returns information string that is printed to console when executing this command
        /// </summary>
        /// <returns>"Images fetch"</returns>
        public override string GetInfoString()
        {
            return "Images fetch";
        }
    }

    /// <summary>
    /// This command has precedence over any other commands.
    /// It's immediately executed from the queue even if connector is already executing another command.
    /// </summary>
    public class EmergencyStop : ShutdownFramework
    {
        public EmergencyStop(string reason = "") { this.Reason = reason; }

        /// <summary>
        /// Returns information string that is printed to console when executing this command
        /// </summary>
        /// <returns></returns>
        public override string GetInfoString()
        {
            return string.IsNullOrEmpty(this.Reason) ? "Emergency stop" : string.Format("Emergency stop ({0})", this.Reason);
        }
    }

    /// <summary>
    /// Instructs the framework to stop execution of the current test case.
    /// </summary>
    public class StopExecution : BaseCommand
    {
        const string CommandName = "stop";

        public StopExecution()
        {
            this.Command = CommandName;
        }

        /// <summary>
        /// Creates a string that instructs the framework to stop execution.
        /// </summary>
        /// <returns>"stop\n"</returns>
        public override string CreateCommand() { return Command + "\n"; }

        /// <summary>
        /// Returns information string that is printed to console when executing this command
        /// </summary>
        /// <returns>"Stop execution"</returns>
        public override string GetInfoString() { return "Stop execution"; }
    }

    /// <summary>
    /// Instructs the framework to shutdown itself.
    /// </summary>
    public class ShutdownFramework : BaseCommand
    {
        public string Reason = "";
        const string CommandName = "quit";

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="reason">Reason for the framework shutdown.</param>
        public ShutdownFramework(string reason = "")
        {
            this.Command = CommandName;
            this.Reason = reason;
        }
        /// <summary>
        /// Creates a string that instructs the framework to shutdown itself.
        /// </summary>
        /// <returns>"quit\n"</returns>
        public override string CreateCommand() { return Command + "\n"; }

        /// <summary>
        /// Returns information string that is printed to console when executing this command
        /// </summary>
        /// <returns>"Framework shutdown" appended with a possible reason in parentheses.</returns>
        public override string GetInfoString()
        {
            if (string.IsNullOrEmpty(this.Reason))
                return "Framework shutdown";
            return string.Format("Framework shutdown ({0})", Reason);
        }
    }

    /// <summary>
    /// Notifies the framework that the last case of the current queue has been run.
    /// So framework performs some finalizations e.g. stops tracing
    /// </summary>
    public class TestRunEnd : BaseCommand
    {
        const string CommandName = "test_run_end";

        public TestRunEnd()
        {
            this.Command = CommandName;
        }

        /// <summary>
        /// Creates a string that notifies framework that whole test run has been executed.
        /// </summary>
        /// <returns>"test_run_end\n"</returns>
        public override string CreateCommand() { return Command + "\n"; }

        /// <summary>
        /// Returns information string that is printed to console when executing this command
        /// </summary>
        /// <returns>"Test run end"</returns>
        public override string GetInfoString() { return "Test run end"; }
    }

    /// <summary>
    /// 
    /// </summary>
    public class DisableLockScreen : BaseCommand
    {
        const string CommandName = "disable_lock_screen";

        public DisableLockScreen()
        {
            this.Command = CommandName;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns>"disable_lock_screen\n"</returns>
        public override string CreateCommand() { return Command + "\n"; }

        /// <summary>
        /// Returns information string that is printed to console when executing this command
        /// </summary>
        /// <returns>"Disable lock screen"</returns>
        public override string GetInfoString() { return "Disable lock screen"; }
    }

    /// <summary>
    /// 
    /// </summary>
    public class ExecuteTestStep : BaseCommand
    {
        const string CommandName = "execute";

        /// <summary>
        /// Creates a new <see cref="ExecuteTestStep"/> object.
        /// </summary>
        /// <param name="testStep">Test step to be executed.</param>
        public ExecuteTestStep(string testStep)
        {
            this.Command = CommandName;
            this.TestStep = testStep;
        }

        /// <summary>
        /// Test step to be executed.
        /// </summary>
        public string TestStep
        {
            get;
            private set;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns>"execute\n"</returns>
        public override string CreateCommand()
        {
            String[] strParams = { Command, TestStep };
            return String.Join("|", strParams) + "\n";        
        }

        /// <summary>
        /// Returns information string that is printed to console when executing this command
        /// </summary>
        /// <returns>"Execute test step"</returns>
        public override string GetInfoString() { return "Execute test step"; }
    }

    /// <summary>
    /// Enables updating of the settings file after the framework is started.
    /// </summary>
    public class SettingsCommand : BaseCommand
    {
#if FRAMEWORK_SUPPORTS_MARBLE_SETTINGS_DIRECTORY
        /// <summary>
        /// The settings file path property is private since it is not required when using 
        /// settings directories and the new settings functionality.
        /// </summary>
        private string SettingsFilePath { get; set; }
#else
        public string SettingsFilePath { get; set; }
#endif
        const string CommandName = "settings";

#if FRAMEWORK_SUPPORTS_MARBLE_SETTINGS_DIRECTORY
        /// <summary>
        /// Constructor
        /// </summary>
        public SettingsCommand()
        {
            this.Command = CommandName;
            this.SettingsFilePath = string.Empty;
        }

#else
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="settingsFilePath">File system path of the settings file that framework should open.</param>
        public SettingsCommand(string settingsFilePath)
        {
            this.Command = CommandName;
            this.SettingsFilePath = settingsFilePath;
        }
#endif

        /// <summary>
        /// Creates a string that instructs the framework to update settings.
        /// </summary>
        /// <returns>String that can be sent to framework.</returns>
        public override string CreateCommand()
        {
            String[] strParams = { Command, this.SettingsFilePath };
            return String.Join("|", strParams) + "\n";
        }

        /// <summary>
        /// Returns information string that is printed to console when executing this command
        /// </summary>
        /// <returns>"Settings update"</returns>
        public override string GetInfoString()
        {
            return "Settings update";
        }
    }

    /// <summary>
    /// Encapsulates information required to send a capture command to framework.
    /// Results to real phone display capture (png) and detected display elements (xml).
    /// </summary>
    public class CaptureCommand: BaseCommand
    {
        public string ResultPath { get; set; }
        const string CommandName = "capture";

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="resultPath">File system path for the resulting display capture and xml file.</param>
        public CaptureCommand(string resultPath)
        {
            this.Command = CommandName;
            this.ResultPath = resultPath;
        }

        /// <summary>
        /// Creates a string that instructs framework to perform capture
        /// </summary>
        /// <returns>String that can be sent to framework</returns>
        public override string CreateCommand()
        {
            String[] strParams = { Command, this.ResultPath};
            return String.Join("|", strParams) + "\n";
        }

        /// <summary>
        /// Returns information string that is printed to console when executing this command
        /// </summary>
        /// <returns>"Display capture"</returns>
        public override string GetInfoString()
        {
            return "Display capture";
        }
    }

    /// <summary>
    /// Encapsulates information required to send init command to the marble fw socket server
    /// </summary>
    public class InitMarbleServerCommand : BaseCommand
    {
        const string CommandName = "init_server";

        public InitMarbleServerCommand()
        {
            this.Command = CommandName;
        }

        /// <summary>
        /// Creates a string that instructs framework to initialize BlackBox
        /// </summary>
        /// <returns></returns>
        public override string CreateCommand() { return Command + "\n"; }

        /// <summary>
        /// Returns information string that is printed to console when executing this command
        /// </summary>
        /// <returns></returns>
        public override string GetInfoString()
        {
            return "Initialize Marble Server";
        }
    }

    /// <summary>
    /// Encapsulates information required to send a test case execution command to framework
    /// </summary>
    public class RunTestCaseCommand: BaseCommand
    {
        public TestScript TestScript { get; set; }
        public string TestCaseName { get; set; }
        public string ReportPath { get; set; }
        const string CommandName = "run";

        /// <summary>
        /// Whether to run the test case in blackbox or whitebox mode.
        /// </summary>
        public bool RunInBlackbox { get; set; }

        /// <summary>
        /// Whether BLT-UE current measurement/dummy battery simulation is enabled
        /// </summary>
        public bool BltUeEnabled { get; set; }

        /// <summary>
        /// File path of the workflow XAML test case file to run.
        /// </summary>
        public string XamlFilePath
        {
            get;
            private set;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="testCaseName">Name of the test case.</param>
        /// <param name="xamlFilePath">File path of the workflow XAML file containing the test case.</param>
        /// <param name="reportFolder">Path to the directory where resulting XML is saved.</param>
        /// <param name="runInBlackbox">Flag that indicates whether to run the test case in blackbox (or whitebox) mode.</param>
        /// <param name="enableBltUe">Indicates whether BLT-UE currentmeasurement and dummy battery simulation is enabled for test run</param>
        public RunTestCaseCommand(string testCaseName, string xamlFilePath, string reportFolder, bool runInBlackbox = false, bool enableBltUe = false)
        {
            // Store the information
            this.Command = CommandName;
            this.TestCaseName = testCaseName;
            this.XamlFilePath = xamlFilePath;
            this.ReportPath = reportFolder;
            this.RunInBlackbox = runInBlackbox;
            this.BltUeEnabled = enableBltUe;
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="testScript">Information about the exact location of the test method to be executed</param>
        /// <param name="testCaseName">Name of the test case to be executed</param>
        /// <param name="reportFolder">Path to the directory where resulting xml is saved</param>
        /// <param name="runInBlackbox">Flag that indicates whether to run the test case in blackbox (or whitebox) mode.</param>
        /// <param name="enableBltUe">Indicates whether BLT-UE currentmeasurement and dummy battery simulation is enabled for test run</param>
        public RunTestCaseCommand(TestScript testScript, string testCaseName, string reportFolder, bool runInBlackbox = false, bool enableBltUe = false)
        {
            this.TestScript = testScript;
            this.Command = CommandName;
            this.TestCaseName = testCaseName;
            this.ReportPath = reportFolder;
            this.RunInBlackbox = runInBlackbox;
            this.BltUeEnabled = enableBltUe;
        }

        /// <summary>
        /// Creates a string that instructs framework to execute this test case
        /// </summary>
        /// <returns>String that can be sent to framework</returns>
        public override string CreateCommand()
        {
            IEnumerable<string> strParams = new[] { Command };

            // If this is a workflow xaml test
            if (!string.IsNullOrEmpty(XamlFilePath))
            {
                strParams = strParams.Concat(new[] { XamlFilePath, ReportPath, RunInBlackbox.ToString() });
            }

            // Else if this is a CTT test
            else if (CoreTestToolUtilities.IsCoreTestToolScript(TestScript))
            {
                strParams = strParams.Concat(new[] { FileUtilities.ConvertRelativePathToAbsolutePath(TestScript.Directory), TestScript.file,
                    TestScript.className, TestScript.method, TestCaseName, ReportPath, RunInBlackbox.ToString(), BltUeEnabled.ToString() });
            }

            // Else if this is a NTH test
            else if (NokiaTestHarnessUtilities.IsNokiaTestHarnessScript(TestScript))
            {
                strParams = strParams.Concat(new[] { TestScript.Directory, TestScript.file, TestScript.className, TestScript.method, TestCaseName,
                    ReportPath, RunInBlackbox.ToString(), BltUeEnabled.ToString() });
            }

            // Else this is a standard test
            else
            {
                //String[] strParams = { fwCommand, folder, file, className, methodName, testCaseName, reportFolder };
                strParams = strParams.Concat(TestScript.getValues());
                strParams = strParams.Concat(new[] { TestCaseName, ReportPath, RunInBlackbox.ToString(), BltUeEnabled.ToString() });
            }

            return String.Join("|", strParams) + "\n";
        }

        /// <summary>
        /// Returns information string that is printed to console when executing this command
        /// </summary>
        /// <returns>Name of the test case in this command</returns>
        public override string GetInfoString()
        {
            return this.TestCaseName;
        }
    }

    /// <summary>
    /// Encapsulates information required to send a command to retrieve the phone menu XML information.
    /// </summary>
    /// <remarks>
    /// Run test case command requires a single command parameter to be sent to framework (menu XML file path).
    /// </remarks>
    public class MenuCommand : BaseCommand
    {
        /// <summary>
        /// Command to send to the framework.
        /// </summary>
        const string CommandName = "menu";

        /// <summary>
        /// Creates a new <see cref="MenuCommand"/> object.
        /// </summary>
        /// <param name="menuXmlFilePath">File path where the phone menu XML information is to be saved.</param>
        public MenuCommand(string menuXmlFilePath)
        {
            // Store the information
            this.Command = CommandName;
            this.MenuXmlFilePath = menuXmlFilePath;
        }

        /// <summary>
        /// File path of the menu XML file.
        /// </summary>
        public string MenuXmlFilePath
        {
            get;
            private set;
        }

        /// <summary>
        /// Creates a string that instructs framework to execute this test case.
        /// </summary>
        /// <returns>String that can be sent to framework.</returns>
        public override string CreateCommand()
        {
            String[] strParams = { Command, this.MenuXmlFilePath };
            return String.Join("|", strParams) + "\n";
        }

        /// <summary>
        /// Returns information string that is printed to console when executing this command.
        /// </summary>
        /// <returns>"Retrieving phone menu information"</returns>
        public override string GetInfoString()
        {
            return "Retrieving phone menu information";
        }
    }

    /// <summary>
    /// Encapsulates information required to send a command to create a Core Test Tool (CTT) test set.
    /// </summary>
    /// <remarks>
    /// Create test set command requires an array of assemblies and a test set file path name for the file to create.
    /// </remarks>
    public class CreateCoreTestToolTestSetCommand : BaseCommand
    {
        /// <summary>
        /// Command to send to the framework.
        /// </summary>
        const string CommandName = "create_ctt_test_set";

        /// <summary>
        /// Creates a new <see cref="CreateCoreTestToolTestSetCommand"/>
        /// </summary>
        /// <param name="assemblyFilePaths">Assembly file paths.</param>
        /// <param name="testSetFilePath">File path of the test set file to be created.</param>
        public CreateCoreTestToolTestSetCommand(string[] assemblyFilePaths, string testSetFilePath)
        {
            // Store the information
            this.Command = CommandName;
            AssemblyFilePaths = assemblyFilePaths;
            TestSetFilePath = testSetFilePath;
        }

        /// <summary>
        /// Assembly file paths.
        /// </summary>
        /// <remarks>The framework will retrieve the test cases from each assembly.</remarks>
        public string[] AssemblyFilePaths
        {
            get;
            private set;
        }

        /// <summary>
        /// File path of the test set file to be created.
        /// </summary>
        public string TestSetFilePath
        {
            get;
            private set;
        }

        /// <summary>
        /// Creates a string that instructs framework to execute this test case.
        /// </summary>
        /// <returns>String that can be sent to framework.</returns>
        public override string CreateCommand()
        {
            String[] strParams = { Command, CreateXml(AssemblyFilePaths), TestSetFilePath };
            return String.Join("|", strParams) + "\n";
        }

        /// <summary>
        /// Generates XML information about the assemblies.
        /// </summary>
        /// <param name="assemblyFilePaths">Assembly file paths.</param>
        /// <returns>XML string containing the assemblies.</returns>
        /// <remarks>This XML information is processed by the framework.</remarks>
        private static string CreateXml(string[] assemblyFilePaths)
        {
            XElement root = new XElement("Assemblies");

            foreach (string assemblyFilePath in assemblyFilePaths)
            {
                XElement assembly = new XElement("Assembly");
                assembly.SetAttributeValue("Location", assemblyFilePath);
                root.Add(assembly);
            }

            return root.ToString(SaveOptions.DisableFormatting);
        }

        /// <summary>
        /// Returns information string that is printed to console when executing this command.
        /// </summary>
        /// <returns>"Create test set"</returns>
        public override string GetInfoString()
        {
            return "Create CTT test set";
        }
    }


    /// <summary>
    /// Encapsulates information required to send a command to create a SX test set.
    /// </summary>
    /// <remarks>
    /// Create test set command requires an array of assemblies and a test set file path name for the file to create.
    /// </remarks>
    public class CreateSxTestSetCommand : BaseCommand
    {
        /// <summary>
        /// Command to send to the framework.
        /// </summary>
        const string CommandName = "create_sx_test_set";

        /// <summary>
        /// Creates a new <see cref="Marble.Communication.CreateSxTestSetCommand"/>
        /// </summary>
        /// <param name="scriptFilePaths">Script file paths.</param>
        /// <param name="testSetFilePath">File path of the test set file to be created.</param>
        public CreateSxTestSetCommand(string[] scriptFilePaths, string testSetFilePath)
        {
            // Store the information
            this.Command = CommandName;
            ScriptFilePaths = scriptFilePaths;
            TestSetFilePath = testSetFilePath;
        }

        /// <summary>
        /// Script file paths.
        /// </summary>
        /// <remarks>The framework will retrieve the test cases from SX files.</remarks>
        public string[] ScriptFilePaths
        {
            get;
            private set;
        }

        /// <summary>
        /// File path of the test set file to be created.
        /// </summary>
        public string TestSetFilePath
        {
            get;
            private set;
        }

        /// <summary>
        /// Creates a string that instructs framework to execute this test case.
        /// </summary>
        /// <returns>String that can be sent to framework.</returns>
        public override string CreateCommand()
        {
            String[] strParams = { Command, CreateXml(ScriptFilePaths), TestSetFilePath };
            return String.Join("|", strParams) + "\n";
        }

        /// <summary>
        /// Generates XML information about the scripts.
        /// </summary>
        /// <param name="scriptFilePaths">Script file paths.</param>
        /// <returns>XML string containing the scripts.</returns>
        /// <remarks>This XML information is processed by the framework.</remarks>
        private static string CreateXml(string[] scriptFilePaths)
        {
            XElement root = new XElement("SXScripts");

            foreach (string sp in scriptFilePaths)
            {
                XElement s = new XElement("Script");
                s.SetAttributeValue("Location", sp);
                root.Add(s);
            }

            return root.ToString(SaveOptions.DisableFormatting);
        }

        /// <summary>
        /// Returns information string that is printed to console when executing this command.
        /// </summary>
        /// <returns>"Create test set"</returns>
        public override string GetInfoString()
        {
            return "Create SX test set";
        }
    }

    /// <summary>
    /// Encapsulates information required to send a command to update Core Test Tool (CTT) configuration.
    /// </summary>
    /// <remarks>
    /// Update configuration command requires the test application assembly location, the section name and the XML containing the updated information.
    /// </remarks>
    public class UpdateCoreTestToolConfigurationCommand : BaseCommand
    {
        /// <summary>
        /// Command to send to the framework.
        /// </summary>
        const string CommandName = "update_ctt_configuration";

        /// <summary>
        /// Creates a new <see cref="UpdateCoreTestToolConfigurationCommand"/>
        /// </summary>
        /// <param name="assemblyFilePath">Assembly file path.</param>
        /// <param name="sectionName">Name of the section.</param>
        /// <param name="sectionXml">Serialized XML configuration information.</param>
        public UpdateCoreTestToolConfigurationCommand(string assemblyFilePath, string sectionName, string sectionXml)
        {
            // Store the information
            Command = CommandName;
            AssemblyFilePath = assemblyFilePath;
            SectionName = sectionName;
            SectionXml = sectionXml;
        }

        /// <summary>
        /// Assembly file path.
        /// </summary>
        /// <remarks>The framework will update the configuration for the assembly.</remarks>
        public string AssemblyFilePath
        {
            get;
            private set;
        }

        /// <summary>
        /// Name of the section.
        /// </summary>
        /// <remarks>Name of the section in the configuration.</remarks>
        public string SectionName
        {
            get;
            private set;
        }

        /// <summary>
        /// Section configuration information.
        /// </summary>
        /// <remarks>Configuration information that has been serialized to XML.</remarks>
        public string SectionXml
        {
            get;
            private set;
        }

        /// <summary>
        /// Creates a string that instructs framework to update the configuration.
        /// </summary>
        /// <returns>String that can be sent to framework.</returns>
        public override string CreateCommand()
        {
            String[] strParams = { Command, AssemblyFilePath, SectionName, SectionXml };
            return String.Join("|", strParams) + "\n";
        }

        /// <summary>
        /// Returns information string that is printed to console when executing this command.
        /// </summary>
        /// <returns>"Update CTT configuration"</returns>
        public override string GetInfoString()
        {
            return "Update CTT configuration";
        }
    }

}
