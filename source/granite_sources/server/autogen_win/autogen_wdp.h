/*
NOKIA MOBILE PHONES
R&D OULU
MAP SCF



            wdp_isi_m.h
            -------------------
            SW include - ANSI C



Continuus Ref:
--------------
Project:          autogen
%name:            autogen_wdp.h 

%version:         1 

%cvtype:          incl 

%instance:        co_pctls_1 %

%derived_by:      eliasen %

%date_modified:   Tue Nov 23 17:36:40 2004 %

Copyright(c) Nokia Corporation. All rights reserved.

Change History:

VERSION     : 001.004           DRAFT           24-Nov-2004  Stig H. Eliasen
REASON      : included in project
REFERENCE   : -
DESCRIPTION : First version to be released with autogen project

VERSION     : 001.003           DRAFT           17-Apr-2004  Christian J. Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the message macro file
*/

/* ------------------------------------------------------------------------- */


/*  1    ABSTRACT

    1.1    Module type

    Message definition file for autogenen
   

    1.2    Functional description

    This file is the message definition file for the WDP server


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


#ifndef _WDP_ISI_M_H_
#define _WDP_ISI_M_H_


/*  3    CONSTANTS */

/* Message ID's */
#define WDP_HANDLE_REQ                 1
#define WDP_HANDLE_OK_RESP             2
#define WDP_HANDLE_FAIL_RESP           3
#define WDP_HANDLE_RELEASE_REQ         4
#define WDP_HANDLE_RELEASE_RESP        5
#define WDP_UNITDATA_D_REQ             6
#define WDP_UNITDATA_REQ               7
#define WDP_UNITDATA_OK_RESP           8
#define WDP_UNITDATA_FAIL_RESP         9
#define WDP_DATA_SENT_IND              10
#define WDP_ERROR_IND                  11
#define WDP_HANDLE_ABORT_REQ           12
#define WDP_UNITDATA_D_IND             13
#define WDP_UNITDATA_IND               14
#define WDP_HANDLE_SUSPEND_REQ         15
#define WDP_HANDLE_SUSPEND_RESP        16
#define WDP_HANDLE_RESUME_REQ          17
#define WDP_HANDLE_RESUME_RESP         18
#define WDP_PARAM_SET_REQ              23
#define WDP_PARAM_SET_RESP             24
#define WDP_PARAM_IND                  25
#define WDP_SMS_APP_STATUS_IND         26
#define WDP_HANDLE_RESUME_IND          27
#define WDP_PPP_AUTHENTICATION_IND     28
#define WDP_PPP_AUTHENTICATION_REQ     29
#define WDP_PPP_AUTHENTICATION_RESP    30
#define WDP_HANDLE_ABORT_RESP          31
#define WDP_HANDLE_SUSPEND_IND         32

/* Sub block ID's */
#define WDP_PARAM_PPP_AUTH_INFO         1
#define WDP_PARAM_GPRS_INFO             2
#define WDP_PARAM_CLIENT_IP_INFO        3

/* Other constants */
#define WDP_GW_ADDRESS_MAX_LEN              12
#define WDP_ADDRESS_MAX_LEN                 12
#define WDP_HANDLEREQ_SUBBLOCK_MAX           2

/* General defines  */

#define WDP_RECEIVE_PARAM_MAX_LEN           60
#define WDP_SEND_PARAM_MAX_LEN              48
#define WDP_SMS_TDMA_ADDRESS_MAX_LEN        32
#define WDP_APPL_TAG_MAX_LEN                15
#define WDP_ERROR_MAX_LEN                   86
#define WDP_MAX_USERNAME_LEN                32
#define WDP_MAX_PASSWORD_LEN                20
#define WDP_GPRS_MAX_APN_LEN                100 

/*  4    MACROS */

#define WDP_GATEWAY_ADDRESS \
    VALUE_CONST(GWAddressType, "Gateway Address Type", WDP_GATEWAY_ADDRESS_TYPE) \
    STRING(STRING_ASCII, BE, GWAddress, "Gateway Address", WDP_GW_ADDRESS_MAX_LEN)

#define WDP_ADDRESS \
    VALUE_CONST(AddressType, "Address Type", WDP_DESTINATION_ADDRESS_TYPE) \
    VALUE(8, BE, AddressDataLength, "Address Data Length", DEC) \
    STRING(STRING_ASCII, BE, Address, "Address Data", WDP_ADDRESS_MAX_LEN)

#define WDP_APPLICATION_TAG \
    VALUE(8, BE, ApplicationTagLength, "Application Tag Length", DEC) \
    SEQ_OF(ApplicationTag, "Application Tag", WDP_DATA_BYTE, WDP_APPL_TAG_MAX_LEN)

