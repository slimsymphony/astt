/*
NOKIA
[Oulu]
[S40/S30 Asset]



            sm_router_isi_m.h
            -------------------
            SW include - ANSI C



Continuus Ref:
--------------
Project:          S40_ISI

%name:            sm_router_isi_m.h %
%version:         be1iam#002.005 %
%cvtype:          incl %
%instance:        ou1iam_1 %

Document code:    -

Copyright(c) Nokia Corporation. All rights reserved.

Change History:

VERSION     : 002.003       Approved  12-Mar-2010 Daniel Osman
REASON      : Proposal based upon the PCP error: TZ09102141632
REFERENCE   : Inspection reference ActionDB for SWAM Inspection ID: DO09120241812, Task sd1iam3#28406 for 9.2.
DESCRIPTION : add new registration type:  SM_ROUTER_REG_TYPE_LOGICAL_AND added to register for SMs that
match exactly 2 conditions (USER DATA and ORIG ADDRESS). 

VERSION     : 002.004       Approved  23-Mar-2010 Daniel Osman
REASON      : Proposal based upon the PCP error: TZ09102141632
REFERENCE   : Inspection reference ActionDB for SWAM Inspection ID: DO09120241812, Task sd1iam3#28276 for MCL.
DESCRIPTION : Add new registration type:  SM_ROUTER_REG_TYPE_LOGICAL_AND added to register for SMs that
match exactly 2 conditions (USER DATA and ORIG ADDRESS).

VERSION     : 002.003       Approved   09-Feb-2010     Toni Moilanen
REASON      : REQ:408-5644: DUAL SIM SPRINT 3: SMS receiving: SM router server
REFERENCE   : Inspection reference ActionDB for SWAM Inspection ID: MM09122330689
DESCRIPTION : Shared SBs MULTI_SIM_SHARED_SB_SIM_ID and MULTI_SIM_SHARED_SB_ICC added to sending and receiving.

VERSION     : 002.002       Approved   18-May-2009     Juha Turpeinen
REASON      : Proposal based upon the PCP error: JT09051849899
REFERENCE   : Inspection reference ActionDB for SWAM Inspection ID: JT09052757226
DESCRIPTION : More information added for SM_ROUTER_RESPONSE_TYPE_SYSTEM response statuses.

VERSION     : 002.001       Approved   26-Nov-2008     Tuomo Heikka
REASON      : Corrections after inspection TH08111458789.
REFERENCE   : Inspection reference ActionDB for SWAM Inspection ID:
              TH08111458789.
              Task: ou1iam#134862.
DESCRIPTION : Corrected defects found in inspection.

VERSION     : 002.000       Proposal   03-Nov-2008     Mika Kauppinen
REASON      : Corrections after inspection TH08100929947.
REFERENCE   : Inspection reference ActionDB for SWAM Inspection ID:
              TH08111458789.
DESCRIPTION : Corrected for new inspection. Removed version 000.001 support
              as it was never used and causes warnings with autogen.

VERSION     : 001.000       Proposal   08-Oct-2008     Mika Kauppinen
REASON      : Prepared for inspection
REFERENCE   : Inspection reference ActionDB for SWAM Inspection ID: TH08100929947
DESCRIPTION : The first public version.

VERSION     : 000.001       Draft      27-Aug-2008     Mika Kauppinen
REASON      : Initial draft
REFERENCE   : 
DESCRIPTION : Defines Short Message Router Server ISI messages
*/

/* ------------------------------------------------------------------------- */


/*  1    ABSTRACT

    1.1    Module type

    Message definition file for autogen
   

    1.2    Functional description

    This file is the message definition file for the Short Message Router server, SM_ROUTER from now on.


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

#ifndef _SM_ROUTER_ISI_M_H_
#define _SM_ROUTER_ISI_M_H_

#include "multi_sim_shared_isi_m.h"


/*  3    CONSTANTS */

/* Message ID's */
#define SM_ROUTER_STATUS_REQ                    0x10
#define SM_ROUTER_STATUS_RESP                   0x11
#define SM_ROUTER_STORAGE_STATE_SET_REQ         0x12
#define SM_ROUTER_STORAGE_STATE_SET_RESP        0x13
#define SM_ROUTER_MT_SM_STATUS_IND              0x14
#define SM_ROUTER_MT_SM_REGISTER_REQ            0x15
#define SM_ROUTER_MT_SM_REGISTER_RESP           0x16
#define SM_ROUTER_MT_SM_RECEIVED_NTF            0x17
#define SM_ROUTER_MT_SM_RESPONSE_REQ            0x18
#define SM_ROUTER_MT_SM_RESPONSE_RESP           0x19
#define SM_ROUTER_MO_SM_STATUS_IND              0x1A
#define SM_ROUTER_MO_SM_SEND_REQ                0x1B
#define SM_ROUTER_MO_SM_SEND_RESP               0x1C

/* ------------------------------------------------------------------------- */
/* Following message IDs are reserved for SM Router server internal use only */
/* ------------------------------------------------------------------------- */
#define SM_ROUTER_MT_TRIGGER_NTF                0xE0

/* Sub block ID's */
#define SM_ROUTER_SB_ADDRESS                    0x01
#define SM_ROUTER_SB_APPL_PORT                  0x02
#define SM_ROUTER_SB_USIM_PARAMS_LOCATION       0x03
#define SM_ROUTER_SB_SM_USER_DATA               0x04
#define SM_ROUTER_SB_TEXT_STRING                0x05
#define SM_ROUTER_SB_TPDU                       0x06


/* Other constants */

/*  4    MACROS */

/* TODO: Change the version whenever the interface is changed */
/* default ISI version */

#ifndef SM_ROUTER_ISI_VERSION
#define SM_ROUTER_ISI_VERSION
#define SM_ROUTER_ISI_VERSION_Z      2
#define SM_ROUTER_ISI_VERSION_Y      5
#endif

#define SM_ROUTER_ISI_MIN_VERSION(z,y) \
 ((SM_ROUTER_ISI_VERSION_Z == (z) && SM_ROUTER_ISI_VERSION_Y >= (y)) || \
  (SM_ROUTER_ISI_VERSION_Z > (z)))

/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                 "Devices/R&D/S40 Asset Oulu")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                      "S40 Messaging")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,                "Mika Kauppinen")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,           "CONFIDENTIAL")

/* ISI header properties */
PROPERTY_STRING(PROPERTY_ISIHDR_TITLE,                      "SM Router ISI Definitions")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                   "sm_router_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16,                "")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,       "ou1glint")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,     "global_s40_interface/S40_ISI")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16,  "")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,    "ou1glint#1")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16, "")


/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                        "Short Message Router Message Specification")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                     "i_sm_router_m.html")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,              "-")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB,         "ou1glint")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,       "GIF_SPECS_S40-ou1lint#browse")
PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH,               "S40_ISI")
PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

/* Server description */

    COMMENT(COMMENT_TEXT, "The SM (Short Message) Router server is a public ISA (Intelligent Software Architecture) server, which provides support for clients to send and to receive short messages. The SM Router also acts as a controller for SMS server resource MO SM (short message mobile originated). The resource control functionality is specified in SMS server feature and protocol description. The SM Router sends indication when its own status changes or when status of its services changes ")
    COMMENT(COMMENT_TEXT, "(See reference ")
    COMMENT_LINK(LINK_NOTE, "/8/", "", "")
    COMMENT(COMMENT_PARAGRAPH, ").")


