/*
NOKIA                                                             CONFIDENTIAL
R&D Tampere
D/RD/S40MyDevice/MyProductConcepts/InteractionSolutions
Risto-Matti Kunnas



                  srvkbd_isi.h
                  --------------------------------
                  SW Include Document - ANSI C/C++



Continuus Ref:
--------------
database:        ou1gif

project path:    global_interface/ISI/Core

name:            srvkbd_isi.h

version:         013.042

type:            incl

instance:        ou_pcms#1


ISI header file for Keyboard Server

Current   ISI Version : 013.042
Supported ISI Versions: 013.005, 013.006, 013.007, 013.008, 013.009, 013.010, 
                        013.011, 013.012, 013.013, 013.014, 013.015, 013.016, 
                        013.017, 013.018, 013.019, 013.020, 013.021, 013.022, 
                        013.023, 013.024, 013.025, 013.026, 013.027, 013.028, 
                        013.029, 013.030, 013.031, 013.032, 013.033, 013.034, 
                        013.035, 013.036, 013.037, 013.038, 013.039, 013.040, 
                        013.041, 013.042

Generated with autogen version 10_w49 on 26-Mar-2012 17:08:52
DO NOT EDIT - changes will be lost at next autogeneration

Copyright (c) Nokia Corporation. All rights reserved.


ISI version change history

Version     : 013.042    APPROVED    23-Mar-2012    Li Hypoer
Reason      : EVO Simulation REQ from Aadland Bjorn
Reference   : Interface CR: ADB for SWAM: HL12032334392
              Inspection minutes: -
Description : Added Entry KBD_KEY_BACK to KBD_KEY
              Add BACK key in EVO to support EVO HW (KBD_KEY_BACK)
              - KBD_KEY_BACK

Version     : 013.041    APPROVED    04-Nov-2009    Risto-Matti Kunnas
Reason      : RM-RIM: REQ 414-6712
Reference   : Interface CR: ADB for SWAM: RK09101339047
              Inspection minutes: -
Description : Added Subblock KBD_CONFIG_ACTION_ACTIVATION_MASK to KBD_CONFIG_REQ
              Added Subblock KBD_CONFIG_ACTION_ACTIVATION_MASK

Version     : 013.040    APPROVED    13-Oct-2009    Risto-Matti Kunnas
Reason      : RM-RIM: SUB 417-54851
Reference   : Interface CR: ADB for SWAM: RK09091638265
              Inspection minutes: -
Description : Added new field to KBD_CONFIG_REQ.
              - KBD_CONFIG_ACTION

Version     : 013.039    APPROVED    24-Sep-2009    Risto-Matti Kunnas
Reason      : RM-RIM: SCO 417-40820
Reference   : Interface CR: ADB for SWAM: RK09091847711
              Inspection minutes: -
Description : Added Entry KBD_KEY_CURSOR to KBD_KEY
              Added virtual key code.
              - KBD_KEY_CURSOR

Version     : 013.038    APPROVED    19-Aug-2009    Risto-Matti Kunnas
Reason      : RM-RIM: SCO 417-51685
Reference   : Interface CR: ADB for SWAM: RK09062535328
              Inspection minutes: -
Description : Added support for two hard key codes.
              - KBD_KEY_QUICK_LAUNCH
              - KBD_KEY_QUICK_LAUNCH_MESSAGING
              - KBD_KEY_QUICK_LAUNCH_SOCIAL_NETWORKING

Version     : 013.037    APPROVED    17-Feb-2009    Risto-Matti Kunnas
Reason      : RM-RIM: REQ 417-22013
Reference   : Interface CR: ADB for SWAM: RK09021236613
              Inspection minutes: -
Description : Added Entry KBD_SLIDE_SHORT_OPEN to KBD_SLIDE_STATE
              Added support for three slide positions.

Version     : 013.036    APPROVED    16-Sep-2008    Risto-Matti Kunnas
Reason      : RM-RIM: SCO 417-17419
Reference   : Interface CR: ADB for SWAM: RK08082949452
              Inspection minutes:
Description : Added Message KBD_POWER_CONTROL_REQ
              Added Message KBD_POWER_CONTROL_RESP
              Added Constant table KBD_POWER_CONTROL_DEVICE_ID
              Added Constant table KBD_POWER_CONTROL_MODE
              Added support for power mode switching.

Version     : 013.035    APPROVED    11-Sep-2008    Risto-Matti Kunnas
Reason      : RM-RIM: SCO 408-4389
Reference   : Interface CR: ADB for SWAM:
              Inspection minutes:
Description : Added new key code for Vertu Concierge button.
              - KBD_KEY_TPARTY

Version     : 013.034    APPROVED    02-Sep-2008    Risto-Matti Kunnas
Reason      : RM-RIM: 417-13687
Reference   : Interface CR: ADB for SWAM: RK08050962038
              Inspection minutes: ADB for SWAM: RK08090246436 
Description : Added new key codes for AT command support.
              - KBD_KEY_CHANNEL_A
              - KBD_KEY_CHANNEL_B
              - KBD_KEY_FUNCTION
              - KBD_KEY_PHONE_LOCK
              - KBD_KEY_MUTE_KEY
              - KBD_KEY_RECALL
              - KBD_KEY_STORE_MEMORY
              - KBD_KEY_AUXILIARY

Version     : 013.033    DRAFT       13-Aug-2008    Risto-Matti Kunnas
Reason      : RM-RIM:
Reference   : Interface CR:
              Inspection minutes:
Description : Added Message KBD_READ_RAW_DATA_REQ
              Added Message KBD_READ_RAW_DATA_RESP
              Added Subblock KBD_RAW_DATA_INFO
              Added Constant table KBD_READ_RAW_DATA_DEVICE
              Added Constant table KBD_READ_RAW_DATA_SIZE
              Added support for raw value reading. 

Version     : 013.032    APPROVED    06-Aug-2008    Arto Kangas
Reason      : RM-RIM: SCO 417-8543
Reference   : Interface CR: ADB for SWAM: AK08081252230
              Inspection minutes: 
Description : Added camera cover slide bit to special keys mask.

Version     : 013.031    APPROVED    19-Jun-2008    Risto-Matti Kunnas
Reason      : RM-RIM: SUB 408-4122
Reference   : Interface CR: ADB for SWAM: RK08061360471. 
              Inspection minutes: ADB for SWAM: . 
Description : Added Message KBD_CAPACITIVE_KEY_CONTROL_REQ
              Added Message KBD_CAPACITIVE_KEY_CONTROL_RESP
              Added Subblock KBD_CAPACITIVE_KEY_GLOBAL_SETTINGS
              Added Subblock KBD_CAPACITIVE_KEY_TYPE1_SETTINGS
              Added Subblock KBD_CAPACITIVE_KEY_TYPE2_SETTINGS
              Added support for capacitive key run-time configuration. 

Version     : 013.030    APPROVED    03-Jun-2008    Risto-Matti Kunnas
Reason      : RM-RIM: SCO 408-3945
Reference   : Interface CR: ADB for SWAM: RK08050962038. 
              Inspection minutes: ADB for SWAM: . 
Description : Added new key codes for physical keylock. 
              - KBD_KEY_KEYLOCK
              - KBD_KEY_KEYLOCK_TOGGLE

Version     : 013.029    APPROVED    08-Jan-2008    Sami Nieminen
Reason      : RM-RIM: SCO 408-2568
Reference   : Interface CR: ADB for SWAM: SN08010838028. 
              Inspection minutes: ADB for SWAM: . 
Description : Added Entry KBD_KEY_CV to KBD_KEY
              Added Entry KBD_KEY_MEDIA to KBD_KEY
              Added new key codes for Media and Cellular Video keys. 
              - KBD_KEY_MEDIA
              - KBD_KEY_CV

Version     : 013.028    APPROVED    10-Oct-2007    Carsten Hauge
Reason      : 3DFS and Avago subblock and control interface changes
Reference   : Interface CR: ADB for SWAM: CH07100350658. 
              Inspection minutes: ADB for SWAM: CH07100842651. 
Description : Added Subblock KBD_POINTING_DEVICE_INFO to KBD_EVENT_IND
              Added Subblock KBD_POINTING_DEVICE_INFO to KBD_EVENT_SIMULATION_REQ
              Added Message KBD_POINTING_DEVICE_CONTROL_REQ
              Added Message KBD_POINTING_DEVICE_CONTROL_RESP
              Added Subblock KBD_POINTING_DEVICE_INFO
              Added Constant table KBD_POINTING_DEVICE_CONTROL_ACTION
              3DFS and Avago support added.

Version     : 013.027    APPROVED    26-Sep-2007    Carsten Hauge
Reason      : New keycodes for I_CPR 7.2
Reference   : Interface CR: ADB for SWAM: CH07091850137. 
              Inspection minutes: ADB for SWAM: CH07092033202. 
Description : Added Entry KBD_KEY_EXT_MP_NEXT_TRACK to KBD_KEY
              Added Entry KBD_KEY_EXT_MP_PLAY_PAUSE to KBD_KEY
              Added Entry KBD_KEY_EXT_MP_PREV_TRACK to KBD_KEY
              Added Entry KBD_KEY_EXT_MP_STOP to KBD_KEY
              Added Entry KBD_KEY_LAUNCH_MAGNET to KBD_KEY
              Added Entry KBD_KEY_UI_RELAX_MODE to KBD_KEY
              Added new key codes to KBD_KEY table. 

Version     : 013.026    NON-DRAFT   20-Jun-2007    Boerge Fischer
Reason      : Request from Tum Wojciech (EXT-TietoEnator/CzechRepublic)
Reference   : Interface CR: ADB for SWAM BF07062063221. 
              Inspection minutes: ADB for SWAM BF07062062809. 
Description : Added Entry KBD_KEY_DEVICE_0 to KBD_KEY
              Added Entry KBD_KEY_DEVICE_1 to KBD_KEY
              Added Entry KBD_KEY_DEVICE_2 to KBD_KEY
              Added Entry KBD_KEY_MENU to KBD_KEY
              Added new key codes for MENU and DEVICE keys. 
              - KBD_KEY_MENU
              - KBD_KEY_DEVICE_0
              - KBD_KEY_DEVICE_1
              - KBD_KEY_DEVICE_2

Version     : 013.025    NON-DRAFT   07-Dec-2006    Boerge Fischer
Reason      : Change request
Reference   : Interface CR: ADB for SWAM BF06120762364. 
              Inspection minutes: ADB for SWAM BF06120763111. 
Description : Added Entry KBD_KEY_NAVISLIDE_LEFT to KBD_KEY
              Added Entry KBD_KEY_NAVISLIDE_RIGHT to KBD_KEY
              Added new key codes for NaviSlide keys on Tokyo. 
              - KBD_KEY_NAVISLIDE_LEFT
              - KBD_KEY_NAVISLIDE_RIGHT

Version     : 013.024    NON-DRAFT   08-Aug-2006    Boerge Fischer
Reason      : Change request
Reference   : Interface CR: ADB for SWAM BF06062352619. 
              Inspection minutes: ADB for SWAM BF06062734766. 
Description : Added Entry KBD_KEY_IDLE to KBD_KEY_STATE
              Added Entry KBD_KEY_SHORT to KBD_KEY_STATE
              Added Entry KBD_TEST_UI_KEY_IDLE to KBD_TEST_KEY_TEST_STATE
              Added Entry KBD_TEST_UI_KEY_SHORT_PRESSED to KBD_TEST_KEY_TEST_STATE
              Added new key states and corresponding key test states.
              The new key states are to be used by UI to detect PTT
              button shortcuts for Kodiak PoC 'One-Key Interface'.

Version     : 013.023    NON-DRAFT   18-May-2006    Boerge Fischer
Reason      : Change request
Reference   : Interface CR: ADB for SWAM BF06051853253. 
              Inspection minutes: ADB for SWAM BF06051857941. 
Description : Added Entry KBD_KEY_EXT_END to KBD_KEY
              Added Entry KBD_KEY_EXT_SEND to KBD_KEY
              Project info changed from Harlekin to Coconut.
              Added new external key codes:
                 - KBD_KEY_EXT_SEND
                 - KBD_KEY_EXT_END
              Note: New version of autogen no longer generate version
              flagging for CONST_TBL_ENTRY_VER.

Version     : 013.022    NON-DRAFT   01-Nov-2005    Vesa P. Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM VK05103144179. 
Description : Added Entry KBD_KEY_CAMERA to KBD_KEY
              Added Entry KBD_KEY_CAMERA_COVER to KBD_KEY
              Added Entry KBD_KEY_CAMERA_PREPARE to KBD_KEY
              Added Entry KBD_KEY_COVER_SOFT_1 to KBD_KEY
              Added Entry KBD_KEY_COVER_SOFT_2 to KBD_KEY
              Added Entry KBD_KEY_COVER_SOFT_3 to KBD_KEY
              New key codes added. 
              - KBD_KEY_CAMERA
              - KBD_KEY_CAMERA_PREPARE
              - KBD_KEY_CAMERA_COVER
              - KBD_KEY_COVER_SOFT_1
              - KBD_KEY_COVER_SOFT_2
              - KBD_KEY_COVER_SOFT_3

Version     : 013.021    NON-DRAFT   28-Jul-2005    Vesa P. Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM VK05072830018. 
              Inspection minutes: ADB for SWAM VK05072930818. 
Description : 1 new key code added. 
              - KBD_KEY_CLEAR

Version     : 013.020    NON-DRAFT   14-June-2004   Vesa Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM VK04060447498. 
              Inspection minutes: ADB for SWAM VK04061443211. 
Description : New interface to support a control of the external
              keycode mapping. 

Version     : 013.019    NON-DRAFT   14-May-2004    Vesa Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM VK04050745977. 
              Inspection minutes: ADB for SWAM VK04051443595. 
Description : Rotator test support 

Version     : 013.018    NON-DRAFT   13-May-2004    Vesa Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM VK04050645482. 
              Inspection minutes: ADB for SWAM VK04051334551. 
Description : Rotator simulation support 

Version     : 013.017    NON-DRAFT   01-Apr-2004    Vesa Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM VK04032538367. 
              Inspection minutes: ADB for SWAM VK04040231989. 
Description : Keypad (keyboard server)Pre-defined Rotator Speed choices in
              Menu 

Version     : 013.016    NON-DRAFT   12-Mar-2004    Vesa Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM VK04031235527. 
              Inspection minutes: ADB for SWAM  VK04031237429. 
Description : Support for disabling rotator events. 
              Update of macros.

Version     : 013.015    NON-DRAFT   25-Feb-2004    Vesa Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM  VK04021649189. 
              Inspection minutes: ADB for SWAM VK04022536440.
Description : New key codes for rotator and removal of internal messages. 

Version     : 013.014    NON-DRAFT   12-Feb-2004    Vesa Keranen
Reason      : Corrections
Reference   : Inspection minutes: ADB for SWAM VK04020551339.
Description : Corrections based on the inspection.
              New cover page due the header file moving from PCMS to
              continuus.

Version     : 013.013    NON-DRAFT   27-Jan-2004    Vesa Keranen
Reason      : Change request
Reference   : 009-9080: Keyboard server: ISI Interface for Rotator events. 
              Interface CR: ADB for SWAM VK04013030512. 
              Inspection minutes: ADB for SWAM VK04020551339.
Description : A new message, KBD_ROTATOR_EVENT_IND, has been added.

Version     : 013.012    NON-DRAFT   16-Oct-2003    Vesa Keranen
Reason      : Change request
Reference   : Interface CR: ADB for SWAM VK03101654032. 
              Inspection minutes: ADB for SWAM VK03101648494. 
Description : An external key code, KBD_KEY_EXT_PTT, has been added. 

Version     : 013.011    NON-DRAFT   07-Oct-2003    Vesa Keranen
Reason      : Corrections
Reference   : ADB for SWAM:  VK03092649902
              Comment ID: SM03100362173, CH03100252444
Description : Corrections based on the inspection, redundant bit tables
              removed.

Version     : 013.010    NON-DRAFT   24-Sep-2003    Vesa Keranen
Reason      : Improvements
Reference   : -
Description : Improvements caused by running-in of autogen. Autogenerated
              srvkbd_isi.h and i_kbd_m.html taken into use.

Version     : 013.009    NON-DRAFT   09-Jun-2003    Vesa Keranen
Reason      : Change request
Reference   : ADB for SWAM VK03041443971 for Interface CR.ADB for SWAM
              VK03060348130 for Inspection Minutes.
Description : 3 new key codes have been added.
              - KBD_KEY_HOT
              - KBD_KEY_RECORD
              - KBD_KEY_PTT

Version     : 013.008    NON-DRAFT   26-Mar-2003    Jani Lamberg
Reason      : New features & consistency check
Reference   : ADB for SWAM JL03031862541 for Interface CR.ADB for SWAM
              JL03032656169 for Inspection Minutes.
Description : KBD_KEY_TK_LAYOUTx_KEYx constants added

Version     : 013.007    NON-DRAFT   17-Mar-2003    Arno Tuominen
Reason      : New features & consistency check
Reference   : ADB for SWAM AT03020739111 & ISA RM-RIM 009-2767 for CR.
              ADB for SWAM JL02102849741 for Inspection Minutes.
Description : Updated version of the interface

Version     : 013.006    NON-DRAFT   18-Feb-2003    Arno Tuominen
Reason      : Change request
Reference   : ADB for SWAM AT03020739111 for interfrace CR.ISA RM-RIM
              009-2767 for feature CR.
Description : New KBD service: KBD_BUFFERING_CONTROL_REQ/RESP added.
              KBD_BUFFERING_ACK_NTF added.
              Symbol definitions for KBD_BUFFERING_START/STOP added.

Version     : 013.005    NON-DRAFT   30-Oct-2002    Jani Lamberg
Reason      : New features
Reference   : ADB for SWAM JS02070249698 & JL02100346289 for CR.
              ADB for SWAM AT03022432721 for Inspection Minutes.
Description : First version of the interface

------------------------------------------------------------------------------
*/

