
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

class NokiaAccountUsername(object) :
    DisplayName = 'Nokia account username'
    Category = 'Account settings'
    DefaultValue = ''

class NokiaAccountPassword(object) :
    DisplayName = 'Nokia account password'
    Category = 'Account settings'
    DefaultValue = ''

class FacebookAccountUsername(object) :
    DisplayName = 'Facebook account username'
    Category = 'Account settings'
    DefaultValue = ''

class FacebookAccountPassword(object) :
    DisplayName = 'Facebook account password'
    Category = 'Account settings'
    DefaultValue = ''

class GoogleAccountUsername(object) :
    DisplayName = 'Google account username'
    Category = 'Account settings'
    DefaultValue = ''

class GoogleAccountPassword(object) :
    DisplayName = 'Google account password'
    Category = 'Account settings'
    DefaultValue = ''

class NokiaEmailAccountUsername(object) :
    DisplayName = 'Nokia email account username'
    Category = 'Account settings'
    DefaultValue = ''

class NokiaEmailAccountPassword(object) :
    DisplayName = 'Nokia email account password'
    Category = 'Account settings'
    DefaultValue = ''

class OtherEmailAccountUsername(object) :
    DisplayName = 'Other email account username'
    Category = 'Account settings'
    DefaultValue = ''

class OtherEmailAccountPassword(object) :
    DisplayName = 'Nokia email account password'
    Category = 'Account settings'
    DefaultValue = ''

class MainPhoneNumber(object) :
    DisplayName = 'Phone number'
    Category = 'Main phone settings'
    Description = 'Phone number (in format 045123456 or +35845123456)'
    DefaultValue = ''

class CorVAEnabled(object) :
    DisplayName = 'Audio HW connected'
    Category = 'Main phone settings.Audio detection settings'
    DefaultValue = True

class Earpiece(object) :
    DisplayName = 'Earpiece recording device'
    Category = 'Main phone settings.Audio detection settings'
    DefaultValue = 'MOTU Analog 5'

class RemotePhoneNumber(object) :
    DisplayName = 'Phone number'
    Category = 'Remote phone settings'
    Description = 'Phone number (in format 045123456 or +35845123456)'
    DefaultValue = ''

class PhoneReset(object) :
    DisplayName = 'Phone reset'
    Category = 'System settings'
    Description = "Phone's reset timeout in seconds. Default = 30."
    DefaultValue = 30

class SendAndReceiveMessage(object) :
    DisplayName = 'Send and receive message'
    Category = 'System settings'
    Description = "Send and receive message timeout in milliseconds. Default = 5000."
    DefaultValue = 5000

class ReceiveMessagesFrom(object) :
    DisplayName = 'Receive message from'
    Category = 'System settings'
    Description = "Receive message from timeout in milliseconds. Default = 5000."
    DefaultValue = 5000

class DictionarySetting(object) :
    DefaultValue = { "Root" : 
                        { "Child" : 
                            { "EmptyChild" : '' }
                         } 
                    }
