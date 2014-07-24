
import clr;

clr.AddReference('System.Drawing')
clr.AddReference('System.Design')
clr.AddReference('System.Windows.Forms')

from System.Drawing.Design import UITypeEditor
from System.Drawing.Design import UITypeEditorEditStyle
from System.ComponentModel import ITypeDescriptorContext, TypeConverter, StringConverter
from System.Windows.Forms.Design import IWindowsFormsEditorService
from System import IServiceProvider, Object, Array, String
from System.Collections.Generic import List
    
class CustomEditor(UITypeEditor) :
           
    def GetEditStyle(self, context) :

        return UITypeEditorEditStyle.DropDown
    
    def EditValue(self, context, provider, value) :

        service = provider.GetService(clr.GetClrType(IWindowsFormsEditorService))

        if service != None :
            from System.Windows.Forms import Form, TextBox, FormBorderStyle, DockStyle, DialogResult
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

class CustomConverter(StringConverter) :
    
    def GetStandardValues(self, context) :
        from System import String, Array
        return TypeConverter.StandardValuesCollection(Array[String](['X-files', 'Logs', 'X-files and logs']))
    
    def GetStandardValuesSupported(self, context) :
        return True

class SIM1(object) :
    d = dict()
    d.Add("hep", 10)
    DefaultValue = { "PIN1" : 2362352, "PIN2" : -7364746734621332323232434, "PUK2" : 236332636}

class SmsText(object) :
    DisplayName = 'SMS Text'
    Description = 'Sms to be sent to reference device'
    Category = '01. SMS Settings'
    DefaultValue = 'This is a Nokia test message from Marble'
    Editor = CustomEditor()

class SocketPort(object) :
    Category = '02. Socket'
    DefaultValue = 80

class PhoneNumber(object) :
    Category = "Phone"
    DefaultValue = "+3580505050945945849"

class SocketAddress(object) :
    Category = '02. Socket'
    DefaultValue = 'localhost'

class ResetDectionMethod(object) :
    DisplayName = 'Reset dection Method'
    Description = 'Method how to hunt down a reset after each test case execution'
    Category = '03. Common - Debugging'
    DefaultValue = 'X-files'
    Converter = CustomConverter()
    
class NonDecoratedSetting(object) :
    DefaultValue = 100
    Save = False #Won't be deserialized

class DuplicateSettingName(object) :
    DefaultValue = 'Value with same name exists also in other setting file'
    Editor = CustomEditor()
    Save = False

class PythonList(object) :
    a = list()
    a.append("Python")
    a.append("list")
    a.append("is")
    a.append("supported")
    DefaultValue = a

class PythonTuple(object) :

    DefaultValue = "Python", "tuple", "is", "supported", "but", "converted", "to", "list", "because", "tuple", "is", "not", "serializable"

class SettingList(object) :
    
    DefaultValue = List[object](Array[object](["List", "is", "supported"]))

class SomeArray(object) :
    
    DefaultValue = Array[str](["Array", "is", "supported", "but", "also", "converted", "to", "list"])
    
class Clock(object) :
    
    from System import DateTime
    
    DefaultValue = DateTime.Now