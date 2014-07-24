/*
NOKIA MOBILE PHONES
R&D Copenhagen
TSS



            dsp_core_isi_m.h
            -------------------
            SW include - ANSI C



Continuus Ref:
--------------
Project:          [CM_PROJECT_NAME]

%name:            autogen_adsp_core.h %
%version:         co1tss#4 %
%cvtype:          incl %
%instance:        co1pctls_1 %

Change History:

VERSION     : 3                 DRAFT           15-Oct-2004  Christian Jacob Hansen
REASON      : Bug fix
REFERENCE   : -
DESCRIPTION : Change timestamp to PMD_TIMESTAMP_TYPE_ADSP

VERSION     : 2                 DRAFT           13-Oct-2004  Christian Jacob Hansen
REASON      : Bug fix
REFERENCE   : -
DESCRIPTION : Change default Device ID to PN_DEV_DSP_AUX

VERSION     : 1                 DRAFT           12-Oct-2004  Christian Jacob Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the macro file, copied from autogen_dsp_core.h
*/



/*  1    ABSTRACT

    1.1    Module type

    Message definition file for autogen
   

    1.2    Functional description

    This file is the message definition file for the ADSP Core server


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

/* Message ID's */

#define ADSP_FBUS_MODE_REQ                           0x01
#define ADSP_VERSION_REQ                             0x02
#define ADSP_MDI_LOOPBACK_REQ                        0x03
#define ADSP_MEMORY_READ_REQ                         0x04
#define ADSP_MEMORY_WRITE_REQ                        0x05
#define ADSP_BIT_WRITE_SET_REQ                       0x06
#define ADSP_BIT_WRITE_CLEAR_REQ                     0x07
#define ADSP_BIT_MASK_WRITE_REQ                      0x08
#define ADSP_TRACE_MASK_REQ                          0x09
#define ADSP_TRACE_MASK_UPDATE_REQ                   0x0A
#define ADSP_USER_DATA_REQ                           0x0B
#define ADSP_SIGNAL_REQ                              0x0C
#define ADSP_RTC_CALIBRATION_REQ                     0x0D
#define ADSP_MEMORY_CONTROL_REQ                      0x0E
#define ADSP_MSG_LOOP_REQ                            0x0F
#define ADSP_CS_MODE_REQ                             0x10
#define ADSP_SLEEP_REQ                               0x11
#define ADSP_LOAD_MONITOR_REQ                        0x12
#define ADSP_SET_TRACE_LEVEL_REQ                     0x13
#define ADSP_DATA_MEMORY_DUMP_REQ                    0x14

#define ADSP_FBUS_ERROR_IND                          0x40
#define ADSP_TASKSWAP_IND                            0x41
#define ADSP_SIGNAL_IND                              0x42
#define ADSP_ERROR_IND                               0x43
#define ADSP_USER_TRACE_IND                          0x44
#define ADSP_SWDL_START_IND                          0x45
#define ADSP_SWDL_STOP_IND                           0x46
#define ADSP_CS_MODE_IND                             0x47
#define ADSP_PRODUCT_INFO_IND                        0x48
#define ADSP_DATA_MEMORY_DUMP_IND                    0x49
#define ADSP_ALLOC_FREE_IND                          0x4A
#define ADSP_TRACES_LOST_IND                         0x4B

#define ADSP_FBUS_MODE_RESP                          0x80
#define ADSP_VERSION_RESP                            0x81
#define ADSP_MDI_LOOPBACK_RESP                       0x82
#define ADSP_MEMORY_READ_RESP                        0x83
#define ADSP_MEMORY_WRITE_RESP                       0x84
#define ADSP_BIT_WRITE_SET_RESP                      0x85
#define ADSP_BIT_WRITE_CLEAR_RESP                    0x86
#define ADSP_BIT_MASK_WRITE_RESP                     0x87
#define ADSP_TRACE_MASK_RESP                         0x88
#define ADSP_TRACE_MASK_UPDATE_RESP                  0x89
#define ADSP_RTC_CALIBRATION_RESP                    0x8A
#define ADSP_MEMORY_CONTROL_RESP                     0x8B
#define ADSP_MSG_LOOP_RESP                           0x8C
#define ADSP_CS_MODE_RESP                            0x8D
#define ADSP_SLEEP_RESP                              0x8E
#define ADSP_LOAD_MONITOR_RESP                       0x8F
#define ADSP_SET_TRACE_LEVEL_RESP                    0x90

/* Message ID's reserved for DSP5 changes */
#define ADSP_DSP5_MSG_ID1                            0xD0
#define ADSP_DSP5_MSG_ID2                            0xD1
#define ADSP_DSP5_MSG_ID3                            0xD2
#define ADSP_DSP5_MSG_ID4                            0xD3
#define ADSP_DSP5_MSG_ID5                            0xD4
#define ADSP_DSP5_MSG_ID6                            0xD5
#define ADSP_DSP5_MSG_ID7                            0xD6
#define ADSP_DSP5_MSG_ID8                            0xD7
#define ADSP_DSP5_MSG_ID9                            0xD8
#define ADSP_DSP5_MSG_ID10                           0xD9
#define ADSP_DSP5_MSG_ID11                           0xDA
#define ADSP_DSP5_MSG_ID12                           0xDB
#define ADSP_DSP5_MSG_ID13                           0xDC
#define ADSP_DSP5_MSG_ID14                           0xDD
#define ADSP_DSP5_MSG_ID15                           0xDE
#define ADSP_DSP5_MSG_ID16                           0xDF


/* Sub block ID's */
/*
#define ADSP_SB_ALLOC_DATA                           0x01
#define ADSP_SB_FREE_DATA                            0x02
#define ADSP_SB_ALLOC_DATA_TIME                      0x03
#define ADSP_SB_FREE_DATA_TIME                       0x04
*/


/* Other constants */
#define ADSP_MAX_NUM_OF_LOAD_RESULTS         32000
#define ADSP_MAX_MEMORY_ACCESS_SIZE          255
#define ADSP_CORE_MAX_DATA_LEN               128
#define MAX_SIG_DATA_LEN                    1024
#define ADSP_IDLE_MON                        0x00
#define ADSP_PROC_MON                        0x01
#define ADSP_SIG_ID                          0x00
#define ADSP_SIG_ID_AND_DATA                 0x01
#define ADSP_SIG_ID_AND_TIME                 0x02
#define ADSP_SIG_ID_AND_DATA_AND_TIME        0x03
#define ADSP_ALLOC_DATA                      0x01
#define ADSP_ALLOC_DATA_TIME                 0x02
#define ADSP_FREE_DATA                       0x03       
#define ADSP_FREE_DATA_TIME                  0x04
#define ADSP_SYNC_SENDING_DISABLE            0x00
#define ADSP_FBUS_POWERED_DOWN_IMMEDIATELY   0x00
#define ADSP_FBUS_ON_FOREVER                 0xFF


/*  4    MACROS */

#define ADSP_OS_TIMESTAMP \
    PROPERTY(PROPERTY_PMD_PARAMETER) \
    PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED, "t_stamp_lsb") \
    TIMESTAMP(32, BE, t_stamp_msb, "Timestamp", PMD_TIMESTAMP_TYPE_ADSP)

#define ADSP_SIGN_ID \
    PROPERTY(PROPERTY_PMD_PARAMETER) \
    VALUE_CONST(sig_id, "Signal ID", ADSP_SIGNAL_ID)

#define ADSP_TASK_ID \
    PROPERTY(PROPERTY_PMD_PARAMETER) \
    VALUE_CONST(pr_id, "Process ID", ADSP_PROCESS_ID)


/* TODO: Change the version whenever the interface is changed */
/* default ISI version */

#ifndef ADSP_CORE_ISI_VERSION
#define ADSP_CORE_ISI_VERSION
#define ADSP_CORE_ISI_VERSION_Z      3
#define ADSP_CORE_ISI_VERSION_Y      4
#endif

PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, PN_DEV_DSP_AUX)