RES_BEGIN(RESOURCE_ISI_PREFIX, PN_SM_ROUTER_EXTENDED, sm_router, "SM Router Server", 
    RES_VERSION_STRING(SM_ROUTER_ISI_VERSION_Z, SM_ROUTER_ISI_VERSION_Y), TRUE)
    PROPERTY_STRING(COMMENT_CHANGE_REASON,    "Proposal based upon the PCP error: TZ09102141632")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM Inspection ID: DO09120241812")
    /* state DRAFT, NON-DRAFT, PROPOSAL or PROPOSAL */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "09-Mar-2010")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Daniel Osman")
    COMMENT(COMMENT_TEXT, "Add new registration type: SM_ROUTER_REG_TYPE_LOGICAL_AND.")
    COMMENT(COMMENT_TEXT, "For SMs that match conditional-AND of USER DATA and ORIGINATING ADDRESS subblocks.")
    ISI_VERSION_HISTORY("002.003")
    
    /* Multi Sim shared sub blocks  */
    INCLUDE_SHARED_FILE(PN_MULTI_SIM, "002.003", "")

    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(COMMENT_CHANGE_REASON,    "Proposal based upon PCP error: TZ09102141632")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM Inspection ID: DO09120241812")
    /* state DRAFT, NON-DRAFT, PROPOSAL or PROPOSAL */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "23-Mar-2010")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Daniel Osman")
    COMMENT(COMMENT_TEXT, "Add new registration type: SM_ROUTER_REG_TYPE_LOGICAL_AND")
    COMMENT(COMMENT_TEXT, "For SMs that match conditional logical-and of user data and originating address subblocks.")
    ISI_VERSION_HISTORY("002.004")

    PROPERTY_STRING(COMMENT_CHANGE_REASON,    "REQ:408-5644: DUAL SIM SPRINT 7: SMS receiving: SM router server")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Inspection reference ActionDB for SWAM Inspection ID: MM09122330689")
    /* state DRAFT, NON-DRAFT, PROPOSAL or PROPOSAL */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "09-Feb-2010")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Toni Moilanen")
    COMMENT(COMMENT_TEXT, "Shared SBs MULTI_SIM_SHARED_SB_SIM_ID and MULTI_SIM_ SHARED_SB_ICC added to sending and receiving.")
    ISI_VERSION_HISTORY("002.003")

    PROPERTY_STRING(COMMENT_CHANGE_REASON,    "Proposal based upon the PCP error: JT09051849899")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM Inspection ID: JT09052757226")
    /* state DRAFT, NON-DRAFT, PROPOSAL or PROPOSAL */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "18-May-2009")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Juha Turpeinen")
    COMMENT(COMMENT_TEXT, "More information added for SM_ROUTER_RESPONSE_TYPE_SYSTEM response statuses.")
    ISI_VERSION_HISTORY("002.002")

    PROPERTY_STRING(COMMENT_CHANGE_REASON,    "Corrected after inspection.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM Inspection ID: TH08111458789 SM Router ISI v. 002.000 inspection.")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "26-Nov-2008")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Tuomo Heikka")
    COMMENT(COMMENT_TEXT, "Dropped support of previous versions as they were ")
    COMMENT(COMMENT_TEXT, "not approved. Renamed parameter mt_router_status ")
    COMMENT(COMMENT_TEXT, "to mt_service_status in SM_ROUTER_MT_SM_REGISTER_RESP_STR. ")
    COMMENT(COMMENT_TEXT, "Corrected sub block name in description field of SM_ROUTER_MO_SM_SEND_REQ. ")
    ISI_VERSION_HISTORY("002.001")

    PROPERTY_STRING(COMMENT_CHANGE_REASON,    "Corrected after inspection. ID: TH08100929947.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM Inspection ID: TH08111458789 SM Router ISI v. 002.000 inspection.")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "PROPOSAL")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "13-Nov-2008")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Mika Kauppinen")
    PROPERTY(PROPERTY_VERSION_NO_LONGER_SUPPORTED)
    ISI_VERSION_HISTORY("002.000")

    PROPERTY_STRING(COMMENT_CHANGE_REASON,    "First official version for inspection")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ: 414-3471: Chipset API: SMS server changes")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "PROPOSAL")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "08-Oct-2008")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Mika Kauppinen")
    COMMENT(COMMENT_TEXT, "Defines SM Router Server ISI interface")
    PROPERTY(PROPERTY_VERSION_NO_LONGER_SUPPORTED)
    ISI_VERSION_HISTORY("001.000")

    COMMENT(COMMENT_PARAGRAPH, "autogen documentation")
    COMMENT(COMMENT_PARAGRAPH, "Intranet")
    COMMENT(COMMENT_PARAGRAPH, "http://rdsuite.europe.nokia.com/products/autogen/documentation.asp")
    COMMENT(COMMENT_PARAGRAPH, "Link: autogen documentation")
    NOTE("/1/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Server Specification Documentation Guidelines")
    COMMENT(COMMENT_PARAGRAPH, "Document code: XXXL7714-EN")
    COMMENT(COMMENT_PARAGRAPH, "DocMan location: eslns42/SRV/Nokia")
    COMMENT(COMMENT_PARAGRAPH, "DocMan: TP / WP Front End DocMan")
    COMMENT(COMMENT_PARAGRAPH, "Filename: TP/WP/tpwpfendm.nsf")
    NOTE("/2/")

    COMMENT(COMMENT_PARAGRAPH, "ISI General Information")
    COMMENT(COMMENT_PARAGRAPH, "Document code: XXXL7715-EN")
    COMMENT(COMMENT_PARAGRAPH, "DocMan location: eslns42/SRV/Nokia")
    COMMENT(COMMENT_PARAGRAPH, "DocMan: TP / WP Front End DocMan")
    COMMENT(COMMENT_PARAGRAPH, "Filename: TP/WP/tpwpfendm.nsf")
    NOTE("/3/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Common Message Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Database: ou1gif")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Project: GIF_SPECS-ou1gif#browse")
    COMMENT(COMMENT_PARAGRAPH, "Directory Path: GIF_SPECS/CoreSW")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_comm_m.html")
    NOTE("/4/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Common Feature Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Database: ou1gif")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Project: GIF_SPECS-ou1gif#browse")
    COMMENT(COMMENT_PARAGRAPH, "Directory Path: GIF_SPECS/CoreSW")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_comm_fp.doc")
    NOTE("/5/")
    
    COMMENT(COMMENT_PARAGRAPH, "SM Router Server Message Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Database: ou1gif")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Project: GIF_SPECS_S40-browse:project:ou1glint#1")
    COMMENT(COMMENT_PARAGRAPH, "Directory Path: GIF_SPECS_S40/S40_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename:  i_sm_router_m.html")
    NOTE("/6/")

   COMMENT(COMMENT_PARAGRAPH, "ISI SM Router Server Feature and Protocol Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Database: ou1gif")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Project: GIF_SPECS_S40-browse:project:ou1glint#1")
    COMMENT(COMMENT_PARAGRAPH, "Directory Path: GIF_SPECS_S40/S40_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename: sm_router_fp.doc")
    NOTE("/7/")

   COMMENT(COMMENT_PARAGRAPH, "ISI SMS Server Feature and Protocol")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Database: ou1gif")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Project: GIF_SPECS_S40-browse:project:ou1glint#1")
    COMMENT(COMMENT_PARAGRAPH, "Directory Path: GIF_SPECS_S40/S40_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_sms_wm_fp.doc")
    NOTE("/8/")

    COMMENT(COMMENT_PARAGRAPH, "3GPP TS 23.038")
    COMMENT(COMMENT_PARAGRAPH, "Alphabets and language-specific information")
    NOTE("/9/")

    COMMENT(COMMENT_PARAGRAPH, "3GPP TS 23.040")
    COMMENT(COMMENT_PARAGRAPH, "Technical realization of the Short Message "
        "Service (SMS)")
    NOTE("/10/")

    COMMENT(COMMENT_PARAGRAPH, "3GPP TS 24.011")
    COMMENT(COMMENT_PARAGRAPH, "Point-to-Point (PP) Short Message Service (SMS) "
    "support on mobile radio interface")
    NOTE("/11/")

    /* --------------------------------------------------------------------- */
    /* Symbol tables */
    /* --------------------------------------------------------------------- */

    COMMENT(COMMENT_TEXT, "Type of short messages that the client requests to receive.")
    CONST_TBL_BEGIN(SM_ROUTER_MESSAGE_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_SM_TYPE_DELIVER,          0x00, "SMS-DELIVER type.")
        CONST_TBL_ENTRY(SM_ROUTER_SM_TYPE_STATUS_REPORT,    0x01, "SMS-STATUS-REPORT type.")
        CONST_TBL_ENTRY(SM_ROUTER_SM_TYPE_MT_ALL,           0x02, "SMS-MT-ALL type.")
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "SM Router action.")
    CONST_TBL_BEGIN(SM_ROUTER_ACTION, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_ACTION_REGISTER,          0x00, "Register to service.")
        CONST_TBL_ENTRY(SM_ROUTER_ACTION_DEREGISTER,        0x01, "Deregister from service.")
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "Statuses of the SM Router Server and services.")
    CONST_TBL_BEGIN(SM_ROUTER_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_STATUS_NOT_READY,         0x01, "Server is performing startup.")
        CONST_TBL_ENTRY(SM_ROUTER_STATUS_READY,             0x02, "Server status is running.")
        CONST_TBL_ENTRY(SM_ROUTER_STATUS_MO_SM_NOT_READY,   0x03, "MO Service is not ready.")
        CONST_TBL_ENTRY(SM_ROUTER_STATUS_MO_SM_IDLE,        0x04, "MO Service is idle.")
        CONST_TBL_ENTRY(SM_ROUTER_STATUS_MO_SM_BUSY,        0x05, "MO Service is busy.")
        CONST_TBL_ENTRY(SM_ROUTER_STATUS_MT_SM_NOT_READY,   0x06, "MT Service is not ready.")
        CONST_TBL_ENTRY(SM_ROUTER_STATUS_MT_SM_ACTIVE,      0x07, "MT Service is active.")
        CONST_TBL_ENTRY(SM_ROUTER_STATUS_MT_SM_INACTIVE,    0x08, "MT Service is inactive.")
    CONST_TBL_END

    COMMENT(COMMENT_TEXT, "SM route that defines bearer over which the MO SM is sent.")
    CONST_TBL_BEGIN(SM_ROUTER_BEARER_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_BEARER_TYPE_DEFAULT,      0x00, "Bearers according to user selection.")
        CONST_TBL_ENTRY(SM_ROUTER_BEARER_TYPE_CS_ONLY,      0x01, "Only CS bearer is used.")
        CONST_TBL_ENTRY(SM_ROUTER_BEARER_TYPE_PS_ONLY,      0x02, "Only PS bearer is used.")
    CONST_TBL_END

    COMMENT(COMMENT_TEXT, "Defines the specific content in short messages that the client requests to receive in priority order")
    CONST_TBL_BEGIN(SM_ROUTER_REGISTRATION_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_USIM_DDL,        0x01, "Class 2 and (U)SIM data download")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_KODIAK_SMS,      0x02, "Kodiak spesific SM")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_ORIG_ADDRESS,    0x03, "Originating address (Sender phone number)")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_APPL_PORT,       0x04, "Application port as SM destination")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_USER_DATA,       0x05, "Spesific user data content")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_MWI,             0x06, "Message Waiting Indication SM")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_APPL_PORT_ALL,   0x07, "Misc application port SMs")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_CLASS_0,         0x08, "Immediate display (Flash message)")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_CLASS_1,         0x09, "ME (Mobile Equipment) specific")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_CLASS_2,         0x0A, "(U)SIM specific")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_CLASS_3,         0x0B, "TE (Terminal equipment) specific")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_TEXT_MESSAGES,   0x0C, "Basic SMs for default handler")
        CONST_TBL_ENTRY(SM_ROUTER_REG_TYPE_LOGICAL_AND,     0x0D, "SM meets conditional-logical-AND of originating address and user data content")
    CONST_TBL_END

    COMMENT(COMMENT_TEXT, "Defines which of the response type tables is being used.")
    CONST_TBL_BEGIN(SM_ROUTER_RESPONSE_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_RESPONSE_TYPE_INTERNAL,   0x00, "OK response or not SM transfer related fail response.")
        CONST_TBL_ENTRY(SM_ROUTER_RESPONSE_TYPE_SYSTEM,     0x01, "SM protocol or associated protocols specific fail response.")
    CONST_TBL_END

    /* ----------------------------------------------------------------------- */
    /* Constant Table: SM_ROUTER_RESPONSE_TYPE_INTERNAL */
    /* ----------------------------------------------------------------------- */
    COMMENT(COMMENT_TEXT, "If response type is not used or if response type is ")
    COMMENT(COMMENT_TEXT, "SM_ROUTER_RESPONSE_TYPE_INTERNAL then following cause values shall be used:")
    CONST_TBL_BEGIN(SM_ROUTER_RESPONSE_TYPE_INTERNAL, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_OK,                                   0x01,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_NOT_READY,                        0x02,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_MO_SM_BUSY,                       0x03,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_REQUEST,                  0x04,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_DEVICE_FAILURE,                   0x05,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_BEARER_NOT_AVAILABLE,             0x06,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_BEARER_NOT_ALLOWED,               0x07,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_NO_SYSTEM_RESPONSE,               0x08,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_DEST_ADDRESS_FDN_RESTRICTED,      0x09,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_SMSC_ADDRESS_FDN_RESTRICTED,      0x0A,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_BEARERS_INACTIVE,                 0x0B,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_MO_SM_CONTROL_REJECTED,           0x0C,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_PREPAID_REJECTED,                 0x0D,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_MT_SM_RESERVED,                   0x0E,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_MESSAGE_REJECTED,                 0x0F,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_REFERENCE_ID,             0x10,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_FAILED_RESPONSE_ALREADY_SENT,     0x11,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_REGISTRATION_TYPE_MISMATCH,       0x12,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_REGISTRATION_NOT_FOUND,           0x13,  "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_SMSC_ADDR_NOT_AVAILABLE,          0x14,  "")
    CONST_TBL_END


    /* ----------------------------------------------------------------------- */
    /* Constant Table: SM_ROUTER_RESPONSE_TYPE_SYSTEM */
    /* ----------------------------------------------------------------------- */
    COMMENT(COMMENT_TEXT, "If response type is SM_ROUTER_RESPONSE_TYPE_SYSTEM then following response values shall be used. ")
    COMMENT(COMMENT_TEXT, "NOTE: Direction field defines whether the response can be used in accordance ")
    COMMENT(COMMENT_TEXT, "with mobile originating messages or mobile terminating messages (see comment field for MO/MT direction information for the related response). ")
    COMMENT(COMMENT_TEXT, "NOTE 2: The response status can be handled as either temporary or permanent fail status depending on the clients possibility to handle such cases (see comment field for Temporary/Permanent status information for the related response). ")
    CONST_TBL_BEGIN(SM_ROUTER_RESPONSE_TYPE_SYSTEM, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_UNASSIGNED_NUMBER,                        0x01, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_OPER_DETERMINED_BARRED,                   0x08, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_CALL_BARRED,                              0x0A, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_RESERVED,                                 0x0B, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_MSG_TRANSFER_REJECTED,                    0x15, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_MEMORY_CAPACITY_EXCEEDED,                 0x16, "Direction: MT. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_DEST_OUT_OF_ORDER,                        0x1B, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_UNDEFINED_SUBSCRIBER,                     0x1C, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_FACILITY_REJECTED,                        0x1D, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_UNKNOWN_SUBSCRIBER,                       0x1E, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_NETW_OUT_OF_ORDER,                        0x26, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_TEMPORARY_FAILURE,                        0x29, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_CONGESTION,                               0x2A, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_RESOURCE_UNAVAILABLE,                     0x2F, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_REQ_FACILITY_NOT_SUBSCRIBED,              0x32, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_REQ_FACILITY_NOT_IMPLEMENTED,             0x45, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_REFERENCE,                        0x51, "Direction: MO/MT. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_INCORRECT_MESSAGE,                        0x5F, "Direction: MO/MT. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_MAND_INFO,                        0x60, "Direction: MO/MT. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_MSG_TYPE,                         0x61, "Direction: MO/MT. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_MSG_NOT_COMP_WITH_STATE,                  0x62, "Direction: MO/MT. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_INFO_ELEMENT,                     0x63, "Direction: MO/MT. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_PROTOCOL_ERROR,                           0x6F, "Direction: MO/MT. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_INTERWORKING,                             0x7F, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_NO_CAUSE,                                 0x80, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_IMSI_UNKNOWN_HLR,                         0x82, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_ILLEGAL_MS,                               0x83, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_IMSI_UNKNOWN_VLR,                         0x84, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_IMEI_NOT_ACCEPTED,                        0x85, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_ILLEGAL_ME,                               0x86, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_PLMN_NOT_ALLOWED,                         0x8B, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_LA_NOT_ALLOWED,                           0x8C, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_ROAM_NOT_ALLOWED_LA,                      0x8D, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_NO_SUITABLE_CELLS_LA,                     0x8F, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_NETWORK_FAILURE,                          0x91, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_MAC_FAILURE,                              0x94, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_SYNC_FAILURE,                             0x95, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_LOW_LAYER_CONGESTION,                     0x96, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_AUTH_UNACCEPTABLE,                        0x97, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_SERV_OPT_NOT_SUPPORTED,                   0xA0, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_SERV_OPT_NOT_SUBSCRIBED,                  0xA1, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_SERV_OPT_TEMP_OUT_OF_ORDER,               0xA2, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_CALL_CANNOT_BE_IDENTIFIED,                0xA6, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_SEMANTICALLY_INCORR_MSG,                  0xDF, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_LOW_LAYER_INVALID_MAND_INFO,              0xE0, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_LOW_LAYER_INVALID_MSG_TYPE,               0xE1, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_LOW_LAYER_MSG_TYPE_NOT_COMP_WITH_STATE,   0xE2, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_LOW_LAYER_INVALID_INFO_ELEMENT,           0xE3, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_CONDITIONAL_IE_ERROR,                     0xE4, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_LOW_LAYER_MSG_NOT_COMP_WITH_STATE,        0xE5, "Direction: MO. Preferred to be handled as a Temporary fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_CS_BARRED,                                0xE8, "Direction: MO. Preferred to be handled as a Permanent fail status")
        CONST_TBL_ENTRY(SM_ROUTER_ERR_LOW_LAYER_PROTOCOL_ERROR,                 0xEF, "Direction: MO. Preferred to be handled as a Temporary fail status")
    CONST_TBL_END

    COMMENT(COMMENT_TEXT, "Defines the payload or purpose of the short message")
    CONST_TBL_BEGIN(SM_ROUTER_CONTENT_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_CONTENT_TYPE_TEXT_MESSAGE,            0x00, "") 
        CONST_TBL_ENTRY(SM_ROUTER_CONTENT_TYPE_NOKIA_SMART_MESSAGE,     0x01, "")
        CONST_TBL_ENTRY(SM_ROUTER_CONTENT_TYPE_JAVA_MIDLET_SMS,         0x02, "")
        CONST_TBL_ENTRY(SM_ROUTER_CONTENT_TYPE_BREW_SMS,                0x03, "")
        CONST_TBL_ENTRY(SM_ROUTER_CONTENT_TYPE_GPS_SMS,                 0x04, "")
        CONST_TBL_ENTRY(SM_ROUTER_CONTENT_TYPE_PUSH_TO_TALK_SMS,        0x05, "")
        CONST_TBL_ENTRY(SM_ROUTER_CONTENT_TYPE_SIM_ATK_SMS,             0x06, "")
        CONST_TBL_ENTRY(SM_ROUTER_CONTENT_TYPE_TRACFONE_PREPAID_SMS,    0x07, "")
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "MO SM Control result: defines the result of ATK MO SM Control check")
    CONST_TBL_BEGIN(SM_ROUTER_MO_SM_CONTROL_RESULT, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_MO_SM_CTRL_NOT_DONE,      0x00, "Message check not done.")
        CONST_TBL_ENTRY(SM_ROUTER_MO_SM_CTRL_ALLOWED,       0x01, "Sending allowed, addresses unchanged.")
        CONST_TBL_ENTRY(SM_ROUTER_MO_SM_CTRL_MODIFIED,      0x02, "Sending allowed, address(es) changed.")
        CONST_TBL_ENTRY(SM_ROUTER_MO_SM_CTRL_NOT_ALLOWED,   0x03, "Sending not allowed.")
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "SM Router Address types")
    CONST_TBL_BEGIN(SM_ROUTER_ADDRESS_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_ADDRESS_TYPE_UNICODE,     0x01, "16-bit zero terminated")
        CONST_TBL_ENTRY(SM_ROUTER_ADDRESS_TYPE_SMSC,        0x02, "3GPP service center address TS 24.011 /11/")
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "SMS (U)SIM parameters indicators. Defines which of the SMS parameters shall be read and used.")
    BIT_TBL_BEGIN(SM_ROUTER_PARAMETER_INDICATOR, 8, BE, "", "")
      BIT_TBL_ENTRY("XXXXXXX1", SM_ROUTER_PI_DESTINATION_ADDRESS,       "")
      BIT_TBL_ENTRY("XXXXXX1X", SM_ROUTER_PI_SERVICE_CENTRE_ADDRESS,    "")
      BIT_TBL_ENTRY("XXXXX1XX", SM_ROUTER_PI_PROTOCOL_ID,               "")
      BIT_TBL_ENTRY("XXXX1XXX", SM_ROUTER_PI_DATA_CODING_SCHEME,        "")
      BIT_TBL_ENTRY("XXX1XXXX", SM_ROUTER_PI_VALIDITY_PERIOD,           "")
    BIT_TBL_END


    COMMENT(COMMENT_TEXT, "SM Router data types. Defines the format of data in data bytes field.")
    CONST_TBL_BEGIN(SM_ROUTER_DATA_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_SM_DATA_TYPE_3GPP7BIT,    0x01, "7-bit encoding 3GPP TS 23.038 /9/")
        CONST_TBL_ENTRY(SM_ROUTER_SM_DATA_TYPE_8BIT,        0x02, "8-bit encoding (ASCII, Binary)")
        CONST_TBL_ENTRY(SM_ROUTER_SM_DATA_TYPE_UNICODE,     0x03, "16-bit zero terminated")
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "SM Router message storage states.")
    CONST_TBL_BEGIN(SM_ROUTER_MESSAGE_STORAGE_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_MESSAGE_STORAGE_STATE_UNKNOWN,    0x01, "Message storage state not initialized")
        CONST_TBL_ENTRY(SM_ROUTER_MESSAGE_STORAGE_STATE_NOT_FULL,   0x02, "Message storage not in full state")
        CONST_TBL_ENTRY(SM_ROUTER_MESSAGE_STORAGE_STATE_FULL,       0x03, "Message storage in full state")
    CONST_TBL_END


    COMMENT(COMMENT_TEXT, "SM Router MO SM originator types. Defines source of the SM.")
        CONST_TBL_BEGIN(SM_ROUTER_ORIGINATOR_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(SM_ROUTER_ORIGINATOR_DEFAULT,   0x00, "Originator different than USIM")
        CONST_TBL_ENTRY(SM_ROUTER_ORIGINATOR_USIM,      0x01, "Originator USIM")
    CONST_TBL_END


/*--------------------------------------------------------------------------*/
/* Sub constant tables for Router service statuses                          */
/*--------------------------------------------------------------------------*/

    DER_CONST_TBL_BEGIN(SM_ROUTER_MO_SERVICE_STATUS, SM_ROUTER_STATUS, "", "")
        DER_CONST_TBL_ENTRY(SM_ROUTER_STATUS_MO_SM_NOT_READY)
        DER_CONST_TBL_ENTRY(SM_ROUTER_STATUS_MO_SM_IDLE)
        DER_CONST_TBL_ENTRY(SM_ROUTER_STATUS_MO_SM_BUSY)
    DER_CONST_TBL_END

/*--------------------------------------------------------------------------*/

    DER_CONST_TBL_BEGIN(SM_ROUTER_MT_SERVICE_STATUS, SM_ROUTER_STATUS, "", "")
        DER_CONST_TBL_ENTRY(SM_ROUTER_STATUS_MT_SM_NOT_READY)
        DER_CONST_TBL_ENTRY(SM_ROUTER_STATUS_MT_SM_ACTIVE)
        DER_CONST_TBL_ENTRY(SM_ROUTER_STATUS_MT_SM_INACTIVE)
    DER_CONST_TBL_END

/*--------------------------------------------------------------------------*/

    DER_CONST_TBL_BEGIN(SM_ROUTER_GENERAL_STATUS, SM_ROUTER_STATUS, "", "")
        DER_CONST_TBL_ENTRY(SM_ROUTER_STATUS_NOT_READY)
        DER_CONST_TBL_ENTRY(SM_ROUTER_STATUS_READY)
    DER_CONST_TBL_END


/*--------------------------------------------------------------------------*/

    DER_CONST_TBL_BEGIN(SM_ROUTER_STORAGE_STATE_ACTION, SM_ROUTER_MESSAGE_STORAGE_STATE, "", "")
        DER_CONST_TBL_ENTRY(SM_ROUTER_MESSAGE_STORAGE_STATE_NOT_FULL)
    DER_CONST_TBL_END

/*--------------------------------------------------------------------------*/

    DER_CONST_TBL_BEGIN(SM_ROUTER_RESPONSE_OK, SM_ROUTER_RESPONSE_TYPE_INTERNAL, "", "")
        DER_CONST_TBL_ENTRY(SM_ROUTER_OK)
    DER_CONST_TBL_END

/*--------------------------------------------------------------------------*/

    DER_CONST_TBL_BEGIN(SM_ROUTER_RESPONSE_STORAGE_STATE_SET, SM_ROUTER_RESPONSE_TYPE_INTERNAL, "", "")
        DER_CONST_TBL_ENTRY(SM_ROUTER_OK)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_NOT_READY)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_REQUEST)
    DER_CONST_TBL_END

