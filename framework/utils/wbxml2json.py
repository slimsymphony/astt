#!/usr/bin/python

r'''Converter WBXML format cc file into JSON string aligned with ConnSet module.

    Alternatively, the program can be invoked from command line with either two
    arguments (the input and output paths) or just one (output is written to
    standard output).

    This file should keep the same with bootstrap.sx about 'OMA CP -> DM DDF'

    Usage introduction:
    1. Output json string directly
    >python wbxml2json.py cc.wbxml
    >{"PROVIDER-NAME":"Nokia","Name":"cc","Attribute":7,"OriginId":"fac"}

    2. Output refer json string directly
    >python wbxml2json.py -r cc.wbxml
    >{\"PROVIDER-NAME\":\"Nokia\",\"Name\":\"cc\",\"Attribute\":7,\"OriginId\":\"fac\"}

    3. Write json string into specific file
    >python wbxml2json.py cc.wbxml cc.json

    4. Write refer json string into specific file
    >python wbxml2json.py -r cc.wbxml cc.json
'''

__version__ = '1.2'

from base64    import b64encode
from sys       import stdout
from traceback import print_exc
import collections
import copy
# Output flag
FLAG_REF = False

# Key tokens
TOKEN_SWITCH_PAGE   = 0x00
TOKEN_END           = 0x01
TOKEN_STR_I         = 0x03
TOKEN_STR_T         = 0x83
TOKEN_OPAQUE        = 0xC3

TOKEN_TAG = [
    { # Page 0
        0x05:
        (
            'wap-provisioningdoc',
            {
                0x45: ('version', None),
                0x46: ('version', '1.0')
            }
        ),

        0x06:
        (
            'characteristic',
            {
                0x50: ('type', None),
                0x51: ('type', 'PXLOGICAL'),
                0x52: ('type', 'PXPHYSICAL'),
                0x53: ('type', 'PORT'),
                0x54: ('type', 'VALIDITY'),
                0x55: ('type', 'NAPDEF'),
                0x56: ('type', 'BOOTSTRAP'),
                0x57: ('type', 'VENDORCONFIG'),
                0x58: ('type', 'CLIENTIDENTITY'),
                0x59: ('type', 'PXAUTHINFO'),
                0x5A: ('type', 'NAPAUTHINFO'),
                0x5B: ('type', 'ACCESS')
            }
        ),

        0x07:
        (
            'parm',
            {
                0x05: ('name', None),
                0x06: ('value', lambda dummy:dummy),
                0x07: ('name', 'NAME'),
                0x08: ('name', 'NAP-ADDRESS'),
                0x09: ('name', 'NAP-ADDRTYPE'),
                0x0A: ('name', 'CALLTYPE'),
                0x0B: ('name', 'VALIDUNTIL'),
                0x0C: ('name', 'AUTHTYPE'),
                0x0D: ('name', 'AUTHNAME'),
                0x0E: ('name', 'AUTHSECRET'),
                0x0F: ('name', 'LINGER'),
                0x10: ('name', 'BEARER'),
                0x11: ('name', 'NAPID'),
                0x12: ('name', 'COUNTRY'),
                0x13: ('name', 'NETWORK'),
                0x14: ('name', 'INTERNET'),
                0x15: ('name', 'PROXY-ID'),
                0x16: ('name', 'PROXY-PROVIDER-ID'),
                0x17: ('name', 'DOMAIN'),
                0x18: ('name', 'PROVURL'),
                0x19: ('name', 'PXAUTH-TYPE'),
                0x1A: ('name', 'PXAUTH-ID'),
                0x1B: ('name', 'PXAUTH-PW'),
                0x1C: ('name', 'STARTPAGE'),
                0x1D: ('name', 'BASAUTH-ID'),
                0x1E: ('name', 'BASAUTH-PW'),
                0x1F: ('name', 'PUSHENABLED'),
                0x20: ('name', 'PXADDR'),
                0x21: ('name', 'PXADDRTYPE'),
                0x22: ('name', 'TO-NAPID'),
                0x23: ('name', 'PORTNBR'),
                0x24: ('name', 'SERVICE'),
                0x25: ('name', 'LINKSPEED'),
                0x26: ('name', 'DNLINKSPEED'),
                0x27: ('name', 'LOCAL-ADDR'),
                0x28: ('name', 'LOCAL-ADDRTYPE'),
                0x29: ('name', 'CONTEXT-ALLOW'),
                0x2A: ('name', 'TRUST'),
                0x2B: ('name', 'MASTER'),
                0x2C: ('name', 'SID'),
                0x2D: ('name', 'SOC'),
                0x2E: ('name', 'WSP-VERSION'),
                0x2F: ('name', 'PHYSICAL-PROXY-ID'),
                0x30: ('name', 'CLIENT-ID'),
                0x31: ('name', 'DELIVERY-ERR-SDU'),
                0x32: ('name', 'DELIVERY-ORDER'),
                0x33: ('name', 'TRAFFIC-CLASS'),
                0x34: ('name', 'MAX-SDU-SIZE'),
                0x35: ('name', 'MAX-BITRATE-UPLINK'),
                0x36: ('name', 'MAX-BITRATE-DNLINK'),
                0x37: ('name', 'RESIDUAL-BER'),
                0x38: ('name', 'SDU-ERROR-RATIO'),
                0x39: ('name', 'TRAFFIC-HANDL-PRIO'),
                0x3A: ('name', 'TRANSFER-DELAY'),
                0x3B: ('name', 'GUARANTEED-BITRATE-UPLINK'),
                0x3C: ('name', 'GUARANTEED-BITRATE-DNLINK'),
                0x3D: ('name', 'PXADDR-FQDN'),
                0x3E: ('name', 'PROXY-PW'),
                0x3F: ('name', 'PPGAUTH-TYPE'),
                0x47: ('name', 'PULLENABLED'),
                0x48: ('name', 'DNS-ADDR'),
                0x49: ('name', 'MAX-NUM-RETRY'),
                0x4A: ('name', 'FIRST-RETRY-TIMEOUT'),
                0x4B: ('name', 'REREG-THRESHOLD'),
                0x4C: ('name', 'T-BIT'),
                0x4E: ('name', 'AUTH-ENTITY'),
                0x4F: ('name', 'SPI'),
                0x70: ('name', 'IFNETWORKS')
            }
        )
    },

    { # Page 1
        0x06:
        (
            'characteristic',
            {
                0x50: ('type', None),
                0x53: ('type', 'PORT'),
                0x58: ('type', 'CLIENTIDENTITY'),
                0x55: ('type', 'APPLICATION'),
                0x56: ('type', 'APPADDR'),
                0x57: ('type', 'APPAUTH'),
                0x59: ('type', 'RESOURCE')
            }
        ),

        0x07:
        (
            'parm',
            {
                0x05: ('name', None),
                0x06: ('value', lambda dummy:dummy),
                0x07: ('name', 'NAME'),
                0x14: ('name', 'INTERNET'),
                0x1C: ('name', 'STARTPAGE'),
                0x22: ('name', 'TO-NAPID'),
                0x23: ('name', 'PORTNBR'),
                0x24: ('name', 'SERVICE'),
                0x2E: ('name', 'AACCEPT'),
                0x2F: ('name', 'AAUTHDATA'),
                0x30: ('name', 'AAUTHLEVEL'),
                0x31: ('name', 'AAUTHNAME'),
                0x32: ('name', 'AAUTHSECRET'),
                0x33: ('name', 'AAUTHTYPE'),
                0x34: ('name', 'ADDR'),
                0x35: ('name', 'ADDRTYPE'),
                0x36: ('name', 'APPID'),
                0x37: ('name', 'APROTOCOL'),
                0x38: ('name', 'PROVIDER-ID'),
                0x39: ('name', 'TO-PROXY'),
                0x3A: ('name', 'URI'),
                0x3B: ('name', 'RULE')
            }
        )
    }
]

