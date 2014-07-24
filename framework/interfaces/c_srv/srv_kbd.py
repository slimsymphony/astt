#FIXME: Get rid of this and implement it as a activity!

import time, types

import core
from interfaces.isimessage import ISIMessage
from utils.xstruct import xcalcsize, xpack, xunpack
from utils import include

# Local data structures
kbd = include.Include(['pn_const.h', 'srvkbd_isi.h'])

subBlockId = {kbd.KBD_ROLLER_KEY_INFO: 'KBD_ROLLER_KEY_INFO',
              kbd.KBD_SINGLE_PRESS_KEY_EVENT_INFO: 'KBD_SINGLE_PRESS_KEY_EVENT_INFO'}

singlePressState_keyboard = {kbd.KBD_KEY_UP: 'KBD_KEY_UP',
                             kbd.KBD_KEY_DOWN: 'KBD_KEY_DOWN',
                             kbd.KBD_KEY_LONG: 'KBD_KEY_LONG',
                             kbd.KBD_KEY_REPEAT: 'KBD_KEY_REPEAT'}

singlePressState_slide = {kbd.KBD_SLIDE_CLOSED: 'KBD_SLIDE_CLOSED',
                          kbd.KBD_SLIDE_OPEN: 'KBD_SLIDE_OPEN'}

singlePressState_flip = {kbd.KBD_FLIP_OPEN: 'KBD_FLIP_OPEN',
                         kbd.KBD_FLIP_CLOSED: 'KBD_FLIP_CLOSED'}

