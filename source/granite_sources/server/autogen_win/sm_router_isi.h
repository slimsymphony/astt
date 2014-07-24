/*
NOKIA                                                             CONFIDENTIAL
Devices/R&D/S40 Asset Oulu
S40 Messaging
Mika Kauppinen



                  SM Router ISI Definitions
                  --------------------------------
                  SW Include Document - ANSI C/C++



Continuus Ref:
--------------
database:        ou1glint

project path:    global_s40_interface/S40_ISI

name:            sm_router_isi.h

version:         002.004

type:            incl

instance:        ou1glint#1


ISI header file for SM Router Server

Current   ISI Version : 002.004
Supported ISI Versions: 002.001, 002.002, 002.003, 002.004

Generated with autogen version 09_w51 on 24-Mar-2010 09:34:12
DO NOT EDIT - changes will be lost at next autogeneration

Copyright (c) Nokia Corporation. All rights reserved.


ISI version change history
Version     : 002.003    APPROVED    09-Mar-2010    Daniel Osman
Reason      : Proposal based upon the PCP error: TZ09102141632
Reference   : ActionDB for SWAM Inspection ID: DO09120241812
Description : Add new registration type: SM_ROUTER_REG_TYPE_LOGICAL_AND.For
              SMs that match conditional-AND of USER DATA and ORIGINATING
              ADDRESS subblocks.

Version     : 002.004    APPROVED    23-Mar-2010    Daniel Osman
Reason      : Proposal based upon PCP error: TZ09102141632
Reference   : ActionDB for SWAM Inspection ID: DO09120241812
Description : Add new registration type: SM_ROUTER_REG_TYPE_LOGICAL_ANDFor
              SMs that match conditional logical-and of user data and
              originating address subblocks.

Version     : 002.003    APPROVED    09-Feb-2010    Toni Moilanen
Reason      : REQ:408-5644: DUAL SIM SPRINT 7: SMS receiving: SM router
              server
Reference   : Inspection reference ActionDB for SWAM Inspection ID:
              MM09122330689
Description : Added Subblock MULTI_SIM_SHARED_SB_ICC to SM_ROUTER_MO_SM_SEND_REQ
              Added Subblock MULTI_SIM_SHARED_SB_SIM_ID to SM_ROUTER_MO_SM_SEND_REQ
              Added Subblock MULTI_SIM_SHARED_SB_SIM_ID to SM_ROUTER_MO_SM_SEND_RESP
              Added Subblock MULTI_SIM_SHARED_SB_ICC to SM_ROUTER_MT_SM_RECEIVED_NTF
              Added Subblock MULTI_SIM_SHARED_SB_SIM_ID to SM_ROUTER_MT_SM_RECEIVED_NTF
              Added Message SM_ROUTER_MT_TRIGGER_NTF
              Added Subblock MULTI_SIM_SHARED_SB_DEVICE_ID
              Added Subblock MULTI_SIM_SHARED_SB_ICC
              Added Subblock MULTI_SIM_SHARED_SB_SIM_ID
              Added Constant MULTI_SIM_ICC_LEN
              Added Shared file from PN_MULTI_SIM
              Shared SBs MULTI_SIM_SHARED_SB_SIM_ID and MULTI_SIM_
              SHARED_SB_ICC added to sending and receiving.

Version     : 002.002    APPROVED    18-May-2009    Juha Turpeinen
Reason      : Proposal based upon the PCP error: JT09051849899
Reference   : ActionDB for SWAM Inspection ID: JT09052757226
Description : Added Case SM_ROUTER_RESPONSE_TYPE_SYSTEM to SM_ROUTER_MO_SM_SEND_RESP
              More information added for SM_ROUTER_RESPONSE_TYPE_SYSTEM
              response statuses.

Version     : 002.001    APPROVED    26-Nov-2008    Tuomo Heikka
Reason      : Corrected after inspection.
Reference   : ActionDB for SWAM Inspection ID: TH08111458789 SM Router ISI v.
              002.000 inspection.
Description : Dropped support of previous versions as they were not approved.
              Renamed parameter mt_router_status to mt_service_status in
              SM_ROUTER_MT_SM_REGISTER_RESP_STR. Corrected sub block name in
              description field of SM_ROUTER_MO_SM_SEND_REQ. 

Version     : 002.000    PROPOSAL    13-Nov-2008    Mika Kauppinen
Reason      : Corrected after inspection. ID: TH08100929947.
Reference   : ActionDB for SWAM Inspection ID: TH08111458789 SM Router ISI v.
              002.000 inspection.
Description : -

Version     : 001.000    PROPOSAL    08-Oct-2008    Mika Kauppinen
Reason      : First official version for inspection
Reference   : RM-RIM REQ: 414-3471: Chipset API: SMS server changes
Description : Defines SM Router Server ISI interface

------------------------------------------------------------------------------

Description

The SM (Short Message) Router server is a public ISA (Intelligent Software
Architecture) server, which provides support for clients to send and to
receive short messages. The SM Router also acts as a controller for SMS
server resource MO SM (short message mobile originated). The resource control
functionality is specified in SMS server feature and protocol description.
The SM Router sends indication when its own status changes or when status of
its services changes (See reference /8/).

*/

#ifndef _SM_ROUTER_ISI_H
#define _SM_ROUTER_ISI_H

#include "isi_conf.h"

#ifndef SM_ROUTER_ISI_VERSION
#define SM_ROUTER_ISI_VERSION
#define SM_ROUTER_ISI_VERSION_Z   2
#define SM_ROUTER_ISI_VERSION_Y   5
#endif