/*--------------------------------------------------------------------------*/

    DER_CONST_TBL_BEGIN(SM_ROUTER_RESPONSE_REGISTER, SM_ROUTER_RESPONSE_TYPE_INTERNAL, "", "")
        DER_CONST_TBL_ENTRY(SM_ROUTER_OK)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_NOT_READY)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_REQUEST)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_MT_SM_RESERVED)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_REGISTRATION_TYPE_MISMATCH)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_REGISTRATION_NOT_FOUND)
    DER_CONST_TBL_END

/*--------------------------------------------------------------------------*/

    DER_CONST_TBL_BEGIN(SM_ROUTER_RESPONSE_RESPONSE, SM_ROUTER_RESPONSE_TYPE_INTERNAL, "", "")
        DER_CONST_TBL_ENTRY(SM_ROUTER_OK)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_NOT_READY)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_REQUEST)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_FAILED_RESPONSE_ALREADY_SENT)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_REFERENCE_ID)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_NO_SYSTEM_RESPONSE)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_BEARERS_INACTIVE)
    DER_CONST_TBL_END

/*--------------------------------------------------------------------------*/

    DER_CONST_TBL_BEGIN(SM_ROUTER_REQUEST_RESPONSE_INTERNAL, SM_ROUTER_RESPONSE_TYPE_INTERNAL, "", "")
        DER_CONST_TBL_ENTRY(SM_ROUTER_OK)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_MESSAGE_REJECTED)
    DER_CONST_TBL_END