#ifndef _SRVKBD_ISI_H
#define _SRVKBD_ISI_H

#include "isi_conf.h"

#ifndef KBD_ISI_VERSION
#define KBD_ISI_VERSION
#define KBD_ISI_VERSION_Z  13
#define KBD_ISI_VERSION_Y  42
#endif

#define KBD_ISI_MIN_VERSION(z,y) \
 ((KBD_ISI_VERSION_Z == (z) && KBD_ISI_VERSION_Y >= (y)) || \
  (KBD_ISI_VERSION_Z > (z)))

#if !KBD_ISI_MIN_VERSION(13,5)
#error The specified interface version is not supported by this header file
#elif KBD_ISI_MIN_VERSION(13,43)
#error The specified interface version is not supported by this header file
#endif


/* ----------------------------------------------------------------------- */
/* Constants                                                               */
/* ----------------------------------------------------------------------- */

#define KBD_FILL_BYTE                            0x00
#define KBD_ROLLER_KEY_INFO_LENGTH               0x04
#define KBD_SINGLE_PRESS_KEY_EVENT_INFO_LENGTH   0x08
#define KBD_TEST_UI_KEY_RESULT_LENGTH            0x08
#define KBD_TEST_UI_ROTATOR_RESULT_LENGTH        0x08
/* constant for variable-length definitions */
#define KBD_ANY_SIZE                             1

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_KEY                                                 */
/* ----------------------------------------------------------------------- */
/* The bits from 8 to (0x1F00) in keycodes must remain unused to reserve some
   bits for UI's internal keycode handling. The upper bits and the whole
   lower byte can be used by the KBD server for keycodes.
*/
typedef uint16 KBD_KEY_CONST;

