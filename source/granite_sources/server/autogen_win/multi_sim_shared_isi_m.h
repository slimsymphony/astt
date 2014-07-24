/*
NOKIA
[Oulu]
[S40/S30 Asset]



            multi_sim_shared_isi_m.h
            ------------------------
            SW include - ANSI C



Continuus Ref:
--------------
Project:          S40_ISI

%name:            multi_sim_shared_isi_m.h %
%version:         002.010 %
%cvtype:          incl %
%instance:        ou1s40_1 %

Document code:    -

Copyright(c) Nokia Corporation. All rights reserved.

Change History:

VERSION     : 002.010     APPROVED   01-Jun-2011     Mikko Virranniemi
REASON      : AcceptID 1662767: if toggle view is not yet accessed, show user
              response note if selected, server
REFERENCE   : ActionDB for SWAM	MV11060134788: Multi SIM Server ISI IF v002.010:
              Preferred mode flags.
DESCRIPTION : A version update to keep the versions in sync with the
              multi_sim_isi_m.h

VERSION     : 002.009     APPROVED   18-May-2011     Turkka Savaloja
REASON      : AcceptID 1598327: update server interface
REFERENCE   : ActionDB for SWAM	TS11051640334: Multi SIM Server ISI IF update v002.009:
DESCRIPTION : Dummy checkout for version update.

VERSION     : 002.008     APPROVED   15-Apr-2011     Mikko Virranniemi
REASON      : AcceptID 1559268: As a user I want to manage SIMs (rename SIMs,
              default SIM handling), personalize view page changes to server.
REFERENCE   : ActionDB for SWAM	MV11050945632: Multi SIM Server ISI IF 002.008:
              Defaults set addition
DESCRIPTION : A version update to keep the versions in sync with the
              multi_sim_isi_m.h

VERSION     : 002.007     APPROVED   15-Apr-2011     Mikko Virranniemi
REASON      : AcceptID 1503341: As a user I want to manage SIMs in personalize
              view (call, sms, mms, data) interface 1
REFERENCE   : ActionDB for SWAM	MV11041835118: Multi SIM Server ISI IF 002.007:
              Preferred SIM
DESCRIPTION : A version update to keep the versions in sync with the
              multi_sim_isi_m.h

VERSION     : 002.006     APPROVED   31-Mar-2011     Mikko Virranniemi
REASON      : Accept ID: 1309297: Warm swap: Move APPS to IDLE to correct place
REFERENCE   : ActionDB for SWAM	MV11040529102: Multi SIM Server ISI IF V002.006.
DESCRIPTION : A version update to keep the versions in sync with the
              multi_sim_isi_m.h

VERSION     : 002.005     Approved   26-Jan-2011     Mikko Virranniemi
REASON      : PCP EO10122737269: DualSIM / Warm Swap : Phone resets if SIM card
              removed during restoring backup
REFERENCE   : ActionDB for SWAM	MV11012657075: Multi SIM Server: Added
              MULTI_SIM_SERVER_ADJUST_REQ/RESP
DESCRIPTION : A version update to keep the versions in sync with the
              multi_sim_isi_m.h

VERSION     : 002.004     Approved   17-Nov-2010     Tirkkonen Veli-Pekka
REASON      : Inspection
REFERENCE   : ActionDB for SWAM	VT10111774648: Multi SIM server : Added Feature ready request and response.
DESCRIPTION : A version update to keep the versions in sync with the
              multi_sim_isi_m.h

VERSION     : 002.003     Approved   18-Oct-2010     Mikko Virranniemi
REASON      : Inspection
REFERENCE   : ActionDB for SWAM	MV10101130354: Multi SIM Server ISI IF: Some
              flags added.
DESCRIPTION : A version update to keep the versions in sync with the
              multi_sim_isi_m.h

VERSION     : 002.002     Proposal   06-Oct-2010     Mikko Virranniemi
REASON      : PCP KL10092938014: Dual SIM: Completing PIN code change from PUK
              code query results in note "SIM inserted" is shown.
REFERENCE   : ActionDB for SWAM	MV10101130354: Multi SIM Server ISI IF: Some
              flags added.
DESCRIPTION : A version update to keep the versions in sync with the
              multi_sim_isi_m.h

VERSION     : 002.001     Approved   06-May-2010     Tanja Kuusirati
REASON      : Call UI EDT2:Sprint4:Multi SIM Server:ISI IF version 002.001 
REFERENCE   : ActionDB for SWAM	: TK10042655440
DESCRIPTION : Added new interface to set last used sim for call, sms, mms and data.

VERSION     : 002.000       Approved   26-Apr-2010     Tanja Kuusirati
REASON      : Call UI EDT2: Sprint 3:Multi SIM Server:ISI IF version 002.000.
REFERENCE   : ActionDB for SWAM	: TK10042655440
DESCRIPTION : MULTI_SIM_ISI_VERSION updated.

VERSION     : 001.003       Approved   24-Mar-2010     Mikko Virranniemi
REASON      : Call UI EDT2: Sprint 1:Multi SIM Server:ISI IF version 001.003.
REFERENCE   : ActionDB for SWAM: MV10032431445
DESCRIPTION : MULTI_SIM_ISI_VERSION updated.

VERSION     : 001.002       Approved   15-Mar-2010     Mikko Virranniemi
REASON      : Inspection
REFERENCE   : ActionDB for SWAM	: MV10031531470
DESCRIPTION : Device ID description updated.

VERSION     : 001.001       Approved   10-Feb-2010     Mikko Virranniemi
REASON      : Inspection
REFERENCE   : ActionDB for SWAM	: MV09121642475, MV10020230704.
DESCRIPTION : Created

*/