/*--------------------------------------------------------------------------*/

    DER_CONST_TBL_BEGIN(SM_ROUTER_RESPONSE_SEND_INTERNAL, SM_ROUTER_RESPONSE_TYPE_INTERNAL, "", "")
        DER_CONST_TBL_ENTRY(SM_ROUTER_OK)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_NOT_READY)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_MO_SM_BUSY)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_REQUEST)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_DEVICE_FAILURE)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_BEARER_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_BEARER_NOT_ALLOWED)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_NO_SYSTEM_RESPONSE)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_DEST_ADDRESS_FDN_RESTRICTED)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_SMSC_ADDRESS_FDN_RESTRICTED)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_BEARERS_INACTIVE)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_MO_SM_CONTROL_REJECTED)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_PREPAID_REJECTED)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_SMSC_ADDR_NOT_AVAILABLE)
    DER_CONST_TBL_END

/*--------------------------------------------------------------------------*/

    DER_CONST_TBL_BEGIN(SM_ROUTER_REQUEST_RESPONSE_SYSTEM, SM_ROUTER_RESPONSE_TYPE_SYSTEM, "", "")
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_MEMORY_CAPACITY_EXCEEDED)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_REFERENCE)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_INCORRECT_MESSAGE)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_MAND_INFO)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_MSG_TYPE)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_MSG_NOT_COMP_WITH_STATE)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_INVALID_INFO_ELEMENT)
        DER_CONST_TBL_ENTRY(SM_ROUTER_ERR_PROTOCOL_ERROR)
    DER_CONST_TBL_END

