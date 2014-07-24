""" ISIMessage module for GRANITE Server ISI messages.

    This module implements ISI message classes for all GRANITE Server ISI
    messages. All these classes are inherited from ISIMessage class.

    Message classes have all common isi message fields and also own fields that
    are taken from message data. This way it's much more easier to make message
    classes and analyze the response data. All classes contain checks for
    message validity.

    Messages are implemented both for the old message format and for the new
    GRANITE Server.
"""

# ============================================================================
# Module Setup

# System module imports
import os

# GRANITE module imports
import core, interfaces
from utils import include
from core.testcase_exceptions import TestException
from interfaces.isimessage import ISIMessage, ISIMessageException
from utils.xstruct import xpack, xunpack

# Local data definitions
inc = include.Include('granite_p_isi.h')


# lookup macros
inc_lookups = {
    'req_msg':      lambda msg_id:          inc.lookup('_REQ', msg_id)[0],
    'resp_msg':     lambda msg_id:          inc.lookup('_RESP', msg_id)[0]
    }

# ============================================================================
class GRANITEVersionException(ISIMessageException):
# ----------------------------------------------------------------------------
    """Class for GRANITE Server version exceptions."""
    pass

# ============================================================================
class GRANITEISIMessage(ISIMessage):
# ----------------------------------------------------------------------------
    """Base class for GRANITE Server ISI messages."""
    def __init__(self, **isi_message_fields):
        debug.vrb("GRANITEISIMessage: __init__()")
        ISIMessage.__init__(self, **isi_message_fields)
        self.filler = 0
        self.continue_flag = False

        self.initDefaults(
            resource = inc.PN_PRIVATE)

        self.assertFields(
            resource = inc.PN_PRIVATE)

# ----------------------------------------------------------------------------
def grnISIResp(phone, **isi_message_fields):
    """Function for GRANITE Server ISI response messages.

       Checks ISI message's msg_id and gives the message to the right
       GRANITE ISI message response class.
    """
    debug.vrb("----grnISIResp()----")
    grnISIMessageResp = ISIMessage(**isi_message_fields)

    assert grnISIMessageResp.msg_id != inc.GRN_DISPLAY_UPDATE_NTF, \
        'Fatal error: GRN_DISPLAY_UPDATE_NTF received in test execution!'

    if grnISIMessageResp.msg_id == inc.GRN_STATUS_RESP:
        debug.vrb("grnISIResp() --> GRNStatusResp")
        return GRNStatusResp(**isi_message_fields)
    elif grnISIMessageResp.msg_id == inc.GRN_TEST_RESP:
        debug.vrb("grnISIResp() --> GRNTestResp")
        return GRNTestResp(**isi_message_fields)
    elif grnISIMessageResp.msg_id == inc.GRN_TEST_NTF:
        debug.vrb("grnISIResp() --> GRNTestNtf")
        return GRNTestNtf(**isi_message_fields)
    elif grnISIMessageResp.msg_id == inc.GRN_RESULT_RESP:
        debug.vrb("grnISIResp() --> GRNResultResp")
        return GRNResultResp(**isi_message_fields)
    elif grnISIMessageResp.msg_id == inc.GRN_ABORT_RESP:
        debug.vrb("grnISIResp() --> GRNAbortResp")
        return GRNAbortResp(**isi_message_fields)
    elif grnISIMessageResp.msg_id == inc.GRN_CLEAR_RESP:
        debug.vrb("grnISIResp() --> GRNClearResp")
        return GRNClearResp(**isi_message_fields)
    elif grnISIMessageResp.msg_id == inc.GRN_TERM_RESP:
        debug.vrb("grnISIResp() --> GRNTermResp")
        return GRNTermResp(**isi_message_fields)
    elif grnISIMessageResp.msg_id == inc.GRN_CLEAR_TESTCASE_RESP:
        debug.vrb("grnISIResp() --> GRNClearTestCaseResp")
        return GRNClearTestCaseResp(**isi_message_fields)
    elif grnISIMessageResp.msg_id == inc.GRN_PROVISIONING_WRITE_RESP:
        debug.vrb("grnISIResp() --> GRNProvisioningWriteResp")
        return GRNProvisioningWriteResp(**isi_message_fields)
    elif grnISIMessageResp.msg_id == inc.GRN_PROVISIONING_DELETE_RESP:
        debug.vrb("grnISIResp() --> GRNCProvisioningDeleteResp")
        return GRNProvisioningDeleteResp(**isi_message_fields)
    elif grnISIMessageResp.msg_id == inc.GRN_PROVISIONING_SELECT_RESP:
        debug.vrb("grnISIResp() --> GRNProvisioningSelectResp")
        return GRNProvisioningSelectResp(**isi_message_fields)
    elif grnISIMessageResp.msg_id == inc.GRN_PROVISIONING_READ_RESP:
        debug.vrb("grnISIResp() --> GRNProvisioningReadResp")
        return GRNProvisioningReadResp(**isi_message_fields)

    # unknown message received, check sender
    if grnISIMessageResp.send_obj == phone.objectId:

        # msg id is in msg_data[1] in requests that are returned
        # back to the sender
        if len(grnISIMessageResp.msg_data) > 1 and \
           grnISIMessageResp.msg_data[1] in \
           [inc.GRN_STATUS_REQ, inc.GRN_TEST_REQ, inc.GRN_RESULT_REQ,
           inc.GRN_ABORT_REQ, inc.GRN_CLEAR_REQ, inc.GRN_TERM_REQ,
           inc.GRN_CLEAR_TESTCASE_REQ]:
            errorMessage = 'Request to Granite server was returned back to sender. ' \
                           'This is probably a result of a phone reset during test execution.'

            debug.err(errorMessage)
            debug.vrb('Received message: %s' % str(grnISIMessageResp))
            # try to reactivate Granite server so that we get propably changed object id
            # (connection is also ensured inside the function)
            phone.activateGraniteServer(forced = True)
            raise TestException(errorMessage, phone)
        else:
            debug.out('Unknown message received from GRANITE Server: %s' % \
                      str(grnISIMessageResp))

            raise TestException('Request to Granite server was returned back to sender. ' \
                                'This is probably a result of a phone UI freeze.', phone)
    else:
        debug.err('Unknown message received!')
        raise ISIMessageException(grnISIMessageResp,
            'Unknown message received: %s' % str(grnISIMessageResp))

