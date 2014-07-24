/*
NOKIA                                                          CONFIDENTIALITY
Operation System Services
Engine SW
Timo Toivola



                  MTC Server ISI Message Include File
                  --------------------------------
                  SW Include Document - ANSI C/C++



Continuus Ref:
--------------
database:        https://gerrit.nokia.com/r/gitweb?p=s40_sw/ng.git;a=tree

project path:    s40_swcommon_swglobal_interfacecoresw_interfacecoresw_public

name:            mtc_isi.h

version:         022.000

type:            incl

instance:        -


ISI header file for Mobile Terminal Controller Server

Current   ISI Version : 022.000
Supported ISI Versions: 017.000, 017.001, 017.002, 017.003, 017.004, 017.005, 
                        017.006, 017.007, 017.008, 017.009, 017.010, 017.011, 
                        017.012, 017.013, 017.014, 017.015, 017.016, 017.017, 
                        017.018, 017.019, 018.000, 018.002, 018.003, 019.000, 
                        019.001, 020.000, 021.000, 022.000

Generated with autogen version 11w35 on 04-Jun-2012 11:34:37
DO NOT EDIT - changes will be lost at next autogeneration

Copyright (c) Nokia Corporation. All rights reserved.


ISI version change history

Version     : 022.000    NON-DRAFT   04-Jun-2012    Saku Kiiskinen
Reason      : Accept360
Reference   : 2742169: Remove ICF_PN_MEDIA_ flags and usage of those
Description : PERF_IRDA_SUB_SYSTEM removed from PERF_SUB_SYSTEM_ID.

Version     : 021.000    NON-DRAFT   16-Jan-2012    Pasi Tolonen
Reason      : Change request
Reference   : ADB for SWAM PT12010653099 for interface CR.
Description : Changed Message MTC_RESET_GENERATE_REQ
              Discontinued Entry MTC_NOS_READY in MTC_ACTION
              Discontinued Entry MTC_SOS_READY in MTC_ACTION
              Discontinued Entry MTC_SOS_START in MTC_ACTION
              Discontinued Constant table MTC_DEVICE_INFO
              Discontinued Entry MTC_CMT_ONLY_MODE in MTC_NOT_VALID
              Discontinued Entry MTC_POWER_KEY_PRESS_TOO_SHORT in MTC_POWER_OFF_INFO
              Discontinued Entry MTC_DEVICE_RESET in MTC_RESET_TYPE
              Discontinued Entry MTC_RESET_SOS_RESET in MTC_RESET_TYPE_HIDDEN
              Discontinued Entry MTC_CMT_ONLY_MODE in MTC_STATE_CONSTANTS
              Discontinued Entry MTC_RF_INACTIVE in MTC_STATE_CONSTANTS
              Discontinued Entry MTC_WATCHDOG_ADSP in MTC_WD_TYPE
              Cellmo support removed. 

Version     : 020.000    NON-DRAFT   08-Apr-2011    Harri Turunen
Reason      : Change request
Reference   : ADB for SWAM HT11032849362 for interface CR.
Description : Discontinued Entry PERF_CALIBRATION_FAIL in PERF_VCORE_CALIB_STATUS
              Added Entry PERF_CALIBRATION_FAIL_I2C to PERF_VCORE_CALIB_STATUS
              Added Entry PERF_CALIBRATION_FAIL_LDSP_AUTH_FAILS to PERF_VCORE_CALIB_STATUS
              Added Entry PERF_CALIBRATION_FAIL_LDSP_NOT_RESPONDING to PERF_VCORE_CALIB_STATUS
              Added Entry PERF_CALIBRATION_FAIL_LDSP_WRONG_VERSION to PERF_VCORE_CALIB_STATUS
              Added Entry PERF_CALIBRATION_FAIL_NO_LDSP to PERF_VCORE_CALIB_STATUS
              Added Entry PERF_CALIBRATION_FAIL_RND_FLAG_ENABLED to PERF_VCORE_CALIB_STATUS
              Added Entry PERF_CALIBRATION_FAIL_WRONG_ASIC_SPEED to PERF_VCORE_CALIB_STATUS
              Added Entry PERF_CALIBRATION_OK_CALIBRATION_DISABLED to PERF_VCORE_CALIB_STATUS
              Smartreflex calibration status table updated. 

Version     : 019.001    NON-DRAFT   24-Nov-2010    Pasi Tolonen
Reason      : Change request
Reference   : ADB for SWAM PT10112454688 for interface CR.
Description : Modem reset suppport. Obsolete RAT IFs removed. 

Version     : 019.000    NON-DRAFT   28-Apr-2010    Timo Toivola
Reason      : Change request
Reference   : ADB for SWAM TT09052132997 for interface CR.
Description : Only version number increased 

Version     : 018.003    NON-DRAFT   14-Dec-2009    Timo Toivola
Reason      : Change request
Reference   : ADB for SWAM TT09052132997 for interface CR.
Description : Legacy messages removed RM-RIM ID: 417-48390

Version     : 018.002    NON-DRAFT   16-Jun-2009    Harri Turunen
Reason      : Change request
Reference   : ADB for SWAM HT09060947733 for interface CR.
Description : Added Message PERF_GET_REQ
              Added Message PERF_GET_RESP
              Added Subblock PERF_SB_PERFORMANCE_SETTING
              New msg PERF_GET_REQ/RESP RM-RIM ID: 417-44629

Version     : 018.000    NON-DRAFT   05-Feb-2008    Timo Toivola
Reason      : Change request
Reference   : ADB for SWAM TT08020542226 for interface CR.
Description : Changed Message MTC_WATCHDOG_CONTROL_RESP
              Added Entry MTC_RESET_REQUIRED to MTC_STATUS_INFO
              Watchdog control support for modems RM-RIM ID: 403-3284

Version     : 017.019    NON-DRAFT   20-Jun-2007    Harri Turunen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM HT07061549310. 
Description : Added Subblock PERF_SB_HW_CONF_VCORE_PROD to PERF_INFO_RESP
              Added Subblock PERF_SB_HW_CONF_VCORE_PROD
              Discontinued Subblock PERF_SB_HW_CONF_VCORE_PROD_1ST
              Discontinued Subblock PERF_SB_HW_CONF_VCORE_PROD_CUR
              Added Constant table PERF_VCORE_CALIB_INFO
              New sb, PERF_SB_HW_CONF_VCORE_PROD RM-RIM ID: 010-33620

Version     : 017.018    NON-DRAFT   16-May-2007    Harri Turunen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM HT07043054138. 
Description : Added Message PERF_INFO_REQ
              Added Message PERF_INFO_RESP
              Added Sequence PERF_HW_CONF_FREQ_SEQ
              Added Sequence PERF_HW_CONF_VCORE_SEQ
              Added Subblock PERF_SB_HW_CONF_VCORE
              Added Subblock PERF_SB_HW_CONF_VCORE_PROD_1ST
              Added Subblock PERF_SB_HW_CONF_VCORE_PROD_CUR
              Added Bitmask table PERF_INFO_DATA
              Added Constant table PERF_VCORE_CALIB_STATUS
              Added Constant table PERF_VCORE_VSEL_MODE
              New message, PERF_INFO_REQ/RESP RM-RIM ID: 010-33620

Version     : 017.017    NON-DRAFT   20-Dec-2006    Pasi Tolonen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM PT06121537900. 
Description : Added Message MTC_DSP_GENIO_CONFIG_NTF
              New notification MTC_DSP_GENIO_CONFIG_NTF RM-RIM ID: 010-31899

Version     : 017.016    NON-DRAFT   18-Dec-2006    Harri Turunen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM HT06121148817. 
Description : Added Subblock PERF_SB_PERFORMANCE to PERF_SET_REQ
              Added Subblock PERF_SB_PERFORMANCE
              Added Entry PERF_AUDIO_SUB_SYSTEM to PERF_SUB_SYSTEM_ID
              Added Entry PERF_BT_SUB_SYSTEM to PERF_SUB_SYSTEM_ID
              Added Entry PERF_CAMERA_SUB_SYSTEM to PERF_SUB_SYSTEM_ID
              Added Entry PERF_DISPLAY_SUB_SYSTEM to PERF_SUB_SYSTEM_ID
              Added Entry PERF_MEMORY_SUB_SYSTEM to PERF_SUB_SYSTEM_ID
              Added Entry PERF_SECURITY_SUB_SYSTEM to PERF_SUB_SYSTEM_ID
              Added Entry PERF_USB_SUB_SYSTEM to PERF_SUB_SYSTEM_ID
              Added Entry PERF_VIDEO_SUB_SYSTEM to PERF_SUB_SYSTEM_ID
              Added Entry PERF_WLAN_SUB_SYSTEM to PERF_SUB_SYSTEM_ID
              Added Entry PERF_NO_SERVICE to PERF_SUB_SYSTEM_SERVICE
              Added Constant table PERF_VALUE_UNIT
              New clients and sub-block for PERF_SET_REQ RM-RIM ID:
              010-28738, 010-28746, 010-28745

Version     : 017.015    NON-DRAFT   31-Oct-2006    Harri Turunen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM HT06102436714. 
Description : Added Entry PERF_NOS_LOAD_OFF to PERF_STATE_REQ_INFO
              Added Entry PERF_NOS_LOAD_ON to PERF_STATE_REQ_INFO
              Added Entry PERF_SUB_SYSTEM_OFF to PERF_STATE_REQ_INFO
              Added Entry PERF_SUB_SYSTEM_ON to PERF_STATE_REQ_INFO
              New reasons for PERF_STATE_REQ RM-RIM ID: 010-28749

Version     : 017.014    NON-DRAFT   15-Sep-2006    Harri Turunen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM HT06090759277. 
Description : Added Message PERF_SETTINGS_WRITE_REQ
              Added Message PERF_SETTINGS_WRITE_RESP
              Added Message PERF_STATE_REQ
              Added Message PERF_STATE_RESP
              Added Subblock PERF_SB_OPERATING_POINT
              Added Subblock PERF_SB_SERVICE_SETTING
              Added Constant table PERF_STATE_REQ_INFO
              Added Entry PERF_HAL_FAIL to PERF_STATUS_INFO
              Added Entry PERF_NOT_ACTIVE to PERF_STATUS_INFO
              New message pairs for Performance Manager PERF_STATE_REQ/RESP
              and PERF_SETTINGS_WRITE_REQ/RESP. RM-RIM ID: 010-28280

Version     : 017.013    NON-DRAFT   25-Aug-2006    Harri Turunen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM HT06082534368. 
Description : Added Message PERF_SET_REQ
              Added Message PERF_SET_RESP
              Added Constant table PERF_STATUS_INFO
              Added Constant table PERF_SUB_SYSTEM_ID
              Added Constant table PERF_SUB_SYSTEM_SERVICE
              New message pair for Performance Manager PERF_SET_REQ/RESP.
              RM-RIM ID: 010-27564

Version     : 017.012    NON-DRAFT   19-Jun-2006    Pasi Tolonen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM PT06061939747. 
Description : New message pair for reading Vcore value from PMM:
              MTC_VCORE_READ_REQ/RESP. RM-RIM ID: 009-26955

Version     : 017.011    NON-DRAFT   14-Mar-2006    Vesa P.Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM VK06031443009. 
Description : MTC_SW_RESET taken into use in the MTC_STATE_INFO_IND message.
              RM-RIM ID: 009-24821

Version     : 017.010    NON-DRAFT   03-Jan-2006    Vesa P.Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM VK06010348611. 
              Inspection minutes: ADB for SWAM VK06010350953. 
Description : Added Entry MTC_RF_WIFI to MTC_RF_STATUS
              New constant, MTC_RF_WIFI added. RM-RIM ID: 009-22663

Version     : 017.009    NON-DRAFT   12-Oct-2005    Vesa P.Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM VK05092043422. 
              Inspection minutes: ADB for SWAM VK05092745290. 
Description : Added Message MTC_RAT_INFO_NTF
              Added Subblock INFO_SB_ACCELEROMETER_VERSION
              Added Subblock INFO_SB_APE_ADSP_SW
              Added Subblock INFO_SB_APE_BT_VERSION
              Added Subblock INFO_SB_APE_CUI_LCD_VERSION
              Added Subblock INFO_SB_APE_DVB_H_RX_BOOTLOADER_VER
              Added Subblock INFO_SB_APE_DVB_H_RX_HW_VER
              Added Subblock INFO_SB_APE_DVB_H_RX_SW_VER
              Added Subblock INFO_SB_APE_HW_VERSION
              Added Subblock INFO_SB_APE_IPDC_VERSION
              Added Subblock INFO_SB_APE_SW_CORE_VER
              Added Subblock INFO_SB_APE_TEST_VER
              Added Subblock INFO_SB_BOOTCODE_VER
              Added Subblock INFO_SB_CAMERA_DETAILED_VERSION_INFO
              Added Subblock INFO_SB_CAMERA_VER
              Added Subblock INFO_SB_CONTENT_PACK_VER
              Added Subblock INFO_SB_CONTENT_VERSIONS
              Added Subblock INFO_SB_FLIP_MCUSW_VERSION
              Added Subblock INFO_SB_FWID
              Added Subblock INFO_SB_LCD_VERSION
              Added Subblock INFO_SB_LIFETIME
              Added Subblock INFO_SB_MAGNETOMETER_ID
              Added Subblock INFO_SB_NAVISCROLL_VERSION
              Added Subblock INFO_SB_NFC_VERSION
              Added Subblock INFO_SB_PROXIMITY_SENSOR_ID
              Added Subblock INFO_SB_RAT_BAND_INFO
              Added Subblock INFO_SB_REBOOTS
              Added Subblock INFO_SB_ROFS_VERSION
              Added Subblock INFO_SB_SN_IMEI_SV_TO_NET
              Added Subblock INFO_SB_TOUCH_SENSOR_ID
              Added Subblock INFO_SB_UPDATES
              Added Subblock INFO_SB_VARIANT_VER
              Added Constant table INFO_BAND_POS
              Added Constant table INFO_COMPASS_3D_HW_TYPE
              Added Constant table INFO_CONTENT_LOCATION
              Added Bitmask table INFO_EUTRAN_BAND
              Added Bitmask table INFO_GSM_BAND
              Added Bitmask table INFO_RAT_ID
              Added Constant table INFO_ROFS_ID
              Added Bitmask table INFO_WCDMA_BAND
              Added Bitmask table INFO_WCDMA_RX_DIV_BAND
              Added Constant INFO_ANY_SIZE
              Added Constant INFO_BAND_ID_TABLE_MAX_CNT
              Added Constant INFO_SB_APE_ADSP_VER_LEN
              Added Constant INFO_SB_APE_HW_VER_LEN
              Added Constant INFO_SB_SN_IMEI_SV_TO_NET_STR_LEN
              Added Shared file from PN_PHONE_INFO
              New message, MTC_RAT_INFO_NTF added. Added Shared file from
              PN_PHONE_INFO. RM-RIM ID: 009-5586

Version     : 017.008    NON-DRAFT   04-Oct-2005    Vesa P.Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM VK05092050795. 
              Inspection minutes: ADB for SWAM VK05092926351. 
Description : Added Entry MTC_DISK_WIPE to MTC_STATE_CONSTANTS
              New state MTC_DISK_WIPE added. RM-RIM ID: 009-19281 in WP
              RM-RIM tool for details.

Version     : 017.007    NON-DRAFT   23-Aug-2004    Toni Laivo
Reason      : Change request
Reference   : ActionDB for SWAM / TL04082345432
Description : Added Message MTC_RF_CONTROL_REQ
              Added Message MTC_RF_CONTROL_RESP
              Added Message MTC_RF_STATUS_QUERY_REQ
              Added Message MTC_RF_STATUS_QUERY_RESP
              Added Entry MTC_TRANSITION_ONGOING to MTC_STATUS_INFO
              New message pairs MTC_RF_CONTROL_REQ/RESP and
              MTC_RF_STATUS_QUERY_REQ/RESP added. New indication
              MTC_RF_STATUS_INFO_IND added. New constants MTC_RF_OFF,
              MTC_RF_ON and MTC_TRANSITION_ONGOING added. See SCO 009-5586 in
              WP RM-RIM tool for details.

Version     : 017.006    NON-DRAFT   24-Mar-2004    Toni Laivo
Reason      : Change request
Reference   : ActionDB for SWAM / TL04032428422
Description : Added Entry MTC_NOT_AVAILABLE to MTC_ACTION
              Added Entry MTC_NOT_SUPPORTED to MTC_ACTION
              Added Entry MTC_CMT_ONLY_MODE to MTC_NOT_VALID
              Added Entry MTC_CMT_ONLY_MODE to MTC_STATE_CONSTANTS
              Parameter MTC_CMT_ONLY_MODE added for message
              MTC_FORCE_STARTUP_STATE_REQ. Parameter MTC_NOT_SUPPORTED added
              for message MTC_FORCE_STARTUP_STATE_RESP. Parameters
              MTC_NOT_AVAILABLE and MTC_NOT_SUPPORTED added for message
              MTC_SOS_STATUS_QUERY_RESP. See SCO 010-3811 in ISA RM-RIM tool
              for details.

Version     : 017.005    NON-DRAFT   01-Mar-2004    Toni Laivo
Reason      : Change request
Reference   : ActionDB for SWAM / TL04030134794
Description : New message pair MTC_GENERIC_STATUS_QUERY_REQ/RESP added. See
              SCO 009-10070 in ISA RM-RIM tool for details.

Version     : 017.004    NON-DRAFT   19-Nov-2003    Toni Laivo
Reason      : Moved to continuus
Reference   : -
Description : Cover page changed and header moved to continuus.

Version     : 017.003    NON-DRAFT   22-Oct-2003    Toni Laivo
Reason      : Change request and update
Reference   : ActionDB for SWAM / TL03100852978
Description : Message macro definition file updated based on
              skeleton_isi_m.h. Old macros replaced with the latest versions.
              See ActionDB for SWAM / TL03100846583 for updates. Both 8-bit
              and 16-bit ISI header is now supported. See SCO 009-6670 is ISA
              RM-RIM tool for details.

Version     : 017.002    NON-DRAFT   13-May-2003    Toni Laivo
Reason      : Change request
Reference   : ActionDB for SWAM / TL03051344216
Description : A new message pair MTC_SOS_STATUS_QUERY_REQ/RESP added. A new
              message pair MTC_SHUTDOWN_SYNC_REQ/RESP added. Status field
              added to message MTC_STARTUP_SYNQ_RESP. Constants added for
              MTC_RESET_GENERATE_REQ to be used with MTC_HIDDEN_RESET.
              Constant tables updated to match with mtc_isi.doc. See SCO
              010-1195 in ISA RM-RIM tool for details.

Version     : 017.001    NON-DRAFT   08-Mar-2003    Toni Laivo
Reason      : Change request
Reference   : ActionDB for SWAM / TL03040849466
Description : A new message pair MTC_RESET_CONTROL_REQ/RESP added. Constant
              MTC_SERVICE_DISABLED added to status field of message
              MTC_RESET_GENERATE_RESP. See SCO 010-1228 in ISA RM-RIM tool.

Version     : 017.000    NON-DRAFT   23-Sep-2002    Toni Laivo
Reason      : Version update
Reference   : ActionDB for SWAM / IJ02032226253
Description : Version number changed to follow ISI version numbering. Now
              version numbers of mtc_isi.h, mtc_isi_m.h and mtc_isi.doc are
              synchronized. Note! File is backward compatible although
              Z-version number was changed.

------------------------------------------------------------------------------

Description

This file contains definitions of MTC Server ISI message structures and
constants. mtc_isi.h is an 8-bit version of the header file and mtc_isi_16.h
is a 16-bit version (for DSP users).

Both 8-bit and 16-bit versions of header files are generated with autogen
tool based on the message definitions in MTC message macro definition file
mtc_isi_m.h.

The features for MTC server are defined in the message and feature
specification document (see reference /6/) and in the common feature
specification document (see reference /5/).


*/

