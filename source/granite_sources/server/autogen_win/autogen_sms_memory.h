/*
NOKIA MOBILE PHONES
R&D Oulu
MAUI










            sms_memory_isi_m.h
            --------------------------

            SW include - ANSI C






Document code:      -


Copyright(c) Nokia Mobile Phones. All rights reserved.

Change history:

VERSION     : 000.034    DRAFT        18-May-2004  Christian Jacob Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the file
*/


/* ------------------------------------------------------------------------- */


/*  1    ABSTRACT

    1.1    Module type

    Header file for autogen
   

    1.2    Functional description

    This file is the message definition file for the SMS Memory Server


    1.3    Notes


    2    CONTENTS


    1    ABSTRACT
    1.1    Module type
    1.2    Functional description
    1.3    Notes

    2    CONTENTS

    3    CONSTANTS

    4    MACROS

    5    DATA TYPES

    6    CLASSES

    7    OBJECTS

    8    DATA STRUCTURES

    9    FUNCTION PROTOTYPES
*/


/*  3    CONSTANTS */

/* ISI Message ID's */

#define SMS_MEMORY_WRITE_REQ                  0x00
#define SMS_MEMORY_WRITE_RESP                 0x01
#define SMS_MEMORY_READ_REQ                   0x02
#define SMS_MEMORY_READ_RESP                  0x03
#define SMS_MEMORY_ERASE_REQ                  0x04
#define SMS_MEMORY_ERASE_RESP                 0x05
#define SMS_MEMORY_ERASE_BY_TYPE_REQ          0x06
#define SMS_MEMORY_ERASE_BY_TYPE_RESP         0x07
#define SMS_MEMORY_STATUS_REQ                 0x08
#define SMS_MEMORY_STATUS_RESP                0x09
#define SMS_MEMORY_WARNING_LEVEL_IND          0x0A
#define SMS_MEMORY_ERASED_IND                 0x0B
#define SMS_MEMORY_BROWSE_REQ                 0x0C
#define SMS_MEMORY_BROWSE_RESP                0x0D
#define SMS_MEMORY_HEADER_READ_REQ            0x0E
#define SMS_MEMORY_HEADER_READ_RESP           0x0F
#define SMS_MEMORY_FOLDER_WRITE_REQ           0x10
#define SMS_MEMORY_FOLDER_WRITE_RESP          0x11
#define SMS_MEMORY_FOLDER_READ_REQ            0x12
#define SMS_MEMORY_FOLDER_READ_RESP           0x13
#define SMS_MEMORY_FOLDER_ERASE_REQ           0x14
#define SMS_MEMORY_FOLDER_ERASE_RESP          0x15
#define SMS_MEMORY_RENAME_REQ                 0x16
#define SMS_MEMORY_RENAME_RESP                0x17
#define SMS_MEMORY_MOVE_REQ                   0x18
#define SMS_MEMORY_MOVE_RESP                  0x19
#define SMS_MEMORY_READY_IND                  0x1A
#define SMS_MEMORY_UPDATESTATUS_IND           0x1B

#define SMS_MEMORY_GETFREEREFNUMB_REQ         0x2A
#define SMS_MEMORY_GETFREEREFNUMB_RESP        0x2B

/* If the concatenation isn't supported the concatenation ID's are mapped on the simple ID's */
#if SMSFEA_MESSAGE_CONCATENATION

#define SMS_MEMORY_CONCAT_BROWSE_REQ          0x20
#define SMS_MEMORY_CONCAT_BROWSE_RESP         0x21
#define SMS_MEMORY_CONCAT_READ_REQ            0x22
#define SMS_MEMORY_CONCAT_READ_RESP           0x23
#define SMS_MEMORY_CONCAT_ERASE_REQ           0x24
#define SMS_MEMORY_CONCAT_ERASE_RESP          0x25
#define SMS_MEMORY_CONCAT_MOVE_REQ            0x26
#define SMS_MEMORY_CONCAT_MOVE_RESP           0x27
#define SMS_MEMORY_CONCAT_RENAME_REQ          0x28
#define SMS_MEMORY_CONCAT_RENAME_RESP         0x29

#else

#define SMS_MEMORY_CONCAT_BROWSE_REQ          SMS_MEMORY_BROWSE_REQ
#define SMS_MEMORY_CONCAT_BROWSE_RESP         SMS_MEMORY_BROWSE_RESP
#define SMS_MEMORY_CONCAT_READ_REQ            SMS_MEMORY_READ_REQ
#define SMS_MEMORY_CONCAT_READ_RESP           SMS_MEMORY_READ_RESP
#define SMS_MEMORY_CONCAT_ERASE_REQ           SMS_MEMORY_ERASE_REQ
#define SMS_MEMORY_CONCAT_ERASE_RESP          SMS_MEMORY_ERASE_RESP
#define SMS_MEMORY_CONCAT_MOVE_REQ            SMS_MEMORY_MOVE_REQ
#define SMS_MEMORY_CONCAT_MOVE_RESP           SMS_MEMORY_MOVE_RESP
#define SMS_MEMORY_CONCAT_RENAME_REQ          SMS_MEMORY_RENAME_REQ
#define SMS_MEMORY_CONCAT_RENAME_RESP         SMS_MEMORY_RENAME_RESP


#endif /* SMSFEA_MESSAGE_CONCATENATION */



/* Sub block ID's */

#define SMS_MEMORY_HEADER                     0x00 /* old id to be removed */
#define SMS_MEMORY_GSM_HEADER                 0x00 /* new id */
#define SMS_MEMORY_FOLDER_NAME                0x01
#define SMS_MEMORY_STATUS                     0x02
#define SMS_MEMORY_TEMPLATE_STATUS            0x03
#define SMS_MEMORY_PICTURE_TEMPLATE_STATUS    0x04
#define SMS_MEMORY_OVERWRITE_STATUS           0x05
#define SMS_MEMORY_FOLDER_STATUS              0x06
#define SMS_MEMORY_MSG_NAME_STATUS            0x07
#define SMS_MEMORY_GMS                        0xA0
#define SMS_MEMORY_PICTURE                    0xA1

/* Sub block ID's from sms_isi_m.h */

#define SMS_GSM_DELIVER                     0x00
#define SMS_GSM_STATUS_REPORT               0x01
#define SMS_GSM_SUBMIT                      0x02
#define SMS_GSM_COMMAND                     0x03
#define SMS_GSM_MT_UNDEFINED                0x04
#define SMS_GSM_MO_UNDEFINED                0x05

#define SMS_GSM_VALIDITY_PERIOD             0x08
#define SMS_GSM_PARAM_INDICATOR             0x09
#define SMS_GSM_OPTIONAL_FIELDS             0x0A

#define SMS_TDMA_DELIVER                    0x40
#define SMS_TDMA_SUBMIT                     0x41
#define SMS_TDMA_DELIVERY_ACK               0x42
#define SMS_TDMA_MANUAL_ACK                 0x43

#define SMS_TDMA_USER_DATA_UNIT             0x46
#define SMS_TDMA_ADDRESS_INFO               0x47

#define SMS_TDMA_TIME_REL                   0x49
#define SMS_TDMA_TIME_ABS                   0x4A
#define SMS_TDMA_CALLBACK_INFO              0x4B
#define SMS_TDMA_SIGNAL_INFO                0x4C

#define SMS_GSM_COMMON_DATA                 0x80
#define SMS_COMMON_DATA                     0x80
#define SMS_ALPHA_TAG                       0x81
#define SMS_ADDRESS                         0x82

#define SMS_TIME_INFO                       0x84




/* Miscellaneous Constants */

#define SMS_MEMORY_FOLDER_NAME_MAX_LENGTH       16
#define SMS_MEMORY_NAME_MAX_LENGTH              16
#define SMS_MEMORY_RENAME_MAX_LENGTH            14

#define SMS_GMS_BITMAP_DATA_MAX_LENGTH          (140 * 3)    
#define SMS_GMS_USER_DATA_MAX_LENGTH            (140 * 2) /* SMS_USER_DATA_MAX_LENGTH = 140 */

#define SMS_MEMORY_BROWSE_ITEM_MAX_COUNT        150

#define SMS_MEMORY_ADDRESS_MAX_LENGTH           12        /* SMS_ADDRESS_MAX_LENGTH */
#define SMS_MEMORY_TIME_STAMP_MAX_LENGTH        7         /* SMS_TIME_MAX_LENGTH */

#define SMS_MEMORY_FOLDER_UNSPECIFIED           0x00
#define SMS_MEMORY_FOLDER_FIRST_USER_DEFINED    0x06
#define SMS_MEMORY_FOLDER_LAST_USER_DEFINED     0x19

#define SMS_MEMORY_LOCATION_OF_FIRST_UNREAD_MSG 0
#define SMS_MEMORY_ALL_LOCATIONS                0