/* ------------------------------------------------------------------------- */


/*  1    ABSTRACT

    1.1    Module type

    Message definition file for autogen
   

    1.2    Functional description

    This file is the message definition file for the Multi Sim server.


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

#ifndef _MULTI_SIM_SHARED_ISI_M_H_
#define _MULTI_SIM_SHARED_ISI_M_H_


/*  3    CONSTANTS */

/* Shared sub block ID's */

#define MULTI_SIM_SHARED_SB_SIM_ID      0xFD00
#define MULTI_SIM_SHARED_SB_ICC         0xFD01
#define MULTI_SIM_SHARED_SB_DEVICE_ID   0xFD02

/* definitions for this macro file */

/* Other constants */

#define MULTI_SIM_ICC_LEN   10

/* default ISI version */

#ifndef MULTI_SIM_ISI_VERSION
#define MULTI_SIM_ISI_VERSION
#define MULTI_SIM_ISI_VERSION_Z      2
#define MULTI_SIM_ISI_VERSION_Y      10
#endif

/*  4    MACROS */


/* --------------------------------------------------------------------- */
/* Project / Document information */
/* --------------------------------------------------------------------- */


/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                 "Devices/R&D/S40 Asset Oulu")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                      "S40 Messaging")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,                "Mikko Virranniemi")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,           "CONFIDENTIAL")

/* ISI header properties */
PROPERTY_STRING(PROPERTY_ISIHDR_TITLE,                      "Multi Sim Shared ISI Definitions")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                   "multi_sim_shared_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16,                "")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,       "ou1glint")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,     "global_interface/coresw_interface/coresw_public")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16,  "")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,    "ou1glint#1")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16, "")

/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                        "Multi Sim Shared Message Specification")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                     "i_multi_sim_shared_m.html")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,              "-")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB,         "ou1glint")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,       "GIF_SPECS-ou1glint#browse")
PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH,               "coresw_interface/coresw_public")
PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

/* Include also dynamic fields in sub-blocks */
PROPERTY(PROPERTY_ISIHDR_GENERATE_ALL_STRUCTURE_ELEMENTS)

/* Auto-generate changes to ISI version history */
PROPERTY_STRING(PROPERTY_ISI_VERSION_AUTO_GENERATE, "001.002")

RES_BEGIN(RESOURCE_ISI_SHARED,
          PN_MULTI_SIM,
          multi_sim,
          "Multi Sim Shared Subblock Descriptions",
          RES_VERSION_STRING(MULTI_SIM_ISI_VERSION_Z, MULTI_SIM_ISI_VERSION_Y),
          FALSE)