/* ITU-T keycodes */
#define KBD_KEY_0                                0x0030
#define KBD_KEY_1                                0x0031
#define KBD_KEY_2                                0x0032
#define KBD_KEY_3                                0x0033
#define KBD_KEY_4                                0x0034
#define KBD_KEY_5                                0x0035
#define KBD_KEY_6                                0x0036
#define KBD_KEY_7                                0x0037
#define KBD_KEY_8                                0x0038
#define KBD_KEY_9                                0x0039
#define KBD_KEY_STAR                             0x002A
#define KBD_KEY_HASH                             0x0023
/* QWERTY keycodes */
#define KBD_KEY_ROW1_COL1                        0x0080
#define KBD_KEY_ROW1_COL2                        0x0081
#define KBD_KEY_ROW1_COL3                        0x0082
#define KBD_KEY_ROW1_COL4                        0x0083
#define KBD_KEY_ROW1_COL5                        0x0084
#define KBD_KEY_ROW1_COL6                        0x0085
#define KBD_KEY_ROW1_COL7                        0x0086
#define KBD_KEY_ROW1_COL8                        0x0087
#define KBD_KEY_ROW1_COL9                        0x0088
#define KBD_KEY_ROW1_COL10                       0x0089
#define KBD_KEY_ROW1_COL11                       0x008A
#define KBD_KEY_ROW1_COL12                       0x008B
#define KBD_KEY_ROW2_COL1                        0x0090
#define KBD_KEY_ROW2_COL2                        0x0091
#define KBD_KEY_ROW2_COL3                        0x0092
#define KBD_KEY_ROW2_COL4                        0x0093
#define KBD_KEY_ROW2_COL5                        0x0094
#define KBD_KEY_ROW2_COL6                        0x0095
#define KBD_KEY_ROW2_COL7                        0x0096
#define KBD_KEY_ROW2_COL8                        0x0097
#define KBD_KEY_ROW2_COL9                        0x0098
#define KBD_KEY_ROW2_COL10                       0x0099
#define KBD_KEY_ROW2_COL11                       0x009A
#define KBD_KEY_ROW2_COL12                       0x009B
#define KBD_KEY_ROW3_COL1                        0x00A0
#define KBD_KEY_ROW3_COL2                        0x00A1
#define KBD_KEY_ROW3_COL3                        0x00A2
#define KBD_KEY_ROW3_COL4                        0x00A3
#define KBD_KEY_ROW3_COL5                        0x00A4
#define KBD_KEY_ROW3_COL6                        0x00A5
#define KBD_KEY_ROW3_COL7                        0x00A6
#define KBD_KEY_ROW3_COL8                        0x00A7
#define KBD_KEY_ROW3_COL9                        0x00A8
#define KBD_KEY_ROW3_COL10                       0x00A9
#define KBD_KEY_ROW3_COL11                       0x00AA
#define KBD_KEY_ROW3_COL12                       0x00AB
#define KBD_KEY_ROW4_COL1                        0x00B0
#define KBD_KEY_ROW4_COL2                        0x00B1
#define KBD_KEY_ROW4_COL3                        0x00B2
#define KBD_KEY_ROW4_COL4                        0x00B3
#define KBD_KEY_ROW4_COL5                        0x00B4
#define KBD_KEY_ROW4_COL6                        0x00B5
#define KBD_KEY_ROW4_COL7                        0x00B6
#define KBD_KEY_ROW4_COL8                        0x00B7
#define KBD_KEY_ROW4_COL9                        0x00B8
#define KBD_KEY_ROW4_COL10                       0x00B9
#define KBD_KEY_ROW4_COL11                       0x00BA
#define KBD_KEY_ROW4_COL12                       0x00BB
#define KBD_KEY_ROW5_COL1                        0x00C0
#define KBD_KEY_ROW5_COL2                        0x00C1
#define KBD_KEY_ROW5_COL3                        0x00C2
#define KBD_KEY_ROW5_COL4                        0x00C3
#define KBD_KEY_ROW5_COL5                        0x00C4
#define KBD_KEY_ROW5_COL6                        0x00C5
#define KBD_KEY_ROW5_COL7                        0x00C6
#define KBD_KEY_ROW5_COL8                        0x00C7
#define KBD_KEY_ROW5_COL9                        0x00C8
#define KBD_KEY_ROW5_COL10                       0x00C9
#define KBD_KEY_ROW5_COL11                       0x00CA
#define KBD_KEY_ROW5_COL12                       0x00CB
/* Touchkey keycodes */
#define KBD_KEY_TK_LAYOUT0_KEY0                  0x2000
#define KBD_KEY_TK_LAYOUT0_KEY1                  0x2001
#define KBD_KEY_TK_LAYOUT0_KEY2                  0x2002
#define KBD_KEY_TK_LAYOUT0_KEY3                  0x2003
#define KBD_KEY_TK_LAYOUT0_KEY4                  0x2004
#define KBD_KEY_TK_LAYOUT0_KEY5                  0x2005
#define KBD_KEY_TK_LAYOUT0_KEY6                  0x2006
#define KBD_KEY_TK_LAYOUT0_KEY7                  0x2007
#define KBD_KEY_TK_LAYOUT0_KEY8                  0x2008
#define KBD_KEY_TK_LAYOUT0_KEY9                  0x2009
#define KBD_KEY_TK_LAYOUT0_KEY10                 0x200A
#define KBD_KEY_TK_LAYOUT0_KEY11                 0x200B
#define KBD_KEY_TK_LAYOUT0_KEY12                 0x200C
#define KBD_KEY_TK_LAYOUT0_KEY13                 0x200D
#define KBD_KEY_TK_LAYOUT0_KEY14                 0x200E
#define KBD_KEY_TK_LAYOUT0_KEY15                 0x200F
#define KBD_KEY_TK_LAYOUT0_KEY16                 0x2010
#define KBD_KEY_TK_LAYOUT0_KEY17                 0x2011
#define KBD_KEY_TK_LAYOUT0_KEY18                 0x2012
#define KBD_KEY_TK_LAYOUT0_KEY19                 0x2013
#define KBD_KEY_TK_LAYOUT0_KEY20                 0x2014
#define KBD_KEY_TK_LAYOUT0_KEY21                 0x2015
#define KBD_KEY_TK_LAYOUT0_KEY22                 0x2016
#define KBD_KEY_TK_LAYOUT0_KEY23                 0x2017
#define KBD_KEY_TK_LAYOUT0_KEY24                 0x2018
#define KBD_KEY_TK_LAYOUT0_KEY25                 0x2019
#define KBD_KEY_TK_LAYOUT0_KEY26                 0x201A
#define KBD_KEY_TK_LAYOUT0_KEY27                 0x201B
#define KBD_KEY_TK_LAYOUT0_KEY28                 0x201C
#define KBD_KEY_TK_LAYOUT0_KEY29                 0x201D
#define KBD_KEY_TK_LAYOUT0_KEY30                 0x201E
#define KBD_KEY_TK_LAYOUT0_KEY31                 0x201F
#define KBD_KEY_TK_LAYOUT0_KEY32                 0x2020
#define KBD_KEY_TK_LAYOUT0_KEY33                 0x2021
#define KBD_KEY_TK_LAYOUT0_KEY34                 0x2022
#define KBD_KEY_TK_LAYOUT0_KEY35                 0x2023
#define KBD_KEY_TK_LAYOUT0_KEY36                 0x2024
#define KBD_KEY_TK_LAYOUT0_KEY37                 0x2025
#define KBD_KEY_TK_LAYOUT0_KEY38                 0x2026
#define KBD_KEY_TK_LAYOUT0_KEY39                 0x2027
#define KBD_KEY_TK_LAYOUT0_KEY40                 0x2028
#define KBD_KEY_TK_LAYOUT0_KEY41                 0x2029
#define KBD_KEY_TK_LAYOUT0_KEY42                 0x202A
#define KBD_KEY_TK_LAYOUT0_KEY43                 0x202B
#define KBD_KEY_TK_LAYOUT0_KEY44                 0x202C
#define KBD_KEY_TK_LAYOUT0_KEY45                 0x202D
#define KBD_KEY_TK_LAYOUT0_KEY46                 0x202E
#define KBD_KEY_TK_LAYOUT0_KEY47                 0x202F
#define KBD_KEY_TK_LAYOUT0_KEY48                 0x2030
#define KBD_KEY_TK_LAYOUT0_KEY49                 0x2031
#define KBD_KEY_TK_LAYOUT0_KEY50                 0x2032
#define KBD_KEY_TK_LAYOUT0_KEY51                 0x2033
#define KBD_KEY_TK_LAYOUT0_KEY52                 0x2034
#define KBD_KEY_TK_LAYOUT0_KEY53                 0x2035
#define KBD_KEY_TK_LAYOUT0_KEY54                 0x2036
#define KBD_KEY_TK_LAYOUT0_KEY55                 0x2037
#define KBD_KEY_TK_LAYOUT0_KEY56                 0x2038
#define KBD_KEY_TK_LAYOUT0_KEY57                 0x2039
#define KBD_KEY_TK_LAYOUT0_KEY58                 0x203A
#define KBD_KEY_TK_LAYOUT0_KEY59                 0x203B
#define KBD_KEY_TK_LAYOUT0_KEY60                 0x203C
#define KBD_KEY_TK_LAYOUT0_KEY61                 0x203D
#define KBD_KEY_TK_LAYOUT0_KEY62                 0x203E
#define KBD_KEY_TK_LAYOUT0_KEY63                 0x203F
#define KBD_KEY_TK_LAYOUT1_KEY0                  0x2040
#define KBD_KEY_TK_LAYOUT1_KEY1                  0x2041
#define KBD_KEY_TK_LAYOUT1_KEY2                  0x2042
#define KBD_KEY_TK_LAYOUT1_KEY3                  0x2043
#define KBD_KEY_TK_LAYOUT1_KEY4                  0x2044
#define KBD_KEY_TK_LAYOUT1_KEY5                  0x2045
#define KBD_KEY_TK_LAYOUT1_KEY6                  0x2046
#define KBD_KEY_TK_LAYOUT1_KEY7                  0x2047
#define KBD_KEY_TK_LAYOUT1_KEY8                  0x2048
#define KBD_KEY_TK_LAYOUT1_KEY9                  0x2049
#define KBD_KEY_TK_LAYOUT1_KEY10                 0x204A
#define KBD_KEY_TK_LAYOUT1_KEY11                 0x204B
#define KBD_KEY_TK_LAYOUT1_KEY12                 0x204C
#define KBD_KEY_TK_LAYOUT1_KEY13                 0x204D
#define KBD_KEY_TK_LAYOUT1_KEY14                 0x204E
#define KBD_KEY_TK_LAYOUT1_KEY15                 0x204F
#define KBD_KEY_TK_LAYOUT1_KEY16                 0x2050
#define KBD_KEY_TK_LAYOUT1_KEY17                 0x2051
#define KBD_KEY_TK_LAYOUT1_KEY18                 0x2052
#define KBD_KEY_TK_LAYOUT1_KEY19                 0x2053
#define KBD_KEY_TK_LAYOUT1_KEY20                 0x2054
#define KBD_KEY_TK_LAYOUT1_KEY21                 0x2055
#define KBD_KEY_TK_LAYOUT1_KEY22                 0x2056
#define KBD_KEY_TK_LAYOUT1_KEY23                 0x2057
#define KBD_KEY_TK_LAYOUT1_KEY24                 0x2058
#define KBD_KEY_TK_LAYOUT1_KEY25                 0x2059
#define KBD_KEY_TK_LAYOUT1_KEY26                 0x205A
#define KBD_KEY_TK_LAYOUT1_KEY27                 0x205B
#define KBD_KEY_TK_LAYOUT1_KEY28                 0x205C
#define KBD_KEY_TK_LAYOUT1_KEY29                 0x205D
#define KBD_KEY_TK_LAYOUT1_KEY30                 0x205E
#define KBD_KEY_TK_LAYOUT1_KEY31                 0x205F
#define KBD_KEY_TK_LAYOUT1_KEY32                 0x2060
#define KBD_KEY_TK_LAYOUT1_KEY33                 0x2061
#define KBD_KEY_TK_LAYOUT1_KEY34                 0x2062
#define KBD_KEY_TK_LAYOUT1_KEY35                 0x2063
#define KBD_KEY_TK_LAYOUT1_KEY36                 0x2064
#define KBD_KEY_TK_LAYOUT1_KEY37                 0x2065
#define KBD_KEY_TK_LAYOUT1_KEY38                 0x2066
#define KBD_KEY_TK_LAYOUT1_KEY39                 0x2067
#define KBD_KEY_TK_LAYOUT1_KEY40                 0x2068
#define KBD_KEY_TK_LAYOUT1_KEY41                 0x2069
#define KBD_KEY_TK_LAYOUT1_KEY42                 0x206A
#define KBD_KEY_TK_LAYOUT1_KEY43                 0x206B
#define KBD_KEY_TK_LAYOUT1_KEY44                 0x206C
#define KBD_KEY_TK_LAYOUT1_KEY45                 0x206D
#define KBD_KEY_TK_LAYOUT1_KEY46                 0x206E
#define KBD_KEY_TK_LAYOUT1_KEY47                 0x206F
#define KBD_KEY_TK_LAYOUT1_KEY48                 0x2070
#define KBD_KEY_TK_LAYOUT1_KEY49                 0x2071
#define KBD_KEY_TK_LAYOUT1_KEY50                 0x2072
#define KBD_KEY_TK_LAYOUT1_KEY51                 0x2073
#define KBD_KEY_TK_LAYOUT1_KEY52                 0x2074
#define KBD_KEY_TK_LAYOUT1_KEY53                 0x2075
#define KBD_KEY_TK_LAYOUT1_KEY54                 0x2076
#define KBD_KEY_TK_LAYOUT1_KEY55                 0x2077
#define KBD_KEY_TK_LAYOUT1_KEY56                 0x2078
#define KBD_KEY_TK_LAYOUT1_KEY57                 0x2079
#define KBD_KEY_TK_LAYOUT1_KEY58                 0x207A
#define KBD_KEY_TK_LAYOUT1_KEY59                 0x207B
#define KBD_KEY_TK_LAYOUT1_KEY60                 0x207C
#define KBD_KEY_TK_LAYOUT1_KEY61                 0x207D
#define KBD_KEY_TK_LAYOUT1_KEY62                 0x207E
#define KBD_KEY_TK_LAYOUT1_KEY63                 0x207F
#define KBD_KEY_TK_LAYOUT2_KEY0                  0x2080
#define KBD_KEY_TK_LAYOUT2_KEY1                  0x2081
#define KBD_KEY_TK_LAYOUT2_KEY2                  0x2082
#define KBD_KEY_TK_LAYOUT2_KEY3                  0x2083
#define KBD_KEY_TK_LAYOUT2_KEY4                  0x2084
#define KBD_KEY_TK_LAYOUT2_KEY5                  0x2085
#define KBD_KEY_TK_LAYOUT2_KEY6                  0x2086
#define KBD_KEY_TK_LAYOUT2_KEY7                  0x2087
#define KBD_KEY_TK_LAYOUT2_KEY8                  0x2088
#define KBD_KEY_TK_LAYOUT2_KEY9                  0x2089
#define KBD_KEY_TK_LAYOUT2_KEY10                 0x208A
#define KBD_KEY_TK_LAYOUT2_KEY11                 0x208B
#define KBD_KEY_TK_LAYOUT2_KEY12                 0x208C
#define KBD_KEY_TK_LAYOUT2_KEY13                 0x208D
#define KBD_KEY_TK_LAYOUT2_KEY14                 0x208E
#define KBD_KEY_TK_LAYOUT2_KEY15                 0x208F
#define KBD_KEY_TK_LAYOUT2_KEY16                 0x2090
#define KBD_KEY_TK_LAYOUT2_KEY17                 0x2091
#define KBD_KEY_TK_LAYOUT2_KEY18                 0x2092
#define KBD_KEY_TK_LAYOUT2_KEY19                 0x2093
#define KBD_KEY_TK_LAYOUT2_KEY20                 0x2094
#define KBD_KEY_TK_LAYOUT2_KEY21                 0x2095
#define KBD_KEY_TK_LAYOUT2_KEY22                 0x2096
#define KBD_KEY_TK_LAYOUT2_KEY23                 0x2097
#define KBD_KEY_TK_LAYOUT2_KEY24                 0x2098
#define KBD_KEY_TK_LAYOUT2_KEY25                 0x2099
#define KBD_KEY_TK_LAYOUT2_KEY26                 0x209A
#define KBD_KEY_TK_LAYOUT2_KEY27                 0x209B
#define KBD_KEY_TK_LAYOUT2_KEY28                 0x209C
#define KBD_KEY_TK_LAYOUT2_KEY29                 0x209D
#define KBD_KEY_TK_LAYOUT2_KEY30                 0x209E
#define KBD_KEY_TK_LAYOUT2_KEY31                 0x209F
#define KBD_KEY_TK_LAYOUT2_KEY32                 0x20A0
#define KBD_KEY_TK_LAYOUT2_KEY33                 0x20A1
#define KBD_KEY_TK_LAYOUT2_KEY34                 0x20A2
#define KBD_KEY_TK_LAYOUT2_KEY35                 0x20A3
#define KBD_KEY_TK_LAYOUT2_KEY36                 0x20A4
#define KBD_KEY_TK_LAYOUT2_KEY37                 0x20A5
#define KBD_KEY_TK_LAYOUT2_KEY38                 0x20A6
#define KBD_KEY_TK_LAYOUT2_KEY39                 0x20A7
#define KBD_KEY_TK_LAYOUT2_KEY40                 0x20A8
#define KBD_KEY_TK_LAYOUT2_KEY41                 0x20A9
#define KBD_KEY_TK_LAYOUT2_KEY42                 0x20AA
#define KBD_KEY_TK_LAYOUT2_KEY43                 0x20AB
#define KBD_KEY_TK_LAYOUT2_KEY44                 0x20AC
#define KBD_KEY_TK_LAYOUT2_KEY45                 0x20AD
#define KBD_KEY_TK_LAYOUT2_KEY46                 0x20AE
#define KBD_KEY_TK_LAYOUT2_KEY47                 0x20AF
#define KBD_KEY_TK_LAYOUT2_KEY48                 0x20B0
#define KBD_KEY_TK_LAYOUT2_KEY49                 0x20B1
#define KBD_KEY_TK_LAYOUT2_KEY50                 0x20B2
#define KBD_KEY_TK_LAYOUT2_KEY51                 0x20B3
#define KBD_KEY_TK_LAYOUT2_KEY52                 0x20B4
#define KBD_KEY_TK_LAYOUT2_KEY53                 0x20B5
#define KBD_KEY_TK_LAYOUT2_KEY54                 0x20B6
#define KBD_KEY_TK_LAYOUT2_KEY55                 0x20B7
#define KBD_KEY_TK_LAYOUT2_KEY56                 0x20B8
#define KBD_KEY_TK_LAYOUT2_KEY57                 0x20B9
#define KBD_KEY_TK_LAYOUT2_KEY58                 0x20BA
#define KBD_KEY_TK_LAYOUT2_KEY59                 0x20BB
#define KBD_KEY_TK_LAYOUT2_KEY60                 0x20BC
#define KBD_KEY_TK_LAYOUT2_KEY61                 0x20BD
#define KBD_KEY_TK_LAYOUT2_KEY62                 0x20BE
#define KBD_KEY_TK_LAYOUT2_KEY63                 0x20BF
#define KBD_KEY_TK_LAYOUT3_KEY0                  0x20C0
#define KBD_KEY_TK_LAYOUT3_KEY1                  0x20C1
#define KBD_KEY_TK_LAYOUT3_KEY2                  0x20C2
#define KBD_KEY_TK_LAYOUT3_KEY3                  0x20C3
#define KBD_KEY_TK_LAYOUT3_KEY4                  0x20C4
#define KBD_KEY_TK_LAYOUT3_KEY5                  0x20C5
#define KBD_KEY_TK_LAYOUT3_KEY6                  0x20C6
#define KBD_KEY_TK_LAYOUT3_KEY7                  0x20C7
#define KBD_KEY_TK_LAYOUT3_KEY8                  0x20C8
#define KBD_KEY_TK_LAYOUT3_KEY9                  0x20C9
#define KBD_KEY_TK_LAYOUT3_KEY10                 0x20CA
#define KBD_KEY_TK_LAYOUT3_KEY11                 0x20CB
#define KBD_KEY_TK_LAYOUT3_KEY12                 0x20CC
#define KBD_KEY_TK_LAYOUT3_KEY13                 0x20CD
#define KBD_KEY_TK_LAYOUT3_KEY14                 0x20CE
#define KBD_KEY_TK_LAYOUT3_KEY15                 0x20CF
#define KBD_KEY_TK_LAYOUT3_KEY16                 0x20D0
#define KBD_KEY_TK_LAYOUT3_KEY17                 0x20D1
#define KBD_KEY_TK_LAYOUT3_KEY18                 0x20D2
#define KBD_KEY_TK_LAYOUT3_KEY19                 0x20D3
#define KBD_KEY_TK_LAYOUT3_KEY20                 0x20D4
#define KBD_KEY_TK_LAYOUT3_KEY21                 0x20D5
#define KBD_KEY_TK_LAYOUT3_KEY22                 0x20D6
#define KBD_KEY_TK_LAYOUT3_KEY23                 0x20D7
#define KBD_KEY_TK_LAYOUT3_KEY24                 0x20D8
#define KBD_KEY_TK_LAYOUT3_KEY25                 0x20D9
#define KBD_KEY_TK_LAYOUT3_KEY26                 0x20DA
#define KBD_KEY_TK_LAYOUT3_KEY27                 0x20DB
#define KBD_KEY_TK_LAYOUT3_KEY28                 0x20DC
#define KBD_KEY_TK_LAYOUT3_KEY29                 0x20DD
#define KBD_KEY_TK_LAYOUT3_KEY30                 0x20DE
#define KBD_KEY_TK_LAYOUT3_KEY31                 0x20DF
#define KBD_KEY_TK_LAYOUT3_KEY32                 0x20E0
#define KBD_KEY_TK_LAYOUT3_KEY33                 0x20E1
#define KBD_KEY_TK_LAYOUT3_KEY34                 0x20E2
#define KBD_KEY_TK_LAYOUT3_KEY35                 0x20E3
#define KBD_KEY_TK_LAYOUT3_KEY36                 0x20E4
#define KBD_KEY_TK_LAYOUT3_KEY37                 0x20E5
#define KBD_KEY_TK_LAYOUT3_KEY38                 0x20E6
#define KBD_KEY_TK_LAYOUT3_KEY39                 0x20E7
#define KBD_KEY_TK_LAYOUT3_KEY40                 0x20E8
#define KBD_KEY_TK_LAYOUT3_KEY41                 0x20E9
#define KBD_KEY_TK_LAYOUT3_KEY42                 0x20EA
#define KBD_KEY_TK_LAYOUT3_KEY43                 0x20EB
#define KBD_KEY_TK_LAYOUT3_KEY44                 0x20EC
#define KBD_KEY_TK_LAYOUT3_KEY45                 0x20ED
#define KBD_KEY_TK_LAYOUT3_KEY46                 0x20EE
#define KBD_KEY_TK_LAYOUT3_KEY47                 0x20EF
#define KBD_KEY_TK_LAYOUT3_KEY48                 0x20F0
#define KBD_KEY_TK_LAYOUT3_KEY49                 0x20F1
#define KBD_KEY_TK_LAYOUT3_KEY50                 0x20F2
#define KBD_KEY_TK_LAYOUT3_KEY51                 0x20F3
#define KBD_KEY_TK_LAYOUT3_KEY52                 0x20F4
#define KBD_KEY_TK_LAYOUT3_KEY53                 0x20F5
#define KBD_KEY_TK_LAYOUT3_KEY54                 0x20F6
#define KBD_KEY_TK_LAYOUT3_KEY55                 0x20F7
#define KBD_KEY_TK_LAYOUT3_KEY56                 0x20F8
#define KBD_KEY_TK_LAYOUT3_KEY57                 0x20F9
#define KBD_KEY_TK_LAYOUT3_KEY58                 0x20FA
#define KBD_KEY_TK_LAYOUT3_KEY59                 0x20FB
#define KBD_KEY_TK_LAYOUT3_KEY60                 0x20FC
#define KBD_KEY_TK_LAYOUT3_KEY61                 0x20FD
#define KBD_KEY_TK_LAYOUT3_KEY62                 0x20FE
#define KBD_KEY_TK_LAYOUT3_KEY63                 0x20FF
/* External keycodes */
#define KBD_KEY_EXT_PTT                          0x4001
#define KBD_KEY_EXT_SEND                         0x4002
#define KBD_KEY_EXT_END                          0x4003
#define KBD_KEY_CURSOR                           0x4004
/* Special keycodes */
#define KBD_KEY_NO_KEY                           0xE000
#define KBD_KEY_POWER                            0xE001
#define KBD_KEY_SLIDE                            0xE002
#define KBD_KEY_SOFT_L                           0xE003
#define KBD_KEY_SOFT_R                           0xE004
#define KBD_KEY_SEND                             0xE005
#define KBD_KEY_END                              0xE006
#define KBD_KEY_ARROW_U                          0xE007
#define KBD_KEY_ARROW_D                          0xE008
#define KBD_KEY_ROLLER                           0xE009
#define KBD_KEY_VOL_UP                           0xE00A
#define KBD_KEY_VOL_DOWN                         0xE00B
#define KBD_KEY_SELECT                           0xE00C
#define KBD_KEY_ARROW_L                          0xE00D
#define KBD_KEY_ARROW_R                          0xE00E
#define KBD_KEY_VOICE_RECOG                      0xE00F
#define KBD_KEY_FLIP                             0xE010
#define KBD_KEY_ADC1_1                           0xE011
#define KBD_KEY_ADC1_2                           0xE012
#define KBD_KEY_ADC1_3                           0xE013
#define KBD_KEY_ADC1_4                           0xE014
#define KBD_KEY_ADC1_5                           0xE015
#define KBD_KEY_ADC1_6                           0xE016
#define KBD_KEY_ADC1_7                           0xE017
#define KBD_KEY_ADC1_8                           0xE018
#define KBD_KEY_ADC2_1                           0xE021
#define KBD_KEY_ADC2_2                           0xE022
#define KBD_KEY_ADC2_3                           0xE023
#define KBD_KEY_ADC2_4                           0xE024
#define KBD_KEY_ADC2_5                           0xE025
#define KBD_KEY_ADC2_6                           0xE026
#define KBD_KEY_ADC2_7                           0xE027
#define KBD_KEY_ADC2_8                           0xE028
#define KBD_KEY_P0_0_PIN                         0xE031
#define KBD_KEY_P0_1_PIN                         0xE032
#define KBD_KEY_P0_2_PIN                         0xE033
#define KBD_KEY_P0_3_PIN                         0xE034
#define KBD_KEY_P0_4_PIN                         0xE035
#define KBD_KEY_P0_5_PIN                         0xE036
#define KBD_KEY_P1_0_PIN                         0xE041
#define KBD_KEY_P1_1_PIN                         0xE042
#define KBD_KEY_P1_2_PIN                         0xE043
#define KBD_KEY_P1_3_PIN                         0xE044
#define KBD_KEY_P1_4_PIN                         0xE045
#define KBD_KEY_P1_5_PIN                         0xE046
#define KBD_KEY_HOT                              0xE051
#define KBD_KEY_CLEAR                            0xE052
/* Vertu Concierge key */
#define KBD_KEY_TPARTY                           0xE054
#define KBD_KEY_RECORD                           0xE055
#define KBD_KEY_PTT                              0xE056
#define KBD_KEY_ROTATOR_U                        0xE057
#define KBD_KEY_ROTATOR_D                        0xE058
#define KBD_KEY_ROTATOR_L                        0xE059
#define KBD_KEY_ROTATOR_R                        0xE05A
#define KBD_KEY_UI_ROTATION                      0xE05B
/* Camera full press */
#define KBD_KEY_CAMERA                           0xE05C
/* Camera light press */
#define KBD_KEY_CAMERA_PREPARE                   0xE05D
/* Camera lense cover */
#define KBD_KEY_CAMERA_COVER                     0xE05E
/* Used with Cover UI */
#define KBD_KEY_COVER_SOFT_1                     0xE05F
/* Used with Cover UI */
#define KBD_KEY_COVER_SOFT_2                     0xE060
/* Used with Cover UI */
#define KBD_KEY_COVER_SOFT_3                     0xE061
#define KBD_KEY_NAVISLIDE_LEFT                   0xE062
#define KBD_KEY_NAVISLIDE_RIGHT                  0xE063
#define KBD_KEY_MENU                             0xE064
#define KBD_KEY_DEVICE_0                         0xE065
#define KBD_KEY_DEVICE_1                         0xE066
#define KBD_KEY_DEVICE_2                         0xE067
/* Used to launch the electromagnet */
#define KBD_KEY_LAUNCH_MAGNET                    0xE068
/* Used by external music player/headset */
#define KBD_KEY_EXT_MP_PLAY_PAUSE                0xE069
/* Used by external music player/headset */
#define KBD_KEY_EXT_MP_STOP                      0xE06A
/* Used by external music player/headset */
#define KBD_KEY_EXT_MP_PREV_TRACK                0xE06B
/* Used by external music player/headset */
#define KBD_KEY_EXT_MP_NEXT_TRACK                0xE06C
/* Used to toggle between work and relax UI mode */
#define KBD_KEY_UI_RELAX_MODE                    0xE06D
/* Media Key - Launch browser */
#define KBD_KEY_MEDIA                            0xE06E
/* Cellular Video key */
#define KBD_KEY_CV                               0xE06F
/* Physical keylock (switch type) */
#define KBD_KEY_KEYLOCK                          0xE070
/* Physical keylock (spring type) */
#define KBD_KEY_KEYLOCK_TOGGLE                   0xE071
#define KBD_KEY_CHANNEL_A                        0xE072
#define KBD_KEY_CHANNEL_B                        0xE073
#define KBD_KEY_FUNCTION                         0xE074
#define KBD_KEY_PHONE_LOCK                       0xE075
#define KBD_KEY_MUTE_KEY                         0xE076
/* Recall last number */
#define KBD_KEY_RECALL                           0xE077
#define KBD_KEY_STORE_MEMORY                     0xE078
#define KBD_KEY_AUXILIARY                        0xE079
/* Hard key code for ie. people quick launch key */
#define KBD_KEY_QUICK_LAUNCH                     0xE07A
/* Hard key code for messaging quick launch */
#define KBD_KEY_QUICK_LAUNCH_MESSAGING           0xE07B
/* Hard key code for social networking quick launch */
#define KBD_KEY_QUICK_LAUNCH_SOCIAL_NETWORKING   0xE07C
/* Physical back key for EVO */
#define KBD_KEY_BACK                             0xE07D

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_STATUS                                              */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_STATUS_CONST;