#define SM_ROUTER_ISI_MIN_VERSION(z,y) \
 ((SM_ROUTER_ISI_VERSION_Z == (z) && SM_ROUTER_ISI_VERSION_Y >= (y)) || \
  (SM_ROUTER_ISI_VERSION_Z > (z)))

#if !SM_ROUTER_ISI_MIN_VERSION(1,0)
#error The specified interface version is not supported by this header file
#elif SM_ROUTER_ISI_MIN_VERSION(2,6)
#error The specified interface version is not supported by this header file
#endif

#if ((SM_ROUTER_ISI_VERSION_Z ==   1 && SM_ROUTER_ISI_VERSION_Y ==   0) || \
     (SM_ROUTER_ISI_VERSION_Z ==   2 && SM_ROUTER_ISI_VERSION_Y ==   0))
#error The specified interface version is no longer supported
#endif


/* ----------------------------------------------------------------------- */
/* Constants                                                               */
/* ----------------------------------------------------------------------- */

/* SM Router SMS Parameters default location. */
#define SM_ROUTER_PARAMS_LOCATION_DEFAULT        0x00
/* SM Router uninitialized registration id. */
#define SM_ROUTER_REGISTRATION_ID_NONE           0x00
/* constant for variable-length definitions */
#define SM_ROUTER_ANY_SIZE                       1

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_MESSAGE_TYPE                                  */
/* ----------------------------------------------------------------------- */
/* Type of short messages that the client requests to receive. */
typedef uint8 SM_ROUTER_MESSAGE_TYPE_CONST;

/* SMS-DELIVER type. */
#define SM_ROUTER_SM_TYPE_DELIVER                0x00
/* SMS-STATUS-REPORT type. */
#define SM_ROUTER_SM_TYPE_STATUS_REPORT          0x01
/* SMS-MT-ALL type. */
#define SM_ROUTER_SM_TYPE_MT_ALL                 0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_ACTION                                        */
/* ----------------------------------------------------------------------- */
/* SM Router action. */
typedef uint8 SM_ROUTER_ACTION_CONST;

/* Register to service. */
#define SM_ROUTER_ACTION_REGISTER                0x00
/* Deregister from service. */
#define SM_ROUTER_ACTION_DEREGISTER              0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_STATUS                                        */
/* ----------------------------------------------------------------------- */
/* Statuses of the SM Router Server and services. */
typedef uint8 SM_ROUTER_STATUS_CONST;

/* Server is performing startup. */
#define SM_ROUTER_STATUS_NOT_READY               0x01
/* Server status is running. */
#define SM_ROUTER_STATUS_READY                   0x02
/* MO Service is not ready. */
#define SM_ROUTER_STATUS_MO_SM_NOT_READY         0x03
/* MO Service is idle. */
#define SM_ROUTER_STATUS_MO_SM_IDLE              0x04
/* MO Service is busy. */
#define SM_ROUTER_STATUS_MO_SM_BUSY              0x05
/* MT Service is not ready. */
#define SM_ROUTER_STATUS_MT_SM_NOT_READY         0x06
/* MT Service is active. */
#define SM_ROUTER_STATUS_MT_SM_ACTIVE            0x07
/* MT Service is inactive. */
#define SM_ROUTER_STATUS_MT_SM_INACTIVE          0x08

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_BEARER_TYPE                                   */
/* ----------------------------------------------------------------------- */
/* SM route that defines bearer over which the MO SM is sent. */
typedef uint8 SM_ROUTER_BEARER_TYPE_CONST;

/* Bearers according to user selection. */
#define SM_ROUTER_BEARER_TYPE_DEFAULT            0x00
/* Only CS bearer is used. */
#define SM_ROUTER_BEARER_TYPE_CS_ONLY            0x01
/* Only PS bearer is used. */
#define SM_ROUTER_BEARER_TYPE_PS_ONLY            0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_REGISTRATION_TYPE                             */
/* ----------------------------------------------------------------------- */
/* Defines the specific content in short messages that the client requests to
   receive in priority order
*/
typedef uint8 SM_ROUTER_REGISTRATION_TYPE_CONST;

/* Class 2 and (U)SIM data download */
#define SM_ROUTER_REG_TYPE_USIM_DDL              0x01
/* Kodiak spesific SM */
#define SM_ROUTER_REG_TYPE_KODIAK_SMS            0x02
/* Originating address (Sender phone number) */
#define SM_ROUTER_REG_TYPE_ORIG_ADDRESS          0x03
/* Application port as SM destination */
#define SM_ROUTER_REG_TYPE_APPL_PORT             0x04
/* Spesific user data content */
#define SM_ROUTER_REG_TYPE_USER_DATA             0x05
/* Message Waiting Indication SM */
#define SM_ROUTER_REG_TYPE_MWI                   0x06
/* Misc application port SMs */
#define SM_ROUTER_REG_TYPE_APPL_PORT_ALL         0x07
/* Immediate display (Flash message) */
#define SM_ROUTER_REG_TYPE_CLASS_0               0x08
/* ME (Mobile Equipment) specific */
#define SM_ROUTER_REG_TYPE_CLASS_1               0x09
/* (U)SIM specific */
#define SM_ROUTER_REG_TYPE_CLASS_2               0x0A
/* TE (Terminal equipment) specific */
#define SM_ROUTER_REG_TYPE_CLASS_3               0x0B
/* Basic SMs for default handler */
#define SM_ROUTER_REG_TYPE_TEXT_MESSAGES         0x0C
/* SM meets conditional logical-and of originating address and user data
   content
*/
#define SM_ROUTER_REG_TYPE_LOGICAL_AND           0x0D

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_RESPONSE_TYPE                                 */
/* ----------------------------------------------------------------------- */
/* Defines which of the response type tables is being used. */
typedef uint8 SM_ROUTER_RESPONSE_TYPE_CONST;

