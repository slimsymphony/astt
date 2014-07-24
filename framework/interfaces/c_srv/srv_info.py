#FIXME: Get rid of this and implement it as a activity!

import time, types, os

import core
from interfaces.isimessage import ISIMessage, ISIMessageException
from utils.xstruct import xcalcsize, xpack, xunpack
from utils import include

from core.testcase_exceptions import TestException, \
                                         SkipTestException

inc = include.Include(['info_isi.h', 'info_conf.h', 'pn_const.h'])
CUSTOMER_ID = getattr(inc, 'INFO_PP_CUSTOMER_ID_DEFAULT', 1)

lookups = {
    #! Add other lookups accordingly.
    'req_msg':      lambda msg_id:          inc.lookup('_REQ', msg_id)[0],
    'resp_msg':     lambda msg_id:          inc.lookup('_RESP', msg_id)[0],
    'sb_name':      lambda sb_id:           inc.lookup('INFO_SB_PRODUCT_INFO_', sb_id)[0],
    }

# ============================================================================
#   3.1     INFO server module
# ----------------------------------------------------------------------------

# Local data structures

infoStatus = {inc.INFO_OK: 'INFO_OK',
              inc.INFO_FAIL: 'INFO_FAIL',
              inc.INFO_NO_NUMBER: 'INFO_NO_NUMBER',
              inc.INFO_NOT_SUPPORTED: 'INFO_NOT_SUPPORTED'}

infoVersionTarget = {inc.INFO_MCUSW: 'INFO_MCUSW',
                     inc.INFO_HW: 'INFO_HW',
                     inc.INFO_PCI: 'INFO_PCI',
                     inc.INFO_UEM: 'INFO_UEM',
                     inc.INFO_UPP: 'INFO_UPP',
                     inc.INFO_RFIC: 'INFO_RFIC',
                     inc.INFO_DSP: 'INFO_DSP',
                     inc.INFO_LCD: 'INFO_LCD',
                     inc.INFO_ROFS_FOTAID: 'INFO_ROFS_FOTAID',
                     inc.INFO_BT_MCM: 'INFO_BT_MCM',
                     inc.INFO_ADSP: 'INFO_ADSP',
                     inc.INFO_FLIP_MCUSW: 'INFO_FLIP_MCUSW',
                     inc.INFO_ADSP_DEVICE_ID: 'INFO_FLIP_MCUSW',
                     inc.INFO_ADSP_REVISION_ID: 'INFO_ADSP_REVISION_ID'}

infoVersionTargetX = dict([(b, a) for a, b in infoVersionTarget.items()])

infoVersionTarget2 = {inc.INFO_BOOTCODE_VER: 'INFO_BOOTCODE_VER',
                      inc.INFO_APE_SW_CORE_VER: 'INFO_APE_SW_CORE_VER',
                      inc.INFO_CONTENT_FOTAID: 'INFO_CONTENT_FOTAID',
                      inc.INFO_APE_TEST_VER: 'INFO_APE_TEST_VER',
                      inc.INFO_RETU: 'INFO_RETU',
                      inc.INFO_TAHVO: 'INFO_TAHVO',
                      inc.INFO_APE_HW_VERSION: 'INFO_APE_HW_VERSION',
                      inc.INFO_APE_ADSP_SW: 'INFO_APE_ADSP_SW',
                      inc.INFO_CAMERA: 'INFO_CAMERA',
                      inc.INFO_APE_BT_VERSION: 'INFO_APE_BT_VERSION',
                      inc.INFO_CONTENT_PACK: 'INFO_CONTENT_PACK'}

infoVersionTarget2X = dict([(b, a) for a, b in infoVersionTarget2.items()])


def __infoIsiVersion():
    """Defines appropriate ISI version flags.

    Notes:
    """
    return lambda z, y: (inc.INFO_ISI_VERSION_Z == (z) and \
                         inc.INFO_ISI_VERSION_Y >= (y)) or \
                        (inc.INFO_ISI_VERSION_Z > (z))

INFO_ISI_MIN_VERSION = __infoIsiVersion()
INFO_ISI_MIN_VERSION_1_0 = INFO_ISI_MIN_VERSION(1,0)
INFO_ISI_MIN_VERSION_3_0 = INFO_ISI_MIN_VERSION(3,0)
INFO_ISI_MIN_VERSION_4_3 = INFO_ISI_MIN_VERSION(4,3)

