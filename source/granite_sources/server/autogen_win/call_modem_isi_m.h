/*
NOKIA
Oulu
D RD WM MACN










            call_modem_isi_m.h
            --------------------------

            SW include - ANSI C





Continuus Ref:
--------------
database:           ou1gif

project path:       global_interface/mrsw_interface/mrsw_public

name:               call_modem_isi_m.h

instance:           ou_cs#1

Copyright(c)Nokia. All rights reserved.



Change history:

VERSION     : 030.002    APPROVED  13-Oct-2010  Mika Leppanen
REASON      : Inspection
REFERENCE   : ADB for SWAM inspection ID: ML10100647928
DESCRIPTION : Corrected inspection defects.

VERSION     : 030.001    DRAFT     21-Sep-2010  Mika Leppanen
REASON      : New feature
REFERENCE   : RM RIM SUB ID: 417-75797 AT+CTFR CALL DEFLECTION
DESCRIPTION : Added support for Call Deflection. Corrected specification
              defects.

VERSION     : 030.000    APPROVED  20-Apr-2010  Mika Leppanen
REASON      : New feature
REFERENCE   : RM RIM REQ ID: 417-66370:WGE IO:SR-VCC EUTRAN -> GERAN
              RM-RIM REQ ID: 417-66371: WGE IO: SR-VCC EUTRAN -> UTRAN
              ADB for SWAM inspection ID: ML10041345405
DESCRIPTION : Added support for SRVCC.

VERSION     : 002.007    DRAFT     19-Apr-2010  Mika Leppanen
REASON      : Corrections
REFERENCE   : ADB for SWAM inspection ID: ML10041344346
DESCRIPTION : Approved in inspection.

VERSION     : 002.006    DRAFT     06-Apr-2010  Mika Leppanen
REASON      : Corrections
REFERENCE   : ADB for SWAM CR ID: ML10040137193
DESCRIPTION : Corrected specification defects.

VERSION     : 002.005    APPROVED  14-Dec-2009  Mika Leppanen
REASON      : Correction
REFERENCE   : ADB for SWAM inspection ID: ML09121440932
DESCRIPTION : Corrected 3GPP references.

VERSION     : 002.004    APPROVED  26-Nov-2009  Mika Leppanen
REASON      : Inspection
REFERENCE   : ADB for SWAM inspection ID: ML09112053316
DESCRIPTION : Approved in inspection.

VERSION     : 002.003    DRAFT     09-Nov-2009  Mika Leppanen
REASON      : New feature
REFERENCE   : RM RIM REQ ID: 417-54415 Emergency category support
              without SIM card
DESCRIPTION : Added support for permanent memory emergency numbers.
              Also made corrections and updates to specification.

VERSION     : 002.002    APPROVED  12-May-2009  Mika Leppanen
REASON      : Correction
REFERENCE   : -
DESCRIPTION : Changed ISI version defines.

VERSION     : 002.001    APPROVED  29-Apr-2009  Mika Leppanen
REASON      : Inspection
REFERENCE   : ADB for SWAM inspection ID: ML09042747666
DESCRIPTION : Inspection defects corrected.

VERSION     : 002.000    DRAFT     14-Apr-2009  Mika Leppanen
REASON      : Corrections
REFERENCE   : ADB for SWAM change request ID: ML09041542192
DESCRIPTION : Corrections and updates to specification.

VERSION     : 001.004    APPROVED  17-Oct-2008  Mika Leppanen
REASON      : Inspection
REFERENCE   : ADB for SWAM inspection ID: ML08101343164
DESCRIPTION : Inspection defects corrected.

VERSION     : 001.003    DRAFT     22-Sep-2008  Mika Leppanen
REASON      : Corrections
REFERENCE   : ADB for Wireless Modem ID: ML08022739068
DESCRIPTION : Corrections and updates to specification.

VERSION     : 001.002.1  APPROVED  28-May-2008  Timo Ketara
REASON      : First release of the Modem ISI specs to licensees
REFERENCE   : Inspection in ADB for SWAM TK08052757470
DESCRIPTION : File paths changed to match the new GIF structure.
              The generating of 16 bit header file removed.

VERSION     : 001.002    APPROVED  09-Apr-2008  Mika Leppanen
REASON      : Inspection
REFERENCE   : ADB for SWAM inspection ID: ML08032837180
DESCRIPTION : Inspection defects corrected.

VERSION     : 001.001    DRAFT     26-Mar-2008  Mika Leppanen
REASON      : Document created
REFERENCE   : RM-RIM SUB 414-4198
DESCRIPTION : Created first version of Modem Call Server interface 
              specification.

*/


/* ------------------------------------------------------------------------- */


/*  1    ABSTRACT

    1.1    Module type

    Header file for the ISI Autogeneration Application
   

    1.2    Functional description

    This file is the message definition file for the Modem Call Server


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

#ifdef DO_VENDOR_OUTPUT
PROPERTY(PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT)
#endif /* DO_VENDOR_OUTPUT */

/* Message ID's */

#define CALL_MODEM_CREATE_REQ                     0x01
#define CALL_MODEM_CREATE_RESP                    0x02
#define CALL_MODEM_COMING_IND                     0x03
#define CALL_MODEM_MO_ALERT_IND                   0x04
#define CALL_MODEM_MT_ALERT_IND                   0x05
#define CALL_MODEM_WAITING_IND                    0x06
#define CALL_MODEM_ANSWER_REQ                     0x07
#define CALL_MODEM_ANSWER_RESP                    0x08
#define CALL_MODEM_RELEASE_REQ                    0x09
#define CALL_MODEM_RELEASE_RESP                   0x0A
#define CALL_MODEM_RELEASE_IND                    0x0B
#define CALL_MODEM_TERMINATED_IND                 0x0C
#define CALL_MODEM_STATUS_REQ                     0x0D
#define CALL_MODEM_STATUS_RESP                    0x0E
#define CALL_MODEM_STATUS_IND                     0x0F
#define CALL_MODEM_PRESENT_IND                    0x10
#define CALL_MODEM_CONTROL_REQ                    0x11
#define CALL_MODEM_CONTROL_RESP                   0x12
#define CALL_MODEM_CONTROL_IND                    0x13
#define CALL_MODEM_DTMF_SEND_REQ                  0x17
#define CALL_MODEM_DTMF_SEND_RESP                 0x18
#define CALL_MODEM_DTMF_STOP_REQ                  0x19
#define CALL_MODEM_DTMF_STOP_RESP                 0x1A
#define CALL_MODEM_DTMF_STATUS_IND                0x1B
#define CALL_MODEM_DTMF_TONE_IND                  0x1C
#define CALL_MODEM_RECONNECT_IND                  0x1E
#define CALL_MODEM_PROPERTY_GET_REQ               0x1F
#define CALL_MODEM_PROPERTY_GET_RESP              0x20
#define CALL_MODEM_PROPERTY_SET_REQ               0x21
#define CALL_MODEM_PROPERTY_SET_RESP              0x22
#define CALL_MODEM_PROPERTY_SET_IND               0x23
#define CALL_MODEM_EMERG_NBR_MODIFY_REQ           0x24
#define CALL_MODEM_EMERG_NBR_MODIFY_RESP          0x25
#define CALL_MODEM_EMERG_NBR_GET_REQ              0x26
#define CALL_MODEM_EMERG_NBR_GET_RESP             0x27
#define CALL_MODEM_EMERG_NBR_CHECK_REQ            0x28
#define CALL_MODEM_EMERG_NBR_CHECK_RESP           0x29
#define CALL_MODEM_EMERG_NBR_IND                  0x31
#define CALL_MODEM_SERVICE_DENIED_IND             0x32
#define CALL_MODEM_USER_CONNECT_IND               0x33
#define CALL_MODEM_RELEASE_END_REQ                0x34
#define CALL_MODEM_RELEASE_END_RESP               0x35
#define CALL_MODEM_NOTIFICATION_IND               0xA0
#define CALL_MODEM_BLACKLIST_CLEAR_REQ            0xA4
#define CALL_MODEM_BLACKLIST_CLEAR_RESP           0xA5
#define CALL_MODEM_BLACKLIST_TIMER_IND            0xA6

#ifndef DO_VENDOR_OUTPUT
#define CALL_MODEM_RAB_IND                        0xA8
#endif /* !DO_VENDOR_OUTPUT */

#define CALL_MODEM_BC_GET_REQ                     0xAA
#define CALL_MODEM_BC_GET_RESP                    0xAB
#define CALL_MODEM_BC_CHECK_REQ                   0xAC
#define CALL_MODEM_BC_CHECK_RESP                  0xAD
#define CALL_MODEM_SS_DATA_IND                    0xAF
#define CALL_MODEM_RESOURCE_IND                   0x40
#define CALL_MODEM_RESOURCE_REQ                   0x41
#define CALL_MODEM_RESOURCE_RESP                  0x42
#define CALL_MODEM_RESOURCE_CLEAR_IND             0x43
#define CALL_MODEM_RESOURCE_CONF_REQ              0x44
#define CALL_MODEM_RESOURCE_CONF_RESP             0x45
#define CALL_MODEM_RESOURCE_CONF_IND              0x46
#define CALL_MODEM_TERMINATE_REQ                  0x47
#define CALL_MODEM_TERMINATE_RESP                 0x48
#define CALL_MODEM_NETWORK_CONN_IND               0x49
#define CALL_MODEM_VCC_STATUS_IND                 0x4A
#define CALL_MODEM_VCC_STATUS_REQ                 0x4B
#define CALL_MODEM_VCC_STATUS_RESP                0x4C
#define CALL_MODEM_VCC_STATUS_CLEAR_IND           0x4D
#define CALL_MODEM_COMB_STATUS_IND                0x4E
#define CALL_MODEM_BLACKLIST_BLOCKED_IND          0x4F
#define CALL_MODEM_MESSAGE_IND                    0x50

/* Sub block ID's */

#define CALL_MODEM_SB_ORIGIN_ADDRESS                 0x01
#define CALL_MODEM_SB_ORIGIN_SUBADDRESS              0x02
#define CALL_MODEM_SB_DESTINATION_ADDRESS            0x03
#define CALL_MODEM_SB_DESTINATION_SUBADDRESS         0x04
#define CALL_MODEM_SB_DESTINATION_PRE_ADDRESS        0x05
#define CALL_MODEM_SB_DESTINATION_POST_ADDRESS       0x06
#define CALL_MODEM_SB_MODE                           0x07
#define CALL_MODEM_SB_CAUSE                          0x08
#define CALL_MODEM_SB_OPERATION                      0x09
#define CALL_MODEM_SB_STATUS                         0x0A
#define CALL_MODEM_SB_STATUS_INFO                    0x0B
#define CALL_MODEM_SB_ALERTING_INFO                  0x0C
#define CALL_MODEM_SB_RELEASE_INFO                   0x0D
#define CALL_MODEM_SB_ORIGIN_INFO                    0x0E
#define CALL_MODEM_SB_DTMF_DIGIT                     0x0F
#define CALL_MODEM_SB_DTMF_STRING                    0x10
#define CALL_MODEM_SB_DTMF_STATUS                    0x11
#define CALL_MODEM_SB_DTMF_TONE                      0x12
#define CALL_MODEM_SB_PROPERTY_INFO                  0x13
#define CALL_MODEM_SB_EMERG_NUMBER                   0x14
#define CALL_MODEM_SB_DESTINATION_CS_ADDRESS         0x16
#define CALL_MODEM_SB_STATE_AUTO_CHANGE              0x18
#define CALL_MODEM_SB_DTMF_BCD_STRING                0x19
#define CALL_MODEM_SB_DTMF_INFO                      0x1A
#define CALL_MODEM_SB_EMERG_NUMBER_INFO              0x1B
#define CALL_MODEM_SB_STATUS_MODE                    0x1C
#define CALL_MODEM_SB_ADDR_AND_STATUS_INFO           0x1D
#define CALL_MODEM_SB_DTMF_TIMERS                    0x1E

#ifndef DO_VENDOR_OUTPUT
#define CALL_MODEM_SB_NAS_SYNC_INDICATOR             0x1F
#endif /* !DO_VENDOR_OUTPUT */

#define CALL_MODEM_SB_NW_CAUSE                       0x20
#define CALL_MODEM_SB_DESTINATION_ISI_ADDRESS        0x23
#define CALL_MODEM_SB_CONNECTED_ADDRESS              0x24
#define CALL_MODEM_SB_CONNECTED_SUBADDRESS           0x25

#define CALL_MODEM_SB_CHECK_INFO                     0x40
#define CALL_MODEM_SB_RESOURCE                       0x41
#define CALL_MODEM_SB_RESOURCE_CONF                  0x42
#define CALL_MODEM_SB_RESOURCE_CONF_REQUIRED         0x43
#define CALL_MODEM_SB_RESOURCE_SEQ_ID                0x44
#define CALL_MODEM_SB_RESOURCE_STATUS                0x45
#define CALL_MODEM_SB_RESOURCE_CHECK_INFO            0x46
#define CALL_MODEM_SB_LINE_ID                        0x47
#define CALL_MODEM_SB_USER_TO_USER                   0x48
#define CALL_MODEM_SB_MSG_INFO                       0x49
#define CALL_MODEM_SB_ORIGIN_CS_ADDRESS              0x4A
#define CALL_MODEM_SB_REQ_INFO                       0x4B
#define CALL_MODEM_SB_EMERG_NUMBER_MOD_INFO          0x4C

#define CALL_MODEM_SB_CUG_INFO                       0xA0
#define CALL_MODEM_SB_ALERTING_PATTERN               0xA1
#define CALL_MODEM_SB_REDIRECTING_ADDRESS            0xA4
#define CALL_MODEM_SB_REDIRECTING_SUBADDRESS         0xA5
#define CALL_MODEM_SB_REMOTE_ADDRESS                 0xA6
#define CALL_MODEM_SB_REMOTE_SUBADDRESS              0xA7
#define CALL_MODEM_SB_USER_TO_USER_INFO              0XA8
#define CALL_MODEM_SB_DIAGNOSTICS                    0xA9
#define CALL_MODEM_SB_SS_DIAGNOSTICS                 0xAA
#define CALL_MODEM_SB_NEW_DESTINATION                0xAB
#define CALL_MODEM_SB_NOTIFY                         0xB1
#define CALL_MODEM_SB_SS_NOTIFY                      0xB2
#define CALL_MODEM_SB_SS_CODE                        0xB3
#define CALL_MODEM_SB_SS_STATUS                      0xB4
#define CALL_MODEM_SB_SS_NOTIFY_INDICATOR            0xB5
#define CALL_MODEM_SB_SS_HOLD_INDICATOR              0xB6
#define CALL_MODEM_SB_SS_ECT_INDICATOR               0xB7

#ifndef DO_VENDOR_OUTPUT
#define CALL_MODEM_SB_RAB_INFO                       0xB9
#endif /* !DO_VENDOR_OUTPUT */

#define CALL_MODEM_SB_BC                             0xBA
#define CALL_MODEM_SB_CAUSE_OF_NO_CLI                0xBC
#define CALL_MODEM_SB_MM_CAUSE                       0xBD
#define CALL_MODEM_SB_DETAILED_CAUSE                 0xBF
#define CALL_MODEM_SB_SS_DATA                        0xC0
#define CALL_MODEM_SB_ALS_INFO                       0xC1
#define CALL_MODEM_SB_VCC_STATUS_INFO                0xC2


/* Constants */

#define CALL_MODEM_CUG_DEFAULT                    0xFFFF
#define CALL_MODEM_DTMF_DEFAULT                   0x00
#define CALL_MODEM_DTMF_NO_DELAY                  0x01
#define CALL_MODEM_INDEX_NOT_VALID                0x00
#define CALL_MODEM_NUMBER_TYPE_NONE               0x00
#define CALL_MODEM_NUMBER_GROUP_NONE              0x00
#define CALL_MODEM_NO_LINK_ID                     0x00
#define CALL_MODEM_NULL                           0x00

/*  4    MACROS */

#ifndef MODEM_CALL_ISI_VERSION
#define MODEM_CALL_ISI_VERSION
#define MODEM_CALL_ISI_VERSION_Z        30
#define MODEM_CALL_ISI_VERSION_Y        2
#endif

/* these macros are redefined versions of the COMMON macros defined
   in isi_macros.h. These local versions are needed in order to
   generate a back-ward compatible header file 
*/

#define CALL_MODEM_COMMON_MSG_HDR \
    VALUE(8, BE, tr_id, "Transaction ID", DEC) \
    REFERENCE(8, BE, message_id, "Message ID", MSG_ID)

/* This string property determines from which version of the resource, */
/* version history will be auto-generated. Value of 255.255 should prevent */
/* it altogether for time being. */
PROPERTY_STRING(PROPERTY_ISI_VERSION_AUTO_GENERATE, "001.001")

/* --------------------------------------------------------------------- */
/* Project / Document information */
/* --------------------------------------------------------------------- */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME, "Oulu")
PROPERTY_STRING(PROPERTY_PROJECT_NAME, "D RD WM MACN")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME, "Mika Leppanen")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY, "CONFIDENTIAL")