/* OK response or not SM transfer related fail response. */
#define SM_ROUTER_RESPONSE_TYPE_INTERNAL         0x00
/* SM protocol or associated protocols specific fail response. */
#define SM_ROUTER_RESPONSE_TYPE_SYSTEM           0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_RESPONSE_TYPE_INTERNAL                        */
/* ----------------------------------------------------------------------- */
/* If response type is not used or if response type is
   SM_ROUTER_RESPONSE_TYPE_INTERNAL then following cause values shall be
   used:
*/
typedef uint8 SM_ROUTER_RESPONSE_TYPE_INTERNAL_CONST;

#define SM_ROUTER_OK                             0x01
#define SM_ROUTER_ERR_NOT_READY                  0x02
#define SM_ROUTER_ERR_MO_SM_BUSY                 0x03
#define SM_ROUTER_ERR_INVALID_REQUEST            0x04
#define SM_ROUTER_ERR_DEVICE_FAILURE             0x05
#define SM_ROUTER_ERR_BEARER_NOT_AVAILABLE       0x06
#define SM_ROUTER_ERR_BEARER_NOT_ALLOWED         0x07
#define SM_ROUTER_ERR_NO_SYSTEM_RESPONSE         0x08
#define SM_ROUTER_ERR_DEST_ADDRESS_FDN_RESTRICTED 0x09
#define SM_ROUTER_ERR_SMSC_ADDRESS_FDN_RESTRICTED 0x0A
#define SM_ROUTER_ERR_BEARERS_INACTIVE           0x0B
#define SM_ROUTER_ERR_MO_SM_CONTROL_REJECTED     0x0C
#define SM_ROUTER_ERR_PREPAID_REJECTED           0x0D
#define SM_ROUTER_ERR_MT_SM_RESERVED             0x0E
#define SM_ROUTER_ERR_MESSAGE_REJECTED           0x0F
#define SM_ROUTER_ERR_INVALID_REFERENCE_ID       0x10
#define SM_ROUTER_ERR_FAILED_RESPONSE_ALREADY_SENT 0x11
#define SM_ROUTER_ERR_REGISTRATION_TYPE_MISMATCH 0x12
#define SM_ROUTER_ERR_REGISTRATION_NOT_FOUND     0x13
#define SM_ROUTER_ERR_SMSC_ADDR_NOT_AVAILABLE    0x14

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_RESPONSE_TYPE_SYSTEM                          */
/* ----------------------------------------------------------------------- */
/* If response type is SM_ROUTER_RESPONSE_TYPE_SYSTEM then following response
   values shall be used. NOTE: Direction field defines whether the response
   can be used in accordance with mobile originating messages or mobile
   terminating messages (see comment field for MO/MT direction information
   for the related response). NOTE 2: The response status can be handled as
   either temporary or permanent fail status depending on the clients
   possibility to handle such cases (see comment field for
   Temporary/Permanent status information for the related response). 
*/
typedef uint8 SM_ROUTER_RESPONSE_TYPE_SYSTEM_CONST;

/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_UNASSIGNED_NUMBER          0x01
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_OPER_DETERMINED_BARRED     0x08
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_CALL_BARRED                0x0A
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_RESERVED                   0x0B
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_MSG_TRANSFER_REJECTED      0x15
/* Direction: MT. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_MEMORY_CAPACITY_EXCEEDED   0x16
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_DEST_OUT_OF_ORDER          0x1B
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_UNDEFINED_SUBSCRIBER       0x1C
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_FACILITY_REJECTED          0x1D
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_UNKNOWN_SUBSCRIBER         0x1E
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_NETW_OUT_OF_ORDER          0x26
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_TEMPORARY_FAILURE          0x29
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_CONGESTION                 0x2A
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_RESOURCE_UNAVAILABLE       0x2F
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_REQ_FACILITY_NOT_SUBSCRIBED 0x32
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_REQ_FACILITY_NOT_IMPLEMENTED 0x45
/* Direction: MO/MT. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_INVALID_REFERENCE          0x51
/* Direction: MO/MT. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_INCORRECT_MESSAGE          0x5F
/* Direction: MO/MT. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_INVALID_MAND_INFO          0x60
/* Direction: MO/MT. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_INVALID_MSG_TYPE           0x61
/* Direction: MO/MT. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_MSG_NOT_COMP_WITH_STATE    0x62
/* Direction: MO/MT. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_INVALID_INFO_ELEMENT       0x63
/* Direction: MO/MT. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_PROTOCOL_ERROR             0x6F
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_INTERWORKING               0x7F
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_NO_CAUSE                   0x80
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_IMSI_UNKNOWN_HLR           0x82
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_ILLEGAL_MS                 0x83
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_IMSI_UNKNOWN_VLR           0x84
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_IMEI_NOT_ACCEPTED          0x85
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_ILLEGAL_ME                 0x86
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_PLMN_NOT_ALLOWED           0x8B
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_LA_NOT_ALLOWED             0x8C
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_ROAM_NOT_ALLOWED_LA        0x8D
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_NO_SUITABLE_CELLS_LA       0x8F
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_NETWORK_FAILURE            0x91
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_MAC_FAILURE                0x94
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_SYNC_FAILURE               0x95
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_LOW_LAYER_CONGESTION       0x96
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_AUTH_UNACCEPTABLE          0x97
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_SERV_OPT_NOT_SUPPORTED     0xA0
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_SERV_OPT_NOT_SUBSCRIBED    0xA1
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_SERV_OPT_TEMP_OUT_OF_ORDER 0xA2
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_CALL_CANNOT_BE_IDENTIFIED  0xA6
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_SEMANTICALLY_INCORR_MSG    0xDF
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_LOW_LAYER_INVALID_MAND_INFO 0xE0
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_LOW_LAYER_INVALID_MSG_TYPE 0xE1
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_LOW_LAYER_MSG_TYPE_NOT_COMP_WITH_STATE 0xE2
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_LOW_LAYER_INVALID_INFO_ELEMENT 0xE3
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_CONDITIONAL_IE_ERROR       0xE4
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_LOW_LAYER_MSG_NOT_COMP_WITH_STATE 0xE5
/* Direction: MO. Preferred to be handled as a Permanent fail status */
#define SM_ROUTER_ERR_CS_BARRED                  0xE8
/* Direction: MO. Preferred to be handled as a Temporary fail status */
#define SM_ROUTER_ERR_LOW_LAYER_PROTOCOL_ERROR   0xEF

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_CONTENT_TYPE                                  */
/* ----------------------------------------------------------------------- */
/* Defines the payload or purpose of the short message */
typedef uint8 SM_ROUTER_CONTENT_TYPE_CONST;

