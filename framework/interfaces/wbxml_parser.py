# -*- coding: utf-8 -*-
# ============================================================================
# NOKIA
# MP
#
# %full_filespec:   wbxml_parser.py
#                   ----------------------------------------------------------
#                   Granite Module - Python
#
#
# Copyright (c)     Nokia. All rights reserved.
#
# ----------------------------------------------------------------------------
""" Granite internal

    WBXML -> XML parser. """

# ============================================================================
# Module Setup

# Python library module imports
import os, types, clr

clr.AddReference('GraniteWbxmlDecoder')

from Nokia.Granite.Tracing.Decoding import GraniteWbxmlDocument
from System import Array, Byte

import core
from utils.nodeutils import NodeUtils

global captureIndex, errorBitmapIndex
captureIndex, errorBitmapIndex = 0, 0


def parseWbxml(data, phoneName=None):
    """Parses wbxml data coming from Granite server. Call in srv_granite.py
       Return value will be NodeUtils instance.
    """
    global captureIndex, errorBitmapIndex

    #import time
    #startTime = time.clock()

    #testFile = open('wbxml_data.txt', 'w')
    #testFile.write(str([hex(x) for x in data]) + '\n\n')
    #testFile.close()

    if phoneName and phoneName!='Main':
        resultDir = os.path.join(core.FW_conf['test_result_dir'],phoneName)
    else:
        resultDir = core.FW_conf['test_result_dir']

    # load data to wbxml as byte array            
    GraniteWbxmlDocument.Instance.Decode(Array[Byte](data),
                                resultDir,
                                "",
                                core.FW_conf['error_capture'],
                                captureIndex, errorBitmapIndex)

    respTeststepDoc, captureIndex, errorBitmapIndex = GraniteWbxmlDocument.Instance.ResponseData

    respTeststep = NodeUtils(respTeststepDoc)

    del respTeststepDoc

    GraniteWbxmlDocument.Instance.ResponseData.Clear()
        
    # debug.brf('********* wbxml parse took: %s' % str(time.clock() - startTime))
    
    debug.out('Response teststep:')
    debug.out(respTeststep.toprettyxml())
               
    return respTeststep