TOKEN_VALUE = [
    { # Page 0
        # ADDRTYPE
        0x85: 'IPV4',
        0x86: 'IPV6',
        0x87: 'E164',
        0x88: 'ALPHA',
        0x89: 'APN',
        0x8A: 'SCODE',
        0x8B: 'TETRA-ITSI',
        0x8C: 'MAN',

        # CALLTYPE
        0x90: 'ANALOG-MODEM',
        0x91: 'V.120',
        0x92: 'V.110',
        0x93: 'X.31',
        0x94: 'BIT-TRANSPARENT',
        0x95: 'DIRECT-ASYNCHRONOUS-DATA-SERVICE',

        # AUTHTYPE/PXAUTH-TYPE/BEARER/LINKSPEED/SERVICE
        0x9A: 'PAP',
        0x9B: 'CHAP',
        0x9C: 'HTTP-BASIC',
        0x9D: 'HTTP-DIGEST',
        0x9E: 'WTLS-SS',
        0x9F: 'MD5',
        0xA2: 'GSM-USSD',
        0xA3: 'GSM-SMS',
        0xA4: 'ANSI-136-GUTS',
        0xA5: 'IS-95-CDMA-SMS',
        0xA6: 'IS-95-CDMA-CSD',
        0xA7: 'IS-95-CDMA-PACKET',
        0xA8: 'ANSI-136-CSD',
        0xA9: 'ANSI-136-GPRS',
        0xAA: 'GSM-CSD',
        0xAB: 'GSM-GPRS',
        0xAC: 'AMPS-CDPD',
        0xAD: 'PDC-CSD',
        0xAE: 'PDC-PACKET',
        0xAF: 'IDEN-SMS',
        0xB0: 'IDEN-CSD',
        0xB1: 'IDEN-PACKET',
        0xB2: 'FLEX/REFLEX',
        0xB3: 'PHS-SMS',
        0xB4: 'PHS-CSD',
        0xB5: 'TETRA-SDS',
        0xB6: 'TETRA-PACKET',
        0xB7: 'ANSI-136-GHOST',
        0xB8: 'MOBITEX-MPAK',
        0xB9: 'CDMA2000-1X-SIMPLE-IP',
        0xBA: 'CDMA2000-1X-MOBILE-IP',
        0xC5: 'AUTOBAUDING',
        0xCA: 'CL-WSP',
        0xCB: 'CO-WSP',
        0xCC: 'CL-SEC-WSP',
        0xCD: 'CO-SEC-WSP',
        0xCE: 'CL-SEC-WTA',
        0xCF: 'CO-SEC-WTA',
        0xD0: 'OTA-HTTP-TO',
        0xD1: 'OTA-HTTP-TLS-TO',
        0xD2: 'OTA-HTTP-PO',
        0xD3: 'OTA-HTTP-TLS-PO',

        # AUTH-ENTITY
        0xE0: 'AAA',
        0xE1: 'HA'
    },

    { # Page 1
        # ADDRTYPE
        0x86: 'IPV6',
        0x87: 'E164',
        0x88: 'ALPHA',
        0x8D: 'APPSRV',
        0x8E: 'OBEX',

        0x90: ',',
        0x91: 'HTTP-',
        0x92: 'BASIC',
        0x93: 'DIGEST'
    }
]