def __getVersionTarget(target):
    if type(target) == types.StringType:
        target = infoVersionTargetX.get(target)
    return target

def __getVersionTarget2(target):
    if type(target) == types.StringType:
        target = infoVersionTarget2X.get(target)
    return target

def __getSnTarget(target):
    if type(target) == types.StringType:
        target = getattr(inc, target)
    return target

def getSerialNbr(phone, target = ''):
    """Read the serial number of the phone with getSerialNbr()

        You can check the following value(s) from response:
            status = inc.INFO_OK |
                     inc.INFO_FAIL |
                     inc.INFO_NO_NUMBER |
                     inc.INFO_NOT_SUPPORTED
    """

    if target == '':
        iTarget = __getSnTarget('INFO_SN_IMEI_PLAIN')
    else:
        iTarget = __getSnTarget(target)

    request = InfoSerialNbrReq(msg_id = inc.INFO_SERIAL_NUMBER_READ_REQ,
                               target = iTarget)

    tries, notAvailable = 0, False

    while tries < 3:
        try:
            response = InfoSerialNbrResp(isi_message = \
                       phone.transferMsg(request))
        except ISIMessageException, (err):
            debug.out('Error in response ISI message: %s' % err)
            if tries < 2:
                debug.out("Reading phone's serial number failed! " \
                          "Trying again...")
                tries += 1
                debug.out("Sleeping for a while...")
                time.sleep(tries)
                continue
            else:
                debug.out("Unable to read phone's serial number!")
                notAvailable = True
                break

        if response.status == inc.INFO_OK:
            debug.vrb('Reading phone serial number: %s' % response.msg_data_str)
            break
        elif response.status in [inc.INFO_NO_NUMBER, inc.INFO_NOT_SUPPORTED]:
            debug.vrb('\n\'%s\'-serial number not available: %s\n' % \
                                                (target, response.status_str))
            notAvailable = True
            break
        else:
            if tries < 2:
                debug.out("Reading phone's serial number failed! " \
                          "Trying again...")
                tries += 1
                debug.out("Sleeping for a while...")
                time.sleep(tries)
            else:
                debug.out("Unable to read phone's serial number!")
                notAvailable = True
                break

    if notAvailable:
        return 'not available'
    else:
        return response.sub_block_str

def getVersion(phone, target, target2 = 0):
    """Read the HW/SW versions of the phone with getVersion()

        You can check the following value(s) from response:
            status = inc.INFO_OK |
                     inc.INFO_FAIL
    """

    request = InfoVersionReq(msg_id=inc.INFO_VERSION_READ_REQ,
                             target_version=__getVersionTarget(target),
                             target2_version=__getVersionTarget2(target2))

    notAvailable = False

    try:
        response = InfoVersionResp(isi_message = \
                                phone.transferMsg(request))
    except ISIMessageException, (err):
        debug.out('Error in response ISI message: %s' % err)
        notAvailable = True

    if response.status == inc.INFO_OK:
        debug.vrb('Reading phone version number: %s' % response.msg_data_str)
    else:
        debug.vrb('\n\'%s\'-version number read failed: %s\n' % \
                                    (target or target2, response.status_str))
        notAvailable = True

    if notAvailable:
        return 'not available'
    else:
        return response.sub_block_str

def getSwVersion(phone = None):
    """Read the MCUSW-versions of the phone"""
    if not phone:
        phone = core.FW_conf['connection']
    return getVersion(phone, target = 'INFO_MCUSW')

def getHwVersion(phone):
    """Read the HW-versions of the phone"""
    return getVersion(phone, target = 'INFO_HW')

def getCpVersion(phone = None):
    """Read content pack version from the phone"""
    if not phone:
        phone = core.FW_conf['connection']
    return getVersion(phone, target = 0, target2 = 'INFO_CONTENT_PACK')

def infoProductInfoReadReq(phone, **isi_message_fields):
    # Default values
    default_values = {
        'target' : inc.INFO_PRODUCT_MANUFACTURER
        }

    # Overwrite default values with given values.
    default_values.update(isi_message_fields)

    # Transferring message.
    response = phone.__transferMessage(phone, InfoProductInfoReadReq,
                                           InfoProductInfoReadResp,
                                           **default_values)

    phone.failUnlessEqual(response.status, inc.INFO_OK,
        'Operation PpDataWriteReq failed. Cause not INFO_OK(' + str(response.status))

    # Creating return value
    return response