/* Constants from sms_isi_m.h */

#define SMS_SC_TIME_STAMP_SIZE              7
#define SMS_DISCHARGE_TIME_SIZE             7
#define SMS_GSM_PARAM_INDICATOR_MAX_LEN     10

/*  4    MACROS */

#define SMS_MEM_MSG_HDR \
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    SMS_MEMORY_COMMON_FIELD;") \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE(8, BE, trans_id, "Transaction ID", DEC) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, message_id, "Message ID", MSG_ID)

#define SMS_MEMORY_COMMON_SB_HDR \
    REFERENCE(8, BE, SubBlockID, "Sub Block ID", SB_ID) \
    REFERENCE(8, BE, SubBlockLength, "Sub Block Length", SB_LENGTH)

#define SMS_MEMORY_COMMON_SB_HDR_LONG \
    REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID) \
    FILLER(FILLER_FIXED, 8) \
    REFERENCE(16, BE, sub_block_length, "Sub Block Length", SB_LENGTH)


#ifndef SMS_MEMORY_VERSION
#define SMS_MEMORY_VERSION
#define SMS_MEMORY_VERSION_Z      0
#define SMS_MEMORY_VERSION_Y      34
#endif

/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                 "R&D Oulu")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                      "MAUI")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,                "Mika Rekkila")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,           "CONFIDENTIALITY")

/* Don't use this for ISI header generation */
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                   "sms_memory_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16,                "")

PROPERTY(PROPERTY_ISIHDR_GENERATE_ALL_STRUCTURE_ELEMENTS)
PROPERTY(PROPERTY_ISIHDR_GENERATE_BOOLS)


RES_BEGIN(RESOURCE_ISI, PN_SMS_MEMORY, SMS_MEMORY, "SMS Memory Server", 
    RES_VERSION_STRING(SMS_MEMORY_VERSION_Z, 
                       SMS_MEMORY_VERSION_Y), TRUE)


    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    COMMENT(COMMENT_TEXT, "First version of the file");
    ISI_VERSION_HISTORY("000.034")


    /* --------------------------------------------------------------------- */
    /* Constants */
    /* --------------------------------------------------------------------- */

    CONSTANT(SMS_MEMORY_BROWSE_ITEM_MAX_COUNT, 150)


    /* --------------------------------------------------------------------- */
    /* Symbols */
    /* --------------------------------------------------------------------- */

    CONST_TBL_BEGIN(SMS_MESSAGE_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_MEMORY_MESSAGE_NOT_PRESENT,     0x00, "")
        CONST_TBL_ENTRY(SMS_MEMORY_MT_READ,                 0x01, "")
        CONST_TBL_ENTRY(SMS_MEMORY_MO_DELIVERED,            0x02, "")
        CONST_TBL_ENTRY(SMS_MEMORY_MT_NOT_READ,             0x03, "")
        CONST_TBL_ENTRY(SMS_MEMORY_MO_SENT,                 0x05, "")
        CONST_TBL_ENTRY(SMS_MEMORY_MO_NOT_SENT,             0x07, "")
    CONST_TBL_END


    CONST_TBL_BEGIN(SMS_MESSAGE_LOCATION_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_MEMORY_LOCATION_NOT_USED,       0x00, "")
        CONST_TBL_ENTRY(SMS_MEMORY_LOCATION_MT_NOT_READ,    0x01, "")
        CONST_TBL_ENTRY(SMS_MEMORY_LOCATION_MT_READ,        0x02, "")
        CONST_TBL_ENTRY(SMS_MEMORY_LOCATION_MT,             0x03, "")
        CONST_TBL_ENTRY(SMS_MEMORY_LOCATION_MO_NOT_SENT,    0x04, "")
        CONST_TBL_ENTRY(SMS_MEMORY_LOCATION_MO_SENT,        0x08, "")
        CONST_TBL_ENTRY(SMS_MEMORY_LOCATION_MO,             0x0C, "")
        CONST_TBL_ENTRY(SMS_MEMORY_LOCATION_USED,           0x0F, "")
    CONST_TBL_END


    CONST_TBL_BEGIN(SMS_MEMORY_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_MEMORY_TYPE_DEFAULT,            0x00, "")
        CONST_TBL_ENTRY(SMS_MEMORY_TYPE_SIM,                0x01, "")
        CONST_TBL_ENTRY(SMS_MEMORY_TYPE_ME,                 0x02, "")
    CONST_TBL_END


    CONST_TBL_BEGIN(SMS_MESSAGE_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_MESSAGE_GMS_TYPE,               0x80, "")
        CONST_TBL_ENTRY(SMS_MESSAGE_RINGINGTONE_TYPE,       0x81, "")
        CONST_TBL_ENTRY(SMS_MESSAGE_BUSINESSCARD_TYPE,      0x82, "")
        CONST_TBL_ENTRY(SMS_MESSAGE_CLASS0_TYPE,            0x83, "")
    CONST_TBL_END


    CONST_TBL_BEGIN(SMS_MEMORY_FOLDER, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_UNSPECIFIED,          SMS_MEMORY_FOLDER_UNSPECIFIED, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_NONE,                 0x01, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_INBOX,                0x02, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_OUTBOX,               0x03, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_ARCHIVE,              0x04, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_TEMPLATES,            0x05, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_FIRST_USER_DEFINED,   SMS_MEMORY_FOLDER_FIRST_USER_DEFINED, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_2ND_USER_DEFINED,     0x07, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_3RD_USER_DEFINED,     0x08, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_4TH_USER_DEFINED,     0x09, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_5TH_USER_DEFINED,     0x0A, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_6TH_USER_DEFINED,     0x0B, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_7TH_USER_DEFINED,     0x0C, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_8TH_USER_DEFINED,     0x0D, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_9TH_USER_DEFINED,     0x0E, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_10TH_USER_DEFINED,    0x0F, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_11TH_USER_DEFINED,    0x10, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_12TH_USER_DEFINED,    0x11, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_13TH_USER_DEFINED,    0x12, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_14TH_USER_DEFINED,    0x13, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_15TH_USER_DEFINED,    0x14, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_16TH_USER_DEFINED,    0x15, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_17TH_USER_DEFINED,    0x16, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_18TH_USER_DEFINED,    0x17, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_19TH_USER_DEFINED,    0x18, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_LAST_USER_DEFINED,    SMS_MEMORY_FOLDER_LAST_USER_DEFINED, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_NOT_SENT,             0x1A, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FOLDER_ANY,                  0xFF, "")
    CONST_TBL_END


    CONST_TBL_BEGIN(SMS_MEMORY_CAUSE, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_MEMORY_OK,                      0x00, "")
        CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE,          0x01, "")
        CONST_TBL_ENTRY(SMS_MEMORY_INVALID_LOCATION,        0x02, "")
        CONST_TBL_ENTRY(SMS_MEMORY_FULL,                    0x03, "")
        CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED,        0x04, "")
        CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER,       0x05, "")
        CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM,                  0x06, "")
        CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED,            0x07, "")
        CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED,            0x08, "")
        CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED,       0x09, "")
        CONST_TBL_ENTRY(SMS_MEMORY_EMPTY_LOCATION,          0x0A, "")
        CONST_TBL_ENTRY(SMS_MEMORY_OPER_REWRITE_FAIL,       0x0B, "")
        CONST_TBL_ENTRY(SMS_MEMORY_OPER_READ_FAIL,          0x0C, "")
        CONST_TBL_ENTRY(SMS_MEMORY_OPER_WRITE_FAIL,         0x0D, "")
        CONST_TBL_ENTRY(SMS_MEMORY_OPER_ERASE_FAIL,         0x0E, "")
        CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY,               0x0F, "")
    CONST_TBL_END


    CONST_TBL_BEGIN(SMS_MEMORY_CONFIGURATION, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_MEMORY_CONF_STATIC,             0x00, "")
        CONST_TBL_ENTRY(SMS_MEMORY_CONF_DYNAMIC,            0x01, "")
    CONST_TBL_END


    CONST_TBL_BEGIN(SMS_MESSAGE_NAME_INDICATOR, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_MESSAGE_NAME_NOT_AVAIL,         0x01, "")
        CONST_TBL_ENTRY(SMS_MESSAGE_NAME_GIVEN,             0x02, "")
        CONST_TBL_ENTRY(SMS_MESSAGE_NAME_USER_DATA,         0x03, "")
        CONST_TBL_ENTRY(SMS_MESSAGE_NAME_ADDRESS,           0x04, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_MEMORY_CONCATENATION_INDICATORS, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_UDHI_8BIT_REF_NUMBER,           0x00, "")
        CONST_TBL_ENTRY(SMS_UDHI_16BIT_REF_NUMBER,          0x08, "")
    CONST_TBL_END


    /* Sequences */

    SEQ_BEGIN(SMS_MEMORY_BYTE, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, byte_value, "Byte", HEX)
    SEQ_END

    SEQ_BEGIN(SMS_MEMORY_WORD, DONT_CREATE_STRUCT, "", "")
        VALUE(16, BE, word_value, "Word", DEC)
    SEQ_END


    /* --------------------------------------------------------------------- */
    /* Symbols from sms_isi_m.h */
    /* --------------------------------------------------------------------- */

