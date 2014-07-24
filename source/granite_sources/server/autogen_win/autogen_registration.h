/*
NOKIA
CoreSW Copenhagen
Corleone












                PhoNet Registration Message Macros
                ----------------------------------
                SW Include Document


Project  : coresw

Name     : pn_registration_m.h

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

#define MSG_HDR \
    REFERENCE(8, BE, msg_id, "Message ID", MSG_ID)

#define FIELD_HEADER \
    PROPERTY(PROPERTY_PMD_PARAMETER) \
    COMMON_SB

/* === Constants for optional fields in registration command === */
#define PN_REG_FIELD_VERSION             0x00  /* 0 */
#define PN_REG_FIELD_DEVICE_TYPE         0x01  /* 1 */
#define PN_REG_FIELD_LINK_INFO           0x02  /* 2 */
#define PN_REG_FIELD_MEDIA_SPECIFIC      0x03  /* 3 */
#define PN_REG_FIELD_H2H_REQ             0x04  /* 4 */
#define PN_REG_FIELD_H2H_RESP            0x05  /* 5 */


PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,    "")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16, "")

PROPERTY(PROPERTY_ALIGNMENT_CHECK_DISABLE)

RES_BEGIN(RESOURCE_PHONET, PN_REGISTRATION, REG, "PhoNet Registration", "", FALSE)

    CONST_TBL_BEGIN(REG_DEVICE_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(PN_DEV_TYPE_PHONET_HOST, 0x00, "")
        CONST_TBL_ENTRY(PN_DEV_TYPE_PHONET_SLAVE, 0x01, "")
        CONST_TBL_ENTRY(PN_DEV_TYPE_NON_PHONET, 0x02, "")
        CONST_TBL_ENTRY(PN_DEV_TYPE_DONT_CARE, 0x03, "")
        CONST_TBL_ENTRY(PN_DEV_TYPE_ACCESSORY, 0x04, "")
    CONST_TBL_END


    /* Sequences */

    SEQ_BEGIN(REG_FIELD_DATA, DONT_CREATE_STRUCT, "", "")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, data, "Data", HEX)
    SEQ_END


    /* Sub blocks */

    PROPERTY(PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY)
    SB_BEGIN(PN_REG_FIELD_VERSION, "", "")
        FIELD_HEADER
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, xx, "XX", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, yy, "YY", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, zz, "ZZ", DEC)
    SB_END

    PROPERTY(PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY)
    SB_BEGIN(PN_REG_FIELD_DEVICE_TYPE, "", "")
        FIELD_HEADER
        SEQ_OF_REF(data, "Data", REG_FIELD_DATA, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
    SB_END

    PROPERTY(PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY)
    SB_BEGIN(PN_REG_FIELD_LINK_INFO, "", "")
        FIELD_HEADER
        SEQ_OF_REF(data, "Data", REG_FIELD_DATA, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
    SB_END

    PROPERTY(PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY)
    SB_BEGIN(PN_REG_FIELD_MEDIA_SPECIFIC, "", "")
        FIELD_HEADER
        SEQ_OF_REF(data, "Data", REG_FIELD_DATA, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
    SB_END

    PROPERTY(PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY)
    SB_BEGIN(PN_REG_FIELD_H2H_REQ, "", "")
        FIELD_HEADER
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, prot, "Protocol version", DEC)
    SB_END

    PROPERTY(PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY)
    SB_BEGIN(PN_REG_FIELD_H2H_RESP, "", "")
        FIELD_HEADER
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, prot, "Protocol version", DEC)
    SB_END


    /* Messages */

    /* PNS_REGISTRATION_CMD */

    MSG_BEGIN(PNS_REGISTRATION_CMD, MESSAGE_REQ, "", "")
        MSG_HDR
    MSG_END


    /* PNS_DEREGISTRATION_CMD */

    MSG_BEGIN(PNS_DEREGISTRATION_CMD, MESSAGE_REQ, "", "")
        MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(all_dev, "All Devices", TRUE_FALSE)
    MSG_END


    /* PNS_DYNAMIC_REG */

    MSG_BEGIN(PNS_DYNAMIC_REG_REQ, MESSAGE_REQ, "", "")
        MSG_HDR
        FILLER(FILLER_FIXED, 8)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, ran_num, "Random Number", HEX)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(dev_type, "Device Type ID", REG_DEVICE_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(asked, "Asked Number", PN_DEVICE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, optional, "Optional Fields", REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PN_REG_FIELD_VERSION)
            SB_LST_ENTRY(PN_REG_FIELD_DEVICE_TYPE)
            SB_LST_ENTRY(PN_REG_FIELD_LINK_INFO)
            SB_LST_ENTRY(PN_REG_FIELD_MEDIA_SPECIFIC)
            SB_LST_ENTRY(PN_REG_FIELD_H2H_REQ)
            SB_LST_ENTRY(PN_REG_FIELD_H2H_RESP)
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(PNS_DYNAMIC_REG_RESP, MESSAGE_RESP, "", "")
        MSG_HDR
        FILLER(FILLER_FIXED, 8)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, ran_num, "Random Number", HEX)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(dev_type, "Device Type ID", REG_DEVICE_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(dev, "Device ID", PN_DEVICE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, optional, "Optional Fields", REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PN_REG_FIELD_VERSION)
            SB_LST_ENTRY(PN_REG_FIELD_DEVICE_TYPE)
            SB_LST_ENTRY(PN_REG_FIELD_LINK_INFO)
            SB_LST_ENTRY(PN_REG_FIELD_MEDIA_SPECIFIC)
            SB_LST_ENTRY(PN_REG_FIELD_H2H_REQ)
            SB_LST_ENTRY(PN_REG_FIELD_H2H_RESP)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PNS_DYNAMIC_REG_REQ, PNS_DYNAMIC_REG_RESP)


    /* PNS_FIXED_REG */

    MSG_BEGIN(PNS_FIXED_REG_REQ, MESSAGE_REQ, "", "")
        MSG_HDR
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, optional, "Optional Fields", REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PN_REG_FIELD_VERSION)
            SB_LST_ENTRY(PN_REG_FIELD_DEVICE_TYPE)
            SB_LST_ENTRY(PN_REG_FIELD_LINK_INFO)
            SB_LST_ENTRY(PN_REG_FIELD_MEDIA_SPECIFIC)
            SB_LST_ENTRY(PN_REG_FIELD_H2H_REQ)
            SB_LST_ENTRY(PN_REG_FIELD_H2H_RESP)
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(PNS_FIXED_REG_RESP, MESSAGE_RESP, "", "")
        MSG_HDR
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, optional, "Optional Fields", REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PN_REG_FIELD_VERSION)
            SB_LST_ENTRY(PN_REG_FIELD_DEVICE_TYPE)
            SB_LST_ENTRY(PN_REG_FIELD_LINK_INFO)
            SB_LST_ENTRY(PN_REG_FIELD_MEDIA_SPECIFIC)
            SB_LST_ENTRY(PN_REG_FIELD_H2H_REQ)
            SB_LST_ENTRY(PN_REG_FIELD_H2H_RESP)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PNS_FIXED_REG_REQ, PNS_FIXED_REG_RESP)

RES_END


/* End of file pn_registration_m.h */