/* --------------------------------------------------------------------- */
/* ISI version history */
/* --------------------------------------------------------------------- */
	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "AcceptID 1662767: if toggle view is not yet accessed, show user response note if selected, server")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Accept ID: 665902: Dual SIM - FullTouch (Gaia)")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "01-Jun-2011")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Mikko Virranniemi")
    COMMENT(COMMENT_TEXT, "A version update to keep the versions in sync with the multi_sim_isi.h")
    ISI_VERSION_HISTORY("002.010")

	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "AcceptID 1598327: update server interface")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Accept ID: 1382145: As a user I want to set default SIM for data connection")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "18-May-2011")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Turkka Savaloja")
    COMMENT(COMMENT_TEXT, "Dummy checkout for version update.")
    ISI_VERSION_HISTORY("002.009")

    PROPERTY_STRING(COMMENT_CHANGE_REASON,    "AcceptID 1559268: As a user I want to manage SIMs (rename SIMs, default SIM handling), personalize view page changes to server.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Accept ID: 665902: Dual SIM - FullTouch (Gaia)")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "15-Apr-2011")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Mikko Virranniemi")
    COMMENT(COMMENT_TEXT, "A version update to keep the versions in sync with the multi_sim_isi.h")
    ISI_VERSION_HISTORY("002.008")

	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "AcceptID 1503341: As a user I want to manage SIMs in personalize view (call, sms, mms, data) interface 1")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Accept ID: 665902: Dual SIM - FullTouch (Gaia)")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "15-Apr-2011")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Mikko Virranniemi")
    COMMENT(COMMENT_TEXT, "A version update to keep the versions in sync with the multi_sim_isi.h")
    ISI_VERSION_HISTORY("002.007")

	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "Accept ID: 1309297: Warm swap: Move APPS to IDLE to correct place")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Accept ID: 665902: Dual SIM - FullTouch (Gaia)")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "31-Mar-2011")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Mikko Virranniemi")
    COMMENT(COMMENT_TEXT, "A version update to keep the versions in sync with the multi_sim_isi.h")
    ISI_VERSION_HISTORY("002.006")

	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "PCP EO10122737269: DualSIM / Warm Swap : Phone resets if SIM card removed during restoring backup")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ: 408-5644: 'Smart' Dual SIM in S40")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "26-Jan-2011")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Mikko Virranniemi")
    COMMENT(COMMENT_TEXT, "A version update to keep the versions in sync with the multi_sim_isi.h")
    ISI_VERSION_HISTORY("002.005")

	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "Inspection.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ: 408-5644: 'Smart' Dual SIM in S40")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "18-Nov-2010")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Tirkkonen Veli-Pekka")
    COMMENT(COMMENT_TEXT, "A version update to keep the versions in sync with the multi_sim_isi.h")
    ISI_VERSION_HISTORY("002.004")

	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "Inspection.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ: 408-5644: 'Smart' Dual SIM in S40")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "18-Oct-2010")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Mikko Virranniemi")
    COMMENT(COMMENT_TEXT, "A version update to keep the versions in sync with the multi_sim_isi.h")
    ISI_VERSION_HISTORY("002.003")

	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "PCP KL10092938014: Dual SIM: Completing PIN code change from PUK code query results in note SIM inserted is shown.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ: 408-5644: 'Smart' Dual SIM in S40")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "PROPOSAL")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "06-Oct-2010")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Mikko Virranniemi")
    COMMENT(COMMENT_TEXT, "A version update to keep the versions in sync with the multi_sim_isi.h")
    ISI_VERSION_HISTORY("002.002")

	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "Call UI EDT3: Sprint3:Multi SIM Server:ISI IF version 002.001")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ: 408-5644: 'Smart' Dual SIM in S40")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "06-May-2010")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Tanja Kuusirati")
    COMMENT(COMMENT_TEXT, "Added new interface to set last used sim for call, sms, mms and data.")
    ISI_VERSION_HISTORY("002.001")

	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "Call UI EDT3: Sprint 3:Multi SIM Server:ISI IF version 002.000")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ: 408-5644: 'Smart' Dual SIM in S40")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "PROPOSAL")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "22-Apr-2010")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Tanja Kuusirati")
    COMMENT(COMMENT_TEXT, "Multi SIM server ISI IF update.")
    ISI_VERSION_HISTORY("002.000")

	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "Call UI EDT2: Sprint 1:Multi SIM Server:ISI IF version 001.003")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ: 408-5644: 'Smart' Dual SIM in S40")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "24-Mar-2010")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Mikko Virranniemi")
    COMMENT(COMMENT_TEXT, "MULTI_SIM_ISI_VERSION updated.")
    ISI_VERSION_HISTORY("001.003")

	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "Call UI Sprint 3: Multi SIM server: ISI IF (001.001) update")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ: 408-5644: 'Smart' Dual SIM in S40")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "15-Mar-2010")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Mikko Virranniemi")
    COMMENT(COMMENT_TEXT, "Device ID description updated.")
    ISI_VERSION_HISTORY("001.002")

	PROPERTY_STRING(COMMENT_CHANGE_REASON,    "First official version for inspection")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ: 408-5644: 'Smart' Dual SIM in S40")
    /* state DRAFT, NON-DRAFT, PROPOSAL or APPROVED */
    PROPERTY_STRING(COMMENT_CHANGE_STATUS,    "APPROVED")
    /* date of change, eg. "01-Sep-2002" */
    PROPERTY_STRING(COMMENT_CHANGE_DATE,      "10-Feb-2010")
    /* change responsible person */
    PROPERTY_STRING(COMMENT_CHANGE_PERSON,    "Mikko Virranniemi")
    COMMENT(COMMENT_TEXT, "Defines Multi Sim Server shared ISI interface")
    ISI_VERSION_HISTORY("001.001")

    COMMENT(COMMENT_PARAGRAPH, "autogen documentation")
    COMMENT(COMMENT_PARAGRAPH, "Intranet")
    COMMENT(COMMENT_PARAGRAPH, "http://rdsuite.europe.nokia.com/products/autogen/documentation.asp")
    COMMENT(COMMENT_PARAGRAPH, "Link: autogen documentation")
    NOTE("/1/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Server Specification Documentation Guidelines")
    COMMENT(COMMENT_PARAGRAPH, "Document code: DSY02803-EN")
    COMMENT(COMMENT_PARAGRAPH, "DocMan location: eslns42/SRV/Nokia")
    COMMENT(COMMENT_PARAGRAPH, "DocMan: DCT DocMan")
    COMMENT(COMMENT_PARAGRAPH, "Filename: TP/PP/ppmgmtdm.nsf")
    NOTE("/2/")

    COMMENT(COMMENT_PARAGRAPH, "ISI General Information")
    COMMENT(COMMENT_PARAGRAPH, "Document code: DSY02801-EN")
    COMMENT(COMMENT_PARAGRAPH, "DocMan location: eslns42/SRV/Nokia")
    COMMENT(COMMENT_PARAGRAPH, "DocMan: DCT DocMan")
    COMMENT(COMMENT_PARAGRAPH, "Filename: TP/PP/ppmgmtdm.nsf")
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
    
    COMMENT(COMMENT_PARAGRAPH, "ISI Multi Sim Server Feature and Protocol Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Database: ou1glint")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Project: GIF_SPECS_S40-browse:project:ou1glint#1")
    COMMENT(COMMENT_PARAGRAPH, "GIF_SPECS_S40/S40_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_multi_sim_fp.doc")
    NOTE("/6/")

    COMMENT(COMMENT_PARAGRAPH, "SIM Server ISI Message Description")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Database: ou1gif")
    COMMENT(COMMENT_PARAGRAPH, "Continuus Project: GIF_SPECS-ou1gif#browse")
    COMMENT(COMMENT_PARAGRAPH, "GIF_SPECS/CoreSW/coresw_public_spec")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_sim_m.html")
    NOTE("/7/")

