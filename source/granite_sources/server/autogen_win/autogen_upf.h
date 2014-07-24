/*
NOKIA MOBILE PHONES
R&D Oulu
Modena



            upf_isi_m.h
            -------------------
            SW include - ANSI C



Continuus Ref:
--------------
Project:          [CM_PROJECT_NAME]

%name:            autogen_upf.h %
%version:         1 %
%cvtype:          incl %
%instance:        co_pctls_1 %

Document code:    -

Copyright(c) Nokia Corporation. All rights reserved.

Change History:

VERSION     : 020.002           DRAFT           17-Apr-2004  Christian Jacob Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the message macro file
*/

/* ------------------------------------------------------------------------- */


/*  1    ABSTRACT

    1.1    Module type

    Message definition file for autogen
   

    1.2    Functional description

    This file is the message definition file for the User Profiles server


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

#ifndef _UPF_ISI_M_H_
#define _UPF_ISI_M_H_

/* If product build, include configuration file to improve decoding */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT
#include "srvupf_conf.h"
#endif

/*  3    CONSTANTS */

/* Message ID's */
#define UPF_SETTINGS_READ_REQ                   1
#define UPF_SETTINGS_READ_RESP                  2
#define UPF_SETTINGS_WRITE_REQ                  3
#define UPF_SETTINGS_WRITE_RESP                 4
#define UPF_ACTIVE_MODE_READ_REQ                5
#define UPF_ACTIVE_MODE_READ_RESP               6
#define UPF_ACTIVE_MODE_CHANGE_REQ              7
#define UPF_ACTIVE_MODE_CHANGE_RESP             8
#define UPF_DEFAULT_RESTORE_REQ                 9
#define UPF_DEFAULT_RESTORE_RESP                10
#define UPF_MODE_SETTING_CHANGED_IND            11
#define UPF_SINGLE_SETTING_DEFAULT_RESTORE_REQ  12
#define UPF_SINGLE_SETTING_DEFAULT_RESTORE_RESP 13
#define UPF_DEMO_MODE_REQ                       14
#define UPF_DEMO_MODE_RESP                      15
#define UPF_MODE_CHANGED_IND                    16

/* Sub block ID's */
#define UPF_SB_SETTING_TYPE_INFO                1
#define UPF_SB_SETTING_INFO                     2
#define UPF_SB_SETTING_VALUE_INFO               3
#define UPF_SB_SETTING_VALUE_TYPE_INFO          4

/* Other constants */
#define UPF_CURRENT_VALUE                       1

/* Default values */
#ifndef UPF_UI_MODE_NAME_LENGTH_MIN
#define UPF_UI_MODE_NAME_LENGTH_MIN             2
#endif

#ifndef UPF_UI_MODE_NAME_LENGTH_MAX
#define UPF_UI_MODE_NAME_LENGTH_MAX             34
#endif


/*  4    MACROS */

#define UPF_MSG_HDR \
	VALUE(8, BE, transaction_id, "Transaction ID", DEC) \
	REFERENCE(8, BE, message_id, "Message ID", MSG_ID) \

#define UPF_SB \
    REFERENCE(8, BE, block_id, "Sub Block ID", SB_ID) \
    REFERENCE(8, BE, block_length, "Sub Block Length", SB_LENGTH) 

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT
    #define SETTING_DATA_CONST(name)
#else /* AUTOGEN_ENVIRONMENT_LOCAL */
    #define SETTING_DATA_CONST(name) \
        COMMENT(COMMENT_TEXT, "1 or 8 bytes") \
        VALUE(8, BE, data_length, "Setting data length", DEC) \
        COMMENT(COMMENT_TEXT, "If gallery is used for tone selection, settings data is represented as ") \
        COMMENT_LINK(LINK_SEQUENCE, "UDF_CM_SOURCE_ID_INFO", "", "") \
        COMMENT(COMMENT_TEXT, ". Else, the following constants are possible: ") \
        COMMENT_LINK(LINK_TABLE, #name, "", "") \
        SEQ_OF_REF(setting_value, "Setting data", UPF_DATA, N, ISIHDR_MARKER_SINGLE_ELEMENT)
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT */

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT
    #define SETTING_DATA_VALUE
#else /* AUTOGEN_ENVIRONMENT_LOCAL */
    #define SETTING_DATA_VALUE \
        COMMENT(COMMENT_TEXT, "1 or 8 bytes") \
        VALUE(8, BE, data_length, "Setting data length", DEC) \
        COMMENT(COMMENT_TEXT, "If gallery is used for tone selection, settings data is represented as ") \
        COMMENT_LINK(LINK_SEQUENCE, "UDF_CM_SOURCE_ID_INFO", "", "") \
        SEQ_OF_REF(setting_value, "Setting data", UPF_DATA, N, ISIHDR_MARKER_SINGLE_ELEMENT)
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT */


/* TODO: Change the version whenever the interface is changed */
/* default ISI version */

#ifndef UPF_ISI_VERSION
#define UPF_ISI_VERSION
#define UPF_ISI_VERSION_Z      20
#define UPF_ISI_VERSION_Y      2
#endif


/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                 "R&D Copenhagen")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                      "Hamlet")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,                "Christian B. Larsen")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,           "CONFIDENTIALITY")

/* ISI header properties */
PROPERTY_STRING(PROPERTY_ISIHDR_TITLE,                      "srvupf_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                   "srvupf_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16,                "")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,       "ou_gif")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,     "global_interface/ISI/IAM")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16,  "")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,    "1.1.1")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16, "")

/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                        "ISI User Profiles Server Message Descriptions")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                     "i_upf_m.html")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,              "-")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB,         "ou_gif")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,       "GIF_SPECS-ou_gif#1.1.1")
PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH,               "GIF_SPECS/IAM")
PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)


