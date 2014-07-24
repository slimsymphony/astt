/*
NOKIA                                                             CONFIDENTIAL
MP SW
Modem API
Deliverable software



                  call_modem_isi.h
                  --------------------------------
                  SW Include Document - ANSI C/C++



Continuus Ref:
--------------
database:        ou1gif

project path:    global_interface/modem_interface/modem_vendor_if

name:            call_modem_isi.h

version:         002.008

type:            incl

instance:        ou_cs#1


ISI header file for Modem Call Server

Current   ISI Version : 002.008
Supported ISI Versions: 001.003, 001.004, 002.000, 002.001, 002.002, 002.003, 
                        002.004, 002.005, 002.006, 002.007, 002.008

Generated with autogen version 10_w33 on 08-Nov-2010 15:19:37
DO NOT EDIT - changes will be lost at next autogeneration

Copyright (c) Nokia Corporation. All rights reserved.


ISI version change history

Version     : 002.008    APPROVED    08-Nov-2010    Nokia
Reason      : Only editorial changes
Reference   : Nokia CR id: TK10101254735
Description : -

Version     : 002.007    APPROVED    19-Apr-2010    Nokia
Reason      : Released version
Reference   : -
Description : Approved in inspection.

Version     : 002.006    DRAFT       06-Apr-2010    Nokia
Reason      : Corrections
Reference   : Nokia CR id: ML10040137193
Description : Corrected specification defects.

Version     : 002.005    APPROVED    14-Dec-2009    Nokia
Reason      : Correction
Reference   : Nokia CR id: ML09121440932
Description : Corrected 3GPP references.

Version     : 002.004    APPROVED    26-Nov-2009    Nokia
Reason      : Released version
Reference   : -
Description : Approved in inspection.

Version     : 002.003    DRAFT       09-Nov-2009    Nokia
Reason      : New feature
Reference   : Nokia CR id: ML09110954456
Description : Added Subblock CALL_MODEM_SB_EMERG_NUMBER_MOD_INFO to CALL_MODEM_EMERG_NBR_MODIFY_REQ
              Discontinued Subblock CALL_MODEM_SB_ALERTING_PATTERN in CALL_MODEM_NOTIFICATION_IND
              Added Subblock CALL_MODEM_SB_EMERG_NUMBER_MOD_INFO
              Added Constant CALL_MODEM_NULL
              Added support for permanent memory emergency numbers. Also made
              corrections and updates to specification.

Version     : 002.002    APPROVED    12-May-2009    Nokia
Reason      : Correction
Reference   : -
Description : Changed ISI version defines.

Version     : 002.001    APPROVED    29-Apr-2009    Nokia
Reason      : Released version
Reference   : -
Description : Inspection defects corrected.

Version     : 002.000    DRAFT       14-Apr-2009    Nokia
Reason      : Corrections
Reference   : Nokia CR id: ML09041542192
Description : Added Subblock CALL_MODEM_SB_ALERTING_PATTERN to CALL_MODEM_COMING_IND
              Discontinued Subblock CALL_MODEM_SB_CAUSE in CALL_MODEM_COMING_IND
              Added Subblock CALL_MODEM_SB_CHECK_INFO to CALL_MODEM_SERVICE_DENIED_IND
              Added Entry CALL_MODEM_EMERG_NUMBER_UNKNOWN to CALL_MODEM_EMERG_NUMBER_OPERATION
              Discontinued Entry CALL_MODEM_OP_CUG in CALL_MODEM_OPERATION
              Added Entry CALL_MODEM_OP_UNKNOWN to CALL_MODEM_OPERATION
              Added Entry CALL_MODEM_PROP_UNKNOWN to CALL_MODEM_PROPERTY
              Added Entry CALL_MODEM_RES_CONF_UNKNOWN to CALL_MODEM_RES_CONF_OPERATION
              Corrections and updates to specification.

Version     : 001.004    APPROVED    17-Oct-2008    Nokia
Reason      : Released version
Reference   : -
Description : Corrections and updates to specification. 

Version     : 001.003    DRAFT       22-Sep-2008    Nokia
Reason      : Corrections
Reference   : Nokia CR id: ML08092547479
Description : Changed Message CALL_MODEM_BLACKLIST_CLEAR_REQ
              Changed Subblock CALL_MODEM_SB_NEW_DESTINATION
              Discontinued Entry CALL_MODEM_CAUSE_SIM_LOCK_OPERATIVE in CALL_MODEM_CAUSE
              Corrections and updates to specification. 

------------------------------------------------------------------------------

Description

The purpose of this document is to specify the ISI messages for Modem Call
Server.

Copyright (c) Nokia. This material, including documentation and any related 
computer programs, is protected by copyright controlled by Nokia.
All rights are reserved. Copying, including reproducing, storing, adapting or
translating, any or all of this material requires the prior written consent 
of Nokia. This material also contains confidential information, which may not
be disclosed to others without the prior written consent of Nokia.

*/

#ifndef _CALL_MODEM_ISI_H
#define _CALL_MODEM_ISI_H

#include "isi_conf.h"

#ifndef MODEM_CALL_ISI_VERSION
#define MODEM_CALL_ISI_VERSION
#define MODEM_CALL_ISI_VERSION_Z   2
#define MODEM_CALL_ISI_VERSION_Y   8
#endif

#define MODEM_CALL_ISI_MIN_VERSION(z,y) \
 ((MODEM_CALL_ISI_VERSION_Z == (z) && MODEM_CALL_ISI_VERSION_Y >= (y)) || \
  (MODEM_CALL_ISI_VERSION_Z > (z)))

#if !MODEM_CALL_ISI_MIN_VERSION(1,3)
#error The specified interface version is not supported by this header file
#elif MODEM_CALL_ISI_MIN_VERSION(2,9)
#error The specified interface version is not supported by this header file
#endif


/* ----------------------------------------------------------------------- */
/* Constants                                                               */
/* ----------------------------------------------------------------------- */

/* Value: 0xFFFF */
#define CALL_MODEM_CUG_DEFAULT                   0xFFFF
/* Value: 0x0070 */
#define CALL_MODEM_DTMF_P_DIGIT                  0x0070
/* Value: 0x0077 */
#define CALL_MODEM_DTMF_W_DIGIT                  0x0077
/* Value: 0x0000 */
#define CALL_MODEM_DTMF_NO_TONE                  0x0000
#define CALL_MODEM_NO_LINK_ID                    0x00  /* Value: 0x00 */
#define CALL_MODEM_DTMF_DEFAULT                  0x00  /* Value: 0x00 */
#define CALL_MODEM_DTMF_NO_DELAY                 0x01  /* Value: 0x01 */
#define CALL_MODEM_NULL                          0x00  /* Value: 0x00 */
#define CALL_MODEM_STATUS_SWAP_INITIATED         0x10  /* Obsolete value */
/* Obsolete value */
#define CALL_MODEM_SSC_CLIP                      0x001E
/* Obsolete value */
#define CALL_MODEM_SSC_COLP                      0x004C
/* Obsolete value */
#define CALL_MODEM_SSC_COLR                      0x004D
/* Obsolete value */
#define CALL_MODEM_SSC_CNAP                      0x012C
#define CALL_MODEM_MODE_ORIGINATOR               0x01  /* Obsolete value */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_ADDRESS_TYPE                                  */
/* ----------------------------------------------------------------------- */
/* Address type consists of numbering plan and type of address. The four
   least significant bits (1-4) contain numbering plan and the next three
   bits (5-7) contain type of number. See 'Called Party BCD Number IE' in
   3GPP TS 24.008 ch. 10.5.4.7. Field contains values from octet 3 of address
   IE.
*/
typedef uint8 CALL_MODEM_ADDRESS_TYPE_CONST;

#define CALL_MODEM_NBR_PLAN_UNKNOWN              0x00  /* ----0000 */
#define CALL_MODEM_NBR_PLAN_ISDN_TELEPHONY       0x01  /* ----0001 */
#define CALL_MODEM_NBR_PLAN_DATA                 0x03  /* ----0011 */
#define CALL_MODEM_NBR_PLAN_TELEX                0x04  /* ----0100 */
#define CALL_MODEM_NBR_PLAN_PRIVATE              0x09  /* ----1001 */
#define CALL_MODEM_NBR_PLAN_NATIONAL             0x08  /* ----1000 */
#define CALL_MODEM_NBR_TYPE_UNKNOWN              0x00  /* -000---- */
#define CALL_MODEM_NBR_TYPE_INTERNATIONAL        0x10  /* -001---- */
#define CALL_MODEM_NBR_TYPE_NATIONAL             0x20  /* -010---- */
#define CALL_MODEM_NBR_TYPE_NETWORK_SPECIFIC     0x30  /* -011---- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_PRESENTATION_SCREEN_INDICATOR                 */
/* ----------------------------------------------------------------------- */
/* Presentation and screening indicators are coded into one byte. The two
   least significant bits (1-2) contain screening  indicator and the two bits
   (6-7) contain presenation indicator. See 'Calling Party BCD Number IE' in
   3GPP TS 24.008 ch. 10.5.4.9. Field contains values from octet 3a of
   address IE.
*/
typedef uint8 CALL_MODEM_PRESENTATION_SCREEN_INDICATOR_CONST;

#define CALL_MODEM_PRESENTATION_ALLOWED          0x00  /* -00----- */
#define CALL_MODEM_PRESENTATION_RESTRICTED       0x20  /* -01----- */
#define CALL_MODEM_PRESENTATION_UNAVAILABLE      0x40  /* -10----- */
#define CALL_MODEM_USER_NOT_SCREENED             0x00  /* ------00 */
#define CALL_MODEM_USER_SCREENED_PASSED          0x01  /* ------01 */
#define CALL_MODEM_USER_SCREENED_FAILED          0x02  /* ------10 */
#define CALL_MODEM_SCREEN_NETW_PROVIDED          0x03  /* ------11 */

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_MODE                                         */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_MODE_CONST;

#define CALL_MODEM_MODE_EMERGENCY                0x00
#define CALL_MODEM_MODE_SPEECH                   0x01
#define CALL_MODEM_MODE_ALS_LINE_2               0xA2
#define CALL_MODEM_MODE_MULTIMEDIA               0xA3

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_MODE_INFO                                     */
/* ----------------------------------------------------------------------- */
/* When B0 is set to '0' it indicates a local origination i.e. call is mobile
   originated and when set to '1' it indicates a remote origination i.e. call
   is mobile terminated. Clients shall set the value to '0' when sending
   requests to Modem Call Server. 
*/
typedef uint8 CALL_MODEM_MODE_INFO_CONST;

#define CALL_MODEM_MODE_LOCAL_ORIGINATOR         0x00  /* -------0 */
#define CALL_MODEM_MODE_REMOTE_ORIGINATOR        0x01  /* -------1 */

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_UUS_TYPE                                     */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_UUS_TYPE_CONST;

#define CALL_MODEM_UUS_TYPE_UUS1                 0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_UUS_ACTIVATION_TYPE                          */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_UUS_ACTIVATION_TYPE_CONST;

#define CALL_MODEM_UUS_ACTIVATION_IMPLICIT       0x01

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_ID                                            */
/* ----------------------------------------------------------------------- */
/* NOTE: Call ID values in range 1-7 are used dynamically as unique call IDs
   when referencing to a specific call.
*/
typedef uint8 CALL_MODEM_ID_CONST;

#define CALL_MODEM_ID_NONE                       0x00  /* -----000 */
#define CALL_MODEM_ID_1                          0x01  /* -----001 */
#define CALL_MODEM_ID_2                          0x02  /* -----010 */
#define CALL_MODEM_ID_3                          0x03  /* -----011 */
#define CALL_MODEM_ID_4                          0x04  /* -----100 */
#define CALL_MODEM_ID_5                          0x05  /* -----101 */
#define CALL_MODEM_ID_6                          0x06  /* -----110 */
#define CALL_MODEM_ID_7                          0x07  /* -----111 */
#define CALL_MODEM_ID_CONFERENCE                 0x10  /* ---1---- */
#define CALL_MODEM_ID_WAITING                    0x20  /* --1----- */
#define CALL_MODEM_ID_HOLD                       0x40  /* -1------ */
#define CALL_MODEM_ID_ACTIVE                     0x80  /* 1------- */
#define CALL_MODEM_ID_ALL                        0xF0  /* 1111---- */

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_CAUSE_TYPE_SENDER                            */
/* ----------------------------------------------------------------------- */
/* Client cause value. Clients shall use this value or network type in call
   release requests that are sent to Call Server.
*/
#define CALL_MODEM_CAUSE_TYPE_CLIENT             0x01
/* Call Server cause value. Clients shall not use this value in requests that
   are sent to Call Server.
*/
#define CALL_MODEM_CAUSE_TYPE_SERVER             0x02
/* Network interface cause value. Clients shall use this value or client type
   in call release requests that are sent to Call Server.
*/
#define CALL_MODEM_CAUSE_TYPE_NETWORK            0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_CAUSE                                        */
/* ----------------------------------------------------------------------- */
/* Call Server generated cause values. Call Server uses these causes to
   indicate e.g. errors in validation of received requests, call releases
   that are caused modem state (e.g. no service, no SIM card) and channel
   lost. Clients shall use causes CALL_MODEM_CAUSE_RELEASE_BY_USER and
   CALL_MODEM_CAUSE_BUSY_USER_REQUEST in release requests that are sent to
   Call Server.
*/
typedef uint8 CALL_MODEM_CAUSE_CONST;

/* Indicates that call does not exists e.g. in CALL_STATUS_RESP. */
#define CALL_MODEM_CAUSE_NO_CALL                 0x01
/* Can be used by client to indicate normal call clearing. Maps to cause 16
   in network interface.
*/
#define CALL_MODEM_CAUSE_RELEASE_BY_USER         0x03
/* Can be used by client to indicate that user has rejected the call. Maps to
   cause 17 in network interface.
*/
#define CALL_MODEM_CAUSE_BUSY_USER_REQUEST       0x04
/* Indicates that request has been erroneus. */
#define CALL_MODEM_CAUSE_ERROR_REQUEST           0x05
/* Indicates that procedure is rejected because call is active. */
#define CALL_MODEM_CAUSE_CALL_ACTIVE             0x07
/* Indicates that procedure is rejected because no call is active. */
#define CALL_MODEM_CAUSE_NO_CALL_ACTIVE          0x08
/* Indicates that procedure is rejected because call mode is invalid. */
#define CALL_MODEM_CAUSE_INVALID_CALL_MODE       0x09
/* Indicates that procedure is rejected because address is too long. */
#define CALL_MODEM_CAUSE_TOO_LONG_ADDRESS        0x0B
/* Indicates that procedure is rejected because address is invalid. */
#define CALL_MODEM_CAUSE_INVALID_ADDRESS         0x0C
/* Indicates that call is cleared because emergency call establishment has
   started.
*/
#define CALL_MODEM_CAUSE_EMERGENCY               0x0D
/* Indicates that call is cleared because of no service. */
#define CALL_MODEM_CAUSE_NO_SERVICE              0x0E
/* Call creation has failed because SIM code required or PIN rights lost. */
#define CALL_MODEM_CAUSE_CODE_REQUIRED           0x10
/* Indicates that procedure is not allowed. Used e.g. if call control or call
   answer request arrives to invalid call state.
*/
#define CALL_MODEM_CAUSE_NOT_ALLOWED             0x11
/* Indicates that DMTF handling error has occurred. */
#define CALL_MODEM_CAUSE_DTMF_ERROR              0x12
/* Indicates that call is cleared because call re-establishment has failed. 
*/
#define CALL_MODEM_CAUSE_CHANNEL_LOSS            0x13
/* Call creation has failed because of Fixed Dialling Number check. */
#define CALL_MODEM_CAUSE_FDN_NOT_OK              0x14
/* Blacklist has blocked the number. */
#define CALL_MODEM_CAUSE_BLACKLIST_BLOCKED       0x16
/* Blacklist has delayed the call establishment to the number. */
#define CALL_MODEM_CAUSE_BLACKLIST_DELAYED       0x17
/* Indicates that emergency call has failed because network is not found. */
#define CALL_MODEM_CAUSE_EMERGENCY_FAILURE       0x1A
/* Call creation has failed because no connection to SIM card. */
#define CALL_MODEM_CAUSE_NO_SIM                  0x1F