#define KBD_OK                                   0x00
#define KBD_FAIL                                 0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_KEY_STATE                                           */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_KEY_STATE_CONST;

#define KBD_KEY_UP                               0x00
#define KBD_KEY_DOWN                             0x01
#define KBD_KEY_LONG                             0x02
#define KBD_KEY_REPEAT                           0x03
#define KBD_KEY_SHORT                            0x04
#define KBD_KEY_IDLE                             0x05

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_ROLLER_DIRECTION                                    */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_ROLLER_DIRECTION_CONST;

#define KBD_ROLLER_NORTH                         0x01
#define KBD_ROLLER_SOUTH                         0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_ROTATOR_MODE                                        */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_ROTATOR_MODE_CONST;

#define KBD_ROTATOR_SLOW_MODE                    0x00
#define KBD_ROTATOR_FAST_MODE_START              0x01
#define KBD_ROTATOR_FAST_MODE_STEP               0x02
#define KBD_ROTATOR_FAST_MODE_STOP               0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_ROTATOR_DIRECTION                                   */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_ROTATOR_DIRECTION_CONST;

#define KBD_ROTATOR_CLOCKWISE                    0x00
#define KBD_ROTATOR_ANTI_CLOCKWISE               0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_ROTATOR_CONTROL_ACTION                              */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_ROTATOR_CONTROL_ACTION_CONST;

