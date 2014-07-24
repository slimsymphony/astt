/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_ostrich.h
                -----------------
                SW Include






Project:          autogen

%name:            autogen_ostrich.h %
%version:         co1tss#120 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Fri Mar 19 12:50:16 2010 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file is the message definition file for the ostrich resource
*/


/* ============================================================================================= */
/* Message ID's */
/* ============================================================================================= */

/* PC->Ostrich messages */
#define OSTRICH_ACTIVE                           0x01
#define OSTRICH_FILTER                           0x02
#define OSTRICH_MARKER_SET                       0x03
#define OSTRICH_TIME_SET                         0x04
#define OSTRICH_STATUS_QUERY                     0x05
#define OSTRICH_GO_OFFLINE                       0x06
#define OSTRICH_AD_CONVERSION                    0x07
#define OSTRICH_LOAD_DATA                        0x08
#define OSTRICH_SEND_DATA                        0x09
#define OSTRICH_HELLO                            0x0A
#define OSTRICH_AYT_OSTRICH                      0x0B
#define OSTRICH_CLEAR_MEMORY                     0x0C
#define OSTRICH_HANDLE_STI_STREAM                0x0D
#define OSTRICH_SET_POWER_LIMITS                 0x0E
#define OSTRICH_LIST_PARAMETERS                  0x0F
#define OSTRICH_SET_DHCP_PARAMETERS              0x10
#define OSTRICH_CALL_DHCP                        0x11
#define OSTRICH_SET_IP_PARAMETERS                0x12
#define OSTRICH_SET_SYSTEM_PARAMETERS            0x13
#define OSTRICH_PREPARE_TCP                      0x14
#define OSTRICH_SET_MAINTENANCE_PARAMETERS       0x15
#define OSTRICH_LIST_PARAMETERS_1_5              0x16
#define OSTRICH_SET_STI_TIMING_PARAMETERS        0x17
#define OSTRICH_LIST_PARAMETERS_1_6              0x18
#define OSTRICH_SET_PHONE_VOLT_PERIOD            0x19
#define OSTRICH_SET_PORTS                        0x21
#define OSTRICH_SET_ID                           0x22
#define OSTRICH_LIST_PARAMETERS_1_7              0x23
#define OSTRICH_SET_MEMORY_OVERRUN_CHECK         0x24
#define OSTRICH_2_LIST_PARAMETERS                0x25
#define OSTRICH_SET_MAC_ADDRESS                  0x26
#define OSTRICH_SET_LINE_SPEED                   0x28
#define OSTRICH_SET_DIRECT_DATA_CHANNEL          0x29



/* Ostrich messages->PC */
#define OSTRICH_ACTIVE_RESP                      OSTRICH_ACTIVE
#define OSTRICH_FILTER_RESP                      OSTRICH_FILTER
#define OSTRICH_MARKER_SET_RESP                  OSTRICH_MARKER_SET
/*
#define OSTRICH_TIME_SET_RESP                    OSTRICH_TIME_SET
*/
#define OSTRICH_STATUS_QUERY_RESP                OSTRICH_STATUS_QUERY
#define OSTRICH_GO_OFFLINE_RESP                  OSTRICH_GO_OFFLINE
#define OSTRICH_AD_CONVERSION_RESP               OSTRICH_AD_CONVERSION
#define OSTRICH_LOAD_DATA_RESP                   OSTRICH_LOAD_DATA
#define OSTRICH_SEND_DATA_RESP                   OSTRICH_SEND_DATA
#define OSTRICH_HELLO_RESP                       OSTRICH_HELLO
#define OSTRICH_AYT_OSTRICH_RESP                 OSTRICH_AYT_OSTRICH
#define OSTRICH_CLEAR_MEMORY_RESP                OSTRICH_CLEAR_MEMORY
#define OSTRICH_HANDLE_STI_STREAM_RESP           OSTRICH_HANDLE_STI_STREAM
#define OSTRICH_SET_POWER_LIMITS_RESP            OSTRICH_SET_POWER_LIMITS
#define OSTRICH_SET_DHCP_PARAMETERS_RESP         OSTRICH_SET_DHCP_PARAMETERS
#define OSTRICH_CALL_DHCP_RESP                   OSTRICH_CALL_DHCP
#define OSTRICH_SET_IP_PARAMETERS_RESP           OSTRICH_SET_IP_PARAMETERS
#define OSTRICH_SET_SYSTEM_PARAMETERS_RESP       OSTRICH_SET_SYSTEM_PARAMETERS
#define OSTRICH_LIST_PARAMETERS_1_5_RESP         OSTRICH_LIST_PARAMETERS_1_5
#define OSTRICH_SET_STI_TIMING_PARAMETERS_RESP   OSTRICH_SET_STI_TIMING_PARAMETERS
#define OSTRICH_LIST_PARAMETERS_1_6_RESP         OSTRICH_LIST_PARAMETERS_1_6
#define OSTRICH_SET_PHONE_VOLT_PERIOD_RESP       OSTRICH_SET_PHONE_VOLT_PERIOD
#define OSTRICH_SET_PORTS_RESP                   OSTRICH_SET_PORTS
#define OSTRICH_SET_ID_RESP                      OSTRICH_SET_ID
#define OSTRICH_LIST_PARAMETERS_1_7_RESP         OSTRICH_LIST_PARAMETERS_1_7
#define OSTRICH_SET_MEMORY_OVERRUN_CHECK_RESP    OSTRICH_SET_MEMORY_OVERRUN_CHECK
#define OSTRICH_2_LIST_PARAMETERS_RESP           OSTRICH_2_LIST_PARAMETERS
#define OSTRICH_SET_MAC_ADDRESS_RESP             OSTRICH_SET_MAC_ADDRESS
#define OSTRICH_SET_LINE_SPEED_RESP              OSTRICH_SET_LINE_SPEED
#define OSTRICH_SET_DIRECT_DATA_CHANNEL_RESP     OSTRICH_SET_DIRECT_DATA_CHANNEL


/* PC->Musti messages */
#define MUSTI_ACTIVE                             0x51
#define MUSTI_FILTER                             0x52
#define MUSTI_MARKER_SET                         0x53
#define MUSTI_TIME_SET                           0x54
#define MUSTI_STATUS_QUERY                       0x55
#define MUSTI_GO_OFFLINE                         0x56
#define MUSTI_AD_CONVERSION                      0x57
#define MUSTI_LOAD_DATA                          0x58
#define MUSTI_SEND_DATA                          0x59
#define MUSTI_HELLO                              0x5A
#define MUSTI_CLEAR_MEMORY                       0x5C
#define MUSTI_HANDLE_DATA_STREAM                 0x5D
#define MUSTI_SET_POWER_LIMITS                   0x5E
#define MUSTI_SET_DHCP_PARAMETERS                0x60
#define MUSTI_SET_IP_PARAMETERS                  0x62
#define MUSTI_SET_STI_TIMING_PARAMETERS          0x67
#define MUSTI_SET_PHONE_VOLT_PERIOD              0x69
#define MUSTI_2_HELLO                            0x6A
#define MUSTI_INTRODUCE                          0x6B
#define MUSTI_2_ACTIVE                           0x6C
#define MUSTI_2_FILTER                           0x6D
#define MUSTI_3_ACTIVE                           0x6E
#define MUSTI_3_FILTER                           0x6F
#define MUSTI_3_LIST_PARAMETERS                  0x70
#define MUSTI_SET_PORTS                          0x71
#define MUSTI_SET_ID                             0x72
#define MUSTI_SET_TIMESTAMP_SOURCE               0x73
#define MUSTI_SET_MEMORY_OVERRUN_CHECK           0x74
#define MUSTI_2_LIST_PARAMETERS                  0x75
#define MUSTI_SET_MAC_ADDRESS                    0x76
#define MUSTI_SET_LINE_SPEED                     0x78
#define MUSTI_SET_DIRECT_DATA_CHANNEL            0x79


/* Musti messages->PC */
#define MUSTI_ACTIVE_RESP                        MUSTI_ACTIVE
#define MUSTI_3_ACTIVE_RESP                      MUSTI_3_ACTIVE
#define MUSTI_3_FILTER_RESP                      MUSTI_3_FILTER
#define MUSTI_FILTER_RESP                        MUSTI_FILTER
#define MUSTI_MARKER_SET_RESP                    MUSTI_MARKER_SET
#define MUSTI_TIME_SET_RESP                      MUSTI_TIME_SET
#define MUSTI_STATUS_QUERY_RESP                  MUSTI_STATUS_QUERY
#define MUSTI_GO_OFFLINE_RESP                    MUSTI_GO_OFFLINE
#define MUSTI_AD_CONVERSION_RESP                 MUSTI_AD_CONVERSION
#define MUSTI_LOAD_DATA_RESP                     MUSTI_LOAD_DATA
#define MUSTI_SEND_DATA_RESP                     MUSTI_SEND_DATA
#define MUSTI_HELLO_RESP                         MUSTI_HELLO
#define MUSTI_CLEAR_MEMORY_RESP                  MUSTI_CLEAR_MEMORY
#define MUSTI_HANDLE_DATA_STREAM_RESP            MUSTI_HANDLE_DATA_STREAM
#define MUSTI_SET_POWER_LIMITS_RESP              MUSTI_SET_POWER_LIMITS
#define MUSTI_SET_DHCP_PARAMETERS_RESP           MUSTI_SET_DHCP_PARAMETERS
#define MUSTI_SET_IP_PARAMETERS_RESP             MUSTI_SET_IP_PARAMETERS
#define MUSTI_SET_STI_TIMING_PARAMETERS_RESP     MUSTI_SET_STI_TIMING_PARAMETERS
#define MUSTI_SET_PHONE_VOLT_PERIOD_RESP         MUSTI_SET_PHONE_VOLT_PERIOD
#define MUSTI_2_HELLO_RESP                       MUSTI_2_HELLO
#define MUSTI_INTRODUCE_RESP                     MUSTI_INTRODUCE
#define MUSTI_2_ACTIVE_RESP                      MUSTI_2_ACTIVE
#define MUSTI_2_FILTER_RESP                      MUSTI_2_FILTER
#define MUSTI_3_LIST_PARAMETERS_RESP             MUSTI_3_LIST_PARAMETERS
#define MUSTI_SET_PORTS_RESP                     MUSTI_SET_PORTS
#define MUSTI_SET_ID_RESP                        MUSTI_SET_ID
#define MUSTI_SET_TIMESTAMP_SOURCE_RESP          MUSTI_SET_TIMESTAMP_SOURCE
#define MUSTI_SET_MEMORY_OVERRUN_CHECK_RESP      MUSTI_SET_MEMORY_OVERRUN_CHECK
#define MUSTI_2_LIST_PARAMETERS_RESP             MUSTI_2_LIST_PARAMETERS
#define MUSTI_SET_MAC_ADDRESS_RESP               MUSTI_SET_MAC_ADDRESS
#define MUSTI_SET_LINE_SPEED_RESP                MUSTI_SET_LINE_SPEED
#define MUSTI_SET_DIRECT_DATA_CHANNEL_RESP       MUSTI_SET_DIRECT_DATA_CHANNEL

/* New trace box messages */
#define TB_INIT                            0x7A
 #define TB_ACTIVATE_REQ                    0x00
 #define TB_ACTIVATE_RESP                   0x01
 #define TB_ALLOW_BAN_LOGBOOK_REQ           0x10 /* Fido */
 #define TB_ALLOW_BAN_LOGBOOK_RESP          0x11
 #define TB_ALLOW_BAN_ALERTS_REQ            0x12
 #define TB_ALLOW_BAN_ALERTS_RESP           0x13
 #define TB_ALLOW_CONTROL_PANEL_REQ         0x14
 #define TB_ALLOW_CONTROL_PANEL_RESP        0x15
 #define TB_STATE_MESSAGES_GET_REQ          0x16
 #define TB_STATE_MESSAGES_GET_RESP         0x17
 #define TB_TERMINATE_REQ                   0x18
 #define TB_TERMINATE_RESP                  0x19
 #define TB_DATA_CHANNEL_RESERVE_REQ        0x1A
 #define TB_DATA_CHANNEL_RESERVE_RESP       0x1B
 #define TB_DATA_CHANNEL_OPEN_CLOSE_REQ     0x1C
 #define TB_DATA_CHANNEL_OPEN_CLOSE_RESP    0x1D

#define TB_COMMAND                         0x7B
 #define TB_RESET_REQ                       0x00
 #define TB_RESET_RESP                      0x01
 #define TB_PERFORMANCE_STATUS_REQ          0x02
 #define TB_PERFORMANCE_STATUS_RESP         0x03
 #define TB_PERFORMANCE_STATUS_NTF          0x04
 #define TB_TIME_SET_REQ                    0x09 /* Fido */
 #define TB_TIME_SET_RESP                   0x0A
 #define TB_PORT_OPEN_CLOSE_REQ             0x10
 #define TB_PORT_OPEN_CLOSE_RESP            0x11
 #define TB_ALL_PORT_OPEN_CLOSE_REQ         0x12
 #define TB_ALL_PORT_OPEN_CLOSE_RESP        0x13
 #define TB_PORT_PARAMETERS_SET_REQ         0x14
 #define TB_PORT_PARAMETERS_SET_RESP        0x15
 #define TB_ALL_PORT_PARAMETERS_GET_REQ     0x16
 #define TB_ALL_PORT_PARAMETERS_GET_RESP    0x17
 #define TB_ALL_PORT_CURRENT_PROTOCOL_GET_REQ   0x18
 #define TB_ALL_PORT_CURRENT_PROTOCOL_GET_RESP  0x19
 #define TB_ALL_PORT_MARKER_SET_REQ         0x1A
 #define TB_ALL_PORT_MARKER_SET_RESP        0x1B
 #define TB_TEXTUAL_COMMAND_SET_REQ         0x1C
 #define TB_TEXTUAL_COMMAND_SET_RESP        0x1D
 #define TB_TEXTUAL_COMMANDS_FILE_SET_REQ   0x1E
 #define TB_TEXTUAL_COMMANDS_FILE_SET_RESP  0x1F
 #define TB_SEND_TO_DEVICE_REQ              0x20
 #define TB_SEND_TO_DEVICE_RESP             0x21
 #define TB_DATA_TARGET_SET_REQ             0x22
 #define TB_DATA_TARGET_SET_RESP            0x23

#define TB_INFO                            0x7C
 #define TB_VERSION_GET_REQ                 0x00
 #define TB_VERSION_GET_RESP                0x01
 #define TB_THROUGHPUT_QUERY_REQ            0x02
 #define TB_THROUGHPUT_QUERY_RESP           0x03
 #define TB_PORT_INDICATION_GET_REQ         0x10 /* Fido */
 #define TB_PORT_INDICATION_GET_RESP        0x11
 #define TB_SW_INDICATION_GET_REQ           0x12
 #define TB_SW_INDICATION_GET_RESP          0x13
 #define TB_DATA_PROCESSING_STATE_GET_REQ   0x14
 #define TB_DATA_PROCESSING_STATE_GET_RESP  0x15
 #define TB_SIGNAL_CHARACTERISTICS_GET_REQ  0x16 /**/
 #define TB_SIGNAL_CHARACTERISTICS_GET_RESP 0x17 /**/

#define TB_CONFIGURATION                   0x7D
 #define TB_PHONE_INTERVIEW_MODE_SET_REQ    0x00
 #define TB_PHONE_INTERVIEW_MODE_SET_RESP   0x01
 #define TB_PHONE_INTERVIEW_MODE_GET_REQ    0x02
 #define TB_PHONE_INTERVIEW_MODE_GET_RESP   0x03
 #define TB_STI_PROTOCOL_SET_REQ            0x04
 #define TB_STI_PROTOCOL_SET_RESP           0x05
 #define TB_STI_PROTOCOL_GET_REQ            0x06
 #define TB_STI_PROTOCOL_GET_RESP           0x07
 #define TB_CONFIG_GET_REQ                  0x42 /* Fido */
 #define TB_CONFIG_GET_RESP                 0x43
 #define TB_ALL_PORT_GET_REQ                0x44
 #define TB_ALL_PORT_GET_RESP               0x45
 #define TB_PORT_OR_BOX_RENAME_REQ          0x46
 #define TB_PORT_OR_BOX_RENAME_RESP         0x47
 #define TB_PORT_REMOVE_REQ                 0x48
 #define TB_PORT_REMOVE_RESP                0x49
 #define TB_PORT_INSERT_REQ                 0x4A
 #define TB_PORT_INSERT_RESP                0x4B
 #define TB_PORT_DISCONNECT_REQ             0x50
 #define TB_PORT_DISCONNECT_RESP            0x51
 #define TB_ALL_PORT_DISCONNECT_REQ         0x52
 #define TB_ALL_PORT_DISCONNECT_RESP        0x53
 #define TB_PORT_CONNECT_REQ                0x54
 #define TB_PORT_CONNECT_RESP               0x55
 #define TB_PORT_WINK_LED_REQ               0x56
 #define TB_PORT_WINK_LED_RESP              0x57
 #define TB_ALL_FREE_BOX_GET_REQ            0x58
 #define TB_ALL_FREE_BOX_GET_RESP           0x59
 #define TB_BOX_WINK_LED_REQ                0x5A
 #define TB_BOX_WINK_LED_RESP               0x5B
 #define TB_EMULATE_MUSTI_REQ               0x5E
 #define TB_EMULATE_MUSTI_RESP              0x5F
 #define TB_CONFIG_PARAMETERS_SET_REQ       0x62
 #define TB_CONFIG_PARAMETERS_SET_RESP      0x63
 #define TB_REMOTE_RES_GET_REQ              0x64
 #define TB_REMOTE_RES_GET_RESP             0x65
 #define TB_REMOTE_RES_CONNECT_REQ          0x66
 #define TB_REMOTE_RES_CONNECT_RESP         0x67
 #define TB_REMOTE_RES_DISCONNECT_REQ       0x68
 #define TB_REMOTE_RES_DISCONNECT_RESP      0x69
 #define TB_REMOTE_RES_REMOVE_REQ           0x6A
 #define TB_REMOTE_RES_REMOVE_RESP          0x6B
 #define TB_SW_VERSION_GET_REQ              0x6C
 #define TB_SW_VERSION_GET_RESP             0x6D

#define TB_FILTER                          0x7E
 #define TB_FILTER_CLEAR_REQ                0x00
 #define TB_FILTER_CLEAR_RESP               0x01
 #define TB_FILTER_SET_REQ                  0x02
 #define TB_FILTER_SET_RESP                 0x03
 #define TB_FILTER_GET_REQ                  0x04
 #define TB_FILTER_GET_RESP                 0x05
 #define TB_FILTER_RESET_REQ                0x06
 #define TB_FILTER_RESET_RESP               0x07

#define TB_CONNECT                         0x7F
 #define TB_SESSION_START_REQ               0x00 /*Fido */
 #define TB_SESSION_START_RESP              0x01
 #define TB_SESSION_END_REQ                 0x02
 #define TB_SESSION_END_RESP                0x03

#define TB_ALERT                           0xF9
 #define TB_ALERT_PORT_CHANGE_IND                  0x00
 #define TB_ALERT_PORT_REMOVE_IND                  0x01
 #define TB_ALERT_PORT_OR_BOX_RENAME_IND           0x02
 #define TB_ALERT_CONFIG_CHANGE_IND                0x03
 #define TB_ALERT_FREE_BOX_APPEAR_IND              0x04
 #define TB_ALERT_FREE_BOX_DISAPPEAR_IND           0x05
 #define TB_ALERT_PORT_PARAMETERS_CHANGE_IND       0x06
 #define TB_ALERT_PORT_CURRENT_PROTOCOL_CHANGE_IND 0x07
 #define TB_ALERT_LOGBOOK_MESSAGE_IND              0x08
 #define TB_ALERT_REMOTE_RES_CHANGE_IND            0x0B
 #define TB_ALERT_REMOTE_RES_REMOVE_IND            0x0C
 #define TB_ALERT_CONTROL_PANEL_OFF_IND            0x0D
 #define TB_ALERT_DEVICE_CONNECTION_CHANGE_IND     0x0E
 #define TB_ALERT_DATA_TO_DEVICE_FAILED_IND        0x0F