#if !MODEM_CALL_ISI_MIN_VERSION(1,3)
/* Call creation has failed because SIM lock is operative. */
#define CALL_MODEM_CAUSE_SIM_LOCK_OPERATIVE      0x20
#endif /* !MODEM_CALL_ISI_MIN_VERSION(1,3) */

/* Indicates that procedure is rejected because DTMF sending is ongoing. */
#define CALL_MODEM_CAUSE_DTMF_SEND_ONGOING       0x24
/* Indicates that procedure is rejected because CS is inactive. */
#define CALL_MODEM_CAUSE_CS_INACTIVE             0x25
/* Indicates that procedure is rejected because startup is ongoing. */
#define CALL_MODEM_CAUSE_NOT_READY               0x26
/* Indicates that procedure is rejected because Bearer Capability negotiation
   has failed. 
*/
#define CALL_MODEM_CAUSE_INCOMPATIBLE_DEST       0x27

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_NW_CAUSE                                     */
/* ----------------------------------------------------------------------- */
/* Cause values used in network interface. See 'Cause IE' in 3GPP TS 24.008
   ch. 10.5.4.11.
   
   For MT releases Call Server generates cause values in some cases
   internally. 
   
   On MM connection failures following cause values are used: 
   - 127 MM connection establishment fails
   - 102 MM connection establishment fails to timeout
   - 47  MM connection is released abnormally e.g. during active call
   - 34  MM connection is interrupted by lower layer failure.
   
   When call release message that contain invalid contents is received
   following cause values are used:
   - 96  Invalid mandatory information
   - 99  Informatio element non-existent or not implemented
   
   When Supplementary Service operation (e.g. conference build) is rejected
   and failure response from network does not contain 'Cause IE' following
   cause values are used: 
   - 29  Facility rejected
   Same cause value is used also Supplementary Service operation fails to
   timeout.
*/
typedef uint8 CALL_MODEM_NW_CAUSE_CONST;

#define CALL_MODEM_NW_CAUSE_UNASSIGNED_NUMBER    0x01
#define CALL_MODEM_NW_CAUSE_NO_ROUTE             0x03
#define CALL_MODEM_NW_CAUSE_CH_UNACCEPTABLE      0x06
#define CALL_MODEM_NW_CAUSE_OPER_BARRING         0x08
#define CALL_MODEM_NW_CAUSE_NORMAL               0x10
#define CALL_MODEM_NW_CAUSE_USER_BUSY            0x11
#define CALL_MODEM_NW_CAUSE_NO_USER_RESPONSE     0x12
#define CALL_MODEM_NW_CAUSE_ALERT_NO_ANSWER      0x13
#define CALL_MODEM_NW_CAUSE_CALL_REJECTED        0x15
#define CALL_MODEM_NW_CAUSE_NUMBER_CHANGED       0x16
#define CALL_MODEM_NW_CAUSE_NON_SELECT_CLEAR     0x1A
#define CALL_MODEM_NW_CAUSE_DEST_OUT_OF_ORDER    0x1B
#define CALL_MODEM_NW_CAUSE_INVALID_NUMBER       0x1C
#define CALL_MODEM_NW_CAUSE_FACILITY_REJECTED    0x1D
#define CALL_MODEM_NW_CAUSE_RESP_TO_STATUS       0x1E
#define CALL_MODEM_NW_CAUSE_NORMAL_UNSPECIFIED   0x1F
#define CALL_MODEM_NW_CAUSE_NO_CHANNEL           0x22
#define CALL_MODEM_NW_CAUSE_NETW_OUT_OF_ORDER    0x26
#define CALL_MODEM_NW_CAUSE_TEMPORARY_FAILURE    0x29
#define CALL_MODEM_NW_CAUSE_CONGESTION           0x2A
#define CALL_MODEM_NW_CAUSE_ACCESS_INFO_DISC     0x2B
#define CALL_MODEM_NW_CAUSE_CHANNEL_NA           0x2C
#define CALL_MODEM_NW_CAUSE_RESOURCES_NA         0x2F
#define CALL_MODEM_NW_CAUSE_QOS_NA               0x31
#define CALL_MODEM_NW_CAUSE_FACILITY_UNSUBS      0x32
#define CALL_MODEM_NW_CAUSE_COMING_BARRED_CUG    0x37
#define CALL_MODEM_NW_CAUSE_BC_UNAUTHORIZED      0x39
#define CALL_MODEM_NW_CAUSE_BC_NA                0x3A
#define CALL_MODEM_NW_CAUSE_SERVICE_NA           0x3F
#define CALL_MODEM_NW_CAUSE_BEARER_NOT_IMPL      0x41
#define CALL_MODEM_NW_CAUSE_ACM_MAX              0x44
#define CALL_MODEM_NW_CAUSE_FACILITY_NOT_IMPL    0x45
#define CALL_MODEM_NW_CAUSE_ONLY_RDI_BC          0x46
#define CALL_MODEM_NW_CAUSE_SERVICE_NOT_IMPL     0x4F
#define CALL_MODEM_NW_CAUSE_INVALID_TI           0x51
#define CALL_MODEM_NW_CAUSE_NOT_IN_CUG           0x57
#define CALL_MODEM_NW_CAUSE_INCOMPATIBLE_DEST    0x58
#define CALL_MODEM_NW_CAUSE_INV_TRANS_NET_SEL    0x5B
#define CALL_MODEM_NW_CAUSE_SEMANTICAL_ERR       0x5F
#define CALL_MODEM_NW_CAUSE_INVALID_MANDATORY    0x60
#define CALL_MODEM_NW_CAUSE_MSG_TYPE_INEXIST     0x61
#define CALL_MODEM_NW_CAUSE_MSG_TYPE_INCOMPAT    0x62
#define CALL_MODEM_NW_CAUSE_IE_NON_EXISTENT      0x63
#define CALL_MODEM_NW_CAUSE_COND_IE_ERROR        0x64
#define CALL_MODEM_NW_CAUSE_MSG_INCOMPATIBLE     0x65
#define CALL_MODEM_NW_CAUSE_TIMER_EXPIRY         0x66
#define CALL_MODEM_NW_CAUSE_PROTOCOL_ERROR       0x6F
#define CALL_MODEM_NW_CAUSE_INTERWORKING         0x7F

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_STATUS                                       */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_STATUS_CONST;

#define CALL_MODEM_STATUS_IDLE                   0x00
#define CALL_MODEM_STATUS_CREATE                 0x01
#define CALL_MODEM_STATUS_COMING                 0x02
#define CALL_MODEM_STATUS_PROCEEDING             0x03
#define CALL_MODEM_STATUS_MO_ALERTING            0x04
#define CALL_MODEM_STATUS_MT_ALERTING            0x05
#define CALL_MODEM_STATUS_WAITING                0x06
#define CALL_MODEM_STATUS_ANSWERED               0x07
#define CALL_MODEM_STATUS_ACTIVE                 0x08
#define CALL_MODEM_STATUS_MO_RELEASE             0x09
#define CALL_MODEM_STATUS_MT_RELEASE             0x0A
#define CALL_MODEM_STATUS_HOLD_INITIATED         0x0B
#define CALL_MODEM_STATUS_HOLD                   0x0C
#define CALL_MODEM_STATUS_RETRIEVE_INITIATED     0x0D
#define CALL_MODEM_STATUS_RECONNECT_PENDING      0x0E

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_PRESENT_INFO                                  */
/* ----------------------------------------------------------------------- */
/* The four least significant bits (1-4) contain call present. Other bits are
   spare.
*/
typedef uint8 CALL_MODEM_PRESENT_INFO_CONST;

#define CALL_MODEM_PRESENT                       0x00  /* ----0000 */
#define CALL_MODEM_NOT_PRESENT                   0x01  /* ----0001 */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_ALERTING_INFO                                 */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_ALERTING_INFO_CONST;

#define CALL_MODEM_AI_GEN_ALERTING_TONE          0x01  /* -------1 */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_RELEASE_INFO                                  */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_RELEASE_INFO_CONST;

#define CALL_MODEM_RI_IN_BAND_INFO               0x01  /* -------1 */

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_OPERATION                                    */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_OPERATION_CONST;

/* Used in CALL_MODEM_CONTROL_RESP if requested call operation is unknown. In
   that case CALL_MODEM_SERVICE_DENIED_IND is not sent for rejected
   operation. Shall not be used in requests that are sent to Call Server.
*/
#define CALL_MODEM_OP_UNKNOWN                    0x00
#define CALL_MODEM_OP_HOLD                       0x01
#define CALL_MODEM_OP_RETRIEVE                   0x02
#define CALL_MODEM_OP_SWAP                       0x03
#define CALL_MODEM_OP_CONFERENCE_BUILD           0x04
#define CALL_MODEM_OP_CONFERENCE_SPLIT           0x05

#if !MODEM_CALL_ISI_MIN_VERSION(2,0)
#define CALL_MODEM_OP_CUG                        0xA0
#endif /* !MODEM_CALL_ISI_MIN_VERSION(2,0) */

#define CALL_MODEM_OP_TRANSFER                   0xA1

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_DTMF_STATUS                                  */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_DTMF_STATUS_CONST;

#define CALL_MODEM_DTMF_IDLE                     0x00
#define CALL_MODEM_DTMF_ACTIVE                   0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_RECONNECT_STATUS                             */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_RECONNECT_STATUS_CONST;

#define CALL_MODEM_RECONNECT_PENDING             0x01
#define CALL_MODEM_RECONNECTED                   0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_PROPERTY                                     */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_PROPERTY_CONST;

/* Used in CALL_MODEM_PROPERTY_GET_RESP and CALL_MODEM_PROPERTY_SET_RESP if
   requested property or property value is unknown. Shall not be used in
   requests that are sent to Call Server.
*/
#define CALL_MODEM_PROP_UNKNOWN                  0x00
#define CALL_MODEM_PROP_ALL                      0x01
#define CALL_MODEM_PROP_IMMEDIATE_CONNECT        0xA0
#define CALL_MODEM_PROP_CUG_INFO                 0xA1
#define CALL_MODEM_PROP_CALL_MODE_DEFAULT        0xA2
#define CALL_MODEM_PROP_ALS                      0xA6
#define CALL_MODEM_PROP_LINE_ID                  0xA8
#define CALL_MODEM_PROP_EMERG                    0xA9
#define CALL_MODEM_PROP_CTM                      0xAC

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_PROP_IMMEDIATE_CONNECT                       */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_PROP_IMMEDIATE_CONNECT_CONST;

#define CALL_MODEM_IMM_CONNECT_OFF               0x00
#define CALL_MODEM_IMM_CONNECT_ON                0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_PROP_ALS                                     */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_PROP_ALS_CONST;

#define CALL_MODEM_PROP_ALS_LINE_NORMAL          0x00
#define CALL_MODEM_PROP_ALS_LINE_2               0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_PROP_LINE_ID                                 */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_PROP_LINE_ID_CONST;

#define CALL_MODEM_PROP_PRESENT_DEFAULT          0x00
#define CALL_MODEM_PROP_PRESENT_ALLOWED          0x01
#define CALL_MODEM_PROP_PRESENT_RESTRICTED       0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_PROP_EMERG                                   */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_PROP_EMERG_CONST;

#define CALL_MODEM_PROP_EMERG_CHK_DEFAULT        0x00
#define CALL_MODEM_PROP_EMERG_CHK_DISABLED       0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_PROP_CTM                                     */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_PROP_CTM_CONST;

#define CALL_MODEM_PROP_CTM_NOT_SUPPORTED        0x00
#define CALL_MODEM_PROP_CTM_SUPPORTED            0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_EMERG_NUMBER_OPERATION                       */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_EMERG_NUMBER_OPERATION_CONST;

#define CALL_MODEM_EMERG_NUMBER_REMOVE           0x00
#define CALL_MODEM_EMERG_NUMBER_ADD              0x01
/* Used in CALL_MODEM_EMERG_NBR_MODIFY_RESP if requested emergency number
   operation is unknown. Shall not be used in requests that are sent to Call
   Server.
*/
#define CALL_MODEM_EMERG_NUMBER_UNKNOWN          0xFF

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_EMERG_NUMBER_CHECK_STATUS                    */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_EMERG_NUMBER_CHECK_STATUS_CONST;

#define CALL_MODEM_EMERG_NBR_CHECK_FAIL          0x00
#define CALL_MODEM_EMERG_NBR_CHECK_PASS          0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_PREFERENTIAL_CUG                             */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_PREFERENTIAL_CUG_CONST;

#define CALL_MODEM_CUG_PREF                      0x00
#define CALL_MODEM_CUG_PREF_SUPPRESS             0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_CUG_OUTGOING_ACCESS                          */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_CUG_OUTGOING_ACCESS_CONST;

#define CALL_MODEM_CUG_OA                        0x00
#define CALL_MODEM_CUG_OA_SUPPRESS               0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_ALERTING_PATTERN                             */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_ALERTING_PATTERN_CONST;

#define CALL_MODEM_ALERTING_LEVEL_0              0x00
#define CALL_MODEM_ALERTING_LEVEL_1              0x01
#define CALL_MODEM_ALERTING_LEVEL_2              0x02
#define CALL_MODEM_ALERTING_CATEGORY_1           0x04
#define CALL_MODEM_ALERTING_CATEGORY_2           0x05
#define CALL_MODEM_ALERTING_CATEGORY_3           0x06
#define CALL_MODEM_ALERTING_CATEGORY_4           0x07
#define CALL_MODEM_ALERTING_CATEGORY_5           0x08

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_CONDITION                                    */
/* ----------------------------------------------------------------------- */
/* See 'Cause IE' in 3GPP TS 24.008 ch. 10.5.4.11. Field contains values from
   cause diagnostics octet 5 of 'Cause IE' when octet is coded according to
   NOTE 9. Note is applicable for causes 1, 3, 16, 21 and 49.
*/
typedef uint8 CALL_MODEM_CONDITION_CONST;

#define CALL_MODEM_COND_UNKNOWN                  0x00
#define CALL_MODEM_COND_PERMANENT                0x01
#define CALL_MODEM_COND_TRANSIENT                0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_SS_DIAGNOSTICS                               */
/* ----------------------------------------------------------------------- */
/* See 'Cause IE' in 3GPP TS 24.008 ch. 10.5.4.11. Field contains values from
   cause diagnostics octet 5 of 'Cause IE' when octet is coded according to
   NOTE 1. Note is applicable for causes 17, 29, 34, 50, 55, 69 and 87
*/
typedef uint8 CALL_MODEM_SS_DIAGNOSTICS_CONST;