RES_BEGIN(RESOURCE_ISI, PN_UPF, UPF, "User Profiles Server", 
    RES_VERSION_STRING(UPF_ISI_VERSION_Z, UPF_ISI_VERSION_Y), TRUE)

    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Approved in inspection")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Action DB for SWAM Change Request RN04012658453")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "17-Apr-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Christian Jacob Hansen")
    COMMENT(COMMENT_TEXT, "Added UPF_LIGHT_SEQUENCE_STATE")
    ISI_VERSION_HISTORY("020.002")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "-")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "-")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "17-Apr-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Christian Jacob Hansen")
    COMMENT(COMMENT_TEXT, "First version of the interface done with message macros")
    ISI_VERSION_HISTORY("020.000")


    /* --------------------------------------------------------------------- */
    /* Notes / references  */
    /* --------------------------------------------------------------------- */

    COMMENT(COMMENT_PARAGRAPH, "Autogeneration Process")
    COMMENT(COMMENT_PARAGRAPH, "Lotus Notes Database: Engine TEC DocMan")
    COMMENT(COMMENT_PARAGRAPH, "Document Number: DSJ00311")
    COMMENT(COMMENT_PARAGRAPH, "Filename: autogen_proc.doc")
    NOTE("/1/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Server Specification Documentation Guidelines")
    COMMENT(COMMENT_PARAGRAPH, "Document code: XXXL7714-EN-1.0")
    COMMENT(COMMENT_PARAGRAPH, "DocMan location: salns04m/SA4/NMP/Nokia")
    COMMENT(COMMENT_PARAGRAPH, "DocMan: TEC /SWP / ISA DocMan")
    COMMENT(COMMENT_PARAGRAPH, "Filename: nmp\\pcp\\ad\\swdoc.nsf")
    NOTE("/2/")

    COMMENT(COMMENT_PARAGRAPH, "ISI General Information")
    COMMENT(COMMENT_PARAGRAPH, "Document code: XXXL7715-EN-1.0")
    COMMENT(COMMENT_PARAGRAPH, "DocMan location: salns04m/SA4/NMP/Nokia")
    COMMENT(COMMENT_PARAGRAPH, "DocMan: TEC /SWP / ISA DocMan")
    COMMENT(COMMENT_PARAGRAPH, "Filename: nmp\\pcp\\ad\\swdoc.nsf")
    NOTE("/3/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Common Message Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Database: ou_gif")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Project: GIF_SPECS-ou_gif#1.1.1")
    COMMENT(COMMENT_PARAGRAPH, "Directory Path: GIF_SPECS/CoreSW")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_comm_m.html")
    NOTE("/4/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Common Feature Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Database: ou_gif")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Project: GIF_SPECS-ou_gif#1.1.1")
    COMMENT(COMMENT_PARAGRAPH, "Directory Path: GIF_SPECS/CoreSW")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_comm_fp.doc")
    NOTE("/5/")

    COMMENT(COMMENT_PARAGRAPH, "ISI User Profiles Server Feature and Protocol Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Part: ISI:COMMON.BASE")
    COMMENT(COMMENT_PARAGRAPH, "Item name: ISI:PROFILES_SERVER_FP.BASE-SPEC ")
    COMMENT(COMMENT_PARAGRAPH, "Workset: ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_upf_fp.doc")
    NOTE("/6/")


    /* --------------------------------------------------------------------- */
    /* Constants */
    /* --------------------------------------------------------------------- */

    COMMENT(COMMENT_TEXT, 
        "These constants are here for backward compatibility")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONSTANT(UPF_ISI_VERSION_ZZZ, UPF_ISI_VERSION_Z)
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONSTANT(UPF_ISI_VERSION_YYY, UPF_ISI_VERSION_Y)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(UPF_UI_MODE_NAME_LENGTH_MIN, UPF_UI_MODE_NAME_LENGTH_MIN)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(UPF_UI_MODE_NAME_LENGTH_MAX, UPF_UI_MODE_NAME_LENGTH_MAX)


    /* --------------------------------------------------------------------- */
    /* Symbol tables */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_OK,                             1, "")
        CONST_TBL_ENTRY(UPF_INVALID_MODE,                   2, "")
        CONST_TBL_ENTRY(UPF_NOT_ALLOWED,                    3, "")
        CONST_TBL_ENTRY(UPF_NOT_PRESENT,                    4, "")
        CONST_TBL_ENTRY(UPF_NOT_EXIST,                      5, "")
        CONST_TBL_ENTRY(UPF_INVALID_DATA,                   6, "")
        CONST_TBL_ENTRY(UPF_INVALID_DATA_LENGTH,            7, "")
        CONST_TBL_ENTRY(UPF_CAUSE_UNKNOWN,                  8, "")
        CONST_TBL_ENTRY(UPF_MEMORY_FAILURE,                 9, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_VALUE_INFO, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_CURRENT_VALUE,                      1, "")
        CONST_TBL_ENTRY(UPF_DEFAULT_VALUE,                      2, "")
        CONST_TBL_ENTRY(UPF_MINIMUM_VALUE,                      3, "")
        CONST_TBL_ENTRY(UPF_MAXIMUM_VALUE,                      4, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_CHANGED_NAME_STATES, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_DEFAULT_NAME,                   0, "")
        CONST_TBL_ENTRY(UPF_CHANGED_NAME,                   1, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_MODE_ACTIVATION_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_CONTINUOUS_MODE_ACTIVATION,     0, "")
        CONST_TBL_ENTRY(UPF_TIMED_MODE_ACTIVATION,          1, "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    /* Reserved for Server internal use:  Value 0x02 */")
        CONST_TBL_ENTRY(UPF_TIMED_MODE_EXPIRATION,          3, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_ACTIVATION_VALUES, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_DISABLE_SETTINGS,               0, "")
        CONST_TBL_ENTRY(UPF_ENABLE_SETTINGS,                1, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE, 8, BE, "", "")

        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_KEY_TONE_VOLUME_STATE", "", "")
        CONST_TBL_ENTRY(UPF_KEY_TONE_VOLUME_STATE,              0x00, "")

        COMMENT(COMMENT_PARAGRAPH, "Read only")
        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_LIGHT_SELECT_STATE", "", "")
        CONST_TBL_ENTRY(UPF_LIGHT_SELECT_STATE,                 0x01, "")

        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_RINGING_OPT_STATE", "", "")
        CONST_TBL_ENTRY(UPF_RINGING_OPT_STATE,                  0x02, "")

        COMMENT(COMMENT_TEXT, "Defined in ringdata_tune_id.h")
        CONST_TBL_ENTRY(UPF_RINGING_TYPE_STATE,                 0x03, "")

        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_RINGING_VOLUME_STATE", "", "")
        CONST_TBL_ENTRY(UPF_RINGING_VOLUME_STATE,               0x04, "")

        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_SMS_RINGING_TYPE_STATE", "", "")
        CONST_TBL_ENTRY(UPF_SMS_RINGING_TYPE_STATE,             0x05, "")

        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_VIBRA_SELECT_STATE", "", "")
        CONST_TBL_ENTRY(UPF_VIBRA_SELECT_STATE,                 0x06, "")

        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_WARNING_TONES_STATE", "", "")
        CONST_TBL_ENTRY(UPF_WARNING_TONES_STATE,                0x07, "")

        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_CLI_GROUP_RING_MASK_STATE", "", "")
        CONST_TBL_ENTRY(UPF_CLI_GROUP_RING_MASK_STATE,          0x08, "")
        
        COMMENT(COMMENT_PARAGRAPH, "Read only")
        COMMENT(COMMENT_PARAGRAPH, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_AUTO_ANSWER_SELECT_STATE", "", "")
        CONST_TBL_ENTRY(UPF_AUTO_ANSWER_SELECT_STATE,           0x09, "")

        COMMENT(COMMENT_PARAGRAPH, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_SMS_TONE_TYPE_STATE", "", "")
        CONST_TBL_ENTRY(UPF_SMS_TONE_TYPE_STATE,                0x0A, "")

        COMMENT(COMMENT_PARAGRAPH, "Read only")
        CONST_TBL_ENTRY(UPF_MODE_STATE,                         0x0B, "")

        CONST_TBL_ENTRY(UPF_MODE_NAME_STATE,                    0x0C, "")

        COMMENT(COMMENT_TEXT, "Look at ringdata_tune_id.h")
        CONST_TBL_ENTRY(UPF_IM_ALERT_TONE_STATE,                0x0D, "")

        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_ACTIVE_COVER_STATE", "", "")
        CONST_TBL_ENTRY(UPF_ACTIVE_COVER_STATE,                 0x0E, "")

        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_RHYTHMIC_BACKLIGHT_STATE", "", "")
        CONST_TBL_ENTRY(UPF_RHYTHMIC_BACKLIGHT_STATE,           0x0F, "")

        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_COVER_LIGHT_STATE", "", "")
        CONST_TBL_ENTRY(UPF_COVER_LIGHT_STATE,                  0x10, "")

        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_PUSH_TO_TALK_VOICE_STATUS_STATE", "", "")
        CONST_TBL_ENTRY(UPF_PUSH_TO_TALK_VOICE_STATUS_STATE,    0x11, "")

        CONST_TBL_ENTRY(UPF_PUSH_TO_TALK_NOTIFY_TONE_STATE,     0x12, "")
        CONST_TBL_ENTRY(UPF_PUSH_TO_TALK_CALLBACK_TONE_STATE,   0x13, "")

        COMMENT(COMMENT_TEXT, "Setting values: ")
        COMMENT_LINK(LINK_TABLE, "UPF_SETTING_TYPE_LIGHT_SEQUENCE_STATE", "", "020.002")
        CONST_TBL_ENTRY_VER(UPF_LIGHT_SEQUENCE_STATE,           0x14, "020.002", "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_KEY_TONE_VOLUME_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_UI_KEY_TONE_VOLUME_OFF,         0, "")
        CONST_TBL_ENTRY(UPF_UI_KEY_TONE_VOLUME_LEVEL_1,     1, "")
        CONST_TBL_ENTRY(UPF_UI_KEY_TONE_VOLUME_LEVEL_2,     2, "")
        CONST_TBL_ENTRY(UPF_UI_KEY_TONE_VOLUME_LEVEL_3,     3, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_LIGHT_SELECT_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_UI_LIGHT_SELECTION_TIMED,       0, "")
        CONST_TBL_ENTRY(UPF_UI_LIGHT_SELECTION_ON,          1, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_RINGING_OPT_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_UI_RINGING_OPT_RING,            0, "")
        CONST_TBL_ENTRY(UPF_UI_RINGING_OPT_ASCENDING,       1, "")
        CONST_TBL_ENTRY(UPF_UI_RINGING_OPT_RING_ONCE,       2, "")
        CONST_TBL_ENTRY(UPF_UI_RINGING_OPT_BEEP_ONCE,       3, "")
        CONST_TBL_ENTRY(UPF_UI_RINGING_OPT_VIP_GROUP,       4, "")
        CONST_TBL_ENTRY(UPF_UI_RINGING_OPT_SILENT,          5, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_RINGING_VOLUME_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_UI_RINGING_VOLUME_LEVEL_1,      0, "")
        CONST_TBL_ENTRY(UPF_UI_RINGING_VOLUME_LEVEL_2,      1, "")
        CONST_TBL_ENTRY(UPF_UI_RINGING_VOLUME_LEVEL_3,      2, "")
        CONST_TBL_ENTRY(UPF_UI_RINGING_VOLUME_LEVEL_4,      3, "")
        CONST_TBL_ENTRY(UPF_UI_RINGING_VOLUME_LEVEL_5,      4, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_SMS_RINGING_TYPE_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_UI_SMS_RINGING_TYPE_NONE,       0, "")
        CONST_TBL_ENTRY(UPF_UI_SMS_RINGING_TYPE_STANDARD,   1, "")
        CONST_TBL_ENTRY(UPF_UI_SMS_RINGING_TYPE_SPECIAL,    2, "")
        CONST_TBL_ENTRY(UPF_UI_SMS_RINGING_TYPE_BEEP_ONCE,  3, "")
        CONST_TBL_ENTRY(UPF_UI_SMS_RINGING_TYPE_LONG_LOUD,  4, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_VIBRA_SELECT_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_UI_VIBRA_OFF,                   0, "")
        CONST_TBL_ENTRY(UPF_UI_VIBRA_ON,                    1, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_WARNING_TONES_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_UI_WARNING_TONES_OFF,           0, "")
        CONST_TBL_ENTRY(UPF_UI_WARNING_TONES_ON,            1, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_CLI_GROUP_RING_MASK_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_UI_GROUP_MASK,                  0, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_AUTO_ANSWER_SELECT_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_UI_AUTO_ANSWER_OFF,             0, "")
        CONST_TBL_ENTRY(UPF_UI_AUTO_ANSWER_ON,              1, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_SMS_TONE_TYPE_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_UI_SMS_TONE_OFF,                0, "")
        CONST_TBL_ENTRY(UPF_UI_SMS_TONE_ON,                 1, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_MODE_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_UI_MODE_1,                      1, "")
        CONST_TBL_ENTRY(UPF_UI_MODE_2,                      2, "")
        CONST_TBL_ENTRY(UPF_UI_MODE_3,                      3, "")
        CONST_TBL_ENTRY(UPF_UI_MODE_4,                      4, "")
        CONST_TBL_ENTRY(UPF_UI_MODE_5,                      5, "")
        CONST_TBL_ENTRY(UPF_UI_MODE_6,                      6, "")
        CONST_TBL_ENTRY(UPF_UI_MODE_7,                      7, "")
        CONST_TBL_ENTRY(UPF_UI_MODE_8,                      8, "")
        CONST_TBL_ENTRY(UPF_UI_CURRENT_MODE,                255, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_ACTIVE_COVER_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_ACTIVE_COVER_OFF,               0, "")
        CONST_TBL_ENTRY(UPF_ACTIVE_COVER_ON,                1, "")
        CONST_TBL_ENTRY(UPF_ACTIVE_COVER_NEVER_CONNECTED,   2, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_RHYTHMIC_BACKLIGHT_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_RHYTHMIC_BACKLIGHT_OFF,         0, "")
        CONST_TBL_ENTRY(UPF_RHYTHMIC_BACKLIGHT_ON,          1, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_COVER_LIGHT_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_COVER_LIGHT_OFF,                0, "")
        CONST_TBL_ENTRY(UPF_COVER_LIGHT_ON,                 1, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_PUSH_TO_TALK_VOICE_STATUS_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(UPF_PUSH_TO_TALK_VOICE_STATUS_NO_DISTURB,   0, "")
        CONST_TBL_ENTRY(UPF_PUSH_TO_TALK_VOICE_STATUS_EARPIECE,     1, "")
        CONST_TBL_ENTRY(UPF_PUSH_TO_TALK_VOICE_STATUS_LOUDSPEAKER,  2, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(UPF_SETTING_TYPE_LIGHT_SEQUENCE_STATE, 8, BE, "020.002", "")
        CONST_TBL_ENTRY(UPF_LIGHT_SEQUENCE_OFF,             0, "")
        CONST_TBL_ENTRY(UPF_LIGHT_SEQUENCE_ON,              1, "")
    CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* FTD data table */
    /* --------------------------------------------------------------------- */


    /* --------------------------------------------------------------------- */
    /* Sequences */
    /* --------------------------------------------------------------------- */

    SEQ_BEGIN(UPF_DATA, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, data, "Data", HEX)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFCmSourceIdInfo")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(UDF_CM_SOURCE_ID_INFO, CREATE_STRUCT, "", "")
        COMMENT(COMMENT_TEXT,
            "Depends on source object. Usually an unique ID number")
        VALUE(32, BE, instance, "Object instance", HEX)
        COMMENT(COMMENT_TEXT,
            "Defined in cm_source.h (one of the values in enum CM_SOURCE_CATEGORY)")
        VALUE(32, BE, category, "Object category", HEX)
    SEQ_END


    /* --------------------------------------------------------------------- */
    /* Setting data*/
    /* --------------------------------------------------------------------- */


    /* UDF_KEY_TONE_VOLUME_STATE */

    SEQ_BEGIN(UDF_SETTING_KEY_TONE_VOLUME_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_KEY_TONE_VOLUME_STATE)
    SEQ_END

    /* UPF_LIGHT_SELECT_STATE */

    SEQ_BEGIN(UPF_SETTING_LIGHT_SELECT_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_LIGHT_SELECT_STATE)
    SEQ_END

    /* UPF_RINGING_OPT_STATE */

    SEQ_BEGIN(UPF_SETTING_RINGING_OPT_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_RINGING_OPT_STATE)
    SEQ_END

    /* UPF_RINGING_TYPE_STATE */

    SEQ_BEGIN(UPF_SETTING_RINGING_TYPE_STATE, DONT_CREATE_STRUCT, "", "")
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, UPF_RINGING_TYPE_STATE)
        VALUE(8, BE, data_length, "Setting data length", DEC)
#ifdef UPF_GALLERY_TONES
        SEQ_OF(setting_gallery, "Setting data", UDF_CM_SOURCE_ID_INFO, 1)
#else
        VALUE(8, BE, setting_value, "Setting data", HEX)
#endif /* UPF_GALLERY_TONES */
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT */
        SETTING_DATA_VALUE
    SEQ_END

    /* UPF_RINGING_VOLUME_STATE */

    SEQ_BEGIN(UPF_SETTING_RINGING_VOLUME_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_RINGING_VOLUME_STATE)
    SEQ_END

    /* UPF_SMS_RINGING_TYPE_STATE */

    SEQ_BEGIN(UPF_SETTING_SMS_RINGING_TYPE_STATE, DONT_CREATE_STRUCT, "", "")
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, UPF_SMS_RINGING_TYPE_STATE_MAX_LENGTH)
        VALUE(8, BE, data_length, "Setting data length", DEC)
#ifdef UPF_GALLERY_TONES
        SEQ_OF(setting_gallery, "Setting data", UDF_CM_SOURCE_ID_INFO, 1)
#else
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_SMS_RINGING_TYPE_STATE)
#endif /* UPF_GALLERY_TONES */
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT */
        SETTING_DATA_CONST(UPF_SETTING_TYPE_SMS_RINGING_TYPE_STATE)
    SEQ_END

    /* UPF_VIBRA_SELECT_STATE */

    SEQ_BEGIN(UPF_SETTING_VIBRA_SELECT_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_VIBRA_SELECT_STATE)
    SEQ_END

    /* UPF_WARNING_TONES_STATE */

    SEQ_BEGIN(UPF_SETTING_WARNING_TONES_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_WARNING_TONES_STATE)
    SEQ_END

    /* UPF_CLI_GROUP_RING_MASK_STATE */

    SEQ_BEGIN(UPF_SETTING_CLI_GROUP_RING_MASK_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE(8, BE, setting_value, "Setting data", HEX)
    SEQ_END

    /* UPF_AUTO_ANSWER_SELECT_STATE */

    SEQ_BEGIN(UPF_SETTING_AUTO_ANSWER_SELECT_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_AUTO_ANSWER_SELECT_STATE)
    SEQ_END

    /* UPF_SMS_TONE_TYPE_STATE */

    SEQ_BEGIN(UPF_SETTING_SMS_TONE_TYPE_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_SMS_TONE_TYPE_STATE)
    SEQ_END

    /* UPF_MODE_STATE */

    SEQ_BEGIN(UPF_SETTING_MODE_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_MODE_STATE)
    SEQ_END

    /* UPF_MODE_NAME_STATE */
    
    SEQ_BEGIN(UPF_SETTING_MODE_NAME_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, UPF_UI_MODE_NAME_LENGTH_MIN)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, UPF_UI_MODE_NAME_LENGTH_MAX)
        REFERENCE(8, BE, data_length, "Setting data length", N)
        STRING_REF(STRING_ASCII, BE, setting_value, "Setting data", N, ISIHDR_DONT_GENERATE)
    SEQ_END

    /* UPF_ACTIVE_COVER_STATE */

    SEQ_BEGIN(UPF_SETTING_ACTIVE_COVER_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_ACTIVE_COVER_STATE)
    SEQ_END

    /* UPF_RHYTHMIC_BACKLIGHT_STATE */

    SEQ_BEGIN(UPF_SETTING_RHYTHMIC_BACKLIGHT_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_RHYTHMIC_BACKLIGHT_STATE)
    SEQ_END

    /* UPF_COVER_LIGHT_STATE */

    SEQ_BEGIN(UPF_SETTING_COVER_LIGHT_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_COVER_LIGHT_STATE)
    SEQ_END

    /* UPF_PUSH_TO_TALK_VOICE_STATUS_STATE */

    SEQ_BEGIN(UPF_SETTING_PUSH_TO_TALK_VOICE_STATUS_STATE, DONT_CREATE_STRUCT, "", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_PUSH_TO_TALK_VOICE_STATUS_STATE)
    SEQ_END

    /* UPF_LIGHT_SEQUENCE_STATE */

    SEQ_BEGIN(UPF_SETTING_LIGHT_SEQUENCE_STATE, DONT_CREATE_STRUCT, "020.002", "")
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 1)
        VALUE(8, BE, data_length, "Setting data length", DEC)
        VALUE_CONST(setting_value, "Setting data", UPF_SETTING_TYPE_LIGHT_SEQUENCE_STATE)
    SEQ_END

    /* UPF_IM_ALERT_TONE_STATE */

    SEQ_BEGIN(UPF_SETTING_IM_ALERT_TONE_STATE, DONT_CREATE_STRUCT, "", "")
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, UPF_IM_ALERT_TONE_STATE)
        VALUE(8, BE, data_length, "Setting data length", DEC)