# ============================================================================
class GRNStatusReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_STATUS_REQ

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - recv_obj              integer
       - utid                  integer
       - private_id            integer (not an isi field)
    """
    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNStatusReq: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = inc.GRN_STATUS_REQ,
            utid = 1)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_STATUS_REQ)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNStatusReq: _get_msg_id_str()")
        return 'GRN_STATUS_REQ'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNStatusReq: _get_msg_data()")

        # Checking data
        self.failUnless(isinstance(self.msg_id, int) or \
                        isinstance(self.msg_id, long), \
                'Parameter msg_id is not integer in GRN_STATUS_REQ')
        self.failUnless(isinstance(self.recv_obj, int) or \
                        isinstance(self.recv_obj, long), \
                'Parameter recv_obj is not integer in GRN_STATUS_REQ')
        self.failUnless(isinstance(self.utid, int) or \
                        isinstance(self.utid, long), \
                'Parameter utid is not integer in GRN_STATUS_REQ')

        # Packing message
        packed_data = xpack('>HB',
            inc.PN_PRIVATE_GRANITE,
            0)

        return packed_data

# ============================================================================
class GRNStatusResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_STATUS_RESP

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - continue_flag         integer (not an isi field)
       - state                 integer (not an isi field)
       - version_zzz           integer (not an isi field)
       - version_yyy           integer (not an isi field)
       - version_xxx           integer (not an isi field)
       - latest_known_id       integer (not an isi field)
       - old_state             integer (not an isi field)
       - last_tid              integer (not an isi field)
       - err_cause             integer (not an isi field)
       - err_state             integer (not an isi field)
       - err_tid               integer (not an isi field)
       - if_version_zzz        integer (not an isi field)
       - if_version_yyy        integer (not an isi field)
    """
    # own fields from msg_data
    continue_flag = None
    if_version_zzz = None
    if_version_yyy = None
    state = None
    version_zzz = None
    version_yyy = None
    version_xxx = None
    old_state = None
    latest_known_id = None
    last_tid = None
    err_cause = None
    err_state = None
    err_tid = None

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNStatusResp: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_STATUS_RESP)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNStatusResp: _get_msg_id_str()")
        return 'GRN_STATUS_RESP'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNStatusResp: _get_msg_data()")

        # Packing message
        return xpack('>B',
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNStatusResp: _check_set_msg_data()")

        # msg id is in msg_data[1] in requests that are returned
        # back to the sender
        if self.msg_id != inc.GRN_STATUS_RESP and \
           len(new_msg_data) > 1 and \
           new_msg_data[1] == inc.GRN_STATUS_REQ:
            debug.vrb('GRN_STATUS_REQ to GRANITE Server was returned back to sender. ' \
                      'GRANITE Server has not been activated for some reason.')

            return new_msg_data

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_STATUS_RESP,
            'Invalid msg_id: %s in GRN_STATUS_RESP!' % str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 22,
            'GRN_STATUS_RESP msg_data was invalid')

        # take own fields from msg_data
        GRNStatusResp.continue_flag = new_msg_data[2]
        GRNStatusResp.version_zzz = new_msg_data[10]
        GRNStatusResp.version_yyy = new_msg_data[11]
        GRNStatusResp.version_xxx = new_msg_data[12]
        GRNStatusResp.state = new_msg_data[18]
        GRNStatusResp.old_state = new_msg_data[19]
        GRNStatusResp.latest_known_id = \
            xunpack('>H', new_msg_data[20:22])[0]

        # IF version info
        GRNStatusResp.if_version_zzz = new_msg_data[3]
        GRNStatusResp.if_version_yyy = new_msg_data[4]

        # state info
        GRNStatusResp.last_tid = new_msg_data[22]
        GRNStatusResp.err_cause = new_msg_data[23]
        GRNStatusResp.err_state = new_msg_data[24]
        GRNStatusResp.err_tid = new_msg_data[25]

        valid_state_names = [
            'GRN_SERVER_STATE_STARTING',
            'GRN_SERVER_STATE_IDLE',
            'GRN_SERVER_STATE_PARSING',
            'GRN_SERVER_STATE_RUNNING',
            'GRN_SERVER_STATE_ABORTING',
            'GRN_SERVER_STATE_SUSPENDED',
            'GRN_SERVER_STATE_INACTIVE',
            'GRN_SERVER_STATE_REPORTING',
            'GRN_SERVER_STATE_CLEARING',
            'GRN_SERVER_STATE_TERMINATING']

        valid_state_values = _lookupNames(valid_state_names)

        # check that GRANITE Server's state is valid
        self.failFieldUnless('"state check"',
            GRNStatusResp.state in valid_state_values,
            'Invalid state in GRN_STATUS_RESP: %d' % GRNStatusResp.state)

        # if no if versions found, take values from server version
        if GRNStatusResp.if_version_zzz == None and \
           GRNStatusResp.if_version_yyy == None:
            GRNStatusResp.if_version_zzz = GRNStatusResp.version_zzz
            GRNStatusResp.if_version_yyy = GRNStatusResp.version_yyy

        return new_msg_data

# ============================================================================
class GRNTestReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_TEST_REQ

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - recv_obj              integer
       - utid                  integer
       - wbxml_data            wbxml (not an isi field)
       - continue_flag         integer (not an isi field)
       - private_id            integer (not an isi field)
    """
    # own fields to msg_data
    wbxml_data = None
    continue_flag = None

    def __init__(self, wbxml_data, continue_flag, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNTestReq: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = inc.GRN_TEST_REQ,
            utid = 1)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_TEST_REQ)

        # save own fields
        GRNTestReq.wbxml_data = wbxml_data
        GRNTestReq.continue_flag = continue_flag

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNTestReq: _get_msg_id_str()")
        return 'GRN_TEST_REQ'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNTestReq: _get_msg_data()")

        # Checking data
        self.failUnless(isinstance(self.msg_id, int) or \
                        isinstance(self.msg_id, long), \
                'Parameter msg_id is not integer in GRN_TEST_REQ')
        self.failUnless(isinstance(self.recv_obj, int) or \
                        isinstance(self.recv_obj, long), \
                'Parameter recv_obj is not integer in GRN_TEST_REQ')
        self.failUnless(isinstance(self.utid, int) or \
                        isinstance(self.utid, long), \
                'Parameter utid is not integer in GRN_TEST_REQ')
        self.failUnless(isinstance(GRNTestReq.continue_flag, int) or \
                        isinstance(GRNTestReq.continue_flag, long), \
                'Parameter continue_flag is not integer in GRN_TEST_REQ')

        # Packing message
        packed_data = xpack('>HBHBBBH*[',
            inc.PN_PRIVATE_GRANITE,
            GRNTestReq.continue_flag,
            0,
            1,
            inc.GRN_WBXML_REQ_INFO,
            inc.GRN_OPTION_POLLED,
            len(GRNTestReq.wbxml_data) + 4,
            GRNTestReq.wbxml_data)

        return packed_data

# ============================================================================
class GRNTestResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_TEST_RESP

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - utid                  integer
       - msg_id                integer
       - continue_flag         integer (not an isi field)
       - response              integer (not an isi field)
       - cause                 integer (not an isi field)
       - number_of_sub_blocks  integer (not an isi field)
       - sub_block             integer (not an isi field)
       - wbxml_data            wbxml (not an isi field)
    """
    # own fields from msg_data
    continue_flag = None
    response = None
    cause = None
    number_of_sub_blocks = None
    sub_block = None
    wbxml_data = None

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNTestResp: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_TEST_RESP)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNTestResp: _get_msg_id_str()")
        return 'GRN_TEST_RESP'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNTestResp: _get_msg_data()")

        # Packing message
        return xpack('>BB',
            self.utid,
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNTestResp: _check_set_msg_data()")

        # msg id is in msg_data[1] in requests that are returned
        # back to the sender
        if self.msg_id != inc.GRN_TEST_RESP and \
           len(new_msg_data) > 1 and \
           new_msg_data[1] == inc.GRN_TEST_REQ:
            debug.vrb('GRN_TEST_REQ to GRANITE Server was returned back to sender. ' \
                      'GRANITE Server has not been activated for some reason.')

            return new_msg_data

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_TEST_RESP,
            'Invalid msg_id: %s in GRN_TEST_RESP!' % str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 6,
            'GRN_TEST_RESP msg_data was invalid')

        # take own fields from msg_data
        GRNTestResp.continue_flag = new_msg_data[2]
        GRNTestResp.response = new_msg_data[3]
        GRNTestResp.cause = new_msg_data[4]
        GRNTestResp.number_of_sub_blocks = new_msg_data[5]
        if len(new_msg_data) > 6:
            GRNTestResp.sub_block = new_msg_data[6]
        if len(new_msg_data) > 10:
            GRNTestResp.wbxml_data = new_msg_data[10:]
            
        self.failFieldUnless('"cause check"',
            GRNTestResp.cause in _validCauseValues(),
            'Invalid cause in GRN_TEST_RESP: %d' % GRNTestResp.cause)

        return new_msg_data