#define CALL_MODEM_SSD_OUTGOING_BARR_CUG         0x01
#define CALL_MODEM_SSD_NO_CUG                    0x02
#define CALL_MODEM_SSD_UNKNOWN_CUG               0x03
#define CALL_MODEM_SSD_INCOMPATIBLE_CUG          0x04
#define CALL_MODEM_SSD_CUG_FAIL                  0x05
#define CALL_MODEM_SSD_CLIR_NOT_SUBSCRIBED       0x06

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_NOTIFICATION_INDICATOR                       */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_NOTIFICATION_INDICATOR_CONST;

#define CALL_MODEM_NOTIFY_USER_SUSPENDED         0x00
#define CALL_MODEM_NOTIFY_USER_RESUMED           0x01
#define CALL_MODEM_NOTIFY_BEARER_CHANGE          0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_MMI_SS_CODES                                 */
/* ----------------------------------------------------------------------- */
/* See 'Codes for defined Supplementary Services' in 3GPP TS 22.030 Annex B. 
*/
typedef uint16 CALL_MODEM_MMI_SS_CODES_CONST;

#define CALL_MODEM_SSC_ALL_FWDS                  0x0002
#define CALL_MODEM_SSC_ALL_COND_FWD              0x0004
#define CALL_MODEM_SSC_CFU                       0x0015
#define CALL_MODEM_SSC_CFB                       0x0043
#define CALL_MODEM_SSC_CFNRY                     0x003D
#define CALL_MODEM_SSC_CFGNC                     0x003E
#define CALL_MODEM_SSC_OUTGOING_BARR_SERV        0x014D
#define CALL_MODEM_SSC_INCOMING_BARR_SERV        0x0161
#define CALL_MODEM_SSC_CALL_WAITING              0x002B
#define CALL_MODEM_SSC_CLIR                      0x001F
#define CALL_MODEM_SSC_ECT                       0x0060
#define CALL_MODEM_SSC_MPTY                      0xFFFE
#define CALL_MODEM_SSC_CALL_HOLD                 0xFFFF

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_SS_STATUS                                     */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_SS_STATUS_CONST;

#define CALL_MODEM_SS_STATUS_ACTIVE              0x01  /* -------1 */
#define CALL_MODEM_SS_STATUS_REGISTERED          0x02  /* ------1- */
#define CALL_MODEM_SS_STATUS_PROVISIONED         0x04  /* -----1-- */
#define CALL_MODEM_SS_STATUS_QUIESCENT           0x08  /* ----1--- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_SS_NOTIFICATION                               */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_SS_NOTIFICATION_CONST;

#define CALL_MODEM_SSN_INCOMING_IS_FWD           0x01  /* -------1 */
#define CALL_MODEM_SSN_INCOMING_FWD              0x02  /* ------1- */
#define CALL_MODEM_SSN_OUTGOING_FWD              0x04  /* -----1-- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_SS_INDICATOR                                  */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_SS_INDICATOR_CONST;

#define CALL_MODEM_SSI_CALL_IS_WAITING           0x01  /* -------1 */
#define CALL_MODEM_SSI_MPTY                      0x02  /* ------1- */
#define CALL_MODEM_SSI_CLIR_SUPPR_REJ            0x04  /* -----1-- */

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_SS_HOLD_INDICATOR                            */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_SS_HOLD_INDICATOR_CONST;

#define CALL_MODEM_HOLD_IND_RETRIEVED            0x00
#define CALL_MODEM_HOLD_IND_ON_HOLD              0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_SS_ECT_INDICATOR                             */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_SS_ECT_INDICATOR_CONST;

#define CALL_MODEM_ECT_CALL_STATE_ALERT          0x00
#define CALL_MODEM_ECT_CALL_STATE_ACTIVE         0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_BLACKLIST_DURATION                           */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_BLACKLIST_DURATION_CONST;

#define CALL_MODEM_BLACKLIST_TIMEOUT             0x00
#define CALL_MODEM_BLACKLIST_DURATION_5          0x05
#define CALL_MODEM_BLACKLIST_DURATION_60         0x3C
#define CALL_MODEM_BLACKLIST_DURATION_180        0xB4

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_BC_CHECK_RESULT                              */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_BC_CHECK_RESULT_CONST;

#define CALL_MODEM_BC_CHECK_RESULT_FAIL          0x00
#define CALL_MODEM_BC_CHECK_RESULT_OK            0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_DTMF_PAUSE_VALUES                            */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_DTMF_PAUSE_VALUES_CONST;

#define CALL_MODEM_DTMF_PAUSE_1S                 0x01
#define CALL_MODEM_DTMF_PAUSE_2S                 0x02
#define CALL_MODEM_DTMF_PAUSE_3S                 0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_DTMF_INFO_VALUES                             */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_DTMF_INFO_VALUES_CONST;

/* CALL_MODEM_DTMF_TONE_IND indications are sent to clients during DTMF
   string sending.
*/
#define CALL_MODEM_DTMF_ENABLE_TONE_IND_SEND     0x01
/* CALL_MODEM_DTMF_TONE_IND indications are not sent to clients during DTMF
   string sending.
*/
#define CALL_MODEM_DTMF_DISABLE_TONE_IND_SEND    0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_CAUSE_OF_NO_CLI_VALUES                       */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_CAUSE_OF_NO_CLI_VALUES_CONST;

#define CALL_MODEM_CLI_UNAVAILABLE               0x01
#define CALL_MODEM_CLI_REJECT_BY_USER            0x02
#define CALL_MODEM_CLI_INTERACTION               0x03
#define CALL_MODEM_CLI_COIN_LINE_PAYPHONE        0x04

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_MM_CAUSE_VALUES                              */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_MM_CAUSE_VALUES_CONST;

#define CALL_MODEM_MM_CAUSE_HLR_IMSI_UNKNOWN     0x02
#define CALL_MODEM_MM_CAUSE_ILLEGAL_MS           0x03
#define CALL_MODEM_MM_CAUSE_VLR_IMSI_UNKNOWN     0x04
#define CALL_MODEM_MM_CAUSE_IMEI_NOT_ACCEPTED    0x05
#define CALL_MODEM_MM_CAUSE_ILLEGAL_ME           0x06
#define CALL_MODEM_MM_CAUSE_PLMN_NOT_ALLOWED     0x0B
#define CALL_MODEM_MM_CAUSE_LA_NOT_ALLOWED       0x0C
#define CALL_MODEM_MM_CAUSE_ROAM_NOT_ALLOWED_LA  0x0D
#define CALL_MODEM_MM_CAUSE_NO_SUITABLE_CELLS_LA 0x0F
#define CALL_MODEM_MM_CAUSE_NETWORK_FAILURE      0x11
#define CALL_MODEM_MM_CAUSE_MAC_FAILURE          0x14
#define CALL_MODEM_MM_CAUSE_SYNC_FAILURE         0x15
#define CALL_MODEM_MM_CAUSE_CONGESTION           0x16
#define CALL_MODEM_MM_CAUSE_AUTH_UNACCEPTABLE    0x17
#define CALL_MODEM_MM_CAUSE_NOT_SUPP_S_OPTION    0x20
#define CALL_MODEM_MM_CAUSE_NOT_SUBS_S_OPTION    0x21
#define CALL_MODEM_MM_CAUSE_OUT_OF_ORDER_S_OPTION 0x22
#define CALL_MODEM_MM_CAUSE_CALL_NOT_IDENTIFIED  0x26
#define CALL_MODEM_MM_CAUSE_SEMANT_INCORRECT     0x5F
#define CALL_MODEM_MM_CAUSE_INV_MAND_INFORMATION 0x60
#define CALL_MODEM_MM_CAUSE_NON_EXISTENT_MSG_TYPE 0x61
#define CALL_MODEM_MM_CAUSE_NOT_COMP_MSG_TYPE    0x62
#define CALL_MODEM_MM_CAUSE_NOT_EXISTENT_IE      0x63
#define CALL_MODEM_MM_CAUSE_CONDITIONAL_IE_ERROR 0x64
#define CALL_MODEM_MM_CAUSE_MSG_NOT_COMPATIBLE   0x65
#define CALL_MODEM_MM_CAUSE_PROTOCOL_ERROR       0x6F

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_ALS_STATUS                                   */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_ALS_STATUS_CONST;

/* This is used e.g. in startup if Call Server has not yet accuired ALS
   status from SIM.
*/
#define CALL_MODEM_ALS_STATUS_NOT_READY          0x00
#define CALL_MODEM_ALS_STATUS_DISABLED           0x01
#define CALL_MODEM_ALS_STATUS_ENABLED            0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_AUTO_ST_CHANGE                               */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_AUTO_ST_CHANGE_CONST;

#define CALL_MODEM_AUTO_ST_CHANGE_DISABLE        0x00
#define CALL_MODEM_AUTO_ST_CHANGE_DISABLE_WAITING 0x01

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_REQ_ADDITIONAL_INFO                           */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_REQ_ADDITIONAL_INFO_CONST;

/* Default value */
#define CALL_MODEM_ADD_INFO_NONE                 0x00  /* 00000000 */
#define CALL_MODEM_ADD_INFO_EMERG_CALL           0x01  /* -------1 */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_EMERG_SERVICE_CATEGORY                        */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_EMERG_SERVICE_CATEGORY_CONST;

/* Default value */
#define CALL_MODEM_SERVICE_CAT_NONE              0x00  /* 00000000 */
#define CALL_MODEM_SERVICE_CAT_POLICE            0x01  /* -------1 */
#define CALL_MODEM_SERVICE_CAT_AMBULANCE         0x02  /* ------1- */
#define CALL_MODEM_SERVICE_CAT_FIRE_BRIGADE      0x04  /* -----1-- */
#define CALL_MODEM_SERVICE_CAT_MARINE_GUARD      0x08  /* ----1--- */
#define CALL_MODEM_SERVICE_CAT_MOUNTAIN_RESCUE   0x10  /* ---1---- */

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_STATUS_MOD                                   */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_STATUS_MOD_CONST;

#define CALL_MODEM_STATUS_MODE_DEFAULT           0x00
#define CALL_MODEM_STATUS_MODE_ADDR              0x01
#define CALL_MODEM_STATUS_MODE_ADDR_AND_ORIGIN   0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_USER_CONN                                    */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_USER_CONN_CONST;

#define CALL_MODEM_USER_CONN_CLOSED              0x00
#define CALL_MODEM_USER_CONN_ATTACHED            0x01

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_EMERG_NBR_ORIGIN                              */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_EMERG_NBR_ORIGIN_CONST;

#define CALL_MODEM_EMERG_NBR_ORIG_HARD_CODED     0x01  /* -------1 */
#define CALL_MODEM_EMERG_NBR_ORIG_SIM            0x02  /* ------1- */
#define CALL_MODEM_EMERG_NBR_ORIG_NETWORK        0x04  /* -----1-- */
#define CALL_MODEM_EMERG_NBR_ORIG_PERMANENT_MEM  0x08  /* ----1--- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_RESOURCE_IDS                                  */
/* ----------------------------------------------------------------------- */
typedef uint16 CALL_MODEM_RESOURCE_IDS_CONST;

#define CALL_MODEM_RES_ID_MO_INIT                0x0001  /* ---------------1 */
#define CALL_MODEM_RES_ID_MT_INIT                0x0002  /* --------------1- */
#define CALL_MODEM_RES_ID_MT_ANSWER              0x0004  /* -------------1-- */
#define CALL_MODEM_RES_ID_HOLD                   0x0008  /* ------------1--- */
#define CALL_MODEM_RES_ID_RETRIEVE               0x0010  /* -----------1---- */
#define CALL_MODEM_RES_ID_AUTO_HOLD              0x0020  /* ----------1----- */
#define CALL_MODEM_RES_ID_AUTO_RETRIEVE          0x0040  /* ---------1------ */
#define CALL_MODEM_RES_ID_SWAP                   0x0080  /* --------1------- */
#define CALL_MODEM_RES_ID_CONF_BUILD             0x0100  /* -------1-------- */
#define CALL_MODEM_RES_ID_CONF_SPLIT             0x0200  /* ------1--------- */
#define CALL_MODEM_RES_ID_TRANSFER               0x0400  /* -----1---------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_RESOURCE_IDS_MASK                             */
/* ----------------------------------------------------------------------- */
typedef uint16 CALL_MODEM_RESOURCE_IDS_MASK_CONST;

#define CALL_MODEM_RES_ID_MASK_MO_INIT           0x0001  /* ---------------1 */
#define CALL_MODEM_RES_ID_MASK_MT_INIT           0x0002  /* --------------1- */
#define CALL_MODEM_RES_ID_MASK_MT_ANSWER         0x0004  /* -------------1-- */
#define CALL_MODEM_RES_ID_MASK_HOLD              0x0008  /* ------------1--- */
#define CALL_MODEM_RES_ID_MASK_RETRIEVE          0x0010  /* -----------1---- */
#define CALL_MODEM_RES_ID_MASK_AUTO_HOLD         0x0020  /* ----------1----- */
#define CALL_MODEM_RES_ID_MASK_AUTO_RETRIEVE     0x0040  /* ---------1------ */
#define CALL_MODEM_RES_ID_MASK_SWAP              0x0080  /* --------1------- */
#define CALL_MODEM_RES_ID_MASK_CONF_BUILD        0x0100  /* -------1-------- */
#define CALL_MODEM_RES_ID_MASK_CONF_SPLIT        0x0200  /* ------1--------- */
#define CALL_MODEM_RES_ID_MASK_TRANSFER          0x0400  /* -----1---------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_RESOURCE_IDS_CONF_REQ                         */
/* ----------------------------------------------------------------------- */
typedef uint16 CALL_MODEM_RESOURCE_IDS_CONF_REQ_CONST;

#define CALL_MODEM_RES_ID_CONF_MO_INIT           0x0001  /* ---------------1 */
#define CALL_MODEM_RES_ID_CONF_MT_INIT           0x0002  /* --------------1- */
#define CALL_MODEM_RES_ID_CONF_MT_ANSWER         0x0004  /* -------------1-- */
#define CALL_MODEM_RES_ID_CONF_HOLD              0x0008  /* ------------1--- */
#define CALL_MODEM_RES_ID_CONF_RETRIEVE          0x0010  /* -----------1---- */
#define CALL_MODEM_RES_ID_CONF_AUTO_HOLD         0x0020  /* ----------1----- */
#define CALL_MODEM_RES_ID_CONF_AUTO_RETRIEVE     0x0040  /* ---------1------ */
#define CALL_MODEM_RES_ID_CONF_SWAP              0x0080  /* --------1------- */
#define CALL_MODEM_RES_ID_CONF_CONF_BUILD        0x0100  /* -------1-------- */
#define CALL_MODEM_RES_ID_CONF_CONF_SPLIT        0x0200  /* ------1--------- */
#define CALL_MODEM_RES_ID_CONF_TRANSFER          0x0400  /* -----1---------- */

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_RESOURCE_STATUS                              */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_RESOURCE_STATUS_CONST;

#define CALL_MODEM_RESOURCE_ALLOWED              0x01
#define CALL_MODEM_RESOURCE_DENIED               0x02

/* ----------------------------------------------------------------------- */
/* Bitmask Table: CALL_MODEM_CHECK_INFO                                    */
/* ----------------------------------------------------------------------- */
/* This field can be used to disable various checks that are made for MO
   calls in Call Server i.e. they are already made by the client or not
   needed for the call. 
*/
typedef uint8 CALL_MODEM_CHECK_INFO_CONST;