/*--------------------------------------------------------------------------*/

    COMMENT(COMMENT_TEXT, "SM Router SMS Parameters default location.")
    CONSTANT(SM_ROUTER_PARAMS_LOCATION_DEFAULT, 0)

    COMMENT(COMMENT_TEXT, "SM Router uninitialized registration id.")
    CONSTANT(SM_ROUTER_REGISTRATION_ID_NONE,    0)
   
    /* --------------------------------------------------------------------- */
    /* Sub blocks */
    /* --------------------------------------------------------------------- */
     
    SB_BEGIN(SM_ROUTER_SB_APPL_PORT, "", "")
        COMMON_SB_16_LONG
        COMMENT(COMMENT_TEXT, "Amount of application ports.")
        REFERENCE(8, BE, port_count, "Port count", N)
        FILLER(FILLER_FIXED, 8)
        COMMENT(COMMENT_TEXT, "Port data is formed of an array of uint16 port numbers.")
        SEQ_OF_REF(port_data, "Port data", AUTOGEN_SEQ_WORD_DEC, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    SB_BEGIN(SM_ROUTER_SB_ADDRESS, "", "")
        COMMON_SB_16_LONG
        COMMENT(COMMENT_TEXT, "Defines format of address data.")
        VALUE_CONST(address_type, "Address type", SM_ROUTER_ADDRESS_TYPE)
        REFERENCE(8, BE, address_data_length, "Address data length", N)
        COMMENT(COMMENT_TEXT, "Address data according to address type.")
        SEQ_OF_REF(address_data, "Address data", AUTOGEN_SEQ_BYTE_DEC, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    SB_BEGIN(SM_ROUTER_SB_USIM_PARAMS_LOCATION, "", "")
        COMMON_SB_16_LONG
        COMMENT(COMMENT_TEXT, "SMS parameters location on (U)SIM. From 1 to 255 or SM_ROUTER_PARAMS_LOCATION_DEFAULT.")
        VALUE(8, BE, location_number, "Location number", DEC)
        COMMENT(COMMENT_TEXT, "Bit field that defines which of the SMS parameters shall be read and used.")
        VALUE_CONST(indicator, "Indicator", SM_ROUTER_PARAMETER_INDICATOR)
        FILLER(FILLER_FIXED, 16)
    SB_END

    SB_BEGIN(SM_ROUTER_SB_TEXT_STRING, "", "")
        COMMON_SB_16_LONG
        COMMENT(COMMENT_TEXT, "Data length in UNICODE characters, not counting trailing zero.")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 32761)
        REFERENCE(16, BE, data_length, "Data length", N)
        COMMENT(COMMENT_TEXT, "Zero terminated UNICODE string.")
        REFERENCE_TRANSFORM(N, M, ALG_ADD, 1)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, text, "Text", M, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END    

    SB_BEGIN(SM_ROUTER_SB_SM_USER_DATA, "", "")
        COMMON_SB_16_LONG
        COMMENT(COMMENT_TEXT, "Format of user data field.")
        VALUE_CONST(data_type, "Data type", SM_ROUTER_DATA_TYPE)
        COMMENT(COMMENT_TEXT, "Data length in bytes.")
        REFERENCE(8, BE, data_length, "Data length", N)
        COMMENT(COMMENT_TEXT, "Number of septets if data type is SM_ROUTER_SM_DATA_TYPE_3GPP7BIT. Otherwise ignored.")
        VALUE(8, BE, septet_count, "Septet count", DEC)
        COMMENT(COMMENT_TEXT, "User data according to data type. No zero termination.")
        SEQ_OF_REF(user_data, "User Data", AUTOGEN_SEQ_BYTE_DEC, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    SB_BEGIN(SM_ROUTER_SB_TPDU, "", "")
        COMMON_SB_16_LONG
        COMMENT(COMMENT_TEXT, "TPDU length in bytes.")
        REFERENCE(8, BE, tpdu_length, "TPDU length", N)
        COMMENT(COMMENT_TEXT, "SMS Transfer Protocol Data Unit including SMS user data. See ")
        COMMENT_LINK(LINK_NOTE, "/10/", "", "")
        SEQ_OF_REF(tpdu_data, "TPDU data", AUTOGEN_SEQ_BYTE_DEC, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

/* --------------------------------------------------------------------- */
/* Messages */
/* --------------------------------------------------------------------- */


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_STATUS_REQ                                           */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_STATUS_REQ, MESSAGE_REQ, "", "")
        COMMON_PREFIX_MSG_HDR
    MSG_END


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_STATUS_RESP                                          */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_STATUS_RESP, MESSAGE_RESP, "", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, "Handling of this message cannot fail, status is always SM_ROUTER_OK.")
        VALUE_CONST(response, "Response", SM_ROUTER_RESPONSE_OK)
        COMMENT(COMMENT_TEXT, "General Router Status.")
        VALUE_CONST(router_status, "Router status", SM_ROUTER_GENERAL_STATUS)
        COMMENT(COMMENT_TEXT, "Current MO Service Status.")
        VALUE_CONST(mo_service_status, "MO Service Status", SM_ROUTER_MO_SERVICE_STATUS)
        COMMENT(COMMENT_TEXT, "Current MT Service Status.")
        VALUE_CONST(mt_service_status, "MT Service Status", SM_ROUTER_MT_SERVICE_STATUS)
    MSG_END

    MSG_PAIR(SM_ROUTER_STATUS_REQ, SM_ROUTER_STATUS_RESP)


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_SM_STATUS_IND                                     */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_MT_SM_STATUS_IND, MESSAGE_IND, "", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, "General Router Status always SM_ROUTER_STATUS_READY.")
        VALUE(8, BE, router_status, "Router Status", DEC)
        COMMENT(COMMENT_TEXT, "Current MT Service Status.")
        VALUE_CONST(mt_service_status, "MT Service Status", SM_ROUTER_MT_SERVICE_STATUS)
    MSG_END


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MO_SM_STATUS_IND                                     */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_MO_SM_STATUS_IND, MESSAGE_IND, "", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, "General Router Status always SM_ROUTER_STATUS_READY.")
        VALUE(8, BE, router_status, "Router Status", DEC)
        COMMENT(COMMENT_TEXT, "Current MO Service Status.")
        VALUE_CONST(mo_service_status,"MO Service Status", SM_ROUTER_MO_SERVICE_STATUS)
    MSG_END

