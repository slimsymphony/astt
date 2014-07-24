/*
NOKIA                                                             CONFIDENTIAL
MP
Test Services Oulu



            granite_isi_m.h
            -------------------
            SW include - ANSI C


          
Copyright(c) Nokia Corporation. All rights reserved.

Change History:   See section ISI version history

*/

/* ------------------------------------------------------------------------- */


/*  1    ABSTRACT

    1.1    Module type

    Message definition file for autogen
   

    1.2    Functional description

    This file is the message definition file for the Granite private interface.


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

#ifndef _GRN_ISI_M_H_
#define _GRN_ISI_M_H_

/*  3    CONSTANTS */

/* Message ID's */

#define GRN_STATUS_REQ                  0x00
#define GRN_STATUS_RESP                 0x01
#define GRN_TEST_REQ                    0x02
#define GRN_TEST_RESP                   0x03
#define GRN_TEST_NTF                    0x04
#define GRN_ABORT_REQ                   0x05
#define GRN_ABORT_RESP                  0x06
#define GRN_DISPLAY_UPDATE_NTF          0x09
#define GRN_CTC_START_REQ               0x0A
#define GRN_CTC_START_RESP              0x0B
#define GRN_CTC_STOP_REQ                0x0C
#define GRN_CTC_STOP_RESP               0x0D
#define GRN_RESULT_REQ                  0x0F
#define GRN_RESULT_RESP                 0x10
#define GRN_TERM_REQ                    0x11
#define GRN_TERM_RESP                   0x12
#define GRN_CLEAR_REQ                   0x14
#define GRN_CLEAR_RESP                  0x16
#define GRN_CLEAR_TESTCASE_REQ          0x17
#define GRN_CLEAR_TESTCASE_RESP         0x19
#define GRN_RESET_PHONE_REQ             0x1E
#define GRN_PROVISIONING_WRITE_REQ      0x1F
#define GRN_PROVISIONING_WRITE_RESP     0x20
#define GRN_PROVISIONING_READ_REQ       0x21
#define GRN_PROVISIONING_READ_RESP      0x22
#define GRN_PROVISIONING_SELECT_REQ     0x23
#define GRN_PROVISIONING_SELECT_RESP    0x24
#define GRN_PROVISIONING_DELETE_REQ     0x25
#define GRN_PROVISIONING_DELETE_RESP    0x26

/* Sub block ID's */

#define GRN_NO_INFO                     0x00
#define GRN_PARSE_ERROR_INFO            0x01
#define GRN_WBXML_REQ_INFO              0x02
#define GRN_RUN_STEP_INFO               0x03
#define GRN_WBXML_RESP_INFO             0x04
#define GRN_DISPLAY_DATA_INFO           0x05
#define GRN_INDEX_INFO                  0x06
#define GRN_SERVER_VERSION_INFO         0x07
#define GRN_SERVER_STATE_INFO           0x08
#define GRN_PROVISIONG_DATA             0x0D

/* Other constants */

/* TODO: Change the version whenever the interface is changed */
/* default ISI version */

#ifndef GRN_ISI_VERSION
#define GRN_ISI_VERSION
#define GRN_ISI_VERSION_Z      1
#define GRN_ISI_VERSION_Y      8
#endif

#define GRN_ISI_VERSION_ZZZ    GRN_ISI_VERSION_Z
#define GRN_ISI_VERSION_YYY    GRN_ISI_VERSION_Y

/*  4    MACROS */

#define GRN_MSG_HDR      \
        COMMON_MSG_HDR   \
        REFERENCE(16, BE, private_id, "Private ID", PRIVATE_ID)   \
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, FALSE) \
        COMMENT(COMMENT_TEXT, "This message cannot be continued") \
        VALUE_CONST(Continue, "Continue", TRUE_FALSE)

#define GRN_MSG_HDR_MULTI  \
        COMMON_MSG_HDR     \
        REFERENCE(16, BE, private_id, "Private ID", PRIVATE_ID)   \
        PROPERTY_STRING(PROPERTY_ITEM_DEFAULT_VALUE, "FALSE") \
        COMMENT(COMMENT_TEXT, "TRUE if message is incomplete and continued " \
                              "in the next message. " \
                              "FALSE in the last messsage.") \
        VALUE_CONST(Continue, "Continue", TRUE_FALSE)

#define GRN_SB_HDR_WITH_OPTION(OptionSet) \
        REFERENCE(8, BE, ID, "Sub Block ID", SB_ID) \
        VALUE_CONST(Option, "Option", OptionSet) \
        REFERENCE(16, BE, Length, "Sub Block Length", SB_LENGTH)

#define GRN_SB_HDR \
        REFERENCE(8, BE, ID, "Sub Block ID", SB_ID) \
        FILLER(FILLER_FIXED, 8) \
        REFERENCE(16, BE, Length, "Sub Block Length", SB_LENGTH)

#define MAX_PROVISIONG_DATA 32763

/* --------------------------------------------------------------------- */
/* Project / Document information */
/* --------------------------------------------------------------------- */
/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                 "MP")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                      "SETS Oulu")
/*
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,                "OWNER_NAME")
*/
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,           "CONFIDENTIAL")

/* ISI header properties */
PROPERTY_STRING(PROPERTY_ISIHDR_TITLE,                      "Granite Server Private ISI Interface")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                   "granite_p_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16,                "")

/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                        "Granite Server Private Message Specification")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                     "i_granite_m.html")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,              "-")
PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

/* Interface description */
/*
COMMENT(COMMENT_PARAGRAPH,
        "The features for this server are defined in the feature specification "
        "document for this server (see reference ")
COMMENT_LINK(LINK_NOTE, "/5/", "", "")
COMMENT(COMMENT_TEXT,
        ") and the common feature "
        "specification document (see reference ")
COMMENT_LINK(LINK_NOTE, "/6/", "", "")
COMMENT(COMMENT_PARAGRAPH,
        ").")
COMMENT(COMMENT_PARAGRAPH,
        "Each version of Granite server implements one version of this private int"
        "erface. Each version of the Granite framework usually supports several ve"
        "rsions of the interface.")
*/

/*  you could include links to other documents in the desciption
COMMENT(COMMENT_BULLET,    "Bullet A.....")
COMMENT(COMMENT_BULLET,    "Bullet B.....")
COMMENT(COMMENT_PARAGRAPH, "Besides, you can...")
COMMENT(COMMENT_NEWLINE,   "")
COMMENT(COMMENT_TEXT,      
    "The features for this server are defined in the feature "
    "specification document (see reference ")
COMMENT(LINK_NOTE, "/4/", "", "")
COMMENT(COMMENT_TEXT,      
    ") and in the common feature specification document (see reference ")
COMMENT(LINK_NOTE, "/5/", "", "")
COMMENT(COMMENT_TEXT,      
    "). The protocol description for [Granite server] can be found in reference ")
COMMENT(LINK_NOTE, "/6/", "", "")
COMMENT(COMMENT_TEXT,       ".")
*/

/* This ID must be agreed with Joergen Edelbo 
   See: http://cowww02.europe.nokia.com/projects/isacoresw/cl/pn_private.htm
*/
#define PN_PRIVATE_GRANITE         0xFF0D

/* Defining default object ID for the private entity */
PROPERTY_STRING(PROPERTY_PMD_PHONET_OBJECT_ID, "PN_OBJ_GRN_SERV")

PROPERTY(PROPERTY_ISIHDR_GENERATE_BOOLS)