/* --------------------------------------------------------------------- */
/* Symbol tables */
/* --------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
/* Constant Table:  */
/* ----------------------------------------------------------------------- */

/*--------------------------------------------------------------------------*/
/* Sub constant tables                          */
/*--------------------------------------------------------------------------*/
   
/* --------------------------------------------------------------------- */
/* Sub blocks */
/* --------------------------------------------------------------------- */

    SB_BEGIN(MULTI_SIM_SHARED_SB_SIM_ID, "", "")
        COMMON_SB_16_LONG
        COMMENT(COMMENT_TEXT, "Unique ID of the SIM card. Generated by the Multi SIM server.")
        VALUE(16, BE, sim_id, "SIM ID", DEC)
        FILLER(FILLER_FIXED, 16)
    SB_END

    SB_BEGIN(MULTI_SIM_SHARED_SB_ICC, "", "")
        COMMON_SB_16_LONG
        COMMENT(COMMENT_TEXT, "The SIM card identification field. See SIM Server ISI Message Description ")
        COMMENT_LINK(LINK_NOTE, "/7/","","")
        COMMENT(COMMENT_TEXT, ". BCD coded.")
        SEQ_OF(icc, "ICC",AUTOGEN_SEQ_BYTE_HEX, MULTI_SIM_ICC_LEN)
        FILLER(FILLER_FIXED, 16)
    SB_END

    SB_BEGIN(MULTI_SIM_SHARED_SB_DEVICE_ID, "", "")
        COMMON_SB_16_LONG
        COMMENT(COMMENT_TEXT, "Phonet device id. Possible values 0 (no phonet device id), PN_DEV_MODEM or PN_DEV_MODEM_2.")
        VALUE(8, BE, device_id, "Device ID", DEC)
        FILLER(FILLER_FIXED, 24)
    SB_END

RES_END

/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */


#endif /* _MULTI_SIM_SHARED_ISI_M_H_ */


/* End of file multi_sim_shared_isi_m.h */