RES_BEGIN(RESOURCE_ISI, PN_ADSP_CORE, ADSP_CORE, "ADSP Core Server", 
    RES_VERSION_STRING(ADSP_CORE_ISI_VERSION_Z, ADSP_CORE_ISI_VERSION_Y), TRUE)


    RES_COMMENT(COMMENT_ISIHDR_FILENAME,    "")
    RES_COMMENT(COMMENT_ISIHDR_FILENAME_16, "dsp_core_isi.h")

    /* --------------------------------------------------------------------- */
    /* Project / Document information */
    /* --------------------------------------------------------------------- */

    RES_COMMENT(COMMENT_SITE_NAME,              "SITE_NAME")
    RES_COMMENT(COMMENT_PROJECT_NAME,           "PROJECT_NAME")
    RES_COMMENT(COMMENT_OWNER_NAME,             "OWNER_NAME")

    RES_COMMENT(COMMENT_CONFIDENTIALITY,        "CONFIDENTIAL")

    RES_COMMENT(COMMENT_CONTINUUS_PROJECT_NAME,  "CM_PROJECT_NAME")
    RES_COMMENT(COMMENT_CONTINUUS_INSTANCE_NAME, "CM_INSTANCE_NAME")

    RES_COMMENT(COMMENT_PCMS_ISIHDR_PART,       "PCMS_ISIHDR_PART")
    RES_COMMENT(COMMENT_PCMS_ISIHDR_ITEM,       "PCMS_ISIHDR_ITEM")

    RES_COMMENT(COMMENT_PCMS_ISIHDR_ITEM_16,    "PCMS_ISIHDR_ITEM_16")
    RES_COMMENT(COMMENT_PCMS_HTML_PART,         "PCMS_HTML_PART")
    RES_COMMENT(COMMENT_PCMS_HTML_ITEM,         "PCMS_HTML_ITEM")

    RES_COMMENT(COMMENT_PCMS_WORKSET,           "PCMS_WORKSET")
    RES_COMMENT(COMMENT_ISIHDR_TITLE,           "ISIHDR_TITLE")

    RES_COMMENT(COMMENT_HTML_TITLE,             "HTML_TITLE")
    RES_COMMENT(COMMENT_HTML_FILENAME,          "i_dsp_core_isi_m.html")
    RES_COMMENT(COMMENT_HTML_DOCUMENT_NUMBER,   "HTML_DOC_NUMBER")

    RES_COMMENT(COMMENT_INCLUDE_HTML_INTRODUCTION, "")

    RES_COMMENT(COMMENT_SUPPORT_BITFIELDS_IN_ISIHDR, "")
    RES_COMMENT(COMMENT_SUPPORT_BOOLS_IN_ISIHDR, "")


    /* --------------------------------------------------------------------- */
    /* Server description */
    /* --------------------------------------------------------------------- */


    /* --------------------------------------------------------------------- */
    /* ISI version history */
    /* --------------------------------------------------------------------- */

    ISI_VERSION_COMMENT(COMMENT_CHANGE_REASON,    "-")
    ISI_VERSION_COMMENT(COMMENT_CHANGE_REFERENCE, "-")
    ISI_VERSION_COMMENT(COMMENT_CHANGE_STATUS,    "DRAFT")
    ISI_VERSION_COMMENT(COMMENT_CHANGE_DATE,      "23-Jun-2003")
    ISI_VERSION_COMMENT(COMMENT_CHANGE_PERSON,    "Christian Jacob Hansen")
    ISI_VERSION_COMMENT(COMMENT_TEXT, "First version of the file")
    ISI_VERSION_HISTORY("003.004")


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
    COMMENT(COMMENT_PARAGRAPH, "Part:      ISI:COMMON.BASE")
    COMMENT(COMMENT_PARAGRAPH, "Item name: ISI:COMMON_MESSAGES.BASE-SPEC")
    COMMENT(COMMENT_PARAGRAPH, "Workset:   ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename:  i_comm_m.doc")
    NOTE("/4/")

    COMMENT(COMMENT_PARAGRAPH, "ISI Common Feature Descriptions")
    COMMENT(COMMENT_PARAGRAPH, "Part:      ISI:COMMON.BASE")
    COMMENT(COMMENT_PARAGRAPH, "Item name: ISI:COMMON_MESSAGES.BASE-SPEC")
    COMMENT(COMMENT_PARAGRAPH, "Workset:   ISI:WS_ISI")
    COMMENT(COMMENT_PARAGRAPH, "Filename:  i_comm_f.doc")
    NOTE("/5/")


    /* --------------------------------------------------------------------- */
    /* Symbol tables */
    /* --------------------------------------------------------------------- */

    CONST_TBL_BEGIN(ADSP_LOAD_MONITOR_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(ADSP_IDLE_MON,                           ADSP_IDLE_MON, "")
        CONST_TBL_ENTRY(ADSP_PROC_MON,                           ADSP_PROC_MON, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_MEMORY_TRACE_TABLE, 4, BE, "", "")
        CONST_TBL_ENTRY(ADSP_ALLOC_DATA,                         ADSP_ALLOC_DATA, "")
        CONST_TBL_ENTRY(ADSP_ALLOC_DATA_TIME,                    ADSP_ALLOC_DATA_TIME, "")
        CONST_TBL_ENTRY(ADSP_FREE_DATA_TIME,                     ADSP_FREE_DATA_TIME, "")
    CONST_TBL_END

    CONST_TBL_BEGIN(FBUS_RATES, 8, BE, "", "")
        CONST_TBL_ENTRY(ADSP_FBUS_9_6,                           0x00, "9600")
        CONST_TBL_ENTRY(ADSP_FBUS_19_2,                          0x01, "19200")
        CONST_TBL_ENTRY(ADSP_FBUS_28_8,                          0x02, "28800")
        CONST_TBL_ENTRY(ADSP_FBUS_38_4,                          0x03, "38400")
        CONST_TBL_ENTRY(ADSP_FBUS_57_6,                          0x04, "57600")
        CONST_TBL_ENTRY(ADSP_FBUS_115_2,                         0x05, "115200")
        CONST_TBL_ENTRY(ADSP_FBUS_230_4,                         0x06, "230400")
        CONST_TBL_ENTRY(ADSP_FBUS_533_3,                         0x07, "533300")
        CONST_TBL_ENTRY(ADSP_FBUS_2x533_3,                       0x08, "2*533300")
        CONST_TBL_ENTRY(ADSP_FBUS_1_295,                         0x09, "1295000")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_CORE_FBUS_ERRORS, 16, BE, "", "")
        CONST_TBL_ENTRY(ADSP_CORE_FBUS_FRAMING_ERROR,            0x0000, "Framing error")
        CONST_TBL_ENTRY(ADSP_CORE_FBUS_OVERRUN_ERROR,            0x0001, "Overrun error")
        CONST_TBL_ENTRY(ADSP_CORE_FBUS_PARITY_ERROR,             0x0002, "Parity error")
        CONST_TBL_ENTRY(ADSP_CORE_FBUS_CURRENTP_ERROR,           0x0003, "Parity error")
        CONST_TBL_ENTRY(ADSP_CORE_FBUS_MEDIA_REQ_ERROR,          0x0004, "FBUS media not available")
        CONST_TBL_ENTRY(ADSP_CORE_FBUS_STATE_ERROR,              0x0005, "Statemachine error")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_FBUS_RESP_ERRORS, 16, BE, "", "")
        CONST_TBL_ENTRY(FBUS_SET_OK,                            0x0000, "Baud rate changed")
        CONST_TBL_ENTRY(FBUS_SUPPORT_ERROR,                     0x0001, "Selected baud rate is not supported")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_RTC_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(CALIBRATION_OK,                         0x00, "RTC calibration successful")
        CONST_TBL_ENTRY(CALIBRATION_FAILED,                     0x01, "RTC calibration failed")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_IGNORE_EVENTS, 16, BE, "", "")
        CONST_TBL_ENTRY(IGNORE_OFF,                             0x0000, "All events accepted")
        CONST_TBL_ENTRY(IGNORE_ALL_EVENTS,                      0x0001, "All events ignored")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_ACCESS_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(IO_ACCESS,                              0x00, "IO access to DSP's IO registers")
        CONST_TBL_ENTRY(DBUS_ACCESS,                            0x01, "IO access via DBus")
        CONST_TBL_ENTRY(RFBUS_ACCESS,                           0x02, "IO access via RFBus")
        CONST_TBL_ENTRY(RD_VAR_ACCESS,                          0x03, "Access to DSP variable")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_ACCESS_STATUS, 8, BE, "", "")
        CONST_TBL_ENTRY(IO_ACCESS_OK,                           0x00, "Memory access successful")
        CONST_TBL_ENTRY(IO_ERROR,                               0x01, "Error while memory access")
        CONST_TBL_ENTRY(IO_ERROR_ILLEGAL_ACCESS,                0x02, "Illegal access type")
        CONST_TBL_ENTRY(IO_ERROR_ILLEGAL_VAR,                   0x03, "Illegal variable index")
    CONST_TBL_END

    CONST_TBL_BEGIN(MEMORY_CTRL_SEL, 8, BE, "", "")
        CONST_TBL_ENTRY(CTRL_TO_DSP,                            0x00, "DSP controls the selected memory bank")
        CONST_TBL_ENTRY(CTRL_TO_MCU,                            0x01, "MCU controls the selected memory bank")
    CONST_TBL_END

    CONST_TBL_BEGIN(MEMORY_BANK_SEL, 8, BE, "", "")
        CONST_TBL_ENTRY(MEM_CTRL_PDRAM0,                        0x00, "PDRAM bank 0")
        CONST_TBL_ENTRY(MEM_CTRL_PDRAM1,                        0x01, "PDRAM bank 1")
        CONST_TBL_ENTRY(MEM_CTRL_PDRAM2,                        0x02, "PDRAM bank 2")
        CONST_TBL_ENTRY(MEM_CTRL_PDRAM3,                        0x03, "PDRAM bank 3")
        CONST_TBL_ENTRY(MEM_CTRL_PDRAM4,                        0x04, "PDRAM bank 4")
        CONST_TBL_ENTRY(MEM_CTRL_PDRAM5,                        0x05, "PDRAM bank 5")
        CONST_TBL_ENTRY(MEM_CTRL_PDRAM6,                        0x06, "PDRAM bank 6")
        CONST_TBL_ENTRY(MEM_CTRL_PDRAM7,                        0x07, "PDRAM bank 7")
        CONST_TBL_ENTRY(MEM_CTRL_PDRAM8,                        0x08, "PDRAM bank 8")
        CONST_TBL_ENTRY(MEM_CTRL_PDRAM9,                        0x09, "PDRAM bank 9")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_MEMORY_CTRL_STATUS, 16, BE, "", "")
        CONST_TBL_ENTRY(MEM_CTRL_CHANGE_FAILED,                 0x0000, "Memory control change failed")
        CONST_TBL_ENTRY(MEM_CTRL_CHANGE_OK,                     0x0001, "Memory control changed")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_ERROR_TYPE, 16, BE, "", "")
        CONST_TBL_ENTRY(ADSP_USER_ERROR,                         0x00, "User error")
        CONST_TBL_ENTRY(ADSP_OS_ERROR,                           0x01, "OS kernel error")
        CONST_TBL_ENTRY(ADSP_USER_ERROR_LONG,                    0x02, "User error in long format")
        CONST_TBL_ENTRY(ADSP_OS_ERROR_LONG,                      0x03, "OS kernel error in long format")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_ERROR_SUB_TYPE, 16, BE, "", "")
        CONST_TBL_ENTRY(ADSP_NON_FATAL_ERROR,                    0x00, "Non fatal error")
        CONST_TBL_ENTRY(ADSP_FATAL_ERROR,                        0x01, "Fatal error")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_MSG_LOOP_STATE, 8, BE, "", "")
        CONST_TBL_ENTRY(ADSP_MSG_LOOP_IDLE,                      0x00, "Disable loop")
        CONST_TBL_ENTRY(ADSP_MSG_LOOP_ACTIVE,                    0x01, "Enable loop")
    CONST_TBL_END

    CONST_TBL_BEGIN(W_RAT_SWITCH_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(W_UTRA_FDD,                             0x00, "Switch to UTRA Frequency Division Duplex")
        CONST_TBL_ENTRY(W_UTRA_TDD,                             0x01, "Time Division Duplex")
        CONST_TBL_ENTRY(W_GSM,                                  0x02, "Switch to GSM")
        CONST_TBL_ENTRY(W_RAT_QUERY,                            0x07, "Query of RAT")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_CS_MODE_STATUS, 2, BE, "", "")
        CONST_TBL_ENTRY(ADSP_CS_SUCCESS,                         0x00, "No error")
        CONST_TBL_ENTRY(ADSP_CS_FAILURE_ORIG_STATE_RESTORED,     0x01, "Error, DSP enters previous state")
        CONST_TBL_ENTRY(ADSP_CS_FAILURE_STATE_CORRUPTED,         0x02, "Error, can't recover to previous state")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_RAT, 8, BE, "", "")
        CONST_TBL_ENTRY(ADSP_UTRA_FDD,                           0x00, "UTRA Frequency Division Duplex")
        CONST_TBL_ENTRY(ADSP_UTRA_TDD,                           0x01, "Time Division Duplex")
        CONST_TBL_ENTRY(ADSP_GSM,                                0x02, "GSM")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_CS_MODE_FAILURE_REASON, 6, BE, "", "")
        CONST_TBL_ENTRY(ADSP_CS_NO_FAILURE_REASON,               0x00, "If status is SUCCESS")
        CONST_TBL_ENTRY(ADSP_CS_CHANNEL_OPEN,                    0x01, "Radio channel is open, operation not possible")
    CONST_TBL_END

    CONST_TBL_BEGIN(ADSP_SLEEP_CTRL, 8, BE, "", "")
        CONST_TBL_ENTRY(ADSP_DISABLE_SLEEP,                      0x00, "Sleep disabled")
        CONST_TBL_ENTRY(ADSP_ENABLE_SLEEP,                       0x01, "Sleep enabled")
        CONST_TBL_ENTRY(ADSP_FORCE_SLEEP,                        0x02, "Force DSP to sleep(used for production testing purposes)")
    CONST_TBL_END


    /* Field test display constants */

