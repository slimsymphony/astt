/*
NOKIA
CoreSW Copenhagen
Corleone









                autogen_rpc_resp.h
                ------------------

                SW Include






Status:           DRAFT

Continuus DB:     co_pctls

Project:          autogen

%name:            autogen_rpc_resp.h %

%version:         co1tss#5 %

%instance:        co_pctls_1 %

%derived_by:      eliasen %

%date_modified:   Mon Sep  4 16:26:36 2006 %

Copyright (c) 2003-2005. Nokia Corporation. All rights reserved


Change history:

VERSION     : 5          DRAFT        04-Sep-2006  Stig Holmsten Eliasen
REASON      : Optimizations
REFERENCE   : JK06082943672
DESCRIPTION : Updated according to requirement.

VERSION     : 4          DRAFT        02-May-2005  Christian J. Hansen
REASON      : Improvement
REFERENCE   : -
DESCRIPTION : Updated to use properties
              Defined message pair relations

VERSION     : 3          DRAFT        15-Jul-2003  Christian J. Hansen
REASON      : Bug fix
REFERENCE   : Task: co_pctls#22110
DESCRIPTION : Fixed decoding of RPC0 response

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

    Contains definitions for the RPC RESP resource.
    To be used until file is officially made and released
*/


/* ============================================================================================= */
/* Symbol definitions */
/* ============================================================================================= */

/* Message ID's */

/* repsonse message IDs */
#define dev_sw_version_resp     0x00
#define dev_get_info_resp       0x01


RES_BEGIN(RESOURCE_PHONET_EXT, PN_RPC_RESP, RPC_RESP, "Remote Procedure Calls (Responses)", "", FALSE)
    

    /* --------------------------------------------------------------------- */
    /* Symbol tables */
    /* --------------------------------------------------------------------- */

    CONST_TBL_BEGIN(RPC_ARG_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(PN_RPC_ARG_VOID,   0x00, "")
        CONST_TBL_ENTRY(PN_RPC_ARG_BYTE,   0x01, "")
        CONST_TBL_ENTRY(PN_RPC_ARG_WORD,   0x02, "")
        CONST_TBL_ENTRY(PN_RPC_ARG_STRING, 0x03, "")
    CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* Messages */
    /* --------------------------------------------------------------------- */

    MSG_BEGIN(dev_sw_version_resp, MESSAGE_RESP, "", "")
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        VALUE_CONST(string, "string", RPC_ARG_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, sv_version, "SW Version", 
            REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
    MSG_END

    MSG_PAIR_EXT(dev_sw_version_get, dev_sw_version_resp, PN_RPC_REQ)

    MSG_BEGIN(dev_get_info_resp, MESSAGE_RESP, "", "")
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        VALUE_CONST(string, "string", RPC_ARG_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, filename, "Filename", 
            REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
    MSG_END

    MSG_PAIR_EXT(dev_get_info_get, dev_get_info_resp, PN_RPC_REQ)

RES_END


/* End of file autogen_rpc_resp.h */