# ============================================================================
class GRNTestNtf(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_TEST_NTF

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - notify                integer (not an isi field)
    """
    # own fields from msg_data
    notify = None

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNTestNtf: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_TEST_NTF)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNTestNtf: _get_msg_id_str()")
        return 'GRN_TEST_NTF'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNTestNtf: _get_msg_data()")

        # Packing message
        return xpack('>B',
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNTestNtf: _check_set_msg_data()")

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_TEST_NTF,
            'Invalid msg_id: %s in GRN_TEST_NTF!' % str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 6,
            'GRN_TEST_NTF msg_data was invalid')

        # take own fields from msg_data
        GRNTestNtf.notify = new_msg_data[3]

        # check that notify value is valid
        valid_notify_names = [
            'GRN_NTF_NONE',
            'GRN_NTF_PARSE_START',
            'GRN_NTF_PARSE_CONTINUE',
            'GRN_NTF_PARSE_DONE',
            'GRN_NTF_RUN_START',
            'GRN_NTF_RUN_DONE']

        valid_notify_values = _lookupNames(valid_notify_names)

        if not GRNTestNtf.notify in valid_notify_values:
            debug.vrb('Invalid notify in GRN_TEST_NTF: %d' % GRNTestNtf.notify)

        return new_msg_data

# ============================================================================
class GRNResultReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_RESULT_REQ

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - recv_obj              integer
       - utid                  integer
       - index                 integer (not an isi field)
       - data_index_1          integer (not an isi field)
       - data_index_2          integer (not an isi field)
       - data_index_3          integer (not an isi field)
       - data_index_4          integer (not an isi field)
       - private_id            integer (not an isi field)
    """
    # own fields to msg_data
    index = None
    # own fields from msg_data
    data_index_1 = None
    data_index_2 = None
    data_index_3 = None
    data_index_4 = None

    def __init__(self, index, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNResultReq: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = inc.GRN_RESULT_REQ,
            utid = 1)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_RESULT_REQ)

        # save own fields
        GRNResultReq.index = index

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNResultReq: _get_msg_id_str()")
        return 'GRN_RESULT_REQ'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNResultReq: _get_msg_data()")

        # Checking data
        self.failUnless(isinstance(self.msg_id, int) or \
                        isinstance(self.msg_id, long), \
                'Parameter msg_id is not integer in GRN_RESULT_REQ')
        self.failUnless(isinstance(self.recv_obj, int) or \
                        isinstance(self.recv_obj, long), \
                'Parameter recv_obj is not integer in GRN_RESULT_REQ')
        self.failUnless(isinstance(self.utid, int) or \
                        isinstance(self.utid, long), \
                'Parameter utid is not integer in GRN_RESULT_REQ')
        self.failUnless(isinstance(GRNResultReq.index, int) or \
                        isinstance(GRNResultReq.index, long), \
                'Parameter index is not integer in GRN_RESULT_REQ')

        # Packing message
        packed_data = xpack('>HBHBBBHL',
            inc.PN_PRIVATE_GRANITE,
            0,
            0,
            1,
            inc.GRN_INDEX_INFO,
            0,
            8,
            GRNResultReq.index)

        # take own fields from msg_data
        GRNResultReq.data_index_1 = packed_data[10]
        GRNResultReq.data_index_2 = packed_data[11]
        GRNResultReq.data_index_3 = packed_data[12]
        GRNResultReq.data_index_4 = packed_data[13]

        return packed_data

# ============================================================================
class GRNResultResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_RESULT_RESP

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - utid                  integer
       - msg_id                integer
       - response              integer (not an isi field)
       - cause                 integer (not an isi field)
       - number_of_sub_blocks  integer (not an isi field)
       - sub_block             integer (not an isi field)
       - data_index_1          integer (not an isi field)
       - data_index_2          integer (not an isi field)
       - data_index_3          integer (not an isi field)
       - data_index_4          integer (not an isi field)
       - end_of_data           integer (not an isi field)
       - message_check_1       integer (not an isi field)
       - message_check_2       integer (not an isi field)
       - wbxml_data            wbxml (not an isi field)
    """
    # own fields from msg_data
    response = None
    cause = None
    number_of_sub_blocks = None
    sub_block = None
    data_index_1 = None
    data_index_2 = None
    data_index_3 = None
    data_index_4 = None
    end_of_data = None
    message_check_1 = None
    message_check_2 = None
    wbxml_data = None

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNResultResp: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_RESULT_RESP)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNResultResp: _get_msg_id_str()")
        return 'GRN_RESULT_RESP'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNResultResp: _get_msg_data()")

        # Packing message
        return xpack('>BB',
            self.utid,
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNResultResp: _check_set_msg_data()")

        # msg id is in msg_data[1] in requests that are returned
        # back to the sender
        if self.msg_id != inc.GRN_RESULT_RESP and \
           len(new_msg_data) > 1 and \
           new_msg_data[1] == inc.GRN_RESULT_REQ:
            debug.vrb('GRN_RESULT_REQ to GRANITE Server was returned back to sender. ' \
                      'GRANITE Server has not been activated for some reason.')

            return new_msg_data

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_RESULT_RESP,
            'Invalid msg_id: %s in GRN_RESULT_RESP!' % str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 19,
            'GRN_RESULT_RESP msg_data was invalid')

        # take own fields from msg_data
        GRNResultResp.response = new_msg_data[3]
        GRNResultResp.cause = new_msg_data[4]
        GRNResultResp.number_of_sub_blocks = new_msg_data[5]
        GRNResultResp.sub_block = new_msg_data[6]
        GRNResultResp.data_index_1 = new_msg_data[10]
        GRNResultResp.data_index_2 = new_msg_data[11]
        GRNResultResp.data_index_3 = new_msg_data[12]
        GRNResultResp.data_index_4 = new_msg_data[13]
        GRNResultResp.end_of_data = new_msg_data[15]
        GRNResultResp.message_check_1 = new_msg_data[16]
        GRNResultResp.message_check_2 = new_msg_data[17]
        GRNResultResp.wbxml_data = new_msg_data[18:]

        self.failFieldUnless('"message lenght check"',
            len(GRNResultResp.wbxml_data) + 4 == \
            GRNResultResp.message_check_1 * 256 + GRNResultResp.message_check_2,
            'Invalid message lenght in GRN_RESULT_RESP: %d' % \
            len(GRNResultResp.wbxml_data))

        self.failFieldUnless('"cause check"',
            GRNResultResp.cause in _validCauseValues(),
            'Invalid cause in GRN_RESULT_RESP: %d' % GRNResultResp.cause)

        return new_msg_data

# ============================================================================
class GRNAbortReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_ABORT_REQ

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - recv_obj              integer
       - utid                  integer
       - private_id            integer (not an isi field)
    """
    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNAbortReq: __init__()")

        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = inc.GRN_ABORT_REQ,
            utid = 1)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_ABORT_REQ)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNAbortReq: _get_msg_id_str()")
        return 'GRN_ABORT_REQ'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNAbortReq: _get_msg_data()")

        # Checking data
        self.failUnless(isinstance(self.msg_id, int) or \
                        isinstance(self.msg_id, long), \
                'Parameter msg_id is not integer in GRN_ABORT_REQ')
        self.failUnless(isinstance(self.recv_obj, int) or \
                        isinstance(self.recv_obj, long), \
                'Parameter recv_obj is not integer in GRN_ABORT_REQ')
        self.failUnless(isinstance(self.utid, int) or \
                        isinstance(self.utid, long), \
                'Parameter utid is not integer in GRN_ABORT_REQ')

        # Packing message
        packed_data = xpack('>HB',
            inc.PN_PRIVATE_GRANITE,
            0)

        return packed_data
    
# ============================================================================
class GRNAbortResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_ABORT_RESP

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - response              integer (not an isi field)
       - cause                 integer (not an isi field)
    """
    # own fields from msg_data
    response = None
    cause = None

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNAbortResp: __init__()")

        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_ABORT_RESP)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNAbortResp: _get_msg_id_str()")
        return 'GRN_ABORT_RESP'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNAbortResp: _get_msg_data()")

        # Packing message
        return xpack('>B',
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNAbortResp: _check_set_msg_data()")

        # msg id is in msg_data[1] in requests that are returned
        # back to the sender
        if self.msg_id != inc.GRN_ABORT_RESP and \
           len(new_msg_data) > 1 and \
           new_msg_data[1] == inc.GRN_ABORT_REQ:
            debug.vrb('GRN_ABORT_REQ to GRANITE Server was returned back to sender. ' \
                      'GRANITE Server has not been activated for some reason.')

            return new_msg_data

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_ABORT_RESP,
            'Invalid msg_id: %s in GRN_ABORT_RESP!' % str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 6,
            'GRN_ABORT_RESP msg_data was invalid')

        # take own fields from msg_data
        GRNAbortResp.response = new_msg_data[3]
        GRNAbortResp.cause = new_msg_data[4]

        self.failFieldUnless('"cause check"',
            GRNAbortResp.cause in _validCauseValues(),
            'Invalid cause in GRN_ABORT_RESP: %d' % GRNAbortResp.cause)

        return new_msg_data

# ============================================================================
class GRNTermReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_TERM_REQ

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - recv_obj              integer
       - utid                  integer
       - private_id            integer (not an isi field)
    """
    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNTermReq: __init__()")

        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = inc.GRN_TERM_REQ,
            utid = 1)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_TERM_REQ)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNTermReq: _get_msg_id_str()")
        return 'GRN_TERM_REQ'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNTermReq: _get_msg_data()")

        # Checking data
        self.failUnless(isinstance(self.msg_id, int) or \
                        isinstance(self.msg_id, long), \
                'Parameter msg_id is not integer in GRN_TERM_REQ')
        self.failUnless(isinstance(self.recv_obj, int) or \
                        isinstance(self.recv_obj, long), \
                'Parameter recv_obj is not integer in GRN_TERM_REQ')
        self.failUnless(isinstance(self.utid, int) or \
                        isinstance(self.utid, long), \
                'Parameter utid is not integer in GRN_TERM_REQ')

        # Packing message
        packed_data = xpack('>HB',
            inc.PN_PRIVATE_GRANITE,
            0)

        return packed_data