/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MO_SM_SEND_REQ                                       */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_MO_SM_SEND_REQ, MESSAGE_REQ, "", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, "Content type of MO SM. Will be used for prepaid checking. Default value: SM_ROUTER_CONTENT_TYPE_TEXT_MESSAGE.")
        VALUE_CONST(content_type, "Content type", SM_ROUTER_CONTENT_TYPE)
        COMMENT(COMMENT_TEXT, "SM route that defines bearer over which the MO SM is sent. Default value: SM_ROUTER_BEARER_TYPE_DEFAULT.")
        VALUE_CONST(bearer_type, "Bearer type", SM_ROUTER_BEARER_TYPE)
        COMMENT(COMMENT_TEXT, "Client has next MO SM waiting for sending after this one.")
        VALUE(8, BE, more_messages, "More Messages", DEC)
        COMMENT(COMMENT_TEXT,"Re-send of previously unsuccessfully sent SM with the same TP-MR as in the failed send case.")
        VALUE(8, BE, repeated_message, "Repeated message", DEC)
        COMMENT(COMMENT_TEXT,"Defines source of the SM. Needed to bypass FDN check for (U)SIM originated SM. Default value: SM_ROUTER_ORIGINATOR_DEFAULT.")
        VALUE_CONST(message_originator, "Message originator", SM_ROUTER_ORIGINATOR_TYPE)
        FILLER(FILLER_FIXED, 16)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 2)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 255)
        REFERENCE (8, BE, sub_block_count, "Number of Sub Blocks", N_SB)
        COMMENT(COMMENT_PARAGRAPH, "Mandatory:")
        COMMENT(COMMENT_PARAGRAPH, "- SMS-Submit or SMS-Command TPDU sub block(s)")
        COMMENT(COMMENT_PARAGRAPH, "[SM_ROUTER_SB_TPDU] (can be many of these)")
        COMMENT(COMMENT_PARAGRAPH, "Conditional:")
        COMMENT(COMMENT_PARAGRAPH, "- SMSC address sub block")
        COMMENT(COMMENT_PARAGRAPH, "[SM_ROUTER_SB_ADDRESS] (SM_ROUTER_ADDRESS_TYPE_SMSC) or")
        COMMENT(COMMENT_PARAGRAPH, "- USIM SMS parameters sub block")
        COMMENT(COMMENT_PARAGRAPH, "[SM_ROUTER_SB_USIM_PARAMS_LOCATION] or")
        COMMENT(COMMENT_PARAGRAPH, "both. Either SMSC address or its location ")
        COMMENT(COMMENT_PARAGRAPH, "information must be included.")
        COMMENT(COMMENT_PARAGRAPH, "Optional:")
        COMMENT(COMMENT_PARAGRAPH, "- Multi SIM information sub block")
        COMMENT(COMMENT_PARAGRAPH, "Either [MULTI_SIM_SHARED_SB_SIM_ID] or ")
        COMMENT(COMMENT_PARAGRAPH, "[MULTI_SIM_SHARED_SB_ICC], not both.")
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Message details", N_SB, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY (SM_ROUTER_SB_TPDU)
            SB_LST_ENTRY (SM_ROUTER_SB_ADDRESS)
            SB_LST_ENTRY (SM_ROUTER_SB_USIM_PARAMS_LOCATION)
            SB_LST_ENTRY (MULTI_SIM_SHARED_SB_SIM_ID)
            SB_LST_ENTRY (MULTI_SIM_SHARED_SB_ICC)
        SB_LST_REF_END
    MSG_END