#ifndef _MTC_ISI_H
#define _MTC_ISI_H

#include "isi_conf.h"

#ifndef MTC_ISI_VERSION
#define MTC_ISI_VERSION
#define MTC_ISI_VERSION_Z  22
#define MTC_ISI_VERSION_Y   0
#endif

#define MTC_ISI_MIN_VERSION(z,y) \
 ((MTC_ISI_VERSION_Z == (z) && MTC_ISI_VERSION_Y >= (y)) || \
  (MTC_ISI_VERSION_Z > (z)))

#if !MTC_ISI_MIN_VERSION(17,0)
#error The specified interface version is not supported by this header file
#elif MTC_ISI_MIN_VERSION(22,1)
#error The specified interface version is not supported by this header file
#endif


/* ----------------------------------------------------------------------- */
/* Constants                                                               */
/* ----------------------------------------------------------------------- */

#define MTC_LAST_REQ_ID                          0x18
#define MTC_LAST_MSG_ID                          0xC3
#define MTC_SLEEP_WITH_RESET                     0x8000
/* constant for variable-length definitions */
#define MTC_ANY_SIZE                             1

/* ----------------------------------------------------------------------- */
/* Constant Table: MTC_ACTION                                              */
/* ----------------------------------------------------------------------- */
typedef uint8 MTC_ACTION_CONST;