def getProductManufacturer(test=None):
    resp = infoProductInfoReadReq(test, target=inc.INFO_PRODUCT_MANUFACTURER)
    return resp.string
    
def getProductName(test=None):
    resp = infoProductInfoReadReq(test, target=inc.INFO_PRODUCT_NAME)
    return resp.product    


def __transferMessage(testcase, sendMsgClass, receiveMsgClass, **updated_values):
    """ Internal helper function for transferring/receiving messages.
    """
    assert 0, "__transferMessage from Phone-class should be used"

    # Creating request.
    request = sendMsgClass(**updated_values)

    # Printing parameters.
    

    # Sending message.
    data = core.FW_conf['connection'].transferMsg(request)

    # Creating response.
    response = receiveMsgClass(isi_message = data)

    return response

# ============================================================================
#   3.2     INFO server ISI message classes
# ----------------------------------------------------------------------------

class InfoISIMessage(ISIMessage):

    def __init__(self, **isi_message_fields):
        ISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(resource = inc.PN_INFO)
        self.assertFields(resource = inc.PN_INFO)
        self.filler = 0
        
        
##
## ISI MESSEGE SUB BLOCK (UN)PACK METHODS
##
    def _get_unpack_sub_blocks(self):
        while(self.sb_msg_data):
            sb_id = xunpack('>B', self.sb_msg_data[:1])[0]
            sb_name = lookups['sb_name'](sb_id)
            if sb_name:
                method_name = sb_name.lower()
                eval('self.' + method_name)
            else:
                debug.err('Sub block nbr:' + sb_id + ' NOT successful unpacked!')
                break

    def _get_pack_sub_blocks(self):
        #! Change this accordingly.
        self.sub_block_nbr, sb_data = 0, []
        for sb_name in self.sb_names:
            method_name = sb_name.replace('INFO_', '').lower()
            try:
                sb_data += eval('self.' + method_name)
            except Exception, e:
                debug.err('Sub block ' + repr(sb_name) + ' NOT successful packed: ' + e)
                pass
            else:
                #! Change this accordingly.
                self.sub_block_nbr += 1

        return sb_data
##        
##
## INFO_SB_PRODUCT_INFO_MANUFACTURER
##
    def _get_info_sb_product_info_manufacturer(self):
        if self.sb_msg_data:
            self.string = ''
            self.sub_block_id, self.sub_block_len, self.filler, self.str_len, string_buffer = xunpack('>BBBB*[', self.sb_msg_data)
            for i in range(self.str_len-1):
                ichar, string_buffer = xunpack('>B*[', string_buffer)
                self.string += chr(ichar)

            self.sb_msg_data = self.sb_msg_data[self.sub_block_len:]

##
## INFO_SB_PRODUCT_INFO_NAME
##
    def _get_info_sb_product_info_name(self):
        if self.sb_msg_data:
            self.product = ''
            self.sub_block_id, self.sub_block_len, self.filler, self.str_len, string_buffer = xunpack('>BBBB*[', self.sb_msg_data)
            for i in range(self.str_len-1):
                ichar, string_buffer = xunpack('>B*[', string_buffer)
                self.product += chr(ichar)            
            self.sb_msg_data = self.sb_msg_data[self.sub_block_len:]

        
class InfoSerialNbrReq(InfoISIMessage):

    def __init__(self, **isi_message_fields):
        InfoISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id = None, target = None)

    def _get_msg_id_str(self):
        return inc.lookup('_REQ', self.msg_id)

    def _get_msg_data_str(self):
        return 'target: %s' % inc.lookup('INFO_SN_', self.target)[0]

    def _get_msg_data(self):
        return xpack('>B',  self.target)

    def _check_set_msg_data(self, new_msg_data):
        self.target = xunpack('>B', new_msg_data)
        return new_msg_data