singlePressKeyCode = {kbd.KBD_KEY_0: 'KBD_KEY_0', kbd.KBD_KEY_1: 'KBD_KEY_1',
                      kbd.KBD_KEY_2: 'KBD_KEY_2', kbd.KBD_KEY_3: 'KBD_KEY_3',
                      kbd.KBD_KEY_4: 'KBD_KEY_4', kbd.KBD_KEY_5: 'KBD_KEY_5',
                      kbd.KBD_KEY_6: 'KBD_KEY_6', kbd.KBD_KEY_7: 'KBD_KEY_7',
                      kbd.KBD_KEY_8: 'KBD_KEY_8', kbd.KBD_KEY_9: 'KBD_KEY_9',
                      kbd.KBD_KEY_STAR: 'KBD_KEY_STAR', kbd.KBD_KEY_HASH: 'KBD_KEY_HASH',
                      kbd.KBD_KEY_ROW1_COL1: 'KBD_KEY_ROW1_COL1', kbd.KBD_KEY_ROW1_COL2: 'KBD_KEY_ROW1_COL2',
                      kbd.KBD_KEY_ROW1_COL3: 'KBD_KEY_ROW1_COL3',kbd.KBD_KEY_ROW1_COL4: 'KBD_KEY_ROW1_COL4',
                      kbd.KBD_KEY_ROW1_COL5: 'KBD_KEY_ROW1_COL5',kbd.KBD_KEY_ROW1_COL6: 'KBD_KEY_ROW1_COL6',
                      kbd.KBD_KEY_ROW1_COL7: 'KBD_KEY_ROW1_COL7',kbd.KBD_KEY_ROW1_COL8: 'KBD_KEY_ROW1_COL8',
                      kbd.KBD_KEY_ROW1_COL9: 'KBD_KEY_ROW1_COL9',kbd.KBD_KEY_ROW1_COL10: 'KBD_KEY_ROW1_COL10',
                      kbd.KBD_KEY_ROW1_COL11: 'KBD_KEY_ROW1_COL11',kbd.KBD_KEY_ROW1_COL12: 'KBD_KEY_ROW1_COL12',
                      kbd.KBD_KEY_ROW2_COL1: 'KBD_KEY_ROW2_COL1',kbd.KBD_KEY_ROW2_COL2: 'KBD_KEY_ROW2_COL2',
                      kbd.KBD_KEY_ROW2_COL3: 'KBD_KEY_ROW2_COL3',kbd.KBD_KEY_ROW2_COL4: 'KBD_KEY_ROW2_COL4',
                      kbd.KBD_KEY_ROW2_COL5: 'KBD_KEY_ROW2_COL5',kbd.KBD_KEY_ROW2_COL6: 'KBD_KEY_ROW2_COL6',
                      kbd.KBD_KEY_ROW2_COL7: 'KBD_KEY_ROW2_COL7',kbd.KBD_KEY_ROW2_COL8: 'KBD_KEY_ROW2_COL8',
                      kbd.KBD_KEY_ROW2_COL9: 'KBD_KEY_ROW2_COL9',kbd.KBD_KEY_ROW2_COL10: 'KBD_KEY_ROW2_COL10',
                      kbd.KBD_KEY_ROW2_COL11: 'KBD_KEY_ROW2_COL11',kbd.KBD_KEY_ROW2_COL12: 'KBD_KEY_ROW2_COL12',
                      kbd.KBD_KEY_ROW3_COL1: 'KBD_KEY_ROW3_COL1',kbd.KBD_KEY_ROW3_COL2: 'KBD_KEY_ROW3_COL2',
                      kbd.KBD_KEY_ROW3_COL3: 'KBD_KEY_ROW3_COL3',kbd.KBD_KEY_ROW3_COL4: 'KBD_KEY_ROW3_COL4',
                      kbd.KBD_KEY_ROW3_COL5: 'KBD_KEY_ROW3_COL5',kbd.KBD_KEY_ROW3_COL6: 'KBD_KEY_ROW3_COL6',
                      kbd.KBD_KEY_ROW3_COL7: 'KBD_KEY_ROW3_COL7',kbd.KBD_KEY_ROW3_COL8: 'KBD_KEY_ROW3_COL8',
                      kbd.KBD_KEY_ROW3_COL9: 'KBD_KEY_ROW3_COL9',kbd.KBD_KEY_ROW3_COL10: 'KBD_KEY_ROW3_COL10',
                      kbd.KBD_KEY_ROW3_COL11: 'KBD_KEY_ROW3_COL11',kbd.KBD_KEY_ROW3_COL12: 'KBD_KEY_ROW3_COL12',
                      kbd.KBD_KEY_ROW4_COL1: 'KBD_KEY_ROW4_COL1',kbd.KBD_KEY_ROW4_COL2: 'KBD_KEY_ROW4_COL2',
                      kbd.KBD_KEY_ROW4_COL3: 'KBD_KEY_ROW4_COL3',kbd.KBD_KEY_ROW4_COL4: 'KBD_KEY_ROW4_COL4',
                      kbd.KBD_KEY_ROW4_COL5: 'KBD_KEY_ROW4_COL5',kbd.KBD_KEY_ROW4_COL6: 'KBD_KEY_ROW4_COL6',
                      kbd.KBD_KEY_ROW4_COL7: 'KBD_KEY_ROW4_COL7',kbd.KBD_KEY_ROW4_COL8: 'KBD_KEY_ROW4_COL8',
                      kbd.KBD_KEY_ROW4_COL9: 'KBD_KEY_ROW4_COL9',kbd.KBD_KEY_ROW4_COL10: 'KBD_KEY_ROW4_COL10',
                      kbd.KBD_KEY_ROW4_COL11: 'KBD_KEY_ROW4_COL11',kbd.KBD_KEY_ROW4_COL12: 'KBD_KEY_ROW4_COL12',
                      kbd.KBD_KEY_ROW5_COL1: 'KBD_KEY_ROW5_COL1',kbd.KBD_KEY_ROW5_COL2: 'KBD_KEY_ROW5_COL2',
                      kbd.KBD_KEY_ROW5_COL3: 'KBD_KEY_ROW5_COL3',kbd.KBD_KEY_ROW5_COL4: 'KBD_KEY_ROW5_COL4',
                      kbd.KBD_KEY_ROW5_COL5: 'KBD_KEY_ROW5_COL5',kbd.KBD_KEY_ROW5_COL6: 'KBD_KEY_ROW5_COL6',
                      kbd.KBD_KEY_ROW5_COL7: 'KBD_KEY_ROW5_COL7',kbd.KBD_KEY_ROW5_COL8: 'KBD_KEY_ROW5_COL8',
                      kbd.KBD_KEY_ROW5_COL9: 'KBD_KEY_ROW5_COL9',kbd.KBD_KEY_ROW5_COL10: 'KBD_KEY_ROW5_COL10',
                      kbd.KBD_KEY_ROW5_COL11: 'KBD_KEY_ROW5_COL11',kbd.KBD_KEY_ROW5_COL12: 'KBD_KEY_ROW5_COL12',
                      kbd.KBD_KEY_NO_KEY: 'KBD_KEY_NO_KEY', kbd.KBD_KEY_POWER: 'KBD_KEY_POWER',
                      kbd.KBD_KEY_SLIDE: 'KBD_KEY_SLIDE', kbd.KBD_KEY_SOFT_L: 'KBD_KEY_SOFT_L',
                      kbd.KBD_KEY_SOFT_R: 'KBD_KEY_SOFT_R', kbd.KBD_KEY_SEND: 'KBD_KEY_SEND',
                      kbd.KBD_KEY_END: 'KBD_KEY_END', kbd.KBD_KEY_ARROW_U: 'KBD_KEY_ARROW_U',
                       kbd.KBD_KEY_ARROW_D: 'KBD_KEY_ARROW_D', kbd.KBD_KEY_ROLLER: 'KBD_KEY_ROLLER',
                       kbd.KBD_KEY_VOL_UP: 'KBD_KEY_VOL_UP', kbd.KBD_KEY_VOL_DOWN: 'KBD_KEY_VOL_DOWN',
                       kbd.KBD_KEY_SELECT: 'KBD_KEY_SELECT', kbd.KBD_KEY_ARROW_L: 'KBD_KEY_ARROW_L',
                       kbd.KBD_KEY_ARROW_R: 'KBD_KEY_ARROW_R', kbd.KBD_KEY_VOICE_RECOG: 'KBD_KEY_VOICE_RECOG',
                       kbd.KBD_KEY_FLIP: 'KBD_KEY_FLIP', kbd.KBD_KEY_ADC1_1: 'KBD_KEY_ADC1_1',
                       kbd.KBD_KEY_ADC1_2: 'KBD_KEY_ADC1_2', kbd.KBD_KEY_ADC1_3: 'KBD_KEY_ADC1_3',
                       kbd.KBD_KEY_ADC1_4: 'KBD_KEY_ADC1_4', kbd.KBD_KEY_ADC1_5: 'KBD_KEY_ADC1_5',
                       kbd.KBD_KEY_ADC1_6: 'KBD_KEY_ADC1_6', kbd.KBD_KEY_ADC1_7: 'KBD_KEY_ADC1_7',
                       kbd.KBD_KEY_ADC1_8: 'KBD_KEY_ADC1_8', kbd.KBD_KEY_ADC2_1: 'KBD_KEY_ADC2_1',
                       kbd.KBD_KEY_ADC2_2: 'KBD_KEY_ADC2_2', kbd.KBD_KEY_ADC2_3: 'KBD_KEY_ADC2_3',
                       kbd.KBD_KEY_ADC2_4: 'KBD_KEY_ADC2_4', kbd.KBD_KEY_ADC2_5: 'KBD_KEY_ADC2_5',
                       kbd.KBD_KEY_ADC2_6: 'KBD_KEY_ADC2_6', kbd.KBD_KEY_ADC2_7: 'KBD_KEY_ADC2_7',
                       kbd.KBD_KEY_ADC2_8: 'KBD_KEY_ADC2_8', kbd.KBD_KEY_P0_0_PIN: 'KBD_KEY_P0_0_PIN',
                       kbd.KBD_KEY_P0_1_PIN: 'KBD_KEY_P0_1_PIN', kbd.KBD_KEY_P0_2_PIN: 'KBD_KEY_P0_2_PIN',
                       kbd.KBD_KEY_P0_3_PIN: 'KBD_KEY_P0_3_PIN', kbd.KBD_KEY_P0_4_PIN: 'KBD_KEY_P0_4_PIN',
                       kbd.KBD_KEY_P0_5_PIN: 'KBD_KEY_P0_5_PIN', kbd.KBD_KEY_P1_0_PIN: 'KBD_KEY_P1_0_PIN',
                       kbd.KBD_KEY_P1_1_PIN: 'KBD_KEY_P1_1_PIN', kbd.KBD_KEY_P1_2_PIN: 'KBD_KEY_P1_2_PIN',
                       kbd.KBD_KEY_P1_3_PIN: 'KBD_KEY_P1_3_PIN', kbd.KBD_KEY_P1_4_PIN: 'KBD_KEY_P1_4_PIN',
                       kbd.KBD_KEY_P1_5_PIN: 'KBD_KEY_P1_5_PIN'}