#define MTC_START                                0x03
#define MTC_READY                                0x04

#if !MTC_ISI_MIN_VERSION(21,0)
#define MTC_NOS_READY                            0x0C
#endif /* !MTC_ISI_MIN_VERSION(21,0) */


#if !MTC_ISI_MIN_VERSION(21,0)
#define MTC_SOS_START                            0x11
#endif /* !MTC_ISI_MIN_VERSION(21,0) */


#if !MTC_ISI_MIN_VERSION(21,0)
#define MTC_SOS_READY                            0x12
#endif /* !MTC_ISI_MIN_VERSION(21,0) */

#define MTC_NOT_SUPPORTED                        0x14
#define MTC_NOT_AVAILABLE                        0x15

/* ----------------------------------------------------------------------- */
/* Constant Table: MTC_STATUS_INFO                                         */
/* ----------------------------------------------------------------------- */
typedef uint8 MTC_STATUS_INFO_CONST;

#define MTC_OK                                   0x00
#define MTC_FAIL                                 0x01
#define MTC_NOT_ALLOWED                          0x02
#define MTC_STATE_TRANSITION_GOING_ON            0x05
#define MTC_ALREADY_ACTIVE                       0x06
#define MTC_SERVICE_DISABLED                     0x10
#define MTC_NOT_READY_YET                        0x13
/* #define MTC_NOT_SUPPORTED                     0x14 (already defined) */
#define MTC_TRANSITION_ONGOING                   0x16
#define MTC_RESET_REQUIRED                       0x17

/* ----------------------------------------------------------------------- */
/* Constant Table: MTC_STATE_CONSTANTS                                     */
/* ----------------------------------------------------------------------- */
typedef uint8 MTC_STATE_CONSTANTS_CONST;

#define MTC_POWER_OFF                            0x00
#define MTC_NORMAL                               0x01
#define MTC_CHARGING                             0x02
#define MTC_ALARM                                0x03
#define MTC_TEST                                 0x04
#define MTC_LOCAL                                0x05
#define MTC_SELFTEST_FAIL                        0x08

#if !MTC_ISI_MIN_VERSION(21,0)
#define MTC_RF_INACTIVE                          0x0A
#endif /* !MTC_ISI_MIN_VERSION(21,0) */

#define MTC_DISK_WIPE                            0x0D
/* Constant MTC_SW_RESET must be greater than the last state constant. */
#define MTC_SW_RESET                             0x0E

#if MTC_ISI_MIN_VERSION(17,6) && !MTC_ISI_MIN_VERSION(21,0)
#define MTC_CMT_ONLY_MODE                        0xFF
#endif /* MTC_ISI_MIN_VERSION(17,6) && !MTC_ISI_MIN_VERSION(21,0) */


/* ----------------------------------------------------------------------- */
/* Constant Table: MTC_RESET_TYPE                                          */
/* ----------------------------------------------------------------------- */
typedef uint8 MTC_RESET_TYPE_CONST;

#define MTC_HIDDEN_RESET                         0x07
#define MTC_STATE_VIA_RESET                      0x08

#if !MTC_ISI_MIN_VERSION(21,0)
#define MTC_DEVICE_RESET                         0x0B
#endif /* !MTC_ISI_MIN_VERSION(21,0) */


/* ----------------------------------------------------------------------- */
/* Constant Table: MTC_SLEEP_TYPE                                          */
/* ----------------------------------------------------------------------- */
typedef uint8 MTC_SLEEP_TYPE_CONST;

#define MTC_LIGHT_SLEEP                          0x09
#define MTC_DEEP_SLEEP                           0x0A

/* ----------------------------------------------------------------------- */
/* Constant Table: MTC_WD_ACTION                                           */
/* ----------------------------------------------------------------------- */
typedef uint8 MTC_WD_ACTION_CONST;

#define MTC_WATCHDOG_ENABLE                      0x01
#define MTC_WATCHDOG_DISABLE                     0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: MTC_FORCE_ACTION                                        */
/* ----------------------------------------------------------------------- */
typedef uint8 MTC_FORCE_ACTION_CONST;

#define MTC_SET                                  0x0E
#define MTC_CLEAR                                0x0F

/* ----------------------------------------------------------------------- */
/* Constant Table: MTC_DEVICE_INFO - Obsolete from version 021.000         */
/* ----------------------------------------------------------------------- */

#if !MTC_ISI_MIN_VERSION(21,0)
typedef uint8 MTC_DEVICE_INFO_CONST;

#define MTC_CDSP                                 0xA1
#define MTC_ADSP                                 0xA2
#endif /* !MTC_ISI_MIN_VERSION(21,0) */


/* ----------------------------------------------------------------------- */
/* Constant Table: MTC_RESET_TYPE_HIDDEN                                   */
/* ----------------------------------------------------------------------- */
typedef uint8 MTC_RESET_TYPE_HIDDEN_CONST;

#define MTC_RESET_SW_RESET                       0x00

