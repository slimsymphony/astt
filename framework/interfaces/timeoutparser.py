# -*- coding: ascii -*-
# ============================================================================
# NOKIA
# Devices
# GTES, Testing Tools
#
#
# %full_filespec:   timeoutparser.py
#                   ----------------------------------------------------------
#                   Granite Module - Python
#
#
# Copyright (c)     Nokia. All rights reserved.
#
# ----------------------------------------------------------------------------
""" Granite internal

    Timeout parser for test steps. """
# ============================================================================
#   MODULE CODE
# ----------------------------------------------------------------------------

# ============================================================================
class TimeoutParser:
# ----------------------------------------------------------------------------
    timevalue = 0

    def parseAttributes(self, node):
        """Gets all teststep tags from nodeutils and calls handle methods.

            Parameters

            node         nodeutils instance
        """
        self.timevalue = 0

        # Take all necessary tags
        keypressList = node.findall('//keypress')
        configList = node.findall('//config')
        self.handleKeypressTagLists(keypressList, configList)

        expectList = node.findall('//expect')
        delayList = node.findall('//delay')
        touchList = node.findall('//press | //move | //release')
        sxList = node.findall('//sx')

        self.handletagList(expectList)
        self.handletagList(delayList)
        self.handletagList(touchList)
        self.handletagList(sxList)

        # add default timeout
        self.timevalue += 4000

        # minimum is 10000
        if self.timevalue < 10000:
            self.timevalue = 10000

        return long(self.timevalue)

    def handletagList(self, tagList):
        """Timeout handler for all tags except keypresses.

            Parameters

            tagList         list of nodeutils tags
        """
        delay = 50
        i = 0

        while i != len(tagList):
            try:
                # Take tag repeat attribute
                repeat = 1

                for attribute in tagList[i].getAttributes():
                    if attribute == "repeat":
                        repeat *= long(tagList[i][attribute])
            finally:
                for attribute in tagList[i].getAttributes():
                    if attribute == "timeout":
                        self.timevalue += long(tagList[i][attribute]) + delay
                        # add some extra "just in case"
                        self.timevalue += 5000
                    else:
                        if attribute == "length":
                            self.timevalue += repeat * (long(tagList[i][attribute]) + delay)

                        if attribute == "wait":
                            self.timevalue += repeat * (long(tagList[i][attribute]) + delay)

            # Check tags attributes and add default value if it's necessary

            if tagList[i].getName() == "capture":
                self.timevalue += repeat * 5000

            # increase timeout for sx dumps (in case of long list in capture)
            if tagList[i].getName() == "sx" and tagList[i]['text'] == 'dump':
                self.timevalue += repeat * 20000

            if tagList[i].getName() == "expect":
                if 'timeout' not in tagList[i].getAttributes():
                    self.timevalue += repeat * (15000 + delay)

            if 'wait' not in tagList[i].getAttributes():
                if tagList[i].getName() == "delay":
                    self.timevalue += repeat * (500 + delay)
                else:
                    if tagList[i].getName() == "info" or tagList[i].getName() == "keyblock":
                        self.timevalue += repeat * (1500 + delay)

            i = i + 1

    def handleKeypressTagLists(self, keypressList, configList):
        """Timeout handler for all tags except keypresses.

            Parameters

            keypressList         list of keypress nodeutils tags
            configList           list of config nodeutils tags
        """
        delay = 100
        i = 0

        while i != len(keypressList):
            try:
                # Take tag repeat attribute
                repeat = 1

                for attribute in keypressList[i].getAttributes():
                    if attribute == "repeat":
                        # NOTE: Only one repeat can exist in keypress
                        repeat = long(keypressList[i][attribute])
            finally:
                for attribute in keypressList[i].getAttributes():
                    if attribute in ["length", "wait"]:
                        self.timevalue += repeat * (long(keypressList[i][attribute]) + delay)

            if 'length' not in keypressList[i].getAttributes():
                # config tag value
                self.timevalue += repeat * (long(configList[0]["keypress_length"]) + delay)

            if 'wait' not in keypressList[i].getAttributes():
                # config tag value
                self.timevalue += repeat * (long(configList[0]["keypress_wait"]) + delay)

            i = i + 1

def getTimeout(node):
    value = TimeoutParser()
    return value.parseAttributes(node)