/*PROPERTY_STRING(PROPERTY_ISIHDR_TITLE, "")*/

#ifdef DO_VENDOR_OUTPUT
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME, "call_wm_isi.h")
#else /* DO_VENDOR_OUTPUT */
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME, "call_modem_isi.h")
#endif /* DO_VENDOR_OUTPUT */

PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB, "ou1gif")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH, 
    "global_interface/mrsw_interface/mrsw_public")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME, "ou_cs#1")

PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB, "ou1gif")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME, "GIF_SPECS")
PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH, 
    "GIF_SPECS/MultiradioSW/mrsw_public_spec")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER, "-")

#ifdef DO_VENDOR_OUTPUT
PROPERTY_STRING(PROPERTY_HTML_FILENAME, "i_call_wm_isi_m.html")
#else /* DO_VENDOR_OUTPUT */
PROPERTY_STRING(PROPERTY_HTML_FILENAME, "i_call_modem_isi_m.html")
#endif /* DO_VENDOR_OUTPUT */

PROPERTY_STRING(PROPERTY_HTML_TITLE, "ISI Modem Call Server Message Descriptions")

PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

    /* --------------------------------------------------------------------- */
    /* Introduction */
    /* --------------------------------------------------------------------- */

    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)

    COMMENT(COMMENT_PARAGRAPH,
        "The purpose of this document is to specify the ISI messages for "
        "Modem Call Server.")
    COMMENT(COMMENT_NEWLINE,   "")
    COMMENT(COMMENT_PARAGRAPH,
        "The features for this server are defined in the feature specification "
        "document for this server (see reference ")
    COMMENT_LINK(LINK_NOTE, "/1/", "", "")
    COMMENT(COMMENT_TEXT,
        ") and the common feature specification document (see reference ")
    COMMENT_LINK(LINK_NOTE, "/2/", "", "")
    COMMENT(COMMENT_PARAGRAPH, ").")
    COMMENT(COMMENT_NEWLINE,   "")
    COMMENT(COMMENT_PARAGRAPH,
        "This html document has been created from call_modem_isi_m.h message "
        "definition file with Autogen. High level pseudo code has been used in "
        "descriping the functionalty of some messages and subblocks.")

    /* CALL_ISI */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define CALL_MODEM_SRV_ISI_HEADER \\")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    byte    tr_id; \\")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    byte    message_id; \\")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    byte    call_id; \\")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    byte    sub_blocks;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    CALL_MODEM_SRV_ISI_HEADER")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } CALL_MODEM_ISI_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")

    /* GENERIC HEADERS */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8    tr_id;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8    message_id;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8    request;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8    data;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } CALL_MODEM_SRV_REQ;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8    tr_id;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8    message_id;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8    response;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8    data;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } CALL_MODEM_SRV_RESP;")


