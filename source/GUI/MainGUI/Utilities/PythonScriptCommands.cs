using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Marble.ViewModel;

namespace Marble.Utilities
{
    using System.Globalization;
    using System.Windows;
    using System.Windows.Data;
    using System.Windows.Markup;

    using ICSharpCode.AvalonEdit.CodeCompletion;
    using ICSharpCode.AvalonEdit.Document;
    using ICSharpCode.AvalonEdit.Editing;

    /// <summary>
    /// Converts python string to boolean stating whether python script has valid prefix and postfix.
    /// </summary>
    public class HasPythonScriptValidPrefixAndPostfix : MarkupExtension, IValueConverter
    {
        private static HasPythonScriptValidPrefixAndPostfix converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new HasPythonScriptValidPrefixAndPostfix());
        }

        #region IValueConverter Members

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(value is string) || string.IsNullOrEmpty(value as string)) return false;

            var pythonScript = value as string;
            pythonScript = pythonScript.Trim();

            return pythonScript.StartsWith(PythonScriptCommands.PythonScriptCommonPrefix)
                   && pythonScript.EndsWith(PythonScriptCommands.PythonScriptCommonPostfix);

        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        #endregion
    }

    /// Implements AvalonEdit ICompletionData interface to provide the entries in the
    /// completion drop down.
    public class PythonParserCompletionData : ICompletionData
    {
        public PythonParserCompletionData(string text)
        {
            this.Text = text;
        }

        public System.Windows.Media.ImageSource Image
        {
            get { return null; }
        }

        public string Text { get; private set; }

        private object content;

        // Use this property if you want to show a fancy UIElement in the list.
        public object Content
        {
            get
            {
                if (content == null)
                    return this.Text;

                return content;
            }
            set
            {
                this.content = value;
            }
        }

        private object description;

        public object Description
        {
            get
            {
                //if (this.description == null || this.description.ToString() == string.Empty) 
                //    return "Description for " + this.Text;

                return description;
            }
            set
            {
                this.description = value;
            }
        }

        public double Priority { get; private set; }

        public void Complete(TextArea textArea, ISegment completionSegment,
            EventArgs insertionRequestEventArgs)
        {
            textArea.Document.Replace(completionSegment, this.Text);
        }
    }

    public enum AvailableMarblePythonCommands
    {
        self = 0,

        // 1. Basic commands
        back,
        check,
        clear,
        comment,
        doubleTap,
        drag,
        exit,
        expect,
        input,
        navigate,
        notExpect,
        pinch,
        pinchIn,
        pinchOut,
        select,
        swipe,
        tryExpect,

        // 2. Additional commands

        capture,
        delay,
        deviceInfo,
        fail,
        file,
        media,
        orientation,
        packages,
        reboot,
        settings,
        time,
        volume,
        toggle,

        // 3. Advanced commands

        addLogMarker,
        device,
        shell,
        sql,
        waitForEvent,

        // 4. BlackBox commands

        blackBox,

        blackBoxEnabled,
        ////connectUsb,
        ////connectSim,
        ////connectMemoryCard,
        ////connectAvPlug,
        ////executeHwOperation,

        /// 5. Power consumption testing commands

        battery
    }

    public class PythonScriptCommands
    {
        public static readonly string PythonScriptCommonPrefix = "self.";
        public static readonly string PythonScriptCommonPostfix = ")";

        /// <summary>
        /// Gets drag command ( self.drag(' ITEM ', (RELATIVE_X,RELATIVE_Y)) ).
        /// </summary>
        /// <param name="item"></param>
        /// <param name="relativeX"></param>
        /// <param name="relativeY"></param>
        /// <returns></returns>
        public static string GetDragCommand(string item, double relativeX, double relativeY)
        {
            return string.Format("self.gesture.drag('{0}', ({1:0.0000},{2:0.0000}))", item, relativeX, relativeY);
        }

        public static string GetDragCommand(string item, Point coordinate, Point size)
        {
            return PythonScriptCommands.GetDragCommand(item, Math.Round(coordinate.X / size.X, 4), Math.Round(coordinate.Y / size.Y, 4));
        }

        /// <summary>
        /// Gets toggle command ( self.toggle(' ITEM ') and self.toggle.set(' ITEM ', True/False) ).
        /// </summary>
        /// <param name="item"></param>
        /// <param name="newValue"></param>
        /// <returns></returns>
        public static string GetToggleCommand(string item, bool? newValue = null)
        {
            const string commandPrefix = "self.toggle('";
            const string commandPostfix = "')";

            const string commandPrefixForSet = "self.toggle.set('";
            const string commandPostfixForSet = ")";

            switch (newValue)
            {
                case null:
                    return commandPrefix + item + commandPostfix;
                case true:
                    return commandPrefixForSet + item + "', True" + commandPostfixForSet;
                case false:
                    return commandPrefixForSet + item + "', False" + commandPostfixForSet;
            }

            return null;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        public static string GetExpectCommand(string item, ElementSelectionMethod method = ElementSelectionMethod.BestPossible)
        {
            var methodName = Enum.GetName(typeof(ElementSelectionMethod), method);

            if (method == ElementSelectionMethod.BestPossible || methodName == null)
                return string.Format("self.expect('{0}')", item);

            methodName = Char.ToLowerInvariant(methodName[0]) + methodName.Substring(1);
            return string.Format("self.expect.{0}('{1}')", methodName, item);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        public static string GetNotExpectCommand(string item)
        {
            return string.Format("self.notExpect('{0}')", item);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        public static string GetCheckCommand(string item, ElementSelectionMethod method = ElementSelectionMethod.BestPossible)
        {
            var methodName = Enum.GetName(typeof(ElementSelectionMethod), method);

            if(method == ElementSelectionMethod.BestPossible || methodName == null)
                return string.Format("self.check('{0}')", item);

            methodName = Char.ToLowerInvariant(methodName[0]) + methodName.Substring(1);
            return string.Format("self.check.{0}('{1}')", methodName, item);            
        }


        public static PythonParserCompletionData GetDefaultParserCompletionDataAfterSelf(AvailableMarblePythonCommands command)
        {
            switch (command)
            {
                case AvailableMarblePythonCommands.self:
                    break;
                case AvailableMarblePythonCommands.back:
                    return new PythonParserCompletionData("back()") { Content = "back" };
                case AvailableMarblePythonCommands.battery:
                    return new PythonParserCompletionData("battery");
                case AvailableMarblePythonCommands.check:
                    return new PythonParserCompletionData("check('')") { Content = "check" };
                case AvailableMarblePythonCommands.clear:
                    return new PythonParserCompletionData("clear()") { Content = "clear" };
                case AvailableMarblePythonCommands.comment:
                    return new PythonParserCompletionData("comment('')") { Content = "comment" };
                case AvailableMarblePythonCommands.doubleTap:
                    return new PythonParserCompletionData("doubleTap('')") { Content = "doubleTap" };
                case AvailableMarblePythonCommands.drag:
                    return new PythonParserCompletionData("drag(''), ( , ))") { Content = "drag" };
                case AvailableMarblePythonCommands.exit:
                    return new PythonParserCompletionData("exit()") { Content = "exit" };
                case AvailableMarblePythonCommands.expect:
                    return new PythonParserCompletionData("expect('')") { Content = "expect" };
                case AvailableMarblePythonCommands.input:
                    return new PythonParserCompletionData("input('')") { Content = "input" };
                case AvailableMarblePythonCommands.navigate:
                    return new PythonParserCompletionData("navigate('')") { Content = "navigate" };
                case AvailableMarblePythonCommands.notExpect:
                    return new PythonParserCompletionData("notExpect('')") { Content = "notExpect" };
                case AvailableMarblePythonCommands.pinch:
                    return new PythonParserCompletionData("pinch()") { Content = "pinch" };
                case AvailableMarblePythonCommands.pinchIn:
                    return new PythonParserCompletionData("pinchIn()") { Content = "pinchIn" };
                case AvailableMarblePythonCommands.pinchOut:
                    return new PythonParserCompletionData("pinchOut()") { Content = "pinchOut" };
                case AvailableMarblePythonCommands.@select:
                    return new PythonParserCompletionData("select('')") { Content = "select" };
                case AvailableMarblePythonCommands.swipe:
                    return new PythonParserCompletionData("swipe(( , ), ( , ))") { Content = "swipe" };
                case AvailableMarblePythonCommands.tryExpect:
                    return new PythonParserCompletionData("tryExpect('')") { Content = "tryExpect" };
                case AvailableMarblePythonCommands.capture:
                    return new PythonParserCompletionData("capture()") { Content = "capture" };
                case AvailableMarblePythonCommands.delay:
                    return new PythonParserCompletionData("delay()") { Content = "delay" };
                case AvailableMarblePythonCommands.deviceInfo:
                    return new PythonParserCompletionData("deviceInfo()") { Content = "deviceInfo" };
                case AvailableMarblePythonCommands.fail:
                    return new PythonParserCompletionData("fail('')") { Content = "fail" };
                case AvailableMarblePythonCommands.file:
                    return new PythonParserCompletionData("file");
                case AvailableMarblePythonCommands.media:
                    return new PythonParserCompletionData("media");
                case AvailableMarblePythonCommands.orientation:
                    return new PythonParserCompletionData("orientation");
                case AvailableMarblePythonCommands.packages:
                    return new PythonParserCompletionData("packages");
                case AvailableMarblePythonCommands.reboot:
                    return new PythonParserCompletionData("reboot()") { Content = "reboot" };
                case AvailableMarblePythonCommands.settings:
                    return new PythonParserCompletionData("settings");
                case AvailableMarblePythonCommands.time:
                    return new PythonParserCompletionData("time");
                case AvailableMarblePythonCommands.volume:
                    return new PythonParserCompletionData("volume");
                case AvailableMarblePythonCommands.toggle:
                    return new PythonParserCompletionData("toggle()") { Content = "toggle" };
                case AvailableMarblePythonCommands.addLogMarker:
                    return new PythonParserCompletionData("addLogMarker('')") { Content = "addLogMarker" };
                case AvailableMarblePythonCommands.device:
                    return new PythonParserCompletionData("device");
                case AvailableMarblePythonCommands.shell:
                    return new PythonParserCompletionData("shell('')") { Content = "shell" };
                case AvailableMarblePythonCommands.sql:
                    return new PythonParserCompletionData("sql");
                case AvailableMarblePythonCommands.waitForEvent:
                    return new PythonParserCompletionData("waitForEvent('')") { Content = "waitForEvent" };
                case AvailableMarblePythonCommands.blackBox:
                    return new PythonParserCompletionData("blackBox");
                case AvailableMarblePythonCommands.blackBoxEnabled:
                    return new PythonParserCompletionData("blackBoxEnabled");
                //case AvailableMarblePythonCommands.connectUsb:
                //    completionDatas.Add(new PythonParserCompletionData("connectUsb('')") { Content = "connectUsb" });
                //    break;
                //case AvailableMarblePythonCommands.connectSim:
                //    completionDatas.Add(new PythonParserCompletionData("connectSim('')") { Content = "connectSim" });
                //    break;
                //case AvailableMarblePythonCommands.connectMemoryCard:
                //    completionDatas.Add(new PythonParserCompletionData("connectMemoryCard('')") { Content = "connectMemoryCard" });
                //    break;
                //case AvailableMarblePythonCommands.connectAvPlug:
                //    completionDatas.Add(new PythonParserCompletionData("connectAvPlug('')") { Content = "connectAvPlug" });
                //    break;
                //case AvailableMarblePythonCommands.executeHwOperation:
                //    completionDatas.Add(new PythonParserCompletionData("executeHwOperation('')") { Content = "executeHwOperation" });
                //    break;
                default:
                    throw new ArgumentOutOfRangeException("command");
            }

            return null;
        }

        public static List<PythonParserCompletionData> GetParserCompletionDataList(AvailableMarblePythonCommands command)
        {
            List<PythonParserCompletionData> completionDatas = new List<PythonParserCompletionData>();

            switch (command)
            {
                case AvailableMarblePythonCommands.self:
                    return getParserCompletionDataListForSelf();
                case AvailableMarblePythonCommands.back:
                    const string wikiDescription = "Steps back to the previous UI state by pressing the HW-key back. By default one back press is executed. Integer number can be given as a parameter to execute multiple back steps at once.";

                    completionDatas.Add(new PythonParserCompletionData("()") { Description = wikiDescription });
                    completionDatas.Add(new PythonParserCompletionData("(") { Description = wikiDescription });
                    break;
                case AvailableMarblePythonCommands.battery:
                    completionDatas.Add(new PythonParserCompletionData("measureCurrent()"));
                    completionDatas.Add(new PythonParserCompletionData("setVoltage('')"));
                    completionDatas.Add(new PythonParserCompletionData("isEnabled()"));
                    break;
                case AvailableMarblePythonCommands.check:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    completionDatas.Add(new PythonParserCompletionData("description('')"));
                    completionDatas.Add(new PythonParserCompletionData("text('')"));
                    break;
                case AvailableMarblePythonCommands.clear:
                    completionDatas.Add(new PythonParserCompletionData("()"));
                    break;
                case AvailableMarblePythonCommands.comment:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    break;
                case AvailableMarblePythonCommands.doubleTap:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    break;
                case AvailableMarblePythonCommands.drag:
                    completionDatas.Add(new PythonParserCompletionData("(''), ( , ))"));
                    break;
                case AvailableMarblePythonCommands.exit:
                    completionDatas.Add(new PythonParserCompletionData("()"));
                    break;
                case AvailableMarblePythonCommands.expect:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    break;
                case AvailableMarblePythonCommands.input:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    break;
                case AvailableMarblePythonCommands.navigate:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    completionDatas.Add(new PythonParserCompletionData("jump('')"));
                    break;
                case AvailableMarblePythonCommands.notExpect:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    break;
                case AvailableMarblePythonCommands.pinch:
                case AvailableMarblePythonCommands.pinchIn:
                case AvailableMarblePythonCommands.pinchOut:
                    completionDatas.Add(new PythonParserCompletionData("()"));
                    break;
                case AvailableMarblePythonCommands.@select:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    completionDatas.Add(new PythonParserCompletionData("description('')"));
                    completionDatas.Add(new PythonParserCompletionData("indexTree('')"));
                    completionDatas.Add(new PythonParserCompletionData("resourceId('')"));
                    completionDatas.Add(new PythonParserCompletionData("text('')"));
                    completionDatas.Add(new PythonParserCompletionData("long('')"));
                    break;
                case AvailableMarblePythonCommands.swipe:
                    completionDatas.Add(new PythonParserCompletionData("(( , ), ( , ))"));
                    break;
                case AvailableMarblePythonCommands.tryExpect:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    break;
                case AvailableMarblePythonCommands.capture:
                    completionDatas.Add(new PythonParserCompletionData("()"));
                    break;
                case AvailableMarblePythonCommands.delay:
                    completionDatas.Add(new PythonParserCompletionData("()"));
                    break;
                case AvailableMarblePythonCommands.deviceInfo:
                    completionDatas.Add(new PythonParserCompletionData("()"));
                    break;
                case AvailableMarblePythonCommands.fail:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    break;
                case AvailableMarblePythonCommands.file:
                    // Properties:
                    completionDatas.Add(new PythonParserCompletionData("externalStorage"));
                    completionDatas.Add(new PythonParserCompletionData("temp"));

                    // Commands:
                    completionDatas.Add(new PythonParserCompletionData("cat()"));
                    completionDatas.Add(new PythonParserCompletionData("copy()"));
                    completionDatas.Add(new PythonParserCompletionData("createDirectory()"));
                    completionDatas.Add(new PythonParserCompletionData("createFile()"));
                    completionDatas.Add(new PythonParserCompletionData("getDate()"));
                    completionDatas.Add(new PythonParserCompletionData("fileExists()"));
                    completionDatas.Add(new PythonParserCompletionData("getAttributes()"));
                    completionDatas.Add(new PythonParserCompletionData("getFolderContent()"));
                    completionDatas.Add(new PythonParserCompletionData("move()"));
                    completionDatas.Add(new PythonParserCompletionData("readFile()"));
                    completionDatas.Add(new PythonParserCompletionData("removeFile()"));
                    completionDatas.Add(new PythonParserCompletionData("removeFolder()"));
                    completionDatas.Add(new PythonParserCompletionData("removeItem()"));
                    completionDatas.Add(new PythonParserCompletionData("removeItems()"));
                    completionDatas.Add(new PythonParserCompletionData("setAttributes()"));
                    completionDatas.Add(new PythonParserCompletionData("getFileSize()"));
                    completionDatas.Add(new PythonParserCompletionData("type()"));
                    completionDatas.Add(new PythonParserCompletionData("write()"));
                    break;
                case AvailableMarblePythonCommands.media:
                    completionDatas.Add(new PythonParserCompletionData("launchWebUrl('')"));
                    completionDatas.Add(new PythonParserCompletionData("playAudio('')"));
                    completionDatas.Add(new PythonParserCompletionData("playVideo('')"));
                    completionDatas.Add(new PythonParserCompletionData("playWithMusicPlayer('')"));
                    completionDatas.Add(new PythonParserCompletionData("showImage('')"));
                    break;
                case AvailableMarblePythonCommands.orientation:
                    completionDatas.Add(new PythonParserCompletionData("get()"));
                    completionDatas.Add(new PythonParserCompletionData("setLandscape()"));
                    completionDatas.Add(new PythonParserCompletionData("setPortrait()"));
                    break;
                case AvailableMarblePythonCommands.packages:
                    //#Installation, which by default re-installs the package if it already exists.
                    completionDatas.Add(new PythonParserCompletionData("installPackage(r'')"));

                    //#Installation, which does not re-install the package if it already exists.
                    completionDatas.Add(new PythonParserCompletionData("installPackage(r'', reinstall=False)"));

                    //#Installation from remote location: i.e. apk file have been already copied to the device, but not yet installed. 
                    //#By default re-installs the package if it already exists.
                    completionDatas.Add(new PythonParserCompletionData("installRemotePackage('')"));

                    //#Installation from remote location, which does not re-install the package if it already exists
                    completionDatas.Add(new PythonParserCompletionData("installRemotePackage('', reinstall=False)"));

                    //#By using package name, uninstalls a package from the device.
                    completionDatas.Add(new PythonParserCompletionData("uninstallPackage('')"));

                    //#Lists the installed packages from the device.
                    completionDatas.Add(new PythonParserCompletionData("listPackages()"));
                    //for apk in packagesDict.Keys :
                    //    self.comment('apk: %s; package: %s' % (apk, packagesDict[apk]))

                    //#By using apk file name (without directory name), checks if the apk is installed on the device.
                    completionDatas.Add(new PythonParserCompletionData("apkExists('')"));

                    //#By using apk file name (without directory name), finds the package info (apk location and package name).
                    //#Returns tuple with None values, if not found.
                    completionDatas.Add(new PythonParserCompletionData("findPackageByFileName('')"));

                    //#By using package name, finds the apk location from the device.
                    //#Returns None, if not found.
                    completionDatas.Add(new PythonParserCompletionData("findApkPath('')"));

                    //#By using package name, checks if the package exists on the device.
                    completionDatas.Add(new PythonParserCompletionData("packageExists('')"));
                    break;
                case AvailableMarblePythonCommands.reboot:
                    completionDatas.Add(new PythonParserCompletionData("()"));
                    break;
                case AvailableMarblePythonCommands.settings:
                    break;
                case AvailableMarblePythonCommands.time:
                    completionDatas.Add(new PythonParserCompletionData("getSystemDateTime()"));
                    completionDatas.Add(new PythonParserCompletionData("setSystemDate()"));
                    completionDatas.Add(new PythonParserCompletionData("setSystemDateTime()"));
                    completionDatas.Add(new PythonParserCompletionData("setSystemTime()"));
                    completionDatas.Add(new PythonParserCompletionData("synchPcDateTime()"));
                    break;
                case AvailableMarblePythonCommands.volume:
                    completionDatas.Add(new PythonParserCompletionData("down()"));
                    completionDatas.Add(new PythonParserCompletionData("up()"));
                    completionDatas.Add(new PythonParserCompletionData("getMedia()"));
                    completionDatas.Add(new PythonParserCompletionData("getRinger()"));
                    completionDatas.Add(new PythonParserCompletionData("setMedia()"));
                    completionDatas.Add(new PythonParserCompletionData("setRinger()"));
                    break;
                case AvailableMarblePythonCommands.toggle:
                    completionDatas.Add(new PythonParserCompletionData("()"));
                    completionDatas.Add(new PythonParserCompletionData("get('')"));
                    completionDatas.Add(new PythonParserCompletionData("set('')"));
                    break;
                case AvailableMarblePythonCommands.addLogMarker:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    break;
                case AvailableMarblePythonCommands.device:
                    break;
                case AvailableMarblePythonCommands.shell:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    break;
                case AvailableMarblePythonCommands.sql:
                    break;
                case AvailableMarblePythonCommands.waitForEvent:
                    completionDatas.Add(new PythonParserCompletionData("('')"));
                    break;
                case AvailableMarblePythonCommands.blackBox:
                    ////completionDatas.AddRange(PythonScriptCommands.GetParserCompletionDataList(AvailableMarblePythonCommands.blackBoxEnabled));
                    ////completionDatas.AddRange(PythonScriptCommands.GetParserCompletionDataList(AvailableMarblePythonCommands.connectUsb));
                    ////completionDatas.AddRange(PythonScriptCommands.GetParserCompletionDataList(AvailableMarblePythonCommands.connectSim));
                    ////completionDatas.AddRange(PythonScriptCommands.GetParserCompletionDataList(AvailableMarblePythonCommands.connectMemoryCard));
                    ////completionDatas.AddRange(PythonScriptCommands.GetParserCompletionDataList(AvailableMarblePythonCommands.connectAvPlug));
                    ////completionDatas.AddRange(PythonScriptCommands.GetParserCompletionDataList(AvailableMarblePythonCommands.executeHwOperation));

                    completionDatas.Add(new PythonParserCompletionData("blackBoxEnabled"));
                    completionDatas.Add(new PythonParserCompletionData("connectUsb"));
                    completionDatas.Add(new PythonParserCompletionData("connectSim"));
                    completionDatas.Add(new PythonParserCompletionData("connectMemoryCard"));
                    completionDatas.Add(new PythonParserCompletionData("connectAvPlug"));
                    completionDatas.Add(new PythonParserCompletionData("executeHwOperation"));
                    break;
                case AvailableMarblePythonCommands.blackBoxEnabled:
                    break;
                ////case AvailableMarblePythonCommands.connectUsb:
                ////    completionDatas.Add(new PythonParserCompletionData("('')"));
                ////    break;
                ////case AvailableMarblePythonCommands.connectSim:
                ////    completionDatas.Add(new PythonParserCompletionData("('')"));
                ////    break;
                ////case AvailableMarblePythonCommands.connectMemoryCard:
                ////    completionDatas.Add(new PythonParserCompletionData("('')"));
                ////    break;
                ////case AvailableMarblePythonCommands.connectAvPlug:
                ////    completionDatas.Add(new PythonParserCompletionData("('')"));
                ////    break;
                ////case AvailableMarblePythonCommands.executeHwOperation:
                ////    completionDatas.Add(new PythonParserCompletionData("('')"));
                ////    break;
                default:
                    throw new ArgumentOutOfRangeException("command");
            }

            return completionDatas;
        }

        ////private static List<PythonParserCompletionData> getParserCompletionDataListForSelf()
        ////{
        ////    List<PythonParserCompletionData> completionDatas = new List<PythonParserCompletionData>();

        ////    foreach (var availableMarblePythonCommand in (AvailableMarblePythonCommands[]) Enum.GetValues(typeof(AvailableMarblePythonCommands)))
        ////    {
        ////        if (availableMarblePythonCommand == AvailableMarblePythonCommands.self) continue;

        ////        //completionDatas.AddRange(PythonScriptCommands.GetParserCompletionDataList(availableMarblePythonCommand));
        ////        completionDatas.Add(new PythonParserCompletionData(availableMarblePythonCommand.ToString()));
        ////    }

        ////    return completionDatas.Sort();
        ////}

        private static List<PythonParserCompletionData> getParserCompletionDataListForSelf()
        {
            List<PythonParserCompletionData> completionDatas =
                (from availableMarblePythonCommand in (AvailableMarblePythonCommands[])Enum.GetValues(typeof(AvailableMarblePythonCommands))
                 where availableMarblePythonCommand != AvailableMarblePythonCommands.self
                 orderby availableMarblePythonCommand.ToString()
                 select new PythonParserCompletionData(availableMarblePythonCommand.ToString())).ToList();

            return completionDatas;
        }

        public static List<PythonParserCompletionData> GetParserCompletionDataListForSelf()
        {
            List<PythonParserCompletionData> completionDatas =
                (from availableMarblePythonCommand in (AvailableMarblePythonCommands[])Enum.GetValues(typeof(AvailableMarblePythonCommands))
                 where availableMarblePythonCommand != AvailableMarblePythonCommands.self
                 orderby availableMarblePythonCommand.ToString()
                 select GetDefaultParserCompletionDataAfterSelf(availableMarblePythonCommand)).ToList();

            return completionDatas;
        }
    }
}