#define SM_ROUTER_CONTENT_TYPE_TEXT_MESSAGE      0x00
#define SM_ROUTER_CONTENT_TYPE_NOKIA_SMART_MESSAGE 0x01
#define SM_ROUTER_CONTENT_TYPE_JAVA_MIDLET_SMS   0x02
#define SM_ROUTER_CONTENT_TYPE_BREW_SMS          0x03
#define SM_ROUTER_CONTENT_TYPE_GPS_SMS           0x04
#define SM_ROUTER_CONTENT_TYPE_PUSH_TO_TALK_SMS  0x05
#define SM_ROUTER_CONTENT_TYPE_SIM_ATK_SMS       0x06
#define SM_ROUTER_CONTENT_TYPE_TRACFONE_PREPAID_SMS 0x07

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_MO_SM_CONTROL_RESULT                          */
/* ----------------------------------------------------------------------- */
/* MO SM Control result: defines the result of ATK MO SM Control check */
typedef uint8 SM_ROUTER_MO_SM_CONTROL_RESULT_CONST;

/* Message check not done. */
#define SM_ROUTER_MO_SM_CTRL_NOT_DONE            0x00
/* Sending allowed, addresses unchanged. */
#define SM_ROUTER_MO_SM_CTRL_ALLOWED             0x01
/* Sending allowed, address(es) changed. */
#define SM_ROUTER_MO_SM_CTRL_MODIFIED            0x02
/* Sending not allowed. */
#define SM_ROUTER_MO_SM_CTRL_NOT_ALLOWED         0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_ADDRESS_TYPE                                  */
/* ----------------------------------------------------------------------- */
/* SM Router Address types */
typedef uint8 SM_ROUTER_ADDRESS_TYPE_CONST;

/* 16-bit zero terminated */
#define SM_ROUTER_ADDRESS_TYPE_UNICODE           0x01
/* 3GPP service center address TS 24.011 /11/ */
#define SM_ROUTER_ADDRESS_TYPE_SMSC              0x02

/* ----------------------------------------------------------------------- */
/* Bitmask Table: SM_ROUTER_PARAMETER_INDICATOR                            */
/* ----------------------------------------------------------------------- */
/* SMS (U)SIM parameters indicators. Defines which of the SMS parameters
   shall be read and used.
*/
typedef uint8 SM_ROUTER_PARAMETER_INDICATOR_CONST;

#define SM_ROUTER_PI_DESTINATION_ADDRESS         0x01  /* -------1 */
#define SM_ROUTER_PI_SERVICE_CENTRE_ADDRESS      0x02  /* ------1- */
#define SM_ROUTER_PI_PROTOCOL_ID                 0x04  /* -----1-- */
#define SM_ROUTER_PI_DATA_CODING_SCHEME          0x08  /* ----1--- */
#define SM_ROUTER_PI_VALIDITY_PERIOD             0x10  /* ---1---- */

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_DATA_TYPE                                     */
/* ----------------------------------------------------------------------- */
/* SM Router data types. Defines the format of data in data bytes field. */
typedef uint8 SM_ROUTER_DATA_TYPE_CONST;

/* 7-bit encoding 3GPP TS 23.038 /9/ */
#define SM_ROUTER_SM_DATA_TYPE_3GPP7BIT          0x01
/* 8-bit encoding (ASCII, Binary) */
#define SM_ROUTER_SM_DATA_TYPE_8BIT              0x02
/* 16-bit zero terminated */
#define SM_ROUTER_SM_DATA_TYPE_UNICODE           0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_MESSAGE_STORAGE_STATE                         */
/* ----------------------------------------------------------------------- */
/* SM Router message storage states. */
typedef uint8 SM_ROUTER_MESSAGE_STORAGE_STATE_CONST;

