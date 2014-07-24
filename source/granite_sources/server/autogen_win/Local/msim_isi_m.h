/*
NOKIA
R&D Oulu
MACN













            MSIM server interface description
            ---------------------------------

            SW module - Autogen input file






database:           ou1gif

project path:       global_interface/mrsw_interface/mrsw_entity

name:               msim_isi_m.h

instance:           ou1cs#1

document code:      -

Copyright(c) Nokia. All rights reserved.



Change History:

VERSION    : 005.002         06-Sep-2010         Petri Kynsilehto      Approved
REASON     : Update
REFERENCE  : WP RM RIM REQ: 417-69398: SMS storage
             ADB SWAM ID: PK10081344111
DESCRIPTION: ISI IF update for SMS storage.

VERSION    : 005.001         06-May-2010         Petri Kynsilehto      Approved
REASON     : Update
REFERENCE  : WP RM RIM REQ: REQ 417-48843 Access to SIM card in case
             of emergency call 
             ADB SWAM ID: PK10043045416
DESCRIPTION: ISI IF Update.

VERSION    : 005.000         03-Mar-2010         Petri Kynsilehto      Approved
REASON     : Update
REFERENCE  : WP RM RIM SUBs: 417-32951 MACN: EPS AKA procedure - Modem SIM,
             417-25093 MACN: Support for security interworking - WGE
             idle mode mobility, 
             417-63881 Refresh support for new EFs in Modem SIM arch,
             417-8980 MACN 3GPP CR REL 7: Allow the UE to go to the
             HPLMN if available and not return to the last RPLMN -
             MACN and
             417-57516 Remove limitation on CBMID count - MSIM Server
             ADB SWAM ID: PK10021947175
DESCRIPTION: Eutran support for MSIM.

VERSION    : 004.000         25-Jan-2010         Petri Kynsilehto      Approved
REASON     : Update
REFERENCE  : WP RM RIM SUB: 417-64810 WM Source Code delivery for
             Licensees - MACN CM part
             ADB SWAM ID: PK10012143954
DESCRIPTION: Renamed sub-block and refresh file ID.


VERSION    : 003.001         30-Oct-2009         Tapio Askeli          Approved
REASON     : Update
REFERENCE  : RM-RIM SUB: 417-25473: MACN: Storage of EMM information to 
             USIM/ME memory - Modem SIM
             RM-RIM SUB: 417-32922: Equivalent HPLMN display mode
             ADB SWAM ID: TA09101943985
DESCRIPTION: Added new sub-blocks.
             Added a define MSIM_REFRESH_LAST_FILE_ID.
             Checked and corrected data formats.

VERSION    : 003.000         2-Oct-2009         Mika Kaikkonen         Approved
REASON     : Correction
REFERENCE  : RM-RIM REQ 417-4253
             ADB SWAM ID: MK09081348753
             ADB SWAM ID: MK09090850430
DESCRIPTION: Interface update

VERSION    : 002.003         29-Jan-2009         Esa Harju             Approved
REASON     : Correction
REFERENCE  : RM-RIM REQ 417-4253
             ADB SWAM ID: EH09012228715
DESCRIPTION: Added indication structure for MSIM_CS_IND as earlier used
             generic structure tMSIM_Ind contains service type field that has
             been removed from MSIM_CS_IND.
             Changed field order in MSIM_SB_INFO_REQUEST to be aligned
             with rest of the documentation.
             Added size definitions.

VERSION    : 002.002         28-Nov-2008         Petri Kynsilehto      Approved
REASON     : Correction
REFERENCE  : RM-RIM REQ 417-4253
             ADB SWAM ID: PK08112835747
DESCRIPTION: Added support for updating SMS parameters.

VERSION    : 002.001         20-Oct-2008         Petri Kynsilehto      Approved
REASON     : Correction
REFERENCE  : RM-RIM REQ 417-4253
             ADB SWAM ID: PK08102048204
DESCRIPTION: Corrected constant: MSIM_ONE_EMRG_CALL_CODE_LEN.

VERSION    : 002.000         09-Oct-2008         Esa Harju      Approved
REASON     : Updates based on further analysis
REFERENCE  : RM-RIM REQ 417-4253
             ADB SWAM ID:EH08100133214
DESCRIPTION: Discontinued unused services: MSIM_IMSI_REQ/RESP.
             Discontinued unused sub-services: MSIM_PB_REQ/RESP:
              MSIM_PB_LOCATION, MSIM_PB_MSISDN
             Discontinued unused status values: MSIM_STA_LOCK_ACTIVE.
             Added constant:
              MSIM_ONE_EMERG_CALL_CODE_LEN

VERSION    : 001.000         11-Aug-2008         Esa Harju      Approved
REASON     : Document approved
REFERENCE  : RM-RIM REQ 417-4253
             ADB SWAM ID:EH08061947229
DESCRIPTION: Document approved.

VERSION    : 000.003         07-Aug-2008         Esa Harju      Proposal
REASON     : Updates after inspection
REFERENCE  : RM-RIM REQ 417-4253
DESCRIPTION: Removed MSIM_PB_IND as same information is carried in MSIM_IND.
             Removed MSIM_STATE_SIM_LOCK_OPERATIVE.
             Removed generic indication type tSIM_Indication. Clients using
              it should start using appropriate message structure in the
              future.

VERSION    : 000.002         31-Jul-2008         Esa Harju      Proposal
REASON     : Updates after inspection
REFERENCE  : RM-RIM REQ 417-4253
DESCRIPTION: Corrected some messages formats in HTML vs. header file.
             Removed MSIM_OPERATOR_REQ & MSIM_OPERATOR_RESP message pair.
             Removed MSIM_IMSI_EQUAL_REQ & MSIM_IMSI_EQUAL_RESP IMSI_EQUAL
              sub-message pair.
             Removed MSIM_SB_CARD_TYPE sub-block.
             Removed those sub-blocks that are no longer required by Modem SW.
             Removed service type field from those messages that do not have
             more than one useable service:
              - MSIM_STATUS_REQ
              - MSIM_IMSI_REQ
              - MSIM_IMSI_EQUAL_REQ
              - MSIM_CPHS_REQ
              - MSIM_CSP_REQ
              - MSIM_SAT_REQ
              - MSIM_PB_REQ
             Added missing sequence MSIM_EMERG_CALL_CODE generation.
             Changed notifications to indications.
             All constants are now prefixed with MSIM.
             Removed unused values from MSIM_MISC_SERVICE_TYPE_TABLE,
              MSIM_REFRESH_FILE_ID_TABLE and MSIM_STATUS_TABLE.
             Combined various statuses under single status table and
              derived used status from that in order to eliminate multiple
              definitions of same status values, which were put into comments
              by Autogen.

             VERSION    : 000.001         19-Jun-2008         Esa Harju      Proposal
REASON     : First version created based on sim_isi_m.h
REFERENCE  : RM-RIM REQ 417-4253
DESCRIPTION: Created initial version of Modem SIM server message description
             document.
*/

#ifndef MSIM_ISI_VERSION
#define MSIM_ISI_VERSION
#define MSIM_ISI_VERSION_Z   5
#define MSIM_ISI_VERSION_Y   2
#endif /* MSIM_ISI_VERSION */


#ifndef _MSIM_ISI_M_H_
#define _MSIM_ISI_M_H_

/*  3    CONSTANTS */

/*----------------------------------------------*/

/* --------------------------------------------------------------------- */
/* Message ID's                                                          */
/* --------------------------------------------------------------------- */
#define MSIM_AUTHENTICATION_REQ                   1
#define MSIM_AUTHENTICATION_RESP                  2

#define MSIM_CS_READ_REQ                          3
#define MSIM_CS_READ_RESP                         4

#define MSIM_CS_WRITE_REQ                         5
#define MSIM_CS_WRITE_RESP                        6

#define MSIM_DATA_SIZES_REQ                       7
#define MSIM_DATA_SIZES_RESP                      8

#define MSIM_STATUS_REQ                           9
#define MSIM_STATUS_RESP                         10

#define MSIM_IMSI_REQ                            11
#define MSIM_IMSI_RESP                           12

#define MSIM_IMSI_EQUAL_REQ                      13
#define MSIM_IMSI_EQUAL_RESP                     14

#define MSIM_SMS_REQ                             15
#define MSIM_SMS_RESP                            16

#define MSIM_DYNAMIC_FLAGS_REQ                   17
#define MSIM_DYNAMIC_FLAGS_RESP                  18

#define MSIM_FDN_CHECK_REQ                       19
#define MSIM_FDN_CHECK_RESP                      20

#define MSIM_CPHS_REQ                            21
#define MSIM_CPHS_RESP                           22

#define MSIM_READ_TABLE_REQ                      23
#define MSIM_READ_TABLE_RESP                     24

#define MSIM_CSP_REQ                             25
#define MSIM_CSP_RESP                            26

#define MSIM_SAT_REQ                             27
#define MSIM_SAT_RESP                            28

#define MSIM_REFRESH_REQ                         29
#define MSIM_REFRESH_RESP                        30
#define MSIM_REFRESH_IND                         31

#define MSIM_GPRS_REQ                            32
#define MSIM_GPRS_RESP                           33

#define MSIM_PB_REQ                              34
#define MSIM_PB_RESP                             35

#define MSIM_SMS_STORAGE_REQ                     36
#define MSIM_SMS_STORAGE_RESP                    37

#define MSIM_ACL_IND                             39
#define MSIM_SERVER_READY_IND                    40
#define MSIM_CS_IND                              41
#define MSIM_IND                                 42

/* --------------------------------------------------------------------- */
/* Sub block ID's                                                        */
/* --------------------------------------------------------------------- */
#define MSIM_SB_CS_START                         100
#define MSIM_SB_ACC                              (MSIM_SB_CS_START + 0)
#define MSIM_SB_CIPHERING_KEY                    (MSIM_SB_CS_START + 1)
#define MSIM_SB_CIPHERING_KEY_SNR                (MSIM_SB_CS_START + 2)
#define MSIM_SB_FORBIDDEN_PLMNS                  (MSIM_SB_CS_START + 3)
#define MSIM_SB_GPRS_CIPHERING_KEY               (MSIM_SB_CS_START + 4)
#define MSIM_SB_GPRS_CIPHERING_KEY_SNR           (MSIM_SB_CS_START + 5)
#define MSIM_SB_GPRS_RAI                         (MSIM_SB_CS_START + 6)
#define MSIM_SB_GPRS_RAUS                        (MSIM_SB_CS_START + 7)
#define MSIM_SB_GPRS_TMSI                        (MSIM_SB_CS_START + 8)
#define MSIM_SB_GPRS_TMSI_SIGN_VALUE             (MSIM_SB_CS_START + 9)
#define MSIM_SB_HPLMN                            (MSIM_SB_CS_START + 10)
#define MSIM_SB_HPLMN_SEARCH                     (MSIM_SB_CS_START + 11)
#define MSIM_SB_IMSI                             (MSIM_SB_CS_START + 12)
#define MSIM_SB_LAI                              (MSIM_SB_CS_START + 13)
#define MSIM_SB_TMSI                             (MSIM_SB_CS_START + 14)
#define MSIM_SB_UMTS_CS_KSI                      (MSIM_SB_CS_START + 15)
#define MSIM_SB_UMTS_CS_CIPHERING_KEY            (MSIM_SB_CS_START + 16)
#define MSIM_SB_UMTS_CS_INTEGRITY_KEY            (MSIM_SB_CS_START + 17)
#define MSIM_SB_UMTS_PS_KSI                      (MSIM_SB_CS_START + 18)
#define MSIM_SB_UMTS_PS_CIPHERING_KEY            (MSIM_SB_CS_START + 19)
#define MSIM_SB_UMTS_PS_INTEGRITY_KEY            (MSIM_SB_CS_START + 20)
#define MSIM_SB_UMTS_START_PS                    (MSIM_SB_CS_START + 21)
#define MSIM_SB_UMTS_START_MAX                   (MSIM_SB_CS_START + 22)
#define MSIM_SB_UMTS_START_CS                    (MSIM_SB_CS_START + 23)
#define MSIM_SB_LOC_UPD_STATUS                   (MSIM_SB_CS_START + 24)
#define MSIM_SB_OPERATOR_PLMN                    (MSIM_SB_CS_START + 25)
#define MSIM_SB_USER_PLMN                        (MSIM_SB_CS_START + 26)
#define MSIM_SB_HOME_PLMN                        (MSIM_SB_CS_START + 27)
#define MSIM_SB_ECC                              (MSIM_SB_CS_START + 28)
#define MSIM_SB_PLMN_SELECTOR                    (MSIM_SB_CS_START + 29)
#define MSIM_SB_EQUIVALENT_HPLMNS                (MSIM_SB_CS_START + 30)
#define MSIM_SB_RAT_MODE                         (MSIM_SB_CS_START + 31)
#define MSIM_SB_CARD_TYPE                        (MSIM_SB_CS_START + 32)
#define MSIM_SB_SIMLOCK_STATUS                   (MSIM_SB_CS_START + 33)
#define MSIM_SB_EHPLMN_DISPLAY_MODE              (MSIM_SB_CS_START + 34)
#define MSIM_SB_GUTI                             (MSIM_SB_CS_START + 35)
#define MSIM_SB_TAI                              (MSIM_SB_CS_START + 36)
#define MSIM_SB_EPS_UPD_STATUS                   (MSIM_SB_CS_START + 37)
#define MSIM_SB_ASME_KSI                         (MSIM_SB_CS_START + 38)
#define MSIM_SB_ASME_KEY                         (MSIM_SB_CS_START + 39)
#define MSIM_SB_UL_NAS_COUNT                     (MSIM_SB_CS_START + 40)
#define MSIM_SB_DL_NAS_COUNT                     (MSIM_SB_CS_START + 41)
#define MSIM_SB_NAS_SECUR_ALGOR_IDS              (MSIM_SB_CS_START + 42)
#define MSIM_SB_LAST_RPLMNSI                     (MSIM_SB_CS_START + 43)

#define MSIM_FDN_CHECK_SB_START                  180
#define MSIM_SB_PHONE_NUMBER_FIELD               (MSIM_FDN_CHECK_SB_START + 0)
#define MSIM_SB_SMS_DEST_ADR                     (MSIM_FDN_CHECK_SB_START + 1)
#define MSIM_SB_SMSC_ADR                         (MSIM_FDN_CHECK_SB_START + 2)

#define MSIM_PB_SB_START                         200
#define MSIM_PB_FDN_LIST_STATUS                  (MSIM_PB_SB_START + 1)
#define MSIM_PB_INFO_REQUEST                     (MSIM_PB_SB_START + 2)
#define MSIM_PB_LOCATION                         (MSIM_PB_SB_START + 3)
#define MSIM_PB_MSISDN                           (MSIM_PB_SB_START + 4)
#define MSIM_PB_STATUS                           (MSIM_PB_SB_START + 5)
#define MSIM_PB_SB_END                           (MSIM_PB_SB_START + 6)

#define MSIM_SB_SMS_STORAGE_START                250
#define MSIM_SB_SMS_STATUS                       (MSIM_SB_SMS_STORAGE_START + 0)
#define MSIM_SB_SMS_REMAINDER                    (MSIM_SB_SMS_STORAGE_START + 1)
#define MSIM_SB_SMS_INDEX                        (MSIM_SB_SMS_STORAGE_START + 2)
#define MSIM_SB_SMS_QUERY                        (MSIM_SB_SMS_STORAGE_START + 3)
#define MSIM_SB_SMS_LOCATION_COUNT               (MSIM_SB_SMS_STORAGE_START + 4)

#define MSIM_SB_AUT_START                        300
#define MSIM_SB_UMTS_AUTN_PARAMS                 (MSIM_SB_AUT_START + 0)
#define MSIM_SB_RES_PARAMS                       (MSIM_SB_AUT_START + 1)
#define MSIM_SB_UMTS_AUTN_FAIL_PARAMS            (MSIM_SB_AUT_START + 2)
#define MSIM_SB_RAND_PARAMS                      (MSIM_SB_AUT_START + 3)
#define MSIM_SB_AUT_END                          (MSIM_SB_AUT_START + 4)

/* --------------------------------------------------------------------- */
/* Sub-message IDs                                                       */
/* --------------------------------------------------------------------- */

/* MSIM_CS_READ_REQ/RESP and MSIM_CS_WRITE_REQ/RESP */
#define MSIM_ST_CS_DATA_READ_REQ                 1
#define MSIM_ST_CS_DATA_WRITE_REQ                2
#define MSIM_ST_CS_STATUS_REQ                    3
#define MSIM_ST_CS_DATA_READ_ALL_GSS_REQ         4
#define MSIM_ST_CS_DATA_READ_LIMITED_GSS_REQ     5

/* MSIM_SMS_REQ */
#define MSIM_ST_READ_PARAMETER                   9
#define MSIM_ST_READ_STATUS                     10
#define MSIM_ST_WRITE_STATUS                    11
#define MSIM_ST_UPDATE_PARAMETER                12

/* MSIM_DYNAMIC_FLAGS_REQ */
#define MSIM_ST_READ_DYN_FLAGS                   6
#define MSIM_ST_WRITE_DYN_FLAGS                  7

/* MSIM_REFRESH_REQ/RESP */
#define MSIM_ST_REFRESH_REGISTER                 1
#define MSIM_ST_REFRESH_UNREGISTER               2
#define MSIM_ST_REFRESH_OK                       3
#define MSIM_ST_REFRESH_NOT_OK                   4
#define MSIM_ST_REFRESH_DONE                     5
#define MSIM_ST_REFRESH_ERROR                    6
/* MSIM_REFRESH_IND */
#define MSIM_ST_REFRESH_REQUESTED                7
#define MSIM_ST_REFRESH_NOW                      8
#define MSIM_ST_REFRESH_CANCELLED                9
#define MSIM_ST_REFRESH_STARTING                10

/* MSIM_GPRS_REQ/RESP */
#define MSIM_ST_ACL_STATUS                       1
#define MSIM_ST_CHECK_APN                        2

/* MSIM_IND */
#define MSIM_ST_ALL_SERVICES                     2
#define MSIM_ST_FDN                              3
#define MSIM_ST_INFO                             4
#define MSIM_ST_EMERGENCY_CODES                  8


/* --------------------------------------------------------------------- */
/* Constants                                                             */
/* --------------------------------------------------------------------- */
#define MSIM_RND_PARAMS_LEN                     16
#define MSIM_UMTS_AUTN_PARAMS_LEN               16
#define MSIM_RES_MAX_LEN                        16
#define MSIM_UMTS_CS_CIPH_KEY_LEN               16
#define MSIM_UMTS_CS_INTE_KEY_LEN               16
#define MSIM_UMTS_PS_CIPH_KEY_LEN               16
#define MSIM_UMTS_PS_INTE_KEY_LEN               16
#define MSIM_CIPH_KEY_LEN                        8
#define MSIM_GPRS_CIPH_KEY_LEN                   8
#define MSIM_UMTS_AUTS_PARAMS_LEN               14

#define MSIM_ACC_CTRL_LEN                        2
#define MSIM_BCCH_INFO_LEN                      16
#define MSIM_HPLMN_LEN                           3
#define MSIM_LAI_LEN                             5
#define MSIM_IMSI_LEN                            8
#define MSIM_TMSI_LEN                            4
#define MSIM_RAI_LEN                             6
#define MSIM_GPRS_TMSI_LEN                       4
#define MSIM_GPRS_TMSI_SIGN_VAL_LEN              3
#define MSIM_UMTS_CS_HFN_LEN                     3
#define MSIM_UMTS_PS_HFN_LEN                     3
#define MSIM_UMTS_START_MAX_LEN                  3
#define MSIM_PLMN_LEN                            3
#define MSIM_PLMN_ACCESS_TECHNOLOGY_LEN          2

#define MSIM_GUTI_LEN                           12
#define MSIM_TAI_LEN                             5
/* EPS NAS Security Context lengths defined in TS 33.401 */
#define MSIM_ASME_KSI_LEN                        1
#define MSIM_ASME_KEY_LEN                       32
#define MSIM_UL_NAS_COUNT_LEN                    4
#define MSIM_DL_NAS_COUNT_LEN                    4
#define MSIM_SB_NAS_SECUR_ALGOR_IDS_LEN          1

#define MSIM_MAX_NBR_OF_EMRG_CALL_CODES          5
#define MSIM_ONE_EMRG_CALL_CODE_LEN              3

#define MSIM_SMS_ADDRESS_MAX_LEN                12

#define MSIM_CBS_MSG_MAX_LENGTH                 82

#define MSIM_MAX_NUMBER_OF_TAGS                 10

#define MSIM_MAX_NBR_OF_CBMIDS                   5

#define MSIM_NAME_LEN                           51 /* incl. zero termination */
#define MSIM_NUMBER_LEN                         49 /* incl. zero termination */

#define MSIM_SMS_REMAINDER_LEN                 175 /* EFsms in 3GPP TS 31.102 */

/*  4    MACROS */

#define MSIM_MSG_HDR \
    VALUE(8, BE, TransactionID, "Transaction ID", DEC) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)

#define MSIM_SB_16_LONG \
    REFERENCE(16, BE, SubBlockID, "Sub Block ID", SB_ID) \
    REFERENCE(16, BE, SubBlockLength, "Sub Block Length", SB_LENGTH)

#define MSIM_SB_16_LONG_SEQ \
    VALUE(16, BE, SubBlockID, "Sub Block ID", HEX) \
    VALUE(16, BE, SubBlockLength, "Sub Block Length", DEC)

#define SUB_MSG_REQ \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)

#define SUB_MSG_RESP(statustbl) \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) \
    VALUE_CONST(Status, "Status", statustbl)

#define SUB_MSG_REQUEST_HDR \
    PROPERTY(PROPERTY_HTML_DONT_GENERATE) \
    SEQ_OF(Req, "Req", MSIM_REQUEST, 1) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)

#define SUB_MSG_INFO_HDR(statustbl) \
    PROPERTY(PROPERTY_HTML_DONT_GENERATE) \
    SEQ_OF(Resp, "Resp", MSIM_INFO_RESPONSE, 1) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE_CONST(Status, "Status", statustbl)

#define SUB_MSG_RESP_HDR(statustbl) \
    PROPERTY(PROPERTY_HTML_DONT_GENERATE) \
    SEQ_OF(Resp, "Resp", MSIM_INFO_RESPONSE, 1) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE_CONST(Status, "Status", statustbl)

#define SUB_MSG_IND_HDR(statustbl) \
    PROPERTY(PROPERTY_HTML_DONT_GENERATE) \
    SEQ_OF(Head, "Head", MSIM_IND_SEQ, 1) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE_CONST(Status, "Status", statustbl)


    /* --------------------------------------------------------------------- */
    /* Project / Document information */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                "DRD / CT / WM")
    PROPERTY_STRING(PROPERTY_PROJECT_NAME,                     "MACN")
    PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,            "Petri Kynsilehto")
    PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,          "CONFIDENTIAL")

    /* ISI header properties */
    PROPERTY_STRING(PROPERTY_ISIHDR_TITLE,                     "msim_isi.h")
    PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                  "msim_isi.h")
    PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16,               "")
    PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,      "ou1gif")
    PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,
        "global_interface/mrsw_interface/mrsw_entity")
    PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,   "ou1cs#1")
    PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16,"")

    /* HTML properties */
    PROPERTY_STRING(PROPERTY_HTML_TITLE,                       "MSIM Server "
        "Message Description")
    PROPERTY_STRING(PROPERTY_HTML_FILENAME,                    "i_msim_m.html")
    PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,             "")
    PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB,        "ou1gif")
    PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,      "GIF_SPECS")
    PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH,              "GIF_SPECS/"
        "MultiradioSW/mrsw_entity_spec")
    PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

    PROPERTY(PROPERTY_ISIHDR_GENERATE_ALL_STRUCTURE_ELEMENTS)