#if (defined AUTOGEN_ENVIRONMENT_LOCAL || IPF_US_TDMA_RAT == ON)

    BIT_TBL_BEGIN(SMS_TDMA_ENCODING_IDENTIFIER, 8, BE, "", "")
        BIT_TBL_ENTRY("XXX11111", SMS_TDMA_ENC_IE,              "")
        BIT_TBL_ENTRY("XXX00001", SMS_TDMA_ENC_IRA,             "")
        BIT_TBL_ENTRY("XXX00010", SMS_TDMA_ENC_USER_SPECIFIC,   "")
        BIT_TBL_ENTRY("XXX00011", SMS_TDMA_ENC_LATIN,           "")
        BIT_TBL_ENTRY("XXX00100", SMS_TDMA_ENC_BMP,             "")
        BIT_TBL_ENTRY("XXX00101", SMS_TDMA_ENC_HEBREW,          "")
        BIT_TBL_ENTRY("111XXXXX", SMS_TDMA_USER_DATA_TYPE_IE,   "")
        BIT_TBL_ENTRY("000XXXXX", SMS_TDMA_USER_DATA_NORMAL,    "")
        BIT_TBL_ENTRY("001XXXXX", SMS_TDMA_USER_DATA_EMAIL,     "")
    BIT_TBL_END

    BIT_TBL_BEGIN(SMS_TDMA_PRESENTATION_INDICATOR, 8, BE, "", "")
        BIT_TBL_ENTRY("XXXX1111", SMS_TDMA_SCREENING_IE,            "")
        BIT_TBL_ENTRY("XXXX0000", SMS_TDMA_NOT_SCREENED,            "")
        BIT_TBL_ENTRY("XXXX0001", SMS_TDMA_SCREENED_PASSED,         "")
        BIT_TBL_ENTRY("XXXX0010", SMS_TDMA_SCREENED_FAILED,         "")
        BIT_TBL_ENTRY("XXXX0011", SMS_TDMA_NETWORK_PROVIDED,        "")
        BIT_TBL_ENTRY("1111XXXX", SMS_TDMA_PRESENTATION_IE,         "")
        BIT_TBL_ENTRY("0000XXXX", SMS_TDMA_PRESENTATION_ALLOWD,     "")
        BIT_TBL_ENTRY("0001XXXX", SMS_TDMA_PRESENTATION_RESTR,      "")
        BIT_TBL_ENTRY("0010XXXX", SMS_TDMA_NUMBER_NOT_AVAILABLE,    "")
    BIT_TBL_END

    BIT_TBL_BEGIN(SMS_TDMA_ACKNOWLEDGEMENT_REQUEST, 8, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXX1", SMS_TDMA_DEL_ACK_REQUESTED, "")
        BIT_TBL_ENTRY("XXXXXX1X", SMS_TDMA_MAN_ACK_REQUESTED, "")
    BIT_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_OPTIONAL_DATA_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_ORIG_ADDRESS,                  0x00, "")
        CONST_TBL_ENTRY(SMS_TDMA_DEST_ADDRESS,                  0x01, "")
        CONST_TBL_ENTRY(SMS_TDMA_CALLBACK,                      0x02, "")
        CONST_TBL_ENTRY(SMS_TDMA_MC_TIMESTAMP,                  0x03, "")
        CONST_TBL_ENTRY(SMS_TDMA_VALIDITY_PERIOD,               0x04, "")
        CONST_TBL_ENTRY(SMS_TDMA_DELIVERY_TIME,                 0x05, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_LANGUAGE_IDENTIFIER, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_LANGUAGE_NOT_DEFINED,          0x00, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_NUMBERING_PLAN_INDICATOR, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_NP_UNKNOWN,                    0x00, "")
        CONST_TBL_ENTRY(SMS_TDMA_NP_INTERNET_ASCII,             0x0E, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_TYPE_OF_NUMBER_INDICATOR, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_TN_UNKNOWN,                    0x00, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_TIME_ZONE_OFFSET_DIRECTION, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_TIME_ZONE_SUBTRACT,            0x00, "")
        CONST_TBL_ENTRY(SMS_TDMA_TIME_ZONE_ADD,                 0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_DAYLIGHT_SAVING, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_STANDARD_TIME,                 0x00, "")
        CONST_TBL_ENTRY(SMS_TDMA_DAYLIGHT_SAVING_TIME,          0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_PITCH_INDICATOR, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_PITCH_MEDIUM,                  0x00, "")
        CONST_TBL_ENTRY(SMS_TDMA_PITCH_HIGH,                    0x01, "")
        CONST_TBL_ENTRY(SMS_TDMA_PITCH_LOW,                     0x02, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_CADENCE_INDICATOR, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_NO_TONE,                   0x00, "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_LONG,                      0x01, "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_SHORT,                     0x02, "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_SHORT_LONG,                0x03, "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_SHORT_2,                   0x04, "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_SHORT_LONG_2,              0x05, "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_SHORT_4,                   0x06, "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_PBX_LONG,                  0x07, "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_PBX_SHORT,                 0x08, "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_PBX_SHORT_LONG,            0x09, "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_PBX_SHORT_LONG_2,          0x0A, "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_PBX_SHORT_4,               0x0B, "")
        CONST_TBL_ENTRY(SMS_TDMA_CAD_PIP_4,                     0x0C, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_PRIVACY_INDICATOR, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_PRIVACY_NOT_RESTR,             0x00, "")
        CONST_TBL_ENTRY(SMS_TDMA_PRIVACY_RESTRICTED,            0x01, "")
        CONST_TBL_ENTRY(SMS_TDMA_PRIVACY_CONFIDENTIAL,          0x02, "")
        CONST_TBL_ENTRY(SMS_TDMA_PRIVACY_SECRET,                0x03, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_URGENCY_INDICATOR, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_URGENCY_BULK,                  0x00, "")
        CONST_TBL_ENTRY(SMS_TDMA_URGENCY_NORMAL,                0x01, "")
        CONST_TBL_ENTRY(SMS_TDMA_URGENCY_URGENT,                0x02, "")
        CONST_TBL_ENTRY(SMS_TDMA_URGENCY_EMERGENCY,             0x03, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_MESSAGE_UPDATING, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_MESSAGE_UPDATE,                0x00, "")
        CONST_TBL_ENTRY(SMS_TDMA_MESSAGE_NEW,                   0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_VALIDITY_INDICATOR, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_VALIDITY_INDEFINITE,           0x00, "")
        CONST_TBL_ENTRY(SMS_TDMA_VALIDITY_POWER_DOWN,           0x01, "")
        CONST_TBL_ENTRY(SMS_TDMA_VALIDITY_SID_AREA,             0x02, "")
        CONST_TBL_ENTRY(SMS_TDMA_VALIDITY_DISPLAY_ONLY,         0x03, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_TDMA_DISPLAY_TIME_INDICATOR, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_TDMA_DISPLAY_TIME_TEMP,             0x00, "")
        CONST_TBL_ENTRY(SMS_TDMA_DISPLAY_TIME_DEFAULT,          0x01, "")
        CONST_TBL_ENTRY(SMS_TDMA_DISPLAY_TIME_INVOKE,           0x02, "")
    CONST_TBL_END

#endif /* defined AUTOGEN_ENVIRONMENT_LOCAL || IPF_US_TDMA_RAT == ON */

    CONST_TBL_BEGIN(SMS_ADDRESS_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_UNICODE_ADDRESS,                    0x00, "")
        CONST_TBL_ENTRY(SMS_GSM_0340_ADDRESS,                   0x01, "")
        CONST_TBL_ENTRY(SMS_GSM_0411_ADDRESS,                   0x02, "")
        CONST_TBL_ENTRY(SMS_TDMA_IRA_ADDRESS,                   0x03, "")
        CONST_TBL_ENTRY(SMS_TDMA_TBCD_ADDRESS,                  0x04, "")
        CONST_TBL_ENTRY(SMS_TDMA_LATIN_ADDRESS,                 0x05, "")
        CONST_TBL_ENTRY(SMS_TDMA_BMP_ADDRESS,                   0x06, "")
        CONST_TBL_ENTRY(SMS_TDMA_HEBREW_ADDRESS,                0x07, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(SMS_ALPHA_TAG_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SMS_UNICODE_ALPHA_TAG,                  0x00, "")
        CONST_TBL_ENTRY(SMS_TDMA_IRA_ALPHA_TAG,                 0x01, "")
        CONST_TBL_ENTRY(SMS_TDMA_LATIN_ALPHA_TAG,               0x02, "")
        CONST_TBL_ENTRY(SMS_TDMA_BMP_ALPHA_TAG,                 0x03, "")
        CONST_TBL_ENTRY(SMS_TDMA_HEBREW_ALPHA_TAG,              0x04, "")
    CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* Sub blocks from sms_isi_m.h */
    /* --------------------------------------------------------------------- */

    /* SMS_ADDRESS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_ADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(address_type, "Address type", SMS_ADDRESS_TYPE)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, address_data_length, "Address data Length", L)
        SEQ_OF_REF(address_data, "Address data", SMS_MEMORY_BYTE, L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* SMS_COMMON_DATA */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_COMMON_DATA, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, data_length, "Data Length", L)
        FILLER_EX(pad, 8, 1)
        SEQ_OF_REF(data_bytes, "Data bytes", SMS_MEMORY_BYTE, L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


        /* SMS_GSM_COMMON_DATA */

        PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_GSM_COMMON_DATA, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, data_length, "Data length", L)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, character_amount, "Character amount", DEC)
        SEQ_OF_REF(data_bytes, "Data bytes", SMS_MEMORY_BYTE, L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* SMS_GSM_DELIVER */

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 252)
    SB_BEGIN(SMS_GSM_DELIVER, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, message_parameters, "Message parameters", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, protocol_id, "Protocol id", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, data_coding_scheme, "Data coding scheme", DEC)
        SEQ_OF(sc_time_stamp, "SC time stamp", SMS_MEMORY_BYTE, SMS_SC_TIME_STAMP_SIZE)
        FILLER(FILLER_FIXED, 24)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_block_count, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_ADDRESS)
            SB_LST_ENTRY(SMS_COMMON_DATA)
            SB_LST_ENTRY(SMS_GSM_COMMON_DATA)
        SB_LST_REF_END
    SB_END


    /* SMS_GSM_PARAM_INDICATOR */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_GSM_PARAM_INDICATOR, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_GSM_PARAM_INDICATOR_MAX_LEN)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, parameter_indicator_length, "Parameter indicator length", L)
        SEQ_OF_REF(parameter_indicators, "Parameter indicators", SMS_MEMORY_BYTE, L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* SMS_GSM_OPTIONAL_FIELDS */

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 252)
    SB_BEGIN(SMS_GSM_OPTIONAL_FIELDS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, protocol_id, "Protocol id", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, data_coding_scheme, "Data coding scheme", DEC)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks",
            REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_COMMON_DATA)
            SB_LST_ENTRY(SMS_GSM_COMMON_DATA)
        SB_LST_REF_END
    SB_END


    /* SMS_GSM_STATUS_REPORT */

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 252)
    SB_BEGIN(SMS_GSM_STATUS_REPORT, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, message_parameters, "Message parameters", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, reference_for_message, "Reference for message", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, status, "Status", DEC)
        SEQ_OF(sc_time_stamp, "SC time stamp", SMS_MEMORY_BYTE, SMS_SC_TIME_STAMP_SIZE)
        SEQ_OF(discharge_time, "Discharge time", SMS_MEMORY_BYTE, SMS_DISCHARGE_TIME_SIZE)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, sub_block_count, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N,
            ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_ADDRESS)
            SB_LST_ENTRY(SMS_GSM_PARAM_INDICATOR)
            SB_LST_ENTRY(SMS_GSM_OPTIONAL_FIELDS)
        SB_LST_REF_END
    SB_END


    /* SMS_GSM_VALIDITY_PERIOD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_GSM_VALIDITY_PERIOD, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, validity_period_length, "Validity period length", L)
        SEQ_OF_REF(validity_period_data, "Validity period data", SMS_MEMORY_BYTE, L, ISIHDR_MARKER_ANYSIZE_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* SMS_TIME_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_TIME_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, year, "Year", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, month, "month", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, day_of_month, "Day of Month", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, hour, "Hour", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, minute, "Minute", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, second, "Second", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, time_zone, "Time zone", DEC)
        FILLER(FILLER_FIXED, 16)
    SB_END


    /* SMS_GSM_SUBMIT */

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 252)
    SB_BEGIN(SMS_GSM_SUBMIT, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        COMMENT(COMMENT_TEXT, "+ length of subsequent blocks")
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, message_parameters, "Message parameters", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, message_reference, "Message reference", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, protocol_id, "Protocol id", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, data_coding_scheme, "Data coding scheme", DEC)
        FILLER(FILLER_FIXED, 8)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_block_count, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N,
            ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_ADDRESS)
            SB_LST_ENTRY(SMS_COMMON_DATA)
            SB_LST_ENTRY(SMS_GSM_COMMON_DATA)
            SB_LST_ENTRY(SMS_GSM_VALIDITY_PERIOD)
            SB_LST_ENTRY(SMS_TIME_INFO)
        SB_LST_REF_END
    SB_END


    /* SMS_GSM_COMMAND */

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 252)
    SB_BEGIN(SMS_GSM_COMMAND, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, message_parameters, "Message parameters", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, message_reference, "Message reference", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, protocol_id, "Protocol id", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, command_type, "Command type", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, message_number, "Message number", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_block_count, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_ADDRESS)
            SB_LST_ENTRY(SMS_COMMON_DATA)
            SB_LST_ENTRY(SMS_GSM_COMMON_DATA)
        SB_LST_REF_END
    SB_END


    /* SMS_GSM_MT_UNDEFINED */

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 252)
    SB_BEGIN(SMS_GSM_MT_UNDEFINED, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, message_parameters, "Message parameters", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_block_count, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_ADDRESS)
            SB_LST_ENTRY(SMS_COMMON_DATA)
            SB_LST_ENTRY(SMS_GSM_COMMON_DATA)
        SB_LST_REF_END
    SB_END


    /* SMS_GSM_MO_UNDEFINED */

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 252)
    SB_BEGIN(SMS_GSM_MO_UNDEFINED, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, message_parameters, "Message parameters", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, message_reference, "Message reference", DEC)
        FILLER(FILLER_FIXED, 24)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_block_count, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_ADDRESS)
            SB_LST_ENTRY(SMS_COMMON_DATA)
            SB_LST_ENTRY(SMS_GSM_COMMON_DATA)
        SB_LST_REF_END
    SB_END


    /* SMS_ALPHA_TAG */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_ALPHA_TAG, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, alpha_tag_length, "Data Length", L)
        VALUE_CONST(alpha_tag_type, "Alpha tag type", SMS_ALPHA_TAG_TYPE)
        SEQ_OF_REF(alpha_tag_data, "Alpha tag data", SMS_MEMORY_BYTE, L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


#if (defined AUTOGEN_ENVIRONMENT_LOCAL || IPF_US_TDMA_RAT == ON)

    /* SMS_TDMA_USER_DATA_UNIT */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_TDMA_USER_DATA_UNIT, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        FILLER(FILLER_FIXED, 8)
        REFERENCE(16, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_encoding_identifier, "SMS TDMA Encoding Identifier", SMS_TDMA_ENCODING_IDENTIFIER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_language_identifier, "SMS TDMA Language Identifier", SMS_TDMA_LANGUAGE_IDENTIFIER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 65524)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(16, BE, user_data_length, "User data length", L)
        SEQ_OF_REF(user_data, "User Data", SMS_MEMORY_BYTE, L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* SMS_TDMA_ADDRESS_INFO */

    DER_CONST_TBL_BEGIN(SMS_TDMA_ADDRESS_TYPE, SMS_TDMA_OPTIONAL_DATA_TYPE, "", "")
        DER_CONST_TBL_ENTRY(SMS_TDMA_ORIG_ADDRESS)
        DER_CONST_TBL_ENTRY(SMS_TDMA_DEST_ADDRESS)
        DER_CONST_TBL_ENTRY(SMS_TDMA_CALLBACK)
    DER_CONST_TBL_END

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 252)
    SB_BEGIN(SMS_TDMA_ADDRESS_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_optional_data_type, "SMS TDMA Optional data type", SMS_TDMA_ADDRESS_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_presentation_indicator, "SMS TDMA Presentation Indicator", SMS_TDMA_PRESENTATION_INDICATOR)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_numbering_plan, "SMS TDMA Numbering Plan", SMS_TDMA_NUMBERING_PLAN_INDICATOR)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_type_of_number, "SMS TDMA Type of Number", SMS_TDMA_TYPE_OF_NUMBER_INDICATOR)
        FILLER(FILLER_FIXED, 8)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_block_count, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_ADDRESS)
        SB_LST_REF_END
    SB_END


    /* SMS_TDMA_TIME_ABS */

    DER_CONST_TBL_BEGIN(SMS_TDMA_TIME_ABS_TYPE, SMS_TDMA_OPTIONAL_DATA_TYPE, "", "")
        DER_CONST_TBL_ENTRY(SMS_TDMA_VALIDITY_PERIOD)
        DER_CONST_TBL_ENTRY(SMS_TDMA_DELIVERY_TIME)
        DER_CONST_TBL_ENTRY(SMS_TDMA_MC_TIMESTAMP)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_TDMA_TIME_ABS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_optional_data_type, "SMS TDMA Optional data type", SMS_TDMA_TIME_ABS_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_time_zone_offset_direction, "SMS TDMA Time zone offset direction", SMS_TDMA_TIME_ZONE_OFFSET_DIRECTION)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(32, BE, time, "Time", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, time_zone_offset, "Time zone offset", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_daylight_saving, "SMS TDMA Daylight Saving", SMS_TDMA_DAYLIGHT_SAVING)
        FILLER(FILLER_FIXED, 8)
    SB_END


    /* SMS_TDMA_CALLBACK_INFO */

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 252)
    SB_BEGIN(SMS_TDMA_CALLBACK_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        FILLER(FILLER_FIXED, 8)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_block_count, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_TDMA_ADDRESS_INFO)
            SB_LST_ENTRY(SMS_ALPHA_TAG)
        SB_LST_REF_END
    SB_END


    /* SMS_TDMA_SIGNAL_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_TDMA_SIGNAL_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_pitch_indicator, "SMS TDMA Pitch Indicator", SMS_TDMA_PITCH_INDICATOR)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_cadence_indicator, "SMS TDMA Cadence Indicator", SMS_TDMA_CADENCE_INDICATOR)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 15)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, duration, "Duration", DEC)
        FILLER(FILLER_FIXED, 24)
    SB_END


    /* SMS_TDMA_DELIVER */

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 65532)
    SB_BEGIN(SMS_TDMA_DELIVER, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        FILLER(FILLER_FIXED, 8)
        REFERENCE(16, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, message_reference, "Message reference", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_privacy_indicator, "SMS TDMA Privacy Indicator", SMS_TDMA_PRIVACY_INDICATOR)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_urgency_indicator, "SMS TDMA Urgency Indicator", SMS_TDMA_URGENCY_INDICATOR)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(ack_request, "SMS TDMA acknowledge Request", SMS_TDMA_ACKNOWLEDGEMENT_REQUEST)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, ack_time, "Acknowledgement time", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(message_updating, "Message Updating", SMS_TDMA_MESSAGE_UPDATING)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_validity_indicator, "SMS TDMA Validity Indicator", SMS_TDMA_VALIDITY_INDICATOR)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_display_time_indicator, "SMS TDMA Display time Indicator", SMS_TDMA_DISPLAY_TIME_INDICATOR)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, sms_tdma_callback_count, "SMS TDMA Callback Info count", DEC)
        FILLER(FILLER_FIXED, 8)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_block_count, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_TDMA_USER_DATA_UNIT)
            SB_LST_ENTRY(SMS_TDMA_ADDRESS_INFO)
            SB_LST_ENTRY(SMS_TDMA_TIME_ABS)
            SB_LST_ENTRY(SMS_TDMA_CALLBACK_INFO)
            SB_LST_ENTRY(SMS_TDMA_SIGNAL_INFO)
        SB_LST_REF_END
    SB_END


    /* SMS_TDMA_TIME_REL */

    DER_CONST_TBL_BEGIN(SMS_TDMA_TIME_REL_TYPE, SMS_TDMA_OPTIONAL_DATA_TYPE, "", "")
        DER_CONST_TBL_ENTRY(SMS_TDMA_VALIDITY_PERIOD)
        DER_CONST_TBL_ENTRY(SMS_TDMA_DELIVERY_TIME)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_TDMA_TIME_REL, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_optional_data_type, "SMS TDMA Optional data type", SMS_TDMA_TIME_REL_TYPE)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 255)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, time, "Time", DEC)
    SB_END


    /* SMS_TDMA_SUBMIT */

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 65532)
    SB_BEGIN(SMS_TDMA_SUBMIT, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        FILLER_EX(pad, 8, 1)
        REFERENCE(16, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, message_reference, "Message reference", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_privacy_indicator, "SMS TDMA Privacy Indicator", SMS_TDMA_PRIVACY_INDICATOR)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sms_tdma_urgency_indicator, "SMS TDMA Urgency Indicator", SMS_TDMA_URGENCY_INDICATOR)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(ack_request, "SMS TDMA acknowledge Request", SMS_TDMA_ACKNOWLEDGEMENT_REQUEST)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(message_updating, "Message Updating", SMS_TDMA_MESSAGE_UPDATING)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, sms_tdma_callback_count, "SMS TDMA Callback Info count", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_block_count, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N,
            ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_TDMA_USER_DATA_UNIT)
            SB_LST_ENTRY(SMS_TDMA_ADDRESS_INFO)
            SB_LST_ENTRY(SMS_TDMA_CALLBACK_INFO)
            SB_LST_ENTRY(SMS_TDMA_TIME_REL)
            SB_LST_ENTRY(SMS_TDMA_TIME_ABS)
        SB_LST_REF_END
    SB_END


    /* SMS_TDMA_DELIVERY_ACK */

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 65532)
    SB_BEGIN(SMS_TDMA_DELIVERY_ACK, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        FILLER(FILLER_FIXED, 8)
        REFERENCE(16, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, message_reference, "Message reference", DEC)
        FILLER(FILLER_FIXED, 8)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_block_count, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_TDMA_USER_DATA_UNIT)
            SB_LST_ENTRY(SMS_TDMA_ADDRESS_INFO)
        SB_LST_REF_END
    SB_END


    /* SMS_TDMA_MANUAL_ACK */

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 65532)
    SB_BEGIN(SMS_TDMA_MANUAL_ACK, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        FILLER_EX(pad, 8, 1)
        REFERENCE(16, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, message_reference, "Message reference", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 15)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, user_response_code, "User response code", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_block_count, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_TDMA_USER_DATA_UNIT)
            SB_LST_ENTRY(SMS_TDMA_ADDRESS_INFO)
        SB_LST_REF_END
    SB_END

