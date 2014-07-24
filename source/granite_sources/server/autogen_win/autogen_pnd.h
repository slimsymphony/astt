/*
NOKIA MOBILE PHONES
R&D Southwood
ALPHA SCF



            pnd_isi_m.h
            -------------------
            SW include - ANSI C



Continuus Ref:
--------------
Project:          [CM_PROJECT_NAME]

%name:            autogen_pnd.h %
%version:         co1tss#005.033 %
%cvtype:          incl %
%instance:        co_pctls_1 %

Document code:    -

Copyright(c) Nokia Corporation. All rights reserved.

Change history:

VERSION     : 005.032    DRAFT        21-Apr-2005  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Changed by Phonebook server team in UK

VERSION     : 005.013    DRAFT        18-May-2004  Christian Jacob Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the file
*/

/* ------------------------------------------------------------------------- */


/*  1    ABSTRACT

    1.1    Module type

    Message definition file for autogen
   

    1.2    Functional description

    This file is the message definition file for the Phonebook server


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

#ifndef _PND_ISI_M_H_
#define _PND_ISI_M_H_

/* If product build, include configuration file to improve decoding */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT
#include "srvpb_conf.h"
#endif


/*  3    CONSTANTS */


/* Message ID's */

#define PND_MEMORY_TYPE_LIST_REQ         0x01
#define PND_MEMORY_TYPE_LIST_RESP        0x02
#define PND_MEMORY_STATUS_REQ            0x03
#define PND_MEMORY_STATUS_RESP           0x04
#define PND_EMPTY_LOCATION_REQ           0x05
#define PND_EMPTY_LOCATION_RESP          0x06
#define PND_READ_REQ                     0x07
#define PND_READ_RESP                    0x08
#define PND_FIELD_READ_REQ               0x09
#define PND_FIELD_READ_RESP              0x0A
#define PND_WRITE_REQ                    0x0B
#define PND_WRITE_RESP                   0x0C       
#define PND_FIELD_WRITE_REQ              0x0D
#define PND_FIELD_WRITE_RESP             0x0E
#define PND_ERASE_REQ                    0x0F
#define PND_ERASE_RESP                   0x10
/* Removed - do not reuse 0x11-0x12 */
#define PND_LOCATION_CHECK_REQ           0x13
#define PND_LOCATION_CHECK_RESP          0x14
#define PND_MEMORY_RESERVE_REQ           0x15
#define PND_MEMORY_RESERVE_RESP          0x16
#define PND_MEMORY_RELEASE_REQ           0x17
#define PND_MEMORY_RELEASE_RESP          0x18
#define PND_FACTORY_SET_REQ              0x19
#define PND_FACTORY_SET_RESP             0x1A
#define PND_CALL_STACK_CHANGED_IND       0x1B
#define PND_FIELD_ERASE_REQ              0x1C
#define PND_FIELD_ERASE_RESP             0x1D
#define PND_RECORD_UPDATED_IND           0x1E
#define PND_PROPERTY_SET_REQ             0x1F
#define PND_PROPERTY_SET_RESP            0x20
#define PND_PROPERTY_GET_REQ             0x21
#define PND_PROPERTY_GET_RESP            0x22
#define PND_RESET_CALL_CTRS_REQ          0x23
#define PND_RESET_CALL_CTRS_RESP         0x24
#define PND_FIELD_DESCRIPTORS_GET_REQ    0x25
#define PND_FIELD_DESCRIPTORS_GET_RESP   0x26
#define PND_DEFAULT_NUMBER_SET_REQ       0x27
#define PND_DEFAULT_NUMBER_SET_RESP      0x28
/* Removed - do not reuse 0x29 */
#define PND_SET_RECOVERY_STATE_REQ       0x2A
#define PND_SET_RECOVERY_STATE_RESP      0x2B
/* Removed - do not reuse 0x2c-0x2d */
#define PND_MEMORY_RELEASE_IND           0x2E
#define PND_CLOG_GETCOUNTER_REQ          0x2F
#define PND_CLOG_GETCOUNTER_RESP         0x30
#define PND_CLOG_GETLOG_REQ              0x31
#define PND_CLOG_GETLOG_RESP             0x32
#define PND_CLOG_COUNTERSAVE_REQ         0x33
#define PND_CLOG_COUNTERSAVE_RESP        0x34
#define PND_CLOG_FORCERESYNC_REQ         0x35
#define PND_CLOG_FORCERESYNC_RESP        0x36
/* Removed - do not reuse 0x37 */
#define PND_INIT_READY_IND               0x38
#define PND_REFMEM_QUERY_REQ             0x39
#define PND_REFMEM_QUERY_RESP            0x3A
#define PND_LANGUAGE_CHANGED_IND         0x3B
#define PND_MEM_READ_IND                 0x3C
#define PND_DYN_START_REQ                0x3D
#define PND_DYN_START_RESP               0x3E
#define PND_DYN_STOP_REQ                 0x3F
#define PND_DYN_STOP_RESP                0x40
#define PND_PRESENCE_UPDATED_IND         0x41
#define PND_PROPERTY_SET_IND             0x42
#define PND_READ_RECOVERY_REQ            0x43
#define PND_READ_RECOVERY_RESP           0x44
/* Notice: If you add a new message id, remember */
/*         to modify PND_LAST_MESSAGE_ID below ! */
#define PND_LAST_MESSAGE_ID              0x44


/* Sub Block ID's */

#define PND_RECORD_INFO                  0x01
#define PND_CALL_STACK_INFO              0x02
#define PND_LOCATION_STATUS_INFO         0x03
#define PND_RECORD_REFERENCE_FIELD       0x04
#define PND_MEM_TYPE_INFO                0x05
#define PND_MEM_TYPE_AVAILABLE_INFO      0x06
#define PND_NAME_FIELD                   0x07
#define PND_EMAIL_ADDRESS_FIELD          0x08
#define PND_POST_ADDRESS_FIELD           0x09
#define PND_NOTE_FIELD                   0x0A
#define PND_PHONE_NUMBER_FIELD           0x0B
#define PND_RING_TONE_ID_FIELD           0x0C
/* Removed - do not reuse 0x0E */
#define PND_REQUEST_FAILED               0x0F
#define PND_MEMORY_STATUS_INFO           0x10
/* Removed - do not reuse 0x11 */
#define PND_VM_PASSWORD_FIELD            0x12
#define PND_TIME_STAMP_FIELD             0x13
#define PND_LANGUAGE_INFO                0x14
#define PND_DEFAULT_MEMORY_INFO          0x15
/* Removed - do not reuse 0x16-0x18 */
#define PND_CALL_COUNT_FIELD             0x19
#define PND_FIELD_REFERENCE_FIELD        0x1A
#define PND_CLI_ICON_FIELD               0x1B
#define PND_CLI_ICON_ENABLE_STATUS_FIELD 0x1C
#define PND_FIELD_DESCRIPTOR_INFO        0x1D
#define PND_GROUP_ID_FIELD               0x1E
#define PND_MATCHED_FIELD_INFO           0x1F
/* Removed - do not reuse 0x20-0x25 */
#define PND_FIELD_LIST_INFO              0x26
/* Removed - do not reuse 0x27 */
#define PND_ORDER_DATA_FIELD             0x28
#define PND_REFMEM_QUERY_INFO_FIELD      0x29
#define PND_DEVICE_FIELD                 0x2A
#define PND_CHANGELOG_FIELD              0x2B
#define PND_WEB_ADDRESS_FIELD            0x2C
#define PND_REF_MASKED_CRITERIA_INFO     0x2D
#define PND_REF_SMSDL_FIELD              0x2E
#define PND_REF_VOICETAG_FIELD           0x2F
#define PND_RESERVATION_INFO             0x30
#define PND_REF_VALUE_CRITERIA_INFO      0x31
#define PND_NUMBER_TYPE_INFO             0x32
#define PND_IMAGE_ID_FIELD               0x33
#define PND_POC_GROUP_NICKNAME           0x34
#define PND_POC_GROUP_PASSWORD           0x35
#define PND_POC_GROUP_DOMAIN             0x36
#define PND_RING_TONE_SOURCE_ID_FIELD    0x37
#define PND_IMPS_ID_FIELD                0x38
#define PND_NICKNAME_FIELD               0x39
#define PND_PS_DYNAMIC_FIELD             0x3a
#define PND_IM_DYNAMIC_FIELD             0x3b
#define PND_REF_IMLIST_FIELD             0x3c
#define PND_REF_PSLIST_FIELD             0x3d
#define PND_READING_FIELD                0x3e
#define PND_SIP_ADDRESS_FIELD            0x3f
#define PND_POC_GROUP_STATUS_FIELD       0x40
#define PND_POC_GROUP_FLAGS_FIELD        0x41
#define PND_PTT_LOGIN_STATUS_FIELD       0x42
#define PND_REF_SUPERGROUP_FIELD         0x43
#define PND_CALL_DURATION_FIELD          0x44
#define PND_VIDEO_TONE_SOURCE_ID_FIELD   0x45
#define PND_FIRST_NAME_FIELD             0x46
#define PND_LAST_NAME_FIELD              0x47
#define PND_FIRST_NAME_READING_FIELD     0x48
#define PND_LAST_NAME_READING_FIELD      0x49
#define PND_ADDRESS_CONTAINER_FIELD      0x4a
#define PND_EXTENDED_ADDRESS_SUBFIELD    0x4b
#define PND_STREET_SUBFIELD              0x4c
#define PND_LOCALITY_SUBFIELD            0x4d
#define PND_REGION_SUBFIELD              0x4e
#define PND_POSTCODE_SUBFIELD            0x4f
#define PND_COUNTRY_SUBFIELD             0x50
#define PND_NAME_DISPLAY_INFO            0x51
#define PND_FORMATTED_NAME_FIELD         0x52

/* Notice: If you add a new subblock id, remember */
/*         to modify PND_LAST_SUBBLOCK_ID below ! */
#define PND_LAST_SUBBLOCK_ID             0x52

/* Other constants */

#define PND_RESERVATION_KEY_NONE         0x0000
#define PND_FIELD_NEW                    0x80
#define PND_LOCATION_ALL                 0xffff
#define PND_LOCATION_ANY                 0xffff
#define PND_LUID_ANY                     0x0000

/* Default values */ /* TODO - Værdierne skal rettes */
#ifndef PND_DEFAULT_NAME_LENGTH
#define PND_DEFAULT_NAME_LENGTH                 60
#endif

#ifndef PND_DEFAULT_NUMBER_LENGTH
#define PND_DEFAULT_NUMBER_LENGTH               40
#endif

#ifndef PND_DEFAULT_TEXT_LENGTH
#define PND_DEFAULT_TEXT_LENGTH                 120
#endif

#ifndef PND_DEFAULT_VMBX_PASSWD_LENGTH
#define PND_DEFAULT_VMBX_PASSWD_LENGTH          4
#endif

#ifndef PND_RECORD_MAX_FIELD_COUNT
#define PND_RECORD_MAX_FIELD_COUNT              10
#endif

#ifndef PND_DEFAULT_CHANGELOG_LENGTH
#define PND_DEFAULT_CHANGELOG_LENGTH            6
#endif

#ifndef PND_DEFAULT_REFERENCE_MASK_LENGTH
#define PND_DEFAULT_REFERENCE_MASK_LENGTH       7
#endif

#ifndef PND_MAX_NUMBER_TYPES_COUNT
#define PND_MAX_NUMBER_TYPES_COUNT              12
#endif

#ifndef PND_READING_FIELD_LENGTH
#define PND_READING_FIELD_LENGTH                60
#endif

#ifndef PND_POC_GROUP_NICKNAME_LENGTH_CNF
#define PND_POC_GROUP_NICKNAME_LENGTH_CNF       60
#endif

#ifndef PND_POC_GROUP_PASSWORD_LENGTH_CNF
#define PND_POC_GROUP_PASSWORD_LENGTH_CNF       11
#endif

#ifndef PND_POC_GROUP_DOMAIN_LENGTH_CNF
#define PND_POC_GROUP_DOMAIN_LENGTH_CNF         60
#endif

#ifndef PND_DEFAULT_DEVICE_ID_LENGTH
#define PND_DEFAULT_DEVICE_ID_LENGTH            13
#endif

#ifndef PND_DEFAULT_CLI_LOGO_WIDTH
#define PND_DEFAULT_CLI_LOGO_WIDTH              14
#endif

#ifndef PND_DEFAULT_CLI_LOGO_HEIGHT
#define PND_DEFAULT_CLI_LOGO_HEIGHT             15
#endif

#ifndef PND_DEFAULT_EXTENDED_ADDRESS_LENGTH
#define PND_DEFAULT_EXTENDED_ADDRESS_LENGTH 50
#endif

#ifndef PND_DEFAULT_STREET_LENGTH
#define PND_DEFAULT_STREET_LENGTH 50
#endif

#ifndef PND_DEFAULT_LOCALITY_LENGTH
#define PND_DEFAULT_LOCALITY_LENGTH 50
#endif

#ifndef PND_DEFAULT_REGION_LENGTH
#define PND_DEFAULT_REGION_LENGTH 50
#endif

#ifndef PND_DEFAULT_POSTCODE_LENGTH
#define PND_DEFAULT_POSTCODE_LENGTH 50
#endif

#ifndef PND_DEFAULT_COUNTRY_LENGTH
#define PND_DEFAULT_COUNTRY_LENGTH 50
#endif

/*  4    MACROS */

#define PND_MSG_HEADER \
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    PND_PFIRST_SUBBLOCK") \
    VALUE (8, BE, TransactionId, "Transaction ID", DEC) \
    REFERENCE (8, BE, MessageId, "Message ID", MSG_ID)

#define PND_SB_HEADER\
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    PND_PNEXT_SUBBLOCK") \
    REFERENCE(8, BE, SubBlockId, "Subblock ID", SB_ID) \
    FILLER_EX(Reserved1, 8, 1) \
    REFERENCE(16, BE, SubBlockLength, "Subblock length", SB_LENGTH)


#define SPEED_DIAL_LOCATION_STAR_KEY 1

/* TODO: Change the version whenever the interface is changed */
/* default ISI version */

#ifndef PND_ISI_VERSION
#define PND_ISI_VERSION
#define PND_ISI_VERSION_Z      5
#define PND_ISI_VERSION_Y      32
#endif