APPID_MAP = {
    'w2':       'Browser',
    'w4':       'MMS',
    '554':      'Streaming',
    'ap0004':   'Supl',
    'w902E':    'NatFw'
}

CODEC_MEDIA_SUB_TYPE_MAP = {
    '0':       'AMR-NB',
    '1':       'iLBC',
    '3':       'G711a',
    '4':       'G711u',
    '5':       'G726-40',
    '6':       'G726-32',
    '7':       'G726-24',
    '8':       'G726-16',
    '9':       'CNComfort',
    '10':      'G729',
    '11':      'AMR-WB',
    '12':      'GSM-EFR',
    '13':      'GSM-FR'
}

TAG_MAP = {
    # Common
    'PXLOGICAL':        'ProxyList',
    'NAPDEF':           'NapList',
    'APPLICATION':      'AppList',
    'NAME':             'Name',
    'PXAUTHINFO':       'AuthInfo',
    'NAPAUTHINFO':      'AuthInfo',
    'APPAUTH':          'AuthInfo',
    'PXAUTH-TYPE':      'AuthType',
    'AUTHTYPE':         'AuthType',
    'PXAUTH-ID':        'AuthName',
    'AUTHNAME':         'AuthName',
    'PXAUTH-PW':        'AuthSecret',
    'AUTHSECRET':       'AuthSecret',
    'AAUTHLEVEL':       'AAuthLevel',
    'AAUTHDATA':        'AAuthData',
    'PXADDR':           'Addr',
    'NAP-ADDRESS':      'Addr',
    'ADDR':             'Addr',
    'PXADDRTYPE':       'AddrType',
    'NAP-ADDRTYPE':     'AddrType',
    'ADDRTYPE':         'AddrType',
    'APPID':            'ClientId',

    # For Bootstrap
    'PROVURL':          'ProvUrl',
    'RESTRICT':         'Restrict',
    'ATTRIBUTE':        'Attribute',

    # For Proxy
    'PROXY-ID':         'ProxyId',
    'PUSHENABLED':      'PushEnabled',
    'PULLENABLED':      'PullEnabled',
    'PORT':             'Ports',
    'PORTNBR':          'PortNbr',

    # For NAP
    'NAPID':            'ID',
    'BEARER':           'BearerType',
    'DNS-ADDR':         'DNS',
    'SPI':              'AAASpi',
    'VALIDITY':         'Validity',
    'COUNTRY':          'Country',
    'NETWORK':          'Network',
    'VALIDUNTIL':       'ValidUntil',
    'LINGER':           'Linger',
    'IFNETWORKS':       'IFNetworks',

    # For App
    'PROVIDER-ID':      'Provider',
    'URI':              'URL',
    'RESOURCE':         'HomePage',
    'AAUTHTYPE':        'AAuthType',
    'AAUTHNAME':        'AAuthName',
    'AAUTHSECRET':      'AAuthSecret',
    'APPADDR':          'AppAddr',
    #For app 'w9013' - VoIP settings
    'SMPORT':           'SMPort',
    'EMPORT':           'EMPort',
    'MEDIAQOS':         'MediaQoS',
    'NODTMFOOB':        'NoDTMFOoB',
    'DTMFPAYLOADTYPE':  'DTMFPayLoadType',
    'SECURECALLPREF':   'SecureCallPref',
    'RTCP-XR-VOIP-METRICS': 'RTCPMetrics',
    'MOMAXALERT':           'MoMaxAlert',
    'MTMAXALERT':           'MtMaxAlert',
    'ALLOWVOIPOVERWCDMA':   'AllowVoIPCDMA',
    'PROVIDERURI':          'ProviderURI',
    'IPVOICEMAILBOXURI':    'IPVoiceMailURI',
    'CODEC':                'Codecs',
    'MEDIASUBTYPE':         'Codec',
    'PRIORITYINDEX':        'Index',
    'OCTET-ALIGN':          'OctetAlign',
    'MODE-SET':             'ModeSet',
    'MODE-CHANGE-PERIOD':   'ModePeriod',
    'MODE-CHANGE-NEIGHBOR': 'ModeNeighbor',
    'PTIME':                'PTime',
    'VAD':                  'VoiceDetect',
    'MODE':                 'Mode',
    'ANNEXB':               'AnnexB',
    'G726RFCPAYLOADFORMAT': 'G726Format',

    #For app 'w9010' - SIP settings
    'PTYPE':            'PType',
    'APROTOCOL':        'AProtocol',
    'SIGQOS':           'SigQoS',
    'TIMER-T1':         'TimerT1',
    'TIMER-T2':         'TimerT2',

    #For app 'w902E' - NAT/FW settings
    'STUNSRVADDR':      'STUNAddr',
    'STUNSRVPORT':      'STUNPort',
    'NATREFRESHTCP':    'NATRefreshTCP',
    'NATREFRESHUDP':    'NATRefreshUDP',
    'REFRESHTCP':       'RefreshTCP',
    'REFRESHUDP':       'RefreshUDP',
    'STUNRETRANSMIT':   'STUNRetransmit',

    # For WLAN
    'PRI-H-SSID':       'SSIDHidden',
    'NETMODE':          'NetMode',
    'SECMODE':          'SecMode',
    'WEPKEYIND':        'WepKeyInd',
    'WEPAUTHMODE':      'WepAuthMode',
    'WEPKEY':           'WepKey',
    'INDEX':            'Index',
    'DATA':             'Data',
    'WLANHAND':         'Handover',
    'EAP':              'ToEAPRef',
    'WLAN':             'BearerParams',

    # For MMS
    'MIN-UDP-PORT':     'MinUdpPort',
    'MAX-UDP-PORT':     'MaxUdpPort',

    # For Email
    'FROM':             'EmailAddr',
    'MTR':              'MailToRetrieve'
}