#define KBD_ROTATOR_ENABLE                       0x00
#define KBD_ROTATOR_DISABLE                      0x01
#define KBD_ROTATOR_SPEED_SETTING_0              0x02
#define KBD_ROTATOR_SPEED_SETTING_1              0x03
#define KBD_ROTATOR_SPEED_SETTING_2              0x04
#define KBD_ROTATOR_SPEED_SETTING_3              0x05
#define KBD_ROTATOR_SPEED_SETTING_4              0x06

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_CONTROL_ACTION                                      */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_CONTROL_ACTION_CONST;

#define KBD_KEYCODE_MAPPING_PRIMARY              0x00
#define KBD_KEYCODE_MAPPING_SECONDARY            0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_ROTATOR_CONTROL_STATUS                              */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_ROTATOR_CONTROL_STATUS_CONST;

#define KBD_ROTATOR_OK                           0x00
#define KBD_ROTATOR_FAIL                         0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_SLIDE_STATE                                         */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_SLIDE_STATE_CONST;

#define KBD_SLIDE_CLOSED                         0x00
#define KBD_SLIDE_OPEN                           0x01
#define KBD_SLIDE_SHORT_OPEN                     0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_FLIP_STATE                                          */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_FLIP_STATE_CONST;

#define KBD_FLIP_CLOSED                          0x00
#define KBD_FLIP_OPEN                            0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_KEYLOCK_STATE                                       */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_KEYLOCK_STATE_CONST;