#if !MTC_ISI_MIN_VERSION(21,0)
#define MTC_RESET_SOS_RESET                      0x01
#endif /* !MTC_ISI_MIN_VERSION(21,0) */

#define MTC_RESET_MODEM_RESET                    0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: MTC_POWER_OFF_INFO                                      */
/* ----------------------------------------------------------------------- */
typedef uint8 MTC_POWER_OFF_INFO_CONST;

#define MTC_NORMAL_POWER_OFF                     0x00

#if !MTC_ISI_MIN_VERSION(21,0)
#define MTC_POWER_KEY_PRESS_TOO_SHORT            0x0D
#endif /* !MTC_ISI_MIN_VERSION(21,0) */


/* ----------------------------------------------------------------------- */
/* Constant Table: MTC_NOT_VALID                                           */
/* ----------------------------------------------------------------------- */
typedef uint8 MTC_NOT_VALID_CONST;

#define MTC_NOT_VALID                            0x00
/* #define MTC_CMT_ONLY_MODE                     0xFF (already defined) */

/* ----------------------------------------------------------------------- */
/* Constant Table: MTC_RF_STATUS                                           */
/* ----------------------------------------------------------------------- */
typedef uint8 MTC_RF_STATUS_CONST;

#define MTC_RF_OFF                               0x00
#define MTC_RF_ON                                0x01
#define MTC_RF_WIFI                              0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: PERF_STATUS_INFO - Valid from version 017.013           */
/* ----------------------------------------------------------------------- */
typedef uint8 PERF_STATUS_INFO_CONST;

#define PERF_OK                                  0x00
#define PERF_FAIL                                0x01
#define PERF_HAL_FAIL                            0x02
#define PERF_NOT_ACTIVE                          0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: PERF_SUB_SYSTEM_ID - Valid from version 017.013         */
/* ----------------------------------------------------------------------- */
typedef uint16 PERF_SUB_SYSTEM_ID_CONST;

#define PERF_NETWORK_SUB_SYSTEM                  0x0000
#define PERF_AUDIO_SUB_SYSTEM                    0x0001
#define PERF_VIDEO_SUB_SYSTEM                    0x0002
#define PERF_CAMERA_SUB_SYSTEM                   0x0003
#define PERF_DISPLAY_SUB_SYSTEM                  0x0004
#define PERF_USB_SUB_SYSTEM                      0x0005
#define PERF_BT_SUB_SYSTEM                       0x0006
#define PERF_WLAN_SUB_SYSTEM                     0x0008
#define PERF_MEMORY_SUB_SYSTEM                   0x0009
#define PERF_SECURITY_SUB_SYSTEM                 0x000A

/* ----------------------------------------------------------------------- */
/* Constant Table: PERF_SUB_SYSTEM_SERVICE - Valid from version 017.013    */
/* ----------------------------------------------------------------------- */
typedef uint16 PERF_SUB_SYSTEM_SERVICE_CONST;

#define PERF_IDLE                                0x0000
#define PERF_CALL                                0x0001
#define PERF_HS_CALL                             0x0002
#define PERF_NO_SERVICE                          0xFFFF

/* ----------------------------------------------------------------------- */
/* Constant Table: PERF_STATE_REQ_INFO - Valid from version 017.014        */
/* ----------------------------------------------------------------------- */
typedef uint8 PERF_STATE_REQ_INFO_CONST;

#define PERF_ON                                  0x00
#define PERF_OFF                                 0x01
#define PERF_SUB_SYSTEM_ON                       0x02
#define PERF_SUB_SYSTEM_OFF                      0x03
#define PERF_NOS_LOAD_ON                         0x04
#define PERF_NOS_LOAD_OFF                        0x05

/* ----------------------------------------------------------------------- */
/* Constant Table: PERF_VALUE_UNIT - Valid from version 017.016            */
/* ----------------------------------------------------------------------- */
typedef uint8 PERF_VALUE_UNIT_CONST;

#define PERF_MIPS                                0x00
#define PERF_MHZ                                 0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: PERF_VCORE_CALIB_STATUS - Valid from version 017.018    */
/* ----------------------------------------------------------------------- */
typedef uint32 PERF_VCORE_CALIB_STATUS_CONST;

#define PERF_CALIBRATION_OK                      0x00000000
#define PERF_CALIBRATION_OK_EFUSE_NOT_FOUND      0x00000001
#define PERF_CALIBRATION_OK_UNDERFLOW            0x00000002
#define PERF_CALIBRATION_OK_CALIBRATION_DISABLED 0x00000003
#define PERF_CALIBRATION_FAIL_VCORE_TOO_HIGH     0x00000010
#define PERF_CALIBRATION_FAIL_EFUSE_NOT_FOUND    0x00000011

#if MTC_ISI_MIN_VERSION(17,18) && !MTC_ISI_MIN_VERSION(20,0)
#define PERF_CALIBRATION_FAIL                    0x00000012
#endif /* MTC_ISI_MIN_VERSION(17,18) && !MTC_ISI_MIN_VERSION(20,0) */

#define PERF_CALIBRATION_FAIL_I2C                0x00000012
#define PERF_CALIBRATION_FAIL_NO_LDSP            0x00000013
#define PERF_CALIBRATION_FAIL_LDSP_NOT_RESPONDING 0x00000014
#define PERF_CALIBRATION_FAIL_LDSP_AUTH_FAILS    0x00000015
#define PERF_CALIBRATION_FAIL_LDSP_WRONG_VERSION 0x00000016
#define PERF_CALIBRATION_FAIL_RND_FLAG_ENABLED   0x00000020
#define PERF_CALIBRATION_FAIL_WRONG_ASIC_SPEED   0x00000021

/* ----------------------------------------------------------------------- */
/* Constant Table: PERF_VCORE_VSEL_MODE - Valid from version 017.018       */
/* ----------------------------------------------------------------------- */
typedef uint32 PERF_VCORE_VSEL_MODE_CONST;

#define PERF_SMPS_OPERATION_FORCED_PWM           0x00000000
#define PERF_SMPS_OPERATION_FAST_PFM             0x00000001

/* ----------------------------------------------------------------------- */
/* Constant Table: PERF_VCORE_CALIB_INFO - Valid from version 017.019      */
/* ----------------------------------------------------------------------- */
typedef uint8 PERF_VCORE_CALIB_INFO_CONST;

#define PERF_VCORE_1ST                           0x00
#define PERF_VCORE_CUR                           0x01

/* ----------------------------------------------------------------------- */
/* Bitmask Table: MTC_WD_TYPE                                              */
/* ----------------------------------------------------------------------- */
typedef uint8 MTC_WD_TYPE_CONST;

#define MTC_WATCHDOG_SW                          0x01  /* -------1 */
#define MTC_WATCHDOG_UPP                         0x02  /* ------1- */
#define MTC_WATCHDOG_CDSP                        0x04  /* -----1-- */

#if !MTC_ISI_MIN_VERSION(21,0)
#define MTC_WATCHDOG_ADSP                        0x08  /* ----1--- */
#endif /* !MTC_ISI_MIN_VERSION(21,0) */

#define MTC_WATCHDOG_MODEM                       0x10  /* ---1---- */
#define MTC_WATCHDOG_MODEM_SW                    0x20  /* --1----- */
#define MTC_WATCHDOG_ALL                         0xFF  /* 11111111 */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: PERF_INFO_DATA - Valid from version 017.018              */
/* ----------------------------------------------------------------------- */
typedef uint16 PERF_INFO_DATA_CONST;

#define PERF_HW_CONF_VCORE                       0x0001  /* ---------------1 */
#define PERF_HW_CONF_VCORE_PROD_1ST              0x0002  /* --------------1- */
#define PERF_HW_CONF_VCORE_PROD_CUR              0x0004  /* -------------1-- */

/* ----------------------------------------------------------------------- */
/* Message ID's                                                            */
/* ----------------------------------------------------------------------- */