class Element(object):
    r'''Class for WBXML element
    '''
    def __init__(self, tag = None, parent = None):
        r'''Creates a new WBXML element object
        '''
        self._tag = tag
        self._attribute = dict()
        self._content = dict()
        self._parent = parent
        self._children = list()

        if parent != None:
            parent._children.append(self)

class FileHandler(object):
    r'''Handle wbxml cc file
    '''
    def __init__(self, path):
        r'''Creates a new file handler for the file at the given path
        '''
        self.__bytes = open(path, 'rb')
        self._const_string_tbl = list()
        self._token_page = 0

    def __iter__(self):
        r'''Returns an iterator over this file handler
        '''
        return self

    def __next__(self):
        r'''Implement the function of iterator
        '''
        return self.next()

    def next(self):
        r'''Implement the function of iterator
        '''
        return self.read_byte()
    def read_byte(self, length = None):
        r'''In most cases, it's used to read one byte from specific wbxml file.
            Only in read_opaque(), it's used to read multi bytes.
            If the length is ommited, one token is read and returned as an integer,
            Otherwise, the specified length of tokens are returned as a string.
        '''
        data = self.__bytes.read(1 if length == None else length)

        if len(data) == 0:
            raise StopIteration()

        return ord(data) if length == None else data

    def read_string(self):
        r'''Reads tokens until the end-of-string (0x00) is reached
        '''
        string = ''
        while True:
            char = self.read_byte()
            if char == 0:
                return string
            string += chr(char)

    def read_opaque(self):
        r'''Reads an opaque data buffer, and returns it as a base64 string
        '''
        length = self.read_byte()
        string = self.read_byte(length)
        return b64encode(string)

def create_const_string_tbl(file_handler):
    r'''Create string table according
    '''
    length = file_handler.read_byte()
    # If const string length is longer than 0x7F, there're 2 bytes to construct the length
    # Such as 0x81/0x03 means 0x80 * 1 + 0x03, 0x82/0x11 means 0x80 * 2 + 0x11
    if length > 127:
        length = 128 * (length & 0b1111111) + file_handler.read_byte()
    file_handler._const_string_tbl = [file_handler.read_byte() for i in range(0, length)]

def retrieve_const_string(file_handler):
    r'''Get string from string table
    '''
    string = ''

    offset = file_handler.read_byte()
    # If const string length is longer than 0x7F, there're 2 bytes to construct the length
    # Such as 0x81/0x03 means 0x80 * 1 + 0x03, 0x82/0x11 means 0x80 * 2 + 0x11
    if offset > 127:
        offset = 128 * (offset & 0b1111111) + file_handler.read_byte()

    for i in range(offset, len(file_handler._const_string_tbl)):
        char = file_handler._const_string_tbl[i]
        if char == 0x00:
            break
        string += chr(char)

    return string

def route_token(*keys):
    r'''Parse token and return the (key value).
        For invalid token, raise a KeyError exception.
    '''
    token = TOKEN_TAG
    try:
        for key in keys:
            token = token[key]
        return token
    except:
        raise KeyError(' '.join([hex(k) for k in keys]))