#define CALL_MODEM_CHK_DISABLE_NONE              0x00  /* 00000000 */
#define CALL_MODEM_CHK_DISABLE_EMERG             0x01  /* -------1 */
#define CALL_MODEM_CHK_DISABLE_FDN               0x02  /* ------1- */
#define CALL_MODEM_CHK_DISABLE_BLACKLIST         0x04  /* -----1-- */
#define CALL_MODEM_CHK_DISABLE_ALS               0x08  /* ----1--- */

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_RES_CONF_STATUS                              */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_RES_CONF_STATUS_CONST;

/* Sent when Modem Call Server starts up. */
#define CALL_MODEM_RES_CONF_STARTUP              0x01
#define CALL_MODEM_RES_CONF_RECONFIGURED         0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_RES_CONF_OPERATION                           */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_RES_CONF_OPERATION_CONST;

/* Used in CALL_MODEM_RESOURCE_CONF_RESP if resource configuration operation
   is unknown. Shall not be used in requests that are sent to Call Server.
*/
#define CALL_MODEM_RES_CONF_UNKNOWN              0x00
#define CALL_MODEM_RES_CONF_GET                  0x01
#define CALL_MODEM_RES_CONF_SET                  0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_LINE_ID                                      */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_LINE_ID_CONST;

/* Default line ID value from Modem Call Server properties is used for the
   call.
*/
#define CALL_MODEM_PRESENT_DEFAULT               0x00
/* Overrides default line ID value in Modem Call Server properties for the
   call
*/
#define CALL_MODEM_PRESENT_ALLOWED               0x01
/* Overrides default line ID value in Modem Call Server properties for the
   call
*/
#define CALL_MODEM_PRESENT_RESTRICTED            0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_MSG                                          */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_MSG_CONST;

#define CALL_MODEM_MSG_SETUP                     0x01  /* Setup message. */
/* Connect message. */
#define CALL_MODEM_MSG_CONNECT                   0x02
/* First releasing message or internal call release. */
#define CALL_MODEM_MSG_RELEASE                   0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: CALL_MODEM_MSG_DIRECTION                                */
/* ----------------------------------------------------------------------- */
typedef uint8 CALL_MODEM_MSG_DIRECTION_CONST;

/* Message is sent to network. */
#define CALL_MODEM_MSG_DIRECT_SENT               0x01
/* Message is received from network. */
#define CALL_MODEM_MSG_DIRECT_RECEIVED           0x02
/* Used for internal call release e.g. radio link failure. */
#define CALL_MODEM_MSG_DIRECT_INTERNAL           0x03

/* ----------------------------------------------------------------------- */
/* Message ID's                                                            */
/* ----------------------------------------------------------------------- */

#define CALL_MODEM_CREATE_REQ                    0x01
#define CALL_MODEM_CREATE_RESP                   0x02
#define CALL_MODEM_COMING_IND                    0x03
#define CALL_MODEM_MO_ALERT_IND                  0x04
#define CALL_MODEM_MT_ALERT_IND                  0x05
#define CALL_MODEM_WAITING_IND                   0x06
#define CALL_MODEM_ANSWER_REQ                    0x07
#define CALL_MODEM_ANSWER_RESP                   0x08
#define CALL_MODEM_RELEASE_REQ                   0x09
#define CALL_MODEM_RELEASE_RESP                  0x0A
#define CALL_MODEM_RELEASE_IND                   0x0B
#define CALL_MODEM_TERMINATED_IND                0x0C
#define CALL_MODEM_STATUS_REQ                    0x0D
#define CALL_MODEM_STATUS_RESP                   0x0E
#define CALL_MODEM_STATUS_IND                    0x0F
#define CALL_MODEM_PRESENT_IND                   0x10
#define CALL_MODEM_CONTROL_REQ                   0x11
#define CALL_MODEM_CONTROL_RESP                  0x12
#define CALL_MODEM_CONTROL_IND                   0x13
#define CALL_MODEM_DTMF_SEND_REQ                 0x17
#define CALL_MODEM_DTMF_SEND_RESP                0x18
#define CALL_MODEM_DTMF_STOP_REQ                 0x19
#define CALL_MODEM_DTMF_STOP_RESP                0x1A
#define CALL_MODEM_DTMF_STATUS_IND               0x1B
#define CALL_MODEM_DTMF_TONE_IND                 0x1C
#define CALL_MODEM_RECONNECT_IND                 0x1E
#define CALL_MODEM_PROPERTY_GET_REQ              0x1F
#define CALL_MODEM_PROPERTY_GET_RESP             0x20
#define CALL_MODEM_PROPERTY_SET_REQ              0x21
#define CALL_MODEM_PROPERTY_SET_RESP             0x22
#define CALL_MODEM_PROPERTY_SET_IND              0x23
#define CALL_MODEM_EMERG_NBR_MODIFY_REQ          0x24
#define CALL_MODEM_EMERG_NBR_MODIFY_RESP         0x25
#define CALL_MODEM_EMERG_NBR_GET_REQ             0x26
#define CALL_MODEM_EMERG_NBR_GET_RESP            0x27
#define CALL_MODEM_EMERG_NBR_CHECK_REQ           0x28
#define CALL_MODEM_EMERG_NBR_CHECK_RESP          0x29
#define CALL_MODEM_EMERG_NBR_IND                 0x31
#define CALL_MODEM_SERVICE_DENIED_IND            0x32
#define CALL_MODEM_USER_CONNECT_IND              0x33
#define CALL_MODEM_RELEASE_END_REQ               0x34
#define CALL_MODEM_RELEASE_END_RESP              0x35
#define CALL_MODEM_RESOURCE_IND                  0x40
#define CALL_MODEM_RESOURCE_REQ                  0x41
#define CALL_MODEM_RESOURCE_RESP                 0x42
#define CALL_MODEM_RESOURCE_CLEAR_IND            0x43
#define CALL_MODEM_RESOURCE_CONF_REQ             0x44
#define CALL_MODEM_RESOURCE_CONF_RESP            0x45
#define CALL_MODEM_RESOURCE_CONF_IND             0x46
#define CALL_MODEM_TERMINATE_REQ                 0x47
#define CALL_MODEM_TERMINATE_RESP                0x48
#define CALL_MODEM_NETWORK_CONN_IND              0x49
#define CALL_MODEM_MESSAGE_IND                   0x50
#define CALL_MODEM_NOTIFICATION_IND              0xA0
#define CALL_MODEM_BLACKLIST_CLEAR_REQ           0xA4
#define CALL_MODEM_BLACKLIST_CLEAR_RESP          0xA5
#define CALL_MODEM_BLACKLIST_TIMER_IND           0xA6
#define CALL_MODEM_BC_GET_REQ                    0xAA
#define CALL_MODEM_BC_GET_RESP                   0xAB
#define CALL_MODEM_BC_CHECK_REQ                  0xAC
#define CALL_MODEM_BC_CHECK_RESP                 0xAD
#define CALL_MODEM_SS_DATA_IND                   0xAF

/* ----------------------------------------------------------------------- */
/* Subblock ID's                                                           */
/* ----------------------------------------------------------------------- */

#define CALL_MODEM_SB_ORIGIN_ADDRESS             0x01
#define CALL_MODEM_SB_ORIGIN_SUBADDRESS          0x02
#define CALL_MODEM_SB_DESTINATION_ADDRESS        0x03
#define CALL_MODEM_SB_DESTINATION_SUBADDRESS     0x04
#define CALL_MODEM_SB_DESTINATION_PRE_ADDRESS    0x05
#define CALL_MODEM_SB_DESTINATION_POST_ADDRESS   0x06
#define CALL_MODEM_SB_CONNECTED_ADDRESS          0x24
#define CALL_MODEM_SB_CONNECTED_SUBADDRESS       0x25
#define CALL_MODEM_SB_MODE                       0x07
#define CALL_MODEM_SB_CAUSE                      0x08
#define CALL_MODEM_SB_OPERATION                  0x09
#define CALL_MODEM_SB_STATUS                     0x0A
#define CALL_MODEM_SB_STATUS_INFO                0x0B
#define CALL_MODEM_SB_ALERTING_INFO              0x0C
#define CALL_MODEM_SB_RELEASE_INFO               0x0D
#define CALL_MODEM_SB_ORIGIN_INFO                0x0E
#define CALL_MODEM_SB_DTMF_DIGIT                 0x0F
#define CALL_MODEM_SB_DTMF_STRING                0x10
#define CALL_MODEM_SB_DTMF_BCD_STRING            0x19
#define CALL_MODEM_SB_DTMF_INFO                  0x1A
#define CALL_MODEM_SB_PROPERTY_INFO              0x13
#define CALL_MODEM_SB_EMERG_NUMBER               0x14
#define CALL_MODEM_SB_DTMF_STATUS                0x11
#define CALL_MODEM_SB_DTMF_TONE                  0x12
#define CALL_MODEM_SB_CUG_INFO                   0xA0
#define CALL_MODEM_SB_ALERTING_PATTERN           0xA1
#define CALL_MODEM_SB_REDIRECTING_ADDRESS        0xA4
#define CALL_MODEM_SB_REDIRECTING_SUBADDRESS     0xA5
#define CALL_MODEM_SB_REMOTE_ADDRESS             0xA6
#define CALL_MODEM_SB_REMOTE_SUBADDRESS          0xA7
#define CALL_MODEM_SB_DIAGNOSTICS                0xA9
#define CALL_MODEM_SB_SS_DIAGNOSTICS             0xAA
#define CALL_MODEM_SB_NEW_DESTINATION            0xAB
#define CALL_MODEM_SB_NOTIFY                     0xB1
#define CALL_MODEM_SB_SS_NOTIFY                  0xB2
#define CALL_MODEM_SB_SS_CODE                    0xB3
#define CALL_MODEM_SB_SS_STATUS                  0xB4
#define CALL_MODEM_SB_SS_NOTIFY_INDICATOR        0xB5
#define CALL_MODEM_SB_SS_HOLD_INDICATOR          0xB6
#define CALL_MODEM_SB_SS_ECT_INDICATOR           0xB7
#define CALL_MODEM_SB_DESTINATION_CS_ADDRESS     0x16
#define CALL_MODEM_SB_BC                         0xBA
#define CALL_MODEM_SB_CAUSE_OF_NO_CLI            0xBC
#define CALL_MODEM_SB_MM_CAUSE                   0xBD
#define CALL_MODEM_SB_MSG_INFO                   0x49
#define CALL_MODEM_SB_DETAILED_CAUSE             0xBF
#define CALL_MODEM_SB_SS_DATA                    0xC0
#define CALL_MODEM_SB_ALS_INFO                   0xC1
#define CALL_MODEM_SB_STATE_AUTO_CHANGE          0x18
#define CALL_MODEM_SB_EMERG_NUMBER_INFO          0x1B
#define CALL_MODEM_SB_STATUS_MODE                0x1C
#define CALL_MODEM_SB_ADDR_AND_STATUS_INFO       0x1D
#define CALL_MODEM_SB_DTMF_TIMERS                0x1E
#define CALL_MODEM_SB_NW_CAUSE                   0x20
#define CALL_MODEM_SB_DESTINATION_ISI_ADDRESS    0x23
#define CALL_MODEM_SB_RESOURCE                   0x41
#define CALL_MODEM_SB_RESOURCE_CONF              0x42
#define CALL_MODEM_SB_RESOURCE_CONF_REQUIRED     0x43
#define CALL_MODEM_SB_RESOURCE_SEQ_ID            0x44
#define CALL_MODEM_SB_RESOURCE_STATUS            0x45
#define CALL_MODEM_SB_RESOURCE_CHECK_INFO        0x46
#define CALL_MODEM_SB_CHECK_INFO                 0x40
#define CALL_MODEM_SB_LINE_ID                    0x47
#define CALL_MODEM_SB_USER_TO_USER               0x48
#define CALL_MODEM_SB_ORIGIN_CS_ADDRESS          0x4A
#define CALL_MODEM_SB_REQ_INFO                   0x4B
#define CALL_MODEM_SB_EMERG_NUMBER_MOD_INFO      0x4C

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_ORIGIN_ADDRESS                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_ADDRESS_TYPE */
    uint8   addr_type;
    /* Values from the bitmask table CALL_MODEM_PRESENTATION_SCREEN_INDICATOR
    */
    uint8   presentation;
    uint8   unused;
    uint8   addr_len;     /* Number of Unicode characters */
    /* Possible values for address string characters are unicodes '0', '1',
       '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', 'a', 'b' and 'c'.
    */
    char16  addr;
    } CALL_MODEM_SB_ORIGIN_ADDR_STR;

#define SIZE_CALL_MODEM_SB_ORIGIN_ADDRESS_STR   (6*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SIZEOF_ORIGIN_ADDR_FIXED    0x06

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_ORIGIN_SUBADDRESS                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* See 'Calling Party Subaddress IE' in 3GPP TS 24.008 ch. 10.5.4.10.
       Byte contains octet 2 from 'Calling Party Subaddress IE'.
    */
    uint8   addr_len;
    /* See 'Calling Party Subaddress IE' in 3GPP TS 24.008 ch. 10.5.4.10.
       First byte contains octet 3 from 'Calling Party Subaddress IE'.
    */
    uint8   addr;
    } CALL_MODEM_SB_ORIGIN_SUBADDR_STR;

#define SIZE_CALL_MODEM_SB_ORIGIN_SUBADDRESS_STR   (4*sizeof(uint8))

#define CALL_MODEM_SB_SIZEOF_ORIGIN_SUBADDR_FIXED    0x03

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DESTINATION_ADDRESS                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_ADDRESS_TYPE */
    uint8   addr_type;
    uint8   unused1;
    uint8   unused2;
    uint8   addr_len;     /* Number of Unicode characters */
    /* Possible values for address string characters are unicodes '0', '1',
       '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', 'a', 'b' and 'c'. In
       case of CALL_MODEM_EMERG_NBR_CHECK_REQ characters that are in the
       string before valid emergency number are not validated i.e. they may
       be also other characters than defined above.
    */
    char16  addr;
    } CALL_MODEM_SB_DEST_ADDR_STR;

#define SIZE_CALL_MODEM_SB_DESTINATION_ADDRESS_STR   (6*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SB_SIZEOF_DEST_ADDR_FIXED    0x06

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DESTINATION_SUBADDRESS                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* See 'Called Party Subaddress IE' in 3GPP TS 24.008 ch. 10.5.4.8. Byte
       contains octet 2 from 'Called Party Subaddress IE'.
    */
    uint8   addr_len;
    /* See 'Called Party Subaddress IE' in 3GPP TS 24.008 ch. 10.5.4.8. First
       byte contains octet 3 from 'Called Party Subaddress IE'.
    */
    uint8   addr;
    } CALL_MODEM_SB_DEST_SUBADDR_STR;

#define SIZE_CALL_MODEM_SB_DESTINATION_SUBADDRESS_STR   (4*sizeof(uint8))

#define CALL_MODEM_SB_SIZEOF_DEST_SUBADDR_FIXED    0x03

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DESTINATION_PRE_ADDRESS                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   unused;
    uint8   addr_len;     /* Number of Unicode characters */
    /* Possible values for address string characters are unicodes '0', '1',
       '2', '3', '4', '5', '6', '7', '8', '9', '*' and '#'.
    */
    char16  addr;
    } CALL_MODEM_SB_DEST_PRE_ADDR_STR;