#endif /* defined AUTOGEN_ENVIRONMENT_LOCAL || IPF_US_TDMA_RAT == ON */


    /* --------------------------------------------------------------------- */
    /* Sub blocks */
    /* --------------------------------------------------------------------- */

    /* SMS_MEMORY_HEADER */

    DER_CONST_TBL_BEGIN(SMS_MEMORY_HEADER_MEM_TYPE, SMS_MEMORY_TYPE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_ME)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_Header")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_MEMORY_HEADER, "", "")
        SMS_MEMORY_COMMON_SB_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_HEADER_MEM_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MessageType, "Message type", SMS_MESSAGE_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MessageStatus, "Message status", SMS_MESSAGE_STATUS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, MessageReference, "Message reference", HEX)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, ProtocolId, "Protocol id", HEX)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        STRING(STRING_BCD, NSW, SCAddress, "Service Center address", SMS_MEMORY_ADDRESS_MAX_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        STRING(STRING_BCD, NSW, Address, "Address", SMS_MEMORY_ADDRESS_MAX_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        STRING(STRING_BCD, NSW, SCTimeStamp, "SC time stamp", SMS_MEMORY_TIME_STAMP_MAX_LENGTH)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MessageNameInd, "Message name indicator", SMS_MESSAGE_NAME_INDICATOR)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_NAME_MAX_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, MessageNameLength, "Message name length", N)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, MessageName, "Message name", N, ISIHDR_RESERVE_SPACE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, sequence_count, "Sequence Count", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, sequence_id, "Sequence ID", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, ref_number, "Reference Number", DEC)
    SB_END


    /* SMS_MEMORY_GSM_HEADER */

    DER_CONST_TBL_BEGIN(SMS_MEMORY_GSM_HEADER_MEM_TYPE, SMS_MEMORY_TYPE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_ME)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_GSM_Header")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_MEMORY_GSM_HEADER, "", "")
        SMS_MEMORY_COMMON_SB_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_GSM_HEADER_MEM_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MessageType, "Message type", SMS_MESSAGE_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MessageStatus, "Message status", SMS_MESSAGE_STATUS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, MessageReference, "Message reference", HEX)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, ProtocolId, "Protocol id", HEX)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        STRING(STRING_BCD, NSW, SCAddress, "Service Center address", SMS_MEMORY_ADDRESS_MAX_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        STRING(STRING_BCD, NSW, Address, "Address", SMS_MEMORY_ADDRESS_MAX_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        STRING(STRING_BCD, NSW, SCTimeStamp, "SC time stamp", SMS_MEMORY_TIME_STAMP_MAX_LENGTH)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MessageNameInd, "Message name indicator", SMS_MESSAGE_NAME_INDICATOR)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_NAME_MAX_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, MessageNameLength, "Message name length", N)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, MessageName, "Message name", N, ISIHDR_RESERVE_SPACE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, sequence_count, "Sequence Count", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, sequence_id, "Sequence ID", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, ref_number, "Reference Number", DEC)
    SB_END


    /* SMS_MEMORY_FOLDER_NAME */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_FolderName")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_MEMORY_FOLDER_NAME, "", "")
        SMS_MEMORY_COMMON_SB_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_FOLDER_NAME_MAX_LENGTH+1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, FolderNameLength, "Folder name length", N)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, FolderName, "Folder name", N, ISIHDR_RESERVE_SPACE)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* SMS_MEMORY_STATUS */

    DER_CONST_TBL_BEGIN(SMS_MEMORY_STATUS_MEM_TYPE, SMS_MEMORY_TYPE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_ME)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_Status")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_MEMORY_STATUS, "", "")
        SMS_MEMORY_COMMON_SB_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_STATUS_MEM_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryConfiguration, "Memory configuration", SMS_MEMORY_CONFIGURATION)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Capacity, "Capacity of messages", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, MessageCount, "Total number of messages", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, UnreadMessageCount, "Total number of unread messages", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryFull, "Message memory full", TRUE_FALSE)
        FILLER_EX(PaddingByte1, 8, 1)
    SB_END


    /* SMS_MEMORY_PICTURE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_Picture")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SMS_SUB_PICTURE_LEN    12")
    SB_BEGIN(SMS_MEMORY_PICTURE, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        FILLER_EX(PaddingByte1, 8, 1)
        REFERENCE(16, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, deliver, "Deliver", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, template_nbr, "Template number", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, info_field, "info_field", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, bitmap_depth, "bitmap_depth", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, bitmap_width, "bitmap_width", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, bitmap_height, "bitmap_height", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(16, BE, bitmap_data_length, "bitmap_data_length", N)
        SEQ_OF_REF(bitmap_data, "bitmap_data", SMS_MEMORY_BYTE, N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    uint8   pad2[1];")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* SMS_MEMORY_TEMPLATE_STATUS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_TemplateStatus")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_MEMORY_TEMPLATE_STATUS, "", "")
        COMMON_SB
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Capacity, "Capacity", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, MessageCount, "Message Count", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, DefaultMessageCount, "Default Message Count", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryFull, "Memory Full", TRUE_FALSE)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
    SB_END


    /* SMS_MEMORY_PICTURE_TEMPLATE_STATUS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_PictureTemplateStatus")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_MEMORY_PICTURE_TEMPLATE_STATUS, "", "")
        COMMON_SB
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Capacity, "Capacity", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, MessageCount, "Message Count", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, DefaultMessageCount, "Default Message Count", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryFull, "Memory Full", TRUE_FALSE)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
    SB_END


    /* SMS_MEMORY_OVERWRITE_STATUS */

    DER_CONST_TBL_BEGIN(SMS_MEMORY_OVERWRITE_STATUS_TYPE, SMS_MEMORY_TYPE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_ME)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_OverwriteStatus")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_MEMORY_OVERWRITE_STATUS, "", "")
        COMMON_SB
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, CapacityInInbox, "Capacity In Inbox", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, CapacityInOutbox, "Capacity In Outbox", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory Type", SMS_MEMORY_OVERWRITE_STATUS_TYPE)
        FILLER_EX(PaddingByte1, 8, 1)
    SB_END


    /* SMS_MEMORY_FOLDER_STATUS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_FolderStatus")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_MEMORY_FOLDER_STATUS, "", "")
        COMMON_SB
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, FolderCount, "Folder Count", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, MaxFolderCount, "Max Folder Count", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_FOLDER_NAME_MAX_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, FolderNameLength, "Folder Name Length", DEC)
    SB_END


    /* SMS_MEMORY_MSG_NAME_STATUS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_MsgNameStatus")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SMS_MEMORY_MSG_NAME_STATUS, "", "")
        COMMON_SB
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_NAME_MAX_LENGTH)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, MessageNameLength, "Message Name Length", DEC)
    SB_END



    /* SMS_MEMORY_GMS */
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_GMS")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SMS_SUB_GMS_LEN    4")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 65532)
    SB_BEGIN(SMS_MEMORY_GMS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_block_count, "Number of subsequent blocks", N_SB)
        REFERENCE(16, BE, sub_block_length, "Sub Block Length", SB_LENGTH)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SMS_GSM_DELIVER)
            SB_LST_ENTRY(SMS_GSM_SUBMIT)