def parse_attribute(file_handler, base_token, element):
    r'''Parse the attribute of a WBXML element.
    '''
    name = False
    value = None
    multi_part_value = ''

    for token in file_handler:
        if token == TOKEN_END:
            # Indicate current attribute ends,
            # So, record current attribute if exist
            if name and (not name in element._attribute):
                element._attribute[name] = multi_part_value
            break

        elif token in route_token(file_handler._token_page, base_token, 1):
            # Indicate current attribute ends,
            # So, record current attribute if exist
            if name and (not name in element._attribute):
                element._attribute[name] = multi_part_value
                # Reset multi_part_value
                multi_part_value = ''

            # Get a new attribute according to token
            (name, value) = route_token(file_handler._token_page, base_token, 1, token)
            if (value != None)\
               and (not isinstance(value, dict))\
               and (not isinstance(value, collections.Callable)):
                element._attribute[name] = value
                # Reset name and value
                name = False
                value = None

        elif token == TOKEN_SWITCH_PAGE:
            file_handler._token_page = file_handler.read_byte()

        elif token == TOKEN_STR_I:
            # Indicate a raw string
            multi_part_value += file_handler.read_string()

        elif token == TOKEN_STR_T:
            # Indicate a string from const string table
            multi_part_value += retrieve_const_string(file_handler)

        elif value == None:
            multi_part_value += str(token)

        elif isinstance(value, dict):
            multi_part_value += value[token]

        elif isinstance(value, collections.Callable):
            # As the page may change a lot, retrieve latest value
            # Token of this value must be 6
            if TOKEN_VALUE[file_handler._token_page].has_key(token):
                multi_part_value += TOKEN_VALUE[file_handler._token_page][token]

def parse_element(file_handler, parent):
    r'''Parse the element as well as their children recursively
    '''

    for token in file_handler:
        if token == TOKEN_END:
            break
        elif token == TOKEN_STR_I:
            element = Element(file_handler.read_string(), parent)
        elif token == TOKEN_OPAQUE:
            element = Element(file_handler.read_opaque(), parent)
        else:
            base_token = (0b00111111 & token)
            tag = route_token(file_handler._token_page, base_token, 0)
            element = Element(tag, parent)

            if (0b10000000 & token):
                parse_attribute(file_handler, base_token, element)

            if (0b01000000 & token):
                parse_element(file_handler, element)

            load_content(element)

def load_content(element):
    r'''Load the 'name', 'value' and 'type' into its parent's content.
        And, map the OMA CP format string into DM DDF format.
    '''
    if element._tag == 'parm':
        # 'name' is mandatory
        if 'name' in element._attribute:
            parm_name = element._attribute['name']

            if 'value' in element._attribute:
                parm_value = element._attribute['value']
            else:
                # No 'value' is valid, it'll be transformed into true later
                parm_value = '?'

            # Handle special parm, special parm first
            if (not handle_multiple_parm(parm_name, parm_value, element._parent))\
               and (not handle_ext_parm(parm_name, parm_value, element._parent))\
               and (not handle_ignore_parm(parm_name, element._parent)):
                # Handle normal parm
                if parm_name == 'APPID' and parm_value in APPID_MAP:
                    parm_value = APPID_MAP[parm_value]

                if parm_name == 'Codec' and parm_value in CODEC_MEDIA_SUB_TYPE_MAP:
                    parm_value = CODEC_MEDIA_SUB_TYPE_MAP[parm_value]

                if parm_name in TAG_MAP:
                    parm_name = TAG_MAP[parm_name]

                # Record the mapped (name value)
                if not parm_name in element._parent._content:
                    element._parent._content[parm_name] = parm_value
                elif isinstance(parm_value, dict)\
                     and isinstance(element._parent._content[parm_name], dict):
                    for key, value in parm_value.items():
                        if not key in element._parent._content[parm_name]:
                            element._parent._content[parm_name][key] = value
                elif isinstance(parm_value, list)\
                     and isinstance(element._parent._content[parm_name], list):
                    element._parent._content[parm_name].append(parm_value)

    elif element._tag == 'characteristic':
        # Handle character, special character first
        if (not handle_ignore_character(element))\
           and (not handle_unique_character(element)):
            # 'characteristic' is mandatory
            if 'type' in element._attribute:
                char_type = element._attribute['type']

                if char_type in TAG_MAP:
                    char_type = TAG_MAP[char_type]

                # At first, insert something into current characterister
                if char_type == 'AppList':
                    element._content['Type'] = 'App'
                elif char_type == 'NapList':
                    element._content['Type'] = 'Nap'
                elif char_type == 'ProxyList':
                    element._content['Type'] = 'Proxy'
                    if not 'Ext' in element._content:
                        element._content['Ext'] = dict()
                    element._content['Ext']['InternetEnabled'] = '?'

                # Append the content to its parent
                if not char_type in element._parent._content:
                    element._parent._content[char_type] = list()
                element._parent._content[char_type].append(element._content)

def handle_multiple_parm(name, value, parent):
    r'''Parse the multiple parm into a dict to handle them as array
    '''
    if name == 'TO-PROXY':
        array_name = 'ToConRef'
        sub_dict = {'ConRef':value}

        if value != 'INTERNET':
            sub_dict['Type'] = 'Proxy'

    elif name == 'TO-NAPID':
        array_name = 'ToConRef'
        sub_dict = {'ConRef':value}

        if value != 'INTERNET':
            sub_dict['Type'] = 'Nap'

    elif name == 'PRI-SSID'\
         or name == 'PRI-U-SSID':
        array_name = 'SSIDList'
        sub_dict = {'SSID':value}

    elif name == 'PDOMAIN':
        array_name = 'Domains'
        sub_dict = {'DomainName':value}

    elif name == 'SERVICE':
        array_name = 'Services'
        sub_dict = {'ServiceName':value}

    else:
        return False

    if not array_name in parent._content:
        parent._content[array_name] = list()
    parent._content[array_name].append(sub_dict)

    return True