#define KBD_KEYLOCK_CLOSED                       0x00
#define KBD_KEYLOCK_OPEN                         0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_PWR_KEY_STATUS                                      */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_PWR_KEY_STATUS_CONST;

#define KBD_PROCEED                              0x00
#define KBD_ABORT                                0x01
#define KBD_WAIT                                 0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_TEST_ACTION                                         */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_TEST_ACTION_CONST;

#define KBD_TEST_UI_START                        0x00
#define KBD_TEST_UI_RESULT_GET                   0x01
#define KBD_TEST_UI_STOP                         0x02
#define KBD_TEST_FLIP_CONNECTION                 0x03
#define KBD_TEST_FLIP_POWER_ON                   0x04
#define KBD_TEST_FLIP_POWER_OFF                  0x05

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_TEST_STATUS                                         */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_TEST_STATUS_CONST;

#define KBD_TEST_OK                              0x00
#define KBD_TEST_FAIL                            0x01
#define KBD_TEST_BUSY                            0x02
#define KBD_TEST_NOT_SUPPORTED                   0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_BUFFERING_ACTION                                    */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_BUFFERING_ACTION_CONST;

#define KBD_BUFFERING_STOP                       0x00
#define KBD_BUFFERING_START                      0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_POINTING_DEVICE_CONTROL_ACTION - Valid from version 013.028 */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_POINTING_DEVICE_CONTROL_ACTION_CONST;

#define KBD_POINTING_DEVICE_LOW_SENSITIVITY      0x00
#define KBD_POINTING_DEVICE_HIGH_SENSITIVITY     0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_READ_RAW_DATA_DEVICE - Valid from version 013.033   */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_READ_RAW_DATA_DEVICE_CONST;

/* Read raw data from capacitive key device */
#define KBD_READ_RAW_DATA_CAPACITIVE_KEY         0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_READ_RAW_DATA_SIZE - Valid from version 013.033     */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_READ_RAW_DATA_SIZE_CONST;

#define KBD_READ_RAW_DATA_SIZE_8                 0x00  /* 8-bit data */
#define KBD_READ_RAW_DATA_SIZE_16                0x01  /* 16-bit data */
#define KBD_READ_RAW_DATA_SIZE_32                0x02  /* 32-bit data */

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_POWER_CONTROL_DEVICE_ID - Valid from version 013.036 */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_POWER_CONTROL_DEVICE_ID_CONST;

/* Capacitive key device identifier */
#define KBD_POWER_CONTROL_CAPACITIVE_KEY         0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_POWER_CONTROL_MODE - Valid from version 013.036     */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_POWER_CONTROL_MODE_CONST;

/* Enter power off state */
#define KBD_POWER_CONTROL_MODE_OFF               0x00
/* Enter lowest supported state */
#define KBD_POWER_CONTROL_MODE_LOW               0x01
/* Enter default power state */
#define KBD_POWER_CONTROL_MODE_DEFAULT           0x02
/* Enter maximum power state */
#define KBD_POWER_CONTROL_MODE_MAX               0x03
/* Increase power state */
#define KBD_POWER_CONTROL_MODE_STEP_UP           0x04
/* Decrease power state */
#define KBD_POWER_CONTROL_MODE_STEP_DOWN         0x05

/* ----------------------------------------------------------------------- */
/* Constant Table: KBD_CONFIG_ACTION                                       */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_CONFIG_ACTION_CONST;

/* Deactivate keyboard events */
#define KBD_CONFIG_ACTION_DEACTIVATE             0x01
/* Activate keyboard events */
#define KBD_CONFIG_ACTION_ACTIVATE               0x02
/* Deactivate key event simulation */
#define KBD_CONFIG_ACTION_SIM_DEACTIVATE         0x03
/* Activate key event simulation */
#define KBD_CONFIG_ACTION_SIM_ACTIVATE           0x04
/* Deactivate simulation and keyboard events */
#define KBD_CONFIG_ACTION_KEY_SIM_DEACTIVATE     0x05
/* Activate simulation and keyboard events */
#define KBD_CONFIG_ACTION_KEY_SIM_ACTIVATE       0x06
/* Activate selected keys */
#define KBD_CONFIG_ACTION_ACTIVATE_SPECIFIC_KEYS 0x07

/* ----------------------------------------------------------------------- */
/* Bitmask Table: KBD_TEST_KEY_TEST_STATE                                  */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_TEST_KEY_TEST_STATE_CONST;

#define KBD_TEST_UI_KEY_PRESSED                  0x01  /* -------1 */
#define KBD_TEST_UI_KEY_RELEASED                 0x02  /* ------1- */
#define KBD_TEST_UI_KEY_LONG_PRESSED             0x04  /* -----1-- */
#define KBD_TEST_UI_KEY_REPEAT_PRESSED           0x08  /* ----1--- */
#define KBD_TEST_UI_KEY_OPENED                   0x10  /* ---1---- */
#define KBD_TEST_UI_KEY_CLOSED                   0x20  /* --1----- */
#define KBD_TEST_UI_KEY_SHORT_PRESSED            0x40  /* -1------ */
#define KBD_TEST_UI_KEY_IDLE                     0x80  /* 1------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: KBD_DEVICE_STATUS                                        */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_DEVICE_STATUS_CONST;

#define KBD_ADC_KEYBOARD_MASK                    0x01  /* -------1 */
#define KBD_MATRIX_KEYBOARD_MASK                 0x02  /* ------1- */
#define KBD_METAL_DOME_KEYBOARD_MASK             0x04  /* -----1-- */
#define KBD_FLIP_KEYBOARD_MASK                   0x08  /* ----1--- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: KBD_SPECIAL_KEY_STATUS                                   */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_SPECIAL_KEY_STATUS_CONST;

#define KBD_KEY_SLIDE_MASK                       0x01  /* -------1 */
#define KBD_KEY_POWER_MASK                       0x02  /* ------1- */
#define KBD_KEY_FLIP_MASK                        0x04  /* -----1-- */
#define KBD_KEY_GENIO_MASK                       0x08  /* ----1--- */
#define KBD_KEY_KEYLOCK_MASK                     0x10  /* ---1---- */
#define KBD_KEY_CAMERA_COVER_MASK                0x20  /* --1----- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: KBD_SPECIAL_KEY_STATUS_KDI_P0                            */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_SPECIAL_KEY_STATUS_KDI_P0_CONST;

#define KBD_KEY_P0_0_PIN_MASK                    0x01  /* -------1 */
#define KBD_KEY_P0_1_PIN_MASK                    0x02  /* ------1- */
#define KBD_KEY_P0_2_PIN_MASK                    0x04  /* -----1-- */
#define KBD_KEY_P0_3_PIN_MASK                    0x08  /* ----1--- */
#define KBD_KEY_P0_4_PIN_MASK                    0x10  /* ---1---- */
#define KBD_KEY_P0_5_PIN_MASK                    0x20  /* --1----- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: KBD_SPECIAL_KEY_STATUS_KDI_P1                            */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_SPECIAL_KEY_STATUS_KDI_P1_CONST;

#define KBD_KEY_P1_0_PIN_MASK                    0x01  /* -------1 */
#define KBD_KEY_P1_1_PIN_MASK                    0x02  /* ------1- */
#define KBD_KEY_P1_2_PIN_MASK                    0x04  /* -----1-- */
#define KBD_KEY_P1_3_PIN_MASK                    0x08  /* ----1--- */
#define KBD_KEY_P1_4_PIN_MASK                    0x10  /* ---1---- */
#define KBD_KEY_P1_5_PIN_MASK                    0x20  /* --1----- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: KBD_MULTI_KEY_STATUS                                     */
/* ----------------------------------------------------------------------- */
typedef uint8 KBD_MULTI_KEY_STATUS_CONST;

#define KBD_ROLLER_MASK                          0x01  /* -------1 */

/* ----------------------------------------------------------------------- */
/* Message ID's                                                            */
/* ----------------------------------------------------------------------- */
/* The message ID's from 0xA0 to 0xBF have been reserved only for the
   internal use of the KBD Server. 
*/

