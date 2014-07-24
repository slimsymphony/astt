
import clr;

class Connection(object) :
    DisplayName = 'connection'
    Description = 'Connection type (USB, FBUS etc.)'
    DefaultValue = ''

class PmdFilePath(object) :
    DisplayName = 'pmd-file path'
    Description = 'Pmd-file is required for translation and interpretation of the trace logs.'
    DefaultValue = '..\\phone_packages\\rm766__rdRDourbu006.mcusw.pmd'

class TraceConnection(object) :
    DisplayName = 'trace connection'
    Description = 'Trace connection; If defined, trace log will be taken from main phone during test run'
    DefaultValue = ''

class AccountPhoneNumber(object) :
    DisplayName = 'phone number'
    Category = 'Account'
    Description = 'Phone number (in format 045123456 or +35845123456)'
    DefaultValue = ''

class AccountPinCode(object) :
    DisplayName = 'pin code'
    Category = 'Account'
    DefaultValue = ''

class AccountPin2Code(object) :
    DisplayName = 'pin2 code'
    Category = 'Account'
    DefaultValue = ''

class AccountPuk1Code(object) :
    DisplayName = 'puk1 code'
    Category = 'Account'
    DefaultValue = ''

class AccountPuk2Code(object) :
    DisplayName = 'puk2 code'
    Category = 'Account'
    DefaultValue = ''

class AccountServiceNumber(object) :
    DisplayName = 'service number'
    Category = 'Account'
    DefaultValue = ''

class AccountVoiceMailNumber(object) :
    DisplayName = 'voice mail number'
    Category = 'Account'
    DefaultValue = ''

class Account2PhoneNumber(object) :
    DisplayName = 'phone number'
    Category = 'Account2'
    Description = 'Phone number (in format 045123456 or +35845123456)'
    DefaultValue = ''

class Account2PinCode(object) :
    DisplayName = 'pin code'
    Category = 'Account2'
    DefaultValue = ''

class Account2Pin2Code(object) :
    DisplayName = 'pin2 code'
    Category = 'Account2'
    DefaultValue = ''

class Account2Puk1Code(object) :
    DisplayName = 'puk1 code'
    Category = 'Account2'
    DefaultValue = ''

class Account2Puk2Code(object) :
    DisplayName = 'puk2 code'
    Category = 'Account2'
    DefaultValue = ''

class Account2ServiceNumber(object) :
    DisplayName = 'service number'
    Category = 'Account2'
    DefaultValue = ''

class Account2VoiceMailNumber(object) :
    DisplayName = 'voice mail number'
    Category = 'Account2'
    DefaultValue = ''

# CorVA Audio detection settings

class CorVAEnabled(object) :
    DisplayName = 'CorVAEnabled'
    Category = 'CorVA'
    Description = 'Audio HW connected'
    DefaultValue = ''

class CorVAEnabled(object) :
    DisplayName = 'CorVAEnabled'
    Category = 'CorVA'
    Description = 'Audio HW connected'
    DefaultValue = True

class Earpiece(object) :
    DisplayName = 'Earpiece'
    Category = 'CorVA'
    Description = 'Earpiece recording device'
    DefaultValue = 'MOTU Analog 5'

class Loudspeaker(object) :
    DisplayName = 'Loudspeaker'
    Category = 'CorVA'
    Description = 'Loudspeaker recording device'
    DefaultValue = 'MOTU Analog 3'

class Headset(object) :
    DisplayName = 'Headset'
    Category = 'CorVA'
    Description = 'Headset recording device'
    DefaultValue = 'MOTU Analog 1'

class HeadsetInput(object) :
    DisplayName = 'HeadsetInput'
    Category = 'CorVA'
    Description = 'Headset input audio player device'
    DefaultValue = 'MOTU Analog 3'

class FMTX(object) :
    DisplayName = 'FMTX'
    Category = 'CorVA'
    Description = 'FM Transmitting audio player device'
    DefaultValue = 'MOTU Analog 1'