# ============================================================================
class GRNTermResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_TERM_RESP

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - response              integer (not an isi field)
       - cause                 integer (not an isi field)
    """
    # own fields from msg_data
    response = None
    cause = None

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNTermResp: __init__()")

        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_TERM_RESP)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNTermResp: _get_msg_id_str()")
        return 'GRN_TERM_RESP'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNTermResp: _get_msg_data()")

        # Packing message
        return xpack('>B',
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNTermResp: _check_set_msg_data()")

        # msg id is in msg_data[1] in requests that are returned
        # back to the sender
        if self.msg_id != inc.GRN_TERM_RESP and \
           len(new_msg_data) > 1 and \
           new_msg_data[1] == inc.GRN_TERM_REQ:
            debug.vrb('GRN_TERM_REQ to GRANITE Server was returned back to sender. ' \
                      'GRANITE Server has not been activated for some reason.')

            return new_msg_data

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_TERM_RESP,
            'Invalid msg_id: %s in GRN_TERM_RESP!' % str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 6,
            'GRN_TERM_RESP msg_data was invalid')

        # take own fields from msg_data
        GRNTermResp.response = new_msg_data[3]
        GRNTermResp.cause = new_msg_data[4]

        self.failFieldUnless('"cause check"',
            GRNTermResp.cause in _validCauseValues(),
            'Invalid cause in GRN_TERM_RESP: %d' % GRNTermResp.cause)

        return new_msg_data

# ============================================================================
class GRNClearReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_CLEAR_REQ

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - recv_obj              integer
       - utid                  integer
       - private_id            integer (not an isi field)
    """
    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNClearReq: __init__()")

        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = inc.GRN_CLEAR_REQ,
            utid = 1)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_CLEAR_REQ)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNClearReq: _get_msg_id_str()")
        return 'GRN_CLEAR_REQ'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNClearReq: _get_msg_data()")

        # Checking data
        self.failUnless(isinstance(self.msg_id, int) or \
                        isinstance(self.msg_id, long), \
                'Parameter msg_id is not integer in GRN_CLEAR_REQ')
        self.failUnless(isinstance(self.recv_obj, int) or \
                        isinstance(self.recv_obj, long), \
                'Parameter recv_obj is not integer in GRN_CLEAR_REQ')
        self.failUnless(isinstance(self.utid, int) or \
                        isinstance(self.utid, long), \
                'Parameter utid is not integer in GRN_CLEAR_REQ')

        # Packing message
        packed_data = xpack('>HB',
            inc.PN_PRIVATE_GRANITE,
            0)

        return packed_data

# ============================================================================
class GRNClearResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_CLEAR_RESP

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - response              integer (not an isi field)
       - cause                 integer (not an isi field)
    """
    # own fields from msg_data
    response = None
    cause = None

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNClearResp: __init__()")

        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_CLEAR_RESP)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNClearResp: _get_msg_id_str()")
        return 'GRN_CLEAR_RESP'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNClearResp: _get_msg_data()")

        # Packing message
        return xpack('>B',
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNClearResp: _check_set_msg_data()")

        # msg id is in msg_data[1] in requests that are returned
        # back to the sender
        if self.msg_id != inc.GRN_CLEAR_RESP and \
           len(new_msg_data) > 1 and \
           new_msg_data[1] == inc.GRN_CLEAR_REQ:
            debug.vrb('GRN_CLEAR_REQ to GRANITE Server was returned back to sender. ' \
                      'GRANITE Server has not been activated for some reason.')

            return new_msg_data

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_CLEAR_RESP,
            'Invalid msg_id: %s in GRN_CLEAR_RESP!' % str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 6,
            'GRN_CLEAR_RESP msg_data was invalid')

        # take own fields from msg_data
        GRNClearResp.response = new_msg_data[3]
        GRNClearResp.cause = new_msg_data[4]

        self.failFieldUnless('"cause check"',
            GRNClearResp.cause in _validCauseValues(),
            'Invalid cause in GRN_CLEAR_RESP: %d' % GRNClearResp.cause)

        return new_msg_data

# ============================================================================
class GRNClearTestCaseReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_CLEAR_TESTCASE_REQ

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - recv_obj              integer
       - utid                  integer
       - private_id            integer (not an isi field)
    """
    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNClearTestCaseReq: __init__()")

        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = inc.GRN_CLEAR_TESTCASE_REQ,
            utid = 1)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_CLEAR_TESTCASE_REQ)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNClearTestCaseReq: _get_msg_id_str()")
        return 'GRN_CLEAR_TESTCASE_REQ'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNClearTestCaseReq: _get_msg_data()")

        # Checking data
        self.failUnless(isinstance(self.msg_id, int) or \
                        isinstance(self.msg_id, long), \
                'Parameter msg_id is not integer in GRN_CLEAR_TESTCASE_REQ')
        self.failUnless(isinstance(self.recv_obj, int) or \
                        isinstance(self.recv_obj, long), \
                'Parameter recv_obj is not integer in GRN_CLEAR_TESTCASE_REQ')
        self.failUnless(isinstance(self.utid, int) or \
                        isinstance(self.utid, long), \
                'Parameter utid is not integer in GRN_CLEAR_TESTCASE_REQ')

        # Packing message
        packed_data = xpack('>HB',
            inc.PN_PRIVATE_GRANITE,
            0)

        return packed_data