#define MTC_STATE_REQ                            0x01
#define MTC_STATE_QUERY_REQ                      0x02
#define MTC_POWER_OFF_REQ                        0x03
#define MTC_POWER_ON_REQ                         0x04
#define MTC_SLEEP_REQ                            0x05
#define MTC_RESET_GENERATE_REQ                   0x06
#define MTC_SLEEP_ENABLE_REQ                     0x07
#define MTC_SLEEP_DISABLE_REQ                    0x08
#define MTC_CLOCK_CHANGE_REQ                     0x09
#define MTC_WATCHDOG_CONTROL_REQ                 0x0A
#define MTC_STARTUP_SYNQ_REQ                     0x0B
#define MTC_FORCE_STARTUP_STATE_REQ              0x0C
#define MTC_RAT_REQ                              0x0D
#define MTC_RAT_QUERY_REQ                        0x0E
#define MTC_MEM_DL_REQ                           0x0F
#define MTC_EXT_MEM_ACCESS_REQ                   0x10
#define MTC_RESET_CONTROL_REQ                    0x11
#define MTC_SHUTDOWN_SYNC_REQ                    0x12
#define MTC_SOS_STATUS_QUERY_REQ                 0x13
#define MTC_GENERIC_STATUS_QUERY_REQ             0x14
#define MTC_RF_CONTROL_REQ                       0x15
#define MTC_RF_STATUS_QUERY_REQ                  0x16
#define MTC_VCORE_READ_REQ                       0x17
#define PERF_SET_REQ                             0x30
#define PERF_STATE_REQ                           0x31
#define PERF_SETTINGS_WRITE_REQ                  0x32
#define PERF_INFO_REQ                            0x33
#define PERF_GET_REQ                             0x34
#define MTC_STATE_RESP                           0x64
#define MTC_STATE_QUERY_RESP                     0x65
#define MTC_POWER_OFF_RESP                       0x66
#define MTC_POWER_ON_RESP                        0x67
#define MTC_SLEEP_RESP                           0x68
#define MTC_RESET_GENERATE_RESP                  0x69
#define MTC_SLEEP_ENABLE_RESP                    0x6A
#define MTC_SLEEP_DISABLE_RESP                   0x6B
#define MTC_CLOCK_CHANGE_RESP                    0x6C
#define MTC_WATCHDOG_CONTROL_RESP                0x6D
#define MTC_STARTUP_SYNQ_RESP                    0x6E
#define MTC_FORCE_STARTUP_STATE_RESP             0x6F
#define MTC_RAT_RESP                             0x70
#define MTC_RAT_QUERY_RESP                       0x71
#define MTC_MEM_DL_RESP                          0x72
#define MTC_EXT_MEM_ACCESS_RESP                  0x73
#define MTC_RESET_CONTROL_RESP                   0x74
#define MTC_SHUTDOWN_SYNC_RESP                   0x75
#define MTC_SOS_STATUS_QUERY_RESP                0x76
#define MTC_GENERIC_STATUS_QUERY_RESP            0x77
#define MTC_RF_CONTROL_RESP                      0x78
#define MTC_RF_STATUS_QUERY_RESP                 0x79
#define MTC_RAT_INFO_NTF                         0x7A
#define MTC_VCORE_READ_RESP                      0x7B
#define MTC_DSP_GENIO_CONFIG_NTF                 0x7C
#define PERF_SET_RESP                            0x90
#define PERF_STATE_RESP                          0x91
#define PERF_SETTINGS_WRITE_RESP                 0x92
#define PERF_INFO_RESP                           0x93
#define PERF_GET_RESP                            0x94
#define MTC_STATE_INFO_IND                       0xC0
#define MTC_CLOCK_CHANGE_IND                     0xC1
#define MTC_RF_STATUS_INFO_IND                   0xC2

/* ----------------------------------------------------------------------- */
/* Subblock ID's                                                           */
/* ----------------------------------------------------------------------- */

#define PERF_SB_OPERATING_POINT                  0x30
#define PERF_SB_SERVICE_SETTING                  0x31
#define PERF_SB_PERFORMANCE                      0x32
#define PERF_SB_HW_CONF_VCORE                    0x33
#define PERF_SB_HW_CONF_VCORE_PROD_1ST           0x34
#define PERF_SB_HW_CONF_VCORE_PROD_CUR           0x35
#define PERF_SB_HW_CONF_VCORE_PROD               0x36
#define PERF_SB_PERFORMANCE_SETTING              0x37
#define MTC_SB_LONG_PWR_KEY_COUNT                0x02
#define MTC_SB_MEM_DL_DATA                       0x01

/* ----------------------------------------------------------------------- */
/* Shared file inclusion                                                   */
/* ----------------------------------------------------------------------- */

#if MTC_ISI_MIN_VERSION(17,9)
#include "info_shared_isi.h"
#endif /* MTC_ISI_MIN_VERSION(17,9) */


/* ----------------------------------------------------------------------- */
/* Sequence: PERF_HW_CONF_FREQ_SEQ - Valid from version 017.018            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint32  hz;
    uint16  pll_mul;
    uint16  pll_div;
    } PERF_HW_CONF_FREQ_SEQ_STR;

#define SIZE_PERF_HW_CONF_FREQ_SEQ_STR   sizeof(PERF_HW_CONF_FREQ_SEQ_STR)


/* ----------------------------------------------------------------------- */
/* Sequence: PERF_HW_CONF_VCORE_SEQ - Valid from version 017.018           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    /* Values from the constant table PERF_VCORE_VSEL_MODE */
    uint32  smps_mode;
    uint32  vcore_raw;
    uint32  vcore_final;
    PERF_HW_CONF_FREQ_SEQ_STR mcu_freq;
    PERF_HW_CONF_FREQ_SEQ_STR dsp1_freq;
    PERF_HW_CONF_FREQ_SEQ_STR dsp2_freq;
    } PERF_HW_CONF_VCORE_SEQ_STR;

#define SIZE_PERF_HW_CONF_VCORE_SEQ_STR   sizeof(PERF_HW_CONF_VCORE_SEQ_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: PERF_SB_OPERATING_POINT - Valid from version 017.014          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   sb_len;
    uint8   operating_point;
    uint8   fill1;
    } PERF_SB_OPERATING_POINT_STR;

#define SIZE_PERF_SB_OPERATING_POINT_STR   \
        sizeof(PERF_SB_OPERATING_POINT_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: PERF_SB_SERVICE_SETTING - Valid from version 017.014          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   sb_len;
    /* Values from the constant table PERF_SUB_SYSTEM_ID */
    uint16  sub_system;
    /* Values from the constant table PERF_SUB_SYSTEM_SERVICE */
    uint16  service;
    uint8   operating_point;
    uint8   fill1;
    } PERF_SB_SERVICE_SETTING_STR;

#define SIZE_PERF_SB_SERVICE_SETTING_STR   \
        sizeof(PERF_SB_SERVICE_SETTING_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: PERF_SB_PERFORMANCE - Valid from version 017.016              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   sb_len;
    uint8   fill1;
    uint8   value_unit;  /* Values from the constant table PERF_VALUE_UNIT */
    uint16  value;
    uint8   fill2;
    uint8   fill3;
    } PERF_SB_PERFORMANCE_STR;

#define SIZE_PERF_SB_PERFORMANCE_STR   sizeof(PERF_SB_PERFORMANCE_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: PERF_SB_HW_CONF_VCORE - Valid from version 017.018            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   fill1;
    uint16  sb_len;
    uint8   fill2;
    uint8   fill3;
    uint8   vcore1_count;
    uint8   vcore2_count;
    /* Values from the constant table PERF_VCORE_CALIB_STATUS */
    uint32  status;
    uint8   fill4[3];
    uint8   fill5[3];
    uint8   fill6[3];
    uint8   fill7[3];
    PERF_HW_CONF_VCORE_SEQ_STR vcore_master[MTC_ANY_SIZE];
    } PERF_SB_HW_CONF_VCORE_STR;

#define SIZE_PERF_SB_HW_CONF_VCORE_STR   (18*sizeof(uint8) + \
        sizeof(uint16) + sizeof(uint32))


/* ----------------------------------------------------------------------- */
/* Subblock: PERF_SB_HW_CONF_VCORE_PROD_1ST - Versions 017.018 - 017.019   */
/* ----------------------------------------------------------------------- */

#if MTC_ISI_MIN_VERSION(17,18) && !MTC_ISI_MIN_VERSION(17,19)

typedef struct
    {
    uint8   sb_id;
    uint8   sb_len;
    uint8   vcore_count;
    uint8   fill1;
    /* Values from the constant table PERF_VCORE_CALIB_STATUS */
    uint32  status;
    uint8   fill2[3];
    uint8   fill3[3];
    uint8   fill4[3];
    uint8   fill5[3];
    uint32  vcore_raw[MTC_ANY_SIZE];
    } PERF_SB_HW_CONF_VCORE_PROD_1ST_STR;

#define SIZE_PERF_SB_HW_CONF_VCORE_PROD_1ST_STR   (16*sizeof(uint8) + \
        sizeof(uint32))

#endif /* MTC_ISI_MIN_VERSION(17,18) && !MTC_ISI_MIN_VERSION(17,19) */


/* ----------------------------------------------------------------------- */
/* Subblock: PERF_SB_HW_CONF_VCORE_PROD_CUR - Versions 017.018 - 017.019   */
/* ----------------------------------------------------------------------- */

#if MTC_ISI_MIN_VERSION(17,18) && !MTC_ISI_MIN_VERSION(17,19)