#if (defined AUTOGEN_ENVIRONMENT_LOCAL || IPF_US_TDMA_RAT == ON)
            SB_LST_ENTRY(SMS_TDMA_DELIVER)
            SB_LST_ENTRY(SMS_TDMA_SUBMIT)
#endif /* defined AUTOGEN_ENVIRONMENT_LOCAL || IPF_US_TDMA_RAT == ON */
            SB_LST_ENTRY(SMS_MEMORY_PICTURE)
        SB_LST_END
    SB_END



    /* --------------------------------------------------------------------- */
    /* Messages */
    /* --------------------------------------------------------------------- */

    /* SMS_MEMORY_WRITE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_WriteReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_WRITE_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MessageStatus, "Message status", SMS_MESSAGE_STATUS) 
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, SubBlockCount, "Number of sub blocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SMS_GSM_DELIVER)
            SB_LST_ENTRY(SMS_GSM_STATUS_REPORT)
            SB_LST_ENTRY(SMS_GSM_SUBMIT)
            SB_LST_ENTRY(SMS_GSM_COMMAND)
            SB_LST_ENTRY(SMS_GSM_MT_UNDEFINED)
            SB_LST_ENTRY(SMS_GSM_MO_UNDEFINED)
#if (defined AUTOGEN_ENVIRONMENT_LOCAL || IPF_US_TDMA_RAT == ON)
            SB_LST_ENTRY(SMS_TDMA_DELIVER)
            SB_LST_ENTRY(SMS_TDMA_SUBMIT)
            SB_LST_ENTRY(SMS_TDMA_DELIVERY_ACK)
            SB_LST_ENTRY(SMS_TDMA_MANUAL_ACK)
#endif /* defined AUTOGEN_ENVIRONMENT_LOCAL || IPF_US_TDMA_RAT == ON */
            SB_LST_ENTRY(SMS_MEMORY_GMS)
        SB_LST_END
    MSG_END


    DER_CONST_TBL_BEGIN(SMS_MEMORY_WRITE_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_FULL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SMS_MEMORY_WRITE_MEM_TYPE, SMS_MEMORY_TYPE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_ME)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_WriteResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_WRITE_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_WRITE_CAUSE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_WRITE_MEM_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MessageStatus, "Message status", SMS_MESSAGE_STATUS) 
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, SubBlockCount, "Number of sub blocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SMS_MEMORY_STATUS)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(SMS_MEMORY_WRITE_REQ, SMS_MEMORY_WRITE_RESP)


    /* SMS_MEMORY_READ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ReadReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_READ_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, SMS_MEMORY_LOCATION_OF_FIRST_UNREAD_MSG)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(UpdateStatus, "Update Status", TRUE_FALSE)
        FILLER_EX(PaddingByte1, 8, 1)
    MSG_END


    DER_CONST_TBL_BEGIN(SMS_MEMORY_READ_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_EMPTY_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SMS_MEMORY_READ_MEM_TYPE, SMS_MEMORY_TYPE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_ME)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ReadResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_READ_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_READ_CAUSE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MessageStatus, "Message status", SMS_MESSAGE_STATUS) 
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_READ_MEM_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, SubBlockCount, "Number of sub blocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SMS_GSM_DELIVER)
            SB_LST_ENTRY(SMS_GSM_STATUS_REPORT)
            SB_LST_ENTRY(SMS_GSM_SUBMIT)
            SB_LST_ENTRY(SMS_GSM_COMMAND)
            SB_LST_ENTRY(SMS_GSM_MT_UNDEFINED)
            SB_LST_ENTRY(SMS_GSM_MO_UNDEFINED)
#if (defined AUTOGEN_ENVIRONMENT_LOCAL || IPF_US_TDMA_RAT == ON)
            SB_LST_ENTRY(SMS_TDMA_DELIVER)
            SB_LST_ENTRY(SMS_TDMA_SUBMIT)
            SB_LST_ENTRY(SMS_TDMA_DELIVERY_ACK)
            SB_LST_ENTRY(SMS_TDMA_MANUAL_ACK)
#endif /* defined AUTOGEN_ENVIRONMENT_LOCAL || IPF_US_TDMA_RAT == ON */
            SB_LST_ENTRY(SMS_MEMORY_GMS)
        SB_LST_END
    MSG_END

    MSG_PAIR(SMS_MEMORY_READ_REQ, SMS_MEMORY_READ_RESP)


    /* SNS_MEMORY_CONCAT_READ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ConcatReadReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_CONCAT_READ_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(UpdateStatus, "Update Status", TRUE_FALSE)
        FILLER_EX(PaddingByte1, 8, 1)
    MSG_END

    DER_CONST_TBL_BEGIN(SMS_MEMORY_CONCAT_READ_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_EMPTY_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ConcatReadResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_CONCAT_READ_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_CONCAT_READ_CAUSE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MessageStatus, "Memory Status", SMS_MESSAGE_STATUS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory Type", SMS_MEMORY_GSM_HEADER_MEM_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, SubBlockCount, "Number of sub blocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SMS_GSM_DELIVER)
            SB_LST_ENTRY(SMS_GSM_STATUS_REPORT)
            SB_LST_ENTRY(SMS_GSM_SUBMIT)
            SB_LST_ENTRY(SMS_GSM_COMMAND)
            SB_LST_ENTRY(SMS_GSM_MT_UNDEFINED)
            SB_LST_ENTRY(SMS_GSM_MO_UNDEFINED)
#if (defined AUTOGEN_ENVIRONMENT_LOCAL || IPF_US_TDMA_RAT == ON)
            SB_LST_ENTRY(SMS_TDMA_DELIVER)
            SB_LST_ENTRY(SMS_TDMA_SUBMIT)
            SB_LST_ENTRY(SMS_TDMA_DELIVERY_ACK)
            SB_LST_ENTRY(SMS_TDMA_MANUAL_ACK)
#endif /* defined AUTOGEN_ENVIRONMENT_LOCAL || IPF_US_TDMA_RAT == ON */
            SB_LST_ENTRY(SMS_MEMORY_GMS)
        SB_LST_END
    MSG_END

    MSG_PAIR(SMS_MEMORY_CONCAT_READ_REQ, SMS_MEMORY_CONCAT_READ_RESP)


    /* SMS_MEMORY_ERASE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_EraseReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_ERASE_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, SMS_MEMORY_ALL_LOCATIONS)
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(LocationStatus, "Message Location Status", SMS_MESSAGE_LOCATION_STATUS)
        FILLER_EX(PaddingByte1, 8, 1)
    MSG_END


    DER_CONST_TBL_BEGIN(SMS_MEMORY_ERASE_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_EMPTY_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_EraseResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_ERASE_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_ERASE_CAUSE)
        FILLER_EX(PaddingByte1, 8, 1)
    MSG_END

    MSG_PAIR(SMS_MEMORY_ERASE_REQ, SMS_MEMORY_ERASE_RESP)


    /* SMS_MEMORY_CONCAT_ERASE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ConcatEraseReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_CONCAT_ERASE_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory Type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, SMS_MEMORY_ALL_LOCATIONS)
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(LocationStatus, "Message Location Status", SMS_MESSAGE_LOCATION_STATUS)
        FILLER_EX(PaddingByte1, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ConcatEraseResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_CONCAT_ERASE_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_ERASE_CAUSE)
        FILLER_EX(PaddingByte1, 8, 1)
    MSG_END

    MSG_PAIR(SMS_MEMORY_CONCAT_ERASE_REQ, SMS_MEMORY_CONCAT_ERASE_RESP)


    /* SMS_MEMORY_ERASE_BY_TYPE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_EraseByTypeReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_ERASE_BY_TYPE_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MessageType, "Message type", SMS_MESSAGE_TYPE)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
    MSG_END


    DER_CONST_TBL_BEGIN(SMS_MEMORY_ERASE_BY_TYPE_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_EraseByTypeResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_ERASE_BY_TYPE_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_ERASE_BY_TYPE_CAUSE)
        FILLER_EX(PaddingByte1, 8, 1)
    MSG_END

    MSG_PAIR(SMS_MEMORY_ERASE_BY_TYPE_REQ, SMS_MEMORY_ERASE_BY_TYPE_RESP)


    /* SMS_MEMORY_STATUS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_StatusReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_STATUS_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
    MSG_END


    DER_CONST_TBL_BEGIN(SMS_MEMORY_STATUS_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_StatusResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_STATUS_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_STATUS_CAUSE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, SubBlockCount, "Number of sub blocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SMS_MEMORY_STATUS)
            SB_LST_ENTRY(SMS_MEMORY_TEMPLATE_STATUS)
            SB_LST_ENTRY(SMS_MEMORY_PICTURE_TEMPLATE_STATUS)
            SB_LST_ENTRY(SMS_MEMORY_OVERWRITE_STATUS)
            SB_LST_ENTRY(SMS_MEMORY_FOLDER_STATUS)
            SB_LST_ENTRY(SMS_MEMORY_MSG_NAME_STATUS)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(SMS_MEMORY_STATUS_REQ, SMS_MEMORY_STATUS_RESP)


    /* SMS_MEMORY_READY_IND */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ReadyInd")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_READY_IND, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
    MSG_END


    /* SMS_MEMORY_WARNING_LEVEL_IND */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_Indication")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_WARNING_LEVEL_IND, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
    MSG_END


    /* SMS_MEMORY_UPDATESTATUS_IND */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_UPDATESTATUS_IND, MESSAGE_IND, "", "")
        SMS_MEM_MSG_HDR
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
    MSG_END


    /* SMS_MEMORY_ERASED_IND */

    DER_CONST_TBL_BEGIN(SMS_MEMORY_ERASED_IND_MEM_TYPE, SMS_MEMORY_TYPE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_ME)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ErasedInd")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_ERASED_IND, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_ERASED_IND_MEM_TYPE)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
    MSG_END


    /* SMS_MEMORY_BROWSE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_BrowseReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_BROWSE_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(LocationStatus, "Message location status", SMS_MESSAGE_LOCATION_STATUS)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
    MSG_END


    DER_CONST_TBL_BEGIN(SMS_MEMORY_BROWSE_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    /* TODO: 2 Filler Bytes efter Location */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_BrowseResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_BROWSE_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_BROWSE_CAUSE)
        FILLER_EX(PaddingByte1, 8, 1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_BROWSE_ITEM_MAX_COUNT)
        REFERENCE(16, BE, Count, "Count of locations", N)
        SEQ_OF_REF(Location, "Locations", SMS_MEMORY_WORD, N, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    MSG_END

    MSG_PAIR(SMS_MEMORY_BROWSE_REQ, SMS_MEMORY_BROWSE_RESP)


    /* SMS_MEMORY_CONCAT_BROWSE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ConcatBrowseReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_CONCAT_BROWSE_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(LocationStatus, "Message Location Status", SMS_MESSAGE_LOCATION_STATUS)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
    MSG_END

    /* TODO: 2 Filler Bytes efter Location */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ConcatBrowseResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_CONCAT_BROWSE_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_BROWSE_CAUSE)
        FILLER_EX(PaddingByte1, 8, 1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_BROWSE_ITEM_MAX_COUNT)
        REFERENCE(16, BE, Count, "Count of locations", N)
        SEQ_OF_REF(Location, "Locations", SMS_MEMORY_WORD, N, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    MSG_END

    MSG_PAIR(SMS_MEMORY_CONCAT_BROWSE_REQ, SMS_MEMORY_CONCAT_BROWSE_RESP)


    /* SMS_MEMORY_HEADER_READ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_HeaderReadReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_HEADER_READ_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
    MSG_END


    DER_CONST_TBL_BEGIN(SMS_MEMORY_HEADER_READ_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_EMPTY_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_HeaderReadResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_HEADER_READ_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_HEADER_READ_CAUSE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, SubBlockCount, "Number of sub blocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SMS_MEMORY_GSM_HEADER)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(SMS_MEMORY_HEADER_READ_REQ, SMS_MEMORY_HEADER_READ_RESP)


    /* SMS_MEMORY_FOLDER_WRITE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_FolderWriteReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_FOLDER_WRITE_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, SubBlockCount, "Number of sub blocks", N_SB)
        FILLER_EX(PaddingByte1, 8, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SMS_MEMORY_FOLDER_NAME)
        SB_LST_REF_END
    MSG_END


    DER_CONST_TBL_BEGIN(SMS_MEMORY_FOLDER_WRITE_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_FULL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_FolderWriteResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_FOLDER_WRITE_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_FOLDER_WRITE_CAUSE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, SubBlockCount, "Number of sub blocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N_SB, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SMS_MEMORY_FOLDER_NAME)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(SMS_MEMORY_FOLDER_WRITE_REQ, SMS_MEMORY_FOLDER_WRITE_RESP)


    /* SMS_MEMORY_FOLDER_READ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_FolderReadReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_FOLDER_READ_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        FILLER_EX(PaddingByte1, 8, 1)
    MSG_END

    DER_CONST_TBL_BEGIN(SMS_MEMORY_FOLDER_READ_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_FolderReadResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_FOLDER_READ_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_FOLDER_READ_CAUSE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, SubBlockCount, "Number of sub blocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SMS_MEMORY_FOLDER_NAME)
        SB_LST_END
    MSG_END

    MSG_PAIR(SMS_MEMORY_FOLDER_READ_REQ, SMS_MEMORY_FOLDER_READ_RESP)


    /* SMS_MEMORY_FOLDER_ERASE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_FolderEraseReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_FOLDER_ERASE_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, SMS_MEMORY_FOLDER_FIRST_USER_DEFINED)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_FOLDER_LAST_USER_DEFINED)
        VALUE(8, BE, Folder, "Folder", DEC)
        FILLER_EX(PaddingByte1, 8, 1)
    MSG_END


    DER_CONST_TBL_BEGIN(SMS_MEMORY_FOLDER_ERASE_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_FolderEraseResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_FOLDER_ERASE_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_FOLDER_ERASE_CAUSE)
        FILLER_EX(PaddingByte1, 8, 1)
    MSG_END

    MSG_PAIR(SMS_MEMORY_FOLDER_ERASE_REQ, SMS_MEMORY_FOLDER_ERASE_RESP)


    /* SMS_MEMORY_RENAME */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_RenameReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_RENAME_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        STRING(STRING_UNICODE, BE, MessageName, "Message name", SMS_MEMORY_RENAME_MAX_LENGTH+1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_NAME_MAX_LENGTH)
        VALUE(8, BE, MessageNameLength, "Message name length", DEC)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
    MSG_END


    DER_CONST_TBL_BEGIN(SMS_MEMORY_RENAME_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OPER_REWRITE_FAIL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OPER_READ_FAIL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OPER_WRITE_FAIL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OPER_ERASE_FAIL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_FULL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_EMPTY_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SMS_MEMORY_RENAME_MEM_TYPE, SMS_MEMORY_TYPE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_ME)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_RenameResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_RENAME_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_RENAME_CAUSE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_RENAME_MEM_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_RENAME_MAX_LENGTH+1)
        REFERENCE(8, BE, MessageNameLength, "Message name length", N)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        STRING_REF(STRING_UNICODE, BE, MessageName, "Message name", N, ISIHDR_RESERVE_SPACE)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
    MSG_END

    MSG_PAIR(SMS_MEMORY_RENAME_REQ, SMS_MEMORY_RENAME_RESP)


    /* SMS_MEMORY_CONCAT_RENAME */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ConcatRenameReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_CONCAT_RENAME_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        STRING(STRING_UNICODE, BE, MessageName, "Message name", SMS_MEMORY_RENAME_MAX_LENGTH+1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_NAME_MAX_LENGTH)
        VALUE(8, BE, MessageNameLength, "Message name length", DEC)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
        FILLER_EX(PaddingByte3, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ConcatRenameResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_CONCAT_RENAME_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_RENAME_CAUSE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "Memory type", SMS_MEMORY_RENAME_MEM_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Folder, "Folder", SMS_MEMORY_FOLDER)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_RENAME_MAX_LENGTH+1)
        REFERENCE(8, BE, MessageNameLength, "Message name length", N)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "Location", DEC)
        STRING_REF(STRING_UNICODE, BE, MessageName, "Message name", N, ISIHDR_RESERVE_SPACE)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
    MSG_END

    MSG_PAIR(SMS_MEMORY_CONCAT_RENAME_REQ, SMS_MEMORY_CONCAT_RENAME_RESP)


    /* SMS_MEMORY_MOVE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_MoveReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_MOVE_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, CurrentLocation, "Current location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, SMS_MEMORY_FOLDER_FIRST_USER_DEFINED)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_FOLDER_LAST_USER_DEFINED)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, CurrentFolder, "Current folder", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(CurrentMemoryType, "Current memory type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(NewMemoryType, "New memory type", SMS_MEMORY_TYPE)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, SMS_MEMORY_FOLDER_FIRST_USER_DEFINED)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_FOLDER_LAST_USER_DEFINED)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, SMS_MEMORY_FOLDER_UNSPECIFIED)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, NewFolder, "New folder", DEC)
    MSG_END


    DER_CONST_TBL_BEGIN(SMS_MEMORY_MOVE_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OPER_REWRITE_FAIL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OPER_READ_FAIL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OPER_WRITE_FAIL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OPER_ERASE_FAIL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_FULL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_EMPTY_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SMS_MEMORY_MOVE_MEM_TYPE, SMS_MEMORY_TYPE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_TYPE_ME)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_MoveResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_MOVE_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_MOVE_CAUSE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "New memory type", SMS_MEMORY_MOVE_MEM_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "New location", DEC)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
    MSG_END

    MSG_PAIR(SMS_MEMORY_MOVE_REQ, SMS_MEMORY_MOVE_RESP)


    /* SMS_MEMORY_CONCAT_MOVE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ConcatMoveReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_CONCAT_MOVE_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, CurrentLocation, "Current location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, SMS_MEMORY_FOLDER_FIRST_USER_DEFINED)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_FOLDER_LAST_USER_DEFINED)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, CurrentFolder, "Current folder", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(CurrentMemoryType, "Current memory type", SMS_MEMORY_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(NewMemoryType, "New memory type", SMS_MEMORY_TYPE)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, SMS_MEMORY_FOLDER_FIRST_USER_DEFINED)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SMS_MEMORY_FOLDER_LAST_USER_DEFINED)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, SMS_MEMORY_FOLDER_UNSPECIFIED)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, NewFolder, "New folder", DEC)
    MSG_END 

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_ConcatMoveResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_CONCAT_MOVE_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_MOVE_CAUSE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(MemoryType, "New memory type", SMS_MEMORY_MOVE_MEM_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, Location, "New location", DEC)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
    MSG_END

    MSG_PAIR(SMS_MEMORY_CONCAT_MOVE_REQ, SMS_MEMORY_CONCAT_MOVE_RESP)


    /* SMS_MEMORY_GETFREEREFNUMB */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_GetFreeRefNumbReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SMS_MEMORY_GETFREEREFNUMB_REQ, MESSAGE_REQ, "", "")
        SMS_MEM_MSG_HDR
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
    MSG_END

    DER_CONST_TBL_BEGIN(SMS_MEMORY_GETFREEREFNUMB_CAUSE, SMS_MEMORY_CAUSE, "", "")
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OK)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OPER_REWRITE_FAIL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OPER_READ_FAIL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OPER_WRITE_FAIL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_OPER_ERASE_FAIL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_FULL)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SERVICE_RESERVED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NO_SIM)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_PUK_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_SEC_CODE_REQUIRED)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_EMPTY_LOCATION)
        DER_CONST_TBL_ENTRY(SMS_MEMORY_NOT_READY)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSMSMemory_GetFreeRefNumbResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ==================================================*/")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Still used DCT3.5 backward compatible definitions */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ==================================================*/")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Location status */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define ISI_SMS_STATUS_MASK         B0000_1111")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define ISI_SMS_STATUS_NOT_USED     B0000_0000")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define ISI_SMS_STATUS_MT_NOT_READ  B0000_0001")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define ISI_SMS_STATUS_MT_READ      B0000_0010")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define ISI_SMS_STATUS_MT           B0000_0011")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define ISI_SMS_STATUS_MO_NOT_SENT  B0000_0100")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define ISI_SMS_STATUS_MO_SENT      B0000_1000")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define ISI_SMS_STATUS_MO           B0000_1100")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define ISI_SMS_STATUS_USED         B0000_1111")


    MSG_BEGIN(SMS_MEMORY_GETFREEREFNUMB_RESP, MESSAGE_RESP, "", "")
        SMS_MEM_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(SMSMemoryCause, "SMS Memory Cause", SMS_MEMORY_GETFREEREFNUMB_CAUSE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(udhi_element_id, "UDHI Element ID", SMS_MEMORY_CONCATENATION_INDICATORS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, refNumber, "Reference Number", DEC)
        FILLER_EX(PaddingByte1, 8, 1)
        FILLER_EX(PaddingByte2, 8, 1)
    MSG_END

    MSG_PAIR(SMS_MEMORY_GETFREEREFNUMB_REQ, SMS_MEMORY_GETFREEREFNUMB_RESP)

RES_END
 

/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */

/* End of File */
