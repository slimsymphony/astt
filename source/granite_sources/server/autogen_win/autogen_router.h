/*
NOKIA
CoreSW Copenhagen
Corleone












                PhoNet Router Message Macros
                ----------------------------
                SW Include Document


Project  : coresw

Name     : pn_router_isi_m.h

Version  : 1

Type     : incl

Instance : co_core#1



Copyright (c) Nokia Corporation. All rights reserved.



Change History:


VERSION     : 2          DRAFT        04-Sep-2006  Stig Holmsten Eliasen
REASON      : Optimizations
REFERENCE   : JK06082943672
DESCRIPTION : Updated according to requirement.

VERSION     : 1         -        20-Jun-2003  Christian J. Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the file.

------------------------------------------------------------------------------
*/

PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,    "")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16, "")

RES_BEGIN(RESOURCE_ISI, PN_ROUTER, ROUTER, "PhoNet Router", "", FALSE)

    CONST_TBL_BEGIN(DEVICE_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(PN_DEV_TYPE_PHONET_HOST,  0x00, "")
        CONST_TBL_ENTRY(PN_DEV_TYPE_PHONET_SLAVE, 0x01, "")
        CONST_TBL_ENTRY(PN_DEV_TYPE_NON_PHONET,   0x02, "")
        CONST_TBL_ENTRY(PN_DEV_TYPE_DONT_CARE,    0x03, "")
        CONST_TBL_ENTRY(PN_DEV_TYPE_ACCESSORY,    0x04, "")
    CONST_TBL_END


    /* PNS_DEV_ADDED_IND */

    MSG_BEGIN(PNS_DEV_ADDED_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(device_id, "Device ID", PN_DEVICE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(device_type, "Device type", DEVICE_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(media, "Media", PN_MEDIA)
    MSG_END

    /* PNS_DEV_REMOVED_IND */

    MSG_BEGIN(PNS_DEV_REMOVED_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(device_id, "Device ID", PN_DEVICE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(device_type, "Device type", DEVICE_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(media, "Media", PN_MEDIA)
    MSG_END

RES_END

/* End of file pn_router_isi_m.h */