#define SIZE_CALL_MODEM_SB_DESTINATION_PRE_ADDRESS_STR   (4*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SB_SIZEOF_DEST_PRE_ADDR_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DESTINATION_POST_ADDRESS                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   unused;
    uint8   addr_len;     /* Number of Unicode characters */
    /* Possible values for address string characters are unicodes '0', '1',
       '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', '*', '#',
       'p' and 'w'.
    */
    char16  addr;
    } CALL_MODEM_SB_DEST_POST_ADDR_STR;

#define SIZE_CALL_MODEM_SB_DESTINATION_POST_ADDRESS_STR   (4*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SB_SIZEOF_DEST_POST_ADDR_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_CONNECTED_ADDRESS                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_ADDRESS_TYPE */
    uint8   addr_type;
    /* Values from the bitmask table CALL_MODEM_PRESENTATION_SCREEN_INDICATOR
    */
    uint8   presentation;
    uint8   unused;
    uint8   addr_len;     /* Number of Unicode characters */
    /* Possible values for address string characters are unicodes '0', '1',
       '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', 'a', 'b' and 'c'.
    */
    char16  addr;
    } CALL_MODEM_SB_CONN_ADDR_STR;

#define SIZE_CALL_MODEM_SB_CONNECTED_ADDRESS_STR   (6*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SB_SIZEOF_CONN_ADDR_FIXED    0x06

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_CONNECTED_SUBADDRESS                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* See 'Connected Subaddress IE' in 3GPP TS 24.008 ch. 10.5.4.14. Byte
       contains octet 2 from 'Connected Subaddress IE'.
    */
    uint8   addr_len;
    /* See 'Connected Subaddress IE' in 3GPP TS 24.008 ch. 10.5.4.14. First
       Byte contains octet 3 from 'Connected Subaddress IE'.
    */
    uint8   addr;
    } CALL_MODEM_SB_CONN_SUBADDR_STR;

#define SIZE_CALL_MODEM_SB_CONNECTED_SUBADDRESS_STR   (4*sizeof(uint8))

#define CALL_MODEM_SB_SIZEOF_CONN_SUBADDR_FIXED    0x03

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_MODE                                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   mode;        /* Values from the constant table CALL_MODEM_MODE */
    /* Values from the bitmask table CALL_MODEM_MODE_INFO */
    uint8   mode_info;
    } CALL_MODEM_SB_MODE_STR;

#define SIZE_CALL_MODEM_SB_MODE_STR   sizeof(CALL_MODEM_SB_MODE_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_CAUSE                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* xxxx----  Filler
       ----xxxx  Cause type
    */
    uint8   cause_type;
    uint8   cause;      /* Values from the constant table CALL_MODEM_CAUSE */
    } CALL_MODEM_SB_CAUSE_STR;

#define SIZE_CALL_MODEM_SB_CAUSE_STR   sizeof(CALL_MODEM_SB_CAUSE_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_OPERATION                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_OPERATION */
    uint8   operation;
    uint8   unused;
    } CALL_MODEM_SB_OPER_STR;

#define SIZE_CALL_MODEM_SB_OPERATION_STR   sizeof(CALL_MODEM_SB_OPER_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_STATUS                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   status;    /* Values from the constant table CALL_MODEM_STATUS */
    uint8   unused;
    } CALL_MODEM_SB_STATUS_STR;

#define SIZE_CALL_MODEM_SB_STATUS_STR   sizeof(CALL_MODEM_SB_STATUS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_STATUS_INFO                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   mode;        /* Values from the constant table CALL_MODEM_MODE */
    /* Values from the bitmask table CALL_MODEM_MODE_INFO */
    uint8   mode_info;
    uint8   status;    /* Values from the constant table CALL_MODEM_STATUS */
    uint8   unused1;
    uint8   unused2;
    } CALL_MODEM_SB_ST_INFO_STR;

#define SIZE_CALL_MODEM_SB_STATUS_INFO_STR   \
        sizeof(CALL_MODEM_SB_ST_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_ALERTING_INFO                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_ALERTING_INFO */
    uint8   alerting_info;
    uint8   unused;
    } CALL_MODEM_SB_ALERT_INFO_STR;

#define SIZE_CALL_MODEM_SB_ALERTING_INFO_STR   \
        sizeof(CALL_MODEM_SB_ALERT_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_RELEASE_INFO                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_RELEASE_INFO */
    uint8   release_info;
    uint8   unused;
    } CALL_MODEM_SB_REL_INFO_STR;

#define SIZE_CALL_MODEM_SB_RELEASE_INFO_STR   \
        sizeof(CALL_MODEM_SB_REL_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_ORIGIN_INFO                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_PRESENTATION_SCREEN_INDICATOR
    */
    uint8   presentation;
    uint8   unused1;
    uint8   unused2;
    uint8   unused3;
    /* Field links CALL_MODEM_ORIGIN_INFO and CALL_MODEM_ADDR_AND_STATUS_INFO
       sub blocks in CALL_MODEM_STATUS_RESP. Sub blocks that have same value
       for link id field contain information about same number.
    */
    uint8   link_id;
    uint8   name_len;     /* Number of Unicode characters. */
    char16  name;
    } CALL_MODEM_SB_ORIGIN_INFO_STR;

#define SIZE_CALL_MODEM_SB_ORIGIN_INFO_STR   (8*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SB_SIZEOF_ORIGIN_INFO_FIXED    0x08

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DTMF_DIGIT                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Possible value for DTMF digit are unicodes '0', '1', '2', '3', '4',
       '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', '*' and '#'. Note: 'p'
       and 'w' are not valid values.
    */
    char16  data;
    } CALL_MODEM_SB_DTMF_DIGIT_STR;

#define SIZE_CALL_MODEM_SB_DTMF_DIGIT_STR   \
        sizeof(CALL_MODEM_SB_DTMF_DIGIT_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DTMF_STRING                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_DTMF_PAUSE_VALUES */
    uint8   pause_length;
    uint8   data_len;     /* Number of DTMF digits. */
    /* Possible values for DTMF string characters are unicodes '0', '1', '2',
       '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', '*', '#', 'p'
       and 'w'.
    */
    char16  data;
    } CALL_MODEM_SB_DTMF_STRING_STR;

#define SIZE_CALL_MODEM_SB_DTMF_STRING_STR   (4*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SB_SIZEOF_DTMF_STRING_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DTMF_BCD_STRING                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_DTMF_PAUSE_VALUES */
    uint8   pause_length;
    uint8   unused;
    uint16  data_len;     /* Number of DTMF numbers */
    /* Possible values for DTMF string are numbers coded in BCD 0x00, 0x01,
       0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A (= '*'), 0x0B (=
       '#'), 0x0C (= pause) and 0x0F (= endmark). BCD value 0x0C is never
       sent across the radio interface.
    */
    uint8   data;
    } CALL_MODEM_SB_DTMF_BCD_STRING_STR;

#define SIZE_CALL_MODEM_SB_DTMF_BCD_STRING_STR   (5*sizeof(uint8) + \
        sizeof(uint16))

#define CALL_MODEM_SB_SIZEOF_DTMF_BCD_STRING_FIXED    0x06

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DTMF_INFO                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_DTMF_INFO_VALUES */
    uint8   dtmf_info;
    uint8   unused;
    } CALL_MODEM_SB_DTMF_INFO_STR;

#define SIZE_CALL_MODEM_SB_DTMF_INFO_STR   \
        sizeof(CALL_MODEM_SB_DTMF_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_PROPERTY_INFO                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* A subset of values from the constant table CALL_MODEM_PROPERTY */
    uint8   property;
    uint8   property_value;
    } CALL_MODEM_SB_PROP_INFO_STR;

#define SIZE_CALL_MODEM_SB_PROPERTY_INFO_STR   \
        sizeof(CALL_MODEM_SB_PROP_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_EMERG_NUMBER                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_EMERG_NBR_ORIGIN */
    uint8   origin;
    uint8   unused1;
    uint8   unused2;
    /* Field links CALL_MODEM_EMERG_NUMBER and CALL_MODEM_EMERG_NUMBER_INFO
       sub blocks. Sub blocks that have same value for link id field contain
       information about same number.
    */
    uint8   link_id;
    uint8   unused3;
    uint8   addr_len;     /* Number of Unicode characters. */
    /* Possible values for address string characters are unicodes '0', '1',
       '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', 'a', 'b' and 'c'.
    */
    char16  addr;
    } CALL_MODEM_SB_EMERG_NBR_STR;

#define SIZE_CALL_MODEM_SB_EMERG_NUMBER_STR   (8*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SB_SIZEOF_EMERG_NBR_FIXED    0x08

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DTMF_STATUS                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_DTMF_STATUS */
    uint8   status;
    uint8   unused;
    } CALL_MODEM_SB_DTMF_ST_STR;

#define SIZE_CALL_MODEM_SB_DTMF_STATUS_STR   \
        sizeof(CALL_MODEM_SB_DTMF_ST_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DTMF_TONE                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Possible values for DTMF tone are CALL_MODEM_DTMF_NO_TONE and unicodes
       '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D',
       '*', and '#'.
    */
    char16  tone;
    } CALL_MODEM_SB_DTMF_TONE_STR;

#define SIZE_CALL_MODEM_SB_DTMF_TONE_STR   \
        sizeof(CALL_MODEM_SB_DTMF_TONE_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_CUG_INFO                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_PREFERENTIAL_CUG */
    uint8   pref_cug;
    /* Values from the constant table CALL_MODEM_CUG_OUTGOING_ACCESS */
    uint8   cug_oa;
    uint16  cug_ind;
    uint8   unused;
    uint8   unused2;
    } CALL_MODEM_SB_CUG_INFO_STR;

#define SIZE_CALL_MODEM_SB_CUG_INFO_STR   sizeof(CALL_MODEM_SB_CUG_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_ALERTING_PATTERN                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_ALERTING_PATTERN */
    uint8   alerting_pattern;
    uint8   unused;
    } CALL_MODEM_SB_ALERT_PATT_STR;

#define SIZE_CALL_MODEM_SB_ALERTING_PATTERN_STR   \
        sizeof(CALL_MODEM_SB_ALERT_PATT_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_REDIRECTING_ADDRESS                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_ADDRESS_TYPE */
    uint8   addr_type;
    /* Values from the bitmask table CALL_MODEM_PRESENTATION_SCREEN_INDICATOR
    */
    uint8   presentation;
    uint8   unused;
    uint8   addr_len;     /* Number of Unicode characters. */
    /* Possible values for address string characters are unicodes '0', '1',
       '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', 'a', 'b' and 'c'.
    */
    char16  addr;
    } CALL_MODEM_SB_REDIR_ADDR_STR;

#define SIZE_CALL_MODEM_SB_REDIRECTING_ADDRESS_STR   (6*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SB_SIZEOF_REDIR_ADDR_FIXED    0x06

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_REDIRECTING_SUBADDRESS                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* See 'Redirecting Party Subaddress IE' in 3GPP TS 24.008 ch.
       10.5.4.21c. Byte contains octet 2 from 'Redirecting Party Subaddress
       IE'.
    */
    uint8   addr_len;
    /* See 'Redirecting Party Subaddress IE' in 3GPP TS 24.008 ch.
       10.5.4.21c. First byte contains octet 3 from 'Redirecting Party
       Subaddress IE'.
    */
    uint8   addr;
    } CALL_MODEM_SB_REDIR_SUBADDR_STR;

#define SIZE_CALL_MODEM_SB_REDIRECTING_SUBADDRESS_STR   (4*sizeof(uint8))

#define CALL_MODEM_SB_SIZEOF_REDIR_SUBADDR_FIXED    0x03

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_REMOTE_ADDRESS                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_ADDRESS_TYPE */
    uint8   addr_type;
    /* Values from the bitmask table CALL_MODEM_PRESENTATION_SCREEN_INDICATOR
    */
    uint8   presentation;
    uint8   unused;
    uint8   addr_len;     /* Number of Unicode characters. */
    /* Possible values for address string characters are unicodes '0', '1',
       '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', 'a', 'b' and 'c'.
    */
    char16  addr;
    } CALL_MODEM_SB_REMOTE_ADDR_STR;

#define SIZE_CALL_MODEM_SB_REMOTE_ADDRESS_STR   (6*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SB_SIZEOF_REMOTE_ADDR_FIXED    0x06

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_REMOTE_SUBADDRESS                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* See 'ISDN-SubaddressString' in 3GPP TS 29.002 ch. 17.7.8. Byte
       contains 'ISDN-SubaddressString' length.
    */
    uint8   addr_len;
    /* See 'ISDN-SubaddressString' in 3GPP TS 29.002 ch. 17.7.8. First byte
       contains 'type of subbaddress' octet from 'ISDN-SubaddressString'.
    */
    uint8   addr;
    } CALL_MODEM_SB_REMOTE_SUBADDR_STR;

#define SIZE_CALL_MODEM_SB_REMOTE_SUBADDRESS_STR   (4*sizeof(uint8))

#define CALL_MODEM_SB_SIZEOF_REMOTE_SUBADDR_FIXED    0x03

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DIAGNOSTICS                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_CONDITION */
    uint8   condition;
    uint8   unused;
    } CALL_MODEM_SB_DIAGN_STR;

#define SIZE_CALL_MODEM_SB_DIAGNOSTICS_STR   sizeof(CALL_MODEM_SB_DIAGN_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_SS_DIAGNOSTICS                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_SS_DIAGNOSTICS */
    uint8   diagnostics;
    uint8   unused;
    } CALL_MODEM_SB_SS_DIAGN_STR;

#define SIZE_CALL_MODEM_SB_SS_DIAGNOSTICS_STR   \
        sizeof(CALL_MODEM_SB_SS_DIAGN_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_NEW_DESTINATION - Valid from version 001.003    */
/* ----------------------------------------------------------------------- */
/* See 'Cause IE' in 3GPP TS 24.008 ch. 10.5.4.11. Field contains values from
   cause diagnostics octet 5 of 'Cause IE' onwards when octets are coded
   according to NOTE 5. Note is applicable for cause 22 and coding of the
   field is same as for 'Called Party BCD Number IE'.
*/

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_ADDRESS_TYPE */
    uint8   addr_type;
    uint8   unused1;
    uint8   unused2;
    uint8   addr_len;     /* Number of Unicode characters. */
    /* Possible values for address string characters are unicodes '0', '1',
       '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', 'a', 'b' and 'c'.
    */
    char16  addr;
    } CALL_MODEM_SB_NEW_DEST_STR;

#define SIZE_CALL_MODEM_SB_NEW_DESTINATION_STR   (6*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SB_SIZEOF_NEW_DEST_FIXED    0x06

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_NEW_DESTINATION - Obsolete from version 001.003 */
/* ----------------------------------------------------------------------- */

#if !MODEM_CALL_ISI_MIN_VERSION(1,3)

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_ADDRESS_TYPE */
    uint8   addr_type;
    /* Values from the bitmask table CALL_MODEM_PRESENTATION_SCREEN_INDICATOR
    */
    uint8   presentation;
    uint8   unused;
    uint8   addr_len;     /* Number of Unicode characters. */
    /* Possible values for address string characters are unicodes '0', '1',
       '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', 'a', 'b' and 'c'.
    */
    char16  addr;
    } CALL_MODEM_SB_NEW_DESTINATION_STR;

#define SIZE_CALL_MODEM_SB_NEW_DESTINATION_STR   (6*sizeof(uint8) + \
        sizeof(char16))

#endif /* !MODEM_CALL_ISI_MIN_VERSION(1,3) */


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_NOTIFY                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_NOTIFICATION_INDICATOR */
    uint8   notification;
    uint8   unused;
    } CALL_MODEM_SB_NOTIFY_STR;