#ifdef UPF_GALLERY_TONES
        SEQ_OF(setting_gallery, "Setting data", UDF_CM_SOURCE_ID_INFO, 1)
#else
        VALUE(8, BE, setting_value, "Setting data", HEX)
#endif /* UPF_GALLERY_TONES */
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT */
        SETTING_DATA_VALUE
    SEQ_END

    /* UPF_PUSH_TO_TALK_CALLBACK_TONE_STATE */

    SEQ_BEGIN(UPF_SETTING_PUSH_TO_TALK_CALLBACK_TONE_STATE, DONT_CREATE_STRUCT, "", "")
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, UPF_PUSH_TO_TALK_CALLBACK_TONE_STATE)
        VALUE(8, BE, data_length, "Setting data length", DEC)
#ifdef UPF_GALLERY_TONES
        SEQ_OF(setting_gallery, "Setting data", UDF_CM_SOURCE_ID_INFO, 1)
#else
        VALUE(8, BE, setting_value, "Setting data", HEX)
#endif /* UPF_GALLERY_TONES */
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT */
    SEQ_END

    /* UPF_PUSH_TO_TALK_NOTIFY_TONE_STATE */

    SEQ_BEGIN(UPF_SETTING_PUSH_TO_TALK_NOTIFY_TONE_STATE, DONT_CREATE_STRUCT, "", "")
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, UPF_PUSH_TO_TALK_NOTIFY_TONE_STATE)
        VALUE(8, BE, data_length, "Setting data length", DEC)