#define KBD_EVENT_IND                            0x00
#define KBD_INFO_REQ                             0x01
#define KBD_INFO_RESP                            0x02
#define KBD_CONFIG_REQ                           0x03
#define KBD_CONFIG_RESP                          0x04
#define KBD_ROTATOR_CONTROL_REQ                  0x05
#define KBD_ROTATOR_CONTROL_RESP                 0x06
#define KBD_CONTROL_REQ                          0x07
#define KBD_CONTROL_RESP                         0x08
#define KBD_PWR_KEY_CHECK_REQ                    0x0E
#define KBD_PWR_KEY_CHECK_RESP                   0x0F
#define KBD_PWR_KEY_INFO_IND                     0x10
#define KBD_EVENT_SIMULATION_REQ                 0x11
#define KBD_EVENT_SIMULATION_RESP                0x12
#define KBD_TEST_REQ                             0x15
#define KBD_TEST_RESP                            0x16
#define KBD_BUFFERING_CONTROL_REQ                0x17
#define KBD_BUFFERING_CONTROL_RESP               0x18
#define KBD_BUFFERING_ACK_NTF                    0x19
#define KBD_ROTATOR_EVENT_IND                    0x22
#define KBD_POINTING_DEVICE_CONTROL_REQ          0x23
#define KBD_POINTING_DEVICE_CONTROL_RESP         0x24
#define KBD_CAPACITIVE_KEY_CONTROL_REQ           0x25
#define KBD_CAPACITIVE_KEY_CONTROL_RESP          0x26
#define KBD_READ_RAW_DATA_REQ                    0x27
#define KBD_READ_RAW_DATA_RESP                   0x28
#define KBD_POWER_CONTROL_REQ                    0x29
#define KBD_POWER_CONTROL_RESP                   0x2A

/* ----------------------------------------------------------------------- */
/* Subblock ID's                                                           */
/* ----------------------------------------------------------------------- */

#define KBD_ROLLER_KEY_INFO                      0x00
#define KBD_SINGLE_PRESS_KEY_EVENT_INFO          0x01
#define KBD_ROTATOR_EVENT_INFO                   0x03
#define KBD_TEST_UI_KEY_RESULT                   0x02
#define KBD_TEST_UI_ROTATOR_RESULT               0x04
#define KBD_POINTING_DEVICE_INFO                 0x05
#define KBD_CAPACITIVE_KEY_GLOBAL_SETTINGS       0x06
#define KBD_CAPACITIVE_KEY_TYPE1_SETTINGS        0x07
#define KBD_CAPACITIVE_KEY_TYPE2_SETTINGS        0x08
#define KBD_RAW_DATA_INFO                        0x09
#define KBD_CONFIG_ACTION_ACTIVATION_MASK        0x0A

/* ----------------------------------------------------------------------- */
/* Sequence: KBD_TEST_UI_KEY_T                                             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint16  key_code;     /* Values from the constant table KBD_KEY */
    uint8   fill_byte;
    /* Values from the bitmask table KBD_TEST_KEY_TEST_STATE */
    uint8   key_test_state;
    } KBD_TEST_UI_KEY_T;


/* ----------------------------------------------------------------------- */
/* Subblock: KBD_ROLLER_KEY_INFO                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   id;
    uint8   length;
    /* Values from the constant table KBD_ROLLER_DIRECTION */
    uint8   direction;
    uint8   movement;
    } KBD_ROLLER_KEY_INFO_T;


/* ----------------------------------------------------------------------- */
/* Subblock: KBD_SINGLE_PRESS_KEY_EVENT_INFO                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   id;
    uint8   length;
    uint16  key_code;     /* Values from the constant table KBD_KEY */
    uint8   state;        /* Values from the constant table KBD_KEY_STATE */
    uint8   fill_byte1;
    uint8   fill_byte2;
    uint8   fill_byte3;
    } KBD_SINGLE_PRESS_KEY_EVENT_INFO_T;


/* ----------------------------------------------------------------------- */
/* Subblock: KBD_ROTATOR_EVENT_INFO                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   id;
    uint8   length;
    uint8   mode;       /* Values from the constant table KBD_ROTATOR_MODE */
    /* Values from the constant table KBD_ROTATOR_DIRECTION */
    uint8   direction;
    uint16  ticks;
    uint8   fill_byte1;
    uint8   fill_byte2;
    } KBD_ROTATOR_EVENT_INFO_T;


/* ----------------------------------------------------------------------- */
/* Subblock: KBD_TEST_UI_KEY_RESULT                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   id;
    uint8   fill_byte1;
    uint16  length;
    uint8   fill_byte2;
    uint8   fill_byte3;
    uint16  number_of_keys;
    KBD_TEST_UI_KEY_T key_table[KBD_ANY_SIZE];
    } KBD_TEST_UI_KEY_RESULT_T;


/* ----------------------------------------------------------------------- */
/* Subblock: KBD_TEST_UI_ROTATOR_RESULT                                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   id;
    uint8   fill_byte;
    uint16  length;
    /* 
       Cumulative value of clockwise ticks
    */
    uint16  clockwise_ticks;
    /* 
       Cumulative value of anticlockwise ticks
    */
    uint16  anticlockwise_ticks;
    } KBD_TEST_UI_ROTATOR_RESULT_T;


/* ----------------------------------------------------------------------- */
/* Subblock: KBD_POINTING_DEVICE_INFO - Valid from version 013.028         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   id;
    uint8   length;
    int8    x_axis;
    int8    y_axis;
    } KBD_POINTING_DEVICE_INFO_T;


/* ----------------------------------------------------------------------- */
/* Subblock: KBD_CAPACITIVE_KEY_GLOBAL_SETTINGS - Valid from version 013.031 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   id;
    uint8   length;
    uint8   fill_byte;
    uint8   fill_byte1;
    /* 
       Power mode value
    */
    uint16  powermode;
    /* 
       Burst pulses or Ambience ctrl0
    */
    uint16  repetition_level;
    /* 
       Detector Integrator or Ambience ctrl1
    */
    uint16  detector_integrator;
    /* 
       Filtering Level or Ambience ctrl2
    */
    uint16  key_filtering_level;
    } KBD_CAPACITIVE_KEY_GLOBAL_SETTINGS_T;


/* ----------------------------------------------------------------------- */
/* Subblock: KBD_CAPACITIVE_KEY_TYPE1_SETTINGS - Valid from version 013.031 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   id;
    uint8   length;
    uint8   key_index;
    uint8   matrix_burst_pulses;
    uint8   detect_threshold;
    uint8   aks_offset;
    uint8   fill_byte;
    uint8   fill_byte1;
    } KBD_CAPACITIVE_KEY_TYPE1_SETTINGS_T;


/* ----------------------------------------------------------------------- */
/* Subblock: KBD_CAPACITIVE_KEY_TYPE2_SETTINGS - Valid from version 013.031 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   id;
    uint8   length;
    uint8   stage_number;
    uint8   parameter_mask;
    /* 
       Stage configuration bits [6:0]
    */
    uint16  stage_connection_low;
    /* 
       Stage configuration bits [13:7]
    */
    uint16  stage_connection_high;
    /* 
       AFE offset value
    */
    uint16  afe_offset;
    /* 
       Sensitivity value
    */
    uint16  sensitivity;
    /* 
       Offset low value
    */
    uint16  offset_low;
    /* 
       Offset high value
    */
    uint16  offset_high;
    /* 
       Offset low clamp value
    */
    uint16  offset_low_clamp;
    /* 
       Offset high clamp value
    */
    uint16  offset_high_clamp;
    } KBD_CAPACITIVE_KEY_TYPE2_SETTINGS_T;


/* ----------------------------------------------------------------------- */
/* Subblock: KBD_RAW_DATA_INFO - Valid from version 013.033                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   id;
    uint8   length;
    uint8   fill_byte;
    uint8   fill_byte1;
    /* 
       Upper 16-bits of raw data
    */
    uint16  high_byte;
    /* 
       Lower 16 bits of raw data
    */
    uint16  low_byte;
    } KBD_RAW_DATA_INFO_T;