/* trace box subblocks */

#define TB_SB_FILTER_GENERAL                     0x00
#define TB_SB_FILTER_CHANNEL_GROUPS              0x01
#define TB_SB_FILTER_CHANNEL_MASTERS             0x02
#define TB_SB_PORT_STATE                         0x20 /*Fido */
#define TB_SB_PORT_INDICATION_VALUE              0x21
#define TB_SB_PORT_RENAME                        0x22
#define TB_SB_LOGBOOK_MESSAGE                    0x23
#define TB_SB_PORT_MUSTI                         0x24
#define TB_SB_FREE_BOX                           0x25
#define TB_SB_PORT_TO_FREE_BOX                   0x26
#define TB_SB_PORT_PROTOCOL_XTI                  0x27
/* #define TB_SB_PORT_PROTOCOL_STI                  0x28 TBS? */
#define TB_SB_PORT_RESYNC_MIN_PAUSE_XTI          0x29
#define TB_SB_PORT_RESYNC_MIN_PAUSE_STI          0x2A
#define TB_SB_PORT_STREAM_MAX_PAUSE_XTI          0x2B

#define TB_SB_PORT_STREAM_MAX_PAUSE_STI          0x2C /* 2.7 */
#define TB_SB_PORT_TRANSMIT_MIN_PAUSE_STI        0x2D /* 2.7 */
#define TB_SB_PORT_SEPARATE_ADSP_DSP             0x2E /* 2.7 */
#define TB_SB_PORT_PROTOCOL                      0x2F /* 2.7 */

#define TB_SB_PORT_MASTER_ENDIANNESS             0x30

#define TB_SB_PORT_CURRENT_PROTOCOL              0x31 /* 2.7 */

#define TB_SB_PORT_ALL_MASTER_ENDIANNESS         0x32
#define TB_SB_SW_INDICATION_VALUE                0x33

#define TB_SB_CONFIG                             0x34 /* 2.7 */
#define TB_SB_COMMAND                            0x35 /* 2.7 */
#define TB_SB_RESPONSE                           0x36 /* 2.7 */

#define TB_SB_REMOTE_RESOURCE                    0x37
#define TB_SB_DATA_PROCESSING_STATE              0x38
#define TB_SB_STATE_MESSAGE                      0x39

#define TB_SB_SENDING_FAILURE                    0x3A /* 2.7 */

#define TB_SB_MARKER                             0x3B

#define TB_SB_BOX_RENAME                         0x3C /* 2.7 */

#define TB_SB_PORT_MASTER_FILTER                 0x3D
#define TB_SB_PORT_ALL_MASTER_FILTER             0x3E

#define TB_SB_EYES_STATE                         0x3F /* 2.7 */
#define TB_SB_PORT_TIMING_CORRECTION_DATA        0x40 /* 2.7 */
#define TB_SB_PORT_CALIBRATION_MODE              0x41 /* 2.7 */
#define TB_SB_PORT_DETECT_TARGET_PRESENCE        0x42 /* 2.7 */

/* Musti Originated Messages */
#define GPS_INFO                           0xFA

/* Ostrich Originated Messages */
#define OSTRICH_PHONE_VOLTAGE                    0xFB
#define OSTRICH_AYT_PC                           0xFC
#define OSTRICH_PHONET_STAMP                     0xFD
#define OSTRICH_ALERT                            0xFE
#define OSTRICH_MARKER                           0xFF


/* MCU_OSMO msg id's */

#define NOS_TRACES                               0x80
#define DSP_OSMO                                 0x81   
#define INSTR_DATA                               0x82
#define MCU_ASCII_PRINTF                         0x83
#define MCU_RAW_DATA                             0x84
#define MCU_RAW_DATA_NEW                         0x85
#define MCU_TRACE_DATA                           0x86

#define PRIMARY_MSG                              0x87
#define DSP_ASCII_PRINTF                         0x88
#define DSP_RAW_DATA                             0x89
#define DSP_RAW_DATA2                            0x8A
#define ADSP_RAW_DATA                            0x8D
#define DSP_RAW_DATA_NEW                         0x8F
#define ADSP_RAW_DATA_NEW                        0x90
#define SYMBIAN_TRACE                            0x91

#define TB_TRACE_MSG                             0x94
#define TB_TRACE_EXCEPTION_MSG                   0x95


/* ============================================================================================= */
/* Resource definition */
/* ============================================================================================= */

#define OSTRICH_PARAMETERS \
    REFERENCE(8, BE, n_par, "N par", N) \
    SEQ_OF_REF(par, "Par", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_DONT_GENERATE)

#define OSTRICH_SUCCESS \
    VALUE(8, BE, success, "Success", HEX)

#define OSTRICH_DECISION \
    VALUE_CONST(decision, "Decision", OSTRICH_ACCEPTANCE)

#define OSTRICH_COMMENT \
    STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, comment, "Comment", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)

#define LIST_OF_GROUPS \
    REFERENCE(8, BE, n, "Number of IDs", N) \
    CHOICE_BEGIN(ids, "IDs", GROUP) \
        CASE_BEGIN(PRIMARY_GROUP, "", "") \
            SEQ_OF_REF(list, "ID", PRIMARY_GROUP_MSG, N, ISIHDR_DONT_GENERATE) \
        CASE_END \
        CASE_BEGIN(SECONDARY_GROUP, "", "") \
            SEQ_OF_REF(list, "ID", SECONDARY_GROUP_MSG, N, ISIHDR_DONT_GENERATE) \
        CASE_END \
        CASE_BEGIN(STATUS_GROUP, "", "") \
            SEQ_OF_REF(list, "ID", STATUS_GROUP_MSG, N, ISIHDR_DONT_GENERATE) \
        CASE_END \
        CASE_BEGIN(COMMAND_GROUP, "", "") \
            SEQ_OF_REF(list, "ID", COMMAND_GROUP_MSG, N, ISIHDR_DONT_GENERATE) \
        CASE_END \
        CASE_BEGIN(PRIMARY_GROUP_XTI, "", "") \
            SEQ_OF_REF(list, "ID", PRIMARY_GROUP_XTI_MSG, N, ISIHDR_DONT_GENERATE) \
        CASE_END \
        CASE_BEGIN(SECONDARY_GROUP_XTI, "", "") \
            SEQ_OF_REF(list, "ID", SECONDARY_GROUP_XTI_MSG, N, ISIHDR_DONT_GENERATE) \
        CASE_END \
        CASE_BEGIN(STATUS_GROUP_XTI, "", "") \
            SEQ_OF_REF(list, "ID", STATUS_GROUP_XTI_MSG, N, ISIHDR_DONT_GENERATE) \
        CASE_END \
        CASE_BEGIN(COMMAND_GROUP_XTI, "", "") \
            SEQ_OF_REF(list, "ID", COMMAND_GROUP_XTI_MSG, N, ISIHDR_DONT_GENERATE) \
        CASE_END \
        DEFAULT_BEGIN("", "") \
            SEQ_OF_REF(list, "ID", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_DONT_GENERATE) \
        DEFAULT_END \
    CHOICE_END

PROPERTY_STRING(PROPERTY_PROJECT_NAME, "Device Trace and Debug Tools")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME, "Stig Holmsten Eliasen")
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME, "Copenhagen")

PROPERTY_VALUE(PROPERTY_PHONET_DEVICE_ID, PN_DEV_TRACEBOX)
PROPERTY(PROPERTY_DEVICE_DEPENDENT_MESSAGES)
PROPERTY_VALUE(PROPERTY_PHONET_OBJECT_ID, 1)
PROPERTY_STRING(PROPERTY_HTML_FILENAME, "i_tracebox_m.html")
PROPERTY_STRING(PROPERTY_HTML_TITLE, "Tracebox Message Specification")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,    "TB_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16, "")
PROPERTY(PROPERTY_SUBMSG_NAMES_ARE_UNIQUE)
PROPERTY(PROPERTY_HTML_EXPAND_CONSTANT_LISTS)