#ifdef UPF_GALLERY_TONES
        SEQ_OF(setting_gallery, "Setting data", UDF_CM_SOURCE_ID_INFO, 1)
#else
        VALUE(8, BE, setting_value, "Setting data", HEX)
#endif /* UPF_GALLERY_TONES */
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT */
        SETTING_DATA_VALUE
    SEQ_END

    /* Default */

    SEQ_BEGIN(UDF_SETTING_DEFAULT, DONT_CREATE_STRUCT, "", "")
        REFERENCE(8, BE, data_length, "Setting data length", N)
        SEQ_OF_REF(setting_value, "Setting data", UPF_DATA, N, ISIHDR_MARKER_SINGLE_ELEMENT)
    SEQ_END


    /* --------------------------------------------------------------------- */
    /* Sub blocks */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFSettingTypeInfo")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(UPF_SB_SETTING_TYPE_INFO, "", "")
        UPF_SB
        VALUE_CONST(mode_type, "Mode type", UPF_SETTING_TYPE_MODE_STATE)
        VALUE_CONST(setting_type, "Setting type", UPF_SETTING_TYPE)
    SB_END


    DER_CONST_TBL_BEGIN(UPF_STATUS_SETTING_INFO, UPF_STATUS, "", "")
        DER_CONST_TBL_ENTRY(UPF_OK)
        DER_CONST_TBL_ENTRY(UPF_INVALID_MODE)
        DER_CONST_TBL_ENTRY(UPF_NOT_EXIST)
        DER_CONST_TBL_ENTRY(UPF_NOT_PRESENT)
        DER_CONST_TBL_ENTRY(UPF_CAUSE_UNKNOWN)
        DER_CONST_TBL_ENTRY(UPF_MEMORY_FAILURE)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFSettingInfo")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 252)
    SB_BEGIN(UPF_SB_SETTING_INFO, "", "")
        UPF_SB
        REFERENCE_CONST(setting_type, "Setting type", ID, UPF_SETTING_TYPE)
        VALUE_CONST(status, "Status", UPF_STATUS_SETTING_INFO)
        VALUE_CONST(mode_type, "Mode type", UPF_SETTING_TYPE_MODE_STATE)
        VALUE_CONST(changed_name, "Changed name", UPF_CHANGED_NAME_STATES)
        FILLER_EX(reserved_1, 8, 1)
        CHOICE_BEGIN(Setting, "Setting data", ID)
            CASE(UPF_KEY_TONE_VOLUME_STATE,             UDF_SETTING_KEY_TONE_VOLUME_STATE)
            CASE(UPF_LIGHT_SELECT_STATE,                UPF_SETTING_LIGHT_SELECT_STATE)
            CASE(UPF_RINGING_OPT_STATE,                 UPF_SETTING_RINGING_OPT_STATE)
            CASE(UPF_RINGING_TYPE_STATE,                UPF_SETTING_RINGING_TYPE_STATE)
            CASE(UPF_RINGING_VOLUME_STATE,              UPF_SETTING_RINGING_VOLUME_STATE)
            CASE(UPF_SMS_RINGING_TYPE_STATE,            UPF_SETTING_SMS_RINGING_TYPE_STATE)
            CASE(UPF_VIBRA_SELECT_STATE,                UPF_SETTING_VIBRA_SELECT_STATE)
            CASE(UPF_WARNING_TONES_STATE,               UPF_SETTING_WARNING_TONES_STATE)
            CASE(UPF_CLI_GROUP_RING_MASK_STATE,         UPF_SETTING_CLI_GROUP_RING_MASK_STATE)
            CASE(UPF_AUTO_ANSWER_SELECT_STATE,          UPF_SETTING_AUTO_ANSWER_SELECT_STATE)
            CASE(UPF_SMS_TONE_TYPE_STATE,               UPF_SETTING_SMS_TONE_TYPE_STATE)
            CASE(UPF_MODE_STATE,                        UPF_SETTING_MODE_STATE)
            CASE(UPF_MODE_NAME_STATE,                   UPF_SETTING_MODE_NAME_STATE)
            CASE(UPF_IM_ALERT_TONE_STATE,               UPF_SETTING_IM_ALERT_TONE_STATE)
            CASE(UPF_ACTIVE_COVER_STATE,                UPF_SETTING_ACTIVE_COVER_STATE)
            CASE(UPF_RHYTHMIC_BACKLIGHT_STATE,          UPF_SETTING_RHYTHMIC_BACKLIGHT_STATE)
            CASE(UPF_COVER_LIGHT_STATE,                 UPF_SETTING_COVER_LIGHT_STATE)
            CASE(UPF_PUSH_TO_TALK_VOICE_STATUS_STATE,   UPF_SETTING_PUSH_TO_TALK_VOICE_STATUS_STATE)
            CASE(UPF_PUSH_TO_TALK_NOTIFY_TONE_STATE,    UPF_SETTING_PUSH_TO_TALK_NOTIFY_TONE_STATE)
            CASE(UPF_PUSH_TO_TALK_CALLBACK_TONE_STATE,  UPF_SETTING_PUSH_TO_TALK_CALLBACK_TONE_STATE)
            CASE_VER(UPF_LIGHT_SEQUENCE_STATE,          UPF_SETTING_LIGHT_SEQUENCE_STATE, "020.002", "")
            CASE_DEFAULT(UDF_SETTING_DEFAULT)
        CHOICE_END
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFSettingValueInfo")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 252)
    SB_BEGIN(UPF_SB_SETTING_VALUE_INFO, "", "")
        UPF_SB
        REFERENCE_CONST(setting_type, "Setting type", ID, UPF_SETTING_TYPE)
        VALUE_CONST(mode_type, "Mode type", UPF_SETTING_TYPE_MODE_STATE)
        VALUE_CONST(changed_name, "Changed name", UPF_CHANGED_NAME_STATES)
        FILLER_EX(reserved_1, 8, 1)
        FILLER_EX(reserved_2, 8, 1)
        CHOICE_BEGIN(Setting, "Setting data", ID)
            CASE(UPF_KEY_TONE_VOLUME_STATE,             UDF_SETTING_KEY_TONE_VOLUME_STATE)
            CASE(UPF_LIGHT_SELECT_STATE,                UPF_SETTING_LIGHT_SELECT_STATE)
            CASE(UPF_RINGING_OPT_STATE,                 UPF_SETTING_RINGING_OPT_STATE)
            CASE(UPF_RINGING_TYPE_STATE,                UPF_SETTING_RINGING_TYPE_STATE)
            CASE(UPF_RINGING_VOLUME_STATE,              UPF_SETTING_RINGING_VOLUME_STATE)
            CASE(UPF_SMS_RINGING_TYPE_STATE,            UPF_SETTING_SMS_RINGING_TYPE_STATE)
            CASE(UPF_VIBRA_SELECT_STATE,                UPF_SETTING_VIBRA_SELECT_STATE)
            CASE(UPF_WARNING_TONES_STATE,               UPF_SETTING_WARNING_TONES_STATE)
            CASE(UPF_CLI_GROUP_RING_MASK_STATE,         UPF_SETTING_CLI_GROUP_RING_MASK_STATE)
            CASE(UPF_AUTO_ANSWER_SELECT_STATE,          UPF_SETTING_AUTO_ANSWER_SELECT_STATE)
            CASE(UPF_SMS_TONE_TYPE_STATE,               UPF_SETTING_SMS_TONE_TYPE_STATE)
            CASE(UPF_MODE_STATE,                        UPF_SETTING_MODE_STATE)
            CASE(UPF_MODE_NAME_STATE,                   UPF_SETTING_MODE_NAME_STATE)
            CASE(UPF_IM_ALERT_TONE_STATE,               UPF_SETTING_IM_ALERT_TONE_STATE)
            CASE(UPF_ACTIVE_COVER_STATE,                UPF_SETTING_ACTIVE_COVER_STATE)
            CASE(UPF_RHYTHMIC_BACKLIGHT_STATE,          UPF_SETTING_RHYTHMIC_BACKLIGHT_STATE)
            CASE(UPF_COVER_LIGHT_STATE,                 UPF_SETTING_COVER_LIGHT_STATE)
            CASE(UPF_PUSH_TO_TALK_VOICE_STATUS_STATE,   UPF_SETTING_PUSH_TO_TALK_VOICE_STATUS_STATE)
            CASE(UPF_PUSH_TO_TALK_NOTIFY_TONE_STATE,    UPF_SETTING_PUSH_TO_TALK_NOTIFY_TONE_STATE)
            CASE(UPF_PUSH_TO_TALK_CALLBACK_TONE_STATE,  UPF_SETTING_PUSH_TO_TALK_CALLBACK_TONE_STATE)
            CASE_VER(UPF_LIGHT_SEQUENCE_STATE,          UPF_SETTING_LIGHT_SEQUENCE_STATE, "020.002", "")
            CASE_DEFAULT(UDF_SETTING_DEFAULT)
        CHOICE_END
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    DER_CONST_TBL_BEGIN(UPF_STATUS_VALUE_TYPE_INFO, UPF_STATUS, "", "")
        DER_CONST_TBL_ENTRY(UPF_OK)
        DER_CONST_TBL_ENTRY(UPF_INVALID_MODE)
        DER_CONST_TBL_ENTRY(UPF_NOT_EXIST)
        DER_CONST_TBL_ENTRY(UPF_NOT_PRESENT)
        DER_CONST_TBL_ENTRY(UPF_NOT_ALLOWED)
        DER_CONST_TBL_ENTRY(UPF_INVALID_DATA_LENGTH)
        DER_CONST_TBL_ENTRY(UPF_INVALID_DATA)
        DER_CONST_TBL_ENTRY(UPF_MEMORY_FAILURE)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFSettingValueTypeInfo")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(UPF_SB_SETTING_VALUE_TYPE_INFO, "", "")
        UPF_SB
        VALUE_CONST(setting_type, "Setting type", UPF_SETTING_TYPE)
        VALUE_CONST(mode_type, "Mode type", UPF_SETTING_TYPE_MODE_STATE)
        VALUE_CONST(status, "Status", UPF_STATUS_VALUE_TYPE_INFO)
        FILLER_EX(reserved_1, 8, 1)
        FILLER_EX(reserved_2, 8, 1)
        FILLER_EX(reserved_3, 8, 1)
    SB_END


    /* --------------------------------------------------------------------- */
    /* Messages */
    /* --------------------------------------------------------------------- */


    /* UPF_SETTINGS_READ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFSettingsReadReq")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_SETTINGS_READ_REQ, MESSAGE_REQ, "", "")
        UPF_MSG_HDR
        VALUE_CONST(value_type, "Value type", UPF_VALUE_INFO)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, no_of_sub_blocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_block, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(UPF_SB_SETTING_TYPE_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFSettingsReadResp")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_SETTINGS_READ_RESP, MESSAGE_RESP, "", "")
        UPF_MSG_HDR
        FILLER_EX(reserved_1, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, no_of_sub_blocks, "Number of sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_block, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(UPF_SB_SETTING_INFO)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(UPF_SETTINGS_READ_REQ, UPF_SETTINGS_READ_RESP)


    /* UPF_SETTINGS_WRITE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFSettingsWriteReq")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_SETTINGS_WRITE_REQ, MESSAGE_REQ, "", "")
        UPF_MSG_HDR
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, UPF_CURRENT_VALUE)
        VALUE_CONST(value_type, "Value type", UPF_VALUE_INFO)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, no_of_sub_blocks, "Number of Sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_block, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(UPF_SB_SETTING_VALUE_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFSettingsWriteResp")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_SETTINGS_WRITE_RESP, MESSAGE_RESP, "", "")
        UPF_MSG_HDR
        FILLER_EX(reserved_1, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, no_of_sub_blocks, "Number of Sub blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_block, "Sub blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(UPF_SB_SETTING_VALUE_TYPE_INFO)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(UPF_SETTINGS_WRITE_REQ, UPF_SETTINGS_WRITE_RESP)


    /* UPF_ACTIVE_MODE_READ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFActiveModeReadReq")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_ACTIVE_MODE_READ_REQ, MESSAGE_REQ, "", "")
        UPF_MSG_HDR
        FILLER_EX(reserved_1, 8, 1)
        FILLER_EX(reserved_2, 8, 1)
    MSG_END

    DER_CONST_TBL_BEGIN(UPF_STATUS_ACTIVE_MODE_READ, UPF_STATUS, "", "")
        DER_CONST_TBL_ENTRY(UPF_OK)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFActiveModeReadResp")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_ACTIVE_MODE_READ_RESP, MESSAGE_RESP, "", "")
        UPF_MSG_HDR
        VALUE_CONST(status, "Status", UPF_STATUS_ACTIVE_MODE_READ)
        VALUE_CONST(mode_type, "Mode type", UPF_SETTING_TYPE_MODE_STATE)
        VALUE_CONST(mode_activation_type, "Mode activation type", UPF_MODE_ACTIVATION_TYPES)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 23)
        VALUE(8, BE, expiration_hours, "Expiration hours", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 59)
        VALUE(8, BE, expiration_minutes, "Expiration minutes", DEC)
        FILLER_EX(padding_1, 8, 1)
    MSG_END

    MSG_PAIR(UPF_ACTIVE_MODE_READ_REQ, UPF_ACTIVE_MODE_READ_RESP)


    /* UPF_ACTIVE_MODE_CHANGE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFActiveModeChangeReq")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_ACTIVE_MODE_CHANGE_REQ, MESSAGE_REQ, "", "")
        UPF_MSG_HDR
        VALUE_CONST(new_mode_type, "New mode type", UPF_SETTING_TYPE_MODE_STATE)
        VALUE_CONST(mode_activation_type, "Mode activation type", UPF_MODE_ACTIVATION_TYPES)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 23)
        VALUE(8, BE, expiration_hours, "Expiration hours", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 59)
        VALUE(8, BE, expiration_minutes, "Expiration minutes", DEC)
        FILLER_EX(padding_1, 8, 1)
        FILLER_EX(padding_2, 8, 1)
    MSG_END

    DER_CONST_TBL_BEGIN(UPF_STATUS_ACTIVE_MODE_CHANGE, UPF_STATUS, "", "")
        DER_CONST_TBL_ENTRY(UPF_OK)
        DER_CONST_TBL_ENTRY(UPF_INVALID_MODE)
        DER_CONST_TBL_ENTRY(UPF_NOT_ALLOWED)
        DER_CONST_TBL_ENTRY(UPF_MEMORY_FAILURE)
        DER_CONST_TBL_ENTRY(UPF_INVALID_DATA)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFActiveModeChangeResp")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_ACTIVE_MODE_CHANGE_RESP, MESSAGE_RESP, "", "")
        UPF_MSG_HDR
        VALUE_CONST(status, "Status", UPF_STATUS_ACTIVE_MODE_CHANGE)
        FILLER_EX(reserved_1, 8, 1)
    MSG_END

    MSG_PAIR(UPF_ACTIVE_MODE_CHANGE_REQ, UPF_ACTIVE_MODE_CHANGE_RESP)


    /* UPF_DEFAULT_RESTORE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFDefaultRestoreReq")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_DEFAULT_RESTORE_REQ, MESSAGE_REQ, "", "")
        UPF_MSG_HDR
        FILLER_EX(reserved_1, 8, 1)
        FILLER_EX(reserved_2, 8, 1)
    MSG_END

    DER_CONST_TBL_BEGIN(UPF_STATUS_DEFAULT_RESTORE, UPF_STATUS, "", "")
        DER_CONST_TBL_ENTRY(UPF_OK)
        DER_CONST_TBL_ENTRY(UPF_MEMORY_FAILURE)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFDefaultRestoreResp")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_DEFAULT_RESTORE_RESP, MESSAGE_RESP, "", "")
        UPF_MSG_HDR
        VALUE_CONST(status, "Status", UPF_STATUS_DEFAULT_RESTORE)
        FILLER_EX(reserved_1, 8, 1)
    MSG_END

    MSG_PAIR(UPF_DEFAULT_RESTORE_REQ, UPF_DEFAULT_RESTORE_RESP)


    /* UPF_SINGLE_SETTING_DEFAULT_RESTORE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFSingleSettingDefaultRestoreReq")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_SINGLE_SETTING_DEFAULT_RESTORE_REQ, MESSAGE_REQ, "", "")
        UPF_MSG_HDR
        VALUE_CONST(mode, "Mode type", UPF_SETTING_TYPE_MODE_STATE)
        VALUE_CONST(setting, "Setting type", UPF_SETTING_TYPE)
    MSG_END

    DER_CONST_TBL_BEGIN(UPF_STATUS_SINGLE_SETTING_DEFAULT_RESTORE, UPF_STATUS, "", "")
        DER_CONST_TBL_ENTRY(UPF_OK)
        DER_CONST_TBL_ENTRY(UPF_INVALID_MODE)
        DER_CONST_TBL_ENTRY(UPF_NOT_ALLOWED)
        DER_CONST_TBL_ENTRY(UPF_NOT_EXIST)
        DER_CONST_TBL_ENTRY(UPF_MEMORY_FAILURE)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFSingleSettingDefaultRestoreResp")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_SINGLE_SETTING_DEFAULT_RESTORE_RESP, MESSAGE_RESP, "", "")
        UPF_MSG_HDR
        VALUE_CONST(status, "Status", UPF_STATUS_SINGLE_SETTING_DEFAULT_RESTORE)
        FILLER_EX(reserved_1, 8, 1)
    MSG_END

    MSG_PAIR(UPF_SINGLE_SETTING_DEFAULT_RESTORE_REQ, UPF_SINGLE_SETTING_DEFAULT_RESTORE_RESP)


    /* UPF_DEMO_MODE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFDemoModeReq")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_DEMO_MODE_REQ, MESSAGE_REQ, "", "")
        UPF_MSG_HDR
        VALUE_CONST(mode, "Mode type", UPF_SETTING_TYPE_MODE_STATE)
        VALUE_CONST(activation, "Activation", UPF_ACTIVATION_VALUES)
        VALUE(8, BE, tune_group, "Tune group", HEX)
        FILLER_EX(reserved_1, 8, 1)
        FILLER_EX(reserved_2, 8, 1)
        FILLER_EX(reserved_3, 8, 1)
    MSG_END

    DER_CONST_TBL_BEGIN(UPF_STATUS_DEMO_MODE, UPF_STATUS, "", "")
        DER_CONST_TBL_ENTRY(UPF_OK)
        DER_CONST_TBL_ENTRY(UPF_INVALID_MODE)
        DER_CONST_TBL_ENTRY(UPF_CAUSE_UNKNOWN)
        DER_CONST_TBL_ENTRY(UPF_MEMORY_FAILURE)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFDemoModeResp")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_DEMO_MODE_RESP, MESSAGE_RESP, "", "")
        UPF_MSG_HDR
        VALUE_CONST(status, "Status", UPF_STATUS_DEMO_MODE)
        FILLER_EX(reserved_1, 8, 1)
    MSG_END

    MSG_PAIR(UPF_DEMO_MODE_REQ, UPF_DEMO_MODE_RESP)


    /* UPF_MODE_SETTING_CHANGED_IND */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFModeSettingChangedInd")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_MODE_SETTING_CHANGED_IND, MESSAGE_IND, "", "")
        UPF_MSG_HDR
        VALUE_CONST(mode_type, "Mode type", UPF_SETTING_TYPE_MODE_STATE)
        VALUE_CONST(setting_type, "Setting type", UPF_SETTING_TYPE)
        FILLER_EX(reserved_1, 8, 1)
        FILLER_EX(reserved_2, 8, 1)
        FILLER_EX(reserved_3, 8, 1)
        REFERENCE(8, BE, data_length, "Setting data length", N)
        SEQ_OF_REF(setting_data, "Setting data", UPF_DATA, N, ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    MSG_END


    /* UPF_MODE_CHANGED_IND */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tUPFModeChangedInd")
	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(UPF_MODE_CHANGED_IND, MESSAGE_IND, "", "")
        UPF_MSG_HDR
        VALUE_CONST(mode_type, "Mode type", UPF_SETTING_TYPE_MODE_STATE)
        VALUE_CONST(mode_activation_type, "Mode activation type", UPF_MODE_ACTIVATION_TYPES)
    MSG_END

RES_END


/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */


#endif /* _UPF_ISI_M_H_


/* End of file upf_isi_m.h */