/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                 "R&D Southwood")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                      "ALPHA SCF")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,                "Scott Wilcox")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,           "CONFIDENTIALITY")

/* ISI header properties */
PROPERTY_STRING(PROPERTY_ISIHDR_TITLE,                      "pnd_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                   "pnd_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16,                "")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,       "ou_gif")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,     "global_interface/ISI/IAM")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16,  "")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,    "CM_INSTANCE_NAME")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16, "")

/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                        "ISI Phonebook Server Message Descriptions")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                     "i_pnd_m.html")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,              "-")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB,         "ou_gif")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,       "GIF_SPECS-ou_gif#xxx")
PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH,               "GIF_SPECS/IAM")
PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

RES_BEGIN(RESOURCE_ISI, PN_PHONEBOOK, phonebook, "Phonebook Server", 
    RES_VERSION_STRING(PND_ISI_VERSION_Z, PND_ISI_VERSION_Y), TRUE)

    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "WP-RM SCO 005-4659: Support for video telephony flag")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "fa1iam#20483")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "PROPOSAL")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "18-Apr-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Dom Esplen")
    COMMENT(COMMENT_TEXT, "Correction for PND_CALL_DURATION_FIELD, plus addition of PND_NUMBER_TYPE_VIDEOCALL")
    ISI_VERSION_HISTORY("005.032")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "WP RM SCO 005-4621: Support for Integrated Call List")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "fa1iam#20057")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "PROPOSAL")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "15-Apr-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Andy Taylor")
    COMMENT(COMMENT_TEXT, "Added PND_LOG_MEM_INTEGRATED_CALL_LIST logical memory")
    ISI_VERSION_HISTORY("005.031")
        
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "SWAM Change Request (LT04040747769)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "so_ui#21055")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "PROPOSAL")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "07-Apr-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Andy Taylor")
    COMMENT(COMMENT_TEXT, "Added PND_CAUSE_READING_TOO_LONG.")
    ISI_VERSION_HISTORY("005.013")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change Request (RM_RIM 011-2505)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "so_ui#20785")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "PROPOSAL")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "24-Mar-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Gábor.S Somogyi")
    COMMENT(COMMENT_TEXT, "Added PND_PHONE_NUMBER_SEARCH")
    ISI_VERSION_HISTORY("005.012")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Reason for change...")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Reference...")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "APPROVED")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "DD-MMM-YYYY")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Christian Jacob Hansen")
    COMMENT(COMMENT_TEXT, "First version of the interface")
    ISI_VERSION_HISTORY("005.011")


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


    /* --------------------------------------------------------------------- */
    /* Constants */
    /* --------------------------------------------------------------------- */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_DEFAULT_NAME_LENGTH, PND_DEFAULT_NAME_LENGTH)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_DEFAULT_NUMBER_LENGTH, PND_DEFAULT_NUMBER_LENGTH)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_DEFAULT_TEXT_LENGTH, PND_DEFAULT_TEXT_LENGTH)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_DEFAULT_VMBX_PASSWD_LENGTH, PND_DEFAULT_VMBX_PASSWD_LENGTH)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_RECORD_MAX_FIELD_COUNT, PND_RECORD_MAX_FIELD_COUNT)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_DEFAULT_CHANGELOG_LENGTH, PND_DEFAULT_CHANGELOG_LENGTH)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_DEFAULT_REFERENCE_MASK_LENGTH, PND_DEFAULT_REFERENCE_MASK_LENGTH)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_MAX_NUMBER_TYPES_COUNT, PND_MAX_NUMBER_TYPES_COUNT)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_READING_FIELD_LENGTH, PND_READING_FIELD_LENGTH)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_POC_GROUP_NICKNAME_LENGTH_CNF, PND_POC_GROUP_NICKNAME_LENGTH_CNF)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_POC_GROUP_PASSWORD_LENGTH_CNF, PND_POC_GROUP_PASSWORD_LENGTH_CNF)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_POC_GROUP_DOMAIN_LENGTH_CNF, PND_POC_GROUP_DOMAIN_LENGTH_CNF)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_DEFAULT_DEVICE_ID_LENGTH, PND_DEFAULT_DEVICE_ID_LENGTH)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_DEFAULT_CLI_LOGO_WIDTH, PND_DEFAULT_CLI_LOGO_WIDTH)

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(PND_DEFAULT_CLI_LOGO_HEIGHT, PND_DEFAULT_CLI_LOGO_HEIGHT)

    CONSTANT(PND_VOICETAG_DONT_CARE, 0x00)
    CONSTANT(PND_SMSDL_GROUP_DONT_CARE, 0x00)

    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#ifdef  PND_EXCL_PTRS_FROM_MSG /* Please see 1.3 for information of this flag */")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#define PND_PFIRST_SUBBLOCK")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#define PND_PNEXT_SUBBLOCK")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#define PND_PFIRST_SUBBLOCK tSUB_BLOCK* pFirstSubBlock;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#define PND_PNEXT_SUBBLOCK  tSUB_BLOCK* pNextSubBlock;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef byte tPndFieldUniqueId;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
    CONSTANT(PND_IM_DYN_CONTACT_PERMANENT_MASK, 0x01)
    CONSTANT(PND_IM_DYN_CONTACT_TEMPORARY,      0x00)
    CONSTANT(PND_IM_DYN_CONTACT_GROUP_MASK,     0x02)
    CONSTANT(PND_IM_DYN_CONTACT_PRIVATE_MASK,   0x04)
    CONSTANT(PND_IM_DYN_CONTACT_SINGLE,         0x00)

    /* --------------------------------------------------------------------- */
    /* Symbol tables */
    /* --------------------------------------------------------------------- */


    /* Predefined values for VMBX Location Indexes */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(VMBX_LOCATION_INDEX, 16, BE, "", "")
        CONST_TBL_ENTRY(PND_VMBX_LOCATION_PRIM_LINE, 0x0001, "")
        CONST_TBL_ENTRY(PND_VMBX_LOCATION_ALT_LINE, 0x0002, "")
        CONST_TBL_ENTRY(PND_VMBX_LOCATION_FAX, 0x0003, "")
        CONST_TBL_ENTRY(PND_VMBX_LOCATION_DATA, 0x0004, "")
    CONST_TBL_END


    /* Memory status allocation types */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_MEMORY_STATUS_ALLOCATION_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_MEMORY_ALLOCATION_STATIC,       0x01, "")
        CONST_TBL_ENTRY(PND_MEMORY_ALLOCATION_DYNAMIC,      0x02, "")
    CONST_TBL_END


    /* Logical memories */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_LOGICAL_MEMORIES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_LOG_MEM_LCS,                  0x01, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_MCS,                  0x02, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_RCS,                  0x03, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_PD,                   0x05, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_ADN,                  0x06, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_FDN,                  0x07, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_OWN_NBR,              0x08, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_VMBX,                 0x09, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_SDN,                  0x0c, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_SPEED_DIAL,           0x0e, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_CLI_GRP_LST,          0x10, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_VMBX_SIM,             0x13, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_COMB,                 0x15, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_SMSDL_GROUP_INFO,     0x16, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_OWN_NBR_SIM,          0x17, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_POC_GROUPS,           0x18, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_IM_BLOCKED,           0x19, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_PS_BLOCKED,           0x1a, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_IM_PUBLIC_GROUPS,     0x1b, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_IM_PRIVATE_GROUPS,    0x1c, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_OWN_PRESENCE,         0x1d, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_IM_TEMP,              0x1e, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_WATCHERS,             0x1f, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_IM_ACTIVE_CHAT,       0x20, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_PRIVATE,              0x21, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_IM_CONTACTS,          0x22, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_GROUPS,               0x23, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_COMB_GROUPS,          0x24, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_PD_GROUPS,            0x25, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_ADN_GROUPS,           0x26, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_RUC,                  0x27, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_INTEGRATED_CALL_LIST, 0x28, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_DEFAULT,              0xfe, "")
        CONST_TBL_ENTRY(PND_LOG_MEM_ALL,                  0xff, "")
    CONST_TBL_END


    /* Physical memories */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_PHYSICAL_MEMORIES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_PHYS_MEM_SIM,                   0x01, "")
        CONST_TBL_ENTRY(PND_PHYS_MEM_ME,                    0x02, "")
        CONST_TBL_ENTRY(PND_PHYS_MEM_ANY,                   0xFE, "")
        CONST_TBL_ENTRY(PND_PHYS_MEM_ALL,                   0xFF, "")
    CONST_TBL_END


    /* Read Mode */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    BIT_TBL_BEGIN(PND_READ_MODE, 8, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXX0", PND_PRIMARY_READ_OFF, "")
        BIT_TBL_ENTRY("XXXXXXX1", PND_PRIMARY_READ_ON,  "")
    BIT_TBL_END


    /* Search Modes */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_SEARCH_MODES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_SEARCH_MODE_ABSOLUTE,           0x01, "")
        CONST_TBL_ENTRY(PND_SEARCH_MODE_FIRST,              0x02, "")
        CONST_TBL_ENTRY(PND_SEARCH_MODE_LAST,               0x03, "")
        CONST_TBL_ENTRY(PND_SEARCH_MODE_NEXT,               0x04, "")
        CONST_TBL_ENTRY(PND_SEARCH_MODE_PREV,               0x05, "")
        CONST_TBL_ENTRY(PND_SEARCH_MODE_NEXT_PARTIAL,       0x06, "")
        CONST_TBL_ENTRY(PND_SEARCH_MODE_PREV_PARTIAL,       0x07, "")
    CONST_TBL_END


    /* Primary search keys */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_PRIMARY_SEARCH_KEYS, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_LOCATION,  0x01, "")
        CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_NAME,      0x02, "")
        CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_NUMBER,    0x03, "")
        CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_LUID,      0x06, "")
        CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_BOPOMOFO,  0x07, "")
        CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_STROKE,    0x08, "")
        CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_EMAIL,     0x09, "")
        CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_IMPS_ID,   0x0a, "")
        CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_READING,   0x0b, "")
        CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_SIP,       0x0c, "")
	CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_BUDDY_ID,  0x0d, "")
	CONST_TBL_ENTRY(PND_PRIMARY_SERACH_KEY_IM_PRIORITY,0x0e, "")
	CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_IM_PRIORITY_BOPOMOFO, 0x0f, "")
	CONST_TBL_ENTRY(PND_PRIMARY_SEARCH_KEY_IM_PRIORITY_STROKE, 0x10, "")
    CONST_TBL_END


    /* Number types */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_NUMBER_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_NUMBER_TYPE_STANDARD,   0x01, "")
        CONST_TBL_ENTRY(PND_NUMBER_TYPE_HOME,       0x02, "")
        CONST_TBL_ENTRY(PND_NUMBER_TYPE_MOBILE,     0x03, "")
        CONST_TBL_ENTRY(PND_NUMBER_TYPE_FAX,        0x04, "")
        CONST_TBL_ENTRY(PND_NUMBER_TYPE_CAR,        0x05, "")
        CONST_TBL_ENTRY(PND_NUMBER_TYPE_WORK,       0x06, "")
        CONST_TBL_ENTRY(PND_NUMBER_TYPE_OFFICE,     0x07, "")
        CONST_TBL_ENTRY(PND_NUMBER_TYPE_PAGER,      0x08, "")
        CONST_TBL_ENTRY(PND_NUMBER_TYPE_MODEM,      0x09, "")
        CONST_TBL_ENTRY(PND_NUMBER_TYPE_PHONE,      0x0A, "")
        CONST_TBL_ENTRY(PND_NUMBER_TYPE_POC,        0x0B, "")
        CONST_TBL_ENTRY(PND_NUMBER_TYPE_VIDEOCALL,  0x0C, "")        
    CONST_TBL_END


    /* Field types */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_FIELD_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_BOOL_TYPE,      0x01, "")
        CONST_TBL_ENTRY(PND_BYTE_TYPE,      0x02, "")
        CONST_TBL_ENTRY(PND_WORD_TYPE,      0x03, "")
        CONST_TBL_ENTRY(PND_DWORD_TYPE,     0x04, "")
        CONST_TBL_ENTRY(PND_STRING_TYPE,    0x05, "")
        CONST_TBL_ENTRY(PND_STRUCT_TYPE,    0x06, "")
        CONST_TBL_ENTRY(PND_BINARY_TYPE,    0x07, "")
	CONST_TBL_ENTRY(PND_CONTAINER_TYPE, 0x26, "")
    CONST_TBL_END


    /* Location status information */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_LOCATION_STATUS_INFO, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_LOCATION_EMPTY,     0x01, "")
        CONST_TBL_ENTRY(PND_LOCATION_FULL,      0x02, "")
        CONST_TBL_ENTRY(PND_LOCATION_LOCKED,    0x03, "")
    CONST_TBL_END


    /* Factory Set Levels */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_FACTORY_SET_LEVELS, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_FACTORY_SET_LEVEL_SETTINGS,     0x01, "")
        CONST_TBL_ENTRY(PND_FACTORY_SET_LEVEL_VALUES,       0x02, "")
        CONST_TBL_ENTRY(PND_FACTORY_SET_LEVEL_FULL,         0x03, "")
    CONST_TBL_END


    /* Memory Availability Information */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_MEMORY_AVAILABILITY_INFORMATION, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_MEM_AVAILABLE,                  0x01, "")
        CONST_TBL_ENTRY(PND_MEM_NOT_AVAILABLE,              0x02, "")
    CONST_TBL_END


    /* Recovery Actions */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_RECOVERY_ACTIONS, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_RECOVERY_ACTION_NONE,           0x00, "")
        CONST_TBL_ENTRY(PND_RECOVERY_ACTION_ERASE_ALL,      0x03, "")
        CONST_TBL_ENTRY(PND_RECOVERY_ACTION_COPY_ALL,       0x04, "")
    CONST_TBL_END


    /* Group ID values */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_GROUP_IDS, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_CLI_GROUP_FAMILY,               0x01, "")
        CONST_TBL_ENTRY(PND_CLI_GROUP_VIP,                  0x02, "")
        CONST_TBL_ENTRY(PND_CLI_GROUP_FRIENDS,              0x03, "")
        CONST_TBL_ENTRY(PND_CLI_GROUP_COLLEAGUES,           0x04, "")
        CONST_TBL_ENTRY(PND_CLI_GROUP_OTHER,                0x05, "")
    CONST_TBL_END


    /* Reference memory compare types */
    
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_REFMEM_COMPARE_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_CLIGRP_SEARCH,                0x01, "")
        CONST_TBL_ENTRY(PND_SMSDL_SEARCH,                 0x02, "")
        CONST_TBL_ENTRY(PND_VOICETAG_SEARCH,              0x03, "")
        CONST_TBL_ENTRY(PND_EMAIL_SEARCH,                 0x04, "")
        CONST_TBL_ENTRY(PND_IMLIST_SEARCH,                0x05, "")
        CONST_TBL_ENTRY(PND_PSLIST_SEARCH,                0x06, "")
        CONST_TBL_ENTRY(PND_IMAGE_SEARCH,                 0x07, "")
        CONST_TBL_ENTRY(PND_SIP_ADDR_SEARCH,              0x08, "")

        CONST_TBL_ENTRY_VER(PND_PHONE_NUMBER_SEARCH,      0x09, "005.012", "")
        CONST_TBL_ENTRY_VER(PND_SUPERGROUP_SEARCH,        0x0a, "005.012", "")
        CONST_TBL_ENTRY_VER(PND_EMAIL_AND_NUMBER_SEARCH,  0x0b, "005.012", "")
        CONST_TBL_ENTRY_VER(PND_PTT_LOGIN_STATUS_SEARCH,  0x0c, "005.012", "")
        CONST_TBL_ENTRY_VER(PND_EXTENDED_ADDRESS_SEARCH,  0x0d, "005.012", "")
    CONST_TBL_END


    /* Reference memory compare modes */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_REFMEM_COMPARE_MODES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_NORMAL_SEARCH,                  0x00, "")
        CONST_TBL_ENTRY(PND_NEGATION_SEARCH,                0x01, "")
    CONST_TBL_END


    /* Field group values */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_FIELD_GROUPS, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_FIELD_GROUP_NONE,   0x00, "")
        CONST_TBL_ENTRY(PND_TEXT_FIELD_GROUP,   0x01, "")
    CONST_TBL_END


    /* Fail reasons */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_FAIL_REASON, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_CAUSE_BUSY,                     0x21, "")
        CONST_TBL_ENTRY(PND_CAUSE_UPDATE_IMPOSSIBLE,        0x22, "")
        CONST_TBL_ENTRY(PND_CAUSE_COMMUNICATION_ERROR,      0x23, "")
        CONST_TBL_ENTRY(PND_CAUSE_NO_SIM,                   0x24, "")
        CONST_TBL_ENTRY(PND_CAUSE_NOT_ALLOWED,              0x25, "")
        CONST_TBL_ENTRY(PND_CAUSE_SIM_NOT_READY,            0x26, "")
        CONST_TBL_ENTRY(PND_CAUSE_INIT_NOT_READY,           0x27, "")
        CONST_TBL_ENTRY(PND_CAUSE_INFORMATION_UNKNOWN,      0x28, "")
        CONST_TBL_ENTRY(PND_CAUSE_INVALID_PARAMETER,        0x29, "")
        CONST_TBL_ENTRY(PND_CAUSE_PIN_REQUIRED,             0x2A, "")
        CONST_TBL_ENTRY(PND_CAUSE_PIN2_REQUIRED,            0x2B, "")
        CONST_TBL_ENTRY(PND_CAUSE_PUK_REQUIRED,             0x2C, "")
        CONST_TBL_ENTRY(PND_CAUSE_PUK2_REQUIRED,            0x2D, "")
        CONST_TBL_ENTRY(PND_CAUSE_SECURITY_CODE_REQUIRED,   0x2E, "")
        CONST_TBL_ENTRY(PND_CAUSE_MEMORY_FULL,              0x2F, "")
        CONST_TBL_ENTRY(PND_CAUSE_MEMORY_EMPTY,             0x30, "")
        CONST_TBL_ENTRY(PND_CAUSE_MEMORY_UNKNOWN,           0x31, "")
        CONST_TBL_ENTRY(PND_CAUSE_LOCATION_FULL,            0x32, "")
        CONST_TBL_ENTRY(PND_CAUSE_LOCATION_EMPTY,           0x33, "")
        CONST_TBL_ENTRY(PND_CAUSE_LOCATION_INVALID,         0x34, "")
        CONST_TBL_ENTRY(PND_CAUSE_NAME_ILLEGAL,             0x35, "")
        CONST_TBL_ENTRY(PND_CAUSE_NAME_TOO_LONG,            0x36, "")
        CONST_TBL_ENTRY(PND_CAUSE_NAME_TRUNCATED,           0x37, "")
        CONST_TBL_ENTRY(PND_CAUSE_NUMBER_ILLEGAL,           0x38, "")
        CONST_TBL_ENTRY(PND_CAUSE_NUMBER_TOO_LONG,          0x39, "")
        CONST_TBL_ENTRY(PND_CAUSE_NUMBER_TRUNCATED,         0x3A, "")
        CONST_TBL_ENTRY(PND_CAUSE_ENTRY_NOT_FOUND,          0x3B, "")
        CONST_TBL_ENTRY(PND_CAUSE_FIELD_NOT_FOUND,          0x3C, "")
        CONST_TBL_ENTRY(PND_CAUSE_NOT_SUPPORTED,            0x3D, "")
        CONST_TBL_ENTRY(PND_CAUSE_FIELD_LIMIT_EXCEEDED,     0x3E, "")
        CONST_TBL_ENTRY(PND_CAUSE_LOC_AND_LUID_INCONSISTENT,0x3F, "")
        CONST_TBL_ENTRY(PND_CAUSE_LUID_INVALID,             0x40, "")
        CONST_TBL_ENTRY(PND_CAUSE_CHANGELOG_ERROR,          0x41, "")
        CONST_TBL_ENTRY(PND_CAUSE_INVALID_ICC_REFERENCE,    0x42, "")
        CONST_TBL_ENTRY(PND_CAUSE_NUMBER_RESTRICTED,        0x43, "")

        CONST_TBL_ENTRY_VER(PND_CAUSE_READING_TOO_LONG,     0x44, "005.013", "")
	CONST_TBL_ENTRY(PND_CAUSE_POC_NUMBER_LIMIT_EXCEEDED,0x45,"")
    CONST_TBL_END


    /* Field types */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_FIELD_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_CALL_COUNT_FIELD,               PND_CALL_COUNT_FIELD, "")
        CONST_TBL_ENTRY(PND_CLI_ICON_ENABLE_STATUS_FIELD,   PND_CLI_ICON_ENABLE_STATUS_FIELD, "")
        CONST_TBL_ENTRY(PND_CLI_ICON_FIELD,                 PND_CLI_ICON_FIELD, "")
        CONST_TBL_ENTRY(PND_EMAIL_ADDRESS_FIELD,            PND_EMAIL_ADDRESS_FIELD, "")
        CONST_TBL_ENTRY(PND_FIELD_REFERENCE_FIELD,          PND_FIELD_REFERENCE_FIELD, "")
        CONST_TBL_ENTRY(PND_GROUP_ID_FIELD,                 PND_GROUP_ID_FIELD, "")
        CONST_TBL_ENTRY(PND_NAME_FIELD,                     PND_NAME_FIELD, "")
        CONST_TBL_ENTRY(PND_NOTE_FIELD,                     PND_NOTE_FIELD, "")
        CONST_TBL_ENTRY(PND_ORDER_DATA_FIELD,               PND_ORDER_DATA_FIELD, "")
        CONST_TBL_ENTRY(PND_PHONE_NUMBER_FIELD,             PND_PHONE_NUMBER_FIELD, "")
        CONST_TBL_ENTRY(PND_POST_ADDRESS_FIELD,             PND_POST_ADDRESS_FIELD, "")
        CONST_TBL_ENTRY(PND_RECORD_REFERENCE_FIELD,         PND_RECORD_REFERENCE_FIELD, "")
        CONST_TBL_ENTRY(PND_RING_TONE_ID_FIELD,             PND_RING_TONE_ID_FIELD, "")
        CONST_TBL_ENTRY(PND_TIME_STAMP_FIELD,               PND_TIME_STAMP_FIELD, "")
        CONST_TBL_ENTRY(PND_VM_PASSWORD_FIELD,              PND_VM_PASSWORD_FIELD, "")
        CONST_TBL_ENTRY(PND_WEB_ADDRESS_FIELD,              PND_WEB_ADDRESS_FIELD, "")
        CONST_TBL_ENTRY(PND_PTT_LOGIN_STATUS_FIELD,         PND_PTT_LOGIN_STATUS_FIELD, "")
        CONST_TBL_ENTRY(PND_REF_SUPERGROUP_FIELD,           PND_REF_SUPERGROUP_FIELD, "")
        CONST_TBL_ENTRY(PND_VIDEO_TONE_SOURCE_ID_FIELD,     PND_VIDEO_TONE_SOURCE_ID_FIELD, "")
        CONST_TBL_ENTRY(PND_FIRST_NAME_FIELD,               PND_FIRST_NAME_FIELD, "")
        CONST_TBL_ENTRY(PND_LAST_NAME_FIELD,                PND_LAST_NAME_FIELD, "")
        CONST_TBL_ENTRY(PND_FIRST_NAME_READING_FIELD,       PND_FIRST_NAME_READING_FIELD, "")
        CONST_TBL_ENTRY(PND_LAST_NAME_READING_FIELD,        PND_LAST_NAME_READING_FIELD, "")
        CONST_TBL_ENTRY(PND_ADDRESS_CONTAINER_FIELD,        PND_ADDRESS_CONTAINER_FIELD, "")
        CONST_TBL_ENTRY(PND_FORMATTED_NAME_FIELD,           PND_FORMATTED_NAME_FIELD, "")
    CONST_TBL_END


    /* Change type values */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_CHANGE_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_CLOG_ADD,                       0x01, "")
        CONST_TBL_ENTRY(PND_CLOG_MODIFY,                    0x02, "")
        CONST_TBL_ENTRY(PND_CLOG_DELETE,                    0x03, "")
    CONST_TBL_END


    /* Call Counters Reset Modes */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_CALL_COUNTERS_RESET_MODES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_RESET_CALL_COUNT,               0x01, "")
        CONST_TBL_ENTRY(PND_RESET_NEW_NBR_COUNT,            0x02, "")
        CONST_TBL_ENTRY(PND_RESET_ALL_CALL_CTRS,            0x03, "")
    CONST_TBL_END


    /* Property set values */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_PROPERTY_SET, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_DEFAULT_MEMORY_INFO,            PND_DEFAULT_MEMORY_INFO, "")
        CONST_TBL_ENTRY(PND_LANGUAGE_INFO,                  PND_LANGUAGE_INFO, "")
        CONST_TBL_ENTRY(PND_ALL_PROPERTIES,                 0xFF, "")
    CONST_TBL_END


    /* Reservation type values */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_RESERVATION_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_ACTION_ANY,                     0x00, "")
        CONST_TBL_ENTRY(PND_ACTION_MOVE,                    0x01, "")
    CONST_TBL_END

    /* IM Dynamic States */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_IM_DYNAMIC_STATES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_IM_DYN_STATE_ONLINE_MASK,         0x01, "")
        CONST_TBL_ENTRY(PND_IM_DYN_STATE_NEWINV_MASK,         0x02, "")
        CONST_TBL_ENTRY(PND_IM_DYN_STATE_NEWMSG_MASK,         0x04, "")
        CONST_TBL_ENTRY(PND_IM_DYN_STATE_ACTIVECHAT_MASK,     0x08, "")
        CONST_TBL_ENTRY(PND_IM_DYN_STATE_ALERT_MASK,          0x10, "")
        CONST_TBL_ENTRY(PND_IM_DYN_STATE_NOT_ON_SERVER_MASK,  0x20, "")
        CONST_TBL_ENTRY(PND_IM_DYN_STATE_COMMCAP_MASK,        0x40, "")
        CONST_TBL_ENTRY(PND_IM_DYN_STATE_ONLINESTATUS_MASK,   0x80, "")
    CONST_TBL_END

    /* Dynamic Features */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(PND_DYNAMIC_FEATURES, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_DYN_FEATURE_IM,               0x01, "")
        CONST_TBL_ENTRY(PND_DYN_FEATURE_PS,               0x02, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(PND_IM_DYNAMIC_CONTACTS, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_IM_DYN_CONTACT_PERMANENT,      0x01, "")
        CONST_TBL_ENTRY(PND_IM_DYN_CONTACT_GROUP,          0x02, "")
        CONST_TBL_ENTRY(PND_IM_DYN_CONTACT_PRIVATE,        0x04, "")
        CONST_TBL_ENTRY(PND_IM_DYN_CONTACT_PUBLIC,         0x00, "")
        CONST_TBL_ENTRY(PND_IM_DYN_CONTACT_BLOCKED,        0x08, "")
        CONST_TBL_ENTRY(PND_IM_DYN_CONTACT_JOINED,         0x10, "")
        CONST_TBL_ENTRY(PND_IM_DYN_CONTACT_INVITATION,     0x20, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(PND_PTT_LOGIN_STATUS_CONTENTS, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_PTT_LOGIN_STATUS_NO_SUBSCRIPTION,            0x00, "")
        CONST_TBL_ENTRY(PND_PTT_LOGIN_STATUS_SUBSCRIPTION_NEEDED,        0x01, "")
        CONST_TBL_ENTRY(PND_PTT_LOGIN_STATUS_INFORMATION_NOT_AVAILABLE,  0x02, "")
        CONST_TBL_ENTRY(PND_PTT_LOGIN_STATUS_USER_LOGGED_IN,             0x03, "")
        CONST_TBL_ENTRY(PND_PTT_LOGIN_STATUS_USER_NOT_LOGGED_IN,         0x04, "")
        CONST_TBL_ENTRY(PND_PTT_LOGIN_STATUS_USER_IN_DND,                0x05, "")

        CONST_TBL_ENTRY(PND_CDMA_POC_PS_STATUS_DONOT_DISTURB,            0x06, "")
        CONST_TBL_ENTRY(PND_CDMA_POC_PS_STATUS_UNKNOWN,                  0x07, "")
        CONST_TBL_ENTRY(PND_CDMA_POC_PS_STATUS_NOT_SET,                  0xff, "")		
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Sub block */
    /* --------------------------------------------------------------------- */

    /* PND_REQUEST_FAILED */
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#ifndef PND_EXCL_PTRS_FROM_MSG")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef void tSUB_BLOCK;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef struct ")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte SubBlockId;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    word SubBlockLength;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    } tPbISISubBlockHeader;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    PND_PNEXT_SUBBLOCK")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte SubBlockId;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    word SubBlockLength;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    }tSubBlockHeader;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    PND_PNEXT_SUBBLOCK")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte SubBlockId;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    word SubBlockLength;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tPndFieldUniqueId FieldUniqueId;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    }tPbFieldHeader;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif /* PND_EXCL_PTRS_FROM_MSG */")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_REQUEST_FAILED")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_REQUEST_FAILED, "", "")
        PND_SB_HEADER
        VALUE_CONST(FailReason, "Fail reason", PND_FAIL_REASON)
        FILLER_EX(Reserved2, 8, 3)
    SB_END


    /* PND_MEMORY_STATUS_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MEMORY_STATUS_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_MEMORY_STATUS_INFO, "", "")
        PND_SB_HEADER
        COMMENT(COMMENT_TEXT, "The biggest location index that can be used")
        VALUE(16, BE, MaxNumberOfLocations, "Max number of locations", DEC)
        COMMENT(COMMENT_TEXT, "Number of locations in use")
        VALUE(16, BE, NumberOfUsedLocations, "Number of used locations", DEC)
        COMMENT(COMMENT_TEXT, "Used fration in percentages (100 if memory is full)")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 100)
        VALUE_EX(8, BE, FractionUsed, "Fraction Used", DEC, 1.0, 0.0, "%")
        VALUE_CONST(MemoryAllocationType, "Memory Allocation Type", PND_MEMORY_STATUS_ALLOCATION_TYPES)
        FILLER_EX(Reserved2, 8, 2)
    SB_END


    /* PND_CALL_STACK_INFO */

    DER_CONST_TBL_BEGIN(PND_CALL_STACK_MEM, PND_LOGICAL_MEMORIES, "", "")
        DER_CONST_TBL_ENTRY(PND_LOG_MEM_LCS)
        DER_CONST_TBL_ENTRY(PND_LOG_MEM_MCS)
        DER_CONST_TBL_ENTRY(PND_LOG_MEM_RCS)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CALL_STACK_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_CALL_STACK_INFO, "", "")
        PND_SB_HEADER
        VALUE_CONST(StackId, "Stack ID", PND_CALL_STACK_MEM)
        COMMENT(COMMENT_TEXT, "Number of new numbers in stack")
        VALUE(8, BE, NewNumberCount, "Number of new numbers in stack", DEC)
        COMMENT(COMMENT_TEXT, "Total amount of missed calls (for example)")
        VALUE(8, BE, CallCount, "Call count", DEC)
        COMMENT(COMMENT_TEXT, "Number of locations in use")
        VALUE(8, BE, LocationCount, "Number of used locations", DEC)
        COMMENT(COMMENT_TEXT, "Total amount of locations in the stack")
        VALUE(8, BE, MaxNumberOfLocations, "Number of locations", DEC)
        FILLER_EX(Reserved2, 8, 3)
    SB_END


    /* PND_LOCATION_STATUS_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_LOCATION_STATUS_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_LOCATION_STATUS_INFO, "", "")
        PND_SB_HEADER
        VALUE_CONST(LocationInfo, "Location info", PND_LOCATION_STATUS_INFO)
        FILLER_EX(Reserved2, 8, 3)
    SB_END


    /* PND_MEM_TYPE_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MEM_TYPE_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_MEM_TYPE_INFO, "", "")
        PND_SB_HEADER
        VALUE_CONST(PhysicalMemory, "Physical memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        FILLER_EX(Reserved2, 16, 1)
    SB_END


    /* PND_MEM_TYPE_AVAILABLE_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MEM_TYPE_AVAILABLE_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_MEM_TYPE_AVAILABLE_INFO, "", "")
        PND_SB_HEADER
        VALUE_CONST(PhysicalMemory, "Physical memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        VALUE_CONST(AvailabilityInfo, "Availability info", PND_MEMORY_AVAILABILITY_INFORMATION)
        FILLER_EX(Reserved, 8, 1)
    SB_END


    /* PND_LANGUAGE_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_LANGUAGE_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_LANGUAGE_INFO, "", "")
        PND_SB_HEADER
        VALUE(8, BE, Language, "Language", DEC)
        FILLER_EX(Reserved2, 8, 3)
    SB_END


    /* PND_DEFAULT_MEMORY_INFO */

    DER_CONST_TBL_BEGIN(PND_DEFAULT_MEMORIES, PND_LOGICAL_MEMORIES, "", "")
        DER_CONST_TBL_ENTRY(PND_LOG_MEM_PD)
        DER_CONST_TBL_ENTRY(PND_LOG_MEM_ADN)
        DER_CONST_TBL_ENTRY(PND_LOG_MEM_COMB)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_DEFAULT_MEMORY_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_DEFAULT_MEMORY_INFO, "", "")
        PND_SB_HEADER
        VALUE_CONST(DefaultLogicalMemory, "Default logical memory", PND_DEFAULT_MEMORIES)
        FILLER_EX(Reserved2, 8, 3)
    SB_END


    /* PND_RECORD_REFERENCE_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_RECORD_REFERENCE_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_RECORD_REFERENCE_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE_CONST(PhysicalMemory, "Physical Memory", PND_PHYSICAL_MEMORIES)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LOCATION_ALL)
        VALUE(16, BE, LocationIndex, "Location Index", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LUID_ANY)
        VALUE(32, BE, LUID, "Luid", DEC)
        VALUE_CONST(LogicalMemory, "Logical Memory", PND_LOGICAL_MEMORIES)
        FILLER_EX(Reserved2, 8, 3)
    SB_END


    /* PND_CALL_COUNT_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CALL_COUNT_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_CALL_COUNT_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE(8, BE, MissedCallCount, "Missed call count", DEC)
        FILLER_EX(Reserved2, 8, 2)
    SB_END


    /* PND_CLI_ICON_ENABLE_STATUS_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CLI_ICON_ENABLE_STATUS_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_CLI_ICON_ENABLE_STATUS_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE_CONST(EnableStatus, "Enable Status", ENABLED_DISABLED)
        FILLER_EX(Reserved2, 8, 2)
    SB_END


    /* PND_CLI_ICON_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CLI_ICON_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_CLI_ICON_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE(8, BE, LogoWidth, "Logo width", DEC)
        VALUE(8, BE, LogoHeight, "Logo height", DEC)
        VALUE(8, BE, DetailedInfo, "Detailed info", BIN)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, (PND_DEFAULT_CLI_LOGO_WIDTH*PND_DEFAULT_CLI_LOGO_HEIGHT)/8)
        REFERENCE(16, BE, LogoDataLength, "Logo data length", N)
        SEQ_OF_REF(LogoData, "Logo data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if (((((PND_DEFAULT_CLI_LOGO_WIDTH*PND_DEFAULT_CLI_LOGO_HEIGHT)/8)+10) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-((((PND_DEFAULT_CLI_LOGO_WIDTH*PND_DEFAULT_CLI_LOGO_HEIGHT)/8)+10) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_FIELD_REFERENCE_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIELD_REFERENCE_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_FIELD_REFERENCE_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE_CONST(PhysicalMemory, "Physical Memory", PND_PHYSICAL_MEMORIES)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LOCATION_ALL)
        VALUE(16, BE, LocationIndex, "Location Index", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LUID_ANY)
        VALUE(32, BE, LUID, "Luid", DEC)
        VALUE_CONST(LogicalMemory, "Logical Memory", PND_LOGICAL_MEMORIES)
        VALUE_CONST(FieldType, "Field Type", PND_FIELD_TYPES)
        COMMENT(COMMENT_TEXT, "Unique Field identifier for the referenced field")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, RefFieldUniqueId, "Ref Field unique ID", DEC)
        FILLER_EX(Reserved2, 8, 1)
    SB_END


    /* PND_NAME_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_NAME_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_NAME_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_NAME_LENGTH+1)
        REFERENCE(8, BE, NameLength, "Name length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Name, "Name", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END



    /* PND_FIRST_NAME_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIRST_NAME_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_FIRST_NAME_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_NAME_LENGTH+1)
        REFERENCE(8, BE, FirstNameLength, "First Name length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, FirstName, "First Name", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_LAST_NAME_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_LAST_NAME_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_LAST_NAME_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_NAME_LENGTH+1)
        REFERENCE(8, BE, LastNameLength, "Last Name length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, LastName, "Last Name", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_FIRST_NAME_READING_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIRST_NAME_READING_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_FIRST_NAME_READING_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_NAME_LENGTH+1)
        REFERENCE(8, BE, FirstNameReadingLength, "First Name Reading length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, FirstNameReading, "First Name Reading", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_LAST_NAME_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_LAST_NAME_READING_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_LAST_NAME_READING_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_NAME_LENGTH+1)
        REFERENCE(8, BE, LastNameReadingLength, "Last Name Reading length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, LastNameReading, "Last Name Reading", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END    

    /* PND_PHONE_NUMBER_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_PHONE_NUMBER_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_PHONE_NUMBER_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE_CONST(NumberType, "Number Type", PND_NUMBER_TYPES)
        VALUE(16, BE, VoiceTagID, "Voice Tag ID", DEC)
        VALUE(8, BE, SmsDlGroupID, "SMS DL Group ID", DEC)
        COMMENT(COMMENT_TEXT, "Length of the string including the terminator in bytes")
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_NUMBER_LENGTH+1)
        REFERENCE(8, BE, PhoneNumberLength, "Phone number length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, PhoneNumber, "Phone number", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_NUMBER_LENGTH+1)*2+10) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved3[4-(((PND_DEFAULT_NUMBER_LENGTH+1)*2+10) % 4)]; ")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_RING_TONE_ID_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_RING_TONE_ID_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_RING_TONE_ID_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        FILLER_EX(Reserved2, 8, 1)
        /* Where is the MAX value defined for this ? */
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        VALUE(16, BE, RingToneId, "Ring tone ID", DEC)
    SB_END


    /* PND_GROUP_ID_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_GROUP_ID_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_GROUP_ID_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE_CONST(GroupID, "Group ID", PND_GROUP_IDS)
        VALUE_CONST(CompareMode, "Compare mode", PND_REFMEM_COMPARE_MODES)
        FILLER_EX(Reserved2, 8, 1)
    SB_END


    /* PND_EMAIL_ADDRESS_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_EMAIL_ADDRESS_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_EMAIL_ADDRESS_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_TEXT_LENGTH+1)
        REFERENCE(8, BE, EmailAddressLength, "EMail Address Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, EmailAddress, "EMail address", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_TEXT_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_TEXT_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_POST_ADDRESS_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_POST_ADDRESS_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_POST_ADDRESS_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_TEXT_LENGTH+1)
        REFERENCE(8, BE, PostAddressLength, "Postal address length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, PostAddress, "Postal address", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_TEXT_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_TEXT_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_NOTE_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_NOTE_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_NOTE_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_TEXT_LENGTH+1)
        REFERENCE(8, BE, NoteLength, "Note length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Note, "Note", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_TEXT_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_TEXT_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_WEB_ADDRESS_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_WEB_ADDRESS_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_WEB_ADDRESS_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        COMMENT(COMMENT_TEXT, "Length of the string including the terminator in bytes")
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_TEXT_LENGTH+1)
        REFERENCE(8, BE, WebAddressLength, "Web Address Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, WebAddress, "Web Address String", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_TEXT_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_TEXT_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_VM_PASSWORD_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_VM_PASSWORD_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_VM_PASSWORD_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        COMMENT(COMMENT_TEXT, "Length of the string including the terminator in bytes")
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_VMBX_PASSWD_LENGTH+1)
        REFERENCE(8, BE, PassWordLength, "Password length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        COMMENT(COMMENT_TEXT, "Voice Mailbox Password")
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, PassWord, "Password", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_VMBX_PASSWD_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_VMBX_PASSWD_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_TIME_STAMP_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_TIME_STAMP_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_TIME_STAMP_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        FILLER_EX(Reserved2, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1999)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2098)
        VALUE(16, BE, Year, "Year", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 12)
        VALUE(8, BE, Month, "Month", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 31)
        VALUE(8, BE, Day, "Day", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 23)
        VALUE(8, BE, Hour, "Hour", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 59)
        VALUE(8, BE, Minute, "Minute", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 59)
        VALUE(8, BE, Seconds, "Seconds", DEC)
        COMMENT(COMMENT_TEXT, "Unique Field identifier for the referenced field")
        VALUE(8, BE, RefFieldUniqueId, "Ref Field unique ID", DEC)
        FILLER_EX(Reserved3, 8, 2)
    SB_END
    
    /* PND_CALL_DURATION_FIELD */
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CALL_DURATION_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_CALL_DURATION_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, RefFieldUniqueId, "Ref Field Unique ID", DEC)
        FILLER_EX(Reserved2, 8, 2)        
        VALUE(32, BE, Duration, "Call Duration", DEC)
    SB_END    
    
   /* PND_REF_SUPERGROUP_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_REF_SUPERGROUP_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_REF_SUPERGROUP_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, RefFieldUniqueId, "Ref Field Unique ID", DEC)
        VALUE(16, BE, GroupID, "Group ID", DEC)
    SB_END


    /* PND_FIELD_LIST_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIELD_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(PND_FIELD_INFO, CREATE_STRUCT, "", "")
        VALUE_CONST(FieldName, "Field name", PND_FIELD_TYPES)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, UniqueId, "Field unique ID", DEC)
        FILLER_EX(Reserved2, 8, 2)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIELD_LIST_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_FIELD_LIST_INFO, "", "")
        PND_SB_HEADER
        FILLER_EX(Reserved2, 8, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_RECORD_MAX_FIELD_COUNT)
        REFERENCE(8, BE, FieldCount, "Field count", N)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        SEQ_OF_REF(FieldInfo, "Field info", PND_FIELD_INFO, N, ISIHDR_RESERVE_SPACE)
    SB_END


    /* PND_REFMEM_QUERY_INFO_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_REFMEM_QUERY_INFO_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_REFMEM_QUERY_INFO_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE_CONST(Available, "Available", TRUE_FALSE)
        VALUE(16, BE, ID, "ID", HEX)
    SB_END


    /* PND_DEVICE_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_DEVICE_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_DEVICE_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_DEVICE_ID_LENGTH+1)
        REFERENCE(16, BE, DeviceLength, "Device length", N)
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, Device, "Device", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if (((PND_DEFAULT_DEVICE_ID_LENGTH+1+2) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-((PND_DEFAULT_DEVICE_ID_LENGTH+1+2) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_CHANGELOG_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CHANGELOG_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_CHANGELOG_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_CHANGELOG_LENGTH+1)
        REFERENCE(16, BE, ChangeLogLength, "Change log length", N)
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, ChangeLog, "Change log", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if (((PND_DEFAULT_CHANGELOG_LENGTH+1+2) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-((PND_DEFAULT_CHANGELOG_LENGTH+1+2) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_REF_MASKED_CRITERIA_INFO */

    DER_CONST_TBL_BEGIN(PND_REF_MASKED_CRIT_COMP_TYPES, PND_REFMEM_COMPARE_TYPES, "", "")
        DER_CONST_TBL_ENTRY(PND_SMSDL_SEARCH)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_REF_MASKED_CRITERIA_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_REF_MASKED_CRITERIA_INFO, "", "")
        PND_SB_HEADER
        VALUE_CONST(CompareType, "Compare type", PND_REF_MASKED_CRIT_COMP_TYPES)
        VALUE_CONST(CompareMode, "Compare mode", PND_REFMEM_COMPARE_MODES)
        FILLER_EX(Reserved2, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_REFERENCE_MASK_LENGTH)
        REFERENCE(8, BE, LengthOfMask, "Length of mask", N)
        SEQ_OF_REF(Mask, "Mask", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if((PND_DEFAULT_REFERENCE_MASK_LENGTH % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved3[4-(PND_DEFAULT_REFERENCE_MASK_LENGTH % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_REF_VALUE_CRITERIA_INFO */

    DER_CONST_TBL_BEGIN(PND_REF_VALUE_CRIT_COMP_TYPES, PND_REFMEM_COMPARE_TYPES, "", "")
        DER_CONST_TBL_ENTRY(PND_CLIGRP_SEARCH)
        DER_CONST_TBL_ENTRY(PND_VOICETAG_SEARCH)
        DER_CONST_TBL_ENTRY(PND_EMAIL_SEARCH)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_REF_VALUE_CRITERIA_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_REF_VALUE_CRITERIA_INFO, "", "")
        PND_SB_HEADER
        VALUE_CONST(CompareType, "Compare type", PND_REF_VALUE_CRIT_COMP_TYPES)
        VALUE_CONST(CompareMode, "Compare mode", PND_REFMEM_COMPARE_MODES)
        FILLER_EX(Reserved2, 8, 2)
        VALUE(32, BE, Value, "Value", DEC)
    SB_END


    /* PND_ORDER_DATA_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_ORDER_DATA_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_ORDER_DATA_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        COMMENT(COMMENT_TEXT, "Order value for the reference memory record")
        VALUE(8, BE, Value, "Value", DEC)
        FILLER_EX(Reserved2, 8, 1)
        FILLER_EX(Reserved3, 8, 1)
    SB_END


    /* PND_FIELD_DESCRIPTOR_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIELD_DESCRIPTOR_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_FIELD_DESCRIPTOR_INFO, "", "")
        PND_SB_HEADER
        COMMENT(COMMENT_TEXT, "Field Sub Block ID")
        VALUE_CONST(FieldName, "Field name", PND_FIELD_TYPES)
        VALUE_CONST(FieldPrimType, "Field primitive type", PND_FIELD_TYPE)
        COMMENT(COMMENT_TEXT, "Maximum allowed field length in bytes")
        VALUE(16, BE, MaxFieldLength, "Max Field Length", DEC)
        COMMENT(COMMENT_TEXT, "1 - primary field")
        COMMENT(COMMENT_TEXT, "0 - additional field")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        VALUE(8, BE, FieldPriority, "Field priority", DEC)
        COMMENT(COMMENT_TEXT, "Max. number of fields with the Field Name in the reco"
                "iCOMMENT_TEXT, f Field Group is PND_FIELD_GROUP_NONE.")
        COMMENT(COMMENT_TEXT, "Max. number of fields beloging to this Field Group in the reco"
                "iCOMMENT_TEXT, f Field Group is not PND_FIELD_GROUP_NONE.")
                VALUE(8, BE, MaxFieldsNumber, "Max fields count", DEC)
        COMMENT(COMMENT_TEXT, "Field Group where the field with this Field Name belon"
                "If PND_FIELD_GROUP_NONE, then field doesn't belong to any Field Groups")
        VALUE_CONST(FieldGroup, "Field group", PND_FIELD_GROUPS)
        FILLER_EX(Reserved2, 8, 1)
    SB_END


    /* PND_MATCHED_FIELD_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MATCHED_FIELD_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_MATCHED_FIELD_INFO, "", "")
        PND_SB_HEADER
        COMMENT(COMMENT_TEXT, "Field ID of matched field")
        VALUE_CONST(MatchedFieldID, "Field subblock ID", PND_FIELD_TYPES)
        COMMENT(COMMENT_TEXT, "Unique Field ID of matched field")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, MatchedUnicID, "Field unique ID", DEC)
        COMMENT(COMMENT_TEXT, "Unique reference of matched item. Used to continue traversing")
        VALUE(16, BE, UnicRefID, "Unique match ID", DEC)
    SB_END


    /* PND_REF_SMSDL_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_REF_SMSDL_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_REF_SMSDL_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        COMMENT(COMMENT_TEXT, "Reference ID pointing to another field within same record")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, RefFieldUniqueId, "Reference Field unique ID", DEC)
        FILLER_EX(Reserved2, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_REFERENCE_MASK_LENGTH)
        REFERENCE(8, BE, LengthOfID, "Length of mask", N)
        SEQ_OF_REF(SmsDlGroupID, "SMSDL group ID", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if((PND_DEFAULT_REFERENCE_MASK_LENGTH % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved3[4-(PND_DEFAULT_REFERENCE_MASK_LENGTH % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_REF_VOICETAG_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_REF_VOICETAG_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_REF_VOICETAG_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        COMMENT(COMMENT_TEXT, "Reference ID pointing to another field within same record")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, RefFieldUniqueId, "Reference Field unique ID", DEC)
        VALUE(16, BE, VoiceTagID, "Voicetag ID", HEX)
    SB_END
       

    /* PND_RESERVATION_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_RESERVATION_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_RESERVATION_INFO, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_RESERVATION_KEY_NONE)
        VALUE(16, BE, ReservationKey, "Reservation key", HEX)
        VALUE_CONST(ReservationType, "Reservation type", PND_RESERVATION_TYPES)
        FILLER_EX(Reserved2, 8, 1)
    SB_END


    /* PND_NUMBER_TYPE_INFO */

    SEQ_BEGIN(PND_NUMBER, DONT_CREATE_STRUCT, "", "")
    VALUE_CONST(number, "Number", PND_NUMBER_TYPES)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_NUMBER_TYPE_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_NUMBER_TYPE_INFO, "", "")
        PND_SB_HEADER
        COMMENT(COMMENT_TEXT, "Length of NumberTypes in bytes")
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_MAX_NUMBER_TYPES_COUNT)
        REFERENCE(8, BE, NumberTypeCount, "Number type count", N)
        COMMENT(COMMENT_TEXT, "Supported phone number types")
        SEQ_OF_REF(NumberTypes, "NumberTypes", PND_NUMBER, N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if (((PND_MAX_NUMBER_TYPES_COUNT+1) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-((PND_MAX_NUMBER_TYPES_COUNT+1) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END



    /* PND_READING_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_READING_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_READING_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_READING_FIELD_LENGTH+1)
        REFERENCE(8, BE, ReadingLength, "Reading Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE, BE, Reading, "Reading", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_READING_FIELD_LENGTH+1)*2+2) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_READING_FIELD_LENGTH+1)*2+2) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_RING_TONE_SOURCE_ID_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_RING_TONE_SOURCE_ID_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_RING_TONE_SOURCE_ID_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        FILLER_EX(Reserved2, 8, 3)
        VALUE(32, BE, Instance, "Instance", DEC)
        VALUE(32, BE, Category, "Category", DEC)
    SB_END


    /* PND_IMAGE_ID_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_IMAGE_ID_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_IMAGE_ID_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        FILLER_EX(Reserved2, 8, 3)
        VALUE(32, BE, Instance, "Instance", DEC)
        VALUE(32, BE, Category, "Category", DEC)
    SB_END


    /* PND_IMPS_ID_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_IMPS_ID_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_IMPS_ID_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_TEXT_LENGTH+1)
        REFERENCE(8, BE, IMPSIdLength, "IMPS ID Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE, BE, IMPSId, "IMPS ID", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_TEXT_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_TEXT_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_NICKNAME_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_NICKNAME_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_NICKNAME_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_NAME_LENGTH+1)
        REFERENCE(8, BE, NicknameLength, "Nickname Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE, BE, Nickname, "Nickname", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_PS_DYNAMIC_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_PS_DYNAMIC_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_PS_DYNAMIC_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE(8, BE, PresenceStatus, "Presence Status", DEC)
        VALUE(8, BE, PublishingLevel, "Publishing Level", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_TEXT_LENGTH+1)
        REFERENCE(8, BE, StatusMessageLength, "Status Message Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        VALUE(32, BE, Instance, "Instance", DEC)
        VALUE(32, BE, Category, "Category", DEC)
        STRING_REF(STRING_UNICODE, BE, StatusMessage, "Status Message", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_NAME_LENGTH+1)*2+16) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_NAME_LENGTH+1)*2+16) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_IM_DYNAMIC_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_IM_DYNAMIC_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_IM_DYNAMIC_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE_CONST(IMDynState, "IM Dynamic State", PND_IM_DYNAMIC_STATES)
        VALUE_CONST(IMDynContact, "IM Dynamic Contact", PND_IM_DYNAMIC_CONTACTS)
        FILLER_EX(Reserved, 8, 1)
    SB_END


    /* PND_REF_IMLIST_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_REF_IMLIST_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_REF_IMLIST_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, RefFieldUniqueId, "Reference Field Unique ID", DEC)
        FILLER_EX(Reserved2, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_REFERENCE_MASK_LENGTH)
        REFERENCE(8, BE, LengthOfID, "Length Of Mask", N)
        SEQ_OF_REF(IMListId, "PS List ID", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if((PND_DEFAULT_REFERENCE_MASK_LENGTH % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved3[4-(PND_DEFAULT_REFERENCE_MASK_LENGTH % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_REF_PSLIST_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_REF_PSLIST_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_REF_PSLIST_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, RefFieldUniqueId, "Reference Field Unique ID", DEC)
        FILLER_EX(Reserved2, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_REFERENCE_MASK_LENGTH)
        REFERENCE(8, BE, LengthOfID, "Length Of Mask", N)
        SEQ_OF_REF(PSListId, "PS List ID", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if((PND_DEFAULT_REFERENCE_MASK_LENGTH % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved3[4-(PND_DEFAULT_REFERENCE_MASK_LENGTH % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_POC_GROUP_NICKNAME */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_POC_GROUP_NICKNAME")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_POC_GROUP_NICKNAME, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_POC_GROUP_NICKNAME_LENGTH_CNF+1)
        REFERENCE(8, BE, NameLength, "Poc Group Nickname Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        SEQ_OF_REF(Name, "Poc Group Nickname", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_POC_GROUP_NICKNAME_LENGTH_CNF+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_POC_GROUP_NICKNAME_LENGTH_CNF+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_POC_GROUP_PASSWORD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_POC_GROUP_PASSWORD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_POC_GROUP_PASSWORD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_POC_GROUP_PASSWORD_LENGTH_CNF+1)
        REFERENCE(8, BE, NameLength, "Poc Group Nickname Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        SEQ_OF_REF(Name, "Poc Group Nickname", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_POC_GROUP_PASSWORD_LENGTH_CNF+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_POC_GROUP_PASSWORD_LENGTH_CNF+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_POC_GROUP_DOMAIN */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_POC_GROUP_DOMAIN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_POC_GROUP_DOMAIN, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_POC_GROUP_DOMAIN_LENGTH_CNF+1+1)
        REFERENCE(8, BE, NameLength, "Poc Group Domain Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        SEQ_OF_REF(Name, "Poc Group Nickname", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_POC_GROUP_DOMAIN_LENGTH_CNF+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_POC_GROUP_DOMAIN_LENGTH_CNF+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_SIP_ADDRESS_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_SIP_ADDRESS_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_SIP_ADDRESS_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_TEXT_LENGTH+1)
        REFERENCE(8, BE, SIPAddressLength, "SIP Address Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        SEQ_OF_REF(Name, "SIP address", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_TEXT_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_TEXT_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* PND_POC_GROUP_STATUS_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_POC_GROUP_STATUS_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_POC_GROUP_STATUS_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE(8, BE, GroupStatus, "PoC Group Status", DEC)
        FILLER_EX(Reserved2, 8, 2)
    SB_END


    /* PND_POC_GROUP_FLAGS_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_POC_GROUP_FLAGS_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_POC_GROUP_FLAGS_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        FILLER_EX(Reserved2, 8, 3)
        VALUE(32, BE, GroupStatus, "PoC Group Status", DEC)
    SB_END

    /* PND_PTT_LOGIN_STATUS_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_PTT_LOGIN_STATUS_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_PTT_LOGIN_STATUS_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE_CONST(loginStatus, "Login Status", PND_PTT_LOGIN_STATUS_CONTENTS)
        VALUE(16, BE, buddyId, "Buddy ID", DEC)
    SB_END

    /* PND_VIDEO_TONE_SOURCE_ID_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_VIDEO_TONE_SOURCE_ID_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_VIDEO_TONE_SOURCE_ID_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        FILLER_EX(Reserved2, 8, 3)
        VALUE(32, BE, Instance, "Instance", DEC)
        VALUE(32, BE, Category, "Category", DEC)
    SB_END

    /* PND_FORMATTED_NAME_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FORMATTED_NAME_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_FORMATTED_NAME_FIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_NAME_LENGTH+1)
        REFERENCE(8, BE, FormattedNameLength, "Name length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, FormattedName, "Name", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_NAME_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END
  

    /* PND_EXTENDED_ADDRESS_SUBFIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_EXTENDED_ADDRESS_SUBFIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_EXTENDED_ADDRESS_SUBFIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_EXTENDED_ADDRESS_LENGTH+1)
        REFERENCE(8, BE, ExtendedAddressLength, "Extended Address Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, ExtendedAddress, "Extended Address", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_EXTENDED_ADDRESS_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_EXTENDED_ADDRESS_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END
    

    /* PND_STREET_SUBFIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_STREET_SUBFIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_STREET_SUBFIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_STREET_LENGTH+1)
        REFERENCE(8, BE, StreetLength, "Street Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Street, "Street", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_STEET_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_STEET_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END    
    
    /* PND_LOCALITY_SUBFIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_LOCALITY_SUBFIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_LOCALITY_SUBFIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_LOCALITY_LENGTH+1)
        REFERENCE(8, BE, LocalityLength, "Locality Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Locality, "Locality", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_LOCALITY_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_LOCALITY_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END       
    
    /* PND_REGION_SUBFIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_REGION_SUBFIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_REGION_SUBFIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_REGION_LENGTH+1)
        REFERENCE(8, BE, RegionLength, "Region Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Region, "Region", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_REGION_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_REGION_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END       
    
    /* PND_POSTCODE_SUBFIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_POSTCODE_SUBFIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_POSTCODE_SUBFIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_POSTCODE_LENGTH+1)
        REFERENCE(8, BE, PostcodeLength, "Postcode Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Postcode, "Postcode", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_POSTCODE_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_POSTCODE_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END  

    /* PND_COUNTRY_SUBFIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_COUNTRY_SUBFIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(PND_COUNTRY_SUBFIELD, "", "")
        PND_SB_HEADER
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, PND_DEFAULT_COUNTRY_LENGTH+1)
        REFERENCE(8, BE, CountryLength, "Country Length", NSIZE)
        REFERENCE_TRANSFORM(NSIZE, N, ALG_DIV, 2)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Country, "Country", N, ISIHDR_RESERVE_SPACE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if ((((PND_DEFAULT_COUNTRY_LENGTH+1)*2+6) % 4) != 0)")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    byte Reserved2[4-(((PND_DEFAULT_COUNTRY_LENGTH+1)*2+6) % 4)];")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")
        FILLER(FILLER_VARIABLE, 32)
    SB_END      
 
    
    /* PND_ADDRESS_CONTAINER_FIELD */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_ADDRESS_CONTAINER_FIELD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY(PROPERTY_SB_LENGTH_MISSING)    
    SB_BEGIN(PND_ADDRESS_CONTAINER_FIELD, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    PND_PNEXT_SUBBLOCK") 
        REFERENCE(8, BE, SubBlockId, "Subblock ID", SB_ID) 
        FILLER_EX(Reserved1, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, 8)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "SubBlockLength")
        VALUE(16, BE, SubBlockLength, "Subblock length", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_FIELD_NEW)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        VALUE_CONST(AddressType, "Address Type", PND_NUMBER_TYPES)
        FILLER_EX(Reserved2, 8, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    PND_PFIRST_SUBBLOCK")
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_EXTENDED_ADDRESS_SUBFIELD)
            SB_LST_ENTRY(PND_STREET_SUBFIELD)
            SB_LST_ENTRY(PND_LOCALITY_SUBFIELD)
            SB_LST_ENTRY(PND_REGION_SUBFIELD)
            SB_LST_ENTRY(PND_POSTCODE_SUBFIELD)
            SB_LST_ENTRY(PND_COUNTRY_SUBFIELD)	
        SB_LST_REF_END
    SB_END  

    /* PND_RECORD_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_RECORD_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY(PROPERTY_SB_LENGTH_MISSING)
    SB_BEGIN(PND_RECORD_INFO, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    PND_PNEXT_SUBBLOCK") 
        REFERENCE(8, BE, SubBlockId, "Subblock ID", SB_ID) 
        FILLER_EX(Reserved1, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, 16)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "SubBlockLength")
        VALUE(16, BE, SubBlockLength, "Subblock length", DEC)
        VALUE_CONST(PhysicalMemory, "Physical Memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical Memory", PND_LOGICAL_MEMORIES)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LOCATION_ANY)
        VALUE(16, BE, LocationIndex, "Location Index", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LUID_ANY)
        VALUE(32, BE, LUID, "Luid", DEC)
        FILLER_EX(Reserved2, 8, 3)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    PND_PFIRST_SUBBLOCK")
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_CALL_COUNT_FIELD)
            SB_LST_ENTRY(PND_CLI_ICON_ENABLE_STATUS_FIELD)
            SB_LST_ENTRY(PND_CLI_ICON_FIELD)
            SB_LST_ENTRY(PND_EMAIL_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_FIELD_LIST_INFO)
            SB_LST_ENTRY(PND_FIELD_REFERENCE_FIELD)
            SB_LST_ENTRY(PND_GROUP_ID_FIELD)
            SB_LST_ENTRY(PND_MATCHED_FIELD_INFO)
            SB_LST_ENTRY(PND_NAME_FIELD)
            SB_LST_ENTRY(PND_READING_FIELD)	
            SB_LST_ENTRY(PND_NOTE_FIELD)
            SB_LST_ENTRY(PND_ORDER_DATA_FIELD)
            SB_LST_ENTRY(PND_PHONE_NUMBER_FIELD)
            SB_LST_ENTRY(PND_POST_ADDRESS_FIELD)
/*            SB_LST_ENTRY(PND_RECORD_REFERENCE_FIELD) */
            SB_LST_ENTRY(PND_REF_SMSDL_FIELD)
            SB_LST_ENTRY(PND_REF_VOICETAG_FIELD)
            SB_LST_ENTRY(PND_RING_TONE_ID_FIELD)
            SB_LST_ENTRY(PND_TIME_STAMP_FIELD)
            SB_LST_ENTRY(PND_VM_PASSWORD_FIELD)
            SB_LST_ENTRY(PND_WEB_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_IMAGE_ID_FIELD)
            SB_LST_ENTRY(PND_IMPS_ID_FIELD)
            SB_LST_ENTRY(PND_NICKNAME_FIELD)
            SB_LST_ENTRY(PND_PS_DYNAMIC_FIELD)
            SB_LST_ENTRY(PND_IM_DYNAMIC_FIELD)
            SB_LST_ENTRY(PND_REF_IMLIST_FIELD)
            SB_LST_ENTRY(PND_REF_PSLIST_FIELD)
            SB_LST_ENTRY(PND_POC_GROUP_NICKNAME)
            SB_LST_ENTRY(PND_POC_GROUP_DOMAIN)
            SB_LST_ENTRY(PND_SIP_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_POC_GROUP_STATUS_FIELD)
            SB_LST_ENTRY(PND_POC_GROUP_FLAGS_FIELD)
            SB_LST_ENTRY(PND_PTT_LOGIN_STATUS_FIELD)			
            SB_LST_ENTRY(PND_REF_SUPERGROUP_FIELD)
            SB_LST_ENTRY(PND_VIDEO_TONE_SOURCE_ID_FIELD)
            SB_LST_ENTRY(PND_FIRST_NAME_FIELD)			
            SB_LST_ENTRY(PND_LAST_NAME_FIELD)				
            SB_LST_ENTRY(PND_FIRST_NAME_READING_FIELD)			
            SB_LST_ENTRY(PND_LAST_NAME_READING_FIELD)	
            SB_LST_ENTRY(PND_ADDRESS_CONTAINER_FIELD)	
            SB_LST_ENTRY(PND_FORMATTED_NAME_FIELD)
        SB_LST_REF_END
    SB_END 
    
    /* --------------------------------------------------------------------- */
    /* Messages */
    /* --------------------------------------------------------------------- */

    /* PND_FACTORY_SET */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FACTORY_SET_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_FACTORY_SET_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(FactorySetLevel, "Factory set level", PND_FACTORY_SET_LEVELS)
        FILLER_EX(Reserved, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FACTORY_SET_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_FACTORY_SET_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_FACTORY_SET_REQ, PND_FACTORY_SET_RESP)


    /* PND_PROPERTY_SET */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_PROPERTY_SET_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_PROPERTY_SET_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_LANGUAGE_INFO)
            SB_LST_ENTRY(PND_DEFAULT_MEMORY_INFO)
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_PROPERTY_SET_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_PROPERTY_SET_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_REQUEST_FAILED)        
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_PROPERTY_SET_REQ, PND_PROPERTY_SET_RESP)


    /* PND_PROPERTY_GET */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_PROPERTY_GET_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_PROPERTY_GET_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(PropertyID, "Property ID", PND_PROPERTY_SET)
        FILLER_EX(Reserved, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_PROPERTY_GET_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_PROPERTY_GET_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_LANGUAGE_INFO)
            SB_LST_ENTRY(PND_DEFAULT_MEMORY_INFO)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_PROPERTY_GET_REQ, PND_PROPERTY_GET_RESP)


    /* PND_RESET_CALL_CTRS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_RESET_CALL_CTRS_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_RESET_CALL_CTRS_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(Mode, "Mode", PND_CALL_COUNTERS_RESET_MODES)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_MEM_TYPE_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_RESET_CALL_CTRS_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_RESET_CALL_CTRS_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_RESET_CALL_CTRS_REQ, PND_RESET_CALL_CTRS_RESP)


    /* PND_MEMORY_TYPE_LIST */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MEMORY_TYPE_LIST_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_MEMORY_TYPE_LIST_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 5)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_MEM_TYPE_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MEMORY_TYPE_LIST_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_MEMORY_TYPE_LIST_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_MEM_TYPE_AVAILABLE_INFO)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_MEMORY_TYPE_LIST_REQ, PND_MEMORY_TYPE_LIST_RESP)


    /* PND_MEMORY_STATUS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MEMORY_STATUS_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_MEMORY_STATUS_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        COMMENT(COMMENT_TEXT, "DRAFT - DO NOT USE!")
        VALUE_CONST(PhysicalMemory, "Physical memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        FILLER_EX(Reserved, 8, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MEMORY_STATUS_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_MEMORY_STATUS_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        COMMENT(COMMENT_TEXT, "DRAFT - DO NOT USE!")
        VALUE_CONST(PhysicalMemory, "Physical memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LUID_ANY)
        VALUE(32, BE, LastLUID, "Last used LUID", DEC)
        FILLER_EX(Reserved, 8, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_MEMORY_STATUS_INFO)
            SB_LST_ENTRY(PND_CALL_STACK_INFO)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_MEMORY_STATUS_REQ, PND_MEMORY_STATUS_RESP)


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIELD_DESCRIPTORS_GET_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_FIELD_DESCRIPTORS_GET_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        FILLER_EX(Reserved, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIELD_DESCRIPTORS_GET_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_FIELD_DESCRIPTORS_GET_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_FIELD_DESCRIPTOR_INFO)
            SB_LST_ENTRY(PND_NUMBER_TYPE_INFO)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_FIELD_DESCRIPTORS_GET_REQ, PND_FIELD_DESCRIPTORS_GET_RESP)


    /* PND_MEMORY_RESERVE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MEMORY_RESERVE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_MEMORY_RESERVE_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        COMMENT(COMMENT_TEXT, "DRAFT - DO NOT USE!")
        VALUE_CONST(PhysicalMemory, "Physical memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        FILLER_EX(Reserved, 8, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MEMORY_RESERVE_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_MEMORY_RESERVE_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_MEMORY_RESERVE_REQ, PND_MEMORY_RESERVE_RESP)


    /* PND_MEMORY_RELEASE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MEMORY_RELEASE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_MEMORY_RELEASE_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        COMMENT(COMMENT_TEXT, "DRAFT - DO NOT USE!")
        VALUE_CONST(PhysicalMemory, "Physical memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        FILLER_EX(Reserved, 8, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MEMORY_RELEASE_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_MEMORY_RELEASE_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_MEMORY_RELEASE_REQ, PND_MEMORY_RELEASE_RESP)


    /* PND_READ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_READ_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_READ_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(SearchMode, "Search mode", PND_SEARCH_MODES)
        VALUE_CONST(PrimarySearchKey, "Primary search key", PND_PRIMARY_SEARCH_KEYS)
        VALUE_CONST(ReadMode, "Read Mode", PND_READ_MODE)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 5)
        VALUE(8, BE, AmountOfRecords, "Amount of records to be recalled", DEC)
        COMMENT(COMMENT_TEXT, "DRAFT - DO NOT USE!")
        VALUE_CONST(PhysicalMemory, "Physical memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LUID_ANY)
        VALUE(32, BE, LUID, "Luid", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LOCATION_ANY)
        VALUE(16, BE, LocationIndex, "Location index", DEC)
        FILLER_EX(Reserved, 8, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_CALL_COUNT_FIELD)
            SB_LST_ENTRY(PND_CLI_ICON_ENABLE_STATUS_FIELD)
            SB_LST_ENTRY(PND_CLI_ICON_FIELD)
            SB_LST_ENTRY(PND_EMAIL_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_FIELD_REFERENCE_FIELD)
            SB_LST_ENTRY(PND_GROUP_ID_FIELD)
            SB_LST_ENTRY(PND_NAME_FIELD)
            SB_LST_ENTRY(PND_READING_FIELD)
            SB_LST_ENTRY(PND_NOTE_FIELD)
            SB_LST_ENTRY(PND_ORDER_DATA_FIELD)
            SB_LST_ENTRY(PND_PHONE_NUMBER_FIELD)
            SB_LST_ENTRY(PND_POST_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_REF_SMSDL_FIELD)
            SB_LST_ENTRY(PND_REF_VOICETAG_FIELD)
            SB_LST_ENTRY(PND_RING_TONE_ID_FIELD)
            SB_LST_ENTRY(PND_RING_TONE_SOURCE_ID_FIELD)
            SB_LST_ENTRY(PND_TIME_STAMP_FIELD)
            SB_LST_ENTRY(PND_VM_PASSWORD_FIELD)
            SB_LST_ENTRY(PND_WEB_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_IMAGE_ID_FIELD)
            SB_LST_ENTRY(PND_IMPS_ID_FIELD)
            SB_LST_ENTRY(PND_NICKNAME_FIELD)
            SB_LST_ENTRY(PND_PS_DYNAMIC_FIELD)
            SB_LST_ENTRY(PND_IM_DYNAMIC_FIELD)
            SB_LST_ENTRY(PND_REF_IMLIST_FIELD)
            SB_LST_ENTRY(PND_REF_PSLIST_FIELD)
            SB_LST_ENTRY(PND_POC_GROUP_NICKNAME)
            SB_LST_ENTRY(PND_POC_GROUP_PASSWORD)
            SB_LST_ENTRY(PND_POC_GROUP_DOMAIN)
            SB_LST_ENTRY(PND_SIP_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_POC_GROUP_STATUS_FIELD)
            SB_LST_ENTRY(PND_POC_GROUP_FLAGS_FIELD)
            SB_LST_ENTRY(PND_SIP_ADDRESS_FIELD)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_READ_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_READ_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 5)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_RECORD_INFO)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_READ_REQ, PND_READ_RESP)


    /* PND_WRITE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_WRITE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_WRITE_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_RECORD_INFO)       
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_WRITE_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_WRITE_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_RECORD_REFERENCE_FIELD)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_WRITE_REQ, PND_WRITE_RESP)


    /* PND_ERASE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_ERASE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_ERASE_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_RECORD_REFERENCE_FIELD)
            SB_LST_ENTRY(PND_REF_VALUE_CRITERIA_INFO)
            SB_LST_ENTRY(PND_REF_MASKED_CRITERIA_INFO)
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_ERASE_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_ERASE_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_ERASE_REQ, PND_ERASE_RESP)


    /* PND_LOCATION_CHECK */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_LOCATION_CHECK_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_LOCATION_CHECK_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_RECORD_REFERENCE_FIELD)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_LOCATION_CHECK_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_LOCATION_CHECK_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_LOCATION_STATUS_INFO)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_LOCATION_CHECK_REQ, PND_LOCATION_CHECK_RESP)

   
    /* PND_EMPTY_LOCATION */

    DER_CONST_TBL_BEGIN(PND_SEARCH_MODES_EMPTY_LOC, PND_SEARCH_MODES, "", "")
        DER_CONST_TBL_ENTRY(PND_SEARCH_MODE_ABSOLUTE)
        DER_CONST_TBL_ENTRY(PND_SEARCH_MODE_FIRST)
        DER_CONST_TBL_ENTRY(PND_SEARCH_MODE_LAST)
        DER_CONST_TBL_ENTRY(PND_SEARCH_MODE_NEXT)
        DER_CONST_TBL_ENTRY(PND_SEARCH_MODE_PREV)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_EMPTY_LOCATION_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_EMPTY_LOCATION_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(SearchMode, "Search mode", PND_SEARCH_MODES_EMPTY_LOC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_RECORD_REFERENCE_FIELD)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_EMPTY_LOCATION_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_EMPTY_LOCATION_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_RECORD_REFERENCE_FIELD)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_EMPTY_LOCATION_REQ, PND_EMPTY_LOCATION_RESP)


    /* PND_FIELD_READ */

    DER_CONST_TBL_BEGIN(PND_FIELD_READ_FIELDS, PND_FIELD_TYPES, "", "")
        DER_CONST_TBL_ENTRY(PND_CLI_ICON_ENABLE_STATUS_FIELD)
        DER_CONST_TBL_ENTRY(PND_CLI_ICON_FIELD)
        DER_CONST_TBL_ENTRY(PND_EMAIL_ADDRESS_FIELD)
        DER_CONST_TBL_ENTRY(PND_FIELD_REFERENCE_FIELD)
        DER_CONST_TBL_ENTRY(PND_GROUP_ID_FIELD)
        DER_CONST_TBL_ENTRY(PND_NAME_FIELD)
        DER_CONST_TBL_ENTRY(PND_NOTE_FIELD)
        DER_CONST_TBL_ENTRY(PND_ORDER_DATA_FIELD)
        DER_CONST_TBL_ENTRY(PND_PHONE_NUMBER_FIELD)
        DER_CONST_TBL_ENTRY(PND_POST_ADDRESS_FIELD)
        DER_CONST_TBL_ENTRY(PND_RING_TONE_ID_FIELD)
        DER_CONST_TBL_ENTRY(PND_TIME_STAMP_FIELD)
        DER_CONST_TBL_ENTRY(PND_VM_PASSWORD_FIELD)
        DER_CONST_TBL_ENTRY(PND_WEB_ADDRESS_FIELD)
        DER_CONST_TBL_ENTRY(PND_PTT_LOGIN_STATUS_FIELD)			
        DER_CONST_TBL_ENTRY(PND_REF_SUPERGROUP_FIELD)
        DER_CONST_TBL_ENTRY(PND_VIDEO_TONE_SOURCE_ID_FIELD)
        DER_CONST_TBL_ENTRY(PND_FIRST_NAME_FIELD)			
        DER_CONST_TBL_ENTRY(PND_LAST_NAME_FIELD)	        
        DER_CONST_TBL_ENTRY(PND_FIRST_NAME_READING_FIELD)                
        DER_CONST_TBL_ENTRY(PND_LAST_NAME_READING_FIELD)        
        DER_CONST_TBL_ENTRY(PND_ADDRESS_CONTAINER_FIELD)
        DER_CONST_TBL_ENTRY(PND_FORMATTED_NAME_FIELD)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIELD_READ_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_FIELD_READ_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        COMMENT(COMMENT_TEXT, "DRAFT - DO NOT USE!")
        VALUE_CONST(PhysicalMemory, "Physical memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LUID_ANY)
        VALUE(32, BE, LUID, "Luid", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LOCATION_ANY)
        VALUE(16, BE, LocationIndex, "Location index", DEC)
        VALUE_CONST(FieldType, "Field type", PND_FIELD_READ_FIELDS)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        FILLER_EX(Reserved, 8, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 59)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIELD_READ_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_FIELD_READ_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 3)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_CALL_COUNT_FIELD)
            SB_LST_ENTRY(PND_CLI_ICON_ENABLE_STATUS_FIELD)
            SB_LST_ENTRY(PND_CLI_ICON_FIELD)
            SB_LST_ENTRY(PND_EMAIL_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_FIELD_LIST_INFO)
            SB_LST_ENTRY(PND_FIELD_REFERENCE_FIELD)
            SB_LST_ENTRY(PND_GROUP_ID_FIELD)
            SB_LST_ENTRY(PND_MATCHED_FIELD_INFO)
            SB_LST_ENTRY(PND_NAME_FIELD)
            SB_LST_ENTRY(PND_READING_FIELD)	
            SB_LST_ENTRY(PND_NOTE_FIELD)
            SB_LST_ENTRY(PND_ORDER_DATA_FIELD)
            SB_LST_ENTRY(PND_PHONE_NUMBER_FIELD)
            SB_LST_ENTRY(PND_POST_ADDRESS_FIELD)