#define  FIRST_FTD_SUB_BLOCK_ID     0x10
#define  LAST_FTD_SUB_BLOCK_ID      0x28
#define  NUMBER_OF_FTD_SUB_BLOCKS  (LAST_FTD_SUB_BLOCK_ID -  FIRST_FTD_SUB_BLOCK_ID + 1)

    CONSTANT(FIRST_FTD_SUB_BLOCK_ID,                            FIRST_FTD_SUB_BLOCK_ID)
    CONSTANT(LAST_FTD_SUB_BLOCK_ID,                             LAST_FTD_SUB_BLOCK_ID)
    CONSTANT(NUMBER_OF_FTD_SUB_BLOCKS,                          NUMBER_OF_FTD_SUB_BLOCKS)

    FTD_TBL_BEGIN("", "")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_VERSION_1,                  0x10, "", "ADSP SW version 1-12 characters")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_VERSION_2,                  0x11, "", "ADSP SW version 13-24 characters")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_VERSION_3,                  0x12, "", "ADSP SW version 25-36 characters")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_VERSION_DATE,               0x13, "", "ADSP SW version date")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_SPECIFIC_ERR_CNT_1,         0x14, "", "ADSP specific error counter 1")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_SPECIFIC_ERR_CNT_2,         0x15, "", "ADSP specific error counter 2")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_SPECIFIC_ERR_CNT_3,         0x16, "", "ADSP specific error counter 3")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_SPECIFIC_ERR_CNT_4,         0x17, "", "ADSP specific error counter 4")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_SPECIFIC_ERR_CNT_5,         0x18, "", "ADSP specific error counter 5")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_SPECIFIC_ERR_CNT_6,         0x19, "", "ADSP specific error counter 6")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_SPECIFIC_ERR_CNT_7,         0x1A, "", "ADSP specific error counter 7")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_SPECIFIC_ERR_CNT_8,         0x1B, "", "ADSP specific error counter 8")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_APP_START_FAIL_CNT_1,       0x1C, "", "ADSP Application start fail counter 1")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_APP_START_FAIL_CNT_2,       0x1D, "", "ADSP Application start fail counter 2")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_APP_START_FAIL_CNT_3,       0x1E, "", "ADSP Application start fail counter 3")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_APP_START_FAIL_CNT_4,       0x1F, "", "ADSP Application start fail counter 4")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_APP_START_FAIL_CNT_5,       0x20, "", "ADSP Application start fail counter 5")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_APP_START_FAIL_CNT_6,       0x21, "", "ADSP Application start fail counter 6")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_APP_START_FAIL_CNT_7,       0x22, "", "ADSP Application start fail counter 7")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_APP_START_FAIL_CNT_8,       0x23, "", "ADSP Application start fail counter 8")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_TEST_INDEX,                 0x24, "", "Input for ADSP_TEST_DATA sub blocks")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_TEST_DATA_1,                0x25, "", "ADSP Test data 1")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_TEST_DATA_2,                0x26, "", "ADSP Test data 2")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_TEST_DATA_3,                0x27, "", "ADSP Test data 3")
        FTD_TBL_ENTRY_STRING(FTD_SB_ADSP_TEST_DATA_4,                0x28, "", "ADSP Test data 4")
    FTD_TBL_END

    /* RF ASIC type numbers returned in RF ASIC version request */

    CONST_TBL_BEGIN(ADSP_RF_ASIC_VERSION_TYPE, 8, BE, "", "")
        CONST_TBL_ENTRY(RF_IC_HAGAR,                            0x1,  "Hagar")
        CONST_TBL_ENTRY(RF_IC_HELGA,                            0x2,  "Helga")
        CONST_TBL_ENTRY(RF_IC_MJOLNER,                          0x3,  "Mjolner")
        CONST_TBL_ENTRY(RF_IC_REX,                              0x10, "REX")
        CONST_TBL_ENTRY(RF_IC_TEX,                              0x11, "TEX")
        CONST_TBL_ENTRY(RF_IC_KIEKU,                            0x12, "Kieku")
        CONST_TBL_ENTRY(RF_IC_KAIKU,                            0x13, "Kaiku")
    CONST_TBL_END

    /* BIT MAP definitions */

    BIT_TBL_BEGIN(TRACE_STATUS, 16, BE, "", "")
        BIT_TBL_COMMENT(COMMENT_PARAGRAPH, "Trace status(global / default settings). If "
            "TRACE_ON_OFF is enabled all selected traces from trace mask are active "
            "otherwise all are disabled. If TIMESTAMP_ON_OFF is selected system "
            "time is added to each trace and if the FBUS_TRACE is set the FBus "
            "is used for tracing otherwise traces are sent via STI. All FBUS & "
            "STI mode changes has to be done using the Media manager.")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX1", TRACE_ON,                 "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX0", TRACE_OFF,                "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX1X", TIMESTAMP_ON,             "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX0X", TIMESTAMP_OFF,            "")
        BIT_TBL_ENTRY("XXXXXXXXXXX1XXXX", FBUS_TRACE,               "FBus trace active")
        BIT_TBL_ENTRY("XXXXXXXXXXX0XXXX", STI_TRACE,                "STI trace active")
        BIT_TBL_ENTRY("XXXXXXXXXX1XXXXX", MCDI_SEND_TRACE_STATUS,   "MCDI send traces active / inactive")
        BIT_TBL_ENTRY("XXXXXXXXX1XXXXXX", MCDI_RECEIVE_TRACE_STATUS,"MCDI receive traces active / inactive")
        BIT_TBL_ENTRY("XXXXXXXX1XXXXXXX", MADI_SEND_TRACE_STATUS,   "MADI send traces active / inactive")
        BIT_TBL_ENTRY("XXXXXXX1XXXXXXXX", MADI_RECEIVE_TRACE_STATUS,"MADI receive traces active / inactive")
        BIT_TBL_ENTRY("XXXXXX1XXXXXXXXX", DADI_SEND_TRACE_STATUS,   "DADI send traces active / inactive")
        BIT_TBL_ENTRY("XXXXX1XXXXXXXXXX", DADI_RECEIVE_TRACE_STATUS,"DADI receive traces active / inactive")
        BIT_TBL_ENTRY("XXXX1XXXXXXXXXXX", ADSP_CORE_STORE_MASK,      "If 1 Trace mask will be stored to PMM")
        BIT_TBL_ENTRY("XXX1XXXXXXXXXXXX", MEMORY_ALLOC_TRACE_ON,    "")
        BIT_TBL_ENTRY("XXX0XXXXXXXXXXXX", MEMORY_ALLOC_TRACE_OFF,   "")
        BIT_TBL_ENTRY("XX1XXXXXXXXXXXXX", MEMORY_FREE_TRACE_ON,     "")
        BIT_TBL_ENTRY("XX0XXXXXXXXXXXXX", MEMORY_FREE_TRACE_OFF,    "")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH, "Error handler trace mask."
        "If activated and error has occurred the DSP_ERROR_IND message is sent to the device"
        "which activates the traces. If memory dump is enabled the DSP data memory is dumped"
        "with using DSP_DATA_MEMORY_DUMP_IND message when error has occurred.")
    BIT_TBL_BEGIN(TRACE_ERROR_HANDLER, 16, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX1", ERROR_HANDLER_TRACE_ON,        "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX0", ERROR_HANDLER_TRACE_OFF,       "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX1X", ERROR_HANDLER_FORMAT_LONG,     "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX0X", ERROR_HANDLER_FORMAT_SHORT,    "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXX1XX", ERROR_HANDLER_MEMORY_DUMP_ON,  "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXX0XX", ERROR_HANDLER_MEMORY_DUMP_OFF, "")
    BIT_TBL_END

    COMMENT(COMMENT_PARAGRAPH, "Version request selection. The RFIC"
        "version requests are only for ASICs which are connected to RFBus.")
    BIT_TBL_BEGIN(ADSP_VERSION_TYPE, 16, BE, "", "")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX1", ADSP_SW_VERSION, "Request DSP SW version")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX1X", ASIC_VERSION,   "Request ASIC version ID numbers")
    BIT_TBL_END

    BIT_TBL_BEGIN(ADSP_LOAD_MON_CTRL, 8, BE, "", "")
        BIT_TBL_COMMENT(COMMENT_PARAGRAPH, "DSP load monitor control bits")
        BIT_TBL_ENTRY("XXXXXXX1", ADSP_LOAD_MON_IDLE,             "Idle monitor")
        BIT_TBL_ENTRY("XXXXXX1X", ADSP_LOAD_MON_PROC,             "Process monitor")
        BIT_TBL_ENTRY("XXXXX1XX", ADSP_LOAD_MON_10US_SAMPLE_TIME, "10us sample_time")
        BIT_TBL_ENTRY("XXXX1XXX", ADSP_LOAD_MON_NULL_RESULTS,     "results -> null(do not send results)")
    BIT_TBL_END

    BIT_TBL_BEGIN(ADSP_TRACE_GROUPS, 16, BE, "", "")
        BIT_TBL_COMMENT(COMMENT_PARAGRAPH ,"DSP trace group bit masks for trace level selection.")
        BIT_TBL_ENTRY("0000000000000000", ADSP_TRACE_LEVEL_OFF, "Disable all traces")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXXX1", ADSP_TRACE_LEVEL_1, "Trace level 1")
        BIT_TBL_ENTRY("XXXXXXXXXXXXXX1X", ADSP_TRACE_LEVEL_2, "Trace level 2")
        BIT_TBL_ENTRY("XXXXXXXXXXXXX1XX", ADSP_TRACE_LEVEL_3, "Trace level 3")
        BIT_TBL_ENTRY("XXXXXXXXXXXX1XXX", ADSP_TRACE_LEVEL_4, "Trace level 4")
        BIT_TBL_ENTRY("XXXXXXXXXXX1XXXX", ADSP_TRACE_LEVEL_5, "Trace level 5")
        BIT_TBL_ENTRY("XXXXXXXXXX1XXXXX", ADSP_TRACE_LEVEL_6, "Trace level 6")
        BIT_TBL_ENTRY("XXXXXXXXX1XXXXXX", ADSP_TRACE_LEVEL_7, "Trace level 7")
        BIT_TBL_ENTRY("XXXXXXXX1XXXXXXX", ADSP_TRACE_LEVEL_8, "Trace level 8")
        BIT_TBL_ENTRY("XXXXXXX1XXXXXXXX", ADSP_TRACE_LEVEL_9, "Trace level 9")
        BIT_TBL_ENTRY("XXXXXX1XXXXXXXXX", ADSP_TRACE_LEVEL_10, "Trace level 10")
        BIT_TBL_ENTRY("XXXXX1XXXXXXXXXX", ADSP_TRACE_LEVEL_11, "Trace level 11")
        BIT_TBL_ENTRY("XXXX1XXXXXXXXXXX", ADSP_TRACE_LEVEL_12, "Trace level 12")
        BIT_TBL_ENTRY("XXX1XXXXXXXXXXXX", ADSP_TRACE_LEVEL_13, "Trace level 13")
        BIT_TBL_ENTRY("XX1XXXXXXXXXXXXX", ADSP_TRACE_LEVEL_14, "Trace level 14")
        BIT_TBL_ENTRY("X1XXXXXXXXXXXXXX", ADSP_TRACE_LEVEL_15, "Trace level 15")
        BIT_TBL_ENTRY("1XXXXXXXXXXXXXXX", ADSP_TRACE_LEVEL_16, "Trace level 16")
    BIT_TBL_END


    /* --------------------------------------------------------------------- */
    /* Sequences */
    /* --------------------------------------------------------------------- */

    SEQ_BEGIN(DATA_BYTE_PAR, DONT_CREATE_STRUCT, "", "")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, data, "Data", HEX)
    SEQ_END

    SEQ_BEGIN(DATA_WORD, DONT_CREATE_STRUCT, "", "")
        VALUE(16, BE, data, "Data", HEX)
    SEQ_END

    SEQ_BEGIN(DATA_WORD_PAR, DONT_CREATE_STRUCT, "", "")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, data, "Data", HEX)
    SEQ_END

    SEQ_BEGIN(OS_ADSP_TASK_ID_SEQ, DONT_CREATE_STRUCT, "", "")
        ADSP_TASK_ID
    SEQ_END

    SEQ_BEGIN(SIG_ID_SEQ, DONT_CREATE_STRUCT, "", "")
        ADSP_SIGN_ID
    SEQ_END


    /* --------------------------------------------------------------------- */
    /* Messages */
    /* --------------------------------------------------------------------- */

    /* ADSP_FBUS_MODE */

    COMMENT(COMMENT_PARAGRAPH, "This message is used to adjust FBUS speed and timer values.")
    MSG_BEGIN(ADSP_FBUS_MODE_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        MERGE_BEGIN(16, BE, word_1, "First word")
            PROPERTY(PROPERTY_PMD_PARAMETER)
            VALUE_CONST(baud_rate, "Baud rate", FBUS_RATES)
            PROPERTY(PROPERTY_PMD_PARAMETER)
            PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0x01)
            PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0xFF)
            PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, ADSP_SYNC_SENDING_DISABLE)
            VALUE_EX(8, BE, sync_intv, "Sync Sending Interval", DEC, 100, 0, "msec")
        MERGE_END
        MERGE_BEGIN(16, BE, word_2, "Second word")
            PROPERTY(PROPERTY_PMD_PARAMETER)
            PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0x01)
            PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 0xFE)
            PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, ADSP_FBUS_POWERED_DOWN_IMMEDIATELY)
            PROPERTY_VALUE(PROPERTY_ITEM_EXCEPTIONAL_VALUE, ADSP_FBUS_ON_FOREVER)
            VALUE_EX(8, BE, idle_tout, "Idle Timeout", DEC, 100, 0, "msec")
            FILLER(FILLER_FIXED, 8)
        MERGE_END
        FILLER(FILLER_FIXED, 16)
    MSG_END

    MSG_BEGIN(ADSP_FBUS_MODE_RESP, MESSAGE_RESP, "", "")
        MSG_COMMENT(COMMENT_PARAGRAPH, "This message is send after DSP has accomplished FBUS mode change.")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(fbus_error, "Error", ADSP_FBUS_RESP_ERRORS)
    MSG_END

    MSG_PAIR(ADSP_FBUS_MODE_REQ, ADSP_FBUS_MODE_RESP)

    /* ADSP_FBUS_ERROR */

    COMMENT(COMMENT_PARAGRAPH, "This indication is sent via FBUS from DSP to "
        "connected device when FBus error has"
        "been detected. Indication can not be ordered from Communication Layer.")
    MSG_BEGIN(ADSP_FBUS_ERROR_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(error, "Error", ADSP_CORE_FBUS_ERRORS)
    MSG_END


    /* ADSP_VERSION */

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message is used to request DSP SW version. Notice that this is not the same as"
        "server version, which is requested by the message COMM_SERVER_VERSION_GET_REQ.")
    MSG_BEGIN(ADSP_VERSION_REQ, MESSAGE_REQ, "", "") 
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(type, "Version", ADSP_VERSION_TYPE)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message is used to send DSP SW or RFIC version to requester. The version numbers "
        "are in version string where the SW and RFICs versions are separated with space "
        "= 0x96 in ASCII. If both SW & RFIC versions are requested the SW version is always "
        "returned before the RFIC versions. In RFIC version string there are two values xxyy. "
        "xx = RFIC type and yy = RFIC version number.")
    MSG_BEGIN(ADSP_VERSION_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "productinf")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "HDxxx according global.h")
        VALUE(8, BE, product, "Product Project", HEX)
        COMMENT(COMMENT_TEXT, "Length in words")
        REFERENCE(8, BE, length_of_string, "Length of version string", N)
        REFERENCE_TRANSFORM(N, M, ALG_MUL, 2)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        STRING_REF(STRING_ASCII, BE, ADSP_version_string, "Version number", M, ISIHDR_MARKER_ANYSIZE)
    MSG_END

    MSG_PAIR(ADSP_VERSION_REQ, ADSP_VERSION_RESP)


    /* ADSP_MDI_LOOPBACK */

    MSG_BEGIN(ADSP_MDI_LOOPBACK_REQ, MESSAGE_REQ, "", "")
        MSG_COMMENT(COMMENT_PARAGRAPH, "This "
            "message is used to request DSP to echo this message back to the requester via "
            "active media.")
        COMMON_MSG_HDR
        BLOCK_REF(BE, loopback_data, "msg", BLOCK_PN_MSG, 0, 0, 0, REF_AS_MANY_AS_POSSIBLE)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message is used to send received DSP_MDI_LOOPBACK_REQ data back.")
    MSG_BEGIN(ADSP_MDI_LOOPBACK_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        BLOCK_REF(BE, loopback_data, "msg", BLOCK_PN_MSG, 0, 0, 0, REF_AS_MANY_AS_POSSIBLE)
    MSG_END

    MSG_PAIR(ADSP_MDI_LOOPBACK_REQ, ADSP_MDI_LOOPBACK_RESP)


    /* ADSP_MEMORY_READ */

    COMMENT(COMMENT_PARAGRAPH, "This message is "
        "used to request DSP to read selected IO register or DSP variable.")
    MSG_BEGIN(ADSP_MEMORY_READ_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, address, "address of IO register or index to var table", HEX)

        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "memory_select")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(access_types, "Access Types", ADSP_ACCESS_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, read_length, "Number Of Words To Be Read", DEC)

        FILLER(FILLER_FIXED, 16)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "This message "
        "return read data word(s) from selected IO or memory location and the status of access.")
    MSG_BEGIN(ADSP_MEMORY_READ_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "read_param")
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, ADSP_MAX_MEMORY_ACCESS_SIZE)
        REFERENCE(8, BE, read_length, "Number of words", N)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(status, "Status", ADSP_ACCESS_STATUS)

        SEQ_OF_REF(read_data, "Data", DATA_WORD_PAR, N, ISIHDR_MARKER_ANYSIZE)
    MSG_END

    MSG_PAIR(ADSP_MEMORY_READ_REQ, ADSP_MEMORY_READ_RESP)


    /* ADSP_MEMORY_WRITE */

    COMMENT(COMMENT_PARAGRAPH, "This message is "
        "used to write data to DSP's memory or IO register.")
    MSG_BEGIN(ADSP_MEMORY_WRITE_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Address of IO register or index to var table")
        VALUE(16, BE, address, "Address", HEX)

        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "write_param")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(access_types, "Access types", ADSP_ACCESS_TYPE)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, ADSP_MAX_MEMORY_ACCESS_SIZE)
        REFERENCE(8, BE, write_length, "Number of words", N)

        SEQ_OF_REF(write_data, "Data", DATA_WORD_PAR, N, ISIHDR_MARKER_ANYSIZE)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "This message is "
        "used to inform the requester device when write access is completed and if the "
        "error was occurred while access.")
    MSG_BEGIN(ADSP_MEMORY_WRITE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR

        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "status")
        FILLER(FILLER_FIXED, 8)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(access_status, "Status", ADSP_ACCESS_STATUS)
    MSG_END

    MSG_PAIR(ADSP_MEMORY_WRITE_REQ, ADSP_MEMORY_WRITE_RESP)


    /* ADSP_BIT_WRITE_SET */

    COMMENT(COMMENT_PARAGRAPH, "This message "
        "is used to set one or several bits from DSP's memory or IO register.")
    MSG_BEGIN(ADSP_BIT_WRITE_SET_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, address, "Address of IO register or index to var table", HEX)

        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "write_param")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(access_types, "Access types", ADSP_ACCESS_TYPE)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, ADSP_MAX_MEMORY_ACCESS_SIZE)
        REFERENCE(8, BE, write_length, "Number of words", N)

        SEQ_OF_REF(write_data, "Data", DATA_WORD_PAR, N, ISIHDR_MARKER_ANYSIZE)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "This message is "
        "!used to inform the requester device when bit write access is completed and if "
        "the error was occurred while access. ")
    MSG_BEGIN(ADSP_BIT_WRITE_SET_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR

        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "status")
        FILLER(FILLER_FIXED, 8)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(access_status, "Status", ADSP_ACCESS_STATUS)
    MSG_END

    MSG_PAIR(ADSP_BIT_WRITE_SET_REQ, ADSP_BIT_WRITE_SET_RESP)


    /* ADSP_BIT_WRITE_CLEAR */

    COMMENT(COMMENT_PARAGRAPH, "This message "
        "is used to reset one or several bits from DSP's memory or IO space. ")
    MSG_BEGIN(ADSP_BIT_WRITE_CLEAR_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Address of IO register or index to var table")
        VALUE(16, BE, address, "Address", HEX)
        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "write_param")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(access_types, "Access types", ADSP_ACCESS_TYPE)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, ADSP_MAX_MEMORY_ACCESS_SIZE)
        REFERENCE(8, BE, write_length, "Number of words", N)
        SEQ_OF_REF(write_data, "Data", DATA_WORD_PAR, N, ISIHDR_MARKER_ANYSIZE)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "This message is "
        "used to inform the requester device when bit write access is completed and if "
        "the error was occurred while access.")
    MSG_BEGIN(ADSP_BIT_WRITE_CLEAR_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR

        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "status")
        FILLER(FILLER_FIXED, 8)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(access_status, "Status", ADSP_ACCESS_STATUS)
    MSG_END

    MSG_PAIR(ADSP_BIT_WRITE_CLEAR_REQ, ADSP_BIT_WRITE_CLEAR_RESP)


    /* ADSP_BIT_MASK_WRITE */

    COMMENT(COMMENT_PARAGRAPH, "This message "
        "is used to set and reset one or several bits from DSP's memory or IO space. There are own "
        "parameter fields for set mask and clear mask.")
    MSG_BEGIN(ADSP_BIT_MASK_WRITE_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Address of IO register or index to var table")
        VALUE(16, BE, address, "Address", HEX)
        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "write_param")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(access_types, "Access types", ADSP_ACCESS_TYPE)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, ADSP_MAX_MEMORY_ACCESS_SIZE)
        REFERENCE(8, BE, write_length, "Number of words", N)
        SEQ_OF_REF(set_data,   "Data to be set", DATA_WORD_PAR, N, ISIHDR_MARKER_ANYSIZE)
        SEQ_OF_REF(clear_data, "Data to be cleared", DATA_WORD_PAR, N, ISIHDR_MARKER_ANYSIZE)
    MSG_END

    MSG_BEGIN(ADSP_BIT_MASK_WRITE_RESP, MESSAGE_RESP, "", "")
        MSG_COMMENT(COMMENT_PARAGRAPH, "This message is "
            "used to inform the requester device when bit mask write access is completed and if "
            "the error was occurred while access.")
        COMMON_MSG_HDR

        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "status")
        FILLER(FILLER_FIXED, 8)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(access_status, "Status", ADSP_ACCESS_STATUS)
    MSG_END

    MSG_PAIR(ADSP_BIT_MASK_WRITE_REQ, ADSP_BIT_MASK_WRITE_RESP)


    /* Trace messages */

    /* ADSP_TASKSWAP_IND */

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message indicates OS taskswap. The message is sent whenever the OS swap from "
        "one task to another and the taskswap trace is enabled. The process "
        "id indicates the process to swap to. Indication is sent to resource, which has "
        "activated the traces. Indication can not be ordered from Communication Layer.")
    MSG_BEGIN(ADSP_TASKSWAP_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        ADSP_TASK_ID
        ADSP_OS_TIMESTAMP
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message indicates that a signal has been sent between 2 processes. The "
        "message is sent whenever the OS signal is send or received and the corresponding "
        "trace is enabled. The actual trace message can contain signal ID/signal data/time stamp "
        "depending on the SIGTYPE parameter. Indication is sent to resource, which has "
        "activated the traces. Indication can not be ordered from Communication Layer.")
    MSG_BEGIN(ADSP_SIGNAL_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 8)
        PROPERTY_STRING(PROPERTY_PMD_ANCHOR, "ADSP_SIGNAL_ID")
        SEQ_OF_REF(data_w, "Data", DATA_BYTE_PAR, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_ANYSIZE)
    MSG_END


    /* ADSP_ERROR_IND */

    SEQ_BEGIN(ERROR_SEQ, CREATE_STRUCT, "", "")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED, "error_code_lsw")
        VALUE(32, BE, error_code_msw, "Main Error Code", HEX)

        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED, "extra_error_code_lsw")
        VALUE(32, BE, extra_error_code_msw, "Extra Error Info", HEX)
    SEQ_END

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message indicates that a system error or user error has occurred. The "
        "indication message contains the error code and extra error parameter and "
        "depending of trace parameters it can also contain the time stamp information.")
    MSG_BEGIN(ADSP_ERROR_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        ADSP_TASK_ID
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(type, "Error type", ADSP_ERROR_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sub_type, "Error sub type", ADSP_ERROR_SUB_TYPE)
        SEQ_OF(error_codes, "Error code & extra code", ERROR_SEQ, 1)
        ADSP_OS_TIMESTAMP
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, pid_list_latest_entry_index, "Index to last signal entry in PID list", DEC)
        SEQ_OF(pid_list, "List of process ID's before error", OS_ADSP_TASK_ID_SEQ, 32)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, rx_msg_latest_entry_index, "Index to last signal entry in rx signal list", DEC)
        SEQ_OF(rx_msg_id_list, "Received signals", SIG_ID_SEQ, 16)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, tx_msg_latest_entry_index, "Index to last signal entry in tx signal list", DEC)
        SEQ_OF(tx_msg_id_list, "Send signals", SIG_ID_SEQ, 16)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, warn_latest_entry_index, "Index to last signal entry in warning list", DEC)
        SEQ_OF(warning_list, "List of previous warning numbers", ERROR_SEQ, 8)
        SEQ_OF(extra_info, "Extra debug info", DATA_WORD_PAR, 4)
    MSG_END


    /* ADSP_DATA_MEMORY_DUMP */

    COMMENT(COMMENT_PARAGRAPH, "This message will "
        "generate DSP fatal error and DSP will start to dump the data memory with DSP_DATA_MEMORY_DUMP_IND "
        "messages. This is used for debugging purposes and it is not allowed in official sale sw releases.")
    MSG_BEGIN(ADSP_DATA_MEMORY_DUMP_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message is used to send whole DSP data memory if error has occurred and memory dump is selected "
        "from trace mask. NOTE! This feature is not allowed in official sale sw releases.")
    MSG_BEGIN(ADSP_DATA_MEMORY_DUMP_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR

        MERGE_BEGIN(32, BE, num_of_words_addr, "Number of words")
            REFERENCE(8, BE, num_of_words, "Number of words", N)
            PROPERTY(PROPERTY_PMD_PARAMETER)
            VALUE(24, BE, address_msb, "Address of data", HEX)
        MERGE_END

        SEQ_OF_REF(read_data, "Data", DATA_WORD_PAR, N, ISIHDR_MARKER_ANYSIZE)
    MSG_END


    /* ADSP_USER_TRACE_IND */

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message is used to carry free formatted user data out of the process. The user "
        "can use this message for tracing anything at the inside the process. The actual "
        "data part of this message is not decoded by the PCMess. There is no OS signal for "
        "this, because trace data is passed via function call. Indication can not be "
        "ordered from Communication Layer. Indication is sent to resource, which has "
        "activated the traces.")
    MSG_BEGIN(ADSP_USER_TRACE_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        SEQ_OF_REF(data_word, "Data", DATA_WORD_PAR, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_ANYSIZE)
    MSG_END


    /* ADSP_ALLOC_FREE_IND */

    SEQ_BEGIN(ADSP_ALLOC_DATA_SEQ, DONT_CREATE_STRUCT, "", "")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, size, "Size", DEC)
    SEQ_END

    SEQ_BEGIN(ADSP_ALLOC_DATA_TIME_SEQ, DONT_CREATE_STRUCT, "", "")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, size, "Size", DEC)
        ADSP_OS_TIMESTAMP
    SEQ_END

    SEQ_BEGIN(ADSP_FREE_DATA_TIME_SEQ, DONT_CREATE_STRUCT, "", "")
        ADSP_OS_TIMESTAMP
    SEQ_END

    SEQ_BEGIN(ADSP_MEMORY_TRACE_SEQ, CREATE_STRUCT, "", "")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Address of the allocated / freed memory")
        VALUE(16, BE, address, "Address", HEX)

        MERGE_BEGIN(16, BE, os_data, "OS parameters")
            PROPERTY(PROPERTY_PMD_PARAMETER)
            VALUE(8, BE, process, "Process ID", HEX)
            PROPERTY(PROPERTY_PMD_PARAMETER)
            VALUE(4, BE, pool, "Pool ID", HEX)
            PROPERTY(PROPERTY_PMD_PARAMETER)
            REFERENCE_CONST(block_type, "Block type", ADSP_MEM_SIZE_TIME_SEL, ADSP_MEMORY_TRACE_TABLE)
        MERGE_END

        CHOICE_BEGIN(mem_alloc_block, "Size and time stamp selection", ADSP_MEM_SIZE_TIME_SEL)
            CASE(ADSP_ALLOC_DATA,      ADSP_ALLOC_DATA_SEQ)
            CASE(ADSP_ALLOC_DATA_TIME, ADSP_ALLOC_DATA_TIME_SEQ)
            CASE(ADSP_FREE_DATA_TIME,  ADSP_FREE_DATA_TIME_SEQ)
        CHOICE_END
    SEQ_END

    COMMENT(COMMENT_PARAGRAPH, "Message "
        "is used to trace memory allocations or deallocations. Memory traces are activated "
        "from DSP trace mask.")
    MSG_BEGIN(ADSP_ALLOC_FREE_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        COMMENT(COMMENT_TEXT, "Number of alloc / free blocks in message")
        REFERENCE(8, BE, num_blocks, "Number of blocks", N)
        SEQ_OF_REF(alloc_data, "Data", ADSP_MEMORY_TRACE_SEQ, N, ISIHDR_DONT_GENERATE)
    MSG_END


    /* ADSP_TRACES_LOST_IND */

    COMMENT(COMMENT_PARAGRAPH, "This message is used to "
        "indicate that some of the traces are lost(DSP trace buffer has overflowed).")
    MSG_BEGIN(ADSP_TRACES_LOST_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, number_of_lost_traces, "Number Of Lost Traces", DEC)
    MSG_END


    /* ADSP_TRACE_MASK */

    COMMENT(COMMENT_PARAGRAPH, "With this message "
        "the OS trace mask content is queried from the DSP.")
    MSG_BEGIN(ADSP_TRACE_MASK_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "This message "
        "gives the contents of OS trace masks at the DSP.")
    MSG_BEGIN(ADSP_TRACE_MASK_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(trace_stat, "Trace status", TRACE_STATUS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(16, BE, trace_mask_length, "Trace mask length", N)
        SEQ_OF_REF(trace_mask, "Trace mask", DATA_WORD, N, ISIHDR_MARKER_ANYSIZE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(error_handler_stat, "Error handler trace", TRACE_ERROR_HANDLER)
        SEQ_OF(trace_swap, "Task swap traces", DATA_WORD_PAR, 4)
    MSG_END

    MSG_PAIR(ADSP_TRACE_MASK_REQ, ADSP_TRACE_MASK_RESP)


    /* ADSP_TRACE_MASK_UPDATE */

    COMMENT(COMMENT_PARAGRAPH, "This message is used to modify trace mask table.")
    MSG_BEGIN(ADSP_TRACE_MASK_UPDATE_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(trace_stat, "Trace status", TRACE_STATUS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(16, BE, trace_mask_length, "Trace mask length", N)
        SEQ_OF_REF(trace_mask, "Trace mask", DATA_WORD, N, ISIHDR_MARKER_ANYSIZE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(error_handler_stat, "Error handler trace", TRACE_ERROR_HANDLER)
        SEQ_OF(trace_swap, "Task swap traces", DATA_WORD_PAR, 4)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "This message is send after trace masks are updated.")
    MSG_BEGIN(ADSP_TRACE_MASK_UPDATE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    MSG_PAIR(ADSP_TRACE_MASK_UPDATE_REQ, ADSP_TRACE_MASK_UPDATE_RESP)


    /* ADSP_USER_DATA */

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message is used to send OS process specific data into task. There must exist "
        "OS signal to carry this data into target OS process. ISI header is included "
        "into OS signal. IGNORE_EVENTS field can be used to set task to silent mode.")
    MSG_BEGIN(ADSP_USER_DATA_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(ignore, "Events accepted or ignored", ADSP_IGNORE_EVENTS)
        ADSP_TASK_ID
        SEQ_OF_REF(data_w, "User data", DATA_WORD_PAR, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_ANYSIZE)
    MSG_END


    /* ADSP_SIGNAL */

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message is used to send DSP internal OS signal from external device."
        "ISI header is removed before sending as OS signal.")
    MSG_BEGIN(ADSP_SIGNAL_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        ADSP_TASK_ID
        ADSP_SIGN_ID
        SEQ_OF_REF(data_w, "OSE signal data", DATA_WORD_PAR, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_ANYSIZE)
    MSG_END


    /* ADSP_RTC_CALIBRATION */

    COMMENT(COMMENT_PARAGRAPH, "This message "
        "is used to request fast clock and slow sleep clock ratio from DSP. The same message can "
        "be used in production to check the functionality of sleep clock.")
    MSG_BEGIN(ADSP_RTC_CALIBRATION_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "Calculated "
        "calibration value is the ratio between fast clock and slow sleep clock. For example "
        "with 19.2MHz system clock and with 32768Hz sleep clock the ideal clock ratio result "
        "is 585.9375. Calibration result is 32-bit value in Q16 format. CALIBRATION_FAILED "
        "status is returned, when calibration value could not be calculated. The message usage in "
        "production can be optimized by calculating only the integer part of ratio in local mode, "
        "which is enough for functionality check.")
    MSG_BEGIN(ADSP_RTC_CALIBRATION_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR

        COMMENT(COMMENT_TEXT, "rtc_status")
        FILLER(FILLER_FIXED, 8)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(status, "Calibration Status", ADSP_RTC_STATUS)

        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED, "rtc_calib_value_lsb")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(32, BE, rtc_calib_value_msb, "Sleep clock ratio", Q16)
    MSG_END

    MSG_PAIR(ADSP_RTC_CALIBRATION_REQ, ADSP_RTC_CALIBRATION_RESP)


    /* ADSP_MEMORY_CONTROL */

    COMMENT(COMMENT_PARAGRAPH, "This message "
        "is used to change the control of memory banks between the MCU and DSP.")
    MSG_BEGIN(ADSP_MEMORY_CONTROL_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR

        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "memory_ctrl")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(memory_ctrl_sel, "Memory control selection", MEMORY_CTRL_SEL)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(memory_bank_sel, "Memory bank selection", MEMORY_BANK_SEL)

        FILLER(FILLER_FIXED, 16)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "This message "
        "informs if the control of requested memory bank can not be changed.")
    MSG_BEGIN(ADSP_MEMORY_CONTROL_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(memory_ctrl_status, "Status", ADSP_MEMORY_CTRL_STATUS)
        FILLER(FILLER_FIXED, 16)
    MSG_END

    MSG_PAIR(ADSP_MEMORY_CONTROL_REQ, ADSP_MEMORY_CONTROL_RESP)


    /* ADSP_MSG_LOOP */

    COMMENT(COMMENT_PARAGRAPH, "This message "
        "is used to enable or disable message loop. With this message any message from any "
        "resource can be selected to be looped back to sender. ID for received message "
        "tells, which message is looped and ID for sent message tells the ID of response "
        "message. When messages are looped, sender and receiver objects and devices are exchanged.")
    MSG_BEGIN(ADSP_MSG_LOOP_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR

        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "state_resource")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(state, "Loop state", ADSP_MSG_LOOP_STATE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(loop_resource, "Loop resource", PN_RESOURCE)

        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, received_msg_id, "ID for received message", HEX)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, sent_msg_id, "ID for sent message", HEX)
    MSG_END

    MSG_BEGIN(ADSP_MSG_LOOP_RESP, MESSAGE_RESP, "", "")
        MSG_COMMENT(COMMENT_PARAGRAPH, "Response to "
            "message loop request. The data in the message is zero.")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    MSG_PAIR(ADSP_MSG_LOOP_REQ, ADSP_MSG_LOOP_RESP)


    /* ADSP_SWDL_START_IND */

    COMMENT(COMMENT_PARAGRAPH, "SW downloading "
        "start indication is sent when CDSP start to download sw from flash. The indication "
        "message is sent to device which has activated the traces.")
    MSG_BEGIN(ADSP_SWDL_START_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "SW downloading "
        "stop indication is sent when CDSP stop to download sw from flash. The indication "
        "message is sent to device which has activated the traces.")
    MSG_BEGIN(ADSP_SWDL_STOP_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        FILLER(FILLER_FIXED, 16)
    MSG_END


    /* ADSP_CS_MODE */

    COMMENT(COMMENT_PARAGRAPH, "This message "
        "is used to config operating mode of DSP CS. "
        "Message can be sent when DSP CS server is active, to force leaving WCDMA or GSM or "
        "to request current mode of DSP CS server. "
        "Mode switch is not possible, if any radio channel is open in DSP. "
        "(Switch is rejected, query accepted) "
        "Mode switch is buffered, if timed radio channel disconnection is pending on DSP.")
    MSG_BEGIN(ADSP_CS_MODE_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(mode, "Mode", W_RAT_SWITCH_TYPE)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message is used to report "
        "starting of mode switch/mode query procedure or report "
        "that initialization of DSP CS Server has started.")
    MSG_BEGIN(ADSP_CS_MODE_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        MERGE_BEGIN(8, BE, stat, "Status & reason")
            PROPERTY(PROPERTY_PMD_PARAMETER)
            VALUE_CONST(fail_reas, "Failure reason", ADSP_CS_MODE_FAILURE_REASON)   /* 6bits */
            PROPERTY(PROPERTY_PMD_PARAMETER)
            VALUE_CONST(status, "Operation status", ADSP_CS_MODE_STATUS)         /* 2 bits */    
        MERGE_END 
    MSG_END

    MSG_PAIR(ADSP_CS_MODE_REQ, ADSP_CS_MODE_RESP)


    /* ADSP_CS_MODE_IND */

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message is used to indicate, that DSP CS Server is activated "
        "or commanded mode switch is completed or to report result for state query. "
        "If SW download failure occurs, DSP does not send this message.")
    MSG_BEGIN(ADSP_CS_MODE_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(mode, "Mode Of Server", ADSP_RAT)
    MSG_END


    /* ADSP_PRODUCT_INFO_IND */

    COMMENT(COMMENT_PARAGRAPH, "This "
        "message is used to indicate, that core sw is up and running and DSP can start "
        "to request tuning values etc. from MCU.")
    MSG_BEGIN(ADSP_PRODUCT_INFO_IND, MESSAGE_IND, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, profile, "Product Profile", DEC)
    MSG_END


    /* ADSP_SLEEP */

    COMMENT(COMMENT_PARAGRAPH, "Allow or disallow DSP to go to sleep")
    MSG_BEGIN(ADSP_SLEEP_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR

        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "sleep_enable")
        COMMENT(COMMENT_PARAGRAPH, "Reservation for submessage ID")
        FILLER(FILLER_FIXED, 8)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(enable_sleep, "Sleep selection", ADSP_SLEEP_CTRL)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "Response to sleep enable / disable request")
    MSG_BEGIN(ADSP_SLEEP_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR

        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "sleep_status")
        COMMENT(COMMENT_PARAGRAPH, "Reservation for submessage ID")
        FILLER(FILLER_FIXED, 8)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(sleep_stat, "Sleep status", ADSP_SLEEP_CTRL)
    MSG_END

    MSG_PAIR(ADSP_SLEEP_REQ, ADSP_SLEEP_RESP)


    /* ADSP_LOAD_MONITOR */

    COMMENT(COMMENT_PARAGRAPH, "Controls the DSP load monitoring features")
    MSG_BEGIN(ADSP_LOAD_MONITOR_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR

        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "monitor_control")
        COMMENT(COMMENT_PARAGRAPH, "Reservation for submessage ID")
        FILLER(FILLER_FIXED, 8)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(mon_ctrl, "Control bits", ADSP_LOAD_MON_CTRL)

        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Timer ticks or 10us * sample_time depending the bit in monitor_control")
        VALUE(16, BE, sample_time, "Sample time", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Number of samples needed to calculate one result")
        VALUE(16, BE, samples, "Number of samples", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "If 0, continuous.")
        VALUE(16, BE, results, "Number of results", DEC)
    MSG_END

    SEQ_BEGIN(ADSP_IDLE_MON_SEQ, DONT_CREATE_STRUCT, "", "")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, sample_time, "Sample time", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, ADSP_MAX_NUM_OF_LOAD_RESULTS)
        REFERENCE(16, BE, samples, "Number of samples", SAMPLES)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED, "applications_lo")
        VALUE(32, BE, applications_hi, "Active Applications", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Counts down the results. 1 = last, 0 = continuous")
        VALUE(16, BE, result_counter, "Result counter", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, successive_max_load, "Maximum number of consecutive load periods", DEC)
        SEQ_OF_REF(data, "Data", DATA_WORD_PAR, SAMPLES, ISIHDR_MARKER_ANYSIZE)
    SEQ_END

    SEQ_BEGIN(ADSP_PROC_MON_SEQ, DONT_CREATE_STRUCT, "", "")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, sample_time, "Sample time", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(16, BE, samples, "Number of samples", DEC)

        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_STRING(PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED, "applications_lo")
        VALUE(32, BE, applications_hi, "Active Applications", DEC)

        PROPERTY(PROPERTY_PMD_PARAMETER)
        COMMENT(COMMENT_TEXT, "Counts down the results. 1 = last, 0 = continuous")
        VALUE(16, BE, result_counter, "Result counter", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, ADSP_MAX_NUM_OF_LOAD_RESULTS)
        REFERENCE(16, BE, processes, "Number of processes", PROCESSES)
        SEQ_OF_REF(data, "Data", DATA_WORD_PAR, PROCESSES, ISIHDR_MARKER_ANYSIZE)
    SEQ_END

    COMMENT(COMMENT_PARAGRAPH, "Message for "
        "delivering load monitor measurements")
    MSG_BEGIN(ADSP_LOAD_MONITOR_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR

        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "result_type_info")
        COMMENT(COMMENT_PARAGRAPH, "If result_type == DSP_IDLE_MON idle results are returned and "
            "if result_type == DSP_PROC_MON process monitor results are returned.")
        REFERENCE_CONST(result_type, "Result type", RESULT_TYPE, ADSP_LOAD_MONITOR_TYPE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(mon_ctrl, "Info bits", ADSP_LOAD_MON_CTRL)

        CHOICE_BEGIN(results, "Results", RESULT_TYPE)
            CASE(ADSP_IDLE_MON, ADSP_IDLE_MON_SEQ)
            CASE(ADSP_PROC_MON, ADSP_PROC_MON_SEQ)
        CHOICE_END
    MSG_END

    MSG_PAIR(ADSP_LOAD_MONITOR_REQ, ADSP_LOAD_MONITOR_RESP)


    /* ADSP_SET_TRACE_LEVEL */

    COMMENT(COMMENT_PARAGRAPH, "Trace "
        "level selection. Message is used to activate or deactivate group of DSP traces.")
    MSG_BEGIN(ADSP_SET_TRACE_LEVEL_REQ, MESSAGE_REQ, "", "")
        COMMON_MSG_HDR
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(trace_group, "Trace group mask", ADSP_TRACE_GROUPS)
    MSG_END

    COMMENT(COMMENT_PARAGRAPH, "Response "
        "to trace level selection")
    MSG_BEGIN(ADSP_SET_TRACE_LEVEL_RESP, MESSAGE_RESP, "", "")
        COMMON_MSG_HDR
        PROPERTY_STRING(PROPERTY_ISIHDR_VARNAME_16, "status")
        FILLER(FILLER_FIXED, 8)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(stat, "Trace group set status", OK_FAIL)
    MSG_END

    MSG_PAIR(ADSP_SET_TRACE_LEVEL_REQ, ADSP_SET_TRACE_LEVEL_RESP)


    /* ADSP5 messages */

    MSG_BEGIN(ADSP_DSP5_MSG_ID1, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID2, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID3, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID4, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID5, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID6, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID7, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID8, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID9, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID10, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID11, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID12, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID13, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID14, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID15, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

    MSG_BEGIN(ADSP_DSP5_MSG_ID16, MESSAGE_NTF, "", "")
        COMMON_MSG_HDR
    MSG_END

RES_END


/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */


/* End of file autogen_dsp_core.h */