#define SIZE_CALL_MODEM_SB_NOTIFY_STR   sizeof(CALL_MODEM_SB_NOTIFY_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_SS_NOTIFY                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_SS_NOTIFICATION */
    uint8   ss_notification;
    uint8   unused;
    } CALL_MODEM_SB_SS_NOTIFY_STR;

#define SIZE_CALL_MODEM_SB_SS_NOTIFY_STR   \
        sizeof(CALL_MODEM_SB_SS_NOTIFY_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_SS_CODE                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_MMI_SS_CODES */
    uint16  mmi_ss_code;
    } CALL_MODEM_SB_SS_CODE_STR;

#define SIZE_CALL_MODEM_SB_SS_CODE_STR   sizeof(CALL_MODEM_SB_SS_CODE_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_SS_STATUS                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_SS_STATUS */
    uint8   ss_status;
    uint8   unused;
    } CALL_MODEM_SB_SS_STATUS_STR;

#define SIZE_CALL_MODEM_SB_SS_STATUS_STR   \
        sizeof(CALL_MODEM_SB_SS_STATUS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_SS_NOTIFY_INDICATOR                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_SS_INDICATOR */
    uint8   ss_indicator;
    uint8   unused;
    } CALL_MODEM_SB_SS_NOTIFY_IND_STR;

#define SIZE_CALL_MODEM_SB_SS_NOTIFY_INDICATOR_STR   \
        sizeof(CALL_MODEM_SB_SS_NOTIFY_IND_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_SS_HOLD_INDICATOR                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_SS_HOLD_INDICATOR */
    uint8   ss_hold_indicator;
    uint8   unused;
    } CALL_MODEM_SB_SS_HOLD_IND_STR;

#define SIZE_CALL_MODEM_SB_SS_HOLD_INDICATOR_STR   \
        sizeof(CALL_MODEM_SB_SS_HOLD_IND_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_SS_ECT_INDICATOR                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_SS_ECT_INDICATOR */
    uint8   ss_ect_indicator;
    uint8   unused;
    } CALL_MODEM_SB_SS_ECT_IND_STR;

#define SIZE_CALL_MODEM_SB_SS_ECT_INDICATOR_STR   \
        sizeof(CALL_MODEM_SB_SS_ECT_IND_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DESTINATION_CS_ADDRESS                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   padding1;
    uint8   padding2;
    uint8   padding3;
    /* See 'Called Party BCD Number IE' in 3GPP TS 24.008 ch. 10.5.4.7. Byte
       contains octet 2 from 'Called Party BCD Number IE'.
    */
    uint8   addr_len;
    /* See 'Called Party BCD Number IE' in 3GPP TS 24.008 ch. 10.5.4.7. First
       byte contains octet 3 from 'Called Party BCD Number IE'.
    */
    uint8   addr;
    } CALL_MODEM_SB_DEST_CS_ADDR_STR;

#define SIZE_CALL_MODEM_SB_DESTINATION_CS_ADDRESS_STR   (7*sizeof(uint8))

#define CALL_MODEM_SB_SIZEOF_DEST_CS_ADDR_FIXED    0x06

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_BC                                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* See 'Bearer Capability IE' in 3GPP TS 24.008 ch. 10.5.4.5. Byte
       contains octet 2 from 'Bearer Capability IE'.
    */
    uint8   bc_length;
    /* See 'Bearer Capability IE' in 3GPP TS 24.008 ch. 10.5.4.5. First byte
       contains octet 3 from 'Bearer Capability IE'.
    */
    uint8   bc_data;
    } CALL_MODEM_SB_BC_STR;

#define SIZE_CALL_MODEM_SB_BC_STR   (4*sizeof(uint8))

#define CALL_MODEM_SB_SIZEOF_BC_FIXED    0x03

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_CAUSE_OF_NO_CLI                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_CAUSE_OF_NO_CLI_VALUES */
    uint8   cause;
    uint8   padding;
    } CALL_MODEM_SB_CAUSE_OF_NO_CLI_STR;

#define SIZE_CALL_MODEM_SB_CAUSE_OF_NO_CLI_STR   \
        sizeof(CALL_MODEM_SB_CAUSE_OF_NO_CLI_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_MM_CAUSE                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_MM_CAUSE_VALUES */
    uint8   cause;
    uint8   padding;
    } CALL_MODEM_SB_MM_CAUSE_STR;

#define SIZE_CALL_MODEM_SB_MM_CAUSE_STR   sizeof(CALL_MODEM_SB_MM_CAUSE_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_MSG_INFO                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   msg;          /* Values from the constant table CALL_MODEM_MSG */
    /* Values from the constant table CALL_MODEM_MSG_DIRECTION */
    uint8   msg_dir;
    /* Transaction identifier from the received or sent message. TI flag is
       coded to bit 8 and bits 5 to 7 are TI value. Bits 1 to 4 are set to
       zero. If internal call release has occurred field is coded as clearing
       would have been initiated by mobile i.e. similar to messages sent to
       network.
    */
    uint8   transaction_id;
    uint8   padding1;
    uint8   padding2;
    uint8   padding3;
    } CALL_MODEM_SB_MSG_INFO_STR;

#define SIZE_CALL_MODEM_SB_MSG_INFO_STR   sizeof(CALL_MODEM_SB_MSG_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DETAILED_CAUSE                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* See 'Cause IE' in 3GPP TS 24.008 ch. 10.5.4.11. Byte contains octet 2
       from 'Cause IE'.
    */
    uint8   cause_len;
    /* See 'Cause IE' in 3GPP TS 24.008 ch. 10.5.4.11. First byte contains
       octet 3 from 'Cause IE'.
    */
    uint8   cause;
    } CALL_MODEM_SB_DETAIL_CAUSE_STR;

#define SIZE_CALL_MODEM_SB_DETAILED_CAUSE_STR   (4*sizeof(uint8))

#define CALL_MODEM_SB_SIZEOF_DETAIL_CAUSE_FIXED    0x03

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_SS_DATA                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* See 'Facility IE' in 3GPP TS 24.008 ch. 10.5.4.15. Byte contains octet
       2 from 'Facility IE'.
    */
    uint8   ss_data_len;
    /* See 'Facility IE' in 3GPP TS 24.008 ch. 10.5.4.15. First byte contains
       octet 3 from 'Facility IE'.
    */
    uint8   ss_data;
    } CALL_MODEM_SB_SS_DATA_STR;

#define SIZE_CALL_MODEM_SB_SS_DATA_STR   (4*sizeof(uint8))

#define CALL_MODEM_SB_SIZEOF_SS_DATA_FIXED    0x03

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_ALS_INFO                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_ALS_STATUS */
    uint8   als_sim_status;
    /* Values from the constant table CALL_MODEM_ALS_STATUS */
    uint8   als_pp_status;
    } CALL_MODEM_SB_ALS_INFO_STR;

#define SIZE_CALL_MODEM_SB_ALS_INFO_STR   sizeof(CALL_MODEM_SB_ALS_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_STATE_AUTO_CHANGE                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_AUTO_ST_CHANGE */
    uint8   state_auto_change;
    uint8   unused;
    } CALL_MODEM_SB_ST_AUTO_CH_STR;

#define SIZE_CALL_MODEM_SB_STATE_AUTO_CHANGE_STR   \
        sizeof(CALL_MODEM_SB_ST_AUTO_CH_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_EMERG_NUMBER_INFO                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Field links CALL_MODEM_EMERG_NUMBER and CALL_MODEM_EMERG_NUMBER_INFO
       sub blocks. Sub blocks that have same value for link id field contain
       information about same number.
    */
    uint8   link_id;
    /* Values from the bitmask table CALL_MODEM_EMERG_SERVICE_CATEGORY */
    uint8   serv_category;
    uint8   unused;
    uint8   alpha_id_len; /* Number of Unicode characters */
    char16  alpha_id;
    } CALL_MODEM_SB_EMERG_NBR_INFO_STR;

#define SIZE_CALL_MODEM_SB_EMERG_NUMBER_INFO_STR   (6*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SB_SIZEOF_EMERG_NBR_INFO_FIXED    0x06

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_STATUS_MODE                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   mode;  /* Values from the constant table CALL_MODEM_STATUS_MOD */
    uint8   unused;
    } CALL_MODEM_SB_CALL_ST_MODE_STR;

#define SIZE_CALL_MODEM_SB_STATUS_MODE_STR   \
        sizeof(CALL_MODEM_SB_CALL_ST_MODE_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_ADDR_AND_STATUS_INFO                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   mode;        /* Values from the constant table CALL_MODEM_MODE */
    /* Values from the bitmask table CALL_MODEM_MODE_INFO */
    uint8   mode_info;
    uint8   status;    /* Values from the constant table CALL_MODEM_STATUS */
    uint8   unused1;
    /* Field links CALL_MODEM_ORIGIN_INFO and CALL_MODEM_ADDR_AND_STATUS_INFO
       sub blocks in CALL_MODEM_STATUS_RESP. Sub blocks that have same value
       for link id field contain information about same number.
    */
    uint8   link_id;
    /* Values from the bitmask table CALL_MODEM_ADDRESS_TYPE */
    uint8   addr_type;
    /* Values from the bitmask table CALL_MODEM_PRESENTATION_SCREEN_INDICATOR
    */
    uint8   presentation;
    uint8   unused2;
    uint8   addr_len;     /* Number of Unicode characters */
    /* Possible values for address string characters are unicodes '0', '1',
       '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', 'a', 'b' and 'c'.
    */
    char16  addr;
    } CALL_MODEM_SB_ADDR_AND_ST_INFO_STR;

#define SIZE_CALL_MODEM_SB_ADDR_AND_STATUS_INFO_STR   (12*sizeof(uint8) + \
        sizeof(char16))

#define CALL_MODEM_SB_SIZEOF_ADDR_AND_ST_INFO_FIXED    0x0C

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DTMF_TIMERS                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint16  dtmf_dur;
    uint16  dtmf_gap;
    uint8   unused;
    uint8   unused2;
    } CALL_MODEM_SB_DTMF_TIMERS_STR;

#define SIZE_CALL_MODEM_SB_DTMF_TIMERS_STR   \
        sizeof(CALL_MODEM_SB_DTMF_TIMERS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_NW_CAUSE                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   unused;
    uint8   cause;   /* Values from the constant table CALL_MODEM_NW_CAUSE */
    } CALL_MODEM_SB_NW_CAUSE_STR;

#define SIZE_CALL_MODEM_SB_NW_CAUSE_STR   sizeof(CALL_MODEM_SB_NW_CAUSE_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_DESTINATION_ISI_ADDRESS                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_ADDRESS_TYPE */
    uint8   addr_type;
    uint8   unused1;
    uint8   unused2;
    uint8   addr_len;     /* Number of Unicode characters */
    /* Possible values for address string characters are unicodes '0', '1',
       '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', 'a', 'b' and 'c'.
    */
    char16  addr;
    } CALL_MODEM_SB_DEST_ISI_ADDR_STR;

#define SIZE_CALL_MODEM_SB_DESTINATION_ISI_ADDRESS_STR   (6*sizeof(uint8) + \
        sizeof(char16))


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_RESOURCE                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint16  res;  /* Values from the bitmask table CALL_MODEM_RESOURCE_IDS */
    } CALL_MODEM_SB_RES_STR;

#define SIZE_CALL_MODEM_SB_RESOURCE_STR   sizeof(CALL_MODEM_SB_RES_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_RESOURCE_CONF                                   */
/* ----------------------------------------------------------------------- */
/* Resource mask and operation resources mask fiels are  used to set what
   resources and operation resources are configured in  requests that are
   sent to Call Server. Call Server does not change  the status of the
   resources which mask is set to zero.
*/

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint16  res;  /* Values from the bitmask table CALL_MODEM_RESOURCE_IDS */
    /* Values from the bitmask table CALL_MODEM_RESOURCE_IDS_MASK */
    uint16  res_mask;
    uint8   padding1;
    uint8   padding2;
    } CALL_MODEM_SB_RES_CONF_STR;

#define SIZE_CALL_MODEM_SB_RESOURCE_CONF_STR   \
        sizeof(CALL_MODEM_SB_RES_CONF_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_RESOURCE_CONF_REQUIRED                          */
/* ----------------------------------------------------------------------- */
/* Resource configuration required field indicates for what resources the
   resource configuration is mandatory before resources are allowed. These
   settings are read from product profile. 
*/

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_RESOURCE_IDS_CONF_REQ */
    uint16  res_pp;
    } CALL_MODEM_SB_RES_CONF_REQ_STR;

#define SIZE_CALL_MODEM_SB_RESOURCE_CONF_REQUIRED_STR   \
        sizeof(CALL_MODEM_SB_RES_CONF_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_RESOURCE_SEQ_ID                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   sequence_id;
    uint8   padding;
    } CALL_MODEM_SB_RES_SEQ_ID_STR;

#define SIZE_CALL_MODEM_SB_RESOURCE_SEQ_ID_STR   \
        sizeof(CALL_MODEM_SB_RES_SEQ_ID_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_RESOURCE_STATUS                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_RESOURCE_STATUS */
    uint8   res_status;
    uint8   padding;
    } CALL_MODEM_SB_RES_STATUS_STR;

#define SIZE_CALL_MODEM_SB_RESOURCE_STATUS_STR   \
        sizeof(CALL_MODEM_SB_RES_STATUS_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_RESOURCE_CHECK_INFO                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* A subset of values from the bitmask table CALL_MODEM_RESOURCE_IDS */
    uint16  res;
    } CALL_MODEM_SB_RES_CHECK_INFO_STR;

#define SIZE_CALL_MODEM_SB_RESOURCE_CHECK_INFO_STR   \
        sizeof(CALL_MODEM_SB_RES_CHECK_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_CHECK_INFO                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the bitmask table CALL_MODEM_CHECK_INFO */
    uint8   check_info;
    uint8   padding;
    } CALL_MODEM_SB_CHECK_INFO_STR;

#define SIZE_CALL_MODEM_SB_CHECK_INFO_STR   \
        sizeof(CALL_MODEM_SB_CHECK_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_LINE_ID                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   line_id;  /* Values from the constant table CALL_MODEM_LINE_ID */
    uint8   padding;
    } CALL_MODEM_SB_LINE_ID_STR;

#define SIZE_CALL_MODEM_SB_LINE_ID_STR   sizeof(CALL_MODEM_SB_LINE_ID_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_USER_TO_USER                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table CALL_MODEM_UUS_TYPE */
    uint8   uus_type;
    /* Values from the constant table CALL_MODEM_UUS_ACTIVATION_TYPE */
    uint8   uus_act_type;
    /* See 'User-to-User IE' in 3GPP TS 24.008 ch. 10.5.4.25. Byte contains
       octet 2 from 'User-to-User IE'.
    */
    uint8   utou_len;
    /* See 'User-to-User IE' in 3GPP TS 24.008 ch. 10.5.4.25. First byte
       contains octet 3 from 'User-to-User IE'.
    */
    uint8   utou;
    } CALL_MODEM_SB_USER_TO_USER_STR;

#define SIZE_CALL_MODEM_SB_USER_TO_USER_STR   (6*sizeof(uint8))

#define CALL_MODEM_SIZEOF_USER_TO_USER_FIXED    0x05

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_ORIGIN_CS_ADDRESS                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* See 'Calling Party BCD Number IE' in 3GPP TS 24.008 ch. 10.5.4.9. Byte
       contains octet 2 from 'Calling Party BCD Number IE'.
    */
    uint8   addr_len;
    /* See 'Calling Party BCD Number IE' in 3GPP TS 24.008 ch. 10.5.4.9.
       First byte contains octet 3 from 'Calling Party BCD Number IE'.
    */
    uint8   addr;
    } CALL_MODEM_SB_ORIGIN_CS_ADDR_STR;