def handle_ext_parm(name, value, parent):
    r'''To collect some parm together into 'Ext' dict
    '''
    if name == 'INTERNET':
        new_name = 'InternetEnabled'

    elif name == 'PUSHENABLED':
        new_name = 'PushEnabled'

    elif name == 'PULLENABLED':
        new_name = 'PullEnabled'

    else:
        return False

    if not 'Ext' in parent._content:
        parent._content['Ext'] = dict()

    if not new_name in parent._content['Ext']:
        parent._content['Ext'][new_name] = value

    return True

def handle_ignore_parm(name, parent):
    r'''Just omit some parm
    '''
    if (parent._attribute['type'] == 'VENDORCONFIG' and name == 'NAME')\
       or (parent._attribute['type'] == 'BOOTSTRAP' and name == 'COUNTRY')\
       or (parent._attribute['type'] == 'BOOTSTRAP' and name == 'NETWORK')\
       or (parent._attribute['type'] == 'VOIPURIS' and name == 'TO-APPREF'):
        return True

    else:
        return False

def handle_ignore_character(element):
    r'''Consider one character's sub parm belonging to its father character
    '''
    if ((element._attribute['type'] == 'PXPHYSICAL'\
       and element._parent._attribute['type'] == 'PXLOGICAL')\
       or element._attribute['type'] == 'VOIPURIS'\
       or element._attribute['type'] == 'NW'\
       or element._attribute['type'] == 'NATIAP'):
        for key, value in element._content.items():
            element._parent._content[key] = value
        return True
    elif (element._attribute['type'] == 'APPADDR'):
        addr = element._parent._content.get('Addr', '')
        if addr != '':
            return True
        client_id = element._parent._content.get('ClientId', '')
        if client_id =='Supl':
            for key, value in element._content.items():
                element._parent._content[key] = value
            return True
    return False

def handle_unique_character(element):
    r'''Some tags is defined as character in OMA CP which is considered as dictionary array.
        However, in DM DDF, they are unique, so just store it as single dictionary instead of
        dictionary array. eg:
        "xxx":[{"yyy":"zzz"}] ==> "xxx":{"yyy":"zzz"}
    '''
    new_name = False
    if element._attribute['type'] == 'WLAN':
        new_name = 'BearerParams'
    elif element._attribute['type'] == 'RESOURCE':
        new_name = 'HomePage'
    elif (element._attribute['type'] == 'PXAUTHINFO')\
         or (element._attribute['type'] == 'NAPAUTHINFO')\
         or (element._attribute['type'] == 'APPAUTH'):
        new_name = 'AuthInfo'

    if new_name:
        # Only record the first one if there're more than one
        if not new_name in element._parent._content:
            element._parent._content[new_name] = element._content
        return True
    else:
        return False

def update_email_dict(target_dict, new_dict):
    r'''Convert CP email into DM DDF and add it into specific DM email dict
    '''
    client_id = new_dict['ClientId']

    if target_dict\
       and ((client_id == '25' and 'Send' in target_dict)\
            or ((client_id == '110' or client_id == '143')\
                and 'Receive' in target_dict)):
        return False
    else:
        if not target_dict:
            target_dict = dict()

        # Add ToConRef, make sure not to add redundant one
        if 'ToConRef' in new_dict:
            if 'ToConRef' in target_dict:
                exist_conref_list = list()
                # Get exist ConRef list for referrence
                for item in target_dict['ToConRef']:
                    exist_conref_list.append(item['ConRef'])

                # Traverse new ConRef list
                for item in new_dict['ToConRef']:
                    if not item['ConRef'] in exist_conref_list:
                        target_dict['ToConRef'].append(item)
            else:
                target_dict['ToConRef'] = new_dict['ToConRef']

        # Add 'Type', 'ClientId' and 'Name'
        target_dict['Type'] = 'App'
        target_dict['ClientId'] = 'Email'
        target_dict['Name'] = new_dict['Provider']

        # Rearrange 'AppAddr', assume there's only one 'AppAddr'
        if 'AppAddr' in new_dict:
            app_addr = new_dict['AppAddr'][0]

            if 'Addr' in app_addr:
                new_dict['Addr'] = app_addr['Addr']

            if 'Ports' in app_addr:
                port = app_addr['Ports'][0]
                if 'PortNbr' in port:
                    new_dict['PortNbr'] = port['PortNbr']

        # Delete 'ClientId', 'Provider', 'ToConRef', 'AppAddr' and 'Type'
        new_dict.pop('ClientId')
        new_dict.pop('Provider')
        new_dict.pop('Type')
        if 'AppAddr' in new_dict:
            new_dict.pop('AppAddr')
        if 'ToConRef' in new_dict:
            new_dict.pop('ToConRef')

        # Handle special cases
        if client_id == '25':
            # Change "Name" into "EmailName"
            if 'Name' in new_dict:
                new_dict['EmailName'] = new_dict['Name']
                new_dict.pop('Name')

            # Add new_dict to 'Send'
            target_dict['Send'] = new_dict

        else:
            if client_id == '110':
                new_dict['RecvProtocol'] = 'POP3'
            else:
                new_dict['RecvProtocol'] = 'IMAP4'

            # Remove 'Name'
            if 'Name' in new_dict:
                new_dict.pop('Name')

            # Add new_dict to 'Receive'
            target_dict['Receive'] = new_dict

        return target_dict