RES_BEGIN(RESOURCE_ISI_PRIVATE, PN_PRIVATE_GRANITE, GRANITE, "GRANITE private interface", 
    RES_VERSION_STRING(GRN_ISI_VERSION_Z, GRN_ISI_VERSION_Y), FALSE)


    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    /* TODO: Add version history block every time the interface is changed */
	PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "ISI interface update")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "2013-08-27")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Risto Pakanen")
    COMMENT(COMMENT_TEXT, "Updated GRN_DISPLAY_UPDATE_NTF message and added ntf_sending attribute")
    ISI_VERSION_HISTORY("001.008")	

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "ISI interface update")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "2013-04-26")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Vaino Holopainen")
    COMMENT(COMMENT_TEXT, "Removed ISM setting support")
    ISI_VERSION_HISTORY("001.007")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "ISI interface update")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "2013-01-23")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Vaino Holopainen")
    COMMENT(COMMENT_TEXT, "Removed ISM ucs2_string setting support")
    ISI_VERSION_HISTORY("001.006")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "ISI interface update")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "2012-10-23")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Joni Vanhamaki")
    COMMENT(COMMENT_TEXT, "Updated provisioning settings messages")
    ISI_VERSION_HISTORY("001.005")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "ISI interface update")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "2012-09-4")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Teemu Kokko")
    COMMENT(COMMENT_TEXT, "Added new tag and renamed attribute")
    ISI_VERSION_HISTORY("001.004")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "ISI interface update")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "2012-06-6")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Risto Pakanen")
    COMMENT(COMMENT_TEXT, "ISI messages added for CTC usage and Provisioning write & read")
    ISI_VERSION_HISTORY("001.003")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "ISI interface update")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "2012-05-16")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Teemu Kokko")
    COMMENT(COMMENT_TEXT, "Common-request and display-notify data structures added")
    ISI_VERSION_HISTORY("001.002")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "ISI interface update")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "2012-04-17")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Risto Pakanen")
    COMMENT(COMMENT_TEXT, "Data structures updated")
    ISI_VERSION_HISTORY("001.001")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Creation of Granite server")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "2012-02-13")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Risto Pakanen")
    COMMENT(COMMENT_TEXT, "Granite server private interface is based on ART2 server's private interface")
    ISI_VERSION_HISTORY("001.000")

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
    COMMENT(COMMENT_PARAGRAPH, "Workset:   ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Part:      ISI:COMMON.BASE")
    COMMENT(COMMENT_PARAGRAPH, "Item:      ISI:COMMON_MESSAGES.BASE-SPEC")
    COMMENT(COMMENT_PARAGRAPH, "Filename:  i_comm_m.doc")
    NOTE("/4/")
/*
    COMMENT(COMMENT_PARAGRAPH, "GRANITE Server Feature Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Part:      ISI:GRANITESERVER.BASE")
    COMMENT(COMMENT_PARAGRAPH, "Item name: ISI:GRANITESERVER.BASE-SPEC")
    COMMENT(COMMENT_PARAGRAPH, "Workset:   ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename:  i_grn_server_f.doc")
    NOTE("/5/")
*/

    COMMENT(COMMENT_PARAGRAPH, "ISI Common Feature Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Workset: ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Part: ISI:COMMON.BASE")
    COMMENT(COMMENT_PARAGRAPH, "Item: ISI:COMMON_FEATURES.BASE-SPEC")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_comm_f.doc")
    NOTE("/6/")

    COMMENT(COMMENT_PARAGRAPH, "Binary XML Content Format Specification")
    COMMENT(COMMENT_PARAGRAPH, "Version 1.3, 25 July 2001")
    COMMENT(COMMENT_PARAGRAPH, "Wireless Application Protocol")
    COMMENT(COMMENT_PARAGRAPH, "WAP-192-WBXML-20010725-a")
    COMMENT(COMMENT_PARAGRAPH, "Wireless Application Protocol Forum, Ltd.")
    NOTE("/7/")

    /* TODO: place other document references and notes here... */