#define SIZE_CALL_MODEM_SB_ORIGIN_CS_ADDRESS_STR   (4*sizeof(uint8))

#define CALL_MODEM_SB_SIZEOF_ORIGIN_CS_ADDR_FIXED    0x03

/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_REQ_INFO                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   tr_id;        /* Transaction Identifier from the request. */
    uint8   padding;
    } CALL_MODEM_SB_REQ_INFO_STR;

#define SIZE_CALL_MODEM_SB_REQ_INFO_STR   sizeof(CALL_MODEM_SB_REQ_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: CALL_MODEM_SB_EMERG_NUMBER_MOD_INFO - Valid from version 002.003 */
/* ----------------------------------------------------------------------- */
/* Emergency number is valid in the country defined by the Mobile Country
   Code. MCC can be also coded empty by setting all digits to CALL_MODEM_NULL
   (0x00). In that case emergency number is valid regardless of the MCC. For
   MCCs that have less than three digits ASCII zeros are filled before the
   number e.g. for MCC 10 the programmed number would be 010 in ASCII.
   
   Mobile Country Code range can be used in case one country has several
   MCCs. In that case MCC is used as a base value and range defines how many
   country codes that are in the sequence belong to same country. Range can
   be also set to default by setting value to CALL_MODEM_NULL (0x00). E.g.
   for United Kingdom valid MCCs are 234 and 235. In that case MCC would be
   coded as 234 and range would be 2 meaning that there is two numbers in
   sequence.
*/

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Field links CALL_MODEM_EMERG_NUMBER and
       CALL_MODEM_SB_EMERG_NUMBER_MOD_INFO sub blocks in
       CALL_MODEM_EMERG_NBR_MODIFY_REQ. Sub blocks that have same value for
       link id field contain information about same number.
    */
    uint8   link_id;
    /* Values from the bitmask table CALL_MODEM_EMERG_SERVICE_CATEGORY */
    uint8   serv_category;
    uint8   mcc_digit_1;
    uint8   mcc_digit_2;
    uint8   mcc_digit_3;
    /* NULL value means default range i.e. MCC consists of one value. Other
       values define how many MCCs belong to range.
    */
    uint8   mcc_range;
    } CALL_MODEM_SB_EMERG_NBR_MOD_INFO_STR;

#define SIZE_CALL_MODEM_SB_EMERG_NUMBER_MOD_INFO_STR   \
        sizeof(CALL_MODEM_SB_EMERG_NBR_MOD_INFO_STR)


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_CREATE_REQ                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    CALL_MODEM_SB_MODE_STR mode;
    /* Subblock list:
       CALL_MODEM_SB_BC
       CALL_MODEM_SB_CHECK_INFO
       CALL_MODEM_SB_DESTINATION_ADDRESS
       CALL_MODEM_SB_DESTINATION_CS_ADDRESS
       CALL_MODEM_SB_DESTINATION_ISI_ADDRESS
       CALL_MODEM_SB_DESTINATION_POST_ADDRESS
       CALL_MODEM_SB_DESTINATION_PRE_ADDRESS
       CALL_MODEM_SB_DESTINATION_SUBADDRESS
       CALL_MODEM_SB_EMERG_NUMBER_INFO
       CALL_MODEM_SB_LINE_ID
       CALL_MODEM_SB_ORIGIN_SUBADDRESS
       CALL_MODEM_SB_RESOURCE_CHECK_INFO
       CALL_MODEM_SB_USER_TO_USER
    */
    } CALL_MODEM_CREATE_REQ_STR;

#define SIZE_CALL_MODEM_CREATE_REQ_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_MODE_STR))

#define CALL_MODEM_SIZEOF_CREATE_REQ_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_CREATE_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
    */
    } CALL_MODEM_CREATE_RESP_STR;

#define SIZE_CALL_MODEM_CREATE_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_COMING_IND                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    CALL_MODEM_SB_MODE_STR mode;
    /* Subblock list:
       CALL_MODEM_SB_ALERTING_PATTERN
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_CAUSE_OF_NO_CLI
       CALL_MODEM_SB_DESTINATION_ADDRESS
       CALL_MODEM_SB_DESTINATION_SUBADDRESS
       CALL_MODEM_SB_ORIGIN_ADDRESS
       CALL_MODEM_SB_ORIGIN_INFO
       CALL_MODEM_SB_ORIGIN_SUBADDRESS
       CALL_MODEM_SB_REDIRECTING_ADDRESS
       CALL_MODEM_SB_REDIRECTING_SUBADDRESS
       CALL_MODEM_SB_USER_TO_USER
    */
    } CALL_MODEM_COMING_IND_STR;

#define SIZE_CALL_MODEM_COMING_IND_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_MODE_STR))

#define CALL_MODEM_SIZEOF_COMING_IND_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_MO_ALERT_IND                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_ALERTING_INFO
    */
    } CALL_MODEM_MO_ALERT_IND_STR;

#define SIZE_CALL_MODEM_MO_ALERT_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_MT_ALERT_IND                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_ALERTING_PATTERN
    */
    } CALL_MODEM_MT_ALERT_IND_STR;

#define SIZE_CALL_MODEM_MT_ALERT_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_WAITING_IND                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_ALERTING_PATTERN
    */
    } CALL_MODEM_WAITING_IND_STR;

#define SIZE_CALL_MODEM_WAITING_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_ANSWER_REQ                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_DESTINATION_SUBADDRESS
    */
    } CALL_MODEM_ANSWER_REQ_STR;

#define SIZE_CALL_MODEM_ANSWER_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_ANSWER_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
    */
    } CALL_MODEM_ANSWER_RESP_STR;

#define SIZE_CALL_MODEM_ANSWER_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RELEASE_REQ                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    CALL_MODEM_SB_CAUSE_STR cause;
    /* Subblock list:
       CALL_MODEM_SB_STATE_AUTO_CHANGE
    */
    } CALL_MODEM_RELEASE_REQ_STR;

#define SIZE_CALL_MODEM_RELEASE_REQ_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_CAUSE_STR))

#define CALL_MODEM_SIZEOF_RELEASE_REQ_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RELEASE_RESP                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
    */
    } CALL_MODEM_RELEASE_RESP_STR;

#define SIZE_CALL_MODEM_RELEASE_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RELEASE_IND                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    CALL_MODEM_SB_CAUSE_STR cause;
    /* Subblock list:
       CALL_MODEM_SB_DIAGNOSTICS
       CALL_MODEM_SB_NEW_DESTINATION
       CALL_MODEM_SB_RELEASE_INFO
       CALL_MODEM_SB_SS_DIAGNOSTICS
    */
    } CALL_MODEM_RELEASE_IND_STR;

#define SIZE_CALL_MODEM_RELEASE_IND_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_CAUSE_STR))

#define CALL_MODEM_SIZEOF_RELEASE_IND_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_TERMINATED_IND                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    CALL_MODEM_SB_CAUSE_STR cause;
    CALL_MODEM_SB_MODE_STR mode;
    /* Subblock list:
       CALL_MODEM_SB_DIAGNOSTICS
       CALL_MODEM_SB_MM_CAUSE
       CALL_MODEM_SB_NEW_DESTINATION
       CALL_MODEM_SB_NW_CAUSE
       CALL_MODEM_SB_SS_DIAGNOSTICS
    */
    } CALL_MODEM_TERMINATED_IND_STR;

#define SIZE_CALL_MODEM_TERMINATED_IND_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_CAUSE_STR) + sizeof(CALL_MODEM_SB_MODE_STR))

#define CALL_MODEM_SIZEOF_TERMINATED_IND_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_STATUS_REQ                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_STATUS_MODE
    */
    } CALL_MODEM_STATUS_REQ_STR;

#define SIZE_CALL_MODEM_STATUS_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_STATUS_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;
    /* Number of sub blocks depends on number of calls and call status mode.
       See i_call_modem_f.doc
    */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_ADDR_AND_STATUS_INFO
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_ORIGIN_INFO
       CALL_MODEM_SB_STATUS_INFO
    */
    } CALL_MODEM_STATUS_RESP_STR;

#define SIZE_CALL_MODEM_STATUS_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_STATUS_IND                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    CALL_MODEM_SB_STATUS_STR status;
    CALL_MODEM_SB_MODE_STR mode;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_CHECK_INFO
       CALL_MODEM_SB_CONNECTED_ADDRESS
       CALL_MODEM_SB_CONNECTED_SUBADDRESS
       CALL_MODEM_SB_DESTINATION_ADDRESS
       CALL_MODEM_SB_DESTINATION_POST_ADDRESS
       CALL_MODEM_SB_DESTINATION_PRE_ADDRESS
       CALL_MODEM_SB_DESTINATION_SUBADDRESS
       CALL_MODEM_SB_DETAILED_CAUSE
       CALL_MODEM_SB_EMERG_NUMBER_INFO
       CALL_MODEM_SB_LINE_ID
       CALL_MODEM_SB_NW_CAUSE
       CALL_MODEM_SB_ORIGIN_ADDRESS
       CALL_MODEM_SB_ORIGIN_INFO
       CALL_MODEM_SB_ORIGIN_SUBADDRESS
       CALL_MODEM_SB_REDIRECTING_ADDRESS
       CALL_MODEM_SB_REDIRECTING_SUBADDRESS
       CALL_MODEM_SB_USER_TO_USER
    */
    } CALL_MODEM_STATUS_IND_STR;

#define SIZE_CALL_MODEM_STATUS_IND_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_STATUS_STR) + sizeof(CALL_MODEM_SB_MODE_STR))

#define CALL_MODEM_SIZEOF_STATUS_IND_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_PRESENT_IND                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the bitmask table CALL_MODEM_PRESENT_INFO */
    uint8   call_present;
    uint8   sub_blocks;   /* For future expansion */
    /* Subblock list: */
    } CALL_MODEM_PRESENT_IND_STR;

#define SIZE_CALL_MODEM_PRESENT_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_CONTROL_REQ                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    CALL_MODEM_SB_OPER_STR operation;
    /* Subblock list: */
    } CALL_MODEM_CONTROL_REQ_STR;

#define SIZE_CALL_MODEM_CONTROL_REQ_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_OPER_STR))

#define CALL_MODEM_SIZEOF_CONTROL_REQ_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_CONTROL_RESP                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    CALL_MODEM_SB_OPER_STR operation;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
    */
    } CALL_MODEM_CONTROL_RESP_STR;

#define SIZE_CALL_MODEM_CONTROL_RESP_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_OPER_STR))

#define CALL_MODEM_SIZEOF_CONTROL_RESP_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_CONTROL_IND                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    CALL_MODEM_SB_OPER_STR operation;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_DIAGNOSTICS
       CALL_MODEM_SB_SS_DIAGNOSTICS
    */
    } CALL_MODEM_CONTROL_IND_STR;

#define SIZE_CALL_MODEM_CONTROL_IND_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_OPER_STR))

#define CALL_MODEM_SIZEOF_CONTROL_IND_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_DTMF_SEND_REQ                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_DTMF_BCD_STRING
       CALL_MODEM_SB_DTMF_DIGIT
       CALL_MODEM_SB_DTMF_INFO
       CALL_MODEM_SB_DTMF_STRING
       CALL_MODEM_SB_DTMF_TIMERS
    */
    } CALL_MODEM_DTMF_SEND_REQ_STR;

#define SIZE_CALL_MODEM_DTMF_SEND_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_DTMF_SEND_RESP                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
    */
    } CALL_MODEM_DTMF_SEND_RESP_STR;

#define SIZE_CALL_MODEM_DTMF_SEND_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_DTMF_STOP_REQ                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;   /* For future expansion */
    /* Subblock list: */
    } CALL_MODEM_DTMF_STOP_REQ_STR;

#define SIZE_CALL_MODEM_DTMF_STOP_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_DTMF_STOP_RESP                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_DTMF_BCD_STRING
       CALL_MODEM_SB_DTMF_STRING
    */
    } CALL_MODEM_DTMF_STOP_RESP_STR;

#define SIZE_CALL_MODEM_DTMF_STOP_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_DTMF_STATUS_IND                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    CALL_MODEM_SB_DTMF_ST_STR status;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_DIAGNOSTICS
       CALL_MODEM_SB_DTMF_BCD_STRING
       CALL_MODEM_SB_DTMF_INFO
       CALL_MODEM_SB_DTMF_STRING
    */
    } CALL_MODEM_DTMF_STATUS_IND_STR;

#define SIZE_CALL_MODEM_DTMF_STATUS_IND_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_DTMF_ST_STR))

#define CALL_MODEM_SIZEOF_DTMF_STATUS_IND_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_DTMF_TONE_IND                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    CALL_MODEM_SB_DTMF_TONE_STR tone;
    /* Subblock list: */
    } CALL_MODEM_DTMF_TONE_IND_STR;

#define SIZE_CALL_MODEM_DTMF_TONE_IND_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_DTMF_TONE_STR))

#define CALL_MODEM_SIZEOF_DTMF_TONE_IND_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RECONNECT_IND                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the constant table CALL_MODEM_RECONNECT_STATUS */
    uint8   reconnect_status;
    uint8   sub_blocks;   /* For future expansion */
    /* Subblock list: */
    } CALL_MODEM_RECONNECT_IND_STR;

#define SIZE_CALL_MODEM_RECONNECT_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_PROPERTY_GET_REQ                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the constant table CALL_MODEM_PROPERTY */
    uint8   property;
    uint8   sub_blocks;   /* For future expansion */
    /* Subblock list: */
    } CALL_MODEM_PROPERTY_GET_REQ_STR;

#define SIZE_CALL_MODEM_PROPERTY_GET_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_PROPERTY_GET_RESP                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the constant table CALL_MODEM_PROPERTY */
    uint8   property;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_ALS_INFO
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_CUG_INFO
       CALL_MODEM_SB_PROPERTY_INFO
    */
    } CALL_MODEM_PROPERTY_GET_RESP_STR;

#define SIZE_CALL_MODEM_PROPERTY_GET_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_PROPERTY_SET_REQ                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   unused;
    uint8   sub_blocks;
    CALL_MODEM_SB_PROP_INFO_STR property_info;
    /* Subblock list:
       CALL_MODEM_SB_CUG_INFO
    */
    } CALL_MODEM_PROPERTY_SET_REQ_STR;

#define SIZE_CALL_MODEM_PROPERTY_SET_REQ_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_PROP_INFO_STR))

#define CALL_MODEM_SIZEOF_PROPERTY_SET_REQ_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_PROPERTY_SET_RESP                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   unused;
    uint8   sub_blocks;
    CALL_MODEM_SB_PROP_INFO_STR property_info;
    /* Subblock list:
       CALL_MODEM_SB_ALS_INFO
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_CUG_INFO
    */
    } CALL_MODEM_PROPERTY_SET_RESP_STR;

#define SIZE_CALL_MODEM_PROPERTY_SET_RESP_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_PROP_INFO_STR))

#define CALL_MODEM_SIZEOF_PROPERTY_SET_RESP_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_PROPERTY_SET_IND                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the constant table CALL_MODEM_PROPERTY */
    uint8   property;
    uint8   sub_blocks;
    CALL_MODEM_SB_PROP_INFO_STR property_info;
    /* Subblock list:
       CALL_MODEM_SB_ALS_INFO
       CALL_MODEM_SB_CUG_INFO
    */
    } CALL_MODEM_PROPERTY_SET_IND_STR;