# Parse "BOOTSTRAP", there may be several "BOOTSTRAP"
def handle_bootstrap(cc_dict):
    r'''Handle bootstrap
    '''

    if 'BOOTSTRAP' in cc_dict:
        temp = cc_dict['BOOTSTRAP']
        cc_dict.pop('BOOTSTRAP')

        for item in temp:
            for key, value in item.items():
                cc_dict[key] = value
    return cc_dict


# Convert "Restrict" to "Attribute"
# Note: 1. No "VENDORCONFIG"/"Restrict" means full "Attribute"
#       2. Only consider the first "VENDORCONFIG"
#       3. If there's "Attribute", ignore "Restrict"
def handle_vendorcfg(cc_dict):
    r'''Handle vendor config
    '''

    # Attribute should be aligned with connset_lib_types.h:
    # All          0
    # Editable     0x01
    # Deletable    0x02
    # Visible      0x04
    attribute_value = 7

    if 'VENDORCONFIG' in cc_dict:
        # Only consider the first item
        vendorcfg = cc_dict['VENDORCONFIG'][0]
        cc_dict.pop('VENDORCONFIG')

        if 'Attribute' in vendorcfg:
            attribute_value = 0
            if -1 != vendorcfg['Attribute'].find('EDIT'):
                attribute_value += 1
            if -1 != vendorcfg['Attribute'].find('DELETE'):
                attribute_value += 2
            if -1 != vendorcfg['Attribute'].find('VIEW'):
                attribute_value += 4
        elif 'Restrict' in vendorcfg:
            if -1 != vendorcfg['Restrict'].find('WRITE'):
                attribute_value -= 1
            if -1 != vendorcfg['Restrict'].find('DELETE'):
                attribute_value -= 2
            if -1 != vendorcfg['Restrict'].find('VIEW'):
                attribute_value -= 4

    # Set 'Attribute'
    cc_dict['Attribute'] = attribute_value
    return cc_dict


def handle_email_app(cc_dict):
    r'''Handle email application
    '''
    if 'AppList' in cc_dict:
        email_list = list()
        email_list_dict = dict()
        app_remove_list = list()
        is_email_app = False

        app_list = cc_dict['AppList']
        for item in app_list:
            if ('ClientId' in item)\
           and (item['ClientId'] == '25'\
             or item['ClientId'] == '110'\
             or item['ClientId'] == '143'):
                if 'Provider' in item:
                    email_list.append(item)
                app_remove_list.append(item)
                is_email_app = True

        for item in app_remove_list:
            app_list.remove(item)

        for item in email_list:
            email_dict = False
            if item['Provider'] in email_list_dict:
                email_dict = email_list_dict[item['Provider']]
            email_dict = update_email_dict(email_dict, item)
            if email_dict:
                # 'Provider' has been changed into 'Name'
                email_list_dict[email_dict['Name']] = email_dict

        for key, value in email_list_dict.items():
            if ('Send' in value)\
           and ('Receive' in value)\
           and ('ToConRef' in value):
                app_list.append(value)

        if is_email_app:
            cc_dict.pop('AppList')
            cc_dict['AppList'] = app_list

    return cc_dict

def combine_into_voip_app(w9013_app_dict, w9010_app_dict):
    r'''combine the VoIP settings w9013 and  SIP settings w9010 into the application VoIP.
    '''
    voip_app_dict = dict()
    if w9013_app_dict:
        voip_app_dict = w9013_app_dict
        voip_app_dict['ClientId'] = 'VoIP'
        voip_app_dict.pop('APPREF', False)
        voip_app_dict.pop('TO-APPREF', False)
        if w9010_app_dict:
            # contruct sip dictionary
            sip_dict = copy.deepcopy(w9010_app_dict)
            sip_dict.pop('ClientId', False)
            sip_dict.pop('Type', False)
            sip_dict.pop('Name', False)
            sip_dict.pop('Provider', False)
            app_addr_list = sip_dict.pop('AppAddr', False)
            auth_info_dict = sip_dict.pop('AuthInfo', False)
            sip_dict.pop('ToConRef', False)
            sip_dict.pop('APPREF', False)
            homepage_dict = sip_dict.pop('HomePage', False)
            if homepage_dict:
                sip_addr = homepage_dict.pop('URL', False)
                if sip_addr:
                    sip_dict['Addr'] = sip_addr
                sip_dict['AuthInfo'] = homepage_dict
            if sip_dict:
                voip_app_dict['SIP'] = sip_dict

            # contruct sip-out dictionary
            sip_out_dict = dict()
            app_addr_dict = dict()
            if app_addr_list:
                app_addr_dict = app_addr_list[0]
                ports_list = app_addr_dict.pop("Ports", False)
                if ports_list:
                    port = ports_list[0].get('PortNbr', False)
                    if port:
                        app_addr_dict['Port'] = port
            if app_addr_dict:
                sip_out_dict = app_addr_dict
            if auth_info_dict:
                sip_out_dict['AuthInfo'] = auth_info_dict
            if sip_out_dict:
                voip_app_dict['SIPOut'] = sip_out_dict

    return voip_app_dict