/* PN_MODEM_SIM_SRV */
RES_BEGIN(RESOURCE_ISI, PN_MODEM_SIM_SRV, MSIM, "MSIM Server",
    RES_VERSION_STRING(MSIM_ISI_VERSION_Z, MSIM_ISI_VERSION_Y), TRUE)

    /* --------------------------------------------------------------------- */
    /* ISI version history                                                   */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Document updates")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM RIM REQ: 417-69398")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "06-Sep-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Petri Kynsilehto")
    COMMENT(COMMENT_PARAGRAPH,                 "ISI IF update for SMS storage.")
    ISI_VERSION_HISTORY(                       "005.002")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Document updates")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM RIM REQ: 417-48843")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "06-May-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Petri Kynsilehto")
    COMMENT(COMMENT_PARAGRAPH,                 "ISI IF update.")
    ISI_VERSION_HISTORY(                       "005.001")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Document updates")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM RIM SUBs: "
        "417-32951, 417-25093, 417-63881, 417-8980 and 417-57516")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "03-Mar-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Petri Kynsilehto")
    COMMENT(COMMENT_PARAGRAPH,                 "EUTRAN support.")
    ISI_VERSION_HISTORY(                       "005.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Document updates")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ 417-60959")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "25-Jan-2010")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Petri Kynsilehto")
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    ISI_VERSION_HISTORY(                       "004.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Document updates")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ 417-25473, SUB: 417-32922")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "30-Oct-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Tapio Askeli")
    COMMENT(COMMENT_PARAGRAPH,                 "Added sub-blocks for EMM information "
        "storing and equivalent HPLMN display mode handling.")
    ISI_VERSION_HISTORY(                       "003.001")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Document updates")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ 417-4253")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "13-Oct-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Mika Kaikkonen")
    COMMENT(COMMENT_PARAGRAPH,                 "ISI interface update")
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    ISI_VERSION_HISTORY(                       "003.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Document updates")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ 417-4253")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "29-Jan-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Esa Harju")
    COMMENT(COMMENT_PARAGRAPH,                 "Added structure for indication"
        " message MSIM_CS_IND.")
    COMMENT(COMMENT_PARAGRAPH,                 "Changed field order in "
        "MSIM_SB_INFO_REQUEST structure.")
    COMMENT(COMMENT_PARAGRAPH,                 "Added size definitions")

    ISI_VERSION_HISTORY(                       "002.003")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Document updates")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ 417-4253")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "28-Nov-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Petri Kynsilehto")
    COMMENT(COMMENT_PARAGRAPH,                 "Added support for"
        " updating SMS parameters.")
    ISI_VERSION_HISTORY(                       "002.002")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Document updates")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ 417-4253")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "20-Oct-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Petri Kynsilehto")
    COMMENT(COMMENT_PARAGRAPH,                 "Corrected constant"
        " MSIM_ONE_EMRG_CALL_CODE_LEN.")
    ISI_VERSION_HISTORY(                       "002.001")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Document updates")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ 417-4253")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "09-Oct-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Esa Harju")
    COMMENT(COMMENT_PARAGRAPH,                 "Document updated based on "
        "further analysis of interface usage.")
    ISI_VERSION_HISTORY(                       "002.000")

    /* Document changed to approved status. No changes were done to previous
     * proposal. */
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Document approved")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ 417-4253")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "11-Aug-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Esa Harju")
    COMMENT(COMMENT_PARAGRAPH,                 "Document approved.")
    ISI_VERSION_HISTORY(                       "001.000")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Rework based on feedback from "
        "inspection.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ 417-4253")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Proposal")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "07-Aug-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Esa Harju")
    COMMENT(COMMENT_PARAGRAPH,                 "Updates after inspection.")
    ISI_VERSION_HISTORY(                       "000.003")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Rework based on feedback from "
        "inspection.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ 417-4253")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Proposal")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "31-Jul-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Esa Harju")
    COMMENT(COMMENT_PARAGRAPH,                 "Updates after inspection.")
    ISI_VERSION_HISTORY(                       "000.002")

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "New MSIM server interface "
        "created.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM REQ 417-4253")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Proposal")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "19-Jun-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Esa Harju")
    COMMENT(COMMENT_PARAGRAPH,                 "Created initial version of "
        "Modem SIM server message description document.")
    ISI_VERSION_HISTORY(                       "000.001")

    /* --------------------------------------------------------------------- */


    /* --------------------------------------------------------------------- */
    /* Notes references                                                      */
    /* --------------------------------------------------------------------- */
    COMMENT(COMMENT_PARAGRAPH, "Autogen tool")
    COMMENT(COMMENT_PARAGRAPH, "Intranet:  http://autogen")
    NOTE("1")

    COMMENT(COMMENT_PARAGRAPH,
        "ISI Server Specification Documentation Guidelines")
    COMMENT(COMMENT_PARAGRAPH, "Document number:  DSY02804-EN")
    COMMENT(COMMENT_PARAGRAPH, "Docman:           PP DocMan")
    COMMENT(COMMENT_PARAGRAPH, "Server:           eslns42/SRV/Nokia")
    COMMENT(COMMENT_PARAGRAPH, "Database:         TP\\PP\\ppmgmtdm.nsf")
    COMMENT(COMMENT_PARAGRAPH, "Filename:         i_docgui.doc")
    NOTE("2")

    COMMENT(COMMENT_PARAGRAPH, "ISI General Information")
    COMMENT(COMMENT_PARAGRAPH, "Document number:  DSY02801-EN")
    COMMENT(COMMENT_PARAGRAPH, "Docman:           PP DocMan")
    COMMENT(COMMENT_PARAGRAPH, "Server:           eslns42/SRV/Nokia")
    COMMENT(COMMENT_PARAGRAPH, "Database:         TP\\PP\\ppmgmtdm.nsf")
    COMMENT(COMMENT_PARAGRAPH, "Filename:         i_geninf.doc")
    NOTE("3")

    COMMENT(COMMENT_PARAGRAPH, "ISI Common Message Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Database: ou1gif")
    COMMENT(COMMENT_PARAGRAPH, "Project:  GIF_SPECS-ou1gif")
    COMMENT(COMMENT_PARAGRAPH, "Directory path: GIF_SPECS/CoreSW/"
            "coresw_public_spec")
    COMMENT(COMMENT_PARAGRAPH, "Filename: i_comm_m.html")
    NOTE("4")

    /* --------------------------------------------------------------------- */
    /* Constants                                                             */
    /* --------------------------------------------------------------------- */
    CONSTANT(MSIM_SMS_CB_DATA_DOWNLOAD_AVAIL, 0x73)
    CONSTANT(MSIM_SERV_SIM_REMOVED_CS, 0x35)
    CONSTANT(MSIM_MAX_NBR_OF_CBMIDS, 5)
    CONSTANT_VER(MSIM_ONE_EMRG_CALL_CODE_LEN, 3, "002.000", "")
    /* Following constant is required since otherwise Autogen indicates in HTML
     * file that this constant is valid only until version 002.000 when
     * MSIM_IMSI sequence was removed although it is still used in
     * MSIM_CS_READ_RESP message MSIM_SB_IMSI sub-block. Constant is generated
     * to header file regardless whether this exist here or not. */
    CONSTANT(MSIM_IMSI_LEN, 8)
    CONSTANT_VER(MSIM_INVALID_KEY_SET_IDENTIFIER, 7, "005.000", "")

    /* --------------------------------------------------------------------- */
    /* Status                                                                */
    /* --------------------------------------------------------------------- */
    /* This table contains all status values */
    CONST_TBL_BEGIN(MSIM_SERV_MAIN_STATUS_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(MSIM_STA_OK,                         0x01,
            "Result is OK")
        CONST_TBL_ENTRY(MSIM_STA_NOT_OK,                     0x02, "")
        CONST_TBL_ENTRY(MSIM_STA_NOT_AVAIL,                  0x03, "")
        CONST_TBL_ENTRY(MSIM_STA_INIT_OK,                    0x04, "")
        CONST_TBL_ENTRY(MSIM_STA_INIT_NOT_OK,                0x05, "")
        CONST_TBL_ENTRY(MSIM_STA_INIT_OK_CS,                 0x06, "")
        CONST_TBL_ENTRY(MSIM_STA_INIT_NOT_OK_CS,             0x07,
            "Error occured during initialisation.")
        CONST_TBL_ENTRY(MSIM_STA_SB_NOT_OK,                  0x08, "")
        CONST_TBL_ENTRY(MSIM_STA_UPDATE_IMPOSSIBLE,          0x09, "")
        CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE,         0x0A,
            "Information is not available for example due to loss of contact "
            "to the smart card")
        CONST_TBL_ENTRY(MSIM_STA_PIN_VERIFY_OK,              0x10, "")
        CONST_TBL_ENTRY(MSIM_STA_PIN_REQUIRED,               0x11, "")
        CONST_TBL_ENTRY(MSIM_STA_PIN_VERIFY_REQUIRED,        0x12,
            "The requested PIN needs to be verified.")
        CONST_TBL_ENTRY(MSIM_STA_SIM_BLOCKED,                0x13,
            "Access to files protected by PIN is blocked and PUK is required "
            "for access.")
        CONST_TBL_ENTRY(MSIM_STA_WRONG_OLD_PIN,              0x14, "")
        CONST_TBL_ENTRY(MSIM_STA_NO_PIN,                     0x15,
            "The requested PIN is not supported by the application.")
        CONST_TBL_ENTRY(MSIM_STA_PIN_BLOCKED,                0x16,
            "PIN has been blocked and PUK is required.")
        CONST_TBL_ENTRY(MSIM_STA_PIN_PERMANENTLY_BLOCKED,    0x17,
            "PIN has been permanently blocked.")
        CONST_TBL_ENTRY(MSIM_STA_PIN_RIGHTS_LOST_IND_CS,     0x18,
            "PIN code is incorrect or it has not been entered.")
        CONST_TBL_ENTRY(MSIM_STA_PIN_RIGHTS_GRANTED_IND_CS,  0x19,
            "PIN code has been entered correctly.")
        CONST_TBL_ENTRY(MSIM_STA_PIN_DISABLED,               0x1A,
            "PIN code is disabled.")
        CONST_TBL_ENTRY(MSIM_STA_FDN_STATUS_ERROR,           0x20, "")
        CONST_TBL_ENTRY(MSIM_STA_FDN_CHECK_PASSED,           0x21,
            "Number(s) is found from FDN list.")
        CONST_TBL_ENTRY(MSIM_STA_FDN_CHECK_FAILED,           0x22,
            "Number(s) is not found from FDN list.")
        CONST_TBL_ENTRY(MSIM_STA_FDN_CHECK_DISABLED,         0x23,
            "FDN feature is disabled on [U]SIM.")
        CONST_TBL_ENTRY(MSIM_STA_FDN_CHECK_NO_FDN_SIM,       0x24,
            "FDN feature is not present on [U]SIM.")
        CONST_TBL_ENTRY(MSIM_STA_ACL_ENABLED,                0x30,
            "ACL feature is enabled in service table, EFust")
        CONST_TBL_ENTRY(MSIM_STA_ACL_DISABLED,               0x31,
           "ACL feature is disabled in service table, EFust")
        CONST_TBL_ENTRY(MSIM_STA_APN_CHECK_PASSED,           0x32,
            "The APN is on the EFacl file.")
        CONST_TBL_ENTRY(MSIM_STA_APN_CHECK_FAILED,           0x33,
            "The APN is not on the EFacl file.")
        CONST_TBL_ENTRY(MSIM_STA_ACL_NOT_AVAILABLE,          0x34,
            "ACL feature is not activated on USIM. This means that the smart "
            "card does not support ACL.")
        CONST_TBL_ENTRY(MSIM_STA_SIM_REMOVED,                0x40, "")
        CONST_TBL_ENTRY(MSIM_STA_SIM_DISCONNECTED,           0x41,
            "[U]ICC card has been disconnected or removed.")
        CONST_TBL_ENTRY(MSIM_STA_CONNECTED_INDICATION_CS,    0x42,
           "[U]ICC card has been connected.")
        CONST_TBL_ENTRY(MSIM_STA_SIM_NOT_INITIALISED,        0x43, "")
        CONST_TBL_ENTRY(MSIM_STA_ICC_EQUAL,                  0x80, "")
        CONST_TBL_ENTRY(MSIM_STA_ICC_NOT_EQUAL,              0x81, "")
        CONST_TBL_ENTRY(MSIM_STA_PN_LIST_ENABLE_OK,          0x85, "")
        CONST_TBL_ENTRY(MSIM_STA_PN_LIST_DISABLE_OK,         0x86, "")
        CONST_TBL_ENTRY(MSIM_STA_IMSI_EQUAL,                 0x8A, "")
        CONST_TBL_ENTRY(MSIM_STA_IMSI_NOT_EQUAL,             0x8B, "")
        CONST_TBL_ENTRY(MSIM_STA_FDN_ENABLED,                0x90,
            "FDN feature is enabled.")
        CONST_TBL_ENTRY(MSIM_STA_FDN_DISABLED,               0x91,
            "FDN feature is disabled.")
        CONST_TBL_ENTRY(MSIM_STA_SRES_ERROR,                 0x95, "")
        CONST_TBL_ENTRY(MSIM_STA_COMMUNICATION_ERROR,        0xA0, "")
        CONST_TBL_ENTRY(MSIM_STA_NAME_TOO_LONG,              0xA1, "")
        CONST_TBL_ENTRY(MSIM_STA_NUMBER_TOO_LONG,            0xA2, "")
        CONST_TBL_ENTRY(MSIM_STA_ILLEGAL_NUMBER,             0xA3, "")
        CONST_TBL_ENTRY(MSIM_STA_INVALID_LOCATION,           0xA4, "")
        CONST_TBL_ENTRY(MSIM_STA_NO_MATCH,                   0xA5, "")
        CONST_TBL_ENTRY(MSIM_STA_NO_FREE_LOCATIONS,          0xA6, "")
        CONST_TBL_ENTRY(MSIM_STA_INVALID_FILE,               0xA7, "")
        CONST_TBL_ENTRY(MSIM_STA_SERVICE_NOT_AVAIL,          0xA8, "")
        CONST_TBL_ENTRY(MSIM_STA_FILE_NOT_AVAILABLE,         0xA9, "")
        CONST_TBL_ENTRY(MSIM_STA_ILLEGAL_LENGTH,             0xAA,
           "The length of data has exceeded the maximum data space returned in"
           " MSIM_GPRS_RESP(MSIM_ACL_READ_REQ)")
        CONST_TBL_ENTRY_VER(MSIM_STA_LOCK_ACTIVE,            0xAB, "",
            "002.000")
        CONST_TBL_ENTRY_VER(MSIM_STA_SIMLOCK_ACTIVE,         0xB0, "003.000",
            "")
        CONST_TBL_ENTRY_VER(MSIM_STA_SIMLOCK_INACTIVE,       0xB1, "003.000",
            "")
        CONST_TBL_ENTRY_VER(MSIM_STA_INIT_LIMITED_ACCESS,    0xB2, "005.001",
            "")
        CONST_TBL_ENTRY(MSIM_STA_NOSERVICE,                  0xF0, "")
        CONST_TBL_ENTRY(MSIM_STA_NOTREADY,                   0xF1, "")
        CONST_TBL_ENTRY(MSIM_STA_ERROR,                      0xF2, "")
    CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* Status derivatives                                                    */
    /* --------------------------------------------------------------------- */
    DER_CONST_TBL_BEGIN(MSIM_AUTHENTIFICATION_STATUS,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_SB_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_UPDATE_IMPOSSIBLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_CS_WRITE_STATUS, MSIM_SERV_MAIN_STATUS_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_SB_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_CS_READ_RESP_STATUS, MSIM_SERV_MAIN_STATUS_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_SB_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_SIM_REMOVED)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_STATUS_STATUS, MSIM_SERV_MAIN_STATUS_TABLE, "",
        "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_SIM_DISCONNECTED)
        DER_CONST_TBL_ENTRY(MSIM_STA_SIM_NOT_INITIALISED)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_APP_SELECTION_STATUS,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_READ_TABLE_STATUS_TABLE,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY_VER(MSIM_STA_SERVICE_NOT_AVAIL, "003.000", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_READ_STATUS, MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_IMSI_STATUS, MSIM_SERV_MAIN_STATUS_TABLE,
        "", "002.000")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SMS_STATUS, MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_UPDATE_IMPOSSIBLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SMS_STORAGE_STATUS, MSIM_SERV_MAIN_STATUS_TABLE, "005.002", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(MSIM_STA_NO_FREE_LOCATIONS)
        DER_CONST_TBL_ENTRY(MSIM_STA_SERVICE_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END


    DER_CONST_TBL_BEGIN(MSIM_NO_STATUS_FROM_SUBSYSTEM,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_VOICE_MSG_STATUS, MSIM_SERV_MAIN_STATUS_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_FDN_CHECK_STATUS, MSIM_SERV_MAIN_STATUS_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_CHECK_PASSED)
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_CHECK_FAILED)
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_CHECK_DISABLED)
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_STATUS_ERROR)
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_CHECK_NO_FDN_SIM)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_READ_FIELD_ICC_STATUS,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_IND_STATUS_TABLE, MSIM_SERV_MAIN_STATUS_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_PIN_VERIFY_REQUIRED)
        DER_CONST_TBL_ENTRY(MSIM_STA_SIM_BLOCKED)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_PIN_PERMANENTLY_BLOCKED)
        DER_CONST_TBL_ENTRY(MSIM_STA_SIM_DISCONNECTED)
        DER_CONST_TBL_ENTRY(MSIM_STA_COMMUNICATION_ERROR)
        DER_CONST_TBL_ENTRY(MSIM_STA_IMSI_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_IMSI_NOT_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_ICC_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_ICC_NOT_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_PN_LIST_ENABLE_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_PN_LIST_DISABLE_OK)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_ST_ALL_SERVICES_STATUS_TABLE,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_SIM_DISCONNECTED)
        DER_CONST_TBL_ENTRY(MSIM_STA_COMMUNICATION_ERROR)
        DER_CONST_TBL_ENTRY(MSIM_STA_IMSI_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_IMSI_NOT_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_ICC_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_ICC_NOT_EQUAL)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_ST_FDN_STATUS_TABLE, MSIM_SERV_MAIN_STATUS_TABLE,
        "", "003.000")
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_PN_LIST_ENABLE_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_PN_LIST_DISABLE_OK)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_ST_INFO_STATUS_TABLE, MSIM_SERV_MAIN_STATUS_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_NOT_OK)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SERVER_READY_IND_STATUS_TABLE,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_OK)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_CS_IND_STATUS_TABLE, MSIM_SERV_MAIN_STATUS_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_OK_CS)
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_NOT_OK_CS)
        DER_CONST_TBL_ENTRY(MSIM_STA_PIN_RIGHTS_LOST_IND_CS)
        DER_CONST_TBL_ENTRY(MSIM_STA_PIN_RIGHTS_GRANTED_IND_CS)
        DER_CONST_TBL_ENTRY(MSIM_STA_CONNECTED_INDICATION_CS)
        DER_CONST_TBL_ENTRY_VER(MSIM_STA_SIMLOCK_ACTIVE, "003.000", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_STA_SIMLOCK_INACTIVE, "003.000", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_STA_INIT_LIMITED_ACCESS, "005.001", "")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_IMSI_ICC_EQUAL_STATUS,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_ICC_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_ICC_NOT_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_FDN_STATUS, MSIM_SERV_MAIN_STATUS_TABLE, "",
        "003.000")
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_ENABLED)
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_DISABLED)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_IND_PREF_LANG_STATUS_TABLE,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_ST_REFRESH_REGISTER_STATUS,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_ST_REFRESH_UNREGISTER_STATUS,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_ST_REFRESH_PERMISSION_STATUS,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_ST_REFRESH_RESULT_STATUS,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_ST_ACL_STATUS_STATUS_TABLE,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_ACL_ENABLED)
        DER_CONST_TBL_ENTRY(MSIM_STA_ACL_DISABLED)
        DER_CONST_TBL_ENTRY(MSIM_STA_ACL_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY_VER(MSIM_STA_NOTREADY, "003.000", "")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_ST_ACL_CHECK_APN_STATUS_TABLE,
        MSIM_SERV_MAIN_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_APN_CHECK_PASSED)
        DER_CONST_TBL_ENTRY(MSIM_STA_APN_CHECK_FAILED)
        DER_CONST_TBL_ENTRY(MSIM_STA_ACL_DISABLED)
        DER_CONST_TBL_ENTRY(MSIM_STA_ACL_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY_VER(MSIM_STA_FILE_NOT_AVAILABLE, "003.000", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_STA_NOTREADY, "003.000", "")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_ACL_IND_STATUS_TABLE, MSIM_SERV_MAIN_STATUS_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_STA_ACL_ENABLED)
        DER_CONST_TBL_ENTRY(MSIM_STA_ACL_DISABLED)
        DER_CONST_TBL_ENTRY(MSIM_STA_ACL_NOT_AVAILABLE)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_PB_STATUS_TABLE, MSIM_SERV_MAIN_STATUS_TABLE,
        "", "003.000")
        DER_CONST_TBL_ENTRY(MSIM_STA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(MSIM_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_PIN_VERIFY_REQUIRED)
        DER_CONST_TBL_ENTRY(MSIM_STA_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(MSIM_STA_PIN_BLOCKED)
        DER_CONST_TBL_ENTRY(MSIM_STA_PIN_PERMANENTLY_BLOCKED)
        DER_CONST_TBL_ENTRY(MSIM_STA_SIM_DISCONNECTED)
        DER_CONST_TBL_ENTRY_VER(MSIM_STA_LOCK_ACTIVE, "", "002.000")
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_WRONG_OLD_PIN)
        DER_CONST_TBL_ENTRY(MSIM_STA_COMMUNICATION_ERROR)
        DER_CONST_TBL_ENTRY(MSIM_STA_UPDATE_IMPOSSIBLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NO_FREE_LOCATIONS)
        DER_CONST_TBL_ENTRY(MSIM_STA_NO_MATCH)
        DER_CONST_TBL_ENTRY(MSIM_STA_ILLEGAL_NUMBER)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_PN_LIST_ENABLE_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_PN_LIST_DISABLE_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_NO_PIN)
        DER_CONST_TBL_ENTRY(MSIM_STA_PIN_VERIFY_OK)
        DER_CONST_TBL_ENTRY(MSIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(MSIM_STA_IMSI_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_IMSI_NOT_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(MSIM_STA_NAME_TOO_LONG)
        DER_CONST_TBL_ENTRY(MSIM_STA_SRES_ERROR)
        DER_CONST_TBL_ENTRY(MSIM_STA_SIM_REMOVED)
        DER_CONST_TBL_ENTRY(MSIM_STA_CONNECTED_INDICATION_CS)
        DER_CONST_TBL_ENTRY(MSIM_STA_PIN_RIGHTS_LOST_IND_CS)
        DER_CONST_TBL_ENTRY(MSIM_STA_PIN_RIGHTS_GRANTED_IND_CS)
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_OK_CS)
        DER_CONST_TBL_ENTRY(MSIM_STA_INIT_NOT_OK_CS)
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_ENABLED)
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_DISABLED)
        DER_CONST_TBL_ENTRY(MSIM_STA_INVALID_FILE)
        DER_CONST_TBL_ENTRY(MSIM_STA_ICC_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_ICC_NOT_EQUAL)
        DER_CONST_TBL_ENTRY(MSIM_STA_SIM_NOT_INITIALISED)
        DER_CONST_TBL_ENTRY(MSIM_STA_ILLEGAL_LENGTH)
        DER_CONST_TBL_ENTRY(MSIM_STA_NUMBER_TOO_LONG)
        DER_CONST_TBL_ENTRY(MSIM_STA_SERVICE_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_CHECK_PASSED)
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_CHECK_FAILED)
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_CHECK_DISABLED)
        DER_CONST_TBL_ENTRY(MSIM_STA_FDN_CHECK_NO_FDN_SIM)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(MSIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(MSIM_STA_ERROR)
        DER_CONST_TBL_ENTRY(MSIM_STA_FILE_NOT_AVAILABLE)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SIMLOCK_STATUS_TABLE, MSIM_SERV_MAIN_STATUS_TABLE,
        "003.000", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_STA_SIMLOCK_ACTIVE, "003.000", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_STA_SIMLOCK_INACTIVE, "003.000", "")
    DER_CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* MSIM_MISC_SERVICE_TYPE and its derivatives                            */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    CONST_TBL_BEGIN(MSIM_MISC_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(MSIM_ST_PIN,                          1,
            "Service Type for PIN1")
        CONST_TBL_ENTRY(MSIM_ST_ALL_SERVICES,                 2, "")
        COMMENT(COMMENT_TEXT, "Fixed Dialling Number")
        CONST_TBL_ENTRY_VER(MSIM_ST_FDN,                      3,
            "", "003.000")
        CONST_TBL_ENTRY(MSIM_ST_INFO,                         4,
            "SIM RAM Information Storage")
        CONST_TBL_ENTRY(MSIM_ST_READ_SMS_PARAM_CNT,           5,
            "The number of SMS parameter records on the card.")
        CONST_TBL_ENTRY(MSIM_ST_READ_DYN_FLAGS,               6, "")
        CONST_TBL_ENTRY(MSIM_ST_WRITE_DYN_FLAGS,              7, "")
        CONST_TBL_ENTRY(MSIM_ST_EMERGENCY_CODES,              8, "")
        CONST_TBL_ENTRY(MSIM_ST_READ_PARAMETER,               9, "")
        CONST_TBL_ENTRY(MSIM_ST_READ_STATUS,                 10, "")
        CONST_TBL_ENTRY(MSIM_ST_WRITE_STATUS,                11, "")
        CONST_TBL_ENTRY(MSIM_ST_UPDATE_PARAMETER,            12, "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_READ_SERVICE_TYPE, MSIM_MISC_SERVICE_TYPE_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_ST_READ_SMS_PARAM_CNT)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_IND_ST_TABLE, MSIM_MISC_SERVICE_TYPE_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_ST_ALL_SERVICES )
        DER_CONST_TBL_ENTRY(MSIM_ST_EMERGENCY_CODES)
        DER_CONST_TBL_ENTRY_VER(MSIM_ST_FDN, "", "003.000")
        DER_CONST_TBL_ENTRY(MSIM_ST_INFO)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SERVER_READY_IND_ST_TABLE,
        MSIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_ST_ALL_SERVICES)
    DER_CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* MSIM_REFRESH_SERVICE_TYPE_TABLE and its derivatives                   */
    /* --------------------------------------------------------------------- */
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_REFRESH_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(MSIM_ST_REFRESH_REQUESTED,            7, "")
        CONST_TBL_ENTRY(MSIM_ST_REFRESH_NOW,                  8, "")
        CONST_TBL_ENTRY(MSIM_ST_REFRESH_CANCELLED,            9, "")
        CONST_TBL_ENTRY_VER(MSIM_ST_REFRESH_STARTING,         10,"",
            "003.000")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* MSIM_ST_TABLE and its derivatives                                     */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_ST_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(MSIM_ST_GPRS_CALL_CONTROL_AVAIL,          1, "")
        CONST_TBL_ENTRY(MSIM_ST_SMSCB_DATA_DOWNLOAD_AVAIL,        2, "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_READ_TABLE_SERVICE_TYPE, MSIM_ST_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_ST_SMSCB_DATA_DOWNLOAD_AVAIL)
        DER_CONST_TBL_ENTRY(MSIM_ST_GPRS_CALL_CONTROL_AVAIL)
    DER_CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* MSIM_LINE_TYPE and its derivatives                                    */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_LINE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(MSIM_LT_PRIMARY_LINE,     0, "")
        CONST_TBL_ENTRY(MSIM_LT_ALTERNATE_LINE,   1, "")
        CONST_TBL_ENTRY(MSIM_LT_ALL_LINES,        2, "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SINGLE_LINE, MSIM_LINE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_LT_PRIMARY_LINE)
        DER_CONST_TBL_ENTRY(MSIM_LT_ALTERNATE_LINE)
    DER_CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* MSIM_STATE and its derivatives                                        */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_STATE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(MSIM_STATE_SIM_INIT_WAIT,           1, "")
        CONST_TBL_ENTRY(MSIM_STATE_SIM_PIN_VERIFY_REQUIRED, 2, "")
        CONST_TBL_ENTRY(MSIM_STATE_SIM_PERMANENTLY_BLOCKED, 3, "")
        CONST_TBL_ENTRY(MSIM_STATE_SIM_REMOVED,             4, "")
        CONST_TBL_ENTRY(MSIM_STATE_SIM_REJECTED,            5, "")
        CONST_TBL_ENTRY(MSIM_STATE_SIM_BLOCKED,             6, "")
        CONST_TBL_ENTRY(MSIM_STATE_SIM_OK,                  7, "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SERVER_READY_IND_STATE_TABLE, MSIM_STATE_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_STATE_SIM_OK)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_CS_IND_STATE_TABLE, MSIM_STATE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_STATE_SIM_INIT_WAIT)
        DER_CONST_TBL_ENTRY(MSIM_STATE_SIM_PIN_VERIFY_REQUIRED)
        DER_CONST_TBL_ENTRY(MSIM_STATE_SIM_PERMANENTLY_BLOCKED)
        DER_CONST_TBL_ENTRY(MSIM_STATE_SIM_REMOVED)
        DER_CONST_TBL_ENTRY(MSIM_STATE_SIM_REJECTED)
        DER_CONST_TBL_ENTRY(MSIM_STATE_SIM_BLOCKED)
        DER_CONST_TBL_ENTRY(MSIM_STATE_SIM_OK)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_IND_PREF_LANG_STATE_TABLE, MSIM_STATE_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_STATE_SIM_INIT_WAIT)
    DER_CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* MSIM_CAUSES and its derivatives                                       */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_CAUSES_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(MSIM_NO_CAUSE,                       1,       "")
        CONST_TBL_ENTRY(MSIM_CAUSE_3V5V_CARD,                2,       "")
        CONST_TBL_ENTRY(MSIM_CAUSE_5V_CARD,                  3,       "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SERVER_READY_IND_CAUSE_TABLE, MSIM_CAUSES_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_NO_CAUSE)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_CS_IND_CAUSE_TABLE, MSIM_CAUSES_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_NO_CAUSE)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_IND_PREF_LANG_CAUSE_TABLE, MSIM_CAUSES_TABLE, "",
        "")
        DER_CONST_TBL_ENTRY(MSIM_NO_CAUSE)
    DER_CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* Subblock status                                                       */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* MSIM_SB_STA and its derivatives                                       */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_SB_STA_TABLE,8, BE, "", "")
        CONST_TBL_ENTRY(MSIM_SB_STA_OK,                  1, "")
        CONST_TBL_ENTRY(MSIM_SB_STA_NOT_OK,              2, "")
        CONST_TBL_ENTRY(MSIM_SB_STA_FILE_NOT_AVAIL,      3, "")
        CONST_TBL_ENTRY(MSIM_SB_STA_3G_GSM_NOT_SUPPORTED,5, "")
        CONST_TBL_ENTRY(MSIM_SB_STA_SYNCH_FAIL,          6, "")
        CONST_TBL_ENTRY(MSIM_SB_STA_MAC_FAIL,            7, "")
        CONST_TBL_ENTRY(MSIM_SB_STA_PS_NOT_SUPPORTED,    8, "")
        CONST_TBL_ENTRY_VER(MSIM_SB_STA_SERVICE_NOT_AVAIL,   9, "003.001",
            "")
        CONST_TBL_ENTRY_VER(MSIM_SB_STA_LOCATION_NOT_FOUND, 10, "005.002",
            "")
        CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_PARAMS_STATUS, MSIM_SB_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_3G_GSM_NOT_SUPPORTED)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_PS_NOT_SUPPORTED)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_STA_STATUS, MSIM_SB_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_FILE_NOT_AVAIL)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_CIPHERING_KEY_SNR_STATUS, MSIM_SB_STA_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_FILE_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_3G_GSM_NOT_SUPPORTED)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_UMTS_FAIL_PARAMS_STATUS, MSIM_SB_STA_TABLE, "",
        "")
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_MAC_FAIL)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_SYNCH_FAIL)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_PHONE_STATUS, MSIM_SB_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_NOT_OK)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_UST_STATUS_TABLE, MSIM_SB_STA_TABLE, "003.001", "")
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_SERVICE_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_FILE_NOT_AVAIL)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_SMS_QUERY_STATUS, MSIM_SB_STA_TABLE, "005.002", "")
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_LOCATION_NOT_FOUND)
        DER_CONST_TBL_ENTRY(MSIM_SB_STA_FILE_NOT_AVAIL)
    DER_CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* MSIM_SMS_TYPE_OF_NUMBER                                               */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_SMS_TYPE_OF_NUMBER, 8, BE, "003.000", "")
        CONST_TBL_ENTRY(MSIM_SMS_DESTINATION_ADDRESS_NUMERIC, 0x00,
        "Numeric destination address")
        CONST_TBL_ENTRY(MSIM_SMS_DESTINATION_ADDRESS_ALPHANUMERIC, 0x01,
        "Alphanumeric destination address")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* MSIM_CARD_TYPE and its derivatives                                    */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_CARD_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(MSIM_CT_NORMAL_SIM,                      0x00, "")
        CONST_TBL_ENTRY(MSIM_CT_NORMAL_SIM_SPE_FACILITY,         0x01, "")
        CONST_TBL_ENTRY(MSIM_CT_MAINTENANCE,                     0x02, "")
        CONST_TBL_ENTRY(MSIM_CT_TEST_SIM,                        0x04, "")
        CONST_TBL_ENTRY(MSIM_CT_TYPE_APPROVAL_SIM,               0x80, "")
        CONST_TBL_ENTRY(MSIM_CT_TYPE_APPROVAL_SIM_SPE_FACILITY,  0x81, "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_CARD_TYPE_TABLE, MSIM_CARD_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_CT_NORMAL_SIM)
        DER_CONST_TBL_ENTRY(MSIM_CT_TYPE_APPROVAL_SIM)
        DER_CONST_TBL_ENTRY(MSIM_CT_TEST_SIM)
        DER_CONST_TBL_ENTRY(MSIM_CT_NORMAL_SIM_SPE_FACILITY)
        DER_CONST_TBL_ENTRY(MSIM_CT_MAINTENANCE)
    DER_CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* MSIM_CARD_GENERATION and its derivatives                              */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
        CONST_TBL_BEGIN(MSIM_CARD_GENERATION_TABLE, 8, BE, "003.000", "")
        CONST_TBL_ENTRY(MSIM_SIM_CARD,                     2, "")
        CONST_TBL_ENTRY(MSIM_USIM_CARD,                    3, "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_CARD_GENERATION_TABLE, MSIM_CARD_GENERATION_TABLE,
        "003.000", "")
        DER_CONST_TBL_ENTRY(MSIM_SIM_CARD)
        DER_CONST_TBL_ENTRY(MSIM_USIM_CARD)
    DER_CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* MSIM_PLMN_OPERATIONS and its derivatives                              */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_PLMN_OPERATIONS_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(MSIM_PLMN_ADD,                      42, "")
        CONST_TBL_ENTRY(MSIM_PLMN_REMOVE,                   87, "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_FORBIDDEN_PLMNS_FPLMN,
        MSIM_PLMN_OPERATIONS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_PLMN_ADD)
        DER_CONST_TBL_ENTRY(MSIM_PLMN_REMOVE)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_USER_PLMN_UPLMN, MSIM_PLMN_OPERATIONS_TABLE,
        "", "")
        DER_CONST_TBL_ENTRY(MSIM_PLMN_ADD)
        DER_CONST_TBL_ENTRY(MSIM_PLMN_REMOVE)
    DER_CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* MSIM_REFRESH_FILE_ID and its derivatives                              */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_REFRESH_FILE_ID_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(MSIM_REFRESH_SERVICE_TABLE,                          1,
            "Refresh Service Table")
        CONST_TBL_ENTRY(MSIM_REFRESH_IMSI,                                   2,
            "Refresh IMSI (EFimsi)")
        CONST_TBL_ENTRY(MSIM_REFRESH_FORBIDDEN_PLMNS,                        3,
            "Refresh forbidden PLMNs (EFfplmn)")
        CONST_TBL_ENTRY(MSIM_REFRESH_LOCATION_INFORMATION,                   4,
            "Refresh location information (EFloci)")
        CONST_TBL_ENTRY(MSIM_REFRESH_CIPHERING_KEY_KC,                       5,
            "Refresh ciphering key Kc (EFkc)")
        CONST_TBL_ENTRY(MSIM_REFRESH_PLMN_SELECTOR,                          6,
            "Refresh PLMN selector (EFplmnsel)")
        CONST_TBL_ENTRY(MSIM_REFRESH_ACCESS_CONTROL_CLASS,                   7,
            "Refresh Access Control Class (EFacc)")
        CONST_TBL_ENTRY(MSIM_REFRESH_HPLMN_SEARCH_PERIOD,                    8,
            "HPLMN search period (EFhplmn)")
        CONST_TBL_ENTRY(MSIM_REFRESH_PHASE_IDENTIFICATION,                   9,
            "")
        CONST_TBL_ENTRY(MSIM_REFRESH_EMERGENCY_CALL_CODES,                  10,
            "Refresh Emergency Call Codes (EFecc)")
        CONST_TBL_ENTRY(MSIM_REFRESH_CELL_BROADCAST_MESSSAGE_ID_DATA_DOWNLOAD,
          11, "")
        CONST_TBL_ENTRY(MSIM_REFRESH_GPRS_CIPHERING_KEY_KCGPRS,             12,
            "Refresh GPRS ciphering key (EFkcgprs)")
        CONST_TBL_ENTRY(MSIM_REFRESH_OPERATOR_PLMN_LIST,                    13,
            "Refresh operator PLMN list (EFopl)")
        CONST_TBL_ENTRY(MSIM_REFRESH_PLMN_NETWORK_NAME,                     14,
            "Refresh PLMN Network Name (EFpnn)")
        CONST_TBL_ENTRY(MSIM_REFRESH_CUSTOMER_SERVICE_PROFILE,              15,
            "")
        CONST_TBL_ENTRY(MSIM_REFRESH_CPHS_INFO,                             16,
            "")
        CONST_TBL_ENTRY(MSIM_REFRESH_SHORT_MESSAGE_SERVICE_STATUS,          17,
            "Refresh SMS Status (EFsmss)")
        CONST_TBL_ENTRY(MSIM_REFRESH_CSP_LINE_2,                            18,
            "")
        CONST_TBL_ENTRY(MSIM_REFRESH_USER_CONTROLLED_PLMN_SELECTOR_ACCESS_TECH,
          19, "Refresh User Controlled PLMN selector with Access Technology "
          "(EFplnmwact)")
        CONST_TBL_ENTRY(
            MSIM_REFRESH_OPERATOR_CONTROLLED_PLMN_SELECTOR_ACCESS_TECH,     20,
            "Refresh Operator Controlled PLMN selector withAccess Technology "
            "(EFoplnmwact)")
        CONST_TBL_ENTRY(MSIM_REFRESH_HPLMN_SELECTOR_ACCESS_TECH,            21,
            "Refresh HPLNM selector with Access Technology (EFhplnmwact)")
        CONST_TBL_ENTRY(MSIM_REFRESH_CIPHERING_INTEGRITY_KEYS,              22,
            "Refresh Ciphering and Integrity Keys (EFkeys)")
        CONST_TBL_ENTRY(
            MSIM_REFRESH_CIPHERING_INTEGRITY_KEYS_PACKET_SWITCHED_DOMAIN,   23,
            "Refresh Ciphering Keys and integrity keys for Packet Switched "
            "domain (EFkeysps)")
        CONST_TBL_ENTRY(
            MSIM_REFRESH_INITIALISATION_VALUES_FOR_HYPERFRAME_NUMBER,       24,
            "Refresh Inittialization values for Hypeframe number "
            "(EFstart-hpn)")
        CONST_TBL_ENTRY(MSIM_REFRESH_MAXIMUM_VALUE_OF_START,                25,
            "Refresh Maximum value of START (EFthreshold)")
        CONST_TBL_ENTRY(MSIM_REFRESH_PACKET_SWITCHED_LOCATION_INFORMATION,  26,
            "Refresh Packet Switched Location Information (EFpsloci)")
        CONST_TBL_ENTRY(MSIM_REFRESH_APPLICATION_DIRECTORY,                 27,
            "")
        CONST_TBL_ENTRY(MSIM_REFRESH_UNKNOWN_FILES,                         28,
            "")
        CONST_TBL_ENTRY(MSIM_REFRESH_ACTING_HPLMN,                          29,
            "")
        CONST_TBL_ENTRY(MSIM_REFRESH_DYNAMIC_FLAGS1,                        30,
            "")
        CONST_TBL_ENTRY(MSIM_REFRESH_EQUIVALENT_HPLMNS,                     31,
            "")
        CONST_TBL_ENTRY_VER(MSIM_REFRESH_RAT_MODE,                          32,
            "004.000","")
        CONST_TBL_ENTRY_VER(MSIM_REFRESH_EHPLMN_PRESENTATION_INDICATION,    33,
            "005.000", "")
        CONST_TBL_ENTRY_VER(MSIM_REFRESH_EPS_LOCATION_INFORMATION,          34,
            "005.000", "")
        CONST_TBL_ENTRY_VER(MSIM_REFRESH_EPS_NAS_SECURITY_CONTEXT,          35,
            "005.000", "")

        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME,
            "MSIM_REFRESH_LAST_FILE_ID")

        CONST_TBL_ENTRY_VER(MSIM_REFRESH_LAST_RPLMN_SELECTION_INDICATION,   36,
            "005.000", "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_REFERSH_FILE_IDS, MSIM_REFRESH_FILE_ID_TABLE, "",
        "")
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_SERVICE_TABLE)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_IMSI)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_FORBIDDEN_PLMNS)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_LOCATION_INFORMATION)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_CIPHERING_KEY_KC)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_PLMN_SELECTOR)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_ACCESS_CONTROL_CLASS)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_HPLMN_SEARCH_PERIOD)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_PHASE_IDENTIFICATION)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_EMERGENCY_CALL_CODES)
        DER_CONST_TBL_ENTRY(
            MSIM_REFRESH_CELL_BROADCAST_MESSSAGE_ID_DATA_DOWNLOAD)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_GPRS_CIPHERING_KEY_KCGPRS)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_OPERATOR_PLMN_LIST)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_PLMN_NETWORK_NAME)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_CUSTOMER_SERVICE_PROFILE)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_CPHS_INFO)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_SHORT_MESSAGE_SERVICE_STATUS)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_CSP_LINE_2)
        DER_CONST_TBL_ENTRY(
            MSIM_REFRESH_USER_CONTROLLED_PLMN_SELECTOR_ACCESS_TECH)
        DER_CONST_TBL_ENTRY(
            MSIM_REFRESH_OPERATOR_CONTROLLED_PLMN_SELECTOR_ACCESS_TECH)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_HPLMN_SELECTOR_ACCESS_TECH)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_CIPHERING_INTEGRITY_KEYS)
        DER_CONST_TBL_ENTRY(
            MSIM_REFRESH_CIPHERING_INTEGRITY_KEYS_PACKET_SWITCHED_DOMAIN)
        DER_CONST_TBL_ENTRY(
            MSIM_REFRESH_INITIALISATION_VALUES_FOR_HYPERFRAME_NUMBER)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_MAXIMUM_VALUE_OF_START)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_PACKET_SWITCHED_LOCATION_INFORMATION)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_APPLICATION_DIRECTORY)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_UNKNOWN_FILES)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_ACTING_HPLMN)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_EQUIVALENT_HPLMNS)
        DER_CONST_TBL_ENTRY(MSIM_REFRESH_DYNAMIC_FLAGS1)
        DER_CONST_TBL_ENTRY_VER(MSIM_REFRESH_RAT_MODE,"004.000", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_REFRESH_EHPLMN_PRESENTATION_INDICATION,
            "005.000", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_REFRESH_EPS_LOCATION_INFORMATION,"005.000", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_REFRESH_EPS_NAS_SECURITY_CONTEXT,"005.000", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_REFRESH_LAST_RPLMN_SELECTION_INDICATION,
            "005.000", "")
    DER_CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* Service types for MSIM_AUTHENTICATION_REQ / MSIM_AUTHENTICATION_RESP  */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_AUTH_SERVICE_TYPE_TABLE, 8, BE, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_PARAGRAPH, "A GSM authentication will be preformed "
            "either on a 3G card if GSM Security Context is enabled (service "
            "38 in the USIM Service Table) or on a 2G card.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Mandatory sub-blocks in request:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RAND_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_CIPHERING_KEY_SNR")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response - OK 3G (USIM) case:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RES_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_CIPHERING_KEY_SNR")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_CS_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_CS_INTEGRITY_KEY")
        COMMENT(COMMENT_TEXT, "Note1: Kc and CKSN are stored on the card if "
            "the authentication succeeds")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "Note2: The CK and IK values are derived "
            "from Kc by the MSIM server and stored on USIM card together with "
            "an invalid KSI")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "Sub-blocks in response - OK 2G (SIM) case:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RES_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_CIPHERING_KEY_SNR")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_CS_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_CS_INTEGRITY_KEY")
        COMMENT(COMMENT_TEXT, "Note1: Kc and CKSN are stored on the card if "
            "the authentication succeeds")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Note2: The CK and IK values are derived from Kc "
            "by the MSIM server and stored on [U]SIM card together with an "
            "invalid KSI")
        CONST_TBL_ENTRY(MSIM_ST_CS_GSM_CONTEXT,       5, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_PARAGRAPH, "A UMTS authentication will be performed on "
            "a 3G (USIM) card.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Mandatory sub-blocks in request:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RAND_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_AUTN_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_CS_KSI")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response - OK case:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RES_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_CS_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_CS_INTEGRITY_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_CS_KSI")
        COMMENT(COMMENT_PARAGRAPH, "Note: IK and KSI are stored on the [U]SIM "
            "card.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "If GSM Access is enabled (Service No. 27 in the "
            "USIM Service Table) on the USIM card, Kc sub-block is also "
            "included.")
        COMMENT(COMMENT_BULLET, "MSIM_SB_CIPHERING_KEY")
        COMMENT(COMMENT_PARAGRAPH, "Kc is stored on the card together with an "
            "invalid CKSN.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response - Error case:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_AUTN_FAIL_PARAMS")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response when 2G (SIM) card "
            "inserted in ME:")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "If an UMTS authentication is issued on a 2G "
            "card. This should only happen due to an error in the network. The "
            "MSIM server try to respond as if the service type was "
            "SIM_ST_CS_GSM_CONTEXT.")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RES_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_CIPHERING_KEY_SNR")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_CS_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_CS_INTEGRITY_KEY")
        COMMENT(COMMENT_TEXT, "Note1: Kc and CKSN are stored on the card if "
            "the authentication succeeded")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Note2: The CK and IK values are derived from Kc "
            "by the MSIM server and stored on SIM card together with an "
            "invalid KSI")
        CONST_TBL_ENTRY(MSIM_ST_CS_UMTS_CONTEXT,             6, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_PARAGRAPH, "A GSM authentication will be performed "
            "either on a 3G card with GSM Security Context enabled (service 38 "
            "in the USIM Service Table), or on a 2G card with GPRS enabled "
            "(service 38 in the SIM Service Table).")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Required sub-blocks in request:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RAND_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_GPRS_CIPHERING_KEY_SNR")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response - OK 3G case:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RES_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_GPRS_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_GPRS_CIPHERING_KEY_SNR")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_PS_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_PS_INTEGRITY_KEY")
        COMMENT(COMMENT_TEXT, "Note: Kc_gprs and CKSN_gprs are stored on the "
            "card if the authentication was successful.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "Note: The PS_CK and PS_IK values are "
            "derived from Kc_gprs by the MSIM server and kept together with "
            "an invalid PS_KSI.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response - OK 2G case:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RES_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_GPRS_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_GPRS_CIPHERING_KEY_SNR")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_PS_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_PS_INTEGRITY_KEY")
        COMMENT(COMMENT_TEXT, "Note: Kc_gprs and CKSN_gprs are stored on the "
            "card if the authentication was successful.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Note:The PS_CK and PS_IK values are derived "
            "from Kc_gprs by the MSIM server and kept together with an invalid "
            "PS_KSI.")
        CONST_TBL_ENTRY(MSIM_ST_PS_GSM_CONTEXT,              7, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_PARAGRAPH, "A UMTS authentication will be performed on "
            "a 3G card.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Required sub-blocks in request:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RAND_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_AUTN_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_PS_KSI")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response - OK case:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RES_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_PS_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_PS_INTEGRITY_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_PS_KSI")
        COMMENT(COMMENT_PARAGRAPH, "Note: IK and KSI are stored on the [U]SIM "
            "card.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "If GSM Access is enabled (Service No. 27 in the "
            "USIM Service Table) on the USIM card, Kc sub-block is also "
            "included.")
        COMMENT(COMMENT_BULLET, "MSIM_SB_CIPHERING_KEY")
        COMMENT(COMMENT_PARAGRAPH, "Kc is stored on the card together with an "
            "invalid CKSN.")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response - Error case:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_AUTN_FAIL_PARAMS")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response - 2G (SIM) card inserted "
            "in ME:")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "If an UMTS authentication is issued on a 2G "
            "card. This should only happen due to an error in the network. The "
            "MSIM server try to respond as if the service type was "
            "MSIM_ST_CS_GSM_CONTEXT.")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RES_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_CIPHERING_KEY_SNR")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_PS_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_PS_INTEGRITY_KEY")
        COMMENT(COMMENT_TEXT, "Note 1: Kc and CKSN are stored on the card if "
            "the authentication succeded")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Note 2: The CK and IK values are derived from "
            "Kc by the MSIM server and stored on [U]SIM card together with an "
            "invalid KSI")
        CONST_TBL_ENTRY(MSIM_ST_PS_UMTS_CONTEXT,             8, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_PARAGRAPH, "EPS authentication will be performed on "
            "a 3G card.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Required sub-blocks in request:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RAND_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_AUTN_PARAMS")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response - OK case:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_RES_PARAMS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_PS_CIPHERING_KEY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_PS_INTEGRITY_KEY")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response - Error case:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_UMTS_AUTN_FAIL_PARAMS")
        COMMENT(COMMENT_PARAGRAPH, "Note 1: CK and IK are not stored on the [U]SIM "
            "card.")
        COMMENT(COMMENT_PARAGRAPH, "Note 2: Kasme must be calculeted from CK and IK")
        CONST_TBL_ENTRY_VER(MSIM_ST_EPS_CONTEXT,                 9, "005.000","")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for MSIM_SMS_STORAGE_REQ / MSIM_SMS_STORAGE_RESP        */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_SMS_STORAGE_SERVICE_TYPE_TABLE, 8, BE, "005.002", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_PARAGRAPH, "This service type is used for reading "
            "Status and Remainder from a given record in EFsms.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Required sub-blocks in request:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_SMS_INDEX")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response - OK case:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_SMS_STATUS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_SMS_REMAINDER")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "In error case response does not contain any "
            "sub-blocks")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Note: MSIM_SB_SMS_STATUS and "
           "MSIM_SB_SMS_REMAINDER can be read separetaly or simultaneously")
        CONST_TBL_ENTRY_VER(MSIM_ST_READ_MESSAGE,       1, "005.002", "")

        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_PARAGRAPH, "This service type is used for writing "
            "Status and Remainder to first free record in EFsms.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Required sub-blocks in request:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_SMS_STATUS")
        COMMENT(COMMENT_BULLET, "MSIM_SB_SMS_REMAINDER")
        COMMENT(COMMENT_TEXT, "Sub-blocks in response - OK case:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_SMS_INDEX")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "In error case response does not contain any "
            "sub-blocks")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Note: MSIM_SB_SMS_STATUS and "
           "MSIM_SB_SMS_REMAINDER can be written separetaly or simultaneously")

        CONST_TBL_ENTRY_VER(MSIM_ST_WRITE_MESSAGE,      2, "005.002", "")

        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_PARAGRAPH, "This service type is used for erasing "
            "Status and Remainder from a given record in EFsms.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Required sub-blocks in request:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_SMS_INDEX")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Response does not contain any sub-blocks")
        CONST_TBL_ENTRY_VER(MSIM_ST_ERASE_MESSAGE,      3, "005.002", "")

        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_PARAGRAPH, "This service type is used for querying "
            "EFsms file contents.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Sub-blocks in request and response:")
        COMMENT(COMMENT_BULLET, "MSIM_SB_SMS_QUERY")
        COMMENT(COMMENT_BULLET, "MSIM_SB_SMS_LOCATION_COUNT")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Note: MSIM_SB_SMS_QUERY can be included 1-3 times "
            "in request. Query types are specified in MSIM_QUERY_TYPE table.")
        CONST_TBL_ENTRY_VER(MSIM_ST_QUERY_MESSAGE,      4, "005.002", "")
    CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* MSIM_SB_CS_WRITE_RESP_SB_ID_DEFINES and its derivatives               */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_SB_CS_WRITE_RESP_SB_ID_DEFINES_TABLE, 16, BE, "", "")
        CONST_TBL_ENTRY(MSIM_SB_TMSI,                        114, "")
        CONST_TBL_ENTRY(MSIM_SB_LAI,                         113, "")
        CONST_TBL_ENTRY(MSIM_SB_LOC_UPD_STATUS,              124, "")
        CONST_TBL_ENTRY(MSIM_SB_FORBIDDEN_PLMNS,             103, "")
        CONST_TBL_ENTRY(MSIM_SB_GPRS_CIPHERING_KEY_SNR,      105, "")
        CONST_TBL_ENTRY(MSIM_SB_GPRS_RAI,                    106, "")
        CONST_TBL_ENTRY(MSIM_SB_GPRS_RAUS,                   107, "")
        CONST_TBL_ENTRY(MSIM_SB_GPRS_TMSI,                   108, "")
        CONST_TBL_ENTRY(MSIM_SB_GPRS_TMSI_SIGN_VALUE,        109, "")
        CONST_TBL_ENTRY(MSIM_SB_CIPHERING_KEY_SNR,           102, "")
        CONST_TBL_ENTRY(MSIM_SB_UMTS_CS_KSI,                 115, "")
        CONST_TBL_ENTRY(MSIM_SB_UMTS_PS_KSI,                 118, "")
        CONST_TBL_ENTRY(MSIM_SB_UMTS_START_PS,               121, "")
        CONST_TBL_ENTRY(MSIM_SB_UMTS_START_CS,               123, "")
        CONST_TBL_ENTRY_VER(MSIM_SB_GUTI,                    135, "003.001", "")
        CONST_TBL_ENTRY_VER(MSIM_SB_TAI,                     136, "003.001", "")
        CONST_TBL_ENTRY_VER(MSIM_SB_EPS_UPD_STATUS,          137, "003.001", "")
        CONST_TBL_ENTRY_VER(MSIM_SB_ASME_KSI,                138, "003.001", "")
        CONST_TBL_ENTRY_VER(MSIM_SB_ASME_KEY,                139, "003.001", "")
        CONST_TBL_ENTRY_VER(MSIM_SB_UL_NAS_COUNT,            140, "003.001", "")
        CONST_TBL_ENTRY_VER(MSIM_SB_DL_NAS_COUNT,            141, "003.001", "")
        CONST_TBL_ENTRY_VER(MSIM_SB_NAS_SECUR_ALGOR_IDS,     142, "003.001", "")
        CONST_TBL_ENTRY_VER(MSIM_SB_GPRS_CIPHERING_KEY,      104, "005.000", "")
        CONST_TBL_ENTRY_VER(MSIM_SB_UMTS_PS_CIPHERING_KEY,   119, "005.000", "")
        CONST_TBL_ENTRY_VER(MSIM_SB_UMTS_PS_INTEGRITY_KEY,   120, "005.000", "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_CS_WRITE_RESP_SB_ID,
        MSIM_SB_CS_WRITE_RESP_SB_ID_DEFINES_TABLE, "", "")
        DER_CONST_TBL_ENTRY(MSIM_SB_TMSI)
        DER_CONST_TBL_ENTRY(MSIM_SB_LAI)
        DER_CONST_TBL_ENTRY(MSIM_SB_LOC_UPD_STATUS)
        DER_CONST_TBL_ENTRY(MSIM_SB_FORBIDDEN_PLMNS)
        DER_CONST_TBL_ENTRY(MSIM_SB_GPRS_CIPHERING_KEY_SNR)
        DER_CONST_TBL_ENTRY(MSIM_SB_GPRS_RAI)
        DER_CONST_TBL_ENTRY(MSIM_SB_GPRS_RAUS)
        DER_CONST_TBL_ENTRY(MSIM_SB_GPRS_TMSI)
        DER_CONST_TBL_ENTRY(MSIM_SB_GPRS_TMSI_SIGN_VALUE)
        DER_CONST_TBL_ENTRY(MSIM_SB_CIPHERING_KEY_SNR)
        DER_CONST_TBL_ENTRY(MSIM_SB_UMTS_CS_KSI)
        DER_CONST_TBL_ENTRY(MSIM_SB_UMTS_PS_KSI)
        DER_CONST_TBL_ENTRY(MSIM_SB_UMTS_START_PS)
        DER_CONST_TBL_ENTRY(MSIM_SB_UMTS_START_CS)
        DER_CONST_TBL_ENTRY_VER(MSIM_SB_GUTI, "003.001", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_SB_TAI, "003.001", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_SB_EPS_UPD_STATUS, "003.001", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_SB_ASME_KSI, "003.001", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_SB_ASME_KEY, "003.001", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_SB_UL_NAS_COUNT, "003.001", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_SB_DL_NAS_COUNT, "003.001", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_SB_NAS_SECUR_ALGOR_IDS, "003.001", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_SB_GPRS_CIPHERING_KEY, "005.000", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_SB_UMTS_PS_CIPHERING_KEY, "005.000", "")
        DER_CONST_TBL_ENTRY_VER(MSIM_SB_UMTS_PS_INTEGRITY_KEY, "005.000", "")
    DER_CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* MSIM_PB_LOCATION_TYPE and its derivatives                             */
    /* --------------------------------------------------------------------- */
    #define MSIM_PB_SB_START                         200
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_PB_LOCATION_TYPE_TABLE, 16, BE, "", "")
        CONST_TBL_ENTRY(MSIM_PB_FDN_LIST_STATUS,    (MSIM_PB_SB_START + 1), "")
        CONST_TBL_ENTRY(MSIM_PB_INFO_REQUEST,       (MSIM_PB_SB_START + 2), "")
        CONST_TBL_ENTRY_VER(MSIM_PB_LOCATION,       (MSIM_PB_SB_START + 3), "",
            "002.000")
        CONST_TBL_ENTRY_VER(MSIM_PB_MSISDN,         (MSIM_PB_SB_START + 4), "",
            "002.000")
        CONST_TBL_ENTRY(MSIM_PB_STATUS,             (MSIM_PB_SB_START + 5), "")
        CONST_TBL_ENTRY(MSIM_PB_SB_END,             (MSIM_PB_SB_START + 6), "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_SB_REQUEST_TAGS, MSIM_PB_LOCATION_TYPE_TABLE, "",
        "")
        DER_CONST_TBL_ENTRY(MSIM_PB_FDN_LIST_STATUS)
        DER_CONST_TBL_ENTRY_VER(MSIM_PB_MSISDN, "", "002.000")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(MSIM_PB_LOCATION_TYPE, MSIM_PB_LOCATION_TYPE_TABLE, "",
        "002.000")
        DER_CONST_TBL_ENTRY(MSIM_PB_MSISDN)
    DER_CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* RAT mode settings                                                */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_RAT_MODE, 8, BE, "004.000", "")
        COMMENT(COMMENT_TEXT, "All supported bands and RATs used.")
        CONST_TBL_ENTRY(MSIM_RAT_MODE_DUAL,                     0, "")
        COMMENT(COMMENT_TEXT, "2G only, all supported bands on 2G used.")
        CONST_TBL_ENTRY(MSIM_RAT_MODE_2G_ONLY,                  1, "")
        COMMENT(COMMENT_TEXT, "3G only, all supported bands on 3G used.")
        CONST_TBL_ENTRY(MSIM_RAT_MODE_3G_ONLY,                  2, "")
    CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /*  EHPLMN display mode                                                  */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_EHPLMN_DISPLAY_MODE, 8, BE, "003.001", "")
        COMMENT(COMMENT_TEXT, "No preference for the display mode.")
        CONST_TBL_ENTRY(MSIM_EHPLMN_DM_NO_PREF,                       0, "")
        COMMENT(COMMENT_TEXT, "Display the highest-priority available EHPLMN "
            "only.")
        CONST_TBL_ENTRY(MSIM_EHPLMN_DM_HIGHEST_PRIO_ONLY,             1, "")
        COMMENT(COMMENT_TEXT, "Display all the available EHPLMNs.")
        CONST_TBL_ENTRY(MSIM_EHPLMN_DM_DISPLAY_ALL,                   2, "")
    CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /*  Last RPLMN Selection Indication                                      */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_LAST_RPLMNSI, 8, BE, "005.000", "")
        COMMENT(COMMENT_TEXT, "The UE shall attempt registration on the last RPLMN")
        CONST_TBL_ENTRY(MSIM_LAST_RPLMN_SELECTION_INDICATION_RPLMN,    0, "")
        COMMENT(COMMENT_TEXT, "The UE shall attempt registration on the home "
            "network")
        CONST_TBL_ENTRY(MSIM_LAST_RPLMN_SELECTION_INDICATION_HPLMN,    1, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /*  SMS Storage Query types                                              */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_QUERY_TYPE, 8, BE, "005.002", "")
        COMMENT(COMMENT_TEXT, "Free space")
        CONST_TBL_ENTRY(MSIM_SMS_NEXT_FREE,
            0, "")
        COMMENT(COMMENT_TEXT, "Message received by UE from network; "
            "message read")
        CONST_TBL_ENTRY(MSIM_SMS_NEXT_MT_READ,
            1, "")
        COMMENT(COMMENT_TEXT, "Message received by UE from network; "
            "message to be read")
        CONST_TBL_ENTRY(MSIM_SMS_NEXT_MT_UNREAD,
            2, "")
        COMMENT(COMMENT_TEXT, "UE originating message; message to be sent")
        CONST_TBL_ENTRY(MSIM_SMS_NEXT_MO_TO_BE_SENT,
            7, "")
        COMMENT(COMMENT_TEXT, "UE originating message; "
            "message sent to the network: Status report not requested")
        CONST_TBL_ENTRY(MSIM_SMS_NEXT_MO_SENT_SR_NOT_REQUESTED,
            5, "")
        COMMENT(COMMENT_TEXT, "UE originating message; "
            "message sent to the network: Status report requested but "
            "not (yet) received" )
        CONST_TBL_ENTRY(MSIM_SMS_NEXT_MO_SENT_SR_REQUESTED_NOT_RECEIVED,
            13, "")
        COMMENT(COMMENT_TEXT, "UE originating message; "
            "message sent to the network: Status report requested, received "
            "but not stored in EF-SMSR" )
        CONST_TBL_ENTRY(MSIM_SMS_NEXT_MO_SENT_SR_REQUESTED_RECEIVED_NOT_STORED,
            21, "")
        COMMENT(COMMENT_TEXT, "UE originating message; "
            "message sent to the network: Status report requested, received "
            "and stored in EF-SMSR" )
        CONST_TBL_ENTRY(MSIM_SMS_NEXT_MO_SENT_SR_REQUESTED_RECEIVED_STORED,
            29, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /*  SMS Storage Read types                                               */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MSIM_READ_TYPE, 8, BE, "005.002", "")
        COMMENT(COMMENT_TEXT, "Read status byte only")
        CONST_TBL_ENTRY(MSIM_SMS_STORAGE_READ_STATUS,    1, "")
        COMMENT(COMMENT_TEXT, "Read remainder only")
        CONST_TBL_ENTRY(MSIM_SMS_STORAGE_READ_REMAINDER, 2, "")
        COMMENT(COMMENT_TEXT, "Read whole record (status and remainder)")
        CONST_TBL_ENTRY(MSIM_SMS_STORAGE_READ_RECORD,    3, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Sequences                                                             */
    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_ECC_RECORD")
    SEQ_BEGIN(MSIM_SB_ECC_RECORD, CREATE_STRUCT, "", "")
        VALUE(8, BE, Ecc1, "Ecc1", HEX)
        VALUE(8, BE, Ecc2, "Ecc2", HEX)
        VALUE(8, BE, Ecc3, "Ecc3", HEX)
        VALUE(8, BE, EccTypeIndicator, "ECC Type Indicator", HEX)
        COMMENT(COMMENT_PARAGRAPH, "First byte of field and any padding bytes")
        STRING_REF(STRING_ASCII, BE, EccAlphaIdentifier,
            "Ecc Alpha Identifier", L, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "tMSIM_SB_FORBIDDEN_PLMNS_PLMN")
    SEQ_BEGIN(MSIM_SB_FORBIDDEN_PLMNS_PLMN, CREATE_STRUCT, "", "")
        SEQ_OF(PLMN, "PLMN", AUTOGEN_SEQ_BYTE_HEX, MSIM_PLMN_LEN)
        FILLER(FILLER_FIXED, 8)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "tMSIM_SB_OPERATOR_PLMNS_PLMN")
    SEQ_BEGIN(MSIM_SB_OPERATOR_PLMNS_PLMN, CREATE_STRUCT, "", "")
        SEQ_OF(PLMN, "PLMN", AUTOGEN_SEQ_BYTE_HEX, MSIM_PLMN_LEN)
        FILLER(FILLER_FIXED, 8)
        SEQ_OF(PLMNAccessTechnologyID, "PLMN Access Technology ID",
            AUTOGEN_SEQ_BYTE_HEX, MSIM_PLMN_ACCESS_TECHNOLOGY_LEN)
        FILLER(FILLER_FIXED, 16)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_PLMN_RECORD")
    SEQ_BEGIN(MSIM_SB_PLMN_RECORD, CREATE_STRUCT, "", "")
        SEQ_OF(PLMN, "PLMN", AUTOGEN_SEQ_BYTE_HEX, MSIM_PLMN_LEN)
        FILLER(FILLER_FIXED, 8)
    SEQ_END

    SEQ_BEGIN(MSIM_RESP_IMSI, CREATE_STRUCT, "", "002.000")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, length, "Length", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "IMSI number.")
        SEQ_OF(imsi, "imsi", AUTOGEN_SEQ_BYTE_HEX, MSIM_IMSI_LEN)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "MSIM_INFO_DYNAMIC_FLAGS_STR")
    SEQ_BEGIN(MSIM_INFO_DYNAMIC_FLAGS, CREATE_STRUCT, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Coding:")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0: Alternate line.")
        COMMENT(COMMENT_BULLET, "1: Primary line.")
        VALUE(8, BE, selected_line, "Selected Line", HEX)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Coding:")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0: Calling Line Identity presentation, "
            "restricted.")
        COMMENT(COMMENT_BULLET, "1: Calling Line Identity presentation, "
            "presented.")
        VALUE(8, BE, clir_flag, "CLIR flag", HEX)
        FILLER(FILLER_FIXED, 16)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tCSP_Optionals")
    SEQ_BEGIN(CSP_OPTIONALS, CREATE_STRUCT, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, HML_Spec, "HML Spec", HEX)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, D5InfoNumbers, "D5 Info Numbers", HEX)
        FILLER(FILLER_FIXED, 16)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "MSIM_SERV_CSP_CPHS_TELESERVICES_STR")
    SEQ_BEGIN(MSIM_SERV_CSP_CPHS_TELESERVICES_STR, CREATE_STRUCT, "", "")
        COMMENT(COMMENT_TEXT, "Alternate Line Service.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, als, "ALS", HEX)
        FILLER(FILLER_FIXED, 24)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "MSIM_SERV_CSP_NBR_IDENTIFICATION_STR")
    SEQ_BEGIN(MSIM_SERV_CSP_NBR_IDENTIFICATION_STR, CREATE_STRUCT, "", "")
        COMMENT(COMMENT_TEXT, "Menu to block Calling Line Identity.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, cli_block, "CLI Block", HEX)
        COMMENT(COMMENT_TEXT, "Menu to send Calling Line Identity.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, cli_send, "CLI Send", HEX)
        COMMENT(COMMENT_TEXT, "Malicious Call Indicator.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, malicious_call_ind, "Malicious Call Indicator", HEX)
        COMMENT(COMMENT_TEXT, "Connected Line Identity Presentation.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, conn_line_ind_pres, "Connected Line Indentity "
            "Presentation", HEX)
        COMMENT(COMMENT_TEXT, "Connected Line Identity Restricted.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, conn_line_ind_restriction, "Connected Line Indication "
            "Restriction", HEX)
        COMMENT(COMMENT_TEXT, "Calling Line Identity Presentation.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, clip, "CLIP", HEX)
        FILLER(FILLER_FIXED, 16)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "MSIM_SERV_CSP_STR")
    SEQ_BEGIN(MSIM_SERV_CSP_STR, CREATE_STRUCT, "", "")
        SEQ_OF(nbr_identification, "Number Identification",
            MSIM_SERV_CSP_NBR_IDENTIFICATION_STR, 1)
        COMMENT(COMMENT_TEXT, "CPHS Teleservices.")
        SEQ_OF(cphs_teleservices, "CPHS Teleservices",
            MSIM_SERV_CSP_CPHS_TELESERVICES_STR, 1)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "MSIM_INFO_CBMID_STR")
    SEQ_BEGIN(MSIM_INFO_CBMID_STR, CREATE_STRUCT, "", "005.000")
        SEQ_OF(cbmid, "CBMID", AUTOGEN_SEQ_WORD_DEC, MSIM_MAX_NBR_OF_CBMIDS)
        FILLER(FILLER_FIXED, 16)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_REFRESH_FILE_LIST_STR")
    SEQ_BEGIN(MSIM_REFRESH_FILE_LIST_STR, CREATE_STRUCT, "", "")
        COMMENT(COMMENT_TEXT, "FileID of elementary file to refresh.")
        VALUE_CONST(FileID, "FileID", MSIM_REFERSH_FILE_IDS)
        COMMENT(COMMENT_TEXT, "Ask client if refresh of elementary file is "
            "allowed before refresh is executed")
        VALUE_CONST(AskBeforeRefresh, "Ask Before Refresh", TRUE_FALSE)
        FILLER(FILLER_FIXED, 16)
    SEQ_END

    SEQ_BEGIN(MSIM_REFERSH_FILE_LIST, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(FileID, "File ID", MSIM_REFERSH_FILE_IDS)
    SEQ_END

    SEQ_BEGIN(MSIM_EMRG_CALL_CODE, CREATE_STRUCT, "", "")
        COMMENT(COMMENT_TEXT,"Format of 6 digit ECC string: ECC digit1, ECC "
            "digit2, ECC digit3, ECC digit4, ECC digit5, ECC digit6, NULL")
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, emrg_call_code,
            "Emergency Call Code", ( 2 * MSIM_ONE_EMRG_CALL_CODE_LEN ) + 1)
        FILLER(FILLER_FIXED, 8)
    SEQ_END

    SEQ_BEGIN(MSIM_EMRG_CALL_CODES, CREATE_STRUCT, "", "")
        SEQ_OF(emrg_call_codes, "Emergency Call Codes",
            MSIM_EMRG_CALL_CODE, MSIM_MAX_NBR_OF_EMRG_CALL_CODES)
    SEQ_END

    SEQ_BEGIN(MSIM_PB_TAG, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(Tag, "Tag", MSIM_SB_REQUEST_TAGS)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_Imsi")
    SEQ_BEGIN(MSIM_IMSI, CREATE_STRUCT, "", "002.000")
        SEQ_OF(Imsi, "IMSI", MSIM_RESP_IMSI, 1)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "MSIM_SERV_CPHS_STR")
    COMMENT(COMMENT_TEXT, "CPHS Service table.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "Indicates if the optional data-field is able to be "
        "read and updated. Data-field is available if it is 'activated' and "
        "'allocated'.")
    SEQ_BEGIN(MSIM_SERV_CPHS_STR, CREATE_STRUCT, "", "")
        COMMENT(COMMENT_TEXT, "CPHS phase.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0x01: Phase 1.")
        COMMENT(COMMENT_BULLET, "0x02: Phase 2.")
        COMMENT(COMMENT_TEXT, "etc.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, phase, "phase", HEX)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Customer Service Profile(CSP) data-field is "
            "allocated.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "CSP is a list of user accesible services.")
        VALUE(8, BE, csp_allocated, "csp_allocated", HEX)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Customer Service Profile(CSP) data-field is "
            "active.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "CSP is a list of user accesible services.")
        VALUE(8, BE, csp_active, "csp_active", HEX)
        COMMENT(COMMENT_TEXT, "Service String Table(SST) data-field is "
            "allocated.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, service_string_tbl_allocated,
            "service_string_tbl_allocated", HEX)
        COMMENT(COMMENT_TEXT, "Service String Table(SST) data-field is "
            "active.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, service_string_tbl_active, "service_string_tbl_active",
            HEX)
        COMMENT(COMMENT_TEXT, "Mailbox numbers data-field is allocated.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Mailbox Number is the dialling number to the "
            "Voice Mailbox.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, mailbox_numbers_allocated, "mailbox_numbers_allocated",
            HEX)
        COMMENT(COMMENT_TEXT, "Mailbox numbers data-field is active.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Mailbox Number is the dialling number to the "
            "Voice Mailbox.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, mailbox_numbers_active, "mailbox_numbers_active", HEX)
        COMMENT(COMMENT_TEXT, "Information Number data-field is allocated.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, inf_nbr_allocated, "inf_nbr_allocated", HEX)
        COMMENT(COMMENT_TEXT, "Information Number data-field is active.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, inf_nbr_active, "inf_nbr_active", HEX)
        FILLER(FILLER_FIXED, 24)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tCPHS_Optionals")
    SEQ_BEGIN(CPHS_OPTIONALS, CREATE_STRUCT, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, MailboxNumbInfo, "MailboxNumbInfo", HEX)
        FILLER(FILLER_FIXED, 24)
    SEQ_END

    /* Autogen warns that MSIM_FDN_CHECK_GENERIC_SB is not used in macro file.
     * While this is true it is used on code as well as aliases created from it
     * and thus it is required here.
     */
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_FDN_CHECK_GENERIC_SB")
    SEQ_BEGIN(MSIM_FDN_CHECK_GENERIC_SB, CREATE_STRUCT, "", "003.000")
        VALUE(16, BE, SubBlockID, "Sub Block ID", HEX)
        VALUE(16, BE, SubBlockLength, "Sub Block Length", DEC)
        VALUE_CONST(Status, "Status", MSIM_SB_PHONE_STATUS)
        REFERENCE(8, BE, NumLen, "Number Length", N)
        FILLER(FILLER_FIXED, 16)
        SEQ_OF_REF(Num, "Number", AUTOGEN_SEQ_WORD_HEX, N,
            ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SEQ_END

    /* Autogen warns that MSIM_SB_INFO_REQUEST is not used in macro file.
     * While this is true it is used on code and thus it is required here.
     */
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_INFO_REQUEST")
    SEQ_BEGIN(MSIM_SB_INFO_REQUEST, CREATE_STRUCT, "", "")
        MSIM_SB_16_LONG_SEQ
        FILLER(FILLER_FIXED, 8)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, MSIM_MAX_NUMBER_OF_TAGS)
        REFERENCE(8, BE, NumberOfTags, "Number of Tags", M)
        SEQ_OF_REF(Tags, "Tags", MSIM_PB_TAG, M, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SEQ_END

    /* Autogen warns that MSIM_SB_UINT8 is not used in macro file.
     * While this is true it is used on code and thus it is required here.
     */
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_UINT8")
    SEQ_BEGIN(MSIM_SB_UINT8, CREATE_STRUCT, "", "")
        MSIM_SB_16_LONG_SEQ
        VALUE(8, BE, Data, "Data", HEX)
        FILLER(FILLER_FIXED, 24)
    SEQ_END

#if 0
    /* Autogen warns that MSIM_SB_PRIMITIVE is not used in macro file.
     * While this is true it is used on code and thus it is required here.
     */
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_PRIMITIVE")
    SEQ_BEGIN(MSIM_SB_PRIMITIVE, CREATE_STRUCT, "", "")
        MSIM_SB_16_LONG_SEQ
    SEQ_END
#endif /* 0 */

    /* Autogen warns that MSIM_SB is not used in macro file.
     * While this is true it is used on code and thus it is required here.
     */
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "tMSIM_SB_PRIMITIVE")
    SEQ_BEGIN(MSIM_SB, CREATE_STRUCT, "", "")
        VALUE(16, BE, SubBlockID, "Sub Block ID", HEX)
        VALUE(16, BE, SubBlockLength, "Sub Block Length", DEC)
    SEQ_END

    /* Autogen warns that MSIM_SB_NAME_NUMBER is not used in macro file.
     * While this is true it is used on code and thus it is required here.
     */
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_NAME_NUMBER")
    SEQ_BEGIN(MSIM_SB_NAME_NUMBER, CREATE_STRUCT, "", "")
        MSIM_SB_16_LONG_SEQ
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, MSIM_NAME_LEN)
        REFERENCE(8, BE, NameLength, "Length of Name", NAME_LEN)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, MSIM_NUMBER_LEN)
        REFERENCE(8, BE, NumberLength, "Length of Number", NUM_LEN)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Name, "Name", NAME_LEN,
            ISIHDR_RESERVE_SPACE)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Number, "Number",
            NUM_LEN, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SEQ_END

    /* Autogen warns that MSIM_SB_UNSUPPORTED is not used in macro file.
     * While this is true it is used on code and thus it is required here.
     */
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_UNSUPPORTED")
    SEQ_BEGIN(MSIM_SB_UNSUPPORTED, CREATE_STRUCT, "", "")
        VALUE(16, BE, SubBlockID, "Sub Block ID", HEX)
        VALUE(16, BE, SubBlockLength, "Sub Block Length", DEC)
        VALUE(8, BE, Status, "Status", HEX)
        FILLER(FILLER_FIXED, 24)
    SEQ_END

    /* Autogen warns that MSIM_SAT_CB_DOWNLOAD_REQ is not used in macro file.
     * While this is true it is used on code and thus it is required here.
     */
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SAT_CB_DOWNLOAD_Req")
    SEQ_BEGIN(MSIM_SAT_CB_DOWNLOAD_REQ, CREATE_STRUCT, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        VALUE(8, BE, MessageID, "Message ID", HEX)
        VALUE(8, BE, ServiceType, "Service Type", HEX)
        VALUE(8, BE, SerialMsb, "Serial MSB", HEX)
        VALUE(8, BE, SerialLsb, "Serial LSB", HEX)
        VALUE(8, BE, MessageMsb, "Message MSB", HEX)
        VALUE(8, BE, MessageLsb, "Message LSB", HEX)
        VALUE(8, BE, CodingScheme, "Data Coding Scheme", HEX)
        VALUE(8, BE, Page, "Page", HEX)
        FILLER(FILLER_FIXED, 24)
        SEQ_OF(Message, "Message", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_CBS_MSG_MAX_LENGTH)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    SEQ_BEGIN(MSIM_SB_CS_WRITE_RESP_SB, CREATE_STRUCT, "", "")
        VALUE_CONST(SubBlockID, "Sub Block ID Type", MSIM_SB_CS_WRITE_RESP_SB_ID)
        VALUE(16, BE, SubBlockLength, "Sub Block Length", DEC)
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 24)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_Request")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "tMSIM_REFRESH_UNREGISTER_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "tMSIM_REFRESH_PERMISSION_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "tMSIM_REFRESH_RESULT_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "tMSIM_REFRESH_CANCELLED_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "tMSIM_ST_MMS_ICP_READ_REQ")
    SEQ_BEGIN(MSIM_REQUEST, CREATE_STRUCT, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        VALUE(8, BE, MessageID, "Message ID", HEX)
        VALUE(8, BE, ServiceType, "Service Type", HEX)
        FILLER(FILLER_FIXED, 8)
    SEQ_END

    /* Autogen warns that MSIM_RESPONSE is not used in macro file.
     * While this is true it is used on code as well as aliases created from it
     * and thus it is required here.
     */
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_Response")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "tMSIM_REFRESH_REGISTER_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME,
        "tMSIM_REFRESH_UNREGISTER_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME,
        "tMSIM_REFRESH_PERMISSION_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "tMSIM_REFRESH_RESULT_RESP")
    SEQ_BEGIN(MSIM_RESPONSE, CREATE_STRUCT, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        VALUE(8, BE, MessageID, "Message ID", HEX)
        VALUE(8, BE, ServiceType, "Service Type", HEX)
        VALUE(8, BE, Status, "Status", HEX)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_Ind")
    SEQ_BEGIN(MSIM_IND_SEQ, CREATE_STRUCT, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        VALUE(8, BE, MessageID, "Message ID", HEX)
        VALUE_CONST(ServiceType, "Service Type", MSIM_IND_ST_TABLE)
        VALUE_CONST(Status, "Status", MSIM_IND_STATUS_TABLE)
        VALUE_CONST(State, "State", MSIM_STATE_TABLE)
        VALUE_CONST(Cause, "Cause", MSIM_CAUSES_TABLE)
        COMMENT(COMMENT_TEXT, "Application on [U]SIM that is active.")
        VALUE(8, BE, ApplicationNumber, "Application Number", HEX)
        FILLER(FILLER_FIXED, 8)
    SEQ_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_CS_READ_REQ")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "MSIM_ST_CS_DATA_READ_ALL_GSS_REQ.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "MSIM_ST_CS_DATA_READ_LIMITED_GSS_REQ.")
    SEQ_BEGIN(MSIM_CS_READ_REQ, CREATE_STRUCT, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        VALUE(8, BE, MessageID, "Message ID", HEX)
        VALUE(8, BE, ServiceType, "Service Type", HEX)
        VALUE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", HEX)
    SEQ_END

    /* Autogen warns that MSIM_CS_READ_REQ_ST_DATA_READ is not used in macro
     * file. While this is true it is used on code and thus it is required
     * here.
     */
    PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "tMSIM_CS_READ_REQ_ST_DATA_READ")
    SEQ_BEGIN(MSIM_CS_READ_REQ_ST_DATA_READ, CREATE_STRUCT, "", "")
        SEQ_OF(Req, "Req", MSIM_CS_READ_REQ, 1)
        VALUE(16, BE, SubblockID, "Sub Block ID", HEX)
    SEQ_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_InfoResponse")
    SEQ_BEGIN(MSIM_INFO_RESPONSE, CREATE_STRUCT, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        VALUE(8, BE, ServiceType, "Service Type", HEX)
        VALUE_CONST(Status, "Status", MSIM_SB_STA_TABLE)
    SEQ_END


    /* --------------------------------------------------------------------- */
    /* Sub blocks                                                            */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_LOCATION")
    SB_BEGIN(MSIM_PB_LOCATION, "", "002.000")
        MSIM_SB_16_LONG
        VALUE_CONST(LocationType, "Location Type", MSIM_PB_LOCATION_TYPE)
        VALUE(16, BE, Location, "Location", DEC)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_RAND_PARAMS")
    SB_BEGIN(MSIM_SB_RAND_PARAMS, "", "")
        MSIM_SB_16_LONG
        COMMENT(COMMENT_PARAGRAPH, "The status field can not be used in "
        "requests and shall carry default value of 0xFF in these cases.")
        VALUE_CONST(Status, "Status", MSIM_SB_PARAMS_STATUS)
        FILLER(FILLER_FIXED, 24)
        SEQ_OF(Rnd, "Random Parameters", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_RND_PARAMS_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_UMTS_AUTN_PARAMS")
    SB_BEGIN(MSIM_SB_UMTS_AUTN_PARAMS, "", "")
        MSIM_SB_16_LONG
        COMMENT(COMMENT_PARAGRAPH, "The status field can not be used because "
        "this sub-block is only used in requests. Default value = 0xFF.")
        VALUE_CONST(Status, "Status", MSIM_SB_PARAMS_STATUS)
        FILLER(FILLER_FIXED, 24)
        SEQ_OF(AutnParams, "Authentication Parameters", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_UMTS_AUTN_PARAMS_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_UMTS_CS_KSI")
    SB_BEGIN(MSIM_SB_UMTS_CS_KSI, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        COMMENT(COMMENT_TEXT, "KSI or MSIM_INVALID_KEY_SET_IDENTIFIER")
        VALUE(8, BE, CsKsi, "The Key Set Identifier", HEX)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_UMTS_PS_KSI")
    SB_BEGIN(MSIM_SB_UMTS_PS_KSI, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        COMMENT(COMMENT_TEXT, "KSI or MSIM_INVALID_KEY_SET_IDENTIFIER")
        VALUE(8, BE, PsKsi, "The Key Set Identifier", HEX)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_CIPHERING_KEY_SNR")
    SB_BEGIN(MSIM_SB_CIPHERING_KEY_SNR, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_CIPHERING_KEY_SNR_STATUS)
        COMMENT(COMMENT_TEXT, "CKSN or MSIM_INVALID_KEY_SET_IDENTIFIER")
        VALUE(8, BE, CipheringKeySequenceNumber,
            "Ciphering Key Sequence Number", HEX)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "tMSIM_SB_GPRS_CIPHERING_KEY_SNR")
    SB_BEGIN(MSIM_SB_GPRS_CIPHERING_KEY_SNR, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        COMMENT(COMMENT_TEXT, "CKSN or MSIM_INVALID_KEY_SET_IDENTIFIER")
        VALUE(8, BE, GprsCipheringKeySNR, "GPRS Ciphering Key Sequence Number",
            HEX)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_RES_PARAMS")
    SB_BEGIN(MSIM_SB_RES_PARAMS, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_PARAMS_STATUS)
        FILLER(FILLER_FIXED, 16)
        VALUE(8, BE, LengthOfRes, "Length of Response", DEC)
        SEQ_OF(RES, "RES", AUTOGEN_SEQ_BYTE_HEX, MSIM_RES_MAX_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "tMSIM_SB_UMTS_CS_CIPHERING_KEY")
    SB_BEGIN(MSIM_SB_UMTS_CS_CIPHERING_KEY, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 24)
        SEQ_OF(CsCipheringKey, "CS Ciphering Key", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_UMTS_CS_CIPH_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "tMSIM_SB_UMTS_CS_INTEGRITY_KEY")
    SB_BEGIN(MSIM_SB_UMTS_CS_INTEGRITY_KEY, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 24)
        SEQ_OF(CsIntegrityKey, "CS Integrity Key", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_UMTS_CS_INTE_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "tMSIM_SB_UMTS_PS_CIPHERING_KEY")
    SB_BEGIN(MSIM_SB_UMTS_PS_CIPHERING_KEY, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 24)
        SEQ_OF(PsCipheringKey, "PS Ciphering Key", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_UMTS_PS_CIPH_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "tMSIM_SB_UMTS_PS_INTEGRITY_KEY")
    SB_BEGIN(MSIM_SB_UMTS_PS_INTEGRITY_KEY, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 24)
        SEQ_OF(PsIntegrityKey, "UMTS Integrity Key", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_UMTS_PS_INTE_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_CIPHERING_KEY")
    SB_BEGIN(MSIM_SB_CIPHERING_KEY, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 24)
        SEQ_OF(CipheringKey, "Ciphering Key", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_CIPH_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_GPRS_CIPHERING_KEY")
    SB_BEGIN(MSIM_SB_GPRS_CIPHERING_KEY, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 24)
        SEQ_OF(GprsCipheringKey, "GPRS Ciphering Key", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_GPRS_CIPH_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "tMSIM_SB_UMTS_AUTN_FAIL_PARAMS")
    SB_BEGIN(MSIM_SB_UMTS_AUTN_FAIL_PARAMS, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_UMTS_FAIL_PARAMS_STATUS)
        VALUE(8, BE, LengthOfAUTS, "Length Of AUTS", DEC)
        SEQ_OF(AutsParams, "AUTS Parameters", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_UMTS_AUTS_PARAMS_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_ACC")
    COMMENT(COMMENT_TEXT, "This sub-block contains the Access Control Class")
    SB_BEGIN(MSIM_SB_ACC, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 8)
        SEQ_OF(ACCData, "ACC Data", AUTOGEN_SEQ_BYTE_HEX, MSIM_ACC_CTRL_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_ECC")
    SB_BEGIN(MSIM_SB_ECC, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 254)
        REFERENCE(8, BE, NumberOfEccCodes, "Number of ECC Codes", N)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 4)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 254)
        VALUE(8, BE, EccCodeLength, "ECC Code Length", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 251)
        REFERENCE(8, BE, EccAlphaIdentifierLength, "ECC Alpha ID Length", L)
        COMMENT(COMMENT_PARAGRAPH, "First byte of array of "
            "tMSIM_SB_ECC_RECORDs")
        SEQ_OF_REF(EccRecord, "ECC Record", MSIM_SB_ECC_RECORD, N,
            ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_FORBIDDEN_PLMNS")
    COMMENT(COMMENT_TEXT, "This sub-block contains the forbidden PLMNs")
    SB_BEGIN(MSIM_SB_FORBIDDEN_PLMNS, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        VALUE_CONST(FPLMNListOperation, "FPLMN List Operation",
            MSIM_SB_FORBIDDEN_PLMNS_FPLMN)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 4)
        VALUE(16, BE, MaxNoOfFPLMNS, "Maximum Number of FPLMNs", DEC)
        SEQ_OF_REF(fplmns, "FPLMNs", MSIM_SB_FORBIDDEN_PLMNS_PLMN,
            REF_AS_MANY_AS_POSSIBLE,  ISIHDR_MARKER_SINGLE_ELEMENT)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_HPLMN")
    COMMENT(COMMENT_TEXT, "This sub-block contains the Home PLMN")
    SB_BEGIN(MSIM_SB_HPLMN, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        VALUE(8, BE, NoOfDigitsInMNC, "Number of Digits in MNC", DEC)
        SEQ_OF(HPLMN, "HPLMN", AUTOGEN_SEQ_BYTE_HEX, MSIM_HPLMN_LEN)
        FILLER(FILLER_FIXED, 24)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_HPLMN_SEARCH")
    COMMENT(COMMENT_TEXT, "This sub-block contains the time interval between "
        "two searches for a higher priority PLMN.")
    SB_BEGIN(MSIM_SB_HPLMN_SEARCH, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        VALUE(8, BE, TimeInterval, "Time Interval", HEX)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_LAI")
    COMMENT(COMMENT_TEXT, "This sub-block contains Location Area Information "
        "from EFloci.")
    SB_BEGIN(MSIM_SB_LAI, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 31.102.")
        SEQ_OF(LAI, "LAI", AUTOGEN_SEQ_BYTE_HEX, MSIM_LAI_LEN)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_LOC_UPD_STATUS")
    COMMENT(COMMENT_TEXT, "This sub-block contains Location update status from"
        " EFloci.")
    SB_BEGIN(MSIM_SB_LOC_UPD_STATUS, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 31.102.")
        VALUE(8, BE, LocationUpdateStatus, "Location Update Status", HEX)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_OPERATOR_PLMNS")
    SB_BEGIN(MSIM_SB_OPERATOR_PLMN, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        COMMENT(COMMENT_TEXT, "N/A")
        VALUE(8, BE, OPLMNListOperation, "OPLMN List Operation", HEX)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 8)
        VALUE(16, BE, MaxNoOfOPLMNS, "Maximum Number of OPLMNs", DEC)
        SEQ_OF_REF(oplmns, "OPLMNs", MSIM_SB_OPERATOR_PLMNS_PLMN,
            REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_USER_PLMNS")
    COMMENT(COMMENT_TEXT, "This sub-block contains User Controlled PLMNs from "
        "EFplnmwact.")
    SB_BEGIN(MSIM_SB_USER_PLMN, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        VALUE_CONST(UPLMNListOperation, "UPLMN List Operation",
            MSIM_SB_USER_PLMN_UPLMN)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 8)
        VALUE(16, BE, MaxNoOfUPLMNS, "Maximum Number of UPLMNs", DEC)
        SEQ_OF_REF(uplmns, "UPLMNs", MSIM_SB_OPERATOR_PLMNS_PLMN,
            REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_HOME_PLMNS")
    COMMENT(COMMENT_TEXT, "This sub-block contains Home PLMNs from "
        "EFhplnmwact.")
    SB_BEGIN(MSIM_SB_HOME_PLMN, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        VALUE_CONST(HPLMNListOperation, "HPLMN List Operation",
            MSIM_SB_USER_PLMN_UPLMN)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        VALUE(16, BE, MaxNoOfHPLMNS, "Maximum Number of HPLMNs", DEC)
        SEQ_OF_REF(hplmns, "HPLMNs", MSIM_SB_OPERATOR_PLMNS_PLMN,
            REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_PLMN_SELECTOR")
    SB_BEGIN(MSIM_SB_PLMN_SELECTOR, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        VALUE_CONST(PLMNSelListOperation, "PLMN Selector List Operation",
            MSIM_SB_USER_PLMN_UPLMN)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 8)
        VALUE(16, BE, MaxNoOfPLMNS, "Maximum Number of PLMNs", DEC)
        COMMENT(COMMENT_PARAGRAPH, "First byte of array of "
            "MSIM_SB_PLMN_RECORDs")
        SEQ_OF_REF(PLMNRecord, "PLMN Record", MSIM_SB_PLMN_RECORD,
            REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_EQUIVALENT_HPLMNS")
    SB_BEGIN(MSIM_SB_EQUIVALENT_HPLMNS, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 8)
        VALUE(16, BE, NoEHPLMNs, "Number of EHPLMNs", DEC)
        COMMENT(COMMENT_PARAGRAPH, "First byte of array of "
            "tMSIM_SB_PLMN_RECORD")
        SEQ_OF_REF(EHPLMNRecord, "EHPLMN Record", MSIM_SB_PLMN_RECORD,
            REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_IMSI")
    SB_BEGIN(MSIM_SB_IMSI, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        VALUE(8, BE, LengthOfIMSI, "Length of IMSI", DEC)
        VALUE(8, BE, NoOfDigitsInMNC, "Number of Digits in MNC", DEC)
        FILLER(FILLER_FIXED, 8)
        SEQ_OF(IMSI, "IMSI",AUTOGEN_SEQ_BYTE_HEX, MSIM_IMSI_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_TMSI")
    COMMENT(COMMENT_TEXT, "This sub-block contains Temporary Mobile Subscriber"
        " Identity from EFloci.")
    SB_BEGIN(MSIM_SB_TMSI, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 24)
        COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 31.102.")
        SEQ_OF(TMSI, "TMSI",AUTOGEN_SEQ_BYTE_HEX, MSIM_TMSI_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_GPRS_RAI")
    SB_BEGIN(MSIM_SB_GPRS_RAI, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 8)
        SEQ_OF(Rai, "RAI", AUTOGEN_SEQ_BYTE_HEX, MSIM_RAI_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_GPRS_RAUS")
    SB_BEGIN(MSIM_SB_GPRS_RAUS, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        VALUE(8, BE, GprsRaus, "GPRS RAUS", HEX)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_GPRS_TMSI")
    SB_BEGIN(MSIM_SB_GPRS_TMSI, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 24)
        SEQ_OF(GprsTMSI, "GPRS TMSI", AUTOGEN_SEQ_BYTE_HEX, MSIM_GPRS_TMSI_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME,
        "tMSIM_SB_GPRS_TMSI_SIGN_VALUE")
    SB_BEGIN(MSIM_SB_GPRS_TMSI_SIGN_VALUE, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        SEQ_OF(GprsTMSISignatureValue, "GPRS TMSI Signature Value",
            AUTOGEN_SEQ_BYTE_HEX, MSIM_GPRS_TMSI_SIGN_VAL_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_UMTS_START_PS")
    SB_BEGIN(MSIM_SB_UMTS_START_PS, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        SEQ_OF(Hfn, "HFN", AUTOGEN_SEQ_BYTE_HEX, MSIM_UMTS_PS_HFN_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_UMTS_START_CS")
    SB_BEGIN(MSIM_SB_UMTS_START_CS, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        SEQ_OF(Hfn, "HFN", AUTOGEN_SEQ_BYTE_HEX, MSIM_UMTS_CS_HFN_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_UMTS_START_MAX")
    SB_BEGIN(MSIM_SB_UMTS_START_MAX, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        SEQ_OF(StartMax, "Maximum Value of START_CS or START_PS",
            AUTOGEN_SEQ_BYTE_HEX, MSIM_UMTS_START_MAX_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    SB_BEGIN(MSIM_PB_STATUS, "", "003.000")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_PB_STATUS_TABLE)
        FILLER(FILLER_FIXED, 24)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    SB_BEGIN(MSIM_PB_FDN_LIST_STATUS, "", "003.000")
        MSIM_SB_16_LONG
        VALUE_CONST(Data, "Data", MSIM_FDN_STATUS)
        FILLER(FILLER_FIXED, 24)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    SB_BEGIN(MSIM_PB_INFO_REQUEST, "", "003.000")
        MSIM_SB_16_LONG
        FILLER(FILLER_FIXED, 8)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, MSIM_MAX_NUMBER_OF_TAGS)
        REFERENCE(8, BE, NumberOfTags, "Number of Tags", N)
        SEQ_OF_REF(Tags, "Tags", MSIM_PB_TAG, N, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    SB_BEGIN(MSIM_PB_MSISDN, "", "002.000")
        MSIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, MSIM_NAME_LEN)
        REFERENCE(8, BE, NameLength, "Length of Name", NAME_LEN)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, MSIM_NUMBER_LEN)
        REFERENCE(8, BE, NumberLength, "Length of Number", NUM_LEN)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Name, "Name", NAME_LEN,
            ISIHDR_RESERVE_SPACE)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Number, "Number",
            NUM_LEN, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_PHONE_NUMBER_FIELD")
    SB_BEGIN(MSIM_SB_PHONE_NUMBER_FIELD, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_PHONE_STATUS)
        REFERENCE(8, BE, NumLen, "Length of Number", N)
        FILLER(FILLER_FIXED, 16)
        SEQ_OF_REF(Num, "Number", AUTOGEN_SEQ_WORD_HEX, N,
            ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_SMS_DEST_ADR")
    SB_BEGIN(MSIM_SB_SMS_DEST_ADR, "", "003.000")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_PHONE_STATUS)
        REFERENCE(8, BE, NumLen, "Length of Number", N)
        FILLER(FILLER_FIXED, 16)
        SEQ_OF_REF(Num, "Number", AUTOGEN_SEQ_WORD_HEX, N,
            ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_SMS_DEST_ADR")
    SB_BEGIN(MSIM_SB_SMS_DEST_ADR, "003.000", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_PHONE_STATUS)
        REFERENCE(8, BE, NumLen, "Length of Number", N)
        VALUE_CONST(TypeOfNumber, "Type of Number", MSIM_SMS_TYPE_OF_NUMBER)
        FILLER(FILLER_FIXED, 8)
        SEQ_OF_REF(Num, "Number", AUTOGEN_SEQ_WORD_HEX, N,
            ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_SMSC_ADR")
    SB_BEGIN(MSIM_SB_SMSC_ADR, "", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_PHONE_STATUS)
        REFERENCE(8, BE, NumLen, "Length of Number", N)
        FILLER(FILLER_FIXED, 16)
        SEQ_OF_REF(Num, "Number", AUTOGEN_SEQ_WORD_HEX, N,
            ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_RAT_MODE")
    SB_BEGIN(MSIM_SB_RAT_MODE, "004.000", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        COMMENT(COMMENT_TEXT, "RAT mode settings from EFrat.")
        VALUE_CONST(RAT_mode, "RAT Mode", MSIM_RAT_MODE)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_CARD_TYPE")
    SB_BEGIN(MSIM_SB_CARD_TYPE, "003.000", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        VALUE_CONST(CardGeneration, "Card Generation",
            MSIM_SB_CARD_GENERATION_TABLE)
        VALUE_CONST(CardType, "Card Type", MSIM_SB_CARD_TYPE_TABLE)
        FILLER(FILLER_FIXED, 8)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_SIMLOCK_STATUS")
    SB_BEGIN(MSIM_SB_SIMLOCK_STATUS, "003.000", "")
        MSIM_SB_16_LONG        
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        VALUE_CONST(SimlockStatus, "SIMLock Status", MSIM_SIMLOCK_STATUS_TABLE)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_EHPLMN_DISPLAY_MODE")
    COMMENT(COMMENT_TEXT, "This sub-block contains an indication to the ME for "
        "the presentation of the available EHPLMN(s) from EFehplmnpi. "
        "If service n°71 and service n°73 are available, this file "
        "shall be present.")
    SB_BEGIN(MSIM_SB_EHPLMN_DISPLAY_MODE, "003.001", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_UST_STATUS_TABLE)
        COMMENT(COMMENT_TEXT, "The usage of the EHPLMN presentation indication "
            "is defined in TS 23.122.")
        VALUE_CONST(ehplmn_display_mode, "EHPLMN display mode",
            MSIM_EHPLMN_DISPLAY_MODE)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_GUTI")
    COMMENT(COMMENT_TEXT, "This sub-block contains Globally Unique "
        "Temporary Identifier from EFepsloci. If service n°85 is available, "
        "this file shall be present.")
    SB_BEGIN(MSIM_SB_GUTI, "003.001", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_UST_STATUS_TABLE)
        COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 24.301.")
        SEQ_OF(guti, "Globally Unique Temporary Identifier",
            AUTOGEN_SEQ_BYTE_HEX, MSIM_GUTI_LEN)
        FILLER(FILLER_FIXED, 24)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_TAI")
    COMMENT(COMMENT_TEXT, "This sub-block contains Last visited "
        "registered TAI from EFepsloci. If service n°85 is available, "
        "this file shall be present.")
    SB_BEGIN(MSIM_SB_TAI, "003.001", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_UST_STATUS_TABLE)
        COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 24.301.")
        SEQ_OF(tai, "Last visited registered TAI", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_TAI_LEN)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_EPS_UPD_STATUS")
    COMMENT(COMMENT_TEXT, "This sub-block contains EPS update status "
        "from EFepsloci. If service n°85 is available, "
        "this file shall be present.")
    SB_BEGIN(MSIM_SB_EPS_UPD_STATUS, "003.001", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_UST_STATUS_TABLE)
        COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 24.301.")
        VALUE(8, BE, eps_upd_status, "EPS Update Status", HEX)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_ASME_KSI")
    COMMENT(COMMENT_TEXT, "This sub-block contains ASME Key set "
        "identifier from EFepsnsc. If service n°85 is available, "
        "this file shall be present.")
    SB_BEGIN(MSIM_SB_ASME_KSI, "003.001", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_UST_STATUS_TABLE)
        COMMENT(COMMENT_TEXT, "KSI Coded according to 3GPP TS 33.401 or "
            "MSIM_INVALID_KEY_SET_IDENTIFIER")
        SEQ_OF(asme_ksi, "ASME Key Set Identifier", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_ASME_KSI_LEN)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_ASME_KEY")
    COMMENT(COMMENT_TEXT, "This sub-block contains ASME Key "
        "from EFepsnsc. If service n°85 is available, "
        "this file shall be present.")
    SB_BEGIN(MSIM_SB_ASME_KEY, "003.001", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_UST_STATUS_TABLE)
        COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 33.401.")
        SEQ_OF(asme_key, "ASME Key", AUTOGEN_SEQ_BYTE_HEX, MSIM_ASME_KEY_LEN)
        FILLER(FILLER_FIXED, 24)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_UL_NAS_COUNT")
    COMMENT(COMMENT_TEXT, "This sub-block contains uplink NAS count"
        "from EFepsnsc. If service n°85 is available, "
        "this file shall be present.")
    SB_BEGIN(MSIM_SB_UL_NAS_COUNT, "003.001", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_UST_STATUS_TABLE)
        COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 33.401.")
        SEQ_OF(ul_nas_count, "Uplink NAS count", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_UL_NAS_COUNT_LEN)
        FILLER(FILLER_FIXED, 24)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_DL_NAS_COUNT")
    COMMENT(COMMENT_TEXT, "This sub-block contains downlink NAS count "
        "from EFepsnsc. If service n°85 is available, "
        "this file shall be present.")
    SB_BEGIN(MSIM_SB_DL_NAS_COUNT, "003.001", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_UST_STATUS_TABLE)
        COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 33.401.")
        SEQ_OF(dl_nas_count, "Downlink NAS count", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_DL_NAS_COUNT_LEN)
        FILLER(FILLER_FIXED, 24)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_NAS_SECUR_ALGOR_IDS")
    COMMENT(COMMENT_TEXT, "This sub-block contains identifiers of selected NAS "
        "integrity and encryption algorithms from EFepsnsc. If service n°85 "
        "is available, this file shall be present.")
    SB_BEGIN(MSIM_SB_NAS_SECUR_ALGOR_IDS, "003.001", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_UST_STATUS_TABLE)
        COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 33.401 and TS 24.301.")
        SEQ_OF(nas_secur_algor_ids,
            "Identifiers of selected NAS integrity and encryption algorithms",
            AUTOGEN_SEQ_BYTE_HEX, MSIM_SB_NAS_SECUR_ALGOR_IDS_LEN)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_LAST_RPLMNSI")
    COMMENT(COMMENT_TEXT, "This sub-block contains an indication "
        "for the selection of the RPLMN or the home network at switch on, "
        "or following recovery from lack of coverage.")
    SB_BEGIN(MSIM_SB_LAST_RPLMNSI, "005.000", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        COMMENT(COMMENT_TEXT, "Selection of the RPLMN or the home network")
        VALUE_CONST(lrplmnsi, "Last RPLMN Selection Indication",
            MSIM_LAST_RPLMNSI)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_SMS_STATUS")
    SB_BEGIN(MSIM_SB_SMS_STATUS, "005.002", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        VALUE(8, BE, sms_status, "Status byte of the record in EFsms", HEX)
        FILLER(FILLER_FIXED, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_SMS_REMAINDER")
    SB_BEGIN(MSIM_SB_SMS_REMAINDER, "005.002", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        SEQ_OF(sms_remainder, "Remainder of a record in EFsms",
            AUTOGEN_SEQ_BYTE_HEX, MSIM_SMS_REMAINDER_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_SMS_INDEX")
    SB_BEGIN(MSIM_SB_SMS_INDEX, "005.002", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        VALUE_CONST(read_type, "Read type", MSIM_READ_TYPE)
        VALUE(16, BE, index, "Record number in EFsms", HEX)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_SMS_QUERY")
    SB_BEGIN(MSIM_SB_SMS_QUERY, "005.002", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_SMS_QUERY_STATUS)
        VALUE_CONST(query_type, "Query type", MSIM_QUERY_TYPE)
        COMMENT(COMMENT_TEXT, "Query starting point in request. "
            "Query result in response.")
        VALUE(16, BE, location, "Record number in EFsms", HEX)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SB_SMS_LOCATION_COUNT")
    SB_BEGIN(MSIM_SB_SMS_LOCATION_COUNT, "005.002", "")
        MSIM_SB_16_LONG
        VALUE_CONST(Status, "Status", MSIM_SB_STA_STATUS)
        FILLER(FILLER_FIXED, 8)
        VALUE(16, BE, location_count, "Number of records in EFsms", HEX)
    SB_END

    /* --------------------------------------------------------------------- */
    /* Messages                                                              */
    /* --------------------------------------------------------------------- */

    /* MSIM_AUTHENTICATION */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_AUTHENTICATION_REQ")
    COMMENT(COMMENT_TEXT, "This message allows a client to perform "
        "authentication on the [U]MSIM card.")
    MSG_BEGIN(MSIM_AUTHENTICATION_REQ, MESSAGE_REQ, "", "")
        MSIM_MSG_HDR
        VALUE_CONST(ServiceType, "Service Type", MSIM_AUTH_SERVICE_TYPE_TABLE)
        REFERENCE(8, BE, NoOfSubBlocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(MSIM_SB_RAND_PARAMS)
            SB_LST_ENTRY(MSIM_SB_UMTS_AUTN_PARAMS)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_KSI)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_KSI)
            SB_LST_ENTRY(MSIM_SB_CIPHERING_KEY_SNR)
            SB_LST_ENTRY(MSIM_SB_GPRS_CIPHERING_KEY_SNR)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_AUTHENTICATION_RESP")
    COMMENT(COMMENT_TEXT, "This message returns the result of the "
        "authentication on the [U]SIM card.")
    MSG_BEGIN(MSIM_AUTHENTICATION_RESP, MESSAGE_RESP, "", "")
        MSIM_MSG_HDR
        VALUE_CONST(ServiceType, "Service Type", MSIM_AUTH_SERVICE_TYPE_TABLE)
        VALUE_CONST(Status, "Status", MSIM_AUTHENTIFICATION_STATUS)
        FILLER(FILLER_FIXED, 24)
        REFERENCE(8, BE, NoOfSubBlocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(MSIM_SB_RES_PARAMS)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_INTEGRITY_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_KSI)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_INTEGRITY_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_KSI)
            SB_LST_ENTRY(MSIM_SB_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_CIPHERING_KEY_SNR)
            SB_LST_ENTRY(MSIM_SB_GPRS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_GPRS_CIPHERING_KEY_SNR)
            SB_LST_ENTRY(MSIM_SB_UMTS_AUTN_FAIL_PARAMS)
            SB_LST_ENTRY(MSIM_SB_RAND_PARAMS)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(MSIM_AUTHENTICATION_REQ, MSIM_AUTHENTICATION_RESP)


    /* MSIM_CS_READ - MSIM_ST_CS_DATA_READ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    COMMENT(COMMENT_TEXT, "This message is used to read specific information "
        "for CS subsystem. It is possible to request any number of "
        "sub-blocks.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "MSIM_ST_CS_DATA_READ_ALL_REQ.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "MSIM_ST_CS_DATA_READ_ALL_GSS_REQ.")
    SUB_MSG_BEGIN(MSIM_ST_CS_DATA_READ_REQ, MSIM_CS_READ_REQ, MESSAGE_REQ, "",
        "")
        SUB_MSG_REQ
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Block IDs", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCK_IDS, SubblockID, "Sub Block IDs", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(MSIM_SB_ACC)
            SB_LST_ENTRY(MSIM_SB_ECC)
            SB_LST_ENTRY(MSIM_SB_FORBIDDEN_PLMNS)
            SB_LST_ENTRY(MSIM_SB_HPLMN)
            SB_LST_ENTRY(MSIM_SB_HPLMN_SEARCH)
            SB_LST_ENTRY(MSIM_SB_LAI)
            SB_LST_ENTRY(MSIM_SB_LOC_UPD_STATUS)
            SB_LST_ENTRY(MSIM_SB_OPERATOR_PLMN)
            SB_LST_ENTRY(MSIM_SB_USER_PLMN)
            SB_LST_ENTRY(MSIM_SB_HOME_PLMN)
            SB_LST_ENTRY(MSIM_SB_PLMN_SELECTOR)
            SB_LST_ENTRY(MSIM_SB_EQUIVALENT_HPLMNS)
            SB_LST_ENTRY(MSIM_SB_IMSI)
            SB_LST_ENTRY(MSIM_SB_TMSI)
            SB_LST_ENTRY(MSIM_SB_GPRS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_GPRS_CIPHERING_KEY_SNR)
            SB_LST_ENTRY(MSIM_SB_GPRS_RAI)
            SB_LST_ENTRY(MSIM_SB_GPRS_RAUS)
            SB_LST_ENTRY(MSIM_SB_GPRS_TMSI)
            SB_LST_ENTRY(MSIM_SB_GPRS_TMSI_SIGN_VALUE)
            SB_LST_ENTRY(MSIM_SB_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_CIPHERING_KEY_SNR)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_KSI)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_INTEGRITY_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_KSI)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_INTEGRITY_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_START_PS)
            SB_LST_ENTRY(MSIM_SB_UMTS_START_CS)
            SB_LST_ENTRY(MSIM_SB_UMTS_START_MAX)
            SB_LST_ENTRY_VER(MSIM_SB_CARD_TYPE,"003.000", "")
            SB_LST_ENTRY_VER(MSIM_SB_SIMLOCK_STATUS,"003.000", "")
            SB_LST_ENTRY_VER(MSIM_SB_EHPLMN_DISPLAY_MODE, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_GUTI, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_TAI, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_EPS_UPD_STATUS, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_ASME_KSI, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_ASME_KEY, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_UL_NAS_COUNT, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_DL_NAS_COUNT, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_NAS_SECUR_ALGOR_IDS, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_RAT_MODE,"004.000", "")
            SB_LST_ENTRY_VER(MSIM_SB_LAST_RPLMNSI, "005.000", "")
        SB_LST_REF_END
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_CS_READ_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_CS_DATA_READ_RESP_STR")
    COMMENT(COMMENT_TEXT, "This message returns information to CS subsystem.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "MSIM_ST_CS_DATA_READ_ALL_GSS_REQ.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "MSIM_ST_CS_DATA_READ_LIMITED_GSS_REQ.")
    SUB_MSG_BEGIN(MSIM_ST_CS_DATA_READ_REQ, MSIM_CS_READ_RESP, MESSAGE_RESP,
        "", "")
        SUB_MSG_REQ
        VALUE_CONST(Status, "Status", MSIM_CS_READ_RESP_STATUS)
        FILLER(FILLER_FIXED, 24)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(MSIM_SB_ACC)
            SB_LST_ENTRY(MSIM_SB_ECC)
            SB_LST_ENTRY(MSIM_SB_FORBIDDEN_PLMNS)
            SB_LST_ENTRY(MSIM_SB_HPLMN)
            SB_LST_ENTRY(MSIM_SB_HPLMN_SEARCH)
            SB_LST_ENTRY(MSIM_SB_LAI)
            SB_LST_ENTRY(MSIM_SB_LOC_UPD_STATUS)
            SB_LST_ENTRY(MSIM_SB_OPERATOR_PLMN)
            SB_LST_ENTRY(MSIM_SB_USER_PLMN)
            SB_LST_ENTRY(MSIM_SB_HOME_PLMN)
            SB_LST_ENTRY(MSIM_SB_PLMN_SELECTOR)
            SB_LST_ENTRY(MSIM_SB_EQUIVALENT_HPLMNS)
            SB_LST_ENTRY(MSIM_SB_IMSI)
            SB_LST_ENTRY(MSIM_SB_TMSI)
            SB_LST_ENTRY(MSIM_SB_GPRS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_GPRS_CIPHERING_KEY_SNR)
            SB_LST_ENTRY(MSIM_SB_GPRS_RAI)
            SB_LST_ENTRY(MSIM_SB_GPRS_RAUS)
            SB_LST_ENTRY(MSIM_SB_GPRS_TMSI)
            SB_LST_ENTRY(MSIM_SB_GPRS_TMSI_SIGN_VALUE)
            SB_LST_ENTRY(MSIM_SB_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_CIPHERING_KEY_SNR)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_KSI)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_INTEGRITY_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_KSI)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_INTEGRITY_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_START_PS)
            SB_LST_ENTRY(MSIM_SB_UMTS_START_CS)
            SB_LST_ENTRY(MSIM_SB_UMTS_START_MAX)
            SB_LST_ENTRY_VER(MSIM_SB_CARD_TYPE,"003.000", "")
            SB_LST_ENTRY_VER(MSIM_SB_SIMLOCK_STATUS,"003.000", "")
            SB_LST_ENTRY_VER(MSIM_SB_EHPLMN_DISPLAY_MODE, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_GUTI, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_TAI, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_EPS_UPD_STATUS, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_ASME_KSI, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_ASME_KEY, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_UL_NAS_COUNT, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_DL_NAS_COUNT, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_NAS_SECUR_ALGOR_IDS, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_RAT_MODE,"004.000", "")
            SB_LST_ENTRY_VER(MSIM_SB_LAST_RPLMNSI, "005.000", "")
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_CS_DATA_READ_REQ, MSIM_CS_READ_REQ,
        MSIM_ST_CS_DATA_READ_REQ, MSIM_CS_READ_RESP)


    /* MSIM_CS_READ - MSIM_ST_CS_STATUS */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_CS_STATUS_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_CS_STATUS_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message reads the status of the MSIM server.")
    SUB_MSG_BEGIN(MSIM_ST_CS_STATUS_REQ,  MSIM_CS_READ_REQ, MESSAGE_REQ,
        "", "")
        SUB_MSG_REQ
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_CS_STATUS_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_CS_STATUS_RESP_STR")
    COMMENT(COMMENT_TEXT, "This message returns the status of the MSIM server."
        " Number of sub-blocks are returned.")
    SUB_MSG_BEGIN(MSIM_ST_CS_STATUS_REQ,  MSIM_CS_READ_RESP, MESSAGE_RESP, "",
        "")
        SUB_MSG_RESP(MSIM_CS_READ_RESP_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_CS_STATUS_REQ, MSIM_CS_READ_REQ,
        MSIM_ST_CS_STATUS_REQ, MSIM_CS_READ_RESP)

    /* MSIM_CS_READ - MSIM_ST_CS_DATA_READ_ALL_GSS */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    COMMENT(COMMENT_TEXT, "This message reads all possible sub-blocks for CS "
        "subsystem.")
    SUB_MSG_BEGIN(MSIM_ST_CS_DATA_READ_ALL_GSS_REQ, MSIM_CS_READ_REQ,
        MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END



    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    COMMENT(COMMENT_TEXT, "This message returns all possible sub-blocks for CS"
        " subsystem.")
    SUB_MSG_BEGIN(MSIM_ST_CS_DATA_READ_ALL_GSS_REQ, MSIM_CS_READ_RESP,
        MESSAGE_RESP, "", "")
        SUB_MSG_RESP(MSIM_CS_READ_RESP_STATUS)
        FILLER(FILLER_FIXED, 24)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(MSIM_SB_ACC)
            SB_LST_ENTRY(MSIM_SB_FORBIDDEN_PLMNS)
            SB_LST_ENTRY(MSIM_SB_HPLMN)
            SB_LST_ENTRY(MSIM_SB_HPLMN_SEARCH)
            SB_LST_ENTRY(MSIM_SB_LAI)
            SB_LST_ENTRY(MSIM_SB_LOC_UPD_STATUS)
            SB_LST_ENTRY(MSIM_SB_HOME_PLMN)
            SB_LST_ENTRY(MSIM_SB_EQUIVALENT_HPLMNS)
            SB_LST_ENTRY(MSIM_SB_IMSI)
            SB_LST_ENTRY(MSIM_SB_TMSI)
            SB_LST_ENTRY(MSIM_SB_GPRS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_GPRS_CIPHERING_KEY_SNR)
            SB_LST_ENTRY(MSIM_SB_GPRS_RAI)
            SB_LST_ENTRY(MSIM_SB_GPRS_RAUS)
            SB_LST_ENTRY(MSIM_SB_GPRS_TMSI)
            SB_LST_ENTRY(MSIM_SB_GPRS_TMSI_SIGN_VALUE)
            SB_LST_ENTRY(MSIM_SB_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_CIPHERING_KEY_SNR)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_KSI)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_INTEGRITY_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_KSI)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_INTEGRITY_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_START_PS)
            SB_LST_ENTRY(MSIM_SB_UMTS_START_CS)
            SB_LST_ENTRY(MSIM_SB_UMTS_START_MAX)
            SB_LST_ENTRY_VER(MSIM_SB_CARD_TYPE,"003.000", "")
            SB_LST_ENTRY_VER(MSIM_SB_SIMLOCK_STATUS,"003.000", "")
            SB_LST_ENTRY_VER(MSIM_SB_EHPLMN_DISPLAY_MODE, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_GUTI, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_TAI, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_EPS_UPD_STATUS, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_ASME_KSI, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_ASME_KEY, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_UL_NAS_COUNT, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_DL_NAS_COUNT, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_NAS_SECUR_ALGOR_IDS, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_RAT_MODE,"004.000", "")
            SB_LST_ENTRY_VER(MSIM_SB_LAST_RPLMNSI, "005.000", "")
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_CS_DATA_READ_ALL_GSS_REQ, MSIM_CS_READ_REQ,
        MSIM_ST_CS_DATA_READ_ALL_GSS_REQ, MSIM_CS_READ_RESP)


    /* MSIM_CS_READ - MSIM_ST_CS_DATA_READ_LIMITED_GSS_REQ */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    COMMENT(COMMENT_TEXT, "This message reads limited service sub-blocks for"
        " CS subsystem.")
    SUB_MSG_BEGIN(MSIM_ST_CS_DATA_READ_LIMITED_GSS_REQ, MSIM_CS_READ_REQ,
        MESSAGE_REQ, "005.001", "")
        SUB_MSG_REQ
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    COMMENT(COMMENT_TEXT, "This message returns limited service sub-blocks for"
        " CS subsystem.")
    SUB_MSG_BEGIN(MSIM_ST_CS_DATA_READ_LIMITED_GSS_REQ, MSIM_CS_READ_RESP,
        MESSAGE_RESP, "005.001", "")
        SUB_MSG_RESP(MSIM_CS_READ_RESP_STATUS)
        FILLER(FILLER_FIXED, 24)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(MSIM_SB_LAI)
            SB_LST_ENTRY(MSIM_SB_LOC_UPD_STATUS)
            SB_LST_ENTRY(MSIM_SB_IMSI)
            SB_LST_ENTRY(MSIM_SB_TMSI)
            SB_LST_ENTRY(MSIM_SB_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_CIPHERING_KEY_SNR)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_KSI)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_CIPHERING_KEY)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_INTEGRITY_KEY)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_CS_DATA_READ_LIMITED_GSS_REQ, MSIM_CS_READ_REQ,
        MSIM_ST_CS_DATA_READ_LIMITED_GSS_REQ, MSIM_CS_READ_RESP)


    /* MSIM_CS_WRITE - MSIM_ST_CS_DATA_WRITE */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_CS_WRITE_REQ")
    COMMENT(COMMENT_TEXT, "This message allows a client to update data on the "
        "[U]SIM card.")
    MSG_BEGIN(MSIM_CS_WRITE_REQ, MESSAGE_REQ, "", "")
        MSIM_MSG_HDR
        FILLER(FILLER_FIXED, 8)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N,
            ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(MSIM_SB_TMSI)
            SB_LST_ENTRY(MSIM_SB_LAI)
            SB_LST_ENTRY(MSIM_SB_LOC_UPD_STATUS)
            SB_LST_ENTRY(MSIM_SB_FORBIDDEN_PLMNS)
            SB_LST_ENTRY(MSIM_SB_GPRS_CIPHERING_KEY_SNR)
            SB_LST_ENTRY(MSIM_SB_GPRS_RAI)
            SB_LST_ENTRY(MSIM_SB_GPRS_RAUS)
            SB_LST_ENTRY(MSIM_SB_GPRS_TMSI)
            SB_LST_ENTRY(MSIM_SB_GPRS_TMSI_SIGN_VALUE)
            SB_LST_ENTRY(MSIM_SB_CIPHERING_KEY_SNR)
            SB_LST_ENTRY(MSIM_SB_UMTS_CS_KSI)
            SB_LST_ENTRY(MSIM_SB_UMTS_PS_KSI)
            SB_LST_ENTRY(MSIM_SB_UMTS_START_CS)
            SB_LST_ENTRY(MSIM_SB_UMTS_START_PS)
            SB_LST_ENTRY_VER(MSIM_SB_GUTI, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_TAI, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_EPS_UPD_STATUS, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_ASME_KSI, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_ASME_KEY, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_UL_NAS_COUNT, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_DL_NAS_COUNT, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_NAS_SECUR_ALGOR_IDS, "003.001", "")
            SB_LST_ENTRY_VER(MSIM_SB_GPRS_CIPHERING_KEY, "005.000", "")
            SB_LST_ENTRY_VER(MSIM_SB_UMTS_PS_CIPHERING_KEY, "005.000", "")
            SB_LST_ENTRY_VER(MSIM_SB_UMTS_PS_INTEGRITY_KEY, "005.000", "")
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_CS_WRITE_RESP")
    COMMENT(COMMENT_TEXT, "This message returns the result of updating data on"
        " the [U]SIM card.")
    MSG_BEGIN(MSIM_CS_WRITE_RESP, MESSAGE_RESP, "", "")
        MSIM_MSG_HDR
        VALUE_CONST(Status, "Status", MSIM_CS_WRITE_STATUS)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT(COMMENT_TEXT, "The returned sub-blocks includes only the "
            "Sub-Block ID and the result of updating the data. One sub-block "
            "is returned for each sub-block in MSIM_CS_WRITE_REQ("
            "MSIM_ST_CS_DATA_WRITE_REQ).")
        SEQ_OF_REF(sub_blocks, "Sub Block", MSIM_SB_CS_WRITE_RESP_SB, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
    MSG_END

    MSG_PAIR(MSIM_CS_WRITE_REQ, MSIM_CS_WRITE_RESP)


    /* MSIM_DATA_SIZES */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_DataSizeReadReq")
    COMMENT(COMMENT_TEXT, "This command reads the length of various data "
        "field and the number of records of formatted data fields.")
    MSG_BEGIN(MSIM_DATA_SIZES_REQ, MESSAGE_REQ, "", "")
        PROPERTY(PROPERTY_HTML_DONT_GENERATE)
        SEQ_OF(Req, "Req", MSIM_REQUEST, 1)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(ServiceType, "Service Type", MSIM_READ_SERVICE_TYPE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        FILLER(FILLER_FIXED, 8)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_DataSizeReadResp")
    COMMENT(COMMENT_TEXT, "This command returns the value of requested "
        "datafield.")
    MSG_BEGIN(MSIM_DATA_SIZES_RESP, MESSAGE_RESP, "", "")
        PROPERTY(PROPERTY_HTML_DONT_GENERATE)
        SEQ_OF(Resp, "Resp", MSIM_INFO_RESPONSE, 1)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(ServiceType, "Service Type", MSIM_READ_SERVICE_TYPE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Status, "Status", MSIM_READ_STATUS)
        COMMENT(COMMENT_TEXT, "Value of requested data. ServiceType give the "
            "type of data.")
        VALUE(8, BE, DataSize, "Data Size", DEC)
        FILLER(FILLER_FIXED, 24)
    MSG_END

    MSG_PAIR(MSIM_DATA_SIZES_REQ, MSIM_DATA_SIZES_RESP)


    /* MSIM_STATUS */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_CardStatus_Req")
    COMMENT(COMMENT_TEXT, "This message allows a client to request the status "
        "of the [U]SIM card. The status indicates if card is connected or or "
        "disconncected.")
    MSG_BEGIN(MSIM_STATUS_REQ, MESSAGE_REQ, "", "")
        MSIM_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_CardStatus_Resp")
    COMMENT(COMMENT_TEXT, "This message returns the status of the [U]SIM card."
        " The status indicates if card is connected or disconncected.")
    MSG_BEGIN(MSIM_STATUS_RESP, MESSAGE_RESP, "", "")
        MSIM_MSG_HDR
        VALUE_CONST(Status, "Status", MSIM_STATUS_STATUS)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "bool8")
        COMMENT(COMMENT_TEXT, "CardTypeRead is TRUE if card is connected and "
            "FALSE if card is disconnected.")
        VALUE_CONST(CardTypeRead, "Card Type Read", TRUE_FALSE)
        COMMENT(COMMENT_TEXT, "Cardtype is 'UE operation mode'(USIM) or "
            "'MS operation mode'(SIM) byte from the EFad file status.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "CardType is 0xFF if CardTypeRead is FALSE.")
        VALUE_CONST(Cardtype, "Card Type", MSIM_SB_CARD_TYPE_TABLE)
        FILLER(FILLER_FIXED, 24)
    MSG_END

    MSG_PAIR(MSIM_STATUS_REQ, MSIM_STATUS_RESP)


    /* MSIM_SMS - READ_PARAMETER */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SMS_ReadParam_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_SMS_READPARAM_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message requests a SMS parameters from a given"
        " location in EFsmsp.")
    SUB_MSG_BEGIN(MSIM_ST_READ_PARAMETER, MSIM_SMS_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        COMMENT(COMMENT_TEXT, "Location where to get SMS parameters in "
            "EFsmsp.")
        VALUE(8, BE, LocationNumber, "Location Number", DEC)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SMS_ReadParam_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_SMS_READPARAM_RESP_STR")
    SUB_MSG_BEGIN(MSIM_ST_READ_PARAMETER, MSIM_SMS_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_REQ
        VALUE_CONST(Status, "Status", MSIM_SB_APP_SELECTION_STATUS)
        COMMENT(COMMENT_TEXT, "Location where SMS parameters in EFsmsp are "
            "fetched.")
        VALUE(8, BE, LocationNumber, "Location Number", DEC)
        COMMENT(COMMENT_TEXT, "See 3GPP TS 51.011 or 31.102 for EFsmsp. Value "
            "is undefined if status is not MSIM_STA_OK.")
        VALUE(8, BE, ParametersIndicators, "Parameters Indicators", HEX)
        COMMENT(COMMENT_TEXT, "See 3GPP TS 23.040 for TP-PID. Value is "
            "undefined if status is not MSIM_STA_OK.")
        VALUE(8, BE, ProtocolID, "Protocol ID", HEX)
        COMMENT(COMMENT_TEXT, "See 3GPP TS 23.040 for TP-DCS. Value is "
            "undefined if status is not MSIM_STA_OK.")
        VALUE(8, BE, DataCodingScheme, "Data Coding Scheme", HEX)
        COMMENT(COMMENT_TEXT, "See 3GPP TS 23.040 for TP-VP. Value is "
            "undefined if status is not MSIM_STA_OK.")
        VALUE(8, BE, ValidityPeriod, "Validity Period", HEX)
        FILLER(FILLER_FIXED, 24)
        COMMENT(COMMENT_TEXT, "See 3GPP TS 23.040 for TP-DA. Value is "
            "undefined if status is not MSIM_STA_OK.")
        SEQ_OF(DestinationAddress, "Destination Address", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_SMS_ADDRESS_MAX_LEN)
        COMMENT(COMMENT_TEXT, "See 3GPP TS 24.011 for RP-DA. Value is "
            "undefined if status is not MSIM_STA_OK.")
        SEQ_OF(ServiceCenterAddress, "Service Center Address",
            AUTOGEN_SEQ_BYTE_HEX, MSIM_SMS_ADDRESS_MAX_LEN)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_READ_PARAMETER, MSIM_SMS_REQ, MSIM_ST_READ_PARAMETER,
        MSIM_SMS_RESP)


    /* MSIM_SMS - UPDATE_PARAMETER */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SMS_UpdateParam_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_SMS_UPDATEPARAM_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message updates a SMS parameters to given"
        " location in EFsmsp.")
    SUB_MSG_BEGIN(MSIM_ST_UPDATE_PARAMETER, MSIM_SMS_REQ, MESSAGE_REQ,
        "002.002", "")
        SUB_MSG_REQ
        COMMENT(COMMENT_TEXT, "Location where SMS parameters in EFsmsp are "
            "updated.")
        VALUE(8, BE, LocationNumber, "Location Number", DEC)
        COMMENT(COMMENT_TEXT, "See 3GPP TS 51.011 or 31.102 for EFsmsp.")
        VALUE(8, BE, ParametersIndicators, "Parameters Indicators", HEX)
        COMMENT(COMMENT_TEXT, "See 3GPP TS 23.040 for TP-PID.")
        VALUE(8, BE, ProtocolID, "Protocol ID", HEX)
        COMMENT(COMMENT_TEXT, "See 3GPP TS 23.040 for TP-DCS.")
        VALUE(8, BE, DataCodingScheme, "Data Coding Scheme", HEX)
        COMMENT(COMMENT_TEXT, "See 3GPP TS 23.040 for TP-VP.")
        VALUE(8, BE, ValidityPeriod, "Validity Period", HEX)
        COMMENT(COMMENT_TEXT, "See 3GPP TS 23.040 for TP-DA.")
        SEQ_OF(DestinationAddress, "Destination Address", AUTOGEN_SEQ_BYTE_HEX,
            MSIM_SMS_ADDRESS_MAX_LEN)
        COMMENT(COMMENT_TEXT, "See 3GPP TS 24.011 for RP-DA.")
        SEQ_OF(ServiceCenterAddress, "Service Center Address",
            AUTOGEN_SEQ_BYTE_HEX, MSIM_SMS_ADDRESS_MAX_LEN)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SMS_UpdateParam_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_SMS_UPDATEPARAM_RESP_STR")
    SUB_MSG_BEGIN(MSIM_ST_UPDATE_PARAMETER, MSIM_SMS_RESP, MESSAGE_RESP,
        "002.002", "")
        SUB_MSG_REQ
        VALUE_CONST(Status, "Status", MSIM_SMS_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_UPDATE_PARAMETER, MSIM_SMS_REQ,
        MSIM_ST_UPDATE_PARAMETER, MSIM_SMS_RESP)


    /* MSIM_SMS - READ_STATUS */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SMS_ReadStatus_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_SMS_READSTATUS_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message reads SMS status (message reference "
        "and memory capacity exceeded flag) from EFsmss.")
    SUB_MSG_BEGIN(MSIM_ST_READ_STATUS, MSIM_SMS_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SMS_ReadStatus_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_SMS_READSTATUS_RESP_STR")
    COMMENT(COMMENT_TEXT, "This message returns SMS status (message reference "
        "and memory capacity exceeded flag) from EFsmss.")
    SUB_MSG_BEGIN(MSIM_ST_READ_STATUS, MSIM_SMS_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP(MSIM_SB_APP_SELECTION_STATUS)
        COMMENT(COMMENT_TEXT, "TP-Message-Reference from last SMS. See 3GPP "
            "23.040. Value is undefined if status is not MSIM_STA_OK.")
        VALUE(8, BE, MessageReference, "Message Reference", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "bool8")
        COMMENT(COMMENT_TEXT, "True: Memory capacity available. See 3GPP TS "
            "51.011 or 31.102. Value is undefined if status is not "
            "MSIM_STA_OK.")
        VALUE(8, BE, MessageCapacityExceeded, "Message Capacity Exceeded", HEX)
        FILLER(FILLER_FIXED, 16)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_READ_STATUS, MSIM_SMS_REQ, MSIM_ST_READ_STATUS,
        MSIM_SMS_RESP)


    /* MSIM_SMS - WRITE_STATUS */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SMS_WriteStatus_req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_SMS_WRITESTATUS_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message writes SMS status (message reference "
        "and memory capacity exceeded flag) to EFsmss on [U]SIM.")
    SUB_MSG_BEGIN(MSIM_ST_WRITE_STATUS, MSIM_SMS_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        COMMENT(COMMENT_TEXT, "TP-Message-Reference from last SMS. See 3GPP "
            "TS 23.040.")
        VALUE(8, BE, MessageReference, "Message Reference", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "bool8")
        COMMENT(COMMENT_TEXT, "True: Memory capacity available. See 3GPP TS "
            "51.011 or 31.102.")
        VALUE(8, BE, MessageCapacityExceeded, "Message Capacity Exceeded", HEX)
        FILLER(FILLER_FIXED, 24)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SMS_WriteStatus_resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_SMS_WRITESTATUS_RESP_STR")
    COMMENT(COMMENT_TEXT, "This message returns the result of writing SMS "
        "status (message reference and memory capacity exceeded flag) to "
        "EFsmss on [U]SIM.")
    SUB_MSG_BEGIN(MSIM_ST_WRITE_STATUS, MSIM_SMS_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP(MSIM_SMS_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_WRITE_STATUS, MSIM_SMS_REQ, MSIM_ST_WRITE_STATUS,
        MSIM_SMS_RESP)


    /* MSIM_DYNAMIC_FLAGS - WRITE_DYN_FLAGS */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_DynFlagsWrite_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_DYNFLAGSWRITE_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message allows a client to write dynamic flags"
        " into the Orange-directory on [U]SIM.")
    SUB_MSG_BEGIN(MSIM_ST_WRITE_DYN_FLAGS, MSIM_DYNAMIC_FLAGS_REQ, MESSAGE_REQ,
        "", "")
        SUB_MSG_REQUEST_HDR
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        FILLER(FILLER_FIXED, 8)
        SEQ_OF(DynFlags, "Dynamic Flags", MSIM_INFO_DYNAMIC_FLAGS, 1)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_DynFlagsWrite_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_DYNFLAGSWRITE_RESP_STR")
    COMMENT(COMMENT_TEXT, "This message returns the result of writing dynamic "
        "flags into the Orange-directory on [U]SIM.")
    SUB_MSG_BEGIN(MSIM_ST_WRITE_DYN_FLAGS, MSIM_DYNAMIC_FLAGS_RESP,
        MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(MSIM_NO_STATUS_FROM_SUBSYSTEM)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_WRITE_DYN_FLAGS, MSIM_DYNAMIC_FLAGS_REQ,
        MSIM_ST_WRITE_DYN_FLAGS, MSIM_DYNAMIC_FLAGS_RESP)


    /* MSIM_DYNAMIC_FLAGS - READ_DYN_FLAGS */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_DynFlagsRead_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_DYNFLAGSREAD_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message allows a client to read dynamic flags "
        "from the Orange-directory on [U]SIM.")
    SUB_MSG_BEGIN(MSIM_ST_READ_DYN_FLAGS, MSIM_DYNAMIC_FLAGS_REQ, MESSAGE_REQ,
        "", "")
        SUB_MSG_REQUEST_HDR
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_DynFlagsRead_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_DYNFLAGSREAD_RESP_STR")
    COMMENT(COMMENT_TEXT, "This message returns the dynamic flags from the "
        "Orange-directory on [U]SIM.")
    SUB_MSG_BEGIN(MSIM_ST_READ_DYN_FLAGS, MSIM_DYNAMIC_FLAGS_RESP,
        MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(MSIM_VOICE_MSG_STATUS)
        SEQ_OF(DynFlags, "Dynamic Flags", MSIM_INFO_DYNAMIC_FLAGS, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_READ_DYN_FLAGS, MSIM_DYNAMIC_FLAGS_REQ,
        MSIM_ST_READ_DYN_FLAGS, MSIM_DYNAMIC_FLAGS_RESP)


    /* MSIM_FDN_CHECK */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_FDN_CHECK_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_FDN_CHECK_REQ_STR")
    COMMENT(COMMENT_TEXT,"This message is used request FDN check.")
    MSG_BEGIN(MSIM_FDN_CHECK_REQ, MESSAGE_REQ, "", "")
        MSIM_MSG_HDR
        FILLER(FILLER_FIXED, 8)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlockStart, "Sub Block Start", N,
            ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(MSIM_SB_PHONE_NUMBER_FIELD)
            SB_LST_ENTRY(MSIM_SB_SMS_DEST_ADR)
            SB_LST_ENTRY(MSIM_SB_SMSC_ADR)
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_FDN_CHECK_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_FDN_CHECK_RESP_STR")
    COMMENT(COMMENT_TEXT,"This message returns the result of FDN check.")
    MSG_BEGIN(MSIM_FDN_CHECK_RESP, MESSAGE_RESP, "", "")
        MSIM_MSG_HDR
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(Status, "Status", MSIM_FDN_CHECK_STATUS)
        FILLER(FILLER_FIXED, 24)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 2)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlockStart, "Sub Block Start", N,
            ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(MSIM_SB_PHONE_NUMBER_FIELD)
            SB_LST_ENTRY(MSIM_SB_SMS_DEST_ADR)
            SB_LST_ENTRY(MSIM_SB_SMSC_ADR)
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(MSIM_FDN_CHECK_REQ, MSIM_FDN_CHECK_RESP)


    /* MSIM_CPHS */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_ReadCphsReq")
    COMMENT(COMMENT_TEXT,"This message allows a client to read the Common PCN "
        "HandSet(CPHS) information in EF_6F16 on [U]SIM. CPHS is Orange "
        "specific information.")
    MSG_BEGIN(MSIM_CPHS_REQ, MESSAGE_REQ, "", "")
        MSIM_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_ReadCphsResp")
    COMMENT(COMMENT_TEXT, "This message returns the Common PCN HandSet(CPHS) "
        "information from EF_6F16 on [U]SIM. CPHS is Orange specific "
        "information.")
    MSG_BEGIN(MSIM_CPHS_RESP, MESSAGE_RESP, "", "")
        MSIM_MSG_HDR
        VALUE_CONST(Status, "Status", MSIM_SB_APP_SELECTION_STATUS)
        PROPERTY(PROPERTY_HTML_DONT_GENERATE)
        FILLER(FILLER_FIXED, 8)
        PROPERTY(PROPERTY_HTML_DONT_GENERATE)
        SEQ_OF(OptionalData, "Optional Data", CPHS_OPTIONALS, 1)
        PROPERTY(PROPERTY_HTML_DONT_GENERATE)
        SEQ_OF(CPHS_Data, "CPHS Data", MSIM_SERV_CPHS_STR, 1)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, MailboxNumbInfo, "Mailbox Numb Info", HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "CPHS phase.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0x01: Phase 1.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0x02: Phase 2.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "etc.")
        VALUE(8, BE, phase, "Phase", HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Customer Service Profile (CSP) data-field is "
            "allocated.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "CSP is a list of user accesible services.")
        VALUE(8, BE, csp_allocated, "CSP Allocated", HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Customer Service Profile (CSP) data-field is "
            "active.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "CSP is a list of user accesible services.")
        VALUE(8, BE, csp_active, "CSP Active", HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Service String Table (SST) data-field is "
            "allocated.")
        VALUE(8, BE, service_string_tbl_allocated,
            "Service String Table Allocated", HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Service String Table (SST) data-field is "
            "active.")
        VALUE(8, BE, service_string_tbl_active, "Service String Table Active",
            HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Mailbox numbers data field is allocated.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Mailbox Number is the dialling number to the "
            "Voice Mailbox.")
        VALUE(8, BE, mailbox_numbers_allocated, "Mailbox Numbers Allocated",
            HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Mailbox numbers data field is active.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Mailbox Number is the dialling number to the "
            "Voice Mailbox.")
        VALUE(8, BE, mailbox_numbers_active, "Mailbox Numbers Active", HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Information Number data field is allocated.")
        VALUE(8, BE, inf_nbr_allocated, "Information Number Allocated", HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Information Number data field is active.")
        VALUE(8, BE, inf_nbr_active, "Information Number Active", HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        FILLER(FILLER_FIXED, 24)
    MSG_END

    MSG_PAIR(MSIM_CPHS_REQ, MSIM_CPHS_RESP)


    /* MSIM_READ_TABLE */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_ServiceTableReadReq")
    COMMENT(COMMENT_TEXT, "This message requests the status of a specific "
        "service(s) in the [U]SIM Service Table.")
    MSG_BEGIN(MSIM_READ_TABLE_REQ, MESSAGE_REQ, "", "")
        PROPERTY(PROPERTY_HTML_DONT_GENERATE)
        SEQ_OF(Req, "Req", MSIM_REQUEST, 1)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(ServiceType, "Service Type", MSIM_READ_TABLE_SERVICE_TYPE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        FILLER(FILLER_FIXED, 8)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_ServiceTable_Resp")
    COMMENT(COMMENT_TEXT, "This message returns the status of a specific "
        "service in the [U]SIM Service Table.")
    MSG_BEGIN(MSIM_READ_TABLE_RESP, MESSAGE_RESP, "","")
        PROPERTY(PROPERTY_HTML_DONT_GENERATE)
        SEQ_OF(Resp, "Resp", MSIM_INFO_RESPONSE, 1)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(ServiceType, "Service Type", MSIM_READ_TABLE_SERVICE_TYPE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Status, "Status", MSIM_READ_TABLE_STATUS_TABLE)
    MSG_END

    MSG_PAIR(MSIM_READ_TABLE_REQ, MSIM_READ_TABLE_RESP)


    /* MSIM_CSP */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_ReadCspReq")
    COMMENT(COMMENT_TEXT, "This message allows a client to read the Customer "
        "Service Profile (CSP) for a specific line on [U]SIM card.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "CSP is a list of user accessible Services in "
        "EF_6F15")
    MSG_BEGIN(MSIM_CSP_REQ, MESSAGE_REQ, "", "")
        MSIM_MSG_HDR
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE_CONST(Line, "Line", MSIM_SINGLE_LINE)
        FILLER(FILLER_FIXED, 8)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_ReadCspResp")
    COMMENT(COMMENT_TEXT, "This message returns the Customer Service Profile"
        "(CSP).")
    MSG_BEGIN(MSIM_CSP_RESP, MESSAGE_RESP, "", "")
        MSIM_MSG_HDR
        VALUE_CONST(Status, "Status", MSIM_SB_APP_SELECTION_STATUS)
        FILLER(FILLER_FIXED, 8)
        SEQ_OF(OptionalData, "Optional Data", CSP_OPTIONALS, 1)
        SEQ_OF(CSP_Data, "CSP Data", MSIM_SERV_CSP_STR, 1)
    MSG_END

    MSG_PAIR(MSIM_CSP_REQ, MSIM_CSP_RESP)


    /* MSIM_SAT */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SAT_READ_CBMIDS_Req")
    MSG_BEGIN(MSIM_SAT_REQ, MESSAGE_REQ, "", "")
        MSIM_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SAT_READ_CBMIDS_Resp")
    MSG_BEGIN(MSIM_SAT_RESP, MESSAGE_RESP, "", "005.000")
        MSIM_MSG_HDR
        VALUE_CONST(Status, "Status", MSIM_READ_FIELD_ICC_STATUS)
        REFERENCE(8, BE, EF_CBMID_Count, "EF CBMID Count", N)
        SEQ_OF_REF(EF_CBMID, "EF CBMID", MSIM_INFO_CBMID_STR, N,
            ISIHDR_MARKER_SINGLE_ELEMENT)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SAT_READ_CBMIDS_Resp")
        MSG_BEGIN(MSIM_SAT_RESP, MESSAGE_RESP, "005.000", "")
        MSIM_MSG_HDR
        VALUE_CONST(Status, "Status", MSIM_READ_FIELD_ICC_STATUS)
        REFERENCE(8, BE, EF_CBMID_Count, "EF CBMID Count", N)
        SEQ_OF_REF(cbmid, "CBMID", AUTOGEN_SEQ_WORD_DEC, N,
            ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    MSG_END

    MSG_PAIR(MSIM_SAT_REQ, MSIM_SAT_RESP)


    /* MSIM_REFRESH - MSIM_ST_REFRESH_REGISTER */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_REFRESH_REGISTER_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_REFRESH_REGISTER_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message allows clients during start-up to "
        "register for refresh.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The message contains a list of files that the "
        "client uses together with an indication if the client wants to be "
        "asked for permission before refresh is done or not.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "To keep track of which clients have registered for "
        "refresh, the object ID is retrieved from the message header and "
        "stored in the MSIM Server.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "Note: If client registers several times then the "
        "last registration will remain in effect overriding previous "
        "registrations.")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_REGISTER, MSIM_REFRESH_REQ, MESSAGE_REQ,
        "", "")
        SUB_MSG_REQ
        COMMENT(COMMENT_TEXT, "Number of records to refresh.")
        REFERENCE(8, BE, NumberOfFiles, "Number of Files", N)
        COMMENT(COMMENT_TEXT, "First record")
        SEQ_OF_REF(FileList, "File List", MSIM_REFRESH_FILE_LIST_STR, N,
            ISIHDR_MARKER_ANYSIZE)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_REFRESH_REGISTER_RESP_STR")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_REGISTER, MSIM_REFRESH_RESP, MESSAGE_RESP,
        "", "")
        SUB_MSG_RESP_HDR(MSIM_ST_REFRESH_REGISTER_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_REFRESH_REGISTER, MSIM_REFRESH_REQ,
        MSIM_ST_REFRESH_REGISTER, MSIM_REFRESH_RESP)


    /* MSIM_REFRESH - MSIM_ST_REFRESH_UNREGISTER */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_REFRESH_UNREGISTER_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message allows clients to unregister for "
        "refresh.")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_UNREGISTER, MSIM_REFRESH_REQ, MESSAGE_REQ,
        "", "")
        SUB_MSG_REQ
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_REFRESH_UNREGISTER_RESP_STR")
    COMMENT(COMMENT_TEXT, "This message returns the result of unregister for "
        "refresh.")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_UNREGISTER, MSIM_REFRESH_RESP, MESSAGE_RESP,
        "", "")
        SUB_MSG_RESP_HDR(MSIM_ST_REFRESH_UNREGISTER_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_REFRESH_UNREGISTER, MSIM_REFRESH_REQ,
        MSIM_ST_REFRESH_UNREGISTER, MSIM_REFRESH_RESP)


    /* MSIM_REFRESH_REQ - MSIM_ST_REFRESH_OK */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_REFRESH_OK_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message allows a client to accept execution of"
        " refresh.")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_OK, MSIM_REFRESH_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_REFRESH_OK_RESP_STR")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_OK, MSIM_REFRESH_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(MSIM_ST_REFRESH_PERMISSION_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_REFRESH_OK, MSIM_REFRESH_REQ, MSIM_ST_REFRESH_OK,
        MSIM_REFRESH_RESP)


    /* MSIM_REFRESH - MSIM_ST_REFRESH_NOT_OK */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_REFRESH_NOT_OK_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message allows a client to reject execution of"
        " refresh.")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_NOT_OK, MSIM_REFRESH_REQ, MESSAGE_REQ,
        "", "")
        SUB_MSG_REQ
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_REFRESH_NOT_OK_RESP_STR")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_NOT_OK, MSIM_REFRESH_RESP, MESSAGE_RESP,
        "", "")
        SUB_MSG_RESP_HDR(MSIM_ST_REFRESH_PERMISSION_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_REFRESH_NOT_OK, MSIM_REFRESH_REQ,
        MSIM_ST_REFRESH_NOT_OK, MSIM_REFRESH_RESP)


    /* MSIM_REFRESH_REQ - MSIM_ST_REFRESH_DONE */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_REFRESH_DONE_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message is used by clients to report that "
        "refresh is executed successfully.")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_DONE, MSIM_REFRESH_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_REFRESH_DONE_RESP_STR")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_DONE, MSIM_REFRESH_RESP, MESSAGE_RESP,
        "", "")
        SUB_MSG_RESP_HDR(MSIM_ST_REFRESH_RESULT_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_REFRESH_DONE, MSIM_REFRESH_REQ, MSIM_ST_REFRESH_DONE,
        MSIM_REFRESH_RESP)


    /* MSIM_REFRESH_REQ - MSIM_ST_REFRESH_ERROR */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_REFRESH_ERROR_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message is used by clients to report that "
        "refresh has failed.")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_ERROR, MSIM_REFRESH_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_REFRESH_ERROR_RESP_STR")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_ERROR, MSIM_REFRESH_RESP, MESSAGE_RESP,
        "", "")
        SUB_MSG_RESP_HDR(MSIM_ST_REFRESH_RESULT_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_REFRESH_ERROR, MSIM_REFRESH_REQ,
        MSIM_ST_REFRESH_ERROR, MSIM_REFRESH_RESP)


    /* MSIM_REFRESH_IND - MSIM_ST_REFRESH_REQUESTED */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_REFRESH_REQUESTED_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "tMSIM_REFRESH_NOW_IND")
    COMMENT(COMMENT_TEXT, "This message requests clients for permission to "
        "execute refresh.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The message includes a list of the FileIDs to "
        "refresh. Each client may accept or reject the request.")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_REQUESTED, MSIM_REFRESH_IND, MESSAGE_IND, "",
        "")
        SUB_MSG_REQ
        REFERENCE(8, BE, NumberOfFiles, "Number of Files", N)
        COMMENT(COMMENT_TEXT, "First record")
        SEQ_OF_REF(FileList, "File List", MSIM_REFERSH_FILE_LIST, N,
            ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END


    /* MSIM_REFRESH_IND - MSIM_ST_REFRESH_NOW */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    COMMENT(COMMENT_TEXT, "This message requests a client to start re-reading "
        "data from [U]SIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The message includes a list of the FileIDs to "
        "refresh.")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_NOW, MSIM_REFRESH_IND, MESSAGE_IND, "", "")
        SUB_MSG_REQ
        REFERENCE(8, BE, NumberOfFiles, "Number of Files", N)
        SEQ_OF_REF(FileList, "File List", MSIM_REFERSH_FILE_LIST, N,
            ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END


    /* MSIM_REFRESH_IND - MSIM_ST_REFRESH_CANCELLED */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    COMMENT(COMMENT_TEXT, "This indication informs clients that the refresh "
        "is cancelled.")
    SUB_MSG_BEGIN(MSIM_ST_REFRESH_CANCELLED, MSIM_REFRESH_IND, MESSAGE_IND,
        "", "")
        SUB_MSG_REQ
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END


    /* MSIM_GPRS - MSIM_ST_ACL_STATUS */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_ACL_Status_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_ACL_STATUS_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message requests the status of the ACL feature"
        " in EFust on USIM.")
    SUB_MSG_BEGIN(MSIM_ST_ACL_STATUS, MSIM_GPRS_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_ACL_Status_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_ACL_STATUS_RESP_STR")
    COMMENT(COMMENT_TEXT, "This message returns the status of the ACL feature "
        "in EFust on USIM.")
    SUB_MSG_BEGIN(MSIM_ST_ACL_STATUS, MSIM_GPRS_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_REQ
        COMMENT(COMMENT_TEXT, "Status of the ACL feature in EFust on USIM.")
        VALUE_CONST(status, "Status", MSIM_ST_ACL_STATUS_STATUS_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_ACL_STATUS, MSIM_GPRS_REQ, MSIM_ST_ACL_STATUS,
        MSIM_GPRS_RESP)


    /* MSIM_GPRS - MSIM_ST_CHECK_APN */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_CheckAPN_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_CHECKAPN_REQ_STR")
    COMMENT(COMMENT_TEXT, "This message checks if an APN is available in the "
        "ACL file, EFacl.")
    COMMENT(COMMENT_TEXT, "The format of APN shall follow the APN TLV format "
        "in 3GPP TS 31.102 but without the tag value and length.")
    COMMENT(COMMENT_TEXT, "The length is given in the APNlength field.")
    COMMENT(COMMENT_TEXT, "An example of an APN:5nokia3com")
    SUB_MSG_BEGIN(MSIM_ST_CHECK_APN, MSIM_GPRS_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        COMMENT(COMMENT_TEXT, "Length of APN to check. If length is zero then "
            "they will be checked for the network provided APN.")
        REFERENCE(8, BE, APNLength, "APN Length", N)
        COMMENT(COMMENT_TEXT, "APN to be checked against EFacl.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_DEC, N,
            ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_CheckAPN_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_CHECKAPN_RESP_STR")
    COMMENT(COMMENT_TEXT, "This message returns the result of checking if an "
        "APN is available in the ACL file, EFacl.")
    SUB_MSG_BEGIN(MSIM_ST_CHECK_APN, MSIM_GPRS_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP(MSIM_ST_ACL_CHECK_APN_STATUS_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(MSIM_ST_CHECK_APN, MSIM_GPRS_REQ, SIM_ST_CHECK_APN,
        MSIM_GPRS_RESP)


    /* MSIM_IND */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    MSG_BEGIN(MSIM_IND, MESSAGE_BASE, "", "")
        MSIM_MSG_HDR
        VALUE_CONST(ServiceType, "Service Type", MSIM_IND_ST_TABLE)
        VALUE_CONST(Status, "Status", MSIM_IND_STATUS_TABLE)
        VALUE_CONST(State, "State", MSIM_STATE_TABLE)
        VALUE_CONST(Cause, "Cause", MSIM_CAUSES_TABLE)
        COMMENT(COMMENT_TEXT, "Application on [U]SIM that is active.")
        VALUE(8, BE, ApplicationNumber, "Application Number", HEX)
        FILLER(FILLER_FIXED, 8)
    MSG_END

    /* MSIM_IND - Emergency Call Codes */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_IndEmergencyCalls")
    COMMENT(COMMENT_TEXT, "This message includes the Emergency Call Codes "
        "available in EFecc. ")
    COMMENT(COMMENT_TEXT, "The indication is broadcasted when the MSIM server "
        "is initializing but it can provide ECCs to clients.")
    SUB_MSG_BEGIN(MSIM_ST_EMERGENCY_CODES, MSIM_IND, MESSAGE_IND, "", "")
        SUB_MSG_IND_HDR(MSIM_IND_PREF_LANG_STATUS_TABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(State, "State", MSIM_IND_PREF_LANG_STATE_TABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Cause, "Cause", MSIM_IND_PREF_LANG_CAUSE_TABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT(COMMENT_TEXT, "Application on [U]SIM that is active.")
        VALUE(8, BE, ApplicationNumber, "Application Number", HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        FILLER(FILLER_FIXED, 8)
        COMMENT(COMMENT_TEXT, "If an Emergency Call Code is less than 6 digits"
            " a null terminator is inserted after the last digit. ")
        COMMENT(COMMENT_TEXT, "Due to backward compatibility reasons only the "
            "first 5 ECCs without alpha identifier are sent out in 3G mode.")
        SEQ_OF(EmergCodes, "Emergency Codes", MSIM_EMRG_CALL_CODES,
            ISIHDR_MARKER_ANYSIZE)
    SUB_MSG_END


    /* MSIM_IND - MSIM_ST_ALL_SERVICES */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    SUB_MSG_BEGIN(MSIM_ST_ALL_SERVICES, MSIM_IND, MESSAGE_IND, "", "")
        SUB_MSG_IND_HDR(MSIM_ST_ALL_SERVICES_STATUS_TABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(State, "State", MSIM_STATE_TABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Cause, "Cause", MSIM_IND_PREF_LANG_CAUSE_TABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT(COMMENT_TEXT, "Application on [U]SIM that is active.")
        VALUE(8, BE, ApplicationNumber, "Application Number", HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END


    /* MSIM_IND - MSIM_ST_INFO */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    SUB_MSG_BEGIN(MSIM_ST_INFO, MSIM_IND, MESSAGE_IND, "", "")
        SUB_MSG_IND_HDR(MSIM_ST_INFO_STATUS_TABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(State, "State", MSIM_SERVER_READY_IND_STATE_TABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Cause, "Cause", MSIM_IND_PREF_LANG_CAUSE_TABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT(COMMENT_TEXT, "Application on [U]SIM that is active.")
        VALUE(8, BE, ApplicationNumber, "Application Number", HEX)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        FILLER(FILLER_FIXED, 8)
    SUB_MSG_END


    /* MSIM_SERVER_READY_IND */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    COMMENT(COMMENT_TEXT, "This indication is sent out when the MSIM server is"
        "able to process ISI messages. If client is only interested in knowing"
        " when the MSIM server is ready for providing its services then"
        "it is recommended to use this indication.")
    MSG_BEGIN(MSIM_SERVER_READY_IND, MESSAGE_IND, "", "")
        MSIM_MSG_HDR
        VALUE_CONST(ServiceType, "Service Type",
            MSIM_SERVER_READY_IND_ST_TABLE)
        VALUE_CONST(Status, "Status", MSIM_SERVER_READY_IND_STATUS_TABLE)
        VALUE_CONST(State, "State", MSIM_SERVER_READY_IND_STATE_TABLE)
        VALUE_CONST(Cause, "Cause", MSIM_SERVER_READY_IND_CAUSE_TABLE)
        COMMENT(COMMENT_TEXT, "Application on [U]SIM that is started.")
        VALUE(8, BE, ApplicationNumber, "Application Number", HEX)
        FILLER(FILLER_FIXED, 8)
    MSG_END


    /* MSIM_CS_IND */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_CS_Ind")
    COMMENT(COMMENT_TEXT, "This indication is broadcasted when an event that "
        "is relevant to CS subsystem has occured.")
    MSG_BEGIN(MSIM_CS_IND, MESSAGE_IND, "", "")
        MSIM_MSG_HDR
        COMMENT(COMMENT_TEXT, "or MSIM_SERV_SIM_REMOVED_CS")
        VALUE_CONST(Status, "Status", MSIM_CS_IND_STATUS_TABLE)
        VALUE_CONST(State, "State", MSIM_CS_IND_STATE_TABLE)
        VALUE_CONST(Cause, "Cause", MSIM_CS_IND_CAUSE_TABLE)
        COMMENT(COMMENT_TEXT, "Application on [U]SIM that is active.")
        VALUE(8, BE, ApplicationNumber, "Application Number", HEX)
        FILLER(FILLER_FIXED, 16)
    MSG_END


    /* MSIM_ACL_IND */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_ACL_IND")
    COMMENT(COMMENT_TEXT, "This message indicates a state change of the ACL "
        "feature present in the USIM service table, EFust")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The indication is distributed when the ACL feature "
        "is enabled or disabled and during start-up.")
    MSG_BEGIN(MSIM_ACL_IND, MESSAGE_IND, "", "")
        MSIM_MSG_HDR
        FILLER(FILLER_FIXED, 8)
        COMMENT(COMMENT_TEXT, "Status of ACL feature.")
        VALUE_CONST(Status, "Status", MSIM_ACL_IND_STATUS_TABLE)
    MSG_END


    /* MSIM_IMSI_EQUAL */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_Icc_Equal_Req")
    COMMENT(COMMENT_TEXT, "This message allows a client to compare the content"
        " of the EFiccid file available at current and previous initialization"
        " of the ME.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This indicates if the [U]SIM card has been "
        "changed.")
    MSG_BEGIN(MSIM_IMSI_EQUAL_REQ, MESSAGE_REQ, "", "")
        MSIM_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_Icc_Equal_Resp")
    COMMENT(COMMENT_TEXT, "This message returns the result of EFiccid file "
        "comparison.")
    MSG_BEGIN(MSIM_IMSI_EQUAL_RESP, MESSAGE_RESP, "", "")
        MSIM_MSG_HDR
        VALUE_CONST(Status, "Status", MSIM_IMSI_ICC_EQUAL_STATUS)
        FILLER(FILLER_FIXED, 8)
    MSG_END

    MSG_PAIR(MSIM_IMSI_EQUAL_REQ, MSIM_IMSI_EQUAL_RESP)


    /* MSIM_SMS_STORAGE */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SMS_STORAGE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_SMS_STORAGE_REQ_STR")
    COMMENT(COMMENT_TEXT,"This message is for SMS storage access.")
    MSG_BEGIN(MSIM_SMS_STORAGE_REQ, MESSAGE_REQ, "005.002", "")
        MSIM_MSG_HDR
        VALUE_CONST(ServiceType, "Service Type",
            MSIM_SMS_STORAGE_SERVICE_TYPE_TABLE)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlockStart, "Sub Block Start", N,
            ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY_VER(MSIM_SB_SMS_STATUS,         "005.002", "")
            SB_LST_ENTRY_VER(MSIM_SB_SMS_REMAINDER,      "005.002", "")
            SB_LST_ENTRY_VER(MSIM_SB_SMS_INDEX,          "005.002", "")
            SB_LST_ENTRY_VER(MSIM_SB_SMS_QUERY,          "005.002", "")
            SB_LST_ENTRY_VER(MSIM_SB_SMS_LOCATION_COUNT, "005.002", "")
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tMSIM_SMS_STORAGE_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,
        "SIZE_MSIM_SMS_STORAGE_RESP_STR")
    COMMENT(COMMENT_TEXT,"This message returns the result of SMS storage access.")
    MSG_BEGIN(MSIM_SMS_STORAGE_RESP, MESSAGE_RESP, "005.002", "")
        MSIM_MSG_HDR
        VALUE_CONST(ServiceType, "Service Type",
            MSIM_SMS_STORAGE_SERVICE_TYPE_TABLE)
        VALUE_CONST(Status, "Status", MSIM_SMS_STORAGE_STATUS)
        FILLER(FILLER_FIXED, 24)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlockStart, "Sub Block Start", N,
            ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY_VER(MSIM_SB_SMS_STATUS,         "005.002", "")
            SB_LST_ENTRY_VER(MSIM_SB_SMS_REMAINDER,      "005.002", "")
            SB_LST_ENTRY_VER(MSIM_SB_SMS_INDEX,          "005.002", "")
            SB_LST_ENTRY_VER(MSIM_SB_SMS_QUERY,          "005.002", "")
            SB_LST_ENTRY_VER(MSIM_SB_SMS_LOCATION_COUNT, "005.002", "")
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(MSIM_SMS_STORAGE_REQ, MSIM_SMS_STORAGE_RESP)

RES_END


/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */

#endif /* _MSIM_ISI_M_H_ */

/* End of file msim_isi_m.h */