typedef struct
    {
    uint8   sb_id;
    uint8   sb_len;
    uint8   vcore_count;
    uint8   fill1;
    /* Values from the constant table PERF_VCORE_CALIB_STATUS */
    uint32  status;
    uint8   fill2[3];
    uint8   fill3[3];
    uint8   fill4[3];
    uint8   fill5[3];
    uint32  vcore_raw[MTC_ANY_SIZE];
    } PERF_SB_HW_CONF_VCORE_PROD_CUR_STR;

#define SIZE_PERF_SB_HW_CONF_VCORE_PROD_CUR_STR   (16*sizeof(uint8) + \
        sizeof(uint32))

#endif /* MTC_ISI_MIN_VERSION(17,18) && !MTC_ISI_MIN_VERSION(17,19) */


/* ----------------------------------------------------------------------- */
/* Subblock: PERF_SB_HW_CONF_VCORE_PROD - Valid from version 017.019       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   sb_len;
    uint8   vcore_count;
    /* Values from the constant table PERF_VCORE_CALIB_INFO */
    uint8   calib_info;
    /* Values from the constant table PERF_VCORE_CALIB_STATUS */
    uint32  status;
    uint8   fill1[3];
    uint8   fill2[3];
    uint8   fill3[3];
    uint8   fill4[3];
    uint32  vcore_raw[MTC_ANY_SIZE];
    } PERF_SB_HW_CONF_VCORE_PROD_STR;

#define SIZE_PERF_SB_HW_CONF_VCORE_PROD_STR   (16*sizeof(uint8) + \
        sizeof(uint32))


/* ----------------------------------------------------------------------- */
/* Subblock: PERF_SB_PERFORMANCE_SETTING - Valid from version 018.002      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sb_id;
    uint8   sb_len;
    uint8   fill1;
    uint8   value_unit;  /* Values from the constant table PERF_VALUE_UNIT */
    uint16  value;
    /* Values from the constant table PERF_SUB_SYSTEM_ID */
    uint16  sub_system;
    } PERF_SB_PERFORMANCE_SETTING_STR;

#define SIZE_PERF_SB_PERFORMANCE_SETTING_STR   \
        sizeof(PERF_SB_PERFORMANCE_SETTING_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_POWER_OFF_REQ                                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   fill1;    /* Values from the constant table MTC_POWER_OFF_INFO */
    uint8   fill2;
    } MTC_POWER_OFF_REQ_STR;

#define SIZE_MTC_POWER_OFF_REQ_STR   sizeof(MTC_POWER_OFF_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_POWER_OFF_RESP                                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATUS_INFO */
    uint8   status;
    uint8   fill1;
    } MTC_POWER_OFF_RESP_STR;

#define SIZE_MTC_POWER_OFF_RESP_STR   sizeof(MTC_POWER_OFF_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_POWER_ON_REQ                                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   fill1;
    uint8   fill2;
    } MTC_POWER_ON_REQ_STR;

#define SIZE_MTC_POWER_ON_REQ_STR   sizeof(MTC_POWER_ON_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_POWER_ON_RESP                                              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATUS_INFO */
    uint8   status;
    uint8   fill1;
    } MTC_POWER_ON_RESP_STR;

#define SIZE_MTC_POWER_ON_RESP_STR   sizeof(MTC_POWER_ON_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_RESET_GENERATE_REQ - Obsolete from version 021.000         */
/* ----------------------------------------------------------------------- */

#if !MTC_ISI_MIN_VERSION(21,0)

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;         /* Values from the constant table MTC_RESET_TYPE */
    /* A subset of values from the constant table MTC_STATE_CONSTANTS */
    uint8   state;
    } MTC_RESET_GENERATE_REQ_STR;

#define SIZE_MTC_RESET_GENERATE_REQ_STR   sizeof(MTC_RESET_GENERATE_REQ_STR)

#endif /* !MTC_ISI_MIN_VERSION(21,0) */


/* ----------------------------------------------------------------------- */
/* Message: MTC_RESET_GENERATE_REQ - Valid from version 021.000            */
/* ----------------------------------------------------------------------- */

#if MTC_ISI_MIN_VERSION(21,0)

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;         /* Values from the constant table MTC_RESET_TYPE */
    /* A subset of values from the constant table MTC_STATE_CONSTANTS */
    uint8   state;
    } MTC_RESET_GENERATE_REQ_STR;

#define SIZE_MTC_RESET_GENERATE_REQ_STR   sizeof(MTC_RESET_GENERATE_REQ_STR)

#endif /* MTC_ISI_MIN_VERSION(21,0) */


/* ----------------------------------------------------------------------- */
/* Message: MTC_RESET_GENERATE_RESP                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATUS_INFO */
    uint8   status;
    uint8   fill1;
    } MTC_RESET_GENERATE_RESP_STR;

#define SIZE_MTC_RESET_GENERATE_RESP_STR   \
        sizeof(MTC_RESET_GENERATE_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_SLEEP_REQ                                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* x---------------  Reset bit
       -xxxxxxxxxxxxxxx  Sleep time
    */
    uint16  timeout;
    } MTC_SLEEP_REQ_STR;

#define SIZE_MTC_SLEEP_REQ_STR   sizeof(MTC_SLEEP_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_SLEEP_RESP                                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATUS_INFO */
    uint8   status;
    uint8   fill1;
    } MTC_SLEEP_RESP_STR;

#define SIZE_MTC_SLEEP_RESP_STR   sizeof(MTC_SLEEP_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_STATE_REQ                                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATE_CONSTANTS */
    uint8   state;
    uint8   fill1;
    } MTC_STATE_REQ_STR;

#define SIZE_MTC_STATE_REQ_STR   sizeof(MTC_STATE_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_STATE_RESP                                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATUS_INFO */
    uint8   status;
    uint8   fill1;
    } MTC_STATE_RESP_STR;

#define SIZE_MTC_STATE_RESP_STR   sizeof(MTC_STATE_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_STATE_INFO_IND                                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATE_CONSTANTS */
    uint8   state;
    /* A subset of values from the constant table MTC_ACTION */
    uint8   action;
    } MTC_STATE_INFO_IND_STR;

#define SIZE_MTC_STATE_INFO_IND_STR   sizeof(MTC_STATE_INFO_IND_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_STATE_QUERY_REQ                                            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   fill1;
    uint8   fill2;
    } MTC_STATE_QUERY_REQ_STR;

#define SIZE_MTC_STATE_QUERY_REQ_STR   sizeof(MTC_STATE_QUERY_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_STATE_QUERY_RESP                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATE_CONSTANTS */
    uint8   current;
    /* A subset of values from the constant table MTC_STATE_CONSTANTS */
    uint8   target;
    } MTC_STATE_QUERY_RESP_STR;

#define SIZE_MTC_STATE_QUERY_RESP_STR   sizeof(MTC_STATE_QUERY_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_SLEEP_ENABLE_REQ                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;         /* Values from the constant table MTC_SLEEP_TYPE */
    uint8   fill1;
    } MTC_SLEEP_ENABLE_REQ_STR;

#define SIZE_MTC_SLEEP_ENABLE_REQ_STR   sizeof(MTC_SLEEP_ENABLE_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_SLEEP_ENABLE_RESP                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATUS_INFO */
    uint8   status;
    uint8   fill1;
    } MTC_SLEEP_ENABLE_RESP_STR;

#define SIZE_MTC_SLEEP_ENABLE_RESP_STR   sizeof(MTC_SLEEP_ENABLE_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_SLEEP_DISABLE_REQ                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   type;         /* Values from the constant table MTC_SLEEP_TYPE */
    uint8   fill1;
    } MTC_SLEEP_DISABLE_REQ_STR;

#define SIZE_MTC_SLEEP_DISABLE_REQ_STR   sizeof(MTC_SLEEP_DISABLE_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_SLEEP_DISABLE_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATUS_INFO */
    uint8   status;
    uint8   fill1;
    } MTC_SLEEP_DISABLE_RESP_STR;

#define SIZE_MTC_SLEEP_DISABLE_RESP_STR   sizeof(MTC_SLEEP_DISABLE_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_WATCHDOG_CONTROL_REQ                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   action;       /* Values from the constant table MTC_WD_ACTION */
    uint8   watchdog_list; /* Values from the bitmask table MTC_WD_TYPE */
    } MTC_WATCHDOG_CONTROL_REQ_STR;

#define SIZE_MTC_WATCHDOG_CONTROL_REQ_STR   \
        sizeof(MTC_WATCHDOG_CONTROL_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_WATCHDOG_CONTROL_RESP - Obsolete from version 018.000      */
/* ----------------------------------------------------------------------- */

#if !MTC_ISI_MIN_VERSION(18,0)

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATUS_INFO */
    uint8   status;
    uint8   fill1;
    } MTC_WATCHDOG_CONTROL_RESP_STR;

