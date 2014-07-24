#FIXME: Get rid of this and implement it as a activity!

import core
from interfaces.isimessage import ISIMessage
from utils.xstruct import xpack, xunpack
from utils import include

# Local data structures
mtc = include.Include('mtc_isi.h')

mtc_state = {mtc.MTC_POWER_OFF: 'POWER_OFF',
             mtc.MTC_NORMAL: 'NORMAL',
             mtc.MTC_CHARGING: 'CHARGING',
             mtc.MTC_ALARM: 'ALARM',
             mtc.MTC_TEST: 'TEST',
             mtc.MTC_LOCAL: 'LOCAL',
             mtc.MTC_SELFTEST_FAIL: 'SELFTEST_FAIL',
             mtc.MTC_RF_INACTIVE: 'RF_INACTIVE',
             mtc.MTC_SW_RESET: 'SW_RESET' }

mtc_status = {mtc.MTC_OK: 'OK',
              mtc.MTC_FAIL: 'FAIL',
              mtc.MTC_STATE_TRANSITION_GOING_ON: 'STATE_TRANSITION_GOING_ON',
              mtc.MTC_NOT_ALLOWED: 'NOT_ALLOWED',
              mtc.MTC_ALREADY_ACTIVE: 'ALREADY_ACTIVE' }

def mtcPowerOn(phone, timeout = None):
    """You can set power on or power off with mtcPower()

        You can check the following value(s) from response:
            status = mtc.MTC_OK |
                     mtc.MTC_FAIL |
                     mtc.MTC_STATE_TRANSITION_GOING_ON |
                     mtc.MTC_NOT_ALLOWED |
                     mtc.MTC_ALREADY_ACTIVE
    """
    request = MtcPowerReq(msg_id = mtc.MTC_POWER_ON_REQ)
    if timeout:
        response = MtcPowerResp(\
            isi_message = phone.transferMsg(request, timeout))
    else:
        response = MtcPowerResp(\
            isi_message = phone.transferMsg(request))
    return response

def mtcPowerOff(phone, timeout=None):
    """
    You can set power on or power off with mtcPower().

    You can check the following value(s) from response:
        status = mtc.MTC_OK |
                 mtc.MTC_FAIL |
                 mtc.MTC_STATE_TRANSITION_GOING_ON |
                 mtc.MTC_NOT_ALLOWED |
                 mtc.MTC_ALREADY_ACTIVE
                                                        """
    request = MtcPowerReq(msg_id=mtc.MTC_POWER_OFF_REQ)
    if timeout:
        response = MtcPowerResp(\
            isi_message = phone.transferMsg(request, timeout))
    else:
        response = MtcPowerResp(\
            isi_message = phone.transferMsg(request))
    return response

def mtcResetGenerate(phone, type=mtc.MTC_HIDDEN_RESET, state=mtc.MTC_RESET_SW_RESET, 
                     timeout=None):
    """
    You can reset phone with mtcResetGenerate(), parameters:
        type = MTC_STATE_VIA_RESET
        state = mtc.MTC_CHARGING | mtc.MTC_ALARM | mtc.MTC_NORMAL |
                mtc.MTC_LOCAL | mtc.MTC_TEST |
                mtc.MTC_RF_INACTIVE |
                mtc.MTC_SELFTEST_FAIL |
                mtc.MTC_DISK_WIPE

        type = MTC_DEVICE_RESET
        state = mtc.MTC_CDSP | mtc.MTC_ADPS
        
        type = MTC_HIDDEN_RESET
        state = mtc.MTC_RESET_SW_RESET | mtc.MTC_RESET_SOS_RESET

                Note: state can be defined with parameter only when
                      reset type is the mtc.MTC_STATE_VIA_RESET or mtc.MTC_DEVICE_RESET

    You can check the following value(s) from response:
         status = mtc.MTC_OK |
                  mtc.MTC_FAIL |
                                                            """
    request = MtcResetGenerateReq(type=type, state=state)
    if timeout:
        response = MtcResetGenerateResp(\
            isi_message = phone.transferMsg(request, timeout))
    else:
        response = MtcResetGenerateResp(\
            isi_message = phone.transferMsg(request))
    return response