PROPERTY(PROPERTY_ALIGNMENT_CHECK_DISABLE)
#if ((defined AUTOGEN_INCLUDE_OST) && (defined AUTOGEN_INCLUDE_TB_INTO_OST))
/* Tracebox definitions for OST protocol */
RES_BEGIN(RESOURCE_OST, OST_TRACEBOX_CONTROL, OST_TB, "OST Tracebox Control", "", FALSE)
#else
/* Tracebox definitions for PhoNet protocol */
RES_BEGIN(RESOURCE_ISI, PN_TRACEBOX, TB, "Tracebox", "", FALSE)
#endif

    /* --------------------------------------------------------------------- */
    /* Symbols */
    /* --------------------------------------------------------------------- */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONST_TBL_BEGIN(OSTRICH_TIME_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(OSTRICH_TIME,            0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OSTRICH_GROUPS, 8, BE, "", "")
        CONST_TBL_ENTRY(PRIMARY_GROUP,       0x01, "")
        CONST_TBL_ENTRY(SECONDARY_GROUP,     0x02, "")
        CONST_TBL_ENTRY(STATUS_GROUP,        0x03, "")
        CONST_TBL_ENTRY(COMMAND_GROUP,       0x04, "")
        CONST_TBL_ENTRY(PRIMARY_GROUP_XTI,   0x05, "")
        CONST_TBL_ENTRY(SECONDARY_GROUP_XTI, 0x06, "")
        CONST_TBL_ENTRY(STATUS_GROUP_XTI,    0x07, "")
        CONST_TBL_ENTRY(COMMAND_GROUP_XTI,   0x08, "")
        CONST_TBL_ENTRY(ALERT,               0xFE, "")
        CONST_TBL_ENTRY(EVERYTHING,          0xFF, "")
    CONST_TBL_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONST_TBL_BEGIN(OSTRICH_POWER_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(PHONE_POWER,         0x01, "")
        CONST_TBL_ENTRY(ACTUAL_POWER,        0x02, "")
        CONST_TBL_ENTRY(EXTERNAL_POWER,      0x03, "")
    CONST_TBL_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONST_TBL_BEGIN(OSTRICH_MEMORY_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(DATA_IN_STI_TX,      0x00, "")
        CONST_TBL_ENTRY(DAJ_DATA,            0x01, "")
        CONST_TBL_ENTRY(STI_BLOCK_DATA,      0x02, "")
        CONST_TBL_ENTRY(DATA_IN_XTI_TX,      0x03, "")
        CONST_TBL_ENTRY(XTI_BLOCK_DATA,      0x04, "")
        CONST_TBL_ENTRY(MAIN_BUFFER,         0xFE, "")
        CONST_TBL_ENTRY(EVERYTHING,          0xFF, "")
    CONST_TBL_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONST_TBL_BEGIN(OSTRICH_STI_STREAM, 8, BE, "", "")
        CONST_TBL_ENTRY(CLOSE_STI,           0x01, "")
        CONST_TBL_ENTRY(OPEN_STI,            0x02, "")
    CONST_TBL_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONST_TBL_BEGIN(OSTRICH_CHANNEL, 8, BE, "", "")
        CONST_TBL_ENTRY(CHANNEL_1,   0x01, "")
        CONST_TBL_ENTRY(CHANNEL_2,   0x02, "")
        CONST_TBL_ENTRY(CHANNEL_3,   0x03, "")
        CONST_TBL_ENTRY(CHANNEL_4,   0x04, "")
        CONST_TBL_ENTRY(CHANNEL_5,   0x05, "")
        CONST_TBL_ENTRY(CHANNEL_6,   0x06, "")
    CONST_TBL_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONST_TBL_BEGIN(OSTRICH_BUS, 8, BE, "", "")
        CONST_TBL_ENTRY(XTI,   0x01, "")
        CONST_TBL_ENTRY(STI,   0x02, "")
    CONST_TBL_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONST_TBL_BEGIN(OSTRICH_PAUSE, 8, BE, "", "")
        CONST_TBL_ENTRY(PAUSE_BETWEEN_STI_MSGS, 0x01, "")
        CONST_TBL_ENTRY(PAUSE_TO_CANCEL_ERROR,  0x02, "")
        CONST_TBL_ENTRY(PAUSE_BETWEEN_TX_BYTES, 0x03, "")
    CONST_TBL_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONST_TBL_BEGIN(OSTRICH_MARKER_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(OSTRICH_ASSIGNED_MARKER,        0x01, "")
        CONST_TBL_ENTRY(PC_ASSIGNED_MARKER,             0x02, "")
        CONST_TBL_ENTRY(TIMEBASE_MARKER,                0x03, "")
        CONST_TBL_ENTRY(INVALID_PC_MSG,                 0x04, "")
        CONST_TBL_ENTRY(INVALID_STI_MSG,                0x05, "")
        CONST_TBL_ENTRY(DATA_CORRUPTED,                 0x06, "")
        CONST_TBL_ENTRY(VOLTAGE_FAILURE,                0x07, "")
        CONST_TBL_ENTRY(BATTERY_RUNNING,                0x08, "")
        CONST_TBL_ENTRY(BATTERY_GETTING_LOW,            0x09, "")
        CONST_TBL_ENTRY(NORMAL_POWER,                   0x0A, "")
        CONST_TBL_ENTRY(MEMORY_IS_CLOSED,               0x0B, "")
        CONST_TBL_ENTRY(MEMORY_WARNING,                 0x0C, "")
        CONST_TBL_ENTRY(MEMORY_IS_NORMAL,               0x0D, "")
        CONST_TBL_ENTRY(STREAM_TO_PHONE_BLOCKED_UP,     0x0E, "")
        CONST_TBL_ENTRY(PHONE_LOST,                     0x0F, "")
        CONST_TBL_ENTRY(PHONE_GOT,                      0x10, "")
        CONST_TBL_ENTRY(NO_PHONE_DATA_STREAM,           0x11, "")
        CONST_TBL_ENTRY(YES_PHONE_DATA_STREAM,          0x12, "")
        CONST_TBL_ENTRY(PAUSE_IN_STI_STREAM_LONG,       0x13, "")
        CONST_TBL_ENTRY(STI_FPGA_OVERFLOW,              0x14, "")
        CONST_TBL_ENTRY(STI_FPGA_ILLEGAL,               0x15, "")
        CONST_TBL_ENTRY(STI_PROC_BUF_OVERFLOW,          0x16, "")
        CONST_TBL_ENTRY(NO_MEMORY,                      0x18, "")
        CONST_TBL_ENTRY(INVALID_XTI_MSG,                0x1B, "")
        CONST_TBL_ENTRY(FLASH_DISK_ERROR,               0x1C, "")
        CONST_TBL_ENTRY(CHANNEL_DIRECT_BLOCKED_UP,      0x1D, "")

        CONST_TBL_ENTRY(PHONE_1_VOLT_LOW,               0x1F, "")
        CONST_TBL_ENTRY(PHONE_1_VOLT_NORMAL_AGAIN,      0x20, "")
        CONST_TBL_ENTRY(PHONE_2_VOLT_LOW,               0x21, "")
        CONST_TBL_ENTRY(PHONE_2_VOLT_NORMAL_AGAIN,      0x22, "")
        CONST_TBL_ENTRY(PAUSE_IN_XTI_STREAM_LONG,       0x23, "")
        CONST_TBL_ENTRY(XTI_FPGA_OVERFLOW,              0x24, "")
        CONST_TBL_ENTRY(XTI_FPGA_ILLEGAL_MSG,           0x25, "")
        CONST_TBL_ENTRY(XTI_PROC_BUF_OVERFLOW,          0x26, "")
        CONST_TBL_ENTRY(XTI_ILLEGAL_FROM_FPGA,          0x27, "")
        CONST_TBL_ENTRY(XTI_MARKER_STORED,              0x28, "")
        CONST_TBL_ENTRY(STI_MARKER_STORED,              0x29, "")
        CONST_TBL_ENTRY(TIME_BASE_CHANGED,              0x2A, "")
        CONST_TBL_ENTRY(STI_BLOCK_DATA_SEND_ENDED,      0x2B, "")
        CONST_TBL_ENTRY(DIRECT_CHANNEL_CLOSED,          0x2C, "")
        CONST_TBL_ENTRY(DIRECT_DATA_SEND_ENDED,         0x2D, "")
        CONST_TBL_ENTRY(XTI_PHONE_OVERFLOW,             0x2E, "")
        CONST_TBL_ENTRY(XTI_ILLEGAL_BIT_RATE,           0x2F, "")
        CONST_TBL_ENTRY(XTI_NOT_WOKEN_UP,               0x30, "")
        CONST_TBL_ENTRY(XTI_NOT_CONFIRM_DATA_LEN,       0x31, "")
        CONST_TBL_ENTRY(XTI_NOT_CONFIRM_DATA,           0x32, "")
        CONST_TBL_ENTRY(XTI_BLOCK_DATA_SEND_ENDED,      0x33, "")
        CONST_TBL_ENTRY(XTI_BLOCK_DATA_SEND_BROKEN,     0x34, "")
        CONST_TBL_ENTRY(XTI_BLOCK_DATA_SEND_ERRORS,     0x35, "")
        CONST_TBL_ENTRY(MASS_MEDIA_OPEN_STI,            0x36, "")
        CONST_TBL_ENTRY(MASS_MEDIA_OPEN_FAIL_STI,       0x37, "")
        CONST_TBL_ENTRY(MASS_MEDIA_CLOSE_STI,           0x38, "")
        CONST_TBL_ENTRY(MASS_MEDIA_OPEN_XTI,            0x3A, "")
        CONST_TBL_ENTRY(MASS_MEDIA_OPEN_FAIL_XTI,       0x3B, "")
        CONST_TBL_ENTRY(MASS_MEDIA_CLOSE_XTI,           0x3C, "")
        CONST_TBL_ENTRY(MASS_MEDIA_OPER_FAIL_XTI,       0x3D, "")
        CONST_TBL_ENTRY(MASS_MEDIA_ACCESS_DIRECT,       0x3E, "")
        CONST_TBL_ENTRY(MASS_MEDIA_DEVICE_ERROR,        0x3F, "")
        CONST_TBL_ENTRY(MASS_MEDIA_COMM_ERROR,          0x40, "")
        CONST_TBL_ENTRY(STI_BLOCK_DATA_SEND_BROKEN,     0x41, "")
        CONST_TBL_ENTRY(STI_BLOCK_DATA_SEND_ERRORS,     0x42, "")
        CONST_TBL_ENTRY(STI_DIRECT_SEND_BROKEN,         0x43, "")
        CONST_TBL_ENTRY(STI_DIRECT_SEND_ERROR,          0x44, "")
        CONST_TBL_ENTRY(MASS_MEDIA_OPER_FAIL_STI,       0x45, "")
        CONST_TBL_ENTRY(STI_ILLEGAL_FROM_FPGA,          0x46, "")
        CONST_TBL_ENTRY(DIRECT_NOT_SUPPORTED,           0x47, "")
        CONST_TBL_ENTRY(CONNECTION_RESTART,             0x49, "")
        CONST_TBL_ENTRY(XTI_UNFINISHED_MSG,             0x4A, "")
        CONST_TBL_ENTRY(NO_DIRECT_CHANNEL,              0x4E, "")
        CONST_TBL_ENTRY(DIRECT_NOT_CONNECTED,           0x4F, "")
    CONST_TBL_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONST_TBL_BEGIN(OSTRICH_DEFAULT, 8, BE, "", "")
        CONST_TBL_ENTRY(OSTRICH_DEFAULT,     0x01, "")
    CONST_TBL_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONST_TBL_BEGIN(OSTRICH_ACCEPTANCE, 8, BE, "", "")
        CONST_TBL_ENTRY(REJECTED, 0x00, "")
        CONST_TBL_ENTRY(ACCEPTED, 0x01, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OSTRICH_PRIMARY_GROUPS, 8, BE, "", "")
        CONST_TBL_ENTRY(MCU_STI_OSMO_WRITE_BYTE,        0x0A, "")
        CONST_TBL_ENTRY(MCU_STI_OSMO_WRITE_WORD,        0x8A, "")
        CONST_TBL_ENTRY(MCU_STI_OSMO_WRITE_DWORD,       0x4A, "")
        CONST_TBL_ENTRY(MCU_IO_WRITE,                   0x2A, "")
        CONST_TBL_ENTRY(MCU_IO_READ,                    0xAA, "")
        CONST_TBL_ENTRY(MCU_IO_WRITE_MATCH,             0x6A, "")
        CONST_TBL_ENTRY(MCU_IO_READ_MATCH,              0xEA, "")
        CONST_TBL_ENTRY(DSP_STI_OSMO_WRITE,             0x9A, "")
        CONST_TBL_ENTRY(DSP_IO_WRITE,                   0x3A, "")
        CONST_TBL_ENTRY(DSP_IO_READ,                    0xBA, "")
        CONST_TBL_ENTRY(ADSP_OSMO_WRITE,                0x7A, "")
        CONST_TBL_ENTRY(ADSP_IO_WRITE,                  0xCA, "")
        CONST_TBL_ENTRY(ADSP_IO_READ,                   0xFA, "")
        CONST_TBL_ENTRY(MCU_WRITE_MATCH_VER_2,          0x1A, "")
        CONST_TBL_ENTRY(MCU_READ_MATCH_VER_2,           0x5A, "")
        CONST_TBL_ENTRY(DSP_BLOCK_DUMP,                 0xDA, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OSTRICH_SECONDARY_GROUPS, 8, BE, "", "")
        CONST_TBL_ENTRY(MCU_OSMO,                       0x80, "")
        CONST_TBL_ENTRY(DSP_OSMO,                       0x81, "")
        CONST_TBL_ENTRY(INSTRUMENTATION,                0x82, "")
        CONST_TBL_ENTRY(ASCII_PRINTF,                   0x83, "")
        CONST_TBL_ENTRY(RAW_TASK_DATA,                  0x84, "")
        CONST_TBL_ENTRY(DSP_BLOCK_DUMP_,                0x86, "")
        CONST_TBL_ENTRY(DSP_ASCII_PRINTF,               0x88, "")
        CONST_TBL_ENTRY(DSP_RAW_DATA,                   0x89, "")
        CONST_TBL_ENTRY(DSP_SPECIFIC_DATA,              0x8A, "")
        CONST_TBL_ENTRY(ADSP_OSMO,                      0x8B, "")
        CONST_TBL_ENTRY(ADSP_ASCII_PRINTF,              0x8C, "")
        CONST_TBL_ENTRY(ADSP_RAW_DATA,                  0x8D, "")
        CONST_TBL_ENTRY(ADSP_SPECIFIC_DATA,             0x8E, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OSTRICH_STATUS_GROUPS, 8, BE, "", "")
        CONST_TBL_ENTRY(PHONE_SUPPLY_VOLTAGE,           0xFB, "")
        CONST_TBL_ENTRY(AYT,                            0xFC, "")
        CONST_TBL_ENTRY(TIME_STAMPS,                    0xFD, "")
        CONST_TBL_ENTRY(ALERTS,                         0xFE, "")
        CONST_TBL_ENTRY(MARKERS,                        0xFF, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OSTRICH_COMMAND_GROUPS, 8, BE, "", "")
        CONST_TBL_ENTRY(MCU_MASS_MEDIA,                 0x0A, "")
        CONST_TBL_ENTRY(CDSP_MASS_MEDIA,                0x0B, "")
        CONST_TBL_ENTRY(ADSP_MASS_MEDIA,                0x07, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OSTRICH_PRIMARY_GROUPS_XTI, 8, BE, "", "")
        CONST_TBL_ENTRY(DSP_OSMO_,                      0x0B, "")
        CONST_TBL_ENTRY(DSP_OSMO_T,                     0x1B, "")
        CONST_TBL_ENTRY(MCU_OSMO_,                      0x7B, "")
        CONST_TBL_ENTRY(MCU_OSMO_T,                     0x8B, "")
        CONST_TBL_ENTRY(VIA_IO_READ,                    0x9B, "")
        CONST_TBL_ENTRY(VIA_IO_READ_T,                  0xAB, "")
        CONST_TBL_ENTRY(VIA_IO_WRITE,                   0xBB, "")
        CONST_TBL_ENTRY(VIA_IO_WRITE_T,                 0xCB, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OSTRICH_SECONDARY_GROUPS_XTI, 8, BE, "", "")
        CONST_TBL_ENTRY(MCU_OSMO,                       0x80, "")
        CONST_TBL_ENTRY(MCU_ASCII_PRINTF,               0x83, "")
        CONST_TBL_ENTRY(MCU_RAW_DATA,                   0x84, "")
        CONST_TBL_ENTRY(MCU_RAW_DATA_NEW,               0x85, "")
        CONST_TBL_ENTRY(MCU_INSTRUMENTATION_DATA,       0x82, "")
        CONST_TBL_ENTRY(DSP_OSMO,                       0x81, "")
        CONST_TBL_ENTRY(DSP_ASCII_PRINTF,               0x88, "")
        CONST_TBL_ENTRY(DSP_RAW_DATA,                   0x89, "")
        CONST_TBL_ENTRY(DSP_RAW_DATA_NEW,               0x8F, "")
        CONST_TBL_ENTRY(DSP_SPECIFIC_DATA,              0x8A, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OSTRICH_STATUS_GROUPS_XTI, 8, BE, "", "")
        CONST_TBL_ENTRY(GPS,                            0xFA, "")
        CONST_TBL_ENTRY(PHONE_SUPPLY_VOLTAGE,           0xFB, "")
        CONST_TBL_ENTRY(TIME_STAMPS,                    0xFD, "")
        CONST_TBL_ENTRY(MARKERS,                        0xFF, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(OSTRICH_COMMAND_GROUPS_XTI, 8, BE, "", "")
        CONST_TBL_ENTRY(MCU_MASS_MEDIA,                 0x0A, "")
        CONST_TBL_ENTRY(DSP_MASS_MEDIA,                 0x0B, "")
        CONST_TBL_ENTRY(MCU_BIT_RATE,                   0x0C, "")
        CONST_TBL_ENTRY(DSP_BIT_RATE,                   0x0D, "")
        CONST_TBL_ENTRY(MCU_TICK_LENGTH,                0x0E, "")
        CONST_TBL_ENTRY(DSP_TICK_LENGTH,                0x0F, "")
    CONST_TBL_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONST_TBL_BEGIN(MUSTI_HANDLE_DATA_STREAM_OC, 8, BE, "", "")
        CONST_TBL_ENTRY(MUSTI_CLOSE_CH2,                            0x01, "")
        CONST_TBL_ENTRY(MUSTI_OPEN_CH2,                             0x02, "")
        CONST_TBL_ENTRY(MUSTI_CLOSE_CH1,                            0x03, "")
        CONST_TBL_ENTRY(MUSTI_OPEN_CH1,                             0x04, "")
    CONST_TBL_END


    /* sequences */

    SEQ_BEGIN(NOT_USED, DONT_CREATE_STRUCT, "", "")
        FILLER(FILLER_FIXED, 8)
    SEQ_END


    SEQ_BEGIN(PRIMARY_GROUP_MSG, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(msgtype, "Msg type", OSTRICH_PRIMARY_GROUPS)
    SEQ_END

    SEQ_BEGIN(SECONDARY_GROUP_MSG, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(msgtype, "Msg type", OSTRICH_SECONDARY_GROUPS)
    SEQ_END

    SEQ_BEGIN(STATUS_GROUP_MSG, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(msgtype, "Msg type", OSTRICH_STATUS_GROUPS)
    SEQ_END

    SEQ_BEGIN(COMMAND_GROUP_MSG, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(msgtype, "Msg type", OSTRICH_COMMAND_GROUPS)
    SEQ_END

    SEQ_BEGIN(PRIMARY_GROUP_XTI_MSG, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(msgtype, "Msg type", OSTRICH_PRIMARY_GROUPS_XTI)
    SEQ_END

    SEQ_BEGIN(SECONDARY_GROUP_XTI_MSG, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(msgtype, "Msg type", OSTRICH_SECONDARY_GROUPS_XTI)
    SEQ_END

    SEQ_BEGIN(STATUS_GROUP_XTI_MSG, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(msgtype, "Msg type", OSTRICH_STATUS_GROUPS_XTI)
    SEQ_END

    SEQ_BEGIN(COMMAND_GROUP_XTI_MSG, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(msgtype, "Msg type", OSTRICH_COMMAND_GROUPS_XTI)
    SEQ_END


    /* --------------------------------------------------------------------- */
    /* Trace box messages */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_OK,                  0x00, "")
        CONST_TBL_ENTRY(TB_FAIL,                0x01, "")
        CONST_TBL_ENTRY(TB_INVALID_PARAMETER,   0x02, "")
        CONST_TBL_ENTRY(TB_PROBLEMS,            0x03, "")
        CONST_TBL_ENTRY(TB_IMPOSSIBLE,          0x04, "")
        CONST_TBL_ENTRY(TB_PARTITIONED,         0x05, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    BIT_TBL_BEGIN(TB_CHANNEL, 8, BE, "", "")
        BIT_TBL_ENTRY("xxxxxxx1", TB_CHANNEL_1, "")
        BIT_TBL_ENTRY("xxxxxx1x", TB_CHANNEL_2, "")
    BIT_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    BIT_TBL_BEGIN(TB_PROCESSING_STATUS, 8, BE, "", "")
        BIT_TBL_ENTRY("xxxxxxx1", TB_DATA_PROCESSING_ERROR, "")
    BIT_TBL_END


    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_FALSE_TRUE, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_FALSE,               0x00, "")
        CONST_TBL_ENTRY(TB_TRUE,                0x01, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_ALERTS, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_ALERTS_NO,            0x00, "")
        CONST_TBL_ENTRY(TB_ALERTS_COMMON_ONLY,   0x01, "")
        CONST_TBL_ENTRY(TB_ALERTS_SPECIFIC_ONLY, 0x02, "")
        CONST_TBL_ENTRY(TB_ALERTS_ALL,           0x03, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_PORTS, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_PORT_1,               0x01, "")
        CONST_TBL_ENTRY(TB_PORT_2,               0x02, "")
        CONST_TBL_ENTRY(TB_PORT_3,               0x03, "")
        CONST_TBL_ENTRY(TB_PORT_4,               0x04, "")
        CONST_TBL_ENTRY(TB_PORT_5,               0x05, "")
        CONST_TBL_ENTRY(TB_PORT_6,               0x06, "")
        CONST_TBL_ENTRY(TB_PORT_7,               0x07, "")
        CONST_TBL_ENTRY(TB_PORT_8,               0x08, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_INDICATION_IDS, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_INDICATION_DEVICE_SENDING_SPEED, 0x00, "")
        CONST_TBL_ENTRY(TB_INDICATION_BOX_OUTPUT_SPEED,     0x01, "")
        CONST_TBL_ENTRY(TB_INDICATION_BOX_MEMORY_USAGE,     0x02, "")
        CONST_TBL_ENTRY(TB_INDICATION_USB_INPUT_SPEED,      0x03, "")
        CONST_TBL_ENTRY(TB_INDICATION_DOWLOAD_SPEED,        0x04, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_MESSAGE_LEVEL, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_MESSAGE_INFO,         0x00, "")
        CONST_TBL_ENTRY(TB_MESSAGE_WARNING,      0x01, "")
        CONST_TBL_ENTRY(TB_MESSAGE_ERROR,        0x02, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_MUSTI_PORT_EMULATION, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_PORT_MUSTI_NO,        0x00, "")
        CONST_TBL_ENTRY(TB_PORT_MUSTI_1,         0x01, "")
        CONST_TBL_ENTRY(TB_PORT_MUSTI_2,         0x02, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_XTI_PROTOCOL, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_PROTOCOL_AUTO,        0x00, "")
        CONST_TBL_ENTRY(TB_PROTOCOL_XTI_V2,      0x01, "")
        CONST_TBL_ENTRY(TB_PROTOCOL_XTI_V3,      0x02, "")
        CONST_TBL_ENTRY(TB_PROTOCOL_XTI_ST,      0x03, "")
        CONST_TBL_ENTRY(TB_PROTOCOL_STI_TI,      0x04, "")
        CONST_TBL_ENTRY(TB_PROTOCOL_STI_C,       0x05, "")
        CONST_TBL_ENTRY(TB_PROTOCOL_UNKNOWN,     0x06, "")
        CONST_TBL_ENTRY(TB_PROTOCOL_XTI_V2_AUTO, 0x81, "")
        CONST_TBL_ENTRY(TB_PROTOCOL_XTI_V3_AUTO, 0x82, "")
        CONST_TBL_ENTRY(TB_PROTOCOL_XTI_ST_AUTO, 0x83, "")
        CONST_TBL_ENTRY(TB_PROTOCOL_STI_TI_AUTO, 0x84, "")
        CONST_TBL_ENTRY(TB_PROTOCOL_STI_C_AUTO,  0x85, "")
        CONST_TBL_ENTRY(TB_PROTOCOL_UNKNOWN_AUTO,0x86, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_MASTER_ENDIANNESS, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_ENDIANNESS_LITTLE,    0x00, "")
        CONST_TBL_ENTRY(TB_ENDIANNESS_BIG,       0x01, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_EXTERNAL_CONTROL, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_EXT_CONTROL_OFF,      0x00, "")
        CONST_TBL_ENTRY(TB_EXT_CONTROL_FIDO,     0x01, "")
        CONST_TBL_ENTRY(TB_EXT_CONTROL_MUSTI,    0x02, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_SEND_FAIL_REASON, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_TARGET_PORT_NO,              0x00, "")
        CONST_TBL_ENTRY(TB_TARGET_PORT_CLOSED,          0x01, "")
        CONST_TBL_ENTRY(TB_TARGET_PORT_NOT_CONNECTED,   0x02, "")
        CONST_TBL_ENTRY(TB_DEVICE_NOT_WOKEN_UP,         0x03, "")
        CONST_TBL_ENTRY(TB_DEVICE_ILLEGAL_BIT_RATE,     0x04, "")
        CONST_TBL_ENTRY(TB_DEVICE_NOT_CONFIRM_DATA_LEN, 0x05, "")
        CONST_TBL_ENTRY(TB_DEVICE_NOT_CONFIRM_DATA,     0x06, "")
        CONST_TBL_ENTRY(TB_INTERNAL_ERROR,              0x07, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_CALIBRATION_MODE, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_CALIBRATION_OFF,             0x00, "")
        CONST_TBL_ENTRY(TB_CALIBRATION_MANUAL,          0x01, "")
        CONST_TBL_ENTRY(TB_CALIBRATION_AUTO,            0x02, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_TRACE_SIGNAL, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_TRC_DATA_0,         0x00, "")
        CONST_TBL_ENTRY(TB_TRC_DATA_1,         0x01, "")
        CONST_TBL_ENTRY(TB_TRC_DATA_2,         0x02, "")
        CONST_TBL_ENTRY(TB_TRC_DATA_3,         0x03, "")
        CONST_TBL_ENTRY(TB_TRC_CLK,            0x20, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_RESPONSE_ACTION, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_ON_CHANGES_ONLY,    0x00, "")
        CONST_TBL_ENTRY(TB_NOW,                0x01, "")
        CONST_TBL_ENTRY(TB_NOW_WITH_RESET,     0x02, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_TRACEBOXES, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_OSTRICH,            0x00, "")
        CONST_TBL_ENTRY(TB_MUSTI,              0x01, "")
        CONST_TBL_ENTRY(TB_FIDO,               0x02, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_DEVICE_CONNECTED, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_DEVICE_NO,          0x00, "")
        CONST_TBL_ENTRY(TB_DEVICE_YES,         0x01, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_EMULATE_MUSTI_PORT, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_PORT_MUSTI_NO,      0x00, "")
        CONST_TBL_ENTRY(TB_PORT_MUSTI_1,       0x01, "")
        CONST_TBL_ENTRY(TB_PORT_MUSTI_2,       0x02, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    BIT_TBL_BEGIN(TB_SIGNAL_CHARACTERISTICS, 8, BE, "", "")
        BIT_TBL_ENTRY("xxxxxxx1", TB_DATA_EYES, "")
    BIT_TBL_END


    SEQ_BEGIN(TB_PORT, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(port, "Port", TB_PORTS)
    SEQ_END

    SEQ_BEGIN(TB_MASTER_ENDIAN_MASK, DONT_CREATE_STRUCT, "", "")
        COMMENT(COMMENT_TEXT, "If a bit is '0' then the corresponding master is little endian")
        VALUE(8, BE, master_endian_mask, "Master endian mask", BIN)
    SEQ_END

    SEQ_BEGIN(TB_MASTER_FILTER_MASK, DONT_CREATE_STRUCT, "", "")
        COMMENT(COMMENT_TEXT, "If a bit is '1' then data from corresponding master is filtered out")
        VALUE(8, BE, master_filter_mask, "Master filter mask", BIN)
    SEQ_END

    SEQ_BEGIN(TB_EYES_REGION, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, edge_count, "Number of edges detected", DEC)
    SEQ_END

    SEQ_BEGIN(PORT, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(port, "Port", TB_PORTS)
    SEQ_END

    SEQ_BEGIN(RESP_TYPE, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(immediate, "Immediate", TB_FALSE_TRUE)
    SEQ_END

    SEQ_BEGIN(RESP_WHEN, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(response_when, "Response when", TB_RESPONSE_ACTION)
    SEQ_END



    /* --------------------------------------------------------------------- */
    /* TB_INIT */
    /* --------------------------------------------------------------------- */

    /* TB_ACTIVATE */

    #define TB_ACTIVATE_ALL 0xFF

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    BIT_TBL_BEGIN(TB_ACTIVATE_TYPE, 8, BE, "", "")
        BIT_TBL_ENTRY("11111111", TB_ACTIVATE_ALL, "")
    BIT_TBL_END

    SUB_MSG_BEGIN(TB_ACTIVATE_REQ, TB_INIT, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, TB_ACTIVATE_ALL)
        VALUE_CONST(type, "Type", TB_ACTIVATE_TYPE)
        VALUE(8, BE, rec_obj, "Receiver object", HEX)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ACTIVATE_RESP, TB_INIT, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_ACTIVATE_REQ,  TB_INIT,  
                 TB_ACTIVATE_RESP, TB_INIT)

    DER_CONST_TBL_BEGIN(TB_STATUS_OK, TB_STATUS, "", "")
        DER_CONST_TBL_ENTRY(TB_OK)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(TB_STATUS_OK_FAIL, TB_STATUS, "", "")
        DER_CONST_TBL_ENTRY(TB_OK)
        DER_CONST_TBL_ENTRY(TB_FAIL)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(TB_STATUS_OK_INVALID, TB_STATUS, "", "")
        DER_CONST_TBL_ENTRY(TB_OK)
        DER_CONST_TBL_ENTRY(TB_INVALID_PARAMETER)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(TB_STATUS_OK_PARTITIONED, TB_STATUS, "", "")
        DER_CONST_TBL_ENTRY(TB_OK)
        DER_CONST_TBL_ENTRY(TB_PARTITIONED)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(TB_STATUS_OK_FAIL_INVALID, TB_STATUS, "", "")
        DER_CONST_TBL_ENTRY(TB_OK)
        DER_CONST_TBL_ENTRY(TB_FAIL)
        DER_CONST_TBL_ENTRY(TB_INVALID_PARAMETER)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(TB_STATUS_OK_FAIL_INVALID_PROBLEMS, TB_STATUS, "", "")
        DER_CONST_TBL_ENTRY(TB_OK)
        DER_CONST_TBL_ENTRY(TB_FAIL)
        DER_CONST_TBL_ENTRY(TB_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(TB_PROBLEMS)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(TB_STATUS_OK_FAIL_INVALID_IMPOSSIBLE, TB_STATUS, "", "")
        DER_CONST_TBL_ENTRY(TB_OK)
        DER_CONST_TBL_ENTRY(TB_FAIL)
        DER_CONST_TBL_ENTRY(TB_INVALID_PARAMETER)
        DER_CONST_TBL_ENTRY(TB_IMPOSSIBLE)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(TB_STATUS_OK_FAIL_PROBLEMS, TB_STATUS, "", "")
        DER_CONST_TBL_ENTRY(TB_OK)
        DER_CONST_TBL_ENTRY(TB_FAIL)
        DER_CONST_TBL_ENTRY(TB_PROBLEMS)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(TB_SW_SPEED_INDICATION_IDS, TB_INDICATION_IDS, "", "")
        DER_CONST_TBL_ENTRY(TB_INDICATION_USB_INPUT_SPEED)
        DER_CONST_TBL_ENTRY(TB_INDICATION_DOWLOAD_SPEED)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(TB_BOX_SPEED_MEMORY_INDICATION_IDS, TB_INDICATION_IDS, "", "")
        DER_CONST_TBL_ENTRY(TB_INDICATION_DEVICE_SENDING_SPEED)
        DER_CONST_TBL_ENTRY(TB_INDICATION_BOX_OUTPUT_SPEED)
        DER_CONST_TBL_ENTRY(TB_INDICATION_BOX_MEMORY_USAGE)
    DER_CONST_TBL_END


    DER_CONST_TBL_BEGIN(TB_PROTOCOL_XTI_VERSION, TB_XTI_PROTOCOL, "", "")
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_AUTO)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_XTI_V2)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_XTI_V3)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_XTI_ST)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(TB_XTI_PROTOCOL_AUTO, TB_XTI_PROTOCOL, "", "")
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_XTI_V2)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_XTI_V3)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_XTI_ST)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_STI_TI)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_STI_C)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_UNKNOWN)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_XTI_V2_AUTO)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_XTI_V3_AUTO)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_XTI_ST_AUTO)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_STI_TI_AUTO)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_STI_C_AUTO)
        DER_CONST_TBL_ENTRY(TB_PROTOCOL_UNKNOWN_AUTO)
    DER_CONST_TBL_END


    COMMENT(COMMENT_TEXT, "Subblock used by TB_ALL_FREE_BOX_GET_RESP")
	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_FREE_BOX, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE(8, BE, hw_ver, "HW version", DEC)
        STRING(STRING_UNICODE, LE, serial_no, "Serial number", 17) /* 17 unicode characters, 34 bytes) */
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, connection_hostname, "Connection hostname", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
        VALUE(-32, BE, conn_port, "Connection port", DEC)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, fido_box_name, "Fido box name", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_STATE, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_CONST(connected, "Connected", TB_FALSE_TRUE)
        VALUE_CONST(open, "Open", TB_FALSE_TRUE)
        VALUE_CONST(device_connected, "Device connected", TB_DEVICE_CONNECTED)
        VALUE_CONST(emulate_musti_port, "Emulate Musti port", TB_EMULATE_MUSTI_PORT)
        VALUE(8, BE, hw_ver, "HW version", DEC)
        STRING(STRING_UNICODE, LE, serial_no, "Serial number", 17) /* 17 unicode characters, 34 bytes) */
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, remote_host_attached, "Remote host attached name", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
        VALUE(-32, LE, remote_attached_port, "Remote attached port", DEC)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, remote_host_shared, "Remote host shared name", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
        VALUE(-32, LE, remote_shared_port, "Remote shared port", DEC)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, fido_box_name, "Fido box name", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_INDICATION_VALUE, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_CONST(indication, "Indication ID", TB_BOX_SPEED_MEMORY_INDICATION_IDS)
        VALUE(32, LE, ind_val, "Indication value", DEC)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_RENAME, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(old_port, "Old port", TB_PORTS)
        VALUE_CONST(new_port, "New port", TB_PORTS)
    SB_END

    PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_LOGBOOK_MESSAGE, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(msg_level, "Message level", TB_MESSAGE_LEVEL)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, msg_text, "Message text", REF_AS_LONG_AS_POSSIBLE, ISIHDR_MARKER_ANYSIZE_WORD)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_MUSTI, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(tb_port, "Tracebox Port", TB_PORTS)
        VALUE_CONST(musti_port_emul, "Musti port emulation", TB_MUSTI_PORT_EMULATION)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_TO_FREE_BOX, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(port, "Port", TB_PORTS)
        STRING(STRING_UNICODE, LE, serial_no, "Serial number", 17) /* 17 unicode characters, 34 bytes) */
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_PROTOCOL_XTI, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_CONST(protocol, "XTI Protocol", TB_XTI_PROTOCOL)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_RESYNC_MIN_PAUSE_XTI, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_EX(32, LE, pause, "Pause", DEC, 1.0, 0.0, "microsec")
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_RESYNC_MIN_PAUSE_STI, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_EX(32, LE, pause, "Pause", DEC, 1.0, 0.0, "microsec")
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_STREAM_MAX_PAUSE_XTI, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_EX(32, LE, pause, "Pause", DEC, 1.0, 0.0, "microsec")
    SB_END


	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_STREAM_MAX_PAUSE_STI, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_EX(32, LE, pause, "Pause", DEC, 1.0, 0.0, "microsec")
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_TRANSMIT_MIN_PAUSE_STI, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_EX(32, LE, pause, "Pause", DEC, 1.0, 0.0, "microsec")
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_SEPARATE_ADSP_DSP, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_PROTOCOL, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_CONST(protocol, "XTI protocol version", TB_PROTOCOL_XTI_VERSION)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_MASTER_ENDIANNESS, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE(8, BE, interval_start, "Master interval start", DEC)
        VALUE(8, BE, interval_end, "Master interval end", DEC)
        VALUE_CONST(endianness, "Master endianness", TB_MASTER_ENDIANNESS)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_CURRENT_PROTOCOL, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_CONST(protocol, "XTI protocol version auto", TB_XTI_PROTOCOL_AUTO)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_ALL_MASTER_ENDIANNESS, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_CONST(endianness, "Master endianness", TB_MASTER_ENDIANNESS)
        SEQ_OF(master_endian_mask, "Master endian bitmask", TB_MASTER_ENDIAN_MASK, 32)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_SW_INDICATION_VALUE, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(throughput_source, "Throughput source", TB_SW_SPEED_INDICATION_IDS)
        VALUE_EX(32, LE, speed, "Speed", DEC, 1.0, 0.0, "bits per sec")
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_CONFIG, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE(8, BE, sw_version_x, "Fido sw version x", DEC)
        VALUE(8, BE, sw_version_y, "Fido sw version y", DEC)
        VALUE(8, BE, sw_version_z, "Fido sw version z", DEC)
        VALUE(8, BE, sw_version_w, "Fido sw version w", DEC)
        VALUE_CONST(autoconfig, "Automatic configuration", TB_FALSE_TRUE)
        VALUE_CONST(port_share, "Ports can be shaged", TB_FALSE_TRUE)
        VALUE_CONST(ext_control, "External control", TB_EXTERNAL_CONTROL)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, config_file, "Configuration file", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
    SB_END

/* TB_SB_COMMAND                            0x35 version 2.7 ? */
/* TB_SB_RESPONSE                           0x36 version 2.7 ? */


	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_REMOTE_RESOURCE, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE(-32, LE, conn_port, "Connection port", DEC)
        VALUE_CONST(connected, "Connected", TB_FALSE_TRUE)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, remote_host_name, "Remote resource host name", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_DATA_PROCESSING_STATE, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_CONST(status, "Status", TB_PROCESSING_STATUS)
        VALUE(32, LE, msg_code, "Message code", DEC)
        VALUE(32, LE, error_count, "Number of errors", DEC)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_STATE_MESSAGE, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE(32, LE, msg_code, "Message code", HEX) 
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, mnemonic, "State mnemonic", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, msg_text, "Processing state description", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_SENDING_FAILURE, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(fail_reason, "Fail reason", TB_SEND_FAIL_REASON)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_MARKER, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE(32, LE, marker_index, "Marker index", DEC)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_BOX_RENAME, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        STRING(STRING_UNICODE, LE, serial_no, "Serial number", 17) /* 17 unicode characters, 34 bytes) */
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, new_name, "Fido box new name", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_MASTER_FILTER, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE(8, BE, interval_start, "Master interval start", DEC)
        VALUE(8, BE, interval_end, "Master interval end", DEC)
        VALUE_CONST(filter_set, "Filter activated", TB_FALSE_TRUE)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_ALL_MASTER_FILTER, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_CONST(filtering, "Filtering state", TB_FALSE_TRUE)
        SEQ_OF(master_filter_bitmask, "Master filter bitmask", TB_MASTER_ENDIAN_MASK, 32)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_EYES_STATE, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_CONST(trc_signal, "Trace signal", TB_TRACE_SIGNAL)
        SEQ_OF(rising_edge, "Rising edge", TB_EYES_REGION, 16)
        SEQ_OF(falling_edge, "Falling edge", TB_EYES_REGION, 16)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_TIMING_CORRECTION_DATA, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        /* 8 bytes of selected sampling points */
        VALUE(8, BE, rising_trc_data_0, "Rising edge trc data 0", DEC)
        VALUE(8, BE, falling_trc_data_0, "Falling edge trc data 0", DEC)
        VALUE(8, BE, rising_trc_data_1, "Rising edge trc data 1", DEC)
        VALUE(8, BE, falling_trc_data_1, "Falling edge trc data 1", DEC)
        VALUE(8, BE, rising_trc_data_2, "Rising edge trc data 2", DEC)
        VALUE(8, BE, falling_trc_data_2, "Falling edge trc data 2", DEC)
        VALUE(8, BE, rising_trc_data_3, "Rising edge trc data 3", DEC)
        VALUE(8, BE, falling_trc_data_3, "Falling edge trc data 3", DEC)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_CALIBRATION_MODE, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_CONST(mode, "Calibration mode", TB_CALIBRATION_MODE)
    SB_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    SB_BEGIN(TB_SB_PORT_DETECT_TARGET_PRESENCE, "", "")
        REFERENCE(8, BE, sb_id, "Sub Block ID", SB_ID)
        REFERENCE(32, LE, sb_len, "Sub Block Length", SB_LENGTH)
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_CONST(detect, "Detect", TB_FALSE_TRUE)
    SB_END


    /*** Sequences containing subblocks ***/
    SEQ_BEGIN(PORT_OPEN_CLOSE, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_STATE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(ALL_PORT_GET, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_STATE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(ALL_PORTS_PARAMETERS, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_PROTOCOL_XTI)
            SB_LST_ENTRY(TB_SB_PORT_RESYNC_MIN_PAUSE_XTI)
            SB_LST_ENTRY(TB_SB_PORT_STREAM_MAX_PAUSE_XTI)
            SB_LST_ENTRY(TB_SB_PORT_MASTER_ENDIANNESS)
            SB_LST_ENTRY(TB_SB_PORT_ALL_MASTER_ENDIANNESS)
            SB_LST_ENTRY(TB_SB_PORT_PROTOCOL)
            SB_LST_ENTRY(TB_SB_PORT_MASTER_FILTER)
            SB_LST_ENTRY(TB_SB_PORT_ALL_MASTER_FILTER)
            SB_LST_ENTRY(TB_SB_PORT_TIMING_CORRECTION_DATA)
            SB_LST_ENTRY(TB_SB_PORT_CALIBRATION_MODE)
            SB_LST_ENTRY(TB_SB_PORT_DETECT_TARGET_PRESENCE)
            SB_LST_ENTRY(TB_SB_PORT_RESYNC_MIN_PAUSE_STI)
            SB_LST_ENTRY(TB_SB_PORT_STREAM_MAX_PAUSE_STI)
            SB_LST_ENTRY(TB_SB_PORT_TRANSMIT_MIN_PAUSE_STI)
            SB_LST_ENTRY(TB_SB_PORT_SEPARATE_ADSP_DSP)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(PORT_CURRENT_PROTOCOL, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_CURRENT_PROTOCOL)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(PORT_MARKER, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_MARKER)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(TEXTUAL_CMD, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(TEXTUAL_CMDS, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(DATA_TO_DEV_RESP, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(PORT_OR_BOX_RENAME, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_RENAME)
            SB_LST_ENTRY(TB_SB_BOX_RENAME)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(PORT_REMOVE, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_STATE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(PORT_INSERT, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_STATE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(PORT_DISCONNECT, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_STATE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(PORT_CONNECT, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_STATE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(PORT_WINK_LED, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(BOX_WINK_LED, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(ALL_FREE_BOX_GET, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_FREE_BOX)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(EMULATE_MUSTI, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_STATE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(CONFIG_PARAMETERS_SET, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_CONFIG)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(REMOTE_RES_GET, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_REMOTE_RESOURCE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(REMOTE_RES_CONNECT, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_REMOTE_RESOURCE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(REMOTE_RES_DISCONNECT, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_REMOTE_RESOURCE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END

    SEQ_BEGIN(REMOTE_RES_REMOVE, CREATE_STRUCT, "", "")
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_REMOTE_RESOURCE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SEQ_END



    /* TB_ALLOW_BAN_LOGBOOK - Fido */
    SUB_MSG_BEGIN(TB_ALLOW_BAN_LOGBOOK_REQ, TB_INIT, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(mode, "Mode", TB_FALSE_TRUE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALLOW_BAN_LOGBOOK_RESP, TB_INIT, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_INVALID)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_ALLOW_BAN_LOGBOOK_REQ,  TB_INIT,  
                 TB_ALLOW_BAN_LOGBOOK_RESP, TB_INIT)

    /* TB_ALLOW_BAN_ALERTS - Fido */
    SUB_MSG_BEGIN(TB_ALLOW_BAN_ALERTS_REQ, TB_INIT, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(type, "Type", TB_ALERTS)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALLOW_BAN_ALERTS_RESP, TB_INIT, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_INVALID)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_ALLOW_BAN_ALERTS_REQ,  TB_INIT,  
                 TB_ALLOW_BAN_ALERTS_RESP, TB_INIT)

    /* TB_ALLOW_CONTROL_PANEL - Fido */
    SUB_MSG_BEGIN(TB_ALLOW_CONTROL_PANEL_REQ, TB_INIT, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(mode, "Mode", TB_FALSE_TRUE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALLOW_CONTROL_PANEL_RESP, TB_INIT, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_INVALID)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_ALLOW_CONTROL_PANEL_REQ,  TB_INIT,  
                 TB_ALLOW_CONTROL_PANEL_RESP, TB_INIT)

    /* TB_STATE_MESSAGES_GET - Fido */
#define TB_ALL_MESSAGES  0x00

    SUB_MSG_BEGIN(TB_STATE_MESSAGES_GET_REQ, TB_INIT, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, TB_ALL_MESSAGES)
        VALUE(32, LE, msg_code, "Message code", HEX)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_STATE_MESSAGES_GET_RESP, TB_INIT, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_INVALID)
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_STATE_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(TB_STATE_MESSAGES_GET_REQ,  TB_INIT,  
                 TB_STATE_MESSAGES_GET_RESP, TB_INIT)

    /* TB_TERMINATE - Fido */
    SUB_MSG_BEGIN(TB_TERMINATE_REQ, TB_INIT, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_TERMINATE_RESP, TB_INIT, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_TERMINATE_REQ,  TB_INIT,  
                 TB_TERMINATE_RESP, TB_INIT)

    /* TB_DATA_CHANNEL_RESERVE - Fido */
    SUB_MSG_BEGIN(TB_DATA_CHANNEL_RESERVE_REQ, TB_INIT, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        COMMENT(COMMENT_TEXT, "CLIENT ID IDENTIFYING THIS RESERVATION")
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, client_id, "Client ID", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_DATA_CHANNEL_RESERVE_RESP, TB_INIT, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_DATA_CHANNEL_RESERVE_REQ,  TB_INIT,  
                 TB_DATA_CHANNEL_RESERVE_RESP, TB_INIT)

    /* TB_DATA_CHANNEL_OPEN_CLOSE - Fido */
    SUB_MSG_BEGIN(TB_DATA_CHANNEL_OPEN_CLOSE_REQ, TB_INIT, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(close_open, "Close or open", TB_FALSE_TRUE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_DATA_CHANNEL_OPEN_CLOSE_RESP, TB_INIT, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_DATA_CHANNEL_OPEN_CLOSE_REQ,  TB_INIT,  
                 TB_DATA_CHANNEL_OPEN_CLOSE_RESP, TB_INIT)


    /* --------------------------------------------------------------------- */
    /* TB_COMMAND */
    /* --------------------------------------------------------------------- */

/*
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    BIT_TBL_BEGIN(TB_RESET_TYPE, 8, BE, "", "")
    BIT_TBL_END
*/

    SUB_MSG_BEGIN(TB_RESET_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        PROPERTY_VALUE(PROPERTY_ITEM_DEFAULT_VALUE, 0)
        COMMENT(COMMENT_TEXT, "No types supported yet...")
        VALUE(8, BE, type, "Type", HEX)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_RESET_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_RESET_REQ,  TB_COMMAND,
                 TB_RESET_RESP, TB_COMMAND)

    /* TB_TIME_SET - Fido */
    SUB_MSG_BEGIN(TB_TIME_SET_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        COMMENT(COMMENT_TEXT, "Number of seconds elapsed since 01-Jan-1980 00:00:00 GMT")
        VALUE(32, LE, timestamp, "Timestamp", HEX)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_TIME_SET_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_INVALID)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_TIME_SET_REQ,  TB_COMMAND,
                 TB_TIME_SET_RESP, TB_COMMAND)

    /* TB_PORT_OPEN_CLOSE - Fido */

    SUB_MSG_BEGIN(TB_PORT_OPEN_CLOSE_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(close_open, "Close or open", TB_FALSE_TRUE)
        REFERENCE(8, BE, no_of_ports, "No of ports", N)
        SEQ_OF_REF(ports, "Ports", TB_PORT, N, ISIHDR_MARKER_ANYSIZE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_PORT_OPEN_CLOSE_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_PROBLEMS)
        SEQ_OF_REF(ports, "Port list", PORT_OPEN_CLOSE, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_PORT_OPEN_CLOSE_REQ,  TB_COMMAND,
                 TB_PORT_OPEN_CLOSE_RESP, TB_COMMAND)

    /* TB_ALL_PORT_OPEN_CLOSE - Fido */
    SUB_MSG_BEGIN(TB_ALL_PORT_OPEN_CLOSE_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(close_open, "Close or open", TB_FALSE_TRUE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALL_PORT_OPEN_CLOSE_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_PROBLEMS)
        SEQ_OF_REF(ports, "Port list", PORT_OPEN_CLOSE, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_ALL_PORT_OPEN_CLOSE_REQ,  TB_COMMAND,
                 TB_ALL_PORT_OPEN_CLOSE_RESP, TB_COMMAND)

    /* TB_PORT_PARAMETERS_SET - Fido */
    SUB_MSG_BEGIN(TB_PORT_PARAMETERS_SET_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_PROTOCOL_XTI)
            SB_LST_ENTRY(TB_SB_PORT_RESYNC_MIN_PAUSE_XTI)
            SB_LST_ENTRY(TB_SB_PORT_STREAM_MAX_PAUSE_XTI)
            SB_LST_ENTRY(TB_SB_PORT_MASTER_ENDIANNESS)
            SB_LST_ENTRY(TB_SB_PORT_PROTOCOL)
            SB_LST_ENTRY(TB_SB_PORT_ALL_MASTER_ENDIANNESS)
            SB_LST_ENTRY(TB_SB_PORT_MASTER_FILTER)
            SB_LST_ENTRY(TB_SB_PORT_ALL_MASTER_FILTER)
            SB_LST_ENTRY(TB_SB_PORT_TIMING_CORRECTION_DATA)
            SB_LST_ENTRY(TB_SB_PORT_CALIBRATION_MODE)
            SB_LST_ENTRY(TB_SB_PORT_DETECT_TARGET_PRESENCE)
            SB_LST_ENTRY(TB_SB_PORT_RESYNC_MIN_PAUSE_STI)
            SB_LST_ENTRY(TB_SB_PORT_STREAM_MAX_PAUSE_STI)
            SB_LST_ENTRY(TB_SB_PORT_TRANSMIT_MIN_PAUSE_STI)
            SB_LST_ENTRY(TB_SB_PORT_SEPARATE_ADSP_DSP)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_PORT_PARAMETERS_SET_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_PROBLEMS)
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_PROTOCOL_XTI)
            SB_LST_ENTRY(TB_SB_PORT_RESYNC_MIN_PAUSE_XTI)
            SB_LST_ENTRY(TB_SB_PORT_STREAM_MAX_PAUSE_XTI)
            SB_LST_ENTRY(TB_SB_PORT_MASTER_ENDIANNESS)
            SB_LST_ENTRY(TB_SB_PORT_PROTOCOL)
            SB_LST_ENTRY(TB_SB_PORT_ALL_MASTER_ENDIANNESS)
            SB_LST_ENTRY(TB_SB_PORT_MASTER_FILTER)
            SB_LST_ENTRY(TB_SB_PORT_ALL_MASTER_FILTER)
            SB_LST_ENTRY(TB_SB_PORT_TIMING_CORRECTION_DATA)
            SB_LST_ENTRY(TB_SB_PORT_CALIBRATION_MODE)
            SB_LST_ENTRY(TB_SB_PORT_DETECT_TARGET_PRESENCE)
            SB_LST_ENTRY(TB_SB_PORT_RESYNC_MIN_PAUSE_STI)
            SB_LST_ENTRY(TB_SB_PORT_STREAM_MAX_PAUSE_STI)
            SB_LST_ENTRY(TB_SB_PORT_TRANSMIT_MIN_PAUSE_STI)
            SB_LST_ENTRY(TB_SB_PORT_SEPARATE_ADSP_DSP)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(TB_PORT_PARAMETERS_SET_REQ,  TB_COMMAND,
                 TB_PORT_PARAMETERS_SET_RESP, TB_COMMAND)

    /* TB_ALL_PORT_PARAMETERS_GET - Fido */
    SUB_MSG_BEGIN(TB_ALL_PORT_PARAMETERS_GET_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALL_PORT_PARAMETERS_GET_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_PARTITIONED)
        SEQ_OF_REF(port_params, "Port parameters", ALL_PORTS_PARAMETERS, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_ALL_PORT_PARAMETERS_GET_REQ,  TB_COMMAND,
                 TB_ALL_PORT_PARAMETERS_GET_RESP, TB_COMMAND)

    /* TB_ALL_PORT_CURRENT_PROTOCOL_GET - Fido */
    SUB_MSG_BEGIN(TB_ALL_PORT_CURRENT_PROTOCOL_GET_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALL_PORT_CURRENT_PROTOCOL_GET_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK)
        SEQ_OF_REF(port_protocol, "Port protocol", PORT_CURRENT_PROTOCOL, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_ALL_PORT_CURRENT_PROTOCOL_GET_REQ,  TB_COMMAND,
                 TB_ALL_PORT_CURRENT_PROTOCOL_GET_RESP, TB_COMMAND)

    /* TB_ALL_PORT_MARKER_SET - Fido */
    SUB_MSG_BEGIN(TB_ALL_PORT_MARKER_SET_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, LE, marker, "Marker text", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALL_PORT_MARKER_SET_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID)
        SEQ_OF_REF(port_marker, "Port marker", PORT_MARKER, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_ALL_PORT_MARKER_SET_REQ,  TB_COMMAND,
                 TB_ALL_PORT_MARKER_SET_RESP, TB_COMMAND)

    /* TB_TEXTUAL_COMMAND_SET - Fido */
    SUB_MSG_BEGIN(TB_TEXTUAL_COMMAND_SET_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, cmd_text, "Command text", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_TEXTUAL_COMMAND_SET_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID)
        SEQ_OF_REF(textual_cmd, "Textual command", TEXTUAL_CMD, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_TEXTUAL_COMMAND_SET_REQ,  TB_COMMAND,
                 TB_TEXTUAL_COMMAND_SET_RESP, TB_COMMAND)

    /* TB_TEXTUAL_COMMANDS_FILE_SET - Fido */
    SUB_MSG_BEGIN(TB_TEXTUAL_COMMANDS_FILE_SET_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, LE, cmd_file_text, "Command file text", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_MARKER_ANYSIZE_WORD)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_TEXTUAL_COMMANDS_FILE_SET_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_PROBLEMS)
        SEQ_OF_REF(textual_cmds, "Textual commands", TEXTUAL_CMDS, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_TEXTUAL_COMMANDS_FILE_SET_REQ,  TB_COMMAND,
                 TB_TEXTUAL_COMMANDS_FILE_SET_RESP, TB_COMMAND)

    /* TB_SEND_TO_DEVICE - Fido */
    SUB_MSG_BEGIN(TB_SEND_TO_DEVICE_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(port, "Port", TB_PORTS)
        SEQ_OF_REF(data, "Data", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_ANYSIZE_BYTE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_SEND_TO_DEVICE_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID)
        SEQ_OF_REF(data_to_dev_resp, "Data to device resp", DATA_TO_DEV_RESP, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_SEND_TO_DEVICE_REQ,  TB_COMMAND,
                 TB_SEND_TO_DEVICE_RESP, TB_COMMAND)

    /* TB_DATA_TARGET_SET - Fido */
    SUB_MSG_BEGIN(TB_DATA_TARGET_SET_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(port, "Port", TB_PORTS)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_DATA_TARGET_SET_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_DATA_TARGET_SET_REQ,  TB_COMMAND,
                 TB_DATA_TARGET_SET_RESP, TB_COMMAND)



    /* --------------------------------------------------------------------- */
    /* TB_INFO */
    /* --------------------------------------------------------------------- */

    SUB_MSG_BEGIN(TB_VERSION_GET_REQ, TB_INFO, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_VERSION_GET_RESP, TB_INFO, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE(8, BE, major, "Major version", DEC)
        VALUE(8, BE, minor, "Minor version", DEC)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_VERSION_GET_REQ,  TB_INFO,
                 TB_VERSION_GET_RESP, TB_INFO)

    /* TB_PORT_INDICATION_GET - Fido */
    SUB_MSG_BEGIN(TB_PORT_INDICATION_GET_REQ, TB_INFO, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(immediate_resp, "Immediate response", TB_FALSE_TRUE)
        REFERENCE(8, BE, PORT_count, "No of ports", N)
        SEQ_OF_REF(port_list, "List of ports", PORT, N, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_PORT_INDICATION_GET_RESP, TB_INFO, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_INVALID)
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_INDICATION_VALUE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(TB_PORT_INDICATION_GET_REQ,  TB_INFO,
                 TB_PORT_INDICATION_GET_RESP, TB_INFO)

    /* TB_SW_INDICATION_GET - Fido */
    SUB_MSG_BEGIN(TB_SW_INDICATION_GET_REQ, TB_INFO, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(immediate_resp, "Immediate response", TB_FALSE_TRUE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_SW_INDICATION_GET_RESP, TB_INFO, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK)
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_INDICATION_VALUE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(TB_SW_INDICATION_GET_REQ,  TB_INFO,
                 TB_SW_INDICATION_GET_RESP, TB_INFO)

    /* TB_DATA_PROCESSING_STATE_GET - Fido */
    SUB_MSG_BEGIN(TB_DATA_PROCESSING_STATE_GET_REQ, TB_INFO, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(immediate_resp, "Immediate response", TB_FALSE_TRUE)
        REFERENCE(8, BE, PORT_count, "No of ports", N)
        SEQ_OF_REF(port_list, "List of ports", PORT, N, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_DATA_PROCESSING_STATE_GET_RESP, TB_INFO, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK)
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_DATA_PROCESSING_STATE)
            SB_LST_ENTRY(TB_SB_STATE_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(TB_DATA_PROCESSING_STATE_GET_REQ,  TB_INFO,
                 TB_DATA_PROCESSING_STATE_GET_RESP, TB_INFO)

    /* TB_SIGNAL_CHARACTERISTICS_GET - Fido */
    SUB_MSG_BEGIN(TB_SIGNAL_CHARACTERISTICS_GET_REQ, TB_INFO, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(response_when, "Response when", TB_RESPONSE_ACTION)
        VALUE_CONST(characteristics, "Signal characteristics", TB_SIGNAL_CHARACTERISTICS)
        REFERENCE(8, BE, PORT_count, "No of ports", N)
        SEQ_OF_REF(port_list, "List of ports", PORT, N, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_SIGNAL_CHARACTERISTICS_GET_RESP, TB_INFO, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_INVALID)
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_EYES_STATE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(TB_SIGNAL_CHARACTERISTICS_GET_REQ,  TB_INFO,
                 TB_SIGNAL_CHARACTERISTICS_GET_RESP, TB_INFO)



             

    /* TB_THROUGHPUT_QUERY */

    SUB_MSG_BEGIN(TB_THROUGHPUT_QUERY_REQ, TB_INFO, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_THROUGHPUT_QUERY_RESP, TB_INFO, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_EX(32, LE, throughput1, "Throughput channel 1", DEC, 1.0, 0.0, "bytes/s")
        VALUE_EX(32, LE, throughput2, "Throughput channel 2", DEC, 1.0, 0.0, "bytes/s")
    SUB_MSG_END

    SUB_MSG_PAIR(TB_THROUGHPUT_QUERY_REQ,  TB_INFO,
                 TB_THROUGHPUT_QUERY_RESP, TB_INFO)

    /* --------------------------------------------------------------------- */
    /* TB_COMMAND */
    /* --------------------------------------------------------------------- */

    /* TB_PERFORMANCE_STATUS */

#define TB_STOP_NOTIFICATIONS 0x0000

    SUB_MSG_BEGIN(TB_PERFORMANCE_STATUS_REQ, TB_COMMAND, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        FILLER(FILLER_FIXED, 8)
        PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, TB_STOP_NOTIFICATIONS)
        VALUE_EX(16, BE, interval, "Time interval", DEC, 1.0, 0.0, "s")
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_PERFORMANCE_STATUS_RESP, TB_COMMAND, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
    SUB_MSG_END

    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_PARAGRAPH, "This notification is sent when ")
    COMMENT_LINK(LINK_MESSAGE, "TB_COMMAND", "TB_PERFORMANCE_STATUS_REQ", "000.000")
    COMMENT(COMMENT_PARAGRAPH, " is received with a valid time interval.")
    COMMENT(COMMENT_PARAGRAPH, "To stop receiving notifications again, send ")
    COMMENT_LINK(LINK_MESSAGE, "TB_COMMAND", "TB_PERFORMANCE_STATUS_REQ", "000.000")
    COMMENT(COMMENT_PARAGRAPH, " with time interval = TB_STOP_NOTIFICATIONS.")
    SUB_MSG_BEGIN(TB_PERFORMANCE_STATUS_NTF, TB_COMMAND, MESSAGE_NTF, "", "")
        COMMON_SUB_MSG_HDR
        FILLER(FILLER_FIXED, 8)
        VALUE_EX(32, BE, throughput1, "Throughput channel 1", DEC, 1.0, 0.0, "bytes/s")
        VALUE_EX(32, BE, throughput2, "Throughput channel 2", DEC, 1.0, 0.0, "bytes/s")
    SUB_MSG_END

    SUB_MSG_PAIR(TB_PERFORMANCE_STATUS_REQ,  TB_COMMAND,
                 TB_PERFORMANCE_STATUS_RESP, TB_COMMAND)


    /* --------------------------------------------------------------------- */
    /* TB_CONFIGURATION */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_PHONE_INTERVIEW_MODE, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_MODE_BANNED,         0x00, "")
        CONST_TBL_ENTRY(TB_MODE_COMPULSORY,     0x01, "")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(TB_STI_PROTOCOL, 8, BE, "", "")
        CONST_TBL_ENTRY(TB_STI_PROTOCOL_C,      0x00, "")
        CONST_TBL_ENTRY(TB_STI_PROTOCOL_TI,     0x01, "")
    CONST_TBL_END

    /* TB_PHONE_INTERVIEW_MODE_SET */

    SUB_MSG_BEGIN(TB_PHONE_INTERVIEW_MODE_SET_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(channel, "Channel", TB_CHANNEL)
        VALUE_CONST(mode, "Mode", TB_PHONE_INTERVIEW_MODE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_PHONE_INTERVIEW_MODE_SET_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_PHONE_INTERVIEW_MODE_SET_REQ,  TB_CONFIGURATION,
                 TB_PHONE_INTERVIEW_MODE_SET_RESP, TB_CONFIGURATION)

    /* TB_PHONE_INTERVIEW_MODE_GET */

    SUB_MSG_BEGIN(TB_PHONE_INTERVIEW_MODE_GET_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(channel, "Channel", TB_CHANNEL)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_PHONE_INTERVIEW_MODE_GET_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(mode, "Mode", TB_PHONE_INTERVIEW_MODE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_PHONE_INTERVIEW_MODE_GET_REQ,  TB_CONFIGURATION,
                 TB_PHONE_INTERVIEW_MODE_GET_RESP, TB_CONFIGURATION)

    /* TB_STI_PROTOCOL_SET */

    SUB_MSG_BEGIN(TB_STI_PROTOCOL_SET_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(sti_protocol, "STI protocol", TB_STI_PROTOCOL)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_STI_PROTOCOL_SET_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_STI_PROTOCOL_SET_REQ,  TB_CONFIGURATION,
                 TB_STI_PROTOCOL_SET_RESP, TB_CONFIGURATION)

    /* TB_STI_PROTOCOL_GET */

    SUB_MSG_BEGIN(TB_STI_PROTOCOL_GET_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_STI_PROTOCOL_GET_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
        VALUE_CONST(sti_protocol, "STI protocol", TB_STI_PROTOCOL)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_STI_PROTOCOL_GET_REQ,  TB_CONFIGURATION,
                 TB_STI_PROTOCOL_GET_RESP, TB_CONFIGURATION)

    /* TB_CONFIG_GET - Fido */
    SUB_MSG_BEGIN(TB_CONFIG_GET_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_CONFIG_GET_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK)
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_CONFIG)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(TB_CONFIG_GET_REQ,  TB_CONFIGURATION,
                 TB_CONFIG_GET_RESP, TB_CONFIGURATION)

 
    /* TB_ALL_PORT_GET - Fido */
    SUB_MSG_BEGIN(TB_ALL_PORT_GET_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALL_PORT_GET_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK)
        SEQ_OF_REF(ports, "Port list", ALL_PORT_GET, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_ALL_PORT_GET_REQ,  TB_CONFIGURATION,
                 TB_ALL_PORT_GET_RESP, TB_CONFIGURATION)

    /* TB_PORT_OR_BOX_RENAME - Fido */
    SUB_MSG_BEGIN(TB_PORT_OR_BOX_RENAME_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_RENAME)
            SB_LST_ENTRY(TB_SB_BOX_RENAME)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_PORT_OR_BOX_RENAME_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_PROBLEMS)
        SEQ_OF_REF(ports, "Ports", PORT_OR_BOX_RENAME, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_PORT_OR_BOX_RENAME_REQ,  TB_CONFIGURATION,
                 TB_PORT_OR_BOX_RENAME_RESP, TB_CONFIGURATION)

    /* TB_PORT_REMOVE - Fido */
    SUB_MSG_BEGIN(TB_PORT_REMOVE_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, PORT_count, "No of ports", N)
        SEQ_OF_REF(port_list, "List of ports", PORT, N, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_PORT_REMOVE_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_PROBLEMS)
        SEQ_OF_REF(ports, "Ports", PORT_REMOVE, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_PORT_REMOVE_REQ,  TB_CONFIGURATION,
                 TB_PORT_REMOVE_RESP, TB_CONFIGURATION)

    /* TB_PORT_INSERT - Fido */
    SUB_MSG_BEGIN(TB_PORT_INSERT_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, PORT_count, "No of ports", N)
        SEQ_OF_REF(port_list, "List of ports", PORT, N, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_PORT_INSERT_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_PROBLEMS)
        SEQ_OF_REF(ports, "Ports", PORT_INSERT, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_PORT_INSERT_REQ,  TB_CONFIGURATION,
                 TB_PORT_INSERT_RESP, TB_CONFIGURATION)

    /* TB_PORT_DISCONNECT - Fido */
    SUB_MSG_BEGIN(TB_PORT_DISCONNECT_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, PORT_count, "No of ports", N)
        SEQ_OF_REF(port_list, "List of ports", PORT, N, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_PORT_DISCONNECT_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_PROBLEMS)
        SEQ_OF_REF(ports, "Ports", PORT_DISCONNECT, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_PORT_DISCONNECT_REQ,  TB_CONFIGURATION,
                 TB_PORT_DISCONNECT_RESP, TB_CONFIGURATION)

    /* TB_ALL_PORT_DISCONNECT - Fido */
    SUB_MSG_BEGIN(TB_ALL_PORT_DISCONNECT_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALL_PORT_DISCONNECT_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_PROBLEMS)
        SEQ_OF_REF(ports, "Ports", PORT_DISCONNECT, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_ALL_PORT_DISCONNECT_REQ,  TB_CONFIGURATION,
                 TB_ALL_PORT_DISCONNECT_RESP, TB_CONFIGURATION)

    /* TB_PORT_CONNECT - Fido */
    SUB_MSG_BEGIN(TB_PORT_CONNECT_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_TO_FREE_BOX)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_PORT_CONNECT_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_PROBLEMS)
        SEQ_OF_REF(ports, "Ports", PORT_CONNECT, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_PORT_CONNECT_REQ,  TB_CONFIGURATION,
                 TB_PORT_CONNECT_RESP, TB_CONFIGURATION)

    /* TB_PORT_WINK_LED - Fido */
    SUB_MSG_BEGIN(TB_PORT_WINK_LED_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(port, "Port", TB_PORTS)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_PORT_WINK_LED_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_IMPOSSIBLE)
        SEQ_OF_REF(port, "Port", PORT_WINK_LED, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_PORT_WINK_LED_REQ,  TB_CONFIGURATION,
                 TB_PORT_WINK_LED_RESP, TB_CONFIGURATION)

    /* TB_ALL_FREE_BOX_GET - Fido */
    SUB_MSG_BEGIN(TB_ALL_FREE_BOX_GET_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALL_FREE_BOX_GET_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK)
        SEQ_OF_REF(free_box, "Free box", ALL_FREE_BOX_GET, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_ALL_FREE_BOX_GET_REQ,  TB_CONFIGURATION,
                 TB_ALL_FREE_BOX_GET_RESP, TB_CONFIGURATION)

    /* TB_BOX_WINK_LED - Fido */
    SUB_MSG_BEGIN(TB_BOX_WINK_LED_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        STRING(STRING_UNICODE, BE, serial_no, "Serial number", 17) /* 17 unicode characters, 34 bytes) */
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_BOX_WINK_LED_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_IMPOSSIBLE)
        SEQ_OF_REF(leds, "Box leds", BOX_WINK_LED, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_BOX_WINK_LED_REQ,  TB_CONFIGURATION,
                 TB_BOX_WINK_LED_RESP, TB_CONFIGURATION)

    /* TB_EMULATE_MUSTI - Fido */
    SUB_MSG_BEGIN(TB_EMULATE_MUSTI_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_PORT_MUSTI)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_EMULATE_MUSTI_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_PROBLEMS)
        SEQ_OF_REF(ports, "Ports", EMULATE_MUSTI, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_EMULATE_MUSTI_REQ,  TB_CONFIGURATION,
                 TB_EMULATE_MUSTI_RESP, TB_CONFIGURATION)

    /* TB_CONFIG_PARAMETERS_SET - Fido */
    SUB_MSG_BEGIN(TB_CONFIG_PARAMETERS_SET_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(auto_conf, "Auto configuration mode", TB_FALSE_TRUE)
        VALUE_CONST(port_share, "Port sharing", TB_FALSE_TRUE)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_CONFIG_PARAMETERS_SET_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID)
        SEQ_OF_REF(config_param, "Config param", CONFIG_PARAMETERS_SET, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_CONFIG_PARAMETERS_SET_REQ,  TB_CONFIGURATION,
                 TB_CONFIG_PARAMETERS_SET_RESP, TB_CONFIGURATION)

    /* TB_REMOTE_RES_GET - Fido */
    SUB_MSG_BEGIN(TB_REMOTE_RES_GET_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_REMOTE_RES_GET_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK)
        SEQ_OF_REF(remote_res, "Remote res", REMOTE_RES_GET, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_REMOTE_RES_GET_REQ,  TB_CONFIGURATION,
                 TB_REMOTE_RES_GET_RESP, TB_CONFIGURATION)

    /* TB_REMOTE_RES_CONNECT - Fido */
    SUB_MSG_BEGIN(TB_REMOTE_RES_CONNECT_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_REMOTE_RESOURCE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_REMOTE_RES_CONNECT_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_PROBLEMS)
        SEQ_OF_REF(remote_res, "Remote res connect", REMOTE_RES_CONNECT, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_REMOTE_RES_CONNECT_REQ,  TB_CONFIGURATION,
                 TB_REMOTE_RES_CONNECT_RESP, TB_CONFIGURATION)

    /* TB_REMOTE_RES_DISCONNECT - Fido */
    SUB_MSG_BEGIN(TB_REMOTE_RES_DISCONNECT_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_REMOTE_RESOURCE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_REMOTE_RES_DISCONNECT_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_PROBLEMS)
        SEQ_OF_REF(remote_res, "Remote res disconnect", REMOTE_RES_DISCONNECT, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_REMOTE_RES_DISCONNECT_REQ,  TB_CONFIGURATION,
                 TB_REMOTE_RES_DISCONNECT_RESP, TB_CONFIGURATION)

    /* TB_REMOTE_RES_REMOVE - Fido */
    SUB_MSG_BEGIN(TB_REMOTE_RES_REMOVE_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, sb_count, "No of subblocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub blocks", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(TB_SB_REMOTE_RESOURCE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_REMOTE_RES_REMOVE_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL_INVALID_PROBLEMS)
        SEQ_OF_REF(remote_res, "Remote res remove", REMOTE_RES_REMOVE, REF_OPTIONAL, ISIHDR_DONT_GENERATE)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_REMOTE_RES_REMOVE_REQ,  TB_CONFIGURATION,
                 TB_REMOTE_RES_REMOVE_RESP, TB_CONFIGURATION)

    /* TB_SW_VERSION_GET - Fido */
    SUB_MSG_BEGIN(TB_SW_VERSION_GET_REQ, TB_CONFIGURATION, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_SW_VERSION_GET_RESP, TB_CONFIGURATION, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK)
        VALUE(8, BE, sw_version_x, "SW version x", DEC)
        VALUE(8, BE, sw_version_y, "SW version y", DEC)
        VALUE(8, BE, sw_version_z, "SW version z", DEC)
        VALUE(8, BE, sw_version_w, "SW version w", DEC)
        VALUE_CONST(tracebox, "Tracebox identifier", TB_TRACEBOXES)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_SW_VERSION_GET_REQ,  TB_CONFIGURATION,
                 TB_SW_VERSION_GET_RESP, TB_CONFIGURATION)




                 

    /* --------------------------------------------------------------------- */
    /* TB_FILTER */
    /* --------------------------------------------------------------------- */

    BIT_TBL_BEGIN(TB_FILTER_GENERAL, 8, BE, "", "")
        BIT_TBL_ENTRY("xxxxxxx1", TB_FILTER_INDICATIONS, "")
        BIT_TBL_ENTRY("xxxxxx1x", TB_FILTER_MARKERS, "")
    BIT_TBL_END

    BIT_TBL_BEGIN(TB_FILTER_GROUPS, 8, BE, "", "")
        BIT_TBL_ENTRY("xxxxxxx1", TB_FILTER_HW_TRACES, "")
        BIT_TBL_ENTRY("xxxxxx1x", TB_FILTER_MCU_TRACES, "")
        BIT_TBL_ENTRY("xxxxx1xx", TB_FILTER_DSP_TRACES, "")
        BIT_TBL_ENTRY("xxxx1xxx", TB_FILTER_SYMBIAN_TRACES, "")
    BIT_TBL_END

    SEQ_BEGIN(TB_MASTER, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(master, "Master", XTI_MASTER_ID)
    SEQ_END

	PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    PROPERTY(PROPERTY_SB_LENGTH_MISSING)
    SB_BEGIN(TB_SB_FILTER_GENERAL, "", "")
		REFERENCE(8, BE, sb_id, "Subblock ID", SB_ID)
        VALUE_CONST(filter, "General filter", TB_FILTER_GENERAL)
    SB_END

    PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    PROPERTY(PROPERTY_SB_LENGTH_MISSING)
    SB_BEGIN(TB_SB_FILTER_CHANNEL_GROUPS, "", "")
		REFERENCE(8, BE, sb_id, "Subblock ID", SB_ID)
        VALUE_CONST(channel, "Channel", TB_CHANNEL)
        VALUE_CONST(filter, "Filter", TB_FILTER_GROUPS)
    SB_END

    PROPERTY(PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4)
    PROPERTY(PROPERTY_SB_LENGTH_MISSING)
    SB_BEGIN(TB_SB_FILTER_CHANNEL_MASTERS, "", "")
		REFERENCE(8, BE, sb_id, "Subblock ID", SB_ID)
        VALUE_CONST(channel, "Channel", TB_CHANNEL)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 250)
        REFERENCE(8, BE, n_masters, "Number of masters", N)
        SEQ_OF_REF(master, "Master", TB_MASTER, N, ISIHDR_DONT_GENERATE)
    SB_END
    
    /* TB_FILTER_CLEAR */

    SUB_MSG_BEGIN(TB_FILTER_CLEAR_REQ, TB_FILTER, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_FILTER_GENERAL)
            SB_LST_ENTRY(TB_SB_FILTER_CHANNEL_GROUPS)
            SB_LST_ENTRY(TB_SB_FILTER_CHANNEL_MASTERS)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_FILTER_CLEAR_RESP, TB_FILTER, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_FILTER_CLEAR_REQ, TB_FILTER,
                 TB_FILTER_CLEAR_RESP, TB_FILTER)

    /* TB_FILTER_SET */

    SUB_MSG_BEGIN(TB_FILTER_SET_REQ, TB_FILTER, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_FILTER_GENERAL)
            SB_LST_ENTRY(TB_SB_FILTER_CHANNEL_GROUPS)
            SB_LST_ENTRY(TB_SB_FILTER_CHANNEL_MASTERS)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_FILTER_SET_RESP, TB_FILTER, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_FILTER_SET_REQ, TB_FILTER,
                 TB_FILTER_SET_RESP, TB_FILTER)

    /* TB_FILTER_GET */

    SUB_MSG_BEGIN(TB_FILTER_GET_REQ, TB_FILTER, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_FILTER_GET_RESP, TB_FILTER, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_FILTER_GENERAL)
            SB_LST_ENTRY(TB_SB_FILTER_CHANNEL_GROUPS)
            SB_LST_ENTRY(TB_SB_FILTER_CHANNEL_MASTERS)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(TB_FILTER_GET_REQ, TB_FILTER,
                 TB_FILTER_GET_RESP, TB_FILTER)

    /* TB_FILTER_RESET */

    SUB_MSG_BEGIN(TB_FILTER_RESET_REQ, TB_FILTER, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_FILTER_RESET_RESP, TB_FILTER, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_FILTER_RESET_REQ, TB_FILTER,
                 TB_FILTER_RESET_RESP, TB_FILTER)


    /* --------------------------------------------------------------------- */
    /* TB_CONNECT */
    /* --------------------------------------------------------------------- */

    /* TB_SESSION_START - Fido */
    SUB_MSG_BEGIN(TB_SESSION_START_REQ, TB_CONNECT, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_SESSION_START_RESP, TB_CONNECT, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK_FAIL)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_SESSION_START_REQ,  TB_CONNECT,
                 TB_SESSION_START_RESP, TB_CONNECT)

    /* TB_SESSION_END - Fido */
    SUB_MSG_BEGIN(TB_SESSION_END_REQ, TB_CONNECT, MESSAGE_REQ, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_SESSION_END_RESP, TB_CONNECT, MESSAGE_RESP, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(status, "Status", TB_STATUS_OK)
    SUB_MSG_END

    SUB_MSG_PAIR(TB_SESSION_END_REQ,  TB_CONNECT,
                 TB_SESSION_END_RESP, TB_CONNECT)


    /* --------------------------------------------------------------------- */
    /* TB_ALERT */
    /* --------------------------------------------------------------------- */

    SUB_MSG_BEGIN(TB_ALERT_PORT_CHANGE_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_PORT_STATE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_PORT_REMOVE_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_PORT_STATE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_PORT_OR_BOX_RENAME_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_PORT_RENAME)
            SB_LST_ENTRY(TB_SB_BOX_RENAME)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_CONFIG_CHANGE_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_CONFIG)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_FREE_BOX_APPEAR_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_FREE_BOX)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_FREE_BOX_DISAPPEAR_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_FREE_BOX)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_PORT_PARAMETERS_CHANGE_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_PORT_PROTOCOL_XTI)
            SB_LST_ENTRY(TB_SB_PORT_RESYNC_MIN_PAUSE_XTI)
            SB_LST_ENTRY(TB_SB_PORT_STREAM_MAX_PAUSE_XTI)
            SB_LST_ENTRY(TB_SB_PORT_MASTER_ENDIANNESS)
            SB_LST_ENTRY(TB_SB_PORT_PROTOCOL)
            SB_LST_ENTRY(TB_SB_PORT_ALL_MASTER_ENDIANNESS)
            SB_LST_ENTRY(TB_SB_PORT_MASTER_FILTER)
            SB_LST_ENTRY(TB_SB_PORT_ALL_MASTER_FILTER)
            SB_LST_ENTRY(TB_SB_PORT_TIMING_CORRECTION_DATA)
            SB_LST_ENTRY(TB_SB_PORT_CALIBRATION_MODE)
            SB_LST_ENTRY(TB_SB_PORT_DETECT_TARGET_PRESENCE)
            SB_LST_ENTRY(TB_SB_PORT_RESYNC_MIN_PAUSE_STI)
            SB_LST_ENTRY(TB_SB_PORT_STREAM_MAX_PAUSE_STI)
            SB_LST_ENTRY(TB_SB_PORT_TRANSMIT_MIN_PAUSE_STI)
            SB_LST_ENTRY(TB_SB_PORT_SEPARATE_ADSP_DSP)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_PORT_CURRENT_PROTOCOL_CHANGE_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_PORT_CURRENT_PROTOCOL)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_LOGBOOK_MESSAGE_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_REMOTE_RES_CHANGE_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_REMOTE_RESOURCE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_REMOTE_RES_REMOVE_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_REMOTE_RESOURCE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_CONTROL_PANEL_OFF_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_DEVICE_CONNECTION_CHANGE_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        VALUE_CONST(port, "Port", TB_PORTS)
        VALUE_CONST(device_connected, "Device connected", TB_DEVICE_CONNECTED)
    SUB_MSG_END

    SUB_MSG_BEGIN(TB_ALERT_DATA_TO_DEVICE_FAILED_IND, TB_ALERT, MESSAGE_IND, "", "")
        COMMON_SUB_MSG_HDR
        REFERENCE(8, BE, n_sb, "Number of subblocks", N_SB)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N_SB, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(TB_SB_SENDING_FAILURE)
            SB_LST_ENTRY(TB_SB_LOGBOOK_MESSAGE)
        SB_LST_REF_END
    SUB_MSG_END



    /* --------------------------------------------------------------------- */
    /* Ostrich control messages */
    /* --------------------------------------------------------------------- */

    /* OSTRICH_ACTIVE */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_ACTIVE, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        REFERENCE_CONST(group, "Group", GROUP, OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        VALUE(8, BE, rec_obj, "Rec object", HEX)
        LIST_OF_GROUPS
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_ACTIVE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(group, "Group", OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_ACTIVE, OSTRICH_ACTIVE_RESP)


    /* OSTRICH_FILTER */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_FILTER, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        REFERENCE_CONST(group, "Group", GROUP, OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        LIST_OF_GROUPS
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_FILTER_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(group, "Group", OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_FILTER, OSTRICH_FILTER_RESP)


    /* OSTRICH_MARKER_SET */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_MARKER_SET, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, remarks, "Remarks", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_MARKER_SET_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_SUCCESS
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_MARKER_SET, OSTRICH_MARKER_SET_RESP)

    
    /* OSTRICH_TIME_SET */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_TIME_SET, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        VALUE_EX(32, BE, base, "Base", DEC, 1.0, 0.0, "S")
        OSTRICH_COMMENT
    MSG_END

   
    
    /* OSTRICH_STATUS_QUERY */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_STATUS_QUERY, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_STATUS_QUERY_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        VALUE(8, BE, PhonePwr, "Phone pwr", DEC)
        VALUE_CONST(Phone2Ostr, "Phone2Ostr", OSTRICH_STI_STREAM)
        VALUE(32, BE, FreeMem, "Free mem", DEC)
        VALUE(32, BE, STIData, "Amount of STI data", DEC)
        VALUE(32, BE, DAJData, "Amount of DAJ data", DEC)
        VALUE(32, BE, BlockData, "Block data", DEC)
        VALUE(8, BE, Ostr2PhoneState, "Ostr2PhoneState", DEC)
        VALUE(8, BE, VState, "V state", DEC)
        VALUE(8, BE, MainPwr, "Main pwr", DEC)
        VALUE(8, BE, Batt,  "Battery state",  DEC)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_STATUS_QUERY, OSTRICH_STATUS_QUERY_RESP)


    /* OSTRICH_GO_OFFLINE */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_GO_OFFLINE, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_GO_OFFLINE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_GO_OFFLINE, OSTRICH_GO_OFFLINE_RESP)


    /* OSTRICH_LIST_PARAMETERS_1_7 */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_LIST_PARAMETERS_1_7, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_LIST_PARAMETERS_1_7_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, serial_number, "Serial Number", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, hw_version, "HW Version", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, sw_version, "SW Version", 17)
        VALUE(32, BE, DefIpAdd, "Default IP Address", DEC)
        VALUE(32, BE, DefSubMask, "Default Subnet Mask", DEC)
        VALUE(32, BE, DefBroadcast_add, "Default Broadcast Address", DEC)
        VALUE(32, BE, LeasedIpAdd, "Leased IP Address", DEC)
        VALUE(32, BE, LeasedSubMask, "Leased Subnet Mask", DEC)
        VALUE(32, BE, LeasedBroadcastAdd, "Leased Broadcast Address", DEC)
        VALUE(16, BE, udp_port, "UDP Port", DEC)
        VALUE(16, BE, tcp_port, "TCP Port", DEC)
        VALUE(8, BE, ethernet_media, "Ethernet Media", DEC)
        VALUE(32, BE, lease_time, "Lease Time", DEC)
        VALUE(8, BE, dhcp_startup_call, "DHCP Startup Call", DEC)
        VALUE(32, BE, MainPwrSupLoLim, "Main Power Supply Lower Limit", DEC)
        VALUE(32, BE, BatteryLoLim, "Battery Lower Limit", DEC)
        VALUE(32, BE, PhoneSupplyLowLim, "Phone Supply Lower Limit", DEC)
        VALUE(32, BE, PhonePwrSupMeasurePeriod, "Phone Power Supply Measurement Period", DEC)
        VALUE(32, BE, PauseBetweenRecStiMsg, "Pause Between Received Sti Messages", DEC)
        VALUE(32, BE, PauseAllowToCancelDataErr, "Pause Allowing To Cancel Data Error", DEC)
        VALUE(32, BE, PauseBetweenTransBytes, "Pause Between Transmitted Bytes", DEC)
        VALUE(8, BE, MemOverrunCheck, "Memory Overrun Checking", DEC)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_LIST_PARAMETERS_1_7, OSTRICH_LIST_PARAMETERS_1_7_RESP)


    /* OSTRICH_AD_CONVERSION */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_AD_CONVERSION, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(power, "Power type", OSTRICH_POWER_TYPES)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_AD_CONVERSION_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(power, "Power type", OSTRICH_POWER_TYPES)
        VALUE_CONST(result, "Result", OK_FAIL)
        VALUE_EX(32, BE, value, "Voltage", DEC, 1.0, 0.0, "MV")
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_AD_CONVERSION, OSTRICH_AD_CONVERSION_RESP)


    /* OSTRICH_LOAD_DATA */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_LOAD_DATA, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_BUS)
        FILLER(FILLER_FIXED, 8)
        BLOCK_REF(BE, msg, "Msg", BLOCK_PN_MSG, 0, 0, 0, REF_AS_MANY_AS_POSSIBLE)
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_LOAD_DATA_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_BUS)
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(success, "Success", OK_FAIL)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_LOAD_DATA, OSTRICH_LOAD_DATA_RESP)


    /* OSTRICH_SEND_DATA */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SEND_DATA, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_BUS)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SEND_DATA_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_BUS)
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(success, "Success", OK_FAIL)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_SEND_DATA, OSTRICH_SEND_DATA_RESP)


    /* OSTRICH_HELLO */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_HELLO, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_HELLO_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, ostrich_id, "Ostrich ID", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, serial_number, "Serial Number", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, sw_version, "SW Version", 17)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_HELLO, OSTRICH_HELLO_RESP)


    /* OSTRICH_AYT_OSTRICH */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_AYT_OSTRICH, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_AYT_OSTRICH_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_AYT_OSTRICH, OSTRICH_AYT_OSTRICH_RESP)


    /* OSTRICH_CLEAR_MEMORY */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_CLEAR_MEMORY, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(type, "Type", OSTRICH_MEMORY_TYPES)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_CLEAR_MEMORY_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(type, "Type", OSTRICH_MEMORY_TYPES)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_SUCCESS
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_CLEAR_MEMORY, OSTRICH_CLEAR_MEMORY_RESP)


    /* OSTRICH_HANDLE_STI_STREAM */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_HANDLE_STI_STREAM, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(action, "Action", OSTRICH_STI_STREAM)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_HANDLE_STI_STREAM_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(action, "Action", OSTRICH_STI_STREAM)
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(report, "Report", OK_FAIL)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_HANDLE_STI_STREAM, OSTRICH_HANDLE_STI_STREAM_RESP)


    /* OSTRICH_SET_POWER_LIMITS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_POWER_LIMITS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_POWER_LIMITS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
    MSG_END

    MSG_PAIR(OSTRICH_SET_POWER_LIMITS, OSTRICH_SET_POWER_LIMITS_RESP)


    /* OSTRICH_SET_DHCP_PARAMETERS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_DHCP_PARAMETERS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 8)
        VALUE(8, BE, mode, "Mode", HEX)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_DHCP_PARAMETERS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_SET_DHCP_PARAMETERS, OSTRICH_SET_DHCP_PARAMETERS_RESP)


    /* OSTRICH_CALL_DHCP */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_CALL_DHCP, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_CALL_DHCP_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    MSG_PAIR(OSTRICH_CALL_DHCP, OSTRICH_CALL_DHCP_RESP)


    /* OSTRICH_SET_IP_PARAMETERS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_IP_PARAMETERS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_IP_PARAMETERS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_SET_IP_PARAMETERS, OSTRICH_SET_IP_PARAMETERS_RESP)


    /* OSTRICH_SET_SYSTEM_PARAMETERS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_SYSTEM_PARAMETERS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_SYSTEM_PARAMETERS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    MSG_PAIR(OSTRICH_SET_SYSTEM_PARAMETERS, OSTRICH_SET_SYSTEM_PARAMETERS_RESP)


    /* OSTRICH_LIST_PARAMETERS_1_5 */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_LIST_PARAMETERS_1_5, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_LIST_PARAMETERS_1_5_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    MSG_PAIR(OSTRICH_LIST_PARAMETERS_1_5, OSTRICH_LIST_PARAMETERS_1_5_RESP)


    /* OSTRICH_SET_STI_TIMING_PARAMETERS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_STI_TIMING_PARAMETERS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(pause, "Pause", OSTRICH_PAUSE)
        FILLER(FILLER_FIXED, 8)
        VALUE_EX(32, BE, Value_in_microsec, "Value", DEC, 1.0, 0.0, "Microsec")
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_STI_TIMING_PARAMETERS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_SET_STI_TIMING_PARAMETERS, OSTRICH_SET_STI_TIMING_PARAMETERS_RESP)


    /* OSTRICH_LIST_PARAMETERS_1_6 */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_LIST_PARAMETERS_1_6, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_LIST_PARAMETERS_1_6_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 8)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, id, "ID", 18)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, SrNr, "Sr nr", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, SWVer, "SW ver", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, HWVer, "hW ver", 17)
        VALUE(32, BE, DefIP, "def IP", DEC)
        VALUE(32, BE, DefSubN, "def sub N", DEC)
        VALUE(32, BE, DefBCast, "def b cast", DEC)
        VALUE(32, BE, LeasedIP, "Leased IP", DEC)
        VALUE(32, BE, LeasedSubn, "Leased subn", DEC)
        VALUE(32, BE, LeasedBCast, "Leased b cast", DEC)
        VALUE(16, BE, UDPPort, "UDP port", HEX)
        VALUE(16, BE, TCPPort, "TCP port", HEX)
        VALUE(8, BE, EMedia, "e media", HEX)
        VALUE(32, BE, LeaseTime, "Lease time", DEC)
        VALUE(8, BE, DHCP, "DHCP", HEX)
        VALUE(32, BE, MainPower, "Main power", HEX)
        VALUE(32, BE, BatteryLow, "Battery low", HEX)
        VALUE(32, BE, PhoneLower, "Phone lower", HEX)
        VALUE(32, BE, PhoneMeas, "Phone meas", HEX)
        VALUE(32, BE, STIPause, "STI pause", DEC)
        VALUE(32, BE, ErrorCnl, "Error cnl", HEX)
        VALUE(32, BE, PauseTx, "Pause TX", DEC)
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, msg, "Msg", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
    MSG_END

    MSG_PAIR(OSTRICH_LIST_PARAMETERS_1_6, OSTRICH_LIST_PARAMETERS_1_6_RESP)


    /* OSTRICH_SET_PHONE_VOLT_PERIOD */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_PHONE_VOLT_PERIOD, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        VALUE_EX(8, BE, period, "Period", DEC, 1.0, 0.0, "S")
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_PHONE_VOLT_PERIOD_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, data, "Data", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
    MSG_END

    MSG_PAIR(OSTRICH_SET_PHONE_VOLT_PERIOD, OSTRICH_SET_PHONE_VOLT_PERIOD_RESP)


    /* OSTRICH_SET_PORTS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_PORTS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        VALUE(16, BE, tcp_port, "TCP port", DEC)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_PORTS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_SET_PORTS, OSTRICH_SET_PORTS_RESP)

    
    /* OSTRICH_SET_ID */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_ID, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, id, "ID", 17)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_ID_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_SET_ID, OSTRICH_SET_ID_RESP)

    
    /* OSTRICH_SET_MEMORY_OVERRUN_CHECK */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_MEMORY_OVERRUN_CHECK, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        VALUE(8, BE, mode, "Mode", DEC)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_MEMORY_OVERRUN_CHECK_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_SET_MEMORY_OVERRUN_CHECK, OSTRICH_SET_MEMORY_OVERRUN_CHECK_RESP)

    
    /* OSTRICH_2_LIST_PARAMETERS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_2_LIST_PARAMETERS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_2_LIST_PARAMETERS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, data, "Data", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
    MSG_END

    MSG_PAIR(OSTRICH_2_LIST_PARAMETERS, OSTRICH_2_LIST_PARAMETERS_RESP)

    
    /* OSTRICH_SET_MAC_ADDRESS */

    SEQ_BEGIN(OSTRICH_MAC_ADDRESS, DONT_CREATE_STRUCT, "", "")
        VALUE(8, BE, data, "Data", HEX)
    SEQ_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_MAC_ADDRESS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        SEQ_OF(addr, "Addr", OSTRICH_MAC_ADDRESS, 6)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_MAC_ADDRESS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_SET_MAC_ADDRESS, OSTRICH_SET_MAC_ADDRESS_RESP)

    
    /* OSTRICH_SET_LINE_SPEED */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_LINE_SPEED, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 8)
        VALUE(8, BE, speed, "Speed", DEC)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_LINE_SPEED_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(OSTRICH_SET_LINE_SPEED, OSTRICH_SET_LINE_SPEED_RESP)

    
    /* OSTRICH_SET_DIRECT_DATA_CHANNEL */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_DIRECT_DATA_CHANNEL, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_SET_DIRECT_DATA_CHANNEL_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(success, "Success", OK_FAIL)
        OSTRICH_COMMENT
    MSG_END

    /* --------------------------------------------------------------------- */
    /* Musti control messages */
    /* --------------------------------------------------------------------- */

    /* MUSTI_ACTIVE */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_ACTIVE, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        REFERENCE_CONST(group, "Group", GROUP, OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        VALUE(8, BE, rec_obj, "Rec object", HEX)
        LIST_OF_GROUPS
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_ACTIVE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(group, "Group", OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_ACTIVE, MUSTI_ACTIVE_RESP)


    /* MUSTI_FILTER */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_FILTER, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        REFERENCE_CONST(group, "Group", GROUP, OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        LIST_OF_GROUPS
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_FILTER_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(group, "Group", OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_FILTER, MUSTI_FILTER_RESP)


    /* MUSTI_MARKER_SET */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_MARKER_SET, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, remarks, "Remarks", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_MARKER_SET_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_SUCCESS
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_MARKER_SET, MUSTI_MARKER_SET_RESP)

    
    /* MUSTI_TIME_SET */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_TIME_SET, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        VALUE_EX(32, BE, base, "Base", DEC, 1.0, 0.0, "S")
        OSTRICH_COMMENT
    MSG_END
   
  
    /* MUSTI_STATUS_QUERY */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_STATUS_QUERY, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_STATUS_QUERY_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        VALUE(8, BE, XTI_state, "State Of XTI Processor", DEC)
        VALUE(8, BE, STI_state, "State Of STI Processor", DEC)
        VALUE(8, BE, CH1_state, "Logical State Of Channel CH1", DEC)
        VALUE(8, BE, CH2_state, "Logical State Of Channel CH2", DEC)
        VALUE(8, BE, cable_chan_CH1, "Cable To Channel CH1", DEC)
        VALUE(8, BE, cable_chan_CH2, "Cable To Channel CH2", DEC)
        VALUE(8, BE, TX_buffers_CH1, "TX Buffers State Of The Channel CH1", DEC)
        VALUE(8, BE, TX_buffers_CH2, "TX Buffers State Of The Channel CH2", DEC)
        VALUE(8, BE, DDC, "Direct Data Channel", DEC)
        VALUE(8, BE, MMD_CH1, "Mass Media Device Acc By Phone Conn To CH1", DEC)
        VALUE(8, BE, MMD_CH2, "Mass Media Device Acc By Phone Conn To CH2", DEC)
        VALUE(32, BE, no_of_free_bytes, "Number Of Free Bytes", DEC)
        VALUE(32, BE, no_of_occ_bytes, "Number Of Occupied Bytes", DEC)
        VALUE(32, BE, no_of_bytes_waiting_CH1, "Number Of Bytes Waiting For CH1", DEC)
        VALUE(32, BE, no_of_bytes_waiting_CH2, "Number Of Bytes Waiting For CH2", DEC)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_STATUS_QUERY, MUSTI_STATUS_QUERY_RESP)


    /* MUSTI_GO_OFFLINE */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_GO_OFFLINE, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_GO_OFFLINE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_GO_OFFLINE, MUSTI_GO_OFFLINE_RESP)


    /* MUSTI_AD_CONVERSION */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_AD_CONVERSION, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_AD_CONVERSION_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(report, "Report", OK_FAIL)
        VALUE_EX(32, BE, value, "Voltage", DEC, 1.0, 0.0, "MV")
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_AD_CONVERSION, MUSTI_AD_CONVERSION_RESP)


    /* MUSTI_LOAD_DATA */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_LOAD_DATA, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        BLOCK_REF(BE, msg, "Msg", BLOCK_PN_MSG, 0, 0, 0, REF_AS_MANY_AS_POSSIBLE)
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_LOAD_DATA_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(success, "Success", OK_FAIL)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_LOAD_DATA, MUSTI_LOAD_DATA_RESP)


    /* MUSTI_SEND_DATA */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SEND_DATA, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SEND_DATA_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        VALUE_CONST(success, "Success", OK_FAIL)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_SEND_DATA, MUSTI_SEND_DATA_RESP)


    /* MUSTI_HELLO */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_HELLO, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_HELLO_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, musti_id, "Musti ID", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, serial_number, "Serial Number", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, sw_version, "SW Version", 17)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_HELLO, MUSTI_HELLO_RESP)


    /* MUSTI_2_HELLO */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_2_HELLO, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, musti_id, "Musti ID", 17)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_2_HELLO_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, musti_id, "Musti ID", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, serial_number, "Serial Number", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, sw_version, "SW Version", 17)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_2_HELLO, MUSTI_2_HELLO_RESP)


    /* MUSTI_INTRODUCE */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_INTRODUCE, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_INTRODUCE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, musti_id, "Musti ID", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, serial_number, "Serial Number", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, sw_version, "SW Version", 17)
        VALUE(8, BE, state, "State", DEC)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_INTRODUCE, MUSTI_INTRODUCE_RESP)


    /* MUSTI_2_ACTIVE */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_2_ACTIVE, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        REFERENCE_CONST(group, "Group", GROUP, OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        VALUE(8, BE, rec_obj, "Rec object", HEX)
        LIST_OF_GROUPS
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_2_ACTIVE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(group, "Group", OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_2_ACTIVE, MUSTI_2_ACTIVE_RESP)


    /* MUSTI_3_ACTIVE */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_3_ACTIVE, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        REFERENCE_CONST(group, "Group", GROUP, OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        VALUE(8, BE, rec_obj, "Rec object", HEX)
        LIST_OF_GROUPS
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_3_ACTIVE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(group, "Group", OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_3_ACTIVE, MUSTI_3_ACTIVE_RESP)


    /* MUSTI_2_FILTER */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_2_FILTER, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        REFERENCE_CONST(group, "Group", GROUP, OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        LIST_OF_GROUPS
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_2_FILTER_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(group, "Group", OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_2_FILTER, MUSTI_2_FILTER_RESP)


    /* MUSTI_3_FILTER */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_3_FILTER, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        REFERENCE_CONST(group, "Group", GROUP, OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        LIST_OF_GROUPS
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_3_FILTER_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(group, "Group", OSTRICH_GROUPS)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_2_FILTER, MUSTI_2_FILTER_RESP)


    /* MUSTI_2_LIST_PARAMETERS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_2_LIST_PARAMETERS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_2_LIST_PARAMETERS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, musti_id, "Musti ID", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, serial_number, "Serial Number", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, sw_version, "SW Version", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, hw_version, "HW Version", 17)
        SEQ_OF(addr, "Addr", OSTRICH_MAC_ADDRESS, 6)
        VALUE(8, BE, speed, "Speed", DEC)
        VALUE(32, BE, DefIpAdd, "Default IP Address", DEC)
        VALUE(32, BE, DefSubMask, "Default Subnet Mask", DEC)
        VALUE(32, BE, DefGateway_add, "Default Gateway Address", DEC)
        VALUE(32, BE, LeasedIpAdd, "Leased IP Address", DEC)
        VALUE(32, BE, LeasedSubMask, "Leased Subnet Mask", DEC)
        VALUE(16, BE, tcp_port, "TCP Port", DEC)
        VALUE(8, BE, dhcp_startup_call, "DHCP Startup Call", DEC)
        VALUE(32, BE, PhonePwrSupAlarmLvlCh1, "Phone Power Supply Alarm Level For CH 1", DEC)
        VALUE(32, BE, PhonePwrSupAlarmLvlCh2, "Phone Power Supply Alarm Level For CH 2", DEC)
        VALUE(32, BE, PhonePwrSupSavPeriodCh1, "Phone Power Supply Saving Period For CH 1", DEC)
        VALUE(32, BE, PhonePwrSupSavPeriodCh2, "Phone Power Supply Saving Period For CH 2", DEC)
        VALUE(32, BE, MaxPauseAllowedBetCompOfXTI, "Maximum Pause Allowed Between The Components Of An XTI Message", DEC)
        VALUE(32, BE, PauseAllowingToCancelXTI, "Pause Allowing To Cancel The XTI Data Error", DEC)
        VALUE(32, BE, TrickLenForXTI, "Trick Length For XTI Data", DEC)
        VALUE(32, BE, MaxPauseAllowedBetCompOfSTI, "Maximal Pause Allowed Between The Components Of An STI Message", DEC)
        VALUE(32, BE, PauseAllowingToCancelSTI, "Pause Allowing To Cancel The STI Data Error", DEC)
        VALUE(32, BE, MinAllowPauseBetBytTraMustiSTI, "Min Allowed Pause Between Bytes Trans From Musti To STI", DEC)
        VALUE(8, BE, MemOverrunCheck, "Memory Overrund Checking", DEC)
        VALUE(8, BE, ChanCH1State, "Channel CH1 State", DEC)
        VALUE(8, BE, ChanCH2State, "Channel CH2 State", DEC)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_2_LIST_PARAMETERS, MUSTI_2_LIST_PARAMETERS_RESP)


    /* MUSTI_3_LIST_PARAMETERS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_3_LIST_PARAMETERS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_3_LIST_PARAMETERS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        SEQ_OF(bin_part_len, "Binary Part Length", AUTOGEN_SEQ_BYTE_HEX, 4)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, musti_id, "Musti ID", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, serial_number, "Serial Number", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, sw_version, "SW Version", 17)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, hw_version, "HW Version", 17)
        SEQ_OF(addr, "Addr", OSTRICH_MAC_ADDRESS, 6)
        VALUE(8, BE, speed, "Speed", DEC)
        VALUE(32, BE, DefIpAdd, "Default IP Address", DEC)
        VALUE(32, BE, DefSubMask, "Default Subnet Mask", DEC)
        VALUE(32, BE, DefGateway_add, "Default Gateway Address", DEC)
        VALUE(32, BE, LeasedIpAdd, "Leased IP Address", DEC)
        VALUE(32, BE, LeasedSubMask, "Leased Subnet Mask", DEC)
        VALUE(16, BE, tcp_port, "TCP Port", DEC)
        VALUE(8, BE, dhcp_startup_call, "DHCP Startup Call", DEC)
        VALUE(32, BE, PhonePwrSupAlarmLvlCh1, "Phone Power Supply Alarm Level For CH 1", DEC)
        VALUE(32, BE, PhonePwrSupAlarmLvlCh2, "Phone Power Supply Alarm Level For CH 2", DEC)
        VALUE(32, BE, PhonePwrSupSavPeriodCh1, "Phone Power Supply Saving Period For CH 1", DEC)
        VALUE(32, BE, PhonePwrSupSavPeriodCh2, "Phone Power Supply Saving Period For CH 2", DEC)
        VALUE(32, BE, MaxPauseAllowedBetCompOfXTI, "Maximum Pause Allowed Between The Components Of An XTI Message", DEC)
        VALUE(32, BE, PauseAllowingToCancelXTI, "Pause Allowing To Cancel The XTI Data Error", DEC)
        VALUE(32, BE, TrickLenForXTI, "Trick Length For XTI Data", DEC)
        VALUE(32, BE, MaxPauseAllowedBetCompOfSTI, "Maximal Pause Allowed Between The Components Of An STI Message", DEC)
        VALUE(32, BE, PauseAllowingToCancelSTI, "Pause Allowing To Cancel The STI Data Error", DEC)
        VALUE(32, BE, MinAllowPauseBetBytTraMustiSTI, "Min Allowed Pause Between Bytes Trans From Musti To STI", DEC)
        VALUE(8, BE, MemOverrunCheck, "Memory Overrund Checking", DEC)
        VALUE(8, BE, ChanCH1State, "Channel CH1 State", DEC)
        VALUE(8, BE, ChanCH2State, "Channel CH2 State", DEC)
        VALUE(8, BE, SourceOfXTITimestamps, "Source Of XTI Timestamps", DEC)
        SEQ_OF(NotUsed, "Not Used Reserved For Future Implementations", NOT_USED, 42)
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_3_LIST_PARAMETERS, MUSTI_3_LIST_PARAMETERS_RESP)


    /* MUSTI_SET_MAC_ADDRESS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_MAC_ADDRESS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        SEQ_OF(addr, "Addr", OSTRICH_MAC_ADDRESS, 6)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_MAC_ADDRESS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_SET_MAC_ADDRESS, MUSTI_SET_MAC_ADDRESS_RESP)


    /* MUSTI_SET_LINE_SPEED */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_LINE_SPEED, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        VALUE(8, BE, new_line_speed, "The New Line Speed", DEC)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_LINE_SPEED_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_SET_LINE_SPEED, MUSTI_SET_LINE_SPEED_RESP)


    /* MUSTI_CLEAR_MEMORY */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_CLEAR_MEMORY, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(type, "Type", OSTRICH_MEMORY_TYPES)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_CLEAR_MEMORY_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(type, "Type", OSTRICH_MEMORY_TYPES)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_SUCCESS
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_CLEAR_MEMORY, MUSTI_CLEAR_MEMORY_RESP)


    /* MUSTI_HANDLE_DATA_STREAM */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_HANDLE_DATA_STREAM, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(ch, "Channel", MUSTI_HANDLE_DATA_STREAM_OC)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_HANDLE_DATA_STREAM_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_HANDLE_DATA_STREAM, MUSTI_HANDLE_DATA_STREAM_RESP)


    /* MUSTI_SET_POWER_LIMITS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_POWER_LIMITS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(ch, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        VALUE_EX(32, BE, limit, "Value Of The Limit", DEC, 1.0, 0.0, "mV")
        FILLER(FILLER_FIXED, 8)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_POWER_LIMITS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(ch, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_SET_POWER_LIMITS, MUSTI_SET_POWER_LIMITS_RESP)


    /* MUSTI_SET_DHCP_PARAMETERS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_DHCP_PARAMETERS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 8)
        VALUE(8, BE, mode, "Mode", HEX)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_DHCP_PARAMETERS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_SET_DHCP_PARAMETERS, MUSTI_SET_DHCP_PARAMETERS_RESP)


    /* MUSTI_SET_IP_PARAMETERS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_IP_PARAMETERS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        SEQ_OF(NewDefaultAdd, "New Default IP Address", AUTOGEN_SEQ_BYTE_HEX, 4)
        SEQ_OF(NewDefaultSubMask, "New Default Subnet Mask", AUTOGEN_SEQ_BYTE_HEX, 4)
        SEQ_OF(NewDefaultGateAdd, "New Default Gateway Address", AUTOGEN_SEQ_BYTE_HEX, 4)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_IP_PARAMETERS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_SET_IP_PARAMETERS, MUSTI_SET_IP_PARAMETERS_RESP)


    /* MUSTI_SET_STI_TIMING_PARAMETERS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_STI_TIMING_PARAMETERS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(ch, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        VALUE(32, BE, parameter_value, "Value Of Parameter", DEC)
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_STI_TIMING_PARAMETERS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(ch, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_SET_STI_TIMING_PARAMETERS, MUSTI_SET_STI_TIMING_PARAMETERS_RESP)


    /* MUSTI_SET_PHONE_VOLT_PERIOD */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_PHONE_VOLT_PERIOD, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(ch, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        VALUE_EX(8, BE, period, "Period", DEC, 1.0, 0.0, "S")
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_PHONE_VOLT_PERIOD_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(ch, "Channel", OSTRICH_CHANNEL)
        FILLER(FILLER_FIXED, 8)
        OSTRICH_DECISION
    MSG_END

    MSG_PAIR(MUSTI_SET_PHONE_VOLT_PERIOD, MUSTI_SET_PHONE_VOLT_PERIOD_RESP)


    /* MUSTI_SET_PORTS */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_PORTS, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        VALUE(16, BE, tcp_port, "TCP port", DEC)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_PORTS_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_SET_PORTS, MUSTI_SET_PORTS_RESP)
    

    /* MUSTI_SET_ID */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_ID, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, id, "ID", 17)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_ID_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_SET_ID, MUSTI_SET_ID_RESP)


    /* MUSTI_SET_TIMESTAMP_SOURCE */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_TIMESTAMP_SOURCE, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        VALUE(8, BE, Mode, "Mode", DEC)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_TIMESTAMP_SOURCE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_SET_TIMESTAMP_SOURCE, MUSTI_SET_TIMESTAMP_SOURCE_RESP)


    /* MUSTI_SET_MEMORY_OVERRUN_CHECK */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_MEMORY_OVERRUN_CHECK, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        VALUE(8, BE, Mode, "Mode", DEC)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_MEMORY_OVERRUN_CHECK_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_DECISION
    MSG_END

    MSG_PAIR(MUSTI_SET_MEMORY_OVERRUN_CHECK, MUSTI_SET_MEMORY_OVERRUN_CHECK_RESP)


    /* MUSTI_SET_DIRECT_DATA_CHANNEL */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_DIRECT_DATA_CHANNEL, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(channel, "Channel", OSTRICH_CHANNEL)
        OSTRICH_COMMENT
    MSG_END

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(MUSTI_SET_DIRECT_DATA_CHANNEL_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        OSTRICH_SUCCESS
        OSTRICH_COMMENT
    MSG_END

    MSG_PAIR(MUSTI_SET_DIRECT_DATA_CHANNEL, MUSTI_SET_DIRECT_DATA_CHANNEL_RESP)

    /* --------------------------------------------------------------------- */
    /* Musti Originated Messages */
    /* --------------------------------------------------------------------- */
    /* REQ 417-54939 Include GPS_INFO in Public PMD files                    */
    /* Renamed from MUSTI_GPS_INFO. Info may come from external GPS via USB  */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    PROPERTY(PROPERTY_PMD_PUBLIC)
    PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "gps")
    MSG_BEGIN(GPS_INFO, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, info, "Info", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
    MSG_END

    /* --------------------------------------------------------------------- */
    /* Ostrich Originated Messages */
    /* --------------------------------------------------------------------- */

    /* OSTRICH_PHONE_VOLTAGE */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_PHONE_VOLTAGE, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        VALUE_EX(32, BE, vola, "Voltage", DEC, 1.0, 0.0, "MV")
    MSG_END


    /* OSTRICH_AYT_PC */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_AYT_PC, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(Default, "Default", OSTRICH_DEFAULT)
        FILLER(FILLER_FIXED, 8)
    MSG_END

    
    /* OSTRICH_PHONET_STAMP */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_PHONET_STAMP, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(type, "Type", OSTRICH_TIME_TYPES)
        FILLER(FILLER_FIXED, 8)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
    MSG_END


    /* OSTRICH_ALERT */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_ALERT, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        REFERENCE_CONST(alert, "Alert", ALERT, OSTRICH_MARKER_TYPES)
        FILLER(FILLER_FIXED, 8)
        CHOICE_BEGIN(data, "Data", ALERT)

            CASE_BEGIN(INVALID_XTI_MSG, "", "")
                VALUE(8, BE, n_par, "N par", DEC)
                VALUE(8, BE, error, "Error", DEC)
            CASE_END

            CASE_BEGIN(INVALID_STI_MSG, "", "")
                VALUE(8, BE, n_par, "N par", DEC)
                VALUE(8, BE, error, "Error", DEC)
            CASE_END

            CASE_BEGIN(STI_BLOCK_DATA_SEND_ENDED, "", "")
                VALUE(8, BE, n_par, "N par", DEC)
                VALUE(32, BE, n_bytes, "N bytes", DEC)
            CASE_END

            CASE_BEGIN(XTI_BLOCK_DATA_SEND_ENDED, "", "")
                VALUE(8, BE, n_par, "N par", DEC)
                VALUE(32, BE, n_bytes, "N bytes", DEC)
            CASE_END

            CASE_BEGIN(DIRECT_DATA_SEND_ENDED, "", "")
                VALUE(8, BE, n_par, "N par", DEC)
                VALUE(32, BE, n_bytes, "N bytes", DEC)
            CASE_END

            CASE_BEGIN(XTI_ILLEGAL_BIT_RATE, "", "")
                REFERENCE(8, BE, length, "Length", N)
                STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, rate, "Rate", N, ISIHDR_DONT_GENERATE)
            CASE_END

            DEFAULT_BEGIN("", "")
                REFERENCE(8, BE, n_par, "N par", N)
                SEQ_OF_REF(par, "Par", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_DONT_GENERATE)
            DEFAULT_END
        CHOICE_END

        OSTRICH_COMMENT
    MSG_END


    /* OSTRICH_MARKER */

    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(OSTRICH_MARKER, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        VALUE_CONST(type, "Type", OSTRICH_MARKER_TYPES)
#if ((defined AUTOGEN_INCLUDE_OST) && (defined AUTOGEN_INCLUDE_TB_INTO_OST))
        VALUE(8, BE, sender_obj, "Sender", HEX)
#else
        FILLER(FILLER_FIXED, 8)
#endif
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        VALUE(32, BE, index, "Index", DEC)
        OSTRICH_PARAMETERS
        OSTRICH_COMMENT
    MSG_END

#ifndef TB_SPEC_ONLY

#if ((!defined AUTOGEN_INCLUDE_OST) || (!defined AUTOGEN_INCLUDE_TB_INTO_OST))
    /* This section can currently not be included to be decoded in OST protocol.
       Autogen can generate the PMD file but FastTrace / Tracing SDK reports the 
       following error: 
         Couldn't load PMD file; Duplicate CMessage objects '<name>' in CMessageType 'STI trace'.
       All messages are marked as STI trace : MSG_BEGIN(..., STI_TRACE, "", "")

       neo 3/8 - 2009
    */


    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    CONST_TBL_BEGIN(CS_ID, 8, BE, "", "")
        CONST_TBL_ENTRY(UNKNOWN,                        0x00, "")
        CONST_TBL_ENTRY(DAMPS,                          0x10, "")
        CONST_TBL_ENTRY(GSM,                            0x20, "")
        CONST_TBL_ENTRY(CDMA,                           0x40, "")
        CONST_TBL_ENTRY(WCDMA,                          0x50, "")
        CONST_TBL_ENTRY(APPLICATION,                    0x60, "")
    CONST_TBL_END

    /* XTI_STI_MSG */

    BIT_TBL_BEGIN(PRIMARY_MSG_TYPE, 16, BE, "", "")
        BIT_TBL_ENTRY("00000-----------", _DSP_OSMOT, "")
        BIT_TBL_ENTRY("00010-00--------", _DSP_OSMO, "")
        BIT_TBL_ENTRY("011-------------", _MCU_OSMOT, "")
        BIT_TBL_ENTRY("110---00--------", _MCU_OSMO, "")

        BIT_TBL_ENTRY("100----00-------", _MCU_IO_READ, "")
        BIT_TBL_ENTRY("100----01-------", _DSP_IO_READ, "")
        BIT_TBL_ENTRY("100----10-------", DMA_IO_READ, "")

        BIT_TBL_ENTRY("101----00-------", _MCU_IO_WRITE, "")
        BIT_TBL_ENTRY("101----01-------", _DSP_IO_WRITE, "")
        BIT_TBL_ENTRY("101----10-------", DMA_IO_WRITE, "")

        BIT_TBL_ENTRY("1110100000000000", RAW_MODE, "")

        BIT_TBL_ENTRY("1111100000000000", MCU_IO_OVERFLOW, "")
        BIT_TBL_ENTRY("1111100100000000", DSP_IO_OVERFLOW, "")
        BIT_TBL_ENTRY("1111101000000000", DMA_IO_OVERFLOW, "")
    BIT_TBL_END

    MSG_BEGIN(PRIMARY_MSG, STI_TRACE, "", "")
        COMMON_MSG_HDR
        REFERENCE_CONST(msg, "Msg", TYPE, PRIMARY_MSG_TYPE)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        CHOICE_BEGIN(address, "Address", TYPE)
            CASE_BEGIN(RAW_MODE, "", "")
            CASE_END
            DEFAULT_BEGIN("", "")
                VALUE(32, BE, address, "Address", HEX)
            DEFAULT_END
        CHOICE_END
        SEQ_OF_REF(data, "Data", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
    MSG_END

    /* NOS_TRACES */

    PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "mcu")
    MSG_BEGIN(NOS_TRACES, STI_TRACE, "", "")
        VALUE(8, BE, transaction_id, "Transaction ID", DEC)
        REFERENCE(8, BE, group_id, "Group ID", MSG_ID)
        REFERENCE(8, BE, trace_id, "Trace ID", TRACE_ID_OS)
        FILLER(FILLER_FIXED, 8)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PMD_ANCHOR, "OS_TRACE_STRUCTURE", NULL, 0, REF_AS_MANY_AS_POSSIBLE)
    MSG_END

    /* DSP_OSMO */

    MSG_BEGIN(DSP_OSMO, STI_TRACE, "", "")
        COMMON_MSG_HDR
    MSG_END


    /* INSTR_DATA */

    MSG_BEGIN(INSTR_DATA, STI_TRACE, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, MsgType, "Msg type", HEX)
        FILLER(FILLER_FIXED, 8)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
    MSG_END


    /* MCU_ASCII_PRINTF */

    PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "mcu")
    MSG_BEGIN(MCU_ASCII_PRINTF, STI_TRACE, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, channel, "Channel", HEX)
        FILLER(FILLER_FIXED, 8)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, msg, "Msg", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
    MSG_END


    /* MCU_RAW_DATA */

    PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "mcu")
    MSG_BEGIN(MCU_RAW_DATA, STI_TRACE, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, ch, "Channel", HEX)
        FILLER(FILLER_FIXED, 8)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        VALUE(8, BE, type, "Type", HEX)
        SEQ_OF_REF(data, "Data", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
    MSG_END


    /* MCU_RAW_DATA_NEW */

    PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "mcu")
    MSG_BEGIN(MCU_RAW_DATA_NEW, STI_TRACE, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, ch, "Channel", HEX)
        FILLER(FILLER_FIXED, 8)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        SEQ_OF_REF(data, "Data", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
    MSG_END


    /* MCU_TRACE_DATA */

    PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "mcu")
    PROPERTY(PROPERTY_PMD_PUBLIC)
    MSG_BEGIN(MCU_TRACE_DATA, STI_TRACE, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, ch, "Channel", HEX)
        FILLER(FILLER_FIXED, 8)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, PN_DEV_HOST)
	    BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PROTOCOL, "ENTRY_POINT_MASTER_TRACE", NULL, 0, REF_LENGTH_UNKNOWN)
    MSG_END


    /* SYMBIAN_TRACE */

    MSG_BEGIN(SYMBIAN_TRACE, STI_TRACE, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, ch, "Channel", HEX)
        FILLER(FILLER_FIXED, 8)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        AUTOGEN_SYMBIAN_TRACE_STRUCTURE()
    MSG_END


    /* DSP_ASCII_PRINTF */

    PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "cdsp")
    MSG_BEGIN(DSP_ASCII_PRINTF, STI_TRACE, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, channel, "Channel", HEX)
        FILLER(FILLER_FIXED, 8)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        VALUE(16, BE, id, "ID", HEX)
        STRING_REF(STRING_ASCII_ZERO_TERMINATED, BE, msg, "Msg", REF_LENGTH_DETERMINED_BY_ZERO, ISIHDR_DONT_GENERATE)
    MSG_END


    /* ADSP_RAW_DATA */
    
    PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "adsp")
    MSG_BEGIN(ADSP_RAW_DATA, STI_TRACE, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, channel, "Channel", HEX)
        VALUE_CONST(cs_id, "CS ID", CS_ID)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        SEQ_OF_REF(data, "Data", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
    MSG_END


    /* ADSP_RAW_DATA_NEW */

    PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "adsp")
	MSG_BEGIN(ADSP_RAW_DATA_NEW, STI_TRACE, "", "") 
		COMMON_MSG_HDR 
		VALUE(8, BE, channel, "Channel", HEX) 
		REFERENCE_CONST(cs_id, "CS ID", CS, CS_ID) 
		TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI) 
		CHOICE_BEGIN(data, "Data", CS) 
			CASE_BEGIN(APPLICATION, "", "") 
                AUTOGEN_ADSP5_OLD_TRACE_STRUCTURE()
            CASE_END
		CHOICE_END 
	MSG_END 


    /* CDSP_RAW_DATA */

    PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "cdsp")
    MSG_BEGIN(DSP_RAW_DATA, STI_TRACE, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, channel, "Channel", HEX)
        REFERENCE_CONST(cs_id, "CS ID", CS, CS_ID)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        CHOICE_BEGIN(cs, "CS", CS)
            CASE_BEGIN(APPLICATION, "", "")
                VALUE(16, BE, sw_id, "SW assigned ID", HEX)
                AUTOGEN_ADSP5_OLD_TRACE_STRUCTURE()
            CASE_END
            DEFAULT_BEGIN("", "")
                SEQ_OF_REF(data, "Data", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
            DEFAULT_END
        CHOICE_END
    MSG_END

    
    /* DSP_RAW_DATA2 */

    PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "cdsp")
    MSG_BEGIN(DSP_RAW_DATA2, STI_TRACE, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, channel, "Channel", HEX)
        FILLER(FILLER_FIXED, 8)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        SEQ_OF_REF(data, "Data", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
    MSG_END


    /* DSP_RAW_DATA_NEW */

    CONST_TBL_BEGIN(DSP_RAW_DATA_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(DSP5_TRACE,                 0xD0, "")
        CONST_TBL_ENTRY(DSP5_TRACE_NEW,             0xD1, "")
        CONST_TBL_ENTRY(DSP_DATA_MEMORY_DUMP_IND,   0x49, "")
        CONST_TBL_ENTRY(DSP_INVARIANT_TRACE,        0x00, "")
    CONST_TBL_END

#define DSP_INVARIANT_TRACE_DATA 0x21

    PROPERTY(PROPERTY_SB_LENGTH_MISSING)
    SB_BEGIN(DSP_INVARIANT_TRACE_DATA, "", "")
        REFERENCE(8, BE, sb_id, "Subblock ID", SB_ID)
        FILLER(FILLER_FIXED, 8)
        FILLER(FILLER_FIXED, 8)
        AUTOGEN_INVARIANT_TRACE_STRUCTURE()
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_PMD_TRACE_IDENTIFIER, "cdsp")
    PROPERTY(PROPERTY_PMD_PUBLIC)
    MSG_BEGIN(DSP_RAW_DATA_NEW, STI_TRACE, "", "")
        COMMON_MSG_HDR
        VALUE(8, BE, channel, "Channel", HEX)
        FILLER(FILLER_FIXED, 8)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        VALUE_CONST(cs_id, "CS ID", CS_ID)
        REFERENCE_CONST(type, "Type", TYPE, DSP_RAW_DATA_TYPE)
        CHOICE_BEGIN(data, "Data", TYPE)

            CASE_BEGIN(DSP5_TRACE, "", "")
                AUTOGEN_CDSP5_OLD_TRACE_STRUCTURE()
            CASE_END

            CASE_BEGIN(DSP5_TRACE_NEW, "", "")
                AUTOGEN_CDSP5_TRACE_STRUCTURE()
            CASE_END

            CASE_BEGIN(DSP_DATA_MEMORY_DUMP_IND, "", "")
                REFERENCE(16, BE, length, "Length", N) 
                VALUE(32, BE, Address, "Address", HEX)
                SEQ_OF_REF(data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_DONT_GENERATE)
            CASE_END

            CASE_BEGIN(DSP_INVARIANT_TRACE, "", "")
                FILLER(FILLER_FIXED, 8)
                PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
                PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
                REFERENCE(8, BE, sub_block_ount, "Number of subblocks", N)
                SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
                    SB_LST_ENTRY(DSP_INVARIANT_TRACE_DATA)
                SB_LST_REF_END
            CASE_END

        CHOICE_END
    MSG_END
#endif   /* #if ((!defined AUTOGEN_INCLUDE_OST) || (!defined AUTOGEN_INCLUDE_TB_INTO_OST)) */


    /* TB_TRACE_MSG */

    PROPERTY(PROPERTY_PMD_MESSAGE_IS_CARRIER)
    PROPERTY(PROPERTY_PMD_PUBLIC)
    MSG_BEGIN(TB_TRACE_MSG, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
        REFERENCE(8, BE, master, "Master", XTI_MASTER_ID)
        VALUE(8, BE, channel, "Channel", HEX)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        BLOCK_REF(BE, data, "Data", BLOCK_PMD_ANCHOR, 
            "XTI_MASTER_STRUCTURE", NULL, 0, REF_AS_MANY_AS_POSSIBLE)
    MSG_END


    /* TB_TRACE_EXCEPTION_MSG */

    CONST_TBL_BEGIN(EXCEPTION_CODES, 8, BE, "", "")
        CONST_TBL_ENTRY(LONG_MESSAGE_FIRST,      0x01, "")
        CONST_TBL_ENTRY(LONG_MESSAGE,            0x02, "")
        CONST_TBL_ENTRY(LONG_MESSAGE_LAST,       0x03, "")
        CONST_TBL_ENTRY(UNFINISHED_MESSAGE,      0x04, "")
        CONST_TBL_ENTRY(OVRF_MESSAGE,            0x05, "")
        CONST_TBL_ENTRY(LONG_UNFINISHED_MESSAGE, 0x06, "")
        CONST_TBL_ENTRY(LONG_OVRF_MESSAGE,       0x07, "")
        CONST_TBL_ENTRY(OVRF,                    0x08, "")
    CONST_TBL_END

    MSG_BEGIN(TB_TRACE_EXCEPTION_MSG, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_SUPPRESS_AUTOGEN_WARNINGS)
        REFERENCE(8, BE, master, "Master", XTI_MASTER_ID)
        VALUE(8, BE, channel, "Channel", HEX)
        TIMESTAMP(64, BE, time, "Time", PMD_TIMESTAMP_TYPE_STI_XTI)
        REFERENCE_CONST(reason, "Reason", EXCEPTION, EXCEPTION_CODES)
        CHOICE_BEGIN(exception, "Exception", EXCEPTION)
            CASE_BEGIN(LONG_MESSAGE_FIRST, "", "")
                BLOCK_REF(BE, data, "Data", BLOCK_PMD_ANCHOR, 
                    "XTI_MASTER_STRUCTURE", NULL, 0, REF_AS_MANY_AS_POSSIBLE)
            CASE_END
            CASE_BEGIN(UNFINISHED_MESSAGE, "", "")
                BLOCK_REF(BE, data, "Data", BLOCK_PMD_ANCHOR, 
                    "XTI_MASTER_STRUCTURE", NULL, 0, REF_AS_MANY_AS_POSSIBLE)
            CASE_END
            CASE_BEGIN(OVRF_MESSAGE, "", "")
                BLOCK_REF(BE, data, "Data", BLOCK_PMD_ANCHOR, 
                    "XTI_MASTER_STRUCTURE", NULL, 0, REF_AS_MANY_AS_POSSIBLE)
            CASE_END
            CASE_BEGIN(OVRF, "", "")
                VALUE(8, BE, ovrf_count, "Number of overflows", DEC)
            CASE_END
            DEFAULT_BEGIN("", "")
                SEQ_OF_REF(exception_data, "Exception data" , AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
            DEFAULT_END
        CHOICE_END
    MSG_END

#endif /* TB_SPEC_ONLY */

RES_END

/*  End of file autogen_ostrich.h */