allKeys = kbd.returnValueKey('KBD_KEY')
allKeys = [item for item in allKeys if item[0]>=48]#48=0x30, lowest key id in srvkbd_isi.h
singlePressKeyCode.update(dict(allKeys))

if getattr(kbd, 'KBD_KEY_CURSOR', None):
    singlePressKeyCode.update({kbd.KBD_KEY_CURSOR: 'KBD_KEY_CURSOR'})

directionOfMovement = {kbd.KBD_ROLLER_NORTH: 'KBD_ROLLER_NORTH',
                       kbd.KBD_ROLLER_SOUTH: 'KBD_ROLLER_SOUTH'}

dbgServer = "KEYBOARD SERVER COMPONENT : "


def keyDown(phone, keyCode):
    """ Press and hold selected key

        Parameters          Data type
        - keyCode           integer

        keyState == KBD_KEY_DOWN

        Remember to release the key by using function keyUp!!

        Returns nothing

        Exception is generated in error situations
    """

    # Pressing key
    debug.vrb(dbgServer + "keyDown() start")
    simulateKeyEvent(phone, keyCode, kbd.KBD_KEY_DOWN)
    return

def keyLong(phone, keyCode):
    """ Long press selected key

        Parameters          Data type
        - keyCode           integer

        keyState == KBD_KEY_LONG

        Returns nothing

        Exception is generated in error situations
    """

    # Pressing key
    debug.vrb(dbgServer + "keyLong() start")
    simulateKeyEvent(phone, keyCode, kbd.KBD_KEY_LONG)
    return