RES_BEGIN(RESOURCE_ISI, PN_MODEM_CALL, MODEM_CALL, "Modem Call Server", 
    RES_VERSION_STRING(MODEM_CALL_ISI_VERSION_Z, MODEM_CALL_ISI_VERSION_Y), TRUE)    

    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Inspection")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "ADB for SWAM inspection ID: ML10100647928")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "APPROVED")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "13-Oct-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Corrected inspection defects.")
    ISI_VERSION_HISTORY("030.002")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "New feature")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "RM RIM SUB ID: 417-75797 AT+CTFR CALL DEFLECTION")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "21-Sep-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Added support for Call Deflection. "
        "Corrected specification defects.")
    ISI_VERSION_HISTORY("030.001")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "New feature")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "RM RIM REQ ID: 417-66370:WGE IO:SR-VCC EUTRAN -> GERAN")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "RM-RIM REQ ID: 417-66371: WGE IO: SR-VCC EUTRAN -> UTRAN")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "ADB for SWAM inspection ID: ML10041345405")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "APPROVED")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "20-Apr-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Added support for SRVCC.")
    ISI_VERSION_HISTORY("030.000")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Inspection")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "ADB for SWAM inspection ID: ML10041344346")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "APPROVED")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "19-Apr-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Approved in inspection.")
    ISI_VERSION_HISTORY("002.007")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Corrections")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "ADB for SWAM CR ID: ML10040137193")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "06-Apr-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Corrected specification defects.")
    ISI_VERSION_HISTORY("002.006")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Correction")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "ADB for SWAM inspection ID: ML09121440932")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "APPROVED")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "14-Dec-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Corrected 3GPP references.")
    ISI_VERSION_HISTORY("002.005")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Inspection")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "ADB for SWAM inspection ID: ML09112053316")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "APPROVED")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "26-Nov-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Approved in inspection.")
    ISI_VERSION_HISTORY("002.004")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "New feature")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "RM RIM REQ ID: 417-54415 Emergency category support without SIM "
        "card")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "09-Nov-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Added support for permanent memory emergency numbers. "
        "Also made corrections and updates to specification.")
    ISI_VERSION_HISTORY("002.003")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Correction")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "APPROVED")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "12-May-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Changed ISI version defines.")

    ISI_VERSION_HISTORY("002.002")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Inspection")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "ADB for SWAM inspection ID: ML09042747666")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "APPROVED")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "29-Apr-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Inspection defects corrected.")

    ISI_VERSION_HISTORY("002.001")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Corrections")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "ADB for SWAM change request ID: ML09041542192")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "14-Apr-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Corrections and updates to specification.")

    ISI_VERSION_HISTORY("002.000")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Inspection")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "ADB for SWAM inspection ID: ML08101343164")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "APPROVED")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "17-Oct-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Corrections and updates to specification. ")

    ISI_VERSION_HISTORY("001.004")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Corrections")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "ADB for Wireless Modem ID: ML08022739068")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "22-Sep-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Corrections and updates to specification. ")

    ISI_VERSION_HISTORY("001.003")


    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Inspection")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, 
        "ADB for SWAM inspection ID: ML08032837180")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "APPROVED")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "09-Apr-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Inspection defects corrected.")
    ISI_VERSION_HISTORY("001.002")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Document created")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM SUB 414-4198")

    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "26-Mar-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Leppanen")
    COMMENT(COMMENT_TEXT,
        "Created first version of Modem Call Server interface specification.")
    ISI_VERSION_HISTORY("001.001")

    /* --------------------------------------------------------------------- */
    /* Messages */
    /* --------------------------------------------------------------------- */

    /* Constants */

    COMMENT(COMMENT_PARAGRAPH, "Value: 0xFFFF")
    CONSTANT(CALL_MODEM_CUG_DEFAULT, 0xFFFF)

    COMMENT(COMMENT_PARAGRAPH, "Value: 0x0070")
    CONSTANT(CALL_MODEM_DTMF_P_DIGIT, 0x0070)

    COMMENT(COMMENT_PARAGRAPH, "Value: 0x0077")
    CONSTANT(CALL_MODEM_DTMF_W_DIGIT, 0x0077)

    COMMENT(COMMENT_PARAGRAPH, "Value: 0x0000")
    CONSTANT(CALL_MODEM_DTMF_NO_TONE, 0x0000)

    COMMENT(COMMENT_PARAGRAPH, "Value: 0x00")
    CONSTANT(CALL_MODEM_NO_LINK_ID, 0x00)

    COMMENT(COMMENT_PARAGRAPH, "Value: 0x00")
    CONSTANT(CALL_MODEM_DTMF_DEFAULT, 0x00)

    COMMENT(COMMENT_PARAGRAPH, "Value: 0x01")
    CONSTANT(CALL_MODEM_DTMF_NO_DELAY, 0x01)

    COMMENT(COMMENT_PARAGRAPH, "Value: 0x00")
    CONSTANT_VER(CALL_MODEM_NULL, 0x00, "002.003", "")

    COMMENT(COMMENT_PARAGRAPH, "Obsolete value")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONSTANT(CALL_MODEM_STATUS_SWAP_INITIATED, 0x10)

    COMMENT(COMMENT_PARAGRAPH, "Obsolete value")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONSTANT(CALL_MODEM_SSC_CLIP, 0x001E)

    COMMENT(COMMENT_PARAGRAPH, "Obsolete value")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONSTANT(CALL_MODEM_SSC_COLP, 0x004C)

    COMMENT(COMMENT_PARAGRAPH, "Obsolete value")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONSTANT(CALL_MODEM_SSC_COLR, 0x004D)

    COMMENT(COMMENT_PARAGRAPH, "Obsolete value")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONSTANT(CALL_MODEM_SSC_CNAP, 0x012C)

    COMMENT(COMMENT_PARAGRAPH, "Obsolete value")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONSTANT(CALL_MODEM_MODE_ORIGINATOR,  0x01)

    /* Constant tables */

    COMMENT(COMMENT_PARAGRAPH,
        "Address type consists of numbering plan and type of address. The "
        "four least significant bits (1-4) contain numbering plan and the "
        "next three bits (5-7) contain type of number. "
        "See 'Called Party BCD Number IE' in 3GPP TS 24.008 ch. 10.5.4.7. "
        "Field contains values from octet 3 of address IE.")
    BIT_TBL_BEGIN(CALL_MODEM_ADDRESS_TYPE, 8, BE, "", "")
        BIT_TBL_ENTRY("XXXX0000", CALL_MODEM_NBR_PLAN_UNKNOWN,            "")
        BIT_TBL_ENTRY("XXXX0001", CALL_MODEM_NBR_PLAN_ISDN_TELEPHONY,     "")
        BIT_TBL_ENTRY("XXXX0011", CALL_MODEM_NBR_PLAN_DATA,               "")
        BIT_TBL_ENTRY("XXXX0100", CALL_MODEM_NBR_PLAN_TELEX,              "")
        BIT_TBL_ENTRY("XXXX1001", CALL_MODEM_NBR_PLAN_PRIVATE,            "")
        BIT_TBL_ENTRY("XXXX1000", CALL_MODEM_NBR_PLAN_NATIONAL,           "")

        BIT_TBL_ENTRY("X000XXXX", CALL_MODEM_NBR_TYPE_UNKNOWN,            "")
        BIT_TBL_ENTRY("X001XXXX", CALL_MODEM_NBR_TYPE_INTERNATIONAL,      "")
        BIT_TBL_ENTRY("X010XXXX", CALL_MODEM_NBR_TYPE_NATIONAL,           "")
        BIT_TBL_ENTRY("X011XXXX", CALL_MODEM_NBR_TYPE_NETWORK_SPECIFIC,   "")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
        "Presentation and screening indicators are coded into one byte. "
        "The two least significant bits (1-2) contain screening  "
        "indicator and the two bits (6-7) contain presenation indicator. "
        "See 'Calling Party BCD Number IE' in 3GPP TS 24.008 ch. 10.5.4.9. "
        "Field contains values from octet 3a of address IE.")
    BIT_TBL_BEGIN(CALL_MODEM_PRESENTATION_SCREEN_INDICATOR, 8, BE, "", "")
        BIT_TBL_ENTRY("X00XXXXX", CALL_MODEM_PRESENTATION_ALLOWED,        "")
        BIT_TBL_ENTRY("X01XXXXX", CALL_MODEM_PRESENTATION_RESTRICTED,     "")
        BIT_TBL_ENTRY("X10XXXXX", CALL_MODEM_PRESENTATION_UNAVAILABLE,    "")

        BIT_TBL_ENTRY("XXXXXX00", CALL_MODEM_USER_NOT_SCREENED,           "")
        BIT_TBL_ENTRY("XXXXXX01", CALL_MODEM_USER_SCREENED_PASSED,        "")
        BIT_TBL_ENTRY("XXXXXX10", CALL_MODEM_USER_SCREENED_FAILED,        "")
        BIT_TBL_ENTRY("XXXXXX11", CALL_MODEM_SCREEN_NETW_PROVIDED,        "")
    BIT_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_MODE, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_MODE_EMERGENCY,                    0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_MODE_SPEECH,                       0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_MODE_ALS_LINE_2,                   0xA2, "")
        CONST_TBL_ENTRY(CALL_MODEM_MODE_MULTIMEDIA,                   0xA3, "")
    CONST_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
        "When B0 is set to '0' it indicates a local origination i.e. call "
        "is mobile originated and when set to '1' it indicates a remote "
        "origination i.e. call is mobile terminated. Clients shall set "
        "the value to '0' when sending requests to Modem Call Server. ")
    BIT_TBL_BEGIN(CALL_MODEM_MODE_INFO, 8, BE, "", "")
    BIT_TBL_ENTRY("XXXXXXX0", CALL_MODEM_MODE_LOCAL_ORIGINATOR, "")
    BIT_TBL_ENTRY("XXXXXXX1", CALL_MODEM_MODE_REMOTE_ORIGINATOR, "")
    BIT_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_UUS_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_UUS_TYPE_UUS1,                   0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_UUS_ACTIVATION_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_UUS_ACTIVATION_IMPLICIT,         0x01, "")
    CONST_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
        "NOTE: Call ID values in range 1-7 are used dynamically as unique"
        " call IDs when referencing to a specific call.")
    BIT_TBL_BEGIN(CALL_MODEM_ID, 8, BE, "", "")
        BIT_TBL_ENTRY("xxxxx000", CALL_MODEM_ID_NONE,                  "")
        BIT_TBL_ENTRY("xxxxx001", CALL_MODEM_ID_1,                     "")
        BIT_TBL_ENTRY("xxxxx010", CALL_MODEM_ID_2,                     "")
        BIT_TBL_ENTRY("xxxxx011", CALL_MODEM_ID_3,                     "")
        BIT_TBL_ENTRY("xxxxx100", CALL_MODEM_ID_4,                     "")
        BIT_TBL_ENTRY("xxxxx101", CALL_MODEM_ID_5,                     "")
        BIT_TBL_ENTRY("xxxxx110", CALL_MODEM_ID_6,                     "")
        BIT_TBL_ENTRY("xxxxx111", CALL_MODEM_ID_7,                     "")
        BIT_TBL_ENTRY("xxx1xxxx", CALL_MODEM_ID_CONFERENCE,            "")
        BIT_TBL_ENTRY("xx1xxxxx", CALL_MODEM_ID_WAITING,               "")
        BIT_TBL_ENTRY("x1xxxxxx", CALL_MODEM_ID_HOLD,                  "")
        BIT_TBL_ENTRY("1xxxxxxx", CALL_MODEM_ID_ACTIVE,                "")
        BIT_TBL_ENTRY("1111xxxx", CALL_MODEM_ID_ALL,                   "")
    BIT_TBL_END

    BIT_TBL_BEGIN(CALL_MODEM_CAUSE_TYPE_SENDER, 8, BE, "030.001", "")
        COMMENT(COMMENT_PARAGRAPH,
            "Client cause value. Clients shall use this value or "
            "network type in call release requests that are sent "
            "to Call Server.")
        BIT_TBL_ENTRY("xxxx0001", CALL_MODEM_CAUSE_TYPE_CLIENT,        "")
        COMMENT(COMMENT_PARAGRAPH,
            "Call Server cause value. Clients shall not use this value "
            "in requests that are sent to Call Server.")
        BIT_TBL_ENTRY("xxxx0010", CALL_MODEM_CAUSE_TYPE_SERVER,        "")
        COMMENT(COMMENT_PARAGRAPH,
            "Network interface cause value. Clients shall use this "
            "value or client type in call release requests that are "
            "sent to Call Server.")
        BIT_TBL_ENTRY("xxxx0011", CALL_MODEM_CAUSE_TYPE_NETWORK,      "")
    BIT_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_CAUSE_TYPE_SENDER, 4, BE, "", "030.001")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_TYPE_CLIENT,             0x01, 
            "Client cause value. Clients shall use this value or "
            "network type in call release requests that are sent "
            "to Call Server.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_TYPE_SERVER,             0x02, 
            "Call Server cause value. Clients shall not use this value "
            "in requests that are sent to Call Server.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_TYPE_NETWORK,            0x03, 
            "Network interface cause value. Clients shall use this "
            "value or client type in call release requests that are "
            "sent to Call Server.")
    CONST_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
        "Call Server generated cause values. Call Server uses these "
        "causes to indicate e.g. errors in validation of received requests, "
        "call releases that are caused modem state (e.g. no service, no "
        "SIM card) and channel lost. Clients shall use causes "
        "CALL_MODEM_CAUSE_RELEASE_BY_USER and "
        "CALL_MODEM_CAUSE_BUSY_USER_REQUEST in release requests that are "
        "sent to Call Server.")

    CONST_TBL_BEGIN(CALL_MODEM_CAUSE, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_NO_CALL,                     0x01, 
            "Indicates that call does not exists e.g. in CALL_STATUS_RESP.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_RELEASE_BY_USER,             0x03, 
            "Can be used by client to indicate normal call clearing. "
            "Maps to cause 16 in network interface.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_BUSY_USER_REQUEST,           0x04, 
            "Can be used by client to indicate that user has rejected the call. "
            "Maps to cause 17 in network interface.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_ERROR_REQUEST,               0x05, 
            "Indicates that request has been erroneus.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_CALL_ACTIVE,                 0x07, 
            "Indicates that procedure is rejected because call is active.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_NO_CALL_ACTIVE,              0x08,
            "Indicates that procedure is rejected because no call is active.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_INVALID_CALL_MODE,           0x09,
            "Indicates that procedure is rejected because call mode is invalid.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_TOO_LONG_ADDRESS,            0x0B,
            "Indicates that procedure is rejected because address is too long.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_INVALID_ADDRESS,             0x0C, 
            "Indicates that procedure is rejected because address is invalid.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_EMERGENCY,                   0x0D,
            "Indicates that call is cleared because emergency call establishment "
            "has started.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_NO_SERVICE,                  0x0E,
            "Indicates that call is cleared because of no service.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_CODE_REQUIRED,               0x10,
             "Call creation has failed because SIM code required or PIN rights lost.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_NOT_ALLOWED,                 0x11, 
            "Indicates that procedure is not allowed. Used e.g. if call control "
            "or call answer request arrives to invalid call state.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_DTMF_ERROR,                  0x12, 
            "Indicates that DMTF handling error has occurred.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_CHANNEL_LOSS,                0x13, 
            "Indicates that call is cleared because call re-establishment has failed. ")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_FDN_NOT_OK,                  0x14, 
            "Call creation has failed because of Fixed Dialling Number check.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_BLACKLIST_BLOCKED,           0x16, 
            "Blacklist has blocked the number.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_BLACKLIST_DELAYED,           0x17, 
            "Blacklist has delayed the call establishment to the number.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_EMERGENCY_FAILURE,           0x1A, 
            "Indicates that emergency call has failed because network is not found.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_NO_SIM,                      0x1F, 
            "Call creation has failed because no connection to SIM card.")
        COMMENT(COMMENT_TEXT,
            "Call creation has failed because SIM lock is operative.")
        CONST_TBL_ENTRY_VER(CALL_MODEM_CAUSE_SIM_LOCK_OPERATIVE,      0x20,
            "", "001.003")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_DTMF_SEND_ONGOING,           0x24, 
             "Indicates that procedure is rejected because DTMF sending is ongoing.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_CS_INACTIVE,                 0x25,
             "Indicates that procedure is rejected because CS is inactive.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_NOT_READY,                   0x26, 
             "Indicates that procedure is rejected because startup is ongoing.")
        CONST_TBL_ENTRY(CALL_MODEM_CAUSE_INCOMPATIBLE_DEST,           0x27,
             "Indicates that procedure is rejected because Bearer Capability "
             "negotiation has failed. ")
        COMMENT(COMMENT_TEXT,
             "Call release request has been rejected because of call "
             "deflection. Cause is used only in case resource controller "
             "provides it in resource reject request.")
        CONST_TBL_ENTRY_VER(CALL_MODEM_CAUSE_DEFLECT_REJECTED,        0x28,
            "030.001", "")
        COMMENT(COMMENT_TEXT,
             "Call deflection response has not been received from network. "
             "Cause is used only in case network has not answered to call "
             "deflection request and call clearing is completed.");
        CONST_TBL_ENTRY_VER(CALL_MODEM_CAUSE_DEFLECT_NO_RESPONSE,     0x29,
            "030.001", "")
    CONST_TBL_END


    COMMENT(COMMENT_PARAGRAPH,
            "Cause values used in network interface. See 'Cause IE' in "
            "3GPP TS 24.008 ch. 10.5.4.11.")

    COMMENT(COMMENT_NEWLINE,   "")

    COMMENT(COMMENT_PARAGRAPH,
            "For MT releases Call Server generates cause values in some cases "
            "internally. ")

    COMMENT(COMMENT_NEWLINE,   "")

    COMMENT(COMMENT_PARAGRAPH,
            "On MM connection failures following cause values are used: ")
    COMMENT(COMMENT_PARAGRAPH,
            "- 127 MM connection establishment fails")
    COMMENT(COMMENT_PARAGRAPH,
            "- 102 MM connection establishment fails to timeout")
    COMMENT(COMMENT_PARAGRAPH,
            "- 47  MM connection is released abnormally e.g. during active call")
    COMMENT(COMMENT_PARAGRAPH,
            "- 34  MM connection is interrupted by lower layer failure.")

    COMMENT(COMMENT_NEWLINE,   "")

    COMMENT(COMMENT_PARAGRAPH,
           "When call release message that contain invalid contents is received "
           "following cause values are used:")
    COMMENT(COMMENT_PARAGRAPH,
            "- 96  Invalid mandatory information")
    COMMENT(COMMENT_PARAGRAPH,
            "- 99  Informatio element non-existent or not implemented")

    COMMENT(COMMENT_NEWLINE,   "")

    COMMENT(COMMENT_PARAGRAPH,
           "When Supplementary Service operation (e.g. conference build) is "
           "rejected and failure response from network does not contain "
            "'Cause IE' following cause values are used: ")
    COMMENT(COMMENT_PARAGRAPH,
            "- 29  Facility rejected")
    COMMENT(COMMENT_PARAGRAPH,
           "Same cause value is used also Supplementary Service operation "
           "fails to timeout.")

    CONST_TBL_BEGIN(CALL_MODEM_NW_CAUSE, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_UNASSIGNED_NUMBER,       0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_NO_ROUTE,                0x03, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_CH_UNACCEPTABLE,         0x06, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_OPER_BARRING,            0x08, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_NORMAL,                  0x10, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_USER_BUSY,               0x11, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_NO_USER_RESPONSE,        0x12, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_ALERT_NO_ANSWER,         0x13, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_CALL_REJECTED,           0x15, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_NUMBER_CHANGED,          0x16, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_NON_SELECT_CLEAR,        0x1A, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_DEST_OUT_OF_ORDER,       0x1B, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_INVALID_NUMBER,          0x1C, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_FACILITY_REJECTED,       0x1D, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_RESP_TO_STATUS,          0x1E, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_NORMAL_UNSPECIFIED,      0x1F, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_NO_CHANNEL,              0x22, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_NETW_OUT_OF_ORDER,       0x26, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_TEMPORARY_FAILURE,       0x29, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_CONGESTION,              0x2A, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_ACCESS_INFO_DISC,        0x2B, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_CHANNEL_NA,              0x2C, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_RESOURCES_NA,            0x2F, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_QOS_NA,                  0x31, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_FACILITY_UNSUBS,         0x32, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_COMING_BARRED_CUG,       0x37, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_BC_UNAUTHORIZED,         0x39, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_BC_NA,                   0x3A, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_SERVICE_NA,              0x3F, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_BEARER_NOT_IMPL,         0x41, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_ACM_MAX,                 0x44, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_FACILITY_NOT_IMPL,       0x45, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_ONLY_RDI_BC,             0x46, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_SERVICE_NOT_IMPL,        0x4F, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_INVALID_TI,              0x51, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_NOT_IN_CUG,              0x57, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_INCOMPATIBLE_DEST,       0x58, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_INV_TRANS_NET_SEL,       0x5B, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_SEMANTICAL_ERR,          0x5F, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_INVALID_MANDATORY,       0x60, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_MSG_TYPE_INEXIST,        0x61, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_MSG_TYPE_INCOMPAT,       0x62, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_IE_NON_EXISTENT,         0x63, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_COND_IE_ERROR,           0x64, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_MSG_INCOMPATIBLE,        0x65, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_TIMER_EXPIRY,            0x66, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_PROTOCOL_ERROR,          0x6F, "")
        CONST_TBL_ENTRY(CALL_MODEM_NW_CAUSE_INTERWORKING,            0x7F, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_IDLE,                       0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_CREATE,                     0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_COMING,                     0x02, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_PROCEEDING,                 0x03, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_MO_ALERTING,                0x04, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_MT_ALERTING,                0x05, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_WAITING,                    0x06, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_ANSWERED,                   0x07, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_ACTIVE,                     0x08, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_MO_RELEASE,                 0x09, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_MT_RELEASE,                 0x0A, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_HOLD_INITIATED,             0x0B, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_HOLD,                       0x0C, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_RETRIEVE_INITIATED,         0x0D, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_RECONNECT_PENDING,          0x0E, "")
    CONST_TBL_END


    COMMENT(COMMENT_PARAGRAPH,
        "The four least significant bits (1-4) contain call present. "
        "Other bits are spare."
        ) 
    BIT_TBL_BEGIN(CALL_MODEM_PRESENT_INFO, 8, BE, "", "")
        BIT_TBL_ENTRY("XXXX0000", CALL_MODEM_PRESENT,  "")
        BIT_TBL_ENTRY("XXXX0001", CALL_MODEM_NOT_PRESENT,    "")
    BIT_TBL_END


    BIT_TBL_BEGIN(CALL_MODEM_ALERTING_INFO, 8, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXX1", CALL_MODEM_AI_GEN_ALERTING_TONE,        "")
    BIT_TBL_END


    BIT_TBL_BEGIN(CALL_MODEM_RELEASE_INFO, 8, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXX1", CALL_MODEM_RI_IN_BAND_INFO,             "")
    BIT_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_OPERATION, 8, BE, "", "")
       COMMENT(COMMENT_TEXT,
           "Used in CALL_MODEM_CONTROL_RESP if requested call operation "
           "is unknown. In that case CALL_MODEM_SERVICE_DENIED_IND is not "
           "sent for rejected operation. Shall not be used in requests that "
           "are sent to Call Server.")
        CONST_TBL_ENTRY_VER(CALL_MODEM_OP_UNKNOWN,                    0x00,
            "002.000", "")
        CONST_TBL_ENTRY(CALL_MODEM_OP_HOLD,                           0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_OP_RETRIEVE,                       0x02, "")
        CONST_TBL_ENTRY(CALL_MODEM_OP_SWAP,                           0x03, "")
        CONST_TBL_ENTRY(CALL_MODEM_OP_CONFERENCE_BUILD,               0x04, "")
        CONST_TBL_ENTRY(CALL_MODEM_OP_CONFERENCE_SPLIT,               0x05, "")
        CONST_TBL_ENTRY_VER(CALL_MODEM_OP_CUG,                        0xA0, "",
            "002.000")
        CONST_TBL_ENTRY(CALL_MODEM_OP_TRANSFER,                       0xA1, "")
        COMMENT(COMMENT_TEXT,
            "Used in CALL_MODEM_RELEASE_REQ to request call deflection for "
            "incoming call.")
        CONST_TBL_ENTRY_VER(CALL_MODEM_OP_DEFLECT,                    0x06,
            "030.001", "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_DTMF_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_DTMF_IDLE,                         0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_DTMF_ACTIVE,                       0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_RECONNECT_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_RECONNECT_PENDING,                 0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_RECONNECTED,                       0x02, "")
    CONST_TBL_END


    CONST_TBL_BEGIN(CALL_MODEM_PROPERTY, 8, BE, "", "")
       COMMENT(COMMENT_TEXT,
           "Used in CALL_MODEM_PROPERTY_GET_RESP and "
           "CALL_MODEM_PROPERTY_SET_RESP if requested property or property "
           "value is unknown. Shall not be used in requests that are sent to "
           "Call Server.")
        CONST_TBL_ENTRY_VER(CALL_MODEM_PROP_UNKNOWN,                0x00,
            "002.000", "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_ALL,                        0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_IMMEDIATE_CONNECT,          0xA0, "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_CUG_INFO,                   0xA1, "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_CALL_MODE_DEFAULT,          0xA2, "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_ALS,                        0xA6, "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_LINE_ID,                    0xA8, "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_EMERG,                      0xA9, "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_CTM,                        0xAC, "")
    CONST_TBL_END



    CONST_TBL_BEGIN(CALL_MODEM_PROP_IMMEDIATE_CONNECT, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_IMM_CONNECT_OFF,                 0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_IMM_CONNECT_ON,                  0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_PROP_ALS, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_ALS_LINE_NORMAL,            0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_ALS_LINE_2,                 0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_PROP_LINE_ID, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_PRESENT_DEFAULT,            0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_PRESENT_ALLOWED,            0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_PRESENT_RESTRICTED,         0x02, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_PROP_EMERG, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_EMERG_CHK_DEFAULT,          0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_EMERG_CHK_DISABLED,         0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_PROP_CTM, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_CTM_NOT_SUPPORTED,          0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_PROP_CTM_SUPPORTED,              0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_EMERG_NUMBER_OPERATION, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_EMERG_NUMBER_REMOVE,           0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_EMERG_NUMBER_ADD,              0x01, "")
        COMMENT(COMMENT_TEXT,
           "Used in CALL_MODEM_EMERG_NBR_MODIFY_RESP if requested emergency "
           "number operation is unknown. Shall not be used in requests that "
           "are sent to Call Server.")
        CONST_TBL_ENTRY_VER(CALL_MODEM_EMERG_NUMBER_UNKNOWN,      0xFF,
            "002.000", "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_EMERG_NUMBER_CHECK_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_EMERG_NBR_CHECK_FAIL,          0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_EMERG_NBR_CHECK_PASS,          0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_PREFERENTIAL_CUG, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_CUG_PREF,                          0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_CUG_PREF_SUPPRESS,                 0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_CUG_OUTGOING_ACCESS, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_CUG_OA,                            0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_CUG_OA_SUPPRESS,                   0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_ALERTING_PATTERN, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_ALERTING_LEVEL_0,                  0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_ALERTING_LEVEL_1,                  0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_ALERTING_LEVEL_2,                  0x02, "")
        CONST_TBL_ENTRY(CALL_MODEM_ALERTING_CATEGORY_1,               0x04, "")
        CONST_TBL_ENTRY(CALL_MODEM_ALERTING_CATEGORY_2,               0x05, "")
        CONST_TBL_ENTRY(CALL_MODEM_ALERTING_CATEGORY_3,               0x06, "")
        CONST_TBL_ENTRY(CALL_MODEM_ALERTING_CATEGORY_4,               0x07, "")
        CONST_TBL_ENTRY(CALL_MODEM_ALERTING_CATEGORY_5,               0x08, "")
    CONST_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
         "See 'Cause IE' in 3GPP TS 24.008 ch. 10.5.4.11. "
         "Field contains values from cause diagnostics octet 5 of "
         "'Cause IE' when octet is coded according to NOTE 9. "
         "Note is applicable for causes 1, 3, 16, 21 and 49.")
    CONST_TBL_BEGIN(CALL_MODEM_CONDITION, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_COND_UNKNOWN,                      0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_COND_PERMANENT,                    0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_COND_TRANSIENT,                    0x02, "")
    CONST_TBL_END

    COMMENT(COMMENT_PARAGRAPH,
         "See 'Cause IE' in 3GPP TS 24.008 ch. 10.5.4.11. "
         "Field contains values from cause diagnostics octet 5 of "
         "'Cause IE' when octet is coded according to NOTE 1. "
         "Note is applicable for causes 17, 29, 34, 50, 55, 69 and 87")
    CONST_TBL_BEGIN(CALL_MODEM_SS_DIAGNOSTICS, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_SSD_OUTGOING_BARR_CUG,         0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSD_NO_CUG,                    0x02, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSD_UNKNOWN_CUG,               0x03, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSD_INCOMPATIBLE_CUG,          0x04, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSD_CUG_FAIL,                  0x05, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSD_CLIR_NOT_SUBSCRIBED,       0x06, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_NOTIFICATION_INDICATOR, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_NOTIFY_USER_SUSPENDED,             0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_NOTIFY_USER_RESUMED,               0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_NOTIFY_BEARER_CHANGE,              0x02, "")
    CONST_TBL_END


    COMMENT(COMMENT_PARAGRAPH,
         "See 'Codes for defined Supplementary Services' in 3GPP TS 22.030 "
         "Annex B. ")
    CONST_TBL_BEGIN(CALL_MODEM_MMI_SS_CODES, 16, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_ALL_FWDS,                   0x0002, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_ALL_COND_FWD,               0x0004, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_CFU,                        0x0015, "")
        CONST_TBL_ENTRY_VER(CALL_MODEM_SSC_DEFLECT,                0x0042,
            "030.001", "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_CFB,                        0x0043, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_CFNRY,                      0x003D, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_CFGNC,                      0x003E, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_OUTGOING_BARR_SERV,         0x014D, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_INCOMING_BARR_SERV,         0x0161, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_CALL_WAITING,               0x002B, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_CLIR,                       0x001F, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_ECT,                        0x0060, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_MPTY,                       0xFFFE, "")
        CONST_TBL_ENTRY(CALL_MODEM_SSC_CALL_HOLD,                  0xFFFF, "")
    CONST_TBL_END

    BIT_TBL_BEGIN(CALL_MODEM_SS_STATUS, 8, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXX1", CALL_MODEM_SS_STATUS_ACTIVE,            "")
        BIT_TBL_ENTRY("XXXXXX1X", CALL_MODEM_SS_STATUS_REGISTERED,        "")
        BIT_TBL_ENTRY("XXXXX1XX", CALL_MODEM_SS_STATUS_PROVISIONED,       "")
        BIT_TBL_ENTRY("XXXX1XXX", CALL_MODEM_SS_STATUS_QUIESCENT,         "")
    BIT_TBL_END

    BIT_TBL_BEGIN(CALL_MODEM_SS_NOTIFICATION, 8, BE, "",       "")
        BIT_TBL_ENTRY("XXXXXXX1", CALL_MODEM_SSN_INCOMING_IS_FWD,         "")
        BIT_TBL_ENTRY("XXXXXX1X", CALL_MODEM_SSN_INCOMING_FWD,            "")
        BIT_TBL_ENTRY("XXXXX1XX", CALL_MODEM_SSN_OUTGOING_FWD,            "")
    BIT_TBL_END

    BIT_TBL_BEGIN(CALL_MODEM_SS_INDICATOR, 8, BE, "",          "")
        BIT_TBL_ENTRY("XXXXXXX1", CALL_MODEM_SSI_CALL_IS_WAITING,         "")
        BIT_TBL_ENTRY("XXXXXX1X", CALL_MODEM_SSI_MPTY,                    "")
        BIT_TBL_ENTRY("XXXXX1XX", CALL_MODEM_SSI_CLIR_SUPPR_REJ,          "")
    BIT_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_SS_HOLD_INDICATOR, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_HOLD_IND_RETRIEVED,                0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_HOLD_IND_ON_HOLD,                  0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_SS_ECT_INDICATOR, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_ECT_CALL_STATE_ALERT,              0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_ECT_CALL_STATE_ACTIVE,             0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_BLACKLIST_DURATION, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_BLACKLIST_TIMEOUT,                 0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_BLACKLIST_DURATION_5,              0x05, "")
        CONST_TBL_ENTRY(CALL_MODEM_BLACKLIST_DURATION_60,             0x3C, "")
        CONST_TBL_ENTRY(CALL_MODEM_BLACKLIST_DURATION_180,            0xB4, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_BC_CHECK_RESULT, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_BC_CHECK_RESULT_FAIL,             0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_BC_CHECK_RESULT_OK,               0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_DTMF_PAUSE_VALUES, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_DTMF_PAUSE_1S,                     0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_DTMF_PAUSE_2S,                     0x02, "")
        CONST_TBL_ENTRY(CALL_MODEM_DTMF_PAUSE_3S,                     0x03, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_DTMF_INFO_VALUES, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_DTMF_ENABLE_TONE_IND_SEND,         0x01, 
            "CALL_MODEM_DTMF_TONE_IND indications are sent to clients during "
            "DTMF string sending.")
        CONST_TBL_ENTRY(CALL_MODEM_DTMF_DISABLE_TONE_IND_SEND,        0x02, 
            "CALL_MODEM_DTMF_TONE_IND indications are not sent to clients "
            "during DTMF string sending.")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_CAUSE_OF_NO_CLI_VALUES, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_CLI_UNAVAILABLE,                   0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_CLI_REJECT_BY_USER,                0x02, "")
        CONST_TBL_ENTRY(CALL_MODEM_CLI_INTERACTION,                   0x03, "")
        CONST_TBL_ENTRY(CALL_MODEM_CLI_COIN_LINE_PAYPHONE,            0x04, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_MM_CAUSE_VALUES, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_HLR_IMSI_UNKNOWN,         0x02, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_ILLEGAL_MS,               0x03, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_VLR_IMSI_UNKNOWN,         0x04, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_IMEI_NOT_ACCEPTED,        0x05, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_ILLEGAL_ME,               0x06, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_PLMN_NOT_ALLOWED,         0x0B, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_LA_NOT_ALLOWED,           0x0C, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_ROAM_NOT_ALLOWED_LA,      0x0D, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_NO_SUITABLE_CELLS_LA,     0x0F, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_NETWORK_FAILURE,          0x11, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_MAC_FAILURE,              0x14, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_SYNC_FAILURE,             0x15, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_CONGESTION,               0x16, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_AUTH_UNACCEPTABLE,        0x17, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_NOT_SUPP_S_OPTION,        0x20, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_NOT_SUBS_S_OPTION,        0x21, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_OUT_OF_ORDER_S_OPTION,    0x22, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_CALL_NOT_IDENTIFIED,      0x26, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_SEMANT_INCORRECT,         0x5F, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_INV_MAND_INFORMATION,     0x60, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_NON_EXISTENT_MSG_TYPE,    0x61, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_NOT_COMP_MSG_TYPE,        0x62, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_NOT_EXISTENT_IE,          0x63, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_CONDITIONAL_IE_ERROR,     0x64, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_MSG_NOT_COMPATIBLE,       0x65, "")
        CONST_TBL_ENTRY(CALL_MODEM_MM_CAUSE_PROTOCOL_ERROR,           0x6F, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_ALS_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_ALS_STATUS_NOT_READY,              0x00, 
            "This is used e.g. in startup if Call Server has not yet "
            "accuired ALS status from SIM.")
        CONST_TBL_ENTRY(CALL_MODEM_ALS_STATUS_DISABLED,               0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_ALS_STATUS_ENABLED,                0x02, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_AUTO_ST_CHANGE, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_AUTO_ST_CHANGE_DISABLE,            0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_AUTO_ST_CHANGE_DISABLE_WAITING,    0x01, "")
    CONST_TBL_END

    BIT_TBL_BEGIN(CALL_MODEM_REQ_ADDITIONAL_INFO, 8, BE, "", "")
        BIT_TBL_ENTRY("00000000", CALL_MODEM_ADD_INFO_NONE,            "Default value")
        BIT_TBL_ENTRY("xxxxxxx1", CALL_MODEM_ADD_INFO_EMERG_CALL,      "")
    BIT_TBL_END

    BIT_TBL_BEGIN(CALL_MODEM_EMERG_SERVICE_CATEGORY, 8, BE, "", "")
        BIT_TBL_ENTRY("00000000", CALL_MODEM_SERVICE_CAT_NONE,             "Default value")
        BIT_TBL_ENTRY("xxxxxxx1", CALL_MODEM_SERVICE_CAT_POLICE,           "")
        BIT_TBL_ENTRY("xxxxxx1x", CALL_MODEM_SERVICE_CAT_AMBULANCE,        "")
        BIT_TBL_ENTRY("xxxxx1xx", CALL_MODEM_SERVICE_CAT_FIRE_BRIGADE,     "")
        BIT_TBL_ENTRY("xxxx1xxx", CALL_MODEM_SERVICE_CAT_MARINE_GUARD,     "")
        BIT_TBL_ENTRY("xxx1xxxx", CALL_MODEM_SERVICE_CAT_MOUNTAIN_RESCUE,  "")
    BIT_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_STATUS_MOD, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_MODE_DEFAULT,               0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_MODE_ADDR,                  0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_STATUS_MODE_ADDR_AND_ORIGIN,       0x02, "")
    CONST_TBL_END
 
    CONST_TBL_BEGIN(CALL_MODEM_USER_CONN, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_USER_CONN_CLOSED,                  0x00, "")
        CONST_TBL_ENTRY(CALL_MODEM_USER_CONN_ATTACHED,                0x01, "")
    CONST_TBL_END

    BIT_TBL_BEGIN(CALL_MODEM_EMERG_NBR_ORIGIN, 8, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXX1", CALL_MODEM_EMERG_NBR_ORIG_HARD_CODED,     "")
        BIT_TBL_ENTRY("XXXXXX1X", CALL_MODEM_EMERG_NBR_ORIG_SIM,            "")
        BIT_TBL_ENTRY("XXXXX1XX", CALL_MODEM_EMERG_NBR_ORIG_NETWORK,        "")
        BIT_TBL_ENTRY("XXXX1XXX", CALL_MODEM_EMERG_NBR_ORIG_PERMANENT_MEM,  "")
    BIT_TBL_END

    BIT_TBL_BEGIN(CALL_MODEM_RESOURCE_IDS, 16, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX1", CALL_MODEM_RES_ID_MO_INIT,       "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX1X", CALL_MODEM_RES_ID_MT_INIT,       "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXX1XX", CALL_MODEM_RES_ID_MT_ANSWER,     "")
        BIT_TBL_ENTRY("XXXXXXXXXXXX1XXX", CALL_MODEM_RES_ID_HOLD,          "")
        BIT_TBL_ENTRY("XXXXXXXXXXX1XXXX", CALL_MODEM_RES_ID_RETRIEVE,      "")
        BIT_TBL_ENTRY("XXXXXXXXXX1XXXXX", CALL_MODEM_RES_ID_AUTO_HOLD,     "")
        BIT_TBL_ENTRY("XXXXXXXXX1XXXXXX", CALL_MODEM_RES_ID_AUTO_RETRIEVE, "")
        BIT_TBL_ENTRY("XXXXXXXX1XXXXXXX", CALL_MODEM_RES_ID_SWAP,          "")
        BIT_TBL_ENTRY("XXXXXXX1XXXXXXXX", CALL_MODEM_RES_ID_CONF_BUILD,    "")
        BIT_TBL_ENTRY("XXXXXX1XXXXXXXXX", CALL_MODEM_RES_ID_CONF_SPLIT,    "")
        BIT_TBL_ENTRY("XXXXX1XXXXXXXXXX", CALL_MODEM_RES_ID_TRANSFER,      "")
        BIT_TBL_ENTRY_VER("XXXX1XXXXXXXXXXX", CALL_MODEM_RES_ID_DEFLECT,
            "030.001","")
    BIT_TBL_END

    BIT_TBL_BEGIN(CALL_MODEM_RESOURCE_IDS_MASK, 16, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX1", CALL_MODEM_RES_ID_MASK_MO_INIT,       "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX1X", CALL_MODEM_RES_ID_MASK_MT_INIT,       "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXX1XX", CALL_MODEM_RES_ID_MASK_MT_ANSWER,     "")
        BIT_TBL_ENTRY("XXXXXXXXXXXX1XXX", CALL_MODEM_RES_ID_MASK_HOLD,          "")
        BIT_TBL_ENTRY("XXXXXXXXXXX1XXXX", CALL_MODEM_RES_ID_MASK_RETRIEVE,      "")
        BIT_TBL_ENTRY("XXXXXXXXXX1XXXXX", CALL_MODEM_RES_ID_MASK_AUTO_HOLD,     "")
        BIT_TBL_ENTRY("XXXXXXXXX1XXXXXX", CALL_MODEM_RES_ID_MASK_AUTO_RETRIEVE, "")
        BIT_TBL_ENTRY("XXXXXXXX1XXXXXXX", CALL_MODEM_RES_ID_MASK_SWAP,          "")
        BIT_TBL_ENTRY("XXXXXXX1XXXXXXXX", CALL_MODEM_RES_ID_MASK_CONF_BUILD,    "")
        BIT_TBL_ENTRY("XXXXXX1XXXXXXXXX", CALL_MODEM_RES_ID_MASK_CONF_SPLIT,    "")
        BIT_TBL_ENTRY("XXXXX1XXXXXXXXXX", CALL_MODEM_RES_ID_MASK_TRANSFER,      "")
        BIT_TBL_ENTRY_VER("XXXX1XXXXXXXXXXX",
            CALL_MODEM_RES_ID_MASK_DEFLECT,"030.001","")
    BIT_TBL_END

    BIT_TBL_BEGIN(CALL_MODEM_RESOURCE_IDS_CONF_REQ, 16, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX1", CALL_MODEM_RES_ID_CONF_MO_INIT,       "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX1X", CALL_MODEM_RES_ID_CONF_MT_INIT,       "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXX1XX", CALL_MODEM_RES_ID_CONF_MT_ANSWER,     "")
        BIT_TBL_ENTRY("XXXXXXXXXXXX1XXX", CALL_MODEM_RES_ID_CONF_HOLD,          "")
        BIT_TBL_ENTRY("XXXXXXXXXXX1XXXX", CALL_MODEM_RES_ID_CONF_RETRIEVE,      "")
        BIT_TBL_ENTRY("XXXXXXXXXX1XXXXX", CALL_MODEM_RES_ID_CONF_AUTO_HOLD,     "")
        BIT_TBL_ENTRY("XXXXXXXXX1XXXXXX", CALL_MODEM_RES_ID_CONF_AUTO_RETRIEVE, "")
        BIT_TBL_ENTRY("XXXXXXXX1XXXXXXX", CALL_MODEM_RES_ID_CONF_SWAP,          "")
        BIT_TBL_ENTRY("XXXXXXX1XXXXXXXX", CALL_MODEM_RES_ID_CONF_CONF_BUILD,    "")
        BIT_TBL_ENTRY("XXXXXX1XXXXXXXXX", CALL_MODEM_RES_ID_CONF_CONF_SPLIT,    "")
        BIT_TBL_ENTRY("XXXXX1XXXXXXXXXX", CALL_MODEM_RES_ID_CONF_TRANSFER,      "")
        BIT_TBL_ENTRY_VER("XXXX1XXXXXXXXXXX",
            CALL_MODEM_RES_ID_CONF_DEFLECT,"030.001","")
    BIT_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_RESOURCE_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_RESOURCE_ALLOWED,            0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_RESOURCE_DENIED,             0x02, "")
    CONST_TBL_END

    COMMENT(COMMENT_TEXT, "This field can be used to disable various "
        "checks that are made for MO calls in Call Server i.e. they "
        "are already made by the client or not needed for the call. ")
    BIT_TBL_BEGIN(CALL_MODEM_CHECK_INFO, 8, BE, "", "")
        BIT_TBL_ENTRY("00000000", CALL_MODEM_CHK_DISABLE_NONE,        "")
        BIT_TBL_ENTRY("XXXXXXX1", CALL_MODEM_CHK_DISABLE_EMERG,       "")
        BIT_TBL_ENTRY("XXXXXX1X", CALL_MODEM_CHK_DISABLE_FDN,         "")
        BIT_TBL_ENTRY("XXXXX1XX", CALL_MODEM_CHK_DISABLE_BLACKLIST,   "")
        BIT_TBL_ENTRY("XXXX1XXX", CALL_MODEM_CHK_DISABLE_ALS,         "")
    BIT_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_RES_CONF_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_RES_CONF_STARTUP,            0x01, 
            "Sent when Modem Call Server starts up.")
        CONST_TBL_ENTRY(CALL_MODEM_RES_CONF_RECONFIGURED,       0x02, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_RES_CONF_OPERATION, 8, BE, "", "")
       COMMENT(COMMENT_TEXT,
           "Used in CALL_MODEM_RESOURCE_CONF_RESP if resource configuration "
           "operation is unknown. Shall not be used in requests that are "
           "sent to Call Server.")
        CONST_TBL_ENTRY_VER(CALL_MODEM_RES_CONF_UNKNOWN,        0x00,
            "002.000", "")
        CONST_TBL_ENTRY(CALL_MODEM_RES_CONF_GET,                0x01, "")
        CONST_TBL_ENTRY(CALL_MODEM_RES_CONF_SET,                0x02, "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(CALL_MODEM_RES_CONF_OPERATION_REQUEST, 
        CALL_MODEM_RES_CONF_OPERATION, "",
        "")
        DER_CONST_TBL_ENTRY(CALL_MODEM_RES_CONF_GET)
        DER_CONST_TBL_ENTRY(CALL_MODEM_RES_CONF_SET)
    DER_CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_LINE_ID, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_PRESENT_DEFAULT,             0x00,
            "Default line ID value from Modem Call Server properties "
            "is used for the call.")
        CONST_TBL_ENTRY(CALL_MODEM_PRESENT_ALLOWED,             0x01,
            "Overrides default line ID value in Modem Call Server properties "
            "for the call")
        CONST_TBL_ENTRY(CALL_MODEM_PRESENT_RESTRICTED,          0x02,
            "Overrides default line ID value in Modem Call Server properties "
            "for the call")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_MSG, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_MSG_SETUP,                   0x01, 
            "Setup message.")
        CONST_TBL_ENTRY(CALL_MODEM_MSG_CONNECT,                 0x02, 
            "Connect message.")
        CONST_TBL_ENTRY(CALL_MODEM_MSG_RELEASE,                 0x03, 
            "First releasing message or internal call release.")
    CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_MSG_DIRECTION, 8, BE, "", "")
        CONST_TBL_ENTRY(CALL_MODEM_MSG_DIRECT_SENT,             0x01, 
            "Message is sent to network.")
        CONST_TBL_ENTRY(CALL_MODEM_MSG_DIRECT_RECEIVED,         0x02, 
            "Message is received from network.")
        CONST_TBL_ENTRY(CALL_MODEM_MSG_DIRECT_INTERNAL,         0x03, 
            "Used for internal call release e.g. radio link failure.")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(CALL_MODEM_VCC_STATUS, CALL_MODEM_STATUS,
        "030.000", "")
        DER_CONST_TBL_ENTRY(CALL_MODEM_STATUS_ACTIVE)
        DER_CONST_TBL_ENTRY(CALL_MODEM_STATUS_HOLD)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(CALL_MODEM_VCC_MODE, CALL_MODEM_MODE, "030.000", "")
        DER_CONST_TBL_ENTRY(CALL_MODEM_MODE_EMERGENCY)
        DER_CONST_TBL_ENTRY(CALL_MODEM_MODE_SPEECH)
    DER_CONST_TBL_END

    CONST_TBL_BEGIN(CALL_MODEM_BLACKLIST_STATUS, 8, BE, "030.001", "")
        CONST_TBL_ENTRY(CALL_MODEM_BLACKLIST_STATUS_BLOCKED,     0x01, 
            "Blacklist has blocked number. Call establishment to number "
            "is not possible until number is removed from blacklist.")
        CONST_TBL_ENTRY(CALL_MODEM_BLACKLIST_STATUS_NOT_BLOCKED, 0x02, 
            "Blocked number has been removed from blacklist. "
            "Call establishment to number is possible.")
    CONST_TBL_END

    /* Sequences */

    SEQ_BEGIN(CALL_MODEM_HEX_DATA, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, hex_data, "Hex Data", HEX)
    SEQ_END

    /* Sub blocks */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_ORIGIN_ADDR_FIXED    0x06")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_ORIGIN_ADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_ORIGIN_ADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(addr_type, "Address type", CALL_MODEM_ADDRESS_TYPE)
        VALUE_CONST(presentation, "Presentation indicator",
            CALL_MODEM_PRESENTATION_SCREEN_INDICATOR)
        FILLER_EX(unused, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 123)
        REFERENCE(8, BE, addr_len, "Address length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for address string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', "
            "'a', 'b' and 'c'.")
        STRING_REF(STRING_UNICODE, BE, addr, "Address", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_ORIGIN_SUBADDR_FIXED    0x03")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_ORIGIN_SUBADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_ORIGIN_SUBADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        COMMENT(COMMENT_TEXT,
            "See 'Calling Party Subaddress IE' in 3GPP TS 24.008 "
            "ch. 10.5.4.10. Byte contains octet 2 from "
            "'Calling Party Subaddress IE'.")
        REFERENCE(8, BE, addr_len, "Subaddress length", N)
        COMMENT(COMMENT_TEXT,
            "See 'Calling Party Subaddress IE' in 3GPP TS 24.008 "
            "ch. 10.5.4.10. First byte contains octet 3 from "
            "'Calling Party Subaddress IE'.")
        SEQ_OF_REF(addr, "Subaddress", CALL_MODEM_HEX_DATA, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_DEST_ADDR_FIXED    0x06")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DEST_ADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_DESTINATION_ADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(addr_type, "Address type", CALL_MODEM_ADDRESS_TYPE)
        FILLER_EX(unused1, 8, 1)
        FILLER_EX(unused2, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 123)
        REFERENCE(8, BE, addr_len, "Address length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for address string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', "
            "'a', 'b' and 'c'. In case of CALL_MODEM_EMERG_NBR_CHECK_REQ "
            "characters that are in the string before valid emergency " 
            "number are not validated i.e. they may be also other "
            "characters than defined above.")
        STRING_REF(STRING_UNICODE, BE, addr, "Address", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_DEST_SUBADDR_FIXED    0x03")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DEST_SUBADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_DESTINATION_SUBADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        COMMENT(COMMENT_TEXT,
            "See 'Called Party Subaddress IE' in 3GPP TS 24.008 "
            "ch. 10.5.4.8. Byte contains octet 2 from "
            "'Called Party Subaddress IE'.")
        REFERENCE(8, BE, addr_len, "Subaddress length", N)
        COMMENT(COMMENT_TEXT,
            "See 'Called Party Subaddress IE' in 3GPP TS 24.008 "
            "ch. 10.5.4.8. First byte contains octet 3 from "
            "'Called Party Subaddress IE'.")
        SEQ_OF_REF(addr, "Subaddress", CALL_MODEM_HEX_DATA, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_DEST_PRE_ADDR_FIXED    0x04")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DEST_PRE_ADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_DESTINATION_PRE_ADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        FILLER_EX(unused, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 123)
        REFERENCE(8, BE, addr_len, "Address length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for address string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*' and '#'.")
        STRING_REF(STRING_UNICODE, BE, addr, "Address", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_DEST_POST_ADDR_FIXED    0x04")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DEST_POST_ADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_DESTINATION_POST_ADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        FILLER_EX(unused, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 123)
        REFERENCE(8, BE, addr_len, "Subaddress length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for address string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', "
            "'C', 'D', '*', '#', 'p' and 'w'.")
        STRING_REF(STRING_UNICODE, BE, addr, "Subaddress", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_CONN_ADDR_FIXED    0x06")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_CONN_ADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_CONNECTED_ADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(addr_type, "Address type", CALL_MODEM_ADDRESS_TYPE)
        VALUE_CONST(presentation, "Presentation indicator",
            CALL_MODEM_PRESENTATION_SCREEN_INDICATOR)
        FILLER_EX(unused, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 123)
        REFERENCE(8, BE, addr_len, "Address length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for address string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', "
            "'a', 'b' and 'c'.")
        STRING_REF(STRING_UNICODE, BE, addr, "Address", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_CONN_SUBADDR_FIXED    0x03")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_CONN_SUBADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_CONNECTED_SUBADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        COMMENT(COMMENT_TEXT,
            "See 'Connected Subaddress IE' in 3GPP TS 24.008 "
            "ch. 10.5.4.14. Byte contains octet 2 from "
            "'Connected Subaddress IE'.")
        REFERENCE(8, BE, addr_len, "Subaddress length", N)
        COMMENT(COMMENT_TEXT,
            "See 'Connected Subaddress IE' in 3GPP TS 24.008 "
            "ch. 10.5.4.14. First Byte contains octet 3 from "
            "'Connected Subaddress IE'.")
        SEQ_OF_REF(addr, "Subaddress", CALL_MODEM_HEX_DATA, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_MODE_STR")

    SB_BEGIN(CALL_MODEM_SB_MODE, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(mode, "Call Mode", CALL_MODEM_MODE)
        VALUE_CONST(mode_info, "Call Mode Info", CALL_MODEM_MODE_INFO)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_CAUSE_STR")


    SB_BEGIN(CALL_MODEM_SB_CAUSE, "030.001", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)

        VALUE(8, BE, cause_type, "Cause type", DEC)
        VALUE(8, BE, cause, "Cause", DEC)

    SB_END


    SB_BEGIN(CALL_MODEM_SB_CAUSE, "", "030.001")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)

        VALUE(8, BE, cause_type, "Cause type", DEC)
        VALUE(8, BE, cause, "Cause", DEC)

    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_OPER_STR")

    SB_BEGIN(CALL_MODEM_SB_OPERATION, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(operation, "Operation", CALL_MODEM_OPERATION)
        FILLER_EX(unused, 8, 1)
    SB_END



    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_STATUS_STR")

    SB_BEGIN(CALL_MODEM_SB_STATUS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Call Status", CALL_MODEM_STATUS)
        FILLER_EX(unused, 8, 1)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_ST_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_STATUS_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        VALUE_CONST(mode, "Call mode", CALL_MODEM_MODE)
        VALUE_CONST(mode_info, "Call mode info", CALL_MODEM_MODE_INFO)
        VALUE_CONST(status, "Call status", CALL_MODEM_STATUS)
        FILLER_EX(unused1, 8, 1)
        FILLER_EX(unused2, 8, 1)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_ALERT_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_ALERTING_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(alerting_info, "Alerting information", CALL_MODEM_ALERTING_INFO)
        FILLER_EX(unused, 8, 1)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_REL_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_RELEASE_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(release_info, "Release information", CALL_MODEM_RELEASE_INFO)
        FILLER_EX(unused, 8, 1)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_ORIGIN_INFO_FIXED    0x08")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_ORIGIN_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_ORIGIN_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(presentation, "Presentation indicator",
            CALL_MODEM_PRESENTATION_SCREEN_INDICATOR)
        FILLER_EX(unused1, 8, 1)
        FILLER_EX(unused2, 8, 1)
        FILLER_EX(unused3, 8, 1)
        COMMENT(COMMENT_TEXT,
        "Field links CALL_MODEM_ORIGIN_INFO and CALL_MODEM_ADDR_AND_STATUS_INFO sub blocks in CALL_MODEM_STATUS_RESP. "
        "Sub blocks that have same value for link id field contain information about same number.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 255)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_NO_LINK_ID)
        VALUE(8, BE, link_id, "Link ID", DEC)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 122)
        REFERENCE(8, BE, name_len, "Name length", N)
        STRING_REF(STRING_UNICODE, BE, name, "Name", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DTMF_DIGIT_STR")

    SB_BEGIN(CALL_MODEM_SB_DTMF_DIGIT, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        COMMENT(COMMENT_TEXT,
            "Possible value for DTMF digit are unicodes '0', '1', '2', "
            "'3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', '*' "
            "and '#'. ")
        COMMENT(COMMENT_PARAGRAPH,
            "Note: 'p' and 'w' are not valid values.")
        VALUE(-16, BE, data, "DTMF Digit", UNICODE_CHAR)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_DTMF_STRING_FIXED    0x04")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DTMF_STRING_STR")

    SB_BEGIN(CALL_MODEM_SB_DTMF_STRING, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(pause_length, "Pause length", CALL_MODEM_DTMF_PAUSE_VALUES)
        COMMENT(COMMENT_TEXT, "Number of DTMF digits.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 123)
        REFERENCE(8, BE, data_len, "DTMF length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for DTMF string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', "
            "'C', 'D', '*', '#', 'p' and 'w'.")
        STRING_REF(STRING_UNICODE, BE, data, "DTMF digits", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_DTMF_BCD_STRING_FIXED    0x06")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DTMF_BCD_STRING_STR")

    SB_BEGIN(CALL_MODEM_SB_DTMF_BCD_STRING, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(pause_length, "Pause length", CALL_MODEM_DTMF_PAUSE_VALUES)
        FILLER_EX(unused, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of DTMF numbers")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 482)
        REFERENCE(16, BE, data_len, "DTMF length", N)
        REFERENCE_TRANSFORM(N, M, ALG_DIV_ROUND_UP, 2)
        COMMENT(COMMENT_TEXT,
            "Possible values for DTMF string are numbers coded in BCD "
            "0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, "
            "0x0A (= '*'), 0x0B (= '#'), 0x0C (= pause) and 0x0F (= endmark). "
            "BCD value 0x0C is never sent across the radio interface.")
        STRING_REF(STRING_BCD, NSW, data, "DTMF string", M,
            ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DTMF_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_DTMF_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(dtmf_info, "Additonal DTMF info",
            CALL_MODEM_DTMF_INFO_VALUES)
        FILLER_EX(unused, 8, 1)
    SB_END

    /* CALL_PROPERTY_INFO */

    DER_CONST_TBL_BEGIN(CALL_MODEM_PROPERTY_INFO_PROPERTY, 
        CALL_MODEM_PROPERTY, "",
        "")
        DER_CONST_TBL_ENTRY(CALL_MODEM_PROP_IMMEDIATE_CONNECT)
        DER_CONST_TBL_ENTRY(CALL_MODEM_PROP_CUG_INFO)
        DER_CONST_TBL_ENTRY(CALL_MODEM_PROP_CALL_MODE_DEFAULT)
        DER_CONST_TBL_ENTRY(CALL_MODEM_PROP_ALS)
        DER_CONST_TBL_ENTRY(CALL_MODEM_PROP_LINE_ID)
        DER_CONST_TBL_ENTRY(CALL_MODEM_PROP_EMERG)
        DER_CONST_TBL_ENTRY(CALL_MODEM_PROP_CTM)
        DER_CONST_TBL_ENTRY_VER(CALL_MODEM_PROP_UNKNOWN, "002.000", "")
    DER_CONST_TBL_END


    DER_CONST_TBL_BEGIN(CALL_MODEM_MODE_DEFAULT,
        CALL_MODEM_MODE, "",  "")
        DER_CONST_TBL_ENTRY(CALL_MODEM_MODE_SPEECH)
        DER_CONST_TBL_ENTRY(CALL_MODEM_MODE_MULTIMEDIA)
    DER_CONST_TBL_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_PROP_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_PROPERTY_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        REFERENCE_CONST(property, "Property", PROP,
            CALL_MODEM_PROPERTY_INFO_PROPERTY)
        CHOICE_BEGIN(prop_value, "Property value", PROP)

            CASE_BEGIN(CALL_MODEM_PROP_IMMEDIATE_CONNECT,"","")
                VALUE_CONST(property_value, "Property Value",
                    CALL_MODEM_PROP_IMMEDIATE_CONNECT)
            CASE_END

            CASE_BEGIN(CALL_MODEM_PROP_CALL_MODE_DEFAULT,"","")
                VALUE_CONST(property_value, "Property Value", 
                    CALL_MODEM_MODE_DEFAULT)
            CASE_END

            CASE_BEGIN(CALL_MODEM_PROP_ALS,"","")
                VALUE_CONST(property_value, "Property Value",
                    CALL_MODEM_PROP_ALS)
            CASE_END

            CASE_BEGIN(CALL_MODEM_PROP_LINE_ID,"","")
                VALUE_CONST(property_value, "Property Value",
                    CALL_MODEM_PROP_LINE_ID)
            CASE_END

            CASE_BEGIN(CALL_MODEM_PROP_EMERG,"","")
                VALUE_CONST(property_value, "Property Value",
                    CALL_MODEM_PROP_EMERG)
            CASE_END

            CASE_BEGIN(CALL_MODEM_PROP_CTM,"","")
                VALUE_CONST(property_value, "Property Value",
                    CALL_MODEM_PROP_CTM)
            CASE_END

            DEFAULT_BEGIN("", "")
                PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0x00)
                PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0x00)
                VALUE(8, BE, property_value, "Property Value", HEX)
            DEFAULT_END

        CHOICE_END
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_EMERG_NBR_FIXED    0x08")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_EMERG_NBR_STR")

    SB_BEGIN(CALL_MODEM_SB_EMERG_NUMBER, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(origin, "Emergency number origin", CALL_MODEM_EMERG_NBR_ORIGIN)
        FILLER_EX(unused1, 8, 1)
        FILLER_EX(unused2, 8, 1)
        COMMENT(COMMENT_TEXT,
        "Field links CALL_MODEM_EMERG_NUMBER and CALL_MODEM_EMERG_NUMBER_INFO sub blocks. "
        "Sub blocks that have same value for link id field contain information about same number.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 255)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_NO_LINK_ID)
        VALUE(8, BE, link_id, "Link ID", DEC)
        FILLER_EX(unused3, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 122)
        REFERENCE(8, BE, addr_len, "Address length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for address string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', "
            "'a', 'b' and 'c'.")
        STRING_REF(STRING_UNICODE, BE, addr, "Address", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DTMF_ST_STR")

    SB_BEGIN(CALL_MODEM_SB_DTMF_STATUS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "DTMF Status", CALL_MODEM_DTMF_STATUS)
        FILLER_EX(unused, 8, 1)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DTMF_TONE_STR")

    SB_BEGIN(CALL_MODEM_SB_DTMF_TONE, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        COMMENT(COMMENT_TEXT, "Possible values for DTMF tone are ")
        COMMENT_LINK(LINK_CONSTANT, "CALL_MODEM_DTMF_NO_TONE", "", "")
        COMMENT(COMMENT_TEXT,
            " and unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', "
            "'C', 'D', '*', and '#'.")
        VALUE(-16, BE, tone, "DTMF Tone", UNICODE_CHAR)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_CUG_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_CUG_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(pref_cug, "Preferential CUG", CALL_MODEM_PREFERENTIAL_CUG)
        VALUE_CONST(cug_oa, "CUG output access", CALL_MODEM_CUG_OUTGOING_ACCESS)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0x0000)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0x7FFF)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_CUG_DEFAULT)
        VALUE(16, BE, cug_ind, "CUG index", DEC)
        FILLER_EX(unused, 8, 1)
        FILLER_EX(unused2, 8, 1)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_ALERT_PATT_STR")

    SB_BEGIN(CALL_MODEM_SB_ALERTING_PATTERN, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(alerting_pattern, "Alerting pattern",
            CALL_MODEM_ALERTING_PATTERN)
        FILLER_EX(unused, 8, 1)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_REDIR_ADDR_FIXED    0x06")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_REDIR_ADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_REDIRECTING_ADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(addr_type, "Address type", CALL_MODEM_ADDRESS_TYPE)
        VALUE_CONST(presentation, "Presentation indicator",
            CALL_MODEM_PRESENTATION_SCREEN_INDICATOR)
        FILLER_EX(unused, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 123)
        REFERENCE(8, BE, addr_len, "Address length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for address string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', "
            "'a', 'b' and 'c'.")
        STRING_REF(STRING_UNICODE, BE, addr, "Address", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_REDIR_SUBADDR_FIXED    0x03")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_REDIR_SUBADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_REDIRECTING_SUBADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        COMMENT(COMMENT_TEXT,
            "See 'Redirecting Party Subaddress IE' in 3GPP TS 24.008 "
            "ch. 10.5.4.21c. Byte contains octet 2 from "
            "'Redirecting Party Subaddress IE'.")
        REFERENCE(8, BE, addr_len, "Subaddress length", N)
        COMMENT(COMMENT_TEXT,
            "See 'Redirecting Party Subaddress IE' in 3GPP TS 24.008 "
            "ch. 10.5.4.21c. First byte contains octet 3 from "
            "'Redirecting Party Subaddress IE'.")
        SEQ_OF_REF(addr, "Subaddress", CALL_MODEM_HEX_DATA, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_REMOTE_ADDR_FIXED    0x06")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_REMOTE_ADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_REMOTE_ADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(addr_type, "Address type", CALL_MODEM_ADDRESS_TYPE)
        VALUE_CONST(presentation, "Presentation indicator",
            CALL_MODEM_PRESENTATION_SCREEN_INDICATOR)
        FILLER_EX(unused, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE,123)
        REFERENCE(8, BE, addr_len, "Address length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for address string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', "
            "'a', 'b' and 'c'.")
        STRING_REF(STRING_UNICODE, BE, addr, "Address", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_REMOTE_SUBADDR_FIXED    0x03")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_REMOTE_SUBADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_REMOTE_SUBADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        COMMENT(COMMENT_TEXT,
            "See 'ISDN-SubaddressString' in 3GPP TS 29.002 ch. 17.7.8. "
            "Byte contains 'ISDN-SubaddressString' length.")
        REFERENCE(8, BE, addr_len, "Subaddress length", N)
        COMMENT(COMMENT_TEXT,
            "See 'ISDN-SubaddressString' in 3GPP TS 29.002 ch. 17.7.8. "
            "First byte contains 'type of subbaddress' octet from "
            "'ISDN-SubaddressString'.")
        SEQ_OF_REF(addr, "Subaddress", CALL_MODEM_HEX_DATA, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DIAGN_STR")

    SB_BEGIN(CALL_MODEM_SB_DIAGNOSTICS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(condition, "Condition", CALL_MODEM_CONDITION)
        FILLER_EX(unused, 8, 1)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_SS_DIAGN_STR")

    SB_BEGIN(CALL_MODEM_SB_SS_DIAGNOSTICS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(diagnostics, "SS diagnostics", CALL_MODEM_SS_DIAGNOSTICS)
        FILLER_EX(unused, 8, 1)
    SB_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_NEW_DEST_FIXED    0x06")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_NEW_DEST_STR")

    COMMENT(COMMENT_PARAGRAPH,
         "See 'Cause IE' in 3GPP TS 24.008 ch. 10.5.4.11. "
         "Field contains values from cause diagnostics octet 5 of "
         "'Cause IE' onwards when octets are coded according to NOTE 5. "
         "Note is applicable for cause 22 and coding of the field "
         "is same as for 'Called Party BCD Number IE'.")

    SB_BEGIN(CALL_MODEM_SB_NEW_DESTINATION, "001.003", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(addr_type, "Address type", CALL_MODEM_ADDRESS_TYPE)
        FILLER_EX(unused1, 8, 1)
        FILLER_EX(unused2, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 123)
        REFERENCE(8, BE, addr_len, "Address length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for address string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', "
            "'a', 'b' and 'c'.")
        STRING_REF(STRING_UNICODE, BE, addr, "Address", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    SB_BEGIN(CALL_MODEM_SB_NEW_DESTINATION, "", "001.003")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(addr_type, "Address type", CALL_MODEM_ADDRESS_TYPE)
        VALUE_CONST(presentation, "Presentation indicator",
            CALL_MODEM_PRESENTATION_SCREEN_INDICATOR)
        FILLER_EX(unused, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 123)
        REFERENCE(8, BE, addr_len, "Address length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for address string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', "
            "'a', 'b' and 'c'.")
        STRING_REF(STRING_UNICODE, BE, addr, "Address", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_NOTIFY_STR")

    SB_BEGIN(CALL_MODEM_SB_NOTIFY, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(notification, "Notification indicator",
            CALL_MODEM_NOTIFICATION_INDICATOR)
        FILLER_EX(unused, 8, 1)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_SS_NOTIFY_STR")

    SB_BEGIN(CALL_MODEM_SB_SS_NOTIFY, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(ss_notification, "SS notification",
            CALL_MODEM_SS_NOTIFICATION)
        FILLER_EX(unused, 8, 1)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_SS_CODE_STR")

    SB_BEGIN(CALL_MODEM_SB_SS_CODE, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(mmi_ss_code, "MMI SS code", CALL_MODEM_MMI_SS_CODES )
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_SS_STATUS_STR")

    SB_BEGIN(CALL_MODEM_SB_SS_STATUS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(ss_status, "SS status", CALL_MODEM_SS_STATUS)
        FILLER_EX(unused, 8, 1)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_SS_NOTIFY_IND_STR")

    SB_BEGIN(CALL_MODEM_SB_SS_NOTIFY_INDICATOR, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(ss_indicator, "SS indicator", CALL_MODEM_SS_INDICATOR)
        FILLER_EX(unused, 8, 1)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_SS_HOLD_IND_STR")

    SB_BEGIN(CALL_MODEM_SB_SS_HOLD_INDICATOR, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(ss_hold_indicator, "SS hold indicator",
            CALL_MODEM_SS_HOLD_INDICATOR)
        FILLER_EX(unused, 8, 1)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_SS_ECT_IND_STR")

    SB_BEGIN(CALL_MODEM_SB_SS_ECT_INDICATOR, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(ss_ect_indicator, "SS ECT indicator",
            CALL_MODEM_SS_ECT_INDICATOR)
        FILLER_EX(unused, 8, 1)
    SB_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_DEST_CS_ADDR_FIXED    0x06")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DEST_CS_ADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_DESTINATION_CS_ADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 246)
        COMMENT(COMMENT_TEXT,
            "See 'Called Party BCD Number IE' in 3GPP TS 24.008 "
            "ch. 10.5.4.7. Byte contains octet 2 from 'Called Party "
            "BCD Number IE'.")
        REFERENCE(8, BE, addr_len, "Called Party Number length", N)
        COMMENT(COMMENT_TEXT,
            "See 'Called Party BCD Number IE' in 3GPP TS 24.008 "
            "ch. 10.5.4.7. First byte contains octet 3 from 'Called Party "
            "BCD Number IE'.")
        SEQ_OF_REF(addr, "Called Party Number", CALL_MODEM_HEX_DATA, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)        
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* CALL_MODEM_SB_BC */

    SEQ_BEGIN(CALL_MODEM_SB_DATA, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, bc_data, "BC Data", DEC)
    SEQ_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_BC_FIXED    0x03")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_BC_STR")

    SB_BEGIN(CALL_MODEM_SB_BC, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        COMMENT(COMMENT_TEXT,
            "See 'Bearer Capability IE' in 3GPP TS 24.008 ch. 10.5.4.5. "
            "Byte contains octet 2 from 'Bearer Capability IE'.")
        REFERENCE(8, BE, bc_length, "BC length", N)
        COMMENT(COMMENT_TEXT,
            "See 'Bearer Capability IE' in 3GPP TS 24.008 ch. 10.5.4.5. "
            "First byte contains octet 3 from 'Bearer Capability IE'.")
        SEQ_OF_REF(bc_data, "BC Data", CALL_MODEM_SB_DATA, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* CALL_MODEM_SB_RAB */

#ifndef DO_VENDOR_OUTPUT

    SEQ_BEGIN(CALL_MODEM_RAB_INFO_DATA, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, rb, "RB Identity", HEX)
    SEQ_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_RAB_INFO_FIXED    0x04")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_RAB_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_RAB_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        COMMENT(COMMENT_TEXT,
            "See 'RAB ID' in 3GPP TS 25.331.")
        VALUE(8, BE, rab_id, "RAB ID", HEX)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 8)
        REFERENCE(8, BE, num_of_rbs, "Number of RB identities", N)
        COMMENT(COMMENT_TEXT,
            "See 'Radio Bearer' in 3GPP TS 25.331.")
        SEQ_OF_REF(rb, "RB Identity", CALL_MODEM_RAB_INFO_DATA, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

#endif /* !DO_VENDOR_OUTPUT */

    /* CALL_MODEM_CAUSE_OF_NO_CLI */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_CAUSE_OF_NO_CLI_STR")

    SB_BEGIN(CALL_MODEM_SB_CAUSE_OF_NO_CLI, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(cause, "Cause of No CLI", CALL_MODEM_CAUSE_OF_NO_CLI_VALUES)
        FILLER_EX(padding, 8, 1)
    SB_END

    /* CALL_MODEM_MM_CAUSE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_MM_CAUSE_STR")

    SB_BEGIN(CALL_MODEM_SB_MM_CAUSE, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(cause, "MM cause", CALL_MODEM_MM_CAUSE_VALUES)
        FILLER_EX(padding, 8, 1)
    SB_END

    /* CALL_MODEM_SB_PRIM_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_MSG_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_MSG_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(msg, "Message",
            CALL_MODEM_MSG)
        VALUE_CONST(msg_dir, "Message direction",
            CALL_MODEM_MSG_DIRECTION)
        COMMENT(COMMENT_TEXT,
            "Transaction identifier from the received or sent message. "
            "TI flag is coded to bit 8 and bits 5 to 7 are TI value. "
            "Bits 1 to 4 are set to zero. If internal call release has "
            "occurred field is coded as clearing would have been initiated "
            "by mobile i.e. similar to messages sent to network.")
        VALUE(8, BE, transaction_id, "Transaction ID", HEX)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
    SB_END

    /* CALL_MODEM_DETAILED_CAUSE */

    SEQ_BEGIN(CALL_MODEM_DETAILED_CAUSE_DATA, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, cause, "Cause", DEC)
    SEQ_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_DETAIL_CAUSE_FIXED    0x03")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DETAIL_CAUSE_STR")

    SB_BEGIN(CALL_MODEM_SB_DETAILED_CAUSE, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        COMMENT(COMMENT_TEXT,
            "See 'Cause IE' in 3GPP TS 24.008 ch. 10.5.4.11. "
            "Byte contains octet 2 from 'Cause IE'.")
        REFERENCE(8, BE, cause_len, "Cause Length", N)
        COMMENT(COMMENT_TEXT,
            "See 'Cause IE' in 3GPP TS 24.008 ch. 10.5.4.11. "
            "First byte contains octet 3 from 'Cause IE'.")
        SEQ_OF_REF(cause, "Cause", CALL_MODEM_DETAILED_CAUSE_DATA, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    /* CALL_MODEM_SS_DATA */

    SEQ_BEGIN(CALL_MODEM_SS_DATA, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, ss_data, "SS Data", DEC)
    SEQ_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_SS_DATA_FIXED    0x03")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_SS_DATA_STR")

    SB_BEGIN(CALL_MODEM_SB_SS_DATA, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        COMMENT(COMMENT_TEXT,
            "See 'Facility IE' in 3GPP TS 24.008 ch. 10.5.4.15. "
            "Byte contains octet 2 from 'Facility IE'.")
        REFERENCE(8, BE, ss_data_len, "SS Data Length", N)
        COMMENT(COMMENT_TEXT,
            "See 'Facility IE' in 3GPP TS 24.008 ch. 10.5.4.15. "
            "First byte contains octet 3 from 'Facility IE'.")
        SEQ_OF_REF(ss_data, "SS Data", CALL_MODEM_SS_DATA, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    /* CALL_MODEM_ALS_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_ALS_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_ALS_INFO, "", "") 
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(als_sim_status, "ALS SIM status", CALL_MODEM_ALS_STATUS)
        VALUE_CONST(als_pp_status, "ALS product profile status", CALL_MODEM_ALS_STATUS)
    SB_END

    /* CALL_MODEM_SB_STATE_AUTO_CHANGE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_ST_AUTO_CH_STR")

    SB_BEGIN(CALL_MODEM_SB_STATE_AUTO_CHANGE, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(state_auto_change, "State auto change", CALL_MODEM_AUTO_ST_CHANGE)
        FILLER_EX(unused, 8, 1)
    SB_END

    /* CALL_MODEM_SB_EMERG_NUMBER_INFO */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_EMERG_NBR_INFO_FIXED    0x06")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_EMERG_NBR_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_EMERG_NUMBER_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        COMMENT(COMMENT_TEXT,
        "Field links CALL_MODEM_EMERG_NUMBER and CALL_MODEM_EMERG_NUMBER_INFO sub blocks. "
        "Sub blocks that have same value for link id field contain information about same number.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 255)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_NO_LINK_ID)
        VALUE(8, BE, link_id, "Link ID", DEC)
        VALUE_CONST(serv_category, "Service Category", CALL_MODEM_EMERG_SERVICE_CATEGORY)
        FILLER_EX(unused, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 123)
        REFERENCE(8, BE, alpha_id_len, "Alpha ID length", N)
        STRING_REF(STRING_UNICODE, BE, alpha_id, "Alpha ID", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

   /* CALL_MODEM_SB_STATUS_MODE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_CALL_ST_MODE_STR")

    SB_BEGIN(CALL_MODEM_SB_STATUS_MODE, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(mode, "mode", CALL_MODEM_STATUS_MOD)
        FILLER_EX(unused, 8, 1)
    SB_END

    /* CALL_MODEM_SB_ADDR_AND_STATUS_INFO */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_ADDR_AND_ST_INFO_FIXED    0x0C")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_ADDR_AND_ST_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_ADDR_AND_STATUS_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        VALUE_CONST(mode, "Call mode", CALL_MODEM_MODE)
        VALUE_CONST(mode_info, "Call mode info", CALL_MODEM_MODE_INFO)
        VALUE_CONST(status, "Call status", CALL_MODEM_STATUS)
        FILLER_EX(unused1, 8, 1)
        COMMENT(COMMENT_TEXT,
        "Field links CALL_MODEM_ORIGIN_INFO and CALL_MODEM_ADDR_AND_STATUS_INFO sub blocks "
        "in CALL_MODEM_STATUS_RESP. "
        "Sub blocks that have same value for link id field contain information about same number.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 255)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_NO_LINK_ID)
        VALUE(8, BE, link_id, "Link ID", DEC)
        VALUE_CONST(addr_type, "Address type", CALL_MODEM_ADDRESS_TYPE)
        VALUE_CONST(presentation, "Presentation indicator",
            CALL_MODEM_PRESENTATION_SCREEN_INDICATOR)
        FILLER_EX(unused2, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 80)
        REFERENCE(8, BE, addr_len, "Address length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for address string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', "
            "'a', 'b' and 'c'.")
        STRING_REF(STRING_UNICODE, BE, addr, "Address", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    /* CALL_MODEM_SB_DTMF_TIMERS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DTMF_TIMERS_STR")

    SB_BEGIN(CALL_MODEM_SB_DTMF_TIMERS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 5)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_DTMF_NO_DELAY)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_DTMF_DEFAULT)
        VALUE(16, BE, dtmf_dur, "DTFM duration in milliseconds", DEC )
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 5)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1000)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_DTMF_NO_DELAY)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_DTMF_DEFAULT)
        VALUE(16, BE, dtmf_gap, "DTMF gap in milliseconds", DEC )
        FILLER_EX(unused, 8, 1)
        FILLER_EX(unused2, 8, 1)
    SB_END

    /* CALL_MODEM_SB_NAS_SYNC_INDICATOR */

#ifndef DO_VENDOR_OUTPUT

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_NAS_SYNC_IND_STR")

    SB_BEGIN(CALL_MODEM_SB_NAS_SYNC_INDICATOR, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH) 
        COMMENT(COMMENT_TEXT, 
            "Four least significant bits of the CoID. "
            "See 'CoID' in 3GPP TS 24.008 ch. 5.2.1.11.")
        VALUE(8, BE, coid, "Codec ID", DEC )
        FILLER_EX(unused, 8, 1)
    SB_END

#endif /* !DO_VENDOR_OUTPUT */

    /* CALL_MODEM_SB_NW_CAUSE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_NW_CAUSE_STR")

    SB_BEGIN(CALL_MODEM_SB_NW_CAUSE, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        FILLER_EX(unused, 8, 1)
        VALUE_CONST(cause, "Cause", CALL_MODEM_NW_CAUSE)
    SB_END

    /* CALL_MODEM_SB_DESTINATION_ISI_ADDRESS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_DEST_ISI_ADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_DESTINATION_ISI_ADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(addr_type, "Address type", CALL_MODEM_ADDRESS_TYPE)
        FILLER_EX(unused1, 8, 1)
        FILLER_EX(unused2, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of Unicode characters")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 123)
        REFERENCE(8, BE, addr_len, "Address length", N)
        COMMENT(COMMENT_TEXT,
            "Possible values for address string characters are unicodes "
            "'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', "
            "'a', 'b' and 'c'.")
        STRING_REF(STRING_UNICODE, BE, addr, "Address", N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    /* CALL_MODEM_SB_RESOURCE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_RES_STR")

    SB_BEGIN(CALL_MODEM_SB_RESOURCE, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(res, "Resources", CALL_MODEM_RESOURCE_IDS)
    SB_END

    /* CALL_MODEM_SB_RESOURCE_CONF */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_RES_CONF_STR")

    COMMENT(COMMENT_TEXT, "Resource mask and operation resources mask fiels are "
        " used to set what resources and operation resources are configured in "
        " requests that are sent to Call Server. Call Server does not change "
        " the status of the resources which mask is set to zero.")
    SB_BEGIN(CALL_MODEM_SB_RESOURCE_CONF, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(res, "Resources", CALL_MODEM_RESOURCE_IDS)
        VALUE_CONST(res_mask, "Resource mask", CALL_MODEM_RESOURCE_IDS_MASK)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
    SB_END

    /* CALL_MODEM_SB_RESOURCE_CONF_REQUIRED */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_RES_CONF_REQ_STR")

    COMMENT(COMMENT_TEXT, "Resource configuration required field indicates "
        "for what resources the resource configuration is mandatory before "
        "resources are allowed. These settings are read from product profile. ")
    SB_BEGIN(CALL_MODEM_SB_RESOURCE_CONF_REQUIRED, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(res_pp, "Resource configuration required", 
            CALL_MODEM_RESOURCE_IDS_CONF_REQ)
    SB_END

    /* CALL_MODEM_SB_RESOURCE_SEQ_ID */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_RES_SEQ_ID_STR")

    SB_BEGIN(CALL_MODEM_SB_RESOURCE_SEQ_ID, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 255)
        VALUE(8, BE, sequence_id, "Sequence id", DEC )
        FILLER_EX(padding, 8, 1)
    SB_END

    /* CALL_MODEM_SB_RESOURCE_STATUS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_RES_STATUS_STR")

    SB_BEGIN(CALL_MODEM_SB_RESOURCE_STATUS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(res_status, "Resource status", CALL_MODEM_RESOURCE_STATUS)
        FILLER_EX(padding, 8, 1)
    SB_END

    /* CALL_MODEM_SB_RESOURCE_CHECK_INFO */

    DER_BIT_TBL_BEGIN(CALL_MODEM_RESOURCE_CHECK_IDS,
        CALL_MODEM_RESOURCE_IDS, "", "")
        DER_BIT_TBL_ENTRY(CALL_MODEM_RES_ID_MO_INIT)
    DER_BIT_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_RES_CHECK_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_RESOURCE_CHECK_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(res, "Resources", CALL_MODEM_RESOURCE_CHECK_IDS)
    SB_END

    /* CALL_MODEM_SB_CHECK_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_CHECK_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_CHECK_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(check_info, "Check info", CALL_MODEM_CHECK_INFO)
        FILLER_EX(padding, 8, 1)
    SB_END

    /* CALL_MODEM_SB_LINE_ID */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_LINE_ID_STR")

    SB_BEGIN(CALL_MODEM_SB_LINE_ID, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(line_id, "Line ID", CALL_MODEM_LINE_ID)
        FILLER_EX(padding, 8, 1)
    SB_END

    /* CALL_MODEM_SB_USER_TO_USER */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF,
        "#define CALL_MODEM_SIZEOF_USER_TO_USER_FIXED    0x05")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_USER_TO_USER_STR")

    SB_BEGIN(CALL_MODEM_SB_USER_TO_USER, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(uus_type, "User to user type", CALL_MODEM_UUS_TYPE)
        VALUE_CONST(uus_act_type, "User to user activation type", CALL_MODEM_UUS_ACTIVATION_TYPE)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 240)
        COMMENT(COMMENT_TEXT,
            "See 'User-to-User IE' in 3GPP TS 24.008 ch. 10.5.4.25. "
            "Byte contains octet 2 from 'User-to-User IE'.")
        REFERENCE(8, BE, utou_len, "User to user length", N)
        COMMENT(COMMENT_TEXT,
            "See 'User-to-User IE' in 3GPP TS 24.008 ch. 10.5.4.25. "
            "First byte contains octet 3 from 'User-to-User IE'.")
        SEQ_OF_REF(utou, "User to user", CALL_MODEM_HEX_DATA, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SB_SIZEOF_ORIGIN_CS_ADDR_FIXED    0x03")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_ORIGIN_CS_ADDR_STR")

    SB_BEGIN(CALL_MODEM_SB_ORIGIN_CS_ADDRESS, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 246)
        COMMENT(COMMENT_TEXT,
            "See 'Calling Party BCD Number IE' in 3GPP TS 24.008 "
            "ch. 10.5.4.9. Byte contains octet 2 from 'Calling Party "
            "BCD Number IE'.")
        REFERENCE(8, BE, addr_len, "Number length", N)
        COMMENT(COMMENT_TEXT,
            "See 'Calling Party BCD Number IE' in 3GPP TS 24.008 "
            "ch. 10.5.4.9. First byte contains octet 3 from 'Calling "
            "Party BCD Number IE'.")
        SEQ_OF_REF(addr, "Number", CALL_MODEM_HEX_DATA, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)        
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    /* CALL_MODEM_SB_REQ_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_REQ_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_REQ_INFO, "", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        COMMENT(COMMENT_TEXT,
            "Transaction Identifier from the request.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 255)
        VALUE(8, BE, tr_id, "Transaction id", DEC )
        FILLER_EX(padding, 8, 1)
    SB_END

    /* CALL_MODEM_SB_EMERG_NUMBER_MOD_INFO */

    COMMENT(COMMENT_PARAGRAPH,
        "Emergency number is valid in the country defined by the Mobile "
        "Country Code. Mobile Country Code is coded as ASCII string. "
        "MCC can be also coded empty by setting all digits "
        "to CALL_MODEM_NULL (0x00). In that case emergency number is valid "
        "regardless of the MCC. For MCCs that have less than "
        "three digits ASCII zeros are filled before the number e.g. for "
        "MCC 10 the programmed number would be 010 in ASCII.")

    COMMENT(COMMENT_NEWLINE, "")

    COMMENT(COMMENT_PARAGRAPH,
        "Mobile Country Code range can be used in case one country has "
        "several MCCs. In that case MCC is used as a base value and range "
        "defines how many country codes that are in the sequence belong to "
        "same country. Range can be also set to default by setting value "
        "to CALL_MODEM_NULL (0x00). "
        "E.g. for United Kingdom valid MCCs are 234 and 235. In that "
        "case MCC would be coded as 234 and range would be 2 meaning that "
        "there is two numbers in sequence.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_EMERG_NBR_MOD_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_EMERG_NUMBER_MOD_INFO, "002.003", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)

        COMMENT(COMMENT_TEXT,
            "Field links CALL_MODEM_EMERG_NUMBER and "
            "CALL_MODEM_SB_EMERG_NUMBER_MOD_INFO sub blocks in "
            "CALL_MODEM_EMERG_NBR_MODIFY_REQ. "
            "Sub blocks that have same value for link id field contain "
            "information about same number.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 255)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_NO_LINK_ID)
        VALUE(8, BE, link_id, "Link ID", DEC)

        VALUE_CONST(serv_category, "Service Category", 
            CALL_MODEM_EMERG_SERVICE_CATEGORY)

        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, '0')
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, '9')
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_NULL)
        VALUE(8, BE, mcc_digit_1, "MCC digit 1", ASCII)

        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, '0')
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, '9')
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_NULL)
        VALUE(8, BE, mcc_digit_2, "MCC digit 2", ASCII)

        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, '0')
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, '9')
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_NULL)
        VALUE(8, BE, mcc_digit_3, "MCC digit 3", ASCII)

        COMMENT(COMMENT_PARAGRAPH,
            "NULL value means default range i.e. MCC consists of one value. "
            "Other values define how many MCCs belong to range.")

        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, '2')
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, '9')
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, CALL_MODEM_NULL)
        VALUE(8, BE, mcc_range, "MCC range", ASCII)
    SB_END

    /* CALL_MODEM_SB_VCC_STATUS_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "CALL_MODEM_SB_VCC_STATUS_INFO_STR")

    SB_BEGIN(CALL_MODEM_SB_VCC_STATUS_INFO, "030.000", "")
        REFERENCE(8, BE, sub_block_id, "Sub Block ID", SB_ID)
        REFERENCE(8, BE, sub_block_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(vcc_call_mode, "VCC call mode", CALL_MODEM_VCC_MODE)
        VALUE_CONST(vcc_call_status, "VCC call status", CALL_MODEM_VCC_STATUS)
    SB_END


    /* Messages */

    /* CALL_MODEM_CREATE */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_CREATE_REQ_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_CREATE_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(mode, "Mode", CALL_MODEM_SB_MODE, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_PRE_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_POST_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_SUBADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_SUBADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_CS_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_ISI_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_BC)
            SB_LST_ENTRY(CALL_MODEM_SB_EMERG_NUMBER_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_USER_TO_USER)
            SB_LST_ENTRY(CALL_MODEM_SB_CHECK_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE_CHECK_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_LINE_ID)
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_CREATE_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_CREATE_REQ, CALL_MODEM_CREATE_RESP)

    /* CALL_MODEM_COMING_IND */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_COMING_IND_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_COMING_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(mode, "Mode", CALL_MODEM_SB_MODE, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_SUBADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_SUBADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_REDIRECTING_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_REDIRECTING_SUBADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE_OF_NO_CLI)
            SB_LST_ENTRY_VER(CALL_MODEM_SB_CAUSE, "", "002.000")
            SB_LST_ENTRY(CALL_MODEM_SB_USER_TO_USER)
            SB_LST_ENTRY_VER(CALL_MODEM_SB_ALERTING_PATTERN, "002.000","")
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_MO_ALERT_IND */

    MSG_BEGIN(CALL_MODEM_MO_ALERT_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
         SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_ALERTING_INFO)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_MT_ALERT_IND */

    MSG_BEGIN(CALL_MODEM_MT_ALERT_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "pattern")
            SB_LST_ENTRY(CALL_MODEM_SB_ALERTING_PATTERN)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_WAITING_IND */

    MSG_BEGIN(CALL_MODEM_WAITING_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "pattern")
            SB_LST_ENTRY(CALL_MODEM_SB_ALERTING_PATTERN)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_ANSWER */

    MSG_BEGIN(CALL_MODEM_ANSWER_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_SUBADDRESS)
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_ANSWER_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_ANSWER_REQ, CALL_MODEM_ANSWER_RESP)

    /* CALL_MODEM_RELEASE */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_RELEASE_REQ_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_RELEASE_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SEQ_OF(cause, "Cause", CALL_MODEM_SB_CAUSE, 1)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_STATE_AUTO_CHANGE)
            SB_LST_ENTRY_VER(CALL_MODEM_SB_OPERATION, "030.001", "")
            SB_LST_ENTRY_VER(CALL_MODEM_SB_DESTINATION_ADDRESS, 
                "030.001", "")
            SB_LST_ENTRY_VER(CALL_MODEM_SB_DESTINATION_SUBADDRESS,
                "030.001", "")
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_RELEASE_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
            SB_LST_ENTRY_VER(CALL_MODEM_SB_OPERATION, "030.001", "")
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_RELEASE_REQ, CALL_MODEM_RELEASE_RESP)

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_RELEASE_IND_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_RELEASE_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(cause, "Cause", CALL_MODEM_SB_CAUSE, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_RELEASE_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_DIAGNOSTICS)
            SB_LST_ENTRY(CALL_MODEM_SB_SS_DIAGNOSTICS)
            SB_LST_ENTRY(CALL_MODEM_SB_NEW_DESTINATION)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_TERMINATED_IND */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_TERMINATED_IND_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_TERMINATED_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 2)
        SEQ_OF(cause, "Cause", CALL_MODEM_SB_CAUSE, 1)
        SEQ_OF(mode, "Mode", CALL_MODEM_SB_MODE, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_DIAGNOSTICS)
            SB_LST_ENTRY(CALL_MODEM_SB_SS_DIAGNOSTICS)
            SB_LST_ENTRY(CALL_MODEM_SB_NEW_DESTINATION)
            SB_LST_ENTRY(CALL_MODEM_SB_MM_CAUSE)
            SB_LST_ENTRY(CALL_MODEM_SB_NW_CAUSE)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_STATUS */

    MSG_BEGIN(CALL_MODEM_STATUS_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "mode")
            SB_LST_ENTRY(CALL_MODEM_SB_STATUS_MODE)
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_STATUS_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(call_id, 8, 1)
        COMMENT(COMMENT_TEXT, "Number of sub blocks depends on number of calls "
            "and call status mode. See i_call_modem_f.doc")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "cause")
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "status_info")
            SB_LST_ENTRY(CALL_MODEM_SB_STATUS_INFO)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "addr_and_status_info")
            SB_LST_ENTRY(CALL_MODEM_SB_ADDR_AND_STATUS_INFO)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "origin_info")
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_INFO)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_STATUS_REQ, CALL_MODEM_STATUS_RESP)


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_STATUS_IND_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_STATUS_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 2)
        SEQ_OF(status, "Status", CALL_MODEM_SB_STATUS, 1)
        SEQ_OF(mode, "Mode", CALL_MODEM_SB_MODE, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_SUBADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_SUBADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_PRE_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_POST_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_CONNECTED_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_CONNECTED_SUBADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_REDIRECTING_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_REDIRECTING_SUBADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DETAILED_CAUSE)
            SB_LST_ENTRY(CALL_MODEM_SB_EMERG_NUMBER_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_NW_CAUSE)
            SB_LST_ENTRY(CALL_MODEM_SB_USER_TO_USER)
            SB_LST_ENTRY(CALL_MODEM_SB_CHECK_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_LINE_ID)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_PRESENT_IND */

    MSG_BEGIN(CALL_MODEM_PRESENT_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_present, "Call present", CALL_MODEM_PRESENT_INFO)
        COMMENT(COMMENT_TEXT, "For future expansion")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)   
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_CONTROL */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_CONTROL_REQ_FIXED    0x04") 

    MSG_BEGIN(CALL_MODEM_CONTROL_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(operation, "Operation", CALL_MODEM_SB_OPERATION, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
        SB_LST_REF_END
    MSG_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_CONTROL_RESP_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_CONTROL_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(operation, "Operation", CALL_MODEM_SB_OPERATION, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_CONTROL_REQ, CALL_MODEM_CONTROL_RESP)


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_CONTROL_IND_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_CONTROL_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(operation, "Operation", CALL_MODEM_SB_OPERATION, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
            SB_LST_ENTRY(CALL_MODEM_SB_DIAGNOSTICS)
            SB_LST_ENTRY(CALL_MODEM_SB_SS_DIAGNOSTICS)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_DTMF_SEND */

    MSG_BEGIN(CALL_MODEM_DTMF_SEND_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "digit")
            SB_LST_ENTRY(CALL_MODEM_SB_DTMF_DIGIT)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "string")
            SB_LST_ENTRY(CALL_MODEM_SB_DTMF_STRING)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "bcd_string")
            SB_LST_ENTRY(CALL_MODEM_SB_DTMF_BCD_STRING)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "dtmf_info")
            SB_LST_ENTRY(CALL_MODEM_SB_DTMF_INFO)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "dtmf_timer")
            SB_LST_ENTRY(CALL_MODEM_SB_DTMF_TIMERS)
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_DTMF_SEND_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_DTMF_SEND_REQ, CALL_MODEM_DTMF_SEND_RESP)

    /* CALL_MODEM_DTMF_STOP */

    MSG_BEGIN(CALL_MODEM_DTMF_STOP_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        COMMENT(COMMENT_TEXT, "For future expansion")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)   
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_DTMF_STOP_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "cause")
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "string")
            SB_LST_ENTRY(CALL_MODEM_SB_DTMF_STRING)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "bcd_string")
            SB_LST_ENTRY(CALL_MODEM_SB_DTMF_BCD_STRING)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_DTMF_STOP_REQ, CALL_MODEM_DTMF_STOP_RESP)

    /* CALL_MODEM_DTMF_STATUS_IND */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_DTMF_STATUS_IND_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_DTMF_STATUS_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(status, "DTMF Status", CALL_MODEM_SB_DTMF_STATUS, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
            SB_LST_ENTRY(CALL_MODEM_SB_DTMF_STRING)
            SB_LST_ENTRY(CALL_MODEM_SB_DTMF_BCD_STRING)
            SB_LST_ENTRY(CALL_MODEM_SB_DTMF_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_DIAGNOSTICS)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_DTMF_TONE_IND */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_DTMF_TONE_IND_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_DTMF_TONE_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(tone, "DTMF Tone", CALL_MODEM_SB_DTMF_TONE, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_RECONNECT_IND */

    MSG_BEGIN(CALL_MODEM_RECONNECT_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(reconnect_status, "Reconnect Status",
            CALL_MODEM_RECONNECT_STATUS)
        COMMENT(COMMENT_TEXT, "For future expansion")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)   
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_PROPERTY_GET */

    MSG_BEGIN(CALL_MODEM_PROPERTY_GET_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(property, "Property", CALL_MODEM_PROPERTY)
        COMMENT(COMMENT_TEXT, "For future expansion")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)   
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_PROPERTY_GET_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(property, "Property", CALL_MODEM_PROPERTY)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
            SB_LST_ENTRY(CALL_MODEM_SB_PROPERTY_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_CUG_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_ALS_INFO)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_PROPERTY_GET_REQ, CALL_MODEM_PROPERTY_GET_RESP)

    /* CALL_MODEM_PROPERTY_SET */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_PROPERTY_SET_REQ_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_PROPERTY_SET_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(property_info, "Property Value", CALL_MODEM_SB_PROPERTY_INFO, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CUG_INFO)
        SB_LST_REF_END
    MSG_END


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_PROPERTY_SET_RESP_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_PROPERTY_SET_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(property_info, "Property Value", CALL_MODEM_SB_PROPERTY_INFO, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
            SB_LST_ENTRY(CALL_MODEM_SB_CUG_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_ALS_INFO)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_PROPERTY_SET_REQ, CALL_MODEM_PROPERTY_SET_RESP)


    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_PROPERTY_SET_IND_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_PROPERTY_SET_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(property, "Property", CALL_MODEM_PROPERTY)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(property_info, "Property Value", CALL_MODEM_SB_PROPERTY_INFO, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CUG_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_ALS_INFO)
        SB_LST_REF_END
    MSG_END


    /* CALL_MODEM_EMERG_NBR_CHECK */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_EMERG_NBR_CHECK_REQ_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_EMERG_NBR_CHECK_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(number, "Address", CALL_MODEM_SB_DESTINATION_ADDRESS, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
        SB_LST_REF_END
    MSG_END


    MSG_BEGIN(CALL_MODEM_EMERG_NBR_CHECK_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(status, "Check status", CALL_MODEM_EMERG_NUMBER_CHECK_STATUS)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_EMERG_NUMBER)
            SB_LST_ENTRY(CALL_MODEM_SB_EMERG_NUMBER_INFO)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_EMERG_NBR_CHECK_REQ, CALL_MODEM_EMERG_NBR_CHECK_RESP)


    /* CALL_MODEM_EMERG_NBR_GET */

    MSG_BEGIN(CALL_MODEM_EMERG_NBR_GET_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        COMMENT(COMMENT_TEXT, "For future expansion")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_EMERG_NBR_GET_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
            SB_LST_ENTRY(CALL_MODEM_SB_EMERG_NUMBER)
            SB_LST_ENTRY(CALL_MODEM_SB_EMERG_NUMBER_INFO)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_EMERG_NBR_GET_REQ, CALL_MODEM_EMERG_NBR_GET_RESP)

    /* CALL_MODEM_EMERG_NBR_MODIFY */

    MSG_BEGIN(CALL_MODEM_EMERG_NBR_MODIFY_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(operation, "Operation", CALL_MODEM_EMERG_NUMBER_OPERATION)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N, 
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "number")
            SB_LST_ENTRY(CALL_MODEM_SB_EMERG_NUMBER)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "number_mod_info")
            SB_LST_ENTRY_VER(CALL_MODEM_SB_EMERG_NUMBER_MOD_INFO, "002.003",
            "")
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_EMERG_NBR_MODIFY_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(operation, "Operation", CALL_MODEM_EMERG_NUMBER_OPERATION)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_EMERG_NBR_MODIFY_REQ, CALL_MODEM_EMERG_NBR_MODIFY_RESP)


    /* CALL_MODEM_NOTIFICATION_IND */

    MSG_BEGIN(CALL_MODEM_NOTIFICATION_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "notify")
            SB_LST_ENTRY(CALL_MODEM_SB_NOTIFY)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "ss_code")
            SB_LST_ENTRY(CALL_MODEM_SB_SS_CODE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "ss_status")
            SB_LST_ENTRY(CALL_MODEM_SB_SS_STATUS)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "ss_notify")
            SB_LST_ENTRY(CALL_MODEM_SB_SS_NOTIFY)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "ss_notify_ind")
            SB_LST_ENTRY(CALL_MODEM_SB_SS_NOTIFY_INDICATOR)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "ss_hold_ind")
            SB_LST_ENTRY(CALL_MODEM_SB_SS_HOLD_INDICATOR)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "ss_etc_ind")
            SB_LST_ENTRY(CALL_MODEM_SB_SS_ECT_INDICATOR)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "remote_addr")
            SB_LST_ENTRY(CALL_MODEM_SB_REMOTE_ADDRESS)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "remote_subaddr")
            SB_LST_ENTRY(CALL_MODEM_SB_REMOTE_SUBADDRESS)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "cug_info")
            SB_LST_ENTRY(CALL_MODEM_SB_CUG_INFO)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "origin_info")
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_INFO)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "pattern")
            SB_LST_ENTRY_VER(CALL_MODEM_SB_ALERTING_PATTERN, "", "002.003")
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "alert_info")
            SB_LST_ENTRY(CALL_MODEM_SB_ALERTING_INFO)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_BLACKLIST_CLEAR */

    MSG_BEGIN(CALL_MODEM_BLACKLIST_CLEAR_REQ, MESSAGE_REQ, "001.003", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        COMMENT(COMMENT_TEXT, "For future expansion")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)   
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_BLACKLIST_CLEAR_REQ, MESSAGE_REQ, "", "001.003")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(call_id, 8, 1)
        COMMENT(COMMENT_TEXT, "For future expansion")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)   
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_BLACKLIST_CLEAR_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        COMMENT(COMMENT_TEXT, "For future expansion")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)   
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_BLACKLIST_CLEAR_REQ, CALL_MODEM_BLACKLIST_CLEAR_RESP)

    /* CALL_MODEM_BLACKLIST_TIMER_IND */

    MSG_BEGIN(CALL_MODEM_BLACKLIST_TIMER_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(duration, "Duration", CALL_MODEM_BLACKLIST_DURATION)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)   
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_ADDRESS)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_BLACKLIST_BLOCKED_IND */

    MSG_BEGIN(CALL_MODEM_BLACKLIST_BLOCKED_IND, MESSAGE_IND, "030.001", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(status, "Status", CALL_MODEM_BLACKLIST_STATUS)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)   
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_ADDRESS)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_GSM_BC_GET */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_BC_GET_REQ_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_BC_GET_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(padding, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(mode, "Mode", CALL_MODEM_SB_MODE, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_BC_GET_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(padding, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "cause")
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "ccp")
            SB_LST_ENTRY(CALL_MODEM_SB_BC)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_BC_GET_REQ, CALL_MODEM_BC_GET_RESP)


    /* CALL_MODEM_GSM_BC_CHECK */

    MSG_BEGIN(CALL_MODEM_BC_CHECK_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(padding, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "ccp")
            SB_LST_ENTRY(CALL_MODEM_SB_BC)
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_BC_CHECK_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(result, "BC Check Result", CALL_MODEM_BC_CHECK_RESULT)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "cause")
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_BC_CHECK_REQ, CALL_MODEM_BC_CHECK_RESP)


    /* CALL_MODEM_GSM_RAB_IND */

