# -*- coding: utf-8 -*-
""" Granite FW's XML -> WBXML encoder.

    Notes

    The latest WAP Binary XML Content Format (WBXML) specification can be
    found from here: http://www.w3.org/TR/wbxml/
"""

# ============================================================================
# Module Setup

# Python library module imports
import types

import core
from interfaces.c_srv.srv_kbd import kbd
from utils import include

font = include.Include('font_def_priv.h')
grn = include.Include('granite_p_isi.h')


# ============================================================================
class Wbxml:
# ----------------------------------------------------------------------------
    data = []

    def parse(self, testcase):
        """Add basic tokens:
            wbxml version
            Public Identifier
            UTF-8 charset
            String table length
        """
        self.test = testcase
        
        # some attributes are removed before sending step to server
        # Thus, clone must be made here
        teststep = testcase.teststep.clone()
        
        self.data = []
        self.splitData = []
        self.data.extend([grn.GRN_WBXML_VERSION,
                          grn.GRN_WBXML_PUBLIC_ID,
                          grn.GRN_WBXML_CHARSET_UTF8,
                          0]) # GRN_WBXML_STRTAB_LENGTH is always 0

        self.testStephandler(teststep)
        self.splitData.append(self.data)
        
        self.test = None
        self.data = []
                
        return self.splitData

    def testStephandler(self, teststep):
        """Handle teststep/rootTag"""
        if teststep.getAttributes() and teststep.getChildNodes():
            self.data.append(grn.GRN_WBXML_C | grn.GRN_WBXML_A | grn.GRN_WBXML_TAG_teststep)
            self.handleAttributes(teststep)
            self.handleChildren(teststep)
        else:
            if teststep.getAttributes():
                self.data.append(grn.GRN_WBXML_A | grn.GRN_WBXML_TAG_teststep)
                self.handleAttributes(teststep)
            else:
                if teststep.getChildNodes():
                    self.data.append(grn.GRN_WBXML_C | grn.GRN_WBXML_TAG_teststep)
                    self.handleChildren(teststep)
                else:
                    self.data.append(grn.GRN_WBXML_TAG_teststep)

        self.data.append(grn.GRN_WBXML_END)

    def handleChildren(self, node):
        """Handle given tag childNodes"""
        for child in node.getChildNodes():
            self.checkDataLength()
            if child.getName() in ["key_in", "expect", "text", "keyblock",
                                   "sx", "animation", "capture", "keypress",
                                   "delay", "display", "config", "bitmap",
                                   "block", "touch", "press", "move", "release"]:
                self.handleTag(child)
            else:
                if child.getName() == "data":
                    self.handleDataTag(child)
                else:
                    debug.err("unknown child: %s" % child)

    def handleTag(self, tag):
        """Check tag and apply information to wbxml format"""
        tag = self.checkUnsupportedAttributes(tag)

        if tag.getName() in  ['text', 'sx', 'animation']:
            if tag.getAttributes():
                self.data.append(grn.GRN_WBXML_C | grn.GRN_WBXML_A | \
                                 getattr(grn, "GRN_WBXML_TAG_" + \
                                         tag.getName()))
                self.handleAttributes(tag)
                self.data.append(grn.GRN_WBXML_END)
            else:
                self.data.append(grn.GRN_WBXML_C | \
                         getattr(grn, "GRN_WBXML_TAG_" + \
                                 tag.getName()))

            self.handleTextElement(tag['text'])
        else:
            if tag.getChildNodes() and tag.getAttributes():
                self.data.append(grn.GRN_WBXML_C | grn.GRN_WBXML_A | \
                                 getattr(grn, "GRN_WBXML_TAG_" + \
                                         tag.getName()))
                self.handleAttributes(tag)
                self.handleChildren(tag)
            else:
                if tag.getChildNodes():
                    self.data.append(grn.GRN_WBXML_C | \
                                     getattr(grn, "GRN_WBXML_TAG_" + \
                                             tag.getName()))
                    self.handleChildren(tag)
                else:
                    self.data.append(grn.GRN_WBXML_A | \
                                     getattr(grn, "GRN_WBXML_TAG_" + \
                                             tag.getName()))
                    self.handleAttributes(tag)

        self.data.append(grn.GRN_WBXML_END)

    def checkUnsupportedAttributes(self, tag):
        """This method checks all non supported attributes from tag."""
        for attribute in tag.getAttributes():
            if attribute == 'zoneName' or attribute == 'layoutName':
                tag.removeAttribute(attribute)
            if attribute == 'name':
                if tag.getName() in ['display', 'animation', 'bitmap', 'capture']:
                    tag.removeAttribute(attribute)
        return tag

    def handleTextElement(self, value):
        """This method handle given text to wbxml format."""
        if value.strip():
            self.data.append(grn.GRN_WBXML_STR_I)

            if type(value) == types.UnicodeType:
                st = value.encode('utf-8')
            else:
                st = unicode(value, 'Latin-1').encode('utf-8')

            for char in st:
                self.data.append(ord(char))

            self.data.append(0x00)
            self.checkDataLength()

    def handleAttributes(self, element):
        """This method handle given tag attributes"""
        for attribute in element.getAttributes():
            if attribute in ["length", "wait", "timeout", "repeat", "x", "y",
                             "height", "width", "format", "checksum",
                             "animation_id", "max_isi_data_length", "screen",
                             "offset", "gap", "repeat", "masku", "maskd",
                             "maskl", "maskr", "long_press_length",
                             "repeat_length", "keypress_length",
                             "keypress_wait", "short_press_length",
                             "keys_idle_length", "touch_id"]:
                # NOTE: getattr None is done to ensure backwards compatibility
                attrDefine = getattr(grn, "GRN_WBXML_ATTR_" + attribute, None)

                if not attrDefine is None:
                    self.data.append(attrDefine)
                    self.mb_u_int32(element[attribute])
                else:
                    debug.err('%s WAS NOT FOUND FROM GRANITE DEFINE FILES!' % \
                              attribute)
            else:
                if attribute == "key":
                    self.data.append(grn.GRN_WBXML_ATTR_key)
                    self.handleKeyAttribute(element[attribute])
                else:
                    if attribute in ["highlighted", "valid", "truncated",
                                     "items", "bitmap_capture", "dimmed",
                                     "wildcard", "action", "background", "ntf_sending"]:
                        self.data.append(getattr(grn, 'GRN_WBXML_ATTR_' + \
                                                 attribute))
                        self.handleEnumeratedAttribute(element[attribute])
                    else:
                        if attribute == "name":
                            self.data.append(grn.GRN_WBXML_ATTR_name)
                            self.handleTextElement(element[attribute])
                        else:
                            if attribute == "font":
                                self.data.append(grn.GRN_WBXML_ATTR_font)
                                self.handleFontAttribute(element[attribute])
                            elif not attribute in ["save", "waitUntilNoUIevents", "dragHold"]:# Ignore save, waitUntilNoUIevents and dragHold attributes
                                debug.err("unknown attribute: %s" % attribute)

        # FIXME: get rid of this if
        if element.getChildNodes():
            self.data.append(grn.GRN_WBXML_END)

    def handleEnumeratedAttribute(self, value):
        """handle enumerated attributes to wbxml format"""
        try:
            self.data.append(getattr(grn, 'GRN_WBXML_ATTR_VALUE_' + value))
        except AttributeError:
            self.test.fail("Unknown attribute value: %r " % value)

    def handleKeyAttribute(self, value):
        self.mb_u_int32(getattr(kbd, value))

    def mb_u_int32(self, value):
        """This method convert given value to mb_u_int32 format"""
        c = long(value)
        i = 0
        if c <= 0x7F:
            "1 byte encoding."
            "Single byte value follows"
            self.data.append(grn.GRN_WBXML_EXT_T_0)
            self.data.append(c)
        else:
            "2 -> n byte encoding"
            "Multi byte value follows"
            self.data.append (grn.GRN_WBXML_EXT_T_0)
            result = []
            j = 0
            while c > 0:
                i = c & 0x7F
                if j > 0:
                    i = i | 0x80
                result.append (i)
                c = c >> 7
                j = j + 1

            i = len(result) - 1;
            while i >= 0:
                self.data.append(result[i])
                i = i - 1

    def handleFontAttribute(self, value):
        """Handle font attribute to wbxml format"""
        fontname = ""
        fonttype = ""
        if value.find('-') >= 0:
            fontname = 'FONT_NAME_PRIV_' + value.split('-')[0]
            fonttype = 'FONT_TYPE_PRIV_' + value.split('-')[1]
        else:
            fontname = 'FONT_NAME_PRIV_' + value

        if not fonttype:
            fontdata =  getattr(font, fontname)
        else:
            fontdata = getattr(font, fontname) + (getattr(font, fonttype) << 16)

        self.mb_u_int32(fontdata)

    def handleDataTag(self, dataTag):
        """Handle Data tag"""
        firstChildsValue = dataTag.getChildNodes[0]
        self.checkDataLength(len(firstChildsValue) / 2)
        self.data.append(grn.GRN_WBXML_C | grn.GRN_WBXML_TAG_data)
        self.opaque(firstChildsValue) # content
        self.data.append(grn.GRN_WBXML_END)

    def opaque(self, value):
        """Handle opaque data
            value must be string.
            Ex. 0x80 = '80'
        """
        opaqueData = []

        for i in range(0, len(value), 2):
            opaqueData.append(int(value[i:i + 2], 16))

        self.data.append(grn.GRN_WBXML_OPAQUE)
        self.mb_u_int32(len(opaqueData))
        self.data.extend(opaqueData)

    def checkDataLength(self, value=None):
        """Check data length.
            Value must be len()-value."""
        if not value: value = 0
        if len(self.data) + value >= core.FW_conf['encoder_isi_length'] - 300:
            self.splitData.append(self.data)
            self.data = []

def parse(testcase):
    wbxml = Wbxml()
    return wbxml.parse(testcase)