def keyUp(phone, keyCode):
    """ Release selected key

        Parameters          Data type
        - keyCode           integer

        keyState == KBD_KEY_UP

        Returns nothing

        Exception is generated in error situations
    """

    # Pressing key
    debug.vrb(dbgServer + "keyUp() start")
    simulateKeyEvent(phone, keyCode, kbd.KBD_KEY_UP)
    return

def keyRepeat(phone, keyCode):
    """ Repeat selected key

        Parameters          Data type
        - keyCode           integer

        keyState == KBD_KEY_REPEAT

        Returns nothing

        Exception is generated in error situations
    """

    # Pressing key
    debug.vrb(dbgServer + "keyRepeat() start")
    simulateKeyEvent(phone, keyCode, kbd.KBD_KEY_REPEAT)
    return

def simulateKeyEvent(phone, keyCode, keyState):
    """ Simulate key event

        Parameters          Data type
        - keyCode           integer
        - keyState          integer

        Returns nothing

        Exception is generated in error situations
    """

    debug.vrb(dbgServer + "simulateKeyEvent() start")
    debug.vrb(dbgServer + "    keyCode = " + str(keyCode))
    debug.vrb(dbgServer + "    keyState = " + str(keyState))

    # Creating isi message
    blockEventInfo = {
        'block_id' : kbd.KBD_SINGLE_PRESS_KEY_EVENT_INFO,
        'key_code' : keyCode,
        'key_state' : keyState}
    isi_message_fields = {
        'sub_blocks' : [blockEventInfo]}

    # Sending message
    retData = kbdEventSimulation(phone, **isi_message_fields)

    # Checking response
    self.failUnless(retData.get('status') == kbd.KBD_OK, \
        'Simulating event failed. Status = ' + str(retData.get('status')))

    debug.vrb(dbgServer + "simulateKeyEvent() end")
    return

def kbdReadInfo(phone, **isi_message_fields):
    """ Read keyboard info

        For list of required parameters see class KbdInfoReq

        Returns dictionary
            - msg_id
            - devices
            - misc_port
            - upp_kdi_port_0
            - upp_kdi_port_1
            - multi_key_status

        Exception is generated in error situations
    """

    debug.vrb(dbgServer + "kbdReadInfo() start")
    _printParameters(**isi_message_fields)

    # Creating request
    debug.vrb(dbgServer + "Creating request")
    request = KbdInfoReq(**isi_message_fields)
    debug.vrb(dbgServer + "request = " + str(request.isi_message))

    # Sending message
    debug.vrb(dbgServer + "Exchanging messages")
    data = phone.transferMsg(request)

    # Creating response
    debug.vrb(dbgServer + "Creating responses")
    debug.vrb(dbgServer + "response = " + str(data))
    response = KbdInfoResp(isi_message = data)
    retData = {
        'msg_id' : response.msg_id,
        'devices' : response.devices,
        'misc_port' : response.misc_port,
        'upp_kdi_port_0' : response.upp_kdi_port_0,
        'upp_kdi_port_1' : response.upp_kdi_port_1,
        'multi_key_status' : response.multi_key_status}

    debug.vrb(dbgServer + "response = " + str(retData))
    debug.vrb(dbgServer + "kbdReadInfo() end")
    return retData