#define WDP_USERNAME \
    VALUE(8, BE, username_length, "Username Length", DEC) \
    STRING(STRING_ASCII, BE, username, "Username", WDP_MAX_USERNAME_LEN)

#define WDP_PASSWORD \
    VALUE(8, BE, password_length, "Password Length", DEC) \
    STRING(STRING_ASCII, BE, password, "Password", WDP_MAX_PASSWORD_LEN)

#define WDP_ACCESSPOINTNAME \
    VALUE(8, BE, apn_name_length, "Length Of The Access Point Name", DEC) \
    STRING(STRING_ASCII, BE, apn_name, "Access Point Name", WDP_GPRS_MAX_APN_LEN)

#define WDP_CLIENT_IP_ADDRESS \
    VALUE(8, BE, client_ip_address_length, "Length Of Client IP Address", DEC) \
    STRING(STRING_ASCII, BE, client_ip_address, "Client IP Address To Be Used", WDP_ADDRESS_MAX_LEN)

#define WDP_SEND_PARAM \
    PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, WDP_SEND_PARAM_MAX_LEN) \
    REFERENCE(8, BE, SendParamLength, "Send Parameters Length", N_PAR) \
    SEQ_OF_REF(SendParameters, "Send Parameters", WDP_DATA_BYTE, N_PAR, ISIHDR_RESERVE_SPACE)

#define WDP_RECEIVE_PARAM \
    PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, WDP_RECEIVE_PARAM_MAX_LEN) \
    REFERENCE(8, BE, ReceiveParamLength, "Receive Parameters Length", N_PAR) \
    SEQ_OF_REF(ReceivParam, "Receive Parameters", WDP_DATA_BYTE, N_PAR, ISIHDR_RESERVE_SPACE)


/* TODO: Change the version whenever the interface is changed */
/* default ISI version */

#ifndef WDP_ISI_VERSION
#define WDP_ISI_VERSION
#define WDP_ISI_VERSION_Z      1
#define WDP_ISI_VERSION_Y      3
#endif

PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,    "")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16, "")

PROPERTY_STRING(PROPERTY_HTML_FILENAME, "")

