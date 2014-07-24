/*
NOKIA MOBILE PHONES
R&D Copenhagen
SIM Server














            SIM server shared interface description
            --------------------------------

            SW module - Autogen input file





Object Name:        %full_name: co1core#1/incl/sim_shared_isi_m.h/co1core2#020.001 %
 
Filename:           sim_shared_isi_m.h

Document Code:      -

Copyright(c) Nokia Mobile Phones. All rights reserved.



Change History:

VERSION    : 020.001    6-Nov-2009    Thomas Kure Thorngreen    Approved
REASON     : Correct minor errors in SIM ISI macro file, causing PMD decode problems.
REFERENCE  : ActionDB for SWAM: TT09110554994
DESCRIPTION: -

VERSION    : 020.000    12-Aug-2009    Nikolaj Skov    Approved
REASON     : Remove parts of SIM ISI IF not supported by S40 Adaptation SIM Server.
REFERENCE  : ActionDB for SWAM: NS09061946380
DESCRIPTION: -

VERSION    : 018.002    11-Feb-2009    Nikolaj Skov    Approved
REASON     : Change to SUB_MSG_REQUEST_HDR macro.
REFERENCE  : ActionDB for SWAM: NS09021134415
DESCRIPTION: Added padding byte to SUB_MSG_REQUEST_HDR.

VERSION    : 018.000    04-Jan-2008    Thomas Stormark   Approved
REASON     : Updating ISI interface CR to I_CPR_7.2 on Smartcard profile: Parental Control Pincode and OMA BCAST AUTHENTICATE response
REFERENCE  : CM Synergy task: co1core#86560
             WP RM-RIM Tool: 006-15505, 006-16563
             ActionDB for SWAM: TS07110689414
DESCRIPTION: Added ext bcast support to Authenticate req/resp and new PIN_PC to pin isi related msg.
             SIM_SB_AM_HANDLE subblock has been moved to the new sim_shared_isi.h file.

*/


#ifndef _SIM_SHARED_ISI_H_
#define _SIM_SHARED_ISI_H_



/*  3    CONSTANTS */
#ifndef SIM_ISI_VERSION
#define SIM_ISI_VERSION
#define SIM_ISI_VERSION_Z   20
#define SIM_ISI_VERSION_Y   1 /* minor */
#endif 

    /* --------------------------------------------------------------------- */
    /* Project / Document information */
    /* --------------------------------------------------------------------- */

/* Project / Document properties */

PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                "R&D Copenhagen")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                     "Smartcards")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,               "smartcards.support@nokia.com")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,          "CONFIDENTIAL")


/* ISI header properties */
PROPERTY_STRING(PROPERTY_ISIHDR_TITLE,                     "SIM Server Shared ISI Message Specification")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                  "sim_shared_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,      "ou1gif")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,    "global_interface/coresw_interface/coresw_public")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,   "co1core#1")

/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                       "SIM Server Shared ISI Message Description")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                    "i_sim_shared_isi.html")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,             "")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB,        "ou1gif")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,      "GIF_SPECS-ou1gif#browse")
PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH,              "GIF_SPECS/CoreSW/coresw_public_spec")
PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

PROPERTY(PROPERTY_ISIHDR_GENERATE_ALL_STRUCTURE_ELEMENTS)