def kbdEventSimulation(phone,**isi_message_fields):
    """ Simulate keyboard event

        For list of required parameters see class KbdEventSimulationReq

        Returns dictionary
            - msg_id
            - status

        Exception is generated in error situations
    """

    debug.vrb(dbgServer + "kbdEventSimulation() start")
    _printParameters(**isi_message_fields)

    # Creating request
    debug.vrb(dbgServer + "Creating request")
    request = KbdEventSimulationReq(**isi_message_fields)
    debug.vrb(dbgServer + "request = " + str(request.isi_message))

    # Sending message
    debug.vrb(dbgServer + "Exchanging messages")
    data = phone.transferMsg(request)

    # Creating response
    debug.vrb(dbgServer + "Creating responses")
    debug.vrb(dbgServer + "response = " + str(data))
    response = KbdEventSimulationResp(isi_message = data)
    retData = {
        'msg_id' : response.msg_id,
        'status' : response.status}

    debug.vrb(dbgServer + "response = " + str(retData))
    debug.vrb(dbgServer + "kbdEventSimulation() end")
    return retData

# ============================================================================
#   3.2     Keyboard server ISI message classes
# ----------------------------------------------------------------------------

class KbdISIMessage(ISIMessage):

    def __init__(self, **isi_message_fields):
        ISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(resource=kbd.PN_KEY)
        self.assertFields(resource=kbd.PN_KEY)

# ============================================================================
#   3.3     KBD_EVENT_IND
# ----------------------------------------------------------------------------

class KbdEventInd(KbdISIMessage):

    def __init__(self, **isi_message_fields):
        KbdISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id=kbd.KBD_EVENT_IND,
                          direction_of_movement=None, amount_of_movements=None,
                          single_press_key_code=None, single_press_key_state=None,
                          fill_byte=None)
        self.assertFields(msg_id=kbd.KBD_EVENT_IND)
       
    def _get_msg_id_str(self):
        return kbd.lookup('_IND', self.msg_id)

    def _get_msg_data(self):
        if self.sub_block_id == kbd.KBD_ROLLER_KEY_INFO:
            msg_data = xpack('>BBBBBB', self.fill_byte, self.sub_block_nbr,
                             self.sub_block_id, self.sub_block_len,
                             self.direction_of_movement, self.amount_of_movements)
        else:
            if self.sub_block_id == kbd.KBD_SINGLE_PRESS_KEY_EVENT_INFO:
                msg_data = xpack('>BBBBHBBBB', self.fill_byte, self.sub_block_nbr,
                                self.sub_block_id, self.sub_block_len,
                                 self.single_press_key_code, self.single_press_key_state,
                                self.fill_byte, self.fill_byte, self.fill_byte)
            else:
                msg_data = xpack('>BB*[', self.fill_byte, self.sub_block_nbr, self.other_data)            
        
        return msg_data

    def _get_msg_data_str(self):
        msg_data_str = self.fill_byte, self.sub_block_nbr
        if self.sub_block_id == kbd.KBD_ROLLER_KEY_INFO:
            msg_data_str += self.kbd_roller_key_info_sb_str
        else:
            if self.sub_block_id == kbd.KBD_SINGLE_PRESS_KEY_EVENT_INFO:
                msg_data_str += self.kbd_single_press_key_event_info_sb_str
            else:
                msg_data_str += self.other_data

        return msg_data_str

    def _get_kbd_roller_key_info_sb_str(self):
        return 'kbd_roller_key_info_sb: %s, %s, %s, %s, %s'%\
               (self,sub_block_id_str, self.sub_block_len,
                self.direction_of_movement, self.amount_of_movements)        

    def _get_kbd_single_press_key_event_info_sb_str(self):
        return 'kbd_single_press_key_event_info_sb: %s, %s, %s, %s, %s, %s, %s'%\
               (self.sub_block_id_str, self.sub_block_len,
                self.single_press_key_code_str, self.single_press_key_state_str,
                self.fill_byte, self.fill_byte, self.fill_byte)
        
    def _get_sub_block_id_str(self):
        return '%s' % (subBlockId.get(self.sub_block_id,\
                                      '%s' %self.sub_block_id))

    def _get_single_press_key_state_str(self):
        if self.single_press_key_code != kbd.KBD_KEY_FLIP and\
           self.single_press_key_code != kbd.KBD_KEY_SLIDE:
            return '%s' % (singlePressState_keyboard.\
                           get(self.single_press_key_state,\
                               'UNKNOWN: %s' %self.single_press_key_state)) 
        if self.single_press_key_code == kbd.KBD_KEY_FLIP:
            return '%s' % (singlePressState_flip.\
                           get(self.single_press_key_state,\
                               'UNKNOWN: %s' %self.single_press_key_state))
        if self.single_press_key_code == kbd.KBD_KEY_SLIDE:
            return '%s' % (singlePressState_slide.\
                           get(self.single_press_key_state,\
                               'UNKNOWN: %s' %self.single_press_key_state))            

    def _get_single_press_key_code_str(self):        
        return '%s' % (singlePressKeyCode.get(self.single_press_key_code,\
                                            '%s' %self.single_press_key_code))

    def _get_direction_of_movement_str(self):
        return '%s' % (directionOfMovement.get(self.direction_of_movement,\
                                            '%s' %self.direction_of_movement))        
        
    def _check_set_msg_data(self, new_msg_data):
        fill_byte, sub_block_nbr, sub_block_id, other_data = xunpack('>BBB*[', new_msg_data)

        if sub_block_id == kbd.KBD_ROLLER_KEY_INFO:
            self.fill_byte, self.sub_block_nbr,\
                            self.sub_block_id, self.sub_block_len,\
                            self.direction_of_movement,\
                            self.amount_of_movements = xunpack('>BBBBBB', new_msg_data)
        else:
            if sub_block_id == kbd.KBD_SINGLE_PRESS_KEY_EVENT_INFO:
                self.fill_byte, self.sub_block_nbr,\
                                self.sub_block_id, self.sub_block_len,\
                                self.single_press_key_code, self.single_press_key_state,\
                                self.fill_byte, self.fill_byte,\
                                self.fill_byte = xunpack('>BBBBHBBBB', new_msg_data)
            else:
                self.fill_byte, self.sub_block_nbr, self.other_data = xunpack('>BB*[', new_msg_data)
                self.single_press_key_code = 'UNKNOWN'
                self.single_press_key_state = 'UNKNOWN'
            
        return new_msg_data            