RES_BEGIN(RESOURCE_ISI, PN_WDP, WDP, "WDP Server", 
    RES_VERSION_STRING(WDP_ISI_VERSION_Z, WDP_ISI_VERSION_Y), TRUE)

    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "DRAFT")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "17-Ape-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Christian Jacob Hansen")
    COMMENT(COMMENT_TEXT, "First version of the interface defined with message macros")
    ISI_VERSION_HISTORY("001.003")


    /* --------------------------------------------------------------------- */
    /* Symbol tables */
    /* --------------------------------------------------------------------- */

    CONST_TBL_BEGIN(WDP_HANDLE_PARAMETER_VALUES, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_ACCEPT_TRUNCATED_MESSAGES,       0x01, "")
        CONST_TBL_ENTRY(WDP_INCLUDE_ALL_RECEIVE_INFO,        0x02, "")
        CONST_TBL_ENTRY(WDP_BEARER_CONN_CONTROL,             0x04, "")
        CONST_TBL_ENTRY(WDP_CHECK_REMOTE_ADDRESS,            0x08, "")
        CONST_TBL_ENTRY(WDP_SHORT_VALIDITY_PERIOD,           0x10, "")
        CONST_TBL_ENTRY(WDP_BEARER_AUTORESUME,               0x20, "")
        CONST_TBL_ENTRY(WDP_LISTEN,                          0x40, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_DESTINATION_ADDRESS_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_ADDRESS_GSM0340,                 0x00, "")
        CONST_TBL_ENTRY(WDP_ADDRESS_INET,                    0x01, "")
        CONST_TBL_ENTRY(WDP_ADDRESS_SERVICE_CODE_ONLY,       0x02, "")
        CONST_TBL_ENTRY(WDP_ADDRESS_INET6,                   0x03, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_AUTHENTICATION_PARAMETER_FLAGS, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_PARAM_PPP_AUTH_PAP,              0x00, "")
        CONST_TBL_ENTRY(WDP_PARAM_PPP_AUTH_CHAP,             0x01, "")
        CONST_TBL_ENTRY(WDP_PARAM_PPP_AUTH_PROMPT,           0x02, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_DATACALL_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_NONTRANSP_ISDN_9600,             0x01, "")
        CONST_TBL_ENTRY(WDP_NONTRANSP_ISDN_14400,            0x02, "")
        CONST_TBL_ENTRY(WDP_NONTRANSP_ISDN_19200,            0x03, "")
        CONST_TBL_ENTRY(WDP_NONTRANSP_ISDN_28800,            0x04, "")
        CONST_TBL_ENTRY(WDP_NONTRANSP_ISDN_38400,            0x05, "")
        CONST_TBL_ENTRY(WDP_NONTRANSP_ISDN_43200,            0x06, "")
        CONST_TBL_ENTRY(WDP_NONTRANSP_ISDN_57600,            0x07, "")
        CONST_TBL_ENTRY(WDP_NONTRANSP_AUTOBAUD,              0x20, "")
        CONST_TBL_ENTRY(WDP_NONTRANSP_9600,                  0x21, "")
        CONST_TBL_ENTRY(WDP_NONTRANSP_14400,                 0x22, "")
        CONST_TBL_ENTRY(WDP_NONTRANSP_19200,                 0x23, "")
        CONST_TBL_ENTRY(WDP_NONTRANSP_28800,                 0x24, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_QOS_PRECEDENCE, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PREC_0,                 0x00, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PREC_1,                 0x01, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PREC_2,                 0x02, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PREC_3,                 0x03, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_QOS_DELAY, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_DELC_0,                 0x00, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_DELC_1,                 0x01, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_DELC_2,                 0x02, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_DELC_3,                 0x03, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_DELC_4,                 0x04, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_QOS_RELIABILITY, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_RELC_0,                 0x00, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_RELC_1,                 0x01, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_RELC_2,                 0x02, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_RELC_3,                 0x03, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_RELC_4,                 0x04, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_RELC_5,                 0x05, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_QOS_PEAK_THROUGHPUT, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PETC_0,                 0x00, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PETC_1,                 0x01, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PETC_2,                 0x02, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PETC_3,                 0x03, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PETC_4,                 0x04, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PETC_5,                 0x05, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PETC_6,                 0x06, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PETC_7,                 0x07, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PETC_8,                 0x08, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_PETC_9,                 0x09, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_QOS_MEAN_THROUGHPUT, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_0,                 0x00, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_1,                 0x01, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_2,                 0x02, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_3,                 0x03, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_4,                 0x04, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_5,                 0x05, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_6,                 0x06, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_7,                 0x07, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_8,                 0x08, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_9,                 0x09, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_10,                0x0A, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_11,                0x0B, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_12,                0x0C, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_13,                0x0D, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_14,                0x0E, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_15,                0x0F, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_16,                0x10, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_17,                0x11, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_18,                0x12, "")
        CONST_TBL_ENTRY(WDP_GPRS_QOS_METC_19,                0x13, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_DATA_COMPRESSION, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_GPRS_PDP_DCOMP_ON,               0x01, "")
        CONST_TBL_ENTRY(WDP_GPRS_PDP_DCOMP_OFF,              0x02, "")
        CONST_TBL_ENTRY(WDP_GPRS_PDP_DCOMP_DEFAULT,          0xFF, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_HEADER_COMPRESSION, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_GPRS_PDP_HCOMP_ON,               0x01, "")
        CONST_TBL_ENTRY(WDP_GPRS_PDP_HCOMP_OFF,              0x02, "")
        CONST_TBL_ENTRY(WDP_GPRS_PDP_HCOMP_DEFAULT,          0xFF, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_GATEWAY_ADDRESS_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_GW_ADDRESS_GSM0411,              0x00, "")
        CONST_TBL_ENTRY(WDP_GW_ADDRESS_NOT_AVAILABLE,        0x01, "")
        CONST_TBL_ENTRY(WDP_GW_ADDRESS_INET,                 0x02, "")
        CONST_TBL_ENTRY(WDP_GW_ADDRESS_INET6,                0x03, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_COMMUNICATION_CHANNELS, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_NPD,                             0x01, "")
        CONST_TBL_ENTRY(WDP_NCSD,                            0x02, "")
        CONST_TBL_ENTRY(WDP_PD,                              0x04, "")
        CONST_TBL_ENTRY(WDP_CSD,                             0x08, "")
        CONST_TBL_ENTRY(WDP_COMM_CHANNEL_SPECIAL,            0x10, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_HANDLE_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_SPECIAL,                         0x01, "")
        CONST_TBL_ENTRY(WDP_DEFAULT,                         0x00, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_ERROR_CODES, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_OK,                              0x00, "")
        CONST_TBL_ENTRY(WDP_MEMORY_FAIL,                     0x01, "")
        CONST_TBL_ENTRY(WDP_PORT_RESERVED,                   0x02, "")
        CONST_TBL_ENTRY(WDP_SEND_FAIL,                       0x03, "")
        CONST_TBL_ENTRY(WDP_HANDLE_FAIL,                     0x04, "")
        CONST_TBL_ENTRY(WDP_COMM_CHANNEL_FAIL,               0x05, "")
        CONST_TBL_ENTRY(WDP_GWADDRESS_FAIL,                  0x06, "")
        CONST_TBL_ENTRY(WDP_ADDRESS_FAIL,                    0x07, "")
        CONST_TBL_ENTRY(WDP_CONNECT_FAIL,                    0x08, "")
        CONST_TBL_ENTRY(WDP_WCMP_ERROR,                      0x09, "")
        CONST_TBL_ENTRY(WDP_BEARER_SUSPENDED,                0x0A, "")
        CONST_TBL_ENTRY(WDP_PARAM_FAIL,                      0x0B, "")
        CONST_TBL_ENTRY(WDP_ICMP_ERROR,                      0x0C, "")
        CONST_TBL_ENTRY(WDP_PD_SUSPENDED,                    0x0D, "")
        CONST_TBL_ENTRY(WDP_ERROR,                           0x0E, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_DATA_CODING_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_8BIT,                            0x00, "")
        CONST_TBL_ENTRY(WDP_7BIT,                            0x01, "")
        CONST_TBL_ENTRY(WDP_UCS2,                            0x02, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_ERROR_CAUSE_BYTES, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_SOCKET_ERROR,                    0x79, "")
        CONST_TBL_ENTRY(WDP_NETWORK_DISCONNECTED,            0x80, "")
        CONST_TBL_ENTRY(WDP_NETWORK_CSD_BUSY,                0x81, "")
        CONST_TBL_ENTRY(WDP_NETWORK_CSD_NO_ANSWER,           0x82, "")
        CONST_TBL_ENTRY(WDP_NETWORK_BEARER_NOT_AVAILABLE,    0x83, "")
        CONST_TBL_ENTRY(WDP_NETWORK_GPRS_TOO_MANY_CONTEXTS,  0x84, "")
        CONST_TBL_ENTRY(WDP_NETWORK_GPRS_ERROR,              0x85, "")
        CONST_TBL_ENTRY(WDP_NETWORK_PPP_NEG_FAILED,          0x86, "")
        CONST_TBL_ENTRY(WDP_NETWORK_BEARER_RESERVED,         0xA0, "")
        CONST_TBL_ENTRY(WDP_NETWORK_BEARER_BARRED,           0xA1, "")
        CONST_TBL_ENTRY(WDP_NETWORK_PERMANENT_FAILURE,       0xA2, "")
        CONST_TBL_ENTRY(WDP_NETWORK_TEMPORARY_FAILURE,       0xA3, "")
        CONST_TBL_ENTRY(WDP_NETWORK_TOO_BIG_SEGMENT,         0xA4, "")
        CONST_TBL_ENTRY(WDP_NETWORK_UNASSIGNED_NUMBER,       0xA5, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_LOWER_LAYER_ERROR_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_ERROR_TYPE_MCU,                  0x01, "")
        CONST_TBL_ENTRY(WDP_ERROR_TYPE_BEARER,               0x02, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_RECEIVE_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_RECEIVE_COMPLETE,                0x00, "")
        CONST_TBL_ENTRY(WDP_RECEIVE_TRUNCATED,               0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_SUSPEND_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_SUSPEND_BUSY,                    0x01, "")
        CONST_TBL_ENTRY(WDP_SUSPEND_MEMORY_FULL,             0x02, "")
        CONST_TBL_ENTRY(WDP_SUSPEND_MEMORY_FULL_XCD_SENT,    0x03, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_PARAM_ID, 8, BE, "", "")
        CONST_TBL_ENTRY(WAP_PARAM_REDIRECT,                  40, "")
        CONST_TBL_ENTRY(WAP_PARAM_RETRANSMIT,                41, "")
        CONST_TBL_ENTRY(WAP_PARAM_RES_ID,                    42, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_AUTHENTICATION_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_AUTH_OK,                         0x00, "")
        CONST_TBL_ENTRY(WDP_AUTH_ABORT,                      0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(WDP_SMS_APPLICATION_STATUS_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(WDP_APP_SUSPENDED,                   0x01, "")
        CONST_TBL_ENTRY(WDP_APP_ALL_ACTIVE,                  0x02, "")
    CONST_TBL_END
 

    /* --------------------------------------------------------------------- */
    /* FTD data table */
    /* --------------------------------------------------------------------- */

    FTD_TBL_BEGIN("", "") /* FTD Type is unknown */
        FTD_TBL_ENTRY_STRING(FTD_SB_WDP_SENT_DATAGRAMS,          0x0100, "", "")
        FTD_TBL_ENTRY_STRING(FTD_SB_WDP_RCVD_DATAGRAMS,          0x0101, "", "")
        FTD_TBL_ENTRY_STRING(FTD_SB_WDP_SENT_OK_DATAGRAMS,       0x0102, "", "")
        FTD_TBL_ENTRY_STRING(FTD_SB_WDP_LAST_ERROR_IND_TYPE,     0x0103, "", "")
        FTD_TBL_ENTRY_STRING(FTD_SB_WDP_LAST_ERROR_IND_CODE,     0x0104, "", "")
        FTD_TBL_ENTRY_STRING(FTD_SB_WDP_SENT_WCMP_ERROR_TYPE,    0x0105, "", "")
        FTD_TBL_ENTRY_STRING(FTD_SB_WDP_SENT_WCMP_ERROR_CODE,    0x0106, "", "")
        FTD_TBL_ENTRY_STRING(FTD_SB_WDP_RCVD_ERROR_TYPE,         0x0107, "", "")
        FTD_TBL_ENTRY_STRING(FTD_SB_WDP_RCVD_ERROR_CODE,         0x0108, "", "")
        FTD_TBL_ENTRY_STRING(FTD_SB_WDP_BIGGEST_SENT_DATAGRAM,   0x0109, "", "")
        FTD_TBL_ENTRY_STRING(FTD_SB_WDP_BIGGEST_RCVD_DATAGRAM,   0x010A, "", "")
        FTD_TBL_ENTRY_STRING(FTD_SB_RESET_WDP_COUNTERS,          0x010B, "", "")
    FTD_TBL_END

    /* --------------------------------------------------------------------- */
    /* Sequences */
    /* --------------------------------------------------------------------- */

    SEQ_BEGIN(WDP_DATA_BYTE, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, data, "Data", HEX)
    SEQ_END


    /* --------------------------------------------------------------------- */
    /* Sub blocks */
    /* --------------------------------------------------------------------- */

    SB_BEGIN(WDP_PARAM_PPP_AUTH_INFO, "", "")
        COMMON_SB
        VALUE_CONST(authentication, "Authentication protocol flags", WDP_AUTHENTICATION_PARAMETER_FLAGS)
        VALUE_CONST(datacall_type, "Datacall type", WDP_DATACALL_TYPE)
        WDP_USERNAME
        WDP_PASSWORD
// TODO...
        FILLER(FILLER_VARIABLE, 32)
    SB_END
    
    SB_BEGIN(WDP_PARAM_CLIENT_IP_INFO, "", "")
        COMMON_SB
        WDP_CLIENT_IP_ADDRESS
// TODO...
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    SB_BEGIN(WDP_PARAM_GPRS_INFO, "", "")
        COMMON_SB
        VALUE_CONST(qos_req_precedence, "Precedence For QOS Request", WDP_QOS_PRECEDENCE)
        VALUE_CONST(qos_req_delay, "Delay For QOS Request", WDP_QOS_DELAY)
        VALUE_CONST(qos_req_reliability, "Reliability For QOS Request", WDP_QOS_RELIABILITY)
        VALUE_CONST(qos_req_peak_throughput, "Peak Throughput for QOS Request", WDP_QOS_PEAK_THROUGHPUT)
        VALUE_CONST(qos_req_mean_throughput, "Mean Throughput For QOS Request", WDP_QOS_MEAN_THROUGHPUT)
        VALUE_CONST(qos_min_precedence, "Precedence For QOS Min", WDP_QOS_PRECEDENCE)
        VALUE_CONST(qos_min_delay, "Delay For QOS Min", WDP_QOS_DELAY)
        VALUE_CONST(qos_min_reliability, "Reliability For QOS Min", WDP_QOS_RELIABILITY)
        VALUE_CONST(qos_min_peak_throughput, "Peak Throughput for QOS min", WDP_QOS_PEAK_THROUGHPUT)
        VALUE_CONST(qos_min_mean_throughput, "Mean Throughput for QOS min", WDP_QOS_MEAN_THROUGHPUT)
        VALUE_CONST(data_compression, "Data Compression", WDP_DATA_COMPRESSION)
        VALUE_CONST(header_compression, "Header Compressio", WDP_HEADER_COMPRESSION)
        WDP_ACCESSPOINTNAME
// TODO...
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    /* --------------------------------------------------------------------- */
    /* Messages */
    /* --------------------------------------------------------------------- */

    /* WDP_HANDLE */

    MSG_BEGIN(WDP_HANDLE_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(CommChannel, "Communication Channel", WDP_COMMUNICATION_CHANNELS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, HandleParamWTP, "Parameter WTP", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, HandleParamWTLS, "Parameter WTLS", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(HandleParamWDP, "Parameter WDP", WDP_HANDLE_PARAMETER_VALUES)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "ApplicationPortLsb")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, ApplicationPortMsb, "Application Port", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "DestPortLsb")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, DestPortMsb, "Destination Port", DEC)
        WDP_GATEWAY_ADDRESS
        WDP_ADDRESS
        WDP_APPLICATION_TAG
        FILLER(FILLER_FIXED, 16)
        REFERENCE(8, BE, num_of_sub_blocks, "Number Of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Block", N, ISIHDR_POINTER)
            SB_LST_ENTRY(WDP_PARAM_PPP_AUTH_INFO)
            SB_LST_ENTRY(WDP_PARAM_GPRS_INFO)
            SB_LST_ENTRY(WDP_PARAM_CLIENT_IP_INFO)
        SB_LST_END
    MSG_END

    MSG_BEGIN(WDP_HANDLE_OK_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        VALUE_CONST(CommChannel, "Communication Channel", WDP_COMMUNICATION_CHANNELS)
        VALUE_CONST(HandleStatus, "Handle Status", WDP_HANDLE_STATUS)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "ApplicationPortLsb")
        VALUE(16, BE, ApplicationPortMsb, "Application Port", DEC)
    MSG_END

    DER_CONST_TBL_BEGIN(WDP_HANDLE_FAIL_STATUS, WDP_ERROR_CODES, "", "")
        DER_CONST_TBL_ENTRY(WDP_MEMORY_FAIL)
        DER_CONST_TBL_ENTRY(WDP_PORT_RESERVED)
    DER_CONST_TBL_END

    MSG_BEGIN(WDP_HANDLE_FAIL_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(CommChannel, "Communication Channel Available", WDP_COMMUNICATION_CHANNELS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(HandleFailCause, "Fail Reason", WDP_HANDLE_FAIL_STATUS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(ApplicationPortPresent, "Application Port Present", TRUE_FALSE)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "ApplicationPortLsb")
        VALUE(16, BE, ApplicationPortMsb, "Application Port", DEC)
    MSG_END

    MSG_PAIR(WDP_HANDLE_REQ, WDP_HANDLE_OK_RESP)
    MSG_PAIR(WDP_HANDLE_REQ, WDP_HANDLE_FAIL_RESP)

    /* WDP_HANDLE_ABORT */

    MSG_BEGIN(WDP_HANDLE_ABORT_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        VALUE_CONST(CommChannel, "Communication Channel", WDP_COMMUNICATION_CHANNELS)
    MSG_END

    MSG_BEGIN(WDP_HANDLE_ABORT_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        VALUE_CONST(Status, "Status", WDP_ERROR_CODES)
    MSG_END

    MSG_PAIR(WDP_HANDLE_ABORT_REQ, WDP_HANDLE_ABORT_RESP)

    /* WDP_HANDLE_RELEASE */

    MSG_BEGIN(WDP_HANDLE_RELEASE_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "ApplicationPortLsb")
        VALUE(16, BE, ApplicationPortMsb, "Application Port", DEC)
    MSG_END

    MSG_BEGIN(WDP_HANDLE_RELEASE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "ApplicationPortLsb")
        VALUE(16, BE, ApplicationPortMsb, "Application Port", DEC)
    MSG_END

    MSG_PAIR(WDP_HANDLE_RELEASE_REQ, WDP_HANDLE_RELEASE_RESP)

    /* WDP_UNITDATA_D */

    MSG_BEGIN(WDP_UNITDATA_D_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        VALUE_CONST(DataCoding, "Data Coding", WDP_DATA_CODING_TYPES)
        REFERENCE(16, BE, DataLength, "Data Length", N)
        SEQ_OF_REF(DataPtr, "Data", WDP_DATA_BYTE, N, ISIHDR_MARKER_POINTER)
        VALUE_CONST(CommChannel, "Communication Channel", WDP_COMMUNICATION_CHANNELS)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "ApplicationPortLsb")
        VALUE(16, BE, ApplicationPortMsb, "Application Port", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "DestPortLsb")
        VALUE(16, BE, DestPortMsb, "Destination Port", DEC)
        WDP_GATEWAY_ADDRESS
        WDP_ADDRESS
        WDP_SEND_PARAM
    MSG_END

    /* WDP_UNITDATA */

    MSG_BEGIN(WDP_UNITDATA_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        VALUE_CONST(DataCoding, "Data Coding", WDP_DATA_CODING_TYPES)
        VALUE(16, BE, DataLength, "Data Length", DEC)
        FILLER_EX(Fill_1, 8, 1)
        FILLER_EX(Fill_2, 8, 1)
        POINTER(BE, DataPtr, "Pointer To Data", POINTER_UINT8)
        VALUE_CONST(CommChannel, "Communication Channel", WDP_COMMUNICATION_CHANNELS)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "ApplicationPortLsb")
        VALUE(16, BE, ApplicationPortMsb, "Application Port", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "DestPortLsb")
        VALUE(16, BE, DestPortMsb, "Destination Port", DEC)
        WDP_GATEWAY_ADDRESS
        WDP_ADDRESS
        WDP_SEND_PARAM
    MSG_END

    MSG_BEGIN(WDP_UNITDATA_OK_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "SendReferenceLsb")
        VALUE(16, BE, SendReferenceMsb, "Reference Number", DEC)
    MSG_END

    MSG_BEGIN(WDP_UNITDATA_FAIL_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        VALUE_CONST(SendErrorCause, "Send Error Cause", WDP_ERROR_CODES)
        VALUE_CONST(ConnErrorCause, "Connection Error Cause", WDP_ERROR_CAUSE_BYTES)
    MSG_END

    MSG_PAIR(WDP_UNITDATA_REQ, WDP_UNITDATA_OK_RESP)
    MSG_PAIR(WDP_UNITDATA_REQ, WDP_UNITDATA_FAIL_RESP)

    /* WDP_DATA_SENT_IND */

    MSG_BEGIN(WDP_DATA_SENT_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "SendReferenceLsb")
        VALUE(16, BE, SendReferenceMsb, "Reference Number", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "MessageReferenceLsb")
        VALUE(16, BE, MessageReferenceMsb, "Message Reference", DEC)
    MSG_END

    /* WDP_ERROR_IND */

    MSG_BEGIN(WDP_ERROR_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(ErrorType, "Error Type", WDP_LOWER_LAYER_ERROR_TYPES)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "IdentifierLsb")
        VALUE(16, BE, IdentifierMsb, "Identifier Number", DEC)
        VALUE_CONST(ErrorCode, "Error Code", WDP_ERROR_CODES)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, WDP_ERROR_MAX_LEN)
        REFERENCE(8, BE, ErrorLength, "Error Message Length", N)
        SEQ_OF_REF(Error, "Error Message", WDP_DATA_BYTE, N, ISIHDR_RESERVE_SPACE)
    MSG_END

    /* WDP_UNITDATA_D_IND */

    MSG_BEGIN(WDP_UNITDATA_D_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "SendReferenceLsb")
        VALUE(16, BE, SendReferenceMsb, "Reference Number", DEC)
        VALUE_CONST(DataCoding, "Data Coding", WDP_DATA_CODING_TYPES)
        REFERENCE(16, BE, datalength, "Data Length", N)
        SEQ_OF_REF(data, "Data", WDP_DATA_BYTE, N, ISIHDR_DONT_GENERATE)
        VALUE_CONST(ReceiveStatus, "Receive Status", WDP_RECEIVE_STATUS)
        VALUE_CONST(AdditionalInfo, "Additional Information Present", TRUE_FALSE)
        VALUE_CONST(CommChannel, "Communication Channel", WDP_COMMUNICATION_CHANNELS)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "SourcePortLsb")
        VALUE(16, BE, SourcePortMsb, "Source Port", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "ApplicationPortLsb")
        VALUE(16, BE, ApplicationPortMsb, "Application Port", DEC)
        WDP_GATEWAY_ADDRESS
        WDP_ADDRESS
        WDP_RECEIVE_PARAM
    MSG_END


    /* WDP_UNITDATA_IND */

    MSG_BEGIN(WDP_UNITDATA_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "ReceiveReferenceLsb")
        VALUE(16, BE, ReceiveReferenceMsb, "Reference Number", DEC)
        VALUE_CONST(DataCoding, "Data Coding", WDP_DATA_CODING_TYPES)
        VALUE(16, BE, Datalength, "Data Length", DEC)
        POINTER(BE, DataPtr, "Pointer to Data", POINTER_UINT8)
        VALUE_CONST(ReceiveStatus, "Receive Status", WDP_RECEIVE_STATUS)
        VALUE_CONST(ReceiveInfoPresent, "Additional Information", TRUE_FALSE)
        VALUE_CONST(CommChannel, "Communication Channel", WDP_COMMUNICATION_CHANNELS)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "SourcePortLsb")
        VALUE(16, BE, SourcePortMsb, "Source Port", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED, "ApplicationPortLsb")
        VALUE(16, BE, ApplicationPortMsb, "Application Port", DEC)
        WDP_GATEWAY_ADDRESS
        WDP_ADDRESS
        WDP_RECEIVE_PARAM
    MSG_END

    /* WDP_HANDLE_SUSPEND */

    MSG_BEGIN(WDP_HANDLE_SUSPEND_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        VALUE_CONST(SuspendType, "Suspend Type", WDP_SUSPEND_TYPES)
    MSG_END

    MSG_BEGIN(WDP_HANDLE_SUSPEND_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        VALUE_CONST(CommChannel, "Communication Channel", WDP_COMMUNICATION_CHANNELS)
        VALUE_CONST(Status, "Status", WDP_ERROR_CODES)
    MSG_END
        
    MSG_PAIR(WDP_HANDLE_SUSPEND_REQ, WDP_HANDLE_SUSPEND_RESP)

    /* WDP_HANDLE_SUSPEND_IND*/

    MSG_BEGIN(WDP_HANDLE_SUSPEND_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        VALUE_CONST(Status, "Status", WDP_ERROR_CODES)
    MSG_END

    /* WDP_HANDLE_RESUME */

    MSG_BEGIN(WDP_HANDLE_RESUME_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(CommChannel, "Communication Channel", WDP_COMMUNICATION_CHANNELS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Status, "Status", WDP_ERROR_CODES)
    MSG_END

    MSG_BEGIN(WDP_HANDLE_RESUME_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, HandleId, "Handle ID", DEC)
    MSG_END

    MSG_BEGIN(WDP_HANDLE_RESUME_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(CommChannel, "Communication Channel", WDP_COMMUNICATION_CHANNELS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(Status, "Status", WDP_ERROR_CODES)
    MSG_END

    MSG_PAIR(WDP_HANDLE_RESUME_REQ, WDP_HANDLE_RESUME_RESP)

    /* WDP_PARAM_SET */

    SEQ_BEGIN(WDP_PARAM_REDIRECT, CREATE_STRUCT, "", "")
        VALUE(16, BE, redirectPortNumber, "Redirect Port Number", DEC)
        VALUE(8, BE, redirectFlags, "Redirect Flags", DEC)
        VALUE(8, BE, redirectAddressType, "Redirect Address Type", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, WDP_ADDRESS_MAX_LEN)
        REFERENCE(8, BE, redirectAddressLen, "Redirect Address Length", N)
        FILLER_EX(fillByte, 8, 1)
        SEQ_OF_REF(RedirectAddress, "Redirect Address", WDP_DATA_BYTE, N, ISIHDR_RESERVE_SPACE)
    SEQ_END

    SEQ_BEGIN(WDP_PARAM_RES_ID, CREATE_STRUCT, "", "")
        VALUE(8, BE, reservationId, "Reservation ID", DEC)
        FILLER_EX(fill_1, 8, 1)
        FILLER_EX(fill_2, 8, 1)
        FILLER_EX(fill_3, 8, 1)
    SEQ_END

    MSG_BEGIN(WDP_PARAM_SET_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        REFERENCE_CONST(ParamID, "Param ID", ID, WDP_PARAM_ID)
        CHOICE_BEGIN(Param, "Parameter Data", ID)
            CASE(WAP_PARAM_REDIRECT, WDP_PARAM_REDIRECT)
            CASE(WAP_PARAM_RES_ID, WDP_PARAM_RES_ID)
        CHOICE_END
    MSG_END

    MSG_BEGIN(WDP_PARAM_SET_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        VALUE_CONST(Status, "Status", WDP_ERROR_CODES)
    MSG_END

    MSG_PAIR(WDP_PARAM_SET_REQ, WDP_PARAM_SET_RESP)

    MSG_BEGIN(WDP_PARAM_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(Status, "Status", WDP_SMS_APPLICATION_STATUS_TYPES)
    MSG_END


    /* WDP_SMS_APP_STATUS_IND */

    MSG_BEGIN(WDP_SMS_APP_STATUS_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(Status, "Status", WDP_ERROR_CODES)
    MSG_END

    /* WDP_PPP_AUTHENTICATION */

    MSG_BEGIN(WDP_PPP_AUTHENTICATION_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        WDP_USERNAME
        WDP_PASSWORD
    MSG_END

    MSG_BEGIN(WDP_PPP_AUTHENTICATION_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        WDP_USERNAME
        WDP_PASSWORD
        VALUE_CONST(Status, "Status", WDP_AUTHENTICATION_STATUS)
    MSG_END

    MSG_BEGIN(WDP_PPP_AUTHENTICATION_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, HandleId, "Handle ID", DEC)
        VALUE_CONST(Status, "Status", WDP_ERROR_CODES)
    MSG_END

    MSG_PAIR(WDP_PPP_AUTHENTICATION_REQ, WDP_PPP_AUTHENTICATION_RESP)

RES_END


/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */


#endif /* _WDP_ISI_M_H_ */


/* End of file wdp_isi_m.h */