RES_BEGIN(RESOURCE_ISI_SHARED,
          PN_SIM,
          SIM,
          "Shared SIM Server ISI Interface",
          RES_VERSION_STRING(SIM_ISI_VERSION_Z, SIM_ISI_VERSION_Y),
          FALSE)

    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Correct minor errors in SIM ISI macro file, causing PMD decode problems.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: TT09110554994")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "6-Nov-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Thomas Kure Thorngreen")
    COMMENT(COMMENT_PARAGRAPH,                 "-")
    ISI_VERSION_HISTORY(                       "020.001")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Remove parts of SIM ISI IF not supported by S40 Adaptation SIM Server.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NS09061946380")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "13-Aug-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov")
    COMMENT(COMMENT_PARAGRAPH,                 "-")
    ISI_VERSION_HISTORY(                       "020.000")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change to SUB_MSG_REQUEST_HDR macro.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NS09021134415")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "11-Feb-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov")
    COMMENT(COMMENT_PARAGRAPH,                 "Version updated.")
    ISI_VERSION_HISTORY(                       "018.002")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Updating ISI interface CR to I_CPR_7.2 on Smartcard profile: Parental Control Pincode and OMA BCAST AUTHENTICATE response")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM: 006-15505, 006-16563")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Synergy/CM task: co1core#86560")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM:TS07110689414")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "04-Jan-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Thomas Stormark")
    COMMENT(COMMENT_PARAGRAPH,                 "Added ext bcast support to Authenticate req/resp and new PIN_PC to pin isi related msg.")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_SB_AM_HANDLE subblock has been moved to the new sim_shared_isi.h file.")
    ISI_VERSION_HISTORY(                       "018.000")

    /* --------------------------------------------------------------------- */
    /* Notes / references  */
    /* --------------------------------------------------------------------- */

/* Macros */
#define SIM_SB_16_LONG \
    PROPERTY(PROPERTY_PMD_PARAMETER) \
    REFERENCE(16, BE, SubBlockID, "Sub Block ID", SB_ID) \
    REFERENCE(16, BE, SubBlockLength, "Sub Block Length", SB_LENGTH)

/* Message ID's */

/* Sub block ID's */

/* Start of shared subblocks - must be in range: 0xF000 - 0xF7FF*/
#define  SIM_SB_SHARED_START                       0xF400      /* We just choose the middle */
#define  SIM_SB_AM_HANDLE_ID                       SIM_SB_SHARED_START + 0