# ============================================================================
#   3.4     KBD_INFO_REQ / KBD_INFO_RESP
# ----------------------------------------------------------------------------

class KbdInfoReq(KbdISIMessage):
    """ Class for KBD_INFO_REQ

        Parameters              Data type
        - filler_1 (optional)   integer
        - filler_2 (optional)   integer
    """

    dbgClass = "KbdInfoReq : "

    def __init__(self, **isi_message_fields):

        debug.vrb(dbgServer + self.dbgClass + "__init__()")

        KbdISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = kbd.KBD_INFO_REQ,
            filler_1 = 0,
            filler_2 = 0)

        # Checking field values
        self.assertFields(
            msg_id = kbd.KBD_INFO_REQ)

    def _get_msg_id_str(self):

        debug.vrb(dbgServer + self.dbgClass + "_get_msg_id_str()")
        return 'KBD_INFO_REQ'

    def _get_msg_data(self):

        debug.vrb(dbgServer + self.dbgClass + "_get_msg_data()")

        # Checking data
        self.failUnless(
            type(self.filler_1) == types.IntType or \
            type(self.filler_1) == types.LongType, \
            'Parameter filler_1 is not integer in KBD_INFO_REQ')
        self.failUnless(
            type(self.filler_2) == types.IntType or \
            type(self.filler_2) == types.LongType, \
            'Parameter filler_2 is not integer in KBD_INFO_REQ')

        # Packing message
        return xpack('>BB',
            self.filler_1,
            self.filler_2)

class KbdInfoResp(KbdISIMessage):
    """ Class for KBD_INFO_RESP

        Parameters              Data type
        - isi_message           ISIMessage instance

        Fields                  Data type
        - msg_id                integer
        - devices               integer
        - misc_port             integer
        - upp_kdi_port_0        integer
        - upp_kdi_port_1        integer
        - multi_key_status      integer
        - filler_1              integer
    """

    dbgClass = "KbdInfoResp : "

    def __init__(self, **isi_message_fields):

        debug.vrb(dbgServer + self.dbgClass + "__init__()")

        KbdISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None,
            devices = None,
            misc_port = None,
            upp_kdi_port_0 = None,
            upp_kdi_port_1 = None,
            multi_key_status = None,
            filler_1 = None)

        # Checking field values
        self.assertFields(
            msg_id = kbd.KBD_INFO_RESP,
            filler_1 = 0)

    def _get_msg_id_str(self):

        debug.vrb(dbgServer + self.dbgClass + "_get_msg_id_str()")
        return 'KBD_INFO_RESP'

    def _get_msg_data(self):

        debug.vrb(dbgServer + self.dbgClass + "_get_msg_data()")

        # Packing message
        return xpack('>BBBBBB',
            self.devices,
            self.misc_port,
            self.upp_kdi_port_0,
            self.upp_kdi_port_1,
            self.multi_key_status,
            self.filler_1)

    def _check_set_msg_data(self, new_msg_data):

        debug.vrb(dbgServer + self.dbgClass + "_check_set_msg_data()")

        # Unpacking message
        self.devices, \
        self.misc_port, \
        self.upp_kdi_port_0, \
        self.upp_kdi_port_1, \
        self.multi_key_status, \
        self.filler_1, \
        extra_data = xunpack('>BBBBBB*[', new_msg_data)

        # Checking extra data
        self.failFieldUnless('extra_data', \
            extra_data == None, \
            'KBD_INFO_RESP message is too long')

        return new_msg_data

