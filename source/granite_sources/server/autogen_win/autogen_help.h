/*
NOKIA MOBILE PHONES
R&D Oulu
Modena



            help_isi_m.h
            -------------------
            SW include - ANSI C



Continuus Ref:
--------------
Project:          global_interface/ISI/IAM

%name:            autogen_help.h %
%version:         1 %
%cvtype:          incl %
%instance:        co_pctls_1 %

Document code:    -

Copyright(c) Nokia Corporation. All rights reserved.

Change History:

VERSION     : 003.002           DRAFT           18-May-2004  Christian Jacob Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the interface
*/

/* ------------------------------------------------------------------------- */


/*  1    ABSTRACT

    1.1    Module type

    Message definition file for autogen
   

    1.2    Functional description

    This file is the message definition file for the Help server


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

#ifndef _HELP_ISI_M_H_
#define _HELP_ISI_M_H_


/*  3    CONSTANTS */

/* Message ID's */
#define HELP_STATIC_ACTIVATE_REQ        0x01
#define HELP_DYNAMIC_ACTIVATE_REQ       0x02
#define HELP_STATIC_ACTIVATE_RESP       0x03
#define HELP_DYNAMIC_ACTIVATE_RESP      0x04
#define HELP_TEMP_DEACTIVATE_REQ        0x05
#define HELP_TEMP_DEACTIVATE_RESP       0x06

/* Sub block ID's */


/* Other constants */


/*  4    MACROS */

#define HELP_MSG_HDR \
	VALUE(8, BE, utid, "Transaction ID", DEC) \
	REFERENCE(8, BE, message_id, "Message ID", MSG_ID) \

/* TODO: Change the version whenever the interface is changed */
/* default ISI version */

#ifndef HELP_ISI_VERSION
#define HELP_ISI_VERSION
#define HELP_ISI_VERSION_Z      3
#define HELP_ISI_VERSION_Y      2
#endif


/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                 "R&D Oulu")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                      "Modena")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,                "Juha Turpeinen")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,           "CONFIDENTIALITY")

/* ISI header properties */
PROPERTY_STRING(PROPERTY_ISIHDR_TITLE,                      "ISIHDR_TITLE")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                   "help_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16,                "")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,       "ou_gif")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,     "global_interface/ISI/IAM")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16,  "")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,    "-")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16, "")

/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                        "ISI HELP Server Message Descriptions")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                     "i_help_m.html")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,              "-")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB,         "ou_gif")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,       "GIF_SPECS-ou_gif#xxx")
PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH,               "GIF_SPECS/IAM")
PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