#define SIZE_MTC_WATCHDOG_CONTROL_RESP_STR   \
        sizeof(MTC_WATCHDOG_CONTROL_RESP_STR)

#endif /* !MTC_ISI_MIN_VERSION(18,0) */


/* ----------------------------------------------------------------------- */
/* Message: MTC_WATCHDOG_CONTROL_RESP - Valid from version 018.000         */
/* ----------------------------------------------------------------------- */

#if MTC_ISI_MIN_VERSION(18,0)

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATUS_INFO */
    uint8   status;
    uint8   fill1;
    } MTC_WATCHDOG_CONTROL_RESP_STR;

#define SIZE_MTC_WATCHDOG_CONTROL_RESP_STR   \
        sizeof(MTC_WATCHDOG_CONTROL_RESP_STR)

#endif /* MTC_ISI_MIN_VERSION(18,0) */


/* ----------------------------------------------------------------------- */
/* Message: MTC_FORCE_STARTUP_STATE_REQ                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   action;     /* Values from the constant table MTC_FORCE_ACTION */
    /* A subset of values from the constant table MTC_STATE_CONSTANTS */
    uint8   state;
    } MTC_FORCE_STARTUP_STATE_REQ_STR;

#define SIZE_MTC_FORCE_STARTUP_STATE_REQ_STR   \
        sizeof(MTC_FORCE_STARTUP_STATE_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_FORCE_STARTUP_STATE_RESP                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATUS_INFO */
    uint8   status;
    uint8   fill1;
    } MTC_FORCE_STARTUP_STATE_RESP_STR;

#define SIZE_MTC_FORCE_STARTUP_STATE_RESP_STR   \
        sizeof(MTC_FORCE_STARTUP_STATE_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_RF_CONTROL_REQ - Valid from version 017.007                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   action;       /* Values from the constant table MTC_RF_STATUS */
    uint8   fill1;
    } MTC_RF_CONTROL_REQ_STR;

#define SIZE_MTC_RF_CONTROL_REQ_STR   sizeof(MTC_RF_CONTROL_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_RF_CONTROL_RESP - Valid from version 017.007               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table MTC_STATUS_INFO */
    uint8   status;
    uint8   fill1;
    } MTC_RF_CONTROL_RESP_STR;

#define SIZE_MTC_RF_CONTROL_RESP_STR   sizeof(MTC_RF_CONTROL_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_RF_STATUS_QUERY_REQ - Valid from version 017.007           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   fill1[2];
    } MTC_RF_STATUS_QUERY_REQ_STR;

#define SIZE_MTC_RF_STATUS_QUERY_REQ_STR   \
        sizeof(MTC_RF_STATUS_QUERY_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_RF_STATUS_QUERY_RESP - Valid from version 017.007          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   current;      /* Values from the constant table MTC_RF_STATUS */
    uint8   target;       /* Values from the constant table MTC_RF_STATUS */
    } MTC_RF_STATUS_QUERY_RESP_STR;

#define SIZE_MTC_RF_STATUS_QUERY_RESP_STR   \
        sizeof(MTC_RF_STATUS_QUERY_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_RF_STATUS_INFO_IND                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   target;       /* Values from the constant table MTC_RF_STATUS */
    /* A subset of values from the constant table MTC_ACTION */
    uint8   action;
    } MTC_RF_STATUS_INFO_IND_STR;

#define SIZE_MTC_RF_STATUS_INFO_IND_STR   sizeof(MTC_RF_STATUS_INFO_IND_STR)


/* ----------------------------------------------------------------------- */
/* Message: MTC_RAT_INFO_NTF - Valid from version 017.009                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   fill1;
    uint8   sb_count;
    /* Subblock list:
       INFO_SB_RAT_BAND_INFO
    */
    } MTC_RAT_INFO_NTF_STR;

#define SIZE_MTC_RAT_INFO_NTF_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: MTC_DSP_GENIO_CONFIG_NTF - Valid from version 017.017          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   status;      /* Values from the constant table MTC_STATUS_INFO */
    uint8   fill1;
    uint32  genio_conf_addr;
    } MTC_DSP_GENIO_CONFIG_NTF_STR;

#define SIZE_MTC_DSP_GENIO_CONFIG_NTF_STR   \
        sizeof(MTC_DSP_GENIO_CONFIG_NTF_STR)


/* ----------------------------------------------------------------------- */
/* Message: PERF_SET_REQ - Valid from version 017.013                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Values from the constant table PERF_SUB_SYSTEM_ID */
    uint16  sub_system;
    /* Values from the constant table PERF_SUB_SYSTEM_SERVICE */
    uint16  service;
    uint8   fill1;
    uint8   sb_count;
    /* Subblock list:
       PERF_SB_PERFORMANCE
    */
    } PERF_SET_REQ_STR;

#define SIZE_PERF_SET_REQ_STR   (4*sizeof(uint8) + 2*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: PERF_SET_RESP - Valid from version 017.013                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Values from the constant table PERF_SUB_SYSTEM_ID */
    uint16  sub_system;
    /* Values from the constant table PERF_SUB_SYSTEM_SERVICE */
    uint16  service;
    uint8   status;     /* Values from the constant table PERF_STATUS_INFO */
    /* No sub-blocks exist yet, will be defined when more granular
       information in response is needed. 
    */
    uint8   sb_count;
    } PERF_SET_RESP_STR;

#define SIZE_PERF_SET_RESP_STR   sizeof(PERF_SET_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: PERF_STATE_REQ - Valid from version 017.014                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   state;   /* Values from the constant table PERF_STATE_REQ_INFO */
    uint8   sb_count;
    /* Subblock list:
       PERF_SB_OPERATING_POINT
    */
    uint8   sub_blocks[MTC_ANY_SIZE];
    } PERF_STATE_REQ_STR;

#define SIZE_PERF_STATE_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: PERF_STATE_RESP - Valid from version 017.014                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table PERF_STATUS_INFO */
    uint8   status;
    uint8   fill1;
    } PERF_STATE_RESP_STR;

#define SIZE_PERF_STATE_RESP_STR   sizeof(PERF_STATE_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: PERF_SETTINGS_WRITE_REQ - Valid from version 017.014           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   fill1;
    uint8   sb_count;
    /* Subblock list:
       PERF_SB_SERVICE_SETTING
    */
    uint8   sub_blocks[MTC_ANY_SIZE];
    } PERF_SETTINGS_WRITE_REQ_STR;

#define SIZE_PERF_SETTINGS_WRITE_REQ_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: PERF_SETTINGS_WRITE_RESP - Valid from version 017.014          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   status;     /* Values from the constant table PERF_STATUS_INFO */
    uint8   fill1;
    } PERF_SETTINGS_WRITE_RESP_STR;

#define SIZE_PERF_SETTINGS_WRITE_RESP_STR   \
        sizeof(PERF_SETTINGS_WRITE_RESP_STR)


/* ----------------------------------------------------------------------- */
/* Message: PERF_INFO_REQ - Valid from version 017.018                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  req_data;     /* Values from the bitmask table PERF_INFO_DATA */
    } PERF_INFO_REQ_STR;

#define SIZE_PERF_INFO_REQ_STR   sizeof(PERF_INFO_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: PERF_INFO_RESP - Valid from version 017.018                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table PERF_STATUS_INFO */
    uint8   status;
    uint8   sb_count;
    /* Subblock list:
       PERF_SB_HW_CONF_VCORE
       PERF_SB_HW_CONF_VCORE_PROD
    */
    uint8   sub_blocks[MTC_ANY_SIZE];
    } PERF_INFO_RESP_STR;

#define SIZE_PERF_INFO_RESP_STR   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: PERF_GET_REQ - Valid from version 018.002                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   fill1;
    uint8   fill2;
    } PERF_GET_REQ_STR;

#define SIZE_PERF_GET_REQ_STR   sizeof(PERF_GET_REQ_STR)


/* ----------------------------------------------------------------------- */
/* Message: PERF_GET_RESP - Valid from version 018.002                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   status;     /* Values from the constant table PERF_STATUS_INFO */
    uint8   sb_count;
    /* Subblock list:
       PERF_SB_OPERATING_POINT
       PERF_SB_PERFORMANCE_SETTING
       PERF_SB_SERVICE_SETTING
    */
    uint8   sub_blocks[MTC_ANY_SIZE];
    } PERF_GET_RESP_STR;

#define SIZE_PERF_GET_RESP_STR   (4*sizeof(uint8))


/* ------------------------------------------------------------------------- */
/* Definitions below are added for backward compatibility.                   */
/* DO NOT USE THESE!!! Use above mentioned definitions instead.              */
/* ------------------------------------------------------------------------- */
 
/* DO NOT USE THIS DEFINITION, USE MTC_STATE_REQ_STR INSTEAD!!!              */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte state;
    byte reserved1;
    } tMTC_StateReq;