# ============================================================================
#   3.5     KBD_EVENT_SIMULATION_REQ / KBD_EVENT_SIMULATION_RESP
# ----------------------------------------------------------------------------

class KbdEventSimulationReq(KbdISIMessage):
    """ Class for KBD_EVENT_SIMULATION_REQ

        Parameters              Data type
        - filler_1 (optional)   integer
        - sub_blocks            list of sub block dictionaries
                                [{block_1}, {block_2}, ... ]

        For sub_block data refer to ISI KBD Server Message Descriptions
        document and _packSubBlocks function in srv_sms_memory.py file.
    """

    dbgClass = "KbdEventSimulationReq : "

    def __init__(self, **isi_message_fields):

        debug.vrb(dbgServer + self.dbgClass + "__init__()")

        KbdISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = kbd.KBD_EVENT_SIMULATION_REQ,
            filler_1 = 0,
            sub_block_count = None,
            sub_blocks = None)

        # Checking field values
        self.assertFields(
            msg_id = kbd.KBD_EVENT_SIMULATION_REQ)

    def _get_msg_id_str(self):

        debug.vrb(dbgServer + self.dbgClass + "_get_msg_id_str()")
        return 'KBD_EVENT_SIMULATION_REQ'

    def _get_msg_data(self):

        debug.vrb(dbgServer + self.dbgClass + "_get_msg_data()")

        # Checking data
        self.failUnless(
            type(self.filler_1) == types.IntType or \
            type(self.filler_1) == types.LongType, \
            'Parameter filler_1 is not integer in KBD_EVENT_SIMULATION_REQ')

        # Packing sub blocks
        sub_data = _packSubBlocks(self, self.sub_blocks)
        self.sub_block_count = len(self.sub_blocks)

        # Packing message
        return xpack('>BB*[',
            self.filler_1,
            self.sub_block_count,
            sub_data)

class KbdEventSimulationResp(KbdISIMessage):
    """ Class for KBD_EVENT_SIMULATION_RESP

        Parameters              Data type
        - isi_message           ISIMessage instance

        Fields                  Data type
        - msg_id                integer
        - status                integer
        - filler_1              integer
    """

    dbgClass = "KbdEventSimulationResp : "

    def __init__(self, **isi_message_fields):

        debug.vrb(dbgServer + self.dbgClass + "__init__()")

        KbdISIMessage.__init__(self, **isi_message_fields)

        self.initDefaults(
            msg_id = None,
            status = None,
            filler_1 = None)

        # Checking field values
        self.assertFields(
            msg_id = kbd.KBD_EVENT_SIMULATION_RESP,
            filler_1 = 0)

        legalStatus = [kbd.KBD_OK, kbd.KBD_FAIL]
        self.assertFields(
            status = 'status in ' + str(legalStatus))

    def _get_msg_id_str(self):

        debug.vrb(dbgServer + self.dbgClass + "_get_msg_id_str()")
        return 'KBD_EVENT_SIMULATION_RESP'

    def _get_msg_data(self):

        debug.vrb(dbgServer + self.dbgClass + "_get_msg_data()")

        # Packing message
        return xpack('>BB',
            self.status,
            self.filler_1)

    def _check_set_msg_data(self, new_msg_data):

        debug.vrb(dbgServer + self.dbgClass + "_check_set_msg_data()")

        # Unpacking message
        self.status, \
        self.filler_1, \
        extra_data = xunpack('>BB*[', new_msg_data)

        # Checking extra data
        self.failFieldUnless('extra_data', \
            extra_data == None, \
            'KBD_EVENT_SIMULATION_RESP message is too long')

        return new_msg_data

# ============================================================================
#   3.6     Internal functions (do not use directly)
# ----------------------------------------------------------------------------