/* Message storage state not initialized */
#define SM_ROUTER_MESSAGE_STORAGE_STATE_UNKNOWN  0x01
/* Message storage not in full state */
#define SM_ROUTER_MESSAGE_STORAGE_STATE_NOT_FULL 0x02
/* Message storage in full state */
#define SM_ROUTER_MESSAGE_STORAGE_STATE_FULL     0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: SM_ROUTER_ORIGINATOR_TYPE                               */
/* ----------------------------------------------------------------------- */
/* SM Router MO SM originator types. Defines source of the SM. */
typedef uint8 SM_ROUTER_ORIGINATOR_TYPE_CONST;

/* Originator different than USIM */
#define SM_ROUTER_ORIGINATOR_DEFAULT             0x00
/* Originator USIM */
#define SM_ROUTER_ORIGINATOR_USIM                0x01

/* ----------------------------------------------------------------------- */
/* Message ID's                                                            */
/* ----------------------------------------------------------------------- */

#define SM_ROUTER_STATUS_REQ                     0x10
#define SM_ROUTER_STATUS_RESP                    0x11
#define SM_ROUTER_STORAGE_STATE_SET_REQ          0x12
#define SM_ROUTER_STORAGE_STATE_SET_RESP         0x13
#define SM_ROUTER_MT_SM_STATUS_IND               0x14
#define SM_ROUTER_MT_SM_REGISTER_REQ             0x15
#define SM_ROUTER_MT_SM_REGISTER_RESP            0x16
#define SM_ROUTER_MT_SM_RECEIVED_NTF             0x17
#define SM_ROUTER_MT_SM_RESPONSE_REQ             0x18
#define SM_ROUTER_MT_SM_RESPONSE_RESP            0x19
#define SM_ROUTER_MO_SM_STATUS_IND               0x1A
#define SM_ROUTER_MO_SM_SEND_REQ                 0x1B
#define SM_ROUTER_MO_SM_SEND_RESP                0x1C
#define SM_ROUTER_MT_TRIGGER_NTF                 0xE0

/* ----------------------------------------------------------------------- */
/* Subblock ID's                                                           */
/* ----------------------------------------------------------------------- */

#define SM_ROUTER_SB_APPL_PORT                   0x0002
#define SM_ROUTER_SB_ADDRESS                     0x0001
#define SM_ROUTER_SB_USIM_PARAMS_LOCATION        0x0003
#define SM_ROUTER_SB_TEXT_STRING                 0x0005
#define SM_ROUTER_SB_SM_USER_DATA                0x0004
#define SM_ROUTER_SB_TPDU                        0x0006

/* ----------------------------------------------------------------------- */
/* Shared file inclusion                                                   */
/* ----------------------------------------------------------------------- */

#if SM_ROUTER_ISI_MIN_VERSION(2,3)
#include "multi_sim_shared_isi.h"
#endif /* SM_ROUTER_ISI_MIN_VERSION(2,3) */


/* ----------------------------------------------------------------------- */
/* Subblock: SM_ROUTER_SB_APPL_PORT                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint16  sb_id;
    uint16  sb_len;
    uint8   port_count;   /* Amount of application ports. */
    uint8   fill1;
    /* Port data is formed of an array of uint16 port numbers. */
    uint16  port_data[SM_ROUTER_ANY_SIZE];
    } SM_ROUTER_SB_APPL_PORT_STR;

#define SIZE_SM_ROUTER_SB_APPL_PORT_STR   (2*sizeof(uint16) + 2*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Subblock: SM_ROUTER_SB_ADDRESS                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint16  sb_id;
    uint16  sb_len;
    /* Defines format of address data.
       Values from the constant table SM_ROUTER_ADDRESS_TYPE
    */
    uint8   address_type;
    uint8   address_data_length;
    /* Address data according to address type. */
    uint8   address_data[SM_ROUTER_ANY_SIZE];
    } SM_ROUTER_SB_ADDRESS_STR;

#define SIZE_SM_ROUTER_SB_ADDRESS_STR   (2*sizeof(uint16) + 2*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Subblock: SM_ROUTER_SB_USIM_PARAMS_LOCATION                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint16  sb_id;
    uint16  sb_len;
    /* SMS parameters location on (U)SIM. From 1 to 255 or
       SM_ROUTER_PARAMS_LOCATION_DEFAULT.
    */
    uint8   location_number;
    /* Bit field that defines which of the SMS parameters shall be read and
       used.
       Values from the bitmask table SM_ROUTER_PARAMETER_INDICATOR
    */
    uint8   indicator;
    uint8   fill1[2];
    } SM_ROUTER_SB_USIM_PARAMS_LOCATION_STR;

#define SIZE_SM_ROUTER_SB_USIM_PARAMS_LOCATION_STR   \
        sizeof(SM_ROUTER_SB_USIM_PARAMS_LOCATION_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: SM_ROUTER_SB_TEXT_STRING                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint16  sb_id;
    uint16  sb_len;
    /* Data length in UNICODE characters, not counting trailing zero. */
    uint16  data_length;
    char16  text[SM_ROUTER_ANY_SIZE]; /* Zero terminated UNICODE string. */
    } SM_ROUTER_SB_TEXT_STRING_STR;

#define SIZE_SM_ROUTER_SB_TEXT_STRING_STR   (3*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Subblock: SM_ROUTER_SB_SM_USER_DATA                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint16  sb_id;
    uint16  sb_len;
    /* Format of user data field.
       Values from the constant table SM_ROUTER_DATA_TYPE
    */
    uint8   data_type;
    uint8   data_length;  /* Data length in bytes. */
    /* Number of septets if data type is SM_ROUTER_SM_DATA_TYPE_3GPP7BIT.
       Otherwise ignored.
    */
    uint8   septet_count;
    /* User data according to data type. No zero termination. */
    uint8   user_data[SM_ROUTER_ANY_SIZE];
    } SM_ROUTER_SB_SM_USER_DATA_STR;