# ============================================================================
class GRNClearTestCaseResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_CLEAR_TESTCASE_RESP

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - response              integer (not an isi field)
       - cause                 integer (not an isi field)
    """
    # own fields from msg_data
    response = None
    cause = None

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNClearTestCaseResp: __init__()")

        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_CLEAR_TESTCASE_RESP)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNClearTestCaseResp: _get_msg_id_str()")
        return 'GRN_CLEAR_TESTCASE_RESP'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNClearTestCaseResp: _get_msg_data()")

        # Packing message
        return xpack('>B',
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNClearTestCaseResp: _check_set_msg_data()")

        # msg id is in msg_data[1] in requests that are returned
        # back to the sender
        if self.msg_id != inc.GRN_CLEAR_TESTCASE_RESP and \
           len(new_msg_data) > 1 and \
           new_msg_data[1] == inc.GRN_CLEAR_TESTCASE_REQ:
            debug.vrb('GRN_CLEAR_TESTCASE_REQ to GRANITE Server was returned back to sender. ' \
                      'GRANITE Server has not been activated for some reason.')

            return new_msg_data

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_CLEAR_TESTCASE_RESP,
            'Invalid msg_id: %s in GRN_CLEAR_TESTCASE_RESP!' % \
                str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 6,
            'GRN_CLEAR_TESTCASE_RESP msg_data was invalid')

        # take own fields from msg_data
        GRNClearTestCaseResp.response = new_msg_data[3]
        GRNClearTestCaseResp.cause = new_msg_data[4]

        self.failFieldUnless('"cause check"',
            GRNClearTestCaseResp.cause in _validCauseValues(),
            'Invalid cause in GRN_CLEAR_TESTCASE_RESP: %d' % \
                GRNClearTestCaseResp.cause)

        return new_msg_data

# ============================================================================
class GRN_ISM_WriteSettingReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    def __init__(self, **isi_message_fields):
        """Initialize message."""
        GRANITEISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id = inc.GRN_ISM_API_WRITE_REQ,
                           utid = 1,
                          sub_block_nbr = 1)

    def _get_msg_id_str(self):
        return inc_lookups['req_msg'](self.msg_id)

    def _get_msg_data_str(self):
        return 'setting_name: %s, setting_id: %s, setting_value: %s' % \
                    (self.setting_name, self.setting_id, self.setting_value)

    def _get_pack_setting_value(self):
        if isinstance(self.setting_value, bool) and \
           self.sb_id == inc.GRN_ISM_API_BOOL_SETTING:
            sb_data = xpack('>BBHBBBB', self.sb_id, self.filler, 8,
                    self.setting_value, self.filler, self.filler, self.filler)
        elif isinstance(self.setting_value, (int, long)) and \
             self.sb_id in [inc.GRN_ISM_API_ENUM_SETTING,
                            inc.GRN_ISM_API_INT32_SETTING,
                            inc.GRN_ISM_API_FIM_ID_SETTING]:
            sb_data = xpack('>BBHL', self.sb_id, self.filler, 8, self.setting_value)
        elif isinstance(self.setting_value, (str, unicode)) and \
             self.sb_id in [inc.GRN_ISM_API_UCS2_STRING_SETTING,
                            inc.GRN_ISM_API_FILEPATH_SETTING]:
            sb_data = xpack('>BBHH', self.sb_id, self.filler, 0, 0)
            # pack setting string
            str_data = map(ord, self.setting_value.encode('UTF-16-BE')) + [0, 0]
            # add padding
            count = (4 - (len(sb_data) + len(str_data)) % 4) % 4
            str_data += xpack('>*[', [0] * count)
            # add string data
            sb_data += str_data
            # sub block length, value length
            sb_data[2:6] = xpack('>HH', len(sb_data), len(self.setting_value) + 1)
        else:
            assert 0, 'Mismatching ISA setting type/value!'

        return sb_data

    def _get_msg_data(self):
        msg_data = xpack('>HBBBBLBBBB', inc.PN_PRIVATE_GRANITE,
                         self.continue_flag, self.filler,
                         self.filler, self.filler, self.setting_id, self.filler,
                         self.filler, self.filler, self.sub_block_nbr)
        # pack setting value sub block
        msg_data += self.pack_setting_value

        return msg_data

# ============================================================================
class GRN_ISM_WriteSettingResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    def __init__(self, **isi_message_fields):
        GRANITEISIMessage.__init__(self, **isi_message_fields)
        self.assertFields(msg_id = inc.GRN_ISM_API_WRITE_RESP)

    def _get_msg_id_str(self):
        return inc_lookups['resp_msg'](self.msg_id)

    def _get_msg_data_str(self):
        return 'response: %s' % self.response

    def _get_unpack_setting_value(self):
        self.sb_id, sb_data = xunpack('>B*[', self.sb_msg_data)

        if self.sb_id == inc.GRN_ISM_API_BOOL_SETTING:
            self.filler, self.sb_length, self.setting_value, self.filler, \
                        self.filler, self.filler = xunpack('>BHBBBB', sb_data)
            self.setting_value = bool(self.setting_value)
        elif self.sb_id in [inc.GRN_ISM_API_ENUM_SETTING,
                            inc.GRN_ISM_API_INT32_SETTING,
                            inc.GRN_ISM_API_FIM_ID_SETTING]:
            self.filler, self.sb_length, \
                                self.setting_value = xunpack('>BHL', sb_data)
        elif self.sb_id in [inc.GRN_ISM_API_UCS2_STRING_SETTING,
                            inc.GRN_ISM_API_FILEPATH_SETTING]:
            self.filler, self.sb_length, self.value_length, \
                            self.setting_value = xunpack('>BHH*[', sb_data)
            self.setting_value = ''.join(map(chr, self.setting_value)). \
                                            decode('UTF-16-BE').rstrip('\0')

    def _check_set_msg_data(self, new_msg_data):
        self.private_id, self.continue_flag, \
                self.response, self.sub_block_nbr, self.sb_msg_data = \
                                                xunpack('>HBBB*[', new_msg_data)

        if self.sub_block_nbr >= 1:
            self.unpack_setting_value

        return new_msg_data

# ============================================================================
class GRN_ISM_ReadSettingReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    def __init__(self, **isi_message_fields):
        """Initialize message."""
        GRANITEISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id = inc.GRN_ISM_API_READ_REQ,
                          utid = 1,
                          setting_value = 0, sub_block_nbr = 1)

    def _get_msg_id_str(self):
        return inc_lookups['req_msg'](self.msg_id)

    def _get_msg_data_str(self):
        return 'setting_name: %s, setting_id: %s' % \
                                        (self.setting_name, self.setting_id)

    def _get_pack_setting_value(self):
        sb_data = []
        if self.sb_id == inc.GRN_ISM_API_BOOL_SETTING:
            sb_data = xpack('>BBHBBBB', self.sb_id, self.filler, 8,
                    self.setting_value, self.filler, self.filler, self.filler)
        elif self.sb_id in [inc.GRN_ISM_API_ENUM_SETTING,
                            inc.GRN_ISM_API_INT32_SETTING,
                            inc.GRN_ISM_API_FIM_ID_SETTING]:
            sb_data = xpack('>BBHL', self.sb_id, self.filler, 8,
                                     self.setting_value)
        elif self.sb_id in [inc.GRN_ISM_API_UCS2_STRING_SETTING,
                            inc.GRN_ISM_API_FILEPATH_SETTING]:
            sb_data = xpack('>BBHHBB', self.sb_id, self.filler, 8, 0,
                                       self.filler, self.filler)

        return sb_data

    def _get_msg_data(self):
        msg_data = xpack('>HBBBBLBBBB', inc.PN_PRIVATE_GRANITE,
                         self.continue_flag, self.filler,
                         self.filler, self.filler, self.setting_id,
                         self.filler, self.filler, self.filler,
                         self.sub_block_nbr)

        # pack setting value sub block
        msg_data += self.pack_setting_value

        return msg_data

# ============================================================================
class GRN_ISM_ReadSettingResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    def __init__(self, **isi_message_fields):
        GRANITEISIMessage.__init__(self, **isi_message_fields)
        self.assertFields(msg_id = inc.GRN_ISM_API_READ_RESP)

    def _get_msg_id_str(self):
        return inc_lookups['resp_msg'](self.msg_id)

    def _get_msg_data_str(self):
        return 'response: %s, setting_name: %s, setting_id: %s, ' \
               'setting_value: %s' % (self.response, self.setting_name,
                                      self.setting_id, self.setting_value)

    def _get_unpack_setting_value(self):
        self.sb_id, sb_data = xunpack('>B*[', self.sb_msg_data)

        if self.sb_id == inc.GRN_ISM_API_BOOL_SETTING:
            self.filler, self.sb_length, self.setting_value, self.filler, \
                        self.filler, self.filler = xunpack('>BHBBBB', sb_data)
            self.setting_value = bool(self.setting_value)
        elif self.sb_id in [inc.GRN_ISM_API_ENUM_SETTING,
                            inc.GRN_ISM_API_INT32_SETTING,
                            inc.GRN_ISM_API_FIM_ID_SETTING]:
            self.filler, self.sb_length, \
                                self.setting_value = xunpack('>BHL', sb_data)
        elif self.sb_id in [inc.GRN_ISM_API_UCS2_STRING_SETTING,
                            inc.GRN_ISM_API_FILEPATH_SETTING]:
            self.filler, self.sb_length, self.value_length, \
                            self.setting_value = xunpack('>BHH*[', sb_data)
            self.setting_value = ''.join(map(chr, self.setting_value)). \
                                            decode('UTF-16-BE').rstrip('\0')

    def _check_set_msg_data(self, new_msg_data):
        self.private_id, self.continue_flag, \
            self.response, self.filler, self.sub_block_nbr, \
                        self.sb_msg_data = xunpack('>HBBBB*[', new_msg_data)

        if self.sub_block_nbr >= 1:
            self.unpack_setting_value

        return new_msg_data

# ============================================================================
class GRNResetPhoneReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_RESET_PHONE_REQ

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - recv_obj              integer
       - utid                  integer
       - private_id            integer (not an isi field)
	   - reset_reason		   byte
    """
    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNResetPhoneReq: __init__()")

        GRANITEISIMessage.__init__(self, **isi_message_fields)

        # get reset reason, or use default HW_RESET_SW_RESET_REQUESTED = 4
        self.reset_reason = isi_message_fields.get('reset_reason', 4)

        self.initDefaults(
            msg_id = inc.GRN_RESET_PHONE_REQ,
            utid = 1)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_RESET_PHONE_REQ)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNResetPhoneReq: _get_msg_id_str()")
        return 'GRN_RESET_PHONE_REQ'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNResetPhoneReq: _get_msg_data()")

        # Checking data
        self.failUnless(isinstance(self.msg_id, int) or \
                        isinstance(self.msg_id, long), \
                'Parameter msg_id is not integer in GRN_RESET_PHONE_REQ')
        self.failUnless(isinstance(self.recv_obj, int) or \
                        isinstance(self.recv_obj, long), \
                'Parameter recv_obj is not integer in GRN_RESET_PHONE_REQ')
        self.failUnless(isinstance(self.utid, int) or \
                        isinstance(self.utid, long), \
                'Parameter utid is not integer in GRN_RESET_PHONE_REQ')

        # Packing message
        packed_data = xpack('>HBB',
            inc.PN_PRIVATE_GRANITE,
            0,
            self.reset_reason)

        return packed_data        
        