/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MO_SM_SEND_RESP                                      */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_MO_SM_SEND_RESP, MESSAGE_RESP, "", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, "Either internal or system response type is used.")
        REFERENCE_CONST(response_type, "Response type", RESPONSE_TYPE, SM_ROUTER_RESPONSE_TYPE)
        CHOICE_BEGIN(SM_ROUTER_RESPONSE_TYPE, "Response type", RESPONSE_TYPE)
            CASE_BEGIN(SM_ROUTER_RESPONSE_TYPE_SYSTEM,"002.002","")
            COMMENT(COMMENT_TEXT, "Only MO error values applicable.")
            VALUE_CONST(response, "Response", SM_ROUTER_RESPONSE_TYPE_SYSTEM)
            CASE_END
            DEFAULT_BEGIN("","")
            VALUE_CONST(response, "Response", SM_ROUTER_RESPONSE_SEND_INTERNAL)
            DEFAULT_END
        CHOICE_END
        COMMENT(COMMENT_TEXT, "MO SM Control result defines the result of ATK MO SM Control check.")
        VALUE_CONST(control_result, "Control result", SM_ROUTER_MO_SM_CONTROL_RESULT)
        COMMENT(COMMENT_TEXT, "Assigned SM message reference if success response or if response type is SM_ROUTER_RESPONSE_TYPE_SYSTEM. Otherwise zero.")
        VALUE(8, BE, reference_id, "Reference id", DEC)
        COMMENT(COMMENT_TEXT, "Number of successfully sent TPDUs.")
        VALUE(8, BE, sent_tpdu_count, "Sent TPDU count", DEC)
        FILLER(FILLER_FIXED, 16)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 3)
        REFERENCE (8, BE, sub_block_count, "Number of Sub Blocks", N_SB)
        COMMENT(COMMENT_PARAGRAPH, "Optional:")
        COMMENT(COMMENT_PARAGRAPH, "- SMS-Submit-Report TPDU sub block")
        COMMENT(COMMENT_PARAGRAPH, "[SM_ROUTER_SB_TPDU]")
        COMMENT(COMMENT_PARAGRAPH, "- MO SM Control Alpha ID sub block")
        COMMENT(COMMENT_PARAGRAPH, "[SM_ROUTER_SB_TEXT_STRING]")
        COMMENT(COMMENT_PARAGRAPH, "Optional:")
        COMMENT(COMMENT_PARAGRAPH, "- Multi SIM information sub block")
        COMMENT(COMMENT_PARAGRAPH, "[MULTI_SIM_SHARED_SB_SIM_ID]")
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Message details", N_SB, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY (SM_ROUTER_SB_TPDU)
            SB_LST_ENTRY (SM_ROUTER_SB_TEXT_STRING)
            SB_LST_ENTRY (MULTI_SIM_SHARED_SB_SIM_ID)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(SM_ROUTER_MO_SM_SEND_REQ, SM_ROUTER_MO_SM_SEND_RESP)

/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_SM_REGISTER_REQ                                   */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_MT_SM_REGISTER_REQ, MESSAGE_REQ, "", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, "SM_ROUTER_REGISTRATION_ID_NONE in registration, SM Router assigned Id in deregistration.")
        VALUE(16, BE, registration_id,"Registration Id", DEC)
        COMMENT(COMMENT_TEXT, "Registration or deregistration.")
        VALUE_CONST(action, "Action", SM_ROUTER_ACTION)
        COMMENT(COMMENT_TEXT, "Defines the specific SM content together with possible sub block(s).")
        VALUE_CONST(registration_type, "Registration type", SM_ROUTER_REGISTRATION_TYPE)
        COMMENT(COMMENT_TEXT, "Either specific MT SM type or all MT SM types. Default value: SM_ROUTER_SM_TYPE_DELIVER.")
        VALUE_CONST(message_type, "Message type", SM_ROUTER_MESSAGE_TYPE)
        FILLER(FILLER_FIXED, 16)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 255)
        REFERENCE (8, BE, sub_block_count, "Number of Sub Blocks", N_SB)
        COMMENT(COMMENT_PARAGRAPH, "For SM_ROUTER_REG_TYPE_LOGICAL_AND, must have exactly 2 subblocks:")
        COMMENT(COMMENT_PARAGRAPH, "SM_ROUTER_SB_ADDRESS and SM_ROUTER_SB_SM_USER_DATA.")
        COMMENT(COMMENT_PARAGRAPH, "For other registration types, many sub blocks allowed but of one type only can be included.")
        COMMENT(COMMENT_PARAGRAPH, "Optional:")
        COMMENT(COMMENT_PARAGRAPH, "- Application port(s) sub block(s)")
        COMMENT(COMMENT_PARAGRAPH, "[SM_ROUTER_SB_APPL_PORT]")
        COMMENT(COMMENT_PARAGRAPH, "- Originator address sub block(s)")
        COMMENT(COMMENT_PARAGRAPH, "[SM_ROUTER_SB_ADDRESS] (SM_ROUTER_ADDRESS_TYPE_UNICODE)")
        COMMENT(COMMENT_PARAGRAPH, "- SM user data sub block(s)")
        COMMENT(COMMENT_PARAGRAPH, "[SM_ROUTER_SB_SM_USER_DATA]")
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Message details", N_SB, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY (SM_ROUTER_SB_APPL_PORT)
            SB_LST_ENTRY (SM_ROUTER_SB_ADDRESS)
            SB_LST_ENTRY (SM_ROUTER_SB_SM_USER_DATA)
        SB_LST_REF_END
    MSG_END