#define SIZE_SM_ROUTER_SB_SM_USER_DATA_STR   (2*sizeof(uint16) + \
        3*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Subblock: SM_ROUTER_SB_TPDU                                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint16  sb_id;
    uint16  sb_len;
    uint8   tpdu_length;  /* TPDU length in bytes. */
    /* SMS Transfer Protocol Data Unit including SMS user data. See /10/ */
    uint8   tpdu_data[SM_ROUTER_ANY_SIZE];
    } SM_ROUTER_SB_TPDU_STR;

#define SIZE_SM_ROUTER_SB_TPDU_STR   (2*sizeof(uint16) + sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_STATUS_REQ                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    } SM_ROUTER_STATUS_REQ_STR;

#define SIZE_SM_ROUTER_STATUS_REQ_STR   sizeof(SM_ROUTER_STATUS_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_STATUS_RESP                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* Handling of this message cannot fail, status is always SM_ROUTER_OK.
       A subset of values from the constant table
       SM_ROUTER_RESPONSE_TYPE_INTERNAL
    */
    uint8   response;
    /* General Router Status.
       A subset of values from the constant table SM_ROUTER_STATUS
    */
    uint8   router_status;
    /* Current MO Service Status.
       A subset of values from the constant table SM_ROUTER_STATUS
    */
    uint8   mo_service_status;
    /* Current MT Service Status.
       A subset of values from the constant table SM_ROUTER_STATUS
    */
    uint8   mt_service_status;
    } SM_ROUTER_STATUS_RESP_STR;

#define SIZE_SM_ROUTER_STATUS_RESP_STR   sizeof(SM_ROUTER_STATUS_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_SM_STATUS_IND                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* General Router Status always SM_ROUTER_STATUS_READY. */
    uint8   router_status;
    /* Current MT Service Status.
       A subset of values from the constant table SM_ROUTER_STATUS
    */
    uint8   mt_service_status;
    } SM_ROUTER_MT_SM_STATUS_IND_STR;

#define SIZE_SM_ROUTER_MT_SM_STATUS_IND_STR   \
        sizeof(SM_ROUTER_MT_SM_STATUS_IND_STR)


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MO_SM_STATUS_IND                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* General Router Status always SM_ROUTER_STATUS_READY. */
    uint8   router_status;
    /* Current MO Service Status.
       A subset of values from the constant table SM_ROUTER_STATUS
    */
    uint8   mo_service_status;
    } SM_ROUTER_MO_SM_STATUS_IND_STR;

#define SIZE_SM_ROUTER_MO_SM_STATUS_IND_STR   \
        sizeof(SM_ROUTER_MO_SM_STATUS_IND_STR)


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MO_SM_SEND_REQ                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* Content type of MO SM. Will be used for prepaid checking. Default
       value: SM_ROUTER_CONTENT_TYPE_TEXT_MESSAGE.
       Values from the constant table SM_ROUTER_CONTENT_TYPE
    */
    uint8   content_type;
    /* SM route that defines bearer over which the MO SM is sent. Default
       value: SM_ROUTER_BEARER_TYPE_DEFAULT.
       Values from the constant table SM_ROUTER_BEARER_TYPE
    */
    uint8   bearer_type;
    /* Client has next MO SM waiting for sending after this one. */
    uint8   more_messages;
    /* Re-send of previously unsuccessfully sent SM with the same TP-MR as in
       the failed send case.
    */
    uint8   repeated_message;
    /* Defines source of the SM. Needed to bypass FDN check for (U)SIM
       originated SM. Default value: SM_ROUTER_ORIGINATOR_DEFAULT.
       Values from the constant table SM_ROUTER_ORIGINATOR_TYPE
    */
    uint8   message_originator;
    uint8   fill1[2];
    uint8   sub_block_count;
    /* Mandatory:
       - SMS-Submit or SMS-Command TPDU sub block(s)
       [SM_ROUTER_SB_TPDU] (can be many of these)
       Conditional:
       - SMSC address sub block
       [SM_ROUTER_SB_ADDRESS] (SM_ROUTER_ADDRESS_TYPE_SMSC) or
       - USIM SMS parameters sub block
       [SM_ROUTER_SB_USIM_PARAMS_LOCATION] or
       both. Either SMSC address or its location 
       information must be included.
       Optional:
       - Multi SIM information sub block
       Either [MULTI_SIM_SHARED_SB_SIM_ID] or 
       [MULTI_SIM_SHARED_SB_ICC], not both.
       Subblock list:
       MULTI_SIM_SHARED_SB_ICC
       MULTI_SIM_SHARED_SB_SIM_ID
       SM_ROUTER_SB_ADDRESS
       SM_ROUTER_SB_TPDU
       SM_ROUTER_SB_USIM_PARAMS_LOCATION
    */
    uint8   sub_blocks[SM_ROUTER_ANY_SIZE];
    } SM_ROUTER_MO_SM_SEND_REQ_STR;

