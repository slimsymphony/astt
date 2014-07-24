#FIXME: Get rid of this and implement it as a activity!

import core
from interfaces.isimessage import ISIMessage
from utils.xstruct import xpack, xunpack
from utils import include

isi = include.Include('pn_name_msg.h')

# Local data definitions

# ============================================================================
#   3.1     NameServiceMessage, NameQueryReq and NameQueryResp classes
# ----------------------------------------------------------------------------
class NameServiceMessage(ISIMessage):

    def __init__(self, **isi_message_fields):
        ISIMessage.__init__(self, **isi_message_fields)
        self.initDefaults(resource=isi.PN_NAMESERVICE)
        self.assertFields(resource=isi.PN_NAMESERVICE)

class NameQueryReq(NameServiceMessage):
    """Class for parsing PNS_NAME_QUERY_REQ messages.

    Field name:     Description (default):

    msg_id          PNS_NAME_QUERY_REQ
    name            32-bit name value
    mask            32-bit mask value
    """
    def __init__(self, **isi_message_fields):
        NameServiceMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id=isi.PNS_NAME_QUERY_REQ, name=None, mask=None)
        self.assertFields(msg_id=isi.PNS_NAME_QUERY_REQ)

    def _get_msg_data(self):
        return xpack('>B:reserved1 B:reserved2 L:name L:mask', 0, 0,
                     self.name, self.mask)

    def _get_msg_data_str(self):
        return 'name:%s mask:%s' % (self.name_str, self.mask_str)

    def _check_set_msg_data(self, new_msg_data):
        reserved, self.name, self.mask, extra = xunpack('>HLL', new_msg_data)
        self.failUnless(not extra, 'Extra data after msg data:%s' % extra)

        return new_msg_data

    def _get_name_str(self):
        return self.name is not None and '0x%08X' % self.name or 'undefined'

    def _get_mask_str(self):
        return self.mask is not None and '0x%08X' % self.mask or 'undefined'

class NameQueryResp(NameServiceMessage):
    """Class for parsing PNS_NAME_QUERY_RESP messages.

    Field name:         Description (default):

    msg_id              PNS_NAME_QUERY_RESP
    total_matches       total matches found
    matches_in_this_msg (read only field!) == len(matches)
    matches             matches in this message:
                        list of tuples (name, device id, object id, record flags)

    FIXME: object id is not handled as a 10 bit value!

        device_id = names[index+1] & 0xFC
        object_id = ((names[index+1] & 0x03) << 8) + \
                      names[index+2] & 0xFF
    """

    def __init__(self, **isi_message_fields):
        NameServiceMessage.__init__(self, **isi_message_fields)
        self.initDefaults(msg_id=isi.PNS_NAME_QUERY_RESP, total_matches=None,
                          matches=[])
        self.assertFields(msg_id=isi.PNS_NAME_QUERY_RESP)

    def _get_msg_data(self):

        # Pack subblocks separately
        sub_data = []
        for name, dev_id, obj_id, rec_flags in self.matches:
            sub_data.extend(xpack('>LBBBB',name,dev_id,obj_id,rec_flags,0))

        return xpack('>HHH*[',
                     self.total_matches, self.matches_in_this_msg, 0, sub_data)

    def _get_msg_data_str(self):
        return 'total matches:%s matches:%s' % \
               (self.total_matches_str, self.matches_str)

    def _check_set_msg_data(self, new_msg_data):

        if new_msg_data:
            self.failUnless(not None in new_msg_data, \
                "None is not allowed in message data: %s" % str(new_msg_data))

        # First unpack common fields..
        self.total_matches, matches_in_this_msg, reserved, sub_data = \
            xunpack('>HHH*[', new_msg_data)

        # FIXME: Decide if we unpack only matches_in_this_msg# sub blocks or
        #        all possible fields.. (and then assert for extra stuff)

        # .. then take care of the subblocks.
        self.matches = []
        while sub_data:
            name_value, dev_id, obj_id, rec_flags, reserved, sub_data = \
                xunpack('>LBBBB*[',sub_data)
            self.matches.append((name_value,dev_id,obj_id,rec_flags))

        # And finally, assert the message data complies with the specification:
        self.assertDefined(
            ['total_matches', 'matches_in_this_msg', 'matches'])

        # FIXME: Check match fields?

        if matches_in_this_msg != len(self.matches):
            self.failField('matches_in_this_msg',
                'Sub block count:%s does not match with data:%s' % \
                (matches_in_this_msg, self.matches_str))

        return new_msg_data

    def _get_matches_in_this_msg(self):
        return len(self.matches)

    def _get_total_matches_str(self):
        return self.total_matches is not None \
               and '0x%04X' % self.total_matches or str(None)

    def _get_matches_str(self):
        #return ', '.join([\
        #    '(name:0x%08X device:0x%02X object:0x%02X flags:0x%02X)' % match \
        #     for match in self.matches])
        return str(self.matches)

    def addMatch(name_value, device_id, object_id, record_flags):
        # FIXME: assert values?
        # Note: This function is mainly used for constructing expected resps.
        self.matches.append((name_value, device_id, object_id, record_flags))

# ============================================================================
#   3.2     queryName function
# ----------------------------------------------------------------------------
def queryName(phone, name_value, mask_value=0xFFFFFFFFL):
    """Query name(s) from the name service.

        name_value      32-bit name
        mask_value      32-bit mask

        returns:        list of matched names in tuples:
                        (32-bit name, device id, 10-bit object id, rec. fields)

    """
    req = NameQueryReq(name=name_value, mask=mask_value)

    phone.sendMsg(req)
    matched_names = []
    while 1:
        resp = NameQueryResp(isi_message=\
                        phone.recvMsgFrom(req.resource))
        if resp.matches:
            matched_names.extend(resp.matches)

        if resp.total_matches == len(matched_names):
            break

    return matched_names