#ifndef DO_VENDOR_OUTPUT

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, 
        "#define CALL_MODEM_SIZEOF_RAB_IND_FIXED    0x04")

    MSG_BEGIN(CALL_MODEM_RAB_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        REFERENCE_TRANSFORM(N, M, ALG_SUB, 1)
        SEQ_OF(rab_info, "RAB Information", CALL_MODEM_SB_RAB_INFO, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", M,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "mode")
            SB_LST_ENTRY(CALL_MODEM_SB_MODE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "nas_sync_ind")
            SB_LST_ENTRY(CALL_MODEM_SB_NAS_SYNC_INDICATOR)
        SB_LST_REF_END
    MSG_END

#endif /* !DO_VENDOR_OUTPUT */

    /* CALL_MODEM_SS_DATA_IND */

    MSG_BEGIN(CALL_MODEM_SS_DATA_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        FILLER_EX(unused1, 8, 1)   /* Non-backwards compatible change: */
        FILLER_EX(unused2, 8, 1)   /* AIR IF SS operation and code     */
        FILLER_EX(unused3, 8, 1)
        FILLER_EX(unused4, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "ss_data")
            SB_LST_ENTRY(CALL_MODEM_SB_SS_DATA)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_EMERG_NBR_IND */

    MSG_BEGIN(CALL_MODEM_EMERG_NBR_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "number")
            SB_LST_ENTRY(CALL_MODEM_SB_EMERG_NUMBER)
            PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME,
            "emerg_number_info")
            SB_LST_ENTRY(CALL_MODEM_SB_EMERG_NUMBER_INFO)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_SERVICE_DENIED_IND */

    MSG_BEGIN(CALL_MODEM_SERVICE_DENIED_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        COMMENT(COMMENT_TEXT, "Message ID for requested service")
        VALUE(8, BE, req_message_id, "Requested Service Message ID", HEX)
        VALUE_CONST(additional_info, "Additional info about request",
            CALL_MODEM_REQ_ADDITIONAL_INFO)
        COMMENT(COMMENT_TEXT,
            "Call ID if message relates to some existing call. "
            "Otherwise CALL_MODEM_ID_NONE.")
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        FILLER_EX(unused1, 8, 1)
        FILLER_EX(unused2, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_PRE_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_POST_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_EMERG_NUMBER_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_MODE)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_SUBADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_OPERATION)
            SB_LST_ENTRY_VER(CALL_MODEM_SB_CHECK_INFO, "002.000", "")
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_RELEASE_END_REQ */

    MSG_BEGIN(CALL_MODEM_RELEASE_END_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        COMMENT(COMMENT_TEXT, "For future expansion")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)   
        SB_LST_REF_END
    MSG_END

    MSG_BEGIN(CALL_MODEM_RELEASE_END_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_RELEASE_END_REQ, CALL_MODEM_RELEASE_END_RESP)

    /* CALL_MODEM_USER_CONNECT_IND */

    MSG_BEGIN(CALL_MODEM_USER_CONNECT_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(user_conn, "User connection state", CALL_MODEM_USER_CONN )
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)   
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_RESOURCE_IND */

    MSG_BEGIN(CALL_MODEM_RESOURCE_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)

        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N, 
            ISIHDR_DONT_GENERATE)

            /* Resource */
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE)
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE_SEQ_ID)
            SB_LST_ENTRY(CALL_MODEM_SB_REQ_INFO)

            /* BC related */
            SB_LST_ENTRY(CALL_MODEM_SB_MODE) 
            SB_LST_ENTRY(CALL_MODEM_SB_BC)

            /* Destination address */
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_PRE_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_POST_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_CS_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_ISI_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_SUBADDRESS)

            /* Origin address */
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_CS_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_SUBADDRESS)

            /* Redirecting address */
            SB_LST_ENTRY(CALL_MODEM_SB_REDIRECTING_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_REDIRECTING_SUBADDRESS)

            /* Presentation related */
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE_OF_NO_CLI)
            SB_LST_ENTRY(CALL_MODEM_SB_ALERTING_PATTERN)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_INFO)

            /* Misc */
            SB_LST_ENTRY(CALL_MODEM_SB_USER_TO_USER)
            SB_LST_ENTRY(CALL_MODEM_SB_EMERG_NUMBER_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_CHECK_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_LINE_ID)

        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_RESOURCE_REQ */

    MSG_BEGIN(CALL_MODEM_RESOURCE_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)

        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 3)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)

            /* Resource */
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE)
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE_SEQ_ID)
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE_STATUS)

            /* BC related */
            SB_LST_ENTRY(CALL_MODEM_SB_MODE) 
            SB_LST_ENTRY(CALL_MODEM_SB_BC)

            /* Destination address */
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_PRE_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_POST_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_CS_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_ISI_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DESTINATION_SUBADDRESS)

            /* Origin address */
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_CS_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_SUBADDRESS)

            /* Redirecting address */
            SB_LST_ENTRY(CALL_MODEM_SB_REDIRECTING_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_REDIRECTING_SUBADDRESS)

            /* Presentation related */
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE_OF_NO_CLI)
            SB_LST_ENTRY(CALL_MODEM_SB_ALERTING_PATTERN)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_INFO)

            /* Misc */
            SB_LST_ENTRY(CALL_MODEM_SB_USER_TO_USER)
            SB_LST_ENTRY(CALL_MODEM_SB_EMERG_NUMBER_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_CHECK_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_LINE_ID)

            /* Cause */
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
            SB_LST_ENTRY(CALL_MODEM_SB_DETAILED_CAUSE)

        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_RESOURCE_RESP */

    MSG_BEGIN(CALL_MODEM_RESOURCE_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE_SEQ_ID)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_RESOURCE_REQ, CALL_MODEM_RESOURCE_RESP)

    /* CALL_MODEM_RESOURCE_CLEAR_IND */

    MSG_BEGIN(CALL_MODEM_RESOURCE_CLEAR_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N, 
            ISIHDR_DONT_GENERATE)

            /* Resource */
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE)
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE_SEQ_ID)

        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_RESOURCE_CONF_IND */

    MSG_BEGIN(CALL_MODEM_RESOURCE_CONF_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(conf_status, "Conf status", CALL_MODEM_RES_CONF_STATUS)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N, 
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE)
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE_CONF_REQUIRED)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_RESOURCE_CONF_REQ */

    MSG_BEGIN(CALL_MODEM_RESOURCE_CONF_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(conf_operation, "Conf operation",
            CALL_MODEM_RES_CONF_OPERATION_REQUEST)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE_CONF)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_RESOURCE_CONF_RESP */

    MSG_BEGIN(CALL_MODEM_RESOURCE_CONF_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(conf_operation, "Conf operation",
            CALL_MODEM_RES_CONF_OPERATION)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_RESOURCE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_RESOURCE_CONF_REQ, CALL_MODEM_RESOURCE_CONF_RESP)

    /* CALL_MODEM_TERMINATE_REQ */

    MSG_BEGIN(CALL_MODEM_TERMINATE_REQ, MESSAGE_REQ, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_TERMINATE_RESP */

    MSG_BEGIN(CALL_MODEM_TERMINATE_RESP, MESSAGE_RESP, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_TERMINATE_REQ, CALL_MODEM_TERMINATE_RESP)

    /* CALL_MODEM_NETWORK_CONN_IND */

    MSG_BEGIN(CALL_MODEM_NETWORK_CONN_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N, 
            ISIHDR_DONT_GENERATE)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_MESSAGE_IND */

    MSG_BEGIN(CALL_MODEM_MESSAGE_IND, MESSAGE_IND, "", "")
        CALL_MODEM_COMMON_MSG_HDR
        VALUE_CONST(call_id, "Call ID", CALL_MODEM_ID)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N, 
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_MSG_INFO)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_CS_ADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_ORIGIN_SUBADDRESS)
            SB_LST_ENTRY(CALL_MODEM_SB_DETAILED_CAUSE)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_VCC_STATUS_IND */

    MSG_BEGIN(CALL_MODEM_VCC_STATUS_IND, MESSAGE_IND, "030.000", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
    MSG_END

    /* CALL_MODEM_VCC_STATUS_REQ */

    MSG_BEGIN(CALL_MODEM_VCC_STATUS_REQ, MESSAGE_REQ, "030.000", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_VCC_STATUS_INFO)
        SB_LST_REF_END
    MSG_END

    /* CALL_MODEM_VCC_STATUS_RESP */

    MSG_BEGIN(CALL_MODEM_VCC_STATUS_RESP, MESSAGE_RESP, "030.000", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_CAUSE)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(CALL_MODEM_VCC_STATUS_REQ, CALL_MODEM_VCC_STATUS_RESP)

    /* CALL_MODEM_VCC_STATUS_CLEAR_IND */

    MSG_BEGIN(CALL_MODEM_VCC_STATUS_CLEAR_IND, MESSAGE_IND, "030.000", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
    MSG_END

    /* CALL_MODEM_COMB_STATUS_IND */

    MSG_BEGIN(CALL_MODEM_COMB_STATUS_IND, MESSAGE_IND, "030.000", "")
        CALL_MODEM_COMMON_MSG_HDR
        FILLER_EX(unused, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, sub_blocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, u, "Sub blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(CALL_MODEM_SB_STATUS_INFO)
        SB_LST_REF_END
    MSG_END

/*  5   REFERENCES  */

    COMMENT(COMMENT_PARAGRAPH, "ISI Modem Call Server Feature Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_call_modem_f.doc")
    NOTE("/1/")

    COMMENT(COMMENT_PARAGRAPH, "ISI General Information")
    COMMENT(COMMENT_PARAGRAPH, "Document code: DSY02801-EN")
    COMMENT(COMMENT_PARAGRAPH, "DocMan location: eslns42/SRV/Nokia")
    COMMENT(COMMENT_PARAGRAPH, "DocMan: PP DocMan")
    COMMENT(COMMENT_PARAGRAPH, "Filename: TP\\PP\\ppmgmtdm.nsf")
    COMMENT(COMMENT_PARAGRAPH, "http://www7.connecting.nokia.com/tp/pp/ppmgmtdm.nsf/WebAllByID2/DSY02801-EN")
    NOTE("/2/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Server Specification Documentation Guidelines")
    COMMENT(COMMENT_PARAGRAPH, "Document code: DSY02803-EN")
    COMMENT(COMMENT_PARAGRAPH, "DocMan location: eslns42/SRV/Nokia")
    COMMENT(COMMENT_PARAGRAPH, "DocMan: PP DocMan")
    COMMENT(COMMENT_PARAGRAPH, "Filename: TP\\PP\\ppmgmtdm.nsf")
    COMMENT(COMMENT_PARAGRAPH, "http://www7.connecting.nokia.com/tp/pp/ppmgmtdm.nsf/WebAllByID2/DSY02803-EN")
    NOTE("/3/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Common Features Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_comm_f.doc")
    NOTE("/4/")


/*  6   DATA TYPES */

/*  7   CLASSES */

/*  8   OBJECTS */

/*  9   DATA STRUCTURES */

/*  10   FUNCTION PROTOTYPES */

RES_END

/* End of file call_isi_m.h */