#define SIZE_SM_ROUTER_MO_SM_SEND_REQ_STR   (12*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MO_SM_SEND_RESP                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* Either internal or system response type is used.
       Values from the constant table SM_ROUTER_RESPONSE_TYPE
    */
    uint8   response_type;
    /* A subset of values from the constant table
       SM_ROUTER_RESPONSE_TYPE_INTERNAL
    */
    uint8   response;
    /* MO SM Control result defines the result of ATK MO SM Control check.
       Values from the constant table SM_ROUTER_MO_SM_CONTROL_RESULT
    */
    uint8   control_result;
    /* Assigned SM message reference if success response or if response type
       is SM_ROUTER_RESPONSE_TYPE_SYSTEM. Otherwise zero.
    */
    uint8   reference_id;
    uint8   sent_tpdu_count; /* Number of successfully sent TPDUs. */
    uint8   fill1[2];
    uint8   sub_block_count;
    /* Optional:
       - SMS-Submit-Report TPDU sub block
       [SM_ROUTER_SB_TPDU]
       - MO SM Control Alpha ID sub block
       [SM_ROUTER_SB_TEXT_STRING]
       Optional:
       - Multi SIM information sub block
       [MULTI_SIM_SHARED_SB_SIM_ID]
       Subblock list:
       MULTI_SIM_SHARED_SB_SIM_ID
       SM_ROUTER_SB_TEXT_STRING
       SM_ROUTER_SB_TPDU
    */
    uint8   sub_blocks[SM_ROUTER_ANY_SIZE];
    } SM_ROUTER_MO_SM_SEND_RESP_STR;

#define SIZE_SM_ROUTER_MO_SM_SEND_RESP_STR   (12*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_SM_REGISTER_REQ                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* SM_ROUTER_REGISTRATION_ID_NONE in registration, SM Router assigned Id
       in deregistration.
    */
    uint16  registration_id;
    /* Registration or deregistration.
       Values from the constant table SM_ROUTER_ACTION
    */
    uint8   action;
    /* Defines the specific SM content together with possible sub block(s).
       Values from the constant table SM_ROUTER_REGISTRATION_TYPE
    */
    uint8   registration_type;
    /* Either specific MT SM type or all MT SM types. Default value:
       SM_ROUTER_SM_TYPE_DELIVER.
       Values from the constant table SM_ROUTER_MESSAGE_TYPE
    */
    uint8   message_type;
    uint8   fill1[2];
    uint8   sub_block_count;
    /* For SM_ROUTER_REG_TYPE_LOGICAL_AND, must have exactly 2 subblocks:
       SM_ROUTER_SB_ADDRESS and SM_ROUTER_SB_SM_USER_DATA.
       For other registration types, many sub blocks allowed but of one type
       only can be included.
       Optional:
       - Application port(s) sub block(s)
       [SM_ROUTER_SB_APPL_PORT]
       - Originator address sub block(s)
       [SM_ROUTER_SB_ADDRESS] (SM_ROUTER_ADDRESS_TYPE_UNICODE)
       - SM user data sub block(s)
       [SM_ROUTER_SB_SM_USER_DATA]
       Subblock list:
       SM_ROUTER_SB_ADDRESS
       SM_ROUTER_SB_APPL_PORT
       SM_ROUTER_SB_SM_USER_DATA
    */
    uint8   sub_blocks[SM_ROUTER_ANY_SIZE];
    } SM_ROUTER_MT_SM_REGISTER_REQ_STR;

#define SIZE_SM_ROUTER_MT_SM_REGISTER_REQ_STR   (10*sizeof(uint8) + \
        sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_SM_REGISTER_RESP                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* Indicates success of the request.
       A subset of values from the constant table
       SM_ROUTER_RESPONSE_TYPE_INTERNAL
    */
    uint8   response;
    uint8   fill1;
    /* Value depends on requested action and success. See /7/ */
    uint16  registration_id;
    /* Current MT Service Status.
       A subset of values from the constant table SM_ROUTER_STATUS
    */
    uint8   mt_service_status;
    } SM_ROUTER_MT_SM_REGISTER_RESP_STR;

#define SIZE_SM_ROUTER_MT_SM_REGISTER_RESP_STR   \
        sizeof(SM_ROUTER_MT_SM_REGISTER_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_SM_RECEIVED_NTF                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* Registration Id - verification for client. Indicates the id of
       matching MT SM registration.
    */
    uint16  registration_id;
    uint8   reference_id; /* Message reference for MT message. */
    uint8   sub_block_count;
    /* Mandatory:
       - SMSC address sub block
       [SM_ROUTER_SB_ADDRESS] (SM_ROUTER_ADDRESS_TYPE_SMSC)
       - SMS-Deliver, SMS-Status-Report or undefined TPDU sub block
       [SM_ROUTER_SB_TPDU]
       - Multi SIM information sub blocks
       [MULTI_SIM_SHARED_SB_SIM_ID]
       [MULTI_SIM_SHARED_SB_ICC]
       Subblock list:
       MULTI_SIM_SHARED_SB_ICC
       MULTI_SIM_SHARED_SB_SIM_ID
       SM_ROUTER_SB_ADDRESS
       SM_ROUTER_SB_TPDU
    */
    uint8   sub_blocks[SM_ROUTER_ANY_SIZE];
    } SM_ROUTER_MT_SM_RECEIVED_NTF_STR;

