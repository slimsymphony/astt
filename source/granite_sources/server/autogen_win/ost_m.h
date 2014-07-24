/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                ost_m.h
                ----------
                SW Include






Project:          autogen

%name:            ost_m.h %
%version:         3 %
%instance:        co1tss_1 %
%derived_by:      nosterga %
%date_modified:   Tue Aug  4 16:59:16 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen / ost_m.h

    This file contains macro definitions for the OST protocol.
*/


#ifdef AUTOGEN_INCLUDE_OST

/* ============================================================================================= */
/* OST Control Protocol                                                                          */
/* ============================================================================================= */

#ifdef AUTOGEN_INCLUDE_OST_CONTROL_PROTOCOL

#define OST_CONTROL_PROTOCOL 0x00

PROPERTY(PROPERTY_PROTOCOL_HAS_NO_MESSAGES)
RES_BEGIN(RESOURCE_OST, OST_CONTROL_PROTOCOL, OST_CP, "OST Control Protocol", "", FALSE)

    MSG_BEGIN(AUTOGEN_NO_MESSAGE_ID, MESSAGE_NONE, "", "")
        SEQ_OF_REF(ost_control_protocol, "OST Control Protocol", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
    MSG_END

RES_END

#endif

/* ============================================================================================= */
/* OST PhoNet                                                                                    */
/* ============================================================================================= */

#ifdef AUTOGEN_INCLUDE_OST_PHONET_PROTOCOL

#define OST_PHONET           0x80

PROPERTY(PROPERTY_PROTOCOL_HAS_NO_MESSAGES)
RES_BEGIN(RESOURCE_OST, OST_PHONET, OST_PHONET, "PhoNet Protocol", "", FALSE)

    MSG_BEGIN(AUTOGEN_NO_MESSAGE_ID, MESSAGE_NONE, "", "")
        BLOCK_REF(BE, msg, "Msg", BLOCK_PROTOCOL, "PROTOCOL_PHONET", NULL, 0, REF_LENGTH_UNKNOWN)
    MSG_END

RES_END

#endif

/* ============================================================================================= */
/* OST Tracebox Control                                                                          */
/* ============================================================================================= */

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT

#define OST_TRACEBOX_CONTROL 0x81

#define AUTOGEN_INCLUDE_TB_INTO_OST

/* Redefine COMMON_MSG_HDR because Transaction ID is removed when transporting over OST */
#undef  COMMON_MSG_HDR
#define COMMON_MSG_HDR \
    REFERENCE(8, BE, message_id, "Message ID", MSG_ID)

/* Redefine COMMON_SUB_MSG_HDR because Transaction ID is removed when transporting over OST */
#undef  COMMON_SUB_MSG_HDR
#define COMMON_SUB_MSG_HDR \
    COMMON_MSG_HDR \
    REFERENCE(8, BE, sub_message_id, "Sub Message ID", SUB_MSG_ID)

#include "autogen_ostrich.h"
#undef AUTOGEN_INCLUDE_TB_INTO_OST

/* Reset the original meaning of COMMON_MSG_HDR and COMMON_SUB_MSG_HDR */
#include "isi_macros_empty.h"
#include "isi_macros.h"

#endif

/* ============================================================================================= */
/* OST XTI v3 traces                                                                             */
/* ============================================================================================= */

#ifdef AUTOGEN_INCLUDE_OST_XTIV3

#define OST_XTIv3            0x84

#define OST_XTIv3_MSG        0x00

PROPERTY(PROPERTY_PROTOCOL_HAS_NO_MESSAGES)
RES_BEGIN(RESOURCE_OST, OST_XTIv3, OST_XTIv3, "XTI v3", "", FALSE)

    PROPERTY(PROPERTY_PMD_MESSAGE_IS_CARRIER)
    PROPERTY(PROPERTY_PMD_PUBLIC)
    MSG_BEGIN(OST_XTIv3_MSG, MESSAGE_IND, "", "")
        VALUE(8, BE, tracebox_port, "Tracebox Port", HEX)
        REFERENCE(8, BE, master, "Master", XTI_MASTER_ID)
        VALUE(8, BE, channel, "Channel", HEX)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        BLOCK_REF(BE, data, "Data", BLOCK_PMD_ANCHOR, "XTI_MASTER_STRUCTURE", NULL, 0, REF_AS_MANY_AS_POSSIBLE)
    MSG_END
RES_END

#endif

#endif /* AUTOGEN_INCLUDE_OST */