class MaxRecordTime(object) :
    DisplayName = 'MaxRecordTime'
    Category = 'CorVA'
    Description = 'Maximum recording time'
    DefaultValue = 120

class ReferenceAudioPath(object) :
    DisplayName = 'ReferenceAudioPath'
    Category = 'CorVA'
    Description = 'Reference audio location'
    DefaultValue = '../reference_files/audio'

class AudioTestDataFolder(object) :
    DisplayName = 'AudioTestDataFolder'
    Category = 'CorVA'
    Description = 'Test data audio location'
    DefaultValue = '../test_content'

class Mode(object) :
    DisplayName = 'Mode'
    Category = 'CorVA'
    Description = 'Default detection mode'
    DefaultValue = 3

class Framesize(object) :
    DisplayName = 'Framesize'
    Category = 'CorVA'
    Description = 'Default frame size'
    DefaultValue = 4000

class Threshold(object) :
    DisplayName = 'Threshold'
    Category = 'CorVA'
    Description = 'Default threshold'
    DefaultValue = 10

class NoiseLevel(object) :
    DisplayName = 'Noiselevel'
    Category = 'CorVA'
    Description = 'Default noise level'
    DefaultValue = 0.01

class StartChannel(object) :
    DisplayName = 'StartChannel'
    Category = 'CorVA'
    Description = 'Default start channel'
    DefaultValue = 1

class DefaultAudioRecordingTime(object) :
    DisplayName = 'DefaultAudioRecordingTime'
    Category = 'CorVA'
    Description = 'Default recording time'
    DefaultValue = 10

class DefaultCorVAActionOnFail(object) :
    DisplayName = 'DefaultActionOnFail'
    Category = 'CorVA'
    Description = 'Fail mode'
    DefaultValue = 'Fail case'

class SavePassedRecordings(object) :
    DisplayName = 'SavePassedRecordings'
    Category = 'CorVA'
    Description = 'Save passed recordings'
    DefaultValue = False

class AccessoryBoxConnected(object) :
    DisplayName = 'AccessoryBoxConnected'
    Category = 'CorVA'
    Description = 'Accessory box in use'
    DefaultValue = False

# M3W Test API settings

class LibrarySearchPath(object) :
    DisplayName = 'LibrarySearchPath'
    Category = 'M3W'
    Description = 'Library search path'
    DefaultValue = 'Z:\\s40ng\\s40_sw\\test_tools\\s40_tdk\\tmp'

class TestDataPathPC(object) :
    DisplayName = 'TestDataPathPC'
    Category = 'M3W'
    Description = 'Test data path on PC'
    DefaultValue = 'C:\\marble_103\\test_data'

class TestDataPathPhone(object) :
    DisplayName = 'TestDataPathPhone'
    Category = 'M3W'
    Description = 'Test data path on phone'
    DefaultValue = 'e:\\test_data'

class BaseDirectoryInPhone(object) :
    DisplayName = 'BaseDirectoryInPhone'
    Category = 'M3W'
    Description = 'Default folder for wrapper and libraries in the device under test'
    DefaultValue = 'c:\\predefdynsw'

class DefaultM3WActionOnFail(object) :
    DisplayName = 'DefaultActionOnFail'
    Category = 'M3W'
    Description = 'Fail mode'
    DefaultValue = 'Fail case'

class DefaultOutput(object) :
    DisplayName = 'DefaultOutput'
    Category = 'M3W'
    Description = 'Default audio output routing'
    DefaultValue = 'Accessory'

class DefaultVolume(object) :
    DisplayName = 'DefaultVolume'
    Category = 'M3W'
    Description = 'Default audio output volume'
    DefaultValue = 150

class UnloadLibrariesAfterTC(object) :
    DisplayName = 'UnloadLibrariesAfterTC'
    Category = 'M3W'
    Description = 'Developer mode (always unload libraries)'
    DefaultValue = False