#define SIZE_SM_ROUTER_MT_SM_RECEIVED_NTF_STR   (6*sizeof(uint8) + \
        sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_SM_RESPONSE_REQ                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* Message reference for MT message. Same as in
       SM_ROUTER_MT_SM_RECEIVED_NTF
    */
    uint8   reference_id;
    /* Either internal or system response type is used.
       Values from the constant table SM_ROUTER_RESPONSE_TYPE
    */
    uint8   response_type;
    /* A subset of values from the constant table
       SM_ROUTER_RESPONSE_TYPE_INTERNAL
    */
    uint8   response;
    uint8   sub_block_count;
    /* Optional:
       - SMS-Deliver-Report TPDU sub block
       [SM_ROUTER_SB_TPDU]
       Subblock list:
       SM_ROUTER_SB_TPDU
    */
    uint8   sub_blocks[SM_ROUTER_ANY_SIZE];
    } SM_ROUTER_MT_SM_RESPONSE_REQ_STR;

#define SIZE_SM_ROUTER_MT_SM_RESPONSE_REQ_STR   (8*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_SM_RESPONSE_RESP                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* Indicates success of response request.
       A subset of values from the constant table
       SM_ROUTER_RESPONSE_TYPE_INTERNAL
    */
    uint8   response;
    /* Message reference for MT message. Same as in
       SM_ROUTER_MT_SM_RESPONSE_REQ
    */
    uint8   reference_id;
    } SM_ROUTER_MT_SM_RESPONSE_RESP_STR;

#define SIZE_SM_ROUTER_MT_SM_RESPONSE_RESP_STR   \
        sizeof(SM_ROUTER_MT_SM_RESPONSE_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_STORAGE_STATE_SET_REQ                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* Requested Message Storage state. Indicates that memory full case has
       been solved.
       A subset of values from the constant table
       SM_ROUTER_MESSAGE_STORAGE_STATE
    */
    uint8   new_state;
    } SM_ROUTER_STORAGE_STATE_SET_REQ_STR;

#define SIZE_SM_ROUTER_STORAGE_STATE_SET_REQ_STR   \
        sizeof(SM_ROUTER_STORAGE_STATE_SET_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_STORAGE_STATE_SET_RESP                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* Informs if state change succeeded or not.
       A subset of values from the constant table
       SM_ROUTER_RESPONSE_TYPE_INTERNAL
    */
    uint8   response;
    /* Message Storage state of SM Router.
       Values from the constant table SM_ROUTER_MESSAGE_STORAGE_STATE
    */
    uint8   state;
    } SM_ROUTER_STORAGE_STATE_SET_RESP_STR;

#define SIZE_SM_ROUTER_STORAGE_STATE_SET_RESP_STR   \
        sizeof(SM_ROUTER_STORAGE_STATE_SET_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: SM_ROUTER_MT_TRIGGER_NTF - Valid from version 002.003          */
/* ----------------------------------------------------------------------- */
/* This message is only for SM router server internal use. With this message
   certain actions can be started in the SM router server's MT state machine.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;
    uint8   sub_type;
    /* Action identification number for MT state machine. */
    uint16  action_id;
    uint8   fill1[2];
    } SM_ROUTER_MT_TRIGGER_NTF_STR;

#define SIZE_SM_ROUTER_MT_TRIGGER_NTF_STR   \
        sizeof(SM_ROUTER_MT_TRIGGER_NTF_STR)




/* ----------------------------------------------------------------------- */
/* Notes                                                                   */
/* ----------------------------------------------------------------------- */
/*
   /1/   autogen documentation
         Intranet
         http://rdsuite.europe.nokia.com/products/autogen/documentation.asp
         Link: autogen documentation

   /2/   ISI Server Specification Documentation Guidelines
         Document code: XXXL7714-EN
         DocMan location: eslns42/SRV/Nokia
         DocMan: TP / WP Front End DocMan
         Filename: TP/WP/tpwpfendm.nsf

   /3/   ISI General Information
         Document code: XXXL7715-EN
         DocMan location: eslns42/SRV/Nokia
         DocMan: TP / WP Front End DocMan
         Filename: TP/WP/tpwpfendm.nsf

   /4/   ISI Common Message Descriptions
         Continuus Database: ou1gif
         Continuus Project: GIF_SPECS-ou1gif#browse
         Directory Path: GIF_SPECS/CoreSW
         Filename: i_comm_m.html

   /5/   ISI Common Feature Descriptions
         Continuus Database: ou1gif
         Continuus Project: GIF_SPECS-ou1gif#browse
         Directory Path: GIF_SPECS/CoreSW
         Filename: i_comm_fp.doc

   /6/   SM Router Server Message Descriptions
         Continuus Database: ou1gif
         Continuus Project: GIF_SPECS_S40-browse:project:ou1glint#1
         Directory Path: GIF_SPECS_S40/S40_ISI
         Filename:  i_sm_router_m.html

   /7/   ISI SM Router Server Feature and Protocol Descriptions
         Continuus Database: ou1gif
         Continuus Project: GIF_SPECS_S40-browse:project:ou1glint#1
         Directory Path: GIF_SPECS_S40/S40_ISI
         Filename: sm_router_fp.doc

   /8/   ISI SMS Server Feature and Protocol
         Continuus Database: ou1gif
         Continuus Project: GIF_SPECS_S40-browse:project:ou1glint#1
         Directory Path: GIF_SPECS_S40/S40_ISI
         Filename: i_sms_wm_fp.doc

   /9/   3GPP TS 23.038
         Alphabets and language-specific information

   /10/  3GPP TS 23.040
         Technical realization of the Short Message Service (SMS)

   /11/  3GPP TS 24.011
         Point-to-Point (PP) Short Message Service (SMS) support on mobile
         radio interface
*/


#endif /* _SM_ROUTER_ISI_H */
