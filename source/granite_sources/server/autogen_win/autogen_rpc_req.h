/*
NOKIA
CoreSW Copenhagen
Corleone









                autogen_rpc_req.h
                -----------------

                SW Include






Status:           DRAFT

Continuus DB:     co_pctls

Project:          autogen

%name:            autogen_rpc_req.h %

%version:         co1tss#4 %

%instance:        co_pctls_1 %

%derived_by:      eliasen %

%date_modified:   Mon Sep  4 16:26:25 2006 %

Copyright (c) 2003-2005. Nokia Corporation. All rights reserved


Change history:

VERSION     : 4          DRAFT        04-Sep-2006  Stig Holmsten Eliasen
REASON      : Optimizations
REFERENCE   : JK06082943672
DESCRIPTION : Updated according to requirement.

VERSION     : 3          DRAFT        02-May-2005  Christian J. Hansen
REASON      : Improvement
REFERENCE   : -
DESCRIPTION : Updated to use properties

VERSION     : 2          DRAFT        20-Jun-2003  Christian J. Hansen
REASON      : Change
REFERENCE   : Task: co_pctls#21842
DESCRIPTION : Changed resource type to RESOURCE_PHONET_EXT

VERSION     : 1          DRAFT        25-Feb-2003  Christian J. Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the file
*/

/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    Contains definitions for the RPC REQ resource.
    To be used until file is officially made and released
*/


/* ============================================================================================= */
/* Symbol definitions */
/* ============================================================================================= */

/* Message ID's */

/* request message IDs */
#define dev_sw_version_get      0x00
#define dev_get_info_get        0x01


RES_BEGIN(RESOURCE_PHONET_EXT, PN_RPC_REQ, RPC_REQ, "Remote Procedure Calls (Requests)", "", FALSE)
    

    /* --------------------------------------------------------------------- */
    /* Symbol tables */
    /* --------------------------------------------------------------------- */

    CONST_TBL_BEGIN(TRACE_FILE, 8, BE, "", "")
        CONST_TBL_ENTRY(TRACE_FILE_PMD, 0x41, "")
        CONST_TBL_ENTRY(TRACE_FILE_TRC, 0x4A, "")
        CONST_TBL_ENTRY(TRACE_FILE_INC, 0x50, "")
        CONST_TBL_ENTRY(TRACE_FILE_MED, 0x4d, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(RPC_ARG_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(PN_RPC_ARG_VOID,   0x00, "")
        CONST_TBL_ENTRY(PN_RPC_ARG_BYTE,   0x01, "")
        CONST_TBL_ENTRY(PN_RPC_ARG_WORD,   0x02, "")
        CONST_TBL_ENTRY(PN_RPC_ARG_STRING, 0x03, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(RPC_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(PN_RPC_TYPE_BYTE,   0x01, "")
    CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* Messages */
    /* --------------------------------------------------------------------- */

    MSG_BEGIN(dev_sw_version_get, MESSAGE_REQ, "", "")
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY_STRING(PROPERTY_ITEM_DEFAULT_VALUE, "PN_RPC_ARG_STRING")
        VALUE_CONST(string, "string", RPC_ARG_TYPE)
        PROPERTY_STRING(PROPERTY_ITEM_DEFAULT_VALUE, "PN_RPC_ARG_VOID")
        VALUE_CONST(void_type, "void", RPC_ARG_TYPE)
    MSG_END

    MSG_BEGIN(dev_get_info_get, MESSAGE_REQ, "", "")
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY_STRING(PROPERTY_ITEM_DEFAULT_VALUE, "PN_RPC_ARG_STRING")
        VALUE_CONST(string, "string", RPC_ARG_TYPE)
        VALUE_CONST(type, "type", RPC_TYPE)
        PROPERTY_STRING(PROPERTY_ITEM_DEFAULT_VALUE, "TRACE_FILE_PMD")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(trace_file, "File Type", TRACE_FILE)
    MSG_END

RES_END


/* End of file autogen_rpc_req.h */