# ============================================================================
class GRNDisplayUpdateNtf(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_DISPLAY_UPDATE_NTF

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - utid                  integer
       - msg_id                integer
       - private_id            long
       - continue_flag         integer (not an isi field)
       - x                     integer (not an isi field)
       - y                     integer (not an isi field)
       - width                 integer (not an isi field)
       - height                integer (not an isi field)
       - time_stamp            integer (not an isi field)
       - fps                   integer (not an isi field)
       - type                  char    (not an isi field)
    """
    # own fields from msg_data
    x = None
    y = None
    width = None
    height = None
    time_stamp = None
    fps = None
    type = ""

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNDisplayUpdateNtf: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_DISPLAY_UPDATE_NTF)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNDisplayUpdateNtf: _get_msg_id_str()")
        return 'GRN_DISPLAY_UPDATE_NTF'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNDisplayUpdateNtf: _get_msg_data()")

        # Packing message
        return xpack('>BB',
            self.utid,
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNDisplayUpdateNtf: _check_set_msg_data()")

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_DISPLAY_UPDATE_NTF,
            'Invalid msg_id: %s in GRN_DISPLAY_UPDATE_NTF!' % str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 20,
            'GRN_DISPLAY_UPDATE_NTF msg_data was invalid')

        # take own fields from msg_data
        GRNDisplayUpdateNtf.x, GRNDisplayUpdateNtf.y, GRNDisplayUpdateNtf.width, GRNDisplayUpdateNtf.height, \
        GRNDisplayUpdateNtf.fps, GRNDisplayUpdateNtf.time_stamp, typeStringData = \
            xunpack('>HHHHHL*[', new_msg_data[4:])

        GRNDisplayUpdateNtf.type = ""

        # create type string
        for typeChar in typeStringData:
            if typeChar > 0:
                GRNDisplayUpdateNtf.type += chr(typeChar)

        return new_msg_data

# ============================================================================
class GRNProvisioningDeleteReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_PROVISIONING_DELETE_REQ

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - recv_obj              integer
       - utid                  integer
       - private_id            integer (not an isi field)
       - continue_flag         integer (not an isi field)
       - delete_all            integer (not an isi field)
       - configuration_context integer (not an isi field)
       - sim_id                integer (not an isi field)
    """
    def __init__(self, continue_flag, delete_all, configuration_context, sim_id, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNProvisioningDeleteReq: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = inc.GRN_PROVISIONING_DELETE_REQ,
            utid = 1)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_PROVISIONING_DELETE_REQ)

        GRNProvisioningDeleteReq.continue_flag = continue_flag
        GRNProvisioningDeleteReq.delete_all = delete_all
        GRNProvisioningDeleteReq.configuration_context = configuration_context
        GRNProvisioningDeleteReq.sim_id = sim_id

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNProvisioningDeleteReq: _get_msg_id_str()")
        return 'GRN_PROVISIONING_DELETE_REQ'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNProvisioningDeleteReq: _get_msg_data()")

        # Checking data
        self.failUnless(isinstance(self.msg_id, int) or \
                        isinstance(self.msg_id, long), \
                'Parameter msg_id is not integer in GRN_PROVISIONING_DELETE_REQ')
        self.failUnless(isinstance(self.recv_obj, int) or \
                        isinstance(self.recv_obj, long), \
                'Parameter recv_obj is not integer in GRN_PROVISIONING_DELETE_REQ')
        self.failUnless(isinstance(self.utid, int) or \
                        isinstance(self.utid, long), \
                'Parameter utid is not integer in GRN_PROVISIONING_DELETE_REQ')
        self.failUnless(isinstance(GRNProvisioningDeleteReq.continue_flag, int) or \
                        isinstance(GRNProvisioningDeleteReq.continue_flag, long), \
                'Parameter continue_flag is not integer in GRN_PROVISIONING_DELETE_REQ')
        self.failUnless(isinstance(GRNProvisioningDeleteReq.delete_all, int) or \
                        isinstance(GRNProvisioningDeleteReq.delete_all, long), \
                'Parameter delete_all is not integer in GRN_PROVISIONING_DELETE_REQ')
        self.failUnless(isinstance(GRNProvisioningDeleteReq.configuration_context, int) or \
                        isinstance(GRNProvisioningDeleteReq.configuration_context, long), \
                'Parameter configuration_context is not integer in GRN_PROVISIONING_DELETE_REQ')
        self.failUnless(isinstance(GRNProvisioningDeleteReq.sim_id, int) or \
                        isinstance(GRNProvisioningDeleteReq.sim_id, long), \
                'Parameter sim_id is not integer in GRN_PROVISIONING_DELETE_REQ')

        # Packing message
        packed_data = xpack('>HBBHB',
            inc.PN_PRIVATE_GRANITE,
            GRNProvisioningDeleteReq.continue_flag,
            GRNProvisioningDeleteReq.delete_all,
            GRNProvisioningDeleteReq.configuration_context,
            GRNProvisioningDeleteReq.sim_id)

        return packed_data