def mtcStateQuery(phone, timeout=None):
    """
    You can check the following value(s) from response:
        current_state = mtc.MTC_POWER_OFF, mtc.MTC_NORMAL, mtc.MTC_CHARGING,
                        mtc.MTC_ALARM, mtc.MTC_TEST, mtc.MTC_LOCAL,
                        mtc.MTC_SELFTEST_FAIL,
                        mtc.MTC_RF_INACTIVE,
                        mtc.MTC_SW_RESET,
        target_state =  same as above-mentioned..

        NOTE:
        If the current and target states are different
        then state transition is ongoing.
                                                              """
    request = MtcStateQueryReq()
    if timeout:
        response = MtcStateQueryResp(\
            isi_message = phone.transferMsg(request, timeout))
    else:
        response = MtcStateQueryResp(\
            isi_message = phone.transferMsg(request))
    return response

def mtcStateSet(phone, target_state=mtc.MTC_NORMAL, timeout=None):
    """
    You can set state with mtcStateSet(), parameter:
        target_state =  mtc.MTC_POWER_OFF, mtc.MTC_NORMAL, mtc.MTC_CHARGING,
                        mtc.MTC_ALARM, mtc.MTC_TEST, mtc.MTC_LOCAL,
                        mtc.MTC_SELFTEST_FAIL,
                        mtc.MTC_RF_INACTIVE,
                        mtc.MTC_SW_RESET,

    You can check the following value(s) from response:
        mtc_status = mtc.MTC_OK,
                     mtc.MTC_FAIL,
                     mtc.MTC_STATE_TRANSITION_GOING_ON,
                     mtc.MTC_NOT_ALLOWED,
                     mtc.MTC_ALREADY_ACTIVE
                                                        """
    request = MtcStateReq(target_state=target_state)
    if timeout:
        response = MtcStateResp(\
            isi_message = phone.transferMsg(request, timeout))
    else:
        response = MtcStateResp(\
            isi_message = phone.transferMsg(request))
    return response

# ============================================================================
#   3.1.2    Server test functions
# ----------------------------------------------------------------------------

# ============================================================================
#   3.2     MTC server ISI message classes
# ----------------------------------------------------------------------------

class MtcISIMessage(ISIMessage):

    def __init__(self, **isi_message_fields):
        ISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(resource=mtc.PN_MTC)
        self.assertFields(resource=mtc.PN_MTC)

class MtcPowerReq(MtcISIMessage):

    def __init__(self, **isi_message_fields):          
        MtcISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id=None, reserved1=0, reserved2=0)

    def _get_msg_id_str(self): 
        return mtc.lookup('_REQ', self.msg_id)

    def _get_msg_data(self):
        return xpack('>BB',  self.reserved1, self.reserved2) # reserved bytes

    def _check_set_msg_data(self, new_msg_data):        
        self.reserved1, self.reserved2 = xunpack('>BB', new_msg_data)
        return new_msg_data

class MtcPowerResp(MtcISIMessage):

    def __init__(self, **isi_message_fields):
        MtcISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id=None, status=None, reserved=0)
       
    def _get_msg_id_str(self):
        return mtc.lookup('_RESP', self.msg_id)

    def _get_msg_data(self):
        return xpack('>BB', self.status, self.reserved)

    def _get_msg_data_str(self):
        return 'status:%s reserved:%s' % (self.status_str, self.reserved_str)

    def _get_status_str(self):
        return '%s' % (mtc_status.get(self.status, 'UNKNOWN!'))

    def _get_reserved_str(self):
        return '%s' % (str(self.reserved))  

    def _check_set_msg_data(self, new_msg_data):        
        self.status, self.reserved, extra_data = xunpack('>BB*[', new_msg_data)
        # FIXME: checking for extra_data
        return new_msg_data

class MtcResetGenerateReq(MtcISIMessage):

    def __init__(self, **isi_message_fields):          
        MtcISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id=mtc.MTC_RESET_GENERATE_REQ, type=None, state=None)
        self.assertFields(msg_id=mtc.MTC_RESET_GENERATE_REQ)

    def _get_msg_id_str(self): 
        return mtc.lookup('_REQ', self.msg_id)

    def _get_msg_data(self):
        return xpack('>BB', self.type, self.state) # reserved bytes

    def _check_set_msg_data(self, new_msg_data):        
        self.type, self.state = xunpack('>BB', new_msg_data)
        return new_msg_data

