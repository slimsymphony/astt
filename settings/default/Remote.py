
import clr;

# connection settings

class Connection(object) :
    DisplayName = 'connection'
    Description = 'Fuse connection identifier for the remote phone.'
    DefaultValue = ''
    ReadOnlyForUser = True

class PmdFilePath(object) :
    DisplayName = 'pmd-file path'
    Description = 'Pmd-file is required for translation and interpretation of the trace logs.'
    DefaultValue = '..\phone_packages\local.pmd'
    ReadOnlyForUser = False

class TraceConnection(object) :
    DisplayName = 'trace connection'
    Description = 'Trace connection; If defined, trace log will be taken from main phone during test run'
    DefaultValue = ''
    ReadOnlyForUser = True
    
class BluetoothName(object) :
    DisplayName = 'bluetooth name'
    Category = 'Phone'
    Description = 'Bluetooth name\nAccess path: Remote.BluetoothName'
    DefaultValue = ''
    
class WLANName(object) :
    DisplayName = 'WLAN name'
    Category = 'WLAN'
    Description = 'If Remote needs to use different WLAN network than Main, use this setting (Name of the WLAN network).\nAccess path: Remote.WLANName'
    DefaultValue = ''
    
class WLANPassword(object) :
    DisplayName = 'WLAN password'
    Category = 'WLAN'
    DefaultValue = ''
    Description = 'If Remote needs to use different WLAN network than Main, use this setting (Password of the WLAN network).\nAccess path: Remote.WLANPassword'

# SIM1 settings

class SIM1PhoneNumber(object) :
    DisplayName = 'phone number'
    Category = 'SIM1'
    Description = 'Phone number (in format 045123456 or +35845123456)\nAccess path: Remote.SIM1PhoneNumber'
    DefaultValue = ''

class SIM1PinCode(object) :
    DisplayName = 'pin code'
    Category = 'SIM1'
    Description = 'Access path: Remote.SIM1PinCode'
    DefaultValue = ''

class SIM1Pin2Code(object) :
    DisplayName = 'pin2 code'
    Category = 'SIM1'
    Description = 'Access path: Remote.SIM1Pin2Code'
    DefaultValue = ''

class SIM1Puk1Code(object) :
    DisplayName = 'puk1 code'
    Category = 'SIM1'
    Description = 'Access path: Remote.SIM1Puk1Code'
    DefaultValue = ''

class SIM1Puk2Code(object) :
    DisplayName = 'puk2 code'
    Category = 'SIM1'
    Description = 'Access path: Remote.SIM1Puk2Code'
    DefaultValue = ''

class SIM1ServiceNumber(object) :
    DisplayName = 'service number'
    Category = 'SIM1'
    Description = 'Access path: Remote.SIM1ServiceNumber'
    DefaultValue = ''

class SIM1VoiceMailNumber(object) :
    DisplayName = 'voice mail number'
    Category = 'SIM1'
    Description = 'Access path: Remote.SIM1VoiceMailNumber'
    DefaultValue = ''

# SIM2 settings

class SIM2PhoneNumber(object) :
    DisplayName = 'phone number'
    Category = 'SIM2'
    Description = 'Phone number (in format 045123456 or +35845123456)\nAccess path: Remote.SIM2PhoneNumber'
    DefaultValue = ''

class SIM2PinCode(object) :
    DisplayName = 'pin code'
    Category = 'SIM2'
    Description = 'Access path: Remote.SIM2PinCode'
    DefaultValue = ''

class SIM2Pin2Code(object) :
    DisplayName = 'pin2 code'
    Category = 'SIM2'
    Description = 'Access path: Remote.SIM2Pin2Code'
    DefaultValue = ''

class SIM2Puk1Code(object) :
    DisplayName = 'puk1 code'
    Category = 'SIM2'
    Description = 'Access path: Remote.SIM2Puk1Code'
    DefaultValue = ''

class SIM2Puk2Code(object) :
    DisplayName = 'puk2 code'
    Category = 'SIM2'
    Description = 'Access path: Remote.SIM2Puk2Code'
    DefaultValue = ''

class SIM2ServiceNumber(object) :
    DisplayName = 'service number'
    Category = 'SIM2'
    Description = 'Access path: Remote.SIM2ServiceNumber'
    DefaultValue = ''

class SIM2VoiceMailNumber(object) :
    DisplayName = 'voice mail number'
    Category = 'SIM2'
    Description = 'Access path: Remote.SIM2VoiceMailNumber'
    DefaultValue = ''