/* ----------------------------------------------------------------------- */
/* Subblock: KBD_CONFIG_ACTION_ACTIVATION_MASK - Valid from version 013.041 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   id;
    uint8   length;
    /* 
       Defines which matrix rows are enabled
       XXXXXXXX XXXXXXX1 Activate row 0
       1XXXXXXX XXXXXXXX Activate row 15
    */
    uint16  matrix_row_mask;
    /* 
       Defines which matrix columns are enabled
       XXXXXXXX XXXXXXX1 Activate column 0
       1XXXXXXX XXXXXXX Activate column 15
    */
    uint16  matrix_column_mask;
    /* 
       Defines which GenIO keys are enabled
       XXXXXXXX XXXXXXX1 first GenIO key in configuration
    */
    uint16  genio_mask;
    /* 
       Defines which special keys are enabled
       XXXXXXX1 Slide/fold activation
       XXXXXX1X Power key activation
       XXXXX1XX Keylock activation
    */
    uint8   special_key_mask;
    uint8   fill_byte;
    uint8   fill_byte1;
    uint8   fill_byte2;
    } KBD_CONFIG_ACTION_ACTIVATION_MASK_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_EVENT_IND                                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill_byte;
    uint8   num_of_sub_blocks;
    /* Subblock list:
       KBD_POINTING_DEVICE_INFO
       KBD_ROLLER_KEY_INFO
       KBD_SINGLE_PRESS_KEY_EVENT_INFO
    */
    } KBD_EVENT_IND_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_ROTATOR_EVENT_IND                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* 
       Values from the constant table KBD_ROTATOR_MODE
    */
    uint8   mode;
    /* Values from the constant table KBD_ROTATOR_DIRECTION */
    uint8   direction;
    /* 
       Slow Mode = 1, Fast Mode = Cumulative ticks
    */
    uint16  ticks;
    /* Slow Mode = Angle of a single tick, 
       Fast Mode = Cumulative angle of the rotation
    */
    uint16  angle;
    } KBD_ROTATOR_EVENT_IND_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_INFO_REQ                                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill_byte1;
    uint8   fill_byte2;
    } KBD_INFO_REQ_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_INFO_RESP                                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* One bit for each keyboard technology.
       Keyboard OK = 0, Keyboard FAIL = 1
       Values from the bitmask table KBD_DEVICE_STATUS
    */
    uint8   kbd_devices;
    /* Special keys with own IO line (not KDI data port). 
       One bit for each key.
       Key up/closed = 0, Key down/open = 1
       Values from the bitmask table KBD_SPECIAL_KEY_STATUS
    */
    uint8   special_keys;
    /* Special keys with own IO line (KDI data port 0). 
       One bit for each key.
       Key up = 0, Key down = 1
       Values from the bitmask table KBD_SPECIAL_KEY_STATUS_KDI_P0
    */
    uint8   special_keys_p0;
    /* Special keys with own IO line (KDI data port 1). 
       One bit for each key.
       Key up = 0, Key down = 1
       Values from the bitmask table KBD_SPECIAL_KEY_STATUS_KDI_P1
    */
    uint8   special_keys_p1;
    /* Multi-press key status, One bit for every multi-press key.
       Key OK = 0, Key FAIL = 1
       Values from the bitmask table KBD_MULTI_KEY_STATUS
    */
    uint8   multi_press_keys;
    uint8   fill_byte1;
    } KBD_INFO_RESP_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_CONFIG_REQ                                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Keyboard deactivate = 0x01, Keyboard activate = 0x02, Simulation
       deactivate = 0x03, Simulation activate = 0x04,Keyboard and simulation
       deactivate = 0x05, Keyboard and simulation activate = 0x06, Activate
       selected keys = 0x07
       Values from the constant table KBD_CONFIG_ACTION
    */
    uint8   kbd_config_action;
    /* Currently only single block is allowed, others are ignored. */
    uint8   num_of_sub_blocks;
    /* Subblock list:
       KBD_CONFIG_ACTION_ACTIVATION_MASK
    */
    uint8   subblocks[KBD_ANY_SIZE];
    } KBD_CONFIG_REQ_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_CONFIG_RESP                                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* One bit for each keyboard technology.
       Keyboard not present = 0, Keyboard present = 1
       Values from the bitmask table KBD_DEVICE_STATUS
    */
    uint8   kbd_devices;
    /* Special keys with own I/O line (not KDI data port).
       One bit for each key.
       Key not present = 0, Key present = 1
       Values from the bitmask table KBD_SPECIAL_KEY_STATUS
    */
    uint8   special_keys;
    /* Special keys with own I/O line (KDI data port 0).
       One bit for each key.
       Key not present = 0, Key present = 1
       Values from the bitmask table KBD_SPECIAL_KEY_STATUS_KDI_P0
    */
    uint8   special_keys_p0;
    /* Special keys with own I/O line (KDI data port 1).
       One bit for each key.
       Key not present = 0, Key present = 1
       Values from the bitmask table KBD_SPECIAL_KEY_STATUS_KDI_P1
    */
    uint8   special_keys_p1;
    /* Multi-press key status, One bit for every multi-press key.
       Key not present = 0, Key present = 1
       Values from the bitmask table KBD_MULTI_KEY_STATUS
    */
    uint8   multi_press_keys;
    uint8   num_of_soft_keys;
    } KBD_CONFIG_RESP_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_ROTATOR_CONTROL_REQ                                        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Values from the constant table KBD_ROTATOR_CONTROL_ACTION */
    uint8   action;
    uint8   num_of_sub_blocks;
    /* Subblock list: */
    } KBD_ROTATOR_CONTROL_REQ_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_ROTATOR_CONTROL_RESP                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Values from the constant table KBD_ROTATOR_CONTROL_STATUS */
    uint8   status;
    uint8   num_of_sub_blocks;
    /* Subblock list: */
    } KBD_ROTATOR_CONTROL_RESP_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_CONTROL_REQ                                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   action;   /* Values from the constant table KBD_CONTROL_ACTION */
    uint8   num_of_sub_blocks;
    /* Subblock list: */
    } KBD_CONTROL_REQ_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_CONTROL_RESP                                               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   status;       /* Values from the constant table KBD_STATUS */
    uint8   num_of_sub_blocks;
    /* Subblock list: */
    } KBD_CONTROL_RESP_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_PWR_KEY_CHECK_REQ                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill_byte1;
    uint8   fill_byte2;
    } KBD_PWR_KEY_CHECK_REQ_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_PWR_KEY_CHECK_RESP                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   status;   /* Values from the constant table KBD_PWR_KEY_STATUS */
    uint8   fill_byte;
    } KBD_PWR_KEY_CHECK_RESP_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_PWR_KEY_INFO_IND                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* A subset of values from the constant table KBD_PWR_KEY_STATUS */
    uint8   status;
    uint8   fill_byte;
    } KBD_PWR_KEY_INFO_IND_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_EVENT_SIMULATION_REQ                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill_byte;
    uint8   num_of_sub_blocks;
    /* Subblock list:
       KBD_POINTING_DEVICE_INFO
       KBD_ROLLER_KEY_INFO
       KBD_ROTATOR_EVENT_INFO
       KBD_SINGLE_PRESS_KEY_EVENT_INFO
    */
    } KBD_EVENT_SIMULATION_REQ_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_EVENT_SIMULATION_RESP                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   status;       /* Values from the constant table KBD_STATUS */
    uint8   fill_byte;
    } KBD_EVENT_SIMULATION_RESP_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_TEST_REQ                                                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   action;      /* Values from the constant table KBD_TEST_ACTION */
    uint8   num_of_sub_blocks;
    /* Subblock list: */
    } KBD_TEST_REQ_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_TEST_RESP                                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   status;      /* Values from the constant table KBD_TEST_STATUS */
    uint8   num_of_sub_blocks;
    /* Subblock list:
       KBD_TEST_UI_KEY_RESULT
       KBD_TEST_UI_ROTATOR_RESULT
    */
    } KBD_TEST_RESP_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_BUFFERING_CONTROL_REQ                                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   action; /* Values from the constant table KBD_BUFFERING_ACTION */
    uint8   fill_byte;
    } KBD_BUFFERING_CONTROL_REQ_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_BUFFERING_CONTROL_RESP                                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   status;       /* Values from the constant table KBD_STATUS */
    uint8   fill_byte;
    } KBD_BUFFERING_CONTROL_RESP_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_BUFFERING_ACK_NTF                                          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   fill_byte1;
    uint8   fill_byte2;
    } KBD_BUFFERING_ACK_NTF_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_POINTING_DEVICE_CONTROL_REQ - Valid from version 013.028   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Values from the constant table KBD_POINTING_DEVICE_CONTROL_ACTION */
    uint8   action;
    uint8   num_of_sub_blocks;
    /* Subblock list: */
    } KBD_POINTING_DEVICE_REQ_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_POINTING_DEVICE_CONTROL_RESP - Valid from version 013.028  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   status;       /* Values from the constant table KBD_STATUS */
    uint8   num_of_sub_blocks;
    /* Subblock list: */
    } KBD_POINTING_DEVICE_RESP_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_CAPACITIVE_KEY_CONTROL_REQ - Valid from version 013.031    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint16  num_of_sub_blocks;
    /* Subblock list:
       KBD_CAPACITIVE_KEY_GLOBAL_SETTINGS
       KBD_CAPACITIVE_KEY_TYPE1_SETTINGS
       KBD_CAPACITIVE_KEY_TYPE2_SETTINGS
    */
    uint8   subblocks[KBD_ANY_SIZE];
    } KBD_CAPACITIVE_KEY_CONTROL_REQ_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_CAPACITIVE_KEY_CONTROL_RESP - Valid from version 013.031   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   status;       /* Values from the constant table KBD_STATUS */
    uint8   num_of_sub_blocks;
    /* Subblock list: */
    } KBD_CAPACITIVE_KEY_CONTROL_RESP_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_READ_RAW_DATA_REQ - Valid from version 013.033             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Values from the constant table KBD_READ_RAW_DATA_DEVICE */
    uint8   device_id;
    uint8   fill_byte;
    } KBD_READ_RAW_DATA_REQ_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_READ_RAW_DATA_RESP - Valid from version 013.033            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    uint8   status;       /* Values from the constant table KBD_STATUS */
    uint8   fill_byte;
    uint8   fill_byte1;
    /* Values from the constant table KBD_READ_RAW_DATA_SIZE */
    uint8   register_size;
    uint16  num_of_sub_blocks;
    /* Subblock list:
       KBD_RAW_DATA_INFO
    */
    uint8   subblocks[KBD_ANY_SIZE];
    } KBD_READ_RAW_DATA_RESP_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_POWER_CONTROL_REQ - Valid from version 013.036             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* Values from the constant table KBD_POWER_CONTROL_DEVICE_ID */
    uint8   device_id;
    /* Values from the constant table KBD_POWER_CONTROL_MODE */
    uint8   power_mode;
    } KBD_POWER_CONTROL_REQ_T;


/* ----------------------------------------------------------------------- */
/* Message: KBD_POWER_CONTROL_RESP - Valid from version 013.036            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   transaction_id;
    uint8   message_id;
    /* KBD_OK = success, KBD_FAIL = not supported or stepping reached limit.
       Values from the constant table KBD_STATUS
    */
    uint8   status;
    uint8   fill_byte;
    } KBD_POWER_CONTROL_RESP_T;




/* ----------------------------------------------------------------------- */
/* Notes                                                                   */
/* ----------------------------------------------------------------------- */
/*
   /1/  Autogeneration Process
        Intranet
        http://tracing.europe.nokia.com/autogen/documentation.asp
        Filename: autogen_proc.doc

   /2/  ISI Server Specification Documentation Guidelines
        Document code:   XXXL7714-EN
        DocMan location: eslns42/SRV/Nokia
        DocMan:          TP/WP Front End DocMan
        Filename:        TP/WP/tpwpfendm.nsf

   /3/  ISI General Information
        Document code:   XXXL7715-EN
        DocMan location: eslns42/SRV/Nokia
        DocMan:          TP/WP Front End DocMan
        Filename:        TP/WP/tpwpfendm.nsf

   /4/  ISI Common Message Descriptions
        Continuus Database: ou1gif
        Continuus Project:  GIF_SPECS-ou1gif#browse
        Directory Path:     GIF_SPECS/CoreSW
        Filename:           i_comm_m.doc

   /5/  ISI Common Feature Descriptions
        Continuus Database: ou1gif
        Continuus Project:  GIF_SPECS-ou1gif#browse
        Directory Path:     GIF_SPECS/CoreSW
        Filename:           i_comm_fp.doc

   /6/  ISI KBD Server Feature Descriptions
        Continuus Database: ou1gif
        Continuus Project:  GIF_SPECS-ou1gif#browse
        Directory Path:     GIF_SPECS/CoreSW
        Filename:           i_kbd_f.doc
*/


#endif /* _SRVKBD_ISI_H */