#define SIZE_CALL_MODEM_PROPERTY_SET_IND_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_PROP_INFO_STR))

#define CALL_MODEM_SIZEOF_PROPERTY_SET_IND_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_EMERG_NBR_CHECK_REQ                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   unused;
    uint8   sub_blocks;
    CALL_MODEM_SB_DEST_ADDR_STR number;
    /* Subblock list: */
    } CALL_MODEM_EMERG_NBR_CHECK_REQ_STR;

#define SIZE_CALL_MODEM_EMERG_NBR_CHECK_REQ_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_DEST_ADDR_STR))

#define CALL_MODEM_SIZEOF_EMERG_NBR_CHECK_REQ_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_EMERG_NBR_CHECK_RESP                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the constant table CALL_MODEM_EMERG_NUMBER_CHECK_STATUS */
    uint8   status;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_EMERG_NUMBER
       CALL_MODEM_SB_EMERG_NUMBER_INFO
    */
    } CALL_MODEM_EMERG_NBR_CHECK_RESP_STR;

#define SIZE_CALL_MODEM_EMERG_NBR_CHECK_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_EMERG_NBR_GET_REQ                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   unused;
    uint8   sub_blocks;   /* For future expansion */
    /* Subblock list: */
    } CALL_MODEM_EMERG_NBR_GET_REQ_STR;

#define SIZE_CALL_MODEM_EMERG_NBR_GET_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_EMERG_NBR_GET_RESP                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   unused;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_EMERG_NUMBER
       CALL_MODEM_SB_EMERG_NUMBER_INFO
    */
    } CALL_MODEM_EMERG_NBR_GET_RESP_STR;

#define SIZE_CALL_MODEM_EMERG_NBR_GET_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_EMERG_NBR_MODIFY_REQ                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the constant table CALL_MODEM_EMERG_NUMBER_OPERATION */
    uint8   operation;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_EMERG_NUMBER
       CALL_MODEM_SB_EMERG_NUMBER_MOD_INFO
    */
    } CALL_MODEM_EMERG_NBR_MODIFY_REQ_STR;

#define SIZE_CALL_MODEM_EMERG_NBR_MODIFY_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_EMERG_NBR_MODIFY_RESP                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the constant table CALL_MODEM_EMERG_NUMBER_OPERATION */
    uint8   operation;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
    */
    } CALL_MODEM_EMERG_NBR_MODIFY_RESP_STR;

#define SIZE_CALL_MODEM_EMERG_NBR_MODIFY_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_NOTIFICATION_IND                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_ALERTING_INFO
       CALL_MODEM_SB_ALERTING_PATTERN
       CALL_MODEM_SB_CUG_INFO
       CALL_MODEM_SB_NOTIFY
       CALL_MODEM_SB_ORIGIN_INFO
       CALL_MODEM_SB_REMOTE_ADDRESS
       CALL_MODEM_SB_REMOTE_SUBADDRESS
       CALL_MODEM_SB_SS_CODE
       CALL_MODEM_SB_SS_ECT_INDICATOR
       CALL_MODEM_SB_SS_HOLD_INDICATOR
       CALL_MODEM_SB_SS_NOTIFY
       CALL_MODEM_SB_SS_NOTIFY_INDICATOR
       CALL_MODEM_SB_SS_STATUS
    */
    } CALL_MODEM_NOTIFICATION_IND_STR;

#define SIZE_CALL_MODEM_NOTIFICATION_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_BLACKLIST_CLEAR_REQ - Valid from version 001.003    */
/* ----------------------------------------------------------------------- */

#if MODEM_CALL_ISI_MIN_VERSION(1,3)

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   unused;
    uint8   sub_blocks;   /* For future expansion */
    /* Subblock list: */
    } CALL_MODEM_BLACKLIST_CLEAR_REQ_STR;

#define SIZE_CALL_MODEM_BLACKLIST_CLEAR_REQ_STR   (4*sizeof(uint8))

#endif /* MODEM_CALL_ISI_MIN_VERSION(1,3) */


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_BLACKLIST_CLEAR_REQ - Obsolete from version 001.003 */
/* ----------------------------------------------------------------------- */

#if !MODEM_CALL_ISI_MIN_VERSION(1,3)

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;
    uint8   sub_blocks;   /* For future expansion */
    /* Subblock list: */
    } CALL_MODEM_BLACKLIST_CLEAR_REQ_STR;

#define SIZE_CALL_MODEM_BLACKLIST_CLEAR_REQ_STR   (4*sizeof(uint8))

#endif /* !MODEM_CALL_ISI_MIN_VERSION(1,3) */


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_BLACKLIST_CLEAR_RESP                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   unused;
    uint8   sub_blocks;   /* For future expansion */
    /* Subblock list: */
    } CALL_MODEM_BLACKLIST_CLEAR_RESP_STR;

#define SIZE_CALL_MODEM_BLACKLIST_CLEAR_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_BLACKLIST_TIMER_IND                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the constant table CALL_MODEM_BLACKLIST_DURATION */
    uint8   duration;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_DESTINATION_ADDRESS
    */
    } CALL_MODEM_BLACKLIST_TIMER_IND_STR;

#define SIZE_CALL_MODEM_BLACKLIST_TIMER_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_BC_GET_REQ                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   padding;
    uint8   sub_blocks;
    CALL_MODEM_SB_MODE_STR mode;
    /* Subblock list: */
    } CALL_MODEM_BC_GET_REQ_STR;

#define SIZE_CALL_MODEM_BC_GET_REQ_STR   (4*sizeof(uint8) + \
        sizeof(CALL_MODEM_SB_MODE_STR))

#define CALL_MODEM_SIZEOF_BC_GET_REQ_FIXED    0x04

/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_BC_GET_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   padding;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_BC
       CALL_MODEM_SB_CAUSE
    */
    } CALL_MODEM_BC_GET_RESP_STR;

#define SIZE_CALL_MODEM_BC_GET_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_BC_CHECK_REQ                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   padding;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_BC
    */
    } CALL_MODEM_BC_CHECK_REQ_STR;

#define SIZE_CALL_MODEM_BC_CHECK_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_BC_CHECK_RESP                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the constant table CALL_MODEM_BC_CHECK_RESULT */
    uint8   result;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
    */
    } CALL_MODEM_BC_CHECK_RESP_STR;

#define SIZE_CALL_MODEM_BC_CHECK_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_SS_DATA_IND                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   unused1;
    uint8   unused2;
    uint8   unused3;
    uint8   unused4;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_SS_DATA
    */
    } CALL_MODEM_SS_DATA_IND_STR;

#define SIZE_CALL_MODEM_SS_DATA_IND_STR   (8*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_EMERG_NBR_IND                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   unused;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_EMERG_NUMBER
       CALL_MODEM_SB_EMERG_NUMBER_INFO
    */
    } CALL_MODEM_EMERG_NBR_IND_STR;

#define SIZE_CALL_MODEM_EMERG_NBR_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_SERVICE_DENIED_IND                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   req_message_id; /* Message ID for requested service */
    /* Values from the bitmask table CALL_MODEM_REQ_ADDITIONAL_INFO */
    uint8   additional_info;
    /* Call ID if message relates to some existing call. Otherwise
       CALL_MODEM_ID_NONE.
       Values from the bitmask table CALL_MODEM_ID
    */
    uint8   call_id;
    uint8   unused1;
    uint8   unused2;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_CHECK_INFO
       CALL_MODEM_SB_DESTINATION_ADDRESS
       CALL_MODEM_SB_DESTINATION_POST_ADDRESS
       CALL_MODEM_SB_DESTINATION_PRE_ADDRESS
       CALL_MODEM_SB_EMERG_NUMBER_INFO
       CALL_MODEM_SB_MODE
       CALL_MODEM_SB_OPERATION
       CALL_MODEM_SB_ORIGIN_ADDRESS
       CALL_MODEM_SB_ORIGIN_INFO
       CALL_MODEM_SB_ORIGIN_SUBADDRESS
    */
    } CALL_MODEM_SERVICE_DENIED_IND_STR;

#define SIZE_CALL_MODEM_SERVICE_DENIED_IND_STR   (8*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RELEASE_END_REQ                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;   /* For future expansion */
    /* Subblock list: */
    } CALL_MODEM_RELEASE_END_REQ_STR;

#define SIZE_CALL_MODEM_RELEASE_END_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RELEASE_END_RESP                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
    */
    } CALL_MODEM_RELEASE_END_RESP_STR;

#define SIZE_CALL_MODEM_RELEASE_END_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_USER_CONNECT_IND                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the constant table CALL_MODEM_USER_CONN */
    uint8   user_conn;
    uint8   sub_blocks;
    /* Subblock list: */
    } CALL_MODEM_USER_CONNECT_IND_STR;

#define SIZE_CALL_MODEM_USER_CONNECT_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RESOURCE_IND                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_ALERTING_PATTERN
       CALL_MODEM_SB_BC
       CALL_MODEM_SB_CAUSE_OF_NO_CLI
       CALL_MODEM_SB_CHECK_INFO
       CALL_MODEM_SB_DESTINATION_ADDRESS
       CALL_MODEM_SB_DESTINATION_CS_ADDRESS
       CALL_MODEM_SB_DESTINATION_ISI_ADDRESS
       CALL_MODEM_SB_DESTINATION_POST_ADDRESS
       CALL_MODEM_SB_DESTINATION_PRE_ADDRESS
       CALL_MODEM_SB_DESTINATION_SUBADDRESS
       CALL_MODEM_SB_EMERG_NUMBER_INFO
       CALL_MODEM_SB_LINE_ID
       CALL_MODEM_SB_MODE
       CALL_MODEM_SB_ORIGIN_ADDRESS
       CALL_MODEM_SB_ORIGIN_CS_ADDRESS
       CALL_MODEM_SB_ORIGIN_INFO
       CALL_MODEM_SB_ORIGIN_SUBADDRESS
       CALL_MODEM_SB_REDIRECTING_ADDRESS
       CALL_MODEM_SB_REDIRECTING_SUBADDRESS
       CALL_MODEM_SB_REQ_INFO
       CALL_MODEM_SB_RESOURCE
       CALL_MODEM_SB_RESOURCE_SEQ_ID
       CALL_MODEM_SB_USER_TO_USER
    */
    } CALL_MODEM_RESOURCE_IND_STR;

#define SIZE_CALL_MODEM_RESOURCE_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RESOURCE_REQ                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_ALERTING_PATTERN
       CALL_MODEM_SB_BC
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_CAUSE_OF_NO_CLI
       CALL_MODEM_SB_CHECK_INFO
       CALL_MODEM_SB_DESTINATION_ADDRESS
       CALL_MODEM_SB_DESTINATION_CS_ADDRESS
       CALL_MODEM_SB_DESTINATION_ISI_ADDRESS
       CALL_MODEM_SB_DESTINATION_POST_ADDRESS
       CALL_MODEM_SB_DESTINATION_PRE_ADDRESS
       CALL_MODEM_SB_DESTINATION_SUBADDRESS
       CALL_MODEM_SB_DETAILED_CAUSE
       CALL_MODEM_SB_EMERG_NUMBER_INFO
       CALL_MODEM_SB_LINE_ID
       CALL_MODEM_SB_MODE
       CALL_MODEM_SB_ORIGIN_ADDRESS
       CALL_MODEM_SB_ORIGIN_CS_ADDRESS
       CALL_MODEM_SB_ORIGIN_INFO
       CALL_MODEM_SB_ORIGIN_SUBADDRESS
       CALL_MODEM_SB_REDIRECTING_ADDRESS
       CALL_MODEM_SB_REDIRECTING_SUBADDRESS
       CALL_MODEM_SB_RESOURCE
       CALL_MODEM_SB_RESOURCE_SEQ_ID
       CALL_MODEM_SB_RESOURCE_STATUS
       CALL_MODEM_SB_USER_TO_USER
    */
    } CALL_MODEM_RESOURCE_REQ_STR;

#define SIZE_CALL_MODEM_RESOURCE_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RESOURCE_RESP                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_RESOURCE_SEQ_ID
    */
    } CALL_MODEM_RESOURCE_RESP_STR;

#define SIZE_CALL_MODEM_RESOURCE_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RESOURCE_CLEAR_IND                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_RESOURCE
       CALL_MODEM_SB_RESOURCE_SEQ_ID
    */
    } CALL_MODEM_RESOURCE_CLEAR_IND_STR;

#define SIZE_CALL_MODEM_RESOURCE_CLEAR_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RESOURCE_CONF_IND                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the constant table CALL_MODEM_RES_CONF_STATUS */
    uint8   conf_status;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_RESOURCE
       CALL_MODEM_SB_RESOURCE_CONF_REQUIRED
    */
    } CALL_MODEM_RESOURCE_CONF_IND_STR;

#define SIZE_CALL_MODEM_RESOURCE_CONF_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RESOURCE_CONF_REQ                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* A subset of values from the constant table
       CALL_MODEM_RES_CONF_OPERATION
    */
    uint8   conf_operation;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_RESOURCE_CONF
    */
    } CALL_MODEM_RESOURCE_CONF_REQ_STR;

#define SIZE_CALL_MODEM_RESOURCE_CONF_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_RESOURCE_CONF_RESP                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    /* Values from the constant table CALL_MODEM_RES_CONF_OPERATION */
    uint8   conf_operation;
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
       CALL_MODEM_SB_RESOURCE
    */
    } CALL_MODEM_RESOURCE_CONF_RESP_STR;

#define SIZE_CALL_MODEM_RESOURCE_CONF_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_TERMINATE_REQ                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
    */
    } CALL_MODEM_TERMINATE_REQ_STR;

#define SIZE_CALL_MODEM_TERMINATE_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_TERMINATE_RESP                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_CAUSE
    */
    } CALL_MODEM_TERMINATE_RESP_STR;

#define SIZE_CALL_MODEM_TERMINATE_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_NETWORK_CONN_IND                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list: */
    } CALL_MODEM_NETWORK_CONN_IND_STR;

#define SIZE_CALL_MODEM_NETWORK_CONN_IND_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: CALL_MODEM_MESSAGE_IND                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   tr_id;
    uint8   message_id;
    uint8   call_id;      /* Values from the bitmask table CALL_MODEM_ID */
    uint8   sub_blocks;
    /* Subblock list:
       CALL_MODEM_SB_DETAILED_CAUSE
       CALL_MODEM_SB_MSG_INFO
       CALL_MODEM_SB_ORIGIN_CS_ADDRESS
       CALL_MODEM_SB_ORIGIN_SUBADDRESS
    */
    } CALL_MODEM_MESSAGE_IND_STR;

#define SIZE_CALL_MODEM_MESSAGE_IND_STR   (4*sizeof(uint8))


#define CALL_MODEM_SRV_ISI_HEADER \
    byte    tr_id; \
    byte    message_id; \
    byte    call_id; \
    byte    sub_blocks;
 
typedef struct
    {
    CALL_MODEM_SRV_ISI_HEADER
    } CALL_MODEM_ISI_STR;
 
typedef struct
    {
    uint8    tr_id;
    uint8    message_id;
    uint8    request;
    uint8    data;
    } CALL_MODEM_SRV_REQ;
 
typedef struct
    {
    uint8    tr_id;
    uint8    message_id;
    uint8    response;
    uint8    data;
    } CALL_MODEM_SRV_RESP;


#endif /* _CALL_MODEM_ISI_H */