class MtcResetGenerateResp(MtcISIMessage):

    def __init__(self, **isi_message_fields):
        MtcISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id=mtc.MTC_RESET_GENERATE_RESP, status=None, reserved=0)        
       
    def _get_msg_id_str(self):
        return mtc.lookup('_RESP', self.msg_id)

    def _get_msg_data(self):
        return xpack('>BB', self.status, self.reserved)

    def _get_msg_data_str(self):
        return 'status:%s reserved:%s' % (self.status_str, self.reserved_str)

    def _get_status_str(self):
        return '%s' % (mtc_status.get(self.status, 'UNKNOWN!'))

    def _get_reserved_str(self):
        return '%s' % (str(self.reserved))     

    def _check_set_msg_data(self, new_msg_data):        
        self.status, self.reserved, extra_data = xunpack('>BB*[', new_msg_data)
        # FIXME: checking for extra_data       
        return new_msg_data

class MtcStateQueryReq(MtcISIMessage):

    def __init__(self, **isi_message_fields):          
        MtcISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id=mtc.MTC_STATE_QUERY_REQ, reserved1=0, reserved2=0)

    def _get_msg_id_str(self): 
        return mtc.lookup('_REQ', self.msg_id)

    def _get_msg_data(self):
        return xpack('>BB',  self.reserved1, self.reserved2) # reserved bytes

    def _check_set_msg_data(self, new_msg_data):        
        self.reserved1, self.reserved2 = xunpack('>BB', new_msg_data)
        return new_msg_data

class MtcStateQueryResp(MtcISIMessage):

    def __init__(self, **isi_message_fields):
        MtcISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id=mtc.MTC_STATE_QUERY_RESP,\
                          current_state=None, target_state=None) 
       
    def _get_msg_id_str(self):
        return mtc.lookup('_RESP', self.msg_id)

    def _get_msg_data(self):
        return xpack('>BB', self.current_state, self.target_state)

    def _get_msg_data_str(self):
        return 'current_state:%s target_state:%s' % (self.current_state_str, self.target_state_str)
        
    def _get_current_state_str(self):
        return '%s' % (mtc_state.get(self.current_state, 'UNKNOWN!'))

    def _get_target_state_str(self):
        return '%s' % (mtc_state.get(self.target_state, 'UNKNOWN!'))

    def _check_set_msg_data(self, new_msg_data):        
        self.current_state, self.target_state, extra_data = xunpack('>BB*[', new_msg_data)
        # FIXME: checking for extra_data       
        return new_msg_data

class MtcStateReq(MtcISIMessage):

    def __init__(self, **isi_message_fields):          
        MtcISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id=mtc.MTC_STATE_REQ, target_state=None, reserved=0)

    def _get_msg_id_str(self): 
        return mtc.lookup('_REQ', self.msg_id)

    def _get_msg_data(self):
        return xpack('>BB', self.target_state, self.reserved) 

    def _check_set_msg_data(self, new_msg_data):        
        self.target_state, self.reserved = xunpack('>BB', new_msg_data)
        return new_msg_data

class MtcStateResp(MtcISIMessage):

    def __init__(self, **isi_message_fields):
        MtcISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id=mtc.MTC_STATE_RESP, status=None, reserved=None) 
       
    def _get_msg_id_str(self):
        return mtc.lookup('_RESP', self.msg_id)

    def _get_msg_data(self):
        return xpack('>BB', self.status, self.reserved)

    def _get_msg_data_str(self):
        return 'status:%s reserved:%s' % (self.status_str, self.reserved_str)
        
    def _get_status_str(self):
        return '%s' % (mtc_status.get(self.status, 'UNKNOWN!'))

    def _get_reserved_str(self):
        return '%s' % (str(self.reserved))        

    def _check_set_msg_data(self, new_msg_data):        
        self.status, self.reserved, extra_data = xunpack('>BB*[', new_msg_data)
        # FIXME: checking for extra_data       
        return new_msg_data