/*            SB_LST_ENTRY(PND_RECORD_REFERENCE_FIELD) */
            SB_LST_ENTRY(PND_REF_SMSDL_FIELD)
            SB_LST_ENTRY(PND_REF_VOICETAG_FIELD)
            SB_LST_ENTRY(PND_RING_TONE_ID_FIELD)
            SB_LST_ENTRY(PND_TIME_STAMP_FIELD)
            SB_LST_ENTRY(PND_VM_PASSWORD_FIELD)
            SB_LST_ENTRY(PND_WEB_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_IMAGE_ID_FIELD)
            SB_LST_ENTRY(PND_IMPS_ID_FIELD)
            SB_LST_ENTRY(PND_NICKNAME_FIELD)
            SB_LST_ENTRY(PND_PS_DYNAMIC_FIELD)
            SB_LST_ENTRY(PND_IM_DYNAMIC_FIELD)
            SB_LST_ENTRY(PND_REF_IMLIST_FIELD)
            SB_LST_ENTRY(PND_REF_PSLIST_FIELD)
            SB_LST_ENTRY(PND_POC_GROUP_NICKNAME)
            SB_LST_ENTRY(PND_POC_GROUP_DOMAIN)
            SB_LST_ENTRY(PND_SIP_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_POC_GROUP_STATUS_FIELD)
            SB_LST_ENTRY(PND_POC_GROUP_FLAGS_FIELD)
            SB_LST_ENTRY(PND_PTT_LOGIN_STATUS_FIELD)			
            SB_LST_ENTRY(PND_REF_SUPERGROUP_FIELD)
            SB_LST_ENTRY(PND_VIDEO_TONE_SOURCE_ID_FIELD)
            SB_LST_ENTRY(PND_FIRST_NAME_FIELD)			
            SB_LST_ENTRY(PND_LAST_NAME_FIELD)				
            SB_LST_ENTRY(PND_FIRST_NAME_READING_FIELD)			
            SB_LST_ENTRY(PND_LAST_NAME_READING_FIELD)	
            SB_LST_ENTRY(PND_ADDRESS_CONTAINER_FIELD)	
            SB_LST_ENTRY(PND_FORMATTED_NAME_FIELD)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_FIELD_READ_REQ, PND_FIELD_READ_RESP)


    /* PND_FIELD_WRITE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIELD_WRITE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_FIELD_WRITE_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        COMMENT(COMMENT_TEXT, "DRAFT - DO NOT USE!")
        VALUE_CONST(PhysicalMemory, "Physical memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LUID_ANY)
        VALUE(32, BE, LUID, "Luid", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LOCATION_ANY)
        VALUE(16, BE, LocationIndex, "Location index", DEC)
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 4)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)      
            SB_LST_ENTRY(PND_CALL_COUNT_FIELD)
            SB_LST_ENTRY(PND_CLI_ICON_ENABLE_STATUS_FIELD)
            SB_LST_ENTRY(PND_CLI_ICON_FIELD)
            SB_LST_ENTRY(PND_EMAIL_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_FIELD_LIST_INFO)
            SB_LST_ENTRY(PND_FIELD_REFERENCE_FIELD)
            SB_LST_ENTRY(PND_GROUP_ID_FIELD)
            SB_LST_ENTRY(PND_MATCHED_FIELD_INFO)
            SB_LST_ENTRY(PND_NAME_FIELD)
            SB_LST_ENTRY(PND_READING_FIELD)	
            SB_LST_ENTRY(PND_NOTE_FIELD)
            SB_LST_ENTRY(PND_ORDER_DATA_FIELD)
            SB_LST_ENTRY(PND_PHONE_NUMBER_FIELD)
            SB_LST_ENTRY(PND_POST_ADDRESS_FIELD)
/*            SB_LST_ENTRY(PND_RECORD_REFERENCE_FIELD) */
            SB_LST_ENTRY(PND_REF_SMSDL_FIELD)
            SB_LST_ENTRY(PND_REF_VOICETAG_FIELD)
            SB_LST_ENTRY(PND_RING_TONE_ID_FIELD)
            SB_LST_ENTRY(PND_TIME_STAMP_FIELD)
            SB_LST_ENTRY(PND_VM_PASSWORD_FIELD)
            SB_LST_ENTRY(PND_WEB_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_IMAGE_ID_FIELD)
            SB_LST_ENTRY(PND_IMPS_ID_FIELD)
            SB_LST_ENTRY(PND_NICKNAME_FIELD)
            SB_LST_ENTRY(PND_PS_DYNAMIC_FIELD)
            SB_LST_ENTRY(PND_IM_DYNAMIC_FIELD)
            SB_LST_ENTRY(PND_REF_IMLIST_FIELD)
            SB_LST_ENTRY(PND_REF_PSLIST_FIELD)
            SB_LST_ENTRY(PND_POC_GROUP_NICKNAME)
            SB_LST_ENTRY(PND_POC_GROUP_DOMAIN)
            SB_LST_ENTRY(PND_SIP_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_POC_GROUP_STATUS_FIELD)
            SB_LST_ENTRY(PND_POC_GROUP_FLAGS_FIELD)
            SB_LST_ENTRY(PND_PTT_LOGIN_STATUS_FIELD)			
            SB_LST_ENTRY(PND_REF_SUPERGROUP_FIELD)
            SB_LST_ENTRY(PND_VIDEO_TONE_SOURCE_ID_FIELD)
            SB_LST_ENTRY(PND_FIRST_NAME_FIELD)			
            SB_LST_ENTRY(PND_LAST_NAME_FIELD)				
            SB_LST_ENTRY(PND_FIRST_NAME_READING_FIELD)			
            SB_LST_ENTRY(PND_LAST_NAME_READING_FIELD)	
            SB_LST_ENTRY(PND_ADDRESS_CONTAINER_FIELD)	
            SB_LST_ENTRY(PND_FORMATTED_NAME_FIELD)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIELD_WRITE_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_FIELD_WRITE_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_FIELD_REFERENCE_FIELD)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_FIELD_WRITE_REQ, PND_FIELD_WRITE_RESP)


    /* PND_FIELD_ERASE */

    DER_CONST_TBL_BEGIN(PND_FIELD_ERASE_FIELDS, PND_FIELD_TYPES, "", "")
        DER_CONST_TBL_ENTRY(PND_CLI_ICON_ENABLE_STATUS_FIELD)
        DER_CONST_TBL_ENTRY(PND_CLI_ICON_FIELD)
        DER_CONST_TBL_ENTRY(PND_EMAIL_ADDRESS_FIELD)
        DER_CONST_TBL_ENTRY(PND_FIELD_REFERENCE_FIELD)
        DER_CONST_TBL_ENTRY(PND_GROUP_ID_FIELD)
        DER_CONST_TBL_ENTRY(PND_NAME_FIELD)
        DER_CONST_TBL_ENTRY(PND_NOTE_FIELD)
        DER_CONST_TBL_ENTRY(PND_ORDER_DATA_FIELD)
        DER_CONST_TBL_ENTRY(PND_PHONE_NUMBER_FIELD)
        DER_CONST_TBL_ENTRY(PND_POST_ADDRESS_FIELD)
        DER_CONST_TBL_ENTRY(PND_RING_TONE_ID_FIELD)
        DER_CONST_TBL_ENTRY(PND_TIME_STAMP_FIELD)
        DER_CONST_TBL_ENTRY(PND_VM_PASSWORD_FIELD)
        DER_CONST_TBL_ENTRY(PND_WEB_ADDRESS_FIELD)
        DER_CONST_TBL_ENTRY(PND_PTT_LOGIN_STATUS_FIELD)			
        DER_CONST_TBL_ENTRY(PND_REF_SUPERGROUP_FIELD)
        DER_CONST_TBL_ENTRY(PND_VIDEO_TONE_SOURCE_ID_FIELD)
        DER_CONST_TBL_ENTRY(PND_FIRST_NAME_FIELD)			
        DER_CONST_TBL_ENTRY(PND_LAST_NAME_FIELD)	        
        DER_CONST_TBL_ENTRY(PND_FIRST_NAME_READING_FIELD)                
        DER_CONST_TBL_ENTRY(PND_LAST_NAME_READING_FIELD)        
        DER_CONST_TBL_ENTRY(PND_ADDRESS_CONTAINER_FIELD)
        DER_CONST_TBL_ENTRY(PND_FORMATTED_NAME_FIELD)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIELD_ERASE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_FIELD_ERASE_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        COMMENT(COMMENT_TEXT, "DRAFT - DO NOT USE!")
        VALUE_CONST(PhysicalMemory, "Physical memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LUID_ANY)
        VALUE(32, BE, LUID, "Luid", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LOCATION_ANY)
        VALUE(16, BE, LocationIndex, "Location index", DEC)
        VALUE_CONST(FieldType, "Field type", PND_FIELD_ERASE_FIELDS)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tPndFieldUniqueId")
        VALUE(8, BE, FieldUniqueId, "Field unique ID", DEC)
        FILLER_EX(Reserved, 8, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_FIELD_ERASE_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_FIELD_ERASE_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_FIELD_ERASE_REQ, PND_FIELD_ERASE_RESP)


    /* PND_DEFAULT_NUMBER_SET */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_DEFAULT_NUMBER_SET_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_DEFAULT_NUMBER_SET_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_FIELD_REFERENCE_FIELD)
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_DEFAULT_NUMBER_SET_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_DEFAULT_NUMBER_SET_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_DEFAULT_NUMBER_SET_REQ, PND_DEFAULT_NUMBER_SET_RESP)


    /* PND_SET_RECOVERY_STATE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_SET_RECOVERY_STATE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_SET_RECOVERY_STATE_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(RecoveryState, "Recovery state", PND_RECOVERY_ACTIONS)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_RECORD_REFERENCE_FIELD)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_SET_RECOVERY_STATE_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_SET_RECOVERY_STATE_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_SET_RECOVERY_STATE_REQ, PND_SET_RECOVERY_STATE_RESP)


    /* PND_CLOG_GETCOUNTER */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CLOG_GETCOUNTER_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_CLOG_GETCOUNTER_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CLOG_GETCOUNTER_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_CLOG_GETCOUNTER_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved1, 8, 2)
        VALUE(32, BE, SlowSynchNeeded, "Slow Sync Needed", HEX)
        VALUE(32, BE, LastCounter, "Last Counter", HEX)
        VALUE(32, BE, NextCounter, "Next Counter", HEX)
        VALUE(32, BE, NumberOfEntries, "NumberOfEntries", DEC)
        FILLER_EX(Reserved2, 8, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_CLOG_GETCOUNTER_REQ, PND_CLOG_GETCOUNTER_RESP)


    /* PND_CLOG_GETLOG */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CLOG_GETLOG_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_CLOG_GETLOG_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        FILLER_EX(Reserved1, 8, 1)
        COMMENT(COMMENT_TEXT, "Starting change log counter")
        VALUE(32, BE, Counter, "Counter", DEC)
        FILLER_EX(Reserved2, 8, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_DEVICE_FIELD)
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CLOG_GETLOG_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_CLOG_GETLOG_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved1, 8, 1)
        VALUE_CONST(LastFrame, "Last frame", YES_NO)
        COMMENT(COMMENT_TEXT, "The last change log counter")
        VALUE(32, BE, Counter, "Counter", DEC)
        FILLER_EX(Reserved2, 8, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_CHANGELOG_FIELD)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_CLOG_GETLOG_REQ, PND_CLOG_GETLOG_RESP)


    /* PND_CLOG_COUNTERSAVE_SET */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CLOG_COUNTERSAVE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_CLOG_COUNTERSAVE_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        VALUE(8, BE, SyncSucceeded, "Sync Succeeded", DEC)
        FILLER_EX(reserved, 8, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_DEVICE_FIELD)
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CLOG_COUNTERSAVE_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_CLOG_COUNTERSAVE_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_REQUEST_FAILED)    
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_CLOG_COUNTERSAVE_REQ, PND_CLOG_COUNTERSAVE_RESP)


    /* PND_CLOG_FORCERESYNC */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CLOG_FORCERESYNC_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_CLOG_FORCERESYNC_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        VALUE_CONST(ChangeType, "Change type", PND_CHANGE_TYPES)
        VALUE(32, BE, LUID, "Luid", DEC)
        FILLER_EX(Reserved, 8, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_RESERVATION_INFO)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CLOG_FORCERESYNC_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_CLOG_FORCERESYNC_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_CLOG_FORCERESYNC_REQ, PND_CLOG_FORCERESYNC_RESP)


    /* PND_CALL_STACK_CHANGED_IND */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_CALL_STACK_CHANGED_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_CALL_STACK_CHANGED_IND, MESSAGE_IND, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_CALL_STACK_INFO)
        SB_LST_REF_END
    MSG_END


    /* PND_RECORD_UPDATED_IND */

    CONST_TBL_BEGIN(PND_RECORD_UPDATE_OPERATION, 8, BE, "", "")
        CONST_TBL_ENTRY(PND_WRITE_REQ,          PND_WRITE_REQ, "")
        CONST_TBL_ENTRY(PND_ERASE_REQ,          PND_ERASE_REQ, "")
        CONST_TBL_ENTRY(PND_FIELD_WRITE_REQ,    PND_FIELD_WRITE_REQ, "")
        CONST_TBL_ENTRY(PND_FIELD_ERASE_REQ,    PND_FIELD_ERASE_REQ, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_RECORD_UPDATED_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_RECORD_UPDATED_IND, MESSAGE_IND, "", "")
        PND_MSG_HEADER
        COMMENT(COMMENT_TEXT, "DRAFT - DO NOT USE!")
        VALUE_CONST(PhysicalMemory, "Physical Memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical Memory", PND_LOGICAL_MEMORIES)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LUID_ANY)
        VALUE(32, BE, LUID, "Luid", DEC)
        VALUE(16, BE, LocationIndex, "Location Index", DEC)
        VALUE_CONST(Operation, "Operation", PND_RECORD_UPDATE_OPERATION)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_CLI_ICON_ENABLE_STATUS_FIELD)
            SB_LST_ENTRY(PND_CLI_ICON_FIELD)
            SB_LST_ENTRY(PND_EMAIL_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_FIELD_REFERENCE_FIELD)
            SB_LST_ENTRY(PND_GROUP_ID_FIELD)
            SB_LST_ENTRY(PND_NAME_FIELD)
            SB_LST_ENTRY(PND_NOTE_FIELD)
            SB_LST_ENTRY(PND_ORDER_DATA_FIELD)
            SB_LST_ENTRY(PND_PHONE_NUMBER_FIELD)
            SB_LST_ENTRY(PND_POST_ADDRESS_FIELD)
            SB_LST_ENTRY(PND_REF_SMSDL_FIELD)
            SB_LST_ENTRY(PND_REF_VOICETAG_FIELD)
            SB_LST_ENTRY(PND_RING_TONE_ID_FIELD)
            SB_LST_ENTRY(PND_TIME_STAMP_FIELD)
            SB_LST_ENTRY(PND_VM_PASSWORD_FIELD)
            SB_LST_ENTRY(PND_WEB_ADDRESS_FIELD)
        SB_LST_REF_END
    MSG_END


    /* PND_INIT_READY_IND */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_INIT_READY_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_INIT_READY_IND, MESSAGE_IND, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 2)
    MSG_END


    /* PND_MEMORY_RELEASE_IND */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_MEMORY_RELEASE_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_MEMORY_RELEASE_IND, MESSAGE_IND, "", "")
        PND_MSG_HEADER
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        FILLER_EX(Reserved, 8, 1)
    MSG_END


    /* PND_REFMEM_QUERY */

    DER_CONST_TBL_BEGIN(PND_REFMEM_QUERY_TYPE, PND_REFMEM_COMPARE_TYPES, "", "")
        DER_CONST_TBL_ENTRY(PND_VOICETAG_SEARCH)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_REFMEM_QUERY_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_REFMEM_QUERY_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(RefmemID, "Refmem ID", PND_REFMEM_QUERY_TYPE)
        FILLER_EX(Reserved, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_REFMEM_QUERY_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_REFMEM_QUERY_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_REFMEM_QUERY_INFO_FIELD)       
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_REFMEM_QUERY_REQ, PND_REFMEM_QUERY_RESP)


    /* PND_DYN_START */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_DYN_START_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_DYN_START_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(DynFeature, "Dynamic Feature", PND_DYNAMIC_FEATURES)
        FILLER_EX(Reserved, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_DYN_START_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_DYN_START_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        VALUE_CONST(DynFeature, "Dynamic Feature", PND_DYNAMIC_FEATURES)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_DYN_START_REQ, PND_DYN_START_RESP)

    
    /* PND_DYN_STOP */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_DYN_STOP_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_DYN_STOP_REQ, MESSAGE_REQ, "", "")
        PND_MSG_HEADER
        VALUE_CONST(DynFeature, "Dynamic Feature", PND_DYNAMIC_FEATURES)
        FILLER_EX(Reserved, 8, 1)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_DYN_STOP_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_DYN_STOP_RESP, MESSAGE_RESP, "", "")
        PND_MSG_HEADER
        VALUE_CONST(DynFeature, "Dynamic Feature", PND_DYNAMIC_FEATURES)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_REQUEST_FAILED)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(PND_DYN_STOP_REQ, PND_DYN_STOP_RESP)


    /* PND_PRESENCE_UPDATED */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_PRESENCE_UPDATED_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_PRESENCE_UPDATED_IND, MESSAGE_IND, "", "")
        PND_MSG_HEADER
        VALUE_CONST(PhysicalMemory, "Physical memory", PND_PHYSICAL_MEMORIES)
        VALUE_CONST(LogicalMemory, "Logical memory", PND_LOGICAL_MEMORIES)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LUID_ANY)
        VALUE(32, BE, LUID, "Luid", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, PND_LOCATION_ALL)
        VALUE(16, BE, LocationIndex, "Location Index", DEC)
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_PS_DYNAMIC_FIELD)
            SB_LST_ENTRY(PND_IM_DYNAMIC_FIELD)
        SB_LST_REF_END
    MSG_END


    /* PND_PROPERTY_SET */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#ifndef PND_EXCL_PTRS_FROM_MSG")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "uint8 PbMsg_Unpack( byte *pPbISIMessage,")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                    void **pPbMessage);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "uint8 PbMsg_Pack( void *pPbMessage,")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                  byte **pISIMessage);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void *PbMsg_Create( uint8 MessageId);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void  PbMsg_Release( void *pMsg);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void *PbMsg_SubBlockCreate( uint8 SubBlockId);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void  PbMsg_SubBlockRelease( void *SubBlockPtr);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "tSUB_BLOCK* PbMsg_SubBlockGet( const void *pPbMsg, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                               uint8 SubBlockId);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "tSUB_BLOCK* PbMsg_NextSubBlockGet( const void *pThisSubBlock, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                                   uint8 SubBlockId);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "uint8 PbMsg_SubBlockAdd( void* pMsg, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                         const void* pSubBlock );")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "uint8 PbMsg_SubBlockRemove( void *pPbMsg,")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                            const uint8 SubBlockId );")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "tPND_RECORD_INFO *PbMsg_RecordCreate( void); ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void  PbMsg_RecordRelease( tPND_RECORD_INFO *pRecord);  ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void* PbMsg_RecordFieldGet( const tPND_RECORD_INFO *pRecord, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                            uint8 FieldId); ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void* PbMsg_RecordNextFieldGet( const void *pThisSubBlock, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                                uint8 FieldId);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "uint8 PbMsg_RecordFieldAdd( tPND_RECORD_INFO* pRecord, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                            const tSUB_BLOCK* pNewSubBlock );")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "uint16 PbMsg_CalculateRecordLength( tPND_RECORD_INFO *pRecord);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void   PbMsg_RecordPack( tPND_RECORD_INFO *pRecord,")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                         byte **ppISIMessage);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void   PbMsg_RecordUnpack( byte *pISIMessage,")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                           tPND_RECORD_INFO **pRecord);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void *PbMsg_RecordFieldExtract( tPND_RECORD_INFO *pRecord, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                            tPndFieldUniqueId UniqueFieldId);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void *PbMsg_RecordFieldCopy( void* pSubBlock );")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "tPND_RECORD_INFO *PbMsg_RecordCopy( tPND_RECORD_INFO* pRecord );")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void *PbMsg_RecordFieldGetByID( tPND_RECORD_INFO *pRecord, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                            tPndFieldUniqueId UniqueFieldId);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "uint32 PbMsg_RecordFieldCountType( tPND_RECORD_INFO *pRecord, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                               uint8 SubBlockId);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "tSUB_BLOCK *PbMsg_SubBlockExtract( void *pPbMsg, uint8 SubBlockId);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void *PbMsg_RecordFieldGetByRefIDAndType( tPND_RECORD_INFO *pRecord, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                                       tPndFieldUniqueId UniqueFieldId, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                                       uint8 fieldType);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void *PbMsg_RecordFieldGetVoicetagByRefId( tPND_RECORD_INFO *pRecord, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                                        tPndFieldUniqueId UniqueFieldId);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "void *PbMsg_RecordFieldGetSmsDlByRefId( tPND_RECORD_INFO *pRecord, ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "                                     tPndFieldUniqueId UniqueFieldId);")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif /* PND_EXCL_PTRS_FROM_MSG */")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tPND_PROPERTY_SET_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(PND_PROPERTY_SET_IND, MESSAGE_IND, "", "")
        PND_MSG_HEADER
        FILLER_EX(Reserved, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, subblocks, "Subblocs", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(PND_LANGUAGE_INFO)
            SB_LST_ENTRY(PND_DEFAULT_MEMORY_INFO)
        SB_LST_REF_END
    MSG_END


RES_END


/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */


#endif /* _PND_ISI_M_H_


/* End of file pnd_isi_m.h */


