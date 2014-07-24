
import clr;

clr.AddReference('System.Drawing')
clr.AddReference('System.Design')
clr.AddReference('System.Windows.Forms')

from System import Environment
from System.Drawing.Design import UITypeEditor, UITypeEditorEditStyle
from System.Windows.Forms import OpenFileDialog, DialogResult

#class DebugLevelConverter(StringConverter) :
#    
#    def GetStandardValues(self, context) :
#        from System import Int32, Array
#        return TypeConverter.StandardValuesCollection(Array[Int32]([1, 2, 3, 4]))
#    
#    def GetStandardValuesSupported(self, context) :
#        return True

class XmlFileNameEditor(UITypeEditor) :
           
    def GetEditStyle(self, context) :

        return UITypeEditorEditStyle.Modal
    
    def EditValue(self, context, provider, value) :

        dialog = OpenFileDialog()
        dialog.Filter = "XML files (*.xml)|*.xml|All files (*.*)|*.*"
        dialog.InitialDirectory = Environment.SpecialFolder.Recent.ToString();
        
        if dialog.ShowDialog() == DialogResult.OK :
            value = dialog.FileName
        
        dialog.Dispose()
        
        return value

class DebugLevel(object) :
    DisplayName = 'debug level'
    Description = "Select how much debug info you want to get to main/remote console. 1 = lowest, 4 = highest"
    DefaultValue = 2
    #Converter = DebugLevelConverter()

class EnableBlackBox(object) :
    DisplayName = 'enable blackbox'
    Description = "Setting for enabling or disabling blackbox"
    DefaultValue = False

class EnableGrayBox(object) :
    DisplayName = 'enable graybox'
    Description = "Setting for enabling whitebox touch and key simulation in blackbox mode"
    DefaultValue = False

class DisableTestCaseSetupAndTeardown(object) :
    DisplayName = 'disable test case setup and teardown'
    Description = "Setting for enabling or disabling test case setup and teardown. If enabled, test cases will give warning and No result will be given"
    DefaultValue = False

class EnableMonkeyTesting(object) :
    DisplayName = 'enable monkey testing'
    Description = "Disable certain framework features for monkey testing"
    DefaultValue = False

class TracingEnabled(object) :
    DisplayName = 'tracing enabled'
    Description = "Setting for enabling or disabling tracing"
    DefaultValue = False

class MemoryLeakTestingEnabled(object) :
    DisplayName = 'memory leak testing enabled'
    Description = "Setting for enabling or disabling memory leak analysis"
    DefaultValue = False

class DeleteSuccessBlx(object) :
    DisplayName = 'delete success blx'
    Description = "enable deletion of successful testcase result blx"
    DefaultValue = False

class TraceXmlFilePath(object) :
    DisplayName = 'trace xml-file path'
    Description = "Xml-file for enabling phone traces"
    DefaultValue = ''
    Editor = XmlFileNameEditor()