#define MTC_STATE_REQ_LEN ( sizeof(tMTC_StateReq) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_STATE_RESP_STR INSTEAD!!!             */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte status;
    byte reserved1;
    } tMTC_StateResp;
#define MTC_STATE_RESP_LEN ( sizeof(tMTC_StateResp) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_STATE_INFO_IND_STR INSTEAD!!!         */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte state;
    byte action;
    } tMTC_StateInfoInd;
#define MTC_STATE_INFO_IND_LEN ( sizeof(tMTC_StateInfoInd) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_SLEEP_REQ_STR INSTEAD!!!              */
typedef struct
    {
    byte UTID;
    byte msg_id;
    word timeout;
    } tMTC_SleepReq;
#define MTC_SLEEP_REQ_LEN ( sizeof(tMTC_SleepReq) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_SLEEP_RESP_STR INSTEAD!!!             */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte status;
    byte reserved;
    } tMTC_SleepResp;
#define MTC_SLEEP_RESP_LEN ( sizeof(tMTC_SleepResp) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_STATE_QUERY_REQ_STR INSTEAD!!!        */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte reserved1;
    byte reserved2;
    } tMTC_StateQueryReq;
#define MTC_STATE_QUERY_REQ_LEN ( sizeof(tMTC_StateQueryReq) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_STATE_QUERY_RESP_STR INSTEAD!!!       */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte current;
    byte target;
    } tMTC_StateQueryResp;
#define MTC_STATE_QUERY_RESP_LEN ( sizeof(tMTC_StateQueryResp) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_POWER_OFF_REQ_STR INSTEAD!!!          */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte reserved1;
    byte reserved2;
    } tMTC_PowerOffReq;
#define MTC_POWER_OFF_REQ_LEN ( sizeof(tMTC_PowerOffReq) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_POWER_OFF_RESP_STR INSTEAD!!!         */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte status;
    byte reserved;
    } tMTC_PowerOffResp;
#define MTC_POWER_OFF_RESP_LEN ( sizeof(tMTC_PowerOffResp) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_POWER_ON_REQ_STR INSTEAD!!!           */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte reserved1;
    byte reserved2;
    } tMTC_PowerOnReq;
#define MTC_POWER_ON_REQ_LEN ( sizeof(tMTC_PowerOnReq) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_POWER_ON_RESP_STR INSTEAD!!!          */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte status;
    byte reserved;
    } tMTC_PowerOnResp;
#define MTC_POWER_ON_RESP_LEN ( sizeof(tMTC_PowerOnResp) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_RESET_GENERATE_REQ_STR INSTEAD!!!     */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte type;
    byte state;
    } tMTC_ResetGenerateReq;
#define MTC_RESET_GENERATE_REQ_LEN ( sizeof(tMTC_ResetGenerateReq) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_RESET_GENERATE_RESP_STR INSTEAD!!!    */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte status;
    byte reserved;
    } tMTC_ResetGenerateResp;
#define MTC_RESET_GENERATE_RESP_LEN ( sizeof(tMTC_ResetGenerateResp) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_SLEEP_ENABLE_REQ_STR INSTEAD!!!       */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte type;
    byte reserved;
    } tMTC_SleepEnableReq;
#define MTC_SLEEP_ENABLE_REQ_LEN ( sizeof(tMTC_SleepEnableReq) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_SLEEP_ENABLE_RESP_STR INSTEAD!!!      */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte status;
    byte reserved;
    } tMTC_SleepEnableResp;
#define MTC_SLEEP_ENABLE_RESP_LEN ( sizeof(tMTC_SleepEnableResp) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_SLEEP_DISABLE_REQ_STR INSTEAD!!!      */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte type;
    byte reserved;
    } tMTC_SleepDisableReq;
#define MTC_SLEEP_DISABLE_REQ_LEN ( sizeof(tMTC_SleepDisableReq) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_SLEEP_DISABLE_RESP_STR INSTEAD!!!     */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte status;
    byte reserved1;
    } tMTC_SleepDisableResp;
#define MTC_SLEEP_DISABLE_RESP_LEN ( sizeof(tMTC_SleepDisableResp) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_CLOCK_CHANGE_REQ_STR INSTEAD!!!       */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte clock;
    byte action;
    } tMTC_ClockChangeReq;
#define MTC_CLOCK_CHANGE_REQ_LEN ( sizeof(tMTC_ClockChangeReq) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_CLOCK_CHANGE_RESP_STR INSTEAD!!!      */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte status;
    byte reserved1;
    } tMTC_ClockChangeResp;
#define MTC_CLOCK_CHANGE_RESP_LEN ( sizeof(tMTC_ClockChangeResp) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_CLOCK_CHANGE_IND_STR INSTEAD!!!       */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte clock;
    byte action;
    } tMTC_ClockChangeInd;
#define MTC_CLOCK_CHANGE_IND_LEN ( sizeof(tMTC_ClockChangeInd) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_WATCHDOG_CONTROL_REQ_STR INSTEAD!!!   */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte action;
    byte watchdog_list;
    } tMTC_WatchdogControlReq;
#define MTC_WATCHDOG_CONTROL_REQ_LEN ( sizeof(tMTC_WatchdogControlReq) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_WATCHDOG_CONTROL_RESP_STR INSTEAD!!!  */
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte status;
    byte reserved1;
    } tMTC_WatchdogControlResp;
#define MTC_WATCHDOG_CONTROL_RESP_LEN ( sizeof(tMTC_WatchdogControlResp) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_ENOS_STARTUP_SYNQ_REQ_STR INSTEAD!!!  */
#define MTC_ENOS_STARTUP_SYNQ_REQ       MTC_STARTUP_SYNQ_REQ
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte reserved1;
    byte reserved2;
    } tMTC_EnosSynqReq;
#define MTC_ENOS_STARTUP_SYNQ_REQ_LEN ( sizeof(tMTC_EnosSynqReq) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_ENOS_STARTUP_SYNQ_RESP_STR INSTEAD!!! */
#define MTC_ENOS_STARTUP_SYNQ_RESP      MTC_STARTUP_SYNQ_RESP
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte reserved1;
    byte reserved2;
    } tMTC_EnosSynqResp;
#define MTC_ENOS_STARTUP_SYNQ_RESP_LEN ( sizeof(tMTC_EnosSynqResp) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_FORCE_STARTUP_STATE_REQ_STR INSTEAD!!!*/
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte action;
    byte state;
    } tMTC_ForceStartUpStateReq;
#define MTC_FORCE_STARTUP_STATE_REQ_LEN ( sizeof(tMTC_ForceStartUpStateReq) )
 
/* DO NOT USE THIS DEFINITION, USE MTC_FORCE_STARTUP_STATE_RESP_STR INSTEAD!!!*/
typedef struct
    {
    byte UTID;
    byte msg_id;
    byte status;
    byte reserved1;
    } tMTC_ForceStartUpStateResp;
#define MTC_FORCE_STARTUP_STATE_RESP_LEN ( sizeof(tMTC_ForceStartUpStateResp) )


/* ----------------------------------------------------------------------- */
/* Notes                                                                   */
/* ----------------------------------------------------------------------- */
/*
   /1/  Autogeneration Process
        Intranet
        http://tracing.europe.nokia.com/autogen/documentation.asp
        Filename: autogen_proc.doc

   /2/  ISI Server Specification Documentation Guidelines
        Document code: XXXL7714-EN
        DocMan location: eslns42/SRV/Nokia
        DocMan: TP / WP Front End DocMan
        Filename: TP/WP/tpwpfendm.nsf

   /3/  ISI General Information
        Document code: XXXL7715-EN
        DocMan location: eslns42/SRV/Nokia
        DocMan: TP / WP Front End DocMan
        Filename: TP/WP/tpwpfendm.nsf

   /4/  ISI Common Message Descriptions
        Continuus Database: ou1gif
        Continuus Project: GIF_SPECS-ou1gif#browse
        Directory Path: GIF_SPECS/CoreSW
        Filename:  i_comm_m.html

   /5/  ISI Common Feature Descriptions
        Continuus Database: ou1gif
        Continuus Project: GIF_SPECS-ou1gif#browse
        Directory Path: GIF_SPECS/CoreSW
        Filename:  i_comm_fp.doc

   /6/  Mobile Terminal Controller (MTC) Feature and Message Descriptions.
        Continuus database: ou1gif
        Continuus Project:  GIF_SPECS-ou1gif#browse
        Directory path:     GIF_SPECS/CoreSW
        Filename:           mtc_isi.doc

   /7/  Mobile Terminal Controller Design Model.
        Part:      ISI:DES_MTC.BASE
        Item name: ISI:MTC_DESIGN_SPEC.BASE-MISC
        Workset:   ISI:WS_ISI
        Filename:  mtc_design.doc
*/


#endif /* _MTC_ISI_H */
