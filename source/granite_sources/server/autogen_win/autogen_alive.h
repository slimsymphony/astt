/*
NOKIA MOBILE PHONES
R&D Copenhagen
VALHALLA CL - CPH












                PhoNet Alive Message Macros
                ----------------------------------
                SW Include Document


Project  : coresw

Name     : pn_alive_isi_m.h

Version  : 1

Type     : incl

Instance : co_core#1



Copyright (c) Nokia Corporation. All rights reserved.



Change History:


VERSION     : 1         -        18-May-2004  Christian J. Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the file.

------------------------------------------------------------------------------
*/

#define ALIVE_REQ       0x00
#define ALIVE_RESP      ALIVE_REQ

PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,    "")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16, "")

PROPERTY(PROPERTY_ALIGNMENT_CHECK_DISABLE)
PROPERTY(PROPERTY_DEVICE_DEPENDENT_MESSAGES)

PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, PN_DEV_DSP_AUX)

RES_BEGIN(RESOURCE_ISI, PN_ALIVE, ALIVE, "Alive", "", FALSE)

    /* Messages */

    /* ALIVE */

    MSG_BEGIN(ALIVE_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ALIVE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_PAIR(ALIVE_REQ, ALIVE_RESP)

RES_END


/* End of file pn_alive_isi_m.h */