/*
    COMMENT(COMMENT_PARAGRAPH, "GRANITE Message Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Part:      ISI:GRANITE")
    COMMENT(COMMENT_PARAGRAPH, "Item name: ISI:GRANITE")
    COMMENT(COMMENT_PARAGRAPH, "Workset:   ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename:  i_granite_m.html")
    NOTE("/4/")

    COMMENT(COMMENT_PARAGRAPH, "GRANITE Protocol Description")
    COMMENT(COMMENT_PARAGRAPH, "Part:      ISI:GRANITE")
    COMMENT(COMMENT_PARAGRAPH, "Item name: ISI:GRANITE.BASE-SPEC")
    COMMENT(COMMENT_PARAGRAPH, "Workset:   ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename:  i_granite_p.doc")
    NOTE("/6/")

    ...

*/

    /* --------------------------------------------------------------------- */
    /* Symbol tables */
    /* --------------------------------------------------------------------- */

    /* Server state */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tGRN_server_state")

    CONST_TBL_BEGIN(GRN_SERVER_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(GRN_SERVER_STATE_STARTING,  0x00, "")
        CONST_TBL_ENTRY(GRN_SERVER_STATE_IDLE,      0x01, "")
        CONST_TBL_ENTRY(GRN_SERVER_STATE_PARSING,   0x02, "")
        CONST_TBL_ENTRY(GRN_SERVER_STATE_RUNNING,   0x03, "")
        CONST_TBL_ENTRY(GRN_SERVER_STATE_ABORTING,  0x04, "")
        CONST_TBL_ENTRY(GRN_SERVER_STATE_SUSPENDED, 0x05, "")
        CONST_TBL_ENTRY(GRN_SERVER_STATE_INACTIVE,          0x07, "")
        CONST_TBL_ENTRY(GRN_SERVER_STATE_REPORTING,         0x08, "")
        CONST_TBL_ENTRY(GRN_SERVER_STATE_CLEARING,          0x09, "")
        CONST_TBL_ENTRY(GRN_SERVER_STATE_TERMINATING,       0x0A, "")
        CONST_TBL_ENTRY(GRN_SERVER_STATE_CLEARING_TESTCASE, 0x0B, "")
    CONST_TBL_END

    /* Subblock option */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tGRN_option")

    CONST_TBL_BEGIN(GRN_OPTIONS, 8, BE, "", "")
        CONST_TBL_ENTRY(GRN_OPTION_NONE,   0x00, "")
        CONST_TBL_ENTRY(GRN_OPTION_POLLED, 0x01, "")
        CONST_TBL_ENTRY(GRN_OPTION_FILE,   0x02, "")
        CONST_TBL_ENTRY(GRN_OPTION_END,    0x03, "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(GRN_OPTIONS_POLLED, GRN_OPTIONS, "", "")
        DER_CONST_TBL_ENTRY(GRN_OPTION_POLLED)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(GRN_OPTIONS_END, GRN_OPTIONS, "", "")
        DER_CONST_TBL_ENTRY(GRN_OPTION_NONE)
        DER_CONST_TBL_ENTRY(GRN_OPTION_END)
    DER_CONST_TBL_END

    /* Test notifications */

    COMMENT(COMMENT_PARAGRAPH, "Future versions may add other notifications. "
    "Unidentified notifications may be ignored.")

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tGRN_notification")

    CONST_TBL_BEGIN(GRN_NOTIFICATIONS, 8, BE, "", "")
        COMMENT(COMMENT_TEXT,"Server is expecting continuation to a test request")
        CONST_TBL_ENTRY(GRN_NTF_PARSE_CONTINUE, 0x02, "")
        CONST_TBL_ENTRY(GRN_NTF_PARSE_DONE,     0x03, "")
    CONST_TBL_END

    /* Test causes */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tGRN_cause")

    CONST_TBL_BEGIN(GRN_CAUSES, 8, BE, "", "")
        CONST_TBL_ENTRY(GRN_CAUSE_NONE,                  0x00, "")
        CONST_TBL_ENTRY(GRN_CAUSE_INVALID_WBXML_DATA,    0x01, "")
        CONST_TBL_ENTRY(GRN_CAUSE_MEMORY_FULL,           0x02, "")
        CONST_TBL_ENTRY(GRN_CAUSE_ERROR_TERMINATION,     0x03, "")
        CONST_TBL_ENTRY(GRN_CAUSE_NOTEXPECTED_RESULT,    0x04, "")
        CONST_TBL_ENTRY(GRN_CAUSE_STATE_UNKNOWN,         0x09, "")
        CONST_TBL_ENTRY(GRN_CAUSE_STATE_STARTING,        0x0B, "")
        CONST_TBL_ENTRY(GRN_CAUSE_STATE_IDLE,            0x11, "")
        CONST_TBL_ENTRY(GRN_CAUSE_STATE_PARSING,         0x06, "")
        CONST_TBL_ENTRY(GRN_CAUSE_STATE_RUNNING,         0x07, "")
        CONST_TBL_ENTRY(GRN_CAUSE_STATE_ABORTING,        0x08, "")
        CONST_TBL_ENTRY(GRN_CAUSE_STATE_SUSPENDED,       0x15, "")
        CONST_TBL_ENTRY(GRN_CAUSE_STATE_INACTIVE,        0x17, "")
        CONST_TBL_ENTRY(GRN_CAUSE_STATE_REPORTING,       0x18, "")
        CONST_TBL_ENTRY(GRN_CAUSE_STATE_CLEARING,        0x19, "")
        CONST_TBL_ENTRY(GRN_CAUSE_STATE_TERMINATING,     0x1A, "")
        CONST_TBL_ENTRY(GRN_CAUSE_STATE_CLEARING_TESTCASE, 0x1B, "")
    CONST_TBL_END

    /* WBXML errors */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tGRN_error")

    CONST_TBL_BEGIN(GRN_TEST_PARSE_ERRORS, 8, BE, "", "")
        CONST_TBL_ENTRY(GRN_TEST_PARSE_NOERROR,          0x00, "")
        CONST_TBL_ENTRY(GRN_TEST_PARSE_MEMORY_ERROR,     0x01, "")
        CONST_TBL_ENTRY(GRN_TEST_ILLEGAL_PUBLIC_ID,      0x03, "")
        CONST_TBL_ENTRY(GRN_TEST_ILLEGAL_CHARSET,        0x04, "")
        CONST_TBL_ENTRY(GRN_TEST_STR_T_NOT_EMPTY,        0x05, "")
        CONST_TBL_ENTRY(GRN_TEST_ILLEGAL_MB_U_INT32,     0x06, "")
        CONST_TBL_ENTRY(GRN_TEST_ILLEGAL_UTF8_STRING,    0x07, "")
        CONST_TBL_ENTRY(GRN_TEST_UNEXPECTED_TAG,         0x08, "")
        CONST_TBL_ENTRY(GRN_TEST_UNEXPECTED_DATA_END,    0x0D, "")
        CONST_TBL_ENTRY(GRN_TEST_UNEXPECTED_ELEMENT,     0x0E, "")
    CONST_TBL_END

    /* WBXML encoding values */

    COMMENT(COMMENT_PARAGRAPH, "The first byte of any WBXML data identifies "
    "WBXML version in use.")

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")

    CONST_TBL_BEGIN(GRN_WBXML_VERSIONS, 8, BE, "", "")
        CONST_TBL_ENTRY(GRN_WBXML_VERSION, 0x03, "")
    CONST_TBL_END


    COMMENT(COMMENT_PARAGRAPH, "The second byte of any WBXML data is a "
    "publick ID that identifies encoding of tags. In case of GRANITE server's "
    "private interface this has little significance, for all parties know "
    "encoding conventions, and the WBXML data is not used elsewhere.")

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")

    CONST_TBL_BEGIN(GRN_WBXML_PUBLIC_IDS, 8, BE, "", "")
        CONST_TBL_ENTRY(GRN_WBXML_PUBLIC_ID, 0x20, "")
    CONST_TBL_END


    COMMENT(COMMENT_PARAGRAPH, "The third byte of any WBXML data identifies "
    "character encoding used in all texts.")

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")

    CONST_TBL_BEGIN(GRN_WBXML_CHARSETS, 8, BE, "", "")
        CONST_TBL_ENTRY(GRN_WBXML_CHARSET_UTF8, 0x6A, "")
    CONST_TBL_END


    COMMENT(COMMENT_PARAGRAPH, "Encoding of WBXML Global tokens as specified "
    "in the WBXML standard ")
    COMMENT_LINK(LINK_NOTE, "/7/", "", "")
    COMMENT(COMMENT_PARAGRAPH, ". Tokens marked \"Not used\" are not used in "
    "messages to or from GRANITE server.")

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")

    CONST_TBL_BEGIN(GRN_WBXML_GLOBALS, 8, BE, "", "")
        CONST_TBL_ENTRY(GRN_WBXML_SWITCH_PAGE, 0x00, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_END,         0x01, "")
        CONST_TBL_ENTRY(GRN_WBXML_ENTITY,      0x02, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_STR_I,       0x03, "used for string values and text content")
        CONST_TBL_ENTRY(GRN_WBXML_LITERAL,     0x04, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_EXT_I_0,     0x40, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_EXT_I_1,     0x41, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_EXT_I_2,     0x42, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_PI,          0x43, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_LITERAL_C,   0x44, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_EXT_T_0,     0x80, "used for integer values")
        CONST_TBL_ENTRY(GRN_WBXML_EXT_T_1,     0x81, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_EXT_T_2,     0x82, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_STR_T,       0x83, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_LITERAL_A,   0x84, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_EXT_0,       0xC0, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_EXT_1,       0xC1, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_EXT_2,       0xC2, "Not used")
        CONST_TBL_ENTRY(GRN_WBXML_OPAQUE,      0xC3, "used for bitmap images")
        CONST_TBL_ENTRY(GRN_WBXML_LITERAL_AC,  0xC4, "Not used")
    CONST_TBL_END


    COMMENT(COMMENT_PARAGRAPH, "Two bits in a tag byte are reserved "
    "for attribute and content indicators.")

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    BIT_TBL_BEGIN(GRN_WBXML_TAG_BITS, 8, BE, "", "")
        BIT_TBL_ENTRY("1-------", GRN_WBXML_A, "Tag has attributes")
        BIT_TBL_ENTRY("-1------", GRN_WBXML_C, "Tag has contents")
        BIT_TBL_ENTRY("--111111", GRN_WBXML_TAG_MASK, "Mask for tag")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH, "These encodings are used for XML tags in "
    "messages to and from GRANITE server. Literal tags are not used.")

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")

    CONST_TBL_BEGIN(GRN_WBXML_TAGS, 8, BE, "", "")
        /* Available range 0x05-0x3F */
        CONST_TBL_ENTRY(GRN_WBXML_TAG_teststep,     0x05, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_sx,           0x06, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_delay,        0x07, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_key_in,       0x08, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_keypress,     0x09, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_expect,       0x0B, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_display,      0x0C, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_bitmap,       0x0D, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_text,         0x0E, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_data,         0x0F, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_capture,      0x10, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_animation,    0x11, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_config,       0x12, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_block,        0x13, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_touch,        0x14, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_press,        0x15, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_move,         0x16, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_release,      0x17, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_xml,          0x18, "")
        CONST_TBL_ENTRY(GRN_WBXML_TAG_java,          0x19, "")
    CONST_TBL_END


    COMMENT(COMMENT_PARAGRAPH, "These encodings are used for XML attribute "
    "names in messages to and from GRANITE server. None of the codes encodes any "
    "part of the attribute value. Literal names are not used. The value that "
    "follows must be of the type indicated in Comment.")
    COMMENT(COMMENT_PARAGRAPH, "The Comment indicates how attribute values are "
    "encoded. Comment \"string\" means that the attribute value is encoded as "
    "a string. Values of other attributes shall not be encoded as a string. "
    "Comment with alternatives means that the values is one of alternatives "
    "encoded with a single byte as shown in table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_ATTR_VALUES", "", "")
    COMMENT(COMMENT_PARAGRAPH, ". The value \"yes\" may be omitted. If the "
    "list of alternatives is surrounded  by braces, more than one alternative "
    "may be specified. Comment \"integer\" means that value is a number "
    "encoded with the GRN_WBXML_EXT_T_0 byte (defined in table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_GLOBALS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ") followed by the value in mb_uint32 "
    "encoding. However, small values may (but need not) be encoded with "
    "single bytes as shown in table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_ATTR_VALUES", "", "")
    COMMENT(COMMENT_PARAGRAPH, ". The value zero can be omitted completely.")

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")

    CONST_TBL_BEGIN(GRN_WBXML_ATTR_LABELS, 8, BE, "", "")
        /* 0x00-0x04 Reserved for global tokens */
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_wait,                   0x05, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_key,                    0x06, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_length,                 0x07, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_repeat,                 0x08, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_timeout,                0x09, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_font,                   0x0A, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_color,                  0x0B, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_x,                      0x0C, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_y,                      0x0D, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_width,                  0x0E, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_height,                 0x0F, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_mask,                   0x10, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_highlighted,            0x11, "yes/no")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_name,                   0x12, "string")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_valid,                  0x13, "yes/no")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_id,                     0x14, "integer")
        COMMENT(COMMENT_TEXT, "integer with ")
        COMMENT_LINK(LINK_TABLE, "GRN_STATUS_BITS", "", "")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_result,                 0x15, "")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_format,                 0x16, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_checksum,               0x17, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_animation_id,           0x18, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_truncated,              0x19, "yes/no")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_items,                  0x1A, "{text/animation/bitmap/items/all}")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_bitmap_capture,         0x1B, "yes/no")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_max_isi_data_length,    0x1C, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_keypress_length,        0x1D, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_keypress_wait,          0x1E, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_screen,                 0x1F, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_dimmed,                 0x20, "yes/no")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_wait_for_key_release,   0x21, "yes/no")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_wildcard,               0x22, "yes/no")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_offset,                 0x24, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_gap,                    0x25, "integer")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_little_endian_cpu,      0x30, "yes/no")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_training,               0x31, "yes/no")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_action,                 0x32, "hold/release")
        COMMENT(COMMENT_TEXT, "integer (default: 800)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_long_press_length,  0x33, "")
        COMMENT(COMMENT_TEXT, "integer (default: 500)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_repeat_length,      0x34, "")
        COMMENT(COMMENT_TEXT, "integer (8+8+8 bit RGB)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_fore_color,                 0x35, "")
        COMMENT(COMMENT_TEXT, "integer (8+8+8 bit RGB)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_bg,                 0x36, "")
        COMMENT(COMMENT_TEXT, "yes/no/all (default: no)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_background,         0x37, "")
        COMMENT(COMMENT_TEXT, "yes/no (default: no)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_landscape,          0x38, "")
        COMMENT(COMMENT_TEXT, "integer (default may vary)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_font_type,          0x39, "")
        COMMENT(COMMENT_TEXT, "integer (default: 0)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_short_press_length, 0x3A, "")
        COMMENT(COMMENT_TEXT, "integer (default: 0)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_keys_idle_length,   0x3B, "")
        COMMENT(COMMENT_TEXT, "integer (default: 0)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_is_checksum,        0x52, "")
        COMMENT(COMMENT_TEXT, "integer (default: 0)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_checksum_id,        0x53, "")
        COMMENT(COMMENT_TEXT, "yes/no (default: no)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_ntf_sending,        0x54, "")
        COMMENT(COMMENT_TEXT, "integer (default: 0)")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_touch_id,           0x55, "")
        /* 0x40-0x44 Reserved for global tokens */
        /* 0x80-0xFF Reserved for global tokens and attribute values */
    CONST_TBL_END


    COMMENT(COMMENT_PARAGRAPH, "These encodings are used for XML for attribute "
    "values. Encoding as a string is used only for attributes marked with "
    "\"string\" in the table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_ATTR_LABELS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ". Integer values greater than 15 must (and "
    "all integer values may) be encoded with with the GRN_WBXML_EXT_T_0 byte ("
    "defined in table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_GLOBALS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ") followed by the value in mb_uint32 "
    "encoding.")
    COMMENT(COMMENT_PARAGRAPH, "If attribute value is encoded using bytes of "
    "this table, it is encoded with single byte only, except that the value "
    "of items attribute in capture tag can be a sequence of bytes.")
    COMMENT(COMMENT_PARAGRAPH, "If the value of attribute is \"yes\" or zero "
    "it can be omitted.")

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")

    CONST_TBL_BEGIN(GRN_WBXML_ATTR_VALUES, 8, BE, "", "")
        /* 0x00-0x84 Reserved for global tokens and attribute starts */
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_yes,              0x85, "")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_no,               0x86, "")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_text,             0x87, "for items in capture tag")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_animation,        0x88, "for items in capture tag")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_bitmap,           0x89, "for items in capture tag")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_items,            0x90, "for items in capture tag")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_all,              0x91, "for items in capture tag")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_hold,             0x92, "for action in keypress")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_release,          0x93, "for action in keypress")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_0,                0xB0, "numeric value zero")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_1,                0xB1, "numeric value one")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_2,                0xB2, "numeric value two")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_3,                0xB3, "numeric value three")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_4,                0xB4, "numeric value four")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_5,                0xB5, "numeric value five")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_6,                0xB6, "numeric value six")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_7,                0xB7, "numeric value seven")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_8,                0xB8, "numeric value eight")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_9,                0xB9, "numeric value nine")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_10,               0xBA, "numeric value ten")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_11,               0xBB, "numeric value eleven")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_12,               0xBC, "numeric value twelve")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_13,               0xBD, "numeric value thirteen")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_14,               0xBE, "numeric value fourteen")
        CONST_TBL_ENTRY(GRN_WBXML_ATTR_VALUE_15,               0xBF, "numeric value fifteen")
        /* 0xC0-0xC4 Reserved for global tokens */
    CONST_TBL_END


    COMMENT(COMMENT_PARAGRAPH, "Value of result attribute is an integer where "
        "each bit has independent meaning (what was wrong in the display). "
        "This table identifies the bit used for each meaning.")

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tGRN_status_bits")

    BIT_TBL_BEGIN(GRN_STATUS_BITS, 16, BE, "", "")
        BIT_TBL_ENTRY("0000000000000000", GRN_STATUS_NONE, "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "GRN_STATUS_text")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "GRN_STATUS_animation_id")
        BIT_TBL_ENTRY("---------------1", GRN_STATUS_data, "")
        BIT_TBL_ENTRY("--------------1-", GRN_STATUS_x, "")
        BIT_TBL_ENTRY("-------------1--", GRN_STATUS_y, "")
        BIT_TBL_ENTRY("------------1---", GRN_STATUS_width, "")
        BIT_TBL_ENTRY("-----------1----", GRN_STATUS_height, "")
        BIT_TBL_ENTRY("----------1-----", GRN_STATUS_highlighted, "")
        BIT_TBL_ENTRY("---------1------", GRN_STATUS_font, "")
        BIT_TBL_ENTRY("--------1-------", GRN_STATUS_color, "")
        BIT_TBL_ENTRY("-------1--------", GRN_STATUS_truncated, "")
        BIT_TBL_ENTRY("------1---------", GRN_STATUS_screen, "")
        BIT_TBL_ENTRY("-----1----------", GRN_STATUS_dimmed, "")
        BIT_TBL_ENTRY("----1-----------", GRN_STATUS_background, "")
        BIT_TBL_ENTRY("---1------------", GRN_STATUS_is_checksum, "")
        BIT_TBL_ENTRY("--1-------------", GRN_STATUS_checksum_id, "")
    BIT_TBL_END


    COMMENT(COMMENT_PARAGRAPH, "Provisioning data type one of these: JSON,XML,WBXML")

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")

    CONST_TBL_BEGIN(GRN_PROVISIONING_DATA_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(GRN_PROVISIONING_JSON,  0x00, "JSON [Default]")
        CONST_TBL_ENTRY(GRN_PROVISIONING_XML,   0x01, "XML")
        CONST_TBL_ENTRY(GRN_PROVISIONING_WBXML, 0x02, "WBXML")
    CONST_TBL_END

    COMMENT(COMMENT_PARAGRAPH, "Provisioning responses")

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")

    CONST_TBL_BEGIN(GRN_PROVISIONING_RESPONSE, 8, BE, "", "")
        CONST_TBL_ENTRY(GRN_PROVISIONING_OK,            0x00, "Success")
        CONST_TBL_ENTRY(GRN_PROVISIONING_FAIL,          0x01, "Failure")
        CONST_TBL_ENTRY(GRN_PROVISIONING_NOT_SUPPORTED, 0x02, "Not supported")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Sequences */
    /* --------------------------------------------------------------------- */

    SEQ_BEGIN(GRN_BYTES, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, Byte, "Byte", HEX)
    SEQ_END

    SEQ_BEGIN(PROV_BYTES, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, Data, "Data", HEX)
    SEQ_END

    /* --------------------------------------------------------------------- */
    /* Sub blocks */
    /* --------------------------------------------------------------------- */

    /* no info */

    COMMENT(COMMENT_PARAGRAPH,
        "Zero bytes can be used between subblocks as fillers for proper "
        "alignment of the next subblock. They are not included in the number "
        "of subblocks shown in the Blocks field.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_no_info")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_no_info")

    PROPERTY(PROPERTY_SB_LENGTH_MISSING)
    PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)

    SB_BEGIN(GRN_NO_INFO, "", "")
        REFERENCE(8, BE, ID, "Sub Block ID", SB_ID) \
    SB_END

    /* parse error */

    COMMENT(COMMENT_PARAGRAPH,
        "This subblock contains details of WBXML syntax error (in test step).")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_parse_error_info")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_parse_error_info")

    SB_BEGIN(GRN_PARSE_ERROR_INFO, "", "")
        GRN_SB_HDR
        COMMENT(COMMENT_TEXT,
            "The number of WBXML bytes before the erroneous ones, counted "
            "from the first WBXML byte (even in case the WBXML was split "
            "to several messages).")
        VALUE(32, BE, Index, "Index", DEC)
        VALUE_CONST(Code, "Code", GRN_TEST_PARSE_ERRORS)
        VALUE(8, BE, BadByte, "BadByte", HEX)
        FILLER(FILLER_FIXED, 16)
    SB_END

    /* wbxml req -- test step */

    COMMENT(COMMENT_PARAGRAPH, "The length of this subblock can be anything "
    "(whithin limits). Therefore this subblock should be the last, in order "
    "to avoid bad alignment in next subblocks.")
    COMMENT(COMMENT_PARAGRAPH, "Test step is encoded in WBXML. If a test step "
    "is too long for a message, the WBXML encoded test step may be split at "
    "any point and parts be sent in separate messages.")
    COMMENT(COMMENT_PARAGRAPH, "There are various constrains on the WBXML "
    "encoding. The global tokens have their normal encodings that is shown in "
    "the table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_GLOBALS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ", but most of them (marked \"Not used\") shall "
    "not be used. The WBXML header bytes must have values from tables ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_VERSIONS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ", ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_PUBLIC_IDS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ", and ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_CHARSETS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ". The string table shall not be used (so the "
    "length of the string table is zero, and shall be encoded as a single "
    "zero byte. All XML tags shall be encoded by codes shown in the table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_TAGS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ". Tags not shown in the table shall not be "
    "used. First byte of an attribute identifies the label of the attribute "
    "and shall be encoded with a single byte as shown in table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_ATTR_LABELS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ". The first byte shall be followed by the "
    "encoded attribute value (of the appropriate type). The value shall not "
    "be encoded as a string unless it really is a string value. String values "
    "start with the GRN_WBXML_STR_I byte, followed by the string in UTF-8 "
    "encoding, and end with a zero byte. Integer values shall be encoded with "
    "GRN_WBXML_EXT_T_0 byte followed by mb_uint32 encoding of the value. "
    "However, for small values can be encoded with a single byte. Single byte "
    "encodings are shown in the table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_ATTR_VALUES", "", "")
    COMMENT(COMMENT_PARAGRAPH, ". These encodings shall be used for "
    "attributes with a limited set of valid values. More than one byte from "
    "the table shall not be used except for items in capture tag. Attribute "
    "value may be omitted if it is \"yes\" or zero. Tag content can be inner "
    "tags or text but not both. Text is encoded as a single string in the same "
    "way as a string attribute value.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_wbxml_req_info")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_wbxml_req_info")

    PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)

    SB_BEGIN(GRN_WBXML_REQ_INFO, "", "")
        GRN_SB_HDR_WITH_OPTION(GRN_OPTIONS_POLLED)
        SEQ_OF_REF(WbxmlData, "WBXML Data", GRN_BYTES, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_ANYSIZE)
    SB_END

    /* wbxml resp -- test result */

    COMMENT(COMMENT_PARAGRAPH, "The length of this subblock can be anything "
    "(whithin limits). Therefore this subblock should be the last, in order "
    "to avoid bad alignment in next subblocks.")
    COMMENT(COMMENT_PARAGRAPH, "If there is no WBXML result or the index in "
    "request points beyond the end of the WBXML result, this subblock may be "
    "absent or the WBXML Data may have zero length.")

    COMMENT(COMMENT_PARAGRAPH, "Test result encoded in WBXML or part of one. "
    "If the beginning of the WBXML encoded result is absent, this subblock is "
    "preceded by an ")
    COMMENT_LINK(LINK_SUBBLOCK, "GRN_INDEX_INFO", "", "")
    COMMENT(COMMENT_PARAGRAPH, " subblock that indicates how much is missing "
    "from the beginning. Option indicates whether there are more WBXML bytes "
    "after the ones in this block: GRN_OPTION_END means that there are not.")

    COMMENT(COMMENT_PARAGRAPH, "Only a subset of possible WBXML encodings are"
    "used. The global tokens have their normal encodings that is shown in "
    "the table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_GLOBALS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ", but most of them (marked \"Not used\") shall "
    "not be used. The WBXML header has values from tables ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_VERSIONS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ", ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_PUBLIC_IDS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ", and ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_CHARSETS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ". The string table is not used (so the "
    "length of the string table is zero, and is encoded as a single "
    "zero byte. All XML tags are encoded by codes shown in the table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_TAGS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ". Tags not shown in the table are not "
    "used. First byte of an attribute identifies the label of the attribute "
    "as shown in table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_ATTR_LABELS", "", "")
    COMMENT(COMMENT_PARAGRAPH, ". The first byte is followed by the "
    "encoded attribute value (of the appropriate type). The value is not "
    "encoded as a string unless it really is a string value. String values "
    "start with the GRN_WBXML_STR_I byte, followed by the string in UTF-8 "
    "encoding, and end with a zero byte. Integer values are encoded with "
    "GRN_WBXML_EXT_T_0 byte followed by mb_uint32 encoding of the value. "
    "However, for small values can be encoded with a single byte. Single byte "
    "encodings are shown in the table ")
    COMMENT_LINK(LINK_TABLE, "GRN_WBXML_ATTR_VALUES", "", "")
    COMMENT(COMMENT_PARAGRAPH, ". These encodings are used for "
    "attributes with a limited set of valid values. More than one byte from "
    "the table is not used except. Attribute "
    "value may be omitted if it is \"yes\" or zero. Tag content can be inner "
    "tags only or text only or image data only. If the content is text it is "
    "encoded as a single string in the same way as a string attribute value. "
    "Image data (screen image or a part of one) is encoded as opaque data. "
    "The format of the image (including the order of the bytes) is as it is "
    "obtained in screen capture.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_wbxml_resp_info")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_wbxml_resp_info")

    PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)

    SB_BEGIN(GRN_WBXML_RESP_INFO, "", "")
        GRN_SB_HDR_WITH_OPTION(GRN_OPTIONS_END)
        SEQ_OF_REF(WbxmlData, "WBXML Data", GRN_BYTES, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_ANYSIZE)
    SB_END

    /* index */

    COMMENT(COMMENT_PARAGRAPH, "In ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_RESULT_REQ", "", "")
    COMMENT(COMMENT_PARAGRAPH, " message indicates how many bytes shall be "
    "omitted from the beginning of the requested result.")
    COMMENT(COMMENT_PARAGRAPH, "In ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_RESULT_RESP", "", "")
    COMMENT(COMMENT_PARAGRAPH, " message indicates how many bytes are omitted "
    "from the beginning of the WBXML Data of the next subblock. The value in "
    "the response should be the same as in the request; if it is not, the "
    "request can be repeated.")
    COMMENT(COMMENT_PARAGRAPH, "The Index is always the number of WBXML bytes "
    "omitted from the beginning. If the Index is zero or this subblock is not "
    "present at all, that means the beginning of WBXML encoded result.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_index_info")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_index_info")

    SB_BEGIN(GRN_INDEX_INFO, "", "")
        GRN_SB_HDR
        VALUE(32, BE, Index, "Index", DEC)
    SB_END

    /* version */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_version_info")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_version_info")

    SB_BEGIN(GRN_SERVER_VERSION_INFO, "", "")
        GRN_SB_HDR
        COMMENT(COMMENT_TEXT, "Version number see reference ")
        COMMENT_LINK(LINK_NOTE, "/4/", "", "")
        VALUE(8, BE, VersionZZZ, "VersionZZZ", DEC)
        COMMENT(COMMENT_TEXT, "Version number see reference ")
        COMMENT_LINK(LINK_NOTE, "/4/", "", "")
        VALUE(8, BE, VersionYYY, "VersionYYY", DEC)
        COMMENT(COMMENT_TEXT, "Version number see reference ")
        COMMENT_LINK(LINK_NOTE, "/4/", "", "")
        VALUE(8, BE, VersionXXX, "VersionXXX", DEC)
        FILLER(FILLER_FIXED, 8)
    SB_END

    /* server state */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_server_state_info")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_server_state_info")

    SB_BEGIN(GRN_SERVER_STATE_INFO, "", "")
        GRN_SB_HDR
        VALUE_CONST(State, "State", GRN_SERVER_STATE)
        COMMENT(COMMENT_PARAGRAPH,
            "State before phone reset or last ")
        COMMENT_LINK(LINK_MESSAGE, "GRN_CLEAR_REQ", "", "")
        COMMENT(COMMENT_PARAGRAPH,
            " message. In the latter case, state GRN_SERVER_STATE_INACTIVE "
            "means that the phone has rebooted.")
        COMMENT(COMMENT_PARAGRAPH,
            "After the initial start the value is undefined and even illegal "
            "values are possible.")
        VALUE_CONST(OldState, "OldState", GRN_SERVER_STATE)
        COMMENT(COMMENT_PARAGRAPH,
            "Last tag in running.")
        COMMENT(COMMENT_PARAGRAPH,
            "Before the first test case is started the value can be anything.")
        VALUE(16, BE, LatestKnownId, "LatestKnownId", DEC)
        COMMENT(COMMENT_PARAGRAPH,
            "Transaction ID of the last received test or result request, or z"
            "ero.")
        VALUE(8,BE,LastTID,"LastTID",DEC)
        COMMENT(COMMENT_PARAGRAPH,
            "Cause of error. Cleared to GRN_CAUSE_NONE on next ")
        COMMENT_LINK(LINK_MESSAGE, "GRN_CLEAR_REQ", "", "")
        COMMENT(COMMENT_PARAGRAPH,
            " message.")
        PROPERTY_STRING(PROPERTY_ITEM_DEFAULT_VALUE, "GRN_CAUSE_NONE")
        VALUE_CONST(ErrCause, "ErrCause", GRN_CAUSES)
        COMMENT(COMMENT_PARAGRAPH,
            "State of the server when error occurred.")
        VALUE_CONST(ErrState, "ErrState", GRN_SERVER_STATE)
        COMMENT(COMMENT_PARAGRAPH,
            "Transaction ID of the last received test or result request when t"
            "he error occurred, or zero.")
        VALUE(8,BE,ErrTID,"ErrTID",DEC)
    SB_END

    /* GRN_PROVISIONG_DATA */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_provisioning_data")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_provisioning_data")

    /* Force extra byte which can be used for data termination */
    PROPERTY_VALUE(PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE, 5)
    SB_BEGIN(GRN_PROVISIONG_DATA, "", "")
        GRN_SB_HDR
        COMMENT(COMMENT_TEXT, "Length of data is limited to maximum size of this subblock")
    PROPERTY_VALUE(PROPERTY_ARRAY_MAXIMUM_SIZE, MAX_PROVISIONG_DATA)
    SEQ_OF_REF(Data, "Data", PROV_BYTES, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_ANYSIZE)
    SB_END

    /* --------------------------------------------------------------------- */
    /* Messages */
    /* --------------------------------------------------------------------- */

    /* Status query */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_status_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_status_req")

    MSG_BEGIN(GRN_STATUS_REQ, MESSAGE_REQ, "", "")
        GRN_MSG_HDR
    MSG_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_status_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_status_resp")

    MSG_BEGIN(GRN_STATUS_RESP, MESSAGE_RESP, "", "")
        GRN_MSG_HDR
        COMMENT(COMMENT_TEXT, "Interface version number")
        VALUE(8,BE,IFversionZZZ,"IFversionZZZ",DEC)
        COMMENT(COMMENT_TEXT, "Interface version number")
        VALUE(8,BE,IFversionYYY,"IFversionYYY",DEC)
        REFERENCE(8, BE, Blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(GRN_SERVER_VERSION_INFO)
            SB_LST_ENTRY(GRN_SERVER_STATE_INFO)
        SB_LST_REF_END
    MSG_END


    MSG_PAIR(GRN_STATUS_REQ, GRN_STATUS_RESP)


    /* Test step */

    COMMENT(COMMENT_PARAGRAPH,
        "Test step is encoded in WBXML and put in a ")
    COMMENT_LINK(LINK_SUBBLOCK, "GRN_WBXML_REQ_INFO", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " subblock. If the test step is too long for a single message, it can "
        "be split. Each message except the last one must have TRUE in the "
        "Continue field. A response (")
    COMMENT_LINK(LINK_MESSAGE, "GRN_TEST_RESP", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        ") is sent only after the last request message except in case of "
        "error. The server may respond with a notification (")
    COMMENT_LINK(LINK_MESSAGE, "GRN_TEST_NTF", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        ") to each message.")
    COMMENT(COMMENT_PARAGRAPH,
        "This message also means that the results of the previous test step "
        "will not be queried anymore.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_test_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_test_req")

    MSG_BEGIN(GRN_TEST_REQ, MESSAGE_REQ, "", "")
        GRN_MSG_HDR_MULTI
        FILLER(FILLER_FIXED, 16)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, Blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            COMMENT(COMMENT_TEXT, "WBXML encoded test step (or part of one)")
            SB_LST_ENTRY(GRN_WBXML_REQ_INFO)
        SB_LST_REF_END
    MSG_END


    COMMENT(COMMENT_PARAGRAPH,
        "These notifications may be sent as preliminary responses to ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_TEST_REQ", "", "")
    COMMENT(COMMENT_TEXT,
        " requests. Server need not send all notifications. Future versions of server "
        "may send other notifications. Unidentified notifications (content of Notify "
        "field not any of values in ")
    COMMENT_LINK(LINK_TABLE, "GRN_NOTIFICATIONS", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        ") can be ignored.")

    COMMENT(COMMENT_PARAGRAPH,
        "Notifications as specified here have no subblocks. Future versions of "
        "GRANITE server may put subblocks to notifications. Unexpected subblocks can be "
        "ignored.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_test_ntf")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_test_ntf")

    MSG_BEGIN(GRN_TEST_NTF, MESSAGE_NTF, "", "")
        GRN_MSG_HDR_MULTI
        VALUE_CONST(Notify, "Notify", GRN_NOTIFICATIONS)
        FILLER(FILLER_FIXED, 8)
        REFERENCE(8, BE, Blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
        SB_LST_REF_END
    MSG_END


    COMMENT(COMMENT_PARAGRAPH,
        "This message is sent when the requested test step is executed or an "
        "error condition is detected. Error details are given in a subblock "
        "if there was a syntax error in the test request. Otherwise there is "
        "no subblock. The result of the test is not in the message but can be "
        "queried with ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_RESULT_REQ", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " messages.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_test_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_test_resp")

    MSG_BEGIN(GRN_TEST_RESP, MESSAGE_RESP, "", "")
        GRN_MSG_HDR_MULTI
        VALUE_CONST(Response, "Response", OK_FAIL)
        VALUE_CONST(Cause, "Cause", GRN_CAUSES)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, Blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(GRN_PARSE_ERROR_INFO)
        SB_LST_REF_END
    MSG_END


    MSG_PAIR(GRN_TEST_REQ, GRN_TEST_RESP)

    /* test step result */

    COMMENT(COMMENT_PARAGRAPH,
        "After execution of test case the results can be queried with "
        "GRN_RESULT_REQ messages. Result must be queried before any of ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_TEST_REQ", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " or ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_CLEAR_REQ", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " or ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_TERM_REQ", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " message, for any one of these clears the result in the server. "
        "The result or a part of it is returned in a ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_RESULT_RESP", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " message. Several requests may be needed to get all of the result.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_result_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_result_req")

    MSG_BEGIN(GRN_RESULT_REQ, MESSAGE_REQ, "", "")
        GRN_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, Blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(GRN_INDEX_INFO)
        SB_LST_REF_END
    MSG_END


    COMMENT(COMMENT_PARAGRAPH,
        "Result of last test or a part of it. The ")
    COMMENT_LINK(LINK_SUBBLOCK, "GRN_INDEX_INFO", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " subblock (if present) identifies the part. The ")
    COMMENT_LINK(LINK_SUBBLOCK, "GRN_WBXML_RESP_INFO", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " subblock (if present) contains the result in WBXML encoding. The latter "
        "or both subblocks may be absent if there is no result or the result is "
        "so short that the requested part does not exist.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_result_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_result_resp")

    MSG_BEGIN(GRN_RESULT_RESP, MESSAGE_RESP, "", "")
        GRN_MSG_HDR
        VALUE_CONST(Response, "Response", OK_FAIL)
        VALUE_CONST(Cause, "Cause", GRN_CAUSES)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, Blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(GRN_INDEX_INFO)
            SB_LST_ENTRY(GRN_WBXML_RESP_INFO)
        SB_LST_REF_END
    MSG_END


    MSG_PAIR(GRN_RESULT_REQ, GRN_RESULT_RESP)

    /* abort */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_abort_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_abort_req")

    MSG_BEGIN(GRN_ABORT_REQ, MESSAGE_REQ, "", "")
        GRN_MSG_HDR
    MSG_END


    COMMENT(COMMENT_PARAGRAPH,
        "GRANITE server sends this message when it has received an ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_ABORT_REQ", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " message and has aborted the currently executing test case.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_abort_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_abort_resp")

    MSG_BEGIN(GRN_ABORT_RESP, MESSAGE_RESP, "", "")
        GRN_MSG_HDR
        VALUE_CONST(Response, "Response", OK_FAIL)
        VALUE_CONST(Cause, "Cause", GRN_CAUSES)
        FILLER(FILLER_FIXED, 8)
    MSG_END


    MSG_PAIR(GRN_ABORT_REQ, GRN_ABORT_RESP)

    /* termination */

    COMMENT(COMMENT_PARAGRAPH,
        "Indication that test session is over and GRANITE server should release all "
        "resources it may have reserved for execution of tests. In particular, "
        "results of the last test case will not queried anymore.")
    COMMENT_LINK(LINK_MESSAGE, "GRN_CLEAR_REQ", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " message is required before the next test step is sent.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_term_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_term_req")

    MSG_BEGIN(GRN_TERM_REQ, MESSAGE_REQ, "", "")
        GRN_MSG_HDR
    MSG_END

    COMMENT(COMMENT_PARAGRAPH,
        "GRANITE server sends this message when it has received an ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_TERM_REQ", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " message and has terminated.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_term_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_term_resp")

    MSG_BEGIN(GRN_TERM_RESP, MESSAGE_RESP, "", "")
        GRN_MSG_HDR
        VALUE_CONST(Response, "Response", OK_FAIL)
        VALUE_CONST(Cause, "Cause", GRN_CAUSES)
        FILLER(FILLER_FIXED, 8)
    MSG_END


    MSG_PAIR(GRN_TERM_REQ, GRN_TERM_RESP)

    /* activation */

    COMMENT(COMMENT_PARAGRAPH,
        "This message is needed before the server can be given a test step.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_clear_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_clear_req")

    MSG_BEGIN(GRN_CLEAR_REQ, MESSAGE_REQ, "", "")
        GRN_MSG_HDR
    MSG_END


    COMMENT(COMMENT_PARAGRAPH,
        "GRANITE server sends this message when it has received an ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_CLEAR_REQ", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " message and completed clearing. GRANITE server is ready for "
        "the next test step.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_clear_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_clear_resp")

    MSG_BEGIN(GRN_CLEAR_RESP, MESSAGE_RESP, "", "")
        GRN_MSG_HDR
        VALUE_CONST(Response, "Response", OK_FAIL)
        VALUE_CONST(Cause, "Cause", GRN_CAUSES)
        FILLER(FILLER_FIXED, 8)
    MSG_END


    MSG_PAIR(GRN_CLEAR_REQ, GRN_CLEAR_RESP)

    /* test step separation */

    COMMENT(COMMENT_PARAGRAPH,
        "This message is should be used between test cases. The message is si"
        "milar in meaning to ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_CLEAR_REQ", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " message but in addition lets server to delete data structures that "
        "are no more needed in the next test case.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_clear_testcase_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_clear_testcase_req")

    MSG_BEGIN(GRN_CLEAR_TESTCASE_REQ, MESSAGE_REQ, "", "")
        GRN_MSG_HDR
    MSG_END


    COMMENT(COMMENT_PARAGRAPH,
        "GRANITE server sends this message when it has received an ")
    COMMENT_LINK(LINK_MESSAGE, "GRN_CLEAR_TESTCASE_REQ", "", "")
    COMMENT(COMMENT_PARAGRAPH,
        " message and completed clearing. GRANITE server is ready for "
        "the next test step.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_clear_testcase_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_clear_testcase_resp")

    MSG_BEGIN(GRN_CLEAR_TESTCASE_RESP, MESSAGE_RESP, "", "")
        GRN_MSG_HDR
        VALUE_CONST(Response, "Response", OK_FAIL)
        VALUE_CONST(Cause, "Cause", GRN_CAUSES)
        FILLER(FILLER_FIXED, 8)
    MSG_END


    MSG_PAIR(GRN_CLEAR_TESTCASE_REQ, GRN_CLEAR_TESTCASE_RESP)


    /* GRN_RESET_PHONE_REQ */

    COMMENT(COMMENT_PARAGRAPH,
        "This message is used for generating phone resets.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_reset_phone_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_reset_phone_req")

    MSG_BEGIN(GRN_RESET_PHONE_REQ, MESSAGE_REQ, "", "")
        GRN_MSG_HDR
        COMMENT(COMMENT_TEXT, "Reset reason (valid values in hw_power.h)")
        VALUE(8,BE,reset_reason,"reset_reason",DEC)
    MSG_END

    /* GRN_DISPLAY_UPDATE_NTF */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_display_update_ntf")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_display_update_ntf")

    MSG_BEGIN(GRN_DISPLAY_UPDATE_NTF, MESSAGE_NTF, "001.008", "")
        GRN_MSG_HDR
        FILLER(FILLER_FIXED, 8)
		VALUE(16, BE, X, "X", DEC)
		VALUE(16, BE, Y, "Y", DEC)
		VALUE(16, BE, Width, "Width", DEC)
		VALUE(16, BE, Height, "Height", DEC)
        VALUE(16, BE, Fps, "Fps", DEC)
        VALUE(32, BE, TimeStamp, "TimeStamp", DEC)
		COMMENT(COMMENT_TEXT, "Display update notification type")
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, Type, "Display update type", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE)
    MSG_END

    /* GRN_CTC_START_REQ */

    COMMENT(COMMENT_TEXT, "This message is used to start CTC++ coverage measurement.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_ctc_start_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_ctc_start_req")

    MSG_BEGIN(GRN_CTC_START_REQ, MESSAGE_REQ, "001.003", "")
        GRN_MSG_HDR
        /* To make divisible by 4 */
        FILLER(FILLER_FIXED, 16)
        /* CTC data filename */
        COMMENT(COMMENT_PARAGRAPH, "Filename for CTC data")
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, filename, "Filename for CTC data", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE)
        /* If sub block size is dynamic, add this as last element to ensure 
           a length divisible by 4 */
        FILLER(FILLER_VARIABLE, 32)
    MSG_END

    /* GRN_CTC_START_RESP */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_ctc_start_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_ctc_start_resp")

    MSG_BEGIN(GRN_CTC_START_RESP, MESSAGE_RESP, "001.003", "")
        GRN_MSG_HDR
        VALUE_CONST(Response, "Response", OK_FAIL)
    MSG_END

    MSG_PAIR(GRN_CTC_START_REQ, GRN_CTC_START_RESP)

    /* GRN_CTC_STOP_REQ */

    COMMENT(COMMENT_TEXT, "This message is used to stop CTC++ coverage measurement.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_ctc_stop_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_ctc_stop_req")

    MSG_BEGIN(GRN_CTC_STOP_REQ, MESSAGE_REQ, "001.003", "")
        GRN_MSG_HDR
    MSG_END

    /* GRN_CTC_STOP_RESP */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_ctc_stop_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_ctc_stop_resp")

    MSG_BEGIN(GRN_CTC_STOP_RESP, MESSAGE_RESP, "001.003", "")
        GRN_MSG_HDR
        VALUE_CONST(Response, "Response", OK_FAIL)
    MSG_END

    MSG_PAIR(GRN_CTC_STOP_REQ, GRN_CTC_STOP_RESP)

    /* GRN_PROVISIONING_WRITE_REQ */

    COMMENT(COMMENT_TEXT, "This message is used to write Provisioning settings to phone")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_provisioning_write_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_provisioning_write_req")

    MSG_BEGIN(GRN_PROVISIONING_WRITE_REQ, MESSAGE_REQ, "001.005", "")
        GRN_MSG_HDR
        VALUE_CONST(DataType, "Data type", GRN_PROVISIONING_DATA_TYPES)
        VALUE(8, BE, SimID, "SIM ID", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, Blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(GRN_PROVISIONG_DATA)
        SB_LST_REF_END
    MSG_END

    /* GRN_PROVISIONING_WRITE_RESP */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_provisioning_write_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_provisioning_write_resp")

    MSG_BEGIN(GRN_PROVISIONING_WRITE_RESP, MESSAGE_RESP, "001.005", "")
        GRN_MSG_HDR
        VALUE_CONST(Response, "Response", GRN_PROVISIONING_RESPONSE)
        VALUE(16, BE, CC, "Configuration Context", DEC)
    MSG_END

    MSG_PAIR(GRN_PROVISIONING_WRITE_REQ, GRN_PROVISIONING_WRITE_RESP)

    /* GRN_PROVISIONING_SELECT_REQ */

    COMMENT(COMMENT_TEXT, "This message is used to select Provisioning settings")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_provisioning_select_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_provisioning_select_req")

    MSG_BEGIN(GRN_PROVISIONING_SELECT_REQ, MESSAGE_REQ, "001.005", "")
        GRN_MSG_HDR
        VALUE(8, BE, SimID, "SIM ID", DEC)
        VALUE(16, BE, CC, "Configuration Context", DEC)
    MSG_END

    /* GRN_PROVISIONING_SELECT_RESP */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_provisioning_select_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_provisioning_select_resp")

    MSG_BEGIN(GRN_PROVISIONING_SELECT_RESP, MESSAGE_RESP, "001.005", "")
        GRN_MSG_HDR
        VALUE_CONST(Response, "Response", GRN_PROVISIONING_RESPONSE)
    MSG_END

    MSG_PAIR(GRN_PROVISIONING_SELECT_REQ, GRN_PROVISIONING_SELECT_RESP)

    /* GRN_PROVISIONING_DELETE_REQ */

    COMMENT(COMMENT_TEXT, "This message is used to delete one or all Provisioning settings")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_provisioning_delete_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_provisioning_delete_req")

    MSG_BEGIN(GRN_PROVISIONING_DELETE_REQ, MESSAGE_REQ, "001.005", "")
        GRN_MSG_HDR
        COMMENT(COMMENT_PARAGRAPH, "Priority order: Delete all, SimID, CC\n")
        COMMENT(COMMENT_PARAGRAPH, "E.g. to delete by CC")
        COMMENT(COMMENT_PARAGRAPH, "DeleteAll -> FALSE, SimID -> 0, CC -> 'desired CC'")
        VALUE_CONST(DeleteAll, "Delete all?", TRUE_FALSE)
        VALUE(16, BE, CC, "Configuration Context", DEC)
        VALUE(8, BE, SimID, "SIM ID", DEC)
    MSG_END

    /* GRN_PROVISIONING_DELETE_RESP */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_provisioning_delete_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_provisioning_delete_resp")

    MSG_BEGIN(GRN_PROVISIONING_DELETE_RESP, MESSAGE_RESP, "001.005", "")
        GRN_MSG_HDR
        VALUE_CONST(Response, "Response", GRN_PROVISIONING_RESPONSE)
    MSG_END

    MSG_PAIR(GRN_PROVISIONING_DELETE_REQ, GRN_PROVISIONING_DELETE_RESP)

    /* GRN_PROVISIONING_READ_REQ */

    COMMENT(COMMENT_TEXT, "This message is read Provisioning settings from phone.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_provisioning_read_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_provisioning_read_req")

    MSG_BEGIN(GRN_PROVISIONING_READ_REQ, MESSAGE_REQ, "001.005", "")
        GRN_MSG_HDR
        VALUE(8, BE, SimID, "SIM ID", DEC)
        VALUE(16, BE, CC, "Configuration Context", DEC)
        VALUE_CONST(DataType, "Data type", GRN_PROVISIONING_DATA_TYPES)
    MSG_END

    /* GRN_PROVISIONING_READ_RESP */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGRN_provisioning_read_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "SIZE_tGRN_provisioning_read_resp")

    /* Force extra byte for failure cases */
    PROPERTY_VALUE(PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE, 9)

    MSG_BEGIN(GRN_PROVISIONING_READ_RESP, MESSAGE_RESP, "001.005", "")
        GRN_MSG_HDR
        VALUE_CONST(Response, "Response", GRN_PROVISIONING_RESPONSE)
        FILLER(FILLER_FIXED, 8)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, Blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(GRN_PROVISIONG_DATA)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(GRN_PROVISIONING_READ_REQ, GRN_PROVISIONING_READ_RESP)

RES_END


/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */


#endif /* _GRN_ISI_M_H_ */


/* End of file granite_isi_m.h */