# ============================================================================
class GRNProvisioningDeleteResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_PROVISIONING_DELETE_RESP

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - response              integer (not an isi field)
    """
    # own fields from msg_data
    response = None

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNProvisioningDeleteResp: __init__()")

        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_PROVISIONING_DELETE_RESP)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNProvisioningDeleteResp: _get_msg_id_str()")
        return 'GRN_PROVISIONING_DELETE_RESP'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNProvisioningDeleteResp: _get_msg_data()")

        # Packing message
        return xpack('>B',
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNProvisioningDeleteResp: _check_set_msg_data()")

        # msg id is in msg_data[1] in requests that are returned
        # back to the sender
        if self.msg_id != inc.GRN_PROVISIONING_DELETE_RESP and \
           len(new_msg_data) > 1 and \
           new_msg_data[1] == inc.GRN_PROVISIONING_DELETE_REQ:
            debug.vrb('GRN_PROVISIONING_DELETE_REQ to GRANITE Server was returned back to sender. ' \
                      'GRANITE Server has not been activated for some reason.')

            return new_msg_data

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_PROVISIONING_DELETE_RESP,
            'Invalid msg_id: %s in GRN_PROVISIONING_DELETE_RESP!' % str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 4,
            'GRN_PROVISIONING_DELETE_RESP msg_data was invalid')

        # take own fields from msg_data
        GRNProvisioningDeleteResp.response = new_msg_data[3]

        return new_msg_data

# ============================================================================
class GRNProvisioningReadReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_PROVISIONING_READ_REQ

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - recv_obj              integer
       - utid                  integer
       - private_id            integer (not an isi field)
       - continue_flag         integer (not an isi field)
       - configuration_context integer (not an isi field)
       - sim_id                integer (not an isi field)
    """
    def __init__(self, continue_flag, configuration_context, sim_id, data_type, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNProvisioningReadReq: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = inc.GRN_PROVISIONING_READ_REQ,
            utid = 1)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_PROVISIONING_READ_REQ)

        GRNProvisioningReadReq.continue_flag = continue_flag
        GRNProvisioningReadReq.configuration_context = configuration_context
        GRNProvisioningReadReq.sim_id = sim_id
        GRNProvisioningReadReq.data_type = data_type

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNProvisioningReadReq: _get_msg_id_str()")
        return 'GRN_PROVISIONING_READ_REQ'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNProvisioningReadReq: _get_msg_data()")

        # Checking data
        self.failUnless(isinstance(self.msg_id, int) or \
                        isinstance(self.msg_id, long), \
                'Parameter msg_id is not integer in GRN_PROVISIONING_READ_REQ')
        self.failUnless(isinstance(self.recv_obj, int) or \
                        isinstance(self.recv_obj, long), \
                'Parameter recv_obj is not integer in GRN_PROVISIONING_READ_REQ')
        self.failUnless(isinstance(self.utid, int) or \
                        isinstance(self.utid, long), \
                'Parameter utid is not integer in GRN_PROVISIONING_READ_REQ')
        self.failUnless(isinstance(GRNProvisioningReadReq.continue_flag, int) or \
                        isinstance(GRNProvisioningReadReq.continue_flag, long), \
                'Parameter continue_flag is not integer in GRN_PROVISIONING_READ_REQ')
        self.failUnless(isinstance(GRNProvisioningReadReq.configuration_context, int) or \
                        isinstance(GRNProvisioningReadReq.configuration_context, long), \
                'Parameter configuration_context is not integer in GRN_PROVISIONING_READ_REQ')
        self.failUnless(isinstance(GRNProvisioningReadReq.sim_id, int) or \
                        isinstance(GRNProvisioningReadReq.sim_id, long), \
                'Parameter sim_id is not integer in GRN_PROVISIONING_READ_REQ')
        self.failUnless(isinstance(GRNProvisioningReadReq.data_type, int) or \
                        isinstance(GRNProvisioningReadReq.data_type, long), \
                'Parameter data_type is not integer in GRN_PROVISIONING_READ_REQ')

        # Packing message
        packed_data = xpack('>HBBHB',
            inc.PN_PRIVATE_GRANITE,
            GRNProvisioningReadReq.continue_flag,
            GRNProvisioningReadReq.sim_id,
            GRNProvisioningReadReq.configuration_context,
            GRNProvisioningReadReq.data_type)

        return packed_data

# ============================================================================
class GRNProvisioningReadResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_PROVISIONING_READ_RESP

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - utid                  integer
       - msg_id                integer
       - response              integer (not an isi field)
       - data                  list [int] (not an isi field)
    """
    # own fields from msg_data
    response = None
    number_of_sub_blocks = None
    sub_block_len = None
    sub_block_id = None
    data = None

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNProvisioningReadResp: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_PROVISIONING_READ_RESP)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNProvisioningReadResp: _get_msg_id_str()")
        return 'GRN_PROVISIONING_READ_RESP'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNProvisioningReadResp: _get_msg_data()")

        # Packing message
        return xpack('>BB',
            self.utid,
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNProvisioningReadResp: _check_set_msg_data()")

        # msg id is in msg_data[1] in requests that are returned
        # back to the sender
        if self.msg_id != inc.GRN_PROVISIONING_READ_RESP and \
           len(new_msg_data) > 1 and \
           new_msg_data[1] == inc.GRN_PROVISIONING_READ_REQ:
            debug.brf('GRN_PROVISIONING_READ_REQ to GRANITE Server was returned back to sender. ' \
                      'GRANITE Server has not been activated for some reason.')

            return new_msg_data

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_PROVISIONING_READ_RESP,
            'Invalid msg_id: %s in GRN_PROVISIONING_READ_RESP!' % str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 4,
            'GRN_PROVISIONING_READ_RESP msg_data was invalid')

        # take own fields from msg_data
        GRNProvisioningReadResp.response = new_msg_data[3]
        GRNProvisioningReadResp.number_of_sub_blocks = new_msg_data[5]

        if GRNProvisioningReadResp.response == 0 and GRNProvisioningReadResp.number_of_sub_blocks == 1:
            
            GRNProvisioningReadResp.sub_block_id = new_msg_data[6]
            
            self.failFieldUnless('"sub_block_id check"',
                                 GRNProvisioningReadResp.sub_block_id == inc.GRN_PROVISIONG_DATA,
                                 'Invalid sub_block_id: %s in GRN_PROVISIONING_READ_RESP!' % str(GRNProvisioningReadResp.sub_block_id))

            GRNProvisioningReadResp.sub_block_len = (new_msg_data[8] << 8) + (new_msg_data[9])

            GRNProvisioningReadResp.data = new_msg_data[10:(10 + GRNProvisioningReadResp.sub_block_len - 4)]

            self.failFieldUnless('"message lenght check"',
                len(GRNProvisioningReadResp.data) + 4 == \
                GRNProvisioningReadResp.sub_block_len,
                'Invalid message lenght in GRN_PROVISIONING_READ_RESP: %d' % \
                len(GRNProvisioningReadResp.data))

        return new_msg_data

# ============================================================================
class GRNProvisioningWriteReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_PROVISIONING_WRITE_REQ

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - recv_obj              integer
       - utid                  integer
       - provisioning_data     integer (not an isi field)
       - sim_id                integer (not an isi field)
       - data_type             integer (not an isi field)
       - continue_flag         integer (not an isi field)
       - private_id            integer (not an isi field)
    """
    # own fields to msg_data
    provisioning_data = None
    continue_flag = None
    sim_id = None
    data_type = None
    grn_provisioning_data_id = None

    def __init__(self, sim_id, data_type, continue_flag, provisioning_data, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNProvisioningWriteReq: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = inc.GRN_PROVISIONING_WRITE_REQ,
            utid = 1)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_PROVISIONING_WRITE_REQ)

        # save own fields
        GRNProvisioningWriteReq.provisioning_data = provisioning_data
        GRNProvisioningWriteReq.continue_flag = continue_flag
        GRNProvisioningWriteReq.sim_id = sim_id
        GRNProvisioningWriteReq.data_type = data_type
        GRNProvisioningWriteReq.grn_provisioning_data_id = 13


    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNProvisioningWriteReq: _get_msg_id_str()")
        return 'GRN_PROVISIONING_WRITE_REQ'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNProvisioningWriteReq: _get_msg_data()")

        # Checking data
        self.failUnless(isinstance(self.msg_id, int) or \
                        isinstance(self.msg_id, long), \
                'Parameter msg_id is not integer in GRN_PROVISIONING_WRITE_REQ')
        self.failUnless(isinstance(self.recv_obj, int) or \
                        isinstance(self.recv_obj, long), \
                'Parameter recv_obj is not integer in GRN_PROVISIONING_WRITE_REQ')
        self.failUnless(isinstance(self.utid, int) or \
                        isinstance(self.utid, long), \
                'Parameter utid is not integer in GRN_PROVISIONING_WRITE_REQ')
        self.failUnless(isinstance(GRNProvisioningWriteReq.continue_flag, int) or \
                        isinstance(GRNProvisioningWriteReq.continue_flag, long), \
                'Parameter continue_flag is not integer in GRN_PROVISIONING_WRITE_REQ')
        self.failUnless(isinstance(GRNProvisioningWriteReq.data_type, int) or \
                        isinstance(GRNProvisioningWriteReq.data_type, long), \
                'Parameter data_type is not integer in GRN_PROVISIONING_WRITE_REQ')
        self.failUnless(isinstance(GRNProvisioningWriteReq.sim_id, int) or \
                        isinstance(GRNProvisioningWriteReq.sim_id, long), \
                'Parameter sim_id is not integer in GRN_PROVISIONING_WRITE_REQ')

        # Packing message
        packed_data = xpack('>HBBBBBBH*[',
            inc.PN_PRIVATE_GRANITE,
            GRNProvisioningWriteReq.continue_flag,
            GRNProvisioningWriteReq.data_type,
            GRNProvisioningWriteReq.sim_id,
            1,
            GRNProvisioningWriteReq.grn_provisioning_data_id,
            0,
            len(GRNProvisioningWriteReq.provisioning_data) + 4,
            GRNProvisioningWriteReq.provisioning_data + [0,0,0])

        return packed_data