/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_SM_REGISTER_RESP                                  */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_MT_SM_REGISTER_RESP, MESSAGE_RESP, "", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, "Indicates success of the request.")
        VALUE_CONST(response, "Response", SM_ROUTER_RESPONSE_REGISTER)
        FILLER(FILLER_FIXED, 8)
        COMMENT(COMMENT_TEXT, "Value depends on requested action and success. See ")
        COMMENT_LINK(LINK_NOTE, "/7/", "", "")
        VALUE(16, BE, registration_id,"Registration Id", DEC)
        COMMENT(COMMENT_TEXT, "Current MT Service Status.")
        VALUE_CONST(mt_service_status, "MT Service Status", SM_ROUTER_MT_SERVICE_STATUS)
    MSG_END

    MSG_PAIR(SM_ROUTER_MT_SM_REGISTER_REQ, SM_ROUTER_MT_SM_REGISTER_RESP)


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_SM_RECEIVED_NTF                                   */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_MT_SM_RECEIVED_NTF, MESSAGE_NTF, "", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, "Registration Id - verification for client. Indicates the id of matching MT SM registration.")
        VALUE(16, BE, registration_id,"Registration Id", DEC)
        COMMENT(COMMENT_TEXT, "Message reference for MT message.")
        VALUE(8, BE, reference_id, "Reference id", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 3)
        REFERENCE (8, BE, sub_block_count, "Number of Sub Blocks", N_SB)
        COMMENT(COMMENT_PARAGRAPH, "Mandatory:")
        COMMENT(COMMENT_PARAGRAPH, "- SMSC address sub block")
        COMMENT(COMMENT_PARAGRAPH, "[SM_ROUTER_SB_ADDRESS] (SM_ROUTER_ADDRESS_TYPE_SMSC)")
        COMMENT(COMMENT_PARAGRAPH, "- SMS-Deliver, SMS-Status-Report or undefined TPDU sub block")
        COMMENT(COMMENT_PARAGRAPH, "[SM_ROUTER_SB_TPDU]")
        COMMENT(COMMENT_PARAGRAPH, "- Multi SIM information sub blocks")
        COMMENT(COMMENT_PARAGRAPH, "[MULTI_SIM_SHARED_SB_SIM_ID]")
        COMMENT(COMMENT_PARAGRAPH, "[MULTI_SIM_SHARED_SB_ICC]")
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Message details", N_SB, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY (SM_ROUTER_SB_ADDRESS)
            SB_LST_ENTRY (SM_ROUTER_SB_TPDU)
            SB_LST_ENTRY (MULTI_SIM_SHARED_SB_SIM_ID)
            SB_LST_ENTRY (MULTI_SIM_SHARED_SB_ICC)
        SB_LST_REF_END
   MSG_END

/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_SM_RESPONSE_REQ                                   */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_MT_SM_RESPONSE_REQ, MESSAGE_REQ, "", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, "Message reference for MT message. Same as in SM_ROUTER_MT_SM_RECEIVED_NTF")
        VALUE(8, BE, reference_id, "Reference id", DEC)
        COMMENT(COMMENT_TEXT, "Either internal or system response type is used.")
        REFERENCE_CONST(response_type, "Response type", RESPONSE_TYPE, SM_ROUTER_RESPONSE_TYPE)
        CHOICE_BEGIN(response, "Response val", RESPONSE_TYPE)        
            CASE_BEGIN(SM_ROUTER_RESPONSE_TYPE_SYSTEM, "", "")
               COMMENT(COMMENT_TEXT, "Only non-MO error values applicable.")
               VALUE_CONST(response, "Response system", SM_ROUTER_REQUEST_RESPONSE_SYSTEM)
            CASE_END
               VALUE_CONST(response, "Response", SM_ROUTER_REQUEST_RESPONSE_INTERNAL)
            DEFAULT_BEGIN("", "")
            DEFAULT_END            
        CHOICE_END
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        REFERENCE (8, BE, sub_block_count, "Number of Sub Blocks", N_SB)
        COMMENT(COMMENT_PARAGRAPH, "Optional:")
        COMMENT(COMMENT_PARAGRAPH, "- SMS-Deliver-Report TPDU sub block")
        COMMENT(COMMENT_PARAGRAPH, "[SM_ROUTER_SB_TPDU]")
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Message details", N_SB, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY (SM_ROUTER_SB_TPDU)
        SB_LST_REF_END
    MSG_END

/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_SM_RESPONSE_RESP                                  */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_MT_SM_RESPONSE_RESP, MESSAGE_RESP, "", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, "Indicates success of response request.")
        VALUE_CONST(response, "Response", SM_ROUTER_RESPONSE_RESPONSE)
        COMMENT(COMMENT_TEXT, "Message reference for MT message. Same as in SM_ROUTER_MT_SM_RESPONSE_REQ")
        VALUE(8, BE, reference_id, "Reference id", DEC)
    MSG_END

    MSG_PAIR(SM_ROUTER_MT_SM_RESPONSE_REQ, SM_ROUTER_MT_SM_RESPONSE_RESP)

/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_STORAGE_STATE_SET_REQ                                */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_STORAGE_STATE_SET_REQ, MESSAGE_REQ, "", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, "Requested Message Storage state. Indicates that memory full case has been solved.")
        VALUE_CONST(new_state, "New state", SM_ROUTER_STORAGE_STATE_ACTION)
    MSG_END

/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_STORAGE_STATE_SET_RESP                               */
/* ----------------------------------------------------------------------- */
    MSG_BEGIN(SM_ROUTER_STORAGE_STATE_SET_RESP, MESSAGE_RESP, "", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, "Informs if state change succeeded or not.")
        VALUE_CONST(response, "Response", SM_ROUTER_RESPONSE_STORAGE_STATE_SET)
        COMMENT(COMMENT_TEXT, "Message Storage state of SM Router.")
        VALUE_CONST(state, "State", SM_ROUTER_MESSAGE_STORAGE_STATE)
    MSG_END

    MSG_PAIR(SM_ROUTER_STORAGE_STATE_SET_REQ, SM_ROUTER_STORAGE_STATE_SET_RESP)



/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_TRIGGER_NTF                                       */
/* ----------------------------------------------------------------------- */
    COMMENT(COMMENT_TEXT,
            "This message is only for SM router server internal use. "
            "With this message certain actions can be started in the "
            "SM router server's MT state machine.")
    MSG_BEGIN(SM_ROUTER_MT_TRIGGER_NTF, MESSAGE_NTF, "002.003", "")
        COMMON_PREFIX_MSG_HDR
        COMMENT(COMMENT_TEXT, 
            "Action identification number for MT state machine.")
        VALUE(16, BE, action_id, "Action ID", DEC)
        FILLER(FILLER_FIXED, 16)
    MSG_END

RES_END

/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */


#endif /* _SM_ROUTER_ISI_M_H_ */


/* End of file sm_router_isi_m.h */
