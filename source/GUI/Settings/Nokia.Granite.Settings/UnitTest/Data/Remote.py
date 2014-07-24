
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

class PhoneNumber(object) :
    DisplayName = 'phone number'
    Category = 'Account'
    Description = 'Phone number (in format 045123456 or +35845123456)'
    DefaultValue = ''

class PhoneNumber2(object) :
    DisplayName = 'phone number'
    Category = 'Account2'
    Description = 'Phone number (in format 045123456 or +35845123456)'
    DefaultValue = ''