# ============================================================================
class GRNProvisioningWriteResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_PROVISIONING_WRITE_RESP

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - response              integer (not an isi field)
       - configuration_context integer (not an isi field)
    """
    # own fields from msg_data
    response = None
    configuration_context = None

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNProvisioningWriteResp: __init__()")

        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_PROVISIONING_WRITE_RESP)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNProvisioningWriteResp: _get_msg_id_str()")
        return 'GRN_PROVISIONING_WRITE_RESP'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNProvisioningWriteResp: _get_msg_data()")

        # Packing message
        return xpack('>B',
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNProvisioningWriteResp: _check_set_msg_data()")

        # msg id is in msg_data[1] in requests that are returned
        # back to the sender
        if self.msg_id != inc.GRN_PROVISIONING_WRITE_RESP and \
           len(new_msg_data) > 1 and \
           new_msg_data[1] == inc.GRN_PROVISIONING_WRITE_REQ:
            debug.vrb('GRN_PROVISIONING_WRITE_REQ to GRANITE Server was returned back to sender. ' \
                      'GRANITE Server has not been activated for some reason.')

            return new_msg_data

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_PROVISIONING_WRITE_RESP,
            'Invalid msg_id: %s in GRN_PROVISIONING_WRITE_RESP!' % str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 6,
            'GRN_PROVISIONING_WRITE_RESP msg_data was invalid')

        # take own fields from msg_data
        GRNProvisioningWriteResp.response = new_msg_data[3]
        GRNProvisioningWriteResp.configuration_context = (new_msg_data[4] << 8) + (new_msg_data[5])

        return new_msg_data

# ============================================================================
class GRNProvisioningSelectReq(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_PROVISIONING_SELECT_REQ

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - recv_obj              integer
       - utid                  integer
       - private_id            integer (not an isi field)
       - continue_flag         integer (not an isi field)
       - configuration_context integer (not an isi field)
       - sim_id                integer (not an isi field)
    """
    def __init__(self, continue_flag, configuration_context, sim_id, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNProvisioningSelectReq: __init__()")
        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = inc.GRN_PROVISIONING_SELECT_REQ,
            utid = 1)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_PROVISIONING_SELECT_REQ)

        GRNProvisioningSelectReq.continue_flag = continue_flag
        GRNProvisioningSelectReq.configuration_context = configuration_context
        GRNProvisioningSelectReq.sim_id = sim_id

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNProvisioningSelectReq: _get_msg_id_str()")
        return 'GRN_PROVISIONING_SELECT_REQ'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNProvisioningSelectReq: _get_msg_data()")

        # Checking data
        self.failUnless(isinstance(self.msg_id, int) or \
                        isinstance(self.msg_id, long), \
                'Parameter msg_id is not integer in GRN_PROVISIONING_SELECT_REQ')
        self.failUnless(isinstance(self.recv_obj, int) or \
                        isinstance(self.recv_obj, long), \
                'Parameter recv_obj is not integer in GRN_PROVISIONING_SELECT_REQ')
        self.failUnless(isinstance(self.utid, int) or \
                        isinstance(self.utid, long), \
                'Parameter utid is not integer in GRN_PROVISIONING_SELECT_REQ')
        self.failUnless(isinstance(GRNProvisioningSelectReq.continue_flag, int) or \
                        isinstance(GRNProvisioningSelectReq.continue_flag, long), \
                'Parameter continue_flag is not integer in GRN_PROVISIONING_SELECT_REQ')
        self.failUnless(isinstance(GRNProvisioningSelectReq.configuration_context, int) or \
                        isinstance(GRNProvisioningSelectReq.configuration_context, long), \
                'Parameter configuration_context is not integer in GRN_PROVISIONING_SELECT_REQ')
        self.failUnless(isinstance(GRNProvisioningSelectReq.sim_id, int) or \
                        isinstance(GRNProvisioningSelectReq.sim_id, long), \
                'Parameter sim_id is not integer in GRN_PROVISIONING_SELECT_REQ')

        # Packing message
        packed_data = xpack('>HBBH',
            inc.PN_PRIVATE_GRANITE,
            GRNProvisioningSelectReq.continue_flag,
            GRNProvisioningSelectReq.sim_id,
            GRNProvisioningSelectReq.configuration_context)

        return packed_data

# ============================================================================
class GRNProvisioningSelectResp(GRANITEISIMessage):
# ----------------------------------------------------------------------------
    """ISI message class for GRN_PROVISIONING_SELECT_RESP

       Parameters              Data type
       - isi_message           ISIMessage instance

       Fields                  Data type
       - msg_id                integer
       - response              integer (not an isi field)
    """
    # own fields from msg_data
    response = None

    def __init__(self, **isi_message_fields):
        """Initialize message."""
        debug.vrb("GRNProvisioningSelectResp: __init__()")

        GRANITEISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None)

        # Checking field values
        self.assertFields(
            msg_id = inc.GRN_PROVISIONING_SELECT_RESP)

    def _get_msg_id_str(self):
        """Return message id string."""
        debug.vrb("GRNProvisioningSelectResp: _get_msg_id_str()")
        return 'GRN_PROVISIONING_SELECT_RESP'

    def _get_msg_data(self):
        """Return message data."""
        debug.vrb("GRNProvisioningSelectResp: _get_msg_data()")

        # Packing message
        return xpack('>B',
            self.msg_id)

    def _check_set_msg_data(self, new_msg_data):
        """Check message data."""
        debug.vrb("GRNProvisioningSelectResp: _check_set_msg_data()")

        # msg id is in msg_data[1] in requests that are returned
        # back to the sender
        if self.msg_id != inc.GRN_PROVISIONING_SELECT_RESP and \
           len(new_msg_data) > 1 and \
           new_msg_data[1] == inc.GRN_PROVISIONING_SELECT_REQ:
            debug.vrb('GRN_PROVISIONING_SELECT_REQ to GRANITE Server was returned back to sender. ' \
                      'GRANITE Server has not been activated for some reason.')

            return new_msg_data

        self.failFieldUnless('"msg_id check"',
            self.msg_id == inc.GRN_PROVISIONING_SELECT_RESP,
            'Invalid msg_id: %s in GRN_PROVISIONING_SELECT_RESP!' % str(self.msg_id))

        # Checking msg_data
        self.failFieldUnless('"msg_data check"',
            len(new_msg_data) >= 4,
            'GRN_PROVISIONING_SELECT_RESP msg_data was invalid')

        # take own fields from msg_data
        GRNProvisioningSelectResp.response = new_msg_data[3]

        return new_msg_data


# ----------------------------------------------------------------------------
def _validCauseValues():
    """Returns a list of GRANITE Server's valid cause values."""
    # cause values according to server's version
    valid_cause_names = [
        'GRN_CAUSE_NONE',
        'GRN_CAUSE_INVALID_WBXML_DATA',
        'GRN_CAUSE_MEMORY_FULL',
        'GRN_CAUSE_ERROR_TERMINATION',
        'GRN_CAUSE_NOTEXPECTED_RESULT',
        'GRN_CAUSE_STATE_UNKNOWN',
        'GRN_CAUSE_STATE_STARTING',
        'GRN_CAUSE_STATE_IDLE',
        'GRN_CAUSE_STATE_PARSING',
        'GRN_CAUSE_STATE_RUNNING',
        'GRN_CAUSE_STATE_ABORTING',
        'GRN_CAUSE_STATE_SUSPENDED',
        'GRN_CAUSE_STATE_INACTIVE',
        'GRN_CAUSE_STATE_REPORTING',
        'GRN_CAUSE_STATE_CLEARING',
        'GRN_CAUSE_STATE_TERMINATING']

    valid_cause_values = _lookupNames(valid_cause_names)

    return valid_cause_values

# ----------------------------------------------------------------------------
def _lookupNames(namelist):
    """Returns valid include values.

        Parameters

            namelist    list of value names
    """
    valuelist = []

    for name in namelist:
        try:
            valuelist.append(getattr(inc, name))
        except AttributeError:
            pass

    return valuelist

