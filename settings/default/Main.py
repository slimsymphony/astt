import clr;
from System import Array, String
from System.ComponentModel import TypeConverter, StringConverter


# Connection settings
class Connection(object) :
    DisplayName = 'connection'
    Category = 'Connection'
    Description = 'Serial number of the main phone.'
    DefaultValue = ''
    ReadOnlyForUser = True

class TraceConnection(object) :
    DisplayName = 'trace connection'
    Category = 'Connection'
    Description = 'Trace connection; If defined, trace log will be taken from main phone during test run'
    DefaultValue = ''
    ReadOnlyForUser = True

# Phone settings

class SecurityCode(object) :
    DisplayName = 'security code'
    Category = 'Phone'
    Description = 'Security code of the phone\nAccess path: Main.SecurityCode'
    DefaultValue = ''
    
class BluetoothName(object) :
    DisplayName = 'bluetooth name'
    Category = 'Phone'
    Description = 'Bluetooth name\nAccess path: Main.BluetoothName'
    DefaultValue = ''
    
class WLANName(object) :
    DisplayName = '1st WLAN name'
    Category = 'WLAN'
    Description = 'WLAN SSID name\nAccess path: Main.WLANName'
    DefaultValue = ''
    
class WLANPassword(object) :
    DisplayName = '1st WLAN password'
    Category = 'WLAN'
    DefaultValue = ''
    Description = 'Password for the WLAN network\nAccess path: Main.WLANPassword'
    
class WLANName2(object) :
    DisplayName = '2nd WLAN name'
    Category = 'WLAN'
    Description = 'Second WLAN SSID name\nAccess path: Main.WLANName2'
    DefaultValue = ''
    
class WLANPassword2(object) :
    DisplayName = '2nd WLAN password'
    Category = 'WLAN'
    DefaultValue = ''
    Description = 'Password for the second WLAN network\nAccess path: Main.WLANPassword2'
    
# SIM1 settings

class SIM1PhoneNumber(object) :
    DisplayName = 'phone number'
    Category = 'SIM1'
    Description = 'Phone number (in format 045123456 or +35845123456)\nAccess path: Main.SIM1PhoneNumber'
    DefaultValue = ''

class SIM1PinCode(object) :
    DisplayName = 'pin code'
    Category = 'SIM1'
    Description = 'Access path: Main.SIM1PinCode'
    DefaultValue = ''

class SIM1Pin2Code(object) :
    DisplayName = 'pin2 code'
    Category = 'SIM1'
    Description = 'Access path: Main.SIM1Pin2Code'
    DefaultValue = ''

class SIM1Puk1Code(object) :
    DisplayName = 'puk1 code'
    Category = 'SIM1'
    Description = 'Access path: Main.SIM1Puk1Code'
    DefaultValue = ''

class SIM1Puk2Code(object) :
    DisplayName = 'puk2 code'
    Category = 'SIM1'
    Description = 'Access path: Main.SIM1Puk2Code'
    DefaultValue = ''

class SIM1ServiceNumber(object) :
    DisplayName = 'service number'
    Category = 'SIM1'
    Description = 'Access path: Main.SIM1ServiceNumber'
    DefaultValue = ''

class SIM1VoiceMailNumber(object) :
    DisplayName = 'voice mail number'
    Category = 'SIM1'
    Description = 'Access path: Main.SIM1VoiceMailNumber'
    DefaultValue = ''

# SIM2 settings

class SIM2PhoneNumber(object) :
    DisplayName = 'phone number'
    Category = 'SIM2'
    Description = 'Phone number (in format 045123456 or +35845123456)\nAccess path: Main.SIM2PhoneNumber'
    DefaultValue = ''

class SIM2PinCode(object) :
    DisplayName = 'pin code'
    Category = 'SIM2'
    Description = 'Access path: Main.SIM2PinCode'
    DefaultValue = ''

class SIM2Pin2Code(object) :
    DisplayName = 'pin2 code'
    Category = 'SIM2'
    Description = 'Access path: Main.SIM2Pin2Code'
    DefaultValue = ''

class SIM2Puk1Code(object) :
    DisplayName = 'puk1 code'
    Category = 'SIM2'
    Description = 'Access path: Main.SIM2Puk1Code'
    DefaultValue = ''

class SIM2Puk2Code(object) :
    DisplayName = 'puk2 code'
    Category = 'SIM2'
    Description = 'Access path: Main.SIM2Puk2Code'
    DefaultValue = ''

class SIM2ServiceNumber(object) :
    DisplayName = 'service number'
    Category = 'SIM2'
    Description = 'Access path: Main.SIM2ServiceNumber'
    DefaultValue = ''

class SIM2VoiceMailNumber(object) :
    DisplayName = 'voice mail number'
    Category = 'SIM2'
    Description = 'Access path: Main.SIM2VoiceMailNumber'
    DefaultValue = ''