def _packSubBlocks(self, sub_blocks):
    """ Internal helper function

        Parameters          Data type
        - sub_blocks        list of sub block dictionaries
                            [{block_1}, {block_2}, ... ]

        Required sub block data is listed in functions below

        Sub block id                        Pack function
        KBD_SINGLE_PRESS_KEY_EVENT_INFO     _packKbdSinglePressKeyEventInfo

        In responses all parameters are included. 'if required' marked
        fillers may not exist.

        Returns packed sub block data

        Exception is generated in error situations
    """

    debug.vrb(dbgServer + "_packSubBlocks() start")
    _printParameters(sub_blocks = sub_blocks)

    self.failUnless(type(sub_blocks) == types.ListType, \
        'Parameter sub_blocks is not a list')

    sub_data = []

    # Packing sub blocks
    for single_block in sub_blocks:

        # Checking sub block data
        self.failUnless(type(single_block) == types.DictionaryType, \
            'Sub block data is not in dictionary')
        self.failUnless(len(single_block) > 0, 'Empty sub block')
        self.failUnless(single_block.has_key('block_id'), \
            'Sub block id is missing')

        block_id = single_block.get('block_id')

        if block_id == kbd.KBD_SINGLE_PRESS_KEY_EVENT_INFO:

            packed_block = _packKbdSinglePressKeyEventInfo(self, single_block)
            sub_data.extend(packed_block)

        else:
            # Unknown sub block id
            self.fail('Can not pack sub block. Unknown id (' + str(block_id) + ')')

    debug.vrb(dbgServer + "_packSubBlocks() end")
    return sub_data

def _packKbdSinglePressKeyEventInfo(self, single_block):
    """ Internal helper function

        Data :
        - block_id              int
        - block_length          int (optional)
        - key_code              int
        - key_state             int
        - filler_1              int (optional)
        - filler_2              int (optional)
        - filler_3              int (optional)

        Returns packed sub block data

        Exception is generated in error situations
    """

    subBlockId = 'KBD_SINGLE_PRESS_KEY_EVENT_INFO'
    debug.vrb(dbgServer + "packing sub block " + subBlockId)
    debug.vrb(dbgServer + "    data = " + str(single_block))
    header_length = 8

    ##### Required parameters

    # key_code
    self.failUnless(single_block.has_key('key_code'), \
        'Parameter key_code is missing from sub block ' + str(subBlockId))
    key_code = single_block.get('key_code')
    self.failUnless(
        type(key_code) == types.IntType or \
        type(key_code) == types.LongType, \
        'Parameter key_code is not integer in sub block ' + str(subBlockId))

    # key_state
    self.failUnless(single_block.has_key('key_state'), \
        'Parameter key_state is missing from sub block ' + str(subBlockId))
    key_state = single_block.get('key_state')
    self.failUnless(
        type(key_state) == types.IntType or \
        type(key_state) == types.LongType, \
        'Parameter key_state is not integer in sub block ' + str(subBlockId))

    ##### Optional parameters
    
    # filler_1
    if single_block.has_key('filler_1'):
        filler_1 = single_block.get('filler_1')
        self.failUnless(
            type(filler_1) == types.IntType or \
            type(filler_1) == types.LongType, \
            'Parameter filler_1 is not integer in sub block ' + str(subBlockId))
    else:
        filler_1 = 0
    
    # filler_2
    if single_block.has_key('filler_2'):
        filler_2 = single_block.get('filler_2')
        self.failUnless(
            type(filler_2) == types.IntType or \
            type(filler_2) == types.LongType, \
            'Parameter filler_2 is not integer in sub block ' + str(subBlockId))
    else:
        filler_2 = 0
    
    # filler_3
    if single_block.has_key('filler_3'):
        filler_3 = single_block.get('filler_3')
        self.failUnless(
            type(filler_3) == types.IntType or \
            type(filler_3) == types.LongType, \
            'Parameter filler_3 is not integer in sub block ' + str(subBlockId))
    else:
        filler_3 = 0

    # block_length
    if single_block.has_key('block_length'):
        block_length = single_block.get('block_length')
        self.failUnless(
            type(block_length) == types.IntType or \
            type(block_length) == types.LongType, \
            'Parameter block_length is not integer in sub block ' + str(subBlockId))
    else:
        block_length = header_length

    ##### Packing sub block

    # Packing sub block body
    packed_block = xpack('>BBHBBBB',
        kbd.KBD_SINGLE_PRESS_KEY_EVENT_INFO,
        block_length,
        key_code,
        key_state,
        filler_1,
        filler_2,
        filler_3)

    return packed_block

def _printParameters(**isi_message_fields):
    """ Internal helper function
    """

    for func_param in isi_message_fields.keys():
        if func_param == 'sub_blocks':
            debug.vrb(dbgServer + "    " + func_param + " = ")
            param_value = isi_message_fields.get(func_param)
            for singleBlock in param_value:
                debug.vrb(dbgServer + "        " + str(singleBlock))
        else:
            debug.vrb(dbgServer + "    " + func_param + " = " + str(isi_message_fields.get(func_param)))