/* Other constants */


    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /* Subblock's                                                            */
    /*                                                                       */
    /* Valid only from 018.000                                               */
    /* --------------------------------------------------------------------- */


    /* --------------------------------------------------------------------- */
    /* Application Management Handle  START                                  */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* Shared Subblock status                                                */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_SHARED_SB_STA_TABLE,8, BE, "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_SB_STA_OK,                  1,  "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_SB_STA_NOT_OK,              2,  "018.000", "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_SHARED_SB_AM_STA_STATUS, SIM_SHARED_SB_STA_TABLE, "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_SB_STA_OK,        "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_SB_STA_NOT_OK,    "018.000", "")
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_SERVICE_STATUS_TABLE_TYPE, 8, BE, "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "The requested NAA application service is	available.")
	  CONST_TBL_ENTRY_VER(SIM_STA_APP_SERVICE_AVAILABLE,      0,  "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "The requested NAA application service is not available.")
	  CONST_TBL_ENTRY_VER(SIM_STA_APP_SERVICE_NOT_AVAILABLE,  1,  "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "is not available, e.g. could be loss of contact to the card.")
	  CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,         0x24,  "018.000", "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_SERVICE_STATUS_TABLE, SIM_SERVICE_STATUS_TABLE_TYPE, "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_STA_APP_SERVICE_AVAILABLE,      "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_STA_APP_SERVICE_NOT_AVAILABLE,  "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,            "018.000", "")
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_AM_APP_TYPE_TABLE_TYPE, 8, BE, "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application is of type 2G ICC SIM (TS 51.011)  aka 2G SIM")
	 CONST_TBL_ENTRY_VER(SIM_AM_APP_TYPE_ICC_SIM,      0, "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application is of type 3G UICC USIM (TS 31.102)  aka 3G USIM")
         CONST_TBL_ENTRY_VER(SIM_AM_APP_TYPE_UICC_USIM,    1, "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application is of type 3G UICC ISIM (TS 31.103)  aka 3G ISIM")
         CONST_TBL_ENTRY_VER(SIM_AM_APP_TYPE_UICC_ISIM,    2, "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Information is not available, e.g. could be loss of contact to the card")
         CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,   0x24, "018.000", "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_AM_APP_STATUS_TABLE_TYPE, 8, BE, "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Application Management API is ready for usage")
        CONST_TBL_ENTRY_VER(SIM_AM_READY,                    0,    "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application selection procedure has been executed successful.")
        CONST_TBL_ENTRY_VER(SIM_AM_APP_ACTIVATE_SUCCESS,     1,    "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application selection procedure has failed.")        
	CONST_TBL_ENTRY_VER(SIM_AM_APP_ACTIVATE_FAIL,        2,    "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application has stopped initialisation procedure due to needed user verification procedure (PIN verification needed).")        
	CONST_TBL_ENTRY_VER(SIM_AM_APP_USR_VERIFY_REQUIRED,  3,    "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application has done successful selection and initialisation procedure and is ready for usage.")        
	CONST_TBL_ENTRY_VER(SIM_AM_APP_READY,                4,    "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA Application has done successful application closure and no further access is possible.")   
	CONST_TBL_ENTRY_VER(SIM_AM_APP_TERMINATE,            5,    "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Permanent error. NAA application is dysfunctional.")        
	CONST_TBL_ENTRY_VER(SIM_AM_APP_ERROR,                6,    "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Information is not available, e.g. could be loss of contact to the card.")      
	CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,      0x24,    "018.000", "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_AM_APP_STATUS_TABLE, SIM_AM_APP_STATUS_TABLE_TYPE, "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_READY,                       "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_ACTIVATE_SUCCESS,        "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_ACTIVATE_FAIL,           "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_USR_VERIFY_REQUIRED,     "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_READY,                   "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_TERMINATE,               "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_ERROR,                   "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,            "018.000", "")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_AM_APP_TYPE_TABLE, SIM_AM_APP_TYPE_TABLE_TYPE, "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_TYPE_ICC_SIM,    "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_TYPE_UICC_USIM,  "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_TYPE_UICC_ISIM,  "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,    "018.000", "")
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_GEC_TABLE_TYPE, 8, BE, "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_OK,                       0,  "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_NOT_OK,                   1,  "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_OUT_OF_MEM_MSK,           2,  "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_OUT_OF_MEM_MUK,           3,  "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_COND_USE_NOT_SATISFIED,   4,  "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_AUTH_ERR_MAC,             5,  "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_KEY_FRESH,                6,  "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_DATA_NOT_FOUND,           7,  "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_NOT_AVAILABLE,         0xff,  "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_STA_ILLEGAL_LENGTH,             76,  "018.000", "")
        CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,          0x24,  "018.000", "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_GEC_TABLE, SIM_GEC_TABLE_TYPE, "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_OK,                      "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_NOT_OK,                  "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_OUT_OF_MEM_MSK,          "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_OUT_OF_MEM_MUK,          "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_COND_USE_NOT_SATISFIED,  "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_AUTH_ERR_MAC,            "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_KEY_FRESH,               "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_DATA_NOT_FOUND,          "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_NOT_AVAILABLE,           "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_STA_ILLEGAL_LENGTH,             "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,            "018.000", "")
    DER_CONST_TBL_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_HANDLE")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Subblock used for Application Status and Application service status information.. From 018.000 this subblock is found in sim_shared_isi.h")
     SB_BEGIN(SIM_SB_AM_HANDLE_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SHARED_SB_AM_STA_STATUS)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Internal application number reference to the target NAA application.")
        VALUE(8, BE, AppNum, "AppNum", HEX)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Type of NAA application.")
	VALUE_CONST(AppType, "AppType", SIM_AM_APP_TYPE_TABLE)
        VALUE_CONST(AppStatus, "AppStatus", SIM_AM_APP_STATUS_TABLE)
        VALUE_CONST(AppServiceStatus, "AppServiceStatus", SIM_SERVICE_STATUS_TABLE)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Generic Error Code. Holds the context dependent detailed error information.")
	VALUE_CONST(GecId, "GecId", SIM_GEC_TABLE)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
    SB_END

    /* --------------------------------------------------------------------- */
    /* Application Management Handle  END                                    */
    /* --------------------------------------------------------------------- */

RES_END

#endif /* _SIM_SHARED_ISI_H_ */