def handle_voip_app(cc_dict):
    r'''Hanlde all app 'w9013' and 'w9010' - combine them into app 'VoIP'.
    '''
    if 'AppList' in cc_dict:
        w9013_list = list()
        w9010_list = list()
        other_list = list()
        app_list = cc_dict['AppList']
        for item in app_list:
            if ('ClientId' in item):
                if item['ClientId'] == 'w9013':
                    w9013_list.append(item)
                elif item['ClientId'] == 'w9010':
                    w9010_list.append(item)
                else:
                    other_list.append(item)
        for w9013_app in w9013_list:
            voip_app = dict()
            if ('TO-APPREF' in w9013_app):
                for w9010_app in w9010_list:
                    if ('APPREF' in w9010_app) and (w9010_app['APPREF'] == w9013_app['TO-APPREF']):
                        voip_app = combine_into_voip_app(w9013_app, w9010_app)
                        break
            if not voip_app:
                voip_app = combine_into_voip_app(w9013_app, False)
            other_list.append(voip_app)

        cc_dict.pop('AppList')
        cc_dict['AppList'] = other_list
    return cc_dict

def cc_dict_rearrange(cc_dict):
    r'''Rearrange the cc dict before converting to JSON string
    '''

    cc_dict = handle_bootstrap(cc_dict)

    cc_dict = handle_vendorcfg(cc_dict)

    cc_dict = handle_email_app(cc_dict)

    cc_dict = handle_voip_app(cc_dict)

    cc_dict['OriginId'] = 'fac'

    return cc_dict


def cc_dict_2_json(cc_dict, cc_json):
    r'''Convert cc dict to JSON string
    '''
    cc_json += '{'
    for key, value in cc_dict.items():
        if FLAG_REF:
            cc_json += '\\"' + key + '\\"' + ':'
        else:
            cc_json += '"' + key + '"' + ':'

        if isinstance(value, list):
            cc_json += '['
            for item in value:
                if isinstance(item, dict):
                    cc_json = cc_dict_2_json(item, cc_json)
                elif isinstance(item, str):
                    if item == '?':
                        cc_json += 'true' + ','
                    else:
                        if FLAG_REF:
                            cc_json += '\\"' + item + '\\"' + ','
                        else:
                            cc_json += '"' + item + '"' + ','
                elif isinstance(item, int):
                    cc_json += str(item) + ','

            cc_json = cc_json[:len(cc_json) - 1] + ']' + ','

        elif isinstance(value, dict):
            cc_json = cc_dict_2_json(value, cc_json)

        elif isinstance(value, str):
            if value == '?':
                cc_json += 'true' + ','
            else:
                if FLAG_REF:
                    cc_json += '\\"' + value + '\\"' + ','
                else:
                    cc_json += '"' + value + '"' + ','

        elif isinstance(value, int):
            cc_json += str(value) + ','

    return cc_json[:len(cc_json) - 1] + '}' + ','


def construct_json(cc_dict, des_file):
    r'''Construct cc JSON string
    '''
    cc_dict = cc_dict_rearrange(cc_dict)

    cc_json = cc_dict_2_json(cc_dict, '')

    cc_json = cc_json[:len(cc_json) - 1]

    # Output the cc json string
    if des_file != None:
        file_handler = open(des_file, 'w')
        file_handler.write(cc_json)
        file_handler.close()
    else:
        #stdout.write(cc_json)
        return cc_json


def parse_cc(src_file, des_file = None):
    r'''Parses the input WBXML file into json string
    '''
    try:
        file_handler = FileHandler(src_file)

        # Read version
        file_handler.read_byte()

        # Read public id which should be provisioning
        if file_handler.read_byte() != 0x0B:
            return False

        # Read charset
        file_handler.read_byte()

        # Create const string table
        create_const_string_tbl(file_handler)

        root_element = Element()
        parse_element(file_handler, root_element)

        # Construct JSON string
        if root_element:
            for item in root_element._children:
                if item._tag == 'wap-provisioningdoc':
                    json = construct_json(item._content, des_file)
                    return True, json
        return False, None
    except Exception as e:
        #print_exc(file = stdout)
        return False, None


def wbxml2json():
    r'''Entry interface
    '''
    import sys
    import os.path
    global FLAG_REF

    if len(sys.argv) > 1:
        parm_pos = 0
        if '-r' == sys.argv[1]:
            FLAG_REF = True
            parm_pos = 2
        else:
            parm_pos = 1

        if (len(sys.argv) > parm_pos):
            if os.path.exists(sys.argv[parm_pos]):
                success, json = parse_cc(*sys.argv[parm_pos:])
                if not success:
                    raise Exception('Invalid file!')
                else:
                    return json
            else:
                raise Exception('File not exist!')
        else:
            raise Exception('Please input the file!')
    else:
        raise Exception('Please input the file!')

def convert(wbxmlFile):

    import os.path
    global FLAG_REF

    if os.path.exists(wbxmlFile):
        success, json = parse_cc(wbxmlFile)
        if not success:
            raise Exception('Invalid file!')
        else:
            return json
    else:
        raise Exception('File not exist!')

# Command-line entry point
if __name__ == '__main__':
    wbxml2json()