class InfoSerialNbrResp(InfoISIMessage):

    def __init__(self, **isi_message_fields):
        InfoISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id = None, status = None,
                          sub_block_nbr = 0, sub_block = None)
        self.assertFields(msg_id = inc.INFO_SERIAL_NUMBER_READ_RESP)

    def _get_msg_id_str(self):
        return inc.lookup('_RESP', self.msg_id)

    def _get_msg_data(self):
        return xpack('>BB*[', self.status, self.sub_block_nbr, self.sub_block)

    def _get_msg_data_str(self):
        if self.sub_block_nbr:
            msg_data = 'status: %s, sub_block_id: %s, sub_block: %s\n' %\
            (self.status_str, inc.lookup('INFO_SB_', self.sub_block[0])[0], \
             self.sub_block_str.replace('\n',' ').replace('\0',''))
        else:
            msg_data = msg_data = 'status: %s\n' % self.status_str

        return msg_data

    def _get_sub_block_str(self):
        if self.sub_block_nbr:
            if (self.sub_block[0] == inc.INFO_SB_SN_IMEI_PLAIN,
                self.sub_block[0] == inc.INFO_SB_SN_IMEI2_PLAIN or \
                self.sub_block[0] == inc.INFO_SB_SN_ESN_PLAIN or \
                self.sub_block[0] == inc.INFO_SB_SN_ESNX_PLAIN):
                return '%s' % \
                        ''.join(map(chr, self.sub_block[4:self.sub_block[1]]))
            else:
                return '%s' % \
                        ','.join(map(hex, self.sub_block[4:self.sub_block[1]]))
        else:
            return 'not available'

    def _get_status_str(self):
        return '%s' % (infoStatus.get(self.status, 'UNKNOWN!'))

    def _check_set_msg_data(self, new_msg_data):
        self.status, self.sub_block_nbr, \
                            self.sub_block = xunpack('>BB*[', new_msg_data)
        return new_msg_data

class InfoVersionReq(InfoISIMessage):

    def __init__(self, **isi_message_fields):
        InfoISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id = None, target_version = None,
                          target2_version = None)

    def _get_msg_id_str(self):
        return inc.lookup('_REQ', self.msg_id)

    def _get_msg_data_str(self):
        return 'target: %s, target2: %s' % \
                (infoVersionTarget.get(self.target_version),
                infoVersionTarget.get(self.target_version))

    def _get_msg_data(self):
        return xpack('>HL',  self.target_version, self.target2_version)

    def _check_set_msg_data(self, new_msg_data):
        self.target_version, self.target2_version \
                        = xunpack('>HL', new_msg_data)
        return new_msg_data

class InfoVersionResp(InfoSerialNbrResp):

    def __init__(self, **isi_message_fields):
        InfoISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id = None, status = None,
                          sub_block_nbr = 0, sub_block = None)
        self.assertFields(msg_id = inc.INFO_VERSION_READ_RESP)

    def _get_sub_block_str(self):
        sb_name = inc.lookup('INFO_SB_', self.sub_block[0])[0]

        if sb_name in ['INFO_SB_VERSION_BY_DSP_CORE_SRV']:
            version_str = self.sub_block[6:]
            str_length = self.sub_block[5]
        else:
            version_str = self.sub_block[4:]
            str_length = self.sub_block[3]

        if self.sub_block_nbr:
            version = ''.join(map(chr, version_str[:str_length]))
            if version.replace('\n',' ').replace('\0','').replace(' ','') == '':
                return 'not available'
            else:
                return version
        else:
            return 'not available'


##
## 3.29 INFO_PRODUCT_INFO_READ_REQ
##
# ============================================================================
class InfoProductInfoReadReq(InfoISIMessage):
# ----------------------------------------------------------------------------
    def __init__(self, **isi_message_fields):
        InfoISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id = inc.INFO_PRODUCT_INFO_READ_REQ)

    def _get_msg_id_str(self):
        return inc.lookup('_REQ', self.msg_id)

    def _get_msg_data(self):
        msg_data = xpack('>BB', self.target, self.filler)

        return msg_data

##
## 3.30 INFO_PRODUCT_INFO_READ_RESP
##
# ============================================================================
class InfoProductInfoReadResp(InfoISIMessage):
# ----------------------------------------------------------------------------
    def __init__(self, **isi_message_fields):
        InfoISIMessage.__init__(self, **isi_message_fields)
        self.assertFields(msg_id = inc.INFO_PRODUCT_INFO_READ_RESP)

    def _get_msg_id_str(self):
        return inc.lookup('_RESP', self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        self.status, self.sub_block_count, self.sb_msg_data = xunpack('>BB*[', new_msg_data)
        if self.sub_block_count:
            self.unpack_sub_blocks  

        return new_msg_data