RES_BEGIN(RESOURCE_ISI, PN_HELP, HELP, "Help Server", 
    RES_VERSION_STRING(HELP_ISI_VERSION_Z, HELP_ISI_VERSION_Y), TRUE)

    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "-")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "-")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "NON_DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "15-FEB-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Christian Jacob Hansen")
    COMMENT(COMMENT_TEXT, "First autogenerated version")
    ISI_VERSION_HISTORY("003.002")


    /* --------------------------------------------------------------------- */
    /* Notes / references  */
    /* --------------------------------------------------------------------- */

    COMMENT(COMMENT_PARAGRAPH, "Autogeneration Process")
    COMMENT(COMMENT_PARAGRAPH, "Lotus Notes Database: Engine TEC DocMan")
    COMMENT(COMMENT_PARAGRAPH, "Document Number:      DSJ00311")
    COMMENT(COMMENT_PARAGRAPH, "Filename:             autogen_proc.doc")
    NOTE("/1/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Server Specification Documentation Guidelines")
    COMMENT(COMMENT_PARAGRAPH, "Part:      ISI:INSTRUCTIONS.BASE")
    COMMENT(COMMENT_PARAGRAPH, "Item name: ISI:DOCUMENTATION_GUIDELINES.BASE-MISC")
    COMMENT(COMMENT_PARAGRAPH, "Workset:   ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename:  i_docgui.doc")
    NOTE("/2/")

    COMMENT(COMMENT_PARAGRAPH, "ISI General Information")
    COMMENT(COMMENT_PARAGRAPH, "Part:      ISI:INSTRUCTIONS.BASE")
    COMMENT(COMMENT_PARAGRAPH, "Item name: ISI:GENERAL_INFORMATION.BASE-MISC")
    COMMENT(COMMENT_PARAGRAPH, "Workset:   ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename:  i_geninf.doc")
    NOTE("/3/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Common Message Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Part:      ISI:COMMON.BASE")
    COMMENT(COMMENT_PARAGRAPH, "Item name: ISI:COMMON_MESSAGES.BASE-SPEC")
    COMMENT(COMMENT_PARAGRAPH, "Workset:   ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename:  i_comm_m.doc")
    NOTE("/4/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Common Feature Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Part:      ISI:COMMON.BASE")
    COMMENT(COMMENT_PARAGRAPH, "Item name: ISI:COMMON_MESSAGES.BASE-SPEC")
    COMMENT(COMMENT_PARAGRAPH, "Workset:   ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename:  i_comm_f.doc")
    NOTE("/5/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Help Server Feature and Protocol Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Project: Isa_ui_interface")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_help_fp.doc")
    NOTE("/6/")

    COMMENT(COMMENT_PARAGRAPH, "Help Server Design")
    COMMENT(COMMENT_PARAGRAPH, "Workset: ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Part: ISI:DES_HELP.BASE")
    COMMENT(COMMENT_PARAGRAPH, "Item: ISI:HELP_SERVER_DESIGN.BASE-SPEC")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_help_d.doc")
    NOTE("/7/")


    /* --------------------------------------------------------------------- */
    /* Constants */
    /* --------------------------------------------------------------------- */

    COMMENT(COMMENT_TEXT, 
        "These constants are here for backward compatibility")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONSTANT(HELP_ISI_VERSION_ZZZ, HELP_ISI_VERSION_Z)
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONSTANT(HELP_ISI_VERSION_YYY, HELP_ISI_VERSION_Y)


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define HELP_ACTIVATE_RESP                       0x03 /* Do not use the old HELP_ACTIVATE_RESP defintion anymore */")
    MSG_ID_SECTION

    /* --------------------------------------------------------------------- */
    /* Symbol tables */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(HELP_MODES, 8, BE, "", "")
        CONST_TBL_ENTRY(HELP_AUTO_SCROLL,                   0x01, "")
        CONST_TBL_ENTRY(HELP_AUTO_SCROLL_ALLWAYS,           0x02, "")
        CONST_TBL_ENTRY(HELP_ACTIVATION_BLOCK,              0x03, "")
        CONST_TBL_ENTRY(HELP_ACTIVATION_UNBLOCK,            0x04, "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(HELP_MODES_BLOCK, HELP_MODES, "", "")
        DER_CONST_TBL_ENTRY(HELP_ACTIVATION_BLOCK)
        DER_CONST_TBL_ENTRY(HELP_ACTIVATION_UNBLOCK)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(ACTIVATION_STATUS_VALUES, 8, BE, "", "")
        CONST_TBL_ENTRY(HELP_ACTIVATE_OK,                   0x00, "")
        CONST_TBL_ENTRY(HELP_ACTIVATE_EMPTY_DATA_FAIL,      0x01, "")
        CONST_TBL_ENTRY(HELP_ACTIVATE_HANDLE_FAIL,          0x02, "")
        CONST_TBL_ENTRY(HELP_ACTIVATE_INVALID_MODE_FAIL,    0x03, "")
        CONST_TBL_ENTRY(HELP_ACTIVATE_INVALID_TYPE_FAIL,    0x04, "")
        CONST_TBL_ENTRY(HELP_ACTIVATE_GENERAL_FAIL,         0x05, "")
        CONST_TBL_ENTRY(HELP_ACTIVATE_ACTIVATION_OFF_FAIL,  0x06, "")
        CONST_TBL_ENTRY(HELP_ACTIVATE_NVD_FAIL,             0x07, "")
        CONST_TBL_ENTRY(HELP_ACTIVATE_TEMP_BLOCKED,         0x08, "")
        CONST_TBL_ENTRY(HELP_DEACTIVATE_OK,                 0x09, "")
        CONST_TBL_ENTRY(HELP_DEACTIVATE_FAIL,               0x0A, "")
    CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* FTD data table */
    /* --------------------------------------------------------------------- */


    /* --------------------------------------------------------------------- */
    /* Messages */
    /* --------------------------------------------------------------------- */

    /* HELP_STATIC_ACTIVATE */

	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "HELP_STATIC_ACTIVATE_STR")
    MSG_BEGIN(HELP_STATIC_ACTIVATE_REQ, MESSAGE_REQ, "", "")
        HELP_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, handle, "Help handle", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(mode, "Help mode", HELP_MODES)
        FILLER_EX(pad1, 8, 1)
        FILLER_EX(pad2, 8, 1)
        FILLER_EX(pad3, 8, 1)
    MSG_END

	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "HELP_ACTIVATE_RESP_STR")
    MSG_BEGIN(HELP_STATIC_ACTIVATE_RESP, MESSAGE_RESP, "", "")
        HELP_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(status, "Activation status", ACTIVATION_STATUS_VALUES)
        FILLER_EX(pad1, 8, 1)
    MSG_END

    MSG_PAIR(HELP_STATIC_ACTIVATE_REQ, HELP_STATIC_ACTIVATE_RESP)


    /* HELP_DYNAMIC_ACTIVATE */

	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(HELP_DYNAMIC_ACTIVATE_REQ, MESSAGE_REQ, "", "")
        HELP_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(mode, "Help mode", HELP_MODES)
        FILLER_EX(pad1, 8, 1)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, text, "Text to be shown", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE)
    MSG_END

	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(HELP_DYNAMIC_ACTIVATE_RESP, MESSAGE_RESP, "", "")
        HELP_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(status, "Activation status", ACTIVATION_STATUS_VALUES)
        FILLER_EX(pad1, 8, 1)
    MSG_END

    MSG_PAIR(HELP_DYNAMIC_ACTIVATE_REQ, HELP_DYNAMIC_ACTIVATE_RESP)


    /* HELP_TEMP_DEACTIVATE */

	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(HELP_TEMP_DEACTIVATE_REQ, MESSAGE_REQ, "", "")
        HELP_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(value, "Value", HELP_MODES_BLOCK)
        FILLER_EX(pad1, 8, 1)
    MSG_END

	PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(HELP_TEMP_DEACTIVATE_RESP, MESSAGE_RESP, "", "")
        HELP_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(status, "Activation status", ACTIVATION_STATUS_VALUES)
        FILLER_EX(pad1, 8, 1)
    MSG_END

    MSG_PAIR(HELP_TEMP_DEACTIVATE_REQ, HELP_TEMP_DEACTIVATE_RESP)

RES_END


/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */


#endif /* _HELP_ISI_M_H_


/* End of file help_isi_m.h */